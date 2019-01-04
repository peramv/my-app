/*********************************************************************************************
 * @file    SegEventDates.Controller.js
 * @author  Matira Thanetkulabut
 * @desc    Controller JS file for SEG Dates screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Account > Contract Information > SEG Dates
 *  
 *  History : 
 *  
 *  26-Sep-2016 Matira Thanetkulabut P0256533 T84091 MSF - Desktop
 *              - Initial
 */
 
DesktopWeb.ScreenController = function(){
    
    // PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _dtSegDatesInq = 'dtSegDatesReload';
	
	// PRIVATE METHODS ****************************************	
	function populateScreen(responseXML)
	{		
        _resources.grids['segDate'].loadData(IFDS.Xml.getNode(responseXML, '//SEGDates'));
    }
    
    // PUBLIC ITEMS *************************************
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
            
            var requestXML = IFDS.Xml.newDocument('data');
            IFDS.Xml.addSingleNode(requestXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
            IFDS.Xml.addSingleNode(requestXML, 'contractType', DesktopWeb._SCREEN_PARAM_MAP['ContractType']);	
            IFDS.Xml.addSingleNode(requestXML, 'contractVer', DesktopWeb._SCREEN_PARAM_MAP['ContractVer']);	
            
            DesktopWeb.Ajax.doSmartviewAjax(_dtSegDatesInq, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);			
		
            function responseHandler(success, responseXML, contextErrors)
            {	
                if (success)
                {
                    populateScreen(responseXML);
                }
            }
		}
		
	}	
}