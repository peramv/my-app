/*********************************************************************************************
 * @file	ClassSetup_TradeDayCtrls.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Trade Day Controls screen, part of Class Setup flow
 *********************************************************************************************/
 /*
 * Procedure: ClassSetup_TradeDayCtrls.Resources.js
 *
 * Purpose  : Trade Configuration screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Trade Configuration screens
 *
 * History  : 
 *      12 Nov 2012 H.Sartsangchan Created. 
 *                  IN3135980 Load type validation does not work properly on Class setup
 *					- Add "Change" Listener to fund for update class dropdownlist to value that belong to fund
 *
 *		25 Apr 2012 C. Sangkasen P0212170 Master Account & AMS
 *					- Introduced field AMS Model Type.                            
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    20 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030808 T54932 
 *             - Extend the hight of screen to support French 
 *             
 *     3 Feb 2016 Winnie Cheng P0251001 CHG0043877 T82126
 *             - Adding one dropdown field for Partial Redemption Indicator - Red. Gross/Net
 *
 */
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px; padding-bottom: 8px;'
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
		redGrossNetDefault: new DesktopWeb.Controls.SMVComboBox({ //Partial Redemption
			fieldLabel: _translationMap['RedemptionGrossNet']
			,width: 127
			,showCode: true
		})
		,wireElig: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['WireOrderAllowed']
		})	
		,ordType: new DesktopWeb.Controls.SMVComboBox({			
			fieldLabel: _translationMap['OrderType']
			,width: 100
	        ,showCode: true	
		}) 		
		,rrsp: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['RRSP']
		})		
		,rrif: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['RRIF']
		})		
		,esop: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['EsoP']
		})		
		,nscCompliant: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['NSCCompliant']
		})		
		,ams: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['AMSEgibility']
			, listeners:{          
					check: function(ctl, val) {
						_controller.doAMSCheck(val);
					}
				}	
		})		
		,marginAllowed: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['MarginAllowed']
		})				
		,freeRoll: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['RolloverAllowed']
		})
		,cssErrCorr: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['CSSCorrection']
		})
		,eligICTIn: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['EligibleICTIn']
			,allowBlank: false
			,showCode: true
		}) 		
		,eligICTOut: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['EligibleICTOut']
			,allowBlank: false
			,showCode: true
		}) 		
		,erisaOptn: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ERISAAllowed']
			,allowBlank: false
			,editable: false
			,listeners: {
				beforeselect: function(combo) { this.oldValue = combo.getValue(); }
				,select: function(combo) { _controller.selectERISAOptnHandler(combo); }
			}
			,showCode: true			
		}) 		
		,erisaClassGroup: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['ERISAClsGrp']
			,maxLength: 10
		}) 		
				
		,freeRollFund: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Fund']
			,width: 225
			,showCode: true
			,enableKeyEvents: true
			,listeners:{
				select: function(combo,record){ _controller.updateClassList(record.get('code'),null);}
			}
		})		
		,freeRollCl	: new DesktopWeb.Controls.ComboBox({
			fieldLabel: _translationMap['Class']
			,width: 125
			,showCode: true
			,valueField: 'classCode'
			,displayField: 'value'
			,store: new Ext.data.XmlStore({ 
					record: 'ClassInfo'
					,fields: ['classCode','description','value']					 					 
				    ,listeners:{
						load:function(aStore,records){
							Ext.each(records,function(item){
								if((item.get('classCode') != "") && (item.get('description') != "")){
									item.set('value', item.get('classCode') + ' - ' + item.get('description'));
								}
							});														
						}
					}
				}				
			)
		})			
		,freeRollQualPrd: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['QualPeriod']
			,width: 125
		})				
		,freeRollPUD: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AmtType']
			,width: 225
			,showCode: true
		})	
		,amsModelType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AMSModelType']
			,width: 127
			,showCode: true
		})			

		,stopFlags: {
			pacStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopPAC']
			})		 
			,swpStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopSWP']
			})
			,purStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopPurchase']
			})
			,redStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopRedeem']
			})
			,commRebStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopCommRebate']
			})
			,autoXferOutStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopAutoTransferOut']
			})
			,autoXferInStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopAutoTransferIn']
			})
			,xferOutStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopTransferOut']
			})
			,xferInStop: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['StopTransferIn']
			})
		}						
		
		,minMax: {
			minInit: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinInitialAmount']
				,width: 60
			})				
			,minSub: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinSubsequentAmount']
				,width: 60
			})			
			,redMinInit: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinInitialAmount']
				,width: 60
			})				
			,redMinSub: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinSubsequentAmount']
				,width: 60
			})			
			,pacMin: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['PACMinAmount']
				,width: 60
			})				
			,swpMin: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['SWPMinAmount']
				,width: 60
			})					
			,minFundClBal: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinFundClassBalance']
				,width: 60
			})		
			,minAcctBal: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinAccountBalance']
				,width: 60
			})			
		}		
		,calcMethods: {
			pShipUnitAsmt: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['PartnershipUnitAssign']
				,allowBlank: false
				,width: 157
				,showCode: true
			})
			,freeConsol: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['FreeConsolidation']
				,allowBlank: false
				,width: 157
				,showCode: true
			})					
			,purAgingRule: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['PurchaseAgingRule']
				,allowBlank: false
				,width: 157
				,showCode: true
			})
			,gainLossMthd: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['GainLossMethod']
				,allowBlank: false
				,width: 157
				,showCode: true
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

		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth - 18
				,items: [
					_header
					,_breadCrumbList
					,new Ext.Container({
						style: 'padding-left:12px; padding-right:10px;overflow-y:auto'
						,autoScroll: true
						,height: 600
						,items: [							
							{								
								xtype: 'fieldset'
								,style: 'padding-left:2px;'
								,title: _translationMap['Eligibility']
								,items: [
									{
										layout: 'column'										
										,defaults: {											
											layout: 'form'
										}
										,items: [
											{
												columnWidth: 0.28
												,items: [
													_fields['rrsp']													
													,_fields['marginAllowed']
													,_fields['esop']													
													,_fields['freeRoll']
												]
											}
											,{
												columnWidth: 0.28
												,items: [
													_fields['nscCompliant']													
													,_fields['rrif']													
													,_fields['cssErrCorr']
												]
											}											
											,{
												columnWidth: 0.44
												,labelWidth: 120
												,items: [
													_fields['eligICTIn']
													,_fields['eligICTOut']
													,_fields['erisaOptn']
													,_fields['erisaClassGroup']
												]
											}											
										]
									}
								]																																
							}
							,{
								layout: 'column'
								,style: 'margin-bottom:2px;'								
								,items: [									
									{								
										xtype: 'fieldset'										
										,columnWidth: 0.50
										,title: _translationMap['RolloverDetails']
										,style: ' margin-right:3px; padding-left:2px;'
										,items: [
											{
												layout: 'form'
												,labelWidth: 74																						
												,items: [_fields['freeRollFund'], _fields['freeRollCl'], _fields['freeRollPUD'], _fields['freeRollQualPrd']]
											}
										]																																
									}
									,{								
										xtype: 'fieldset'										
										,columnWidth: 0.50
										,title: _translationMap['CalculationMethods']
										,style: 'margin-left:3px; padding-left:2px;'
										,items: [
											{
												layout: 'form'
												,labelWidth: 132																							
												,items: [
													_fields['calcMethods']['purAgingRule'],
													_fields['calcMethods']['freeConsol'],
													_fields['calcMethods']['pShipUnitAsmt'],
													_fields['calcMethods']['gainLossMthd']
												]
											}
										]																																
									}										
								]
							}						
							,{								
								xtype: 'fieldset'
								,style: 'padding-left:2px;'
								,title: _translationMap['StopFlags']
								,items: [
									{
										layout: 'column'										
										,defaults: {
											columnWidth: 0.20
											,layout: 'form'
										}
										,items: [
											{
												columnWidth: 0.18
												,items: [
													_fields['stopFlags']['purStop']
													,_fields['stopFlags']['redStop']
												]
											}
											,{
												columnWidth: 0.17
												,items: [
													_fields['stopFlags']['pacStop']
													,_fields['stopFlags']['swpStop']
												]
											}
											,{
												columnWidth: 0.25
												,items: [
													_fields['stopFlags']['autoXferInStop']
													,_fields['stopFlags']['autoXferOutStop']
												]
											}
											,{
												items: [
													_fields['stopFlags']['xferInStop']
													,_fields['stopFlags']['xferOutStop']
												]
											}
											,{
												items: [
													_fields['stopFlags']['commRebStop']
												]
											}
										]										
									}
								]																																
							}
							,{
								layout: 'column'
								,style: 'margin-bottom:0px'
								,defaults: {
									columnWidth: 0.333
								}
								,items: [
									{
										xtype: 'fieldset'										
										,style: 'margin-right:3px; padding-left:2px;'
										,title: _translationMap['PurchaseMinAmounts']																	
										,items: [
											{											
												layout: 'form'
												,labelWidth: 150
												,items: [
													_fields['minMax']['minInit']
													,_fields['minMax']['minSub']																								
												]												
											}									
										]
									}
									,{
										xtype: 'fieldset'										
										,title: _translationMap['RedemptionMinAmounts']		
										,style: 'margin-left:3px; padding-left:2px;'															
										,items: [
											{											
												layout: 'form'
												,labelWidth: 150
												,items: [
													_fields['minMax']['redMinInit']
													,_fields['minMax']['redMinSub']																								
												]												
											}									
										]
									}
									,{
										xtype: 'fieldset'
										,title: "Wire Order"		
										,style: 'margin-left:3px; padding-left:2px;'															
										,items: [
											{											
												layout: 'form'
												,labelWidth: 100
												,height: 58
												,items: [
													_fields['wireElig']
													, _fields['ordType']
												]												
											}									
										]
									}
								]
							}
							,{
								layout: 'column'								
								,defaults: {
									columnWidth: 0.333
								}
								,items: [
									{
										xtype: 'fieldset'										
										,style: 'margin-right:3px; padding-left:2px;'
										,title: _translationMap['SystematicMinAmounts']																	
										,items: [
											{											
												layout: 'form'
												,labelWidth: 150
												,items: [
													_fields['minMax']['pacMin']
													,_fields['minMax']['swpMin']																								
												]												
											}									
										]
									}
									,{
										xtype: 'fieldset'
										,title: _translationMap['MinBalanceAmounts']		
										,style: 'margin-left:3px; padding-left:5px;'															
										,items: [
											{											
												layout: 'form'
												,labelWidth: 150
												,items: [
													_fields['minMax']['minFundClBal']
													,_fields['minMax']['minAcctBal']																								
												]												
											}									
										]
									}
									,{
										xtype: 'fieldset'
										,title: _translationMap['AMS']		
										,style: 'margin-left:3px; padding-left:2px;'
										,items: [
											{											
												layout: 'form'
												,height: 58
												,items: [
													_fields['ams']
													,{
														layout: 'form'
														,style: 'margin-left:0px; padding-left:0px;'
														,labelWidth: 71
														,items: [ _fields['amsModelType'] ]
													}	
												]												
											}									
										]
									}
								]
							}
							,{
								layout: 'column'								
								,defaults: {
									columnWidth: 1.00
								}
								,items: [{
									layout: 'form'
									,style: 'margin-left:3px'	
									,items: [
									   _fields['redGrossNetDefault']
									]
								}]
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