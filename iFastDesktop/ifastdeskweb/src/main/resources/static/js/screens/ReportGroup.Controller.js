/*
 * Procedure: ReportGroup.Controller.js
 *
 * Purpose  : ReportGroup screens manage reportgroup data 			  
 *             
 * Notes    : Open screens by Menu -> MF and MFR Maintenance -> Report Group
 *							  Menu -> System Maintenance -> Holding Company -> Report Groups
 *
 * History  : 
 *	
 *		5 Mar 2013 Hirun Sartsangchan PETP0206635 FN01 MFR MFI Enhancements
 *			- Created
 *
 *		9 May 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3316087 T53528
 *			- Fix the prepopulate  screen when launching from Main Menu by 
 *			The Prepopulate will be
 *			1)Holding Company must be editable.
 *			2)There is any data on grid so the pre-populate of holding company 
 *              on Add screen is follow the selected record.
 *			3)There is no data on Grid so the pre-populate of holding company 
 *              on Add screen is follow the Holding Company Search criteria if this field is not blank
 *			4)Otherwise there is no pre-populate on Add screen
 *		
 *		23 May 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3330320 T53597
 *			- When launching screen from Holding Company, the As Of Date has to set 
 *            and there is no error message on initiate screen.
 *          - Fix display Delivery Name as 2 lines
 *          - Fix setting default value of language to Eng and Supplement Req to No
 *          - Fix Report Group info has not to cleared when a user presses Add/Modify button
 *          - Support launching screen from Account Associate screen 
 *
 *		29 May 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3338220 T53638
 *          - Change the update state by
 *          1) Call with  validation mode
 *          2) if there is no error, call commit screen which will make the update to database.
 *  
 *		10 Jun 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3343398 T53727
 *         - Fix The report group google suggle cannot select the record which 
 *           there are different reportgroup name but the same reportGroup id.
 *
 *		10 Jul 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3359189 T53824
 *          - Update query province and language to search by exact code.
 *
 *		05 Aug 2013 Gomoot Thawornwachirakun PETP0206635 FN01 DFT0012847 T53963
 *          - Add ability to set dynamic mandatory PSTL field on selected country
 *
 *    11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *		24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *			- Fixed screens don't response when user's profile has too many slots attached.   
 */
 

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _holdingCompanySearchService = 'holdingCompanySearch';
	var _dtReportGroupInqService = 'dtReportGroupInq';	
	var _rptGrpSearchView = 'ReportGroupSearch';
	var _suggestRptGrpSearch = "reportGroup"
	
	var _dtReportGroupUpdService = 'dtReportGroupUpd';
	var _historyService = 'dtHistoricalInfo';	
	
	var _lastSearchHoldingCompany = '';
	var _lastSearchReportGroup = '';
	var _lastSearchReportGroupUUID = '';
	var _lastSearchAsDateOptCheck = '';
	var _lastSearchAsOfDate = '';

	var _nextRecNum = null;
	var _requestRecNum = 25;
	var _permissionsMap = {};
	var _defaultValues = {};
	var _defaultHoldingEntity = {};
	
	var _cnewitem = 0;
	var _lockHoldingCompanyBySearch = false;
	var _lockHoldingCompanyByDefault = false;
		
	// PRIVATE METHODS ****************************************
	function loadPopups(initViewXML)
	{		
		if (IFDS.Xml.getNode(initViewXML, '/*//List[@listName="provCountries"]'))		
		_resources.popups['reportGroup'].getField('province').getStore().loadData(
				IFDS.Xml.getNode(initViewXML, '/*//List[@listName="provCountries"]'));	
		if (IFDS.Xml.getNode(initViewXML, '/*//List[@listName="languages"]'))
		_resources.popups['reportGroup'].getField('language').getStore().loadData(
				IFDS.Xml.getNode(initViewXML, '/*//List[@listName="languages"]'));	
	}
	
	function storePermissions(initViewXML)
	{				
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/delPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/inqPerm').toLowerCase() == 'yes';		
	}
	
	function storeDefaultValues(DefaultValuesXML)
	{
		_defaultValues['effectiveDate'] =  DesktopWeb.Util.getDateDisplayValue(
									IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/effectiveDate'));
		_defaultValues['stopDate'] =  DesktopWeb.Util.getDateDisplayValue(
									IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/stopDate'));	
		_defaultValues['languages']  =  IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'languages']");
	}
	
	function storeHoldingEntityDisp(HoldingEntityDispXML)
	{	
		_defaultHoldingEntity['holdingEntityCode'] = IFDS.Xml.getNodeValue(HoldingEntityDispXML, '/*//holdingEntityDisp/holdingEntityCode');
		_defaultHoldingEntity['holdingEntityDesc'] = IFDS.Xml.getNodeValue(HoldingEntityDispXML, '/*//holdingEntityDisp/holdingEntityDesc');
		_defaultHoldingEntity['displayValue'] = IFDS.Xml.getNodeValue(HoldingEntityDispXML, '/*//holdingEntityDisp/displayValue');
	}
	
	function setHoldingEntityDisp()
	{	
		var record  = _resources.fields['holdingCompanySrch'].selectedRecord;
		
		if (record != null)
		{
			_defaultHoldingEntity['holdingEntityCode'] = record.data['holdingCompanyCode'];		
			_defaultHoldingEntity['holdingEntityDesc'] = record.data['holdingCompanyDesc'];
			_defaultHoldingEntity['holdingEntityValue'] = record.data['displayValue'];	
		}
		else
		{
			_defaultHoldingEntity['holdingEntityCode'] = "";
			_defaultHoldingEntity['holdingEntityDesc'] = "";
			_defaultHoldingEntity['holdingEntityValue'] = "";
		}
	}
			
	function isNewRecord(record)
	{
		return record.data['runMode'] == _self.ADD
	}
	
	function getUpdatedRecordCount()
	{		
		var store = _resources.grids['reportGroupInfo'].getStore();
		var newRecords = store.query('runMode', _self.ADD);	
		var modRecords = store.query('runMode', _self.MOD);		
		var delRecords = store.query('runMode', _self.DEL);
		return newRecords.length + modRecords.length + delRecords.length 
	}
	
	function buildUpdateXML(mode)
	{				
		var updateXML = IFDS.Xml.newDocument('data');
		var store = _resources.grids['reportGroupInfo'].getStore();		

		var reportGroups = IFDS.Xml.addSingleNode(updateXML, 'ReportGroups');	  
		IFDS.Xml.addSingleNode(reportGroups, 'runMode', mode);		
		var delRecords = store.query('runMode', _self.DEL);
		delRecords.each(addToXML);
		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToXML);
		var newRecords = store.query('runMode', _self.ADD);
		newRecords.each(addToXML);

		
		return updateXML;
		
		function addToXML(item)
		{
			var recordXML = IFDS.Xml.addSingleNode(reportGroups, 'ReportGroupDetl');			
			IFDS.Xml.addAttribute(recordXML, 'RecordSource', item.data['reportGroupIndex']);
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item.data['runMode']);
			IFDS.Xml.addSingleNode(recordXML, 'reportGroupIndex', item.data['reportGroupIndex']);
			IFDS.Xml.addSingleNode(recordXML, 'holdingCompanyCode', item.data['holdingEntityCode']);
			IFDS.Xml.addSingleNode(recordXML, 'reportGroupID', item.data['reportGroupID']);
			IFDS.Xml.addSingleNode(recordXML, 'reportGroupName', item.data['reportGroupName']);
			IFDS.Xml.addSingleNode(recordXML, 'reportGroupName2', item.data['reportGroupName2']);
			IFDS.Xml.addSingleNode(recordXML, 'deliveryName1', item.data['deliveryName1']);
			IFDS.Xml.addSingleNode(recordXML, 'deliveryName2', item.data['deliveryName2']);
			IFDS.Xml.addSingleNode(recordXML, 'address1', item.data['address1']);
			IFDS.Xml.addSingleNode(recordXML, 'address2', item.data['address2']);			
			IFDS.Xml.addSingleNode(recordXML, 'address3', item.data['address3']);
			IFDS.Xml.addSingleNode(recordXML, 'address4', item.data['address4']);
			IFDS.Xml.addSingleNode(recordXML, 'city', item.data['city']);
			IFDS.Xml.addSingleNode(recordXML, 'province', item.data['province']);			
			IFDS.Xml.addSingleNode(recordXML, 'pstl', item.data['pstl']);
			IFDS.Xml.addSingleNode(recordXML, 'supplyInfoReq', item.data['supplyInfoReq']);
			IFDS.Xml.addSingleNode(recordXML, 'language', item.data['langCode']);
			IFDS.Xml.addSingleNode(recordXML, 'effectiveDate', DesktopWeb.Util.getSMVDateValue(item.data['effectiveDate']));
			IFDS.Xml.addSingleNode(recordXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(item.data['stopDate']));
			IFDS.Xml.addSingleNode(recordXML, 'version', item.data['version']);		
		}		
	}

	function doSearch(holdingCompany, reportGroup, effectiveAsOfDateOptCheck, effectiveAsOfDate, runMode, append)
	{		
		var paramXML = IFDS.Xml.newDocument('data');
			
		if (holdingCompany && holdingCompany.length > 0) IFDS.Xml.addSingleNode(paramXML, 'holdingEntityCode', holdingCompany);
		if (reportGroup && reportGroup.length > 0) 
		{
			IFDS.Xml.addSingleNode(paramXML, 'reportGroupID', reportGroup);		
		}
		if (effectiveAsOfDateOptCheck && effectiveAsOfDate && effectiveAsOfDate.length > 0) 
			IFDS.Xml.addSingleNode(paramXML, 'effectiveDate', DesktopWeb.Util.getSMVDateValue(effectiveAsOfDate));
		
		
		IFDS.Xml.addSingleNode(paramXML, 'runMode', 'reload');			
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', (_nextRecNum)?_nextRecNum:'1');
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);
			
		DesktopWeb.Ajax.doSmartviewAjax(_dtReportGroupInqService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);		
		function responseHandler(success,responseXML)
		{		
			if (IFDS.Xml.getNode(responseXML, _dtReportGroupInqService + 'Response'))
			{
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _dtReportGroupInqService + 'Response')); 
				_self.updateActionButtons();
				
				storeHoldingEntityDisp(responseXML);
				_lockHoldingCompanyBySearch = false;
				
				if (smartviewResults.successful)
				{									
					loadReportGroupGrid(IFDS.Xml.getNode(responseXML, "//ReportGroups"),append);
					updateMoreButton(responseXML);				
				}
				
				if (!append)
					_self.updatesFlag = false;
			}
		}
		
	}	
	
	function loadReportGroupGrid(reportGroupXML,append)
	{			
		if (reportGroupXML != null )
		{
			_resources.grids['reportGroupInfo'].getStore().loadData(IFDS.Xml.getNode(reportGroupXML, '/*//ReportGroups'),append);			
			refreshGrdreportGroupInfo(0);			
			_lockHoldingCompanyBySearch = true;
		}
	}
	
	function setDefaultSearch(state, date)
	{
		if (_defaultHoldingEntity['HoldingEntityCode'] != _self.BLANK && _defaultHoldingEntity['HoldingEntityCode'] != undefined)
			setDefaultHoldingCompanySearch();
			
		_resources.fields['asOfDate'].setValue(_defaultValues['effectiveDate']);
		
		if (state == "init")
		{
			_resources.fields['optSelectAsOfDate'].setValue(true);
			_resources.fields['optSelectAll'].setValue(false);			
		}
		else if (date != "")
			_resources.fields['asOfDate'].setValue(date);

	}
	
	function setDefaultHoldingCompanySearch()
	{						
		var xml = IFDS.Xml.newDocument("data");
		var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
			
		IFDS.Xml.addSingleNode(possibleMatchXML, _resources.fields['holdingCompanySrch'].valueField, _defaultHoldingEntity['holdingEntityCode']);
		IFDS.Xml.addSingleNode(possibleMatchXML, _resources.fields['holdingCompanySrch'].displayField, _defaultHoldingEntity['displayValue']);	
		IFDS.Xml.addSingleNode(possibleMatchXML, "holdingCompanyDesc" , _defaultHoldingEntity['holdingEntityDesc']);	
		
		_resources.fields['holdingCompanySrch'].getStore().loadData(xml);
		_resources.fields['holdingCompanySrch'].setValue(_defaultHoldingEntity['holdingEntityCode']);		
	}
	
	function setDefaultHoldingCompanyPopup(obj)
	{						
		var code = "";
		var dispValue = "";
		var desc = "";
		if (obj)
		{
			code = obj.data['holdingEntityCode'];
			dispValue = obj.data['holdingEntityCode'] + " - " + obj.data['holdingEntityDesc'];	
			desc = obj.data['holdingEntityDesc'];
		}
		else
		{
			var selectedRecord = _resources.grids['reportGroupInfo'].getSelectedRecord();
			
			if (selectedRecord)
			{
				code      = selectedRecord.data['holdingEntityCode'];
				dispValue = selectedRecord.data['holdingEntityCode'] + " - " + selectedRecord.data['holdingEntityDesc'];	
				desc      = selectedRecord.data['holdingEntityDesc'];
			}
			else
			{
				setHoldingEntityDisp();
				code      = _defaultHoldingEntity['holdingEntityCode'];
				dispValue = _defaultHoldingEntity['holdingEntityValue'];
				desc      = _defaultHoldingEntity['holdingEntityDesc'];
			}
		}
		
		if (code != "")
		{

			var xml = IFDS.Xml.newDocument("data");
			var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
				
			IFDS.Xml.addSingleNode(possibleMatchXML, _resources.popups['reportGroup'].getField('holdingCompanySrchPopup').valueField, code);
			IFDS.Xml.addSingleNode(possibleMatchXML, _resources.popups['reportGroup'].getField('holdingCompanySrchPopup').displayField, dispValue);	
			IFDS.Xml.addSingleNode(possibleMatchXML, "holdingCompanyDesc" , desc);
			
			_resources.popups['reportGroup'].getField('holdingCompanySrchPopup').getStore().loadData(xml);
			_resources.popups['reportGroup'].getField('holdingCompanySrchPopup').setValue(code);	
		}		
	}
	
	function storeContextErrors(errorNodes)
	{
		clearContextErrors();
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var reportGroupIndex = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');			
			
			var recordIndex = _resources.grids['reportGroupInfo'].getStore().find('reportGroupIndex', reportGroupIndex);
			var reportGroupErrRecord = _resources.grids['reportGroupInfo'].getStore().getAt(recordIndex);
			
			if (reportGroupErrRecord !== undefined)
			{
				reportGroupErrRecord.set('errMsg', errMsg);
				_resources.grids['reportGroupInfo'].getStore().commitChanges();
				if(firstErrRecIndex==-1)
					firstErrRecIndex = recordIndex;
			}
		}
			
		if(firstErrRecIndex==-1)
		{
			_resources.grids['reportGroupInfo'].getSelectionModel().selectFirstRow();
		}else{
			_resources.grids['reportGroupInfo'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['reportGroupInfo'].focusRow(firstErrRecIndex);
		}
	}
	
	function clearContextErrors(feeAggrID)
	{
		if ( feeAggrID && feeAggrID.length > 0 )
		{
			var recordIndex = _resources.grids['reportGroupInfo'].getStore().find('reportGroupIndex', reportGroupIndex);
			var reportGroupErrRecord = _resources.grids['reportGroupInfo'].getStore().getAt(recordIndex);
			reportGroupErrRecord.set('errMsg', errMsg);
		}else{
			var errReportGroupErrRecord = _resources.grids['reportGroupInfo'].getStore().queryBy(
				function(record, id){
					return (record.get('errMsg') != "");
				}
			);
			errReportGroupErrRecord.each( function resetError(item) { item.set('errMsg', '') });			
			
		}
	}
	
	function refreshGrdreportGroupInfo(index)
	{						
		_resources.grids['reportGroupInfo'].setSelectedRecord(index);		
	}
	
	function updateMoreButton(responseXML)
	{	
		var moreRecNode = IFDS.Xml.getNode(responseXML, "/*//moreRecordsExist");
		if (moreRecNode)
		{					
			var moreRec = IFDS.Xml.getNodeValue(moreRecNode, ".");
			if(moreRec == 'yes')
			{				
				_nextRecNum = IFDS.Xml.getNodeValue(responseXML,"//rangeStartForNext");
				_resources.grids['reportGroupInfo'].enableButton('moreBtn');
			}else{				
				_nextRecNum = null;
				_resources.grids['reportGroupInfo'].disableButton('moreBtn');
			}
		}
	}

	function goToScreen(screenName,reportgroupId, isReadonly, searchUUID
			, holdingSearch, optSelectAsOfDate,asOfDate)
	{
		var params = {};
		params['prevScreen'] = 'ReportGroup';
		params['ReportGroupId'] = reportgroupId;
		params['BrowserTitle'] = 'Account Associate';
		params['from_screen'] = 'ReportGroup';
		
		(isReadonly) ? params['Readonly'] = 'Y' : params['Readonly'] = 'N';
				
		params['ReportGroupSearch'] = searchUUID ;
		params['HoldingEntityCode'] = holdingSearch;			
		params['asOfDate'] = asOfDate;
		params['optSelectAsOfDate'] = optSelectAsOfDate; 
		
		DesktopWeb.Util.goToScreen(screenName, params);
	}
	
	function getUrlVars()
    {
         var vars = [], hash;
         var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
         for(var i = 0; i < hashes.length; i++)
         {
             hash = hashes[i].split('=');                        
             vars[hash[0]] = hash[1];
         }
         return vars;
    }
	 
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		,BLANK: ''		
		,INQ : 'inq'
		,NEWRECORD: 'NEWRPT'
		,updatesFlag: false	
		,cnewitem: _cnewitem		
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			if (DesktopWeb._SCREEN_PARAM_MAP['from_screen'] == 'AcctAssociate')
			{
				var url_vars = getUrlVars();
				for(var i in url_vars)
				{				
					 if (i == 'ReportGroupId' || i == 'ReportGroupSearch')
						DesktopWeb._SCREEN_PARAM_MAP[i] = url_vars[i] ;
				} 
				
				var reportGroupId = DesktopWeb._SCREEN_PARAM_MAP['ReportGroupSearch'];	
				if (reportGroupId != _self.BLANK && reportGroupId != undefined && reportGroupId.length > 0) 
				{
					_self.setSuggestValue(
						_rptGrpSearchView
						, reportGroupId
						, "holdingEntityCode"
						,_defaultHoldingEntity['HoldingEntityCode']
						, _suggestRptGrpSearch
						, _self.initScreen);
				}
				else 
					_self.initScreen();
			}
			else
				_self.initScreen();
		}
		
		, initScreen: function()
		{
			var initParamXML = IFDS.Xml.newDocument('data');
			var state = "init";
			var asOfDate = "";
			var from_screen = DesktopWeb._SCREEN_PARAM_MAP['from_screen']
			var reportGroupUUID = DesktopWeb._SCREEN_PARAM_MAP['ReportGroupSearch'];
			var selectedRecordId = DesktopWeb._SCREEN_PARAM_MAP['ReportGroupId'];
			var option           = DesktopWeb._SCREEN_PARAM_MAP['optSelectAsOfDate'];
			_defaultHoldingEntity['HoldingEntityCode'] = DesktopWeb._SCREEN_PARAM_MAP['HoldingEntityCode'];	
			
			if (from_screen == 'AcctAssociate')
				state = "init2";

			IFDS.Xml.addSingleNode(initParamXML, 'runMode', state);
			
			if (_defaultHoldingEntity['HoldingEntityCode'] != _self.BLANK && _defaultHoldingEntity['HoldingEntityCode'] != undefined)
			{
				IFDS.Xml.addSingleNode(initParamXML, "holdingEntityCode", _defaultHoldingEntity['HoldingEntityCode']);
				
				var isReadonly = DesktopWeb._SCREEN_PARAM_MAP['Readonly'];
				if (isReadonly != _self.BLANK  && isReadonly != undefined && isReadonly == 'N')
				{
					_resources.fields['holdingCompanySrch'].enableField();
					_lockHoldingCompanyByDefault = false;
				} else {
					_resources.fields['holdingCompanySrch'].disableField();
					_lockHoldingCompanyByDefault = true;
				}
			}
			else
			{
				_lockHoldingCompanyByDefault = false;
			}

			if (reportGroupUUID != _self.BLANK && reportGroupUUID != undefined && reportGroupUUID.length > 0) 
			{
				var recordSearch = _resources.fields['reportGroup'].selectedRecord;
				if (recordSearch && recordSearch != undefined)
					IFDS.Xml.addSingleNode(initParamXML, 'reportGroupID', recordSearch.get('reportGroupID'));
			}
			
			//All / Effective As Of
			if (option != _self.BLANK && option != undefined && option.length > 0)
			{
				asOfDate = DesktopWeb._SCREEN_PARAM_MAP['asOfDate'];
				if (option == 'true' && asOfDate && asOfDate && asOfDate.length > 0) 
					IFDS.Xml.addSingleNode(initParamXML, 'effectiveDate', DesktopWeb.Util.getSMVDateValue(asOfDate));
			}
			
			IFDS.Xml.addSingleNode(initParamXML, 'startRecNum', 1);
			IFDS.Xml.addSingleNode(initParamXML, 'requestRecNum', _requestRecNum );
			
			
			DesktopWeb.Ajax.doSmartviewAjax(_dtReportGroupInqService, {ignoreErrorCode: '15'}, initParamXML, responseHandler, _translationMap['ProcMsg_Loading']); 
			function responseHandler(success, responseXML)
			{
				storePermissions(responseXML);
				storeDefaultValues(responseXML);
				storeHoldingEntityDisp(responseXML);
				loadPopups(responseXML);
				setDefaultSearch(state, asOfDate);
				
				
				if (option != _self.BLANK && option != undefined && option.length > 0 )
				{
					if (option == 'true')
					{
						_resources.fields['optSelectAsOfDate'].setValue(true);
						_resources.fields['optSelectAll'].setValue(false);
					}
					else
					{
						_resources.fields['optSelectAsOfDate'].setValue(false);
						_resources.fields['optSelectAll'].setValue(true);
					}
				}
				
				_lockHoldingCompanyBySearch = false;
				_lastSearchHoldingCompany = _resources.fields['holdingCompanySrch'].getValue();
				
				var selectedRptGroup = _resources.fields['reportGroup'].selectedRecord;
				if (selectedRptGroup)
				{
					_lastSearchReportGroup =  selectedRptGroup.data['reportGroupID'];
					_lastSearchReportGroupUUID = selectedRptGroup.data['reportGroupUUID'];
				}
				_lastSearchAsDateOptCheck = _resources.fields['optSelectAsOfDate'].checked;
				_lastSearchAsOfDate = _resources.fields['asOfDate'].getRawValue();
			
				if (success)
				{
					loadReportGroupGrid(IFDS.Xml.getNode(responseXML, "//ReportGroups"));
					
					if (selectedRecordId && selectedRecordId != undefined)
					{
						var index = _resources.grids['reportGroupInfo'].store.find("reportGroupIndex",selectedRecordId);
						_resources.grids['reportGroupInfo'].setSelectedRecord(index);
					}
				}
				_self.updateActionButtons();
				updateMoreButton(responseXML);
				
			}
		
		}
		, setSuggestValue: function(smartview, searchValue, searchHoldCompField, searchHoldCompValue, field, callbackFn)
		{
			var xml = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(xml, 'searchValue', searchValue);
			
			if (searchHoldCompValue != null)
			{
				IFDS.Xml.addSingleNode(xml, searchHoldCompField, searchHoldCompValue);
			}
						
			IFDS.Xml.addSingleNode(xml, 'startRecordNum', '1');
			IFDS.Xml.addSingleNode(xml, 'maxRecords', 14);
			
			DesktopWeb.Ajax.doSmartviewAjax(smartview, {ignoreErrorCode: '199'}, xml, responseHandler, "");

			function responseHandler(success, responseXML)
			{
				if (success)
				{
					
					_resources.fields[field].getStore().loadData(IFDS.Xml.getNode(responseXML, '/*//PossibleMatches'));
					
					if (field == _suggestRptGrpSearch)
						_resources.fields[field].setValue(IFDS.Xml.getNodeValue(responseXML, '/*//reportGroupUUID'));
					else
						_resources.fields[field].setValue(IFDS.Xml.getNodeValue(responseXML, '/*//displayValue'));
						
					if (callbackFn && callbackFn != undefined)
					{
						callbackFn();
					}
				}
			}
		}
		
		,updateActionButtons: function()
		{
			//_resources.grids['reportGroupInfo'].disableAllButtons();
			_resources.grids['reportGroupInfo'].disableButton('addBtn');
			_resources.grids['reportGroupInfo'].disableButton('modBtn');
			_resources.grids['reportGroupInfo'].disableButton('delBtn');								
			_resources.grids['reportGroupInfo'].disableButton('adminBtn');				
			_resources.grids['reportGroupInfo'].disableButton('historicalBtn');
			
			_resources.buttons['btnSearch'].disable();
			
			if(_permissionsMap[this.INQ])
				_resources.buttons['btnSearch'].enable();
			
			if(_permissionsMap[this.ADD])
				_resources.grids['reportGroupInfo'].enableButton('addBtn');
		
			var selectedRecord = _resources.grids['reportGroupInfo'].getSelectedRecord();	
			
			if (selectedRecord)
			{	
				_resources.grids['reportGroupInfo'].enableButton('adminBtn');				
				_resources.grids['reportGroupInfo'].enableButton('historicalBtn');
				Ext.getCmp('AccountList').enable();
				
				if (selectedRecord.data['runMode'] == this.ADD)
				{
					_resources.grids['reportGroupInfo'].enableButton('modBtn');
					_resources.grids['reportGroupInfo'].enableButton('delBtn');
					_resources.grids['reportGroupInfo'].disableButton('adminBtn');				
					_resources.grids['reportGroupInfo'].disableButton('historicalBtn');
					Ext.getCmp('AccountList').disable();
				}
				else
				{								
					if (_permissionsMap[this.MOD])			
					{
						_resources.grids['reportGroupInfo'].enableButton('modBtn');
					}
					else
					{
						_resources.grids['reportGroupInfo'].disableButton('modBtn');
					}
					
					if (_permissionsMap[this.DEL]
						&& selectedRecord.data['allowDelete'] == 'yes')		
					{
						_resources.grids['reportGroupInfo'].enableButton('delBtn');
					}
					else
					{
						_resources.grids['reportGroupInfo'].disableButton('delBtn');
					}
				}
				_self.updateContent();
			}
			else
			{
				_resources.grids['reportGroupInfo'].disableButton('modBtn');
				_resources.grids['reportGroupInfo'].disableButton('delBtn');								
				_resources.grids['reportGroupInfo'].disableButton('adminBtn');				
				_resources.grids['reportGroupInfo'].disableButton('historicalBtn');
				
				Ext.getCmp('AccountList').disable();
			}		
		}	
		
		,openActionPopup: function(action)
		{			
			_resources.popups['reportGroup'].init(action);
			_resources.popups['reportGroup'].show();
			_self.populateReportGroup(action);
		}
		
		, populateReportGroup : function(action)
		{

			if (_lockHoldingCompanyByDefault)
			{							
				_resources.popups['reportGroup'].getField('holdingCompanySrchPopup').disableField();
			}
			else
			{				
				_resources.popups['reportGroup'].getField('holdingCompanySrchPopup').enableField();
			}
										
			switch(action)
			{
				case _self.ADD:
				{		
					_resources.popups['reportGroup'].getField('reportGroupID').enableField();
					
					setDefaultHoldingCompanyPopup(null);
					
					_resources.popups['reportGroup'].getField('effectiveDate').setValue(_defaultValues['effectiveDate']);
					_resources.popups['reportGroup'].getField('stopDate').setValue(_defaultValues['stopDate']);
					_resources.popups['reportGroup'].getField('language').setValue(_defaultValues['languages']);
					_resources.popups['reportGroup'].getField('supplyInfoReq').setValue("no");	

					break;
				}
				case _self.MOD:
				{											
					var rec = _resources.grids['reportGroupInfo'].getSelectedRecord();	
					if (rec.data['runMode'] != _self.ADD)
					{ 
						//For Modify mode, the reportGroupID and holding company must not be modified .
						_resources.popups['reportGroup'].getField('reportGroupID').disableField();
						_resources.popups['reportGroup'].getField('holdingCompanySrchPopup').disableField();
					} 
					else
					{
						_resources.popups['reportGroup'].getField('reportGroupID').enableField();
						_resources.popups['reportGroup'].getField('holdingCompanySrchPopup').enableField();
					}
						
					if (rec)
					{		
						setDefaultHoldingCompanyPopup(rec);
						_resources.popups['reportGroup'].getField('reportGroupID').setValue(rec.data['reportGroupID']);
						
						_resources.popups['reportGroup'].getField('reportGroupName').setValue(rec.data['reportGroupName']);
						_resources.popups['reportGroup'].getField('reportGroupName2').setValue(rec.data['reportGroupName2']);
						_resources.popups['reportGroup'].getField('effectiveDate').setValue(rec.data['effectiveDate']);
						_resources.popups['reportGroup'].getField('stopDate').setValue(rec.data['stopDate']);
						_resources.popups['reportGroup'].getField('deliveryName1').setValue(rec.data['deliveryName1']);
						_resources.popups['reportGroup'].getField('deliveryName2').setValue(rec.data['deliveryName2']);
						_resources.popups['reportGroup'].getField('address1').setValue(rec.data['address1']);
						_resources.popups['reportGroup'].getField('address2').setValue(rec.data['address2']);
						_resources.popups['reportGroup'].getField('address3').setValue(rec.data['address3']);
						_resources.popups['reportGroup'].getField('address4').setValue(rec.data['address4']);
						
						_resources.popups['reportGroup'].getField('city').setValue(rec.data['city']);
						
						_resources.popups['reportGroup'].getField('province').setValue(rec.data['province']);
						_resources.popups['reportGroup'].getField('pstl').setValue(rec.data['pstl']);				
						_resources.popups['reportGroup'].getField('language').setValue(rec.data['langCode']);
						_resources.popups['reportGroup'].getField('supplyInfoReq').setValue(rec.data['supplyInfoReq']);	
					}
					break;
				}
			}
		}
		
		, deleteSelectedRecord: function()
		{		
			var tempRecord = _resources.grids['reportGroupInfo'].getSelectedRecord();
			var index  = _resources.grids['reportGroupInfo'].store.indexOf(tempRecord)
			
			if (tempRecord.data['runMode'] == this.ADD)
			{
				_resources.grids['reportGroupInfo'].removeSelectedRecord();										
			}					
			else
			{
				
				tempRecord.data['runMode'] = this.DEL;
				tempRecord.commit();
				_resources.grids['reportGroupInfo'].store.filterBy(function(record) {
					return record.data.runMode != _self.DEL;
				});										
			}
			
			_resources.grids['reportGroupInfo'].setSelectedRecord(index - 1 <= 0 ? 0 : index - 1 );
			var rec = _resources.grids['reportGroupInfo'].getSelectedRecord();
			if(! rec)
			{
				_self.clearContent();
			}
			
			this.updatesFlag = (getUpdatedRecordCount() > 0);	
			_self.updateActionButtons();
					
		}
		
		,openAdminPopup: function()
		{
			title = _translationMap['ReportGroup']+ ' - ' +_translationMap['Admin']			
			selectrecord = _resources.grids['reportGroupInfo'].getSelectedRecord();
					
			var adminData = {};
			adminData['userName'] = selectrecord.data['createUser'];
			adminData['procDate'] = selectrecord.data['createDate'];
			adminData['modUser'] = selectrecord.data['modifyUser'];
			adminData['modDate'] = selectrecord.data['modifyDate'];
			_resources.popups['admin'].init(title,adminData);
			_resources.popups['admin'].show();
		}
		
		,savePopup: function(action, data)
		{
			if (action == this.ADD)
			{
				_resources.grids['reportGroupInfo'].addRecord(data);
				_resources.grids['reportGroupInfo'].selectLastRecord();
			}
			else if(action == this.MOD)
			{
				if (isNewRecord(_resources.grids['reportGroupInfo'].getSelectedRecord()))
				{
					data['runMode'] = this.ADD
					_resources.grids['reportGroupInfo'].updateSelectedRecord(data);
				}
				else
				{
					_resources.grids['reportGroupInfo'].updateSelectedRecord(data);
				}
				var tempRecord = _resources.grids['reportGroupInfo'].getSelectedRecord();
				var index  = _resources.grids['reportGroupInfo'].store.indexOf(tempRecord)
				_resources.grids['reportGroupInfo'].setSelectedRecord(index);
			}					
			this.updatesFlag = (getUpdatedRecordCount() > 0);		
		}
		
		,doUpdate: function(mode)
		{						
			var updateStatus = null;	
			
			DesktopWeb.Ajax.doSmartviewUpdate(_dtReportGroupUpdService, null, buildUpdateXML(mode), responseHandler, null);			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)				
				{					
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{	
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 																			
				}
			}
			return updateStatus;			
		}	
		
		,doValidateCommitScreen : function()
		{			
			if (_self.doUpdate('validate') == DesktopWeb._SUCCESS)
				DesktopWeb.Util.commitScreen();
		}
		
		,doValidateSearch: function()
		{
			var isSuccess = true;
			
			if (_resources.fields['holdingCompanySrch'].getValue() == _self.BLANK && _resources.fields['reportGroup'].getValue() == _self.BLANK)			
			{
				_resources.fields['holdingCompanySrch'].markInvalid(_translationMap['Error_EitherHoldComOrReportGroup']);
				_resources.fields['reportGroup'].markInvalid(_translationMap['Error_EitherHoldComOrReportGroup']);
				isSuccess = false;
			}
			
			if (_resources.fields['optSelectAsOfDate'].checked && _resources.fields['asOfDate'].getValue() == _self.BLANK)
			{
				_resources.fields['asOfDate'].markInvalid(_translationMap['Error_EffectiveDateRequire']);
				isSuccess = false;
			}
			return isSuccess;
		}
		
		,doValidatePopup: function(action , data)
		{	
			var isSuccess = true;
			if (data['effectiveDate'] == undefined || (data['stopDate'] == undefined ))
			{
				isSuccess = false;
				_resources.popups['reportGroup'].getField('effectiveDate').markInvalid(_translationMap['Error_StartDateOrEndDateIsBlank']);
			}
			else if (data['effectiveDate'] > data['stopDate'])
			{
				isSuccess = false;
				_resources.popups['reportGroup'].getField('effectiveDate').markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
			}
			
			data['effectiveDate'] = _resources.popups['reportGroup'].getField('effectiveDate').getDisplayDateString();
			data['stopDate']      = _resources.popups['reportGroup'].getField('stopDate').getDisplayDateString();
							
			var provRecord = _resources.popups['reportGroup'].getField('province').getSelectedRecord()
			var reqField = (provRecord && provRecord != undefined) ?
				provRecord.data['requirePSTL'] :'';
			if (reqField == 'yes' && data['pstl'] == '')
			{
				isSuccess = false;
				_resources.popups['reportGroup'].getField('pstl').allowBlank = false;
				_resources.popups['reportGroup'].getField('pstl').validate();
			}
			else
			{
				_resources.popups['reportGroup'].getField('pstl').allowBlank = true;
				_resources.popups['reportGroup'].getField('pstl').clearInvalid();
			}
			
			return isSuccess;
		}
		
		,updateContent: function()
		{			
			var selectedRecord = _resources.grids['reportGroupInfo'].getSelectedRecord();
			if (selectedRecord)
			{
				_resources.fields['reportGroupID'].setValue(selectedRecord.data['reportGroupID']);
				_resources.fields['reportGroupName'].setValue(selectedRecord.data['reportGroupName'] + selectedRecord.data['reportGroupName2']);
					
				_resources.fields['effectiveDate'].setValue(selectedRecord.data['effectiveDate']);
				_resources.fields['stopDate'].setValue(selectedRecord.data['stopDate']);
				
				var deliveryNameTemp = selectedRecord.data['deliveryName1'];
				if (selectedRecord.data['deliveryName2'].trim() != '')
					deliveryNameTemp += "\n" +  selectedRecord.data['deliveryName2'];
				_resources.fields['deliveryName1'].setValue(deliveryNameTemp);
				
				_resources.fields['address'].setValue(selectedRecord.data['address1']
								+ "\n" +  selectedRecord.data['address2']
								+ "\n" +  selectedRecord.data['address3']
								+ "\n" +  selectedRecord.data['address4']);
				
				_resources.fields['city'].setValue(selectedRecord.data['city']);
				_resources.fields['province'].setValue(_self.getProvinceCountry(selectedRecord.data['province']));				
				_resources.fields['pstl'].setValue(selectedRecord.data['pstl']);				
				_resources.fields['language'].setValue(_self.getLanguageDesc(selectedRecord.data['langCode']));
				_resources.fields['supplyInfoReq'].setValue(selectedRecord.data['supplyInfoReq']);				
			}
		}
		, getProvinceCountry : function (code)
		{
			var  result = '';
			if (code === undefined || code.trim() === '')  return result ;
			var provStore = _resources.popups['reportGroup'].getField('province').getStore();
			var provRecord = provStore.query('code', new RegExp('^' + Ext.escapeRe(String(code)) + '$'));
			var result = '';
			provRecord.each( function getItem(item)	{ result =  item.data['value']; });
			
			return result
		}
		
		, getLanguageDesc : function (code)
		{
			var  result = '';
			if (code === undefined || code.trim() === '')  return result ;
			var langStore = _resources.popups['reportGroup'].getField('language').getStore();
			var langRecord = langStore.query('code', new RegExp('^' + Ext.escapeRe(String(code)) + '$'));
			
			langRecord.each( function getItem(item)	{ result =  item.data['value']; });
			
			return result
		}	
		
		,clearReportGroupScreen: function(){		
			_resources.grids['reportGroupInfo'].getStore().removeAll();
			_resources.grids['reportGroupInfo'].disableAllButtons();
			_self.clearContent();
		}
		
		
		,clearContent: function(){
			_resources.fields['reportGroupID'].reset();
			_resources.fields['reportGroupName'].reset();
			_resources.fields['effectiveDate'].reset();
			_resources.fields['stopDate'].reset();			
			_resources.fields['deliveryName1'].reset();			
			_resources.fields['address'].reset();
			_resources.fields['city'].reset();
			_resources.fields['province'].reset();
			_resources.fields['pstl'].reset();
			_resources.fields['language'].reset();
			_resources.fields['supplyInfoReq'].reset();
		}

		,clickHandleSearchBtn: function()
		{
			if(_self.doValidateSearch())
			{			
				if(this.updatesFlag){
						DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
						function handlePromptMsg(btn){
							if(btn){
								doSearchCallback();
							}
						}
				}				
				else 
				{					
					doSearchCallback();
				}
				
			}
			
			function doSearchCallback()
			{
				_nextRecNum = 1
				_self.clearReportGroupScreen();

				_lastSearchHoldingCompany = _resources.fields['holdingCompanySrch'].getValue();
				
				var selectedRptGroup = _resources.fields['reportGroup'].selectedRecord;
				if (selectedRptGroup)
				{
					_lastSearchReportGroup =  selectedRptGroup.data['reportGroupID'];
					_lastSearchReportGroupUUID = selectedRptGroup.data['reportGroupUUID'];
				}
				_lastSearchAsDateOptCheck = _resources.fields['optSelectAsOfDate'].checked;
				_lastSearchAsOfDate = _resources.fields['asOfDate'].getRawValue();

				
				doSearch(_lastSearchHoldingCompany,
						 _lastSearchReportGroup,
						 _lastSearchAsDateOptCheck,
						 _lastSearchAsOfDate,
						 'reload', 
						 false);
						
			}
		}
		
		,clickHandleAccountListBtn: function()
		{
			var selectedRecord = _resources.grids['reportGroupInfo'].getSelectedRecord();			
			goToScreen("AcctAssociate"
			,selectedRecord.data['reportGroupIndex']
			,_resources.fields['holdingCompanySrch'].readOnly
			,_lastSearchReportGroupUUID
			,_lastSearchHoldingCompany
			,_lastSearchAsDateOptCheck
			,_lastSearchAsOfDate
			);
		}
		
		,clickHandleMoreBtn: function()
		{
			doSearch( _lastSearchHoldingCompany
					, _lastSearchReportGroup
					, _lastSearchAsDateOptCheck
					, _lastSearchAsOfDate			
					, 'reload'
					, true);		
		}
		
		,selectopt: function()
		{
			if (_resources.fields['optSelectAll'].checked)
			{
					_resources.fields['asOfDate'].setDisabled(true);
					_resources.fields['asOfDate'].clearInvalid();
			}
			else if(_resources.fields['optSelectAsOfDate'].checked)
					_resources.fields['asOfDate'].setDisabled(false);
			
		}
		
		,openHistoryPopup: function()
		{
			var viewParam = {};
			var historyName = null;
			var tempRecord  = _resources.grids['reportGroupInfo'].getSelectedRecord();
			
			if (tempRecord != undefined && tempRecord != null)
			{
				viewParam['auditType'] = 'ReportGroup';
				viewParam['searchValue1'] = _resources.grids['reportGroupInfo'].getSelectedRecord().data['reportGroupIndex'];
				historyName = _translationMap['ReportGroup']+ ' - ' +_translationMap['History'];
				
				_resources.popups['history'].init(historyName, _historyService, viewParam, true);
				_resources.popups['history'].show();
			}			
		}
				
		,updateHoldingAndReportGroupSearchText:function()
		{
			if (_resources.fields['holdingCompanySrch'].getValue() != _self.Blank || _resources.fields['reportGroup'].getValue() != _self.Blank )
			{
				_resources.fields['holdingCompanySrch'].clearInvalid();
				_resources.fields['reportGroup'].clearInvalid();
			}
		}
		
		,checkHasAcctAsso: function(action,datafrompopup)
		{	
			var rec = _resources.grids['reportGroupInfo'].getSelectedRecord();
			if (action == _self.MOD && rec.data['hasAcctAsso'] == 'yes' )
			{
				if(rec.data['stopDate'] != datafrompopup['stopDate'])
				{
					alert(_translationMap['Error_WarningChangedStopDate']);
				}
				else if(rec.data['effectiveDate'] != datafrompopup['effectiveDate'])
				{
					alert(_translationMap['Error_WarningChangedEffectiveDate']);
				}
			}
		}
	}	
}	
