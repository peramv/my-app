/*********************************************************************************************
 * @file	RESPNotional.Resources.js		
 * @author	Rod Walker
 * @desc	Resources JS file for RESP Notional Info screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  30 Apr 2014 G. Thawornwachirakun P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *  30 May 2014 Narin Suanlamyai P0220132 FN03 DFT0034351 T55198
 *					- Disable SAGES fields for non-SAGES environment
 *
 *  08 Feb 2018 Narin Suanlamyai P0263049 DFT0081186
 *					- Correct stylesheet to enable scrollbar function
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 525;
	var _layoutWidth = 700;
	
	// **** buttons ****
	var _buttons = {
		refreshBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Refresh']
			,disabled: true
			,listeners: {
				click: function(){_controller.doRefresh()}
			}																											 																		
		})		
	}
	
	// **** fields ****
	var _fields = {
		period: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Period']
			,width: 125
			,disabled: true
		})
		,periodRadio: new DesktopWeb.Controls.Radio({
			name: 'filter'
			,listeners: {
				check: function(){_controller.toggleFilterFields()}
			}			
			,disabled: true
		})
		,asOfDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['AsOf']
			,width: 100
			,disabled: true
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,asOfRadio: new DesktopWeb.Controls.Radio({
			name: 'filter'
			,style: 'margin-top: 8px;'
			,listeners: {
				check: function(){_controller.toggleFilterFields()}
			}			
			,disabled: true
		})
		,marketValue: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['MarketValue']
		})				
	}
	
	// **** grids ****
	var _grids = {
		infoLevel: new DesktopWeb.AdvancedControls.GridPanel({
			width: 270			
			,autoScroll: true
			,height: 50
			,hideHeaders: true
			,autoExpandColumn: 'infoLevel'		
			,store: new Ext.data.XmlStore({
				record: 'Element'
				,fields: ['code', 'value']				
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					beforerowselect: function(){
						_grids['infoLevel'].previousRow = _grids['infoLevel'].getSelectedRecord();
					}
					,rowselect: function(){						
						_controller.updatePeriodFilter();
						if (_grids['infoLevel'].previousRow)
						{							
							// don't call refresh on the initial selection
							_controller.doRefresh();					
						}
					}					
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				columns: [
					{id: 'infoLevel', dataIndex: 'value'}
				]
			})			
		})		
	}
	
	// **** popups ****
	var _popups = {
		history: new DesktopWeb.AdvancedControls.HistoryPopup()					
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight

		,buttons: _buttons
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				{						
					layout: 'column'																																					
					,items: [
						{
							layout: 'column'
							,width: 400
							,items: [
								{
									layout: 'form'
									,width: 110
									,labelWidth: 110
									,items: [new DesktopWeb.Controls.Label({fieldLabel: _translationMap['InformationLevel']})]
								}								
								,_grids['infoLevel']
							]						
						}						
						,{
							layout: 'column'
							,width: 300
							,items: [
								{
									layout: 'form'
									,width: 25									
									,items: [_fields['periodRadio'], _fields['asOfRadio']]
								}		
								,{
									layout: 'form'
									,width: 210
									,labelWidth: 50
									,items: [_fields['period'], _fields['asOfDate']]
								}
								,{
									layout: 'form'
									,width: 60									
									,items: [_buttons['refreshBtn']]								
								}																	
							]						
						}						
					]												
				}
				,{
					layout: 'form'
					,style: 'padding-top: 10px; padding-left: 15px;'
					,items: [
						_fields['marketValue']
					]
				}
				,new DesktopWeb.AdvancedControls.GridPanel({																																						
					height: 24																		
					,enableHdMenu: false
					,enableColumnMove: false											
					,store: new Ext.data.XmlStore({
						record: 'PossibleMatch'					
						,fields: []				
					})							
					,columns: [																																															
						{header: "", width: 255, resizable: false, fixed: true}
						,{header: _translationMap["Purchase"], width: 105, resizable: false, fixed: true}
						,{header: _translationMap["Redemption"], width: 105, resizable: false, fixed: true}
						,{header: _translationMap["Repayments"], width: 105, resizable: false, fixed: true}
						,{header: _translationMap["Balance"], width: 105, resizable: false, fixed: true}				
					]											
				})
				,new Ext.Container({
					id: 'notional-details'					
					,height: 400
					,style: 'position:relative;overflow-y:scroll'																					
					,items: [
						{
							xtype: 'fieldset'
							,hidden: true
							,id: 'contributionAndIncome'							
							,title: _translationMap['ContributionAndIncome']							
							,items: [								
							]
						}
						,{
							xtype: 'fieldset'
							,id: 'sagesContributionFS'
							,hidden: true
							,title: _translationMap['sagesContributionFS']
							,items: [
							]
						}
						,{
							xtype: 'fieldset'
							,id: 'grants'
							,hidden: true							
							,title: _translationMap['Grants']							
							,items: [								
							]
						}
						,{
							xtype: 'fieldset'
							,id: 'qesi'
							,hidden: true
							,title: _translationMap['QESIContribution']													
							,items: [								
							]
						}
					]
				})					
																			
			]																				
		})		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				text: 'Historical'
				,handler: function(){
					_controller.openHistoricalPopup();
				}				
			})			
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					DesktopWeb.Util.commitScreen()						
				}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){
					if (_controller.updatesFlag)
					{
						DesktopWeb.Util.displayDiscardPrompt(callback)
					}
					else
					{
						callback(true);
					}
					
					function callback(discard)
					{
						if (discard)
						{				
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			})
		]			
	}
}

DesktopWeb.ScreenResources.DataRow = Ext.extend( Ext.Panel, {	
	initComponent: function(){		
		this.addEvents({'edit' : true});
		
		var labelWidth = 241
		var columnWidth = 101		
				
		this.purchaseFld = null;
		var purchaseVal = this.initialConfig.purchase.value.replace(/\,/g, '');
		if (isNaN(purchaseVal) || this.initialConfig.staticRow)
		{
			this.purchaseFld = new DesktopWeb.Controls.Label({
				width: columnWidth
				,style: 'padding-left:10px; padding-top:2px;'
				,id: this.initialConfig.purchase.id
				,text: this.initialConfig.purchase.value				 		
			})
		}
		else
		{
			this.purchaseFld = new DesktopWeb.Controls.NumberField({
				width: columnWidth
				,value: this.initialConfig.purchase.value
				,disabled: !this.initialConfig.allowEdit
				,allowNegative: true
				,id: this.initialConfig.purchase.id				 					
			})
		}
		this.purchaseFld.addListener('change', this.onEdit, this);		
		
		this.redemptionFld = null;
		var redemptionVal = this.initialConfig.redemption.value.replace(/\,/g, '');
		if (isNaN(redemptionVal) || this.initialConfig.staticRow)
		{
			this.redemptionFld = new DesktopWeb.Controls.Label({
				width: columnWidth
				,style: 'padding-left:10px; padding-top:2px;'
				,text: this.initialConfig.redemption.value
				,id: this.initialConfig.redemption.id 		
			})
		}
		else
		{
			this.redemptionFld = new DesktopWeb.Controls.NumberField({
				width: columnWidth
				,value: this.initialConfig.redemption.value
				,disabled: !this.initialConfig.allowEdit
				,allowNegative: true
				,id: this.initialConfig.redemption.id
			})
		}
		this.redemptionFld.addListener('change', this.onEdit, this);
		
		this.repaymentsFld = null;
		var repaymentsVal = this.initialConfig.repayments.value.replace(/\,/g, '');
		if (isNaN(repaymentsVal) || this.initialConfig.staticRow)
		{
			this.repaymentsFld = new DesktopWeb.Controls.Label({
				width: columnWidth
				,style: 'padding-left:10px; padding-top:2px;'
				,text: this.initialConfig.repayments.value
				,id: this.initialConfig.repayments.id 			
			})
		}
		else
		{
			this.repaymentsFld = new DesktopWeb.Controls.NumberField({
				width: columnWidth
				,value: this.initialConfig.repayments.value 			
				,disabled: !this.initialConfig.allowEdit
				,allowNegative: true
				,id: this.initialConfig.repayments.id				
			})
		}
		this.repaymentsFld.addListener('change', this.onEdit, this);
		
		
		this.balanceFld = new DesktopWeb.Controls.Label({
			width: columnWidth
			,style: 'padding-left:10px; padding-top:2px;'
			,text: this.initialConfig.balance.value
			,id: this.initialConfig.balance.id 			
		})
		
		//need at least one non-label field, so this is in case whole row is to be static
		this.hiddenFld = new DesktopWeb.Controls.TextField({
			hidden: true
		})
						
		var config = {
			id: this.initialConfig.id
			,layout: 'form'
			,labelWidth: labelWidth
			,height: 30
			,items: [
				{
					xtype: 'compositefield'
					,labelStyle: 'overflow:hidden; text-overflow: ellipsis; white-space:nowrap'
					,fieldLabel: this.initialConfig.rowLabel
					,items: [
						this.purchaseFld, this.redemptionFld, this.repaymentsFld, this.balanceFld, this.hiddenFld
					]
				}
			]			
		}

		Ext.apply(this, Ext.apply(this.initialConfig, config));							
		DesktopWeb.ScreenResources.DataRow.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.ScreenResources.DataRow.superclass.onRender.call(this, ct, position);		
	}
	
	,onEdit: function(fld, newValue)
	{
		if (newValue == "")
		{
			fld.setValue("0.00");
		}
	
		if (!isNaN(this.balanceFld.getValue()))
		{	
			this.updateBalance();
		}
		//Changes for Incident 2867256 
		//DesktopWeb.ScreenController.updatesFlag = true;
		DesktopWeb._SCREEN_CONTROLLER.updatesFlag = true;
		
		this.fireEvent('edit', this);
	}
	
	,updateBalance: function()
	{
		var pur = (!isNaN(this.purchaseFld.getValue()) ? this.purchaseFld.getValue() : 0);
		var red = (!isNaN(this.redemptionFld.getValue()) ? this.redemptionFld.getValue() : 0);
		var rpy = (!isNaN(this.repaymentsFld.getValue()) ? this.repaymentsFld.getValue() : 0);
		
		this.balanceFld.setValue((pur - red - rpy).toFixed(2));
	}
	
	,getData: function()
	{
		var data = {};
		data[this.purchaseFld.id] = this.purchaseFld.getValue();
		data[this.redemptionFld.id] = this.redemptionFld.getValue();
		data[this.repaymentsFld.id] = this.repaymentsFld.getValue();
		data[this.balanceFld.id] = this.balanceFld.getValue();
		
		return data;
	}
	
	,disable: function()
	{
		this.purchaseFld.disable();
		this.redemptionFld.disable();
		this.repaymentsFld.disable();
		this.balanceFld.disable();
		this.superclass().disable.call(this);
	}
});