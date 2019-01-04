/*******************************************************************************
 * @file WhtRatesMaint.Controller.js
 * @author Hatthaseriphong, Nopphawan
 * @desc Controller JS file of the Withholding Tax Rates Maintenance
 ******************************************************************************/
/*
 * Procedure: WhtRatesMaint.Controller.js
 * 
 * Purpose : Controller for Withholding Tax Rates Maintenance screen
 * 
 * Notes : - Withholding Tax Rates Maintenance 
 *         - Open screen from Menu -> System Maintenance -> Withholding Tax Rates Maintenance
 * 
 * History :
 * 
 * 05 Jan 2018 N. Hatthaseriphong P0274848 Withholding Tax Rates Maintenance 
 *             - Created
 * 
 */

DesktopWeb.ScreenController = function() {
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _resources = null;
	var _nextStartRecNum = null;
	var _requestRecNum = 25; // The number of record display on table
	var _uuidRunning = 0;

	var _currFileType = null;
	var _currSearchObj = new Object;

	var _interfaceFileXML = null;
	var _interfaceFileReloadXML = null;

	var _dtWithHoldTaxRatesInq = "dtWithHoldTaxRatesInq";
	var _dtWithHoldTaxRatesUpd = "dtWithHoldTaxRatesUpd";

	var _SCREENMODE_UPD = 'upd';

	var _INQPERM = 'inqPerm'
	var _ADDPERM = 'addPerm';
	var _MODPERM = 'modPerm';
	var _DELPERM = 'delPerm';
	var _VERPERM = 'verPerm';

	var _RUNMODE_INIT = 'init';
	var _RUNMODE_RELOAD = 'reload';
	var _RUNMODE_ADD = 'add';
	var _RUNMODE_MOD = 'mod';
	var _RUNMODE_DEL = 'del';
	var _RUNMODE_VER = 'ver';

	var _ADDBTN = 'addBtn';
	var _MODBTN = 'modBtn';
	var _DELBTN = 'delBtn';
	var _VERBTN = 'verBtn';
	var _MOREBTN = 'moreBtn';
	var _ADMINBTN = 'adminBtn';

	var _DEFAULT_START_DATE = null;
	var _DEFAULT_STOP_DATE = null;

	var _whtGrid = null;
	var _whtMaintPopup = null;

	var _permissionsMap = {};
	var _dropdownListMap = {};
	var _whtPopFldList = {};

	// ****** resource's object ******/
	function initResourceName() {
		_whtGrid = _resources.grids['whtGrid'];
		_whtMaintPopup = _resources.popups['whtMaintPopup'];

		// all fields in whtMaintPopup
		_whtPopFldList['taxJuris'] = 'pTaxJurisFld';
		_whtPopFldList['taxModel'] = 'pTaxModelFld';
		_whtPopFldList['factorCode'] = 'pComponentFld';
		_whtPopFldList['rateType'] = 'pRateTypeFld';
		_whtPopFldList['rate'] = 'pTaxRateFld';
		_whtPopFldList['startDate'] = 'pStartDateFld';
		_whtPopFldList['stopDate'] = 'pStopDateFld';
		_whtPopFldList['verifyStat'] = 'pVerifyStatFld';
		_whtPopFldList['applyAll'] = 'pApplyAllChk';
	}

	function initialButton() {
		if (_permissionsMap[_INQPERM])
			_resources.buttons['searchBtn'].enable();
		if (_permissionsMap[_ADDPERM])
			_whtGrid.enableButton(_ADDBTN);
	}

	function enableScreen() {
		if (_permissionsMap[_ADDPERM])
			_whtGrid.enableButton(_ADDBTN);
		if (_permissionsMap[_MODPERM])
			_whtGrid.enableButton(_MODBTN);
		if (_permissionsMap[_DELPERM])
			_whtGrid.enableButton(_DELBTN);
		if (_permissionsMap[_VERPERM])
			_whtGrid.enableButton(_VERBTN);

		_whtGrid.enableButton(_ADMINBTN);
	}

	function disableScreen() {
		_resources.buttons['searchBtn'].disable();
		_whtGrid.disableButton(_ADDBTN);
		_whtGrid.disableButton(_MODBTN);
		_whtGrid.disableButton(_DELBTN);
		_whtGrid.disableButton(_VERBTN);
		_whtGrid.disableButton(_MOREBTN);
		_whtGrid.disableButton(_ADMINBTN);
	}

	// ****** store user permission ******/
	function storePermissions(initViewXML) {
		_permissionsMap[_INQPERM] = IFDS.Xml.getNodeValue(initViewXML,
				'//Permissions/inqPerm').toLowerCase() == _self.YES;
		_permissionsMap[_ADDPERM] = IFDS.Xml.getNodeValue(initViewXML,
				'//Permissions/addPerm').toLowerCase() == _self.YES;
		_permissionsMap[_MODPERM] = IFDS.Xml.getNodeValue(initViewXML,
				'//Permissions/modPerm').toLowerCase() == _self.YES;
		_permissionsMap[_DELPERM] = IFDS.Xml.getNodeValue(initViewXML,
				'//Permissions/delPerm').toLowerCase() == _self.YES;
		_permissionsMap[_VERPERM] = IFDS.Xml.getNodeValue(initViewXML,
				'//Permissions/verPerm').toLowerCase() == _self.YES;
	}

	// ****** load all drop-down lists ******/
	function populateDropdownList(responseXML) {
		var taxJurisListNode = IFDS.Xml.getNode(responseXML,
				"//List[@listName='taxJurisList']");
		var taxModelListNode = IFDS.Xml.getNode(responseXML,
				"//List[@listName='taxModelList']");
		var componentListNode = IFDS.Xml.getNode(responseXML,
				"//List[@listName='factorCodeList']");
		var rateTypeListNode = IFDS.Xml.getNode(responseXML,
				"//List[@listName='rateTypeList']");
		var verifyStatListNode = IFDS.Xml.getNode(responseXML,
				"//List[@listName='verifyStatList']");

		_dropdownListMap['taxJuris'] = taxJurisListNode;
		_dropdownListMap['taxModel'] = taxModelListNode;
		_dropdownListMap['factorCode'] = componentListNode;
		_dropdownListMap['rateType'] = rateTypeListNode;
		_dropdownListMap['verifyStat'] = verifyStatListNode;

		// main screen (search criteria)
		_resources.fields['taxJuris'].loadData(taxJurisListNode);
		_resources.fields['taxModel'].loadData(taxModelListNode);

		// whtMaintPopup pop-up
		_whtMaintPopup.getField('pTaxJurisFld').loadData(taxJurisListNode);
		_whtMaintPopup.getField('pTaxJurisFld').getStore().removeAt(0); // remove
		// ALL
		_whtMaintPopup.getField('pTaxModelFld').loadData(taxModelListNode);
		_whtMaintPopup.getField('pTaxModelFld').getStore().removeAt(0); // remove
		// ALL
		_whtMaintPopup.getField('pComponentFld').loadData(componentListNode);
		_whtMaintPopup.getField('pRateTypeFld').loadData(rateTypeListNode);
		_whtMaintPopup.getField('pVerifyStatFld').loadData(verifyStatListNode);
	}

	// ****** populate initial value ******/
	function loadDefaultValues(initViewXML) {
		var defaultValuesNode = IFDS.Xml.getNode(initViewXML, "//DefaultValues");

		// drop-down list selected
		var taxJuris = IFDS.Xml.getNodeValue(initViewXML,
				"/*//ListSelection[@id = 'taxJurisList']");
		var taxModel = IFDS.Xml.getNodeValue(initViewXML,
				"/*//ListSelection[@id = 'taxModelList']");

		_resources.fields['taxJuris'].setValue(taxJuris);
		_resources.fields['taxModel'].setValue(taxModel);

		_DEFAULT_START_DATE = IFDS.Xml.getNodeValue(defaultValuesNode, 'startDate');
		_DEFAULT_STOP_DATE = IFDS.Xml.getNodeValue(defaultValuesNode, 'stopDate');
	}

	/** ******* public function ******** */

	/** * TODO INIT ** */
	function init(res) {
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;

		initResourceName();
		disableScreen();

		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);

		DesktopWeb._SCREEN_PARAM_MAP['interfaceName'] = 'ifds.dt.System.WithHoldTaxRates';
		DesktopWeb.Ajax.doSmartviewAjax(_dtWithHoldTaxRatesInq, null, dataXML,
				responseHandler, _translationMap['ProcMsg_Searching']);

		function responseHandler(success, responseXML) {
			if (success) {
				storePermissions(responseXML);
				populateDropdownList(responseXML);
				loadDefaultValues(responseXML);
				initialButton();
			}
		}
	}

	function getListDescription(listName, value) {
		if (!!_dropdownListMap[listName])
			return IFDS.Xml.getNodeValue(_dropdownListMap[listName],
					'Element[code = "' + value + '"]/value');
		return '';
	}

	function recordHandler(isActive, isAllowVerify) {
		// only active records can be modify, delete, verify
		if (isActive == _self.YES) {
			enableScreen();
			if (isAllowVerify == _self.NO)
				_whtGrid.disableButton(_VERBTN);
		} else {
			_whtGrid.disableButton(_MODBTN);
			_whtGrid.disableButton(_DELBTN);
			_whtGrid.disableButton(_VERBTN);
		}
	}

	function doValidateSearch() {
		var taxJuris = _resources.fields['taxJuris'].isValid();
		var taxModel = _resources.fields['taxModel'].isValid();
		return (taxJuris && taxModel);
	}

	function doValidateSave() {
		var currentBusinessDate = DesktopWeb.Util.stringToDate(_DEFAULT_START_DATE);
		var startDate = _whtMaintPopup.getField('pStartDateFld').getValue();
		var stopDate = _whtMaintPopup.getField('pStopDateFld').getValue();

		if (startDate > stopDate) {
			_whtMaintPopup.getField('pStopDateFld').markInvalid(
					_translationMap['ERR_STOP_CANNOT_EARLIER_THAN_DEFF']);
			return false;
		} else {
			// inactive record is not allowed to input
			if (startDate > currentBusinessDate) {
				_whtMaintPopup.getField('pStartDateFld').markInvalid(
						_translationMap['ERR_DEFF_CANNOT_GREATER_THAN_CURBUSDATE']);
				return false;
			}
			if (stopDate < currentBusinessDate) {
				_whtMaintPopup.getField('pStopDateFld').markInvalid(
						_translationMap['ERR_STOP_CANNOT_EARLIER_THAN_CURBUSDATE']);
				return false;
			}
		}

		return true;
	}

	function doSearch(getMore) {
		var dataXML = IFDS.Xml.newDocument('data');

		IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_RELOAD);
		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', getMore ? _nextStartRecNum
				: 1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);
		IFDS.Xml.addSingleNode(dataXML, 'taxJuris', _resources.fields['taxJuris']
				.getValue());
		IFDS.Xml.addSingleNode(dataXML, 'taxModel', _resources.fields['taxModel']
				.getValue());
		IFDS.Xml.addSingleNode(dataXML, 'activeOnly',
				_resources.fields['activeBox'].getValue() == 0 ? _self.NO : _self.YES);

		DesktopWeb.Ajax.doSmartviewAjax(_dtWithHoldTaxRatesInq, null, dataXML,
				responseHandler, _translationMap['ProcMsg_Searching']);

		function responseHandler(success, responseXML) {
			if (success) {
				_whtGrid.getStore().loadData(
						IFDS.Xml.getNode(responseXML, "//DistributionTaxList"), getMore);

				if (getMore) {
					_whtGrid.getSelectionModel().selectRow(_nextStartRecNum - 1);
					_whtGrid.focusRow(_nextStartRecNum - 1);
				}
				_nextStartRecNum = DesktopWeb.Ajax
						.getSmartviewNextStartRecNum(responseXML);

				if (_nextStartRecNum)
					_whtGrid.enableButton(_MOREBTN);
				else
					_whtGrid.disableButton(_MOREBTN);

				// set record's permission
				recordHandler(_whtGrid.getSelectedRecord().data['active'], _whtGrid
						.getSelectedRecord().data['allowVerify']);

			} else {
				_whtGrid.clearData();
				initialButton();
			}
		}
	}

	function doSave(action) {
		var whtRecord = _whtGrid.getSelectedRecord();
		var whtData = {};

		var runMode = action;
		var version = 0; // _RUNMODE_ADD's version = 0
		var whtUUID = "";
		var taxJuris = _whtMaintPopup.getField('pTaxJurisFld').getValue();
		var taxModel = _whtMaintPopup.getField('pTaxModelFld').getValue();
		var component = _whtMaintPopup.getField('pComponentFld').getValue();
		var rateType = _whtMaintPopup.getField('pRateTypeFld').getValue();
		var taxRate = _whtMaintPopup.getField('pTaxRateFld').getValue();
		var startDate = DesktopWeb.Util.getSMVDateValue(_whtMaintPopup.getField(
				'pStartDateFld').getDisplayDateString());
		var stopDate = DesktopWeb.Util.getSMVDateValue(_whtMaintPopup.getField(
				'pStopDateFld').getDisplayDateString());
		var verifyStat = _whtMaintPopup.getField('pVerifyStatFld').getValue();
		var applyAll = _whtMaintPopup.getField('pApplyAllChk').getValue() == 0 ? _self.NO
				: _self.YES;

		if (action == _RUNMODE_MOD || action == _RUNMODE_DEL
				|| action == _RUNMODE_VER) {
			whtUUID = whtRecord.data['whdRatesUUID'];
			version = whtRecord.data['version'];
		}

		// set withholding tax rates request values
		whtData['runMode'] = runMode;
		whtData['version'] = version;
		whtData['whdRatesUUID'] = whtUUID;
		whtData['taxJuris'] = taxJuris;
		whtData['taxModel'] = taxModel;
		whtData['factorCode'] = component;
		whtData['rateType'] = rateType;
		whtData['rate'] = taxRate;
		whtData['startDate'] = startDate;
		whtData['stopDate'] = stopDate;
		whtData['verifyStat'] = verifyStat;
		whtData['applyAll'] = applyAll;

		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'screenMode', _SCREENMODE_UPD);

		// create request tags
		for ( var tag in whtData) {
			IFDS.Xml.addSingleNode(dataXML, tag, whtData[tag]);
		}

		DesktopWeb.Ajax.doSmartviewUpdate(_dtWithHoldTaxRatesUpd, null, dataXML,
				responseHandler, _translationMap['ProcMsg_Processing']);

		function responseHandler(success, responseXML) {
			if (success) {
				// notification message when use apply all process
				if (applyAll == _self.YES) {
					DesktopWeb.Util.displayWarning(_translationMap['WRN_APPLY_ALL']);
				}
				// response the updated record(s) for displaying on the screen
				var whtNode = IFDS.Xml.getNode(responseXML, "//DistributionTaxList");

				if (whtNode != null) {
					switch (action) {
						case _RUNMODE_ADD: // add successfully
							var whtListNode = IFDS.Xml.newDocument('DistributionTaxList');
							var whtInfoNode = IFDS.Xml.getNode(responseXML,
									"/*//DistributionTaxInfo[taxJuris='" + taxJuris + "']");
							IFDS.Xml.appendNode(whtListNode, whtInfoNode);
							_whtGrid.getStore().loadData(whtListNode, true);
							_whtGrid.selectLastRecord();
							break;
						case _RUNMODE_MOD: // modify successfully
							var whtInfoNode = IFDS.Xml.getNode(responseXML,
									"/*//DistributionTaxInfo[referredUUID='" + whtUUID + "']");
							setUpdatedDataToGrid(whtInfoNode, whtRecord);
							break;
						case _RUNMODE_DEL: // delete successfully
							var rowIndex = _whtGrid.getRecordIndex(whtRecord);
							// remove the deleted record from the screen
							whtRecord.data['runMode'] = _RUNMODE_DEL;
							_whtGrid.store.filterBy(function(record) {
								return record.data.runMode != _RUNMODE_DEL;
							});
							if (rowIndex == _whtGrid.getStore().getCount())
								// delete the last row, focus on the previous row
								_whtGrid.setSelectedRecord(rowIndex - 1);
							else
								// after delete successfully, focus on the next row
								_whtGrid.setSelectedRecord(rowIndex);
							break;
						case _RUNMODE_VER: // verify successfully
							var whtInfoNode = IFDS.Xml.getNode(responseXML,
									"/*//DistributionTaxInfo[referredUUID='" + whtUUID + "']");
							setUpdatedDataToGrid(whtInfoNode, whtRecord);
							break;
					} // switch-case
				} // if (whtNode != null)
				// after process is successful, set record's permission and hide the pop-up
				if (_whtGrid.getStore().getCount() == 0) { // there is no record on the screen
					disableScreen();
					initialButton();
				} else {
					recordHandler(_whtGrid.getSelectedRecord().data['active'], _whtGrid
							.getSelectedRecord().data['allowVerify']);
				}
				_whtMaintPopup.hide();
			} // if (success)
		} // responseHandler
	}

	function setUpdatedDataToGrid(node, selectedRecord) {
		var value = "";
		for ( var field in selectedRecord.data) {
			value = IFDS.Xml.getNodeValue(node, field);
			// set date format for date fields
			if (field.match(/date/i) != null)
				value = DesktopWeb.Util.getDateDisplayValue(value);
			// set data to grid
			selectedRecord.data[field] = value;
		}
		selectedRecord.commit();
	}

	function openWhtMaintPopup(action) {
		_whtMaintPopup.getField('pApplyAllChk').setValue('');
		_whtMaintPopup.getField('pApplyAllChk').show();

		// populate pop-up by action mode
		if (action == _RUNMODE_ADD) {
			for ( var name in _whtPopFldList) {
				if (_whtMaintPopup.rendered)
					_whtMaintPopup.getField(_whtPopFldList[name]).setValue('');

				_whtMaintPopup.getField(_whtPopFldList[name]).clearInvalid();
				_whtMaintPopup.getField(_whtPopFldList[name]).enableField();
			}

			_whtMaintPopup.getField('pStartDateFld').disableField();
			_whtMaintPopup.getField('pStartDateFld').setValue(
					DesktopWeb.Util.getDateDisplayValue(_DEFAULT_START_DATE));
			_whtMaintPopup.getField('pStopDateFld').setValue(
					DesktopWeb.Util.getDateDisplayValue(_DEFAULT_STOP_DATE));

			// always add a new record with unverified status (02)
			_whtMaintPopup.getField('pVerifyStatFld').disableField();
			_whtMaintPopup.getField('pVerifyStatFld').setValue('02');

		} else {
			var whtRecord = _whtGrid.getSelectedRecord();

			_whtMaintPopup.getField('pTaxJurisFld').setValue(
					whtRecord.data['taxJuris']);
			_whtMaintPopup.getField('pTaxModelFld').setValue(
					whtRecord.data['taxModel']);
			_whtMaintPopup.getField('pComponentFld').setValue(
					whtRecord.data['factorCode']);
			_whtMaintPopup.getField('pRateTypeFld').setValue(
					whtRecord.data['rateType']);
			_whtMaintPopup.getField('pTaxRateFld').setValue(whtRecord.data['rate']);
			_whtMaintPopup.getField('pStartDateFld').setValue(
					whtRecord.data['startDate']);
			_whtMaintPopup.getField('pStopDateFld').setValue(
					whtRecord.data['stopDate']);
			_whtMaintPopup.getField('pVerifyStatFld').setValue(
					whtRecord.data['verifyStat']);

			for ( var name in _whtPopFldList) {
				_whtMaintPopup.getField(_whtPopFldList[name]).disableField();
			}

			if (action == _RUNMODE_MOD) {
				_whtMaintPopup.getField('pTaxRateFld').enableField();
				_whtMaintPopup.getField('pTaxRateFld').focus();
				_whtMaintPopup.getField('pApplyAllChk').enableField();
			}

			if (action == _RUNMODE_DEL) {
				_whtMaintPopup.getField('pApplyAllChk').hide();
			}

			if (action == _RUNMODE_VER) {
				_whtMaintPopup.getField('pVerifyStatFld').enableField();
				_whtMaintPopup.getField('pVerifyStatFld').focus();
				_whtMaintPopup.getField('pApplyAllChk').hide();
			}
		}

		_resources.popups['whtMaintPopup'].init(action);
		_resources.popups['whtMaintPopup'].show();
	}

	function openAdminPopup() {
		var title = null;
		var xml = null;

		title = _translationMap["WhtRatesMaint"] + ' - ' + _translationMap['Admin'];
		xml = _whtGrid.getSelectedRecord();

		if (xml && xml != undefined) {
			var adminData = {};
			adminData['userName'] = xml.data['userName'];
			adminData['procDate'] = xml.data['processDate'];
			adminData['modUser'] = xml.data['modUser'];
			adminData['modDate'] = xml.data['modDate'];

			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();
		}
	}

	// PUBLIC ITEMS *************************************
	return {
		init : init,
		recordHandler : recordHandler,
		getListDescription : getListDescription,
		doValidateSearch : doValidateSearch,
		doValidateSave : doValidateSave,
		doSearch : doSearch,
		doSave : doSave,
		openWhtMaintPopup : openWhtMaintPopup,
		openAdminPopup : openAdminPopup,
		RUNMODE_ADD : _RUNMODE_ADD,
		RUNMODE_MOD : _RUNMODE_MOD,
		RUNMODE_DEL : _RUNMODE_DEL,
		RUNMODE_VER : _RUNMODE_VER,
		BLANK : '',
		YES : 'yes',
		NO : 'no'
	}
}