*====================================================================
*
* Dies ist die Haupt-Include Datei für Acodey. Sie bindet alle
* anderen Include-Dateien ein, die von Acodey verwendet werden. 
* Immer, wenn Sie Konstanten von Acodey benötigten, binden Sie diese
* Datei in Ihrer Klasse oder Prozedur ein.
*
* Machen Sie keine Änderungen in dieser Datei, da sie durch Updates
* überschrieben wird. Alle Konstanten können Sie in dem Intermediate
* Layern anpassen. Die Standarddatei dafür ist die Datei iAcodey.H
*
* WICHTIG: Wenn Sie ein Acodey-Projekt kompilieren, müssen Sie im
*          Projektverzeichnis sein, oder aber einen Pfad auf das
*          Headerverzeichnis haben, andernfalls werden Header-Dateien
*          von Visual FoxPro nicht gefunden.
*
*====================================================================

	*-----------------------------------------------------------------
	* Die Namen aller Headerdateien werden hier als Konstanten abge-
	* legt. Einmal als "Header\Datei.H" und einmal als "Datei.H". Da
	* alle Namen hier definiert werden, können wir diese problemlos
	* umbenennen.
	*-----------------------------------------------------------------
	*:SECTION Headerfiles_Defines
		#DEFINE __FILE_ACO_ERR  #INCLUDE Aco_Err.H
		#DEFINE __FILE_IACODEY  #INCLUDE iAcodey.H
		#DEFINE __FILE_IACODEYD #INCLUDE iAcodeyD.H
		#DEFINE __FILE_ACO_LEN  #INCLUDE Aco_Len.H
		#DEFINE __FILE_ACO_LDE  #INCLUDE Aco_Lde.H
	*:ENDSECTION
	
	*-----------------------------------------------------------------
	* Der Name der Hauptprozeduredatei wird hier abgelegt. Sie kann
	* auch leer sein. Dann wird keine Prozedurdatei geladen und Sie
	* müssen dies entweder selber tun, oder aber alle Prozeduren im
	* Pfad verfügbar haben.
	*-----------------------------------------------------------------
	*:SECTION GlobalProcedureFile
		#DEFINE __GLOBALPROCEDUREFILE Acodey
	*:ENDSECTION

	*-----------------------------------------------------------------
	* Die Namen aller FLL-Biblitoheken ablegen.
	*-----------------------------------------------------------------
	*:SECTION FLL_Libraries
		#DEFINE __FILE_FLL_ACODEY Acodey.FLL
		#DEFINE __FILE_FLL_FOXTOOLS FoxTools.Fll
	*:ENDSECTION
	
	*-----------------------------------------------------------------
	* Die Namen der Prozeduren in dem Global Procedure File sind 
	* ebenfalls einstellbar, mit Ausnahme der Prozeduren, die für 
	* eine Kompatibilität mit alten Programmversionen sorgen. Die hier
	* aufgeführten x5_ Funktionen haben ein etwas anderes Interface
	* als die Originalfunktionen aus den neuen VFP Versionen.
	*-----------------------------------------------------------------
	*:SECTION Procedure_Names
		#DEFINE GPF_ADDOBJECTX AddObjectX
		#DEFINE GPF_DecodeLC DecodeLC
		#DEFINE GPF_DecodeALC DecodeALC
		#DEFINE GPF_GetGlobalService GetGlobalService
		#DEFINE GPF_GetGlobalServiceBroker GetGlobalServiceBroker
		#DEFINE GPF_Service Service
		#DEFINE GPF_INITREFERENCETRACKING initreferencetracking 
		#DEFINE GPF_NewObjectX NewObjectX
		#DEFINE GPF_RemoveGSB RemoveGSB
		#DEFINE GPF_PrgHome PrgHome
		#DEFINE GPF_IsValidReference IsValidReference
		#DEFINE GPF_x5_PrgLevel x5_PrgLevel
		#DEFINE GPF_x5_CompObj x5_CompObj
		#DEFINE GPF_x5_ALines x5_ALines
		#DEFINE GPF_ReduceX ReduceX
		#DEFINE GPF_CleanUpEmpty CleanUpEmpty
	*:ENDSECTION
	
	*:IFFEAT ActiveDebugging
	*-----------------------------------------------------------------
	* Konstanten für die möglichen Werte, die __DEBUGLEVEL annehmen 
	* kann.
	*-----------------------------------------------------------------
	#DEFINE __DEBUG_NONE                                             0
	#DEFINE __DEBUG_REGULAR                                          1
	#DEFINE __DEBUG_ADVANCED                                         2
	#DEFINE __DEBUG_ACTIVE                                           3
	*:ENDFEAT
	
	*-----------------------------------------------------------------
	* Konstanten für die möglichen Werte für __CASCADING_DESTROY.
	* 
	*  __CD_ALWAYS      Es wird immer ein Cascading Destroy durchge-
	*                   führt. 
	*
	*  __CD_NEVER       Es wird kein Cascading Destroy durchgeführt
	*                   und der Code wird auch nicht in die Applika-
	*                   tion eingebunden.
	*
	*  __CD_DEPENDS     Das Cascading Destroy wird über das Property
	*                   lCascadingDestroy gesteuert, das standardmäßig
	*                   auf .T. gesetzt ist. Für die Komponenten, bei
	*                   denen kein Cascading Destroy notwendig ist, 
	*                   können Sie diese Eigenschaft dann auf .F. set-
	*                   zen, bzw. dies in den Basisklassen pauschal 
	*                   für alle Komponenten deaktivieren und bei Be-
	*                   darf wieder aktivieren.
	*
	*-----------------------------------------------------------------
	#DEFINE __CD_ALWAYS                                              0
	#DEFINE __CD_NEVER                                               1
	#DEFINE __CD_DEPENDS                                             2

	*-----------------------------------------------------------------
	* Alle Konstanten zur Rückwärtskompatibilität können drei Werte 
	* annehmen:
	*
	* __BACKWARD_YES   Die Rückwärtskompatibilität für dieses spe-
	*                  zielle Feature bleibt erhalten. Dies ist der 
	*                  Standardwert. Wenn Sie die Rückwärtskompatibi-
	*                  lität ausschalten wollen, was im Regelfall
	*                  einen Geschwindigkeits- und Größenvorteil
	*                  bringt, können Sie entweder die Konstante än-
	*                  dern, oder aber über der Integrator den Code
	*                  komplett entfernen lassen.
	*-----------------------------------------------------------------
	#DEFINE __BACKWARD_YES                                           0
	#DEFINE __BACKWARD_NO                                            1
	*:IFFEAT ActiveDebugging
	#DEFINE __BACKWARD_WARN                                          2
	*:ENDFEAT
	
	*-----------------------------------------------------------------
	* Defines all valid characters that can be used in a several
	* expression. Although umlauts are valid for VFP as well, we skip
	* them, because they might cause conflicts later on.
	*-----------------------------------------------------------------
	#DEFINE __VALID_NAME_CHARS                         "1234567890_"+;
	            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
	#DEFINE __VALID_LC_CHARS __VALID_NAME_CHARS + ";.\:|"

	*-----------------------------------------------------------------
	* Um eine Fehlermeldung auszugeben, wird die Unterroutine Aco_Err
	* verwendent, die als Parameter __ERRMSG die Fehlermeldung erhält.
	* Diese Unterroutine kümmert sich um den ganzen Rest und wird 
	* mittels #INCLUDE aufgerufen.
	* Achtung: __SHOWERROR darf erst nach dem Einbinden des Interme-
	*          diate Layers verwendet werden, da der Anwender noch die
	*          Möglichkeit haben muß, einige Parameter zu definieren.
	*-----------------------------------------------------------------
	#DEFINE __SHOWERROR __FILE_ACO_ERR
	#DEFINE __ERRMSG #DEFINE ___ERRMSG 

	*-----------------------------------------------------------------
	* VFP Versionen. Diese Konstanten haben folgende Bedeutung.
	*
	* __VFP5            VFP 5 oder niedriger. Versionen unterhalb von
	*                   VFP 5 werden allerdings nicht mehr unter-
	*                   stützt.
	* __VFP6            VFP 6 oder höher.
	* __VFP7            VFP 7 oder höher.
	* __VFP8            VFP 8 oder höher.
	* __VFP9            VFP 9 oder höher.
	* __VFP5ONLY        nur VFP 5
	* __VFP6ONLY        nur VFP 6
	* __VFP7ONLY        nur VFP 7
	* __VFPX5C          alle Versionen bis VFP 5 (Kompatibilität)
	* __VFPX6C          alle Versionen bis VFP 6 (Kompatibilität)
	* __VFPSUPP         alle unterstützten Versionen von VFP.
	* __VFP6SP3         VFP 6, SP 3 oder höher. Diese Konstante ist
	*                   notwendig, da SP 3 einige neue Klassen und
	*                   Befehle einführte.
	* __VFP6SP4         VFP 6, SP 4 oder höher. Diese Konstante ist
	*                   notwendig, da SP 4 einige neue Befehle ein-
	*                   führte.
	* __VFP6SP5         VFP 6, SP 5 oder höher
	* __VFP7SP1         VFP 7, SP 1 oder höher
	* __VFP8SP1         VFP 8, SP 1 oder höher
	*
	*-----------------------------------------------------------------
	#DEFINE __VFPSUPP (not "03.00.00" $ Version())

	#DEFINE __VFP5 (TYPE("Version(4)") == "U")
	#DEFINE __VFP5ONLY (__VFP5 and not "03.00.00" $ Version())

	#DEFINE __VFP6 (TYPE("Version(4)") == "C")
	#DEFINE __VFP6ONLY (__VFP6 and Left(Version(4),5) == "06.00")
	#DEFINE __VFP6SP3 (__VFP6 and Version(4) >= "06.00.8492.00")
	#DEFINE __VFP6SP4 (__VFP6 and Version(4) >= "06.00.8862.00")
	#DEFINE __VFP6SP5 (__VFP6 and Version(4) >= "06.00.8961.00")

	#DEFINE __VFP7 (__VFP6 and Left(Version(4),5) >= "07.00")
	#DEFINE __VFP7ONLY (__VFP6 and Left(Version(4),5) == "07.00")
	#DEFINE __VFP7SP1 (__VFP7 and Version(4) >= "07.00.0000.9262")

	#DEFINE __VFP8 (__VFP6 and Left(Version(4),5) >= "08.00")
	#DEFINE __VFP8ONLY (__VFP6 and Left(Version(4),5) == "08.00")
	#DEFINE __VFP8SP1 (__VFP8 and Version(4) >= "08.00.0000.3117")

	#DEFINE __VFP9 (__VFP6 and Left(Version(4),5) >= "09.00")
	#DEFINE __VFP9ONLY (__VFP6 and Left(Version(4),5) == "09.00")

	#DEFINE __VFPX5C __VFP5ONLY
	#DEFINE __VFPX6C (__VFP5ONLY or __VFP6ONLY)
	#DEFINE __VFPX7C (__VFP5ONLY or __VFP6ONLY or __VFP7ONLY)
	#DEFINE __VFPX8C (__VFP5ONLY or __VFP6ONLY or __VFP7ONLY or __VFP8ONLY)
	
	*-----------------------------------------------------------------
	* Die nachfolgenden DEFINEs regeln die Konvertierung der Ersatz-
	* funktionen von älteren VFP-Produkten. Dadurch daß sie beim 
	* Kompilieren umbenannt werden, können auch neuere VFP Versionen
	* die APPs ausführen, die für die alte Version kompiliert worden
	* sind, ohne daß sie einen Fehler liefern, weil angeblich eine
	* Funktion nicht gefunden werden können. Diese Funktionen können
	* nicht umbenannt werden (noch nicht).
	*-----------------------------------------------------------------
	#DEFINE GPF_X5C_INT_GETPATHANDNAME x5c_INT_GetPathAndName
	#IF __VFP5
		#DEFINE VarType                x5c_Vartype
		#DEFINE JustFName              x5c_JustFName
		#DEFINE JustPath               x5c_JustPath
		#DEFINE JustExt                x5c_JustExt
		#DEFINE JustStem               x5c_JustStem
		#DEFINE ForceExt               x5c_ForceExt
		#DEFINE AddBS                  x5c_AddBS
		#DEFINE StrToFile              x5c_StrToFile
		#DEFINE FileToStr              x5c_FileToStr
		#DEFINE NewObject              x5c_NewObject
	#ENDIF

	*-----------------------------------------------------------------
	* Gibt an, in welcher Umgebung wir uns gerade befinden.
	*
	* __VFPENV_RUNTIME    Laufzeitumgebung, die einige Features nicht
	*                     bereitstellt.
	* __VFPENV_DEVELOP    Entwicklungsumgebung
	*
	*-----------------------------------------------------------------
	#DEFINE __VFPENV_RUNTIME (Version(2) == 0)
	#DEFINE __VFPENV_DEVELOP (not Version(2) == 0)

	*-----------------------------------------------------------------
	* Fehlernummern in VFP
	* (...) Bislang noch nicht komplett
	*-----------------------------------------------------------------
	#DEFINE ERR_NO_ERROR                                             0
	#DEFINE ERR_FILE_NOT_FOUND                                       1
	#DEFINE ERR_FILE_IN_USE                                          3
	#DEFINE ERR_CONTINUE_WITHOUT_LOCATE                             42
	#DEFINE ERR_TYPE_MISMATCH                                      107
	#DEFINE ERR_RECORD_IN_USE                                      109
	#DEFINE ERR_USERDEFINED                                       1098
	#DEFINE ERR_TOO_FEW_ARGUMENTS                                 1229
	#DEFINE ERR_MISSING_OPERAND                                   1231
	#DEFINE ERR_DIVISION_BY_ZERO                                  1307
	#DEFINE ERR_CONNECTIVITY                                      1526
	#DEFINE ERR_TRIGGER_FAILED                                    1539
	#DEFINE ERR_FIELD_NO_NULL_VALUES                              1581
	#DEFINE ERR_FIELD_VALIDATION_VIOLATED                         1582
	#DEFINE ERR_RECORD_VALIDATION_VIOLATED                        1583
	#DEFINE ERR_UPDATE_CONFLICT                                   1585
	#DEFINE ERR_FLOCK_IN_TRANSACTION                              1594
	#DEFINE ERR_FILE_ACCESS_DENIED                                1705
	#DEFINE ERR_UNIQUENESS_VIOLATED                               1884
	#DEFINE ERR_NO_SETFOCUS_IN_VALID                              2012
	
	*-----------------------------------------------------------------
	* Fehlernummern für die LLFF (Low Level File Functions). Diese
	* werden durch FERROR() zurückgegeben.
	*-----------------------------------------------------------------
	#DEFINE FERROR_NO_ERROR                                          0
	#DEFINE FERROR_FILE_NOT_FOUND                                    2
	#DEFINE FERROR_TOO_MANY_FILES                                    4
	#DEFINE FERROR_ACCESS_DENIED                                     5
	#DEFINE FERROR_INVALID_HANDLE                                    6
	#DEFINE FERROR_OUT_OF_MEMORY                                     8
	#DEFINE FERROR_SEEK_ERROR                                       25
	#DEFINE FERROR_DISK_FULL                                        29
	#DEFINE FERROR_ERROR_OPEN_FILE                                  31

	*-----------------------------------------------------------------
	* Parameter für die ZOrder() Methode
	*-----------------------------------------------------------------
	#DEFINE ZORDER_BRINGTOFRONT                                      0
	#DEFINE ZORDER_SENDTOBACK                                        1
	
	*-----------------------------------------------------------------
	* Datentypen verwendet by TYPE(), VARTYPE(), AFIELDS(), usw.
	*-----------------------------------------------------------------
	#DEFINE T_CHARACTER                                            "C"
	#DEFINE T_NUMERIC                                              "N"
	#DEFINE T_DOUBLE                                               "B"
	#DEFINE T_DATE                                                 "D"
	#DEFINE T_DATETIME                                             "T"
	#DEFINE T_MEMO                                                 "M"
	#DEFINE T_GENERAL                                              "G"
	#DEFINE T_OBJECT                                               "O"
	#DEFINE T_SCREEN                                               "S"
	#DEFINE T_LOGICAL                                              "L"
	#DEFINE T_CURRENCY                                             "Y"
	#DEFINE T_UNDEFINED                                            "U"
	#DEFINE T_OPTIONAL                                             "L"
	#DEFINE T_INTEGER                                              "I"
	#DEFINE T_FLOAT                                                "F"
	#DEFINE T_NULL                                                 "X"
	#DEFINE T_VARCHAR                                              "V"
	#DEFINE T_ARRAY                                                "A"
	#DEFINE T_COLLECTION                                           "C"
	#DEFINE T_VARBINARY                                            "Q"
	#DEFINE T_BLOB                                                 "W"
	#DEFINE T_XML                                 T_CHARACTER+T_OBJECT

	*-----------------------------------------------------------------
	* Der Sinn der folgenden Konstanten ist derzeit unklar und Micro-
	* soft hat dazu keinerlei Informationen. Sie stammen aus der 
	* FoxPro.H und waren mit "QueryUnload" dokumentiert. Allerdings
	* hat QueryUnload keinen Parameter und ReleaseType angeblich
	* andere Werte.
	*-----------------------------------------------------------------
	#DEFINE FORM_CONTROLMENU                                         0
	#DEFINE FORM_CODE                                                1
	#DEFINE APP_WINDOWS                                              2
	#DEFINE APP_TASKMANAGER                                          3
	#DEFINE FORM_MDIFORM                                             4
	
	*-----------------------------------------------------------------
	* Die Spalten des von AVCXCLASSES() zurückgegebenen Arrays.
	*-----------------------------------------------------------------
	#DEFINE AVCX_CLASS                                               1
	#DEFINE AVCX_BASECLASS                                           2
	#DEFINE AVCX_PARENTCLASS                                         3
	#DEFINE AVCX_PARENTCLASSLIB                                      4
	#DEFINE AVCX_CLASSICON                                           5
	#DEFINE AVCX_CONTAINERICON                                       6
	#DEFINE AVCX_SCALEMODE                                           7
	#DEFINE AVCX_CLASSDESCRIPTION                                    8
	#DEFINE AVCX_INCLUDEFILE                                         9
	#DEFINE AVCX_USERINFO                                           10
	#DEFINE AVCX_OLEPUBLIC                                          11

	*-----------------------------------------------------------------
	* Werte die die zweite Spalte des aCommand Arrays annehmen kann,
	* daß an CommandTargetQuery übergeben wird.
	*-----------------------------------------------------------------
	#DEFINE CMDF_NOTSUPPORTED                                        0
	#DEFINE CMDF_SUPPORTED                                           1
	#DEFINE CMDF_ENABLED                                             2
	#DEFINE CMDF_LATCHED                                             4
	#DEFINE CMDF_NINCHED                                             8

	*-----------------------------------------------------------------
	* Werte von nCommandTextFlag (2. Parameter) der Methode
	* CommandTargetQuery eines ActiveDocument Objektes.
	*-----------------------------------------------------------------
	#DEFINE CMDTEXTF_NONE                                            0
	#DEFINE CMDTEXTF_NAME                                            1
	#DEFINE CMDTEXTF_STATUS                                          2
	
	*-----------------------------------------------------------------
	* nCommandID für das CommandTargetExec Ereignis eines Active
	* Documents und auch in der ersten Spalte von CommandTargetQuery
	* verwendet. Die gleichen Konstanten werden auch von anderen
	* Funktionen und Methoden verwendet, zum Beispiel von ExecWB()
	* des Internet Explorers.
	*-----------------------------------------------------------------
	#DEFINE CMDID_OPEN                                               1
	#DEFINE CMDID_NEW                                                2
	#DEFINE CMDID_SAVE                                               3
	#DEFINE CMDID_SAVEAS                                             4
	#DEFINE CMDID_SAVECOPYAS                                         5
	#DEFINE CMDID_PRINT                                              6
	#DEFINE CMDID_PRINTPREVIEW                                       7
	#DEFINE CMDID_PAGESETUP                                          8
	#DEFINE CMDID_SPELL                                              9
	#DEFINE CMDID_PROPERTIES                                        10
	#DEFINE CMDID_CUT                                               11
	#DEFINE CMDID_COPY                                              12
	#DEFINE CMDID_PASTE                                             13
	#DEFINE CMDID_PASTESPECIAL                                      14
	#DEFINE CMDID_UNDO                                              15
	#DEFINE CMDID_REDO                                              16
	#DEFINE CMDID_SELECTALL                                         17
	#DEFINE CMDID_CLEARSELECTION                                    18
	#DEFINE CMDID_ZOOM                                              19
	#DEFINE CMDID_GETZOOMRANGE                                      20
	#DEFINE CMDID_UPDATECOMMANDS                                    21
	#DEFINE CMDID_REFRESH                                           22
	#DEFINE CMDID_STOP                                              23
	#DEFINE CMDID_HIDETOOLBARS                                      24
	#DEFINE CMDID_SETPROGRESSMAX                                    25
	#DEFINE CMDID_SETPROGRESSPOS                                    26
	#DEFINE CMDID_SETPROGRESSTEXT                                   27
	#DEFINE CMDID_SETTITLE                                          28
	#DEFINE CMDID_SETDOWNLOADSTATE                                  29
	#DEFINE CMDID_STOPDOWNLOAD                                      30
	#DEFINE CMDID_ONTOOLBARACTIVATED                                31
	#DEFINE CMDID_ENABLE_INTERACTION                                36
	#DEFINE CMDID_ONUNLOAD                                          37
	
	*-----------------------------------------------------------------
	* nExecOption (2. Parameter) für das CommandTargetExec Ereignis
	* des ActiveDocument Objektes.
	*-----------------------------------------------------------------
	#DEFINE CMDEXECOPT_DODEFAULT                                     0
	#DEFINE CMDEXECOPT_PROMPTUSER                                    1
	#DEFINE CMDEXECOPT_DONTPROMPTUSER                                2
	#DEFINE CMDEXECOPT_SHOWHELP                                      3
	
	*-----------------------------------------------------------------
	* Rückgabewerte für das CommandTargetExec Ereignis
	*-----------------------------------------------------------------
	#DEFINE CMD_OK                                                   0
	#DEFINE CMD_NOTSUPPORTED                                         1
	#DEFINE CMD_DISABLED                                             2
	#DEFINE CMD_NOHELP                                               3
	#DEFINE CMD_CANCELED                                             4

	*-----------------------------------------------------------------
	* nBuildAction (2. Parameter) für die Build() Methode des
	* ProjectHook Objektes.
	*-----------------------------------------------------------------
	#DEFINE BUILDACTION_REBUILD                                      1
	#DEFINE BUILDACTION_BUILDAPP                                     2
	#DEFINE BUILDACTION_BUILDEXE                                     3
	#DEFINE BUILDACTION_BUILDDLL                                     4
	#DEFINE BUILDACTION_BUILDMTDLL                                   5
	
	*-----------------------------------------------------------------
	* SCCStatus Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE SCCFILE_NOTCONTROLLED                                    0
	#DEFINE SCCFILE_NOTCHECKEDOUT                                    1
	#DEFINE SCCFILE_CHECKEDOUTCU                                     2
	#DEFINE SCCFILE_CHECKEDOUTOU                                     3
	#DEFINE SCCFILE_MERGECONFLICT                                    4
	#DEFINE SCCFILE_MERGE                                            5
	#DEFINE SCCFILE_CHECKEDOUTMU                                     6
	
	*-----------------------------------------------------------------
	* Type Eigenschaft des File Objektes
	*-----------------------------------------------------------------
	#DEFINE FILETYPE_DATABASE                                      "d"
	#DEFINE FILETYPE_FREETABLE                                     "D"
	#DEFINE FILETYPE_QUERY                                         "Q"
	#DEFINE FILETYPE_FORM                                          "K"
	#DEFINE FILETYPE_REPORT                                        "R"
	#DEFINE FILETYPE_LABEL                                         "B"
	#DEFINE FILETYPE_CLASSLIB                                      "V"
	#DEFINE FILETYPE_PROGRAM                                       "P"
	#DEFINE FILETYPE_APILIB                                        "L"
	#DEFINE FILETYPE_APPLICATION                                   "Z"
	#DEFINE FILETYPE_MENU                                          "M"
	#DEFINE FILETYPE_TEXT                                          "T"
	#DEFINE FILETYPE_OTHER                                         "x"
	
	*-----------------------------------------------------------------
	* Instancing Eigenschaft des Server Objektes
	*-----------------------------------------------------------------
	#DEFINE SERVERINSTANCE_SINGLEUSE                                 1
	#DEFINE SERVERINSTANCE_NOTCREATABLE                              2
	#DEFINE SERVERINSTANCE_MULTIUSE                                  3
	
	*-----------------------------------------------------------------
	* OLEDropEffect Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE DROPEFFECT_NONE                                          0
	#DEFINE DROPEFFECT_COPY                                          1
	#DEFINE DROPEFFECT_MOVE                                          2
	#DEFINE DROPEFFECT_LINK                                          4
	
	*-----------------------------------------------------------------
	* OLEDropMode Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE DROP_DISABLED                                            0
	#DEFINE DROP_ENABLED                                             1
	#DEFINE DROP_PASSTOCONTAINER                                     2

	*-----------------------------------------------------------------
	* OLEDropHasData Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE DROPHASDATA_VFPDETERMINE                                -1
	#DEFINE DROPHASDATA_NOTUSEFUL                                    0
	#DEFINE DROPHASDATA_USEFUL                                       1
	
	*-----------------------------------------------------------------
	* Globale Clipboard Formate.
	*-----------------------------------------------------------------
	#DEFINE CF_TEXT                                                  1
	#DEFINE CF_BITMAP                                                2
	#DEFINE CF_METAFILEPICT                                          3
	#DEFINE CF_SYLK                                                  4
	#DEFINE CF_DIF                                                   5
	#DEFINE CF_TIFF                                                  6
	#DEFINE CF_OEMTEXT                                               7
	#DEFINE CF_DIB                                                   8
	#DEFINE CF_PALETTE                                               9
	#DEFINE CF_PENDATA                                              10
	#DEFINE CF_RIFF                                                 11
	#DEFINE CF_WAVE                                                 12
	#DEFINE CF_UNICODETEXT                                          13
	#DEFINE CF_ENHMETAFILE                                          14
	#DEFINE CF_FILES                                                15
	#DEFINE CF_HDROP                                                15
	#DEFINE CF_LOCALE                                               16
	#DEFINE CF_MAX                                                  17
	
	*-----------------------------------------------------------------
	* Sonstige Clipboard Formate
	*-----------------------------------------------------------------
	#DEFINE CFSTR_HYPERLINK       "Hyperlink"
	#DEFINE CFSTR_BIFF            "Biff"
	#DEFINE CFSTR_BIFF3           "Biff3"
	#DEFINE CFSTR_BIFF4           "Biff4"
	#DEFINE CFSTR_BIFF5           "Biff5"
	#DEFINE CFSTR_BIFF7           "Biff7"
	#DEFINE CFSTR_BIFF8           "Biff8"
	#DEFINE CFSTR_XLTABLE         "XlTable"
	#DEFINE CFSTR_CSV             "CSV"
	#DEFINE CFSTR_WK1             "Wk1"
	#DEFINE CFSTR_URL             "UniformResourceLocator"
	#DEFINE CFSTR_RTF             "Rich Text Format"
	#DEFINE CFSTR_RTFNOOBJS       "Rich Text Format Without Objects"
	#DEFINE CFSTR_RETEXTOBJ       "RichEdit Text and Objects"
	
	*-----------------------------------------------------------------
	* Clipboardformate, die in VFP verwendet werden.
	*-----------------------------------------------------------------
	#DEFINE CFSTR_OLEVARIANTARRAY "OLE Variant Array"
	#DEFINE CFSTR_OLEVARIANT      "OLE Variant"
	#DEFINE CFSTR_VFPSOURCEOBJECT "VFP Source Object"
	
	*-----------------------------------------------------------------
	* Status (4. Parameter) des DragOver() Ereignisses
	*-----------------------------------------------------------------
	#DEFINE DRAG_ENTER                                               0
	#DEFINE DRAG_LEAVE                                               1
	#DEFINE DRAG_OVER                                                2

	*-----------------------------------------------------------------
	* Parameter für die Drag() Methode
	*-----------------------------------------------------------------
	#DEFINE DRAG_CANCEL                                              0
	#DEFINE DRAG_BEGIN                                               1
	#DEFINE DRAG_END                                                 2
	
	*-----------------------------------------------------------------
	* DragMode Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE DRAG_MANUAL                                              0
	#DEFINE DRAG_AUTOMATIC                                           1

	*-----------------------------------------------------------------
	* RGB-Werte der gebräuchlichsten Farben.
	*-----------------------------------------------------------------
	#DEFINE COLOR_WHITE                                       16777215
	#DEFINE COLOR_BLACK                                              0
	#DEFINE COLOR_GRAY                                        12632256
	#DEFINE COLOR_DARK_GRAY                                    8421504
	#DEFINE COLOR_RED                                              255
	#DEFINE COLOR_DARK_BLUE                                    8388608
	#DEFINE COLOR_CYAN                                        16776960
	#DEFINE COLOR_DARK_CYAN                                    8421376
	#DEFINE COLOR_GREEN                                          65280
	#DEFINE COLOR_DARK_GREEN                                     32768
	#DEFINE COLOR_YELLOW                                         65535
	#DEFINE COLOR_DARK_YELLOW                                    32896
	#DEFINE COLOR_BLUE                                        16711680
	#DEFINE COLOR_DARK_RED                                         128
	#DEFINE COLOR_MAGENTA                                     16711935
	#DEFINE COLOR_DARK_MAGENTA                                 8388736
	
	*-----------------------------------------------------------------
	* MousePointer Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE MOUSE_DEFAULT                                            0
	#DEFINE MOUSE_ARROW                                              1
	#DEFINE MOUSE_CROSSHAIR                                          2
	#DEFINE MOUSE_IBEAM                                              3
	#DEFINE MOUSE_ICON_POINTER                                       4
	#DEFINE MOUSE_SIZE_POINTER                                       5
	#DEFINE MOUSE_SIZE_NE_SW                                         6
	#DEFINE MOUSE_SIZE_N_S                                           7
	#DEFINE MOUSE_SIZE_NW_SE                                         8
	#DEFINE MOUSE_SIZE_W_E                                           9
	#DEFINE MOUSE_UP_ARROW                                          10
	#DEFINE MOUSE_HOURGLASS                                         11
	#DEFINE MOUSE_NO_DROP                                           12
	#DEFINE MOUSE_HIDE_POINTER                                      13
	#DEFINE MOUSE_ARROW2                                            14
	#DEFINE MOUSE_HAND                                              15
	#DEFINE MOUSE_DOWN_ARROW                                        16
	#DEFINE MOUSE_MAGNIGLASS                                        17
	#DEFINE MOUSE_CUSTOM                                            99

	*-----------------------------------------------------------------
	* ScrollBars Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE SCROLLBARS_NONE                                          0
	#DEFINE SCROLLBARS_HORIZONTAL                                    1
	#DEFINE SCROLLBARS_VERTICAL                                      2
	#DEFINE SCROLLBARS_BOTH                                          3
	
	*-----------------------------------------------------------------
	* DrawMode Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE DRAWMODE_BLACKNESS       1       && 1 - Blackness
	#DEFINE DRAWMODE_NOT_MERGE_PEN   2       && 2 - Not Merge Pen
	#DEFINE DRAWMODE_MASK_NOT_PEN    3       && 3 - Mask Not Pen
	#DEFINE DRAWMODE_NOT_COPY_PEN    4       && 4 - Not Copy Pen
	#DEFINE DRAWMODE_MASK_PEN_NOT    5       && 5 - Mask Pen Not
	#DEFINE DRAWMODE_INVERT          6       && 6 - Invert
	#DEFINE DRAWMODE_XOR_PEN         7       && 7 - Xor Pen
	#DEFINE DRAWMODE_NOT_MASK_PEN    8       && 8 - Not Mask Pen
	#DEFINE DRAWMODE_MASK_PEN        9       && 9 - Mask Pen
	#DEFINE DRAWMODE_NOT_XOR_PEN     10      && 10 - Not Xor Pen
	#DEFINE DRAWMODE_NOP             11      && 11 - Nop
	#DEFINE DRAWMODE_MERGE_NOT_PEN   12      && 12 - Merge Not Pen
	#DEFINE DRAWMODE_COPY_PEN        13      && 13 - Copy Pen
	#DEFINE DRAWMODE_MERGE_PEN_NOT   14      && 14 - Merge Pen Not
	#DEFINE DRAWMODE_MERGE_PEN       15      && 15 - Merge Pen
	#DEFINE DRAWMODE_WHITENESS       16      && 16 - Whiteness
	
	*-----------------------------------------------------------------
	* DrawStyle Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE DRAWSTYLE_SOLID           0       && 0 - Solid
	#DEFINE DRAWSTYLE_DASH            1       && 1 - Dash
	#DEFINE DRAWSTYLE_DOT             2       && 2 - Dot
	#DEFINE DRAWSTYLE_DASH_DOT        3       && 3 - Dash-Dot
	#DEFINE DRAWSTYLE_DASH_DOT_DOT    4       && 4 - Dash-Dot-Dot
	#DEFINE DRAWSTYLE_INVISIBLE       5       && 5 - Invisible
	#DEFINE DRAWSTYLE_INSIDE_SOLID    6       && 6 - Inside Solid
	
	*-----------------------------------------------------------------
	* FillStyle Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE FILLSTYLE_SOLID                   0       && 0 - Solid
	#DEFINE FILLSTYLE_TRANSPARENT             1       && 1 - Transparent
	#DEFINE FILLSTYLE_HORIZONTAL_LINE         2       && 2 - Horizontal Line
	#DEFINE FILLSTYLE_VERTICAL_LINE           3       && 3 - Vertical Line
	#DEFINE FILLSTYLE_UPWARD_DIAGONAL         4       && 4 - Upward Diagonal
	#DEFINE FILLSTYLE_DOWNWARD_DIAGONAL       5       && 5 - Downward Diagonal
	#DEFINE FILLSTYLE_CROSS                   6       && 6 - Cross
	#DEFINE FILLSTYLE_DIAGONAL_CROSS          7       && 7 - Diagonal Cross
	
	*-----------------------------------------------------------------
	* ScaleMode Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE SCALEMODE_PIXELS          3       && 3 - Pixel
	#DEFINE SCALEMODE_FOXELS          0       && 0 - Foxels
	
	*-----------------------------------------------------------------
	* WindowState Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE WINDOWSTATE_NORMAL                                       0
	#DEFINE WINDOWSTATE_MINIMIZED                                    1
	#DEFINE WINDOWSTATE_MAXIMIZED                                    2
	
	*-----------------------------------------------------------------
	* BorderStyle Eigenschaft für Formulare
	*-----------------------------------------------------------------
	#DEFINE BORDER_NONE                                              0
	#DEFINE BORDER_SINGLE                                            1
	#DEFINE BORDER_DOUBLE                                            2
	#DEFINE BORDER_SYSTEM                                            3
	
	*-----------------------------------------------------------------
	* DockPosition Eigenschaft
	*-----------------------------------------------------------------
	#DEFINE TOOL_NOTDOCKED                                          -1
	#DEFINE TOOL_TOP                                                 0
	#DEFINE TOOL_LEFT                                                1
	#DEFINE TOOL_RIGHT                                               2
	#DEFINE TOOL_BOTTOM                                              3
	
	*-----------------------------------------------------------------
	* Button Parameter für Ereignisse wie MouseDown(), MouseUp(), usw.
	*-----------------------------------------------------------------
	#DEFINE BUTTON_LEFT                                              1
	#DEFINE BUTTON_RIGHT                                             2
	#DEFINE BUTTON_MIDDLE                                            4
	
	*-----------------------------------------------------------------
	* Messagebox() Parameter. Aus jedem Block kann jeweils ein Wert
	* verwendet und zu den Werten aus den anderen Blöcken addiert
	* werden.
	*-----------------------------------------------------------------
	#DEFINE MB_OK                   0       && OK button only
	#DEFINE MB_OKCANCEL             1       && OK and Cancel buttons
	#DEFINE MB_ABORTRETRYIGNORE     2       && Abort, Retry, and Ignore buttons
	#DEFINE MB_YESNOCANCEL          3       && Yes, No, and Cancel buttons
	#DEFINE MB_YESNO                4       && Yes and No buttons
	#DEFINE MB_RETRYCANCEL          5       && Retry and Cancel buttons

	#DEFINE MB_ICONSTOP             16      && Critical message
	#DEFINE MB_ICONQUESTION         32      && Warning query
	#DEFINE MB_ICONEXCLAMATION      48      && Warning message
	#DEFINE MB_ICONINFORMATION      64      && Information message

	#DEFINE MB_APPLMODAL            0       && Application modal message box
	#DEFINE MB_DEFBUTTON1           0       && First button is default
	#DEFINE MB_DEFBUTTON2           256     && Second button is default
	#DEFINE MB_DEFBUTTON3           512     && Third button is default
	#DEFINE MB_SYSTEMMODAL          4096    && System Modal
	
	*-----------------------------------------------------------------
	* Rückgabewerte der MessageBox() Funktion.
	*-----------------------------------------------------------------
	#DEFINE IDOK            1       && OK button pressed
	#DEFINE IDCANCEL        2       && Cancel button pressed
	#DEFINE IDABORT         3       && Abort button pressed
	#DEFINE IDRETRY         4       && Retry button pressed
	#DEFINE IDIGNORE        5       && Ignore button pressed
	#DEFINE IDYES           6       && Yes button pressed
	#DEFINE IDNO            7       && No button pressed
	
	*-----------------------------------------------------------------
	* Konstanten für den Modus bei FOPEN() und FCREATE()
	*-----------------------------------------------------------------
	#DEFINE F_READONLY                                               0
	#DEFINE F_WRITEONLY                                              1
	#DEFINE F_READWRITE                                              2
	#DEFINE F_READONLY_UNBUFF                                       10
	#DEFINE F_WRITEONLY_UNBUFF                                      11
	#DEFINE F_READWRITE_UNBUFF                                      12
	
	*-----------------------------------------------------------------
	* Gültige Parameterwerte für die PrtInfo() Funktion.
	*-----------------------------------------------------------------
	#DEFINE PRT_ORIENTATION                                          1
	#DEFINE PRT_PAPERSIZE                                            2
	#DEFINE PRT_PAPERLENGTH                                          3
	#DEFINE PRT_PAPERWIDTH                                           4
	#DEFINE PRT_SCALE                                                5
	#DEFINE PRT_COPIES                                               6
	#DEFINE PRT_DEFASOURCE                                           7
	#DEFINE PRT_PRINTQUAL                                            8
	#DEFINE PRT_COLOR                                                9
	#DEFINE PRT_DUPLEX                                              10
	#DEFINE PRT_YRESOLUTION                                         11
	#DEFINE PRT_TTOPTION                                            12
	#DEFINE PRT_COLLATE                                             13
	
	*-----------------------------------------------------------------
	* PrtInfo() Rückgabewerte: Papiergrößen
	*-----------------------------------------------------------------
	#DEFINE PRTPAPER_LETTER      1       && Letter 8 1/2 x 11 in               
	#DEFINE PRTPAPER_LETTERSMALL 2       && Letter Small 8 1/2 x 11 in         
	#DEFINE PRTPAPER_TABLOID     3       && Tabloid 11 x 17 in                 
	#DEFINE PRTPAPER_LEDGER      4       && Ledger 17 x 11 in                  
	#DEFINE PRTPAPER_LEGAL       5       && Legal 8 1/2 x 14 in                
	#DEFINE PRTPAPER_STATEMENT   6       && Statement 5 1/2 x 8 1/2 in         
	#DEFINE PRTPAPER_EXECUTIVE   7       && Executive 7 1/4 x 10 1/2 in      
	#DEFINE PRTPAPER_A3          8       && A3 297 x 420 mm                    
	#DEFINE PRTPAPER_A4          9       && A4 210 x 297 mm                    
	#DEFINE PRTPAPER_A4SMALL     10      && A4 Small 210 x 297 mm              
	#DEFINE PRTPAPER_A5          11      && A5 148 x 210 mm                    
	#DEFINE PRTPAPER_B4          12      && B4 250 x 354                       
	#DEFINE PRTPAPER_B5          13      && B5 182 x 257 mm                    
	#DEFINE PRTPAPER_FOLIO       14      && Folio 8 1/2 x 13 in                
	#DEFINE PRTPAPER_QUARTO      15      && Quarto 215 x 275 mm                
	#DEFINE PRTPAPER_10X14       16      && 10x14 in                           
	#DEFINE PRTPAPER_11X17       17      && 11x17 in                           
	#DEFINE PRTPAPER_NOTE        18      && Note 8 1/2 x 11 in                 
	#DEFINE PRTPAPER_ENV_9       19      && Envelope #9 3 7/8 x 8 7/8          
	#DEFINE PRTPAPER_ENV_10      20      && Envelope #10 4 1/8 x 9 1/2         
	#DEFINE PRTPAPER_ENV_11      21      && Envelope #11 4 1/2 x 10 3/8        
	#DEFINE PRTPAPER_ENV_12      22      && Envelope #12 4 \276 x 11           
	#DEFINE PRTPAPER_ENV_14      23      && Envelope #14 5 x 11 1/2            
	#DEFINE PRTPAPER_CSHEET      24      && C size sheet                       
	#DEFINE PRTPAPER_DSHEET      25      && D size sheet                       
	#DEFINE PRTPAPER_ESHEET      26      && E size sheet                       
	#DEFINE PRTPAPER_ENV_DL      27      && Envelope DL 110 x 220mm            
	#DEFINE PRTPAPER_ENV_C5      28      && Envelope C5 162 x 229 mm           
	#DEFINE PRTPAPER_ENV_C3      29      && Envelope C3  324 x 458 mm          
	#DEFINE PRTPAPER_ENV_C4      30      && Envelope C4  229 x 324 mm          
	#DEFINE PRTPAPER_ENV_C6      31      && Envelope C6  114 x 162 mm          
	#DEFINE PRTPAPER_ENV_C65     32      && Envelope C65 114 x 229 mm          
	#DEFINE PRTPAPER_ENV_B4      33      && Envelope B4  250 x 353 mm          
	#DEFINE PRTPAPER_ENV_B5      34      && Envelope B5  176 x 250 mm          
	#DEFINE PRTPAPER_ENV_B6      35      && Envelope B6  176 x 125 mm          
	#DEFINE PRTPAPER_ENV_ITALY   36      && Envelope 110 x 230 mm              
	#DEFINE PRTPAPER_ENV_MONARCH 37      && Envelope Monarch 3.875 x 7.5 in    
	#DEFINE PRTPAPER_ENV_PERSONAL 38     && 6 3/4 Envelope 3 5/8 x 6 1/2 in    
	#DEFINE PRTPAPER_FANFOLD_US  39      && US Std Fanfold 14 7/8 x 11 in      
	#DEFINE PRTPAPER_FANFOLD_STD_GERMAN  40 && German Std Fanfold 8 1/2 x 12 in   
	#DEFINE PRTPAPER_FANFOLD_LGL_GERMAN  41 && German Legal Fanfold 8 1/2 x 13 in 
	
	*-----------------------------------------------------------------
	* PrtInfo() Rückgabewerte: Papierschächte
	*-----------------------------------------------------------------
	#DEFINE PRTBIN_UPPER                                             1
	#DEFINE PRTBIN_ONLYONE                                           1
	#DEFINE PRTBIN_LOWER                                             2
	#DEFINE PRTBIN_MIDDLE                                            3
	#DEFINE PRTBIN_MANUAL                                            4
	#DEFINE PRTBIN_ENVELOPE                                          5
	#DEFINE PRTBIN_ENVMANUAL                                         6
	#DEFINE PRTBIN_AUTO                                              7
	#DEFINE PRTBIN_TRACTOR                                           8
	#DEFINE PRTBIN_SMALLFMT                                          9
	#DEFINE PRTBIN_LARGEFMT                                         10
	#DEFINE PRTBIN_LARGECAPACITY                                    11
	#DEFINE PRTBIN_CASSETTE                                         14
	
	*-----------------------------------------------------------------
	* PrtInfo() Rückgabewerte: Druckqualität
	*-----------------------------------------------------------------
	#DEFINE PRTRES_DRAFT                                            -1
	#DEFINE PRTRES_LOW                                              -2
	#DEFINE PRTRES_MEDIUM                                           -3
	#DEFINE PRTRES_HIGH                                             -4
	
	*-----------------------------------------------------------------
	* PrtInfo() Rückgabewerte: Farbdrucker
	*-----------------------------------------------------------------
	#DEFINE PRTCOLOR_MONOCHROME                                      1
	#DEFINE PRTCOLOR_COLOR                                           2
	
	*-----------------------------------------------------------------
	* PrtInfo() Rückgabewerte: Duplex-Druck
	*-----------------------------------------------------------------
	#DEFINE PRTDUP_SIMPLEX                                           1
	#DEFINE PRTDUP_VERTICAL                                          2
	#DEFINE PRTDUP_HORIZONTAL                                        3
	
	*-----------------------------------------------------------------
	* PrtInfo() Rückgabewerte: TrueType Fonts
	*-----------------------------------------------------------------
	#DEFINE PRTTT_BITMAP                                             1
	#DEFINE PRTTT_DOWNLOAD                                           2
	#DEFINE PRTTT_SUBDEV                                             3
	
	*-----------------------------------------------------------------
	* Parameter für die FontMetric() Funktion.
	*-----------------------------------------------------------------
	#DEFINE TM_HEIGHT                                                1
	#DEFINE TM_ASCENT                                                2
	#DEFINE TM_DESCENT                                               3
	#DEFINE TM_INTERNALLEADING                                       4
	#DEFINE TM_EXTERNALLEADING                                       5
	#DEFINE TM_AVECHARWIDTH                                          6
	#DEFINE TM_MAXCHARWIDTH                                          7
	#DEFINE TM_WEIGHT                                                8
	#DEFINE TM_ITALIC                                                9
	#DEFINE TM_UNDERLINED                                           10
	#DEFINE TM_STRUCKOUT                                            11
	#DEFINE TM_FIRSTCHAR                                            12
	#DEFINE TM_LASTCHAR                                             13
	#DEFINE TM_DEFAULTCHAR                                          14
	#DEFINE TM_BREAKCHAR                                            15
	#DEFINE TM_PITCHANDFAMILY                                       16
	#DEFINE TM_CHARSET                                              17
	#DEFINE TM_OVERHANG                                             18
	#DEFINE TM_ASPECTX                                              19
	#DEFINE TM_ASPECTY                                              20
	
	*-----------------------------------------------------------------
	* Parameter für die SysMetric() Funktion
	*-----------------------------------------------------------------
	#DEFINE SYSMETRIC_SCREENWIDTH         1 && Screen width
	#DEFINE SYSMETRIC_SCREENHEIGHT        2 && Screen width
	#DEFINE SYSMETRIC_SIZINGBORDERWIDTH                              3
	#DEFINE SYSMETRIC_SIZINGBORDERHEIGHT                             4
	#DEFINE SYSMETRIC_VSCROLLBARWIDTH                                5
	#DEFINE SYSMETRIC_VSCROLLBARHEIGHT                               6
	#DEFINE SYSMETRIC_HSCROLLBARWIDTH                                7
	#DEFINE SYSMETRIC_HSCROLLBARHEIGHT                               8
	#DEFINE SYSMETRIC_WINDOWTITLEHEIGHT                              9
	#DEFINE SYSMETRIC_WINDOWBORDERWIDTH                             10
	#DEFINE SYSMETRIC_WINDOWBORDERHEIGHT                            11
	#DEFINE SYSMETRIC_WINDOWFRAMEWIDTH                              12
	#DEFINE SYSMETRIC_WINDOWFRAMEHEIGHT                             13
	#DEFINE SYSMETRIC_THUMBBOXWIDTH                                 14
	#DEFINE SYSMETRIC_THUMBBOXHEIGHT                                15
	#DEFINE SYSMETRIC_ICONWIDTH                                     16
	#DEFINE SYSMETRIC_ICONHEIGHT                                    17
	#DEFINE SYSMETRIC_CURSORWIDTH                                   18
	#DEFINE SYSMETRIC_CURSORHEIGHT                                  19
	#DEFINE SYSMETRIC_MENUBAR                                       20
	#DEFINE SYSMETRIC_CLIENTWIDTH                                   21
	#DEFINE SYSMETRIC_CLIENTHEIGHT                                  22
	#DEFINE SYSMETRIC_KANJIWINHEIGHT                                23
	#DEFINE SYSMETRIC_MINDRAGWIDTH                                  24
	#DEFINE SYSMETRIC_MINDRAGHEIGHT                                 25
	#DEFINE SYSMETRIC_MINWINDOWWIDTH                                26
	#DEFINE SYSMETRIC_MINWINDOWHEIGHT                               27
	#DEFINE SYSMETRIC_TITLEBARBUTTONWIDTH                           28
	#DEFINE SYSMETRIC_TITLEBARBUTTONHEIGHT                          29
	#DEFINE SYSMETRIC_MOUSEPRESENT                                  30
	#DEFINE SYSMETRIC_DEBUGVERSION                                  31
	#DEFINE SYSMETRIC_MOUSEBUTTONSWAP                               32
	#DEFINE SYSMETRIC_HALFHEIGHTBUTTONWIDTH                         33
	#DEFINE SYSMETRIC_HALFHEIGHTBUTTONHEIGHT                        34
	
	*-----------------------------------------------------------------
	* Konstanten für die Windows API Funktion GetSysMetric()
	*-----------------------------------------------------------------
	#DEFINE SM_CXSCREEN                                              0
	#DEFINE SM_CYSCREEN                                              1
	#DEFINE SM_CXVSCROLL                                             2
	#DEFINE SM_CYHSCROLL                                             3
	#DEFINE SM_CYCAPTION                                             4
	#DEFINE SM_CXBORDER                                              5
	#DEFINE SM_CYBORDER                                              6
	#DEFINE SM_CXDLGFRAME                                            7
	#DEFINE SM_CYDLGFRAME                                            8
	#DEFINE SM_CYVTHUMB                                              9
	#DEFINE SM_CXHTHUMB                                             10
	#DEFINE SM_CXICON                                               11
	#DEFINE SM_CYICON                                               12
	#DEFINE SM_CXCURSOR                                             13
	#DEFINE SM_CYCURSOR                                             14
	#DEFINE SM_CYMENU                                               15
	#DEFINE SM_CXFULLSCREEN                                         16
	#DEFINE SM_CYFULLSCREEN                                         17
	#DEFINE SM_CYKANJIWINDOW                                        18
	#DEFINE SM_MOUSEPRESENT                                         19
	#DEFINE SM_CYVSCROLL                                            20
	#DEFINE SM_CXHSCROLL                                            21
	#DEFINE SM_DEBUG                                                22
	#DEFINE SM_SWAPBUTTON                                           23
	#DEFINE SM_RESERVED1                                            24
	#DEFINE SM_RESERVED2                                            25
	#DEFINE SM_RESERVED3                                            26
	#DEFINE SM_RESERVED4                                            27
	#DEFINE SM_CXMIN                                                28
	#DEFINE SM_CYMIN                                                29
	#DEFINE SM_CXSIZE                                               30
	#DEFINE SM_CYSIZE                                               31
	#DEFINE SM_CXFRAME                                              32
	#DEFINE SM_CYFRAME                                              33
	#DEFINE SM_CXMINTRACK                                           34
	#DEFINE SM_CYMINTRACK                                           35
	#DEFINE SM_CMETRICS                                             36
	
	*-----------------------------------------------------------------
	* Buffermodi die von CursorSetProp() und CursorGetProp() bei der
	* Eigenschaft "Buffering" verwendet werden.
	*-----------------------------------------------------------------
	#DEFINE DB_BUFOFF                                                1
	#DEFINE DB_BUFLOCKRECORD                                         2
	#DEFINE DB_BUFOPTRECORD                                          3
	#DEFINE DB_BUFLOCKTABLE                                          4
	#DEFINE DB_BUFOPTTABLE                                           5
	
	*-----------------------------------------------------------------
	* Werte für die "UpdateType" Eigenschaft der Funktionen 
	* DBSetProp(), DBGetProp(), CursorSetProp() und CursorGetProp().
	*-----------------------------------------------------------------
	#DEFINE DB_UPDATE                                                1
	#DEFINE DB_DELETEINSERT                                          2
	
	*-----------------------------------------------------------------
	* Werte für die "WhereType" Eigenschaft der Funktionen 
	* DBSetProp(), DBGetProp(), CursorSetProp() und CursorGetProp().
	*-----------------------------------------------------------------
	#DEFINE DB_KEY                                                   1
	#DEFINE DB_KEYANDUPDATABLE                                       2
	#DEFINE DB_KEYANDMODIFIED                                        3
	#DEFINE DB_KEYANDTIMESTAMP                                       4
	
	*-----------------------------------------------------------------
	* Werte für die "DispLogin" Eigenschaft der Funktionen DBSetProp()
	* und DBGetProp().
	*-----------------------------------------------------------------
	#DEFINE DB_PROMPTCOMPLETE                                        1
	#DEFINE DB_PROMPTALWAYS                                          2
	#DEFINE DB_PROMPTNEVER                                           3

	*-----------------------------------------------------------------
	* Werte für die Eigenschaft "Transactions" der Funktionen
	* DBSetProp() und DBGetProp().
	*-----------------------------------------------------------------
	#DEFINE DB_TRANSAUTO                                             1
	#DEFINE DB_TRANSMANUAL                                           2
	
	*-----------------------------------------------------------------
	* Werte für die Eigenschaft "SourceType" der Funktion 
	* CursorGetprop().
	*-----------------------------------------------------------------
	#DEFINE DB_SRCLOCALVIEW                                          1
	#DEFINE DB_SRCREMOTEVIEW                                         2
	#DEFINE DB_SRCTABLE                                              3

	*-----------------------------------------------------------------
	* Sprach ID (Language ID)
	*
	* Die Sprach-ID ist ein 16 bit Wert, der eine Kombination der
	* primären Sprach-ID und der sekundären Sprach-ID beinhaltet. 
	* Die primäre SPrach-ID gibt die eigentliche Sprache an, die se-
	* kundäre ID gibt Unterarten der gleichen Sprache an. Die Bits in
	* diesem 16-Bit Wert sind wie folgt belegt:
	*
	*       +-----------------------+-------------------------+
	*       |     Sublanguage ID    |   Primary Language ID   |
	*       +-----------------------+-------------------------+
	*        15                   10 9                       0   bit
	*
	* Die folgenden Kombinationen aus primärer Sprach-ID und sekun-
	* därer Sprach-ID haben spezielle Bedeutungen:
	*
	*    Primary Lang ID  Sublanguage ID      Result
	*    ---------------  ---------------     -----------------------
	*    LANG_NEUTRAL     SUBLANG_NEUTRAL     Language neutral
	*    LANG_NEUTRAL     SUBLANG_DEFAULT     User default language
	*    LANG_NEUTRAL     SUBLANG_SYS_DEFAULT System default language
	*
	* Um eine Sprach-ID zu erhalten, müssen jeweils die primäre 
	* Sprach-ID und die sekundäre Sprach-ID bitweise UND verknüpft
	* werden. Dies kann in VFP durch eine Addition der beiden Werte
	* erfolgen.
	*-----------------------------------------------------------------
	
	*-----------------------------------------------------------------
	* Primäre Sprach-IDs.
	*-----------------------------------------------------------------
	#DEFINE LANG_NEUTRAL                                          0x00
	#DEFINE LANG_AFRIKAANS                                        0x36
	#DEFINE LANG_ALBANIAN                                         0x1c
	#DEFINE LANG_ARABIC                                           0x01
	#DEFINE LANG_BASQUE                                           0x2d
	#DEFINE LANG_BELARUSIAN                                       0x23
	#DEFINE LANG_BULGARIAN                                        0x02
	#DEFINE LANG_CATALAN                                          0x03
	#DEFINE LANG_CHINESE                                          0x04
	#DEFINE LANG_CROATIAN                                         0x1a
	#DEFINE LANG_CZECH                                            0x05
	#DEFINE LANG_DANISH                                           0x06
	#DEFINE LANG_DUTCH                                            0x13
	#DEFINE LANG_ENGLISH                                          0x09
	#DEFINE LANG_ESTONIAN                                         0x25
	#DEFINE LANG_FAEROESE                                         0x38
	#DEFINE LANG_FARSI                                            0x29
	#DEFINE LANG_FINNISH                                          0x0b
	#DEFINE LANG_FRENCH                                           0x0c
	#DEFINE LANG_GERMAN                                           0x07
	#DEFINE LANG_GREEK                                            0x08
	#DEFINE LANG_HEBREW                                           0x0d
	#DEFINE LANG_HUNGARIAN                                        0x0e
	#DEFINE LANG_ICELANDIC                                        0x0f
	#DEFINE LANG_INDONESIAN                                       0x21
	#DEFINE LANG_ITALIAN                                          0x10
	#DEFINE LANG_JAPANESE                                         0x11
	#DEFINE LANG_KOREAN                                           0x12
	#DEFINE LANG_LATVIAN                                          0x26
	#DEFINE LANG_LITHUANIAN                                       0x27
	#DEFINE LANG_NORWEGIAN                                        0x14
	#DEFINE LANG_POLISH                                           0x15
	#DEFINE LANG_PORTUGUESE                                       0x16
	#DEFINE LANG_ROMANIAN                                         0x18
	#DEFINE LANG_RUSSIAN                                          0x19
	#DEFINE LANG_SERBIAN                                          0x1a
	#DEFINE LANG_SLOVAK                                           0x1b
	#DEFINE LANG_SLOVENIAN                                        0x24
	#DEFINE LANG_SPANISH                                          0x0a
	#DEFINE LANG_SWEDISH                                          0x1d
	#DEFINE LANG_THAI                                             0x1e
	#DEFINE LANG_TURKISH                                          0x1f
	#DEFINE LANG_UKRAINIAN                                        0x22
	#DEFINE LANG_VIETNAMESE                                       0x2a
	
	*-----------------------------------------------------------------
	* Sekundäre Sprach-ID.
	*
	* Der Name, der direkt hinter SUBLANG_ folgt, bestimmt, welche
	* primäre Sprach-ID mit dieser sekundären Sprach-ID kombiniert
	* werden kann, um eine gültige Sprach-ID zu erhalten.
	*-----------------------------------------------------------------
	#DEFINE SUBLANG_NEUTRAL                                     0x0000
	#DEFINE SUBLANG_DEFAULT                                     0x0400
	#DEFINE SUBLANG_SYS_DEFAULT                                 0x0800
	#DEFINE SUBLANG_ARABIC_SAUDI_ARABIA                         0x0400
	#DEFINE SUBLANG_ARABIC_IRAQ                                 0x0800
	#DEFINE SUBLANG_ARABIC_EGYPT                                0x0C00
	#DEFINE SUBLANG_ARABIC_LIBYA                                0x1000
	#DEFINE SUBLANG_ARABIC_ALGERIA                              0x1400
	#DEFINE SUBLANG_ARABIC_MOROCCO                              0x1800
	#DEFINE SUBLANG_ARABIC_TUNISIA                              0x1C00
	#DEFINE SUBLANG_ARABIC_OMAN                                 0x2000
	#DEFINE SUBLANG_ARABIC_YEMEN                                0x2400
	#DEFINE SUBLANG_ARABIC_SYRIA                                0x2800
	#DEFINE SUBLANG_ARABIC_JORDAN                               0x2C00
	#DEFINE SUBLANG_ARABIC_LEBANON                              0x3000
	#DEFINE SUBLANG_ARABIC_KUWAIT                               0x3400
	#DEFINE SUBLANG_ARABIC_UAE                                  0x3800
	#DEFINE SUBLANG_ARABIC_BAHRAIN                              0x3C00
	#DEFINE SUBLANG_ARABIC_QATAR                                0x4000
	#DEFINE SUBLANG_CHINESE_TRADITIONAL                         0x0400
	#DEFINE SUBLANG_CHINESE_SIMPLIFIED                          0x0800
	#DEFINE SUBLANG_CHINESE_HONGKONG                            0x0C00
	#DEFINE SUBLANG_CHINESE_SINGAPORE                           0x1000
	#DEFINE SUBLANG_DUTCH                                       0x0400
	#DEFINE SUBLANG_DUTCH_BELGIAN                               0x0800
	#DEFINE SUBLANG_ENGLISH_US                                  0x0400
	#DEFINE SUBLANG_ENGLISH_UK                                  0x0800
	#DEFINE SUBLANG_ENGLISH_AUS                                 0x0C00
	#DEFINE SUBLANG_ENGLISH_CAN                                 0x1000
	#DEFINE SUBLANG_ENGLISH_NZ                                  0x1400
	#DEFINE SUBLANG_ENGLISH_EIRE                                0x1800
	#DEFINE SUBLANG_ENGLISH_SOUTH_AFRICA                        0x1C00
	#DEFINE SUBLANG_ENGLISH_JAMAICA                             0x2000
	#DEFINE SUBLANG_ENGLISH_CARIBBEAN                           0x2400
	#DEFINE SUBLANG_ENGLISH_BELIZE                              0x2800
	#DEFINE SUBLANG_ENGLISH_TRINIDAD                            0x2C00
	#DEFINE SUBLANG_FRENCH                                      0x0400
	#DEFINE SUBLANG_FRENCH_BELGIAN                              0x0800
	#DEFINE SUBLANG_FRENCH_CANADIAN                             0x0C00
	#DEFINE SUBLANG_FRENCH_SWISS                                0x1000
	#DEFINE SUBLANG_FRENCH_LUXEMBOURG                           0x1400
	#DEFINE SUBLANG_GERMAN                                      0x0400
	#DEFINE SUBLANG_GERMAN_SWISS                                0x0800
	#DEFINE SUBLANG_GERMAN_AUSTRIAN                             0x0C00
	#DEFINE SUBLANG_GERMAN_LUXEMBOURG                           0x1000
	#DEFINE SUBLANG_GERMAN_LIECHTENSTEIN                        0x1400
	#DEFINE SUBLANG_ITALIAN                                     0x0400
	#DEFINE SUBLANG_ITALIAN_SWISS                               0x0800
	#DEFINE SUBLANG_KOREAN                                      0x0400
	#DEFINE SUBLANG_KOREAN_JOHAB                                0x0800
	#DEFINE SUBLANG_NORWEGIAN_BOKMAL                            0x0400
	#DEFINE SUBLANG_NORWEGIAN_NYNORSK                           0x0800
	#DEFINE SUBLANG_PORTUGUESE                                  0x0800
	#DEFINE SUBLANG_PORTUGUESE_BRAZILIAN                        0x0400
	#DEFINE SUBLANG_SERBIAN_LATIN                               0x0800
	#DEFINE SUBLANG_SERBIAN_CYRILLIC                            0x0C00
	#DEFINE SUBLANG_SPANISH                                     0x0400
	#DEFINE SUBLANG_SPANISH_MEXICAN                             0x0800
	#DEFINE SUBLANG_SPANISH_MODERN                              0x0C00
	#DEFINE SUBLANG_SPANISH_GUATEMALA                           0x1000
	#DEFINE SUBLANG_SPANISH_COSTA_RICA                          0x1400
	#DEFINE SUBLANG_SPANISH_PANAMA                              0x1800
	#DEFINE SUBLANG_SPANISH_DOMINICAN_REPUBLIC                  0x1C00
	#DEFINE SUBLANG_SPANISH_VENEZUELA                           0x2000
	#DEFINE SUBLANG_SPANISH_COLOMBIA                            0x2400
	#DEFINE SUBLANG_SPANISH_PERU                                0x2800
	#DEFINE SUBLANG_SPANISH_ARGENTINA                           0x2C00
	#DEFINE SUBLANG_SPANISH_ECUADOR                             0x3000
	#DEFINE SUBLANG_SPANISH_CHILE                               0x3400
	#DEFINE SUBLANG_SPANISH_URUGUAY                             0x3800
	#DEFINE SUBLANG_SPANISH_PARAGUAY                            0x3C00
	#DEFINE SUBLANG_SPANISH_BOLIVIA                             0x4000
	#DEFINE SUBLANG_SPANISH_EL_SALVADOR                         0x4400
	#DEFINE SUBLANG_SPANISH_HONDURAS                            0x4800
	#DEFINE SUBLANG_SPANISH_NICARAGUA                           0x4C00
	#DEFINE SUBLANG_SPANISH_PUERTO_RICO                         0x5000
	#DEFINE SUBLANG_SWEDISH                                     0x0400
	#DEFINE SUBLANG_SWEDISH_FINLAND                             0x0800

	*-----------------------------------------------------------------
	* Visual FoxPro Systemkapazitäten
	*
	* Anmerkung: Es gibt keine Dokumentation darüber, wie viele Data-
	*            Sessions tatsächlich zur Verfügung stehen.
	*
	*-----------------------------------------------------------------
	#DEFINE CAPACITY_MAX_DATASESSIONS                            32768
	#DEFINE CAPACITY_MAX_ARRAYELEMENTS                           65000
	#IF __VFP5
		#DEFINE CAPACITY_MAX_MEMOWIDTH                             1024
	#ELSE
		#DEFINE CAPACITY_MAX_MEMOWIDTH                             8192
	#ENDIF
	#DEFINE CAPACITY_MAX_TXNLEVEL                                    5
	#DEFINE CAPACITY_MAX_PRGLEVEL                                  128

	*-----------------------------------------------------------------
	* Misc constants
	*-----------------------------------------------------------------
	#DEFINE DEFAULT_DATASESSION                                      1
	#DEFINE SELECT_NEW_WORKAREA                                      0

	*-----------------------------------------------------------------
	* Array columns for AFIELDS()
	*-----------------------------------------------------------------
	#DEFINE AFIELDS_Name                                             1
	#DEFINE AFIELDS_Type                                             2
	#DEFINE AFIELDS_Width                                            3
	#DEFINE AFIELDS_Decimals                                         4
	#DEFINE AFIELDS_Null                                             5
	#DEFINE AFIELDS_NoCPTrans                                        6
	#DEFINE AFIELDS_FieldValidExpr                                   7
	#DEFINE AFIELDS_FieldValidText                                   8
	#DEFINE AFIELDS_DefaultValue                                     9
	#DEFINE AFIELDS_TableValidExpr                                  10
	#DEFINE AFIELDS_TableValidText                                  11
	#DEFINE AFIELDS_LongName                                        12
	#DEFINE AFIELDS_InsertTrigger                                   13
	#DEFINE AFIELDS_UpdateTrigger                                   14
	#DEFINE AFIELDS_DeleteTrigger                                   15
	#DEFINE AFIELDS_TableComment                                    16
	#DEFINE AFIELDS_ArraySize                                       16
	
	*-----------------------------------------------------------------
	* Constants for the third parameter of PEMSTATUS()
	*-----------------------------------------------------------------
	#DEFINE PEM_CHANGED                                              0
	#DEFINE PEM_READONLY                                             1
	#DEFINE PEM_PROTECTED                                            2
	#DEFINE PEM_TYPE                                                 3
	#DEFINE PEM_USER_DEFINED                                         4
	#DEFINE PEM_EXIST                                                5
	#DEFINE PEM_INHERITED                                            6

	*-----------------------------------------------------------------
	* All possible key strokes as the are coded by INKEY() and are
	* used in the KeyPress event.
	* (...) noch nicht vollständig
	*-----------------------------------------------------------------
	#DEFINE KEY_0                                                   48
	#DEFINE KEY_1                                                   49
	#DEFINE KEY_2                                                   50
	#DEFINE KEY_3                                                   51
	#DEFINE KEY_4                                                   52
	#DEFINE KEY_5                                                   53
	#DEFINE KEY_6                                                   54
	#DEFINE KEY_7                                                   55
	#DEFINE KEY_8                                                   56
	#DEFINE KEY_9                                                   57
	#DEFINE KEY_A                                                   97
	#DEFINE KEY_B                                                   98
	#DEFINE KEY_BACKSPACE                                          127
	#DEFINE KEY_C                                                   99
	#DEFINE KEY_COMMA                                               44
	#DEFINE KEY_D                                                  100
	#DEFINE KEY_DEL                                                  7
	#DEFINE KEY_DOWNARROW                                           24
	#DEFINE KEY_E                                                  101
	#DEFINE KEY_ENTER                                               13
	#DEFINE KEY_F                                                  102
	#DEFINE KEY_G                                                  103
	#DEFINE KEY_H                                                  104
	#DEFINE KEY_I                                                  105
	#DEFINE KEY_INS                                                 22
	#DEFINE KEY_J                                                  106
	#DEFINE KEY_K                                                  107
	#DEFINE KEY_L                                                  108
	#DEFINE KEY_M                                                  109
	#DEFINE KEY_N                                                  110
	#DEFINE KEY_O                                                  111
	#DEFINE KEY_P                                                  112
	#DEFINE KEY_POINT                                               46
	#DEFINE KEY_Q                                                  113
	#DEFINE KEY_R                                                  114
	#DEFINE KEY_S                                                  115
	#DEFINE KEY_SPACEBAR                                            32
	#DEFINE KEY_T                                                  116
	#DEFINE KEY_U                                                  117
	#DEFINE KEY_UPARROW                                              5
	#DEFINE KEY_V                                                  118
	#DEFINE KEY_W                                                  119
	#DEFINE KEY_X                                                  120
	#DEFINE KEY_Y                                                  121
	#DEFINE KEY_Z                                                  122

	*-----------------------------------------------------------------
	* All possible combinations for the nShiftAltCtrl parameter in the
	* Keypress event.
	* (...) noch nicht vollständig
	*-----------------------------------------------------------------
	#DEFINE KEY_SAC_NONE                                             0

	*-----------------------------------------------------------------
	* Werte für den dritten Parameter von AMEMBERS().
	*-----------------------------------------------------------------
	#DEFINE AMEMBERS_ALLPEMS                                         1
	#DEFINE AMEMBERS_OBJECTS                                         2

	*-----------------------------------------------------------------
	* Werte für den zweiten Parameter der Funktion ALEN()
	*-----------------------------------------------------------------
	#DEFINE ALEN_LINES                                               1
	#DEFINE ALEN_ROWS                                                1
	#DEFINE ALEN_COLS                                                2

	*-----------------------------------------------------------------
	* BackStyle property
	*-----------------------------------------------------------------
	#DEFINE BACKSTYLE_TRANSPARENT                                    0
	#DEFINE BACKSTYLE_OPAQUE                                         1

	*-----------------------------------------------------------------
	* Konstanten für alle SYS() Funktionen. Bitte lesen Sie die Hilfe
	* zu den einzelnen Konstanten, um nähere Informationen zu erhal-
	* ten. Die folgenden SYS() Funktionen sind undokumentiert. Die 
	* hier gebotene Erklärung hat keinen Anspruch auf Richtigkeit:
	* 
	* SYS_DIALOGRESOURCES 
	*
	*   Zeigt alle Dialogresourcen in VFP an. Diese Dialoge sind funk-
	*   tionslos. Der zweite (numerische) Parameter gibt an, welche 
	*   Resource angezeigt werden soll. Sie können die Pfeiltasten 
	*   verwenden, um durch die Resourcen zu blättern.
	*
	* SYS_MEMORYHANDLESINUSE
	*
	*   Gibt die Anzahl der von Visual FoxPro angeforderten Memory-
	*   handles zurück. Wenn diese Zahl zwar steigt, aber nach Ab-
	*   schluß einer Funktion nicht mehr sinkt, liegt ein Speicherleck
	*   vor.
	*
	* SYS_MEMORYAVAILABLE
	*
	*   Gibt in Bytes den Speicher zurück, der für Visual FoxPro noch
	*   zur Verfügung steht. In etwa gilt die folgende Gleichung:
	*
	*     SYS_VFPMEMORY = SYS_MEMORYINUSE + SYS_MEMORYAVAILABLE 
	*
	*-----------------------------------------------------------------
	#DEFINE SYS_MACHINE_USER                                         0
	#DEFINE SYS_JULIANSYSTEMDATE                                     1
	#DEFINE SYS_SECONDS                                              2
	#DEFINE SYS_FILENAME                                             3
	#DEFINE SYS_DEFAULTDRIVE                                         5
	#DEFINE SYS_SETPRINTERTO                                         6
	#DEFINE SYS_SETFORMAT                                            7
	#DEFINE SYS_PRODUCTID                                            9
	#DEFINE SYS_JULIANTODATE                                        10
	#DEFINE SYS_DATETOJULIAN                                        11
	#DEFINE SYS_MEMORY                                              12
	#DEFINE SYS_PRINTSTATUS                                         13
	#DEFINE SYS_KEY                                                 14
	#DEFINE SYS_CHARTRANSLATE                                       15
	#DEFINE SYS_PROGRAM                                             16
	#DEFINE SYS_CPU                                                 17
	#DEFINE SYS_VARREAD                                             18
	#DEFINE SYS_TRANSLATEGERMAN                                     20
	#DEFINE SYS_MASTERINDEX                                         21
	#DEFINE SYS_MASTERTAG                                           22
	#DEFINE SYS_EMSUSAGE                                            23
	#DEFINE SYS_EMSLIMIT                                            24
	#DEFINE SYS_SETCONSOLE                                         100
	#DEFINE SYS_SETDEVICE                                          101
	#DEFINE SYS_SETPRINTER                                         102
	#DEFINE SYS_SETTALK                                            103
	#DEFINE SYS_DIALOGRESOURCES                                    999
	#DEFINE SYS_VFPMEMORY                                         1001
	#DEFINE SYS_MEMORYHANDLESINUSE                                1011
	#DEFINE SYS_MEMORYAVAILABLE                                   1013
	#DEFINE SYS_MEMORYINUSE                                       1016
	#DEFINE SYS_HELPDIAGNOSTICON                                  1023
	#DEFINE SYS_HELPDIAGNOSTICOFF                                 1024
	#DEFINE SYS_PAGESETUP                                         1037
	#DEFINE SYS_PROPERTYINFO                                      1269
	#DEFINE SYS_OBJECTREFERENCE                                   1270
	#DEFINE SYS_OBJECTSCXFILE                                     1271
	#DEFINE SYS_OBJECTHIERARCHY                                   1272
	#DEFINE SYS_DOMENU                                            1500
	#DEFINE SYS_FILESEARCH                                        2000
	#DEFINE SYS_SET                                               2001
	#DEFINE SYS_SETCURSOR                                         2002
	#DEFINE SYS_CURDIR                                            2003
	#DEFINE SYS_HOME                                              2004
	#DEFINE SYS_SETRESOURCE                                       2005
	#DEFINE SYS_VIDEO                                             2006
	#DEFINE SYS_CHECKSUM                                          2007
	#DEFINE SYS_FILES                                             2010
	#DEFINE SYS_LOCKSTATUS                                        2011
	#DEFINE SYS_BLOCKSIZE                                         2012
	#DEFINE SYS_SYSMENU                                           2013
	#DEFINE SYS_MINIMUMPATH                                       2014
	#DEFINE SYS_RANDOMPROCNAME                                    2015
	#DEFINE SYS_SHOWGETSWINDOW                                    2016
	#DEFINE SYS_DISPLAYSIGNONSCREEN                               2017
	#DEFINE SYS_ERRORPARAMETER                                    2018
	#DEFINE SYS_CONFIGFPW                                         2019
	#DEFINE SYS_DISKSIZE                                          2020
	#DEFINE SYS_INDEXFILTER                                       2021
	#DEFINE SYS_CLUSTERSIZE                                       2022
	#DEFINE SYS_TEMPPATH                                          2023
	#DEFINE SYS_TABLETYPE                                         2029
	#DEFINE SYS_VTABLEBINDING                                     2333
	#DEFINE SYS_INVOCATIONMODE                                    2334
	#DEFINE SYS_UNATTENDEDMODE                                    2335
	#DEFINE SYS_GETLOCALEID                                       3004
	#DEFINE SYS_SETLOCALEID                                       3005
	#DEFINE SYS_SETLANGUAGE                                       3006
	#DEFINE SYS_CACHE                                             3050
	#DEFINE SYS_LOCKINTERVAL                                      3051
	#DEFINE SYS_OVERRIDEREPROCESS                                 3052
	#DEFINE SYS_ODBCHANDLE                                        3053
	#DEFINE SYS_RUSHMORE                                          3054
	#DEFINE SYS_WHERECOMPLEXITY                                   3055
	#DEFINE SYS_READREGISTRY                                      3056
	#DEFINE SYS_ACTIVEDOCUMENT                                    4204

	*-----------------------------------------------------------------
	* Zweiter Parameter für SYS(3050), SYS_CACHE
	*-----------------------------------------------------------------
	#DEFINE SYS_CACHE_FOREGROUND                                     1
	#DEFINE SYS_CACHE_BACKGROUND                                     2

	*-----------------------------------------------------------------
	* Set( "Date", 1 ) returns the date format using the following
	* constants.
	*-----------------------------------------------------------------
	#DEFINE SET_DATE1_MDY                                            0
	#DEFINE SET_DATE1_DMY                                            1
	#DEFINE SET_DATE1_YMD                                            2

	*-----------------------------------------------------------------
	* Constants for the DataSession property.
	*-----------------------------------------------------------------
	#DEFINE DATASESSION_DEFAULT                                      1
	#DEFINE DATASESSION_PRIVATE                                      2

	*-----------------------------------------------------------------
	* The second parameter for OBJTOCLIENT()
	*-----------------------------------------------------------------
	#DEFINE OBJTOCLIENT_TOP                                          1
	#DEFINE OBJTOCLIENT_LEFT                                         2
	#DEFINE OBJTOCLIENT_WIDTH                                        3
	#DEFINE OBJTOCLIENT_HEIGHT                                       4

	*-----------------------------------------------------------------
	* The BorderStyle property for many objects
	*-----------------------------------------------------------------
	#DEFINE BORDERSTYLE_TRANSPARENT                                  0
	#DEFINE BORDERSTYLE_SOLID                                        1
	#DEFINE BRODERSTYLE_DASH                                         2
	#DEFINE BORDERSTYLE_DOT                                          3
	#DEFINE BORDERSTYLE_DASH_DOT                                     4
	#DEFINE BORDERSTYLE_DASH_DOT_DOT                                 5
	#DEFINE BORDERSTYLE_INSIDE_SOLID                                 6
	#DEFINE BORDERSTYLE_DEFAULT                      BORDERSTYLE_SOLID

	*-----------------------------------------------------------------
	* The following define can be used in the Init of objects in order
	* to prevent instanciating them. Due to a bug in VFP .F. might not
	* be sufficient and the object won't be released. By manually
	* firing Destroy(), we can be sure that the object is released 
	* properly through the CascadingDestroy. In addition, firing 
	* Destroy() is necessary when the reference tracking feature is
	* used.
	*-----------------------------------------------------------------
	#DEFINE DONTCREATE This.CleanUp() and This.Destroy() and .F.
	
	*-----------------------------------------------------------------
	* Colors for the GetSysColor() API function
	*-----------------------------------------------------------------
	#DEFINE COLOR_SCROLLBAR                                          0
	#DEFINE COLOR_BACKGROUND                                         1
	#DEFINE COLOR_ACTIVECAPTION                                      2
	#DEFINE COLOR_INACTIVECAPTION                                    3
	#DEFINE COLOR_MENU                                               4
	#DEFINE COLOR_WINDOW                                             5
	#DEFINE COLOR_WINDOWFRAME                                        6
	#DEFINE COLOR_MENUTEXT                                           7
	#DEFINE COLOR_WINDOWTEXT                                         8
	#DEFINE COLOR_CAPTIONTEXT                                        9
	#DEFINE COLOR_ACTIVEBORDER                                      10
	#DEFINE COLOR_INACTIVEBORDER                                    11
	#DEFINE COLOR_APPWORKSPACE                                      12
	#DEFINE COLOR_HIGHLIGHT                                         13
	#DEFINE COLOR_HIGHLIGHTTEXT                                     14
	#DEFINE COLOR_BTNFACE                                           15
	#DEFINE COLOR_BTNSHADOW                                         16
	#DEFINE COLOR_GRAYTEXT                                          17
	#DEFINE COLOR_BTNTEXT                                           18
	#DEFINE COLOR_INACTIVECAPTIONTEXT                               19
	#DEFINE COLOR_BTNHIGHLIGHT                                      20
	#DEFINE COLOR_3DDKSHADOW                                        21
	#DEFINE COLOR_3DLIGHT                                           22
	#DEFINE COLOR_INFOTEXT                                          23
	#DEFINE COLOR_INFOBK                                            24
	#DEFINE COLOR_HOTLIGHT                                          26
	#DEFINE COLOR_GRADIENTACTIVECAPTION                             27
	#DEFINE COLOR_GRADIENTINACTIVECAPTION                           28
	#DEFINE COLOR_DESKTOP                             COLOR_BACKGROUND
	#DEFINE COLOR_3DFACE                                 COLOR_BTNFACE
	#DEFINE COLOR_3DSHADOW                             COLOR_BTNSHADOW
	#DEFINE COLOR_3DHIGHLIGHT                       COLOR_BTNHIGHLIGHT
	#DEFINE COLOR_3DHILIGHT                         COLOR_BTNHIGHLIGHT
	#DEFINE COLOR_BTNHILIGHT                        COLOR_BTNHIGHLIGHT
	
	*-----------------------------------------------------------------
	* Die möglichen Rückgabewerte für die Funktion GetFldState().
	*-----------------------------------------------------------------
	#DEFINE GETFLDSTATE_NOCHANGE                                     1
	#DEFINE GETFLDSTATE_EDIT                                         2
	#DEFINE GETFLDSTATE_APPEND                                       3
	#DEFINE GETFLDSTATE_APPENDEDIT                                   4
	
	*-----------------------------------------------------------------
	* GetFldState() kann zwei spezielle Parameter entgegennehmen, die
	* nicht einer Feldnummer entsprechen.
	*-----------------------------------------------------------------
	#DEFINE GETFLDSTATE_DELETECHANGED                                0
	#DEFINE GETFLDSTATE_ALLFIELDS                                   -1
	#DEFINE GETFLDSTATE_RECORD_INFO                                  0
	
	*-----------------------------------------------------------------
	* Die einzelnen Arrayspalten für AError()
	*-----------------------------------------------------------------
	#DEFINE AERROR_COLUMNS                                           7
	#DEFINE AERROR_ERRORCODE                                         1
	#DEFINE AERROR_MESSAGE                                           2
	#DEFINE AERROR_PARAMETER                                         3
	#DEFINE AERROR_NULLFIELD                                         3
	#DEFINE AERROR_WORKAREA                                          4
	#DEFINE AERROR_DATASESSION                                       4
	#DEFINE AERROR_TRIGGER                                           5
	#DEFINE AERROR_OLE_MESSAGE                                       3
	#DEFINE AERROR_OLE_APPLICATION                                   4
	#DEFINE AERROR_OLE_HELPFILE                                      5
	#DEFINE AERROR_OLE_CONTEXTID                                     6
	#DEFINE AERROR_OLE_EXCEPTION                                     7
	#DEFINE AERROR_ODBC_MESSAGE                                      3
	#DEFINE AERROR_ODBC_SQL_STATE                                    4
	#DEFINE AERROR_ODBC_ERROR                                        5
	#DEFINE AERROR_ODBC_CONNECTION_HANDLE                            6
	
	*--------------------------------------------------------------------------------------
	* Konstanten für AEVENTS()
	*--------------------------------------------------------------------------------------
	#DEFINE AEVENTS_SOURCE                                                                0
	#DEFINE AEVENTS_MESSAGES                                                              1
	#DEFINE AEVENTS_WINMSG                                                                1
	
	*--------------------------------------------------------------------------------------
	* Konstanten für die vfpCrypt Komponente
	*--------------------------------------------------------------------------------------
	***
	*** Algorithm Classes
	***
	#DEFINE dnALG_CLASS_ANY          0
	#DEFINE dnALG_CLASS_SIGNATURE    BITLSHIFT(1,13)
	#DEFINE dnALG_CLASS_MSG_ENCRYPT  BITLSHIFT(2,13)
	#DEFINE dnALG_CLASS_DATA_ENCRYPT BITLSHIFT(3,13)
	#DEFINE dnALG_CLASS_HASH         BITLSHIFT(4,13)
	#DEFINE dnALG_CLASS_KEY_EXCHANGE BITLSHIFT(5,13)

	***
	*** Algorithm Types
	***
	#DEFINE dnALG_TYPE_ANY 		 0
	#DEFINE dnALG_TYPE_DSS           BITLSHIFT(1,9)
	#DEFINE dnALG_TYPE_RSA           BITLSHIFT(2,9)
	#DEFINE dnALG_TYPE_BLOCK         BITLSHIFT(3,9)
	#DEFINE dnALG_TYPE_STREAM        BITLSHIFT(4,9)

	***
	*** Generic Sub-ID
	***
	#DEFINE dnALG_SID_ANY            0

	***
	*** Some RSA sub-ids
	***
	#DEFINE dnALG_SID_RSA_ANY        0
	#DEFINE dnALG_SID_RSA_PKCS       1
	#DEFINE dnALG_SID_RSA_MSATWORK   2
	#DEFINE dnALG_SID_RSA_ENTRUST    3
	#DEFINE dnALG_SID_RSA_PGP        4

	***
	*** Some DSS sub-ids
	***
	#DEFINE dnALG_SID_DSS_ANY        0
	#DEFINE dnALG_SID_DSS_PKCS       1
	#DEFINE dnALG_SID_DSS_DMS        2

	***
	*** Block cipher sub ids
	*** DES sub_ids
	***
	#DEFINE dnALG_SID_DES           1
	#DEFINE dnALG_SID_3DES		3
	#DEFINE dnALG_SID_DESX		4
	#DEFINE dnALG_SID_IDEA		5
	#DEFINE dnALG_SID_CAST		6
	#DEFINE dnALG_SID_SAFERSK64	7
	#DEFINE dnALD_SID_SAFERSK128	8

	***
	*** KP_MODE
	***
	#DEFINE dnCRYPT_MODE_CBCI	6	&& ANSI CBC Interleaved
	#DEFINE dnCRYPT_MODE_CFBP	7	&& ANSI CFB Pipelined
	#DEFINE dnCRYPT_MODE_OFBP	8	&& ANSI OFB Pipelined
	#DEFINE dnCRYPT_MODE_CBCOFM	9	&& ANSI CBC + OF Masking
	#DEFINE dnCRYPT_MODE_CBCOFMI	10	&& ANSI CBC + OFM Interleaved

	***
	*** RC2 sub-ids
	***
	#DEFINE dnALG_SID_RC2           2

	***
	*** Stream cipher sub-ids
	***
	#DEFINE dnALG_SID_RC4           1
	#DEFINE dnALG_SID_SEAL          2

	***
	*** Hash sub ids
	***
	#DEFINE dnALG_SID_MD2           1
	#DEFINE dnALG_SID_MD4           2
	#DEFINE dnALG_SID_MD5           3
	#DEFINE dnALG_SID_SHA           4
	#DEFINE dnALG_SID_MAC           5
	#DEFINE dnALG_SID_RIPEMD	6
	#DEFINE dnALG_SID_RIPEMD160	7
	#DEFINE dnALG_SID_SSL3SHAMD5	8

	***
	*** algorithm identifier definitions
	***
	#DEFINE dnCALG_MD2        BITOR(BITOR(dnALG_CLASS_HASH,dnALG_TYPE_ANY),dnALG_SID_MD2)
	#DEFINE dnCALG_MD4        BITOR(BITOR(dnALG_CLASS_HASH,dnALG_TYPE_ANY),dnALG_SID_MD4)
	#DEFINE dnCALG_MD5        BITOR(BITOR(dnALG_CLASS_HASH,dnALG_TYPE_ANY),dnALG_SID_MD5)
	#DEFINE dnCALG_SHA        BITOR(BITOR(dnALG_CLASS_HASH,dnALG_TYPE_ANY),dnALG_SID_SHA)
	#DEFINE dnCALG_MAC        BITOR(BITOR(dnALG_CLASS_HASH,dnALG_TYPE_ANY),dnALG_SID_MAC)
	#DEFINE dnCALG_RSA_SIGN   BITOR(BITOR(dnALG_CLASS_SIGNATURE,dnALG_TYPE_RSA),dnALG_SID_RSA_ANY)
	#DEFINE dnCALG_DSS_SIGN   BITOR(BITOR(dnALG_CLASS_SIGNATURE,dnALG_TYPE_DSS),dnALG_SID_DSS_ANY)
	#DEFINE dnCALG_RSA_KEYX   BITOR(BITOR(dnALG_CLASS_KEY_EXCHANGE,dnALG_TYPE_RSA),dnALG_SID_RSA_ANY)
	#DEFINE dnCALG_DES        BITOR(BITOR(dnALG_CLASS_DATA_ENCRYPT,dnALG_TYPE_BLOCK),dnALG_SID_DES)
	#DEFINE dnCALG_RC2 	  BITOR(BITOR(dnALG_CLASS_DATA_ENCRYPT,dnALG_TYPE_BLOCK),dnALG_SID_RC2)
	#DEFINE dnCALG_RC4 	  BITOR(BITOR(dnALG_CLASS_DATA_ENCRYPT,dnALG_TYPE_STREAM),dnALG_SID_RC4)
	#DEFINE dnCALG_SEAL       BITOR(BITOR(dnALG_CLASS_DATA_ENCRYPT,dnALG_TYPE_STREAM),dnALG_SID_SEAL)

	***
	*** dwFlags definitions for CryptAquireContext
	***
	#DEFINE dnCRYPT_VERIFYCONTEXT     0xF0000000
	#DEFINE dnCRYPT_NEWKEYSET         0x8
	#DEFINE dnCRYPT_DELETEKEYSET      0x10

	***
	*** dwFlag definitions for CryptGenKey
	***
	#DEFINE dnCRYPT_EXPORTABLE        0x00000001
	#DEFINE dnCRYPT_USER_PROTECTED    0x00000002
	#DEFINE dnCRYPT_CREATE_SALT       0x00000004
	#DEFINE dnCRYPT_UPDATE_KEY        0x00000008

	***
	*** exported key blob definitions
	***
	#DEFINE dnSIMPLEBLOB              0x1
	#DEFINE dnPUBLICKEYBLOB           0x6
	#DEFINE dnPRIVATEKEYBLOB          0x7

	#DEFINE dnAT_KEYEXCHANGE          1
	#DEFINE dnAT_SIGNATURE            2

	#DEFINE dnCRYPT_USERDATA          1

	***
	*** dwParam
	***
	#DEFINE dnKP_IV                   1       && Initialization vector
	#DEFINE dnKP_SALT                 2       && Salt value
	#DEFINE dnKP_PADDING              3       && Padding values
	#DEFINE dnKP_MODE                 4       && Mode of the cipher
	#DEFINE dnKP_MODE_BITS            5       && Number of bits to feedback
	#DEFINE dnKP_PERMISSIONS          6       && Key permissions DWORD
	#DEFINE dnKP_ALGID                7       && Key algorithm
	#DEFINE dnKP_BLOCKLEN             8       && Block size of the cipher

	***
	*** KP_PADDING
	***
	#DEFINE dnPKCS5_PADDING           1       && PKCS 5 (sec 6.2) padding method

	***
	*** KP_MODE
	***
	#DEFINE dnCRYPT_MODE_CBC          1       && Cipher block chaining
	#DEFINE dnCRYPT_MODE_ECB          2       && Electronic code book
	#DEFINE dnCRYPT_MODE_OFB          3       && Output feedback mode
	#DEFINE dnCRYPT_MODE_CFB          4       && Cipher feedback mode
	#DEFINE dnCRYPT_MODE_CTS          5       && Ciphertext stealing mode

	***
	*** KP_PERMISSIONS
	***
	#DEFINE dnCRYPT_ENCRYPT           0x0001  && Allow encryption
	#DEFINE dnCRYPT_DECRYPT           0x0002  && Allow decryption
	#DEFINE dnCRYPT_EXPORT            0x0004  && Allow key to be exported
	#DEFINE dnCRYPT_READ              0x0008  && Allow parameters to be read
	#DEFINE dnCRYPT_WRITE             0x0010  && Allow parameters to be set
	#DEFINE dnCRYPT_MAC               0x0020  && Allow MACs to be used with key

	#DEFINE dnHP_ALGID                0x0001  && Hash algorithm
	#DEFINE dnHP_HASHVAL              0x0002  && Hash value
	#DEFINE dnHP_HASHSIZE             0x0004  && Hash value size

	***
	*** CryptGetProvParam
	***
	#DEFINE dnPP_ENUMALGS             1
	#DEFINE dnPP_ENUMCONTAINERS       2
	#DEFINE dnPP_IMPTYPE              3
	#DEFINE dnPP_NAME                 4
	#DEFINE dnPP_VERSION              5
	#DEFINE dnPP_CONTAINER            6

	#DEFINE dnCRYPT_FIRST             1
	#DEFINE dnCRYPT_NEXT              2

	#DEFINE dnCRYPT_IMPL_HARDWARE     1
	#DEFINE dnCRYPT_IMPL_SOFTWARE     2
	#DEFINE dnCRYPT_IMPL_MIXED        3
	#DEFINE dnCRYPT_IMPL_UNKNOWN      4

	***
	*** CryptSetProvParam
	***
	#DEFINE dnPP_CLIENT_HWND          1

	#DEFINE dnPROV_RSA_FULL           1
	#DEFINE dnPROV_RSA_SIG            2
	#DEFINE dnPROV_DSS                3
	#DEFINE dnPROV_FORTEZZA           4
	#DEFINE dnPROV_MS_EXCHANGE        5
	#DEFINE dnPROV_SSL                6

	***
	***STT defined Providers
	***
	#DEFINE dnPROV_STT_MER            7
	#DEFINE dnPROV_STT_ACQ            8
	#DEFINE dnPROV_STT_BRND           9
	#DEFINE dnPROV_STT_ROOT           10
	#DEFINE dnPROV_STT_ISS            11


	#DEFINE dsMS_DEF_PROV_A       "Microsoft Base Cryptographic Provider v1.0"

	#DEFINE dnMAXUIDLEN               64

	#DEFINE dnCUR_BLOB_VERSION        2

	*** Format Message Constants (Part of Window.h)
	#DEFINE dnFORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
	#DEFINE dnFORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
	#DEFINE dnFORMAT_MESSAGE_FROM_STRING     0x00000400
	#DEFINE dnFORMAT_MESSAGE_FROM_HMODULE    0x00000800
	#DEFINE dnFORMAT_MESSAGE_FROM_SYSTEM     0x00001000
	#DEFINE dnFORMAT_MESSAGE_ARGUMENT_ARRAY  0x00002000
	#DEFINE dnFORMAT_MESSAGE_MAX_WIDTH_MASK  0x000000FF

	#DEFINE dcCREATECRYPTKEYS_ERR_LOC	'Cryptographic Service Provider could not be found or'+chr(13)+chr(10)+'Failed to Create Key  Container or'+chr(13)+chr(10)+'Failed to Create Keys in CSP Container'
	#DEFINE dcB	'B'
	#DEFINE dcBR 'BR'
	#DEFINE dcCompleted	'Completed'
	#DEFINE dcCRYPTINITIALIZE_ERR_LOC	'Crypt Service Provider Failed to Acquire'
	#DEFINE dcCRYPTSIGGENKEY_ERR_LOC	'Crypt Service Provider Failed to Create an Signature Key Container'
	#DEFINE dcCRYPTSIGGETKEY_ERR_LOC	'Crypt Service Provider Failed to Return an Signature Key Container'
	#DEFINE dcCRYPTEXCGENKEY_ERR_LOC	'Crypt Service Provider Failed to Create an Exchange Key Container'
	#DEFINE dcCRYPTEXCGETKEY_ERR_LOC	'Crypt Service Provider Failed to Return an Exchange Key Container'
	#DEFINE	dcCRYPTPROVTYP_ERR_LOC	'Crypt Service Provider Not Installed or Not Found'
	#DEFINE dcCRYPTNEWKEYCONTAINER_ERR_LOC 'New Crypt Key Container Could not be Created'
	#DEFINE dcCRYPTDELETEKEYCONTAINER_ERR_LOC 'Crypt Key Container Could not be Deleted'
	#DEFINE dcCRYPTUSEKEYCONTAINER_ERR_LOC 'Crypt Key Container Could not be Opened for Use'
	#DEFINE dcDecryptSessionFileParameter_ERR_LOC	'Must Enter an Encrypted File Name and a Decrypted File Name and'+chr(13)+chr(10)+'a Password'+chr(13)+chr(10)+'in a parameter of this Function'
	#DEFINE	dcDecryptSessionFileNoFile_ERR_LOC	'Encrypted File Could Not be Opened'+chr(13)+chr(10)+'Please Enter a File that Exists and is Not Already Open'
	#DEFINE dcDecryptSessionFileExists_ERR_LOC	'Decrypted File Exists' + chr(13)+chr(10) + 'Do you wish to OverWrite it?'
	#DEFINE dcDecryptSessionFileCreate_ERR_LOC	'Decrypted File Could not be Created/Overwritten'
	#DEFINE	dcDecryptSessionFileWrite_ERR_LOC	'Error Occured During Write of Decryption File'
	#DEFINE dcDecryptSessionFileComplete_LOC	'File Decryption Completed'
	#DEFINE dcEmpty ''
	#DEFINE dcEncryptSessionFileParameter_ERR_LOC	'Must Enter a Decrypted File Name and an Encrypted File Name and'+chr(13)+chr(10)+'a Password'+chr(13)+chr(10)+'in a parameter of this Function'
	#DEFINE	dcEncryptSessionFileNoFile_ERR_LOC	'Decrypted File Could Not be Opened'+chr(13)+chr(10)+'Please Enter a File that Exists and is Not Already Open'
	#DEFINE dcEncryptSessionFileExists_ERR_LOC	'Encrypted File Exists' + chr(13)+chr(10) + 'Do you wish to OverWrite it?'
	#DEFINE dcEncryptSessionFileCreate_ERR_LOC	'Encrypted File Could not be Created/Overwritten'
	#DEFINE	dcEncryptSessionFileWrite_ERR_LOC	'Error Occured During Write of Encryption File'
	#DEFINE dcEncryptSessionFileComplete_LOC	'File Encryption Completed'
	#DEFINE dcError	'ERROR'
	#DEFINE dcErrorCode	'Error Facility - '
	#DEFINE dcErrorFacility	'Error Facility - '
	#DEFINE	dcErrorIn	'Error in '
	#DEFINE dcErrorSeverity	'Error Severity - '
	#DEFINE dcErrorSigningData 'Error Signing Data'
	#DEFINE dcFileExists 'File Exists'
	#DEFINE dcFOXPRO_APP 'FOXPRO_APP'
	#DEFINE dcgetcryptsessionkeyhandleparam 'B,S,BR,SR'
	#DEFINE dcgetcryptsessionkeyhandleERR_LOC	" must be called with parameter picType = 'B' or 'S' or 'BR' or 'SR'"
	#DEFINE	dcSignFileParamter_ERR_LOC	'Must Enter a Signature Reference, a Decrypted File Name, and'+chr(13)+chr(10)+'a password'+chr(13)+chr(10)+'as a parameter to This Function'
	#DEFINE dcSignFileDecryptedFile_ERR_LOC	'Decrypted File Could not be Opened'
	#DEFINE	dcSignFileHashObjcet_ERR_LOC	'Error Creating Hash Object for Signature'
	#DEFINE	dcSignFileHashing_ERR_LOC	'Error Hashing Data'
	#DEFINE dcS	'S'
	#DEFINE dcSR	'SR'

	*--------------------------------------------------------------------------------------
	* Konstanten (diese Werte stammen aus der WiaDef.h, die mit dem Windows 10 SDK 
	* installiert wird).
	*--------------------------------------------------------------------------------------
	#define WIA_DIP_FIRST 2
	#define WIA_RESERVED_FOR_NEW_PROPS 1024
	#define WIA_DPA_FIRST (WIA_DIP_FIRST + WIA_RESERVED_FOR_NEW_PROPS)
	#define WIA_DPC_FIRST (WIA_DPA_FIRST + WIA_RESERVED_FOR_NEW_PROPS)
	#define WIA_DPS_FIRST (WIA_DPC_FIRST + WIA_RESERVED_FOR_NEW_PROPS)
	#define WIA_DPS_DOCUMENT_HANDLING_STATUS (WIA_DPS_FIRST + 13)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT (WIA_DPS_FIRST + 14)
	#define WIA_DPS_PAGES (WIA_DPS_FIRST + 22)
	
	*--------------------------------------------------------------------------------------
	* Werte für WIA_DPS_DOCUMENT_HANDLING_SELECT
	*--------------------------------------------------------------------------------------
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_FEEDER         (0x001)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_FLATBED        (0x002)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_DUPLEX         (0x004)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_FRONT_FIRST    (0x008)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_BACK_FIRST     (0x010)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_FRONT_ONLY     (0x020)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_BACK_ONLY      (0x040)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_NEXT_PAGE      (0x080)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_PREFEED        (0x100)
	#define WIA_DPS_DOCUMENT_HANDLING_SELECT_AUTO_ADVANCE   (0x200)
	
	*--------------------------------------------------------------------------------------
	* Werte für WIA_DPS_DOCUMENT_HANDLING_STATUS
	*--------------------------------------------------------------------------------------
	#define WIA_DPS_DOCUMENT_HANDLING_STATUS_FEED_READY     (0x01)
	#define WIA_DPS_DOCUMENT_HANDLING_STATUS_FLAT_READY     (0x02)
	#define WIA_DPS_DOCUMENT_HANDLING_STATUS_DUP_READY      (0x04)
	#define WIA_DPS_DOCUMENT_HANDLING_STATUS_FLAT_COVER_UP  (0x08)
	#define WIA_DPS_DOCUMENT_HANDLING_STATUS_PATH_COVER_UP  (0x10)
	#define WIA_DPS_DOCUMENT_HANDLING_STATUS_PAPER_JAM      (0x20)
	
	*--------------------------------------------------------------------------------------
	* Werte für die Bildformate
	*--------------------------------------------------------------------------------------
	#define FORMATID_wiaFormatBMP "{B96B3CAB-0728-11D3-9D7B-0000F81EF32E}"
	#define FORMATID_WIAFORMATPNG "{B96B3CAF-0728-11D3-9D7B-0000F81EF32E}"
	#define FORMATID_wiaFormatGIF "{B96B3CB0-0728-11D3-9D7B-0000F81EF32E}"
	#define FORMATID_wiaFormatJPEG "{B96B3CAE-0728-11D3-9D7B-0000F81EF32E}"
	#define FORMATID_wiaFormatTIFF "{B96B3CB1-0728-11D3-9D7B-0000F81EF32E}"
        
	*-----------------------------------------------------------------
	* Allgemeine Konstanten für eine eine simulierte ControlSource. Da
	* wir verschiedene Befehle für Variablen und Felder benötigen, 
	* müssen wir zuvor den Typen ermitteln.
	*-----------------------------------------------------------------
	#DEFINE ccAco_CtrlSource_Auto                                    0
	#DEFINE ccAco_CtrlSource_Var                                     1
	#DEFINE ccAco_CtrlSource_Field                                   2
	#DEFINE ccAco_CtrlSource_Expression                              3
	
	*-----------------------------------------------------------------
	* Mögliche Werte für die Eigenschaft nOpenMode der Komponenten
	* DataBehavior.
	*-----------------------------------------------------------------
	#DEFINE ccAco_DataB_NoOpen                                       0
	#DEFINE ccAco_DataB_Open                                         1
	#DEFINE ccAco_DataB_Apply                                        2
	#DEFINE ccAco_DataB_AutoOpenApply                                3
	#DEFINE ccAco_DataB_OnDemand                                     4
	#DEFINE ccAco_DataB_InOrder                                      5
	
	*-----------------------------------------------------------------
	* verschiedene Konstanten des DataBehaviors
	*-----------------------------------------------------------------
	#DEFINE ccAco_DataB_RecordTable	                                0
	
	*-----------------------------------------------------------------
	* Die Fehlercodes für das Update. Die Konstante 
	* ccAco_DataB_Err_User können Sie als Ausgangspunkt für eigene
	* Fehlernummern verwenden. Dies ist die erste Nummer, die zur Ver-
	* fügung steht.
	*-----------------------------------------------------------------
	#DEFINE ccAco_DataB_Err_Transaction_Failed                  100000
	#DEFINE ccAco_DataB_Err_Update_Not_Allowed                  100001
	#DEFINE ccAco_DataB_Err_Update_Failure                      100002
	#DEFINE ccAco_DataB_Err_User                                200000
	
	*-----------------------------------------------------------------
	* Die Möglichen Werte der Eigenschaft nQueryMode der Komponente
	* DataBehavior.
	*-----------------------------------------------------------------
	#DEFINE ccAco_DataB_SourceNone                                   0
	#DEFINE ccAco_DataB_SourceProperties                             1
	#DEFINE ccAco_DataB_SourceValues                                 2
	#DEFINE ccAco_DataB_SourceValuesFallBack                         3

	*-----------------------------------------------------------------
	* Mögliche Werte für die Eigenschaft nSkipMode der Komponente
	* IONavControl.
	*-----------------------------------------------------------------
	#DEFINE ccAco_IONav_SkipCycle                                    0
	#DEFINE ccAco_IONav_SkipEnable                                   1
	#DEFINE ccAco_IONav_SkipDisable                                  2
	
	*-----------------------------------------------------------------
	* Mögliche Werte für die Eigenschaft nAutoRefreshType der Kompo-
	* nente IONavControl.
	*-----------------------------------------------------------------
	#DEFINE ccAco_IONav_RefreshContainer                             1
	#DEFINE ccAco_IONav_RefreshControl                               2
	
	*-----------------------------------------------------------------
	* Mögliche Werte für die Eigenschaft nAskQueryUnload der Kompo-
	* nente IONavControl.
	*-----------------------------------------------------------------
	#DEFINE ccAco_IONav_OnCloseAsk                                   0
	#DEFINE ccAco_IONav_OnCloseSave                                  1
	#DEFINE ccAco_IONav_OnCloseRevert                                2
	
	*-----------------------------------------------------------------
	* Mögliche Werte der Eigenschaft nGetData der Komponente
	* LocalViewBehavior
	*-----------------------------------------------------------------
	#DEFINE ccAco_ViewDB_NoData                                      0
	#DEFINE ccAco_ViewDB_Use                                         1
	#DEFINE ccAco_ViewDB_UseAndRequery                               2
	
	*-----------------------------------------------------------------
	* Die diversen Arrays in der Komponente UpdateConflictHandler
	*-----------------------------------------------------------------
	#DEFINE ccAco_UpCnfHnd_ConflictColumns                           5
	#DEFINE ccAco_UpCnfHnd_ConflictRef                               1
	#DEFINE ccAco_UpCnfHnd_ConflictRecNo                             2
	#DEFINE ccAco_UpCnfHnd_ConflictTryAgain                          3
	#DEFINE ccAco_UpCnfHnd_ConflictType                              4
	#DEFINE ccAco_UpCnfHnd_ConflictData                              5

	*-----------------------------------------------------------------
	* Das Array aContainer des MultiContainerController's
	*-----------------------------------------------------------------
	#DEFINE ccAco_MCC_Columns                                        5
	#DEFINE ccAco_MCC_Name                                           1
	#DEFINE ccAco_MCC_Class                                          2
	#DEFINE ccAco_MCC_Reference                                      3
	#DEFINE ccAco_MCC_DE_Name                                        4
	#DEFINE ccAco_MCC_DE_Class                                       5
	
	*-----------------------------------------------------------------
	* Das Array aPipes der Komponente srvNamedPipeManager
	*-----------------------------------------------------------------
	#DEFINE ccAco_Pipe_Columns                                       4
	#DEFINE ccAco_Pipe_Name                                          1
	#DEFINE ccAco_Pipe_Count                                         2
	#DEFINE ccAco_Pipe_Receiver                                      3
	#DEFINE ccAco_Pipe_Sender                                        4

	*-----------------------------------------------------------------
	* Intermediate Layer. Es gibt zwei Intermediate-Dateien. Die Datei
	* iAcodey.H wird für die eigentliche Programmversion verwendet.
	* Die Datei iAcodeyD.H enthält die Konstanten, die in der Debug-
	* Version verwendet werden sollen. Umgeschaltet werden zwischen
	* den beiden kann über die Eigenschaft _SCREEN.AcodeyBuild, die
	* bei Bedarf hinzugefügt werden kann. Sie kann die Werte RELEASE
	* oder DEBUG annenehmen. Alle andere Werte werden als RELEASE ge-
	* wertet. Die Namen der Include-Dateien sind selbstverständlich
	* ebenfalls konfigurierbar.
	*
	* WICHTIG: In VFP 5 ist dies auf Grund eines Bugs nicht möglich.
	*          Dort führt jeder Zugriff auf eine Variable innerhalb
	*          einer #IF Zeile sofort zu einem GPF. Daher wird in 
	*          VFP 5 immer die Datei iAcodey.H inkludiert. Sollten Sie
	*          unterschiedliche Werte benötigen, müssen Sie dort über
	*          #IF selbst andere Werte setzen.
	*
	*-----------------------------------------------------------------
