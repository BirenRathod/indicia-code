using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.UI.WebControls;
using Indicia.DataServices;

namespace Indicia.WebControls
{
    /// <summary>
    /// Interface containing required Indicia survey question information
    /// Used to extend standard .Net controls so the information can be sent back to Indicia 
    /// </summary>
    public interface IIndiciaAttributes
    {
        int IndiciaAttributeID { get; set; }
        SurveyAttributeType IndiciaAttributeType { get; set; }
        String IndiciaAttributeCaption { get; set; }
        String IndiciaAttributeJSONID { get; set; }
        Boolean IndiciaIsRequired { get; set; }
        String GetValue();
    }

    public class IndiciaCalendar : Calendar, IIndiciaAttributes
    {
        public IndiciaCalendar()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public String GetValue()
        {
            return this.SelectedDate.ToString("yyyy-MM-dd"); //date format accepted by Indicia warehouse
        }
    }

    public class IndiciaCheckBox : CheckBox, IIndiciaAttributes
    {
        public IndiciaCheckBox()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public String GetValue()
        {
            //.Net produces 'True' 'False' instead of lowercase as required by JSON / Indicia
            if (this.Checked)
            {
                return "true";
            }
            else
            {
                return "false";
            }
        }
    }

    public class IndiciaCheckBoxList : CheckBoxList, IIndiciaAttributes
    {
        public IndiciaCheckBoxList()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public String GetValue()
        {
            //Indicia multi-value attributes should be in array [1,2,3] or ["a","b","c"]
            List<String> selectedValues = this.Items.Cast<ListItem>().Where(li => li.Selected).Select(li => li.Value).ToList();
            return "[" + String.Join(",", selectedValues) + "]";
        }
    }

    public class IndiciaDropDownList : DropDownList, IIndiciaAttributes
    {
        public IndiciaDropDownList()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public String GetValue()
        {
            return this.SelectedValue.ToString();
        }
    }

    public class IndiciaListBox : ListBox, IIndiciaAttributes
    {
        public IndiciaListBox()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public String GetValue()
        {
            List<String> selectedValues = this.Items.Cast<ListItem>().Where(li => li.Selected).Select(li => li.Value).ToList();
            return "[" + String.Join(",", selectedValues) + "]";
        }
    }

    public class IndiciaRadioButton : RadioButton, IIndiciaAttributes
    {
        public IndiciaRadioButton()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public string GetValue()
        {
            //.Net produces 'True' 'False' instead of lowercase as required by JSON / Indicia
            if (this.Checked)
            {
                return "true";
            }
            else
            {
                return "false";
            }
        }
    }

    public class IndiciaRadioButtonList : RadioButtonList, IIndiciaAttributes
    {
        public IndiciaRadioButtonList()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public String GetValue()
        {
            return this.SelectedValue;
        }
    }


    public class IndiciaTextBox : TextBox, IIndiciaAttributes
    {
        public IndiciaTextBox()
        { }

        public int IndiciaAttributeID { get; set; }
        public SurveyAttributeType IndiciaAttributeType { get; set; }
        public String IndiciaAttributeCaption { get; set; }
        public String IndiciaAttributeJSONID { get; set; }
        public Boolean IndiciaIsRequired { get; set; }

        public String GetValue()
        {
            return this.Text;
        }

    }
}
