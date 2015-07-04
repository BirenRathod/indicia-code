<?php
/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function mobile_iform_form_system_theme_settings_alter(&$form, &$form_state)  {

  $form['mobile_iform_settings'] = array(
    '#type' => 'fieldset',
    '#weight' => -20,
    '#title' => t('Mobile IForm Configuration'),
  );
  $form['mobile_iform_settings']['app_home'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to start page.'),
    '#description' => t(<<<EOD
Under certain conditions we want to return to the starting point which may not
be the home page of the website. Enter the path relative to the base path here
without a leading slash.
EOD
          ),
    '#default_value' => mobile_jquery_theme_get_setting('app_home'),
    '#weight' => -20,
  );
  
}