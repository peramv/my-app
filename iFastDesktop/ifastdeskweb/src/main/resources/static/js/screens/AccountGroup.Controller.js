/*********************************************************************************************
 * @file	AccountGroup.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Account Group screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Account Group
 *				
 *  History : 
 *
 *  23 Jul 2014 Narin S. P0233553 T55642
 *					- Created.
 *
 *  03 Sept 2014 Narin S. P0233553 T55678
 *					- Add validation for account group and linked account.
 *
 *  18 Sept 2014 Narin S. P0233553 DFT0041280 T55739
 *					- Always enable search value field.
 *
 *  03 Oct 2014 Narin S. P0233553 DFT0041998 DFT0042095 T55805
 *					- Sent all associated modified accounts to validation service. 
 *						They are required for stopping account group and linked account validation
 *					- Disable modify button for both account group and linked account 
 *						when they have been stopped
 *
 *  09 Oct 2014 Narin S. P0233553 DFT0042444 T55852
 *					- Search For field is mandatory field if Search Value is not blank.
 *
 *  16 Oct 2014 Narin S. P0233553 DFT0042580 T55888
 *					- Fixed displaying Group ID field on Account Group popup when AutoGrpID is no.
 *					- Change LinkedAccts tag name to LnkAccts
 *
 *	28 Oct 2014 Narin S. P0233553 DFT0043383 T55939
 *					- Support Account Level
 *
 *	17 Nov 2014 Narin S. P0233553 DFT0044183 T55983
 *					- Fixed the change is lost if user selects other account group.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.
 *
 *  23 Sep. 2016 Winnie Cheng. P0256381 T83741 CHG0045765 Fund Broker Linkage for Germany
 *					- modify.
 *
 *  13 Oct 2016 Winnie Cheng. P0256381  T83939 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, imp. Delete error handing and bug fixing
 *
 *  20 Oct 2016 Winnie Cheng. P0256381  T84056 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, imp. Delete error handing for account and bug fixing for other grouptypes
 *                  - Adding duplication validation in popUp stage
 *
 *  28 Oct 2016 Winnie Cheng. P0256381  T84097 DFT0068689 CHG0045765 Fund Broker Linkage for Germany
 *                  - utilize 'ACBRLK', remove recussive populate otherReference number
 *
 *  8 Nov 2016 Winnie Cheng. P0256381  T84187 DFT0069088 CHG0045765 Fund Broker Linkage for Germany
 *                  - remove additional popUp
 *
 *  17 Nov 2016 Winnie Cheng. P0256381  T84279 DFT0069397 CHG0045765 Fund Broker Linkage for Germany
 *                  - disable modify button for inactive account Grp
 *
 *  09 Feb 2017 Winnie Cheng. P0256381  T84847 INC0033305 CHG0048848  Account Group
 *                  - do not reset "Search for" fields if accessing this screen from C++ link
 *                  
 *  25 oct 2017 Sreejith A. P0266789-1212 Desktop changes for Account Linkage
 *  		    	- Delete button enable by config
 *  				- Group id and Description field max length setting from config
 *  		   	 	- Desc field made available in linkage popup for CRMREL group
 *  				- Other config changes for CRMREL group
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'add';
	var _MOD = 'mod';
	var _DEL = 'del';
	var _INQ = 'inq';
	var _ACC = 'acc';
	var _LINKAGEERRORCODE = '1664';
	var _LINKAGEERRORCODEDEL = '504';
	
	var _initXML = null;
	var _acctGrpXML = null;
	var _updateXML = null;
	
    var _nextStartRecNum = 1;
	var _requestRecNum = 25;
	var _requestRecNumDetl = 25;
	
	var _nextUUID = 1;
	
	var _currentSearch	= new Array();
	var _permissions	= new Array();
	var _defaultValues	= new Array();
	var _configs		= new Array();

	var _dtAcctGrpInqService = "dtAcctGrpInq";
	var _dtAcctGrpProcService = "dtAcctGrpProc";
	var _dtAcctGrpValService = "dtAcctGrpVal";
	var _dtHistoryService = 'dtHistoricalInfo';
	
	var _searchedFlag = false;

	var _showOtherRefNumColumn = 7;
	var _AFTACCTGRPTYPE = 'ACBRLK';

	// PRIVATE METHODS ****************************************	
	/** Store user permission **/
	function storePermissions(initViewXML)
	{
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function loadDefaultValues(responseXML)
	{
		var defaultValuesNode = IFDS.Xml.getNode(responseXML, "//DefaultValues");

		if (defaultValuesNode)
		{
			_defaultValues['curBusDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'curBusDate'));
			_defaultValues['nextBusDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'nextBusDate'));
			_defaultValues['primaryAcct'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'primaryAcct'));
		}
		
		var defaultStopDate = new Date();
		defaultStopDate.setYear(9999);
		defaultStopDate.setMonth(11);
		defaultStopDate.setDate(31);
		
		_defaultValues['stopDate'] = DesktopWeb.Util.getDateString(defaultStopDate, DesktopWeb.Util.getDateDisplayFormat());
	}

	function loadConfigurations(initViewXML)
	{
		_configs['salesRepbyBranch'] = IFDS.Xml.getNodeValue(initViewXML, '//salesRepbyBranch').toLowerCase() == _self.YES;
		_configs['autoGrpId'] = IFDS.Xml.getNodeValue(initViewXML, '//autoGrpID').toLowerCase() == _self.YES;
		//For Germany account group
		_configs['groupType'] = IFDS.Xml.getNodeValue(initViewXML, '//GroupTypes/GroupType/@groupType');
	}
	
	function loadRequestRecNums(grpType) {
		//For Germany, AcctGrp grid records are set up to 100, can be reConfig from the table
		if (_self.getConfig(grpType, "RequestRecNum") != null) {
			_requestRecNum = _self.getConfig(grpType, "RequestRecNum");
		} else {
			_requestRecNum = 25;
		} 
		//For Germany, Linke Account grid records are set up to 100, , can be reConfig from the table
		if (_self.getConfig(grpType, "ReqRecNumDetl") != null) {
			_requestRecNumDetl = _self.getConfig(_configs['groupType'], "ReqRecNumDetl");
		} else {
			_requestRecNumDetl = 25;
		}
	}
	
	function populateDropdownList()
	{
		try{
			_resources.fields['grpType'].loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'GroupTypeList']"));
			_resources.fields['searchFor'].loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'AcctGrpSrchList']"));
			_resources.popups['acctGrpPopup'].getField('grpType').loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'GroupTypeList']"));
			_resources.popups['acctGrpPopup'].getField('grpStat').loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'GroupStatusList']"));
			_resources.popups['linkedAcctPopup'].getField('grpType').loadData(IFDS.Xml.getNode(_initXML, "//List[@listName = 'GroupTypeList']"));
			
			defaultDropdowns(_configs['groupType']);
		}catch(err){
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
		}
	}
	
	function populateDefaultSearchCriteria(initViewXML)
	{
		// For Account Level
		var acctNum = DesktopWeb._SCREEN_PARAM_MAP['AccountNum']
		if (acctNum && acctNum.length > 0)
		{
			_resources.fields['searchFor'].setValue('Acct');
			_resources.fields['searchValue'].setValue(acctNum);
			_resources.fields['searchFor'].disableField();
			_resources.fields['searchValue'].disableField();
		}
	}

	function doSearch(runMode, append)
	{
		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(dataXML, 'grpStat', _currentSearch['grpStat']);
		IFDS.Xml.addSingleNode(dataXML, 'acctStat', _currentSearch['acctStat']);
		
		var requestRecNum = _requestRecNum;
		var startRecNum = _nextStartRecNum;
		if (runMode == 'reloadDetl')
		{
			var selectedRecord = _resources.grids['acctGrp'].getSelectedRecord();
			
			requestRecNum = _requestRecNumDetl;
			startRecNum = selectedRecord.data['nextStartRecordNumLinkedAcct'];
			
			IFDS.Xml.addSingleNode(dataXML, 'grpType', _currentSearch['grpType']);
			IFDS.Xml.addSingleNode(dataXML, 'grpId', selectedRecord.data['grpId']);
			
		}else{
			IFDS.Xml.addSingleNode(dataXML, 'grpType', _currentSearch['grpType']);
			IFDS.Xml.addSingleNode(dataXML, 'searchFor', _currentSearch['searchFor']);
			IFDS.Xml.addSingleNode(dataXML, 'searchValue', _currentSearch['searchValue']);
		}
		
		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?startRecNum:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', requestRecNum);

		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_dtAcctGrpInqService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{
			_searchedFlag = true;
			// hanldle response
			if (success){
			
				var acctGrpNode = IFDS.Xml.getNode(responseXML, '//AcctGrps/AcctGrp');
				if (acctGrpNode)
				{
					if (runMode == 'reloadDetl') // Linked Accounts
					{
						var newLinkedAcctXml = IFDS.Xml.getNode(responseXML, '//LnkAccts/LnkAcct');
						if (newLinkedAcctXml)
						{
							var newLinkedAcctsXml = IFDS.Xml.getNode(responseXML, '//LnkAccts');
							if (append)
							{
								var linkedAcctXml = IFDS.Xml.stringToXML(selectedRecord.data['LnkAccts']);
								
								// Store new xml to grid data
								IFDS.Xml.appendNode(linkedAcctXml, IFDS.Xml.cloneDocument(newLinkedAcctsXml));
								selectedRecord.data['LnkAccts'] = IFDS.Xml.serialize(linkedAcctXml);
								
								// Append data to grid
								_resources.grids['linkedAcct'].appendData(newLinkedAcctsXml);
							}else{
								selectedRecord.data['LnkAccts'] = IFDS.Xml.serialize(newLinkedAcctsXml);
								_resources.grids['linkedAcct'].loadData(newLinkedAcctsXml);
							}
							
							// control more button
							var nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
							if (nextStartRecNum)
							{
								selectedRecord.data['hasMoreLinkedAccts'] = 'yes';
								selectedRecord.data['nextStartRecordNumLinkedAcct'] = nextStartRecNum;
								_resources.grids['linkedAcct'].enableButton('moreBtn');
							}
							else
							{
								selectedRecord.data['hasMoreLinkedAccts'] = 'no';
								_resources.grids['linkedAcct'].disableButton('moreBtn');
							}
						}else{
							// Handle if there is no linked-acct in selected group
							updateLinkedAcctGridButtons(null);
						}
					}else{ // Account Group
						if (append)
						{
							_resources.grids['acctGrp'].appendData(IFDS.Xml.getNode(responseXML, '//AcctGrps'));
							
						}else{
							_resources.grids['acctGrp'].loadData(IFDS.Xml.getNode(responseXML, '//AcctGrps'));
						}
						
						_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
						if (_nextStartRecNum)
						{
							_resources.grids['acctGrp'].enableButton('moreBtn');
						}
						else
						{
							_resources.grids['acctGrp'].disableButton('moreBtn');
						}
					}
				}else{
					if (runMode == 'reloadDetl')
					{
						updateLinkedAcctGridButtons(null);
					}
				}
				_resources.buttons['resetBtn'].enable();
			}else{
				updateAcctGrpGridButtons(null);
			}
			
		}
	}
	
	function getNewGrpId()
	{
		var newGrpId = null;
		
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', 'getNextGrpID');
		IFDS.Xml.addSingleNode(dataXML, 'grpType', '');
		
		// call service
		DesktopWeb.Ajax.doSmartviewUpdate(_dtAcctGrpProcService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{
			// hanldle response
			if (success){
				newGrpId = IFDS.Xml.getNodeValue(responseXML, '//nextGrpID');
			}
		}
		return newGrpId;
	}
	
	function validateUpdateAcctGrp(data, action)
	{
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		var acctGrpXML = IFDS.Xml.addSingleNode(dataXML, 'acctGrp');
		var runMode = action;
		if (action == _MOD)
		{
			var selectedAcctGrpRecord = _resources.grids['acctGrp'].getSelectedRecord();
			if (selectedAcctGrpRecord.data['runMode'] == _ADD) runMode = _ADD;
			data['version'] = selectedAcctGrpRecord.data['version'];
		}
		IFDS.Xml.addSingleNode(acctGrpXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(acctGrpXML, 'acctGrpUUID', data['acctGrpUUID']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpType', data['grpType']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpId', data['grpId']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpDesc', data['grpDesc']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'deff', DesktopWeb.Util.getSMVDateValue(data['deff']));
		IFDS.Xml.addSingleNode(acctGrpXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpStat', data['grpStat']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpRemark', data['grpRemark']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'version', data['version']);
		
		var updateLinkedAcctRecords = _resources.grids['linkedAcct'].getStore().queryBy(function(record){ return record.get('runMode') != '' });
		var linkedAcctsXML = IFDS.Xml.addSingleNode(acctGrpXML, 'LnkAccts');
		for (var i = 0; i < updateLinkedAcctRecords.getCount(); i++)
		{
			buildUpdateLinkedAcctXML(linkedAcctsXML, updateLinkedAcctRecords.itemAt(i));
		} 
		
		// call service
        DesktopWeb.Ajax.doSmartviewAjax(_dtAcctGrpValService, null, dataXML, responseHandler, _translationMap['Validating']);
			
		function buildUpdateLinkedAcctXML(context, updatedLinkedAcct){
			var linkedAcctXML = IFDS.Xml.addSingleNode(context, 'LnkAcct');
			IFDS.Xml.addAttribute(linkedAcctXML, 'RecordSource', updatedLinkedAcct.data['lnkAcctUUID']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'lnkAcctUUID', updatedLinkedAcct.data['lnkAcctUUID']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'acct', updatedLinkedAcct.data['acct']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'deff', DesktopWeb.Util.getSMVDateValue(updatedLinkedAcct.data['deff']));
			IFDS.Xml.addSingleNode(linkedAcctXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(updatedLinkedAcct.data['stopDate']));
			IFDS.Xml.addSingleNode(linkedAcctXML, 'primaryAcct', updatedLinkedAcct.data['primaryAcct']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'version', updatedLinkedAcct.data['version']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'runMode', updatedLinkedAcct.data['runMode']);
		}

		function responseHandler(success, responseXML, contextErrors, contextWarnings) {
			if (success) {	
				// Check if group is stoped and any linked accounts still active
				var grpStopDate = DesktopWeb.Util.stringToDate(data['stopDate'], DesktopWeb.Util.getDateDisplayFormat());
				var curBusDate = DesktopWeb.Util.stringToDate(_defaultValues['curBusDate'], DesktopWeb.Util.getDateDisplayFormat());
				_self.updatesFlag = true;
				updateAcctGrpRecord(data, action);
				updateStatusFilters();
				_resources.popups['acctGrpPopup'].hide();
			}
		}
	}
	
	function validateUpdateLinkedAcct(data, action)
	{
        // build parameter xml
		var selectedAcctGrpRecord = _resources.grids['acctGrp'].getSelectedRecord();
		var dataXML = IFDS.Xml.newDocument('data');
		var acctGrpXML = IFDS.Xml.addSingleNode(dataXML, 'acctGrp');

		IFDS.Xml.addSingleNode(acctGrpXML, 'runMode', selectedAcctGrpRecord.data['runMode']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'acctGrpUUID', selectedAcctGrpRecord.data['acctGrpUUID']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpType', selectedAcctGrpRecord.data['grpType']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpId', selectedAcctGrpRecord.data['grpId']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpDesc', selectedAcctGrpRecord.data['grpDesc']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'deff', DesktopWeb.Util.getSMVDateValue(selectedAcctGrpRecord.data['deff']));
		IFDS.Xml.addSingleNode(acctGrpXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(selectedAcctGrpRecord.data['stopDate']));
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpStat', selectedAcctGrpRecord.data['grpStat']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'grpRemark', selectedAcctGrpRecord.data['grpRemark']);
		IFDS.Xml.addSingleNode(acctGrpXML, 'version', selectedAcctGrpRecord.data['version']);
		
		var linkedAcctsXML = IFDS.Xml.addSingleNode(acctGrpXML, 'LnkAccts');
		var linkedAcctXML = IFDS.Xml.addSingleNode(linkedAcctsXML, 'LnkAcct');

		if (action == _MOD)
		{
			var selectedLinkedAcctRecord = _resources.grids['linkedAcct'].getSelectedRecord();
			if (selectedLinkedAcctRecord.data['runMode'] == _ADD) runMode = _ADD;
			data['version'] = selectedLinkedAcctRecord.data['version'];
		}

		//SMV need this data to deal with last member to be deleted
		var runMode = action;
		var totalNumOfAccts = _resources.grids['linkedAcct'].getStore().getCount();
		var isLastAcct = 'NO';
		if (action == _DEL && totalNumOfAccts == 1) {
			var isLastAcct = 'YES';
		}
		
		IFDS.Xml.addSingleNode(linkedAcctXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(linkedAcctXML, 'isLastAcct', isLastAcct);
		IFDS.Xml.addSingleNode(linkedAcctXML, 'lnkAcctUUID', data['lnkAcctUUID']);
		IFDS.Xml.addSingleNode(linkedAcctXML, 'acct', data['acct']);
		IFDS.Xml.addSingleNode(linkedAcctXML, 'deff', DesktopWeb.Util.getSMVDateValue(data['deff']));
		IFDS.Xml.addSingleNode(linkedAcctXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
		IFDS.Xml.addSingleNode(linkedAcctXML, 'primaryAcct', data['primaryAcct']);
		IFDS.Xml.addSingleNode(linkedAcctXML, 'version', data['version']);
		
		var updateLinkedAcctRecords = _resources.grids['linkedAcct'].getStore().queryBy(function(record){ 
											return (record.get('runMode') != '' && record.get('lnkAcctUUID') != data['lnkAcctUUID']); 
										});
		for (var i = 0; i < updateLinkedAcctRecords.getCount(); i++)
		{
			buildUpdateLinkedAcctXML(linkedAcctsXML, updateLinkedAcctRecords.itemAt(i));
		} 
		
		function buildUpdateLinkedAcctXML(context, updatedLinkedAcct){
			var linkedAcctXML = IFDS.Xml.addSingleNode(context, 'LnkAcct');
			IFDS.Xml.addAttribute(linkedAcctXML, 'RecordSource', updatedLinkedAcct.data['lnkAcctUUID']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'lnkAcctUUID', updatedLinkedAcct.data['lnkAcctUUID']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'acct', updatedLinkedAcct.data['acct']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'deff', DesktopWeb.Util.getSMVDateValue(updatedLinkedAcct.data['deff']));
			IFDS.Xml.addSingleNode(linkedAcctXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(updatedLinkedAcct.data['stopDate']));
			IFDS.Xml.addSingleNode(linkedAcctXML, 'primaryAcct', updatedLinkedAcct.data['primaryAcct']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'version', updatedLinkedAcct.data['version']);
			IFDS.Xml.addSingleNode(linkedAcctXML, 'runMode', updatedLinkedAcct.data['runMode']);
		}
		// call service
        DesktopWeb.Ajax.doSmartviewAjax(_dtAcctGrpValService, null, dataXML, responseHandler, _translationMap['Validating']);
			
		function responseHandler(success, responseXML, contextErrors)
		{
			if (success)
			{
				_self.updatesFlag = true;
				data['name'] = IFDS.Xml.getNodeValue(responseXML, '//AcctInfo/name');
				data['dlrOwnership'] = IFDS.Xml.getNodeValue(responseXML, '//AcctInfo/dlrOwnership');
				data['broker'] = IFDS.Xml.getNodeValue(responseXML, '//AcctInfo/broker');
				data['branch'] = IFDS.Xml.getNodeValue(responseXML, '//AcctInfo/branch');
				data['slsrep'] = IFDS.Xml.getNodeValue(responseXML, '//AcctInfo/slsrep');

				updateLinkedAcctRecord(data, action);
				updateStatusFilters();
				_resources.popups['linkedAcctPopup'].hide();
			}
		}
	}
	
	function updateAcctGrpRecord(data, action)
	{
		switch(action)
		{
			case _ADD:
			{
				data['allowMod'] = 'yes';
				data['allowDel'] = 'yes';
				data['version']  = '0';
				data['hasMoreLinkedAccts'] = 'no';
				data['errMsg'] = '';
				_resources.grids['acctGrp'].addRecord(data);
				_resources.grids['acctGrp'].selectLastRecord();
				break;
			}
			case _MOD:
			{
				var acctGrpRec = _resources.grids['acctGrp'].getSelectedRecord();
				var runMode = _MOD;
				if (acctGrpRec.data['runMode'] == _ADD) runMode = _ADD;
				acctGrpRec.data['runMode'] = runMode;
				acctGrpRec.data['grpDesc'] = data['grpDesc'];
				acctGrpRec.data['deff'] = data['deff'];
				acctGrpRec.data['stopDate'] = data['stopDate'];				
				acctGrpRec.data['grpStat'] = data['grpStat'];
				acctGrpRec.data['grpRemark'] = data['grpRemark'];
				data['errMsg'] = '';
				acctGrpRec.commit();
				break;
			}
			case _DEL:
			{
				var acctGrpRec = _resources.grids['acctGrp'].getSelectedRecord();
				if (acctGrpRec.data['runMode'] == _ADD) {
					_resources.grids['acctGrp'].removeSelectedRecord();
					_resources.grids['acctGrp'].selectFirstRecord();	

				} else {
					acctGrpRec.data['runMode'] = _DEL;
					// Set row selected back to next record if the 1st one is deleted
					var selectedSubmissionIndex  = _resources.grids['acctGrp'].store.indexOf(acctGrpRec);
					if (selectedSubmissionIndex == 0){
						setSelectedRow('acctGrp', selectedSubmissionIndex + 1);
					} else {
						_resources.grids['acctGrp'].selectFirstRecord();
					}
					acctGrpRec.commit();
					//trigger grid fire for last acctGrp Deletion
					if (_resources.grids['acctGrp'].store.getCount() < 1) {
						clearGrid('linkedAcct');
					}
				}
				updateAcctGrpGridButtons();
				break;
			}
		}
	}

	function updateLinkedAcctRecord(data, action)
	{
		switch(action)
		{
			case _ADD:
			{
				data['allowMod'] = 'yes';
				data['allowDel'] = 'yes';
				data['version']  = '0';
				data['errMsg'] = '';
				
				_resources.grids['linkedAcct'].addRecord(data);
				_resources.grids['linkedAcct'].selectLastRecord();
				
				break;
			}
			case _MOD:
			{
				var linkedAcctRec = _resources.grids['linkedAcct'].getSelectedRecord();
				var runMode = _MOD;
				data['runMode'] = (linkedAcctRec.data['runMode'] == _ADD)?_ADD:_MOD;
				data['allowMod'] = 'yes';
				data['allowDel'] = 'yes';
				data['errMsg'] = '';
				
				_resources.grids['linkedAcct'].updateSelectedRecord(data);
				break;
			}
			case _DEL: 
			{
				var linkedAcctRec = _resources.grids['linkedAcct'].getSelectedRecord();

				if (linkedAcctRec.data['runMode'] == _ADD) {
					_resources.grids['linkedAcct'].removeSelectedRecord();
					_resources.grids['linkedAcct'].selectFirstRecord();					
				} else {
					linkedAcctRec.data['runMode'] = _DEL;
					// Set row selected back to next record if the 1st one is deleted
					var selectedSubmissionIndex  = _resources.grids['linkedAcct'].store.indexOf(linkedAcctRec);
					if (selectedSubmissionIndex == 0){
						setSelectedRow('linkedAcct', selectedSubmissionIndex + 1);
					}else{
						_resources.grids['linkedAcct'].selectFirstRecord();
					}
					linkedAcctRec.commit();
				}
				break;
			}
		}
		updateLinkedAcctsOfAcctGrp();
	}
	
	function updateLinkedAcctsOfAcctGrp()
	{
		var acctGrpRec = _resources.grids['acctGrp'].getSelectedRecord();
		var linkedAcctRecords = _resources.grids['linkedAcct'].getAllRecords();
		var linkedAcctsXML = IFDS.Xml.newDocument('LnkAccts');
	
		Ext.each(linkedAcctRecords, function(linkedAcctRecord){
			createLinkedAcctXML(linkedAcctsXML, linkedAcctRecord);
		});

		acctGrpRec.data['LnkAccts'] = IFDS.Xml.serialize(linkedAcctsXML);
		
		if (!acctGrpRec.data['runMode'] || acctGrpRec.data['runMode'].length == 0 ) {
			acctGrpRec.data['runMode'] = _ACC;
		}
		
		acctGrpRec.commit();
		
		function createLinkedAcctXML(context, record)
		{
			if (context)
			{
				var linkedAcctXML = IFDS.Xml.addSingleNode(context, 'LnkAcct');
				IFDS.Xml.addSingleNode(linkedAcctXML, 'errMsg', record.data['errMsg']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'lnkAcctUUID', record.data['lnkAcctUUID']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'acct', record.data['acct']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'name', record.data['name']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'dlrOwnership', record.data['dlrOwnership']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'othRef', record.data['othRef']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'broker', record.data['broker']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'branch', record.data['branch']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'slsrep', record.data['slsrep']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'deff', DesktopWeb.Util.getSMVDateValue(record.data['deff']));
				IFDS.Xml.addSingleNode(linkedAcctXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(record.data['stopDate']));
				IFDS.Xml.addSingleNode(linkedAcctXML, 'primaryAcct', record.data['primaryAcct']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'allowMod', record.data['allowMod']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'allowDel', record.data['allowDel']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'userName', record.data['userName']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'processDate', record.data['processDate']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'modUser', record.data['modUser']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'modDate', record.data['modDate']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'version', record.data['version']);
				IFDS.Xml.addSingleNode(linkedAcctXML, 'runMode', record.data['runMode']);
			}
		}
	}
	
	function updateStatusFilters()
	{
		if (_self.updatesFlag)
		{
			_resources.fields['acctGrpStat'].disable();
			_resources.fields['linkedAcctStat'].disable();
		}else{
			_resources.fields['acctGrpStat'].enable();
			_resources.fields['linkedAcctStat'].enable();
		}
	}
	
	function updateAcctGrpGridButtons(record)
	{
		var grid = _resources.grids['acctGrp'];
		if (_permissions[_self.ADD]){
			grid.enableButton('addBtn'); 
		}else{
			grid.disableButton('addBtn'); 
		}
		if(record)
		{	
			var curBusDate = DesktopWeb.Util.stringToDate(_defaultValues['curBusDate'], DesktopWeb.Util.getDateDisplayFormat());
			var stopDate = DesktopWeb.Util.stringToDate(record.data['stopDate'], DesktopWeb.Util.getDateDisplayFormat());
			if (record.data['allowMod'] == 'yes' && _permissions[_self.MOD]){
				if (stopDate <= curBusDate && Ext.isEmpty(record.data['runMode'])){
					grid.disableButton('modBtn');
				}else{
					grid.enableButton('modBtn'); 
				}
			}else{
				grid.disableButton('modBtn'); 
			}
			
			if (record.data['allowDel'] == 'yes' && _permissions[_self.DEL] && stopDate > curBusDate){
				grid.enableButton('delBtn'); 
			}else{
				grid.disableButton('delBtn'); 
			}
			//Delete button is available for Germany only, will overwritten the original for AFT
			if(_AFTACCTGRPTYPE ==_configs['groupType']){
			    if ( _permissions[_self.DEL] && record.data['stopDate'] > getCurrDate()) {
			    	grid.enableButton('delBtn'); 
			    } else {
			    	grid.disableButton('delBtn'); 
			    }
			}
			//Modify button for germany
			if (_AFTACCTGRPTYPE ==_configs['groupType'] && record.data['stopDate'] <= getCurrDate()) {
				grid.disableButton('modBtn'); 
			} 

			if (record.data['runMode'] == _self.ADD){
				grid.disableButton('historyBtn'); 
				grid.disableButton('adminBtn'); 
			}else{
				grid.enableButton('historyBtn'); 
				grid.enableButton('adminBtn'); 
			}
		} else {//handling adding one record, delete it without commit
			var selectedAcctGrp = _resources.grids['acctGrp'].getSelectedRecord();
			if (selectedAcctGrp == null) {
				_resources.grids['acctGrp'].disableButton('delBtn'); 
				_resources.grids['acctGrp'].disableButton('modBtn'); 
			}
		}
	}
	
	function updateLinkedAcctGridButtons(record)
	{
		var grid = _resources.grids['linkedAcct'];
		var selectedAcctGrp = _resources.grids['acctGrp'].getSelectedRecord();

		if (selectedAcctGrp && _permissions[_self.ADD]){
			grid.enableButton('addBtn'); 
		}else{
			grid.disableButton('addBtn'); 
		}
		if(record)
		{
			var curBusDate = DesktopWeb.Util.stringToDate(_defaultValues['curBusDate'], DesktopWeb.Util.getDateDisplayFormat());
			var stopDate = DesktopWeb.Util.stringToDate(record.data['stopDate'], DesktopWeb.Util.getDateDisplayFormat());
			if (record.data['allowMod'] == 'yes' && _permissions[_self.MOD]){
				if (stopDate <= curBusDate && Ext.isEmpty(record.data['runMode'])){
					grid.disableButton('modBtn'); 
				}else{
					grid.enableButton('modBtn'); 
				}
				if (_permissions[_self.MOD] && _AFTACCTGRPTYPE ==_configs['groupType']) {
					grid.enableButton('modBtn'); 
				}
			}else{
				grid.disableButton('modBtn'); 
			}
			
			if (record.data['allowDel'] == 'yes' && _permissions[_self.DEL] && stopDate > curBusDate){
				grid.enableButton('delBtn'); 
			}else{
				grid.disableButton('delBtn'); 
			}

			//Delete button is available for Germany only, will overwritten the original for AFT
			if(_AFTACCTGRPTYPE ==_configs['groupType']){
			    if (_permissions[_self.DEL]  && record.data['stopDate'] > getCurrDate()) {
        			grid.enableButton('delBtn'); 
        		} else {
        			grid.disableButton('delBtn'); 
        		}
			}
			
			//Add button is diabled if AcctGrp is inActive for AFT
			if (_AFTACCTGRPTYPE ==_configs['groupType'] && selectedAcctGrp.data['stopDate'] <= getCurrDate()) {
				grid.disableButton('addBtn'); 
			} 
			
			if (record.data['runMode'] == _self.ADD){
				grid.disableButton('historyBtn'); 
				grid.disableButton('adminBtn'); 
			}else{
				grid.enableButton('historyBtn'); 
				grid.enableButton('adminBtn'); 
			}
		} else {
			if (_AFTACCTGRPTYPE ==_configs['groupType'] && selectedAcctGrp.data['stopDate'] <= getCurrDate()) {
				grid.disableButton('addBtn'); 
			}
		}
	}
	
	function updateShareholderName(record)
	{
		if (record)
		{
			Ext.getCmp('bb_shareholderName').setText(_translationMap['ShareholderName'] + ': ' + record.data['name']);
		}else{
			Ext.getCmp('bb_shareholderName').setText(_translationMap['ShareholderName'] + ': ');
		}
	}
	
	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
		if (_resources.fields['grpType'].getValue() != null && _permissions[_self.ADD]) {
			_resources.grids['acctGrp'].enableButton('addBtn');
		} 
		if (name == 'linkedAcct') updateShareholderName(null);
	}

	function disableScreen()
	{
		_resources.fields['grpType'].disable();
		_resources.fields['searchFor'].disable();
		_resources.fields['searchValue'].disable();
		_resources.fields['acctGrpStat'].disable();
		_resources.fields['linkedAcctStat'].disable();
		_resources.buttons['searchBtn'].disable();
		_resources.grids['acctGrp'].disableAllButtons();	
		_resources.grids['linkedAcct'].disableAllButtons();	
	}

	
	function setSelectedRow(gridName, index) {
		_resources.grids[gridName].setSelectedRecord(index);
	}
	
	function isNumber(str) {
        var pattern = /^\d+$/;
        return pattern.test(str); // returns a boolean
    }

	function validateSearchCriteria()
	{
		_resources.fields['grpType'].clearInvalid();
		_resources.fields['searchFor'].clearInvalid();
		_resources.fields['searchValue'].clearInvalid();
		
		if (_resources.fields['grpType'].getValue().length < 1) {
			_resources.fields['grpType'].markInvalid(_translationMap['FIELD_IS_REQUIRED']);
			return false;
		}
		//acctNummer has to be integer
		if('Acct' == _resources.fields['searchFor'].getValue() && !isNumber(_resources.fields['searchValue'].getValue())) {
			_resources.fields['searchValue'].markInvalid();	
			_resources.fields['searchValue'].focus();
			return false;
		}
		
		_resources.fields['searchFor'].allowBlank = Ext.isEmpty(_resources.fields['searchValue'].getValue());
		
		if(_resources.fields['searchFor'].getValue().length > 0 && _resources.fields['searchValue'].getValue().length < 1) {
			_resources.fields['searchValue'].markInvalid(_translationMap['FIELD_IS_REQUIRED']);
			return false;
		} else if (_resources.fields['searchValue'].getValue().length > 0 && _resources.fields['searchFor'].getValue().length < 1) {
			_resources.fields['searchFor'].allowBlank = Ext.isEmpty(_resources.fields['searchValue'].getValue());
			_resources.fields['searchFor'].markInvalid(_translationMap['FIELD_IS_REQUIRED']);
			return false;
		} else {
			return true;
		}
		
		return _resources.fields['grpType'].isValid() 
				&& _resources.fields['searchFor'].isValid() 
				&& _resources.fields['searchValue'].isValid();
	}
	
	function buildUpdateXML(isUpdate)
	{		
		var updateAccRecords = _resources.grids['acctGrp'].getStore().queryBy(function(record){ return record.get('runMode') == _ACC });
		var updateDelRecords = _resources.grids['acctGrp'].getStore().queryBy(function(record){ return record.get('runMode') == _DEL });
		var updateModRecords = _resources.grids['acctGrp'].getStore().queryBy(function(record){ return record.get('runMode') == _MOD });
		var updateAddRecords = _resources.grids['acctGrp'].getStore().queryBy(function(record){ return record.get('runMode') == _ADD });

		var updateXML = IFDS.Xml.newDocument('data');
		
		var totalRecs = updateAccRecords.length + updateDelRecords.length + updateModRecords.length + updateAddRecords.length;
		if (totalRecs < 1 ) {
		   return updateXML; //Add + Delete the same acctGrp without commit, don't call API
		}
		
		if (!isUpdate)  // This is for validation before committing.
		{
			IFDS.Xml.addSingleNode(updateXML, 'runMode', 'validation');
		}
		
		var acctGrpsXML = IFDS.Xml.addSingleNode(updateXML, 'AcctGrps');
				
		buildUpdateXMLAll(acctGrpsXML, updateAccRecords );
		buildUpdateXMLAll(acctGrpsXML, updateDelRecords );
		buildUpdateXMLAll(acctGrpsXML, updateModRecords );
		buildUpdateXMLAll(acctGrpsXML, updateAddRecords );
		
		return updateXML;
		
		function buildUpdateXMLAll(context, updatedRecords)
		{
			for (var i = 0; i < updatedRecords.getCount(); i++)
			{
				buildUpdateXMLByRecord(context, updatedRecords.itemAt(i));
			} 
		}

		function buildUpdateXMLByRecord(context, record)
		{
			var acctGrpXML = IFDS.Xml.addSingleNode(context, 'AcctGrp');
			IFDS.Xml.addAttribute(acctGrpXML, 'RecordSource', record.get('acctGrpUUID'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'runMode', record.get('runMode')==_ACC?'':record.get('runMode'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'acctGrpUUID', record.get('acctGrpUUID'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'grpType', record.get('grpType'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'grpId', record.get('grpId'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'grpDesc', record.get('grpDesc'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'deff', DesktopWeb.Util.getSMVDateValue(record.get('deff')));
			IFDS.Xml.addSingleNode(acctGrpXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(record.get('stopDate')));
			IFDS.Xml.addSingleNode(acctGrpXML, 'grpStat', record.get('grpStat'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'grpRemark', record.get('grpRemark'));
			IFDS.Xml.addSingleNode(acctGrpXML, 'version', record.get('version'));
			
			var newLinkedAcctsStr = record.get('LnkAccts');	
			if (newLinkedAcctsStr != null && newLinkedAcctsStr.length > 0) {
			
				var newLinkedAcctsXML = IFDS.Xml.stringToXML(newLinkedAcctsStr);
				
				var addLinkedAccts = IFDS.Xml.getNodes(newLinkedAcctsXML, "//LnkAcct[runMode='" + _ADD + "']");
				var modLinkedAccts = IFDS.Xml.getNodes(newLinkedAcctsXML, "//LnkAcct[runMode='" + _MOD + "']");
				var delLinkedAccts = IFDS.Xml.getNodes(newLinkedAcctsXML, "//LnkAcct[runMode='" + _DEL + "']");
				
				var linkedAcctsXML = IFDS.Xml.addSingleNode(acctGrpXML, 'LnkAccts');
				
				Ext.each(delLinkedAccts, function(delLinkedAcct){buildUpdateLinkedAcctXML(delLinkedAcct, linkedAcctsXML)});
				Ext.each(modLinkedAccts, function(modLinkedAcct){buildUpdateLinkedAcctXML(modLinkedAcct, linkedAcctsXML)});
				Ext.each(addLinkedAccts, function(addLinkedAcct){buildUpdateLinkedAcctXML(addLinkedAcct, linkedAcctsXML)});
			
		
				function buildUpdateLinkedAcctXML(updatedLinkedAcct, context){
					var linkedAcctXML = IFDS.Xml.addSingleNode(context, 'LnkAcct');
					IFDS.Xml.addAttribute(linkedAcctXML, 'RecordSource', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'lnkAcctUUID'));
					IFDS.Xml.addSingleNode(linkedAcctXML, 'lnkAcctUUID', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'lnkAcctUUID'));
					IFDS.Xml.addSingleNode(linkedAcctXML, 'acct', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'acct'));
					IFDS.Xml.addSingleNode(linkedAcctXML, 'deff', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'deff'));
					IFDS.Xml.addSingleNode(linkedAcctXML, 'stopDate', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'stopDate'));
					IFDS.Xml.addSingleNode(linkedAcctXML, 'primaryAcct', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'primaryAcct'));
					IFDS.Xml.addSingleNode(linkedAcctXML, 'version', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'version'));
					IFDS.Xml.addSingleNode(linkedAcctXML, 'runMode', IFDS.Xml.getNodeValue(updatedLinkedAcct, 'runMode'));
               }
			}
		}
	}
	//Dynamic populate "Other Reference number" for Germany account Group - config
	function setUpdatedLinkedAcctPopUpForACBRLK() {
		if(_self.getConfig(_resources.popups['linkedAcctPopup'].getField('grpType').getValue(), "OtherRefNum") == "YES") {
			_resources.popups['linkedAcctPopup'].getField('acctOtherRefNum').show();
		} else {
			_resources.popups['linkedAcctPopup'].getField('acctOtherRefNum').hide();
		}
	}
	//Germany Account(ACBRLK)/Fund Group Broker Linkage
	function setUpdatedAcctGrpPopUpForACBRLK() {
		if (_AFTACCTGRPTYPE == _resources.fields['grpType'].getValue()) {
		  _resources.popups['acctGrpPopup'].getField('grpType').setValue(_resources.fields['grpType'].getValue()); 
		  _resources.popups['acctGrpPopup'].getField('grpType').disable();
		} else {
		  _resources.popups['acctGrpPopup'].getField('grpType').setValue('');
		  _resources.popups['acctGrpPopup'].getField('grpType').enable();
		}
	}
	
	//Group id and desc Maxlength is set from the config if available for group type
	function setMaxLengthFromConfig (grpType,popupNm) {
		// Group ID and desc length reset
		_resources.popups[popupNm].getField('grpId').reset();
		_resources.popups[popupNm].getField('grpDesc').reset();
		
		if (_self.getConfig(grpType, "GroupIDLength") != null) {
			_resources.popups[popupNm].getField('grpId').maxLength = _self.getConfig(grpType, "GroupIDLength");
		} else {
			_resources.popups[popupNm].getField('grpId').maxLength = 15;
		}
		
		if (_self.getConfig(grpType, "GroupDescLength") != null) {
			_resources.popups[popupNm].getField('grpDesc').maxLength = _self.getConfig(grpType, "GroupDescLength");
		} else {
			_resources.popups[popupNm].getField('grpDesc').maxLength = 40;
		}
	}
	
	//defaulting  dropdowns
	function defaultDropdowns(grpType) {
	 	//Search for defaulting
	    	var defaultsearchFor = IFDS.Xml.getNodeValue(_initXML, "/*//ListSelection[@id = 'AcctGrpSrchList']");
	    	if(defaultsearchFor.length > 0){
	    	    _resources.fields['searchFor'].setValue(defaultsearchFor);
	    	}
	    	//GroupType defaulting
		var defaultGrpType = IFDS.Xml.getNodeValue(_initXML, "/*//ListSelection[@id = 'GroupTypeList']");
		if(defaultGrpType.length > 0 && _resources.fields['grpType'].getValue() == ''){
		    _resources.fields['grpType'].setValue(defaultGrpType);
		}
	}
	
	function defaultGrpTypeDrpdwn(grpType) {
	    	//GroupType defaulting
		var defaultGrpType = IFDS.Xml.getNodeValue(_initXML, "/*//ListSelection[@id = 'GroupTypeList']");
		var grpTypeField = _resources.popups['acctGrpPopup'].getField('grpType');
		
		if(grpType.length > 0){
		    grpTypeField.setValue(grpType);
		}
		else if(defaultGrpType.length > 0){
		    grpTypeField.setValue(defaultGrpType);
		}
		
		grpTypeField.fireEvent('select',grpTypeField);
	}
	
	//Germany Account(ACBRLK)/Fund Group Broker Linkage, init set up
	function setUpdatedFormForACBRLK(grpType) {
		if(_self.getConfig(grpType, "OtherRefNum") == "YES") {
			_resources.grids['linkedAcct'].showColumn (_showOtherRefNumColumn);
		} else {
			_resources.grids['linkedAcct'].hideColumn (_showOtherRefNumColumn);
		}
		//Delete buttons added for Germany
		if(_self.getConfig(grpType, "Delete") == "YES") {
			_resources.grids['acctGrp'].showButton('delBtn');
			_resources.grids['linkedAcct'].showButton('delBtn');
		} else {
			_resources.grids['acctGrp'].hideButton('delBtn');
			_resources.grids['linkedAcct'].hideButton('delBtn');
		}
		//Modify button hide for Germany 
		if(_self.getConfig(grpType, "AccountModify") == "NO") {
			_resources.grids['linkedAcct'].hideButton('modBtn');
		} else {
			_resources.grids['linkedAcct'].showButton('modBtn');
		}
	}
	//Germany Account(ACBRLK) group, defaulting with currentDate
	function getCurrDate() {
	   	var startDateACBRLK = new Date();
		return DesktopWeb.Util.getDateString(startDateACBRLK, DesktopWeb.Util.getDateDisplayFormat());
    }

	function storeContextErrors(errorNodes)
	{
		//reset deleted records runmode in order to display the deleted acctGrp with ERROR
		var delRecords  = _resources.grids['acctGrp'].getStore().queryBy(function(record){ return record.get('runMode') == 'del' });
		for (var i = 0; i < errorNodes.length; i++) {
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			var errorCode = IFDS.Xml.getNodeValue(errorNodes[i], 'errorCode');
			var errorUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			if (errorCode == _LINKAGEERRORCODE  || errorCode == _LINKAGEERRORCODEDEL) {
				for (var i = 0; i < delRecords.getCount(); i++) {
					var acctGrpUUID = delRecords.itemAt(i).data['acctGrpUUID'];
					if ( errorUUID == acctGrpUUID) {
						delRecords.itemAt(i).set('runMode', '');	
					}
				}
			}
		}
		
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			if(table == 'AcctGrp')
			{
				var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				
				// Update acctGrp grid
				var recordIndex = _resources.grids['acctGrp'].getStore().find('acctGrpUUID', uuid);
				var acctGrpRecord = _resources.grids['acctGrp'].getStore().getAt(recordIndex);
				acctGrpRecord.set('errMsg', errMsg);
				_resources.grids['acctGrp'].getStore().commitChanges();
				if(firstErrRecIndex == -1)firstErrRecIndex = recordIndex;
			}else{
				var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				var acctGrpUUID = null;
				
				// find acctGrp uuid by linkedAcct uuid from _updateXML
				var acctGrpXML = IFDS.Xml.getNode(_updateXML, "//AcctGrp[LnkAccts/LnkAcct/lnkAcctUUID='" + uuid + "']");
				if (acctGrpXML){
					acctGrpUUID = IFDS.Xml.getNodeValue(acctGrpXML, 'acctGrpUUID');
					var acctGrpRecIndex = _resources.grids['acctGrp'].getStore().find('acctGrpUUID', acctGrpUUID);
					var acctGrpRecord = _resources.grids['acctGrp'].getStore().getAt(acctGrpRecIndex);
					var linkedAcctsXML = IFDS.Xml.stringToXML(acctGrpRecord.data['LnkAccts']);
					var linkedAcctXML = IFDS.Xml.getNode(linkedAcctsXML, "//LnkAcct[lnkAcctUUID='" + uuid + "']");

					//handler if the account is deleted and assign it back to the grid
					var runModeNode = IFDS.Xml.getNode(linkedAcctXML, 'runMode');
					if (IFDS.Xml.getNodeValue(runModeNode, '//runMode') == 'del') {
						IFDS.Xml.setNodeValue(runModeNode, '');
					}
					
					var errMsgNode = IFDS.Xml.getNode(linkedAcctXML, 'errMsg');
					if (errMsgNode == null){
						IFDS.Xml.addSingleNode(linkedAcctXML, 'errMsg', errMsg);
					}else{
						IFDS.Xml.setNodeValue(errMsgNode, errMsg);
					}
					acctGrpRecord.data['LnkAccts'] = IFDS.Xml.serialize(linkedAcctsXML);
					_resources.grids['acctGrp'].getStore().commitChanges();
					
					if(firstErrRecIndex == -1)firstErrRecIndex = acctGrpRecIndex;
				}
			}
		}
		
		if(firstErrRecIndex==-1)
		{
			_resources.grids['acctGrp'].getSelectionModel().selectFirstRow();
		}else{
			_resources.grids['acctGrp'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['acctGrp'].focusRow(firstErrRecIndex);
		}
	}

	// PUBLIC ITEMS *************************************
	return {				
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,INQ: _INQ
		,YES: 'yes'
		,NO: 'no'
		,configs: _configs
		,updatesFlag: false
		,AFTACCTGRPTYPE: _AFTACCTGRPTYPE
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
            // Call init service
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'runMode', 'init');
			
			DesktopWeb.Ajax.doSmartviewAjax(_dtAcctGrpInqService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
            
			function responseHandler(success, responseXML)
			{
				if (success){
					// Handle response
					_initXML = responseXML;
					
					// Load configuration 
					loadConfigurations(responseXML);
					
					// Load Default Values
					loadDefaultValues(responseXML);
					
					// Load permission if success
					storePermissions(responseXML);
					
					// Load dropdown if success
					populateDropdownList(responseXML);
					
					//Load form layout change for Germany - Group Type
					if (_AFTACCTGRPTYPE ==_configs['groupType']) {
						//Reset RequestRecNums for Germany
						loadRequestRecNums(_configs['groupType']);
					}
					
					//Load form layout change
					setUpdatedFormForACBRLK(_configs['groupType']);
					
					// Call render screen function
					if (_permissions[_self.INQ]){
						populateDefaultSearchCriteria(responseXML);				
					}

					if (_permissions[_self.ADD]){
						_resources.grids['acctGrp'].enableButton('addBtn'); 
					}
					
					if (!_configs['salesRepbyBranch']){
						var linkedAcctGrid = _resources.grids['linkedAcct'];
						linkedAcctGrid.hideColumn(linkedAcctGrid.getColumnModel().findColumnIndex('branch')); 
					}
					
				}else{
					disableScreen();
				}
			}
		}

		,getLinkedAcctsXML: function(acctGrpUUID)
		{
			return IFDS.Xml.getNode(_acctGrpXML, "//AcctGrps/AcctGrp[acctGrpUUID='" + acctGrpUUID + "']/LnkAccts");
		}
		
		,selectAcctGrp: function(record)
		{
			updateAcctGrpGridButtons(record);
			clearGrid('linkedAcct');
			if (record.data['LnkAccts'] && record.data['LnkAccts'].length > 0)
			{
				var linkedAcctXML = IFDS.Xml.stringToXML(record.data['LnkAccts']);
				_resources.grids['linkedAcct'].loadData(linkedAcctXML);
				
				if (record.data['hasMoreLinkedAccts'] == 'yes')
				{
					_resources.grids['linkedAcct'].enableButton('moreBtn');
				}
			}else{
				if (record.data['runMode'] == _self.ADD){
					updateLinkedAcctGridButtons(null);
				}else{
					doSearch('reloadDetl', false);
				}
			}
			
			if (_self.getConfig(record.data['grpType'], "PrimaryPerGroup")) {
				_resources.grids['linkedAcct'].showColumn (6);
			} 
			else {
				_resources.grids['linkedAcct'].hideColumn (6);
			}
			
			if(_self.getConfig(record.data['grpType'], "OtherRefNum") == "YES") {
				_resources.popups['linkedAcctPopup'].getField('acctOtherRefNum').show();
			} else {
				_resources.popups['linkedAcctPopup'].getField('acctOtherRefNum').hide();
			}
			
			this.enableDisableDates(_configs['groupType'], 'linkedAcctPopup');
			
		}
		
		,selectLinkedAcct: function(record)
		{
			updateShareholderName(record);
			updateLinkedAcctGridButtons(record);
		}
		
		,getDisplay: function(listName, code)
		{
			var listNode = IFDS.Xml.getNode(_initXML, "//List[@listName = '" + listName + "']/Element[code='" + code + "']");
			return (listNode)?IFDS.Xml.getNodeValue(listNode, 'value'):code;
		}
		
		,openActionPopup: function(name, action)
		{		
			var popup = _resources.popups[name];	
			popup.show();
			popup.init(action);
		}
		
		,openHistoryPopup: function(recType)
		{
			var viewParam = {};
			var historyName = null;
			if (recType == 'AcctGrp')
			{
				var selectedAcctGrp = _resources.grids['acctGrp'].getSelectedRecord();
				viewParam['auditType'] = 'AcctGroupMstr';
				viewParam['searchValue1'] = selectedAcctGrp.get('acctGrpUUID');
				historyName = _translationMap['AccountGroup']+ ' - ' +_translationMap['History'];
			}
			else
			{
				var selectedLinkedAcct = _resources.grids['linkedAcct'].getSelectedRecord();
				viewParam['auditType'] = 'AcctGroupMember';
				viewParam['searchValue1'] = selectedLinkedAcct.get('lnkAcctUUID');		
				historyName = _translationMap['LinkedAccount']+ ' - ' +_translationMap['History'];		
			}
			_resources.popups['history'].init(historyName, _dtHistoryService, viewParam, true);
			_resources.popups['history'].show();
		}
		
		,openAdminPopup: function(recType)
		{					
			var title = null;	
			var selectedRecord = null;
			if (recType == 'AcctGrp')
			{
				selectedRecord = _resources.grids['acctGrp'].getSelectedRecord();
				title = _translationMap['AccountGroup']+ ' - ' +_translationMap['Admin']
			}else{
				selectedRecord = _resources.grids['linkedAcct'].getSelectedRecord();
				title = _translationMap['LinkedAccount']+ ' - ' +_translationMap['Admin']
			}
			var adminData = {};
			adminData['userName'] = selectedRecord.get('userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('processDate'));
			adminData['modUser'] = selectedRecord.get('modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}

		,updateSearchButton: function()
		{
			if (_resources.fields['grpType'].getValue().length > 0)
			{
				if (_resources.fields['searchFor'].getValue().length > 0)
				{
					_resources.buttons['searchBtn'].enable();
				}else{
					_resources.buttons['searchBtn'].enable();
				}
			}else{
				_resources.buttons['searchBtn'].disable();
			}
		}
		//New added for Germany, will apply to all clients too
	    ,doReset: function() {
			if (_self.updatesFlag) {
				DesktopWeb.Util.displayDiscardPrompt(performReset);
			} else {
				performReset(true);
			}
			function performReset(confirm) {
				if (confirm){
					clearGrid('acctGrp');
					clearGrid('linkedAcct');
					_self.updatesFlag = false; 
					_searchedFlag = false;
					_resources.fields['grpType'].enable();

					var defaultGrpType = IFDS.Xml.getNodeValue(_initXML, "/*//ListSelection[@id = 'GroupTypeList']");
					if (_AFTACCTGRPTYPE == _resources.fields['grpType'].getValue() && defaultGrpType.length > 0) {
						_resources.fields['grpType'].setValue(defaultGrpType);
					}
					//From C++ window link, do not reset Search for fields
					var acctNum = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
					if(acctNum) {
						populateDefaultSearchCriteria();
					} else {
						_resources.fields['searchFor'].enable();
						_resources.fields['searchFor'].reset();
						_resources.fields['searchValue'].enable();
						_resources.fields['searchValue'].reset();
					}
					
					_resources.buttons['resetBtn'].disable();
					_resources.buttons['searchBtn'].enable();
					
					_resources.fields['acctGrpStat'].enable();
					_resources.fields['linkedAcctStat'].enable();

					_resources.fields['acctGrpStat'].setValue('active');
					_resources.fields['linkedAcctStat'].setValue('active');
					
					if (_permissions[_self.ADD]){
						_resources.grids['acctGrp'].enableButton('addBtn'); 
					}
				}
		    }
		}
		
		,clickHandle_searchBtn: function()
		{
			if (_self.updatesFlag){
				DesktopWeb.Util.displayDiscardPrompt(performSearch);
			}else{
				performSearch(true);
			}
			function performSearch(confirm){
				if (confirm){
					if (validateSearchCriteria()){
						_self.updatesFlag = false;
						_currentSearch['grpType'] = _resources.fields['grpType'].getValue();
						_currentSearch['searchFor'] = _resources.fields['searchFor'].getValue();
						_currentSearch['searchValue'] = _resources.fields['searchValue'].getValue();
						_currentSearch['grpStat'] = _resources.fields['acctGrpStat'].getValue().getGroupValue();
						_currentSearch['acctStat'] = _resources.fields['linkedAcctStat'].getValue().getGroupValue();
						//reset request records number when account group type changes
						loadRequestRecNums(_currentSearch['grpType']);

						_nextStartRecNum = 1;
						
						clearGrid('linkedAcct');
						clearGrid('acctGrp');
						
						updateStatusFilters();
						doSearch('reload', false);
					}
				}
			}
		}
		
		,changeHandle_GrpStat: function()
		{
			_currentSearch['grpStat'] = _resources.fields['acctGrpStat'].getValue().getGroupValue();
			if (_searchedFlag)
			{
				_nextStartRecNum = 1;
				
				clearGrid('linkedAcct');
				clearGrid('acctGrp');
				
				doSearch('reload', false);
			}
		}

		,changeHandle_LinkedAcctStat: function()
		{
			_currentSearch['acctStat'] = _resources.fields['linkedAcctStat'].getValue().getGroupValue();
			if (_searchedFlag)
			{
				clearGrid('linkedAcct');
				
				var selectedAcct = _resources.grids['acctGrp'].getSelectedRecord();
				if (selectedAcct) doSearch('reloadDetl', false);
			}
		}

		,clickHandle_moreBtn: function()
		{
			doSearch('reload', true);
		}
		
		,clickHandle_moreBtnDetl: function()
		{
			doSearch('reloadDetl', true);
		}
		
		,getNewGrpId: function()
		{
			var newGrpId = getNewGrpId();
			return newGrpId;
		}
		
		,getDefault: function(defaultName)
		{
			return _defaultValues[defaultName];
		}
		
		,validateAcctGrp: function(data, action)
		{
			validateUpdateAcctGrp(data, action);
		}
		
		,validateLinkedAcct: function(data, action)
		{
			validateUpdateLinkedAcct(data, action);
		}
		
		,getNewAcctGrpUUID: function()
		{
			return "TMPACCTGRP" + (_nextUUID++);
		}
		
		,getNewLinkedAcctUUID: function()
		{
			return "TMPLNKACCT" + (_nextUUID++);
		}
		
		,loadAccountSuggestField: function(acctNum)
		{	
			var accountXML = IFDS.Xml.newDocument('data');			
			IFDS.Xml.addSingleNode(accountXML, 'searchValue', acctNum);
			IFDS.Xml.addSingleNode(accountXML, 'startRecordNum', '');
			IFDS.Xml.addSingleNode(accountXML, 'maxRecords', 14);			
			IFDS.Xml.addSingleNode(accountXML, 'incAllStat', 'yes');
				
			DesktopWeb.Ajax.doSmartviewAjax('AccountSearch', null, accountXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{					
				if (success)
				{
					_resources.popups['linkedAcctPopup'].getField('account').getStore().loadData(IFDS.Xml.getNode(responseXML, '/*//PossibleMatches'));
					_resources.popups['linkedAcctPopup'].getField('account').setValue(acctNum);
				}			
			}
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
			_updateXML = buildUpdateXML(true);

			DesktopWeb.Ajax.doSmartviewUpdate(_dtAcctGrpProcService, null, IFDS.Xml.cloneDocument(_updateXML), responseHandler, _translationMap['ProcMsg_Saving']);			
			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}else{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}
		
		, doCommitValidate: function()
		{
			var updateStatus = null;
			_updateXML = buildUpdateXML(false);
			DesktopWeb.Ajax.doSmartviewAjax(_dtAcctGrpProcService, null, IFDS.Xml.cloneDocument(_updateXML), responseHandler, _translationMap['ProcMsg_Saving'], Ext.Msg.OKCANCEL);			

			function responseHandler(success, responseXML, contextErrors, warnings, btn)
			{
				
				if (success)
				{					
					if (btn == null || btn == 'ok') {
						DesktopWeb.Util.commitScreen();
					}
				}
				else 
				{
					storeContextErrors(contextErrors);
				}
			}
		}
		
		,getConfig: function(grpType, configName)
		{			
			var xml;
			var configValue = null;
			xml = IFDS.Xml.getNode(_initXML, "//GroupTypes/GroupType[@groupType='" + grpType + "']/Configs/Config[@configName='UseAcctGroupConfig']");
			if (xml != null && IFDS.Xml.getNodeValue(xml, 'configValue').toLowerCase() == 'yes') {
				xml = IFDS.Xml.getNode(_initXML, "//GroupTypes/GroupType[@groupType='" + grpType + "']/Configs/Config[@configName='" + configName + "']");
				if (xml != null) {
					configValue = IFDS.Xml.getNodeValue(xml, 'configValue');
				} 
			}
			else {
				if (configName == "AutoGroupID") {
					configValue = _self.configs['autoGrpId'];
				}
			}
			return configValue;
		}
		
		,populateGrpStatusByGrpType: function (grpType)
		{
			var applStatus = IFDS.Xml.getNodes(_initXML, "//GroupTypes/GroupType[@groupType='" + grpType + "']/Statuses/statusCode");
			_resources.popups['acctGrpPopup'].getField('grpStat').getStore().clearFilter(true);
			_resources.popups['acctGrpPopup'].getField('grpStat').getStore().filterBy(
				function (record) {				
					var retValue = false;
					Ext.each(applStatus, function(elmXML) {				
						if (record.get('code') == IFDS.Xml.getNodeValue(elmXML, ".")) {
							retValue = true;
						}
					});	
					return retValue;
				}
			);
		}
		
		,enableGrpStatus: function (appli)
		{
			if (appli) {
				_resources.popups['acctGrpPopup'].getField('grpStat').show();
				_resources.popups['acctGrpPopup'].getField('grpRemark').show();
			} else {
				_resources.popups['acctGrpPopup'].getField('grpStat').hide();
				_resources.popups['acctGrpPopup'].getField('grpRemark').hide();
			}		
		}	

		,defaultGrpStatus: function (appli, action, defaultVal)
		{
			if (appli && action == _ADD)
			{
				_resources.popups['acctGrpPopup'].getField('grpStat').setValue(defaultVal);
			}
		}
		
		,clearGrpStatus: function (newValue, oldValue)
		{
			if (oldValue != newValue && _resources.popups['acctGrpPopup'].getField('grpStat').getValue() != "")
			{
				_resources.popups['acctGrpPopup'].getField('grpStat').setValue("");
			}
		}
		
		,enableGrpId: function (appli)
		{
			if (appli) {
				_resources.popups['acctGrpPopup'].getField('grpId').show();
			} else {
				_resources.popups['acctGrpPopup'].getField('grpId').hide();
			}
		}
		//Germany does not need Dates, but assign current date. SMV will store as system dates
		,setStartStopDate: function (grpType,popUpNm) {
			if (_AFTACCTGRPTYPE == grpType) {
				_resources.popups[popUpNm].getField('deff').setValue(getCurrDate());
				_resources.popups[popUpNm].getField('stopDate').setValue(_defaultValues['stopDate']);
			} else {
				_resources.popups[popUpNm].getField('deff').setValue(_self.getDefault('curBusDate'));
				_resources.popups[popUpNm].getField('stopDate').setValue(_self.getDefault('stopDate'));
			}
		}
		
		//Germany will need to display the acctGrp description from linked account popUp, not for other clients
		//CRMREL group type also require acctGrp description in linked account popUp
		,enableGrpDesc: function (grpType,popUpNm) {
			if (_AFTACCTGRPTYPE == grpType || _self.getConfig(grpType, "ShowDescInActLnk") == 'YES') {
				_resources.popups[popUpNm].getField('grpDesc').show();
			} else {
				_resources.popups[popUpNm].getField('grpDesc').hide();
			}
		}
		
		//Germany needs to disable Deff/StopDates based on config. table
		,enableDisableDates: function (grpType, popUpNm) {
			if (_self.getConfig(grpType, "DisableDeff") == 'YES') {
				_resources.popups[popUpNm].getField('deff').disable();
				_resources.popups[popUpNm].getField('deff').allowBlank = true;
			} else {
				_resources.popups[popUpNm].getField('deff').enable();
				_resources.popups[popUpNm].getField('deff').allowBlank = false;
			}
			if (_self.getConfig(grpType, "DisableStopDate") == 'YES') {
				_resources.popups[popUpNm].getField('stopDate').disable();
				_resources.popups[popUpNm].getField('stopDate').allowBlank = true;
			} else {
				_resources.popups[popUpNm].getField('stopDate').enable();
				_resources.popups[popUpNm].getField('stopDate').allowBlank = false;
			}
		}
		
		//acctGrp defaulting
		,setDefaultDropdownVal: function (grpType) {
			defaultDropdowns(grpType);
		}
		//Germany reset grids record nums from 25 to 100
		,loadRequestRecNums: function () {
			loadRequestRecNums();
		}
		//Germany acctGrp
		,setFormForACBRLK: function (grpType) {
			setUpdatedFormForACBRLK(grpType);
		}
		//Germany acctGrp PopUp 
		,setAcctGrpPopUpForACBRLK: function () {
		  setUpdatedAcctGrpPopUpForACBRLK();
		}
		//Germany Linked accounts PopUp
		,setLinkedAcctPopUpForACBRLK: function () {
		   setUpdatedLinkedAcctPopUpForACBRLK();
		}
		//Germany acctGrp GroupID length change
		,setAcctGrpMaxLengthFromConfig: function (grpType,popupNm) {
		    setMaxLengthFromConfig(grpType,popupNm);
		}
		//Return, to be called for multiple Group Types change
		,clearGrid:	function (name) {
			clearGrid(name);
	    }
	
		,enablePrimaryAcct: function (appli)
		{
			if (appli) {
				_resources.popups['linkedAcctPopup'].getField('primaryAcct').show();
			}
			else {
				_resources.popups['linkedAcctPopup'].getField('primaryAcct').hide();
			}		
		}
		//Returns true if value is numeric
		,isNumber : function(value) {
		    return isNumber(value);
		}
		//To set default Group type from config
		,defaultGrpTypeDrpdwn : function(grpType) {
		    defaultGrpTypeDrpdwn(grpType);
		}
	}	
}