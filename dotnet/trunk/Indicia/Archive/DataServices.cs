using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Indicia.Security;
using System.Net;
using System.Web;
using System.IO;
using Newtonsoft.Json;
using System.Collections;

namespace Indicia.DataServices
{
	//	{
	//  "id":"sample",
	//  "fields":{
	//	 "website_id":{"value":"1"},
	//	 "survey_id":{"value":"1"},
	//	 "entered_sref":{"value":"SP41"},
	//	 "geom":{"value":"POLYGON((-158240.806825904 6761745.97504841,-158112.504644672
	//		  6777941.30688427,-141943.016288715 6777796.17577468,-142103.477852791
	//		  6761601.59748373,-158240.806825904 6761745.97504841))"},
	//	 "entered_sref_system":{"value":"OSGB"},
	//	 "date":{"value":"2013-06-13"},
	//	 "comment":{"value":"This is an example record"},
	//	 "smpAttr:3":{"value":"158"},
	//	 "smpAttr:41":{"value":""},
	//	 "input_form":{"value":"node\/69"}
	//  },
	//  "subModels":[
	//	 {
	//		"fkId":"sample_id",
	//		"model":{
	//		  "id":"occurrence",
	//		  "fields":{
	//			 "zero_abundance":{"value":"f"},
	//			 "taxa_taxon_list_id":{"value":"30"},
	//			 "website_id":{"value":"1"},
	//			 "record_status":{"value":"C"}
	//		  }
	//		}
	//	 },
	//	 {
	//		"fkId":"sample_id",
	//		"model":{
	//		  "id":"occurrence",
	//		  "fields":{
	//			 "zero_abundance":{"value":"f"},
	//			 "taxa_taxon_list_id":{"value":"34"},
	//			 "website_id":{"value":"1"},
	//			 "record_status":{"value":"C"}
	//		  }
	//		}
	//	 }
	//  ]
	//}


	public class DataService
	{

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

		public enum AttributeType
		{
			loc,
			occ,
			psn,
			smp
		}

		private const String SERVICEURL = "index.php/services/data/";
		private const String OCCURRENCE = "occurrence";
		private const String SAVEDATA = "save";

		public Authorisation.AuthorisationToken _authToken;
		public Method _method = Method.GET;
		public Mode _mode;
		public View _view;
		//public String _wantRecords;
		//public String _wantColumns;
		//public String _wantCount;
		public String _warehouseURL;
		public Uri _serviceURI;
		public WebRequest _req;
		public String _JSON;
		public Dictionary<String, String> RequestData;

		public DataService(String WarehouseURL)
		{
			_warehouseURL = WarehouseURL;
			//create standard which creates basic url with params
			_serviceURI = new Uri(new Uri(_warehouseURL), SERVICEURL);
		}

		public WebRequest Request
		{
			get { return _req; }

			set { _req = value; }
		}

		public String WarehouseURL
		{
			get { return _warehouseURL; }
			set { _warehouseURL = WarehouseURL; _serviceURI = new Uri(new Uri(_warehouseURL), SERVICEURL); }
		}

		public String SaveData()
		{
			Uri URL = new Uri(_serviceURI, SAVEDATA);

			BuildRequest(URL);

			StreamReader stIn = new StreamReader(_req.GetResponse().GetResponseStream());
			string strResponse = stIn.ReadToEnd();
			stIn.Close();
			return strResponse;
		}


		//private void BuildRequest(Uri URL)
		//{
		//	UriBuilder ub = new UriBuilder(URL);
		//	System.Collections.Specialized.NameValueCollection queryString = HttpUtility.ParseQueryString(URL.Query);

		//	if (queryString.Get("nonce") == null)
		//	{ queryString.Add("nonce", _authToken.Nonce); }
		//	else { queryString["nonce"] = _authToken.Nonce; }

		//	if (queryString.Get("auth_token") == null)
		//	{ queryString.Add("auth_token", _authToken.AuthToken); }
		//	else { queryString["auth_token"] = _authToken.AuthToken; }

		//	switch (_method)
		//	{
		//		case Method.GET:
		//			foreach (KeyValuePair<String, String> param in RequestData)
		//			{
		//				if (queryString.Get(param.Key) == null)
		//				{ queryString.Add(param.Key, param.Value); }
		//				else { queryString[param.Key] = param.Value; }
		//			}
		//			break;

