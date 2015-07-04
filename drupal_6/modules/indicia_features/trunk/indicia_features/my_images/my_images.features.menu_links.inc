<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function my_images_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:622f1ca5-bc25-11e0-a701-430b6d02c0c0
  $menu_links['primary-links:622f1ca5-bc25-11e0-a701-430b6d02c0c0'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'My Images',
    'options' => array(
      'attributes' => array(
        'title' => 'My Images',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10',
    'uuid' => '622f1ca5-bc25-11e0-a701-430b6d02c0c0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('My Images');


  return $menu_links;
}
