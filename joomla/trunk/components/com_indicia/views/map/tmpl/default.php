<?php
global $mainframe;
$params =& $mainframe->getPageParameters('com_indicia');
JHTML::script('OpenLayers.js', $params->get('indicia_url').'media/js/');
JHTML::script('jquery.js', $params->get('indicia_url').'media/js/');
JHTML::script('jquery.indiciaMap.js', $params->get('indicia_url').'media/js/');
// The map uses Google if there is an API key, otherwise reverts to virtual earth
if ($params->get('google_map_key')) {
	JHTML::script('?file=api&v=2&key='.$params->get('google_map_key'), 'http://maps.google.com/');
} else {
	JHTML::script('mapcontrol.ashx?v=6.1', 'http://dev.virtualearth.net/mapcontrol/');
}


if ($params->get('geoserver_url')) {
	echo "<h2>".JText::_('Distribution Map')."</h2>";
	// request the species name and image from the data services
	$url = $params->get('indicia_url')."index.php/services/data";
	if (array_key_exists('taxa_taxon_list_id', $_GET)) {
		$request="$url/taxa_taxon_list?mode=json&id=".$_GET['taxa_taxon_list_id'];
		$readAuth=data_entry_helper::get_read_auth($params->get('website_id'), $params->get('password'));
		$request .= "&nonce=".$readAuth['nonce']."&auth_token=".$readAuth['auth_token'];
		$session=curl_init($request);
		curl_setopt($session, CURLOPT_RETURNTRANSFER, true);
		$taxon = json_decode(array_pop(explode("\r\n\r\n",curl_exec($session))), true);
		// We only want the first entry in the list, as there should be only one.
		$taxon=$taxon[0];
		echo "<p>".JText::_($params->get('map_intro')).' '.JText::sprintf($params->get('filtered_by_taxon'), $taxon['taxon'])."</p>";
	} else {
		echo "<p>".JText::_($params->get('map_intro'));
	}
}
?>
<script type="text/javascript" language="javascript">

jQuery(document).ready(function() {
	<?php if ($params->get('google_map_key')) : ?>
	var base_layers = [ 'google_physical', 'google_satellite' ];
	<?php else: ?>
	base_layers = [ 'virtual_earth' ];
	<?php endif; ?>
	var vector = new OpenLayers.Layer.Vector('Drawing Layer');
	<?php if (array_key_exists('taxa_taxon_list_id', $_GET)) : ?>
		var otherSpecies = new OpenLayers.Layer.WMS(
		  	'Occurrences',
		  	'<?php echo $params->get('geoserver_url'); ?>wms',
			{
				layers: '<?php echo $params->get('map_feature_type'); ?>', transparent: true,
				styles: 'distribution_point',
				filter: '<ogc:Filter xmlns:gml=\"http://www.opengis.net/gml\" xmlns:ogc=\"http://www.opengis.net/ogc\">' +
					'<ogc:PropertyIsNotEqualTo><ogc:PropertyName>taxa_taxon_list_id</ogc:PropertyName>' +
					'<ogc:Literal><?php echo $_GET['taxa_taxon_list_id']; ?></ogc:Literal>' +
					'</ogc:PropertyIsNotEqualTo></ogc:Filter>'
			}, { isBaseLayer: false, sphericalMercator: true});
		var thisSpecies = new OpenLayers.Layer.WMS(
		  	'Occurrences of <?php echo $taxon['taxon']; ?>',
		  	'<?php echo $params->get('geoserver_url'); ?>wms',
			{
				layers: '<?php echo $params->get('map_feature_type'); ?>', transparent: true,
				filter: '<ogc:Filter xmlns:gml=\"http://www.opengis.net/gml\" xmlns:ogc=\"http://www.opengis.net/ogc\">' +
					'<ogc:PropertyIsEqualTo><ogc:PropertyName>taxa_taxon_list_id</ogc:PropertyName>' +
					'<ogc:Literal><?php echo $_GET['taxa_taxon_list_id']; ?></ogc:Literal>' +
					'</ogc:PropertyIsEqualTo></ogc:Filter>'
			}, { isBaseLayer: false, sphericalMercator: true});
		var customLayers = [vector, otherSpecies, thisSpecies];
	<?php else : ?>
		var allSpecies = new OpenLayers.Layer.WMS(
		  	'Occurrences',
		  	'<?php echo $params->get('geoserver_url'); ?>wms',
			{
				layers: '<?php echo $params->get('map_feature_type'); ?>', transparent: true
			}, { isBaseLayer: false, sphericalMercator: true});
		var customLayers = [vector, allSpecies];
	<?php endif; ?>
	var drawControl = new OpenLayers.Control.DrawFeature(vector, OpenLayers.Handler.Polygon);
	jQuery('#map').indiciaMap({
		indiciaSvc : "<?php echo $params->get('indicia_url'); ?>",
		indiciaGeoSvc : "<?php echo $params->get('geoserver_url'); ?>",
		presetLayers : base_layers,
		initial_zoom: <?php echo $params->get('init_zoom'); ?>,
		initial_long: <?php echo $params->get('init_x'); ?>,
		initial_lat: <?php echo $params->get('init_y'); ?>,
		width: "600px",
		height: "600px",
		layers: customLayers,
		controls: []
	});
});
</script>
<div id="map"></div>