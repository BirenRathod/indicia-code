$(document).ready(function() {
  
  function enable_site_settings() {
    var enable=$('#edit-field-summary-report-grouping-value-region').attr('checked');
    if (enable) {
      $('#edit-field-summary-report-display-value-map-wrapper').show();
      $('.group-site-settings').show();
    } else {
      $('#edit-field-summary-report-display-value-map-wrapper').hide();
      // ensure option is not checked as invalid
      $('#edit-field-summary-report-display-value-map').attr('checked', false);
      $('.group-site-settings').hide();
    }
  }

  function enable_map_settings() {
    var enable=$('#edit-field-summary-report-display-value-map').attr('checked');
    if (enable) {
      $('.group-map-settings').show();
    } else {
      $('.group-map-settings').hide();
    }
  }

  $('input[name="field_summary_report_grouping[value]"]').change(enable_site_settings);

  $('input[name="field_summary_report_display[value]"]').change(enable_map_settings);

  // set the initial state
  enable_site_settings();
  enable_map_settings()

});