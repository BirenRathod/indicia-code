<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function easy_login_user_default_permissions() {
  $permissions = array();

  /*// Exported permission: add twitter accounts
  $permissions['add twitter accounts'] = array(
    'name' => 'add twitter accounts',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );*/
  
  // Exported permission: collate regional records
  $permissions['collate regional records'] = array(
    'name' => 'collate regional records',
    'roles' => array(
      '0' => 'regional collator',
    ),
  );

  return $permissions;
}
