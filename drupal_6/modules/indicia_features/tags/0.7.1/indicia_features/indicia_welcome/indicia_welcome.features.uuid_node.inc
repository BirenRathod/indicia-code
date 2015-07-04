<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function indicia_welcome_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'type' => 'story',
  'language' => '',
  'uid' => '1',
  'status' => '1',
  'comment' => '2',
  'promote' => '1',
  'moderate' => '0',
  'sticky' => '0',
  'tnid' => '0',
  'translate' => '0',
  'title' => 'Instant Indicia Installed',
  'body' => '<?php 
  $uid= db_fetch_object(db_query("select nid from {uuid_node} where uuid=\'dec4465b-bcf4-11e0-b59d-7b3ab1cadf00\'"));
?>
<p>
	Welcome to your new Instant Indicia website. This website is ready for you to setup online recording. This news article is a temporary page designed to help you get started and can be removed when your site is ready. Instant Indicia lets you choose from a number of ready made <em>features</em> to enable on your site, ranging from simple reports or data input forms to complete site modules.</p>
<ul>
	<li>
		<a href="admin/build/features">Select which features you want on your website.</a></li>
	<li>
		<a href="admin/settings/iform/settings">Change Indicia configuration settings for your website.</a></li>
	<li>
		<a href="admin/settings/iform/diagnostics">Perform some diagnostic tests to ensure your connection to the Warehouse works.</a></li>
	<li>
		<a href="node/<?php echo $uid->nid; ?>/delete">Remove this news story.</a></li>
</ul>
',
  'teaser' => '<?php 
  $uid= db_fetch_object(db_query("select nid from {uuid_node} where uuid=\'dec4465b-bcf4-11e0-b59d-7b3ab1cadf00\'"));
?>
<p>
	Welcome to your new Instant Indicia website. This website is ready for you to setup online recording. This home page is a temporary page designed to help you get started and can be replaced when your site is ready. Instant Indicia lets you choose from a number of ready made <em>features</em> to enable on your site, ranging from simple reports or data input forms to complete site modules.</p>
<ul>
	<li>
		<a href="admin/build/features">Select which features you want on your website.</a></li>
	<li>
		<a href="admin/settings/iform/settings">Change Indicia configuration settings for your website.</a></li>
	<li>
		<a href="admin/settings/iform/diagnostics">Perform some diagnostic tests to ensure your connection to the Warehouse works.</a></li>
	<li>
		<a href="node/<?php echo $uid->nid; ?>/delete">Remove this news story.</a></li>
</ul>
',
  'log' => '',
  'format' => '3',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'taxonomy' => array(),
  'uuid' => 'dec4465b-bcf4-11e0-b59d-7b3ab1cadf00',
);
  return $nodes;
}
