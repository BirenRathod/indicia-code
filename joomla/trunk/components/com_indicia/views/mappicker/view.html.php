<?php

//defined(_JEXEC) or die('Restricted Access');
jimport('joomla.application.component.view');

class IndiciaViewMapPicker extends JView {

	function display()
	{
		$this->assign('nextUri','index.php?option=com_indicia&view=otherdata&Itemid=' .
				JRequest::getCmd('Itemid'));

		parent::display();
	}

}

?>
