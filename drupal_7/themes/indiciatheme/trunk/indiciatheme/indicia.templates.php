<?php
global $indicia_templates;
$indicia_templates['controlWrap'] = "<div id=\"ctrl-wrap-{id}\" class=\"ctrl-wrap\">{control}</div>\n";
$indicia_templates['suffix'] = " \n";
$indicia_templates['requiredsuffix'] = '<span class="deh-required">*</span>'."\n";
$indicia_templates['two-col-50'] = '<div class="at-panel panel-display two-50 clearfix">' .
    '<div class="region region-two-50-first"><div class="region-inner clearfix">{col-1}</div></div>' .
    '<div class="region region-two-50-second"><div class="region-inner clearfix">{col-2}</div></div>' .
'</div>';