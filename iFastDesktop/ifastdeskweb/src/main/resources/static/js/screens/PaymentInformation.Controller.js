/*********************************************************************************************
 * @file	PaymentInformation.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Payment Information screen
 *********************************************************************************************/
/*
 *  History :
 *
 *  19 Jun 2017 Narin Suanlamyai/ Gomoot T.
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

	var _MOD = 'MOD';

	var _lastPymtId = '';
	var _page_number = '';
	var _conPymtPageNum = '';
	var _verify = false;
	var _approve = false;
	var _stop = false;
	var _massStatus = null;

	var _requestRecNum = 100;
	var _nextRecNum = {};

	var _defaultValues = {};
	var _currentSearch = {};
	var _permissionsMap = {};
	var _searchValue = {};
	var _searchValueFields = ['searchType', 'searchValue', 'pymtFor', 'fromDate', 'toDate', 'broker', 'branch', 'slsRep', 'payType', 'pStatus', 'accountNum'];
	var _fieldList = ['paymentFor', 'searchValue', 'paymentType', 'paymentStatus','accountFld','brokerFld', 'branchFld', 'slsrepFld','startDate','toDate'];

	var _dtPaymentRecInit = "dtPaymentRecInit";
	var _dtReload1 = "dtPaymentRecReload1"; //84.P - 100 record
	var _dtReload2 = "dtPaymentRecReload2";
	var _dtUpd = "dtPaymentRecUpd"; //139.P
	
	var _historyService = 'dtHistoricalInfo';

	// PRIVATE METHODS ****************************************
	function initLocalValues() {
		for (var i = 0; i < _searchValueFields.length; i++)
			_searchValue[_searchValueFields[i]] = '';

		_nextRecNum['conPymtGrid'] = '';
		_nextRecNum['transGrid'] = '';
		_nextRecNum['paymentsGrid'] = '';
		_massStatus = null;
	}
	function init(res) {
		_resources = res;
		_self = DesktopWeb._SCREEN_CONTROLLER;
		initLocalValues();

		_resources.grids['transGrid'].show();
		_resources.grids['paymentsGrid'].hide();
		_resources.layout.get('childLayout').setTitle(_translationMap['Transactions']);
		
		// Call init service
		var dataXML = IFDS.Xml.newDocument('data');

		DesktopWeb.Ajax.doSmartviewAjax(_dtPaymentRecInit, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])

		function responseHandler(success, responseXML) {
			//prompt("Payment Informaiton Initail response", IFDS.Xml.serialize(responseXML));
			if (success) {
				
				storeDefaultValues(responseXML);
				// Load dropdown
				enableScreen();
				populateDropdownList(responseXML);

				if (!!DesktopWeb._SCREEN_PARAM_MAP['searchType'] && DesktopWeb._SCREEN_PARAM_MAP['searchType'].toLowerCase() == 'transnumber') {

					_resources.fields['searchFor'].setValue('transNum');
					_resources.fields['searchValue'].setValue(DesktopWeb._SCREEN_PARAM_MAP['searchValue']);
					handleSearchChange();
					doSearch(false);
				}
			} else {
				disableScreen();

			}
		}
	}
	/** Store user permission **/
	function storePermissions(responseXML) {
		/**
		 ** Permissions is not sent in initial service, dtPaymentRecInit
		 ** while implementing the ExtJS version.
		 **
		 **/
	}

	function storeDefaultValues(responseXML) {
		var defaultDatesNode = IFDS.Xml.getNode(responseXML, "//DefaultDates");
		_defaultValues['fromDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultDatesNode, 'frmDt'));
		_defaultValues['toDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultDatesNode, 'toDt'));

		_defaultValues['pymtStatus'] = IFDS.Xml.getNodeValue(responseXML, 'pymtStatus');

		_resources.fields['startDate'].setValue(_defaultValues['fromDate']);
		_resources.fields['toDate'].setValue(_defaultValues['toDate']);
	}

	function populateDropdownList(responseXML) {
		try {
			_resources.fields['searchFor'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'SearchTypeFilter']"));
			_resources.fields['paymentFor'].loadData(IFDS.Xml.getNode(responseXML, "//List[@id = 'PaymentForOptions']"));
			_resources.fields['paymentType'].loadData(IFDS.Xml.getNode(responseXML, "//List[@id = 'PaymentTypeOptions']"));
			_resources.fields['paymentStatus'].loadData(IFDS.Xml.getNode(responseXML, "//List[@id = 'PaymentStatusOptions']"));

			_defaultValues['PaymentStatusOptions'] = IFDS.Xml.getNodeValue(responseXML, "//ListSelection[@id = 'PaymentStatusOptions']")
			_defaultValues['PaymentTypeOptions'] = IFDS.Xml.getNodeValue(responseXML, "//ListSelection[@id = 'PaymentTypeOptions']")


			if (_resources.fields['searchFor'].getStore().getCount() > 0)
				_resources.fields['searchFor'].setValue(_resources.fields['searchFor'].getStore().getAt(0).get('code'));

			if (_resources.fields['paymentStatus'].getStore().getCount() > 0)
				_resources.fields['paymentStatus'].setValue(_resources.fields['paymentStatus'].getStore().getAt(0).get('code'));

			if (_resources.fields['paymentType'].getStore().getCount() > 0)
				_resources.fields['paymentType'].setValue(_resources.fields['paymentType'].getStore().getAt(0).get('code'));
			
			handleSearchChange();

			_resources.buttons['searchBtn'].enable();
		} catch (err) {
			DesktopWeb.Util.displayError("Cannot load dropdown list", function () {
				disableScreen();
			});
		}
	}

	function doSearch(append) {

		var paramXML = IFDS.Xml.newDocument('data');
		var disableAll = false;

		if (!!DesktopWeb._SCREEN_PARAM_MAP['searchType'] && DesktopWeb._SCREEN_PARAM_MAP['searchType'].toLowerCase() == 'transnumber') {
			disableAll = true;
			IFDS.Xml.addSingleNode(paramXML, 'searchType', DesktopWeb._SCREEN_PARAM_MAP['searchType']);
			IFDS.Xml.addSingleNode(paramXML, 'searchValue', DesktopWeb._SCREEN_PARAM_MAP['searchValue']);

			IFDS.Xml.addSingleNode(paramXML, 'startRecNum', '1');
			IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', DesktopWeb._SCREEN_PARAM_MAP['rangeEnd']);

		} else {

			for (var i = 0; i < _searchValueFields.length; i++) {
				
				IFDS.Xml.addSingleNode(paramXML, _searchValueFields[i], _searchValue[_searchValueFields[i]]);
			}
			IFDS.Xml.addSingleNode(paramXML, 'startRecNum', (_nextRecNum['conPymtGrid']) ? _nextRecNum['conPymtGrid'] : '1');
			IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);
		}

		//conPymtGrid
		DesktopWeb.Ajax.doSmartviewAjax(_dtReload1, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML) {

			if (success) {
				loadXMLtoGrid(IFDS.Xml.getNode(responseXML, "//ConsolidatedPayments"), append, 'conPymtGrid');
				setReloadButton(responseXML);

				if (disableAll) {
					_resources.buttons['refreshBtn'].disable();
				}
			} else {
				disableScreen();
				if (!disableAll)
					_resources.buttons['refreshBtn'].enable();
			}
		}

	}
	
	function getPageNumber(responseXML, vEnd, vTotal) {
		var range_start = "1";
		var range_end = vEnd;
		var totalRecord = vTotal;

		if (range_end == null){
			range_end = IFDS.Xml.getNodeValue(responseXML, '//rangeEnd');
		}
		if (totalRecord == null){
			totalRecord = IFDS.Xml.getNodeValue(responseXML, '//totRecCnt');
		}
		
		page_display = range_start + " - " + range_end + " of " + totalRecord;

		return page_display;
	}

	function setReloadButton(responseXML) {
		_defaultValues['totRecCnt'] = IFDS.Xml.getNodeValue(responseXML, '//totRecCnt').toLowerCase() != '';
		_defaultValues['vrfAll'] = IFDS.Xml.getNodeValue(responseXML, '//vrfAll').toLowerCase() == 'yes';
		_defaultValues['appvAll'] = IFDS.Xml.getNodeValue(responseXML, '//appvAll').toLowerCase() == 'yes';
		_defaultValues['stpAll'] = IFDS.Xml.getNodeValue(responseXML, '//stpAll').toLowerCase() == 'yes';
		_defaultValues['ok'] = IFDS.Xml.getNodeValue(responseXML, '//oK').toLowerCase() == 'yes';
		
		var buttons = _resources.grids['conPymtGrid'].buttons;

		(_defaultValues['ok']) ? _resources.screenButtons[0].enable() : _resources.screenButtons[0].disable();
		(_defaultValues['totRecCnt']) ? buttons[0].show() : buttons[0].hide();
		(_defaultValues['vrfAll']) ? buttons[1].show() : buttons[1].hide();
		(_defaultValues['appvAll']) ? buttons[2].show() : buttons[2].hide();
		(_defaultValues['stpAll']) ? buttons[3].show() : buttons[3].hide();

		buttons[0].enable();
		buttons[1].enable();
		buttons[2].enable();
		buttons[3].enable();
		
		_conPymtPageNum = getPageNumber(responseXML, null, null);
		_verify = false;
		_approve = false;
		_stop = false;
		updateCheckbox();

		for (var fieldName in _resources.fields) {			
			_resources.fields[fieldName].disableField();
		}

		_resources.buttons['searchBtn'].disable();
		_resources.buttons['refreshBtn'].enable();
	}

	function loadXMLtoGrid(xml, append, gridName) {
		if (!!xml) {
			var index = _resources.grids[gridName].getSelectionModel().last;
			index = (index == 0) ? 0 : index;

			_resources.grids[gridName].getStore().loadData(xml, append);

			if (_resources.grids[gridName].getStore().getCount() > 0)
				_resources.grids[gridName].setSelectedRecord(index);
			
			updateActionButtons(gridName);
			updateMoreButton(xml, gridName);
		}
	} //loadXMLtoGrid

	function updateActionButtons(gridName) {

		if (gridName == 'conPymtGrid') {
			//modifyBtn
			//pymtAction
			_resources.grids[gridName].enableButton('historyBtn');

			if (_resources.grids[gridName].getSelectedRecord().data.statUpd == 'yes') {
				_resources.grids[gridName].enableButton('modifyBtn');
				_resources.grids[gridName].enableButton('resetBtn');
			} else {
				_resources.grids[gridName].disableButton('modifyBtn');
				_resources.grids[gridName].disableButton('resetBtn');
			}

		} else if (gridName == 'transGrid') {

			//_resources.grids[gridName].enableButton('pymtAction');
			if (!!_resources.grids['conPymtGrid'].getSelectedRecord()) {
				var paymentFor = _resources.grids['conPymtGrid'].getSelectedRecord().data.pymtFor;
				paymentFor = paymentFor.toLowerCase();
				//var childGrid = "";

				switch (paymentFor) {
				case 'id':
				case 'pw': {
						//childGrid = 'transGrid';
						if (!!DesktopWeb._SCREEN_PARAM_MAP['searchType'] && DesktopWeb._SCREEN_PARAM_MAP['searchType'].toLowerCase() == 'transnumber') {}
						else {

							var selectedRecord = _resources.grids['transGrid'].getSelectedRecord();
							if (!!selectedRecord) {
								_resources.grids['transGrid'].enableButton('detailsBtn');
							}
						}
						//_resources.grids['transGrid'].enableButton('detailsBtn');
						break;
					}				
				case 'co':
				case 'tf':
					//childGrid = 'paymentsGrid';
					break;
				}
			}

		}
	} //funcUpdateActionButtons


	function updateMoreButton(responseXML, gridName) {

		_nextRecNum[gridName] = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);

		if (_nextRecNum[gridName]) {
			_resources.grids[gridName].enableButton('moreBtn');
		} else
			_resources.grids[gridName].disableButton('moreBtn');
	} //function updateMoreButton

	function enableScreen() {
		_resources.grids['paymentsGrid'].reset();
		_resources.grids['transGrid'].reset();
		_resources.grids['conPymtGrid'].reset();
		clearInvalid();

		for (var fieldName in _resources.fields) {
		
			_resources.fields[fieldName].enableField();
		}
		_resources.buttons['searchBtn'].enable();
		_resources.buttons['refreshBtn'].disable();
		
		var conPymtGrid_buttons = _resources.grids['conPymtGrid'].buttons;
		conPymtGrid_buttons[0].hide();
		conPymtGrid_buttons[1].hide();
		conPymtGrid_buttons[2].hide();
		conPymtGrid_buttons[3].hide();
		
		var transGrid_buttons = _resources.grids['transGrid'].buttons;
		transGrid_buttons[0].hide();
		
		var paymentsGrid_buttons = _resources.grids['paymentsGrid'].buttons;
		paymentsGrid_buttons[0].hide();
		
		// reset value in label
		_conPymtPageNum = '';
		_transPageNum = '';
		
		_verify = false;
		_approve = false;
		_stop = false;
		_lastPymtId = 0;
		updateCheckbox();
	}
	
	function clickHandleRefreshBtn() {
		enableScreen();
		handleSearchChange();
	}
	
	function disableScreen() {

		_resources.grids['paymentsGrid'].reset();
		_resources.grids['transGrid'].reset();
		_resources.grids['conPymtGrid'].reset();
		clearInvalid();

		for (var fieldName in _resources.fields) {
			_resources.fields[fieldName].disableField();
		}

		_resources.buttons['searchBtn'].disable();
		_resources.buttons['refreshBtn'].disable();

		var buttons = _resources.grids['conPymtGrid'].buttons;
		buttons[1].hide();
		buttons[2].hide();
		buttons[3].hide();

		_verify = false;
		_approve = false;
		_stop = false;
		updateCheckbox();
	}

	function validateSearchCriteria() {

		var isValid = true;
		if (!_resources.fields['startDate'].disabled ) {
			
			isValid = _resources.fields['startDate'].isValid();
			
			if (isValid ) {
				isValid = _resources.fields['toDate'].isValid();
			}
			
			if (isValid) {
 				if (_resources.fields['startDate'].getValue() > _resources.fields['toDate'].getValue()) {
					isValid = false;
					_resources.fields['startDate'].markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
				} else 
					_resources.fields['startDate'].clearInvalid();
			}
		}
		return isValid;

	}

	function limitSearchFields() {
		
		var searchFor = _resources.fields['searchFor'].getValue().toLowerCase();
		var paymentType = _resources.fields['paymentType'].getValue().toLowerCase();
		
		if ( searchFor ==  "paymentfor") {
			
			switch (paymentType) {
				case 'e':
				case 'all':
					_resources.fields['paymentStatus'].enableField();
					_resources.fields['paymentStatus'].enable();
					break;
				default:
					_resources.fields['paymentStatus'].disableField();
					_resources.fields['paymentStatus'].disable();
			}
			
			var paymentFor = _resources.fields['paymentFor'].getValue().toLowerCase();
			switch (paymentFor) {
				case 'id':
				case 'pw': {
					_resources.fields['accountFld'].enableField();
					_resources.fields['accountFld'].enable();
					break;
				}
				default:
					_resources.fields['accountFld'].disableField();
					_resources.fields['accountFld'].disable();
			}
		}
		
	}
	function handlePaymentForChange() {
		limitSearchFields();
	}

	function handlePayTypeChange() {
		limitSearchFields();
	}

	function handleSearchChange() {
		//_field
		var tmpSearchFor = _resources.fields['searchFor'].getValue().toLowerCase();
		var disableList = [];
		var enableList = [];
		clearInvalid();
		switch (tmpSearchFor) {
		case "paymentfor":			
			disableList = ['accountFld'];
			enableList = ['paymentType', 'paymentStatus','startDate', 'toDate', 'brokerFld', 'branchFld', 'slsrepFld'];			
			_resources.fields['paymentFor'].show();
			_resources.fields['searchValue'].hide();
			
			
			break;

		case "paymentid":
		case "transnum":
			_resources.fields['paymentFor'].hide();
			_resources.fields['searchValue'].show();
			disableList = ['paymentType', 'paymentStatus', 'startDate', 'toDate','accountFld', 'brokerFld', 'branchFld', 'slsrepFld'];			
			break;
		case "paymentdate":
			_resources.fields['paymentFor'].show();
			_resources.fields['searchValue'].hide();

			disableList = ['paymentType', 'paymentStatus','accountFld', 'brokerFld', 'branchFld', 'slsrepFld'];
			enableList = ['startDate', 'toDate'];		
			break;

		case "payentity":
			_resources.fields['paymentFor'].show();
			_resources.fields['searchValue'].hide();
			disableList = ['paymentType', 'paymentStatus','accountFld'];
			enableList = ['startDate', 'toDate', 'brokerFld', 'branchFld', 'slsrepFld'];
			
			break;
		case "account":
			
			_resources.fields['paymentFor'].hide();
			_resources.fields['searchValue'].hide();
			disableList = ['paymentType', 'paymentStatus','brokerFld', 'branchFld', 'slsrepFld'];
			enableList = ['accountFld','startDate','toDate'];

			break;
		}
		
		
		for (var i = 0; i < disableList.length; i++){
			_resources.fields[disableList[i]].disableField();
			_resources.fields[disableList[i]].disable();
		}
		
		for (var i = 0; i < enableList.length; i++) {
			_resources.fields[enableList[i]].enableField();
			_resources.fields[enableList[i]].enable();
		}
		
		limitSearchFields();
	}

	function clearInvalid() {
		
		for (var i = 0; i < _fieldList.length; i++){			
			_resources.fields[_fieldList[i]].clearInvalid();
		}		
	}

	function disableAllSearch() {
		
		for (var i = 0; i < _fieldList.length; i++){			
			_resources.fields[_fieldList[i]].disableField();
		}
		_resources.buttons['searchBtn'].disable();

	}

	function getSearchValue() {
		//_field
		var tmpSearchFor = _resources.fields['searchFor'].getValue().toLowerCase();
		var tmpSearchForValue = _resources.fields['searchFor'].getValue();
		initLocalValues();
		switch (tmpSearchFor) {
		case "paymentfor":
			_searchValue['searchType'] = tmpSearchForValue;
			_searchValue['searchValue'] = _resources.fields['paymentFor'].getValue();
			_searchValue['pymtFor'] = _resources.fields['paymentFor'].getValue();

			_searchValue['payType'] = _resources.fields['paymentType'].getValue();
			_searchValue['pStatus'] = _resources.fields['paymentStatus'].getValue(); // DesktopWeb.Util.getDateDisplayValue
			_searchValue['fromDate'] = _resources.fields['startDate'].getSMVDateString();
			_searchValue['toDate'] = _resources.fields['toDate'].getSMVDateString();
			_searchValue['accountNum'] = _resources.fields['accountFld'].getValue();

			_searchValue['broker'] = _resources.fields['brokerFld'].getValue();
			_searchValue['branch'] = _resources.fields['branchFld'].getValue();
			_searchValue['slsRep'] = _resources.fields['slsrepFld'].getValue();
			
			_searchValue['broker'] = !!_searchValue['broker'] ? _searchValue['broker'] : 'all';
			_searchValue['branch'] = !!_searchValue['branch'] ? _searchValue['branch'] : 'all';
			_searchValue['slsRep'] = !!_searchValue['slsRep'] ? _searchValue['slsRep'] : 'all';
			break;

		case "paymentid":
			_searchValue['searchType'] = tmpSearchForValue;
			_searchValue['searchValue'] = _resources.fields['searchValue'].getValue();
			break;
		case "transnum":
			_searchValue['searchType'] = "TransNumber";
			_searchValue['searchValue'] = _resources.fields['searchValue'].getValue();
			break;
		case "paymentdate":
			_searchValue['searchType'] = tmpSearchForValue;
			_searchValue['searchValue'] = _resources.fields['paymentFor'].getValue();
			_searchValue['pymtFor'] = _resources.fields['paymentFor'].getValue();
			_searchValue['fromDate'] = _resources.fields['startDate'].getSMVDateString();
			_searchValue['toDate'] = _resources.fields['toDate'].getSMVDateString();

			break;

		case "payentity":
			_searchValue['searchType'] = tmpSearchForValue;
			_searchValue['searchValue'] = _resources.fields['paymentFor'].getValue();
			_searchValue['pymtFor'] = _resources.fields['paymentFor'].getValue();
			_searchValue['fromDate'] = _resources.fields['startDate'].getSMVDateString();
			_searchValue['toDate'] = _resources.fields['toDate'].getSMVDateString();

			_searchValue['broker'] = _resources.fields['brokerFld'].getValue();
			_searchValue['branch'] = _resources.fields['branchFld'].getValue();
			_searchValue['slsRep'] = _resources.fields['slsrepFld'].getValue();
			_searchValue['broker'] = !!_searchValue['broker'] ? _searchValue['broker'] : 'all';
			_searchValue['branch'] = !!_searchValue['branch'] ? _searchValue['branch'] : 'all';
			_searchValue['slsRep'] = !!_searchValue['slsRep'] ? _searchValue['slsRep'] : 'all';
			
			break;
		case "account":
			_searchValue['searchType'] = tmpSearchForValue;
			_searchValue['searchValue'] = _resources.fields['accountFld'].getValue();
			_searchValue['fromDate'] = _resources.fields['startDate'].getSMVDateString();
			_searchValue['toDate'] = _resources.fields['toDate'].getSMVDateString();

			break;

		}
	}

	function clickHandleSearchBtn() {
		if (validateSearchCriteria()) {
			initLocalValues();
			getSearchValue();

			doSearch(false);
		}
	}

	function selectConsolidatedPayment(record, append) {

		if (record.pymtId != _lastPymtId || append) {
			_lastPymtId = record.pymtId;

			var payFor = record.pymtFor.toLowerCase();

			switch (payFor) {
			case 'id':
			case 'pw': //pw
				gridName = 'transGrid';
				disableGrid = 'paymentsGrid';
				_resources.grids[disableGrid].reset();
				_resources.grids[gridName].show();
				_resources.grids[disableGrid].hide();
				_resources.layout.get('childLayout').setTitle(_translationMap['Transactions']);
				break;

			case 'co':
			case 'tf': //tf
				gridName = 'paymentsGrid';
				disableGrid = 'transGrid';
				_resources.grids[disableGrid].reset();
				_resources.grids[gridName].show();
				_resources.grids[disableGrid].hide();
				_resources.layout.get('childLayout').setTitle(_translationMap['Payments']);
				//Payments
				break;
			}

			var items = _resources.layout.items;
			var paramXML2 = IFDS.Xml.newDocument('data');
			var buttons = _resources.grids[gridName].buttons;
			var vColRangeEnd = null;
			//  second call to do normal process
			IFDS.Xml.addSingleNode(paramXML2, 'pymtId', _lastPymtId);
			IFDS.Xml.addSingleNode(paramXML2, 'paymentFor', record.pymtFor);
			if (!append) {
				_nextRecNum[gridName] = '1';
			} 
			
			IFDS.Xml.addSingleNode(paramXML2, 'startRecNum', _nextRecNum[gridName]);
			IFDS.Xml.addSingleNode(paramXML2, 'requestRecNum', _requestRecNum);

			//DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _smvDateFormat;
			DesktopWeb.Ajax.doSmartviewAjax(_dtReload2, {
				ignoreErrorCode : '15'
			}, paramXML2, responseHandler2, _translationMap['ProcMsg_Loading']);

			function responseHandler2(success, responseXML2) {
				if (success) {
					loadXMLtoGrid(IFDS.Xml.getNode(responseXML2, "//PayReconTxnPayList"), append, gridName);
					vColRangeEnd = IFDS.Xml.getNodeValue(responseXML2, '//rangeEnd');
					getTotalRecordNum(_lastPymtId, record.pymtFor, gridName, vColRangeEnd);
				} 
			}
			
			
		}
	}
	
	function getTotalRecordNum(vLastPymtId, vPymtFor, vGridName, vRangeEnd){
		var transGrid_buttons = null;
		var paramXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(paramXML, 'pymtId', vLastPymtId);
		IFDS.Xml.addSingleNode(paramXML, 'paymentFor', vPymtFor);
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtReload2, {
			ignoreErrorCode : '15'
		}, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML) {
			if (success) {
			
				transGrid_buttons = _resources.grids[vGridName].buttons;
				transGrid_buttons[0].setValue(getPageNumber(responseXML,vRangeEnd,null));
				transGrid_buttons[0].enable();
				transGrid_buttons[0].show();

			} 
		}
	}

	function clickHandleDetailsBtn() {
		//transGrid
		var selectedRecord = _resources.grids['transGrid'].getSelectedRecord();
		if (!!selectedRecord) {
			document.getElementById('btnTransactionDetails').click();
			//document.getElementById('btnAcctDetail').click();
		}
	}

	function getTransNum() {
		var selectedRecord = _resources.grids['transGrid'].getSelectedRecord();
		return selectedRecord.data.transNum;
	}

	function getFundCode() {
		var selectedRecord = _resources.grids['transGrid'].getSelectedRecord();

		return selectedRecord.data.fund;
	}

	function getClassCode() {
		var selectedRecord = _resources.grids['transGrid'].getSelectedRecord();
		return selectedRecord.data['class'];
	}

	function getTransId() {
		var selectedRecord = _resources.grids['transGrid'].getSelectedRecord();

		return selectedRecord.data.transID;
	}

	function getAccountNum() {
		var selectedRecord = _resources.grids['transGrid'].getSelectedRecord();

		return selectedRecord.data.acct;
	}

	function clickResetBtn() {
		var rec = _resources.grids['conPymtGrid'].getSelectedRecord();
		if (!!rec && rec.data.pymtStat !== _resources.fields['paymentStatus'].getValueDesc()) {
			rec.data.runMode = '';
			rec.data.newStatus = _resources.fields['paymentStatus'].getValue();
			rec.data.pymtStat = _resources.fields['paymentStatus'].getValueDesc();
			rec.commit();

		}
	}
	/*clickResetBtn*/

	function clickHandleHistoricalBtn() {
		var viewParam = {};
		var historyName = null;
		var tempRecord = _resources.grids['conPymtGrid'].getSelectedRecord();

		if (tempRecord != undefined && tempRecord != null) {
			viewParam['auditType'] = 'PayRecon';
			viewParam['auditRecId'] = tempRecord.data['recId'];
			historyName = _translationMap['HistoricalPayment'];

			_resources.popups['history'].init(historyName, _historyService, viewParam, true);
			_resources.popups['history'].show();
		}
	} //funcHistoryPopup

	function openModifyPopup() {
		_resources.popups['consPymtPoup'].show();
		_resources.popups['consPymtPoup'].init(_resources.grids['conPymtGrid'].getSelectedRecord());
	}

	function getUpdatedRecordCount() {
		var store = _resources.grids['conPymtGrid'].getStore();
		var modRecords = store.query('runMode', _self.MOD);
		var buttons = _resources.grids['conPymtGrid'].buttons;

		return modRecords.length > 0 || _verify || _approve || _stop;
	} //function getUpdatedRecordCount

	function savePopup(data) {
		_resources.grids['conPymtGrid'].updateSelectedRecord(data);
		this.updatesFlag = (getUpdatedRecordCount() > 0);
	}

	function buildUpdateXML() {
		var updateXML = IFDS.Xml.newDocument('data');
		var store = _resources.grids['conPymtGrid'].getStore();

		IFDS.Xml.addSingleNode(updateXML, 'searchType', _searchValue['searchType']);
		IFDS.Xml.addSingleNode(updateXML, 'paymentFor', _searchValue['searchValue']);

		IFDS.Xml.addSingleNode(updateXML, 'broker', _searchValue['broker'] );
		IFDS.Xml.addSingleNode(updateXML, 'branch', _searchValue['branch'] );
		IFDS.Xml.addSingleNode(updateXML, 'slsRep', _searchValue['slsRep'] );

		IFDS.Xml.addSingleNode(updateXML, 'payType', _searchValue['payType']);
		IFDS.Xml.addSingleNode(updateXML, 'searchStatus', _searchValue['pStatus']);
		IFDS.Xml.addSingleNode(updateXML, 'accountNum', _searchValue['accountNum']);
		IFDS.Xml.addSingleNode(updateXML, 'fromDate', _searchValue['fromDate']);
		IFDS.Xml.addSingleNode(updateXML, 'toDate', _searchValue['toDate']);
		var buttons = _resources.grids['conPymtGrid'].buttons;
		IFDS.Xml.addSingleNode(updateXML, 'verifyAll', _verify ? 'yes' : 'no');
		IFDS.Xml.addSingleNode(updateXML, 'approveAll', _approve ? 'yes' : 'no');
		IFDS.Xml.addSingleNode(updateXML, 'stopAll', _stop ? 'yes' : 'no');

		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToXML);

		return updateXML;

		function addToXML(item) {
			var expectedStatus = _resources.fields['paymentStatus'].getValueDesc();
			if (_verify)
				expectedStatus += " Verified";
			else if (_approve)
				expectedStatus = "Approved";
			else if (_stop)
				expectedStatus = "Stopped";

			if (expectedStatus != item.data['pymtStat']) {
				var recordXML = IFDS.Xml.addSingleNode(updateXML, 'PaymentUpdate');
				IFDS.Xml.addSingleNode(recordXML, 'vrecid', item.data['recId']);
				IFDS.Xml.addSingleNode(recordXML, 'version', item.data['version']);
				IFDS.Xml.addSingleNode(recordXML, 'newStatus', item.data['newStatus']);
			}
		} //addToXML
	}

	function doUpdate() {
		var updateStatus = null;

		DesktopWeb.Ajax.doSmartviewUpdate(_dtUpd, null, buildUpdateXML(), responseHandler, null);
		function responseHandler(success, responseXML, contextErrors) {
			if (success) {
				updateStatus = DesktopWeb._SUCCESS;
			} else {
				//storeContextErrors(contextErrors);
				updateStatus = DesktopWeb._FAIL
			}
		}
		return updateStatus;
	} //doUpdate

	function clickOK() {
		this.updatesFlag = (getUpdatedRecordCount() > 0);
		var message = '';
		if (this.updatesFlag) {
			if (_verify) {
				message = _translationMap['VerifyMsg']
					 + _resources.fields['paymentStatus'].getValueDesc()
					 + _translationMap['NextMsg'];
				DesktopWeb.Util.displayYesNo(message, handlePromptMsg)

			} //handlePromptMsg
			else if (_approve) {
				message = _translationMap['ApproveMsg']
					 + _resources.fields['paymentStatus'].getValueDesc()
					 + _translationMap['NextMsg'];
				DesktopWeb.Util.displayYesNo(message, handlePromptMsg)

			} else if (_stop) {
				message = _translationMap['StopMsg']
					 + _resources.fields['paymentStatus'].getValueDesc()
					 + _translationMap['NextMsg'];
				DesktopWeb.Util.displayYesNo(message, handlePromptMsg)
			} else
				DesktopWeb.Util.commitScreen();

			function handlePromptMsg(btn) {
				if (btn == 'yes') {
					DesktopWeb.Util.commitScreen();
				}
			}

		} else
			DesktopWeb.Util.cancelScreen();
	}

	function clickHandleMoreBtn(gridName) {
		if (gridName == 'conPymtGrid')
			doSearch(true);
		else {
			selectConsolidatedPayment(_resources.grids['conPymtGrid'].getSelectedRecord().data, true)
		}
	}

	function updateGridStatus(newCode, newStatusDesc) {
		var searchStatus = _massStatus;

		if (searchStatus == null || searchStatus == '') {
			searchStatus = _resources.fields['paymentStatus'].getValueDesc();
		}

		_resources.grids['conPymtGrid'].getStore().each(function (rec) {
			if (searchStatus == rec.data.pymtStat) {

				var nodeArray = null;
				if (!!rec.data.ListXML) {
					nodeArray = IFDS.Xml.getNodes(IFDS.Xml.stringToXML(rec.data.ListXML), "//Element");

				
					for (var i = 0; i < nodeArray.length; i++) {
						var code = IFDS.Xml.getNodeValue(nodeArray[i], "code");
						var desc = IFDS.Xml.getNodeValue(nodeArray[i], "value");

						if (desc == newStatusDesc) {

							rec.data.runMode = _MOD;
							rec.data.newStatus = code;
							rec.data.pymtStat = desc;
							rec.commit();
							break;
						}
					}
				}
			}
		});
	}
	function checkedStopAll(checked) {
		if (checked) {
			_verify = false;
			_approve = false;
			_stop = true;
			updateCheckbox();
			updateGridStatus('', 'Stopped');
			_massStatus = 'Stopped';

		} else {
			updateGridStatus(_resources.fields['paymentStatus'].getValue(), _resources.fields['paymentStatus'].getValueDesc());
			_massStatus = null;
			_stop = false;
		}
	}

	function checkedApproveAll(checked) {
		if (checked) {
			_verify = false;
			_approve = true;
			_stop = false;
			updateCheckbox();
			updateGridStatus('', 'Approved');
			_massStatus = 'Approved';
		} else {
			updateGridStatus(_resources.fields['paymentStatus'].getValue(), _resources.fields['paymentStatus'].getValueDesc());
			_massStatus = null;
			_approve = false;
		}

	}

	function checkedVerifyAll(checked) {
		if (checked) {
			_verify = true;
			_approve = false;
			_stop = false;
			updateCheckbox();
			updateGridStatus('', _resources.fields['paymentStatus'].getValueDesc() + ' Verified');
			_massStatus = _resources.fields['paymentStatus'].getValueDesc() + ' Verified';
		} else {
			updateGridStatus(_resources.fields['paymentStatus'].getValue(), _resources.fields['paymentStatus'].getValueDesc());
			_massStatus = null;
			_verify = false;
		}
	}

	function updateCheckbox() {
		var buttons = _resources.grids['conPymtGrid'].buttons;
		buttons[0].setValue(_conPymtPageNum);
		buttons[1].setValue(_verify);
		buttons[2].setValue(_approve);
		buttons[3].setValue(_stop);

	}

	// PUBLIC ITEMS *************************************
	return {
		getAccountNum : getAccountNum,
		getTransId : getTransId,
		getFundCode : getFundCode,
		getClassCode : getClassCode,
		getTransNum : getTransNum,
		savePopup : savePopup,
		doUpdate : doUpdate,
		MOD : _MOD,
		updatesFlag : false,
		init : init,
		handleSearchChange : handleSearchChange,
		handlePaymentForChange : handlePaymentForChange,
		handlePayTypeChange : handlePayTypeChange,
		clickOK : clickOK,
		clickHandleSearchBtn : clickHandleSearchBtn,
		clickHandleRefreshBtn : clickHandleRefreshBtn,
		clickHandleHistoricalBtn : clickHandleHistoricalBtn,
		clickHandleMoreBtn : clickHandleMoreBtn,
		openModifyPopup : openModifyPopup,
		clickResetBtn : clickResetBtn,
		selectConsolidatedPayment : selectConsolidatedPayment,
		updateActionButtons : updateActionButtons,
		checkedStopAll : checkedStopAll,
		checkedApproveAll : checkedApproveAll,
		checkedVerifyAll : checkedVerifyAll,

		clickHandleDetailsBtn : clickHandleDetailsBtn
	}
}