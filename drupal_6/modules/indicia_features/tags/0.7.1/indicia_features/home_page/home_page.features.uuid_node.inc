<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function home_page_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'type' => 'story',
  'language' => '',
  'uid' => '1',
  'status' => '1',
  'comment' => '2',
  'promote' => '1',
  'moderate' => '0',
  'sticky' => '1',
  'tnid' => '0',
  'translate' => '0',
  'title' => 'Introduction',
  'body' => '<?php 
  $uid= db_fetch_object(db_query("select nid from {uuid_node} where uuid=\'08bc3d8d-bcfd-11e0-b59d-7b3ab1cadf00\'"));
?>
<p>
	Welcome to your home page. You can <a href="<?php echo url(\'node/\'.$uid->nid.\'/edit\'); ?>">edit this content</a>. Because it is marked as sticky, it will always appear on the home page.</p>
',
  'teaser' => '<?php 
  $uid= db_fetch_object(db_query("select nid from {uuid_node} where uuid=\'08bc3d8d-bcfd-11e0-b59d-7b3ab1cadf00\'"));
?>
<p>
	Welcome to your home page. You can <a href="<?php echo url(\'node/\'.$uid->nid.\'/edit\'); ?>">edit this content</a>. Because it is marked as sticky, it will always appear on the home page.</p>
',
  'log' => '',
  'format' => '3',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'taxonomy' => array(),
  'uuid' => '08bc3d8d-bcfd-11e0-b59d-7b3ab1cadf00',
);
  return $nodes;
}
