/*******************************************************************************
 * @file WhtRatesMaint.Resources.js
 * @author Hatthaseriphong, Nopphawan
 * @desc Resources JS file of the Withholding Tax Rates Maintenance
 ******************************************************************************/
/*
 * History :
 * 
 * 05 Jan 2018 N. Hatthaseriphong P0274848 Withholding Tax Rates Maintenance 
 *             - Created
 * 
 */

DesktopWeb.ScreenResources = function(ctrlr) {
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _controller = ctrlr;

	// ****** content dimensions ******
	var _layoutHeight = 480;
	var _layoutWidth = 720;
	var _labelWidth = 120;
	var _fieldWidth = 200;

	// ****** buttons ******
	var _buttons = {
		searchBtn : new DesktopWeb.Controls.ActionButton({
			itemId : 'searchBtn',
			text : _translationMap['Search'],
			handler : function() {
				if (_fields['taxJuris'].isValid() && _fields['taxModel'].isValid())
					_controller.doSearch(false);
			}
		})
	}

	// ****** fields ******
	var _fields = {
		taxJuris : new DesktopWeb.Controls.SMVComboBox({
			itemId : 'taxJuris',
			fieldLabel : _translationMap['TaxJuris'],
			width : _fieldWidth,
			editable : true,
			allowBlank : false
		}),
		taxModel : new DesktopWeb.Controls.SMVComboBox({
			itemId : 'taxModel',
			fieldLabel : _translationMap['TaxModel'],
			width : _fieldWidth,
			editable : true,
			allowBlank : false
		}),
		activeBox : new DesktopWeb.Controls.Checkbox({
			boxLabel : _translationMap['OnlyActive'],
			height : 30,
			checked : true
		})
	}

	// ****** grids ******
	var _grids = {
		whtGrid : new DesktopWeb.AdvancedControls.GridPanel({
			width : _layoutWidth - 12,
			height : 340,
			// autoExpandColumn : 'taxJuris',
			autoScroll : true,
			trackMouseOver : true,
			store : new Ext.data.XmlStore({
				record : 'DistributionTaxInfo',
				fields : [ 'whdRatesUUID', 'referredUUID', 'taxJuris', 'taxModel',
						'factorCode', 'rateType', 'rate', 'startDate', 'stopDate',
						'verifyStat', 'version', 'active', 'allowVerify', 'userName',
						'processDate', 'modUser', 'modDate' ],
				listeners : {
					load : function(store, records) {
						Ext.each(records, function(record) {
							// display date field in format
							record.data.startDate = DesktopWeb.Util
									.getDateDisplayValue(record.data.startDate);
							record.data.stopDate = DesktopWeb.Util
									.getDateDisplayValue(record.data.stopDate);
							record.data.processDate = DesktopWeb.Util
									.getDateDisplayValue(record.data.processDate);
							record.data.modDate = DesktopWeb.Util
									.getDateDisplayValue(record.data.modDate);
						});

						store.fireEvent('datachanged', store);
						store.filterBy(function(record) {
							return record.data.runMode != _controller.RUNMODE_DEL;
						});
						_grids['whtGrid'].getSelectionModel().selectFirstRow();
					}
				}
			}),
			selModel : new Ext.grid.RowSelectionModel({
				singleSelect : true,
				listeners : {
					rowselect : function(selModel, index, record) {
						// set record's permission
						_controller.recordHandler(record.data.active,
								record.data.allowVerify);
					}
				}
			}),
			colModel : new Ext.grid.ColumnModel({
				defaults : {
					menuDisabled : true,
					sortable : false
				},
				columns : [ {
					header : _translationMap['TaxJuris'],
					id : 'taxJuris',
					dataIndex : 'taxJuris',
					renderer : function(value) {
						return _controller.getListDescription('taxJuris', value);
					}
				}, {
					header : _translationMap['TaxModel'],
					id : 'taxModel',
					dataIndex : 'taxModel',
					width : 75,
					renderer : function(value) {
						return _controller.getListDescription('taxModel', value);
					}
				}, {
					header : _translationMap['Component'],
					id : 'factorCode',
					dataIndex : 'factorCode',
					renderer : function(value) {
						return _controller.getListDescription('factorCode', value);
					}
				}, {
					header : _translationMap['RateType'],
					id : 'rateType',
					dataIndex : 'rateType',
					renderer : function(value) {
						return _controller.getListDescription('rateType', value);
					}
				}, {
					header : _translationMap['TaxRate'],
					id : 'rate',
					dataIndex : 'rate',
					width : 70
				}, {
					header : _translationMap['EffectiveDate'],
					id : 'startDate',
					dataIndex : 'startDate',
					width : 80
				}, {
					header : _translationMap['StopDate'],
					id : 'stopDate',
					dataIndex : 'stopDate',
					width : 80
				}, {
					header : _translationMap['VerifyStatus'],
					id : 'verifyStat',
					dataIndex : 'verifyStat',
					width : 80,
					renderer : function(value) {
						return _controller.getListDescription('verifyStat', value);
					}
				} ]
			}),
			buttons : [ new DesktopWeb.Controls.ActionButton({
				itemId : 'addBtn',
				text : _translationMap['Add'],
				handler : function() {
					_controller.openWhtMaintPopup(_controller.RUNMODE_ADD);
				}
			}), new DesktopWeb.Controls.ActionButton({
				itemId : 'modBtn',
				text : _translationMap['Modify'],
				handler : function() {
					_controller.openWhtMaintPopup(_controller.RUNMODE_MOD);
				}
			}), new DesktopWeb.Controls.ActionButton({
				itemId : 'delBtn',
				text : _translationMap['Delete'],
				handler : function() {
					_controller.openWhtMaintPopup(_controller.RUNMODE_DEL);
				}
			}), new DesktopWeb.Controls.ActionButton({
				itemId : 'verBtn',
				text : _translationMap['Verify'],
				handler : function() {
					_controller.openWhtMaintPopup(_controller.RUNMODE_VER);
				}
			}), new DesktopWeb.Controls.ActionButton({
				itemId : 'moreBtn',
				text : _translationMap['More'],
				handler : function() {
					_controller.doSearch(true);
				}
			}), new DesktopWeb.Controls.ActionButton({
				itemId : 'adminBtn',
				text : _translationMap['Admin'],
				handler : function() {
					_controller.openAdminPopup();
				}
			}) ]
		})
	}

	// ****** popups ******
	var _popups = {
		whtMaintPopup : new DesktopWeb.AdvancedControls.PopupWindow({
			width : 380,
			// height: 260,
			autoScroll : true,
			action : null,
			closeAction : 'hide',
			title : '',
			modal : true,
			defaults : {
				border : false
			},
			items : [
					{ // item[0]
						html : _translationMap['DeleteConfirmMsg'],
						style : 'text-align:center;font-weight:bold;'
					},
					{
						layout : 'form',
						itemId : 'whtMaintPopup',
						style : 'padding:10px',
						border : false,
						labelWidth : _labelWidth,
						items : [
								new DesktopWeb.Controls.SMVComboBox({
									itemId : 'pTaxJurisFld',
									fieldLabel : _translationMap['TaxJuris'],
									width : _fieldWidth,
									editable : true,
									allowBlank : false
								}),
								new DesktopWeb.Controls.SMVComboBox({
									itemId : 'pTaxModelFld',
									fieldLabel : _translationMap['TaxModel'],
									width : _fieldWidth,
									editable : true,
									allowBlank : false
								}),
								new DesktopWeb.Controls.SMVComboBox({
									itemId : 'pComponentFld',
									fieldLabel : _translationMap['Component'],
									width : _fieldWidth,
									editable : true,
									allowBlank : false
								}),
								new DesktopWeb.Controls.SMVComboBox({
									itemId : 'pRateTypeFld',
									fieldLabel : _translationMap['RateType'],
									width : _fieldWidth,
									editable : true,
									allowBlank : false
								}),
								new DesktopWeb.Controls.NumberField({
									itemId : 'pTaxRateFld',
									fieldLabel : _translationMap['TaxRate'],
									width : _fieldWidth - 105,
									minValue : 0,
									maxValue : 100,
									decimalPrecision : 4,
									allowDecimals : true,
									allowBlank : false
								}),
								new DesktopWeb.Controls.DateField({
									itemId : 'pStartDateFld',
									fieldLabel : _translationMap['EffectiveDate'],
									format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util
											.getDateDisplayFormat())
								}),
								new DesktopWeb.Controls.DateField({
									itemId : 'pStopDateFld',
									fieldLabel : _translationMap['StopDate'],
									format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util
											.getDateDisplayFormat())
								}), new DesktopWeb.Controls.SMVComboBox({
									itemId : 'pVerifyStatFld',
									fieldLabel : _translationMap['VerifyStatus'],
									width : _fieldWidth,
									editable : true
								// allowBlank : false
								}), new DesktopWeb.Controls.Checkbox({
									itemId : 'pApplyAllChk',
									boxLabel : _translationMap['ApplyAll'],
									height : 20,
									checked : false
								}) ]
					// items
					} ] // items
			,
			buttons : [
					new DesktopWeb.Controls.ActionButton({
						itemId : 'okBtn',
						text : _translationMap['OK'],
						handler : function() {
							// verify each field of popup
							if (_popups['whtMaintPopup'].isValid()
									&& _controller.doValidateSave()) {
								_controller.doSave(_popups['whtMaintPopup'].action);
							}
						}
					}), new DesktopWeb.Controls.ActionButton({
						itemId : 'cancelBtn',
						text : _translationMap['Cancel'],
						handler : function() {
							_popups['whtMaintPopup'].hide();
						}
					}) ] // buttons
			,
			init : function(action) {
				this.action = action;
				_popups['whtMaintPopup'].get(0).hide();
				switch (action) {
					case _controller.RUNMODE_ADD:
						this.setTitle(_translationMap['WhtRatesMaint'] + ' - '
								+ _translationMap['Add']);
						break;
					case _controller.RUNMODE_MOD:
						this.setTitle(_translationMap['WhtRatesMaint'] + ' - '
								+ _translationMap['Modify']);
						break;
					case _controller.RUNMODE_DEL:
						this.setTitle(_translationMap['WhtRatesMaint'] + ' - '
								+ _translationMap['Delete']);
						_popups['whtMaintPopup'].get(0).show();
						break;
					case _controller.RUNMODE_VER:
						this.setTitle(_translationMap['WhtRatesMaint'] + ' - '
								+ _translationMap['Verify']);
						break;
				}
			}
		}), // whtMaintPopup

		admin : new DesktopWeb.AdvancedControls.PopupWindow({
			width : 395,
			closeAction : 'hide',
			modal : true,
			defaults : {
				border : false
			},
			items : [ {
				layout : 'column',
				style : 'padding:4px',
				defaults : {
					border : false,
					labelWidth : 80
				},
				items : [ {
					width : 185,
					layout : 'form',
					defaults : {
						width : 80
					},
					items : [ new DesktopWeb.Controls.Label({
						itemId : 'userName',
						fieldLabel : _translationMap['Username']
					}), new DesktopWeb.Controls.Label({
						itemId : 'modUser',
						fieldLabel : _translationMap['ModUser']
					}) ]
				}, {
					width : 185,
					layout : 'form',
					defaults : {
						width : 80
					},
					items : [ new DesktopWeb.Controls.Label({
						itemId : 'procDate',
						fieldLabel : _translationMap['ProcessDate']
					}), new DesktopWeb.Controls.Label({
						itemId : 'modDate',
						fieldLabel : _translationMap['ModDate']
					}) ]
				} ]
			} ],
			buttons : [ new DesktopWeb.Controls.ActionButton({
				text : _translationMap['OK'],
				handler : function() {
					_popups['admin'].hide();
				}
			}) ],
			init : function(title, data) {
				this.setTitle(title);
				this.getField('procDate').setValue(data['procDate']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['userName']);
				this.getField('modUser').setValue(data['modUser']);
			}
		})
	// admin
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
			items : [ {
				xtype : 'fieldset',
				title : _translationMap['Search'],
				layout : 'column',
				items : [ {
					// Row#1
					layout : 'form',
					columnWidth : 0.50,
					autoHeight : true,
					labelWidth : _labelWidth,
					items : [ _fields['taxJuris'], _fields['taxModel'] ]
				}, {
					// Row#2
					layout : 'form',
					columnWidth : 0.50,
					autoHeight : true,
					labelWidth : _labelWidth,
					items : [ _fields['activeBox'], _buttons['searchBtn'] ]
				} ]
			// items
			}, {
				xtype : 'fieldset',
				title : _translationMap['WhtRates'],
				layout : 'column',
				width : _layoutWidth,
				items : [ _grids['whtGrid'] ]
			} ]
		}),
		screenButtons : {
			items : [ new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Close'],
				handler : function() {
					DesktopWeb.Util.cancelScreen();
				}
			}) ]
		}
	}
}