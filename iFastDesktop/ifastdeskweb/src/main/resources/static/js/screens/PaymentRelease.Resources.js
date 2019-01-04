/*********************************************************************************************
 * @file	PaymentRelease.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Payment Release screen
 *********************************************************************************************/
/*
 *  History :
 *
 *  19 Jun 2017 Narin Suanlamyai
 *		- Initail version from converting XSL version to ExtJS version
 *
 *  23 Mar 2018 Supareuk S. CHG0054159 INC0040826
 *      - Added ability to display total record on the screen
 */

DesktopWeb.ScreenResources = function (ctrlr) {
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 575;
	var _layoutWidth = 720;
	var _labelWidthFirstColumn = 90;
	var _labelWidthSecondColumn = 95;
	var _labelWidthGovFileDetails = 150;

	// **** buttons ****
	var _buttons = {
		searchBtn : new DesktopWeb.Controls.ActionButton({
			text : _translationMap['Search'],
			itemId : 'searchBtn',
			style : "float:right;",
			disabled : true,
			listeners : {
				click : function () {
					_controller.clickHandleSearchBtn();
				}
			}
		}),
		refreshBtn : new DesktopWeb.Controls.ActionButton({
			text : _translationMap['Refresh'],
			style : 'padding:4px;',
			itemId : 'refreshBtn',
			disabled : true,
			listeners : {
				click : function () {
					_controller.clickRefreshBtn();
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
			allowBlank : false
		}),

		batchStatus : new DesktopWeb.Controls.SMVComboBox({
			fieldLabel : _translationMap['BatchStatus'],
			width : 160,
			editable : true,
			allowBlank : false
		}),
		searchValue : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['Value'],
			allowBlank : false,
			width : 160,
			editable : true

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
		batchPymtGrid : new DesktopWeb.AdvancedControls.GridPanel({
			id : 'batchPymtGrid',
			width : _layoutWidth - 12,
			autoScroll : true,
			height : 175,
			autoExpandColumn : 'fileNm',
			buttonAlign : 'left',
			reset : function () {
				this.getStore().removeAll();
				this.disableAllButtons();
			},
			store : new Ext.data.XmlStore({

				record : 'PymtBatchDetails',
				fields : ['pymtBatchID', 'pymtFor', 'stat', 'payDate', 'fileNm', 'pymtCntr', 'achProc', 'recId', 'procDate', 'userNm', 'modDate', 'modID'],
				listeners : {
					load : function (store, records) {
						Ext.each(records, function (record) {
							record.data.payDate = DesktopWeb.Util.getDateDisplayValue(record.data.payDate);
							record.data.procDate = DesktopWeb.Util.getDateDisplayValue(record.data.procDate);
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				} //listeners

			}),
			selModel : new Ext.grid.RowSelectionModel({
				singleSelect : true,
				listeners : {
					rowselect : function (selModel, index, record) {							
						if (selModel) {						
							_controller.updateActionButtons('batchPymtGrid');
							_controller.reloadPayment(record.data, false);
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
						dataIndex : 'errMsg',
						width : 25,
						renderer : function (val) {
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}, {
						header : _translationMap['PaymentFor'],
						width : 125,
						id : 'pymtFor',
						dataIndex : 'pymtFor'
					}, {
						header : _translationMap['Status'],
						width : 100,
						id : 'stat',
						dataIndex : 'stat'
					}, {
						header : _translationMap['PaymentDate'],
						width : 100,
						dataIndex : 'payDate'
					}, {
						header : _translationMap['PaymentFileName'],
						width : 100,
						id : 'fileNm',
						dataIndex : 'fileNm'
					}, {
						header : _translationMap['Counter'],
						width : 100,
						dataIndex : 'pymtCntr'
					}, {
						header : _translationMap['ACHProcessor'],
						width : 100,
						dataIndex : 'achProc'
					}
				]
			}),
			buttons : [
				new DesktopWeb.Controls.Label({
					itemId: "batchPymtPageNumber",
					text: "" // "Page Number 1 Loading..."
				}), '->',
				new DesktopWeb.Controls.ActionButton({
					itemId : 'moreBtn',
					text : _translationMap['More'],
					disabled : true,
					handler : function () {
						_controller.clickHandleMoreBtn('batchPymtGrid');
					}
				})
			]
		}),
		paymentsGrid : new DesktopWeb.AdvancedControls.GridPanel({
			id : 'paymentsGrid',
			width : _layoutWidth - 12,
			autoScroll : true,
			height : 175,
			autoExpandColumn : 'payAmt',
			buttonAlign : 'left',
			reset : function () {
				this.getStore().removeAll();
				this.disableAllButtons();
			},
			store : new Ext.data.XmlStore({
				record : 'ConsolidatedPaymentDetail',
				fields : ['pymtId', 'pymtStat', 'pymtFor', 'consolInd', 'curr', 'payAmt', 'statUpd', 'recId', 'version']

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
						dataIndex : 'errMsg',
						width : 25,
						renderer : function (val) {
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}, {
						header : _translationMap['PaymentID'],
						width : 125,
						dataIndex : 'pymtId'
					}, {
						header : _translationMap['Status'],
						width : 100,
						dataIndex : 'pymtStat'
					}, {
						header : _translationMap['ConsolidateIndicator'],
						width : 100,
						dataIndex : 'consolInd'
					}, {
						header : _translationMap['Currency'],
						width : 125,
						dataIndex : 'curr'
					}, {
						header : _translationMap['Amount'],
						width : 125,
						dataIndex : 'payAmt',
						id : 'payAmt'
					}
				]
			}),
			buttons : [
				new DesktopWeb.Controls.Label({
					itemId: "paymentPageNumber",
					text: "" //"Page Number 2 Loading..."
				}),'->',
				new DesktopWeb.Controls.ActionButton({
					itemId : 'genBAFFBtn',
					text : _translationMap['GenerateBAFFFile'],
					disabled : false,
					handler : function () {
						_controller.openGenBAFFPopup();
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'adminBtn',
					text : _translationMap['Admin'],
					disabled : false,
					handler : function () {
						_controller.openAdminPopup();
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'moreBtn',
					text : _translationMap['More'],
					disabled : true,
					handler : function () {
						_controller.clickHandleMoreBtn('paymentsGrid');
					}
				})
			]
		})
	}

	// **** popups ****
	var _popups = {
		genBAFFPopup : new DesktopWeb.AdvancedControls.PopupWindow({
			width : 350,
			closeAction : 'hide',
			pymtBatchID : '',
			title : _translationMap['GenerateBAFFFile'],
			modal : true,
			defaults : {
				border : false
			},
			items : [{
					layout : 'auto',
					style : 'padding:4px',
					defaults : {
						border : false,
						labelWidth : 80,
						layout : 'form'
					},
					items : [
						new DesktopWeb.Controls.Radio({
							boxLabel : _translationMap['RunNow'],
							name : "genBAFFSched",
							itemId : 'runNow',
							checked : true,
							listeners : {
								check : function (ctl, val) {
									if (val) {
										_controller.doBatchCheck();
									}
								}
							}
						}), new DesktopWeb.Controls.Radio({
							boxLabel : _translationMap['RunSchedule'],
							name : "genBAFFSched",
							itemId : 'runSchedule',
							listeners : {
								check : function (ctl, val) {
									if (val) {
										_controller.doBatchCheck();
									}
								}
							}
						}), {
							xtype : 'fieldset',
							style : 'margin-left: 20px;',
							border : false,
							items : [{
									layout : 'column',
									style : 'padding-top:10px',
									border : false,
									defaults : {
										border : false,
										layout : 'form'
									},
									items : [{
											columnWidth : 0.55,
											labelWidth : 48,
											items : [
												new DesktopWeb.Controls.DateField({
													fieldLabel : _translationMap['RunOn'],
													itemId : "runOn",
													allowBlank : false,
													format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
												})
											]
										}, {
											columnWidth : 0.45,
											labelWidth : 20,
											items : [												
												new Ext.form.TimeField({
													fieldLabel : _translationMap['At'],
													itemId : "runAt",
													emptyText : _translationMap['HHMM'],
													format : "H:i",
													altFormats : "H:i",
													minValue : "00:00",
													maxValue : "23:59",
													invalidText : _translationMap['InvalidTimeFormat'],
													allowBlank : false,
													width : 75
												})
											]
										}
									]
								}
							]
						}
					]
				}
			],

			buttons : [
				new DesktopWeb.Controls.ActionButton({
					text : _translationMap['OK'],
					handler : function () {
						_controller.generateBatch(_popups['genBAFFPopup'].getData());
					}
				}), new DesktopWeb.Controls.ActionButton({
					text : _translationMap['Cancel'],
					handler : function () {
						_popups['genBAFFPopup'].hide();
					}
				})
			],
			init : function (pymtBatchID) {
				this.pymtBatchID = pymtBatchID;
				_controller.initBatch();
			},
			getData : function () {
				var data = {};
				data['pymtBatchId'] = this.pymtBatchID;

				if (this.getField("runNow").getValue()) {
					data['runNow'] = 'yes';
				} else {
					data['runNow'] = 'no';
				}
				data['runOn'] = this.getField('runOn').getValue();
				data['runTime'] = this.getField('runAt').getValue();

				return data;
			}
		}),
		admin : new DesktopWeb.AdvancedControls.PopupWindow({
			width : 395,
			closeAction : 'hide',
			modal : true,
			defaults : {
				border : false
			},
			items : [{
					layout : 'column',
					style : 'padding:4px',
					defaults : {
						border : false,
						labelWidth : 80
					},
					items : [{
							width : 185,
							layout : 'form',
							defaults : {
								width : 80
							},
							items : [
								new DesktopWeb.Controls.Label({
									itemId : 'userName',
									fieldLabel : _translationMap['Username']
								}), new DesktopWeb.Controls.Label({
									itemId : 'modUser',
									fieldLabel : _translationMap['ModUser']
								})
							]
						}, {
							width : 185,
							layout : 'form',
							defaults : {
								width : 80
							},
							items : [
								new DesktopWeb.Controls.Label({
									itemId : 'procDate',
									fieldLabel : _translationMap['ProcessDate']
								}), new DesktopWeb.Controls.Label({
									itemId : 'modDate',
									fieldLabel : _translationMap['ModDate'],
									value : 'test'
								})
							]
						}
					]
				}
			],
			buttons : [
				new DesktopWeb.Controls.ActionButton({
					text : _translationMap['OK'],
					handler : function () {
						_popups['admin'].hide();
					}
				})
			],
			init : function (title, data) {
				this.setTitle(title);
				this.getField('procDate').setValue(data['procDate']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['userName']);
				this.getField('modUser').setValue(data['modUser']);
			}
		})
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
							columnWidth : 0.50,
							autoHeight : true,
							labelWidth : _labelWidthFirstColumn,
							items : [
								_fields['searchFor'],
								_fields['searchValue'],
								_fields['paymentFor'],
								_fields['batchStatus']
							]
						}, {
							// Row#1 Col#2							
									// Row#1 Col#2
									layout : 'form',
									columnWidth : 0.50,
									autoHeight : true,
									labelWidth : _labelWidthSecondColumn,
									items : [
										_fields['startDate'],
										_fields['toDate']
										,{
										layout: 'column'																		
										,border: false
										,style : 'float:right;text-align:right'
										,defaults: {border: false, layout: 'form'}
										,items: [
											{
												columnWidth: 0.43
												,items: [
													_buttons['searchBtn']
												]
											}
											,{
												columnWidth: 0.17
												,items: [
													_buttons['refreshBtn']
												]
											}
										]
									}
									]
								}
							]
						
				}, {
					xtype : 'fieldset',
					title : _translationMap['PaymentBatch'],
					layout : 'column',
					style : 'margin-bottom:10px',
					width : _layoutWidth,
					items : [
						_grids['batchPymtGrid']
					]
				}, {
					xtype : 'fieldset',
					title : _translationMap['Payments'],
					layout : 'column',
					style : 'margin-bottom:10px;',
					width : _layoutWidth,
					autoHeight : true,
					items : [
						_grids['paymentsGrid']
					]
				}
			]
		}),
		screenButtons : [
			new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Close'],
				handler : function () {
					DesktopWeb.Util.cancelScreen();
				}
			})
		]
	}
}


