/*********************************************************************************************
 * @file	DOTAndAddendum.Controller.js
 * @author 	Narin Suanlamyai
 * @desc	Controller JS file for Declaration of Trust and Addendum screen.
 *
 * History
 * 06 Jun 2017 Narin Suanlamyai P0263049 NetServer Modernization
 *             Replace xsl style to ExtJS style
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){	


	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _initDataXML = null;
	var _initView = 'dtDOTInit';

    var _nextStartRecNum = 1;
	var _requestRecNum = 25;
	
	// PRIVATE METHODS ****************************************	
	function doSearch(append)
	{
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(requestXML,"accountNum",DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
		IFDS.Xml.addSingleNode(requestXML,"startRecNum", (append)?_nextStartRecNum:1);
		IFDS.Xml.addSingleNode(requestXML,"requestRecNum",_requestRecNum);
		
		DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading'])
		
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				if (append)
				{
					_resources.grids['dotGrid'].appendData(IFDS.Xml.getNode(responseXML, '//OutputActionList'));
					
				}else{
					_resources.grids['dotGrid'].loadData(IFDS.Xml.getNode(responseXML, '//OutputActionList'));
				}
				
				// control more button
				_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
				//alert(_nextStartRecNum);
				if (_nextStartRecNum)
				{
					_resources.grids['dotGrid'].enableButton('moreBtn');
				}
				else
				{
					_resources.grids['dotGrid'].disableButton('moreBtn');
				}
				//alert(_nextStartRecNum);
			}
		}
	}
	
	// PUBLIC ITEMS *************************************
	return {
		
		updatesFlag: false	
				
		,init: function(res)
		{						
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			doSearch(false);
		}
		
		,clickHandle_moreBtn: function()
		{
			//alert(_nextStartRecNum);
			doSearch(true);
		}
	}	
}	