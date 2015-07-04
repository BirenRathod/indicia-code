<?php

//defined(_JEXEC) or die('Restricted Access');
jimport('joomla.application.component.view');

class IndiciaViewSpeciespicker extends JView {

	function display()
	{
		global $mainframe;
		require_once(JPATH_COMPONENT.DS.'helpers'.DS.'prefix.php');
		require_once(JPATH_COMPONENT.DS.'helpers'.DS.'data_entry_helper.php');
		$params =& $mainframe->getPageParameters('com_indicia');
		$readAuth = data_entry_helper::get_read_auth($params->get('website_id'), $params->get('password'));
		switch ($params->get('taxon_selector')) {
			case 'auto':
				$species_picker = data_entry_helper::autocomplete('taxa_taxon_list_id', 'taxa_taxon_list', 'taxon', 'id',
					$readAuth + array('taxon_list_id' => $params->get('taxon_list_id')));
				break;
			case 'tree':
				$species_picker = 'Not implemented';
				break;
			case 'list':
				$species_picker = '<div class="imagelist">'.
					data_entry_helper::list_in_template(
					'taxa_taxon_list', $readAuth + array('taxon_list_id' => $params->get('taxon_list_id'), 'preferred' => 't', 'view' => 'details'),
					'<div class="imagebox">
					<input id="species|id|" name="taxa_taxon_list_id" type="radio" value="|id|" class="species_radio"/>
					<a>
					<img src="'. $params->get('indicia_url').'upload/|image_path|" width="100" height="150" /><br />
					<em>|taxon|</em>
					</a>
					</div>').'</div>';
				break;
			default:
				$species_picker = 'Picker type not recognised';
		}
		$this->assign('species_picker', $species_picker);
		$this->assign('nextUri','index.php?option=com_indicia&view=mappicker&Itemid=' .
				JRequest::getCmd('Itemid'));
		parent::display();
		require_once(JPATH_COMPONENT.DS.'helpers'.DS.'suffix.php');
	}
}