<?php
require_once(JPATH_COMPONENT.DS.'helpers'.DS.'data_entry_helper.php');
$params =& $mainframe->getPageParameters('com_indicia');
JHTML::stylesheet('ui.datepicker.css', $path=$params->get('indicia_url').'/media/css/');
JHTML::script('ui.datepicker.js', $path=$params->get('indicia_url').'/media/js/');
$readAuth = data_entry_helper::get_read_auth($params->get('website_id'), $params->get('password'));
?>
<h1><?php echo JText::_('Other Information'); ?></h1>
<p><?php echo JText::_('Please enter additional info'); ?></p>
<form class="indicia" method="POST" action="<?php echo $this->nextUri; ?>" >
<fieldset>
<?php echo data_entry_helper::get_auth($params->get('website_id'), $params->get('password')); ?>
<input class="auto" type='hidden' id='website_id' name='website_id' value='<?php echo $params->get('website_id'); ?>' />
<label for="date"><?php echo JText::_('Date'); ?>:</label>
<?php echo data_entry_helper::date_picker('date', data_entry_helper::get_from_session('date', JText::_('click here'))); ?>
<br />
<?php
$user = JFactory::getUser();
if ($user->id==0) : ?>
<label for="recorder_names"><?php echo JText::_('Name of Recorder'); ?>:</label>
<input type="text" name="recorder_names" id="recorder_names" value="<?php echo data_entry_helper::get_from_session('recorder_names'); ?>" />
<br/>
<?php else : ?>
<input type="hidden" class="hidden" name="recorder_names" id="recorder_names" value="<?php echo $user->name ?>" />
<?php endif; ?>
<?php
if ($survey_id=$params->get('survey_id')) : ?>
<input type='hidden' class="hidden" id='survey_id' name='survey_id' value='<?php echo $survey_id; ?>'/>
<?php else : ?>
<label for="survey_id"><?php echo JText::_('Survey'); ?>:</label>
<?php echo data_entry_helper::select('survey_id', 'survey', 'title', 'id', $readAuth,
	data_entry_helper::get_from_session('survey_id')); ?>
<br />
<?php endif; ?>
<label for='comment'><?php echo JText::_('Comment'); ?>:</label>
<textarea id='comment' name='comment'><?php echo data_entry_helper::get_from_session('comment'); ?></textarea>
<br />
<?php
$attrs = explode('\l\n', $params->get('custom_attributes'));
foreach($attrs as $attr) {
	// $attr should be of form label|attr id|type|type specific params
	$tokens = explode('|', $attr);
	if ($tokens[2]='radio_group') {
		echo '<label for="'.$tokens[1].'">'.JText::_($tokens[0]).':</label><div>';
		echo data_entry_helper::radio_group($tokens[1], 'termlists_term', 'term', 'id',
				$readAuth + array('termlist_id' => $tokens[3]), '<br/>',
				data_entry_helper::get_from_session($tokens[1]));
		echo "</div>";
	}
	elseif ($tokens[2]='select') {
		echo '<label for="'.$tokens[1].'">'.JText::_($tokens[0]).':</label>';
		echo data_entry_helper::select($tokens[1], 'termlists_term', 'term', 'id',
				$readAuth + array('termlist_id' => $tokens[3]),
				data_entry_helper::get_from_session($tokens[1]));
		echo '<br/>';
	}
}
?>
<br/>
<input class="auto" type="submit" value="<?php echo JText::_('Save Record'); ?>"/>
</fieldset>
</form>