		//		case Method.POST:
		//			{
		//				JsonSerializer js = new JsonSerializer();
		//			}
		//			break;
		//	}
		//	ub.Query = queryString.ToString();
		//	_req = WebRequest.Create(ub.Uri);
		//}

		private void BuildRequest(Uri URL)
		{

			UriBuilder ub = new UriBuilder(URL);
			System.Collections.Specialized.NameValueCollection queryString = HttpUtility.ParseQueryString(URL.Query);
			switch (_method)
			{
				case Method.GET:

					if (queryString.Get("mode") == null)
					{ queryString.Add("mode", _mode.ToString()); }
					else { queryString["mode"] = _mode.ToString(); }

					if (queryString.Get("view") == null)
					{ queryString.Add("view", _view.ToString()); }
					else { queryString["view"] = _view.ToString(); }

					//if (queryString.Get("wantRecords") == null)
					//{ queryString.Add("wantRecords", _wantRecords.ToString()); }
					//else { queryString["wantRecords"] = _wantRecords.ToString(); }

					//if (queryString.Get("wantColumns") == null)
					//{ queryString.Add("wantColumns", _wantColumns.ToString()); }
					//else { queryString["wantColumns"] = _wantColumns.ToString(); }

					//if (queryString.Get("wantCount") == null)
					//{ queryString.Add("wantCount", _wantCount.ToString()); }
					//else { queryString["wantCount"] = _wantCount.ToString(); }

					if (queryString.Get("nonce") == null)
					{ queryString.Add("nonce", _authToken.Nonce); }
					else { queryString["nonce"] = _authToken.Nonce; }

					if (queryString.Get("auth_token") == null)
					{ queryString.Add("auth_token", _authToken.AuthToken); }
					else { queryString["auth_token"] = _authToken.AuthToken; }

					if (queryString.Get("submission") == null)
					{ queryString.Add("submission", _JSON); }
					else { queryString["submission"] = _JSON; }

					ub.Query = queryString.ToString();
					_req = WebRequest.Create(ub.Uri);

					break;


				case Method.POST:

					if (queryString.Get("nonce") == null)
					{ queryString.Add("nonce", _authToken.Nonce); }
					else { queryString["nonce"] = _authToken.Nonce; }

					if (queryString.Get("auth_token") == null)
					{ queryString.Add("auth_token", _authToken.AuthToken); }
					else { queryString["auth_token"] = _authToken.AuthToken; }

					ub.Query = queryString.ToString();
					_req = WebRequest.Create(ub.Uri);

					_req.ContentType = "application/x-www-form-urlencoded";
					_req.Method = _method.ToString();
					string urlParams = "mode=" + _mode.ToString();
					//		urlParams += "&view=" + _view.ToString();
					//		urlParams += "&wantRecords=" + _wantRecords;
					//		urlParams += "&wantColumns=" + _wantColumns;
					//		urlParams += "&wantColumns=" + _wantCount;
					urlParams += "&submission=" + _JSON;
					byte[] bytes = System.Text.Encoding.ASCII.GetBytes(urlParams);

					_req.ContentLength = bytes.Length;

					System.IO.Stream stOut = _req.GetRequestStream();
					stOut.Write(bytes, 0, bytes.Length);
					stOut.Close();

					break;
			}
		}
	}


	//public class Sample
	//{
	//	public String id = "sample";
	//	public Dictionary<String, Dictionary<String, String>> fields;
	//	public List<SubModel> subModels;

	//	private const String FIELD_WEBSITE_ID = "website_id";
	//	private const String FIELD_SURVEY_ID = "survey_id";
	//	private const String FIELD_LOCATION_ID = "location_id";
	//	private const String FIELD_DATE_START = "date_start";
	//	private const String FIELD_DATE_END = "date_end";
	//	private const String FIELD_DATE_TYPE = "date_type";
	//	private const String FIELD_SREF_VALUE = "entered_sref";
	//	private const String FIELD_SREF_SYSTEM = "entered_sref_system";
	//	private const String FIELD_GEOM = "geom";
	//	private const String FIELD_LOCATION_NAME = "location_name";
	//	private const String FIELD_EXTERNAL_KEY = "external_key";
	//	private const String FIELD_COMMENT = "comment";
	//	private const String FIELD_DELETED = "deleted";
	//	private const String FIELD_RECORDER_NAMES = "recorder_names";
	
	//	public Sample()
	//	{
	//		fields = new Dictionary<String, Dictionary<String, String>>();
	//		subModels = new List<SubModel>();
	//	}

