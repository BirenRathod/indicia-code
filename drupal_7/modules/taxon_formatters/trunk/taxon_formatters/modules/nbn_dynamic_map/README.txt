NBN Map taxon formatter output module.

This module allows formatters to be added to the list of taxon formatter presets which use the NBN WMS web services to return a distribution map for a species, 
overlaid onto an OpenLayers map.

Theme functions
===============

theme_nbn_dynamic_map_output($image_path, $response, $preset)
--------------------------------------------

Creates the final HTML output for the map. The image path (which could be in the cache) passed as a parameter, along with the response from the web service 
call which includes the terms and conditions link ($response['!TermsAndConditions']) and logo ($response['!NBNLogo']). The preset['settings'] includes
width and height elements.