/*********************************************************************************************
 * @file	FinanInst.Controller.js
 * @author	Sukjaitham, Supareuk
 * @desc	Resources JS file Financial Institution Regulatory screen.
 *********************************************************************************************/
/*
 * Procedure: FinanInst.Controller.js
 *
 * Purpose  : Controller for Financial Institution Regulatory screen
 *             
 * Notes    : - Setup Financial Institution Regulatory
 *            - Open screen from 
 *               Menu -> System Maintenance -> Financial Institution Regulatory
 *				 Menu -> Broker Level Maintenance -> Broker Regulatory
 *				 Menu -> Broker Level Maintenance -> Intermediary Regulatory
 *				 Menu -> Fund Level Maintenance -> Fund Regulatory
 *
 * History  :  
 *		18 Jul 2013 S. Sukjaitham, G. Thawornwachirakun P0193400 T54301
 *					- Created.
 *
 *		15 Aug 2013 G. Thawornwachirakun P0193400 T54018
 *					- Fix GIIN format 
 *          - Add missing groupType element on dtFinanInstUpd service
 *
 *		23 Aug 2013 G. Thawornwachirakun P0193400 DFT0014730 T54066
 *					- Remove GIIN format 
 *          - Add display warning message from popup screen
 * 
 *		23 Aug 2013 G. Thawornwachirakun P0193400 DFT0019082 T54243
 *					- Fix javascript error when there is any invalid character 
 *            in xml element (identification section)
 *
 *    09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54302
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *    8 Feb 2014 Winnie Cheng P0223057 T77753
 *                  - Added new fields and logic,segeragated FFI search for level
 *                    back-end sent a lists and save new fields values
 *                    back-end sent an error node in returned response xml
 *
 *  20 Feb 2014 Winnie Cheng P0223057 T77795
 *                  - Remove Country disable line of code
 *                    change set Report To Country with code, not description
 *
 *    28 Feb 2014 Winnie Cheng P0223057 T77807 DFT0029706
 *                  - Aggregation FFI shows null when it is blank when reporting FFI is "no"
 *
 *    7 Mar 2014 Winnie Cheng P0223057 T77835 DFT0030208
 *                  - modify functions for setTitle dynamically
 *
 *
 *    12 Mar 2014 Winnie Cheng P0223057 T77851 DFT0030443
 *                  - FFI screens should enable Country/AggregationFFI when ReportingFFI is "Environment Default"
 *
 *    01 Oct 2014 G. Thawornwachirakun P0235711 T55822
 *                  - Modify Apply Lower Threshold to be always updatable
 *                    for Broker and Intermediary level
 *
 *    28 Nov 2014 G. Thawornwachirakun P0235711 DFT0045015 T56120
 *                  - When Reporting FFI is set 'No', 
 *                     the user must be able to select Apply Lower Threshold.
 *                    And this field must not be required field.
 *                  Note: 
 *                   This changed is only for Broker and Intermediary level
 *   
 *    19 Jan 2015 A. Mongkonrat P0205605 I0 T80201
 *                  - FATCA Phase II. Add a new Reporting Unit field and combine grids into tab.
 *
 *    28 Jan 2015 A. Mongkonrat P0205605 I0 T80255
 *                  - FATCA Phase II. Support a new 'Reporting Unit' FFI type.
 *                    Enable Country and Description field for 'Reporting Unit' FFI.
 *                  - Identification Grid doesn't refresh properly.
 *
 *    21 Dec 2015 Watchara Th. P0241558 T81890 FATCA Reporting Enhancement
 *					- Add new tabs (Address and Contact) for
 *					  Fund/Fund Group level and Sponsoring Entity level.
 *
 *    04 Feb 2016 Aurkarn M. P0241558 T82184 DFT0059301 FATCA Reporting Enhancement
 *					- Fix description field inside popup window to hold the original description
 *
 *    09 Jan 2016 Aurkarn M. P0241558 T82213 DFT0059298 FATCA Reporting Enhancement 
 *                  - Fix issue where Country field is not required when other fields inside 'Address' tab not empty
 *
 *    23 Feb 2016 Aurkarn M. P0241558 T82290 DFT0059716 FATCA Reporting Enhancement 
 *                  - In detail panel, field "Code" should displays only Code.
 *
 *    06 Jul 2016 Matira T. P0255392 T83155 2016 FATCA Reporting Enhancements
 *					- Add logic to support new field FISponsor.
 *
 *    17 Oct 2016 Matira T. P0255392 T84039 DFT0068425 2016 FATCA Reporting Enhancements
 *					- Fix confirmation window appears if we naviagte out of the screen without modifying.
 *
 *     3 Feb 2017  Winnie Cheng P0259672  T84745
 *			  - Enhance the screen for CRS Report regulation rule and FATCA change accordingly
 *
 *   20 Jun 2017 Matira T. P0264940 P0264940-35 CRS-FATCA Enhancement 17.5
 *					- remove ResponsibilityTab and respGrd
 *
 *   22 Jan 2018 Matira T. P0268206-125 FATCA 18.3
 *					- re-write layout of screen and support to access by Extract screen.
 *
 *   7 Nov 2018 Umamahesh. P0277786-178 FATCA 19.2
 *					- Added logic to support FilerCategory for FATCA/CRS.
 *
 */
 
