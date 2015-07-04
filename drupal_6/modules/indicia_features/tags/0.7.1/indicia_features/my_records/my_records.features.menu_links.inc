<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function my_records_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:390b070b-b175-11e0-8f78-c5fda54158f2
  $menu_links['primary-links:390b070b-b175-11e0-8f78-c5fda54158f2'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'My Records',
    'options' => array(
      'attributes' => array(
        'title' => 'My Records',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10',
    'uuid' => '390b070b-b175-11e0-8f78-c5fda54158f2',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('My Records');


  return $menu_links;
}
