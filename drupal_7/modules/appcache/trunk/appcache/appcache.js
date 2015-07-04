(function ($) {

/**
 * This behavior prevents links in iOS from opening in Safari if the site is
 * running as a web application instead of in Safari itself. Unfortunately,
 * there is no way to determine from the DOM which environment the site is
 * being loaded in.
 */
Drupal.behaviors.appCacheClick = {
  attach: function (context, settings) {
    $("a.ios-enhanced").click(function (event) {
      var baseUrl = window.location.protocol + "//" + window.location.hostname + Drupal.settings.basePath;

      if (this.href.indexOf(baseUrl) == 0) {
        event.preventDefault();
        window.location = $(this).attr("href");
      }
    });
  }
};

}(jQuery));

