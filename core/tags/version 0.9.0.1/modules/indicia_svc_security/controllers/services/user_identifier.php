<?php defined('SYSPATH') or die('No direct script access.');
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
 * @package Services
 * @author  Indicia Team
 * @license http://www.gnu.org/licenses/gpl.html GPL 3.0
 * @link  http://code.google.com/p/indicia/
 */

/**
 * Controller for service calls relating to the use of user identifiers to associated
 * client website users with warehouse user accounts. An example usage of this is
 * to use a twitter account identifier to identify a single user across multiple client
 * websites.
 */
class User_Identifier_Controller extends Service_Base_Controller {
  protected $db;
  
  /**
   * Service method that takes a list of user identifiers such as email addresses and returns the appropriate user ID
   * from the warehouse, which can then be used in subsequent calls to save the data. Takes the 
   * following parameters in the $_GET or $_POST data in addition to a nonce and auth_token for a write operation:<ul>
   * <li><strong>identifiers</strong/><br/>
   * Required. A JSON encoded array of identifiers known for the user. Each array entry is an object 
   * with a type property (e.g. twitter, openid) and identifier property (e.g. twitter account). An identifier of type
   * email must be provided in case a new user account has to be created on the warehouse.</li>
   * <li><strong>surname</strong/><br/>
   * Required. Surname of the user, enabling a new user account to be created on the warehouse.</li>
   * <li><strong>first_name</strong/><br/>
   * Optional. First name of the user, enabling a new user account to be created on the warehouse.</li>
   * <li><strong>cms_user_id</strong/><br/>
   * Required. User ID from the client website's login system.</li>
   * <li><strong>warehouse_user_id</strong/><br/>
   * Optional. Where a user ID is already known but a new identifier is being provided (e.g. an email switch), provide the warehouse user ID.</li>
   * <li><strong>force</strong/><br/>
   * Optional. Only relevant after a request has returned an array of several possible matches. Set to 
   * merge or split to define the action.</li>
   * <li><strong>users_to_merge</strong/><br/>
   * If force=merge, then this parameter can be optionally used to limit the list of users in the merge operation.
   * Pass a JSON encoded array of user IDs.</li>
   * <li><strong>attribute_values</strong>
   * Optional list of custom attribute values for the person which have been modified on the client website
   * and should be synchronised into the warehouse person record. The custom attributes must already exist
   * on the warehouse and have a matching caption, as well as being marked as synchronisable or the attribute
   * values will be ignored. Provide this as a JSON object with the properties being the caption of the 
   * attribute and the values being the values to change.
   * </li>
   * <li><strong>shares_to_prevent</strong>
   * If the user has opted out of allowing their records to be shared with other 
   * websites, the sharing tasks which they have opted out of should be passed as a comma separated list
   * here. Valid sharing tasks are: reporting, peer_review, verification, data_flow, moderation. They 
   * will then be stored against the user account. </li>
   * </ul>
   * @return JSON JSON object containing the following properties:
   *   userId - If a single user account has been identified then returns the Indicia user ID for the existing 
   *     or newly created account. Otherwise not returned.
   *   attrs - If a single user account has been identifed then returns a list of captions and values for the 
   *     attributes to update on the client account.
   *   possibleMatches - If a list of possible users has been identified then this property includes a list of people that 
   *     match from the warehouse - each with the user ID, website ID and website title they are
   *     members of. If this happens then the client must ask the user to confirm that they 
   *     are the same person as the users of this website and if so, the response is sent back with a force=merge
   *     parameter to force the merge of the people. If they are the same person as only some of the other users,
   *     then use users_to_merge to supply an array of the user IDs that should be merged. Alternatively, if 
   *     force=split is passed through then the best fit user ID is returned and no merge operation occurs.
   *   error - Error string if an error occurred.
   * @link http://code.google.com/p/indicia/wiki/WebServicesUserIdentifiers
   */
  public function get_user_id() {
    try {
      // don't use $_REQUEST as it can do funny things escaping quotes etc.
      $request=array_merge($_GET, $_POST);
      if (!array_key_exists('identifiers', $request))
        throw new exception('Error: missing identifiers parameter');
      $identifiers = json_decode($request['identifiers']);
      if (!is_array($identifiers))
        throw new Exception('Error: identifiers parameter not of correct format');
      if (empty($request['surname']))
        throw new exception('Call to get_user_id requires a surname in the GET or POST data.');
      // We don't need a website_id in the request as the authentication data contains it, but
      // we do need to know the cms_user_id so that we can ensure any previously recorded data for
      // this user is attributed correctly to the warehouse user.
      if (!isset($request['cms_user_id']) || !$request['cms_user_id'])
        throw new exception('Call to get_user_id requires a cms_user_id in the GET or POST data.');
      // authenticate requesting website for this service. This can create a user, so need write
      // permission.
      $this->authenticate('write');
      $this->db = new Database();
      if (!empty($request['warehouse_user_id'])) {
        $userId=$request['warehouse_user_id'];
        $qry = $this->db->select('person_id')->from('users')->where(array('id'=>$userId))->get()->result_array(false);
        $this->person_id = $qry[0]['person_id'];
      } else {
        $existingUsers = array();
        // work through the list of identifiers and find the users for the ones we already know about, 
        // plus find the list of identifiers we've not seen before.
        // email is a special identifier used to create person.
        $email = null;
        foreach ($identifiers as $identifier) {
          // store the email address, since this is always required to create a person
          if ($identifier->type==='email') {
            $email=$identifier->identifier;
            // The query to find an existing user is slightly different for emails, since the 
            // email can be in the user identifier list or the person record
            $joinType='LEFT';
          } else
            $joinType='INNER';
          $this->db->select('DISTINCT u.id as user_id, u.person_id')
              ->from('users as u')
              ->join('people as p', 'p.id', 'u.person_id')
              ->join('user_identifiers as um', 'um.user_id', 'u.id', $joinType)
              ->join('termlists_terms as tlt1', 'tlt1.id', 'um.type_id', $joinType)
              ->join('termlists_terms as tlt2', 'tlt2.meaning_id', 'tlt1.meaning_id', $joinType)
              ->join('terms as t', 't.id', 'tlt2.term_id', $joinType)
              ->where(array('u.deleted'=>'f', 'p.deleted'=>'f'));
          if ($identifier->type==='email') {
            // Filter to find either the user identifier or the email in the person record
            $this->db->where("(um.identifier ='".$identifier->identifier."' OR p.email_address='".$identifier->identifier."')");
            $this->db->where("(t.term='".$identifier->type."' OR p.email_address='".$identifier->identifier."')");
          } else {
            $this->db->where("um.identifier='".$identifier->identifier."'");
            $this->db->where("t.term IN ('".$identifier->type."')");
          }
          
          if (isset($request['users_to_merge'])) {
            $usersToMerge = json_decode($request['users_to_merge']);
            $this->db->in('user_id', $usersToMerge);
          }
          $r = $this->db->get()->result_array(true);
          foreach($r as $existingUser) {
            // create a placeholder for the known user we just found
            if (!isset($existingUsers[$existingUser->user_id]))
              $existingUsers[$existingUser->user_id]=array();
            // add the identifier detail to this known user
            $existingUsers[$existingUser->user_id][] = array(
              'identifier'=>$identifier->identifier,
              'type'=>$identifier->type,
              'person_id'=>$existingUser->person_id);
          }
          
        }
        if ($email === null)
          throw new exception('Call to get_user_id requires an email address in the list of provided identifiers.');
        // Now we have a list of the existing users that match this identifier. If there are none, we 
        // can create a new user and attach to the current website. If there is one, then we can
        // just return it. If more than one, then we have a resolution task since it probably
        // means 2 user records refer to the same physical person, or someone is sharing their
        // identifiers!
        if (count($existingUsers)===0)
          $userId = $this->createUser($email);
        elseif (count($existingUsers)===1) {
          // single, known user associated with these identifiers
          $keys = array_keys($existingUsers);
          $userId = array_pop($keys);
          $this->person_id = $existingUsers[$userId][0]['person_id'];
        }
        if (!isset($userId)) {
          $resolution = $this->resolveMultipleUsers($identifiers, $existingUsers);        
          // response could be a list of possible users to match against, or a single user ID.
          if (isset($resolution['possibleMatches'])) {
            echo json_encode($resolution);
            return;
          } else {
            $userId = $resolution['userId'];
            $this->person_id = $existingUsers[$userId][0]['person_id'];
          }
        }
      }
      $this->storeIdentifiers($userId, $identifiers);
      $this->associateWebsite($userId);
      $this->storeSharingPreferences($userId);
      $attrs = $this->getAttributes();
      $this->storeCustomAttributes($userId, $attrs);
      // Convert the attributes to update in the client website account into an array
      // of captions & values
      $attrsToReturn = array();
      foreach ($attrs as $attr)
        $attrsToReturn[$attr['caption']]=$attr['value'];
      echo json_encode(array(
        'userId'=>$userId,
        'attrs'=>$attrsToReturn
      ));
      // If allocating a new user ID, then update the created_by_id for all records that were created by this cms_user_id. This 
      // takes ownership of the records.
      if (empty($request['warehouse_user_id']))
        postgreSQL::setOccurrenceCreatorByCmsUser($this->website_id, $userId, $request['cms_user_id'], $this->db);
    }
    catch (Exception $e) {
      $this->handle_error($e);
    }
  }
  
