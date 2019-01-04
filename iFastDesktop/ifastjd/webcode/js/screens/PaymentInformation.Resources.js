/*********************************************************************************************
 * @file	PaymentInformation.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Payment Information screen
 *********************************************************************************************/
/*
 *  History :
 *
 *  19 Jun 2017 Narin Suanlamyai / Gomoot T.
 *		- Initail version from converting XSL version to ExtJS version
 *    Note: 
 *    - PaymentFor get list from SearchTypeFilter 
 *
 *    When user select Search Using , fields will be enabled only when select 
 *
 *    PaymentFor : PaymentFor (listener limitSearchField) , PayType (listener limitSearchField),
 *								Broker, Branch, SalesRep, Account,  Status , From Date, ToDate 
 *		Account    : searchValue (for account input), From Date, ToDate 
 *		Payment Date : PaymentFor, From Date, ToDate 
 *		Payment Id   : searchValue 
 *		Pay Entity   : PaymentFor, Broker, Branch, SalesRep, From Date, ToDate 
 *		Transaction Number:  searchValue
 *		
 *  23 Mar 2018 Supareuk S. CHG0054159 INC0040826
 *      - Added ability to display total record on the screen
 */

DesktopWeb.ScreenResources = function (ctrlr) {
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 615;
	var _layoutWidth = 720;
	var _labelWidthFirstColumn = 80;
	var _labelWidthSecondColumn = 70;

	// **** buttons ****
	var _buttons = {
		searchBtn : new DesktopWeb.Controls.ActionButton({
			text : _translationMap['Search'],
			disabled : true,
			listeners : {
				click : function () {
					_controller.clickHandleSearchBtn();
				}
			}
		}),
		refreshBtn : new DesktopWeb.Controls.ActionButton({
			text : _translationMap['Refresh'],
			disabled : true,
			listeners : {
				click : function () {
					_controller.clickHandleRefreshBtn();
				}
			}
		})
	}

	// **** fields ****
	var _fields = {
		searchFor : new DesktopWeb.Controls.SMVComboBox({
			fieldLabel : _translationMap['SearchFor'],
			width : 160,
			editable : true,
			allowBlank : false,
			listeners : {
				select : function () {
					_controller.handleSearchChange();
				},
				change : function (fld, newValue) {
					if (newValue == "") {
						_controller.handleSearchChange();
					}
				}
			}
		}),
		paymentFor : new DesktopWeb.Controls.SMVComboBox({
			fieldLabel : _translationMap['PaymentFor'],
			width : 160,
			editable : true,
			//allowBlank : false,
			listeners : {
				select : function () {
					_controller.handlePaymentForChange();
				},
				change : function (fld, newValue) {
					if (newValue == "") {
						_controller.handlePaymentForChange();
					}
				}
			}
		}),
		paymentType : new DesktopWeb.Controls.SMVComboBox({
			fieldLabel : _translationMap['PaymentType'],
			width : 160,
			editable : true,			
			listeners : {
				select : function () {
					_controller.handlePayTypeChange();
				},
				change : function (fld, newValue) {
					if (newValue == "") {
						_controller.handlePayTypeChange();
					}
				}
			}
		}),
		paymentStatus : new DesktopWeb.Controls.SMVComboBox({
			fieldLabel : _translationMap['PaymentStatus'],
			width : 160,
			editable : true/*,
			allowBlank : false*/
		}),
		searchValue : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['Value'],
			allowBlank : false,
			width : 160,
			editable : true

		}),
		accountFld : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['PaymentAccount'],
			width : 160,
			//TAO allowBlank : false,
			hidden : false
		}),
		brokerFld : new DesktopWeb.Controls.SuggestField({
			fieldLabel : _translationMap['Broker'],
			emptyText : _translationMap['All'],
			smartview : 'brokerSearch',			
			fields : ['displayValue', 'agencyCode'],
			valueField : 'agencyCode',
			width : 280,
			//allowBlank : false,
			listeners:{
				populated: function(){
					_fields['branchFld'].enableField();
					_fields['branchFld'].enable();
				}
				,cleared: function(){
					 _fields['branchFld'].reset();
					 _fields['branchFld'].disableField();
					 _fields['branchFld'].disable();
					 _fields['slsrepFld'].reset();
					 _fields['slsrepFld'].disableField();
					 _fields['slsrepFld'].disable();
				}
			}
		
		}),
		branchFld : new DesktopWeb.Controls.SuggestField({
			fieldLabel : _translationMap['Branch'],
			emptyText : _translationMap['All'],
			smartview : 'branchSearch',
			fields : ['displayValue', 'branch'],
			addtlSearchParams : [{
					name : 'agencyCode',
					valueFn : function () {
						return _fields['brokerFld'].getValue();
					}
				}
			],
			valueField : 'branch',
			width : 280,
			disabled : true,
			//allowBlank : false,
			listeners:{
				populated: function(){
					_fields['slsrepFld'].enableField();
					_fields['slsrepFld'].enable();
				}
				,cleared: function(){					 
					 _fields['slsrepFld'].reset();
					 _fields['slsrepFld'].disableField();
					 _fields['slsrepFld'].disable();
				}
			}
		}),
		slsrepFld : new DesktopWeb.Controls.SuggestField({
			fieldLabel : _translationMap['SalesRep'],
			emptyText : _translationMap['All'],
			smartview : 'salesRepSearch',
			fields : ['displayValue', 'agentCode'],
			addtlSearchParams : [{
					name : 'agencyCode',
					valueFn : function () {
						return _fields['brokerFld'].getValue();
					}
				}, {
					name : 'branch',
					valueFn : function () {
						return _fields['branchFld'].getValue();
					}
				}
			],
			valueField : 'agentCode',
			width : 280,
				//allowBlank : false,
			disabled : true
		
		}),
		startDate : new DesktopWeb.Controls.DateField({
			fieldLabel : _translationMap['FromDate'],
			width : 100,
			allowBlank : false,
			format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		}),
		toDate : new DesktopWeb.Controls.DateField({
			fieldLabel : _translationMap['ToDate'],
			width : 100,
			allowBlank : false,
			format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
	}

	// **** grids ****
	var _grids = {
		conPymtGrid : new DesktopWeb.AdvancedControls.GridPanel({
			width : _layoutWidth - 12,
			autoScroll : true,
			height : 175,
			autoExpandColumn : 'conIndc',
			buttonAlign : 'left',
			reset : function () {
				this.getStore().removeAll();
				this.disableAllButtons();
			}
		,
			store : new Ext.data.XmlStore({
				record : 'ConsolidatedPaymentDetail',
				fields : ['errMsg', 'pymtId', 'pymtStat', 'pymtFor', 'tapeDate', 'consolInd', 'curr',
				'payAmt', 'batchID', 'statUpd', 'recId', 'version', 'runMode', 'pymtStatMsg' , 'ListNode' , 'ListXML'],
				listeners : {
					load : function (store, records) {
						Ext.each(records, function (record) {
							record.data.tapeDate = DesktopWeb.Util.getDateDisplayValue(record.data.tapeDate);
							
							record.data.ListNode = IFDS.Xml.getNode(store.reader.xmlData,
														"/*//ConsolidatedPaymentDetail[recId='" + record.data.recId
																+ "']//List[@id='ValidStatuses']");	
              if (!!record.data.ListNode)																
							record.data.ListXML =  IFDS.Xml.serialize(record.data.ListNode);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			}),
			selModel : new Ext.grid.RowSelectionModel({
				singleSelect : true,
				listeners : {
					rowselect : function (selModel, index, record) {

						if (selModel) {
							_controller.updateActionButtons('conPymtGrid');
							_controller.selectConsolidatedPayment(record.data, false);
						}
					}
				}
			}),
			colModel : new Ext.grid.ColumnModel({
				defaults : {
					menuDisabled : true,
					sortable : false
				},
				columns : [{
						header : _translationMap['Status'],
						dataIndex : 'pymtStat',
						width : 100,			
						tooltip :"5555",
						renderer: function(val, metadata, record)
						{
							if (!!record.data['pymtStatMsg'])
									metadata.attr = 'qtip="' + record.data['pymtStatMsg'] + '"';
						  return val; 
					 }
					}, {
						header : _translationMap['PaymentID'],
						dataIndex : 'pymtId',
						width : 100
					}, {
						header : _translationMap['PaymentDate'],
						dataIndex : 'tapeDate',
						width : 80
					}, {
						header : _translationMap['ConsolidateIndicator'],
						dataIndex : 'consolInd',
						id : 'conIndc'
					}, {
						header : _translationMap['Amount'],
						dataIndex : 'payAmt',
						width : 80
					}, {
						header : _translationMap['Currency'],
						dataIndex : 'curr',
						width : 75
					}, {
						header : _translationMap['BatchID'],
						dataIndex : 'batchID',
						width : 100
					}, {
						header : _translationMap['TransType'],
						dataIndex : 'pymtFor',
						width : 50
					}
				]
			}),
			buttons : [
				new DesktopWeb.Controls.Label({
					itemId: "pageNumber"
				}), new DesktopWeb.Controls.Checkbox({
					boxLabel : _translationMap['VerifyAll'],
					//name : "pymtAction",
					itemId : "vrfAll"
					,listeners: {
						check: function(cb, checked)
						{
							_controller.checkedVerifyAll(checked);
						}
					}
				}), new DesktopWeb.Controls.Checkbox({
					boxLabel : _translationMap['ApproveAll'],
				//	name : "pymtAction",
					itemId : "appvAll"
					,listeners: {
						check: function(cb, checked)
						{
							_controller.checkedApproveAll(checked);
						}
					}
				}), new DesktopWeb.Controls.Checkbox({
					boxLabel : _translationMap['StopAll'],
					//name : "pymtAction",
					itemId : "stpAll",
					listeners: {
						check: function(cb, checked)
						{
							_controller.checkedStopAll(checked);
						}
					}
				}), '->'
				, new DesktopWeb.Controls.ActionButton({
					itemId : 'modifyBtn',
					text : _translationMap['Modify'],
					handler : function () {
						_controller.openModifyPopup();
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'historyBtn',
					text : _translationMap['Historical'],
					disabled : true,
					handler : function () {
						_controller.clickHandleHistoricalBtn();
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'moreBtn',
					text : _translationMap['More'],
				  disabled : true,
					handler : function () {
						_controller.clickHandleMoreBtn('conPymtGrid');
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'resetBtn',
					text : _translationMap['Reset'],
					disabled : true,
					handler : function () {
						_controller.clickResetBtn();
					}
				})
			]
		}),
		transGrid : new DesktopWeb.AdvancedControls.GridPanel({
			width : _layoutWidth - 12,
			autoScroll : true,
			height : 175,
			buttonAlign : 'left',
			reset : function () {
				this.getStore().removeAll();
				this.disableAllButtons();
			}
		 ,
			store : new Ext.data.XmlStore({
				record : 'PayReconTxnDetails',
				fields : ['errMsg', 'broker', 'branch', 'slsRep', 'shrHolder', 'acct', 'level', 'fund', 'class', 'tradeDt', 'settleDt', 'transType', 'transNum', 'amt', 'tapeDt', 'transID', 'runMode'],
				listeners : {
					load : function (store, records) {
						Ext.each(records, function (record) {
							record.data.tradeDt = DesktopWeb.Util.getDateDisplayValue(record.data.tradeDt);
							record.data.settleDt = DesktopWeb.Util.getDateDisplayValue(record.data.settleDt);
							record.data.tapeDt = DesktopWeb.Util.getDateDisplayValue(record.data.tapeDt);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			}),
			selModel : new Ext.grid.RowSelectionModel({
				singleSelect : true
			}),
			colModel : new Ext.grid.ColumnModel({
				defaults : {
					menuDisabled : true,
					sortable : false
				},
				columns : [{
						header : _translationMap['TransType'],
						dataIndex : 'transType',
						width : 80
					}, {
						header : _translationMap['Broker'],
						dataIndex : 'broker',
						width : 80
					}, {
						header : _translationMap['Amount'],
						dataIndex : 'amt',
						width : 80
					}, {
						header : _translationMap['Account'],
						dataIndex : 'acct',
						width : 80
					}, {
						header : _translationMap['ConsolidationLevel'],
						dataIndex : 'level',
						width : 100
					}, {
						header : _translationMap['TransNum'],
						dataIndex : 'transNum',
						width : 80
					}, {
						header : _translationMap['TradeDate'],
						dataIndex : 'tradeDt',
						width : 80
					}, {
						header : _translationMap['SettlementDate'],
						dataIndex : 'settleDt',
						width : 80
					}, {
						header : _translationMap['Fund'],
						dataIndex : 'fund',
						width : 80
					}, {
						header : _translationMap['Class'],
						dataIndex : 'class',
						width : 80
					}
				]
			}),
			buttons : [
				new DesktopWeb.Controls.Label({
					itemId : 'pageNumber'
				}), '->',
				new DesktopWeb.Controls.ActionButton({
					itemId : 'moreBtn',
					text : _translationMap['More'],
					disabled : true,
					handler : function () {
						_controller.clickHandleMoreBtn();
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'detailsBtn'
					, id : 'btnTransactionDetails'
				  , name : 'btnTransactionDetails',
					text : _translationMap['Details'],
					disabled : true,
					handler : function () {
						_controller.clickHandleDetailsBtn();
					}
				})
			]
		}),
		paymentsGrid : new DesktopWeb.AdvancedControls.GridPanel({
			width : _layoutWidth - 12,
			autoScroll : true,
			height : 175,
			buttonAlign : 'left',
			autoExpandColumn : 'amount',
			reset : function () {				
				this.getStore().removeAll();
				this.disableAllButtons();
			},
			store : new Ext.data.XmlStore({
				record : 'PayReconPayDetails',
				fields : ['errMsg', 'broker', 'branch', 'slsRep', 'shrHolder', 'acct', 'level', 'fund', 'class', 'tradeDt', 'settleDt', 'transType', 'transNum', 'amt', 'tapeDt', 'transID', 'runMode'],
				listeners : {
					load : function (store, records) {
						Ext.each(records, function (record) {
							record.data.tradeDt = DesktopWeb.Util.getDateDisplayValue(record.data.tradeDt);
							record.data.settleDt = DesktopWeb.Util.getDateDisplayValue(record.data.settleDt);
							record.data.tapeDt = DesktopWeb.Util.getDateDisplayValue(record.data.tapeDt);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			}),
			selModel : new Ext.grid.RowSelectionModel({
				singleSelect : true
			}),
			colModel : new Ext.grid.ColumnModel({
				defaults : {
					menuDisabled : true,
					sortable : false
				},
				columns : [{
						header : _translationMap['Broker'],
						dataIndex : 'broker',
						width : 125
					}, {
						header : _translationMap['Branch'],
						dataIndex : 'branch',
						width : 125
					}, {
						header : _translationMap['SalesRep'],
						dataIndex : 'slsRep',
						width : 125
					}, {
						header : _translationMap['Amount'],
						dataIndex : 'amt',
						id : 'amount'
					}, {
						header : _translationMap['Fund'],
						dataIndex : 'fund',
						width : 80
					}, {
						header : _translationMap['Class'],
						dataIndex : 'class',
						width : 80
					}
				]
			}),
			buttons : [
				new DesktopWeb.Controls.Label({
					itemId: "pageNumber"
				}), '->',
				new DesktopWeb.Controls.ActionButton({
					itemId : 'moreBtn',
					text : _translationMap['More'],
					disabled : true,
					handler : function () {
						_controller.clickHandleMoreBtn();
					}
				})
			]
		})
	}

	// **** popups ****
	var _popups = {
		consPymtPoup : new DesktopWeb.AdvancedControls.PopupWindow({
			width : 375,
			action : null,
			modal : true,
			defaults : {
				border : false
			},
			data : '',
			title : _translationMap['ConsolidatedPayments'] + " - " + _translationMap['Modify'],
			items : [{
					layout : 'form',
					style : 'padding:4px',
					labelWidth : 120,
					items : [
						new DesktopWeb.Controls.TextField({
							itemId : 'batchIDText',
							width : 200,
							fieldLabel : _translationMap['BatchID']
						}), new DesktopWeb.Controls.TextField({
							itemId : 'paymentIDText',
							width : 200,
							fieldLabel : _translationMap['PaymentID']
						}), new DesktopWeb.Controls.DateField({
							itemId : 'paymentDateText',
							fieldLabel : _translationMap['PaymentDate'],
							format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						}), new DesktopWeb.Controls.TextField({
							itemId : 'conIndcText',
							width : 200,
							fieldLabel : _translationMap['ConsolidateIndicator']
						}), new DesktopWeb.Controls.TextField({
							itemId : 'amountText',
							width : 200,
							fieldLabel : _translationMap['Amount']
						}), new DesktopWeb.Controls.SMVComboBox({
							itemId : 'statusFld',
							width : 200,
							fieldLabel : _translationMap['Status'],
							allowBlank : true,
							editable : false
						})
					]
				}
			]
			,
			buttons : [
				new DesktopWeb.Controls.ActionButton({
					text : _translationMap['OK'],
					handler : function () {
						_popups['consPymtPoup'].save();
					}

				}), new DesktopWeb.Controls.ActionButton({
					text : _translationMap['Cancel'],
					handler : function () {
						_popups['consPymtPoup'].hide();
					}
				})
			]
			/**/
			,init: function(record) {
				//consPymtPoup
				data = record.data;
				this.getField('batchIDText').setValue(record.data.batchID);
				this.getField('paymentIDText').setValue(record.data.pymtId);				
				this.getField('amountText').setValue(record.data.payAmt);
				this.getField('conIndcText').setValue(record.data.consolInd);
				this.getField('paymentDateText').setValue(record.data.tapeDate);
				this.getField('statusFld').loadData(record.data.ListNode);
				
				this.getField('batchIDText').disableField();
				this.getField('paymentIDText').disableField();				
				this.getField('amountText').disableField();
				this.getField('conIndcText').disableField();
				this.getField('paymentDateText').disableField();
				
				var record = this.getField('statusFld').findRecord('value', record.data.pymtStat);
				var code =	 (record != null ? record.get('code') : null);			
				this.getField('statusFld').setValue(code);
				//record.data.tapeDate
			}
			,save: function() {
				var saveData = {}				
				saveData['runMode'] = _controller.MOD
				saveData['newStatus'] = this.getField('statusFld').getValue();		
				saveData['pymtStat'] = this.getField('statusFld').getValueDesc();		
				
				_controller.savePopup(saveData);
				_popups['consPymtPoup'].hide();
			}

		}),
		history : new DesktopWeb.AdvancedControls.HistoryPopup()
	}

	// PUBLIC ITEMS
	return {
		layoutWidth : _layoutWidth,
		layoutHeight : _layoutHeight,
		buttons : _buttons,
		fields : _fields,
		grids : _grids,
		popups : _popups,
		layout : new Ext.Container({
			height : _layoutHeight,
			width : _layoutWidth,
			items : [{
					itemId : 'mainLayout',
					xtype : 'fieldset',
					title : _translationMap['PaymentReleaseSearch'],
					layout : 'column',
					style : 'margin-bottom:20px',
					width : _layoutWidth,
					items : [{
							// Row#1 Col#1
							layout : 'form',
							columnWidth : 0.45,
							autoHeight : true,
							labelWidth : _labelWidthFirstColumn,
							items : [
								_fields['searchFor'], _fields['paymentFor'], _fields['searchValue'], _fields['paymentType'], _fields['paymentStatus'], _fields['accountFld']
							]
						}, {
							// Row#1 Col#2
							layout : 'form',
							columnWidth : 0.55,
							autoHeight : true,
							labelWidth : _labelWidthSecondColumn,
							items : [
								_fields['brokerFld'], _fields['branchFld'], _fields['slsrepFld'], {
									layout : 'column'
									//,style: 'padding-top:10px'
								,
									border : false,
									defaults : {
										border : false,
										layout : 'form',
										labelWidth : _labelWidthSecondColumn
									},
									items : [{
											columnWidth : 0.50,
											items : [
												_fields['startDate']
											]
										}, {
											columnWidth : 0.50,
											labelWidth : _labelWidthSecondColumn - 10,
											items : [
												_fields['toDate']
											]
										}
									]
								}, {
									layout : 'column',
									border : false,
									defaults : {
										border : false,
										layout : 'form'
									},
									items : [{
											columnWidth : 0.60,
											items : [

											]
										}, {
											columnWidth : 0.17,
											items : [
												_buttons['searchBtn']
											]
										}, {
											columnWidth : 0.23,
											items : [
												_buttons['refreshBtn']
											]
										}
									]
								}
								//,_buttons['searchBtn']
							]
						}
					]
				}, {
					xtype : 'fieldset',
					itemId : 'conPymtLayout',
					title : _translationMap['ConsolidatedPayments'],
					layout : 'column',
					style : 'margin-bottom:10px',
					width : _layoutWidth,
					items : [
						_grids['conPymtGrid']
					]
				}
			, {
					xtype : 'fieldset',
					id : 'childLayout',
					title : _translationMap['Transactions'],
					layout : 'column',
					style : 'margin-bottom:10px;',
					width : _layoutWidth,
					autoHeight : true,
					items : [
						_grids['transGrid'],
						_grids['paymentsGrid']
					]
				}
			]
		}),
		screenButtons : [
			new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['OK'],
				itemId : 'ok',
				id : 'ok',
				handler: function(){
					_controller.clickOK();
				} 
			}), new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Cancel'],
				handler : function () {
					DesktopWeb.Util.cancelScreen();
				}
			})
		]
	}
}
