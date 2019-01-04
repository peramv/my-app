/*********************************************************************************************
 * @file	RegAcctExtr.Controller.js
 * @author	Matira Thanetkulabut
 * @desc	Controller JS file for Reportable Accounts Extract screen
 *********************************************************************************************/
/*
 *	Navigate: Menu > System Maintenance > Reportable Accounts Extract
 *
 *	History : 
 *
 *	20-Nov-2017 Matira Thanetkulabut P0268205-34 FATCA-CRS Enhancement 18.2
 *				- Initial
 *
 *	08-Dec-2017 Matira Thanetkulabut P0268205-60 FATCA-CRS 18.2 QV2
 *				- Approve, detail functionality and fix some issues
 *
 *	25-Dec-2017 Matira Thanetkulabut P0268205-88 DFT0079829
 *				- Display Error message
 *
 *	09-Jan-2018 Matira Thanetkulabut P0268205-108 DFT0080147
 *				- Fix logic to enable/disable approve button
 *
 *	22-Jan-2018 Matira Thanetkulabut P0268206-125
 *				- Move Add, Refresh, Correct, Suppress, UnSuppress functionalities to Review screen
 *
 *	07-Feb-2018 Matira Thanetkulabut P0268206-130 DFT0081020
 *				- Support new request status "Correction Pending"
 *
 *	26-Feb-2018 Matira Thanetkulabut P0268205-171 DFT0081854
 *				- Support main library changed
 *
 *  14-Mar-2018 Matira Thanetkulabut P0268206-161 DFT0082239
 *				- Display error/warning flag at Account level to indicate that on sub-level has some error/warning
 *
 *	19-Mar-2018 Matira Thanetkulabut P0268206-179 DFT0082646
 *				- Loading reporting year's list
 *
 *	06-Sep-2018 Sadia Imtiaz P0277568-274 DFT0085998
 *				- Hard error issue on after "More" button is clicked in reportable account extract
 */
 
