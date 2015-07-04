<?php

/**
 * Implementation of hook_default_page_manager_pages().
 */
function home_page_default_page_manager_pages() {
  $page = new stdClass;
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'home';
  $page->task = 'page';
  $page->admin_title = 'Home Page';
  $page->admin_description = 'A home page layout';
  $page->path = 'home';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array();
  $page->default_handlers = array();
  $handler = new stdClass;
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_home_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'home';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display;
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
          1 => 1,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'left_col',
          1 => 'right_col',
        ),
        'parent' => 'main',
        'class' => '',
      ),
      'left_col' => array(
        'type' => 'region',
        'title' => 'left-col',
        'width' => 50,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
      ),
      'right_col' => array(
        'type' => 'region',
        'title' => 'right-col',
        'width' => 50,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'left_col' => NULL,
      'right_col' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass;
    $pane->pid = 'new-1';
    $pane->panel = 'left_col';
    $pane->type = 'views';
    $pane->subtype = 'latest_news';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '10',
      'pager_id' => '',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-1'] = $pane;
    $display->panels['left_col'][0] = 'new-1';
    $pane = new stdClass;
    $pane->pid = 'new-2';
    $pane->panel = 'right_col';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => 'Latest Photos',
      'body' => '<?php
  iform_load_helpers(array(\'report_helper\'));
  $auth = report_helper::get_read_auth(variable_get(\'indicia_website_id\',\'\'), variable_get(\'indicia_password\',\'\'));
  echo report_helper::report_grid(array(
    \'id\'=>\'latest-photos\',
    \'readAuth\' => $auth,
    \'dataSource\'=>\'library/occurrence_images/occurrence_image_list\',
    \'itemsPerPage\' => 4,
    \'columns\' => array(
      array(
        \'fieldname\' => \'path\',
        \'template\' => \'<div class="gallery-img"><a class="fancybox" href="{imageFolder}{path}"><img src="{imageFolder}thumb-{path}" title="{caption}" alt="{caption}"/></a></div>\'
      )
    ),
    \'includeAllColumns\' => false,
    \'headers\' => false,
    \'galleryColCount\' => 4,
    \'extraParams\' => array(
      \'date_from\'=>\'\',
      \'date_to\'=>\'\',
      \'survey_id\'=>\'\',
      \'taxon_group_id\'=>\'\',
      \'smpattrs\'=>\'\',
      \'occattrs\'=>\'\'
    )
  ));
  report_helper::add_resource(\'defaultStylesheet\');
  handle_resources();
?>',
      'format' => '3',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $display->content['new-2'] = $pane;
    $display->panels['right_col'][0] = 'new-2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['home'] = $page;

 return $pages;

}
