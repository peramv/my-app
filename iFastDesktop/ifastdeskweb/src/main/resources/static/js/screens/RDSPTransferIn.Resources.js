/*******************************************************************************
 * @file RDSPTransferIn.Resources.js
 * @author Usha S
 * @desc Resources JS file for Transfer In.
 ******************************************************************************/
DesktopWeb.ScreenResources = function(ctrlr) {
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _layoutHeight = 672;
	var _layoutWidth = 750;
	var _childLayoutHeight = 115;
	var _labelWidth = 180;
	

	DesktopWeb.Controls.AmountTextField = Ext.extend(DesktopWeb.Controls.TextField, {
		style : 'padding-left:5px;text-align:right;',
		regex : /^-?\d*[,\d*]+(\.\d{1,2})?$/ , 
		regexText: _translationMap['InvalidAmountFormat'],
		width : 100,
		style : 'padding-left:5px;text-align:right;',
        listeners: {
	        		change: function(object, v, oldValue){
	        			if (v && v.indexOf && v.indexOf(',') != -1)
	        			{	
	        				v = v.replace(/,/g, ''); 
	        			}	
	        			if(isNaN(v)) {
	        				if(!_buttons['okScreenButton'].disabled) {
	        					_buttons['okScreenButton'].disable();
	        				}
	        			}
	        			else {
	        				var amountFormat = '0,000';
	        				if(v.indexOf('.') == -1) {
	        					object.setValue(Ext.util.Format.number(v, amountFormat));
	        				}
	        				else {
	        					var splitAmount = v.split(".");	        				
	        					object.setValue(Ext.util.Format.number(splitAmount[0], amountFormat) + "." + splitAmount[1]);
	        				}
	        				if(_controller.fieldsUpdated() && !_controller.inValidData()) {
	        					_buttons['okScreenButton'].enable();
	        				} else {
	        					_buttons['okScreenButton'].disable();
	        				}
	        			 }
	        		}
				,blur: function(object) {
					var val = object.getValue();
					if(val && val.indexOf && val.indexOf('-') != -1) {
        				_buttons['okScreenButton'].disable();
        				errMsg = _translationMap['InvalidAmountFormat'];
        				object.markInvalid(errMsg);
        				object.isMarkInvalid = true;
        			}
				}
        	}
	});
	
	// **** fields ****
	var _fields = {
			rdspTransfer: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['RDSPTransfer'],
				width : 150
			}),
		extRDSPContNum : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['ExtRDSPContNum'],
			style : 'padding-left:5px;',
			allowBlank : false,
			width : 100,
			validator : function(value){
				return _controller.mandatoryFieldCheck(value);
		    },
			listeners: {
				change: function(object, newValue, oldValue){
					if(_controller.fieldsUpdated() && !_controller.inValidData())
						_buttons['okScreenButton'].enable();
					else
						_buttons['okScreenButton'].disable();
				}
			}
		}),
		extSpecimenPlanNum : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['ExtSpecimenPlanNum'],
			style : 'padding-left:5px;',
			allowBlank : false,
			width : 100,
			validator : function(value){
				return _controller.mandatoryFieldCheck(value);
		    },
			listeners: {
				change: function(object, newValue, oldValue){
					if(_controller.fieldsUpdated() && !_controller.inValidData())
						_buttons['okScreenButton'].enable();
					else
						_buttons['okScreenButton'].disable();
				}
			}
		}),
		internalRDSPContNum : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['InternalRDSPContNum'],
			style : 'padding-left:5px;',
			disabled: true,
			width : 100
		}),
		internalSpecimenPlanNum : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['InternalSpecimenPlanNum'],
			style : 'padding-left:5px;',
			disabled: true,
			width : 100
		}),

		nonTaxablePrivateCntbns : new DesktopWeb.Controls.AmountTextField({
			fieldLabel : _translationMap['NonTaxablePrivateCntbns']
		}),
		canadaDisabilitySavingsGrant : new DesktopWeb.Controls.AmountTextField({
			fieldLabel : _translationMap['CanadaDisabilitySavingsGrant']
		}),
		taxableReportsRollovers : new DesktopWeb.Controls.AmountTextField({
			fieldLabel : _translationMap['TaxableReportsRollovers']
		}),
		canadaDisabilitySavingsBond : new DesktopWeb.Controls.AmountTextField({
			fieldLabel : _translationMap['CanadaDisabilitySavingsBond']
		}),

		fairMarketValue : new DesktopWeb.Controls.AmountTextField({
			fieldLabel : _translationMap['FairMarketValue']
		}),
		grantBondsPaid : new DesktopWeb.Controls.AmountTextField({
			fieldLabel : _translationMap['GrantBondsPaid']
		}),
		contributions : new DesktopWeb.Controls.AmountTextField({
			fieldLabel : _translationMap['Contributions']
		}),

		dapLdapPriorToCurrentYear : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['DapLdapPriorToCurrentYear']
		}),
		dapLdapThisYear : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['DapLdapThisYear']
		}),
		nonTaxablePortion : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['NonTaxablePortion']
		}),
		taxablePortion : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['TaxablePortion']
		}),

		nonTaxablePriorDapLdap : new DesktopWeb.Controls.AmountTextField({
			labelWidth : 0,
			id : 'NonTaxablePriorDapLdap'
		}),
		nonTaxablePresentDapLdap : new DesktopWeb.Controls.AmountTextField({
			labelWidth : 0,
			id : 'NonTaxablePresentDapLdap'
		}),
		taxablePriorDapLdap : new DesktopWeb.Controls.AmountTextField({
			labelWidth : 0,
			id : 'TaxablePriorDapLdap'
		}),
		taxablePresentDapLdap : new DesktopWeb.Controls.AmountTextField({
			labelWidth : 0,
			id : 'TaxablePresentDapLdap'
		}),
		formEditableFlag : new Ext.form.Hidden({
			itemId:'FormEditableFlag'			
		}),
		esdcSent : new Ext.form.Hidden({
			itemId:'EsdcSent'			
		}),
		esdcResponse : new Ext.form.Hidden({
			itemId:'EsdcResponse'			
		}),
		moneyOutTrade : new Ext.form.Hidden({
			itemId:'MoneyOutTrade'			
		}),
		/*transferInStatusTypeCode : new Ext.form.Hidden({
			itemId:'TransferInStatusTypeCode'			
		}),*/
		accountNumber : new Ext.form.Hidden({
			itemId:'AccountNumber'			
		}),
		transactionId : new Ext.form.Hidden({
			itemId:'TransactionId'			
		}),
		transferInStatusTypeCode : new DesktopWeb.Controls.TextField({
			fieldLabel : _translationMap['transferStatus'],
			style : 'padding-left:10px;',
			disabled: true,
			hidden : true,
			width : 100
		})
	}
	
	// **** buttons ****
	var _buttons = {
		okScreenButton :new DesktopWeb.Controls.ScreenButton(
				{
					itemId : 'okBtnScreen',
					disabled : true,
					text: _translationMap['OK'],
					handler: function(){
						if (_controller.fieldsUpdated()) {
							DesktopWeb.Util.commitScreen();
						}
					}
				}
			)
		,cancelScreenButton : new DesktopWeb.Controls.ScreenButton(
			{
				text: _translationMap['Cancel'],
			    handler: function(){
				  if(_controller.fieldsUpdated()) {
					  		DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
							function handlePromptMsg(btn){
								if(btn){
									_controller.goToScreen();
								}
							}
						}else{
						_controller.goToScreen();
					}				  
				  }
			}
		)
	}

	return {
		layoutWidth : _layoutWidth,
		layoutHeight : _layoutHeight,
		fields : _fields,
		buttons: _buttons,
		layout : new Ext.Container(
				{
					height : _layoutHeight,
					width : _layoutWidth,
					items : [ {
						layout: 'form',
						style: 'padding-left: 10px',
						items : [
							_fields['rdspTransfer'],
								{
									height : _childLayoutHeight,
									xtype : 'fieldset',
									title : _translationMap['AccountInformation'],
									items : [ {
										layout : 'column',
										labelWidth : _labelWidth,
										items : [
												{
													columnWidth : 0.50,
													layout : 'form',
													items : [
															_fields['extRDSPContNum'],
															_fields['internalRDSPContNum'] ]
												},
												{
													columnWidth : 0.50,
													layout : 'form',
													items : [
															_fields['extSpecimenPlanNum'],
															_fields['internalSpecimenPlanNum'] ]
												} ]
									} ]
								},
								{
									height : _childLayoutHeight,
									xtype : 'fieldset',
									title : _translationMap['TransferBalances'],
										items : [{
													layout : "column",
													labelWidth : _labelWidth,
													items : [
														{
															layout : 'form',
															columnWidth : 0.50,
															items : [ _fields['nonTaxablePrivateCntbns'] ]
														},
														{
															layout : 'form',
															columnWidth : 0.50,
															items : [ _fields['taxableReportsRollovers'] ]
														} ]
												},
												{
													layout : "column",
													labelWidth : _labelWidth,
													items : [
														{
															layout : 'form',
															columnWidth : 0.50,
															items : [ _fields['canadaDisabilitySavingsGrant'] ]
														},
														{
															layout : 'form',
															columnWidth : 0.50,
															items : [ _fields['canadaDisabilitySavingsBond'] ]
														} ]
												}]					
								},
								{
									height : _childLayoutHeight,
									xtype : 'fieldset',
									title : _translationMap['OpenCloseBalances'],
									items : [
											{
												layout : 'column',
												labelWidth : _labelWidth,
												items : [ {
													layout : 'form',
													columnWidth : 0.50,
													items : [ _fields['fairMarketValue'] ]
												} ]
											},

											{
												layout : 'column',
												labelWidth : _labelWidth,
												items : [
														{
															layout : 'form',
															columnWidth : 0.50,
															items : [ _fields['grantBondsPaid'] ]
														},
														{
															layout : 'form',
															columnWidth : 0.50,
															items : [ _fields['contributions'] ]
														} ]
											} ]
								},

								{
									height : 140,
									xtype : 'fieldset',
									title : _translationMap['DapOrLdap'],
									items : [ {
											layout : 'column',											
											items : [									
													{
														layout : 'form',
														columnWidth : 0.44,
														xtype : 'label',
														html : '&nbsp;'
													},
													{
														layout : 'form',
														columnWidth : 0.32,
														labelWidth : _labelWidth,
														items : [ _fields['nonTaxablePortion'] ]
													} ,
													{
														layout : 'form',
														columnWidth : 0.22,
														labelWidth : _labelWidth,
														items : [ _fields['taxablePortion'] ]
													} 
												]
											},
											{
												layout : 'column',
												items : [									
													{
														layout : 'form',
														columnWidth : 0.30,
														labelWidth : 200,
														items : [ _fields['dapLdapPriorToCurrentYear'] ]
													},
													{
														layout : 'form',
														columnWidth : 0.31,
														labelWidth : 0,
														items : [ _fields['nonTaxablePriorDapLdap'] ]
													} ,
													{
														layout : 'form',
														columnWidth : 0.31,
														labelWidth : 0,
														items : [ _fields['taxablePriorDapLdap'] ]
													}
												]
											},
											{
												layout : 'column',
												items : [									
													{
														layout : 'form',
														columnWidth : 0.30,
														labelWidth : 200,
														items : [ _fields['dapLdapThisYear'] ]
													},
													{
														layout : 'form',
														columnWidth : 0.31,
														labelWidth : 0,
														items : [ _fields['nonTaxablePresentDapLdap'] ]
													} ,
													{
														layout : 'form',
														columnWidth : 0.31,
														labelWidth : 0,
														items : [ _fields['taxablePresentDapLdap'] ]
													} 
												]
											}]
									},
									{
										height : 140,
										items : [ {
											
											layout : 'form',
											columnWidth : 0.50,
											labelWidth : 170,
											items : [ _fields['transferInStatusTypeCode'] ]
											
										}]
								
									}
									
									]
							}]
				}),
		screenButtons: {
			items:[
					_buttons['okScreenButton']
					,_buttons['cancelScreenButton']
			]
		}
	}
}