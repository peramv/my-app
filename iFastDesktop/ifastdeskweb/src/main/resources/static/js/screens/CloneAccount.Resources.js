/*********************************************************************************************
 * @file	CloneAccount.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for Clone Account screen
 *********************************************************************************************/
/*
 * Procedure: CloneAccount.Resources.js
 *
 * Purpose  : Resources file for Clone Account screen
 *             
 * Notes    : 
 *
 * History  :  
 *	15 Aug 2013 G. Thawornwachirakun P0193400 T54018
 *					- Add onlyActive param to broker,branch,and slsRep search
 *
 *	01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 */
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 330;
	var _layoutWidth = 670;
	
	// **** fields ****
	var _fields = {
		broker: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Broker']
			,smartview: 'brokerSearch'		
			,addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'yes'}}]
			,fields: ['displayValue', 'agencyCode']						
			,valueField: 'agencyCode'								
			,width: 535				
			,allowBlank: false			
			,listeners:{
				populated: function(){				
					if (_controller.isBranchUpdateAllowed())
					{
						_fields['branch'].enable();
					}
					_fields['slsrep'].enable();					
				}
				,cleared: function(){
					 _fields['branch'].reset();
					 _fields['branch'].disable();
					 _fields['slsrep'].reset();
					 _fields['slsrep'].disable();
				}
			}
		})
		,branch: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Branch']
			,smartview: 'branchSearch'
			,fields: ['displayValue', 'branch']
			,addtlSearchParams: 
				[{name: 'agencyCode', valueFn: function(){return _fields['broker'].getValue();}}
				,{name: 'onlyActive', valueFn: function(){return 'yes';}}
				]
			,valueField: 'branch'								
			,width: 535
			,disabled: true			
			,listeners:{
				populated: function(){
					if (!_fields['branch'].disabled)
					{
						_fields['slsrep'].reset();
						_fields['slsrep'].enable();
					}
				}

				,cleared: function(){				
					if (!_fields['branch'].disabled)
					{	 
						_fields['slsrep'].reset();	
						_fields['slsrep'].disable();
					}													 												 
				}
			}			
		})
		,slsrep: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Slsrep']			
			,smartview: 'salesRepSearch'				
			,fields: ['displayValue', 'agentCode']
			,forceSelection: false
			,addtlSearchParams: [
				{name: 'agencyCode', valueFn: function(){return _fields['broker'].getValue();}}
				,{name: 'branch', valueFn: function(){return _fields['branch'].getValue();}}
				,{name: 'onlyActive', valueFn: function(){return 'yes';}}
			]
			,valueField: 'agentCode'
			,width: 535											
			,allowBlank: false
			,listeners: {					
				change: function()
				{
					if (this.selectedRecord == null)
					{						
						DesktopWeb.Util.displayPrompt(_translationMap['NewSalesRepPrompt'], 
							function(btn, text){
							    if (btn != 'ok'){
							        _fields['slsrep'].setValue("");
							        _fields['slsrep'].markInvalid();
							    }
								else
								{
									_controller.setNewSalesRep(true)
									
									if (!_controller.isBranchUpdateAllowed())
									{
										_fields['branch'].reset();										
									}
								}
							});
					}
					else if (this.selectedRecord != null)
					{	
						if (_fields['branch'].getValue() == "")
						{
							var branchCode = IFDS.Xml.getNodeValue(this.selectedRecord.node, 'branch');
							var branchDesc = IFDS.Xml.getNodeValue(this.selectedRecord.node, 'branchDisplayValue');
							_fields['branch'].prepopulate(branchCode, branchDesc);
						}
						_controller.setNewSalesRep(false);
					}				
				}
			}								
		})
		,acctDesig: new DesktopWeb.Controls.SMVComboBox({
			width: 110
			,fieldLabel: _translationMap['AcctDesign']
			,allowBlank: false
			,listeners: {
				change: function(){
					_controller.handleAcctDesigChange();					
				}
				,select: function(){
					_controller.handleAcctDesigChange();					
				}
			}
		})
		,taxType: new DesktopWeb.Controls.SMVComboBox({
			width: 250
			,fieldLabel: _translationMap['TaxType']
			,allowBlank: false	
			,listeners: {
				select: function(fld, rec, index)
				{		
					_controller.toggleRegAgentField(rec.data['code']);
					_controller.toggleRegAgentAcctNumField(rec.data['code']);
					_controller.populateAgentDropdowns(rec.data['code']);
				}
			}
			
		})
		,altAcct: new DesktopWeb.Controls.TextField({
			width: 125
			,fieldLabel: _translationMap['AltAcctNbr']
		})
		,effDate: new DesktopWeb.Controls.DateField({
			width: 100
			,fieldLabel: _translationMap['EffectiveDate']
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
	
	,regAgent: new DesktopWeb.Controls.SMVComboBox({
		width: 240
		,fieldLabel: _translationMap['RegAgent']
		,allowBlank: false
		,disabled: true	
		
	})
	,regAgentAcctNum: new DesktopWeb.Controls.TextField({
		width: 125
		,fieldLabel: _translationMap['RegAgentAcctNum']
		,allowBlank: false
		,disabled: true	
	})
	
		,intermCode: new DesktopWeb.Controls.SMVComboBox({
			width: 240
			,fieldLabel: _translationMap['IntermCode']
			,allowBlank: false
			,listeners: {
				change: function(){
					_controller.handleIntermCodeChange();					
				}
				,select: function(){
					_controller.handleIntermCodeChange();					
				}
			}	
		})
		,intermAcct: new DesktopWeb.Controls.TextField({
			width: 125
			,fieldLabel: _translationMap['IntermAcctNbr']
			,allowBlank: false
		})
		,distributionInfo: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['DistributionInfo']
			,hideLabel: true
			,disabled: true			
		})
		,bankInfo: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['BankInfo']
			,hideLabel: true
			,disabled: true			
		})
		,allEntities: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['AllEntities']
			,hideLabel: true
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
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				{
					defaults: {
						labelWidth: 100
					}
					,items: [
						{
							layout: 'form'
							,items : [
								_fields['broker']
								,_fields['branch']
								,_fields['slsrep']
							]
						}
						,{
							layout: 'column'
							,defaults: {
								layout: 'form'
							}
							,items: [
								{
									columnWidth: 0.57
									,items: [
										_fields['acctDesig']
										,_fields['taxType']
										,_fields['regAgent']
										,_fields['intermCode']
									]
								}
								,{
									labelWidth: 130
									,columnWidth: 0.43
									,items: [	
										_fields['altAcct']
										,_fields['effDate']
										,_fields['regAgentAcctNum']
										,_fields['intermAcct']
									]
								}
							]
						}
						,{
							layout: 'column'
							,xtype: 'fieldset'
							,title: _translationMap['CloneOptions']
							,bodyStyle: 'padding-left: 55px'
							,defaults: {
								columnWidth: 0.33
								,layout: 'auto'
							}
							,items: [
								{
									items: [
										_fields['distributionInfo']
									]
								}
								,{
									items: [	
										_fields['bankInfo']
									]
								}
								,{
									items: [
										_fields['allEntities']
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
				text: _translationMap['OK']
				,handler: function(){					
					if (_controller.validateInput())
					{
						DesktopWeb.Util.commitScreen();
					}
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