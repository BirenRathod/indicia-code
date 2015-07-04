<?php

/**
 * Implementation of hook_node_info().
 */
function survey_summaries_node_info() {
  $items = array(
    'survey_summary' => array(
      'name' => t('Survey summary'),
      'module' => 'features',
      'description' => t('A summary of a survey'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Header'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