*!*		#IF __VFP6
*!*			#DEFINE ccLocalSelectFile ;
*!*				Type("_Screen.AcodeyBuild") == T_CHARACTER
*!*		#ELSE
		#DEFINE ccLocalSelectFile .F.
*!*		#ENDIF
	#IF ccLocalSelectFile
		#UNDEF ccLocalSelectFile
		#DEFINE ccLocalSelectFile ;
			Upper(_Screen.AcodeyBuild) == "DEBUG"
	#ELSE
		#UNDEF ccLocalSelectFile
		#DEFINE ccLocalSelectFile .F.
	#ENDIF
	#IF ccLocalSelectFile
		__FILE_IACODEYD
	#ELSE
		__FILE_IACODEY
	#ENDIF
	#UNDEF ccLocalSelectFile
	
	*:IFFEAT ActiveDebugging
	*-----------------------------------------------------------------
	* Assertion message. This macro already includes some general
	* information about the object, causing the assertion.
	*-----------------------------------------------------------------
	#IF __VFP5
		#DEFINE ASSMSG MESSAGE ;
			"Assertion failed on " + ;
			Iif( ;
				Type("m.This") == "O", ;
				"object " + Lower(Sys(1272,m.This)), ;
				"current program" ;
			) + ;
			", line number " + Alltrim(Str(LineNo(1))) + ;
			":" +
	#ELSE
		#DEFINE ASSMSG MESSAGE ;
			"Assertion failed on " + ;
			Iif( Type("m.This")=="O", "object ", "program " ) + ;
			Lower(Program(Program(-1))) + ;
			", line number " + Alltrim(Str(LineNo(1))) + ;
			":" +
	#ENDIF

	*-----------------------------------------------------------------
	* Common assertions and conditions.
	*-----------------------------------------------------------------
	#DEFINE ASSERT_ACODEY_FLL ;
		 Type("AcodeyGetVersion()") == T_NUMERIC
	#DEFINE ASSERT_FOXTOOLS_FLL ;
		 Type("_WMainWind()") == T_NUMERIC
	#DEFINE ASSERT_GPFPRG ;
		Upper([__GLOBALPROCEDUREFILE.]) $ Upper(Set("Procedure"))

	*-----------------------------------------------------------------
	* Defines how much Acodey supports you in debugging. There are
	* 4 defined levels:
	*
	*  0   no debugging at all. Produces the fastest code, but only
	*      should be used in the release version.
	*      __DEBUG_NONE
	*
	*  1   regular debugging. Parameters are asserted, a few checks
	*      are performed
	*      __DEBUG_REGULAR
	*
	*  2   advanced debugging. Whenver possible, Acodey helps you 
	*      with debugging, but Acodey doesn't try finding bugs on its
	*      own. Recommended setting during development.
	*      __DEBUG_ADVANCED
	*
	*  3   ActiveDebugging. Acodey actively locates bugs, verifies
	*      data integrity, etc.
	*      __DEBUG_ACTIVE
	*
	*-----------------------------------------------------------------
	#IfnDef __DEBUGLEVEL
		#Define __DEBUGLEVEL __DEBUG_ADVANCED
	#Endif
	#IF Type( [__DEBUGLEVEL] ) # T_NUMERIC
		__ERRMSG "__DEBUGLEVEL" must be numeric
		__SHOWERROR
		#UNDEF __DEBUGLEVEL
		#DEFINE __DEBUGLEVEL __DEBUG_ADVANCED
	#ENDIF
	#IF not InList( __DEBUGLEVEL, ;
			__DEBUG_NONE, ;
			__DEBUG_REGULAR, ;
			__DEBUG_ADVANCED, ;
			__DEBUG_ACTIVE ;
		)
		__ERRMSG "__DEBUGLEVEL" must be between 0 ("__DEBUG_NONE") ;
		         and 3 ("__DEBUG_ACTIVE"). It's currently ;
		         <__DEBUGLEVEL>
		__SHOWERROR
		#UNDEF __DEBUGLEVEL
		#DEFINE __DEBUGLEVEL __DEBUG_ADVANCED
	#ENDIF
	
	*-----------------------------------------------------------------
	* Defensive programming means that whenever possible, Acodey 
	* tries to resolve conflicts itself. This could be wrong 
	* parameters, a not loaded procedure file, etc. if you set the
	* following define to .T., Acodey will behave defensively, with
	* .F. it expects everything to be all right and crash if it's not.
	* The advantage of defensive programming is that it makes an
	* application more stable. The disadvantages are that it first of
	* all hides bugs. This means, there might be bugs in your code
	* that need to be fixed, but you won't find them, because Acodey
	* tries to fix them itself. This could be a bad thing if the
	* solution of Acodey is not what you intended. The second dis-
	* advantage is that it makes the program slower. If you really
	* need performance, turn off defensive programming. Whenever
	* Acodey attempts to fix something, it will warn you by 
	* displaying an assertion dialog. If you SET ASSERT ON and you get
	* such a dialog, you should fix the bug and not ignore this 
	* message! 
	* If you tested the code thoroughfully and haven't got such a
	* message, chances are good, your code don't need defensive
	* programming. Then turn it off.
	*-----------------------------------------------------------------
	#IFNDEF __DEFENSIVE_PROGRAMMING
		#DEFINE __DEFENSIVE_PROGRAMMING .T.
	#ENDIF
	#IF Type( [__DEFENSIVE_PROGRAMMING] ) # "L"
		__ERRMSG "__DEFENSIVE_PROGRAMMING" must be logical.
		__SHOWERROR
		#UNDEF __DEFENSIVE_PROGRAMMING
		#DEFINE __DEFENSIVE_PROGRAMMING .T.
	#ENDIF
	
	*-----------------------------------------------------------------
	* Bei __BACKWARD_WARN geben wir eine Assert-Meldung aus, sobald
	* wir auf einen Fall treffen, wo die Rückwärtskompatibilität zum
	* tragen kommt. Es muß immer im Anschluß die Nummer angegeben wer-
	* den.
	*-----------------------------------------------------------------
	#DEFINE ASSERTBACKWARD Assert .F. ASSMSG ;
		"Backward compatibility issue discovered: "+

	*:ENDFEAT

	*:IFFEAT ReferenceTracking
	*-----------------------------------------------------------------
	* Reference Tracking ist ein Feature von Acodey, mit dessen Hilfe 
	* Sie schnell hängende Referenzen und ähnliche Probleme entdecken
	* können. Aufgrund von Fehlern in VFP wird ein Objekt manchmal 
	* nicht freigegeben oder das Cascading Destroy versagt. Wenn Sie
	* diese Option auf .T. setzen, registriert sich jede Klasse, die
	* auf den Acodey-Basisklassen basiert sobald es erzeugt und wenn
	* es freigegeben wird. In der Tracking-Tabelle können Sie sehen,
	* welche Objekte derzeit noch existieren.
	*-----------------------------------------------------------------
	#IFNDEF __REFERENCE_TRACKING
		#DEFINE __REFERENCE_TRACKING .F.
	#ENDIF
	#IF Type([__REFERENCE_TRACKING]) # T_LOGICAL
		__ERRMSG "__REFERENCE_TRACKING" must be logical.
		__SHOWERROR
		#UNDEF __REFERENCE_TRACKING
		#DEFINE __REFERENCE_TRACKING .F.
	#ENDIF
	
	*-----------------------------------------------------------------
	* Die folgende Konstante definiert den Namen und Ort der Tracking-
	* Tabelle. Standardmäßig ist dies das HOME() Verziechnis von VFP.
	* In der Entwicklungsumgebung ist dies das Verzeichnis, in das Sie
	* VFP installiert haben, in der Laufzeitversion das Verzeichnis,
	* in dem sich die Runtimebibliothek befindet (normalerweise das
	* \WINDOWS\SYSTEM Verzeichnis). Wenn Sie einen eigenen Pfad defi-
	* nieren, stellen Sie sicher, daß es sich um einen absoluten Pfad
	* handelt, damit dieser unabhängig vom aktuellen Verzeichnis in 
	* der Applikation ist.
	*-----------------------------------------------------------------
	#IFNDEF __REFERENCE_TRACKING_TABLE
		#DEFINE __REFERENCE_TRACKING_TABLE ;
			Home() + "RefTrack.Dbf"
	#ENDIF
	#IF Type([__REFERENCE_TRACKING_TABLE]) # T_CHARACTER
		__ERRMSG "__REFERENCE_TRACKING_TABLE" must be a string.
		__SHOWERROR
		#UNDEF __REFERENCE_TRACKING_TABLE
		#DEFINE __REFERENCE_TRACKING_TABLE ;
			Home() + "RefTrack.Dbf"
	#ENDIF
	
	*-----------------------------------------------------------------
	* Das ReferenceTracking funktioniert, indem es ein Objekt zu 
	* _SCREEN hinzufügt. Dies gibt Ihnen mehr Kontrolle über den
	* Tracking-Verlauf, da Sie diese Möglichkeit jederzeit ein- bzw.
	* ausschalten können. Diese Konstante definiert den Namen des 
	* Tracking-Objektes in _SCREEN. Standardmäßig ist das __RefTrack,
	* aber Sie können jden gültigen Namen wählen, den Sie möchten.
	*-----------------------------------------------------------------
	#IFNDEF __REFERENCE_TRACKING_OBJ
		#DEFINE __REFERENCE_TRACKING_OBJ __RefTrack
	#ENDIF
	#IF not ( Empty(ChrTran( ;
	          [__REFERENCE_TRACKING_OBJ],__VALID_NAME_CHARS,""));
	    and (  IsAlpha([__REFERENCE_TRACKING_OBJ]) ;
	        or Left([__REFERENCE_TRACKING_OBJ],1) == "_" ) )
		__ERRMSG "__REFERENCE_TRACKING_OBJ": ;
		         <__REFERENCE_TRACKING_OBJ> is not a valid object name.
		__SHOWERROR 
		#UNDEF __REFERENCE_TRACKING_OBJ
		#DEFINE __REFERENCE_TRACKING_OBJ __RefTrack
	#ENDIF
	
	*-----------------------------------------------------------------
	* Sie können jede beliebige Klasse als ReferenceTracking Objekt
	* definieren. Diese Klasse muß folgende Bedingungen erfüllen:
	*  - Es muß eine AddTracking() Methode haben
	*  - Es muß eine RemoveTracking() Methode haben
	*  - Es muß eine lEnabled Eigenschaft haben.
	*  - Es darf nicht auf einer Acodey-Basisklasse basieren, da diese
	*    Klassen das Reference-Tracking im Init aufrufen. Dies würde
	*    eine Endlosschleife verursachen.
	* Die folgende Konstante enthält die zu verwendende Klasse in 
	* LC-Notation.
	*-----------------------------------------------------------------
	#IFNDEF __REFERENCE_TRACKING_CLASS
		*:SECTION RefTrackClass
		#DEFINE __REFERENCE_TRACKING_CLASS "Reftrack.Vcx;RefTrack"
		*:ENDSECTION
	#ENDIF
	#IF Type([__REFERENCE_TRACKING_CLASS]) # T_CHARACTER
		__ERRMSG "__REFERENCE_TRACKING_CLASS" must be a string.
		__SHOWERROR
		#UNDEF __REFERENCE_TRACKING_CLASS
		*:SECTION RefTrackClass
		#DEFINE __REFERENCE_TRACKING_CLASS "Reftrack.Vcx;RefTrack"
		*:ENDSECTION
	#ENDIF
	
	*-----------------------------------------------------------------
	* Standardmäßig wird das ReferenceTracking aktiviert, sobald Sie
	* die Prozedur InitReferenceTracking() aufrufen. Sie können es zur
	* Laufzeit ein- und ausschalten, in dem Sie die lEnabled Eigen-
	* schaft des ReferenceTracking-Objektes ändern. Wenn das Refe-
	* renceTracking beim Start deaktiviert sein soll, setzen Sie die
	* folgende Konstante auf .F.
	*-----------------------------------------------------------------
	#IFNDEF __REFERENCE_TRACKING_ENABLED
		#DEFINE __REFERENCE_TRACKING_ENABLED .T.
	#ENDIF
	#IF Type([__REFERENCE_TRACKING_ENABLED]) # T_LOGICAL
		__ERRMSG "__REFERENCE_TRACKING_ENABLED" must be logical.
		__SHOWERROR
		#UNDEF __REFERENCE_TRACKING_ENABLED
		#DEFINE __REFERENCE_TRACKING_ENABLED .T.
	#ENDIF
	*:ENDFEAT
	
	*:IFFEAT GlobalService
	*-----------------------------------------------------------------
	* Konstanten für den Global Service Broker
	*-----------------------------------------------------------------
	#IFNDEF __GLOBAL_SERVICE_BROKER
		#DEFINE __GLOBAL_SERVICE_BROKER __Acodey__GSB__
	#ENDIF
	#IFNDEF __GLOBAL_SERVICE_BROKER_CLASS
		*:SECTION GSBClass
		#DEFINE __GLOBAL_SERVICE_BROKER_CLASS ;
		        "GlobalServiceBroker.Vcx;GlobalServiceBroker"
		*:ENDSECTION
	#ENDIF
	*:ENDFEAT
	
	*-----------------------------------------------------------------
	* Defines the language that your application should use for
	* interface operations. This is independant of the runtime version
	* you are using. THE LIB uses the ISO 639 code for the language.
	* Possible values for this define are
	* "de"   German
	* "en"   English
	* If you want to create a German application, but use an English
	* runtime, or viceversa, check out the _VFP_LANGUAGE define 
	* below. 
	*-----------------------------------------------------------------
	#IFNDEF __ACODEY_LANGUAGE
		#DEFINE __ACODEY_LANGUAGE "de"
	#ENDIF
	#IF Type( [__ACODEY_LANGUAGE] ) # "C"
		#UNDEF __ACODEY_LANGUAGE
		#DEFINE __ACODEY_LANGUAGE "de"
		__ERRMSG "__ACODEY_LANGUAGE" must be a character
		__SHOWERROR
	#ENDIF
	#IF not InList(__ACODEY_LANGUAGE,"de","en")
		__ERRMSG "__ACODEY_LANGUAGE" must be 'de' or 'en', ;
		         currently it's <__ACODEY_LANGUAGE>.
		__SHOWERROR
		#UNDEF __ACODEY_LANGUAGE
		#DEFINE __ACODEY_LANGUAGE "de"
	#ENDIF
	
	*-----------------------------------------------------------------
	* This setting defines the runtime you are using. Usually it is
	* determined automatically, so you don't have to change the 
	* setting, it always matches the version of VFP, you are using.
	* Only change this setting if you are using a different version
	* of VFP when compiling than when executing the application. 
	* Changing this value without need, might result in unpredictable
	* results.
	*-----------------------------------------------------------------
	#IF Version(3) == "00"
		#DEFINE __VFP_LANGUAGE_Internal "en"
	#ELIF Version(3) == "49"
		#DEFINE __VFP_LANGUAGE_Internal "de"
	#ELSE
		#DEFINE __VFP_LANGUAGE_Internal "en"
	#ENDIF
	#IFNDEF __VFP_LANGUAGE
		#DEFINE __VFP_LANGUAGE __VFP_LANGUAGE_Internal
	#ENDIF
	#IF Type( [__VFP_LANGUAGE] ) # "C"
		__ERRMSG "__VFP_LANGUAGE" must be a string.
		__SHOWERROR
		#UNDEF __VFP_LANGUAGE
		#DEFINE __VFP_LANGUAGE __VFP_LANGUAGE_Internal
	#ENDIF
	#IF not InList(__VFP_LANGUAGE,"de","en")
		__ERRMSG "__VFP_LANGUAGE": Unsupported runtime version ;
		         <__VFP_LANGUAGE>. Using __VFP_LANGUAGE_Internal ;
		         instead.
		__SHOWERROR
		#UNDEF __VFP_LANGUAGE
		#DEFINE __VFP_LANGUAGE __VFP_LANGUAGE_Internal
	#ENDIF
	#UNDEF __VFP_LANGUAGE_Internal

	*-----------------------------------------------------------------
	* NewObject() und NEWOBJECT() haben beide ein gravierendes Pro-
	* blem. Sie laden die angebene Klassenbibliothek immer nach. 
	* In einigen Applikationen aber ist dies nocht das korrekte Ver-
	* halten, weil die Klassenbibliothek unter Umständen gar nicht
	* im Zugriff ist. In diesem Fall kann über __USE_NEWOBJECT die
	* Verwendung dieser Funktion/Methode deaktiviert werden.
	*-----------------------------------------------------------------
	#IFNDEF __USE_NEWOBJECT
		#DEFINE __USE_NEWOBJECT .T.
	#ENDIF
	#IF Type( [__USE_NEWOBJECT] ) # T_LOGICAL
		#UNDEF __USE_NEWOBJECT
		#DEFINE __USE_NEWOBJECT .T.
		__ERRMSG "__USE_NEWOBJECT" must be logical
		__SHOWERROR
	#ENDIF
		
	*-----------------------------------------------------------------
	* Die sprachabängigen Konstanten für die Applikation einbinden.
	* Dies umfaßt alle Texte, die in Acodey-Komponenten verwendet
	* werden mit Ausnahme der Texte für das Debugging.
	*-----------------------------------------------------------------
	#IF __ACODEY_LANGUAGE == "de"
		__FILE_ACO_LDE
	#ELIF __ACODEY_LANGUAGE == "en"
		__FILE_ACO_LEN
	#ELSE
		__ERRMSG "__ACODEY_LANGUAGE" must be 'de' or 'en'
		__SHOWERROR
	#ENDIF		

	*-----------------------------------------------------------------
	* Sprachabängige Konstanten für lokalisierte Strings in VFP
	* einbinden. Dies hängt von der verwendeten VFP-Version, und 
	* nicht der Sprache der Appliaktion ab.
	*-----------------------------------------------------------------
	#IF __VFP_LANGUAGE == "de"
		#IFNDEF VFPLOC_TB_ColorPalette
			#DEFINE VFPLOC_TB_ColorPalette "Farbpalette"
		#ENDIF
		#IFNDEF VFPLOC_TB_DatabaseDesigner
			#DEFINE VFPLOC_TB_DatabaseDesigner "Datenbank-Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_FormControls
			#DEFINE VFPLOC_TB_FormControls "Formular-Steuerelemente"
		#ENDIF
		#IFNDEF VFPLOC_TB_FormDesigner
			#DEFINE VFPLOC_TB_FormDesigner "Formular-Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_Layout
			#DEFINE VFPLOC_TB_Layout "Layout"
		#ENDIF
		#IFNDEF VFPLOC_TB_PrintPreview
			#DEFINE VFPLOC_TB_PrintPreview "Seitenansicht"
		#ENDIF
		#IFNDEF VFPLOC_TB_QueryDesigner
			#DEFINE VFPLOC_TB_QueryDesigner "Abfrage-Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_ReportControls
			#DEFINE VFPLOC_TB_ReportControls "Bericht-Steuerelemente"
		#ENDIF
		#IFNDEF VFPLOC_TB_ReportDesigner
			#DEFINE VFPLOC_TB_ReportDesigner "Berichts-Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_Standard
			#DEFINE VFPLOC_TB_Standard "Standard"
		#ENDIF
		#IFNDEF VFPLOC_TB_ViewDesigner
			#DEFINE VFPLOC_TB_ViewDesigner "Ansichts-Designer"
		#ENDIF
	#ELIF __VFP_LANGUAGE == "en"
		#IFNDEF VFPLOC_TB_ColorPalette
			#DEFINE VFPLOC_TB_ColorPalette "Color Palette"
		#ENDIF
		#IFNDEF VFPLOC_TB_DatabaseDesigner
			#DEFINE VFPLOC_TB_DatabaseDesigner "Database Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_FormControls
			#DEFINE VFPLOC_TB_FormControls "Form Controls"
		#ENDIF
		#IFNDEF VFPLOC_TB_FormDesigner
			#DEFINE VFPLOC_TB_FormDesigner "Form Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_Layout
			#DEFINE VFPLOC_TB_Layout "Layout"
		#ENDIF
		#IFNDEF VFPLOC_TB_PrintPreview
			#DEFINE VFPLOC_TB_PrintPreview "Preview"
		#ENDIF
		#IFNDEF VFPLOC_TB_QueryDesigner
			#DEFINE VFPLOC_TB_QueryDesigner "Query Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_ReportControls
			#DEFINE VFPLOC_TB_ReportControls "Report Controls"
		#ENDIF
		#IFNDEF VFPLOC_TB_ReportDesigner
			#DEFINE VFPLOC_TB_ReportDesigner "Report Designer"
		#ENDIF
		#IFNDEF VFPLOC_TB_Standard
			#DEFINE VFPLOC_TB_Standard "Standard"
		#ENDIF
		#IFNDEF VFPLOC_TB_ViewDesigner
			#DEFINE VFPLOC_TB_ViewDesigner "View Designer"
		#ENDIF
	#ELSE
		__ERRMSG Unsupported runtime version
		__SHOWERROR
	#ENDIF		

	*-----------------------------------------------------------------
	* Wenn __CHECK_DANGLING_REFERENCES auf .T. gesettzt wird, werden
	* einige zusätzliche Tests gefahren, um auf hängende Referenzen,
	* falsche Shutdown-Reihenfolgen, etc. zu prüfen. Nicht alles, was
	* hier gemeldet wird, ist unbedingt ein Fehler, aber es sollte
	* alles überprüft werden, und wenn es möglich ist, sollte der Code
	* so umgeschrieben werden, daß es keine Meldung mehr gibt.
	*
	* Wenn nur die Möglichkeit besteht, daß es sich um ein Problem 
	* handelt, wird die Meldung über DEBUGOUT gemacht, nicht über 
	* einen ASSERT-Dialog. Nur falls die Wahrscheinlichkeit hoch ist,
	* daß es sich tatsächlich um einen Fehler handelt, bekommen Sie
	* den Dialog.
	*
	*-----------------------------------------------------------------
	#IFNDEF __CHECK_DANGLING_REFERENCES
		#IF __DEBUGLEVEL >= __DEBUG_ACTIVE
			#DEFINE __CHECK_DANGLING_REFERENCES .T.
		#ELSE
			#DEFINE __CHECK_DANGLING_REFERENCES .F.
		#ENDIF
	#ENDIF
	#IF Type( [__CHECK_DANGLING_REFERENCES] ) # T_LOGICAL
		#UNDEF __CHECK_DANGLING_REFERENCES
		#IF __DEBUGLEVEL >= __DEBUG_ACTIVE
			#DEFINE __CHECK_DANGLING_REFERENCES .T.
		#ELSE
			#DEFINE __CHECK_DANGLING_REFERENCES .F.
		#ENDIF
		__ERRMSG "__CHECK_DANGLING_REFERENCES" must be logical
		__SHOWERROR
	#ENDIF
	
	*-----------------------------------------------------------------
	* Acodey bietet eine Optimierung an. Dies wird in der Regel 
	* dadurch erreicht, das Abfragen für seltene Fälle entfallen.
	* Sollten diese Fälle dennoch bei Ihnen auftreten, kann es aller-
	* dings uu Fehlverhalten führen. Mögliche Folgeerscheinungen sind
	* immer im Quelltext beschrieben, wenn Code optimiert werden kann.
	* Die Auswirkung der Optimierung kann durchaus beträchtlich sein.
	* So ist beispielsweise das Freigeben von Objekten mit aktivierte
	* Optimierung etwa 80% schneller. Zusammen mit dem Deaktivieren 
	* des Debugmodus und der defensiven Programmierung kann eine App-
	* likation durchaus 50% schneller laufen. Allerdings müssen Sie
	* dann besondere Vorsicht walten lassen, daß Ihre Applikation 
	* wirklich fehlerfrei ist, denn eine optimierte Applikation ver-
	* gibt Fehler nicht, sondern stürzt einfach ab.
	*-----------------------------------------------------------------
	#IFNDEF __ACODEY_OPTIMIZATION
		#DEFINE __ACODEY_OPTIMIZATION .F.
	#ENDIF
	#IF Type( [__ACODEY_OPTIMIZATION] ) # "L"
		#UNDEF __ACODEY_OPTIMIZATION
		#DEFINE __ACODEY_OPTIMIZATION .F.
		__ERRMSG "__ACODEY_OPTIMIZATION" must be a logical
		__SHOWERROR
	#ENDIF
	
	*-----------------------------------------------------------------
	* Zwischen Visual FoxPro 5 und den nachfolgenden Versionen beste-
	* hen teilweise gravierende Unterschiede bei der Freigabe von Ob-
	* jekten. Die offensichtlichste Erscheinungsform ist, daß das 
	* Cascading Destroy in VFP 6 nur noch eingeschränkt funktioniert.
	* Ohne Abstürze geht es nur von Statten, wenn keine hängenden Re-
	* ferenzen vorliegen und außerdem das Release eines Objektes di-
	* rekt aus einem im enthaltenen Objekt getriggert wird. Wird da-
	* gegen zum Beispiel aus einem Toolbar eine Methode eines Objek-
	* tes auf dem Formular aufgerufen, die dann Thisform.Release()
	* durchführt, führt dies mit nahezu tödlicher Sicherheit zu einem
	* Absturz. 
	*
	* Im Gegensatz zum Vorgängerprodukt THE LIB verwaltet Acodey die
	* Referenzen nun anständig und verfügt über ein ausgefeiltes Kon-
	* zept zum CleanUp(). Daher ist hier ein Cascading Destroy nicht
	* nur überflüssig, sondern oftmals auch erst die Ursache für Ab-
	* stürze.
	*
	* Damit Sie aber dennoch Komponenten aus THE LIB verwenden können
	* bzw. in Ihrem Code nicht nach hängenden Referenzen suchen müs-
	* sen, gibt es drei Einstellungen:
	*
	*  __CD_ALWAYS      Es wird immer ein Cascading Destroy durchge-
	*                   führt. 
	*
	*  __CD_NEVER       Es wird kein Cascading Destroy durchgeführt
	*                   und der Code wird auch nicht in die Applika-
	*                   tion eingebunden.
	*
	*  __CD_DEPENDS     Das Cascading Destroy wird über das Property
	*                   lCascadingDestroy gesteuert, das standardmäßig
	*                   auf .T. gesetzt ist. Für die Komponenten, bei
	*                   denen kein Cascading Destroy notwendig ist, 
	*                   können Sie diese Eigenschaft dann auf .F. set-
	*                   zen, bzw. dies in den Basisklassen pauschal 
	*                   für alle Komponenten deaktivieren und bei Be-
	*                   darf wieder aktivieren.
	*
	* Die Standardwerte sind für VFP 5 __CD_ALWAYS und für VFP 6 
	* __CD_DEPENDS verwendet, es sei denn, Sie haben die Konstante 
	* __ACODEY_OPTIMIZATION auf .T. gesetzt. Dann wird in beiden Ver-
	* sionen __CD_NEVER verwendet.
	*
	*-----------------------------------------------------------------
	#IF __ACODEY_OPTIMIZATION
		#DEFINE ccLocalCascadingDestroy __CD_NEVER
	#ELSE
		#IF __VFP6
			#DEFINE ccLocalCascadingDestroy __CD_DEPENDS
		#ELSE
			#DEFINE ccLocalCascadingDestroy __CD_ALWAYS
		#ENDIF
	#ENDIF
	#IFNDEF __CASCADING_DESTROY
		#DEFINE __CASCADING_DESTROY ccLocalCascadingDestroy
	#ENDIF
	#IF Type( [__CASCADING_DESTROY] ) # "N"
		#UNDEF __CASCADING_DESTROY
		#DEFINE __CASCADING_DESTROY ccLocalCascadingDestroy
		__ERRMSG "__CASCADING_DESTROY" must be numeric
		__SHOWERROR
	#ENDIF
	#UNDEF ccLocalCascadingDestroy
	
	*:IFCOMP PL0001
	*-----------------------------------------------------------------
	* KOMPATIBILITÄT PL0001: 
	*   Im Iterator ist das Ereignis eventDrillDown() durch die DO-
	*   Methode DoHandleObject() ausgetauscht worden. Dies geschah,
	*   um die Konsistenz zu wahren.
	*-----------------------------------------------------------------
	#IFNDEF __BACKWARD_PL0001
		#DEFINE __BACKWARD_PL0001 __BACKWARD_YES
	#ENDIF
	*:ENDCOMP
	
	*------------------------------------------------------------------
	* Debugoption für die Zeitmessung des IOControl
	*------------------------------------------------------------------
	#IFNDEF __DEBUG_IOCONTROL_TIMING
		#IF __DEBUGLEVEL >= __DEBUG_ACTIVE
			#DEFINE __DEBUG_IOCONTROL_TIMING .T.
		#ELSE
			#DEFINE __DEBUG_IOCONTROL_TIMING .F.
		#ENDIF
	#ENDIF
	#IF Type( [__DEBUG_IOCONTROL_TIMING] ) # "L"
		#UNDEF __DEBUG_IOCONTROL_TIMING
		#DEFINE __DEBUG_IOCONTROL_TIMING .F.
		__ERRMSG "__DEBUG_IOCONTROL_TIMING" must be a logical
		__SHOWERROR
	#ENDIF

	*------------------------------------------------------------------
	* Debugoption für die Zeitmessung des DataBehavior
	*------------------------------------------------------------------
	#IFNDEF __DEBUG_DATABEHAVIOR_TIMING
		#IF __DEBUGLEVEL >= __DEBUG_ACTIVE
			#DEFINE __DEBUG_DATABEHAVIOR_TIMING .T.
		#ELSE
			#DEFINE __DEBUG_DATABEHAVIOR_TIMING .F.
		#ENDIF
	#ENDIF
	#IF Type( [__DEBUG_DATABEHAVIOR_TIMING] ) # "L"
		#UNDEF __DEBUG_DATABEHAVIOR_TIMING
		#DEFINE __DEBUG_DATABEHAVIOR_TIMING .F.
		__ERRMSG "__DEBUG_DATABEHAVIOR_TIMING" must be a logical
		__SHOWERROR
	#ENDIF

	*------------------------------------------------------------------
	* Einige Operationen gerade bei den Basisklassen sind zwar an sich
	* schnell, aber werden so häufig ausgeführt, daß sie in der Gesamt-
	* heit spürbar werden. Mit den __ACODEY_FEATURE_ Konstanten können
	* Sie diese Optionen gezielt abschalten. Damit wird der Code für 
	* ein bestimmtes Feature gar nicht mehr in die Klassen hineinkompi-
	* liert. Dies erfolgt unabhängig von Einstellungen zu Klassen, die
	* Sie im Integrationsassistenten vornehmen können. Wenn Sie im
	* Integrationsassisten ein Feature entfernen, dann steht es auch
	* nicht im Quellcode zur Verfügung. Wenn Sie hingegen ein Feature 
	* in einigen Komponenten entfernt, in anderen aber dringelassen 
	* haben, dann müssen Sie hier das Feature ebenfalls aktiviert
	* lassen.
	*
	* Benötigt eine Komponente ein bestimmtes Feature, so prüft sie 
	* dies beim Kompilieren und gibt gegebenenfalls eine Fehlermeldung
	* aus.
	*------------------------------------------------------------------
	
	*------------------------------------------------------------------
	* lUsed
	* 
	* CompLabel und CompContainer bieten die Möglichkeit, über die Ei-
	* genschaft lUsed während der Initialisierung .F. zurückzugeben. 
	* Damit wird ein Objekt auf einfache Weise deaktiviert, ohne daß
	* Sie Code schreiben müssen. Da lUsed aber umlenkbar ist und für
	* jedes Objekt geprüft werden muß, ist das recht Performance inten-
	* siv. Hiermit können Sie den entsprechenden Code komplett deakti-
	* vieren.
	*------------------------------------------------------------------
	#IFNDEF __ACODEY_FEATURE_LUSED
		#DEFINE __ACODEY_FEATURE_LUSED .T.
	#ENDIF
	#IF Type( [__ACODEY_FEATURE_LUSED] ) # "L"
		#UNDEF __ACODEY_FEATURE_LUSED
		#DEFINE __ACODEY_FEATURE_LUSED .T.
		__ERRMSG "__ACODEY_FEATURE_LUSED" must be a logical
		__SHOWERROR
	#ENDIF

	*--------------------------------------------------------------------------------------
	* Exceptionhandling. Dieses kann optional genutzt werden. 
	*--------------------------------------------------------------------------------------
	#DEFINE _BEGIN Private __EXCEPTION
	#DEFINE _TRY __EXCEPTION = Iif(Empty(JustExt(Program(Program(-1)))),;
	        JustStem(Program(Program(-1))),JustExt(Program(Program(-1))))
	#DEFINE _THROW Do __Throw with 
	#DEFINE _CATCH IF Vartype(__EXCEPTION) == "O"
	#DEFINE _END Endif

	*--------------------------------------------------------------------------------------
	* In vielen Fällen melden Acodey-Komponenten einen Fehler, indem sie .f. zurückgeben.
	* bei einem einfachen Methodenaufruf kann dies leicht geprüft und entsprechend reagiert
	* werden. Sobald eine Anwendung aber eine gewisse Komplexität erreicht hat, stehen 
	* zwischen Ursache und Reaktion aber bereits mehrere Aufrufebenen, so dass nicht mehr
	* genau festgestellt werden kann, warum ein Fehler aufgetreten ist, ohne dies im ein-
	* zelnen zu debuggen.
	*
	* Ein konkretes Beispiel aus den Komponenten in Acodey ist hierfür etwa die Update-
	* Methode des DataBehavior's. Wenn diese .F. zurückgibt, konnten die Daten nicht ge-
	* schrieben werden. Die Ursache läßt sich bei der Übergabe einen UpdateConflictHandlers
	* zwar über diesen ermitteln, nicht aber wenn kein solcher Handler verwendet wird. 
	*
	* Das Logging Feature in Acodey bietet eine Alternative. Wenn die Option __ACODEY_LOGGING
	* aktiviert, also .T. ist, schreiben Komponenten beim Auftreten eines Fehlers einen
	* englischen Protokolleintrag, der über __ACODEY_LOGGING_WRITE ausgegeben wird. In der
	* Grundeinstellung handelt es sich dabei um einen Aufruf des Logging Dienstes, wobei
	* die Meldung als Kurztext übergeben wird.
	*
	* Der Logging Service schreibt in der Grundkonfiguration alle Meldungen nur in das
	* DEBUGOUT Fenster und an einen Windows Debugger. Ersteres können Sie für die Entwick-
	* lung nutzen, letzteres über das Programm DBGVIEW von http://www.sysinternals.com auch
	* für die Laufzeitumgebung. Zusätzlich können Sie eigene Handler schreiben und beim
	* Logging-Dienst per BINDEVENT() registrieren, um weitere Protokolle zu unterstützen,
	* wie etwa das Windows Ereignisprotokoll.
	*
	* Das Logging-Feature steht erst ab VFP 6 zur Verfügung. Bis einschließlich VFP 7 muss
	* die Logging Komponente ausgetauscht werden, da die Acodey Logging-Komponente nur ab
	* VFP 8 eingesetzt werden kann.
	*--------------------------------------------------------------------------------------
	#IFNDEF __ACODEY_LOGGING
		#IF __VFP6
			#DEFINE __ACODEY_LOGGING .T.
		#ELSE
			#DEFINE __ACODEY_LOGGING .F.
		#ENDIF
	#ENDIF
	#IF Type( [__ACODEY_LOGGING] ) # "L"
		#UNDEF __ACODEY_LOGGING
		#IF __VFP6
			#DEFINE __ACODEY_LOGGING .T.
		#ELSE
			#DEFINE __ACODEY_LOGGING .F.
		#ENDIF
		__ERRMSG "__ACODEY_LOGGING" must be either .T. or .F.
		__SHOWERROR
	#ENDIF

	*--------------------------------------------------------------------------------------
	* In __ACODEY_LOGGING_WRITE kann der Aufruf hinterlegt werden, mit dem die Komponente
	* das Protokoll erstellt. Komponenten, die diese Funktion nutzen, haben Abhängigkeiten
	* zu GlobalService und Logging. Sie können diese Befehlszeile durch einen anderen 
	* Befehl ersetzen. Bitte beachten Sie, dass Sie hier keinen Funktionsaufruf hinterlegen
	* können, da die abschließende Klammer zu nicht angegeben wird.
	*--------------------------------------------------------------------------------------
	#IFNDEF __ACODEY_LOGGING_WRITE
		#IF __ACODEY_LOGGING
			#DEFINE __ACODEY_LOGGING_WRITE ;
				DO GPF_Service with "Logging", "Do", ;
					Iif( Type("m.This")=="O", "object ", "program " ) + ;
					Lower(Program(Program(-1))) + ;
					" (" + Alltrim(Str(LineNo(1))) + "): " +
		#ELSE
			#DEFINE __ACODEY_LOGGING_WRITE * 
		#ENDIF
	#ENDIF

	*--------------------------------------------------------------------------------------
	* Oftmals deutet ein Rückgabewert von .F. bei Komponenten einen Entwicklerfehler an, 
	* ohne dass dies zwangsläufig der Fall sein muss. Beispielsweise ist es ein Fehler,
	* wenn eine XML Definition nicht geladen werden kann, die in das Programm eingebunden
	* wurde. Wird aber eine XML Definition von extern geladen, kann .F. einen gültigen
	* Rückgabewert darstellen.
	*
	* Wenn Sie __DEBUG_SHOW_WARNINGS auf .T. setzen, wird in solchen Fällen ebenfalls eine
	* ASSERT Meldung ausgegeben. Unter Umständen werden dann aber Meldungen angezeigt, die
	* nicht zwangsweise auf Fehler hindeuten. Alle derartige ASSERT Meldungen fangen mit 
	* dem Text "WARNING: " an. Bei Active Debugging ist diese Option standardmäßig akti-
	* viert.
	*--------------------------------------------------------------------------------------
	#IFNDEF __DEBUG_SHOW_WARNINGS
		#IF __DEBUGLEVEL >= __DEBUG_ACTIVE
			#DEFINE __DEBUG_SHOW_WARNINGS .T.
		#ELSE
			#DEFINE __DEBUG_SHOW_WARNINGS .F.
		#ENDIF
	#ENDIF
	#IF Type( [__DEBUG_SHOW_WARNINGS] ) # "L"
		#UNDEF __DEBUG_SHOW_WARNINGS
		#IF __DEBUGLEVEL >= __DEBUG_ACTIVE
			#DEFINE __DEBUG_SHOW_WARNINGS .T.
		#ELSE
			#DEFINE __DEBUG_SHOW_WARNINGS .F.
		#ENDIF
		__ERRMSG "__DEBUG_SHOW_WARNINGS" must be a logical value
		__SHOWERROR
	#ENDIF

	*--------------------------------------------------------------------------------------
	* Über die CLA Notation können Klassen in einer einzigen Eigenschaft angegeben werden.
	* Der Integrator erlaubt die Anpassung an die tatsächlichen Namen. Was mit diesen bei-
	* den Funktionen jedoch nicht möglich ist, ist die Anpassung der Klassennamen zur Lauf-
	* zeit. Das kann aus mehreren Gründen notwendig sein:
	*
	* - Klassen sollen dynamisch zur Laufzeit ausgetauscht werden können, etwa um Fehler
	*   zu fixen.
	*
	* - Die CLA Notation soll unabhägig vom Speicherort der Klasse gestaltet werden.
	*
	* - Um die Abhängigkeit von Pfaden zu reudzieren, soll Klassenbibliothek oder Anwendung
	*   um einen Pfad erweitert werden.
	*
	* Um eine eigene Funktion für die Konvertierung der Klassennamen zu verwenden, defi-
	* nieren Sie die Konstante __DECODEALC_HOOK auf den Funktionsausdruck:
	*
	*  #DEFINE __DECODEALC_HOOK  MyDecodeHook
	*--------------------------------------------------------------------------------------
	#IFNDEF __DECODEALC_HOOK
		#DEFINE __DECODEALC_HOOK
	#ENDIF
	
	*--------------------------------------------------------------------------------------
	* Anwendungspfad für PE Anwendungen
	*--------------------------------------------------------------------------------------
	#IFNDEF APP_PATH
		#DEFINE APP_PATH
	#ENDIF

	*--------------------------------------------------------------------------------------
	* Gibt an, unter welchen Bedingungen alle SQL Befehle protokolliert werden sollen.
	* Die Protokollierung erfolgt über __ACODEY_LOGGING_WRITE
	*--------------------------------------------------------------------------------------
	#IFNDEF __DEBUG_ODBC_STATEMENT_LOGGING
		#DEFINE __DEBUG_ODBC_STATEMENT_LOGGING .F.
	#ENDIF
