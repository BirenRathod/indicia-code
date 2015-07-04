<?php

/**
 * Implementation of hook_user_default_roles().
 */
function indicia_quickstart_user_default_roles() {
  $roles = array();

  // Exported role: admin user
  $roles['admin user'] = array(
    'name' => 'admin user',
  );

  // Exported role: site editor
  $roles['site editor'] = array(
    'name' => 'site editor',
  );
  
  // Exported role: verifier
  $roles['verifier'] = array(
    'name' => 'verifier',
  );

  return $roles;
}
