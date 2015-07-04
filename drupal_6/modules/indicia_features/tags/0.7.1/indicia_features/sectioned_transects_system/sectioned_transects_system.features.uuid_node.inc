<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function sectioned_transects_system_uuid_features_default_content() {
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
  'title' => 'All Sites',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'report_grid',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '1',
    'permission_name' => 'region coordinator',
    'report_name' => 'library/locations/species_and_occurrence_counts',
    'param_presets' => 'date_from=
date_to=
survey_id=
location_type_id=Transect
locattrs=',
    'param_defaults' => '',
    'output' => 'default',
    'report_group' => 'report',
    'params_in_map_toolbar' => '0',
    'refresh_timer' => '',
    'load_on_refresh' => '',
    'columns_config' => '[
  {
    "actions":
    [
      {
        "caption":"edit",
        "url":"{rootFolder}site-details",
        "urlParams":
        {
          "id":"{id}"
        }
      }
    ]
  }
]',
    'gallery_col_count' => '1',
    'items_per_page' => '20',
    'download_link' => '1',
    'footer' => '',
    'redirect_on_success' => '',
    'message_after_save' => '0',
  ),
  'taxonomy' => array(),
  'uuid' => '240ac08d-c99f-11e0-9708-e2fa3c3d7fc6',
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
  'title' => 'My Sites',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'report_grid',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '0',
    'permission_name' => '',
    'report_name' => 'library/locations/species_and_occurrence_counts',
    'param_presets' => 'date_from=
date_to=
survey_id=
location_type_id=Transect
locattrs=CMS User ID
attr_location_cms_user_id={user_id}',
    'param_defaults' => '',
    'output' => 'default',
    'report_group' => 'report',
    'params_in_map_toolbar' => '0',
    'refresh_timer' => '',
    'load_on_refresh' => '',
    'columns_config' => '[
  {
    "fieldname":"id",
    "visible":false
  },
  {
    "fieldname":"name",
    "display":"Site Name"
  },
  {
    "fieldname":"occurrences",
    "display":"No. of records"
  },
  {
    "fieldname":"taxa",
    "display":"No. of species"
  },
  {
    "fieldname":"groups",
    "visible":false
  },
  {
    "fieldname":"attr_location_cms_user_id",
    "visible":false
  },
  {
    "display":"Actions",
    "actions":
    [
      {
        "caption":"edit",
        "url":"{rootFolder}site-details",
        "urlParams":
        {
          "id":"{id}"
        }
      }
    ]
  }
]',
    'gallery_col_count' => '1',
    'items_per_page' => '20',
    'download_link' => '1',
    'footer' => '<a href="{rootFolder}site-details" class="pager-button">Add Site</a>',
    'redirect_on_success' => '',
    'message_after_save' => '0',
  ),
  'path' => 'site-list',
  'taxonomy' => array(),
  'uuid' => '84ffb1b0-c4ee-11e0-9708-e2fa3c3d7fc6',
  'pathauto_perform_alias' => FALSE,
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
  'title' => 'Site Details',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'sectioned_transects_edit_transect',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '1',
    'permission_name' => 'online recording',
    'map_centroid_lat' => 'default',
    'map_centroid_long' => 'default',
    'map_zoom' => 'default',
    'map_width' => '100%',
    'map_height' => '350',
    'remember_pos' => '0',
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
    'maxSectionCount' => '12',
    'sites_list_path' => 'site-list',
    'section_edit_path' => 'section-details',
    'spatial_systems' => 'OSGB',
    'redirect_on_success' => 'site-list',
    'message_after_save' => '1',
  ),
  'path' => 'site-details',
  'taxonomy' => array(),
  'uuid' => '84ffc99c-c4ee-11e0-9708-e2fa3c3d7fc6',
  'pathauto_perform_alias' => FALSE,
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
  'title' => 'Walk Data Entry',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'sectioned_transects_input_sample',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '1',
    'permission_name' => 'online recording',
    'map_centroid_lat' => 'default',
    'map_centroid_long' => 'default',
    'map_zoom' => 'default',
    'map_width' => '500',
    'map_height' => '600',
    'remember_pos' => '0',
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
    'redirect_on_success' => '',
    'message_after_save' => '0',
  ),
  'path' => 'input-data',
  'taxonomy' => array(),
  'uuid' => '84ffede9-c4ee-11e0-9708-e2fa3c3d7fc6',
  'pathauto_perform_alias' => FALSE,
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
  'title' => 'My Walks',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'report_grid',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '1',
    'permission_name' => 'online recording',
    'report_name' => 'library/samples/samples_list',
    'param_presets' => 'date_from=
date_to=
survey_id=
smpattrs=CMS User ID
attr_sample_cms_user_id={user_id}
sample_method_id=Transect',
    'param_defaults' => '',
    'output' => 'default',
    'report_group' => 'report',
    'params_in_map_toolbar' => '0',
    'refresh_timer' => '',
    'load_on_refresh' => '',
    'columns_config' => '[
  {
    "actions":
    [
      {
        "caption":"edit",
        "url":"{rootFolder}input-data",
        "urlParams":
        {
          "sample_id":"{sample_id}"
        }
      }
    ]
  }
]',
    'gallery_col_count' => '1',
    'items_per_page' => '20',
    'download_link' => '1',
    'footer' => '<a href="{rootFolder}input-data" class="pager-button">Add Walk Details</a>',
    'redirect_on_success' => '',
    'message_after_save' => '0',
  ),
  'taxonomy' => array(),
  'uuid' => '84fffa3b-c4ee-11e0-9708-e2fa3c3d7fc6',
);
  return $nodes;
}
