/*********************************************************************************************
 * @file	AcctBalOverride.Resources.js
 * @author	
 * @desc	Resources JS file for Account Balance Override screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 350;
	var _layoutWidth = 600;
	
	// **** fields ****
	var _fields = {
		searchValue: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['SearchValue']
			,style: 'text-transform: none'
			,width: 360
			,listeners: {
				render: function(c){
					Ext.QuickTips.register({
						target: c.getEl()
						,width: 150
						,showDelay: 0
						,dismissDelay: 0
						,text: _controller.alertSearchOptions()
					})
				}
			}
		})
		,account: new DesktopWeb.Controls.Label({
			fieldLabel: 'AcctNum/Name'
			,width: 360
		})
		,fund: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Fund']
			,smartview: 'fundSearch'				
			,fields: ['fund', 'class', 'displayValue']
			,valueField: 'displayValue'
			,displayField: 'displayValue'								
			,width: 360
			,listeners: {
				render: function(c){
					Ext.QuickTips.register({
						target: c.getEl()
						,width: 175
						,showDelay: 0
						,dismissDelay: 0
						,text: _controller.alertFundSuggestOptions()
					})
				}
			}
		})
		,startDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['StartDate']
			,allowBlank: false
			,width: 135
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,endDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['EndDate']
			,allowBlank: false
			,width: 135
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
	}
	
	// **** buttons ***
	
	var _buttons = {		
		search: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,handler: function() {
				if(_fields['startDate'].isValid() && _fields['endDate'].isValid()){
					_controller.searchAcctBalOvrd();
				}
			}
		})
	}
	
	// **** grids ****
	var _grids = {
		acctBalOvrd: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth
			,style: "margin-bottom:15px"
			,autoScroll: true							
			,height: 150
			,autoExpandColumn: 'name'											
			,store: new Ext.data.XmlStore({
				record: 'AccountBalance'					
				,fields: ['fundRowID', 'acctNum', 'acctRowID', 'fundCode', 'classCode', 'bayCom', 'name', 'effDate','units', 'version', 'UpdAllowed']					
				,listeners: {
					load: function(store, records)
					{															
						Ext.each(records, function(record){
							record.data.effDate = DesktopWeb.Util.getDateDisplayValue(record.data.effDate);						
						});

						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}	
			})	
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.updateActionButtons();}
					,rowdeselect: function(){_controller.updateActionButtons();}
				}						
			})			
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['Account'], dataIndex: 'acctNum', width:100}					
					,{header: _translationMap['Name'], id:'name', dataIndex: 'name'}
					,{header: _translationMap['EffectiveDate'], dataIndex: 'effDate', width:80}
					,{header: _translationMap['Fund'], width:80, renderer: function(val, metaData, record){return (record.data['fundCode'] + ' - ' + record.data['classCode'])}}
					,{header: _translationMap['Units'], dataIndex: 'units', width:80}					
				]							
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']							
					,handler: function(){_controller.openActionPopup(_controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup(_controller.DEL);}							
				})									
			]			
		})		
	}
	
	// **** popups ****
	var _popups = {			
		acctBalOvrdPopup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 520
			,action: null
			,modal: true	
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']							
					,style: {'text-align':'center','padding':'2px'}
				}										
				,{
					style: 'padding:5px'
					,layout: 'form'
					,items: [
						new DesktopWeb.Controls.SuggestField({
							itemId: 'accountFld'
							,id: 'acctId'	
							,fieldLabel: _translationMap['Account']
							,smartview: 'AccountSearch'				
							,fields: ['displayValue', 'acctNum', 'addr1', 'addr2', 'addr3', 'addr4', 'addr5', 'broker', 'brokerName', 'branch', 'brnName', 'salesRep', 'slsrepName', 'brkAcct']
							,valueField: 'displayValue'
							,displayField: 'displayValue'								
							,width: 380												
							,allowBlank: false
							,listeners: {
								'render': function(c){								
									_controller.accountSuggestOptionQuickTip();
									this.on("valid", function(){										
										_controller.accountSuggestDetails(_popups['acctBalOvrdPopup'].action);
									})
									,this.on("invalid", function(){
										_controller.accountSuggestOptionQuickTip();
									})										
								}									
							}												
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'fundFld'
							,id: 'fundId'
							,fieldLabel: _translationMap['Fund']
							,smartview: 'fundSearch'				
							,fields: ['fund', 'class', 'displayValue']
							,valueField: 'displayValue'
							,displayField: 'displayValue'								
							,width: 380
							,allowBlank: false
							,listeners: {
								render: function(c){								
									_controller.fundSuggestOptionQuickTip();
								}
							}	
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'effDateFld'	
							,width: 150							
							,fieldLabel: _translationMap['EffectiveDate']
							,allowBlank: false	
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())							
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'unitsFld'	
							,width: 150							
							,fieldLabel: _translationMap['Units']
							,allowBlank: false	
							,originalValue: ''							
						})
					]	
				}																		
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['acctBalOvrdPopup'].isValid())
						{
							_controller.savePopup(_popups['acctBalOvrdPopup'].action, _popups['acctBalOvrdPopup'].getData());
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_controller.closeActionPopup();}
				})
			]
			,listeners: {
				'afterlayout': function(){					
					if(this.action != _controller.ADD){
						Ext.QuickTips.unregister(_popups['acctBalOvrdPopup'].getField('accountFld').id);
						Ext.QuickTips.unregister(_popups['acctBalOvrdPopup'].getField('fundFld').id);
					}	
					else{
						_controller.accountSuggestOptionQuickTip();
						_controller.fundSuggestOptionQuickTip();
					}
				}
			}
			,init: function(action)
			{										
				this.action = action					
				this.clearAllFields();
				this.get(0).hide(); //hide delete message
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['AcctBalOvrd'] + ' - ' + _translationMap['Add']);
						this.enableAllFields();
						this.getField('accountFld').focus();				
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['AcctBalOvrd'] + ' - ' + _translationMap['Modify']);
						this.disableAllFields();							
						this.getField('unitsFld').enableField();									
						this.populateWithSelectedRecord();	
						this.getField('unitsFld').focus();				
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['AcctBalOvrd'] + ' - ' + _translationMap['Delete']);
						this.get(0).show();
						this.disableAllFields();
						this.populateWithSelectedRecord();
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['acctBalOvrd'].getSelectedRecord();
				_controller.accountSearch(rec.data['acctRowID']);
				_controller.fundSearch(rec.data['fundRowID'], false);	
				this.getField('effDateFld').setValue(rec.data['effDate']);
				this.getField('unitsFld').setValue(rec.data['units']);				
			}
			,getData: function()
			{
				var data = {};				
				var acctrecord = this.getField('accountFld').findRecord(this.getField('accountFld').valueField, this.getField('accountFld').getValue());
				data['acctNum'] = acctrecord.data['acctNum'];
				var record = this.getField('fundFld').findRecord(this.getField('fundFld').valueField, this.getField('fundFld').getValue());
				data['fundCode'] = record.data['fund'];				
				data['classCode'] = record.data['class'];									
				data['effDate'] = this.getField('effDateFld').getDisplayDateString();
				data['units'] = this.getField('unitsFld').getValue();				
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
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth																
				,items: [
					{
						layout: 'form'
						,items:	[
							_fields['searchValue']										
							,_fields['account']
							,_fields['fund']
							,_fields['startDate']
						]
					}													
					,{
						layout: 'column'
						,items:[
							{
								columnWidth: 0.85
								,layout: 'form'
								,items:	_fields['endDate']	
							}
							,{
								columnWidth: 0.15
								,layout: 'form'
								,items:	_buttons['search']	
							}							
						]						
					}										
					,_grids['acctBalOvrd']																	
				]				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}	