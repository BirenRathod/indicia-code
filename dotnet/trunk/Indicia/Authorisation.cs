using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Indicia.Security
{
	public class Authorisation
	{

		public enum AuthorisationTokenType
		{
			Read
		 , Write
		}

		/// <summary>
		/// 
		/// </summary>
		public class AuthorisationToken
		{
			private string _nonce;
			private byte[] _token;
			private AuthorisationTokenType _tokenType;

			/// <summary>
			/// Contains authorisation data for connecting to an Indicia Warehouse
			/// </summary>
			/// <param name="nonce">Nonce returned by Indicia webservice</param>
			/// <param name="token">Encrypted authorisation token</param>
			/// <param name="TokenType">Token is authorised for read or write access</param>
			public AuthorisationToken(string nonce, byte[] token, AuthorisationTokenType TokenType)
			{
				this._nonce = nonce;
				this._token = token;
				this._tokenType = TokenType;		
			}

			/// <summary>
			/// Nonce returned from Indicia WebService
			/// </summary>
			public string Nonce
			{
				get { return _nonce; }
				private set { _nonce = value; }
			}

			/// <summary>
			/// Authorisation Token as byte[]
			/// </summary>
			public byte[] Token
			{
				get { return _token; }
				private set { _token = value; }
			}

			/// <summary>
			/// Authorisation Token as formatted string. Use this to send requests to Indicia WebService
			/// </summary>
			public string AuthToken
			{
				get { return BitConverter.ToString(_token).Replace("-", "").ToLower(); } //Indicia needs token in lowercase, .NET produces uppercase.
				private set { }
			}

			/// <summary>
			/// Token is authorised for Read or Write
			/// </summary>
			public AuthorisationTokenType TokenType
			{
				get { return _tokenType; }
				private set { _tokenType = value; }
			}
		}
		//TODO: implement indicia service user_identifier/get_user_id
	}
}
