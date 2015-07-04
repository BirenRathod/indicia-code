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
  $fields['profile_location_collation'] = array(
      'title' => 'Location of collation',
      'explanation' => 'For users who are in the regional collator role, this allows the '.
          'location which defines the boundary of their collation to be defined, for example '.
          'the boundary of a Local Record Centre.',
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
  $fields['profile_record_privacy'] = array(
      'title' => 'Record privacy',
      'explanation' => 'Tick this box if you would like to opt out of allowing your records to appear on other websites. '.
          'They will still be visible to users of this website.',
      'category' => 'Preferences',
      'type' => 'checkbox',
      'weight' => 0,
      'required' => 0,
      'register' => 0,
      'visibility' => 4,
      'autocomplete' => 0,
      'page' => '',
  );
  $fields['profile_training'] = array(
      'title' => 'Training',
      'explanation' => 'Tick this box to enable training mode. When in training mode, the records you create will be hidden from other users and will ' .
          'be only used for your training purposes. This only affects the records you create and not sites so you will still be able to practice inputting records for any '.
          'sites that you have already created.',
      'category' => 'Preferences',
      'type' => 'checkbox',
      'weight' => 0,
      'required' => 0,
      'register' => 0,
      'visibility' => 2,
      'autocomplete' => 0,
      'page' => '',
  );
  $fields['profile_u16'] = array(
      'title' => 'Under 16',
      'explanation' => 'Tick if you are under 16 years old?',
      'category' => 'Name',
      'type' => 'checkbox',
      'weight' => 3,
      'required' => 0,
      'register' => 1,
      'visibility' => 1,
      'autocomplete' => 0,
      'page' => 'Account',
  );
  $fields['profile_dob'] = array(
      'title' => 'Date of birth',
      'category' => 'Name',
      'type' => 'date',
      'weight' => 4,
      'required' => 0,
      'register' => 1,
      'visibility' => 1,
      'autocomplete' => 0,
      'page' => 'Account',
  );
  return $fields;
}