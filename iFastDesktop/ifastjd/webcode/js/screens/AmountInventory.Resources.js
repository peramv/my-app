/*********************************************************************************************
 * @file	AmountInventory.Resources.js
 * @author	Matira Thanetkulabut
 * @desc	Resources file for Amount Inventory screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Account > Historical Market Value > Invest Info
 *            Menu > Account > Transaction History > Invest Info
 *  
 *  History : 
 *  
 *  9-Nov-2016 Matira Thanetkulabut P0256533 T84110 MSF - Desktop
 *              - Initial
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    // content dimensions
    var _layoutHeight = 600;
    var _layoutWidth  = 750;

    // **** fields **** 
    var _fields = {
		invTypeFld: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['InvType']
            ,width: 120
            ,allowBlank: false
			,displayField: 'code'
			,valueField: 'value'
			,tpl: '<tpl for=".">' + '<div class="x-combo-list-item">' + '{code}&nbsp;' + '</div></tpl>'	
			,editable: false
			,autoSelect: true
            ,tabIndex: 1
			,listeners: 
            {
				select: function(fld, record, index)
                {
					_controller.clearFilter();
                    _controller.populateDropdowns(fld.getValueDesc());
					_fields['selectedInvType'].setValue(fld.getValue());
                }
            }
        })
		,fndClssFld: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['FndCls']
            ,width: 120
            ,displayField: 'code'
			,valueField: 'value'
			,tpl: '<tpl for=".">' + '<div class="x-combo-list-item">' + '{code}&nbsp;' + '</div></tpl>'	
			,editable: false
			,autoSelect: true
            ,tabIndex: 2
            ,listeners: 
            {
                select: function(fld, record, index)
                {
                    _fields['selectedFndCls'].setValue(fld.getValue());
                }
            }
        }) 
		,fndGrpFld: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['FndGrp']
            ,width: 120
            ,displayField: 'code'
			,valueField: 'value'
			,tpl: '<tpl for=".">' + '<div class="x-combo-list-item">' + '{code}&nbsp;' + '</div></tpl>'	
			,editable: false
			,autoSelect: true
            ,tabIndex: 3
            ,listeners: 
            {
                select: function(fld, record, index)
                {
                    _fields['selectedFndGrp'].setValue(fld.getValue());
                }
            }
        }) 
		,selectedInvType: new DesktopWeb.Controls.Label(
        {
            fieldLabel: ''
			,width: 200
            ,style: 'font-size: 13px; margin-bottom: 10px'
        })
		,selectedFndCls: new DesktopWeb.Controls.Label(
        {
            fieldLabel: ''
			,width: 200
            ,style: 'font-size: 13px; margin-bottom: 10px'
        })
		,selectedFndGrp: new DesktopWeb.Controls.Label(
        {
            fieldLabel: ''
			,width: 200
            ,style: 'font-size: 13px; margin-bottom: 10px'
        })
		,modeLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['Mode']
			,text: 'Account'
			,width: 120
        })
		,modeSrch: new DesktopWeb.Controls.RadioGroup({
			hideLabel: true
			,width: 270
			,column: 2
			,items:[
				{
					boxLabel: _translationMap['All']
					, name: 'modeSrch'
					, id: 'optAll'
					, width: 120
					, inputValue: false	
				}
				,{
					boxLabel: _translationMap['Active']
					, name: 'modeSrch'
					, id: 'optActive'
					, width: 120	
					, inputValue: true		
				}
			]
			,listeners:{
				change: function( grp, chked ){
					_controller.changeHandle_ModeSrch();
				}
			}
		})	
		,sortByFld: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['SortBy']
            ,width: 100
            ,allowBlank: false
			,editable: false
			,autoSelect: true
            ,tabIndex: 5
            ,listeners: 
            {
                select: function(fld, record, index)
                {
                    
                }
            }
        })
		,orderBox: new DesktopWeb.Controls.Checkbox(
        {
            boxLabel: _translationMap['Desc']
            ,tabIndex: 6
        })
		,invIDLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['InvId']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,statLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['Status']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,lastActivityDateLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['LastActDate']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
        })
		,origInvIDLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['OrigInv']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,origFndLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['OrigFnd']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,origClsLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['OrigCls']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,unitLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['Unit']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,fundLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['Fund']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,classLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['Class']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
		,aggBalLabel: new DesktopWeb.Controls.Label(
        {
			fieldLabel: _translationMap['AggBal']
            ,text: ''
            ,style: 'font-size: 13px; margin-bottom: 3px'
        })
    }
    
    // **** buttons ****
	var _buttons = {
		refresh: new DesktopWeb.Controls.ActionButton(
        {
            style: 'margin-bottom: 3px'
            ,text: _translationMap['Refresh']
            , handler: function()
            {
				if(_fields['invTypeFld'].isValid() && _fields['sortByFld'].isValid()){
					_controller.search();
				}
            }  
        })
    }
    
    // **** grids ****
	var _grids = {
		summary: new DesktopWeb.AdvancedControls.GridPanel(
        {
            height: 150
            ,store: new Ext.data.XmlStore(
            {
                record: 'Investment'
                ,fields: ['investId', 'investStat', 'lastActivityDate', 'origInvestId', 'origFund', 'origClass', 'unitCost', 
						  'fundCode', 'classCode', 'aggrBalance', 'investTransType', 'investDate', 'matureDate', 'investAmount',
						  'lotBalance', 'enableWithHoldTax', 'eligDate', 'eligAmount', 'resetDate', 'resetTransId']          
				,listeners: 
                {
                    load: function(store, records)
                    {		
                        Ext.each(records, function(record)
                        {
                            record.data.investDate = DesktopWeb.Util.getDateDisplayValue(record.data.investDate);
                            record.data.matureDate = DesktopWeb.Util.getDateDisplayValue(record.data.matureDate);
                            record.data.lastActivityDate = DesktopWeb.Util.getDateDisplayValue(record.data.lastActivityDate);
                        });
                        store.fireEvent('datachanged', store);
                    }
                }
			})
            ,selModel: new Ext.grid.RowSelectionModel(
            {					
                singleSelect: true
				,listeners: 
                {
                    rowselect: function(selModel, index, record)
                    {
                        _controller.populateDetails(record);
                        _controller.buildDetls(index+1);
                    }
                    ,rowdeselect: function()
                    {
                        _controller.clearInfo();
                    }
                }
            })
            ,colModel: new Ext.grid.ColumnModel(
            {
                defaults: 
                { menuDisabled: true }
                ,columns: [
                {
                    header: _translationMap['TransType']
                    ,width: 120
                    ,dataIndex: 'investTransType'
                }
                ,{
                    header: _translationMap['InvDate']
                    ,dataIndex: 'investDate'
                    ,width: 90
                }
				,{
                    header: _translationMap['MatDate']
                    ,dataIndex: 'matureDate'
                    ,width: 90
                }
				,{
                    header: _translationMap['InvAmt']
                    ,dataIndex: 'investAmount'
                    ,width: 120
                }
				,{
                    header: _translationMap['LotBal']
                    ,dataIndex: 'lotBalance'
                    ,width: 120
                }]
            })      
            ,buttons: [					
                new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'withHoldBtn'								
                    ,text: _translationMap['WithHoldTax']
                    ,disabled: true
                    ,style: 'margin-right: 5'		
                    ,handler: function()
                    {
                        _controller.openPopup('withHold', _grids['summary'].getSelectedRecord());
                    }
                })
				,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'moreBtn'								
                    ,text: _translationMap['More']
                    ,disabled: true
                    ,style: 'margin-right: 5'		
                    ,handler: function(){_controller.clickHandle_moreBtn();}
                })
            ]
        })
		,details: new DesktopWeb.AdvancedControls.GridPanel(
        {
            height: 150
            ,store: new Ext.data.XmlStore(
            {
                record: 'InvestmentDetl'
                ,fields: ['transNumber', 'transId', 'transType', 'tradeDate', 'settleDate', 'transAmount', 'marketValue', 
						  'taxExempt', 'enableFee', 'enableRedDetl', 'isMoneyOut']          
				,listeners: 
                {
                    load: function(store, records)
                    {		
                        Ext.each(records, function(record)
                        {
                            record.data.tradeDate = DesktopWeb.Util.getDateDisplayValue(record.data.tradeDate);
                            record.data.settleDate = DesktopWeb.Util.getDateDisplayValue(record.data.settleDate);
							if(record.data.isMoneyOut == 'yes'){
								record.data.transType = "<ins onclick='DesktopWeb._SCREEN_CONTROLLER.clickHandle_link(\"" + record.data.transId + "\")' >" + record.data.transType + "</ins>";
							}
                        });
                        store.fireEvent('datachanged', store);
                    }
                }     
			})
             ,selModel: new Ext.grid.RowSelectionModel(
            {					
                singleSelect: true
				,listeners: 
                {
                    rowselect: function(selModel, index, record)
                    {
                        _controller.buildButtons(record,index+1);
                    }
                    ,rowdeselect: function()
                    {
                    }
                }
            })
            ,colModel: new Ext.grid.ColumnModel(
            {
                defaults: 
                { menuDisabled: true }
                ,columns: [
                {
                    header: _translationMap['TransNo']
                    ,width: 90
                    ,dataIndex: 'transNumber'
                }
                ,{
                    header: _translationMap['TransID']
                    ,dataIndex: 'transId'
                    ,width: 90
                }
				,{
                    header: _translationMap['TransType']
                    ,dataIndex: 'transType'
                    ,width: 110
                }
				,{
                    header: _translationMap['TradeDate']
                    ,dataIndex: 'tradeDate'
                    ,width: 80
                }
				,{
                    header: _translationMap['SetlDate']
                    ,dataIndex: 'settleDate'
                    ,width: 80
                }
				,{
                    header: _translationMap['Amount']
                    ,dataIndex: 'transAmount'
                    ,width: 90
                }
				,{
                    header: _translationMap['MktVal']
                    ,dataIndex: 'marketValue'
                    ,width: 90
                }
				,{
                    header: _translationMap['TaxExem']
                    ,dataIndex: 'taxExempt'
                    ,width: 90
                }]
            })      
            ,buttons: [					
                new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'redDetlBtn'								
                    ,text: _translationMap['RedDetl']
                    ,disabled: true	
                    ,handler: function()
                    {
						_controller.openPopup('redem', _grids['details'].getSelectedRecord());
                    }
                })
				,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'feeBtn'								
                    ,text: _translationMap['Fee']
                    ,disabled: true	
                    ,handler: function()
                    {
                       _controller.openPopup('fee', _grids['details'].getSelectedRecord());
                    }
                })
				,new DesktopWeb.Controls.ActionButton(
                {
                    itemId: 'moreBtn'								
                    ,text: _translationMap['More']
                    ,disabled: true		
                    ,handler: function(){_controller.clickHandle_moreBtnDetl();}
                })
            ]
        })
		,feeGrid: new DesktopWeb.AdvancedControls.GridPanel(
		{																																		
			height: 200																		
			,enableHdMenu: false											
			,store: new Ext.data.XmlStore({
				record: 'InvestmentFee'					
				,fields: ['feeCode','feeDesc',
					'feeRate', 'feeAmount', 'portionAmount']				
			})	
			,selModel: new Ext.grid.RowSelectionModel(
			{					
			})
			,colModel: new Ext.grid.ColumnModel(
			{
				defaults: { menuDisabled: true }
				,columns: [																																															
					{header: _translationMap['FeeCode'], width: 80, dataIndex: 'feeCode'}
					,{header: _translationMap['FeeDesc'],width: 100, dataIndex: 'feeDesc'}
					,{header: _translationMap['FeeRate'], width: 100, dataIndex: 'feeRate'}				
					,{header: _translationMap['FeeAmt'], width: 100, dataIndex: 'feeAmount'}				
					,{header: _translationMap['Amount'], width: 100, dataIndex: 'portionAmount'}				
				]
			})											
		})
		,redemGrid: new DesktopWeb.AdvancedControls.GridPanel(
		{																																		
			height: 200																		
			,enableHdMenu: false											
			,store: new Ext.data.XmlStore({
				record: 'RedeemDetl'					
				,fields: ['redFeeCode','redFeeDesc',
					'redFeeRate', 'redFeeAmount', 'redPortionAmount']				
			})	
			,selModel: new Ext.grid.RowSelectionModel(
			{					
			})
			,colModel: new Ext.grid.ColumnModel(
			{
				defaults: { menuDisabled: true }
				,columns: [																																															
					{header: _translationMap['FeeCode'], width: 80, dataIndex: 'redFeeCode', resizable: false, fixed: true}
					,{header: _translationMap['FeeDesc'],width: 100, dataIndex: 'redFeeDesc', resizable: false, fixed: true}
					,{header: _translationMap['FeeRate'], width: 100, dataIndex: 'redFeeRate', resizable: false, fixed: true}				
					,{header: _translationMap['FeeAmt'], width: 100, dataIndex: 'redFeeAmount', resizable: false, fixed: true}				
					,{header: _translationMap['Amount'], width: 100, dataIndex: 'redPortionAmount', resizable: false, fixed: true}				
				]
			})											
		})
		
	}
	
	// **** popups ****
    var _popups = {
		withHold: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 395
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,items: [
            {
                layout: 'column'
                ,style: 'padding:4px'
                ,defaults: {border: false}
                ,items: [
                {
                    width: 185
                    ,layout: 'form'
					,labelWidth: 80
                    ,items: [
                        new DesktopWeb.Controls.Label(
                        {
                            itemId: 'eligDate'
                            ,fieldLabel: _translationMap['EligDate']
                        })
                        ,new DesktopWeb.Controls.Label(
                        {
                            itemId: 'eligAmt'
                            ,fieldLabel: _translationMap['EligAmt']
                        })
                    ]
                }
                ,{
                    width: 185
                    ,layout: 'form'
					,labelWidth: 100
                    ,items: 
                    [
                        new DesktopWeb.Controls.Label(
                        {
                            itemId: 'resetDate'
                            ,fieldLabel: _translationMap['ResetDate']
                        })
                        ,new DesktopWeb.Controls.Label(
                        {
                            itemId: 'resetTransId'
                            ,fieldLabel: _translationMap['ResetTrans']
                        })
                    ]
                }]
            }]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['Close']
                    ,handler: function()
                    {
                        _popups['withHold'].hide();
                    }
                })
            ]
            ,init: function(title, data)
            {
                this.setTitle(title);
                this.getField('eligDate').setValue(data['eligDate']);
                this.getField('eligAmt').setValue(data['eligAmount']);
                this.getField('resetDate').setValue(data['resetDate']);
                this.getField('resetTransId').setValue(data['resetTransId']);
            }
        })
		,redem: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 500
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,items: [_grids['redemGrid']]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['Close']
                    ,handler: function()
                    {
                        _popups['redem'].hide();
                    }
                })
            ]
			,init: function(title)
            {
                _grids['redemGrid'].getStore().removeAll();
                this.setTitle(title);
            }
        })
		,fee: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 500
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,items: [_grids['feeGrid']]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['Close']
                    ,handler: function()
                    {
                        _popups['fee'].hide();
                    }
                })
            ]
			,init: function(title)
            {
                _grids['feeGrid'].getStore().removeAll();
                this.setTitle(title);
            }
        })
		,transHist: new DesktopWeb.AdvancedControls.PopupWindow(
        {
            width: 395
            ,closeAction: 'hide'
            ,modal: true
            ,defaults: {border:false}
            ,items: [
				new DesktopWeb.AdvancedControls.GridPanel({
					id: 'feeGrid'																																		
					,height: 24																		
					,enableHdMenu: false
					,enableColumnMove: false											
					,store: new Ext.data.XmlStore({
						record: 'InvestmentFee'					
						,fields: ['feeCode','feeDesc',
							'feeRate', 'feeAmount', 'portionAmount']				
					})							
					,columns: [																																															
						{header: _translationMap['FeeCode'], width: 80, dataIndex: 'feeCode', resizable: false, fixed: true}
						,{header: _translationMap['FeeDesc'],width: 100, dataIndex: 'feeDesc', resizable: false, fixed: true}
						,{header: _translationMap['FeeRate'], width: 100, dataIndex: 'feeRate', resizable: false, fixed: true}				
						,{header: _translationMap['FeeAmt'], width: 100, dataIndex: 'feeAmount', resizable: false, fixed: true}				
						,{header: _translationMap['Amount'], width: 100, dataIndex: 'portionAmount', resizable: false, fixed: true}				
					]											
				})
			]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['Close']
                    ,handler: function()
                    {
                        _popups['transHist'].hide();
                    }
                })
            ]
        })
	}
	
     // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth

        ,layoutHeight: _layoutHeight

        ,fields: _fields

        ,grids: _grids

        ,popups: _popups

        ,buttons: _buttons

        ,layout: new Ext.Container(
        {
            height: _layoutHeight
            ,width: _layoutWidth
            ,items: [
			{
			
                itemId: 'mainLayout1'
                ,style: 'padding-left:5px; padding-right:10px'							
                ,layout: 'column'
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.3
                    ,labelWidth: 80
                    ,items :[
						_fields['invTypeFld']
                    ]
                }
                ,{
                    layout: 'form'
                    ,columnWidth: 0.4
                    ,items :[
                        _fields['selectedInvType']
                    ]
                } 
				,{
                    layout: 'form'
                    ,columnWidth: 0.3
                    ,labelWidth: 60
                    ,items :[
						_fields['modeLabel']
                    ]
                }]
			}
			,{
				itemId: 'mainLayout2'
                ,style: 'padding-left:5px; padding-right:10px'							
                ,layout: 'column'
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.3
                    ,labelWidth: 80
                    ,items :[
                        _fields['fndClssFld']
                    ]
                }
                ,{
                    layout: 'form'
                    ,columnWidth: 0.4
                    ,items :[
                        _fields['selectedFndCls']
                    ]
                } 
				,{
                    layout: 'form'
                    ,columnWidth: 0.3
                    ,items :[
						_fields['modeSrch']
                    ]
                }]
			}	
			,{
				itemId: 'mainLayout3'
                ,style: 'padding-left:5px; padding-right:10px'							
                ,layout: 'column'
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.3
                    ,labelWidth: 80
                    ,items :[
                        _fields['fndGrpFld']
                    ]
                }
                ,{
                    layout: 'form'
                    ,columnWidth: 0.4
                    ,items :[
                        _fields['selectedFndGrp']
                    ]
                } 
				,{
                    layout: 'form'
                    ,columnWidth: 0.3
                    ,labelWidth: 60
                    ,items :[
                        _fields['sortByFld']
                    ]
                }]
			}
			,{
				itemId: 'mainLayout4'
                ,style: 'padding-left:5px; padding-right:10px'							
                ,layout: 'column'
                ,items: [
                {
                    layout: 'form'
                    ,columnWidth: 0.3
                    ,labelWidth: 80
                    ,items :[
                    ]
                }
                ,{
                    layout: 'form'
                    ,columnWidth: 0.4
                    ,items :[
                    ]
                } 
				,{
                    layout: 'form'
                    ,columnWidth: 0.15
                    ,labelWidth: 60
                    ,items :[
                        _fields['orderBox']
                    ]
                }
				
				,{
                    layout: 'form'
                    ,columnWidth: 0.15
                    ,labelWidth: 150
                    ,items :[
                        _buttons['refresh']
                    ]
                }]
			}			
            ,{
                xtype: 'fieldset'
                ,title: _translationMap['InvenSum']									
                ,layout: 'column'
                ,items: [
                {
					layout: 'column'
					,defaults: {border: false}
					,style: 'margin-left:5px;'
					,items: [
					{
						layout: 'form'
						,columnWidth: 0.23
						,labelWidth: 100
						,items: [
							_fields['invIDLabel']
							,_fields['origInvIDLabel']
						]
					}
					,{
						layout: 'form'
						,columnWidth: 0.23
						,labelWidth: 80
						,items: [
							_fields['statLabel']
							,_fields['origFndLabel']
						]
					}
					,{
						layout: 'form'
						,columnWidth: 0.44
						,labelWidth: 120
						,items: [
							_fields['lastActivityDateLabel']
							,_fields['origClsLabel']
						]				
					}]
				}
				,{
					layout: 'column'
					,defaults: {border: false}
					,style: 'margin-left:5px;margin-bottom:5px'
					,items: [
					{
						layout: 'form'
						,columnWidth: 0.23
						,labelWidth: 80
						,items: [
							_fields['unitLabel']
						]
					}
					,{
						layout: 'form'
						,columnWidth: 0.23
						,labelWidth: 80
						,items: [
							_fields['fundLabel']
						]
					}
					,{
						layout: 'form'
						,columnWidth: 0.3
						,labelWidth: 120
						,items: [
							_fields['classLabel']
						]				
					}
					,{
						layout: 'form'
						,columnWidth: 0.24
						,labelWidth: 80
						,items: [
							_fields['aggBalLabel']
						]				
					}]
				}
				,_grids['summary']
				]
			}
            ,{
                xtype: 'fieldset'
                ,title: _translationMap['InvenDetls']
                ,items: [
                {
                    layout: 'column'																
                    ,items: [
						_grids['details']
					]
                }]
            }
		]
		
		})
        
        ,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
                text: _translationMap['Close']
                ,handler: function(){
                    DesktopWeb.Util.cancelScreen();
                }
            })
        ]
    }

}	