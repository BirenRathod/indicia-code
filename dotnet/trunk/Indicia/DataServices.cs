using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using System.Xml.Linq;
using Indicia.Security;
using Newtonsoft.Json;
using Indicia;
using Newtonsoft.Json.Linq;

namespace Indicia.DataServices
{
    //TODO: caching

    /// <summary>
    /// 
    /// </summary>
    public class DataService
    {
        private const String SERVICEURL = "index.php/services/data/";
        private const String SAVEDATA = "save";
        private const String TERMLIST = "termlists_term";
        private const String TAXALIST = "cache_taxon_searchterm";//"taxa_taxon_list";
        private const String SAMPLEATTRIBUTELIST = "sample_attribute";
        private const String OCCURRENCEATTRIBUTELIST = "occurrence_attribute";
        private const String LOCATIONATTRIBUTELIST = "location_attribute";

        public enum Method
        {
            GET,
            POST
        }

        public enum Mode
        {
            json,
            csv,
            nbn,
            xml
        }

        public enum View
        {
            detail,
            gv,
            list
        }

        private enum IndiciaTokenType
        {
            read,
            write
        }

        private Method _method = Method.GET;
        private Mode _mode = Mode.json;
        private View _view = View.list;
        private String _warehouseURL;
        private Uri _serviceURI;
        private WebRequest _req;
        private String _JSON;
        private Dictionary<String, String> _requestData;
        private IndiciaToken _indiciaToken = IndiciaToken.Instance;
        private IndiciaTokenType _tokenType = IndiciaTokenType.read;
        private int _numRetries;

        #region setters

        private Method DataMethod
        {
            get { return _method; }
            set { _method = value; }
        }

        private Mode DataMode
        {
            get { return _mode; }
            set { _mode = value; }
        }

        private View DataView
        {
            get { return _view; }
            set { _view = value; }
        }

        /// <summary>
        /// Request object that will be sent. Provided for convenience, calling the matching method for the Indicia service required will set required fields
        /// </summary>
        public WebRequest Request
        {
            get { return _req; }
            set { _req = value; }
        }

        /// <summary>
        /// URL of Indicia warehouse to send request to
        /// </summary>
        public String WarehouseURL
        {
            get { return _warehouseURL; }
            private set { _warehouseURL = WarehouseURL; _serviceURI = new Uri(new Uri(_warehouseURL), SERVICEURL); }
        }

        /// <summary>
        /// Data to send with request, KVP of [Name], [Value]
        /// </summary>
        public Dictionary<String, String> RequestData
        {
            get { return _requestData; }
            set { _requestData = value; }
        }

        #endregion

        /// <summary>
        /// This class allows requests to be made to an Indicia Warehouse
        /// </summary>
        /// <remarks>
        /// Currently implemented Indicia services: Save (sample); get sample_attribute, get occurrence_attribute, get location_attribute, cache_taxon_searchterm, termlists_term
        /// </remarks>
        public DataService()
        {
            _warehouseURL = ConfigurationManager.AppSettings["Indicia_WarehouseURL"];
            if (String.IsNullOrEmpty(_warehouseURL))
            { throw new ConfigurationException("Application setting Indicia_WarehouseURL required"); }

            string numRetries = ConfigurationManager.AppSettings["Indicia_NumTokenRetries"];
            if (String.IsNullOrEmpty(numRetries))
            { throw new ConfigurationException("Application setting Indicia_NumTokenRetries required"); }
            else
            {
                int.TryParse(numRetries, out _numRetries);
                if (_numRetries <= 0)
                { throw new ConfigurationException("Application setting Indicia_NumTokenRetries must be a positive integer"); }
            }

            _serviceURI = new Uri(new Uri(_warehouseURL), SERVICEURL);
            RequestData = new Dictionary<String, String>();
        }

        /// <summary>
        /// Submit a sample to Indicia Warehouse
        /// Required post parameters: "submission" : {JSON containing sample}
        /// </summary>
        /// <returns>Success, or JSON from Indicia Warehouse describing validation failures</returns>
        public dynamic SaveData()
        {
            Uri URL = new Uri(_serviceURI, SAVEDATA);
            _tokenType = IndiciaTokenType.write;
            _method = Method.POST;
            BuildRequest(URL);
            return MakeRequest();
        }

        /// <summary>
        /// Get Term List. List of options for Indicia Survey question
        /// Required get parameters: termlist_id:  int 
        /// </summary>
        /// <returns>List of TermItem</returns>
        public List<TermItem> GetTermList()
        {
            Uri URL = new Uri(_serviceURI, TERMLIST);
            _tokenType = IndiciaTokenType.read;
            BuildRequest(URL);
            var jsonResponse = MakeRequest();
            List<TermItem> tmp = jsonResponse.ToObject<List<TermItem>>();
            return tmp.OrderBy(t => t.SortOrder).ToList();
        }

        /// <summary>
        /// Get possible matches from taxon list 
        /// Example get parameters: "taxon_list_id":  int (required)
        /// "limit": "100"
        /// "q", "fox"
        /// "qfield", "searchterm"
        /// "query", "{\"where\":[\"(simplified='t' or simplified is null) AND (preferred='t' or language_iso<>'lat')\"]}
        /// More information in Indicia docs
        /// </summary>
        /// <returns>List of TaxonSearchItem</returns>
        public List<TaxonSearchItem> GetTaxaSearchList()
        {
            Uri URL = new Uri(_serviceURI, TAXALIST);
            _tokenType = IndiciaTokenType.read;
            BuildRequest(URL);
            var jsonResponse = MakeRequest();
            return jsonResponse.ToObject<List<TaxonSearchItem>>();
        }

