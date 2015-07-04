<?php
global $mainframe;
require_once(JPATH_COMPONENT.DS.'helpers'.DS.'prefix.php');
require_once(JPATH_COMPONENT.DS.'helpers'.DS.'data_entry_helper.php');
JHTML::script('OpenLayers.js', $params->get('indicia_url').'media/js/');
JHTML::script('jquery.js', $params->get('indicia_url').'media/js/');
JHTML::script('jquery.indiciaMap.js', $params->get('indicia_url').'media/js/');
JHTML::script('jquery.indiciaMap.edit.js', $params->get('indicia_url').'media/js/');
JHTML::script('jquery.indiciaMap.edit.locationFinder.js', $params->get('indicia_url').'media/js/');
$params =& $mainframe->getPageParameters('com_indicia');
$readAuth = data_entry_helper::get_read_auth($params->get('website_id'), $params->get('password'));
?>
<script src="http://maps.google.com/maps?file=api&h1=fr&amp;v=2&amp;key=<?php echo $params->get('google_map_key'); ?>"
      type="text/javascript"></script>
<h1><?php echo JText::_('Location Details'); ?></h1>
<p><?php echo JText::_('Location Intro'); ?></p>
<form class="indicia" method="POST" action="<?php echo $this->nextUri; ?>" >
<fieldset><legend><?php echo JText::_('Locality'); ?></legend>
<label for="location_name"><?php echo JText::_('Description of locality'); ?>:</label>
<input name="location_name" class="wide" value="<?php echo data_entry_helper::get_from_session('location_name'); ?>" /><br />
<div id="map"></div>
<br/>
<input class="auto" type="submit" value="<?php echo JText::_('Next'); ?>" />
</fieldset>
</form>
<?php
require_once(JPATH_COMPONENT.DS.'helpers'.DS.'suffix.php');

// Find the user's language, or the component default
$user = JFactory::getUser();
if ($user->id==0) {
	// Not logged in, so use default in component parameters
	$lang_id = $params->get('language_id');
} else {
	$lang=JFactory::getLanguage();
	$lang_id=$lang->get('tag');
}
?>

<script type="text/javascript" language="javascript">

jQuery(document).ready(function() {
	<?php if ($params->get('google_map_key')) : ?>
	var base_layers = [ 'google_physical', 'google_satellite' ];
	<?php else: ?>
	base_layers = [ 'virtual_earth' ];
	<?php endif; ?>
	jQuery('#map').indiciaMap({
		indiciaSvc : "<?php echo $params->get('indicia_url'); ?>",
		indiciaGeoSvc : "<?php echo $params->get('geoserver_url'); ?>",
		presetLayers : base_layers,
		initial_zoom: <?php echo $params->get('init_zoom'); ?>,
		initial_long: <?php echo $params->get('init_x'); ?>,
		initial_lat: <?php echo $params->get('init_y'); ?>,
		scroll_wheel_zoom: false,
		width: "600px",
		height: "400px"
	}).indiciaMapEdit({
		systems: {2169: "<?php echo JText::_('EPSG_2169'); ?>", 4326 : "<?php echo JText::_('EPSG_4326'); ?>"},
		label_spatial_ref: "<?php echo JText::_('Spatial Reference'); ?>",
		label_system: "<?php echo JText::_('Spatial Reference System'); ?>"
	}).locationFinder({
		apiKey: "<?php echo $params->get('geoplanet_api_key'); ?>",
		preferredArea: "<?php echo $params->get('pref_area'); ?>",
		country: "<?php echo $params->get('country'); ?>",
		lang: "<?php echo $lang_id; ?>"
	});
});

</script>