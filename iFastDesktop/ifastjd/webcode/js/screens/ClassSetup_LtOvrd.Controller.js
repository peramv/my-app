/*********************************************************************************************
 * @file	ClassSetup_LtOvrd.Controller.js
 * @author	Rod Walker
 * @desc	Controller file for LimitationOverride screen, part of Class Setup
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *          
 *  11-Dec-2017 Sreejith A P0274726 P0266789-1870
 * 			   - Added Reason and remarks fields
 *             
 *  13-Feb-2018 Sreejith A P0274726 P0274726-83 
 * 			   - Removed Reason and remarks fields
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _changeFlag = false;
	var _initView = 'dtClassLtOvrdInit';
	var _inqView = 'dtClassLtOvrdInq';
	var _updateView = 'dtClassLtOvrdUpd';
	var _initDataXML = null;
	var _permissionsMap = null;
	
	// PRIVATE METHODS ****************************************	
	
	function setHeader()
	{						
		_resources.header.setText(_translationMap['LimitationOverride'] + ' - ' 
			+ _translationMap['Fund'] + ': ' + DesktopWeb._SCREEN_PARAM_MAP['fundCode'] + ', '
			+ _translationMap['Class'] + ': ' + DesktopWeb._SCREEN_PARAM_MAP['classCode']);
	}

	function populateDropdowns()
	{			
		_resources.popups['fundLtOvrd'].getField('ruleType').loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@id = 'RuleTypeList']"));
		_resources.fields['onlineEWI'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'EWIList']"));
		_resources.fields['cycleEWI'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'EWIList']"));
		_resources.fields['esgEWI'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'EWIList']"));
	}
	
	function populateScreen(inqDataXML)
	{		
		_resources.grids['fundLtOvrd'].loadData(IFDS.Xml.getNode(inqDataXML, '*/FundLtOvrds'), ['addBtn']);	
    if(_permissionsMap['mod'] == 'yes')
    {
      _resources.grids['fundLtOvrd'].enableButton('addBtn');
      _resources.grids['fundLtOvrd'].enableButton('delBtn');
    }
    else 
    {
      _resources.grids['fundLtOvrd'].disableButton('addBtn');
      _resources.grids['fundLtOvrd'].disableButton('delBtn');
    }
	}
	
	function goToScreen(screenName)
	{
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_' + screenName;
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
		
		if (screenName == "Search")
		{
			urlParams['createCache'] = 'true';	
		}
		else
		{
			urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		}			
									
		window.location = DesktopWeb.Ajax.buildURL(urlParams);
	}
	
	function filterOptions()
	{
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "TaxJurisList"]/Element[code = "*"]'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "AcctTypeList"]/Element[code = "*"]'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "TaxTypeList"]/Element[code = "*"]'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "AcctDesignationList"]/Element[code = "*"]'));		
	}
	
	function buildUpdateXML()
	{
		var updateXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(updateXML, 'fundCode', DesktopWeb._SCREEN_PARAM_MAP['fundCode']);
		IFDS.Xml.addSingleNode(updateXML, 'classCode', DesktopWeb._SCREEN_PARAM_MAP['classCode']);
		IFDS.Xml.addSingleNode(updateXML, 'processingMode', 'update');		
		
		var fundLtOvrdsXML = IFDS.Xml.addSingleNode(updateXML, 'FundLtOvrds');		
		var store = _resources.grids['fundLtOvrd'].getStore();
		
		var newRecords = store.query('runMode', _self.ADD);
		newRecords.each(addToXML);				
		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToXML);				
		var delRecords = store.query('runMode', _self.DEL);
		delRecords.each(addToXML);				
		
		return updateXML;
		
		function addToXML(item)
		{
			var recordXML = IFDS.Xml.addSingleNode(fundLtOvrdsXML, 'FundLtOvrd');
			for (var i in item.data)
			{
				IFDS.Xml.addSingleNode(recordXML, i, item.data[i]);
			}			
		}		
	}
		
	function getValueDescFromList(listId, value)
	{
		var desc = IFDS.Xml.getNodeValue(_initDataXML, '//List[@id = "' + listId + '"]/Element[code = "' + value + '"]/value');
		// if @id didn't work, try @listName
		if (!desc)
		{
			desc = IFDS.Xml.getNodeValue(_initDataXML, '//List[@listName = "' + listId + '"]/Element[code = "' + value + '"]/value');
		}
		return desc;
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		
		ADD: 'a', MOD: 'm', DEL: 'd'
		
		,updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			setHeader();
			_resources.fields['onlineEWI'].disableField();
			_resources.fields['cycleEWI'].disableField();
			_resources.fields['esgEWI'].disableField();
			
      DesktopWeb.Ajax.doRetrieveCache(['InitData'], function(responseXML){
        var node = IFDS.Xml.getNode(responseXML, '//Permissions');	
        _permissionsMap = {};
        _permissionsMap['inq'] = IFDS.Xml.getNodeValue(node, 'inq');
        _permissionsMap['add'] = IFDS.Xml.getNodeValue(node, 'add');
        _permissionsMap['mod'] = IFDS.Xml.getNodeValue(node, 'mod');
        _permissionsMap['del'] = IFDS.Xml.getNodeValue(node, 'del');
      }, _translationMap['ProcMsg_Loading'])
      
			DesktopWeb.Ajax.doSmartviewCall(_initView, null, null, responseHandler1, _translationMap['ProcMsg_Loading']);
			
			function responseHandler1(responseXML)
			{				
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _initView + 'Response'));
				 
				if (smartviewResults.successful)
				{
					_initDataXML = responseXML;
					filterOptions();					
					populateDropdowns();					
				}
				
				var requestXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(requestXML, 'fundCode', DesktopWeb._SCREEN_PARAM_MAP['fundCode']);				
				IFDS.Xml.addSingleNode(requestXML, 'classCode', DesktopWeb._SCREEN_PARAM_MAP['classCode']);
				
				DesktopWeb.Ajax.doSmartviewCall(_inqView, null, requestXML, responseHandler2, _translationMap['ProcMsg_Loading']);				
			
				function responseHandler2(responseXML)
				{					
					if (smartviewResults.successful)
					{										
						populateScreen(responseXML);					
					}										
				}
			}			
		}
		
		,updateGridActionButtons: function()
		{
			if (_resources.grids['fundLtOvrd'].getSelectedRecord() != null && _permissionsMap['mod'] == 'yes')
			{
				_resources.grids['fundLtOvrd'].enableButton('delBtn');
			}
			else
			{
				_resources.grids['fundLtOvrd'].disableButton('delBtn');
			}
		}
		
		,populateDetails: function(data)
		{
      if(_permissionsMap['mod'] == 'yes')
      {
        _resources.buttons['taxJurisDecl'].enable();
        _resources.buttons['provResDecl'].enable();
        _resources.buttons['accountTypeDecl'].enable();
        _resources.buttons['taxTypeDecl'].enable();
        _resources.buttons['acctDesigDecl'].enable();
        _resources.fields['onlineEWI'].enableField();
        _resources.fields['cycleEWI'].enableField();
        _resources.fields['esgEWI'].enableField();
      }else {
        _resources.buttons['taxJurisDecl'].disable();
        _resources.buttons['provResDecl'].disable();
        _resources.buttons['accountTypeDecl'].disable();
        _resources.buttons['taxTypeDecl'].disable();
        _resources.buttons['acctDesigDecl'].disable();
        _resources.fields['onlineEWI'].disableField();
        _resources.fields['cycleEWI'].disableField();
        _resources.fields['esgEWI'].disableField();
      }
      
			_resources.fields['taxJurisDecl'].setValue(data['taxJurisDecl']);
			_resources.fields['provResDecl'].setValue(data['provResDecl']);
			_resources.fields['accountTypeDecl'].setValue(data['accountTypeDecl']);
			_resources.fields['taxTypeDecl'].setValue(data['taxTypeDecl']);
			_resources.fields['acctDesigDecl'].setValue(data['acctDesigDecl']);
			
			_resources.fields['onlineEWI'].setValue(data['onlineEWI']);
			_resources.fields['cycleEWI'].setValue(data['cycleEWI']);
			_resources.fields['esgEWI'].setValue(data['esgEWI']);
		}
		
		,clearDetails: function()
		{
			_resources.fields['taxJurisDecl'].setValue("");
			_resources.buttons['taxJurisDecl'].disable();
			_resources.fields['provResDecl'].setValue("");
			_resources.buttons['provResDecl'].disable();
			_resources.fields['accountTypeDecl'].setValue("");
			_resources.buttons['accountTypeDecl'].disable();
			_resources.fields['taxTypeDecl'].setValue("");
			_resources.buttons['taxTypeDecl'].disable();
			_resources.fields['acctDesigDecl'].setValue("");
			_resources.buttons['acctDesigDecl'].disable();
			
			_resources.fields['onlineEWI'].reset()
			_resources.fields['onlineEWI'].disableField();
			_resources.fields['cycleEWI'].reset()
			_resources.fields['cycleEWI'].disableField();
			_resources.fields['esgEWI'].reset()
			_resources.fields['esgEWI'].disableField();
		}
		
		,getRuleTypeOverrideType: function(ruleType)
		{			
			return IFDS.Xml.getNodeValue(_initDataXML, "*/List[@id = 'RuleTypeList']/Element[code = '" + ruleType + "']/code/@override");
		}
		
		,openRulePopup: function(action)
		{
			if (action == this.ADD)
			{
				_resources.grids['fundLtOvrd'].clearSelectedRecord();
			}
			_resources.popups['fundLtOvrd'].setAction(action);
			_resources.popups['fundLtOvrd'].show();
		}
		
		,openDetailsPopup: function(field, list)
		{
			_resources.popups['details'].setEditDetails(field, list);						
			_resources.popups['details'].show();
		}
		
		,closePopup: function(popupName)
		{
			_resources.popups[popupName].hide();
		}
		
		,saveRuleUpdate: function(action, data)
		{
			if (action == this.ADD)
			{
				// Duplicate ruletype is not allowed
				var records = _resources.grids['fundLtOvrd'].getStore().queryBy(
					function(record)
					{
						return (record.get('runMode') != _self.DEL 
								&& record.get('ruleType') == data['ruleType'])?record:null;
					}
				);

				if (records.getCount()>0)
				{
					DesktopWeb.Util.displayWarning(_translationMap['RuleType'] 
													+ " '"
													+ getValueDescFromList('RuleTypeList', data['ruleType'])
													+ "' "
													+ _translationMap['AlreadyExists']);
				}
				_resources.grids['fundLtOvrd'].addRecord(data);				
				_resources.grids['fundLtOvrd'].selectLastRecord();
			}
			else
			{
				// annoying case where deleting a brand new record
				if (_resources.grids['fundLtOvrd'].getSelectedRecord().data['runMode'] == this.ADD)
				{					
					_resources.grids['fundLtOvrd'].removeSelectedRecord();						
				}
				else
				{
					_resources.grids['fundLtOvrd'].updateSelectedRecord(data);
				}					
				this.clearDetails();
				_resources.grids['fundLtOvrd'].selectFirstRecord();
			}			
			this.setUpdatesFlag();
			_self.closePopup('fundLtOvrd');						
		}
		
		,saveDetailsUpdate: function(field, value)
		{
			var record = _resources.grids['fundLtOvrd'].getSelectedRecord();
			if (!record.data['runMode'])
			{
				record.data['runMode'] = _self.MOD;
			}
			record.data[field] = value;
			this.populateDetails(_resources.grids['fundLtOvrd'].getSelectedRecord().data);
		}
		
		,updateEWIValue: function(field, value)
		{
			var record = _resources.grids['fundLtOvrd'].getSelectedRecord();
			if (!record.data['runMode'])
			{
				record.data['runMode'] = _self.MOD;
			}
			record.data[field] = value;
		}
		
		,getListValueDesc: function(listName, value)
		{
			var valueDesc = null
			valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "*/List[@id = '" + listName + "']/Element[code = '" + value + "']/value");
			
			if (valueDesc == null)
			{
				valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "*/List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");
			}
			return valueDesc;
		}
		
		,getDetailsListXML: function(listName)
		{
			return IFDS.Xml.getNode(_initDataXML, "*/List[@id = '" + listName + "']");
		}
		
		,loadOverrideValuesList: function(listName)
		{
			_resources.popups['fundLtOvrd'].getField('overrideValues').loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@id = '" + listName + "']"));
		}
		
		,setUpdatesFlag: function()
		{
			this.updatesFlag = true;
		}
		
		,clearUpdatesFlag: function()
		{
			this.updatesFlag = false;
		}
		
		,ok: function()
		{					
			DesktopWeb.Ajax.doSmartviewCall(_updateView, null, buildUpdateXML(), responseHandler, _translationMap['ProcMsg_Processing']);
			
			function responseHandler(responseXML)
			{
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _updateView + 'Response'));
				 
				if (smartviewResults.successful)
				{					
					goToScreen('Search');					
				}
			}		
		}
		
		,cancel: function()
		{
			goToScreen('Search');
		}
	}	
}	