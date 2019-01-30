/*********************************************************************************************
 * @file	RDSPNotionalLotInquiry.Resources.js
 * @author	Usha S
 * @desc	Resources JS file for NotionalLotDetailsInquiry.
 *********************************************************************************************/
DesktopWeb.ScreenResources = function(ctrlr) {
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _layoutHeight = 700;
	var _layoutWidth = 750;
	var pageSize = 100;
	var currRecord = 0;
	var ineration= 0;
	
	function showPaymentDate(record) {
		var category = record.data.notionalCategory;
		if(category == "01" || category == "02") {
			return record.data.paymentDate;
		}
		return "";
	}

	function getTransactionTypeValue(val) {
		for(var index = 0; index < _translationMap['TransactionTypes'].length; ++index) {
			var description = _translationMap['TransactionTypes'][index];
			var keys = description.key.transType.split(",");
			for(var i = 0; i < keys.length; ++i) {
				if (keys[i].trim() === val) {
					return description.text;
				}
			}
		}
		return "";
	}
	
	function getNotionalCategoryValue(val) {
	for(var index = 0; index < _translationMap['NotionalCategoryTypes'].length; ++index) {
		var description = _translationMap['NotionalCategoryTypes'][index];
		var keys = description.key.notionalType.split(",");
		for(var i = 0; i < keys.length; ++i) {
			if (keys[i].trim() === val) {
				return description.text;
			}
		}
	}
	return "";
}
	
	
	// **** buttons ****
	var _buttons = {
			closeScreenButton : new DesktopWeb.Controls.ScreenButton(
			{
				text: _translationMap['Close']
				,handler: function(){
					_controller.goToScreen();
				}
			})
		    ,moreBtn: new DesktopWeb.Controls.ActionButton({
				itemId: 'moreBtn'
				,text: _translationMap['More']
				,handler: function(){
					_controller.getNotionalLotActivityDetails(_grids['RDSPTransactionDetailsGrid'].getStore().getCount(), pageSize);
				}
			})
			,refreshButton : new DesktopWeb.Controls.ActionButton({
				itemId: 'refreshBtn'
					,text: _translationMap['Refresh']
					,handler: function(){
						currRecord = 0;
						_controller.getNotionalLotActivityDetails(0, pageSize);
						
					}
			})
	}
	
	var _fields = {
		RDSPNotionalLotDetailLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['RDSPNotionalLotDetail']
		}) 	
		,NotionalCategoryField: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap["NotionalCategory"]
			,editable: true
			,width: 150
			,autoSelect: true
			,listeners : {
				select : function( combo, record, index ){
				_controller.setTransTypeList(record.data.code);
				}
			}
		})
		,TransactionTypeField: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap["TransactionType"]
			,editable: true
			,width: 150
			,autoSelect: true
		})
		,LotIDField: new DesktopWeb.Controls.NumberField({
			fieldLabel : _translationMap['LotID'],
			style : 'padding-left:5px;text-align:right;',
			width: 150
			,allowDecimals: false
			,setValue : function(v)
			{
			    return v;
			}
			,listeners : {
				change : function(){
					// if not empty disable other fields
					if(this.getValue()) {
						_fields['NotionalCategoryField'].disable();
						_fields['TransactionTypeField'].disable();
						_fields['FromField'].disable();
						_fields['ToField'].disable();
						_fields['TransactionNumberField'].disable();						
					} else {
						_fields['NotionalCategoryField'].enable();
						_fields['TransactionTypeField'].enable();
						_fields['FromField'].enable();
						_fields['ToField'].enable();
						_fields['TransactionNumberField'].enable();	
					}
				
				}
			}
		})
		,FromField: new DesktopWeb.Controls.DateField({
				fieldLabel: _translationMap['TradeFromDate']
				,style : 'padding-left:5px;'
				,width : 150
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,maxValue : new Date()
				,validator : function(value){
					var validate=_controller.validateFromDate(value);
					if(_fields['ToField'] && ineration == 0) {
						ineration ++;
						_fields['ToField'].validate();
					} else {
						ineration = 0;
					}
					return validate;
			    }
		}),
		ToField: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['TradeToDate']
				,style : 'padding-left:5px;'
				,width : 150
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,value : new Date()
				,maxValue : new Date()
				,validator : function(value){
					var validate=_controller.validateToDate(value);
					if(_fields['FromField'] && ineration == 0) {
					_fields['FromField'].validate();
					}else {
						ineration = 0;
					}
					return validate;
			    }
		})
		,TransactionNumberField: new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['TransactionNumber'],
			style : 'padding-left:5px;text-align:right;',
			width : 150,
			listeners : {
				change : function(){
					// if not empty disable other fields
					if(this.getValue()) {
						_fields['NotionalCategoryField'].disable();
						_fields['TransactionTypeField'].disable();
						_fields['FromField'].disable();
						_fields['ToField'].disable();
						_fields['LotIDField'].disable();	
						
						
					} else {
						_fields['NotionalCategoryField'].enable();
						_fields['TransactionTypeField'].enable();
						_fields['FromField'].enable();
						_fields['ToField'].enable();
						_fields['LotIDField'].enable();	
						
					}
				
				}
			}
		})
		,LotIdLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['LotID'],
			style : 'padding-left:5px;',
			width : 100
		})
		,OriginalAmountLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['OriginalAmount'],
			style : 'padding-left:5px;',
			width : 100
		})
		,DepletedAmountLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['DepletedAmount'],
			style : 'padding-left:5px;',
			width : 100
		})
		,BalanceLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['Balance'],
			style : 'padding-left:5px;',
			width : 100
		})
	}
	var _grids = {
			RDSPTransactionDetailsGrid : new DesktopWeb.AdvancedControls.GridPanel({
				width: _layoutWidth-15
				,sortable: true
				,dirty: false
				,autoScroll: true
				,height: 300
				,id: 'RDSPTransactionDetailsGrid'
				,store: new Ext.data.XmlStore(
						{
							record: 'notionalLotActivityDetails'
							,fields: [
								'notionalCategory',
								'transactionType',
								'transactionNumber',
								{name:'lotId', type:'int'},
								'amount',
								'tradeDate',
								'paymentDate'
							]
						}
					)
				
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.getLotIdBalances(record.data)
								}
							}
						}
					}
				)
				,viewConfig: { autoFill: true }
				
			
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true,
		                sortable: false				
					}

					,columns: [
						{width: 0, id:'transId', dataIndex: 'transactionId',hidden: true, height: 15}
						,{header: _translationMap['Category'], id:'Category',  align: "center", dataIndex: 'notionalCategory',width: 30
							,renderer: function(val, metaData, record){return getNotionalCategoryValue(val);}
						}
						,{header: _translationMap['TransactionType'], id:'TransactionType', align:"center", dataIndex: 'transactionType', width: 30
							,renderer: function(val, metaData, record){return getTransactionTypeValue(val);} 
							}
						,{header: _translationMap['TransactionNumber'], id:'TransactionNumber', align:"center", dataIndex: 'transactionNumber', width: 30}
						,{header: _translationMap['LotID'], id:'LotID', align:"center", dataIndex: 'lotId', width: 30}
						,{header: _translationMap['Amount'], id:'Amount', align:"center", dataIndex: 'amount',width: 30 }
						,{header: _translationMap['TradeDate'], id:'TradeDate', align:"center", dataIndex: 'tradeDate',width: 30 }
						,{header: _translationMap['PayDate'], id:'PayDate', align:"center", dataIndex: 'paymentDate',width: 30 
							,renderer: function(val, metaData, record){return showPaymentDate(record);} }
					
					]
				})
				,buttons: [_buttons['moreBtn']
				]			

			})
	}
	

	return {
		layoutWidth : _layoutWidth,
		layoutHeight : _layoutHeight,
		fields : _fields,
		grids: _grids,
		buttons: _buttons,
		pageSize : pageSize,
		layout : new Ext.Container(
				{
					height : _layoutHeight,
					width : _layoutWidth,
					items:[
						{                        
		                    layout: 'column',
		                    labelWidth: 140,		                    
		                    items: [
		                        {
		                        	layout: 'form'
		                        	,columnWidth: 0.45
		                            ,items: [
		                            	_fields['NotionalCategoryField']]
		                            
		                        },
		                        {
		                        	items:[_fields['TransactionTypeField']]
		                        	,columnWidth: 0.45
		                        	,layout: 'form'
		                           
		                        }
		                      ]
						},
						{                        
		                    layout: 'column',
		                    
		                    items: [
		                        {
		                        	columnWidth: 0.45
		                        	,labelWidth: 140
		                            ,items: [_fields['FromField']]
		                        	,layout: 'form'	                        	
		                        },
		                        {
		                        	items:[_fields['ToField']],
		                        	labelWidth: 140,
		                        	columnWidth: 0.45
		                        	,layout: 'form'
		                        }
		                      ]
						},                        
                        {
                        	layout : 'column',
                        	labelWidth: 140,
		                    items: [
		                        {
		                        	columnWidth: 0.45,
		                        	labelWidth: 140
		                            ,items: [_fields['TransactionNumberField']]
		                        	,layout: 'form'	                        	
		                        },
		                        {
		                        	items:[_fields['LotIDField']],
		                        	labelWidth: 140,
		                        	columnWidth: 0.45
		                        	,layout: 'form'
		                           
		                        },
		                        {
		                        	columnWidth: 0.10,
		                        	labelWidth: 140
		                            ,items: [_buttons['refreshButton']]
	                        		,layout: 'form'
		                            
		                        }
		                      ]
                        },                        
                        new Ext.Container({
        					height: _layoutHeight
        					, width: _layoutWidth
        					, items: [	
        						{
        						xtype: 'fieldset'
        						,title: _translationMap['RDSPTransactionDetails']
        						,items:[
        	                        {
        							layout: 'column'
        							,items: [_grids['RDSPTransactionDetailsGrid']]
        							}        							
        						  ]        						
        						},
        						{
                                    xtype: 'fieldset',
                                    title: _translationMap['LotDetails'],
                                    id: 'lotDetailsFieldSet',
                            		hidden : false,
                                    items: [
                                        {
                                        	layout: 'column',
                                            style: 'padding-right: 5px; padding-bottom: 5px; padding-left: 5px; ',
                                            labelWidth: 150,
                                            items: [                                            	
                                            	{
                        							columnWidth: 0.50
                        							,layout: 'form'
                        							,items: [
                        								_fields['LotIdLabel']
                        							]
                        						},
                        						{                        							
                        							columnWidth: 0.50
                        							,layout: 'form'
                        							,items: [
                        								_fields['OriginalAmountLabel']
                        								,_fields['DepletedAmountLabel']
                        								,_fields['BalanceLabel']
                        							]
                        						}
                                              ]
                                          }
                                        ]
                                }
        					]
        				})				
						]
				}),
		screenButtons : {
			items : [ _buttons['closeScreenButton']
			]
		}
	}
}
