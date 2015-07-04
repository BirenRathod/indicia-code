<?php

/**
 * @file
 * Administrative page callbacks.
 */

function appcache_settings_form($form_state) {
  $form = array();

  $form['appcache_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the HTML5 offline application cache'),
    '#default_value' => variable_get('appcache_enabled', FALSE),
  );

  $form['appcache_automatic'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically cache visited pages and resources'),
    '#description' => t('This setting will tell browsers to cache all resources they visit, except for any Administrative pages. In this mode, no other modules will be able to modify the application cache manifest.'),
    '#default_value' => variable_get('appcache_automatic', FALSE),
    '#states' => array(
      'visible' => array(
        ':input[name="appcache_enabled"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['appcache_custom'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="appcache_enabled"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="appcache_automatic"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['appcache_custom']['appcache_cache'] = array(
    '#type' => 'textarea',
    '#title' => t('CACHE section'),
    '#description' => t('Enter the resources to store in the application cache. Do not include the leading %base_url.', array('%base_url' => $GLOBALS['base_url'])),
    '#default_value' => implode("\r\n", variable_get('appcache_cache', array())),
  );
  
  $form['appcache_custom']['appcache_cache_extra'] = array(
    '#type' => 'fieldset',
    '#title' => t('CACHE section extra parameters'),
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE,
  );
  
  $form['appcache_custom']['appcache_cache_extra']['appcache_cache_query'] = array(
    '#type' => 'textarea',
    '#title' => t('Query string added'),
    '#description' => t('A query string will be appended to the clean ending of JavaScript and CSS files. Current string is: %query_string', array('%query_string' => variable_get('css_js_query_string', 0))),
    '#default_value' => implode("\r\n", variable_get('appcache_cache_query', array())),
  );

  $form['appcache_custom']['appcache_network'] = array(
    '#type' => 'textarea',
    '#title' => t('NETWORK section'),
    '#description' => t('Enter the resources to never store in the application cache. Do not include the leading %base_url.', array('%base_url' => $GLOBALS['base_url'])),
    '#default_value' => implode("\r\n", variable_get('appcache_network', array())),
  );

  $form['appcache_custom']['appcache_fallback'] = array(
    '#type' => 'textarea',
    '#title' => t('FALLBACK section'),
    '#description' => t('Enter the fallback paths to use if a resource is not found in the application cache. Do not include the leading %base_url.', array('%base_url' => $GLOBALS['base_url'])),
    '#default_value' => implode("\r\n", variable_get('appcache_fallback', array())),
  );

  $form['#submit'] = array('appcache_settings_submit', 'appcache_cache_clear');

  return system_settings_form($form);
}

/**
 * FAPI submit callback to save appcache sections as arrays.
 */
function appcache_settings_submit($form, &$form_state) {
  $sections = array('cache', 'cache_query', 'network', 'fallback');

  foreach ($sections as $section) {
    $form_state['values']['appcache_' . $section] = explode("\r\n", $form_state['values']['appcache_' . $section]);
  }
}

