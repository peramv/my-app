/*********************************************************************************************
 * @file	PaymentRelease.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Payment Release screen
 *********************************************************************************************/
/*
 *  History :
 *
 *  19 Jun 2017 Narin Suanlamyai
 *		- Initail version from converting XSL version to ExtJS version
 *
 *  23 Mar 2018 Supareuk S. CHG0054159 INC0040826
 *      - Added ability to display total record on the screen
 */

DesktopWeb.ScreenController = function () {

	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var ADD = 'ADD';
	var MOD = 'MOD';
	var DEL = 'DEL';
	var INQ = 'INQ';

	var _nextRecNum = {};
	
	var _lastSearchFor = '';
	var _lastPaymentFor = '';
	var _lastBatchStatus = '';
	var _lastSearchValue = '';
	var _lastStartDate = '';
	var _lastEndDate = '';
	var _lastBatchId = '';

	var _dtInit = "dtPaymentBatchInit" //135.P PaymentRelease:q
	var _dtReload = "dtPaymentBatchReload" //136
	var _dtPaymentReload = "dtPaymentRecReload1"
	var _dtGenReload = "dtGenerateBAFFReload";
	var _dtGenInit = "dtGenerateBAFFInit";

	var _smvDateFormat = "mdy";
	var _jobDateFormat = "dmy";

	var _lastFG = '';
	var _lastLevel = '';
	var _lastExtAcctSrch = '';

	var _requestRecNum = 100;
	var _permissionsMap = {};
	var _defaultValues = {};

	var _cnewitem = 0;

	function funcInit(res) {
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;

		_smvDateFormat = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		_jobDateFormat = "dmy";

		DesktopWeb.Ajax.doSmartviewAjax(_dtInit, {
			ignoreErrorCode : '15'
		}, null, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML) {
			if (success) {

				storeDefaultValues(responseXML);
				loadToStore(responseXML);
				_resources.buttons['searchBtn'].enable();
				_resources.buttons['refreshBtn'].enable();
			
				_resources.grids['batchPymtGrid'].disableAllButtons();
				_resources.grids['paymentsGrid'].disableAllButtons();
			}

		}
	} //function funcInit

	function loadToStore(initViewXML) {
		var node = IFDS.Xml.getNode(initViewXML, '/*//List[@listName="SearchTypeOptions"]');
		if (!!node) {
			_resources.fields['searchFor'].getStore().loadData(node);
			if (_resources.fields['searchFor'].getStore().getCount() > 0)
				_resources.fields['searchFor'].setValue(_resources.fields['searchFor'].getStore().getAt(0).get('code'));
			handleSearchChange();
		}

		node = IFDS.Xml.getNode(initViewXML, '/*//List[@id="PaymentForOptions"]');
		if (!!node) {
			_resources.fields['paymentFor'].getStore().loadData(node);
			if (_resources.fields['paymentFor'].getStore().getCount() > 0)
				_resources.fields['paymentFor'].setValue(_resources.fields['paymentFor'].getStore().getAt(0).get('code'));
		}

		node = IFDS.Xml.getNode(initViewXML, '/*//List[@id="BatchStatusOptions"]');
		if (!!node) {
			_resources.fields['batchStatus'].getStore().loadData(node);
			if (_resources.fields['batchStatus'].getStore().getCount() > 1)
				_resources.fields['batchStatus'].allowBlank = true;
				_resources.fields['batchStatus'].setValue(_resources.fields['batchStatus'].getStore().getAt(0).get('code'));
				_resources.fields['batchStatus'].allowBlank = false;
		}

	} //function loadToStore


	function storeDefaultValues(DefaultValuesXML) {
		_defaultValues['fromDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultDates/fromDate'));
		_defaultValues['toDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//DefaultDates/toDate'));
		_defaultValues['allowGenBAFF'] = IFDS.Xml.getNodeValue(DefaultValuesXML, '/*//allowGenBAFF').toLowerCase() == 'yes';
		_nextRecNum['batchPymtGrid'] = '';
		_nextRecNum['paymentGrid'] = '';
		_resources.fields['startDate'].setValue(_defaultValues['fromDate']);
		_resources.fields['toDate'].setValue(_defaultValues['toDate']);
	} //function storeDefaultValues


	

	function doSearch(searchType, searchValue, batchStatus, fromDate, toDate, append) {
		var vRangeEnd = null;
		var vTotalRecord = null;
		var paramXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(paramXML, 'searchType', searchType);
		IFDS.Xml.addSingleNode(paramXML, 'searchValue', searchValue);
		IFDS.Xml.addSingleNode(paramXML, 'batchStatus', batchStatus);
		IFDS.Xml.addSingleNode(paramXML, 'fromDate', fromDate);
		IFDS.Xml.addSingleNode(paramXML, 'toDate', toDate);
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', (_nextRecNum['batchPymtGrid']) ? _nextRecNum['batchPymtGrid'] : '1');
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

		DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _smvDateFormat;

		DesktopWeb.Ajax.doSmartviewAjax(_dtReload, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);
		function responseHandler(success, responseXML) {
			if (success) {
				loadXMLtoGrid(IFDS.Xml.getNode(responseXML, "//PaymentBatches"), append, 'batchPymtGrid');
				
				vRangeEnd = IFDS.Xml.getNodeValue(responseXML, '//rangeEnd');
				vTotalRecord = IFDS.Xml.getNodeValue(responseXML, '//total');
				updatePageNumber("batchPymtGrid", "1", vRangeEnd, vTotalRecord);
			}
		}
	} //doSearch

	function loadXMLtoGrid(xml, append, gridName) {
		if (!!xml) {
			var index = _resources.grids[gridName].getSelectionModel().last;
			index = (index == 0) ? 0 : index;
			_resources.grids[gridName].getStore().loadData(xml, append);			
			_resources.grids[gridName].setSelectedRecord(index);

			updateActionButtons(gridName);
			updateMoreButton(xml, gridName);
		}
	} //loadXMLtoGrid

	function updatePageNumber(vGridName, vRageStart, vRangeEnd, vTotal) {
		
		var pageNumberDispformat = "";
		var transGrid_buttons = null;

		pageNumberDispformat = vRageStart + " - " + vRangeEnd + " of " + vTotal;
		
		transGrid_buttons = _resources.grids[vGridName].buttons;
		transGrid_buttons[0].setValue(pageNumberDispformat);
		transGrid_buttons[0].enable();
	} //function updateMoreButton
	
	function resetPageNumber(gridName) {
		var transGrid_buttons = null;
		transGrid_buttons = _resources.grids[gridName].buttons;
		transGrid_buttons[0].setValue("");
	} //function updateMoreButton

	function updateMoreButton(responseXML, gridName) {
	
		_nextRecNum[gridName] = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
		
		if (_nextRecNum[gridName]) {
			_resources.grids[gridName].enableButton('moreBtn');
		} else
			_resources.grids[gridName].disableButton('moreBtn');
	} //function updateMoreButton

	function openAdminPopup() {
		title = _translationMap['PaymentRelease'] + ' - ' + _translationMap['Admin']
			selectrecord = _resources.grids['batchPymtGrid'].getSelectedRecord();

		var adminData = {};
		adminData['userName'] = selectrecord.data['userNm'];
		adminData['procDate'] = selectrecord.data['procDate'];
		adminData['modUser'] = selectrecord.data['modID'];
		adminData['modDate'] = selectrecord.data['modDate'];
		_resources.popups['admin'].init(title, adminData);
		_resources.popups['admin'].show();
	} //penAdminPopup

	function openGenBAFFPopup() {
		_resources.popups['genBAFFPopup'].show();
		var pymtBatchID = '';
		if (_resources.grids['batchPymtGrid'].getSelectedRecord())
			pymtBatchID = _resources.grids['batchPymtGrid'].getSelectedRecord().data.pymtBatchID;
		_resources.popups['genBAFFPopup'].init(pymtBatchID);
		//

	}

	function genGenBAFFPopup() {
		_resources.popups['genBAFFPopup'].show();
		/*
		runOn
		runTime
		ronNow
		pymtBatchId

		 */

	}

	function clickRefreshBtn() {
		resetPageNumber('paymentsGrid');
		resetPageNumber('batchPymtGrid');
		_resources.grids['paymentsGrid'].reset();
		_resources.grids['batchPymtGrid'].reset();
		_lastBatchId = '';
	}

	function handleSearchChange() {
		//_field
		var tmpSearchFor = _resources.fields['searchFor'].getValue().toLowerCase();

		switch (tmpSearchFor) {
		case "paymentfor":
			_resources.fields['paymentFor'].show();
			_resources.fields['batchStatus'].enable();
			_resources.fields['startDate'].enable();
			_resources.fields['toDate'].enable();
			_resources.fields['searchValue'].reset();
			_resources.fields['searchValue'].hide();
			break;
		case "batchid":
		case "batchname":
			_resources.fields['paymentFor'].hide();
			_resources.fields['paymentFor'].clearInvalid();
			_resources.fields['batchStatus'].disable();
			_resources.fields['batchStatus'].clearInvalid();
			_resources.fields['startDate'].disable();
			_resources.fields['startDate'].clearInvalid();
			_resources.fields['toDate'].disable();
			_resources.fields['toDate'].clearInvalid();
			_resources.fields['searchValue'].show();
			break;
		}

	}
	function clickHandleMoreBtn(gridName) {
		//doSearch(_lastFG, _lastLevel, _lastExtAcctSrch, 'reload', true);
		if (gridName.toLowerCase() == 'batchpymtgrid')
			doSearch(_lastSearchFor, _lastSearchValue, _lastBatchStatus, _lastStartDate, _lastEndDate, true);
		else
			reloadPayment(_resources.grids['batchPymtGrid'].getSelectedRecord().data, true);

	} //clickHandleMoreBtn

	function clickHandleSearchBtn() {
		if (validateSearch()) {
			if (this.updatesFlag) {
				DesktopWeb.Util.displayYesNo(handlePromptMsg)
				function handlePromptMsg(btn) {
					if (btn) {
						updatesFlag = false;
						doSearchCallback();
					}
				} //handlePromptMsg
			} else {
				doSearchCallback();
			}
		}
	} //clickHandleSearchBtn

	function doSearchCallback() {

		clickRefreshBtn();
		_lastSearchFor = _resources.fields['searchFor'].getValue();

		if (_lastSearchFor.toLowerCase() == "paymentfor") {
			_lastPaymentFor = _resources.fields['paymentFor'].getValue();
			_lastBatchStatus = _resources.fields['batchStatus'].getValue();

			_lastStartDate = DesktopWeb.Util.getSMVDateValue(_resources.fields['startDate'].getDisplayDateString());
			_lastEndDate = DesktopWeb.Util.getSMVDateValue(_resources.fields['toDate'].getDisplayDateString());

			_lastSearchValue = _lastPaymentFor;
		} else {
			_lastSearchValue = _resources.fields['searchValue'].getValue();
			_lastBatchStatus = _lastStartDate = _lastEndDate = "";
		}

		_nextRecNum['batchPymtGrid'] = 1;
		doSearch(_lastSearchFor, _lastSearchValue, _lastBatchStatus, _lastStartDate, _lastEndDate, false);

	} //doSearchCallback


	function validateSearch() {
		var allowSearch = false;

		if (_resources.fields['searchFor'].isValid()) {
			if (_resources.fields['searchFor'].getValue().toLowerCase() == "paymentfor") {

				allowSearch = (_resources.fields['paymentFor'].isValid() &&
					_resources.fields['batchStatus'].isValid() &&
					_resources.fields['startDate'].isValid() &&
					_resources.fields['toDate'].isValid());

				if (allowSearch && 
						_resources.fields['startDate'].getValue() >  _resources.fields['toDate'].getValue()) {
					allowSearch = false;
					_resources.fields['startDate'].markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
				}
				else
					_resources.fields['startDate'].clearInvalid();
			} else {
				allowSearch = (_resources.fields['searchValue'].getValue() != '');
			}
		}
		
		

		return allowSearch;
	}

	function updateActionButtons(gridName) {

		if (gridName == 'batchPymtGrid') {

			var selectedRecord = _resources.grids['batchPymtGrid'].getSelectedRecord();

			if (!!selectedRecord) {
				_resources.grids['paymentsGrid'].enableButton('adminBtn');

				if (!!selectedRecord.data.stat && selectedRecord.data.stat.toLowerCase() == 'o' &&
					_defaultValues['allowGenBAFF']) {
					_resources.grids['paymentsGrid'].enableButton('genBAFFBtn');
				} else
					_resources.grids['paymentsGrid'].disableButton('genBAFFBtn');

			} else {
				_resources.grids['paymentsGrid'].disableButton('adminBtn');
			}
		}
	} //funcUpdateActionButtons

	
	function reloadPayment(record, append) {
		
		if (record.pymtBatchID != _lastBatchId || append) {
			_lastBatchId = record.pymtBatchID;
			
			var vRangeEnd = null;
			var vTotalRecord = null;
			var paramXML = IFDS.Xml.newDocument('data');
			var paramXMLForTotalRec = IFDS.Xml.newDocument('data');
			
			IFDS.Xml.addSingleNode(paramXML, 'searchType', 'batchid');
			IFDS.Xml.addSingleNode(paramXML, 'searchValue', _lastBatchId);

			IFDS.Xml.addSingleNode(paramXML, 'fromDate', _lastStartDate);
			IFDS.Xml.addSingleNode(paramXML, 'toDate', _lastEndDate);
			
			paramXMLForTotalRec = paramXML;
			
			/* Reset next record number when selected the record on upper grid 
			 */ 
			if (!append){ 
				_nextRecNum['paymentsGrid'] = '1';
			}
			
			IFDS.Xml.addSingleNode(paramXML, 'startRecNum', _nextRecNum['paymentsGrid']);
			IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

			DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _smvDateFormat;
			DesktopWeb.Ajax.doSmartviewAjax(_dtPaymentReload, {
				ignoreErrorCode : '15'
			}, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);
			function responseHandler(success, responseXML) {
				if (success) {
					loadXMLtoGrid(IFDS.Xml.getNode(responseXML, "//ConsolidatedPayments"), append, 'paymentsGrid');
					//getTotalRecordNum(paramXMLForTotalRec);
					vRangeEnd = IFDS.Xml.getNodeValue(responseXML, '//rangeEnd');
					getTotalRecordNum(paramXMLForTotalRec, vRangeEnd);
					
				}
			}
		}
	}
	
	function getTotalRecordNum(paramXML, vRangeEnd){		
		var vTotalRecord = null;
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtPaymentReload, {
			ignoreErrorCode : '15'
		}, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML) {
			if (success) {
				vTotalRecord = IFDS.Xml.getNodeValue(responseXML, '//totRecCnt');
				updatePageNumber("paymentsGrid", "1", vRangeEnd, vTotalRecord);
			} 
		}
	}

	//Batch section
	function initBatch() {
		//dtGenerateBAFFInit
		var paramXML = IFDS.Xml.newDocument('data');
		DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _smvDateFormat;

		DesktopWeb.Ajax.doSmartviewAjax(_dtGenInit, {
			ignoreErrorCode : '15'
		}, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);
		function responseHandler(success, responseXML) {
			if (success) {
				var runDate = IFDS.Xml.getNodeValue(responseXML, '/*//runOn');
				var runTime = IFDS.Xml.getNodeValue(responseXML, '/*//runTime');

				var tempDate = new Date(runDate);
				var hourmin = runTime.split(":");

				tempDate.setHours(hourmin[0]);
				tempDate.setMinutes(hourmin[1]);

				_resources.popups['genBAFFPopup'].getField('runOn').setValue(tempDate);
				_resources.popups['genBAFFPopup'].getField('runAt').setValue(tempDate);

			}

			doBatchCheck();
		}
	}

	function generateBatch(data) {
		//dtGenerateBAFFInit
		var paramXML = IFDS.Xml.newDocument('data');

		DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _jobDateFormat;
		IFDS.Xml.addSingleNode(paramXML, 'runOn', data['runOn'].format(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb._SCREEN_PARAM_MAP['dateFormat'])));
		IFDS.Xml.addSingleNode(paramXML, 'runTime', data['runTime']);

		IFDS.Xml.addSingleNode(paramXML, 'runNow', data['runNow']);
		IFDS.Xml.addSingleNode(paramXML, 'pymtBatchId', data['pymtBatchId']);

		DesktopWeb.Ajax.doSmartviewAjax(_dtGenReload, {
			ignoreErrorCode : '15'
		}, paramXML, responseHandler, _translationMap['ProcMsg_Processing']);
		function responseHandler(success, responseXML) {
			if (success) {
				DesktopWeb.Util.displayInfo(_translationMap['JobSuccess'], function () {
					_resources.popups['genBAFFPopup'].hide();
				});
			}
		}
	}

	function doBatchCheck() {

		if (_resources.popups['genBAFFPopup'].getField("runNow").getValue()) {
			_resources.popups['genBAFFPopup'].getField('runOn').disable();
			_resources.popups['genBAFFPopup'].getField('runAt').disable();

		} else {
			_resources.popups['genBAFFPopup'].getField('runOn').enable();
			_resources.popups['genBAFFPopup'].getField('runAt').enable();
		}

	}

	// PUBLIC ITEMS *************************************
	return {
		updatesFlag : false,
		init : funcInit,
		updateActionButtons : updateActionButtons,
		openAdminPopup : openAdminPopup,
		openGenBAFFPopup : openGenBAFFPopup,
		handleSearchChange : handleSearchChange,
		reloadPayment : reloadPayment,
		clickHandleSearchBtn : clickHandleSearchBtn,
		clickHandleMoreBtn : clickHandleMoreBtn,
		doBatchCheck : doBatchCheck,
		validateSearch : validateSearch,
		initBatch : initBatch,
		generateBatch : generateBatch,
		clickRefreshBtn : clickRefreshBtn
		//openHistoryPopup : funcHistoryPopup
	}
}
