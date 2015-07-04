<?php

/**
 * Return an associative array defining the list of required profile fields.
 */
function _easy_login_profile_fields() {
  $fields = array();
  $fields['profile_indicia_user_id'] = array(
      'title' => 'Indicia User ID',
      'explanation' => 'User ID for this account on the warehouse',
      'category' => 'System',
      'type' => 'textfield',
      'weight' => 1,
      'required' => 0,
      'register' => 0,
      'visibility' => 4,
      'autocomplete' => 0,
      'options' => '',
      'page' => ''
  );
  $fields['profile_first_name'] = array(
      'title' => 'First name',
      'explanation' => 'User\'s first name',
      'category' => 'Name',
      'type' => 'textfield',
      'weight' => 1,
      'required' => 0,
      'register' => 1,
      'visibility' => 2,
      'autocomplete' => 0,
      'options' => '',
      'page' => 'Account'
  );
  $fields['profile_last_name'] = array(
      'title' => 'Last name',
      'explanation' => 'User\'s last name',
      'category' => 'Name',
      'type' => 'textfield',
      'weight' => 2,
      'required' => 1,
      'register' => 1,
      'visibility' => 2,
      'autocomplete' => 0,
      'options' => '',
      'page' => 'Account'
  );
  $fields['profile_location'] = array(
      'title' => 'Location',
      'explanation' => 'If you would like to, please tell us the area you generally record in. This will allow us to tailor data entry screens and '.
	      'reports to the information that is most likely to be of interest to you.',
      'category' => 'Preferences',
      'type' => 'selection',
      'weight' => 0,
      'required' => 0,
      'register' => 0,
      'visibility' => 2,
      'autocomplete' => 0,
      'options' => '',
      'page' => ''
  );
  $fields['profile_taxon_groups'] = array(
      'title' => 'Species groups',
      'explanation' => 'If you would like to, please tell us the species groups you are interested in recording. This indicates a preference only, you will still '.
          'be able to record other species. It also allows us to tailor reports in iRecord to show you information that is most likely to be of interest.',
      'category' => 'Preferences',
      'type' => 'selection',
      'weight' => 1,
      'required' => 0,
      'register' => 0,
      'visibility' => 2,
      'autocomplete' => 0,
      'options' => '',
      'page' => '',
      'checkboxes' => true
  );
  $fields['profile_location_expertise'] = array(
      'title' => 'Location of expertise',
      'explanation' => 'Area your expertise applies in if relevant, e.g. the county you are a county recorder for. If left blank then verification access is given for all locations.',
      'category' => 'Preferences',
      'type' => 'selection',
      'weight' => 0,
      'required' => 0,
      'register' => 0,
      'visibility' => 2,
      'autocomplete' => 0,
      'options' => '',
      'page' => ''
  );
  $fields['profile_taxon_groups_expertise'] = array(
      'title' => 'Species groups you have expertise in',
      'explanation' => 'If considered an expert in one or more species groups (e.g. if a county recorder) select them here. If left blank then all species will be available for verification.',
      'category' => 'Preferences',
      'type' => 'selection',
      'weight' => 1,
      'required' => 0,
      'register' => 0,
      'visibility' => 2,
      'autocomplete' => 0,
      'options' => '',
      'page' => '',
      'checkboxes' => true
  );
  $fields['profile_surveys_expertise'] = array(
      'title' => 'Surveys you are an expert for',
      'explanation' => 'If expertise is restricted to one or more surveys, select them here. If left blank then any survey\'s data can be verified.' ,
      'category' => 'Preferences',
      'type' => 'selection',
      'weight' => 2,
      'required' => 0,
      'register' => 0,
      'visibility' => 2,
      'autocomplete' => 0,
      'options' => '',
      'page' => ''
  );
  return $fields;
}