using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;
using System.Security.Cryptography;
using Newtonsoft.Json;
using System.Configuration;
using System.Threading;

namespace Indicia.Security
{
    /// <summary>
    /// Class to authenticate website to an Indicia Warehouse
    /// https://indicia-docs.readthedocs.org/en/latest/developing/web-services/security-services-details/index.html
    /// </summary>
    public sealed class IndiciaToken
    {
        private const String SERVICEURL = "index.php/services/security/";
        private const String READNONCE = "get_read_nonce";
        private const String WRITENONCE = "get_nonce";
        private const String READWRITENONCES = "get_read_write_nonces";

        private static volatile IndiciaToken instance = null;
        private static readonly object padlock = new object();
        private static readonly object padlockGetReadToken = new object();
        private static readonly object padlockGetWriteToken = new object();
        private static readonly object padlockRefreshReadToken = new object();
        private static readonly object padlockRefreshWriteToken = new object();

        private Authorisation.AuthorisationToken _readToken;
        private Authorisation.AuthorisationToken _writeToken;

        // "WarehouseURL"  Domain of Indicia Warehouse
        // "WebsiteID"  ID of website registered on the Indicia Warehouse given in WarehouseURL
        // "Password"  Password of website registered on the Indicia Warehouse given in WarehouseURL
        private String _warehouseURL;
        private String _websiteID;
        private String _websitePassword;

        private static Uri _serviceURI;

        private IndiciaToken()
        {
            _warehouseURL = ConfigurationManager.AppSettings["Indicia_WarehouseURL"];
            if (String.IsNullOrEmpty(_warehouseURL))
            { throw new ConfigurationException("Application setting Indicia_WarehouseURL required"); }

            _websiteID = ConfigurationManager.AppSettings["Indicia_WebsiteID"];
            if (String.IsNullOrEmpty(_websiteID))
            { throw new ConfigurationException("Application setting Indicia_WebsiteID required"); }
            else
            {
                int tempID;
                int.TryParse(_websiteID, out tempID);
                if (tempID <= 0)
                { throw new ConfigurationException("Application setting Indicia_WebsiteID must be a positive integer"); }
            }

            _websitePassword = ConfigurationManager.AppSettings["Indicia_WebsitePassword"];
            if (String.IsNullOrEmpty(_websitePassword))
            { throw new ConfigurationException("Application setting Indicia_WebsitePassword required"); }

            _serviceURI = new Uri(new Uri(_warehouseURL), SERVICEURL);
            _readToken = GetReadToken();
            _writeToken = GetWriteToken();
        }

        public static IndiciaToken Instance
        {
            get
            {
                lock (padlock)
                {
                    if (instance == null)
                    {
                        instance = new IndiciaToken();
                    }
                    return instance;
                }
            }
        }

        public Authorisation.AuthorisationToken ReadToken
        {
            get
            {
                lock (padlockGetReadToken)
                {
                    return _readToken;
                }
            }
            private set
            {
                lock (padlockGetReadToken)
                {
                    _readToken = value;
                }
            }
        }

        public Authorisation.AuthorisationToken WriteToken
        {
            get
            {
                lock (padlockGetWriteToken)
                {
                    return _writeToken;
                }
            }
            private set
            {
                lock (padlockGetWriteToken)
                {
                    _writeToken = value;
                }
            }
        }

        /// <summary>
        /// Request new read token from Indicia Warehouse
        /// </summary>
        public void RefreshReadToken()
        {
            Boolean haveEntered = false;

            try
            {
                if (Monitor.TryEnter(padlockRefreshReadToken))
                {
                    haveEntered = true;
                    //possible api call to check token expiration, if expired? for case when two calls come in at once. one will proceed, the other wait.
                    ReadToken = GetReadToken();
                    Monitor.Exit(padlockRefreshReadToken);
                    haveEntered = false;
                }
                else
                {
                    //wait for refresh to finish
                    Monitor.Enter(padlockRefreshReadToken);
                    haveEntered = true;
                    Monitor.Exit(padlockRefreshReadToken);
                    haveEntered = false;
                }
            }
            finally
            {
                if (haveEntered)
                {
                    Monitor.Exit(padlockRefreshReadToken);
                }
            }
        }

