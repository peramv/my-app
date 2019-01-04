/*********************************************************************************************
 * @file    RESPNotionalBalance.Controller.js
 * @author  Narin Suanlamyai
 * @desc    Controller JS file for Notional Balance screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  16 Jun 2015 Narin Suanlamyai P0241773 T81011
 *      - Initial (Rewriting RESP Notional Info screen)
 *
 *  13 Jul 2015 Narin Suanlamyai P0241773 T81239
 *      - Add Adjustment pop-up
 *
 *  01 Aug 2015 Narin Suanlamyai P0241773 T81348
 *      - Fix selection Period change back to LTD
 *
 *  17 Sep 2015 Narin Suanlamyai P0241773 T81293
 *      - Add admin popup for breakdown
 *      - Effective date cannot be more than current business date
 *
 *  18 Nov 2015 Narin Suanlamyai P0241773 DFT0056095 T81754
 *      - Fix duplicate BCTESG label on Notional Details screen
 *
 *  11 Dec 2015 Narin Suanlamyai P0241773 DFT0056498 T81878
 *      - Fixed error message when adjusted balance is going to be negative
 *		- Fixed missing balance amount on adjustment screen.
 *		- Screen allows negative if it is more negative.
 *
 *  17 Dec 2015 Narin Suanlamyai P0241773 DFT0057429 T81893
 *      - Greyed-out Receive, Paid Out, and Return columns for Paid by Other row.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *		- Fixed screens don't response when user's profile has too many slots attached. 
 *
 *	21 Apr 2016 Narin Suanlamyai P0241773 DFT0059694 T82619
 *		- Refresh the search result when user changes the Informaiton Level
 *
 *	16 May 2016 Narin Suanlamyai P0241773 DFT0061569 T82733
 *		- Do the adjustment validation at notional bucket type.
 *		- The warning/error will be displayed next to adjusted balance row.
 *
 *  25 May 2016 Busarakorn S. P0241773 DFT0063337 T82916
 *      - Enable column Income Redemption on Benef level.
 *
 *  03 Jun 2016 Watchara Th. P0241773 DFT0064018 T83013
 *      - RESP Usability Improvement for Trade Entry.
 *      - Add a button to launch RESP National Balance from RESP Transfer Trade
 *      
 *  29 Jul 2016 Watchara Th. P0241773 DFT0065723 T83393
 *  	- Added current business date to initialize RESP Notional Adjustment pop-up  
 *
 *  08 Aug 2016 Watchara Th. P0241773 DFT0065536 T83423
 *      - Enabled field "Balance" at both account and beneficiary levels for all grant types.
 *
 *	28 Sep 2016 Narin Suanlamyai P0241773 DFT0059465 T83889
 *		 - Display QESI Pre-Feb 2007 in read-only mode.
 *		 - QESI Pre-Feb 2007 amount is calculated on the screen.
 *		 - Formula: QESI Pre-Feb 2007 = CNTB + P98C - QESIAC - QESIUC - QESIYTD
 *
 *	21 Oct 2016 Nopphawan Hatthaseriphong P0241773 DFT0068179 T84080 
 *		 - Fixed QESI buckets are getting created for Non-QESI account 
 *         by calculation QESI Basic Pre-Feb 21 2007 only QESI account
 *         (call updateQESIPreFeb2007).
 *         Add condition to check this account is QESI or not (from <isQESI> tag) 
 *         before calling updateQESIPreFeb2007.
 *         
 */
 
