/*********************************************************************************************
 * @file	TrailerFeeInquiry.Controller.js	
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Trailer Fee Inquiry screen
 *********************************************************************************************/
/*
 * Procedure: TrailerFeeInquiry.Controller.js
 *
 * Purpose  : Translation JS file file for Trailer Fee Inquiry screen
 *             
 * Notes    : System Maintenance --> Trailer Fee Inquiry
 *
 * History  :  
 *		28 Apr 2014 N. Suanlamyai P0225140 T55105
 *					- Created
 *
 *		02 Jun 2014 N. Suanlamyai P0225140 DFT0034605 T55222
 *					- Fixed Start Date and End Date fields are not accepting February.
 *
 *		19 Aug 2014 N. Suanlamyai P0225140 DFT0038019 T55596
 *					- User is allowed to inquiry trailer fee with combination of account and fund/class.
 *
 */
 
DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    var _initService = '';
    var _reloadService = '';
	var _classSearchService = 'classSearch';
	var _trailerFeeSearchService = 'dtTrailerFeeDetlInq';
    
	var _currentSearchCriteria	= new Array();
	var _permissionsMap	= new Array();
	var _configurationMap = new Array();
	
	var _initTrlFeeXML = null;
	var _trlFeeXML = null;
	
    var _nextStartRecNum = 0;
	var _requestRecNum = 25;
    var _nextStartRecNumDetl = 0;
	var _requestRecNumDetl = 25;
	
	// PRIVATE METHODS ****************************************
	function storePermission(initViewXML)
	{
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == _self.YES;
	}
	
	function loadDefaultSearchCriteria(initViewXML)
	{
		var fromMonth = IFDS.Xml.getNodeValue(initViewXML, '//fromMonth');
		var fromYear = IFDS.Xml.getNodeValue(initViewXML, '//fromYear');
		var toMonth = IFDS.Xml.getNodeValue(initViewXML, '//toMonth');
		var toYear = IFDS.Xml.getNodeValue(initViewXML, '//toYear');

		var startDate = new Date(fromYear, fromMonth - 1, 1);
		var endDate = new Date(toYear, toMonth - 1, 1);

		_resources.fields['startDateFld'].setValue(startDate);
		_resources.fields['endDateFld'].setValue(endDate);
		
		_self.salesRepByBranch = _configurationMap['salesRepbyBranch'];
	}
	
	function loadConfigurations(initViewXML)
	{
		_configurationMap['salesRepbyBranch'] = IFDS.Xml.getNodeValue(initViewXML, '//salesRepbyBranch').toLowerCase() == _self.YES;
	}
	
	function loadDropdowns(initViewXML)
	{
		// No dropdown
	}
	
	function loadClass(fundCode)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'fundCode', fundCode);
										
		DesktopWeb.Ajax.doSmartviewAjax(_classSearchService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
		
		function responseHandler(success, responseXML)
		{										
			if (success)
			{
				_resources.fields['classFld'].enable();
				_resources.fields['classFld'].loadData(IFDS.Xml.getNode(responseXML, '/*//Classes'));
			}
		}
	}
	
	function doSearch(append)
	{
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'agencyCode', _currentSearchCriteria['agencyCode']);
		IFDS.Xml.addSingleNode(dataXML, 'branch', _currentSearchCriteria['branch']);
		IFDS.Xml.addSingleNode(dataXML, 'agentCode', _currentSearchCriteria['agentCode']);
		IFDS.Xml.addSingleNode(dataXML, 'account', _currentSearchCriteria['account']);
		IFDS.Xml.addSingleNode(dataXML, 'fund', _currentSearchCriteria['fund']);
		IFDS.Xml.addSingleNode(dataXML, 'class', _currentSearchCriteria['class']);
		IFDS.Xml.addSingleNode(dataXML, 'fromMonth', _currentSearchCriteria['fromMonth']);
		IFDS.Xml.addSingleNode(dataXML, 'fromYear', _currentSearchCriteria['fromYear']);
		IFDS.Xml.addSingleNode(dataXML, 'toMonth', _currentSearchCriteria['toMonth']);
		IFDS.Xml.addSingleNode(dataXML, 'toYear', _currentSearchCriteria['toYear']);
		
		IFDS.Xml.addSingleNode(dataXML, 'runMode', 'summary');
		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?_nextStartRecNum:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);
		
		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_trailerFeeSearchService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{						
            // hanldle response
			if (success){
            	if (append)
				{
            		// User clicks More button
					IFDS.Xml.appendNode(IFDS.Xml.getNode(_trlFeeXML, '//TrailerFees'), 
										IFDS.Xml.cloneDocument(IFDS.Xml.getNode(responseXML, '//TrailerFee')));
					_resources.grids['trlSumGrid'].appendData(IFDS.Xml.cloneDocument(IFDS.Xml.getNode(responseXML, '//TrailerFees')));
					_resources.grids['trlSumGrid'].setSelectedRecord(_nextStartRecNum - 1);
				}else{
            		_trlFeeXML = IFDS.Xml.cloneDocument(responseXML);
					_resources.grids['trlSumGrid'].loadData(_trlFeeXML);
				}
			}
			
            // control more button
			_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
			if (_nextStartRecNum)
			{
				_resources.grids['trlSumGrid'].enableButton('moreBtn');
			}
			else
			{
				_resources.grids['trlSumGrid'].disableButton('moreBtn');
			}
		}
	}
	
	function loadSummaryTable(trlFeeXML, append)
	{
		if(append)
		{
			_resources.grids['trlSumGrid'].appendData(trlFeeXML);
			_resources.grids['trlSumGrid'].setSelectedRecord(_nextStartRecNumDetl - 1);
		}else{
			_resources.grids['trlSumGrid'].loadData(trlFeeXML);
		}
	}

	function loadTrailerFeeDetails(aFund, aClass, append)
	{
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'agencyCode', _currentSearchCriteria['agencyCode']);
		IFDS.Xml.addSingleNode(dataXML, 'branch', _currentSearchCriteria['branch']);
		IFDS.Xml.addSingleNode(dataXML, 'agentCode', _currentSearchCriteria['agentCode']);
		IFDS.Xml.addSingleNode(dataXML, 'account', _currentSearchCriteria['account']);
		IFDS.Xml.addSingleNode(dataXML, 'fund', aFund);
		IFDS.Xml.addSingleNode(dataXML, 'class', aClass);
		IFDS.Xml.addSingleNode(dataXML, 'fromMonth', _currentSearchCriteria['fromMonth']);
		IFDS.Xml.addSingleNode(dataXML, 'fromYear', _currentSearchCriteria['fromYear']);
		IFDS.Xml.addSingleNode(dataXML, 'toMonth', _currentSearchCriteria['toMonth']);
		IFDS.Xml.addSingleNode(dataXML, 'toYear', _currentSearchCriteria['toYear']);
		
		IFDS.Xml.addSingleNode(dataXML, 'runMode', 'detail');
		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?_nextStartRecNumDetl:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNumDetl);
		
        // call service
		DesktopWeb.Ajax.doSmartviewAjax(_trailerFeeSearchService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{						
            // hanldle response
			if (success){
				if (append)
				{
					_resources.grids['trlDetlGrid'].appendData(IFDS.Xml.getNode(responseXML, "//TrailerFees/TrailerFee/TrailerFeeDetls"));
					_resources.grids['trlDetlGrid'].setSelectedRecord(_nextStartRecNumDetl - 1);
				}else{
					_resources.grids['trlDetlGrid'].loadData(IFDS.Xml.getNode(responseXML, "//TrailerFees/TrailerFee/TrailerFeeDetls"));
				}
			}
			
            // control more button
			_nextStartRecNumDetl = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
			if (_nextStartRecNumDetl)
			{
				_resources.grids['trlDetlGrid'].enableButton('moreBtn');
			}
			else
			{
				_resources.grids['trlDetlGrid'].disableButton('moreBtn');
			}
		}
	}
	
	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}

	function disableScreen()
	{
		_resources.fields['brokerFld'].disable();
		_resources.fields['branchFld'].disable();
		_resources.fields['slsrepFld'].disable();
		_resources.fields['acctFld'].disable();
		_resources.fields['fundFld'].disable();
		_resources.fields['classFld'].disable();
		_resources.fields['startDateFld'].disable();
		_resources.fields['endDateFld'].disable();
		_resources.buttons['searchBtn'].disable();
	}

	// PUBLIC ITEMS *************************************
	return {
		
        updatesFlag: false
		,salesRepByBranch: true
		,YES: 'yes'
		,NO: 'no'

		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;			

            // Call init service
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'runMode', 'init');
			
			DesktopWeb.Ajax.doSmartviewAjax(_trailerFeeSearchService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
            
			function responseHandler(success, responseXML)
			{
                // Handle response
				_initTrlFeeXML = responseXML;
				
				// Load configuration 
				loadConfigurations(responseXML);
				
                // Load permission if success
                storePermission(responseXML);
				
                // Load dropdown if success
                
                // Call render screen function
				if (_permissionsMap[_self.INQ])
				{
					loadDefaultSearchCriteria(responseXML);				
				}else{
					disableScreen();
				}
			}
		}

		,handleFundPopulated: function(fundCode)
		{
			// enable the class dropdown field and load classes that belong to a selected fund
			loadClass(fundCode);
		}

		,searchIsValid: function()
		{
			// Clear all invalid
			_resources.fields['brokerFld'].clearInvalid();
			if (this.salesRepByBranch) _resources.fields['branchFld'].clearInvalid();
			_resources.fields['slsrepFld'].clearInvalid();
			_resources.fields['startDateFld'].clearInvalid();
			_resources.fields['endDateFld'].clearInvalid();
			_resources.fields['acctFld'].clearInvalid();
			_resources.fields['fundFld'].clearInvalid();
			
			// Validate Search Criteria
			var isValid = true;
			isValid = _resources.fields['brokerFld'].isValid() && isValid;
			if (this.salesRepByBranch) isValid = _resources.fields['branchFld'].isValid() && isValid;
			isValid = _resources.fields['slsrepFld'].isValid() && isValid;
			isValid = _resources.fields['startDateFld'].isValid() && isValid;
			isValid = _resources.fields['endDateFld'].isValid() && isValid;
			
			if (_resources.fields['startDateFld'].isValid() && _resources.fields['endDateFld'].isValid())
			{
				// Start Date cannot be more than End Date
				var startDate = _resources.fields['startDateFld'].getValue();
				var endDate = _resources.fields['endDateFld'].getValue();
				var isValidDate = true;
				
				if (startDate > endDate)
				{
					_resources.fields['startDateFld'].markInvalid(_translationMap['ERR_StartDateNotMoreThanEndDate']);
					isValidDate = false;
					isValid = false;
				}
				
				if (isValidDate)
				{
					// Period cannot be more than 1 year
					var diffYear = endDate.getYear() - startDate.getYear();
				
					if (diffYear < 0)
					{
						// (end Date > start Date) is not valid.
						_resources.fields['startDateFld'].markInvalid(_translationMap['ERR_StartDateNotMoreThanEndDate']);
						isValid = false;
					}else if (diffYear > 0)
					{
						if (diffYear > 1)
						{
							// Obviously it is more than one year
							_resources.fields['startDateFld'].markInvalid(_translationMap['ERR_PeriodNotMoreThanOneYear']);
							_resources.fields['endDateFld'].markInvalid(_translationMap['ERR_PeriodNotMoreThanOneYear']);
							isValid = false;
						}else{
							var diffMonth = (11 - startDate.getMonth()) + 1 /* 1 for start month */ + endDate.getMonth() + 1 /* 1 for end month */; 
							if (diffMonth > 12 ){
								_resources.fields['startDateFld'].markInvalid(_translationMap['ERR_PeriodNotMoreThanOneYear']);
								_resources.fields['endDateFld'].markInvalid(_translationMap['ERR_PeriodNotMoreThanOneYear']);
								isValid = false;
							}
						}
					}
				}
			}
			
			return isValid;
		}
		
		,doSearch: function()
		{
			// Store search criteria; they would be used for more button
			_currentSearchCriteria['agencyCode'] = _resources.fields['brokerFld'].getValue();
			_currentSearchCriteria['branch'] = _resources.fields['branchFld'].getValue();
			_currentSearchCriteria['agentCode'] = _resources.fields['slsrepFld'].getValue();
			_currentSearchCriteria['account'] = _resources.fields['acctFld'].getValue();
			_currentSearchCriteria['fund'] = _resources.fields['fundFld'].getValue();
			_currentSearchCriteria['class'] = _resources.fields['classFld'].getValue();

			var startDate = _resources.fields['startDateFld'].getValue();
			var endDate = _resources.fields['endDateFld'].getValue();
			_currentSearchCriteria['fromMonth'] = startDate.getMonth() + 1;
			_currentSearchCriteria['fromYear'] = startDate.getYear();
			_currentSearchCriteria['toMonth'] = endDate.getMonth() + 1;
			_currentSearchCriteria['toYear'] = endDate.getYear();
			
			// Clear data in grid before do actual search
			clearGrid('trlDetlGrid');
			clearGrid('trlSumGrid');
			
			// Call doSearch
			doSearch(false);
		}
		
		,doReload: function()
		{					
			// Call doSearch with append and more
			doSearch(true);
		}
		
		,handleSummaryRecordSelectChange: function(aFund, aClass)
		{
			// Clear data in grid before do new load
			clearGrid('trlDetlGrid');
			
			// Handle selecting summary record
			loadTrailerFeeDetails(aFund, aClass, false);
		}
		
		,loadMoreDetailsTable: function()
		{
			loadTrailerFeeDetails(_resources.grids['trlSumGrid'].getSelectedRecord().data['fund']
							, _resources.grids['trlSumGrid'].getSelectedRecord().data['class']
							, true);
		}
	}	
}	