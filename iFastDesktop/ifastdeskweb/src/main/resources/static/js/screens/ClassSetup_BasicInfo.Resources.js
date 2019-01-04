/*********************************************************************************************
 * @file	ClassSetup_BasicInfo.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Basic Information screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  20 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030808 T54932 
 *             - Apply Scrollable when screen reach the maximum of layout 
 *
 *  24 July 2015 Winnie Cheng P0242521 FN01 T81053  R15.5
 *             - Added Prorated Transfer field to support MFS Proportional Transfers
 *             
 *   2 Feb 2015 dchatcha P0248860 CHG0043555 FN01 T82168 R16.3
 *          - Adding a new sub-category "GARS" for Manulife GARS and QROPS Reports
 *
 *  10 July 2016 Winnie Cheng P0255686 FN01 T83008 R16.5
 *          -  Adding a new "Allow Negative Balance" sub-category
 *
 *  22 July 2016 Matira T. P0256538 FN01 T83329 R16.5
 *          -  Adding 2 new sub-category: CustomPayOFnd and PortfolioPayOFnd
 *
 *  08 Nov 2016 Aurkarn M. P0256121 FN01 T84156 R17.2
 *          - Added the logic to show sub-categroy "Target Date Mutual Fund"
 *
 *  05 Sep 2017 Nopphawan H. P0269957 CHG0050809 T86217 R18.1
 *          - Added the logic to show sub-categroy "Multi Managed Funds"
 *
 *  29 Aug 2017 Matira T. P0271575 P0271575-11 R18.1
 *          - Added the logic to show sub-category "Price not required"
 *
 *  18 Oct 2017 Matira T. P0271575 P0271575-21 DFT0078153
 *          - Fix sub-category "Price not required" is not displaying
 *          
 *	07 Nov 2017 Sreejith A P0266789-1286 R18.2
 *          - Added the logic to show sub-categroy "MCH Assets" 
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 800;
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
		fundCode: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['FundCode']									
			,width: 100								
		})	
		,classCode: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['ClassCode']
			,allowBlank: false				
			,width: 100
			,maxLength: 2
		})
		,classE: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['EnglishDescription']					
			,width: 150												
		})	
		,classF: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['FrenchDescription']
			,width: 150
		})
		,deff: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['EffectiveDate']					
			,width: 100
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,statDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['StatusDate']					
			,width: 100
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,stopDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['StopDate']					
			,width: 100
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		,stat: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Status']				
			,name: 'status'
			,width: 125
			,allowBlank: false		
			,lastQuery: ''
			,showCode: true	
		})
		,company: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ESGCompanyCode']
			,width: 150
			,allowBlank: false						
		})
		,loadType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['LoadType']						
			,width: 140
			,allowBlank: false	
            ,showCode: true			
		})
		,inventCat: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['InventoryCategory']						
			,width: 140
			,showCode: true	
		})	
		,bareTrustee: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['BareTrustee']					
			,width: 175	
            ,showCode: true			
		})
		,riskRating: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['RiskRating']						
			,width: 150
			,showCode: true	
		})
		,trackingType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['TrackingType']
			,width: 150
            ,showCode: true
		})	
		,FundCurHldyOpt: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FundClassCurrHoliday']						
			,width: 185						
			,showCode: true	
		})
		,inventTrk_basedOn: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['BasedOn']
			,width: 220  //200
			,showCode: true	
		})
		,inventTrk_applicable: new DesktopWeb.Controls.Checkbox({
			fieldLabel: _translationMap['Applicable']			
			,hideLabel: false			
		})
		,proratedXfer: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ProratedTransfer']		
			,width: 140
			,showCode: true			
		})
		,fundSubCats: {
			'01': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['PrivatePoolFund']
				})
			,'02': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['FundofFund']
				})
			,'03': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['AllocatorFund']
				})
			,'04': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['FlagshipFund']
				})
			,'07': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['InstitutionalFund']
				})
			,'10': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['PoolFunds']
				})
			,'11': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['CorporateClassFunds']
				})
			,'12': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['InterestFund']
				})
			,'14': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['HighInterestInvestmentFund']
				})
			,'15': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['TaxSlipReporting']
				})		
			,'22': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['OEICFunds']
			})
			,'23': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['Section18Report']
			})
			,'24': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['TSReportable']
			})
			,'25': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['GARSFund']
			})
			,'26': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['CustomPayOFnd']
			})
            ,'27': new DesktopWeb.Controls.Checkbox({
					boxLabel: _translationMap['PortfolioPayOFnd']
			})
			,'28': new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['AllowNegativeBalanceFund']
			})
			,'29': new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['TargetDateMutualFnd']
			})
			,'30': new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['MultiManagedFunds']
			})
			,'31': new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['PriceNotRequired']
			})
			,'32': new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['MCHAssets']
			})
		}
		,trfPayFreq: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['TrailerPaymentFrequency']
			,width: 200
            ,showCode: true				
		})
	}
	
	
	// **** grids ****
	var _grids = {		
		fundIdentifier: new DesktopWeb.AdvancedControls.GridPanel(
			{														
				autoScroll: false							
				,height: 105
				,autoExpandColumn: 'idType'									
				,store: new Ext.data.XmlStore(
					{
						record: 'FundIdentifier'					
						,fields: ['runMode', 'idType','idValue', 'fundIDVer', 'fundIDUUID']
						,listeners: {
							load: function(store, records)
							{															
								store.filterBy(function(record){return record.data.runMode != _controller.DEL});																																		
							}
							,update: function(store)
							{								
								store.filterBy(function(record){return record.data.runMode != _controller.DEL});
							}																			
						}			
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){_controller.updateGridActionButtons('fundIdentifier');}
							,rowdeselect: function(){_controller.updateGridActionButtons('fundIdentifier')}
						}
				})				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns: [
						{header: _translationMap['IdType'], id: 'idType', dataIndex: 'idType', renderer: function(value){return value + ' - ' + _controller.getListValueDesc('FundIdentifierList', value)}}
						,{header: _translationMap['IdValue'], dataIndex: 'idValue', width: 300}																		
					]		
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'								
						,text: _translationMap['Add']
						,handler: function(){
							_controller.openPopup('fundIdentifier', _controller.ADD)
						}														
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'								
						,text: _translationMap['Modify']
						,handler: function(){
							_controller.openPopup('fundIdentifier', _controller.MOD)
						}													
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'								
						,text: _translationMap['Delete']
						,handler: function(){
							_controller.openPopup('fundIdentifier', _controller.DEL)
						}													
					})
				]			
			}
		)
		,shareGroup: new DesktopWeb.AdvancedControls.GridPanel({											
				autoScroll: false							
				,height: 105
				,autoExpandColumn: 'groupName'									
				,store: new Ext.data.XmlStore({
					record: 'ShareGroup'					
					,fields: ['shGroup','deff','active', 'grpFundsRID', 'runMode']
					,listeners: {
						load: function(store, records)
						{	
							Ext.each(records, function(record){
								record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							});
								
							store.filterBy(function(record){
								return record.data.runMode != _controller.DEL
							});
						}
						,update: function(store)
						{								
							store.filterBy(function(record){return record.data.runMode != _controller.DEL});
						}																			
					}			
				})
				,selModel: new Ext.grid.RowSelectionModel({					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){_controller.updateGridActionButtons('shareGroup');}
							,rowdeselect: function(){_controller.updateGridActionButtons('shareGroup')}
						}
				})		
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
							menuDisabled: true
						}
						,columns: [							
							{header: _translationMap['GroupName'], id: 'groupName', dataIndex: 'shGroup', renderer: function(value){return _controller.getListValueDesc('ShGroupList', value)}}
							,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width:160}	
							,{header: _translationMap['Active'], dataIndex: 'active', width:160
								, renderer: function(value){
										var tempValue = value.toLowerCase();
										if (tempValue == 'yes')
											value = _translationMap['Yes'];
										else if (tempValue == 'no')
											value = _translationMap['No'];
										return value;
										}
								}
						]		
					}
				)
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'								
						,text: _translationMap['Add']
						,handler: function(){
							_controller.openPopup('shareGroup', _controller.ADD)
						}														
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'								
						,text: _translationMap['Modify']
						,handler: function(){
							_controller.openPopup('shareGroup', _controller.MOD)
						}													
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'								
						,text: _translationMap['Delete']
						,handler: function(){
							_controller.openPopup('shareGroup', _controller.DEL)
						}													
					})
				]			
			}
		)
	}
	
	// **** popups ****
	var _popups = {
		fundIdentifier: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 343
			,action: null						
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center'														
				}						
				,{						
					layout: 'form'
					,labelWidth: 75
					,style: 'padding:4px'																						
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'idType'
							,width: 220
							,fieldLabel: _translationMap['IdType']
							,allowBlank: false	
							,showCode: true
						})											
						,new DesktopWeb.Controls.TextField({
							itemId: 'idValue'
							,width: 100									
							,fieldLabel: _translationMap['IdValue']
							,allowBlank: false														
						})		
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['OK']
						,handler: function(){
							if (_popups['fundIdentifier'].isValid())
							{
								_controller.savePopupData('fundIdentifier', _popups['fundIdentifier'].action, _popups['fundIdentifier'].getData());					
								_controller.closePopup('fundIdentifier');		
							}							
						}	
					}
				)
				,new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['Cancel']
						,handler: function(){_controller.closePopup('fundIdentifier');}
					}
				)
			]
			,init: function(action)
			{										
				this.action = action					
				this.clearAllFields();
				this.get(0).hide(); //hide delete message
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['FundIdentifier']+ ' - ' +_translationMap['Add']);
						this.enableAllFields();																						
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['FundIdentifier']+ ' - ' +_translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();													
						this.getField('idType').disableField();				
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['FundIdentifier']+ ' - ' +_translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['fundIdentifier'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];
				this.getField('idType').setValue(rec.data['idType']);
				this.getField('idValue').setValue(rec.data['idValue']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['idType'] = this.getField('idType').getValue();
				data['idValue'] = this.getField('idValue').getValue();				
				return data;
			}														
		})
		,shareGroup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 310
			,action: null						
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
					,labelWidth: 85																					
					,items: [																
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'shGroup'
							,width: 176 									
							,fieldLabel: _translationMap['GroupName']
							,allowBlank: false	
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'deff'
							,width: 100									
							,fieldLabel: _translationMap['EffectiveDate']
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
							,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
							,allowBlank: false														
						})
						,new DesktopWeb.Controls.YesNoComboBox({
							itemId: 'active'
							,width: 100									
							,fieldLabel: _translationMap['Active']
							,hideLabel: false																				
						})						
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['shareGroup'].isValid())
						{
							_controller.savePopupData('shareGroup', _popups['shareGroup'].action, _popups['shareGroup'].getData());					
							_controller.closePopup('shareGroup');		
						}							
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_controller.closePopup('shareGroup');}
				})
			]
			,init: function(action)
			{										
				this.action = action					
				this.clearAllFields();
				this.get(0).hide(); //hide delete message
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['ShareGroup']+ ' - ' +_translationMap['Add']);
						this.enableAllFields();																													
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['ShareGroup']+ ' - ' +_translationMap['Modify']);
						this.enableAllFields();
						this.getField('shGroup').disableField();											
						this.populateWithSelectedRecord();																						
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['ShareGroup']+ ' - ' + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['shareGroup'].getSelectedRecord();
				this.curRunMode = rec.data['runMode'];				
				this.getField('shGroup').setValue(rec.data['shGroup']);
				this.getField('deff').setValue(rec.data['deff']);				
				this.getField('active').setValue(rec.data['active']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;				
				data['shGroup'] = this.getField('shGroup').getValue();				
				data['deff'] = this.getField('deff').getDisplayDateString();
				data['active'] = this.getField('active').getValue();
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
						style: 'padding-left:12px; padding-right:10px;'
						,autoScroll: false
						,height: 600						
						,items: [
							{
								layout: 'column'																
								,items: [
									{
										layout: 'form'
										,columnWidth: 0.6
										,labelWidth: 165
										,items: [
											_fields['classCode']
											,_fields['classE']											
											,_fields['deff']
											,_fields['bareTrustee']	
											,_fields['company']																					
											,_fields['FundCurHldyOpt']
											,_fields['trfPayFreq']
											,{
												xtype: 'compositefield'
												,fieldLabel: _translationMap['InventoryTracking']												
												,items: [													
													_fields['inventTrk_applicable']													
													,_fields['inventTrk_basedOn']
												]
											}		
																																												
										]
									}
									,{
										layout: 'form'
										,columnWidth: 0.4
										,labelWidth: 120
										,items: [
											_fields['loadType']
											,_fields['classF']
											,_fields['statDate']
											,_fields['stopDate']
											,_fields['stat']
											,_fields['riskRating']
											,_fields['inventCat']
											,new Ext.Container({
												id: 'trackingTypeField'
												,hideMode: 'offsets'
												,hidden: true
												,layout: 'form'	
												,items: [
													_fields['trackingType']
												]
											})
											,_fields['proratedXfer']
										]
									}
								]
							}								
							,{
								xtype: 'fieldset'
								,title: _translationMap['FundSubCategories']
								,style: 'padding-bottom: 0px'																	
								,items: [
									{									
										layout: 'column'
										,style: 'padding-left: 10px'
										,defaults: {
											columnWidth: 0.33
										}
										,items: [
											{
												layout: 'auto'
												,items: [
													_fields.fundSubCats['01']
													,_fields.fundSubCats['04']
													,_fields.fundSubCats['11']
													,_fields.fundSubCats['15']	
													,_fields.fundSubCats['24']
													,_fields.fundSubCats['26']
													,_fields.fundSubCats['30']
												]												
											}
											,{
												layout: 'auto'
												,items: [
													_fields.fundSubCats['02']
													,_fields.fundSubCats['07']
													,_fields.fundSubCats['12']
													,_fields.fundSubCats['22']
													,_fields.fundSubCats['25']
													,_fields.fundSubCats['27']
													,_fields.fundSubCats['31']
												]
											}
											,{
												layout: 'auto'
												,items: [
													_fields.fundSubCats['03']
													,_fields.fundSubCats['10']
													,_fields.fundSubCats['14']
													,_fields.fundSubCats['23']
													,_fields.fundSubCats['28']
													,_fields.fundSubCats['29']
													,_fields.fundSubCats['32']
												]
											}										
										]
										
									}
								]
							}						
							,{
								xtype: 'fieldset'
								,title: _translationMap['FundIdentifiers']																	
								,items: [
									_grids['fundIdentifier']
								]
							}
							,{
								xtype: 'fieldset'
								,title: _translationMap['ShareGroups']																	
								,items: [
									_grids['shareGroup']	
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