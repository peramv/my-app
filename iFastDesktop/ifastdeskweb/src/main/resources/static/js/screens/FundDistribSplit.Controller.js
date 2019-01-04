/*******************************************************************************
 * @file FundDistribSplit.Controller.js
 * @author Narin Suanlamyai
 * @desc Controller JS file for Fund Distribution Split Maintenance screen
 ******************************************************************************/
/*
 * Navigate: Menu > System Maintenance > Fund Distribution Split Maintenance
 * 
 * History :
 * 
 * 29-Dec-2017 Narin Suanlamyai P0274848 Distribution Processing - Initial
 * screen.
 * 
 */

DesktopWeb.ScreenController = function() {

	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var _changeFlag = false;
	var _inqView = 'dtFundDistribSplitInq';
	var _updateView = 'dtFundDistribSplitUpd';

	var _initDataXML = null;
	var _reloadDataXML = null;
	var _fundRuleXML = null;
	var _detailXML = null;
	var _currentSearchCriteria = new Array();
	var _nextUUID = 1;
	var _permissionsMap = {};

	var _nextStartRecNum = 0;
	var _requestRecNum = 25;
	var _nextStartRecNumDtl = 0;

	var _defaultValuesMap = {};

	function storePermissions() {
		// store permissions to _permissionsMap object
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//Permissions/inqPerm').toLowerCase() == _self.YES;
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//Permissions/addPerm').toLowerCase() == _self.YES;
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//Permissions/modPerm').toLowerCase() == _self.YES;
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//Permissions/delPerm').toLowerCase() == _self.YES;
	}

	function storeDefaultValues() {
		// store default values to _defaultValuesMap object
		_defaultValuesMap['deff'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//DefaultValues/deff');
		_defaultValuesMap['stopDate'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//DefaultValues/stopDate');
		_defaultValuesMap['distribType'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//DefaultValues/distribType');
		_defaultValuesMap['distribOpt'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//DefaultValues/distribOpt');
		_defaultValuesMap['verifyStat'] = IFDS.Xml.getNodeValue(_initDataXML,
				'//DefaultValues/verifyStat');
	}

	function populateDropdownList() {
		_resources.fields['distribTypeFld'].loadData(IFDS.Xml.getNode(
				_initDataXML, "//List[@listName = 'DistributionTypeList']"));
		_resources.popups['distribMstr'].getField('distribType').loadData(
				IFDS.Xml.getNode(_initDataXML,
						"//List[@listName = 'DistributionTypeList']"));
		_resources.popups['distribMstr'].getField('verifyStat').loadData(
				IFDS.Xml.getNode(_initDataXML,
						"//List[@listName = 'VerifyStatusList']"));
		_resources.popups['distribDetl'].getField('distribOpt').loadData(
				IFDS.Xml.getNode(_initDataXML,
						"//List[@listName = 'DistributionOptionList']"));
	}

	function applyPermissions() {
		if (_permissionsMap['inq']) {
			_resources.buttons['searchBtn'].enable();
			if (_permissionsMap['add']) {
				_resources.grids['distribMstr'].enableButton('addBtn');
			}
		} else {
			disableScreen();
		}
	}

	function doSearch(append) {
		// build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');

		IFDS.Xml.addSingleNode(dataXML, 'runMode', 'reload');
		IFDS.Xml.addSingleNode(dataXML, 'fundCode',
				_currentSearchCriteria['fundCode']);
		IFDS.Xml.addSingleNode(dataXML, 'classCode',
				_currentSearchCriteria['classCode']);
		IFDS.Xml.addSingleNode(dataXML, 'distribType',
				_currentSearchCriteria['distribType']);
		IFDS.Xml.addSingleNode(dataXML, 'onlyActive',
				_currentSearchCriteria['onlyActive']);

		IFDS.Xml.addSingleNode(dataXML, 'startRecNum',
				append ? _nextStartRecNum : 1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);

		DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, dataXML,
				responseHandler, _translationMap['ProcMsg_Searching'])

		function responseHandler(success, responseXML) {
			_reloadDataXML = IFDS.Xml.cloneDocument(responseXML);
			if (success) {
				if (append) {
					// User clicks More button
					_resources.grids['distribMstr'].appendData(responseXML);
					_resources.grids['distribMstr']
							.setSelectedRecord(_nextStartRecNum - 1);
				} else {
					_resources.grids['distribMstr'].loadData(IFDS.Xml.getNode(
							responseXML, "//FundDistribSplitList"));
				}

				// control more button
				_nextStartRecNum = DesktopWeb.Ajax
						.getSmartviewNextStartRecNum(responseXML);
				if (_nextStartRecNum) {
					_resources.grids['distribMstr'].enableButton('moreBtn');
				} else {
					_resources.grids['distribMstr'].disableButton('moreBtn');
				}
			} else {
				// TODO: Control when search failed
			}

			applyPermissions();
		}
	}

	function doUpdate() {
		var updateStatus = null;
		DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(),
				responseHandler, null);

		function responseHandler(success, responseXML, contextErrors, warnings,
				btn) {
			if (success) {
				updateStatus = DesktopWeb._SUCCESS;
			} else {
				storeContextErrors(contextErrors);
				updateStatus = DesktopWeb._FAIL
			}
		}
		return updateStatus;
	}

	function loadDistributionDetails(distribMstrRecord) {
		var splitDetlStr = distribMstrRecord.data['fundDistribSplitDetls'];
		if (!splitDetlStr) {
			splitDetlStr = "<FundDistribSplitDetls/>";
		}
		_resources.grids['distribDetl'].loadData(IFDS.Xml
				.stringToXML(splitDetlStr));
	}

	function updateDistribMstrGridButtons(distribMstrRecord) {
		if (_permissionsMap['add']) {
			_resources.grids['distribMstr'].enableButton('addBtn');
		}
		if (_permissionsMap['mod']) {
			_resources.grids['distribMstr'].enableButton('modBtn');
		}
		if (_permissionsMap['del']) {
			_resources.grids['distribMstr'].enableButton('delBtn');
		}
		if (distribMstrRecord.data['gbcd'] !== "yes") {
			_resources.grids['distribMstr'].disableButton('modBtn');
			_resources.grids['distribMstr'].disableButton('delBtn');
		}
		if (distribMstrRecord.data['runMode'] === _self.ADD) {
			_resources.grids['distribMstr'].disableButton('adminBtn');
			_resources.grids['distribMstr'].disableButton('historicalBtn');
		} else {
			_resources.grids['distribMstr'].enableButton('adminBtn');
			_resources.grids['distribMstr'].enableButton('historicalBtn');
		}
	}

	function updateDistribDetlGridButtons(distribDetlRecord) {
		if (_permissionsMap['add']) {
			_resources.grids['distribDetl'].enableButton('addBtn');
		}

		if (distribDetlRecord) {
			if (_permissionsMap['mod']) {
				_resources.grids['distribDetl'].enableButton('modBtn');
			}
			if (_permissionsMap['del']) {
				_resources.grids['distribDetl'].enableButton('delBtn');
			}
		}

		var distribMstrRecord = _resources.grids['distribMstr']
				.getSelectedRecord();
		if (distribMstrRecord && distribMstrRecord.data['gbcd'] !== "yes") {
			_resources.grids['distribDetl'].disableButton('addBtn');
			_resources.grids['distribDetl'].disableButton('modBtn');
			_resources.grids['distribDetl'].disableButton('delBtn');
		}
	}

	function storeContextErrors(errorNodes) {
		for (var i = 0; i < errorNodes.length; i++) {
			var table = IFDS.Xml.getNodeValue(errorNodes[i],
					'recordSource/source/xmlElementName');
			var elementSource = IFDS.Xml.getNodeValue(errorNodes[i],
					'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			var gridName = (table === "FundDistribSplit") ? "distribMstr"
					: "distribDetl";
			var uuidField = (table === "FundDistribSplit") ? "mstrUUID"
					: "detlUUID";

			var recordIndex = _resources.grids[gridName].getStore().find(
					uuidField, elementSource);
			if (recordIndex != -1) {
				var record = _resources.grids[gridName].getStore().getAt(
						recordIndex);
				if (record) {
					record.set('errMsg', errMsg);
					record.commit();
				}
			}
		}
	}

	function clearContextErrors() {
		var updatedDistribMstrRecords = _resources.grids['distribMstr']
				.getStore().queryBy(function(record) {
					return record.get('runMode') !== _self.BLANK;
				});

		for (var i = 0; i < updatedDistribMstrRecords.length; i++) {
			var distribMstrRecord = updatedDistribMstrRecords.itemAt(i);
			distribMstrRecord.data['errMsg'] = "";
			distribMstrRecord.commit();
		}
	}

	function clearGrid(name) {
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}

	function clearField(name) {
		_resources.fields[name].reset();
		_resources.fields[name].disable();
	}

	function disableScreen() {
		_resources.fields['fundFld'].disableField();
		_resources.fields['classFld'].disableField();
		_resources.fields['distribTypeFld'].disableField();
		_resources.fields['activeBox'].disableField();
		_resources.buttons['searchBtn'].disable();
		_resources.grids['distribMstr'].disableAllButtons();
		_resources.grids['distribDetl'].disableAllButtons();
	}

	function updateFundDistribSplitDetlsContext() {
		var allDistribDetlRecords = _resources.grids['distribDetl']
				.getAllRecords();
		var selectedDistribMstrRecord = _resources.grids['distribMstr']
				.getSelectedRecord();
		var fundDistribSplitDetlsNode = IFDS.Xml
				.newDocument("FundDistribSplitDetls");
		Ext.each(allDistribDetlRecords, function(distribDetlRecord) {
			var fundDistribSplitDetlNode = IFDS.Xml.addSingleNode(
					fundDistribSplitDetlsNode, "FundDistribSplitDetl");
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "errMsg",
					distribDetlRecord.data['errMsg']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "runMode",
					distribDetlRecord.data['runMode']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "mstrUUID",
					distribDetlRecord.data['mstrUUID']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "detlUUID",
					distribDetlRecord.data['detlUUID']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "distribOpt",
					distribDetlRecord.data['distribOpt']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "toFundCode",
					distribDetlRecord.data['toFundCode']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "toFundDesc",
					distribDetlRecord.data['toFundDesc']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "toClassCode",
					distribDetlRecord.data['toClassCode']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "toClassDesc",
					distribDetlRecord.data['toClassDesc']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "prcnt",
					distribDetlRecord.data['prcnt']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "username",
					distribDetlRecord.data['userName']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "processDate",
					distribDetlRecord.data['processDate']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "modUser",
					distribDetlRecord.data['modUser']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "modDate",
					distribDetlRecord.data['modDate']);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "version",
					distribDetlRecord.data['version']);
		});
		selectedDistribMstrRecord.data['fundDistribSplitDetls'] = IFDS.Xml
				.serialize(fundDistribSplitDetlsNode);
		selectedDistribMstrRecord.commit();
	}

	function buildUpdateXML() {
		var updatedDistribRecords = _resources.grids['distribMstr'].getStore()
				.queryBy(
						function(record) {
							return record.get('runMode') == _self.ADD
									|| record.get('runMode') == _self.MOD
									|| record.get('runMode') == _self.DEL
									|| record.get('runMode') == _self.UPD;
						});

		if (updatedDistribRecords.length <= 0)
			return null;

		var updateXML = IFDS.Xml.newDocument("data");
		var fundDistribXML = IFDS.Xml.addSingleNode(updateXML,
				"FundDistribSplitList");
		for (var i = 0; i < updatedDistribRecords.length; i++) {
			buildUpdateDistribXML(fundDistribXML, updatedDistribRecords
					.itemAt(i));
		}

		return updateXML;
	}

	function buildUpdateDistribXML(context, distribRecord) {
		var fundDistribSplitNode = buildUpdateDistribMstrXML(context,
				distribRecord);

		var fundDistribSplitDetlsNode = IFDS.Xml.addSingleNode(
				fundDistribSplitNode, "FundDistribSplitDetls");
		var fundDistribSplitDetlsXML = IFDS.Xml
				.stringToXML(distribRecord.data['fundDistribSplitDetls']);
		var fundDistribSplitDetlXMLs = IFDS.Xml.getNodes(
				fundDistribSplitDetlsXML, "//FundDistribSplitDetl");

		if (distribRecord.data['runMode'] !== _self.DEL) {
			Ext.each(fundDistribSplitDetlXMLs,
					function(fundDistribSplitDetlXML) {
						if (IFDS.Xml.getNodeValue(fundDistribSplitDetlXML,
								"runMode") !== _self.DEL) {
							buildUpdateDistribDetlXML(
									fundDistribSplitDetlsNode,
									fundDistribSplitDetlXML);
						}
					});
		}

		return fundDistribSplitNode;
	}

	function buildUpdateDistribMstrXML(context, distribMstrRecord) {
		var fundDistribSplitNode = IFDS.Xml.addSingleNode(context,
				"FundDistribSplit");
		IFDS.Xml.addAttribute(fundDistribSplitNode, 'RecordSource',
				distribMstrRecord.data['mstrUUID']);
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "mstrUUID",
				distribMstrRecord.data['mstrUUID']);
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "runMode",
				distribMstrRecord.data['runMode']);
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "fundCode",
				distribMstrRecord.data['fundCode']);
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "classCode",
				distribMstrRecord.data['classCode']);
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "distribType",
				distribMstrRecord.data['distribType']);
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "deff", DesktopWeb.Util
				.getSMVDateValue(distribMstrRecord.data['deff']));
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "verifyStat",
				distribMstrRecord.data['verifyStat']);
		IFDS.Xml.addSingleNode(fundDistribSplitNode, "version",
				distribMstrRecord.data['version']);

		return fundDistribSplitNode;
	}

	function buildUpdateDistribDetlXML(context, distribDetlRecordXML) {
		var fundDistribSplitDetlNode = null;
		var runMode = IFDS.Xml.getNodeValue(distribDetlRecordXML, "runMode");

		if (runMode !== _self.DEL) {
			var fundDistribSplitDetlNode = IFDS.Xml.addSingleNode(context,
					"FundDistribSplitDetl");
			runMode = Ext.isEmpty(runMode) ? _self.UPD : runMode;
			IFDS.Xml.addAttribute(fundDistribSplitDetlNode, 'RecordSource',
					IFDS.Xml.getNodeValue(distribDetlRecordXML, "detlUUID"));
			IFDS.Xml
					.addSingleNode(fundDistribSplitDetlNode, "runMode", runMode);
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "mstrUUID",
					IFDS.Xml.getNodeValue(distribDetlRecordXML, "mstrUUID"));
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "detlUUID",
					IFDS.Xml.getNodeValue(distribDetlRecordXML, "detlUUID"));
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "distribOpt",
					IFDS.Xml.getNodeValue(distribDetlRecordXML, "distribOpt"));
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "toFundCode",
					IFDS.Xml.getNodeValue(distribDetlRecordXML, "toFundCode"));
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "toClassCode",
					IFDS.Xml.getNodeValue(distribDetlRecordXML, "toClassCode"));
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "prcnt", IFDS.Xml
					.getNodeValue(distribDetlRecordXML, "prcnt"));
			IFDS.Xml.addSingleNode(fundDistribSplitDetlNode, "version",
					IFDS.Xml.getNodeValue(distribDetlRecordXML, "version"));
		}

		return fundDistribSplitDetlNode;
	}

	function init(res) {
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;

		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(requestXML, 'runMode', 'init');

		DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, requestXML,
				responseHandler1, _translationMap['ProcMsg_Loading']);

		function responseHandler1(success, responseXML) {
			if (success) {
				_initDataXML = responseXML;
				storePermissions();
				storeDefaultValues();
				populateDropdownList();
				applyPermissions();
			} else {
				disableScreen();
			}
		}
	}

	function openActionPopup(popupName, action) {
		_resources.popups[popupName].show();
		_resources.popups[popupName].init(action);
	}

	function openHistoricalPopup() {
		var viewParam = {};
		var historyName = null;
		var selectedRecord = _resources.grids['distribMstr']
				.getSelectedRecord();

		if (selectedRecord != undefined && selectedRecord != null) {
			viewParam['auditType'] = 'FundDistribSplit';
			viewParam['searchValue1'] = '0';
			viewParam['searchValue2'] = selectedRecord.data['fundCode'];
			viewParam['searchValue3'] = selectedRecord.data['classCode'];
			viewParam['searchValue4'] = DesktopWeb.Util
					.getSMVDateValue(selectedRecord.data['deff']);
			viewParam['searchValue5'] = selectedRecord.data['distribType'];
			viewParam['searchValue6'] = '';

			historyName = _translationMap['FundDistributionSplit'] + ' - '
					+ _translationMap['History'];

			_resources.popups['history'].init(historyName, 'dtHistoricalInfo',
					viewParam, true);
			_resources.popups['history'].show();
		}
	}

	function openAdminPopup(gridName) {
		var title = null;
		var xml = null;

		title = _translationMap['Admin'];
		xml = _resources.grids[gridName].getSelectedRecord();

		if (xml && xml != undefined) {
			var adminData = {};
			adminData['userName'] = xml.data['username'];
			adminData['procDate'] = xml.data['processDate'];
			adminData['modUser'] = xml.data['modUser'];
			adminData['modDate'] = xml.data['modDate'];

			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();
		}
	}

	function loadClass(fundCode, classField, classCode) {
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'fundCode', fundCode);

		DesktopWeb.Ajax.doSmartviewAjax('classSearch', null, dataXML,
				responseHandler, _translationMap['ProcMsg_Loading'])

		function responseHandler(success, responseXML) {
			if (success) {
				if (classField != null) {
					classField.enable();
					classField.loadData(IFDS.Xml.getNode(responseXML,
							'/*//Classes'));

					if (!Ext.isEmpty(classCode)) {
						classField.setValue(classCode);
					}
				}
			}
		}
	}

	function performSearch() {
		// Store search criteria; they would be used for more button
		_currentSearchCriteria['fundCode'] = _resources.fields['fundFld']
				.getValue();
		_currentSearchCriteria['classCode'] = _resources.fields['classFld']
				.getValue();
		_currentSearchCriteria['distribType'] = _resources.fields['distribTypeFld']
				.getValue();
		_currentSearchCriteria['onlyActive'] = _resources.fields['activeBox']
				.getValue() == 0 ? _self.NO : _self.YES;

		// Clear data in grid before do actual search
		clearGrid('distribMstr');
		clearGrid('distribDetl');

		// Call doSearch
		doSearch(false);
	}

	function doReload() {
		// Call doSearch with append and more
		doSearch(true);
	}

	function getNewUUID() {
		return "TMPUUID" + (_nextUUID++);
	}

	function isSearchCriteriaValid() {
		return _resources.fields['fundFld'].isValid()
				&& _resources.fields['classFld'].isValid()
				&& _resources.fields['distribTypeFld'].isValid()
				&& _resources.fields['activeBox'].isValid();
	}

	function getDescriptionFromList(value, listName) {
		var listNode = IFDS.Xml.getNode(_initDataXML, "//List[@listName = '"
				+ listName + "']/Element[code='" + value + "']");
		listNode = (listNode) ? listNode : IFDS.Xml.getNode(_initDataXML,
				"//List[@id = '" + listName + "']/Element[code='" + value
						+ "']");
		return (listNode) ? IFDS.Xml.getNodeValue(listNode, 'value') : value;
	}

	function selectDistributionRecord(record) {
		// update buttons
		updateDistribMstrGridButtons(record);

		// load distribution details (split) records to distribution detail grid
		loadDistributionDetails(record);
	}

	function selectDistributionDetailsRecord(record) {
		// update buttons
		updateDistribDetlGridButtons(record);
	}

	function getFundDistribSplitDetails(mstrUUID) {
		var splitDetlXML = IFDS.Xml.getNode(_reloadDataXML,
				"//FundDistribSplit[mstrUUID='" + mstrUUID
						+ "']/FundDistribSplitDetls");
		return splitDetlXML ? IFDS.Xml.serialize(splitDetlXML)
				: "<FundDistribSplitDetls/>";
	}

	function isValidDistribMstrRecord(distribMstrData) {
		var isValid = false;
		if (_resources.popups['distribMstr'].isValid()) {
			isValid = true;
		}
		return isValid;
	}

	function updateDistribMstrRecord(distribMstrData) {
		switch (distribMstrData['action']) {
		case this.ADD:
			distribMstrData['fundDistribSplitDetls'] = "<FundDistribSplitDetls/>";
			_resources.grids['distribMstr'].addRecord(distribMstrData);
			_resources.grids['distribMstr'].selectLastRecord();
			_resources.popups['distribMstr'].hide();
			break;

		case this.MOD:
			distribMstrData['runMode'] = (distribMstrData['runMode'] === _self.ADD) ? _self.ADD
					: _self.MOD;
			_resources.grids['distribMstr']
					.updateSelectedRecord(distribMstrData);
			_resources.popups['distribMstr'].hide();
			break;

		case this.DEL:
			if (distribMstrData['runMode'] === _self.ADD) {
				_resources.grids['distribMstr'].removeSelectedRecord();
			} else {
				distribMstrData['runMode'] = _self.DEL;
				_resources.grids['distribMstr']
						.updateSelectedRecord(distribMstrData);
			}
			clearGrid("distribDetl");
			_resources.grids['distribMstr'].selectFirstRecord();
			_resources.popups['distribMstr'].hide();
			break;

		}
	}

	function isValidDistribDetlRecord(distribDetlData) {
		var isValid = false;
		var popup = _resources.popups['distribDetl'];
		if (popup.isValid()) {
			isValid = true;
			// Verify Fund/Class against distribution option
			var distribOpt = popup.getField('distribOpt').getValue();
			if (distribOpt === _self.DISTRIBUTION_OPTION_REDIRECT) {
				var toFund = popup.getField('toFund').getValue();
				var toClass = popup.getField('toClass').getValue();
				if (toFund === "CASH") {
					popup.getField('distribOpt').markInvalid(
							_translationMap['ERR_CannotRedirectToCash']);
					isValid = false;
				}
				if (isValid) {
					var distribMstr = _resources.grids['distribMstr']
							.getSelectedRecord();
					var fromFund = distribMstr.data['fundCode'];
					var fromClass = distribMstr.data['classCode'];
					if (fromFund === toFund && fromClass === toClass) {
						popup.getField('distribOpt').markInvalid(
								_traslationMap['ERR_CannotRedirectToSameFund']);
						isValid = false;
					}
				}
			}

			if (isValid) {
				// Validate duplicate distribution details at user input level
				var distribDetlRecords = _resources.grids['distribDetl']
						.getStore()
						.queryBy(
								function(record) {
									return record.get('runMode') !== _self.DEL
											&& record.get('detlUUID') !== popup.detlUUID;
								});
				for (var i = 0; i < distribDetlRecords.length; i++) {
					var distribDetlRecord = distribDetlRecords.itemAt(i);
					if (distribDetlRecord.data['distribOpt'] === popup
							.getField('distribOpt').getValue()
							&& distribDetlRecord.data['toFundCode'] === popup
									.getField('toFund').getValue()
							&& distribDetlRecord.data['toClassCode'] === popup
									.getField('toClass').getValue()) {
						isValid = false;
						DesktopWeb.Util
								.displayError(_translationMap['ERR_DuplicateDistribOptFundClass']);
						break;
					}
				}
			}

		}
		return isValid;
	}

	function updateDistribDetlRecord(distribDetlData) {
		switch (distribDetlData['action']) {
		case this.ADD:
			_resources.grids['distribDetl'].addRecord(distribDetlData);
			_resources.grids['distribDetl'].selectLastRecord();

			updateFundDistribSplitDetlsContext();
			updateRunModeSelectedDistribMstr();

			_resources.popups['distribDetl'].hide();
			break;

		case this.MOD:
			distribDetlData['runMode'] = (distribDetlData['runMode'] === _self.ADD) ? _self.ADD
					: _self.MOD;
			_resources.grids['distribDetl']
					.updateSelectedRecord(distribDetlData);

			updateFundDistribSplitDetlsContext();
			updateRunModeSelectedDistribMstr();

			_resources.popups['distribDetl'].hide();
			break;

		case this.DEL:
			if (distribDetlData['runMode'] === _self.ADD) {
				_resources.grids['distribDetl'].removeSelectedRecord();
			} else {
				distribDetlData['runMode'] = _self.DEL;
				_resources.grids['distribDetl']
						.updateSelectedRecord(distribDetlData);
			}

			updateFundDistribSplitDetlsContext();
			updateRunModeSelectedDistribMstr();

			_resources.grids['distribDetl'].selectFirstRecord();
			_resources.popups['distribDetl'].hide();
			break;

		}

		function updateRunModeSelectedDistribMstr(runMode) {
			if (Ext.isEmpty(runMode)) {
				runMode = _self.MOD;
			}
			var distribMstrRecord = _resources.grids['distribMstr']
					.getSelectedRecord();
			if (Ext.isEmpty(distribMstrRecord.data['runMode'])) {
				distribMstrRecord.data['runMode'] = runMode;
				distribMstrRecord.commit();
			}
		}
	}

	function distributionOptionHandler(distribOpt) {
		var popup = _resources.popups['distribDetl'];
		clearToFundToClassOnPopup();
		popup.getField('toFund').loadToClass = false;
		switch (distribOpt) {
		case _self.DISTRIBUTION_OPTION_CASH:
			popup.getField('toFund').prepopulate("CASH", "CASH CASH");
			_self.loadClass("CASH", popup.getField("toClass"));
			popup.getField("toFund").disableField();
			popup.getField("toClass").disableField();
			break;
		case _self.DISTRIBUTION_OPTION_REDIRECT:
			break;
		case _self.DISTRIBUTION_OPTION_REINVEST:
			var distribMstrRecord = _resources.grids['distribMstr']
					.getSelectedRecord();
			popup.getField('toFund').prepopulate(
					distribMstrRecord.data['fundCode'],
					distribMstrRecord.data['fundDesc']);
			_self.loadClass(distribMstrRecord.data['fundCode'], popup
					.getField("toClass"), distribMstrRecord.data['classCode']);
			popup.getField('toFund').loadToClass = true;
			popup.getField("toFund").disableField();
			popup.getField("toClass").disableField();
			break;
		}

		popup.getField('toFund').loadToClass = true;

		function clearToFundToClassOnPopup() {
			popup.getField('toClass').clearValue();
			popup.getField('toClass').clearInvalid();
			popup.getField('toClass').enableField();
			popup.getField('toFund').clearValue();
			popup.getField('toFund').clearInvalid();
			popup.getField('toFund').enableField();
		}
	}

	function isScreenValid() {
		var isValid = true;
		var updatedDistribMstrRecords = _resources.grids['distribMstr']
				.getStore().queryBy(
						function(record) {
							return record.get('runMode') !== _self.BLANK
									&& record.get('runMode') !== _self.DEL;
						});

		for (var i = 0; i < updatedDistribMstrRecords.length; i++) {
			var distribMstrRecord = updatedDistribMstrRecords.itemAt(i);
			var distribDetlRecordsString = distribMstrRecord.data['fundDistribSplitDetls'];
			distribDetlRecordsString = Ext.isEmpty(distribDetlRecordsString) ? "<FundDistribSplitDetls/>"
					: distribDetlRecordsString;
			var distribDetlRecordsXML = IFDS.Xml
					.stringToXML(distribDetlRecordsString);
			var distribDetlNodes = IFDS.Xml.getNodes(distribDetlRecordsXML,
					"FundDistribSplitDetl");
			var totalPrcnt = 0;
			Ext
					.each(distribDetlNodes,
							function(distribDetlNode) {
								if (IFDS.Xml.getNodeValue(distribDetlNode,
										"runMode") !== _self.DEL) {
									var prcnt = IFDS.Xml.getNodeValue(
											distribDetlNode, "prcnt");
									var prcntFloat = parseFloat(prcnt);
									totalPrcnt = totalPrcnt + prcntFloat;
								}
							});
			if (totalPrcnt !== 100.00) {
				isValid = false;
				distribMstrRecord.data['errMsg'] = _translationMap["ERR_TotalPercentageMustBe100"];
				distribMstrRecord.commit();
			}
		}

		return isValid;
	}
	
	function hasUpdatedRecords() {
		var updatedDistribRecords = _resources.grids['distribMstr'].getStore()
		.queryBy(
				function(record) {
					return record.get('runMode') == _self.ADD
							|| record.get('runMode') == _self.MOD
							|| record.get('runMode') == _self.DEL
							|| record.get('runMode') == _self.UPD;
				});

		return updatedDistribRecords.length > 0;
	}

	// PUBLIC ITEMS *************************************
	return {

		ADD : 'add',
		MOD : 'mod',
		DEL : 'del',
		UPD : 'upd',
		YES : 'yes',
		NO : 'no',
		BLANK : '',
		DISTRIBUTION_OPTION_CASH : 'CS',
		DISTRIBUTION_OPTION_REINVEST : 'RI',
		DISTRIBUTION_OPTION_REDIRECT : 'RD',
		updatesFlag : false,
		defaultValuesMap : _defaultValuesMap,
		init : init,
		openActionPopup : openActionPopup,
		openHistoricalPopup : openHistoricalPopup,
		openAdminPopup : openAdminPopup,
		loadClass : loadClass,
		doSearch : performSearch,
		doReload : doReload,
		doUpdate : doUpdate,
		getNewUUID : getNewUUID,
		isSearchCriteriaValid : isSearchCriteriaValid,
		getDescriptionFromList : getDescriptionFromList,
		selectDistributionRecord : selectDistributionRecord,
		selectDistributionDetailsRecord : selectDistributionDetailsRecord,
		updateDistribDetlGridButtons : updateDistribDetlGridButtons,
		getFundDistribSplitDetails : getFundDistribSplitDetails,
		isValidDistribMstrRecord : isValidDistribMstrRecord,
		updateDistribMstrRecord : updateDistribMstrRecord,
		isValidDistribDetlRecord : isValidDistribDetlRecord,
		updateDistribDetlRecord : updateDistribDetlRecord,
		distributionOptionHandler : distributionOptionHandler,
		isScreenValid : isScreenValid,
		clearContextErrors : clearContextErrors,
		hasUpdatedRecords : hasUpdatedRecords
	} // close return public variable & functions
}