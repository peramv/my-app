/*********************************************************************************************
 * @file	AMSAssetInfo.Controller.js
 * @author	Siva Chandran
 * @desc	Controller JS file for AMS Asset Information screen
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
	
	var _initView = 'dtAMSAssetInit';
	var _curSearchType =  null;	
	
	// PRIVATE METHODS ****************************************
	function populateScreen(dataXML)
	{
		_resources.fields['account'].setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		_resources.fields['shareholder'].setValue(IFDS.Xml.getNodeValue(dataXML, '*/AMSAssetInfo/shrNum'));
		_resources.fields['name'].setValue(IFDS.Xml.getNodeValue(dataXML, '*/AMSAssetInfo/name'));
		
		_curSearchType = DesktopWeb._SCREEN_PARAM_MAP['searchType'];		
		_resources.fields['searchType'].setValue(_curSearchType);		
		displayGrid(_curSearchType);
		populateGrid(_curSearchType, dataXML);				
	}
	
	function displayGrid(type)
	{
		for (var i in _resources.grids)
		{
			_resources.grids[i].hide();
		}
		
		_resources.grids[type + 'Info'].show();
	}
	
	function populateGrid(type, dataXML)
	{
		_resources.grids[type + 'Info'].loadData(dataXML);
	}
	
	function sendReloadRequest(callback)
	{
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(requestXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(requestXML, "searchType", DesktopWeb._SCREEN_PARAM_MAP['searchType']);			
		
		DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']); 
		
		function responseHandler(success, responseXML)
		{
			DesktopWeb.Util.debugXML(responseXML);						
			if (success)
			{									
				callback(responseXML);					
			}
		}
	}
	
	// PUBLIC ITEMS *************************************
	return {
		
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(requestXML, "searchType", DesktopWeb._SCREEN_PARAM_MAP['searchType']);			
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']); 
			
			function responseHandler(success, responseXML)
			{
				DesktopWeb.Util.debugXML(responseXML);						
				if (success)
				{									
					populateScreen(responseXML);					
				}
			}
		}
		
		,onChangeSearchType: function()
		{
			var searchType = _resources.fields['searchType'].getValue();
			if (searchType != "" && searchType != _curSearchType)
			{
				_curSearchType = searchType;
				sendReloadRequest(callback);
			}
			else
			{
				_resources.fields['searchType'].setValue(_curSearchType);
			}
			
			function callback(responseXML)
			{
				displayGrid(_curSearchType)
				populateGrid(_curSearchType, responseXML);
			}	
		}
	}
}