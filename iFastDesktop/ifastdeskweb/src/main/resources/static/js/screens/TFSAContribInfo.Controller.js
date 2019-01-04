/*********************************************************************************************
 * @file	TFSAContribInfo.Controller.js
 * @author	
 * @desc	Controller JS file for TFSA Contribution Information screen.
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
		
	var _initView = 'dtAcctContribInq';	
		
	// PRIVATE METHODS ****************************************
	function loadTfsaContribInfo(initViewXML)
	{				
		_resources.grids['tfsaAcctContribInfo'].loadData(IFDS.Xml.getNode(initViewXML, '/*//AcctContribList'), null);
	}			
		
	// PUBLIC ITEMS *************************************
	return {
				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;							
			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
				
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']); 
			function responseHandler(success, responseXML)
			{						
				if (success)
				{									
					loadTfsaContribInfo(responseXML);									
				}
			}
		}						
	}	
}	