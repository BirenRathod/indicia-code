jQuery(document).ready(function($) {
  "use strict";
  
  function changeU16() {
    if ($('#edit-profile-u16:checked').length===1) {
      $('#edit-profile-dob-wrapper').show();
    } else {
      $('#edit-profile-dob-wrapper').hide();
    }
  }
  
  $('#edit-profile-dob-wrapper').hide();
  // pseudo required
  $('#edit-profile-dob-wrapper label').html($('#edit-profile-dob-wrapper label').html() + '<span class="form-required" title="This field is required.">*</span>');
  
  // hide irrelevant years
  var dt = new Date(), yr = dt.getFullYear();
  $.each($('#edit-profile-dob-year option'), function(idx, elem) {
    if ($(elem).val()>yr || $(elem).val()<yr-16)
      $(elem).remove();
  });
  $('#edit-profile-dob-year').prepend('<option value=""></option>');
  // clear Drupal's default, which is current year (i.e. not useful!)
  if ($('#edit-profile-dob-year').val()==yr) {
    $('#edit-profile-dob-year').val(yr-16);
  }
  $('#edit-profile-u16').change(changeU16);
  changeU16();
});