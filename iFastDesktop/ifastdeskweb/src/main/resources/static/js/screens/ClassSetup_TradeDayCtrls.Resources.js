/*********************************************************************************************
 * @file	ClassSetup_TradeDayCtrls.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Trade Day Controls screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *	21 May 2015 Winnie Cheng P0241128 T80810
 *			   - Added one field "Redemption Notice Period". 
 *	
 *	8 Jan 2018	Sreejith A P0274727 P0274727-1
 *			- Added purchase payment lead days and
 *				  different settlement currency fields
 *
 *	23 Jan 2018	Sreejith.A P0274733 P0274733-156
 *			   - Added MFR payment lead days
 *
 *	22 Mar 2018 Sreejith.A P0274727 P0274727-88
 *			   - T+0 Project P0274727 changes revert from 18.3
 *
 *	12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 808;
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
		cutOffDays:{
			header: {
				numDays: new DesktopWeb.Controls.TextField({
					style: 'border: none; text-transform: none; background:transparent;'
					,width: 75
					,readOnly: true
					,value: _translationMap['Days']
				})
				,dayType: new DesktopWeb.Controls.TextField({
					style: 'border: none; text-transform: none; background:transparent;'
					,width: 120
					,readOnly: true
					,value: _translationMap['DayType']
				})
				,cutOffTime: new DesktopWeb.Controls.TextField({
					style: 'border: none; text-transform: none; background:transparent;'
					,width: 50
					,readOnly: true
					,value: _translationMap['Time']
				})
			}
			,pur: {
				numDays: new DesktopWeb.ScreenResources.NumberField()
				,dayType: new DesktopWeb.ScreenResources.SMVComboBox({showCode: true})
			}
			,red:{
				numDays: new DesktopWeb.ScreenResources.NumberField()
				,dayType: new DesktopWeb.ScreenResources.SMVComboBox({showCode: true})
				,cutOffTime: new DesktopWeb.Controls.TextField({
					emptyText: _translationMap['HHMM']
					,regex: /^(?:0?\d|1[0-9]|2[0123]):?[0-5]\d$/
					,regexText: _translationMap['InvalidTimeFormat']
					,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '5'}
					,width: 50
				})
			}
			,exchIn:{
				numDays: new DesktopWeb.ScreenResources.NumberField()
				,dayType: new DesktopWeb.ScreenResources.SMVComboBox({showCode: true})
			}
			,exchOut:{
				numDays: new DesktopWeb.ScreenResources.NumberField()
				,dayType: new DesktopWeb.ScreenResources.SMVComboBox({showCode: true})
			} 
		}
		,purchase: {
			purchasePmtLdDays: {
				AmountType: new DesktopWeb.Controls.Checkbox({
						boxLabel: _translationMap['AmountType']
						, width: 120
						, listeners: {
							check: function(fld) {
								_controller.onAmountTypeChange(this.getValue(),_fields['purchase']['purchasePmtLdDays']);
							}
						}
				})
    			,UnitDaysLabel: new DesktopWeb.Controls.TextField({
					style: 'border: none; text-transform: none; background:transparent;'
					,width: 35
					,readOnly: true
    			})
				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
					width: 45
					,name: 'Unit Days'
					,allowNegative: true
					,allowBlank: true
				})
				,UnitDayType: new DesktopWeb.Controls.SMVComboBox({width: 90,  showCode: true})
				,AmountDaysLabel: new DesktopWeb.Controls.TextField({
					style: 'border: none; text-transform: none; background:transparent;'
					,width: 50
					,readOnly: true
					,value: _translationMap['AmountDays']
				})
				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
					width: 45
					,name: 'Amount Days'
					,allowNegative: true
					,allowBlank: true
				})
				,AmountDayType: new DesktopWeb.Controls.SMVComboBox({width: 90,  showCode: true})
			}
			,diffSettleCurr: {
				AmountType: new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['AmountType']
					, width: 120
    				, listeners: {
    					check: function() {
    						_controller.onAmountTypeChange(this.getValue(),_fields['purchase']['diffSettleCurr']);
    					}
    				}
				})
				,UnitDaysLabel: new DesktopWeb.Controls.TextField({
					style: 'border: none; text-transform: none; background:transparent;'
					,width: 35
					,readOnly: true
        		})
				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
					width: 45
					,name: 'Unit Days'
					,allowNegative: true
					,allowBlank: true
				})
				,UnitDayType: new DesktopWeb.Controls.SMVComboBox({width: 90,  showCode: true})
				,AmountDaysLabel: new DesktopWeb.Controls.TextField({
					style: 'border: none; text-transform: none; background:transparent;'
					,width: 50
					,readOnly: true
					,value: _translationMap['AmountDays']
				})
				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
					width: 45
					,name: 'Amount Days'
					,allowNegative: true
					,allowBlank: true
				})
				,AmountDayType: new DesktopWeb.Controls.SMVComboBox({width: 90,  showCode: true})
			}
		}
		
		,purAutoCancDays: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['Purchase']
		})
		,redAutoCancDays: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['Redemption']			
		})
		,exchAutoCancDays: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['Exchange']			
		})
		,tfrAutoCancDays: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['Transfer']			
		})
		
		,tradeLeadDays: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['TradeLeadDays']		
		})

		,tradeLeadDaysPur: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['Purchase']			
		})
		,tradeLeadDaysRed: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['Redemption']			
		})
		
		,lastDivdDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastDividendDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,lastSetlDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastSettleDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,nextSetlDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['NextSettleDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,lastValDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastValuationDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,nextValDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['NextValuationDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,lastNR: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastCycleDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,nextNR: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['NextCycleDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,lastMFeeDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastMgmtFeeDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,lastMFRDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastMgmtFeeRebateDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,lastTFRDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastTFRDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,navCalcDays: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['NAVCalcDays']			
		})
		,lastCrysDate: new DesktopWeb.ScreenResources.DateField({
			fieldLabel: _translationMap['LastCrystalisationDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,pymtLeadDays: {
			numDays: new DesktopWeb.ScreenResources.NumberField({width: 45})
			,dayType: new DesktopWeb.Controls.SMVComboBox({width: 100, disabled: true, showCode: true})
			,dayFld: new DesktopWeb.Controls.TextField({
				width: 40
				,disabled: true
				,style: 'text-transform:none'
				,value: _translationMap['Day']
			})
		}
		,mfrPymtLeadDays: {
			numDays: new DesktopWeb.ScreenResources.NumberField({width: 45, allowBlank: true})
			,dayType: new DesktopWeb.Controls.SMVComboBox({width: 100, disabled: true, showCode: true})
			,dayFld: new DesktopWeb.Controls.TextField({
				width: 40
				,disabled: true
				,style: 'text-transform:none'
				,value: _translationMap['Day']
			})
		}
		,tradeDayDelay: {
			numDays: new DesktopWeb.ScreenResources.NumberField({width: 45, allowBlank: false})
			,dayType: new DesktopWeb.Controls.SMVComboBox({width: 100, allowBlank: false, showCode: true})
			,dayFld: new DesktopWeb.Controls.TextField({
				width: 40
				,disabled: true
				,style: 'text-transform:none'
				,value: _translationMap['Day']
			})
		}
		,redNoticePeriod: new DesktopWeb.ScreenResources.NumberField({
			fieldLabel: _translationMap['RedemptionNoticePeriod']			
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
		
		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					_header
					,_breadCrumbList
					,new Ext.Container({
						style: 'padding-left:12px; padding-right:10px'
						,items: [
							{
								layout: 'column'
								,style: 'margin-bottom:10px;'
								,items: [
									{
										xtype: 'fieldset'
										,columnWidth: 0.37
										,height: 180
										,style: 'margin-right:3px; padding-left:10px;'
										,title: _translationMap['AutoForceCancelDays']																	
										,items: [
											{
												layout: 'form'
												,labelWidth: 110
												,style: 'padding-top:12px'
												,items: [
													_fields['purAutoCancDays']
													,_fields['redAutoCancDays']
													,_fields['exchAutoCancDays']
													,_fields['tfrAutoCancDays']
												]
												
											}
										]
									}
									,{
										xtype: 'fieldset'
										,columnWidth: 0.63
										,style: 'margin-left:3px; padding-left:10px;'
										,title: _translationMap['CutOffDays']																	
										,items: [
											{
												layout: 'form'
												,labelWidth: 120
												,defaults: {
													width: 200
													,msgTarget: 'side'
												}
												,items: [
													{
														xtype: 'compositefield'
														,fieldLabel: ' '
														,labelSeparator: ''
														,id: 'cutOffHeaderCompFld'
														,width: 255
														,items: [													
															_fields['cutOffDays']['header']['numDays']
															,_fields['cutOffDays']['header']['dayType']
															,_fields['cutOffDays']['header']['cutOffTime']
														]
													}													
													,{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['Purchase']
														,id: 'cutOffPurCompFld'
														,items: [													
															_fields['cutOffDays']['pur']['numDays']
															,_fields['cutOffDays']['pur']['dayType']
														]
													}													
													,{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['Redemption']
														,id: 'cutOffRedCompFld'
														,width: 255
														,items: [
															_fields['cutOffDays']['red']['numDays']
															,_fields['cutOffDays']['red']['dayType']
															,_fields['cutOffDays']['red']['cutOffTime']
														]
													}
													,{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['ExchangeIn']	
														,id: 'cutOffExInCompFld'											
														,items: [													
															_fields['cutOffDays']['exchIn']['numDays']
															,_fields['cutOffDays']['exchIn']['dayType']
														]
													}
													,{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['ExchangeOut']		
														,id: 'cutOffExOutCompFld'										
														,items: [													
															_fields['cutOffDays']['exchOut']['numDays']
															,_fields['cutOffDays']['exchOut']['dayType']
														]
													}
												]
												
											}
										]
									}
								]
							}
							,{
								xtype: 'fieldset'
								,style: 'padding-left:10px;'
								,title: _translationMap['TradeLeadDays']																
								,items: [
									{
										layout: 'column'
										,defaults: {
											layout: 'form'
											,columnWidth: 0.33
											,labelWidth: 100											
										}
										,items: [
											{
												items: [_fields['tradeLeadDays']]
											}
											,{
												items: [_fields['tradeLeadDaysPur']]
											}
											,{
												items: [_fields['tradeLeadDaysRed']]
											}
										]
									}
								]
							}

							,{
								xtype: 'fieldset'
								,style: 'padding-left:10px;'
								,title: _translationMap['Miscellaneous']																	
								,items: [
									{
										layout: 'column'
										,defaults: {
											layout: 'form'
											,labelWidth: 170
										}
										,items: [
											{
												columnWidth: 0.45
												,items: [
													_fields['lastSetlDate']
													,_fields['lastValDate']
													,_fields['lastNR']
													,_fields['lastMFeeDate']
													,_fields['lastTFRDate']	
													,_fields['navCalcDays']		
													,_fields['lastDivdDate']											
													,_fields['lastCrysDate']
												]
											}
											,{
												columnWidth: 0.55
												,items: [
													_fields['nextSetlDate']
													,_fields['nextValDate']
													,_fields['nextNR']
													,_fields['lastMFRDate']	
													,{
														xtype: 'compositefield'
														,id: 'pymtCompFld'
														,width: 195
														,fieldLabel: _translationMap['PaymentLeadDays']
														,msgTarget: 'side'
														,items: [													
															_fields['pymtLeadDays']['numDays']
															,_fields['pymtLeadDays']['dayType']
															,_fields['pymtLeadDays']['dayFld']
														]
													}
													,{
														xtype: 'compositefield'
														,id: 'mfrPymtCompFld'
														,width: 195
														,fieldLabel: _translationMap['MfrPymtLeadDays']
														,msgTarget: 'side'
														,items: [													
															_fields['mfrPymtLeadDays']['numDays']
															,_fields['mfrPymtLeadDays']['dayType']
															,_fields['mfrPymtLeadDays']['dayFld']
														]
													}
													,{
														xtype: 'compositefield'
														,id: 'trdDayDelayCompFld'
														,width: 195
														,fieldLabel: _translationMap['TradeDayDelay']
														,msgTarget: 'side'
														,items: [
															_fields['tradeDayDelay']['numDays']
															,_fields['tradeDayDelay']['dayType']
															,_fields['tradeDayDelay']['dayFld']
														]
													}
													,_fields['redNoticePeriod']	
												]
											}
										]
									}
								]
							}
							,{
								layout: 'column'
								,style: 'margin-bottom:10px;'
								,items: [
									{
										xtype: 'fieldset'
										,style: 'padding-left:10px;'
										,title:  _translationMap['PurchasePaymentLeadDays']	
										,width: 728
										,items: [
											{
												layout: 'form'
												,labelWidth: 185
												,defaults: {
													msgTarget: 'side'
												}
												,items: [													
													{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['PurchasePaymentLeadDays']
														,width : 505
														,invalidClass: ''
														,items: [		
															_fields['purchase']['purchasePmtLdDays']['AmountType']
															,_fields['purchase']['purchasePmtLdDays']['UnitDaysLabel']
															,_fields['purchase']['purchasePmtLdDays']['UnitDays']
															,_fields['purchase']['purchasePmtLdDays']['UnitDayType']
															,_fields['purchase']['purchasePmtLdDays']['AmountDaysLabel']
															,_fields['purchase']['purchasePmtLdDays']['AmountDays']
															,_fields['purchase']['purchasePmtLdDays']['AmountDayType']
														]
													}
													,{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['DifferentSettleCurrency']
														,width : 505
														,invalidClass: ''
														,items: [	
															_fields['purchase']['diffSettleCurr']['AmountType']
															,_fields['purchase']['diffSettleCurr']['UnitDaysLabel']
															,_fields['purchase']['diffSettleCurr']['UnitDays']
															,_fields['purchase']['diffSettleCurr']['UnitDayType']
															,_fields['purchase']['diffSettleCurr']['AmountDaysLabel']
															,_fields['purchase']['diffSettleCurr']['AmountDays']
															,_fields['purchase']['diffSettleCurr']['AmountDayType']

														]
													}
												]
												
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

DesktopWeb.ScreenResources.NumberField = Ext.extend( DesktopWeb.Controls.NumberField, {
	width: 75
	,allowBlank: false
	,allowDecimals: false
	,allowNegative: false
});

DesktopWeb.ScreenResources.DateField = Ext.extend( DesktopWeb.Controls.DateField, {
	width: 100	
});

DesktopWeb.ScreenResources.SMVComboBox = Ext.extend( DesktopWeb.Controls.SMVComboBox, {
	width: 120
});
