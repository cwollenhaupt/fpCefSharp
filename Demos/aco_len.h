*====================================================================
* Diese Datei enthält alle englischen Sprachdefinitionen, die in
* Acodey verwendet werden. Wenn Sie eine englischsprachige Anwendung
* erstellen wollen, setzen Sie die Eigenschaft __ACODEY_LANGUAGE auf
* "en". Ändern Sie niemals diese Datei, da sie bei zukünftigen Ver-
* sionen angepaßt wird.
*====================================================================

	#UNDEF __INCLUDE_OK

	#IFNDEF LOC_X5C_FileExists
		#DEFINE LOC_X5C_FileExists "already exists, overwrite it?"
	#ENDIF
	#IFNDEF LOC_ERR_Error
		#DEFINE LOC_ERR_Error "Error: "
	#ENDIF
	#IFNDEF LOC_ERR_Method
		#DEFINE LOC_ERR_Method "Method: "
	#ENDIF
	#IFNDEF LOC_ERR_Line
		#DEFINE LOC_ERR_Line "Line: "
	#ENDIF
	#IFNDEF LOC_ERR_RuntimeError
		#DEFINE LOC_ERR_RuntimeError "Runtime error: "
	#ENDIF
	#IFNDEF LOC_IONAV_RevertQuestion
		#DEFINE LOC_IONAV_RevertQuestion "Do you want to revert the changes?"
	#ENDIF
	#IFNDEF LOC_IONAV_SaveQuestion
		#DEFINE LOC_IONAV_SaveQuestion "Do you want to save the changes?"
	#ENDIF
	#IFNDEF LOC_IONAV_DeleteQuestion
		#DEFINE LOC_IONAV_DeleteQuestion "Do you really want to delete this record?"
	#ENDIF
	#IFNDEF LOC_IONAV_SaveRevertQuestion
		#DEFINE LOC_IONAV_SaveRevertQuestion "Data in this record has changed. Do you want to save the changes?"
	#ENDIF
	#IFNDEF LOC_DATAB_InvalidValue
		#DEFINE LOC_DATAB_InvalidValue "Invalid value!"
	#ENDIF
	#IFNDEF LOC_DATAB_CorrectAndTryAgain
		#DEFINE LOC_DATAB_CorrectAndTryAgain "Please fix the problems with this record and try saving again."
	#ENDIF
	#IFNDEF LOC_DATAB_RecordLockErrorMessage
		#DEFINE LOC_DATAB_RecordLockErrorMessage "Cannot lock record."
	#ENDIF
	#IFNDEF LOC_DATAB_UpdateError
		#DEFINE LOC_DATAB_UpdateError "An error occurred while saving this record. Please fix the problems with this record and try saving again."
	#ENDIF
	#IFNDEF LOC_ERR_Suspend
		#DEFINE LOC_ERR_Suspend "Suspend?"
	#ENDIF
	#IFNDEF LOC_DATAB_RecordValidationErrorMessage
		#DEFINE LOC_DATAB_RecordValidationErrorMessage "This record violates the record validation rule."
	#ENDIF
	#IFNDEF LOC_DATAB_UpdateConflict
		#DEFINE LOC_DATAB_UpdateConflict "Another user updated this record."
	#ENDIF
	#IFNDEF LOC_DATAB_FLockInTransaction
		#DEFINE LOC_DATAB_FLockInTransaction "Access denied while attempting to lock table."
	#ENDIF
	#IFNDEF LOC_DATAB_UniquenessViolated
		#DEFINE LOC_DATAB_UniquenessViolated "Uniqueness of index violated."
	#ENDIF
	#IFNDEF LOC_DATAB_AddTrigger
		#DEFINE LOC_DATAB_AddTrigger "This record contains invalid values. Probably you have not entered all required fields."
	#ENDIF
	#IFNDEF LOC_DATAB_DeleteTrigger
		#DEFINE LOC_DATAB_DeleteTrigger "Cannot delete record because other records depend on this record."
	#ENDIF
	#IFNDEF LOC_DATAB_EditTrigger
		#DEFINE LOC_DATAB_EditTrigger "Cannot update related records. Probably these records are currently being edited and therefore lcoked. Please wait until the other record is available again."
	#ENDIF

	#IFNDEF __SET_ANSI
		#DEFINE __SET_ANSI OFF
	#ENDIF
	#IFNDEF __SET_AUTOSAVE
		#DEFINE __SET_AUTOSAVE OFF
	#ENDIF
	#IFNDEF __SET_BELL
		#DEFINE __SET_BELL ON
	#ENDIF
	#IFNDEF __SET_BELL_TO
		#DEFINE __SET_BELL_TO TO '', 1
	#ENDIF
	#IFNDEF __SET_BLOCKSIZE_TO
		#DEFINE __SET_BLOCKSIZE_TO TO 64
	#ENDIF
	#IFNDEF __SET_CARRY
		#DEFINE __SET_CARRY OFF
	#ENDIF
	#IFNDEF __SET_CENTURY
		#DEFINE __SET_CENTURY ON
	#ENDIF
	#IFNDEF __SET_CLOCK
		#DEFINE __SET_CLOCK STATUS
	#ENDIF
	#IFNDEF __SET_COLLATE_TO
		#DEFINE __SET_COLLATE_TO TO 'MACHINE'
	#ENDIF
	#IFNDEF __SET_COMPATIBLE
		#DEFINE __SET_COMPATIBLE OFF
	#ENDIF
	#IFNDEF __SET_CONFIRM
		#DEFINE __SET_CONFIRM OFF
	#ENDIF
	#IFNDEF __SET_CPDIALOG
		#DEFINE __SET_CPDIALOG ON
	#ENDIF
	#IFNDEF __SET_CURRENCY
		#DEFINE __SET_CURRENCY LEFT
	#ENDIF
	#IFNDEF __SET_CURRENCY_TO
		#DEFINE __SET_CURRENCY_TO TO '$'
	#ENDIF
	#IFNDEF __SET_DATE_TO
		#DEFINE __SET_DATE_TO TO AMERICAN
	#ENDIF
	#IFNDEF __SET_DECIMALS_TO
		#DEFINE __SET_DECIMALS_TO TO 2
	#ENDIF
	#IFNDEF __SET_DELETED
		#DEFINE __SET_DELETED ON
	#ENDIF
	#IFNDEF __SET_DELIMITERS
		#DEFINE __SET_DELIMITERS OFF
	#ENDIF
	#IFNDEF __SET_DEVELOPMENT
		#DEFINE __SET_DEVELOPMENT OFF
	#ENDIF
	#IFNDEF __SET_ECHO
		#DEFINE __SET_ECHO OFF
	#ENDIF
	#IFNDEF __SET_ESCAPE
		#DEFINE __SET_ESCAPE ON
	#ENDIF
	#IFNDEF __SET_EXACT
		#DEFINE __SET_EXACT OFF
	#ENDIF
	#IFNDEF __SET_EXCLUSIVE
		#DEFINE __SET_EXCLUSIVE OFF
	#ENDIF
	#IFNDEF __SET_FDOW_TO
		#DEFINE __SET_FDOW_TO TO 1
	#ENDIF
	#IFNDEF __SET_FIELDS
		#DEFINE __SET_FIELDS OFF
	#ENDIF
	#IFNDEF __SET_FIXED
		#DEFINE __SET_FIXED OFF
	#ENDIF
	#IFNDEF __SET_FWEEK_TO
		#DEFINE __SET_FWEEK_TO TO 1
	#ENDIF
	#IFNDEF __SET_HEADINGS
		#DEFINE __SET_HEADINGS ON
	#ENDIF
	#IFNDEF __SET_HOURS_TO
		#DEFINE __SET_HOURS_TO TO 12
	#ENDIF
	#IFNDEF __SET_KEYCOMP_TO
		#DEFINE __SET_KEYCOMP_TO TO WINDOWS
	#ENDIF
	#IFNDEF __SET_LOGERRORS
		#DEFINE __SET_LOGERRORS ON
	#ENDIF
	#IFNDEF __SET_LOCK
		#DEFINE __SET_LOCK OFF
	#ENDIF
	#IFNDEF __SET_MARK_TO
		#DEFINE __SET_MARK_TO TO '/'
	#ENDIF
	#IFNDEF __SET_MEMOWIDTH_TO
		#DEFINE __SET_MEMOWIDTH_TO TO 1024
	#ENDIF
	#IFNDEF __SET_MULTILOCKS
		#DEFINE __SET_MULTILOCKS ON
	#ENDIF
	#IFNDEF __SET_NEAR
		#DEFINE __SET_NEAR ON
	#ENDIF
	#IFNDEF __SET_NOTIFY
		#DEFINE __SET_NOTIFY ON
	#ENDIF
	#IFNDEF __SET_NULL
		#DEFINE __SET_NULL OFF
	#ENDIF
	#IFNDEF __SET_OPTIMIZE
		#DEFINE __SET_OPTIMIZE ON
	#ENDIF
	#IFNDEF __SET_ODOMETER_TO
		#DEFINE __SET_ODOMETER_TO TO 100
	#ENDIF
	#IFNDEF __SET_PALETTE
		#DEFINE __SET_PALETTE OFF
	#ENDIF
	#IFNDEF __SET_POINT_TO
		#DEFINE __SET_POINT_TO TO '.'
	#ENDIF
	#IFNDEF __SET_REFRESH_TO
		#DEFINE __SET_REFRESH_TO TO 0,5
	#ENDIF
	#IFNDEF __SET_REPROCESS_TO
		#DEFINE __SET_REPROCESS_TO TO 0
	#ENDIF
	#IFNDEF __SET_SAFETY
		#DEFINE __SET_SAFETY OFF
	#ENDIF
	#IFNDEF __SET_SECONDS
		#DEFINE __SET_SECONDS ON
	#ENDIF
	#IFNDEF __SET_SEPARATOR_TO
		#DEFINE __SET_SEPARATOR_TO TO ","
	#ENDIF
	#IFNDEF __SET_STATUS_BAR
		#DEFINE __SET_STATUS_BAR ON
	#ENDIF
	#IFNDEF __SET_SYSFORMATS
		#DEFINE __SET_SYSFORMATS ON
	#ENDIF
	#IFNDEF __SET_TALK
		#DEFINE __SET_TALK OFF
	#ENDIF
	#IFNDEF __SET_UNIQUE
		#DEFINE __SET_UNIQUE OFF
	#ENDIF
	#IFNDEF LOC_SBE_TRACKINFO_CAPTION
		#DEFINE LOC_SBE_TRACKINFO_CAPTION "TrackInfo"
	#ENDIF
	#IFNDEF LOC_SBE_TEXT_CAPTION
		#DEFINE LOC_SBE_TEXT_CAPTION "Information"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Menus (menuRightClick)
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_MENURIGHTCLICK_PRINT
		#DEFINE LOC_MENURIGHTCLICK_PRINT "\<Print"
	#ENDIF
	#IFNDEF LOC_MENURIGHTCLICK_COPY
		#DEFINE LOC_MENURIGHTCLICK_COPY "\<Copy"
	#ENDIF
	#IFNDEF LOC_MENURIGHTCLICK_CUT
		#DEFINE LOC_MENURIGHTCLICK_CUT "Cu\<t"
	#ENDIF
	#IFNDEF LOC_MENURIGHTCLICK_PASTE
		#DEFINE LOC_MENURIGHTCLICK_PASTE "\<Paste"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peSidebarElementFilterControl
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PESIDEBARELEMENTFILTERCONTROL_TOOLTIP
		#DEFINE LOC_PESIDEBARELEMENTFILTERCONTROL_TOOLTIP "Field to search in"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peWorkflowSheet
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEWORKFLOWSHEET_RESULTSIZE
		#DEFINE LOC_PEWORKFLOWSHEET_RESULTSIZE "This search returns " + m.lcAbout + ;
			" hits. Displaying all entries might take several minutes. Do you want to " + ;
			"continue?"
	#ENDIF
	#IFNDEF LOC_PEWORKFLOWSHEET_SAVEDEFAULTFILTER
		#DEFINE LOC_PEWORKFLOWSHEET_SAVEDEFAULTFILTER ;
			"Do you want to define the current filter as default filter for this form?"
	#ENDIF
	#IFNDEF LOC_PEWORKFLOWSHEET_TOOMANYRECORDS
		#DEFINE LOC_PEWORKFLOWSHEET_TOOMANYRECORDS ;
			"The external filter contains too many records. The search is limited to a subset!"
	#ENDIF
	#IFNDEF LOC_PEWORKFLOWSHEET_PLEASEWAIT
		#DEFINE LOC_PEWORKFLOWSHEET_PLEASEWAIT "Please wait..."
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peEditform
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEEDITFORM_NOPRIVILEGE
		#DEFINE LOC_PEEDITFORM_NOPRIVILEGE ;
			"You don't have the required rights to start this form"
	#ENDIF
	#IFNDEF LOC_PEEDITFORM_NORECORDLOCK
		#DEFINE LOC_PEEDITFORM_NORECORDLOCK ;
			"Another user is currently editing this record. Only one user can edit a " + ;
			"record at a time. Please wait until the record becomes available."
	#ENDIF
	#IFNDEF LOC_PEEDITFORM_ALLREQUIREDFIELDS
		#DEFINE LOC_PEEDITFORM_ALLREQUIREDFIELDS ;
			"Please fill out all required fields."
	#ENDIF

	*--------------------------------------------------------------------------------------
	* p222TaskhandlerForm
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_P222TASKHANDLERFORM_NOPRIVILEGE
		#DEFINE LOC_P222TASKHANDLERFORM_NOPRIVILEGE ;
			"You don't have the required rights to start this form"
	#ENDIF

	*--------------------------------------------------------------------------------------
	* SectionTitle
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_SECTIONTITLE_COUNT_ONE
		#DEFINE LOC_SECTIONTITLE_COUNT_ONE "1 record in query"
	#ENDIF
	#IFNDEF LOC_SECTIONTITLE_COUNT
		#DEFINE LOC_SECTIONTITLE_COUNT " records in query"
	#ENDIF

	*--------------------------------------------------------------------------------------
	* WorkflowDataSheet
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEWORKFLOWSHEET_REQUERY
		#DEFINE LOC_PEWORKFLOWSHEET_REQUERY ;
			"Query execution failed. Please try a different search criteria!"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peQuickFind
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEQUICKFIND_POPUPCAPTION
		#DEFINE LOC_PEQUICKFIND_POPUPCAPTION "Select item"
	#ENDIF
	#IFNDEF LOC_PEQUICKFIND_TOOMANYHITS
		#DEFINE LOC_PEQUICKFIND_TOOMANYHITS ;
			"Your search returned more than " + Transform(m.tuPar1) + " hits. " + ;
			"Only the first " + Transform(m.tuPar1) + " are shown. Please " + ;
			"refine your search to narrow down the result."
	#ENDIF

	*--------------------------------------------------------------------------------------
	* peFilterControlIO
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPEOBJECT
		#DEFINE LOC_PEFILTERCONTROLIO_TYPEOBJECT "Please choose a filter"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPECHAR
		#DEFINE LOC_PEFILTERCONTROLIO_TYPECHAR "Search for text" + Chr(13) + ;
			", = search for multiple alternative values" + Chr(13) + ;
			"* = matches any number of unknown characters" + Chr(13) + ;
			"? = matches a single unknown character"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPEDATE
		#DEFINE LOC_PEFILTERCONTROLIO_TYPEDATE "Search for a date" + Chr(13) + ;
			", = search for multiple alternative values" + Chr(13) + ;
			"< = field is less or equal" + Chr(13) + ;
			"> = field is equal or larger" + Chr(13) + ;
			"=TODAY = current date" + Chr(13) + ;
			"=TODAY(-10) = 10 days ago" + Chr(13) + ;
			"=MONTH = current month" + Chr(13) + ;
			"=Month(-10) = 10 months ago"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPENUMBER
		#DEFINE LOC_PEFILTERCONTROLIO_TYPENUMBER "Search for a number" + Chr(13) + ;
			", = search for multiple alternative values" + Chr(13) + ;
			"< = field is less or equal" + Chr(13) + ;
			"> = field is equal or larger"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPEGENERIC
		#DEFINE LOC_PEFILTERCONTROLIO_TYPEGENERIC ;
			", = search for multiple alternative values"
	#ENDIF

	*--------------------------------------------------------------------------------------
	* pcrSidebarFilter
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PCRSIDEBARFILTER_CLEAREXTERNAL
		#DEFINE LOC_PCRSIDEBARFILTER_CLEAREXTERNAL ;
			"Do you want to clear the external filter, as well?"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_REPLACEFILTER
		#DEFINE LOC_PCRSIDEBARFILTER_REPLACEFILTER ;
			"Do you want to replace the existing filter '"+m.tuPar1+"'?"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_DELETEFILTER
		#DEFINE LOC_PCRSIDEBARFILTER_DELETEFILTER ;
			"Do you want to delete filter '"+m.tuPar1+"'?"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSNULL
		#DEFINE LOC_PCRSIDEBARFILTER_HITSNULL ;
			"Enter a search term and click the Search button."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_NOHITSINV
		#DEFINE LOC_PCRSIDEBARFILTER_NOHITSINV ;
			"Enter a search term and click the Search button. Your last search did not match any records."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_NOHITS
		#DEFINE LOC_PCRSIDEBARFILTER_NOHITS "Your search did not match any records."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSONEINV
		#DEFINE LOC_PCRSIDEBARFILTER_HITSONEINV ;
			"Enter a search term and click the Search button. Your last search returned one match " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSONE
		#DEFINE LOC_PCRSIDEBARFILTER_HITSONE ;
			"Found one matching record in " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSINV
		#DEFINE LOC_PCRSIDEBARFILTER_HITSINV ;
			"Enter a search term and click the Search button. Your last search returned " + Alltrim(Str(m.lnHits)) + ;
				" records in " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITS
		#DEFINE LOC_PCRSIDEBARFILTER_HITS ;
			Alltrim(Str(m.lnHits)) + " records found in " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_BUTTONCLEAR
		#DEFINE LOC_PCRSIDEBARFILTER_BUTTONCLEAR "C\<lear"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_BUTTONSEARCH
		#DEFINE LOC_PCRSIDEBARFILTER_BUTTONSEARCH "\<Search"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* ioMultipleValuesPopup
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_IOMULTIPLEVALUESPOPUP_BUTTONSAVE
		#DEFINE LOC_IOMULTIPLEVALUESPOPUP_BUTTONSAVE "\<Save"
	#ENDIF