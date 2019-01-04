/*********************************************************************************************
 * @file    RESPNotionalActivity.Controller.js
 * @author  Narin Suanlamyai
 * @desc    Controller JS file for Notional Activity screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  16 Jun 2015 Narin Suanlamyai P0241773 T81239
 *      - Initial
 *
 *  01 Aug 2015 Narin Suanlamyai P0241773 T81348
 *      - Reset Additional Information section
 *
 *  17 Sep 2015 Narin Suanlamyai    P0241773 T81293
 *       - Add validation for From/To Date fields
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *		 - Fixed screens don't response when user's profile has too many slots attached. 
 *
 *	21 Apr 2016 Narin Suanlamyai P0241773 DFT0059694 T82619
 *		 - Refresh the search result when user changes the Informaiton Level
 *
 *	10 May 2016 Narin Suanlamyai P0241773 DFT0060804 T82810
 *		- Update list of Activity Category combobox to load data from new transaction category list.
 *		- Add a new column Category.
 *
 */
 
DesktopWeb.ScreenController = function () {    
    
    // PRIVATE VARIABLES *************************************
    var _self = null;
    var _resources = null;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    var _notlActInqView = "dtNotlActivityINQ";
        
    var _ADD = 'add';
    var _MOD = 'mod';
    var _DEL = 'del';
    var _INQ = 'inq';

    var _currentSearch    = new Array();
    var _permissions    = new Array();
    var _defaultValues    = new Array();
    
    var _requestRecNum = 25;
    var _notlActXML = null;
    
    // PRIVATE METHODS ***************************************
    function storePermissions(xml) {
        var permissionsNode = IFDS.Xml.getNode(xml, '//Permissions');
        if (Ext.isObject(permissionsNode)) {
            _permissions[_self.INQ] = IFDS.Xml.getNodeValue(permissionsNode, 'inqPerm').toLowerCase() == 'yes';
            _permissions[_self.ADD] = IFDS.Xml.getNodeValue(permissionsNode, 'addPerm').toLowerCase() == 'yes';
            _permissions[_self.MOD] = IFDS.Xml.getNodeValue(permissionsNode, 'modPerm').toLowerCase() == 'yes';    
            _permissions[_self.DEL] = IFDS.Xml.getNodeValue(permissionsNode, 'delPerm').toLowerCase() == 'yes';
        }
    }

    function storeDefaultValues(xml) {
        var defaultValuesNode = IFDS.Xml.getNode(xml, '//DefaultValues');
        if (Ext.isObject(defaultValuesNode)) {
            _defaultValues['infoLevel'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'infoLevel');
            _defaultValues['txnCat'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'txnCat');
            _defaultValues['cateCode'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'cateCode');
            _defaultValues['cateValue'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'cateValue');
            _defaultValues['reasonCode'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'reasonCode');
            _defaultValues['fromDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'fromDate'));
            _defaultValues['toDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'toDate'));
            
            _currentSearch['txnCat'] = _defaultValues['txnCat'];
            _currentSearch['cateCode'] = _defaultValues['cateCode'];
            _currentSearch['cateValue'] = _defaultValues['cateValue'];
            _currentSearch['reasonCode'] = _defaultValues['reasonCode'];
            _currentSearch['fromDate'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'fromDate');
            _currentSearch['toDate'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'toDate');
        }
    }
    
    function populateFilters(xml) {
        if (_permissions[_self.INQ]) {
            // Load dropdown list
            _resources.fields['infoLevel'].loadData(IFDS.Xml.getNode(xml, '//List[@listName="InfoLevelOptions"]'));
            _resources.fields['reason'].loadData(IFDS.Xml.getNode(xml, '//List[@listName="ReasonList"]'));
            _resources.fields['actCat'].loadData(IFDS.Xml.getNode(xml, '//TxnCategoryList'));
            
            // populate default values
            _resources.fields['infoLevel'].setValue(_defaultValues['infoLevel']);
            _resources.fields['actCat'].setValue(_defaultValues['txnCat']);
            _resources.fields['reason'].setValue(_defaultValues['reasonCode']);
            _resources.fields['fromDate'].setValue(_defaultValues['fromDate']);
            _resources.fields['toDate'].setValue(_defaultValues['toDate']);
            
            // configure runtime validation
            _resources.fields['fromDate'].setMinValue(_defaultValues['fromDate']);
            _resources.fields['fromDate'].setMaxValue(_defaultValues['toDate']);
            _resources.fields['toDate'].setMinValue(_defaultValues['fromDate']);
            _resources.fields['toDate'].setMaxValue(_defaultValues['toDate']);
            
            // enable search criteria
            _resources.fields['infoLevel'].enable();
            _resources.fields['actCat'].enable();
            _resources.fields['reason'].enable();
            _resources.fields['fromDate'].enable();
            _resources.fields['toDate'].enable();
        
            _resources.buttons['refreshBtn'].enable();
        }
    }
    
    function doSearch(runMode, append) {
        _notlActInfoXML = null;
        var requestXML = IFDS.Xml.newDocument('data');
        
        IFDS.Xml.addSingleNode(requestXML, 'runMode', runMode);
        IFDS.Xml.addSingleNode(requestXML, 'account', _currentSearch['account']);
        
        if (_currentSearch['benefId'] > 0 ) {
            IFDS.Xml.addSingleNode(requestXML, 'benefId', _currentSearch['benefId']);
        }
        
        if (runMode !== 'init') {
            IFDS.Xml.addSingleNode(requestXML, 'txnCat', _currentSearch['txnCat']);
            IFDS.Xml.addSingleNode(requestXML, 'cateCode', _currentSearch['cateCode']);
            IFDS.Xml.addSingleNode(requestXML, 'cateValue', _currentSearch['cateValue']);
            IFDS.Xml.addSingleNode(requestXML, 'reasonCode', _currentSearch['reasonCode']);
            IFDS.Xml.addSingleNode(requestXML, 'fromDate', _currentSearch['fromDate']);
            IFDS.Xml.addSingleNode(requestXML, 'toDate', _currentSearch['toDate']);
        }
        
        IFDS.Xml.addSingleNode(requestXML, 'startRecNum', _currentSearch['startRecNum']);
        IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _currentSearch['requestRecNum']);
        
		DesktopWeb.Ajax.doSmartviewAjax(_notlActInqView, 
                                        (runMode == 'init' ? {ignoreErrorCode: '15'} : null), 
                                        requestXML, 
                                        responseHandler, 
                                        _translationMap['ProcMsg_Searching'])
        
        function responseHandler(success, responseXML) {
			if (runMode === 'init') {
                storePermissions(responseXML);
                storeDefaultValues(responseXML);
                populateFilters(responseXML);
            }
            
            if (append) {
                var newNotlActNodes = IFDS.Xml.getNodes(responseXML, '//NotionalActivities');
                var oldNotlActNode = IFDS.Xml.getNode(_notlActXML, '//NotionalActivities');
                Ext.each(newNotlActNodes, function (newNotlActNode) {
                    IFDS.Xml.appendNode(oldNotlActNode, IFDS.Xml.cloneDocument(newNotlActNode));
                });
                
            }else{
                _notlActXML = IFDS.Xml.cloneDocument(responseXML);
            }
            
            if (success) {
                loadNotionalActivity(responseXML, true);
                
                // control more button
                var nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
                if (nextStartRecNum) {
                    _currentSearch['nextRecNum'] = nextStartRecNum;
                    _resources.grids['notlAct'].enableButton('moreBtn');
                } else {
                    _currentSearch['nextRecNum'] = 1;
                    _resources.grids['notlAct'].disableButton('moreBtn');
                }
            }
        }
    }
    
    function loadNotionalActivity(xml, append) {
        var notlActsNode = IFDS.Xml.getNode(xml, "//NotionalActivities");
        if (notlActsNode) {
            if (append) {
                _resources.grids['notlAct'].appendData(notlActsNode);
            } else {
                _resources.grids['notlAct'].loadData(notlActsNode);
            }
        }
    }
    
    function loadNotionalImpact(notlTransId) {

        clearNotionalImpact();
        
        var notlImpactsNode = IFDS.Xml.getNode(_notlActXML, "//NotionalActivities/NotionalActivity[notlTransId='" + notlTransId + "']/NotionalActivityDetls");
        if (notlImpactsNode) {
            _resources.grids['notlActDetl'].loadData(notlImpactsNode);
        }
    }
    
    function clearNotionalActivity() {
        _resources.grids['notlAct'].getStore().removeAll();
        _resources.grids['notlAct'].disableAllButtons();
        
        // Reset fields in additional information section
        _resources.fields['notlChgReason'].reset();
        _resources.fields['remarks'].reset();
    }
    
    function clearNotionalImpact() {
        _resources.grids['notlActDetl'].getStore().removeAll();
        _resources.grids['notlActDetl'].disableAllButtons();
    }
    
    function loadAdditionalInfo(notlTransId) {
        _resources.fields['notlChgReason'].reset();
        _resources.fields['remarks'].reset();
        var notlActNode = IFDS.Xml.getNode(_notlActXML, "//NotionalActivities/NotionalActivity[notlTransId='" + notlTransId + "']");
        if (notlActNode) {
            _resources.fields['notlChgReason'].setValue(IFDS.Xml.getNodeValue(notlActNode, 'notlChgReason'));
            _resources.fields['remarks'].setValue(IFDS.Xml.getNodeValue(notlActNode, 'remarks'));
        }
    }
    
    function enableRESPNotionalBalanceButton() {
        var fromScreen = DesktopWeb._SCREEN_PARAM_MAP['fromScreen'];
        if (fromScreen === 'RESPNotionalBalance') {
            _resources.screenButtons[0].show();
        }
    }
    
    function goToScreen(screenName) {
        var params = {};
		
        // TODO: if info level is benef, this should be available.
        params['RESPBenefID'] = _currentSearch['benefId'];
        
		DesktopWeb.Util.goToScreen(screenName, params);
    }
    
    // PUBLIC ITEMS ******************************************
    return {
        ADD: _ADD
        ,MOD: _MOD
        ,DEL: _DEL
        ,INQ: _INQ
        
        ,updatesFlag: false
        
        ,init: function (res) {
            _resources = res;
            _self = DesktopWeb._SCREEN_CONTROLLER;
            
            _currentSearch['account'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
            
            var benefParam = DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID'];
            _currentSearch['benefId'] = (isNaN(benefParam)?'0':benefParam);
            
            _currentSearch['startRecNum'] = 1;
            _currentSearch['requestRecNum'] = _requestRecNum;

            enableRESPNotionalBalanceButton();
            
            doSearch('init');
        }
        
        ,clickHandle_searchBtn: function () {
            var searchValid = false;
            
            searchValid = _resources.fields['infoLevel'].isValid();
            searchValid = searchValid && _resources.fields['actCat'].isValid();
            searchValid = searchValid && _resources.fields['reason'].isValid();
            searchValid = searchValid && _resources.fields['fromDate'].isValid();
            searchValid = searchValid && _resources.fields['toDate'].isValid();
            
            if (searchValid) {
                var selectedInfoLevelRecord = _resources.fields['infoLevel'].getSelectedRecord();
                if (selectedInfoLevelRecord.get('level') === 'Benef') {
                    _currentSearch['benefId'] = selectedInfoLevelRecord.get('code');
                } else {
                    _currentSearch['benefId'] = 0;
                }
                
                // Activity Category
				var selectedActCat = _resources.fields['actCat'].getSelectedRecord();
				_currentSearch['txnCat'] = selectedActCat.data['txnCat'];
                _currentSearch['cateCode'] = selectedActCat.get('cateCode');
                _currentSearch['cateValue'] = selectedActCat.get('cateValue');
                _currentSearch['reasonCode'] = _resources.fields['reason'].getValue();
                _currentSearch['fromDate'] = _resources.fields['fromDate'].getSMVDateString();
                _currentSearch['toDate'] = _resources.fields['toDate'].getSMVDateString();
                
                clearNotionalImpact();
                clearNotionalActivity();
                doSearch('reload', false);
            }
            _currentSearch['startRecNum'] = 1;
            _currentSearch['requestRecNum'] = _requestRecNum;
        }
        
        ,selectHandler_infoLevel: function (infoLevelSelectedRecord) {
            var searchValid = false;
            
            searchValid = _resources.fields['infoLevel'].isValid();
            searchValid = searchValid && _resources.fields['actCat'].isValid();
            searchValid = searchValid && _resources.fields['reason'].isValid();
            searchValid = searchValid && _resources.fields['fromDate'].isValid();
            searchValid = searchValid && _resources.fields['toDate'].isValid();
            
            if (searchValid) {
                if (infoLevelSelectedRecord.get('level') === 'Benef') {
                    _currentSearch['benefId'] = infoLevelSelectedRecord.get('code');
                } else {
                    _currentSearch['benefId'] = 0;
                }
                
                // Activity Category
				var selectedActCat = _resources.fields['actCat'].getSelectedRecord();
				_currentSearch['txnCat'] = selectedActCat.get('txnCat');
                _currentSearch['cateCode'] = selectedActCat.get('cateCode');
                _currentSearch['cateValue'] = selectedActCat.get('cateValue');
                _currentSearch['reasonCode'] = _resources.fields['reason'].getValue();
                _currentSearch['fromDate'] = _resources.fields['fromDate'].getSMVDateString();
                _currentSearch['toDate'] = _resources.fields['toDate'].getSMVDateString();
				_currentSearch['startRecNum'] = 1;
				_currentSearch['requestRecNum'] = _requestRecNum;
                
                clearNotionalImpact();
                clearNotionalActivity();
                doSearch('reload', false);
            }
        }
        
        ,selectNotlActivity: function(record, index) {
            _resources.grids['notlAct'].enableButton('adminBtn');
            loadAdditionalInfo(record.get('notlTransId'));
            loadNotionalImpact(record.get('notlTransId'));
        }
        
        ,clickHandle_moreBtn: function () {
            _currentSearch['startRecNum'] = _currentSearch['nextRecNum'];
            _currentSearch['requestRecNum'] = _requestRecNum;
            doSearch('reload', true);
        }
        
        ,openAdminPopup: function(record)
        {                    
            var adminData = {};
            adminData['userName'] = record.get('userName');
            adminData['procDate'] = record.get('processDate');
            adminData['modUser'] = record.get('modUser');
            adminData['modDate'] = record.get('modDate');
            
            _resources.popups['admin'].init(adminData);
            _resources.popups['admin'].show();            
        }
        
        ,goToNotionalBalanceScreen: function () {
            goToScreen('RESPNotionalBalance');
        }
    }    
}    
