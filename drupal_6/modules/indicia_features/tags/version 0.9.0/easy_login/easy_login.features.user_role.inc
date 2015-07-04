<?php

/**
 * Implementation of hook_user_default_roles().
 */
function easy_login_user_default_roles() {
  $roles = array();

  $roles['regional collator'] = array(
    'name' => 'regional collator',
  );

  return $roles;
}