DesktopWeb.ScreenController = function () {    
    
    // PRIVATE VARIABLES *************************************
    var _self = null;
    var _resources = null;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    var _notlBalInqView = "dtNotlBalanceInq";
    var _notlBrkInqView = "dtNotlDetailInq";
    var _notlAdjInqView = "dtNotlAdjustINQ";
    var _notlAdjUpdView = "dtNotlAdjustUPD";
        
    var _ADD = 'add';
    var _MOD = 'mod';
    var _DEL = 'del';
    var _INQ = 'inq';
    var _YES = 'yes';
    var _NOTIONALTYPE_CNTB = "CNTB";
    var _NOTIONALTYPE_P98C = "P98C";
    var _NOTIONALTYPE_INCOME = "INCM";
    var _NOTIONALTYPE_CESG = "CESG";
    var _NOTIONALTYPE_ADCESG = "ADCESG";
    var _NOTIONALGROUP_CESG = "CESG";
    var _NOTIONALGROUP_QESI = "QESI";
    var _NOTIONALGROUP_SAGES = "SAGES";
    var _NOTIONALGROUP_BCTESG = "BCTESG";
    var _NOTIONALGROUP_CLB = "CLB";
    var _NOTIONALGROUP_INCOME = "INCM";
    
    var _ltdYear = null;

    var _currentSearch    = new Array();
    var _currentAdjSearch    = new Array();
    var _permissions    = new Array();
    var _defaultValues    = new Array();
	var _QESIPreFebImpact = ["CNTB-CNTB-Amount", "CNTB-P98C-Amount", "QESI-QESIB-ACAmount", "QESI-QESIB-UCAmount", "QESI-QESIB-YTDAmount"];
    
    var _requestBreakdownRecNum = 25;
    var _notlInfoXML = null;
    
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
            _defaultValues['infoLevelOption'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'infoLevelOption');
            _defaultValues['periodOption'] = IFDS.Xml.getNodeValue(defaultValuesNode, 'periodOption');
            _defaultValues['curBusDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'curBusDate'));
        }
    }
    
    function populateFilters(xml) {
        
        function customizePeriodOptionsList(xmlList) {
            var newPeriodOptionsList = IFDS.Xml.cloneDocument(xmlList);
            var ltdCodeEle = IFDS.Xml.getNode(newPeriodOptionsList, '//Element[level="LTD"]/code');
            _ltdYear = IFDS.Xml.getNodeValue(ltdCodeEle, '.');
            IFDS.Xml.setNodeValue(ltdCodeEle, 'LTD');
            return newPeriodOptionsList;
        }
        
        var infoLevelList = IFDS.Xml.getNode(xml, '//List[@listName="InfoLevelOptions"]');
        if (Ext.isObject(infoLevelList)) {
            _resources.fields['infoLevel'].enable();
            _resources.fields['period'].enable();
            _resources.fields['periodRadio'].enable();
            _resources.fields['asOfRadio'].enable();
            _resources.buttons['refreshBtn'].enable();

            _resources.fields['periodRadio'].setValue(true);

            _resources.fields['infoLevel'].loadData(infoLevelList);
            _resources.fields['period'].loadData(customizePeriodOptionsList(IFDS.Xml.getNode(xml, '//List[@listName="PeriodOptions"]')));

            _resources.fields['infoLevel'].setValue(_defaultValues['infoLevelOption']);
            _resources.fields['period'].setValue('LTD');
        }
    }
    
    function setInitCurrentSearch() {
        var selectedInfoLevelRecord = _resources.fields['infoLevel'].getSelectedRecord();
        if (Ext.isObject(selectedInfoLevelRecord)) {
            _currentSearch['infoLevelDesc'] = selectedInfoLevelRecord.get('description');
            
            if (_resources.fields['periodRadio'].checked) {
                var selectedPeriodRecord = _resources.fields['period'].getSelectedRecord();
                
                _currentSearch['periodLevel'] = selectedPeriodRecord.get('level');
                _currentSearch['periodCode'] = (selectedPeriodRecord.get('code') === 'LTD')?_ltdYear:selectedPeriodRecord.get('code');
                _currentSearch['periodDesc'] = selectedPeriodRecord.get('description');
                _currentSearch['asOfDate'] = null;
                _currentSearch['asOfDateDisp'] = null;
            } else {
                _currentSearch['periodLevel'] = 'AOD';
                _currentSearch['periodCode'] = '';
                _currentSearch['periodDesc'] = '';
                _currentSearch['asOfDate'] = _resources.fields['asOfDate'].getSMVDateString();
                _currentSearch['asOfDateDisp'] = _resources.fields['asOfDate'].getDisplayDateString();
            }
        }
    }
    
    function setScreenButtons() {
        if(DesktopWeb._SCREEN_PARAM_MAP['from_screen'] != 'RESPTransfersDlg') {
            if (_permissions[_self.INQ]) {
                _resources.screenButtons[0].enable();
            }
            if (_permissions[_self.MOD]) {
                _resources.screenButtons[1].enable();
            }
        }
    }
    
    function doSearch(runMode) {
        _notlInfoXML = null;
        var requestXML = IFDS.Xml.newDocument('data');
        
        IFDS.Xml.addSingleNode(requestXML, 'runMode', runMode);
        IFDS.Xml.addSingleNode(requestXML, 'account', _currentSearch['account']);
        IFDS.Xml.addSingleNode(requestXML, 'periodLevel', _currentSearch['periodLevel']);
        
        if (_currentSearch['benefId'] > 0 ) {
            IFDS.Xml.addSingleNode(requestXML, 'benefId', _currentSearch['benefId']);
        }
        
        if (runMode !== 'init') {
            if (_currentSearch['periodLevel'] === 'AOD') {
                IFDS.Xml.addSingleNode(requestXML, 'asOfDate', _currentSearch['asOfDate']);
            } else {
                IFDS.Xml.addSingleNode(requestXML, 'periodCode', _currentSearch['periodCode']);
            }
        }
        
        DesktopWeb.Ajax.doSmartviewAjax(_notlBalInqView, 
                                        (runMode == 'init' ? {ignoreErrorCode: '15'} : null), 
                                        requestXML, 
                                        responseHandler, 
                                        _translationMap['ProcMsg_Searching'])
        
        function responseHandler(success, responseXML) {
            if (runMode === 'init') {
                storePermissions(responseXML);
                storeDefaultValues(responseXML);
                populateFilters(responseXML);
                setInitCurrentSearch();
                setScreenButtons();
            }
            
            if (success) {
                loadNotionalBalance(responseXML);
            }
            _notlInfoXML = IFDS.Xml.cloneDocument(responseXML);
        }
    }
    
    function loadNotionalBalance(xml) {
        loadMarketValue(xml);
        loadContributionIncome(xml);
        loadAssistedUnassisted(xml);
        loadGrants(xml);
    }
    
    function loadMarketValue(xml) {
        _resources.fields['marketValue'].setValue(IFDS.Xml.getNodeValue(xml, '//marketValue'));
    }
    
    function loadContributionIncome(xml) {
        var contribIncomeRoot = _resources.grids['contribIncome'].getRootNode();
        
        var contribNodes = IFDS.Xml.getNodes(xml, '//NotlInfo/NotlInfoGrp[grpType="Contribution"]/NotlDetls/NotlDetl');
        
        var infoLevel = _resources.fields['infoLevel'].getSelectedRecord().get('level');

        Ext.each(contribNodes, function (contribNode) {
            addContributionRow(contribNode);
        });
        
        contribIncomeRoot.collapse(true);
        
        function addContributionRow(contribNode) {
            var notlGroup = IFDS.Xml.getNodeValue(contribNode, 'notlGroup');
            var notlType = IFDS.Xml.getNodeValue(contribNode, 'notlType');
            var desc = IFDS.Xml.getNodeValue(contribNode, 'description');
            if (notlType === _NOTIONALTYPE_CNTB || notlType === _NOTIONALTYPE_P98C) {
                desc = "<ins onclick='DesktopWeb._SCREEN_CONTROLLER.openBreakdownPopup(\"Contribution\", \"" + notlGroup + "\", \"" + notlType + "\")' >" + desc + "</ins>";
            }
            contribIncomeRoot.appendChild({   
                description: desc, 
                received: IFDS.Xml.getNodeValue(contribNode, 'received'), 
                paidOut: IFDS.Xml.getNodeValue(contribNode, 'paidOut'), 
                adjusted: IFDS.Xml.getNodeValue(contribNode, 'adjusted'), 
                balance: IFDS.Xml.getNodeValue(contribNode, 'balance'), 
                disabledColumns: getDisableFields(infoLevel, 'Contribution', notlGroup, notlType),
                disabledColumnsClass: 'DesktopWeb-Disabled-Cell',
                leaf: true,
                expanded:false
            });
        }
    }
    
    function loadAssistedUnassisted(xml) {
        var grantRoot = _resources.grids['acuc'].getRootNode();
        
        var grantNodes = IFDS.Xml.getNodes(xml, '//NotlInfo/NotlInfoGrp[grpType="ACUC"]/NotlDetls/NotlDetl');
        
        var infoLevel = _resources.fields['infoLevel'].getSelectedRecord().get('level');
        
        Ext.each(grantNodes, function (grantNode) {
            addGrantRow(grantNode);
        });
        
        function addGrantRow(grantNode) {
            var notlGroup = IFDS.Xml.getNodeValue(grantNode, 'notlGroup');
            var notlType = IFDS.Xml.getNodeValue(grantNode, 'notlType');

            var grantRow = grantRoot.appendChild({   
                description: IFDS.Xml.getNodeValue(grantNode, 'description'), 
                received: IFDS.Xml.getNodeValue(grantNode, 'received'), 
                paidOut: IFDS.Xml.getNodeValue(grantNode, 'paidOut'), 
                adjusted: IFDS.Xml.getNodeValue(grantNode, 'adjusted'), 
                balance: IFDS.Xml.getNodeValue(grantNode, 'balance'), 
                disabledColumns: getDisableFields(infoLevel, 'ACUC', notlGroup, notlType),
                disabledColumnsClass: 'DesktopWeb-Disabled-Cell',
                leaf: false,
                expanded:true,
                children: []
            });
            
            var acucNodes = IFDS.Xml.getNodes(grantNode, 'ACUCDetls/ACUCDetl');
            Ext.each(acucNodes, function (acucNode) {
                addACUCRow(acucNode, grantRow)
            });
            
        }
        
        function addACUCRow(childNode, parentRow) {
            var childNotlGroup = IFDS.Xml.getNodeValue(childNode, 'notlGroup');
            var childNotlType = IFDS.Xml.getNodeValue(childNode, 'notlType');

            parentRow.appendChild({   
                description: IFDS.Xml.getNodeValue(childNode, 'description'), 
                received: IFDS.Xml.getNodeValue(childNode, 'received'), 
                paidOut: IFDS.Xml.getNodeValue(childNode, 'paidOut'), 
                adjusted: IFDS.Xml.getNodeValue(childNode, 'adjusted'), 
                balance: IFDS.Xml.getNodeValue(childNode, 'balance'), 
                disabledColumns: getDisableFields(infoLevel, 'ACUC', childNotlGroup, childNotlType),
                disabledColumnsClass: 'DesktopWeb-Disabled-Cell',
                leaf: true,
                expanded:false
            });
        }
    }

    function loadGrants(xml) {
        var grantRoot = _resources.grids['grants'].getRootNode();
        
        var grantNodes = IFDS.Xml.getNodes(xml, '//NotlInfo/NotlInfoGrp[grpType="Grant"]/NotlDetls/NotlDetl');
        
        var infoLevel = _resources.fields['infoLevel'].getSelectedRecord().get('level');
        
        Ext.each(grantNodes, function (grantNode) {
            addGrantRow(grantNode);
        });
        
        function addGrantRow(grantNode) {
            var notlGroup = IFDS.Xml.getNodeValue(grantNode, 'notlGroup');
            var notlType = IFDS.Xml.getNodeValue(grantNode, 'notlType');
            var desc = IFDS.Xml.getNodeValue(grantNode, 'description');
            
            if (notlGroup === _NOTIONALGROUP_CLB) {
                desc = "<ins onclick='DesktopWeb._SCREEN_CONTROLLER.openBreakdownPopup(\"Grant\", \"" + notlGroup + "\", \"" + notlType + "\")' >" + desc + "</ins>";
            }
            
            var grantRow = grantRoot.appendChild({   
                description: desc, 
                received: IFDS.Xml.getNodeValue(grantNode, 'received'), 
                paidOut: IFDS.Xml.getNodeValue(grantNode, 'paidOut'), 
                returned: IFDS.Xml.getNodeValue(grantNode, 'returned'), 
                adjusted: IFDS.Xml.getNodeValue(grantNode, 'adjusted'), 
                balance: IFDS.Xml.getNodeValue(grantNode, 'balance'), 
                pendClawBack: IFDS.Xml.getNodeValue(grantNode, 'amtToReturn'), 
                disabledColumns: getDisableFields(infoLevel, 'Grant', notlGroup, notlType),
                disabledColumnsClass: 'DesktopWeb-Disabled-Cell',
                leaf: false,
                expanded:true,
                children: []
            });
            
            if (notlGroup !== _NOTIONALGROUP_CLB) {
                var detlNodes = IFDS.Xml.getNodes(grantNode, 'GrantDetls/GrantDetl');
                Ext.each(detlNodes, function (detlNode) {
                    addGrantDetlRow(detlNode, grantRow)
                });
            }
            
        }
        
        function addGrantDetlRow(childNode, parentRow) {
            var childDesc = IFDS.Xml.getNodeValue(childNode, 'description');
            var childNotlGroup = IFDS.Xml.getNodeValue(childNode, 'notlGroup');
            var childNotlType = IFDS.Xml.getNodeValue(childNode, 'notlType');
            var byOther = "OTHER";
            if (childNotlType.indexOf(byOther, childNotlType.length - byOther.length) === -1) {
                childDesc = "<ins onclick='DesktopWeb._SCREEN_CONTROLLER.openBreakdownPopup(\"Grant\", \"" + childNotlGroup + "\", \"" + childNotlType + "\")' >" + childDesc + "</ins>";
            }
            
            parentRow.appendChild({   
                description: childDesc, 
                received: IFDS.Xml.getNodeValue(childNode, 'received'), 
                paidOut: IFDS.Xml.getNodeValue(childNode, 'paidOut'), 
                returned: IFDS.Xml.getNodeValue(childNode, 'returned'), 
                adjusted: IFDS.Xml.getNodeValue(childNode, 'adjusted'), 
                balance: IFDS.Xml.getNodeValue(childNode, 'balance'), 
                pendClawBack: IFDS.Xml.getNodeValue(childNode, 'amtToReturn'), 
                disabledColumns: getDisableFields(infoLevel, 'Grant', childNotlGroup, childNotlType),
                disabledColumnsClass: 'DesktopWeb-Disabled-Cell',
                leaf: true,
                expanded:false
            });
        }
    }
    
    function getDisableFields(infoLevel, groupType, notlGroup, notlType) {
        var disabledColumns = [];
        if (infoLevel === 'Benef' && notlGroup !== _NOTIONALGROUP_CLB && groupType !== 'Grant') {
            disabledColumns.push('balance');
        } 
        if (notlGroup === _NOTIONALGROUP_INCOME && notlType === _NOTIONALTYPE_INCOME) {
            disabledColumns.push('received');
            disabledColumns.push('adjusted');
            if (infoLevel === 'Benef') {
                disabledColumns.push('balance');
            }
        }
        var byOther = "OTHER";
        if (notlType.indexOf(byOther, notlType.length - byOther.length) > -1) {
            disabledColumns.push('received');
            disabledColumns.push('paidOut');
            disabledColumns.push('returned');
        }
        return disabledColumns;
    }

    function clearNotionalDetails() {
        _resources.fields['marketValue'].reset();
        _resources.grids['contribIncome'].getRootNode().removeAll();
        _resources.grids['acuc'].getRootNode().removeAll();
        _resources.grids['grants'].getRootNode().removeAll();
    }
    
    function doBreakdownSearch(runMode, append) {
        var requestXML = IFDS.Xml.newDocument('data');
        
        IFDS.Xml.addSingleNode(requestXML, 'runMode', runMode);
        IFDS.Xml.addSingleNode(requestXML, 'account', _currentSearch['account']);
        IFDS.Xml.addSingleNode(requestXML, 'periodLevel', _currentSearch['periodLevel']);
        
        if (_currentSearch['benefId'] > 0 ) {
            IFDS.Xml.addSingleNode(requestXML, 'benefId', _currentSearch['benefId']);
        }
        
        if (_currentSearch['periodLevel'] === 'AOD') {
            IFDS.Xml.addSingleNode(requestXML, 'asOfDate', _currentSearch['asOfDate']);
        } else {
            IFDS.Xml.addSingleNode(requestXML, 'periodCode', _currentSearch['periodCode']);
        }

        IFDS.Xml.addSingleNode(requestXML, 'notlGroup', _currentSearch['notlGroup']);
        IFDS.Xml.addSingleNode(requestXML, 'notlType', _currentSearch['notlType']);
        
        if (runMode !== 'init') {
            IFDS.Xml.addSingleNode(requestXML, 'startDate', _currentSearch['startDate']);
            IFDS.Xml.addSingleNode(requestXML, 'endDate', _currentSearch['endDate']);
        }

        IFDS.Xml.addSingleNode(requestXML, 'startRecNum', append?_currentSearch['nextBreakdownRecNum']:'1');
        IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _currentSearch['requestBreakdownRecNum']);
        
        DesktopWeb.Ajax.doSmartviewAjax(_notlBrkInqView, 
                                        null,
                                        requestXML, 
                                        responseHandler, 
                                        _translationMap['ProcMsg_Searching'])
        
        function responseHandler(success, responseXML) {
            if (runMode === 'init') {
                setDefaultDateRange(responseXML);
            }
            if (success) {
                if (!append) {
                    clearNotionalBreakdown();
                } 
                
                loadNotionalBreakdown(responseXML, append);
                
                // control more button
                var nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
                if (nextStartRecNum) {
                    _currentSearch['nextBreakdownRecNum'] = nextStartRecNum;
                    _resources.grids['notlDetls'].enableButton('moreBtn');
                } else {
                    _currentSearch['nextBreakdownRecNum'] = 1;
                    _resources.grids['notlDetls'].disableButton('moreBtn');
                }
            }
        }
        
        function setDefaultDateRange(xml) {
            var defaultValuesNode = IFDS.Xml.getNode(xml, "//DefaultValues");
            if (Ext.isObject(defaultValuesNode)) {
                _resources.popups['notlDetls'].getField('startDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'startDate')));
                _resources.popups['notlDetls'].getField('endDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'endDate')));
                _currentSearch['startDate'] = _resources.popups['notlDetls'].getField('startDate').getSMVDateString();
                _currentSearch['endDate'] = _resources.popups['notlDetls'].getField('endDate').getSMVDateString();
            }
        }
    }
    
    function loadNotionalBreakdown(xml, append) {
        var notlDetlNode = IFDS.Xml.getNode(xml, "//NotlActivities");
        if (notlDetlNode) {
            if (append) {
                _resources.grids['notlDetls'].appendData(notlDetlNode);
            } else {
                _resources.grids['notlDetls'].loadData(notlDetlNode);
            }
        }
    }

    function clearNotionalBreakdown() {
        _resources.grids['notlDetls'].getStore().removeAll();
        _resources.grids['notlDetls'].disableAllButtons();
    }

    function goToScreen(screenName) {
        var params = {};
		
        params['fromScreen'] = 'RESPNotionalBalance';
		params['RESPBenefID'] = _currentSearch['benefId'];
        
		DesktopWeb.Util.goToScreen(screenName, params);
    }
    
    function openAdjustmentPopup() {
        var popup = _resources.popups['adjustPopup'];
        popup.init();
        popup.show();
    }
    
    function doLoadEligibleAdjustment(runMode) {
        var requestXML = IFDS.Xml.newDocument('data');
        
        _currentAdjSearch['account'] = _currentSearch['account'];
        
        if (runMode === 'init') {
            _currentAdjSearch['benefId'] = _currentSearch['benefId'];
            
            _currentAdjSearch['deff'] = DesktopWeb.Util.getSMVDateValue(_defaultValues['curBusDate']);
        }else{
            var selectedInfoLevelRecord = _resources.popups['adjustPopup'].getField('infoLevel').getSelectedRecord();
            
            _currentAdjSearch['benefId'] = selectedInfoLevelRecord.get('code');
            
            _currentAdjSearch['deff'] = _resources.popups['adjustPopup'].getField('deff').getSMVDateString();
        }
        
        // Always send runMode as init for force smartview send all eligible list again
        IFDS.Xml.addSingleNode(requestXML, 'runMode', 'init');
        IFDS.Xml.addSingleNode(requestXML, 'account', _currentAdjSearch['account']);
        
        if (_currentAdjSearch['benefId'] > 0 ) {
            IFDS.Xml.addSingleNode(requestXML, 'benefId', _currentAdjSearch['benefId']);
        }
        
        if (!Ext.isEmpty(_currentAdjSearch['deff'])) {
            IFDS.Xml.addSingleNode(requestXML, 'deff', _currentAdjSearch['deff']);
        }
        
        DesktopWeb.Ajax.doSmartviewAjax(_notlAdjInqView, 
                                        null,
                                        requestXML, 
                                        responseHandler, 
                                        _translationMap['ProcMsg_Searching'])
        
        function responseHandler(success, responseXML) {
            
            function addNotlTypeList(context, code) {
                var eleNode = IFDS.Xml.getNode(responseXML, '//List[@listName="NotionalTypeList"]/Element[code="' + code + '"]')
                IFDS.Xml.appendNode(context, IFDS.Xml.cloneDocument(eleNode));
            }
            
            function getDescNotlTypeList(code) {
                var notlTypeDesc = IFDS.Xml.getNodeValue(responseXML, '//List[@listName="NotionalTypeList"]/Element[code="' + code + '"]/value')
                return notlTypeDesc;
            }
            
            if (success) {
                var adjPopup = _resources.popups['adjustPopup'];
                var defaultValuesNode = IFDS.Xml.getNode(responseXML, '//DefaultValues');
                
                if (runMode === 'init') {
                    // Load Information Level
                    var infoLevelFld = adjPopup.getField('infoLevel');
                    infoLevelFld.reset();
                    infoLevelFld.loadData(IFDS.Xml.getNode(responseXML, '//List[@listName="InfoLevelOptions"]'));
                    infoLevelFld.setValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'infoLevel'));

                    // Load Effective Date
                    var deffFld = adjPopup.getField('deff');
                    deffFld.reset();
                    deffFld.setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'curBusDate')));
                    deffFld.setMaxValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'curBusDate')));
                    
                    // Load Reason
                    var reasonFld = adjPopup.getField('reason');
                    reasonFld.reset();
                    reasonFld.loadData(IFDS.Xml.getNode(responseXML, '//List[@listName="NotlChgReasonList"]'));
                    reasonFld.setValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'reasonCode'));
                    
                    // Reset Remarks
                    var remarkFld = adjPopup.getField('remarks');
                    remarkFld.reset();
                }
                
                // Load Notional Type
                var notlFld = adjPopup.getField('notlType');
                notlFld.reset();
                var notlGrpList = IFDS.Xml.newDocument('List');
                addNotlTypeList(notlGrpList, 'ALL');
                
                // Load adjustment panel
                adjPopup.clearAdjustmentContainer();
                
                var adjustContainer = Ext.getCmp('adjustmentContainer');
                
                var notlBalNodes = IFDS.Xml.getNodes(responseXML, '//NotlBalance');
                
                Ext.each(notlBalNodes, function (notlBalNode) {
                    var notlGrp = IFDS.Xml.getNodeValue(notlBalNode, 'notlGroup');
                    
                    addNotlTypeList(notlGrpList, notlGrp);
                    
                    var notlFldSet = new Ext.form.FieldSet({
                        title: getDescNotlTypeList(notlGrp),
                        id: notlGrp,
                        collapsible: true
                    });
                    
                    var notlBalDetlNodes = IFDS.Xml.getNodes(notlBalNode, 'NotlBalDetls/NotlBalDetl');
                    
                    Ext.each(notlBalDetlNodes, function (notlBalDetlNode) {
                        var notlType = IFDS.Xml.getNodeValue(notlBalDetlNode, 'notlType');
                        var bucketType = IFDS.Xml.getNodeValue(notlBalDetlNode, 'bucketType');
                        var fldId = notlGrp + "-" + notlType + '-' + bucketType;
                        var row = new DesktopWeb.ScreenResources.AdjustRow({
                            rowLabel: IFDS.Xml.getNodeValue(notlBalDetlNode, 'description')
                            ,id: fldId
							,notlGrp: notlGrp
                            ,notlType: notlType
                            ,bucketType: bucketType
                            ,balance: {id: fldId + '_Bal', value: IFDS.Xml.getNodeValue(notlBalDetlNode, 'curBal') }
                            ,adjust: {id: fldId + '_Adj', value: 0.00, readOnly: (bucketType === 'QESI2007')?true:false}
                            ,adjusted: {id: fldId + '_Adjed', value: IFDS.Xml.getNodeValue(notlBalDetlNode, 'curBal') }
							,callbackFn: (_QESIPreFebImpact.indexOf(fldId) < 0)?null:updateQESIPreFeb2007
                        })
                        
                        notlFldSet.add(row);
                    })
					adjustContainer.add(notlFldSet);					
                })
                
				adjustContainer.doLayout();
				
                // Load applicable notional types only
                notlFld.loadData(notlGrpList);
                notlFld.setValue(IFDS.Xml.getNodeValue(defaultValuesNode, 'notlGroup'));
            }
        }
    }
	
	function updateQESIPreFeb2007(fld, adjAmt, balAmt) {
		var selectedInfoLevelRecord = _resources.popups['adjustPopup'].getField('infoLevel').getSelectedRecord();
        var isQESI = selectedInfoLevelRecord.get('isQESI');
        
		if (isQESI.toLowerCase() == _self.YES) {
			var newQESIAdj = getAdjustedBalance('CNTB-CNTB-Amount') 
								+ getAdjustedBalance('CNTB-P98C-Amount') 
								- getAdjustedBalance('QESI-QESIB-ACAmount')
								- getAdjustedBalance('QESI-QESIB-UCAmount')
								- getAdjustedBalance('QESI-QESIB-YTDAmount')
								- getCurrentBalance('QESI-QESIB-QESI2007');
					
			Ext.getCmp('QESI-QESIB-QESI2007').doAdjustment(newQESIAdj);
			
			function getAdjustedBalance(fldName) {
				var fld = Ext.getCmp(fldName);
				return parseFloat((Ext.isObject(fld) && !isNaN(fld.getAdjustedBalance())) ? fld.getAdjustedBalance() : 0);
			}
			
			function getCurrentBalance(fldName) {
				var fld = Ext.getCmp(fldName);
				return parseFloat((Ext.isObject(fld) && !isNaN(fld.getCurrentBalance())) ? fld.getCurrentBalance() : 0);
			}	
		}
	}
	
    function buildAdjustmentUpdateXML() {
        var notlTypeGrps = null;
        var notlTypeGrp = null;
        var notlGrp = null;
        
        var requestXML = IFDS.Xml.newDocument('data');
        
        var adjPopup = _resources.popups['adjustPopup'];
        var selectedInfoLevelRecord = _resources.fields['infoLevel'].getSelectedRecord();
        
        IFDS.Xml.addSingleNode(requestXML, 'runMode', 'upd');
        IFDS.Xml.addSingleNode(requestXML, 'account', _currentSearch['account']);
        IFDS.Xml.addSingleNode(requestXML, 'benefId', adjPopup.getField('infoLevel').getSelectedRecord().get('code'));
        IFDS.Xml.addSingleNode(requestXML, 'effDate', adjPopup.getField('deff').getSMVDateString());
        IFDS.Xml.addSingleNode(requestXML, 'reasonCode', adjPopup.getField('reason').getValue());
        IFDS.Xml.addSingleNode(requestXML, 'remark', adjPopup.getField('remarks').getValue());
        
        var notlBalsNode = IFDS.Xml.addSingleNode(requestXML, 'NotlBalances');
        var notlBalNode = null;
        var notlBalDetlsNode = null;
        var notlBalDetlNode = null;
        
        var adjustContainer = Ext.getCmp('adjustmentContainer');
        notlTypeGrps = adjustContainer.items;
        for (i = 0; i < notlTypeGrps.items.length; i++) {
            notlTypeGrp = notlTypeGrps.items[i].items;
            notlGrp = notlTypeGrps.items[i].id;
            var bucketType = "";
            var notlType = "";
            var adjAmt = 0;
            var cntAdj = 0;
            
            for (j = 0; j < notlTypeGrp.items.length; j++) {
				
				// QESI Pre-Feb 2007 Amount is a calculation value, no need to update
				if (notlTypeGrps.items[i].id !== "QESI-QESIB-QESI2007") {
					adjAmt = notlTypeGrp.items[j].getAdjustment();
					
					if (parseFloat(adjAmt) != 0) {						
						if (cntAdj === 0) {
							cntAdj++;
							notlBalNode = IFDS.Xml.addSingleNode(notlBalsNode, 'NotlBalance');
							IFDS.Xml.addSingleNode(notlBalNode, 'notlGroup', notlGrp);
							
							notlBalDetlsNode = IFDS.Xml.addSingleNode(notlBalNode, 'NotlBalDetls');
						}
						notlType = notlTypeGrp.items[j].notlType;
						bucketType = notlTypeGrp.items[j].bucketType;
						notlBalDetlNode = IFDS.Xml.addSingleNode(notlBalDetlsNode, 'NotlBalDetl');
						IFDS.Xml.addSingleNode(notlBalDetlNode, 'notlType', notlType);
						IFDS.Xml.addSingleNode(notlBalDetlNode, 'bucketType', bucketType);
						IFDS.Xml.addSingleNode(notlBalDetlNode, 'adjustAmt', adjAmt);
					}
				}
            }
        }
        
        return requestXML;
    }

    function buildAdjustmentValidateXMLByNotlType(notlGrp, notlType, bucketType, adjAmt) {
        var requestXML = IFDS.Xml.newDocument('data');
        
        var adjPopup = _resources.popups['adjustPopup'];
        
        IFDS.Xml.addSingleNode(requestXML, 'runMode', 'val');
        IFDS.Xml.addSingleNode(requestXML, 'account', _currentSearch['account']);
        IFDS.Xml.addSingleNode(requestXML, 'benefId', adjPopup.getField('infoLevel').getSelectedRecord().get('code'));
        IFDS.Xml.addSingleNode(requestXML, 'effDate', adjPopup.getField('deff').getSMVDateString());
        IFDS.Xml.addSingleNode(requestXML, 'reasonCode', adjPopup.getField('reason').getValue());
        IFDS.Xml.addSingleNode(requestXML, 'remark', adjPopup.getField('remarks').getValue());
        
        var notlBalsNode = IFDS.Xml.addSingleNode(requestXML, 'NotlBalances');
        var notlBalNode = IFDS.Xml.addSingleNode(notlBalsNode, 'NotlBalance');
		IFDS.Xml.addAttribute(notlBalNode, 'RecordSource', notlGrp + '-' + notlType + '-' + bucketType);
        var notlBalDetlsNode = IFDS.Xml.addSingleNode(notlBalNode, 'NotlBalDetls');
        var notlBalDetlNode = IFDS.Xml.addSingleNode(notlBalDetlsNode, 'NotlBalDetl');
        
		IFDS.Xml.addSingleNode(notlBalNode, 'notlGroup', notlGrp);
		
		IFDS.Xml.addSingleNode(notlBalDetlNode, 'notlType', notlType);
		IFDS.Xml.addSingleNode(notlBalDetlNode, 'bucketType', bucketType);
		IFDS.Xml.addSingleNode(notlBalDetlNode, 'adjustAmt', adjAmt);
		
        return requestXML;
    }

    // PUBLIC ITEMS ******************************************
    return {
        ADD: _ADD
        ,MOD: _MOD
        ,DEL: _DEL
        ,INQ: _INQ
        ,YES: _YES
        
        ,updatesFlag: false
        
        ,init: function (res) {
            _resources = res;
            _self = DesktopWeb._SCREEN_CONTROLLER;
            
            _currentSearch['account'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
            
            var benefParam = DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID'];
            _currentSearch['benefId'] = (isNaN(benefParam)?'0':benefParam);

            _currentSearch['periodLevel'] = 'LTD';
            _currentSearch['periodCode'] = '';
            _currentSearch['asOfDate'] = null;
            
            doSearch('init');
        }
        
        ,openBreakdownPopup: function (groupType, notlGroup, notlType) {
            var popup = _resources.popups['notlDetls'];
            popup.init(groupType, notlGroup, notlType);
            popup.show();
            
            _currentSearch['notlGroup'] = notlGroup;
            _currentSearch['notlType'] = notlType;
            _currentSearch['nextBreakdownRecNum'] = 1;
            _currentSearch['requestBreakdownRecNum'] = _requestBreakdownRecNum;
            
            doBreakdownSearch('init');
        }
        
        ,toggleFilterFields: function () {
            if (_resources.fields['periodRadio'].getValue()) {
                _resources.fields['period'].enable();
                _resources.fields['period'].allowBlank = false;
                _resources.fields['asOfDate'].disable();
                _resources.fields['asOfDate'].reset();
            } else {
                _resources.fields['asOfDate'].enable();
                _resources.fields['asOfDate'].allowBlank = false;
                _resources.fields['period'].disable();
                _resources.fields['period'].reset();
            }
        }
        
        ,clickHandle_searchBtn: function () {
            var searchValid = false;
            
            if (_resources.fields['periodRadio'].checked) {
                searchValid = _resources.fields['period'].isValid();
            } else{
                searchValid = _resources.fields['asOfDate'].isValid();
            }
            
            if (searchValid) {
                var selectedInfoLevelRecord = _resources.fields['infoLevel'].getSelectedRecord();
                if (selectedInfoLevelRecord.get('level') === 'Benef') {
                    _currentSearch['benefId'] = selectedInfoLevelRecord.get('code');
                } else {
                    _currentSearch['benefId'] = 0;
                }
                
                _currentSearch['infoLevelDesc'] = selectedInfoLevelRecord.get('description');
                
                if (_resources.fields['periodRadio'].checked) {
                    var selectedPeriodRecord = _resources.fields['period'].getSelectedRecord();
                    
                    _currentSearch['periodLevel'] = selectedPeriodRecord.get('level');
                    _currentSearch['periodCode'] = (selectedPeriodRecord.get('code') === 'LTD')?_ltdYear:selectedPeriodRecord.get('code');
                    _currentSearch['periodDesc'] = selectedPeriodRecord.get('description');
                    _currentSearch['asOfDate'] = null;
                    _currentSearch['asOfDateDisp'] = null;
                } else {
                    _currentSearch['periodLevel'] = 'AOD';
                    _currentSearch['periodCode'] = '';
                    _currentSearch['periodDesc'] = '';
                    _currentSearch['asOfDate'] = _resources.fields['asOfDate'].getSMVDateString();
                    _currentSearch['asOfDateDisp'] = _resources.fields['asOfDate'].getDisplayDateString();
                }            
                
                clearNotionalDetails();
                doSearch('reload');
            }
        }
		
		,selectHandler_infoLevel: function (infoLevelSelectedRecord) {
            var searchValid = false;
            
            if (_resources.fields['periodRadio'].checked) {
                searchValid = _resources.fields['period'].isValid();
            } else{
                searchValid = _resources.fields['asOfDate'].isValid();
            }
            
            if (searchValid) {
                if (infoLevelSelectedRecord.get('level') === 'Benef') {
                    _currentSearch['benefId'] = infoLevelSelectedRecord.get('code');
                } else {
                    _currentSearch['benefId'] = 0;
                }
                
                _currentSearch['infoLevelDesc'] = infoLevelSelectedRecord.get('description');
				
                clearNotionalDetails();
                doSearch('reload');
			}
		}
        
        ,clickHandle_searchBreakdownBtn: function () {
            _currentSearch['startDate'] = _resources.popups['notlDetls'].getField('startDate').getSMVDateString();
            _currentSearch['endDate'] = _resources.popups['notlDetls'].getField('endDate').getSMVDateString();
            _currentSearch['nextBreakdownRecNum'] = 1;
            _currentSearch['requestBreakdownRecNum'] = _requestBreakdownRecNum;
            
            clearNotionalBreakdown();
            
            doBreakdownSearch('reload', false);
        }
        
        ,setNotlDetlBalance: function (groupType, notlGroup, notlType) {
            var notlDetlNode = null;
			
            if (groupType === "Contribution") {
                notlDetlNode = IFDS.Xml.getNode(_notlInfoXML, "//NotlInfoGrp[grpType='" + groupType + "']/NotlDetls/NotlDetl[notlGroup='" + notlGroup + "' and notlType='" + notlType + "']");

                if (notlDetlNode !== null) {
                    _resources.popups['notlDetls'].getField('contribReceived').setText(IFDS.Xml.getNodeValue(notlDetlNode, "received")); 
                    _resources.popups['notlDetls'].getField('contribPaidOut').setText(IFDS.Xml.getNodeValue(notlDetlNode, "paidOut")); 
                    _resources.popups['notlDetls'].getField('contribAdjusted').setText(IFDS.Xml.getNodeValue(notlDetlNode, "adjusted")); 
                    _resources.popups['notlDetls'].getField('contribBalance').setText(IFDS.Xml.getNodeValue(notlDetlNode, "balance")); 
                    Ext.getCmp('notlDetlBucketPanel').setTitle(IFDS.Xml.getNodeValue(notlDetlNode, "description"));
                }
                
                Ext.getCmp('contribBucketPanel').show();
            } else {
                var panelTitle = "";
                if (notlGroup === _NOTIONALGROUP_CLB) {
                    notlDetlNode = IFDS.Xml.getNode(_notlInfoXML, "//NotlInfoGrp[grpType='" + groupType + "']/NotlDetls/NotlDetl[notlGroup='" + notlGroup + "' and notlType='" + notlType + "']");
                    panelTitle = IFDS.Xml.getNodeValue(notlDetlNode, "description");
                } else {
                    notlDetlNode = IFDS.Xml.getNode(_notlInfoXML, "//NotlInfoGrp[grpType='" + groupType + "']/NotlDetls/NotlDetl/GrantDetls/GrantDetl[notlGroup='" + notlGroup + "' and notlType='" + notlType + "']");
                    if (notlGroup === _NOTIONALGROUP_QESI
						|| notlGroup === _NOTIONALGROUP_SAGES
						|| notlGroup === _NOTIONALGROUP_BCTESG) {
                        panelTitle = IFDS.Xml.getNodeValue(notlDetlNode, "description");
                    } else if (notlGroup === _NOTIONALGROUP_CESG){
						if (notlType === _NOTIONALTYPE_ADCESG) {
							panelTitle = IFDS.Xml.getNodeValue(notlDetlNode, "description") + " " + IFDS.Xml.getNodeValue(notlDetlNode, "../../description");
						} else {
							panelTitle = IFDS.Xml.getNodeValue(notlDetlNode, "../../description") + " " + IFDS.Xml.getNodeValue(notlDetlNode, "description");
						}
					} else {
                        panelTitle = IFDS.Xml.getNodeValue(notlDetlNode, "../../description") + " " + IFDS.Xml.getNodeValue(notlDetlNode, "description");
                    }
                }
                
                if (notlDetlNode !== null) {
                    _resources.popups['notlDetls'].getField('grantReceived').setText(IFDS.Xml.getNodeValue(notlDetlNode, "received")); 
                    _resources.popups['notlDetls'].getField('grantPaidOut').setText(IFDS.Xml.getNodeValue(notlDetlNode, "paidOut")); 
                    _resources.popups['notlDetls'].getField('grantAdjusted').setText(IFDS.Xml.getNodeValue(notlDetlNode, "adjusted")); 
                    _resources.popups['notlDetls'].getField('grantReturned').setText(IFDS.Xml.getNodeValue(notlDetlNode, "returned")); 
                    _resources.popups['notlDetls'].getField('grantBalance').setText(IFDS.Xml.getNodeValue(notlDetlNode, "balance")); 
                    _resources.popups['notlDetls'].getField('grantPendClawBack').setText(IFDS.Xml.getNodeValue(notlDetlNode, "amtToReturn")); 
                    Ext.getCmp('notlDetlBucketPanel').setTitle(panelTitle);
                }

                Ext.getCmp('grantBucketPanel').show();
            }
        }
        
        ,getCurrentSearch: function () {
            return _currentSearch;
        }
        
        ,clickHandle_ActivityBtn: function () {
            goToScreen('RESPNotionalActivity');
        }
        
        ,clickHandle_AdjustmentBtn: function () {
            openAdjustmentPopup();
        }
        
        ,clickHandle_moreBtn: function () {
            doBreakdownSearch('reload', true);
        }
        
        ,loadEligibleAdjustment: function (runMode) {
            doLoadEligibleAdjustment(runMode);
        }
        
        ,selectNotlDetlRecord: function (record, index) {
            _resources.grids['notlDetls'].enableButton('adminBtn');
        }
        
        ,openBreakdownAdminPopup: function (record) {
            var adminData = {};
            adminData['userName'] = record.get('userName');
            adminData['procDate'] = record.get('processDate');
            adminData['modUser'] = record.get('modUser');
            adminData['modDate'] = record.get('modDate');
            
            _resources.popups['breakdownAdmin'].init(adminData);
            _resources.popups['breakdownAdmin'].show();            
        }
        
        ,doAdjustmentUpdate: function () {
            var requestXML = buildAdjustmentUpdateXML();
            
            DesktopWeb.Ajax.doSmartviewAjax(_notlAdjUpdView, 
                                            null, 
                                            requestXML, 
                                            responseHandler, 
                                            _translationMap['ProcMsg_Searching'])
            
            function responseHandler(success, responseXML) {
                if (success) {
                    _resources.popups['adjustPopup'].hide();
                    clearNotionalDetails();
                    doSearch('reload');
                }
            }
        }
        
        ,selectHandle_Adjust_notlType: function (val) {
            var adjustContainer = Ext.getCmp('adjustmentContainer');
            var notlTypeGrps = adjustContainer.items;
            for (i = 0; i < notlTypeGrps.items.length; i++) {
                if (val === 'ALL') {
                    notlTypeGrps.items[i].show();
                    notlTypeGrps.items[i].expand();
                } else {
                    if (val !== notlTypeGrps.items[i].id) {
                        notlTypeGrps.items[i].hide();
                        notlTypeGrps.items[i].collapse();
                    }else{
                        notlTypeGrps.items[i].show();
                        notlTypeGrps.items[i].expand();
                    }
                }
            }
        }
        
        ,selectHandler_Adjust_infoLevel: function (record) {
            var adjPopup = _resources.popups['adjustPopup'];
            if (adjPopup.isDirty()) {
                DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
            }else{
                handlePromptMsg(true);
            }
            
            function handlePromptMsg(confirm) {
                if (confirm) {
                    doLoadEligibleAdjustment('reload');
                } else {
                    adjPopup.getField('infoLevel').setValue(_currentAdjSearch['benefId']);
                }
            }
        }
        
        ,changeHandler_Adjust_deff: function (fld, newVal, oldVal) {
            var adjPopup = _resources.popups['adjustPopup'];
            if (adjPopup.isDirty()) {
                DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
            }else{
                handlePromptMsg(true);
            }
            
            function handlePromptMsg(confirm) {
                if (confirm) {
                    doLoadEligibleAdjustment('reload');
                } else {
                    adjPopup.getField('deff').setValue(oldVal);
                }
            }
        }
		
		,doAdjustmentValidateByNotlType: function (adjObj) {
			var requestXML = buildAdjustmentValidateXMLByNotlType(adjObj.notlGrp, adjObj.notlType, adjObj.bucketType, adjObj.getAdjustment());
            adjObj.isValidAdjustment = true;
            DesktopWeb.Ajax.doSmartviewAjax(_notlAdjUpdView, 
                                            null, 
                                            requestXML, 
                                            responseHandler, 
                                            _translationMap['ProcMsg_Searching'])
            
            function responseHandler(success, responseXML, errors, warnings) {
				if (errors.length > 0) {
					var errMsg = IFDS.Xml.getNodeValue(errors[0], 'text');
					for (var i = 1; i < errors.length; i++)
					{
						errMsg += "<br/><br/>" + IFDS.Xml.getNodeValue(errors[i], 'text')
					}						
					adjObj.isValidAdjustment = false;
					adjObj.setNotification(errMsg, 'error');
				}else if (warnings.length > 0) {
					var warningMsg = IFDS.Xml.getNodeValue(warnings[0], 'text');
					for (var i = 1; i < warnings.length; i++)
					{
						warningMsg += "<br/><br/>" + IFDS.Xml.getNodeValue(warnings[i], 'text')
					}						
					adjObj.isValidAdjustment = true;
					adjObj.setNotification(warningMsg, 'warning');
				}
            }
		}
    }    
}    