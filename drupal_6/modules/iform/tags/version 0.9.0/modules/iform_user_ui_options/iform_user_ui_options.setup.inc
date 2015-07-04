<?php

/**
 * Return an associative array defining the list of required profile fields.
 */
function _iform_ui_options_profile_fields() {
  $fields = array();
  $fields['profile_iform_ui_options'] = array(
      'title' => 'IForm UI options',
      'explanation' => 'Form parameter overrides to pass to dynamic forms for this user, e.g. to override map layer settings.',
      'category' => 'System',
      'type' => 'textfield',
      'weight' => 1,
      'required' => 0,
      'register' => 0,
      'visibility' => 4,
      'autocomplete' => 0,
      'options' => '',
      'page' => ''
  );
  return $fields;
}