<?php
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
 *
 * @package Client
 * @subpackage PrebuiltForms
 * @author  Indicia Team
 * @license http://www.gnu.org/licenses/gpl.html GPL 3.0
 * @link  http://code.google.com/p/indicia/
 */

/**
 * A page for managing the list of members of a group.
 * 
 * @package Client
 * @subpackage PrebuiltForms
 */
class iform_group_admin {
  
  private static $groupType='group';
  
  /** 
   * Return the form metadata.
   * @return array The definition of the form.
   */
  public static function get_group_admin_definition() {
    return array(
      'title'=>'Administer a group',
      'category' => 'Recording groups',
      'description'=>'A form for administering a group, in particular the members list. Should be passed a parameter called group_id.'
    );
  }
  
  /**
   * Get the list of parameters for this form.
   * @return array List of parameters that this form requires.
   */
  public static function get_parameters() {   
    return array(
      array(
        'name'=>'allow_remove',
        'caption'=>'Allow users to be removed from the group',
        'description'=>'Show an icon next to each user to allow them to be removed from the group?',
        'type'=>'boolean',
        'default' => false,
        'group' => 'Other IForm Parameters',
        'required'=>false
      ),
      array(
        'name'=>'allow_role_toggle',
        'caption'=>'Allow users role to be altered',
        'description'=>'Show an icon next to each user to allow their role to be toggled between administrator and member?',
        'type'=>'boolean',
        'default' => false,
        'group' => 'Other IForm Parameters',
        'required'=>false
      ),
      array(
        'name'=>'member_role_name',
        'caption'=>'Member role name',
        'description'=>'On screen name to give to the member role (e.g. student).',
        'type'=>'string',
        'group' => 'Other IForm Parameters',
        'required'=>false
      ),
      array(
        'name'=>'admin_role_name',
        'caption'=>'Administrator role name',
        'description'=>'On screen name to give to the administrator role (e.g. mentor).',
        'type'=>'string',
        'group' => 'Other IForm Parameters',
        'required'=>false
      ),
      array(
        'name'=>'admin_role_name',
        'caption'=>'Administrator role name',
        'description'=>'On screen name to give to the administrator role (e.g. mentor).',
        'type'=>'string',
        'group' => 'Other IForm Parameters',
        'required'=>false
      ),
      array(
        'name'=>'groups_page_path',
        'caption'=>'Path to main groups page',
        'description'=>'Path to the Drupal page which my groups are listed on.',
        'type'=>'text_input',
        'required'=>false
      ), 
    );
  }
  
  /**
   * Return the generated form output.
   * @param array $args List of parameter values passed through to the form depending on how the form has been configured.
   * This array always contains a value for language.
   * @param object $node The Drupal node object.
   * @param array $response When this form is reloading after saving a submission, contains the response from the service call.
   * Note this does not apply when redirecting (in this case the details of the saved object are in the $_GET data).
   * @return Form HTML.
   */
  public static function get_form($args, $node, $response=null) {
    if (!hostsite_get_user_field('indicia_user_id'))
      return 'Please ensure that you\'ve filled in your surname on your user profile before creating or editing groups.';
    self::createBreadcrumb($args);
    iform_load_helpers(array('report_helper'));
    report_helper::$website_id=$args['website_id'];
    $auth = report_helper::get_read_write_auth($args['website_id'], $args['password']);
    if (empty($_GET['group_id'])) 
      return 'This form should be called with a group_id parameter';
    $group = self::loadExistingGroup($_GET['group_id'], $auth, $args);
    hostsite_set_page_title(lang::get('Administer {1}', $group['title']));
    report_helper::$javascript .= "indiciaData.website_id=$args[website_id];\n";
    report_helper::$javascript .= "indiciaData.group_id=$group[id];\n";
    report_helper::$javascript .= 'indiciaData.ajaxFormPostUrl="'.iform_ajaxproxy_url(null, 'groups_user')."\";\n";
    if (!empty($args['admin_role_name']))
      $adminRoleOnScreenName=$args['admin_role_name'];
    else 
      $adminRoleOnScreenName='administrator';
    if (!empty($args['member_role_name']))
      $memberRoleOnScreenName=$args['member_role_name'];
    else 
      $memberRoleOnScreenName='member';
    //Setup actions column
    $actions = 
    array(
      array(
        'caption'=>'Approve member',
        'javascript'=>'approveMember({groups_user_id});',
        'visibility_field'=>'pending'
      ),            
    );
    if ($adminRoleOnScreenName==='administrator')
      $caption='Set user to be an '.$adminRoleOnScreenName;
    else
      $caption='Set user to be a '.$adminRoleOnScreenName;
    //Only allow toggle of user's role if page is configured to allow this.
    if (isset($args['allow_role_toggle']) && $args['allow_role_toggle']==true) {
      $actions[] = array(
        'caption'=>$caption,
        'javascript'=>'toggleRole({groups_user_id},\'{name}\',\'administrator\');',
        'visibility_field'=>'member'
      );
      $actions[] = array(
        'caption'=>'Set user to be a '.$memberRoleOnScreenName,
        'javascript'=>'toggleRole({groups_user_id},\'{name}\',\'member\');',
        'visibility_field'=>'administrator'
      );
    }
    //Only allow removal of users if page is configured to allow this.
    if (isset($args['allow_remove']) && $args['allow_remove']==true)
      $actions[] = array(
        'caption'=>'Remove from group',
        'javascript'=>'removeMember({groups_user_id},\'{name}\');',
      );
    $r = report_helper::report_grid(array(
      'dataSource'=>'library/groups/group_members',
      'readAuth'=>$auth['read'],
      'extraParams'=>array('group_id'=>$group['id']),
      'columns'=>array(
        array(
          'display'=>lang::get('Actions'),
          'actions'=>$actions
        )
      )
    ));
    return $r;
  }
  
  private static function createBreadcrumb($args) {
    if (!empty($args['groups_page_path']) && function_exists('hostsite_set_breadcrumb') && function_exists('drupal_get_normal_path')) {
      $path = drupal_get_normal_path($args['groups_page_path']);
      $node = menu_get_object('node', 1, $path);
      $breadcrumb[$node->title] = $args['groups_page_path'];
      hostsite_set_breadcrumb($breadcrumb);
    }
  }
  
  /**
   * Fetch an existing group's information from the database when editing.
   * @param integer $id Group ID
   * @param array $auth Authorisation tokens
   */
  private static function loadExistingGroup($id, $auth, $args) {
    $group = data_entry_helper::get_population_data(array(
      'table'=>'group',
      'extraParams'=>$auth['read']+array('view'=>'detail', 'id'=>$_GET['group_id']),
      'nocache'=>true
    ));
    if ($group[0]['created_by_id']!==hostsite_get_user_field('indicia_user_id')) {
      if (!function_exists('user_access') || !user_access('Iform groups admin')) {
        // user did not create group. So, check they are an admin
        $admins = data_entry_helper::get_population_data(array(
          'table'=>'groups_user',
          'extraParams'=>$auth['read']+array('group_id'=>$_GET['group_id'], 'administrator'=>'t'),
          'nocache'=>true
        ));
        $found=false;
        foreach($admins as $admin) {
          if ($admin['user_id']===hostsite_get_user_field('indicia_user_id')) {
            $found=true;
            break;
          }
        }
        if (!$found)
          throw new exception(lang::get('You are trying to edit a group you don\'t have admin rights to.'));
      }
    }
    return $group[0];
  }
  
}
