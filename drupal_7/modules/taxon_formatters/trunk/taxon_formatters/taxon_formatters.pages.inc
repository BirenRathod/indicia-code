<?php
/**
 * @file
 * Include file containing functions for the taxon_formatter module
 * relating to management of presets.
 */

/**
 * Creates an overview table of presets.
 * 
 * @return string
 *   The themed preset overview.
 */
function taxon_formatters_preset_overview() {
  $header = array(t('Preset Name'), t('Type'), t('Actions'));
  $rows = array();
  // Always clear the preset cache on this display.
  foreach (taxon_formatters_presets(TRUE) as $preset) {
    $row = array();
    $row[] = l($preset['presetname'], 'admin/config/content/taxon_formatters/' . $preset['presetid']);
    $row[] = $preset['type'];
    $row[] = l(t('View'), 'admin/config/content/taxon_formatters/' . $preset['presetid']) .
          '&nbsp;&nbsp;&nbsp;&nbsp;' .
          l(t('Delete'), 'admin/config/content/taxon_formatters/' . $preset['presetid'] . '/delete');
    $rows[] = $row;
  }
  $output = theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}

/**
 * Creates the preset form.
 * 
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 * @param array $preset
 *   Details of an existing preset if editing or absent if adding.
 * 
 * @return array
 *   A form array.
 */
function taxon_formatters_preset_form($form, &$form_state, $preset = array()) {
  // A hidden value containing the presetid.
  $form['presetid'] = array(
    '#type' => 'value',
    '#value' => isset($preset['presetid']) ? $preset['presetid'] : '',
  );

  // The preset name field.
  $is_default_preset = isset($preset['storage']) && $preset['storage'] === TAXON_FORMATTERS_STORAGE_DEFAULT;
  if ($is_default_preset) {
  // Browsers don't submit disabled form values so we've got to put two copies
  // of the name on the form: one for the submit handler and one for the user.
    $form['presetname'] = array(
      '#type' => 'value',
      '#value' => $preset['presetname'],
    );
    $form['presetname_display'] = array(
      '#type' => 'textfield',
      '#size' => '64',
      '#title' => t('Formatter Preset Name'),
      '#default_value' => $preset['presetname'],
      '#disabled' => TRUE,
    );
  }
  else {
    $form['presetname'] = array(
      '#type' => 'textfield',
      '#size' => '64',
      '#title' => t('Formatter Preset Name'),
      '#default_value' => isset($preset['presetname']) ? $preset['presetname'] : '',
      '#description' => t('The name used to refer to this formatter preset.'),
      '#required' => TRUE,
    );
  }
  
  // Invoke hook_taxon_formatter_types to find what enabled modules provide.
  $format_types = module_invoke_all('taxon_formatter_types');
  $formatters = array('' => '<Please Select>');
  foreach ($format_types as $type => $config) {
    $formatters[$type] = t($config['title']);
  }
  // The format type field.
  if (empty($preset['type'])) {
    //For a new preset, an Ajax field that will load settings for selected type.
    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Formatter'),
      '#options' => $formatters,
      '#description' => t('Select the type of output you want for this preset'),
      '#required' => TRUE,
      '#ajax' => array(
//        'path' => 'taxon_formatter_settings/js/0',
        'callback' => 'get_settings_js',
        'wrapper' => 'taxon-formatter-settings',
        'method' => 'replace',
        'effect' => 'fade',
        'event' => 'change',
      ),
    );
  }
  else {
    // For an existing preset, set this as a fixed value on the form - the
    // user cannot change the fundamental type of an existing formatter.
    $form['type'] = array(
      '#title' => t('Formatter'),
      '#type' => 'item',
      '#value' => t($format_types[$preset['type']]['title']),
    );
  }
  
  // A container for formatter settings
  $form['taxon_formatter_params'] = array(
    '#type' => 'fieldset',
    '#title' => t('Formatter settings'),
    '#prefix' => '<div class="clear-block" id="taxon-formatter-settings">',
    '#suffix' => '</div>',
    '#tree' => FALSE,
  );

  // Define a wrapper in which to place the formatter fields.
  $form['taxon_formatter_params']['taxon_formatter_params_wrapper'] = array(
    '#type' => 'item',
    '#markup' => '<em>' . t('Please select a formatter before defining the settings.') . '</em>',
    '#tree' => FALSE,
  );

  // The formatter type is in $form_state when an Ajax callback is in 
  // progress. It is in $preset if editing an existing preset
  if (!empty($form_state['input']['type']) || (isset($preset['type']))) {
    $settings = (isset($preset['settings'])) ?  json_decode($preset['settings'], TRUE) : array();
    $type = isset($form_state['input']['type']) ? $form_state['input']['type'] : $preset['type'];
    $func = $format_types[$type]['form_callback'];
    $args = isset($format_types[$type]['form_args']) ? $format_types[$type]['form_args'] : NULL;
    // Call the form function for the selected formatter
    $form['taxon_formatter_params']['taxon_formatter_params_wrapper'] = 
            call_user_func($func, $settings, $type, $args);
  }
  
  // The submit button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $is_default_preset ? t('Override Defaults') : t('Save Preset'),
  );

  return $form;
}