  /**
   * Finds the list of custom attributes associated whith the person and the
   * associated values.
   * @return array List of the attributes to synchronise into the client site. 
   */
  private function getAttributes() {
    // find the attribute Ids for the ones we have values for, that are synchronisable 
    // and associated with the current website. Note we deliberately read deleted
    // values so that we can return blanks
    $attrs = $this->db->select('DISTINCT ON (pa.id) pa.id, pav.id as value_id, pa.caption, pa.data_type, '.
          'pav.text_value, pav.int_value, pav.float_value, pav.date_start_value, pav.deleted')
        ->from('person_attributes as pa')
        ->join('person_attributes_websites as paw', 'paw.person_attribute_id', 'pa.id')
        ->join('person_attribute_values as pav', 'pav.person_attribute_id', 'pa.id', 'LEFT')
        ->in('pav.person_id',array(null, $this->person_id))
        ->where(array(
          'pa.synchronisable'=>'t',
          'pa.deleted'=>'f',
          'paw.deleted'=>'f',
          'paw.website_id'=>$this->website_id
        ))
        ->orderby(array('pa.id'=>'ASC', 'pav.deleted'=>'ASC')) // forces the distinct on to prioritise non-deleted records.
        ->get()->result_array(false);
    // discard deletions if they are superceded by another non-deleted value
    // Convert the diff type value fields into a single variant value
    foreach ($attrs as &$attr) {
      if ($attr['deleted'])
        $attr['value']=null;
      else {
        switch ($attr['data_type']) {
          case 'T':
            $attr['value']=$attr['text_value'];
            break;
          case 'F':
            $attr['value']=$attr['float_value'];
            break;
          case 'D':
          case 'V':
            $attr['value']=$attr['date_start_value'];
            break;
          default:
            $attr['value']=$attr['int_value'];
        }
      }
      unset($attr['text_value']);
      unset($attr['float_value']);
      unset($attr['date_value']);
      unset($attr['int_value']);
    }
    return $attrs;
  }
  
