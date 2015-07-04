<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function easy_login_user_default_permissions() {
  $permissions = array();

  // Exported permission: add twitter accounts
  $permissions['add twitter accounts'] = array(
    'name' => 'add twitter accounts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );
  
  // Exported permission: administer experts
  $permissions['administer experts'] = array(
    'name' => 'administer experts',
    'roles' => array(
      '0' => 'admin user',
    ),
  );

  return $permissions;
}
