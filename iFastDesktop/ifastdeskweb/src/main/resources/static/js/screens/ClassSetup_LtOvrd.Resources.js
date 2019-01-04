/*********************************************************************************************
 * @file	ClassSetup_LtOvrd.Resources.js
 * @author	Rod Walker
 * @desc	Resources file for LimitationOverride screen, part of Class Setup
 *********************************************************************************************/
/*
 * History : 
 *
 * 05-Mar-2014 Gomoot T. P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French
 *             
 * 11-Dec-2017 Sreejith A P0274726 P0266789-1870
 * 			   - Added Reason and remarks fields
 *             
 * 13-Feb-2018 Sreejith A P0274726 P0274726-83 
 * 			   - Removed Reason and remarks fields
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750;
	
	var _selectedFlag = null;
	var _selectedDropdown = null;
	var _selectedTaxJurisdiction = null;
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px; padding-bottom: 12px;'
		,height: 15
	})
	
	// **** buttons ****
	var _buttons = {	
		taxJurisDecl: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['Edit']
			,disabled: true
			,handler: function(){
				_controller.openDetailsPopup('taxJurisDecl', 'TaxJurisList');
			}								 																			
		})
		
		,provResDecl: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'	
			,text: _translationMap['Edit']
			,disabled: true						
			,handler: function(){
				_controller.openDetailsPopup('provResDecl', 'TaxJurisList');
			}								 																			
		})
		
		,accountTypeDecl: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'	
			,text: _translationMap['Edit']
			,disabled: true								
			,handler: function(){
				_controller.openDetailsPopup('accountTypeDecl', 'AcctTypeList');
			}								 																			
		})
		
		,taxTypeDecl: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'	
			,text: _translationMap['Edit']
			,disabled: true							
			,handler: function(){
				_controller.openDetailsPopup('taxTypeDecl', 'TaxTypeList');
			}								 																			
		})
		
		,acctDesigDecl: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'		
			,text: _translationMap['Edit']
			,disabled: true					
			,handler: function(){
				_controller.openDetailsPopup('acctDesigDecl', 'AcctDesignationList');
			}								 																			
		})
	}
	
	// **** fields ****
	var _fields = {
		taxJurisDecl: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TaxJurisdiction']
			,text: ''
			,style: 'font-size: 13px; margin-bottom: 3px'
		})
		
		,provResDecl: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ProvinceofResidence']
			,text: ''
			,style: 'font-size: 13px; margin-bottom: 3px'
		})		
		,accountTypeDecl: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['AccountType']
			,text: ''
			,style: 'font-size: 13px; margin-bottom: 3px'
		})		
		,taxTypeDecl: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TaxType']
			,text: ''
			,style: 'font-size: 13px; margin-bottom: 3px'
		})		
		,acctDesigDecl: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['AccountDesignation']
			,text: ''
			,style: 'font-size: 13px; margin-bottom: 3px'
		})
				
		,onlineEWI: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['OnlyEntry']				
			,width: 100			
			,listeners: {
				change: function(fld, newValue){
					_controller.updateEWIValue('onlineEWI', newValue);
				}
			}	
		})
		,cycleEWI: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['CycleProcessing']					
			,width: 100
			,listeners: {
				change: function(fld, newValue){
					_controller.updateEWIValue('cycleEWI', newValue);
				}
			}					
		})
		,esgEWI: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ESGNetwork']					
			,width: 100			
			,listeners: {
				change: function(fld, newValue){
					_controller.updateEWIValue('esgEWI', newValue);
				}
			}
		})
	}
	
	// **** grids ****
	var _grids = {
		fundLtOvrd: new DesktopWeb.AdvancedControls.GridPanel({														
			autoScroll: true							
			,height: 275
			,autoExpandColumn: 'ruleType'
			,store: new Ext.data.XmlStore({
				record: 'FundLtOvrd'					
				,fields: ['runMode', 'ruleTypeDesc', 'ruleType', 'overrideDec', 'overrideLog', 'taxJurisDecl', 'provResDecl', 'accountTypeDecl', 'taxTypeDecl', 'acctDesigDecl', 'onlineEWI', 'cycleEWI', 'esgEWI', 'fundLtOvrdRID', 'seqNo']
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
					rowselect: function(selModel, index, record){
					 	_controller.updateGridActionButtons();
					 	_controller.populateDetails(record.data);
					}
					,rowdeselect: function(){
						_controller.updateGridActionButtons();
						_controller.clearDetails();
					}
				}
			})				
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{
						header: _translationMap['RuleType']
						,id: 'ruleType'
						,dataIndex: 'ruleType'
						,renderer: function(value){
							return (value + ' ' + _controller.getListValueDesc('RuleTypeList', value))
						}
					}
					,{
						header: _translationMap['OverrideValue']
						,id: 'overrideDec'
						,dataIndex: 'overrideDec'
						,width: 300 
						,renderer: function(value, metadata, record){
							var ruleType = record.get('ruleType');
							if (ruleType == '49')
							{
								return (value + ' ' + _controller.getListValueDesc('RefundAmountList', value));
							}
							else if (ruleType == '55')
							{
								return (value + ' ' + _controller.getListValueDesc('DistTaxPayRuleList', value));
							}
							else if (ruleType == '56')
							{
								return (value + ' ' + _controller.getListValueDesc('DistTaxRuleList', value));
							}else{
								var overrideType = _controller.getRuleTypeOverrideType(ruleType);
								if (overrideType == 'overrideLog')
								{
									return _translationMap['Yes'].toUpperCase();
								}else{
									return value;
								}
							}
						}
					}
				]		
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,handler: function(){
						_controller.openRulePopup(_controller.ADD)
					}														
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'								
					,text: _translationMap['Delete']
					,disabled: true
					,handler: function(){
						_controller.openRulePopup(_controller.DEL)
					}													
				})
			]
		})
	}
	
	// **** popups ****
	var _popups = {
		fundLtOvrd: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 405
			,action: null						
			,modal: true
			,forceLayout: true
			,initHidden: true
			,defaults: {border:false}
			,listeners: {				
				beforeshow: function(){this.init()}
			}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']							
					,style: 'text-align:center'														
				}						
				,{
					layout: 'column'
					,labelWidth: 67
					,style: 'padding:4px'																						
					,items: [
						{
							layout: 'form'
							,border: false
							,items: [					
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'ruleType'
									,width: 255
									,fieldLabel: _translationMap['RuleType']
									,allowBlank: false
									,listeners: {
										select : function(fld, rec, index) {
											var ovrType = _controller.getRuleTypeOverrideType(_popups['fundLtOvrd'].getField('ruleType').getValue());
								
											if (_popups['fundLtOvrd'].getField('ruleType').getValue()=="49"){
												_popups['fundLtOvrd'].getField('overrideValues').reset();
												_popups['fundLtOvrd'].getField('overrideAllowed').reset();
												_popups['fundLtOvrd'].getField('overrideAllowed').setValue('no');
												_controller.loadOverrideValuesList('RefundAmountList');
												_popups['fundLtOvrd'].getField('overrideValues').showField();
												_popups['fundLtOvrd'].getField('overrideAllowed').showField();
												_popups['fundLtOvrd'].getField('overrideDec').hideField();
												_popups['fundLtOvrd'].getField('overrideLog').hideField();																						
											}
											else if (_popups['fundLtOvrd'].getField('ruleType').getValue()=="55") // Distribution Tax Payment Rule
											{
												_popups['fundLtOvrd'].getField('overrideValues').reset();
												_controller.loadOverrideValuesList('DistTaxPayRuleList');
												_popups['fundLtOvrd'].getField('overrideValues').setValue('2');
												_popups['fundLtOvrd'].getField('overrideValues').showField();
												_popups['fundLtOvrd'].getField('overrideAllowed').hideField();
												_popups['fundLtOvrd'].getField('overrideDec').hideField();
												_popups['fundLtOvrd'].getField('overrideLog').hideField();																						
											}
											else if (_popups['fundLtOvrd'].getField('ruleType').getValue()=="56") // Distribution Tax Rule
											{
												_popups['fundLtOvrd'].getField('overrideValues').reset();
												_controller.loadOverrideValuesList('DistTaxRuleList');
												_popups['fundLtOvrd'].getField('overrideValues').setValue('1');
												_popups['fundLtOvrd'].getField('overrideValues').showField();
												_popups['fundLtOvrd'].getField('overrideAllowed').hideField();
												_popups['fundLtOvrd'].getField('overrideDec').hideField();
												_popups['fundLtOvrd'].getField('overrideLog').hideField();																						
											}
											else if (ovrType == "overrideLog")
											{
												_popups['fundLtOvrd'].getField('overrideLog').reset();
												_popups['fundLtOvrd'].getField('overrideLog').setValue('yes');
												_popups['fundLtOvrd'].getField('overrideLog').showField();
												_popups['fundLtOvrd'].getField('overrideLog').disableField();
												
												_popups['fundLtOvrd'].getField('overrideValues').hideField();
												_popups['fundLtOvrd'].getField('overrideAllowed').hideField();
												_popups['fundLtOvrd'].getField('overrideDec').hideField();
											}
											else if (ovrType == "overrideDec")
											{
												_popups['fundLtOvrd'].getField('overrideDec').reset();
												_popups['fundLtOvrd'].getField('overrideDec').showField();
												_popups['fundLtOvrd'].getField('overrideValues').hideField();
												_popups['fundLtOvrd'].getField('overrideAllowed').hideField();
												_popups['fundLtOvrd'].getField('overrideLog').hideField();
												
											}
										}
									}
								})	
								,new DesktopWeb.Controls.YesNoComboBox({
									itemId: 'overrideLog'
									,width: 100
									,fieldLabel: _translationMap['OverrideValue']	
									,allowBlank: false
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'overrideDec'
									,width: 100	
									,fieldLabel: _translationMap['OverrideValue']
									,validator: function(value){
										if (this.isVisible() && value != "")
										{
											return true;
										}
										else
										{
											return _translationMap['fldRequired']
										}										
									}
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'overrideValues'
										,width: 180
										,fieldLabel: _translationMap['OverrideValue']
										,allowBlank: false
									})	
								,new DesktopWeb.Controls.YesNoComboBox({
									itemId: 'overrideAllowed'
										,width: 70
										,fieldLabel: _translationMap['OverrideAllowed']
										,allowBlank: false
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
						if (_popups['fundLtOvrd'].isValid())
						{
							_controller.saveRuleUpdate(_popups['fundLtOvrd'].action, _popups['fundLtOvrd'].getData());	
						}							
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_controller.closePopup('fundLtOvrd');}
				})
			]
			,setAction: function(action)
			{
				this.action = action
			}
			,init: function()
			{																	
				this.clearAllFields();
				this.get(0).hide(); //hide delete message				
				switch(this.action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['LimitationOverrideRule']+ ' - ' +_translationMap['Add']);
						this.enableAllFields();						
						this.toggleOverrideType(null, null);
						this.getField('overrideAllowed').setValue('no');
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['LimitationOverrideRule']+ ' - ' +_translationMap['Delete']);
						this.get(0).show();  
						var ruleType = _grids['fundLtOvrd'].getSelectedRecord().get('ruleType');
						this.toggleOverrideType(ruleType, _controller.getRuleTypeOverrideType(ruleType));
						this.populateWithSelectedRecord();
						this.disableAllFields();
						break;
					}
				}
			}
			,toggleOverrideType: function(ruleType, overrideType)
			{					
				if (ruleType == '49')
				{
					_controller.loadOverrideValuesList('RefundAmountList');
					this.getField('overrideValues').showField();
					this.getField('overrideAllowed').showField();
					this.getField('overrideDec').hideField();
					this.getField('overrideLog').hideField();
				}
				else if (ruleType == '55')
				{
					_controller.loadOverrideValuesList('DistTaxPayRuleList');
					this.getField('overrideValues').showField();
					this.getField('overrideAllowed').hideField();
					this.getField('overrideDec').hideField();
					this.getField('overrideLog').hideField();
				}
				else if (ruleType == '56')
				{
					_controller.loadOverrideValuesList('DistTaxRuleList');
					this.getField('overrideValues').showField();
					this.getField('overrideAllowed').hideField();
					this.getField('overrideDec').hideField();
					this.getField('overrideLog').hideField();
				}
				else
				{				
					if (overrideType == 'overrideLog')
					{
						this.getField('overrideDec').hideField();
						this.getField('overrideLog').showField();
						this.getField('overrideValues').hideField();
						this.getField('overrideAllowed').hideField();
						
						this.getField('overrideLog').setValue('yes');
						this.getField('overrideLog').disableField();
					}	
					else 
					{
						this.getField('overrideDec').showField();
						this.getField('overrideLog').hideField();
						this.getField('overrideValues').hideField();
						this.getField('overrideAllowed').hideField();
						
						this.getField('overrideLog').setValue('no');
						this.getField('overrideLog').disableField();
					}
				}
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['fundLtOvrd'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];
				this.getField('ruleType').setValue(rec.data['ruleType']);

				this.getField('overrideDec').setValue(rec.data['overrideDec']);
				this.getField('overrideLog').setValue(rec.data['overrideLog']);	
				
				this.getField('overrideValues').setValue(rec.data['overrideDec']);
				this.getField('overrideAllowed').setValue(rec.data['overrideLog']);			
			}
			,getData: function()
			{
				var data = {};				
				data['runMode'] = this.action;
				data['ruleType'] = this.getField('ruleType').getValue();
				if (this.getField('ruleType').getValue() == '49')
				{
					data['overrideDec'] = this.getField('overrideValues').getValue() ;
					data['overrideLog'] = this.getField('overrideAllowed').getValue() ; 
				}
				else if (this.getField('ruleType').getValue() == '55' || this.getField('ruleType').getValue() == '56')
				{
					data['overrideDec'] = this.getField('overrideValues').getValue() ;
					data['overrideLog'] = '';
				}
				else
				{
					if (this.getField('overrideDec').getValue() != '')
					{
						data['overrideDec'] = this.getField('overrideDec').getValue() ;
					}
					else
					{
						data['overrideDec'] = '';
					}
					
					data['overrideLog'] = this.getField('overrideLog').getValue() ; 
				}
										
				if (this.action == _controller.ADD)
				{				
					data['taxJurisDecl'] = "*";
					data['provResDecl'] = "*";
					data['accountTypeDecl'] = "*";
					data['taxTypeDecl'] = "*";
					data['acctDesigDecl'] = "*";
					data['onlineEWI'] = "E";
					data['cycleEWI'] = "E";
					data['esgEWI'] = "E";
				}
								
				return data;
			}										
		})
		
		,details: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 580
			,fieldToEdit: null
			,fieldList: null								
			,modal: true
			,listeners: {
				beforeshow: function(){
					this.init();
				} 
			}
			,defaults: {border:false, style: 'padding: 4px;'}
			,items: [
				{
					layout: 'form'					
					,labelWidth: 110																						
					,items: [
						new DesktopWeb.Controls.ComboBox({
							itemId: 'inclExcl'			
							,width: 120							
							,fieldLabel: _translationMap['Chooseoptionsto']
							,allowBlank: false
							,store: new Ext.data.ArrayStore({
				        		id: 0,
				        		fields: [
				            		'myId',
				            		'displayText'
				        		],
				        	data: [['include', _translationMap['Include']], ['exclude', _translationMap['Exclude']]]
				    		})				
				    		,valueField: 'myId'
				    		,displayField: 'displayText'
						})				
						,new DesktopWeb.AdvancedControls.ItemSelector({
							itemId: 'optionsSelector'
							,listName: null
							,height: 300
							,width: 540
							,style: 'margin-left:10px; margin-bottom: 10px'		
							,allowReordering: false		
							,availableGridProperties: {
								width: 230				
								,autoExpandColumn: 'options'							
								,store: new Ext.data.XmlStore({
									record: 'Element'					
									,fields: ['code', 'value']																							
								})						
								,columns: [
									{
										id: 'options'					
										,header: _translationMap['Options']
										,dataIndex: 'code' 
										,renderer: function(value){											
											return value + " - " + _controller.getListValueDesc(_popups['details'].getField('optionsSelector').listName, value);;											
										}
									}
								]	
							}
							,selectedGridProperties: {
								width: 230
								,autoExpandColumn: 'options'							
								,store: new Ext.data.XmlStore({
									record: 'Element'					
									,fields: ['code', 'value']														
								})
								,columns: [
									{ 
										id: 'options'
										,header: _translationMap['Options']
										,dataIndex: 'code'
										,renderer: function(value){											
											return value + " - " + _controller.getListValueDesc(_popups['details'].getField('optionsSelector').listName, value);;											
										}
									}
								]
							}
						})													
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						_controller.saveDetailsUpdate(_popups['details'].fieldToEdit, _popups['details'].getData());	
						_controller.closePopup('details');
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){
						_controller.closePopup('details');
					}
				})
			]
			,setEditDetails: function(field, listName)
			{
				this.fieldToEdit = field;
				this.fieldList = listName;
			}
			,init: function()
			{
				this.getField('optionsSelector').listName = this.fieldList;		
				this.getField('optionsSelector').loadAvailableData(_controller.getDetailsListXML(this.fieldList));
				this.getField('optionsSelector').removeAllFromSelected();
				
				var curValue = _fields[this.fieldToEdit].getValue();				
				if (curValue.indexOf("*") == 0)
				{
					this.getField("inclExcl").setValue('exclude');
					curValue = (curValue.length > 1 ? curValue.substring(2) : "");
					curValue = curValue.replace(/!/g, '');
					if (curValue.length > 0)
					{
						this.getField('optionsSelector').setSelectedByData('code', curValue.split(","));
					}
				}
				else
				{
					this.getField("inclExcl").setValue('include');
					if (curValue.length > 0)
					{
						this.getField('optionsSelector').setSelectedByData('code', curValue.split(","));
					}
				}
								
				switch(this.fieldToEdit)
				{
					case 'taxJurisDecl':
					{
						this.setTitle(_translationMap['TaxJurisdiction']+ ' - ' +_translationMap['Edit']);
						break;		
					}
					case 'provResDecl':
					{
						this.setTitle(_translationMap['ProvinceofResidence']+ ' - ' +_translationMap['Edit']);
						break;		
					}
					case 'accountTypeDecl':
					{
						this.setTitle(_translationMap['AccountType']+ ' - ' +_translationMap['Edit']);
						break;		
					}
					case 'taxTypeDecl':
					{
						this.setTitle(_translationMap['TaxType']+ ' - ' +_translationMap['Edit']);
						break;		
					}
					case 'acctDesigDecl':
					{
						this.setTitle(_translationMap['AccountDesignation']+ ' - ' +_translationMap['Edit']);
						break;		
					}					
				}																													
			}
			,getData: function()
			{
				var value = "";
				
				var selectedRecords = this.getField("optionsSelector").getSelectedRecords();
				
				if (this.getField("inclExcl").getValue() == "include")
				{					
					for (var i = 0; i < selectedRecords.length; i++)
					{
						value += (i > 0 ? "," : "") + selectedRecords[i].data['code']; 
					}
					if (value == "") value = "*";
				}
				else
				{
					value = "*";
					for (var i = 0; i < selectedRecords.length; i++)
					{
						value += ",!" + selectedRecords[i].data['code']; 
					}
				}
				
				return value;
			}			
		})
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,header: _header
		
		,grids: _grids
		
		,popups: _popups
		
		,buttons: _buttons
			
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				_header
				,new Ext.Container({
					style: 'padding-left:12px; padding-right:10px'						
					,items: [						
						_grids['fundLtOvrd']
						,{
							xtype: 'fieldset'
							,title: _translationMap['ApplicableTo']
							,items: [
								{
									layout: 'column'																
									,items: [
										{
											layout: 'form'
											,columnWidth: 0.9
											,labelWidth: 165
											,style: 'padding-left: 5px'
											,items: [
												new DesktopWeb.Controls.Label({
													fieldLabel: _translationMap['ApplicationCategory']
													,text: _translationMap['Value']
													,labelStyle: 'text-decoration: underline'
													,style: 'font-size: 13px; text-decoration: underline'
													,labelSeparator: ''
												})
												,_fields['taxJurisDecl']
												,_fields['provResDecl']
												,_fields['accountTypeDecl']
												,_fields['taxTypeDecl']
												,_fields['acctDesigDecl']																												
											]
										}
										,{											
											columnWidth: 0.1												
											,items: [
												new DesktopWeb.Controls.ColumnPlaceHolder()
												,_buttons['taxJurisDecl']
												,_buttons['provResDecl']
												,_buttons['accountTypeDecl']
												,_buttons['taxTypeDecl']
												,_buttons['acctDesigDecl']
											]
										}
									]
								}
							]
						}
						,{
							xtype: 'fieldset'
							,title: _translationMap['Severity']
							,width: 250																																	
							,items: [
								{
									layout: 'form'
									,items: [
										_fields['onlineEWI']
										,_fields['cycleEWI']
										,_fields['esgEWI']											
									]												
								}
							]
						}
					]
				})
			]
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){_controller.ok();}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){_controller.cancel();}
			})
		]			
	}
}