Defines the following hooks:

Hook_taxon_formatter
====================

Returns an array containing definitions of the taxon formatter types defined by a module. For example:
function nbn_map_taxon_formatter_types() {
  $formatter = array(
    'nbn_map' => array(
      'title' => t('NBN Map'),
      // field type is TVK, TLIK or BRC (+GBIF?)
      'field_type' => 'TVK',
      // function that generates the form using Forms API, with arguments for the current settings values, type name (e.g. nbn_map) and optional $args
      'form_callback' => 'nbn_map_taxon_formatter_settings_form',
      'form_args' => array() // can be used to pass arguments to the form
    )
  );
  return $formatter;
}


output theme function
=====================

The system assumes a theme function called theme_<type>_taxon_formatter_output will generate the output. $element['#item'] passes the data for the current field value.
For example, if there is an nbn_map formatter type, then the following code could generate output. Note that you must declare the theme function using hook_theme 
and that the preset is passed as a parameter to the theme function:
function theme_nbn_map_taxon_formatter_output($element, $preset) {
  return my_map_function($element['#item']);
}

function nbn_map_theme() {
  $theme = array();
  $theme["nbn_map_taxon_formatter_output"] = array(
      'arguments' => array('element' => NULL),
  );
  return $theme;
}
