/*********************************************************************************************
 * @file	VersionFeatures.Controller.js
 * @author 	Suchit Majumdar
 * @desc	Controller JS file for Version Features screen.
 *
 * History
 * 06 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54444
 *             Correct the format of all date fields based on registry edit
 *             ,called displayMark
 *
 * 02 June 2017 Rattanaporn P. P0181067 FN01 CHG0049231 T85621
 *             Fix the issue that History button does not poppulate the data.
 * 
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
	var _initDataXML = null;
	var _initView = 'dtVerFeatReload';
	var _updateView = 'dtVerFeatUpdate';
	
	// PRIVATE METHODS ****************************************	
		function loadUrlFields()
		{
			_resources.fields['accountNumber'].setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			_resources.fields['contractType'].setValue(DesktopWeb._SCREEN_PARAM_MAP['ContractType']);
			_resources.fields['versionNumber'].setValue(DesktopWeb._SCREEN_PARAM_MAP['VersionNumber']);
		}

		function loadGridData(responseXML)
		{					
			_resources.grids['versionFeatureGrid'].loadData(IFDS.Xml.getNodes(responseXML, '*/VerFeatures'));
		}

	
		function populateDropdowns()
		{
			var selectedRecord = _resources.grids['versionFeatureGrid'].getSelectedRecord();
			selectedCotacctoptionid= selectedRecord.data.cotacctoptionid;
			_resources.popups['versionFeaturePopup'].getField('status').getStore().loadData(IFDS.Xml.getNodes(_initDataXML, "//List[@listName = 'StatusList']"));
			_resources.popups['versionFeaturePopup'].getField('options').getStore().loadData(IFDS.Xml.getNodes(_initDataXML, "//List[@listName = 'OptionsList']"));
		}

		function buildUpdateXML()
		{
			var xml = IFDS.Xml.newDocument( "Mstr" );

			var records = _resources.grids['versionFeatureGrid'].getAllRecords();
			
			for (var i = 0; i < records.length; i++)
			{
				if (records[i].data['runMode'] != "")
				{
					var recordXML = IFDS.Xml.addSingleNode(xml, "Element");
					IFDS.Xml.addSingleNode(recordXML, "runMode", records[i].data['runMode']);					
					IFDS.Xml.addSingleNode(recordXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
					IFDS.Xml.addSingleNode(recordXML, 'contractType', DesktopWeb._SCREEN_PARAM_MAP['ContractType']);
					IFDS.Xml.addSingleNode(recordXML, 'contractVer',DesktopWeb._SCREEN_PARAM_MAP['VersionNumber']);
					IFDS.Xml.addSingleNode(recordXML, "cotacctoptionid", records[i].data['cotacctoptionid']);
					IFDS.Xml.addSingleNode(recordXML, "featureCode", records[i].data['featureCode']);
					IFDS.Xml.addSingleNode(recordXML, 'optionCode', _self.getListCode('OptionsList', records[i].data['option']));
					IFDS.Xml.addSingleNode(recordXML, 'stat', _self.getListCode('StatusList', records[i].data['status']));
				}
			}
			return xml;
		}			

	
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'	
		,updatesFlag: false	
				
		,init: function(res)
		{						
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML,"account",DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
			IFDS.Xml.addSingleNode(requestXML,"contractType",DesktopWeb._SCREEN_PARAM_MAP['ContractType']);				
			IFDS.Xml.addSingleNode(requestXML,"contractVer",DesktopWeb._SCREEN_PARAM_MAP['VersionNumber']);
			IFDS.Xml.addSingleNode(requestXML,"startRecNum",'');
			IFDS.Xml.addSingleNode(requestXML,"requestRecNum",'');
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading'])
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					_initDataXML = responseXML;
					loadUrlFields();
					loadGridData(responseXML);
				}
			}
		}

		,openActionPopup: function(action)
		{
			populateDropdowns();
			_resources.popups['versionFeaturePopup'].init(action);
			_resources.popups['versionFeaturePopup'].show();
		}

		,closeActionPopup: function()
		{
			_resources.popups['versionFeaturePopup'].hide();
		}
		,savePopup: function(action, data)
		{
			_resources.grids['versionFeatureGrid'].updateSelectedRecord(data);
			this.updatesFlag = true;		
			_resources.popups['versionFeaturePopup'].hide();
		}

		,doUpdate: function()
		{
			var updateStatus = null;
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler);
			function responseHandler(success, responseXML)
			{
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

		,openAdminPopup: function(recType)
		{
			var adminData = {};
			var title =  "Version Features - Admin";
			var selectedRecord = _resources.grids['versionFeatureGrid'].getSelectedRecord();
			adminData['userName'] = selectedRecord.data['userName'];
			adminData['procDate'] = selectedRecord.data['processDate'];
			adminData['modUser'] = selectedRecord.data['modUser'];
			adminData['modDate'] = selectedRecord.data['modDate']
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			

		}

		,openHistoricalPopup: function()
		{
			var viewParam = {}
			var title = "Version Features - History"
			viewParam['auditType'] = 'VerFeatures';
			viewParam['searchValue1'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
			viewParam['searchValue2'] = DesktopWeb._SCREEN_PARAM_MAP['ContractType'];
			viewParam['searchValue3'] = DesktopWeb._SCREEN_PARAM_MAP['VersionNumber'];
			viewParam['searchValue4'] = _resources.grids['versionFeatureGrid'].getSelectedRecord().data["featureCode"];
			viewParam['searchValue5'] = _self.getListCode('OptionList',_resources.grids['versionFeatureGrid'].getSelectedRecord().data['option']);
			_resources.popups['history'].init(title, 'dtHistoricalInfo', viewParam, true);
			_resources.popups['history'].show();
		}

		,getListValueDesc: function(listName, value)
		{
			var valueDesc = null
			valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");
			return valueDesc;
		}

		,getListCode: function(listName, code)
		{
			var valueDesc = null
			valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = '" + listName + "']/Element[value = '" + code + "']/code");
			return valueDesc;
		}

		,checkModifyButton: function(responseXML)
		{
			var selectedRecord = _resources.grids['versionFeatureGrid'].getSelectedRecord();
			if(selectedRecord.data['featureCode'] =='02'){
				_resources.grids['versionFeatureGrid'].enableButton('modBtn');
				_resources.grids['versionFeatureGrid'].enableButton('adminBtn');
				_resources.grids['versionFeatureGrid'].enableButton('historyBtn');
			}
			else{
				_resources.grids['versionFeatureGrid'].disableButton('modBtn');
				_resources.grids['versionFeatureGrid'].disableButton('adminBtn');
				_resources.grids['versionFeatureGrid'].disableButton('historyBtn');


			}
		}

	}	
}	