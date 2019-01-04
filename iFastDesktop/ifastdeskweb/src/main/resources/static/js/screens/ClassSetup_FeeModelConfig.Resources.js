/*********************************************************************************************
 * @file	ClassSetup_FeeModelConfig.Resources.js
 * @author	Aurkarn Mongkonrat
 * @desc	Resources file for Fee Model Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_FeeModelConfig.Resources.js
 *
 * Purpose  : Fee Model Configuration screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Fee Model Configuration screens
 *
 * History  : 24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *            Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration.
 */
 
 DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 15
	})	
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({						
		height: 45						
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id)}
		}
	})	
	
	// **** fields ****
	var _fields = {	
		mgmtFee: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['Applicable']
			,allowBlank: false	
			,editable: false
			,width: 90
		})		
		,mgmtFeePayOpt: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['PayOption']
			,width: 90
			,editable: false
			,showCode: true
		})		 
		,mgmtFeeBroker: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['BrokerPortion']
			,editable: false
			,width: 90
		})		
		,mgmtFeeBrokChg: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['BrokerChange']	
			,editable: false
			,width: 90
		})		
		,mfrRebate: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['Applicable']
			,allowBlank: false	
			,editable: false
			,width: 90
		})

		,mgmtFeeAcctAggr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AcctAggregation']
			,width: 310
			,showCode: true
			,allowBlank: false
			,editable: false
		})		
		,mgmtFeeFundAggr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FundAggregation']
			,width: 310
			,showCode: true
			,allowBlank: false
			,editable: false
		})		 
		,mgmtFeeProrateOpt: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ProrateOption']	
			,width: 310
			,showCode: true
			,allowBlank: false
			,editable: false
		})		
		,mfrAcctAggr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AcctAggregation']	
			,width: 310
			,showCode: true
			,allowBlank: false	
			,editable: false			
		})		
		,mfrFundAggr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FundAggregation']	
			,width: 310	
			,showCode: true
			,allowBlank: false
			,editable: false
		})
		,advFee: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['Applicable']	
			,width: 90	
			,allowBlank: false
			,editable: false
		})
		,advAcctAggr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AcctAggregation']	
			,width: 310
			,showCode: true
			,allowBlank: false	
			,editable: false			
		})		
		,advFundAggr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FundAggregation']	
			,width: 310	
			,showCode: true
			,allowBlank: false
			,editable: false
		})
	}
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight

		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,fields: _fields
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth - 18												
				,items: [					
					_header
					,_breadCrumbList					
					,new Ext.Container({
						autoScroll: true
						,height: 600
						,style: 'padding-left:12px; padding-right:10px;overflow-y:auto'						
						,items: [
						{
								layout: 'column'
								,style: 'margin-bottom:10px'								
								,items: [
									{												
										layout: 'column'
										,defaults: {																						
											layout: 'form'
										}										
										,xtype: 'fieldset'
										,style: 'margin-right:3px; padding-left:10px;'
										,title: _translationMap['ManagementFee']
										,columnWidth: 1	
										,height: 200
										,items: [
											{												
												labelWidth: 75
												,columnWidth: 0.5
												,items: [_fields['mgmtFee'], _fields['mgmtFeePayOpt']]
											}
											,{														
												labelWidth: 90
												,columnWidth: 0.5											
												,items: [_fields['mgmtFeeBroker'], _fields['mgmtFeeBrokChg']]
											}
											,{
												labelWidth: 75
												,items: [_fields['mgmtFeeAcctAggr'], _fields['mgmtFeeFundAggr'], _fields['mgmtFeeProrateOpt']]
											}																						
										]											
									}	
									,{													
										xtype: 'fieldset'
										,style: 'margin-left:0px; padding-left:10px;'
										,title: _translationMap['ManagementFeeRebate']
										,columnWidth: 1
										,height: 140
										,items: [
											{
												layout: 'form'
												,labelWidth: 75
												,items: [_fields['mfrRebate'], _fields['mfrAcctAggr'], _fields['mfrFundAggr']]
											}
										]
									}								
									,{								
										xtype: 'fieldset'
										,style: 'margin-left:0px; padding-left:10px;'
										,title: _translationMap['AdvisorFee']
										,columnWidth: 1
										,height: 140
										,items: [
											{
												layout: 'form'
												,labelWidth: 75
												,items: [_fields['advFee'], _fields['advAcctAggr'], _fields['advFundAggr']]
											}
										]
									}
								]
							}
						]
					})
				]
			}
		)
		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Previous']
				,hidden: true
				,disabled: true				
				,id: 'prevBtn'
				,handler: function(){
					_controller.previous();
				}				
			})				
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Save']
				,id: 'saveBtn'
				,disabled: true
				,handler: function(){
					_controller.save();	
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Reset']
				,id: 'resetBtn'
				,disabled: true
				,handler: function(){
					_controller.reset();	
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,hidden: true				
				,id: 'cancelBtn'
				,handler: function(){
					_controller.cancel();
				}				
			})								
			,new DesktopWeb.Controls.ScreenButton({
				text: ''
				,hidden: true				
				,id: 'nextBtn'
				,handler: function(){
					_controller.next();
				}				
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['ReturntoSummary']
				,hidden: true				
				,id: 'summaryBtn'
				,handler: function(){
					_controller.changeScreen('Summary');
				}				
			})
		]	
	}
}