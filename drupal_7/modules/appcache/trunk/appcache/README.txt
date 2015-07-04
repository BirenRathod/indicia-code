HTML5 Appcache
==============

This module allows you to specify what resources are available when
disconnected from the internet. It uses the HTML5 Application Cache, so browser
support is required for this module to work.

Installation
============

 1. Enable the module as normal.
 2. Grant the "Access site using HTML5 offline cache" permission to any roles
    that should be able to access the site offline.
 3. Enable the application cache at admin/config/services/appcache. To set up
    "default" caching where any visited page is automatically cached, enable
    the "Automatically cache visited pages and resources" setting.
 4. Add the following to the <html> tag in your theme's page template to include
    the cache manifest:

      manifest="<?php print base_path(); ?>/appcache.manifest"

    For example, using the Omega base theme, you might end up with an <html>
    tag in html.tpl.php like this:

     <html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf->version . $rdf->namespaces;?> manifest="<?php print base_path(); ?>/appcache.manifest">

 5. If you're a developer and want to add or alter the cache manifest, see
    appcache.api.php.

