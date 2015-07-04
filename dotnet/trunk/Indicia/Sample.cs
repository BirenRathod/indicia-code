using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Indicia.DataServices
{

	public enum SubModelType
	{
		location
		, occurrence
	}

	/// <summary>
	/// Class to hold answers to a survey. Structured so that JSON output is valid for submission of sample to Indicia Warehouse 
	/// See http://indicia-docs.readthedocs.org/en/latest/developing/web-services/submission-format.html
	/// </summary>
	public class Sample
	{
		private Model _sample;
		private List<SubModel> _subModels;

		[JsonProperty("id", NullValueHandling = NullValueHandling.Ignore)]
		public String id
		{
			get { return this._sample.id; }
		}

		public Dictionary<String, Dictionary<String, Object>> fields
		{
			get { return this._sample.fields; }
		}

		public List<SubModel> subModels
		{
			get { return this._subModels; }
		}

		public Sample()
		{
			this._sample = new Model("sample");
			this._subModels = new List<SubModel>();
		}

		public void AddSubModel(SubModel subModel)
		{
			this._subModels.Add(subModel);
		}

		public void AddToFields(String FieldName, Object Value)
		{
			this._sample.AddToFields(FieldName, Value);
		}
	}


	public class Model
	{
		public string id;
		public Dictionary<String, Dictionary<String, Object>> fields;

		public Model(String ID)
		{
			this.id = ID;
			this.fields = new Dictionary<String, Dictionary<String, Object>>();
		}

		public void AddToFields(String FieldName, Object Value)
		{
			Dictionary<String, Object> dict = new Dictionary<String, Object>(1);
			dict.Add("value", Value);
			if (this.fields.ContainsKey(FieldName))
			{
				this.fields[FieldName] = dict;
			}
			else
			{
				this.fields.Add(FieldName, dict);
			}
		}

		public bool HasFields()
		{
			return this.fields.Count > 0;
		}

	}

	public class SubModel
	{
		public string fkId;
		public Model model;

		public SubModel(SubModelType type)
		{
			this.fkId = "sample_id";
			this.model = new Model(Enum.GetName(typeof(SubModelType), type));
		}

		public void AddToFields(String FieldName, Object Value)
		{
			this.model.AddToFields(FieldName, Value);
		}

		public bool HasFields()
		{
			return this.model.HasFields();
		}

	}


}
