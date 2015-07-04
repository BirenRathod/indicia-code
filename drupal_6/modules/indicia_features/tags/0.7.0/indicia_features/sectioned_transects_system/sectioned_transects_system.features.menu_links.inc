<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function sectioned_transects_system_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:240ac08d-c99f-11e0-9708-e2fa3c3d7fc6
  $menu_links['primary-links:240ac08d-c99f-11e0-9708-e2fa3c3d7fc6'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'All Sites',
    'options' => array(
      'attributes' => array(
        'title' => 'All Sites',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'uuid' => '240ac08d-c99f-11e0-9708-e2fa3c3d7fc6',
  );
  // Exported menu link: primary-links:84ffb1b0-c4ee-11e0-9708-e2fa3c3d7fc6
  $menu_links['primary-links:84ffb1b0-c4ee-11e0-9708-e2fa3c3d7fc6'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'My Sites',
    'options' => array(
      'attributes' => array(
        'title' => 'My Sites',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'uuid' => '84ffb1b0-c4ee-11e0-9708-e2fa3c3d7fc6',
  );
  // Exported menu link: primary-links:84ffede9-c4ee-11e0-9708-e2fa3c3d7fc6
  $menu_links['primary-links:84ffede9-c4ee-11e0-9708-e2fa3c3d7fc6'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'Input Data',
    'options' => array(
      'attributes' => array(
        'title' => 'Walk Data Entry',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'uuid' => '84ffede9-c4ee-11e0-9708-e2fa3c3d7fc6',
  );
  // Exported menu link: primary-links:84fffa3b-c4ee-11e0-9708-e2fa3c3d7fc6
  $menu_links['primary-links:84fffa3b-c4ee-11e0-9708-e2fa3c3d7fc6'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'My Walks',
    'options' => array(
      'attributes' => array(
        'title' => 'My Walks',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'uuid' => '84fffa3b-c4ee-11e0-9708-e2fa3c3d7fc6',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('All Sites');
  t('Input Data');
  t('My Walks');
  t('Sites List');


  return $menu_links;
}
