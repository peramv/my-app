/*********************************************************************************************
 * @file    RegAgreement.Controller.js
 * @author  Hatthaseriphong, Nopphawan
 * @desc    Controller JS file of the Regulatory Agreement Maintenance
 *********************************************************************************************/
/*
 * Procedure: RegAgreement.Controller.js
 *
 * Purpose  : Controller for Regulatory Agreement Maintenance screen
 *
 * Notes    : - Regulatory Agreement Maintenance
 *            - Open screen from 
 *              Menu -> Broker Level Maintenance -> Regulatory Agreement Maintenance
 *
 * History  :
 *
 *    08 Feb 2017 N. Hatthaseriphong P0262306 CHG0048101 T85011 Regulatory Agreement Maintenance
 *        - Created
 *        
 *    29 Mar 2017 N. Hatthaseriphong P0262306 CHG0048101 T85188 Regulatory Agreement Maintenance
 *                DFT0073739 DFT0073746
 *        - Changed 'Pay Type' to 'Party Type'
 *        - Fixed selectRegulationAgreement 
 *
 *    27 Feb 2017 Gomoot T. P0262306 CHG0048101 T85392 DFT0074488
 *        - Add logic to validate Effective date and stopdate
 *
 *    08 May 2017 Gomoot T. P0262306 CHG0048101 T85425 DFT0074520
 *        - Add logic to send all details when user modify data
 *       
 *    19 Feb 2018 Matira T. P0268206-128 DFT0078815 DFT0080777
 *    		- Add Classification field in add/modify regulation popup
 *    		- Add Historical of Responsibility
 */

