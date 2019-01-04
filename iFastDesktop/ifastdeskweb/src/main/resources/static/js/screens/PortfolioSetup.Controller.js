/*********************************************************************************************
 * @file	PortfolioSetup.Controller.js
 * @author	Chatchai Daecha
 * @desc	Controller JS file for Portfolio Setup screen
 *********************************************************************************************/

 /*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *     - Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *	   - Fixed screens don't response when user's profile has too many slots attached.  
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _portfolioInfoXML = null;
	var _selectedMstrRecord = null;
	var _permissionsMap = {};
	var _defaultValues = {};
	
	var _reloadView = 'dtPortfolioInfoReload';
	var _detlOptionsView = 'dtGetPortDetlOptions'
	var _detlClassListView = 'dtGetPortDetlClass'
	var _mstrVldtnView = 'dtPortfolioMstrVldtn';
	var _detlVldtnView = 'dtPortfolioDetlVldtn';
	var _planVldtnView = 'dtPortfolioPlanVldtn';
	var _updateView = 'dtPortfolioUpdate';

	// PRIVATE METHODS ****************************************	
	function storePermissions(initViewXML)
	{		
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';	
	}
	
	function storeDefaultValue(initViewXML)
	{
		_defaultValues['searchType'] = IFDS.Xml.getNodeValue(initViewXML, '*/ListSelection[@id="SearchTypeOptions"]');
		_defaultValues['deff'] = DesktopWeb.Util.getDateDisplayValue( IFDS.Xml.getNodeValue(initViewXML, "/*//DefaultDates/deff"));
		_defaultValues['stopDate'] = DesktopWeb.Util.getDateDisplayValue( IFDS.Xml.getNodeValue(initViewXML, '//DefaultDates/stopDate'));
		_defaultValues['currBusDate'] = DesktopWeb.Util.getDateDisplayValue( IFDS.Xml.getNodeValue(initViewXML, '//DefaultDates/currBusDate'));
		_defaultValues['defaultPlan'] = 'yes';
		
		_resources.fields['searchType'].setValue(_defaultValues['searchType']);
		_resources.fields['searchFromDate'].setValue(_defaultValues['deff']);
		_resources.fields['searchToDate'].setValue(_defaultValues['stopDate']);
		_self.updateSearchType();
	}
	
	function populateDropdowns(initXML)
	{
		try
		{
			_resources.fields['searchType'].loadData(IFDS.Xml.getNode(initXML, "//List[@listName='SearchTypeOptions']"));
			_resources.popups['detls'].getField('investmentType').loadData(IFDS.Xml.getNode(initXML, '//List[@listName="InvestTypeList"]'));
			_resources.popups['plans'].getField('defaultPlan').loadData(IFDS.Xml.getNode(initXML, '//List[@listName="DefaultPlanOptions"]'));			
		}
		catch(e){throw new Error("Error loading data from XML - " + e.description)}		
	}
	
	function formatPortfolioInfoXML(xml)
	{
		var mstrXMLNodes = IFDS.Xml.getNodes(xml, 'Mstr');
		for (var m = 0; m < mstrXMLNodes.length; m++)
		{
			IFDS.Xml.addAttribute(mstrXMLNodes[m], 'recordSource', m + 1);
			
			var planXMLNodes = IFDS.Xml.getNodes(mstrXMLNodes[m], 'Plans/Plan');
			for (var p = 0; p < planXMLNodes.length; p++)
			{
				IFDS.Xml.addAttribute(planXMLNodes[p], 'recordSource', (m + 1) + ":" + (p + 1));
			}
			
			var detlXMLNodes = IFDS.Xml.getNodes(mstrXMLNodes[m], 'Detls/Detl');
			for (var d = 0; d < detlXMLNodes.length; d++)
			{
				IFDS.Xml.addAttribute(detlXMLNodes[d], 'recordSource', (m + 1) + ":" + (d + 1));
			} 
		}
		
		return xml;
	}
	
	function validateMstrChange(data, callbackFn)
	{
		var copyMstrXML = null;
		if (_selectedMstrRecord != null)
		{
			mstrXMLIndex = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) + 1;
			copyMstrXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']'));
			IFDS.Xml.deleteNode(IFDS.Xml.getNode(copyMstrXML, 'Plans'));
			IFDS.Xml.deleteNode(IFDS.Xml.getNode(copyMstrXML, 'Detls'));
		}
		else
		{
			copyMstrXML = IFDS.Xml.newDocument("Mstr");
		}
				
		updateMstrXML(copyMstrXML, data);
				
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.appendNode(requestXML, copyMstrXML);
		
		DesktopWeb.Ajax.doSmartviewAjax(_mstrVldtnView, null, requestXML, responseHandler, _translationMap['ProcMsg_Processing']);		
		
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				if (IFDS.Xml.getNode(responseXML, '*/PortfolioWarnMsg'))
				{
					DesktopWeb.Util.displayWarning(IFDS.Xml.getNodeValue(responseXML, '*/PortfolioWarnMsg'));
					callbackFn(true, {runMode: _self.MOD, stopDate: _defaultValues['currBusDate']});
				}
				else
				{
					callbackFn(true);
				}
			}
		}	
	}
	
	function updateMstrXML(mstrXML, data)
	{
		if (IFDS.Xml.getNodeValue(mstrXML, 'runMode') == _self.ADD
			&& data['runMode'] == _self.DEL)
		{
			IFDS.Xml.deleteNode(mstrXML);
		}
		else
		{					
			for (var i in data)
			{
				IFDS.Xml.replaceSingleNode(mstrXML, i, data[i]);
			}
			
			if (IFDS.Xml.getNode(mstrXML, 'errorMsg'))
			{
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(mstrXML, 'errorMsg'));	
			}		
			
			if (IFDS.Xml.getNode(mstrXML, 'Detls') == null)
			{
				IFDS.Xml.addSingleNode(mstrXML, 'Detls');
			}
			
			if (IFDS.Xml.getNode(mstrXML, 'Plans') == null)
			{
				IFDS.Xml.addSingleNode(mstrXML, 'Plans');
			}
		}		
	}
	
	function validateDetlChange(curRec, data, callbackFn)
	{
		var mstrXMLIndex = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) + 1;
		var copyMstrXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(copyMstrXML, 'Plans'));
		updateDetlsXML(curRec, data, copyMstrXML);
		
		var copyDetlXML = null;					
		if (curRec != null)
		{
			var xmlIndex = _resources.grids['detls'].getRecordIndex(curRec) + 1;
			copyDetlXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(copyMstrXML, 'Detls/Detl[' + xmlIndex + ']'));		
		}
		else
		{
			var lastIndex = IFDS.Xml.getNodes(copyMstrXML, 'Detls/Detl').length;
			copyDetlXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(copyMstrXML, 'Detls/Detl[' + lastIndex + ']'));
		}
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(copyMstrXML, 'Detls'));
		IFDS.Xml.appendNode(IFDS.Xml.addSingleNode(copyMstrXML, 'Detls'), copyDetlXML);
				
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.appendNode(requestXML, copyMstrXML);
		
		DesktopWeb.Ajax.doSmartviewAjax(_detlVldtnView, null, requestXML, responseHandler, _translationMap['ProcMsg_Processing']);		
		
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				callbackFn(true);
			}
		}	
	}
	
	function updateDetlsXML(curRec, data, mstrXML)
	{
		var detlsXML = IFDS.Xml.getNode(mstrXML, 'Detls');
		var detlXML = null;
		if (curRec != null)
		{
			var xmlIndex = _resources.grids['detls'].getRecordIndex(curRec) + 1; 			
			detlXML	= IFDS.Xml.getNode(detlsXML, 'Detl[' + xmlIndex + ']');
			
			if (IFDS.Xml.getNode(detlXML, 'errorMsg'))
			{
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(detlXML, 'errorMsg'));				
			}
		}
		else
		{
			detlXML = IFDS.Xml.addSingleNode(detlsXML, 'Detl');
			//IFDS.Xml.addAttribute(detlXML, 'recordSource', IFDS.Xml.getNodeValue(mstrXML, '@recordSource') + ":" + (IFDS.Xml.getNodes(mstrXML, 'Detls/Detl').length));			
		}
		
		if (IFDS.Xml.getNodeValue(detlXML, 'runMode') == _self.ADD
			&& data['runMode'] == _self.DEL)
		{
			IFDS.Xml.deleteNode(detlXML);
		}
		else
		{
			for (var i in data)
			{
				IFDS.Xml.replaceSingleNode(detlXML, i, data[i]);
			}
		}
		
		if (IFDS.Xml.getNode(mstrXML, 'errorMsg') != null)
		{
			IFDS.Xml.deleteNode(IFDS.Xml.getNode(mstrXML, 'errorMsg'));
		}	
	}
	
	function validatePlanChange(curRec, data, callbackFn)
	{
		var mstrXMLIndex = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) + 1;
		var copyMstrXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(copyMstrXML, 'Detls'));
		updatePlansXML(curRec, data, copyMstrXML);
		
		var copyPlanXML = null;					
		if (curRec != null)
		{
			var xmlIndex = _resources.grids['plans'].getRecordIndex(curRec) + 1;
			copyPlanXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(copyMstrXML, 'Plans/Plan[' + xmlIndex + ']'));		
		}
		else
		{
			var lastIndex = IFDS.Xml.getNodes(copyMstrXML, 'Plans/Plan').length;
			copyPlanXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(copyMstrXML, 'Plans/Plan[' + lastIndex + ']'));
		}
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(copyMstrXML, 'Plans'));
		IFDS.Xml.appendNode(IFDS.Xml.addSingleNode(copyMstrXML, 'Plans'), copyPlanXML);
				
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.appendNode(requestXML, copyMstrXML);
		
		DesktopWeb.Ajax.doSmartviewAjax(_planVldtnView, null, requestXML, responseHandler, _translationMap['ProcMsg_Processing']);		
		
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				callbackFn(true);
			}
		}	
	}
	
	function updatePlansXML(curRec, data, mstrXML)
	{
		var plansXML = IFDS.Xml.getNode(mstrXML, 'Plans');
		var planXML = null;
		if (curRec != null)
		{
			var xmlIndex = _resources.grids['plans'].getRecordIndex(curRec) + 1;
			planXML	= IFDS.Xml.getNode(plansXML, 'Plan[' + xmlIndex + ']');
			if (IFDS.Xml.getNode(planXML, 'errorMsg'))
			{
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(planXML, 'errorMsg'));				
			}			
		}
		else
		{
			planXML = IFDS.Xml.addSingleNode(plansXML, 'Plan');
			//IFDS.Xml.addAttribute(planXML, 'recordSource', IFDS.Xml.getNodeValue(mstrXML, '@recordSource') + ":" + (IFDS.Xml.getNodes(mstrXML, 'Plans/Plan').length));			
		}		
		
		if (IFDS.Xml.getNodeValue(planXML, 'runMode') == _self.ADD
			&& data['runMode'] == _self.DEL)
		{
			IFDS.Xml.deleteNode(planXML);
		}
		else
		{
			for (var i in data)
			{
				IFDS.Xml.replaceSingleNode(planXML, i, data[i]);
			}
		}
		
		if (IFDS.Xml.getNode(mstrXML, 'errorMsg') != null)
		{
			IFDS.Xml.deleteNode(IFDS.Xml.getNode(mstrXML, 'errorMsg'));
		}			
	}
	
	function storeContextErrors(errorNodes)
	{		
		for (var i = 0; i < errorNodes.length; i++)
		{
			var recordType = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName').toLowerCase();
			if (recordType == 'mstr')
			{
				var mstrXMLIndex = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var mstrXML = IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']')				
				IFDS.Xml.replaceSingleNode(mstrXML, 'errorMsg',  IFDS.Xml.getNodeValue(errorNodes[i], 'text'));												
			}
			else if (recordType == 'detl') 								
			{
				var sources = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource').split(':');
				var mstrXMLIndex = sources[0];				
				var detlXMLIndex = sources[1];
				var mstrXML = IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']');
								
				var detlXML = IFDS.Xml.getNode(mstrXML, 'Detls/Detl[' + detlXMLIndex + ']');
				IFDS.Xml.replaceSingleNode(detlXML, 'errorMsg',  IFDS.Xml.getNodeValue(errorNodes[i], 'text'));
			}
			else 								
			{
				var sources = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource').split(':');
				var mstrXMLIndex = sources[0];				
				var planXMLIndex = sources[1];
				var mstrXML = IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']');
				
				var planXML = IFDS.Xml.getNode(mstrXML, 'Plans/Plan[' + planXMLIndex + ']');
				IFDS.Xml.replaceSingleNode(planXML, 'errorMsg',  IFDS.Xml.getNodeValue(errorNodes[i], 'text'));
			}
		}
	}
	
	function buildUpdateXML(portfolioXML)
	{
		var updateXML = IFDS.Xml.cloneDocument(portfolioXML)
		
		var mstrXMLNodes = IFDS.Xml.getNodes(updateXML, 'Mstr');
		for (var m = 0; m < mstrXMLNodes.length; m++)
		{
			IFDS.Xml.addAttribute(mstrXMLNodes[m], 'recordSource', m + 1);
			if (IFDS.Xml.getNodeValue(mstrXMLNodes[m], 'runMode').toLowerCase() == _self.UNCH)
			{			
				var noDetlUpdates = true;			
				var detlXMLNodes = IFDS.Xml.getNodes(mstrXMLNodes[m], 'Detls/Detl');
				for (var d = 0; d < detlXMLNodes.length; d++)
				{
					IFDS.Xml.addAttribute(detlXMLNodes[d], 'recordSource', (m + 1) + ":" + (d + 1));
					if (IFDS.Xml.getNodeValue(detlXMLNodes[d], 'runMode').toLowerCase() != _self.UNCH)
					{
						noDetlUpdates = false;
						break;					
					}								
				}
				
				var noPlanUpdates = true;
				var planXMLNodes = IFDS.Xml.getNodes(mstrXMLNodes[m], 'Plans/Plan');
				for (var p = 0; p < planXMLNodes.length; p++)
				{
					IFDS.Xml.addAttribute(planXMLNodes[p], 'recordSource', (m + 1) + ":" + (p + 1));
					if (IFDS.Xml.getNodeValue(planXMLNodes[p], 'runMode').toLowerCase() != _self.UNCH)
					{
						noPlanUpdates = false;
						break;						
					}								
				}				
				
				if (noDetlUpdates && noPlanUpdates)
				{
					IFDS.Xml.deleteNode(mstrXMLNodes[m]);
				}
			} 			
		}
				
		return updateXML;
	}
	
	function isNewRecord(rec)
	{
		return (rec != null && rec.data['runMode'] == _self.ADD);
	} 
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		,UNCH: 'unch'				

		,updatesFlag: false

		,init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;

			_resources.grids['mstrs'].disableAllButtons();			
			_resources.grids['detls'].disableAllButtons();
			_resources.grids['plans'].disableAllButtons();

			_resources.fields['searchFromDate'].hideField();
			_resources.fields['searchToDate'].hideField();
			_resources.fields['searchPortfolioID'].hideField();
			_resources.fields['searchPortfolioName'].hideField();
			
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, 'searchType', '');
			IFDS.Xml.addSingleNode(requestXML, 'portfolioCode', '');
			IFDS.Xml.addSingleNode(requestXML, 'businessNo', '');
			IFDS.Xml.addSingleNode(requestXML, 'name', '');
			IFDS.Xml.addSingleNode(requestXML, 'deff', '');
			IFDS.Xml.addSingleNode(requestXML, 'stopDate', '');
			
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, null, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{							
				if (success)
				{							
					storePermissions(responseXML);	
					populateDropdowns(responseXML);				
					storeDefaultValue(responseXML);
					
					_portfolioInfoXML = IFDS.Xml.newDocument("PortfolioInfo");
					_resources.grids['mstrs'].loadData(_portfolioInfoXML, ['addBtn']);									
				}
			}
		}
		
		,updateSearchType: function()
		{
			var searchType = _resources.fields['searchType'].getValue();			
			if (searchType == "portCode")
			{
				_resources.fields['searchPortfolioID'].showField();				
				_resources.fields['searchFromDate'].showField();
				_resources.fields['searchToDate'].showField();				
				_resources.fields['searchPortfolioName'].hideField();
				_resources.fields['searchPortfolioName'].clearField();
			}
			else if (searchType == "portName")
			{
				_resources.fields['searchPortfolioName'].showField();
				_resources.fields['searchFromDate'].showField();
				_resources.fields['searchToDate'].showField();
				_resources.fields['searchPortfolioID'].hideField();
				_resources.fields['searchPortfolioID'].clearField();				
			}
			else if (searchType == 'All')
			{
				_resources.fields['searchPortfolioID'].hideField();
				_resources.fields['searchPortfolioID'].clearField();
				_resources.fields['searchPortfolioName'].hideField();
				_resources.fields['searchPortfolioName'].clearField();
				_resources.fields['searchFromDate'].showField();
				_resources.fields['searchToDate'].showField();
			}
			else
			{
				_resources.fields['searchPortfolioID'].hideField();
				_resources.fields['searchPortfolioID'].clearField();
				_resources.fields['searchPortfolioName'].hideField();
				_resources.fields['searchPortfolioName'].clearField();
				_resources.fields['searchFromDate'].hideField();
				_resources.fields['searchFromDate'].clearField();
				_resources.fields['searchToDate'].hideField();
				_resources.fields['searchFromDate'].clearField();
			}
		}
		
		,getDefaultValue: function(valName)
		{
			return _defaultValues[valName];
		}
						
		,doSearch: function()
		{
			if (_self.updatesFlag)
			{
				DesktopWeb.Util.displayDiscardPrompt(callback)
			}
			else
			{
				callback(true);
			}
			
			function callback(discard)
			{
				if (discard)
				{
					_resources.grids['mstrs'].clearSelectedRecord();
					
					var requestXML = IFDS.Xml.newDocument('data');
					IFDS.Xml.addSingleNode(requestXML, 'searchType', _resources.fields['searchType'].getValue());
					IFDS.Xml.addSingleNode(requestXML, 'portfolioCode', _resources.fields['searchPortfolioID'].getValue());
					IFDS.Xml.addSingleNode(requestXML, 'name', _resources.fields['searchPortfolioName'].getValue());
					IFDS.Xml.addSingleNode(requestXML, 'deff', _resources.fields['searchFromDate'].getSMVDateString());
					IFDS.Xml.addSingleNode(requestXML, 'stopDate', _resources.fields['searchToDate'].getSMVDateString());

		
					DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['ProcMsg_Searching']);
		
					function responseHandler(success, responseXML)
					{														
						if (success)
						{	
							//_portfolioInfoXML = formatPortfolioInfoXML(IFDS.Xml.getNode(responseXML, '*/PortfolioInfo'));
							_portfolioInfoXML = IFDS.Xml.getNode(responseXML, '*/PortfolioInfo') 									
							if (_portfolioInfoXML == null)
							{
								_portfolioXML = IFDS.Xml.newDocument('PortfolioInfo'); 								
							}
							_resources.grids['mstrs'].loadData(_portfolioInfoXML);
							_self.updatesFlag = false;
						}
					}
				}
			}
		}
		
		,openActionPopup: function(popupName, action)
		{
			if (action == this.ADD)
			{
				_resources.grids[popupName].clearSelectedRecord();
			}
			_resources.popups[popupName].init(action, (_selectedMstrRecord != null ? _selectedMstrRecord.data['portfolioUUID'] : null));
			_resources.popups[popupName].show();
		}
		
		,updateGridButtons: function()
		{
			var mstrRecord = _resources.grids['mstrs'].getSelectedRecord()
			var mstrAllowUpd = (mstrRecord != null && mstrRecord.data['allowUpd'].toLowerCase() == 'yes');

			// Mstrs ******
			
			// add button			
			if (_permissionsMap[_self.ADD])
			{
				_resources.grids['mstrs'].enableButton('addBtn');				
			}
			else
			{
				_resources.grids['mstrs'].disableButton('addBtn');
			}
			
			// mod button
			if (_permissionsMap[_self.MOD] && mstrRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['mstrs'].enableButton('modBtn');
			}
			else
			{
				_resources.grids['mstrs'].disableButton('modBtn');
			}
			
			// del button
			if (_permissionsMap[_self.DEL] && mstrRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['mstrs'].enableButton('delBtn');
			}
			else
			{
				_resources.grids['mstrs'].disableButton('delBtn');
			}
			
			// admin and historical
			if (mstrRecord != null && !isNewRecord(mstrRecord))
			{
				_resources.grids['mstrs'].enableButton('adminBtn');
				_resources.grids['mstrs'].enableButton('historicalBtn');
			}
			else
			{
				_resources.grids['mstrs'].disableButton('adminBtn');
				_resources.grids['mstrs'].disableButton('historicalBtn');
			}
			
			// Detls ****
			var detlRecord = _resources.grids['detls'].getSelectedRecord()
			
			// add button
			if (_permissionsMap[_self.ADD] && mstrRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['detls'].enableButton('addBtn');
			}
			else
			{
				_resources.grids['detls'].disableButton('addBtn');
			}
						
			// mod button			
			if (_permissionsMap[_self.MOD] && detlRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['detls'].enableButton('modBtn');
			}
			else
			{
				_resources.grids['detls'].disableButton('modBtn');
			}
			
			// del button
			if (_permissionsMap[_self.DEL] && detlRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['detls'].enableButton('delBtn');
			}
			else
			{
				_resources.grids['detls'].disableButton('delBtn');
			}
			
			// admin and historical
			if (detlRecord != null && !isNewRecord(detlRecord))
			{
				_resources.grids['detls'].enableButton('adminBtn');
				_resources.grids['detls'].enableButton('historicalBtn');
			}
			else
			{
				_resources.grids['detls'].disableButton('adminBtn');
				_resources.grids['detls'].disableButton('historicalBtn');
			}
			
			// Plans ***
			var planRecord = _resources.grids['plans'].getSelectedRecord();
						
			// add button
			if (_permissionsMap[_self.ADD] && mstrRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['plans'].enableButton('addBtn');
			}
			else
			{
				_resources.grids['plans'].disableButton('addBtn');
			}
			
			// mod button			
			if (_permissionsMap[_self.MOD] && planRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['plans'].enableButton('modBtn');
			}
			else
			{
				_resources.grids['plans'].disableButton('modBtn');
			}
			
			// del button
			if (_permissionsMap[_self.DEL] && planRecord != null && (mstrAllowUpd || isNewRecord(mstrRecord)))
			{
				_resources.grids['plans'].enableButton('delBtn');
			}
			else
			{
				_resources.grids['plans'].disableButton('delBtn');
			}
			
			// admin and historical
			if (planRecord != null && !isNewRecord(planRecord))
			{
				_resources.grids['plans'].enableButton('adminBtn');
				_resources.grids['plans'].enableButton('historicalBtn');
			}
			else
			{
				_resources.grids['plans'].disableButton('adminBtn');
				_resources.grids['plans'].disableButton('historicalBtn');
			}
		}
		
		,updateSelectedMstrRecord: function()
		{			
			_selectedMstrRecord = _resources.grids['mstrs'].getSelectedRecord();
			
			if (_selectedMstrRecord != null)
			{
				var mstrIndex = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) + 1;							
				_resources.grids['detls'].loadData(IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrIndex + ']/Detls'));				
				_resources.grids['plans'].loadData(IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrIndex + ']/Plans'));				
			}
			else
			{
				_resources.grids['detls'].clearData();
				_resources.grids['plans'].clearData();
			}			
			this.updateGridButtons();			
		}
		
		,saveMstrRecord: function(action, data)
		{			
			var validationReqd = true;					
			
			if (action != this.ADD)
			{				
				// annoying case where mod/del a brand new record		
				if (_selectedMstrRecord.data['runMode'] == this.ADD)
				{					
					if (action == this.DEL)
					{											
						validationReqd = false;																	
					}
					else
					{						
						data['runMode'] = this.ADD;						
					}
				}				
			}
			
			if (validationReqd)
			{
				validateMstrChange(data, callback);
			}
			else
			{
				callback(true);
			}
			
			function callback(success, modData)
			{
				if (success)
				{
					action = (modData != null ? modData['runMode'] : action); 
					Ext.apply(data, modData);
					
					var mstrXML = null;
					if (_selectedMstrRecord == null)
					{
						mstrXML = IFDS.Xml.addSingleNode(_portfolioInfoXML, 'Mstr');												
					}
					else
					{
						var mstrXMLIndex = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) + 1; 
						mstrXML = IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']');
					}					
					updateMstrXML(mstrXML, data);					
					
					var mstrRecordIndexToReSelect = (action == _self.MOD ? _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) : null);
					var detlRecordIndexToReSelect = (action == _self.MOD ? _resources.grids['detls'].getRecordIndex(_resources.grids['detls'].getSelectedRecord()) : null);
					var planRecordIndexToReSelect = (action == _self.MOD ? _resources.grids['plans'].getRecordIndex(_resources.grids['plans'].getSelectedRecord()) : null);
										
					_resources.grids['mstrs'].loadData(_portfolioInfoXML);
					
					if (mstrRecordIndexToReSelect != null)
					{						
						_resources.grids['mstrs'].setSelectedRecord(mstrRecordIndexToReSelect);
						if (detlRecordIndexToReSelect != null)
						{
							_resources.grids['detls'].setSelectedRecord(detlRecordIndexToReSelect);
						}
						if (planRecordIndexToReSelect != null)
						{
							_resources.grids['plans'].setSelectedRecord(planRecordIndexToReSelect);
						}
					}
					else if (action == _self.ADD)
					{
						_resources.grids['mstrs'].selectLastRecord();
					}
					_resources.popups['mstrs'].hide();
					_self.updateGridButtons();
					_self.updatesFlag = true;
				}				
			}			
		}
		
		,saveDetlRecord: function(action, data)
		{			
			var validationReqd = true;
			var curRec = null;			
			
			if (action != this.ADD)
			{
				curRec = _resources.grids['detls'].getSelectedRecord();
				// annoying case where mod/del a brand new record		
				if (curRec.data['runMode'] == this.ADD)
				{
					if (action == this.DEL)
					{						
						validationReqd = false;																	
					}
					else
					{						
						data['runMode'] = this.ADD;						
					}
				}				
			}
			
			if (validationReqd)
			{
				validateDetlChange(curRec, data, callback);
			}
			else
			{
				callback(true);
			}
			
			function callback(success)
			{
				if (success)
				{
					var mstrXMLIndex = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) + 1;				
					updateDetlsXML(curRec, data, IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']'));
										
					var mstrRecordIndexToReSelect = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord);
					var detlRecordIndexToReSelect = (action == _self.MOD ? _resources.grids['detls'].getRecordIndex(_resources.grids['detls'].getSelectedRecord()) : null);
					var planRecordIndexToReSelect = _resources.grids['plans'].getRecordIndex(_resources.grids['plans'].getSelectedRecord());
										
					_resources.grids['mstrs'].loadData(_portfolioInfoXML);
					
					_resources.grids['mstrs'].setSelectedRecord(mstrRecordIndexToReSelect);
					if (detlRecordIndexToReSelect != null)
					{
						_resources.grids['detls'].setSelectedRecord(detlRecordIndexToReSelect);
					}
					else
					{
						_resources.grids['detls'].selectLastRecord();
					}
					if (planRecordIndexToReSelect != null)
					{
						_resources.grids['plans'].setSelectedRecord(planRecordIndexToReSelect);
					}
					
					_resources.popups['detls'].hide();
					_self.updateGridButtons();
					_self.updatesFlag = true;
				}
			}			
		}
		
		,savePlanRecord: function(action, data)
		{			
			var validationReqd = true;
			var curRec = null;			
			
			if (action != this.ADD)
			{
				curRec = _resources.grids['plans'].getSelectedRecord();
				// annoying case where mod/del a brand new record		
				if (curRec.data['runMode'] == this.ADD)
				{
					if (action == this.DEL)
					{						
						validationReqd = false;																	
					}
					else
					{						
						data['runMode'] = this.ADD;						
					}
				}				
			}
			
			if (validationReqd)
			{
				validatePlanChange(curRec, data, callback);
			}
			else
			{
				callback(true);
			}
			
			function callback(success)
			{
				if (success)
				{
					var mstrXMLIndex = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord) + 1; 					
					updatePlansXML(curRec, data, IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + mstrXMLIndex + ']'));
															
					var mstrRecordIndexToReSelect = _resources.grids['mstrs'].getRecordIndex(_selectedMstrRecord);
					var detlRecordIndexToReSelect = _resources.grids['detls'].getRecordIndex(_resources.grids['detls'].getSelectedRecord());
					var planRecordIndexToReSelect = (action == _self.MOD ? _resources.grids['plans'].getRecordIndex(_resources.grids['plans'].getSelectedRecord()) : null);
																			
					_resources.grids['mstrs'].loadData(_portfolioInfoXML);
					
					_resources.grids['mstrs'].setSelectedRecord(mstrRecordIndexToReSelect);
					if (detlRecordIndexToReSelect != null)
					{
						_resources.grids['detls'].setSelectedRecord(detlRecordIndexToReSelect);
					}
					if (planRecordIndexToReSelect != null)
					{
						_resources.grids['plans'].setSelectedRecord(planRecordIndexToReSelect);
					}
					else
					{
						_resources.grids['plans'].selectLastRecord();
					}
					
					_resources.popups['plans'].hide();
					_self.updateGridButtons();
					_self.updatesFlag = true;
				}
			}			
		}
				
		,openAdminPopup: function(recType)
		{
			var title = null;	
			var xml = null;
			if (recType == 'mstrs')
			{
				title = _translationMap['Portfolio']+ ' - ' +_translationMap['Admin']
				var xmlIndex = _resources.grids['mstrs'].getRecordIndex(_resources.grids['mstrs'].getSelectedRecord()) + 1;
				xml = IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + xmlIndex + ']');
			}
			else if(recType == 'detls')
			{
				title = _translationMap['Investment']+ ' - ' +_translationMap['Admin']
				var xmlIndex = _resources.grids['detls'].getRecordIndex(_resources.grids['detls'].getSelectedRecord()) + 1;
				xml = IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + xmlIndex + ']');
			}			
			else // plan
			{
				title = _translationMap['PortfolioPlan']+ ' - ' +_translationMap['Admin']
				var xmlIndex = _resources.grids['plans'].getRecordIndex(_resources.grids['plans'].getSelectedRecord()) + 1;
				xml = IFDS.Xml.getNode(_portfolioInfoXML, 'Mstr[' + xmlIndex + ']');
			}
			var adminData = {};
			adminData['userName'] = IFDS.Xml.getNodeValue(xml, 'userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue( IFDS.Xml.getNodeValue(xml, 'procDate'));
			adminData['modUser'] = IFDS.Xml.getNodeValue(xml, 'modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue( IFDS.Xml.getNodeValue(xml, 'modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();
		}
		
		,openHistoricalPopup: function(recType)
		{
			var viewParam = {}
			var title = ""
			if (recType == 'mstrs')
			{
				viewParam['auditType'] = 'ProdPortfolio';
				viewParam['searchValue1'] = _resources.grids['mstrs'].getSelectedRecord().data["portfolioUUID"];
				title = "Portfolio - History"								
			}
			else if (recType == 'detls')
			{
				viewParam['auditType'] = 'ProdPortfolioDetl';
				viewParam['searchValue1'] = _resources.grids['detls'].getSelectedRecord().data["detlUUID"];
				title = "Investment - History"				
			}
			else
			{
				viewParam['auditType'] = 'ProdPortfolioPlan';
				viewParam['searchValue1'] = _resources.grids['plans'].getSelectedRecord().data["planUUID"];
				title = "Portfolio Plan - History"
			}
			_resources.popups['history'].init(title, 'dtHistoricalInfo', viewParam, true);
			_resources.popups['history'].show();
		}
				
		,fetchDetlOptions : function(portfolioUUID, investmentType, action, callbackFn)
		{			
			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, 'portfolioUUID', portfolioUUID);
			IFDS.Xml.addSingleNode(requestXML, 'investmentType', investmentType);
			IFDS.Xml.addSingleNode(requestXML, 'runMode', action);
			
			var allRecords = _resources.grids['detls'].getAllRecords();
			var selectedDetlRec = _resources.grids['detls'].getSelectedRecord();				
			for (var i = allRecords.length - 1; i >= 0; i--)
			{
				if (allRecords[i] != selectedDetlRec)
				{					
					var detlNode = IFDS.Xml.addSingleNode(requestXML, 'Detl');
					IFDS.Xml.addSingleNode(detlNode, 'runMode', allRecords[i].data['runMode']);
					IFDS.Xml.addSingleNode(detlNode, 'contractType', allRecords[i].data['contractType']);
					IFDS.Xml.addSingleNode(detlNode, 'fund', allRecords[i].data['fund']);
					IFDS.Xml.addSingleNode(detlNode, 'class', allRecords[i].data['class']);
				}				
			}
								
			DesktopWeb.Ajax.doSmartviewAjax(_detlOptionsView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);			
			
			function responseHandler(success, responseXML)
			{			
				if (success)
				{
					callbackFn(IFDS.Xml.getNode(responseXML, 'dtGetPortDetlOptionsResponse'));
				}
			}			
		}
		
		,fetchClassList : function(fundCode, shGroupListXML, callbackFn)
		{			
			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, 'fund', fundCode);
			IFDS.Xml.appendNode(requestXML, IFDS.Xml.cloneDocument(shGroupListXML));
								
			DesktopWeb.Ajax.doSmartviewAjax(_detlClassListView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{			
				if (success)
				{					
					callbackFn(IFDS.Xml.getNode(responseXML, '*/List[@listName="ClassLists"]'));
				}
			}			
		}
		
		,filterDetlRecords: function(record){								
			if(record)
			{									
				var showRecord = (record.data.runMode != _self.DEL);
				if (_resources.fields['activeOnly'].getValue())
				{										
					showRecord = showRecord && (record.data.active.toLowerCase() == 'yes');
				}
				
				if (!showRecord && record == _resources.grids['detls'].getSelectedRecord())
				{					
					_resources.grids['detls'].clearSelectedRecord();
					_self.updateGridButtons();
				}
				return showRecord;
			}
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
									
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(_portfolioInfoXML), responseHandler, null);
			function responseHandler(success, responseXML, contextErrors)
			{				
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{					
					updateStatus = DesktopWeb._FAIL
					storeContextErrors(contextErrors);
					_resources.grids['mstrs'].loadData(_portfolioInfoXML);
															
					var recIndex = _resources.grids['mstrs'].getStore().findBy(function(rec){return rec.data['errorMsg'].length > 0});										
					if (recIndex)
					{						
						_resources.grids['mstrs'].setSelectedRecord(recIndex);
					}
				}				
			}
			return updateStatus;
		}
	}
}