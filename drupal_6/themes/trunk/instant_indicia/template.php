<?php

function instant_indicia_preprocess_page(&$variables) {
  // Check path to determine widget pages
  $pathargs = explode('/',drupal_get_path_alias($_GET['q']));
  if ($pathargs[0] == 'external' || (!empty($_GET['external']) && $_GET['external']==='t')) {
     // Use template: page__widgets
     $variables['template_file'] = 'page-iframe';
  } elseif ($pathargs[0] == 'popup' || (!empty($_GET['popup']) && $_GET['popup']==='t')) {
     // Use template: page__widgets
     $variables['template_file'] = 'page-popup';
  }
  
  drupal_set_html_head('<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">');
  $variables['head'] = drupal_get_html_head();
}
