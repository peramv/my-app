/*********************************************************************************************
 * @file	RESPDiploma.Controller.js
 * @author	Manoj Kumar
 * @desc	Controller JS file for RESP Diploma Screen
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
	var fieldsData = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
		
	var _reloadView = 'dtRESPDipReload';
	var _initDataXML = null;
	
	function loadRESPDiplomaDetails(responseXML)
	{	
		_resources.grids['respDiplomaList'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'RESPList']"));
		_resources.fields['allocation'].loadData(IFDS.Xml.getNode(responseXML,"//List[@listName = 'AllocationList']"));
		_resources.fields['age'].loadData(IFDS.Xml.getNode(responseXML,"//List[@listName = 'AgeList']"));		
	}
	

	

	// PUBLIC ITEMS *************************************
	return {
		ageLower: ''
		,commitCode: ''
		,init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, null, responseHandler, _translationMap['ProcMsg_Loading'])			

			function responseHandler(success, responseXML)
			{
				if (success)
				{
					_initDataXML = responseXML;
					loadRESPDiplomaDetails(responseXML);
				}											
			}
		}
				
		,updateRespDiplomaDetails: function()
		{
 
			fieldsData = _resources.grids['respDiplomaList'].getSelectedRecord().data;
			_resources.fields['allocationType'].setValue(IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = 'AllocType']/Element/value"));
			_resources.fields['maxIssued'].setValue(fieldsData.maxIssued);
			_resources.fields['parentFund'].setValue(fieldsData.parentFund);
			_self.updateAllocation();
		}
		
		,updateAllocation: function()
		{
		_resources.fields['allocation'].reset();
		_self.updateSearchAge();
		_resources.fields['age'].setDisabled(true);
		}


		,updateSearchAge: function()
		{	
			_resources.fields['age'].reset();
			_resources.grids['allocPercentageList'].clearData();
			_resources.fields['age'].setDisabled(false);
		}
		
		,populateAllocPercentList: function(age)
		{										
			_self.ageLower = age;
			//incident #2864346 changes to get RESP diploma selection and filter accordinly 
			_self.commitCode = fieldsData.name
			var allocation = _resources.fields['allocation'].getValue();
			_resources.grids['allocPercentageList'].loadData(IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'AllocationPrcntList_"+allocation+"']"));

		}				
	}	
}