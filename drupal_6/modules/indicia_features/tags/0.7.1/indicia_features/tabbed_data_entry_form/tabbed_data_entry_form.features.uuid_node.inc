<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function tabbed_data_entry_form_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'type' => 'iform',
  'language' => '',
  'uid' => '1',
  'status' => '1',
  'comment' => '0',
  'promote' => '0',
  'moderate' => '0',
  'sticky' => '0',
  'tnid' => '0',
  'translate' => '0',
  'title' => 'Submit Sightings',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'mnhnl_dynamic_1',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '1',
    'permission_name' => 'online recording',
    'map_centroid_lat' => 'default',
    'map_centroid_long' => 'default',
    'map_zoom' => 'default',
    'map_width' => 600,
    'map_height' => 500,
    'remember_pos' => '1',
    'preset_layers' => array(
      '0' => 'google_hybrid',
      '1' => 'bing_hybrid',
    ),
    'wms_base_title' => '',
    'wms_base_url' => '',
    'wms_base_layer' => '',
    'tile_cache_layers' => '',
    'openlayers_options' => '',
    'indicia_wms_layers' => '',
    'standard_controls' => 'layerSwitcher
panZoom',
    'georefDriver' => 'geoplanet',
    'interface' => 'tabs',
    'tabProgress' => '0',
    'emailShow' => '0',
    'nameShow' => '0',
    'copyFromProfile' => NULL,
    'clientSideValidation' => '1',
    'structure' => '=Species=
?Please enter the species you saw and any other information about them.?
[species]
@resizeWidth=1500
@resizeHeight=1500
[species attributes]
[*]
=Place=
?Please provide the spatial reference of the record. You can enter the reference directly, or search for a place then click on the map.?
[place search]
[spatial reference]
[map]
[*]
=Other Information=
?Please provide the following additional information.?
[date]
[sample comment]
[*]
=*=',
    'attribute_termlist_language_filter' => '0',
    'no_grid' => '1',
    'grid_report' => 'reports_for_prebuilt_forms/simple_sample_list_1',
    'save_button_below_all_pages' => '0',
    'multiple_occurrence_mode' => 'multi',
    'species_ctrl' => 'autocomplete',
    'species_include_both_names' => '1',
    'species_include_taxon_group' => '1',
    'occurrence_comment' => '0',
    'occurrence_confidential' => '0',
    'occurrence_images' => '1',
    'col_widths' => '',
    'list_id' => '',
    'extra_list_id' => '2',
    'species_names_filter' => 'all',
    'link_species_popups' => '',
    'spatial_systems' => 'default',
    'defaults' => 'occurrence:record_status=C',
    'includeLocTools' => '0',
    'redirect_on_success' => '',
  ),
  'path' => 'submit-sightings-tabbed',
  'taxonomy' => array(),
  'uuid' => '72fbb6f2-ad87-11e0-aeb9-62cde1fc4d8d',
  'pathauto_perform_alias' => FALSE
);
  return $nodes;
}
