<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function summary_reports_fieldgroup_default_groups() {
  $groups = array();
  
  // Exported group: group_site_settings
  $groups['summary_report-group_site_settings'] = array(
    'group_type' => 'standard',
    'type_name' => 'summary_report',
    'group_name' => 'group_site_settings',
    'label' => 'Site Settings',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '1',
    'fields' => array(
      '0' => 'field_summary_report_spatial',
    ),
  );

  // Exported group: group_map_settings
  $groups['summary_report-group_map_settings'] = array(
    'group_type' => 'standard',
    'type_name' => 'summary_report',
    'group_name' => 'group_map_settings',
    'label' => 'Map Settings',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '1',
    'fields' => array(
      '0' => 'field_summary_report_map_output',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Map Settings');

  return $groups;
}
