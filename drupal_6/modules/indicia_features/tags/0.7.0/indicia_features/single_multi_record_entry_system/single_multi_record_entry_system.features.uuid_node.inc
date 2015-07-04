<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function single_multi_record_entry_system_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'type' => 'page',
  'language' => '',
  'uid' => '1',
  'status' => '1',
  'comment' => '0',
  'promote' => '0',
  'moderate' => '0',
  'sticky' => '0',
  'tnid' => '0',
  'translate' => '0',
  'title' => 'Recording',
  'body' => '<h2><a href="single-record">Submit single record</a></h2>
<p>If you have a single record that you would like to submit, please use this option.</p>
<h2><a href="multiple-records">Submit list of records</a></h2>
<p>If you have a list of records from a single place and time that you would like to submit, please use this option.</p><h2>
<?php 
global $user;
if ($user->uid===0) {
  drupal_set_message(t(\'Before using the recording facilities, please register and log in to the website.\'));
  drupal_goto(\'user/login\',\'destination=recording\');
}
?>',
  'teaser' => '<h2><a href="single-record">Submit single record</a></h2>
<p>If you have a single record that you would like to submit, please use this option.</p>
<h2><a href="multiple-records">Submit list of records</a></h2>
<p>If you have a list of records from a single place and time that you would like to submit, please use this option.</p><h2>
<?php 
global $user;
if ($user->uid===0) {
  drupal_set_message(t(\'Before using the recording facilities, please register and log in to the website.\'));
  drupal_goto(\'user/login\',\'destination=recording\');
}
?>',
  'log' => '',
  'format' => '3',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'path' => 'recording',
  'taxonomy' => array(),
  'uuid' => '5955430e-b90f-11e0-9f01-deef1494ab9e',
  'pathauto_perform_alias' => FALSE
);
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
  'title' => 'Enter Single Record',
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
    'multiple_occurrence_mode' => 'single',
    'species_ctrl' => 'autocomplete',
    'species_include_both_names' => '1',
    'species_include_taxon_group' => '1',
    'occurrence_comment' => '1',
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
    'redirect_on_success' => 'record-accepted',
    'message_after_save' => '0',
  ),
  'path' => 'single-record',
  'taxonomy' => array(),
  'uuid' => '6ef10624-b76d-11e0-9f01-deef1494ab9e',
  'pathauto_perform_alias' => FALSE
);
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
  'title' => 'Record accepted',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'my_dot_map',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '1',
    'permission_name' => 'online recording',
    'map_centroid_lat' => 'default',
    'map_centroid_long' => 'default',
    'map_zoom' => 'default',
    'map_width' => 600,
    'map_height' => 500,
    'remember_pos' => '0',
    'preset_layers' => array(
      '0' => 'google_physical',
    ),
    'wms_base_title' => '',
    'wms_base_url' => '',
    'wms_base_layer' => '',
    'tile_cache_layers' => '',
    'openlayers_options' => '',
    'indicia_wms_layers' => '',
    'standard_controls' => 'layerSwitcher
panZoom',
    'hide_grid' => '0',
    'wms_dist_1_title' => 'My Record',
    'wms_dist_1_internal' => '1',
    'wms_dist_1_url' => '',
    'wms_dist_1_layer' => 'indicia:detail_occurrences',
    'wms_dist_1_filter_against' => 'sample_id',
    'wms_dist_1_filter_field' => '',
    'wms_dist_1_style' => '',
    'wms_dist_1_opacity' => '0.5',
    'wms_dist_2_title' => 'Other records of {species}',
    'wms_dist_2_internal' => '1',
    'wms_dist_2_url' => '',
    'wms_dist_2_layer' => 'indicia:detail_occurrences',
    'wms_dist_2_filter_against' => 'taxon_meaning_id',
    'wms_dist_2_filter_field' => '',
    'wms_dist_2_style' => '',
    'wms_dist_2_opacity' => '0.5',
    'wms_dist_3_title' => '',
    'wms_dist_3_internal' => '0',
    'wms_dist_3_url' => '',
    'wms_dist_3_layer' => '',
    'wms_dist_3_filter_against' => '',
    'wms_dist_3_filter_field' => '',
    'wms_dist_3_style' => '',
    'wms_dist_3_opacity' => '',
    'redirect_on_success' => '',
  ),
  'path' => 'record-accepted',
  'taxonomy' => array(),
  'uuid' => '6ef111d2-b76d-11e0-9f01-deef1494ab9e',
  'pathauto_perform_alias' => FALSE
);
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
  'title' => 'Enter List of Records',
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
    'redirect_on_success' => 'record-accepted',
    'message_after_save' => '0',
  ),
  'path' => 'multiple-records',
  'taxonomy' => array(),
  'uuid' => '6ef11d30-b76d-11e0-9f01-deef1494ab9e',
  'pathauto_perform_alias' => FALSE
);
  return $nodes;
}
