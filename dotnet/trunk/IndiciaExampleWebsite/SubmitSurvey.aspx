<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SubmitSurvey.aspx.cs" Inherits="IndiciaExampleWebsite.SubmitSurvey" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Indicia Survey Submission</title>
    <link href="CSS/Indicia.css" rel="stylesheet" />
</head>
<body>
      <form id="form1" runat="server">
        <div>
            <h1>Example .NET Indicia Survey</h1>
            <p>In order to use this page, enter config settings to validate to an Indicia warehouse and receive a survey definition</p>
            <asp:Panel ID="survey_pnl" runat="server">
            </asp:Panel>
            <asp:Button ID="submitSurvey_btn" runat="server" Text="Submit Survey" OnClick="submitSurvey_btn_Click" />
            <p class="IndiciaError">
            <asp:Literal ID="submitSurveyResponse_ltl" runat="server" ></asp:Literal></p>
        </div>
    </form>
</body>
</html>
