/*********************************************************************************************
 * @file	RemitUnclmAcct.Resources.js
 * @author	Kittichai Sopitwetmontree
 * @desc	Resources JS file for Remittance Unclaimed Property Account
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();	
	// content dimensions
	var _layoutHeight = 200;
	var _layoutWidth = 500;
	
	// **** fields ****
	var _fields = {	
		txtSearchAccount: new DesktopWeb.Controls.TextField
		(
			{
				fieldLabel: _translationMap['Account']	
				, width: 300											
			}
		)
		, suggestAccount: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Account']
			,smartview: 'accountSearch'				
			,fields: ['displayValue', 'acctNum']						
			,valueField: 'acctNum'								
			,width: 300														
		})		
		, lblName: new DesktopWeb.Controls.Label
		(
			{
				text: _translationMap['Name']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'			
				, height: 20
			}
		)
		, valName: new DesktopWeb.Controls.Label
		(
			{
				text: ''
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'				
				, height: 20
			}
		)		
		, lblSIN: new DesktopWeb.Controls.Label
		(
			{
				text: _translationMap['SIN']	
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'				
				, height: 20										
			}
		)		
		, valSIN: new DesktopWeb.Controls.Label
		(
			{
				text: ''
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'				
				, height: 20											
			}
		)
		, lblTaxType: new DesktopWeb.Controls.Label
		(
			{
				text: _translationMap['TaxType']	
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'				
				, height: 20												
			}
		)
		, valTaxType: new DesktopWeb.Controls.Label
		(
			{
				text: ''	
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'				
				, height: 20											
			}
		)		
		, lblRemittanceDate: new DesktopWeb.Controls.Label
		(
			{
				text: _translationMap['PendingTradeExist']	
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'				
				, height: 20												
			}
		)
		, valRemittanceDate: new DesktopWeb.Controls.Label
		(
			{
				text: ''
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'				
				, height: 20												
			}
		)	
		, cboPayType: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['PayType']
				, width: 200	
				, editable: false
				, lastQuery: ''
				, listeners:{ 				
					
				}
			}
		)		

	}
	
	// **** buttons ****
	var _buttons = {
		cmdSearch: new DesktopWeb.Controls.ActionButton
		(
			{
				text: _translationMap['BtnSearch']
				, handler: function() {_controller.doSearch(false);}						
			}
		)
		, cmdRemitUnclmSubmit: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnOk']
				, handler: function(){
					if (_popups['frmRemitUnclmAcct'].isValid())
					{			
						DesktopWeb.Util.commitScreen();
					}
				}
			}
		)
		, cmdRemitUnclmCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnCancel']
				, handler: function(){
					if (_popups['frmRemitUnclmAcct'].isValid())
					{
						_popups['frmRemitUnclmAcct'].hide();
					}
				}
			}
		)
		, cmdScreenButtonSubmit: new DesktopWeb.Controls.ScreenButton(
			{
				text: _translationMap['BtnSubmit']
				 , handler: function(){
					_controller.doPreUpdate();
				}
			}
		)		
		
	}
	
	// **** grids ****
	var _grids = {

	}
	
	// **** popups ****
	var _popups = {	
		frmRemitUnclmAcct: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,title: _translationMap['PendingTradeExistTitle']
				,width: 380
				,height: 150
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
				    {
						html: _translationMap['Confirmation']
						, style: 'text-align:center'		
						, defaults: {border:false}						
					}
					,{
						layout: 'form'
						, defaults: {border: false, labelWidth:50}
						, items: [
							{
								layout: 'column'								
								, style: 'padding:4px'
								, defaults: {border: false}
								,items: [ 
									{
										width: 380
										, layout: 'form'
										, labelWidth: 380
										, defaults: {border: false}										
										, items: [ 
											_fields['lblRemittanceDate'] 
											
										]
									}
								]
							}
														
						]
						
					}
				]
				,buttons: [
					_buttons['cmdRemitUnclmSubmit']
					, _buttons['cmdRemitUnclmCancel']				
				]

			}		
		)
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,popups: _popups
		
		,buttons: _buttons
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,layout: 'form'
				,defaults: {labelWidth: 80}	
				//,style: "align:center;"
				,items: [
					{
						layout: 'column'
						,style: "margin-bottom:10px;"						
						,items: [
							{
								layout: 'form'
								, width: 400
								, items: [
									_fields['suggestAccount']												
								]
							}
							, {
								layout: 'form'
								//, width: 200
								, items: [
									_buttons['cmdSearch']						
								]
							}
						]
					} 
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								layout: 'form'								
								, width: 90
								, items: [
									_fields['lblName']												
								]
							}
							, {
								layout: 'form'
								, items: [									
									_fields['valName']						
								]
							}
						]
						
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								layout: 'form'								
								, width: 90
								, items: [
									_fields['lblSIN']												
								]
							}
							, {
								layout: 'form'
								, items: [									
									_fields['valSIN']						
								]
							}
						]
						
					}
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,items: [
							{
								layout: 'form'								
								, width: 90
								, items: [
									_fields['lblTaxType']												
								]
							}
							, {
								layout: 'form'
								, items: [									
									_fields['valTaxType']						
								]
							}
						]
						
					}
					, {
						layout: 'form'
						,style: "margin-bottom:10px;"
						,items: [
							{
								layout: 'form'								
								, items: [
									_fields['cboPayType']												
								]
							}

						]
						
					}

				]			
			}
		)
		,screenButtons: [	
						
			_buttons['cmdScreenButtonSubmit']
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'Cancel'
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]
	}
}