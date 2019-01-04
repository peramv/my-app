/******************************************************************************
 * Procedure: ExternalTA.Translation.js
 * Purpose  : ExternalTA screens manage External Tranfer Agent data
 * Notes    : Open screens by 
 *						 Menu -> System Maintenance -> External TA Fund Linkage
 * History  :
 *		03 Jul 2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *			- Created
 *
 *		20 Jul 2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *			- Update allowBlank to false for externalAccount field.
 ******************************************************************************/

DesktopWeb.ScreenResources = function (ctrlr) {
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _controller = ctrlr;

	// content dimensions
	var _layoutWidth = 720;
	var _layoutHeight = 320;

	// ****** buttons ******
	var _buttons = {
		btnSearch : new DesktopWeb.Controls.ActionButton({
			text : _translationMap['Search'],
			style : "position:absolute; right:0px; top:0px;",
			handler : function () {
				_controller.clickHandleSearchBtn(false);
			}
		})
	}

	// ****** fields ******
	var _fields = {
		fundGrpSrch : new DesktopWeb.Controls.ComboBox({
			itemId : 'fundGrpSrch',
			fieldLabel : _translationMap['FundGroup'],
			width : 150,
			valueField : 'fundGroupCode',
			displayField : 'displayValue',
			store : new Ext.data.XmlStore({
				record : 'FundGroup',
				fields : ['fundGroupCode', 'fundGroupType', 'fundGroupDesc', 'level', 'displayValue']
			})
		}),
		extAcctSrch : new DesktopWeb.Controls.TextField({
			itemId : 'extAcctSrch',
			width : 200,
			fieldLabel : _translationMap['ExtAcct']

		})
	} // _fields

	// ****** grids ******
	var _grids = {
		gridExternalTA : new DesktopWeb.AdvancedControls.GridPanel({
			width : _layoutWidth,
			height : 235,
			autoScroll : true,
			reset : function () {
				this.getStore().removeAll();
				this.disableAllButtons();
			},
			store : new Ext.data.XmlStore({
				record : 'ExternalTA',
				fields : ['errMsg', 'runMode', 'externalTAUUID', 'fundGroup', 'ruleCode', 'ruleDesc',
					'fundGroupDesc', 'extAcct', 'recvNWAddr', 'startDate', 'stopDate', 'level',
					'allowMod', 'allowDel', 'version', 'userName', 'processDate', 'modUser', 'modDate'],
				listeners : {
					load : function (store, records) {
						Ext.each(records, function (record) {
							record.data.startDate = DesktopWeb.Util.getDateDisplayValue(record.data.startDate);
							record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
							record.data.processDate = DesktopWeb.Util.getDateDisplayValue(record.data.processDate);
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
						});
						store.fireEvent('datachanged', store);
						_grids['gridExternalTA'].getSelectionModel().selectFirstRow();
					}
				}
			}),
			selModel : new Ext.grid.RowSelectionModel({
				singleSelect : true,
				listeners : {
					rowselect : function (selModel, index, record) {
						_controller.updateActionButtons();
					}
				}
			}),
			colModel : new Ext.grid.ColumnModel({
				defaults : {
					menuDisabled : true
				},
				columns : [{
						dataIndex : 'errMsg',
						width : 25,
						renderer : function (val) {
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}, {
						header : _translationMap['FundGroup'],
						dataIndex : 'fundGroup',
						width : 70
					}, {
						header : _translationMap['FundGroupDesc'],
						dataIndex : 'fundGroupDesc',
						width : 100
					}, {
						header : _translationMap['RuleType'],
						dataIndex : 'ruleDesc',
						width : 140
					}, {
						header : _translationMap['ExtAcct'],
						dataIndex : 'extAcct',
						width : 120
					}, {
						header : _translationMap['RecvNWAddr'],
						dataIndex : 'recvNWAddr',
						width : 120
					}, {
						header : _translationMap['StartDate'],
						dataIndex : 'startDate',
						width : 65
					}, {
						header : _translationMap['StopDate'],
						dataIndex : 'stopDate',
						width : 65
					}
				]
			}),
			buttons : [
				new DesktopWeb.Controls.ActionButton({
					itemId : 'addBtn',
					text : _translationMap['Add'],
					handler : function () {
						_controller.openActionPopup(_controller.ADD);
					}
				}),
				new DesktopWeb.Controls.ActionButton({
					itemId : 'modBtn',
					text : _translationMap['Modify'],
					handler : function () {
						_controller.openActionPopup(_controller.MOD);
					}
				}),
				new DesktopWeb.Controls.ActionButton({
					itemId : 'delBtn',
					text : _translationMap['Delete'],
					messageStop : _translationMap['StopConfirmMsg'],
					messageDel :_translationMap['DeleteConfirmMsg'] ,
					handler : function () {
						
						var mode = _grids['gridExternalTA'].getSelectedRecord().data.runMode ;
						DesktopWeb.Util.displayYesNo(mode == _controller.ADD ? this.messageDel:this.messageStop, handlePromptMsg);
						
						function handlePromptMsg(btn) {
							if (btn == 'yes')
								_controller.deleteSelectedRecord();
							else
								return;
						}

					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'moreBtn',
					text : _translationMap['More'],
					handler : function () {
						_controller.clickHandleMoreBtn();
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'adminBtn',
					text : _translationMap['Admin'],
					handler : function () {
						_controller.openAdminPopup();
					}
				}), new DesktopWeb.Controls.ActionButton({
					itemId : 'historicalBtn',
					text : _translationMap['Historical'],
					handler : function () {
						_controller.openHistoryPopup();
					}
				})]
		}) // gridExternalTA
	} // _grids

	// ****** popups ******
	var _popups = {
		externalTAPopup : new DesktopWeb.AdvancedControls.PopupWindow({
			width : 460,
			itemId : 'externalTAPopup',
			action : null,
			modal : true,
			defaults : {
				border : false
			},
			items : [{
					layout : 'form',
					style : 'padding:5px;padding-top:10px',
					labelWidth : 125,
					items : [
						new DesktopWeb.Controls.ComboBox({
							itemId : 'fundGroup',
							allowBlank : false,
							width : 275,
							fieldLabel : _translationMap['FundGroup'],
							valueField : 'fundGroupCode',
							displayField : 'displayValue',
							store : new Ext.data.XmlStore({
								record : 'FundGroup',
								fields : ['fundGroupCode', 'fundGroupType', 'fundGroupDesc', 'level', 'displayValue']
							})						
						}), new DesktopWeb.Controls.SMVComboBox({
							itemId : 'ruleCode',
							allowBlank : false,
							width : 275,
							fieldLabel : _translationMap['RuleType']
						}), new DesktopWeb.Controls.TextField({
							itemId : 'extAcct',
							allowBlank : false,
							width : 275,
							fieldLabel : _translationMap['ExtAcct'],
							maxLength : 40
						}), new DesktopWeb.Controls.TextField({
							itemId : 'recvNWAddr',
							width : 275,
							fieldLabel : _translationMap['RecvNWAddr']
						}), {
							layout : 'column',
							border : false,
							labelWidth : 30,
							defaults : {
								layout : 'form',
								border : false
							},
							items : [{
									labelWidth : 125,
									columnWidth : 0.55,
									items : [
										new DesktopWeb.Controls.DateField({
											itemId : 'startDate',
											allowBlank : false,
											width : 90,
											fieldLabel : _translationMap['StartDate'],
											format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										})
									]
								}, {
									labelWidth : 63,
									columnWidth : 0.45,
									style : 'padding-left:3px',
									items : [
										new DesktopWeb.Controls.DateField({
											itemId : 'stopDate',
											allowBlank : false,
											width : 90,
											fieldLabel : _translationMap['StopDate'],
											format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										})
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
					itemId : 'OKpop',
					handler : function () {

						if (_popups['externalTAPopup'].isValid()) {
							var tempdata = _popups['externalTAPopup'].getData();
							var validateResult = _controller.doValidatePopup(_popups['externalTAPopup'].action, tempdata)
								if (validateResult) {
									_controller.savePopup(_popups['externalTAPopup'].action, tempdata);
									_popups['externalTAPopup'].hide();
								}
						}
					}
				}), new DesktopWeb.Controls.ActionButton({
					text : _translationMap['Cancel'],
					itemId : 'Cancelpop',
					handler : function () {
						_controller.updateActionButtons();
						_popups['externalTAPopup'].hide();
					}
				})
			],
			init : function (action) {
				this.action = action
					this.clearAllFields();

				switch (action) {
				case _controller.ADD: {
						this.setTitle(_translationMap['ExternalTA'] + ' - ' + _translationMap['Add']);
						this.enableAllFields();
						break;
					}
				case _controller.MOD: {
						this.setTitle(_translationMap['ExternalTA'] + ' - ' + _translationMap['Modify']);
						this.disableAllFields();
						break;
					}
				}

			},
			getData : function () {
				var data = {};
				data['runMode'] = _popups['externalTAPopup'].action;
				data['errMsg'] = "";

				data['fundGroup'] = this.getField('fundGroup').getValue();
				var fgRec = this.getField('fundGroup').getSelectedRecord();
				if (!!fgRec) {
					data['fundGroupDesc'] = fgRec.data.fundGroupDesc;
					data['level'] = fgRec.data.level;
				}
				data['ruleCode'] = this.getField('ruleCode').getValue();
				data['ruleDesc'] = this.getField('ruleCode').getRawValue();
				
				data['startDateObj'] = this.getField('startDate').getValue();
				data['startDate'] = this.getField('startDate').getDisplayDateString();
				data['stopDateObj'] = this.getField('stopDate').getValue();
				data['stopDate'] = this.getField('stopDate').getDisplayDateString();

				data['extAcct'] = this.getField('extAcct').getValue();
				data['recvNWAddr'] = this.getField('recvNWAddr').getValue();
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
							items : [new DesktopWeb.Controls.Label({
									itemId : 'userName',
									fieldLabel : _translationMap['Username']
								}), new DesktopWeb.Controls.Label({
									itemId : 'modUser',
									fieldLabel : _translationMap['ModUser']
								})]
						}, {
							width : 185,
							layout : 'form',
							defaults : {
								width : 80
							},
							items : [new DesktopWeb.Controls.Label({
									itemId : 'procDate',
									fieldLabel : _translationMap['ProcessDate']
								}), new DesktopWeb.Controls.Label({
									itemId : 'modDate',
									fieldLabel : _translationMap['ModDate']
								})]
						}
					]
				}
			],
			buttons : [new DesktopWeb.Controls.ActionButton({
					text : _translationMap['OK'],
					handler : function () {
						_popups['admin'].hide();
					}
				})],
			init : function (title, data) {
				this.setTitle(title);
				this.getField('procDate').setValue(data['procDate']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['userName']);
				this.getField('modUser').setValue(data['modUser']);
			}
		}) // admin
	,
		history : new DesktopWeb.AdvancedControls.HistoryPopup()
	} // _popups


	// PUBLIC ITEMS
	return {
		layoutWidth : _layoutWidth,
		layoutHeight : _layoutHeight,
		fields : _fields,
		grids : _grids,
		buttons : _buttons,
		popups : _popups,
		layout : new Ext.Container({
			width : _layoutWidth,
			height : _layoutHeight,
			items : [{
					xtype : 'fieldset',
					title : _translationMap['Search'],
					items : [{
							layout : 'column',
							items : [{
									width : 250,
									layout : 'form',
									labelWidth : 75,
									items : [_fields['fundGrpSrch']]
								}, {
									width : 340,
									layout : 'form',
									labelWidth : 125,
									items : [_fields['extAcctSrch']]
								}, _buttons['btnSearch']]
						}

					]
				}, _grids['gridExternalTA']
			]// items
		}),
		screenButtons : {
			items : [
				new DesktopWeb.Controls.ScreenButton({
					text : _translationMap['OK'],
					handler : function () {
						if (_controller.updatesFlag)
							_controller.doValidateCommitScreen();
						else
							DesktopWeb.Util.cancelScreen();
					}
				}),
				new DesktopWeb.Controls.ScreenButton({
					text : _translationMap['Close'],
					handler : function () {
						DesktopWeb.Util.cancelScreen();
					}
				})]
		}
	}
}