/**
 * Validate the preset form.
 * 
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state.
 */
function taxon_formatters_preset_form_validate($form, &$form_state) {
  // @todo Delegate validation to the sub-module.
}

/**
 * Submits the preset form.
 * 
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state.
 */
function taxon_formatters_preset_form_submit($form, &$form_state) {
  // Build an array of the settings specific to the sub-module.
  $settings = get_form_values_recursively($form['taxon_formatter_params']['taxon_formatter_params_wrapper']);
  // Put the settings in the db field.
  $form_state['values']['settings'] = json_encode($settings);
  // Save the data, overwriting existing or creating a new record.
  if (isset($form_state['values']['presetid']) && is_numeric($form_state['values']['presetid'])) {
    drupal_write_record('taxon_formatters_preset', $form_state['values'], 'presetid');
  }
  else {
    drupal_write_record('taxon_formatters_preset', $form_state['values']);
  }
  drupal_set_message(t('Your form has been saved.'));
  // Return to the list.
  $form_state['redirect'] = 'admin/config/content/taxon_formatters/';
}

/**
 * Creates the preset delete form.
 * 
 * @param array $form_state
 *   The form state.
 * @param array $preset
 *   Details of the preset.
 * 
 * @return array
 *   The form array.
 */
function taxon_formatters_preset_delete_form($form, &$form_state, $preset = array()) {
  if (empty($preset)) {
    drupal_set_message(t('The specified preset was not found'), 'error');
    drupal_goto('admin/config/content/taxon_formatters');
  }

  $form = array();
  $form['presetid'] = array(
    '#type' => 'value',
    '#value' => $preset['presetid'],
  );
  return confirm_form(
    $form,
    t('Are you sure you want to delete the preset %preset?',
      array('%preset' => $preset['presetname'])
    ),
    'admin/config/content/taxon_formatters',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

/**
 * Deletes the preset.
 * 
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state.
 */
function taxon_formatters_preset_delete_form_submit($form, &$form_state) {
  $preset = taxon_formatters_preset($form_state['values']['presetid']);
  taxon_formatters_preset_delete($preset);
  drupal_set_message(t('Preset %name (ID: @id) was deleted.', array('%name' => $preset['presetname'], '@id' => $preset['presetid'])));
  $form_state['redirect'] = 'admin/config/content/taxon_formatters';
}

/**
 * Function to retrieve control #value fields held in an array.
 * 
 * Because the controls can be held in nested fieldsets the function is called
 * recursively to work through the array structure.
 */
function get_form_values_recursively($arr) {
  $r = array();
  foreach ($arr as $setting => $config) {
    if (substr($setting, 0, 1) != '#') {
      // Found a fieldset or a control.
      if (isset($config['#value'])) {
        // It was a control.
        $r[$setting] = $config['#value'];
      }
      else {
        // It was a fieldset.
        $r = array_merge($r, get_form_values_recursively($config));
      }
    }
  }
  return $r;
}
