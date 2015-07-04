using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using Indicia.DataServices;
using Newtonsoft.Json;

namespace esdm.mojoPortal.CustomSurvey.Handlers
{
    /// <summary>
    /// Handles request from client to Indicia Warehouse, making a Taxon List request 
    /// Requires search term sent a URL parameter sTerm
    /// Returns JSON list of species data
    /// </summary>   
    public class IndiciaTaxaSearch : IHttpHandler
    {
        public void ProcessRequest(HttpContext context)
        {
            string searchTermParam = context.Request.QueryString["sTerm"];
            if (String.IsNullOrWhiteSpace(searchTermParam))
            {
                throw new ArgumentException("Expected query string search term parameter 'sTerm' not available", "sTerm");
            }

            List<TaxonSearchItem> SortedTaxonList;

            if (context.Cache["Indicia_TaxaSearch_" + searchTermParam] != null)
            {
                SortedTaxonList = (List<TaxonSearchItem>)context.Cache["Indicia_TaxaSearch_" + searchTermParam];
            }
            else
            {
                DataService ds = new DataService();

                string taxonListID = ConfigurationManager.AppSettings["Indicia_SpeciesPicker_TaxonListID"];
                if (String.IsNullOrEmpty(taxonListID))
                { throw new ConfigurationErrorsException("Application setting Indicia_SpeciesPicker_TaxonListID required"); }
                else
                {
                    int tempID;
                    int.TryParse(taxonListID, out tempID);
                    if (tempID <= 0)
                    { throw new ConfigurationErrorsException("Application setting Indicia_SpeciesPicker_TaxonListID must be a positive integer"); }
                }

                ds.RequestData.Add("taxon_list_id", taxonListID);
                ds.RequestData.Add("limit", "100");
                ds.RequestData.Add("q", "*" + searchTermParam);
                ds.RequestData.Add("qfield", "searchterm");
                ds.RequestData.Add("query", "{\"where\":[\"(simplified='t' or simplified is null) AND (preferred='t' or language_iso<>'lat')\"]}");

                List<TaxonSearchItem> TaxonList = ds.GetTaxaSearchList();
                SortedTaxonList = TaxonList.GroupBy(t => new { t.DefaultCommonName, t.PreferredTaxon }).Select(g => g.First()).OrderBy(o => o.DefaultCommonName).ToList();
                context.Cache.Add("Indicia_TaxaSearch_" + searchTermParam, SortedTaxonList, null, System.Web.Caching.Cache.NoAbsoluteExpiration, new TimeSpan(7, 0, 0, 0), System.Web.Caching.CacheItemPriority.BelowNormal, null);
            }
            context.Request.ContentType = "application/json";
            context.Response.Write(JsonConvert.SerializeObject(SortedTaxonList));
        }

        public bool IsReusable
        {
            get
            {
                return false;
            }
        }
    }
}