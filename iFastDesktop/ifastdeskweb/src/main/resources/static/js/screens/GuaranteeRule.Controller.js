/*********************************************************************************************
 * @file	GuaranteeRule.Controller.js
 * @author	Danny Xu
 * @desc	Controller JS file for SEG - Guarantee Rules screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *        - Fix display date format follows dateFormatDisplay parameter
 *
 *	25 Sep 2014 P. Wongpakdee P0233151 INA Cayenne Day 2 T55815
 *		  - Return valueType in findOverrideRateType
 *		  - add function findGuarCalcRuleCode to assign guarCalcRule as code
 *		  - add function defaultGuarantee to reset blank for Adding and
 *			refresh Rule Description for Modifying
 *		  - validate fields mandatory in saveDetlPopup
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached. 
 *
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _selectedMstrRecord = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _self = null;
	var _resources = null;
	var _initView = 'dtGuarRulesReload';
	var _classSearchView = 'dtGuarRulesReload'; 
	var _updateView = 'dtGuarRulesUpd';
	var _mstrValView = 'dtGuarRulesMstrVldtn';
	var _detlValView = 'dtGuarRulesDetlVldtn';
	var _initDataXML = null;
	var _reloadDataXML = null;
	var _codeTypeInfoXML = null;
	var _permissionsMap = {};
	var _mstrCounter = 1;
	var _buttonFlag = false;
	var _newContractType;
	var _newContractVer;
	
	// PRIVATE METHODS ****************************************
	function storePermissions(initViewXML)
	{		
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function loadGridData(classSearchXML, grid, string)
	{		
		_resources.grids[grid].loadData(IFDS.Xml.getNode(classSearchXML, '/*//' + string), null);
	}
	
	function populateDropdowns(initViewXML)
	{
		_resources.fields['contractType'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'ContractTypeList']"));
		_resources.popups['codeTypePopup'].getField('transType').getStore().loadData(IFDS.Xml.getNode(initViewXML, "/*//List[@listName = 'TransTypeList']"));
		_resources.popups['codeTypePopup'].getField('codeType').getStore().loadData(IFDS.Xml.getNode(initViewXML, "/*//List[@listName = 'CodeTypeList']"));
		_resources.popups['codeTypePopup'].getField('contractType').getStore().loadData(IFDS.Xml.getNode(initViewXML, "/*//List[@listName = 'ContractTypeList']"));
		_resources.popups['guaranteePopup'].getField('guarType').getStore().loadData(IFDS.Xml.getNode(initViewXML, "/*//List[@listName = 'GuaranteeList']"));
		_resources.popups['guaranteePopup'].getField('guarCalcRule').getStore().loadData(IFDS.Xml.getNode(initViewXML, "/*//List[@listName = 'guarCalcRulelist']"));
	}
	
	function isNewRecord(record)
	{
		return record.data['runMode'] == _self.ADD
	}
	
	function getUpdatedRecordCount(grid)
	{
		if (_resources.grids[grid] == null || _resources.grids[grid].getStore() == null)
		{
			return 0;
		}
		var store = _resources.grids[grid].getStore();
		var newRecords = store.query('runMode', _self.ADD);	
		var modRecords = store.query('runMode', _self.MOD);		
		var delRecords = store.query('runMode', _self.DEL);
		return newRecords.length + modRecords.length + delRecords.length 
	}
	
	function formatGuaranteeRuleXML(xml)
	{
		var mstrXMLNodes = IFDS.Xml.getNodes(xml, 'Mstr');
		for (var m = 0; m < mstrXMLNodes.length; m++)
		{
			IFDS.Xml.addAttribute(mstrXMLNodes[m], 'recordSource', m + 1);
			
			var detlXMLNodes = IFDS.Xml.getNodes(mstrXMLNodes[m], 'Detls/Detl');
			IFDS.Xml.addSingleNode(mstrXMLNodes[m], 'num', detlXMLNodes.length);
			
			for (var d = 0; d < detlXMLNodes.length; d++)
			{
				IFDS.Xml.addAttribute(detlXMLNodes[d], 'recordSource', (m + 1) + ":" + (d + 1));
				IFDS.Xml.addSingleNode(detlXMLNodes[d], 'num', m+1);
			} 
		}
		_mstrCounter += mstrXMLNodes.length;
		return xml;
	}
	
	function buildMstrValidateXML(data)
	{
		var recordXML = IFDS.Xml.newDocument('Data');
		addToMstrXML(data);
		return recordXML;
		
		function addToMstrXML(item)
		{			
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item['runMode']);
			IFDS.Xml.addSingleNode(recordXML, 'contractType', item['contractType']);
			IFDS.Xml.addSingleNode(recordXML, 'contractVer', item['contractVer']);
			IFDS.Xml.addSingleNode(recordXML, 'deff', DesktopWeb.Util.getSMVDateValue(item['deff']));
			IFDS.Xml.addSingleNode(recordXML, 'transType', item['transType']);
			IFDS.Xml.addSingleNode(recordXML, 'codeType', item['codeType']);
			IFDS.Xml.addSingleNode(recordXML, 'transCode', item['transCode']);
			IFDS.Xml.addSingleNode(recordXML, 'segGuarCalcUUID', item['segGuarCalcUUID']);
			IFDS.Xml.addSingleNode(recordXML, 'guarCalcID', item['guarCalcID']);
			IFDS.Xml.addSingleNode(recordXML, 'transContractType', item['transContractType']);
			IFDS.Xml.addSingleNode(recordXML, 'transContractVer', item['transContractVer']);
		}
	}
	
	function buildDetlValidateXML(data)
	{
		var recordXML = IFDS.Xml.newDocument('Data');
		addToDetlXML(data);
		return recordXML;
		
		function addToDetlXML(item)
		{
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item['runMode']);
			IFDS.Xml.addSingleNode(recordXML, 'guarType', item['guarType']);
			IFDS.Xml.addSingleNode(recordXML, 'overrideRate', item['overrideRate']);
			IFDS.Xml.addSingleNode(recordXML, 'overrideRateType', item['overrideRateType']);
			IFDS.Xml.addSingleNode(recordXML, 'segGuarCalcDetlUUID', item['segGuarCalcDetlUUID']);
		}
	}
	
	function updateGuaranteeType()
	{
		var tempXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_initDataXML, "/*//List[@listName = 'GuaranteeList']"));
		var selectedRecord = _resources.grids['guaranteeInfo'].getSelectedRecord();
		var value;
		if (selectedRecord)
		{
			value = selectedRecord.data['guarType'];
		}
		
		var store = _resources.grids['guaranteeInfo'].getStore();
		store.each(removeElements);
		_resources.popups['guaranteePopup'].getField('guarType').getStore().loadData(tempXML);
		
		function removeElements(item)
		{
			if (value != item.data['guarType'])
			{
				var xml = IFDS.Xml.getNode(tempXML, "//Element[code = '" + item.data['guarType'] + "']");
				IFDS.Xml.deleteNode(xml);
			}
		}	
	}
	
	function buildUpdateXML()
	{
		var updateXML = IFDS.Xml.newDocument('Mstrs');
		var records = _resources.grids['codeTypeInfo'].getAllRecords();
		for (var i = 0; i < records.length; i++)
		{
			addToMstrXML(records[i]);
		}
		
		return updateXML;
		
		function addToMstrXML(item)
		{
			var detls = buildUpdateDetlXML(item.data['recordSource']);
			if (IFDS.Xml.getNodeValue(detls) == "" && item.data['runMode'] == "")
			{
				return;
			}
			else if (item.data['runMode'] == "")
			{
				item.data['runMode'] = _self.MOD;
			}
			
			var recordXML = IFDS.Xml.addSingleNode(updateXML, 'Mstr');
			IFDS.Xml.addAttribute(recordXML, 'RecordSource', item.data['recordSource']);
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item.data['runMode']);
			IFDS.Xml.addSingleNode(recordXML, 'contractType', item.data['contractType']);
			if (item.data['contractVer'] == null || item.data['contractVer'] == "" || item.data['contractVer'] == " ")
			{
				IFDS.Xml.addSingleNode(recordXML, 'contractVer', "0");
			}
			else
			{
				IFDS.Xml.addSingleNode(recordXML, 'contractVer', item.data['contractVer']);
			}
			IFDS.Xml.addSingleNode(recordXML, 'segGuarCalcUUID', item.data['segGuarCalcUUID']);
			IFDS.Xml.addSingleNode(recordXML, 'guarCalcID', item.data['guarCalcID']);
			IFDS.Xml.addSingleNode(recordXML, 'transType', item.data['transType']);
			IFDS.Xml.addSingleNode(recordXML, 'codeType', item.data['codeType']);
			IFDS.Xml.addSingleNode(recordXML, 'transCode', item.data['transCode']);
			IFDS.Xml.addSingleNode(recordXML, 'deff', DesktopWeb.Util.getSMVDateValue(item.data['deff']));
			IFDS.Xml.addSingleNode(recordXML, 'transContractType', item.data['transContractType']);
			IFDS.Xml.addSingleNode(recordXML, 'transContractVer', item.data['transContractVer']);
			IFDS.Xml.appendNode(recordXML, detls);
		}
	}
	
	function buildUpdateDetlXML(index)
	{
		var updateXML = IFDS.Xml.newDocument('Detls');
		var store = _resources.grids['guaranteeInfo'].getStore();
		var newRecords = store.query('num', index);
		newRecords.each(addToDetlXML);
		return updateXML;
		
		function addToDetlXML(item)
		{
			if (item.data['runMode'] == "")
				return;
			var recordXML = IFDS.Xml.addSingleNode(updateXML, 'Detl');			
			IFDS.Xml.addAttribute(recordXML, 'RecordSource', item.data['recordSource']);
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item.data['runMode']);
			IFDS.Xml.addSingleNode(recordXML, 'segGuarCalcDetlUUID', item.data['segGuarCalcDetlUUID']);
			IFDS.Xml.addSingleNode(recordXML, 'guarCalcID', item.data['guarCalcID']);
			IFDS.Xml.addSingleNode(recordXML, 'guarType', item.data['guarType']);
			IFDS.Xml.addSingleNode(recordXML, 'guarCalcSeq', item.data['guarCalcSeq']);
			IFDS.Xml.addSingleNode(recordXML, 'guarCalcRule', item.data['guarCalcRule']);
			IFDS.Xml.addSingleNode(recordXML, 'overrideRate', item.data['overrideRate']);
			IFDS.Xml.addSingleNode(recordXML, 'overrideRateType', item.data['overrideRateType']);
		}
	}
	
	function emptyVersionNumber(xml)
	{
		var mstrXMLNodes = IFDS.Xml.getNodes(xml, '//GuarRules/Mstr');
		for (var m = 0; m < mstrXMLNodes.length; m++)
		{
			if (IFDS.Xml.getNodeValue(mstrXMLNodes[m], "contractVer") == "0")
			{
				IFDS.Xml.replaceSingleNode(mstrXMLNodes[m], "contractVer", "")
			}
		}
	}
	
	
	function populateNewSeq()
	{
		var store = _resources.grids['guaranteeInfo'].getStore();
		store.each(applyChange);
		
		function applyChange (item)
		{
			if (item.data['guarCalcSeq'] != store.indexOf(item)+1)
			{
				if (item.data['runMode'] != _self.ADD)
				{
					item.data['runMode'] = _self.MOD;
				}
				item.data['guarCalcSeq'] = store.indexOf(item)+1;
			}
		}
		store.filterBy(function(record){return record.data.runMode != _self.DEL && record.data.num == _resources.grids['codeTypeInfo'].getSelectedRecord().data['recordSource']});		
	}
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		
		,updatesFlag: false
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			_resources.grids['codeTypeInfo'].disableAllButtons();
			_resources.grids['guaranteeInfo'].disableButton('modBtn');
			_resources.grids['guaranteeInfo'].disableButton('delBtn');
			
			DesktopWeb.Ajax.doSmartviewUpdate(_initView, null, null, responseHandler, _translationMap['ProcMsg_Loading'])			
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					_initDataXML = responseXML;
					storePermissions(responseXML);
					populateDropdowns(responseXML);
					_resources.grids['codeTypeInfo'].disableAllButtons();
					_resources.grids['codeTypeInfo'].enableButton('addBtn');
					_resources.grids['guaranteeInfo'].disableAllButtons();
					_counter = 0;
					_codeTypeInfoXML = IFDS.Xml.getNode(responseXML, "//GuarRules");
					var coolXML = formatGuaranteeRuleXML(_codeTypeInfoXML);
					_resources.grids['codeTypeInfo'].loadData(coolXML);
					_resources.grids['guaranteeInfo'].loadData(coolXML);
				}											
			}
		}
		
		,findOverrideRateType: function(value, type)
		{
			var _temp = IFDS.Xml.getNode(_initDataXML, "/*//List[@listName = 'guarCalcRuleList_" + type + "']//Element[code = '" + value +  "']/code/@overrideRateType");

			/* If cannot find value from the Misc-Info list; needs to get from data loop (Search mode) */
			if (_temp == null)
			{
				var _valueType = IFDS.Xml.getNodes(_reloadDataXML, '//GuarRules/Mstr/Detls/Detl');	

				for (var m = 0; m < _valueType.length; m++)
				{
					if ( (IFDS.Xml.getNodeValue(_valueType[m], "guarType") == type) && (IFDS.Xml.getNodeValue(_valueType[m], "guarCalcRule") == value) )
					{
						return IFDS.Xml.getNodeValue(_valueType[m], "valueType");
					}				
				}
			}
			else
			{
				return _temp.xml.split ("\"")[1];
			}
		}
		
		,populateGuaranteeType: function()
		{
			updateGuaranteeType();
		}
		
		,getContractType: function()
		{
			return _newContractType;
		}
		
		,getContractVer: function()
		{
			return _newContractVer;
		}
		
		,populateTransCode: function(value)
		{
			_resources.popups['codeTypePopup'].getField('transCode').loadData (IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'CodeValueList_" + value + "' ]"));
		}
		
		,populateRuleDesc: function (value)
		{
			_resources.popups['guaranteePopup'].getField('guarCalcRule').loadData (IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'guarCalcRuleList_" + value + "' ]"));
		}
		
		,findGuarCalcRuleCode: function (value)
		{
			var guarCalcRuleList = IFDS.Xml.getNodes(_initDataXML, "/*//List[@listName = 'guarCalcRulelist']/Element");
			
			for (var m = 0; m < guarCalcRuleList.length; m++)
			{				
				var ListCode = IFDS.Xml.getNodeValue(guarCalcRuleList[m], "code");
				var ListValue = IFDS.Xml.getNodeValue(guarCalcRuleList[m], "value");

				if ((ListCode == value) || (ListValue == value))				
				{
					_resources.popups['guaranteePopup'].getField('guarCalcRule').setValue(ListCode);
					return ListValue;
				}	
			}			
		}		
		
		,disableButtons: function (value, grid)
		{
			if (value != null && value.toLowerCase() == "yes")
			{
				_resources.grids[grid].disableButton('modBtn');
				_resources.grids[grid].disableButton('delBtn');
			}
		}
		
		,updateSelectedMstrRecord: function(grid)
		{
			
			_selectedMstrRecord = _resources.grids[grid].getSelectedRecord();
			
			if (_selectedMstrRecord != null )
			{	
				_resources.grids['guaranteeInfo'].loadData(IFDS.Xml.getNode(_initDataXML, "//Mstr[transType='" + _selectedMstrRecord.data['transType'] + "']/Detls"));					
			}
			else
			{
				_resources.grids['guaranteeInfo'].clearData();
			}
			this.updateActionButtons(grid);
		}
		
		,doLookup: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'contractType', _resources.fields['contractType'].getValue());
			IFDS.Xml.addSingleNode(dataXML, 'contractVer', _resources.fields['versionNumber'].getValue());
						 					
			DesktopWeb.Ajax.doSmartviewAjax(_classSearchView, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching']);
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{					
					_reloadDataXML = responseXML;
					emptyVersionNumber (responseXML);
					_resources.grids['guaranteeInfo'].disableAllButtons();
					_resources.grids['codeTypeInfo'].disableAllButtons();
					_resources.grids['codeTypeInfo'].enableButton('addBtn');
					_counter = 0;
					_codeTypeInfoXML = IFDS.Xml.getNode(responseXML, "//GuarRules");
					var coolXML = formatGuaranteeRuleXML(_codeTypeInfoXML);
					_resources.grids['codeTypeInfo'].loadData(coolXML);
					_resources.grids['guaranteeInfo'].loadData(coolXML);
				}
			}
		}
		
		,openHistoricalPopup: function(recType)
		{
			var viewParam = {}
			var title = ""
			if (recType == 'mstrs')
			{
				viewParam['auditType'] = 'GuarRules';
				viewParam['searchValue1'] = _resources.grids['codeTypeInfo'].getSelectedRecord().data["contractType"];
				viewParam['searchValue2'] = _resources.grids['codeTypeInfo'].getSelectedRecord().data["contractVer"];
				viewParam['searchValue3'] = _resources.grids['codeTypeInfo'].getSelectedRecord().data["transType"];
				viewParam['searchValue4'] = _resources.grids['codeTypeInfo'].getSelectedRecord().data["codeType"];
				viewParam['searchValue5'] = _resources.grids['codeTypeInfo'].getSelectedRecord().data["transCode"];
				title = "Code Type Info - History";
			}
			else if (recType == 'detls')
			{
				viewParam['auditType'] = 'GuarRulesDetl';
				viewParam['searchValue1'] = _resources.grids['guaranteeInfo'].getSelectedRecord().data["guarCalcID"];
				viewParam['searchValue2'] = _resources.grids['guaranteeInfo'].getSelectedRecord().data["guarCalcSeq"];
				viewParam['searchValue3'] = _resources.grids['guaranteeInfo'].getSelectedRecord().data["guarType"];
				title = "Guarantee Info - History";
			}
			_resources.popups['history'].init(title, 'dtHistoricalInfo', viewParam, true);
			_resources.popups['history'].show();
		}
		
		,openAdminPopup: function(recType)
		{
			var title = null;	
			var xml = null;
			if (recType == 'mstrs')
			{
				title = "Code Type Info - Admin";
				var xmlIndex = _resources.grids['codeTypeInfo'].getSelectedRecord().data['recordSource'];
				if (_reloadDataXML)
					xml = IFDS.Xml.getNode(_reloadDataXML, '//Mstr[@recordSource = "' + xmlIndex + '"]');
			}
			else if(recType == 'detls')
			{
				title = "Guarantee Info - Admin";
				var xmlIndex = _resources.grids['guaranteeInfo'].getSelectedRecord().data['recordSource'];
				if (_reloadDataXML)
					xml = IFDS.Xml.getNode(_reloadDataXML, '//Detl[@recordSource = "' + xmlIndex + '"]');
			}
			
			var adminData = {};
			adminData['userName'] = "";
			adminData['procDate'] = "";
			adminData['modUser'] = "";
			adminData['modDate'] = "";
			
			if (xml != null)
			{
				adminData['userName'] = IFDS.Xml.getNodeValue(xml, 'userName');
				adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'processDate'));
				adminData['modUser'] = IFDS.Xml.getNodeValue(xml, 'modUser');
				adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'modDate'));
			}
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();
		}
		
		
		,keepCountMstr: function()
		{
			var temp = _mstrCounter;
			_mstrCounter++;
			return temp;
		}
		
		,setFlag: function()
		{
			_buttonFlag = true;
			_newContractType = _resources.fields['contractType'].getValue();
			_newContractVer = _resources.fields['versionNumber'].getValue();
		}
		
		,getFlag: function()
		{
			return _buttonFlag;
		}
		
		,clearVersionNumber: function(dropdown)
		{
			if (dropdown == 'top')
			{
				_resources.fields['versionNumber'].setValue("");
				_resources.fields['versionNumber'].clearInvalid();
			}
			else if (dropdown == 'popup')
			{
				_resources.popups['codeTypePopup'].getField('contractVer').setValue("");
				_resources.popups['codeTypePopup'].getField('contractVer').clearInvalid();
			}

		}
		
		,populateSearchVersionNumber: function(value)
		{
			var flag = false;
			var versionNum = IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]");
			
			if (versionNum != null)
			{
				var versionNumValue = IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]/Element/value");
				
				if (versionNumValue == '0')
				{
					_resources.fields['versionNumber'].setDisabled(true);
					flag = true;
				}
				else
				{
					_resources.fields['versionNumber'].setDisabled(false);
					_resources.fields['versionNumber'].loadData(versionNum);
					if (IFDS.Xml.getNodes(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]/Element").length == 1)
					{
						_resources.fields['versionNumber'].setValue(versionNumValue);
						flag = true;
					}
				}
			}
			
			return flag;
		}
		
		,populatePopupVersionNumber: function(value)
		{
			var flag = false;
			var versionNum = IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]");
			
			if (versionNum != null)
			{
				var versionNumValue = IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]/Element/value");
				if (versionNumValue == '0')
				{
					_resources.popups['codeTypePopup'].getField('contractVer').disableField();
					_resources.popups['codeTypePopup'].getField('contractVer').setValue(" ");
					flag = true;
				}
				else
				{
					_resources.popups['codeTypePopup'].getField('contractVer').enableField();
					_resources.popups['codeTypePopup'].getField('contractVer').getStore().loadData(versionNum);
					var records = IFDS.Xml.getNodes(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]/Element");
					if (records.length == 1)
					{
						_resources.popups['codeTypePopup'].getField('contractVer').setValue(versionNumValue);
						flag = true;
					}
				}
				
			}
			
			return flag;
		}
		
		,getDefaultDate: function()
		{
			return DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, "//DefaultDates/deff"));
		}
		
		,getListValueDesc: function(listName, value)
		{
			var valueDesc = null;
			valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "*/List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");
			if (valueDesc == null || valueDesc == "")
			{
				valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "*/List[@id = '" + listName + "']/Element[code = '" + value + "']/value");
			}
			return valueDesc;
		}
		
		,updateMstrActionButtons: function(grid)
		{
			var selectedRecord = _resources.grids[grid].getSelectedRecord();
				
			
			if (selectedRecord)
			{
				_resources.grids[grid].enableButton('modBtn');
				_resources.grids[grid].enableButton('delBtn');
				_resources.grids[grid].enableButton('historyBtn');
				_resources.grids[grid].enableButton('adminBtn');
				_resources.grids['guaranteeInfo'].enableButton ('addBtn');
				if (!_permissionsMap[this.MOD])
				{
					_resources.grids[grid].disableButton('modBtn');
				}
				if (!_permissionsMap[this.DEL])
				{
					_resources.grids[grid].disableButton('delBtn');
				}
				var value = _resources.grids['codeTypeInfo'].getSelectedRecord().data.acctContrExists;
				if (value != null && value.toLowerCase() == "yes")
				{
					_resources.grids[grid].disableButton('addBtn');
					_resources.grids[grid].disableButton('modBtn');
					_resources.grids[grid].disableButton('delBtn');
				}
				
			}
			else
			{
				_resources.grids[grid].disableButton('modBtn');
				_resources.grids[grid].disableButton('delBtn');
				_resources.grids[grid].disableButton('historyBtn');
				_resources.grids[grid].disableButton('adminBtn');
				_resources.grids['guaranteeInfo'].disableButton ('addBtn');
			}
			
			
			
		}
		,updateDetlActionButtons: function(grid)
		{
			var selectedRecord = _resources.grids[grid].getSelectedRecord();
			if (_resources.grids['codeTypeInfo'].getSelectedRecord())
				var value = _resources.grids['codeTypeInfo'].getSelectedRecord().data.acctContrExists;
			
			if (selectedRecord)
			{
				_resources.grids[grid].enableButton('modBtn');
				_resources.grids[grid].enableButton('delBtn');
				_resources.grids[grid].enableButton('historyBtn');
				_resources.grids[grid].enableButton('adminBtn');
				if (!_permissionsMap[this.MOD])
				{
					_resources.grids[grid].disableButton('modBtn');
				}
				if (!_permissionsMap[this.DEL])
				{
					_resources.grids[grid].disableButton('delBtn');
				}
				if (value != null && value.toLowerCase() == "yes")
				{
					_resources.grids[grid].disableButton('addBtn');
					_resources.grids[grid].disableButton('modBtn');
					_resources.grids[grid].disableButton('delBtn');
				}
			}
			else
			{
				_resources.grids[grid].disableButton('modBtn');
				_resources.grids[grid].disableButton('delBtn');
				_resources.grids[grid].disableButton('historyBtn');
				_resources.grids[grid].disableButton('adminBtn');
			}
		}
		
		,openActionPopup: function(action, grid, popup)
		{
			if (action == this.ADD)
			{
				_resources.grids[grid].clearSelectedRecord();
			}
			
			_resources.popups[popup].init(action);
			_resources.popups[popup].show();
		}
		
		,defaultGuarantee: function(action, popup)
		{
			var resetBlankAdd = _resources.popups[popup];
			
			if (action == this.ADD)
			{			
				/* Set fields to allow blank for reseting value */
				resetBlankAdd.getField('guarType').allowBlank = true;
				resetBlankAdd.getField('guarCalcRule').allowBlank = true;
						
				/* Clear fields memory from actions MOD&DEL */
				resetBlankAdd.getField('guarType').setValue("");
				resetBlankAdd.getField('guarCalcRule').setValue("");
				resetBlankAdd.getField('overrideRate').setValue("");
					
				/* Rule Description should be enable only until Guarantee Type is specifieds for Adding */
				resetBlankAdd.getField('guarCalcRule').setDisabled(true);					
			}
			else if (action == this.MOD)
			{
				/* Rule Description should be enable for modifying */
				resetBlankAdd.getField('guarCalcRule').setDisabled(false);
				
				/* Refresh Rule Description list based on their Guarantee Type */
				this.populateRuleDesc(resetBlankAdd.getField('guarType').getValue());
			}		
		}		
		
		,closeActionPopup: function(popup)
		{
			_resources.popups[popup].hide();
		}
		
		,doMstrValidation: function(data)
		{
			var updateStatus = false;
			DesktopWeb.Ajax.doSmartviewUpdate(_mstrValView, null, buildMstrValidateXML(data), responseHandler, null);
			function responseHandler(success, responseXML)
			{
				updateStatus = success;
			}
			return updateStatus;			
		}
		
		,doDetlValidation: function(data)
		{
			var updateStatus = false;
			DesktopWeb.Ajax.doSmartviewUpdate(_detlValView, null, buildDetlValidateXML(data), responseHandler, null);
			function responseHandler(success, responseXML)
			{
				updateStatus = success;
			}
			return updateStatus;			
		}
		
		,saveMstrPopup: function(action, data)
		{
			var _success = true;
			var _needVal = true;

			if (action == this.DEL && _resources.grids['codeTypeInfo'].getSelectedRecord().data['runMode'] == this.ADD)
			{
				_needVal = false;
				_resources.grids['codeTypeInfo'].removeSelectedRecord();
			}
			else if (action == this.MOD && _resources.grids['codeTypeInfo'].getSelectedRecord().data['runMode'] == this.ADD)
			{
				data['runMode'] = this.ADD
			}
			
			
			if (_needVal)
			{
				_success = this.doMstrValidation (data);
				if (_success)
				{
					if (action == this.ADD)
					{
						_resources.grids['codeTypeInfo'].addRecord(data);
					}
					else
					{
						_resources.grids['codeTypeInfo'].updateSelectedRecord(data);
					}
				}
			}

			if (_success)
			{
				this.updatesFlag = (getUpdatedRecordCount('guaranteeInfo') > 0) || (getUpdatedRecordCount('codeTypeInfo') > 0);
				
				if (action == this.DEL)
				{
					_resources.grids['guaranteeInfo'].getStore().filterBy(function(rec) {return false});
				}
				_self.updateMstrActionButtons('codeTypeInfo');
				_self.updateDetlActionButtons('guaranteeInfo');
			}
			
			
			
			return _success;
		}
		
		,saveDetlPopup: function(action, data)
		{
			var _success = true;
			var _needVal = true;
			if (action == this.DEL && _resources.grids['guaranteeInfo'].getSelectedRecord().data['runMode'] == this.ADD)
			{
				_needVal = false;
				_resources.grids['guaranteeInfo'].removeSelectedRecord();
			}
			else if (action == this.MOD && _resources.grids['guaranteeInfo'].getSelectedRecord().data['runMode'] == this.ADD)
			{
				data['runMode'] = this.ADD;
			}

			/* Validate mandatory fields again since they are previously set to allow blank while reseting value */
			var valBlankAdd = _resources.popups['guaranteePopup'];
			valBlankAdd.getField('guarType').allowBlank = false;
			valBlankAdd.getField('guarCalcRule').allowBlank = false;
			
			if (valBlankAdd.getField('guarType').isValid() && valBlankAdd.getField('guarCalcRule').isValid());
			else{
				_success = false;
				_needVal = false;
			}			
			
			if (_needVal)
			{
				_success = this.doDetlValidation (data);
				if (_success)
				{
					if (action == this.ADD)
					{
						_resources.grids['guaranteeInfo'].addRecord(data);
						_resources.grids['guaranteeInfo'].selectLastRecord();
					}
					else
					{
						_resources.grids['guaranteeInfo'].updateSelectedRecord(data);
					}
						
				}
			}
			
			if (_success)
			{
				this.updatesFlag = (getUpdatedRecordCount('guaranteeInfo') > 0) || (getUpdatedRecordCount('codeTypeInfo') > 0);
					if (action == this.DEL ||  action == this.MOD)
						{
							
							_resources.grids['guaranteeInfo'].getStore().filterBy(function(rec)
								{return _resources.grids['codeTypeInfo'].getSelectedRecord().data['recordSource'] == rec.data.num && 
								rec.data.runMode != _self.DEL});
							
						}
					
					if (action == this.DEL)
					{
						_resources.grids['guaranteeInfo'].selectFirstRecord();
						populateNewSeq();
					}
						
					_self.updateDetlActionButtons('guaranteeInfo');
			}
			
			
			
			return _success;
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler, _translationMap['ProcMsg_Processing']);
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{
					updateStatus = DesktopWeb._FAIL
				}
			}
			return updateStatus;			
		}	 		
	}	
}	