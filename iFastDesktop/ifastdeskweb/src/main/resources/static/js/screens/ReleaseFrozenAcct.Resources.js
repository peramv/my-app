/*********************************************************************************************
 * @file	ReleaseFrozenAcct.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for Release Frozen Account screen
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 315;
	var _layoutWidth = 560;
	
	var _buttons = {
		lookup: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Lookup']
			,handler: function(){
				_controller.doLookup(_fields['account'].getValue());
			}
		})
		,update: new DesktopWeb.Controls.ActionButton({																									
			text: _translationMap['Update']
			,style: 'position: absolute; right: 0px; bottom: 3px'
			,disabled: true
			,listeners: {
				click: function(){_controller.doUpdate()}
			}
		})	
	}
	
	// **** fields ****
	var _fields = {		
		account: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Account']
			,smartview: 'accountSearch'				
			,fields: ['displayValue', 'acctNum']						
			,valueField: 'acctNum'								
			,width: 405														
		})
		,statementDate: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['RemoveCuratorFileStatementDate']
		})
		,stopNFU: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['StopNFU']
		})
		,stopPurchase: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['StopPurchase']
			,width: 90
			,allowBlank: false
			,disabled: true			
		})
		,stopRedemption: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['StopRedemption']
			,width: 90
			,allowBlank: false
			,disabled: true
		})
		,exchangeIn: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['StopExchIn']
			,width: 90
			,allowBlank: false
			,disabled: true
		})
		,exchangeOut: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['StopExchOut']
			,width: 90
			,allowBlank: false
			,disabled: true
		})
		,reactivePAC: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ReactivePACSWP']
			,width: 90
			,allowBlank: false
			,disabled: true
		})

	}
	
	// **** grids ****
	var _grids = {
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
		
		,buttons: _buttons
		
		,layout: new Ext.Container({
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
							width: 490
							,labelWidth: 70
							,items: [
								_fields['account']
							]
						}
						,{
							width: 60
							,items: [
								_buttons['lookup']
							]
						}
					]
				}
				,{
					xtype: 'fieldset'
					,id: 'accountFieldSet'
					,labelWidth: 215
					,disabled: true
					,width: 370
					,height: 265
					,title: _translationMap['AccountProperties']
					,style: 'margin-top: 10px; margin-left: 90px; padding-left:15px;'
					,items: [
						_fields['statementDate']
						,_fields['stopNFU']
						,_fields['stopPurchase']
						,_fields['stopRedemption']
						,_fields['exchangeOut']
						,_fields['exchangeIn']
						,_fields['reactivePAC']
						,_buttons['update']						
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