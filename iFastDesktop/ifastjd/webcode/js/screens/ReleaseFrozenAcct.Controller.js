/*********************************************************************************************
 * @file	ReleaseFrozenAcct.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for ReleaseFrozenAcct screen
 *********************************************************************************************/
 /*
 *  History :
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.  
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = 'dtRelFrozenAcctInit';
	var _procView = 'dtRelFrozenAcctProc';
	
	// PRIVATE METHODS ****************************************	
	function populateDropdowns(initViewXML)
	{		
		_resources.fields['stopPurchase'].loadData(IFDS.Xml.getNode(initViewXML, "*/List[@listName = 'StopPurchaseList']"));
		_resources.fields['stopRedemption'].loadData(IFDS.Xml.getNode(initViewXML, "*/List[@listName = 'StopRedempList']"));
		_resources.fields['exchangeOut'].loadData(IFDS.Xml.getNode(initViewXML, "*/List[@listName = 'StopTransferOutList']"));
		_resources.fields['exchangeIn'].loadData(IFDS.Xml.getNode(initViewXML, "*/List[@listName = 'StopTransferInList']"));
		_resources.fields['reactivePAC'].loadData(IFDS.Xml.getNode(initViewXML, "*/List[@listName = 'ReactivePACSWPList']"));	
	}
	
	function populateScreen(initViewXML)
	{
		_resources.fields['statementDate'].setValue(IFDS.Xml.getNodeValue(initViewXML, "*/ListSelection[@id = 'RmStmtDateList']"));
		_resources.fields['stopNFU'].setValue(IFDS.Xml.getNodeValue(initViewXML, "*/ListSelection[@id = 'StopNFUList']"));
		
		_resources.fields['stopPurchase'].setValue(IFDS.Xml.getNodeValue(initViewXML, "*/ListSelection[@id = 'StopPurchaseList']"));
		_resources.fields['stopPurchase'].enable();
		_resources.fields['stopRedemption'].setValue(IFDS.Xml.getNodeValue(initViewXML, "*/ListSelection[@id = 'StopRedempList']"));
		_resources.fields['stopRedemption'].enable();
		_resources.fields['exchangeOut'].setValue(IFDS.Xml.getNodeValue(initViewXML, "*/ListSelection[@id = 'StopTransferOutList']"));
		_resources.fields['exchangeOut'].enable();
		_resources.fields['exchangeIn'].setValue(IFDS.Xml.getNodeValue(initViewXML, "*/ListSelection[@id = 'StopTransferInList']"));
		_resources.fields['exchangeIn'].enable();
		_resources.fields['reactivePAC'].setValue(IFDS.Xml.getNodeValue(initViewXML, "*/ListSelection[@id = 'ReactivePACSWPList']"));
		_resources.fields['reactivePAC'].enable();
		
		if (IFDS.Xml.getNodeValue(initViewXML, "*/Permissions/updPerm").toLowerCase() == 'yes')
		{
			_resources.buttons['update'].enable();
		}
		else
		{
			_resources.buttons['update'].disable();
		}
		
		Ext.getCmp('accountFieldSet').enable();		
	}
	
	function resetScreen()
	{
		_resources.fields['statementDate'].reset();
		_resources.fields['stopNFU'].reset();
		
		_resources.fields['stopPurchase'].reset()
		_resources.fields['stopPurchase'].disable();
		_resources.fields['stopRedemption'].reset()
		_resources.fields['stopRedemption'].disable();
		_resources.fields['exchangeOut'].reset();
		_resources.fields['exchangeOut'].disable();
		_resources.fields['exchangeIn'].reset();
		_resources.fields['exchangeIn'].disable();
		_resources.fields['reactivePAC'].reset()
		_resources.fields['reactivePAC'].disable();
		
		_resources.buttons['update'].disable();
		
		Ext.getCmp('accountFieldSet').disable();
	}
	// PUBLIC ITEMS *************************************
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
		}
		
		,doLookup: function(account)
		{
			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, "account", account);
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Searching']);			
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{									
					populateDropdowns(responseXML);
					populateScreen(responseXML);
				}								
				else
				{
					resetScreen();
				}			
			}
		}
		
		,doUpdate: function()
		{
			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, "account", _resources.fields['account'].getValue());
			IFDS.Xml.addSingleNode(requestXML, "rmStmtDate", _resources.fields['statementDate'].getValue());
			IFDS.Xml.addSingleNode(requestXML, "stopNFU", _resources.fields['stopNFU'].getValue());
			IFDS.Xml.addSingleNode(requestXML, "stopPurchase", _resources.fields['stopPurchase'].getValue());
			IFDS.Xml.addSingleNode(requestXML, "stopRedemp", _resources.fields['stopRedemption'].getValue());
			IFDS.Xml.addSingleNode(requestXML, "stopTransferIn", _resources.fields['exchangeIn'].getValue());
			IFDS.Xml.addSingleNode(requestXML, "stopTransferOut", _resources.fields['exchangeOut'].getValue());
			IFDS.Xml.addSingleNode(requestXML, "reactivePACSWP", _resources.fields['reactivePAC'].getValue());
						
			DesktopWeb.Ajax.doSmartviewAjax(_procView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);			
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{									
					DesktopWeb.Util.displayInfo(_translationMap['Account'] + " " + _resources.fields['account'].getValue() + " " + _translationMap['UpdateSuccessful']);
					resetScreen();
				}														
			}
		}
	}	
}	