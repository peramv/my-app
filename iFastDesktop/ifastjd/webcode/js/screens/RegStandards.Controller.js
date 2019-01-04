/*********************************************************************************************
 * @file	RegStd.Controller.js
 * @author	Manoj Kumar
 * @desc	Controller JS file for Regulatory Standards screen
 *********************************************************************************************/
/*
 *  History : 
 *  09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	17 Oct 2013 N. Suanlamyai P0193400 DFT0022411 T54302
 *					- Add band permission to the screen.
 *
 *  21 Oct 2013 S. Supareuk P0216380 FN01 DFT0021918 T54345
 *                  - Added logic to removed duplicated record via add mode and 
 *                    back-end sent an error node in returned response xml
 *
 *  24 Jan 2014 G. Thawornwachirakun P0223930 FN01 
 *          - Support French Translation
 *
 *  8 Feb 2014 Winnie Cheng P0223057 T77753
 *                  - Added new fields and logic for UK FATCA
 *                    back-end sent a lists and save new fields values
 *                    back-end sent an error node in returned response xml
 *
 *  20 Feb 2014 Winnie Cheng P0223057 T77795
 *                  - Remove Country disable line of code
 *                    change set Report To Country with code, not description
 *    
 *  28 Feb 2014 Winnie Cheng P0223057 T77807 DFT0029706
 *                  - Acct and Tax type modify is blank due to code merge missing
 *                    
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  6 Dec 2014 Winnie Cheng P0234088 T78497 
 *             - Replace special char.(horizontal Tab, double inverted commas) of 
 *               description field as a space.
 *
 *  11 Dec 2014 K. Thanyasrisang P0181067 CHG0039135 T56148 
 *             - The "On behalf of 3rd party" field is set to value "NO" for all 
 *               available regulatory standards even if the value is "YES" in 
 *               the Database.
 *
 *  5 Nov 2014 Winnie Cheng P0246836 CHG0042679 T81667 DFT0055800
 *             - Desktop Screen Regulatory Standard field "Tax Type(s) Edit button has to be disabled.
 *               
 *  18 Nov 2014 Winnie Cheng P0247899  T81687 
 *             - Desktop Screen Regulatory Standard modification to allow the user filter records
 *             - Be able to retrive more records by providing "More" button.          
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *			   - Fixed screens don't response when user's profile has too many slots attached. 
 *
 *  3 Feb 2017  Winnie Cheng P0259672  T84745
 *			  - Enhance the screen for CRS Report regulation rule and Jurisdisction records
 *
 *  23 March 2017  Winnie Cheng P0259672  T85110
 *			  - fixing an existing issue that DocList, TaxType/AccountType does not display data after more 100 records
 *
 *   2 May 2017  Winnie Cheng P0262712  T85418
 *			  - Need to assign fatcacode as "CRS" for RegulationRule "CRSRP" - CRS Reporting
 *
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initXml = null;
	var _reloadXml = null;
	var _initView = 'dtRegStandardsInit';
	var _reloadView = 'dtRegStandardsReload';
	var _processView = 'dtRegStandardsProc';
	
	//CRS Reportable Jurisdisction APIs
	var _valCRSReportJuris = 'dtRegStdRepJurisVal';
	var _crsJurisList = 'dtRegStdRepJurisInq';
	var _permissionsMap = {};
	
	var _fatcaUSCtyListXml = null;
	var _fatcaCDOTCtyListXml = null;
	
	var _FATCACODECDOT = 'CDOT';
	var _FATCACODEUS = 'USFATCA';
	var _FATCACODECRS = 'CRS';
	var _SINGLE = _translationMap['SINGLE'];
	var _MULTIPLE = _translationMap['MULTIPLE'];
	
	var _requestRecNum = 100;	//The number of record display on table
	var _nextStartRecNum = 1;	
	var _CMORE = 'moreBtn';
	var _nextUUID = 1;
	
	var _effDateDefault = null;
	var _stopDateDefault = null;

	// PRIVATE METHODS ****************************************
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/add').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/mod').toLowerCase() == 'yes';
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/del').toLowerCase() == 'yes';
	}

	function loadDropDowns(responseXML)
	{		
		_resources.fields['regulationRule'].getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='regRules']"));
		
		var record = _resources.fields['regulationRule'].getStore().getAt(0);	
		record.data.value =  _translationMap['All'];
		_resources.fields['regulationRule'].setValue(_resources.fields['regulationRule'].getStore().getAt(0).get('code'));	
		_resources.fields['countryFilter'].getStore().loadData(IFDS.Xml.getNodes(responseXML,"//List[@listName='regCountries']"));
		_resources.fields['countryFilter'].setValue(_resources.fields['countryFilter'].getStore().getAt(0).get('code'));
		_resources.fields['status'].getStore().loadData(IFDS.Xml.getNodes(responseXML,"//List[@listName='RegStatus']"));
		_resources.fields['status'].setValue(_resources.fields['status'].getStore().getAt(0).get('code'));
		_self.populateGrid(_self.INIT,false);

		_resources.popups['regulatoryStandardsPopup'].getField('regulationRule').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='regRules']"));
		_resources.popups['regulatoryStandardsPopup'].getField('country').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='regCountries']"));
		_resources.popups['regulatoryStandardsPopup'].getField('investorType').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='investorTypes']"));
		_resources.popups['regulatoryStandardsPopup'].getField('province').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='regProvinces']"));
		_resources.popups['regulatoryStandardsPopup'].getField('fundCategory').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='FundCatList']"));
		_resources.popups['regulatoryStandardsPopup'].getField('regModel').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='RegModelList']"));
		
		//CDOT FATCA
		_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='fatcaRegulation']"));
		retriveCountryDropdownLists (responseXML);
	
		var fatcaMstr = null;
		var stopDateDefault = IFDS.Xml.getNodeValue(responseXML, '/*//stopDateDefault');
			stopDateDefault = DesktopWeb.Util.getDateDisplayValue(stopDateDefault);
		_resources.popups['regulatoryStandardsPopup'].getField('stopDate').setValue(stopDateDefault);
		_stopDateDefault = stopDateDefault;

		var effDateDefault = IFDS.Xml.getNodeValue(responseXML, '/*//effDateDefault');
			effDateDefault = DesktopWeb.Util.getDateDisplayValue(effDateDefault);
		_resources.popups['regulatoryStandardsPopup'].getField('effectiveDate').setValue(effDateDefault);
		_effDateDefault = effDateDefault;

		_resources.popups['validTaxTypesPopup'].init(IFDS.Xml.getNode(_initXml, "//List[@listName='taxTypes']"));
		_resources.popups['validAcctTypePopup'].init(IFDS.Xml.getNode(_initXml, "//List[@listName='AcctTypeList']"));
		_resources.popups['validAcctDesignationPopup'].init(IFDS.Xml.getNode(_initXml, "//List[@listName='AcctDesignationList']"));

		//load countries dropdown
		_resources.popups['crsReportPopup'].getField('taxJurisdictions').getStore().loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName='regCountries']"));
		_resources.popups['crsReportPopup'].getField('taxJurisdictions').setValue(_resources.popups['crsReportPopup'].getField('taxJurisdictions').getStore().getAt(0).get('code'));

		//Clone countryList without 'ALL' option
		var oriCountryDropdown = IFDS.Xml.getNode(responseXML, "//List[@listName='regCountries']");
		var clonedCountryDropdown = IFDS.Xml.cloneDocument(oriCountryDropdown); 
		var allCode = IFDS.Xml.getNode(clonedCountryDropdown, "./Element[code='All']");
		 IFDS.Xml.deleteNode(allCode);
		_resources.popups['crsJurisPopup'].getField('jurisdictions').getStore().loadData(clonedCountryDropdown);
	}	
		
	function sendWarnings(data,action)
	{
		var dataXML = null;
		if (action == _self.ADD){
			dataXML = _self.addRecord(data);
		}
        else if(action == _self.MOD){		
			dataXML = _self.modifyRecord(data);				
        }
		else if (action == _self.DEL){
			dataXML = _self.deleteRecord();			
		}
		
		DesktopWeb.Ajax.doSmartviewUpdate(_processView, null, dataXML, responseHandler);
		
		function responseHandler(success, responseXML)
		{	
			if (success)
			{			
				var warnMsgs = IFDS.Xml.getNodes(responseXML, '/*//AmendmentWarning/warnMsg');
				
				if (action == _self.ADD){
					_resources.grids['regStdInfo'].addRecord(data);
					_resources.grids['regStdInfo'].selectLastRecord();
				}
				else if (action == _self.DEL){			
					_resources.grids['regStdInfo'].removeSelectedRecord();								
				}

				if (warnMsgs != null && warnMsgs.length > 0)
				{
					displayAmendmentWarnings(warnMsgs);	
				}
				else
				{
					_self.closeActionPopup();		
					_reloadXml = responseXML;
					_self.populateGrid(_self.INIT,false);
				}
			    _self.updateActionButtons();
				_self.enableMoreButton(_nextStartRecNum);
			}
		}
	}
	
	function displayAmendmentWarnings(warnMsgs)
	{
		var msg = IFDS.Xml.getNodeValue(warnMsgs[0]);				
		for (var i = 1; i < warnMsgs.length; i++)
		{
			msg += IFDS.Xml.getNodeValue(warnMsgs[i]);
		}	
		DesktopWeb.Util.displayInfo(msg);
	}
	
	function retriveCountryDropdownLists(repXml)
	{								
		var fatcaCDOTCtyEls = IFDS.Xml.getNodes(repXml, "//List[@listName='ftcaRgltnCntryList']/Element[fatcaCode='" + _FATCACODECDOT + "']");
		_fatcaCDOTCtyListXml = IFDS.Xml.newDocument('List');
		
		Ext.each(fatcaCDOTCtyEls, function(fatcaCDOTCtyEls){
						IFDS.Xml.appendNode(_fatcaCDOTCtyListXml, IFDS.Xml.cloneDocument(fatcaCDOTCtyEls));
		})
		
		var fatcaUSCtyEls = IFDS.Xml.getNodes(repXml, "//List[@listName='ftcaRgltnCntryList']/Element[fatcaCode='" + _FATCACODEUS + "']");
		_fatcaUSCtyListXml = IFDS.Xml.newDocument('List');
		
		Ext.each(fatcaUSCtyEls, function(fatcaUSCtyEls){
					IFDS.Xml.appendNode(_fatcaUSCtyListXml, IFDS.Xml.cloneDocument(fatcaUSCtyEls));
		})
	}
	
	function replaceInvalidChars(oriString)
	{
		var replacedString = '';
		if(oriString)
		{
		   replacedString = oriString.replace (/(?:\r\n|\r|\n|\t|\"|\u201C|\u201D)/g, ' ');
		} 
		return replacedString;
	}

	function loadMoreRegStandards(responseXML, append) {
		var regRulesXML = IFDS.Xml.getNodes(responseXML, '/*//RegStandardsList');

		if (regRulesXML != null && regRulesXML != undefined && regRulesXML.length > 0) {
			_resources.grids['regStdInfo'].getStore().loadData(regRulesXML, append);
			// Allowing to append more than 100 records
			var regStds = IFDS.Xml.getNodes(IFDS.Xml.cloneDocument(IFDS.Xml.getNode(responseXML, "//RegStandardsList")), '//RegStandard');
			if(regStds) {
				Ext.each(regStds, function(regStd){
					IFDS.Xml.appendNode(IFDS.Xml.getNode(_reloadXml, '//RegStandardsList'), regStd);
				});
			}
		} else {
			_resources.grids['regStdInfo'].clearData();
		}
	}
	
	function getcomplyMstrUUID() {
		var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
		var regStandardUUID = '';
		if(selectedRecord != null) {
			regStandardUUID = selectedRecord.data['regStandardId'];
			if (regStandardUUID!= null) {
				regStandardUUID = regStandardUUID;
			} 
		}
		return regStandardUUID;
	}
	
	function getDisableEffectiveDateFlag() {
		var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
		var inActDeff = _self.NO;
		if(selectedRecord != null) {
			inActDeff = selectedRecord.data['inActDeff'];
			if (inActDeff != null && inActDeff == _self.YES) {
				inActDeff = _self.YES;
			}
		}
		return inActDeff;
	}
	//Validate if CRS Reportable is eligible - uniqueness of rule/country/date
	function validateRegulationPopup(data,action) {
        // build parameter xml
		var crsReportJurisXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'complyRule', data['regRule']);
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'complyCode', data['complyCode']);
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'complyMstrUUID', getcomplyMstrUUID());
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'complyMstrVal', _self.YES);
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'inActDeff', getDisableEffectiveDateFlag()); 
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'complyMstrCntryCode',data['countryCode']);
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'complyMstrStartDate',DesktopWeb.Util.getSMVDateValue(data['effDate']));
		IFDS.Xml.addSingleNode(crsReportJurisXML, 'complyMstrStopDate',DesktopWeb.Util.getSMVDateValue(data['stopDate']));
		
		// call service
        DesktopWeb.Ajax.doSmartviewAjax(_valCRSReportJuris, null, crsReportJurisXML, responseHandler, _translationMap['Validating']);

		function responseHandler(success, responseXML, contextErrors, contextWarnings) {
			if (success) {
				var popupCRS = _resources.popups['crsReportPopup'];
				if(data['rptJuris'].length > 0 && !popupCRS.jurisUpdateFlag) {
					searchCRSJurisdictionRecords('reload', false); 
				} else {
					searchCRSJurisdictionRecords('init', false);
				}
				
				if(popupCRS.jurisUpdateFlag) {
					popupCRS.populate();
					popupCRS.show();
				}
				setDefaultReportableJurisDates();
			}
		}
	}

	//Init loading CRS Jurisdiction list, performint searching
	function searchCRSJurisdictionRecords(runMode, append) {
		var popup = _resources.popups['regulatoryStandardsPopup'];
		var popupCRS = _resources.popups['crsReportPopup'];
		//build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
		
		var requestRecNum = _requestRecNum;
		var startRecNum = 1; 
		if(runMode == 'reload' && append == true) {
			startRecNum = popupCRS.rangeStartForNext;
		}
		
		var searchTaxCountryCode = popupCRS.getField('taxJurisdictions').getValue();
		if(!popupCRS.searchedFlag) {
			searchTaxCountryCode = popupCRS.getField('taxJurisdictions').getStore().getAt(0).get('code');
		} 
		IFDS.Xml.addSingleNode(dataXML, 'cntryCode',  searchTaxCountryCode);
		IFDS.Xml.addSingleNode(dataXML, 'complyRule', popup.getField('regulationRule').getValue()); 
		IFDS.Xml.addSingleNode(dataXML, 'complyCode', popup.getField('regulatoryCode').getValue());
		IFDS.Xml.addSingleNode(dataXML, 'complyMstrUUID', getcomplyMstrUUID());
		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?startRecNum:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', requestRecNum);

		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_crsJurisList, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])

		function responseHandler(success, responseXML) {
			// hanldle response
			if (success) {
				_resources.popups['crsReportPopup'].populate();
				_resources.popups['crsReportPopup'].show();
				
				//deal with init load and append
				var newCRSJurisXml = IFDS.Xml.getNode(responseXML, '//ComplyRptJurisList');
				if(newCRSJurisXml != null) {
					if (append) {
						_resources.grids['taxJurisGrid'].appendData(newCRSJurisXml);
					} else {
						_resources.grids['taxJurisGrid'].getStore().loadData(newCRSJurisXml);
					}
					// control more button
					var nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					_resources.popups['crsReportPopup'].moreRecordsExist = IFDS.Xml.getNodeValue(responseXML, '//RecordRange/moreRecordsExist');
					if (nextStartRecNum) {
						_resources.grids['taxJurisGrid'].enableButton('moreBtn');
						_resources.popups['crsReportPopup'].rangeStartForNext = nextStartRecNum;
					} else {
						_resources.grids['taxJurisGrid'].disableButton('moreBtn');
					}
				} 
			} else {
				_resources.popups['crsReportPopup'].moreRecordsExist = _self.NO;
			}
			_resources.popups['crsReportPopup'].searchedFlag = false;
			updateCRSJurisGridButtons(null);
		}
	}
	
	//Validate CRS Jurisdiction PopUp record
	function validateCRSJurisPopUp(data, action) {
		var popup = _resources.popups['regulatoryStandardsPopup'];
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		//Regulation popUp
		IFDS.Xml.addSingleNode(dataXML, 'complyRule', popup.getField('regulationRule').getValue());
		IFDS.Xml.addSingleNode(dataXML, 'complyCode', popup.getField('regulatoryCode').getValue());
		IFDS.Xml.addSingleNode(dataXML, 'complyMstrUUID', getcomplyMstrUUID());
		IFDS.Xml.addSingleNode(dataXML, 'complyMstrVal', _self.YES);
		IFDS.Xml.addSingleNode(dataXML, 'inActDeff', getDisableEffectiveDateFlag()); 
		IFDS.Xml.addSingleNode(dataXML, 'complyMstrCntryCode', popup.getField('country').getValue());
		IFDS.Xml.addSingleNode(dataXML, 'complyMstrStartDate', DesktopWeb.Util.getSMVDateValue(popup.getField('effectiveDate').getDisplayDateString()));
		IFDS.Xml.addSingleNode(dataXML, 'complyMstrStopDate',DesktopWeb.Util.getSMVDateValue(popup.getField('stopDate').getDisplayDateString()));
		
		var crsJurisXML = IFDS.Xml.addSingleNode(dataXML, 'ComplyRptJurisListItem'); 
		var runMode = action;
		if (action == _self.MOD) {
			var selectedCRSJurisRecord = _resources.grids['taxJurisGrid'].getSelectedRecord();
			if (selectedCRSJurisRecord.data['runMode'] == _self.ADD) runMode = _self.ADD;
		}
		IFDS.Xml.addSingleNode(crsJurisXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(crsJurisXML, 'complyRptJurisUUID', data['complyRptJurisUUID']);
		IFDS.Xml.addSingleNode(crsJurisXML, 'cntryCode', data['cntryCode']);
		IFDS.Xml.addSingleNode(crsJurisXML, 'startDate', DesktopWeb.Util.getSMVDateValue(data['startDate']));
		IFDS.Xml.addSingleNode(crsJurisXML, 'endDate', DesktopWeb.Util.getSMVDateValue(data['endDate']));

		// call service
        DesktopWeb.Ajax.doSmartviewAjax(_valCRSReportJuris, null, crsJurisXML, responseHandler, _translationMap['Validating']);
		
		function responseHandler(success, responseXML, contextErrors, contextWarnings) {
			if (success) {	
				_resources.popups['crsReportPopup'].jurisUpdateFlag = true;
				_resources.popups['crsReportPopup'].discardFlag = true;
				updateCRSJurisRecord(data, action);
				_resources.popups['crsJurisPopup'].hide();
			}
		}
	}
	
	function updateCRSJurisRecord(data, action) {
		switch(action) {
			case _self.ADD: {
				data['errMsg'] = '';
				_resources.grids['taxJurisGrid'].addRecord(data);
				_resources.grids['taxJurisGrid'].selectLastRecord();
				break;
			}
			case _self.MOD: {
				var crsJurisRec = _resources.grids['taxJurisGrid'].getSelectedRecord();
				crsJurisRec.data['runMode'] = (crsJurisRec.data['runMode'] == _self.ADD)?_self.ADD:_self.MOD;
				crsJurisRec.data['cntryCode'] = data['cntryCode'];
				crsJurisRec.data['countryDesc'] = data['countryDesc'];
				crsJurisRec.data['startDate'] = data['startDate'];
				crsJurisRec.data['endDate'] = data['endDate'];	
				data['errMsg'] = '';
				crsJurisRec.commit();
				break;
			}
			updateCRSJurisGridButtons(null);
		}
	}
	//verify CRS Jurisdiction Grid's data and handing the error
	function updatedCRSJurisGridRecords() {
		var crsRequestXML = buildCRSJurisListXML();
		var popup = _resources.popups['regulatoryStandardsPopup'];

		var dataXML = IFDS.Xml.newDocument('data');
		
		if (crsRequestXML != null) {
			IFDS.Xml.addSingleNode(dataXML, 'complyRule', popup.getField('regulationRule').getValue());
			IFDS.Xml.addSingleNode(dataXML, 'complyCode', popup.getField('regulatoryCode').getValue());
			IFDS.Xml.addSingleNode(dataXML, 'complyMstrUUID', getcomplyMstrUUID());
			IFDS.Xml.addSingleNode(dataXML, 'complyMstrVal', _self.YES);
			IFDS.Xml.addSingleNode(dataXML, 'inActDeff', getDisableEffectiveDateFlag()); 
			IFDS.Xml.addSingleNode(dataXML, 'complyMstrCntryCode', popup.getField('country').getValue());
			IFDS.Xml.addSingleNode(dataXML, 'complyMstrStartDate', DesktopWeb.Util.getSMVDateValue(popup.getField('effectiveDate').getDisplayDateString()));
			IFDS.Xml.addSingleNode(dataXML, 'complyMstrStopDate',DesktopWeb.Util.getSMVDateValue(popup.getField('stopDate').getDisplayDateString()));
			IFDS.Xml.appendNode(dataXML, crsRequestXML);
			// call service
			DesktopWeb.Ajax.doSmartviewAjax(_valCRSReportJuris, null, dataXML, responseHandler, _translationMap['Validating']);
		} else {
			_resources.popups['crsReportPopup'].hide();
		}

		function responseHandler(success, responseXML, contextErrors) {
			if (success) {	
				if (_resources.grids['taxJurisGrid'] != null) {
					var popup = _resources.popups['regulatoryStandardsPopup'];
					var getCnt = _resources.grids['taxJurisGrid'].store.getCount();
					var reportableJurisValue = popup.getField('reportableJuris').getValue();
					//set field value during memory
					if (getCnt == 1 && reportableJurisValue == '') {
						popup.getField('reportableJuris').setValue(_SINGLE);
					} else if (getCnt > 1) {
						popup.getField('reportableJuris').setValue(_MULTIPLE);
					}
				}
				_resources.popups['crsReportPopup'].hide();
			} else {
				storeContextErrors(contextErrors);//handling error of grid
				_resources.popups['crsReportPopup'].isError = true;//handling remove the error
			}
		}
	}
	//build CRS Jurisdiction list XML
	function buildCRSJurisListXML() {
		var selectedJurisRecord = _resources.grids['taxJurisGrid'].getSelectedRecord();
		var updatedRecords = _resources.grids['taxJurisGrid'].getStore().queryBy(function(record){ 
			return (record.get('runMode') == 'modify' || 
				(record.get('runMode') == 'add' && record.get('startDate') != record.get('endDate')))
				selectedJurisRecord.enableButton('modBtn'); 
			} 
		);
		
		if (updatedRecords != null && updatedRecords.length > 0) {
			var updateXML = IFDS.Xml.newDocument('data');
			var crsJurisXML = IFDS.Xml.addSingleNode(updateXML, 'ComplyRptJurisList');
			
			buildUpdateXMLAll(crsJurisXML, updatedRecords );
			function buildUpdateXMLAll(context, updatedRecords) {
				for (var i = 0; i < updatedRecords.getCount(); i++) {
					buildUpdateXMLByRecord(context, updatedRecords.itemAt(i));
				} 
			}
			return crsJurisXML;

			function buildUpdateXMLByRecord(context, updRecord) {
				var crsJurisXML = IFDS.Xml.addSingleNode(context, 'ComplyRptJurisListItem');
				IFDS.Xml.addAttribute(crsJurisXML, 'RecordSource', updRecord.data['complyRptJurisUUID']);
				IFDS.Xml.addSingleNode(crsJurisXML, 'complyRptJurisUUID', updRecord.get('complyRptJurisUUID'));
				IFDS.Xml.addSingleNode(crsJurisXML, 'cntryCode', updRecord.get('cntryCode'));
				IFDS.Xml.addSingleNode(crsJurisXML, 'startDate', DesktopWeb.Util.getSMVDateValue(updRecord.get('startDate')));
				IFDS.Xml.addSingleNode(crsJurisXML, 'endDate', DesktopWeb.Util.getSMVDateValue(updRecord.get('endDate')));
				IFDS.Xml.addSingleNode(crsJurisXML, 'runMode', updRecord.get('runMode'));
				IFDS.Xml.appendNode(context, crsJurisXML);
		   } 
		} else {
			return;
		}
	}
		
	function validateSearchCriteria() {
		if (_resources.popups['crsReportPopup'].getField('taxJurisdictions').getValue() == '') {
			_resources.popups['crsReportPopup'].getField('taxJurisdictions').markInvalid(_translationMap['FIELD_IS_REQUIRED']);
			return false;
		} else {
			return true;
		}
	}
	
	function setDefaultReportableJurisDates() {
		var popup = _resources.popups['regulatoryStandardsPopup'];
		var popupCRS = _resources.popups['crsJurisPopup'];
		var newPopupSD = DesktopWeb.Util.stringToDate(popup.getField('effectiveDate').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
		var defaultSD = DesktopWeb.Util.stringToDate(_effDateDefault, DesktopWeb.Util.getDateDisplayFormat());
		if( newPopupSD > defaultSD) {
			popupCRS.getField('startDate').setValue(newPopupSD);
		} else {
			popupCRS.getField('startDate').setValue(_effDateDefault);
		}
		popupCRS.getField('endDate').setValue(_stopDateDefault); 
	}
	
	function updateCRSJurisGridButtons(record) {
		var grid = _resources.grids['taxJurisGrid'];
		grid.enableButton('addBtn'); //based on Regulatory's permission 
		var currDate = DesktopWeb.Util.getDateString(new Date(), DesktopWeb.Util.getDateDisplayFormat());
		currDate = DesktopWeb.Util.stringToDate(currDate, DesktopWeb.Util.getDateDisplayFormat())
		
		if (record) {
			var endDate = DesktopWeb.Util.stringToDate(record.data['endDate'], DesktopWeb.Util.getDateDisplayFormat());
			if (record.data['runMode'] != null || endDate >= currDate) {
				grid.enableButton('modBtn'); 
			} else {
				grid.disableButton('modBtn');
			}
		} else {
			var selectedRecord = grid.getSelectedRecord(); 
			if (selectedRecord != null && (selectedRecord.get('runMode') != null || DesktopWeb.Util.stringToDate(selectedRecord.get('endDate'), 
										   DesktopWeb.Util.getDateDisplayFormat()) > currDate)) {
				grid.enableButton('modBtn');
			} else {
				grid.disableButton('modBtn');
				if(_resources.popups['crsReportPopup'].moreRecordsExist == _self.YES) {
					grid.enableButton('moreBtn');
				} else {
					grid.disableButton('moreBtn');
				}
			}
		}
	}
	
	//handling error of CRS Jurisdiction grid
	function storeContextErrors(errorNodes) {
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++) {
			var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			// Update CRS Juris grid
			var recordIndex = _resources.grids['taxJurisGrid'].getStore().find('complyRptJurisUUID', uuid);
			var crsJurisRecord = _resources.grids['taxJurisGrid'].getStore().getAt(recordIndex);
			crsJurisRecord.set('errMsg', errMsg);
			_resources.grids['taxJurisGrid'].getStore().commitChanges();
			if(firstErrRecIndex == -1)firstErrRecIndex = recordIndex;
		}
		
		if(firstErrRecIndex == -1) {
			_resources.grids['taxJurisGrid'].getSelectionModel().selectFirstRow();
		} else {
			_resources.grids['taxJurisGrid'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['taxJurisGrid'].focusRow(firstErrRecIndex);
		}
	}
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'modify'
		,DEL: 'delete'	
		,INIT: 'init'
		,YES: 'yes'
		,NO: 'no'
		,REGULATIONCODECRSRP: 'CRSRP'
		
		,updatesFlag: false
		,_taxtype: []
		,row: new Array()		
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;	
												
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, null, responseHandler, _translationMap['ProcMsg_Loading']); 	
						
			function responseHandler(success, responseXML)
			{						
				if (success)
				{
					storePermissions(responseXML);
					_initXml = responseXML;
					loadDropDowns(responseXML);
				}
				else 
				{
					_self.updateActionButtons();
					_resources.buttons['search'].disable();
				}
			}
		}
		
		,getInvestFor3rdPartyValue: function()
		{
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			var str = selectedRecord.data.investFor3rdParty;
			var result = str;
			str = str.toLowerCase();
			if (str == 'yes') 
				result = _translationMap['Yes'];
			else if (str == 'no')
				result = _translationMap['No'];
			return result;
		}
		,taxTypesCode: function()
		{
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();							
			var nodeArray = IFDS.Xml.getNodes(_reloadXml,'/*//RegStandard');						
			var codes = '';		
			var allTaxType;
			for(var i=0; i<nodeArray.length; i++)
			{					
				if(selectedRecord.data.regStandardId == (IFDS.Xml.getNodeValue(nodeArray[i], "regStandardId")))
				{					
					var codeArray = IFDS.Xml.getNodes(IFDS.Xml.cloneDocument(nodeArray[i]),'//TaxTypes/code');
					for(var j=0; j<codeArray.length; j++)
					{																
						if(IFDS.Xml.getNodeValue(codeArray[j]) == '*'){
					
							allTaxType = true;
						}
						else{	
							
							codes += IFDS.Xml.getNodeValue(codeArray[j], "")+',';
						}
					}	
					if (allTaxType)
					{
						codes = _translationMap['All'] + "," + codes;
					}
					codes = codes.replace(/(^,)|(,$)/g, "");
					break;
				}							
			}
			
			return codes;
		}
		
		,acctTypeCode: function()
		{
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			var nodeArray = IFDS.Xml.getNodes(_reloadXml,'/*//RegStandard');
			var codes = '';
			var allAcctType;
			for(var i=0; i<nodeArray.length; i++)
			{					
				if(selectedRecord.data.regStandardId == (IFDS.Xml.getNodeValue(nodeArray[i], "regStandardId")))
				{					
					var codeArray = IFDS.Xml.getNodes(IFDS.Xml.cloneDocument(nodeArray[i]),'//AcctTypes/code');
					for(var j=0; j<codeArray.length; j++)
					{										
						if(IFDS.Xml.getNodeValue(codeArray[j]) == '*'){
							allAcctType = true;
						}
						else{	
							codes += IFDS.Xml.getNodeValue(codeArray[j], "")+',';
						}
					}
					if (allAcctType)
					{
						codes = _translationMap['All'] + "," + codes;	
					}
					codes = codes.replace(/(^,)|(,$)/g, "");
					break;
				}							
			}
			return codes;
		}
		//account designation
		,acctDesignCode: function()
		{
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			var nodeArray = IFDS.Xml.getNodes(_reloadXml,'/*//RegStandard');
			var codes = '';
			var allAcctDesignation;
			for(var i=0; i<nodeArray.length; i++)
			{					
				if(selectedRecord.data.regStandardId == (IFDS.Xml.getNodeValue(nodeArray[i], "regStandardId")))
				{					
					var codeArray = IFDS.Xml.getNodes(IFDS.Xml.cloneDocument(nodeArray[i]),'//AcctDesignation/code');
					for(var j=0; j<codeArray.length; j++)
					{										
						if(IFDS.Xml.getNodeValue(codeArray[j]) == '*'){
							allAcctDesignation = true;
						}
						else{	
							codes += IFDS.Xml.getNodeValue(codeArray[j], "")+',';
						}
					}
					if (allAcctDesignation)
					{
						codes = _translationMap['All'] + "," + codes;	
					}
					codes = codes.replace(/(^,)|(,$)/g, "");
					break;
				}							
			}
			return codes;
		}
		//set CRS regulation rule active fields
		,setReportableJurisFields: function(regRule, action) {
			var popup = _resources.popups['regulatoryStandardsPopup'];
			if(regRule == _self.REGULATIONCODECRSRP) {
				popup.getField('reportableJuris').show();

				if(action == _self.DEL){
					Ext.getCmp('repJurisEdit').disable();
				} else {
					Ext.getCmp('repJurisEdit').enable();
					Ext.getCmp('repJurisEdit').show();
				}
				Ext.getCmp('repJurisEdit').show();

				if(action == _self.MOD){
					popup.getField('country').disableField();
				} else {
					popup.getField('country').enableField();
				}
				//enable/disable existing fields
				popup.getField('effectiveDate').enableField();
				popup.getField('investorType').disableField();
				popup.getField('investOnBehalfOfTP').disableField();
				popup.getField('lowerBound').disableField();
				popup.getField('upperBound').disableField();
				popup.getField('fundCategory').disableField();
				popup.getField('regModel').disableField();
			} else {
				popup.getField('reportableJuris').hide();
				Ext.getCmp('repJurisEdit').hide();
			}
		}
		
		,clickHandle_searchTaxJurisBtn: function() {
			if (_resources.popups['crsReportPopup'].jurisUpdateFlag) {
				DesktopWeb.Util.displayDiscardPrompt(performSearch);
			} else {
				performSearch(true);
			}
			function performSearch(confirm){
				if (confirm){
					if (validateSearchCriteria()){
						_resources.popups['crsReportPopup'].jurisUpdateFlag = false;
						_resources.popups['crsReportPopup'].discardFlag = false;
						_nextStartRecNum = 1;
						
						_resources.grids['taxJurisGrid'].getStore().removeAll();

						if (_permissionsMap[this.ADD]) {
							_resources.grids['taxJurisGrid'].enableButton('addBtn');
						} 
						_resources.popups['crsReportPopup'].searchedFlag = true;
						searchCRSJurisdictionRecords('reload', false); 
					}
				}
			}
		}

		,showHideCDOTFields: function(regRule) {
			if(regRule == 'FA') {
				_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').show();	
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').show();
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').allowBlank=false;
				_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').allowBlank=false;
			} else if (regRule == 'FT') {
				_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').show();
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').hide();
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').allowBlank=true;
				_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').allowBlank=false;
			} else {
				//Not affect US facta
				_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').hide();
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').hide();
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').allowBlank=true;
				_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').allowBlank=true;
			}
		}	
		
		,setCryList: function(code)
		{
			_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').clearField();
			if(code == _FATCACODECDOT)
			{
			   _resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').getStore().loadData(_fatcaCDOTCtyListXml);
			} else {
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').getStore().loadData(_fatcaUSCtyListXml);
			}
		}
		
		,getReplacedString: function(desc)
		{
			return replaceInvalidChars(desc);
		}

		,docList: function(cond)
		{
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			var docTemplateReturnValue = []			
			
			if(selectedRecord != null){				
				var nodeArray = IFDS.Xml.getNodes(_reloadXml,'/*//RegStandard');							
				for(var i=0; i<nodeArray.length; i++)
				{					
					if(selectedRecord.data.regStandardId == (IFDS.Xml.getNodeValue(nodeArray[i], "regStandardId")))
					{	
						var docListArray = IFDS.Xml.getNodes(IFDS.Xml.cloneDocument(nodeArray[i]), '/*//docListItem');
						if(cond == 'xTemplate'){
							for(var j=0; j< docListArray.length; j++){
								docTemplateReturnValue[j] = IFDS.Xml.getNodeValue(docListArray[j], 'docCode')
													+ '~' + IFDS.Xml.getNodeValue(docListArray[j], 'description');
							}
						}
						else{
							for(var j=0; j< docListArray.length; j++){
								docTemplateReturnValue[j] = IFDS.Xml.getNodeValue(docListArray[j], 'docItemId');
							}
						}
						break;	
					}							
				}
			}
			return docTemplateReturnValue;	
		}				
		
		,populateDocList: function()
		{			
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();				
			var nodeArray = IFDS.Xml.getNodes(_reloadXml,'/*//RegStandard');						
			
			for(var i=0; i<nodeArray.length; i++)
			{					
				if(selectedRecord.data.regStandardId == (IFDS.Xml.getNodeValue(nodeArray[i], "regStandardId")))
				{						
					var docListArray = IFDS.Xml.getNodes(IFDS.Xml.cloneDocument(nodeArray[i]), '//docList');
					_resources.selectors['docListSelector'].selectedGrid.getStore().loadData(IFDS.Xml.getNode(IFDS.Xml.cloneDocument(docListArray[0]),'//docList'));					
					break;
				}							
			}							
		}
		,populateFatcaValues: function(actionCodeList){
				if(actionCodeList =='FA'){
					_resources.popups['regulatoryStandardsPopup'].getField('actionCode').getStore().loadData(IFDS.Xml.getNodes(_initXml, "//List[@listName='ActCodes_FA_List']"));
				}
				else if(actionCodeList=='FT'){
					_resources.popups['regulatoryStandardsPopup'].getField('actionCode').getStore().loadData(IFDS.Xml.getNodes(_initXml, "//List[@listName='ActCodes_FT_List']"));
				}
				this.showHideCDOTFields(actionCodeList);
		}		
		
		,updateActionButtons: function() {	
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			if (_permissionsMap[this.ADD]) {
				_resources.grids['regStdInfo'].enableButton('addBtn');
			} else {
				_resources.grids['regStdInfo'].disableButton('addBtn');
			}
			
			if(selectedRecord) {
				if (_permissionsMap[this.MOD]) {
					_resources.grids['regStdInfo'].enableButton('modBtn');
				} else {
					_resources.grids['regStdInfo'].disableButton('modBtn');
				}
				
				if (_permissionsMap[this.DEL]) {
					//CRS Reporting rule does not allow deletion
					if(selectedRecord.data['regRule'] == _self.REGULATIONCODECRSRP) {
						_resources.grids['regStdInfo'].disableButton('delBtn');
					} else if (selectedRecord.data['regRule'] == 'FA' && selectedRecord.data['inActDeff'] == _self.YES) {
						_resources.grids['regStdInfo'].disableButton('delBtn');//fatct filling is done
					} else {
						_resources.grids['regStdInfo'].enableButton('delBtn');
					}
				} else {
					_resources.grids['regStdInfo'].disableButton('delBtn');
				}
			} else {
				_resources.grids['regStdInfo'].disableButton('modBtn');
				_resources.grids['regStdInfo'].disableButton('delBtn');
			}		
		}
		
		,enableMoreButton: function (moreRec) {
			(moreRec)
			 ? _resources.grids['regStdInfo'].enableButton(_CMORE)
			 : _self.disableMoreButton();
		}

		,disableMoreButton: function () {
			_resources.grids['regStdInfo'].disableButton(_CMORE);
		}
		
		,updateFatcaFields: function(fatcaRuleType)
		{	
			if(fatcaRuleType == 'FT' || fatcaRuleType == 'FA'){
				if(fatcaRuleType == 'FA'){
					_resources.popups['regulatoryStandardsPopup'].getField('lowerBound').disableField();
					_resources.popups['regulatoryStandardsPopup'].getField('upperBound').disableField();
					_resources.popups['regulatoryStandardsPopup'].getField('fundCategory').disableField();
					_resources.popups['regulatoryStandardsPopup'].getField('regModel').enableField();
					_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').show();
					_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').show();
				}
				else{
					_resources.popups['regulatoryStandardsPopup'].getField('lowerBound').enableField();
					_resources.popups['regulatoryStandardsPopup'].getField('upperBound').enableField();
					_resources.popups['regulatoryStandardsPopup'].getField('fundCategory').enableField();
					_resources.popups['regulatoryStandardsPopup'].getField('regModel').disableField();
					_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').show();
					_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').hide();
				}	
					_resources.popups['regulatoryStandardsPopup'].getField('actionCode').enableField();
					Ext.getCmp('acctTypeEdit').enable();
					_resources.popups['validAcctTypePopup'].clearAllFields();
					_self.populateFatcaValues(fatcaRuleType);
					
			}
			else{
				_resources.popups['regulatoryStandardsPopup'].getField('lowerBound').disableField();
				_resources.popups['regulatoryStandardsPopup'].getField('upperBound').disableField();
				_resources.popups['regulatoryStandardsPopup'].getField('fundCategory').disableField();
				_resources.popups['regulatoryStandardsPopup'].getField('actionCode').disableField();
				_resources.popups['regulatoryStandardsPopup'].getField('regModel').disableField();
				_resources.popups['regulatoryStandardsPopup'].getField('fatcaRegulation').hide();
				_resources.popups['regulatoryStandardsPopup'].getField('reportToCountry').hide();
				Ext.getCmp('acctTypeEdit').disable();
				if(fatcaRuleType == 'CRS') {
					Ext.getCmp('taxTypesEdit').disable();
				}
				_resources.fields['validAcctType'].setValue('');

			}	
		}
		
		,updateAcctRegistFields: function(regRule)
		{
			if (regRule == '0') //it remains as is, new popUp created
			{
				if (_resources.popups['regulatoryStandardsPopup'].getField('acctDesignation').disabled)
				{
					_resources.popups['regulatoryStandardsPopup'].getField('acctDesignation').enable();
				}
				_resources.fields['validAcctType'].setValue(_translationMap['All']);
				Ext.getCmp('acctTypeEdit').enable();
			}
			else 
			{
				if (!_resources.popups['regulatoryStandardsPopup'].getField('acctDesignation').disabled)
				{
					_resources.popups['regulatoryStandardsPopup'].getField('acctDesignation').disable();
				}
				
			}
		}
		//Account Designation
		,updateAcctDesignationFields: function(regRule) {
			if (regRule == _self.REGULATIONCODECRSRP || regRule == '0') {
				_resources.popups['regulatoryStandardsPopup'].getField('acctDesignation').enable();
				_resources.fields['validAcctDesignation'].setValue(_translationMap['All']);
				_resources.fields['validAcctType'].setValue(_translationMap['All']);
				Ext.getCmp('acctDesignateEdit').enable();
				Ext.getCmp('acctTypeEdit').enable();
				this.selectorGridClearData();
				_resources.selectors['docListSelector'].availableGrid.disable();
			} else { 
				_resources.popups['regulatoryStandardsPopup'].getField('acctDesignation').disable();
				_resources.fields['validAcctDesignation'].setValue('');
				Ext.getCmp('acctDesignateEdit').disable();
			}
		}
		
		,setDefaultReportableJurisDates: function() {
			setDefaultReportableJurisDates();
		}

		,selectorGridClearData: function()
		{
			var availableData = _resources.selectors['docListSelector'].availableGrid.getAllRecords();
			var selectedData = _resources.selectors['docListSelector'].selectedGrid.getAllRecords();			
			if(availableData != '' || selectedData != '')
			{	
				_resources.selectors['docListSelector'].availableGrid.clearData();
				_resources.selectors['docListSelector'].selectedGrid.clearData();
			}			
		}
		
		,populateGrid: function(action, append)
		{	
			var requestXML = IFDS.Xml.newDocument('data');

			IFDS.Xml.addSingleNode(requestXML,'regRule', _resources.fields['regulationRule'].getValue());
			IFDS.Xml.addSingleNode(requestXML,'countryCode', _resources.fields['countryFilter'].getValue());
			IFDS.Xml.addSingleNode(requestXML,'regStat', _resources.fields['status'].getValue());
			IFDS.Xml.addSingleNode(requestXML,'startRecNum', (append ? _nextStartRecNum : 1)); 
			IFDS.Xml.addSingleNode(requestXML,'requestRecNum',_requestRecNum);

			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
					
			function responseHandler(success, responseXML) {
			
				if (!append) {
					_self.updatesFlag = false;
				}
			
				if (success) {	
					var moreRecordsNode = IFDS.Xml.getNode(responseXML, '/*//RecordRange/moreRecordsExist');	
					if(moreRecordsNode != null && IFDS.Xml.getNodeValue(moreRecordsNode).toLowerCase() == 'yes') {
						_nextStartRecNum = IFDS.Xml.getNodeValue(responseXML, '/*//RecordRange/rangeStartForNext');
					} else { 
						_nextStartRecNum = 0; 
					}
					
					if(action == _self.INIT) {
						_reloadXml = responseXML;
						var btnsToEnable = (_permissionsMap[_self.ADD] ? ['addBtn'] : null);
						_resources.grids['regStdInfo'].clearData();
						_resources.grids['regStdInfo'].loadData(IFDS.Xml.getNode(responseXML, '/*//RegStandardsList'),btnsToEnable);
					} else {
						loadMoreRegStandards(responseXML, append);
					}
					
					_self.updateActionButtons();
					_self.enableMoreButton(_nextStartRecNum);
				} 
			}
		}		
		
		,docListSelectorPopulation: function()
		{
			_resources.selectors['docListSelector'].loadAvailableData(IFDS.Xml.getNode(_initXml, 	"//List[@listName='regDocLists']"));	
		}	

		,openActionCRSJurisPopup: function(action) {
			var popup = _resources.popups['crsJurisPopup'];	
			popup.show();
			popup.setTitle(_translationMap['crsReportableJuris'] + ' - ' + _translationMap[action]);
			popup.init(action);
		}		
				
		,openActionPopup: function(action)
		{
			_resources.popups['regulatoryStandardsPopup'].action=action;
			_resources.popups['regulatoryStandardsPopup'].show();
			if (action == this.ADD)
			{
				_resources.grids['regStdInfo'].clearSelectedRecord();
				_resources.popups['regulatoryStandardsPopup'].clearAllFields();

				if (_resources.popups['regulatoryStandardsPopup'].getField('country').getStore().getAt(3).get('code')!= null) {
					_resources.popups['regulatoryStandardsPopup'].getField('country').setValue(_resources.popups['regulatoryStandardsPopup'].getField('country').getStore().getAt(3).get('code'));
				}
				if (_resources.popups['regulatoryStandardsPopup'].getField('province').getStore().getAt(0).get('code')!= null) {
					_resources.popups['regulatoryStandardsPopup'].getField('province').setValue(_resources.popups['regulatoryStandardsPopup'].getField('province').getStore().getAt(0).get('code'));
				}
			}
			//set CRS
			_resources.popups['crsReportPopup'].jurisUpdateFlag = false;
			_resources.popups['crsReportPopup'].discardFlag = false;
			_resources.popups['crsReportPopup'].searchedFlag = false;
			_resources.popups['crsReportPopup'].moreRecordsExist = false;
			_resources.popups['crsReportPopup'].getField('taxJurisdictions').clearField();
			
			//clear grid data
			if(_resources.grids['taxJurisGrid'].getStore().getCount() > 0) {
				_resources.grids['taxJurisGrid'].clearData();
			}
		}

		,clickHandle_moreBtn: function() {
			searchCRSJurisdictionRecords('reload', true);
		}

		,closeActionPopup: function()
		{		
			_resources.popups['regulatoryStandardsPopup'].clearAllFields();
			_resources.popups['regulatoryStandardsPopup'].hide();
		}
		
		,savePopup: function(action, data)
		{		

			if (_self.doFrontValidate())
			{
				sendWarnings(data,action);
				this.updatesFlag = true;		
			}
		}
		
		,addRecord: function(data)
		{
			var viewParamXML = IFDS.Xml.newDocument('data');
		
			IFDS.Xml.addSingleNode(viewParamXML, 'action', data['runMode']);
			IFDS.Xml.addSingleNode(viewParamXML, 'regRuleRel', "");
			IFDS.Xml.addSingleNode(viewParamXML, 'startRecNumRel', 1);
			IFDS.Xml.addSingleNode(viewParamXML, 'requestRecNumRel', _requestRecNum);		
			
			var ProcXML = IFDS.Xml.newDocument('RegStandard');
			IFDS.Xml.addSingleNode(ProcXML, 'countryCode', data['countryCode']);
			IFDS.Xml.addSingleNode(ProcXML, 'province', data['provinceCode']);
			IFDS.Xml.addSingleNode(ProcXML, 'regRule', data['regRule']);
			IFDS.Xml.addSingleNode(ProcXML, 'complyCode', data['complyCode']);			
			IFDS.Xml.addSingleNode(ProcXML, 'description', data['description']);
			IFDS.Xml.addSingleNode(ProcXML, 'investorType', data['investorType']);
			//CRSRP -  CRS; CDOT FATCA - FATCA
			if (data['regRule'] == _self.REGULATIONCODECRSRP) {
				IFDS.Xml.addSingleNode(ProcXML, 'fatcaCode', _FATCACODECRS);
			} else {
				IFDS.Xml.addSingleNode(ProcXML, 'fatcaCode', data['fatcaRegulation']);
			}
			IFDS.Xml.addSingleNode(ProcXML, 'rptToCntry', data['reportToCountry']);

			IFDS.Xml.addSingleNode(ProcXML, 'lowerBound', data['lowerBound']);
			IFDS.Xml.addSingleNode(ProcXML, 'upperBound', data['upperBound']);
			IFDS.Xml.addSingleNode(ProcXML, 'fundCategory', data['fundCategory']);
			
			IFDS.Xml.addSingleNode(ProcXML, 'investFor3rdParty', data['investFor3rdParty']);
			IFDS.Xml.addSingleNode(ProcXML, 'effDate', DesktopWeb.Util.getSMVDateValue(data['effDate']));
			IFDS.Xml.addSingleNode(ProcXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
			IFDS.Xml.addSingleNode(ProcXML, 'inActDeff', _self.NO);

			var taxTypes = data['TaxTypes'].split(',');	
			var TaxTypeList = IFDS.Xml.newDocument('TaxTypeList');				
			for ( var i = 0; i < taxTypes.length; i++ )
			{					
				var TaxType = IFDS.Xml.newDocument('TaxType');	
				if (taxTypes[i] == _translationMap['All'])
					IFDS.Xml.addSingleNode(TaxType,'code',"ALL");
				else
					IFDS.Xml.addSingleNode(TaxType,'code',taxTypes[i]);				
				IFDS.Xml.appendNode(TaxTypeList,TaxType);				
			}				
			IFDS.Xml.appendNode(ProcXML, TaxTypeList);

			var acctType = data['AccountType'].split(',');
			var AccountTypeList = IFDS.Xml.newDocument('AccountTypeList');
			for ( var i = 0; i < acctType.length; i++ )
			{					
				var AccountType = IFDS.Xml.newDocument('AccountType');
				
				if (acctType[i] == _translationMap['All'])
					IFDS.Xml.addSingleNode(AccountType,'code',"ALL");
				else
					IFDS.Xml.addSingleNode(AccountType,'code',acctType[i]);
				IFDS.Xml.appendNode(AccountTypeList,AccountType); 
			}
			IFDS.Xml.appendNode(ProcXML, AccountTypeList);
			//AcctDesignation xml
			var acctDesigna = data['AcctDesignation'].split(',');
			var AcctDesignationList  = IFDS.Xml.newDocument('AcctDesignationList');
			for ( var i = 0; i < acctDesigna.length; i++ ) {			
				var AcctDesignation = IFDS.Xml.newDocument('AcctDesignation');
				
				if (acctDesigna[i] == _translationMap['All'])
					IFDS.Xml.addSingleNode(AcctDesignation,'code',"ALL");
				else
					IFDS.Xml.addSingleNode(AcctDesignation,'code',acctDesigna[i]);
				IFDS.Xml.appendNode(AcctDesignationList ,AcctDesignation); 
			}
			IFDS.Xml.appendNode(ProcXML, AcctDesignationList);
			//CRS Juris updated xml only for CRS Report Regulation
			if(data['regRule'] == _self.REGULATIONCODECRSRP) {
				var crsJurisListXML = buildCRSJurisListXML();
				if (crsJurisListXML != null) {
					IFDS.Xml.appendNode(ProcXML, buildCRSJurisListXML()); 
				}
			} else {
				if (_resources.grids['taxJurisGrid'] != null) {
					_resources.grids['taxJurisGrid'].getStore().removeAll();
				}
			}
			
			IFDS.Xml.addSingleNode(ProcXML, 'actionCode', data['actionCode']);
			IFDS.Xml.addSingleNode(ProcXML, 'regModel', data['regModel']);

			var DocList = IFDS.Xml.newDocument('docList');
			for ( var i = 0; i < data['docList'].length; i++ )
			{
				if ( data['docList'][i].data.docCode !=null )
				{	
					var DocListItem = IFDS.Xml.newDocument('docListItem');			
					IFDS.Xml.addSingleNode(DocListItem,'action',data['runMode']);
					IFDS.Xml.addSingleNode(DocListItem,'docCode',data['docList'][i].data.docCode);				
				}
				IFDS.Xml.appendNode(DocList,DocListItem);				
			}
			IFDS.Xml.appendNode(ProcXML, DocList);
			
			IFDS.Xml.appendNode(viewParamXML, ProcXML);
			return viewParamXML;
		}
		
		,modifyRecord: function(data)
		{
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			
			var viewParamXML = IFDS.Xml.newDocument('data');
		
			IFDS.Xml.addSingleNode(viewParamXML, 'action', 'modify');
			IFDS.Xml.addSingleNode(viewParamXML, 'regRuleRel', "");
			IFDS.Xml.addSingleNode(viewParamXML, 'startRecNumRel', 1);
			IFDS.Xml.addSingleNode(viewParamXML, 'requestRecNumRel', _requestRecNum);
			
			var ProcXML = IFDS.Xml.newDocument('RegStandard');
			
			IFDS.Xml.addSingleNode(ProcXML, 'regStandardId', selectedRecord.data['regStandardId']);			
			IFDS.Xml.addSingleNode(ProcXML, 'countryCode', data['countryCode']);
			IFDS.Xml.addSingleNode(ProcXML, 'province', data['provinceCode']);

			regulationRuleCode = _self.getCodeFromList('regRules',data['regRule']);
			IFDS.Xml.addSingleNode(ProcXML, 'regRule', regulationRuleCode);

			IFDS.Xml.addSingleNode(ProcXML, 'complyCode', data['complyCode']);
			IFDS.Xml.addSingleNode(ProcXML, 'description', data['description']);
			IFDS.Xml.addSingleNode(ProcXML, 'investorType', data['investorType']);
			
			//CRSRP -  CRS; CDOT FATCA - FATCA
			if (data['regRule'] == _self.REGULATIONCODECRSRP) {
				IFDS.Xml.addSingleNode(ProcXML, 'fatcaCode', _FATCACODECRS);
			} else {
				IFDS.Xml.addSingleNode(ProcXML, 'fatcaCode', data['fatcaRegulation']);
			}
			IFDS.Xml.addSingleNode(ProcXML, 'rptToCntry', data['reportToCountry']);

			IFDS.Xml.addSingleNode(ProcXML, 'lowerBound', data['lowerBound']);
			IFDS.Xml.addSingleNode(ProcXML, 'upperBound', data['upperBound']);
			FundCategoryCode = _self.getCodeFromList('FundCatList',data['fundCategory']);
			IFDS.Xml.addSingleNode(ProcXML, 'fundCategory', FundCategoryCode);

			IFDS.Xml.addSingleNode(ProcXML, 'investFor3rdParty', data['investFor3rdParty']);
			IFDS.Xml.addSingleNode(ProcXML, 'effDate', DesktopWeb.Util.getSMVDateValue(data['effDate']));
			IFDS.Xml.addSingleNode(ProcXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			IFDS.Xml.addSingleNode(ProcXML, 'inActDeff', selectedRecord.data['inActDeff']);
			
			var taxTypes = data['TaxTypes'].split(',');	
			var TaxTypeList = IFDS.Xml.newDocument('TaxTypeList');				
			for ( var i = 0; i < taxTypes.length; i++ )
			{					
				var TaxType = IFDS.Xml.newDocument('TaxType');		
				if (taxTypes[i] == _translationMap['All'])
					IFDS.Xml.addSingleNode(TaxType,'code',"ALL");
				else
					IFDS.Xml.addSingleNode(TaxType,'code',taxTypes[i]);		
				IFDS.Xml.appendNode(TaxTypeList,TaxType);
			}				
			IFDS.Xml.appendNode(ProcXML, TaxTypeList);		

			var acctType = data['AccountType'].split(',');
			var AccountTypeList = IFDS.Xml.newDocument('AccountTypeList');
			for ( var i = 0; i < acctType.length; i++ )
			{					
				var AccountType = IFDS.Xml.newDocument('AccountType');
				if (acctType[i] == _translationMap['All'])
					IFDS.Xml.addSingleNode(AccountType,'code',"ALL");
				else
					IFDS.Xml.addSingleNode(AccountType,'code',acctType[i]);
				IFDS.Xml.appendNode(AccountTypeList,AccountType);
			}
			IFDS.Xml.appendNode(ProcXML, AccountTypeList);
			
			//acctDesignation xml
			var acctDesigna = data['AcctDesignation'].split(',');
			var AcctDesignationList = IFDS.Xml.newDocument('AcctDesignationList');
			for ( var i = 0; i < acctDesigna.length; i++ ) {			
				var AcctDesignation = IFDS.Xml.newDocument('AcctDesignation');
				
				if (acctDesigna[i] == _translationMap['All'])
					IFDS.Xml.addSingleNode(AcctDesignation,'code',"ALL");
				else
					IFDS.Xml.addSingleNode(AcctDesignation,'code',acctDesigna[i]);
				IFDS.Xml.appendNode(AcctDesignationList ,AcctDesignation); 
			}
			IFDS.Xml.appendNode(ProcXML, AcctDesignationList);
			
			//CRS Juris updated xml only for CRS Report Regulation rule
			if(data['regRule'] == _self.REGULATIONCODECRSRP) {
				var crsJurisListXML = buildCRSJurisListXML();
				if (crsJurisListXML != null) {
					IFDS.Xml.appendNode(ProcXML, buildCRSJurisListXML()); 
				}
			}

			actionCodeCode="";
			if(regulationRuleCode =='FA'){
				actionCodeCode = _self.getCodeFromList('ActCodes_FA_List',data['actionCode']);
			}else if(regulationRuleCode =='FT'){
				actionCodeCode = _self.getCodeFromList('ActCodes_FT_List',data['actionCode']);	
			}
			
			IFDS.Xml.addSingleNode(ProcXML, 'actionCode', actionCodeCode);
			IFDS.Xml.addSingleNode(ProcXML, 'regModel', data['regModel']);
			IFDS.Xml.addSingleNode(ProcXML, 'acctDesignation', data['acctDesignation']);

			var DocList = IFDS.Xml.newDocument('docList');			
			var	docData	= _resources.selectors['docListSelector'].selectedGrid.getAllRecords();
			
			for(var i =0; i<docData.length; i++){				
				if ( docData[i].data.docItemId == null || docData[i].data.docItemId == ''){
					var DocListItem = IFDS.Xml.newDocument('docListItem');			
					IFDS.Xml.addSingleNode(DocListItem,'action','add');
					IFDS.Xml.addSingleNode(DocListItem,'docCode',docData[i].data.docCode);				
					IFDS.Xml.appendNode(DocList,DocListItem);				
				}				
			}
			var matched = false;
			var docCodeList = _self.docList();
			for(var i = 0; i < docCodeList.length; i++){
				for(var j =0; j<docData.length;	j++){					
					if(docCodeList[i] == docData[j].data.docItemId){	
						matched = true;
						break; 
					}
					else{
						matched = false;
					}
				}
				if(!matched)
				{
					var DocListItem = IFDS.Xml.newDocument('docListItem');			
					IFDS.Xml.addSingleNode(DocListItem,'action','delete');
					IFDS.Xml.addSingleNode(DocListItem,'docItemId',docCodeList[i].split('~')[0]);				
					IFDS.Xml.appendNode(DocList,DocListItem);
				}
			}			
			IFDS.Xml.appendNode(ProcXML, DocList);
					
			IFDS.Xml.appendNode(viewParamXML, ProcXML);
			return viewParamXML;
		}
		
		,deleteRecord: function()
		{
			var selectedRecord = _resources.grids['regStdInfo'].getSelectedRecord();
			
			var viewParamXML = IFDS.Xml.newDocument('data');
		
			IFDS.Xml.addSingleNode(viewParamXML, 'action', 'delete');
			IFDS.Xml.addSingleNode(viewParamXML, 'regRuleRel', "");
			IFDS.Xml.addSingleNode(viewParamXML, 'startRecNumRel', 1);
			IFDS.Xml.addSingleNode(viewParamXML, 'requestRecNumRel', _requestRecNum);		
			
			var ProcXML = IFDS.Xml.newDocument('RegStandard');
			
			IFDS.Xml.addSingleNode(ProcXML, 'regStandardId', selectedRecord.data['regStandardId']);			
			IFDS.Xml.addSingleNode(ProcXML, 'description', selectedRecord.data['description']);
			IFDS.Xml.addSingleNode(ProcXML, 'investorType', selectedRecord.data['investorType']);

			IFDS.Xml.addSingleNode(ProcXML, 'lowerBound', selectedRecord.data['lowerBound']);
			IFDS.Xml.addSingleNode(ProcXML, 'upperBound', selectedRecord.data['upperBound']);
			IFDS.Xml.addSingleNode(ProcXML, 'fundCategory', selectedRecord.data['fundCategory']);
			
			IFDS.Xml.addSingleNode(ProcXML, 'fatcaCode', selectedRecord.data['fatcaRegulation']);
			IFDS.Xml.addSingleNode(ProcXML, 'rptToCntry', selectedRecord.data['reportToCountry']);

			IFDS.Xml.addSingleNode(ProcXML, 'investFor3rdParty', selectedRecord.data['investFor3rdParty']);
			
			IFDS.Xml.addSingleNode(ProcXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(selectedRecord.data['stopDate']));

			IFDS.Xml.addSingleNode(ProcXML, 'actionCode', selectedRecord.data['actionCode']);
			
			IFDS.Xml.addSingleNode(ProcXML, 'regModel', selectedRecord.data['regModel']);
			
			IFDS.Xml.addSingleNode(ProcXML, 'acctDesignation', selectedRecord.data['acctDesignation']);

			var	docData	= _resources.selectors['docListSelector'].selectedGrid.getAllRecords();
			
			var DocList = IFDS.Xml.newDocument('docList');
			for ( var i = 0; i < docData.length; i++ )
			{
				if ( docData[i].data.docItemId == '' )
				{	
					var DocListItem = IFDS.Xml.newDocument('docListItem');			
					IFDS.Xml.addSingleNode(DocListItem,'action','add');
					IFDS.Xml.addSingleNode(DocListItem,'docCode',docData[i].data.docCode);				
					IFDS.Xml.appendNode(DocList,DocListItem);				
				}				
			}
			IFDS.Xml.appendNode(ProcXML, DocList);
					
			IFDS.Xml.appendNode(viewParamXML, ProcXML);
			return viewParamXML;
		}
		
		,getRecordIndex: function(fld, value)
		{					
			var record = _resources.popups['regulatoryStandardsPopup'].getField(fld).findRecord(_resources.popups['regulatoryStandardsPopup'].getField(fld).valueField, value);
			var index = _resources.popups['regulatoryStandardsPopup'].getField(fld).getStore().indexOf(record);
			return 	index
		}
		
		,validateRegulationPopup: function(data, action) {
			return 	validateRegulationPopup(data, action);
		}
		
		,editValidTaxTypes: function()
		{
			_resources.popups['validTaxTypesPopup'].populate();
			_resources.popups['validTaxTypesPopup'].show();
		}
		
		,editValidAcctType: function()
		{
			_resources.popups['validAcctTypePopup'].populate();
			_resources.popups['validAcctTypePopup'].show();
		}

		,editValidAcctDesignation: function() {
			_resources.popups['validAcctDesignationPopup'].populate();
			_resources.popups['validAcctDesignationPopup'].show();
		}

		,updateValidTaxTypes: function()
		{
			var taxTypeSelected = _resources.popups['validTaxTypesPopup'].getData();
			if(taxTypeSelected == ''){
				taxTypeSelected = _translationMap['All'];
			}
			_resources.fields['validTaxTypes'].setValue(taxTypeSelected);
		}

		,updateValidAcctType: function()
		{
			var accountTypeSelected = _resources.popups['validAcctTypePopup'].getData();
			if(accountTypeSelected == ''){
					accountTypeSelected= _translationMap['All'];
			}
			_resources.fields['validAcctType'].setValue(accountTypeSelected);
		}
		
		,updateValidAcctDesignation: function() {
			var acctDesignationSelected = _resources.popups['validAcctDesignationPopup'].getData();
			if (acctDesignationSelected == '') {
				acctDesignationSelected= _translationMap['All'];
			}
			_resources.fields['validAcctDesignation'].setValue(acctDesignationSelected);
		}
		
		,validateCRSJurisPopUp: function(data, action) {
			validateCRSJurisPopUp(data, action);
		}
		
		,getNewCRSJurisUUID: function() {
			return "TMPCRSJURIS" + (_nextUUID++);
		}
		
		,updatedCRSJurisGridRecords: function() {
			return updatedCRSJurisGridRecords();
		}
		
		,selectCRSJuris: function(record) {
			updateCRSJurisGridButtons(record);
		}

		,getCodeFromList: function(listName, value)
		{	
			code = IFDS.Xml.getNodeValue(_initXml, "//List[@listName = '" + listName + "']/Element[value = '" + value + "']/code");
			if(code == "" || code == null){code=value;}
			return code;
		}

		,doFrontValidate: function()
		{
			var pass = true;
			if ((_resources.popups['regulatoryStandardsPopup'].getField('regulationRule').getValue() == 'FA' || _resources.popups['regulatoryStandardsPopup'].getField('regulationRule').getValue() == 'FATCA')
				&& _resources.popups['regulatoryStandardsPopup'].getField('regModel').getValue() == '')
			{
				_resources.popups['regulatoryStandardsPopup'].getField('regModel').markInvalid(_translationMap['FldRequired']);
				pass = false;
			}
			return pass;
		}
	}
}