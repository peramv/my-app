/*********************************************************************************************
 * @file	BeneAllocHist.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for Beneficiary Allocation History screen.
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
	
	var _reloadView = 'dtBenAllocHistReload';
	var _dataXML =  null;
		
	// PRIVATE METHODS ****************************************	
	function loadAllocHist()
	{		
		_resources.grids['allocHistory'].loadData(IFDS.Xml.getNode(_dataXML, '*/BeneficiaryAllocHistInfo'));		
	}
	
	function loadAllocDetails(index)
	{		
		_resources.grids['allocDetails'].loadData(IFDS.Xml.getNode(_dataXML, '*/BeneficiaryAllocHistInfo/BeneficiaryAllocDetail[' + index + ']'));		
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(requestXML, "transId", DesktopWeb._SCREEN_PARAM_MAP['TransId']);
			
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{											
				if (success)
				{
					_dataXML = responseXML;
					loadAllocHist();					
				}
			}
		}
		
		,updateSelectedAllocRecord: function()
		{
			var selectedRecord = _resources.grids['allocHistory'].getSelectedRecord();
			if (selectedRecord)
			{
				var recordIndex = _resources.grids['allocHistory'].getRecordIndex(selectedRecord);
				loadAllocDetails(recordIndex + 1);				
			}
			else
			{
				_resources.grids['allocDetails'].clearData();
			}
		}		
	}	
}	