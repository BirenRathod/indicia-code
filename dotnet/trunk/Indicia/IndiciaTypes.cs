using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;
using System.Xml;
using System.Xml.Linq;
using Newtonsoft.Json;

namespace Indicia.DataServices
{
	public enum SurveyAttributeType
	{
		location,
		occurrence,
		sample
	}

	public class SurveyAttributes
	{
		private List<SurveyAttribute> _attributes;

		public List<SurveyAttribute> Attributes
		{ get { return _attributes; } set { _attributes = value; } }

		public SurveyAttributes()
		{
			this._attributes = new List<SurveyAttribute>();
		}
      
	}

	public class SurveyAttribute
	{
		private int _id;
		private String _caption;
		private String _outerStructureBlock;
		private String _innerStructureBlock;
		private String _dataType;
		private String _controlType;
		private int _termlistId;
		private String _multivalue;
		private int _websiteId;
		private int _restrictToSurveyId;
		private String _signature;
		private String _defaultTextValue;
		private String _defaultIntValue;
		private String _defaultFloatValue;
		private String _defaultDateStartValue;
		private String _defaultDateEndValue;
		private String _defaultDateTypeValue;
		private String _validationRules;
		private String _deleted;
		private String _websiteDeleted;
		private int _restrictToSampleMethodId;
		private String _systemFunction;
		private SurveyAttributeType _surveyAttributeType;

		#region properties

		[JsonProperty("id", NullValueHandling = NullValueHandling.Ignore)]
		public int Id
		{
			get { return _id; }
			set { _id = value; }
		}

		[JsonProperty("caption", NullValueHandling = NullValueHandling.Ignore)]
		public String Caption
		{
			get { return _caption; }
			set { _caption = value; }
		}

		[JsonProperty("outer_structure_block", NullValueHandling = NullValueHandling.Ignore)]
		public String OuterStructureBlock
		{
			get { return _outerStructureBlock; }
			set { _outerStructureBlock = value; }
		}

		[JsonProperty("inner_structure_block", NullValueHandling = NullValueHandling.Ignore)]
		public String InnnerStructureBlock
		{
			get { return _innerStructureBlock; }
			set { _innerStructureBlock = value; }
		}

		[JsonProperty("data_type", NullValueHandling = NullValueHandling.Ignore)]
		public String DataType
		{
			get { return _dataType; }
			set { _dataType = value; }
		}

		[JsonProperty("control_type", NullValueHandling = NullValueHandling.Ignore)]
		public String ControlType
		{
			get { return _controlType; }
			set { _controlType = value; }
		}

