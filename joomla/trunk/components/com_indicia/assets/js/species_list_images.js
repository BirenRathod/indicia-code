// This converts a bunch of radio buttons into a set of picture divs that can be clicked.
jQuery(document).ready(function() {
	jQuery('.species_radio').hide();
	jQuery('.imagebox a').click(function() {
    	jQuery(this).prev().attr('checked', true);
    	jQuery(this).parent().css('background-color', '#ffffaa');
    	jQuery(this).parent().siblings().css('background-color', '#ededed');
	});
});