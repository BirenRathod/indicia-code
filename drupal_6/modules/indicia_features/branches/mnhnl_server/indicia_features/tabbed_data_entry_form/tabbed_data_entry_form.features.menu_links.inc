<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function tabbed_data_entry_form_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:72fbb6f2-ad87-11e0-aeb9-62cde1fc4d8d
  $menu_links['primary-links:72fbb6f2-ad87-11e0-aeb9-62cde1fc4d8d'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'Submit Sightings',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'title' => 'Submit Sightings',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'uuid' => '72fbb6f2-ad87-11e0-aeb9-62cde1fc4d8d'
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Submit Sightings');


  return $menu_links;
}
