<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function species_accounts_taxonomy_default_vocabularies() {
  return array(
    'taxonomic_hierarchy' => array(
      'name' => 'Taxonomic hierarchy',
      'description' => '',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '1',
      'tags' => '0',
      'module' => 'features_taxonomic_hierarchy',
      'weight' => '0',
      'nodes' => array(
        'species_account' => 'species_account',
        'image' => 'image'
      ),
    ),
  );
}
