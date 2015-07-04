NBN Designations taxon formatter output module.

This module allows formatters to be added to the list of taxon formatter presets which use the NBN GetTaxonomySearch web service to return a list of designations for a species.

Theme functions
===============

theme_nbn_designations_taxon_formatter_output($element, $preset)
----------------------------------------------------------------

Receives the taxon version key in the $element['#item']['safe_Value'] and converts this to a list of designations. The nbn_designations_get_designations method($tvk, $preset) method is available to call the web service to get the designations.
Unless there is a need to output something other than a <ul> there is unlikely to be a need to override this theme function.

theme_nbn_designations_format_item($element)
--------------------------------------------

Receives a single designation definition in the $element and returns a formatted piece of HTML to display the designation.