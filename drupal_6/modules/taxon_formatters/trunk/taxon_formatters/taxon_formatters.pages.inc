<?php

function taxon_formatters_preset_overview() {
  $header = array(t('Preset Name'), t('Type'), t('Actions'));
  $rows = array();
  // Always clear the preset cache on this display.
  foreach (taxon_formatters_presets(TRUE) as $preset) {
    $row = array();
    $row[] = l($preset['presetname'], 'admin/build/taxon_formatters/'. $preset['presetid']);
    $row[] = $preset['type'];
    $row[] = l(t('View'), 'admin/build/taxon_formatters/'. $preset['presetid'])
          .'&nbsp;&nbsp;&nbsp;&nbsp;'
          .l(t('Delete'), 'admin/build/taxon_formatters/'. $preset['presetid'].'/delete');
    $rows[] = $row;
  }
  $output = theme('table', $header, $rows);
  return $output;
}

function taxon_formatters_preset_form($form_state, $preset = array()) {
  $form = array();
  $form['presetid'] = array(
    '#type' => 'value',
    '#value' => $preset['presetid'],
  );

  // Browsers don't submit disabled form values so we've got to put two copies
  // of the name on the form: one for the submit handler and one for the user.
  if ($preset['storage'] === TAXON_FORMATTERS_STORAGE_DEFAULT) {
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
      '#default_value' => $preset['presetname'],
      '#description' => t('The name used to refer to this formatter preset.'),
      '#required' => true
    );
  }
  $formatTypes = module_invoke_all('taxon_formatter_types');
  $formatters = array(''=>'<Please Select>');
  foreach ($formatTypes as $type=>$config) {
    $formatters[$type] = t($config['title']);
  }
  if (empty($preset['type'])) {
    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Formatter'),
      '#options' => $formatters,
      '#description' => t('Select the type of output you want for this preset'),
      '#required' => true,
      '#default_value' => $preset['type'],
      '#ahah' => array(
        'path' => 'taxon_formatter_settings/js/0',
        'wrapper' => 'taxon-formatter-settings',
        'method' => 'replace',
        'effect' => 'fade',
        'event' => 'change'
      )
    );
  } else {
    // for an existing formatter, set this as a fixed value on the form - the user cannot change the fundamental type of an existing formatter.
    $form['type'] = array(
      '#title' => t('Formatter'),
      '#type' => 'item',
      '#value' => t($formatTypes[$preset['type']]['title'])
    );
  }
  $form['taxon_formatter_params'] = array(
    '#type' => 'fieldset',
    '#title' => t('Formatter settings'),
    '#tree' => FALSE
  );
  
  // Define a wrapper in which to place just the list of settings
  $form['taxon_formatter_params']['taxon_formatter_params_wrapper'] = array(
    '#tree' => FALSE,
    '#weight' => 5,
    '#prefix' => '<div class="clear-block" id="taxon-formatter-settings">',
    '#suffix' => '</div>'
  );
  $type = isset($form_state['post']['type']) ? $form_state['post']['type'] : (isset($preset['type']) ? $preset['type'] : '');
  // Get the selected form's parameters  
  if ($type) {
    if (isset($preset['settings'])) 
      $settings = json_decode($preset['settings'], true);
    else
      $settings = array();
    $form['taxon_formatter_params']['taxon_formatter_params_wrapper'] = call_user_func($formatTypes[$type]['form_callback'], 
        $settings, $type, isset($formatTypes[$type]['form_args']) ? $formatTypes[$type]['form_args'] : null);
  } else {
    $form['taxon_formatter_params']['taxon_formatter_params_wrapper']['dummy'] = array(
      '#type' => 'item',
      '#value' => '<em>'.t('Please select a formatter before defining the settings.').'</em>'
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $preset['storage'] === TAXON_FORMATTERS_STORAGE_DEFAULT ? t('Override Defaults') : t('Save Preset')    
  );  
  
  return $form;
}

function taxon_formatters_preset_form_validate($form, &$form_state) {
  // @todo Delegate validation to the sub-module.
}

function taxon_formatters_preset_form_submit($form, &$form_state) {
  // build an array of the settings specific to the sub-module
  $settings = get_form_values_recursively($form['taxon_formatter_params']['taxon_formatter_params_wrapper']);
  // put the settings in the db field
  $form_state['values']['settings'] = json_encode($settings);
  // save the data, overwriting existing or creating a new record.
  if (isset($form_state['values']['presetid']) && is_numeric($form_state['values']['presetid'])) {
    drupal_write_record('taxon_formatters_preset', $form_state['values'], 'presetid');
  }
  else {
    drupal_write_record('taxon_formatters_preset', $form_state['values']);
  }
  drupal_set_message(t('Your form has been saved.'));
  // return to the list
  $form_state['redirect'] = 'admin/build/taxon_formatters/';
}

function taxon_formatters_preset_delete_form($form_state, $preset = array()) {
  if (empty($preset)) {
    drupal_set_message(t('The specified preset was not found'), 'error');
    drupal_goto('admin/build/taxon_formatters');
  }

  $form = array();
  $form['presetid'] = array('#type' => 'value', '#value' => $preset['presetid']);
  return confirm_form(
    $form,
    t('Are you sure you want to delete the preset %preset?',
      array('%preset' => $preset['presetname'])
    ),
    'admin/build/taxon_formatters',
    t('This action cannot be undone.'),
    t('Delete'),  t('Cancel')
  );
}

function taxon_formatters_preset_delete_form_submit($form, &$form_state) {
  $preset = taxon_formatters_preset($form_state['values']['presetid']);
  taxon_formatters_preset_delete($preset);
  drupal_set_message(t('Preset %name (ID: @id) was deleted.', array('%name' => $preset['presetname'], '@id' => $preset['presetid'])));
  $form_state['redirect'] = 'admin/build/taxon_formatters';
}

/*
 * Function to retrieve control #value fields held in an array.
 * Because the controls can be held in nested fieldsets the function is called 
 * recursively to work through the array structure.
 */
function get_form_values_recursively($arr) {  
  $r = array();
  foreach($arr as $setting => $config) {
    if (substr($setting, 0, 1)!='#') {
      // found a fieldset or a control
      if (isset($config['#value'])) {
        // it was a control
        $r[$setting] = $config['#value'];
      }
      else {
        // it was a fieldset
        $r = array_merge ($r, get_form_values_recursively($config));
      }
    }
  }
  return $r;
}