	//	#region sets
	//	public void SetWebsiteID(String websiteID)
	//	{
	//		AddToFields(FIELD_WEBSITE_ID, websiteID);
	//	}

	//	public void SetSurveyID(String surveyID)
	//	{
	//		AddToFields(FIELD_SURVEY_ID, surveyID);
	//	}

	//	public void SetDate(DateTime date)
	//	{
	//		AddToFields(FIELD_DATE_START, date.ToString("yyyy-MM-dd"));
	//		AddToFields(FIELD_DATE_END, date.ToString("yyyy-MM-dd"));
	//	}

	//	public void SetStartDate(DateTime date)
	//	{
	//		AddToFields(FIELD_DATE_START, date.ToString("yyyy-MM-dd"));
	//	}

	//	public void SetEndDate(DateTime date)
	//	{
	//		AddToFields(FIELD_DATE_END, date.ToString("yyyy-MM-dd"));
	//	}

	//	public void SetDateType(String dateType)
	//	{
	//		AddToFields(FIELD_DATE_TYPE, dateType);
	//	}

	//	public void SetSREF(String code, String position)
	//	{
	//		AddToFields(FIELD_SREF_SYSTEM, code);
	//		AddToFields(FIELD_SREF_VALUE, position);
	//	}

	//	public void SetGeom(String geom)
	//	{
	//		AddToFields(FIELD_GEOM, geom);
	//	}
	//	public void SetLocationName(String locationName)
	//	{
	//		AddToFields(FIELD_LOCATION_NAME, locationName);
	//	}
	//	public void SetExternalKey(String externalKey)
	//	{
	//		AddToFields(FIELD_EXTERNAL_KEY, externalKey);
	//	}

	//	public void SetComment(String comment)
	//	{
	//		AddToFields(FIELD_COMMENT, comment);
	//	}
	//	public void SetDeleted(String deleted)
	//	{
	//		AddToFields(FIELD_DELETED, deleted);
	//	}
	//	public void SetRecorderNames(String recorderNames)
	//	{
	//		AddToFields(FIELD_RECORDER_NAMES, recorderNames);
	//	}
	//	#endregion

	//	public void AddSubModel(SubModel subModel)
	//	{
	//		subModels.Add(subModel);
	//	}

	//	public void AddToFields(String FieldName, String Value)
	//	{
	//		Dictionary<String, String> dict = new Dictionary<String, String>(1);
	//		dict.Add("value", Value);
	//		if (fields.ContainsKey(FieldName))
	//		{
	//			fields[FieldName] = dict;
	//		}
	//		else
	//		{
	//			fields.Add(FieldName, dict);
	//		}
	//	}

	//}

	//public class Occurrence
	//{
	//	public String id = "occurrence";
	//	public Dictionary<String, Dictionary<String, String>> fields;

	//	private const String FIELD_TAXA_TAXON_LIST_ID = "taxa_taxon_list_id";
	//	private const String FIELD_WEBSITE_ID = "website_id";
	//	private const String FIELD_RECORD_STATUS = "record_status";

	//	public Occurrence()
	//	{
	//		fields = new Dictionary<String, Dictionary<String, String>>();
	//	}

	//	public void SetTaxaTaxonListID(string ID)
	//	{
	//		AddToFields(FIELD_TAXA_TAXON_LIST_ID, ID);
	//	}
	//	public void SetWebsiteID(string ID)
	//	{
	//		AddToFields(FIELD_WEBSITE_ID, ID);
	//	}
	//	public void SetRecordStatus(string status)
	//	{
	//		AddToFields(FIELD_RECORD_STATUS, status);
	//	}

	//	private void AddToFields(String FieldName, String Value)
	//	{
	//		Dictionary<String, String> dict = new Dictionary<String, String>(1);
	//		dict.Add("value", Value);
	//		if (fields.ContainsKey(FieldName))
	//		{
	//			fields[FieldName] = dict;
	//		}
	//		else
	//		{
	//			fields.Add(FieldName, dict);
	//		}
	//	}
	//}

	//public class Model
	//{

	//	string ID = "occurrence/location";
	//	public Dictionary<String, Dictionary<String, String>> fields;
	//}

	////TODO: could be location too 
	//public class SubModel
	//{
	//	public String fkId = "sample_id";
	//	public List<Model> models;

	//	public SubModel()
	//	{
	//		models = new List<Model>();
	//	}

	//	public void AddModel(Model model)
	//	{
	//		models.Add(model);
	//	}

	//}

}