		[JsonProperty("termlist_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TermlistId
		{
			get { return _termlistId; }
			set { _termlistId = value; }
		}

		[JsonProperty("multi_value", NullValueHandling = NullValueHandling.Ignore)]
		private String _multiValue
		{
			get { return _multivalue; }
			set { _multivalue = value; }
		}

		public Boolean MultiValue
		{
			get { if (_multivalue == "t") return true; else return false; }
			set { if (MultiValue) _multivalue = "t"; else _multivalue = "f"; }
		}

		[JsonProperty("website_id", NullValueHandling = NullValueHandling.Ignore)]
		public int WebsiteId
		{
			get { return _websiteId; }
			set { _websiteId = value; }
		}

		[JsonProperty("restrict_to_survey_id", NullValueHandling = NullValueHandling.Ignore)]
		public int RestrictToSurveyId
		{
			get { return _restrictToSurveyId; }
			set { _restrictToSurveyId = value; }
		}

		[JsonProperty("signature", NullValueHandling = NullValueHandling.Ignore)]
		public String Signature
		{
			get { return _signature; }
			set { _signature = value; }
		}

		[JsonProperty("default_text_value", NullValueHandling = NullValueHandling.Ignore)]
		public String DefaultTextValue
		{
			get { return _defaultTextValue; }
			set { _defaultTextValue = value; }
		}

		[JsonProperty("default_int_value", NullValueHandling = NullValueHandling.Ignore)]
		public String DefaultIntValue
		{
			get { return _defaultIntValue; }
			set { _defaultIntValue = value; }
		}

		[JsonProperty("default_float_value", NullValueHandling = NullValueHandling.Ignore)]
		public String DefaultFloatValue
		{
			get { return _defaultFloatValue; }
			set { _defaultFloatValue = value; }
		}

		[JsonProperty("default_date_start_value", NullValueHandling = NullValueHandling.Ignore)]
		public String DefaultDateStartValue
		{
			get { return _defaultDateStartValue; }
			set { _defaultDateStartValue = value; }
		}

		[JsonProperty("default_date_end_value", NullValueHandling = NullValueHandling.Ignore)]
		public String DefaultDateEndValue
		{
			get { return _defaultDateEndValue; }
			set { _defaultDateEndValue = value; }
		}

		[JsonProperty("default_date_type_value", NullValueHandling = NullValueHandling.Ignore)]
		public String DefaultDateTypeValue
		{
			get { return _defaultDateTypeValue; }
			set { _defaultDateTypeValue = value; }
		}

		[JsonProperty("validation_rules", NullValueHandling = NullValueHandling.Ignore)]
		public String ValidationRules
		{
			get { return _validationRules; }
			set { _validationRules = value; }
		}

		[JsonProperty("deleted", NullValueHandling = NullValueHandling.Ignore)]
		private String deleted
		{
			get { return _deleted; }
			set { _deleted = value; }
		}
		public Boolean Deleted
		{
			get { if (_deleted == "t") return true; else return false; }
			set { if (Deleted) _deleted = "t"; else _deleted = "f"; }
		}

		[JsonProperty("website_deleted", NullValueHandling = NullValueHandling.Ignore)]
		private String websiteDeleted
		{
			get { return _websiteDeleted; }
			set { _websiteDeleted = value; }
		}
		public Boolean WebsiteDeleted
		{
			get { if (_websiteDeleted == "t") return true; else return false; }
			set { if (WebsiteDeleted) _websiteDeleted = "t"; else _websiteDeleted = "f"; }
		}

		[JsonProperty("restrict_to_sample_method_id", NullValueHandling = NullValueHandling.Ignore)]
		public int RestrictToSampleMethodId
		{
			get { return _restrictToSampleMethodId; }
			set { _restrictToSampleMethodId = value; }
		}

		[JsonProperty("system_function", NullValueHandling = NullValueHandling.Ignore)]
		public String SystemFunction
		{
			get { return _systemFunction; }
			set { _systemFunction = value; }
		}

		public SurveyAttributeType AttributeType
		{
			get { return _surveyAttributeType; }
			set { _surveyAttributeType = value; }
		}

		public String IndiciaJSONAttributeName
		{
			get
			{
				String JSONAttributeName = String.Empty;
				switch (this.AttributeType)
				{
					case SurveyAttributeType.location:
						JSONAttributeName = "locAttr:";
						break;
					case SurveyAttributeType.occurrence:
						JSONAttributeName = "occAttr:";
						break;
					case SurveyAttributeType.sample:
						JSONAttributeName = "smpAttr:";
						break;
				}
				JSONAttributeName += this.Id.ToString();
				return JSONAttributeName;
			}
		}

		public Boolean IsRequired
		{
			get
			{
				return this._validationRules.Contains("required");
			}
		}
		#endregion

		public SurveyAttribute()
		{
		}
	}

	public class TaxonSearchItem
	{

		private int _codeTypeId;
		private String _defaultCommonName;
		private int _Id;
		private String _identififcationDifficulty;
		private String _languageIso;
		private String _nameType;
		private String _original;
		private int _parentId;
		private String _preferred;
		private String _preferredAuthority;
		private int _preferredTaxaTaxonListId;
		private String _preferredTaxon;
		private String _simplified;
		private String _searchTerm;
		private int _searchTermLength;
		private int _sourceId;
		private int _taxaTaxonListId;
		private String _taxonGroup;
		private int _taxonGroupId;
		private int _taxonListId;
		private int _taxonMeaningId;

		#region properties

		[JsonProperty("code_type_id", NullValueHandling = NullValueHandling.Ignore)]
		public int CodeTypeId
		{
			get { return _codeTypeId; }
			set { _codeTypeId = value; }
		}

		[JsonProperty("default_common_name", NullValueHandling = NullValueHandling.Ignore)]
		public string DefaultCommonName
		{
			get { return _defaultCommonName; }
			set { _defaultCommonName = value; }
		}

		[JsonProperty("id", NullValueHandling = NullValueHandling.Ignore)]
		public int Id
		{
			get { return _Id; }
			set { _Id = value; }
		}

		[JsonProperty("identification_difficulty", NullValueHandling = NullValueHandling.Ignore)]
		public string IdentificationDifficulty
		{
			get { return _identififcationDifficulty; }
			set { _identififcationDifficulty = value; }
		}

		[JsonProperty("language_iso", NullValueHandling = NullValueHandling.Ignore)]
		public string LanguageIso
		{
			get { return _languageIso; }
			set { _languageIso = value; }
		}

		[JsonProperty("name_type", NullValueHandling = NullValueHandling.Ignore)]
		public string NameType
		{
			get { return _nameType; }
			set { _nameType = value; }
		}

		[JsonProperty("original", NullValueHandling = NullValueHandling.Ignore)]
		public string Original
		{
			get { return _original; }
			set { _original = value; }
		}

		[JsonProperty("parent_id", NullValueHandling = NullValueHandling.Ignore)]
		public int ParentId
		{
			get { return _parentId; }
			set { _parentId = value; }
		}

		[JsonProperty("preferred", NullValueHandling = NullValueHandling.Ignore)]
		public string Preferred
		{
			get { return _preferred; }
			set { _preferred = value; }
		}

		[JsonProperty("preferred_authority", NullValueHandling = NullValueHandling.Ignore)]
		public string PreferredAuthority
		{
			get { return _preferredAuthority; }
			set { _preferredAuthority = value; }
		}

		[JsonProperty("preferred_taxa_taxon_list_id", NullValueHandling = NullValueHandling.Ignore)]
		public int PreferredTaxaTaxonListId
		{
			get { return _preferredTaxaTaxonListId; }
			set { _preferredTaxaTaxonListId = value; }
		}
		[JsonProperty("preferred_taxon", NullValueHandling = NullValueHandling.Ignore)]
		public string PreferredTaxon
		{
			get { return _preferredTaxon; }
			set { _preferredTaxon = value; }
		}

		[JsonProperty("simplified", NullValueHandling = NullValueHandling.Ignore)]
		public string Simplified
		{
			get { return _simplified; }
			set { _simplified = value; }
		}

		[JsonProperty("searchterm", NullValueHandling = NullValueHandling.Ignore)]
		public string SearchTerm
		{
			get { return _searchTerm; }
			set { _searchTerm = value; }
		}

		[JsonProperty("searchterm_length", NullValueHandling = NullValueHandling.Ignore)]
		public int SearchTermLength
		{
			get { return _searchTermLength; }
			set { _searchTermLength = value; }
		}

		[JsonProperty("source_id", NullValueHandling = NullValueHandling.Ignore)]
		public int SourceId
		{
			get { return _sourceId; }
			set { _sourceId = value; }
		}

		[JsonProperty("taxa_taxon_list_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxaTaxonListId
		{
			get { return _taxaTaxonListId; }
			set { _taxaTaxonListId = value; }
		}

		[JsonProperty("taxon_group", NullValueHandling = NullValueHandling.Ignore)]
		public string TaxonGroup
		{
			get { return _taxonGroup; }
			set { _taxonGroup = value; }
		}

		[JsonProperty("taxon_group_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxonGroupId
		{
			get { return _taxonGroupId; }
			set { _taxonGroupId = value; }
		}

		[JsonProperty("taxon_list_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxonListId
		{
			get { return _taxonListId; }
			set { _taxonListId = value; }
		}

		[JsonProperty("taxon_meaning_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxonMeaningId
		{
			get { return _taxonMeaningId; }
			set { _taxonMeaningId = value; }
		}

		#endregion

		public TaxonSearchItem()
		{
		}
	}

	public class TaxonItem
	{

		private String _allowDataEntry;
		private String _authority;
		private String _common;
		private String _externalKey;
		private int _Id;
		private String _language;
		private String _preferred;
		private String _preferredName;
		private String _taxon;
		private String _taxonGroup;
		private int _taxonGroupId;
		private int _taxonId;
		private String _taxonList;
		private int _taxonListId;
		private int _taxonMeaningId;
		private int _websiteId;

		#region properties
		[JsonProperty("allow_data_entry", NullValueHandling = NullValueHandling.Ignore)]
		public String AllowDataEntry
		{
			get { return _allowDataEntry; }
			set { _allowDataEntry = value; }
		}

		[JsonProperty("authority", NullValueHandling = NullValueHandling.Ignore)]
		public String Authority
		{
			get { return _authority; }
			set { _authority = value; }
		}

		[JsonProperty("common", NullValueHandling = NullValueHandling.Ignore)]
		public String Common
		{
			get { return _common; }
			set { _common = value; }
		}

		[JsonProperty("external_key", NullValueHandling = NullValueHandling.Ignore)]
		public String externalKey
		{
			get { return _externalKey; }
			set { _externalKey = value; }
		}

		[JsonProperty("id", NullValueHandling = NullValueHandling.Ignore)]
		public int Id
		{
			get { return _Id; }
			set { _Id = value; }
		}

		[JsonProperty("preferred", NullValueHandling = NullValueHandling.Ignore)]
		public String Preferred
		{
			get { return _preferred; }
			set { _preferred = value; }
		}

		[JsonProperty("preferred_name", NullValueHandling = NullValueHandling.Ignore)]
		public String PreferredName
		{
			get { return _preferredName; }
			set { _preferredName = value; }
		}

		[JsonProperty("taxon", NullValueHandling = NullValueHandling.Ignore)]
		public String Taxon
		{
			get { return _taxon; }
			set { _taxon = value; }
		}

		[JsonProperty("taxon_group", NullValueHandling = NullValueHandling.Ignore)]
		public String TaxonGroup
		{
			get { return _taxonGroup; }
			set { _taxonGroup = value; }
		}

		[JsonProperty("taxon_group_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxonGroupId
		{
			get { return _taxonGroupId; }
			set { _taxonGroupId = value; }
		}

		[JsonProperty("taxon_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxonId
		{
			get { return _taxonId; }
			set { _taxonId = value; }
		}

		[JsonProperty("taxon_list", NullValueHandling = NullValueHandling.Ignore)]
		public String TaxonList
		{
			get { return _taxonList; }
			set { _taxonList = value; }
		}

		[JsonProperty("taxon_list_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxonListId
		{
			get { return _taxonListId; }
			set { _taxonListId = value; }
		}

		[JsonProperty("taxon_meaning_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TaxonMeaningId
		{
			get { return _taxonMeaningId; }
			set { _taxonMeaningId = value; }
		}

		[JsonProperty("website_id", NullValueHandling = NullValueHandling.Ignore)]
		public int WebsiteId
		{
			get { return _websiteId; }
			set { _websiteId = value; }
		}
		#endregion

	}

	public class TermItem
	{
		private int _Id;
		private int _termId;
		private String _term;
		private int _termlistId;
		private String _termlist;
		private int _websiteId;
		private String _termlistExternalKey;
		private String _iso;
		private int _sortOrder;

		#region properties
		[JsonProperty("id", NullValueHandling = NullValueHandling.Ignore)]
		public int Id
		{
			get { return _Id; }
			set { _Id = value; }
		}

		[JsonProperty("term_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TermId
		{
			get { return _termId; }
			set { _termId = value; }
		}

		[JsonProperty("term", NullValueHandling = NullValueHandling.Ignore)]
		public String Term
		{
			get { return _term; }
			set { _term = value; }
		}

		[JsonProperty("termlist_id", NullValueHandling = NullValueHandling.Ignore)]
		public int TermlistId
		{
			get { return _termlistId; }
			set { _termlistId = value; }
		}

		[JsonProperty("termlist", NullValueHandling = NullValueHandling.Ignore)]
		public String Termlist
		{
			get { return _termlist; }
			set { _termlist = value; }
		}

		[JsonProperty("website_id", NullValueHandling = NullValueHandling.Ignore)]
		public int WebsiteId
		{
			get { return _websiteId; }
			set { _websiteId = value; }
		}

		[JsonProperty("termlist_external_key", NullValueHandling = NullValueHandling.Ignore)]
		public String TermlistExternalKey
		{
			get { return _termlistExternalKey; }
			set { _termlistExternalKey = value; }
		}

		[JsonProperty("iso", NullValueHandling = NullValueHandling.Ignore)]
		public String Iso
		{
			get { return _iso; }
			set { _iso = value; }
		}

		[JsonProperty("sort_order", NullValueHandling = NullValueHandling.Ignore)]
		public int SortOrder
		{
			get { return _sortOrder; }
			set { _sortOrder = value; }
		}

		#endregion

		public TermItem()
		{

		}
	}
}