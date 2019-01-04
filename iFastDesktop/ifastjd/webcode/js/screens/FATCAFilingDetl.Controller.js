/*********************************************************************************************
 * @file	FATCAFilingDetl.Controller.js
 * @author	Pannarasi Wongpakdee
 * @desc	Resources JS file for FATCA Filing Detail screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > FATCA Filing Detail
 *				
 *  History : 
 *
 *  24 Dec 2014 P. Wongpakdee P0205605 T80214
 *					- Created.
 *
 *	05 Feb 2015 P. Wongpakdee P0205605 T80264
 *					- Adjustment section
 *
 *	16 Feb 2015 P. Wongpakdee P0205605 T80349
 *					- Additional requirement (Create dummy record(s)
 *					  at Reporting Unit level for Adjustment)
 *
 *	19 Mar 2015 P. Wongpakdee P0205605 T80523 DFT0049199, DFT0049254, DFT0049255
 *					- To display a fully error message that contain 
 *					  any special characters (quot, double quot, etc).
 *
 *	26 Mar 2015 P. Wongpakdee P0205605 T80536
 *					- Clone a new data group before creating each dummy RFFI(s)
 *					- Send correct AssocDocRefID when creating multiple RFFI(s) in
 *					  function createReportingUnitforAdjustment
 *
 *	31 Mar 2015 P. Wongpakdee P0205605 DFT0049639 T80574
 *					- Clone a new inquiry XML to be use when display an error
 *					  (handle more records as well) at Slip Full View pop up
 *
 *	08 Jan 2016 A. Mongkonrat P0241558 T81995 DFT0058373
 *					- Add Country Of Domicile and remove As of Date.
 *
 *  04 Feb 2016 Aurkarn M. P0241558 T82184 DFT0059297 FATCA Reporting Enhancement
 *                  - Fix issue where user is unable to add filing request if there is a record of previous tax year.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached. 
 *
 *	10 Jan 2017 Matira T. P0259672 T84599 CRS Enhancement Phase2
 *					- Add new field RFI Domicile
 *
 *	01 Feb 2017 Matira T. P0259672 T84754 DFT0071968 CRS Enhancement Phase2
 *					- Fixed to indicate error correctly
 *					- Added genOpt validation for All submission
 *
 *  10 Feb 2017 Matira T. P0259672 T84840 DFT0071968 CRS Enhancement Phase2
 *					- Added condition to indicate error correctly
 *
 *	16 Feb 2017 Matira T. P0259672 T84920 DFT0072303 DFT0072469 CRS Enhancement Phase2
 *					- Changed logic to set default tax year and TPSDate field.
 *					- Added condition to indicate error correctly.
 *
 *	22 Nov 2017 Kornnika T. P0181067 CHG0051876
 *					- Changed _requestRecNumRptUnit from 25 to 0.
 *					
 *
 */
 
 DesktopWeb.ScreenController = function(){	
 
 	// PRIVATE VARIABLES *************************************
	var _self 			= null;
	var _resources 		= null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD 	 = 'add';
	var _MOD 	 = 'mod';
	var _DEL 	 = 'del';
	var _INQ 	 = 'inq';
	var _ADJ 	 = 'adj';
	var _UNCG 	 = 'uncg';
	var _BLNK 	 = '';
	var _USFATCA = 'USFATCA';
	var _CRS     = 'CRS';
	var _ORG 	 = 'ORG';
	var _AMD 	 = 'AMD';
	var _COR 	 = 'COR';
	var _CAN	 = 'CAN';
	var _HMRC	 = 'HMRC';
	var _CRA	 = 'CRA';
	var _IRS	 = 'IRS';
	
	var _REPORTINGFFI	= 'reportingFFI';
	var _REPORTINGUNIT	= 'reportingUnit';
	var _ALLREPORTING	= 'allReporting';

	var _RUNMODE_INIT 			= 'init';
	var _RUNMODE_RELOAD 		= 'reload';
	var _RUNMODE_RELOADRptUnit 	= 'reloadRptUnit';
	var _RUNMODE_RELOADRptSlip 	= 'reloadRptSlip';
	var _RUNMODE_RELOADEnt 		= 'reloadEntity';
	var _RUNMODE_RELOADRFFI		= 'reloadRFFI';

	var _currentSearch	= new Array();
	var _permissions	= new Array();
	var _defaultValues	= new Array();
		
	var _FATCARptInitXML = null;
	var _FATCARptInitAsofDateXML = null;
	
	var _nextStartRecNum 	  = 1;
	var _requestRecNum 		  = 25; // Submission
	var _requestRecNumRptUnit = 0; // Report Unit
	var _requestRecNumSlip 	  = 100; // Slip full View
	
	var _dtFATCARptInitService = "dtFATCARptMstrInit";
	var _dtFATCARptInqService  = "dtFATCARptMstrInq";
	var _dtFATCARptValService  = "dtFATCARptMstrVal";
	var _dtFATCARptProcService = "dtFATCARptMstrProc";	
	var _dtHistoryService 	   = 'dtHistoricalInfo';
	
	var _nextUUID 	  	 = 1;
	var _fullXML 	  	 = null;
	var _slipFullViewXML = null;
	
	var _isSlipFullView  = false;
	var _isAdjustment	 = false;
	var _assocSlipID  	 = null;	
	var _ignoreErrorCode = null;
	var _genOutput 		 = 'no';
	var _origDataRptUnit = {};
	
	var _MSGSTAT_Pending	= '01';	
	var _MSGSTAT_Processed	= '02';
	var _MSGSTAT_Processing	= '04';
	
	var _RUNMODE_Production	= '01';
	var _RUNMODE_Test		= '02';
	
	var _REPORTFILE_All			= '01';
	var _REPORTFILE_SingleRFFI	= '02';
	var _REPORTFILE_SingleUnit	= '03';
	var _REPORTFILE_CntyOfDomicile = '04';
	
	// PRIVATE METHODS ****************************************	
	function storePermissions(initViewXML)
	{
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function loadDefaultValues(responseXML)
	{
		var defaultValuesNode = IFDS.Xml.getNode(responseXML, "//DefaultValues");
		if (defaultValuesNode)
		{
			_defaultValues['regulationFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'regulation');
			_defaultValues['taxYearFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'taxYear');
			_defaultValues['asOfDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'asOfDate'));
			_defaultValues['TPSDeff'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'TPSDeff'));	
            _defaultValues['runDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'runDate'));
			_defaultValues['rfiDomicileFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'RFIDomicile');

			var reg = IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'regulations']");
			_defaultValues['CRSTaxYearFld'] = IFDS.Xml.getNodeValue(reg, "//Element[code='" + _CRS + "']/taxYear");
			_defaultValues['CRSTPSDeff'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(reg, "//Element[code='" + _CRS + "']/TPSDeff"));
			_defaultValues['USFATCATaxYearFld'] = IFDS.Xml.getNodeValue(reg, "//Element[code='" + _USFATCA + "']/taxYear");
			_defaultValues['USFATCATPSDeff'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(reg, "//Element[code='" + _USFATCA + "']/TPSDeff"));
			
			_resources.fields['regulationFld'].setValue(_defaultValues['regulationFld']);
			_resources.fields['taxYearFld'].setValue(_defaultValues[_defaultValues['regulationFld'] + "TaxYearFld"]);
			_resources.fields['rfiDomicileFld'].setValue(_defaultValues['rfiDomicileFld']);
		}
	}

	function populateDropdownList()
	{
		try{
			// Regulation
			_resources.fields['regulationFld'].loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'regulations']"));
			_resources.popups['filingReqPopup'].getField('filReqRegulation').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'regulations']"));			
			
			// Submission Type
			_resources.popups['filingReqPopup'].getField('filReqSubmission').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'submissionType']"));			
			_resources.popups['adjustPopup'].getField('adjReqSubmission').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'submissionType']"));
			_resources.popups['acctReqPopup'].getField('actReqSubmission').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'submissionType']"));
										
			// Remove ORG-Original from Submission List when adjustment
			var store = _resources.popups['adjustPopup'].getField('adjReqSubmission').getStore();
			store.removeAt(store.findExact('code', _ORG));
			
			// Run Mode
			_resources.popups['filingReqPopup'].getField('filReqRunMode').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'runMode']"));			
			_resources.popups['adjustPopup'].getField('adjReqRunMode').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'runMode']"));
			
			// Report File
			_resources.popups['filingReqPopup'].getField('filReqReportFile').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'reportFile']"));			
            
            // Country of Domicile
            _resources.popups['filingReqPopup'].getField('filReqCountryOfDomicile').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'countryOfDomicile']"));			

            // RFIDomicile
			_resources.fields['rfiDomicileFld'].loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'RFIDomicile']"));
			_resources.popups['filingReqPopup'].getField('filReqRFIDomicile').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'RFIDomicile']"));			
		
        }catch(err){
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
		}
	}
	
	function populateDropdownListReporting(listName)
	{		
		try{
			// Reporting FFI / Reporting Unit
			_resources.popups['filingReqPopup'].getField('filReqReportFFI').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = '" + listName + "']"));
			
		}catch(err){
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
		}	

		_resources.popups['filingReqPopup'].getField('filReqReportFFI').enableField();		
	}

	function disableScreen()
	{
		// Search section
		_resources.fields['regulationFld'].disable();
		_resources.fields['taxYearFld'].disable();
		_resources.fields['msgIDFld'].disable();
		_resources.fields['docRefIDFld'].disable();
		_resources.fields['slipIDFld'].disable();
		_resources.buttons['searchBtn'].disable();
		_resources.fields['genOutput'].disable();
		
		// Submission Level
		_resources.grids['submissionGrid'].disableAllButtons();
		
		// Reporting Unit Level
		_resources.grids['reportingUnitGrid'].disableAllButtons();
		
		// Slip Level
		_resources.grids['slipGrid'].disableAllButtons();
	}
	
	function updateSubmissionButtons(record)
	{		
		var submissionGrid = _resources.grids['submissionGrid'];
		submissionGrid.disableButton('addBtn');
		submissionGrid.disableButton('modBtn');
		submissionGrid.disableButton('delBtn');	
		submissionGrid.disableButton('historyBtn');	
		submissionGrid.disableButton('adminBtn');
		
		// disable flag genOutput when no record
		_resources.fields['genOutput'].disableField();		

		// #1 ADD permission
		if (_permissions[_self.ADD]){
			submissionGrid.enableButton('addBtn');
		}
		
		if (record)
		{
			// #2 new record adding
			if (record.data['action'] == _ADD){
				submissionGrid.enableButton('modBtn');
				submissionGrid.enableButton('delBtn');	
			}
			else // MOD & DEL
			{
				// #3 check MOD DEL permission			
				if(_permissions[_self.MOD] && record.data['allowMod'] == 'yes'){
					submissionGrid.enableButton('modBtn');
				}
				
				if (_permissions[_self.DEL] && record.data['allowDel'] == 'yes'){
					submissionGrid.enableButton('delBtn');	
				}
			}			
			
			// enable only if record is selected
			submissionGrid.enableButton('historyBtn');	
			submissionGrid.enableButton('adminBtn');			
		}
	}
	
	function updateRptUnitButtons(record)
	{		
		var rptUnitGrid = _resources.grids['reportingUnitGrid'];
		rptUnitGrid.disableButton('adjustmentBtn');	
		rptUnitGrid.disableButton('historyBtn');	
		rptUnitGrid.disableButton('adminBtn');
		
		if (record)
		{	
			// #1 check MOD permission
			if (_permissions[_self.MOD] && record.data['allowMod'] == 'yes'){
				rptUnitGrid.enableButton('adjustmentBtn');
			}
			
			// #2 new record adjusting
			if (record.data['action'] == _ADJ){
				rptUnitGrid.disableButton('adjustmentBtn');	
			}
			
			if (_resources.grids['submissionGrid'].getSelectedRecord().data['FATCACode'] == _CRS){
				rptUnitGrid.disableButton('adjustmentBtn');
			}
			
			// More button
			var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();	
			
			if (selectedSubmission.data['hasMoreLinkedRptUnit'] == 'yes'){
				rptUnitGrid.enableButton('moreBtn');
			}else{
				rptUnitGrid.disableButton('moreBtn');
			}
			
			// enable only if record is selected
			rptUnitGrid.enableButton('historyBtn');	
			rptUnitGrid.enableButton('adminBtn');			
		}
	}	
	
	function updateSlipButtons(record)
	{
		var slipGrid = _resources.grids['slipGrid'];
		
		slipGrid.disableButton('addBtn');
		slipGrid.disableButton('modBtn');
		slipGrid.disableButton('delBtn');
		slipGrid.disableButton('historyBtn');	
		slipGrid.disableButton('adminBtn');
		slipGrid.disableButton('detailBtn');	
		
		if (record)
		{
			// #1 new record adding
			if (record.data['action'] == _ADD){
				slipGrid.enableButton('addBtn');
				slipGrid.enableButton('modBtn');
				slipGrid.enableButton('delBtn');	
			}
			else // MOD & DEL
			{			
				// #2 account is attached with Slip and not new record adding
				if (record.data['account'] != null && record.data['action'] != _ADD){
					slipGrid.enableButton('detailBtn');
				}
				
				// if CRS detailBtn will be disabled
				if (_resources.grids['submissionGrid'].getSelectedRecord().data['FATCACode'] == _CRS){
					slipGrid.disableButton('detailBtn');
				}

				// #3 check ADD MOD DEL permission
				if (_permissions[_self.ADD] && record.data['allowAdd'] == 'yes'){
					slipGrid.enableButton('addBtn');
				}
				
				if(_permissions[_self.MOD] && record.data['allowMod'] == 'yes'){
					slipGrid.enableButton('modBtn');
				}
				
				if (_permissions[_self.DEL] && record.data['allowDel'] == 'yes'){
					slipGrid.enableButton('delBtn');	
				}
			}
			
			// enable only if record is selected
			slipGrid.enableButton('historyBtn');	
			slipGrid.enableButton('adminBtn');
		}
		
		// #4 disable all buttons at slip level if submission is original
		var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
		if (selectedSubmission && selectedSubmission.data['submissionType'] == _ORG)
		{
			slipGrid.disableButton('addBtn');
			slipGrid.disableButton('modBtn');
			slipGrid.disableButton('delBtn');
		}		
	}

	function updateSlipFullButtons()
	{
		var slipFullGrid = _resources.grids['accountGrid'];
		
		// always enable because Slip Full View screen can be opened only when it has slip record
		slipFullGrid.enableButton('adminBtn');
		slipFullGrid.enableButton('closeBtn');
	}
	
	function validateSearchCriteria()
	{
		_resources.fields['regulationFld'].clearInvalid();
		_resources.fields['taxYearFld'].clearInvalid();
		_resources.fields['msgIDFld'].clearInvalid();
		_resources.fields['docRefIDFld'].clearInvalid();
		_resources.fields['slipIDFld'].clearInvalid();

		var valid = _resources.fields['regulationFld'].isValid();
		valid = _resources.fields['taxYearFld'].isValid() && valid;
		valid = _resources.fields['msgIDFld'].isValid() && valid;
		valid = _resources.fields['docRefIDFld'].isValid() && valid;
		valid = _resources.fields['slipIDFld'].isValid() && valid;
		
		return valid;
	}

	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function searchMainAssignVal()
	{
		_currentSearch['regulationFld'] = _resources.fields['regulationFld'].getValue();
		_currentSearch['taxYearFld'] = _resources.fields['taxYearFld'].getValue();
		_currentSearch['msgIDFld'] = _resources.fields['msgIDFld'].getValue();
		_currentSearch['docRefIDFld'] = _resources.fields['docRefIDFld'].getValue();
		_currentSearch['slipIDFld'] = _resources.fields['slipIDFld'].getValue();	
		_currentSearch['rfiDomicile'] = _resources.fields['rfiDomicileFld'].getValue();	
		
	}
	
	function searchAssignVal()
	{					
		_currentSearch['FATCARptMstrUUID'] = null;
		_currentSearch['FATCARptFileUUID'] = null;
		_currentSearch['FATCARptFileDetlUUID'] = null;
		_currentSearch['FATCARptSlipUUID'] = null;
		
		// Only check ErrorOnly when SlipFullView popup has been opened
		if (_resources.popups['slipFullPopup'].hidden){
			_currentSearch['errorOnly'] = 'no';
		}
		else
		{
			if (_resources.popups['slipFullPopup'].getField('detlErrorOnly').getValue()){
				_currentSearch['errorOnly'] = 'yes';
			}else{
				_currentSearch['errorOnly'] = 'no';
			}
		}
		
		_currentSearch['acct'] = 0;
	}	
	
	function doSearch(runMode, append)
	{
		var requestRecNum = _requestRecNum; // Submission - 25
		var startRecNum = _nextStartRecNum; // Start as 1

		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(dataXML, 'fatcaCode', _currentSearch['regulationFld']);
		IFDS.Xml.addSingleNode(dataXML, 'taxYear', _currentSearch['taxYearFld']);
		IFDS.Xml.addSingleNode(dataXML, 'DocRefID', _currentSearch['docRefIDFld']);		
		IFDS.Xml.addSingleNode(dataXML, 'messageID', _currentSearch['msgIDFld']);
		IFDS.Xml.addSingleNode(dataXML, 'slipID', _currentSearch['slipIDFld']);
		
		/**
		   Submission Level 	: Blank (Only Search section)
		   Reporting Unit Level : MstrUUID
		   Slip Level 			: MstrUUID, FileUUID, FileDetlUUID
		 **/
		 
		var selectedRecordSub = _resources.grids['submissionGrid'].getSelectedRecord();
		var selectedRecordRptUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();	
		var selectedRecordSlip = _resources.grids['slipGrid'].getSelectedRecord();	
			
		if (runMode == _RUNMODE_RELOADRptUnit || runMode == _RUNMODE_RELOADRptSlip)
		{
			if (runMode == _RUNMODE_RELOADRptUnit)
			{
				requestRecNum = _requestRecNumRptUnit; // Report Unit - 25
				startRecNum = selectedRecordSub.data['nextStartRecordNumLinkedRptUnit'];
	
				// Re-use run mode 'reloadRptUnit' by sending FATCARptFileUUID (Reporting RFFI) for adjustment case
				if (_isAdjustment)
				{
					/** #1 FATCARptMstrUUID & #2 FATCARptFileUUID **/
					
					// Need to send original UUIDs in case More function of new adjusting (UUID is a temp one)
					if (append){
						IFDS.Xml.addSingleNode(dataXML, 'FATCARptMstrUUID', selectedRecordSub.data['origFATCARptMstrUUID']);
						IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileUUID', selectedRecordRptUnit.data['origFATCARptFileUUID']);
					}else{
						IFDS.Xml.addSingleNode(dataXML, 'FATCARptMstrUUID', selectedRecordSub.data['FATCARptMstrUUID']);
						IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileUUID', selectedRecordRptUnit.data['FATCARptFileUUID']);
					}
					
					/** #3 FATCARptFileDetlUUID **/
					
					// Check if the adjustment is for Reporting RFFI or Reporting Unit
					var isSingleRFFI = _BLNK;
					if (selectedRecordSub.data['action'] == _ADJ)
					{
						// Case1: More function; identify flag from selected rptFile of Submission level
						var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
						if (selectedSubmission.data['rptFile'] == _REPORTFILE_SingleRFFI)
						{
							isSingleRFFI == 'yes'
						}
						else
						{
							isSingleRFFI == 'no'
						}
					}else{ // action = blank
					
						// Case2: new Adjustment; identify flag from which selected RFFI or Unit on popup
						isSingleRFFI = _resources.popups['adjustPopup'].getField('adjReqRptUnitName').getAllValues('SingleRFFI');
					}
					
					// Re-use run mode 'reloadRptUnit' by sending FATCARptFileDetlUUID (Reporting Unit) for adjustment case
					if (isSingleRFFI == 'yes'){
						IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileDetlUUID', selectedRecordRptUnit.data['FATCARptFileDetlUUID']);
					}else{
						IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileDetlUUID', _currentSearch['FATCARptFileDetlUUID']);
					}					
				}else{
					/** #1 FATCARptMstrUUID & #2 FATCARptFileUUID & #3 FATCARptFileDetlUUID **/					
					IFDS.Xml.addSingleNode(dataXML, 'FATCARptMstrUUID', selectedRecordSub.data['FATCARptMstrUUID']);
					IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileUUID', _currentSearch['FATCARptFileUUID']);
					IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileDetlUUID', _currentSearch['FATCARptFileDetlUUID']);					
				}
				
				/** #4 FATCARptSlipUUID **/
				IFDS.Xml.addSingleNode(dataXML, 'FATCARptSlipUUID', _currentSearch['FATCARptSlipUUID']);
				
			}else{ // runMode is reloadRptSlip
				requestRecNum = _requestRecNumSlip; // Slip Full View - 100
				startRecNum = selectedRecordRptUnit.data['nextStartRecordNumLinkedSlip'];

				IFDS.Xml.addSingleNode(dataXML, 'FATCARptMstrUUID', selectedRecordSub.data['FATCARptMstrUUID']);
				IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileUUID', selectedRecordRptUnit.data['FATCARptFileUUID']);			
				IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileDetlUUID', selectedRecordRptUnit.data['FATCARptFileDetlUUID']);				
				IFDS.Xml.addSingleNode(dataXML, 'FATCARptSlipUUID', _currentSearch['FATCARptSlipUUID']);
			}	
			IFDS.Xml.addSingleNode(dataXML, 'countryOfDomicile', selectedRecordSub.data['countryOfDomicile']);			
		}
		else if (runMode == _RUNMODE_RELOADRFFI)
		{
			// ReloadRFFI need to send FATCARptFileUUID & FATCARptFileDetlUUID
			IFDS.Xml.addSingleNode(dataXML, 'FATCARptMstrUUID', _currentSearch['FATCARptMstrUUID']);
			IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileUUID', selectedRecordRptUnit.data['FATCARptFileUUID']);
			IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileDetlUUID', selectedRecordRptUnit.data['FATCARptFileDetlUUID']);	
			IFDS.Xml.addSingleNode(dataXML, 'FATCARptSlipUUID', _currentSearch['FATCARptSlipUUID']);
		}
		else{ // runMode is reload

			IFDS.Xml.addSingleNode(dataXML, 'FATCARptMstrUUID', _currentSearch['FATCARptMstrUUID']);
			IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileUUID', _currentSearch['FATCARptFileUUID']);	
			IFDS.Xml.addSingleNode(dataXML, 'FATCARptFileDetlUUID', _currentSearch['FATCARptFileDetlUUID']);
			IFDS.Xml.addSingleNode(dataXML, 'FATCARptSlipUUID', _currentSearch['FATCARptSlipUUID']);	
			IFDS.Xml.addSingleNode(dataXML, 'countryOfDomicile', _currentSearch['rfiDomicile']);			
		}

		IFDS.Xml.addSingleNode(dataXML, 'errorOnly', _currentSearch['errorOnly']);
		
		// Call Inq service with runmode reloadEntity to get Entity List
		IFDS.Xml.addSingleNode(dataXML, 'acct', _currentSearch['acct']);		

		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?startRecNum:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', requestRecNum);
		
		
		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_dtFATCARptInqService, _ignoreErrorCode, dataXML, responseHandler, _translationMap['ProcMsg_Searching']);

		function responseHandler(success, responseXML)
		{
			// hanldle response
			if (success){

				var FATCARptInqXML = IFDS.Xml.cloneDocument(responseXML);

				if (runMode == _RUNMODE_RELOAD)
				{
					// disable flag genOutput (initial reload screen ignores error no data found)
					var isInitialReloadReturned = IFDS.Xml.getNode(FATCARptInqXML, "//Submissions/Submission");
					if (!isInitialReloadReturned){
						_resources.fields['genOutput'].disableField();
					}
					
					// reset Main XML for new search; not more function (append = true)					
					if (!append){
						// assign (initial load) to full XML
						_fullXML = IFDS.Xml.cloneDocument(responseXML);
						
						// load to Submission grid
						loadSubmission(_fullXML, append);						
					}
					else{
						// load to full XML (more function)
						appendSubmissionXML(IFDS.Xml.cloneDocument(FATCARptInqXML));
						
						// load to Submission grid
						loadSubmission(FATCARptInqXML, append);
					}
					
					// Control More button
					moreButtonSubmission(FATCARptInqXML, append);
				}
				else if (runMode == _RUNMODE_RELOADRptUnit)
				{
					// Continue to load Slip level to grid if it is not adjustment
					if (!_isAdjustment)
					{

						// load to full XML
						appendRptUnitXML(IFDS.Xml.cloneDocument(FATCARptInqXML));
			
						// load to reting unit grid
						loadReportUnit(FATCARptInqXML, append);
						
						// Control More button
						moreButtonRptUnit(FATCARptInqXML, append);
					}else{	
						// Set flag to identify Adjustment action back to false
						_isAdjustment = false;
						
						// Use responseXML to create dummy record(s) either a Reporting RFFI itself OR Reporting RFFIs under Reporting Unit 
						var FATCARptInqAdjustmentXML = IFDS.Xml.cloneDocument(responseXML);
						createReportingUnitforAdjustment(FATCARptInqAdjustmentXML, _origDataRptUnit);
						
						// Control More button
						moreButtonRptUnit(FATCARptInqAdjustmentXML, append);						
					}
				}
				else if (runMode == _RUNMODE_RELOADRptSlip)
				{
					if (!_isSlipFullView)
					{
						// load to full XML
						appendSlipXML(IFDS.Xml.cloneDocument(FATCARptInqXML));
						
						// load to Slip grid
						loadReportSlip(FATCARptInqXML);
					}
					else{
						// Clone XML for displaying error at Slip Full View pop up
						_slipFullViewXML = IFDS.Xml.cloneDocument(FATCARptInqXML);
						
						// load to Slip Full View grid
						loadReportSlipFullView(FATCARptInqXML, append);

						// Control More button
						moreButtonSlipFullView(FATCARptInqXML, append);
						
					}		
				}
				else if (runMode == _RUNMODE_RELOADEnt)
				{
					try{
						_resources.popups['acctReqPopup'].getField('actReqEntName').loadData(IFDS.Xml.getNode(FATCARptInqXML, "//List[@listName = 'EntityNameList']"));			
					}catch(err){
						DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
					}				
				}
				else if (runMode == _RUNMODE_RELOADRFFI)
				{
					// Set drop down of Reporting Unit/RFFI Name list
					try{
						_resources.popups['adjustPopup'].getField('adjReqRptUnitName').loadData(IFDS.Xml.getNode(FATCARptInqXML, "//List[@listName = 'reportingRFFIAdj']"));			
					}catch(err){
						DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
					}					
				}
			}else{ // no data found
				updateSubmissionButtons(null);
				updateRptUnitButtons(null);
				
				// Prevent case 'no data found' from Slip Full View screen
				if (!_isSlipFullView){
					// Only reset Full XML and buttons from main searching; not Slip Full View screen
					_fullXML = IFDS.Xml.cloneDocument(responseXML);
					updateSlipButtons(null);					
				}
				
				// disable flag genOutput
				_resources.fields['genOutput'].disableField();
			}
		}
	}
	
	function setNodeValue(nodeName, nodeValue, context)
	{
		var node = IFDS.Xml.getNode(context, nodeName);
		
		if (node){
			IFDS.Xml.setNodeValue(node, nodeValue);
		}
		else{
			IFDS.Xml.addSingleNode(context, nodeName, nodeValue);
		}
	}	
	
	function appendSubmissionXML(appendSubXML)
	{		
		// #1 Append XML at Submission Level
		var currSubmissionsNode = IFDS.Xml.getNode(_fullXML, "//Submissions");
		
		// only append XML when node is found
		if (currSubmissionsNode)
		{
			var submissionNodes = IFDS.Xml.getNodes(appendSubXML, "//Submissions/Submission");		
			
			Ext.each(submissionNodes, function(submissionNode){
				IFDS.Xml.appendNode(currSubmissionsNode, submissionNode);
			});
		}
	}
	
	function appendRptUnitXML(appendRptXML)
	{		
		var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
		var selectedSubmissionUUID = selectedSubmission.data['FATCARptMstrUUID'];	
		
		// #1 Append XML at Reporting Unit Level
		var currRptUnitNode = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']/RptUnits");	

		// only append XML when node is found
		if (currRptUnitNode)
		{
			var rptUnitNodes = IFDS.Xml.getNodes(appendRptXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']/RptUnits/RptUnit");
			
			Ext.each(rptUnitNodes, function(rptUnitNode){
				IFDS.Xml.appendNode(currRptUnitNode, rptUnitNode);
			});	
		}
	}
	
	function appendSlipXML(appendSlpXML)
	{	
		var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		var selectedReportUnitUUID = selectedReportUnit.data['FATCARptFileDetlUUID'];	
		
		// #1 Append XML at Slip Level
		var currSlipNode = IFDS.Xml.getNode(_fullXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']/Slips");
		
		// only append XML when node is found
		if (currSlipNode)
		{
			var slipNodes = IFDS.Xml.getNodes(appendSlpXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']/Slips/Slip");
			
			Ext.each(slipNodes, function(slipNode){
				IFDS.Xml.appendNode(currSlipNode, slipNode);
			});				
		}
	}

	function loadSubmission(loadSubXML, append)
	{		
		var chkNodeSubmission = IFDS.Xml.getNode(loadSubXML, '//Submissions/Submission');
		
		if (chkNodeSubmission)
		{
			if (append)
			{
				var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
				var selectedSubmissionIndex  = _resources.grids['submissionGrid'].store.indexOf(selectedSubmission);
		
				// Append data to grid
				_resources.grids['submissionGrid'].getStore().loadData(loadSubXML, true);		
				setSelectedRow('submissionGrid', selectedSubmissionIndex);	
			
			}else{
				// Load data to grid
				_resources.grids['submissionGrid'].loadData(loadSubXML);
			}
			
			
		}else{
			// Handle if there is no linked-Reporting Unit in selected Submission
			updateSubmissionButtons(null);
		}
	}	

	function loadReportUnit(loadRptXML, append)
	{
		var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
		var selectedSubmissionUUID = selectedSubmission.data['FATCARptMstrUUID'];

		// #1 Cut XML for Reporting Unit Level
		var currSubmissionUUID = IFDS.Xml.getNode(loadRptXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']");	

		// only cut XML & load to grid when UUID is not blank
		if(currSubmissionUUID) // Individual
		{
			var cutXML = IFDS.Xml.getNode(loadRptXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']/RptUnits");

			if (append)
			{
				var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
				var selectedReportUnitIndex  = _resources.grids['reportingUnitGrid'].store.indexOf(selectedReportUnit);
		
				// Append data to grid
				_resources.grids['reportingUnitGrid'].getStore().loadData(cutXML, true);		
				setSelectedRow('reportingUnitGrid', selectedReportUnitIndex);				
				
			}else{
				// Load data to grid
				_resources.grids['reportingUnitGrid'].loadData(cutXML);
			}
		}else{ // ALL
			if(selectedSubmission.data['FATCACode'] == _CRS && selectedSubmission.data['countryOfDomicile'] == "*" && selectedSubmission.data['rptFile'] == "01"){
				var cutXML = IFDS.Xml.getNode(loadRptXML, "//Submissions/Submission/RptUnits");
				if(cutXML){
					if (append)
					{
						var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
						var selectedReportUnitIndex  = _resources.grids['reportingUnitGrid'].store.indexOf(selectedReportUnit);
				
						// Append data to grid
						_resources.grids['reportingUnitGrid'].getStore().loadData(cutXML, true);		
						setSelectedRow('reportingUnitGrid', selectedReportUnitIndex);				
						
					}else{
						// Load data to grid
						_resources.grids['reportingUnitGrid'].loadData(cutXML);
					}
				}
				
			}
		}
	}	
	
	function loadReportSlip(loadSlpXML)
	{
		var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		var selectedReportUnitUUID = selectedReportUnit.data['FATCARptFileDetlUUID'];	
		
		// #1 Cut XML for Slip Level
		var currRptUnitUUID = IFDS.Xml.getNode(loadSlpXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']");	
		
		// only cut XML & load to grid when UUID is not blank
		if(currRptUnitUUID)
		{
			var cutXML = IFDS.Xml.getNode(loadSlpXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']/Slips");
		
			// Load data to grid (no more function)
			_resources.grids['slipGrid'].loadData(cutXML);
		}
	}
	
	function loadReportSlipFullView(loadSlpFullXML, append)
	{
		var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		var selectedReportUnitUUID = selectedReportUnit.data['FATCARptFileDetlUUID'];		
	
		// #1 Cut XML for Slip Level
		var currRptUnitUUID = IFDS.Xml.getNode(loadSlpFullXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']");	
		
		// only cut XML & load to grid when UUID is not blank
		if(currRptUnitUUID)
		{
			var cutXML = IFDS.Xml.getNode(loadSlpFullXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']/Slips");
			
			if (append)
			{
				var selectedSlipFullView = _resources.grids['accountGrid'].getSelectedRecord();
				var selectedSlipFullViewIndex  = _resources.grids['accountGrid'].store.indexOf(selectedSlipFullView);
		
				// Append data to grid
				_resources.grids['accountGrid'].getStore().loadData(cutXML, true);		
				setSelectedRow('accountGrid', selectedSlipFullViewIndex);			
				
			}else{
				// Load data to grid
				_resources.grids['accountGrid'].loadData(cutXML);
			}
		}
	}
	
	function moreButtonSubmission(moreSubXML, append)
	{
		// More at Submission level: #1 control more button
		_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(moreSubXML);

		if (_nextStartRecNum){
			_resources.grids['submissionGrid'].enableButton('moreBtn');
		}else{
			_resources.grids['submissionGrid'].disableButton('moreBtn');
		}
	}
	
	function moreButtonRptUnit(moreRptXML, append)
	{
		var selectedRecordSub = _resources.grids['submissionGrid'].getSelectedRecord();	
		var submissionNode = getSelectedSubmissionNode();
		
		// More at Reporting Unit level: #1 update flags to submission grid, #2 update flags to XML, #3 control more button
		var nextStartRecNumRptUnit = DesktopWeb.Ajax.getSmartviewNextStartRecNum(moreRptXML);

		if (nextStartRecNumRptUnit)
		{
			// #1 update flags to submission grid
			selectedRecordSub.data['hasMoreLinkedRptUnit'] = 'yes';
			selectedRecordSub.data['nextStartRecordNumLinkedRptUnit'] = nextStartRecNumRptUnit;
			
			// #2 update flags to XML
			setNodeValue('hasMoreLinkedRptUnit', 'yes', submissionNode);
			setNodeValue('nextStartRecordNumLinkedRptUnit', nextStartRecNumRptUnit, submissionNode);		

			// #3 control more button
			_resources.grids['reportingUnitGrid'].enableButton('moreBtn');
		}
		else{
			// #1 update flags to submission grid
			selectedRecordSub.data['hasMoreLinkedRptUnit'] = 'no';
			selectedRecordSub.data['nextStartRecordNumLinkedRptUnit'] = _BLNK;
			
			// #2 update flags to XML
			setNodeValue('hasMoreLinkedRptUnit', 'no', submissionNode);
			setNodeValue('nextStartRecordNumLinkedRptUnit', _BLNK, submissionNode);				
			
			// #3 control more button			
			_resources.grids['reportingUnitGrid'].disableButton('moreBtn');
		}
	}
	
	function moreButtonSlipFullView(moreSlpFullXML, append)
	{
		var selectedRecordRptUnitFull = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		var rptUnitNode = getSelectedRptUnitNode();
		
		// More at Slip Full View level: #1 update flags to RptUnit grid, #2 update flags to XML, #3 control more button
		var nextStartRecNumSlip = DesktopWeb.Ajax.getSmartviewNextStartRecNum(moreSlpFullXML);

		if (nextStartRecNumSlip)
		{
			// #1 update flags to submission grid
			selectedRecordRptUnitFull.data['hasMoreLinkedSlip'] = 'yes';
			selectedRecordRptUnitFull.data['nextStartRecordNumLinkedSlip'] = nextStartRecNumSlip;
			
			// #2 update flags to XML
			setNodeValue('hasMoreLinkedSlip', 'yes', rptUnitNode);
			setNodeValue('nextStartRecordNumLinkedSlip', nextStartRecNumSlip, rptUnitNode);	

			// #3 control more button
			_resources.grids['accountGrid'].enableButton('moreBtn');
		}
		else{
			// #1 update flags to submission grid
			selectedRecordRptUnitFull.data['hasMoreLinkedSlip'] = 'no';
			selectedRecordRptUnitFull.data['nextStartRecordNumLinkedSlip'] = _BLNK;
			
			// #2 update flags to XML
			setNodeValue('hasMoreLinkedSlip', 'no', rptUnitNode);
			setNodeValue('nextStartRecordNumLinkedSlip', _BLNK, rptUnitNode);			
			
			// #3 control more button	
			_resources.grids['accountGrid'].disableButton('moreBtn');
		}
	}				
	
	function chkRptUnitXMLFound()
	{
		var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
		var selectedSubmissionUUID = selectedSubmission.data['FATCARptMstrUUID'];
		
		if (selectedSubmissionUUID != null)
		{
			var isRptUnitXMLFound = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']/RptUnits/RptUnit");		

			if (isRptUnitXMLFound == null)
			{				
				// call doSearch with runmode = reloadRptUnit
				searchAssignVal();
				doSearch(_RUNMODE_RELOADRptUnit, false);
			}
			else{				
				// load to reporting unit grid
				loadReportUnit(_fullXML, false);
			}
		}
	}
	
	function chkSlipXMLFound()
	{
		var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		var selectedReportUnitUUID = selectedReportUnit.data['FATCARptFileDetlUUID'];
	
		if (selectedReportUnitUUID != null)
		{
			var isSlipXMLFound = IFDS.Xml.getNode(_fullXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']/Slips/Slip");		

			if (isSlipXMLFound == null)
			{
				// call doSearch with runmode = reloadRptUnit
				searchAssignVal();
				doSearch(_RUNMODE_RELOADRptSlip, false);
			}			
			else{
				// load to reporting unit grid
				loadReportSlip(_fullXML);	
			}		
		}
	}	
	
	function validateUpdateSubmission(data, action)
	{
		// skip deleted adding or adjusting new record
		if (action == _DEL && (data['actionSub'] == _ADD || data['actionSub'] == _ADJ))
		{
			_self.doUpdateSubmission(data, action);	
		}
		else{		
			/***** #1 Submission Level ******/
			
			// build parameter xml
			var dataXML = IFDS.Xml.newDocument('data');
			var submissionXML = IFDS.Xml.addSingleNode(dataXML, 'Submission');
			
			IFDS.Xml.addSingleNode(submissionXML, 'action', data['actionSub']); // add,mod,del,adj
			IFDS.Xml.addSingleNode(submissionXML, 'FATCARptMstrUUID', data['FATCARptMstrUUID']);
			IFDS.Xml.addSingleNode(submissionXML, 'origFATCARptMstrUUID', data['origFATCARptMstrUUID']);
			IFDS.Xml.addSingleNode(submissionXML, 'FATCACode', data['FATCACode']);
			IFDS.Xml.addSingleNode(submissionXML, 'FILevel', data['FILevel']);
			IFDS.Xml.addSingleNode(submissionXML, 'FICode', data['FICode']);			
			IFDS.Xml.addSingleNode(submissionXML, 'taxYear', data['taxYear']);
			IFDS.Xml.addSingleNode(submissionXML, 'asOfDate', DesktopWeb.Util.getSMVDateValue(data['asOfDate']));
			IFDS.Xml.addSingleNode(submissionXML, 'TPSDeff', DesktopWeb.Util.getSMVDateValue(data['TPSDeff']));
			IFDS.Xml.addSingleNode(submissionXML, 'submissionType', data['submissionType']);
			IFDS.Xml.addSingleNode(submissionXML, 'submissionSeq', data['submissionSeq']);
			IFDS.Xml.addSingleNode(submissionXML, 'runMode', data['runMode']); // Test,Production
			IFDS.Xml.addSingleNode(submissionXML, 'rptFile', data['rptFile']);
			IFDS.Xml.addSingleNode(submissionXML, 'version', data['version']);
			IFDS.Xml.addSingleNode(submissionXML, 'runDate', DesktopWeb.Util.getSMVDateValue(data['runDate']));
			IFDS.Xml.addSingleNode(submissionXML, 'stat', data['msgStat']);
            IFDS.Xml.addSingleNode(submissionXML, 'countryOfDomicile', data['countryOfDomicile']);
            IFDS.Xml.addSingleNode(submissionXML, 'reptFFIChange', data['reptFFIChange']);
			
			IFDS.Xml.addSingleNode(submissionXML, 'RptUnits');
					
			/***** call service ******/
			
			 DesktopWeb.Ajax.doSmartviewAjax(_dtFATCARptValService, null, dataXML, responseHandler, _translationMap['Validating']);
		
			function responseHandler(success, responseXML, contextErrors, contextWarnings)
			{
				if (success)
				{	
					_self.doUpdateSubmission(data, action);
				}
			}
		}
	}

	function validateUpdateRptUnit(data, action)
	{
		/***** #1 Submission Level ******/
		
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		var submissionXML = IFDS.Xml.addSingleNode(dataXML, 'Submission');
		
		IFDS.Xml.addSingleNode(submissionXML, 'action', data['actionSub']); // adj
		IFDS.Xml.addSingleNode(submissionXML, 'FATCARptMstrUUID', data['FATCARptMstrUUID']);
		IFDS.Xml.addSingleNode(submissionXML, 'origFATCARptMstrUUID', data['origFATCARptMstrUUID']);
		IFDS.Xml.addSingleNode(submissionXML, 'FATCACode', data['FATCACode']);
		IFDS.Xml.addSingleNode(submissionXML, 'FILevel', data['FILevel']);
		IFDS.Xml.addSingleNode(submissionXML, 'FICode', data['FICode']);			
		IFDS.Xml.addSingleNode(submissionXML, 'taxYear', data['taxYear']);
		IFDS.Xml.addSingleNode(submissionXML, 'asOfDate', DesktopWeb.Util.getSMVDateValue(data['asOfDate']));
		IFDS.Xml.addSingleNode(submissionXML, 'TPSDeff', DesktopWeb.Util.getSMVDateValue(data['TPSDeff']));
		IFDS.Xml.addSingleNode(submissionXML, 'submissionType', data['submissionType']);
		IFDS.Xml.addSingleNode(submissionXML, 'submissionSeq', data['submissionSeq']);
		IFDS.Xml.addSingleNode(submissionXML, 'runMode', data['runMode']); // Test,Production
		IFDS.Xml.addSingleNode(submissionXML, 'rptFile', data['rptFile']);
		IFDS.Xml.addSingleNode(submissionXML, 'version', data['version']);
		IFDS.Xml.addSingleNode(submissionXML, 'runDate', DesktopWeb.Util.getSMVDateValue(data['runDate']));
		IFDS.Xml.addSingleNode(submissionXML, 'stat', data['msgStat']);
        IFDS.Xml.addSingleNode(submissionXML, 'countryOfDomicile', data['countryOfDomicile']);
        IFDS.Xml.addSingleNode(submissionXML, 'reptFFIChange', data['reptFFIChange']);
	
		/***** #2 Reporting Unit Level ******/		
	
		var rptUnitsXML = IFDS.Xml.addSingleNode(submissionXML, 'RptUnits');
		var rptUnitXML = IFDS.Xml.addSingleNode(rptUnitsXML, 'RptUnit');
		
		IFDS.Xml.addSingleNode(rptUnitXML, 'action', data['actionRpt']); // adj
		IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileUUID', data['FATCARptFileUUID']); // TEMP
		IFDS.Xml.addSingleNode(rptUnitXML, 'origFATCARptFileUUID', data['origFATCARptFileUUID']); // Original UUID
		IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileDetlUUID', data['FATCARptFileDetlUUID']); // TEMP
		IFDS.Xml.addSingleNode(rptUnitXML, 'origFATCARptFileDetlUUID', data['origFATCARptFileDetlUUID']); // Original UUID		
		IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileVer', data['FATCARptFileVer']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileDetlVer', data['FATCARptFileDetlVer']);		

		// Additional fields to create new reporting unit
		IFDS.Xml.addSingleNode(rptUnitXML, 'rptUnitLevelDesc', data['rptUnitLevelDesc']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'rptUnitName', data['rptUnitName']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'msgID', data['msgID']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'govTaxAgency', data['govTaxAgency']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'numRFFI', data['numRFFI']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'reportingFFI', data['reportingFFI']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'docRefID', data['docRefID']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'assocDocRefID', data['assocDocRefID']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'numSlip', data['numSlip']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'numSlipErr', data['numSlipErr']);	
		IFDS.Xml.addSingleNode(rptUnitXML, 'stat', data['fileStat']);
		
		IFDS.Xml.addSingleNode(rptUnitXML, 'Slips');
		
		/***** call service ******/
		
        DesktopWeb.Ajax.doSmartviewAjax(_dtFATCARptValService, null, dataXML, responseHandler, _translationMap['Validating']);
			
		function responseHandler(success, responseXML, contextErrors)
		{
			if (success)
			{
				// Assign flag to identify if user selects to do an adjustment of original submission record
				_isAdjustment = true;
				
				// Create a new set of data for creating a dummy(s) adjustment
				_origDataRptUnit = createDataSetOfOriginalAdjustment();				
				
				// Call Inq service to get a Reporting RFFI OR all Reporting RFFIs under Reporting Unit (to do dummy adjustment)
				searchAssignVal();
				_nextStartRecNum = 1;				
				doSearch(_RUNMODE_RELOADRptUnit, false);
				
				// Update XML & Grid of Reporting Unit level for Parent record (Dummy Submission)
				_self.doUpdateRptUnitParent(data, action);
			}
		}		
	}	
	
	function validateUpdateSlip(data, action)
	{
		// skip deleted adding new record
		if (action == _DEL && data['actionSlip'] == _ADD)
		{
			_self.doUpdateSlip(data, action);	
		}
		else{	
			/***** #1 Submission Level ******/
			
			// build parameter xml
			var dataXML = IFDS.Xml.newDocument('data');
			var submissionXML = IFDS.Xml.addSingleNode(dataXML, 'Submission');
			
			IFDS.Xml.addSingleNode(submissionXML, 'action', data['actionSub']); // add, mod, del ,uncg
			IFDS.Xml.addSingleNode(submissionXML, 'FATCARptMstrUUID', data['FATCARptMstrUUID']);
			IFDS.Xml.addSingleNode(submissionXML, 'origFATCARptMstrUUID', data['origFATCARptMstrUUID']);
			IFDS.Xml.addSingleNode(submissionXML, 'FATCACode', data['FATCACode']);
			IFDS.Xml.addSingleNode(submissionXML, 'FILevel', data['FILevel']);
			IFDS.Xml.addSingleNode(submissionXML, 'FICode', data['FICode']);				
			IFDS.Xml.addSingleNode(submissionXML, 'taxYear', data['taxYear']);
			IFDS.Xml.addSingleNode(submissionXML, 'asOfDate', DesktopWeb.Util.getSMVDateValue(data['asOfDate']));
			IFDS.Xml.addSingleNode(submissionXML, 'TPSDeff', DesktopWeb.Util.getSMVDateValue(data['TPSDeff']));
			IFDS.Xml.addSingleNode(submissionXML, 'submissionType', data['submissionType']);
			IFDS.Xml.addSingleNode(submissionXML, 'submissionSeq', data['submissionSeq']);
			IFDS.Xml.addSingleNode(submissionXML, 'runMode', data['runMode']); // Test,Production
			IFDS.Xml.addSingleNode(submissionXML, 'rptFile', data['rptFile']);
			IFDS.Xml.addSingleNode(submissionXML, 'version', data['version']);
			IFDS.Xml.addSingleNode(submissionXML, 'runDate', DesktopWeb.Util.getSMVDateValue(data['runDate']));
			IFDS.Xml.addSingleNode(submissionXML, 'stat', data['msgStat']);	
            IFDS.Xml.addSingleNode(submissionXML, 'countryOfDomicile', data['countryOfDomicile']);	
            IFDS.Xml.addSingleNode(submissionXML, 'reptFFIChange', data['reptFFIChange']);            
		
			/***** #2 Reporting Unit Level ******/		
		
			var rptUnitsXML = IFDS.Xml.addSingleNode(submissionXML, 'RptUnits');
			var rptUnitXML = IFDS.Xml.addSingleNode(rptUnitsXML, 'RptUnit');
			
			IFDS.Xml.addSingleNode(rptUnitXML, 'action', data['actionRpt']); // adj
			IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileUUID', data['FATCARptFileUUID']); // TEMP
			IFDS.Xml.addSingleNode(rptUnitXML, 'origFATCARptFileUUID', data['origFATCARptFileUUID']); // Original UUID
			// Single reporting Unit (entire file) is not allowed at slip level; always send origFATCARptFileDetlUUID
			IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileDetlUUID', data['FATCARptFileDetlUUID']); // TEMP
			IFDS.Xml.addSingleNode(rptUnitXML, 'origFATCARptFileDetlUUID', data['origFATCARptFileDetlUUID']); // Original UUID			
			IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileVer', data['FATCARptFileVer']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileDetlVer', data['FATCARptFileDetlVer']);	

			// Additional fields to create new reporting unit
			IFDS.Xml.addSingleNode(rptUnitXML, 'rptUnitLevelDesc', data['rptUnitLevelDesc']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'rptUnitName', data['rptUnitName']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'msgID', data['msgID']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'govTaxAgency', data['govTaxAgency']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'numRFFI', data['numRFFI']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'reportingFFI', data['reportingFFI']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'docRefID', data['docRefID']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'assocDocRefID', data['assocDocRefID']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'numSlip', data['numSlip']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'numSlipErr', data['numSlipErr']);	
			IFDS.Xml.addSingleNode(rptUnitXML, 'stat', data['fileStat']);
	
			/***** #3 Slip Level******/		
			
			var slipsXML = IFDS.Xml.addSingleNode(rptUnitXML, 'Slips');
			var slipXML = IFDS.Xml.addSingleNode(slipsXML, 'Slip');
			
			IFDS.Xml.addSingleNode(slipXML, 'action', data['actionSlip']); // add,mod,del
			IFDS.Xml.addSingleNode(slipXML, 'FATCARptSlipUUID', data['FATCARptSlipUUID']);
			IFDS.Xml.addSingleNode(slipXML, 'reportingFFI', data['reportingFFI']);	
			IFDS.Xml.addSingleNode(slipXML, 'account', data['account']);
			IFDS.Xml.addSingleNode(slipXML, 'entityID', data['entityID']);
			IFDS.Xml.addSingleNode(slipXML, 'entityType', data['entityType']);
			IFDS.Xml.addSingleNode(slipXML, 'entityName', data['entityName']);
			IFDS.Xml.addSingleNode(slipXML, 'submissionType', data['slipType']);
			IFDS.Xml.addSingleNode(slipXML, 'version', data['version']);
			
			/***** call service ******/
			
			DesktopWeb.Ajax.doSmartviewAjax(_dtFATCARptValService, null, dataXML, responseHandler, _translationMap['Validating']);
				
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					// Handle response
					var FATCARptValXML = IFDS.Xml.cloneDocument(responseXML);
					
					// get assocSlipID after validating
					_assocSlipID = IFDS.Xml.getNodeValue(FATCARptValXML, "//AssocFATCASlipID");
					
					_self.doUpdateSlip(data, action);
				}
			}
		}
	}
	
	function createDataSetOfOriginalAdjustment()
	{
		// Need to create a data set of ORIGINAL Adjustment (in case of do a another adjustment and back to hit more button of previous adjustment
		var data = {};
		var selectedRptUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		
		/***** To be used in Reporting Unit Level *****/
		data['actionRpt'] = _ADJ; // adj
		data['FATCARptFileVer'] = 1;
		data['FATCARptFileDetlVer'] = 1;
		
		if (selectedRptUnit.data['action'] == _ADJ) // copy from selected (already) adjusting one
		{
			data['FATCARptFileUUID'] = selectedRptUnit.data['FATCARptFileUUID'];
			data['origFATCARptFileUUID'] = selectedRptUnit.data['origFATCARptFileUUID'];
			// Copy CorrectDocRef ID from CorrectDocRef ID of adjustmenting one
			data['assocDocRefID'] = selectedRptUnit.data['assocDocRefID'];	
		}
		else{ // copy from selected 1st original (that do) adjustment
			data['FATCARptFileUUID'] = _self.getNewRptFileUUID(); // new UUID
			data['origFATCARptFileUUID'] = selectedRptUnit.data['FATCARptFileUUID'];	
			// Copy CorrectDocRef ID from DocRef ID of 1st original adjustment
			data['assocDocRefID'] = selectedRptUnit.data['docRefID'];	
		}
						
		/***** To be used to show new Reporting Unit Level *****/
		data['rptUnitLevelDesc'] = selectedRptUnit.data['rptUnitLevelDesc'];
		data['rptUnitName'] = selectedRptUnit.data['rptUnitName'];
		data['govTaxAgency'] = selectedRptUnit.data['govTaxAgency'];
				
		// Assign additional fields; not show when adjusting
		data['msgID'] = _BLNK;
		data['docRefID'] = _BLNK;
		data['numSlip'] = _BLNK;
		data['numSlipErr'] = _BLNK;
		data['numRFFI'] = _BLNK;
		data['fileStat'] =  _BLNK;

		// Fields will be overriden from Adjustment XML when creating dummy record	
		data['FATCARptFileDetlUUID'] = _BLNK;
		data['origFATCARptFileDetlUUID'] = _BLNK;
		data['reportingFFI'] = _BLNK;

		return data;	
	}	
	
	function createReportingUnitforAdjustment(adjustmentXML, originalData)
	{
		var newDataRptUnit = {};
		var isSingleRFFI = _resources.popups['adjustPopup'].getField('adjReqRptUnitName').getAllValues('SingleRFFI');
		var selectedReportingFFIDesc = _BLNK;
		var selectedOrigFATCARptFileDetlUUID = _BLNK;
		var selectedDocRefID = _BLNK;

		if (isSingleRFFI == 'yes') // Adjustment of Reporting RFFI
		{
			/** Only 1 dummy record is required **/
			
			var selectedReportingNode = IFDS.Xml.getNode(adjustmentXML, "//RptUnits/RptUnit");
			selectedReportingFFIDesc = IFDS.Xml.getNodeValue(selectedReportingNode, 'reportingFFI');	
			selectedOrigFATCARptFileDetlUUID = IFDS.Xml.getNodeValue(selectedReportingNode, 'FATCARptFileDetlUUID');	
			selectedDocRefID = IFDS.Xml.getNodeValue(selectedReportingNode, 'docRefID');
		
			// Get the new set of data
			newDataRptUnit = getNewRptUnitData(selectedReportingFFIDesc, selectedOrigFATCARptFileDetlUUID, selectedDocRefID);
			
			// Update XML & Grid of Reporting Unit level for Child record (Dummy Reporting Unit)
			_self.doUpdateRptUnitChild(newDataRptUnit, _ADJ);
		}
		else{ // Adjustment of Reporting Unit
			
			/** The dummy record(s) is required based on number of reporting RFFI under selected reporting unit **/		
				
			var selectedReportingNodes = IFDS.Xml.getNodes(adjustmentXML, "//RptUnits/RptUnit");
			Ext.each(selectedReportingNodes, function(selectedReportingNode)
			{
				selectedReportingFFIDesc = IFDS.Xml.getNodeValue(selectedReportingNode, 'reportingFFI');	
				selectedOrigFATCARptFileDetlUUID = IFDS.Xml.getNodeValue(selectedReportingNode, 'FATCARptFileDetlUUID');
				selectedDocRefID = IFDS.Xml.getNodeValue(selectedReportingNode, 'docRefID');
				
				// Get the new set of data
				newDataRptUnit = getNewRptUnitData(selectedReportingFFIDesc, selectedOrigFATCARptFileDetlUUID, selectedDocRefID);
				
				// Update XML & Grid of Reporting Unit level for Child record (Dummy Reporting Unit)
				_self.doUpdateRptUnitChild(newDataRptUnit, _ADJ);
			});	
		}
		
		function getNewRptUnitData(reportingFFIDesc, origFileDetlUUID, docRefID)		
		{
			// Need to generate new UUID for every new record (As of Key)
			originalData['FATCARptFileDetlUUID'] = _self.getNewRptFileDetlUUID();
			
			// Overide reportingFFI & origFATCARptFileDetlUUID & assocDocRefID from Adjustment XML
			originalData['reportingFFI'] = reportingFFIDesc;
			originalData['origFATCARptFileDetlUUID'] = origFileDetlUUID;
			originalData['assocDocRefID'] = docRefID;			
					
			return originalData;
		}		
	}
	
	function addSubmissionToXML(data, action)
	{
		if (!_fullXML)
		{			
			_fullXML = IFDS.Xml.newDocument("Submissions");
		}
		var newSubmissionXML = IFDS.Xml.newDocument("Submission");	
		
		IFDS.Xml.addSingleNode(newSubmissionXML, 'action', data['actionSub']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'FATCARptMstrUUID', data['FATCARptMstrUUID']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'origFATCARptMstrUUID', data['origFATCARptMstrUUID']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'FATCACode', data['FATCACode']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'FILevel', data['FILevel']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'FICode', data['FICode']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'taxYear', data['taxYear']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'asOfDate', DesktopWeb.Util.getSMVDateValue(data['asOfDate']));
		IFDS.Xml.addSingleNode(newSubmissionXML, 'TPSDeff', DesktopWeb.Util.getSMVDateValue(data['TPSDeff']));
		IFDS.Xml.addSingleNode(newSubmissionXML, 'submissionType', data['submissionType']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'submissionSeq', data['submissionSeq']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'runMode', data['runMode']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'rptFile', data['rptFile']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'version', data['version']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'runDate', DesktopWeb.Util.getSMVDateValue(data['runDate'])); 
		IFDS.Xml.addSingleNode(newSubmissionXML, 'stat', data['msgStat']);
		IFDS.Xml.addSingleNode(newSubmissionXML, 'RptUnits');
        IFDS.Xml.addSingleNode(newSubmissionXML, 'countryOfDomicile', data['countryOfDomicile']);
        IFDS.Xml.addSingleNode(newSubmissionXML, 'reptFFIChange', data['reptFFIChange']);        
		
		IFDS.Xml.appendNode(IFDS.Xml.getNode(_fullXML, "//Submissions"), newSubmissionXML);
		
		_self.updatesFlag = true;
	}
	
	function addRptUnitToXML(data, action)
	{
		var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
		var selectedSubmissionUUID = selectedSubmission.data['FATCARptMstrUUID'];
		
		var newRptUnitXML = IFDS.Xml.newDocument("RptUnit");
		
		IFDS.Xml.addSingleNode(newRptUnitXML, 'action', data['actionRpt']); // adj
		IFDS.Xml.addSingleNode(newRptUnitXML, 'FATCARptFileUUID', data['FATCARptFileUUID']); // TEMP
		IFDS.Xml.addSingleNode(newRptUnitXML, 'origFATCARptFileUUID', data['origFATCARptFileUUID']); // Original UUID
		IFDS.Xml.addSingleNode(newRptUnitXML, 'FATCARptFileDetlUUID', data['FATCARptFileDetlUUID']); // TEMP
		IFDS.Xml.addSingleNode(newRptUnitXML, 'origFATCARptFileDetlUUID', data['origFATCARptFileDetlUUID']); // Original UUID
		IFDS.Xml.addSingleNode(newRptUnitXML, 'FATCARptFileVer', data['FATCARptFileVer']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'FATCARptFileDetlVer', data['FATCARptFileDetlVer']);
		
		// Additional fields to create new reporting unit
		IFDS.Xml.addSingleNode(newRptUnitXML, 'rptUnitLevelDesc', data['rptUnitLevelDesc']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'rptUnitName', data['rptUnitName']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'msgID', data['msgID']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'govTaxAgency', data['govTaxAgency']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'numRFFI', data['numRFFI']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'reportingFFI', data['reportingFFI']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'docRefID', data['docRefID']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'assocDocRefID', data['assocDocRefID']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'numSlip', data['numSlip']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'numSlipErr', data['numSlipErr']);	
		IFDS.Xml.addSingleNode(newRptUnitXML, 'stat', data['fileStat']);	
		
		IFDS.Xml.addSingleNode(newRptUnitXML, 'Slips');
		
		// Append new Reporting Unit XML to parent Submissiont Node itself - filter by UUID
		IFDS.Xml.appendNode(IFDS.Xml.getNode(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']/RptUnits"), newRptUnitXML);
	
		_self.updatesFlag = true;	
	}
	
	function addSlipToXML(data, action)
	{
		var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		var selectedReportUnitUUID = selectedReportUnit.data['FATCARptFileDetlUUID'];

		var newSlipXML = IFDS.Xml.newDocument("Slip");
		
		IFDS.Xml.addSingleNode(newSlipXML, 'action', data['actionSlip']); // add, mod, del
		IFDS.Xml.addSingleNode(newSlipXML, 'FATCARptSlipUUID', data['FATCARptSlipUUID']);
		IFDS.Xml.addSingleNode(newSlipXML, 'reportingFFI', data['reportingFFI']);
		IFDS.Xml.addSingleNode(newSlipXML, 'account', data['account']);
		IFDS.Xml.addSingleNode(newSlipXML, 'entityID', data['entityID']);
		IFDS.Xml.addSingleNode(newSlipXML, 'entityType', data['entityType']);
		IFDS.Xml.addSingleNode(newSlipXML, 'entityName', data['entityName']);
		IFDS.Xml.addSingleNode(newSlipXML, 'submissionType', data['slipType']);
		IFDS.Xml.addSingleNode(newSlipXML, 'version', data['version']);
		IFDS.Xml.addSingleNode(newSlipXML, 'assocSlipID', _assocSlipID);
		
		// Append new Slip XML to parent RptUnit Node itself - filter by UUID
		IFDS.Xml.appendNode(IFDS.Xml.getNode(_fullXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']/Slips"), newSlipXML);

		_self.updatesFlag = true;		
	}
	
	function updateSubmissionToXML(data, action)
	{
		var submissionNode = getSelectedSubmissionNode();

		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'action'), data['actionSub']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'FATCARptMstrUUID'), data['FATCARptMstrUUID']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'origFATCARptMstrUUID'), data['origFATCARptMstrUUID']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'FATCACode'), data['FATCACode']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'FILevel'), data['FILevel']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'FICode'), data['FICode']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'taxYear'), data['taxYear']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'asOfDate'), DesktopWeb.Util.getSMVDateValue(data['asOfDate']));
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'TPSDeff'), DesktopWeb.Util.getSMVDateValue(data['TPSDeff']));
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'submissionType'), data['submissionType']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'submissionSeq'), data['submissionSeq']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'runMode'), data['runMode']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'rptFile'), data['rptFile']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'version'), data['version']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'runDate'), DesktopWeb.Util.getSMVDateValue(data['runDate']));
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'stat'), data['msgStat']);
        IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'countryOfDomicile'), data['countryOfDomicile']);			
		
		_self.updatesFlag = true;	
	}
	
	function updateSlipToXML(data, action)
	{
		var slipNode = getSelectedSlipNode();
		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'action'), data['actionSlip']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'FATCARptSlipUUID'), data['FATCARptSlipUUID']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'reportingFFI'), data['reportingFFI']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'account'), data['account']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'entityID'), data['entityID']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'entityType'), data['entityType']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'entityName'), data['entityName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'submissionType'), data['slipType']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'version'), data['version']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'assocSlipID'), _assocSlipID);

		_self.updatesFlag = true;	
	}
	
	function updateSubmissionToGrid(data, action)
	{
		switch(action)
		{
			case _ADD:
			{
				data['allowMod'] = 'yes';
				data['allowDel'] = 'yes';
				data['hasMoreLinkedRptUnit'] = 'no';
				data['action'] = _ADD;
				data['stat'] = data['msgStat'];
				data['errMsg'] = '';

				_resources.grids['submissionGrid'].addRecord(data);
				_resources.grids['submissionGrid'].selectLastRecord();
				
				break;
			}
			case _ADJ:
			{
				data['allowMod'] = 'yes';
				data['allowDel'] = 'yes';
				data['hasMoreLinkedRptUnit'] = 'no';
				data['action'] = _ADJ;
				data['stat'] = data['msgStat'];
				data['taxYear'] = data['taxYear'];
				data['submissionType'] = data['submissionType'];
				data['runMode'] = data['runMode'];
				data['errMsg'] = '';
				
				_resources.grids['submissionGrid'].addRecord(data);
				_resources.grids['submissionGrid'].selectLastRecord();
				
				break;			
			}
			case _MOD:
			{
				var submissionRec = _resources.grids['submissionGrid'].getSelectedRecord();
				var runMode = _MOD;

				// Check if new record adding; run mode should always be ADD
				if (submissionRec.data['action'] == _ADD) runMode = _ADD;
				submissionRec.data['action'] = runMode;
				
				submissionRec.data['FATCACode'] = data['FATCACode'];
				submissionRec.data['taxYear'] = data['taxYear'];
				submissionRec.data['asOfDate'] = data['asOfDate'];
				submissionRec.data['TPSDeff'] = data['TPSDeff'];
				submissionRec.data['submissionType'] = data['submissionType'];
				submissionRec.data['runMode'] = data['runMode'];
				submissionRec.data['rptFile'] = data['rptFile'];
				// Reporting Unit drop down split to FILevel & FICode
				submissionRec.data['FILevel'] = data['FILevel'];
				submissionRec.data['FICode'] = data['FICode'];
				submissionRec.data['stat'] = data['msgStat'];
				submissionRec.data['errMsg'] = '';
                submissionRec.data['countryOfDomicile'] = data['countryOfDomicile'];

				submissionRec.commit();
				
				break;
			}
			case _DEL:
			{				
				var submissionRec = _resources.grids['submissionGrid'].getSelectedRecord();
				
				if (submissionRec.data['action'] == _ADD) 
				{
					_resources.grids['submissionGrid'].removeSelectedRecord();
					_resources.grids['submissionGrid'].selectFirstRecord();					
				}else{
					submissionRec.data['action'] = _DEL;
					
					clearGrid('reportingUnitGrid');
					clearGrid('slipGrid');
					
					// Set row selected back to next record if the 1st one is deleted
					var selectedSubmissionIndex  = _resources.grids['submissionGrid'].store.indexOf(submissionRec);
					if (selectedSubmissionIndex == 0){
						setSelectedRow('submissionGrid', selectedSubmissionIndex + 1);
					}else{
						_resources.grids['submissionGrid'].selectFirstRecord();
					}

					submissionRec.commit();
				}
				
				break;
			}
		}	
	}
	
	function updateRptUnitToGrid(data, action)
	{
		switch(action)
		{
			case _ADJ:
			{
				data['allowMod'] = 'yes';
				data['hasMoreLinkedSlip'] = 'no';
				data['action'] = _ADJ;
				data['stat'] = data['fileStat'];
				data['errMsg'] = '';
				
				_resources.grids['reportingUnitGrid'].addRecord(data);
				_resources.grids['reportingUnitGrid'].selectLastRecord();
				
				break;
			}
		}
	}

	function updateSlipToGrid(data, action)
	{
		switch(action)
		{
			case _ADD:
			{
				data['allowMod'] = 'yes';
				data['allowDel'] = 'yes';
				data['action'] = _ADD;
				data['assocSlipID'] = _assocSlipID;
				data['submissionType'] = data['slipType'];
				data['errMsg'] = '';
				
				_resources.grids['slipGrid'].addRecord(data);
				_resources.grids['slipGrid'].selectLastRecord();
				
				break;
			}
			case _MOD:
			{
				var slipRec = _resources.grids['slipGrid'].getSelectedRecord();
				var runMode = _MOD;

				// Check if new record adding; run mode should always be ADD
				if (slipRec.data['action'] == _ADD) runMode = _ADD;
				slipRec.data['action'] = runMode;
				
				slipRec.data['account'] = data['account'];
				slipRec.data['entityName'] = data['entityName'];
				slipRec.data['reportingFFI'] = data['reportingFFI'];
				slipRec.data['submissionType'] = data['slipType'];
				// Entity Name drop down split to entityID & entitytype
				slipRec.data['entityID'] = data['entityID'];
				slipRec.data['entityType'] = data['entityType'];
				slipRec.data['errMsg'] = '';

				slipRec.commit();
				
				break;
			}
			case _DEL:
			{
				var slipRec = _resources.grids['slipGrid'].getSelectedRecord();
				if (slipRec.data['action'] == _ADD) 
				{
					_resources.grids['slipGrid'].removeSelectedRecord();
					_resources.grids['slipGrid'].selectFirstRecord();
				}else{
					slipRec.data['action'] = _DEL;
					
					// Set row selected back to next record if the 1st one is deleted
					var selectedSlipIndex  = _resources.grids['slipGrid'].store.indexOf(slipRec);
					if (selectedSlipIndex == 0){
						setSelectedRow('slipGrid', selectedSlipIndex + 1);
					}else{
						_resources.grids['slipGrid'].selectFirstRecord();
					}

					slipRec.commit();
				}
				
				break;
			}
		}
	}

	function deleteSubmissionFromXML(data, action)
	{
		var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
		var selectedSubmissionUUID = selectedSubmission.data['FATCARptMstrUUID'];
		
		var submissionNode = getSelectedSubmissionNode();	
		
		_self.updatesFlag = true;
		
		// Remove deleted adding new record out from XML
		if (action == _DEL && data['actionSub'] == _ADD)
		{
			var deleteXML = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']");
			
			if (deleteXML)
			{
				IFDS.Xml.deleteNode(deleteXML);	
			}
		}
		else{
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(submissionNode, 'action'), data['actionSub']);
		}
		
		// Disable buttons & genOutput flag (clear check box) if no records in grid
		var isSubmissionInXML = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission");
		if (!isSubmissionInXML)
		{
			updateSubmissionButtons(null);
			_resources.fields['genOutput'].disableField();
			_resources.fields['genOutput'].setValue(false);
		}		
	}
	
	function deleteSlipFromXML(data, action)
	{
		var selectedSlip = _resources.grids['slipGrid'].getSelectedRecord();
		var selectedSlipUUID = selectedSlip.data['FATCARptSlipUUID'];
	
		var slipNode = getSelectedSlipNode();
		
		_self.updatesFlag = true;
		
		// Remove deleted adding new record out from XML
		if (action == _DEL && data['actionSlip'] == _ADD)
		{
			var deleteXML = IFDS.Xml.getNode(_fullXML, "//Slips/Slip[FATCARptSlipUUID='" + selectedSlipUUID + "']");
			
			if (deleteXML)
			{
				IFDS.Xml.deleteNode(deleteXML);
			}			
		}
		else{
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(slipNode, 'action'), data['actionSlip']);
		}
		
		// Disable buttons if no records in grid
		var isSlipInXML = IFDS.Xml.getNode(_fullXML, "//Slips/Slip");
		if (!isSlipInXML)
		{
			updateSlipButtons(null);
		}		
	}
	
	function getSelectedSubmissionNode()
	{	
		var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
		var selectedSubmissionUUID = selectedSubmission.data['FATCARptMstrUUID'];
		
		return  IFDS.Xml.getNode(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSubmissionUUID + "']");
	}

	function getSelectedRptUnitNode()
	{
		var selectedReportUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
		var selectedReportUnitUUID = selectedReportUnit.data['FATCARptFileDetlUUID'];

		return  IFDS.Xml.getNode(_fullXML, "//RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedReportUnitUUID + "']");
	}
	
	function getSelectedSlipNode()
	{
		var selectedSlip = _resources.grids['slipGrid'].getSelectedRecord();
		var selectedSlipUUID = selectedSlip.data['FATCARptSlipUUID'];
	
		return  IFDS.Xml.getNode(_fullXML, "//Slips/Slip[FATCARptSlipUUID='" + selectedSlipUUID + "']");
	}

	function buildUpdateXML()
	{
		var updatedXML = IFDS.Xml.newDocument("data");
		var delSubNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[action='" + _DEL + "']");
		
		var modSubNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[action='" + _MOD + "']");
		
		var adjSubNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[action='" + _ADJ + "']");
		
		var addSubNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[action='" + _ADD + "']");
		
		var uncSubNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[action='" + _UNCG + "']");
		
		var submissionsXML = IFDS.Xml.addSingleNode(updatedXML, "Submissions");
		Ext.each(delSubNodes, function(delSubNode){buildUpdatedSubmissionXML(delSubNode, submissionsXML);});
		Ext.each(modSubNodes, function(modSubNode){buildUpdatedSubmissionXML(modSubNode, submissionsXML);});
		Ext.each(adjSubNodes, function(adjSubNode){buildUpdatedSubmissionXML(adjSubNode, submissionsXML);});
		Ext.each(addSubNodes, function(addSubNode){buildUpdatedSubmissionXML(addSubNode, submissionsXML);});
		Ext.each(uncSubNodes, function(uncSubNode){buildUpdatedSubmissionXML(uncSubNode, submissionsXML);});
		
		return updatedXML;
		
		function buildUpdatedSubmissionXML(submissionNode, context)
		{
			var action = IFDS.Xml.getNodeValue(submissionNode, 'action');
			
			var submissionXML = IFDS.Xml.addSingleNode(context, 'Submission');
			
			/* Always in XML for all actions */
			IFDS.Xml.addAttribute(submissionXML, 'RecordSource', IFDS.Xml.getNodeValue(submissionNode, 'FATCARptMstrUUID'));
			IFDS.Xml.addSingleNode(submissionXML, 'action', action);
			IFDS.Xml.addSingleNode(submissionXML, 'FATCARptMstrUUID', IFDS.Xml.getNodeValue(submissionNode, 'FATCARptMstrUUID'));
			IFDS.Xml.addSingleNode(submissionXML, 'version', IFDS.Xml.getNodeValue(submissionNode, 'version'));
			IFDS.Xml.addSingleNode(submissionXML, 'FATCACode', IFDS.Xml.getNodeValue(submissionNode, 'FATCACode'));
			IFDS.Xml.addSingleNode(submissionXML, 'FILevel', IFDS.Xml.getNodeValue(submissionNode, 'FILevel')); 
			IFDS.Xml.addSingleNode(submissionXML, 'FICode', IFDS.Xml.getNodeValue(submissionNode, 'FICode')); 
			IFDS.Xml.addSingleNode(submissionXML, 'taxYear', IFDS.Xml.getNodeValue(submissionNode, 'taxYear'));
			IFDS.Xml.addSingleNode(submissionXML, 'asOfDate', IFDS.Xml.getNodeValue(submissionNode, 'asOfDate'));
			IFDS.Xml.addSingleNode(submissionXML, 'TPSDeff', IFDS.Xml.getNodeValue(submissionNode, 'TPSDeff'));
			IFDS.Xml.addSingleNode(submissionXML, 'submissionType', IFDS.Xml.getNodeValue(submissionNode, 'submissionType'));
			IFDS.Xml.addSingleNode(submissionXML, 'submissionSeq', IFDS.Xml.getNodeValue(submissionNode, 'submissionSeq'));
			IFDS.Xml.addSingleNode(submissionXML, 'runMode', IFDS.Xml.getNodeValue(submissionNode, 'runMode'));
			IFDS.Xml.addSingleNode(submissionXML, 'rptFile', IFDS.Xml.getNodeValue(submissionNode, 'rptFile'));	
			IFDS.Xml.addSingleNode(submissionXML, 'genOutput', IFDS.Xml.getNodeValue(submissionNode, 'genOutput'));
            IFDS.Xml.addSingleNode(submissionXML, 'countryOfDomicile', IFDS.Xml.getNodeValue(submissionNode, 'countryOfDomicile'));
            IFDS.Xml.addSingleNode(submissionXML, 'reptFFIChange', IFDS.Xml.getNodeValue(submissionNode, 'reptFFIChange'));
			
			switch (action){
				case _DEL:
					break;
				case _MOD:
					IFDS.Xml.addSingleNode(submissionXML, 'rptUnitFILevel', IFDS.Xml.getNodeValue(submissionNode, 'rptUnitFILevel'));
					IFDS.Xml.addSingleNode(submissionXML, 'rptUnitFICode', IFDS.Xml.getNodeValue(submissionNode, 'rptUnitFICode'));
					buildUpdatedRptUnitsXML(submissionNode, submissionXML);
					break;
				case _ADJ:
					IFDS.Xml.addSingleNode(submissionXML, 'origFATCARptMstrUUID', IFDS.Xml.getNodeValue(submissionNode, 'origFATCARptMstrUUID'));
					buildUpdatedRptUnitsXML(submissionNode, submissionXML);
					break;
				case _ADD:
					IFDS.Xml.addSingleNode(submissionXML, 'rptUnitFILevel', IFDS.Xml.getNodeValue(submissionNode, 'rptUnitFILevel'));
					IFDS.Xml.addSingleNode(submissionXML, 'rptUnitFICode', IFDS.Xml.getNodeValue(submissionNode, 'rptUnitFICode'));
					break;							
				case _UNCG: // Unchange mode need to be validated when update again
					IFDS.Xml.addSingleNode(submissionXML, 'origFATCARptMstrUUID', IFDS.Xml.getNodeValue(submissionNode, 'origFATCARptMstrUUID'));			
					buildUpdatedRptUnitsXML(submissionNode, submissionXML);
					break;							
			}
		}
		
		function buildUpdatedRptUnitsXML(submissionNode, context)
		{
			var adjRptNodes = IFDS.Xml.getNodes(submissionNode, "RptUnits/RptUnit[action='" + _ADJ + "']");
			
			var unRptNodes = IFDS.Xml.getNodes(submissionNode, "RptUnits/RptUnit[action='" + _UNCG + "']");
			
			var rptUnitsXML = IFDS.Xml.addSingleNode(context, 'RptUnits');
			
			Ext.each(adjRptNodes, function(adjRptNode){buildUpdatedRptUnitXML(adjRptNode, rptUnitsXML);});
			Ext.each(unRptNodes, function(unRptNode){buildUpdatedRptUnitXML(unRptNode, rptUnitsXML);});

			function buildUpdatedRptUnitXML(rptUnitNode, context)
			{
				var action = IFDS.Xml.getNodeValue(rptUnitNode, 'action');
				
				var rptUnitXML = IFDS.Xml.addSingleNode(context, 'RptUnit');
				
				/* Always in XML for all actions */
				IFDS.Xml.addAttribute(rptUnitXML, 'RecordSource', IFDS.Xml.getNodeValue(rptUnitNode, 'FATCARptFileDetlUUID'));
				IFDS.Xml.addSingleNode(rptUnitXML, 'action', action);
				IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileUUID', IFDS.Xml.getNodeValue(rptUnitNode, 'FATCARptFileUUID'));
				IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileDetlUUID', IFDS.Xml.getNodeValue(rptUnitNode, 'FATCARptFileDetlUUID'));
				IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileVer', IFDS.Xml.getNodeValue(rptUnitNode, 'FATCARptFileVer'));
				IFDS.Xml.addSingleNode(rptUnitXML, 'FATCARptFileDetlVer', IFDS.Xml.getNodeValue(rptUnitNode, 'FATCARptFileDetlVer'));
				
				switch (action){
					case _MOD:
						break;				
					case _ADJ:
					case _UNCG: // Unchange mode need to be validated when update again
						IFDS.Xml.addSingleNode(rptUnitXML, 'origFATCARptFileUUID', IFDS.Xml.getNodeValue(rptUnitNode, 'origFATCARptFileUUID'));
						IFDS.Xml.addSingleNode(rptUnitXML, 'origFATCARptFileDetlUUID', IFDS.Xml.getNodeValue(rptUnitNode, 'origFATCARptFileDetlUUID'));
						buildUpdatedSlipsXML(rptUnitNode, rptUnitXML);
						break;
				}
			}
		}
		
		function buildUpdatedSlipsXML(rptUnitNode, context)
		{
			var delSlipNodes = IFDS.Xml.getNodes(rptUnitNode, "Slips/Slip[action='" + _DEL + "']");

			var modSlipNodes = IFDS.Xml.getNodes(rptUnitNode, "Slips/Slip[action='" + _MOD + "']");

			var addSlipNodes = IFDS.Xml.getNodes(rptUnitNode, "Slips/Slip[action='" + _ADD + "']");

			var slipsXML = IFDS.Xml.addSingleNode(context, 'Slips');
			
			Ext.each(delSlipNodes, function(delSlipNode){buildUpdatedSlipXML(delSlipNode, slipsXML);});
			Ext.each(modSlipNodes, function(modSlipNode){buildUpdatedSlipXML(modSlipNode, slipsXML);});
			Ext.each(addSlipNodes, function(addSlipNode){buildUpdatedSlipXML(addSlipNode, slipsXML);});

			function buildUpdatedSlipXML(slipNode, context)
			{
				var action = IFDS.Xml.getNodeValue(slipNode, 'action');
				
				var slipXML = IFDS.Xml.addSingleNode(context, 'Slip');
				
				/* Always in XML for all actions */
				IFDS.Xml.addAttribute(slipXML, 'RecordSource', IFDS.Xml.getNodeValue(slipNode, 'FATCARptSlipUUID'));
				IFDS.Xml.addSingleNode(slipXML, 'action', action);
				IFDS.Xml.addSingleNode(slipXML, 'FATCARptSlipUUID', IFDS.Xml.getNodeValue(slipNode, 'FATCARptSlipUUID'));
				IFDS.Xml.addSingleNode(slipXML, 'version', IFDS.Xml.getNodeValue(slipNode, 'version'));
				IFDS.Xml.addSingleNode(slipXML, 'account', IFDS.Xml.getNodeValue(slipNode, 'account'));
				IFDS.Xml.addSingleNode(slipXML, 'entityID', IFDS.Xml.getNodeValue(slipNode, 'entityID'));
				IFDS.Xml.addSingleNode(slipXML, 'entityType', IFDS.Xml.getNodeValue(slipNode, 'entityType'));
				IFDS.Xml.addSingleNode(slipXML, 'submissionType', IFDS.Xml.getNodeValue(slipNode, 'submissionType'));
						
				switch (action){
					case _ADD:
						IFDS.Xml.addSingleNode(slipXML, 'assocSlipID', IFDS.Xml.getNodeValue(slipNode, 'assocSlipID'));
						break;
					case _MOD:
						break;
					case _DEL:
						break;
				}
			}
		}
	}	
	
	function clickHandleDetl_searchBtn()
	{
		if (_self.updatesFlag){
			DesktopWeb.Util.displayDiscardPrompt(performSearch);
		}else{
			performSearch(true);
		}
		function performSearch(confirm){
			if (confirm){
				if (validateSearchCriteria()){
					_self.updatesFlag = false;
					
					searchMainAssignVal();
					searchAssignVal();
						
					_nextStartRecNum = 1;
						
					clearGrid('slipGrid');
					clearGrid('reportingUnitGrid');
					clearGrid('submissionGrid');
						
					doSearch(_RUNMODE_RELOAD, false);
					
					// show/hide column for CRS Enhancement Phase2
					if(_currentSearch['regulationFld'] == _CRS){
						_resources.grids['submissionGrid'].showColumn(2);	
						_resources.grids['submissionGrid'].hideColumn(7);
						_resources.grids['reportingUnitGrid'].hideColumn(1);	
						_resources.grids['reportingUnitGrid'].hideColumn(2);						
					}else{
						_resources.grids['submissionGrid'].hideColumn(2);	
						_resources.grids['submissionGrid'].showColumn(7);	
						_resources.grids['reportingUnitGrid'].showColumn(1);	
						_resources.grids['reportingUnitGrid'].showColumn(2);	
					}
				}
			}
		}	
	}
	
	function clickHandleDetl_searchSlipBtn()
	{
		if (_self.updatesFlag){
			DesktopWeb.Util.displayDiscardPrompt(performSearch);
		}else{
			performSearch(true);
		}
		function performSearch(confirm){
			if (confirm){
				if (validateSearchCriteria()){
					_self.updatesFlag = false;
				
					searchAssignVal();
						
					_nextStartRecNum = 1;
						
					clearGrid('accountGrid');
					
					_isSlipFullView = true;
					
					doSearch(_RUNMODE_RELOADRptSlip, false);
					
					updateSlipFullButtons();
				}
			}
		}
	}
	
	function setSelectedRow(gridName, index)
	{
		_resources.grids[gridName].setSelectedRecord(index);
	}
	
	function storeContextErrors(errorNodes)
	{

		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			var filedName = IFDS.Xml.getNodeValue(errorNodes[i], 'fieldSource/xmlElementName');
			var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			
			if(table == 'Submission')
			{
				// Update XML
				var submissionNode = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + uuid + "']");
				updateErrMsgNode(errMsg, submissionNode, true);
				
				// Update Grid
				var recordIndex = _resources.grids['submissionGrid'].getStore().find(filedName, uuid);
				if (recordIndex > -1){
					var errorRecord = _resources.grids['submissionGrid'].getStore().getAt(recordIndex);
					errorRecord.set('errMsg', errMsg);

					_resources.grids['submissionGrid'].getStore().commitChanges(); 
				}
				
			}else if (table == 'RptUnit')
			{
				// Update XML
				var rptUnitNode = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission/RptUnits/RptUnit[FATCARptFileDetlUUID='" + uuid + "']");
					updateErrMsgNode(errMsg, rptUnitNode, true);
					
					// TODO: Update parent level
					var submissionNode = rptUnitNode.parentNode.parentNode;
					updateErrMsgNode(_translationMap['ERR_AT_REPORTING_UNIT_LEVEL'], submissionNode, false);
				
				// Update Grid Reporting Unit Level
				updateErrMsgGridByPrkey(_resources.grids['reportingUnitGrid'], 
									errMsg, 
									filedName, 
									uuid);

				// Update Grid Submission Level
				updateErrMsgGridByPrkey(_resources.grids['submissionGrid'], 
									_translationMap['ERR_AT_REPORTING_UNIT_LEVEL'],
									"FATCARptMstrUUID", 
									IFDS.Xml.getNodeValue(submissionNode, 'FATCARptMstrUUID'));

			}else if (table == 'Slip') 
			{
				// Update XML
				var slipNode = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission/RptUnits/RptUnit/Slips/Slip[FATCARptSlipUUID='" + uuid + "']");

					updateErrMsgNode(errMsg, slipNode);
					
					// TODO: Update parent level
					var rptUnitNode = slipNode.parentNode.parentNode;
					updateErrMsgNode(_translationMap['ERR_AT_SLIP_LEVEL'], rptUnitNode, false);
					
					// TODO: Update parent level
					var submissionNode = rptUnitNode.parentNode.parentNode;
					updateErrMsgNode(_translationMap['ERR_AT_SLIP_LEVEL'], submissionNode, false);
				
				// Update Slip Grid
				updateErrMsgGridByPrkey(_resources.grids['slipGrid'], 
									errMsg, 
									filedName, 
									uuid);

				// Update Grid Reporting Unit Level
				updateErrMsgGridByPrkey(_resources.grids['reportingUnitGrid'],
									_translationMap['ERR_AT_SLIP_LEVEL'],
									"FATCARptFileDetlUUID", 
									IFDS.Xml.getNodeValue(rptUnitNode, 'FATCARptFileDetlUUID'));

				// Update Grid Submission Level
				updateErrMsgGridByPrkey(_resources.grids['submissionGrid'], 
									_translationMap['ERR_AT_SLIP_LEVEL'], 
									"FATCARptMstrUUID", 
									IFDS.Xml.getNodeValue(submissionNode, 'FATCARptMstrUUID'));
			}
		}
		
		function updateErrMsgGridByPrkey(grid, errMsg, prKeyFiled, prKeyValue)
		{
			var store = grid.getStore();
			var recordIndex = store.find(prKeyFiled, prKeyValue);
			if (recordIndex > -1){
				var errorRecord = store.getAt(recordIndex);
				errorRecord.set('errMsg', errMsg);
				store.commitChanges();
			}
		}
		
		function updateErrMsgNode(errMsg, context, replace)
		{
			if (!context) return;
			var errMsgNode = IFDS.Xml.getNode(context, 'errMsg');
			if (errMsgNode)
			{
				var text = IFDS.Xml.getNodeValue(errMsgNode, '.');
				if (!text || (text && text == '') || replace) IFDS.Xml.setNodeValue(errMsgNode, errMsg);
			}else{
				IFDS.Xml.addSingleNode(context, 'errMsg', errMsg);
			}
		}
	}
	
	function clearContextErrors()
	{
		// Update XML
		var errNodes = IFDS.Xml.getNodes(_fullXML, "//errMsg");
		Ext.each(errNodes, function(errNode){
			IFDS.Xml.deleteNode(errNode);
		});
		
		// Update grids
		clearStoreErrorMessage(_resources.grids['submissionGrid'].getStore());
		clearStoreErrorMessage(_resources.grids['reportingUnitGrid'].getStore());
		clearStoreErrorMessage(_resources.grids['slipGrid'].getStore());
		
		function clearStoreErrorMessage(store)
		{
			var errRecords = store.queryBy(function(record){return record.data['errMsg'] != ''});
			for (var i = 0; i < errRecords.getCount(); i++)
			{
				var errRecord = errRecords.itemAt(i);
				errRecord.set('errMsg', _BLNK);
			} 			
			store.commitChanges();
		}
		
	}
	
	function buildErrorFlag(msg)
	{
		return '<img style="text-align:right" qtip="' + msg + '" qclass="x-form-invalid-tip" src="' + DesktopWeb._SRC_PATH + 'images/error_small.png" />'
	}
	
	function replaceInvalidXMLChar(str)
	{
		if ((typeof(str) === 'string' || str instanceof String ) && str.trim().length > 0)
			str = str.replace(/&/g, "&amp;").replace(/>/g, "&gt;").replace(/</g, "&lt;").replace(/"/g, "&quot;").replace(/'/g,"&apos;");
		
		return str;
	}	
 
	// PUBLIC ITEMS *************************************
	return {				
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,INQ: _INQ
		,ADJ: _ADJ
		,UNCG: _UNCG
		,BLNK: _BLNK
		,USFATCA: _USFATCA
		,CRS: _CRS
		,ORG: _ORG
		,AMD: _AMD
		,COR: _COR
		,CAN: _CAN
		,HMRC: _HMRC
		,CRA: _CRA
		,IRS: _IRS
		,REPORTINGFFI: _REPORTINGFFI
		,REPORTINGUNIT: _REPORTINGUNIT
		,ALLREPORTING: _ALLREPORTING
		,MSGSTAT_Pending: _MSGSTAT_Pending
		,MSGSTAT_Processed: _MSGSTAT_Processed
		,MSGSTAT_Processing: _MSGSTAT_Processing
		,RUNMODE_Production: _RUNMODE_Production
		,RUNMODE_Test: _RUNMODE_Test
		,REPORTFILE_All: _REPORTFILE_All
		,REPORTFILE_SingleRFFI: _REPORTFILE_SingleRFFI
		,REPORTFILE_SingleUnit: _REPORTFILE_SingleUnit
        ,REPORTFILE_CntyOfDomicile: _REPORTFILE_CntyOfDomicile
		,updatesFlag: false
		,isErrorOfEffRptListByAsOfDate: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			// Call init service			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);
			
			DesktopWeb.Ajax.doSmartviewAjax(_dtFATCARptInitService, null, dataXML, responseHandler, _translationMap['Loading']);
            
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					// Handle response
					_FATCARptInitXML = IFDS.Xml.cloneDocument(responseXML);
					
					// Load permission
					storePermissions(responseXML);					

					// Load dropdown
					if (_permissions[_self.INQ]){
						populateDropdownList(responseXML);
					}
					
					// Load Default Values
					loadDefaultValues(responseXML);					

					// Call reload service with default Regulation & TaxYear
					_ignoreErrorCode = {ignoreErrorCode: '15'};
					clickHandleDetl_searchBtn();
					_ignoreErrorCode = null;

				}else{
					disableScreen();
				}
			}	
		}
		
		,buildErrorFlag: function(msg)
		{
			return buildErrorFlag(msg);
		}
		
		,clearContextErrors: function()
		{
			clearContextErrors();
		}
		
		,checkUpdatesFlag: function()
		{
			_self.updatesFlag = false;
			
			// Submission level	- no need to check child levels since Parent action has value (not blank) if any changes at all levels
			var isActionSubNotBlank = IFDS.Xml.getNode(_fullXML, "//Submissions/Submission[action!='" + _BLNK + "']");
			
			if (isActionSubNotBlank)
			{
				_self.updatesFlag = true;
			}
		}
		
		,selectSubmission: function(record, index)
		{
			clearGrid('reportingUnitGrid');	
			clearGrid('slipGrid');	
			
			updateSubmissionButtons(record);
			
			/**
				#1 To disable genOutput check box based on conditions
				RunMode : 02-Test & Msg Status : 03-Processing
				RunMode : 01-Production & Msg Status : 03-Processing or 02-Processed
			 **/
			var flagGenOutput = _resources.fields['genOutput'];
			if ( (record.data['stat'] == _MSGSTAT_Processing || (record.data['stat'] == _MSGSTAT_Processed && record.data['runMode'] == _RUNMODE_Production)))
			{
				flagGenOutput.disableField();
				flagGenOutput.setValue(false);
			}
			else
			{
				flagGenOutput.enableField();
				
				// #2 Refresh genOutput check box of each submission
				if (record.data['genOutput'] == 'yes'){
					flagGenOutput.setValue(true);
				}else{
					flagGenOutput.setValue(false);
				}			
			}
			
					
			// 3# control how to display grid when re-selecting record
			if (record.data['action'] == _ADD || record.data['action'] == _DEL){
			
				// Delete the only one record in grid; buttons (except ADD) need to be disable as original state
				if (record.data['action'] == _DEL){
					updateSubmissionButtons(null);
				}
				// Not call search service
				return
			}
			else if (record.data['action'] == _ADJ || record.data['action'] == _MOD){
				// load to reporting unit grid
				loadReportUnit(_fullXML, false);
			}
			else{
				chkRptUnitXMLFound();
			}
		}

		,selectReportingUnit: function(record, index)
		{
			var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
			
			// To load Slip level if inquiry SlipFullView before
			_isSlipFullView = false;

			clearGrid('slipGrid');	
			
			updateRptUnitButtons(record);	
			
			/**
				#1 To enable Add button at slip level when;
				- New adjusting record (only 02-Single reporting RFFI)
				- Existing adjustment (SubmissionType: NOT ORG-Orginal & RunMode: 02-Test & MsgStat: 01-Pending)
			 **/
			 
			if ( (record.data['action'] == _ADJ && selectedSubmission.data['rptFile'] == _REPORTFILE_SingleRFFI) ||
				 (selectedSubmission.data['submissionType'] != _ORG && selectedSubmission.data['runMode'] == _RUNMODE_Test && selectedSubmission.data['stat'] == _MSGSTAT_Pending) )
			{
				// enable add button at slip level
				_resources.grids['slipGrid'].enableButton('addBtn');
			}
			
			// #2 control how to display grid when re-selecting record
			if (record.data['action'] == _ADJ){
				// load to slip grid
				loadReportSlip(_fullXML);
			}
			else{
				chkSlipXMLFound();
			}
		}
		
		,selectSlip: function(record, index)
		{			
			// Delete the only one record in grid; buttons (exept ADD) need to be disable as original state
			if (record.data['action'] == _DEL){
				updateSlipButtons(null);
			}else{
				updateSlipButtons(record);
			}
		}
		
		,selectSlipFullView: function(record, index)
		{
			updateSlipFullButtons();
		}
		
		,openActionPopup: function(name, action)
		{
			var popup = _resources.popups[name];	
			popup.show();
			popup.init(action);
		}
		
		,openHistoryPopup: function(recType)
		{
			var viewParam = {};
			var historyName = null;
			var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
			var selectedRptUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
			var selectedSlip = _resources.grids['slipGrid'].getSelectedRecord();
			
			if (recType == 'Submission')
			{
				viewParam['auditType'] = 'FATCARptMstr';
				viewParam['searchValue1'] = selectedSubmission.get('FATCARptMstrUUID');
				historyName = _translationMap['SubmissionTitle']+ ' - ' +_translationMap['History'];
			}
			else if (recType == 'ReportingUnit')
			{
				viewParam['auditType'] = 'FATCARptFileDetl';
				viewParam['searchValue1'] = selectedRptUnit.get('FATCARptFileDetlUUID');	
				historyName = _translationMap['ReportingTitle']+ ' - ' +_translationMap['History'];		
			}
			else // slipFullPopup
			{
				viewParam['auditType'] = 'FATCARptSlip';
				viewParam['searchValue1'] = selectedSlip.get('FATCARptSlipUUID');	
				historyName = _translationMap['SlipTitle']+ ' - ' +_translationMap['History'];		
			}
			
			_resources.popups['history'].init(historyName, _dtHistoryService, viewParam, true);
			_resources.popups['history'].show();
		}		
		
		,openAdminPopup: function(recType)
		{					
			var title = null;	
			var selectedRecord = null;
			if (recType == 'Submission')
			{
				selectedRecord = _resources.grids['submissionGrid'].getSelectedRecord();
				title = _translationMap['SubmissionTitle']+ ' - ' +_translationMap['Admin']
			}
			else if (recType == 'ReportingUnit')
			{
				selectedRecord = _resources.grids['reportingUnitGrid'].getSelectedRecord();
				title = _translationMap['ReportingTitle']+ ' - ' +_translationMap['Admin']
			}
			else // Slip
			{
				selectedRecord = _resources.grids['slipGrid'].getSelectedRecord();
				title = _translationMap['SlipTitle']+ ' - ' +_translationMap['Admin']
			}
			
			var adminData = {};
			adminData['userName'] = selectedRecord.get('userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('procDate'));
			adminData['modUser'] = selectedRecord.get('modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('modDate'));

			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}

		,clickHandle_searchBtn: function()
		{
			clickHandleDetl_searchBtn();
		}

		,clickHandle_searchSlipBtn: function()
		{
			clickHandleDetl_searchSlipBtn();
		}
		
		,clickHandle_moreBtn: function()
		{
			searchAssignVal();
			doSearch(_RUNMODE_RELOAD, true);
		}
		
		,clickHandle_moreBtnRptUnit: function()
		{
			// Identify if More is required for General inquiry OR Adjustment
			var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
			
			// Assign flag to identify adjustment action
			if (selectedSubmission.data['action'] == _ADJ)
			{
				_isAdjustment = true;
				
				// Create a new set of data for creating a dummy(s) adjustment
				_origDataRptUnit = createDataSetOfOriginalAdjustment();				
			}else{
				_isAdjustment = false;
				_origDataRptUnit = null;
			}
			
			searchAssignVal();
			doSearch(_RUNMODE_RELOADRptUnit, true);
		}
		
		,clickHandle_moreBtnSlipFullView: function()
		{
			searchAssignVal();
			doSearch(_RUNMODE_RELOADRptSlip, true);
		}
		
		,selectHandle_regulationFld: function(regulation)
		{
			_resources.fields['taxYearFld'].setValue(_defaultValues[regulation + "TaxYearFld"]);
		}
		
		,getNewSubmissionUUID: function()
		{
			return "TMPSUBMISSION" + (_nextUUID++);
		}
		
		,getNewRptFileUUID: function()
		{
			return "TMPRPTFILE" + (_nextUUID++);
		}

		,getNewRptFileDetlUUID: function()
		{
			return "TMPRPTFILEDETL" + (_nextUUID++);
		}

		,getNewSlipUUID: function()
		{
			return "TMPSLIP" + (_nextUUID++);
		}
		
		,getDefault: function(defaultName)
		{
			return _defaultValues[defaultName];
		}

		,getCurrentSearch: function(fieldname)
		{
			return _currentSearch[fieldname];
		}
		
		,validateSubmission: function(data, action)
		{
			validateUpdateSubmission(data, action);
		}	

		,validateRptUnit: function(data, action)
		{
			validateUpdateRptUnit(data, action);
		}
		
		,validateSlip: function(data, action)
		{
			validateUpdateSlip(data, action);
		}

		,toPopulateDropdownListReporting: function (listName)
		{
			populateDropdownListReporting(listName);
		}

		,getListValueDesc: function(listName, value)
		{
			var valueDesc = null;
			valueDesc = IFDS.Xml.getNodeValue(_FATCARptInitXML, "*/List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");
			if (valueDesc == null || valueDesc == "")
			{
				valueDesc = IFDS.Xml.getNodeValue(_FATCARptInitXML, "*/List[@id = '" + listName + "']/Element[code = '" + value + "']/value");
			}
			return valueDesc;
		}
		
		,getDisplayReportingUnit: function (listName, FICode, FILevel)
		{
			var dispValue = FICode + ',' + FILevel;
			var reportingUnitList = IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = '" + listName + "']/Element[FILevel='" + FILevel + "' and FICode='" + FICode + "']");
			
			if (reportingUnitList)
			{
				reportingUnitList = reportingUnitList ? reportingUnitList:IFDS.Xml.getNode(_FATCARptInitXML, "//List[@id = '" + listName + "']/Element[FILevel='" + FILevel + "' and FICode='" + FICode + "']");
			
				dispValue = reportingUnitList ? IFDS.Xml.getNodeValue(reportingUnitList, 'FIDesc') : dispValue;
			}else{
				dispValue = _self.BLNK;
			}
			
			return dispValue;
		}		
		
		,loadAccountSuggestField: function(acctNum)
		{	
			var accountXML = IFDS.Xml.newDocument('data');			
			IFDS.Xml.addSingleNode(accountXML, 'searchValue', acctNum);
			IFDS.Xml.addSingleNode(accountXML, 'maxRecords', 14);
			IFDS.Xml.addSingleNode(accountXML, 'startRecordNum', '');
			IFDS.Xml.addSingleNode(accountXML, 'incAllStat', 'no');
			
			DesktopWeb.Ajax.doSmartviewAjax('AccountSearch', null, accountXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{					
				if (success)
				{
					_resources.popups['acctReqPopup'].getField('actReqAccount').getStore().loadData(IFDS.Xml.getNode(responseXML, '/*//PossibleMatches'));
					_resources.popups['acctReqPopup'].getField('actReqAccount').setValue(acctNum);
				}			
			}
		}
		
		,resetReportingUnitDropDown: function(newValue, oldValue)
		{
			if (newValue != oldValue){
				_resources.popups['filingReqPopup'].getField('filReqReportFFI').reset();
				_resources.popups['filingReqPopup'].getField('filReqReportFFI').getStore().removeAll();
			}
		}
		
		,selectReportFile: function(rptFile)
		{
			var listName = null;
			var asOfDate = _resources.popups['filingReqPopup'].getField('filReqAsofDate').getDisplayDateString();
			
			// Report File: 01 - ALL, 02 - Single FFI, 03 - Single Report Unit			
			if (rptFile == _REPORTFILE_All){
				_resources.popups['filingReqPopup'].getField('filReqReportFFI').disableField();
				// Clear previously validation (in case selecting Report File as 02,03 and not select Reporting Unit)
				_resources.popups['filingReqPopup'].getField('filReqReportFFI').clearInvalid();			
			}
			else if (rptFile == _REPORTFILE_SingleRFFI){
				listName = _REPORTINGFFI;
			}
			else if (rptFile == _REPORTFILE_SingleUnit){
				listName = _REPORTINGUNIT;
			}
			
			// No need to call service if reporting file hasn't been selected yet
			if (rptFile != _BLNK)
			{
				// Call init service with As Of Date			
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);
				IFDS.Xml.addSingleNode(dataXML, 'asOfDate', DesktopWeb.Util.getSMVDateValue(asOfDate));
				
				DesktopWeb.Ajax.doSmartviewAjax(_dtFATCARptInitService, null, dataXML, responseHandler, _translationMap['Loading']);	

				function responseHandler(success, responseXML)
				{
					if (success)
					{
						// Handle response
						_FATCARptInitXML = IFDS.Xml.cloneDocument(responseXML);
						
						// Check if there is any effective Reporting RFFI/Unit returned
						var isEffRptRFFIListReturned = IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = '" + _REPORTINGFFI + "']/Element");
						var isEffRptUnitListReturned = IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = '" + _REPORTINGUNIT + "']/Element");
						
						// Clear previously validation & erro flag at AsOfDate field
						_resources.popups['filingReqPopup'].getField('filReqAsofDate').clearInvalid();	
						_self.isErrorOfEffRptListByAsOfDate = false;
				
						if ( (rptFile == _REPORTFILE_SingleRFFI && isEffRptRFFIListReturned) ||
							 (rptFile == _REPORTFILE_SingleUnit && isEffRptUnitListReturned) ||
							 (rptFile == _REPORTFILE_All && (isEffRptRFFIListReturned || isEffRptUnitListReturned) )
						    )
						{
							if (listName != null){
								populateDropdownListReporting(listName);
							}
						}else{
							// Enable & Disable drop down as per their usual behavior
							if (rptFile == _REPORTFILE_All){
								_resources.popups['filingReqPopup'].getField('filReqReportFFI').disableField();
							}
							else{
								_resources.popups['filingReqPopup'].getField('filReqReportFFI').enableField();
							}
							
							// Display an error message dialog
							DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("ERR_REPORTUNIT_IS_STOPPED"));
							
							// Assign flag to identify an error (to be validate in resource file again before closing popup)
							_self.isErrorOfEffRptListByAsOfDate = true;
						}
					}else{
						disableScreen();
					}			
				}
			}
		}
		
		,checkedGenOutput: function(checked)
		{
			var submissionNode = getSelectedSubmissionNode();
			var selectedSub = _resources.grids['submissionGrid'].getSelectedRecord();
			var originalAction = selectedSub.data['action'];
			
			if (submissionNode != null) //found Submission nodes in XML
			{
				if (checked) 
				{	
					_genOutput = 'yes';
					
					if(selectedSub.data['countryOfDomicile'] == '*')
					{
						sendValidation();
					}else{
						// #1 update flag to XML
						setNodeValue('genOutput', 'yes', submissionNode);
						// #2 update flag to grid
						selectedSub.data['genOutput'] = 'yes';				
						// #3 if user only selects genOutput flag and no other actions; assign action = MOD
						if (selectedSub.data['action'] == _BLNK)
						{
							setNodeValue('action', _MOD, submissionNode);
						}
						
						_self.updatesFlag = true;
					}
				}
				else{
					_genOutput = 'no';

					// #1 update flag to XML
					setNodeValue('genOutput', 'no', submissionNode);			
					// #2 update flag to grid
					selectedSub.data['genOutput'] = 'no';
					// #3 if user only de-selects genOutput flag and no other actions; assign action back to previous one
					setNodeValue('action', originalAction, submissionNode);
					
					// Check if any action changes with selected submission
					if (selectedSub.data['action'] == _BLNK){
						_self.updatesFlag = false;
					}
				}
			}
			
			// validate run test all
			function sendValidation()
			{
				// build parameter xml
				var dataXML = IFDS.Xml.newDocument('data');
				var submissionXML = IFDS.Xml.addSingleNode(dataXML, 'Submission');
				
				IFDS.Xml.addSingleNode(submissionXML, 'action', selectedSub.data['actionSub']); // add,mod,del,adj
				IFDS.Xml.addSingleNode(submissionXML, 'FATCARptMstrUUID', selectedSub.data['FATCARptMstrUUID']);
				IFDS.Xml.addSingleNode(submissionXML, 'origFATCARptMstrUUID', selectedSub.data['origFATCARptMstrUUID']);
				IFDS.Xml.addSingleNode(submissionXML, 'FATCACode', selectedSub.data['FATCACode']);
				IFDS.Xml.addSingleNode(submissionXML, 'FILevel', selectedSub.data['FILevel']);
				IFDS.Xml.addSingleNode(submissionXML, 'FICode', selectedSub.data['FICode']);			
				IFDS.Xml.addSingleNode(submissionXML, 'taxYear', selectedSub.data['taxYear']);
				IFDS.Xml.addSingleNode(submissionXML, 'asOfDate', DesktopWeb.Util.getSMVDateValue(selectedSub.data['asOfDate']));
				IFDS.Xml.addSingleNode(submissionXML, 'TPSDeff', DesktopWeb.Util.getSMVDateValue(selectedSub.data['TPSDeff']));
				IFDS.Xml.addSingleNode(submissionXML, 'submissionType', selectedSub.data['submissionType']);
				IFDS.Xml.addSingleNode(submissionXML, 'submissionSeq', selectedSub.data['submissionSeq']);
				IFDS.Xml.addSingleNode(submissionXML, 'runMode', selectedSub.data['runMode']); // Test,Production
				IFDS.Xml.addSingleNode(submissionXML, 'rptFile', selectedSub.data['rptFile']);
				IFDS.Xml.addSingleNode(submissionXML, 'version', selectedSub.data['version']);
				IFDS.Xml.addSingleNode(submissionXML, 'runDate', DesktopWeb.Util.getSMVDateValue(selectedSub.data['runDate']));
				IFDS.Xml.addSingleNode(submissionXML, 'stat', selectedSub.data['msgStat']);
				IFDS.Xml.addSingleNode(submissionXML, 'countryOfDomicile', selectedSub.data['countryOfDomicile']);
				IFDS.Xml.addSingleNode(submissionXML, 'reptFFIChange', selectedSub.data['reptFFIChange']);
				IFDS.Xml.addSingleNode(submissionXML, 'genOutput', _genOutput);
				
				IFDS.Xml.addSingleNode(submissionXML, 'RptUnits');
				
				/***** call service ******/
				
				 DesktopWeb.Ajax.doSmartviewAjax(_dtFATCARptValService, null, dataXML, responseHandler, _translationMap['Validating']);
			
				function responseHandler(success, responseXML, contextErrors, contextWarnings)
				{
					if(success)
					{
						// #1 update flag to XML
						setNodeValue('genOutput', 'yes', submissionNode);
						// #2 update flag to grid
						selectedSub.data['genOutput'] = 'yes';				
						// #3 if user only selects genOutput flag and no other actions; assign action = MOD
						if (selectedSub.data['action'] == _BLNK)
						{
							setNodeValue('action', _MOD, submissionNode);
						}
						
						_self.updatesFlag = true;
					}
					else
					{
						_genOutput = 'no';
						_resources.fields['genOutput'].setValue(false);
					}
				}
			}
		}	
		
		,loadEntityName: function(account)
		{
			searchAssignVal();
			_nextStartRecNum = 1;
			
			if (account != _BLNK)
			{
				_currentSearch['acct'] = account;
				
				// Call dosearch to retrive Entity List by account
				doSearch(_RUNMODE_RELOADEnt, false);				
			}
		}
		
		,validateSubmissionPopupByRunMode: function(runMode)
		{
			var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
			var popupSubmission = _resources.popups['filingReqPopup'];
			
			if (runMode == _RUNMODE_Test) // Run Mode: Test
			{
				if (selectedSubmission.data['submissionType'] != _ORG) // Adjustment case
				{
					// Disable all fields for Run Mode = Test
					popupSubmission.disableAllFields();
					
					if (selectedSubmission.data['stat'] == _MSGSTAT_Pending) // Pending
					{
						popupSubmission.getField('filReqSubmission').enableField();
					}
					else if (selectedSubmission.data['stat'] == _MSGSTAT_Processed) // Processed
					{
						popupSubmission.getField('filReqRunMode').enableField();
					}
				}
				else{
					// Enable all fields for Run Mode = Test
					popupSubmission.enableAllFields();
						
					if (selectedSubmission.data['stat'] == _MSGSTAT_Pending) // Pending
					{							
						popupSubmission.getField('filReqSubmission').disableField();	
						popupSubmission.getField('filReqRunMode').disableField();										
					}
					else if (selectedSubmission.data['stat'] == _MSGSTAT_Processed) // Processed
					{
						popupSubmission.getField('filReqSubmission').disableField();
					}
				}
			}
			else{ //Run Mode: Production
				popupSubmission.disableAllFields();
				popupSubmission.getField('filReqRunMode').enableField();							
			}									
		}
		
		,toFilterSubmissionTypeOfAdjustment: function (action, submissionType)
		{
			if (action == _MOD && submissionType != _ORG)
			{
				// Remove ORG-Original from Submission List ONLY when modify Submission level of adjustment
				var store = _resources.popups['filingReqPopup'].getField('filReqSubmission').getStore();
				store.removeAt(store.findExact('code', _ORG));			
			}
			else{ // add, mod of others submission types, del
				_resources.popups['filingReqPopup'].getField('filReqSubmission').loadData(IFDS.Xml.getNode(_FATCARptInitXML, "//List[@listName = 'submissionType']"));
			}
		}
		
		,loadReportingRFFIList: function()
		{
			searchAssignVal();
			_nextStartRecNum = 1;
			
			// Call Inq service to get list of RFFI/Unit when adjustment
			doSearch(_RUNMODE_RELOADRFFI, false);
		}

		,doUpdateSubmission: function(data, action)
		{
			if (action == _self.ADD)
			{					
				addSubmissionToXML(data, action);
				updateSubmissionToGrid(data, action);
			}
			else // MOD & DEL
			{
				/**
					Additional tags of Submission
					Tag#1 action
					Tag#2 origFATCARptMstrUUID
					Tag#3 genOutput
				**/			
				var submissionNode = getSelectedSubmissionNode();
				setNodeValue('action', data['actionSub'], submissionNode);
				setNodeValue('origFATCARptMstrUUID', data['origFATCARptMstrUUID'], submissionNode);
				var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
				setNodeValue('genOutput', selectedSubmission.data['genOutput'], submissionNode);
				
				if (action == _self.MOD)
				{
					updateSubmissionToXML(data, action);
					updateSubmissionToGrid(data, action);
				}
				else if (action == _self.DEL)
				{
					deleteSubmissionFromXML(data, action);
					updateSubmissionToGrid(data, action);
				}
			}
			
			_resources.popups['filingReqPopup'].hide();
		}

		,doUpdateRptUnitParent: function(data, action)
		{
			if (action == _self.ADJ)
			{
				// #1 Create Submission Level by copying from original
				addSubmissionToXML(data, action);
				updateSubmissionToGrid(data, action);
			}
		}
		
		,doUpdateRptUnitChild: function (data, action)
		{
			if (action == _self.ADJ)
			{
				// #2 Create Reporting Unit Level by copying from original (both Reporting RFFI & Reporting Unit cases)	

				// Clone a new data for each dummy(s) RFFI
				var newData = cloneObject(data);
				
				addRptUnitToXML(newData, action);
				updateRptUnitToGrid(newData, action);

				_resources.popups['adjustPopup'].hide();
				
				function cloneObject(object)		
				{
					var temp = object.constructor();
					for (var key in object){
						temp[key] = object[key];
					}
					return temp;
				}
			}
		}
		
		,doUpdateSlip: function(data, action)
		{
			// #1 Submission Level : update action between ADJ & UNCG & MOD (genOutput is selected)
			if (data['actionSub'] == _UNCG && _genOutput == 'yes'){
				data['actionSub'] = _MOD;
			}
			var submissionNode = getSelectedSubmissionNode();
			setNodeValue('action', data['actionSub'], submissionNode);
			
			// Update Msg Status if any changes (Case: Amendment & Test & Processed)
			var selectedSub = _resources.grids['submissionGrid'].getSelectedRecord();
			if (data['msgStat'] != selectedSub.data['stat'])
			{
				// update flag to XML
				setNodeValue('stat', data['msgStat'], submissionNode);
				// update flag to grid
				selectedSub.data['stat'] = data['msgStat'];
				selectedSub.commit();
			}
					
			// #2 Reporting Unit Level : update action between ADJ & UNCG
			var rptUnitNode = getSelectedRptUnitNode();
			setNodeValue('action', data['actionRpt'], rptUnitNode);
			
			// #3 Slip Level
			if (action == _self.ADD)
			{
				addSlipToXML(data, action);
				updateSlipToGrid(data, action);				
			}
			else // MOD & DEL
			{
				/**
					Additional tags of Slip
					Tag#1 action
					Tag#2 submissionType
				**/
				var slipNode = getSelectedSlipNode();
				setNodeValue('action', data['actionSlip'], slipNode);
				setNodeValue('submissionType', data['submissionType'], slipNode);
			
				if (action == _self.MOD)
				{
					updateSlipToXML(data, action);
					updateSlipToGrid(data, action);
				}
				else if (action == _self.DEL)
				{
					deleteSlipFromXML(data, action);
					updateSlipToGrid(data, action);	
				}
			}
			
			_resources.popups['acctReqPopup'].hide();
		}
		
		,getDisplayNumberWithError: function (errType, numberVal, record)
		{
			var selectedSub = _resources.grids['submissionGrid'].getSelectedRecord();
			var errorNodes = null;

			switch (errType) {
				case 'rptUnit':
					errorNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSub.data['FATCARptMstrUUID'] + "']/RptUnits/RptUnit[FATCARptFileDetlUUID='" + record.data['FATCARptFileDetlUUID'] + "']/ErrMsgID/ErrMsg");
					break;
				case 'rffi':
					errorNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSub.data['FATCARptMstrUUID'] + "']/RptUnits/RptUnit[FATCARptFileDetlUUID='" + record.data['FATCARptFileDetlUUID'] + "']/ErrDocRefID/ErrMsg");
					break;
				case 'slip':
					var selectedRptUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();

					// Slip Full View inquiry records haven't been added to FullXML; needs to find an error from inquiry xml itself.
					if (_isSlipFullView){
						errorNodes = IFDS.Xml.getNodes(_slipFullViewXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSub.data['FATCARptMstrUUID'] + "']/RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedRptUnit.data['FATCARptFileDetlUUID'] + "']/Slips/Slip[FATCARptSlipUUID='" + record.data['FATCARptSlipUUID'] + "']/ErrSlipMsg/ErrMsg");
					}else{
						errorNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + selectedSub.data['FATCARptMstrUUID'] + "']/RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedRptUnit.data['FATCARptFileDetlUUID'] + "']/Slips/Slip[FATCARptSlipUUID='" + record.data['FATCARptSlipUUID'] + "']/ErrSlipMsg/ErrMsg");					
            
						// For support submission record 'All'
						if(!errorNodes || errorNodes.length <= 0 && selectedSub.data['FATCACode'] == this.CRS)
						{
							var parentSub = IFDS.Xml.getNode(_fullXML,"//Submissions/Submission[countryOfDomicile='*']");
							if(parentSub)
							{
							if(IFDS.Xml.getNodeValue(parentSub,'taxYear') == selectedSub.data['taxYear']){
							  errorNodes = IFDS.Xml.getNodes(_fullXML, "//Submissions/Submission[FATCARptMstrUUID='" + IFDS.Xml.getNodeValue(parentSub,'FATCARptMstrUUID') + "']/RptUnits/RptUnit[FATCARptFileDetlUUID='" + selectedRptUnit.data['FATCARptFileDetlUUID'] + "']/Slips/Slip[FATCARptSlipUUID='" + record.data['FATCARptSlipUUID'] + "']/ErrSlipMsg/ErrMsg");					
							}
						  }
						}
					}
					break;
			}
			if ( !errorNodes || errorNodes.length <= 0 ){
				return numberVal;
			}else{			
				var errMsg = "- " + replaceInvalidXMLChar(IFDS.Xml.getNodeValue(errorNodes[0], "text"));
				
				for ( var i = 1; i < errorNodes.length; i++ )
				{
					errMsg += "<br/>- " + replaceInvalidXMLChar(IFDS.Xml.getNodeValue(errorNodes[i], "text"));
				}
				
				return "<font style='vertical-align:top'>" + numberVal + "</font>" + buildErrorSmallFlag(errMsg);
			}
			
			function buildErrorSmallFlag(msg)
			{
				return '<div style="position:absolute; right: 5px;">' + buildErrorFlag(msg) + '</div>'
			}
		}	

		,doUpdate: function()
		{
			var updateStatus = null;
			_updateXML = buildUpdateXML();
			DesktopWeb.Ajax.doSmartviewUpdate(_dtFATCARptProcService, null, IFDS.Xml.cloneDocument(_updateXML), responseHandler, _translationMap['ProcMsg_Saving']);			
			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}else{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}
        
        ,validateSlips: function()
        {
            var isValid = true;
            var selectedSubmission = _resources.grids['submissionGrid'].getSelectedRecord();
            var selectedRptUnit = _resources.grids['reportingUnitGrid'].getSelectedRecord();
            var slipGrd = _resources.grids['slipGrid'];
                        
            if (selectedSubmission != null && 
                selectedSubmission.data['submissionType'] == _AMD &&
                selectedRptUnit != null) {
                
                var numOfAllSlips   = slipGrd.getStore().getCount();
                var numOfCanclSlips = slipGrd.getStore().query('submissionType', _CAN).getCount();
                var numOfAmndSlips  = slipGrd.getStore().query('submissionType', _AMD).getCount();

                if ((numOfCanclSlips > 0 && numOfCanclSlips != numOfAllSlips) ||
                    (numOfAmndSlips > 0 && numOfAmndSlips != numOfAllSlips)) {
                    
                    isValid = false;
                    DesktopWeb.Util.displayError(_translationMap['ERR_MIXING_SUBMISSION_TYPE']);
                    selectedRptUnit.data['errMsg'] = _translationMap['ERR_MIXING_SUBMISSION_TYPE'];
                    _resources.grids['reportingUnitGrid'].getView().refreshRow(selectedRptUnit);
                }
            }
           
            return isValid;
        }
	}	
}	