  /**
   * Creates a new user account using the surname and first_name (if available)
   * in the $_REQUEST.
   */
  private function createUser($email) {
    $person = ORM::factory('person')->where(array('email_address'=>$email, 'deleted'=>'f'))->find();
    if ($person->loaded
        && ((!empty($person->first_name) && $person->first_name != '?'
        && !empty($_REQUEST['first_name']) && $_REQUEST['first_name']!==$person->first_name)
        || $person->surname !== $_REQUEST['surname']))
      throw new exception("The system attempted to use your user account details to register you as a user of the ".
          "central records database, but a different person with email address $email already exists. Please contact your ".
          "site administrator who may be able to help resolve this issue." . print_r($_REQUEST, true));
    $data = array(
      'first_name' => isset($_REQUEST['first_name']) ? $_REQUEST['first_name'] : '?',
      'surname' => $_REQUEST['surname'],
      'email_address'=>$email
    );
    if ($person->loaded)
      $data['id']=$person->id;
    $person->validate(new Validation($data), true);
    $this->checkErrors($person);
    $user = ORM::factory('user');
    // ensure a unique username that fits in the 7-30 char limit
    $unique=0;
    $uname = str_pad($person->first_name.'_'. $person->surname, 7, '_');
    do {
      $rolling = $unique===0 ? '' : '_'.$unique;
      $username = substr($uname, 0, 30-strlen($rolling)).$rolling;
      $unique++;
    } while ($this->db->select('id')->from('users')->where(array('username'=>$username))->get()->count()>0);
    $data = array(
      'person_id'=>$person->id,
      'email_visible'=>'f',
      'username'=>$username,
      // User will not actually have warehouse access, so password fairly irrelevant
      'password' => 'P4ssw0rd',
    );
    $user->validate(new Validation($data), true);
    $this->checkErrors($user);
    $this->person_id=$person->id;
    return $user->id;
  }
  
