<?php

function library_view() {  
  drupal_add_css(drupal_get_path('module', 'forms_and_surveys_library').'/forms_and_surveys_library-styles.css', 'module');
  $r = '<div id="library-toolbar" class="clearfix"><label id="search-label">Search:<input type="text" id="library-search"/></label>';
  global $user;
  profile_load_profile($user);
  $selected = empty($user->profile_favourite_library_forms) ? array() : unserialize($user->profile_favourite_library_forms);
  $active = count($selected)===0 ? ' class="button-active"' : '';
  $r .= "<button type=\"button\" id=\"organise-favourites\"$active/>".t('Find other forms')."</button></div>\n";
  if ($active) 
    $message=t('Click the title of one of the forms to access the form, or use the buttons to add forms to your list of favourite forms so you '.
        'can easily access them again in future.');
  else
    $message=t('Click the title of one of the forms to access the form, or use the Find other forms button to enable searching for additional '.
      'forms you might like to use.');
  drupal_set_message($message.' '.t('Forms are sorted so the ones most likely to be of interest to you are listed first.'));
  $r .= '<ul>';
  global $user;
  profile_load_profile($user);
  // find all the library form details
  $result = db_query("SELECT n.nid, l.library_title, l.library_description, l.location_ids, l.taxon_group_ids FROM {node} n
INNER JOIN {forms_and_surveys_library} l on l.nid=n.nid");
  // create arrays to hold the different sections of forms we will display
  $forms = array();
  // loop through the forms, work out a weighting score
  while ($row=db_fetch_object($result)) {
    $formLocations = unserialize($row->location_ids);
    $formTaxonGroups = unserialize($row->taxon_group_ids);
    // @todo Only add to the list of species forms or location forms if the form does not clash. In fact, why not
    // create a score for each form based on the total number of hits (location/species groups). Score zero
    // if match one but specifies the other and does not match. Score negative if no matches at all. Then can
    // display all forms that are > 0 in order.
    // scoring - - 1000 if from a different location, + 3 if any location overlap, + 1 for each taxon group overlap
    $score = 0;
    if (!empty($user->profile_location) && !empty($formLocations)) {
      if (in_array($user->profile_location, $formLocations)) {
        // a local form - that's a good thing
        $score += 3;
        $row->matchLocation=true;
      } else
        // form from somewhere else, so not really of interest
        $score -= 1000;
    }
    if (!empty($user->profile_taxon_groups) && !empty($formTaxonGroups)) {
      $userTaxonGroups = unserialize($user->profile_taxon_groups);
      if (array_intersect($userTaxonGroups, $formTaxonGroups)) {
        // a local form - that's a good thing
        $score += count(array_intersect($userTaxonGroups, $formTaxonGroups));
        $row->matchTaxonGroups=true;
      }
      else
        // form from somewhere else, so not really of interest
        $score -= 100;
    }
    $row->score = $score;
    $forms[] = $row;
  }
  uasort($forms, 'library_compare_rows');
  $r .= library_output_form_list($forms, $selected);
  drupal_add_js(drupal_get_path('module', 'forms_and_surveys_library').'/forms_and_surveys_library.js');
  drupal_add_js('indiciaData={"ajaxUrl":"'.url('forms_and_surveys_library/set_favourite').'",
  "addCaption": "'.t('Add to favourites').'",
  "removeCaption": "'.t('Remove from favourites').'",
};
', 'inline');
  return $r;
}

/** 
 * Sort function for the form scores. 
 */
function library_compare_rows($a, $b) {
  if ($a->score == $b->score) {
    return 0;
  }
  return ($a->score > $b->score) ? -1 : 1;
}

function library_output_form_list($forms, $selected) {
  $r = '';
  if (!empty($forms)) {
    $r .= '<ul id="library-form-list" class="gallery">';
    foreach($forms as $form) {
      $classes=array();
      if (count($selected)>0 && !in_array($form->nid, $selected))
        $classes[] = 'hidden';
      if (in_array($form->nid, $selected)) {
        $classes[] = 'selected';
      }
      $class = (count($classes)) ? ' class="'.implode(' ', $classes).'"' : '';
      $r .= '<li id="'.str_replace(' ', '_', strtolower($form->library_title)).'"'.$class.'>';
      $r .= '<h3>'.l(t($form->library_title), 'node/'.$form->nid).'</h3>';
      $r .= $form->library_description;
      $buttonCaption = (in_array($form->nid, $selected)) ? 'Remove from favourites' : 'Add to favourites'; 
      $r .= '<button type="button" id="btn-'.$form->nid.'">'.t($buttonCaption).'</button>';
      $r .= '</li>';
    }
    $r .= '</ul>';
    
  }
  return $r;
}
