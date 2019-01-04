/*********************************************************************************************
 * @file	AcctGovFile.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Tax Payer Maintenance screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  16 Oct 2013 N. Suanlamyai P0193400 DFT0020392 T54325
 *					- Add band permission to the screen. 
 *
 *	20 Jan 2014 Narin Suanlamyai P0223930 FN01 - FATCA 1C
 *					- Remove Modify feature
 *					- Rearrangment screen to support new system design
 *					- Add a new table to display holding details
 * 
 *	26 Feb 2014 G. Thawornwachirakun P0223930 DFT0029664 T54848
 *					- Add ignoreErrorCode 15 on inititate screen
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.  
 *
 *  17 Jul 2017 Matira T. P0264940 P0264940-50 FATCA - CRS Coc
 *          - Add to support 'CRS' Tax regulation
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'ADD';
	var _MOD = 'MOD';
	var _DEL = 'DEL';
	var _DOCSTAT_PENDINGREVIEW = '06';

	var _requestRecNum = 50;
	var _nextRecNum = null;
	var _initGovFileXML = null;
	var _govFileXML = null;
	var _selectedGovFileRecord = null;
		
	var _permissionsMap = {};

	var _lastSearchAccount = '';
	var _lastSearchDocStat = '';
	var _lastSearchEntityAccount = '';
	var _lastSearchStartDate = '';
	var _lastSearchEndDate = '';
	var _lastSearchRegulationCode = '';

	var _dtAcctGovFileInqService = "dtAcctGovFileInq";
	var _accountSearchService = "accountSearch";
	
	// PRIVATE METHODS ****************************************	
	/** Store user permission **/
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function updateAcctGovFileSearchButton()
	{
		if (_permissionsMap[_self.INQ])
		{
			_resources.buttons['searchBtn'].enable();
		}else{
			_resources.buttons['searchBtn'].disable();
		}
	}
	
	function loadDefaultAccount(acctNum)
	{
		if (acctNum && acctNum.length > 0 && acctNum != 'ALL')
		{
			var paramXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(paramXML, 'searchValue', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(paramXML, 'incAllStat', 'yes');
			IFDS.Xml.addSingleNode(paramXML, 'maxRecord', '10');
			IFDS.Xml.addSingleNode(paramXML, 'startRecordNum', '1');
			
			DesktopWeb.Ajax.doSmartviewAjax(_accountSearchService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

			function responseHandler(success, responseXML)
			{
				if (success)
				{
					_resources.fields['acctFld'].getStore().loadData(IFDS.Xml.getNode(responseXML, "//PossibleMatches"));
					_resources.fields['acctFld'].setValue(IFDS.Xml.getNodeValue(IFDS.Xml.getNode(responseXML, "//acctNum") , "."));
					initGovFileScreen();
				}
				else
				{
					
				}
			}
		}else{
			_resources.fields['acctFld'].reset();
		}
	}
	
	function populateDropdownList()
	{
		try
		{
			_resources.fields['docStat'].loadData(IFDS.Xml.getNode(_initGovFileXML, "//List[@listName = 'RequestStatusALL']"));
			_resources.fields['entityAcct'].loadData(IFDS.Xml.getNode(_initGovFileXML, "//List[@listName = 'AccountType']"));
			_resources.fields['regulationCode'].loadData(IFDS.Xml.getNode(_initGovFileXML, "//List[@listName = 'RegulationList']"));
		}catch(err){
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
		}
	}	
	
	function loadDefaultSearchCriteria()
	{
		var defaultValuesNode = IFDS.Xml.getNode(_initGovFileXML, "//DefaultValues");
		if (defaultValuesNode)
		{
			var account = IFDS.Xml.getNodeValue(defaultValuesNode, 'account');
			if (account && account.length > 0)
			{
				_resources.fields['docStat'].setValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'docStatus'));
				_resources.fields['entityAcct'].setValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'entityType'));
			}
			_resources.fields['regulationCode'].setValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'FATCACode'));
			_resources.fields['startDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'startDate')));
			_resources.fields['endDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'endDate')));
		}
	}
	
	function loadAggregaionApply()
	{
		var vAggregationApply = (IFDS.Xml.getNodeValue(_initGovFileXML, "//aggregationApply").toLowerCase() == 'yes');
        
		//If vAggregationApply is 'yes' means Client environment supports Aggregation Balance. Then, this column is enabled
		//Otherwise, Aggregation Balance column is disabled.
		_resources.grids['holdingDetlsGrid'].colModel.setHidden(_resources.grids['holdingDetlsGrid'].colModel.getIndexById('aggrBal'), !vAggregationApply);
	}
	
	function loadGovFileMstrGrid(govFileXML, append)
	{
		if (govFileXML)
		{
			var newGovFileXML = IFDS.Xml.cloneDocument(govFileXML);
			_resources.grids['govFileGrid'].getStore().loadData(govFileXML, append);
			if (append)
			{
				var xmlNodes = IFDS.Xml.getNodes(newGovFileXML, '//IndiciaSearchResultDetls/IndiciaSearchResultDetl');
				Ext.each(xmlNodes, function(xmlNode){				
					IFDS.Xml.appendNode(_govFileXML, xmlNode);	
				});
				var grid = _resources.grids['govFileGrid'];
				grid.focusRow(grid.getRecordIndex(grid.getSelectedRecord()));
			}else{
				_govFileXML = newGovFileXML;
				var numberOfRecords = _resources.grids['govFileGrid'].getStore().getCount();
				if (numberOfRecords > 0) _resources.grids['govFileGrid'].getSelectionModel().selectFirstRow();
			}
		}
	}
	
	function clearGovFileScreen()
	{
	
		_resources.grids['entityDetailsGrid'].getStore().removeAll();
		_resources.grids['holdingDetlsGrid'].getStore().removeAll();
		
		_resources.fields['taxType'].reset();
		_resources.fields['acctType'].reset();
		_resources.fields['acctStat'].reset();
		_resources.fields['acctOpenDate'].reset();
		
		_selectedGovFileRecord = null;
		_govFileXML = null;
		
		_resources.grids['govFileGrid'].getStore().removeAll();
		_resources.grids['govFileGrid'].disableAllButtons();	
	}
	
	function loadEntityDetails(entityDetailsXML)
	{
		if (entityDetailsXML)
		{			
			_resources.grids['entityDetailsGrid'].getStore().loadData(entityDetailsXML, false);
		}
	}
	
	function loadHoldingDetails(holdingDetailsXML)
	{
		if (holdingDetailsXML)
		{			
			_resources.grids['holdingDetlsGrid'].getStore().loadData(holdingDetailsXML, false);
		}
	}
	
	function populateGovFileDetails(record)
	{
		_resources.fields['taxType'].setValue(record.get('taxType'));
		_resources.fields['acctType'].setValue(record.get('acctType'));
		_resources.fields['acctStat'].setValue(record.get('acctStatus'));
		_resources.fields['acctOpenDate'].setValue(record.get('acctOpenDate'));
	}
	
	function initGovFileScreen()
	{
		var acctWebParam = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		if (acctWebParam && acctWebParam.length > 0 && acctWebParam != 'ALL') 
		{
			_resources.fields['acctFld'].disableField();
			_resources.fields['regulationCode'].disableField();
			_resources.fields['docStat'].disableField();
			_resources.fields['entityAcct'].disableField();
			doSearch(acctWebParam, null, null, null, null, null, 'init', false);
		}else{
			doSearch('', null, null, null, null, null, 'init', false);
		}
	}
	
	function doSearch(account, regCode, docStatus, entityType, startDate, endDate, runMode, append)
	{
		var paramXML = IFDS.Xml.newDocument('data');
		_lastSearchAccount = account;
		_lastSearchDocStat = docStatus;
		_lastSearchEntityAccount = entityType;
		_lastSearchStartDate = startDate;
		_lastSearchEndDate = endDate;
		_lastSearchRegulationCode = regCode;
	
		if (account && account.length > 0 && account != 'ALL') IFDS.Xml.addSingleNode(paramXML, 'account', account);
		if (regCode && regCode.length > 0) IFDS.Xml.addSingleNode(paramXML, 'FATCACode', regCode);
		if (docStatus && docStatus.length > 0) IFDS.Xml.addSingleNode(paramXML, 'docStatus', docStatus);
		if (entityType && entityType.length > 0) IFDS.Xml.addSingleNode(paramXML, 'entityType', entityType);
		if (startDate && startDate.length > 0) IFDS.Xml.addSingleNode(paramXML, 'startDate', startDate);
		if (endDate && endDate.length > 0) IFDS.Xml.addSingleNode(paramXML, 'endDate', endDate);
		IFDS.Xml.addSingleNode(paramXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', (_nextRecNum)?_nextRecNum:'1');
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);
		
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtAcctGovFileInqService
							, (runMode == 'init' ? {ignoreErrorCode: '15'} : null)
							, paramXML
							, responseHandler
							, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{			
			var permNode = IFDS.Xml.getNode(responseXML, "//Permissions");
			
			if (runMode == 'init')
			{ 
				if (permNode)
				{
					_initGovFileXML = IFDS.Xml.cloneDocument(responseXML);
					populateDropdownList();
					loadDefaultSearchCriteria();
					loadAggregaionApply();
					storePermissions(responseXML);
					updateAcctGovFileSearchButton();
				}else{
					disableScreen();
				}
			}

			if (success)
			{
				loadGovFileMstrGrid(IFDS.Xml.getNode(responseXML, "//IndiciaSearchResultDetls"), append);
				
				// Looking for more records
				var moreRecNode = IFDS.Xml.getNode(responseXML, "//moreRecordsExist");
				if (moreRecNode)
				{
					var moreRec = IFDS.Xml.getNodeValue(moreRecNode, ".");
					if(moreRec == 'yes')
					{
						_nextRecNum = IFDS.Xml.getNodeValue(IFDS.Xml.getNode(responseXML, "//rangeStartForNext"), ".");
						_resources.grids['govFileGrid'].enableButton('moreBtn');
					}else{
						_nextRecNum = null;
						_resources.grids['govFileGrid'].disableButton('moreBtn');
					}
				}
			}
		}
		
	}
	
	function disableScreen()
	{
		_resources.fields['acctFld'].disable();
		_resources.fields['regulationCode'].disable();
		_resources.fields['docStat'].disable();
		_resources.fields['entityAcct'].disable();
		_resources.fields['startDate'].disable();
		_resources.fields['endDate'].disable();
		_resources.buttons['searchBtn'].disable();
		_resources.grids['govFileGrid'].disableAllButtons();	
	}

	function validateSearchCriteria()
	{
		var isValid = _resources.fields['acctFld'].isValid()
		isValid = _resources.fields['regulationCode'].isValid() && isValid;
		isValid = _resources.fields['docStat'].isValid() && isValid;
		isValid = _resources.fields['entityAcct'].isValid() && isValid;
		isValid = _resources.fields['startDate'].isValid() && isValid;
		isValid = _resources.fields['endDate'].isValid() && isValid;
		if (_resources.fields['startDate'].getValue() >  _resources.fields['endDate'].getValue())
		{
			isValid = false;
			_resources.fields['startDate'].markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
		}
		return isValid;
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var acctParam = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
			if (acctParam && acctParam.length > 0 && acctParam != 'ALL') 
			{
				loadDefaultAccount(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			}else{
				initGovFileScreen();
			}
		}

		,getEntityDetailsXML: function(uuid)
		{
			return  IFDS.Xml.getNode(_govFileXML, "//IndiciaSearchResultDetls/IndiciaSearchResultDetl[FATCADueDiligenceUUID='" + uuid + "']/EntityDetls");
		}
		
		,getHoldingDetailsXML: function(uuid)
		{
			return  IFDS.Xml.getNode(_govFileXML, "//IndiciaSearchResultDetls/IndiciaSearchResultDetl[FATCADueDiligenceUUID='" + uuid + "']/AcctBalanceDetls");
		}
		
		,getSelectGovFileMstr: function()
		{
			return _selectedGovFileRecord;
		}
		
		,selectGovFileMstr: function(record)
		{
			_selectedGovFileRecord = record;
			populateGovFileDetails(record);
			
			loadHoldingDetails(_self.getHoldingDetailsXML(record.data.FATCADueDiligenceUUID));
			loadEntityDetails(_self.getEntityDetailsXML(record.data.FATCADueDiligenceUUID));
		}
		
		,getDisplay: function(listName, code)
		{
			var listNode = IFDS.Xml.getNode(_initGovFileXML, "//List[@listName = '" + listName + "']/Element[code='" + code + "']");
			return (listNode)?IFDS.Xml.getNodeValue(listNode, 'value'):code;
		}
		
		,clickHandle_searchBtn: function()
		{
			if (validateSearchCriteria()){
				var confirmSearch = false;
				clearGovFileScreen();
				_nextRecNum = 1;
				doSearch( _resources.fields['acctFld'].getValue()
							, _resources.fields['regulationCode'].getValue()
							, _resources.fields['docStat'].getValue()
							, _resources.fields['entityAcct'].getValue()
							, _resources.fields['startDate'].getSMVDateString()
							, _resources.fields['endDate'].getSMVDateString()
							, 'reload'
							, false);
			}
		}

		,clickHandle_moreBtn: function()
		{
			doSearch( _lastSearchAccount
						, _lastSearchRegulationCode
						, _lastSearchDocStat
						, _lastSearchEntityAccount
						, _lastSearchStartDate
						, _lastSearchEndDate
						, 'reload'
						, true);
		}
    
    ,clickHandle_Status: function(value)
    {
      var listname = "RequestStatus" + value;
      _resources.fields['docStat'].loadData(IFDS.Xml.getNode(_initGovFileXML, "//List[@listName = '" + listname + "']"));
    }
	}	
}	