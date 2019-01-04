/*********************************************************************************************
 * @file	ClassCopy.Resources.js
 * @author	Rod Walker	
 * @desc	Resources JS file for Fund Class Copy screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54443
 *          - Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 410;
	var _layoutWidth = 685;
		
	var _buttons = {
		lookup: new DesktopWeb.Controls.ActionButton({																									
			text: _translationMap['lookupBtn']
			,disabled: true
			,handler: function(){				
				_controller.doLookup();
			}			
		})
	}
	
	// **** fields ****
	var _fields = {		
		basicInfo: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['basicInfo']
		})
		,feeParameters: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['feeParameters']
		})
		,shareholderGroup: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['shareholderGroup']
		})
		,registeredTrustee: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['registeredTrustee']
		})
		,perfFeeParms: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['perfFeeParms']
		})
		,eventSchedule: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['eventSchedule']
		})
		,cusTrdeAndValtDate: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['cusTrdeAndValtDate']
		})
		,partnership: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['partnership']
		})
		,fromFund: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['fromFund']
			,smartview: 'fundOnlySearch'				
			,fields: ['fndDisp', 'fundCode']						
			,valueField: 'fundCode'
			,displayField: 'fndDisp'								
			,width: 490												
			,listeners: {
				populated: function()
				{											
					_buttons['lookup'].enable();
					_controller.clearAll();														
				}
				,cleared: function()
				{
					_buttons['lookup'].disable();
					_controller.clearAll();														
				}				
			}																										
		})
		,toFund: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['toFund']
			,smartview: 'fundOnlySearch'				
			,fields: ['fndDisp', 'fundCode']						
			,valueField: 'fundCode'
			,displayField: 'fndDisp'								
			,width: 490								
			,listeners: {
				populated: function()
				{																				
					_grids['classes'].enableButton('addBtn');					
				}
				,cleared: function()
				{										
					_grids['classes'].disableButton('addBtn');									
				}				
			}																									
		})
	}
	
	// **** grids ****
	var _grids = {
		classes: new DesktopWeb.AdvancedControls.GridPanel({							
			autoScroll: true							
			,height: 175
			,width: _layoutWidth - 16									
			,store: new Ext.data.XmlStore({
				record: 'ClassInfo'					
				,fields: ['runMode'
						  ,'classCode'
						  ,'newClassCode'
						  ,'dateEff'
						  ,'extFundId'
						  ,'cusip'
						  ,'isin'
						  ,'wkn'
						  ,'fundLoadGrp'
						  ,'errMsg'
						  ,'perfFeeFlag']
				,listeners: {
					load: function(store, records)
					{	
						Ext.each(records, function(record){
							record.data.dateEff = DesktopWeb.Util.getDateDisplayValue(record.data.dateEff);
						});						

						store.fireEvent('datachanged', store); //to set data in grid again
						_controller.updateClassButtons();	
						
					}																							
				}						
			})
			,selModel: new Ext.grid.RowSelectionModel({								
				listeners: {
					rowselect: function(selModel, index, record){_controller.updateClassButtons();}
					,rowdeselect: function(){_controller.updateClassButtons();}
				}						
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [																																																							
					{
						dataIndex: 'errMsg'
						,renderer: function(val){
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
						,width: 25
					}
					,{header: _translationMap['fromClass'], dataIndex: 'classCode', width: 75}
					,{header: _translationMap['newClass'], dataIndex: 'newClassCode', width:75}
					,{header: _translationMap['effectiveDate'], dataIndex: 'dateEff', width:85}							
					,{header: _translationMap['isin'], dataIndex: 'isin', width: 85}
					,{header: _translationMap['cusip'], dataIndex: 'cusip', width: 85}
					,{header: _translationMap['wknFundID'], dataIndex: 'wkn', width: 95}
					,{header: _translationMap['extFundID'], dataIndex: 'extFundId', width:85}
					,{header: _translationMap['fundLoadGroup'], dataIndex: 'fundLoadGrp', width:95}
				]
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['addBtn']
					,handler: function(){				    
						_controller.openPopup(_controller.ADD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['modBtn']
					,handler: function(){
						_controller.openPopup(_controller.MOD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'removeBtn'
					,text: _translationMap['rmvBtn']
					,handler: function(){_controller.remove();}							
				})									
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'selectAllBtn'
					,text: _translationMap['selectAllBtn']
					,handler: function(){_controller.selectAll();}							
				})
			]			
		})
	}
	
	// **** popups ****
	var _popups = {
		classCopy: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 510
			,action: null						
			,modal: true
			,defaults: {border:false, style: 'padding:4px'}			
			,items: [								
				{						
					layout: 'column'
					,defaults: {
						layout: 'form'
						,columnWidth: 0.5
						,labelWidth: 105
						,border: false
					}
					,items: [
						{
							items: [
								new DesktopWeb.Controls.TextField({
									fieldLabel: _translationMap['fromClass']
									,itemId: 'classCode'
									,width: 85
									,allowBlank: false									
								})
								,new DesktopWeb.Controls.DateField({
									fieldLabel: _translationMap['effectiveDate']
									,itemId: 'dateEff'
									,width: 100
									,allowBlank: false
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
								,new DesktopWeb.Controls.TextField({
									fieldLabel: _translationMap['cusip']
									,itemId: 'cusip'
									,width: 100									
								})
								,new DesktopWeb.Controls.TextField({
									fieldLabel: _translationMap['extFundID']
									,itemId: 'extFundId'									
									,width: 85
								})
							]
						}
						,{
							items: [
								new DesktopWeb.Controls.TextField({
									fieldLabel: _translationMap['newClass']
									,width: 85
									,itemId: 'newClassCode'
									,allowBlank: false
								})
								,new DesktopWeb.Controls.TextField({
									fieldLabel: _translationMap['isin']
									,itemId: 'isin'
									,width: 100
								})
								,new DesktopWeb.Controls.TextField({
									fieldLabel: _translationMap['wknFundID']
									,itemId: 'wkn'
									,width: 100									
								})
								,new DesktopWeb.Controls.TextField({
									fieldLabel: _translationMap['fundLoadGroup']
									,itemId: 'fundLoadGrp'
									,width: 100									
								})
							]
						}
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['okBtn']
					,handler: function(){
						if (_popups['classCopy'].isValid())
						{
							_controller.saveFundClass(_popups['classCopy'].action,_popups['classCopy'].getData());
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['cancelBtn']
					,handler: function(){_popups['classCopy'].hide();}
				})
			]
			,init: function(action)
			{										
				this.action = action					
				this.clearAllFields();				
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['classAdd']);
						this.enableAllFields();																						
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['classMod']);
						this.enableAllFields();
						this.populateWithSelectedRecord();																					
						break;
					}					
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['classes'].getSelectedRecord();				
				this.getField('classCode').setValue(rec.data['classCode']);
				rec.data['newClassCode'] != "" ? this.getField('newClassCode').setValue(rec.data['newClassCode']) : null;
				rec.data['dateEff'] != "" ? this.getField('dateEff').setValue(rec.data['dateEff']) : null;	
				rec.data['wkn'] != "" ? this.getField('wkn').setValue(rec.data['wkn']) : null;	
				rec.data['isin'] != "" ? this.getField('isin').setValue(rec.data['isin']) : null;	
				rec.data['cusip'] != "" ? this.getField('cusip').setValue(rec.data['cusip']) : null;	
				rec.data['extFundId'] != "" ? this.getField('extFundId').setValue(rec.data['extFundId']) : null;	
				rec.data['fundLoadGrp'] != "" ? this.getField('fundLoadGrp').setValue(rec.data['fundLoadGrp']) : null;	
			}
			,getData: function()
			{
				var data = {};
				data['classCode'] 		= this.getField('classCode').getValue();
				data['newClassCode'] 	= this.getField('newClassCode').getValue();
				data['dateEff'] 		= this.getField('dateEff').getDisplayDateString();
				data['wkn'] 			= this.getField('wkn').getValue();
				data['isin'] 			= this.getField('isin').getValue();
				data['cusip'] 			= this.getField('cusip').getValue();
				data['extFundId']		= this.getField('extFundId').getValue();
				data['fundLoadGrp'] 	= this.getField('fundLoadGrp').getValue();
				return data;
			}														
		})					
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
		    id: 'fundClassCopyScreen'
			,height: _layoutHeight
			,width: _layoutWidth
			,items: [
				{
					layout: 'column'
					,defaults: {
						layout: 'form'
					}
					,items: [
						{
							width: 585
							,labelWidth: 75
							,items: [
								_fields['fromFund']
							]
						}
						,{
							width: 100
							,items: [
								_buttons['lookup']
							]
						}
					]
				}
				,{
					layout: 'form'
					,labelWidth: 400
					,items: [
						new DesktopWeb.Controls.Label({
							fieldLabel: _translationMap['cpyClassInfo']
						})
					]
				}
				,{
					layout: 'column'
					,style: 'padding-left:25px; margin-bottom: 8px;'
					,defaults: {
						layout: 'form'
					}
					,items: [
						{
							columnWidth: 0.35								
							,items: [
								_fields['basicInfo']																	
								,_fields['feeParameters']
								,_fields['shareholderGroup']
								,_fields['registeredTrustee']
							]
						}
						,{
							columnWidth: 0.35								
							,items: [
								_fields['perfFeeParms']
								,_fields['eventSchedule']
								,_fields['cusTrdeAndValtDate']
								,_fields['partnership']													
							]
						}
						,{
							columnWidth: 0.33								
							,items: [
								
							]
						}
						
					]
				}
				,{
					layout: 'form'
					,labelWidth: 75
					,items: [
						_fields['toFund']
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['availClass']
					,style: 'margin-top: 4px;'						
					,items:[
						_grids['classes']
					]
				}
			]																				
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
			    id: 'okBtn'
				,text: _translationMap['okBtn']
				,handler: function(){
					if (_controller.updatesFlag)
					{
						if (_grids['classes'].getStore().getCount() > 0)
						{
							_controller.doValidate();
						}
						else{
							DesktopWeb.Util.displayError('This is no class to be copied.');
						}
					}
				}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['cancelBtn']
				,handler: function(){DesktopWeb.Util.cancelScreen()}
			})
		]			
	}
}