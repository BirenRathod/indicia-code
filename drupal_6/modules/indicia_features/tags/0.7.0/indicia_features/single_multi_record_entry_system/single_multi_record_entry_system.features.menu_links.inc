<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function single_multi_record_entry_system_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:5955430e-b90f-11e0-9f01-deef1494ab9e
  $menu_links['primary-links:5955430e-b90f-11e0-9f01-deef1494ab9e'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'Recording',
    'options' => array(
      'attributes' => array(
        'title' => 'Recording',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'uuid' => '5955430e-b90f-11e0-9f01-deef1494ab9e',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Recording');


  return $menu_links;
}
