/*********************************************************************************************
 * @file	OvrdLimit.Controller.js	
 * @author	Rod Walker	
 * @desc	Resources JS file Fund Limitations Override screen
 *********************************************************************************************/
/*
 * Procedure: OvrdLimit.Controller.js
 *
 * Purpose  : Controller file for Fund Limitations Override screen
 *             
 * Notes    : 
 *
 * History  :
 *
 *		06 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54444
 *					- Correct the format of all date fields based on registry edit
 *					, called displayMark
 *
 *		21 Nov 2013 Winnie Cheng. P0221029 FN01  T77274
 *					- B-A Rollover rule for stop sysmatic rollover for MFS
 *					- Displaying Broker/Branch/Rep or Account on Add(grid), Modify and Delete window
 *
 *		24 Jan 2014 Narin Suanlamyai. P0224204 FN01 T54714
 *					- Identifying and Reporting NSCC Clearing Firms
 *					- Allow user to setup 'Stop Purchase', 'Stop Redemption', 'Stop Transfer IN',
 *					  and 'Stop Transfer OUT' at branch level.
 *
 *		17 Apr 2014 Gomoot T. P0224204 FN01 DFT0032138 T55018
 *					- Fix JavaScript Error when user presses Search button
 *
 *		16 May 2014 Winnie Cheng. P0225761 FN01 T77895
 *					- Allow user to setup 'Stop Purchase/Redemption/TransferIN/TransferOUT at fund group level
 *					- Adding a new validation that preventing Sponser/Fund/Class & FundGroup together
 *					- Loosing BK/BR/RP validation for above rules	
 *
 *		10 Dec 2014 Alka - CHG0039170
 *					- "overrideLog" tag was sent twice in case of adding new Stop Systematic Rollover. So changing sendAddLookupRequest()
 *
 *		27 April 2015 Winnie Cheng. P0240531 FN01 T80476
 *					- Allow user to setup 'Rounding Rule"	
 *
 *		24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.  
 *
 * 		28 March 2016 Sumit Singh P0181067 FN01 T82075
 *					- Desktop is  not checking the menu level permission for Add and Delete on Rep Level Exclusion"	
 *
 *      22-Nov-2016 Zeljko Bajic P0257851 T84326 CHG0047691_MinInvestment
 *					- Added new implementation as required.
 *
 * 		06-Jan-2017 Matira Thanetkulabut P0257853 T84533 Minimum Investment
 *					- Added amount type field.
 *					- Added for support new ruleType 66-67.
 *
 * 		30-Jan-2017 Matira Thanetkulabut P0260717 T84790 SAM Broker Settlement 17.3
 *					- Added for support new ruleType 24-29.
 *
 * 		02-Mar-2017 Matira Thanetkulabut P0260717 T84984 DFT0072929
 *					- Fixed ruleType 66-67 can setup same as Min Init. redemption.
 *
 * 		13-Mar-2017 Matira Thanetkulabut P0260717 T85050 DFT0073213 DFT0073214 DFT0072929 DFT0073225
 *					- hide currency field for ruleType 66-67.
 *					- hide amounttype and currency field for ruletype 24-29.
 *					- set acctLevel = yes for ruletype 24-29,66-67.
 *
 *		22-Mar-2017 Matira Thanetkulabut P0257853 T85108 Minimum Investment DFT0073041 DFT0073475 DFT0073489
 *					- added assetLevel, assetType, amountType and currency fields for modify and details popups.
 *					- fixed issues create buy back rule for all level.
 *
 *		30-Mar-2017 Matira Thanetkulabut P0257853 T85204 Minimum Investment DFT0073792
 *					- fixed listBasedOn options when fundGroup is created.
 *
 *		10-Apr-2017 Nopphawan Hatthaseriphong P0264164 T85279 Diamond Share Class Restriction
 *					- Added Historical button.
 *                  - Added rule 76, 77, 78 and 79.
 *                  - For Rule 79, the currency field should be displayed if the amount type is “D”.
 *
 *		25-Apr-2017 Nopphawan Hatthaseriphong P0264164 T85370 Diamond Share Class Restriction
 *					- Removed hard-coding _withCurr, _dayAmt, _withAssetType, _withAssetLevel
 * 
 *		20-Jun-2017 Nopphawan Hatthaseriphong P0264164 T85751 DFT0075717 Diamond Share Class Restriction
 *					- Fixed RuleType = '60' will not send 'acctLevel' to back-end
 *
 *		28-Jun-2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *					- Add support rule 80 : account level only 
 *					- Move function to private 
 *
 *
 *		4-Jul-2017 Gomoot T. P0268199 CHG0049877 CRM2 Compensation Report T85814
 *					- Add support rule 81 : Broker level only 
 *
 *		24-Jul-2017 Matira Thanetkulabut P0266360 T85923 Custodian File Enhancements
 *					- Adde support rule 82: Broker level
 *
 *		30-Aug-2017 Nopphawan Hatthaseriphong P0269734 CHG0050897 T86187 Unit Calculation Method Override
 *                  - Added new rule type '83 - Unit Calculation Method'
 *                  
 *      02-Feb-2018 Matira Thanetkulabut P0274833-5 NCO - HKB WSDF Create Bulk Transactions as wire (T+2)
 *					- Added new rule 84 - Wire Order Trade                
 */

 
DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _accountInitView = "dtOvrdLimitActInit";
	var _brokerInitView = 'dtOvrdLimitBrkInit';
	var _reloadView = "dtOvrdLimitReload";
	var _modifyView = "dtOvrdLimitModify"
	var _deleteView = "dtOvrdLimitDelete";
	var _addLookupView = "dtOvrdLimitProcess";
	var _addCommitView = "dtOvrdLimitAdd"
	var _stopView = 'dtOvrdLimitStop';
	var _historicalInfo = 'dtHistoricalInfo';

	var _initResponseXml = null;
	var BROKERONLY = 'BK/BR/RP';
	var BROKERBRANCHONLY = 'BR/RP';
	var REPONLY = 'RP';

	var _nextStartRecNum = null;	
	var _listMap = null;
	var _defaultValues = {};	
	var _permissionsMap = {};//added for CHG0043739
	var _brrpCanBlk = ['01','24','25','26','27','28','29','51','52','53','58','65','66','67','68','77','78','79','81','82','83'];
	var _hiddenListBasedOnAcct = ['58','80'];
	var _hiddenListBasedOnBRK  = ['58','60','81','82'];
	// 76, 77, 78 are overrideLog ; others are overrideDec
	var _fundListBasedOnBroker  = ['01','24','25','26','27','28','29','65','66','67','68','77','78','79','83'];
	var _fundListBasedOnAccount = ['01','55','56','57','65','66','67','68','76','77','78','79','83'];
	var _overrideCharList = ['30','46','83']
	var _requestRecNum = 100;

		//Change for CHG0043739 starts
	function storePermissions(initViewXML) {
	  _permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/addPerm').toLowerCase() == 'yes';
	  _permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/modPerm').toLowerCase() == 'yes';
	  _permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/delPerm').toLowerCase() == 'yes';
	  _permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/inqPerm').toLowerCase() == 'yes';
	}

	
	//This method is implemented to check the permissions set for user.
	function checkPermissions(isSearchRecordPresent) {
	    _resources.grids['ovrdRules'].disableButton('addBtn');
	    _resources.grids['ovrdRules'].disableButton('modBtn');
	    _resources.grids['ovrdRules'].disableButton('delBtn');
	    _resources.grids['ovrdRules'].disableButton('stopBtn');
	    _resources.grids['ovrdRules'].disableButton('adminBtn');
	    _resources.grids['ovrdRules'].disableButton('detlsBtn');
	    _resources.grids['ovrdRules'].disableButton('historicalBtn');
	   
		 if (_permissionsMap[_self.ADD])
			_resources.grids['ovrdRules'].enableButton('addBtn');

				//The below permissions will be checked only in case there is any record in search grid
		 if (isSearchRecordPresent) {
			if (_permissionsMap[_self.MOD])
				_resources.grids['ovrdRules'].enableButton('modBtn');
	
			if (_permissionsMap[_self.DEL])
				_resources.grids['ovrdRules'].enableButton('delBtn');
	
			if (_permissionsMap[_self.MOD])
				_resources.grids['ovrdRules'].enableButton('stopBtn');
	
			_resources.grids['ovrdRules'].enableButton('adminBtn');
			_resources.grids['ovrdRules'].enableButton('detlsBtn');
			_resources.grids['ovrdRules'].enableButton('historicalBtn');
		 }
	 
	}
  //Change for CHG0043739 Ends

	// PRIVATE METHODS ****************************************
	function storeDefaultValues(initViewXML)
	{
		_defaultValues['startDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(initViewXML, "/*//DefaultValues/start"));
		_defaultValues['stopDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(initViewXML, "/*//DefaultValues/stop"));   
		_defaultValues['amountType'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(initViewXML, "/*//DefaultValues/amountType"));  
	}
	
	function populateAccount(initViewXML)
	{		
		var accountDesc = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		accountDesc += " - " + IFDS.Xml.getNodeValue(initViewXML, '/*//lastName');
		accountDesc += ", " + IFDS.Xml.getNodeValue(initViewXML, '/*//firstName');		
		_resources.fields['accountNum'].setValue(accountDesc); 
	}
	
	function loadDropdowns(initViewXML)
	{			
		_listMap = {};		
		var listNodes = IFDS.Xml.getNodes(initViewXML, '/*//List');
		for (var i = 0; i < listNodes.length; i++)
		{
		  var listName = IFDS.Xml.getAttributeValue(listNodes[i], '@listName');
			if (!listName)
			{
			    listName = IFDS.Xml.getAttributeValue(listNodes[i], '@id');
			}			
			_listMap[listName] = listNodes[i];
		}
		if (_self.IS_ACCOUNT_LEVEL)
		{					
			_listMap['KIIDComboList'] = IFDS.Xml.newDocument('List');
			IFDS.Xml.appendNode(_listMap['KIIDComboList'], IFDS.Xml.cloneDocument(_listMap['KIIDWaiverList']));
			IFDS.Xml.appendNode(_listMap['KIIDComboList'], IFDS.Xml.cloneDocument(_listMap['KIIDAttestationList']));
		}		

		// dropdown fields in search form
		_resources.fields['ruleType'].loadData(_listMap['RuleTypeOptions']);
		_resources.fields['fundSponsor'].loadData(_listMap['FundSponsorList']);
		_resources.fields['classCode'].loadData(_listMap['ClassList']);

		// dropdown fields in add popup
		var addPopup = _resources.popups['add']
		addPopup.getField('ruleType').loadData(_listMap['RuleTypeOptions']);		
		addPopup.getField('ruleType').getStore().removeAt(0); // remove 'ALL' option			
		addPopup.getField('fundSponsor').loadData(_listMap['FundSponsorList']);
		addPopup.getField('classCode').loadData(_listMap['ClassList']);
		
		addPopup.getField('verifystatus').loadData(_listMap['VerifyStatusList']);
		addPopup.getField('currency').loadData(_listMap['CurrencyList']);
		addPopup.getField('onlineEWI').loadData(_listMap['EWIOptions']);
		addPopup.getField('cycleEWI').loadData(_listMap['EWIOptions']);
		addPopup.getField('esgEWI').loadData(_listMap['EWIOptions']);
		if (_listMap['RDRRuleList'])
		{
			addPopup.getField('rdrAdvice').loadData(_listMap['RDRRuleList']);
		}
		if (_self.IS_ACCOUNT_LEVEL)
		{					
			addPopup.getField('reason').loadData(_listMap['KIIDWaiverReasonList']);			
		}
		else
		{
			addPopup.getField('responsibility').loadData(_listMap['KIIDResponsibleList']);		
		}

		// dropdown fields in modify popup
		var modPopup = _resources.popups['modify'];
		modPopup.getField('onlineEWI').loadData(_listMap['EWIOptions']);
		modPopup.getField('cycleEWI').loadData(_listMap['EWIOptions']);	
		modPopup.getField('esgEWI').loadData(_listMap['EWIOptions']);
		modPopup.getField('verifystatus').loadData(_listMap['VerifyStatusList']);
		modPopup.getField('currency').loadData(_listMap['CurrencyList']);
		if (_listMap['RDRRuleList'])
		{
			modPopup.getField('rdrAdvice').loadData(_listMap['RDRRuleList']);
		}
		if (_self.IS_ACCOUNT_LEVEL)
		{			
			modPopup.getField('reason').loadData(_listMap['KIIDWaiverReasonList']);			
		}
		else 
		{
			modPopup.getField('responsibility').loadData(_listMap['KIIDResponsibleList']);	
		}
	}
	
	function loadOvrdRules(initViewXML, more)
	{				
		
		_resources.fields['broker'].disable();
		_resources.fields['branch'].disable();
		_resources.fields['slsrep'].disable();
		
		_resources.fields['fundSponsor'].disable();
		_resources.fields['fund'].disable();
		_resources.fields['fundGroup'].disable();
		_resources.fields['classCode'].disable();
		_resources.fields['ruleType'].disable();
		_resources.fields['showOnlyActiveRecords'].disable();
		Ext.getCmp('searchBtn').disable();
		Ext.getCmp('resetBtn').enable();
		
		if (more)
		{
			_resources.grids['ovrdRules'].appendData(IFDS.Xml.getNode(initViewXML, '/*//ExistingRulesList'));
		}
		else
		{
			_resources.grids['ovrdRules'].loadData(IFDS.Xml.getNode(initViewXML, '/*//ExistingRulesList'));
		}
	}

	function sendReloadRequest(more)
	{
		var viewParamXML = IFDS.Xml.newDocument('data');	
		if (_self.IS_ACCOUNT_LEVEL)
		{
			IFDS.Xml.addSingleNode(viewParamXML, 'searchType', 'account');
			IFDS.Xml.addSingleNode(viewParamXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		}
		else
		{
			IFDS.Xml.addSingleNode(viewParamXML, 'searchType', 'broker');
			IFDS.Xml.addSingleNode(viewParamXML, 'broker', _resources.fields['broker'].getValue());
			IFDS.Xml.addSingleNode(viewParamXML, 'branch', _resources.fields['branch'].getValue());
			IFDS.Xml.addSingleNode(viewParamXML, 'slsrep', _resources.fields['slsrep'].getValue());
		}
		IFDS.Xml.addSingleNode(viewParamXML, 'fundSponsor', _resources.fields['fundSponsor'].getValue());		
		IFDS.Xml.addSingleNode(viewParamXML, 'fund', (_resources.fields['fund'].getSelectedRecord() ? _resources.fields['fund'].getSelectedRecord().data['fund'] : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'fundGroup', _resources.fields['fundGroup'].getValue());
		IFDS.Xml.addSingleNode(viewParamXML, 'class', (_resources.fields['fund'].getSelectedRecord() ? _resources.fields['fund'].getSelectedRecord().data['class'] : _resources.fields['classCode'].getValue()));		
		IFDS.Xml.addSingleNode(viewParamXML, 'ruleType', _resources.fields['ruleType'].getValue());
		IFDS.Xml.addSingleNode(viewParamXML, 'activeOnly', (_resources.fields['showOnlyActiveRecords'].getValue() ? 'true' : 'false'));
		IFDS.Xml.addSingleNode(viewParamXML, 'startRecNum', (more ? _nextStartRecNum : 1));
		IFDS.Xml.addSingleNode(viewParamXML, 'requestRecNum', _requestRecNum);
																
		DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Searching']);			
		
		function responseHandler(success, responseXML)
		{						
			if (success)
			{					
				loadOvrdRules(responseXML, more);
			
				if (IFDS.Xml.getNodeValue(responseXML, '/*//RecordRange/moreRecordsExist').toLowerCase() == 'yes')
				{
					_resources.grids['ovrdRules'].enableButton('moreBtn');
					_nextStartRecNum = IFDS.Xml.getNodeValue(responseXML, '/*//RecordRange/rangeStartForNext');						
				}
				else
				{
					_resources.grids['ovrdRules'].disableButton('moreBtn');
					_nextStartRecNum = null;
				}
			}	
		}
	}

	function allowAdd()
	{
		var allowAdd = true;

		if (!_self.IS_ACCOUNT_LEVEL)
		{			
			allowAdd = allowAdd && _resources.fields['broker'].isValid();
			allowAdd = allowAdd && _resources.fields['branch'].isValid();
			allowAdd = allowAdd && _resources.fields['slsrep'].isValid();
		}

		return allowAdd;
	}
		
	function sendAddLookupRequest(callbackFn)
	{
		var addPopup = _resources.popups['add'];
		var xml = IFDS.Xml.newDocument("data");
				
		if (_self.IS_ACCOUNT_LEVEL)
		{
			IFDS.Xml.addSingleNode(xml, 'searchType', 'account');
			IFDS.Xml.addSingleNode(xml, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		}
		else
		{
			IFDS.Xml.addSingleNode(xml, 'searchType', 'broker');
			IFDS.Xml.addSingleNode(xml, 'broker', _resources.fields['broker'].getValue());
			IFDS.Xml.addSingleNode(xml, 'branch', _resources.fields['branch'].getValue());
			IFDS.Xml.addSingleNode(xml, 'slsrep', _resources.fields['slsrep'].getValue());
			
		}
		
		IFDS.Xml.addSingleNode(xml, 'startDate', addPopup.getField('startDate').getSMVDateString());
		IFDS.Xml.addSingleNode(xml, 'stopDate', addPopup.getField('stopDate').getSMVDateString());
		
		var listBasedOn = addPopup.getField('listBasedOn').getValue();
		if (listBasedOn == "fundSponsor")
		{			
			IFDS.Xml.addSingleNode(xml, 'fundSponsor', addPopup.getField('fundSponsor').getValue());
		}
		else if (listBasedOn == "fundCode")
		{
			IFDS.Xml.addSingleNode(xml, 'fundSponsor', addPopup.getField('fundSponsor').getValue());
			IFDS.Xml.addSingleNode(xml, 'fund', (addPopup.getField('fundCode').getSelectedRecord() ? addPopup.getField('fundCode').getSelectedRecord().data['fund'] : ""));			
			IFDS.Xml.addSingleNode(xml, 'class', (addPopup.getField('fundCode').getSelectedRecord() ? addPopup.getField('fundCode').getSelectedRecord().data['class'] : "")) ;
		}
		else if (listBasedOn == "classCode")
		{
			IFDS.Xml.addSingleNode(xml, 'fundSponsor', addPopup.getField('fundSponsor').getValue());			
			IFDS.Xml.addSingleNode(xml, 'class', addPopup.getField('classCode').getValue());
		}
		else if (listBasedOn == "fundGroup")
		{					
			IFDS.Xml.addSingleNode(xml, 'fundGroup', addPopup.getField('fundGroup').getValue());
		}		 
		
		var ruleType = addPopup.getField('ruleType').getValue();	
		IFDS.Xml.addSingleNode(xml, 'ruleType', ruleType);
		var dataType = addPopup.getField('ruleType').getSelectedRecord().get('override');		

		if (dataType == 'overrideDec')
		{
			IFDS.Xml.addSingleNode(xml, 'overrideAmt', addPopup.getField('overrideAmt').getValue());
			IFDS.Xml.addSingleNode(xml, 'amountType', addPopup.getField('amountType').getValue());
						
			if (addPopup.getField('listBasedOn').getValue() == 'acctLevelOnly'
			 || addPopup.getField('listBasedOn').getValue() == 'BrkLevelOnly'){
			    IFDS.Xml.addSingleNode(xml, 'acctLevel', 'yes');
			}
			else {
			    IFDS.Xml.addSingleNode(xml, 'acctLevel', 'no');
			}
		}
		else if (dataType == 'overrideLog')
		 {
			//smartview treat acctLevel 3 value :- 1) ?  2) no 3) yes			
			/* Be careful when not sending acctLevel*/
			IFDS.Xml.addSingleNode(xml, 'overrideLog', addPopup.getField('overrideLog').getValue());
			
			//account level : 55,56,57,76,77,78
			//broker level  : 77,78			
			if (addPopup.getField('listBasedOn').hidden) /*58,60,80,81*/
				 IFDS.Xml.addSingleNode(xml, 'acctLevel', 'yes');
			else if (addPopup.getField('listBasedOn').getValue() == 'acctLevelOnly'||
			    addPopup.getField('listBasedOn').getValue() == 'BrkLevelOnly' )
			    IFDS.Xml.addSingleNode(xml, 'acctLevel', 'yes');
			else if (ruleType == '47' || ruleType == '84')
			    IFDS.Xml.addSingleNode(xml, 'acctLevel', (_self.IS_ACCOUNT_LEVEL ? 'yes' : 'no'));	//PSD Exemption							
			else			
			    IFDS.Xml.addSingleNode(xml, 'acctLevel', 'no');			
		}
		else
		{			
			if (_overrideCharList.indexOf(ruleType) >= 0)
			{
				IFDS.Xml.addSingleNode(xml, 'overrideChar', addPopup.getField('overrideChar').getValue());
				if (addPopup.getField('listBasedOn').getValue() == 'acctLevelOnly'
					|| addPopup.getField('listBasedOn').getValue() == 'BrkLevelOnly')
				{
					IFDS.Xml.addSingleNode(xml, 'acctLevel', 'yes');
				}
				else
				{
					IFDS.Xml.addSingleNode(xml, 'acctLevel', 'no');
				}
			}		
			else if (ruleType == '51') //listbaseon hidden
			{
				IFDS.Xml.addSingleNode(xml, 'acctLevel', 'yes');  //always use "yes" for KIID
				IFDS.Xml.addSingleNode(xml, 'fundGroup', addPopup.getField('fundGroup').getValue());
				IFDS.Xml.addSingleNode(xml, 'reasonCode', addPopup.getField('reason').getValue());
				IFDS.Xml.addSingleNode(xml, 'verifyStatus','02');//Always use 'Unverified' for KIID add mode
				if (_self.IS_ACCOUNT_LEVEL)
				{								    					
					IFDS.Xml.addSingleNode(xml, 'overrideChar', addPopup.getField('kiidAttested').getValue());									
				}
				else
				{										
					IFDS.Xml.addSingleNode(xml, 'overrideChar', addPopup.getField('responsibility').getValue());					
				}
			}
			else if (ruleType == '53')
			{				
				IFDS.Xml.addSingleNode(xml, 'overrideChar', addPopup.getField('rdrAdvice').getValue());
				IFDS.Xml.addSingleNode(xml, 'acctLevel', 'yes');				
			}
		}

		IFDS.Xml.addSingleNode(xml, 'onlineEWI', addPopup.getField('onlineEWI').getValue());
		IFDS.Xml.addSingleNode(xml, 'cycleEWI', addPopup.getField('cycleEWI').getValue());
		IFDS.Xml.addSingleNode(xml, 'esgEWI', addPopup.getField('esgEWI').getValue());		
		IFDS.Xml.addSingleNode(xml, 'excludeRule', addPopup.getField('excludeRule').getValue() ? 'yes' : 'no');
		IFDS.Xml.addSingleNode(xml, 'stopRule', addPopup.getField('stopRule').getValue() ? 'yes' : 'no');
		IFDS.Xml.addSingleNode(xml, 'assetLevel', addPopup.getField('assetLevel').getValue());
		IFDS.Xml.addSingleNode(xml, 'assetType', addPopup.getField('assetType').getValue());
		IFDS.Xml.addSingleNode(xml, 'currency', addPopup.getField('currency').getValue());
		
		DesktopWeb.Ajax.doSmartviewUpdate(_addLookupView, null, xml, responseHandler, _translationMap['ProcMsg_Searching']);
					
		function responseHandler(success, responseXML, contextErrors)
		{						
			_addLookupSuccess = success;
			if (success)
			{				
				_resources.grids['addRules'].loadData(responseXML, ['commitBtn']);
			}
			callbackFn(success);
		}			
	}

	function sendAddCommitRequest()
	{
		var addPopup = _resources.popups['add'];
		var xml = IFDS.Xml.newDocument("data");
		if (_self.IS_ACCOUNT_LEVEL)
		{
			IFDS.Xml.addSingleNode(xml, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
		}		
		else
		{
			IFDS.Xml.addSingleNode(xml, 'broker', _resources.fields['broker'].getValue());
			IFDS.Xml.addSingleNode(xml, 'branch', _resources.fields['branch'].getValue());
			IFDS.Xml.addSingleNode(xml, 'slsrep', _resources.fields['slsrep'].getValue());
		}
		
		var ruleType = addPopup.getField('ruleType').getValue();			
		IFDS.Xml.addSingleNode(xml, 'ruleType', ruleType);

		var assetLevel = addPopup.getField('assetLevel').getValue();
		var assetType = addPopup.getField('assetType').getValue();
		var currency = addPopup.getField('currency').getValue();
		var amountType = addPopup.getField('amountType').getValue();

		var pendingRulesXML = IFDS.Xml.addSingleNode(xml, 'PendingRules');

		_resources.grids['addRules'].getStore().each(function (record) {
		    record.data['AssetLevel'] = assetLevel;
		    record.data['AssetType'] = assetType;
		    record.data['Currency'] = currency;
		    record.data['AmountType'] = amountType;

		    buildRuleXML(record.data, pendingRulesXML);
		});

		DesktopWeb.Ajax.doSmartviewUpdate(_addCommitView, null, xml, responseHandler, null);
					
		function responseHandler(success, responseXML, contextErrors)
		{									
			if (success)
			{				
				if (IFDS.Xml.getNode(responseXML, '/*//RuleErrorList') != null)
				{
					_resources.grids['addRules'].loadData(IFDS.Xml.getNode(responseXML, '/*//RuleErrorList'));
				}
				else
				{		
					_resources.popups['add'].init();
				}
				_self.updatesFlag = true;
			}						
		}		
	}
	
	function sendModifyRequest(data)	
	{
		var modifySuccess = true;
		var xml = IFDS.Xml.newDocument("data");
		
		if (_self.IS_ACCOUNT_LEVEL)
		{
			IFDS.Xml.addSingleNode(xml, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
		}		
		else
		{
			IFDS.Xml.addSingleNode(xml, 'broker', _resources.fields['broker'].getValue());
			IFDS.Xml.addSingleNode(xml, 'branch', _resources.fields['branch'].getValue());
			IFDS.Xml.addSingleNode(xml, 'slsrep', _resources.fields['slsrep'].getValue());
		}
		
		IFDS.Xml.addSingleNode(xml, 'RuleType', data['RuleType']);
		
		var pendingRulesXML = IFDS.Xml.addSingleNode(xml, 'PendingRules');
		buildRuleXML(data, pendingRulesXML);		
				
		DesktopWeb.Ajax.doSmartviewUpdate(_modifyView, null, xml, responseHandler, null);
					
		function responseHandler(success, responseXML, contextErrors)
		{								
			if (success)
			{
				if (IFDS.Xml.getNodeValue(responseXML, '/*//RuleErrorList/tPendingRule/UpdateStatus') == 'Error')
				{
					DesktopWeb.Util.displayError(IFDS.Xml.getNodeValue(responseXML, '/*//RuleErrorList/tPendingRule/errorDesc'));
					modifySuccess = false;
				}
				else
				{
					//Display Information message whenever Verified record is modified on the same date as its effective date
					if (IFDS.Xml.getNodeValue(responseXML, '/*//RuleErrorList/tPendingRule/UpdateStatus') == 'Information')
					{
						DesktopWeb.Util.displayInfo(IFDS.Xml.getNodeValue(responseXML, '/*//RuleErrorList/tPendingRule/errorDesc'));
					}
					var data = buildRuleData(IFDS.Xml.getNode(responseXML, '/*//RuleErrorList/tPendingRule'));					
					_resources.grids['ovrdRules'].updateSelectedRecord(data);	
				}
				_self.updatesFlag = true												
			}						
		}
		
		return modifySuccess;			
	}
	
	function sendDeleteRequest(data)	
	{
		var deleteSuccess = true;
		var xml = IFDS.Xml.newDocument("data");
		if (_self.IS_ACCOUNT_LEVEL)
		{
			IFDS.Xml.addSingleNode(xml, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
		}		
		else
		{
			IFDS.Xml.addSingleNode(xml, 'broker', _resources.fields['broker'].getValue());
			IFDS.Xml.addSingleNode(xml, 'branch', _resources.fields['branch'].getValue());
			IFDS.Xml.addSingleNode(xml, 'slsrep', _resources.fields['slsrep'].getValue());
		}
		IFDS.Xml.addSingleNode(xml, 'RuleType', data['RuleType']);
		
		
		var pendingRulesXML = IFDS.Xml.addSingleNode(xml, 'PendingRules');
		
		
		buildRuleXML(data, pendingRulesXML);
		
		DesktopWeb.Ajax.doSmartviewUpdate(_deleteView, null, xml, responseHandler, null);
					
		function responseHandler(success, responseXML, contextErrors)
		{					
			if (success)
			{
				if (IFDS.Xml.getNodeValue(responseXML, '/*//RuleErrorList/tPendingRule/UpdateStatus') == 'Error')
				{
					DesktopWeb.Util.displayError(IFDS.Xml.getNodeValue(responseXML, '/*//RuleErrorList/tPendingRule/errorDesc'));
					deleteSuccess = false;
				}
				else
				{
					var index = _resources.grids['ovrdRules'].getSelectionModel().last;
					index = ( index == 0 ) ? 1 : index;
					_resources.grids['ovrdRules'].removeSelectedRecord();
					
					if (_resources.grids['ovrdRules'].getStore().getCount() >= index - 1 )
						_resources.grids['ovrdRules'].setSelectedRecord(index - 1 );
				}
				_self.updatesFlag = true;
			}		
		}
		
		return deleteSuccess;			
	}
	
	function sendStopRequest()
	{
		var stopSuccess = true;
		var xml = IFDS.Xml.newDocument("data");
		if (_self.IS_ACCOUNT_LEVEL)
		{
			IFDS.Xml.addSingleNode(xml, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
		}		
		else
		{
			IFDS.Xml.addSingleNode(xml, 'broker', _resources.fields['broker'].getValue());
			IFDS.Xml.addSingleNode(xml, 'branch', _resources.fields['branch'].getValue());
			IFDS.Xml.addSingleNode(xml, 'slsrep', _resources.fields['slsrep'].getValue());
		}
		
		var pendingRulesXML = IFDS.Xml.addSingleNode(xml, 'PendingRules');
		_resources.grids['ovrdRules'].getStore().each(function(record){buildRuleXML(record.data, pendingRulesXML);});
		
		DesktopWeb.Ajax.doSmartviewUpdate(_stopView, null, xml, responseHandler, null);
					
		function responseHandler(success, responseXML, contextErrors)
		{						
			if (success)
			{				
				if (IFDS.Xml.getNode(responseXML, '/*//RuleErrorList/*') != null)
				{
					_resources.grids['ovrdRules'].loadData(IFDS.Xml.getNode(responseXML, '/*//RuleErrorList'));
				}
				else
				{							
					sendReloadRequest(false);
				}
				_self.updatesFlag = true;
			}							
		}
	}
	
	
		
	function buildRuleXML(data, containerXML)
	{
		var ruleXML = IFDS.Xml.addSingleNode(containerXML, 'PendingRule');
		IFDS.Xml.addSingleNode(ruleXML, 'RuleType', data['RuleType']);
		IFDS.Xml.addSingleNode(ruleXML, 'Fund', data['Fund']);
		IFDS.Xml.addSingleNode(ruleXML, 'Class', data['Class']);
		IFDS.Xml.addSingleNode(ruleXML, 'FundGroup', data['FundGroup']);
		IFDS.Xml.addSingleNode(ruleXML, 'OverrideLog', data['OverrideLog']);
		IFDS.Xml.addSingleNode(ruleXML, 'OverrideAmt', data['OverrideAmt']);
		IFDS.Xml.addSingleNode(ruleXML, 'OverrideChar', data['OverrideChar']);
		IFDS.Xml.addSingleNode(ruleXML, 'OnlineEWI', data['OnlineEWI']);
		IFDS.Xml.addSingleNode(ruleXML, 'CycleEWI', data['CycleEWI']);
		IFDS.Xml.addSingleNode(ruleXML, 'ESGEWI', data['ESGEWI']);
		IFDS.Xml.addSingleNode(ruleXML, 'Version', data['Version']);
		IFDS.Xml.addSingleNode(ruleXML, 'ControlsID', data['ControlsID']);		 		
		IFDS.Xml.addSingleNode(ruleXML, 'StartDate', DesktopWeb.Util.getSMVDateValue(data['startDateChar']));
		IFDS.Xml.addSingleNode(ruleXML, 'StopDate', DesktopWeb.Util.getSMVDateValue(data['StopDate']));
		IFDS.Xml.addSingleNode(ruleXML, 'ReasonCode', data['reasonCode']);
		IFDS.Xml.addSingleNode(ruleXML, 'verifyStatus', data['verifyStatus']);
		IFDS.Xml.addSingleNode(ruleXML, 'AssetLevel', data['AssetLevel']);
		IFDS.Xml.addSingleNode(ruleXML, 'AssetType', data['AssetType']);
		IFDS.Xml.addSingleNode(ruleXML, 'Currency', data['Currency']);
		IFDS.Xml.addSingleNode(ruleXML, 'AmountType', data['AmountType']);
		}
	
	function buildRuleData(ruleXML)
	{
		var ruleFieldNodes = IFDS.Xml.getNodes(ruleXML, '*');
		var data = {};		
		for (var i = 0, l = ruleFieldNodes.length; i < l; i++)
		{
			data[ruleFieldNodes[i].nodeName] = IFDS.Xml.getNodeValue(ruleFieldNodes[i], '.');
		}
		data['ProcessDate'] = DesktopWeb.Util.getDateDisplayValue(data['ProcessDate']);
		data['ModDate'] = DesktopWeb.Util.getDateDisplayValue(data['ModDate']);
		data['StartDate'] = DesktopWeb.Util.getDateDisplayValue(data['StartDate']);
		data['startDateChar'] = DesktopWeb.Util.getDateDisplayValue(data['startDateChar']);
		data['StopDate'] = DesktopWeb.Util.getDateDisplayValue(data['StopDate']);
		data['stopDateChar'] = DesktopWeb.Util.getDateDisplayValue(data['stopDateChar']);
		return data;		
	}	

	function getSearchConditions(ruleType)
	{
		var ruleTypeLevel = null;
		if (_self.IS_ACCOUNT_LEVEL) {
			ruleTypeLevel = "FV" + ruleType;
		} else {
			ruleTypeLevel = "FZ" + ruleType;
		}
		if (_listMap['ValidationRuleList'] != null) {
			return IFDS.Xml.getNodeValue(_listMap['ValidationRuleList'], 'Element[code = "' + ruleTypeLevel + '"]/value');	
		} else {
			return null;
		}
	}
	
	function setListBasedOn(isFundGroup, ruleType) {
		var listBasedOn = '';
		
		if (_self.IS_ACCOUNT_LEVEL) {
			//SMS00088.P
			var accountFundlevel = _fundListBasedOnAccount.indexOf(ruleType) >= 0;
			if (isFundGroup) 
				listBasedOn = (accountFundlevel) ? 'FundListBasedOnAcctFundGrp' : 'FundListBasedOnFundGrp';
		  else
				listBasedOn = (accountFundlevel) ? 'FundListBasedOnAcct' : 'FundListBasedOn';
		}
		else {
			//SMS00096.P
			var brokerFundlevel = _fundListBasedOnBroker.indexOf(ruleType) >= 0;
			if (isFundGroup) 
				listBasedOn = (brokerFundlevel) ? 'FundListBasedOnBrokerfundGrp' : 'FundListBasedOnFundGrp';
		  else
				listBasedOn = (brokerFundlevel) ? 'FundListBasedOnBroker' : 'FundListBasedOn';
		}		
		
		return _listMap[listBasedOn];
	}
	
	function initScreen(res)
	{
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;			
		_self.IS_ACCOUNT_LEVEL = (DesktopWeb._SCREEN_PARAM_MAP['option'] == 'account');

		var view = "";
		var viewParamXML = IFDS.Xml.newDocument('data');
		
		if (_self.IS_ACCOUNT_LEVEL) 
		{
			handleAccountSetup();
			IFDS.Xml.addSingleNode(viewParamXML, 'searchType', 'account');
			IFDS.Xml.addSingleNode(viewParamXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			view = _accountInitView;
		}
		else
		{
			handleBrokerSetupScreen();
			IFDS.Xml.addSingleNode(viewParamXML, 'searchType', 'broker');
			view = _brokerInitView;
		}
		DesktopWeb.Ajax.doSmartviewAjax(view, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Loading']);
					
		function responseHandler(success, responseXML)
		{		
			if (success)
			{  
				if (_self.IS_ACCOUNT_LEVEL) 
				{
					populateAccount(responseXML);	
				}					
				loadDropdowns(responseXML);
				storeDefaultValues(responseXML);
			    // Load permission
				storePermissions(responseXML);//added for CHG0043739
				_resources.fields['ruleType'].setValue('ALL');
				_self.IS_PERSISTENT = IFDS.Xml.getNodeValue(responseXML, '//uCITSModel') == 'P';
				checkPermissions(false);//added for CHG0043739
				_initResponseXml = responseXML;
			}
		}
	}

	function handleRuleTypeSrchChange()
	{
		_resources.fields['broker'].reset();
		_resources.fields['branch'].reset();
		_resources.fields['branch'].disable();
		_resources.fields['slsrep'].reset();
		_resources.fields['slsrep'].disable();
		
		//For rule - 60 (Rounding Rule), fields below are not required
		if (_resources.fields['ruleType'].getValue() == '60') {
			_resources.fields['fundSponsor'].disable();
			_resources.fields['fund'].disable();
			_resources.fields['classCode'].disable();
			_resources.fields['fundGroup'].disable();
			_resources.fields['showOnlyActiveRecords'].disable();
		} else {
			_resources.fields['fundSponsor'].enable();
			_resources.fields['fund'].enable();
			_resources.fields['classCode'].enable();
			_resources.fields['fundGroup'].enable();
			_resources.fields['showOnlyActiveRecords'].enable();
		}
		
		// KIID, CPF, RDR, Rollover are not require branch/rep
		if (_brrpCanBlk.indexOf(_resources.fields['ruleType'].getValue()) + 1 > 0 
			|| getSearchConditions(_resources.fields['ruleType'].getValue()) == BROKERONLY
			)
		{		
			_resources.fields['branch'].allowBlank = true;
			_resources.fields['slsrep'].allowBlank = true;
		}	
		else if (getSearchConditions(_resources.fields['ruleType'].getValue() == BROKERBRANCHONLY))
		{
			_resources.fields['branch'].allowBlank = false;
			_resources.fields['slsrep'].allowBlank = true;
		}
		else
		{				
			_resources.fields['branch'].allowBlank = false;
			_resources.fields['slsrep'].allowBlank = false;
		}
		verifyAndLoadFundGroups(_resources.fields['ruleType'].getValue(), '');
	}
	
	function doResetSearch()
	{
		_resources.fields['ruleType'].enable();
		_resources.fields['ruleType'].setValue('ALL');

		_resources.fields['broker'].enable();
		_resources.fields['broker'].reset();
		
		_resources.fields['branch'].reset();
		
		_resources.fields['slsrep'].reset();			
		
		_resources.fields['fundSponsor'].enable(); 
		_resources.fields['fundSponsor'].reset();
		
		_resources.fields['fund'].enable();
		_resources.fields['fund'].reset();
		
		_resources.fields['fundGroup'].enable(); 
		_resources.fields['fundGroup'].reset();
		
		_resources.fields['classCode'].enable();
		_resources.fields['classCode'].reset();
		
		_resources.fields['showOnlyActiveRecords'].enable();
		_resources.fields['showOnlyActiveRecords'].setValue(false);
					
		Ext.getCmp('searchBtn').enable();
		Ext.getCmp('resetBtn').disable();
		
		_resources.grids['ovrdRules'].clearData();			
		 checkPermissions(false); //Added for CHG0043739
	}
	
	/*Search */  
	function allowSearch()
	{
		var allow = false;		
		if (_self.IS_ACCOUNT_LEVEL) {
			allow = _resources.fields['ruleType'].isValid();
		}
		else {
			// broker is required for all rules, 
			// branch/rep not required for KIID(51) or CPF(52)
			// rep not required for Stop Purchase (03), Stop Redemption(04), Stop Transfer IN(05), Stop Transfer OUT(06)
			// User is able to search with only broker.
			allow = (_resources.fields['ruleType'].isValid() && _resources.fields['broker'].isValid()
								&& (_resources.fields['ruleType'].getValue() == 'ALL' 
											|| (_resources.fields['branch'].isValid()
											&& _resources.fields['slsrep'].isValid())
									));			
		}
		return allow;
	}	
	function verifyAndLoadFundGroups(ruleType, action) {	
		//initialization
		if (action == _self.ADD) {
			_resources.popups['add'].getField('fundGroup').getStore().removeAll();
			_resources.popups['add'].getField('fundGroup').setValue('');
		} else {
			_resources.fields['fundGroup'].getStore().removeAll();
			_resources.fields['fundGroup'].setValue('');
		}
		
		var fundGroupListNodes = IFDS.Xml.getNodes(_initResponseXml, "//List[@listName='FundGroupList']/Element[rulecode='" + ruleType + "']");
		

		var fundGroupDropdownListXml = IFDS.Xml.newDocument('List');
		if(fundGroupListNodes.length != 0) {		
			Ext.each(fundGroupListNodes, function(fundGroupListNodes){
				IFDS.Xml.appendNode(fundGroupDropdownListXml, IFDS.Xml.cloneDocument(fundGroupListNodes));
			})
			if (action == _self.ADD) {
				_resources.popups['add'].getField('fundGroup').getStore().loadData(fundGroupDropdownListXml);
			} else {
				_resources.fields['fundGroup'].getStore().loadData(fundGroupDropdownListXml);
			}
			return true;
		}
		else {
			return false;
		}
	}
	//Checking permission
	//Modified below method for CHG0043739. This method is called if there is data in the grid to display.
	function updateActionButtons()
	{
		var selectedRecord = _resources.grids['ovrdRules'].getSelectedRecord();	
		
		if (selectedRecord)
		{
		  checkPermissions(true); //Added for CHG0043739
			
			//Disable modify button if modEnable is no
			var isModifyEnabled = selectedRecord.data['modEnable'].toLowerCase();			
			if((_resources.fields['ruleType'].getValue() == '51' || _resources.fields['ruleType'].getValue().toLowerCase() == 'all') && isModifyEnabled=='no')
			{
				_resources.grids['ovrdRules'].disableButton('modBtn');
			}
		}
		else
		    checkPermissions(false); //Added for CHG0043739
		
		//Disable 'add' button if it has an existing unverified record.
		if(_resources.fields['ruleType'].getValue() == '51')
		{
			var allRecs = _resources.grids['ovrdRules'].getAllRecords();
			var firstRec = allRecs[0];//Assuming Unverified record if present will always be the first..
			var verStatus = firstRec.data['verifyStatus'];
			if(verStatus=='02')
			{
				_resources.grids['ovrdRules'].disableButton('addBtn');
			}
		}
	}
	
	/*Popup */
	function openActionPopup(action) {
		if (action == _self.ADD) {
			if (allowAdd()) {
				_resources.popups['add'].show();
			}
		}
		else if (action == _self.MOD) {
			_resources.popups['modify'].show();
		}
		else if (action == _self.DEL) {
			_resources.popups['del'].show();
		}
	}
	
	/*Initial Screen */    
	function handleGridColumnsChange(isBrokerRule) 
	{
		if (isBrokerRule) {
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('account'), true);
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('broker'), false);
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('branch'), false);
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('slsrep'), false);
		} else {
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('account'), false);
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('broker'), true);
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('branch'), true);
			_resources.grids['addRules'].colModel.setHidden(_resources.grids['addRules'].colModel.findColumnIndex('slsrep'), true);
		}				
					
	}
		
	// Dynamic show/hide Broker/Branch/Rep or Account info in popUps*****************  
	function handlePopup(isBrokerRule) {    
		var popName = ['add', 'del', 'modify', 'details'];
		
		for (var iMode = 0; iMode < popName.length ; iMode++) {			
			var popup = _resources.popups[popName[iMode]];
			if (isBrokerRule) {
				if (popup.getField('accountNum')) popup.getField('accountNum').hide();
				if (popup.getField('broker')) popup.getField('broker').show();
				if (popup.getField('branch')) popup.getField('branch').show();
				if (popup.getField('slsrep')) popup.getField('slsrep').show();
				if (popup.getField('rdrAdvice'))
					popup.getField('rdrAdvice').setFieldLabel(_translationMap['RDRApplicable']);
			} else {				
				if (popup.getField('accountNum')) popup.getField('accountNum').show();
				if (popup.getField('broker')) popup.getField('broker').hide();
				if (popup.getField('branch')) popup.getField('branch').hide();
				if (popup.getField('slsrep')) popup.getField('slsrep').hide();
				if (popup.getField('rdrAdvice'))
					popup.getField('rdrAdvice').setFieldLabel(_translationMap['RDRAdvice']);
			}      
		}    
	}
		
		
	function handleAccountSetup() {
		//Inquiry Screen
		_resources.fields['accountNum'].show();
		_resources.fields['broker'].hide();
		_resources.fields['branch'].hide();
		_resources.fields['slsrep'].hide();
		_resources.grids['ovrdRules'].setHeight(400);
		handleGridColumnsChange(false);
		handlePopup(false);
	}
	
	function handleBrokerSetupScreen() {
		_resources.fields['accountNum'].hide();
		_resources.fields['broker'].show();
		_resources.fields['branch'].show();
		_resources.fields['slsrep'].show();
		_resources.grids['ovrdRules'].setHeight(330);
		handleGridColumnsChange(true);
		handlePopup(true);    
	}
	
	
	/*Add popup*/
	//Disable EWI fields based on ruletype
	function handleEWIForRule(ruleType, popUp) {
		if (ruleType == '60' ) {
			popUp.getField('onlineEWI').disable();
			popUp.getField('cycleEWI').disable();	
			popUp.getField('esgEWI').disable();
		} else {
			popUp.getField('onlineEWI').enable();
			popUp.getField('cycleEWI').enable();	
			popUp.getField('esgEWI').enable();
		}		
	} 

	// Set override logic as yes and diable it for non-edit
	function handleOverrideLogFieldForRule(ruleType, popUp) {
		
		if (( _self.IS_ACCOUNT_LEVEL && _hiddenListBasedOnAcct.indexOf(ruleType) >= 0) ||
				(!_self.IS_ACCOUNT_LEVEL && _hiddenListBasedOnBRK.indexOf(ruleType) >= 0 )) {
			popUp.getField('overrideLog').setValue('yes');
			popUp.getField('overrideLog').disable();
		} else {	
			popUp.getField('overrideLog').enable();
		}
	}

	function populateListByRuleType(popup, listName, fieldName) {
		popup.getField(fieldName).hide();
		if (_listMap[listName] != null && _listMap[listName] != undefined) {
	  	popup.getField(fieldName).loadData(_listMap[listName]);
	  	if (popup.getField(fieldName).store.getCount() > 0) {
	  		popup.getField(fieldName).show();
	  		popup.getField(fieldName).enable();
	  	}
	  }
	} /*populateListByRuleType*/
	
	
	function handleAddRuleTypeChange()
	{			
		var addPopup = _resources.popups['add'];
		var ruleType = addPopup.getField('ruleType').getValue();

		var affectedFields = ['listBasedOn', 'fundGroup', 'overrideAmt', 'overrideLog', 'overrideChar', 
		'eligible', 'responsibility', 'kiidAttested', 'reason','rdrAdvice', 'amountType', 'currency', 'assetLevel', 'assetType'];
		
		var fundGrpFlag = verifyAndLoadFundGroups(ruleType, this.ADD);
			
		for (var i = 0; i < affectedFields.length; i++)
		{				
			addPopup.getField(affectedFields[i]).reset();
			addPopup.getField(affectedFields[i]).hide();
		}

		if (ruleType != '')
		{
			populateListByRuleType(addPopup, "AssetLevelList" + ruleType, 'assetLevel');
			populateListByRuleType(addPopup, "AssetTypeList" + ruleType, 'assetType');
			populateListByRuleType(addPopup, "AmountTypeList" + ruleType, 'amountType');
			
			if (addPopup.getField('amountType').store.getCount() > 1) {
				addPopup.getField('amountType').setValue(getDefaultValue('amountType'));
			} else if (addPopup.getField('amountType').store.getCount() == 1) {
				addPopup.getField('amountType').setValue(addPopup.getField('amountType').store.getAt(0).get('code'));
				addPopup.getField('amountType').disable();
				}
	        
			var ruleTypeCurrency = addPopup.getField('ruleType').getSelectedRecord().get('currency');
							
				if (ruleTypeCurrency != null && ruleTypeCurrency != undefined 
					&& ruleTypeCurrency.toLowerCase() == 'yes') {
				addPopup.getField('currency').show();
			}
			 
			var dataType = addPopup.getField('ruleType').getSelectedRecord().get('override');
			if (dataType == 'overrideDec')
			{
				addPopup.getField('listBasedOn').show();
				addPopup.getField('overrideAmt').show();
				addPopup.getField('verifystatus').hide();
				
				addPopup.getField('listBasedOn').loadData(setListBasedOn(fundGrpFlag, ruleType));
			}
			else if (dataType == 'overrideLog')
			{
				addPopup.getField('listBasedOn').show();
				addPopup.getField('overrideLog').show();
				addPopup.getField('verifystatus').hide();
				
				if (( _self.IS_ACCOUNT_LEVEL && _hiddenListBasedOnAcct.indexOf(ruleType) >= 0) || 
					  (!_self.IS_ACCOUNT_LEVEL && _hiddenListBasedOnBRK.indexOf(ruleType) >= 0 ))
					addPopup.getField('listBasedOn').hide();
				else 
					addPopup.getField('listBasedOn').loadData(setListBasedOn(fundGrpFlag, ruleType));
				
				handleOverrideLogFieldForRule(ruleType, addPopup);
				//Disable radio buttons fields only for the rule
				if ( ruleType == '60') {
					addPopup.getField('radioLabel').disable();
					addPopup.getField('excludeRule').disable();
					addPopup.getField('stopRule').disable();
				} else {
					addPopup.getField('radioLabel').enable();
					addPopup.getField('excludeRule').enable();
					addPopup.getField('stopRule').enable();
				}
							
			}
			else if (dataType == 'overrideChar')
			{
				// overrideChar rules are the complicated ones
				// Rule Type 30 is Default Subscription Pay Type.
				// Rule Type 46 is US Cost Basis
				// Rule Type 83 is Unit Calculation
				if (_overrideCharList.indexOf(ruleType) >= 0)
				{
					if (_self.IS_ACCOUNT_LEVEL)
					addPopup.getField('listBasedOn').loadData(_listMap['FundListBasedOnAcct']);
					else
						addPopup.getField('listBasedOn').loadData(_listMap['FundListBasedOnBroker']);
					
					addPopup.getField('listBasedOn').show();					
					addPopup.getField('overrideChar').loadData(_listMap['OverrideListRule' + ruleType]);
					addPopup.getField('overrideChar').show();											
				}

				// KIID rule
				else if (ruleType == '51') // KIID Attestation Rule
				{	
					addPopup.getField('verifystatus').show();			
					addPopup.getField('fundGroup').show();
					if (_self.IS_ACCOUNT_LEVEL)
					{						
						if (!_self.IS_PERSISTENT)
						{
							addPopup.getField('listBasedOn').loadData(_listMap['FundListBasedOn']);					
							addPopup.getField('listBasedOn').show();
						}
						addPopup.getField('kiidAttested').show();
					}
					else
					{						
						addPopup.getField('responsibility').show();
						handleResponsibilityChange(_resources.popups['add']);
						
					}					
				}
				else if (ruleType == '53') // Retail Distribution Review Rule
				{					
					addPopup.getField('rdrAdvice').show();
				}
				
			}
			
			//Handle EWI combo when rule change.
			handleEWIForRule(ruleType, addPopup);
	  } /*if (ruleType != '')*/

		handleAddListBasedOnChange();
	}

	function handleAddListBasedOnChange() {
	 // listBaseOn field is enabled when ruleType is populated.
		var addPopup = _resources.popups['add'];
		var listBasedOn = addPopup.getField('listBasedOn').getValue();
		var ruleType = addPopup.getField('ruleType').getValue();

		var conditionalFields = ['fundSponsor', 'fundCode', 'classCode'];
		if (ruleType != '51')
		 {
			conditionalFields.push('fundGroup');
		}
		else
			addPopup.getField('fundGroup').reset();

		for (var i = 0; i < conditionalFields.length; i++) 
		{
			addPopup.getField(conditionalFields[i]).reset();
			addPopup.getField(conditionalFields[i]).hide();
		}
		/*listBasedOn : fundSponsor,fundCode,classCode,fundGroup */
		if (addPopup.getField(listBasedOn))
			addPopup.getField(listBasedOn).show();
		

		if (_self.IS_ACCOUNT_LEVEL && ruleType == '51')
		 { 
			addPopup.getField('verifystatus').show();
			if (_self.IS_PERSISTENT)
			{
				addPopup.getField('kiidAttested').loadData(_listMap['KIIDComboList']);
			}
			else
			{
				if (listBasedOn == 'fundCode' || listBasedOn == 'classCode') 
				{
					addPopup.getField('kiidAttested').loadData(_listMap['KIIDAttestationList']);
				}
				else
				{
					addPopup.getField('kiidAttested').loadData(_listMap['KIIDWaiverList']);
				}
			}
			addPopup.getField('kiidAttested').reset();
		}
	}

	//Rule type 51 broker level
	function handleResponsibilityChange(popup)
	{			
		var responsibilityFld = popup.getField('responsibility');

		if (responsibilityFld.isVisible())
		{				
			if (responsibilityFld.getValue() == 'R')
			{
				popup.getField('reason').loadData(_listMap['KIIDResponsibleBrkList']);
				popup.getField('reason').enable();
			}
			else if (responsibilityFld.getValue() == 'U')
			{
				popup.getField('reason').loadData(_listMap['KIIDResponsibleNonBrkList']);
				popup.getField('reason').enable();
			}
			else 
			{
				popup.getField('reason').disable();				
			}
			popup.getField('reason').reset();	
			popup.getField('reason').show();	
		}			
		else 
		{
			popup.getField('reason').hide();
		}
	}

	function getRuleDataType(ruleType){
		return IFDS.Xml.getAttributeValue(_listMap['RuleTypeOptions'], 'Element[code = "' + ruleType + '"]/code/@override');	
	}

	 // List Desc
	function getListDesc(listName, value){
		if (!!_listMap[listName])
			return IFDS.Xml.getNodeValue(_listMap[listName], 'Element[code = "' + value + '"]/value');
						
		return '';
	}
	
	function isEnabledCurrency(ruleType){
		var currency = IFDS.Xml.getNodeValue(_listMap['RuleTypeOptions'], 'Element[code = "' + ruleType + '"]/currency');
		return (currency == null || currency == undefined) ? false : currency.toLowerCase() == 'yes';
	}

	function getDefaultValue(fld) {
		return _defaultValues[fld];
	}	

	//Function to compare the current record and modified record,send appropriate verifystatus value
	function getVerifyStatus(oldOvrChar,oldReasonCode,newRec,verifyStatusVal)
	{
		var returnVal='02';//Set default as Unverified

		if((oldOvrChar== newRec.data['OverrideChar']) && (oldReasonCode== newRec.data['reasonCode']))
		{
			if(newRec.data['sameUser']=='N')
			{
				returnVal = verifyStatusVal;//If different user and KIID specific data is not modified then verifyStatus is as per user selection
			}
		}
		return returnVal;
	}
	
	function renderOverrideValue(value, metaData, record)
	{
		var ruleType = record.data['RuleType'];
		var dataType = getRuleDataType(ruleType);

		if (dataType == 'overrideLog')
		{
			return record.data['OverrideLog'];	
		}
		else if (dataType == 'overrideDec')
		{
			return record.data['dispAmt'];
		}
		else if (dataType == 'overrideChar')
		{
			return record.data['OverrideChar'];
		}
		else
		{
			throw new Error("RenderOverrideValue - unknown rule data type");
		}
	}
		
	//List object
	function getList(name){
		return _listMap[name];
	}
	
	/*Handle Grid value*/
	function renderUpdateStatus(value, metaData, record){
		if (record.data['UpdateStatus'].toLowerCase() == 'error')	
		{				
			return DesktopWeb.Util.buildErrorFlag(record.data['errorDesc']); 
		}
		else
		{
			return "";
		}			
	}
	
	/*StopLimitations*/
	function doStopLimitations()
	{			
		Ext.Msg.confirm(_translationMap['OverrideLimitationRules'] + " - " + _translationMap['Stop'],
						 _translationMap['StopConfirm'],
						 responseHandler);
		
		function responseHandler(btn)
		{
			if (btn == 'yes')
			{
				sendStopRequest();
			}
		}
	}//doStopLimitations
	
		/*Admin*/
	function openAdminPopup()	{
		_resources.popups['admin'].init();
		_resources.popups['admin'].show();
	}
	
	/*Detail */
	function openDetailsPopup() {
		_resources.popups['details'].init();
		_resources.popups['details'].show();
	}
	
	/*Add mode */
	function doAddLookup()    
	{
		sendAddLookupRequest(callback);
		
		function callback(success)
		{
			if (success)
			{
				_resources.popups['add'].disableAllFields();
				Ext.getCmp('lookupBtn').disable();
				Ext.getCmp('resetLookupBtn').enable();
			}
		}
	}
	
	
	function doUpdate(action, data)
	{
		if (action == this.MOD)
		{
			if (data['RuleType'] == '52' && (data['OverrideAmt'] != "1.00"
				&& data['OverrideAmt']!= "0.00" ) ) {

					alert("Override value needs to be 1(Yes) or 0 (No).");

			} else {
				return sendModifyRequest(data);
			}
		}
		else if (action == this.DEL)
		{
			return sendDeleteRequest(data);
		}			
	}
	
	/*History */
	function openHistoryPopup() {
	  var viewParam = {};
	  var historyName = null;
	  var selectedRecord = _resources.grids['ovrdRules'].getSelectedRecord();
	  
	  if (selectedRecord && selectedRecord != undefined) {
	    historyName = _translationMap["OverrideLimitationRule"] + ' - '
			 + _translationMap['History'];

		viewParam['auditType'] =  (_self.IS_ACCOUNT_LEVEL) ? 'AcctControls' : 'BrokerageControls';	    
			viewParam['searchValue1'] = selectedRecord.data['ControlsID'];	    
		_resources.popups['history'].init(historyName, _historicalInfo,viewParam, true);
	    _resources.popups['history'].show();
	  }
	}
	
	
	 
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		,DETAILS: 'details'
		,IS_ACCOUNT_LEVEL: null	
		,IS_PERSISTENT : null
		,updatesFlag: false
		,init: initScreen
		//search functionality
		,handleRuleTypeSrchChange: handleRuleTypeSrchChange
		,doReset: doResetSearch
		,allowSearch: allowSearch
		,doReload: sendReloadRequest
		,updateActionButtons: updateActionButtons
		//Add mod delete
		,openActionPopup: openActionPopup
		//Disable EWI fields based on ruletype
		,handleEWIForRule:  handleEWIForRule
		// Set override logic as yes and diable it for non-edit***********
		,setOverrideLogFieldForRule:  handleOverrideLogFieldForRule 
		,setListByRuleType: populateListByRuleType
		,handleAddRuleTypeChange: handleAddRuleTypeChange
		,handleAddListBasedOnChange: handleAddListBasedOnChange
		//ruleType 51 and broker level for add and mod mode
		,handleResponsibilityChange: handleResponsibilityChange
		,getRuleDataType: getRuleDataType 
		,getListDesc: getListDesc
		,isEnabledCurrency:isEnabledCurrency
		//Function to compare the current record and modified record,send appropriate verifystatus value
		,getVerifyStatus: getVerifyStatus
		,getDefaultValue: getDefaultValue
		,renderOverrideValue: renderOverrideValue
		,getList: getList
		,renderUpdateStatus: renderUpdateStatus
		,doStopLimitations: doStopLimitations
		,openAdminPopup: openAdminPopup  
		,openHistoryPopup: openHistoryPopup
		,openDetailsPopup: openDetailsPopup
		,doAddLookup: doAddLookup
		,doAddCommit: sendAddCommitRequest
		,doUpdate: doUpdate
		,overrideCharList: _overrideCharList
		
	}	
}	