DesktopWeb.ScreenController = function(){
	// PRIVATE VARIABLES *************************************
	var _translationMap     = DesktopWeb.Translation.getTranslationMap();
	var _self               = null;
	var _resources          = null;
	var _nextStartRecNum    = null;
	var _requestRecNum      = 25;	//The number of record display on table

	var _dtFFIInqService   		= "dtFinanInstInq";
	var _dtFundFinanInstInq		= "dtFundFinanInstInq";
	var _dtFFIRegulationDetl	= 'srchFinInstRegDetl';
	
	var _dtFFIUpdService    = "dtFinanInstUpd";
	var _dtFFIValService    = "dtFinanInstVal";
	var _dtIdenValService   = "dtFinanIdentVal";
	var _historyService	    = 'dtHistoricalInfo';

	var _searchBroker       = 'brokerSearch';
	var _searchInterm       = 'intrSearch';
	var _searchLegal        = 'entWhereUsedSearch';
	var _searchFundGroup    = 'fundGroupSearch';
	var _searchFund      	= 'fundOnlySearch';

	var _searchAttribute    = {};

	//Default Value
	var _vars               = {};
	var _permissionsMap 	= {};
	var _defaultValues  	= {};

	var _ffiCounter          = 0;
	var _idenCounter         = 0;
	var _idenKey             = 0;

	var _FFIInitXML          = null;
	var _inqFFIresponse      = null;
	var _selectedFFI         = null;
	var _permissionsMap 	 = {};
	var _idenFldsList	     = {};
	var _ffiFldsList	     = {};
	var _ffiFldsCodeList     = {};
	var _searchIDList        = {};
	var _popupList		     = {};
	var _AddressContactFldList = {};
	var _CADD                = 'addBtn';
	var _CMOD                = 'modBtn';
	var _CDEL                = 'delBtn';
	var _CMORE               = 'moreBtn';
	var _CADMIN              = 'adminBtn';
	var _CHISTORY            = 'historicalBtn';
	var _FUNDGROUPTYPEFA	 = 'FATCA';
	var _FUNDGROUPTYPECRS	 = 'CRS';
	var _FUNDGROUPTYPES 	 = 'CRS,FATCA';
	
	var _aggrFFILevelListNode	= null;
	var _aggregationApply 		= null;
	var _service 				= null;
	
	var _fundGroupFATCAListXml= null;
	var _fundGroupCRSListXml= null;
	
	var hasPrevScreen = false;
	
	/** Initialize Foreign Financial Institution Maintenance screen **/
	function initResourceName()
	{
		_searchAttribute['complyRule']             = _self.BLANK;
		_searchAttribute['level']                  = _self.BLANK;
		_searchAttribute['code']                   = _self.BLANK;
		_searchAttribute['groupType']              = _self.BLANK;

		//
		_popupList['FFI']                          = 'finInstPopup';
		_popupList['IDEN']                         = 'idenPopup';
		_popupList['SEARCH']                       = 'search';

		//Search
		_searchIDList[_self.BROKER_LEVEL]	       = 'searchByBroker';
		_searchIDList[_self.LEGALENTITY_LEVEL]	   = 'searchByLegalEntity';
		_searchIDList[_self.FUND_LEVEL]            = 'searchByFund';
		_searchIDList[_self.FUNDGROUP_LEVEL]	   = 'searchByFundGroup';
		_searchIDList[_self.INTERMEDIARY_LEVEL]    = 'searchByIntermediary';

		//FFI specific popup
		_ffiFldsCodeList[_self.BROKER_LEVEL]	   = 'pBrokerFld';
		_ffiFldsCodeList[_self.LEGALENTITY_LEVEL]  = 'pLegalEntityFld';
		_ffiFldsCodeList[_self.FUND_LEVEL]   	   = 'pFundFld';
		_ffiFldsCodeList[_self.FUNDGROUP_LEVEL]	   = 'pFundGroupFld';
		_ffiFldsCodeList[_self.INTERMEDIARY_LEVEL] = 'pIntermediaryFld';

		//FFI data - popup
		_ffiFldsList['complyRule']	               = 'pRegulationFld';
		_ffiFldsList['level']			           = 'pLevelFld';
		_ffiFldsList['fundGroup']		           = 'pFundGroupForLegalEntityFld'
		_ffiFldsList['classification']	           = 'pClassificationFld';
		_ffiFldsList['deff']			           = 'pDeffFld';
		_ffiFldsList['stopDate']		           = 'pStopDateFld';
		_ffiFldsList['reportingFFI']	           = 'pReportingFFIFld';

		_ffiFldsList['description']		           = 'pDescriptionFld';
		_ffiFldsList['countryCode']		          	   = 'pCountryFld';
		_ffiFldsList['aggrffiLevel']		     	  = 'pAggregationLevelFld';
		_ffiFldsList['appLowThres']		           = 'pApplyThresholdFld';
		_ffiFldsList['appLowThresDate']            = 'pApplyThresholdDateFld';
		_ffiFldsList['filerCategory']              = 'pfilerCategoryFld';
		
		// Address and Contact field	
		_AddressContactFldList['contactName'] 	   = 'ContactNameTextField';
		_AddressContactFldList['phoneNum'] 	 	   = 'ContactPhoneNumberTextField';
		_AddressContactFldList['phoneExt'] 		   = 'ContactPhoneExtNumberTextField';
		_AddressContactFldList['email']			   = 'ContactEmailTextField';
		_AddressContactFldList['address1'] 		   = 'Address1TextField';
		_AddressContactFldList['address2'] 		   = 'Address2TextField';
		_AddressContactFldList['address3'] 		   = 'Address3TextField';
		_AddressContactFldList['city'] 			   = 'CityTextField';
		_AddressContactFldList['province'] 		   = 'ProvinceTextField';
		_AddressContactFldList['postalCode'] 	   = 'PostalCodeTextField';
		_AddressContactFldList['country'] 		   = 'CountryDropDown';

		//iden popup field
		_idenFldsList['idType']	                   = 'pIdTypeFld';
		_idenFldsList['idValue']	               = 'pIdValueFld';
		_idenFldsList['deff']		               = 'pDeffFld';
		_idenFldsList['stopDate']                  = 'pStopDateFld';
		_idenFldsList['idStat']                    = 'pStatusFld';
		_idenFldsList['cntryOfIssue']              = 'pCntryFld';
		_idenFldsList['level']                     = 'pLevelFld';
		_idenFldsList['code']                      = 'pCodeFld';
	}

	function initFFIScreen()
	{
		if(DesktopWeb._SCREEN_PARAM_MAP['prevScreen'] == "RegAcctExtr"){
			hasPrevScreen = true;
		}
		initResourceName();
		searchFFI(_searchAttribute, 'init', false);
	}
	

	function enableSearch()
	{
		if (_permissionsMap[_self.INQ])
		{
			_resources.buttons['cmdSearch'].enable();
			_resources.grids['finInstGrd'].enableButton(_CADD);
			_resources.grids['idenGrd'].disableButton(_CADD);
		}
		else
		{
			_resources.buttons['cmdSearch'].disable();
			_resources.grids['finInstGrd'].disableButton(_CMORE);
			_resources.grids['finInstGrd'].disableButton(_CADD);
			_resources.grids['idenGrd'].disableButton(_CADD);
		}
	}


	/** Store user permission **/
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == _self.YES;
		
		if(!hasPrevScreen){
			_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == _self.YES;
			_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == _self.YES;
			_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == _self.YES;
		}
	}
	
	function generateAggregationDropdownLists(oriAggregationListNode, selectedLevelElement, selectedFFICode, selectedDesc)
	{								
		var newAggregationList = IFDS.Xml.newDocument('List');
		var elementList = IFDS.Xml.getNodes(oriAggregationListNode, "Element");
	
		if (selectedFFICode != null && selectedFFICode != ""  && selectedLevelElement != _self.LEGALENTITY_LEVEL) {//selected level/code
			if (selectedLevelElement != null && selectedLevelElement != "") {
				if (selectedDesc != null && selectedDesc != "") {
					var levelElement = IFDS.Xml.newDocument('Element');
					
					IFDS.Xml.addSingleNode(levelElement, 'code', selectedLevelElement + "-" + selectedFFICode);
					IFDS.Xml.addSingleNode(levelElement, 'value', selectedDesc);
					IFDS.Xml.appendNode(newAggregationList, levelElement);
				}
			}
		}
		if (oriAggregationListNode != null) {
			for(var i=0; i<elementList.length; i++)
			{		
				var oriNode = elementList[i];
				var oriCode = IFDS.Xml.getNodeValue(oriNode,'code');
				var oriValue = IFDS.Xml.getNodeValue(oriNode,'value');
				var entityname = IFDS.Xml.getNodeValue(oriNode,'entityname');
				var element = IFDS.Xml.newDocument('Element');
	
				IFDS.Xml.addSingleNode(element, 'code', oriCode + "-" + oriValue);
				IFDS.Xml.addSingleNode(element, 'value', oriValue + " " + entityname);
				IFDS.Xml.appendNode(newAggregationList, element);
			}	
		}
		return newAggregationList;
	}

	/** Load All Dropdown Lists **/
	function populateDropdownList(responseXML)
	{
		var finInstrPopup = _resources.popups[_self.popupList['FFI']];
		var idenPopup = _resources.popups[_self.popupList['IDEN']];

		//regulationList
		var regulationListNode = IFDS.Xml.getNode(responseXML, "//List[@listName='regulationList']");
		if (regulationListNode)
		{
			_resources.fields['regulationSrch'].loadData(regulationListNode);
			finInstrPopup.getField('pRegulationFld').loadData(regulationListNode);
		}

		//FFILevelList
		var FFILevelListNode = IFDS.Xml.getNode(responseXML, "//List[@listName='FFILevelList']");
		if (FFILevelListNode)
		{
			_resources.fields['searchForSrch'].loadData(FFILevelListNode);
			finInstrPopup.getField('pLevelFld').loadData(FFILevelListNode);

			idenPopup.getField('pLevelFld').loadData(FFILevelListNode);
		}

		//FFIList
		finInstrPopup.getField('pClassificationFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='FFIList']"));

		//reportingFFIList
		finInstrPopup.getField('pReportingFFIFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='reportingFFIList']"));
		
		//country of Domicile  CDOT FATCA
		finInstrPopup.getField('pCountryFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='cntryOfIssueList']"));
		
		//AggregationFFIList  CDOT FATCA
		_aggrFFILevelListNode = IFDS.Xml.getNode(responseXML, "//List[@listName='AggrFFIList']");

		//appLowThresList
		finInstrPopup.getField('pApplyThresholdFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='appLowThresList']"));

		//reportingUnitList
		finInstrPopup.getField('pReportingUnitFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='reportingUnitList']"));
		
		//FISponsorList
		finInstrPopup.getField('pFISponsor').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='FISponsorList']"));
    
		//respOfficerList
		var respOfficerListNode = IFDS.Xml.getNode(responseXML, "//List[@listName='respOfficerList']");
		
		//fndGrpList
		retriveFundGroupDropdownLists(responseXML);

		//cntryOfIssueList
		idenPopup.getField('pCntryFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='cntryOfIssueList']"));

		//idTypeList
		idenPopup.getField('pIdTypeFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='idTypeList']"));

		//idTypeFIeList
		idenPopup.getField('pIdTypeFIFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='idTypeFIList']"));

		//idStatusList
		idenPopup.getField('pStatusFld').loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='idStatusList']"));
		
		//CountryList
		_resources.fields['CountryDropDown'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='countryList']"));		
	}

	function storeDefaultValues(DefaultValuesXML)
	{
		//regulation
		_defaultValues['regulationList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'regulationList']");		
		//level
		_defaultValues['FFILevelList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'FFILevelList']");
		//classification
		_defaultValues['FFIList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'FFIList']");
		//reportingFFI
		_defaultValues['reportingFFIList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'reportingFFIList']");
		//appLowThres
		_defaultValues['appLowThresList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'appLowThresList']");
		//respOfficer
		_defaultValues['respOfficerList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'respOfficerList']");
		_defaultValues['fndGrpList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'fndGrpList']");
		_defaultValues['cntryOfIssueList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'cntryOfIssueList']");
		_defaultValues['idTypeList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'idTypeList']");
		_defaultValues['idTypeFIList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'idTypeFIList']");
		_defaultValues['idStatusList'] = IFDS.Xml.getNodeValue(DefaultValuesXML, "/*//ListSelection[@id = 'idStatusList']");

		_defaultValues['effectiveDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/deff'));
		_defaultValues['stopDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/stopDate'));
		//Get Aggregation function control if applyed
		_aggregationApply = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/aggrApply'));

	}

	/** Load Account Regulatory Information **/
	function populateFFIDetails(record)
	{
		if (record)
		{
			_selectedFFI = record;
			
			_resources.fields['regulationLabel'].setValue(getDisplay('regulationList', record.data['complyRule']));
			_resources.fields['classificationLabel'].setValue(getDisplay('FFIList', record.data['classification']));
			_resources.fields['levelLabel'].setValue(getDisplay('FFILevelList', record.data['level']));
			_resources.fields['codeLabel'].setValue(record.data['code']);
			_resources.fields['reportingFFILabel'].setValue(getDisplay('reportingFFIList', record.data['reportingFFI']));
			_resources.fields['descriptionLabel'].setValue(record.data['description']);
			_resources.fields['applyThresholdLabel'].setValue(getDisplay('appLowThresList', record.data['appLowThres']));
			_resources.fields['applyThresholdDateLabel'].setValue(record.data['appLowThresDate']);
			_resources.fields['filerCategoryLabel'].setValue(record.data['filerCategory']);

			var dispReporingUnitLabel = getDisplayReportingUnit(record.data['rptUnitFICode'], record.data['rptUnitFILevel']);
			_resources.fields['reportingUnitLabel'].setValue(dispReporingUnitLabel);
           
			var dispFISponsorLabel = getDisplayFISponsor(record.data['sponsorFICode'], record.data['sponsorFILevel']);
			_resources.fields['fiSponsorLabel'].setValue(dispFISponsorLabel);
            
			//CDOT aggregationFFI and country label set
			if (record.data['aggrDisplayValue'] != null && (record.data['reportingFFI'] != null && record.data['reportingFFI'] != _self.NO_REPORTINGFFI)) {
				_resources.fields['aggregationFFILabel'].setValue(record.data['aggrDisplayValue']); 
			} else {
				_resources.fields['aggregationFFILabel'].setValue(''); 
			}
			_resources.fields['countryLabel'].setValue(getDisplay('cntryOfIssueList', record.data['countryCode']));

			// Fund Group label is applicable only when level is legal entity
			if (record.data['level'] == _self.LEGALENTITY_LEVEL)
			{
				Ext.getCmp("fundGrpSection").enable();
				_resources.fields['fundGroupLabel'].setValue(getDisplay('fndGrpList', record.data['fundGroup']));
			}else{
				_resources.fields['fundGroupLabel'].setValue(_self.BLANK);
				Ext.getCmp("fundGrpSection").disable();
			}
			
			
			
			if (record.data['idenXML'] && record.data['idenXML'].length > 0) {
				_resources.grids['idenGrd'].getStore().loadData(IFDS.Xml.stringToXML(record.data['idenXML']));
			} else {
				if(_resources.grids['idenGrd'].getStore() != null) {
					_resources.grids['idenGrd'].clearGridData();
				}
			}
		
			_resources.fields['deffLabel'].setValue(record.data['deff']);
			_resources.fields['stopDateLabel'].setValue(record.data['stopDate']);
			_resources.fields['ContactNameLabel'].setValue(record.data['contactName']);
			_resources.fields['ContactPhoneNumberLabel'].setValue(record.data['phoneNum']);
			_resources.fields['ContactPhoneExtNumberLabel'].setValue(record.data['phoneExt']);
			_resources.fields['ContactEmailLabel'].setValue(record.data['email']);
			_resources.fields['Address1Label'].setValue(record.data['address1']);
			_resources.fields['Address2Label'].setValue(record.data['address2']);
			_resources.fields['Address3Label'].setValue(record.data['address3']);
			_resources.fields['CityLabel'].setValue(record.data['city']);
			_resources.fields['ProvinceLabel'].setValue(record.data['province']);
			_resources.fields['PostalCodeLabel'].setValue(record.data['postalCode']);
			_resources.fields['CountryFFILabel'].setValue(getDisplay('countryList', record.data['country']));
		}else{
			resetFFIDetails();
		}

		updateFFIButtonsState(record);
	}
	
	//dynamic generated FundGroup dropdown xml
	function retriveFundGroupDropdownLists(repXml) {			
		var fatcaEls = IFDS.Xml.getNodes(repXml, "//List[@listName='fndGrpList']/Element[regRule='" + _self.REGULATIONCODEFATCA + "']");
		_fundGroupFATCAListXml = IFDS.Xml.newDocument('List');
		
		Ext.each(fatcaEls, function(fatcaEls){
						IFDS.Xml.appendNode(_fundGroupFATCAListXml, IFDS.Xml.cloneDocument(fatcaEls));
		})
		
		var crsEls = IFDS.Xml.getNodes(repXml, "//List[@listName='fndGrpList']/Element[regRule='" + _self.REGULATIONCODECRSRP + "']");
		_fundGroupCRSListXml = IFDS.Xml.newDocument('List');
		
		Ext.each(crsEls, function(crsEls){
					IFDS.Xml.appendNode(_fundGroupCRSListXml, IFDS.Xml.cloneDocument(crsEls));
		})
	}

	/** Clear Financial Institution Regulatory Information **/
	function resetFFIDetails()
	{
		_resources.fields['regulationLabel'].reset();
		_resources.fields['classificationLabel'].reset();
		_resources.fields['levelLabel'].reset();
		_resources.fields['codeLabel'].reset();
		_resources.fields['reportingFFILabel'].reset();
		_resources.fields['reportingUnitLabel'].reset();
		_resources.fields['fiSponsorLabel'].reset();
		_resources.fields['countryLabel'].reset();
		_resources.fields['descriptionLabel'].reset();
		_resources.fields['applyThresholdLabel'].reset();
		_resources.fields['applyThresholdDateLabel'].reset();
		_resources.fields['deffLabel'].reset();
		_resources.fields['stopDateLabel'].reset();
		_resources.fields['fundGroupLabel'].setValue(_self.BLANK);
		_resources.fields['aggregationFFILabel'].reset();
		_resources.fields['ContactNameLabel'].reset();
		_resources.fields['ContactPhoneNumberLabel'].reset();
		_resources.fields['ContactPhoneExtNumberLabel'].reset();
		_resources.fields['ContactEmailLabel'].reset();
		_resources.fields['Address1Label'].reset();
		_resources.fields['Address2Label'].reset();
		_resources.fields['Address3Label'].reset();
		_resources.fields['CityLabel'].reset();
		_resources.fields['ProvinceLabel'].reset();
		_resources.fields['PostalCodeLabel'].reset();
		_resources.fields['CountryFFILabel'].reset();
		_resources.fields['filerCategoryLabel'].reset();
		
		Ext.getCmp("fundGrpSection").disable();

		_resources.grids['idenGrd'].clearGridData();
	}

	function setFFIRecord(index)
	{
		_resources.grids['finInstGrd'].setSelectedRecord(index);
		_self.selectFFI();
	}


	function getUpdatedRecordCount()
	{
		var store = _resources.grids['finInstGrd'].getStore();
		var idenStore = _resources.grids['idenGrd'].getStore();
		var result =
			store.query('runMode', _self.ADD).length +
			store.query('runMode', _self.MOD).length +
			store.query('runMode', _self.DEL).length +
			idenStore.query('runMode', _self.ADD).length +
			idenStore.query('runMode', _self.MOD).length +
			idenStore.query('runMode', _self.DEL).length ;
		return result;
	}

	/** Enable/disable operation buttons based-on a selected record **/
	function updateFFIButtonsState(record)
	{
		if (record == null || record == undefined)
			record = _resources.grids['finInstGrd'].getSelectedRecord();

		var pAllowDel = true;
		var pAllowMod = true;
		var pRunMode = _self.BLANK;
		if (record != null && record != undefined)
		{
			pRunMode  = record.data['runMode'];
			if (pRunMode != _self.ADD)
			{
				pAllowDel = (record.data['allowDel'] == 'yes') ? true : false ;
				pAllowMod = (record.data['allowMod'] == 'yes') ? true : false ;
			}
		}
		else
			record = null;

		//addBtn of finInstGrd and idenGrd
		if (_permissionsMap[_self.ADD]) {
			_resources.grids['finInstGrd'].enableButton(_CADD);
			_resources.grids['idenGrd'].enableButton(_CADD);
		} else {
			_resources.grids['finInstGrd'].disableButton(_CADD);
			_resources.grids['idenGrd'].disableButton(_CADD);
		}

		if (record)
		{
			//modBtn of finInstGrd

			if (pAllowMod && (_permissionsMap[_self.MOD] || pRunMode == _self.ADD))
				_resources.grids['finInstGrd'].enableButton(_CMOD);
			else
				_resources.grids['finInstGrd'].disableButton(_CMOD);

			//finInstGrd

			if ( pAllowDel && (_permissionsMap[_self.DEL] || pRunMode == _self.ADD))
				_resources.grids['finInstGrd'].enableButton(_CDEL);
			else
				_resources.grids['finInstGrd'].disableButton(_CDEL);

			//Admin & History Button
			if (pRunMode != _self.ADD)
			{
				_resources.grids['finInstGrd'].enableButton(_CADMIN);
				_resources.grids['finInstGrd'].enableButton(_CHISTORY);
			}
			else
			{
				_resources.grids['finInstGrd'].disableButton(_CADMIN);
				_resources.grids['finInstGrd'].disableButton(_CHISTORY);
			}
		}
		else
		{
			_resources.grids['finInstGrd'].disableButton(_CMOD);
			_resources.grids['finInstGrd'].disableButton(_CDEL);
			_resources.grids['finInstGrd'].disableButton(_CADMIN);
			_resources.grids['finInstGrd'].disableButton(_CHISTORY);
		}

		if (record)
			updateIdenButtonsState(null);
		else
		{
			resetFFIDetails();
			_resources.grids['idenGrd'].disableButton(_CADD);
			_resources.grids['idenGrd'].disableButton(_CMOD);
			_resources.grids['idenGrd'].disableButton(_CDEL);
		}
	}

	function updateIdenButtonsState(record)
	{
		if (record == null || record == undefined)
			record = _resources.grids['idenGrd'].getSelectedRecord();

		var pAllowDel = true;
		var pAllowMod = true;
		var pRunMode = _self.BLANK;
		if (record != null && record != 'undefined')
		{
			pRunMode  = record.data['runMode'];
			if (pRunMode != _self.ADD)
			{
				pAllowDel = (record.data['allowDel'] == 'yes') ? true : false ;
				pAllowMod = (record.data['allowMod'] == 'yes') ? true : false ;
			}
		}
		else
			record = null;

		//addBtn of finInstGrd and idenGrd
		if (_permissionsMap[_self.ADD]) {
			_resources.grids['idenGrd'].enableButton(_CADD);
		} else {
			_resources.grids['idenGrd'].disableButton(_CADD);
		}

		//modBtn of finInstGrd
		if (record)
		{
			( pAllowMod && (_permissionsMap[_self.MOD] || pRunMode == _self.ADD))
				? _resources.grids['idenGrd'].enableButton(_CMOD)
				: _resources.grids['idenGrd'].disableButton(_CMOD);

			//finInstGrd
			(pAllowDel && (_permissionsMap[_self.DEL] || pRunMode == _self.ADD))
				? _resources.grids['idenGrd'].enableButton(_CDEL)
				: _resources.grids['idenGrd'].disableButton(_CDEL);

		}
		else
		{
			_resources.grids['idenGrd'].disableButton(_CMOD);
			_resources.grids['idenGrd'].disableButton(_CDEL);
		}
	}

	/** Load Account Regulatory records to grid **/
	function loadFinanInstGrid(responseXML, append)
	{

		var finanInstsXML = IFDS.Xml.getNodes(responseXML, '/*//FinanInsts');

		if (finanInstsXML != null && finanInstsXML != undefined && finanInstsXML.length > 0)
		{
			_inqFFIresponse = responseXML;
			_resources.grids['finInstGrd'].getStore().loadData(finanInstsXML, append);
		}
		else {
			_resources.grids['finInstGrd'].clearGridData();
			resetFFIDetails();
		}

		if (!append)
			setFFIRecord(0);
	}
	
	function getInitService(code)
	{
		if(code == null) {
			return _dtFFIInqService;
		}
		else if (code == "Fund")
		{
			return _dtFundFinanInstInq;
		}
	}

	function searchFFI(searchAttributeList, runMode, append)
	{
		var requestXML = IFDS.Xml.newDocument('data');

		for (var name in searchAttributeList)
		{
			IFDS.Xml.addSingleNode(requestXML, name, searchAttributeList[name]); //FA
		}

		IFDS.Xml.addSingleNode(requestXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(requestXML, 'startRecNum', (append && _nextStartRecNum)?_nextStartRecNum:'1');
		IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _requestRecNum);
		
		_service = getInitService(DesktopWeb._SCREEN_PARAM_MAP['From_Menu']);

		DesktopWeb.Ajax.doSmartviewAjax(_service
				, (runMode == 'init')?{ignoreErrorCode: '15'}:null
				, requestXML, responseHandler, _translationMap['Loading']);


		function responseHandler(success, responseXML)
		{
			storePermissions(responseXML);
			if (!append)
				_self.updatesFlag = false;

			if (success){
									
				var moreRecordsNode = IFDS.Xml.getNode(responseXML, '//' + _service + 'Response/RecordRange/moreRecordsExist');

				if (moreRecordsNode != null && IFDS.Xml.getNodeValue(moreRecordsNode).toLowerCase() == 'yes')
				{
					_nextStartRecNum = IFDS.Xml.getNodeValue(responseXML, '//' + _service + 'Response/RecordRange/rangeStartForNext');
				}
				else { _nextStartRecNum = 0; }
				_self.enableMoreButton(_nextStartRecNum);

				if (runMode == 'init')
				{
					_FFIInitXML = responseXML;
					storeDefaultValues(responseXML);
							
					if (_aggregationApply == "yes") {
						_resources.fields['aggregationFFILabel'].show();
					} else {
						_resources.fields['aggregationFFILabel'].hide();
					}
					
					populateDropdownList(responseXML);
					enableSearch();
					setDefaultSearch();
					
					if(hasPrevScreen){
						populateScreen();
					}
				}
				
				loadFinanInstGrid(responseXML, append);				

			}else{
				// Handle Rejected Response
				enableSearch();
				loadFinanInstGrid(responseXML, append);
				updateFFIButtonsState();
			}
		}
	}
	//search Address & Contact information from FATCA or CRS regulation rule
	function searchAddressContactIden(complyRule,level, code) {
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'complyRule', complyRule); 
		IFDS.Xml.addSingleNode(dataXML, 'level', level);
		IFDS.Xml.addSingleNode(dataXML, 'code', code);

		DesktopWeb.Ajax.doSmartviewAjax(_dtFFIRegulationDetl, null, dataXML, responseHandler, _translationMap['Loading']);

		function responseHandler(success, responseXML) {
			if (success) {
				setAddressContact(responseXML); 
				var idenNodes = IFDS.Xml.getNode(responseXML, '//Identifications');
				_resources.popups[_self.popupList['FFI']].idenGridSet = idenNodes;
			}
		}
	}
	
	function setAddressContact(responseXML) {
		var nodes = IFDS.Xml.getNodes(responseXML, '//ContactInfo');
		if(nodes.length > 0) {
			for (var name in _self.AddressContactFldList) {
				var itemValue = IFDS.Xml.getNodeValue(responseXML, '//ContactInfo/' + name);
				_resources.fields[_self.AddressContactFldList[name]].setValue(itemValue);
			}
		}
	}
	
	function setDefaultSearch()
	{
		_resources.fields['regulationSrch'].setValue(_defaultValues['regulationList']);
		_resources.fields['searchForSrch'].setValue(_defaultValues['FFILevelList']);

		_self.setSuggestService(_defaultValues['FFILevelList'], _self.popupList['SEARCH'] , _self.BLANK);
	}

	function getDisplay(listName, code)
	{
		var listNode = IFDS.Xml.getNode(_FFIInitXML, "//List[@listName = '" + listName + "']/Element[code='" + code + "']");
		listNode = (listNode) ? listNode:IFDS.Xml.getNode(_FFIInitXML, "//List[@id = '" + listName + "']/Element[code='" + code + "']");
		return (listNode) ? IFDS.Xml.getNodeValue(listNode, 'value') : code;
	}
	
	function getDisplayReportingUnit(FICode, FILevel)
	{
		var dispValue = FICode + ',' + FILevel;
		var reportingUnitList = IFDS.Xml.getNode(_FFIInitXML, "//List[@listName = 'reportingUnitList']/Element[FILevel='" + FILevel + "' and FICode='" + FICode + "']");
		reportingUnitList = reportingUnitList ? reportingUnitList:IFDS.Xml.getNode(_FFIInitXML, "//List[@id = 'reportingUnitList']/Element[FILevel='" + FILevel + "' and FICode='" + FICode + "']");
		
		dispValue = reportingUnitList ? IFDS.Xml.getNodeValue(reportingUnitList, 'FIDesc') : dispValue;
		
		return dispValue;
	}
  
	function getDisplayFISponsor(FICode, FILevel)
	{
		var dispValue = FICode + ' ' + FILevel;
		var fiSponsorList = IFDS.Xml.getNode(_FFIInitXML, "//List[@listName = 'FISponsorList']/Element[FISponsorLevel='" + FILevel + "' and FISponsorCode='" + FICode + "']");
		fiSponsorList = fiSponsorList ? fiSponsorList:IFDS.Xml.getNode(_FFIInitXML, "//List[@id = 'FISponsorList']/Element[FISponsorLevel='" + FILevel + "' and FISponsorCode='" + FICode + "']");
		
		dispValue = fiSponsorList ? IFDS.Xml.getNodeValue(fiSponsorList, 'FISponsorDesc') : dispValue;
	
		return dispValue;
	}  

	function sendValidationFFI(action, data)
	{
		var dataNode = IFDS.Xml.newDocument('data');
		var finanInstNode = IFDS.Xml.addSingleNode(dataNode, 'FinanInst');
		//format date again
		_self.localValidateFFI(action, data);
		var keyNode = IFDS.Xml.addSingleNode(finanInstNode, 'ffiuuid',data['ffiuuid']);
		IFDS.Xml.addAttribute(keyNode, 'RecordSource', data['ffiuuid'] );
		IFDS.Xml.addSingleNode(finanInstNode, 'code', data['code']);
		IFDS.Xml.addSingleNode(finanInstNode, 'version',data['version']);
		IFDS.Xml.addSingleNode(finanInstNode, 'runMode',data['runMode']);

		for (var name in _self.ffiFldsList)
		{
			if (name  == "deff" || name  == "stopDate" || name  == "appLowThresDate") {	
				IFDS.Xml.addSingleNode(finanInstNode, name, DesktopWeb.Util.getSMVDateValue(data[name]));
			} else {
				IFDS.Xml.addSingleNode(finanInstNode, name, data[name]);
			}
		}

		IFDS.Xml.addSingleNode(finanInstNode, 'aggrFfiCode', data['aggrFfiCode']);
		IFDS.Xml.addSingleNode(finanInstNode, 'rptUnitFILevel', data['rptUnitFILevel']);
		IFDS.Xml.addSingleNode(finanInstNode, 'rptUnitFICode',  data['rptUnitFICode']);
		IFDS.Xml.addSingleNode(finanInstNode, 'sponsorFILevel', data['sponsorFILevel']);
		IFDS.Xml.addSingleNode(finanInstNode, 'sponsorFICode',  data['sponsorFICode']);
		
		if (data['level'] == _self.BROKER_LEVEL || data['level'] == _self.INTERMEDIARY_LEVEL)
		{
			var respNodes =IFDS.Xml.addSingleNode(finanInstNode, 'BrokIntrRegDetl',data['BrokIntrRegDetl']);
			IFDS.Xml.addSingleNode(respNodes, 'brokuuid', data['brokuuid']);
			IFDS.Xml.addSingleNode(respNodes, 'version', data['brokversion']);
		}
		else		
		{
			var ContactInfoNode = IFDS.Xml.addSingleNode(finanInstNode, 'ContactInfo');
			for (var name in _self.AddressContactFldList)
			{
                var nodeValue = name == 'phoneNum' ? data[name].replace(/-/g, ''):data[name];
				IFDS.Xml.addSingleNode(ContactInfoNode, name, nodeValue);
			}						
		}
        
		//var success = true;
		DesktopWeb.Ajax.doSmartviewAjax(_dtFFIValService, null
			, dataNode, responseHandler, _translationMap['Validating']);

		function responseHandler(success, responseXML, contextErrors)
		{
			if (success)
			{
				if (action == _self.ADD)
				{
					_resources.grids['finInstGrd'].addRecord(data);
					_resources.grids['finInstGrd'].selectLastRecord();
				}
				else
				{

					_resources.grids['finInstGrd'].updateSelectedRecord(data);
				}

				_self.updatesFlag = true;
				_self.closePopup(_self.popupList['FFI']);
				_self.selectFFI();
			}
			else
			{
				displayFFIError(contextErrors, data);
			}
		}
	}



	function displayFFIError(errMsgs, data)
	{
		Ext.each(errMsgs,
			function(errMsg){
				var text = IFDS.Xml.getNodeValue(errMsg, 'text');
				var name = IFDS.Xml.getNodeValue(errMsg, 'fieldSource/xmlElementName');

				if (name && name != undefined)
				{
					if (name == 'code')
					{
						_resources.popups[_self.popupList['FFI']].getField(
							_self.ffiFldsCodeList[data['level']]).markInvalid(text);
					}
					else
					_resources.popups[_self.popupList['FFI']].getField(
						_self.ffiFldsList[name]).markInvalid(text);
				}
			});
	}


	function sendValidationIden(action, data)
	{
		var dataNode = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataNode, 'runMode', _self.VAL);

		var IdentificationNode = IFDS.Xml.addSingleNode(dataNode, 'Identification');

		var keyNode = IFDS.Xml.addSingleNode(IdentificationNode, 'uuid',data['uuid']);
		IFDS.Xml.addSingleNode(IdentificationNode, 'version',data['version']);
		IFDS.Xml.addSingleNode(IdentificationNode, 'runMode',data['runMode']);

		for (var name in _self.idenFldsList)
		{
			IFDS.Xml.addSingleNode(IdentificationNode, name ,data[name]);
		}

		IFDS.Xml.addSingleNode(IdentificationNode, 'groupType', data['groupType']);
		IFDS.Xml.addAttribute(keyNode, 'RecordSource', data['uuid'] );


		DesktopWeb.Ajax.doSmartviewAjax(_dtIdenValService
			, {ignoreWarning: true}
			, dataNode, responseHandler, _translationMap['Validating']);

		function responseHandler(success, responseXML, contextErrors, warnings)
		{
			if (success)
			{
				var msg = '';
				var popupMsg = '';
				if (warnings.length > 0)
				{
					msg = IFDS.Xml.getNodeValue(warnings[0], 'text');
					popupMsg = msg;
					for (var i = 1; i < warnings.length; i++)
					{
						popupMsg += "<br/>" + IFDS.Xml.getNodeValue(warnings[i], 'text')
						
						//This message is used to keep in grid which has to use &lt; &gt;
						//because XML cannot extract XML which has "<" or ">"
						msg += "&lt;br/&gt;" + IFDS.Xml.getNodeValue(warnings[i], 'text')

					}		
					DesktopWeb.Util.displayWarning(popupMsg, savePopupFunc, Ext.Msg.OKCANCEL);
				}
				else
					savePopupFunc('ok');
					
				
				function savePopupFunc(buttonId)
				{
					if (buttonId == 'ok')
					{										
						if (msg != '')
							data['warnMsg'] = msg;
							
						if (action == _self.ADD)
						{
							_resources.grids['idenGrd'].addRecord(data);
							_resources.grids['idenGrd'].selectLastRecord();
						}
						else
						{
							_resources.grids['idenGrd'].updateSelectedRecord(data);	
						}
						
						var errRecords = _resources.grids['idenGrd'].getStore().queryBy(function(record){
								return record.get('errMsg') != _self.BLANK
							});
							
						var errWarningRecords = _resources.grids['idenGrd'].getStore().queryBy(function(record){
								return record.get('warnMsg') != _self.BLANK
							});
							
						var rec = _resources.grids['finInstGrd'].getSelectedRecord();
						rec.data['idenXML'] = _self.generateIdentifications();
							
						if (errWarningRecords.length == 0 )
							rec.data['warnMsg'] = '';
						else if (msg != '')
							rec.data['warnMsg'] = _translationMap['WARNING_Identification'];
						
						if (errRecords.length == 0)
							rec.data['errMsg'] = _self.BLANK;
							
						if (rec.data['runMode'] == _self.BLANK || rec.data['runMode'] == 'undefined')
							rec.data['runMode'] = _self.UNCHANGE;

						rec.commit();

						_self.updatesFlag = true;
						_self.closePopup(_self.popupList['IDEN']);
						updateIdenButtonsState();
					} /*if (buttonId == 'ok')*/
				}
			}
			else
			{
				if (warnings.length > 0)
				{
					var msg = IFDS.Xml.getNodeValue(warnings[0], 'text');				
					for (var i = 1; i < warnings.length; i++)
					{
						msg += "<br/>" + IFDS.Xml.getNodeValue(warnings[i], 'text')
					}		
					DesktopWeb.Util.displayWarning(msg);
				}
				
				displayIdenError(contextErrors, data);
			}
		}

	}

	function displayIdenError(errMsgs, data)
	{
		Ext.each(errMsgs, function(errMsg){
			var text = IFDS.Xml.getNodeValue(errMsg, 'text');
			var name = IFDS.Xml.getNodeValue(errMsg, 'fieldSource/xmlElementName');
			if (name && name != undefined)
			{
				if (name != 'idType')
					_resources.popups[_self.popupList['IDEN']].getField(
					_self.idenFldsList[name]).markInvalid(text);
				else if (data['level'] == _self.FUND_LEVEL
							|| data['level'] == _self.FUNDGROUP_LEVEL)
					_resources.popups[_self.popupList['IDEN']].getField('pIdTypeFIFld').markInvalid(text);
				else
					_resources.popups[_self.popupList['IDEN']].getField('pIdTypeFld').markInvalid(text);

			}
		});
	}

	function parseStringToXML(data)
	{
		var xmlDoc = null;
		if (window.DOMParser)
		{
			parser = new DOMParser();
			xmlDoc = parser.parseFromString(data,"text/xml");
		}
		else // Internet Explorer
		{
			xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
			xmlDoc.async = false;
			xmlDoc.loadXML(data);
		}
		return xmlDoc;
	}

	function getUpdateRequest(mode)
	{
		var updateXML = IFDS.Xml.newDocument('data');

		var allFinanInstsNode = IFDS.Xml.addSingleNode(updateXML, 'FinanInsts');
		IFDS.Xml.addSingleNode(allFinanInstsNode, 'runMode', mode);
		var store = _resources.grids['finInstGrd'].getStore();

		var delRecords = store.query('runMode', _self.UNCHANGE);
		delRecords.each(addToFFIXML);
		var delRecords = store.query('runMode', _self.DEL);
		delRecords.each(addToFFIXML);
		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToFFIXML);
		var newRecords = store.query('runMode', _self.ADD);
		newRecords.each(addToFFIXML);

		return updateXML;

		function addToFFIXML(item)
		{
			var data = item.data;

			var finanInstNode = IFDS.Xml.addSingleNode(allFinanInstsNode, 'FinanInst');
			var keyNode = IFDS.Xml.addSingleNode(finanInstNode, 'ffiuuid',data['ffiuuid']);
			IFDS.Xml.addAttribute(keyNode, 'RecordSource', item.id );

			IFDS.Xml.addSingleNode(finanInstNode, 'code',data['code']);
			IFDS.Xml.addSingleNode(finanInstNode, 'version',data['version']);
			IFDS.Xml.addSingleNode(finanInstNode, 'runMode',data['runMode']);

			for (var name in _self.ffiFldsList)
			{				
				if (name  == "deff" || name  == "stopDate" || name  == "appLowThresDate")
					IFDS.Xml.addSingleNode(finanInstNode, name, DesktopWeb.Util.getSMVDateValue(data[name]));
				else
					IFDS.Xml.addSingleNode(finanInstNode, name, data[name]);
			}
			IFDS.Xml.addSingleNode(finanInstNode, 'aggrFfiCode', data['aggrFfiCode']);
			IFDS.Xml.addSingleNode(finanInstNode, 'rptUnitFILevel', data['rptUnitFILevel']);
			IFDS.Xml.addSingleNode(finanInstNode, 'rptUnitFICode',  data['rptUnitFICode']);
			IFDS.Xml.addSingleNode(finanInstNode, 'sponsorFILevel', data['sponsorFILevel']);
			IFDS.Xml.addSingleNode(finanInstNode, 'sponsorFICode',  data['sponsorFICode']);

			if (data['level'] == _self.BROKER_LEVEL || data['level'] == _self.INTERMEDIARY_LEVEL)
			{
				var respNodes =IFDS.Xml.addSingleNode(finanInstNode, 'BrokIntrRegDetl');
				var brokKey = IFDS.Xml.addSingleNode(respNodes, 'brokuuid', data['brokuuid']);
				IFDS.Xml.addAttribute(brokKey, 'RecordSource', item.id );
				IFDS.Xml.addSingleNode(respNodes, 'version', data['brokversion']);
			}
			else
			{
				var ContactInfoNode = IFDS.Xml.addSingleNode(finanInstNode, 'ContactInfo');
				for (var name in _self.AddressContactFldList)
				{
                    var nodeValue = name == 'phoneNum' ? data[name].replace(/-/g, ''):data[name];
					IFDS.Xml.addSingleNode(ContactInfoNode, name, nodeValue);
				}				
			}

			//Generate Identifications
			if (data['idenXML'])
			{
				var xmlDoc = parseStringToXML(data['idenXML']);

				var idenNodes = IFDS.Xml.addSingleNode(finanInstNode, 'Identifications');

				var listNodes = IFDS.Xml.getNodes(xmlDoc, "/*//Identification[runMode = '" + _self.DEL + "']");
				addToIdenXML(listNodes, idenNodes, item.id);

				listNodes = IFDS.Xml.getNodes(xmlDoc, "/*//Identification[runMode = '" + _self.MOD + "']");
				addToIdenXML(listNodes, idenNodes, item.id);


				listNodes = IFDS.Xml.getNodes(xmlDoc, "/*//Identification[runMode = '" + _self.ADD + "']");
				addToIdenXML(listNodes, idenNodes, item.id);

			}
		}

		function addToIdenXML(nodes, parentNode, key)
		{
		    if (nodes && nodes != undefined)
			{
				for (var i = 0; i < nodes.length; i++)
				{
					var IdentificationNode = IFDS.Xml.addSingleNode(parentNode, 'Identification');

					var data = {};
					var uuid = IFDS.Xml.getNodeValue(nodes[i], 'uuid');
					var keyNode = IFDS.Xml.addSingleNode(IdentificationNode, 'uuid', uuid);

					IFDS.Xml.addSingleNode(IdentificationNode, 'version',
						IFDS.Xml.getNodeValue(nodes[i],'version'));
					IFDS.Xml.addSingleNode(IdentificationNode, 'runMode',
						IFDS.Xml.getNodeValue(nodes[i],'runMode'));


					for (var name in _self.idenFldsList)
					{
						IFDS.Xml.addSingleNode(IdentificationNode, name ,
							IFDS.Xml.getNodeValue(nodes[i],name));
					}

					IFDS.Xml.addSingleNode(IdentificationNode, 'groupType',
						IFDS.Xml.getNodeValue(nodes[i],'groupType'));
					IFDS.Xml.addAttribute(keyNode, 'RecordSource'
						, key + _self.SEPERATOR + IFDS.Xml.getNodeValue(nodes[i],'key'));
				}
			}
		}

	}


	function storeContextErrors(errorNodes)
	{
		clearContextErrors();
		var firstErrRecIndex = -1;

		Ext.each(errorNodes, function(errorNode){
			var errMsg = IFDS.Xml.getNodeValue(errorNode, 'text');
			var allKeys = IFDS.Xml.getNodeValue(errorNode, 'recordSource/source/elementSource');
			var keyArray = {};
			var ffiIndex = _self.BLANK;
			var idenIndex = _self.BLANK;

			var hasIdenError = (allKeys.indexOf(_self.SEPERATOR) != -1); // -1 (false) = no iden
			if (hasIdenError)
			{
				keyArray = allKeys.split(_self.SEPERATOR);
				ffiIndex = keyArray[0];
				idenIndex = keyArray[1];
			}
			else
				ffiIndex = allKeys;

			var errRecord = _resources.grids['finInstGrd'].getStore().getById(ffiIndex);
			if ( errRecord ){
				if (hasIdenError)
				{
					var xmlDoc = parseStringToXML(errRecord.data['idenXML']);
					var idenList = IFDS.Xml.stringToXML(errRecord.data['idenXML']);
					errRecord.set('errMsg', _translationMap['ERROR_Identification']);

					var idenNodes = IFDS.Xml.getNodes(xmlDoc, "/*//Identification[key = '" + idenIndex + "']");

					if (idenNodes && idenNodes != undefined)
					{
						for (var i = 0; i < idenNodes.length; i++)
						{
							var node = IFDS.Xml.getNode(idenNodes[i], 'errMsg');
							IFDS.Xml.setNodeValue(node,errMsg);

						}
						errRecord.set('idenXML', IFDS.Xml.serialize(xmlDoc));
					}
					errRecord.commit();
				}
				else
				{
					errRecord.set('errMsg', errMsg);
					errRecord.commit();
				}


				var errRecordIndex = _resources.grids['finInstGrd'].getRecordIndex(errRecord);
				if ( firstErrRecIndex == -1 || firstErrRecIndex > errRecordIndex ){
					firstErrRecrIndex = errRecordIndex;
				}
			}
		});

		_resources.grids['finInstGrd'].getSelectionModel().selectRow(firstErrRecIndex);
		_resources.grids['finInstGrd'].focusRow(firstErrRecIndex);

		_self.selectFFI();

	}

	function clearContextErrors()
	{
		var errRecords = _resources.grids['finInstGrd'].getStore().queryBy(function(record){
			return record.get('errMsg') != _self.BLANK
		});

		for(i = 0; i < errRecords.length; i++)
		{
			var data = errRecords.itemAt(i);
			data.set('errMsg', _self.BLANK);

			if (data['idenXML'])
			{
				var xmlDoc = parseStringToXML(errRecord.data['idenXML']);

				var listNodes = IFDS.Xml.getNodes(xmlDoc, "/*//Identification/errMsg");
				if (listNodes)
				{
					for (var i = 0; i < listNodes.length; i++)
					{
						var node = IFDS.Xml.getNode(listNodes[i], 'errMsg');
						IFDS.Xml.setNodeValue(node,_self.BLANK);

					}
					errRecord.set('idenXML', IFDS.Xml.serialize(xmlDoc));
				}
			}
			data.commit();
		}
	}

	function replaceInvalidXMLChar(str)
	{
		if ((typeof(str) === 'string' || str instanceof String ) && str.trim().length > 0)
			str = str.replace(/&/g, "&amp;").replace(/>/g, "&gt;").replace(/</g, "&lt;").replace(/"/g, "&quot;").replace(/'/g,"&apos;");
		
		return str;
	}
	
	function getComplyRule(regulation){
		switch(regulation){
			case _self.GROUPTYPECRSRP:
				return _self.REGULATIONCODECRSRP;
			case _self.GROUPTYPEFATCA:
				return _self.REGULATIONCODEFATCA;
		}
	}
	
	function populateScreen(){
		setSearchCriteria();
		disableSearchField();
		searchFFI(_searchAttribute, _self.INQ, false);
	}
	
	function setSearchCriteria(){
		if(hasPrevScreen){
			_searchAttribute['complyRule'] = getComplyRule(DesktopWeb._SCREEN_PARAM_MAP['regulation']);
			_searchAttribute['level'] = DesktopWeb._SCREEN_PARAM_MAP['FILevel'];
			_searchAttribute['code'] = DesktopWeb._SCREEN_PARAM_MAP['FICode'];
			_searchAttribute['groupType'] = (_searchAttribute['level'] == _self.FUNDGROUP_LEVEL) ? _self.FUNDGROUPTYPE : _self.BLANK;
		
			_resources.fields['regulationSrch'].setValue(_searchAttribute['complyRule']);
			_resources.fields['searchForSrch'].setValue(_searchAttribute['level']);
			
			switch(_searchAttribute['level']){
				case "01": case "02":
					_resources.fields['searchByFund'].setValue(_searchAttribute['code']);
					break;
				case "03":
					_resources.fields['searchByLegalEntity'].setValue(_searchAttribute['code']);
					break;
			}
		}
	}
	
	function disableSearchField()
	{
		if(hasPrevScreen){
			_resources.fields['regulationSrch'].disable();
			_resources.fields['searchForSrch'].disable();
			_resources.fields['searchByFund'].disable();
			_resources.fields['searchByFundGroup'].disable();
			_resources.fields['searchByLegalEntity'].disable();
			_resources.buttons['cmdSearch'].disable();
			
			_resources.grids['finInstGrd'].disableAllButtons();
		}else{
			_resources.fields['regulationSrch'].enable();
			_resources.fields['searchForSrch'].enable();
			_resources.fields['searchByFund'].enable();
			_resources.fields['searchByFundGroup'].enable();
			_resources.fields['searchByLegalEntity'].enable();
			_resources.buttons['cmdSearch'].enable();
		}
	}
	
	function goToScreen()
	{
		var params = {};
		params['prevScreen'] = 'FinanInst';
		params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];

		if(DesktopWeb._SCREEN_PARAM_MAP['prevScreen']){
			DesktopWeb.Util.goToScreen(DesktopWeb._SCREEN_PARAM_MAP['prevScreen'],params);
		}else{
			DesktopWeb.Util.cancelScreen();
		}
			
	}

	// PUBLIC ITEMS *************************************
	return {
		 ADD				: 'a'
		,MOD				: 'm'
		,DEL				: 'd'
		,UNCHANGE			: 'u'
		,INQ				: 'inq'
		,VAL				: 'val'
		,UPD				: 'upd'
		,ERROR				: 'error'
		,BLANK				: ''
		,FUND_LEVEL			: '01'
		,FUNDGROUP_LEVEL	: '02'
		,LEGALENTITY_LEVEL	: '03'
		,BROKER_LEVEL		: '04'
		,INTERMEDIARY_LEVEL	: '05'
		,YES				: 'yes'
		,NO					: 'no'
		,SEPERATOR			: ';'
		,NO_REPORTINGFFI    : '03'
		,YES_REPORTINGFFI	: '02'
		,DEFAULT_ENV_REPORTINGFFI : '01'
		,REPORTING_UNIT_REPORTINGFFI: '04'
		,FI_SPONSOR			: '05'
		,NO_THRESHOLD	    : '02'
		,updatesFlag		: false
		,NEWFFI				: 'NEWFFI'
		,NEWIDEN			: 'NEWIDEN'
		,REGULATIONCODECRSRP: 'CRSRP'
		,REGULATIONCODEFATCA: 'FA'
		,GROUPTYPECRSRP		: 'CRS'
		,GROUPTYPEFATCA		: 'FATCA'

		,defaultValue         : _defaultValues
		,idenFldsList	      : _idenFldsList
		,ffiFldsList	      : _ffiFldsList
		,ffiFldsCodeList      : _ffiFldsCodeList
		,searchIDList         : _searchIDList
		,popupList		      : _popupList
		,AddressContactFldList: _AddressContactFldList
		,goToScreen: goToScreen

		,init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			initFFIScreen();
		}
		
		,getAggretionApply: function()
		{
			return _aggregationApply;
		}
		
		,getServiceTitle: function(code)
		{
			if(code == null) {
				return _translationMap['FIDetails'];
			}
			else if (code == "Fund")
			{
				return _translationMap['FIFundScreen'];
			}
		}
		
		,validateFields: function(code) {
			// Validate all input fields Rule/Level/Code
			var valid = _resources.popups[_self.popupList['FFI']].getField('pRegulationFld').isValid();
			valid = _resources.popups[_self.popupList['FFI']].getField('pLevelFld').isValid() && valid;
			valid = _resources.popups[_self.popupList['FFI']].getField(code).isValid() && valid;
			return valid;
		}

		,searchAddressContactIden: function(complyRule,level, code) { 
			return searchAddressContactIden(complyRule,level, code);
		}
		
		,doSearch: function(more)
		{
			if (_self.getUpdateFlags() && !more)
			{
					DesktopWeb.Util.displayDiscardPrompt(callback)
			}
			else
			{
				callback(true);
			}

			function callback(discard) {
				if (discard) {
					if (!more) {
						_searchAttribute['complyRule'] = _resources.fields['regulationSrch'].getValue();
						_searchAttribute['level'] = _resources.fields['searchForSrch'].getValue();
						_searchAttribute['code'] = _self.BLANK;
						_searchAttribute['groupType'] = (_searchAttribute['level'] == _self.FUNDGROUP_LEVEL)
									? _self.FUNDGROUPTYPE : _self.BLANK;
					}
					//allow search code only
					if(_resources.fields['searchByFund'].getValue()!= _self.BLANK) {
						_searchAttribute['code'] = _resources.fields['searchByFund'].getValue();
					} else if(_resources.fields['searchByFundGroup'].getValue()!= _self.BLANK) {
						_searchAttribute['code'] = _resources.fields['searchByFundGroup'].getValue();
					} else if(_resources.fields['searchByLegalEntity'].getValue()!= _self.BLANK) { 
						_searchAttribute['code'] = _resources.fields['searchByLegalEntity'].getValue();
					}

					searchFFI(
						_searchAttribute
						, _self.INQ
						, more);
				}
			}
		}

		, disableComponent: function(field)
		{
			field.reset();
			field.setValue(_self.BLANK);
			field.disableField();
			field.allowBlank = true;
			field.clearInvalid();
		}

		, enableComponent: function(field)
		{
			field.allowBlank = false;
			field.enableField();
			field.clearInvalid();
		}
		
		, getAggregationFFIList: function(level, code, dispDesc)
		{
			return generateAggregationDropdownLists(_aggrFFILevelListNode, level, code, dispDesc);
		}
	
		, getDynamicAggregationList: function() //CDOT Aggregation list
		{
			
			var selectedFFILevel = _resources.popups[_self.popupList['FFI']].getField('pLevelFld').getValue();
			var codeEntity = null;

			if(_service == _dtFundFinanInstInq){
				if (selectedFFILevel == _self.FUND_LEVEL) { //01 - FUND level
					codeEntity = _ffiFldsCodeList[_self.FUND_LEVEL] ;
				} else {
					codeEntity = _ffiFldsCodeList[_self.FUNDGROUP_LEVEL];
				}
			} else {
				codeEntity = _ffiFldsCodeList[_self.LEGALENTITY_LEVEL] ;
			}
			
			var selectedFFIcode = _resources.popups[_self.popupList['FFI']].getField(codeEntity).getValue();
			var selectedDesc = _resources.popups[_self.popupList['FFI']].getField(codeEntity).getRawValue();
			
			return _self.getAggregationFFIList(selectedFFILevel, selectedFFIcode, selectedDesc);
		}

		,setReportingFFI: function(code)	//CDOT FATCA
		{
			_resources.popups[_self.popupList['FFI']].getField('pRegulationFld').show();
			var fromMenu = DesktopWeb._SCREEN_PARAM_MAP['From_Menu'];
			fromMenu = (fromMenu != null ? fromMenu.toLowerCase() : "");
            
			if(_service == _dtFundFinanInstInq){
				_resources.popups[_self.popupList['FFI']].getField('pFISponsor').show(); 
			}else{
				_resources.popups[_self.popupList['FFI']].getField('pFISponsor').hide(); 
			}
			
			if (code.toLowerCase() == _self.NO_REPORTINGFFI || code.toLowerCase() == _self.REPORTING_UNIT_REPORTINGFFI)
			{
				_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdDateFld'));
				_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld'));
				_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld'));
				
				if (code.toLowerCase() == _self.NO_REPORTINGFFI)
				{
                    _resources.popups[_self.popupList['FFI']].getField('pDescriptionFld').setValue(_self.BLANK);
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pCountryFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld'));
				}
				else
				{
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pCountryFld'));
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld'));
				}
				
				/*
				 * P0235711 FATCA  CRA Guidance 
				 * Apply Lower Threshold field for Broker and Intermediary level 
				 * must be always updateable.
				 */
				if ( fromMenu == 'broker' || fromMenu == 'intermediary' )
				{
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld'));
					/*DFT0045015 - Apply Lower Threshold is able to be blank when Reporting FFI is No*/
					_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld').allowBlank = true;
				}
				else
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld'));
				
				_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').hide(); 
			} 
			else 
			{
				_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld'));
				_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld'));
                
				_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdDateFld').enableField();
				_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pCountryFld'));
				if (_aggregationApply == "yes") {
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').show());
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').loadData(_self.getDynamicAggregationList());
				} else {
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld'));
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').hide(); 
				}
			}
			
			if (code.toLowerCase() == _self.YES_REPORTINGFFI || code.toLowerCase() == _self.DEFAULT_ENV_REPORTINGFFI || code.toLowerCase() == _self.FI_SPONSOR)
			{
				_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pReportingUnitFld').show());
				_resources.popups[_self.popupList['FFI']].getField('pReportingUnitFld').allowBlank = true;
				
				if (code.toLowerCase() == _self.DEFAULT_ENV_REPORTINGFFI) {
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld'));		
				} else {
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld'));
					_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld').allowBlank = true;
				}
				
				if(_service == _dtFundFinanInstInq){
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pFISponsor').show());
					_resources.popups[_self.popupList['FFI']].getField('pFISponsor').allowBlank = true;
				}
			}
			else
			{
				_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pReportingUnitFld'));
				_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pFISponsor'));
				_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld'));
			}
		}
		,setCRSReportingFFI: function(code)	{//CRS Regulation rule
			switch(code) { //NO REPORTING/Sponser, disable all fields
				case  _self.FI_SPONSOR: case _self.NO_REPORTINGFFI: {
					_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld').setValue(_self.BLANK);
					
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pCountryFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdDateFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pReportingUnitFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pFISponsor'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld'));
					//not mandatory
					_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld').allowBlank = true;
					_resources.popups[_self.popupList['FFI']].getField('pCountryFld').allowBlank = true;
					_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld').allowBlank = true;
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').allowBlank = true;
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').hide(); 
					break;
				}
				case _self.DEFAULT_ENV_REPORTINGFFI: case _self.YES_REPORTINGFFI: {
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld'));
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pCountryFld'));
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pReportingUnitFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld'));
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').allowBlank = true;
					_resources.popups[_self.popupList['FFI']].getField('pReportingUnitFld').allowBlank = true;
					//Disable
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdDateFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pFISponsor'));
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').hide(); 
					break;
				}
				case _self.REPORTING_UNIT_REPORTINGFFI: {
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pDescriptionFld'));
					_self.enableComponent(_resources.popups[_self.popupList['FFI']].getField('pCountryFld'));
					_resources.popups[_self.popupList['FFI']].getField('pCountryFld').allowBlank = true;
					//Disable
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pApplyThresholdDateFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pReportingUnitFld'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pFISponsor'));
					_self.disableComponent(_resources.popups[_self.popupList['FFI']].getField('pfilerCategoryFld'));
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').allowBlank = true;
					_resources.popups[_self.popupList['FFI']].getField('pAggregationLevelFld').hide();
					break;
				}
			}
		}

		, setSuggestValue: function(smartview, searchValue
				, searchFieldName, searchFieldValue
				, popupName
				, resultField, resultValueCode
				, callbackFn)
		{
			var xml = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(xml, 'searchValue', searchValue);

			if (searchFieldName != null && searchFieldName.trim().length > 0)
			{
				IFDS.Xml.addSingleNode(xml, searchFieldName, searchFieldValue);
			}

			IFDS.Xml.addSingleNode(xml, 'startRecordNum', '1');
			IFDS.Xml.addSingleNode(xml, 'maxRecords', 14);

			DesktopWeb.Ajax.doSmartviewAjax(smartview, {ignoreErrorCode: '199'}, xml, responseHandler, "");

			function responseHandler(success, responseXML)
			{
				if (success)
				{
					var popup = _resources.popups[popupName];
					var possibleNode = IFDS.Xml.getNode(responseXML, '/*//PossibleMatches');

					if (popup.getField(resultField) instanceof DesktopWeb.Controls.SuggestField)
					{
						popup.getField(resultField).getStore().loadData(possibleNode);

						var value = IFDS.Xml.getNodeValue(responseXML, '/*//' + resultValueCode);
						popup.getField(resultField).setValue(value);

					}
					else
					{
						var value = IFDS.Xml.getNodeValue(responseXML, '/*//' + resultValueCode);
						var dispValue = _self.BLANK;
						popup.getField(resultField).setValue(value);

						if (smartview == _searchFund) {
							dispValue =  IFDS.Xml.getNodeValue(responseXML, '/*//fndDisp')
							popup.idenGroupType  =  IFDS.Xml.getNodeValue(responseXML, '/*//groupType')
						} else
							dispValue = IFDS.Xml.getNodeValue(responseXML, '/*//displayValue');

						popup.getField(resultField).setRawValue(dispValue);


					}

					if (callbackFn && callbackFn != undefined)
					{
						callbackFn();
					}
				}
			}
		}

		,setSuggestService: function(code, popupName, searchId, mode)
		{
			if (popupName == _self.popupList['FFI']) //PopupWindow
			{
				var popup = _resources.popups[_self.popupList['FFI']];

				for (var name in _self.ffiFldsCodeList)
				{
					popup.getField(_self.ffiFldsCodeList[name]).hide();
					popup.getField(_self.ffiFldsCodeList[name]).allowBlank = true;
					popup.getField(_self.ffiFldsCodeList[name]).reset();
				}
				
				if((code != _self.BROKER_LEVEL || code != _self.INTERMEDIARY_LEVEL)
					&& popup.getField('pRegulationFld').getValue()== _self.REGULATIONCODECRSRP) {
					_self.setCRSReportingFFI(popup.getField('pReportingFFIFld').getValue()); //clear invalid
				} else {
					_self.setReportingFFI(popup.getField('pReportingFFIFld').getValue()); //clear invalid
				}

				popup.getField(_self.ffiFldsCodeList[code]).show();
				if (mode == _self.MOD)
				{
					popup.getField(_self.ffiFldsCodeList[code]).disableField();
				}

				popup.getField(_self.ffiFldsCodeList[code]).allowBlank = false

				switch (code) {
					case _self.FUND_LEVEL: {
						popup.getField('pFundGroupForLegalEntityFld').hide();
						popup.getField('pFundGroupForLegalEntityFld').reset();
						if (searchId && searchId != _self.BLANK)
							_self.setSuggestValue(_searchFund, searchId, 'inclInactive','yes'
							, _self.popupList['FFI']
							,_self.ffiFldsCodeList[code], 'fundCode',  null );
						break;
					}
					case _self.FUNDGROUP_LEVEL: {
						popup.getField('pFundGroupForLegalEntityFld').hide();
						popup.getField('pFundGroupForLegalEntityFld').reset();
						if (searchId && searchId != _self.BLANK && mode == _self.MOD)
							popup.getField(_self.ffiFldsCodeList[code]).setValue(searchId);
						break;
					}
					case _self.LEGALENTITY_LEVEL:{
					/*pLegalEntityFld*/
						if (mode != _self.MOD)
							popup.getField('pFundGroupForLegalEntityFld').setValue(_defaultValues['fndGrpList']);

						popup.getField('pFundGroupForLegalEntityFld').show();

						popup.getField('pFISponsor').hide();
						popup.getField('pFISponsor').reset();
                        
						if (searchId && searchId != _self.BLANK)
							_self.setSuggestValue(_searchLegal, searchId, 'entityWhereused','15'
							, _self.popupList['FFI']
							, _self.ffiFldsCodeList[code], 'whereUseKey', null );
						break;
					}
					case _self.BROKER_LEVEL:{
						popup.getField('pFundGroupForLegalEntityFld').hide();
						popup.getField('pFundGroupForLegalEntityFld').reset();
						Ext.getCmp('popup_AddressTab').disable();
						Ext.getCmp('popup_ContactTab').disable();										
						if (searchId && searchId != _self.BLANK)
							_self.setSuggestValue(_searchBroker, searchId, _self.BLANK,_self.BLANK,
								_self.popupList['FFI']
								, _self.ffiFldsCodeList[code], 'agencyCode',  null );
						break;
					}
					case _self.INTERMEDIARY_LEVEL: {
						popup.getField('pFundGroupForLegalEntityFld').hide();
						popup.getField('pFundGroupForLegalEntityFld').reset();
						Ext.getCmp('popup_AddressTab').disable();
						Ext.getCmp('popup_ContactTab').disable();

						if (searchId && searchId != _self.BLANK)
							_self.setSuggestValue(_searchInterm, searchId, _self.BLANK, _self.BLANK
								, _self.popupList['FFI']
								, _self.ffiFldsCodeList[code], 'intrCode', null );
						break;
					}
					default : popup.getField('pFundFld').show();
				}
				if (popup.rendered)
				{
					popup.syncShadow();
				}
			}
			else if (popupName == _self.popupList['SEARCH']) {
				for (var name in _self.searchIDList)
				{
					_resources.fields[_self.searchIDList[name]].hide();
					_resources.fields[_self.searchIDList[name]].reset();
				}
				
				if (_resources.fields[_self.searchIDList[code]] && _resources.fields[_self.searchIDList[code]] != undefined)
					_resources.fields[_self.searchIDList[code]].show();
				else {
					_resources.fields['searchByFund'].show();
				}
			}

		}

		,getFundGroupType: function() {
			if (_resources.fields['regulationSrch'].getValue() == _self.REGULATIONCODEFATCA) {
				return _FUNDGROUPTYPEFA;
			} else if (_resources.fields['regulationSrch'].getValue() == _self.REGULATIONCODECRSRP) {
				return _FUNDGROUPTYPECRS;
			} else {
				return _FUNDGROUPTYPES;
			}
		}		
		
		,getSearchID: function(code)
		{
			var searchID = _self.BLANK;

			if (_resources.fields[_self.searchIDList[code]] && _resources.fields[_self.searchIDList[code]] != undefined)
				searchID = _resources.fields[_self.searchIDList[code]].getValue();

			return searchID;
		}

		,selectFFI: function(record)
		{
			if (record == null || record == undefined) {
				record = _resources.grids['finInstGrd'].getSelectedRecord();
				if(record != null) {
					//pre-set Identification for the new Fund/Sponser record
					if(_resources.popups[_self.popupList['FFI']].idenGridSet!= null && record.data['runMode'] == _self.ADD) {
						_resources.grids['idenGrd'].getStore().loadData(_resources.popups[_self.popupList['FFI']].idenGridSet);
						record.data['idenXML'] = _self.generateIdentifications();
					}
				}
			}
			populateFFIDetails(record);
		}
		
		,refreshIdenGrid: function()
		{
			record = _resources.grids['finInstGrd'].getSelectedRecord();
			if (record)
			{ 
				if (record.data['idenXML'] && record.data['idenXML'].length > 0) {
					_resources.grids['idenGrd'].getStore().loadData(IFDS.Xml.stringToXML(record.data['idenXML']));
				} else {
					_resources.grids['idenGrd'].clearGridData();
				}
			}
		}

		,getDisplay: function(listName, code)
		{
			return getDisplay(listName, code);
		}
		,updateFFIButtonsState: function(record)
		{
			return updateFFIButtonsState(record);
		}
		
		,getDisplayReportingUnit: function(FICode, FILevel)
		{
			return getDisplayReportingUnit(FICode, FILevel)
		}
    
		,getDisplayFISponsor: function(FICode, FILevel)
		{
			return getDisplayFISponsor(FICode, FILevel)
		}
		
		,setFundGroupList: function(code) {
			var popup = _resources.popups[_self.popupList['FFI']];
			
			popup.getField('pFundGroupFld').clearField();
			popup.getField('pFundGroupForLegalEntityFld').clearField();//POP UP id: 'popup_fndGrp'
			
			if(code == this.REGULATIONCODEFATCA) { //FATCA
			   popup.getField('pFundGroupFld').getStore().loadData(_fundGroupFATCAListXml);
			   popup.getField('pFundGroupForLegalEntityFld').getStore().loadData(_fundGroupFATCAListXml);
			} else {//CRSRP
				popup.getField('pFundGroupFld').getStore().loadData(_fundGroupCRSListXml);
				popup.getField('pFundGroupForLegalEntityFld').getStore().loadData(_fundGroupCRSListXml);
			}
		}

		,openActionPopup: function(action, popupName) {
			if (action == this.ADD) {
				_resources.popups[popupName].getField('pDeffFld').enable();
				_resources.popups[popupName].getField('pDeffFld').show();
			}
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();
		}

		,openIdenActionPopup: function(action, popupName)
		{
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();

			var record = _resources.grids['finInstGrd'].getSelectedRecord();
			_resources.popups[popupName].getField('pCodeFld').setRawValue(record.data['displayValue']);

		}

		,localValidateFFI: function(action, data)
		{		
			var success = true;

			if (data['deff'] > data['stopDate'])
			{
				success = false;
				_resources.popups['finInstPopup'].getField(
					_self.ffiFldsList['stopDate']).markInvalid(_translationMap['Error_StopDateNotPriorEffDate']);
			}
			else
			{
				var dispFormat = DesktopWeb.Util.getDateDisplayFormat();
				data['deff'] = DesktopWeb.Util.dateToString(data['deff'], dispFormat);
				data['stopDate'] = DesktopWeb.Util.dateToString(data['stopDate'], dispFormat);
				data['appLowThresDate'] = DesktopWeb.Util.dateToString(data['appLowThresDate'], dispFormat);
			}
			return success;
		}

		,clickHandle_okBtnOnFinInstPopup: function(action, data)
		{
			var isUpd = false; 
			if (action == _self.ADD)
			{
				data['runMode'] = this.ADD;
				data['ffiuuid'] = this.NEWFFI + _ffiCounter++;
				data['version'] = 0;
				isUpd = true; 
			}
			else
			{
				var tempRecord = _resources.grids['finInstGrd'].getSelectedRecord();
				data['ffiuuid'] = tempRecord.data['ffiuuid'];
				data['version'] = tempRecord.data['version'];
				if (tempRecord.data['runMode'] == _self.ADD)
					data['runMode'] = this.ADD;

				for (var i in tempRecord.data)
				{
					if(i != 'Responsibility' && i != 'runMode' && i != 'aggrDisplayValue'){
					
						if (tempRecord.data[i] !== data[i] && data[i]  != undefined)
						{
							isUpd = true;
						}
					}
				}
				
			}

			if(isUpd)
				sendValidationFFI(action, data);
			else
				_resources.popups['finInstPopup'].hide();
		}

		
		,localValidateIDEN: function(action, data)
		{
			var success = true;			
			if (data['deff'] > data['stopDate'])
			{
				success = false;
				_resources.popups[_self.popupList['IDEN']].getField(_self.idenFldsList['stopDate']).markInvalid(
					_translationMap['Error_StopDateNotPriorEffDate']);				
			}
			else
			{
				data['deff'] =	DesktopWeb.Util.getDateString(data['deff']
								, DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
				data['stopDate'] =	DesktopWeb.Util.getDateString(data['stopDate']
								, DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
			}
			
			return success;
		}
		
		,clickHandle_okBtnOnIdenPopup:	function(action, data)
		{		
			var isUpd = false; 
			if (action == _self.ADD)
			{
				data['runMode'] = _self.ADD;
				data['uuid'] = _self.NEWIDEN + _idenCounter++;
				data['version'] = 0;
				data['key'] = _idenKey++;
				var isUpd = true; 
			}
			else
			{
				var tempRecord = _resources.grids['idenGrd'].getSelectedRecord();
				data['key']     = tempRecord.data['key'];
				data['uuid']	= tempRecord.data['uuid'];
				data['version'] = tempRecord.data['version'];

				if (tempRecord.data['runMode'] == _self.ADD)
					data['runMode'] = _self.ADD;
				else if (data['key'] == _self.BLANK)
					data['key'] =  _idenKey++;

				for (var i in tempRecord.data)
				{
					if(i != 'runMode' && i != 'key' && i != 'groupType')
					{
						if (tempRecord.data[i] !== data[i] && data[i]  != undefined)
						{
							isUpd = true;
						}
					}
				}
			}

			if(isUpd)
				sendValidationIden(action, data);
			else
				_resources.popups['idenPopup'].hide();
			
		}

		,getIdentifiersByFFI: function(ffiuuid, record)
		{
			var node = IFDS.Xml.getNode(_inqFFIresponse, "/*//FinanInst[ffiuuid='" + ffiuuid + "']/Identifications");
			return (node != null) ? IFDS.Xml.serialize(node) : _self.BLANK;
		}

		,generateResponsibilities: function(data)
		{
			var xml = "<Responsibilities>";
			xml += "<Responsibility><id>" + data['brokuuid'] + "</id>"
				+ "<desc>Document Tracking</desc>"
				+  "<brokversion>" + data['brokversion'] + "</brokversion>"
				+  "<client>" + data['clntHeldDocTrack'] + "</client>"
				+  "<nominee>"+ data['nomineeDocTrack']	 + "</nominee>"
				+  "</Responsibility>" ;

			xml += "<Responsibility><id>" + data['brokuuid'] + "</id>"
				+ "<desc>Reporting</desc>"
				+  "<brokversion>" + data['brokversion'] + "</brokversion>"
				+  "<client>" + data['clntHeldWholdable'] + "</client>"
				+  "<nominee>"+ data['nomineeWholdable']  + "</nominee>"
				+  "</Responsibility>" ;

			xml += "<Responsibility><id>" + data['brokuuid'] + "</id>"
				+ "<desc>Withholding</desc>"
				+  "<brokversion>" + data['brokversion'] + "</brokversion>"
				+  "<client>" + data['clntHeldRptable'] + "</client>"
				+  "<nominee>"+ data['nomineeRptable']	+ "</nominee>"
				+  "</Responsibility>" ;

			xml += "</Responsibilities>";

			return xml;

		}

		,generateIdentifications: function()
		{
			var xml = _self.BLANK;
			var idenRecords = null;
			if (_resources.grids['idenGrd'].getStore().snapshot)
				idenRecords = _resources.grids['idenGrd'].getStore().snapshot.items;
			else
				idenRecords = _resources.grids['idenGrd'].getStore().data.items;

			for(var i = 0; i <= idenRecords.length-1; i++){
				xml += "<Identification>";
				for (var name in idenRecords[i].data)
				{
					xml += "<" + name + ">"
					    +  replaceInvalidXMLChar(idenRecords[i].data[name])
					    + "</" + name + ">";
				}
				xml += "</Identification>";
			}

			if (xml.length > 0)
				xml = "<Identifications>" + xml +"</Identifications>";
			return xml;
		}

		,closePopup: function(name)
		{
			_resources.popups[name].hide();
		}


		,clickHandleMoreBtn: function()
		{
			_self.doSearch(true);
		}

		,enableMoreButton: function (moreRec)
		{
			 (moreRec)
			 ?  _resources.grids['finInstGrd'].enableButton(_CMORE)
			 : _self.disableMoreButton();
		}

		,disableMoreButton: function ()
		{
			_nextStartRecNum = 1;
			_resources.grids['finInstGrd'].disableButton(_CMORE);
		}

		,deleteFFISelectedRecord: function()
		{
			var tempRecord = _resources.grids['finInstGrd'].getSelectedRecord();
			var index  = _resources.grids['finInstGrd'].store.indexOf(tempRecord)

			var hasChanged	= false;

			if (tempRecord.data['runMode'] == _self.ADD)
			{
				_resources.grids['finInstGrd'].removeSelectedRecord();
			}
			else
			{
				tempRecord.data['runMode'] = _self.DEL;
				tempRecord.commit();

				_resources.grids['finInstGrd'].store.filterBy(function(record) {
					return record.data.runMode != _self.DEL;
				});
			}

			_resources.grids['finInstGrd'].setSelectedRecord(index - 1 < 0 ? 0 : index - 1);
			
			updateFFIButtonsState();
			_self.updatesFlag = true;
		}


		,deleteIdenSelectedRecord: function()
		{
			var tempRecord = _resources.grids['idenGrd'].getSelectedRecord();
			var index  = _resources.grids['idenGrd'].store.indexOf(tempRecord)

			var hasChanged	= false;

			if (tempRecord.data['runMode'] == _self.ADD)
			{
				_resources.grids['idenGrd'].removeSelectedRecord();
			}
			else
			{
				tempRecord.data['runMode'] = _self.DEL;
				tempRecord.commit();

				_resources.grids['idenGrd'].store.filterBy(function(record) {
					return record.data.runMode != _self.DEL;
				});
			}

			var rec = _resources.grids['finInstGrd'].getSelectedRecord();
			rec.data['idenXML'] = _self.generateIdentifications();
			if (rec.data['runMode'] == _self.BLANK || rec.data['runMode'] == undefined)
				rec.data['runMode'] = _self.UNCHANGE;

			rec.commit();

			_resources.grids['idenGrd'].setSelectedRecord(index - 1 <= 0 ? 0 : index - 1);
			updateIdenButtonsState();

			_self.updatesFlag = true;
		}

		,doValidateCommitScreen : function()
		{
			if (_self.doUpdate(_self.VAL) == DesktopWeb._SUCCESS)
				DesktopWeb.Util.commitScreen();
		}
		
		,getUpdateFlags : function()
		{
			_self.updatesFlag = (getUpdatedRecordCount() > 0);
			
			return _self.updatesFlag;
		}

		,doUpdate: function (mode)
		{
			var updateStatus = null;
			mode = (mode && mode != undefined)? mode : _self.UPD;

			DesktopWeb.Ajax.doSmartviewUpdate(_dtFFIUpdService, null, getUpdateRequest(mode), responseHandler, _translationMap['ProcMsg_Saving']);

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
				}
			}

			return updateStatus;
		}

		/*History popup screen*/
		,openHistoryPopup: function()
		{
			var viewParam = {};
			var historyName = null;
			var selectedRecord = _resources.grids['finInstGrd'].getSelectedRecord();

			if (selectedRecord && selectedRecord != undefined)
			{
				viewParam['searchValue1'] = selectedRecord.data['ffiuuid'];
				historyName = _self.getServiceTitle(DesktopWeb._SCREEN_PARAM_MAP['From_Menu']) + ' - ' +_translationMap['History'];

				viewParam['auditType'] = 'FinInstReg';
				_resources.popups['history'].init(historyName, _historyService, viewParam, true);
				_resources.popups['history'].show();
			}

		}

		/*Admin popup screen*/
		,openAdminPopup: function()
		{
			var title = null;
			var xml = null;

			title = _self.getServiceTitle(DesktopWeb._SCREEN_PARAM_MAP['From_Menu']) + ' - ' +_translationMap['Admin']
			xml = _resources.grids['finInstGrd'].getSelectedRecord();

			if (xml && xml != undefined)
			{
				var adminData = {};
				adminData['userName'] = xml.data['userName'];
				adminData['procDate'] = xml.data['processDate'];
				adminData['modUser'] = xml.data['modUser'];
				adminData['modDate'] = xml.data['modDate'];

				_resources.popups['admin'].init(title, adminData);
				_resources.popups['admin'].show();
			}
		}
        
        ,setCountryRequired: function() {
            var isRequired = false;
            var dependFields = ['Address1TextField',
                                'Address2TextField',
                                'Address3TextField',
                                'CityTextField',
                                'PostalCodeTextField',
                                'ProvinceTextField'];
                                
            for (var i = 0; i < dependFields.length; i++) {
                if (_resources.fields[dependFields[i]].getValue().length > 0) {
                    isRequired = true;
                    break;
                }
            }
            
            _resources.fields['CountryDropDown'].allowBlank = !isRequired;
            
            if (!isRequired) {
                _resources.fields['CountryDropDown'].clearInvalid();
            }
        }
        ,generateFilerDropdown: function(_popup) {
        	var filerCategoryListNode = IFDS.Xml.getNode(_FFIInitXML, "//List[@listName='filerCategoryList']");
    		if (filerCategoryListNode) {
    			_popup.getField('pfilerCategoryFld').loadData(filerCategoryListNode);
    		}
        } 
        ,clearFilerCategoryList: function() {
        	var popup = _resources.popups[_self.popupList['FFI']];
        	popup.getField('pfilerCategoryFld').clearValue();
        	popup.getField('pfilerCategoryFld').getStore().removeAll();
        }
	}
}