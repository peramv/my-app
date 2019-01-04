/*********************************************************************************************
 * @file	EntTaxHist.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for Entity Tax Jurisdiction screen
 *
 * History :
 * 10 Jan 2013 G. Thawornwachirakun P0195459 T52973 
 *              Add loading prim-hist record to new grid panel.
 *
 * 04 Feb 2013 G. Thawornwachirakun P0195459 I3230914 T53045
 *              Add logic to control a new checkbox
 *
 * 20 Feb 2013 G. Thawornwachirakun P0195459 I3230914 T53156
 *              Add sending AccountNum when query and update EntityTaxHist. 
 *              Fix misspelling from greter to greater
 *
 * 04 Apr 2013 G. Thawornwachirakun P0195459 I3258601 T53348
 *              Modify validation method to markInvalid to TaxJuris 
 *              and Effective Date 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = 'dtEntTaxHistInit';	
	var _updateView = 'dtEntTaxHistUpd';
	var _warningView = 'dtTaxJurisAmendWarn';	
	var _permissionsMap = {};	
	
	// PRIVATE METHODS ****************************************
	function storePermissions(initViewXML)
	{		
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/modPerm').toLowerCase() == 'yes';
	}
	
	function loadPopups(initViewXML)
	{
		_resources.popups['taxJuris'].getField('taxJuris').getStore().loadData(IFDS.Xml.getNode(initViewXML, '/*//List[@listName="TaxJurisList"]'))
		
		_self.allowCheckbox = IFDS.Xml.getNodeValue(initViewXML, '/*//AccountDetl/allowCheckbox').toLowerCase() == 'yes';					
		_self.allowSync = IFDS.Xml.getNodeValue(initViewXML, '/*//AccountDetl/allowSync').toLowerCase() == 'yes';		
		_self.verifyDate = 	new Date(IFDS.Xml.getNodeValue(initViewXML, '/*//AccountDetl/createDate'));
		_self.verifyDateString = 	DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(initViewXML, '/*//AccountDetl/createDate'));
	}
	
	function loadTaxJurisInfo(initViewXML)
	{
		var btnsToEnable = (_permissionsMap[_self.ADD] ? ['addBtn'] : null);
		_resources.grids['taxJurisInfo'].loadData(IFDS.Xml.getNode(initViewXML, '/*//EntityTaxJurisInfo'), btnsToEnable);
	}
		
	function loadShareholderTaxJurisDetails(initViewXML)
	{
		var btnsToEnable =  null;
		
		_resources.grids['SharetaxJurisHistInfo'].loadData(IFDS.Xml.getNode(initViewXML, '/*//ShareholderTaxJurisDetails'), btnsToEnable);
	}
	
	function isNewRecord(record)
	{
		return record.data['runMode'] == _self.ADD
	}
	
	function getUpdatedRecordCount()
	{		
		var store = _resources.grids['taxJurisInfo'].getStore();
		var newRecords = store.query('runMode', _self.ADD);	
		var modRecords = store.query('runMode', _self.MOD);		
		var delRecords = store.query('runMode', _self.DEL);
		return newRecords.length + modRecords.length + delRecords.length 
	}
	
	function buildUpdateXML()
	{
		var updateXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(updateXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
		IFDS.Xml.addSingleNode(updateXML, 'sync', _resources.grids['taxJurisInfo'].getFooterToolbar().get('chkSync').getValue() ? "yes" : "no");	
		var store = _resources.grids['taxJurisInfo'].getStore();
		
		var newRecords = store.query('runMode', _self.ADD);
		newRecords.each(addToXML);
		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToXML);
		var delRecords = store.query('runMode', _self.DEL);
		delRecords.each(addToXML);
		
		return updateXML;
		
		function addToXML(item)
		{
			var recordXML = IFDS.Xml.addSingleNode(updateXML, 'EntTaxHistUpd');			
			IFDS.Xml.addAttribute(recordXML, 'RecordSource', store.indexOf(item));
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item.data['runMode']);
			IFDS.Xml.addSingleNode(recordXML, 'taxJuris', item.data['taxJuris']);
			IFDS.Xml.addSingleNode(recordXML, 'taxJurisDeff', DesktopWeb.Util.getSMVDateValue(item.data['effDate']));
			IFDS.Xml.addSingleNode(recordXML, 'entTaxHistID', item.data['entTaxHistID']);
			IFDS.Xml.addSingleNode(recordXML, 'version', item.data['version']);			
			IFDS.Xml.addSingleNode(recordXML, 'entityID', DesktopWeb._SCREEN_PARAM_MAP['entityID']);			
		}		
	}
	
	function sendWarnings(data, action)
	{		
		var viewParamXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(viewParamXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);		
		var entityNode = IFDS.Xml.addSingleNode(viewParamXML, 'entityID', DesktopWeb._SCREEN_PARAM_MAP['entityID']);
		IFDS.Xml.addAttribute(entityNode, 'RecordSource', (data['taxJuris'] + "_" + data['taxyr']));
		IFDS.Xml.addSingleNode(viewParamXML, 'runMode', data['runMode']);
		IFDS.Xml.addSingleNode(viewParamXML, 'taxJuris', data['taxJuris']);
		
		DesktopWeb.Ajax.doSmartviewAjax(_warningView, null, viewParamXML, responseHandler);
		
		function responseHandler(success, responseXML, contextErrors)
		{								
			if (success)
			{			
				var warnMsgs = IFDS.Xml.getNodes(responseXML, '/*//AmendmentWarning/warnMsg');
				if (warnMsgs != null && warnMsgs.length > 0)				
					displayAmendmentWarnings(warnMsgs);	
				
				if (action == _self.ADD)
				{
					_resources.grids['taxJurisInfo'].addRecord(data);
					_resources.grids['taxJurisInfo'].selectLastRecord();
				}
				else
				{					
					if (isNewRecord(_resources.grids['taxJurisInfo'].getSelectedRecord()))
						data['runMode'] = this.ADD;
						
					_resources.grids['taxJurisInfo'].updateSelectedRecord(data);
					_self.updateActionButtons();
				}
				
				_self.updatesFlag = (getUpdatedRecordCount() > 0);
				_self.closeActionPopup();
			}
			else
			{
				displayError(contextErrors);
			}
		}
	
	}
	
	function displayAmendmentWarnings(warnMsgs)
	{
		var msg = IFDS.Xml.getNodeValue(warnMsgs[0]);				
		for (var i = 1; i < warnMsgs.length; i++)
		{
			msg += "<br/><br/>" + IFDS.Xml.getNodeValue(warnMsgs[i]);
		}	
		DesktopWeb.Util.displayInfo(msg);
	}
	
	function displayError(errMsgs)
	{
		var error = IFDS.Xml.getNodeValue(errMsgs[0], 'text');
		
		for (var i = 1; i < errMsgs.length; i++)
		{
			error += "<br/><br/>" + IFDS.Xml.getNodeValue(errMsgs[i], 'text');			
		}
		_resources.popups['taxJuris'].getField('taxJuris').markInvalid(error);
	}
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'	
		,verifyDate: ''
		,verifyDateString: ''
		,allowCheckbox: false
		,allowSync: false
		
		,updatesFlag: false
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			_resources.grids['taxJurisInfo'].disableAllButtons();
			
			var viewParamXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(viewParamXML, 'EntityID', DesktopWeb._SCREEN_PARAM_MAP['entityID']);						
			IFDS.Xml.addSingleNode(viewParamXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Loading']); 		
						
			function responseHandler(success, responseXML)
			{							
				if (success)
				{
					storePermissions(responseXML);
					loadPopups(responseXML);					
					loadTaxJurisInfo(responseXML);									
					loadShareholderTaxJurisDetails(responseXML);

					
					_resources.grids['taxJurisInfo'].getFooterToolbar().get('chkSync').setValue(_self.allowSync);
					if (_self.allowCheckbox)  
						_resources.grids['taxJurisInfo'].getFooterToolbar().get('chkSync').enable();
					else
						_resources.grids['taxJurisInfo'].getFooterToolbar().get('chkSync').disable();
				}
			}
		}
		
		,updateActionButtons: function()
		{			
			var selectedRecord = _resources.grids['taxJurisInfo'].getSelectedRecord();	
			
			if (selectedRecord)
			{
				if (selectedRecord.data['runMode'] == this.ADD)
				{
					_resources.grids['taxJurisInfo'].enableButton('modBtn');
					_resources.grids['taxJurisInfo'].enableButton('delBtn');
				}
				else
				{								
					if (_permissionsMap[this.MOD]
						&& selectedRecord.data['allowUpd'] == 'yes')			
					{
						_resources.grids['taxJurisInfo'].enableButton('modBtn');
					}
					else
					{
						_resources.grids['taxJurisInfo'].disableButton('modBtn');
					}
					
					if (_permissionsMap[this.DEL]
						&& selectedRecord.data['allowDel'] == 'yes')		
					{
						_resources.grids['taxJurisInfo'].enableButton('delBtn');
					}
					else
					{
						_resources.grids['taxJurisInfo'].disableButton('delBtn');
					}
				}
			}
			else
			{
				_resources.grids['taxJurisInfo'].disableButton('modBtn');
				_resources.grids['taxJurisInfo'].disableButton('delBtn');
			}		
		}	
		
		,openActionPopup: function(action)
		{
			if (action == this.ADD)
			{
				_resources.grids['taxJurisInfo'].clearSelectedRecord();
			}
			_resources.popups['taxJuris'].init(action);
			_resources.popups['taxJuris'].show();
		}
		
		,closeActionPopup: function()
		{
			_resources.popups['taxJuris'].hide();
		}
		
		,savePopup: function(action, data)
		{					
			if (action != this.DEL && _self.allowSync 			
				&& (_resources.popups['taxJuris'].getField('effDate').getValue() < _self.verifyDate))
			{
				var message = _translationMap['ErrEffectiveDate'] + _self.verifyDateString
							
				_resources.popups['taxJuris'].getField('effDate').markInvalid(message);
			}
			else
			{
				if (action == this.DEL && isNewRecord(_resources.grids['taxJurisInfo'].getSelectedRecord()))
				{
					_resources.grids['taxJurisInfo'].removeSelectedRecord();
					this.updatesFlag = (getUpdatedRecordCount() > 0);		
					this.closeActionPopup();
				
				}
				else
					sendWarnings(data, action);
			}						
		}
		
		,doUpdate: function()
		{						
			var updateStatus = null;
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler, null);			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)				
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{					
					updateStatus = DesktopWeb._FAIL;
				}
			}
			return updateStatus;
		}			
	}	
}	