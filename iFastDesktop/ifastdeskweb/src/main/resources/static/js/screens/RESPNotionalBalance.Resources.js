/*********************************************************************************************
 * @file    RESPNotionalBalance.Resources.js
 * @author  Narin Suanlamyai
 * @desc    Resources JS file for Notional Balance screen
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
 *      - Fix adjustment validation
 *
 *  17 Sep 2015 Narin Suanlamyai P0241773 T81293
 *      - Add admin popup for breakdown
 *      - Effective Date cannot be more than current business date.
 *
 *  11 Dec 2015 Narin Suanlamyai P0241773 DFT0056498 T81878
 *      - Fixed error message when adjusted balance is going to be negative
 *		- Fixed missing balance amount on adjustment screen.
 *		- Screen allows negative if it is more negative.
 *
 *  05 Jan 2016 Nopphawan Hatthaseriphong P0250179 DFT0058218 T82197
 *      - Change the label is grant under the heading Assisted and Unassisted 
 *
 *  10 Feb 2016 Nopphawan Hatthaseriphong P0250179 DFT0058789 T82240
 *      - Adjust a width of Notional Account column
 *        and make tooltips to display the full description of each line.
 *      
 *	21 Apr 2016 Narin Suanlamyai P0241773 DFT0059694 T82619
 *		 - Refresh the search result when user changes the Informaiton Level
 *
 *	16 May 2016 Narin Suanlamyai P0241773 DFT0061569 T82733
 *		- Do the adjustment validation at notional bucket type.
 *		- The warning/error will be displayed next to adjusted balance row.
 *
 *	28 Sep 2016 Narin Suanlamyai P0241773 DFT0059465 T83889
 *		 - Display QESI Pre-Feb 2007 in read-only mode.
 *		 - QESI Pre-Feb 2007 amount is calculated on the screen.
 *		 - Formula: QESI Pre-Feb 2007 = CNTB + P98C - QESIAC - QESIUC - QESIYTD
 *
 * *	21 Oct 2016 Nopphawan Hatthaseriphong P0241773 DFT0068179 T84080 
 *		 - Fixed QESI buckets are getting created for Non-QESI account 
 *         by calculation QESI Basic Pre-Feb 21 2007 only QESI account
 *         (call updateQESIPreFeb2007).
 *         Add condition to check this account is QESI or not (from <isQESI> tag) 
 *         before calling updateQESIPreFeb2007.
 *
 */
 
