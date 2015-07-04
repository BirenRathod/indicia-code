TextBoxPicker = function () {

    var handlerURL;

    function SetHandlerURL(URL) {
        handlerURL = URL;
    }

    function FormatResponseLabel(item) {
        var lbl = item.preferred_taxon + " : " + item.taxon_group;
        if (undefined != item.default_common_name) {
            lbl += " (" + item.default_common_name + ')';
        }
        return lbl;
    }

    function GetPickerData(request, response) {
        searchTerm = request.term.toLowerCase().replace(/\(.+\)/g, '').replace(/ae/g, 'e').replace(/\. /g, '* ').replace(/[^a-zA-Z0-9\+\?*]/g, ''); //remove common spelling variations, non alpha num characters
        $.ajax({
            url: handlerURL + "?sTerm=" + searchTerm
            , dataType: "json"
            , type: "GET"
            , contentType: "application/json; charset=utf-8",
                success: function (data) {
                    response($.map(data, function (item) {
                        return {
                            label: FormatResponseLabel(item),
                            val: item.taxa_taxon_list_id
                        }
                    }))
                },
                error: function (response) {
                    alert(response.responseText);
                },
                failure: function (response) {
                    alert(response.responseText);
                }
            });
    }


    function Init() {
        $("#SpeciesPicker_txt").autocomplete({ source: GetPickerData, minLength: 3, delay: 250 });
    }

    return {
        Init: Init
        , SetHandlerURL: SetHandlerURL
    }

}();