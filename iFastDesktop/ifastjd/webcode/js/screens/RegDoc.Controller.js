/*********************************************************************************************
 * @file	RegulatoryDocument.Controller.js
 * @author	Manoj Kumar
 * @desc	Controller JS file for Regulatory Document screen
 *********************************************************************************************/
 /*
 * History : 
 *
 *  18 Nov 2014 Winnie Cheng P0247899  T81687 
 *             - Desktop Screen Regulatory Documents modification.
 *             - Be able to retrive more records by providing "More" button.
 *    
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *			   - Fixed screens don't response when user's profile has too many slots attached.  
 *    
 */

DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _initDataXML;
	var _initView = 'dtRegDocListsInit';
	var _warningView = 'dtRegDocListsProc';
	var _permissionsMap = {};
	
	var _nextStartRecNum    = null;
	var _requestRecNum      = 100;	//The number of record display on table
	var _CMORE              = 'moreBtn';
	var _initFalg			= true;
	
	// PRIVATE METHODS ****************************************
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/add').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/mod').toLowerCase() == 'yes';
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/del').toLowerCase() == 'yes';
	}
	
	function loadregDocInfo(initViewXML)
	{
		var btnsToEnable = (_permissionsMap[_self.ADD] ? ['addBtn'] : null);

		if (IFDS.Xml.getNode(initViewXML,'/*//RegDocList/DocItem/docCode') != null)	{
			_resources.grids['regDocInfo'].loadData(IFDS.Xml.getNode(initViewXML, '/*//RegDocList'), btnsToEnable);
		}
		else{
			_resources.grids['regDocInfo'].enableButton('addBtn');
		}
		
	}

	function populateDropdowns()
	{
		_resources.popups['regDoc'].getField('taxImpact').getStore().loadData(IFDS.Xml.getNodes(_initDataXML, "//List[@listName = 'TaxImpactList']"));
		_resources.popups['regDoc'].getField('taxJuris').getStore().loadData(IFDS.Xml.getNodes(_initDataXML, "//List[@listName = 'TaxJurisList']"));
		_resources.popups['regDoc'].getField('taxExType').getStore().loadData(IFDS.Xml.getNodes(_initDataXML, "//List[@listName = 'TaxExmptList']"));
	}

	function displayAmendmentWarnings(warnMsgs)
	{
		var msg = IFDS.Xml.getNodeValue(warnMsgs[0]);
		for (var i = 1; i < warnMsgs.length; i++)
		{
			msg +=IFDS.Xml.getNodeValue(warnMsgs[i]);
		}
		DesktopWeb.Util.displayInfo(msg);
	}
	
	/** winnie **/
	function loadRegDocGrid(responseXML, append)
	{

		var regDocXML = IFDS.Xml.getNodes(responseXML, '/*//RegDocList');

		if (regDocXML != null && regDocXML != undefined && regDocXML.length > 0)
		{
			_resources.grids['regDocInfo'].getStore().loadData(regDocXML, append);
		}
		else {
			_resources.grids['regDocInfo'].clearData();
		}
	}
	
	function populatedRegDocGrid(append)
	{
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(requestXML, 'startRecNum', (append && _nextStartRecNum)?_nextStartRecNum:'1');
		IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _requestRecNum);
		
		DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['Loading']);

		function responseHandler(success, responseXML)
		{
			storePermissions(responseXML);
			if (!append)
				_self.updatesFlag = false;

			if (success){			
				var moreRecordsNode = IFDS.Xml.getNode(responseXML, '/*//RecordRange/moreRecordsExist');	
				if(moreRecordsNode != null && IFDS.Xml.getNodeValue(moreRecordsNode).toLowerCase() == 'yes')
				{
					_nextStartRecNum = IFDS.Xml.getNodeValue(responseXML, '/*//RecordRange/rangeStartForNext');
				}
				else { 
					_nextStartRecNum = 0; 
				}
				
				if(_initFalg) {
					storePermissions(responseXML);					
					loadregDocInfo(responseXML);
					_initDataXML= responseXML;
					populateDropdowns();
					_initFalg = false;
				}	
				_self.enableMoreButton(_nextStartRecNum);
				loadRegDocGrid(responseXML, append);
			}else{
				// Handle Rejected Response
				loadRegDocGrid(responseXML, append);

			}
		}
	}
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'modify'
		,DEL: 'delete'
		
		,updatesFlag: false
			
		,init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			_resources.grids['regDocInfo'].disableAllButtons();
			populatedRegDocGrid(false);
		}
		
		,clickHandleMoreBtn: function() {
			_self.doMoreRecords(true);
		}

		,enableMoreButton: function (moreRec) {
			(moreRec)
			 ?  _resources.grids['regDocInfo'].enableButton(_CMORE)
			 : _self.disableMoreButton();
		}

		,disableMoreButton: function () {
			_nextStartRecNum = 1;
			_resources.grids['regDocInfo'].disableButton(_CMORE);
		}
		
		,doMoreRecords: function(more) {
			if (!more) {
				DesktopWeb.Util.displayDiscardPrompt(callback)
			}
			else {
				callback(true);
			}

			function callback(discard) {
				if (discard) {
					populatedRegDocGrid(more);
				}
			}
		}

		,updateActionButtons: function()
		{			
			var selectedRecord = _resources.grids['regDocInfo'].getSelectedRecord();	
			if (selectedRecord)
			{								
				if (_permissionsMap[this.MOD]){

					_resources.grids['regDocInfo'].enableButton('modBtn');						
				}
								
				if (_permissionsMap[this.DEL])		
				{

					_resources.grids['regDocInfo'].enableButton('delBtn');
				}
			}
			else
			{
				_resources.grids['regDocInfo'].disableButton('modBtn');
				_resources.grids['regDocInfo'].disableButton('delBtn');
			}
		}
		
		,openActionPopup: function(action)
		{
			if (action == this.ADD)
			{
				_resources.grids['regDocInfo'].clearSelectedRecord();
				_resources.popups['regDoc'].clearAllFields();		
			}

			_resources.popups['regDoc'].init(action);
			_resources.popups['regDoc'].getField('taxJuris').disable();
			_resources.popups['regDoc'].getField('taxExType').disable();
			_resources.popups['regDoc'].show();
		}
		
		,closeActionPopup: function()
		{
			_resources.popups['regDoc'].clearAllFields();
			_resources.popups['regDoc'].hide();
		}
		,getValueDescFromList: function(listName, code)
		{
			value = IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = '" + listName + "']/Element[code = '" + code + "']/value");
			return value;
		}

		,getCodeFromList: function(listName, value)
		{	
			code = IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = '" + listName + "']/Element[value = '" + value + "']/code");
			return code;
		}

		,savePopup: function(action, data)
		{
			var success = true;
			var viewParamXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(viewParamXML, 'action', data['runMode']);
			IFDS.Xml.addSingleNode(viewParamXML, 'docCode', data['docCode']);
			IFDS.Xml.addSingleNode(viewParamXML, 'docDesc', data['description']);
			IFDS.Xml.addSingleNode(viewParamXML, 'taxImpact', this.getCodeFromList('TaxImpactList', data['taxImpactDesc']));
			IFDS.Xml.addSingleNode(viewParamXML, 'taxJuris', this.getCodeFromList('TaxJurisList', data['taxJurisDesc']));
			IFDS.Xml.addSingleNode(viewParamXML, 'taxExType', this.getCodeFromList('TaxExmptList', data['taxExTypeDesc']));		
			DesktopWeb.Ajax.doSmartviewUpdate(_warningView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Loading']);
			function responseHandler(success, responseXML)
			{
				if (success)				
				{
					var warnMsgs = IFDS.Xml.getNodes(responseXML, '/*//AmendmentWarning/warnMsg');
					if (warnMsgs != null && warnMsgs.length > 0)
					{
						displayAmendmentWarnings(warnMsgs);
					}
					else{
						if(action == _self.MOD)
						{
							_resources.grids['regDocInfo'].updateSelectedRecord(data);
						}
						else if (action == _self.DEL)
						{
							_resources.grids['regDocInfo'].removeSelectedRecord();
						}
						_self.closeActionPopup();
					}

					if (action == _self.ADD)
					{
						_resources.grids['regDocInfo'].addRecord(data);
						_resources.grids['regDocInfo'].selectLastRecord();
					}

				}
			}
			_self.updateActionButtons();
			this.updatesFlag = true;														
		}							
	}
}