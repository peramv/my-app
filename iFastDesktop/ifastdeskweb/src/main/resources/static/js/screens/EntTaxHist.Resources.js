/*********************************************************************************************
 * @file	EntTaxHist.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for Entity Tax Jurisdictionscreen
 *
 * History :
 * 10 Jan 2013 G. Thawornwachirakun P0195459 T52973
 *             Add new GridPanel for displaying prim-hist record
 *
 * 04 Feb 2013 G. Thawornwachirakun P0195459 I3230914 T53045
 *              Add sync checkbox under EntityTaxHist Grid
 *
 * 04 Apr 2013 G. Thawornwachirakun P0195459 I3258601 T53348
 *              Modify validation method to markInvalid to TaxJuris 
 *              and Effective Date 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 500;
	var _layoutWidth = 730;
	
	// **** fields ****
	var _fields = {
	}
	
	// **** grids ****
	var _grids = {
		taxJurisInfo: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth - 16
			,style: "margin-bottom:15px"
			,autoScroll: true							
			,height: 200		
			,buttonAlign : 'left'
			,autoExpandColumn: 'taxJuris'											
			,store: new Ext.data.XmlStore({
				record: 'EntityTaxJurisDetail'					
				,fields: ['runMode', 'taxyr', 'taxJuris', 'taxDesc', 'effDate', 'procDate', 'modDate', 'modUser', 'username', 'allowUpd', 'allowDel', 'version', 'entTaxHistID']
				,listeners: {
					load: function(store, records)
					{		
						Ext.each(records, function(record){
							record.data.effDate = DesktopWeb.Util.getDateDisplayValue(record.data.effDate);
							record.data.procDate = DesktopWeb.Util.getDateDisplayValue(record.data.procDate);
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
						});
					
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL
						});
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
					rowselect: function(selModel, index, record){_controller.updateActionButtons();}
					,rowdeselect: function(){_controller.updateActionButtons();}
				}						
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['TaxYear'], dataIndex: 'taxyr', width:70}
					,{header: _translationMap['TaxJurisdiction'], id:'taxJuris', renderer: function(val, metaData, record){return (record.data['taxJuris'] + ' - ' + record.data['taxDesc'])}}
					,{header: _translationMap['EffDate'], dataIndex: 'effDate', width:90}
					,{header: _translationMap['CreatedOn'], dataIndex: 'procDate', width:90}
					,{header: _translationMap['CreatedBy'], dataIndex: 'username', width:100}
					,{header: _translationMap['ModDate'], dataIndex: 'modDate', width:90}
					,{header: _translationMap['ModUser'], dataIndex: 'modUser', width:100}
				]							
			})
			,buttons: [	
				new DesktopWeb.Controls.Checkbox({
					itemId: 'chkSync'
					,fieldLabel : ""
					,boxLabel : _translationMap['UpdateShareHist']					
				})
				,'->'			
				, new DesktopWeb.Controls.ActionButton({
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
		,SharetaxJurisHistInfo: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth - 16
			,style: "margin-bottom:15px"			
			,autoScroll: true								
			,height: 160
			,autoExpandColumn: 'shrTaxJuris'											
			,store: new Ext.data.XmlStore({			
				record: 'ShareholderTaxJurisDetail'									
				,fields: [ 'shrTaxyr', 'shrTaxJuris', 'shrTaxDesc', 'shrEffDate', 'shrProcDate', 'shrModDate', 'shrModUser', 'shrUsername']
				,listeners: {
					load: function(store, records)
					{															
						Ext.each(records, function(record){
							record.data.shrEffDate = DesktopWeb.Util.getDateDisplayValue(record.data.shrEffDate);
							record.data.shrProcDate = DesktopWeb.Util.getDateDisplayValue(record.data.shrProcDate);
							record.data.shrModDate = DesktopWeb.Util.getDateDisplayValue(record.data.shrModDate);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}	
			})			
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['TaxYear'], dataIndex: 'shrTaxyr', width:70}									
					,{header: _translationMap['TaxJurisdiction'], id:'shrTaxJuris'
						, renderer: function(val, metaData, record){
							return (record.data['shrTaxJuris'] + ' - ' + record.data['shrTaxDesc'])
						  }
					}
					,{header: _translationMap['EffDate'], dataIndex: 'shrEffDate', width:90}
					,{header: _translationMap['CreatedOn'], dataIndex: 'shrProcDate', width:90}							
					,{header: _translationMap['CreatedBy'], dataIndex: 'shrUsername', width:100}
					,{header: _translationMap['ModDate'], dataIndex: 'shrModDate', width:90}
					,{header: _translationMap['ModUser'], dataIndex: 'shrModUser', width:100}
				]							
			})			
		})	
	}
	
	// **** popups ****
	var _popups = {			
		taxJuris: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 410
			,action: null						
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']							
					,style: 'text-align:center'														
				}						
				,{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 90
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'taxJuris'
							,width: 270
							,fieldLabel: _translationMap['TaxJurisdiction']
							,allowBlank: false
						})											
						,new DesktopWeb.Controls.DateField({
							itemId: 'effDate'
							,fieldLabel: _translationMap['EffectiveDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})		
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['taxJuris'].isValid())
							 _controller.savePopup(_popups['taxJuris'].action, _popups['taxJuris'].getData());						
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['taxJuris'].hide();}
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
						this.setTitle(_translationMap['EntityTaxJurisdiction'] + ' - ' + _translationMap['Add']);
						this.enableAllFields();
						this.getField('taxJuris').focus();				
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['EntityTaxJurisdiction'] + ' - ' + _translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();													
						this.getField('taxJuris').focus();				
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['EntityTaxJurisdiction'] + ' - ' + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['taxJurisInfo'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];
				this.getField('taxJuris').setValue(rec.data['taxJuris']);
				this.getField('effDate').setValue(rec.data['effDate']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['taxJuris'] = this.getField('taxJuris').getValue();
				data['taxDesc'] = this.getField('taxJuris').getValueDesc();
				data['taxyr'] = this.getField('effDate').getValue().getFullYear();
				data['effDate'] = this.getField('effDate').getDisplayDateString();
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
						xtype: 'fieldset'
						,title: _translationMap['EntityTaxJurisHistTitle']
						,style: 'margin-top:5px;'
						,items: [
							_grids['taxJurisInfo']
						]
					}	
					,{
						xtype: 'fieldset'
						,title: _translationMap['ShareTaxJurisHistTitle']
						,style: 'margin-top:5px;'
						,items: [
							_grids['SharetaxJurisHistInfo']
						]
					}	
				]				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function(){DesktopWeb.Util.commitScreen()}
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