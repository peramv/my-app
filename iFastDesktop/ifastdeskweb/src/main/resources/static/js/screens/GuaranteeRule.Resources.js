/*********************************************************************************************
 * @file	GuaranteeRule.Resources.js
 * @author	Danny Xu
 * @desc	Controller JS file for SEG - Guarantee Rules screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *        - Fix display date format follows dateFormatDisplay parameter
 *
 * 	02 Sep 2014 P. Wongpakdee P0232147 DFT0038249 T55659
 *		  - Enable a scroll bar for Contact Type grid box to allow more
 *			than maximum 5 records can be shown up
 *
 *	25 Sep 2014 P. Wongpakdee P0233151 INA Cayenne Day 2 T55815
 *		  - display field description in grid guaranteeInfo
 *		  - call function defaultGuarantee for Add/Mod modes
 *		  - set value of guarCalcRule as description in populateWithSelectedRecord
 *		  - call function findGuarCalcRuleCode to assign correct value
 *			for GuaCalcRule and description
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 440;
	var _layoutWidth = 750;
	
	// **** buttons ****
	var _buttons = {		
		searchButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Search']
			,disabled: true
			,handler: function(){
				_controller.doLookup();
				_controller.setFlag();
			}
		})
	}
	
	// **** fields ****
	var _fields = {
		contractType: new DesktopWeb.Controls.SMVComboBox({
			width: 175
			,fieldLabel: _translationMap['ContractType']
			,allowBlank: false
			,listeners: {
				select : function(fld, rec, index) {
					_controller.clearVersionNumber('top');
					var searchFlag = _controller.populateSearchVersionNumber(rec.data.value);
					 _buttons['searchButton'].setDisabled(!searchFlag);
				}
			}
		})
		
		,versionNumber: new DesktopWeb.Controls.SMVComboBox({
			width: 175
			,fieldLabel: _translationMap['VersionNumber']
			,allowBlank: false
			,disabled: true
			,listeners: {
				select : function(fld, rec, index) {_buttons['searchButton'].setDisabled(false);}
				,invalid : function(a, msg) {_buttons['searchButton'].setDisabled(true);}
			}
		})		
	}
	
	// **** grids ****
	var _grids = {
		codeTypeInfo: new DesktopWeb.AdvancedControls.GridPanel({				
			style: "margin-bottom:15px"
			,width: _layoutWidth			
			,autoScroll: true							
			,height: 175
			,autoExpandColumn: 'codeType'
			,store: new Ext.data.XmlStore({
				record: 'Mstr'
				,fields: ['runMode', 
						  'segGuarCalcUUID',
						  'guarCalcID',
						  'contractType',
						  'contrVersioned',
						  'acctContrExists',
						  'contractVer',
						  'transType', 
						  'codeType', 
						  'transCode', 
						  'transId',
						  'deff',
						  'num',
						  'transContractType',
						  'transContractVer',
						  {name: 'recordSource', mapping: '@recordSource'}]
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['deff'] = DesktopWeb.Util.getDateDisplayValue(record.data['deff']);
						});
								
						store.filterBy(function(record){							
							return record.data.runMode != _controller.DEL});																								
					}
					,update: function(store)
					{
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL});
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						_controller.updateMstrActionButtons('codeTypeInfo');
						_grids['guaranteeInfo'].getStore().filterBy(function(rec){return rec.data.runMode != _controller.DEL && 
																						 rec.data.recordSource.split(":", 1) == record.data.recordSource});
						_controller.updateDetlActionButtons('guaranteeInfo');
						_grids['guaranteeInfo'].selectFirstRecord();
						_controller.disableButtons (record.data.acctContrExists, 'codeTypeInfo');
					}
					,rowdeselect: function(){
						_controller.updateMstrActionButtons('codeTypeInfo');}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [	
					{header: _translationMap['ContractType'], id:'contractType', dataIndex: 'contractType', width:90}
					,{header: _translationMap['VersionNumber'], id:'contractVer', dataIndex: 'contractVer', width:90}												
					,{header: _translationMap['TransactionType'], id:'transType', dataIndex: 'transType', width:125, renderer: function(value){ return (_controller.getListValueDesc('TransTypeList', value))}}
					,{header: _translationMap['CodeType'], id:'codeType',  dataIndex: 'codeType', renderer: function(value){ return (_controller.getListValueDesc('CodeTypeList', value))}}
					,{header: _translationMap['Code'], id:'transCode', dataIndex: 'transCode', width:70}
					,{header: _translationMap['EffDate'], id:'deff', dataIndex: 'deff', width:90}
					,{header: _translationMap['TransContractType'], id:'transContractType', dataIndex: 'transContractType', width:115}
					,{header: _translationMap['TransContractVer'], id:'transContractVer', dataIndex: 'transContractVer', width:125}
				]							
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']							
					,handler: function(){_controller.openActionPopup(_controller.ADD, 'codeTypeInfo', 'codeTypePopup');}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD, 'codeTypeInfo', 'codeTypePopup');}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup(_controller.DEL, 'codeTypeInfo', 'codeTypePopup');}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup('mstrs');}						
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'historyBtn'
					,text: _translationMap['History']
					,handler: function(){_controller.openHistoricalPopup('mstrs');}
				})
			]			
		})		
		,guaranteeInfo: new DesktopWeb.AdvancedControls.GridPanel({							
			style: "margin-bottom:15px"
			,autoScroll: true							
			,height: 200
			,autoExpandColumn: 'guarCalcSeq'											
			,store: new Ext.data.XmlStore({
				record: 'Detl'					
				,fields: ['runMode',
						  'segGuarCalcDetlUUID',
						  'guarCalcID',
						  'guarType', 
						  'guarCalcRule',
						  'guarCalcSeq', 
						  'overrideRate',
						  'guarCalcRule',
						  'overrideRateType',
						  'num',
						  'description',
						  {name: 'recordSource', mapping: '@recordSource'}]
				,listeners: {
					load: function(store, records)
					{
						store.filterBy(function(record){return record.data.runMode != _controller.DEL && record.data.num == _grids['codeTypeInfo'].getSelectedRecord().data['recordSource']});																																		
					}
					,update: function(store)
					{								
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
					}																			
				}						
			})
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						_controller.updateDetlActionButtons('guaranteeInfo');
						_controller.disableButtons (_grids['codeTypeInfo'].getSelectedRecord().data.acctContrExists, 'guaranteeInfo');}
					,rowdeselect: function(){_controller.updateDetlActionButtons('guaranteeInfo');}
				}						
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['Guarantee'], dataIndex: 'guarType', width: 150, renderer: function(value){ return (_controller.getListValueDesc('GuaranteeList', value))}}
					,{header: _translationMap['CalculationSequence'], id:'guarCalcSeq', dataIndex: 'guarCalcSeq'}
					,{header: _translationMap['RuleDescription'], dataIndex: 'description', width: 250}
					,{header: _translationMap['OverrideValue'], dataIndex: 'overrideRate', width: 200}
				]
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']							
					,handler: function(){_controller.openActionPopup(_controller.ADD, 'guaranteeInfo', 'guaranteePopup');}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD, 'guaranteeInfo', 'guaranteePopup');}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup(_controller.DEL, 'guaranteeInfo', 'guaranteePopup');}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup('detls');}	
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'historyBtn'
					,text: _translationMap['History']
					,handler: function(){_controller.openHistoricalPopup('detls');}
				})
			]			
		})
	}
	
	// **** popups ****
	var _popups = {			
		codeTypePopup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 620
			,action: null						
			,modal: true
			,listeners: {
				hide: function(a) {
					if (_grids['codeTypeInfo'].getSelectedRecord() == null)
						_grids['codeTypeInfo'].selectLastRecord();
					}
				}
			
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']								
					,style: 'text-align:center'														
				}						
				,{
					layout: 'column'																		
					,style: 'padding:4px'
					,items: [
						{
							layout: 'form'
							,columnWidth: 0.62
							,labelWidth: 125
							,border: false
							,items: [
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'contractType'
									,width: 150
									,fieldLabel: _translationMap['ContractType']
									,allowBlank: false
									,listeners: {
										select : function(fld, rec, index){
											_controller.clearVersionNumber('popup');
											var searchFlag = _controller.populatePopupVersionNumber(rec.data.value);
										}
									}
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'transType'
									,width: 150
									,fieldLabel: _translationMap['TransactionType']
									,allowBlank: false														
								})									
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'codeType'
									,width: 150
									,fieldLabel: _translationMap['CodeType']
									,listeners: {
										select : function(fld, rec, index){
											_popups['codeTypePopup'].getField('transCode').setDisabled(false);
											_controller.populateTransCode(rec.data.code);
										}
									}
									,validator: function(value)
									{
										var flag = (value == "") == (_popups['codeTypePopup'].getField('transCode').getValue() == "");
										if (flag)
											_popups['codeTypePopup'].getField('transCode').clearInvalid();
										return flag;
									}
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'transCode'									
									,width: 200
									,fieldLabel: _translationMap['Code']
									,validator: function(value)
									{
										var flag = (value == "") == (_popups['codeTypePopup'].getField('codeType').getValue() == "");
										if (flag)
											_popups['codeTypePopup'].getField('codeType').clearInvalid();
										return flag;
									}
								})
							]
						}
						,{
							layout: 'form'
							,columnWidth: 0.38
							,labelWidth: 100
							,border: false
							,items: [
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'contractVer'									
									,width: 100
									,fieldLabel: _translationMap['VersionNumber']
									,validator: function(value){return value != ""}														
								})								
								,new DesktopWeb.Controls.DateField({
									itemId: 'deff'
									,width: 100
									,fieldLabel: _translationMap['EffDate']
									,allowBlank: false														
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
							]
						}
						
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['codeTypePopup'].isValid())
						{
							if (_controller.saveMstrPopup(_popups['codeTypePopup'].action, _popups['codeTypePopup'].getData()))
							{
								_controller.closeActionPopup('codeTypePopup');
							}
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['codeTypePopup'].hide();
					}
				})
			]
			,init: function(action)
			{
				this.action = action;
				this.clearAllFields();
				this.get(0).hide(); //hide delete message
					
				if (_controller.getFlag())
				{
					this.getField('contractType').setValue(_controller.getContractType());
					this.getField('contractVer').setValue(_controller.getContractVer());
					this.getField('contractType').setDisabled(true);
					this.getField('contractVer').setDisabled(true);
				}
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap["CodeType"] + " - " + _translationMap["Add"]);
						this.enableAllFields();
						this.getField('deff').setValue(_controller.getDefaultDate());
						this.getField('transCode').setDisabled(true);
						this.getField('codeType').focus();
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap["CodeType"] + " - " + _translationMap["Modify"]);
						this.enableAllFields();
						this.populateWithSelectedRecord();
						this.getField('codeType').focus();
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap["CodeType"] + " - " + _translationMap["Delete"]);
						this.get(0).show();
						this.disableAllFields();
						this.populateWithSelectedRecord();
						break;
					}
				}				
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['codeTypeInfo'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];
				this.getField('transType').setValue(rec.data['transType']);
				
				this.getField('codeType').setValue(rec.data['codeType']);
				
				var codeTypeValue = this.getField('codeType').getValue();
				this.getField('transCode').setDisabled(codeTypeValue == '');
				if (codeTypeValue != '')
					_controller.populateTransCode(codeTypeValue); //transCode needs to populate before setValue.
					
				this.getField('transCode').setValue(rec.data['transCode']);
				this.getField('deff').setValue(rec.data['deff']);
				this.getField('contractType').setValue(rec.data['contractType']);
				this.getField('contractVer').setValue(rec.data['contractVer']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				if (_grids['codeTypeInfo'].getSelectedRecord() == null || _grids['codeTypeInfo'].getSelectedRecord().data['recordSource'] == null)
				{
					data['recordSource'] =_controller.keepCountMstr();
				}
				else
				{
					data['recordSource'] = _grids['codeTypeInfo'].getSelectedRecord().data['recordSource'];
				}
				
				if (data['runMode'] == _controller.ADD)
				{
					data['guarCalcID'] = 0;
				}
					
				if (_grids['codeTypeInfo'].getSelectedRecord() != null)
				{
					data['segGuarCalcUUID'] = _grids['codeTypeInfo'].getSelectedRecord().data['segGuarCalcUUID'];
				}
				
				data['transType'] = this.getField('transType').getValue();
				data['codeType'] = this.getField('codeType').getValue();
				data['transCode'] = this.getField('transCode').getValue();
				if (_grids['codeTypeInfo'].getSelectedRecord() == null)
				{
					data['num'] = 0;
				}
				else
				{
					data['num'] = _grids['codeTypeInfo'].getSelectedRecord().data['num'];
				}
				data['deff'] = this.getField('deff').getDisplayDateString();
				data['contractType'] = this.getField('contractType').getValue();
				data['contractVer'] = this.getField('contractVer').getValue();
				return data;
			}														
		})
		,guaranteePopup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 465
			,action: null						
			,modal: true
			,listeners: {
				hide: function(a) {
					if (_grids['guaranteeInfo'].getSelectedRecord() == null)
						_grids['guaranteeInfo'].selectLastRecord();
					}
				}
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap["DeleteConfirmMsg"]							
					,style: 'text-align:center'
				}
				,{
					layout: 'form'
					,style: 'padding-left:4px; padding-top:4px;'
					,labelWidth: 105
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'guarType'
							,width: 75
							,fieldLabel: _translationMap['Guarantee']
							,allowBlank: false
							,listeners: {
								select : function(fld, rec, index){
									_popups['guaranteePopup'].getField('guarCalcRule').setDisabled(false);
									_controller.populateRuleDesc(rec.data.code);
								}
							}														
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'guarCalcRule'
							,width: 310
							,fieldLabel: _translationMap['RuleDescription']
							,allowBlank: false
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'overrideRate'
							,width: 125
							,fieldLabel: _translationMap['OverrideValue']
						})
					]
				}
			]			
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['guaranteePopup'].isValid())
						{
							if (_controller.saveDetlPopup(_popups['guaranteePopup'].action, _popups['guaranteePopup'].getData()))
							{
								_controller.closeActionPopup('guaranteePopup');
							}
						}						
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['guaranteePopup'].hide();}					
				})
			]
			,init: function(action)
			{										
				this.action = action;
				this.clearAllFields();
				this.get(0).hide(); //hide delete message				
				
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap["GuaranteeInfo"] + " - " + _translationMap["Add"]);
						this.enableAllFields();
						_controller.defaultGuarantee(action, 'guaranteePopup');						
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap["GuaranteeInfo"] + " - " + _translationMap["Modify"]);
						this.enableAllFields();
						this.populateWithSelectedRecord();
						_controller.defaultGuarantee(action, 'guaranteePopup');						
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap["GuaranteeInfo"] + " - " + _translationMap["Delete"]);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();																							
						break;
					}
				}														
			}			
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['guaranteeInfo'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];
				this.getField('guarType').setValue(rec.data['guarType']);
				this.getField('guarCalcRule').setValue(rec.data['description']);
				this.getField('overrideRate').setValue(rec.data['overrideRate']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['guarCalcID'] = _grids['codeTypeInfo'].getSelectedRecord().data['guarCalcID'];
				
				data['guarType'] = this.getField('guarType').getValue();
				if (this.action == _controller.ADD)
				{
					data['guarCalcSeq'] = _grids['guaranteeInfo'].getStore().getCount()+1;
				}
				else
				{
					data['guarCalcSeq'] = _grids['guaranteeInfo'].getSelectedRecord().data['guarCalcSeq'];
				}
				data['recordSource'] = _grids['codeTypeInfo'].getSelectedRecord().data['recordSource'] + ":" + data['guarCalcSeq'];
				data['num'] = data['recordSource'].split(":", 1);
				
				/* Ensure GuarClacRule is assigned as code; not description */
				var CurrGuarCalcRule = this.getField('guarCalcRule').getValue();
				data['description'] = _controller.findGuarCalcRuleCode(CurrGuarCalcRule);
				data['guarCalcRule'] = this.getField('guarCalcRule').getValue();
				
				data['overrideRate'] = this.getField('overrideRate').getValue();
				if (_grids['guaranteeInfo'].getSelectedRecord() != null)
				{
					data['segGuarCalcDetlUUID'] = _grids['guaranteeInfo'].getSelectedRecord().data['segGuarCalcDetlUUID'];
				}
				data['overrideRateType'] = _controller.findOverrideRateType(data['guarCalcRule'], data['guarType']);
				return data;
			}														
		})
		,admin: new DesktopWeb.AdvancedControls.PopupWindow({
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
								new DesktopWeb.Controls.Label({
									itemId: 'userName'
									,fieldLabel: _translationMap['Username']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'modUser'
									,fieldLabel: _translationMap['ModUser']
								})
							]
						}
						,{
							width: 185
							,layout: 'form'
							,defaults: {width: 80}
							,items: [
								new DesktopWeb.Controls.Label({
									itemId: 'procDate'
									,fieldLabel: _translationMap['ProcessDate']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'modDate'
									,fieldLabel: _translationMap['ModDate']										
								})
							]
						}
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){_popups['admin'].hide();}
				})
			]
			,init: function(title, data)
			{
				this.setTitle(title);
				this.getField('procDate').setValue(data['procDate']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['userName']);
				this.getField('modUser').setValue(data['modUser']);	
			}
		})
		,history: new DesktopWeb.AdvancedControls.HistoryPopup()
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [											
					{	
						layout: 'column'
						,style: 'padding-left: 5 px'
						,defaults: {layout: 'form'}
						,items: [
							{
								columnWidth: 0.44
								,items: [
									_fields['contractType']
								]												
							}
							,{
								columnWidth: 0.44
								,items: [
									_fields['versionNumber']
								]
							}
							,{
								columnWidth: 0.12
								,items: [
									_buttons['searchButton']
								]
							}							
						]
					}					
					,_grids['codeTypeInfo']
					,_grids['guaranteeInfo']					
				]				
			}
		)		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){						
					DesktopWeb.Util.commitScreen()}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){DesktopWeb.Util.cancelScreen()}
			})
		]			
	}
}