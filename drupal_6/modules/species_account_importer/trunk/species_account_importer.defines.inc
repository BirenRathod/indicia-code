<?php
// $Id$

// The following settings provide defaults appropriate to importing BWARS
// aculeate atlases.
define('SAI_DEFAULT_SPECIES_REGEX', '/^\*(?P<name>.+)/');
define('SAI_DEFAULT_IGNORE_REGEX', "/^Mapcompiledby/\n/^\[\w+(:\s*\w+)?\]$/");
define('SAI_DEFAULT_RANKS', "Family\nSubfamily");
define('SAI_DEFAULT_RANK_REGEXES', "/^\[(?P<Family>\w+)(:\s*(?P<Subfamily>\w+))?\]$/");
define('SAI_DEFAULT_EXTRACT_GENUS', true);
define('SAI_DEFAULT_EXTRACT_AUTHORITY_FIELD', '');
define('SAI_DEFAULT_CONTENT_TYPE_RANK', false);