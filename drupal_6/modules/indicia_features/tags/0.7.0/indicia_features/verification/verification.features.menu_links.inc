<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function verification_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:f33db6bf-e42a-11e0-8605-b73afd456118
  $menu_links['primary-links:f33db6bf-e42a-11e0-8605-b73afd456118'] = array(
    'menu_name' => 'primary-links',
    'router_path' => 'node/%',
    'link_title' => 'Verification',
    'options' => array(
      'attributes' => array(
        'title' => 'Verification',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'uuid' => 'f33db6bf-e42a-11e0-8605-b73afd456118',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Verification');


  return $menu_links;
}
