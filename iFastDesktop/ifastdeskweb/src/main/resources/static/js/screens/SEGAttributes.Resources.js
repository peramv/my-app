/*********************************************************************************************
 * @file	SEGAttributes.Resources.js
 * @author	Danny Xu
 * @desc	Resources JS file for SEG Attributes screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 * 	03 Sep 2014 P. Wongpakdee P0232147 DFT0038250 T55659
 *		  - Correct typo of moneyEsgEWI description (having a space)
 *
 * 	25 Sep 2014 P. Wongpakdee P0233151 INA Cayenne Day 2 T55815
 *		  - call function validateSearchCriteria while searching
 *		  - call function callupdatesFlagStatus to update a flag
 *			for taxType and jurisdiction
 *		  - correct behavior of OK/Cancel screen button
 *
 *	09 Apr 2015 A. Mongkonrat P0232343 T80576 Fox Project B Payout Contract Type
 *              - Add Allow Negative LWA check box.
 *
 *	07 May 2015 A. Mongkonrat P0232343 T80678 Fox Project B Payout Contract Type
 *       - Extend space between admin and history button.
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 650;
	var _layoutWidth = 750;
	
	// **** buttons ****
	var _buttons = {
		
		searchButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Search']
			,handler: function(){
				if (_controller.validateSearchCriteria())
				{
					_controller.doLookup();
				}
			}
		})
		,dbgAdminButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Admin']
			,handler: function(){
				_controller.openAdminPopup('DBG');
			}
		})
		,dmgAdminButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Admin']
			,handler: function(){
				_controller.openAdminPopup('DMG');
			}
		})
		,cmdAdminButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Admin']
			,handler: function(){
				_controller.openAdminPopup('CMD');
			}
		})
		,gwbAdminButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Admin']
			,handler: function(){
				_controller.openAdminPopup('GWB');
			}
		})
		,generalAdminButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Admin']
			,handler: function(){
				_controller.openAdminPopup('GEN');
			}
		})
		,dbgHistoryButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['History']
			,handler: function(){
				_controller.openHistoricalPopup('DBG');
			}
		})
		,dmgHistoryButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['History']
			,handler: function(){
				_controller.openHistoricalPopup('DMG');
			}
		})
		,cmdHistoryButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['History']
			,handler: function(){
				_controller.openHistoricalPopup('CMD');
			}
		})
		,gwbHistoryButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['History']
			,handler: function(){
				_controller.openHistoricalPopup('GWB');
			}
		})
		,generalHistoryButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['History']
			,handler: function(){
				_controller.openHistoricalPopup('GEN');
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
					//_controller.populateVersionNumber(rec.data.value);
					//_controller.clearVersionNumber();}
					var searchFlag = _controller.populateSearchVersionNumber(rec.data.value);
					 _buttons['searchButton'].setDisabled(!searchFlag);
					_controller.clearVersionNumber();
				}
			}									
		})
		
		,versionNumber: new DesktopWeb.Controls.SMVComboBox({
			width: 175
			,fieldLabel: _translationMap['VersionNumber']
			,allowBlank: false
			,listeners: {
				select : function(fld, rec, index) {_buttons['searchButton'].setDisabled(false);}
				,invalid : function(a, msg) {_buttons['searchButton'].setDisabled(true);}
			}
		})
		
		////////////////////////////////// DBG //////////////////////////////////
		
		,dbgRate: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['DBGRate']
			,allowBlank: false
			,listeners: {
				change: function(){						
					_controller.appendToXml('dbgRate');
				}
			}												
		})
		,dbgRateAfterClosing: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['RateAfterClosingPeriod']				
			,listeners: {
				change: function(){						
					_controller.appendToXml('dbgRateAfterClosing');
				}
			}													
		})
		
		////////////////////////////////// DMG //////////////////////////////////
		
		,dmgRate: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['DMGRate']
			,allowBlank: false	
			,listeners: {
				change: function(){						
					_controller.appendToXml('dmgRate');
				}
			}														
		})
		
		,dmgRateBeforeCDDate: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['RateBeforeCDDate']															
			,disabled: true
			,listeners: {
				change: function(){					
					_controller.appendToXml('dmgRateBeforeCDDate');
				}
			}	
		})
		
		,dmgRateAfterCDDate: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['RateAfterCDDate']																
			,disabled: true
			,listeners: {
				change: function(){					
					_controller.appendToXml('dmgRateAfterCDDate');
				}
			}	
		})
		
		,dmgRateAfterClosing: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['RateAfterClosingPeriod']		
			,listeners: {
				change: function(){					
					_controller.appendToXml('dmgRateAfterClosing');
				}
			}															
		})
		
		////////////////////////////////// CMD //////////////////////////////////
		
		,maxMDAge: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['MaxMDAge']
			,decimalPrecision: 0
			,listeners: {
				change: function(){					
					_controller.appendToXml('maxMDAge');
				}
			}															
		})
		
		,minMDAge: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['MinMDAge']		
			,decimalPrecision: 0
			,listeners: {
				change: function(){					
					_controller.appendToXml('minMDAge');
				}
			}															
		})
		
		,minTerm: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['MinTerm']		
			,decimalPrecision: 0
			,listeners: {
				change: function(){					
					_controller.appendToXml('minTerm');
				}
			}															
		})
		
		,cmdBasedOn: new DesktopWeb.Controls.SMVComboBox({
			width: 215
			,fieldLabel: _translationMap['CMDBasedOn']
			,allowBlank: false
			,msgTarget: 'title'			
			,listeners: {
				change: function(){										
					_controller.appendToXml('cmdBasedOn');
				}
			}															
		})
		
		,dmdBasedOn: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['DMDBasedOn']		
			,disabled: true
			,listeners: {
				change: function(){					
					_controller.appendToXml('dmdBasedOn');
				}
			}															
		})
		
		,defaultCMDBasedOn: new DesktopWeb.Controls.SMVComboBox({
			width: 215
			,fieldLabel: _translationMap['DefaultCMDBasedOn']
			,allowBlank: false
			,msgTarget: 'title'			
			,listeners: {
				change: function(){		
					_controller.appendToXml('defaultCMDBasedOn');
				}
			}															
		})
		
		////////////////////////////////// GWB //////////////////////////////////
		
		,gwaRate: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['GWARate']		
			,listeners: {
				change: function(){					
					_controller.appendToXml('gwaRate');
				}
			}															
		})
		,bonusRate: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['BonusRate']		
			,listeners: {
				change: function(){					
					_controller.appendToXml('bonusRate');
				}
			}															
		})
		,bonusBasePercent: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['BonusBasePercent']		
			,listeners: {
				change: function(){					
					_controller.appendToXml('bonusBasePercent');
				}
			}															
		})
		,lwaAvailability: new DesktopWeb.Controls.SMVComboBox({
			width: 220
			,fieldLabel: _translationMap['LWAAvailability']	
			,allowBlank: false
			,msgTarget: 'title'			
			,listeners: {
				change: function(){					
					_controller.appendToXml('lwaAvailability');
				}
			}	
		})
		,lwaGprMeth: new DesktopWeb.Controls.SMVComboBox({
			width: 220
			,fieldLabel: _translationMap['LWAGPRMeth']	
			,allowBlank: false
			,msgTarget: 'title'
			,listeners: {
				change: function(){					
					_controller.appendToXml('lwaGprMeth');
				}
			}	
		})
		,immBenefElig: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['ImmBenefElig']	
			,listeners: {
				change: function(){					
					_controller.appendToXml('immBenefElig');
				}
			}
		})
		,allowNegativeLWA: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['AllowNegativeLWA']	
			,listeners: {
				check: function(ctl, val){
					_controller.appendToXml('allowNegativeLWA');
				}
			}
		})
		
		////////////////////////////////// General //////////////////////////////////
		
		,clsPrdTerm: new DesktopWeb.Controls.TextField({
			width: 100
			,fieldLabel: _translationMap['ClsPrdTerm']				
			,disabled: true
		})
		,taxType: new DesktopWeb.AdvancedControls.ItemSelector({
			height: 125
			,width: 330
			,style: 'margin-left:20px; margin-bottom: 10px'
			,allowBlank: false
			,allowReordering: false		
			,listeners: {
				change: function(){
					_controller.callupdatesFlagStatus(true);
				}
			}			
			,availableGridProperties: {
				width: 120				
				,autoExpandColumn: 'term'
				,forceLayout: true
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value']														
				})						
				,columns: [
					{id: 'term', header: _translationMap['TaxType'], dataIndex: 'value'}
				]	
			}
			,selectedGridProperties: {
				width: 120
				,autoExpandColumn: 'term'
				,forceLayout: true						
				,store: new Ext.data.XmlStore(
					{
						record: 'Element'					
						,fields: ['code', 'value']														
					}
				)
				,columns: [
					{id: 'term', header: _translationMap['TaxType'], dataIndex: 'value'}
				]
			}
		})
		,jurisdiction: new DesktopWeb.AdvancedControls.ItemSelector({
			height: 125
			,width: 330
			,style: 'margin-left:20px; margin-bottom: 10px'
			,allowBlank: false		
			,allowReordering: false						
			,listeners: {
				change: function(){
					_controller.callupdatesFlagStatus(true);		
				}
			}			
			,availableGridProperties: {
				width: 120				
				,autoExpandColumn: 'freq'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value']														
				})						
				,columns: [
					{id: 'freq', header: _translationMap['Jurisdiction'], dataIndex: 'value'}								
				]	
			}
			,selectedGridProperties: {
				width: 120
				,autoExpandColumn: 'freq'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value']														
				})
				,columns: [
					{id: 'freq', header: _translationMap['Jurisdiction'], dataIndex: 'value'}								
				]
			}						
		})
		,contractOnlineEWI: new DesktopWeb.Controls.SMVComboBox({
			width: 150
			,fieldLabel: _translationMap['OnlineEWI']		
			,listeners: {
				change: function(){
					_controller.appendEWIToXml('contractOnlineEWI', 'onLineEWI');
				}
			}
		})
		,contractEsgEWI: new DesktopWeb.Controls.SMVComboBox({
			width: 150
			,fieldLabel: _translationMap['ESGEWI']		
			,listeners: {
				change: function(){
					_controller.appendEWIToXml('contractEsgEWI', 'eSGEWI');
				}	
			}													
		})
		,moneyOnlineEWI: new DesktopWeb.Controls.SMVComboBox({
			width: 150
			,fieldLabel: _translationMap['OnlineEWI']			
			,listeners: {
				change: function(){
					_controller.appendEWIToXml('moneyOnlineEWI', 'onLineEWI');
				}
			}
																
		})
		,moneyEsgEWI: new DesktopWeb.Controls.SMVComboBox({
			width: 150
			,fieldLabel: _translationMap['ESGEWI']				
			,listeners: {
				change: function(){
						_controller.appendEWIToXml('moneyEsgEWI', 'eSGEWI');
					}	
			}													
		})
		,maturityInstruction: new DesktopWeb.Controls.SMVComboBox({
			width: 175
			,fieldLabel: _translationMap['DefaultMaturityInstruction']
			,allowBlank: false
			,listeners: {
				change: function(){
					_controller.appendToXml('maturityInstruction');
				}
			}
		})
		,revPerThd: new DesktopWeb.Controls.NumberField({
			width: 175
			,fieldLabel: _translationMap['RevPerThd']
			,allowBlank: false	
			,allowNegative: false			
			,listeners: {
				change: function(){						
					_controller.appendToXml('revPerThd');
				}
			}														
		})


	}
	
	// **** grids ****
	var _grids = {
		dbgGrid: new DesktopWeb.AdvancedControls.GridPanel({														
			autoScroll: true							
			,height: 150
			,autoExpandColumn: 'redAgeAttribValue'
			,store: new Ext.data.XmlStore({
				record: 'Reduction'
				,fields: ['runMode'
						  ,'num'
						  ,'cotAttribMstrID'
						  ,'redAgeAttribUUID'
						  ,'redAgeAttribCode'
						  ,'redAgeAttribValue'
						  ,'redAgeAttribDesc'
						  ,'rtAfAttribUUID'
						  ,'rtAfAttribCode' 
						  ,'rtAfAttribValue'
						  ,'rtAfAttribDesc']
				,listeners: {
					 load: function(store, records)
					 {
						store.filterBy(function(record){ return record.data.runMode != _controller.DEL});																																		
					 }
					 	,update: function(store)
					 {								
						store.filterBy(function(record){ return record.data.runMode != _controller.DEL});
					 }																		
				}		
			})
			,selModel: new Ext.grid.RowSelectionModel({					
					singleSelect: true
					,listeners: {
						 rowselect: function(selModel, index, record){_controller.updateActionButtons('dbgGrid');}
						 ,rowdeselect: function(){_controller.updateActionButtons('dbgGrid')}
					}
			})				
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['ReductionAge'], id: 'redAgeAttribValue', dataIndex: 'redAgeAttribValue'}
					,{header: _translationMap['RateAfterReductionAge'], id: 'rtAfAttribValue', dataIndex: 'rtAfAttribValue', width: 300}
				]		
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,handler: function(){
						_controller.openActionPopup(_controller.ADD, 'dbgGrid', 'dbgPopup')
					}														
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'								
					,text: _translationMap['Modify']
					,handler: function(){
						_controller.openActionPopup(_controller.MOD, 'dbgGrid', 'dbgPopup')
					}													
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'								
					,text: _translationMap['Delete']
					,handler: function(){
						_controller.openActionPopup(_controller.DEL, 'dbgGrid', 'dbgPopup')
					}													
				})
			]
		})
		,dmgGrid: new DesktopWeb.AdvancedControls.GridPanel({														
			autoScroll: true							
			,height: 150
			,autoExpandColumn: 'redAgeAttribValue'
			,store: new Ext.data.XmlStore(
				{
					record: 'Reduction'
					,fields: ['runMode'
							  ,'num'
							  ,'cotAttribMstrID'
							  ,'redAgeAttribUUID'
							  ,'redAgeAttribCode'
							  ,'redAgeAttribValue'
							  ,'redAgeAttribDesc'
							  ,'rtAfAttribUUID'
							  ,'rtAfAttribCode' 
							  ,'rtAfAttribValue'
							  ,'rtAfAttribDesc']
					,listeners: {
						 load: function(store, records)
						 {
							store.filterBy(function(record){ return record.data.runMode != _controller.DEL});																																		
						 }
						 	,update: function(store)
						 {								
							store.filterBy(function(record){ return record.data.runMode != _controller.DEL});
						 }																		
					}		
				}
			)
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true
				,listeners: {
					 rowselect: function(selModel, index, record){_controller.updateActionButtons('dmgGrid');}
					 ,rowdeselect: function(){_controller.updateActionButtons('dmgGrid')}
				}
			})				
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['ReductionAge'], id: 'redAgeAttribValue', dataIndex: 'redAgeAttribValue'}
					,{header: _translationMap['RateAfterReductionAge'], id: 'rtAfAttribValue', dataIndex: 'rtAfAttribValue', width: 300}
				]		
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,handler: function(){
						_controller.openActionPopup(_controller.ADD, 'dmgGrid', 'dmgPopup')
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'								
					,text: _translationMap['Modify']
					,handler: function(){
						_controller.openActionPopup(_controller.MOD, 'dmgGrid', 'dmgPopup')
					}													
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'								
					,text: _translationMap['Delete']
					,handler: function(){
						_controller.openActionPopup(_controller.DEL, 'dmgGrid', 'dmgPopup')
					}													
				})
			]
		})
	}
	
	// **** popups ****
	var _popups = {
		dbgPopup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 410
			,action: null						
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: "Are you sure you want to delete this record?"							
					,style: 'text-align:center'
				}
				,{
					layout: 'form'
					,style: 'padding:4px'
					,labelWidth: 160
					,items: [
						new DesktopWeb.Controls.NumberField({
							itemId: 'reductionAge'
							,width: 125
							,fieldLabel: _translationMap['ReductionAge']
							,allowBlank: false
							,decimalPrecision: 0
						})											
						,new DesktopWeb.Controls.NumberField({
							itemId: 'rateReductionAge'
							,width: 125
							,fieldLabel: _translationMap['RateAfterReductionAge']
							,allowBlank: false
						})		
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['dbgPopup'].isValid()
							&& _controller.savePopup(_popups['dbgPopup'].action, _popups['dbgPopup'].getData(), 'dbgGrid'))
						{
							_controller.closeActionPopup('dbgPopup');
							
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['dbgPopup'].hide();}
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
						this.setTitle(_translationMap["DBGReductions"] + " - " + _translationMap['Add']);
						this.enableAllFields();																
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap["DBGReductions"] + " - " + _translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();														
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap["DBGReductions"] + " - " + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['dbgGrid'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];
				this.getField('reductionAge').setValue(rec.data['redAgeAttribValue']);
				this.getField('rateReductionAge').setValue(rec.data['rtAfAttribValue']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['redAgeAttribValue'] = this.getField('reductionAge').getValue();
				data['rtAfAttribValue'] = this.getField('rateReductionAge').getValue();
				if (this.action == _controller.ADD)
					data['num'] = _controller.setNewReductValue();
				return data;
			}														
		})
		,dmgPopup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 410
			,action: null						
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: "Are you sure you want to delete this record?"							
					,style: 'text-align:center'														
				}						
				,{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 160
					,items: [
						new DesktopWeb.Controls.NumberField({
							itemId: 'reductionAge'
							,width: 125
							,fieldLabel: _translationMap['ReductionAge']
							,allowBlank: false
							,decimalPrecision: 0
						})											
						,new DesktopWeb.Controls.NumberField({
							itemId: 'rateReductionAge'
							,width: 125
							,fieldLabel: _translationMap['RateAfterReductionAge']
							,allowBlank: false
						})		
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['dmgPopup'].isValid()
							&& _controller.savePopup(_popups['dmgPopup'].action, _popups['dmgPopup'].getData(), 'dmgGrid'))
						{
							_controller.closeActionPopup('dmgPopup');			
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['dmgPopup'].hide();}
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
						this.setTitle(_translationMap["DMGReductions"] + " - " + _translationMap['Add']);						
						this.enableAllFields();																							
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap["DMGReductions"] + " - " + _translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();																	
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap["DMGReductions"] + " - " + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['dmgGrid'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];
				this.getField('reductionAge').setValue(rec.data['redAgeAttribValue']);
				this.getField('rateReductionAge').setValue(rec.data['rtAfAttribValue']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['redAgeAttribValue'] = this.getField('reductionAge').getValue();
				data['rtAfAttribValue'] = this.getField('rateReductionAge').getValue();
				if (this.action == _controller.ADD)
					data['num'] = _controller.setNewReductValue();
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
					new Ext.Container({
						items: [
							{	
								layout: 'column'
								,height: 40
								,style: 'padding-left: 5 px'
								,defaults: {
									layout: 'form'							
								}
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
						,{
							xtype: 'fieldset'
							,style: 'padding: 5px'
							,items: [ 
								new Ext.Panel({
									layout: 'accordion'
									,id: 'accordionLayout'							
									,items: [
										{
											layout: 'form'
											,title: _translationMap['General']
											,autoHeight: true
											,id: 'GEN'
											,items: [
												{
													style: 'padding-top: 10px; padding-left: 5px'
													,layout: 'form'
													,items: [
														_fields['clsPrdTerm']
													]
												}
												,{
													layout: 'column'
													,defaults: {
														layout: 'form'
														,columnWidth: 0.5
													}
													,items: [
														{
															items: [
																_fields['taxType']
															]
														}
														,{
															items: [
																_fields['jurisdiction']
															]
														}
													]
												}
												,{
													xtype: 'fieldset'
													,checkboxToggle: true
													,listeners: {
														beforecollapse: function(){return false}
														,render: function(){
															_fields['newContractAllowed'] = this.el.dom.firstChild.firstChild;																							
														}											
													}
													,title: _translationMap['NewContractAllowed']
													,autoHeight: true
													,layout: 'column'
													,defaults: {
														columnWidth: 0.5
														,layout: 'form'
														,labelWidth: 75
													}
													,items: [
														{
															items: [
																_fields['contractOnlineEWI']
															]
														}
														,{
															items: [
																_fields['contractEsgEWI']
															]
														}
													]
												}
												,{
													xtype: 'fieldset'
													,checkboxToggle: true
													,listeners: {
														beforecollapse: function(){return false}
														,render: function(){
															_fields['newMoneyAllowed'] = this.el.dom.firstChild.firstChild;																							
														}											
													}
													,title: _translationMap['NewMoneyAllowed']
													,autoHeight: true
													,layout: 'column'
													,defaults: {
														columnWidth: 0.5
														,layout: 'form'
														,labelWidth: 75
													}
													,items: [
														{
															items: [
																_fields['moneyOnlineEWI']
															]
														}
														,{
															items: [
																_fields['moneyEsgEWI']
															]
														}
													]
												}
												,{
													layout: 'form'
													,labelWidth: 200
													,items: [
														_fields['maturityInstruction']
													]
												}
												,{
													layout: 'form'
													,labelWidth: 200
													,items: [
														_fields['revPerThd']
													]
												}

												,{
												layout: 'column'
												,items: [
													{
														layout: 'form'
														,columnWidth: 0.8
														,labelWidth: 150
														,items: [
														]
													}
													,{
														layout: 'form'
														,columnWidth: 0.1
														,items: [
															_buttons['generalAdminButton']
															
														]
													}
													,{
														layout: 'form'
														,columnWidth: 0.1
														,items: [
															_buttons['generalHistoryButton']
															
														]
													}
												]
											}
											]
										}
										,{
											layout: 'form'
											,title: _translationMap['DMG']
											,autoHeight: true
											,id: 'DMG'
											,labelWidth: 125
											,items: [
												{
													layout: 'form'
													,style: 'padding: 10px'
													,items: [
														{
															layout: 'column'
															,items: [
																{
																	layout: 'form'
																	,columnWidth: 0.45
																	,labelWidth: 100
																	,items: [
																		_fields['dmgRate']
																	]
																}
																,{
																	layout: 'form'
																	,columnWidth: 0.55
																	,labelWidth: 150
																	,items: [
																		_fields['dmgRateAfterClosing']
																	]
																}
															]
														}
														,_grids['dmgGrid']
													]
												}											
												,{
													layout: 'column'
													,items: [
														{
															layout: 'form'
															,columnWidth: 0.8
															,labelWidth: 150
															,items: [
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.1
															,items: [
																_buttons['dmgAdminButton']															
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.1
															,items: [
																_buttons['dmgHistoryButton']																
															]
														}
													]
												}		
											]
										}
										,{
											layout: 'form'
											,title: _translationMap['CMD']
											,autoHeight: true
											,id: 'CMD'
											,items: [
												{
													layout: 'column'												//,height: 40
													,items: [
														{
															layout: 'form'
															,columnWidth: 0.45
															,style: 'padding: 10 px'
															,labelWidth: 100
															,items: [
																_fields['maxMDAge']	
																,_fields['minMDAge']
																,_fields['minTerm']
															]												
														}
														,{
															layout: 'form'
															,columnWidth: 0.55
															,style: 'padding: 10 px'
															,labelWidth: 150
															,items: [
																_fields['cmdBasedOn']
																,_fields['dmdBasedOn']
																,_fields['defaultCMDBasedOn']
															]
														}
													]
												}
												,{
													layout: 'column'
													,items: [
														{
															layout: 'form'
															,columnWidth: 0.8
															,labelWidth: 150
															,items: [
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.1
															,items: [
																_buttons['cmdAdminButton']
																
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.1
															,items: [
																_buttons['cmdHistoryButton']
																
															]
														}
													]
												}
											]
										}
										,{
											layout: 'form'
											,title: _translationMap['GWB']
											,autoHeight: true
											,id: 'GWB'
											,items: [
												{
													layout: 'column'
													,labelWidth: 120
													,items: [
														{
															layout: 'form'
															,columnWidth: 0.5
															,style: 'padding-left: 10px'
															,items: [
																_fields['gwaRate']	
																,_fields['bonusRate']
																,_fields['bonusBasePercent']
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.5
															,style: 'padding-left: 0px'
															,items: [
																_fields['lwaAvailability']
																,_fields['lwaGprMeth']
																,{
																	layout: 'column'
																	,labelWidth: 100
																	,items: [
																		{
																			layout: 'form'
																			,columnWidth: 0.5
																			,style: 'padding-left: 0px'
																			,items: [
																				_fields['immBenefElig']
																			]
																		}
																		,{
																			layout: 'form'
																			,columnWidth: 0.5
																			,style: 'padding-left: 0px'
																			,items: [
																				_fields['allowNegativeLWA']
																			]
																		}
																	]
																}														
															]
														}
													]
												}
												,{
													layout: 'column'
													,items: [
														{
															layout: 'form'
															,columnWidth: 0.76
															,labelWidth: 150
															,items: [
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.12
															,items: [
																_buttons['gwbAdminButton']
																
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.12
															,items: [
																_buttons['gwbHistoryButton']
																
															]
														}
													]
												}
											]
										}
										,{
											layout: 'form'
											,title: _translationMap['DBG']
											,autoHeight: true
											,id: 'DBG'
											,labelWidth: 125
											,items: [
												{
													layout: 'form'
													,style: 'padding: 10px'
													,items: [
														{
															layout: 'column'
															,items: [
																{
																	layout: 'form'
																	,columnWidth: 0.45
																	,labelWidth: 100
																	,items: [
																		_fields['dbgRate']
																	]
																}
																,{
																	layout: 'form'
																	,columnWidth: 0.55
																	,labelWidth: 150
																	,items: [
																		_fields['dbgRateAfterClosing']
																	]
																}
															]
														}
														,_grids['dbgGrid']
													]
												}
												,{
													layout: 'column'
													,items: [
														{
															layout: 'form'
															,columnWidth: 0.8
															,labelWidth: 150
															,items: [
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.1
															,items: [
																_buttons['dbgAdminButton']
																
															]
														}
														,{
															layout: 'form'
															,columnWidth: 0.1
															,items: [
																_buttons['dbgHistoryButton']
																
															]
														}
													]
												}			
											]
										}
									]
								})
							]
						}
					]
				})
			]}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					if (_controller.updatesFlag && _controller.searchState)
					{
						if (_controller.callUpdateValidate())
						{
							DesktopWeb.Util.commitScreen()
						}						
					}
					else
					{
						DesktopWeb.Util.cancelScreen();
					} 
				}
			})
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){
						if (_controller.updatesFlag && _controller.searchState)
						{
							DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
						}
						else
						{
							cancelScreen(true);
						}
						function cancelScreen(confirm)
						{
							if (confirm) DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
		]			
	}
}