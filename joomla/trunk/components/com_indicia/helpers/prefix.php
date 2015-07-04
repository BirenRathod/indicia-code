<?php
$params =& $mainframe->getPageParameters('com_indicia');
$media = $params->get('indicia_url').'media';
// Add stuff to the header that virtually all our pages require
JHTML::stylesheet('jquery.autocomplete.css', $path="$media/css/");
JHTML::stylesheet('styles.css', $path=JURI::base().'components/com_indicia/assets/css/');
JHTML::script('jquery.js', $path="$media/js/");
JHTML::script('ui.core.js', $path="$media/js/");
JHTML::script('jquery.autocomplete.js', $path="$media/js/");
JHTML::script('json2.js', $path="$media/js/");
?>

