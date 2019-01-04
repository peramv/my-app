/*********************************************************************************************
 * @file	TrailerFeeSetup.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for TrailerFeeSetup screen  
 *********************************************************************************************/
/*
 *  History : 
 *
 *  09 Oct 2013 G. Thawornwachirakun P0217718 T54332
 *					 DFT0022359: Fix status of scale-detl when add and then modify data
 *						, mode must be add.
 *					 DFT0023048: Revert code to be able to modify fields
 *						[Account level] Fund Group, Fund, and Class are disabled.
 *						[System level and BrokerBranceSlsRep] Fund Group, Fund, Class 
 *							, broker, branch, and slsrep fields are disabled.
 *
 *  01 Nov 2013 G. Thawornwachirakun P0217718 T54434
 *					 DFT0023321: When user input broker, branch, slsrep, the MaxFee 
 *											will be gray-out.
 *					 DFT0023316: Change dateformat display follows dateFormatDisplay
 *
 *  11 Nov 2013 G. Thawornwachirakun P0217718 T54441
 *           DFT0023571: Fix Front to auto populate to model 
 *               when user input Fund-Class or Fund Group; and gray-out model
 *               when user input broker,  branch,or slsrep
 *
 *  27 Nov 2013 G. Thawornwachirakun P0217718 T54442
 *           DFT0024910 : Fix DateField to not auto rotate date by system.
 *           DFT0024880 : StopDate Column is missing on Account screen
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 550;
	var _layoutWidth = 765;
	
	// **** fields ****
	var _fields = {
		searchValue: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['SearchBy']			
				,width: 120			
				,value: 'ALL'
					,listeners: {
						select: function(fld){_controller.showSearchFields()}				
					}
			}											
		)	
		,searchFundGroup: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['FundGroup']
				,listWidth: 130			
				,width: 75						
					,listeners: {
						render: function(fld){fld.hideField()}							
					}
			}											
		)	
		,searchFundCode: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['FundCode']
				,width: 60
					,listeners: {
						render: function(fld){fld.hideField()}
					}												
			}
		)
		,searchClassCode: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['ClassCode']			
				,width: 60
					,listeners: {
						render: function(fld){fld.hideField()}
					}																						
			}
		)			
		,searchBrokerCode: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['BrokerCode']			
				,width: 60
					,listeners: {
						render: function(fld){fld.hideField()}
					}																						
			}
		)
		,searchBranchCode: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['BranchCode']			
				,width: 60
					,listeners: {
						render: function(fld){fld.hideField()}
					}																						
			}
		)
		,searchSlsRepCode: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['SlsRepCode']			
				,width: 60
					,listeners: {
						render: function(fld){fld.hideField()}
					}																						
			}
		)
		,searchDistribChannel: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['DistributionChannel']		
				,width: 150
					,listeners: {
						render: function(fld){fld.hideField()}
					}																						
			}
		)		
	}
	
	var _selectors = {
		trailerRules: new DesktopWeb.AdvancedControls.ItemSelector(
			{
				height: 120
				, width:420
				,style: 'margin-top: 20px; margin-left:20px; margin-bottom: 10px'		
				,allowReordering: false	
				,availableGridProperties: {
					width: 150				
					,autoExpandColumn: 'trailerRule'
					,store: new Ext.data.XmlStore({
						record: 'Element'					
						,fields: ['code', 'value']														
					})						
					,columns: [
						{id: 'trailerRule', header: _translationMap['AvailableRules'], dataIndex: 'value'}								
					]
				}
				, selectedGridProperties: {
					width: 150
					,autoExpandColumn: 'trailerRule'
					,store: new Ext.data.XmlStore({
						record: 'Element'					
						,fields: ['code', 'value']														
					})						
					,columns: [
						{id: 'trailerRule', header: _translationMap['SelectedRules'], dataIndex: 'value'}								
					]
				}						
			}
		)	
	}
	
	// **** grids ****
	var _grids = {
		feeParms: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth
				,style: "margin-bottom:15px"
				,autoScroll: true							
				,height: 125									
				,store: new Ext.data.XmlStore(
					{
						record: 'FeeParms'
						,fields: ['brokerCode', 'branchCode', 'slsRepCode', 'fundGroup', 'fundCode', 'classCode', 'maxFee', 'effDate', 'stopDate', 'action', 'feeID', 'model', 'OverAllowed', 'OverAllowedDesc', 'distribChannel', 'distribChannelDesc', 'aggFundGroup', 'trailerRulesDisp', 'errmsg','tmpFeeID','ModelID'] 
						//,fields: ['fundGroup', 'fundCode', 'classCode', 'maxFee', 'effDate', 'stopDate', 'action', 'feeID', 'model', 'OverAllowed', 'OverAllowedDesc', 'distribChannel', 'distribChannelDesc', 'aggFundGroup', 'trailerRulesDisp']
						,listeners: {
							load: function(store, records)
							{
								// add xml node index reference to each record, for use with setting selected record,	
								// can't just rely on record index because items for deletion are filtered
								for (var r = 0; r < records.length; r++)
								{
									records[r].xmlIndex = r + 1;
									records[r].data.effDate = DesktopWeb.Util.getDateDisplayValue(records[r].data.effDate);
									records[r].data.stopDate = DesktopWeb.Util.getDateDisplayValue(records[r].data.stopDate);
								}
								store.filterBy(function(record){
									return record.data.action != 'delete'})
							}
							,dataChanged: function()
							{											
								_grids['feeParms'].enableButton('addBtn');
								_controller.clearSelectedFeeParm()
								//_grids['feeParms'].getSelectionModel().selectFirstRow();								
							}								
							,clear: function()
							{
								_controller.clearGrid('feeParmDetails');
							}													
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record)
							{
								// this event seems to be called repeatedly, so only interested when
								// data has been properly loaded and initialzed															
								if (record.xmlIndex)
								{																										
									_controller.setSelectedFeeParm(record.xmlIndex);									
								}
								else
								{
									_controller.clearSelectedFeeParm();	
								}
							}
							,rowdeselect: function(){_controller.clearSelectedFeeParm()}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							 {dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }, width: 25 }							 
							,{header: _translationMap['BrokerCode'], dataIndex: 'brokerCode', width:80,id: 'brokerCode'}
							,{header: _translationMap['BranchCode'], dataIndex: 'branchCode', width:80,id: 'branchCode' }
							,{header: _translationMap['SlsRepCode'], dataIndex: 'slsRepCode', width:80,id: 'slsRepCode'}
							,{header: _translationMap['FundGroup'], dataIndex: 'fundGroup', width:80, 
								renderer: function(value){ return (_controller.getListValueDesc('FundGroupOptions', value))}}
							,{header: _translationMap['FundCode'], dataIndex: 'fundCode', width:80}
							,{header: _translationMap['ClassCode'], dataIndex: 'classCode', width:80}																				
							,{header: _translationMap['EffectiveDate'], dataIndex: 'effDate', width:90}
							,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width:90, id: 'stopDate'}
							,{header: _translationMap['MaxFee'], dataIndex: 'maxFee', width:80, id: 'maxFee'}
							,{header: _translationMap['DistributionChannel'], dataIndex: 'distribChannelDesc', width:120}
							,{header: _translationMap['AggregationGroup'], dataIndex: 'aggFundGroup', width:120}
							,{header: _translationMap['TrailerRules'], dataIndex: 'trailerRulesDisp', width:120}
							,{header: _translationMap['Override'], dataIndex: 'OverAllowedDesc', width:240}
						]		
					}
				)
				,buttons: [					
					new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'addBtn'								
							,text: _translationMap['Add']							
							,handler: function(){_controller.openActionPopup('feeParms', _controller.ADD)}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'modBtn'
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup('feeParms', _controller.MOD)}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'delBtn'
							,text: _translationMap['Delete']
							,handler: function(){_controller.openActionPopup('feeParms', _controller.DEL)}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'moreBtn'
							,text: _translationMap['More']
							,handler: function(){_controller.doReload(true)}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'historicalBtn'
							,text: _translationMap['Historical']
							,handler: function(){_controller.openHistoryPopup('feeParms');}
						}
					)
				]			
			}
		)
		
		,feeParmDetails: new DesktopWeb.AdvancedControls.GridPanel(
			{																						
				height: 125																																										
				,store: new Ext.data.XmlStore(
					{
						record: 'FeeParmsDetail' 					
						,fields: ['GrandFthrEnd', 'AvgType', 'AvgTypeDesc', 'BalAsOf', 'BalAsOfDesc', 'SplitBy', 'SplitByDesc', 'AssetType', 'AssetTypeDesc', 'BalType', 'BalTypeDesc', 'FeeType', 'FeeTypeDesc', 'FeeRate', 'ModelID']
						,listeners: {
							load: function(store, records){
								// add xml node index reference to each record, for use with setting selected record,	
								// can't just rely on record index because items for deletion are filtered
								for (var r = 0; r < records.length; r++)
								{
									records[r].xmlIndex = r + 1;
								}																										
								_grids['feeParmDetails'].getSelectionModel().selectFirstRow();								
							}
							,clear: function(){_controller.clearGrid('scaleDetails');}		
							,dataChanged: function()
							{											
								_grids['feeParmDetails'].enableButton('addBtn');
								_controller.clearSelectedFeeParmDetail()																				
								//_grids['feeParms'].getSelectionModel().selectFirstRow();								
							}	
						}					
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){_controller.setSelectedFeeParmDetail(record.xmlIndex);}
							,rowdeselect: function(){_controller.clearSelectedFeeParmDetail();}								
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{header: _translationMap['GrandFatherEnd'], dataIndex: 'GrandFthrEnd', width:100}								
							,{header: _translationMap['EligBalanceType'], dataIndex: 'BalTypeDesc', width:150}
							,{header: _translationMap['BalanceAsOf'], dataIndex: 'BalAsOfDesc', width:100}
							,{header: _translationMap['AverageType'], dataIndex: 'AvgTypeDesc', width:140}						
							,{header: _translationMap['SplitBy'], dataIndex: 'SplitByDesc', width:70}
							,{header: _translationMap['AssetType'], dataIndex: 'AssetTypeDesc', width:70}
							,{header: _translationMap['Type'], dataIndex: 'FeeTypeDesc', width:70}
							,{header: _translationMap['Rate'], dataIndex: 'FeeRate', width:100}
						]										
					}
				)	
				,buttons: [						
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'addBtn'
							,text: _translationMap['Add']
							,handler: function(){_controller.openActionPopup('feeParmDetails', _controller.ADD)}
						}
					)	
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'modBtn'
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup('feeParmDetails', _controller.MOD)}
						}
					)						
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'historicalBtn'
							,text: _translationMap['Historical']
							,handler: function(){_controller.openHistoryPopup('feeParmDetails');}
						}
					)						
				]																								
			}
		)

		,scaleDetails: new DesktopWeb.AdvancedControls.GridPanel(
			{																									
				height: 125
				,store: new Ext.data.XmlStore(
					{
						record: 'scaleDetail'					
						,fields: ['lowBand', 'uprBand', 'rate', 'action']
						,listeners: {
							load: function(store, records){
								// add xml node index reference to each record, for use with setting selected record,	
								// can't just rely on record index because items for deletion are filtered																											
								for (var r = 0; r < records.length; r++)
								{
									records[r].xmlIndex = r + 1;
								}
								store.filterBy(function(record){return record.data.action != 'delete'})																																		
							}
							,dataChanged: function(){_grids['scaleDetails'].getSelectionModel().selectFirstRow();}																												
						}						
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect:true
						,listeners: {
							rowselect: function(selModel, index, record){																
								if (record.xmlIndex)
								{													
									_controller.setSelectedScaleDetail(record.xmlIndex);																										 								
								}
								else
								{																						
									_controller.clearSelectedScaleDetail();
								}
							}
							,rowdeselect: function(){_controller.clearSelectedScaleDetail();}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{header: _translationMap['LowerBound'], dataIndex: 'lowBand', width:100}
							,{header: _translationMap['UpperBound'], dataIndex: 'uprBand', width:100}
							,{header: _translationMap['ScaleRate'], dataIndex: 'rate', width:100}														
						]		
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'addBtn'
							,text: _translationMap['Add']
							,handler: function(){_controller.openActionPopup('scaleDetails', _controller.ADD)}
						}
					)																		
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'modBtn'
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup('scaleDetails', _controller.MOD)}
						}
					)						
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'delBtn'
							,text: _translationMap['Delete']
							,handler: function(){_controller.openActionPopup('scaleDetails', _controller.DEL)}
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'historicalBtn'
							,text: _translationMap['Historical']
							,handler: function(){_controller.openHistoryPopup('scaleDetails');}
						}
					)			
				]												
			}							
		)
		
		,history: new DesktopWeb.AdvancedControls.GridPanel(
			{																					
				autoScroll: true							
				,height: 125
				,disableSelection: true							
				,store: new Ext.data.XmlStore(
					{
						record: 'HistoricalInfo'					
						,fields: ['fldLbl', 'prevDisp', 'newDisp', 'modUsr', 'modDt', 'modTime']									
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{header: _translationMap['Field'], dataIndex: 'fldLbl', width:100}
							,{header: _translationMap['PrevValue'], dataIndex: 'prevDisp', width:100}
							,{header: _translationMap['NewValue'], dataIndex: 'newDisp', width:100}																				
							,{header: _translationMap['User'], dataIndex: 'modUsr', width:80}
							,{header: _translationMap['Date'], dataIndex: 'modDt', width:80}
							,{header: _translationMap['Time'], dataIndex: 'modTime', width:80}
						]		
					}
				)
			}
		)		
	}
	
	// **** popups ****
	var _popups = {
		feeParms: new DesktopWeb.AdvancedControls.PopupWindow(
			{					
				action: null
				,width: 500
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border: false}					
				,items: [
					{
						html: _translationMap['DeleteRecord']							
						,style: 'text-align:center'														
					}						
					,{													
						layout: 'column'							
						,defaults: {border: false}																				
						,items: [
							{
								columnWidth: 1
								,layout: 'form'
								,labelWidth: 80
								,style: 'padding-left: 4px; padding-top:4px;'												
								,items: [
									{													
										layout: 'column'							
										,border: false
										,defaults: {
											border: false
											,columnWidth: 0.33
											,layout: 'form'
											,labelWidth: 80
										}
										,style: 'padding-left: 0px; padding-top:4px;'
										,items: [
											{
												items: [
													new DesktopWeb.Controls.TextField(
														{
															itemId: 'brokerCode'
															,fieldLabel: _translationMap['BrokerCode']
															,width: 60
															,maxLength: 6															
															, enforceMaxLength : true
															,autoCreate: {tag: 'input', type: 'text', size: '20'
															              , autocomplete:'off', maxlength: '6'}
															,listeners: {
																render: function(fld){											
																	if (_controller.isAccountLevel())
																	{
																		fld.hideField();
																	}																	
																	
																	if (!(_controller.getDefaultValue('brokerApplicable')
																			|| _controller.getDefaultValue('branchApplicable')
																			|| _controller.getDefaultValue('salesRepApplicable')
																	))
																	{
																		fld.disable();
																	}	
																	
																}
																,change: function(fld){																																		
																		_controller.checkDisableField(null);
																}	
															}
															,allowBlank: true
																		  
														}
													)
												]
											}
											,{
												items: [
													new DesktopWeb.Controls.TextField(
														{
															itemId: 'branchCode'
															,fieldLabel: _translationMap['BranchCode']
															,width: 60
															,maxLength: 6
															, enforceMaxLength : true
															,autoCreate: {tag: 'input', type: 'text', size: '20'
															              , autocomplete:'off', maxlength: '6'}
															,listeners: {
																render: function(fld){											
																	if (_controller.isAccountLevel())
																	{
																		fld.hideField();
																	}
																		
																	if ( !_controller.isAllowBranch() || 
																		 (!(_controller.getDefaultValue('branchApplicable')
																			|| _controller.getDefaultValue('salesRepApplicable'))))
																	{
																		fld.disable();
																	}	
																}	
																,change: function(fld){																																		
																		_controller.checkDisableField(null);
																}
															}
															,allowBlank: true	
														}
													)
												]
											}
											,{
												items: [
													new DesktopWeb.Controls.TextField(
														{
															itemId: 'slsRepCode'
															,fieldLabel: _translationMap['SlsRepCode']
															,width: 60
															,maxLength: 6
															, enforceMaxLength : true
															,autoCreate: {tag: 'input', type: 'text', size: '20'
															              , autocomplete:'off', maxlength: '6'}
															,listeners: {
																render: function(fld){											
																	if (_controller.isAccountLevel())
																	{
																		fld.hideField();
																	}																																		
																		
																	if (!_controller.getDefaultValue('salesRepApplicable'))
																	{
																		fld.disable();
																	}	
																}
																,change: function(fld){																																		
																		_controller.checkDisableField(null);
																}																
															}
															,allowBlank: true				
														}
													)
												]
											}
										]
									}
								]
							}
							,{
								columnWidth: 0.55
								,layout: 'form'
								,labelWidth: 80
								,style: 'padding-left: 4px; padding-top:4px;'												
								,items: [
									new DesktopWeb.Controls.SMVComboBox(
										{						
											itemId: 'fundGroup'
											,fieldLabel: _translationMap['FundGroup']
											,width: 120
											,listeners: {
												select: function(){
													_controller.setModel();
												}
												,change: function(){
													_controller.setModel();
												}
											} 
										}											
									)											
									,new DesktopWeb.Controls.TextField(
										{	
											itemId: 'fundCode'					
											,fieldLabel: _translationMap['FundCode']		
											,width:80		
											,listeners: {
												change: function(fld){
														_controller.setModel()
												}
											}
										}
									)	
									,new DesktopWeb.Controls.TextField(
										{
											itemId: 'classCode'
											,fieldLabel: _translationMap['ClassCode']
											,width:80
											,listeners: {
												change: function(fld){
														_controller.setModel()
												}
											}
										}
									)					
									,new DesktopWeb.Controls.ComboBox(
										{
											itemId: 'model'
											,fieldLabel: _translationMap['Model']
											,width:120
											,store: new Ext.data.XmlStore(
												{
													record: 'Model'																													
													,fields: ['ModelID', 'AvgType', 'AvgTypeDesc', 'BalAsOf', 'BalAsOfDesc', 'BalType', 'BalTypeDesc']					
												}
											)
											,displayField: 'ModelID'
											,valueField: 'ModelID'			
											,listWidth: 400
											,itemSelector: 'div'
											,allowBlank: true
											,tpl: new Ext.XTemplate(
												'<tpl for=".">'
													,'<div class="fee-param-model" style="padding:2px">{AvgTypeDesc}/{BalAsOfDesc}/{BalTypeDesc}</div>'
												,'</tpl>'
											)
											,listeners: {
												select: function(){
													_controller.onChangeModel(this.value);
												}
												,change: function(){
													_controller.onChangeModel(this.value);
												}
											} 
										}
									)
									,new DesktopWeb.Controls.SMVComboBox(
										{						
											itemId: 'distribChannel'
											,fieldLabel: _translationMap['DistChannel']
											,width: 120		
										}											
									)									
								]								
							}							
							,{
								columnWidth: 0.45
								,layout: 'form'								
								,labelWidth: 100															
								,items: [
									new DesktopWeb.Controls.DateField(
										{
											itemId: 'effDate'
											,fieldLabel: _translationMap['EffectiveDate']
											,emptyText: _controller.getDateFormatTemplate(DesktopWeb.Util.getDateDisplayFormat())
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
											,listeners: {
												select: function(){
													_controller.setModel();
												}
												,change: function(){
													_controller.setModel();
												}
											} 
										}
									)
									,new DesktopWeb.Controls.DateField(
										{
											itemId: 'stopDate'
											,fieldLabel: _translationMap['StopDate']
											,emptyText: _controller.getDateFormatTemplate(DesktopWeb.Util.getDateDisplayFormat())
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
											,listeners: {
												select: function(){
													_controller.setModel();
												}
												,change: function(){
													_controller.setModel();
												}
											} 
										}
									)
									,new DesktopWeb.Controls.NumberField(
										{
											itemId: 'maxFee'
											,fieldLabel: _translationMap['MaxFee']
											,width: 80
											,allowDecimal: true
											,decimalPrecision: 4
											,allowNegative: false
											,maxValue: 100
											,listeners: {
												render: function(fld){											
													if (_controller.isAccountLevel())
													{
														fld.hideField()
													}
												}							
											}								
										
										}
									)
									,new DesktopWeb.Controls.SMVComboBox(
										{						
											itemId: 'aggFundGroup'
											,fieldLabel: _translationMap['AggrFundGroup']
											,width: 100		
										}											
									)									
								]
							}								
						]						
					}
					,{
						width: 450						
						,layout: 'form'
						,style: 'padding-left:4px'
						,labelWidth: 80												
						,items: [
							new DesktopWeb.Controls.SMVComboBox(
								{						
									itemId: 'OverAllowed'
									,fieldLabel: _translationMap['Override']
									,allowBlank: true
									,width: 290
									,listeners: {
										render: function(fld){											
											if (_controller.isAccountLevel())
											{
												fld.hideField()
											}
										}							
									}			
								}											
							)
							, _selectors['trailerRules']
						]
					}																
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if (_popups['feeParms'].isValid()){
									_controller.validateFeeParmUpdate(_popups['feeParms'].action);	
								}								
							}								
						}
					), 
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'cancelBtn'
							,text: _translationMap['Cancel']
							,handler:function(){_popups['feeParms'].hide()}
						}
					)
				]
				,init: function(action)
				{
					// initialize popup based on action					
					var popup = _popups['feeParms'];
					popup.action = action;
					popup.clearAllFields();																							
					switch(action)
					{
						case _controller.ADD:
						{
							popup.setTitle("Trailer Fee Parameter - Add");
							_controller.enableDisablefields(popup,true);
							popup.getField('maxFee').setValue(_controller.getDefaultValue('maxFee'));
							popup.getField('effDate').setValue(_controller.getDefaultValue('effDate'));
							popup.getField('stopDate').setValue(_controller.getDefaultValue('stopDate'));
							popup.getField('brokerCode').setValue(_controller.getDefaultValue('brokerCode'));
							popup.getField('branchCode').setValue(_controller.getDefaultValue('branchCode'));
							popup.getField('slsRepCode').setValue(_controller.getDefaultValue('slsRepCode'));
							popup.getField('model').setValue(_controller.getDefaultValue('model'));
							popup.getField('slsRepCode').setValue(_controller.getDefaultValue('slsRepCode'));
							popup.getField('fundGroup').setValue(_controller.getDefaultValue('fundGroup'));
							popup.getField('fundCode').setValue(_controller.getDefaultValue('fundCode'));
							popup.getField('classCode').setValue(_controller.getDefaultValue('classCode'));
							popup.getField('aggFundGroup').setValue(_controller.getDefaultValue('aggFundGroup'));
							popup.getField('OverAllowed').setValue(_controller.getDefaultValue('OverAllowed'));
							
							popup.enableAllFields();
							_controller.loadSelector(null);
							popup.get(0).hide();
							break;
						}
						case _controller.MOD:
						{
							popup.setTitle("Trailer Fee Parameter - Modify");							
							popup.enableAllFields();
							//enableAllFields() does not do the purpose !!!!							
							popup.populate();							
							popup.get(0).hide();
							_controller.enableDisablefields(popup,_controller.isNewRecord());
							break;
						}
						case _controller.DEL:
						{
							popup.setTitle("Trailer Fee Parameter - Delete");
							popup.populate();
							popup.disableAllFields();							
							popup.get(0).show();
							break;
						}							
					}
					
				}
				,populate: function()
				{
					var xml = _controller.getSelectedFeeParm();
					// prompt("", IFDS.Xml.serialize(xml));
					var popup = _popups['feeParms'];
					popup.getField('brokerCode').setValue(Ext.DomQuery.selectValue('brokerCode', xml));
					popup.getField('branchCode').setValue(Ext.DomQuery.selectValue('branchCode', xml));
					popup.getField('slsRepCode').setValue(Ext.DomQuery.selectValue('slsRepCode', xml));
					popup.getField('fundGroup').setValue(Ext.DomQuery.selectValue('fundGroup', xml));
					popup.getField('fundCode').setValue(Ext.DomQuery.selectValue('fundCode', xml));
					popup.getField('classCode').setValue(Ext.DomQuery.selectValue('classCode', xml));					
					popup.getField('effDate').setValue(DesktopWeb.Util.getDateDisplayValue(Ext.DomQuery.selectValue('effDate', xml)));
					popup.getField('stopDate').setValue(DesktopWeb.Util.getDateDisplayValue(Ext.DomQuery.selectValue('stopDate', xml)));
					popup.getField('distribChannel').setValue(Ext.DomQuery.selectValue('distribChannel', xml));
					popup.getField('aggFundGroup').setValue(Ext.DomQuery.selectValue('aggFundGroup', xml));	
					popup.getField('model').setValue(Ext.DomQuery.selectValue('//FeeParmsDetail/ModelID', xml));	
		
					if(Ext.DomQuery.selectValue('action', xml) =='add') 
					{
						popup.getField('model').setValue(Ext.DomQuery.selectValue('model', xml));							
					}
					_controller.setCurrentModel(popup.getField('model').getValue());
					_controller.onChangeModel(popup.getField('model').getValue());
					_controller.loadSelector(xml);
					
					if (!_controller.isAccountLevel())
					{										
						popup.getField('maxFee').setValue(Ext.DomQuery.selectValue('maxFee', xml));				
						popup.getField('OverAllowed').setValue(Ext.DomQuery.selectValue('OverAllowed', xml));
					}
				}
			}
		)
		
		,feeParmDetails:  new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,baseTitle: 'Trailer Fee'			
				,width: 565
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border: false}					
				,items: [											
					{			
						layout: 'form'																																		
						,style: 'padding:4px'
						,defaults: {border: false}						
						,items: [
							{
								layout: 'column'																
								,defaults: {border: false}
								,items: [
									{
										width:320										
										,layout: 'form'										
										,labelWidth: 110
										,items: [											
											new DesktopWeb.Controls.TextField(
												{
													itemId: 'GrandFthrEnd'
													,width:100
													,fieldLabel: _translationMap['GrandFatherEnd']									
												}
											)																					
										]
									}									
								] 									
							}
							,{
								layout: 'column'																
								,defaults: {border:false}
								,items: [
									{
										width:330
										,layout: 'form'										
										,labelWidth: 110
										,defaults:{width:200}
										,items: [																								
											new DesktopWeb.Controls.TextField(
												{
													itemId: 'BalType'
													,fieldLabel: _translationMap['EligBalanceType']							
												}
											)
											,new DesktopWeb.Controls.TextField(
												{
													itemId: 'BalAsOf'
													,fieldLabel: _translationMap['BalanceAsOf']
												}
											)
											,new DesktopWeb.Controls.TextField(
												{
													itemId: 'AvgType'
													,fieldLabel: _translationMap['AverageType']	
												}
											)										
										]
									}
									,{
										width:210
										,defaults: {width:100}
										,layout: 'form'
										,labelWidth: 80									
										,items: [									
											new DesktopWeb.Controls.SMVComboBox(
												{
													itemId: 'SplitBy'														
													,fieldLabel: _translationMap['SplitBy']
													,allowBlank: false
													,listeners: {
														beforeselect: function(fld, record, index)
														{															
															var SplitByFld = _popups['feeParmDetails'].getField('SplitBy');	
															if (record.data.code != 'DSC')
															{															
																_popups['feeParmDetails'].getField('AssetType').disable();
																_popups['feeParmDetails'].getField('AssetType').setValue('All');
															}
															else
															{
																_popups['feeParmDetails'].getField('AssetType').enable();
																_popups['feeParmDetails'].getField('AssetType').setValue('REM');
															}
															
														}
													}
												}
											)
											,new DesktopWeb.Controls.SMVComboBox(
												{
													itemId: 'AssetType'														
													,fieldLabel: _translationMap['AssetType']
													,allowBlank: false							
												}
											)
											,new DesktopWeb.Controls.SMVComboBox(
												{
													itemId: 'FeeType'
													,fieldLabel: _translationMap['FeeType']
													,allowBlank: false
													,listeners: {
														beforeselect: function(fld, record, index)
														{															
															var feeRateFld = _popups['feeParmDetails'].getField('FeeRate');	
															if (record.data.code == '2')
															{															
																feeRateFld.setValue('0');
																feeRateFld.disable();																
															}
															else
															{
																feeRateFld.setValue();
																feeRateFld.enable();
															}	
														}
													}							
												}
											)
											,new DesktopWeb.Controls.NumberField(
												{
													itemId: 'FeeRate'
													,fieldLabel: _translationMap['FeeRate']						
													,width: 80
													,allowDecimal: true
													,decimalPrecision: 4
													,allowNegative: false
													,maxValue: 100
																				
												
												}
											)											
										]
									}
								]								
							}				
												
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if(_popups['feeParmDetails'].isValid()){
									_controller.validateFeeParmDetailUpdate(_popups['feeParmDetails'].action);
								}																
							}								
						}
					), 
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'cancelBtn'
							,text: _translationMap['Cancel']
							,handler:function(){_popups['feeParmDetails'].hide()}
						}
					)
				]
				,init: function(action)
				{					
					var popup = _popups['feeParmDetails'];	
					popup.action = action;
					popup.clearAllFields();																								
					
					
					if(action == _controller.MOD)
					{
						popup.setTitle("Trailer Fee Details - Modify");
					}
					else if (action == _controller.ADD)
					{
						popup.setTitle("Trailer Fee Details - Add");
					}
					popup.getField('GrandFthrEnd').disable();
					popup.getField('BalAsOf').disable();
					popup.getField('AvgType').disable();
					popup.getField('BalType').disable();					
					
					popup.populate();
					
					popup.enableAllFields();
					
					if (popup.getField('FeeType').getValue() == '2')
					{
						popup.getField('FeeRate').disable();
					}
					else
					{
						popup.getField('FeeRate').enable();
					}
					
					if (popup.getField('SplitBy').getValue() == 'DSC')
					{
						popup.getField('AssetType').enable();
					}
					else 
					{
						popup.getField('AssetType').disable();
					}
					
					
				}
				,populate: function()
				{
					var popup = _popups['feeParmDetails'];
					var xml = _controller.getSelectedFeeParmDetail();
					popup.getField('GrandFthrEnd').setValue(Ext.DomQuery.selectValue('GrandFthrEnd', xml));
					popup.getField('AvgType').setValue(Ext.DomQuery.selectValue('AvgTypeDesc', xml));
					popup.getField('SplitBy').setValue(Ext.DomQuery.selectValue('SplitBy', xml));
					popup.getField('AssetType').setValue(Ext.DomQuery.selectValue('AssetType', xml));
					popup.getField('BalType').setValue(Ext.DomQuery.selectValue('BalTypeDesc', xml));
					popup.getField('FeeType').setValue(Ext.DomQuery.selectValue('FeeType', xml));
					popup.getField('FeeRate').setValue(Ext.DomQuery.selectValue('FeeRate', xml));
					popup.getField('BalAsOf').setValue(Ext.DomQuery.selectValue('BalAsOfDesc', xml));		
				}				
			}
		)
				
		,scaleDetails: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 500
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						html: "Are you sure you want to delete this record?"							
						,style: 'text-align:center'														
					}						
					,{						
						layout: 'column'																		
						,style: 'padding:4px'
						,defaults: {border: false}						
						,items: [
							{
								columnWidth: .5
								,layout: 'form'								
								,labelWidth: 80
								,items: [
									new DesktopWeb.Controls.TextField(
										{
											itemId: 'lowBand'
											,fieldLabel: _translationMap['LowerBound']							
										}
									)											
									,new DesktopWeb.Controls.TextField(
										{
											itemId: 'rate'
											,fieldLabel: _translationMap['Rate']						
										}
									)
								]
							}							
							,{
								columnWidth: .5
								,layout: 'form'							
								,labelWidth: 80
								,items: [									
									new DesktopWeb.Controls.TextField(
										{
											itemId: 'uprBand'
											,fieldLabel: _translationMap['UpperBound']							
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
							,handler: function(){_controller.validateScaleDetailUpdate(_popups['scaleDetails'].action);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['Cancel']
							,handler: function(){_popups['scaleDetails'].hide();}
						}
					)
				]
				,init: function(action)
				{
					// initialize popup based on action
					var popup = _popups['scaleDetails'];
					popup.action = action
					popup.clearAllFields();
					switch(action)
					{
						case _controller.ADD:
						{
							popup.setTitle('Scale Detail - Add');
							popup.enableAllFields();
							popup.get(0).hide();
							break;
						}
						case _controller.MOD:
						{
							popup.setTitle('Scale Detail - Modify');
							popup.enableAllFields();							
							popup.get(0).hide();
							popup.populate();
							break;
						}
						case _controller.DEL:
						{
							popup.setTitle('Scale Detail - Delete');
							popup.disableAllFields();
							popup.get(0).show();
							popup.populate();
							break;
						}
					}						
				}
				,populate: function()
				{
					var popup = _popups['scaleDetails'];
					var xml = _controller.getSelectedScaleDetail();
					popup.getField('lowBand').setValue(Ext.DomQuery.selectValue('lowBand', xml));
					popup.getField('uprBand').setValue(Ext.DomQuery.selectValue('uprBand', xml));
					popup.getField('rate').setValue(Ext.DomQuery.selectValue('rate', xml));
				}				
			}
		)
		
		,history: new DesktopWeb.AdvancedControls.PopupWindow(
			{				
				width: 580
				,nextStartRecNum: null
				,name: null
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border:false}
				,items: [
					_grids['history']
				]
				,buttons:[
					new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['More']
							,itemId: 'moreBtn'							
							,handler: function()
							{
								_controller.doHistoryCall(_popups['history'].name, _popups['history'].nextStartRecNum, successHandler);
								function successHandler(xml)
								{								
									_popups['history'].populate(xml, true);
								}								
							}							
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['Close']
							,handler: function(){_popups['history'].hide();}
						}
					)					
				]
				,init: function(name)
				{
					//initialize popup based on record type
					_popups['history'].name = name
					switch(name)
					{
						case 'feeParms':
						{
							_popups['history'].setTitle('Trailer Fee Paramter - History');
							break;
						}
						case 'feeParmDetails':
						{
							_popups['history'].setTitle('Trailer Fee Details - History');
							break;
						}
						case 'scaleDetails':
						{
							_popups['history'].setTitle('Scale Details - History');
							break;
						}
					}
				}
				,populate: function(xml, append)
				{					
					_grids['history'].getStore().loadData(xml, append);
					var nextStartRecNum = DesktopWeb.Util.getSmartviewNextStartRecNum(xml);
					if (nextStartRecNum)
					{
						_popups['history'].nextStartRecNum = nextStartRecNum;
						_popups['history'].enableButton('moreBtn');
					}
					else
					{
						_popups['history'].disableButton('moreBtn');
					}
				}
			}
		)		
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,selectors: _selectors
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth																			
				,items: [
					{
						layout: 'column'									
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 80}														
						,items: [
							{
								width: 200						
								,layout: 'form'
								,labelWidth: 65								
								,items: [
									_fields['searchValue']																							
								]
							}
							,{
								width: 165
								,layout: 'form'								
								,items: [
									_fields['searchFundCode']
									,_fields['searchFundGroup']									
									,_fields['searchBrokerCode']
								]
							}
							,{
								width: 160
								,layout: 'form'								
								,items: [
									_fields['searchClassCode']									
									,_fields['searchBranchCode']
								]
							}
							,{
								width: 160
								,layout: 'form'								
								,items: [
									_fields['searchSlsRepCode']									
								]
							}
							,{
								width: 300
								,layout: 'form'		
								,labelWidth: 120										
								,items: [
									_fields['searchDistribChannel']									
								]
							}
							,new DesktopWeb.Controls.ActionButton(
								{
									style: 'position:absolute; top:0px; right:0px'
									,text: _translationMap['Search']	
									,handler: function(){_controller.doReload(false);}										 																			
								}
							)						
						]									
					}
					,_grids['feeParms']
					,{
						xtype: 'fieldset'
						,title: _translationMap['TrailerFeeDetails']
						,style: "margin-bottom:20px"
						,width: _layoutWidth
						,items: _grids['feeParmDetails']
					}							
					,{
						xtype: 'fieldset'						
						,title: _translationMap['ScaleDetails']					
						,width: _layoutWidth
						,items: _grids['scaleDetails']						
					}									
				]				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function()
					{
						//if(_controller.updatesFlag != DesktopWeb._FAIL)
						{
							_controller.doValidate();
						}	
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}