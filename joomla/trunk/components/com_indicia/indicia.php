<?php

// no direct access
defined( '_JEXEC' ) or die( 'Restricted access' );

// find controller path
$path = JPATH_COMPONENT.DS.'controller.php';
jimport('joomla.filesystem.file');
if (JFile::exists($path))
{
	require_once($path);
}
else
{
	JError::raiseError('500', JText::_('Unknown controller '.$path));
}
// instantiate the controller
$controller = new IndiciaController;
// run the controller
$controller->execute(JRequest::getCmd('task', 'display'));
$controller->redirect();



?>