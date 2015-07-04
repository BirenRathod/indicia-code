<?php

/**
 * @file
 * Template.php - process theme data for your sub-theme.
 * 
 * Rename each function and instance of "footheme" to match
 * your subthemes name, e.g. if you name your theme "footheme" then the function
 * name will be "footheme_preprocess_hook". Tip - you can search/replace
 * on "footheme".
 */


/**
 * Override or insert variables for the html template.
 */
/* -- Delete this line if you want to use this function
function indiciatheme_preprocess_html(&$vars) {
}
function indiciatheme_process_html(&$vars) {
}
// */


/**
 * Override or insert variables for the page templates.
 */
function indiciatheme_preprocess_page(&$vars) {
  // Check path to determine widget pages
  $pathargs = explode('/',drupal_get_path_alias($_GET['q']));
  if ($pathargs[0] == 'external' || (!empty($_GET['external']) && $_GET['external']==='t')) {
     // Switch template to remove extraneous stuff for iframes.
     array_unshift($vars['theme_hook_suggestions'], 'page__iframe');
  }
}


/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function indiciatheme_preprocess_node(&$vars) {
}
function indiciatheme_process_node(&$vars) {
}
// */


/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function indiciatheme_preprocess_comment(&$vars) {
}
function indiciatheme_process_comment(&$vars) {
}
// */


/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function indiciatheme_preprocess_block(&$vars) {
}
function indiciatheme_process_block(&$vars) {
}
// */
