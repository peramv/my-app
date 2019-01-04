/*********************************************************************************************
 * @file	LIFGainLoss.Resources.js
 * @author	Suchit Majumdars
 * @desc	Resources JS file for LIFGainLoss screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 */
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 235;
	var _layoutWidth = 600;
	
	// **** fields ****
	var _fields = {	
		yearFilterCombo: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['YrFilter']			
			,width: 70
			,allowBlank: false							
		})		
		,totalGainOrLossBox: new DesktopWeb.Controls.Label({				
			fieldLabel: _translationMap['TotGnOrLs']								
		})				
	}
	// **** buttons ****
	var _buttons = {
		refreshButton: new DesktopWeb.Controls.ActionButton({
			itemId: 'refBtn'
			,style: 'margin-left:20px'
			,text: _translationMap['Refresh']
			,handler: function(){_controller.doRefresh(_fields['yearFilterCombo'].getValue())}
		})			
	}
	
	// **** grids ****
	var _grids = {	
		lifGridDetails: new DesktopWeb.AdvancedControls.GridPanel({				
			width: _layoutWidth
			,height: 200
			,autoScroll: true				
			,style: 'margin-top:5px'		
			,store: new Ext.data.XmlStore({
				record: 'Transaction'
				,fields: ['txnNum', 'deff', 'setDt', 'depTyp','depTypDesc','grossAmt', 'gainLoss']	
				,listeners: {
					load: function(store, records)
					{															
						Ext.each(records, function(record){
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							record.data.setDt = DesktopWeb.Util.getDateDisplayValue(record.data.setDt);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}					
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(){_controller.updateActionButton()}						
					,rowdeselect: function(){_controller.updateActionButton()}
				}
			})			
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: _translationMap['txnNum'], dataIndex: 'txnNum', id: 'txnNum', width: 85}
					,{header: _translationMap['EffDate'], dataIndex: 'deff', width: 85}
					,{header: _translationMap['setDt'], dataIndex: 'setDt', width: 85}
					,{header: _translationMap['depTyp'], id: 'depositType', width: 160, renderer: function(val, metaData, record){return (record.data['depTyp'] + ' - ' + record.data['depTypDesc'])}}
					,{header: _translationMap['grossAmt'], dataIndex: 'grossAmt', width: 95}
					,{header: _translationMap['gainLoss'], dataIndex: 'gainLoss', width: 95}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'updateBtn'								
					,text: _translationMap['UpdateGainLoss']						
					,handler: function(){_controller.openGainLossPopup(_controller.ADD);}
					,disabled: true
				})
			]
		})		
	}
			
	// **** popups ****
	var _popups = {
		gainLossUpdate: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 250
			,defaults: {border:false, style: 'padding-top: 4px; padding-left: 4px;'}
			,modal: true
			,listeners: {
				beforeShow: function(){_popups['gainLossUpdate'].init()}
				,show: function(){_popups['gainLossUpdate'].populateFields()}
			}
			,items: [
				{				
					layout: 'form'					
					,labelWidth: 100				
					,items: [							
						new DesktopWeb.Controls.Label({
							itemId: 'txnNum'
							,width: 100
							,fieldLabel: _translationMap['txnNum']																		
						})										
						,new DesktopWeb.Controls.Label({
							itemId: 'deff'
							,width: 90
							,fieldLabel: _translationMap['EffDate']																		
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'gainLoss'
							,allowBlank: false
							, width: 100
                            ,allowNegative: true
							,fieldLabel: _translationMap['gainLoss']
						})
					]
				}												
			]			
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['gainLossUpdate'].isValid())
						{
							_controller.saveGainLossUpdate( _popups['gainLossUpdate'].getData());							
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){
						_popups['gainLossUpdate'].hide();
					}
				})				
			]			
			,init: function()
			{			
				this.setTitle(_translationMap["gainLoss"] + " - " + _translationMap["Update"]);																														
			}
			,populateFields: function()
			{
				this.clearPopupFields();																																											
				this.populateWithSelectedRecord();							
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['lifGridDetails'].getSelectedRecord();				
				this.getField('txnNum').setValue(rec.data['txnNum']);
				this.getField('deff').setValue(rec.data['deff']);
				this.getField('gainLoss').setValue(rec.data['gainLoss']);				
			}			
			,getData: function()
			{
				var data = {};
				data['txnNum'] = this.getField('txnNum').getValue()							
				data['gainLoss'] = this.getField('gainLoss').getValue();
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
						layout: 'column'									
						,defaults: {
							layout: 'form'						
						}
						,items: [
							{
								width: 165
								,style: 'padding-left: 10px'
								,labelWidth: 75
								,items: [
									_fields['yearFilterCombo']
								]												
							}
							,{
								width: 200
								,items: [
									_buttons['refreshButton']
								]
							}
						]
					}				
					,_grids['lifGridDetails']
					,{
						layout: 'form'
						,style: 'position: relative; left:10px; top: -30px; width: 200px'
						,items: [
							_fields['totalGainOrLossBox']
						]
					}
				]																				
			}
		)		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				 text: _translationMap['Close']	
				,handler: function(){DesktopWeb.Util.cancelScreen()}
			})						
		]			
	}
}