/*********************************************************************************************
 * @file	LIFGainLoss.Controller.js
 * @author	Suchit Majumdar
 * @desc	Controller JS file for LIFGainLoss screen
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
	
	var _LIFGainLossReload = 'dtLIFGainLossReload';
	var _LIFGainLossProc = 'dtLIFGainLossProc';
	var _LIFGainLossInit = 'dtLIFGainLossInit';
	var _updatesAllowed = null;	

	// PRIVATE METHODS ****************************************	
	function populateDropdowns(dataXML)
	{			
		_resources.fields['yearFilterCombo'].loadData(IFDS.Xml.getNodes(dataXML, "*/List[@listName = 'lifPrevYears']"));		
	}

	function loadData(dataXML)
	{
		_updatesAllowed = IFDS.Xml.getNodeValue(dataXML, '*/UpdFlag/UpdAllowed').toLowerCase() == 'yes';		
		_resources.grids['lifGridDetails'].loadData(IFDS.Xml.getNode(dataXML, '*/transactionList'));
		_resources.fields['totalGainOrLossBox'].setValue(IFDS.Xml.getNodeValue(dataXML, '*/totalGainLoss/totGainLoss'));		
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML,"accountNum",DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			
			DesktopWeb.Ajax.doSmartviewAjax(_LIFGainLossInit, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{					
					_resources.fields['totalGainOrLossBox'].setValue('');
					populateDropdowns(responseXML);
				}
			}										
		}
		
		,doRefresh: function(yearVal)
		{
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(requestXML, "lifPrevYear", yearVal);
			
			DesktopWeb.Ajax.doSmartviewAjax(_LIFGainLossReload, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					loadData(responseXML);
				}
			}
		}
		
		,updateActionButton: function()
		{
			var selectedRecord = _resources.grids['lifGridDetails'].getSelectedRecord();
			if (selectedRecord && _updatesAllowed)
			{
				_resources.grids['lifGridDetails'].enableButton('updateBtn');
			}
		}
		
		,openGainLossPopup: function()
		{						
			_resources.popups['gainLossUpdate'].show();	
		}
		
		,saveGainLossUpdate: function(data)
		{
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, "transNumber", data['txnNum']);
			IFDS.Xml.addSingleNode(requestXML, "gainLoss", data['gainLoss']);
			
			DesktopWeb.Ajax.doSmartviewAjax(_LIFGainLossProc, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					loadData(responseXML);
					_resources.popups['gainLossUpdate'].hide();
				}
			}
		}
	}	
}	