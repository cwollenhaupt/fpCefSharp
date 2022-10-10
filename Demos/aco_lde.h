*====================================================================
* Diese Datei enthält alle deutschen Sprachdefinitionen, die in
* Acodey verwendet werden. Wenn Sie eine deutschsprachige Anwendung
* erstellen wollen, setzen Sie die Eigenschaft __ACODEY_LANGUAGE auf
* "de" (Standardeinstellung). Ändern Sie niemals diese Datei, da
* sie bei zukünftigen Versionen angepaßt wird.
*====================================================================

	#UNDEF __INCLUDE_OK

	#IFNDEF LOC_X5C_FileExists
		#DEFINE LOC_X5C_FileExists "existiert bereits. Überschreiben?"
	#ENDIF
	#IFNDEF LOC_ERR_Error
		#DEFINE LOC_ERR_Error "Fehler: "
	#ENDIF
	#IFNDEF LOC_ERR_Method
		#DEFINE LOC_ERR_Method "Methode: "
	#ENDIF
	#IFNDEF LOC_ERR_Line
		#DEFINE LOC_ERR_Line "Zeile: "
	#ENDIF
	#IFNDEF LOC_ERR_RuntimeError
		#DEFINE LOC_ERR_RuntimeError "Ablauffehler: "
	#ENDIF
	#IFNDEF LOC_IONAV_RevertQuestion
		#DEFINE LOC_IONAV_RevertQuestion "Wollen Sie alle Änderungen verwerfen?"
	#ENDIF
	#IFNDEF LOC_IONAV_SaveQuestion
		#DEFINE LOC_IONAV_SaveQuestion "Wollen Sie alle Änderungen speichern?"
	#ENDIF
	#IFNDEF LOC_IONAV_DeleteQuestion
		#DEFINE LOC_IONAV_DeleteQuestion "Sind Sie sicher, daß Sie diesen Eintrag löschen wollen?"
	#ENDIF
	#IFNDEF LOC_IONAV_SaveRevertQuestion
		#DEFINE LOC_IONAV_SaveRevertQuestion "Wollen Sie die Änderungen speichern?"
	#ENDIF
	#IFNDEF LOC_DATAB_InvalidValue
		#DEFINE LOC_DATAB_InvalidValue "Ungültiger Wert!"
	#ENDIF
	#IFNDEF LOC_DATAB_CorrectAndTryAgain
		#DEFINE LOC_DATAB_CorrectAndTryAgain "Bitte korrigieren Sie diesen Eintrag und versuchen Sie erneut zu speichern."
	#ENDIF
	#IFNDEF LOC_DATAB_RecordLockErrorMessage
		#DEFINE LOC_DATAB_RecordLockErrorMessage "Der Datensatz konnte nicht gesperrt werden."
	#ENDIF
	#IFNDEF LOC_DATAB_UpdateError
		#DEFINE LOC_DATAB_UpdateError "Beim Speichern trat ein Fehler auf. Korrigieren Sie die Daten und versuchen Sie erneut zu speichern."
	#ENDIF
	#IFNDEF LOC_ERR_Suspend
		#DEFINE LOC_ERR_Suspend "Programmablauf unterbrechen?"
	#ENDIF
	#IFNDEF LOC_DATAB_RecordValidationErrorMessage
		#DEFINE LOC_DATAB_RecordValidationErrorMessage "Die Gültigkeitsregel für Datensätze wurde verletzt."
	#ENDIF
	#IFNDEF LOC_DATAB_UpdateConflict
		#DEFINE LOC_DATAB_UpdateConflict "Ein anderer Anwender hat zwischenzeitlich die von Ihnen bearbeiteten Daten ebenfalls geändert."
	#ENDIF
	#IFNDEF LOC_DATAB_FLockInTransaction
		#DEFINE LOC_DATAB_FLockInTransaction "Zugriff auf die Tabelle beim Versuch verweigert, diese zu sperren."
	#ENDIF
	#IFNDEF LOC_DATAB_UniquenessViolated
		#DEFINE LOC_DATAB_UniquenessViolated "Die Eindeutigkeit des Indizes wurde verletzt."
	#ENDIF
	#IFNDEF LOC_DATAB_AddTrigger
		#DEFINE LOC_DATAB_AddTrigger "Dieser Datensatz enthält ungültige Bezüge. Wahrscheinlich haben Sie ein Pflichtfeld nicht ausgefüllt."
	#ENDIF
	#IFNDEF LOC_DATAB_DeleteTrigger
		#DEFINE LOC_DATAB_DeleteTrigger "Dieser Satz kann nicht gelöscht werden, da noch Daten existieren, die von diesem Satz abhängig sind."
	#ENDIF
	#IFNDEF LOC_DATAB_EditTrigger
		#DEFINE LOC_DATAB_EditTrigger "Folgedaten können nicht aktualisiert werden. Wahrscheinlich befinden sich diese gerade selbst in der Bearbeitung! Warten Sie, bis die Bearbeitung des anderen Datensatzes abgeschlossen ist."
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
		#DEFINE __SET_CURRENCY_TO TO 'DM'
	#ENDIF
	#IFNDEF __SET_DATE_TO
		#DEFINE __SET_DATE_TO TO GERMAN
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
		#DEFINE __SET_FDOW_TO TO 2
	#ENDIF
	#IFNDEF __SET_FIELDS
		#DEFINE __SET_FIELDS OFF
	#ENDIF
	#IFNDEF __SET_FIXED
		#DEFINE __SET_FIXED OFF
	#ENDIF
	#IFNDEF __SET_FWEEK_TO
		#DEFINE __SET_FWEEK_TO TO 2
	#ENDIF
	#IFNDEF __SET_HEADINGS
		#DEFINE __SET_HEADINGS ON
	#ENDIF
	#IFNDEF __SET_HOURS_TO
		#DEFINE __SET_HOURS_TO TO 24
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
		#DEFINE __SET_MARK_TO TO '.'
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
		#DEFINE __SET_POINT_TO TO ','
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
		#DEFINE __SET_SEPARATOR_TO TO "."
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
		#DEFINE LOC_SBE_TRACKINFO_CAPTION "letzte Änderungen"
	#ENDIF
	#IFNDEF LOC_SBE_TEXT_CAPTION
		#DEFINE LOC_SBE_TEXT_CAPTION "Information"
	#ENDIF

	*--------------------------------------------------------------------------------------
	* Menus (menuRightClick)
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_MENURIGHTCLICK_PRINT
		#DEFINE LOC_MENURIGHTCLICK_PRINT "\<Drucken"
	#ENDIF
	#IFNDEF LOC_MENURIGHTCLICK_COPY
		#DEFINE LOC_MENURIGHTCLICK_COPY "\<Kopieren"
	#ENDIF
	#IFNDEF LOC_MENURIGHTCLICK_CUT
		#DEFINE LOC_MENURIGHTCLICK_CUT "A\<usschneiden"
	#ENDIF
	#IFNDEF LOC_MENURIGHTCLICK_PASTE
		#DEFINE LOC_MENURIGHTCLICK_PASTE "E\<infügen"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peSidebarElementFilterControl
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PESIDEBARELEMENTFILTERCONTROL_TOOLTIP
		#DEFINE LOC_PESIDEBARELEMENTFILTERCONTROL_TOOLTIP "Suchfeld"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peWorkflowSheet
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEWORKFLOWSHEET_RESULTSIZE
		#DEFINE LOC_PEWORKFLOWSHEET_RESULTSIZE "Diese Suche ergibt " + m.lcAbout + ;
			" Datensätze. Das Darstellen dieser Menge von Datensätzen kann einige " + ;
			"Zeit in Anspruch nehmen. Wollen Sie dieses Suche wirklich so anzeigen lassen?"
	#ENDIF
	#IFNDEF LOC_PEWORKFLOWSHEET_SAVEDEFAULTFILTER
		#DEFINE LOC_PEWORKFLOWSHEET_SAVEDEFAULTFILTER ;
			"Wollen Sie den aktuellen Filter als Standardfilter verwenden?"
	#ENDIF
	#IFNDEF LOC_PEWORKFLOWSHEET_TOOMANYRECORDS
		#DEFINE LOC_PEWORKFLOWSHEET_TOOMANYRECORDS ;
			"Der externe Filter enthält zu viele Einträge. Nur ein Teil der Einträge " + ;
			"wird bei der Suche berücksichtigt!"
	#ENDIF
	#IFNDEF LOC_PEWORKFLOWSHEET_PLEASEWAIT
		#DEFINE LOC_PEWORKFLOWSHEET_PLEASEWAIT "Bitte gedulden Sie sich einen Moment..."
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peEditform
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEEDITFORM_NOPRIVILEGE
		#DEFINE LOC_PEEDITFORM_NOPRIVILEGE ;
			"Formular kann wegen fehlender Berechtigung nicht gestartet werden."
	#ENDIF
	#IFNDEF LOC_PEEDITFORM_NORECORDLOCK
		#DEFINE LOC_PEEDITFORM_NORECORDLOCK ;
			"Dieser Datensatz wird zurzeit von einem anderen Benutzer bearbeitet. Bitte versuchen Sie es später erneut."
	#ENDIF
	#IFNDEF LOC_PEEDITFORM_ALLREQUIREDFIELDS
		#DEFINE LOC_PEEDITFORM_ALLREQUIREDFIELDS ;
			"Bitte füllen Sie alle erforderlichen Felder."
	#ENDIF

	*--------------------------------------------------------------------------------------
	* p222TaskhandlerForm
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_P222TASKHANDLERFORM_NOPRIVILEGE
		#DEFINE LOC_P222TASKHANDLERFORM_NOPRIVILEGE ;
			"Formular kann wegen fehlender Berechtigung nicht gestartet werden."
	#ENDIF

	*--------------------------------------------------------------------------------------
	* SectionTitle
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_SECTIONTITLE_COUNT_ONE
		#DEFINE LOC_SECTIONTITLE_COUNT_ONE "1 Datensatz in Abfrage"
	#ENDIF
	#IFNDEF LOC_SECTIONTITLE_COUNT
		#DEFINE LOC_SECTIONTITLE_COUNT " Datensätze in Abfrage"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* WorkflowDataSheet
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEWORKFLOWSHEET_REQUERY
		#DEFINE LOC_PEWORKFLOWSHEET_REQUERY ;
			"Die Anfrage konnte nicht ausgeführt werden. Bitte führen Sie die Anfrage mit " + ;
			"einer anderen Suchbedingungen erneut aus!"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* peQuickFind
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEQUICKFIND_POPUPCAPTION
		#DEFINE LOC_PEQUICKFIND_POPUPCAPTION "Eintrag wählen"
	#ENDIF
	#IFNDEF LOC_PEQUICKFIND_TOOMANYHITS
		#DEFINE LOC_PEQUICKFIND_TOOMANYHITS ;
			"Ihre Anfrage lieferte mehr als " + Transform(m.tuPar1) + " Treffer. " + ;
			"Nur die ersten " + Transform(m.tuPar1) + " Treffer werden angezeigt. " + ;
			"Bitte schränken Sie den Suchbereich ein."
	#ENDIF

	*--------------------------------------------------------------------------------------
	* peFilterControlIO
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPEOBJECT
		#DEFINE LOC_PEFILTERCONTROLIO_TYPEOBJECT "Bitte wählen Sie einen Filter"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPECHAR
		#DEFINE LOC_PEFILTERCONTROLIO_TYPECHAR "Nach Text suchen" + Chr(13) + ;
			", = Nach mehreren Werten gleichzeitig suchen" + Chr(13) + ;
			"* = Platzhalter für beliebige Zeichen" + Chr(13) + ;
			"? = Platzhalter für ein einziges beliebiges Zeichen"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPEDATE
		#DEFINE LOC_PEFILTERCONTROLIO_TYPEDATE "Nach einem Datum suchen" + Chr(13) + ;
			", = Nach mehreren Werten gleichzeitig suchen" + Chr(13) + ;
			"< = Feld ist kleiner oder gleich" + Chr(13) + ;
			"> = Feld ist größer oder gleich" + Chr(13) + ;
			"=HEUTE = heutiges Datum" + Chr(13) + ;
			"=HEUTE(-10) = vor zehn Tagen" + Chr(13) + ;
			"=MONAT = aktueller Monat" + Chr(13) + ;
			"=MONAT(-10) = vor zehn Monaten"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPENUMBER
		#DEFINE LOC_PEFILTERCONTROLIO_TYPENUMBER "Nach einer Zahl suchen" + Chr(13) + ;
			", = Nach mehreren Werten gleichzeitig suchen" + Chr(13) + ;
		"< = Feld ist kleiner oder gleich" + Chr(13) + ;
			"> = Feld ist größer oder gleich"
	#ENDIF
	#IFNDEF LOC_PEFILTERCONTROLIO_TYPEGENERIC
		#DEFINE LOC_PEFILTERCONTROLIO_TYPEGENERIC ;
			", = Nach mehreren Werten gleichzeitig suchen"
	#ENDIF

	*--------------------------------------------------------------------------------------
	* pcrSidebarFilter
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_PCRSIDEBARFILTER_CLEAREXTERNAL
		#DEFINE LOC_PCRSIDEBARFILTER_CLEAREXTERNAL ;
			"Möchten sie den externen Filter auch löschen?"
	#ENDIF
		#IFNDEF LOC_PCRSIDEBARFILTER_REPLACEFILTER
		#DEFINE LOC_PCRSIDEBARFILTER_REPLACEFILTER ;
			"Möchten Sie den bestehenden Filter '"+m.tuPar1+"' überschreiben?"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_DELETEFILTER
		#DEFINE LOC_PCRSIDEBARFILTER_DELETEFILTER ;
			"Möchten Sie den Filter '"+m.tuPar1+"' löschen?"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSNULL
		#DEFINE LOC_PCRSIDEBARFILTER_HITSNULL ;
			"Bitte geben Sie einen Suchbegriff ein und klicken Sie auf Suchen."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_NOHITSINV
		#DEFINE LOC_PCRSIDEBARFILTER_NOHITSINV ;
			"Bitte geben Sie einen Suchbegriff ein und klicken sie auf Suchen. Ihre letzte Suchanfrage lieferte kein Ergebnis."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_NOHITS
		#DEFINE LOC_PCRSIDEBARFILTER_NOHITS "Ihre Suchanfrage lieferte kein Ergebnis"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSONEINV
		#DEFINE LOC_PCRSIDEBARFILTER_HITSONEINV ;
			"Bitte geben Sie einen Suchbegriff ein und klicken Sie auf Suchen. Ihre letzte Suchanfrage lieferte Treffer in " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSONE
		#DEFINE LOC_PCRSIDEBARFILTER_HITSONE ;
			"Ein Eintrag gefunden in " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITSINV
		#DEFINE LOC_PCRSIDEBARFILTER_HITSINV ;
			"Bitte geben Sie einen Suchbegriff ein und klicken Sie auf Suchen. Ihre letzte Suchanfrage lieferte " + Alltrim(Str(m.lnHits)) + ;
				" Einträge in " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_HITS
		#DEFINE LOC_PCRSIDEBARFILTER_HITS ;
			Alltrim(Str(m.lnHits)) + " Einträge gefunden in " + m.lcDuration + "."
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_BUTTONCLEAR
		#DEFINE LOC_PCRSIDEBARFILTER_BUTTONCLEAR "\<Löschen"
	#ENDIF
	#IFNDEF LOC_PCRSIDEBARFILTER_BUTTONSEARCH
		#DEFINE LOC_PCRSIDEBARFILTER_BUTTONSEARCH "\<Suchen"
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* ioMultipleValuesPopup
	*--------------------------------------------------------------------------------------
	#IFNDEF LOC_IOMULTIPLEVALUESPOPUP_BUTTONSAVE
		#DEFINE LOC_IOMULTIPLEVALUESPOPUP_BUTTONSAVE "\<Übernehmen"
	#ENDIF

	
