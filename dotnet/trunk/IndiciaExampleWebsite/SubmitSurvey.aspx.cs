using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Xml.Linq;
using Indicia.DataServices;
using Indicia.Security;
using Indicia.WebControls;
using System.Web.Script.Serialization;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace IndiciaExampleWebsite
{
    public partial class SubmitSurvey : System.Web.UI.Page
    {
        int Indicia_WebsiteID;
        int Indicia_SurveyID;

        protected void Page_Load(object sender, EventArgs e)
        {
            DataService ds = new DataService();

            GetApplicationSettings();

            ds.RequestData.Add("restrict_to_survey_id", Indicia_SurveyID.ToString());
            List<SurveyAttribute> attrs = ds.GetSurvey();

            foreach (SurveyAttribute attr in attrs)
            {
                HtmlGenericControl div = CreateIndiciaQuestion(attr);
                survey_pnl.Controls.Add(div);
            }
        }

        private void GetApplicationSettings()
        {
            string websiteID = ConfigurationManager.AppSettings["Indicia_WebsiteID"];
            if (String.IsNullOrEmpty(websiteID))
            { throw new ConfigurationErrorsException("Application setting WebsiteID required"); }
            else
            {
                int.TryParse(websiteID, out Indicia_WebsiteID);
                if (Indicia_WebsiteID <= 0)
                { throw new ConfigurationErrorsException("Application setting Indicia_WebsiteID must be a positive integer"); }
            }

            string surveyID = ConfigurationManager.AppSettings["Indicia_SurveyID"];
            if (String.IsNullOrEmpty(surveyID))
            { throw new ConfigurationException("Application setting Indicia_SurveyID required"); }
            else
                int.TryParse(surveyID, out  Indicia_SurveyID);
            if (Indicia_SurveyID <= 0)
            { throw new ConfigurationException("Application setting Indicia_SurveyID must be a positive integer"); }
        }

        private HtmlGenericControl CreateIndiciaQuestion(SurveyAttribute attr)
        {
            HtmlGenericControl div = new HtmlGenericControl();
            div.ID = "Indicia_" + attr.Id.ToString() + "_div";
            div.Attributes["class"] = "IndiciaQuestionWrap";
            div.TagName = "div";

            Label lbl = new Label();
            lbl.ID = "Indicia_" + attr.Id.ToString() + "_lbl";
            lbl.Attributes["class"] = "IndiciaQuestionLabel";
            lbl.Text = attr.Caption;
            div.Controls.Add(lbl);

            IIndiciaAttributes IndiciaCtrl = null;
            switch (attr.DataType)
            {
                //TODO: add in more complex controls, validators and default values. Out of scope for this initial investigation 
                case "D":
                    //D=Date = Calendar control
                    IndiciaCtrl = new IndiciaCalendar();
                    break;

                case "L":
                    //L=List => DropDownList 
                    IndiciaCtrl = CreateDropDownList(attr);
                    break;

                case "T":
                    //T=Text => Textbox
                    IndiciaCtrl = CreateTextBox(attr);
                    break;

                default:
                    HtmlGenericControl html = new HtmlGenericControl();
                    html.TagName = "p";
                    html.Attributes.Add("class", "IndiciaError");
                    html.InnerHtml = "Error: Unknown Indicia type";
                    div.Controls.Add(html);
                    break;
            }

            if (IndiciaCtrl != null)
            {
                IndiciaCtrl.IndiciaAttributeType = attr.AttributeType;
                IndiciaCtrl.IndiciaAttributeID = attr.Id;
                IndiciaCtrl.IndiciaIsRequired = attr.IsRequired;
                IndiciaCtrl.IndiciaAttributeCaption = attr.Caption;
                IndiciaCtrl.IndiciaAttributeJSONID = attr.IndiciaJSONAttributeName;

                WebControl ctrl = (WebControl)IndiciaCtrl;
                ctrl.ID = "Indicia_" + attr.Id.ToString();
                ctrl.CssClass = "IndiciaQuestion";
                div.Controls.Add(ctrl);
            }
            return div;
        }

        private IndiciaDropDownList CreateDropDownList(SurveyAttribute attr)
        {
            Indicia.WebControls.IndiciaDropDownList ddl = new Indicia.WebControls.IndiciaDropDownList();
            DataService ds2 = new DataService();
            ds2.RequestData.Add("termlist_id", attr.TermlistId.ToString());
            List<TermItem> ddlData = ds2.GetTermList();

            ddl.DataSource = ddlData;
            ddl.DataTextField = "Term";
            ddl.DataValueField = "TermId";
            ddl.DataBind();
            return ddl;
        }

        private IndiciaTextBox CreateTextBox(SurveyAttribute attr)
        {
            Indicia.WebControls.IndiciaTextBox tbx = new Indicia.WebControls.IndiciaTextBox();
            if (!(String.IsNullOrEmpty(attr.DefaultTextValue)))
            {
                tbx.Text = attr.DefaultTextValue;
            }
            return tbx;
        }

        protected void submitSurvey_btn_Click(object sender, EventArgs e)
        {

            Sample m = new Sample();
            m.AddToFields("website_id", Indicia_WebsiteID);
            m.AddToFields("survey_id", Indicia_SurveyID);
            m.AddToFields("date", DateTime.Now.ToString("yyyy-MM-dd"));

            SubModel smOcc = new SubModel(SubModelType.occurrence);
            smOcc.AddToFields("website_id", Indicia_WebsiteID.ToString());
            SubModel smLoc = new SubModel(SubModelType.location);

            foreach (Control ctrl in survey_pnl.Controls) //these are the 'IndiciaQuestionWrap' divs
            {
                foreach (Control subCtrl in ctrl.Controls)
                {
                    IIndiciaAttributes t = subCtrl as IIndiciaAttributes;
                    if (t == null)
                    { continue; }

                    if (t.IndiciaAttributeJSONID.Contains("smpAttr"))
                    {
                        m.AddToFields(t.IndiciaAttributeJSONID, t.GetValue());
                    }

                    if (t.IndiciaAttributeJSONID.Contains("locAttr"))
                    {
                        smLoc.AddToFields(t.IndiciaAttributeJSONID, t.GetValue());
                    }

                    if (t.IndiciaAttributeJSONID.Contains("occAttr"))
                    {
                        smOcc.AddToFields(t.IndiciaAttributeJSONID, t.GetValue());
                    }
                }
            }

            if (smOcc.HasFields())
            {
                smOcc.AddToFields("taxa_taxon_list_id", "72"); //TODO: this should be implemeted via the species picker
                m.AddSubModel(smOcc);
            }
            if (smLoc.HasFields())
            {
                m.AddSubModel(smLoc);
            }

            // TODO: need to implement method of getting sample location from user. This is outside the scope of this project
            // One way would to implement a web map (OpenLayers, Google, Bing) and get the user to click on location.
            m.AddToFields("entered_sref", "TQ 27647 78433");
            m.AddToFields("entered_sref_system", "OSGB");

            DataService ds = new DataService();
            JavaScriptSerializer jss = new JavaScriptSerializer();
            ds.RequestData.Add("submission", jss.Serialize(m));

            try
            {
                ds.SaveData();
                submitSurveyResponse_ltl.Text = "Thank you, survey submitted";
            }
            catch (ArgumentException ex)
            {
                submitSurveyResponse_ltl.Text = ex.Message;
            }
        }
    }
}