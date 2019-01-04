/*********************************************************************************************
 * @file	FinInstIden.Controller.js	
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Identification Maintenance screen.
 *********************************************************************************************/
/*
 * Procedure: FinInstIden.Controller.js
 *
 * Purpose  : Controller file for Financial Institution Identification screen
 *             
 * Notes    : Setup Financial Institution Identification
 *            - Open screen from 
 *               Menu -> System Maintenance -> Financial Institution Identification
 *
 * History  :  
 *		18 Jul 2013 N. Suanlamyai P0193400 T53802
 *					- Created
 *
 *		15 Aug 2013 G. Thawornwachirakun P0193400 T54018
 *					- Fix GIIN format
 *
 *		23 Aug 2013 G. Thawornwachirakun P0193400 DFT0014730 T54066
 *					- Add display warning message and grid
 *
 *		09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *		17 Oct 2013 N. Suanlamyai P0193400 DFT0022411 T54302
 *					- Add band permission to the screen.
 *
 */

DesktopWeb.ScreenController = function(){
	
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'a';
	var _MOD = 'm';
	var _DEL = 'd';
	var _BLANK = '';
	var _IDENTLEVEL_FUND = '01';
	var _IDENTLEVEL_FUNDGROUP = '02';
	var _IDENTLEVEL_LEGALENTITY = '03';
	var _IDENTLEVEL_BROKER = '04';
	var _IDENTLEVEL_INTERMEDIARY = '05';
	
	var _requestRecNum = 25;
	var _nextRecNum = null;
	var _idenInitXML = null;
	var _defaultValues = {};
	var _currSearch = {};
	
	var _permissionsMap = {};
	
	var _IdentificationInquiryService = "dtFinanIdentInq";
	var _IdentificationValidationService = "dtFinanIdentVal";
	var _IdentificationUpdateService = "dtFinanIdentUpd";
	var _FundSuggestService = "fundOnlySearch";
	var _FundGroupSuggestService = "fundGroupSearch";
	var _LegelEntitySuggestService = "entWhereUsedSearch";
	var _BrokerSuggestService = "brokerSearch";
	var _IntermediarySuggestService = "intrSearch";
	var _historyService = 'dtHistoricalInfo';
	var _IDType_ID = "idTypeIDList";
	var _IDType_FI = "idTypeFIList";
	
	/** Store user permission **/
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inq').toLowerCase() == 'yes';
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/add').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/mod').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/del').toLowerCase() == 'yes';
	}
	
	/** Initialize Financial Institution Identification Maintenance screen **/
	function initFinInstIdenScreen()
	{
		_self.selectHandle_LevelField('01');
		var paramLevel = DesktopWeb._SCREEN_PARAM_MAP['level'];
		var paramCode = DesktopWeb._SCREEN_PARAM_MAP['code'];
		doSearch(paramLevel, paramCode, 'init', false);
	}

	function populateDropdown(responseXML)
	{
		_resources.fields['searchFor'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'levelList']"));
		var popup = _resources.popups['identPopup'];
		popup.getField('pLevelFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'levelList']"));
		popup.getField('pFundGroupFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'fndGrpList']"));
		popup.getField('pCntryFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'cntryOfIssueList']"));
		popup.getField('pStatusFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'idStatusList']"));
	}
	
	function storeDefaultValues(idenInitXML)
	{	
		_defaultValues['level']     = IFDS.Xml.getNodeValue(idenInitXML, "/*//ListSelection[@id = 'levelList']");
		_defaultValues['idTypeFI']  = IFDS.Xml.getNodeValue(idenInitXML, "/*//ListSelection[@id = 'idTypeFIList']");
		_defaultValues['idTypeID']  = IFDS.Xml.getNodeValue(idenInitXML, "/*//ListSelection[@id = 'idTypeIDList']");
		_defaultValues['idType']    = _BLANK;
		_defaultValues['deff']      = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(idenInitXML, "/*//DefaultValues/deff"));
		_defaultValues['stopDate']  = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(idenInitXML, "/*//DefaultValues/stopDate"));
		_defaultValues['cntryOfIssue'] = IFDS.Xml.getNodeValue(idenInitXML, "/*//ListSelection[@id = 'cntryOfIssueList']");
		_defaultValues['idStat'] = IFDS.Xml.getNodeValue(idenInitXML, "/*//ListSelection[@id = 'idStatusList']");
	}
	
	function setDefaultSearch()
	{
		_resources.fields['searchFor'].setValue(_defaultValues['level']);
		_self.selectHandle_LevelField(_defaultValues['level']);
	}
	
	function doSearch(searchFor, searchID, runMode, append)
	{
		var requestXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(requestXML, 'level', searchFor);
		IFDS.Xml.addSingleNode(requestXML, 'code', searchID);
		IFDS.Xml.addSingleNode(requestXML, 'groupType', (searchFor=='02')?'FATCA':_BLANK);
		IFDS.Xml.addSingleNode(requestXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(requestXML, 'startRecNum', (_nextRecNum)?_nextRecNum:'1');
		IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _requestRecNum);
		
		_currSearch['level'] = searchFor;
		_currSearch['code'] = searchID;
		
		DesktopWeb.Ajax.doSmartviewAjax(_IdentificationInquiryService, (runMode == 'init')?{ignoreErrorCode: '15'}:null, requestXML, responseHandler, _translationMap['Loading']);
		
		function responseHandler(success, responseXML)
		{
			if (success){
				
				if ( runMode == 'init' )
				{
					_idenInitXML = responseXML;
					storePermissions(responseXML);
					storeDefaultValues(responseXML);
					populateDropdown(responseXML);
					setDefaultSearch();
					updateButtonState(null);
				}
				
				loadGrid(IFDS.Xml.getNode(responseXML, "//Identifications"), append);
				
				_nextRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
				enableMoreButton( _nextRecNum );
				
			}else{
				// Handle Rejected Response
				if ( runMode == 'init' ){
					disableScreen();
				}else{
					updateButtonState(null);
				}
			}
		}
	}
	
	function disableScreen()
	{
		_resources.grids['identGrd'].disableAllButtons();
		_resources.fields['searchFor'].disable();
		_resources.fields['searchByFund'].disable();
		_resources.fields['searchByFundGroup'].disable();
		_resources.fields['searchByLegalEntity'].disable();
		_resources.fields['searchByBroker'].disable();
		_resources.fields['searchByIntermediary'].disable();
		_resources.buttons['searchBtn'].disable();
	}
	
	function enableMoreButton(moreRec)
	{
		if (moreRec){
			_resources.grids['identGrd'].enableButton('moreBtn');
		}else{
			_resources.grids['identGrd'].disableButton('moreBtn');
		}
	}

	function loadGrid(identifierXML, append)
	{
		if (identifierXML != null)
		{
			_resources.grids['identGrd'].getStore().loadData(identifierXML, append);
		}
	}
	
	function updateButtonState(record)
	{
		/*************************************************
		 ** Enable/Disable the buttons based-on 
		 ** user's permissions and allowMod/allowDel flag
		 *************************************************/
		var identGrd = _resources.grids['identGrd'];
		if ( _permissionsMap[_ADD] ){
			identGrd.enableButton('addBtn');
		}else{
			identGrd.disableButton('addBtn');
		}
		
		if (record)
		{
            if ( (_permissionsMap[_MOD] && record.get('allowMod') == 'yes') || record.get('runMode') == _ADD ){
				identGrd.enableButton('modBtn');
			}else{
				identGrd.disableButton('modBtn');
			}
			
			if ( (_permissionsMap[_DEL] && record.get('allowDel') == 'yes') || record.get('runMode') == _ADD ){
				identGrd.enableButton('delBtn');
			}else{
				identGrd.disableButton('delBtn');
			}
			
			if ( record.get('runMode') == _ADD )
			{
				identGrd.disableButton('adminBtn');
				identGrd.disableButton('historicalBtn');
			}else{
				identGrd.enableButton('adminBtn');
				identGrd.enableButton('historicalBtn');
			}
		}else{
			identGrd.disableButton('modBtn');
			identGrd.disableButton('delBtn');
			identGrd.disableButton('adminBtn');
			identGrd.disableButton('historicalBtn');
		}
	}
	
	function submitIdenPopup(popup)
	{
		if ( popup.isValid() ) 
		{
			var data = popup.getData();
			var requestXML = IFDS.Xml.newDocument('data');
			var idenNode = IFDS.Xml.addSingleNode(requestXML, 'Identification');
			IFDS.Xml.addAttribute(idenNode, 'RecordSource', data['uuid'] );
			IFDS.Xml.addSingleNode(idenNode, 'uuid', data['uuid']);
			IFDS.Xml.addSingleNode(idenNode, 'level', data['level']);
			IFDS.Xml.addSingleNode(idenNode, 'code', data['code']);
			IFDS.Xml.addSingleNode(idenNode, 'idType', data['idType']);
			IFDS.Xml.addSingleNode(idenNode, 'idValue', data['idValue']);
			IFDS.Xml.addSingleNode(idenNode, 'deff', DesktopWeb.Util.getSMVDateValue(data['deff']));
			IFDS.Xml.addSingleNode(idenNode, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
			IFDS.Xml.addSingleNode(idenNode, 'cntryOfIssue', data['cntryOfIssue']);
			IFDS.Xml.addSingleNode(idenNode, 'idStat', data['idStat']);
			IFDS.Xml.addSingleNode(idenNode, 'allowMod', data['allowMod']);
			IFDS.Xml.addSingleNode(idenNode, 'allowDel', data['allowDel']);
			IFDS.Xml.addSingleNode(idenNode, 'version', data['version']);
			IFDS.Xml.addSingleNode(idenNode, 'runMode', data['runMode']);

			DesktopWeb.Ajax.doSmartviewAjax(_IdentificationValidationService
				, {ignoreWarning: true}
				, requestXML, responseHandler, _translationMap['Loading']);
			
			function responseHandler(success, responseXML, contextErrors, warnings)
			{
				var msg = '';
				if (success){
					if (warnings.length > 0)
					{
						var msg = IFDS.Xml.getNodeValue(warnings[0], 'text');				
						for (var i = 1; i < warnings.length; i++)
						{
							msg += "<br/>" + IFDS.Xml.getNodeValue(warnings[i], 'text')
						}		
						
						DesktopWeb.Util.displayWarning(msg, savePopupFunc, Ext.Msg.OKCANCEL);
						
					}
					else
						savePopupFunc('ok');
				
					// Update Identification Table
					function savePopupFunc(buttonId)
					{
					
						if (buttonId == 'ok')
						{
							if (msg != '')
								data['warnMsg'] = msg;
								
							if ( popup.action == _ADD )
							{
								_resources.grids['identGrd'].addRecord(data);
								_resources.grids['identGrd'].setSelectedRecord( _resources.grids['identGrd'].getStore().getCount() - 1 );
								_resources.grids['identGrd'].focusRow( _resources.grids['identGrd'].getStore().getCount() - 1 );
							}else{
								_resources.grids['identGrd'].updateSelectedRecord(data);
							}
							
							_self.updatesFlag = true;
							
							// Hide popup
							popup.hide();
						}
					}
					
				}else{
					// Handle Rejected Response
					if (warnings.length > 0)
					{
						var msg = IFDS.Xml.getNodeValue(warnings[0], 'text');				
						for (var i = 1; i < warnings.length; i++)
						{
							msg += "<br/>" + IFDS.Xml.getNodeValue(warnings[i], 'text')
						}		
						DesktopWeb.Util.displayWarning(msg);
					}
					storeContextErrorsPopup(contextErrors);
				}
			}
		}
	}
	
	function deleteIdentification(record)
	{
		if ( record.get('allowDel') == 'yes' ){
			var deletedRecordIndex = _resources.grids['identGrd'].getRecordIndex(record);
			if ( record.get('runMode') == _ADD ){
				_resources.grids['identGrd'].getStore().remove(record);
			}else{
				record.set('runMode', _DEL); 
				record.commit();
				_self.selectIdentification(null);
			}
			
			_self.updatesFlag = true;
			
			if ( _resources.grids['identGrd'].getStore().getCount() > deletedRecordIndex )
			{
				_resources.grids['identGrd'].setSelectedRecord( deletedRecordIndex );
			}else{
				_resources.grids['identGrd'].setSelectedRecord( deletedRecordIndex - 1 );
			}
			
			updateButtonState(_resources.grids['identGrd'].getSelectedRecord());
			_self.selectIdentification(_resources.grids['identGrd'].getSelectedRecord());
			
		}else{
			DesktopWeb.Utils.displayError(_translationMap['ERROR_RecordNotAllowToDelete']);
		}
	}
	
	function buildUpdateXML(runMode)
	{
		var updateDelRecords = _resources.grids['identGrd'].getStore().queryBy(function(record){ return record.get('runMode') == _DEL });
		var updateModRecords = _resources.grids['identGrd'].getStore().queryBy(function(record){ return record.get('runMode') == _MOD });
		var updateAddRecords = _resources.grids['identGrd'].getStore().queryBy(function(record){ return record.get('runMode') == _ADD });
		
		if ( updateDelRecords.length + updateModRecords.length + updateAddRecords.length <= 0 ) return null;
		
		var updateXML = IFDS.Xml.newDocument('data');
		var identsXML = IFDS.Xml.addSingleNode(updateXML, 'Identifications');
		
		IFDS.Xml.addSingleNode(updateXML, 'runMode', runMode);
		
		buildUpdateXML( identsXML, updateDelRecords );
		buildUpdateXML( identsXML, updateModRecords );
		buildUpdateXML( identsXML, updateAddRecords );
		
		return updateXML;
		
		function buildUpdateXML(context, updatedRecords)
		{
			for(i = 0; i < updatedRecords.length; i++)
			{
				buildUpdateXMLByRecord(context, updatedRecords.itemAt(i));
			}
		}
		
		function buildUpdateXMLByRecord(context, record)
		{
			var identXML = IFDS.Xml.addSingleNode(context, 'Identification');
			IFDS.Xml.addAttribute(identXML, 'RecordSource', record.id);
			IFDS.Xml.addSingleNode(identXML, 'runMode', record.get('runMode'));
			IFDS.Xml.addSingleNode(identXML, 'uuid', record.get('uuid'));
			IFDS.Xml.addSingleNode(identXML, 'level', record.get('level'));
			IFDS.Xml.addSingleNode(identXML, 'code', record.get('code'));
			IFDS.Xml.addSingleNode(identXML, 'version', record.get('version'));
			if ( record.get('runMode') != _DEL ){
				IFDS.Xml.addSingleNode(identXML, 'groupType', record.get('groupType'));
				IFDS.Xml.addSingleNode(identXML, 'idType', record.get('idType'));
				IFDS.Xml.addSingleNode(identXML, 'idValue', record.get('idValue'));
				IFDS.Xml.addSingleNode(identXML, 'deff', DesktopWeb.Util.getSMVDateValue(record.get('deff')));
				IFDS.Xml.addSingleNode(identXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(record.get('stopDate')));
				IFDS.Xml.addSingleNode(identXML, 'cntryOfIssue', record.get('cntryOfIssue'));
				IFDS.Xml.addSingleNode(identXML, 'idStat', record.get('idStat'));
			}
		}
	}
	
	function storeContextErrorsPopup(errNodes)
	{
		var popup = _resources.popups['identPopup'];
		var fldName = null;
		var errMsg = null;
		var fldObj = null;
		Ext.each(errNodes, function(errNode){
			fldName = IFDS.Xml.getNodeValue(errNode, 'fieldSource/xmlElementName');
			errMsg = IFDS.Xml.getNodeValue(errNode, 'text');
			switch ( fldName ){
				case 'level': 
					fldObj = popup.getField('pLevelFld');
					break;
				case 'code': 
					break;
				case 'idType': 
					fldObj = popup.getField('pIdTypeFld');
					break;
				case 'idValue': 
					fldObj = popup.getField('pIdValueFld');
					break;
				case 'deff': 
					fldObj = popup.getField('pDeffFld');
					break;
				case 'stopDate': 
					fldObj = popup.getField('pStopDateFld');
					break;
				case 'cntryOfIssue': 
					fldObj = popup.getField('pCntryFld');
					break;
				case 'idStat': 
					fldObj = popup.getField('pStatusFld');
					break;
			}
			if ( fldObj ) fldObj.markInvalid(errMsg);
		});
	}
	
	function storeContextErrors(errNodes)
	{
		clearContextErrors();
		var firstErrRecIndex = -1;
		
		Ext.each(errNodes, function(errNode){
			var recId = IFDS.Xml.getNodeValue(errNode, 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errNode, 'text');
			var errRecord = _resources.grids['identGrd'].getStore().getById(recId);

			if ( errRecord ){
				errRecord.set('errMsg', errMsg);
				
				// Get a deleted record back to grid to mark and error
				if ( errRecord.get('runMode') == _DEL ){
					errRecord.set('runMode', _BLANK);
				}
				errRecord.commit();
				var errRecordIndex = _resources.grids['identGrd'].getRecordIndex(errRecord);
				if ( firstErrRecIndex == -1 || firstErrRecIndex > errRecordIndex ){
					firstErrRecrIndex = errRecordIndex;
				}
			}
		});
		
		_resources.grids['identGrd'].getSelectionModel().selectRow(firstErrRecIndex);
		_resources.grids['identGrd'].focusRow(firstErrRecIndex);
	}
	
	function clearContextErrors()
	{
		var errRecords = _resources.grids['identGrd'].getStore().queryBy(function(record){ return record.get('errMsg') != _BLANK });
		
		for(i = 0; i < errRecords.length; i++)
		{
			errRecords.itemAt(i).set('errMsg', _BLANK);
			errRecords.itemAt(i).commit();
		}
	}
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,BLANK: _BLANK
		,IDENTLEVEL_FUND: _IDENTLEVEL_FUND
		,IDENTLEVEL_FUNDGROUP: _IDENTLEVEL_FUNDGROUP
		,IDENTLEVEL_LEGALENTITY: _IDENTLEVEL_LEGALENTITY
		,IDENTLEVEL_BROKER: _IDENTLEVEL_BROKER
		,IDENTLEVEL_INTERMEDIARY: _IDENTLEVEL_INTERMEDIARY
		
		,updatesFlag: false
		,defaultValues: _defaultValues
		
		,init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			initFinInstIdenScreen();
		}
		
		,selectHandle_LevelField: function(level)
		{
			_resources.fields['searchByFund'].hide();
			_resources.fields['searchByFundGroup'].hide();
			_resources.fields['searchByLegalEntity'].hide();
			_resources.fields['searchByBroker'].hide();
			_resources.fields['searchByIntermediary'].hide();
			switch ( level )
			{
				case _IDENTLEVEL_FUND: 
					_resources.fields['searchByFund'].show();
					break;
				case _IDENTLEVEL_FUNDGROUP: 
					_resources.fields['searchByFundGroup'].show();
					break;
				case _IDENTLEVEL_LEGALENTITY: 
					_resources.fields['searchByLegalEntity'].show();
					break;
				case _IDENTLEVEL_BROKER: 
					_resources.fields['searchByBroker'].show();
					break;
				case _IDENTLEVEL_INTERMEDIARY:  
					_resources.fields['searchByIntermediary'].show();
					break;
			}
		}
		
		,selectHandle_LevelFieldPopup: function(level)
		{
			var idenPopup = _resources.popups['identPopup'];
			var idTypeListName = 'idTypeIDList';
			idenPopup.getField('pFundFld').hide();
			idenPopup.getField('pFundGroupFld').hide();
			idenPopup.getField('pLegalEntityFld').hide();
			idenPopup.getField('pBrokerFld').hide();
			idenPopup.getField('pIntermediaryFld').hide();
			idenPopup.getField('pIdTypeFld').reset();
			switch ( level )
			{
				case _IDENTLEVEL_FUND: 
					idenPopup.getField('pFundFld').show();
					idTypeListName = _IDType_FI;
					break;
				case _IDENTLEVEL_FUNDGROUP: 
					idenPopup.getField('pFundGroupFld').show();
					idTypeListName = _IDType_FI;
					break;
				case _IDENTLEVEL_LEGALENTITY: 
					idenPopup.getField('pLegalEntityFld').show();
					idTypeListName = _IDType_ID;
					break;
				case _IDENTLEVEL_BROKER: 
					idenPopup.getField('pBrokerFld').show();
					idTypeListName = _IDType_ID;
					break;
				case _IDENTLEVEL_INTERMEDIARY: 
					idenPopup.getField('pIntermediaryFld').show();
					idTypeListName = _IDType_ID;
					break;
			}
			idenPopup.getField('pIdTypeFld').loadData(IFDS.Xml.getNode(_idenInitXML, "//List[@listName = '" + idTypeListName + "']"));
		}
		
		,clickHandle_openActionPopup: function(popup, action)
		{
			popup.init(action);
			popup.populate(_resources.grids['identGrd'].getSelectedRecord(), action);
			popup.show();
		}
		
		,clickHandle_searchBtn: function()
		{
			var field = null;
			var searchFor = _resources.fields['searchFor'].getValue();
			switch ( searchFor )
			{
				case _IDENTLEVEL_FUND:
					field = _resources.fields['searchByFund'];
					break;
				case _IDENTLEVEL_FUNDGROUP:
					field = _resources.fields['searchByFundGroup'];
					break;
				case _IDENTLEVEL_LEGALENTITY:
					field = _resources.fields['searchByLegalEntity'];
					break;
				case _IDENTLEVEL_BROKER:
					field = _resources.fields['searchByBroker'];
					break;
				case _IDENTLEVEL_INTERMEDIARY:
					field = _resources.fields['searchByIntermediary'];
					break;
				default:
					field = _resources.fields['searchByFund'];
				
			}
			_self.updatesFlag = false;
			_nextRecNum = null;
			_resources.grids['identGrd'].clearData();
			doSearch(searchFor, field.getValue(), 'inq', false);
		}
		
		,clickHandle_moreBtn: function()
		{
			doSearch(_currSearch['level'], _currSearch['code'], 'inq', true);
		}
		
		,clickHandle_okBtnOnIdenPopup: function(popup)
		{
			submitIdenPopup(popup);
		}

		,clickHandle_deleteBtnIdenGrd: function()
		{			
			// Delete a selected record
			deleteIdentification(_resources.grids['identGrd'].getSelectedRecord());
		}

		,selectIdentification: function(selectedRecord)
		{			
			if (selectedRecord)
			{
				_resources.fields['levelLabel'].setValue(_self.getListDisplay('levelList', selectedRecord.data['level']));
				_resources.fields['identifierLabel'].setValue(selectedRecord.data['displayValue']);
				_resources.fields['idTypeLabel'].setValue(_self.getIDTypeDisplay(selectedRecord.data['level'], selectedRecord.data['idType']));
				_resources.fields['idValueLabel'].setValue(selectedRecord.data['idValue']);
				_resources.fields['deffLabel'].setValue(selectedRecord.data['deff']);
				_resources.fields['stopDateLabel'].setValue(selectedRecord.data['stopDate']);
				_resources.fields['cntryLabel'].setValue(_self.getListDisplay('cntryOfIssueList', selectedRecord.data['cntryOfIssue']));
				_resources.fields['statusLabel'].setValue(_self.getListDisplay('idStatusList', selectedRecord.data['idStat']));
				
				updateButtonState(selectedRecord);
			}else{
				_resources.fields['levelLabel'].reset();
				_resources.fields['identifierLabel'].reset();
				_resources.fields['idTypeLabel'].reset();
				_resources.fields['idValueLabel'].reset();
				_resources.fields['deffLabel'].reset();
				_resources.fields['stopDateLabel'].reset();
				_resources.fields['cntryLabel'].reset();
				_resources.fields['statusLabel'].reset();
			}
		}
		
		,getListDisplay: function(listName, code)
		{
			var listNode = IFDS.Xml.getNode(_idenInitXML, "//List[@listName = '" + listName + "']/Element[code='" + code + "']");
			return (listNode)?IFDS.Xml.getNodeValue(listNode, 'value'):code;
		}
		
		,getIDTypeDisplay: function(level, code)
		{
			var listName = null;
			switch ( level )
			{
				case _IDENTLEVEL_FUND:
				case _IDENTLEVEL_FUNDGROUP:
					listName = 'idTypeFIList';
					break;
				case _IDENTLEVEL_LEGALENTITY:
				case _IDENTLEVEL_BROKER:
				case _IDENTLEVEL_INTERMEDIARY:
					listName = 'idTypeIDList';
					break;
			}
			return _self.getListDisplay(listName, code);
		}
		
		,loadSuggestFieldPopup: function(level, code, displayValue)
		{
			var suggestFld = null;
			var valueFld = null;
			var displayFld = null;
			var identPopup = _resources.popups['identPopup'];
			switch ( level )
			{
				case _IDENTLEVEL_FUND: // Fund
					suggestFld = identPopup.getField('pFundFld');
					valueFld = 'fundCode';
					displayFld = 'fndDisp';
					break;
				case _IDENTLEVEL_FUNDGROUP: // Fund Group
					suggestFld = identPopup.getField('pFundGroupFld');
					valueFld = 'fundGroupCode';
					displayFld = 'displayValue';
					break;
				case _IDENTLEVEL_LEGALENTITY: // Legal Entity
					suggestFld = identPopup.getField('pLegalEntityFld');
					valueFld = 'whereUseKey';
					displayFld = 'displayValue';
					break;
				case _IDENTLEVEL_BROKER: // Broker
					suggestFld = identPopup.getField('pBrokerFld');
					valueFld = 'agencyCode';
					displayFld = 'displayValue';
					break;
				case _IDENTLEVEL_INTERMEDIARY:  // Intermediary
					suggestFld = identPopup.getField('pIntermediaryFld');
					valueFld = 'intrCode';
					displayFld = 'displayValue';
					break;
			}
			
			if ( level != _IDENTLEVEL_FUNDGROUP ){
				var dataXML = IFDS.Xml.newDocument('data');
				var possMatchesXML = IFDS.Xml.addSingleNode(dataXML, 'PossibleMatches');
				var possMatchXML = IFDS.Xml.addSingleNode(possMatchesXML, 'PossibleMatch');
				IFDS.Xml.addSingleNode(possMatchXML, valueFld, code);
				IFDS.Xml.addSingleNode(possMatchXML, displayFld, displayValue);
				
				// Load possibleMatches into the field
				suggestFld.store.loadData(IFDS.Xml.getNode(dataXML, "//PossibleMatches"));
				// Set value to the field
				suggestFld.setValue(code);
			}else{
				suggestFld.setValue(code);
			}
		}
		,openAdminPopup: function()
		{
			var selectrecord = _resources.grids['identGrd'].getSelectedRecord();
					
			var adminData = {};
			adminData['userName'] = selectrecord.data['userName'];
			adminData['procDate'] = selectrecord.data['processDate'];
			adminData['modUser'] = selectrecord.data['modUser'];
			adminData['modDate'] = selectrecord.data['modDate'];
			_resources.popups['admin'].init(adminData);
			_resources.popups['admin'].show();
		}
		,openHistoryPopup: function(){
			var viewParam = {};
			var historyName = null;
			var selectedRecord  = _resources.grids['identGrd'].getSelectedRecord();
			
			if (selectedRecord != undefined && selectedRecord != null)
			{
				switch ( selectedRecord.data['level'] )
				{
					case _IDENTLEVEL_FUND: 
						viewParam['auditType'] = 'FundIdentifier';
						break;
					case _IDENTLEVEL_FUNDGROUP: 
						viewParam['auditType'] = 'FundGrpIdentifier';
						break;
					case _IDENTLEVEL_LEGALENTITY: 
						viewParam['auditType'] = 'EntitySearchID';
						break;
					case _IDENTLEVEL_BROKER: 
						viewParam['auditType'] = 'EntityIdentifier';
						break;
					case _IDENTLEVEL_INTERMEDIARY:  
						viewParam['auditType'] = 'EntityIdentifier';
						break;
				}
				
				viewParam['searchValue1'] = selectedRecord.data['uuid'];
				historyName = _translationMap['Identification']+ ' - ' +_translationMap['History'];
				
				_resources.popups['history'].init(historyName, _historyService, viewParam, true);
				_resources.popups['history'].show();
			}
		}
		,screenHasChanged: function()
		{
			var updateRecords = _resources.grids['identGrd'].getStore().queryBy(function(record){ return record.get('runMode') != _BLANK });
			
			return (updateRecords.length > 0);
		}
		,doValidate: function()
		{
			var updateStatus = null;
			var updateXML = buildUpdateXML('val');
			
			if ( !updateXML ) 
			{
				_self.updatesFlag = false;
				DesktopWeb.Util.commitScreen();
			}
			
			DesktopWeb.Ajax.doSmartviewUpdate(_IdentificationUpdateService, null, updateXML, responseHandler, _translationMap['ProcMsg_Validating']);
			function responseHandler(success, responseXML, contextErrors)
			{	
				if (success)
				{
					DesktopWeb.Util.commitScreen();
				}else{
					storeContextErrors(contextErrors);
				}
			}
		}
		,doUpdate: function()
		{
			var updateStatus = null;		
			DesktopWeb.Ajax.doSmartviewUpdate(_IdentificationUpdateService, null, buildUpdateXML('upd'), responseHandler, _translationMap['ProcMsg_Saving']);
			function responseHandler(success, responseXML, contextErrors)
			{	
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
					_self.updatesFlag = false;
				}else{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}
	}
}	