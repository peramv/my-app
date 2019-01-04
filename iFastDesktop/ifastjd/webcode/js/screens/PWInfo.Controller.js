/*********************************************************************************************
 * @file	PWInfo.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Private Wealth Information screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Private Wealth Information
 *				
 *  History : 
 *
 *  23 Jul 2014 Narin S. P0233553 T55642
 *					- Created.
 *
 *  03 Sept 2014 Narin S. P0233553 T55678
 *					- Complete modify and assessment functionalities.
 *
 *  18 Sept 2014 Narin S. P0233553 DFT0041241 T55739
 *					- Always enable search value field.
 *					- Display currency and aggregated mv and bv even though 
 *						account/group are not enrolled to Private Wealth program.
 *					- Remove Group ID field from Private Wealth Information section.
 *
 *	25 Sept 2014 Narin S. P0233553 DFT0041354 T55772
 *					- Add Account Private Wealth History button
 *
 *	02 Oct 2014 Narin S. P0233553 DFT0042004 T55823
 *					- Stop Date cannot be future date.
 *
 *	09 Oct 2014 Narin S. P0233553 DFT0042265 T55852
 *					- Fix javascript error if do serach after modification Private Wealth.
 *
 *	16 Oct 2014 Narin S. P0233553 DFT0042698 T55888
 *					- Add warning message if user stops Private Wealth.
 *					- Update tag name from LinkedAccts to LnkAccts
 *
 *	28 Oct 2014 Narin S. P0233553 DFT0043383 T55939
 *					- Support Account Level
 *
 *	17 Nov 2014 Aurkarn M. P0232101 DFT0044321 T56045
 *					- Issue with private wealth screen from Account >Caution/Options >Private wealth
 *
 */
 
