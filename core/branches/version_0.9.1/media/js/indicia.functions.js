/**
 * Indicia, the OPAL Online Recording Toolkit.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/gpl.html.
 */

/**
 * File containing general purpose JavaScript functions for Indicia.
 */
if (typeof window.indiciaData==="undefined") {
  window.indiciaData = {
    onloadFns: [],
    idDiffRuleMessages: {}
  };
  window.indiciaFns = {};
}

(function ($) {
  "use strict";

  /**
   * Enable buttons hover Effect. Since jQuery 1.7 the 'live' function has been
   * deprecated and 'on' function should be used. Use this function to allow
   * non-version specific code.
   */
  indiciaFns.enableHoverEffect = function(){
      var version=$.fn.jquery.split('.'),
          funcname=(version[0]==='1' && version[1]<7) ? 'live' : 'on';

      $('.ui-state-default')[funcname]('mouseover', function() {
          $(this).addClass('ui-state-hover');
      });
      $('.ui-state-default')[funcname]('mouseout', function() {
          $(this).removeClass('ui-state-hover');
      });
  };
  
  /**
   * Method to attach to the hover event of an id difficulty warning icon. The icon should have 
   * data-rule and data-diff attributes, pointing to to the rule ID and id difficulty level
   * respectively.
   */
  indiciaFns.hoverIdDiffIcon = function(e) {
    if ($(e.currentTarget).attr('title')==='') {
      // Hovering over an ID difficulty marker, so load up the message hint. We load the whole 
      // lot for this rule, to save multiple service hits. So check if we've loaded this rule already
      if (typeof indiciaData.idDiffRuleMessages['rule'+$(e.currentTarget).attr('data-rule')]==="undefined") {
        $.ajax({
          dataType: "jsonp",
          url: indiciaData.read.url+'index.php/services/data/verification_rule_datum',
          data: {"verification_rule_id":$(e.currentTarget).attr('data-rule'), "header_name":"INI",
            "auth_token":indiciaData.read.auth_token, "nonce":indiciaData.read.nonce},
          success: function(data) {
            indiciaData.idDiffRuleMessages['rule'+$(e.currentTarget).attr('data-rule')]={};
            $.each(data, function(idx, msg) {
              indiciaData.idDiffRuleMessages['rule'+$(e.currentTarget).attr('data-rule')]
                  ['diff'+msg.key] = msg.value;
            });
            $(e.currentTarget).attr('title', indiciaData.idDiffRuleMessages['rule'+$(e.currentTarget).attr('data-rule')]
                ['diff'+$(e.currentTarget).attr('data-diff')]);
          },
          error: function() {
            // put a default in place.
            $(e.currentTarget).attr('title', 'Caution, identification difficulty level ' + $(e.currentTarget).attr('data-rule') + ' out of 5');
          }
        });
      } else {
        $(e.currentTarget).attr('title', indiciaData.idDiffRuleMessages['rule'+$(e.currentTarget).attr('data-rule')]
                  ['diff'+$(e.currentTarget).attr('data-diff')]);
      }
    }
  };
  
  /** 
   * jQuery UI 1.10 replaced option.selected with option.active. Use this function to allow non-version specific
   * code.
   */
  indiciaFns.activeTab = function(tabs, index) {
    var version=$.ui.version.split('.'), 
        propname;
    // behaviour differs if getting or setting the tab index and changes at jQuery UI 1.10.
    if (typeof index==="undefined" && version[0]==='1' && version[1]<10) {
      return tabs.tabs('option', 'selected');
    } else if (typeof index==="undefined") {
      return tabs.tabs('option', 'active');
    } else if (version[0]==='1' && version[1]<10) {
      return tabs.tabs('select', index);
    } else {
      return tabs.tabs('option', 'active', index);
    }
  };
  
  /** 
   * jQuery UI 1.10 replaced the show event with activate. Use this function to allow non-version specific
   * code to bind to this event
   */
  indiciaFns.bindTabsActivate = function(tabs, fn) {
    var version=$.ui.version.split('.'), 
        evtname=(version[0]==='1' && version[1]<10) ? 'tabsshow' : 'tabsactivate';
    return tabs.bind(evtname, fn);
  };
  
  /** 
   * jQuery UI 1.10 replaced the show event with activate. Use this function to allow non-version specific
   * code to unbind from this event
   */
  indiciaFns.unbindTabsActivate = function(tabs, fn) {
    var version=$.ui.version.split('.'), 
        evtname=(version[0]==='1' && version[1]<10) ? 'tabsshow' : 'tabsactivate';
    return tabs.unbind(evtname, fn);
  };
  
  /** 
   * jQuery UI 1.10 replaced the url method with the href attribute. Use this function to allow 
   * non-version specific code to set the target of a remote tab.
   */
  indiciaFns.setTabHref = function(tabs, tabIdx, liId, href) {
    var version = $.ui.version.split('.');
    if (version[0] === '1' && version[1] < 10) {
      tabs.tabs('url', tabIdx, href);
    } else {
      $('#' + liId + ' a').attr('href', href);
    }
  };

  /**
   * jQuery version independent .live/.delegate/.on code.
   */
  indiciaFns.on = function(events, selector, data, handler) {
    var version = jQuery.fn.jquery.split('.');
    if (version[0] === '1' && version[1] < 4) {
      $(selector).live(events, data, handler);
    } else if (version[0] === '1' && version[1] < 7) {
      $(document).delegate(selector, events, data, handler);
    } else {
      $(document).on(events, selector, data, handler);
    }

  };

}) (jQuery);

jQuery(document).ready(function($) {
  if ($('form input[name=website_id]').length>0) {
    var iform=$('form input[name=auth_token]').parents('form'),
    confirmOnPageExit = function (e) {
      // If we haven't been passed the event get the window.event
      e = e || window.event;
      var message = 'Are you sure you want to navigate away from this page? You will lose any data you have entered.';
      // For IE6-8 and Firefox prior to version 4
      if (e) {
        e.returnValue = message;
      }
      // For Chrome, Safari, IE8+ and Opera 12+
      return message;
    }, 
    detectInput = function() {
      window.onbeforeunload = confirmOnPageExit;
      $(iform).find(':input').unbind('change', detectInput);
    }
    // any data input, need to confirm if navigating away
    $(iform).find(':input').bind('change', detectInput);
    $(iform).submit(function() {
      // allowed to leave page on form submit
      window.onbeforeunload = null;
    });
  }
});