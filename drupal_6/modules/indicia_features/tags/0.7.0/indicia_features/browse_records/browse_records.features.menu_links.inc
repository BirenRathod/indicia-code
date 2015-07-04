<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function browse_records_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:afa4c942-bc23-11e0-a701-430b6d02c0c0
  $menu_links['primary-links:afa4c942-bc23-11e0-a701-430b6d02c0c0'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'Browse Records',
    'options' => array(
      'attributes' => array(
        'title' => 'Browse Records',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '12',
    'uuid' => 'afa4c942-bc23-11e0-a701-430b6d02c0c0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Browse Records');


  return $menu_links;
}
