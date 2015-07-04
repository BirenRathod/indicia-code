<?php

/**
 * Build and return the HTML5 Application Manifest for this site.
 */
function appcache_manifest() {
  $manifest = array();

  $manifest['header'] = "CACHE MANIFEST";

  // Cache the version of the manifest file, so that browsers will refresh their
  // caches of offline resources when Drupal's cache is cleared.
  $cached_version = cache_get('appcache_version');
  if (!$cached_version) {
    $version = REQUEST_TIME;
    cache_set('appcache_version', $version, 'cache', CACHE_TEMPORARY);
  }
  else {
    $version = $cached_version->data;
  }
  $manifest['version'] = "# " . $version . "\n";

  if (variable_get('appcache_automatic', FALSE)) {
    $network = array("*\n");
  }
  else {
    // Invoke hooks to insert or alter resources.
    $fallback = module_invoke_all('appcache_fallback');
    $network = module_invoke_all('appcache_network');
    $cache = module_invoke_all('appcache_cache');
    $cache_query = module_invoke_all('appcache_cache_query');
    
    drupal_alter('appcache_fallback', $fallback);
    drupal_alter('appcache_network', $network);
    drupal_alter('appcache_cache', $cache);
    drupal_alter('appcache_cache_query', $cache_query);
  }

  // If no fallback is set, create one.
  if (empty($fallback)) {
    $fallback = array("/ " . url('appcache-offline') . "\n");
  }

  $manifest['fallback'] = "FALLBACK:\n" . implode("\n", $fallback);

  if (!empty($network)) {
    $manifest['network'] = "NETWORK:\n" . implode("\n", $network);
  }
  if (!empty($cache)) {
    $manifest['cache'] = "CACHE:\n" . implode("\n", $cache);
    
    if(!empty($cache_query)){

      //automatic update to CSS and JS query string for cache management
      //iterates through CACHE list until finds an empty line
      $default_query_string = variable_get('css_js_query_string', 0);
    
      foreach ($cache_query as &$line){
        if (!empty($line)){
         //apply only to JS and CSS  
         if(preg_match('/\.(js|JS|css|CSS)$/', $line)){
          $line = trim($line) . '?' . $default_query_string;
         }
       } else {
         break;
       }
      }
      $manifest['cache'] .= "\n" . implode("\n", $cache_query);
    }
  }

  return implode("\n", $manifest) . "\n";
}

/**
 * Validate a HTML 5 Application Cache Manifest.
 *
 * By default, this function will validate using the service hosted at
 * manifest-validator.com. The validator itself is licensed under the MIT
 * license, and uses node.js. Set the "appcache_validate_endpoint" variable
 * to point at your own instance of the validator, or set it to FALSE to
 * disable manifest validation entirely.
 *
 * @see appcache_requirements()
 *
 * @param $manifest
 *   Optional parameter containing a string of the manifest to validate. By
 *   default, the return of appcache_manifest() is validated.
 *
 * @return
 *   A result array from manifest-validator.com containing an 'isValid'
 *   boolean and an array of error messages keyed by line number, containing
 *   the error and the line content as array keys. If validation is disabled,
 *   FALSE is returned.
 */
function appcache_manifest_validate($manifest = NULL) {
  if (!$endpoint = variable_get("appcache_validate_endpoint", "http://manifest-validator.com/api/validate")) {
    return FALSE;
  }

  $params = array(
    'directinput' => (!empty($manifest) ? $manifest: appcache_manifest()),
  );

  $options = array(
    'method' => 'POST',
    'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
    'data' => http_build_query($params),
  );

  $response = drupal_http_request($endpoint, $options);

  return drupal_json_decode($response->data);
}

