/*********************************************************************************************
 * @file    RESPNotionalActivity.Resources.js
 * @author  Narin Suanlamyai
 * @desc    Resources JS file for Notional Activity screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  13 Jul 2015 Narin Suanlamyai P0241773 T81239
 *                    - Initial
 *
 *  01 Aug 2015 Narin Suanlamyai P0241773 T81348
 *                    - Fix search validation
 *
 *  16 Nov 2015 Aurkarn Mongkonrat P0241773 DFT0056497 T81740
 *                    - Change grid header from showing beneficiary id to beneficiary name.
 *
 *	21 Apr 2016 Narin Suanlamyai P0241773 DFT0059694 T82619
 *		- Refresh the search result when user changes the Informaiton Level
 *
 *	10 May 2016 Narin Suanlamyai P0241773 DFT0060804 T82810
 *		- Update list of Activity Category combobox to load data from new transaction category list.
 *		- Add a new column Category.
 *
 *  19 May 2016 Busarakorn S. P0241773 DFT0063462 T82875
 *      - Added a new column to bottom grid
 *      - Added new field and new column.
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
            width: 355,
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
        actCat: new DesktopWeb.Controls.ComboBox({
            fieldLabel: _translationMap["ActivityCategory"],
            width: 355,
            disabled: true,
            valueField: 'txnCateId',
            displayField: 'description',
            allowBlank: false,
            store: new Ext.data.XmlStore({
                record: 'TxnCategory',
				fields: ['txnCat', 'cateCode', 'cateValue', 'description', 'txnCateId']
            })
        }),
        reason: new DesktopWeb.Controls.SMVComboBox({
            fieldLabel: _translationMap["Reason"],
            width: 200,
            disabled: true,
            allowBlank: false
        }),
        fromDate: new DesktopWeb.Controls.DateField({
            fieldLabel: _translationMap["From"],
            width: 100,
            disabled: true,
            allowBlank: false,
            format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
        }),
        toDate: new DesktopWeb.Controls.DateField({
            fieldLabel: _translationMap["To"],
            width: 100,
            disabled: true,
            allowBlank: false,
            format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
        }),
        remarks: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap["Remarks"]
        }),
        notlChgReason: new DesktopWeb.Controls.Label({
            fieldLabel: _translationMap["Reason"]
        })
    }
    
    // **** grids ****
    var _grids = {
        notlAct: new DesktopWeb.AdvancedControls.GridPanel(
            {
                autoScroll: true,
                height: 250,
                autoExpandColumn: 'description',
                store: new Ext.data.XmlStore({
                    record: 'NotionalActivity',
                    fields: ['notlTransId', 'transType', 'category', 'description', 
                                'deff', 'transNumber', 'amount', 'stat',
                                'remarks', 'notlChgReason', 'userName',
                                'processDate', 'modUser', 'modDate'],
                    listeners: {
                        load: function (store, records) {
                            Ext.each(records, function (record) {
                                record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
                            });

                            store.fireEvent('datachanged', store); //to set data in grid again
                        }
                    }
                }),
                selModel: new Ext.grid.RowSelectionModel({
                    singleSelect: true
                    ,listeners: {
                        rowselect: function(selModel, index, record){
                            if(selModel){
                                _controller.selectNotlActivity(record, index);
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
                        {header: _translationMap["TransactionType"], dataIndex: 'transType', width: 100},
                        {header: _translationMap["Category"], dataIndex: 'category', width: 120},
                        {id: 'description', header: _translationMap["Description"], dataIndex: 'description'},
                        {header: _translationMap["Date"], dataIndex: 'deff', width: 72},
                        {header: _translationMap["TransactionNumber"], dataIndex: 'transNumber', width: 72},
                        {header: _translationMap["NotionalTransactionId"], dataIndex: 'notlTransId', width: 72},
                        {header: _translationMap["Amount"], dataIndex: 'amount', width: 72},
                        {header: _translationMap["Status"], dataIndex: 'stat', width: 72}
                    ]
                }),
                buttons: [
                    new DesktopWeb.Controls.ActionButton({
                        itemId: 'adminBtn',
                        text: _translationMap['Admin'],
                        disabled: true,
                        handler: function () {
                            _controller.openAdminPopup(_grids['notlAct'].getSelectedRecord());
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
        notlActDetl: new DesktopWeb.AdvancedControls.GridPanel(
            {
                autoScroll: true,
                height: 150,
                store: new Ext.data.XmlStore({
                    record: 'NotionalActivityDetl',
                    fields: ['grantType', 'amount', 'ACAmount', 'UCAmount', 'grantPaid', 'YTDAmount', 'benefId', 
                             'benefName' , 'amtToReturn']
                }),
                selModel: new Ext.grid.RowSelectionModel({
                    singleSelect: true
                }),
                colModel: new Ext.grid.ColumnModel({
                    defaults: {
                        menuDisabled: true,
                        sortable: false
                    },
                    columns: [
                        {header: _translationMap["BeneficiaryHeader"], dataIndex: 'benefName', width: 155},
                        {id: 'grantType', header: _translationMap["NotionalAccount"], dataIndex: 'grantType', width: 150},
                        {header: _translationMap["Amount"], dataIndex: 'amount', width: 82},
                        {header: _translationMap["Assisted"], dataIndex: 'ACAmount', width: 82},
                        {header: _translationMap["Unassisted"], dataIndex: 'UCAmount', width: 82},
                        {header: _translationMap["YTD"], dataIndex: 'YTDAmount', width: 82},
						{header: _translationMap["PendingClawBack"], dataIndex: 'amtToReturn', width: 82}
                    ]
                }),
                buttons: []
            }
        )
    }
    
    // **** popups ****
    var _popups = {
        admin: new DesktopWeb.AdvancedControls.PopupWindow({
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
                    ,handler: function(){_popups['admin'].hide();}
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
                            columnWidth: 1.0,
                            items: [
                                {
                                    layout: 'form',
                                    labelWidth: 105,
                                    items: [_fields['infoLevel']]
                                }
                            ]
                        },
                        {
                            columnWidth: 0.65,
                            layout: 'form',
                            labelWidth: 105,
                            items: [ _fields['actCat'] ]
                        },
                        {
                            columnWidth: 0.35,
                            labelWidth: 40,
                            layout: 'form',
                            items: [ _fields['fromDate'] ]
                        },
                        {
                            columnWidth: 0.65,
                            layout: 'form',
                            labelWidth: 105,
                            items: [ _fields['reason'] ]
                        },
                        {
                            columnWidth: 0.25,
                            labelWidth: 40,
                            layout: 'form',
                            items: [ _fields['toDate'] ]
                        },
                        {
                            columnWidth: 0.1,
                            layout: 'form',
                            items: [ _buttons['refreshBtn'] ]
                        }
                    ]
                },
                {
                    layout: 'form',
                    items: [
                        {
                            xtype: 'fieldset',
                            title: _translationMap['NotionalActivity'],
                            items: [
                                {
                                    layout: 'form',
                                    style: 'padding-right: 5px; padding-bottom: 10px; padding-left: 5px;',
                                    items: [_grids['notlAct']]
                                },
                                {
                                    xtype: 'fieldset',
                                    title: _translationMap['AdditionalInformation'],
                                    items: [
                                        {
                                            layout: 'form',
                                            style: 'padding-right: 5px; padding-bottom: 5px; padding-left: 5px;',
                                            labelWidth: 65,
                                            items: [_fields['notlChgReason'], _fields['remarks']]
                                        }
                                    ]
                                }
                            ]
                        },
                        {
                            xtype: 'fieldset',
                            title: ' ',
                            items: [
                                {
                                    layout: 'form',
                                    style: 'padding-right: 5px; padding-bottom: 5px; padding-left: 5px;',
                                    items: [_grids['notlActDetl']]
                                }
                            ]
                        }
                    ]
                }
            ]
        }),
        screenButtons: [
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['NotionalBalance'],
                hidden: true,
                handler: function () {
                    _controller.goToNotionalBalanceScreen('RESPNotionalBalance');
                }
            }),
            new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Close'],
                handler: function () {
                    DesktopWeb.Util.commitScreen();
                }
            })
        ]
    }
}
