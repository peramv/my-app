/*******************************************************************************
 * @file FundDistribSplit.Resources.js
 * @author Narin Suanlamyai
 * @desc Resources file for Fund Distribution Split Maintenance screen
 ******************************************************************************/
/*
 * Navigate: Menu > System Maintenance > Fund Distribution Split Maintenance
 * 
 * History :
 * 
 * 29-Dec-2017 Narin Suanlamyai P0274848 Distribution Processing - Initial
 * screen.
 * 
 * 14-Feb-2018 Pawarin.J P0274848 DFT0081341
 * - Fix dropdown lists to display class code instead of class description
 */

DesktopWeb.ScreenResources = function(ctrlr) {
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 550;
	var _layoutWidth = 680;

	// **** buttons ****
	var _buttons = {
		searchBtn : new DesktopWeb.Controls.ActionButton({
			style : 'margin-top: 35px; margin-left:25px;',
			text : _translationMap['Search'],
			tabIndex : 5,
			handler : function() {
				if (_controller.isSearchCriteriaValid()) {
					if (_controller.updatesFlag) {
						DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)

						function handlePromptMsg(btn) {
							if (btn) {
								_controller.updatesFlag = false;
								_controller.doSearch();
							}
						}
					} else {
						_controller.doSearch();
					}
				}
			}
		})
	}

	// **** fields ****
	var _fields = {
		fundFld : new DesktopWeb.Controls.SuggestField({
			fieldLabel : _translationMap['Fund'],
			width : 250,
			allowBlank : false,
			smartview : 'fundOnlySearch',
			addtlSearchParams : [ {
				name : 'inclInactive',
				valueFn : function() {
					return 'yes'
				}
			} ],
			fields : [ 'fndDisp', 'fundCode', 'fundName' ],
			valueField : 'fundCode',
			displayField : 'fndDisp',
			tabIndex : 1,
			listeners : {
				populated : function(fld, record) {
					_controller.loadClass(record.data['fundCode'],
							_fields['classFld']);
				},
				cleared : function() {
					_fields['classFld'].reset();
					_fields['classFld'].disable();
				}
			}
		}),
		classFld : new DesktopWeb.Controls.ComboBox({
			fieldLabel : _translationMap['Class'],
			width : 75,
			allowBlank : false,
			autoSelect : true,
			disabled : true,
			tabIndex : 2,
			editable : false,
			store : new Ext.data.XmlStore({
				record : 'ClassInfo',
				fields : [ 'classCode', 'description' ],
				listeners : {
					load : function(store, records) {
						if (records.length > 0) {
							_fields['classFld'].enable();
							_fields['classFld']
									.setValue(records[0].data['classCode']);
						}
					}
				}
			}),
			valueField : 'classCode',
			displayField : 'classCode'
		}),
		distribTypeFld : new DesktopWeb.Controls.SMVComboBox({
			fieldLabel : _translationMap["DistributionType"],
			width : 175,
			allowBlank : true,
			editable : true,
			tabIndex : 3
		}),
		activeBox : new DesktopWeb.Controls.Checkbox({
			boxLabel : _translationMap['OnlyActive'],
			checked : false
		})
	}

	// **** grids ****
	var _grids = {
		distribMstr : new DesktopWeb.AdvancedControls.GridPanel(
				{
					autoScroll : true,
					height : 180,
					autoExpandColumn : 'fromFund',
					store : new Ext.data.XmlStore(
							{
								record : 'FundDistribSplit',
								fields : [ 'errMsg', 'mstrUUID', 'fundCode',
										'fundDesc', 'classCode', 'classDesc',
										'distribType', 'deff', 'verifyStat',
										'username', 'processDate', 'modUser',
										'modDate', 'fundDistribSplitDetls',
										'gbcd', 'runMode', 'version' ],
								listeners : {
									load : function(store, records) {
										Ext
												.each(
														records,
														function(record) {
															record.data['deff'] = DesktopWeb.Util
																	.getDateDisplayValue(record.data['deff']);
															record.data['fundDistribSplitDetls'] = _controller
																	.getFundDistribSplitDetails(record.data['mstrUUID']);
														});
										store
												.filterBy(function(record) {
													return record.data.runMode != _controller.DEL
												});
									},
									update : function(store) {
										store
												.filterBy(function(record) {
													return record.data.runMode != _controller.DEL
												});
									}
								}
							}),
					selModel : new Ext.grid.RowSelectionModel({
						singleSelect : true,
						listeners : {
							rowselect : function(selModel, index, record) {
								_controller.selectDistributionRecord(record);
							}
						}
					}),
					colModel : new Ext.grid.ColumnModel(
							{
								defaults : {
									menuDisabled : true
								},
								columns : [
										{
											header : "",
											id : 'errMsg',
											dataIndex : 'errMsg',
											width : 25,
											renderer : function(val) {
												return (val ? DesktopWeb.Util
														.buildErrorFlag(val)
														: '');
											}
										},
										{
											header : _translationMap['FromFund'],
											id : 'fromFund',
											dataIndex : 'fundDesc'
										},
										{
											header : _translationMap['FromClass'],
											dataIndex : 'classCode',
											width : 75
										},
										{
											header : _translationMap['DistributionType'],
											dataIndex : 'distribType',
											width : 130,
											renderer : function(val) {
												return (val ? _controller
														.getDescriptionFromList(
																val,
																"DistributionTypeList")
														: "");
											}
										},
										{
											header : _translationMap['EffectiveDate'],
											dataIndex : 'deff',
											width : 80
										},
										{
											header : _translationMap['VerifyStatus'],
											dataIndex : 'verifyStat',
											width : 80,
											renderer : function(val) {
												return (val ? _controller
														.getDescriptionFromList(
																val,
																"VerifyStatusList")
														: "");
											}
										} ]
							}),
					buttons : [
							new DesktopWeb.Controls.ActionButton({
								itemId : 'addBtn',
								text : _translationMap['Add'],
								disabled : true,
								handler : function() {
									_controller.openActionPopup("distribMstr",
											_controller.ADD);
								}
							}),
							new DesktopWeb.Controls.ActionButton({
								itemId : 'modBtn',
								text : _translationMap['Modify'],
								disabled : true,
								handler : function() {
									_controller.openActionPopup("distribMstr",
											_controller.MOD);
								}
							}),
							new DesktopWeb.Controls.ActionButton({
								itemId : 'delBtn',
								text : _translationMap['Delete'],
								disabled : true,
								handler : function() {
									_controller.openActionPopup("distribMstr",
											_controller.DEL);
								}
							}), new DesktopWeb.Controls.ActionButton({
								itemId : 'adminBtn',
								text : _translationMap['Admin'],
								disabled : true,
								handler : function() {
									_controller.openAdminPopup('distribMstr');
								}
							}), new DesktopWeb.Controls.ActionButton({
								itemId : 'historicalBtn',
								text : _translationMap['Historical'],
								disabled : true,
								handler : function() {
									_controller.openHistoricalPopup();
								}
							}), new DesktopWeb.Controls.ActionButton({
								itemId : 'moreBtn',
								text : _translationMap['More'],
								disabled : true,
								handler : function() {
									_controller.doReload();
								}
							}) ]
				}),
		distribDetl : new DesktopWeb.AdvancedControls.GridPanel(
				{
					height : 180,
					autoExpandColumn : "toFund",
					store : new Ext.data.XmlStore(
							{
								record : 'FundDistribSplitDetl',
								fields : [ 'errMsg', 'mstrUUID', 'detlUUID',
										'distribOpt', 'toFundCode',
										'toFundDesc', 'toClassCode',
										'toClassDesc', 'prcnt', 'verifyStat',
										'username', 'processDate', 'modUser',
										'modDate', 'version', 'runMode' ],
								listeners : {
									load : function(store, records) {
										store
												.filterBy(function(record) {
													return record.data.runMode != _controller.DEL
												});
										if (records.length <= 0)
											_controller
													.updateDistribDetlGridButtons(null);
									},
									update : function(store) {
										store
												.filterBy(function(record) {
													return record.data.runMode != _controller.DEL
												});
									}
								}
							}),
					selModel : new Ext.grid.RowSelectionModel(
							{
								singleSelect : true,
								listeners : {
									rowselect : function(selModel, index,
											record) {
										_controller
												.selectDistributionDetailsRecord(record);
									}
								}
							}),
					colModel : new Ext.grid.ColumnModel(
							{
								defaults : {
									menuDisabled : true
								},
								columns : [
										{
											header : "",
											id : 'errMsg',
											dataIndex : 'errMsg',
											width : 25,
											renderer : function(val) {
												return (val ? DesktopWeb.Util
														.buildErrorFlag(val)
														: '');
											}
										},
										{
											header : _translationMap['DistributionOption'],
											dataIndex : 'distribOpt',
											width : 150,
											renderer : function(val) {
												return (val ? _controller
														.getDescriptionFromList(
																val,
																"DistributionOptionList")
														: "");
											}
										},
										{
											header : _translationMap['ToFund'],
											id : "toFund",
											dataIndex : 'toFundDesc'
										},
										{
											header : _translationMap['ToClass'],
											dataIndex : 'toClassCode',
											width : 100
										},
										{
											header : _translationMap['SplitPercent'],
											dataIndex : 'prcnt',
											width : 80
										} ]
							}),
					buttons : [
							new DesktopWeb.Controls.ActionButton({
								itemId : 'addBtn',
								text : _translationMap['Add'],
								disabled : true,
								handler : function() {
									_controller.openActionPopup("distribDetl",
											_controller.ADD);
								}
							}),
							new DesktopWeb.Controls.ActionButton({
								itemId : 'modBtn',
								text : _translationMap['Modify'],
								disabled : true,
								handler : function() {
									_controller.openActionPopup("distribDetl",
											_controller.MOD);
								}
							}),
							new DesktopWeb.Controls.ActionButton({
								itemId : 'delBtn',
								text : _translationMap['Delete'],
								disabled : true,
								handler : function() {
									_controller.openActionPopup("distribDetl",
											_controller.DEL);
								}
							}) ]
				})
	}

	// **** popups ****
	var _popups = {
		distribMstr : new DesktopWeb.AdvancedControls.PopupWindow(
				{
					title : '',
					action : '',
					gbcd : '',
					runMode : '',
					mstrUUID : '',
					width : 400,
					closeAction : 'hide',
					autoHeight : true,
					modal : true,
					defaults : {
						border : false
					},
					version : '',
					items : [
							{
								html : _translationMap['DeleteConfirmMsg'],
								style : 'text-align:center;font-weight:bold;'
							},
							{
								layout : 'form',
								style : 'padding:4px',
								defaults : {
									border : true
								},
								labelWidth : 100,
								items : [
										new DesktopWeb.Controls.SuggestField(
												{
													itemId : "fromFund",
													fieldLabel : _translationMap["FromFund"],
													width : 250,
													allowBlank : false,
													smartview : 'fundOnlySearch',
													addtlSearchParams : [ {
														name : 'inclInactive',
														valueFn : function() {
															return 'yes'
														}
													} ],
													fields : [ 'fndDisp',
															'fundCode',
															'fundName' ],
													valueField : 'fundCode',
													displayField : 'fndDisp',
													tabIndex : 3,
													loadFromClass : false,
													listeners : {
														populated : function(
																fld, record) {
															if (this.loadFromClass) {
																_controller
																		.loadClass(
																				record.data['fundCode'],
																				_popups["distribMstr"]
																						.getField("fromClass"));
															}
														},
														cleared : function() {
															_popups["distribMstr"]
																	.getField(
																			"fromClass")
																	.reset();
															_popups["distribMstr"]
																	.getField(
																			"fromClass")
																	.disable();
														}
													}
												}),
										new DesktopWeb.Controls.ComboBox(
												{
													itemId : "fromClass",
													fieldLabel : _translationMap['FromClass'],
													width : 75,
													allowBlank : false,
													autoSelect : true,
													tabIndex : 2,
													editable : false,
													store : new Ext.data.XmlStore(
															{
																record : 'ClassInfo',
																fields : [
																		'classCode',
																		'description' ],
																listeners : {
																	load : function(
																			store,
																			records) {
																		if (records.length > 0) {
																			_popups["distribMstr"]
																					.getField(
																							"fromClass")
																					.enable();
																			_popups["distribMstr"]
																					.getField(
																							"fromClass")
																					.setValue(
																							records[0].data['classCode']);
																		}
																	}
																}
															}),
													valueField : 'classCode',
													displayField : 'classCode'
												}),
										new DesktopWeb.Controls.SMVComboBox(
												{
													itemId : 'distribType',
													fieldLabel : _translationMap['DistributionType'],
													allowBlank : false,
													width : 175
												}),
										new DesktopWeb.Controls.DateField(
												{
													itemId : 'deff',
													fieldLabel : _translationMap['EffectiveDate'],
													format : DesktopWeb.Util
															.parseSMVDateFormat(DesktopWeb.Util
																	.getDateDisplayFormat()),
													allowBlank : false
												}),
										new DesktopWeb.Controls.SMVComboBox(
												{
													itemId : 'verifyStat',
													fieldLabel : _translationMap['VerifyStatus'],
													allowBlank : false,
													width : 100
												}) ]
							} ],
					buttons : [
							new DesktopWeb.Controls.ActionButton(
									{
										itemId : 'okBtn',
										text : _translationMap['OK'],
										handler : function() {
											var distribMstrData = _popups['distribMstr']
													.getData();
											if (_controller
													.isValidDistribMstrRecord(distribMstrData)) {
												_controller
														.updateDistribMstrRecord(distribMstrData);
												_controller.updatesFlag = true;
											}
										}
									}), new DesktopWeb.Controls.ActionButton({
								itemId : 'canBtn',
								text : _translationMap['Cancel'],
								handler : function() {
									_popups['distribMstr'].hide();
								}
							}) ],
					init : function(action) {
						// initialize popup based on action
						var popup = _popups['distribMstr'];
						popup.action = action;

						switch (action) {
						case _controller.ADD: {
							popup
									.setTitle(_translationMap["FundDistributionSplit"]
											+ " - " + _translationMap["Add"]);
							popup.populate(action);
							popup.get(0).hide();
							break;
						}
						case _controller.MOD: {
							popup
									.setTitle(_translationMap["FundDistributionSplit"]
											+ " - " + _translationMap["Modify"]);
							popup.populate(action);
							popup.get(0).hide();
							break;
						}
						case _controller.DEL: {
							popup
									.setTitle(_translationMap["FundDistributionSplit"]
											+ " - " + _translationMap["Delete"]);
							popup.populate(action);
							popup.disableAllFields();
							popup.get(0).show();
							break;
						}
						}
						if (popup.rendered)
							popup.syncSize();
					},
					populate : function(action) {
						var popup = _popups['distribMstr'];

						popup.clearAllFields();
						popup.enableAllFields();

						popup.getField('fromFund').loadFromClass = false;

						if (action == _controller.ADD) {
							popup.version = '1';
							popup.runMode = _controller.ADD;
							popup.gbcd = "yes";
							popup.mstrUUID = "DISTMSTR"
									+ _controller.getNewUUID();

							popup.getField('fromFund').setValue("");
							popup.getField('fromFund').clearInvalid();
							popup.getField('fromClass').setValue("");
							popup.getField('fromClass').clearInvalid();
							popup.getField('distribType').setValue("");
							popup.getField('distribType').clearInvalid();
							popup
									.getField('deff')
									.setValue(
											DesktopWeb.Util
													.getDateDisplayValue(_controller.defaultValuesMap['deff']));
							popup.getField('deff').disableField();
							popup.getField('deff').clearInvalid();
							popup.getField('verifyStat').setValue(_controller.defaultValuesMap['verifyStat']);
							popup.getField('verifyStat').disableField();
							popup.getField('verifyStat').clearInvalid();
						} else if (action == _controller.MOD) {
							var distribMstrRec = _grids['distribMstr']
									.getSelectedRecord();

							popup.runMode = distribMstrRec.data['runMode'];
							popup.version = distribMstrRec.data['version'];
							popup.gbcd = distribMstrRec.data['gbcd'];
							popup.mstrUUID = distribMstrRec.data['mstrUUID'];

							popup.getField('fromFund').prepopulate(
									distribMstrRec.data['fundCode'],
									distribMstrRec.data['fundDesc']);
							popup.getField('distribType').setValue(
									distribMstrRec.data['distribType']);
							popup.getField('deff').setValue(
									distribMstrRec.data['deff']);
							popup.getField('verifyStat').setValue(
									distribMstrRec.data['verifyStat']);

							_controller.loadClass(
									distribMstrRec.data['fundCode'],
									_popups["distribMstr"]
											.getField("fromClass"),
									distribMstrRec.data['classCode']);

							if (distribMstrRec.data['runMode'] !== _controller.ADD) {
								popup.getField('fromFund').disableField();
								popup.getField('fromClass').disableField();
								popup.getField('distribType').disableField();
								popup.getField('deff').disableField();
							} else {
								popup.getField('deff').disableField();
								popup.getField('verifyStat').disableField();
							}

						} else if (action == _controller.DEL) {
							var distribMstrRec = _grids['distribMstr']
									.getSelectedRecord();
							popup.runMode = distribMstrRec.data['runMode'];
							popup.version = distribMstrRec.data['version'];
							popup.gbcd = distribMstrRec.data['gbcd'];
							popup.mstrUUID = distribMstrRec.data['mstrUUID'];

							popup.getField('fromFund').prepopulate(
									distribMstrRec.data['fundCode'],
									distribMstrRec.data['fundDesc']);
							popup.getField('distribType').setValue(
									distribMstrRec.data['distribType']);
							popup.getField('deff').setValue(
									distribMstrRec.data['deff']);
							popup.getField('verifyStat').setValue(
									distribMstrRec.data['verifyStat']);

							_controller.loadClass(
									distribMstrRec.data['fundCode'],
									_popups["distribMstr"]
											.getField("fromClass"),
									distribMstrRec.data['classCode']);

						}

						popup.getField('fromFund').loadFromClass = true;

						if (popup.rendered)
							popup.syncSize();
					},
					getData : function() {
						var popup = _popups['distribMstr'];
						var data = {};

						data['mstrUUID'] = popup.mstrUUID;
						data['action'] = popup.action;
						data['runMode'] = popup.runMode;
						data['gbcd'] = popup.gbcd;
						data['version'] = popup.version;
						data['fundCode'] = popup.getField('fromFund')
								.getValue();
						data['fundDesc'] = popup.getField('fromFund')
								.getRawValue();
						data['classCode'] = popup.getField('fromClass')
								.getValue();
						data['classDesc'] = popup.getField('fromClass')
								.getRawValue();
						data['distribType'] = popup.getField('distribType')
								.getValue();
						data['deff'] = popup.getField('deff')
								.getDisplayDateString();
						data['verifyStat'] = popup.getField('verifyStat')
								.getValue();

						return data;
					}
				}),
		distribDetl : new DesktopWeb.AdvancedControls.PopupWindow(
				{
					title : _translationMap['FundDistributionSplitDetl']
							+ " - " + _translationMap['Add'],
					action : '',
					mstrUUID : '',
					detlUUID : '',
					width : 400,
					closeAction : 'hide',
					autoHeight : true,
					modal : true,
					defaults : {
						border : false
					},
					version : '',
					items : [
							{
								html : _translationMap['DeleteConfirmMsg'],
								style : 'text-align:center;font-weight:bold;'
							},
							{
								layout : 'form',
								style : 'padding:4px',
								defaults : {
									border : true
								},
								labelWidth : 110,
								items : [
										new DesktopWeb.Controls.Label(
												{
													itemId : 'fromFund',
													fieldLabel : _translationMap['FromFund']
												}),
										new DesktopWeb.Controls.Label(
												{
													itemId : 'fromClass',
													fieldLabel : _translationMap['FromClass']
												}),
										new DesktopWeb.Controls.Label(
												{
													itemId : 'distribType',
													fieldLabel : _translationMap['DistributionType']
												}),
										new DesktopWeb.Controls.SMVComboBox(
												{
													itemId : 'distribOpt',
													fieldLabel : _translationMap['DistributionOption'],
													width : 150,
													allowBlank : false,
													listeners : {
														select : function(
																combo, record,
																index) {
															_controller
																	.distributionOptionHandler(record.data['code']);
														}
													}
												}),
										new DesktopWeb.Controls.SuggestField(
												{
													itemId : 'toFund',
													fieldLabel : _translationMap['ToFund'],
													width : 250,
													allowBlank : false,
													smartview : 'fundOnlySearch',
													addtlSearchParams : [ {
														name : 'inclInactive',
														valueFn : function() {
															return 'yes'
														}
													} ],
													fields : [ 'fndDisp',
															'fundCode',
															'fundName' ],
													valueField : 'fundCode',
													displayField : 'fndDisp',
													tabIndex : 3,
													loadToClass : false,
													listeners : {
														populated : function(
																fld, record) {
															if (this.loadToClass) {
																_controller
																		.loadClass(
																				record.data['fundCode'],
																				_popups["distribDetl"]
																						.getField("toClass"));
															}
														},
														cleared : function() {
															_popups["distribDetl"]
																	.getField(
																			"toClass")
																	.reset();
															_popups["distribDetl"]
																	.getField(
																			"toClass")
																	.disable();
														}
													}
												}),
										new DesktopWeb.Controls.ComboBox(
												{
													itemId : "toClass",
													fieldLabel : _translationMap['ToClass'],
													width : 75,
													allowBlank : false,
													autoSelect : true,
													tabIndex : 2,
													store : new Ext.data.XmlStore(
															{
																record : 'ClassInfo',
																fields : [
																		'classCode',
																		'description' ],
																listeners : {
																	load : function(
																			store,
																			records) {
																		if (records.length > 0) {
																			_popups["distribDetl"]
																					.getField(
																							"toClass")
																					.enable();
																			_popups["distribDetl"]
																					.getField(
																							"toClass")
																					.setValue(
																							records[0].data['classCode']);
																		}
																	}
																}
															}),
													valueField : 'classCode',
													displayField : 'classCode'
												}),
										new DesktopWeb.Controls.NumberField(
												{
													itemId : "prcnt",
													fieldLabel : _translationMap['SplitPercent'],
													allowDecimals : true,
													allowNegative : false,
													allowBlank : false,
													decimalPrecision : 4,
													maxLength : 8,
													minValue : 0.0001,
													maxValue : 100.0000,
													width : 60,
													style : 'text-align: right;'
												}) ]
							} ],
					buttons : [
							new DesktopWeb.Controls.ActionButton(
									{
										itemId : 'okBtn',
										text : _translationMap['OK'],
										handler : function() {
											var distribDetlData = _popups['distribDetl']
													.getData();
											if (_controller
													.isValidDistribDetlRecord(distribDetlData)) {
												_controller
														.updateDistribDetlRecord(distribDetlData);
												_controller.updatesFlag = true;
											}
										}
									}), new DesktopWeb.Controls.ActionButton({
								itemId : 'canBtn',
								text : _translationMap['Cancel'],
								handler : function() {
									_popups['distribDetl'].hide();
								}
							}) ],
					init : function(action) {
						// initialize popup based on action
						var popup = _popups['distribDetl'];
						popup.action = action;

						switch (action) {
						case _controller.ADD: {
							popup
									.setTitle(_translationMap["FundDistributionSplitDetl"]
											+ " - " + _translationMap["Add"]);
							popup.populate(action);
							popup.get(0).hide();
							break;
						}
						case _controller.MOD: {
							popup
									.setTitle(_translationMap["FundDistributionSplitDetl"]
											+ " - " + _translationMap["Modify"]);
							popup.populate(action);
							popup.get(0).hide();
							break;
						}
						case _controller.DEL: {
							popup
									.setTitle(_translationMap["FundDistributionSplitDetl"]
											+ " - " + _translationMap["Delete"]);
							popup.populate(action);
							popup.disableAllFields();
							popup.get(0).show();
							break;
						}
						}
						if (popup.rendered)
							popup.syncSize();
					},
					populate : function(action) {
						var popup = _popups['distribDetl'];
						var distribMstrRecord = _grids['distribMstr']
								.getSelectedRecord();

						popup.getField('toFund').loadToClass = false;

						popup.clearAllFields();
						popup.enableAllFields();
						switch (action) {
						case _controller.ADD: {
							popup.version = '1';
							popup.runMode = _controller.ADD;
							popup.detlUUID = "DISTDETL"
									+ _controller.getNewUUID();
							popup.mstrUUID = distribMstrRecord.data['mstrUUID'];
							popup.getField('fromFund').setText(
									distribMstrRecord.data['fundDesc']);
							popup.getField('fromClass').setText(
									distribMstrRecord.data['classCode']);
							popup
									.getField('distribType')
									.setText(
											_controller
													.getDescriptionFromList(
															distribMstrRecord.data['distribType'],
															"DistributionTypeList"));
							popup.getField('distribOpt').setValue("");
							popup.getField('distribOpt').clearInvalid();
							popup.getField('toFund').setValue("");
							popup.getField('toFund').clearInvalid();
							popup.getField('toClass').setValue("");
							popup.getField('toClass').clearInvalid();
							popup.getField('prcnt').setValue("0.00");
							popup.getField('prcnt').clearInvalid();
							break;
						}
						case _controller.MOD: {
							var distribMstrRec = _grids['distribMstr']
									.getSelectedRecord();
							var distribDetlRec = _grids['distribDetl']
									.getSelectedRecord();
							popup.runMode = distribDetlRec.data['runMode'];
							popup.version = distribDetlRec.data['version'];
							popup.mstrUUID = distribDetlRec.data['mstrUUID'];
							popup.detlUUID = distribDetlRec.data['detlUUID'];

							popup.getField('fromFund').setText(
									distribMstrRecord.data['fundDesc']);
							popup.getField('fromClass').setText(
									distribMstrRecord.data['classCode']);
							popup
									.getField('distribType')
									.setText(
											_controller
													.getDescriptionFromList(
															distribMstrRecord.data['distribType'],
															"DistributionTypeList"));

							popup.getField('distribOpt').setValue(
									distribDetlRec.data['distribOpt']);

							if (distribDetlRec.data['distribOpt'] === _controller.DISTRIBUTION_OPTION_CASH
									|| distribDetlRec.data['distribOpt'] === _controller.DISTRIBUTION_OPTION_REINVEST) {
								popup.getField("toFund").disableField();
								popup.getField("toClass").disableField();
							}
							popup.getField('toFund').prepopulate(
									distribDetlRec.data['toFundCode'],
									distribDetlRec.data['toFundDesc']);
							popup.getField('prcnt').setValue(
									distribDetlRec.data['prcnt']);

							_controller.loadClass(
									distribDetlRec.data['toFundCode'],
									_popups["distribDetl"].getField("toClass"),
									distribDetlRec.data['toClassCode']);
							break;
						}
						case _controller.DEL: {
							var distribMstrRec = _grids['distribMstr']
									.getSelectedRecord();
							var distribDetlRec = _grids['distribDetl']
									.getSelectedRecord();
							popup.runMode = distribDetlRec.data['runMode'];
							popup.version = distribDetlRec.data['version'];
							popup.mstrUUID = distribDetlRec.data['mstrUUID'];
							popup.detlUUID = distribDetlRec.data['detlUUID'];

							popup.getField('fromFund').setText(
									distribMstrRecord.data['fundDesc']);
							popup.getField('fromClass').setText(
									distribMstrRecord.data['classCode']);
							popup
									.getField('distribType')
									.setText(
											_controller
													.getDescriptionFromList(
															distribMstrRecord.data['distribType'],
															"DistributionTypeList"));

							popup.getField('distribOpt').setValue(
									distribDetlRec.data['distribOpt']);
							popup.getField('toFund').prepopulate(
									distribDetlRec.data['toFundCode'],
									distribDetlRec.data['toFundDesc']);
							popup.getField('prcnt').setValue(
									distribDetlRec.data['prcnt']);

							_controller.loadClass(
									distribDetlRec.data['toFundCode'],
									_popups["distribDetl"].getField("toClass"),
									distribDetlRec.data['toClassCode']);
							break;
						}
						}

						popup.getField('toFund').loadToClass = true;

						if (popup.rendered)
							popup.syncSize();
					},
					getData : function() {
						var popup = _popups['distribDetl'];
						var data = {};

						data['mstrUUID'] = popup.mstrUUID;
						data['detlUUID'] = popup.detlUUID;
						data['action'] = popup.action;
						data['runMode'] = popup.runMode;
						data['version'] = popup.version;
						data['distribOpt'] = popup.getField('distribOpt')
								.getValue();
						data['toFundCode'] = popup.getField('toFund')
								.getValue();
						data['toFundDesc'] = popup.getField('toFund')
								.getRawValue();
						data['toClassCode'] = popup.getField('toClass')
								.getValue();
						data['toClassDesc'] = popup.getField('toClass')
								.getRawValue();
						data['prcnt'] = popup.getField('prcnt').getValue();

						return data;
					}
				}),
		admin : new DesktopWeb.AdvancedControls.PopupWindow({
			title : ' ',
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
		}),
		history : new DesktopWeb.AdvancedControls.HistoryPopup()
	}

	// PUBLIC ITEMS
	return {
		layoutWidth : _layoutWidth

		,
		layoutHeight : _layoutHeight

		,
		fields : _fields

		,
		grids : _grids

		,
		popups : _popups

		,
		buttons : _buttons

		,
		layout : new Ext.Container({
			height : _layoutHeight,
			width : _layoutWidth,
			items : [
					{
						xtype : 'fieldset',
						title : "Search",
						width : _layoutWidth,
						items : [ {
							itemId : 'mainLayout1',
							style : 'padding-left:5px; padding-right:10px',
							layout : 'column',
							items : [
									{
										layout : 'form',
										columnWidth : 0.60,
										labelWidth : 100,
										items : [ _fields['fundFld'],
												_fields['distribTypeFld'] ]
									}, {
										layout : 'form',
										columnWidth : 0.25,
										labelWidth : 35,
										items : [ _fields['classFld'], {
											layout : 'auto',
											style : 'margin-top: 10px;',
											items : [ _fields['activeBox'] ]
										} ]
									}, {
										layout : 'auto',
										columnWidth : 0.15,
										labelWidth : 80,
										items : [ _buttons['searchBtn'] ]
									} ]
						} ]
					}, {
						xtype : 'fieldset',
						title : "Distributions",
						width : _layoutWidth,
						items : [ {
							layout : 'form',
							items : [ _grids["distribMstr"] ]
						} ]
					}, {
						xtype : 'fieldset',
						title : "Distribution Details",
						width : _layoutWidth,
						items : [ {
							layout : 'form',
							items : [ _grids["distribDetl"] ]
						} ]
					} ]
		}),
		screenButtons : [ new DesktopWeb.Controls.ScreenButton({
			text : _translationMap['OK'],
			handler : function() {
				if (_controller.hasUpdatedRecords() && _controller.updatesFlag) {
					_controller.clearContextErrors();
					if (_controller.isScreenValid()) {
						DesktopWeb.Util.commitScreen();
					}
				} else {
					_controller.updatesFlag = false;
					DesktopWeb.Util.cancelScreen();
				}
			}
		}), new DesktopWeb.Controls.ScreenButton({
			text : _translationMap['Cancel'],
			handler : function() {
				if (_controller.updatesFlag) {
					DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
				} else {
					cancelScreen(true);
				}
				function cancelScreen(confirm) {
					if (confirm)
						DesktopWeb.Util.cancelScreen();
				}
			}
		}) ]
	}
}