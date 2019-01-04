/*********************************************************************************************
 * @file	ReportAcctReview.Controller.js
 * @author	Matira T.
 * @desc	Controller JS file for Reportable Account Review screen
 *********************************************************************************************/
/*
 *	Navigate: Menu > Account Level Maintenance > Reportable Account Review
 *
 *	History : 
 *
 *	20-Nov-2017 Matira Thanetkulabut P0268205-34 FATCA-CRS Enhancement 18.2
 *				- Initial
 *
 *	08-Dec-2017 Matira Thanetkulabut P0268205-60 FATCA-CRS 18.2 QV2
 *				- Displayed regulation on account grid
 *				- Added description for TIN Type and RFI Level
 *
 *	25-Dec-2017 Matira Thanetkulabut P0268205-88 DFT0079829
 *				- Display Error message
 *
 *	22-Jan-2018 Matira Thanetkulabut P0268206-125
 *				- Support Add, Refresh, Correct, Suppress, UnSuppress functionalities
 *
 *	05-Feb-2018 Matira Thanetkulabut P0268206-130 DFT0081020
 *				- Reportable account status Pending be replaced with "Extracted". 
 *
 *	26-Feb-2018 Matira Thanetkulabut P0268205-171 DFT0081854
 *				- Support main library changed
 *
 *	19-Mar-2018 Matira Thanetkulabut P0268206-179 DFT0082646
 *				- Loading reporting year's list
 *
 *	27-Mar-2018 Matira Thanetkulabut P0268206-183 DFT0082940
 *				- Fix issues correct and refresh buttons are enabled/disabled incorrectly
 *
 *	05-Sep-2018 Umamaheswara Rao P0277568-261 R19.1 P0277784-75
 *				- Support Add, Modify, Delete for beneficiary payments
 *
 *	08-Oct-2018 Winnie cheng P0277784-97 DFT0086561 P0277784-134 DFT0086559 19.1 QV1
 *				- Disable payType and currency fields
 *
 *  25-Oct-2018 Sadia Imtiaz P0277784-80 DFT0086561 19.1_QV3
 *				- Error image not refreshing issue after navigating back from payment screen to reportable account Info
 *
 *  20-Nov-2018 Umamaheswara Rao P0277786-25 R19.2
 *  		    - Support Admin and More functionalities 
 *              - merge R19.1 latest fixing
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _RUNMODE_INIT 			= 'init';
	var _RUNMODE_RELOAD 		= 'reload';
	var _RUNMODE_ACCT_RELOAD 	= 'reloadAcctDetl';
	
	var _ADD 	 = 'add';
	var _MOD 	 = 'mod';
	var _DEL 	 = 'del';
	var _INQ 	 = 'inq';
	
	var _ADDBTN = 'addBtn';
	var _REFRESHBTN = 'refreshBtn';
	var _CORRECTBTN = 'correctBtn';
	var _SUPRESSBTN = 'supBtn';
	
	var _initXML = null;
	var _acctXML = null;
	var _entXML = null;
	var _taxXML = null;
	var _amtXML = null;
	var _updatedXML = null;
	var _benPymtXML = null;
	
	var _nextStartRecNum 	  = 1;
	var _requestRecNum 		  = 25;
	var _moreRecordsExist = false;
	var _ignoreErrorCode = null;
	var prevScreen = false;
	var acctScreen = false;
	
	var _currentSearch	= new Array();
	var _defaultValues	= new Array();
	var _permissions	= new Array();
	var _btnPerm		= new Array();
	
	var _AcctReviewInqService = "dtRegAcctInfoRevInq";
	var _dtRegAcctExtrUpdService = "dtRegAcctExtrProc";
	var _dtBenPymtInqRequest = "dtBenPymtInq";
	var _dtBenPymtProcRequest = "dtBenPymtProc";
	
	var _PRIMARYBENEFICIARY = "07"; 
	var _SECONDBENEFICIARY = "08";
	var _PENDING = "PEND" ;
	var _nextUUID = 1;

	// PRIVATE METHODS ****************************************	
	function init(res)
	{
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;
		
		// Call init service
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);
		
		DesktopWeb.Ajax.doSmartviewAjax(_AcctReviewInqService, null, dataXML, responseHandler, _translationMap['Loading']);
		
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				// Handle response
				_initXML = IFDS.Xml.cloneDocument(responseXML);
				
				// Load permission
				storePermissions(responseXML);
				
				
				if (_permissions[_self.INQ]){
					// Load dropdown
					populateDropdownList();
					
					// Load Default Values
					loadDefaultValues(responseXML);	
					disableSearchField();					
					// enable button
					if (_permissions[_self.ADD] && !(acctScreen || prevScreen)){
						_resources.buttons[_ADDBTN].enable();
					}
					
					// Call reload service with default
					_ignoreErrorCode = {ignoreErrorCode: '15'};
					clickHandleDetl_searchBtn();
					_ignoreErrorCode = null;
				}else{
					DesktopWeb.Util.displayError("User is not allowed to access screen", function(){disableScreen();});
				}
			}else{
				DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
			}
		}	
	}
	
	function storePermissions(initViewXML)
	{
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
		
	}
	
	function populateDropdownList()
	{
		try{
			// Regulation
			_resources.fields['regulationFld'].loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'regulations']"));
			_resources.popups['addAcct'].getField('filReqRegulation').loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'regulations']"));
			
			// AccountType
			_resources.fields['acctTypeFld'].loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'acctType']"));

			// AccountStatus
			_resources.fields['statFld'].loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'acctStat']"));
        }catch(err){
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
		}
	}
	
	function loadDefaultValues(responseXML)
	{
		var defaultValuesNode = IFDS.Xml.getNode(responseXML, "//DefaultValues");
		try{
			_defaultValues['regulationFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'regulation');
			_defaultValues['reportingYearFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'reportingYear');
			_defaultValues['rfiDomicileFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'domicileCntry');
			_defaultValues['TPSEffDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'TPSEffDate'));
			_defaultValues['statFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'acctStat');
			_defaultValues['acctFld'] = "";
			_defaultValues['acctTypeFld'] = "ALL";
			
			loadDropdownByRegulation(_defaultValues['regulationFld'],'init');
			_resources.fields['regulationFld'].setValue(_defaultValues['regulationFld']);
			_resources.fields['reportingYearFld'].setValue(_defaultValues['reportingYearFld']);
			_resources.fields['rfiDomicileFld'].setValue(_defaultValues['rfiDomicileFld']);
			_resources.fields['statFld'].setValue(_defaultValues['statFld']);
			_resources.fields['acctFld'].setValue(_defaultValues['acctFld']);
			_resources.fields['acctTypeFld'].setValue(_defaultValues['acctTypeFld']);
			
			loadDropdownByRegulation(_defaultValues['regulationFld'],'popup');
			_resources.popups['addAcct'].getField('filReqRegulation').setValue(_defaultValues['regulationFld']);
		}catch(err){
			DesktopWeb.Util.displayError("Cannot load defaultValues", function(){disableScreen();});
		}
	}
	
	function searchAssignVal()
	{
		if(prevScreen){
			_resources.fields['acctFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['account']);
			_resources.fields['acctTypeFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['acctType']);
			_resources.fields['statFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['acctStat']);
			_resources.fields['regulationFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['regulation']);
			loadDropdownByRegulation(DesktopWeb._SCREEN_PARAM_MAP['regulation'],'init');
			_resources.fields['reportingYearFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['reportingYear']);
			_resources.fields['rfiDomicileFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['rfiDomicile']);
			
			var popup = _resources.popups['addAcct'];
			popup.getField('filReqReportingYear').setValue(DesktopWeb._SCREEN_PARAM_MAP['reportingYear']);
			popup.getField('filReqRFIDomicile').setValue(DesktopWeb._SCREEN_PARAM_MAP['rfiDomicile']);
			popup.getField('filReqRegulation').setValue(DesktopWeb._SCREEN_PARAM_MAP['regulation']);
		}else if(acctScreen){
			_resources.fields['acctFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		}
	
		_currentSearch['acctFld'] = _resources.fields['acctFld'].getValue();
		_currentSearch['acctTypeFld'] = _resources.fields['acctTypeFld'].getValue();
		_currentSearch['statFld'] = _resources.fields['statFld'].getValue();
		_currentSearch['regulationFld'] = _resources.fields['regulationFld'].getValue();
		_currentSearch['reportingYearFld'] = _resources.fields['reportingYearFld'].getValue();
		_currentSearch['rfiDomicileFld'] = _resources.fields['rfiDomicileFld'].getValue();
	}
	
	function loadDropdownByRegulation(regCode,mode)
	{
		var node = IFDS.Xml.getNode(_initXML, "//regulations/regulation[@code='" + regCode + "']");
		if(mode == 'init'){
			// Tax Year
			_resources.fields['reportingYearFld'].reset();
			_resources.fields['reportingYearFld'].loadData(IFDS.Xml.getNode(node, "//regulations/regulation[@code='" + regCode + "']/List[@listName = 'reportingYear']"));
			_resources.fields['reportingYearFld'].setValue(IFDS.Xml.getNodeValue(node, "//regulations/regulation[@code='" + regCode + "']/reportingYear"));
			
			// RFIDomicile
			_resources.fields['rfiDomicileFld'].reset();
			_resources.fields['rfiDomicileFld'].loadData(IFDS.Xml.getNode(node, "//regulations/regulation[@code='" + regCode + "']/List[@listName = 'RFIDomiciles']"));
		}else{
			var popup = _resources.popups['addAcct'];
			
			// Tax Year
			popup.getField('filReqReportingYear').reset();
			popup.getField('filReqReportingYear').loadData(IFDS.Xml.getNode(node, "//regulations/regulation[@code='" + regCode + "']/List[@listName = 'reportingYear']"));
			popup.getField('filReqReportingYear').setValue(IFDS.Xml.getNodeValue(node, "//regulations/regulation[@code='" + regCode + "']/reportingYear"));		
			
			// RFIDomicile
			popup.getField('filReqRFIDomicile').reset();
			popup.getField('filReqRFIDomicile').loadData(IFDS.Xml.getNode(node, "//regulations/regulation[@code='" + regCode + "']/List[@listName = 'RFIDomiciles']"));
			
		}
	}
	
	function disableSearchField()
	{
		if(DesktopWeb._SCREEN_PARAM_MAP['prevScreen']){
			prevScreen = true;
			_resources.fields['acctFld'].disable();
			_resources.fields['acctTypeFld'].disable();
			_resources.fields['statFld'].disable();
			_resources.fields['regulationFld'].disable();
			_resources.fields['reportingYearFld'].disable();
			_resources.fields['rfiDomicileFld'].disable();
			_resources.buttons['searchBtn'].disable();
			
			var popup = _resources.popups['addAcct'];
			popup.getField('filReqReportingYear').disable();
			popup.getField('filReqRFIDomicile').disable();
			popup.getField('filReqRegulation').disable();
		}else if(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']){
			acctScreen = true;
			_resources.fields['acctFld'].disable();
		}
	}
	
	function clickHandleDetl_searchBtn()
	{
		if (validateSearchCriteria()){
			searchAssignVal();
			
			clearGrid('acct');
			clearGrid('acctEnt');
			clearGrid('taxPayerJuris');
			clearGrid('balNPaym');
			
			updateActionButtons('acct',null);
			doSearch(_RUNMODE_RELOAD, false, null, null);
		}
	}
	
	function clickHandleDetl_moreBtn()
	{
		searchAssignVal();
		doSearch(_RUNMODE_RELOAD, true, null, null);
	}
	
	function clickHandleDetl_actionBtn(action)
	{
		var account = _resources.grids['acct'].getSelectedRecord();
		
		if(action == "suppress"){
			if(account.data['acctRecordStat'] == 'SPRS'){
				action = "unsuppress";
			}
		}
		
		if(account){
			_updatedXML = IFDS.Xml.newDocument("data");	
			IFDS.Xml.addSingleNode(_updatedXML, 'runMode', action);
			IFDS.Xml.addSingleNode(_updatedXML, 'regExtrAcctUUID', account.data['regExtrAcctUUID']);
			
			DesktopWeb.Ajax.doSmartviewUpdate(_dtRegAcctExtrUpdService, null, IFDS.Xml.cloneDocument(_updatedXML), responseHandler, _translationMap['ProcMsg_Saving']);
			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success){
					var regExtrAcctUUID = IFDS.Xml.getNodeValue(responseXML,"regExtrAcctUUID");
					_currentSearch['acctFld'] = account.data['account'];
					_resources.fields['acctFld'].setValue(_currentSearch['acctFld']);
					doSearch(_RUNMODE_RELOAD, false, regExtrAcctUUID, action);
				}
			}
		}
	}
	
	function validateSearchCriteria()
	{
		_resources.fields['acctFld'].clearInvalid();
		_resources.fields['acctTypeFld'].clearInvalid();
		_resources.fields['statFld'].clearInvalid();
		_resources.fields['reportingYearFld'].clearInvalid();
		_resources.fields['rfiDomicileFld'].clearInvalid();
		_resources.fields['regulationFld'].clearInvalid();

		var valid = _resources.fields['acctFld'].isValid();
		valid = _resources.fields['acctTypeFld'].isValid() && valid;
		valid = _resources.fields['statFld'].isValid() && valid;
		valid = _resources.fields['reportingYearFld'].isValid() && valid;
		valid = _resources.fields['rfiDomicileFld'].isValid() && valid;
		valid = _resources.fields['regulationFld'].isValid() && valid;
		
		return valid;
	}
	
	function getValueByCode(listName, code)
	{
		var valueDesc = "";
		valueDesc = IFDS.Xml.getNodeValue(_initXML, "//List[@listName = '" + listName + "']/Element[code = '" + code + "']/value");
		if (valueDesc == null || valueDesc == "")
		{
			valueDesc = IFDS.Xml.getNodeValue(_initXML, "//List[@id = '" + listName + "']/Element[code = '" + code + "']/value");
		}
		return valueDesc;
	}
	
	function goToScreen()
	{
		var params = {};
		params['prevScreen'] = 'ReportAcctReview';
		params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];
		
		params['account'] = _currentSearch['acctFld'];
		params['acctType'] = _currentSearch['acctTypeFld'];
		params['acctStat'] = _currentSearch['statFld'];
		
		// clear screen flag
		prevScreen = false;
		acctScreen = false;
		
		if(DesktopWeb._SCREEN_PARAM_MAP['prevScreen']){
			DesktopWeb.Util.goToScreen(DesktopWeb._SCREEN_PARAM_MAP['prevScreen'],params);
		}else{
			DesktopWeb.Util.cancelScreen();
		}
			
	}
	
	function setSelected(grid,record)
	{
		if (record) {
			if (grid == "acct") {	
				clearGrid('acctEnt');
				clearGrid('taxPayerJuris');
				clearGrid('balNPaym');
				doSearch(_RUNMODE_ACCT_RELOAD, false, record, null);
				updateActionButtons(grid,record);
			} else if(grid == "acctEnt") {
				loadToGrid("taxPayerJuris",record.data['regExtrEntityUUID']);
				var entity =_resources.grids['acctEnt'].getSelectedRecord().data['entityID'];
				var xml = IFDS.Xml.getNodeValue(_amtXML, '//regExtrAmt/entityID');
				var newRegAmtXML = IFDS.Xml.getNodes(_amtXML, "//RegExtrAmts/*");
				var _balNPayXML = IFDS.Xml.newDocument('RegExtrAmts');
				for (var i = 0; i < newRegAmtXML.length; i++) {
					if (IFDS.Xml.getNodeValue(newRegAmtXML[i], "entityID") == entity) {
						var _tempNodeXML = IFDS.Xml.cloneDocument(newRegAmtXML[i]);
						IFDS.Xml.appendNode(_balNPayXML, _tempNodeXML);
					}
				}
				_resources.grids['balNPaym'].loadData(_balNPayXML);
				if ((record.data['entityType'] == _PRIMARYBENEFICIARY || record.data['entityType'] == _SECONDBENEFICIARY)) {
					_resources.grids['acctEnt'].enableButton('paymentBtn');
				} else {
					_resources.grids['acctEnt'].disableButton('paymentBtn');
				}
			}
		} else {
			updateActionButtons(grid,null);
		}
	}
	
	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function loadToGrid(grid,UUID)
	{
		if(grid == "taxPayerJuris"){
			var nodes = IFDS.Xml.getNodes(_entXML, "//regExtrEntity[@regExtrEntityUUID = '" + UUID + "']/RegExtrJurises");
			_resources.grids[grid].clearData();
			_resources.grids[grid].loadData(nodes);
		}
	}
	
	function doSearch(runMode, append, record, action)
	{
		if(runMode == _RUNMODE_RELOAD){
			if(record && action == "account"){
				// build parameter xml after adding account
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
				IFDS.Xml.addSingleNode(dataXML, 'regExtrAcctUUID', record);
			}else{
				// build parameter xml
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
				IFDS.Xml.addSingleNode(dataXML, 'account', _currentSearch['acctFld']==''?0:_currentSearch['acctFld']);
				IFDS.Xml.addSingleNode(dataXML, 'acctType', _currentSearch['acctTypeFld']);
				IFDS.Xml.addSingleNode(dataXML, 'acctStat', _currentSearch['statFld']);
				IFDS.Xml.addSingleNode(dataXML, 'regulation', _currentSearch['regulationFld']);
				IFDS.Xml.addSingleNode(dataXML, 'reportingYear', _currentSearch['reportingYearFld']);
				IFDS.Xml.addSingleNode(dataXML, 'domicileCntry', _currentSearch['rfiDomicileFld']);
				IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?_nextStartRecNum:1);
				IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);
			}
	
		}else if(runMode == _RUNMODE_ACCT_RELOAD){
			// build parameter xml
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
			IFDS.Xml.addSingleNode(dataXML, 'regExtrAcctUUID', record.data['regExtrAcctUUID']);
		}
		
		DesktopWeb.Ajax.doSmartviewAjax(_AcctReviewInqService, _ignoreErrorCode, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
	
		function responseHandler(success, responseXML)
		{
			// handle response
			if (success){
				if(runMode == _RUNMODE_RELOAD){
					if (append){
						// User clicks More button
						_resources.grids['acct'].appendData(responseXML);
						_resources.grids['acct'].setSelectedRecord(_nextStartRecNum - 1);
					}else{
						// assign (initial load)
						_acctXML = IFDS.Xml.cloneDocument(responseXML);
						// load to  grid
						_resources.grids['acct'].loadData(IFDS.Xml.getNodes(_acctXML, '//RegExtrAccts'));
					}
					// control more button
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					_moreRecordsExist = IFDS.Xml.getNodeValue(responseXML, '//RecordRange/moreRecordsExist').toLowerCase() == 'yes';
					
					if (_nextStartRecNum){
						_resources.buttons['moreBtn'].enable();
					}else{
						_resources.buttons['moreBtn'].disable();
					}
					
					// select a last updated account
					if(action){
						_resources.grids['acct'].selectLastRecord();
					}
				}else if(runMode == _RUNMODE_ACCT_RELOAD){
					// assign (initial load)
					var _fullXML = IFDS.Xml.cloneDocument(responseXML);
					
					_entXML = IFDS.Xml.getNode(_fullXML, '//RegExtrEntities');
					_taxXML = IFDS.Xml.getNode(_fullXML, '//RegExtrJurises');
					_amtXML = IFDS.Xml.getNode(_fullXML, '//RegExtrAmts');
					
					//reload needs to preserve entity selection					
					var selectedEntity= _resources.grids['acctEnt'].getRecordIndex(_resources.grids['acctEnt'].getSelectedRecord());
					
					// load to grid
					_resources.grids['acctEnt'].loadData(_entXML);
					_resources.grids['taxPayerJuris'].loadData(_taxXML);
					_resources.grids['balNPaym'].loadData(_amtXML);
					// reselect entity if it was  previously selected before reload 
					if(selectedEntity != undefined && selectedEntity != null){
					    _resources.grids['acctEnt'].setSelectedRecord(selectedEntity);
					}
				}	
			}
			
			if(!_resources.grids['acct'].getSelectedRecord()){
				updateActionButtons('acct',null);
			}
		}
	}
	
	function getDisplayNumberWithError(errType, numberVal, record)
	{
		var selectedAcct = _resources.grids['acct'].getSelectedRecord();
		
		var errorNodes = null;
		
		switch (errType) {
			case 'account':
				errorNodes = IFDS.Xml.getNodes(_acctXML, "//regExtrAcct[@regExtrAcctUUID='" + record.data['regExtrAcctUUID'] + "']/RegExtrErrs/ErrMsg");
				break;
			case 'entity':
				errorNodes = IFDS.Xml.getNodes(_entXML, "//regExtrAcct[@regExtrAcctUUID='" + selectedAcct.data['regExtrAcctUUID'] + "']/RegExtrEntities/regExtrEntity[@regExtrEntityUUID='" + record.data['regExtrEntityUUID'] + "']/RegExtrErrs/ErrMsg");
				break;
			case 'juris':
				var selectedEnt = _resources.grids['acctEnt'].getSelectedRecord();
				errorNodes = IFDS.Xml.getNodes(_taxXML, "//regExtrAcct[@regExtrAcctUUID='" + selectedAcct.data['regExtrAcctUUID'] + "']/RegExtrEntities/regExtrEntity[@regExtrEntityUUID='" + selectedEnt.data['regExtrEntityUUID'] + "']/RegExtrJurises/regExtrJuris[@regExtrJurisUUID='" + record.data['regExtrJurisUUID'] + "']/RegExtrErrs/ErrMsg");
				break;
			case 'amount':
				errorNodes = IFDS.Xml.getNodes(_amtXML, "//regExtrAcct[@regExtrAcctUUID='" + selectedAcct.data['regExtrAcctUUID'] + "']/RegExtrAmts/regExtrAmt[@regExtrAmtUUID='" + record.data['regExtrAmtUUID'] + "']/RegExtrErrs/ErrMsg");
				break;
		}
	
		if ( !errorNodes || errorNodes.length <= 0 ){
			return numberVal;
		}else{		
			var errType = IFDS.Xml.getNodeValue(errorNodes[0], "errType");
			var indicatorFlag = "W";
			var err = "<img src='"+ DesktopWeb._SRC_PATH + getMsgIconPath(errType) + "' />";
			var errMsg = err + " " + replaceInvalidXMLChar(IFDS.Xml.getNodeValue(errorNodes[0], "text"));
			
			if(errType == "E"){	indicatorFlag = "E";}
			
			for ( var i = 1; i < errorNodes.length; i++ )
			{
				errType = IFDS.Xml.getNodeValue(errorNodes[i], "errType");
				err = "<img src='"+ DesktopWeb._SRC_PATH + getMsgIconPath(errType) + "' />";
				errMsg += '<br/>' + err + " " + replaceInvalidXMLChar(IFDS.Xml.getNodeValue(errorNodes[i], "text"));
				if(indicatorFlag == "W" && errType == "E"){	indicatorFlag = "E";}
			}
			return "<font style='vertical-align:top'>" + "." + "</font>" + buildErrorSmallFlag(errMsg, indicatorFlag);
		}
		
		function buildErrorSmallFlag(msg,flag)
		{
			return '<div style="position:absolute; left: 5px">' + buildErrorFlag(msg,flag) + '</div>'
		}
	}
	
	function buildErrorFlag(msg,flag)
	{
		return '<img qtip="' + msg + '" qclass="" src="' + DesktopWeb._SRC_PATH + getMsgIconPath(flag) + '"/>'
	}
	
	function getMsgIconPath(flag)
	{
		var path = "images/error_small.png";
		if(flag == 'W'){			
			path = "images/warning_small.png";
		}
		return path;
	}
	
	function replaceInvalidXMLChar(str)
	{
		if ((typeof(str) === 'string' || str instanceof String ) && str.trim().length > 0)
			str = str.replace(/&/g, "&amp;").replace(/>/g, "&gt;").replace(/</g, "&lt;").replace(/"/g, "&quot;").replace(/'/g,"&apos;");
		return str;
	}
	
	function disableScreen()
	{
		for (var i in _resources.fields)
		{
			_resources.fields[i].disable();
		}
		
		for (var i in _resources.buttons)
		{
			_resources.buttons[i].disable();
		}
		
		for (var i in _resources.grids)
		{
			_resources.grids[i].disable();
		}
	}
	
	function updateActionButtons(gridName,record)
	{
		if(record){
			if(gridName == "acct"){
				_btnPerm['correct'] = String(record.data['isEnableCor']).toLowerCase() == 'yes';
				_btnPerm['refresh'] = String(record.data['isEnableRef']).toLowerCase() == 'yes';
				_btnPerm['add'] = String(record.data['isEnableAdd']).toLowerCase() == 'yes';
				_btnPerm['suppress'] = String(record.data['isEnableSup']).toLowerCase() == 'yes';
				
				_resources.buttons[_REFRESHBTN].disable();
				_resources.buttons[_CORRECTBTN].disable();
				_resources.buttons[_ADDBTN].disable();
				_resources.buttons[_SUPRESSBTN].disable();
				_resources.buttons[_SUPRESSBTN].setText(_translationMap['Suppress']);
				
				if(_btnPerm['correct']){
					_resources.buttons[_CORRECTBTN].enable();
				}
				if(_btnPerm['refresh']){
					_resources.buttons[_REFRESHBTN].enable();
				}
				if(_btnPerm['suppress']){
					_resources.buttons[_SUPRESSBTN].enable();
					
					var recStatus = record.data['acctRecordStat'];
					if(recStatus == "SPRS"){
						_resources.buttons[_SUPRESSBTN].setText(_translationMap['UnSuppress']);
					}else{
						_resources.buttons[_SUPRESSBTN].setText(_translationMap['Suppress']);
					}
				}
				
				if(_btnPerm['add'] && !(acctScreen || prevScreen)){
					_resources.buttons[_ADDBTN].enable();
				}
			}
		}else{
			_resources.buttons[_REFRESHBTN].disable();
			_resources.buttons[_CORRECTBTN].disable();
			_resources.buttons[_SUPRESSBTN].disable();
		}
	}
	
	function addAccount(action, data)
	{
		if(data){
			_updatedXML = IFDS.Xml.newDocument("data");	
			IFDS.Xml.addSingleNode(_updatedXML, 'runMode', action); // valAddAcct
			IFDS.Xml.addSingleNode(_updatedXML, 'reportingYear',  data['reportingYear']);
			IFDS.Xml.addSingleNode(_updatedXML, 'regulation',  data['regulation']);
			IFDS.Xml.addSingleNode(_updatedXML, 'domicileCntry',  data['domicileCntry']);
			IFDS.Xml.addSingleNode(_updatedXML, 'accountNum',  data['account']);''
			
			DesktopWeb.Ajax.doSmartviewUpdate(_dtRegAcctExtrUpdService, null, IFDS.Xml.cloneDocument(_updatedXML), responseHandler, _translationMap['ProcMsg_Validating']);
			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success){
					IFDS.Xml.replaceSingleNode(_updatedXML, "runMode", "addAcct"); //addAcct
					DesktopWeb.Ajax.doSmartviewUpdate(_dtRegAcctExtrUpdService, null, _updatedXML, responseHandler, _translationMap['ProcMsg_Saving']);
					
					function responseHandler(success, responseXML, contextErrors)
					{
						if (success){
							_resources.popups['addAcct'].hide();
							var regExtrAcctUUID = IFDS.Xml.getNodeValue(responseXML,"regExtrAcctUUID");
							_currentSearch['acctFld'] = data['account'];
							_resources.fields['acctFld'].setValue(_currentSearch['acctFld']);
							doSearch(_RUNMODE_RELOAD, false, regExtrAcctUUID, action);
						}
					}
				}
			}
		}
	}
	
	function openActionPopup(name)
	{
		var popup = _resources.popups[name];
		popup.show();
		popup.init();
	}
	
	function loadBenPymt() 
	{
		var benpymtpopup = _resources.popups['beneficiaryPymtPopup'];
		fetchBenPymtData(false);
		benpymtpopup.getField('Account').setValue(_resources.grids['acct'].getSelectedRecord().data['account']);
		benpymtpopup.getField('entityID').setValue(_resources.grids['acctEnt'].getSelectedRecord().data['entityID']);
		benpymtpopup.getField('entityTypeTest').setValue(getValueByCode('entityType', _resources.grids['acctEnt'].getSelectedRecord().data['entityType']));
		openBenificiaryPopup("beneficiaryPymtPopup");
	}
	
	function openBenificiaryPopup(name)
    {
           var popup = _resources.popups[name];
           popup.show();
    }
	
	function fetchBenPymtData(append)
	{
		var requestXML = IFDS.Xml.newDocument('data');
		if (append) {
			IFDS.Xml.addSingleNode(requestXML, 'runMode', _RUNMODE_RELOAD);
		} else {
			IFDS.Xml.addSingleNode(requestXML, 'runMode', _RUNMODE_INIT);
		}
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrAmtUUID', "");
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrAcctUUID', _resources.grids['acct'].getSelectedRecord().data['regExtrAcctUUID']);				
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrEntityID', _resources.grids['acctEnt'].getSelectedRecord().data['entityID']);				
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrEntType', _resources.grids['acctEnt'].getSelectedRecord().data['entityType']);
    	IFDS.Xml.addSingleNode(requestXML, 'appliedTo', '');
    	IFDS.Xml.addSingleNode(requestXML, 'startRecNum', append?_nextStartRecNum:1);
    	IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _requestRecNum);				
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrAcct', _resources.grids['acct'].getSelectedRecord().data['account']);				
    	IFDS.Xml.addSingleNode(requestXML, 'regulation', _resources.grids['acct'].getSelectedRecord().data['regulation']);
    	IFDS.Xml.addSingleNode(requestXML, 'reportingYear', _resources.fields['reportingYearFld'].getValue());				
    	IFDS.Xml.addSingleNode(requestXML, 'domicileCntry', _resources.fields['rfiDomicileFld'].getValue());
    	
    	DesktopWeb.Ajax.doSmartviewAjax(_dtBenPymtInqRequest, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
		
		function responseHandler(success, responseXML) 
		{  
			if (success) {
				var res = IFDS.Xml.cloneDocument(responseXML);
				_benPymtXML = res;
	                if (append) {
	                    // User clicks More button
	                   _resources.grids['beneficiaryPymtGrid'].appendData(responseXML);
	                   _resources.grids['beneficiaryPymtGrid'].setSelectedRecord(_nextStartRecNum - 1);
	                } else {
	                    _resources.grids['beneficiaryPymtGrid'].loadData(IFDS.Xml.getNodes(_benPymtXML, '//payEntityItems'));
	                }
	        }	
			 	_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
				if (_nextStartRecNum) {
					_resources.grids['beneficiaryPymtGrid'].enableButton('morePaymentBtn');
				} else {
					_resources.grids['beneficiaryPymtGrid'].disableButton('morePaymentBtn');
				}
		}
	}
	
	function getEntityPayAmtUUID()
	{
			return "TMPENTITYPAYAMT" + (_nextUUID++);
	}
	
	function doCommitBenPymt(data,action)
	{
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(requestXML, 'regExtrAmtUUId', data['regExtrAmtUUId']);
		IFDS.Xml.addSingleNode(requestXML, 'runMode', data["runMode"]);				
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrAcct', _resources.grids['acct'].getSelectedRecord().data['account']);				
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrEntityID', _resources.grids['acctEnt'].getSelectedRecord().data['entityID']);				
    	IFDS.Xml.addSingleNode(requestXML, 'regEntType', _resources.grids['acctEnt'].getSelectedRecord().data['entityType']);
    	IFDS.Xml.addSingleNode(requestXML, 'appliedTo', '');
    	IFDS.Xml.addSingleNode(requestXML, 'FILevel', data["payPopupRFILevel"]);
    	IFDS.Xml.addSingleNode(requestXML, 'FICode', data["payPopupRFILevelDesc"]);
    	IFDS.Xml.addSingleNode(requestXML, 'domicileCntry', _resources.fields['rfiDomicileFld'].getValue());
    	IFDS.Xml.addSingleNode(requestXML, 'payType', data['payPopupPaymentType']);
    	IFDS.Xml.addSingleNode(requestXML, 'payAmount', data['payPopupAmount']);
    	IFDS.Xml.addSingleNode(requestXML, 'payCurrency', data['payPopupCurrency']);
    	IFDS.Xml.addSingleNode(requestXML, 'payRecType', '');
    	IFDS.Xml.addSingleNode(requestXML, 'regExtrAcctUUId', _resources.grids['acct'].getSelectedRecord().data['regExtrAcctUUID']);
    	
    	DesktopWeb.Ajax.doSmartviewAjax(_dtBenPymtProcRequest, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);

    	function responseHandler(success, responseXML) 
    	{
			if (success) {
				updateBeneficiaryPaymentGrid(data,action,responseXML);
				_resources.popups['payPopup'].hide();				
			} 
		}
	}
	
	function updateBeneficiaryPaymentGrid(data,action,responseXML)
	{
		switch(action)
		{
			case _ADD:
			{
				// update beneficiary payment grid on beneficiary popup
				creatNewPaymentRecord('beneficiaryPymtGrid' , data, responseXML);				
				// update payment and beneficiary table on Reportable account information frame
				creatNewPaymentRecord('balNPaym' , data, responseXML);
				_resources.grids['balNPaym'].selectLastRecord();
				
				// refresh account details to remove or update any existing or new errors on account
				doSearch(_RUNMODE_ACCT_RELOAD, false, _resources.grids['acct'].getSelectedRecord(), null);

				break;
			}
			case _MOD:
			{
				var beneficiaryPymtGrid = _resources.grids['beneficiaryPymtGrid'].getSelectedRecord();
				beneficiaryPymtGrid.data['PayAmount']= data['payPopupAmount'];
				_resources.grids['beneficiaryPymtGrid'].updateSelectedRecord(data);
				
				// update this record from balance and payment grid on reportable account view 
				var balnPaymentRecord = findExistingRecBalAndPayGrid(data['regExtrAmtUUId']);
				if(balnPaymentRecord != null)
				{
					balnPaymentRecord.each( function updateRecord(item) {
						item.data['amount'] = data['payPopupAmount'];
						_resources.grids['balNPaym'].setSelectedRecord(_resources.grids['balNPaym'].getRecordIndex(item));
						_resources.grids['balNPaym'].updateSelectedRecord(item);
						_resources.grids['balNPaym'].selectFirstRecord();
					});
				}
				
				break;
			}
			case _DEL: 
			{	
				_resources.grids['beneficiaryPymtGrid'].removeSelectedRecord();
				
                if(_resources.grids['beneficiaryPymtGrid'].store.getCount() > 0) {
                	_resources.grids['beneficiaryPymtGrid'].selectFirstRecord();
                } else {
                	handleBenPaymentBtns(null);
                }
                // delete this record from balance and payment grid on reportable account view 
                var balnPaymentRecord = findExistingRecBalAndPayGrid(data['regExtrAmtUUId']);
				if(balnPaymentRecord != null) {
					balnPaymentRecord.each( function removeRecord(item) { _resources.grids['balNPaym'] .getStore().remove(item)});
				}
				
				// refresh account details to remove or update any existing or new errors on account
				doSearch(_RUNMODE_ACCT_RELOAD, false, _resources.grids['acct'].getSelectedRecord(), null);
				
				break;
			}
		}			
	}
		
	function findExistingRecBalAndPayGrid(extAmtUID)
	{
		var record = null;
		record = _resources.grids['balNPaym'].getStore().query('regExtrAmtUUID',extAmtUID);
		return record;
	}
	
	function creatNewPaymentRecord(gridName , data, responseXML)
	{
		// new record for beneficiary payment and balance and payment grids will be created below.
		// the only difference is in the name of fields which will covered in the checks
		var newRec = {};
		newRec['allowMod'] = 'yes';
		newRec['allowDel'] = 'yes';
		newRec['errMsg'] = '';
		
		newRec['FILevel'] = data['payPopupRFILevel'];
		newRec['FICode'] =data['payPopupRFILevelDesc'];
		
		newRec[gridName=='beneficiaryPymtGrid'? 'payType' : 'amountType'] = data['payPopupPaymentType'];
		newRec[gridName=='beneficiaryPymtGrid'? 'PayAmount' : 'amount'] = data['payPopupAmount'];
		newRec[gridName=='beneficiaryPymtGrid'? 'payCurrency' : 'currency'] = data['payPopupCurrency'];
		newRec[gridName=='beneficiaryPymtGrid'? 'domicileCntry' : 'cntryCode']=IFDS.Xml.getNodeValue(responseXML,'//dtBenPymtProcResponse/domicileCntry');	
		
		newRec['regExtrAmtUUID']=IFDS.Xml.getNodeValue(responseXML,'//dtBenPymtProcResponse/regExtrAmtUUID');
		
		var rfiCombo=_resources.popups['payPopup'].getField('payPopupRFILevelDesc').getRawValue();
		newRec['FIName']=rfiCombo.substring(rfiCombo.indexOf('-')+1);

		_resources.grids[gridName].addRecord(newRec);				
		_resources.grids[gridName].selectLastRecord();
		
		return newRec;
	}
	
	function loadDropdownRFIDescription() 
	{
		var popup = _resources.popups['payPopup'];
		popup.getField('payPopupRFILevel').loadData(IFDS.Xml.getNode(_benPymtXML,"//List[@listName = 'regExtrRFILevel']"));
		popup.getField('payPopupRFILevel').setValue(IFDS.Xml.getNodeValue(_benPymtXML,"//ListSelection[@id = 'regExtrRFILevel']"));
		popup.getField('payPopupPaymentType').loadData(IFDS.Xml.getNode(_benPymtXML,"//List[@listName = 'payTypeList']"));
		popup.getField('payPopupPaymentType').setValue(IFDS.Xml.getNodeValue(_benPymtXML,"//ListSelection[@id = 'payTypeList']"));
		popup.getField('payPopupCurrency').loadData(IFDS.Xml.getNode(_benPymtXML,"//List[@id = 'currencyList']"));
		popup.getField('payPopupCurrency').setValue(IFDS.Xml.getNodeValue(_benPymtXML,"//ListSelection[@id = 'currencyList']"));
	 }
	
	function openPaymentPopup(action)
	{
		var popup = _resources.popups['payPopup'];
		popup.show();
		popup.init(action,popup);
	}
	
	function handleBenPaymentBtns(record)
	{
		if(record !='' && record != null) {			
			if(record.data['allowMod'] == 'yes') {
				_resources.grids['beneficiaryPymtGrid'].enableButton('modBtn');
			} else {
				_resources.grids['beneficiaryPymtGrid'].disableButton('modBtn');
			}
			
			if(record.data['allowDel'] == 'yes'){
				_resources.grids['beneficiaryPymtGrid'].enableButton('delBtn');
			} else {
				_resources.grids['beneficiaryPymtGrid'].disableButton('delBtn');
			}
			
			if(record.data['modDate'] == undefined  ) {
				_resources.grids['beneficiaryPymtGrid'].disableButton('adminBtn');
			} else {
				_resources.grids['beneficiaryPymtGrid'].enableButton('adminBtn');
			}
		} else {
			_resources.grids['beneficiaryPymtGrid'].disableButton('delBtn');
			_resources.grids['beneficiaryPymtGrid'].disableButton('modBtn');
			_resources.grids['beneficiaryPymtGrid'].disableButton('adminBtn');
		}
		var acctStatus = _resources.grids['acctEnt'].getSelectedRecord().data['entRecordStat'];
		if(_PENDING === acctStatus) {
			_resources.grids['beneficiaryPymtGrid'].enableButton('addBtn');
		} else {
			_resources.grids['beneficiaryPymtGrid'].disableButton('addBtn');
		}
	}

	function populateAndDisablePayPopupRFIDesc()
	{
		var comboRFI=_resources.popups["payPopup"].getField('payPopupRFILevelDesc');
        comboRFI.setValue(_resources.grids['beneficiaryPymtGrid'].getSelectedRecord().data['FICode']);
        comboRFI.setRawValue(_resources.grids['beneficiaryPymtGrid'].getSelectedRecord().data['FICode']+' - '+_resources.grids['beneficiaryPymtGrid'].getSelectedRecord().data['FIName']);
        comboRFI.selectedIndex=1;
        comboRFI.disableField();
	}
			
	function disablePayPopupFields(popup) 
    {
		popup.getField('payPopupAccountNum').disableField();
		popup.getField('payPopupEntity').disableField();
		popup.getField('payPopupEntityType').disableField();
		popup.getField('payPopupRFILevel').disable();
		popup.getField('payPopupPaymentType').disable();
		popup.getField('payPopupCurrency').disable();
		populateAndDisablePayPopupRFIDesc();
		popup.getField('payPopupAmount').disableField();
	}
	
	function enablePayPopupFields(popup) 
	{
		popup.getField('payPopupAccountNum').disableField();
		popup.getField('payPopupEntity').disableField();
		popup.getField('payPopupEntityType').disableField();
		popup.getField('payPopupRFILevel').enable();
		popup.getField('payPopupPaymentType').disable();
		popup.getField('payPopupCurrency').disable();
		popup.getField('payPopupRFILevelDesc').enableField();
		popup.getField('payPopupAmount').enableField();
	}
	
    function  openAdminPopup()
    {
        var title = null;
        title = _translationMap['BeneficiaryPayment']+ " - " +  _translationMap['Admin'];
        selectedRecord = _resources.grids['beneficiaryPymtGrid'].getSelectedRecord();
        
        if (selectedRecord != null) {
            var adminData = {};
            adminData['userName'] = selectedRecord.data['userName'];
            adminData['procDate'] = selectedRecord.data['processDate'];
            adminData['modUser'] = selectedRecord.data['modUser'];
            adminData['modDate'] = selectedRecord.data['modDate'];    
            _resources.popups['admin'].init(title, adminData);
            _resources.popups['admin'].show();
        }
	}
	
	// PUBLIC ITEMS *************************************
	return {
		init: init
		,getDesc: getValueByCode
		,goToScreen: goToScreen
		,setSelected: setSelected
		,doSearch: clickHandleDetl_searchBtn
		,loadDropdown: loadDropdownByRegulation
		,doMore: clickHandleDetl_moreBtn
		,getDisplayNumberWithError: getDisplayNumberWithError
		,doAction: clickHandleDetl_actionBtn
		,openPopup: openActionPopup
		,addAccount: addAccount 
		,loadBenPymt: loadBenPymt
		,openPaymentPopup: openPaymentPopup
		,ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,doCommitBenPymt: doCommitBenPymt
		,loadDropdownRFIDescription: loadDropdownRFIDescription
		,getEntityPayAmtUUID: getEntityPayAmtUUID
		,handleBenPaymentBtns: handleBenPaymentBtns
		,disablePayPopupFields: disablePayPopupFields
		,enablePayPopupFields: enablePayPopupFields
		,populateAndDisablePayPopupRFIDesc : populateAndDisablePayPopupRFIDesc
		,openAdminPopup: openAdminPopup
		,fetchBenPymtData: fetchBenPymtData
	}
}