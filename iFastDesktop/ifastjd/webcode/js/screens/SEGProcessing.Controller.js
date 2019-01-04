/*********************************************************************************************
 * @file	SEGProcessing.Controller.js	
 * @author	Rod Walker
 * @desc	Controller JS file for SEG Processing screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached. 
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _segEventSchdReloadView = 'dtSegEventSchdReload';		
	var _segEventSchdVldtnsView = 'dtSegEventSchdVldtns';
	var _segEventSchdUpdView = 'dtSegEventSchdUpd';
	var _segRecalcReloadView = 'dtSegRecalcReload';
	var _segRecalcProcessView = 'dtSegRecalcProcess';
	
	var _permissionsMap = null;
	var _defaultValues = null;
	var _eventTypeProps = null;
	var _recalcRequested = false;
	var _updateRequested = false;	
	
	// PRIVATE METHODS ****************************************	
	
	function storePermissions(responseXML)
	{		
		_permissionsMap = {};
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(responseXML, '*/Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(responseXML, '*/Permissions/delPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.CANCEL] = IFDS.Xml.getNodeValue(responseXML, '*/Permissions/cancPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(responseXML, '*/Permissions/modPerm').toLowerCase() == 'yes';
	}
	
	function storeDefaultValues(responseXML)
	{
		_defaultValues = {};
		_defaultValues['schType'] = IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/schType');
		_defaultValues['stat'] = IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/stat');
		_defaultValues['statDesc'] = IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/statDesc');
		_defaultValues['createDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/createDate'));				
		_defaultValues['nextEventDt'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/nextEventDt'));
		_defaultValues['allowAdd'] = IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/allowAdd');		
		_defaultValues['newCMD'] = IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/newCMD');
		_defaultValues['effectDt'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/effectDt'));
		_defaultValues['elig'] = IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/elig');
		_defaultValues['guarSelect'] = IFDS.Xml.getNodeValue(responseXML, '*/DefaultValues/guarSelect');
	}
	
	function storeEventTypeProperties(responseXML)
	{
		_eventTypeProps = {};
		
		var eventTypeNodes = IFDS.Xml.getNodes(responseXML, '*/List[@listName = "EventTypeOptions"]/Element');		
		for (var i = 0; i < eventTypeNodes.length; i++)
		{
			var eventTypeCode = IFDS.Xml.getNodeValue(eventTypeNodes[i], 'code');			
			_eventTypeProps[eventTypeCode] = {};
			var propertyNodes = IFDS.Xml.getNodes(responseXML, '*/EventType' + eventTypeCode + '/*');					
			for (var p = 0; p < propertyNodes.length; p++)
			{
				_eventTypeProps[eventTypeCode][propertyNodes[p].nodeName] = propertyNodes[p].text;
			}			
		}
	}
	
	function populateEventSchedule(responseXML)
	{
		_resources.grids['eventSchedule'].loadData(IFDS.Xml.getNode(responseXML, "//EventSchedules"));
		_self.updateActionButtons();
	}
	
	function populateRecalc(responseXML)
	{
		_resources.grids['recalc'].loadData(IFDS.Xml.getNode(responseXML, "*/SegPendingRecalc"));
		if (IFDS.Xml.getNodeValue(responseXML, '*/SegPendingRecalc/enableProc').toLowerCase() == 'yes')
		{
			_resources.grids['recalc'].enableButton('processBtn')
		}
	}
	
	function populateDropdowns(responseXML)
	{
		var popup = _resources.popups['eventSchedulePopup'];
		popup.getField('eventType').loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName = 'EventTypeOptions']"));		
		popup.getField('guarSelect').loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName = 'GuarSelectOptions']"));		
	}
	
	function buildUpdateXML()
	{
		var updateXML = IFDS.Xml.newDocument('Data');
		IFDS.Xml.addSingleNode(updateXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		
		var records = _resources.grids['eventSchedule'].getAllRecords();
		for (var i = 0; i < records.length; i++)
		{
			if (records[i].data['runMode'] != "")
			{
				var recordXML = IFDS.Xml.addSingleNode(updateXML, 'Detl');
				IFDS.Xml.addSingleNode(recordXML, 'runMode', records[i].data['runMode']);
				IFDS.Xml.addSingleNode(recordXML, 'eventType', records[i].data['eventType']);
				IFDS.Xml.addSingleNode(recordXML, 'nextEventDt', DesktopWeb.Util.getSMVDateValue(records[i].data['nextEventDt']));
				IFDS.Xml.addSingleNode(recordXML, 'stat', records[i].data['stat']);
				IFDS.Xml.addSingleNode(recordXML, 'guarSelect', records[i].data['guarSelect']);							
				IFDS.Xml.addSingleNode(recordXML, 'newCMD', DesktopWeb.Util.getSMVDateValue(records[i].data['newCMD']));
				IFDS.Xml.addSingleNode(recordXML, 'eventSchedID', records[i].data['eventSchedID']);
				IFDS.Xml.addSingleNode(recordXML, 'polEventID', records[i].data['polEventID']);
				IFDS.Xml.addSingleNode(recordXML, 'contractType', DesktopWeb._SCREEN_PARAM_MAP['ContractType']);
				IFDS.Xml.addSingleNode(recordXML, 'maturityID', DesktopWeb._SCREEN_PARAM_MAP['MaturityID']);								
			}
		}
						
		return updateXML;
	}
	
	function sendEventSchValidationRequest(data, callback)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);		
		IFDS.Xml.addSingleNode(dataXML, 'contractType', DesktopWeb._SCREEN_PARAM_MAP['ContractType']);
		IFDS.Xml.addSingleNode(dataXML, 'maturityID', DesktopWeb._SCREEN_PARAM_MAP['MaturityID']);
		
		for (var i in data)
		{
			if (i != 'nextEventDt' && i != 'newCMD')
				IFDS.Xml.addSingleNode(dataXML, i, data[i]);	
		}
		
		IFDS.Xml.addSingleNode(dataXML, 'nextEventDt', DesktopWeb.Util.getSMVDateValue(data['nextEventDt']));
		IFDS.Xml.addSingleNode(dataXML, 'newCMD', DesktopWeb.Util.getSMVDateValue(data['newCMD']));
		
		DesktopWeb.Ajax.doSmartviewAjax(_segEventSchdVldtnsView, null, dataXML, responseHandler, _translationMap["ProcMsg_Processing"]);
		function responseHandler(success, responseXML)
		{
			callback(success);
		}
	}
	
	
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'	
		,DEL: 'del'
		,CANCEL: 'canc'		
		,PROCESS: 'proc'
		
		,updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var eventRequestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(eventRequestXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(eventRequestXML, 'contractType', DesktopWeb._SCREEN_PARAM_MAP['ContractType']);
			IFDS.Xml.addSingleNode(eventRequestXML, 'maturityID', DesktopWeb._SCREEN_PARAM_MAP['MaturityID']);
			
			var recalcRequestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(recalcRequestXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);

			DesktopWeb.Ajax.doSmartviewAjax(_segEventSchdReloadView, null, eventRequestXML, responseHandler1, _translationMap['ProcMsg_Loading']);
			DesktopWeb.Ajax.doSmartviewAjax(_segRecalcReloadView, null, recalcRequestXML, responseHandler2, _translationMap['ProcMsg_Loading']);
			
			function responseHandler1(success, responseXML)
			{								
				if (success)
				{
					_dataXML = responseXML;
					storePermissions(responseXML);
					storeDefaultValues(responseXML);				
					storeEventTypeProperties(responseXML);
					populateEventSchedule(responseXML);
					populateDropdowns(responseXML);
					
				}
			}
			
			function responseHandler2(success, responseXML)			
			{
				if (success)
				{
					populateRecalc(responseXML);
				}
			}
		}
		
		,getDefaultValues: function()
		{
			return _defaultValues;
		}
		
		,getEventTypeProperties: function(eventTypeCode)
		{			
			return _eventTypeProps[eventTypeCode];
		}		
		
		,openEventSchPopup: function(action)
		{
			if (action == this.ADD)
			{
				_resources.grids['eventSchedule'].clearSelectedRecord();
			}
			_resources.popups['eventSchedulePopup'].action = action;
			_resources.popups['eventSchedulePopup'].show();						
		}
		
		,saveEventSchPopup: function(action, data)
		{			
			var needVal = true;

			if (action == this.DEL && _resources.grids['eventSchedule'].getSelectedRecord().data['runMode'] == this.ADD)
			{
				needVal = false;
				_resources.grids['eventSchedule'].removeSelectedRecord();
			}
			else if (action == this.MOD && _resources.grids['eventSchedule'].getSelectedRecord().data['runMode'] == this.ADD)
			{
				data['runMode'] = this.ADD
			}
			
			if (needVal)
			{
				sendEventSchValidationRequest(data, callback);
			}
			else
			{
				_resources.popups['eventSchedulePopup'].hide();
			}
			
			function callback(success)
			{				
				if (success)
				{
					if (action == _self.ADD)
					{
						_resources.grids['eventSchedule'].addRecord(data);
						_resources.grids['eventSchedule'].selectLastRecord();
					}
					else
					{
						if (action == _self.PROCESS)
						{
							data['statDesc'] = _translationMap['Completed'];
						}
						if (action == _self.CANCEL)
						{
							data['statDesc'] = _translationMap['Cancelled'];
						}
						_resources.grids['eventSchedule'].updateSelectedRecord(data);
					}
					
					_self.updatesFlag = true;
					_updateRequested = true;
					_resources.popups['eventSchedulePopup'].hide();
					_self.updateActionButtons();
				}				
			}
		}
			
		,updateActionButtons: function()
		{
			var selectedRecord = _resources.grids['eventSchedule'].getSelectedRecord();
			_resources.grids['eventSchedule'].disableAllButtons();
			
			//add btn
			if (_defaultValues['allowAdd'].toLowerCase() == 'yes' && _permissionsMap[this.ADD])
			{
				_resources.grids['eventSchedule'].enableButton ('addBtn');
			}
			
			if (selectedRecord)
			{
				//mod btn
				if (selectedRecord.data['runMode'] == this.ADD || 
					(selectedRecord.data['allowMod'] == 'yes' && _permissionsMap[this.MOD]))
				{
					_resources.grids['eventSchedule'].enableButton ('modBtn');
				}				
				//del btn
				if ((selectedRecord.data['allowDel'] == 'yes' && selectedRecord.data['runMode'] == '' 
					&& _permissionsMap[this.DEL])|| selectedRecord.data['runMode'] == this.ADD)
				{
					_resources.grids['eventSchedule'].enableButton ('delBtn');
				}
				//cancel btn
				if (selectedRecord.data['allowCanc'] == 'yes' && selectedRecord.data['runMode'] == '' && _permissionsMap[this.CANCEL])
				{
					_resources.grids['eventSchedule'].enableButton ('canBtn');
				}				
				//process btn
				if (selectedRecord.data['allowProc'] == 'yes' && selectedRecord.data['runMode'] == '')
				{
					_resources.grids['eventSchedule'].enableButton ('procBtn');
				}
				//admin btn
				if (selectedRecord.data['eventSchedID'] != '')
				{
					_resources.grids['eventSchedule'].enableButton ('adminBtn');
				}				
			}
		}
		
		,updateRecalcButtons: function()
		{
			var selectedRecord = _resources.grids['recalc'].getSelectedRecord();
			if (selectedRecord != null && _enableRecalcProc) 			
			{
				_resources.grids['recalc'].enableButton('processBtn');				
			}
		}
		
		,doRecalcProcess: function()
		{
			_recalcRequested = true;
			_self.updatesFlag = true;
			
			var recalcRecords = _resources.grids['recalc'].getAllRecords();
			for (var i = 0; i < recalcRecords.length; i++)
			{
				recalcRecords[i].data['stat'] = _translationMap['RecalcRequested'];
				recalcRecords[i].commit();	
			}
			_resources.grids['recalc'].disableButton('processBtn');
		}
		
		,handleEventTypeChangeInPopup: function()
		{
			var popup = _resources.popups['eventSchedulePopup'];
			var eventType = popup.getField('eventType').getValue();
			var eventTypeProps = _self.getEventTypeProperties(eventType);											
			popup.getField('eventTypeSched').setValue(eventTypeProps['eventSchedDesc']);
			
			if (eventTypeProps['newCMD'] == 'yes')
			{
				popup.getField('newCMD').enable();
				popup.getField('newCMD').setValue(_self.getDefaultValues()['newCMD']);
			}
			else
			{
				popup.getField('newCMD').reset();
				popup.getField('newCMD').disable();
			}
			
			if (eventTypeProps['guarSelect'] == 'yes')
			{
				popup.getField('guarSelect').enable();								
				popup.getField('guarSelect').setValue(_self.getDefaultValues()['guarSelect']);							
			}
			else
			{
				popup.getField('guarSelect').disable();
				popup.getField('guarSelect').setValue(_self.getDefaultValues()['guarSelect']);
			}
		}
		
		,openAdminPopup: function()
		{
			var selectedRecord = _resources.grids['eventSchedule'].getSelectedRecord();
			if (selectedRecord)
			{
				_resources.popups['admin'].init(_translationMap["EventSchedule"] + " - " + _translationMap['Admin'], selectedRecord.data);
				_resources.popups['admin'].show();
			}
			else
			{
				throw new Error("No record selected");
			}
		}
					
		,doUpdate: function()
		{
			var updateStatus = null;
			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			if (_recalcRequested)
			{
				DesktopWeb.Ajax.doSmartviewUpdate(_segRecalcProcessView, null, requestXML, responseHandler1, null);
			}
			
			if ((!_recalcRequested || updateStatus == DesktopWeb._SUCCESS) && _updateRequested)
			{
				DesktopWeb.Ajax.doSmartviewUpdate(_segEventSchdUpdView, null, buildUpdateXML(), responseHandler2, null);
			}
			
			function responseHandler1(success, responseXML)
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
			
			function responseHandler2(success, responseXML)
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