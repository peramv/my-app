/*********************************************************************************************
 * @file	DilutionCalculator.Resources.js
 * @author	
 * @desc	Resources JS file for DilutionCalculator screen
 *********************************************************************************************/

 /*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *      - Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 455;
	var _layoutWidth = 580;
		
	// **** fields ****
	var _fields = {
		account: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Account']
			,smartview: 'accountSearch'				
			,fields: ['displayValue', 'acctNum']
			,valueField: 'acctNum'								
			,width: 437				
			,allowBlank: false
		})
		,fund: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Fund']
			,smartview: 'fundClassSearch'				
			,fields: ['fndClsDisp', 'fundCode', 'classCode']						
			,valueField: 'fndClsDisp'
			,displayField: 'fndClsDisp'								
			,width: 437
			,allowBlank: false
			,listeners: {
				select : function(fld, rec, index)  {
					_controller.selectFund(fld, rec, index);
				}
			}
		})
		,transType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['TransactionType']
			,width: 150
			,allowBlank: false			
		})
		,transNum: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['TransactionNum']
			,width: 125
		})
		,grossAmt: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['GrossAmount']
			,allowNegative: true
			,width: 100
			,allowBlank: false
		})
		,tradeDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['TradeDate']
			,width: 100
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,calcDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['CalculationDate']
			,width: 100
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,totalGrossAmt: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TotGrossAmt']
			,width: 100
		})
		,befDistribtion: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['BefDistribution']
			,width: 100			
		})
		,distDilution: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['DistDilution']
			,width: 100
			,disabled: true
			,allowNegative: true
			,enableKeyEvents: true
			,listeners: {
				keyup: function(fld){
					if (!isNaN(fld.getValue()))
					{
						_controller.calcTotal();
					}
				}
			}
		})
		,totalDilution: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TotDilution']
			,width: 100			
		})
	}
	
	// **** grids ****
	var _grids = {
		transactions: new DesktopWeb.AdvancedControls.GridPanel({										
			autoScroll: true
			,height: 160
			,width: 570
			,store: new Ext.data.XmlStore({
				record: 'DilutionDetails'					
				,fields: ['acct',
						  'fund',
						  'class',
						  'transType',
						  'transNum',
						  'tradeGrossAmt',
						  'units',
						  'tradeDate',
						  'tdRate',
						  'calcDate',
						  'calcRate',
						  'gainLoss',
						  'calcRateAvail']
				,listeners: {
					load: function(store, records){
						Ext.each(records, function(record){
							record.data['tradeDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['tradeDate']);
							record.data['calcDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['calcDate']);
						});
						store.fireEvent('datachanged', store);
						_controller.updateTransactionButtons();
					}
				}						
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['Account'], dataIndex:'acct', width:70}
					,{header: _translationMap['FundClass'], renderer: function(val, meta, record){return record.data['fund'] + "/" + record.data['class']}, width:80}
					,{header: _translationMap['TransType'], renderer: function(val, meta, record){return _controller.getElementDescription(record.data['transType'])}, width:80}							
					,{header: _translationMap['TransNum'], dataIndex: 'transNum', width:80}
					,{header: _translationMap['GrossAmt'], dataIndex: 'tradeGrossAmt', width:80}
					,{header: _translationMap['Units'], dataIndex: 'units', width:80}
					,{header: _translationMap['TradeDate'], dataIndex: 'tradeDate', width:80}
					,{header: _translationMap['TradeRate'], dataIndex: 'tdRate', width:80}
					,{header: _translationMap['CalcDate'], dataIndex: 'calcDate', width:80}
					,{header: _translationMap['CalcRate'], dataIndex: 'calcRate', width:80}
					,{header: _translationMap['GainLoss'], dataIndex: 'gainLoss', width:80}
				]							
			})
			,selModel: new Ext.grid.RowSelectionModel({				
				listeners: {
					rowselect: function(){
						_controller.updateTransactionButtons()							
					}
					,rowdeselect: function(){
						_controller.updateTransactionButtons()
					}
				}
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'calcBtn'								
					,text: _translationMap['CalculateDilution']
					,disabled: true
					,handler: function(){_controller.calculateDilution();}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'removeBtn'
					,text: _translationMap['Remove']
					,disabled: true
					,handler: function(){_controller.remove();}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'clearAllBtn'
					,text: _translationMap['ClearAll']
					,disabled: true
					,handler: function(){_controller.clearAll();}							
				})									
			]			
		})
	}
	
	// **** popups ****
	var _popups = {					
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				{
					layout: 'form'
					,labelWidth: 110
					,items: [
						_fields['account']
						,_fields['fund']
					]
				}
				,{
					layout: 'column'
					,labelWidth: 110
					,defaults: {
						layout: 'form'
					}
					,items: [
						{
							columnWidth: 0.5
							,items: [
								_fields['transType']
								,_fields['tradeDate']								
								,_fields['grossAmt']
							]
						}
						,{
							columnWidth: 0.5
							,items: [
								_fields['transNum']								
								,_fields['calcDate']
							]
						}
					]
				}
				,{
					height: 30					
					,items: [					
						new DesktopWeb.Controls.ActionButton({																						
							style: 'position: absolute; right: 75px'
							,text: _translationMap['AddTransactions']
							,handler: function(){								
								_controller.addTransactions();
							}
						})
						,new DesktopWeb.Controls.ActionButton({																						
							style: 'position: absolute; right: 10px'
							,text: _translationMap['Reset']
							,handler: function(){
								_controller.resetForm();
							}
						})
						
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['Transactions']					
					,items:[
						_grids['transactions']						
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['Totals']					
					,items:[
						{
							layout: 'column'
							,style: 'padding-left: 10px;'													
							,items: [
								{
									layout: 'form'
									,width: 275 
									,labelWidth: 165
									,items: [
										_fields['totalGrossAmt']
										,_fields['befDistribtion']
									]
								}
								,{
									layout: 'form'
									,width: 260
									,labelWidth: 115
									,items: [
										_fields['distDilution']
										,_fields['totalDilution']
									]									
								}								
							]
						}
					]
				}							
			]
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Close']
				,handler: function(){DesktopWeb.Util.cancelScreen()}
			})
		]			
	}
}