/*********************************************************************************************
 * @file	RESPZeroRpymt.Controller.js	
 * @author	Rod Walker
 * @desc	Controller JS file for RESP Zero Grant Repayment screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached. 
 *  
 *	14 Jun 2016 Watchara Th. P0241773 CHG0045794 DFT0064894 T83084
 *					- Ignored unexpected error message when accessing the screen.
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initDataXML = null;
	var _reloadView = 'dtRESPGrantRpymtReload';
	var _validateView = 'dtRESPGrantRpymtVldtn';
	var _updateView = 'dtRESPGrantRpymtUpd';
	var _permissionsMap = {};
	
	// PRIVATE METHODS ****************************************	
	
	function storePermissions(initViewXML)
	{				
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//userPermissions/modPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//userPermissions/delPerm').toLowerCase() == 'yes';
	}
	
	function populateScreen(responseXML)
	{		
		_resources.fields['planNumber'].setValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/planNo"));
		_resources.fields['matureDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/matureDt")));
		_resources.fields['grandfathered'].setValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/grandFather").toUpperCase());
		_resources.fields['reportedToHRDC'].setValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/repHRDC").toUpperCase());
		_resources.fields['preContribution'].setValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/pre98Contr").toUpperCase());
		_resources.fields['respStatus'].setValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/respStat"));
		_resources.fields['inceptionDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/incepDt")));
		_resources.fields['siblingOnly'].setValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/siblingOnly").toUpperCase());
		_resources.fields['reportingRequired'].setValue(IFDS.Xml.getNodeValue(responseXML, "*/RESPGrantRpymtInfo/RESPAccountInfo/repReqd").toUpperCase());
				
		_resources.grids['grantPayment'].loadData(IFDS.Xml.getNode(responseXML, '*/RESPGrantRpymtInfo/GrantRpymtRecords'));	
	}
	
	function buildUpdateXML()
	{
		var xml = IFDS.Xml.newDocument( "data" );
	
		var records = _resources.grids['grantPayment'].getAllRecords();
		
		for (var i = 0; i < records.length; i++)
		{
			if (records[i].data['runMode'] != "")
			{
				var recordXML = IFDS.Xml.addSingleNode(xml, "GrantRpymtUpd");
				IFDS.Xml.addSingleNode(recordXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
				IFDS.Xml.addSingleNode(recordXML, "runMode", records[i].data['runMode']);
				IFDS.Xml.addSingleNode(recordXML, "transType", records[i].data['transType']);
				IFDS.Xml.addSingleNode(recordXML, "transDate", DesktopWeb.Util.getSMVDateValue(records[i].get("transDate")));
				IFDS.Xml.addSingleNode(recordXML, "hrdcTransId", records[i].data['hrdcTransId']);
				IFDS.Xml.addSingleNode(recordXML, "dateSent", DesktopWeb.Util.getSMVDateValue(records[i].get("dateSent")));
				IFDS.Xml.addSingleNode(recordXML, "amt", records[i].data['amt']);
				IFDS.Xml.addSingleNode(recordXML, "reported", records[i].data['reported']);
				IFDS.Xml.addSingleNode(recordXML, "normalRvrse", records[i].data['normalRvrse']);
			}
		}
	
		return xml;
	}	
	
	// PUBLIC ITEMS *************************************
	return {
		
		MOD: 'mod'
		,DEL: 'del'
		,CANCEL: 'cancel'
		,updatesFlag: false
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_resources.grids['grantPayment'].disableAllButtons();
						
			var viewParamXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(viewParamXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);									 	
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Loading'], null, ['15']);			
			
			function responseHandler(success, responseXML)
			{
				DesktopWeb.Util.debugXML(responseXML);
				if (success)
				{					
					storePermissions(responseXML);
					populateScreen(responseXML);
				}											
			}
		}
		
		,updateActionButtons: function()
		{
			var selectedRecord = _resources.grids['grantPayment'].getSelectedRecord();			
			if (selectedRecord)
			{
				if (_permissionsMap[_self.MOD])
				{
					if (selectedRecord.data['runMode'] == _self.CANCEL)
					{
						_resources.grids['grantPayment'].disableButton('modBtn');
						_resources.grids['grantPayment'].disableButton('cancelBtn');
					}
					else
					{
						if (selectedRecord.data['reported'].toLowerCase() == 'yes')
						{
							_resources.grids['grantPayment'].disableButton('modBtn');
							_resources.grids['grantPayment'].enableButton('cancelBtn');
						}
						else
						{
							_resources.grids['grantPayment'].enableButton('modBtn');
							_resources.grids['grantPayment'].disableButton('cancelBtn');
						}
					} 
				}
				else
				{
					_resources.grids['grantPayment'].disableButton('modBtn');
					_resources.grids['grantPayment'].disableButton('cancelBtn');
				}
				
				if (_permissionsMap[_self.DEL] && selectedRecord.data['reported'].toLowerCase() != 'yes')
				{					
					_resources.grids['grantPayment'].enableButton('delBtn');
				}
				else
				{
					_resources.grids['grantPayment'].disableButton('delBtn');
				}				
			}
			else
			{
				_resources.grids['grantPayment'].disableAllButtons();
			}
		}
		
		,openActionPopup: function(action)
		{			
			_resources.popups['repaymentPopup'].action = action;
			_resources.popups['repaymentPopup'].show();						
		}
		
		,savePopup: function(action, data)
		{
			var selectedRecord = _resources.grids['grantPayment'].getSelectedRecord();
			var viewParamXML = IFDS.Xml.newDocument('data');
			
			IFDS.Xml.addSingleNode(viewParamXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(viewParamXML, 'runMode', data['runMode']);
			IFDS.Xml.addSingleNode(viewParamXML, 'transType', selectedRecord.data['transType']);
			IFDS.Xml.addSingleNode(viewParamXML, 'transDate', DesktopWeb.Util.getSMVDateValue(data['transDate']));
			IFDS.Xml.addSingleNode(viewParamXML, 'hrdcTransId', selectedRecord.data['hrdcTransId']);
			IFDS.Xml.addSingleNode(viewParamXML, 'dateSent', DesktopWeb.Util.getSMVDateValue(selectedRecord.data['dateSent']));
			IFDS.Xml.addSingleNode(viewParamXML, 'amt', selectedRecord.data['amt']);
			IFDS.Xml.addSingleNode(viewParamXML, 'reported', selectedRecord.data['reported']);
			IFDS.Xml.addSingleNode(viewParamXML, 'normalRvrse', selectedRecord.data['normalRvrse']);
												 
			DesktopWeb.Util.debugXML(viewParamXML);												 	
			DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Processing']);	
			
			function responseHandler(success, responseXML)
			{
				DesktopWeb.Util.debugXML(responseXML);
				if (success)
				{									
					_resources.grids['grantPayment'].updateSelectedRecord(data);
					_resources.popups['repaymentPopup'].hide();
					_self.updatesFlag = true;
				}											
			}
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler);
			
			function responseHandler(success, responseXML)
			{
				DesktopWeb.Util.debugXML(responseXML);
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