DesktopWeb.ScreenController = function(){

	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _RUNMODE_INIT 			= 'init';
	var _RUNMODE_RELOAD 		= 'reload';
	var _RUNMODE_ACCT_RELOAD 	= 'reloadRegExtrAcct';
	var _RUNMODE_RFI_RELOAD 	= 'reloadRegExtrRFI';
	var _RUNMODE_DETL_RELOAD 	= 'reloadExtrDetl';
	
	var _ADD 	 = 'addMstr';
	var _MOD 	 = 'modMstr';
	var _DEL 	 = 'delMstr';
	var _INQ 	 = 'inq';
	var _EXT 	 = 'ext';
	var _APR 	 = 'apr';
	var _BLNK 	 = '';
	var _ADDBTN = 'addBtn';
	var _MODBTN = 'modBtn';
	var _DELBTN = 'delBtn';
	var _DTLBTN = 'detlBtn';
	var _EXTRBTN = 'extractBtn';
	var _APVBTN = 'approveBtn';
	var _REVBTN = 'reviewBtn';
	var _RFIBTN = 'rfiDetlBtn';
	
	var _ignoreErrorCode = null;
	
	var _nextUUID = 1;
	var _nextStartRecNum 	  = 1;
	var _requestRecNum 		  = 25;
	
    var _dtRegAcctExtrInqService = "dtRegAcctExtrInq";
    var _dtRegAcctExtrUpdService = "dtRegAcctExtrProc";
	
	var _defaultValues	= new Array();
	var _currentSearch	= new Array();
	var _permissions	= new Array();
	var _extractStat	= new Array();
	
	var _initXML = null;
	var _fullXML = null;
	var _regMstrXML = null;
	var _rptAcctXML = null;
	var _rfiXML = null;
	var _detlXML = null;
	var _updatedXML = null;
	
	
    // PRIVATE METHODS ****************************************	
	function initResourceName()
	{
		_extractStat['ExtractPending']		= "EPEND";
		_extractStat['ExtractScheduled']	= "ESCHD";
		_extractStat['ExtractProcessed']	= "EPRSD";
		_extractStat['FilingScheduled']		= "FSCHD";
		_extractStat['FilingProcessed']		= "FPRSD";
		_extractStat['CorrectionPending']	= "CPEND";
	}
	
	function storePermissions(initViewXML)
	{
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
		
		if(IFDS.Xml.getNodeValue(initViewXML, '//Permissions/extPerm')){
			_permissions[_self.EXT] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/extPerm').toLowerCase() == 'yes';
		}else{
			_permissions[_self.EXT] = _permissions[_self.ADD];
		}
		
		if(IFDS.Xml.getNodeValue(initViewXML, '//Permissions/aprPerm')){
			_permissions[_self.APR] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/aprPerm').toLowerCase() == 'yes';
		}else{
			_permissions[_self.APR] = _permissions[_self.ADD];
		}
	}
	
	
	function populateDropdownList()
	{
		try{
			// Regulation
			_resources.fields['regulationFld'].loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'regulations']"));
			_resources.popups['snapReqPopup'].getField('filReqRegulation').loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'regulations']"));
			
			// Status
			_resources.fields['extractStatFld'].loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'extractStat']"));
			
        }catch(err){
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen()});
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
			_defaultValues['extractStatFld'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'extractStat');
			
			loadDropdownByRegulation(_defaultValues['regulationFld'],'init');
			_resources.fields['regulationFld'].setValue(_defaultValues['regulationFld']);
			_resources.fields['reportingYearFld'].setValue(_defaultValues['reportingYearFld']);
			_resources.fields['rfiDomicileFld'].setValue(_defaultValues['rfiDomicileFld']);
			_resources.fields['extractStatFld'].setValue(_defaultValues['extractStatFld']);
		}catch(err){
			DesktopWeb.Util.displayError("Cannot load defaultValues", function(){disableScreen();});
		}
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
			var popup = _resources.popups['snapReqPopup'];
			
			// Tax Year
			popup.getField('filReqreportingYear').reset();
			popup.getField('filReqreportingYear').loadData(IFDS.Xml.getNode(node, "//regulations/regulation[@code='" + regCode + "']/List[@listName = 'reportingYear']"));
			popup.getField('filReqreportingYear').setValue(IFDS.Xml.getNodeValue(node, "//regulations/regulation[@code='" + regCode + "']/reportingYear"));		
			
			// RFIDomicile
			popup.getField('filReqRFIDomicile').reset();
			popup.getField('filReqRFIDomicile').loadData(IFDS.Xml.getNode(node, "//regulations/regulation[@code='" + regCode + "']/List[@listName = 'RFIDomiciles']"));
			
		}
	}
	
	function init(res)
	{	
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;
		initResourceName();
		
		// Call init service
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtRegAcctExtrInqService, null, dataXML, responseHandler, _translationMap['Loading']);
		
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
					
					// enable button
					if (_permissions[_self.ADD]){
						_resources.buttons[_ADDBTN].enable();
					}
					
					// Load Default Values
					loadDefaultValues(responseXML);
					
					// Call reload service with default
					_ignoreErrorCode = {ignoreErrorCode: '15'};
					clickHandleDetl_searchBtn();
					_ignoreErrorCode = null;
				}else{
					DesktopWeb.Util.displayError("User is not allowed to access screen", function(){disableScreen();});
				}
			}else{
				DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();})
			}
		}	
	}
	
	function clickHandleDetl_searchBtn()
	{
		if (validateSearchCriteria()){
			searchAssignVal();
			clearGrid('regulation');
			clearGrid('reportAccts');
			clearGrid('RFIs');
			updateActionButtons('regulation',null);	
			doSearch(_RUNMODE_RELOAD, false, null);
		}
	}
	
	function clickHandleDetl_extractBtn(action)
	{
		doExtract(action);
	}
	
	function clickHandleDetl_detlBtn()
	{
		var selected = _resources.grids['regulation'].getSelectedRecord();
		doSearch(_RUNMODE_DETL_RELOAD, false, selected);
		openActionPopup("detailPopup");
	}
	
	function clickHandleDetl_genBtn(action,data)
	{
		genReport(action,data);
	}
	
	function clickHandleDetl_moreBtn()
	{
		var selectedRegulation = _resources.grids['regulation'].getSelectedRecord();
		doSearch(_RUNMODE_ACCT_RELOAD, true, selectedRegulation);
	}
	
	function validateSearchCriteria()
	{
		_resources.fields['regulationFld'].clearInvalid();
		_resources.fields['reportingYearFld'].clearInvalid();
		_resources.fields['rfiDomicileFld'].clearInvalid();
		_resources.fields['extractStatFld'].clearInvalid();

		var valid = _resources.fields['regulationFld'].isValid();
		valid = _resources.fields['reportingYearFld'].isValid() && valid;
		valid = _resources.fields['rfiDomicileFld'].isValid() && valid;
		valid = _resources.fields['extractStatFld'].isValid() && valid;
		
		return valid;
	}
	
	function searchAssignVal()
	{
		if(DesktopWeb._SCREEN_PARAM_MAP['prevScreen']){
			_resources.fields['regulationFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['regulationFld']);
			loadDropdownByRegulation(DesktopWeb._SCREEN_PARAM_MAP['regulationFld'],'init');
			_resources.fields['reportingYearFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['reportingYearFld']);
			_resources.fields['rfiDomicileFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['rfiDomicileFld']);
			_resources.fields['extractStatFld'].setValue(DesktopWeb._SCREEN_PARAM_MAP['extractStatFld']);
			DesktopWeb._SCREEN_PARAM_MAP['prevScreen'] = null;
		}

		_currentSearch['regulationFld'] = _resources.fields['regulationFld'].getValue();
		_currentSearch['reportingYearFld'] = _resources.fields['reportingYearFld'].getValue();
		_currentSearch['rfiDomicileFld'] = _resources.fields['rfiDomicileFld'].getValue();
		_currentSearch['extractStatFld'] = _resources.fields['extractStatFld'].getValue();
	}
	
	function doSearch(runMode, append, record)
	{
		if(runMode == _RUNMODE_RELOAD){
			// build parameter xml when search
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
			IFDS.Xml.addSingleNode(dataXML, 'regulation', _currentSearch['regulationFld']);
			IFDS.Xml.addSingleNode(dataXML, 'reportingYear', _currentSearch['reportingYearFld']);
			IFDS.Xml.addSingleNode(dataXML, 'domicileCntry', _currentSearch['rfiDomicileFld']);		
			IFDS.Xml.addSingleNode(dataXML, 'extractStat', _currentSearch['extractStatFld']);
		}else if(runMode == _RUNMODE_ACCT_RELOAD || runMode == _RUNMODE_RFI_RELOAD || runMode == _RUNMODE_DETL_RELOAD){
			// build parameter xml
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
			IFDS.Xml.addSingleNode(dataXML, 'regExtrMstrUUID', record.data['regExtrMstrUUID']);
			IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?_nextStartRecNum:1);
			IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);
			
			var regulation = _resources.grids['regulation'].getSelectedRecord();
			IFDS.Xml.addSingleNode(dataXML, 'regulation', regulation.data['regulation']);
			IFDS.Xml.addSingleNode(dataXML, 'reportingYear', regulation.data['reportingYear']);
			IFDS.Xml.addSingleNode(dataXML, 'domicileCntry', regulation.data['domicileCntry']);
		}
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtRegAcctExtrInqService, _ignoreErrorCode, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
	
		function responseHandler(success, responseXML)
		{
			// handle response
			if (success){
				if(runMode == _RUNMODE_RELOAD){
					// assign (initial load) to full XML
					_regMstrXML = IFDS.Xml.cloneDocument(responseXML);
					
					// load to regulation grid
					_resources.grids['regulation'].loadData(IFDS.Xml.getNodes(_regMstrXML, '//RegExtrMstrs'));
				}else if(runMode == _RUNMODE_ACCT_RELOAD){
					if (append){
						// User clicks More button
						// refresh _rptAcctXML as it is used to verify errors later  in getDisplayNumberWithError
						_rptAcctXML = IFDS.Xml.cloneDocument(responseXML);
						_resources.grids['reportAccts'].appendData(responseXML);
						_resources.grids['reportAccts'].setSelectedRecord(_nextStartRecNum - 1);
					}else{
						// assign (initial load) to full XML
						_rptAcctXML = IFDS.Xml.cloneDocument(responseXML);
						
						// load to reportAccts grid
						_resources.grids['reportAccts'].loadData(IFDS.Xml.getNodes(_rptAcctXML, '//RegExtrAccts'));
						
						// find previous record
						if(DesktopWeb._SCREEN_PARAM_MAP['regExtrMstrUUID']){
							var recordIndex = _resources.grids['regulation'].getStore().find('regExtrMstrUUID', DesktopWeb._SCREEN_PARAM_MAP['regExtrMstrUUID']);
							if (recordIndex > -1){
								_resources.grids['regulation'].setSelectedRecord(recordIndex);
							}
							DesktopWeb._SCREEN_PARAM_MAP['regExtrMstrUUID'] = null;
						}
						
						if(_resources.grids['reportAccts'].getSelectedRecord() && DesktopWeb._SCREEN_PARAM_MAP['regExtrAcctUUID']){
							var recordIndex = _resources.grids['reportAccts'].getStore().find('regExtrAcctUUID', DesktopWeb._SCREEN_PARAM_MAP['regExtrAcctUUID']);
							if (recordIndex > -1){
								_resources.grids['reportAccts'].setSelectedRecord(recordIndex);
							}
							DesktopWeb._SCREEN_PARAM_MAP['regExtrAcctUUID'] = null;
						}
					}
					
					// control more button
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					if (_nextStartRecNum){
						_resources.buttons['moreBtn'].enable();
					}else{
						_resources.buttons['moreBtn'].disable();
					}
				}else if(runMode == _RUNMODE_RFI_RELOAD){
					// assign (initial load) to full XML
					_rfiXML = IFDS.Xml.cloneDocument(responseXML);
					// load to RFIs grid
					_resources.grids['RFIs'].loadData(IFDS.Xml.getNodes(_rfiXML, '//RegExtrRFIs'));
				}else if(runMode == _RUNMODE_DETL_RELOAD){
					// assign (initial load) to full XML
					_detlXML = IFDS.Xml.cloneDocument(responseXML);
					
					// load to grid
					_resources.popups['detailPopup'].getField('summary').loadData(IFDS.Xml.getNodes(_detlXML, '//RegExtrDetls'));
					_resources.popups['detailPopup'].getField('regExtrActHist').loadData(IFDS.Xml.getNodes(_detlXML, '//RegExtrActHists'));
				}
			}
			
			if(!_resources.grids['regulation'].getSelectedRecord()){
				updateActionButtons('regulation',null);
			}
			
			if(!_resources.grids['reportAccts'].getSelectedRecord()){
				updateActionButtons('reportAccts',null);
			}
			
			if(!_resources.grids['RFIs'].getSelectedRecord()){
				updateActionButtons('RFIs',null);
			}
			
		}
	}
	
	function doExtract(action){
		// support extract and approve modes
		var regulationRec = _resources.grids['regulation'].getSelectedRecord();
		_updatedXML = IFDS.Xml.newDocument("data");	
		
		IFDS.Xml.addSingleNode(_updatedXML, 'runMode', action);
		IFDS.Xml.addSingleNode(_updatedXML, 'regExtrMstrUUID', regulationRec.data['regExtrMstrUUID']);
		IFDS.Xml.addSingleNode(_updatedXML, 'regulation', regulationRec.data['regulation']);
		IFDS.Xml.addSingleNode(_updatedXML, 'reportingYear', regulationRec.data['reportingYear']);
		IFDS.Xml.addSingleNode(_updatedXML, 'domicileCntry', regulationRec.data['domicileCntry']);
		IFDS.Xml.addSingleNode(_updatedXML, 'TPSEffDate', DesktopWeb.Util.convertDateStringFormat(regulationRec.data['TPSEffDate'],"dmy","mdy"));
		//DesktopWeb.Util.getSMVDateValue(regulationRec.data['TPSEffDate'])
		_self.updatesFlag = true;
		DesktopWeb.Util.commitScreen();
	}
	
	function genReport(action,data){
		var regulationRec = _resources.grids['regulation'].getSelectedRecord();
		_updatedXML = IFDS.Xml.newDocument("data");	
		
		IFDS.Xml.addSingleNode(_updatedXML, 'runMode', action);
		IFDS.Xml.addSingleNode(_updatedXML, 'regExtrMstrUUID', regulationRec.data['regExtrMstrUUID']);
		IFDS.Xml.addSingleNode(_updatedXML, 'regulation', regulationRec.data['regulation']);
		IFDS.Xml.addSingleNode(_updatedXML, 'reportingYear', regulationRec.data['reportingYear']);
		IFDS.Xml.addSingleNode(_updatedXML, 'domicileCntry', regulationRec.data['domicileCntry']);
		IFDS.Xml.addSingleNode(_updatedXML, 'subRunMode', data);
		
		_self.updatesFlag = true;
		DesktopWeb.Util.commitScreen();
	}
	
	function openActionPopup(name, action)
	{
		var popup = _resources.popups[name];
		popup.show();
		popup.init(action);
	}
	
	function doUpdateRegulation(data, action)
	{
		DesktopWeb.Util.displayWarning("Do you want to continue " + _translationMap[action] + " this record ? ", callback, Ext.Msg.OKCANCEL);
		
		function callback(confirm)
		{
			if (confirm == 'ok')
			{
				addRegulationToXML(data, action)
			}
		}
	}
	
	function addRegulationToXML(data, action)
	{
		var updatedXML = IFDS.Xml.newDocument("data");
		
		IFDS.Xml.addSingleNode(updatedXML, 'runMode', action);
		IFDS.Xml.addSingleNode(updatedXML, 'regExtrMstrUUID', data['regExtrMstrUUID']);
		IFDS.Xml.addSingleNode(updatedXML, 'regulation', data['regulation']);
		IFDS.Xml.addSingleNode(updatedXML, 'reportingYear', data['reportingYear']);
		IFDS.Xml.addSingleNode(updatedXML, 'domicileCntry', data['domicileCntry']);
		IFDS.Xml.addSingleNode(updatedXML, 'TPSEffDate', data['TPSEffDate']);      
		
		DesktopWeb.Ajax.doSmartviewUpdate(_dtRegAcctExtrUpdService, null, updatedXML, responseHandler, _translationMap['ProcMsg_Saving']);
		
		function responseHandler(success, responseXML, contextErrors)
		{
			if (success){
				updateRegulationToGrid(data, action);
			}
		}
	}
	
	function updateRegulationToGrid(data, action)
	{
		switch(action)
		{
			case _ADD:
			{
				_resources.grids['regulation'].addRecord(data);
				_resources.grids['regulation'].selectLastRecord();
				break;
			}
			case _MOD:
			{
				_resources.grids['regulation'].getSelectedRecord();
				_resources.grids['regulation'].updateSelectedRecord(data);
				break;
			}
			case _DEL:
			{
				var regulationRec = _resources.grids['regulation'].getSelectedRecord();
				
				clearGrid('reportAccts');
				clearGrid('RFIs');
				
				_resources.grids['regulation'].removeSelectedRecord();
				
				// Set row selected back to next record if the 1st one is deleted
				var selectedRegulationIndex  = _resources.grids['regulation'].store.indexOf(regulationRec);
				if (selectedRegulationIndex == 0){
					setSelectedRow('regulation', selectedRegulationIndex + 1);
				}else{
					_resources.grids['regulation'].selectFirstRecord();
				}

				regulationRec.commit();
				
				break;
			}
		}
		_resources.popups['snapReqPopup'].hide();
	}
	
	function getValueByCode(listName, code){
		var valueDesc = null;
		valueDesc = IFDS.Xml.getNodeValue(_initXML, "//List[@listName = '" + listName + "']/Element[code = '" + code + "']/value");
		if (valueDesc == null || valueDesc == "")
		{
			valueDesc = IFDS.Xml.getNodeValue(_initXML, "//List[@id = '" + listName + "']/Element[code = '" + code + "']/value");
		}
		return valueDesc;
	}
	
	function setSelectedRow(gridName, index)
	{
		_resources.grids[gridName].setSelectedRecord(index);
	}
	
	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].clearSelectedRecord();
	}
	
	function storeContextErrors(errorNodes)
	{
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			var fieldName = IFDS.Xml.getNodeValue(errorNodes[i], 'fieldSource/xmlElementName');
			var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			
			if(table == 'regulation')
			{
				// Update XML
				var regulationNode = IFDS.Xml.getNode(_regMstrXML, "//regulations/regulation[regExtrMstrUUID='" + uuid + "']");
				
				updateErrMsgNode(errMsg, regulationNode, true);
				
				// Update Grid
				var recordIndex = _resources.grids['regulation'].getStore().find(fieldName, uuid);

				if (recordIndex > -1){
					var errorRecord = _resources.grids['regulation'].getStore().getAt(recordIndex);
					errorRecord.set('errMsg', errMsg);

					_resources.grids['regulation'].getStore().commitChanges(); 
				}
				
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
	
	function goToScreen(screenName,record)
	{
		var params = {};
		
		params['prevScreen'] = 'RegAcctExtr';
		params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];
		
		var selectedRegulation = _resources.grids['regulation'].getSelectedRecord();
		params['regulation'] = selectedRegulation.data['regulation'];
		params['regExtrMstrUUID'] = selectedRegulation.data['regExtrMstrUUID'];
		
		// save search criteria
		params['regulationFld'] = _currentSearch['regulationFld'];
		params['reportingYearFld'] = _currentSearch['reportingYearFld'] ;
		params['rfiDomicileFld'] = _currentSearch['rfiDomicileFld'];
		params['extractStatFld'] = _currentSearch['extractStatFld'];
		params['regExtrAcctUUID'] = record.data['regExtrAcctUUID'];
		
		if(screenName == "RegAcctInfoRev"){
			params['account'] = record.data['account'];
			params['acctType'] = record.data['acctType'];
			params['acctStat'] = record.data['acctStat'];
			
			params['reportingYear'] = selectedRegulation.data['reportingYear'] ;
			params['rfiDomicile'] = selectedRegulation.data['domicileCntry'];
			params['extractStat'] = selectedRegulation.data['extractStat'];
		}else if(screenName == "FinanInst"){
			var selectedRFI = _resources.grids['RFIs'].getSelectedRecord();
			params['From_Menu'] = selectedRFI.data['FILevel'] == "03" ? "": "Fund"; /* related to getInitService in FinanInst screen */
			params['FILevel'] = selectedRFI.data['FILevel'];
			params['FICode'] = selectedRFI.data['FICode'];
		}
		
		DesktopWeb.Util.goToScreen(screenName, params);
	}
	
	function getNewRegulationUUID()
	{
		return "TMPREGULATION" + (_nextUUID++);
	}
	
	function setSelectedRegulation(gridName,record)
	{
		if(record){
			if(gridName == "regulation"){
				clearGrid('reportAccts');
				clearGrid('RFIs');
				_ignoreErrorCode = {ignoreErrorCode: '15'};
				doSearch(_RUNMODE_ACCT_RELOAD, false, record);
				doSearch(_RUNMODE_RFI_RELOAD, false, record);
				_ignoreErrorCode = null;
			}
			updateActionButtons(gridName,record);
		}else{
			updateActionButtons(gridName,null);
		}
	}

	function updateActionButtons(gridName,record){
		if(record){
			if(gridName == "regulation"){
				switch(record.data['extractStat']){
					case _extractStat['ExtractPending']: 
					case _extractStat['ExtractProcessed']:
						// Both of EPEND and EPRCD have extract, modify and delete permission
						if (_permissions[_self.EXT]){_resources.buttons[_EXTRBTN].enable();}
						if (_permissions[_self.DEL]){_resources.buttons[_DELBTN].enable();}
						if (_permissions[_self.MOD]){_resources.buttons[_MODBTN].enable();}
						
						// Only for EPRCD
						if (record.data['extractStat'] == _extractStat['ExtractProcessed']){
							if(_permissions[_self.APR]){
								var errorNodes = IFDS.Xml.getNodes(_regMstrXML, "//RegExtrMstrs/regExtrMstr[regExtrMstrUUID='" + record.data['regExtrMstrUUID'] + "']/RegExtrErrs/ErrMsg");
								
								if (!errorNodes || errorNodes.length <= 0){
									_resources.buttons[_APVBTN].enable();
								}else{
									_resources.buttons[_APVBTN].disable();
								}
							}
							
							if(_permissions[_self.MOD]){
								_resources.buttons[_DTLBTN].enable();
							}
						}
						break;
					case _extractStat['FilingProcessed']:
					case _extractStat['CorrectionPending']:
						// Both of FPRCD and CPEND have detail permission
						if (_permissions[_self.MOD]){_resources.buttons[_DTLBTN].enable();}
					
						// Only for CPEND has approve permission
						if(record.data['extractStat'] == _extractStat['CorrectionPending'] && _permissions[_self.APR]){
							_resources.buttons[_APVBTN].enable();
						}
						break;
					
				}
			}else if(gridName == "reportAccts"){
				_resources.buttons[_REVBTN].enable();
			}else if(gridName == "RFIs"){
				_resources.buttons[_RFIBTN].enable();
			}
		}else{
			switch(gridName){
				case "regulation":
					_resources.buttons[_MODBTN].disable();
					_resources.buttons[_DELBTN].disable();
					_resources.buttons[_DTLBTN].disable();
					_resources.buttons[_EXTRBTN].disable();
					_resources.buttons[_APVBTN].disable();
					break;
				case "reportAccts":
					_resources.buttons[_REVBTN].disable();
					break;
				case "RFIs":
					_resources.buttons[_RFIBTN].disable();
					break;
			}
		}
	}
	
	function doUpdate()
	{
		var updateStatus = null;
		DesktopWeb.Ajax.doSmartviewUpdate(_dtRegAcctExtrUpdService, null, IFDS.Xml.cloneDocument(_updatedXML), responseHandler, _translationMap['ProcMsg_Saving']);
		
		function responseHandler(success, responseXML, contextErrors)
		{
			if (success){
				updateStatus = DesktopWeb._SUCCESS;
			}else{
				storeContextErrors(contextErrors);
				updateStatus = DesktopWeb._FAIL;
			}
		}
		return updateStatus;
	}
	
	function getDisplayNumberWithError(errType, numberVal, record)
	{
		var selectedSub = _resources.grids['regulation'].getSelectedRecord();
		var errorNodes = null;
		
		switch (errType) {
			case 'account':
				errorNodes = IFDS.Xml.getNodes(_rptAcctXML, "//RegExtrAccts/regExtrAcct[regExtrAcctUUID='" + record.data['regExtrAcctUUID'] + "']/RegExtrErrs/ErrMsg");
				break;
			case 'mstr':
				errorNodes = IFDS.Xml.getNodes(_regMstrXML, "//RegExtrMstrs/regExtrMstr[regExtrMstrUUID='" + record.data['regExtrMstrUUID'] + "']/RegExtrErrs/ErrMsg");
				break;
		}
	
		if ( !errorNodes || errorNodes.length <= 0 ){
			var val = record.data['hasErrorAtSubLvl'];
			return val ? buildErrorFlag("",val) : '';
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
	
	function getMsgIconPath(flag){
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
	
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,INQ: _INQ
		,EXT: _EXT
		,APR: _APR
		,extractStat: _extractStat
		,openPopup: openActionPopup
		,doUpdateRegulation: doUpdateRegulation
		,loadDropdown: loadDropdownByRegulation
		,getDesc: getValueByCode
		,doUpdate: doUpdate
		,updatesFlag: false
		,init: init
		,goToScreen: goToScreen
		,getNewRegulationUUID: getNewRegulationUUID
		,setSelected: setSelectedRegulation
		,buildErrorFlag: buildErrorFlag
		,doSearch: clickHandleDetl_searchBtn
		,doExtract: clickHandleDetl_extractBtn
		,moreDetl: clickHandleDetl_detlBtn
		,genReport: clickHandleDetl_genBtn
		,getMore: clickHandleDetl_moreBtn
		,getDisplayNumberWithError: getDisplayNumberWithError
	}  
}