DesktopWeb.ScreenResources = function (ctrlr) {
    
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    // content dimensions
    var _layoutHeight = 650;
    var _layoutWidth = 750;
    
    // **** buttons ****
    var _buttons = {
        refreshBtn: new DesktopWeb.Controls.ActionButton({
            text: _translationMap["Refresh"],
            disabled: true,
            listeners: {
                click: function () {
                    _controller.clickHandle_searchBtn();
                }
            }
        })
    }
    
    // **** fields ****
    var _fields = {
        infoLevel: new DesktopWeb.Controls.ComboBox({
            fieldLabel: _translationMap["InformationLevel"],
            width: 270,
            disabled: true,
            valueField: 'code',
            displayField: 'description',
            allowBlank: false,
            store: new Ext.data.XmlStore({
                record: 'Element',
                fields: ['level', 'code', 'description']
            }),
			listeners: {
				select: function (fld, record, index) {
					_controller.selectHandler_infoLevel(record);
				}
			}
		}),
        period: new DesktopWeb.Controls.ComboBox({
            fieldLabel: _translationMap["Period"],
            width: 125,
            disabled: true,
            valueField: 'code',
            displayField: 'description',
            allowBlank: false,
            store: new Ext.data.XmlStore({
                record: 'Element',
                fields: ['level', 'code', 'description']
            })
        }),
        periodRadio: new DesktopWeb.Controls.Radio({
            name: 'filter',
            listeners: {
                check: function () {
                    _controller.toggleFilterFields();
                }
            },
            disabled: true
        }),
        asOfDate: new DesktopWeb.Controls.DateField({
            fieldLabel: _translationMap["AsOf"],
            width: 100,
            disabled: true,
            format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
        }),
        asOfRadio: new DesktopWeb.Controls.Radio({
            name: 'filter',
            style: 'margin-top: 8px;',
            listeners: {
                check: function () {
                    _controller.toggleFilterFields();
                }
            },
            disabled: true
        }),
        marketValue: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap["MarketValue"]
        })
    }
    
    // **** grids ****
    var _grids = {
        contribIncomHd: new DesktopWeb.AdvancedControls.GridPanel({
            height: 24
            ,enableHdMenu: false
            ,enableColumnMove: false
            ,store: new Ext.data.XmlStore({
                record: 'PossibleMatch'
                ,fields: []
            }),
            columns:[
                {header: _translationMap['Asset'], width: 210, resizable: false, fixed: true},
                {header: _translationMap['Purchase'], width: 120, align: "right", resizable: false, fixed: true},
                {header: _translationMap['Redemption'], width: 120, align: "right", resizable: false, fixed: true},
                {header: _translationMap['Adjustment'], width: 120, align: "right", resizable: false, fixed: true},
                {header: _translationMap['Balance'], width: 120, align: "right", resizable: false, fixed: true}
            ]
        }),
        contribIncome: new DesktopWeb.AdvancedControls.TreeGrid({
            height: 120,
            useArrows: false,
            trackMouseOver: false,
            hideHeaders: true,
            columns:[
                {header: _translationMap['Asset'], dataIndex: 'description', width: 210},
                {header: _translationMap['Purchase'], dataIndex: 'received', width: 120, align: "right"},
                {header: _translationMap['Redemption'], dataIndex: 'paidOut', width: 120, align: "right"},
                {header: _translationMap['Adjustment'], dataIndex: 'adjusted', width: 120, align: "right"},
                {header: _translationMap['Balance'], dataIndex: 'balance', width: 120, align: "right"}
            ],
            selModel: new Ext.tree.DefaultSelectionModel({
                listeners: {
                    beforeselect: function () {
                        return false;
                    }
                }
            })
        }),
        acucHd: new DesktopWeb.AdvancedControls.GridPanel({
            height: 24
            ,enableHdMenu: false
            ,enableColumnMove: false
            ,store: new Ext.data.XmlStore({
                record: 'PossibleMatch'
                ,fields: []
            }),
            columns:[
                {header: _translationMap['Contribution'], width: 210, resizable: false, fixed: true},
                {header: _translationMap['Purchase'], width: 120, align: "right", resizable: false, fixed: true},
                {header: _translationMap['Redemption'], width: 120, align: "right", resizable: false, fixed: true},
                {header: _translationMap['Adjustment'], width: 120, align: "right", resizable: false, fixed: true},
                {header: _translationMap['Balance'], width: 120, align: "right", resizable: false, fixed: true}
            ]
        }),
        acuc: new DesktopWeb.AdvancedControls.TreeGrid({
            height: 125,
            useArrows: false,
            trackMouseOver: false,
            hideHeaders: true,
            columns:[
                {header: _translationMap['Contribution'], dataIndex: 'description', width: 210},
                {header: _translationMap['Purchase'], dataIndex: 'received', width: 120, align: "right"},
                {header: _translationMap['Redemption'], dataIndex: 'paidOut', width: 120, align: "right"},
                {header: _translationMap['Adjustment'], dataIndex: 'adjusted', width: 120, align: "right"},
                {header: _translationMap['Balance'], dataIndex: 'balance', width: 120, align: "right"}
            ],
            selModel: new Ext.tree.DefaultSelectionModel({
                listeners: {
                    beforeselect: function () {
                        return false;
                    }
                }
            })
        }),
        grantsHd: new DesktopWeb.AdvancedControls.GridPanel({
            height: 38
            ,enableHdMenu: false
            ,enableColumnMove: false
            ,store: new Ext.data.XmlStore({
                record: 'PossibleMatch'
                ,fields: []
            }),
            columns:[
                {header: _translationMap['Grant'], width: 150, fixed: true},
                {header: _translationMap['Received'], width: 90, align: "right"},
                {header: _translationMap['PaidOut'], width: 90, align: "right"},
                {header: _translationMap['Returned'], width: 90, align: "right"},
                {header: _translationMap['Adjustment'], width: 90, align: "right"},
                {header: _translationMap['Balance'], width: 90, align: "right"},
                {header: _translationMap['PendingClawBackCol'], width: 90, align: "right"}
            ]
        }),
        grants: new DesktopWeb.AdvancedControls.TreeGrid({
            height: 125,
            useArrows: false,
            trackMouseOver: false,
            hideHeaders: true,
            columns:[
                {header: _translationMap['Grant'], dataIndex: 'description', width: 150},
                {header: _translationMap['Received'], dataIndex: 'received', width: 90, align: "right"},
                {header: _translationMap['PaidOut'], dataIndex: 'paidOut', width: 90, align: "right"},
                {header: _translationMap['Returned'], dataIndex: 'returned', width: 90, align: "right"},
                {header: _translationMap['Adjustment'], dataIndex: 'adjusted', width: 90, align: "right"},
                {header: _translationMap['Balance'], dataIndex: 'balance', width: 90, align: "right"},
                {header: _translationMap['PendingClawBackCol'], dataIndex: 'pendClawBack', width: 90, align: "right"}
            ],
            selModel: new Ext.tree.DefaultSelectionModel({
                listeners: {
                    beforeselect: function () {
                        return false;
                    }
                }
            })
        }),
        notlDetls: new DesktopWeb.AdvancedControls.GridPanel(
            {
                autoScroll: true,
                height: 300,
                autoExpandColumn: 'txnRuleDesc',
                store: new Ext.data.XmlStore({
                    record: 'NotlActivity',
                    fields: ['account', 'benefId', 'transType', 'transDesc',
                                'txnRuleDesc', 'deff', 'benefName',
                                'transNumber', 'notlTransId', 'amount',
                                'statusCode', 'statusDesc', 'remark',
                                'userName', 'processDate', 'modDate', 'modUser'],
                    listeners: {
                        load: function (store, records) {
                            Ext.each(records, function (record) {
                                record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
                                record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
                            });
                            store.fireEvent('datachanged', store); //to set data in grid again
                            
                            store.filterBy( function (record) {
                                return record.data.runMode != _controller.DEL;
                            });
                        }
                    }
                }),
                selModel: new Ext.grid.RowSelectionModel({
                    singleSelect: true,
                    listeners: {
                        rowselect: function(selModel, index, record){
                            if(selModel){
                                _controller.selectNotlDetlRecord(record, index);
                            }
                        }
                    }
                }),
                colModel: new Ext.grid.ColumnModel({
                    defaults: {
                        menuDisabled: true,
                        sortable: false
                    },
                    columns: [
                        {header: _translationMap["Transaction"], dataIndex: 'transDesc', width: 80},
                        {id: 'txnRuleDesc', header: _translationMap["Description"], dataIndex: 'txnRuleDesc'},
                        {header: _translationMap["TransactionDate"], dataIndex: 'deff', width: 72},
                        {header: _translationMap["Beneficiary"], dataIndex: 'benefName', width: 72},
                        {header: _translationMap["TransactionNumber"], dataIndex: 'transNumber', width: 72},
                        {header: _translationMap["NotionalTransactionId"], dataIndex: 'notlTransId', width: 72},
                        {header: _translationMap["NotionalAmount"], dataIndex: 'amount', width: 72},
                        {header: _translationMap["Status"], dataIndex: 'statusDesc', width: 72}
                    ]
                }),
                buttons: [
                    new DesktopWeb.Controls.ActionButton({
                        itemId: 'adminBtn',
                        text: _translationMap['Admin'],
                        disabled: true,
                        handler: function () {
                            _controller.openBreakdownAdminPopup(_grids['notlDetls'].getSelectedRecord());
                        }
                    }),
                    new DesktopWeb.Controls.ActionButton({
                        itemId: 'moreBtn',
                        text: _translationMap['More'],
                        disabled: true,
                        handler: function () {
                            _controller.clickHandle_moreBtn();
                        }
                    })
                ]
            }
        ),
        adjustmentHd: new DesktopWeb.AdvancedControls.GridPanel({
            height: 24,
            enableHdMenu: false,
            enableColumnMove: false,
            store: new Ext.data.XmlStore({
                record: 'PossibleMatch'
                ,fields: []
            }),
            columns:[
                {header: _translationMap['NotionalAccount'], width: 200, resizable: false, fixed: true},
                {header: _translationMap['BalanceAsOf'], width: 100, align: "right", resizable: false, fixed: true},
                {header: _translationMap['Adjustment'], width: 100, align: "right", resizable: false, fixed: true},
                {header: _translationMap['AdjustedBalance'], width: 100, align: "right", resizable: false, fixed: true}
            ]
        })
    }
    
    // **** popups ****
    var _popups = {
        notlDetls: new DesktopWeb.AdvancedControls.PopupWindow({
            action: null,
            width: 700,
            title: _translationMap["NotionalDetailInformation"],
            closeAction: 'hide',
            autoHeight: true,
            modal: true,
            defaults: {border:false},
            items: [
                {                        
                    layout: 'column',
                    style: 'padding-top:10px; padding-right:10px; padding-left:10px;',
                    defaults: {layout: 'form', border:false},
                    items: [
                        {
                            columnWidth: 0.65,
                            labelWidth: 102,
                            items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'infoLevel',
                                    fieldLabel: _translationMap["InformationLevel"]
                                })
                            ]
                        },
                        {
                            columnWidth: 0.35,
                            labelWidth: 40,
                            items: [
                                new DesktopWeb.Controls.Label({
                                    itemId: 'period',
                                    fieldLabel: _translationMap["Period"],
                                    hidden: true
                                }),
                                new DesktopWeb.Controls.Label({
                                    itemId: 'asOfDate',
                                    fieldLabel: _translationMap["AsOf"],
                                    hidden: true
                                })
                            ]
                        }
                    ]
                },
                {
                    layout: 'form',
                    style: 'padding-right:5px; padding-left:5px;',
                    items: [
                        {
                            xtype: 'fieldset',
                            title: '',
                            id: 'notlDetlBucketPanel',
                            border: true,
                            items: [
                                {
                                    layout: 'column',
                                    id: 'contribBucketPanel',
                                    hidden: true,
                                    border: false,
                                    defaults: {
                                        layout: 'form',
                                        border: false,
                                        columnWidth: 0.25,
                                        style: 'padding-left:10px;'
                                    },
                                    items:[
                                        {
                                            labelWidth: 55,
                                            items:[
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'contribReceived',
                                                    fieldLabel: _translationMap["Purchase"]
                                                })
                                            ]
                                        },
                                        {
                                            labelWidth: 72,
                                            items:[
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'contribPaidOut',
                                                    fieldLabel: _translationMap["Redemption"]
                                                })
                                            ]
                                        },
                                        {
                                            labelWidth: 70,
                                            items:[
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'contribAdjusted',
                                                    fieldLabel: _translationMap["Adjustment"]
                                                })
                                            ]
                                        },
                                        {
                                            labelWidth: 45,
                                            items:[
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'contribBalance',
                                                    fieldLabel: _translationMap["Balance"]
                                                })
                                            ]
                                        }
                                    ]
                                },
                                {
                                    layout: 'column',
                                    id: 'grantBucketPanel',
                                    itemId: 'grantActivityPanel',
                                    hidden: true,
                                    border: false,
                                    defaults: {
                                        layout: 'form',
                                        border: false,
                                        columnWidth: 0.3,
                                        style: 'padding-left:10px;'
                                    },
                                    items:[
                                        {
                                            labelWidth: 70,
                                            items:[
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'grantReceived',
                                                    fieldLabel: _translationMap["Received"]
                                                }),
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'grantAdjusted',
                                                    fieldLabel: _translationMap["Adjustment"]
                                                })
                                            ]
                                        },
                                        {
                                            labelWidth: 55,
                                            items:[
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'grantPaidOut',
                                                    fieldLabel: _translationMap["PaidOut"]
                                                }),
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'grantBalance',
                                                    fieldLabel: _translationMap["Balance"]
                                                })
                                            ]
                                        },
                                        {
                                            labelWidth: 110,
                                            columnWidth: 0.4,
                                            items:[
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'grantReturned',
                                                    fieldLabel: _translationMap["Returned"]
                                                }),
                                                new DesktopWeb.Controls.Label({
                                                    itemId: 'grantPendClawBack',
                                                    fieldLabel: _translationMap["PendingClawBack"]
                                                })
                                            ]
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                },
                {
                    layout: 'column',
                    style: 'padding-right:15px; padding-left:15px;',
                    defaults: {layout: 'form', stlye: 'padding-right: 10px; padding-left: 10px;', border: false},
                    items: [
                        {
                            columnWidth: 0.29,
                            labelWidth: 72,
                            items: [
                                new DesktopWeb.Controls.DateField({
                                    itemId: 'startDate',
                                    fieldLabel: _translationMap['DateRange'],
                                    allowBlank: false,
                                    format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
                                })
                            ]
                        },
                        {
                            columnWidth: 0.61,
                            labelWidth: 25,
                            items: [
                                new DesktopWeb.Controls.DateField({
                                    itemId: 'endDate',
                                    fieldLabel: _translationMap['To'],
                                    allowBlank: false,
                                    format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
                                })
                            ]
                        },
                        {
                            columnWidth: 0.10,
                            items: [
                                new DesktopWeb.Controls.ActionButton({
                                    text: _translationMap['Refresh'],
                                    itemId: 'detlRefresh',
                                    listeners: {
                                        click: function () {
                                            _controller.clickHandle_searchBreakdownBtn();
                                        }
                                    }
                                })        
                            ]
                        }
                    ]                                                
                },
                {
                    layout: 'form',
                    style: 'padding-right:5px; padding-left:5px;',
                    items: [
                        {
                            xtype: 'fieldset',
                            title: 'Activity',
                            items: [
                                _grids['notlDetls']
                            ]
                        }
                    ]
                }
            ],
            buttons: [
                new DesktopWeb.Controls.ActionButton({                                                                                        
                    itemId: 'closeNotlDetls',
                    text: _translationMap['Close'],
                    listeners: {
                        click: function () {
                            _popups['notlDetls'].hide()
                        }
                    }                                                                                                                                                                                     
                })        
            ],
            init: function (groupType, notlGroup, notlType) {
                this.clearNotlBreakdownPopup();
                this.initNotlBreakdownPopup(groupType, notlGroup, notlType);
            },
            clearNotlBreakdownPopup: function() {
                this.getField('infoLevel').reset();
                this.getField('period').reset();
                this.getField('asOfDate').reset();
                this.clearNotlDetlsGrid();

                Ext.getCmp('contribBucketPanel').hide();
                Ext.getCmp('grantBucketPanel').hide();
            },
            clearNotlDetlsGrid: function() {
                _grids['notlDetls'].getStore().removeAll();
                _grids['notlDetls'].disableAllButtons();
            },
            initNotlBreakdownPopup: function (groupType, notlGroup, notlType) {
                var currentSearch = _controller.getCurrentSearch();

                this.getField('infoLevel').setText(currentSearch['infoLevelDesc']);
                
                if (currentSearch['periodLevel'] !== 'AOD') { // LTD or YTD
                    this.getField('period').setText(currentSearch['periodDesc']);
                    this.getField('period').show();
                    this.getField('asOfDate').hide();
                }else{
                    this.getField('asOfDate').setText(currentSearch['asOfDateDisp']);
                    this.getField('asOfDate').show();
                    this.getField('period').hide();
                }
                
                _controller.setNotlDetlBalance(groupType, notlGroup, notlType);
            }
        }),
        adjustPopup: new DesktopWeb.AdvancedControls.PopupWindow({
            action: null,
            width: 595,
            title: _translationMap["AdjustmentPopupTitle"],
            closeAction: 'hide',
            autoHeight: true,
            modal: true,
            defaults: {border:false},
            items: [
                {
                    layout: 'form',
                    style: 'padding:5px;',
                    labelWidth: 105,
                    items: [
                        new DesktopWeb.Controls.ComboBox({
                            id: 'infoLevel',
                            itemId: 'infoLevel',
                            fieldLabel: _translationMap["InformationLevel"],
                            width: 300,
                            disabled: false,
                            valueField: 'code',
                            displayField: 'description',
                            allowBlank: false,
                            store: new Ext.data.XmlStore({
                                record: 'Element',
                                fields: ['level', 'code', 'description', 'isQESI']
                            }),
                            listeners: {
                                select: function (fld, record, index) {
                                    _controller.selectHandler_Adjust_infoLevel(record);
                                }
                            }
                        }),
                        new DesktopWeb.Controls.DateField({
                            itemId: 'deff',
                            fieldLabel: _translationMap["EffectiveDate"],
                            width: 100,
                            disabled: false,
                            format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()),
                            allowBlank: false,
                            listeners: {
                                change: function (fld, newValue, oldValue) {
                                    if (fld.isValid()){
                                        _controller.changeHandler_Adjust_deff(fld, newValue, oldValue);
                                    }
                                }
                            }
                        }),
                        new DesktopWeb.Controls.SMVComboBox({
                            itemId: 'reason',
                            fieldLabel: _translationMap["Reason"],
                            width: 200,
                            disabled: false,
                            valueField: 'code',
                            displayField: 'value',
                            allowBlank: false
                        }),
                        new DesktopWeb.Controls.TextField({
                            itemId: 'remarks',
                            fieldLabel: _translationMap["Remarks"],
                            width: 350,
                            maxLength: 140,
                            disabled: false,
                            allowBlank: false
                        }),
                        {
                            xtype: 'fieldset',
                            title: _translationMap['NotionalAccounts'],
                            id: 'notlAcctsPanel',
                            border: true,
                            labelWidth: 100,
                            items: [
                                new DesktopWeb.Controls.ComboBox({
                                    itemId: 'notlType',
                                    fieldLabel: _translationMap["NotionalType"],
                                    width: 100,
                                    disabled: false,
                                    valueField: 'code',
                                    displayField: 'value', 
                                    store: new Ext.data.XmlStore({
                                        record: 'Element',
                                        fields: ['code', 'value']
                                    }),
                                    allowBlank: false,
                                    listeners: {
                                        select: function (fld, record, index) {
                                            _controller.selectHandle_Adjust_notlType(record.get('code'));
                                        }
                                    }
                                    
                                }),
                                _grids['adjustmentHd'],
                                new Ext.Container({
                                    id: 'adjustmentContainer'
                                    ,height: 275
                                    ,style: 'position:relative; overflow-y: scroll;'
                                    ,items: []
                                }),
                                {
                                    border: false
                                }
                            ]
                        } 
                    ]
                }
            ],
            buttons: [
                new DesktopWeb.Controls.ActionButton({
                    itemId: 'submitAdjustmentPopup',
                    text: _translationMap['OK'],
                    listeners: {
                        click: function () {
                            var adjPopup = _popups['adjustPopup'];
                            if (adjPopup.isDirty()) {
                                if (adjPopup.isValid()) {
                                    _controller.doAdjustmentUpdate();
                                }
                            } else {
                                adjPopup.hide();
                            }
                        }
                    }
                }),
                new DesktopWeb.Controls.ActionButton({
                    itemId: 'closeAdjustmentPopup',
                    text: _translationMap['Cancel'],
                    listeners: {
                        click: function () {
                            var adjPopup = _popups['adjustPopup'];
                            if (adjPopup.isDirty()) {
                                DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
                            }else{
                                handlePromptMsg(true);
                            }
                            
                            function handlePromptMsg(confirm) {
                                if (confirm) {
                                    adjPopup.hide();
                                }
                            }
                        }
                    }
                })
            ],
            init: function () {
                this.clearPopup();
                _controller.loadEligibleAdjustment('init');
            },
            clearPopup: function () {
                this.getField('infoLevel').reset();
                this.getField('deff').reset();
                this.getField('reason').reset();
                this.getField('remarks').reset();
                this.getField('notlType').reset();
                this.clearAdjustmentContainer();
            },
            clearAdjustmentContainer: function () {
                var adjustContainer = Ext.getCmp('adjustmentContainer');
                if (adjustContainer.rendered) {
                    adjustContainer.removeAll();
                }
            },
            isValid: function () {
                var valid = true;
                
                valid = this.getField('infoLevel').isValid() && valid;
                valid = this.getField('deff').isValid() && valid;
                valid = this.getField('reason').isValid() && valid;
                valid = this.getField('remarks').isValid() && valid;
                
                valid = !this.isValidAdjustment() && valid;
                
                return valid;
            },
            isValidAdjustment: function () {
                var isValidAdjusted = true;
                var adjustContainer = Ext.getCmp('adjustmentContainer');
                var notlTypeGrps = adjustContainer.items;
                for (i = 0; i < notlTypeGrps.items.length; i++) {
                    notlTypeGrp = notlTypeGrps.items[i].items;
                    for (j = 0; j < notlTypeGrp.items.length; j++) {
                        if (!notlTypeGrp.items[j].isValidAdjustment) {
                            isValidAdjusted = false;
							break;
                        }
                    }
                }
                return isValidAdjusted;
            },
            isGoing2Negative: function () {
                var negative = false;
                var adjustContainer = Ext.getCmp('adjustmentContainer');
                var notlTypeGrps = adjustContainer.items;
                for (i = 0; i < notlTypeGrps.items.length; i++) {
                    notlTypeGrp = notlTypeGrps.items[i].items;
                    var adjBal = 0;
                    var adj = 0;
                    
                    for (j = 0; j < notlTypeGrp.items.length; j++) {
                        adj = notlTypeGrp.items[j].getAdjustment();
                        adjBal = notlTypeGrp.items[j].getAdjustedBalance();
                        
                        if (adj !== 0 && adjBal < 0) {
                            negative = true;
                        }
                    }
                }
                return negative;
            },
            isDirty: function () {
                var dirty = false;
                var adjustContainer = Ext.getCmp('adjustmentContainer');
                var notlTypeGrps = adjustContainer.items;
                for (i = 0; i < notlTypeGrps.items.length; i++) {
                    notlTypeGrp = notlTypeGrps.items[i].items;
                    var adj = 0;
                    
                    for (j = 0; j < notlTypeGrp.items.length; j++) {
                        adj = notlTypeGrp.items[j].getAdjustment();
                        
                        if (adj !== 0) {
                            dirty = true;
                        }
                    }
                }
                return dirty;
            },
            getData: function () {
                
            }
        }),
        breakdownAdmin: new DesktopWeb.AdvancedControls.PopupWindow({
            width: 395
            ,closeAction: 'hide'
            ,title: _translationMap['Admin']
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
                    ,handler: function(){_popups['breakdownAdmin'].hide();}
                })
            ]
            ,init: function(data)
            {
                this.getField('procDate').setValue(data['procDate']);
                this.getField('modDate').setValue(data['modDate']);
                this.getField('userName').setValue(data['userName']);
                this.getField('modUser').setValue(data['modUser']);    
            }                                        
        })
    } 
    
    // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth,
        
        layoutHeight: _layoutHeight,

        buttons: _buttons,
        
        fields: _fields,
        
        grids: _grids,
        
        popups: _popups,
        
        layout: new Ext.Container({
            height: _layoutHeight,
            width: _layoutWidth,
            items: [
                {                        
                    layout: 'column',
                    items: [
                        {
                            columnWidth: 0.6,
                            items: [
                                {
                                    layout: 'form',
                                    labelWidth: 105,
                                    items: [_fields['infoLevel'], _fields['marketValue']]
                                }
                            ]
                        },
                        {
                            columnWidth: 0.4,
                            layout: 'column',
                            items: [
                                {
                                    columnWidth: 0.08,
                                    items: [
                                        {
                                            layout: 'form',
                                            items: [_fields['periodRadio'], _fields['asOfRadio']]
                                        }        
                                    ]
                                },
                                {
                                    columnWidth: 0.68,
                                    items: [
                                        {
                                            layout: 'form',
                                            labelWidth: 40,
                                            items: [_fields['period'], _fields['asOfDate']]
                                        }
                                    ]
                                },
                                {
                                    columnWidth: 0.24,
                                    items: [
                                        {
                                            layout: 'form',
                                            items: [_buttons['refreshBtn']]
                                        }
                                    ]
                                }
                            ]
                        }
                    ]
                },
                {
                    layout: 'form',
                    items: [
                        {
                            xtype: 'fieldset',
                            title: _translationMap['ContributionAndIncome'],
                            items: [
                                {
                                    layout: 'form',
                                    style: 'padding-right: 5px; padding-bottom: 10px; padding-left: 5px;',
                                    items: [
                                        _grids['contribIncomHd'],
                                        _grids['contribIncome']
                                    ]
                                }
                            ]
                        },
                        {
                            xtype: 'fieldset',
                            title: _translationMap['AssistedAndUnassisted'],
                            items: [
                                {
                                    layout: 'form',
                                    style: 'padding-right: 5px; padding-bottom: 10px; padding-left: 5px;',
                                    items: [
                                        _grids['acucHd'],
                                        _grids['acuc']
                                    ]
                                }
                            ]
                        },
                        {
                            xtype: 'fieldset',
                            title: _translationMap['Grants'],
                            items: [
                                {
                                    layout: 'form',
                                    style: 'padding-right: 5px; padding-bottom: 10px; padding-left: 5px;',
                                    items: [
                                        _grids['grantsHd'],
                                        _grids['grants']
                                    ]
                                }
                            ]
                        }
                    ]
                }
            ]
        }),
        screenButtons: [
            new DesktopWeb.Controls.ScreenButton({
                name: 'activityButton',
                text: _translationMap['Activity'],
                disabled: true,
                handler: function () {
                    _controller.clickHandle_ActivityBtn();
                }
            }),
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Adjustment'],
                disabled: true,
                handler: function () {
                    _controller.clickHandle_AdjustmentBtn();
                }
            }),
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Close'],
                handler: function () {
                    DesktopWeb.Util.cancelScreen();
                }
            })
        ]            
    }
}

