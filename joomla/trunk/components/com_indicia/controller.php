<?php
JHTML::_('script', 'openid.js');

defined('_JEXEC') or die ('Restricted access');
jimport('joomla.application.component.controller');
jimport( 'joomla.methods' );
require_once(JPATH_COMPONENT.DS.'helpers'.DS.'data_entry_helper.php');

class IndiciaController extends JController {

	function display()
	{
		global $mainframe;
		// Perform session storage of post data
		if (JRequest::getCmd('view')=='speciespicker') {
			// The first page of the wizard should reset the indicia session data
			data_entry_helper::clear_session();
		}
		elseif (JRequest::getCmd('view')=='mappicker' || JRequest::getCmd('view')=='otherdata'
				|| JRequest::getCmd('view')=='save') {
			// other data entry pages should dump the $_POST data into the Session so that it can persist
			// across pages of the wizard.
			data_entry_helper::add_post_to_session();
		}

		// Perform some basic mandatory field checks on the entered data, and redirect to pages if required data is missing
		if (JRequest::getCmd('view')!='speciespicker' && JRequest::getCmd('view')!='map' && !$_SESSION['indicia:taxa_taxon_list_id']) {
			$mainframe->redirect( 'index.php?option=com_indicia&view=speciespicker&Itemid='.JRequest::getCmd('Itemid'),
				JText::_('Before proceeding, please specify the species.') );
		}
		elseif (JRequest::getCmd('view')=='otherdata') {
			if (!$_SESSION['indicia:entered_sref'] || !$_SESSION['indicia:entered_sref_system']) {
				$mainframe->redirect( 'index.php?option=com_indicia&view=mappicker&Itemid='.JRequest::getCmd('Itemid'),
						JText::_('Before proceeding, please specify the location by clicking on the map.'));
			}
		}
		elseif (JRequest::getCmd('view')=='save') {
			if (!$_SESSION['indicia:date'] || $_SESSION['indicia:date']=='click here') {
				$mainframe->redirect( 'index.php?option=com_indicia&view=otherdata&Itemid='.JRequest::getCmd('Itemid'),
						JText::_('Before proceeding, please specify the date of the observation.') );
			}
		}
		parent::display();

	}

}

?>
