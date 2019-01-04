/*********************************************************************************************
 * @file	FundGroup.controller.js
 * @author	Winnie Cheng
 * @desc	Controller JS file for Fund Group screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Fund Group
 *				
 *  History : 
 *
 *  23 Sep. 2016 Winnie Cheng. P0256381 T83741 CHG0045765 Fund Broker Linkage for Germany
 *					- Created.
 *
 *  13 Oct 2016 Winnie Cheng. P0256381  T83939 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, imp. Delete error handing, layout adjustment and bug fixing
 *
 *  20 Oct 2016 Winnie Cheng. P0256381  T84056 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, imp. Delete error handing for linked Fund Group
 *                  - Adding duplication validation in popUp stage
 *
 *  28 Oct 2016 Winnie Cheng. P0256381  T84097 DFT0068689 CHG0045765 Fund Broker Linkage for Germany
 *                  - remove a xml tag-lingageConf that caused F5 SQL injection failure
 *
 *  8 Nov 2016 Winnie Cheng. P0256381  T84187 DFT0069088 CHG0045765 Fund Broker Linkage for Germany
 *                  - remove additional popUp
 *
 *  17 Nov 2016 Winnie Cheng. P0256381  T84279 DFT0069397 CHG0045765 Fund Broker Linkage for Germany
 *                  - gotoscreen, minor fixing for last fundGrp's buttons
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
	var _FND = 'fnd';
	var _SEARCHFOR = 'FG';
	var _FNBRLK = 'FNBRLK';
	var _SETGRPTYPE = 'Fd Broker Link Fund Group';
	var _SETFUNDGRP = 'Fund Group';
	var _LINKAGEERRORCODE = '1669';
	var _LINKAGEERRORCODE2 = '1672';
	
	var _initXML = null;
	var _updateXML = null;

    var _nextStartRecNum = 1;
	var _requestRecNum = 100;
	var _requestRecNumDetl = 100;
	
	var _nextUUID = 1;
	
	var _currentSearch	= new Array();
	var _permissions	= new Array();

	var _dtFundGrpInqService = "dtFundGrpInq";
	var _dtFundGrpProcService = "dtFundGrpProc";
	var _dtFundGrpValService = "dtFundGrpVal";
	
	var _searchedFlag = false;
	var _fromScreen = null;
	
	// PRIVATE METHODS ****************************************	
	/** Store user permission **/
	function storePermissions(initViewXML) {
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function populateDropdownList() {
		try {
			_resources.fields['grpType'].getStore().loadData(IFDS.Xml.getNodes(_initXML,"//List[@listName='GroupTypeList']"));
			_resources.popups['fundGrpPopup'].getField('grpType').getStore().loadData(IFDS.Xml.getNodes(_initXML,"//List[@listName='GroupTypeList']"));
			_currentSearch['grpType'] = IFDS.Xml.getNodeValue(_initXML, "//ListSelection[@id = 'GroupTypeList']");
			_resources.fields['grpType'].setValue(_currentSearch['grpType']); 
			_resources.fields['searchFor'].getStore().loadData(IFDS.Xml.getNodes(_initXML,"//List[@listName='SearchList']"));
			_resources.fields['searchFor'].setValue(IFDS.Xml.getNodeValue(_initXML, "//ListSelection[@id = 'SearchList']"));
			setSearchValueField();
		} catch(err) {
			DesktopWeb.Util.displayError("Cannot load dropdown list", function(){disableScreen();});
		}
	}
	
	function doSearch(runMode, append) {
		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', runMode);

		var requestRecNum = _requestRecNum;
		var startRecNum = _nextStartRecNum;

		if (runMode == 'reloadDetl') {
			var selectedRecord = _resources.grids['fundGrp'].getSelectedRecord();
			requestRecNum = _requestRecNumDetl;
			
			startRecNum = selectedRecord.data['nextStartRecordNumLinkedFund'];
			IFDS.Xml.addSingleNode(dataXML, 'grpType', _currentSearch['grpType']);
			IFDS.Xml.addSingleNode(dataXML, 'searchFor', _currentSearch['searchFor']);
			IFDS.Xml.addSingleNode(dataXML, 'fundGroup', selectedRecord.data['fundGroup']);
			IFDS.Xml.addSingleNode(dataXML, 'fund', _currentSearch['fund']);
			IFDS.Xml.addSingleNode(dataXML, 'class', _currentSearch['class']);
			
		}else {
			IFDS.Xml.addSingleNode(dataXML, 'grpType', _currentSearch['grpType']);
			IFDS.Xml.addSingleNode(dataXML, 'searchFor', _currentSearch['searchFor']);
			IFDS.Xml.addSingleNode(dataXML, 'fundGroup', _currentSearch['searchValue']);
			IFDS.Xml.addSingleNode(dataXML, 'fund', _currentSearch['fund']);
			IFDS.Xml.addSingleNode(dataXML, 'class', _currentSearch['class']);
		}
		
		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?startRecNum:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', requestRecNum);

		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_dtFundGrpInqService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
		
		function responseHandler(success, responseXML) {
			_searchedFlag = true;
			// hanldle response
			if (success) {
				var fundGrpNode = IFDS.Xml.getNode(responseXML, '//FundGrps/FundGrp');
				if (fundGrpNode) {
					if (runMode == 'reloadDetl') {
						var newLinkedFundXml = IFDS.Xml.getNode(responseXML, '//LnkFunds/LnkFund');
						if (newLinkedFundXml) {
							var newLinkedFundsXml = IFDS.Xml.getNode(responseXML, '//LnkFunds');
							if (append) {
								var linkedFundXml = IFDS.Xml.stringToXML(selectedRecord.data['LnkFunds']);
								// Store new xml to grid data
								IFDS.Xml.appendNode(linkedFundXml, IFDS.Xml.cloneDocument(newLinkedFundsXml));
								selectedRecord.data['LnkFunds'] = IFDS.Xml.serialize(linkedFundXml);
								// Append data to grid
								_resources.grids['linkedFundClass'].appendData(newLinkedFundsXml);
							} else {
								selectedRecord.data['LnkFunds'] = IFDS.Xml.serialize(newLinkedFundsXml);
								_resources.grids['linkedFundClass'].loadData(newLinkedFundsXml);
							}
							
							// control more button
							var nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
							if (nextStartRecNum) {
								selectedRecord.data['hasMoreLinkedAccts'] = 'yes';
								selectedRecord.data['nextStartRecordNumLinkedFund'] = nextStartRecNum;
								_resources.grids['linkedFundClass'].enableButton('moreBtn');
							} else {
								selectedRecord.data['hasMoreLinkedAccts'] = 'no';
								_resources.grids['linkedFundClass'].disableButton('moreBtn');
							}
						} else {
							// Handle if there is no linked-acct in selected group
							updateLinkedFundGridButtons(null);
						}
					} else { // Fund Group
						if (append) {
							_resources.grids['fundGrp'].appendData(IFDS.Xml.getNode(responseXML, '//FundGrps'));
							
						} else {
							var data = IFDS.Xml.getNode(responseXML, '//FundGrps');
							_resources.grids['fundGrp'].loadData(IFDS.Xml.getNode(responseXML, '//FundGrps'));
						}
						
						_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
						if (_nextStartRecNum) {
							_resources.grids['fundGrp'].enableButton('moreBtn');
						} else {
							_resources.grids['fundGrp'].disableButton('moreBtn');
						}
					}
				} else {
					if (runMode == 'reloadDetl') {
						updateLinkedFundGridButtons(null);
					}
				}
				//enable reset button
				if (_fromScreen != null && _fromScreen == 'FundBrokerLinkage') {
					_resources.buttons['resetBtn'].disable();
				} else {
					_resources.buttons['resetBtn'].enable();
				}
			} else {
				updateFundGrpGridButtons(null);
			}
		}
	}

	function validateUpdateFundGrp(data, action) {
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		var fundGrpXML = IFDS.Xml.addSingleNode(dataXML, 'fundGrp');
		var runMode = action;
		if (action == _MOD) {
			var selectedFundGrpRecord = _resources.grids['fundGrp'].getSelectedRecord();
			if (selectedFundGrpRecord.data['runMode'] == _ADD) runMode = _ADD;
			data['version'] = selectedFundGrpRecord.data['version'];
		}
		IFDS.Xml.addSingleNode(fundGrpXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(fundGrpXML, 'fundGrpUUID', data['fundGrpUUID']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'grpType', data['grpType']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'fundGroup', data['fundGroup']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'grpDesc', data['grpDesc']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'version', data['version']);
		
		var updateLinkedFundRecords = _resources.grids['linkedFundClass'].getStore().queryBy(function(record){ return record.get('runMode') != '' });
		var linkedFundsXML = IFDS.Xml.addSingleNode(fundGrpXML, 'LnkFunds');
		for (var i = 0; i < updateLinkedFundRecords.getCount(); i++) {
			buildUpdateLinkedFundXML(linkedFundsXML, updateLinkedFundRecords.itemAt(i));
		} 
		
		// call service
        DesktopWeb.Ajax.doSmartviewAjax(_dtFundGrpValService, null, dataXML, responseHandler, _translationMap['Validating']);		
			
		function buildUpdateLinkedFundXML(context, updatedLinkedFund){
			var linkedFundXML = IFDS.Xml.addSingleNode(context, 'LnkFund');
			IFDS.Xml.addAttribute(linkedFundXML, 'RecordSource', updatedLinkedFund.data['lnkFundUUID']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'lnkFundUUID', updatedLinkedFund.data['lnkFundUUID']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'fund', updatedLinkedFund.data['fund']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'class', updatedLinkedFund.data['class']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'version', updatedLinkedFund.data['version']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'runMode', updatedLinkedFund.data['runMode']);
		}

		function responseHandler(success, responseXML, contextErrors, contextWarnings) {
			if (success) {
				_self.updatesFlag = true;
				updateFundGrpRecord(data, action);
				_resources.popups['fundGrpPopup'].hide();
			}	
		}
	}
	
	function validateUpdateLinkedFund(data, action) {
        // build parameter xml
		var selectedFundGrpRecord = _resources.grids['fundGrp'].getSelectedRecord();
		var dataXML = IFDS.Xml.newDocument('data');
		var fundGrpXML = IFDS.Xml.addSingleNode(dataXML, 'fundGrp');
		
		IFDS.Xml.addSingleNode(fundGrpXML, 'runMode', selectedFundGrpRecord.data['runMode']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'fundGrpUUID', selectedFundGrpRecord.data['fundGrpUUID']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'grpType', selectedFundGrpRecord.data['grpType']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'fundGroup', selectedFundGrpRecord.data['fundGroup']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'grpDesc', selectedFundGrpRecord.data['grpDesc']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'version', selectedFundGrpRecord.data['version']);
		
		var linkedFundsXML = IFDS.Xml.addSingleNode(fundGrpXML, 'LnkFunds');
		var linkedFundXML = IFDS.Xml.addSingleNode(linkedFundsXML, 'LnkFund');
		var runMode = action;

		IFDS.Xml.addSingleNode(linkedFundXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(linkedFundXML, 'lnkFundUUID', data['lnkFundUUID']);
		IFDS.Xml.addSingleNode(linkedFundXML, 'fund', data['fund']);
		IFDS.Xml.addSingleNode(linkedFundXML, 'class', data['class']);
		IFDS.Xml.addSingleNode(linkedFundXML, 'version', data['version']);

		var updateLinkedFundRecords = _resources.grids['linkedFundClass'].getStore().queryBy(function(record){
										return (record.get('runMode') != '' && record.get('lnkFundUUID') != data['lnkFundUUID']); 
									  });

		for (var i = 0; i < updateLinkedFundRecords.getCount(); i++) {
			buildUpdateLinkedFundXML(linkedFundsXML, updateLinkedFundRecords.itemAt(i));
		} 

		function buildUpdateLinkedFundXML(context, updatedLinkedFund){
			var linkedFundXML = IFDS.Xml.addSingleNode(context, 'LnkFund');
			IFDS.Xml.addAttribute(linkedFundXML, 'RecordSource', updatedLinkedFund.data['lnkFundUUID']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'lnkFundUUID', updatedLinkedFund.data['lnkFundUUID']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'fund', updatedLinkedFund.data['fund']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'class', updatedLinkedFund.data['class']);

			IFDS.Xml.addSingleNode(linkedFundXML, 'version', updatedLinkedFund.data['version']);
			IFDS.Xml.addSingleNode(linkedFundXML, 'runMode', updatedLinkedFund.data['runMode']);
		}
		
		// call service
        DesktopWeb.Ajax.doSmartviewAjax(_dtFundGrpValService, null, dataXML, responseHandler, _translationMap['Validating']);
			
		function responseHandler(success, responseXML, contextErrors) {
			if (success) {
				_self.updatesFlag = true;
				//populate Fund Name in the grid
				data['fundName'] = IFDS.Xml.getNodeValue(responseXML, '//FundInfo/fundName');
				updateLinkedFundRecord(data, action);
				_resources.popups['linkedFundPopup'].hide();
			}
		}
	}
	
	function updateFundGrpRecord(data, action) {
		switch(action) {
			case _ADD: {
				data['version']  = '0';
				data['hasMoreLinkedFunds'] = 'no';
				data['errMsg'] = '';
				_resources.grids['fundGrp'].addRecord(data);
				_resources.grids['fundGrp'].selectLastRecord();
				break;
			}
			case _MOD: {
				var fundGrpRec = _resources.grids['fundGrp'].getSelectedRecord();
				var runMode = _MOD;
				if (fundGrpRec.data['runMode'] == _ADD) runMode = _ADD;
				fundGrpRec.data['runMode'] = runMode;
				fundGrpRec.data['grpDesc'] = data['grpDesc'];
				data['errMsg'] = '';
				fundGrpRec.commit();
				break;
			}
			case _DEL: {
				var fundGrpRec = _resources.grids['fundGrp'].getSelectedRecord();
					
				if (fundGrpRec.data['runMode'] == _ADD) {
					_resources.grids['fundGrp'].removeSelectedRecord();
					_resources.grids['fundGrp'].selectFirstRecord();	
				} else {
					fundGrpRec.data['runMode'] = _DEL;
					// Set row selected back to next record if the 1st one is deleted
					var selectedSubmissionIndex  = _resources.grids['fundGrp'].store.indexOf(fundGrpRec);
					if (selectedSubmissionIndex == 0){
						setSelectedRow('fundGrp', selectedSubmissionIndex + 1);
					} else {
						_resources.grids['fundGrp'].selectFirstRecord();
					}
					fundGrpRec.commit();
					//trigger grid fire for last fundGrp Deletion
					if (_resources.grids['fundGrp'].store.getCount() < 1) {
						clearGrid('linkedFundClass');
					}
				}
				updateFundGrpGridButtons();
				break;
			}
		}
	}
	
	function updateLinkedFundRecord(data, action) {
		switch(action) {
			case _ADD: {
				data['version']  = '0';
				data['errMsg'] = '';
				_resources.grids['linkedFundClass'].addRecord(data);
				_resources.grids['linkedFundClass'].selectLastRecord();
				break;
			}
			case _DEL: {
				var linkedFundRec = _resources.grids['linkedFundClass'].getSelectedRecord();

				if (linkedFundRec.data['runMode'] == _ADD) {
					_resources.grids['linkedFundClass'].removeSelectedRecord();
					_resources.grids['linkedFundClass'].selectFirstRecord();					
				} else {
					linkedFundRec.data['runMode'] = _DEL;
					// Set row selected back to next record if the 1st one is deleted
					var selectedSubmissionIndex  = _resources.grids['linkedFundClass'].store.indexOf(linkedFundRec);
					if (selectedSubmissionIndex == 0){
						setSelectedRow('linkedFundClass', selectedSubmissionIndex + 1);
					}else{
						_resources.grids['linkedFundClass'].selectFirstRecord();
					}

					linkedFundRec.commit();
				}
				break;
			}
		}
		updateLinkedFundsOfFundGrp();
	}
	
	function updateLinkedFundsOfFundGrp() {
		var fundGrpRec = _resources.grids['fundGrp'].getSelectedRecord();
		
		var linkedFundRecords = _resources.grids['linkedFundClass'].getAllRecords();
		var linkedFundsXML = IFDS.Xml.newDocument('LnkFunds');
		
		Ext.each(linkedFundRecords, function(linkedFundRecord){
			createLinkedFundXML(linkedFundsXML, linkedFundRecord);
		});
		
		fundGrpRec.data['LnkFunds'] = IFDS.Xml.serialize(linkedFundsXML);
		
		if (fundGrpRec.data['runMode'] == null || fundGrpRec.data['runMode'].length == 0 ) {
			fundGrpRec.data['runMode'] = _FND;
		}

		fundGrpRec.commit();
		
		function createLinkedFundXML(context, record) {
			if (context) {
				var linkedFundXML = IFDS.Xml.addSingleNode(context, 'LnkFund');
				IFDS.Xml.addSingleNode(linkedFundXML, 'errMsg', record.data['errMsg']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'lnkFundUUID', record.data['lnkFundUUID']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'fund', record.data['fund']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'class', record.data['class']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'isin', record.data['isin']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'wkn', record.data['wkn']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'fundName', record.data['fundName']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'version', record.data['version']);
				IFDS.Xml.addSingleNode(linkedFundXML, 'runMode', record.data['runMode']);
			}
		}
	}
	
	function updateFundGrpGridButtons(record) {
		var grid = _resources.grids['fundGrp'];

		if (_permissions[_self.ADD]) {
			grid.enableButton('addBtn'); 
		} else {
			grid.disableButton('addBtn'); 
		}
		
		if(record) {
			if (_permissions[_self.MOD]) {
				grid.enableButton('modBtn'); 
			} else {
				grid.disableButton('modBtn'); 
			}

			if (_permissions[_self.DEL]) {
				grid.enableButton('delBtn'); 
			} else {
				grid.disableButton('delBtn'); 
			}
		} else {
			if (grid.store.getCount() <= 0) {
				grid.disableButton('modBtn');
				grid.disableButton('delBtn'); 
			}
		}
	}
	
	function updateLinkedFundGridButtons(record) {
		var grid = _resources.grids['linkedFundClass'];
		if (record == null || record.data == null || record.data < 1) {
			grid.disableButton('delBtn'); 
		} else {
			if (_permissions[_self.DEL]) {
				grid.enableButton('delBtn'); 
			} else {
				grid.disableButton('delBtn'); 
			}
		}
		if (_permissions[_self.ADD]) {
			grid.enableButton('addBtn'); 
		} 
	}

	function clearGrid(name) {
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}

	function disableScreen() {
		//only be used if the screen loads from Fund Broker Linkage screen
		_resources.fields['grpType'].disable();
		_resources.fields['searchFor'].disable();
		_resources.fields['searchByFundGrp'].disable();
		_resources.buttons['searchBtn'].disable();
		_resources.buttons['resetBtn'].disable();
		_resources.grids['linkedFundClass'].disableAllButtons();
	}
	
	function isFundClassSelected (code) {
		if ('FC' == code) {//Fund Class
			return true;
		} else {
			return false; 
		}
    }
	
	function setSearchValueField() {
		var code = _resources.fields['searchFor'].getValue();
		if (code.length > 0){
			_resources.fields['searchByFundGrp'].reset();
			_resources.fields['searchByFundClass'].reset();
			_resources.fields['searchByFundGrp'].allowBlank = false;
			_resources.fields['searchByFundClass'].allowBlank = false;
			_resources.fields['searchByFundGrp'].enable();
			_resources.fields['searchByFundClass'].enable();
		} else {
			_resources.fields['searchByFundGrp'].reset();
			_resources.fields['searchByFundClass'].reset();
			_resources.fields['searchByFundGrp'].allowBlank = true;
			_resources.fields['searchByFundClass'].allowBlank = true;
		}
	}

	function validateSearchCriteria() {
		if (_resources.fields['searchFor'].getValue().length > 0 
			&& _resources.fields['grpType'].getValue().length > 0 ) {
			
			if (_resources.fields['searchByFundClass'].getValue().length < 1
				&& _resources.fields['searchByFundGrp'].getValue().length < 1) {
				_resources.fields['searchByFundGrp'].markInvalid(_translationMap['FIELD_IS_REQUIRED']);
				_resources.fields['searchByFundClass'].markInvalid(_translationMap['FIELD_IS_REQUIRED']);
				_resources.fields['searchByFundGrp'].allowBlank = false;
				_resources.fields['searchByFundClass'].allowBlank = false;
				return false;
			} 
			if (_resources.fields['searchFor'].getValue().length < 1 && (
					_resources.fields['searchByFundClass'].getValue().length < 1
					&& _resources.fields['searchByFundGrp'].getValue().length < 1)) {
				_resources.fields['searchFor'].markInvalid(_translationMap['FIELD_IS_REQUIRED']);
				_resources.fields['searchFor'].allowBlank = false;
				return false;
			}
		} 
		return true;
	}
	
	function buildUpdateXML(isUpdate) {
		var updateFndRecords = _resources.grids['fundGrp'].getStore().queryBy(function(record){return  record.get('runMode') == _FND });
		var updateDelRecords = _resources.grids['fundGrp'].getStore().queryBy(function(record){ return record.get('runMode') == _DEL });
		var updateModRecords = _resources.grids['fundGrp'].getStore().queryBy(function(record){ return record.get('runMode') == _MOD });
		var updateAddRecords = _resources.grids['fundGrp'].getStore().queryBy(function(record){ return record.get('runMode') == _ADD });

		var updateXML = IFDS.Xml.newDocument('data');
		var totalRecs = updateFndRecords.length + updateDelRecords.length + updateModRecords.length + updateAddRecords.length;
		if (totalRecs < 1 ) {
		   return updateXML;
		}
		
		if (!isUpdate) {  // This is for validation before committing.
			IFDS.Xml.addSingleNode(updateXML, 'runMode', 'validation');
		}
		var fundGrpsXML = IFDS.Xml.addSingleNode(updateXML, 'FundGrps');
		
		buildUpdateXMLAll(fundGrpsXML, updateFndRecords );
		buildUpdateXMLAll(fundGrpsXML, updateDelRecords ); 
		buildUpdateXMLAll(fundGrpsXML, updateModRecords );
		buildUpdateXMLAll(fundGrpsXML, updateAddRecords );
		
		return updateXML;
		
		function buildUpdateXMLAll(context, updatedRecords) {
			for (var i = 0; i < updatedRecords.getCount(); i++) {
				buildUpdateXMLByRecord(context, updatedRecords.itemAt(i));
			} 
		}
		
		function buildUpdateXMLByRecord(context, record) {
			var fundGrpXML = IFDS.Xml.addSingleNode(context, 'FundGrp');
			IFDS.Xml.addAttribute(fundGrpXML, 'RecordSource', record.get('fundGrpUUID'));
			IFDS.Xml.addSingleNode(fundGrpXML, 'runMode', record.get('runMode')==_FND?'':record.get('runMode'));
			IFDS.Xml.addSingleNode(fundGrpXML, 'fundGrpUUID', record.get('fundGrpUUID'));
			IFDS.Xml.addSingleNode(fundGrpXML, 'grpType', record.get('grpType'));
			IFDS.Xml.addSingleNode(fundGrpXML, 'fundGroup', record.get('fundGroup'));
			IFDS.Xml.addSingleNode(fundGrpXML, 'grpDesc', record.get('grpDesc'));
			IFDS.Xml.addSingleNode(fundGrpXML, 'version', record.get('version'));
			
			var newLinkedFundsStr = record.get('LnkFunds');

			if (newLinkedFundsStr && newLinkedFundsStr.length > 0) {
				var newLinkedFundsXML = IFDS.Xml.stringToXML(newLinkedFundsStr);
				var addLinkedFunds = IFDS.Xml.getNodes(newLinkedFundsXML, "//LnkFund[runMode='" + _ADD + "']");
				var delLinkedFunds = IFDS.Xml.getNodes(newLinkedFundsXML, "//LnkFund[runMode='" + _DEL + "']");
			
				var linkedFundsXML = IFDS.Xml.addSingleNode(fundGrpXML, 'LnkFunds');
				
				Ext.each(delLinkedFunds, function(delLinkedFunds){buildUpdateLinkedFundXML(delLinkedFunds, linkedFundsXML)});
				Ext.each(addLinkedFunds, function(addLinkedFunds){buildUpdateLinkedFundXML(addLinkedFunds, linkedFundsXML)});
			}
			
			function buildUpdateLinkedFundXML(updatedLinkedFund, context){
				var linkedFundXML = IFDS.Xml.addSingleNode(context, 'LnkFund');
				IFDS.Xml.addAttribute(linkedFundXML, 'RecordSource', IFDS.Xml.getNodeValue(updatedLinkedFund, 'lnkFundUUID'));
				IFDS.Xml.addSingleNode(linkedFundXML, 'lnkFundUUID', IFDS.Xml.getNodeValue(updatedLinkedFund, 'lnkFundUUID'));
				IFDS.Xml.addSingleNode(linkedFundXML, 'fund', IFDS.Xml.getNodeValue(updatedLinkedFund, 'fund'));
				IFDS.Xml.addSingleNode(linkedFundXML, 'class', IFDS.Xml.getNodeValue(updatedLinkedFund, 'class'));
				IFDS.Xml.addSingleNode(linkedFundXML, 'version', IFDS.Xml.getNodeValue(updatedLinkedFund, 'version'));
				IFDS.Xml.addSingleNode(linkedFundXML, 'runMode', IFDS.Xml.getNodeValue(updatedLinkedFund, 'runMode'));
			}
		}
	}

	function setSelectedRow(gridName, index) {
		_resources.grids[gridName].setSelectedRecord(index);
	}

	function storeContextErrors(errorNodes) {
		//reset deleted records runmode in order to display the deleted fundGrp with ERROR
		var delRecords  = _resources.grids['fundGrp'].getStore().queryBy(function(record){ return record.get('runMode') == 'del' });
		for (var i = 0; i < errorNodes.length; i++) {
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			var errorCode = IFDS.Xml.getNodeValue(errorNodes[i], 'errorCode');
			var errorUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			if (errorCode == _LINKAGEERRORCODE || errorCode == _LINKAGEERRORCODE2) {
				for (var i = 0; i < delRecords.getCount(); i++) {
					var fundGrpUUID = delRecords.itemAt(i).data['fundGrpUUID'];
					if ( errorUUID == fundGrpUUID) {
						delRecords.itemAt(i).set('runMode', '');//change runMode as blank
					}
				}
			}
		}
		
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++) {
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			if (table == 'FundGrp') {
				var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				// Update fundGrp grid
				var recordIndex = _resources.grids['fundGrp'].getStore().find('fundGrpUUID', uuid);
				var fundGrpRecord = _resources.grids['fundGrp'].getStore().getAt(recordIndex);
				fundGrpRecord.set('errMsg', errMsg);
				_resources.grids['fundGrp'].getStore().commitChanges();
				if(firstErrRecIndex == -1)firstErrRecIndex = recordIndex;
			} else {
				var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				var fundGrpUUID = null;
				// find fundGrp uuid by linkedFund uuid from _updateXML
				var fundGrpXML = IFDS.Xml.getNode(_updateXML, "//FundGrp[LnkFunds/LnkFund/lnkFundUUID='" + uuid + "']");
				if (fundGrpXML){
					fundGrpUUID = IFDS.Xml.getNodeValue(fundGrpXML, 'fundGrpUUID');
					var fundGrpRecIndex = _resources.grids['fundGrp'].getStore().find('fundGrpUUID', fundGrpUUID);
					var fundGrpRecord = _resources.grids['fundGrp'].getStore().getAt(fundGrpRecIndex);
					var linkedFundsXML = IFDS.Xml.stringToXML(fundGrpRecord.data['LnkFunds']);
					var linkedFundXML = IFDS.Xml.getNode(linkedFundsXML, "//LnkFund[lnkFundUUID='" + uuid + "']");
					//handler if the linked fundclass is deleted and assign it back to the grid
					var runModeNode = IFDS.Xml.getNode(linkedFundXML, 'runMode');
					if (IFDS.Xml.getNodeValue(runModeNode, '//runMode') == 'del') {
						IFDS.Xml.setNodeValue(runModeNode, '');
					}
					
					var errMsgNode = IFDS.Xml.getNode(linkedFundXML, 'errMsg');
					if (errMsgNode == null){
						IFDS.Xml.addSingleNode(linkedFundXML, 'errMsg', errMsg);
					}else{
						IFDS.Xml.setNodeValue(errMsgNode, errMsg);
					}
					fundGrpRecord.data['LnkFunds'] = IFDS.Xml.serialize(linkedFundsXML);
					_resources.grids['linkedFundClass'].getStore().commitChanges();
					
					if(firstErrRecIndex == -1)firstErrRecIndex = fundGrpRecIndex;
				}
			}
		}
		
		if (firstErrRecIndex == -1) {
			_resources.grids['fundGrp'].getSelectionModel().selectFirstRow();
		} else {
			_resources.grids['fundGrp'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['fundGrp'].focusRow(firstErrRecIndex);
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
		,updatesFlag: false
		,currentSearch: _currentSearch
		
		,init: function(res) {
						
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			//calling from Fund Broker Linkage screen for display Fund/Class information only
			_fromScreen = DesktopWeb._SCREEN_PARAM_MAP['fromScreen'];
			if (_fromScreen != null && _fromScreen == 'FundBrokerLinkage') {
				var grpType = DesktopWeb._SCREEN_PARAM_MAP['grpType'];
				var fundGroup = DesktopWeb._SCREEN_PARAM_MAP['fundGroupCode'];
				//Set "FundGroupType" and "SearchBy" for "Fund Group screen", non editable
				_resources.fields['grpType'].setValue(_SETGRPTYPE);
				_resources.fields['searchFor'].setValue(_SETFUNDGRP);
				_resources.fields['searchByFundGrp'].setValue(fundGroup);
				_currentSearch['grpType'] = grpType;
				_currentSearch['searchFor']  = _SEARCHFOR;
				_currentSearch['searchValue']  = fundGroup;

				disableScreen();
				doSearch('reload', false);
			} else {
				// Call init service
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, 'runMode', 'init');
				
				DesktopWeb.Ajax.doSmartviewAjax(_dtFundGrpInqService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
				
				function responseHandler(success, responseXML) {
					if (success){
						// Handle response
						_initXML = responseXML;

						// Load permission if success
						storePermissions(responseXML);
						
						// Load dropdown if success
						populateDropdownList(responseXML);

						if (_permissions[_self.ADD]) {
							_resources.grids['fundGrp'].enableButton('addBtn'); 
						}
					} else {
						// When the screen is switched from Fund Broker Linkage screen
						disableScreen();
					}
				}
			}
		}
		//Handling Grid clicking
		,selectFundGrp: function(record) {
			updateFundGrpGridButtons(record);
			clearGrid('linkedFundClass'); 
			if (record.data['LnkFunds'] != null && record.data['LnkFunds'].length > 0) {
				var linkedFundXML = IFDS.Xml.stringToXML(record.data['LnkFunds']);
				_resources.grids['linkedFundClass'].loadData(linkedFundXML);
				//Fund Group allows no Fund/Class as the member(s), Add button required for selected Fund Group always
				_resources.grids['linkedFundClass'].enableButton('addBtn'); 
				
				if (record.data['hasMoreLinkedFunds'] == 'yes') {
					_resources.grids['linkedFundClass'].enableButton('moreBtn');
				}
			} else {
				if (record.data['runMode'] == _self.ADD) {
					updateLinkedFundGridButtons(null);
				} else {
					doSearch('reloadDetl', false);
				}
			}
		}
		
		,selectlinkedFundClass: function(record) {
			updateLinkedFundGridButtons(record);
		}

		,openActionPopup: function(name, action) {
			var popup = _resources.popups[name];	
			popup.show();
			popup.init(action);
		}

		,clickHandle_searchBtn: function() {
			if (_self.updatesFlag) {
				DesktopWeb.Util.displayDiscardPrompt(performSearch);
			} else {
				performSearch(true);
			}
			function performSearch(confirm) {
				if (confirm){
					if (validateSearchCriteria()){
						_self.updatesFlag = false;
						
						_currentSearch['grpType'] = _resources.fields['grpType'].getValue();
						_currentSearch['searchFor'] = _resources.fields['searchFor'].getValue();

						_currentSearch['searchValue'] = '';
						if (_resources.fields['searchByFundGrp'].getValue().length > 0) {
							_currentSearch['searchValue'] = _resources.fields['searchByFundGrp'].getValue();
						} 
						
						_currentSearch['fund'] = _currentSearch['fund'];
						_currentSearch['class'] = _currentSearch['class'];
						_nextStartRecNum = 1;
						
						clearGrid('fundGrp');
						clearGrid('linkedFundClass');

						doSearch('reload', false);
					}
				}
			}
		}
		
		,doReset: function() {
			if (_self.updatesFlag) {
				DesktopWeb.Util.displayDiscardPrompt(performReset);
			} else {
				performReset(true);
			}
			function performReset(confirm) {
				if (confirm){
					_self.updatesFlag = false; //Search Button pressed, no discard again
					_resources.fields['grpType'].enable();

					_resources.fields['searchFor'].enable();
					_resources.fields['searchFor'].reset();
					
					_resources.fields['searchByFundGrp'].enable();
					_resources.fields['searchByFundGrp'].reset();
					_resources.fields['searchByFundClass'].enable();
					_resources.fields['searchByFundClass'].reset();
					
					_resources.buttons['resetBtn'].disable();
					_resources.buttons['searchBtn'].enable();
					
					clearGrid('linkedFundClass');
					clearGrid('fundGrp');
					_currentSearch['fund'] = ''
					_currentSearch['class'] = ''
					if (_permissions[_self.ADD]) {
						_resources.grids['fundGrp'].enableButton('addBtn');
					}
				}
			}
		}
		,clickHandle_moreBtn: function() {
			doSearch('reload', true);
		}
		
		,clickHandle_moreBtnDetl: function() {
			doSearch('reloadDetl', true);
		}

		,validateFundGrp: function(data, action) {
			validateUpdateFundGrp(data, action);
		}
		
		,validatelinkedFund: function(data, action) {
			validateUpdateLinkedFund(data, action)
		}
		
		,resetLinkedFundPopUp: function(fld1,fld2, fld3) {
		    _resources.popups['linkedFundPopup'].getField(fld1).reset();
			_resources.popups['linkedFundPopup'].getField(fld2).reset();
			_resources.popups['linkedFundPopup'].getField(fld3).reset();
		}
		
		,getNewFundGrpUUID: function() {
			return "TMPFUNDGRP" + (_nextUUID++);
		}
		
		,getNewLinkedFundUUID: function() {
			return "TMPLNKFUND" + (_nextUUID++);
		}

		,doUpdate: function() {
			var updateStatus = null;
			_updateXML = buildUpdateXML(true);

			DesktopWeb.Ajax.doSmartviewUpdate(_dtFundGrpProcService, null, IFDS.Xml.cloneDocument(_updateXML), responseHandler, _translationMap['ProcMsg_Saving']);			

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
			
			DesktopWeb.Ajax.doSmartviewAjax(_dtFundGrpProcService, null, IFDS.Xml.cloneDocument(_updateXML), responseHandler, _translationMap['ProcMsg_Saving'], Ext.Msg.OKCANCEL);			

			function responseHandler(success, responseXML, contextErrors, warnings, btn) {
				if (success) {			
					if (btn == null || btn == 'ok') {
						DesktopWeb.Util.commitScreen();
					}
				} else {
					storeContextErrors(contextErrors);
				}
			}
			
		}
		
		,setSearchValueField: function () {
			setSearchValueField();
		}
		
		,clearGrid: function(name) {
		  clearGrid(name);
		}
		
		,handleFundGrpClassSearchChange: function(code) {
			if (isFundClassSelected(code)) {
					_resources.fields['searchByFundClass'].show();
					_resources.fields['searchByFundGrp'].hide();
					_resources.fields['searchByFundGrp'].reset();
			} else {	
					_resources.fields['searchByFundGrp'].show();
					_resources.fields['searchByFundClass'].hide();
					_resources.fields['searchByFundClass'].reset();
			}
		}
	}	
}