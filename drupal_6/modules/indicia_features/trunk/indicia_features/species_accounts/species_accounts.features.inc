<?php

/**
 * Implementation of hook_node_info().
 */
function species_accounts_node_info() {
  $items = array(
    'image' => array(
      'name' => t('Image'),
      'module' => 'features',
      'description' => t('An image which can be attached to a species account for example.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Comment'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'species_account' => array(
      'name' => t('Species Account'),
      'module' => 'features',
      'description' => t('A general purpose content type for storing species accounts. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('General Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
