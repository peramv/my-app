/*********************************************************************************************
 * @file    TransferAccounts.Controller.js
 * @author  Mongkonrat, Aurkarn
 * @desc    Controller JS file Transfer of Accounts screen.
 *********************************************************************************************/
/*
 * Procedure: TransferAccounts.Controller.js
 *
 * Purpose  : Controller for Transfer of Accounts screen
 *
 * Notes    :
 *
 * History  :
 *
 *    22 Mar 2015 A. Mongkonrat P0246257 T82356 Dealer Service Bulk Transfer
 *        - Created
 */

DesktopWeb.ScreenController = function() {
    var _translationMap     = DesktopWeb.Translation.getTranslationMap();
    var _self               = null;
    var _resources          = null;
    var _nextStartRecNum    = null;
    var _numOfRecords       = 25;
    var _permissionsMap     = [];
    var _defaultValues      = [];
    var _bulkTrfUUIDCounter = 0;

    var _INQPERM            = "inqPerm"
    var _ADDPERM            = "addPerm";
    var _DELPERM            = "delPerm";
    var _MODPERM            = "modPerm";
    var _ADD                = "Add";
    var _MOD                = "Mod";
    var _VIEW               = "view";
    var _APPROVE            = "Apv";
    var _REJECT             = "Rej";
    var _REVERSE            = "Rev";
    var _NOMINEE            = "2"
    var _INTERMEDIARY       = "3"
    var _ALL                = "@"
    var _bulkTrfXML         = null;
    var _bulkTrfInitXML     = null;
    var _bulkTrfDetlXML     = null;
    var _trfStatPendingReversal = "PERV";
    var _trfStatProcessingReversal = "PRRV";
    var _trfStatTrfReversed = "TRRV";

    var _RUNMODE_INIT       = "init";
    var _RUNMODE_RELOAD     = "reload";
    var _RUNMODE_DETAIL     = "detail";
    var _RUNMODE_PRINT      = "print";

    var _dtBulkTransferInq  = "dtBulkTransferInq";
    var _dtBulkTransferProc = "dtBulkTransferProc";
	var _dtHistoryService   = "dtHistoricalInfo";

    /** Store user permission **/
    function storePermissions(initViewXML) {
        _permissionsMap[_self.INQPERM] = IFDS.Xml.getNodeValue(initViewXML, 
                                                               '//Permissions/inqPerm').toLowerCase() == 'yes';
        _permissionsMap[_self.ADDPERM] = IFDS.Xml.getNodeValue(initViewXML, 
                                                               '//Permissions/addPerm').toLowerCase() == 'yes';
        _permissionsMap[_self.MODPERM] = IFDS.Xml.getNodeValue(initViewXML, 
                                                               '//Permissions/modPerm').toLowerCase() == 'yes';
        _permissionsMap[_self.DELPERM] = IFDS.Xml.getNodeValue(initViewXML, 
                                                               '//Permissions/delPerm').toLowerCase() == 'yes';
    }

    /** Load All Dropdown Lists **/
    function populateDropdownList() {
        if (_bulkTrfInitXML) {
            _resources.fields['statusSrch'].loadData(IFDS.Xml.getNode(_bulkTrfInitXML, 
                                                                      "//List[@listName = 'BulkTrfStatus']"));
        }
    }

    function getDefaultValue(tagName) {
        var defaultValuesNode = IFDS.Xml.getNode(_bulkTrfInitXML, "//DefaultValues");
        var value = "";

		if (defaultValuesNode) {
			value = IFDS.Xml.getNodeValue(defaultValuesNode, tagName);
		}

        return value;
    }

    function loadDefaultValues() {
        _resources.fields['statusSrch'].setValue(getDefaultValue('bulkTrfStatus'));
        _resources.fields['startDateSrch'].setValue(DesktopWeb.Util.getDateDisplayValue(getDefaultValue('startDate')));
        _resources.fields['endDateSrch'].setValue(DesktopWeb.Util.getDateDisplayValue(getDefaultValue('toDate')));

        if (getDefaultValue('allowBranch').toLowerCase() == 'yes') {
            _resources.fields['fromBranchSrch'].enable();
            _resources.fields['toBranchSrch'].enable();
        }
        else {
            _resources.fields['fromBranchSrch'].disable();
            _resources.fields['toBranchSrch'].disable();
        }
    }

    function getListDisplay(listName, value) {
		var valueDesc = null;
        valueDesc = IFDS.Xml.getNodeValue(_bulkTrfInitXML, 
                                        "//List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");

        return valueDesc;
	}
    
    function disableScreen() {
        _resources.buttons['cmdSearch'].disable();
        _resources.fields['reqIdSrch'].disable();
        _resources.fields['statusSrch'].disable();
        _resources.fields['startDateSrch'].disable();
        _resources.fields['endDateSrch'].disable();
	    _resources.fields['fromBrokerSrch'].disable();
        _resources.fields['fromBranchSrch'].disable();
        _resources.fields['fromSlsRepSrch'].disable();
	    _resources.fields['toBrokerSrch'].disable();
        _resources.fields['toBranchSrch'].disable();
        _resources.fields['toSlsRepSrch'].disable();
        
        _resources.grids['bulkTransfer'].disable();
        _resources.grids['bulkTrfActions'].disable();
    }

    function doSearch(getMore) {
        var dataXML = IFDS.Xml.newDocument('data');
        var startRecNum = _nextStartRecNum;

        IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_RELOAD);
        IFDS.Xml.addSingleNode(dataXML, 'startRecNum', getMore ? startRecNum:1);
        IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _numOfRecords);

        IFDS.Xml.addSingleNode(dataXML, 'bulkTrfNum', _resources.fields['reqIdSrch'].getValue());
        IFDS.Xml.addSingleNode(dataXML, 'startDate', 
                        DesktopWeb.Util.getSMVDateValue(_resources.fields['startDateSrch'].getDisplayDateString()));
        IFDS.Xml.addSingleNode(dataXML, 'endDate', 
                        DesktopWeb.Util.getSMVDateValue(_resources.fields['endDateSrch'].getDisplayDateString()));
        IFDS.Xml.addSingleNode(dataXML, 'frAgencyCode', _resources.fields['fromBrokerSrch'].getValue());
        IFDS.Xml.addSingleNode(dataXML, 'frBranchCode', _resources.fields['fromBranchSrch'].getValue());
        IFDS.Xml.addSingleNode(dataXML, 'frAgentCode', _resources.fields['fromSlsRepSrch'].getValue());
        IFDS.Xml.addSingleNode(dataXML, 'toAgencyCode', _resources.fields['toBrokerSrch'].getValue());
        IFDS.Xml.addSingleNode(dataXML, 'toBranchCode', _resources.fields['toBranchSrch'].getValue());
        IFDS.Xml.addSingleNode(dataXML, 'toAgentCode', _resources.fields['toSlsRepSrch'].getValue());
        IFDS.Xml.addSingleNode(dataXML, 'BulkTrfStatus', _resources.fields['statusSrch'].getValue());

        DesktopWeb.Ajax.doSmartviewAjax(_dtBulkTransferInq, null, dataXML, responseHandler, 
                                        _translationMap['ProcMsg_Searching'])

        function responseHandler(success, responseXML)
        {
            if (success) {
                if (!getMore) {
                    _bulkTrfXML = IFDS.Xml.cloneDocument(responseXML);
                }
                else {
                    var oldNodes = IFDS.Xml.getNode(_bulkTrfXML, "//BulkTransferList");
                    var newNodes = IFDS.Xml.getNode(responseXML, "//BulkTransferList");

                    Ext.each(newNodes, function (newBulkNode) {
                        IFDS.Xml.appendNode(oldNodes, IFDS.Xml.cloneDocument(newBulkNode));
                    });
                }

                _nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);

                if (_nextStartRecNum) {
                    _resources.grids['bulkTransfer'].enableButton('moreBtn');
                }
                else {
                    _resources.grids['bulkTransfer'].disableButton('moreBtn');
                }

                if (!getMore) {
                    _resources.grids['bulkTransfer'].loadData(IFDS.Xml.getNode(responseXML, "//BulkTransferList"));
                    _resources.grids['bulkTransfer'].getSelectionModel().selectFirstRow();
                }else {
                    _resources.grids['bulkTransfer'].appendData(IFDS.Xml.getNode(responseXML,"//BulkTransferList"));
                    _resources.grids['bulkTransfer'].getSelectionModel().selectLastRow();
                }
            }else {
                _resources.grids['bulkTransfer'].disableButton('modBtn');
                _resources.grids['bulkTransfer'].disableButton('adminBtn');
                _resources.grids['bulkTransfer'].disableButton('historicalBtn');
                _resources.grids['bulkTransfer'].disableButton('viewBtn');
                _resources.grids['bulkTransfer'].disableButton('approveBtn');
                _resources.grids['bulkTransfer'].disableButton('rejectBtn');
                _resources.grids['bulkTransfer'].disableButton('reverseBtn');
                _resources.grids['bulkTransfer'].disableButton('moreBtn');

                _resources.grids['bulkTransfer'].clearData();
                _resources.grids['bulkTrfActions'].clearData();

                if (_permissionsMap[_self.ADDPERM]) {
                    _resources.grids['bulkTransfer'].enableButton('addBtn');
                }
            }
        }
    }

    
    return {
         ADD                : _ADD
        ,MOD                : _MOD
        ,VIEW               : _VIEW
        ,APPROVE            : _APPROVE
        ,REJECT             : _REJECT
        ,REVERSE            : _REVERSE
        ,NOMINEE            : _NOMINEE
        ,INTERMEDIARY       : _INTERMEDIARY
        ,ALL                : _ALL
        ,TRF_STAT_PENDING_REVERSAL : _trfStatPendingReversal
        ,TRF_STAT_PROCESSING_REVERSAL : _trfStatProcessingReversal
        ,TRF_STAT_TRANSFER_REVERSED : _trfStatTrfReversed

        ,init: function(res) {
            _resources = res;
            _self = DesktopWeb._SCREEN_CONTROLLER;

            /** TODO INIT **/
            _resources.grids['bulkTransfer'].disableButton('addBtn');
            _resources.grids['bulkTransfer'].disableButton('modBtn');
            _resources.grids['bulkTransfer'].disableButton('adminBtn');
            _resources.grids['bulkTransfer'].disableButton('historicalBtn');
            _resources.grids['bulkTransfer'].disableButton('viewBtn');
            _resources.grids['bulkTransfer'].disableButton('approveBtn');
            _resources.grids['bulkTransfer'].disableButton('rejectBtn');
            _resources.grids['bulkTransfer'].disableButton('reverseBtn');
            _resources.grids['bulkTransfer'].disableButton('moreBtn');
            _resources.buttons['cmdSearch'].disable();

            var dataXML = IFDS.Xml.newDocument('data');
            IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_INIT);

            DesktopWeb.Ajax.doSmartviewAjax(_dtBulkTransferInq, null, dataXML, responseHandler, 
                                                                               _translationMap['ProcMsg_Searching'])

            function responseHandler(success, responseXML) {
                if (success) {
                    _bulkTrfInitXML = IFDS.Xml.cloneDocument(responseXML);
                    storePermissions(responseXML);
                    populateDropdownList();
                    loadDefaultValues();

                    if (_permissionsMap[_self.ADDPERM]) {
                        _resources.grids['bulkTransfer'].enableButton('addBtn');
                    }

                    _resources.buttons['cmdSearch'].enable();
                }else {
                    disableScreen();
                }
            }
        }

        ,doValidateSearch: function() {
            return true;
        }

        ,doSearch: function(getMore) {
            doSearch(getMore);
        }

        ,selectBulkTransfer: function(record) {
            var bulkTrfActionsXML = IFDS.Xml.getNode(_bulkTrfXML, 
                                                     "//BulkTransferList/BulkTransferInfo[bulkTransferUUID='" + 
                                                     record.data['bulkTransferUUID'] + "']/BulkTransferActionList");

            if (_permissionsMap[_self._MODPERM]) {
                _resources.grids['bulkTransfer'].enableButton('modBtn');
            }else {
                _resources.grids['bulkTransfer'].disableButton('modBtn');
            }
            
            _resources.grids['bulkTransfer'].enableButton('approveBtn');
            _resources.grids['bulkTransfer'].enableButton('rejectBtn');
            _resources.grids['bulkTransfer'].enableButton('reverseBtn');
            _resources.grids['bulkTransfer'].enableButton('adminBtn');
            _resources.grids['bulkTransfer'].enableButton('historicalBtn');
            _resources.grids['bulkTransfer'].enableButton('viewBtn');

            _resources.grids['bulkTrfActions'].clearData();
            _resources.grids['bulkTrfActions'].loadData(bulkTrfActionsXML);
        }

        ,openBulkTsfDetails: function(selectedUUID) {
            var popupDetl = _resources.popups['bulkTransferDetls'];
            var dataXML = IFDS.Xml.newDocument('data');

            IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_DETAIL);
            IFDS.Xml.addSingleNode(dataXML, 'bulkTransferUUID', selectedUUID);

            DesktopWeb.Ajax.doSmartviewAjax(_dtBulkTransferInq, null, dataXML, responseHandler,
                                                                               _translationMap['ProcMsg_Searching']);

            function responseHandler(success, responseXML) {
                if (success) {
                    _bulkTrfDetlXML = IFDS.Xml.cloneDocument(responseXML);
                    popupDetl.init();
                    popupDetl.show();
                }else {
                }
            }
        }

        ,getBulkTrfDetlValue: function(tag) {
            return IFDS.Xml.getNodeValue(_bulkTrfDetlXML, '//BulkTransferList/BulkTransferInfo/' + tag);
        }

        ,openBulkTsfMaintUpdate: function(mode, uuid) {
            var popup = _resources.popups['bulkTransferMaint'];
            var dataXML = IFDS.Xml.newDocument('data');

            IFDS.Xml.addSingleNode(dataXML, 'runMode', _RUNMODE_DETAIL);
            IFDS.Xml.addSingleNode(dataXML, 'bulkTransferUUID', uuid);

            DesktopWeb.Ajax.doSmartviewAjax(_dtBulkTransferInq, null, dataXML, responseHandler, 
                                                                                  _translationMap['ProcMsg_Searching']);

            function responseHandler(success, responseXML) {
                if (success) {
                    _bulkTrfDetlXML = IFDS.Xml.cloneDocument(responseXML);
                    popup.getField('blockTrfType').loadData(
                                            IFDS.Xml.getNode(_bulkTrfInitXML, "//List[@listName = 'BlockTrfType']"));
                    popup.getField('acctDesignation').loadData(
                                            IFDS.Xml.getNode(_bulkTrfInitXML, "//List[@listName = 'AcctDesignation']"));

                    popup.init(mode);
                    popup.show();
                }else {
                }
            }
        }

        ,openBulkTsfMaintAdd: function() {
            var popup = _resources.popups['bulkTransferMaint'];
            var dataXML = IFDS.Xml.newDocument('data');

            popup.getField('blockTrfType').loadData(
                                            IFDS.Xml.getNode(_bulkTrfInitXML, "//List[@listName = 'BlockTrfType']"));
            popup.getField('acctDesignation').loadData(
                                            IFDS.Xml.getNode(_bulkTrfInitXML, "//List[@listName = 'AcctDesignation']"));

            popup.init(_ADD);
            popup.show();
        }

        ,openHistoryPopup: function() {
            var viewParam = {};
            var historyName = null;
            var selectedRecord = _resources.grids['bulkTransfer'].getSelectedRecord();

            if (selectedRecord && selectedRecord != undefined) {
                historyName = _translationMap['BulkTrferMaint'] + ' - ' + _translationMap['History'];

                viewParam['searchValue1'] = selectedRecord.data['bulkTransferUUID'];
                viewParam['auditType'] = 'BulkTransfer';

                _resources.popups['history'].init(historyName, _dtHistoryService, viewParam, true);
                _resources.popups['history'].show();
            }
        }

        ,openAdminPopup: function() {
            var title = null;
            var xml = null;

            title = _translationMap['BulkTrferMaint'] + ' - ' + _translationMap['Admin'];
            xml = _resources.grids['bulkTransfer'].getSelectedRecord();

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

        ,getListDisplay: function(listName, value) {
            return getListDisplay(listName, value);
        }

        ,getDefaultValue: function(tagName) {
            return getDefaultValue(tagName);
        }

        ,clickHandle_printBtn: function(data) {
            DesktopWeb.Util.displayYesNo(_translationMap['UserConfirm1'] + 
                                         _translationMap['Print'].toLowerCase() + 
                                         _translationMap['UserConfirm2'], confirmHandler);

			function confirmHandler(btn)
			{
                if (btn != 'yes')
                {
                    return;
                }

                var printNode = IFDS.Xml.newDocument('data');

                for (var tag in data) {
                    if (tag != "bulkTrfAction")
                        IFDS.Xml.addSingleNode(printNode, tag, data[tag]);
                }

                IFDS.Xml.addSingleNode(printNode, 'bulkTrfAction', _RUNMODE_PRINT);
                DesktopWeb.Ajax.doSmartviewAjax(_dtBulkTransferProc, null, printNode, responseHandler, 
                                                                                      _translationMap['Processing']);

                function responseHandler(success, responseXML, contextErrors) {

                    if (success)
                    {
                        DesktopWeb.Util.displayInfo(_translationMap['AUM_Requested']);
                    }
                    else
                    {
                    }
                }
            }
        }

        ,clickHandle_okBtnOnBulkTrfDetlsPopup: function(action, data) {
            _resources.popups['bulkTransferDetls'].hide();
        }

        ,clickHandle_okBtnOnBulkTrfMaintPopup: function(action, data) {
            var bulkTfrNode = IFDS.Xml.newDocument('data');

            for (var tag in data) {
                IFDS.Xml.addSingleNode(bulkTfrNode, tag, data[tag]);
            }

            DesktopWeb.Ajax.doSmartviewAjax(_dtBulkTransferProc, null, bulkTfrNode, responseHandler, 
                                                                                    _translationMap['Processing']);

            function responseHandler(success, responseXML, contextErrors)
            {
                if (success)
                {
                    _resources.popups['bulkTransferMaint'].hide();
                    doSearch(false);
                }
                else
                {
                }
            }
        }

        ,getNextBulkTransferUUID: function() {
            return _bulkTrfUUIDCounter++;
        }
    }
}