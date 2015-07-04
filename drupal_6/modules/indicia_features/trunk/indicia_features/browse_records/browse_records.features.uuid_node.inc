<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function browse_records_uuid_features_default_content() {
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
  'title' => 'Browse Records',
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
    'report_name' => 'library/occurrences/occurrences_list',
    'param_presets' => 'survey_id=
smpattrs=
occattrs=',
    'param_defaults' => 'date_from=
date_to=
taxon_group_id=',
    'output' => 'default',
    'report_group' => 'report',
    'params_in_map_toolbar' => '0',
    'refresh_timer' => '',
    'load_on_refresh' => '',
    'columns_config' => '[

]',
    'gallery_col_count' => '1',
    'items_per_page' => '20',
    'download_link' => '1',
    'footer' => '',
    'redirect_on_success' => '',
    'message_after_save' => '0',
  ),
  'path' => 'browse-records',
  'taxonomy' => array(),
  'uuid' => 'afa4c942-bc23-11e0-a701-430b6d02c0c0'
);
  return $nodes;
}