        /// <summary>
        /// Gets attribute list for Indicia Survey from Indicia Warehouse
        /// Required get parameters: restrict_to_survey_id:  int id 
        /// </summary>
        /// <returns>List of SurveyAttribute</returns>
        public List<SurveyAttribute> GetSurvey()
        {
            List<SurveyAttribute> attrs = new List<SurveyAttribute>();
            _tokenType = IndiciaTokenType.read;
            //samples
            Uri URL = new Uri(_serviceURI, SAMPLEATTRIBUTELIST);
            BuildRequest(URL);
            var jsonResponse = MakeRequest();
            List<SurveyAttribute> sa = jsonResponse.ToObject<List<SurveyAttribute>>();
            sa.ForEach(a => a.AttributeType = SurveyAttributeType.sample);
            attrs.AddRange(sa);

            //occurences
            URL = new Uri(_serviceURI, OCCURRENCEATTRIBUTELIST);
            BuildRequest(URL);
            jsonResponse = MakeRequest();
            List<SurveyAttribute> sa2 = jsonResponse.ToObject<List<SurveyAttribute>>();
            sa2.ForEach(a => a.AttributeType = SurveyAttributeType.occurrence);
            attrs.AddRange(sa2);

            //locations
            URL = new Uri(_serviceURI, LOCATIONATTRIBUTELIST);
            BuildRequest(URL);
            jsonResponse = MakeRequest();
            List<SurveyAttribute> sa3 = jsonResponse.ToObject<List<SurveyAttribute>>();
            sa3.ForEach(a => a.AttributeType = SurveyAttributeType.location);
            attrs.AddRange(sa3);

            return attrs;
        }

        private dynamic MakeRequest()
        {
            int count = 0;

            StreamReader stIn = new StreamReader(_req.GetResponse().GetResponseStream());
            string strResponse = stIn.ReadToEnd();
            stIn.Close();
            dynamic data = JsonConvert.DeserializeObject<dynamic>(strResponse);

            while (count < _numRetries)
            {
                count += 1;
                String errMsg = null;
                String errCode = null;

                if ((data is JObject) && (data["error"] != null))
                {
                    errMsg = data.error;
                    errCode = data.code;

                    if (errCode == "1") //token expired
                    {
                        switch (_tokenType)
                        {
                            case IndiciaTokenType.read:
                                _indiciaToken.RefreshReadToken();
                                break;
                            case IndiciaTokenType.write:
                                _indiciaToken.RefreshWriteToken();
                                break;
                        }
                        BuildRequest(_req.RequestUri);
                        stIn = new StreamReader(_req.GetResponse().GetResponseStream());
                        strResponse = stIn.ReadToEnd();
                        stIn.Close();
                        data = JsonConvert.DeserializeObject<dynamic>(strResponse);
                    }
                    else
                    {
                        if (data["errors"] != null)
                        {
                            errMsg += "; " + data.errors;
                        }
                        ArgumentException ex = new ArgumentException(errMsg);
                        ex.Data.Add("IndiciaCode", errCode);
                        throw ex;
                    }
                }
                else
                {
                    break; //exit loop as no error}
                }
            }
            return data;
        }

        private void BuildRequest(Uri URL)
        {
            UriBuilder ub = new UriBuilder(URL);
            System.Collections.Specialized.NameValueCollection queryString = HttpUtility.ParseQueryString(URL.Query);
            StringBuilder postContent = new StringBuilder();

            switch (_tokenType)
            {
                case IndiciaTokenType.read:
                    queryString.Add("nonce", _indiciaToken.ReadToken.Nonce);
                    queryString.Add("auth_token", _indiciaToken.ReadToken.AuthToken);
                    break;
                case IndiciaTokenType.write:
                    queryString.Add("nonce", _indiciaToken.WriteToken.Nonce);
                    queryString.Add("auth_token", _indiciaToken.WriteToken.AuthToken);
                    break;
            }

            switch (_method)
            {
                case Method.GET:

                    foreach (KeyValuePair<String, String> kvp in RequestData)
                    {
                        if (queryString.Get(kvp.Key) == null)
                        { queryString.Add(kvp.Key, kvp.Value); }
                        else { queryString[kvp.Key] = kvp.Value; }
                    }
                    break;

                case Method.POST:
                    postContent.Append("mode=" + _mode.ToString());
                    foreach (KeyValuePair<String, String> kvp in RequestData)
                    {
                        postContent.Append("&" + kvp.Key + "=" + kvp.Value);
                    }
                    break;
            }

            ub.Query = queryString.ToString();
            _req = WebRequest.Create(ub.Uri);
            _req.Method = _method.ToString();

            if (_method == Method.POST)
            {
                _req.ContentType = "application/x-www-form-urlencoded";
                byte[] bytes = System.Text.Encoding.ASCII.GetBytes(postContent.ToString());
                _req.ContentLength = bytes.Length;
                System.IO.Stream stOut = _req.GetRequestStream();
                stOut.Write(bytes, 0, bytes.Length);
                stOut.Close();
            }
        }
    }
}
