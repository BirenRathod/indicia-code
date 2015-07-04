jQuery.expr[':'].Contains = function(a,i,m){
    return jQuery(a).text().toUpperCase().indexOf(m[3].toUpperCase())>=0;
};


$(document).ready(function() {
  // Show or hide the list items that match the search keys
  $('#library-search').keyup(function(evt) {
    if ($(evt.target).val().trim().length===0) {
      $('#library-form-list li').show();
    } else {
      $('#library-form-list li').not('Contains('+$(evt.target).val() +')').hide();
      $('#library-form-list li:Contains('+evt.target.value+')').show();
    }
  });
  
  function set_visibility() {
    if ($('#organise-favourites').hasClass('button-active')) {
      $('#library-form-list li').not('.selected').removeClass('hidden');
      $('#library-form-list button').show();
    } else {
      $('#library-form-list li').not('.selected').addClass('hidden');
      $('#library-form-list button').hide();
    }
  }
  
  $('#organise-favourites').click(function() {
    $('#organise-favourites').toggleClass('button-active');
    set_visibility();
  });
  
  $('#library-form-list button').click(function(evt) {
    // are we adding or removing?
    var fav = ($(evt.target).parents('li:first').hasClass('selected')) ? 0 : 1;
    $.get(indiciaData.ajaxUrl, 
      {"nid": evt.target.id.substring(4), "favourite":fav},
      function() {
        if (fav===1) {
          $(evt.target).parents('li:first').addClass('selected');
          $(evt.target).html(indiciaData.removeCaption);
        } else {
          $(evt.target).parents('li:first').removeClass('selected');
          $(evt.target).html(indiciaData.addCaption);
        }
      }
    );
  });
  
  set_visibility();
});