/*********************************************************************************************
 * @file	RDSPNotionalActivity.Resources.js
  * @author	Tomasz Przada
 * @desc	Resources JS file for RDSPNotionalActivity.
 *********************************************************************************************/
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 835;
	var _layoutWidth = 750; 
	var _searchIDFieldWidth = 275;
	var _searchIDFieldPopupWidth = 230;
	var _reportingFFIFieldPopupWidth = 310;
	var _respWidth = 125;
	var _MARKET_CANADA = "CANADA";
	var _MARKET_LUX = "LUX";
	
	

	// **** buttons ****
	var _buttons = {
		rdspTransferScreenButton: new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['RDSPTransfer']
					,disabled: true
					,handler: function(){
						_controller.clickHandle_RdspTransfer();
					}
				}
			)
		,notionalBalanceScreenButton :new DesktopWeb.Controls.ScreenButton(
				{
					itemId : 'notionalBalanceBtnScreen',
					text: _translationMap['NotionalBalances']
					,handler: function(){
						_controller.clickHandle_RdspNotionalBalance();
					}
				}
			)
	,closeScreenButton : new DesktopWeb.Controls.ScreenButton(
			{
				text: _translationMap['Close']
				,handler: function(){
					DesktopWeb.Util.cancelScreen();
				}
			}
		)
	}
	
	

	// **** fields ****
	var _fields = {
			fromLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['From'],
			width : 10
		})
		,FromField: new DesktopWeb.Controls.DateField({
				fieldLabel: _translationMap['From']
				,width : 150
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,maxValue : new Date()
		}),
		toLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['To'],
			width : 10
		})
		,ToField: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['To']
				,width : 150
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,maxValue : new Date()
		}),
		BeneficaryNameLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['BeneficiaryName'],
			width : 200
		}),
		
		Label : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['TransactionType'],
			width : 50
		}),
		TransactionTypeField: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap["TransactionType"]
			,editable: true
			,autoSelect: true
			,width: 150
			,listeners : {
				select : function( combo, record, index ){

				_controller.setDescList(record.data.code);

				}
			}
		}),
		DescriptionLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['Description'],
			width : 50
		}),
		DescriptionField: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Description']
			,editable: true
			,autoSelect: true
			,width: 150
		}),
		TransactionNumberField: new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['TransactionNumber'],
			style : 'padding-left:5px;text-align:right;',
			width : 150,
			listeners : {
				change : function(){
					// if not empty disable other fields
					if(this.getValue()) {
						_fields['TransactionTypeField'].disable();
						_fields['DescriptionField'].disable();
						_fields['FromField'].disable();
						_fields['ToField'].disable();
						
						
					} else {
						_fields['TransactionTypeField'].enable();
						_fields['DescriptionField'].enable();
						_fields['FromField'].enable();
						_fields['ToField'].enable();
						
					}
				
				}
			}
		}),
		ContributionAmount : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['ContributionAmount'],
			width : 150,
			hidden : true		
		})
	,
	GrantAmount : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['GrantAmount'],
		width : 150,
		hidden : true	
	})
	,
	GrantPaymentDate : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['GrantPaymentDate'],
		width : 150,
		hidden : true
	})
	,
	BondAmount : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['BondAmount'],
		width : 150,
		hidden : true
	})
	,
	BondPaymentDate : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['BondPaymentDate'],
		width : 150,
		hidden : true
	})
	,
	RspAmount : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['RspAmount'],
		width : 150,
		hidden : true
	})
	,
	RespAmount : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['RespAmount'],
		width : 150,
		hidden : true
	})
	,
	RolloverAmount : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['RolloverAmount'],
		width : 150,
		hidden : true
	})
	,
	PaymentDate : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['PaymentDate'],
		width : 150,
		hidden : true
	})
	,
	AssociatedGrantTransactionNumber : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['AssociatedGrantTransactionNumber'],
		width : 150,
		hidden : true
	})
	,
	AssociatedGrantAmount : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['AssociatedGrantAmount'],
		width : 150,
		hidden : true
	})
	};
		var _grids = {
		RDSPTransactionHistoryDetailsGrid : new DesktopWeb.AdvancedControls.GridPanel({
		width: _layoutWidth-15
		,autoScroll: true
		,height: 300
		,store: new Ext.data.XmlStore(
				{
					record: 'transaction'
					,fields: [
						'transactionId',
						'transactionType', 'description'
						, 'tradeDate','transNumber', 'notionalAmount',
						'transactionStatus', 'ESDCTransID', 'ESDCTransStatus','iFastTransactionType','depositCode','redemptionCode'
					]
		
				}
			)
		
		,selModel: new Ext.grid.RowSelectionModel(
			{
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							//console.log(record.data);
							_controller.getNotionalDetails(record.data)
							
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
				//,
				,{header: _translationMap['TransactionType'], id:'transactionType', dataIndex: 'iFastTransactionType',width: 30
					,renderer: function(val, metaData, record){return _controller.getTransactionTypeValue(val);}
				}
				,{header: _translationMap['Description'], id:'description', dataIndex: 'description', width: 30
					,renderer: function(val, metaData, record){return _controller.getDescription(record);} }
				,{header: _translationMap['TradeDate'], id:'tradeDate', dataIndex: 'tradeDate', width: 30}
				,{header: _translationMap['TransNumber'], id:'transNumber', dataIndex: 'transNumber', width: 30}
				,{header: _translationMap['NotionalAmount'], id:'notionalAmount', dataIndex: 'notionalAmount',width: 30 }
				,{header: _translationMap['TransactionStatus'], id:'transactionStatus', dataIndex: 'transactionStatus',width: 30
				, renderer: function(val, metaData, record){return _controller.getTransactionStatusDescription(val);} 
				}
				,{header: _translationMap['ESDCTransID'], id:'ESDCTransID', dataIndex: 'ESDCTransID',width: 30 }
				,{header: _translationMap['ESDCTransStatus'], id:'ESDCTransStatus', dataIndex: 'ESDCTransStatus',width: 30
				, renderer: function(val, metaData, record){return _controller.getEsdcTransStatusDescription(val);}}
				,	{width: 0, id:'iFastTransactionType', dataIndex: 'iFastTransactionType',hidden: true, height: 15}
				,{width: 0, id:'depositCode', dataIndex: 'depositCode',hidden: true, height: 15}
				,{width: 0, id:'redemptionCode', dataIndex: 'redemptionCode',hidden: true, height: 15}
				
			]
		})
		,buttons: [
			new DesktopWeb.Controls.ActionButton({
				itemId: 'inventoryBtn'
				,text: _translationMap['Inventory']
				,handler: function(){}
			})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'moreBtn'
				,text: _translationMap['More']
				,handler: function(){}
			})
		]

	

	}
	
	
	)
	}
	
	

		


	
	

	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		,layoutHeight: _layoutHeight
		,fields: _fields
		,buttons: _buttons
		,grids:_grids
		,layout: new Ext.Container({
			height: _layoutHeight
			, width: _layoutWidth
			, items: [
				{
					layout: 'column'
					,labelWidth: 125
					,items: [
						{
							columnWidth: 1
							,layout: 'form'
							,items: [
								_fields['BeneficaryNameLabel']
							]
						},
						{
					
							columnWidth: 1.0
							,layout: 'form'
							,items: [
								_fields['TransactionNumberField']
								
							]
						},
						{
							
							columnWidth: 0.5
							,layout: 'form'
							,items: [
								_fields['TransactionTypeField']
								
							]
						}
						,{
							columnWidth: 0.50
							,layout: 'form'
							,items: [
								_fields['FromField']
								
							]
						},
						{
							
							columnWidth: 0.50
							,layout: 'form'
							,items: [
								_fields['DescriptionField']
							]
						}
						,{
							columnWidth: 0.40
							,layout: 'form'
							,items: [
								_fields['ToField']
							]
						}	
						,{
                            columnWidth: 0.1,
                            layout: 'form',
                            items: [ new DesktopWeb.Controls.ActionButton({
								itemId: 'refreshBtn'
									,text: _translationMap['Refresh']
									,handler: function(){
										
										_controller.filterGrid();
										
									}
								}) ]
                        }
					]
					
				},
				new Ext.Container({
					height: _layoutHeight
					, width: _layoutWidth
					, items: [	
						{
						xtype: 'fieldset'
						,title: _translationMap['RDSPTransactionHistoryDetails']
						,items:[
	                        {
							layout: 'column'
							,items: [_grids['RDSPTransactionHistoryDetailsGrid']]
							}
							
						]
						
						},
						{
                            xtype: 'fieldset',
                            title: _translationMap['NotionalDetails'],
                            id: 'notionalDetailsFieldSet',
                    		hidden : true,
                            items: [
                                {
                                	layout: 'column',
                                    style: 'padding-right: 5px; padding-bottom: 5px; padding-left: 5px; ',
                                    labelWidth: 165,
                                    items: [
                                    	
                                    	{
                							columnWidth: 0.50
                							,layout: 'form'
                							,items: [
                								_fields['ContributionAmount']
                								,_fields['GrantAmount']
                								,_fields['BondAmount']
                								
                								
                							]
                						},
                						{
                							
                							columnWidth: 0.50
                							,layout: 'form'
                							,items: [
                								_fields['RolloverAmount']
                								,_fields['RspAmount']
                								,_fields['RespAmount']
                								,_fields['GrantPaymentDate']
                								,_fields['BondPaymentDate']
                							]
                						}
                                 
                                      ]
                                }
                               
                                ]
                        },
                        {
                            xtype: 'fieldset',
                            title: _translationMap['AssociatedGrantInformation'],
                            id: 'assocGrantFieldSet',
                        	layout: 'column',
                            hidden : true,
                            items: [
                                {
                                    layout: 'form',
                                    style: 'padding-right: 5px; padding-bottom: 5px; padding-left: 5px;',
                                    labelWidth: 165,
                                    items: [
                                    	{
                							columnWidth: 0.50
                							,layout: 'form'
                							,items: [
                								_fields['AssociatedGrantTransactionNumber']
                								,_fields['PaymentDate']
                								
                								
                							]
                						},
                						{
                							
                							columnWidth: 0.50
                							,layout: 'form'
                							,items: [
                								_fields['AssociatedGrantAmount']
                							
                							]
                						}
                                    	
                                    ]
                                }
                            ]
                        }
					]
				})
		]
		})
			,screenButtons: {
			items:[
				_buttons['rdspTransferScreenButton']
				,_buttons['notionalBalanceScreenButton']
				,_buttons['closeScreenButton']
			]
		}
	}
}