<?php

/**
 * Implementation of hook_views_default_views().
 */
function summary_reports_views_default_views() {
  $views = array();

  // Exported view: summary_report
  $view = new view;
  $view->name = 'summary_report';
  $view->description = 'List of summary reports';
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_summary_report_display_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'raw',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_summary_report_display_value',
      'table' => 'node_data_field_summary_report_display',
      'field' => 'field_summary_report_display_value',
      'relationship' => 'none',
    ),
    'field_summary_report_inclusion_value' => array(
      'label' => 'Which data should be included?',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_summary_report_inclusion_value',
      'table' => 'node_data_field_summary_report_inclusion',
      'field' => 'field_summary_report_inclusion_value',
      'relationship' => 'none',
    ),
    'phpcode' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'value' => '<?php
switch ($data->node_data_field_summary_report_display_field_summary_report_inclusion_value) {
  case \'Collaborating websites\': 
    echo \'All records\';
    break;
  case \'Current website\': 
    echo \'Records added via iRecord\';
    break;
  case \'Logged in user\': 
    echo \'My records\';
    break;
  default: 
    echo $data->node_data_field_summary_report_display_field_summary_report_inclusion_value;
}
?>',
      'exclude' => 1,
      'id' => 'phpcode',
      'table' => 'customfield',
      'field' => 'phpcode',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<div class="summary-report report-[field_summary_report_display_value]">[title]</div>',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'field_summary_report_display_value' => array(
      'order' => 'ASC',
      'delta' => -1,
      'id' => 'field_summary_report_display_value',
      'table' => 'node_data_field_summary_report_display',
      'field' => 'field_summary_report_display_value',
      'relationship' => 'none',
    ),
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'summary_report' => 'summary_report',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header', '<?php
$breadcrumb = array();
$breadcrumb[] = l(\'Home\', \'<front>\');
$breadcrumb[] = t(\'Summarise\');
// Set Breadcrumbs
drupal_set_breadcrumb($breadcrumb);
?>');
  $handler->override_option('header_format', '3');
  $handler->override_option('header_empty', 1);
  $handler->override_option('items_per_page', '0');
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => 'phpcode',
    'columns' => '8',
    'alignment' => 'horizontal',
    'fill_single_line' => 0,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'summarise');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Summarise',
    'description' => 'Summary reports to provide an overview of iRecord\'s data.',
    'weight' => '4',
    'name' => 'primary-links',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));

  $views[$view->name] = $view;

  return $views;
}
