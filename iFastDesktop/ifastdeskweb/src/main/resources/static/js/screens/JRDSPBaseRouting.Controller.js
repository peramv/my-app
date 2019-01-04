/*********************************************************************************************
 * @file	JRDSPTestRouting.Controller.js
 * @author	Balaji Rajendra babu
 * @desc	Controller JS file for sample routing screen.
 *********************************************************************************************/
 


 
DesktopWeb.ScreenController = function(){
	
	
	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _reloadView = 'dtBenAllocHistReload';
	var _dataXML =  null;
	var _service 				= null;
	var _contextController=null;
		
	// PRIVATE METHODS ****************************************	
	
	
	function route(contextPath,routePath){
		
		_contextController=contextPath;
		
		
		//alert('Routing to path '+contextPath+routePath);
		
		var requestXML = IFDS.Xml.newDocument('data');
		
		//_service = getInitService(DesktopWeb._SCREEN_PARAM_MAP['jrdsp_sample_screen']);

		_service = "jrdspSampleScreen";
/*		DesktopWeb.Ajax.doSmartviewAjax(_service
				, (runMode == 'init')?{ignoreErrorCode: '15'}:null
				, requestXML, responseHandler, _translationMap['Loading']);
		*/
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST',requestXML);
		
		
	}

	// PUBLIC ITEMS *************************************
	return {
		//fields:_resources.fields,
		
		init: function(res)
		{				
			_resources = res;
			//_resources.fields['reportingFFILabel'].show();//.setValue(getDisplay('reportingFFIList', record.data['reportingFFI']);
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			
/*			var requestXML = IFDS.Xml.newDocument('data');
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
			}*/
		},
		doRoute: function(contextPath,routePath){
			console.log('Context to route is : '+ contextPath);
			console.log('Path to route is : '+ routePath);
			
			
			
			//Call the function for the actual functionality
			
			route(contextPath,routePath);
			
		}
		
		
/*		,updateSelectedAllocRecord: function()
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
		}*/		
	}	
}	