  /**
   * For the list of identifiers passed through to the web service for a user, ensure they are all 
   * persisted in the database. 
   */
  private function storeIdentifiers($userId, $identifiers) {
    // build a list of all the identifier types we will need, to ensure that we have terms for them.
    $typeTerms = array();
    foreach ($identifiers as $identifier) {
      if (!in_array($identifier->type, $typeTerms)) 
        $typeTerms[]=$identifier->type;
    }
    // now ensure the termlist is populated
    $defaultLang = kohana::config('indicia.default_lang');
    foreach ($typeTerms as $term) {
      $qry = $this->db->select('t.id')
          ->from('terms as t')
          ->join('termlists_terms as tlt', array('tlt.term_id'=>'t.id'))
          ->join('termlists as tl', array('tl.id'=>'tlt.termlist_id'))
          ->where(array('t.deleted'=>'f', 't.term'=>$term, 'tl.external_key'=>'indicia:user_identifier_types',
               'tlt.deleted'=>'f', 'tl.deleted'=>'f'))
          ->get()->result_array(false);
      if (count($qry)===0) {
        // missing term so insert
        $this->db->query("SELECT insert_term('$term', '$defaultLang', null, 'indicia:user_identifier_types');");
      }
    }
    // Check each identifier to see if it already exists for the user.
    foreach ($identifiers as $identifier) {
      $r = $this->db->select('ui.user_id')
          ->from('terms as t')
          ->join('termlists_terms as tlt1', array('tlt1.term_id'=>'t.id'))
          ->join('termlists_terms as tlt2', array('tlt2.meaning_id'=>'tlt1.meaning_id'))
          ->join('user_identifiers as ui', array('ui.type_id'=>'tlt2.id'))
          ->where(array(
              't.term'=>$identifier->type, 
              'ui.user_id' => $userId,
              'ui.identifier' => $identifier->identifier,
              't.deleted' => 'f',
              'tlt1.deleted' => 'f',
              'tlt2.deleted' => 'f',
              'ui.deleted' => 'f'))
          ->get()->result_array(false);
      if (!count($r)) {
        // identifier does not yet exist so create it
        $this->loadIdentifierTypes();
        $new=ORM::factory('user_identifier');
        $data = array(
          'user_id'=>$userId,
          'type_id'=>$this->identifierTypes[$identifier->type],
          'identifier'=>$identifier->identifier
        );
        $new->validate(new Validation($data), true);
        $this->checkErrors($new);
      }
    }    
  }
  
  /**
   * Loads the contents of the user identifier types termlist into a memory array, making it quicker to lookup.
   */
  private function loadIdentifierTypes() {
    if (!isset($this->identifierTypes)) {
      $this->identifierTypes=array();
      $terms = $this->db
        ->select('termlists_terms.id, term')
        ->from('termlists_terms')
        ->join('terms', 'terms.id', 'termlists_terms.term_id')
        ->join('termlists', 'termlists.id', 'termlists_terms.termlist_id')
        ->where(array('termlists.external_key' => 'indicia:user_identifier_types', 'termlists_terms.deleted' => 'f', 'terms.deleted' => 'f', 'termlists.deleted'=>'f'))
        ->orderby(array('termlists_terms.sort_order'=>'ASC', 'terms.term'=>'ASC'))
        ->get();
      foreach ($terms as $term) {
        $this->identifierTypes[$term->term] = $term->id;
      }
    }
  }
  
  /**
   * Check the errors in a model and throw an exception if there are any.
   */
  private function checkErrors($model) {
    $errors = $model->getAllErrors();
    if (count($errors)) {
      kohana::log('debug', 'Errors on user identifier saved model: '.print_r($errors, true));
      throw new exception(print_r($errors, true));
    }
  }
  
  /**
   * Create the associations between a user and the website that this service call was made on,
   * if the association does not already exist.
   */
  private function associateWebsite($userId) {
    $qry = $this->db->select('id')
        ->from('users_websites')
        ->where(array('user_id'=>$userId, 'website_id'=>$this->website_id))
        ->get()->result_array(false);
        
    if (count($qry)===0)
      // insert new join record
      $uw=ORM::factory('users_website');
    else {
      // update existing
      $uw=ORM::factory('users_website', $qry[0]['id']);
      if ($uw->site_role_id===1 || $uw->site_role_id===2)
        // don't bother updating, they are already admin or editor for this site
        return;
    }
    $data = array(
      'user_id'=>$userId,
      'website_id'=>$this->website_id,
      'site_role_id'=>3
    );
    $uw->validate(new Validation($data), true);
    $this->checkErrors($uw);
  }
  
