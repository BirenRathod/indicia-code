<?php

/**
 * Implementation of hook_uuid_features_default_content().
 */
function registration_terms_of_use_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'type' => 'page',
  'language' => '',
  'uid' => '1',
  'status' => '1',
  'comment' => '0',
  'promote' => '0',
  'moderate' => '0',
  'sticky' => '0',
  'tnid' => '0',
  'translate' => '0',
  'title' => 'Terms of Use',
  'body' => 'By using this web site, you agree to these Terms. If you do not agree, do not use the site. We may need to change these Terms of Use from time to time. If you disagree with a change to the Terms, do not use the site.

When you use this web site, you create and upload content - for instance, wildlife observations, photos of nature, your descriptions of it, and messages to the forums. By putting this information on the site, you are saying that:
(a) the content is yours, or you have the permission of the owner to agree to this usage, and
(b) you agree for us to use it on the site and for any other educational and non-commercial use.

We will supply the wildlife observations collected through this site to local record centres, schemes and societies that have a non-commercial interest in the data. Verified observations will be made available to the NBN Gateway. If you do not want your observations to be made available in this way please do not submit them.
',
  'teaser' => 'By using this web site, you agree to these Terms. If you do not agree, do not use the site. We may need to change these Terms of Use from time to time. If you disagree with a change to the Terms, do not use the site.

When you use this web site, you create and upload content - for instance, wildlife observations, photos of nature, your descriptions of it, and messages to the forums. By putting this information on the site, you are saying that:
(a) the content is yours, or you have the permission of the owner to agree to this usage, and',
  'log' => '',
  'format' => '1',
  'name' => 'admin',
  'picture' => '',
  'data' => 'a:0:{}',
  'path' => 'terms_of_use',
  'taxonomy' => array(),
  'uuid' => '682dd184-bac2-11e0-aa82-1f3dd472bc58',
  'pathauto_perform_alias' => FALSE,
);
  return $nodes;
}
