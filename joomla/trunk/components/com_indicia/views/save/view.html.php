<?php

//defined(_JEXEC) or die('Restricted Access');
jimport('joomla.application.component.view');

class IndiciaViewSave extends JView {

	/**
	 * Builds a submission and submits it to the data services to store a sample and occurrence.
	 * If successful, redirects to the acknolwedge page, otherwise displays the default template
	 * which is the error message.
	 */
	function display()
	{
		global $mainframe;
		$params =& $mainframe->getPageParameters('com_indicia');
		require_once(JPATH_COMPONENT.DS.'helpers'.DS.'data_entry_helper.php');

		// Build a submission with all the data stored in the PHP session
		$data = data_entry_helper::extract_session_array();
		$sampleMod = data_entry_helper::wrap($data, 'sample');
		$occurrenceMod = data_entry_helper::wrap($data, 'occurrence');
		$occurrenceMod['superModels'][] = array(
			'fkId' => 'sample_id',
			'model' => $sampleMod
			);
		$submission = array('submission' => array('entries' => array(
			array ( 'model' => $occurrenceMod )
		)));
		// try to save the submission
		$response = data_entry_helper::forward_post_to('save', $submission);
		if (array_key_exists('success', $response)) {
			// Redirect to the success acknowledgement page if the response is good.
			$mainframe->redirect( 'index.php?option=com_indicia&view=map&taxa_taxon_list_id='.$data['taxa_taxon_list_id'].'&Itemid='.JRequest::getCmd('Itemid'),
							JText::_($params->get('thank_you')));
		}
		else
		{
			// Allow default output of this view, which is to display an error.
			$this->assign('response', $response);
			parent::display();
		}
	}

}

?>