  /**
   * If there are sharing preferences in the $_REQUEST for this user account, then 
   * stores them against the user record. E.g. the user might opt of allowing other
   * websites to pass on their records via the sharing mechanism.
   */
  private function storeSharingPreferences($userId) {
    if (isset($_REQUEST['shares_to_prevent'])) {
      // the web service request parameter is a comma separated list of the tasks this user does not
      // want to share their records with other sites for
      $preventShares = explode(',', $_REQUEST['shares_to_prevent']);
      // build an array of values to post to the db
      $tasks = array('reporting', 'peer_review', 'verification', 'data_flow', 'moderation');
      $values=array();
      foreach ($tasks as $task) {
        $values["allow_share_for_$task"]=(in_array($task, $preventShares) ? 'f' : 't');
      }
      // update their user record.
      $this->db->update('users', $values, array('id'=>$userId));    
    }
  }
  
  /**
   * Stores any changed custom attribute values supplied in the request data against person associated
   * with the user. 
   * @param integer $userId User ID,
   * @param array $attrs Array of attribute & value data.
   */
  private function storeCustomAttributes($userId, &$attrs) {
    if (!empty($_REQUEST['attribute_values'])) {
      $valueData = json_decode($_REQUEST['attribute_values'], true);
      if (count($valueData)) {
        $attrCaptions = array_keys($valueData);
        $pav = ORM::factory('person_attribute_value');
        // loop through all the possible attributes to save the changed ones from the client site
        foreach($attrs as &$attr) {
          // Ignore any attributes we don't have a change value for
          if (in_array($attr['caption'], $attrCaptions)) {
            $data = array(
                'person_id' => $this->person_id,
                'person_attribute_id' => $attr['id'],
                'text_value' => $valueData[$attr['caption']]
            );
            // Store the attribute value we are saving in the array of attributes, so the 
            // full updated list can be returned to the client website
            $attr['value'] = $valueData[$attr['caption']];
            kohana::log('debug', 'NEED TO GET CORRECT TYPE OF VALUE ABOVE');
            if (!empty($attr['value_id'])) {
              $data['id'] = $attr['value_id'];
              $pav->find($attr['value_id']);
            } else
              $pav->clear();
            $pav->validate(new Validation($data), true);
            $this->checkErrors($pav);
          }
        }
        
      }
    }
  }
  
  /**
   * Handle the case when multiple possible users are found for a list of identifiers. 
   * Outcome depends on the settings in $_REQUEST, with options to set force=merge or force=split. If not
   * forced, then the list of possible user IDs along with the websites they belong to are returned so the user
   * can consider the best action. If force=merge then users_to_merge can be set to an array of user IDs that the
   * merge applies to.
   */
  private function resolveMultipleUsers($identifiers, $existingUsers) {
    if (isset($_REQUEST['force'])) {
      if ($_REQUEST['force']==='split') {
        $uid = $this->findBestFit($identifiers, $existingUsers);
        return array('userId'=>$uid);
      } elseif ($_REQUEST['force']==='merge') {
        $uid = $this->findBestFit($identifiers, $existingUsers);
        // Merge the users into 1. A $_REQUEST['users_to_merge'] array can be used to limit which are merged.
        $this->mergeUsers($uid, $existingUsers);
        return array('userId'=>$uid);
      }
    } else {
      // we need to propose that there are several possible existing users which match the supplied identifiers
      // to the client website
      $users = array_keys($existingUsers);
      $this->db->select('users_websites.user_id, users_websites.website_id, websites.title')
        ->from('websites')
        ->join('users_websites', 'users_websites.website_id', 'websites.id')
        ->join('users', 'users.id', 'users_websites.user_id')
        ->join('people', 'people.id', 'users.person_id')
        ->where(array('websites.deleted'=>'f', 'users.deleted'=>'f', 'people.deleted'=>'f'))
        ->where('users_websites.site_role_id is not null')
        ->in('users_websites.user_id', $users);
      if (isset($_REQUEST['users_to_merge'])) {
        $usersToMerge = json_decode($_REQUEST['users_to_merge']);
        $this->db->in('users_websites.user_id', $usersToMerge);
      }
      return array('possibleMatches'=>$this->db->get()->result_array(false));
    }
  }
  
