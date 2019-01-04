/*********************************************************************************************
 * @file    TransferAccounts.Resources.js
 * @author  Mongkonrat, Aurkarn
 * @desc    Resources JS file Transfer of Accounts screen.
 *********************************************************************************************/
/*
 * Procedure: TransferAccounts.Resources.js
 *
 * Purpose  : Resources for Transfer of Accounts screen
 *
 * Notes    :
 *
 * History  :
 *
 *    22 Mar 2015 A. Mongkonrat P0246257 T82356 Dealer Service Bulk Transfer
 *        - Created
 *        
 *    31 May 2016 N. Hatthaseriphong P0246257 T82943 
 *    DFT0063831 DFT0063832 DFT0064015 Dealer Service Bulk Transfer
 *        - Changed a position and renamed Print button to AUM Report.
 *        - Add effective date validation to check it must be the current date.
 *        - Remove all To section required validation in Print action.
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();

    // content dimensions
    var _layoutHeight = 600;  //615
    var _layoutWidth = 750;

    var _bbrSrchFieldWidth = 125;

    // **** buttons ****
    var _buttons = {
        cmdSearch: new DesktopWeb.Controls.ActionButton({
            text: _translationMap['Search']
            ,style: "position:relative; left:130px; top:0px;"
            , handler: function() {
                if (_controller.doValidateSearch())
                    _controller.doSearch(false);}
        })
    }

    // **** fields ****
    var _fields = {
        reqIdSrch: new DesktopWeb.Controls.NumberField({
            itemId: 'reqIdSrch'
            ,allowDecimals: false
			,allowNegative: false
            ,fieldLabel: _translationMap['BulkTrferID']
            ,width: 100
        })
        ,awdBatchIDSrch: new DesktopWeb.Controls.TextField({
            itemId: 'awdBatchIDSrch'
            ,fieldLabel: _translationMap['AWDBatchID']
            ,width: 100
        })
        ,statusSrch: new DesktopWeb.Controls.SMVComboBox({
            itemId: 'statusSrch'
            ,fieldLabel: _translationMap['Status']
            ,labelSeparator: ':<br/><br/>'
            ,editable: false
            ,width: 160
        })
        ,startDateSrch: new DesktopWeb.Controls.DateField({
            itemId: 'startDateSrch'
            ,fieldLabel: _translationMap['StartDate']
            ,width: 100
            ,allowBlank: true
            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
        })
        ,endDateSrch: new DesktopWeb.Controls.DateField({
            itemId: 'endDateSrch'
            ,fieldLabel: _translationMap['EndDate']
            ,width: 100
            ,allowBlank: true
            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
        })
        ,fromBrokerSrch: new DesktopWeb.Controls.SuggestField({
            itemId: 'fromBrokerSrch'
            ,fieldLabel: _translationMap['Broker']
            , style: 'padding-left:5px;'
            , width: _bbrSrchFieldWidth
            , smartview: 'brokerSearch'
            , addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'yes';}}]
            , fields: ['displayValue', 'agencyCode', 'brokerDesc' ]
            , valueField: 'agencyCode'
            , allowBlank: true
        })
        ,fromBranchSrch: new DesktopWeb.Controls.SuggestField({
            itemId: 'fromBranchSrch'
            ,fieldLabel: _translationMap['Branch']
            ,style: 'padding-left:5px;'
            ,width: _bbrSrchFieldWidth
            ,smartview: 'branchSearch'
            ,fields: ['displayValue', 'agencyCode', 'branch', 'matchType']
            ,forceSelection: false
            ,addtlSearchParams: [
                {name: 'agencyCode', valueFn: function() { return _fields['fromBrokerSrch'].getValue(); }}
                ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
              ]
            , valueField: 'branch'
        })
        ,fromSlsRepSrch: new DesktopWeb.Controls.SuggestField({
            itemId: 'fromSlsRepSrch'
            ,fieldLabel: _translationMap['SalesRep']
            ,style: 'padding-left:5px;'
            ,width: _bbrSrchFieldWidth
            ,smartview: 'salesRepSearch'
            ,fields: ['displayValue', 'agentCode', 'branch', 'saleRespDesc']
            ,forceSelection: false
            ,addtlSearchParams: [
                {name: 'agencyCode', valueFn: function() { return _fields['fromBrokerSrch'].getValue(); }}
                ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
            ]
            ,valueField: 'agentCode'
        })
        ,toBrokerSrch: new DesktopWeb.Controls.SuggestField({
            itemId: 'toBrokerSrch'
            ,fieldLabel: _translationMap['Broker']
            ,style: 'padding-left:5px;'
            ,width: _bbrSrchFieldWidth
            ,smartview: 'brokerSearch'
            ,addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'yes';}}]
            ,fields: ['displayValue', 'agencyCode', 'brokerDesc' ]
            ,valueField: 'agencyCode'
            ,allowBlank: true
        })
        ,toBranchSrch: new DesktopWeb.Controls.SuggestField({
            itemId: 'toBranchSrch'
            ,fieldLabel: _translationMap['Branch']
            ,style: 'padding-left:5px;'
            ,width: _bbrSrchFieldWidth
            ,smartview: 'branchSearch'
            ,fields: ['displayValue', 'agencyCode', 'branch', 'matchType']
            ,forceSelection: false
            ,addtlSearchParams: [
                {name: 'agencyCode', valueFn: function() { return _fields['toBrokerSrch'].getValue(); }}
                ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
              ]
            , valueField: 'branch'
        })
        ,toSlsRepSrch: new DesktopWeb.Controls.SuggestField({
            itemId: 'toSlsRepSrch'
            ,fieldLabel: _translationMap['SalesRep']
            ,style: 'padding-left:5px;'
            ,width: _bbrSrchFieldWidth
            ,smartview: 'salesRepSearch'
            ,fields: ['displayValue', 'agentCode', 'branch', 'saleRespDesc']
            ,forceSelection: false
            ,addtlSearchParams: [
                {name: 'agencyCode', valueFn: function() { return _fields['toBrokerSrch'].getValue(); }}
                ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
            ]
            ,valueField: 'agentCode'
        })
    }

    // **** grids ****
    var _grids = {
        bulkTransfer: new DesktopWeb.AdvancedControls.GridPanel({
            width: _layoutWidth
            ,autoScroll: true
            ,height: 235
            ,buttonAlign : 'left'
            //,autoExpandColumn: 'bulkTrfStatus'
            ,store: new Ext.data.XmlStore({
                record: 'BulkTransferInfo'
                ,fields: ['bulkTransferUUID','bulkTrfNum','awdBatchID','bulkTrfStatus','blockTrfType'
                          ,'effectiveDate','dateOfReversal','acctDesignation','frAgencyCode','frBranchCode'
                          ,'frAgentCode','toAgencyCode','toBranchCode','toAgentCode','toIntr','toIntrID'
                          ,'toNomineeID','userName','processDate','modUser','modDate','version'
                          ,'approvedUser','reversedUser','revApprovedUser','bulkTrfAction'
                ]
                ,listeners: {
                    load: function(store, records)
                    {
                        Ext.each(records, function(record){
								record.data.effectiveDate = DesktopWeb.Util.getDateDisplayValue(
                                                                                            record.data.effectiveDate);
								record.data.dateOfReversal = DesktopWeb.Util.getDateDisplayValue(
                                                                                            record.data.dateOfReversal);
							});

                        store.fireEvent('datachanged', store);
                    }
                }
            })
            ,selModel: new Ext.grid.RowSelectionModel({
                singleSelect: true
                ,listeners: {
                     rowselect: function(selModel, index, record){_controller.selectBulkTransfer(record);}
                }
            })
            ,colModel: new Ext.grid.ColumnModel({
                defaults: {
                    menuDisabled: true
                }
                ,columns: [
                    {header: _translationMap['GRD_BulkTrferID'], id:'reqID', dataIndex: 'bulkTrfNum', width: 90}
                    ,{header: _translationMap['Status'], id:'bulkTrfStatus', dataIndex: 'bulkTrfStatus', width: 135
                        ,renderer: function(val){return (_controller.getListDisplay('BulkTrfStatus', val));}
                    }
                    ,{header: _translationMap['GRD_EffectiveDate'], id:'effectiveDate', dataIndex: 'effectiveDate', 
                                                                                                              width: 68}
                    ,{header: _translationMap['GRD_DateOfReversal'], id:'dateOfReversal', dataIndex: 'dateOfReversal', 
                                                                                                              width: 88}
                    ,{header: _translationMap['GRD_FromBroker'], id:'frAgencyCode', dataIndex: 'frAgencyCode',width: 50}
                    ,{header: _translationMap['GRD_FromSlsRep'], id:'frAgentCode', dataIndex: 'frAgentCode', width: 75}
                    ,{header: _translationMap['GRD_ToBroker'], id:'toAgencyCode', dataIndex: 'toAgencyCode', width: 50}
                    ,{header: _translationMap['GRD_ToSlsRep'], id:'toAgentCode', dataIndex: 'toAgentCode', width: 75}
                    ,{header: _translationMap['GRD_BlockTrferType'], id:'blockTrfType', dataIndex: 'blockTrfType', 
                                                                                                              width: 95}
                    ,{header: _translationMap['GRD_AcctDesign'], id:'acctDesignation', dataIndex: 'acctDesignation', 
                                                                                                              width: 75
                        ,renderer: function(val){return (_controller.getListDisplay('AcctDesignation', val));}
                    }
                ]
            })
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    itemId: 'approveBtn'
                    ,text: _translationMap['Approve']
                    ,handler: function(){
                        _controller.openBulkTsfMaintUpdate(_controller.APPROVE,
                                                   _grids['bulkTransfer'].getSelectedRecord().data['bulkTransferUUID']);
                    }

                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'rejectBtn'
                    ,text: _translationMap['Reject']
                    ,handler: function(){
                        _controller.openBulkTsfMaintUpdate(_controller.REJECT,
                                                   _grids['bulkTransfer'].getSelectedRecord().data['bulkTransferUUID']);
                    }
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'reverseBtn'
                    ,text: _translationMap['Reverse']
                    ,handler: function(){
                        _controller.openBulkTsfMaintUpdate(_controller.REVERSE,
                                                   _grids['bulkTransfer'].getSelectedRecord().data['bulkTransferUUID']);
                    }
                })
                ,'->'
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'addBtn'
                    ,text: _translationMap['Add']
                    ,handler: function(){_controller.openBulkTsfMaintAdd();}
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'modBtn'
                    ,text: _translationMap['Modify']
                    ,handler: function(){
                        _controller.openBulkTsfMaintUpdate(_controller.MOD,
                                                   _grids['bulkTransfer'].getSelectedRecord().data['bulkTransferUUID']);
                    }
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'viewBtn'
                    ,text: _translationMap['View']
                    ,handler: function() {
                        _controller.openBulkTsfDetails(
                                                   _grids['bulkTransfer'].getSelectedRecord().data['bulkTransferUUID']);
                    }
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'adminBtn'
                    ,text: _translationMap['Admin']
                    ,handler: function(){_controller.openAdminPopup();}
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'historicalBtn'
                    ,text:_translationMap['Historical']
                    ,handler: function(){_controller.openHistoryPopup();}
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'moreBtn'
                    ,text: _translationMap['More']
                    ,handler: function(){_controller.doSearch(true);}
                })
            ]
        })
        ,bulkTrfActions: new DesktopWeb.AdvancedControls.GridPanel({
            width: _layoutWidth
            ,autoScroll: true
            ,height: 130
            ,width: _layoutWidth - 12
            ,store: new Ext.data.XmlStore({
                record: 'BulkTransferAction'
                ,fields: ['bulkTrfNum', 'seq','processDate', 'userName', 'action']
                ,listeners: {
                    load: function(store, records)
                    {
                        Ext.each(records, function(record){
							record.data.processDate = DesktopWeb.Util.getDateDisplayValue(record.data.processDate);
						});

                        store.fireEvent('datachanged', store);
                    }
                }
            })
            ,selModel: new Ext.grid.RowSelectionModel({
                singleSelect: true
            })
            ,colModel: new Ext.grid.ColumnModel({
                defaults: {
                    menuDisabled: true
                }
                ,columns: [
                    {header: _translationMap['GRD_Action'], id:'action', dataIndex: 'action', width: 100
                        ,renderer: function(val){return (_controller.getListDisplay('BulkTrfAction', val));}
                    }
                    ,{header: _translationMap['GRD_DateTime'], id:'timestamps', dataIndex: 'processDate', width: 150}
                    ,{header: _translationMap['Username'], id:'userName', dataIndex: 'userName', width: 100}
                ]
            })
            ,buttons: [ ]
        })
    }

    var _popups = {
        bulkTransferMaint: new DesktopWeb.AdvancedControls.PopupWindow({
            width: 425
            ,action: null
            ,bulkTransferUUID: null
            ,bulkTrfStatus: null
            ,version: null
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,buttonAlign: 'left'
            ,items: [
                {
                    html: _translationMap['Warn_Reversal']
                    ,itemId: 'warnHeader'
                    ,style: 'text-align:center;font-weight:bold;color:red;padding:4px;'
                }
                ,{
                    layout: 'form'
                    ,itemId: 'popup_main'
                    ,style: 'padding:4px'
                    ,border:false
                    ,labelWidth: 150
                    ,items: [
                        {
                            layout: 'column'
                            ,border: false
                            ,defaults:{
                                layout: 'form'
                                ,border: false
                            }
                            ,items: [
                                {
                                    columnWidth: 0.50
                                    ,labelWidth: 125
                                    ,items: [
                                        new DesktopWeb.Controls.Label({
                                            itemId: 'bulkTrfNum'
                                            ,fieldLabel: _translationMap['BulkTrferID']
                                        })
                                    ]
                                }
                                ,{
                                    columnWidth: 0.50
                                    ,labelWidth: 45
                                    ,items: [
                                        new DesktopWeb.Controls.Label({
                                            itemId: 'bulkTrfStatusDisp'
                                            ,fieldLabel: _translationMap['Status']
                                        })
                                    ]
                                }
                            ]
                        }
                        ,new DesktopWeb.Controls.TextField({
                            itemId: 'awdBatchID'
                            ,fieldLabel: _translationMap['AWDBatchID']
                            ,width: 120
                            ,allowBlank: true
                        })
                        ,new DesktopWeb.Controls.DateField({
                            itemId: 'effectiveDate'
                            ,fieldLabel: _translationMap['EffectiveDate']
                            ,width : 120
                            ,allowBlank: false
                            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
                        })
                        ,new DesktopWeb.Controls.SMVComboBox({
                            itemId: 'blockTrfType'
                            ,fieldLabel: _translationMap['BlockTrferType']
                            ,width: 220
                            ,editable: false
                            ,allowBlank: false
                        })
                        ,new DesktopWeb.Controls.SMVComboBox({
                            itemId: 'acctDesignation'
                            ,fieldLabel: _translationMap['AcctDesign']
                            ,width: 220
                            ,editable: false
                            ,allowBlank: false
                            ,listeners: {
								select: function(combo, record, index){
                                    _popups['bulkTransferMaint'].applyAcctDesignationChg(record.data.code, true);
                                }
                            }
                        })
                        ,{
                            xtype: 'fieldset'
                            ,title: _translationMap['From']
                            ,labelWidth: 115
                            ,items: [
                                new DesktopWeb.Controls.SuggestField({
                                    itemId: 'frAgencyCode'
                                    ,fieldLabel: _translationMap['Broker']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'brokerSearch'
                                    ,addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'yes';}}]
                                    ,fields: ['displayValue', 'agencyCode', 'brokerDesc' ]
                                    ,valueField: 'agencyCode'
                                    ,allowBlank: false
                                    ,listeners:{
                                        populated: function() {
                                            if (_controller.getDefaultValue('allowBranch').toLowerCase() == 'yes') {
                                                _popups['bulkTransferMaint'].getField('frBranchCode').enable();
                                                _popups['bulkTransferMaint'].getField('frSlsRepCode').disable();
                                            }
                                            else {
                                                _popups['bulkTransferMaint'].getField('frBranchCode').disable();
                                                _popups['bulkTransferMaint'].getField('frSlsRepCode').enable();
                                            }
                                            
                                            
                                        }
                                        ,cleared: function() {
                                             _popups['bulkTransferMaint'].getField('frBranchCode').setValue('');
                                             _popups['bulkTransferMaint'].getField('frBranchCode').disable();
                                             _popups['bulkTransferMaint'].getField('frSlsRepCode').setValue('');
                                             _popups['bulkTransferMaint'].getField('frSlsRepCode').disable();
                                        }
                                    }
                                })
                                ,new DesktopWeb.Controls.SuggestField({
                                    itemId: 'frBranchCode'
                                    ,fieldLabel: _translationMap['Branch']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'branchSearch'
                                    ,fields: ['displayValue', 'branch']
                                    ,forceSelection: false
                                    ,addtlSearchParams: [
                                        {name: 'agencyCode', valueFn: function() { 
                                                return _popups['bulkTransferMaint'].getField('frAgencyCode').getValue();
                                            }
                                        }
                                        ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
                                      ]
                                    ,valueField: 'branch'
                                    ,allowBlank: false
                                    ,disabled: true
                                    ,listeners:{
                                        populated: function() {
                                            if (!_popups['bulkTransferMaint'].getField('frBranchCode').disabled)
                                            {
                                                _popups['bulkTransferMaint'].getField('frSlsRepCode').setValue('');
                                                _popups['bulkTransferMaint'].getField('frSlsRepCode').enable();
                                            }
                                        }
                                        ,cleared: function() {
                                            if (!_popups['bulkTransferMaint'].getField('frBranchCode').disabled)
                                            {
                                                _popups['bulkTransferMaint'].getField('frSlsRepCode').setValue('');
                                                _popups['bulkTransferMaint'].getField('frSlsRepCode').disable();
                                            }
                                        }
                                    }
                                })
                                ,new DesktopWeb.Controls.SuggestField({
                                    itemId: 'frSlsRepCode'
                                    ,fieldLabel: _translationMap['SalesRep']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'salesRepSearch'
                                    ,fields: ['displayValue', 'agentCode']
                                    ,forceSelection: false
                                    ,addtlSearchParams: [
                                        {name: 'agencyCode', valueFn: function() { 
                                                return _popups['bulkTransferMaint'].getField('frAgencyCode').getValue();
                                            }
                                        }
                                        ,{name: 'branch', valueFn: function() { 
                                                return _popups['bulkTransferMaint'].getField('frBranchCode').getValue();
                                            }
                                        }
                                        ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
                                    ]
                                    , valueField: 'agentCode'
                                    ,allowBlank: false
                                    ,listeners: {
                                        change: function()
                                        {
                                            if (this.selectedRecord != null)
                                            {
                                                if (_popups['bulkTransferMaint'].getField('frBranchCode').getValue() 
                                                                                                                  == "")
                                                {
                                                    var branchCode = IFDS.Xml.getNodeValue(this.selectedRecord.node, 
                                                                                           'branch');
                                                    var branchDesc = IFDS.Xml.getNodeValue(this.selectedRecord.node, 
                                                                                           'branchDisplayValue');
                                                    _popups['bulkTransferMaint'].getField('frBranchCode').prepopulate(
                                                                                                branchCode, branchDesc);
                                                }
                                            }
                                        }
                                    }
                                })
                                ,new DesktopWeb.Controls.ActionButton({
                                    itemId: 'printBtn'
                                    ,text: _translationMap['AUMReport']
                                	,style: 'float:right; margin-right:18px;'
                                    ,handler: function(){
                                        if (_popups['bulkTransferMaint'].isPopupValid(true)) {
                                            var allData = _popups['bulkTransferMaint'].getData();
                                            _controller.clickHandle_printBtn(allData);
                                        }
                                    }
                                })
                            ]
                        }
                        ,{
                            xtype: 'fieldset'
                            ,title: _translationMap['To']
                            ,labelWidth: 115
                            ,items: [
                                new DesktopWeb.Controls.SuggestField({
                                    itemId: 'toAgencyCode'
                                    ,fieldLabel: _translationMap['Broker']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'brokerSearch'
                                    ,addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'yes';}}]
                                    ,fields: ['displayValue', 'agencyCode', 'brokerDesc' ]
                                    ,valueField: 'agencyCode'
                                    ,allowBlank: false
                                    ,listeners:{
                                        populated: function() {
                                            if (_controller.getDefaultValue('allowBranch').toLowerCase() == 'yes') {
                                                _popups['bulkTransferMaint'].getField('toBranchCode').enable();
                                                _popups['bulkTransferMaint'].getField('toSlsRepCode').disable();
                                            }
                                            else {
                                                _popups['bulkTransferMaint'].getField('toBranchCode').disable();
                                                _popups['bulkTransferMaint'].getField('toSlsRepCode').enable();
                                            }
                                        }
                                        ,cleared: function() {
                                             _popups['bulkTransferMaint'].getField('toBranchCode').setValue('');
                                             _popups['bulkTransferMaint'].getField('toBranchCode').disable();
                                             _popups['bulkTransferMaint'].getField('toSlsRepCode').setValue('');
                                             _popups['bulkTransferMaint'].getField('toSlsRepCode').disable();
                                        }
                                    }
                                })
                                ,new DesktopWeb.Controls.SuggestField({
                                    itemId: 'toBranchCode'
                                    ,fieldLabel: _translationMap['Branch']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'branchSearch'
                                    ,fields: ['displayValue', 'branch']
                                    ,forceSelection: false
                                    ,addtlSearchParams: [
                                        {name: 'agencyCode', valueFn: function() { 
                                                return _popups['bulkTransferMaint'].getField('toAgencyCode').getValue();
                                            }
                                        }
                                        ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
                                      ]
                                    ,valueField: 'branch'
                                    ,allowBlank: false
                                    ,disabled: true
                                    ,listeners:{
                                        populated: function() {
                                            if (!_popups['bulkTransferMaint'].getField('toBranchCode').disabled)
                                            {
                                                _popups['bulkTransferMaint'].getField('toSlsRepCode').setValue('');
                                                _popups['bulkTransferMaint'].getField('toSlsRepCode').enable();
                                            }
                                        }
                                        ,cleared: function() {
                                            if (!_popups['bulkTransferMaint'].getField('toBranchCode').disabled)
                                            {
                                                _popups['bulkTransferMaint'].getField('toSlsRepCode').setValue('');
                                                _popups['bulkTransferMaint'].getField('toSlsRepCode').disable();
                                            }
                                        }
                                    }
                                })
                                ,new DesktopWeb.Controls.SuggestField({
                                    itemId: 'toSlsRepCode'
                                    ,fieldLabel: _translationMap['SalesRep']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'salesRepSearch'
                                    ,fields: ['displayValue', 'agentCode']
                                    ,forceSelection: false
                                    ,addtlSearchParams: [
                                        {name: 'agencyCode', valueFn: function() { 
                                                return _popups['bulkTransferMaint'].getField('toAgencyCode').getValue();
                                            }
                                        }
                                        ,{name: 'branch', valueFn: function() { 
                                                return _popups['bulkTransferMaint'].getField('toBranchCode').getValue();
                                            }
                                        }
                                        ,{name: 'onlyActive', valueFn: function(){return 'yes';}}
                                    ]
                                    , valueField: 'agentCode'
                                    ,allowBlank: false
                                    ,listeners: {
                                        change: function()
                                        {
                                            if (this.selectedRecord != null)
                                            {
                                                if (_popups['bulkTransferMaint'].getField('toBranchCode').getValue() 
                                                                                                                  == "")
                                                {
                                                    var branchCode = IFDS.Xml.getNodeValue(this.selectedRecord.node, 
                                                                                           'branch');
                                                    var branchDesc = IFDS.Xml.getNodeValue(this.selectedRecord.node, 
                                                                                           'branchDisplayValue');
                                                    _popups['bulkTransferMaint'].getField('toBranchCode').prepopulate(
                                                                                                branchCode, branchDesc);
                                                }
                                            }
                                        }
                                    }
                                })
                                ,new DesktopWeb.Controls.SuggestField({
                                    itemId: 'toNomineeID'
                                    ,fieldLabel: _translationMap['Nominee']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'entitySearch'
                                    ,fields: ['displayValue', 'entityId']
                                    ,forceSelection: false
                                    ,valueField: 'entityId'
                                })
                                ,new DesktopWeb.Controls.SuggestField({
                                    itemId: 'toIntermID'
                                    ,fieldLabel: _translationMap['Intermediary']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'intrSearch'
                                    ,fields: ['displayValue', 'intrCode']
                                    ,forceSelection: false
                                    ,valueField: 'intrCode'
                                })
                                ,new DesktopWeb.Controls.SuggestField({
                                    itemId: 'toIntermEntID'
                                    ,fieldLabel: _translationMap['IntermediaryEntity']
                                    ,style: 'padding-left:5px;'
                                    ,width: 250
                                    ,smartview: 'entitySearch'
                                    ,fields: ['displayValue', 'entityId']
                                    ,forceSelection: false
                                    ,valueField: 'entityId'
                                })
                            ]
                        }
                    ]
                }
            ]
            ,buttons: [
                '->'
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'okBtn'
                    ,text: _translationMap['Save']
                    ,listeners: {
                        click: function(){
                            if (_popups['bulkTransferMaint'].isPopupValid()) {
                                var allData = _popups['bulkTransferMaint'].getData();
                                var userAction = '';

                                if (allData['bulkTrfAction'] == _controller.ADD)
                                    userAction = _translationMap['Create'];
                                else if (allData['bulkTrfAction'] == _controller.MOD)
                                    userAction = _translationMap['Modify'];
                                else if (allData['bulkTrfAction'] == _controller.REJECT)
                                    userAction = _translationMap['Reject'];
                                else if (allData['bulkTrfAction'] == _controller.REVERSE)
                                    userAction = _translationMap['Reverse'];
                                else if (allData['bulkTrfAction'] == _controller.APPROVE)
                                    userAction = _translationMap['Approve'];

                                DesktopWeb.Util.displayYesNo(_translationMap['UserConfirm1'] + 
                                                             userAction.toLowerCase() + 
                                                             _translationMap['UserConfirm2'], callback);
                                                             
                                function callback(button) {
                                    if (button == 'yes') {
                                        _controller.clickHandle_okBtnOnBulkTrfMaintPopup(
                                                                          _popups['bulkTransferMaint'].action, allData);
                                    }
                                }
                            }
                        }
                    }
                })
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'cancelBtn'
                    ,text: _translationMap['Cancel']
                    ,handler: function(){_popups['bulkTransferMaint'].hide();}
                })
            ]
            ,init: function(action) //Matainance
            {
                this.action = action;
                this.resetAllFields();

                var vTitle = _translationMap['BulkTrferMaint'];
                var popup = _popups['bulkTransferMaint'];

                switch(action)
                {
                    case _controller.ADD:
                    {
                        this.setTitle(vTitle + ' - ' + _translationMap['Add']);
                        popup.bulkTrfStatus = _controller.getDefaultValue('newBulkTrfStatus');
                        popup.bulkTransferUUID = 'BulkTransferUUID' + _controller.getNextBulkTransferUUID();
                        popup.version = 1;
                        popup.getField('blockTrfType').setValue(_controller.getDefaultValue('blockTrfType'));
                        popup.getField('effectiveDate').setValue(DesktopWeb.Util.getDateDisplayValue(
                                                                           _controller.getDefaultValue('defaultDate')));
                        popup.getFooterToolbar().get('okBtn').setText(_translationMap['Create']);

                        this.setAllReadOnly(false);
                        this.populate(action);
                        break;
                    }
                    case _controller.MOD:
                    {
                        this.setTitle(vTitle + ' - ' + _translationMap['Modify']);
                        popup.getFooterToolbar().get('okBtn').setText(_translationMap['Save']);
                        
                        this.loadDataFromGrd();
                        this.setAllReadOnly(false);
                        this.populate(action);

                        break;
                    }
                    case _controller.APPROVE:
                    {
                        this.setTitle(vTitle + ' - ' + _translationMap['Approve']);
                        popup.getFooterToolbar().get('okBtn').setText(_translationMap['Approve']);
                        
                        this.loadDataFromGrd();
                        this.setAllReadOnly(true);
                        this.populate(action);
                        break;
                    }
                    case _controller.REJECT:
                    {
                        this.setTitle(vTitle + ' - ' + _translationMap['Reject']);
                        popup.getFooterToolbar().get('okBtn').setText(_translationMap['Reject']);

                        this.loadDataFromGrd();
                        this.setAllReadOnly(true);
                        this.populate(action);
                        break;
                    }
                    case _controller.REVERSE:
                    {
                        this.setTitle(vTitle + ' - ' + _translationMap['Reverse']);
                        popup.getFooterToolbar().get('okBtn').setText(_translationMap['Reverse']);

                        this.loadDataFromGrd();
                        this.setAllReadOnly(true);
                        this.populate(action);
                        break;
                    }
                }

            }
            ,populate: function(action) //Matainance
            {
                var popup = _popups['bulkTransferMaint'];
                popup.getField('warnHeader').hide();

                switch (action)
                {
                    case _controller.ADD:
                    {
                        popup.getField('bulkTrfNum').hide();
                        popup.getField('bulkTrfStatusDisp').hide();
                        popup.getField('frBranchCode').disable();
                        popup.getField('frSlsRepCode').disable();
                        popup.getField('toBranchCode').disable();
                        popup.getField('toSlsRepCode').disable();

                        this.displayWarnReversal(action);
                        this.commonDisplayControls();

                        break;
                    }
                    case _controller.MOD:
                    {
                        popup.getField('bulkTrfNum').show();
                        popup.getField('bulkTrfStatusDisp').show();
                        
                        this.displayWarnReversal(action);
                        this.commonDisplayControls();
                        
                        popup.getField('effectiveDate').enableField();
                        
                        break;
                    }
                    case _controller.APPROVE:
                    {
                        popup.getField('bulkTrfNum').show();
                        popup.getField('bulkTrfStatusDisp').show();
                        
                        this.displayWarnReversal(action);
                        this.commonDisplayControls();

                        break;
                    }
                    case _controller.REJECT:
                    {
                        popup.getField('bulkTrfNum').show();
                        popup.getField('bulkTrfStatusDisp').show();
                        
                        this.displayWarnReversal(action);
                        this.commonDisplayControls();

                        break;
                    }
                    case _controller.REVERSE:
                    {
                        popup.getField('bulkTrfNum').show();
                        popup.getField('bulkTrfStatusDisp').show();

                        this.displayWarnReversal(action);
                        this.commonDisplayControls();

                        break;
                    }
                }
            }
            ,displayWarnReversal: function(action) {
                var popup = _popups['bulkTransferMaint'];
                popup.getField('warnHeader').hide();
                
                if (action == _controller.REVERSE) {
                    popup.getField('warnHeader').show();
                }
                else if (action != _controller.ADD){
                    var trfStat = _grids['bulkTransfer'].getSelectedRecord().data['bulkTrfStatus'];
                    if (trfStat.toUpperCase() == _controller.TRF_STAT_PENDING_REVERSAL ||
                        trfStat.toUpperCase() == _controller.TRF_STAT_PROCESSING_REVERSAL ||
                        trfStat.toUpperCase() == _controller.TRF_STAT_TRANSFER_REVERSED) {
                        popup.getField('warnHeader').show();
                    }
                }
            }
            ,loadDataFromGrd: function() {
                var popup = _popups['bulkTransferMaint'];
                var selectedRec = _grids['bulkTransfer'].getSelectedRecord();

                popup.bulkTrfStatus = selectedRec.data['bulkTrfStatus'];
                popup.bulkTransferUUID = selectedRec.data['bulkTransferUUID'];
                popup.version = selectedRec.data['version'];
                popup.getField('blockTrfType').setValue(selectedRec.data['blockTrfType']);
                popup.getField('effectiveDate').setValue(selectedRec.data['effectiveDate']);
                popup.getField('awdBatchID').setValue(selectedRec.data['awdBatchID']);
                popup.getField('acctDesignation').setValue(selectedRec.data['acctDesignation']);

                popup.getField('frAgencyCode').prepopulate(selectedRec.data['frAgencyCode'], 
                                                           _controller.getBulkTrfDetlValue('frAgencyDesc'));
                popup.getField('frBranchCode').prepopulate(selectedRec.data['frBranchCode'], 
                                                           _controller.getBulkTrfDetlValue('frBranchDesc'));
                popup.getField('frSlsRepCode').prepopulate(selectedRec.data['frAgentCode'], 
                                                           _controller.getBulkTrfDetlValue('frAgentDesc'));
                popup.getField('toAgencyCode').prepopulate(selectedRec.data['toAgencyCode'], 
                                                           _controller.getBulkTrfDetlValue('toAgencyDesc'));
                popup.getField('toBranchCode').prepopulate(selectedRec.data['toBranchCode'], 
                                                           _controller.getBulkTrfDetlValue('toBranchDesc'));
                popup.getField('toSlsRepCode').prepopulate(selectedRec.data['toAgentCode'], 
                                                           _controller.getBulkTrfDetlValue('toAgentDesc'));
                popup.getField('toNomineeID').prepopulate(selectedRec.data['toNomineeID'], 
                                                          _controller.getBulkTrfDetlValue('toNomineeEntityDesc'));
                popup.getField('toIntermID').prepopulate(selectedRec.data['toIntr'], 
                                                         _controller.getBulkTrfDetlValue('toIntrDesc'));
                popup.getField('toIntermEntID').prepopulate(selectedRec.data['toIntrID'], 
                                                            _controller.getBulkTrfDetlValue('toIntrEntityDesc'));

                popup.getField('bulkTrfNum').setValue(selectedRec.data['bulkTrfNum']);
            }
            ,setAllReadOnly: function(flag) {
                var popup = _popups['bulkTransferMaint'];

                if (flag) {
                    popup.getField('blockTrfType').disable();
                    popup.getField('awdBatchID').disableField();
                    popup.getField('acctDesignation').disableField();
                    popup.getField('frAgencyCode').disableField();
                    popup.getField('frBranchCode').disableField();
                    popup.getField('frSlsRepCode').disableField();
                    popup.getField('toAgencyCode').disableField();
                    popup.getField('toBranchCode').disableField();
                    popup.getField('toSlsRepCode').disableField();
                    popup.getField('toNomineeID').disableField();
                    popup.getField('toIntermID').disableField();
                    popup.getField('toIntermEntID').disableField();
                }
                else {
                    popup.getField('blockTrfType').enable();
                    popup.getField('awdBatchID').enableField();
                    popup.getField('acctDesignation').enableField();
                    popup.getField('frAgencyCode').enableField();
                    popup.getField('frBranchCode').enableField();
                    popup.getField('frSlsRepCode').enableField();
                    popup.getField('toAgencyCode').enableField();
                    popup.getField('toBranchCode').enableField();
                    popup.getField('toSlsRepCode').enableField();
                    popup.getField('toNomineeID').enableField();
                    popup.getField('toIntermID').enableField();
                    popup.getField('toIntermEntID').enableField();
                }
            }
            ,commonDisplayControls: function(action) {
                var popup = _popups['bulkTransferMaint'];

                this.applyAcctDesignationChg(popup.getField('acctDesignation').getValue(), false);

                popup.getField('bulkTrfStatusDisp').setValue(_controller.getListDisplay('BulkTrfStatus', 
                                                                                        popup.bulkTrfStatus));
                popup.getField('effectiveDate').disableField();

                if (_controller.getDefaultValue('allowDispBlockTrfer').toLowerCase() == 'yes') {
                    popup.getField('blockTrfType').show();
                }else {
                    popup.getField('blockTrfType').hide();
                }

                if (_controller.getDefaultValue('allowModBlockTrfer').toLowerCase() == 'yes') {
                    popup.getField('blockTrfType').enableField();
                }else {
                    popup.getField('blockTrfType').disableField();
                }
            }
            ,applyAcctDesignationChg: function(value, clearField) {
                if (value == _controller.NOMINEE || value == _controller.ALL) {
                    _popups['bulkTransferMaint'].getField('toNomineeID').enableField();
                    _popups['bulkTransferMaint'].getField('toNomineeID').allowBlank = false;
                }else {
                    _popups['bulkTransferMaint'].getField('toNomineeID').disableField();
                    _popups['bulkTransferMaint'].getField('toNomineeID').allowBlank = true;
                    _popups['bulkTransferMaint'].getField('toNomineeID').clearInvalid();

                    if (clearField)
                        _popups['bulkTransferMaint'].getField('toNomineeID').setValue('');
                }

                if (value == _controller.INTERMEDIARY) {
                    _popups['bulkTransferMaint'].getField('toIntermID').enableField();
                    _popups['bulkTransferMaint'].getField('toIntermID').allowBlank = false;

                    _popups['bulkTransferMaint'].getField('toIntermEntID').enableField();
                    _popups['bulkTransferMaint'].getField('toIntermEntID').allowBlank = false;
                }else {
                    _popups['bulkTransferMaint'].getField('toIntermID').disableField();
                    _popups['bulkTransferMaint'].getField('toIntermID').allowBlank = true;
                    _popups['bulkTransferMaint'].getField('toIntermID').clearInvalid();

                    _popups['bulkTransferMaint'].getField('toIntermEntID').disableField();
                    _popups['bulkTransferMaint'].getField('toIntermEntID').allowBlank = true;
                    _popups['bulkTransferMaint'].getField('toIntermEntID').clearInvalid();

                    if (clearField) {
                        _popups['bulkTransferMaint'].getField('toIntermEntID').setValue('');
                        _popups['bulkTransferMaint'].getField('toIntermID').setValue('');
                    }
                }
                
                if (this.action != _controller.ADD && this.action != _controller.MOD) {
                    _popups['bulkTransferMaint'].getField('toNomineeID').disableField();
                    _popups['bulkTransferMaint'].getField('toIntermID').disableField();
                    _popups['bulkTransferMaint'].getField('toIntermEntID').disableField();
                }
            }
            ,isPopupValid: function(isPrint) {
                var isValid = true;
                var allData = _popups['bulkTransferMaint'].getData();
                var popup = _popups['bulkTransferMaint'];
                var fieldsToCheck = "";
                var fieldsToClear = "";
                
                if (isPrint) {
                	fieldsToCheck = ['frAgencyCode',
                                     'frBranchCode',
                                     'frSlsRepCode',
                                     'acctDesignation',
                                     'blockTrfType',
                                     'effectiveDate'];
                	fieldsToClear = ['toNomineeID',
                                     'toIntermID',
                                     'toIntermEntID',
                                     'toAgencyCode',
                                     'toBranchCode',
                                     'toSlsRepCode'];
                	for (var i = 0; i < fieldsToClear.length; i++) {
                		 popup.getField(fieldsToClear[i]).clearInvalid();
                    }
                } else {
                	fieldsToCheck = ['toNomineeID',
                                     'toIntermID',
                                     'toIntermEntID',
                                     'frAgencyCode',
                                     'frBranchCode',
                                     'frSlsRepCode',
                                     'toAgencyCode',
                                     'toBranchCode',
                                     'toSlsRepCode',
                                     'acctDesignation',
                                     'blockTrfType',
                                     'effectiveDate'];
                }
                
                for (var i = 0; i < fieldsToCheck.length; i++) {
                    if (!popup.getField(fieldsToCheck[i]).allowBlank && 
                        popup.getField(fieldsToCheck[i]).getValue() == '') {
                        isValid = false;
                        popup.getField(fieldsToCheck[i]).markInvalid(_translationMap['ERR_REQUIRED_FIELD']);
                    }
                }
                
                if ((allData['bulkTrfAction'] == _controller.MOD) && 
                	(popup.getField('effectiveDate').getValue() != '')) {
                	var currentBusinessDate = DesktopWeb.Util.stringToDate(_controller.getDefaultValue('defaultDate'));
                    if (currentBusinessDate.getTime() !== popup.getField('effectiveDate').getValue().getTime()) {
                    	isValid = false;
                    	popup.getField('effectiveDate').markInvalid(_translationMap['ERR_EFFECTIVEDATE_FIELD']);
                    }
                }
                
                return isValid;
            }
            ,resetAllFields: function()
            {
                if (this.rendered)
                {
                    var popup = _popups['bulkTransferMaint'];

                    popup.bulkTransferUUID = null;
                    popup.bulkTrfStatus = null;
                    popup.version = null;
                    popup.getField('bulkTrfNum').setValue('');
                    popup.getField('awdBatchID').setValue('');
                    popup.getField('effectiveDate').setValue('');
                    popup.getField('blockTrfType').setValue('');
                    popup.getField('acctDesignation').setValue('');
                    popup.getField('frAgencyCode').setValue('');
                    popup.getField('frBranchCode').setValue('');
                    popup.getField('frSlsRepCode').setValue('');
                    popup.getField('toAgencyCode').setValue('');
                    popup.getField('toBranchCode').setValue('');
                    popup.getField('toSlsRepCode').setValue('');
                    popup.getField('toNomineeID').setValue('');
                    popup.getField('toIntermID').setValue('');
                    popup.getField('toIntermEntID').setValue('');

                    popup.getField('awdBatchID').clearInvalid();
                    popup.getField('effectiveDate').clearInvalid();
                    popup.getField('blockTrfType').clearInvalid();
                    popup.getField('acctDesignation').clearInvalid();
                    popup.getField('frAgencyCode').clearInvalid();
                    popup.getField('frBranchCode').clearInvalid();
                    popup.getField('frSlsRepCode').clearInvalid();
                    popup.getField('toAgencyCode').clearInvalid();
                    popup.getField('toBranchCode').clearInvalid();
                    popup.getField('toSlsRepCode').clearInvalid();
                    popup.getField('toNomineeID').clearInvalid();
                    popup.getField('toIntermID').clearInvalid();
                    popup.getField('toIntermEntID').clearInvalid();
                }
            }
            ,getData: function() //Maintenance
            {
                var popup = _popups['bulkTransferMaint'];
                var data = {};

                data['bulkTransferUUID'] = popup.bulkTransferUUID;
                data['bulkTrfStatus'] = popup.bulkTrfStatus;
                data['bulkTrfNum'] = popup.getField('bulkTrfNum').getValue();
                data['awdBatchID'] = popup.getField('awdBatchID').getValue();
                data['effectiveDate'] = DesktopWeb.Util.getSMVDateValue(
                                                                popup.getField('effectiveDate').getDisplayDateString());
                data['blockTrfType'] = popup.getField('blockTrfType').getValue();
                data['acctDesignation'] = popup.getField('acctDesignation').getValue();
                data['frAgencyCode'] = popup.getField('frAgencyCode').getValue();
                data['frBranchCode'] = popup.getField('frBranchCode').getValue();
                data['frAgentCode'] = popup.getField('frSlsRepCode').getValue();
                data['toAgencyCode'] = popup.getField('toAgencyCode').getValue();
                data['toBranchCode'] = popup.getField('toBranchCode').getValue();
                data['toAgentCode'] = popup.getField('toSlsRepCode').getValue();
                data['toNomineeID'] = popup.getField('toNomineeID').getValue() == "" ? 
                                                                         '0':popup.getField('toNomineeID').getValue();
                data['toIntrCode'] = popup.getField('toIntermID').getValue();
                data['toIntrEntityID'] = popup.getField('toIntermEntID').getValue() == "" ? 
                                                                         '0':popup.getField('toIntermEntID').getValue();
                data['version'] = popup.version;
                data['bulkTrfAction'] = popup.action; //add/mod/approve/reject/reverse except print

                return data;
            }
        })
        ,bulkTransferDetls: new DesktopWeb.AdvancedControls.PopupWindow({
            width: 550
            ,action: null
            ,closeAction: 'hide'
            ,title: _translationMap['BulkTrferDetl']
            ,modal: true
            ,defaults: {border:false}
            ,buttonAlign: 'left'
            ,items: [
                {
                    layout: 'form'
                    ,itemId: 'popup_main'
                    ,style: 'padding:4px'
                    ,border:false
                    ,labelWidth: 123
                    ,items: [
                        {
                            layout: 'column'
                            ,border: false
                            ,defaults:{
                                layout: 'form'
                                ,border: false
                            }
                            ,items: [
                                {
                                    columnWidth: 0.55
                                    ,labelWidth: 150
                                    ,items: [
                                        new DesktopWeb.Controls.Label({
                                            itemId: 'bulkTrfNum'
                                            ,fieldLabel: _translationMap['BulkTrferID']
                                        })
                                        ,new DesktopWeb.Controls.Label({
                                            itemId: 'awdBatchID'
                                            ,fieldLabel: _translationMap['AWDBatchID']
                                        })
                                        ,new DesktopWeb.Controls.Label({
                                            itemId: 'blockTrfType'
                                            ,fieldLabel: _translationMap['BlockTrferType']
                                        })
                                        ,new DesktopWeb.Controls.Label({
                                            itemId: 'acctDesignation'
                                            ,fieldLabel: _translationMap['AcctDesign']
                                        })
                                    ]
                                }
                                ,{
                                    columnWidth: 0.45
                                    ,labelWidth: 100
                                    ,items: [
                                        new DesktopWeb.Controls.Label({
                                            itemId: 'bulkTrfStatusDisp'
                                            ,fieldLabel: _translationMap['Status']
                                        })
                                        ,new DesktopWeb.Controls.Label({
                                            itemId: 'effectiveDate'
                                            ,fieldLabel: _translationMap['EffectiveDate']
                                        })
                                        ,new DesktopWeb.Controls.Label({
                                            itemId: 'dateOfReversal'
                                            ,fieldLabel: _translationMap['DateOfReversal']
                                        })
                                    ]
                                }
                            ]
                        }
                        ,{
                            xtype: 'fieldset'
                            ,title: _translationMap['From']
                            ,labelWidth: 115
                            ,items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'frAgencyCode'
                                    ,fieldLabel: _translationMap['Broker']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'frBranchCode'
                                    ,fieldLabel: _translationMap['Branch']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'frSlsRepCode'
                                    ,fieldLabel: _translationMap['SalesRep']
                                })
                                ,new DesktopWeb.Controls.ActionButton({
                                    itemId: 'printBtn'
                                    ,text: _translationMap['AUMReport']
                                    ,style: 'float:right;'
                                    ,handler: function(){
                                        var allData = _popups['bulkTransferDetls'].getData();
                                        _controller.clickHandle_printBtn(allData);
                                    }
                                })
                            ]
                        }
                        ,{
                            xtype: 'fieldset'
                            ,title: _translationMap['To']
                            ,labelWidth: 115
                            ,items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'toAgencyCode'
                                    ,fieldLabel: _translationMap['Broker']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'toBranchCode'
                                    ,fieldLabel: _translationMap['Branch']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'toSlsRepCode'
                                    ,fieldLabel: _translationMap['SalesRep']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'toNominee'
                                    ,fieldLabel: _translationMap['Nominee']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'toInterm'
                                    ,fieldLabel: _translationMap['Intermediary']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'toIntermEnt'
                                    ,fieldLabel: _translationMap['IntermediaryEntity']
                                })
                            ]
                        }
                        ,{
                            layout: 'column'
                            ,border: false
                            ,defaults:{
                                layout: 'form'
                                ,border: false
                            }
                            ,items: [
                                {
                                    columnWidth: 0.50
                                    ,labelWidth: 100
                                    ,items: [
                                        new DesktopWeb.Controls.Label({
                                            itemId: 'createdBy'
                                            ,fieldLabel: _translationMap['CreatedBy']
                                        })
                                        ,new DesktopWeb.Controls.Label({
                                            itemId: 'reversedBy'
                                            ,fieldLabel: _translationMap['ReversedBy']
                                        })
                                    ]
                                }
                                ,{
                                    columnWidth: 0.50
                                    ,labelWidth: 180
                                    ,items: [
                                        new DesktopWeb.Controls.Label({
                                            itemId: 'approvedBy'
                                            ,fieldLabel: _translationMap['BulkTrferApprovedBy']
                                        })
                                        ,new DesktopWeb.Controls.Label({
                                            itemId: 'revApprovedBy'
                                            ,fieldLabel: _translationMap['ReversalApprovedBy']
                                        })
                                    ]
                                }
                                ,{
                                    columnWidth: 1.0
                                    ,labelWidth: 150
                                    ,items: [
                                        new DesktopWeb.Controls.Label({
                                            itemId: 'reqDateOfRev'
                                            ,fieldLabel: _translationMap['RequestDateOfReversal']
                                        })
                                    ]
                                }
                            ]
                        }
                    ]
                }
            ]
            ,buttons: [
                '->'
                ,new DesktopWeb.Controls.ActionButton({
                    itemId: 'okBtn'
                    ,text: _translationMap['OK']
                    ,handler: function(){
                        _controller.clickHandle_okBtnOnBulkTrfDetlsPopup();
                    }
                })
            ]
            ,init: function() {
                var popupDetl = _popups['bulkTransferDetls'];

                popupDetl.getField('bulkTrfNum').setValue(_controller.getBulkTrfDetlValue('bulkTrfNum'));
                popupDetl.getField('awdBatchID').setValue(_controller.getBulkTrfDetlValue('awdBatchID'));
                popupDetl.getField('blockTrfType').setValue(_controller.getListDisplay('BlockTrfType', 
                                                            _controller.getBulkTrfDetlValue('blockTrfType')));
                popupDetl.getField('acctDesignation').setValue(_controller.getListDisplay('AcctDesignation', 
                                                               _controller.getBulkTrfDetlValue('acctDesignation')));
                popupDetl.getField('bulkTrfStatusDisp').setValue(_controller.getListDisplay('BulkTrfStatus', 
                                                                 _controller.getBulkTrfDetlValue('bulkTrfStatus')));
                popupDetl.getField('effectiveDate').setValue(DesktopWeb.Util.getDateDisplayValue(
                                                                    _controller.getBulkTrfDetlValue('effectiveDate')));
                popupDetl.getField('dateOfReversal').setValue(DesktopWeb.Util.getDateDisplayValue(
                                                                    _controller.getBulkTrfDetlValue('dateOfReversal')));
                popupDetl.getField('frAgencyCode').setValue(_controller.getBulkTrfDetlValue('frAgencyDesc'));
                popupDetl.getField('frBranchCode').setValue(_controller.getBulkTrfDetlValue('frBranchDesc'));
                popupDetl.getField('frSlsRepCode').setValue(_controller.getBulkTrfDetlValue('frAgentDesc'));
                popupDetl.getField('toAgencyCode').setValue(_controller.getBulkTrfDetlValue('toAgencyDesc'));
                popupDetl.getField('toBranchCode').setValue(_controller.getBulkTrfDetlValue('toBranchDesc'));
                popupDetl.getField('toSlsRepCode').setValue(_controller.getBulkTrfDetlValue('toAgentDesc'));
                popupDetl.getField('toNominee').setValue(_controller.getBulkTrfDetlValue('toNomineeEntityDesc'));
                popupDetl.getField('toInterm').setValue(_controller.getBulkTrfDetlValue('toIntrDesc'));
                popupDetl.getField('toIntermEnt').setValue(_controller.getBulkTrfDetlValue('toIntrEntityDesc'));
                popupDetl.getField('createdBy').setValue(_controller.getBulkTrfDetlValue('userName'));
                popupDetl.getField('reversedBy').setValue(_controller.getBulkTrfDetlValue('reversedUser'));
                popupDetl.getField('approvedBy').setValue(_controller.getBulkTrfDetlValue('approvedUser'));
                popupDetl.getField('revApprovedBy').setValue(_controller.getBulkTrfDetlValue('revApproveUser'));
                popupDetl.getField('reqDateOfRev').setValue(DesktopWeb.Util.getDateDisplayValue(
                                                                 _controller.getBulkTrfDetlValue('reqDateOfReversal')));
            }
            ,populate: function(record, action) {

            }
            ,resetAllFields: function() {
                if ( this.rendered ) {
                }
            }
            ,getData: function(action) { //Detail
                var data = {};

                data['bulkTransferUUID'] = _controller.getBulkTrfDetlValue('bulkTransferUUID');
                data['bulkTrfStatus'] = _controller.getBulkTrfDetlValue('bulkTrfStatus');
                data['bulkTrfNum'] = _controller.getBulkTrfDetlValue('bulkTrfNum');
                data['awdBatchID'] = _controller.getBulkTrfDetlValue('awdBatchID');
                data['effectiveDate'] = _controller.getBulkTrfDetlValue('effectiveDate');
                data['blockTrfType'] = _controller.getBulkTrfDetlValue('blockTrfType');
                data['acctDesignation'] = _controller.getBulkTrfDetlValue('acctDesignation');
                data['frAgencyCode'] = _controller.getBulkTrfDetlValue('frAgencyCode');
                data['frBranchCode'] = _controller.getBulkTrfDetlValue('frBranch');
                data['frAgentCode'] = _controller.getBulkTrfDetlValue('frAgentCode');
                data['toAgencyCode'] = _controller.getBulkTrfDetlValue('toAgencyCode');
                data['toBranchCode'] = _controller.getBulkTrfDetlValue('toBranch');
                data['toAgentCode'] = _controller.getBulkTrfDetlValue('toAgentCode');
                data['toNomineeID'] = _controller.getBulkTrfDetlValue('toNomineeID') == "" ? 
                                                                     '0':_controller.getBulkTrfDetlValue('toNomineeID');
                data['toIntrCode'] = _controller.getBulkTrfDetlValue('toIntr');
                data['toIntrEntityID'] = _controller.getBulkTrfDetlValue('toIntrID') == "" ? 
                                                                     '0':_controller.getBulkTrfDetlValue('toIntrID');
                data['version'] = _controller.getBulkTrfDetlValue('version');

                return data;
            }
        })
        ,admin: new DesktopWeb.AdvancedControls.PopupWindow({
            width: 395
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,items: [
                {
                    layout: 'column'
                    ,style: 'padding:4px'
                    ,defaults: {border: false, labelWidth:80}
                    ,items: [
                        {
                            width: 185
                            ,layout: 'form'
                            ,defaults: {width:80}
                            ,items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'userName'
                                    ,fieldLabel: _translationMap['Username']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'modUser'
                                    ,fieldLabel: _translationMap['ModUser']
                                })
                            ]
                        }
                        ,{
                            width: 185
                            ,layout: 'form'
                            ,defaults: {width: 80}
                            ,items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'procDate'
                                    ,fieldLabel: _translationMap['ProcessDate']
                                })
                                ,new DesktopWeb.Controls.Label({
                                    itemId: 'modDate'
                                    ,fieldLabel: _translationMap['ModDate']
                                })
                            ]
                        }
                    ]
                }
            ]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['OK']
                    ,handler: function(){_popups['admin'].hide();}
                })
            ]
            ,init: function(title, data)
            {
                this.setTitle(title);
                this.getField('procDate').setValue(data['procDate']);
                this.getField('modDate').setValue(data['modDate']);
                this.getField('userName').setValue(data['userName']);
                this.getField('modUser').setValue(data['modUser']);
            }
        })
        ,history: new DesktopWeb.AdvancedControls.HistoryPopup()
    }

    // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth
        ,layoutHeight: _layoutHeight
        ,fields: _fields
        ,grids: _grids
        ,buttons: _buttons
        ,popups: _popups
        ,layout: new Ext.Container({
            height: _layoutHeight
            , width: _layoutWidth
            , items: [
                {
                    xtype: 'fieldset'
                    ,title: _translationMap['']
                    ,items: [
                        {
                            layout: 'column'
                            ,defaults:{
                                layout: 'form'
                            }
                            ,items: [
                                {
                                    columnWidth: 0.70
                                    ,labelWidth: 80
                                    ,items: [
                                        {
                                            layout: 'column'
                                            ,style:'padding-top:10px'
                                            ,defaults:{
                                                layout: 'form'
                                            }
                                            ,items: [
                                                {
                                                    columnWidth: 0.45
                                                    ,labelWidth: 110
                                                    ,items: [
                                                        _fields['reqIdSrch']
                                                    ]
                                                }
                                                ,{columnWidth: 0.03}
                                                ,{
                                                    columnWidth: 0.45
                                                    ,labelWidth: 50
                                                    ,items: [
                                                        _fields['statusSrch']
                                                    ]
                                                }
                                                ,{columnWidth: 0.07}
                                                ,{
                                                    columnWidth: 0.45
                                                    ,items: [
                                                        {
                                                            xtype: 'fieldset'
                                                            ,title: _translationMap['From']
                                                            ,items: [
                                                                _fields['fromBrokerSrch']
                                                                ,_fields['fromBranchSrch']
                                                                ,_fields['fromSlsRepSrch']
                                                            ]
                                                        }
                                                    ]
                                                }
                                                ,{columnWidth: 0.03}
                                                ,{
                                                    columnWidth: 0.45
                                                    ,items: [
                                                        {
                                                            xtype: 'fieldset'
                                                            ,title: _translationMap['To']
                                                            ,items: [
                                                                _fields['toBrokerSrch']
                                                                ,_fields['toBranchSrch']
                                                                ,_fields['toSlsRepSrch']
                                                            ]
                                                        }
                                                    ]
                                                }
                                                ,{columnWidth: 0.07}
                                            ]
                                        }
                                    ]
                                }
                                ,{
                                    columnWidth: 0.30
                                    ,labelWidth: 90
                                    ,items: [
                                        {
                                            layout: 'column'
                                            ,style:'padding-top:10px'
                                            ,defaults:{
                                                layout: 'form'
                                            }
                                            ,items: [
                                                {
                                                    columnWidth: 1.0
                                                    ,items: [
                                                        _fields['startDateSrch' ]
                                                        ,_fields['endDateSrch' ]
                                                    ]
                                                }
                                                ,{columnWidth: 1.0}
                                                ,{columnWidth: 1.0}
                                                ,{columnWidth: 1.0}
                                                ,{columnWidth: 1.0}
                                                ,{columnWidth: 1.0}
                                                ,{
                                                    columnWidth: 1.0
                                                    ,labelWidth: 70
                                                    ,items: [
                                                        _buttons['cmdSearch']
                                                    ]
                                                }
                                            ]
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                }
                ,_grids['bulkTransfer']
                ,{
                    xtype: 'fieldset'
                    ,title: _translationMap['BulkTransferActions']
                    ,items: [
                        _grids['bulkTrfActions']
                    ]
                }
            ]
        })

        ,screenButtons: {
            items:[
                new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['Close']
						,handler: function(){DesktopWeb.Util.cancelScreen()}
					}
				)
            ]
        }
    }
}