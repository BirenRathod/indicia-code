<?php

/**
 * Implementation of hook_content_default_fields().
 */
function survey_summaries_content_default_fields() {
  $fields = array();

  // Exported field: field_survey_id
  $fields['survey_summary-field_survey_id'] = array(
    'field_name' => 'field_survey_id',
    'type_name' => 'survey_summary',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '1',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'iform_load_helpers(array(\'data_entry_helper\'));
$readAuth = data_entry_helper::get_read_auth(variable_get(\'indicia_website_id\',0), variable_get(\'indicia_password\',\'\'));
$surveys = data_entry_helper::get_population_data(array(
  \'table\'=>\'survey\',
  \'extraParams\'=>$readAuth
));
$r = array();
foreach ($surveys as $survey) {
  $r[$survey[\'id\']]=$survey[\'title\'];
}
return $r;',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Survey',
      'weight' => '-2',
      'description' => 'Select the survey to output a summary for',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_survey_summary_output
  $fields['survey_summary-field_survey_summary_output'] = array(
    'field_name' => 'field_survey_summary_output',
    'type_name' => 'survey_summary',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '5',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '[participation_map]
[latest_photos]
[recorder_league]
[species_totals_by_group_pie]',
          '_error_element' => 'default_value_widget][field_survey_summary_output][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Output',
      'weight' => '-1',
      'description' => 'Setup the output reports that are to be included on this survey summary page. One per line, selected from the following options:
[participation_map]
[latest_photos]
[recorder_league]
[recorder_league_pie]
[species_totals_by_group]
[species_totals_by_group_pie]',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Output');
  t('Survey');

  return $fields;
}
