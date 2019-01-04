/******************************************************************************
 * Procedure: ExternalTA.Translation.js
 * Purpose  : ExternalTA screens manage External Tranfer Agent data
 * Notes    : Open screens by 
 *						 Menu -> System Maintenance -> External TA Fund Linkage
 * History  :
 *		03 Jul 2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *			- Created
 * 
 *		20 Jul 2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *			- Update enable button
 ******************************************************************************/

DesktopWeb.ScreenController = function () {

	// PRIVATE VARIABLES 
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var ADD = 'add';
	var MOD = 'mod';
	var DEL = 'del';
	var INQ = 'inq';

	var _dtInqService = 'dtExternalTAInq';
	var _dtUpdService = 'dtExternalTAProc';
	var _historyService = 'dtHistoricalInfo';

	var _lastFG = '';
	var _lastLevel = '';
	var _lastExtAcctSrch = '';
	
	var _nextRecNum = null;
	var _requestRecNum = 25;
	var _permissionsMap = {};
	var _defaultValues = {};

	var _cnewitem = 0;

	// PRIVATE METHODS ****************************************
	function funcInit(res) {
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;

		var initParamXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(initParamXML, 'runMode', 'init');
		IFDS.Xml.addSingleNode(initParamXML, 'startRecNum', 1);
		IFDS.Xml.addSingleNode(initParamXML, 'requestRecNum', _requestRecNum);

		DesktopWeb.Ajax.doSmartviewAjax(_dtInqService, {
			ignoreErrorCode : '15'
		}, initParamXML, responseHandler, _translationMap['ProcMsg_Loading']);
    
		function responseHandler(success, responseXML) {
			if (success) {
				storePermissions(responseXML);
				storeDefaultValues(responseXML);
				loadToStore(responseXML);
				loadXMLtoGrid(IFDS.Xml.getNode(responseXML, "//ExternalTAList"));
			}
			funcUpdateActionButtons();			
		}
	} //function funcInit

	function loadToStore(initViewXML) {
		var node = IFDS.Xml.getNode(initViewXML, '/*//List[@listName="ruleCode"]');
		if (!!node)
			_resources.popups['externalTAPopup'].getField('ruleCode').getStore().loadData(node);

		node = IFDS.Xml.getNode(initViewXML, '/*//FundGroupList');

		if (!!node) {
			_resources.popups['externalTAPopup'].getField('fundGroup').getStore().loadData(node);
			_resources.fields['fundGrpSrch'].getStore().loadData(node);
		}
	} //function loadToStore

	function storePermissions(initViewXML) {
		_permissionsMap[ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/modPerm').toLowerCase() == 'yes';
		_permissionsMap[DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/delPerm').toLowerCase() == 'yes';
		_permissionsMap[INQ] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/inqPerm').toLowerCase() == 'yes';
	} //function storePermissions

	function storeDefaultValues(DefaultValuesXML) {
		_defaultValues['startDate'] = DesktopWeb.Util.getDateDisplayValue(
				IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/startDate'));
		_defaultValues['toDate'] = DesktopWeb.Util.getDateDisplayValue(
				IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/toDate'));
		_defaultValues['ruleCode'] = IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultValues/ruleCode');
	} //function storeDefaultValues

	function isNewRecord(record) {
		return record.data['runMode'] == _self.ADD
	} //function isNewRecord

	function getUpdatedRecordCount() {
		var store = _resources.grids['gridExternalTA'].getStore();
		var newRecords = store.query('runMode', _self.ADD);
		var modRecords = store.query('runMode', _self.MOD);
		var delRecords = store.query('runMode', _self.DEL);
		return newRecords.length + modRecords.length + delRecords.length
	} //function getUpdatedRecordCount

	function buildUpdateXML(mode) {
		var updateXML = IFDS.Xml.newDocument('data');
		var store = _resources.grids['gridExternalTA'].getStore();

		var ExternalTAList = IFDS.Xml.addSingleNode(updateXML, 'ExternalTAList');
		IFDS.Xml.addSingleNode(ExternalTAList, 'IOMode', mode);
		var delRecords = store.query('runMode', _self.DEL);
		delRecords.each(addToXML);
		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToXML);
		var newRecords = store.query('runMode', _self.ADD);
		newRecords.each(addToXML);

		return updateXML;

		function addToXML(item) {
			var recordXML = IFDS.Xml.addSingleNode(ExternalTAList, 'ExternalTA');
			IFDS.Xml.addAttribute(recordXML, 'RecordSource', item.data['externalTAUUID']);
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item.data['runMode']);
			IFDS.Xml.addSingleNode(recordXML, 'externalTAUUID', item.data['externalTAUUID']);
			IFDS.Xml.addSingleNode(recordXML, 'fundGroup', item.data['fundGroup']);
			IFDS.Xml.addSingleNode(recordXML, 'level', item.data['level']);
			IFDS.Xml.addSingleNode(recordXML, 'ruleCode', item.data['ruleCode']);
			IFDS.Xml.addSingleNode(recordXML, 'extAcct', item.data['extAcct']);
			IFDS.Xml.addSingleNode(recordXML, 'recvNWAddr', item.data['recvNWAddr']);

			IFDS.Xml.addSingleNode(recordXML, 'startDate', DesktopWeb.Util.getSMVDateValue(item.data['startDate']));
			IFDS.Xml.addSingleNode(recordXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(item.data['stopDate']));
			IFDS.Xml.addSingleNode(recordXML, 'version', item.data['version']);
		} //addToXML
	} //function buildUpdateXML

	function doSearch(fundGroup, _lastLevel,extAcct, runMode, append) {
		var paramXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(paramXML, 'level', _lastLevel);
		IFDS.Xml.addSingleNode(paramXML, 'fundGroup', fundGroup);
		IFDS.Xml.addSingleNode(paramXML, 'extAcct', extAcct);
		IFDS.Xml.addSingleNode(paramXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', (_nextRecNum) ? _nextRecNum : '1');
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

		DesktopWeb.Ajax.doSmartviewAjax(_dtInqService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);
		function responseHandler(success, responseXML) {
			if (success) {
				loadXMLtoGrid(IFDS.Xml.getNode(responseXML, "//ExternalTAList"), append);

				if (!append)
					_self.updatesFlag = false;
			}
			else 
			  funcUpdateActionButtons();
		}
	} //doSearch

	function loadXMLtoGrid(xml, append) {
		if (!!xml) {
			var index = _resources.grids['gridExternalTA'].getSelectionModel().last;
			_resources.grids['gridExternalTA'].getStore().loadData(xml, append);
			_resources.grids['gridExternalTA'].setSelectedRecord(index);

			funcUpdateActionButtons();
			updateMoreButton(xml);
		}
	} //loadXMLtoGrid

	function storeContextErrors(errorNodes) {
		clearContextErrors();
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++) {
			var uuid = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');

			var recordIndex = _resources.grids['gridExternalTA'].getStore().find('externalTAUUID', uuid);
			var errRecord = _resources.grids['gridExternalTA'].getStore().getAt(recordIndex);

			if (errRecord !== undefined) {
				errRecord.set('errMsg', errMsg);
				errRecord.commit();

				if (firstErrRecIndex == -1)
					firstErrRecIndex = recordIndex;
			}
		} //for

		if (firstErrRecIndex == -1) {
			_resources.grids['gridExternalTA'].getSelectionModel().selectFirstRow();
		} else {
			_resources.grids['gridExternalTA'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['gridExternalTA'].focusRow(firstErrRecIndex);
		}
	} //function storeContextErrors

	function clearContextErrors() {
		var errRecords = _resources.grids['gridExternalTA'].getStore().queryBy(
				function (record, id) {return (record.get('errMsg') != "");});
		errRecords.each(function resetError(item) {
			item.set('errMsg', '')
		});
	} //function clearContextErrors

	function updateMoreButton(responseXML) {
		_nextRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
		if (_nextRecNum) {
			_resources.grids['gridExternalTA'].enableButton('moreBtn');			
		}else
			_resources.grids['gridExternalTA'].disableButton('moreBtn');
	} //function updateMoreButton

	function openAdminPopup() {
		title = _translationMap['ExternalTA'] + ' - ' + _translationMap['Admin']
		selectrecord = _resources.grids['gridExternalTA'].getSelectedRecord();

		var adminData = {};
		adminData['userName'] = selectrecord.data['userName'];
		adminData['procDate'] = selectrecord.data['processDate'];
		adminData['modUser'] = selectrecord.data['modUser'];
		adminData['modDate'] = selectrecord.data['modDate'];
		_resources.popups['admin'].init(title, adminData);
		_resources.popups['admin'].show();
	} //penAdminPopup

	function clickHandleMoreBtn() {
		doSearch(_lastFG,_lastLevel, _lastExtAcctSrch, 'reload', true);
	} //clickHandleMoreBtn

	function clickHandleSearchBtn() {
		if (this.updatesFlag) {
			DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
			function handlePromptMsg(btn) {
				if (btn) {
					updatesFlag = false;
					doSearchCallback();
				}
			} //handlePromptMsg
		} else {
			doSearchCallback();
		}

		function doSearchCallback() {
			_nextRecNum = 1
			_resources.grids['gridExternalTA'].reset();
			_lastFG = _resources.fields['fundGrpSrch'].getValue();
			if (!!_lastFG && !!_resources.fields['fundGrpSrch'].getSelectedRecord())
			_lastLevel = _resources.fields['fundGrpSrch'].getSelectedRecord().data.level;
			_lastExtAcctSrch = _resources.fields['extAcctSrch'].getValue();
			
			doSearch(_lastFG,_lastLevel, _lastExtAcctSrch, 'reload', false);
		} //doSearchCallback
	} //clickHandleSearchBtn

	function funcHistoryPopup() {
		var viewParam = {};
		var historyName = null;
		var tempRecord = _resources.grids['gridExternalTA'].getSelectedRecord();

		if (tempRecord != undefined && tempRecord != null) {
			viewParam['auditType'] = 'ExternalTA';
			viewParam['searchValue1'] = tempRecord.data['externalTAUUID'];
			historyName = _translationMap['ExternalTA'] + ' - ' + _translationMap['History'];

			_resources.popups['history'].init(historyName, _historyService, viewParam, true);
			_resources.popups['history'].show();
		}
	} //funcHistoryPopup

	function funcUpdateActionButtons() {
		var grid = _resources.grids['gridExternalTA']
		grid.disableAllButtons();

		_resources.buttons['btnSearch'].disable();

		if (_permissionsMap[INQ])
			_resources.buttons['btnSearch'].enable();

		if (_permissionsMap[ADD])
			grid.enableButton('addBtn');

		var selectedRecord = grid.getSelectedRecord();

		if (!!selectedRecord) {
			grid.enableButton('adminBtn');
			grid.enableButton('historicalBtn');

			if (selectedRecord.data['runMode'] == ADD) {
				grid.enableButton('modBtn');
				grid.enableButton('delBtn');
			} else {
				if (_permissionsMap[MOD] )
					grid.enableButton('modBtn');

				if (_permissionsMap[DEL] && selectedRecord.data['allowDel'] == 'yes')
					grid.enableButton('delBtn');
			}
			//_self.updateContent();
		}
	} //funcUpdateActionButtons

	function funcInitPopup(action) {
		_resources.popups['externalTAPopup'].init(action);
		_resources.popups['externalTAPopup'].show();
		populatePopup(action);
	} //funcInitPopup

	function populatePopup(action) {
		var popup = _resources.popups['externalTAPopup'];
		switch (action) {
			case ADD: {
				var fields = popup.findBy(function (cmp) {
						return (cmp.itemId != null && cmp.itemId.length != 0);
					});
				for (var i = 0; i < fields.length; i++) {
					if (fields[i].rendered)
						fields[i].setValue('');

					fields[i].clearInvalid()
				}
				popup.getField('startDate').setValue(_defaultValues['startDate']);
				popup.getField('stopDate').setValue(_defaultValues['toDate']);
				popup.getField('ruleCode').setValue(_defaultValues['ruleCode']);

				break;
			} //case ADD:
			case MOD: {
				var rec = _resources.grids['gridExternalTA'].getSelectedRecord();

				if (!!rec) {
					
					popup.getField('startDate').setValue(rec.data['startDate']);
					popup.getField('stopDate').setValue(rec.data['stopDate']);
					popup.getField('stopDate').enableField();
					popup.getField('ruleCode').setValue(rec.data['ruleCode']);
					popup.getField('fundGroup').setValue(rec.data['fundGroup']);
					popup.getField('recvNWAddr').setValue(rec.data['recvNWAddr']);
					popup.getField('extAcct').setValue(rec.data['extAcct']);
					if (rec.data.runMode == ADD) {
						popup.enableAllFields();
					}
				} //if (!!rec) 
				break;
			} //case MOD: 
		} //	switch (action) {
	} //populatePopup

	function funcDeleteSelectedRecord() {
		var grid = _resources.grids['gridExternalTA'];
		var tempRecord = grid.getSelectedRecord();
		var index = grid.store.indexOf(tempRecord)
		if (tempRecord.data['runMode'] == ADD) {
			grid.removeSelectedRecord();
			grid.setSelectedRecord(index - 1 <= 0 ? 0 : index - 1);
		} else {
			tempRecord.data['runMode'] = DEL;
			tempRecord.data['stopDate'] = _defaultValues['startDate'];
			tempRecord.commit();
			/*grid.store.filterBy(function (record) {
				return record.data.runMode != _self.DEL;
			});*/
		}
		this.updatesFlag = (getUpdatedRecordCount() > 0);
		funcUpdateActionButtons();

	} //funcDeleteSelectedRecord

	function saveToGrid(action, data) {
		var grid = _resources.grids['gridExternalTA'];
		if (action == this.ADD) {
			data.externalTAUUID = "UUID" + ++_cnewitem;
			grid.addRecord(data);
			grid.selectLastRecord();
		} else if (action == this.MOD) {
			if (isNewRecord(grid.getSelectedRecord())) {
				data['runMode'] = this.ADD
					grid.updateSelectedRecord(data);
			} else {
				grid.updateSelectedRecord(data);
			}
			var index = grid.getSelectionModel().last;
			grid.setSelectedRecord(index);
		}
		this.updatesFlag = (getUpdatedRecordCount() > 0);
	} //saveToGrid

	function doUpdate(mode) {
		var updateStatus = null;
		if (!mode)
			mode = 'update';

		DesktopWeb.Ajax.doSmartviewUpdate(_dtUpdService, null, buildUpdateXML(mode), responseHandler, null);
		function responseHandler(success, responseXML, contextErrors) {
			if (success) {
				updateStatus = DesktopWeb._SUCCESS;
			} else {
				storeContextErrors(contextErrors);
				updateStatus = DesktopWeb._FAIL
			}
		}
		return updateStatus;
	} //doUpdate	

	function doValidatePopup(action, data) {
		var isSuccess = true;
		var popup = _resources.popups['externalTAPopup'];
			
		if (isSuccess && data['startDateObj'] > data['stopDateObj']) {
			isSuccess = false;
			_resources.popups['externalTAPopup'].getField('stopDate').markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
		}

		return isSuccess;
	} //doValidatePopup

	function funcValidateCommitScreen() {
		if (doUpdate('validate') == DesktopWeb._SUCCESS)
			DesktopWeb.Util.commitScreen();
	} /*function funcValidateCommitScreen*/

	// PUBLIC ITEMS *************************************
	return {
		ADD : 'add',
		MOD : 'mod',
		DEL : 'del',
		INQ : 'inq',
		updatesFlag : false,
		init : funcInit,
		updateActionButtons : funcUpdateActionButtons,
		openActionPopup : funcInitPopup,
		deleteSelectedRecord : funcDeleteSelectedRecord,
		openAdminPopup : openAdminPopup,
		savePopup : saveToGrid,
		doUpdate : doUpdate,
		doValidateCommitScreen : funcValidateCommitScreen,
		doValidatePopup : doValidatePopup,		
		clickHandleSearchBtn : clickHandleSearchBtn,
		clickHandleMoreBtn : clickHandleMoreBtn,
		openHistoryPopup : funcHistoryPopup
	}
}
