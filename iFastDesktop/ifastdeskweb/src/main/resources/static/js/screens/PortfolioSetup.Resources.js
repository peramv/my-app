/*********************************************************************************************
 * @file	PortfolioSetup.Resources.js
 * @author	Chatchai Daecha
 * @desc	Resources JS file for Portfolio Setup screen
 *********************************************************************************************/

 /*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *     - Fix display date format follows dateFormatDisplay parameter
 *
 *  17 Jun 2016 Matira T. P0255810 CHG0045497 T83083
 *     - Added new field "Family Specimen Number"
 *     
 *  25 Jan 2019 Ravindra P0300024-35
 *	   - Allow Multiple DIFs in a Portfolio. 
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 390;
	var _layoutWidth = 830;	
	
	// **** fields ****
	var _fields = {
		searchType : new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['SearchBy']
			,width:150
			,listeners: {
				select: function(){
					if (_fields['searchFromDate'].isValid() & _fields['searchToDate'].isValid())
					{
						_controller.updateSearchType();
					}
				}													
			}
		})
		,searchFromDate : new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['FromDate']
			,width: 100
			,allowBlank: false		
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,searchToDate : new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['ToDate']
			,width: 100
			,allowBlank: false			
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,searchPortfolioID : new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['PortfolioCode']
			,width: 120			
		})
		,searchPortfolioName : new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['PortfolioName']
			,width: 120			
		})
		,activeOnly: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['ShowActiveRecords']			
			,listeners: {
				check: function(){					
					_grids['detls'].getStore().filterBy(_controller.filterDetlRecords);
				}
			}
		})		
	}
	
	// **** grids ****
	var _grids = {
		mstrs: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth			
			,autoScroll: true
			,height: 150
			,autoExpandColumn: 'name'
			,store: new Ext.data.XmlStore({
				record: 'Mstr'
				,fields: ['errorMsg', 
						  'runMode', 
						  'portfolioUUID', 
						  'portfolioCode', 
						  'portfolioInUse',
						  'name',
						  'businessNo', 
						  'deff', 
						  'stopDate',
						  'modUser',
						  'modDate',
						  'version',
						  'allowUpd',
						  'businessNo-Family']
				,listeners: {
					load: function(store, records)
					{		
						Ext.each(records, function(record){
								record.data['deff'] = DesktopWeb.Util.getDateDisplayValue(record.data['deff']);
								record.data['stopDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['stopDate']);
								record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);
						});
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL;
						})
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(){
						_controller.updateSelectedMstrRecord();							
					}
					,rowdeselect: function(){
						_controller.updateSelectedMstrRecord();
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{
						width: 25
						,mapping: 'errorMsg'
						,renderer: function(val){
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');							
						}
					}
					,{header: _translationMap['PortfolioCode'], dataIndex: 'portfolioCode', width: 150}
					,{header: _translationMap['PortfolioName'], id: 'name', dataIndex: 'name'}
					,{header: _translationMap['Family'] + "<br\>" + _translationMap['BusinessNumber'], id: 'businessNo-Family', dataIndex: 'businessNo-Family'}
					,{header: _translationMap['Individual'] + "<br\>" + _translationMap['BusinessNumber'], id: 'businessNo', dataIndex: 'businessNo'}
					,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width:100}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width:100}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup('mstrs', _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup('mstrs', _controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup('mstrs', _controller.DEL);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup('mstrs');}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'historicalBtn'
					,text: _translationMap['Historical']
					,handler: function(){_controller.openHistoricalPopup('mstrs');}
				})
			]
		})
		,detls: new DesktopWeb.AdvancedControls.GridPanel({				
			autoScroll: true
			,height: 150
			,autoExpandColumn: 'invType'
			,width: 480
			,style: 'margin-right:10px;'			
			,store: new Ext.data.XmlStore(
				{
					record: 'Detl'
					,fields: ['errorMsg', 
							  'runMode', 
							  'detlUUID', 
							  'investmentType',
							  'invTypeDesc', 
							  'contractType', 
							  'contractVer', 
							  'fund', 
							  'class',
							  'defaultFund',
							  'deff', 
							  'stopDate',
							  'userName',
							  'modUser',
							  'modDate',
							  'version',
							  'active'							  
							 ]
					,listeners: {
						load: function(store, records)
						{							
							Ext.each(records, function(record){
								record.data['deff'] = DesktopWeb.Util.getDateDisplayValue(record.data['deff']);
								record.data['stopDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['stopDate']);
								record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);
							});
							store.filterBy(_controller.filterDetlRecords);
						}						
					}
				}
			)
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						_controller.updateGridButtons()
					}
					,rowdeselect: function(){
						_controller.updateGridButtons()
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{width: 25
					, mapping: 'errorMsg'
					, renderer: function(val){
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');							
						}
					}
					,{header: _translationMap['InvestmentCategory'], dataIndex: 'invTypeDesc', id: 'invType'}
					,{header: _translationMap['ContractType'], dataIndex: 'contractType', width: 80}
					,{header: _translationMap['Version'], dataIndex: 'contractVer', width: 48}
					,{header: _translationMap['Fund'], dataIndex: 'fund', width: 45}
					,{header: _translationMap['Class'], dataIndex: 'class', width: 38}
					,{header: _translationMap['Default'], dataIndex: 'defaultFund', width: 100}
					,{header: _translationMap['EffDate'], dataIndex: 'deff', width: 65}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width: 65}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup( 'detls', _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup( 'detls', _controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup('detls', _controller.DEL);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup('detls');}
				})					
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'historicalBtn'
					,text: _translationMap['Historical']
					,handler: function(){_controller.openHistoricalPopup('detls');}
				})
			]
		})
		,plans: new DesktopWeb.AdvancedControls.GridPanel({			
			autoScroll: true
			,height: 150
			,autoExpandColumn: 'name'
			,width: 340
			,store: new Ext.data.XmlStore({
				record: 'Plan'
				,fields: [ 'errorMsg', 
							'runMode', 
							'planUUID', 
							'planCode', 
							'name', 
							'defaultPlan',
							'userName',
							'modUser',
							'modDate',
							'version'							
						]
				,listeners: {
					load: function(store, records)
					{			
						Ext.each(records, function(record){
							record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);
						});
								
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL;
						})
					}
					,update: function(store)
					{								
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL;
						});
					}	
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						_controller.updateGridButtons()
					}
					,rowdeselect: function(){
						_controller.updateGridButtons()
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{width: 25
					, mapping: 'errorMsg'
					, renderer: function(val){							
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}
					,{header: _translationMap['PlanCode'], dataIndex: 'planCode', width: 75}
					,{header: _translationMap['PlanName'], id: 'name', dataIndex: 'name'}
					,{header: _translationMap['Default'], dataIndex: 'defaultPlan', width: 60}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup( 'plans', _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup('plans', _controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup('plans', _controller.DEL);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup('plans');}
				})					
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'historicalBtn'
					,text: _translationMap['Historical']
					,handler: function(){_controller.openHistoricalPopup('plans');}
				})					
			]
		})
	}
	
	// **** popups ****
	var _popups = {
		mstrs: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 470
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false, style: 'padding:4px'}				
				,portfolioInUse: null
				,items: [
					{
						html: _translationMap['DeleteConfirmMsg']
						,style: 'text-align:center'
					}
					,{
						layout: 'form'								
						,labelWidth: 120
						,defaults: {border:false}							
						,items: [
							new DesktopWeb.Controls.TextField({
								itemId: 'portfolioCode'
								,fieldLabel: _translationMap['PortfolioCode']
								,width: 185
								,allowBlank: false													
							})
							,new DesktopWeb.Controls.TextField({
								itemId: 'name'
								,width: 302
								,fieldLabel: _translationMap['PortfolioName']
								,allowBlank: false									
							})
                            ,{
                                layout: 'form'
                                ,labelWidth: 165
                                ,defaults: {border:false}							
                                ,items: [
                                    new DesktopWeb.Controls.TextField({
                                        itemId: 'businessNo'
                                        ,width: 257
                                        ,fieldLabel: _translationMap['Individual'] + _translationMap['BusinessNumber']
                                        ,allowBlank: true
                                    })
                                    ,new DesktopWeb.Controls.TextField({
                                        itemId: 'businessNo-Family'
                                        ,width: 257
                                        ,fieldLabel: _translationMap['Family'] + _translationMap['BusinessNumber']
                                        ,allowBlank: true
                                    })
                                ]
                            }							
							,{
								layout: 'column'
								,defaults: {border:false, layout: 'form'}
								,items: [
									{
										columnWidth: 0.58
										,labelWidth: 120
										,items: [
											new DesktopWeb.Controls.DateField({
												itemId: 'deff'
												,fieldLabel: _translationMap['EffectiveDate']
												,allowBlank: false
												,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											})
										]
									}
									,{
										labelWidth: 75
										,columnWidth: 0.42
										,items: [								
											new DesktopWeb.Controls.DateField({
												itemId: 'stopDate'
												,fieldLabel: _translationMap['StopDate']
												,allowBlank: false
												,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											})
										]
									}
								]
							}			
						]
					}					
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
						text: _translationMap['OK']
						,handler: function()
						{
							if (_popups['mstrs'].isValid())
							{ 
								_controller.saveMstrRecord(_popups['mstrs'].action, _popups['mstrs'].getData());
							}						
						}
					})
					,new DesktopWeb.Controls.ActionButton({
						text: _translationMap['Cancel']
						,handler: function(){
							_popups['mstrs'].hide();
						}							
					})
				]
				,init: function(action)
				{
					this.action = action
					this.clearAllFields();
					this.disableAllFields();
					this.get(0).hide(); //hide delete message
					
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle(_translationMap['Portfolio']+ ' - ' +_translationMap['Add']);
							this.populateDefaultValues();
							this.enableAllFields();
							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['Portfolio']+ ' - ' +_translationMap['Modify']);							
							this.populateWithSelectedRecord();
														
							if (this.portfolioInUse)
							{
								this.getField('stopDate').enableField();
								this.getField('businessNo').disableField();
							}
							else
							{
								this.getField('portfolioCode').disableField();
								this.enableAllFields();
							}							
							break;
						}
						case _controller.DEL:
						{
							this.setTitle(_translationMap['Portfolio']+ ' - ' +_translationMap['Delete']);
							this.get(0).show(); //show delete message
							this.populateWithSelectedRecord();
							this.disableAllFields();
							break;
						}
					}
				}
				,populateDefaultValues: function()
				{					
					this.getField('deff').setValue(_controller.getDefaultValue('deff'));
					this.getField('stopDate').setValue(_controller.getDefaultValue('stopDate'));
				}
				,populateWithSelectedRecord: function()
				{
					var rec = _grids['mstrs'].getSelectedRecord();
					this.getField('portfolioCode').setValue(rec.data['portfolioCode']);
					this.getField('name').setValue(rec.data['name']);
					this.getField('businessNo').setValue(rec.data['businessNo']);
					this.getField('businessNo-Family').setValue(rec.data['businessNo-Family']);
					this.getField('deff').setValue(rec.data['deff']);
					this.getField('stopDate').setValue(rec.data['stopDate']);
					this.portfolioInUse = (rec.data['portfolioInUse'].toLowerCase() == 'yes')
				}
				,getData: function()
				{
					var data = {};
					data['runMode'] = this.action;					
					data['portfolioCode'] = this.getField('portfolioCode').getValue();									
					data['name'] = this.getField('name').getValue();
					data['businessNo'] = this.getField('businessNo').getValue();
					data['businessNo-Family'] = this.getField('businessNo-Family').getValue();
					data['deff'] = this.getField('deff').getSMVDateString();
					data['stopDate'] = this.getField('stopDate').getSMVDateString();
					data['portfolioInUse'] = (this.portfolioInUse ? 'yes': 'no');
					return data;
				}
			}
		)
		,detls: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 490
			,closeAction: 'hide'
			,modal: true
			,defaults: {border:false, style: 'padding:4px'}		
			,portfolioUUID: null
			,optionsXML: null
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center'
				}
				,{
					layout: 'form'														
					,labelWidth: 125
					,defaults: {border: false}
					,items: [ 
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'investmentType'
							,fieldLabel: _translationMap['InvestmentCategory']
							,width: 200	
							,allowBlank: false
							,changeHandler: function(callbackFn){
								var investType = _popups['detls'].getField('investmentType').getValue();								
								var fundFld = _popups['detls'].getField('fund');								
								var classFld = _popups['detls'].getField('class');								
								var contractTypeFld = _popups['detls'].getField('contractType');
								var defaultfld = _popups['detls'].getField('defaultFund');
								
								if (investType.toLowerCase() == 'd') {
									defaultfld.enableField();
								}
																													
								_controller.fetchDetlOptions(_popups['detls'].portfolioUUID, 
									investType,
									_popups['detls'].action, 
									callback);
								function callback(optionsXML)
								{
									_popups['detls'].optionsXML = optionsXML;
									var contractTypeFld = _popups['detls'].getField('contractType');
									if (investType != 'S')
									{	
										fundFld.changeHandler();																																 								
										fundFld.loadData(IFDS.Xml.getNode(optionsXML, 'List[@listName="FundLists"]'));
										fundFld.shGroupXML = IFDS.Xml.getNode(optionsXML, 'ShGroupList');
										if(_popups['detls'].action ==  _controller.MOD) {
											fundFld.disableField();
											fundFld.changeHandler();
											classFld.disableField();
										} else {
											fundFld.clearValue();
											fundFld.enableField();
										}
										contractTypeFld.clearValue();
										contractTypeFld.disableField();										
										contractTypeFld.changeHandler();											
									} 
									else
									{
										contractTypeFld.clearValue();
										contractTypeFld.changeHandler();
										contractTypeFld.loadData(IFDS.Xml.getNode(optionsXML, 'List[@listName="ContractTypeLists"]'));
										contractTypeFld.enableField();
										fundFld.clearValue();
										fundFld.disableField();										
										fundFld.changeHandler();
									}
									
									if (investType.toLowerCase() != 'd') {
										defaultfld.clearValue();
										defaultfld.disableField();
									}
									
									if (callbackFn)
									{
										callbackFn();
									}									
								}									
							}							 					
							,listeners: {
								select: function(){this.changeHandler()}								
							} 
						})
						,{
							layout: 'column'							
							,defaults: {border: false, layout: 'form'}
							,items: [
								{
									columnWidth: 0.60
									,labelWidth: 125
									,items: [ 
										new DesktopWeb.Controls.SMVComboBox({
											itemId: 'contractType'
											,width: 120
											,fieldLabel: _translationMap['ContractType']
											,validator: function(val)
											{
												var investType = _popups['detls'].getField('investmentType').getValue().toLowerCase();
												if (investType == "" || investType != 's' || val != "")
												{
													return true
												}
												else
												{
													return _translationMap['FldRequired']
												} 
											}	
											,changeHandler: function(){													
													var contractVerFld = _popups['detls'].getField('contractVer');
													contractVerFld.clearField();									
													if (this.getValue() != "")
													{	
														contractVerFld.loadData(IFDS.Xml.getNode(_popups['detls'].optionsXML, 'List[@listName="' + this.getValue() + 'VersionLists"]'));
														contractVerFld.enableField();
													}
													else
													{														
														contractVerFld.disableField();
													}
												} 
											,listeners:{
												select: function(){this.changeHandler()}
												,blur: function(){this.changeHandler()}
												,change: function(){this.changeHandler()}
											}		
										})
										,new DesktopWeb.Controls.SMVComboBox({
											itemId: 'fund'
											,fieldLabel: _translationMap['Fund']
											,width: 90
											,shGroupXML: null											
											,validator: function(val)
											{
												var investType = _popups['detls'].getField('investmentType').getValue().toLowerCase();
												if (investType == "" || investType == 's' || val != "")
												{
													return true;
												}
												else
												{
													return _translationMap['FldRequired'];
												} 
											}	
											,changeHandler: function(){
												var fundFld = _popups['detls'].getField('fund');
												var classFld = _popups['detls'].getField('class');
												
												classFld.clearValue();
												if (fundFld.getValue() != "")
												{			
													_controller.fetchClassList(fundFld.getValue(), fundFld.shGroupXML, callback);
												}
												else
												{													
													classFld.disableField();
												} 
																								
												function callback(classListXML)
												{
													classFld.loadData(classListXML);
													if(_popups['detls'].action ==  _controller.MOD) {
														classFld.disableField();
													} else {
														classFld.enableField();
													}
												}
												
											}																			
											,listeners:{
												select: function() {this.changeHandler()}
											}										
										})
										,new DesktopWeb.Controls.DateField({
											itemId: 'deff'
											,fieldLabel: _translationMap['EffectiveDate']
											,width: 90					
											,allowBlank: false						
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										})
										,new DesktopWeb.Controls.SMVComboBox({
											itemId: 'defaultFund'
											,fieldLabel: _translationMap['Default']
											,width: 100
										})
													
									]
								}
								,{
									columnWidth: 0.40
									,labelWidth: 70
									,items: [  
										new DesktopWeb.Controls.SMVComboBox({
											itemId: 'contractVer'
											,fieldLabel: _translationMap['Version']
											,width: 75
											,validator: function(val){
												if (_popups['detls'].getField('contractVer').disabled
													|| _popups['detls'].getField('contractVer').getStore().getCount() == 0
													|| val != "")
												{
													return true;
												}
												else
												{
													return _translationMap['FldRequired'];
												}
											}											
										})
										,new DesktopWeb.Controls.SMVComboBox({
											itemId: 'class'
											,fieldLabel: _translationMap['Class']
											,width: 75
											,validator: function(val)
											{
												var investType = _popups['detls'].getField('investmentType').getValue().toLowerCase();
												if (investType == "" || investType == 's' || val != "")
												{
													return true
												}
												else
												{
													return _translationMap['FldRequired']
												} 
											}												
										})																					
										,new DesktopWeb.Controls.DateField({
											itemId: 'stopDate'
											,fieldLabel: _translationMap['StopDate']
											,width: 90
											,allowBlank: false											
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										})
									]
								}
							]
						}						
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function()
					{
						if (_popups['detls'].isValid(_popups['detls'].action))
						{ 
							_controller.saveDetlRecord(_popups['detls'].action, _popups['detls'].getData());
						}						
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){							
						_popups['detls'].hide();							
					}
				})
			]
			,init: function(action, portfolioUUID)
			{		
				this.action = action;
				this.portfolioUUID = portfolioUUID;
				this.clearAllFields();
				this.get(0).hide(); //hide delete message
				this.disableAllFields();
				
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['Investment']+ ' - ' +_translationMap['Add']);
						this.getField('deff').enableField();
						this.getField('stopDate').enableField();
						this.populateWithDefaultValues();
						this.getField('investmentType').enableField();
						this.getField('investmentType').clearValue();
						this.getField('fund').clearValue();
						this.getField('class').clearValue();
						this.getField('defaultFund').clearValue();
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['Investment']+ ' - ' +_translationMap['Modify']);
						this.populateWithSelectedRecord(this.action);
						if(this.getField('investmentType').getValue().toLowerCase() == 'd') {
							this.getField('defaultFund').enableField();
						}
						this.getField('deff').enableField();
						this.getField('stopDate').enableField();
						this.getField('fund').disableField();
						this.getField('class').disableField();
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['Investment']+ ' - ' +_translationMap['Delete']);
						this.get(0).show(); //show delete message						
						this.populateWithSelectedRecord(this.action);
						break;
					}
				}				
			}
			,populateWithDefaultValues: function()
			{
				var mstrRecord = _grids['mstrs'].getSelectedRecord();
				this.getField('deff').setValue(mstrRecord.data['deff']);
				this.getField('stopDate').setValue(mstrRecord.data['stopDate']);
			}	
			,isValid: function(action) {
				var grid = _grids['detls'];
				var popup = _popups['detls'];
				var valid = true;
				valid = popup.getField('fund').isValid() && valid;
				valid = popup.getField('defaultFund').isValid() && valid;
				var numberOfRows = grid.getStore().getCount();
				
				var newFundValue = popup.getField('fund').getValue();
				if (this.getField('investmentType').getValue().toLowerCase() == 'd') {
					var defaultFund = popup.getField('defaultFund').getValue();
					if (action == _controller.ADD) {
						for (var i = 0; i < numberOfRows; i++) {
							var funds = grid.getStore().getAt(i).data.fund;
							if(newFundValue == funds ) {
								popup.getField('fund').markInvalid(_translationMap['ERR_DUPLICATE_DIF']);
								valid = false;
							}
						}
					}
					
					if (action == _controller.ADD || action == _controller.MOD) {
						if(defaultFund ==_controller.YES) {
							for (var i = 0; i < numberOfRows; i++) {
								var defaultFunds = grid.getStore().getAt(i).data.defaultFund;
								var currentFundValue = grid.getStore().getAt(i).data.fund;
								if( (defaultFunds) == defaultFund && newFundValue != currentFundValue ) {
									popup.getField('defaultFund').markInvalid(_translationMap['ERR_DIF_ALLOWED_AS_DEFAULT']);
									valid = false;
								}
							}
						}
						if(action == _controller.MOD && defaultFund ==_controller.NO) {
							var numOfDifInGrid = 0;
							var gridDefaultFund;
							for(var i = 0; i < numberOfRows; i++) {
								if(grid.getStore().getAt(i).data.investmentType == 'D') {
									numOfDifInGrid++;
									gridDefaultFund = grid.getStore().getAt(i).data.defaultFund;
								}
							}
							if(numOfDifInGrid == 1 && (gridDefaultFund ==_controller.YES)) {
								DesktopWeb.Util.displayError(_translationMap['ERR_DEFAULT_FUND_MUST_SETUP']);
								valid = false;
							}
						}
					}
					if (action == _controller.DEL) {
						if(defaultFund ==_controller.YES) {		
							DesktopWeb.Util.displayError(_translationMap['ERR_DEFAULT_FUND_MUST_SETUP']);
							valid = false;
						}
					}
				}
				return valid;
			}
			,populateWithSelectedRecord: function(action)
			{
				var rec = _grids['detls'].getSelectedRecord();
				if (action == _controller.MOD)
				{
					var self = this;
					this.getField('investmentType').setValue(rec.data['investmentType']);
					this.getField('investmentType').changeHandler(callback);
					
					function callback()
					{
						self.getField('contractType').setValue(rec.data['contractType']);
						self.getField('contractType').changeHandler();
						self.getField('contractVer').setValue(rec.data['contractVer']);
						self.getField('fund').setValue(rec.data['fund']);
						self.getField('class').setValue(rec.data['class']);	
						self.getField('defaultFund').setValue(rec.data['defaultFund']);
						self.getField('deff').setValue(rec.data['deff']);
						self.getField('stopDate').setValue(rec.data['stopDate']);
					}
				}
				else
				{
					this.getField('investmentType').setValue(rec.data['investmentType']);									
					this.getField('contractType').setValue(rec.data['contractType']);
					this.getField('contractVer').setValue(rec.data['contractVer']);	
					this.getField('fund').setValue(rec.data['fund']);
					this.getField('class').setValue(rec.data['class']);
					this.getField('defaultFund').setValue(rec.data['defaultFund']);
					this.getField('deff').setValue(rec.data['deff']);
					this.getField('stopDate').setValue(rec.data['stopDate']);					
				}
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['investmentType'] = this.getField('investmentType').getValue();
				data['invTypeDesc'] = this.getField('investmentType').getValueDesc();
				data['contractType'] = this.getField('contractType').getValue();
				data['contractVer'] = this.getField('contractVer').getValue();
				data['fund'] = this.getField('fund').getValue();
				data['class'] = this.getField('class').getValue();
				data['defaultFund'] = this.getField('defaultFund').getValue();
				data['deff'] = this.getField('deff').getSMVDateString();
				data['stopDate'] = this.getField('stopDate').getSMVDateString();
				data['active'] = 'yes';
				return data;
			}
		})
		,plans: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 344
			,closeAction: 'hide'
			,modal: true
			,defaults: {border:false, style: 'padding:4px'}	
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center'
				}
				,{
					layout: 'form'
					,labelWidth: 85																				
					,items: [ 
						new DesktopWeb.Controls.TextField({
							itemId: 'planCode'
							,width: 100
							,fieldLabel: _translationMap['PlanCode']
							,allowBlank: false
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'name'
							,width: 210
							,fieldLabel: _translationMap['PlanName']
							,allowBlank: false
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'defaultPlan'
							,fieldLabel: _translationMap['Default']
							,width: 100
							,allowBlank: false
						})
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function()
					{
						if (_popups['plans'].isValid())
						{ 
							_controller.savePlanRecord(_popups['plans'].action, _popups['plans'].getData());
						}						
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['plans'].hide();}					
				})
			]
			,init: function(action)
			{
				this.action = action
				this.clearAllFields();
				this.get(0).hide(); //hide delete message				
												
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['PortfolioPlan']+ ' - ' +_translationMap['Add']);
						this.enableAllFields();
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['PortfolioPlan']+ ' - ' +_translationMap['Modify']);
						this.enableAllFields();
						this.getField('planCode').disableField();
						this.populateWithSelectedRecord();						
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['PortfolioPlan']+ ' - ' +_translationMap['Delete']);
						this.get(0).show(); //show delete message
						this.disableAllFields();
						this.populateWithSelectedRecord();
						break;
					}
				}
			}
			,populateDefaultValues: function()
			{
				var defaultValues = _controller.getDefaultValues();
				this.getField('defaultPlan').setValue(defaultValues['defaultPlan']);
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['plans'].getSelectedRecord();
				this.getField('planCode').setValue(rec.data['planCode']);
				this.getField('name').setValue(rec.data['name']);
				this.getField('defaultPlan').setValue(rec.data['defaultPlan']);
			}			
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['planCode'] = this.getField('planCode').getValue();
				data['name'] = this.getField('name').getValue();
				data['defaultPlan'] = this.getField('defaultPlan').getValue();
				return data;
			}
		})
		,admin: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				width: 395				
				,closeAction: 'hide'
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
									new DesktopWeb.Controls.Label(
										{
											itemId: 'userName'
											,fieldLabel: _translationMap['Username']
										}
									)
									,new DesktopWeb.Controls.Label(
										{
											itemId: 'modUser'
											,fieldLabel: _translationMap['ModUser']
										}
									)
								]
							}
							,{
								width: 185
								,layout: 'form'
								,defaults: {width: 80}
								,items: [
									new DesktopWeb.Controls.Label(
										{
											itemId: 'procDate'
											,fieldLabel: _translationMap['ProcessDate']
										}
									)
									,new DesktopWeb.Controls.Label(
										{
											itemId: 'modDate'
											,fieldLabel: _translationMap['ModDate']
											,value: 'test'
										}
									)
								]
							}
						]
					}
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['OK']
							,handler: function(){_popups['admin'].hide();}
						}
					)
				]
				,init: function(title, data)
				{
					this.setTitle(title);
					this.getField('procDate').setValue(data['procDate']);
					this.getField('modDate').setValue(data['modDate']);
					this.getField('userName').setValue(data['userName']);
					this.getField('modUser').setValue(data['modUser']);	
				}
			}
		)
		,history: new DesktopWeb.AdvancedControls.HistoryPopup()
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth			
			,items: [
				{
					layout: 'column'
					,height: 65										
					,items: [
						{
							columnWidth: 0.33
							,layout: 'form'
							,labelWidth: 65
							,items: [
								_fields['searchType']
							]
						}
						,{
							columnWidth: 0.31
							,labelWidth: 90
							,layout: 'form'
							,items: [
								_fields['searchPortfolioID']
								,_fields['searchPortfolioName']									
							]
						}
						,{
							columnWidth: 0.26
							,labelWidth: 80
							,layout: 'form'
							,items: [									
								_fields['searchFromDate']
								,_fields['searchToDate']
							]
						}							
						,{
							columnWidth: 0.1
							,items: [
								new DesktopWeb.Controls.ActionButton({
									text: _translationMap['Search']
									,handler: function(){
										_controller.doSearch();
									}
								})
							]
						}							
					]
				}
				,_grids['mstrs']
				,{
					layout: 'auto'
					,items: [_fields['activeOnly']]
				}							
				,{
					layout: 'column'
					,items:[
						_grids['detls']							
						,_grids['plans']
					]
				}
			]
		})		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function() {
					if (_controller.updatesFlag) {
						_controller.doCommitValidate();
					} else {
						DesktopWeb.Util.cancelScreen();
					}				
				}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){
					if (_controller.updatesFlag)
					{
						DesktopWeb.Util.displayDiscardPrompt(callback)
					}
					else
					{
						callback(true);
					}
					
					function callback(discard)
					{
						if (discard)
						{				
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			})
		]
	}
}