  /**
   * In the case where there are 2 users identified by a single list of identifiers, 
   * resolve the situation. Returns the best matching user (based on first_name and surname match then
   * number of matching identifiers)
   * @todo Note that in conjunction with this, a tool must be provided in the warehouse for admin to 
   * check for and merge potential duplicate users.
   */
  private function findBestFit($identifiers, $existingUsers) {
    $nameMatches = array();    
    foreach ($identifiers as $identifier) {
      // find all the existing users which match this identifier.
      $this->db->select('ui.user_id, p.first_name, p.surname')
          ->from('users as u')
          ->join('people as p', 'p.id', 'u.person_id')
          ->join('user_identifiers as ui', 'ui.user_id', 'u.id')
          ->join('termlists_terms as tlt1', 'tlt1.id', 'ui.type_id')
          ->join('termlists_terms as tlt2', 'tlt2.meaning_id', 'tlt1.meaning_id')
          ->join('terms as t', 't.id', 'tlt2.term_id')
          ->where(array('t.term'=>$identifier->type,
              'ui.identifier'=>$identifier->identifier,
              'u.deleted'=>'f', 'p.deleted'=>'f', 'ui.deleted'=>'f', 'tlt1.deleted'=>'f', 'tlt2.deleted'=>'f', 't.deleted'=>'f'));
      if (isset($_REQUEST['users_to_merge'])) {
        $usersToMerge = json_decode($_REQUEST['users_to_merge']);
        $this->db->in('ui.user_id', $usersToMerge);
      }
      $qry = $this->db->get()->result();
      foreach($qry as $match) {
        if (!isset($existingUsers[$match->user_id]['matches']))
          $existingUsers[$match->user_id]['matches']=1;
        else 
          $existingUsers[$match->user_id]['matches']=$existingUsers[$match->user_id]['matches']+1;
        // keep track of any exact name matches as they have priority
        if ($match->first_name==(isset($_REQUEST['first_name']) ? $_REQUEST['first_name'] : '')
            && $match->surname==$_REQUEST['surname'] && !in_array($match->user_id, $nameMatches))
          $nameMatches[] = $match->user_id;
      }
    }
    // Skim through the list of users to find the one that has the best fit. We try any with a name match
    // first.
    $bestFitUid = 0;
    $bestFitMatchCount = 0;
    foreach ($nameMatches as $uid) {
      if ($existingUsers[$uid]['matches']>$bestFitMatchCount) {
        $bestFitUid=$uid;
        $bestFitMatchCount=$existingUsers[$uid]['matches'];
      }
    }
    // No need to check non-name matches if we've got something.
    if ($bestFitUid!==0)
      return $bestFitUid;
    foreach ($existingUsers as $uid=>$user) {
      if ($user['matches']>$bestFitMatchCount) {
        $bestFitUid=$uid;
        $bestFitMatchCount=$user['matches'];
      }
    }
    // Now we know the user ID to keep
    return $bestFitUid;
  }
  
  /**
   * If a request is received with the force parameter set to merge, this means we can merge the detected users into one.
   */
  private function mergeUsers($uid, $existingUsers) {
    foreach($existingUsers as $userIdToMerge=>$websites) {
      if ($userIdToMerge!=$uid && (!isset($_REQUEST['users_to_merge']) || in_array($userIdToMerge, $_REQUEST['users_to_merge']))) {
        // Own the occurrences
        $this->db->update('occurrences', array('created_by_id'=>$uid), array('created_by_id'=>$userIdToMerge));
        $this->db->update('occurrences', array('updated_by_id'=>$uid), array('updated_by_id'=>$userIdToMerge));
        // delete the old user
        $uidsToDelete[] = $userIdToMerge;
        kohana::log('debug', "User merge operation resulted in deletion of user $userIdToMerge plus the related person");
      }
    }
    
    // use the User Ids list to find a list of people to delete.
    $psnIds = $this->db->select('person_id')->from('users')->in('id', $uidsToDelete)->get()->result_array();
    $pidsToDelete = array();
    foreach ($psnIds as $psnId)
      $pidsToDelete[] = $psnId->person_id;
    // do the actual deletions
    $this->db->from('users')->set(array('deleted'=>'t'))->in('id', $uidsToDelete)->update();
    $this->db->from('people')->set(array('deleted'=>'t'))->in('id', $pidsToDelete)->update();
  }

}