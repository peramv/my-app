/*********************************************************************************************
 * @file	ClassSetup_PerfFeeConfig.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources file for Performance Fee Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 15
	})
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({								
		height: 45									
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id)}
		}
	})	
	
	// **** fields ****
	var _fields = {		
		perfFeeFlag: new DesktopWeb.Controls.YesNoComboBox({
			     fieldLabel: _translationMap['applicable']
				 ,allowBlank: false
		 })   
		,feeMethod: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['feeMethod']				
			,width: 225
			,editable: false
			,allowBlank: false
			,autoSelect: true
			,showCode: true
		})
		,calcBasis: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['calcBasis']				
			,width: 140
			,editable: false
			,allowBlank: false
			,autoSelect: true
			,showCode: true
		})
		,lossCarryForward: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['lossCarryForward']				
			,width: 210
			,editable: false
			,allowBlank: false
			,autoSelect: true
			,showCode: true
		})
		,divAddBack: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['divAddBack']				
			,width: 140
			,editable: false
			,allowBlank: false
			,autoSelect: true
			,showCode: true
		})
		,lotRedMethod: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['lotRedMethod']				
			,width: 200
			,editable: false
			,allowBlank: false
			,autoSelect: true
		})
		,perfFeeCalcPrecision: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['perfFeeCalcPrecision']
			,width: 50
			,allowDecimals: false
			,allowNegative: false
			,allowBlank: false
			,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '1'}
			,validator: function(value){
				if(value == '')
				{
					return _translationMap['requiredFieldErrMsg'];
				}
				if(this.allowedDecrease != 'yes' && this.originalValue > value)
				{
					return _translationMap['precisionLessThanErrMsg'];
				}
			}
		})
		,perfFeePrecision: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['perfFeePrecision']
			,width: 50
			,allowDecimals: false
			,allowNegative: false
			,allowBlank: false
			,baseChars: '0123456'
			,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '1'}
			,validator: function(value){
				if(value == '')
				{
					return _translationMap['requiredFieldErrMsg'];
				}
				if(this.allowedDecrease != 'yes' && this.originalValue > value)
				{
					return _translationMap['precisionLessThanErrMsg'];
				}
			}
		})
		,gavRate: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['gavRate']
			,width: 125
			,allowBlank: false
			,allowNegative: false
			,allowDecimals: true
			,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '15'}
			,validator: function(value){
				if(value == '')
				{
					return _translationMap['requiredFieldErrMsg'];
				}
				if(value <= 0)
				{
					return _translationMap['requiredGreaterThanZero'];
				}
			}
		})
		,classHWMRate: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['classHWMRate']
			,width: 125
		})
		,classHWMResetDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['classHWMResetDate']
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,hurdleApply: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['hurdle']
			,width: 125
			,listeners: {
				check: function(cb, checked)
				{
					_controller.checkedHurdle(checked);
				}
			}
			
		})
	}
	
	// **** grids ****
	var _grids = {
		hurdleConfig: new DesktopWeb.AdvancedControls.GridPanel(
			{														
				autoScroll: true							
				,height: 150
				,hidden: true
				,autoExpandColumn: 'fixedRate'									
				,store: new Ext.data.XmlStore(
					{
						record: 'PerfFeeHurdleConfig'
						,fields: ['hurdleConfigUUID', 'benchmarkType', 'fixedRate', 'indexCode', 'adjRate', 'daysBasis', 'weighting', 'runMode', 'version']
						,listeners: {
							load: function(store, records)
							{															
								store.filterBy(function(record){return record.data.runMode != _controller.DEL});
							}
							,update: function(store)
							{								
								store.filterBy(function(record){return record.data.runMode != _controller.DEL});
							}																			
						}			
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.selectHurdle(record);
								}
							}
						}
				})				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns: [
						{header: _translationMap['benchmarkType'], dataIndex: 'benchmarkType', width: 100
							,renderer: function(val){
								return val + ' - ' + _controller.getValueDescFromList('benchmarkType', val);
							}
						}
						,{id: 'fixedRate', header: _translationMap['fixRate'], dataIndex: 'fixedRate'
							,renderer: function(val){
								return (val && val.length>0)?val + '%':val;
							}
						}
						,{header: _translationMap['benchmarkIndex'], dataIndex: 'indexCode', width: 125
							,renderer: function(val){
								return _controller.getMktIndexDescFromList(val);
							}
						}
						,{header: _translationMap['benchmarkAdjRate'], dataIndex: 'adjRate', width: 175
							,renderer: function(val){
								return (val && val.length>0)?val + '%':val;
							}
						}
						,{header: _translationMap['daysBasis'], dataIndex: 'daysBasis', width: 100
							,renderer: function(val){
								return val + ' - ' + _controller.getValueDescFromList('daysBasis', val);
							}
						}
						,{header: _translationMap['weighting'], dataIndex: 'weighting', width: 100
							,renderer: function(val){
								return (val && val.length>0)?val + '%':val;
							}
						}
					]		
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'								
						,text: _translationMap['Add']
						,handler: function(){
							_controller.openHurdlePopup(_controller.ADD)
						}														
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'								
						,text: _translationMap['Modify']
						,handler: function(){
							_controller.openHurdlePopup(_controller.MOD)
						}													
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'								
						,text: _translationMap['Delete']
						,handler: function(){
							_controller.openHurdlePopup(_controller.DEL)
						}													
					})
				]			
			}
		)
	}
	
	// **** popups ****
	var _popups = {					
		updHurdle: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 600
			,action: null
			,hurdleConfigUUID: null
			,modal: true
			,defaults: {border:false}
			,items: [
				{						
					layout: 'form'
					,style: 'padding:4px'
					,defaults: {border:false}
					,labelWidth: 65
					,items: [ 
						{
							layout: 'column'							
							,defaults: {															
								layout: 'form'
								,border: false
							}
							,items: [
								{
									labelWidth: 105
									,columnWidth: 0.44
									,items: [
										new DesktopWeb.Controls.SMVComboBox({
											itemId: 'benchmarkType'	
											,fieldLabel: _translationMap['benchmarkType']
											,autoSelect: true
											,allowBlank: false
											,editable: false
											,width: 100
											,listeners:{
												select: function(combo, record, index){
													_controller.selectBenchmarkType(combo.getValue());
													
												}
											}
											,showCode: true
										})
										,new DesktopWeb.Controls.ComboBox({
											itemId: 'benchmarkIndex'									
											,fieldLabel: _translationMap['benchmarkIndex']
											,editable: false
											,width: 100
											,store: new Ext.data.XmlStore(
												{
													record: 'MktIndex'
													,fields: ['indexCode', 'indexName', 'daysBasis']			
												}
											)    
											,valueField: 'indexCode'
											,displayField: 'indexName'
											,listeners:{
												select: function(combo, record, index){
													_controller.selectBenchmarkIndex(record);
													
												}
											}
										})
										,new DesktopWeb.Controls.SMVComboBox({
											itemId: 'daysBasis'									
											,fieldLabel: _translationMap['daysBasis']
											,editable: false
											,width: 110
											,showCode: true
										})								
									]
								}
								,{
									labelWidth: 170
									,columnWidth: 0.56
									,items: [
										new DesktopWeb.Controls.NumberField({
											itemId: 'fixRate'									
											,fieldLabel: _translationMap['fixRate']
											,allowDecimals: true
											,decimalPrecision: 9
											,width: 100
											,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '13'}
											,listeners:{
												afterrender: function(p) {
													p.getEl().insertHtml(
														'afterEnd'
														,'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%'
														,true
													);
												}
												,single: true
											}
										})
										,new DesktopWeb.Controls.NumberField({
											itemId: 'benchmarkAdjRate'									
											,fieldLabel: _translationMap['benchmarkAdjRate']
											,allowNegative: true
											,allowDecimals: true
											,decimalPrecision: 9
											,width: 100
											,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '15'}
											,listeners:{
												afterrender: function(p) {
													p.getEl().insertHtml(
														'afterEnd'
														,'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%'
														,true
													);
												}
												,single: true
											}
										})
										,new DesktopWeb.Controls.NumberField({
											itemId: 'weighting'									
											,fieldLabel: _translationMap['weighting']
											,width: 50
											,allowDecimals: false
											,listeners:{
												afterrender: function(p) {
													p.getEl().insertHtml(
														'afterEnd'
														,'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%'
														,true
													);
												}
												,single: true
											}
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
					,handler: function(){
						if (_popups['updHurdle'].isValid())
						{
							_controller.saveHurdle(_popups['updHurdle'].action, _popups['updHurdle']);
						}
					}							
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_controller.closeHurdlePopup(_popups['updHurdle'].action)}
				})
			]
			,init: function(action)
			{										
				this.action = action
				if (this.rendered)
				{
					this.clearAllFields();
				}
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['hurdle']+ ' - ' +_translationMap['Add']);
						this.enableAllFields();
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['hurdle']+ ' - ' +_translationMap['Modify']);
						this.enableAllFields();
						break;
					}
				}	
				this.populate(action);													
			}
			,populate: function(action)
			{
				switch(action)
				{
					case _controller.ADD:
					{
						// load default value
						this.hurdleConfigUUID = '';
						this.getField('benchmarkType').setValue('01');
						_controller.selectBenchmarkType('01');
						this.getField('fixRate').setValue('0');
						this.getField('daysBasis').setValue('01');
						this.getField('weighting').setValue('0');
						this.getField('benchmarkIndex').setValue('');
						this.getField('benchmarkAdjRate').setValue('');
						break;
					}
					case _controller.MOD:
					{
						// populate value from a selected record
						var rec = _grids['hurdleConfig'].getSelectedRecord();
						this.hurdleConfigUUID = rec.get('hurdleConfigUUID');
						var benchmarkType = rec.get('benchmarkType');
						_controller.selectBenchmarkType(benchmarkType);
						
						this.getField('benchmarkType').setValue(benchmarkType);
						if (benchmarkType == '01') { // Fixed
							this.getField('fixRate').setValue(rec.get('fixedRate'));
							this.getField('daysBasis').setValue(rec.get('daysBasis'));
							this.getField('benchmarkIndex').setValue('');
							this.getField('benchmarkAdjRate').setValue('');

						}else{ // Floating
							this.getField('benchmarkIndex').setValue(rec.get('indexCode'));
							this.getField('benchmarkAdjRate').setValue(rec.get('adjRate'));
							this.getField('fixRate').setValue('');
							this.getField('daysBasis').setValue(rec.get('daysBasis'));
						}
						this.getField('weighting').setValue(rec.get('weighting'));
						break;
					}
				}
			}
		})								
		,delHurdle: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 350
			,action: null
			,hurdleConfigUUID: null
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
					,defaults: {border:false, width: 150}
					,labelWidth: 170
					,items: [
						new DesktopWeb.Controls.TextField({
							itemId: 'delBenchmarkType'									
							,fieldLabel: _translationMap['benchmarkType']
							,disable: true
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'delFixRate'									
							,fieldLabel: _translationMap['fixRate']
							,disable: true
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'delDaysBasis'									
							,fieldLabel: _translationMap['daysBasis']
							,disable: true
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'delBenchmarkIndex'									
							,fieldLabel: _translationMap['benchmarkIndex']
							,disable: true
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'delBenchmarkAdjRate'									
							,fieldLabel: _translationMap['benchmarkAdjRate']
							,disable: true
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'delWeighting'									
							,fieldLabel: _translationMap['weighting']
							,disable: true
						})
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['delHurdle'].isValid())
						{
							_controller.saveHurdle(_popups['delHurdle'].action, _popups['delHurdle']);
						}
					}							
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_controller.closeHurdlePopup(_popups['delHurdle'].action);}
				})
			]
			,init: function(action)
			{
				this.action = action;
				if (this.rendered)
				{					
					this.clearAllFields();
					this.disableAllFields();
				}
				this.disableAllFields();
				this.setTitle(_translationMap['hurdle']+ ' - ' +_translationMap['Delete']);
				this.populate();
			}
			,populate: function()
			{
				var rec = _grids['hurdleConfig'].getSelectedRecord();
				this.getField('delBenchmarkType').setValue(_controller.getValueDescFromList('benchmarkType', rec.get('benchmarkType')));
				this.getField('delFixRate').setValue((rec.get('fixedRate')=='')?'':rec.get('fixedRate') + '%');
				this.getField('delDaysBasis').setValue(_controller.getValueDescFromList('daysBasis', rec.get('daysBasis')));
				this.getField('delBenchmarkIndex').setValue(_controller.getValueDescFromList('benchmarkIndex', rec.get('indexCode')));
				this.getField('delBenchmarkAdjRate').setValue((rec.get('adjRate')=='')?'':rec.get('adjRate') + '%');
				this.getField('delWeighting').setValue(rec.get('weighting') + '%');
			}
			,getData: function()
			{
				var data = {};					
				data['runMode'] = this.action;
				data['hurdleConfigUUID'] = this.hurdleConfigUUID;
				data['benchmarkType'] = this.getField('delBenchmarkType').getValue();
				data['fixRate'] = this.getField('delFixRate').getValue();
				data['benchmarkIndex'] = this.getField('delBenchmarkIndex').getValue();
				data['benchmarkAdjRate'] = this.getField('delBenchmarkAdjRate').getValue();
				data['daysBasis'] = this.getField('delDaysBasis').getValue();
				data['weighting'] = this.getField('delWeighting').getValue();					
				return data;
			}
		})								
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					_header
					,_breadCrumbList
					,new Ext.Container({
						style: 'padding-left:12px; padding-right:10px; padding-bottom:50px;'
						,items: [
							{
								xtype: 'fieldset'
								,title: _translationMap['performanceFee']
								,style: 'padding-bottom: 0px'
								,hidden: true
								,items: [
									{
										layout: 'form'
										,labelWidth: 175
										,items: [_fields['perfFeeFlag']]
									}
								]
							}
							,{
								layout: 'column'																
								,items: [
									{
										layout: 'form'
										,columnWidth: 0.61
										,labelWidth: 175
										,items: [
											_fields['feeMethod']
											,_fields['lossCarryForward']
											,_fields['lotRedMethod']
											,_fields['perfFeePrecision']
										]
									}
									,{
										layout: 'form'
										,columnWidth: 0.39
										,labelWidth: 115
										,items: [
											_fields['calcBasis']
											,_fields['divAddBack']
											,_fields['perfFeeCalcPrecision']
										]
									}
								]
							}
							,{
								xtype: 'fieldset'
								,title: _translationMap['initValues']
								,style: 'padding-bottom: 0px'																	
								,items: [
									{
										layout: 'column'
										,style: 'padding-left: 10px'
										,defaults: {
											columnWidth: 0.5
										}
										,items: [
											{
												layout: 'form'
												,labelWidth: 150
												,items: [
													_fields['gavRate']												
												]												
											}
											,{
												layout: 'form'
												,labelWidth: 150
												,items: [
													_fields['classHWMRate']
													,_fields['classHWMResetDate']
												]
											}										
										]
										
									}
								]
							}
							,_fields['hurdleApply']
							,_grids['hurdleConfig']
						]	
					})
				]
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Previous']
				,hidden: true
				,disabled: true				
				,id: 'prevBtn'
				,handler: function(){
					_controller.previous();
				}				
			})				
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Save']
				,id: 'saveBtn'
				,disabled: true
				,handler: function(){

					var divValue = _fields['divAddBack'].getValue();
					var hurdleValue = _fields['hurdleApply'].getValue();

					if (divValue == "03" && hurdleValue == false)
					{
						DesktopWeb.Util.displayError(_translationMap['hurldeRequired']);
					}
					else 
					{
					  _controller.save();	
					}
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Reset']
				,id: 'resetBtn'
				,disabled: true
				,handler: function(){
					_controller.reset();	
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,hidden: true				
				,id: 'cancelBtn'
				,handler: function(){
					_controller.cancel();
				}				
			})								
			,new DesktopWeb.Controls.ScreenButton({
				text: ''
				,hidden: true				
				,id: 'nextBtn'
				,handler: function(){
					_controller.next();
				}				
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['ReturntoSummary']
				,hidden: true				
				,id: 'summaryBtn'
				,handler: function(){
					_controller.changeScreen('Summary');
				}				
			})
		]			
	}
}