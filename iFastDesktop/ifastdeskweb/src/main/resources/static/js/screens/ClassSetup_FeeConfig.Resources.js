/*********************************************************************************************
 * @file	ClassSetup_FeeConfig.Resources.js
 * @author	Rod Walker
 * @desc	Resources file for Fee Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_FeeConfig.Resources.js
 *
 * Purpose  : Fee Configuration screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Fee Configuration screens
 *
 * History  : 
 *
 *  25 Nov 2012 H.Sartsangchan P0207062 FN01 MF/MFR Enhancement
 *          - Rearrange Screen Transfer fee , Management Fee
 *          - Add new Management Fee Rebate panel
 *          - Add new 5 SMVComboobox Fields
 *
 *  02 May 2013 G.Thawornwachirakun P0181067 IN3297463 T53495
 *          - Update to set dynamic allowBlank on Acquisition Based on 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *          - Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration.
 *
 *  07 May 2018 Pao - Supareuk S.
 *  		Field alignment adjustment. This is to adjust trailer fee rebate applicable 
 *  		and performance fee applicable flags to align with other fields on the screen
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 700;
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
		trlFeeDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['TrailerFeeDate']
			,width: 100
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,trlGrandFathDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['TrailerFeeGrandFatherDate']
			,width: 100
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,earlyMatDays: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['EarlyMaturityDays']
			,width: 75
		})
		,sttrMatDays: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['ShortTermTradingMaturityDays']
			,width: 75
		})					
		
		,tfrFee: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['Applicable']
			,allowBlank: false
			,listeners: {
				select: function(){					
					_fields['tfrFeeRate'].clearInvalid();
					_fields['tfrFeeType'].clearInvalid();
					_fields['tfrBasedOn'].clearInvalid();
				}
			}			
		})			 
		,tfrFeeRate: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['Rate']
			,validator: function(val){
				if (_fields['tfrFee'].getValue() == 'yes' && val == "")
				{
					return _translationMap['FldRequired']
				}
				else
				{
					return true;
				}
			}		
			,width: 75
			,maxValue: 100
			,minValue: 0			
		})			
		,tfrFeeType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FeeType']
			,width: 100
			,validator: function(val){
				if (_fields['tfrFee'].getValue() == 'yes' && val == "")
				{
					return _translationMap['FldRequired']
				}
				else
				{
					return true;
				}
			}
			,showCode: true			
		})					
		,tfrBasedOn: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['BasedOn']
			,validator: function(val){
				if (_fields['tfrFee'].getValue() == 'yes' && val == "")
				{
					return _translationMap['FldRequired']
				}
				else
				{
					return true;
				}
			}		
			,width: 307
			,showCode: true			
		})
		,howPaid: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Paid']
			,width: 200
			,showCode: true
		})			
		,tfRebate: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['Applicable']		
			,allowBlank: false
			,editable: false
		})
		,bel: {
			brokerComm: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['BrokerCommision']
				,allowBlank: false
				,width: 75
				,maxValue: 100
				,minValue: 0
			})			 
			,feeType: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['FeeType']
				,allowBlank: false
				,width: 100
				,showCode: true
			})					
			,basedOn: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['BasedOn']
				,allowBlank: false
				,width: 265
				,showCode: true
			})					
			,dscBasedRate: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['DSCBasedRate']
				,width: 75
				,maxValue: 100
				,minValue: 0
			})			
			,minVarDsc: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinVarDSC']
				,width: 75
			})			
			,dscOverride: new DesktopWeb.Controls.YesNoComboBox({
				fieldLabel: _translationMap['DSCOverride']
				,width: 75
			})			
			,withHoldRate: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['WithholdRate']
				,width: 75
				,maxValue: 100
				,minValue: 0
			})
		}
		
		,fel: {
			feeType: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['AcquisitionFeeType']
				,allowBlank: false
				,width: 100
				,showCode: true
			})				 
			,howPaid: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['AcquisitionPaid']
				,width: 190
				,showCode: true				
			})				
			,rate: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['AcquisitionRate']
				,allowBlank: false
				,width: 75
			})	
			,basedOn: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['AcquisitionBasedOn']
				,width: 280
				
				,showCode: true
			})				
			,maxRate: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MaxFeeRate']
				,allowBlank: false
				,width: 75
				,maxValue: 100
				,minValue: 0
			})		
			,minRate: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['MinFeeRate']
				,allowBlank: false
				,width: 75
				,maxValue: 100
				,minValue: 0
			})	
			,withHoldRate: new DesktopWeb.Controls.NumberField({
				fieldLabel: _translationMap['WithholdRate']
				,width: 75
				,maxValue: 100
				,minValue: 0
			})							
		}
		,iwt: {
			deminimisOpt: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['EighthAnnivDeMinimusOption']
				,width: 100
				,showCode: true
			})		
			,mfrTaxOpt: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['MFRPaidBy']
				,width: 150
				,showCode: true
			})
			,deemedDate1: new DesktopWeb.Controls.DateField({
				fieldLabel: _translationMap['FirstDeemedDisposalDate']
				,width: 100
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			})
			,deemedDate2: new DesktopWeb.Controls.DateField({
				fieldLabel: _translationMap['SecondDeemedDisposalDate']
				,width: 100	
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			})
		}
		,perfFeeFlag: new DesktopWeb.Controls.YesNoComboBox({
			    fieldLabel: _translationMap['Applicable']				
		 })

	}
	
	// **** grids ****
	var _grids = {
		feeScale: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true
			,height: 120
			,store: new Ext.data.XmlStore({
				record: 'FeeScale'
				,fields: ['feeCode', 'level', 'lower', 'upper', 'rate', 'deff', 'scaleUUID']
				,listeners: {
					load: function(store, records)
					{	
						Ext.each(records, function(record){
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({					
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){_controller.updateScaleActionButtons();}
						,rowdeselect: function(){_controller.updateScaleActionButtons()}
					}
			})		
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
						menuDisabled: true
					}
					,columns: [
						{header: _translationMap['FeeCode'], id: 'feeCode', dataIndex: 'feeCode', width: 175, renderer: function(value){return value + ' - ' + _controller.getListValueDesc('FeeCodeList', value)}}
						,{header: _translationMap['Level'], dataIndex: 'level', width: 65}
						,{header: _translationMap['Lower'], dataIndex: 'lower', width: 100}	
						,{header: _translationMap['Upper'], dataIndex: 'upper', width: 100}
						,{header: _translationMap['Rate'], dataIndex: 'rate', width: 105}						
						,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width: 100}
					]		
				}
			)
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']					
					,handler: function(){_controller.openScalePopup(_controller.ADD);}														
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'								
					,text: _translationMap['Modify']					
					,handler: function(){_controller.openScalePopup(_controller.MOD)}													
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'								
					,text: _translationMap['Delete']					
					,handler: function(){_controller.openScalePopup(_controller.DEL)}													
				})
			]			
		})
	}
	
	// **** popups ****
	var _popups = {
		feeScale: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 430
			,action: null
			,scaleUUID: null						
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']						
					,style: 'text-align:center'														
				}						
				,{						
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border:false}
					,labelWidth: 65
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'feeCode'									
							,fieldLabel: _translationMap['FeeCode']
							,allowBlank: false
							,width: 315
							,showCode: true
						})
						,{
							layout: 'column'							
							,defaults: {															
								layout: 'form'
								,border: false
							}
							,items: [
								{
									labelWidth: 65
									,columnWidth: 0.48
									,items: [
										new DesktopWeb.Controls.TextField({
											itemId: 'level'									
											,fieldLabel: _translationMap['Level']
											,allowBlank: false
											,width: 90														
										})
										,new DesktopWeb.Controls.NumberField({
											itemId: 'lower'									
											,fieldLabel: _translationMap['Lower']
											,allowBlank: false							
											,width: 90													
										})
										,new DesktopWeb.Controls.NumberField({
											itemId: 'rate'									
											,fieldLabel: _translationMap['Rate']
											,allowBlank: false
											,width: 90														
										})										
									]
								}
								,{
									labelWidth: 90
									,columnWidth: 0.52
									,items: [
										new DesktopWeb.Controls.DateField({
											itemId: 'deff'									
											,fieldLabel: _translationMap['EffectiveDate']
											,allowBlank: false
											,width: 90
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
										})
										,new DesktopWeb.Controls.NumberField({
											itemId: 'upper'
											,fieldLabel: _translationMap['Upper']
											,allowBlank: false
											,width: 90
										})
									]
								}
							]
						}
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['feeScale'].isValid())
						{
							_controller.saveFeeScale(_popups['feeScale'].action, _popups['feeScale'].getData());					
							_controller.closeScalePopup();		
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_controller.closeScalePopup()}
				})
			]
			,init: function(action)
			{
				this.action = action
				if (this.rendered)
				{					
					this.clearAllFields();
				}
				this.get(0).hide(); //hide delete message
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['FeeScale']+ ' - ' +_translationMap['Add']);
						this.enableAllFields();																									
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['FeeScale']+ ' - ' +_translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();
						this.getField('feeCode').disableField();																			
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['FeeScale']+ ' - ' +_translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['feeScale'].getSelectedRecord();
				this.getField('feeCode').setValue(rec.data['feeCode']);				
				this.scaleUUID = rec.data['scaleUUID'];
				this.getField('level').setValue(rec.data['level']);											
				this.getField('deff').setValue(rec.data['deff']);
				this.getField('lower').setValue(rec.data['lower']);
				this.getField('upper').setValue(rec.data['upper'], true);
				this.getField('rate').setValue(rec.data['rate']);					
			}
			,getData: function()
			{
				var data = {};					
				data['runMode'] = this.action;
				data['scaleUUID'] = this.scaleUUID;
				data['feeCode'] = this.getField('feeCode').getValue();
				data['deff'] = this.getField('deff').getDisplayDateString();
				data['level'] = this.getField('level').getValue();
				data['lower'] = this.getField('lower').getValue();
				data['upper'] = this.getField('upper').getValue();
				data['rate'] = this.getField('rate').getValue();					
				return data;
			}		
		})								
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
						autoScroll: true
						,height: 600
						,style: 'padding-left:12px; padding-right:10px;overflow-y:auto'						
						,items: [
							{
								layout: 'column'
								,style: 'margin-bottom:10px'
								,defaults: {
									columnWidth: 0.5
								}
								,items: [
									{
										xtype: 'fieldset'
										,style: 'margin-right:3px; padding-left:10px;'
										,title: _translationMap['TrailerFees']
										,items: [
											{
												layout: 'form'
												,labelWidth: 175
												,items: [_fields['trlFeeDate'], _fields['trlGrandFathDate']]
											}
										]
									}
									,{
										xtype: 'fieldset'
										,style: 'margin-left:3px; padding-left:10px;'
										,title: _translationMap['MaturityDays']
										,items: [
											{
												layout: 'form'
												,labelWidth: 200
												,items: [_fields['earlyMatDays'], _fields['sttrMatDays']]
											}
										]
									}	
								]	
							}
							,{
								layout: 'column'
								,style: 'margin-bottom:10px'
								,defaults: {
									columnWidth: 1
								}
								,items: [
									{
										xtype: 'fieldset'
										,style: 'margin-right:0px; padding-left:10px;'
										,title: _translationMap['TransferFee']										
										,items: [
											{
												layout: 'column'
												,defaults:{
													layout: 'form'
												}
												,items: [
													{
														columnWidth: 0.39														
														,labelWidth: 60														
														,items: [_fields['tfrFee']]
													}													
													,{
														columnWidth: 0.30													
														,labelWidth: 60														
														,items: [_fields['tfrFeeRate']]
													}
													,{
														columnWidth: 0.30
														,labelWidth: 60
														,items: [_fields['tfrFeeType']]
													}
													
												]
											}
											,{
												layout: 'column'
												,defaults:{
													layout: 'form'
												}
												,items: [
													{
														columnWidth: 0.39														
														,labelWidth: 60														
														,items: [_fields['howPaid']]
													}													
													,{
														columnWidth: 0.60													
														,labelWidth: 60														
														,items: [_fields['tfrBasedOn']]
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
								,columnWidth: 0.52
								,labelWidth: 60
								,title: _translationMap['TrailerFeeRebate']								
								,items: [_fields['tfRebate']]
							}
							,{
								xtype: 'fieldset'
								,style: 'padding-left:10px;'
								,columnWidth: 0.52
								,labelWidth: 60
								,title: _translationMap['PerfFeeConfig']								
								,id: 'perfFeeFlag_fieldset'
								,items: [_fields['perfFeeFlag']]
							}							
							,new Ext.Container({
								style: 'position: relative'
								,height: 125 
								,hidden: true								
								,id: 'loadtype_container'
								,items: [
									{
										xtype: 'fieldset'								
										,style: 'position:absolute; width:700px'
										,id: 'bel_fieldset'
										,hidden: true
										,hideMode: 'visibility'
										,title: _translationMap['BackEndLoad']
										,items: [
											{
												layout: 'column'
												,defaults: {																						
													layout: 'form'
												}
												,items: [
													{
														columnWidth: 0.38 
														,labelWidth: 125
														,items: [_fields['bel']['feeType']]
													}
													,{												
														columnWidth: 0.62 
														,labelWidth: 95
														,items: [_fields['bel']['basedOn']]
													}
												]
											}
											,{
												layout: 'column'
												,defaults: {																						
													layout: 'form'
												}
												,items: [
													{
														columnWidth: 0.38
														,labelWidth: 125
														,items: [_fields['bel']['brokerComm'], _fields['bel']['dscBasedRate']]
													}
													,{												
														columnWidth: 0.30
														,labelWidth: 95
														,items: [_fields['bel']['withHoldRate'], _fields['bel']['dscOverride']]
													}
													,{												
														columnWidth: 0.32
														,labelWidth: 95
														,items: [_fields['bel']['minVarDsc']]
													}
												]
											}
										]
									}
									,{
										xtype: 'fieldset'
										,style: 'position:absolute;width:700px'
										,id: 'fel_fieldset'
										,hidden: true
										,hideMode: 'visibility'
										,title: _translationMap['FrontEndLoad']
										,items: [
											{
												layout: 'column'
												,defaults: {																						
													layout: 'form'
												}
												,items: [
													{
														columnWidth: 0.37 
														,labelWidth: 125 
														,items: [_fields['fel']['feeType'], _fields['fel']['rate']]
													}
													,{												
														columnWidth: 0.62 
														,labelWidth: 123
														,items: [_fields['fel']['howPaid'], _fields['fel']['basedOn']]
													}
												]
											}
											,{
												layout: 'column'
												,defaults: {																						
													layout: 'form'
												}
												,items: [
													{
														columnWidth: 0.37
														,labelWidth: 125
														,items: [_fields['fel']['maxRate']]
													}
													,{												
														columnWidth: 0.33
														,labelWidth: 123
														,items: [_fields['fel']['minRate']]
													}
													,{												
														columnWidth: 0.30
														,labelWidth: 95
														,items: [_fields['fel']['withHoldRate']]
													}
												]
											}
										]
									}												
								]
							})

							,{
								xtype: 'fieldset'
								,style: 'position:absolute; width:700px; padding-left:10px;margin-top:10px'
								,columnWidth: 0.52
								,title: _translationMap['FeeScales']
								,hidden: true
								,id: 'feeScales_fieldset1'
								,items: []
							}							
							,new Ext.Container({
								style: 'position: relative'
								,height: 153
								,hidden: true								
								,id: 'iwt_container'
								,items: [								
									{
										layout: 'column'
										,style: 'margin-bottom:10px'								
										,items: [
											{
												xtype: 'fieldset'
												,style: 'margin-right:3px; padding-left:10px;'
												,columnWidth: 0.52
												,title: _translationMap['FeeScales']
												,id: 'feeScales_fieldset2'
												,items: []
											}
											,{
												xtype: 'fieldset'
												,style: 'margin-left:3px; padding-left:10px;'
												,title: _translationMap['IWTFee']																				
												,columnWidth: 0.48
												,items: [
													{
														layout: 'form'
														,labelWidth: 170
														,items: [_fields['iwt']['deminimisOpt'], _fields['iwt']['mfrTaxOpt'], _fields['iwt']['deemedDate1'], _fields['iwt']['deemedDate2']]
													}
												]
											}	
										]	
									}							
								]
							})
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