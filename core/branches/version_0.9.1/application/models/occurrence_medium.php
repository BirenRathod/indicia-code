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
 * @package	Core
 * @subpackage Models
 * @author	Indicia Team
 * @license	http://www.gnu.org/licenses/gpl.html GPL
 * @link 	http://code.google.com/p/indicia/
 */

/**
 * Model class for the Occurrence_Media table.
 *
 * @package	Core
 * @subpackage Models
 * @link	http://code.google.com/p/indicia/wiki/DataModel
 */
class Occurrence_medium_Model extends ORM {
  public $search_field = 'caption';

  protected $belongs_to = array('created_by' => 'user', 'updated_by' => 'user',
    'occurrence');

  public function validate(Validation $array, $save = false) {

    $array->pre_filter('trim');
    $array->add_rules('occurrence_id', 'required');
    $array->add_rules('path', 'required');

    $this->unvalidatedFields = array('caption', 'external_details', 'media_type_id');
    return parent::validate($array, $save);
  }

}