DesktopWeb.ScreenController = function() {
  var _translationMap = DesktopWeb.Translation.getTranslationMap();

  var _self = null;
  var _resources = null;
  var _nextStartRecNum = null;
  var _requestRecNum = 25; //The number of record display on table
  var _uuidRunning = 0;
  
  //service
  var _brokerSearch = 'brokerSearch';
  var _intrSearch = 'intrSearch';
  var _dtHistoricalInfo = 'dtHistoricalInfo';
  var _dtRegAgrmtInq = 'dtRegAgrmtInq';
  var _dtRegAgrmtProc = 'dtRegAgrmtProc';

  var _SCREENMODE_UPD = 'upd';
  
  var _INQPERM = 'inqPerm'
  var _ADDPERM = 'addPerm';
  var _MODPERM = 'modPerm';
  var _DELPERM = 'delPerm';

  var _RUNMODE_INIT = 'init';
  var _RUNMODE_RELOAD = 'reload';
  var _RUNMODE_ADD = 'add';
  var _RUNMODE_MOD = 'mod';
  var _RUNMODE_DEL = 'del';

  var _ADDBTN = 'addBtn';
  var _MODBTN = 'modBtn';
  var _DELBTN = 'delBtn';
  var _MOREBTN = 'moreBtn';
  var _ADMINBTN = 'adminBtn';
  var _HISBTN = 'historicalBtn';

  var _PARTY_TYPE_ALL = 'All';
  var _PARTY_TYPE_BROK = 'BK';
  var _PARTY_TYPE_INTR = 'IN';
  
  var _DEFAULT_START_DATE = null;
  var _DEFAULT_STOP_DATE = null;
  
  // pop up
  var _regGrid = null;
  var _resGrid = null;
  var _regPop = null;
  var _resPop = null;
  
  var _permissionsMap = {};
  var _defaultValues = {};
  var _searchForCodeList = {};
  var _partyTypeCodeList = {};
  var _regPopFldList = {};
  var _resPopFldList = {};
  
  var _initXML = null;

  /****** Initialize screen ******/
  function initResourceName() {
    _searchForCodeList[_PARTY_TYPE_ALL] = 'searchForAll';
    _searchForCodeList[_PARTY_TYPE_BROK] = 'searchForBroker';
    _searchForCodeList[_PARTY_TYPE_INTR] = 'searchForIntermediary';

    _partyTypeCodeList['pPartyCodeFld'] = 'pPartyCodeFld';
    _partyTypeCodeList[_PARTY_TYPE_BROK] = 'pBrokerFld';
    _partyTypeCodeList[_PARTY_TYPE_INTR] = 'pIntermediaryFld';

    _regGrid = _resources.grids['regulationGrid'];
    _resGrid = _resources.grids['responsibilityGrid'];
    _regPop = _resources.popups['regulationPopup'];
    _resPop = _resources.popups['responsibilityPopup'];

    _regPopFldList['regulation'] = 'pRegulationFld';
    _regPopFldList['partyType'] = 'pPartyTypeFld';
    _regPopFldList['broker'] = 'pBrokerFld';
    _regPopFldList['intermediary'] = 'pIntermediaryFld';
    _regPopFldList['partyCode'] = 'pPartyCodeFld';
    _regPopFldList['status'] = 'pStatusFld';
    _regPopFldList['startDate'] = 'pStartDateFld';
    _regPopFldList['stopDate'] = 'pStopDateFld';
    _regPopFldList['receiveDate'] = 'pReceiveDateFld';
    _regPopFldList['classification'] = 'pClassificationFld';
  }

  /****** Store user permission ******/
  function storePermissions(initViewXML) {
    _permissionsMap[_INQPERM] = IFDS.Xml.getNodeValue(initViewXML,
        '//Permissions/inqPerm').toLowerCase() == _self.YES;
    _permissionsMap[_ADDPERM] = IFDS.Xml.getNodeValue(initViewXML,
        '//Permissions/addPerm').toLowerCase() == _self.YES;
    _permissionsMap[_MODPERM] = IFDS.Xml.getNodeValue(initViewXML,
        '//Permissions/modPerm').toLowerCase() == _self.YES;
    _permissionsMap[_DELPERM] = IFDS.Xml.getNodeValue(initViewXML,
        '//Permissions/delPerm').toLowerCase() == _self.YES;
  }
  
  /** Load All Dropdown Lists **/
  function populateDropdownList(responseXML) {
    var regulationListNode = IFDS.Xml.getNode(responseXML,
        "//List[@listName='RegulationList']");
    var searchForListNode = IFDS.Xml.getNode(responseXML,
        "//List[@listName='SearchForList']");
    var partyTypeListNode = IFDS.Xml.getNode(responseXML,
        "//List[@listName='PartyTypeList']");
    var statusListNode = IFDS.Xml.getNode(responseXML,
        "//List[@listName='StatusList']");
    var acctAbilityFATCAListNode = IFDS.Xml.getNode(responseXML,
        "//List[@listName='AcctAbilityFATCAList']");
    var acctDesignListNode = IFDS.Xml.getNode(responseXML,
        "//List[@listName='AcctDesignList']");
    var acctPartyListNode = IFDS.Xml.getNode(responseXML,
        "//List[@listName='AcctPartyList']");
    var ffiListNode = IFDS.Xml.getNode(responseXML,
    	"//List[@listName='FFIList']");

    // main screen
    _resources.fields['regulationSrch'].loadData(regulationListNode);
    _resources.fields['searchForSrch'].loadData(searchForListNode);

    // regulation popup
    _regPop.getField('pRegulationFld').loadData(regulationListNode);
    _regPop.getField('pPartyTypeFld').loadData(partyTypeListNode);
    _regPop.getField('pStatusFld').loadData(statusListNode);
    _regPop.getField('pClassificationFld').loadData(ffiListNode);

    // responsibility popup
    _resPop.getField('pResponsibilityFld').loadData(acctAbilityFATCAListNode);
    _resPop.getField('pAccountDesignationFld').loadData(acctDesignListNode);
    _resPop.getField('pAccountablePartyFld').loadData(acctPartyListNode);
  }

  function populateRegulationPopup() {
    _regPop.getField('pStartDateFld').setValue(
        DesktopWeb.Util.getDateDisplayValue(_DEFAULT_START_DATE));
    _regPop.getField('pStopDateFld').setValue(
        DesktopWeb.Util.getDateDisplayValue(_DEFAULT_STOP_DATE));
  }
  
  function loadDefaultValues(initViewXML) {
    var defaultValuesNode = IFDS.Xml.getNode(initViewXML,
        "//DefaultValues");

    var regulation = IFDS.Xml.getNodeValue(initViewXML,
        "//List[@listName='RegulationList']/Element/code");
    var searchFor = IFDS.Xml.getNodeValue(initViewXML,
        "/*//ListSelection[@id = 'SearchForList']");
    
    _DEFAULT_START_DATE = IFDS.Xml.getNodeValue(defaultValuesNode, 'startDate');
    _DEFAULT_STOP_DATE = IFDS.Xml.getNodeValue(defaultValuesNode, 'stopDate');
    
    // main screen
    _resources.fields['regulationSrch'].setValue(regulation);
    _resources.fields['searchForSrch'].setValue(searchFor);
    _self.setSuggestService(searchFor, 'mainScreen');
  }

  function doSearch(getMore) {
    var dataXML = IFDS.Xml.newDocument('data');
    var searchValue = '';

    IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_RELOAD);
    IFDS.Xml.addSingleNode(dataXML, 'startRecNum', getMore ? _nextStartRecNum
        : 1);
    IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);

    IFDS.Xml.addSingleNode(dataXML, 'regulationType',
        _resources.fields['regulationSrch'].getValue());
    IFDS.Xml.addSingleNode(dataXML, 'searchType',
        _resources.fields['searchForSrch'].getValue());

    // get search value
    if (_resources.fields['searchForAll'].getValue() != '')
      searchValue = _resources.fields['searchForAll'].getValue();
    else if (_resources.fields['searchForBroker'].getValue() != '')
      searchValue = _resources.fields['searchForBroker'].getValue();
    else if (_resources.fields['searchForIntermediary'].getValue() != '')
      searchValue = _resources.fields['searchForIntermediary'].getValue();

    IFDS.Xml.addSingleNode(dataXML, 'searchValue', searchValue);

    DesktopWeb.Ajax.doSmartviewAjax(_dtRegAgrmtInq, null, dataXML,
        responseHandler, _translationMap['ProcMsg_Searching']);

    function responseHandler(success, responseXML) { 
      if (success) {
        _regGrid.getStore().loadData(
            IFDS.Xml.getNode(responseXML, "//RegAgrmtList"), getMore);
        if (getMore)
          _regGrid.selectLastRecord();
        enableScreen();
        _nextStartRecNum = DesktopWeb.Ajax
            .getSmartviewNextStartRecNum(responseXML);

        if (_nextStartRecNum)
          _regGrid.enableButton(_MOREBTN);
        else
          _regGrid.disableButton(_MOREBTN);

      } else {
        _regGrid.clearData();
        _resGrid.clearData();

        if (_permissionsMap[_ADDPERM])
          _regGrid.enableButton(_ADDBTN);
      }
    }
  }

  function doSave(action, popupName) {
    var regRecord = _regGrid.getSelectedRecord();
    var resRecord = _resGrid.getSelectedRecord();
    
    var regAgrmtData = {};
    var regAgrmtDetlData = {};
    var storeRegAgrmtDetl = null;
    var runMode = action;
    var regAgrmtUUID = "";
    var regulationCode = "";
    var partyType = "";
    var partyCode = "";
    var startDate = "";
    var stopDate = "";
    var recvDate = "";
    var stat = "";
    var version = "";
    var classification = "";
    
    // add mode
    if (action == _RUNMODE_ADD) {
      regAgrmtUUID = ++_uuidRunning;
      regulationCode = _regPop.getField('pRegulationFld').getValue();
      partyType = _regPop.getField('pPartyTypeFld').getValue();
      classification = _regPop.getField('pClassificationFld').getCode();
      
      if (partyType == _PARTY_TYPE_BROK)
        partyCode = _regPop.getField('pBrokerFld').getValue();
      else if (partyType == _PARTY_TYPE_INTR)
        partyCode = _regPop.getField('pIntermediaryFld').getValue();

      startDate = DesktopWeb.Util.getSMVDateValue(_regPop.getField(
          'pStartDateFld').getDisplayDateString());
      stopDate = DesktopWeb.Util.getSMVDateValue(_regPop.getField(
          'pStopDateFld').getDisplayDateString());
      recvDate = DesktopWeb.Util.getSMVDateValue(_regPop.getField(
          'pReceiveDateFld').getDisplayDateString());
      stat = _regPop.getField('pStatusFld').getValue();
      version = 0;

    // modify mode
    } else if (action == _RUNMODE_MOD) {
      regAgrmtUUID = regRecord.data['regAgrmtUUID'];
      version = regRecord.data['version'];
      
      if (popupName == 'regulationPopup') { // modify on regulation
        regulationCode = _regPop.getField('pRegulationFld').getValue();
        partyType = _regPop.getField('pPartyTypeFld').getValue();
        partyCode = _regPop.getField('pPartyCodeFld').getValue();
        classification = _regPop.getField('pClassificationFld').getCode();
        
        startDate = DesktopWeb.Util.getSMVDateValue(_regPop.getField(
            'pStartDateFld').getDisplayDateString());
        stopDate = DesktopWeb.Util.getSMVDateValue(_regPop.getField(
            'pStopDateFld').getDisplayDateString());
        recvDate = DesktopWeb.Util.getSMVDateValue(_regPop.getField(
            'pReceiveDateFld').getDisplayDateString());
        stat = _regPop.getField('pStatusFld').getValue();
        
        storeRegAgrmtDetl = _resGrid.getStore();      
        
      } else if (popupName == 'responsibilityPopup') { // modify on responsibility
        runMode = "";
        // responsibility only (detail)
        regAgrmtDetlData['runMode'] = action;
        regAgrmtDetlData['regAgrmtUUID'] = resRecord.data['regAgrmtUUID'];
        regAgrmtDetlData['regAgrmtDetlUUID'] = resRecord.data['regAgrmtDetlUUID'];
        regAgrmtDetlData['acctAbility'] = _resPop.getField('pResponsibilityFld').getValue();
        regAgrmtDetlData['acctDes'] = _resPop.getField('pAccountDesignationFld').getValue();
        regAgrmtDetlData['acctParty'] = _resPop.getField('pAccountablePartyFld').getValue();
        regAgrmtDetlData['version'] = resRecord.data['version'];
      }
    
    // delete mode  
    } else if (action == _RUNMODE_DEL) {
      regAgrmtUUID = regRecord.data['regAgrmtUUID'];
      version = regRecord.data['version'];
    }
    
    // set regulation data
    regAgrmtData['runMode'] = runMode;
    regAgrmtData['regAgrmtUUID'] = regAgrmtUUID;
    regAgrmtData['regulationCode'] = regulationCode;
    regAgrmtData['partyType'] = partyType;
    regAgrmtData['partyCode'] = partyCode;
    regAgrmtData['classification'] = classification;
    regAgrmtData['startDate'] = startDate;
    regAgrmtData['stopDate'] = stopDate;
    regAgrmtData['recvDate'] = recvDate;
    regAgrmtData['stat'] = stat;
    regAgrmtData['version'] = version;

    // create request xml
    var dataXML = IFDS.Xml.newDocument('data');

    IFDS.Xml.addSingleNode(dataXML, 'screenMode', _SCREENMODE_UPD);

    var regAgrmtListXML = IFDS.Xml.addSingleNode(dataXML, 'regAgrmtList');
    var regAgrmtXML = IFDS.Xml.addSingleNode(regAgrmtListXML, 'regAgrmt');

    // create tag for RegulatoryAgrmt
    for (var tag in regAgrmtData) {
      IFDS.Xml.addSingleNode(regAgrmtXML, tag, regAgrmtData[tag]);
    }

    var regAgrmtDetlsXML = IFDS.Xml.addSingleNode(regAgrmtXML, 'regAgrmtDetls');
    var regAgrmtDetlXML = null;

    // create tag for RegulatoryAgrmtDetl
    if (!!regAgrmtDetlData) {
      regAgrmtDetlXML = IFDS.Xml.addSingleNode(regAgrmtDetlsXML,
        'regAgrmtDetl');
      for (var tag in regAgrmtDetlData) {
        IFDS.Xml.addSingleNode(regAgrmtDetlXML, tag, regAgrmtDetlData[tag]);
      }
    }
    
    if (!!storeRegAgrmtDetl) 
    {
        storeRegAgrmtDetl.each(function(record)       
        {         
          regAgrmtDetlXML  = IFDS.Xml.addSingleNode(regAgrmtDetlsXML,'regAgrmtDetl');
          IFDS.Xml.addSingleNode(regAgrmtDetlXML, 'runMode', _self.RUNMODE_MOD);
          IFDS.Xml.addSingleNode(regAgrmtDetlXML, 'regAgrmtUUID', record.data['regAgrmtUUID']);
          IFDS.Xml.addSingleNode(regAgrmtDetlXML, 'regAgrmtDetlUUID', record.data['regAgrmtDetlUUID']);
          IFDS.Xml.addSingleNode(regAgrmtDetlXML, 'acctAbility', record.data['acctAbility']);
          IFDS.Xml.addSingleNode(regAgrmtDetlXML, 'acctDes', record.data['acctDes']);
          IFDS.Xml.addSingleNode(regAgrmtDetlXML, 'acctParty', record.data['acctParty']);
          IFDS.Xml.addSingleNode(regAgrmtDetlXML, 'version', record.data['version']);       
       });
    }
 
    
    DesktopWeb.Ajax.doSmartviewUpdate(_dtRegAgrmtProc, null, dataXML,
        responseHandler, _translationMap['ProcMsg_Processing']);

    function responseHandler(success, responseXML) {
      if (success) {
        if (IFDS.Xml.getNode(responseXML, "//RegAgrmtList") != null) {
          switch (action) {
          case _RUNMODE_ADD: // add successfully
            _regGrid.getStore().loadData(IFDS.Xml.getNode(responseXML, "//RegAgrmtList"), true);
            _regGrid.selectLastRecord();
            _resources.popups[popupName].hide();
            enableScreen();
            break;
          case _RUNMODE_MOD: // modify successfully
//            doSearch(false);
            var regAgrmtNode = IFDS.Xml.getNode(responseXML,
                "//RegAgrmtList/RegAgrmt");
            if (regAgrmtNode)
              setUpdatedDataToGrid(regAgrmtNode, regRecord);
            _resources.popups[popupName].hide();
            break;
          case _RUNMODE_DEL: // delete successfully
//            _regGrid.removeSelectedRecord();
            _resGrid.clearData();
            regRecord.data['runMode'] = _RUNMODE_DEL;
            var rowIndex = _regGrid.getRecordIndex(regRecord);
            (rowIndex == 0) ? rowIndex++ : rowIndex--;
            _regGrid.store.filterBy(function(record) {
              return record.data.runMode != _RUNMODE_DEL;
            });
            _regGrid.setSelectedRecord(rowIndex);
            break;
          }
        }
      }
    }
    
  }

  function setUpdatedDataToGrid(node, selectedRecord) {
    var value = "";
    for (var field in selectedRecord.data) {
      value = IFDS.Xml.getNodeValue(node, field);
      if (field.match(/date/i) != null)
        value = DesktopWeb.Util.getDateDisplayValue(value);
      else if (field == 'RegAgrmtDetlsXML') {
        var node = IFDS.Xml.getNode(node, "/*//RegAgrmt[regAgrmtUUID='"
            + selectedRecord.data.regAgrmtUUID + "']/RegAgrmtDetls");
        value = (node != null) ? IFDS.Xml.serialize(node) : _self.BLANK;
      }else if(field == 'classification'){
    	  value = IFDS.Xml.getNodeValue(node, '//' + field);
      }
      
      // set data to grid
      selectedRecord.data[field] = value;
    }
    selectedRecord.commit();
    _self.selectRegulationAgreement(selectedRecord, _resGrid
        .getRecordIndex(_resGrid.getSelectedRecord()));   
  }

  function enableScreen() {
    if (_permissionsMap[_ADDPERM])
      _regGrid.enableButton(_ADDBTN);

    if (_permissionsMap[_MODPERM])
      _regGrid.enableButton(_MODBTN);

    if (_permissionsMap[_DELPERM])
      _regGrid.enableButton(_DELBTN);

    _regGrid.enableButton(_ADMINBTN);
    _regGrid.enableButton(_HISBTN);
    _resGrid.enableButton(_HISBTN);
  }

  function disableScreen() {
    _resources.buttons['searchBtn'].disable();
    _regGrid.disableButton(_ADDBTN);
    _regGrid.disableButton(_MODBTN);
    _regGrid.disableButton(_DELBTN);
    _regGrid.disableButton(_MOREBTN);
    _regGrid.disableButton(_ADMINBTN);
    _regGrid.disableButton(_HISBTN);
    _resGrid.disableButton(_HISBTN);
    _resGrid.disableButton(_MODBTN);
  }

  function initialButton() {
    if (_permissionsMap[_INQPERM])
      _resources.buttons['searchBtn'].enable();
    if (_permissionsMap[_ADDPERM])
      _regGrid.enableButton(_ADDBTN);
  }

  return {
    searchForCodeList: _searchForCodeList,
    partyTypeCodeList: _partyTypeCodeList,
    RUNMODE_ADD: _RUNMODE_ADD,
    RUNMODE_MOD: _RUNMODE_MOD,
    RUNMODE_DEL: _RUNMODE_DEL,
    BLANK: '',
    YES: 'yes',
    NO: 'no',
    
    init: function(res) {
      _resources = res;
      _self = DesktopWeb._SCREEN_CONTROLLER;

      /** TODO INIT **/
      initResourceName();

      var dataXML = IFDS.Xml.newDocument('data');
      IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);

      DesktopWeb.Ajax.doSmartviewAjax(_dtRegAgrmtInq, null, dataXML,
          responseHandler, _translationMap['ProcMsg_Searching']);

      function responseHandler(success, responseXML) {
        disableScreen();
        if (success) {
          _initXML = IFDS.Xml.cloneDocument(responseXML);
          storePermissions(_initXML);
          populateDropdownList(_initXML);
          loadDefaultValues(_initXML);
          initialButton();
        }
      }
    }
    ,
    openRegPopupAdd: function(action) {
      _self.resetPartyTypeCodeList();

      for ( var name in _regPopFldList) {
        _regPop.getField(_regPopFldList[name]).reset();

        if (_regPop.rendered)
          _regPop.getField(_regPopFldList[name]).setValue('');

        _regPop.getField(_regPopFldList[name]).clearInvalid();
        _regPop.getField(_regPopFldList[name]).enable();
      }

      _regPop.getField('pPartyCodeFld').show();
      _regPop.getField('pPartyCodeFld').disable();

      populateRegulationPopup();

      _regPop.init(action);
      _regPop.show();
    }
    ,
    openRegPopupMod: function(action) {
      var record = _regGrid.getSelectedRecord();

      _self.resetPartyTypeCodeList();

      _regPop.getField('pRegulationFld')
          .setValue(record.data['regulationCode']);
      _regPop.getField('pPartyTypeFld').setValue(record.data['partyType']);

      var partyTypeCode = _regPop.getField('pPartyTypeFld').getValue();

      _regPop.getField(_self.partyTypeCodeList[partyTypeCode]).show();
      _regPop.getField(_self.partyTypeCodeList[partyTypeCode]).disable();
      _regPop.getField(_self.partyTypeCodeList[partyTypeCode]).setValue(
          record.data['partyCodeName']);
      _regPop.getField('pPartyCodeFld').setValue(record.data['partyCode']);
      _regPop.getField('pClassificationFld').setValue(record.data['classification']);
      
      _regPop.getField('pStatusFld').setValue(record.data['status']);
      _regPop.getField('pStartDateFld').setValue(record.data['startDate']);
      _regPop.getField('pStopDateFld').setValue(record.data['stopDate']);
      _regPop.getField('pReceiveDateFld').setValue(record.data['recvDate']);

      _regPop.getField('pRegulationFld').disable();
      _regPop.getField('pPartyTypeFld').disable();

      _regPop.init(action);
      _regPop.show();
    }
    ,
    openResPopupMod: function(mode) {
      var record = _resGrid.getSelectedRecord();
      
      _resPop.getField('pResponsibilityFld').setValue(
          record.data['acctAbility']);
      _resPop.getField('pAccountDesignationFld').setValue(
          record.data['acctDes']);
      _resPop.getField('pAccountablePartyFld').setValue(
          record.data['acctParty']);

      _resPop.getField('pResponsibilityFld').disable();
      _resPop.getField('pAccountDesignationFld').disable();

      _resPop.init(mode);
      _resPop.show();
    }
    ,
    openAdminPopup: function() {
      var title = null;
      var xml = null;

      title = _translationMap["RegAgmtMt"] + ' - ' + _translationMap['Admin'];
      xml = _regGrid.getSelectedRecord();

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
    ,
    openHistoryPopup: function(auditType) {
      var viewParam = {};
      var historyName = null;
      var selectedRecord = _regGrid.getSelectedRecord();

      if (selectedRecord && selectedRecord != undefined) {
		  historyName = _translationMap["RegAgmtMt"] + ' - '
	          + _translationMap['History'];
	
    	switch(auditType){
    		case "RegulatoryAgrmt":
    			viewParam['searchValue1'] = selectedRecord.data['regAgrmtUUID'];
	            viewParam['auditType'] = 'RegulatoryAgrmt';
    			break;
    		case "RegulatoryAgrmtDetl":
    			viewParam['searchValue1'] = _resGrid.getSelectedRecord().data['regAgrmtDetlUUID'];
	            viewParam['auditType'] = 'RegulatoryAgrmtDetl';
    			break;
    	}
    	_resources.popups['history'].init(historyName, _dtHistoricalInfo,
                viewParam, true);
        _resources.popups['history'].show();
  }
    }
    ,
    selectRegulationAgreement: function(record, rowIndex) {
      _resGrid.clearData();
      if (record.data['RegAgrmtDetlsXML'] != null && 
    		  record.data['RegAgrmtDetlsXML'] != _self.BLANK) 
    	  _resGrid.loadData(IFDS.Xml.stringToXML(record.data['RegAgrmtDetlsXML']));
      _resGrid.setSelectedRecord(rowIndex);

      if (_permissionsMap[_MODPERM])
        _resGrid.enableButton(_MODBTN);
      _resGrid.enableButton(_HISBTN);
    }
    ,
    doValidateSearch: function() {
      var regulation = _resources.fields['regulationSrch'].isValid();
      var searchFor = _resources.fields['searchForSrch'].isValid();
      var partyType = _resources.fields['searchForSrch'].getValue();
      var searchValue = false;
      
      if (partyType == _PARTY_TYPE_ALL)
        searchValue = _resources.fields['searchForAll'].isValid();
      else if (partyType == _PARTY_TYPE_BROK)
        searchValue = _resources.fields['searchForBroker'].isValid();
      else if (partyType == _PARTY_TYPE_INTR)
        searchValue = _resources.fields['searchForIntermediary'].isValid();

      return (regulation && searchFor && searchValue);
    }
    ,
    doSearch: function(getMore) {
      doSearch(getMore);
    }
    ,
    doSave: function(action, popup) {
      doSave(action, popup);
    }
    ,
    isValidPopup: function(action, popupName) {
      var popup = _resources.popups[popupName];    
      var isSuccess = true
      var startDate = popup.getField('pStartDateFld').getValue();
      var stopDate = popup.getField('pStopDateFld').getValue();
      
      if (startDate > stopDate)
	  {
		 isSuccess = false;         
		 popup.getField('pStopDateFld').markInvalid(_translationMap['Error_StopDateNotPriorEffDate']);
	  }
			
     return isSuccess;
        
    }
    ,
    setSuggestService: function(code, popupName) {
      if (popupName == 'mainScreen') {
        for ( var name in _self.searchForCodeList) {
          _resources.fields[_self.searchForCodeList[name]].hide();
          _resources.fields[_self.searchForCodeList[name]].reset();
        }
        if (_resources.fields[_self.searchForCodeList[code]] != undefined
            && _resources.fields[_self.searchForCodeList[code]])
          _resources.fields[_self.searchForCodeList[code]].show();
        else
          _resources.fields['searchForAll'].show();
      } else if (popupName == 'regulationPopup') {
        _self.resetPartyTypeCodeList();
        _regPop.getField(_self.partyTypeCodeList[code]).show();
        _regPop.getField(_self.partyTypeCodeList[code]).allowBlank = false;
      }
    }
    ,
    resetPartyTypeCodeList: function() {
      for ( var name in _self.partyTypeCodeList) {
        _regPop.getField(_self.partyTypeCodeList[name]).hide();
//        _regPop.getField(_self.partyTypeCodeList[name]).reset();
        _regPop.getField(_self.partyTypeCodeList[name]).allowBlank = true;
      }
    }
    ,getDescription: function(listName, code){
    	 return IFDS.Xml.getNodeValue(_initXML, "//List[@listName = '" + listName + "']/Element[code = '" + code + "']/value");
    }
  }
}