        /// <summary>
        /// Request new write token from Indicia Warehouse
        /// </summary>
        public void RefreshWriteToken()
        {
            Boolean haveEntered = false;

            try
            {
                if (Monitor.TryEnter(padlockRefreshWriteToken))
                {
                    haveEntered = true;
                    WriteToken = GetWriteToken();
                    Monitor.Exit(padlockRefreshWriteToken);
                    haveEntered = false;
                }
                else
                {
                    //wait for refresh to finish
                    Monitor.Enter(padlockRefreshWriteToken);
                    haveEntered = true;
                    Monitor.Exit(padlockRefreshWriteToken);
                    haveEntered = false;
                }
            }
            finally
            {
                if (haveEntered)
                {
                    Monitor.Exit(padlockRefreshWriteToken);
                }
            }
        }

        /// <summary>
        /// Gets a read token from the Indicia Warehouse
        /// </summary>
        /// <returns>Indicia Read Authorisation token</returns>
        private Authorisation.AuthorisationToken GetReadToken()
        {
            Uri URL = new Uri(_serviceURI, READNONCE);
            string nonce = GetNonce(URL);
            byte[] authToken = GetAuthToken(nonce);

            Authorisation.AuthorisationToken token = new Authorisation.AuthorisationToken(nonce, authToken, Authorisation.AuthorisationTokenType.Read);
            return token;
        }

        /// <summary>
        /// Gets a write token from the Indicia Warehouse
        /// </summary>
        /// <returns>Indicia Write Authorisation token</returns>
        private Authorisation.AuthorisationToken GetWriteToken()
        {
            Uri URL = new Uri(_serviceURI, WRITENONCE);
            string nonce = GetNonce(URL);
            byte[] authToken = GetAuthToken(nonce);

            Authorisation.AuthorisationToken token = new Authorisation.AuthorisationToken(nonce, authToken, Authorisation.AuthorisationTokenType.Write);
            return token;
        }

        /// <summary>
        /// Gets both read and write tokens from the Indicia Warehouse
        /// </summary>
        /// <returns>
        /// List of two AuthorisationTokens
        /// First is Read
        /// Second is Write
        /// </returns>
        private List<Authorisation.AuthorisationToken> GetReadWriteTokens()
        {
            Uri URL = new Uri(_serviceURI, READWRITENONCES);
            string responseJSON = GetNonce(URL);

            Dictionary<string, string> jsonTokens = JsonConvert.DeserializeObject<Dictionary<string, string>>(responseJSON);

            List<Authorisation.AuthorisationToken> tokens = new List<Authorisation.AuthorisationToken>(2);
            byte[] token = GetAuthToken(jsonTokens["read"]);
            tokens.Add(new Authorisation.AuthorisationToken(jsonTokens["read"], token, Authorisation.AuthorisationTokenType.Read));

            token = GetAuthToken(jsonTokens["write"]);
            tokens.Add(new Authorisation.AuthorisationToken(jsonTokens["write"], token, Authorisation.AuthorisationTokenType.Write));

            return tokens;
        }

        /// <summary>
        /// Requests nonce from Indicia Warehouse
        /// </summary>
        /// <param name="URL">URL to API method</param>
        /// <returns>String containing nonce returned from Indicia API</returns>
        private string GetNonce(Uri URL)
        {
            WebRequest req = WebRequest.Create(URL);
            req.Method = "POST";
            req.ContentType = "application/x-www-form-urlencoded";

            string urlParams = "website_id=" + _websiteID;
            req.ContentLength = urlParams.Length;

            StreamWriter stOut = new StreamWriter(req.GetRequestStream(), System.Text.Encoding.ASCII);
            stOut.Write(urlParams);
            stOut.Close();

            StreamReader stIn = new StreamReader(req.GetResponse().GetResponseStream());
            string strResponse = stIn.ReadToEnd(); //nonce
            stIn.Close();

            return strResponse;
        }

        /// <summary>
        /// Encrypts nonce and other data to create authorisation token
        /// </summary>
        /// <param name="nonce">Nonce requested from Indicia API</param>
        /// <returns>Byte[] containing Authorisation Token</returns>
        private byte[] GetAuthToken(string nonce)
        {
            Encoding encoder = new UTF8Encoding();
            System.Security.Cryptography.SHA1 crypto = System.Security.Cryptography.SHA1.Create();
            return crypto.ComputeHash(encoder.GetBytes(nonce + ":" + _websitePassword));  //auth token
        }

    }
}
