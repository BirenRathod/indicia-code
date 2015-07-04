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
 * @package	Client
 * @author	Indicia Team
 * @license	http://www.gnu.org/licenses/gpl.html GPL 3.0
 * @link 	http://code.google.com/p/indicia/
 */

global $custom_terms;

/**
 * Language terms for the survey_reporting_form_2 form.
 *
 * @package	Client
 */
$custom_terms = array(
	'LANG_not_logged_in' => 'Um den Inhalt zu sehen, m�ssen Sie sich einloggen.',
	'LANG_Location_Layer' => 'Ebene der Erfassungsquadrate',
	'LANG_Occurrence_List_Layer'=> 'Ebene der Feststellungen',
	'LANG_Surveys' => 'Erfassung',
	'LANG_Allocate_Locations' => 'Allocate Locations',
	'LANG_Transect' => 'Transekt',
	'LANG_Date' => 'Datum',
	'LANG_Visit_No' => 'Begehung No',
	'LANG_Num_Occurrences' => '# Feststellungen',
	'LANG_Num_Species' => '# Arten',
	'LANG_Show' => 'Anzeigen',
	'LANG_Add_Survey' => 'Neue Erfassung hinzuf�gen',
	'LANG_Not_Allocated' => 'Not Allocated',
	'LANG_Save_Location_Allocations' => 'Save Location Allocations',
	'LANG_Survey' => 'Erfassung',
	'LANG_Show_Occurrence' => 'Feststellung anzeigen',
	'LANG_Edit_Occurrence' => 'Feststellung editieren',
	'LANG_Add_Occurrence' => 'Feststellung hinzuf�gen',
	'LANG_Occurrence_List' => 'Liste der Feststellungen',
	'LANG_Read_Only_Survey' => 'Diese Erfassung ist schreibgesch�tzt.',
	'LANG_Read_Only_Occurrence' => 'Diese Feststellung wurde heruntergeladen und ist jetzt schreibgesch�tzt.',
	'LANG_Save_Survey_Details' => 'Erfassung speichern',
	'LANG_Save_Survey_And_Close' => 'Erfassung speichern und schliessen',
	'LANG_Close_Survey_Confirm' => 'Sind Sie sicher, dass diese Erfassung geschlossen werden soll? Die Daten dieser Erfassung werden gespeichert und schreibgesch�tzt, so dass Sie diese nicht mehr editieren k�nnen.',
	'LANG_Species' => 'Art',
	'LANG_Spatial_ref' => 'Koordinaten',
	'LANG_Click_on_map' => 'Auf Karte klicken um Koordinaten festzulegen',
	'LANG_Comment' => 'Kommentar',
	'LANG_Save_Occurrence_Details' => 'Feststellung speichern',
	'LANG_Territorial' => 'Revieranz.',
	'LANG_Count' => 'Anzahl',
	'LANG_Highlight' => 'Hervorheben',
	'LANG_Download' => 'Reports and Downloads',
	'LANG_Direction_Report' => 'Run a report to check that all non downloaded closed surveys have been walked in the same direction as the previously entered survey on that location. Returns the surveys which are in a different direction.',
	'LANG_Direction_Report_Button' => 'Run Survey Direction Warning Report - CSV',
	'LANG_Initial_Download' => 'Carry out initial download of closed surveys. Sweeps up all records which are in closed surveys but which have not been downloaded yet',
    'LANG_Initial_Download_Button' => 'Initial Download - CSV',
	'LANG_Confirm_Download' => 'Carry out confirmation download. This outputs the same data that will be included in the final download, but does not tag the data as downloaded. Only includes data in the last initial download unless a survey has since been reopened, when it will be excluded from this report.',
    'LANG_Confirm_Download_Button' => 'Confirmation Download - CSV',
	'LANG_Final_Download' => 'Carry out final download. Data will be marked as downloaded and no longer editable.',
    'LANG_Final_Download_Button' => 'Final Download - CSV',
	'LANG_Download_Occurrences' => 'CSV Liste der Feststellungen herunterladen',
	'LANG_No_Access_To_Location' => 'Sie wurden diesem Transekt nicht zugewiesen f�r welches diese Erfassung ausgef�hrt wurde - Sie haben keinen Zugriff auf diese Feststellung.',
	'LANG_No_Access_To_Sample' => 'This record is not a valid top level sample.',
	'LANG_Page_Not_Available' => 'Diese Seite ist zurzeit nicht verf�gbar.',
	'LANG_Return' => 'Zur�ck zum Haupterfassungsschirm',
	'validation_required' => 'Bitte einen Wert f�r dieses Feld eingeben',

	'Atlas Code' => 'Brutstatus',
	'Approximation?' => 'Sch�tzung?',
	'Overflying' => '�berfliegend',
	'Closed' => 'Geschlossen',
	'Cloud Cover' => 'Bew�lkung',
	'Confidence' => '�berzeugung',
	'Count' => 'Anzahl',
	'End Time' => 'Ankuntszeit',
	'No' => 'Nein',
	'validation_required' => 'Bitte einen Wert f�r dieses Feld eingeben',
	'Precipitation' => 'Niederschlag',
	'Reliability of this data' => 'Einsch�tzung dieser Daten',
	'Start Time' => 'Startzeit',
	'Temperature (Celsius)' => 'Temperatur (Celsius)',
	'Territorial' => 'Revieranzeigend',
	'Visit number in year' => 'Begehung',
	'Walk started at end' => 'Wegverlauf',
	'Wind Force' => 'Windst�rke',
	'Yes' => 'Ja',

	'LANG_Error_When_Moving_Sample' => 'An error has occurred during the merge process. Failed to move an occurrence.',
	'LANG_Error_When_Deleting_Sample' => 'An error has occurred during the merge process. Failed to delete empty survey.',
	'LANG_Found_Mergable_Surveys' => 'A number of surveys have been found which share the same transect and date combination as this one.',
	'LANG_Merge_With_ID' => 'Merge this survey with id',
	'LANG_Indicia_Warehouse_Error' => 'Error returned from Indicia Warehouse',
	'LANG_Survey_Already_Exists' => 'Eine Erfassung besteht bereits f�r diese Kombination Transekt/Datum. Sind Sie sicher diese hinzuzuf�gen/zu speichern?',
	'LANG_No_Access_To_Occurrence' => 'This record is not a valid occurrence.'
	
);