//Ext.QuickTips.init();
Ext.apply(Ext.QuickTips.getQuickTip(), {
    maxWidth: 1000
    ,minWidth: 500
    ,showDelay: 50
    ,trackMouse: true
});

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'add';
	var _MOD = 'mod';
	var _DEL = 'del';
	var _INQ = 'inq';
	var _ACC = 'acc';
	var _RUNMODE_INIT 		= 'init';
	var _RUNMODE_RELOAD 	= 'reload';
	var _RUNMODE_VALIDATE 	= 'val';
	var _RUNMODE_UPDATE 	= 'upd';
	
	var _initXML 	= null;
	var _PWInfoXML 	= null;
	
	var _PWInfoObj = null;
	
	var _currentSearch	= new Array();
	var _permissions	= new Array();
	var _defaultValues	= new Array();
	var _configs		= new Array();
	
	var _dtPWInfoAssessService 		= "dtPWAssessProc";
	var _dtPWInfoProcService 		= "dtPWInfoProc";
	var _dtPWInfoValidateService 	= "dtPWInfoProc";
	var _dtPWInfoInqService 		= "dtPWInfoInq";
	var _dtPWAcctHistService 		= 'dtPWAcctHistInq';
	var _dtHistoryService 			= 'dtHistoricalInfo';
	
	var _searchedFlag = false;
	
	// PRIVATE METHODS ****************************************	
	/** Store user permission **/
	function storePermissions(initViewXML)
	{
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inq').toLowerCase() == 'yes';
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/add').toLowerCase() == 'yes';
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/mod').toLowerCase() == 'yes';	
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/del').toLowerCase() == 'yes';
	}
	
	function loadConfigurations(initViewXML)
	{
		_configs['salesRepbyBranch'] = IFDS.Xml.getNodeValue(initViewXML, '//salesRepbyBranch').toLowerCase() == _self.YES;
	}
	
	function loadDefaultValues(responseXML)
	{
		var defaultValuesNode = IFDS.Xml.getNode(responseXML, "//DefaultValues");
		if (defaultValuesNode)
		{
			_defaultValues['curBusDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'curBusDate'));
			_defaultValues['graceDays'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'graceDays');
		}
		
		var defaultStopDate = new Date();
		defaultStopDate.setYear(9999);
		defaultStopDate.setMonth(11);
		defaultStopDate.setDate(31);
		
		_defaultValues['stopDate'] = DesktopWeb.Util.getDateString(defaultStopDate, DesktopWeb.Util.getDateDisplayFormat());
	}

	function populateDropdownList()
	{
		try{
			var searchForXML = IFDS.Xml.newDocument('data');
			addListElement('pwId', _translationMap['PWID'], searchForXML);
			addListElement('acct', _translationMap['AccountNumber'], searchForXML);
			addListElement('grpId', _translationMap['GroupID'], searchForXML);
			_resources.fields['searchFor'].loadData(searchForXML);
		}catch(err){
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
		}
		
		function addListElement(code, value, context){
			var eleNode = IFDS.Xml.addSingleNode(searchForXML, 'Element');
			IFDS.Xml.addSingleNode(eleNode, 'code', code);
			IFDS.Xml.addSingleNode(eleNode, 'value', value);
		}
	}
	
	function populateDefaultSearchCriteria(initViewXML)
	{
		// For Account Level
		var acctNum = DesktopWeb._SCREEN_PARAM_MAP['AccountNum']
		if (acctNum && acctNum.length > 0)
		{
			_resources.fields['searchFor'].setValue('acct');
			_resources.fields['searchValue'].setValue(acctNum);
			_resources.fields['searchFor'].disableField();
			_resources.fields['searchValue'].disableField();
						
			_currentSearch['searchFor'] = _resources.fields['searchFor'].getValue();
			_currentSearch['searchValue'] = _resources.fields['searchValue'].getValue();	
			
			doSearch(_RUNMODE_RELOAD, false);
			_resources.buttons['searchBtn'].disable();
		}
	}
	
	function doSearch(runMode, append)
	{
		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(dataXML, 'searchFor', _currentSearch['searchFor']);
		IFDS.Xml.addSingleNode(dataXML, 'searchValue', _currentSearch['searchValue']);

		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_dtPWInfoInqService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{
			// hanldle response
			if (success){
				_searchedFlag = true;
				
				_PWInfoXML = responseXML;
				
				loadPWInfoObj(IFDS.Xml.getNode(responseXML, '//PWInfo'));
				
				displayPWInfoSection();
				
				loadPWAcct(IFDS.Xml.getNode(responseXML, '//LnkAccts'));
			}else{
				_resources.buttons['PWModBtn'].disable();
				_resources.buttons['PWAssessBtn'].disable();
				_resources.buttons['PWHistoryBtn'].disable();
				_resources.buttons['PWAdminBtn'].disable();
			}
		}
	}
	
	function loadPWInfoObj(PWXML)
	{
		if (PWXML)
		{
			_PWInfoObj = new Array();
			_PWInfoObj['PWUUID'] = IFDS.Xml.getNodeValue(PWXML, 'PWUUID');
			_PWInfoObj['PWID'] = IFDS.Xml.getNodeValue(PWXML, 'PWID');
			_PWInfoObj['PWLevel'] = IFDS.Xml.getNodeValue(PWXML, 'PWLevel');
			_PWInfoObj['PWStatus'] = IFDS.Xml.getNodeValue(PWXML, 'PWStat');
			_PWInfoObj['grpId'] = IFDS.Xml.getNodeValue(PWXML, 'grpID');
			_PWInfoObj['deff'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(PWXML, 'deff'));
			_PWInfoObj['stopDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(PWXML, 'stopDate'));
			_PWInfoObj['graceStartDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(PWXML, 'graceStartDate'));
			_PWInfoObj['graceEndDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(PWXML, 'graceEndDate'));
			_PWInfoObj['lastAssessedDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(PWXML, 'lastAssessedDate'));
			_PWInfoObj['lastAssessedTime'] = IFDS.Xml.getNodeValue(PWXML, 'lastAssessedTime');
			_PWInfoObj['bv'] = IFDS.Xml.getNodeValue(PWXML, 'bv');
			_PWInfoObj['mv'] = IFDS.Xml.getNodeValue(PWXML, 'mv');
			_PWInfoObj['aggbv'] = IFDS.Xml.getNodeValue(PWXML, 'aggbv');
			_PWInfoObj['aggmv'] = IFDS.Xml.getNodeValue(PWXML, 'aggmv');
			_PWInfoObj['allowMod'] = IFDS.Xml.getNodeValue(PWXML, 'allowMod');
			_PWInfoObj['allowDel'] = IFDS.Xml.getNodeValue(PWXML, 'allowDel');
			_PWInfoObj['userName'] = IFDS.Xml.getNodeValue(PWXML, 'userName');
			_PWInfoObj['processDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(PWXML, 'processDate'));
			_PWInfoObj['modDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(PWXML, 'modDate'));
			_PWInfoObj['modUser'] = IFDS.Xml.getNodeValue(PWXML, 'modUser');
			_PWInfoObj['currency'] = IFDS.Xml.getNodeValue(PWXML, 'curr');
			_PWInfoObj['version'] = IFDS.Xml.getNodeValue(PWXML, 'version');
			
			var linkedAcctNode = IFDS.Xml.getNode(PWXML, '//LnkAccts/LnkAcct')
			_PWInfoObj['hasLinkedAcct'] = (linkedAcctNode)?true:false;
		}
	}
	
	function displayPWInfoSection()
	{
		if (_PWInfoObj)
		{
			if (_PWInfoObj['PWID'] && _PWInfoObj['PWID'].length > 0){
				_resources.fields['PWID'].setText(_PWInfoObj['PWID']);
				_resources.fields['PWLevel'].setText(_PWInfoObj['PWLevel']);
				_resources.fields['PWStatus'].setText(_PWInfoObj['PWStatus']);
				_resources.fields['deff'].setText(_PWInfoObj['deff']);
				_resources.fields['stopDate'].setText(_PWInfoObj['stopDate']);
				
				if (_PWInfoObj['graceStartDate'] && _PWInfoObj['graceStartDate'].length > 0)
				{
					_resources.fields['graceStartDate'].setText(_PWInfoObj['graceStartDate']);
					_resources.fields['graceEndDate'].setText(_PWInfoObj['graceEndDate']);
				}else{
					_resources.fields['graceStartDate'].setText(_translationMap['NA']);
					_resources.fields['graceEndDate'].setText(_translationMap['NA']);
				}
				
				_resources.fields['lastAssessedDate'].setText(_PWInfoObj['lastAssessedDate']);
				_resources.fields['lastAssessedTime'].setText(_PWInfoObj['lastAssessedTime']);
				_resources.fields['adjustCost'].setText(_PWInfoObj['bv']);
				_resources.fields['marketValue'].setText(_PWInfoObj['mv']);
			}
			_resources.fields['currency'].setText(_translationMap['Currency'] + ": " + _PWInfoObj['currency']);
			_resources.fields['aggMV'].setText(_PWInfoObj['aggmv']);
			_resources.fields['aggBV'].setText(_PWInfoObj['aggbv']);
			updatePWInfoButtons();
		}
	}
	
	function updatePWInfoButtons()
	{
		if (_PWInfoObj['PWID'] && _PWInfoObj['PWID'].length > 0){
			if (_permissions[_self.MOD] && _PWInfoObj['allowMod'].toLowerCase() == 'yes'){
				_resources.buttons['PWModBtn'].enable();
				_resources.buttons['PWAssessBtn'].enable();
			}
			if (_PWInfoObj['PWID'] && _PWInfoObj['PWID'].length > 0){
				_resources.buttons['PWHistoryBtn'].enable();
				_resources.buttons['PWAdminBtn'].enable();
			}
		}else{
			_resources.buttons['PWModBtn'].disable();
			if (_permissions[_self.MOD] && _PWInfoObj['allowMod'].toLowerCase() == 'yes' && _PWInfoObj['hasLinkedAcct']){
				_resources.buttons['PWAssessBtn'].enable();
			}else{
				_resources.buttons['PWAssessBtn'].disable();
			}
			_resources.buttons['PWHistoryBtn'].disable();
			_resources.buttons['PWAdminBtn'].disable();
		}
	}
		
	function loadPWAcct(PWAcctXML)
	{
		if (PWAcctXML)
		{
			_resources.grids['PWAcct'].loadData(PWAcctXML);
		}
	}
	
	function registerThresholdAmountTip(nodes)
	{
		if(nodes){
			var tooltip = "<div align='center'><table style='font-size:10pt; color:blue; border:1px solid;'>"
							+ "<tr style='font:bold;'><td style='padding:2px;'>Level</td>"
							+ "<td style='padding:2px;'>Lower</td>"
							+ "<td style='padding:2px;'>Upper</td>"
							+ "<td style='padding:2px;'>Currency</td></tr>";
			Ext.each(nodes, function(node){
				var level = IFDS.Xml.getNodeValue(node, 'level');
				var lower = IFDS.Xml.getNodeValue(node, 'lower');
				var upper = IFDS.Xml.getNodeValue(node, 'upper');
				var currency = IFDS.Xml.getNodeValue(node, 'currency');
				tooltip += "<tr><td style='text-align:center; padding:2px;'>" + level + "</td>"
						+ "<td style='padding:2px;'>" + lower + "</td>"
						+ "<td style='padding:2px;'>" + upper + "</td>"
						+ "<td style='text-align:center; padding:2px;'>" + currency + "</td></tr>"
			});
			tooltip += "</table></div><br/>";
			Ext.QuickTips.unregister(_resources.fields["PWLevelThreshold"].id);
			Ext.QuickTips.register({
			    target: _resources.fields["PWLevelThreshold"].id,
			    title: _translationMap['AssetLevelThreshold'],
			    text: tooltip,
			    //width: 300,
			    dismissDelay: 5000
			});
		}
	}
	
	function validateUpdatePWInfo(data, action)
	{
		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		var PWInfoXML = IFDS.Xml.addSingleNode(dataXML, 'PWInfo');
		IFDS.Xml.addSingleNode(PWInfoXML, 'runMode', _RUNMODE_VALIDATE);
		IFDS.Xml.addSingleNode(PWInfoXML, 'PWUUID', data['PWUUID']);
		IFDS.Xml.addSingleNode(PWInfoXML, 'PWID', _PWInfoObj['PWID']);
		IFDS.Xml.addSingleNode(PWInfoXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
		IFDS.Xml.addSingleNode(PWInfoXML, 'graceEndDate', DesktopWeb.Util.getSMVDateValue(data['graceEndDate']));
		IFDS.Xml.addSingleNode(PWInfoXML, 'version', _PWInfoObj['version']);
		
		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_dtPWInfoValidateService, null, dataXML, responseHandler, _translationMap['Validating']);
			
		function responseHandler(success, responseXML, contextErrors, contextWarnings)
		{
			if (success)
			{
				_self.updatesFlag = true;
				updatePWInfoObj(data);
				updatePWInfoSection();
				_resources.popups['PWInfoPopup'].hide();
			}
		}
	}
	
	function updatePWInfoObj(data)
	{
		_PWInfoObj['stopDate'] = data['stopDate'];
		_PWInfoObj['graceEndDate'] = data['graceEndDate'];
	}

	function updatePWInfoSection(data)
	{
		_resources.fields['stopDate'].setText(_PWInfoObj['stopDate']);
		
		if (_PWInfoObj['graceStartDate'] && _PWInfoObj['graceStartDate'].length > 0)
		{
			_resources.fields['graceStartDate'].setText(_PWInfoObj['graceStartDate']);
			_resources.fields['graceEndDate'].setText(_PWInfoObj['graceEndDate']);
		}else{
			_resources.fields['graceStartDate'].setText(_translationMap['NA']);
			_resources.fields['graceEndDate'].setText(_translationMap['NA']);
		}
	}

	function PWAssessment()
	{
		// build parameter xml
		var account = '';
		var grpId = '';
		var pwId = '';
		
		if (_PWInfoObj)
		{
			if (_PWInfoObj['PWID'] && _PWInfoObj['PWID'].length > 0)
			{
				pwId = _PWInfoObj['PWID'];
				grpId = _PWInfoObj['grpId']
			}else{
				var selectedLinkedAcct = _resources.grids['PWAcct'].getSelectedRecord();
				if (selectedLinkedAcct)
				{
					if (selectedLinkedAcct.data['grpID'] && selectedLinkedAcct.data['grpID'].length > 0)
					{
						grpId = selectedLinkedAcct.data['grpID'];
					}else{
						account = selectedLinkedAcct.data['acct'];
					}
					
				}
			}
		}else{
			return;
		}
		
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', 'assess');
		IFDS.Xml.addSingleNode(dataXML, 'acct', account);
		IFDS.Xml.addSingleNode(dataXML, 'grpId', grpId);
		IFDS.Xml.addSingleNode(dataXML, 'pwId', pwId);

		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_dtPWInfoAssessService, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])
        
		function responseHandler(success, responseXML)
		{
			// hanldle response
			if (success)
			{
				clearGrid('PWAcct');
				clearPWInfo();
				
				doSearch(_RUNMODE_RELOAD, false);
			}
		}
	}
	
	function updatePWAcctGridButtons(record)
	{
		_resources.grids['PWAcct'].enableButton('PWAcctHistBtn');
	}
	
	function updateShareholderName(record)
	{
		if (record)
		{
			Ext.getCmp('bb_shareholderName').setText(_translationMap['ShareholderName'] + ': ' + record.data['name']);
		}else{
			Ext.getCmp('bb_shareholderName').setText(_translationMap['ShareholderName'] + ': ');
		}
	}
	
	function clearPWInfo()
	{
		_resources.fields['PWID'].reset();
		_resources.fields['PWLevel'].reset();
		_resources.fields['PWStatus'].reset();
		_resources.fields['deff'].reset();
		_resources.fields['stopDate'].reset();
		_resources.fields['graceStartDate'].reset();
		_resources.fields['graceEndDate'].reset();
		_resources.fields['lastAssessedDate'].reset();
		_resources.fields['lastAssessedTime'].reset();
		_resources.fields['adjustCost'].reset();
		_resources.fields['marketValue'].reset();
		_resources.fields['currency'].reset();
		_resources.fields['currency'].setText(_translationMap['Currency'] + ": ");
		_resources.fields['aggMV'].reset();
		_resources.fields['aggBV'].reset();
		_PWInfoObj = null;
	}

	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
		
		if (name == 'PWAcct') updateShareholderName(null);
	}

	function disableScreen()
	{
		_resources.buttons['searchBtn'].disable();
		_resources.buttons['PWModBtn'].disable();
		_resources.buttons['PWAssessBtn'].disable();
		_resources.buttons['PWHistoryBtn'].disable();
		_resources.buttons['PWAdminBtn'].disable();
		_resources.fields['searchFor'].disable();
		_resources.fields['searchValue'].disable();
	}

	function validateSearchCriteria()
	{
		_resources.fields['searchFor'].clearInvalid();
		_resources.fields['searchValue'].clearInvalid();
		
		return _resources.fields['searchFor'].isValid()
				&& _resources.fields['searchValue'].isValid();
	}
	
	function buildUpdateXML()
	{
		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		var PWInfoXML = IFDS.Xml.addSingleNode(dataXML, 'PWInfo');
		IFDS.Xml.addSingleNode(PWInfoXML, 'runMode', _RUNMODE_UPDATE);
		IFDS.Xml.addSingleNode(PWInfoXML, 'PWUUID', _PWInfoObj['PWUUID']);
		IFDS.Xml.addSingleNode(PWInfoXML, 'PWID', _PWInfoObj['PWID']);
		IFDS.Xml.addSingleNode(PWInfoXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(_PWInfoObj['stopDate']));
		
		if (_PWInfoObj['graceStartDate'] && _PWInfoObj['graceStartDate'].length > 0)
		{
			IFDS.Xml.addSingleNode(PWInfoXML, 'graceEndDate', DesktopWeb.Util.getSMVDateValue(_PWInfoObj['graceEndDate']));
		}else{
			IFDS.Xml.addSingleNode(PWInfoXML, 'graceEndDate', '');
		}
		IFDS.Xml.addSingleNode(PWInfoXML, 'version', _PWInfoObj['version']);
		return dataXML;
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,INQ: _INQ
		,YES: 'yes'
		,NO: 'no'
		,configs: _configs
		,updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
            // Call init service
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);
			
			DesktopWeb.Ajax.doSmartviewAjax(_dtPWInfoInqService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
            
			function responseHandler(success, responseXML)
			{
				if (success){
					// Handle response
					_initXML = responseXML;
					
					// Load configuration 
					loadConfigurations(responseXML);
					
					// Load Default Values
					loadDefaultValues(responseXML);
					
					// Load permission if success
					storePermissions(responseXML);
					
					// Call render screen function
					if (_permissions[_self.INQ]){
						// Load dropdown if success
						populateDropdownList(responseXML);
						
						populateDefaultSearchCriteria(responseXML);
						
						// Register PW Asset Level Threshold Amount tooltip
						registerThresholdAmountTip(IFDS.Xml.getNodes(responseXML, "//ThresholdAmts/ThresholdAmt"));
					}
					
					if (!_configs['salesRepbyBranch']){
						var PWAcctGrid = _resources.grids['PWAcct'];
						PWAcctGrid.hideColumn(PWAcctGrid.getColumnModel().findColumnIndex('branch')); 
					}
				}else{
					disableScreen();
				}
			}
		}
		
		,getDefault: function(defaultName)
		{
			return _defaultValues[defaultName];
		}
		
		,getPWInfoObject: function()
		{
			return _PWInfoObj;
		}

		,selectPWAcct: function(record)
		{
			updateShareholderName(record);
			updatePWAcctGridButtons(record);
		}
		
		,openActionPopup: function(name, action)
		{		
			var popup = _resources.popups[name];	
			popup.show();
			popup.init(action);
		}
		
		,openHistoryPopup: function(auditType)
		{
			var viewParam = {};
			var historyName = null;
			viewParam['auditType'] = auditType;
			viewParam['searchValue1'] = _PWInfoObj['PWUUID'];
			historyName = _translationMap['PrivateWealthInformation']+ ' - ' +_translationMap['History'];
			_resources.popups['history'].init(historyName, _dtHistoryService, viewParam, true);
			_resources.popups['history'].show();
		}
		
		,openAdminPopup: function(recType)
		{					
			var title = null;	
			var adminData = {};
			if (recType == 'PWInfo')
			{
				title = _translationMap['PrivateWealthInformation']+ ' - ' +_translationMap['Admin']
				adminData['userName'] = _PWInfoObj['userName'];
				adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(_PWInfoObj['processDate']);
				adminData['modUser'] = _PWInfoObj['modUser'];
				adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(_PWInfoObj['modDate']);
			}else{
				var selectedRecord = _resources.grids['PWAcct'].getSelectedRecord();
				title = _translationMap['LinkedAccount']+ ' - ' +_translationMap['Admin']
				adminData['userName'] = selectedRecord.get('userName');
				adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('processDate'));
				adminData['modUser'] = selectedRecord.get('modUser');
				adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('modDate'));
			}
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}
		
		,openPWAcctHistPopup: function()
		{
			var popup = _resources.popups['PWAcctHistPopup'];	
			popup.init();
			popup.show();
			
			var selectedPWAcct = _resources.grids['PWAcct'].getSelectedRecord();
			
			if (selectedPWAcct)
			{
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, 'acct', selectedPWAcct.data['acct']);
				IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_RELOAD);
				
				DesktopWeb.Ajax.doSmartviewAjax(_dtPWAcctHistService, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])
				
				function responseHandler(success, responseXML)
				{
					if (success){
						_resources.grids['PWAcctHist'].loadData(IFDS.Xml.getNode(responseXML, '//PWAcctHists'), false);
					}
				}
			}
		}
		
		,clickHandle_searchBtn: function()
		{
			if (_self.updatesFlag){
				DesktopWeb.Util.displayDiscardPrompt(performSearch);
			}else{
				performSearch(true);
			}
			function performSearch(confirm){
				if (confirm){
					if (validateSearchCriteria()){
						_currentSearch['searchFor'] = _resources.fields['searchFor'].getValue();
						_currentSearch['searchValue'] = _resources.fields['searchValue'].getValue();
						
						_self.updatesFlag = false;
						
						clearGrid('PWAcct');
						clearPWInfo();
						
						doSearch(_RUNMODE_RELOAD, false);
					}
				}
			}
		}
		
		,validatePWInfo: function(data, action)
		{
			var curBusDate = DesktopWeb.Util.stringToDate(_defaultValues['curBusDate'], DesktopWeb.Util.getDateDisplayFormat());
			var stopDate = DesktopWeb.Util.stringToDate(data['stopDate'], DesktopWeb.Util.getDateDisplayFormat());
			if (stopDate.getTime() == curBusDate.getTime()){
				DesktopWeb.Util.displayYesNo(_translationMap['CONFIRM_STOPPW_STOPGROUP'], go2Validate);
			}else{
				validateUpdatePWInfo(data, action);
			}
			function go2Validate(buttonId){
				if (buttonId == 'yes'){
					validateUpdatePWInfo(data, action);
				}
			}
		}
		
		,doAssessment: function()
		{
			if (_self.updatesFlag){
				DesktopWeb.Util.displayDiscardPrompt(performAssessment);
			}else{
				performAssessment(true);
			}
			function performAssessment(confirm){
				if (confirm){
					PWAssessment();
				}
			}
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;		
			DesktopWeb.Ajax.doSmartviewUpdate(_dtPWInfoProcService, null, buildUpdateXML(), responseHandler, _translationMap['ProcMsg_Saving']);			
			
			function responseHandler(success, responseXML, contextErrors)
			{	
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}else{
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}
	}	
}	