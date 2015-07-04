<?php

/**
 * @file
 * Page callbacks for the Appcache module.
 */

/**
 * Render the page used to indicate that an internet connection is required.
 */
function appcache_offline() {
  drupal_maintenance_theme();
  drupal_set_title(t('Connect to the internet to continue'));
  $offline_page = array(
    'content' => t('An internet connection is required to continue. Please connect to the internet and <a href="@front">try again</a>.', array('@front' => url('<front>'))),
  );

  return theme('maintenance_page', $offline_page);
}

