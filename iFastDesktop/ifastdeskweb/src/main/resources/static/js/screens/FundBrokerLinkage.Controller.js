/*********************************************************************************************
 * @file	FundBrokerLinkage.controller.js
 * @author	Winnie Cheng
 * @desc	Controller JS file for Fund Group screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Fund Broker Linkage
 *				
 *  History : 
 *
 *  23 Sep. 2016 Winnie Cheng. P0256381  T83741 CHG0045765 Fund Broker Linkage for Germany
 *				- Created.
 *
 *  13 Oct 2016 Winnie Cheng. P0256381  T83939 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, layout adjustment and bug fixing
 *
 *  20 Oct 2016 Winnie Cheng. P0256381  T84056 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, imp. Delete error handing for fund broker linage
 *                  - Adding duplication validation in popUp stage
 *
 *  28 Oct 2016 Winnie Cheng. P0256381  T84097 DFT0068689 CHG0045765 Fund Broker Linkage for Germany
 *                  - After searching without parameter, "ADD" button should be enabled
 *
 *  20 Nov 2016 Winnie Cheng. P0256381   CHG0045765 Fund Group for Germany
 *                  - gotoScreen new > Fund Group
 */

DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'add';
	var _DEL = 'del';
	var _INQ = 'inq';
	
	var _SEARCHBYACCT = 'Acct';
	var _SEARCHBYOTHERREFERENCE = 'OthRef';
	var _SEARCHBYISIN = '02';
	var _SEARCHBYWKN = '03';
	var _SEARCHBYFNDGRPNAME = '04';
	var _SEARCHBYFNDGRPCODE = '05';
	var _GROUPTYPE = 'FNBRLK';
	var _LINKAGEERRORCODE = '1672';
	
	// create following new services
	var _dtFundBrkLinkInqService = "dtFndBrkLkInq"; 
	var _dtFundBrkLinkProcService = "dtFndBrkLkProc";
	var _dtFundBrkLinkValService = "dtFndBrkLkVal";

	var _initResponseXml = null;
	var _nextUUID = 1;

	var _currentSearch	= new Array();
	var _permissions	= new Array();
	
	var _searchedFlag = false;
	var _nextStartRecNum = 1;
	var _requestRecNum = 100; 


	// PRIVATE METHODS ****************************************
	/** Store user permission **/
	function storePermissions(initViewXML) {
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function populateDropdownList(initViewXML) {
		_resources.fields['acctGrpSearchBy'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'AcctSearchList']"));
		_resources.fields['fundGrpClassSearchBy'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'FundSearchList']"));
		_resources.fields['fundBrokerSearchBy'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'FnBrkSearchList']"));

		_resources.fields['acctGrpSearchBy'].setValue(IFDS.Xml.getNodeValue(initViewXML, "/*//ListSelection[@id = 'AcctSearchList']"));
		_resources.fields['fundGrpClassSearchBy'].setValue(IFDS.Xml.getNodeValue(initViewXML, "/*//ListSelection[@id = 'FundSearchList']"));
		_resources.fields['fundBrokerSearchBy'].setValue(IFDS.Xml.getNodeValue(initViewXML, "/*//ListSelection[@id = 'FnBrkSearchList']"));
	} 
	
	function doSearch(runMode, append) {
		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(dataXML, 'acctSrch', _currentSearch['acctSrch']);  
		IFDS.Xml.addSingleNode(dataXML, 'acctSrchValue', _currentSearch['acctSrchValue']);
		
		IFDS.Xml.addSingleNode(dataXML, 'fundSrch', _currentSearch['fundSrch']);
		IFDS.Xml.addSingleNode(dataXML, 'fundSrchValue', _currentSearch['fundSrchValue']);
		IFDS.Xml.addSingleNode(dataXML, 'fund', _currentSearch['fund']);
		IFDS.Xml.addSingleNode(dataXML, 'class', _currentSearch['class']);
		
		IFDS.Xml.addSingleNode(dataXML, 'fundBrokerSrch', _currentSearch['fundBrokerSrch']);
		IFDS.Xml.addSingleNode(dataXML, 'fundBrokerSrchValue', _currentSearch['fundBrokerSrchValue']);
		
		var requestRecNum = _requestRecNum;
		var startRecNum = _nextStartRecNum;

		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?startRecNum:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', requestRecNum);
		
		// call service 
		DesktopWeb.Ajax.doSmartviewAjax(_dtFundBrkLinkInqService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])	
        
		function responseHandler(success, responseXML) {
			_searchedFlag = true;
			// hanldle response
			if (success){
				var fundBrokerLinkageNode = IFDS.Xml.getNode(responseXML, '//FundBrokerEligs'); 
				if (fundBrokerLinkageNode) {
				
					// Fund Group Linkage
						if (append) {
							_resources.grids['fndBrkLinkage'].appendData(IFDS.Xml.getNode(responseXML, '//FundBrokerEligs'));
						}else {
							_resources.grids['fndBrkLinkage'].loadData(IFDS.Xml.getNode(responseXML, '//FundBrokerEligs'));
						}
						
						_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
						
						if (_nextStartRecNum) {
							_resources.grids['fndBrkLinkage'].enableButton('moreBtn');
						} else {
							_resources.grids['fndBrkLinkage'].disableButton('moreBtn');
						}
				}
				//enable reset button
				_resources.buttons['resetBtn'].enable();
				updateFundBrokerLinageGridButtons(null);
			} else {
				if (_permissions[_self.ADD]) { //enable Add button init
					_resources.grids['fndBrkLinkage'].enableButton('addBtn'); 
				}
			}
		}
	}

	function updateFndGrpLinkageRecord(data, action) {
		switch (action) {
			case _ADD: {
				data['version']  = '0';
				data['hasMoreLinkedFunds'] = 'no';
				data['errMsg'] = '';
				data['runMode'] = _ADD;
				_resources.grids['fndBrkLinkage'].addRecord(data);
				_resources.grids['fndBrkLinkage'].selectLastRecord();
				break;
			}
			case _DEL: {
				var fndBrkLinkageRec = _resources.grids['fndBrkLinkage'].getSelectedRecord();
				if (fndBrkLinkageRec.data['runMode'] == _ADD)  {
					_resources.grids['fndBrkLinkage'].removeSelectedRecord();
					_resources.grids['fndBrkLinkage'].selectFirstRecord();
				} else {
					fndBrkLinkageRec.data['runMode'] = _DEL;
					fndBrkLinkageRec.commit();
					var selectedSubmissionIndex  = _resources.grids['fndBrkLinkage'].store.indexOf(fndBrkLinkageRec);
					if (selectedSubmissionIndex == 0){
						setSelectedRow('fndBrkLinkage', selectedSubmissionIndex + 1);
					} else {
						_resources.grids['fndBrkLinkage'].selectFirstRecord();
					}
					_resources.popups['fundBrkLink'].hide();		
				}
				break;
			}
		}
		updateFundBrokerLinageGridButtons(null);
	}
	
	function setSelectedRow(gridName, index) {
		_resources.grids[gridName].setSelectedRecord(index);
	}
	
	function updateFundBrokerLinageGridButtons(record) {
		var grid = _resources.grids['fndBrkLinkage'];

		if (_permissions[_self.ADD]) {
			grid.enableButton('addBtn'); 
		} else {
			grid.disableButton('addBtn'); 
		}

		if (record) {
			if (_permissions[_self.DEL]) {
				grid.enableButton('delBtn'); 
			} else {
				grid.disableButton('delBtn'); 
			}
			if (_permissions[_self.INQ]) {
				grid.enableButton('viewFundGroupBtn'); 
			} else {
				grid.disableButton('viewFundGroupBtn'); 
			}
		} else {
			if (grid.store.getCount() <= 0) {
				grid.disableButton('delBtn');
				grid.disableButton('viewFundGroupBtn'); 
			}
		}
	}
	
	function validateSearchCriteria() {
		var flag = true;
		clearGrid('fndBrkLinkage');
		if (isAllRowsFieldsEmpty()) {
			DesktopWeb.Util.displayInfo(_translationMap['IsAllSearchFieldsEmpty']);		
			_resources.fields['acctGrpSearchBy'].focus();
			flag = false;
		} else if (isAllSearchBy2Empty()) {
			DesktopWeb.Util.displayInfo(_translationMap['IsThreeSearchValueFieldsEmpty']);	
			_resources.fields['searchByAccts'].focus();
			flag = false;
		}
		return flag;
		
		function isAllRowsFieldsEmpty() {
			var flag = false;
			if (isRowAllGrpsEmpty('acctGrpSearchBy','searchByAccts', 'searchByAcctGrp')
				&& isRowAllGrpsEmpty('fundGrpClassSearchBy','searchByFundClass', 'searchByFundGrp')
				&& isRowAllGrpEmpty('fundBrokerSearchBy','searchByFundBroker')) {
				flag = true;
			}
			return flag;
		}	
	
		function isAllSearchBy2Empty() {
			var flag = false;
			if (isRowGrpsEmpty('searchByAccts', 'searchByAcctGrp')//Account & Account Group
				&& isRowGrpsEmpty('searchByFundClass', 'searchByFundGrp')//Fund/Class & Fund Group
				&& isRowGrpEmpty('searchByFundBroker')) {//Fund Broker
				flag = true;
			}
			return flag;
		}	

		function isRowAllGrpsEmpty(searchBy, searchByValue1, searchByValue2) {
			var flag = false;
			var searchBy = _resources.fields[searchBy].getValue();
			var searchByValue1 = _resources.fields[searchByValue1].getValue();
			var searchByValue2 = _resources.fields[searchByValue2].getValue();
			if (Ext.isEmpty(searchBy) && Ext.isEmpty(searchByValue1) && Ext.isEmpty(searchByValue2)) {
				flag = true;
			}
			return flag;
		}
		//fund broker
		function isRowAllGrpEmpty(searchByName, searchByName1) {//for Fund Broker field
			var flag = false;
			var searchBy = _resources.fields[searchByName].getValue();
			var searchByValue1 = _resources.fields[searchByName1].getValue();
			if (Ext.isEmpty(searchBy) && Ext.isEmpty(searchByValue1)) {
				flag = true;
			}
			return flag;
		}
	
		function isRowGrpsEmpty(searchByName1, searchByName2) {
			var flag = false;
			
			var searchByValue1 = _resources.fields[searchByName1].getValue();
			var searchByValue2 = _resources.fields[searchByName2].getValue();
			if (Ext.isEmpty(searchByValue1) && Ext.isEmpty(searchByValue2)) {
				flag = true;
			}
			return flag;
		}
		//fund broker
		function isRowGrpEmpty(searchByName1) {
			var flag = false;
			var searchByValue1 = _resources.fields[searchByName1].getValue();
			if (Ext.isEmpty(searchByValue1)) {
				flag = true;
			}
			return flag;
		}
	}
	
	function clearGrid(name) {
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
		if (_permissions[_self.ADD]) {
			_resources.grids['fndBrkLinkage'].enableButton('addBtn');
		} 
	}

	function validateUpdateFndBrkLinage(data, action) {
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		var fundBrokerElig = IFDS.Xml.addSingleNode(dataXML, 'FundBrokerElig');
		var runMode = action;

		IFDS.Xml.addSingleNode(fundBrokerElig, 'runMode', runMode);
		IFDS.Xml.addSingleNode(fundBrokerElig, 'fundBrokerUUID', data['fundBrokerEligID']);
		IFDS.Xml.addSingleNode(fundBrokerElig, 'groupID', data['acctGroupID']);
		IFDS.Xml.addSingleNode(fundBrokerElig, 'fundGroup', data['fundGroup']);
		IFDS.Xml.addSingleNode(fundBrokerElig, 'fundBrokerCode', data['fundBrokerCode']);

		IFDS.Xml.addSingleNode(fundBrokerElig, 'version', data['version']);

		// call service - validation service
        DesktopWeb.Ajax.doSmartviewAjax(_dtFundBrkLinkValService, {ignoreWarning: true}, dataXML, responseHandler, _translationMap['Validating']);
			
		function responseHandler(success, responseXML, contextErrors, contextWarnings) {
			if (success) {
				_self.updatesFlag = true;
				//populate information in Grid
				data['acctGrpDesc'] = IFDS.Xml.getNodeValue(responseXML, '//Info/acctGrpDesc');
				data['fundGrpDesc'] = IFDS.Xml.getNodeValue(responseXML, '//Info/fundGrpDesc');
				data['fundBrokerName'] = IFDS.Xml.getNodeValue(responseXML, '//Info/fundBrokerName');	
				
				if (contextWarnings!= null && contextWarnings.length > 0) {
					var warningText =IFDS.Xml.getNodeValue(contextWarnings[0], 'text');
					for (var i = 1; i < contextWarnings.length; i++) {
						warningText += "<br/>" + IFDS.Xml.getNodeValue(contextWarnings[i], 'text')
						//This message is used to keep in grid which has to use &lt; &gt;
						//because XML cannot extract XML which has "<" or ">"
						warningText += "&lt;br/&gt;" + IFDS.Xml.getNodeValue(contextWarnings[i], 'text')
					}	
					DesktopWeb.Util.displayWarning(warningText, performDeleteFundBrkLinkage, Ext.Msg.OKCANCEL);
					_self.updatesFlag = true;
				} else {
					//adding to call handling after validation
					updateFndGrpLinkageRecord(data, action);
				}
				_resources.popups['fundBrkLink'].hide();
			} 
			//callBack to get Warning message from response handler
			function performDeleteFundBrkLinkage(confirm){
				if (confirm == 'ok') {
					updateFndGrpLinkageRecord(data, action);//calling handler after "Yes" is pressed
				}
			}
		}
	}

	function buildUpdateXML(isUpdate) {	
		var updateDelRecords = _resources.grids['fndBrkLinkage'].getStore().queryBy(function(record){ return record.get('runMode') == _DEL });
		var updateAddRecords = _resources.grids['fndBrkLinkage'].getStore().queryBy(function(record){ return record.get('runMode') == _ADD });

		var updateXML = IFDS.Xml.newDocument('data');

		if ((updateAddRecords == null || updateAddRecords.getCount() < 0)
			&& (updateDelRecords == null || updateDelRecords.length < 0) ) { 
			return null;
		}
		
		if (!isUpdate) { // This is for validation before committing.
			IFDS.Xml.addSingleNode(updateXML, 'runMode', 'validation');
		}

		var fndBrkLinkageXML = IFDS.Xml.addSingleNode(updateXML, 'FundBrokerEligs');

		buildUpdateXMLAll(fndBrkLinkageXML, updateDelRecords );
		buildUpdateXMLAll(fndBrkLinkageXML, updateAddRecords );
		
		return updateXML;

		function buildUpdateXMLAll(context, updatedRecords) {
			if (updatedRecords != null) {
				for (var i = 0; i < updatedRecords.getCount(); i++) {
					buildUpdateXMLByRecord(context, updatedRecords.itemAt(i));
				} 
			}
		}
		
		function buildUpdateXMLByRecord(context, record) {
				var fndBrkLinkXML = IFDS.Xml.addSingleNode(context, 'FundBrokerElig');
				IFDS.Xml.addAttribute(fndBrkLinkXML, 'RecordSource', record.get('fundBrokerEligID'));
				IFDS.Xml.addSingleNode(fndBrkLinkXML, 'runMode', record.get('runMode'));
				IFDS.Xml.addSingleNode(fndBrkLinkXML, 'fundBrokerUUID', record.get('fundBrokerEligID'));
				IFDS.Xml.addSingleNode(fndBrkLinkXML, 'groupID', record.get('acctGroupID'));
				IFDS.Xml.addSingleNode(fndBrkLinkXML, 'fundGroup', record.get('fundGroup'));
				IFDS.Xml.addSingleNode(fndBrkLinkXML, 'fundBrokerCode', record.get('fundBrokerCode'));
				IFDS.Xml.addSingleNode(fndBrkLinkXML, 'version', record.get('version'));
		}
	}

	function storeContextErrors(errorNodes) {
		//reset deleted records runmode in order to display the deleted fundGrp with ERROR
		var delRecords  = _resources.grids['fndBrkLinkage'].getStore().queryBy(function(record){ return record.get('runMode') == 'del' });
		for (var i = 0; i < errorNodes.length; i++) {
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			var errorCode = IFDS.Xml.getNodeValue(errorNodes[i], 'errorCode');
			var errorUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			if (errorCode == _LINKAGEERRORCODE) {
				for (var i = 0; i < delRecords.getCount(); i++) {
					var fundBrkLinkUUID = delRecords.itemAt(i).data['fundBrokerEligID'];
					if ( errorUUID == fundBrkLinkUUID) {
						delRecords.itemAt(i).set('runMode', '');//change runMode as blank
					}
				}
			}
		}
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++) {
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			//XML design
			var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			
			// Update fndBrkLinkage grid
			var recordIndex = _resources.grids['fndBrkLinkage'].getStore().find('fundBrokerEligID', uuid); 
			var fndBrkLinkageRecord = _resources.grids['fndBrkLinkage'].getStore().getAt(recordIndex);
			fndBrkLinkageRecord.set('errMsg', errMsg);
			_resources.grids['fndBrkLinkage'].getStore().commitChanges();
			if (firstErrRecIndex == -1) firstErrRecIndex = recordIndex;
		}
	
		if (firstErrRecIndex== -1) {
			_resources.grids['fndBrkLinkage'].getSelectionModel().selectFirstRow();
		} else {
			_resources.grids['fndBrkLinkage'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['fndBrkLinkage'].focusRow(firstErrRecIndex);
		}
	}
		
	//Go to Fund Group screen
    function goToScreenOnPopup(screenName, target) {
        var urlParams = {};
        for (var i in DesktopWeb._SCREEN_PARAM_MAP) {
            if (i !== 'screen'){
                urlParams[i] = DesktopWeb._SCREEN_PARAM_MAP[i];
            }
        }
        urlParams['screen'] = screenName;
        urlParams['fromScreen'] = 'FundBrokerLinkage';

		var selectedLinkageRec = _resources.grids['fndBrkLinkage'].getSelectedRecord();
		var fundGroup = selectedLinkageRec.data['fundGroup'];
        urlParams['fundGroupCode'] = fundGroup;
		urlParams['grpType'] = _GROUPTYPE;
		urlParams['extLayout'] = 'popup';
		
		DesktopWeb.Util.goToScreen(screenName, urlParams, target);
    }
	
	function isAcctGrpSelected (code) {
		if (_SEARCHBYACCT == code || _SEARCHBYOTHERREFERENCE == code) {
			return true;
		} else {
			return false;
		}
    }
	
	function isFundGrpSelected (code) {
		if (_SEARCHBYFNDGRPNAME == code || _SEARCHBYFNDGRPCODE == code) {
			return true;
		} else {
			return false;
		}
    }
	
	function setAcctGroupCriterias () {
	    _currentSearch['acctSrch'] == '';
		_currentSearch['acctSrchValue']  = '';
		if (_resources.fields['acctGrpSearchBy'].getValue().length > 0 ) {
			_currentSearch['acctSrch'] = _resources.fields['acctGrpSearchBy'].getValue();

			if (_resources.fields['searchByAccts'].getValue().length  > 0) {
				if (_currentSearch['acctSrch'] != null && 'OthRef' == _currentSearch['acctSrch']) {
					_currentSearch['acctSrchValue'] = _currentSearch['othRef'];
				} else {
					_currentSearch['acctSrchValue'] = _currentSearch['acctNum'];
				}
			} else if (_resources.fields['searchByAcctGrp'].getValue().length > 0) {
				_currentSearch['acctSrchValue'] = _currentSearch['acctGroupID'] ;
			} 
		}
	}
	
	//Fund Group, fund/class
	function setFundGroupCriterias() {
		_currentSearch['fundSrch'] == '';
		_currentSearch['fundSrchValue']  = '';

		if (_resources.fields['fundGrpClassSearchBy'].getValue().length > 0 ) {
			_currentSearch['fundSrch'] = _resources.fields['fundGrpClassSearchBy'].getValue(); 
			if (_currentSearch['fundSrch'] != null && _currentSearch['fundSrch'].length > 0) {
				if (_resources.fields['searchByFundClass'].getValue().length  > 0) {
					if (_currentSearch['fundSrch'] != null && _SEARCHBYISIN == _currentSearch['fundSrch']) {
					    _currentSearch['fundSrchValue'] = _currentSearch['isin'];
					} else if (_SEARCHBYWKN == _currentSearch['fundSrch']) {
						_currentSearch['fundSrchValue'] = _currentSearch['wkn'];
					} 
				} else if (_resources.fields['searchByFundGrp'].getValue().length > 0) {
					_currentSearch['fundSrchValue'] = _resources.fields['searchByFundGrp'].getValue();
					if (_currentSearch['fundSrch'] != null && _SEARCHBYFNDGRPNAME == _currentSearch['fundSrch']) {
						_currentSearch['fundGrpClassSearchBy'] = _currentSearch['fundGroupCode'] ;
						_currentSearch['fundGrpClassSearchBy'] = _currentSearch['fundGroupCode'] ;
					} else {
						_currentSearch['fundGrpClassSearchBy'] = _currentSearch['fundGroupCode'] ;
					}
					_currentSearch['fund'] == '';
					_currentSearch['class']  = '';
				}
			} 
		}
	}
	
	function setFundBrokerCriterias() {
		_currentSearch['fundBrokerSrch'] == '';
		_currentSearch['fundBrokerSrchValue']  = '';
		if (_resources.fields['fundBrokerSearchBy'].getValue().length > 0 ) {
			_currentSearch['fundBrokerSrch'] = _resources.fields['fundBrokerSearchBy'].getValue();
			if (_currentSearch['fundBrokerSrch'] != null && _currentSearch['fundBrokerSrch'].length > 0) {
				if (_resources.fields['searchByFundBroker'].getValue().length > 0) {
					_currentSearch['fundBrokerSrchValue'] = _resources.fields['searchByFundBroker'].getValue();
				}
			}
		} 
	}
		
	// PUBLIC ITEMS *************************************
	return {
		INQ:  _INQ
		,ADD: _ADD
		,DEL: _DEL
		,YES: 'yes'
		,NO: 'no'
		,FROM_SCREEN: null
		,updatesFlag: false
		,currentSearch: _currentSearch
						
		,init: function(res) {	
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;			
			 // Call init service
			var viewParamXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(viewParamXML, 'runMode', 'init');
			
			DesktopWeb.Ajax.doSmartviewAjax(_dtFundBrkLinkInqService, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Searching'])
						
			function responseHandler(success, responseXML) {	
				if (success) { // Handle response
				
					_initResponseXml = responseXML;

					// Load permission
					storePermissions(responseXML);
					
					// Load dropdown if success
					populateDropdownList(responseXML);

					if (_permissions[_self.ADD]) { //enable Add button init
						_resources.grids['fndBrkLinkage'].enableButton('addBtn'); 
					}
			   }
			}
		}
		
		,clickHandle_searchBtn: function() {
			if (_self.updatesFlag) {
				DesktopWeb.Util.displayDiscardPrompt(performSearch);
			} else {
				performSearch(true);
			}
			function performSearch(confirm){
				if (confirm){
					if (validateSearchCriteria()) {
						_self.updatesFlag = false;
						
						_self.setAcctGroupCriterias(); 
						_self.setFundGroupCriterias(); 
						_self.setFundBrokerCriterias(); 
						_nextStartRecNum = 1;

						clearGrid('fndBrkLinkage');
					
						doSearch('reload', false);
					}
				}
			}
		}
		,setAcctGroupCriterias: function() {	
			setAcctGroupCriterias();
		}
		
		,setFundGroupCriterias: function() {	
			setFundGroupCriterias();
		}
		
		,setFundBrokerCriterias: function() {	
			setFundBrokerCriterias();
		}
		
		,handleAcctsGrpsSearchChange: function(code) {
			if (isAcctGrpSelected(code)) {
					_resources.fields['searchByAcctGrp'].reset();
					_resources.fields['searchByAccts'].reset();
					_resources.fields['searchByAccts'].show();
					_resources.fields['searchByAcctGrp'].hide();
			} else {
					_resources.fields['searchByAccts'].reset();
					_resources.fields['searchByAcctGrp'].reset();
					_resources.fields['searchByAcctGrp'].show();
					_resources.fields['searchByAccts'].hide();
			}
		}
		
		,handleFundGrpClassSearchChange: function(code) {
			if (isFundGrpSelected(code)) {
					_resources.fields['searchByFundGrp'].reset();
					_resources.fields['searchByFundClass'].reset();
					_resources.fields['searchByFundGrp'].show();
					_resources.fields['searchByFundClass'].hide();
			} else {
					_resources.fields['searchByFundGrp'].reset();
					_resources.fields['searchByFundClass'].reset();
					_resources.fields['searchByFundClass'].show();
					_resources.fields['searchByFundGrp'].hide();
			}
		}
		
		,resetFields: function(fld) {	
			_resources.fields[fld].reset();
		}
		
		,disableFields: function(fld) {	
			_resources.fields[fld].disable();
		}
		
		,getAcctOtherRefNumber : function(rec) {
			_currentSearch['othRef'] = rec.data['othRef'];
			_currentSearch['acctNum'] = rec.data['acctNum'];
		}
		
		,getAcctGrpDesc : function(rec) {
			_currentSearch['acctGroupDesc'] = rec.data['acctGroupDesc'];
			_currentSearch['acctGroupID'] = rec.data['acctGroupCode'];
		}
		
		,getFundGrpDesc : function(rec) {
			_currentSearch['fundGroupDesc'] = rec.data['fundGroupDesc'];
			_currentSearch['fundGroupCode'] = rec.data['fundGroupCode'];
			_currentSearch['fund'] = '';
			_currentSearch['class'] = '';
		}
		
		,getFundClassSuggestFields : function(rec) {
			_currentSearch['fund'] = rec.data['fund'];
			_currentSearch['class'] = rec.data['class'];
		    _currentSearch['isin'] = rec.data['isin'];
			_currentSearch['wkn'] = rec.data['wkn'];
		}
		
		,getNewFndBrkLinageUUID: function() {
			return "TMPFUNDGRPLINK" + (_nextUUID++);
		}

		,doReset: function() {
			if (_self.updatesFlag) {
				DesktopWeb.Util.displayDiscardPrompt(performReset);
			} else {
				performReset(true);
			}
			function performReset(confirm) {
				if (confirm){
					_self.updatesFlag = false; 
					_resources.fields['acctGrpSearchBy'].enable();
					_resources.fields['acctGrpSearchBy'].reset();
					_resources.fields['searchByAccts'].disable();
					_resources.fields['searchByAccts'].reset();
					_resources.fields['searchByAcctGrp'].disable();
					_resources.fields['searchByAcctGrp'].reset();
					
					_resources.fields['fundGrpClassSearchBy'].enable();
					_resources.fields['fundGrpClassSearchBy'].reset();
					_resources.fields['searchByFundGrp'].disable();
					_resources.fields['searchByFundGrp'].reset();
					_resources.fields['searchByFundClass'].disable();
					_resources.fields['searchByFundClass'].reset();
					
					_resources.fields['fundBrokerSearchBy'].enable();
					_resources.fields['fundBrokerSearchBy'].reset();
					_resources.fields['searchByFundBroker'].disable();
					_resources.fields['searchByFundBroker'].reset();
					
					_resources.grids['fndBrkLinkage'].clearData();		
					updateFundBrokerLinageGridButtons(null);	
					_resources.buttons['resetBtn'].disable();	
				}
		    }
		}
		
		,clickHandle_moreBtn: function() {
			doSearch('reload', true);
		}

		,validatefndBrkLinage: function(data, action) {
			validateUpdateFndBrkLinage(data, action)
		}

		,openActionPopup: function(action) {	
			var popup = _resources.popups['fundBrkLink'];	
			if (action != _DEL) {
				popup.show();
			} else {
				popup.hide();
			}
			popup.init(action);
		}
		
		,selectlinkedFundBrk: function(record) {
			updateFundBrokerLinageGridButtons(record);
		}

		,doUpdate: function() {
			var updateStatus = null;	
			_updateXML = buildUpdateXML(true);
			
			DesktopWeb.Ajax.doSmartviewUpdate(_dtFundBrkLinkProcService, null, IFDS.Xml.cloneDocument(_updateXML), responseHandler, _translationMap['ProcMsg_Saving']);			

			function responseHandler(success, responseXML, contextErrors) {
				if (success) {
					updateStatus = DesktopWeb._SUCCESS;
				} else {
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}		
			
		,doCommitValidate: function() {
			var updateStatus = null;
			_updateXML = buildUpdateXML(false);
			if (_updateXML != null) {
				DesktopWeb.Ajax.doSmartviewAjax(_dtFundBrkLinkProcService, null, IFDS.Xml.cloneDocument(_updateXML), responseHandler, _translationMap['ProcMsg_Saving'], Ext.Msg.OKCANCEL);			
			} else {
				DesktopWeb.Util.closeScreenWithDialog();
			}
			function responseHandler(success, responseXML, contextErrors, warnings, btn) {
				if (success) {				
					if (btn == null || btn == 'ok') {
						DesktopWeb.Util.commitScreen();
					}
				} else  {
					storeContextErrors(contextErrors);
				}
			}
		}
		
		,clickHandle_ViewFundGrpBtn: function () {
			var popup = _resources.popups['fundGrpPopup'];
			popup.show();
			goToScreenOnPopup('FundGroup', "iframePopup");
        }
	}	
}