DesktopWeb.ScreenResources.AdjustRow = Ext.extend( Ext.Panel, {
	
	isValid: true,
	notlGrp: '',
	notlType: '',
	bucketType: '',
	originalBalance: '',
	
	currentBalanceFld: null,
	adjustmentFld: null,
	adjustedAmountFld: null
	
    ,initComponent: function(){
        this.addEvents({'edit' : true});
        
        var labelWidth = 127
        var columnWidth = 95
		
		this.notlGrp = this.initialConfig.notlGrp;
		this.notlType = this.initialConfig.notlType;
        this.bucketType = this.initialConfig.bucketType;
        this.originalBalance = this.initialConfig.balance.value;
		this.callbackFn = this.initialConfig.callbackFn;
        
		this.currentBalanceFld = null;
        this.adjustmentFld = null;
        this.adjustedAmountFld = null;
		this.hiddenFld = null;
		
        this.currentBalanceFld = new DesktopWeb.Controls.Label({
            width: columnWidth
            ,style: 'padding-right:5px; padding-top:2px; text-align: right;'
			,text: this.getNumberDisplayFormat(this.initialConfig.balance.value)
            ,id: this.initialConfig.balance.id
        })
		
		if (!this.initialConfig.adjust.readOnly) {
			this.adjustmentFld = new DesktopWeb.Controls.NumberField({
				width: columnWidth
				,value: this.initialConfig.adjust.value
				,style: 'text-align: right'
				,disabled: this.initialConfig.adjust.disabled
				,allowNegative: true
				,allowDecimal: true
				,decimalPrecision: 2
				,decimalSeparator: '.'
				,id: this.initialConfig.adjust.id
			})
			this.adjustmentFld.addListener('change', this.onAdjustment, this);
		} else {
			this.adjustmentFld = new DesktopWeb.Controls.Label({
				width: columnWidth
				,style: 'padding-right:5px; padding-top:2px; text-align: right;'
				,text: this.getNumberDisplayFormat('0.00')
				,id: this.initialConfig.adjust.id
			})
		}

        this.adjustedAmountFld = new DesktopWeb.Controls.Label({
            width: columnWidth
            ,style: 'padding-right:5px; padding-top:2px; text-align: right;'
			,text: this.getNumberDisplayFormat(this.initialConfig.adjusted.value)
            ,id: this.initialConfig.adjusted.id
        })
		
		//need at least one non-label field, so this is in case whole row is to be static
		this.hiddenFld = new DesktopWeb.Controls.TextField({
			hidden: true
		})
		
		var config = {
            id: this.initialConfig.id
            ,layout: 'form'
            ,labelWidth: 187
            ,height: 30
            ,border: false
            ,style: 'border-top: 5px; border-bottom: 1px'
            ,items: [
                {
                    xtype: 'compositefield'
                    ,labelStyle: 'overflow:hidden; text-overflow: ellipsis; white-space:nowrap'
                    ,fieldLabel: '<span ext:qtip="' + this.initialConfig.rowLabel + '">' + 
        							this.initialConfig.rowLabel + '</span>'	
                    ,labelSeparator: ''
                    ,items: [
                        this.currentBalanceFld, this.adjustmentFld, this.adjustedAmountFld, this.hiddenFld,
						{
							id: 'adjNotiFlag' + this.initialConfig.id,
							border: false,
							defaults: {
								border: false
							}
						}
                    ]
                }
            ]            
        }

        Ext.apply(this, Ext.apply(this.initialConfig, config));
        DesktopWeb.ScreenResources.AdjustRow.superclass.initComponent.apply(this, arguments);
    }
    
    ,onRender: function(ct, position)
    {
        DesktopWeb.ScreenResources.AdjustRow.superclass.onRender.call(this, ct, position);        
    }
    
    ,activateAdjustment: function () {
        this.adjustmentFld.on({
            'change' : {
                fn: this.onAdjustment,
                scope: this
            }
        });
    }
	
    ,onAdjustment: function(fld, newValue)
    {
		this.clearNotification();
		
        if (newValue === "")
        {
            fld.setValue("0");
        }
    
        if (!isNaN(this.adjustmentFld.getValue()))
        {
            this.updateBalance();
        }
        
		if(this.callbackFn)this.callbackFn(this, this.adjustmentFld.getValue(), this.adjustedAmountFld.getValue());
		
        this.fireEvent('edit', this);
    }

    ,updateBalance: function()
    {
        var adjBal = getFloatValue(this.currentBalanceFld) + getFloatValue(this.adjustmentFld);
        
        this.adjustedAmountFld.setValue(this.getNumberDisplayFormat(adjBal));
        
		DesktopWeb._SCREEN_CONTROLLER.doAdjustmentValidateByNotlType(this);
		
		function getFloatValue(fld) {
			return parseFloat((Ext.isObject(fld) && !isNaN(fld.getValue())) ? fld.getValue() : 0);
		}
    }

	,doAdjustment: function (adjAmt) {
		this.adjustmentFld.setValue(this.getNumberDisplayFormat(adjAmt));
		this.updateBalance();
	}
	
    ,getData: function()
    {
        var data = {};
        data[this.currentBalanceFld.id] = this.currentBalanceFld.getValue();
        data[this.adjustmentFld.id] = this.adjustmentFld.getValue();
        data[this.adjustedAmountFld.id] = this.adjustedAmountFld.getValue();
        
        return data;
    }
    
    ,getCurrentBalance: function()
    {
        return this.currentBalanceFld.getValue();
    }
    
    ,getAdjustment: function()
    {
        return this.adjustmentFld.getValue();
    }
    
    ,getAdjustedBalance: function()
    {
        return this.adjustedAmountFld.getValue();
    }
    
    ,disable: function()
    {
        this.currentBalanceFld.disable();
        this.adjustmentFld.disable();
        this.adjustedAmountFld.disable();
        this.superclass().disable.call(this);
    }
	
	,getNumberDisplayFormat: function(formattedNumber)
	{
		var valueNumber = formattedNumber + '';
		if (DesktopWeb._SCREEN_PARAM_MAP['locale'] === 'enUS') {
			valueNumber = valueNumber.replace(',', '');
		} else
		if (DesktopWeb._SCREEN_PARAM_MAP['locale'] === 'frCA') {
			valueNumber = valueNumber.replace(' ', '').replace(',', '.');
		}
		return Ext.util.Format.number(valueNumber, '0.00')
	}
	
	,setNotification: function(notiMsg, severity)
	{
		if (severity == 'error')
		{
			Ext.get('adjNotiFlag' + this.initialConfig.id).dom.innerHTML = DesktopWeb.Util.buildErrorFlag(notiMsg);
		}else{
			Ext.get('adjNotiFlag' + this.initialConfig.id).dom.innerHTML = DesktopWeb.Util.buildWarningFlag(notiMsg);
		}
	}
	
	,clearNotification: function(){
		Ext.get('adjNotiFlag' + this.initialConfig.id).dom.innerHTML = '';
	}
});
