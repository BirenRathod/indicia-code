<?php

/**
 * Implementation of hook_node_info().
 */
function summary_reports_node_info() {
  $items = array(
    'summary_report' => array(
      'name' => t('Summary Report'),
      'module' => 'features',
      'description' => t('A content type that creates a summary report.'),
      'has_title' => '1',
      'title_label' => t('Report Name'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function summary_reports_views_api() {
  return array(
    'api' => '2',
  );
}
