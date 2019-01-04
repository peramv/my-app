/*********************************************************************************************
 * @file	ClassSetup_Search.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Search screen, part of Class Setup flow
 *********************************************************************************************/
 /*
 * Procedure: ClassSetup_Search.Controller.js
 *
 * Purpose  : Class Search screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Class Search screens
 *
 * History  : 
 *  12 Nov 2012 H.Sartsangchan Created. 
 *          IN3135980 Load type validation does not work properly on Class setup
 *          - Replace Fund Load Group List Information depend on fund while do class search
 *                                    
 *  27 Jun 2013 N. Suanlamyai P0214690 T53774
 *          - Add new parameter to indicate a fund supports multiple distribution types
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *             - Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration.
 *             
 *	 8 Jan 2018	Sreejith A P0274727 P0274727-1
 *			- Added new screen "settle day controls"
 *
 *   1 Feb 2018	Sreejith.A P0274726 P0274726-49
 *			- Added new Popup for remarks setup
 * 
 *   2 Mar 2018	Sreejith.A P0274726 P0274726-88
 *			- Tuning and consolidating remarks section
 *
 *	22 Mar 2018 Sreejith.A P0274727 P0274727-88
 *			- T+0 Project P0274727 changes revert from 18.3
 *
 *	12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 */
 
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _classSearchView = 'classSearch';
	var _initView = 'dtClassSetupInit';
	var _inqView = 'dtClassSetupInq';
	var _remarksInqView = 'dtClassRemarksInq';
	var _remarksValView = 'dtClassRemarksVal';
	var _remarksUpdateView = 'dtClassRemarksUpd';
	var _dtHistoryService = 'dtHistoricalInfo';
	var _permissionsMap = null;
	var _defaultValuesXML = null;
	var _changeFlag = false;
	var _remarksInqDataXML = null;
	var _nextUUID = 1;
	
	// PRIVATE METHODS ****************************************
	function storePermissions(initXML)
	{
		var permissionsNode = IFDS.Xml.getNode(initXML, '//Permissions');
		_permissionsMap = {};
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(permissionsNode, 'inq');
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(permissionsNode, 'add');
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(permissionsNode, 'mod');
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(permissionsNode, 'del');		
	}
	
	function storeDefaultValues(initXML)
	{
		_defaultValuesXML = IFDS.Xml.getNode(initXML, '//DefaultValues');		
	}
	
	function loadClassData(classSearchXML)
	{		
		_resources.grids['classes'].loadData(IFDS.Xml.getNode(classSearchXML, '/*//Classes'), null);
	}
	
	function goToScreen(screenName, addtlParams)
	{
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_' + screenName;
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];			
		urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
		Ext.apply(urlParams, addtlParams);
					
		window.location = DesktopWeb.Ajax.buildURL(urlParams);
	}
	
	function buildInitialClassDataXML()
	{
		var xml = IFDS.Xml.newDocument("data");
		
		var fundRec = _resources.fields['fund'].selectedRecord;			
		IFDS.Xml.addSingleNode(xml, 'fundCode', fundRec.data['fundCode']);
		IFDS.Xml.addSingleNode(xml, 'fundCategory', fundRec.data['fundCategory']);
		IFDS.Xml.addSingleNode(xml, 'fundName', fundRec.data['fundName']);
		IFDS.Xml.addSingleNode(xml, 'sponsor', fundRec.data['sponsor']);
		IFDS.Xml.addSingleNode(xml, 'IWTDomiciledFund', fundRec.data['IWTDomiciledFund']);
		IFDS.Xml.addSingleNode(xml, 'IWTEnabled', fundRec.data['IWTEnabled']);
		IFDS.Xml.addSingleNode(xml, 'fundERISAOptn', fundRec.data['fundERISAOptn']);
		IFDS.Xml.addSingleNode(xml, 'fundERISACalcLevel', fundRec.data['fundERISACalcLevel']);
		
		var initialDataNodes = IFDS.Xml.getNodes(_defaultValuesXML, "*");
		
		for (var i = 0; i < initialDataNodes.length; i++)
		{
			if ((initialDataNodes[i].nodeName != 'GIAAttributes' && initialDataNodes[i].nodeName != 'IntConfig')  
				|| (initialDataNodes[i].nodeName == 'GIAAttributes' && fundRec.data['fundCategory'].toLowerCase() == 'g')
				|| (initialDataNodes[i].nodeName == 'IntConfig' && (fundRec.data['fundCategory'].toLowerCase() == 'g' || fundRec.data['fundCategory'].toLowerCase() == 'd')))
			{
				IFDS.Xml.appendNode(xml, initialDataNodes[i]);
			}
		}
				
		return xml;		
	}
	
	function buildScreenDefListXML()
	{
		var listXML = IFDS.Xml.newDocument("Screens");		
		var screenXML = null;
		
		//BasicInfo
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "BasicInfo");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['BasicInfo']);		
		
		//TradeConfig
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "TradeConfig");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['TradeConfig']);		
		
		//DistConfig
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "DistConfig");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['DistConfig']);		
		
		//PriceInfo
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "PriceInfo");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['PriceInfo']);		

		//FeeConfig
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "FeeConfig");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['FeeConfig']);		
		
		//FeeModelConfig
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "FeeModelConfig");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['FeeModelConfig']);	
		
		//Event Schedule
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "EventFreq");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['EventFreq']);
		
		//TradeDayControls		
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "TradeDayCtrls");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['TradeDayCtrls']);	
		
		//SettleDayControls		
		var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
		IFDS.Xml.addSingleNode(screenXML, "id", "SettleDayCtrls");
		IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['SettleDayCtrls']);

		if (_resources.fields['fund'].selectedRecord.data['fundCategory'].toLowerCase() == 'g')		
		{
			//GIAAttributes
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "GIAAttributes");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['GIAAttributes']);
		}
		
		if (_resources.fields['fund'].selectedRecord.data['fundCategory'].toLowerCase() == 'g'
			|| _resources.fields['fund'].selectedRecord.data['fundCategory'].toLowerCase() == 'd')
		{
			//IntConfig
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "IntConfig");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['IntConfig']);
		}
				
		return listXML;
	}
   
   function updateInitData(responseXML,callbackfn)
	{            
      DesktopWeb.Ajax.doRetrieveCache(['InitData'], responseHandler, _translationMap['ProcMsg_Loading'])
      function responseHandler(cacheinitdata)
		{	         
         var _initDataXML = IFDS.Xml.getNode(cacheinitdata, 'InitData/*');	
         var ClassSetupInitResponseNode = IFDS.Xml.getNode(_initDataXML, "//dtClassSetupInitResponse");
         if (IFDS.Xml.getNode(ClassSetupInitResponseNode, "List[@id = 'FundLoadGrpList']") != null)
         {
            IFDS.Xml.deleteNode(IFDS.Xml.getNode(ClassSetupInitResponseNode,"List[@id = 'FundLoadGrpList']"));
            IFDS.Xml.appendNode(ClassSetupInitResponseNode,IFDS.Xml.getNode(responseXML,"dtClassSetupInqResponse/List[@id = 'FundLoadGrpList']"));
         }
         if(IFDS.Xml.getNode(ClassSetupInitResponseNode, "ListSelection[@id = 'FundLoadGrpList']") != null)
         {
            IFDS.Xml.deleteNode(IFDS.Xml.getNode(ClassSetupInitResponseNode,"ListSelection[@id = 'FundLoadGrpList']"));
            IFDS.Xml.appendNode(ClassSetupInitResponseNode,IFDS.Xml.getNode(responseXML,"dtClassSetupInqResponse/ListSelection[@id = 'FundLoadGrpList']"));                        
         }
         DesktopWeb.Ajax.doUpdateCache({InitData: _initDataXML}, callbackfn);                      
      }           
	}
    //Populate grid data to remarks main popup
    function loadFundClsRemarks()
    {
    	updateGridBtns();
    	var requestXML = IFDS.Xml.newDocument('data');
    	IFDS.Xml.addSingleNode(requestXML, 'fundCode', _resources.fields['fund'].getValue());				
    	IFDS.Xml.addSingleNode(requestXML, 'classCode', _resources.grids['classes'].getSelectedRecord().data['classCode']);
    	DesktopWeb.Ajax.doSmartviewAjax(_remarksInqView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);	

    	function responseHandler(success, responseXML)
    	{
    		if (success && _permissionsMap['inq'] == 'yes')
    		{
    			_remarksInqDataXML = responseXML;
    			populateScreen(responseXML);
    			populateDropdowns();						
    		}										
    	}
    }
   	
	 function populateScreen(remInqDataXML)
	 {		
		 _resources.grids['grdRemarks'].loadData(IFDS.Xml.getNode(remInqDataXML, '*/Remarks'));
		 if(_permissionsMap['add'] == 'yes')
		 {
			 _resources.grids['grdRemarks'].enableButton('addBtn');
		 } else {
			 _resources.grids['grdRemarks'].disableButton('addBtn');
		 }
	 }
	 
	 function populateDropdowns()
	 {
		 var remarksTypFld = _resources.popups['RemarkModifyPopup'].getField('remarkType');
		 var reaosnFld = _resources.popups['RemarkModifyPopup'].getField('reason');

		 if (IFDS.Xml.getNode(_remarksInqDataXML, "*//List[@id = 'RemarksTypeList']"))
		 {
			 remarksTypFld.loadData(IFDS.Xml.getNode(_remarksInqDataXML, "*//List[@id = 'RemarksTypeList']"));
		 }
		 if (IFDS.Xml.getNode(_remarksInqDataXML, "*//List[@id = 'ReasonList']"))
		 {
			 reaosnFld.loadData(IFDS.Xml.getNode(_remarksInqDataXML, "*//List[@id = 'ReasonList']"));
		 }
		 //Set default dropdown values from list
		 var defaultRemarksTyp = IFDS.Xml.getNodeValue(_remarksInqDataXML, "/*//ListSelection[@id = 'RemarksTypeList']");
		 if(defaultRemarksTyp.length > 0)
		 {
			 remarksTypFld.setValue(defaultRemarksTyp);
		 }
		 var defaultReason = IFDS.Xml.getNodeValue(_remarksInqDataXML, "/*//ListSelection[@id = 'ReasonList']");
		 if(defaultReason.length > 0)
		 {
			 reaosnFld.setValue(defaultReason);
		 }
	 }
	
	 function updateGridBtns(record)
	 {
		 var grid = _resources.grids['grdRemarks'];
		 grid.disableButton('modBtn');
		 grid.disableButton('delBtn');
		 grid.disableButton('hisBtn'); 
		 grid.disableButton('adminBtn'); 
		 
		 if(record)
		 {
			 if (record.data['runMode'] != _self.ADD)
			 {
				 grid.enableButton('hisBtn'); 
				 grid.enableButton('adminBtn'); 
			 }
			 if(_permissionsMap['mod'] == 'yes')
			 {
				 grid.enableButton('modBtn');
			 }
			 if(_permissionsMap['del'] == 'yes')
			 {
				 grid.enableButton('delBtn');
			 }
		 }
	 }
	 
	 //update data to grid store
	 function updateRemarkRecord(action, data)
	 {
		 if (action == _self.ADD)
		 {
			 data['runMode'] = _self.ADD;
			 _resources.grids['grdRemarks'].addRecord(data);
			 _resources.grids['grdRemarks'].selectLastRecord();
		 } else {
			 var remarkRec = _resources.grids['grdRemarks'].getSelectedRecord();
			 if (action == _self.DEL)
			 {
				 if(remarkRec.data['runMode'] == _self.ADD)
				 {
					 _resources.grids['grdRemarks'].removeSelectedRecord();
					 _resources.grids['grdRemarks'].selectFirstRecord();
				 } else {
					 data['runMode'] = _self.DEL;
					 _resources.grids['grdRemarks'].updateSelectedRecord(data);
					 _resources.grids['grdRemarks'].selectFirstRecord();
				 }
			 } else {
				 if(remarkRec.data['runMode'] != _self.ADD)
				 {
					 data['runMode'] = _self.MOD;
				 }
				 _resources.grids['grdRemarks'].updateSelectedRecord(data);
			 }
			 updateGridBtns(_resources.grids['grdRemarks'].getSelectedRecord());
		 }
		 _changeFlag = true;
		 _resources.popups['RemarkModifyPopup'].hide();
	 }
	
	 function buildUpdateXML(data)
	 {
		 var updateXML = IFDS.Xml.newDocument('data');
		 var remarksXML = null;
		 IFDS.Xml.addSingleNode(updateXML, 'fundCode', _resources.fields['fund'].getValue());
		 IFDS.Xml.addSingleNode(updateXML, 'classCode', _resources.grids['classes'].getSelectedRecord().data['classCode']);

		 if(data)
		 {
			 // for validate service
			 IFDS.Xml.addSingleNode(updateXML, 'processingMode', 'validate');	
			 remarksXML = IFDS.Xml.addSingleNode(updateXML, 'Remark');
			 addToXML(data);
		 } else { 
			 // for update service
			 IFDS.Xml.addSingleNode(updateXML, 'processingMode', 'update');		
			 remarksXML = IFDS.Xml.addSingleNode(updateXML, 'Remarks');		
			 var store = _resources.grids['grdRemarks'].getStore();

			 var newRecords = store.query('runMode', _self.ADD);
			 newRecords.each(addToXML);				
			 var modRecords = store.query('runMode', _self.MOD);
			 modRecords.each(addToXML);				
			 var delRecords = store.query('runMode', _self.DEL);
			 delRecords.each(addToXML);				
		 }
		 return updateXML;

		 function addToXML(item)
		 {
			 if(!data) 
			 {
				 // for update service
				 remarksXML = IFDS.Xml.addSingleNode(remarksXML, 'Remark');
				 IFDS.Xml.addAttribute(remarksXML, 'RecordSource', item.data['fundDetlRemarksUUID']);
				 item = item.data;
			 }
			 for (var i in item)
			 {
				 if(i!='effDate')
				 {
					 IFDS.Xml.addSingleNode(remarksXML, i, item[i]);
				 } else {
					 IFDS.Xml.addSingleNode(remarksXML, i, DesktopWeb.Util.getSMVDateValue(item[i]));
				 }
			 }			
		 }		
	 }
	 
	 //handling error in remarks grid
	 function storeContextErrors(errorNodes)
	 {
		 var firstErrRecIndex = -1;
		 for (var i = 0; i < errorNodes.length; i++) {
			 var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			 var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			 var recordIndex = _resources.grids['grdRemarks'].getStore().find('fundDetlRemarksUUID', uuid);
			 var remarksRecord = _resources.grids['grdRemarks'].getStore().getAt(recordIndex);
			 remarksRecord.set('errMsg', errMsg);
			 _resources.grids['grdRemarks'].getStore().commitChanges();
			 if(firstErrRecIndex == -1)firstErrRecIndex = recordIndex;
		 }

		 if(firstErrRecIndex == -1)
		 {
			 _resources.grids['grdRemarks'].getSelectionModel().selectFirstRow();
		 } else {
			 _resources.grids['grdRemarks'].getSelectionModel().selectRow(firstErrRecIndex);
			 _resources.grids['grdRemarks'].focusRow(firstErrRecIndex);
		 }
	 }
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'a', MOD: 'm' ,DEL: 'd'
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_resources.grids['classes'].disableAllButtons();
			
			var dataXML = IFDS.Xml.stringToXML("<data><infoType>all</infoType></data>");
			DesktopWeb.Ajax.doSmartviewCall(_initView, {cacheKey: 'InitData'}, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])
			 								
			function responseHandler(responseXML)
			{
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _initView + 'Response')); 
				if (smartviewResults.successful)
				{
					storePermissions(responseXML);
					storeDefaultValues(responseXML);
				}											
			}
		}
		
		,doLookup: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'fundCode', _resources.fields['fund'].getValue());
						 					
			DesktopWeb.Ajax.doSmartviewCall(_classSearchView, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
			
			function responseHandler(responseXML)
			{										
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _classSearchView + 'Response')); 
				if (smartviewResults.successful)
				{               
					loadClassData(responseXML);
				}
			}
		}
		
		,updateActionButtons: function()
		{			
			var selectedRecord = _resources.grids['classes'].getSelectedRecord();
						
			if (_resources.fields['fund'].selectedRecord != null && _permissionsMap['add'] == 'yes')
			{
				_resources.grids['classes'].enableButton('addBtn');
			}
			else
			{
				_resources.grids['classes'].disableButton('addBtn');
			}	
			
			if (selectedRecord)
			{											
				_resources.grids['classes'].enableButton('viewBtn');
				_resources.grids['classes'].enableButton('limitOvrdBtn');
				_resources.grids['classes'].enableButton('remarksBtn');
								
			}
			else
			{
				_resources.grids['classes'].disableButton('viewBtn');
				_resources.grids['classes'].disableButton('limitOvrdBtn');
				_resources.grids['classes'].disableButton('remarksBtn');
			}		
		}
		
		,viewClassDetails: function()
		{
				var selectedRecord = _resources.grids['classes'].getSelectedRecord();
				
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, 'infoType', 'all');
				IFDS.Xml.addSingleNode(dataXML, 'runMode', 'i');
				IFDS.Xml.addSingleNode(dataXML, 'fundCode', _resources.fields['fund'].getValue());
				IFDS.Xml.addSingleNode(dataXML, 'classCode', selectedRecord.data['classCode']);			
							
				DesktopWeb.Ajax.doSmartviewCall(_inqView, {cacheKey: 'ExistingClassData'}, dataXML, responseHandler)
         
			function responseHandler(responseXML)
			{
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _inqView + 'Response'));
				if (smartviewResults.successful)
				{
					// JobDesigner caching behaves very strange, unreliable without some delay here					            
					updateInitData(responseXML,function(){goToScreen.defer(250, this, ['Summary'])});
				}
			}
		}
		
		,addClass: function()
		{   
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, 'runMode', 'a');
				IFDS.Xml.addSingleNode(dataXML, 'fundCode', _resources.fields['fund'].getValue());
				IFDS.Xml.addSingleNode(dataXML, 'classCode', '');		
				DesktopWeb.Ajax.doSmartviewCall(_inqView, null , dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(responseXML)
			{
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _inqView + 'Response'));
				if (smartviewResults.successful)
				{               
					// JobDesigner caching behaves very strange, unreliable without some delay here
					var updatedClassDataXML = buildInitialClassDataXML();			

					//Adding two values ratePrecision and unitPresition to dEfaultValues XML.
					var priceInfoNode  = IFDS.Xml.getNode(updatedClassDataXML, 'PriceInfo');
					IFDS.Xml.replaceSingleNode(priceInfoNode, 'ratePrecision', 
					               IFDS.Xml.getNodeValue(responseXML, 'dtClassSetupInqResponse/FundInfo/ratePrecision'));
					IFDS.Xml.replaceSingleNode(priceInfoNode, 'unitsPrecision', 
					               IFDS.Xml.getNodeValue(responseXML, 'dtClassSetupInqResponse/FundInfo/unitsPrecision'));

					var distribConfigNode  = IFDS.Xml.getNode(updatedClassDataXML, 'DistributionConfig');
					IFDS.Xml.addSingleNode(distribConfigNode, 'multiDistType', 
					               IFDS.Xml.getNodeValue(responseXML, 'dtClassSetupInqResponse/FundInfo/multiDistType'));
								   
					var screenDefListXML = buildScreenDefListXML();
					
					updateInitData(responseXML,InitDataUpdated);
               
					function InitDataUpdated()
					{ 
						DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: updatedClassDataXML, ScreenDefList: screenDefListXML}, 
							function(){goToScreen.defer(350, this, ['BasicInfo'])}
						)
					}
				}
			}
		}
		
		,limitationOverride: function()
		{																					
			goToScreen('LtOvrd', 
				{fundCode: _resources.fields['fund'].getValue(), 
					classCode: _resources.grids['classes'].getSelectedRecord().data['classCode']}
			);	
		}
		//initialize main popup
		,loadFundClsRemarks: function ()
		{
			loadFundClsRemarks();
		}
		,populateDropdowns: function()
		{
			populateDropdowns();
		}
		//open ADD/MOD/DEL popup
		,openRemarkPopup: function(action)
		{
			_resources.popups['RemarkModifyPopup'].init(action);
			_resources.popups['RemarkModifyPopup'].show();
		}
		,getNewRemarksUUID: function() {
			return "TMPREMARKS" + (_nextUUID++);
		}
		,openHistoryPopup: function()
		{
			var viewParam = {};
			var historyName = _translationMap['Remarks']+ ' - ' +_translationMap['History'];
			var selectedRecord = _resources.grids['grdRemarks'].getSelectedRecord();
			viewParam['auditType'] = 'FundDetlRemarks';
			viewParam['searchValue1'] = selectedRecord.get('fundDetlRemarksUUID');
			_resources.popups['history'].init(historyName, _dtHistoryService, viewParam, true);
			_resources.popups['history'].show();
		}
		,openAdminPopup: function()
		{					
			var title = null;	
			var selectedRecord = _resources.grids['grdRemarks'].getSelectedRecord();
			title = _translationMap['Remarks']+ ' - ' +_translationMap['Admin']
			var adminData = {};
			adminData['userName'] = selectedRecord.get('userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('processedDate'));
			adminData['modUser'] = selectedRecord.get('modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}
		//to get display value of dropdown code
		,getDisplay: function(listName, code)
		{
			var listNode = IFDS.Xml.getNode(_remarksInqDataXML, "//List[@id = '" + listName + "']/Element[code='" + code + "']");
			return (listNode)?IFDS.Xml.getNodeValue(listNode, 'value'):code;
		}
		,getDefaultEffDate: function()
		{
			return DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_remarksInqDataXML, '//DefaultValues/curBusDate'));
		}
		,updateGridBtns: function(record)
		{
			updateGridBtns(record);
		}
		//validating popup and updating grid records
		,validateRemarkPopUp: function(action, data)
		{
			if (action != _self.DEL)
			{
				var nRemarkType = (_resources.grids['grdRemarks'].getStore().queryBy(function(record) {
					return (record.get('remarkTyp') == _resources.popups['RemarkModifyPopup'].getField('remarkType').getValue() && record.get('runMode') !=_self.DEL)}));
				if (nRemarkType.length > 0 && action != _self.MOD)
				{
					_resources.popups['RemarkModifyPopup'].getField('remarkType').markInvalid(_translationMap['ERR_DUPLICATED_REMARKTYPE']);
					return false;
				}
				//Both reason and remarks cannot be blank
				var reasonVal = _resources.popups['RemarkModifyPopup'].getField('reason').getValue();
				var remarksVal = _resources.popups['RemarkModifyPopup'].getField('remarks').getValue();
				if (reasonVal == '' && remarksVal == '')
				{
					_resources.popups['RemarkModifyPopup'].getField('reason').markInvalid(_translationMap['ERR_REASON_REMARK_MAND']);
					_resources.popups['RemarkModifyPopup'].getField('remarks').markInvalid(_translationMap['ERR_REASON_REMARK_MAND']);
					return false;
				}

				DesktopWeb.Ajax.doSmartviewAjax(_remarksValView, null, buildUpdateXML(data), responseHandler, _translationMap['Validating']);

				function responseHandler(success, responseXML, contextErrors)
				{
					if(success)
					{
						updateRemarkRecord(action, data); //Update data to grid store
					}
				}
			} else {
				updateRemarkRecord(action, data); //Update data to grid store
			}

		}
		//Commit data
		,doCommitValidate: function()
		{
			if(_changeFlag)
			{
				DesktopWeb.Ajax.doSmartviewUpdate(_remarksUpdateView, null, buildUpdateXML(), responseHandler, _translationMap['ProcMsg_Saving']);	

				function responseHandler(success, responseXML, contextErrors)
				{
					if (success)
					{
						_changeFlag = false;
						_resources.popups['RemarksMainPopup'].hide();		
					} else {
						storeContextErrors(contextErrors);
						_resources.popups['RemarksMainPopup'].isError = true; 
					}
				}
			} else {
				_resources.popups['RemarksMainPopup'].hide();
			}
		}
	}	
}	