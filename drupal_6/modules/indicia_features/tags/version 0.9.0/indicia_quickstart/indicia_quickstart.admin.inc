<?php

function indicia_quickstart_other_settings_form_inc() {
  iform_load_helpers(array('data_entry_helper'));
  $readAuth = data_entry_helper::get_read_auth(variable_get('indicia_website_id', ''), variable_get('indicia_password', ''));
  $response = data_entry_helper::get_population_data(array(
    'table' => 'taxon_list',
    'extraParams' => $readAuth + array('orderby'=>'name', 'sortdir'=>'ASC'),
    'nocache' => true
  ));
  $lists = array(''=>t('<Please select>'));
  foreach ($response as $list) {
    $lists[$list['id']] = $list['title'];
  }
  $form=array();
  $form['master_checklist_id'] = array(
    '#type'=>'select',
    '#title'=>'Master Species Checklist',
    '#description'=>t('Select the checklist which contains the master copy of all species used by this site, if such a thing exists. It will be '.
        'used to allow the user to pick from only the species groups that are relevant to the site in their preferences.'),
    '#default_value'=>variable_get('iform_master_checklist_id', ''),
    '#options'=>$lists
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings')    
  );
  return $form;
  
}

/**
 * Validate method for the other settings config form.
 */
function indicia_quickstart_other_settings_form_validate($form, &$form_state) {
  // Nothing to validate
}

/**
 * Submit method for the other settings config form.
 */
function indicia_quickstart_other_settings_form_submit($form, &$form_state) {
  variable_set('iform_master_checklist_id', $form_state['values']['master_checklist_id']);
  drupal_set_message(t('Settings saved.'));
}
