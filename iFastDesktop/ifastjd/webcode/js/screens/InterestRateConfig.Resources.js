/*********************************************************************************************
 * @file	InterestRateConfig.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Interest Rate Configuration screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  17 Aug 2017 N. Hatthaseriphong P0263240 CHG0048754 T86111 DFT0076495
 *					- Fix display default effective date and default stop date
 *
 *  22Aug 2017 Gomoot T. P0263240 CHG0048754 T86111 DFT0076496 
 *					- To protect display description as blank on grid ,
 *             the table will get desc from Inquiry service instead.
 *
 *  18 Oct 2017 Matira T. P0263240-59 DFT0078086
 *          - Expand size of interest segment (base rate) popup.
 *
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 515;
	var _layoutWidth = 575;
	
	// **** fields ****
	var _fields = {
	}
	
	// **** grids ****
	var _grids = {
		intRateCfgGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth
				,title: ''
				,autoScroll: true
				,height: 200
				,store: new Ext.data.XmlStore(
					{
						record: 'IntRateCfg'
						,fields: ['intRateCfgUUID', 'intRateCfgCode', 'fundCategory', 'fundCategoryDesc', 
						'intCalcMthd','intCalcMthdDesc', 'deff', 'stopDate', 'version', 'errMsg', 'inUsed', 'updMode']
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
									record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);									
								});

								store.fireEvent('datachanged', store); //to set data in grid again
							}
						}

					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.setSelectedIntRate(record, index);
								}
							}
							,rowdeselect: function(){
								_controller.setDeselectedIntRate();
							}
						}						
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
							,width: 75
						}
						,columns: [
							{dataIndex: 'errMsg'
								,renderer: function(val){
									return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
								}
								, width: 25
							}
							,{header: _translationMap['Code'], dataIndex: 'intRateCfgCode', width: 75}
							,{header: _translationMap['InvestmentCategory'], dataIndex: 'fundCategoryDesc', width: 150}
							,{header: _translationMap['InterestCalcType'], dataIndex: 'intCalcMthdDesc', width: 150}
							,{header: _translationMap['EffectiveDate'], dataIndex: 'deff'}
							,{header: _translationMap['StopDate'], dataIndex: 'stopDate'}
						]							
					}
				)
				,buttons: [					
					new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'addBtn'								
							,text: _translationMap['Add']							
							,handler: function(){_controller.openActionPopup("intRateCfgUpdate", _controller.ADD);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'modBtn'
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup("intRateCfgUpdate", _controller.MOD);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'delBtn'
							,text: _translationMap['Delete']
							,handler: function(){_controller.openActionPopup("intRateCfgUpdate", _controller.DEL);}							
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
							itemId: 'adminBtn'
							,text: _translationMap['Admin']
							,handler: function(){_controller.openAdminPopup('IntRateCfg');}
						}
					)									
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'historyBtn'
							,text: _translationMap['Historical']
							,handler: function(){_controller.openHistoryPopup('IntRateCfg');}					
						}
					)									
				]
			}
		)
	}
	
	// **** ItemSelector ****
	var _selectors = {
		intSegSelector: new DesktopWeb.AdvancedControls.ItemSelector(
			{
				height: 300
				,width: _layoutWidth
				,allowReordering: true
				,availableGridProperties: {
					title: ''
					,width: 150
					,store: new Ext.data.XmlStore(
						{
							record: 'Element'
							,fields: ['detlUUID', 'code', 'value', 'valueType', 'configValue', 'configValueDisplay', 'seq', 'version', 'updMode', 'errMsg']
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{id: 'intRateCfgCode', header: 'Interest Segments', dataIndex: 'value', width: 125}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true
						}
					)
					
				}
				,selectedGridProperties: {
					width: 280
					,autoExpandColumn: 'intRateCfgValue'
					,store: new Ext.data.XmlStore(
						{
							record: 'Element'
							,fields: ['detlUUID', 'code', 'value', 'valueType', 'configValue', 'configValueDisplay', 'seq', 'version', 'updMode', 'errMsg']	
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{dataIndex: 'errMsg'
									, renderer: function(val){
											return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
										}
									, width: 25
								}
								,{id: 'intRateCfgDesc', header: _translationMap['InterestSegments'], dataIndex: 'value', width: 125}
								,{id: 'intRateCfgValue', header: _translationMap['Value'], dataIndex: 'configValueDisplay', width: 150}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true
							,listeners: {
								rowselect: function(selModel, index, record){
									if(selModel){
										_controller.setSelectedSegment(record, index);
									}
								}
								,rowdeselect: function(){
									_controller.setDeselectedSegment();
								}
							}						
						}
					)

					,buttons: [					
						new DesktopWeb.Controls.ActionButton(		
							{
								itemId: 'edtBtn'								
								,text: _translationMap['Edit']							
								,handler: function(){_controller.openSegmentEditPopup();}
							}
						)
					]
				}
			}
		)

		,BRSegSelector: new DesktopWeb.AdvancedControls.ItemSelector(
			{
				height: 150
				,width: 480
				,allowReordering: false
				,availableGridProperties: {
					title: ''
					,width: 195
					,store: new Ext.data.XmlStore(
						{
							record: 'Element'
							,fields: ['code', 'value']
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{id: 'segment', dataIndex: 'value', width: 190}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true
						}
					)
					
				}
				,selectedGridProperties: {
					width: 195
					,store: new Ext.data.XmlStore(
						{
							record: 'Element'
							,fields: ['code', 'value']
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{id: 'segment', dataIndex: 'value', width: 190}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true
						}
					)
				}
			}
		)
	}

	// **** popups ****
	var _popups = {					
		intRateCfgUpdate: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 350
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						html: _translationMap['DeleteConfirmMsg']
						,style: 'text-align:center;font-weight:bold;'
					}
					,{						
						layout: 'form'																		
						,style: 'padding:4px'
						,defaults: {border: true}
						,labelWidth: 135
						,items: [
							new DesktopWeb.Controls.TextField(
								{
									itemId: 'intRateCfgCodeFld'
									,fieldLabel: _translationMap['Code']
									,allowBlank: false
									,width: 160
								}
							)
							,new DesktopWeb.Controls.SMVComboBox(
								{
									itemId: 'fundCategoryFld'
									,fieldLabel: _translationMap['InvestmentCategory']
									,editable: false
									,allowBlank: false
									,width: 160
									,listeners: {
										select: function(combo, record, index){
											_controller.loadIntCalcMthdList(record.get('code'));
										}
									}
								}
							)
							,new DesktopWeb.Controls.SMVComboBox(
								{
									itemId: 'intCalcTypeFld'
									,fieldLabel: _translationMap['InterestCalcType']
									,editable: false
									,allowBlank: false
									,width: 160
								}
							)
							,new DesktopWeb.Controls.DateField(
								{
									itemId: 'effDateFld'
									,fieldLabel: _translationMap['EffectiveDate']
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								}
							)
							,new DesktopWeb.Controls.DateField(
								{
									itemId: 'stopDateFld'
									,fieldLabel: _translationMap['StopDate']
									,allowBlank: false
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								}
							)
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if (_popups['intRateCfgUpdate'].isValid()){
									_controller.intRateCfgUpdate(_popups['intRateCfgUpdate'].action, _popups['intRateCfgUpdate']);
								}
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: _translationMap['Cancel']
							,handler: function(){_popups['intRateCfgUpdate'].hide();}
						}
					)
				]
				,init: function(action)
				{
					// initialize popup based on action
					var popup = _popups['intRateCfgUpdate'];
					popup.action = action
					popup.clearAllFields();
					
					switch(action)
					{
						case _controller.ADD:
						{
							// Deselect what selected
							var grid = _grids['intRateCfgGrid'];
							
							popup.setTitle(_translationMap['InterestRateConfig']+ ' - ' +_translationMap['Add']);
							popup.defaultPopup();
							popup.enableAllFields();
							popup.get(0).hide();
							break;
						}
						case _controller.MOD:
						{
							popup.setTitle(_translationMap['InterestRateConfig']+ ' - ' +_translationMap['Modify']);
							popup.enableAllFields();
							popup.populate(action);
							popup.get(0).hide();
							break;
						}
						case _controller.DEL:
						{
							popup.setTitle(_translationMap['InterestRateConfig']+ ' - ' +_translationMap['Delete']);
							popup.populate(action);
							popup.disableAllFields();
							popup.get(0).show();
							break;
						}
					}
				}
				,defaultPopup: function()
				{
					var popup = _popups['intRateCfgUpdate'];
					popup.getField('effDateFld').setValue(DesktopWeb.Util.getDateDisplayValue(_controller.getDefault('deff')));
					popup.getField('stopDateFld').setValue(DesktopWeb.Util.getDateDisplayValue(_controller.getDefault('stopDate')));
				}	
				,populate: function(action)
				{
					var popup = _popups['intRateCfgUpdate'];
					var selectedIntRate = _controller.getSelectedIntRate();
					
					_controller.loadIntCalcMthdList(selectedIntRate.get('fundCategory'));
					
					popup.getField('intRateCfgCodeFld').setValue(selectedIntRate.get('intRateCfgCode'));
					popup.getField('fundCategoryFld').setValue(selectedIntRate.get('fundCategory'));
					popup.getField('intCalcTypeFld').setValue(selectedIntRate.get('intCalcMthd'));
					popup.getField('effDateFld').setValue(selectedIntRate.get('deff'));
					popup.getField('stopDateFld').setValue(selectedIntRate.get('stopDate'));

					if(action == _controller.MOD && selectedIntRate.get('inUsed')=='yes')
					{
						popup.getField('intRateCfgCodeFld').disableField();
						popup.getField('fundCategoryFld').disableField();
						popup.getField('intCalcTypeFld').disableField();
						popup.getField('effDateFld').disableField();
					}
				}				
			}
		)
		
		,intSegBRUpdate: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,title: _translationMap['BaseRate']+ ' - ' +_translationMap['Modify']
				,width: 500
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{						
						layout: 'form'											
						,style: 'padding:4px'
						,defaults: {border: true}
						,labelWidth: 60
						,items: [
							new DesktopWeb.Controls.TextField(
								{
									itemId: 'intSegBRFld'
									,fieldLabel: _translationMap['Interest']
									,width: 150
									,allowBlank: false
									,readOnly: true
								}
							)
							,_selectors['BRSegSelector']
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if(_selectors['BRSegSelector'].getSelectedRecords().length>0){
									_controller.intRateCfgDetlUpdate(_popups['intSegBRUpdate'])
								}else{
									DesktopWeb.Util.displayError("Please select at least one item.");
								}
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: _translationMap['Cancel']
							,handler: function(){_popups['intSegBRUpdate'].hide();}
						}
					)
				]
				,init: function(segment)
				{
					// initialize popup based on action
					var popup = _popups['intSegBRUpdate'];
					popup.clearAllFields();
					popup.populate(segment);
				}
				,populate: function(segment)
				{
					var popup = _popups['intSegBRUpdate'];
					popup.getField('intSegBRFld').setValue(segment.get('value'));
					popup.getField('intSegBRFld').disableField();
					_controller.loadBRDetail();
				}
			}
		)
				
		,intSegCodeUpdate: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 270
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{						
						layout: 'form'											
						,style: 'padding:4px'
						,defaults: {border: true}
						,labelWidth: 60
						,items: [
							new DesktopWeb.Controls.TextField(
								{
									itemId: 'intSegCodeFld'
									,fieldLabel: _translationMap['Interest']
									,allowBlank: false
									,width: 150
									,readOnly: true
								}
							)
							,new DesktopWeb.Controls.SMVComboBox(
								{
									itemId: 'segCodeFld'
									,fieldLabel: _translationMap['Value']
									,editable: false
									,allowBlank: false
									,width: 150
								}
							)
						]						
					}												
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if (_popups['intSegCodeUpdate'].isValid()){
									_controller.intRateCfgDetlUpdate(_popups['intSegCodeUpdate'])
								}
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: _translationMap['Cancel']
							,handler: function(){_popups['intSegCodeUpdate'].hide();}
						}
					)
				]
				,init: function(segment)
				{
					// initialize popup based on action
					var popup = _popups['intSegCodeUpdate'];
					popup.clearAllFields();
					popup.populate(segment);
				}
				,populate: function(segment)
				{
					var popup = _popups['intSegCodeUpdate'];
					popup.setTitle(segment.get('value') + ' - ' +_translationMap['Modify']);
					popup.getField('intSegCodeFld').setValue(segment.get('value'));
					popup.getField('intSegCodeFld').disableField();
					_controller.loadConfigValueList(popup.getField('segCodeFld'), _controller.getSelectedIntRate().get('fundCategory'), segment.get('code'));
					popup.getField('segCodeFld').setValue(_controller.getCodeMapping(segment.get('configValue')));
					popup.getField('segCodeFld').clearInvalid();
				}
			}
		)
		
		,intSegDecUpdate: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 270
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{						
						layout: 'form'												
						,style: 'padding:4px'
						,defaults: {border: true}
						,labelWidth: 60
						,items: [
							new DesktopWeb.Controls.TextField(
								{
									itemId: 'intSegDecFld'
									,fieldLabel: _translationMap['Interest']
									,allowBlank: false
									,width: 150
									,readOnly: true
								}
							)
							,new DesktopWeb.Controls.NumberField(
								{
									itemId: 'segDecFld'
									,fieldLabel: _translationMap['Value']
									,allowDecimals: true
									,allowNegative: true
									,allowBlank: false
									,decimalPrecision: 4
									,maxLength: 15
									,width:150
								}
							)
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if (_popups['intSegDecUpdate'].isValid()){
									_controller.intRateCfgDetlUpdate(_popups['intSegDecUpdate']);
								}
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: _translationMap['Cancel']
							,handler: function(){_popups['intSegDecUpdate'].hide();}
						}
					)
				]
				,init: function(segment)
				{
					// initialize popup based on action
					var popup = _popups['intSegDecUpdate'];
					popup.clearAllFields();
					popup.populate(segment);
					
				}
				,populate: function(segment)
				{
					var popup = _popups['intSegDecUpdate'];
					popup.setTitle(segment.get('value') + ' - ' +_translationMap['Modify']);
					popup.getField('intSegDecFld').setValue(segment.get('value'));
					popup.getField('intSegDecFld').disableField();
					popup.getField('segDecFld').setValue(segment.get('configValue'));
					popup.getField('segDecFld').clearInvalid();
				}
			}
		)
		
		,intSegPerUpdate: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 270
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{						
						layout: 'form'												
						,style: 'padding:4px'
						,defaults: {border: true}
						,labelWidth: 60
						,items: [
							new DesktopWeb.Controls.TextField(
								{
									itemId: 'intSegPerFld'
									,fieldLabel: _translationMap['Interest']
									,allowBlank: false
									,width: 150
									,readOnly: true
								}
							)
							,new DesktopWeb.Controls.NumberField(
								{
									itemId: 'segPerFld'
									,fieldLabel: _translationMap['Value']
									,allowDecimals: true
									,allowNegative: false
									,allowBlank: false
									,decimalPrecision: 4
									,minValue: 0.0000
									,maxValue: 100.0000
									,minText: _translationMap['PercentRequired']
									,maxText: _translationMap['PercentRequired']
									,width:150
								}
							)
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if (_popups['intSegPerUpdate'].isValid()){
									_controller.intRateCfgDetlUpdate(_popups['intSegPerUpdate']);
								}
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: _translationMap['Cancel']
							,handler: function(){_popups['intSegPerUpdate'].hide();}
						}
					)
				]
				,init: function(segment)
				{
					// initialize popup based on action
					var popup = _popups['intSegPerUpdate'];
					popup.clearAllFields();
					popup.populate(segment);
					
				}
				,populate: function(segment)
				{
					var popup = _popups['intSegPerUpdate'];
					popup.setTitle(segment.get('value') + ' - ' +_translationMap['Modify']);
					popup.getField('intSegPerFld').setValue(segment.get('value'));
					popup.getField('intSegPerFld').disableField();
					popup.getField('segPerFld').setValue(segment.get('configValue'));
					popup.getField('segPerFld').clearInvalid();
				}
			}
		)
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
		
		,selectors: _selectors
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					_grids['intRateCfgGrid']
					,_selectors['intSegSelector']
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function(){DesktopWeb.Util.commitScreen();}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){
						if(_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg);
							function handlePromptMsg(btn){
								if(btn){
									DesktopWeb.Util.cancelScreen();
								}
							}
						}else{
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
		]			
	}
}
