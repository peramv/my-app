/*********************************************************************************************
 * @file	PDFViewer.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for SmartPDF Viewer screen
 *********************************************************************************************
 *  History :
 *
 *  30 Sept 2014 Narin Suanlamyai P0222874 FN00 T55886
 *					- Initialize
 *
 *  28 Oct 2014 Narin Suanlamyai P0222874 FN00 DFT0043279 T55887
 *					- Adjust Layout base-on French
 *
 *  07 Nov 2014 Rod Walker P0222874 FN00 DFT0043554 T55997
 *					- Update Fax via AWD function
 *
 *  24 Nov 2014 Rod Walker P0222874 FN00 DFT0044823 T56125
 *					- Mandatory Fax Input
 *
 *  29 Apr 2015 Aurkarn Mongkonrat P0241174 T80744
 *					- Add Email via AWD functionality.
 *
 *  29 Apr 2015 Aurkarn Mongkonrat P0241174 T80954 DFT0051572 DFT0051575 DFT0051577 DFT0051578
 *					- The Fax Number field should be a number only field but is taking alphabets.
 *                  - The error message is hidden in the Fax via AWD screen.
 *                  - The Send button remains disabled.
 *
 *  21 Aug 2015 Narin Suanlamyai P0241174 T81250 DFT0052808
 *                  - Allow these special characters ('&', '/', '.', '-') for Recipient Name fields.
 *                  - Escape ampersand (&) before request AWD
 *
 *  24 Sept 2018 Sreejith.A CHG0055141
 *					- “use iFast contact info” check box will be disabled and no default information will be populated on screen. 
 *
 *********************************************************************************************/
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    var _rexRecipientNameFormat = /^[A-Za-z -.&\/]+$/;
    var _rexFaxNumberFormat1    = /^[0-9]{3}-{0,1}[0-9]{3}-{0,1}[0-9]{4}$/;
    var _rexFaxNumberFormat2    = /^[0-9]{1}-{0,1}[0-9]{3}-{0,1}[0-9]{3}-{0,1}[0-9]{4}$/;
    var _rexEmailFormat         = /^([\w-]+(?:\.[\w-]+)*)@((?:[\w-]+\.)*\w[\w-]{0,66})\.([a-z]{2,6}(?:\.[a-z]{2})?)$/i;

	// content dimensions
	var _layoutHeight = 450;
	var _layoutWidth = 650;

	// **** buttons ****
	var _buttons = {
		backBtn: new DesktopWeb.Controls.ScreenButton({
			text: _translationMap['ReturnToTaxSlips']
			,handler: function(){
				_controller.returnToTaxSlips();
			}
		})
		,closeBtn: new DesktopWeb.Controls.ScreenButton({
			text: _translationMap['Close']
			,handler: function(){
				DesktopWeb.Util.cancelScreen();
			}
		})
		,fax: {
			faxBtn: new DesktopWeb.Controls.ActionButton({
				text: _translationMap["Fax"]
				,disabled: true
				,listeners: {
					click: function(){
						_controller.showFaxPrompt();
						_controller.hideEmailPrompt();
						
						_buttons['fax']['faxBtn'].disable();
						_buttons['email']['emailBtn'].enable();
					}
				}
			})
			,sendBtn: new DesktopWeb.Controls.ActionButton({
				text: _translationMap["Send"]
				,style: "margin-bottom: 6px;"
				,handler: function(){
					_controller.sendAWDRequest('fax');
				}
			})
			,cancelBtn: new DesktopWeb.Controls.ActionButton({
				text: _translationMap["Cancel"]
				,handler: function(){
					_controller.hideFaxPrompt();
					
					_buttons['fax']['faxBtn'].enable();
				}
			})
		}
		,email: {
			emailBtn: new DesktopWeb.Controls.ActionButton({
				text: _translationMap["EmailBtn"]
				,disabled: true
				,listeners: {
					click: function(){
						_controller.hideFaxPrompt();
						_controller.showEmailPrompt();
					
						_buttons['fax']['faxBtn'].enable();
						_buttons['email']['emailBtn'].disable();
					}
				}
			})
			,sendBtn: new DesktopWeb.Controls.ActionButton({
				text: _translationMap["Send"]
				,style: "margin-bottom: 6px;"
				,handler: function(){
					_controller.sendAWDRequest('email');
				}
			})
			,cancelBtn: new DesktopWeb.Controls.ActionButton({
				text: _translationMap["Cancel"]
				,handler: function(){
					_controller.hideEmailPrompt();
					
					_buttons['email']['emailBtn'].enable();
				}
			})
		}
	}

	// **** fields ****
	var _fields = {
		fax: {
			ifastContact: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['iFASTContact']
				,checked: false
				,disabled: true
				,listeners: {
					check: function() {
						if (_fields.fax.ifastContact.getValue()) {
							_controller.setContactData();
                            _controller.updateFaxSendBtn();
						} else {
							_controller.enableFaxInputs();
						}
					}
				}
			})
			,firstName: new DesktopWeb.Controls.TextField({
				width: 95
				,fieldLabel: _translationMap['RecipName']
				,allowBlank: false
				,listeners: {
					change: function() {
						_controller.updateFaxSendBtn();
					}
				}
                ,validator: function(value){ //Allow only space and alphabets
					var regxNameFormat = _rexRecipientNameFormat;
					return regxNameFormat.test(value);
				}
			})
			,lastName: new DesktopWeb.Controls.TextField({
				width: 95
				,hideLabel: true
				,allowBlank: false
				,listeners: {
					change: function() {
						_controller.updateFaxSendBtn();
					}
				}
                ,validator: function(value){ //Allow only space and alphabets
					var regxNameFormat = _rexRecipientNameFormat;
					return regxNameFormat.test(value);
				}
			})
			,faxNum: new DesktopWeb.Controls.TextField({
				width: 95
				,fieldLabel: _translationMap["FaxNum"]
				,allowBlank: false
				,listeners: {
					change: function(obj, newVal, oldVal) {
                        newVal = newVal.replace(/-/g, '');
                    
                        if (this.validator(newVal)) {
                            if (newVal.length == 10) // XXX-XXX-XXXX
                                newVal = newVal.substr(0, 3) + '-' + newVal.substr(3, 3) + '-' + newVal.substr(6, 4);
                            else if (newVal.length == 11) // X-XXX-XXX-XXXX
                                newVal = newVal.substr(0, 1) + '-' + newVal.substr(1, 3) + '-' + newVal.substr(4, 3) + '-' + newVal.substr(7, 4);
                                
                            this.setValue(newVal);
                        }
						_controller.updateFaxSendBtn();
					}
				}
                ,validator: function(value){           
                    // 10 digits
					var regxFaxFormat = _rexFaxNumberFormat1;
					var correctFormat = regxFaxFormat.test(value);
                    
                    // 11 digits
                    regxFaxFormat = _rexFaxNumberFormat2;
                    correctFormat = correctFormat || regxFaxFormat.test(value);
                    
                    return correctFormat;
				}
			})
		}
		,email: {
			ifastContact: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['iFASTContact']
				,checked: false
				,disabled: true
				,listeners: {
					check: function() {
						if (_fields.email.ifastContact.getValue()) {
							_controller.setContactData();
                            _controller.updateEmailSendBtn();
						} else {
							_controller.enableEmailInputs();
						}
					}
				}
			})
			,firstName: new DesktopWeb.Controls.TextField({
				width: 95
				,fieldLabel: _translationMap['RecipName']
				,allowBlank: false
				,listeners: {
					change: function() {
						_controller.updateEmailSendBtn();
					}
				}
                ,validator: function(value){ //Allow only space and alphabets
					var regxNameFormat = _rexRecipientNameFormat;
					return regxNameFormat.test(value);
				}
			})
			,lastName: new DesktopWeb.Controls.TextField({
				width: 95
				,hideLabel: true
				,allowBlank: false
				,listeners: {
					change: function() {
						_controller.updateEmailSendBtn();
					}
				}
                ,validator: function(value){ //Allow only space and alphabets
					var regxNameFormat = _rexRecipientNameFormat;
					return regxNameFormat.test(value);
				}
			})
			,emailAddr: new DesktopWeb.Controls.TextField({
				width: 212
				,fieldLabel: _translationMap["EmailAddr"]
				,allowBlank: false
				,listeners: {
					change: function() {
						_controller.updateEmailSendBtn();
					}
				}
				,validator: function(value){
					var regxEmailFormat = _rexEmailFormat;
					return regxEmailFormat.test(value);
				}
			})
		}
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

		//,forms: _forms

		,buttons: _buttons

		,fields: _fields

		,grids: _grids

		,popups: _popups

		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				{
					defaults: {
						labelWidth: 80
					}
					,items: [
						{
							layout: 'form'
							,id: 'mainPDFPanel'
							,border: true
							,tbar: {
								buttons:[
									'->'
									,_buttons['email']['emailBtn']
									,_buttons['fax']['faxBtn']
								]
							}
							,items: [
								{
									layout: 'column'
									,id: "faxPrompt"
									,style: 'display:none; padding:10px 0 0 10px; border-left:1px solid #D0D0D0; border-right:1px solid #D0D0D0'
									,items: [
										{
											layout: 'form'
											,labelWidth: 85
											,width: 185
											,items: [
												_fields['fax']['ifastContact']
											]
										}
										,{
											layout: 'form'
											,labelWidth: 125
											,width: 370
											,items: [
												{
													layout: 'column'
													,width: 365
													,items: [
														{
															layout: "form"
															,width: 250
															,items: [
																_fields['fax']['firstName']
															]
														}
														,{
															layout: "form"
															,labelWidth: 1
															,width: 115
															,items: [
																_fields['fax']['lastName']
															]
														}

													]
												}
												,_fields['fax']['faxNum']
											]
										}
										,{
											layout: 'form'
											,labelWidth: 60
											,width: 75
											,items: [
												_buttons['fax']['sendBtn'],
												_buttons['fax']['cancelBtn']
											]
										}
									]
								}
								,{
									layout: 'column'
									,id: "emailPrompt"
									,style: 'display:none; padding:10px 0 0 10px; border-left:1px solid #D0D0D0; border-right:1px solid #D0D0D0'
									,items: [
										{
											layout: 'form'
											,labelWidth: 85
											,width: 185
											,items: [
												_fields['email']['ifastContact']
											]
										}
										,{
											layout: 'form'
											,labelWidth: 125
											,width: 370
											,items: [
												{
													layout: 'column'
													,width: 365
													,items: [
														{
															layout: "form"
															,width: 250
															,items: [
																_fields['email']['firstName']
															]
														}
														,{
															layout: "form"
															,labelWidth: 1
															,width: 115
															,items: [
																_fields['email']['lastName']
															]
														}

													]
												}
												,_fields['email']['emailAddr']
											]
										}
										,{
											layout: 'form'
											,labelWidth: 60
											,width: 75
											,items: [
												_buttons['email']['sendBtn'],
												_buttons['email']['cancelBtn']
											]
										}
									]
								}
                                ,{}
                                ,{}
								,{
									xtype : "component",
									autoEl : {
										tag : "iframe"
										,name : "pdfFrame"
										,id: "pdfFrame"
										,style: "width:650px; height:415px"
									}
								}

							]
						}
					]
				}
			]
		})

		,screenButtons: [
			_buttons['backBtn']
			,_buttons['closeBtn']
		]
	}
}