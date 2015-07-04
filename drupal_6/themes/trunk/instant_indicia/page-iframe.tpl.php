<?php
// $Id: page.tpl.php,v 1.4 2009/07/13 23:52:58 andregriffin Exp $
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
  "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" >
  <head>
    <title><?php print $head_title ?></title>
    <?php print $head ?>
    <?php print $styles ?>
    <?php print $scripts ?>
    <!--[if lte IE 7]><?php print framework_get_ie_styles(); ?><![endif]--> <!--If Less Than or Equal (lte) to IE 7-->
  </head>
  <body<?php print framework_body_class($left, $right); ?>>
    <!-- Layout -->
    <div class="container"> <!-- add "showgrid" class to display grid -->
  
      <?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block"><ul class="tabs primary">'. $tabs .'</ul>'; endif; ?>
      <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
      <?php if ($tabs): print '<span class="clear"></span></div>'; endif; ?>
      <?php if ($show_messages && $messages): print $messages; endif; ?>
      <?php print $help; ?>
      <?php print $content ?>

    </div> <!-- /.container -->
    <!-- /layout -->

  <?php print $closure ?>

  </body>
</html>