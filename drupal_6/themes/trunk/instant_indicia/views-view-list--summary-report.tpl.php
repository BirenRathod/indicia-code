<?php
// $Id: views-view-list.tpl.php,v 1.3 2008/09/30 19:47:11 merlinofchaos Exp $
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<div class="item-list">
  <?php if (!empty($title)) : ?>
    <h3><?php 
  switch ($title) {
    case 'On a map':
      print t('Maps');
      break;
    case 'On a pie chart':
      print t('Pie Charts');
      break;
    case 'On a bar graph':
      print t('Graphs');
      break;
    case 'As a table of data':
      print t('Data tables');
      break;
    default:
      print $title;
  }
  ?></h3>
  <?php endif; ?>
  <<?php print $options['type']; ?>>
    <?php foreach ($rows as $id => $row): ?>
      <li class="<?php print $classes[$id]; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
  </<?php print $options['type']; ?>>
</div>