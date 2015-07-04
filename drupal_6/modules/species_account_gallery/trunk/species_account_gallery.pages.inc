<?php
// $Id$

function sag_species_gallery($tid=false, $hide=false) {
  $vid = sag_get_vid();
  $load_on_demand = variable_get('sag_load_on_demand', false);
  if (!$vid) {
    return t('Before viewing the gallery, the site administrator must configure the species account gallery module');
  }
  $maxDepth = $load_on_demand ? 1 : null; 
  $tree = taxonomy_get_nested_tree($vid, $maxDepth, $tid);
  $gallery = variable_get('sag_gallery_mode', 'fancybox');
  if ($gallery==='fancybox') {
    $jsFile = drupal_get_path('module', 'iform').'/media/js/fancybox/jquery.fancybox.pack.js';
    $cssFile = drupal_get_path('module', 'iform').'/media/js/fancybox/jquery.fancybox.css';
    // file might be in libraries
    if (file_exists($_SERVER['DOCUMENT_ROOT'] . base_path() . $jsFile)) {
      drupal_add_js($jsFile);
      drupal_add_css($cssFile);
    } else {
      drupal_add_js(str_replace('/modules', '/libraries/', $jsFile));
      drupal_add_css(str_replace('/modules', '/libraries/', $cssFile));
    }
    drupal_add_js('$(document).ready(function() {
    $("a.fancybox").fancybox();
    });','inline');
  }
  drupal_add_js(drupal_get_path('module', 'species_account_gallery').'/jquery.lazyload.js');
  drupal_add_js('$(document).ready(function() {
    $("img.lazy").lazyload();
  });','inline');
  if (variable_get('sag_load_mode', 'full')==='ajax') {
    // add JS for tree loading on the fly
    drupal_add_js(drupal_get_path('module', 'species_account_gallery').'/ajaxTree.js');
    drupal_add_js(array('galleryAjaxPath'=>url('species_gallery/ajax')), 'setting');
  }
  drupal_add_css(drupal_get_path('module', 'species_account_gallery').'/stylesheets/species-account-gallery.css');
  $divId = 'species-account-gallery'.($tid ? "-$tid" : '');
  $output = '<div id="'.$divId.'">';
  if (!$hide) {    
    if ($tid) {
      // If outputting the contents of a term level, and if there is a higher taxon with a node at the current top level, 
      // we want to output it's title and body, as long as we are outputting the first level not an AJAX call for children.
      $sql = 'SELECT n.nid, n.title, nr.body '.
          'FROM {term_node} tn '.          
          'INNER JOIN {node} n on n.nid=tn.nid AND n.type=\'higher_taxon\''.
          'INNER JOIN {node_revisions} nr ON nr.nid=n.nid '.
          'WHERE tn.tid=%d';  
      if ($n = db_fetch_object(db_query($sql, $tid))) {
        if (!empty($n->body)) 
          $output .= '<fieldset class="collapsible collapsed taxon-info"><legend class="info">i</legend>'.$n->body.'</fieldset>';
        drupal_set_title($n->title);
      }
    } else {
      // no parent term, so outputting the very top level. Output the header.
      $output .= variable_get('sag_header','');
    }
    drupal_add_js('misc/collapse.js');
  }
  $output = $output.theme('gallery_tree', gallery_tree($tree), $hide);
  $output .= "</div>\n";
  if ($hide) {
    // reattach collapsible behaviour to ajax content
    $output .= "<script type=\"text/javascript\">\n";
    $output .= "Drupal.attachBehaviors($('#species-account-gallery'));\n";
    $output .= "</script>\n";
  }
  return $output;
}

function taxonomy_get_nested_tree($terms = array(), $max_depth = NULL, $parent = 0, $parents_index = array(), $depth = 0) {
  if (is_int($terms)) {
    $terms = taxonomy_get_tree($terms, $parent);
  }
  $return = array();
  foreach($terms as $term) {
    foreach($term->parents as $term_parent) {
      if ($term_parent == $parent) {
        $return[$term->tid] = $term;
      }
      else {
        $parents_index[$term_parent][$term->tid] = $term;
      }
    }
  }
  foreach($return as &$term) {
    if (isset($parents_index[$term->tid])) {
      $children = taxonomy_get_nested_tree($parents_index[$term->tid], $max_depth, $term->tid, $parents_index, $depth + 1);
      if (is_null($max_depth) || $depth < $max_depth)
        $term->children = $children;
      $term->has_children = count($children)>0;
    }
  }
  return $return;
}

function sag_tree_ajax() {
  if (!isset($_GET['tid'])) {
    echo 'Error: no term ID provided';
  } else {
    echo sag_species_gallery($_GET['tid'], true);
  }
    
}