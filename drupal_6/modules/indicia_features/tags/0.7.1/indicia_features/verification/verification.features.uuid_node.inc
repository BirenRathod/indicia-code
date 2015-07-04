<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function verification_uuid_features_default_content() {
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
  'title' => 'Verification',
  'body' => '',
  'teaser' => '',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'iform' => 'verification_3',
  'needs_review' => 3,
  'params' => array(
    'view_access_control' => '1',
    'permission_name' => 'verifier',
    'map_centroid_lat' => 'default',
    'map_centroid_long' => 'default',
    'map_zoom' => 'default',
    'map_width' => '100%',
    'map_height' => '400',
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
    'report_name' => 'library/occurrences/verification_list',
    'param_presets' => 'survey_id=
date_from=
date_to=
smpattrs=
occattrs=',
    'param_defaults' => 'id=
taxon_group_id=
record_status=C',
    'columns_config' => '[
  {
    "fieldname":"occurrence_id",
    "template":"<div class=\'status-{record_status}\'>{occurrence_id}</div>",
    "display":"ID"
  },
  {
    "fieldname":"taxon",
    "display":"Species",
    "template":"<div class=\'zero-{zero_abundance}\'>{taxon}<br/>{common}</div>"
  },
  {
    "fieldname":"record_status",
    "visible":false
  },
  {
    "fieldname":"common",
    "visible":false
  },
  {
    "fieldname":"zero_abundance",
    "visible":false
  }
]',
    'verifiers_mapping' => '1',
    'email_subject_send_to_verifier' => 'Record of %taxon% requires verification (ID:%id%)',
    'email_body_send_to_verifier' => 'The following record requires verification. Please reply to this mail with the word Verified or Rejected in the email body, followed by any comments you have including the proposed re-identification if relevant on the next line.

%record%',
    'auto_discard_rows' => '1',
    'redirect_on_success' => '',
    'message_after_save' => '0',
  ),
  'path' => 'verification',
  'taxonomy' => array(),
  'uuid' => 'f33db6bf-e42a-11e0-8605-b73afd456118',
  'pathauto_perform_alias' => FALSE,
);
  return $nodes;
}
