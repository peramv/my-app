/*********************************************************************************************
 * @file	ClassSetup_DistConfig.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Distribution Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_DistConfig.Resources.js
 *
 * Purpose  : Resources file for Distribution Configuration screen, part of Class Setup flow
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Distribution Configuration screen
 *
 * History  :  
 *  27 Jun 2013 N. Suanlamyai P0214690 T53774
 *          - Add new 2 checkboxes for new distribution types
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
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
		id: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['Applicable']
			,allowBlank: false			
			,width: 90									
		})	
		,idDefInvestOpt_cs: new DesktopWeb.Controls.Radio({
			boxLabel: _translationMap['Cash']
			,name: 'id_default'
			,width: 150									
		})
		,idDefInvestOpt_ri: new DesktopWeb.Controls.Radio({
			boxLabel: _translationMap['ReInvestment']
			,name: 'id_default'
			,width: 150			
		})
		,idOverrideOpt_cs: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['Cash']			
			,width: 150			
		})		
		,idOverrideOpt_rd: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['ReDirect']
			,width: 150
		})		
		,idOverrideOpt_ri: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['ReInvestment']			
			,width: 150			
		})
		,idAdditional_ci: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['CapitalGainIncome']			
			,width: 150			
		})
		,idAdditional_si: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['SupplementaryIncome']			
			,width: 150			
		})
		
		,cd: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['Applicable']
			,allowBlank: false			
			,width: 90								
		})
		,cdDefInvestOpt_cs: new DesktopWeb.Controls.Radio({
			boxLabel: _translationMap['Cash']
			,name: 'cd_default'
			,width: 150									
		})
		,cdDefInvestOpt_ri: new DesktopWeb.Controls.Radio({
			boxLabel: _translationMap['ReInvestment']
			,name: 'cd_default'
			,width: 150			
		})
		,cdOverrideOpt_cs: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['Cash']			
			,width: 150			
		})		
		,cdOverrideOpt_rd: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['ReDirect']			
			,width: 150			
		})		
		,cdOverrideOpt_ri: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['ReInvestment']			
			,width: 150			
		})
		,distribMode: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['DistribMode']
			,allowBlank: false
			,editable: false
			,width: 175
		    ,listeners:{
				'select': function(id){_controller.resetDefaultAdjustIDFlag()}
			}
			,showCode: true
		})
		,nextRecDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['NextRecordDate']
			,width: 100
			,disable: true
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,distribRateEdit: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['DistribRateEdit']
			,allowBlank: false
			,editable: false
			,width: 175  
			,showCode: true
		})
		,adjustIDFlag: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['DistribAdjustApply']
			,editable: false
			,width: 180 
			,showCode: true
		})
		,grpTrType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['G1G2InvenoryTrack']
			,autoSelect: true
			,width: 180 
			,showCode: true	
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
								xtype: 'fieldset'
								,title: _translationMap['IncomeDistribution']
								,id: 'id_fieldset'												
								,items: [
									{
										layout: 'form'
										,labelWidth: 150
										,items: [
											_fields['id']
											,{
												layout: 'form'
												,id: 'idDetailsForm'
												,items: [
													{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['DefaultInvestment']												
														,items: [			
															_fields['idDefInvestOpt_cs']
															,_fields['idDefInvestOpt_ri']
														]
													}
													,{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['OverrideOptions']											
														,items: [																							
															_fields['idOverrideOpt_cs']
															,_fields['idOverrideOpt_rd']
															,_fields['idOverrideOpt_ri']
														]
													}
													,{
														layout: 'form'
														,id: 'idAdditionalDetailsForm'
														,items:[
															{
																xtype: 'compositefield'
																,fieldLabel: _translationMap['AdditionalID']											
																,items: [																							
																	_fields['idAdditional_ci']
																	,_fields['idAdditional_si']
																]
															}
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
								,title: _translationMap['CapitalGains']
								,id: 'cd_fieldset'												
								,items: [
									{
										layout: 'form'
										,labelWidth: 150
										,items: [
											_fields['cd']
											,{
												layout: 'form'
												,id: 'cdDetailsForm'
												,items: [
													{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['DefaultInvestment']												
														,items: [																																			
															_fields['cdDefInvestOpt_cs']
															,_fields['cdDefInvestOpt_ri']
														]
													}
													,{
														xtype: 'compositefield'
														,fieldLabel: _translationMap['OverrideOptions']											
														,items: [																							
															_fields['cdOverrideOpt_cs']
															,_fields['cdOverrideOpt_rd']
															,_fields['cdOverrideOpt_ri']
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
								,title: _translationMap['DistribOptions']
								,id: 'do_fieldset'												
								,items: [
									{
										layout: 'column'
										,defaults: {
											layout: 'form'																	
										}
										,items: [
											{
												columnWidth: 0.50
												,labelWidth: 150
												,items: [
													_fields['distribMode']
													,_fields['distribRateEdit']
												]
											}
											,{
												columnWidth: 0.50
												,labelWidth: 150
												,items: [
													_fields['nextRecDate']
													,_fields['adjustIDFlag']
												]
											}
											,{
												columnWidth: 0.50
												,labelWidth: 150
												,items: [
													_fields['grpTrType']
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