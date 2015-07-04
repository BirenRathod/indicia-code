<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SpeciesPickerExample.aspx.cs" Inherits="IndiciaExampleWebsite.SpeciesPickerExample" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Indicia Species Picker</title>
    <link href="CSS/jquery-ui.min.css" rel="stylesheet" />
    <link href="CSS/Indicia.css" rel="stylesheet" />
    <script src='<%= ResolveUrl("~/Javascript/JQuery/jquery-1.9.1.min.js") %>'></script>
    <script src='<%= ResolveUrl("~/Javascript/JQuery/jquery-ui.js") %>'></script>
    <script src='<%= ResolveUrl("~/Javascript/SpeciesPicker_Setup.js") %>'></script>
    <script type="text/javascript">
        $(document).ready(function () {
            TextBoxPicker.SetHandlerURL('<%= ResolveUrl("~/Handlers/IndiciaTaxaSearch.ashx") %>');
            TextBoxPicker.Init();
        });
    </script>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            Start typing species name:
            <asp:TextBox ID="SpeciesPicker_txt" runat="server" CssClass="IndiciaWideTextBox" ></asp:TextBox>
        </div>
    </form>
</body>
</html>
