//APP LOGIC.
(function($){
    //When leaving a page with a form
    window.onbeforeunload = function() {
        _log('Leaving.');
    };

    app.initialise();

    //Fixing back buttons for Mac 7.* History bug.
    $(document).on('pagecreate', function(event, ui) {
        if (browserDetect('Safari')){
            if (jQuery.mobile.activePage != null) {
                var nextPageid = event.target.id;
                var currentPageURL = null;

                var external = jQuery.mobile.activePage.attr('data-external-page');
                if (external == null) {
                    currentPageURL = '#' + jQuery.mobile.activePage.attr('id');
                }

                fixPageBackButtons(currentPageURL, nextPageid);
            }
        }
    });

}(app.$ || jQuery));