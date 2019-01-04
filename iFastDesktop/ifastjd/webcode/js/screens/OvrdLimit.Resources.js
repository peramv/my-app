/*********************************************************************************************
 * @file	OvrdLimit.Resources.js	
 * @author	Rod Walker	
 * @desc	Resources JS file file Fund Limitations Override screen
 *********************************************************************************************/
/*
 * Procedure: OvrdLimit.Resources.js
 *
 * Purpose  : Resources file for Fund Limitations Override screen
 *             
 * Notes    : 
 *
 * History  :  
 *		15 Aug 2013 G. Thawornwachirakun P0193400 T54018
 *					- Add onlyActive param to broker,branch,and slsRep search
 *
 *      06 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54444
 *          		- Correct the format of all date fields based on registry edit
 *                    , called displayMark
 *
 *		21 Nov 2013 Winnie Cheng. P0221029 FN01  T77274
 *					- B-A Rollover rule for stop sysmatic rollover for MFS
 *					- Displaying Broker/Branch/Rep or Account on Add(grid), Modify and Delete window
 *
 *		24 Jan 2014 Narin Suanlamyai. P0224204 FN01 T54714
 *					- Identifying and Reporting NSCC Clearing Firms
 *					- Allow user to setup 'Stop Purchase', 'Stop Redemption', 'Stop Transfer IN',
 *					  and 'Stop Transfer OUT' at branch level.
 *
 *
 *		16 May 2014 Winnie Cheng. P0225761 FN01 T77895
 *					- Allow user to setup 'Stop Purchase/Redemption/TransferIN/TransferOUT at fund group level
 *					- Adding a new validation that preventing Sponser/Fund/Class & FundGroup together
 *					- Loosing BK/BR/RP validation for above rules		
 *
 *		27 April 2015 Winnie Cheng. P0240531 FN01 T80476
 *					- Allow user to setup 'Rounding Rule"	
 *
 *      22-Nov-2016 Zeljko Bajic P0257851 T84326 CHG0047691_MinInvestment
 *                  - Added new implementation as required.
 *
 *      06-Jan-2017 Matira Thanetkulabut P0257853 T84533 Minimum Investment
 *                  - Added amount type field.
 *                  - Added for support new ruleType 66-67.
 *
 *      13-Mar-2017 Matira Thanetkulabut P0260717 T85050 DFT0073213 DFT0073214 DFT0072929 DFT0073225
 *                  - hide currency field for ruleType 66-67.
 *					- hide amounttype and currency field for ruletype 24-29.
 *					- set acctLevel = yes for ruletype ruletype 24-29,66-67.
 *
 *		22-Mar-2017 Matira Thanetkulabut P0257853 T85108 Minimum Investment DFT0073041 DFT0073475 DFT0073489
 *					- added assetLevel, assetType, amountType and currency fields for modify and details popups.
 *					- fixed issues create buy back rule for all level.
 *
 *		10-Apr-2017 Nopphawan Hatthaseriphong P0264164 T85279 Diamond Share Class Restriction
 *					- Added Historical button.
 *                  - Added rule 76, 77, 78 and 79.
 *                  - For Rule 79, the currency field should be displayed if the amount type is “D”.
 *    
 *		25-Apr-2017 Nopphawan Hatthaseriphong P0264164 T85370 Diamond Share Class Restriction
 *					- Removed hard-coding _withCurr, _dayAmt, _withAssetType, _withAssetLevel
 *
 *		28-Jun-2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *					- Add support rule 80 : account level only 
 *          - Add standard listener on combobox to manage data change. 
 *         
 *
 *
 *		4-Jul-2017 Gomoot T. P0268199 CHG0049877 CRM2 Compensation Report T85814
 *					- Add support rule 81 : Broker level only 
 *
 *		30-Aug-2017 Nopphawan Hatthaseriphong P0269734 CHG0050897 T86187 Unit Calculation Method Override
 *                  - Added new rule type '83 - Unit Calculation Method'
 *    
 *      02-Feb-2018 Matira Thanetkulabut P0274833-5 NCO - HKB WSDF Create Bulk Transactions as wire (T+2)
 *					- Added new rule 84 - Wire Order Trade 
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 600;
	var _layoutWidth = 740;
	
	// **** fields ****
	var _fields = {
		ruleType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['RuleType']
			,width: 305				
			,allowBlank: false
			,listeners: {
				select: function(combo, record, index){_controller.handleRuleTypeSrchChange(record.data.code); }
			}
		})
		,broker: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Broker']
			,smartview: 'brokerSearch'
			,addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'yes';}}]
			,fields: ['displayValue', 'agencyCode']
			,valueField: 'agencyCode'
			,width: 600
			,allowBlank: false
			,listeners:{
				populated: function(){_fields['branch'].enable();}
				,cleared: function(){
					_fields['branch'].reset(); _fields['branch'].disable();
					_fields['slsrep'].reset(); _fields['slsrep'].disable();	
				}
			}//listeners
		})

		,branch: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Branch']
			,smartview: 'branchSearch'
			,fields: ['displayValue', 'branch']
			,addtlSearchParams: [
				{name: 'agencyCode', valueFn: function(){return _fields['broker'].getValue();}}
				,{name: 'onlyActive', valueFn: function(){return 'yes';}}
			]
			,valueField: 'branch'
			,width: 600
			,disabled: true
			,allowBlank: false
			,listeners:{
				populated: function(){_fields['slsrep'].enable();}
				,cleared: function(){_fields['slsrep'].reset(); _fields['slsrep'].disable();}
			}				
		})

		,slsrep: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['SalesRep']
			,smartview: 'salesRepSearch'				
			,fields: ['displayValue', 'agentCode']
			,addtlSearchParams: [
				{name: 'agencyCode', valueFn: function(){return _fields['broker'].getValue();}}
				,{name: 'branch', valueFn: function(){return _fields['branch'].getValue();}}
				,{name: 'onlyActive', valueFn: function(){return 'yes';}}
			]
			,valueField: 'agentCode'
			,width: 600
			,disabled: true
			,allowBlank: false
		})

		,accountNum: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Account']
			,width: 300
		})

		,fundSponsor: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FundSponsor']
			,width: 150
			,setComponent : function( value ) {       
				if (!!value && value != '' ) {
					_fields['fundGroup'].clearValue(); _fields['fundGroup'].disable();
				} else {
					_fields['fundGroup'].enable();	
				}
			}
			,listeners:{	
				 select:  function(combo, record, index) {this.setComponent(record.data.code);}
				,cleared: function (fld) {this.setComponent(fld.getRawValue());} 
				,change : function (fld) { this.setComponent(fld.getValue());} 
			}			
		})

		,fund: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Fund']
			,smartview: 'fundSearch'				
			,fields: ['displayValue', 'fund', 'class']
			,valueField: 'displayValue'
			,addtlSearchParams: [
				{name: 'fundSponsor', valueFn: function(){return _fields['fundSponsor'].getValue();}}
				,{name: 'showAllClassRecords', valueFn: function(){return 'yes';}}
			]	
			,width: 455
			,setComponent : function( value ) {       
				if (!!value) {
					_fields['classCode'].clearValue();  _fields['classCode'].disable()
					_fields['fundGroup'].clearValue();  _fields['fundGroup'].disable()
				} else {
					_fields['classCode'].enable();
				  _fields['fundGroup'].enable()	;
				}
			}
			,listeners:{
				select: function(combo, record, index) {this.setComponent(combo.getValue());}
				,cleared: function(){this.setComponent();}
				,change: function(fld, newValue, oldValue){this.setComponent(newValue);}
			}
		})
		
		,classCode: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Class']
			,width: 70
			,setComponent : function( value ) {
				if (!!value && value != '' ) {
					_fields['fundGroup'].clearValue();_fields['fundGroup'].disable();
				} else {
				  _fields['fundGroup'].enable()	;
				}
			}
			,listeners:{
				select:  function(combo, record, index) {this.setComponent(record.data.code);}				
				,cleared : function (fld) { this.setComponent(fld.getRawValue());} 
				,change : function (fld) { this.setComponent(fld.getValue());} 

			}				
		})

		,fundGroup: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FundGroup']
			,width: 150
			,setComponent : function( value ) {
				if (!!value) {
					_fields['fundSponsor'].clearValue(); _fields['fundSponsor'].disable();
					_fields['fund'].clearValue();        _fields['fund'].disable();
					_fields['classCode'].clearValue();   _fields['classCode'].disable();
				} else {
					_fields['fundSponsor'].enable();
					_fields['fund'].enable();
					_fields['classCode'].enable();	
				}
			}
			,listeners:{
				 select:  function(combo, record, index) {this.setComponent(record.data.code);}
				,cleared : function (fld) { this.setComponent(fld.getRawValue());}  //keyup   
				,change : function (fld) { this.setComponent(fld.getValue());} 				
			}					
		})

		,showOnlyActiveRecords: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['ShowOnlyActiveRecords']
		})					
	}
	
	// **** grids ****
	var _grids = {
		ovrdRules: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth - 12				
			,autoScroll: true							
			,height: 400
			,autoExpandColumn: 'ruleType'
			,store: new Ext.data.XmlStore({
				record: 'tPendingRule'					
				,fields: [
					'Account', 'Fund', 'Class', 'RuleType', 'OverrideAmt', 'OverrideLog', 
					'OverrideChar', 'StopDate', 'StartDate', 'OnlineEWI', 'onlineEWIDesc', 
					'CycleEWI', 'cycleEWIDesc', 'ESGEWI', 'esgEWIDesc', 'ProcessDate', 'ModDate', 
					'UserName', 'ModUser', 'Version', 'ControlsID', 'FundGroup', 'dispAmt', 
					'RuleStatus', 'ruleDesc', 'startDateChar', 'stopDateChar', 'ruleDataType', 
					'fundSponsor', 'UpdateStatus', 'ovrdCharDesc', 'BrokerControlsID', 'errorDesc',
					'reasonCode','reasonCodeDesc','verifyStatus','verifyStatusDesc', 'sameUser','modEnable', 'AmountType',
					'Currency', 'AssetLevel', 'AssetType'
				]							
			,listeners: {
				load: function(store, records)
				{
					Ext.each(records, function(record){
						record.data.StartDate = DesktopWeb.Util.getDateDisplayValue(record.data.StartDate);
						record.data.StopDate = DesktopWeb.Util.getDateDisplayValue(record.data.StopDate);
						record.data.startDateChar = DesktopWeb.Util.getDateDisplayValue(record.data.startDateChar);
						record.data.stopDateChar = DesktopWeb.Util.getDateDisplayValue(record.data.stopDateChar);
						record.data.ProcessDate = DesktopWeb.Util.getDateDisplayValue(record.data.ProcessDate);
						record.data.ModDate = DesktopWeb.Util.getDateDisplayValue(record.data.ModDate);
					});
					store.fireEvent('datachanged', store); //to set data in grid again
				}
			}
			})
			,selModel: new Ext.grid.RowSelectionModel({		
				singleSelect: true
				,listeners: {
					rowselect: function(){_controller.updateActionButtons();}
					,rowdeselect: function(){_controller.updateActionButtons();}
				}												
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [										
					{id: 'ruleType', header: _translationMap['RuleType'], dataIndex: 'RuleType', renderer: function(value){return value + " - " + _controller.getListDesc('RuleTypeOptions', value)}, width:140}
					,{header: _translationMap['Fund'], dataIndex: 'Fund', width:80}
					,{header: _translationMap['Class'], dataIndex: 'Class', width:60}
					,{header: _translationMap['FundGroup'], dataIndex: 'FundGroup', width:85}
					,{header: _translationMap['FundSponsor'], dataIndex: 'fundSponsor', width:85}					
					,{header: _translationMap['StartDate'], dataIndex: 'startDateChar', width:80}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDateChar', width:80}																		
				]							
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup(_controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton(		{
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD);}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup(_controller.DEL);}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'stopBtn'
					,text: _translationMap['StopLimitations']
					,handler: function(){_controller.doStopLimitations();}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['AdminDates']
					,handler: function(){_controller.openAdminPopup();}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'detlsBtn'
					,text: _translationMap['Details']
					,handler: function(){_controller.openDetailsPopup();}
					,disabled: true
				})							
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,handler: function(){_controller.doReload(true)}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
		            itemId: 'historicalBtn'
		            ,text: _translationMap['Historical']
		            ,handler: function() {_controller.openHistoryPopup();}
				    ,disabled: true
		        })
			]
		})				

		,addRules: new DesktopWeb.AdvancedControls.GridPanel({							
			width: 586				
			,autoScroll: true							
			,height: 123														
			,store: new Ext.data.XmlStore(
				{
					record: 'tPendingRule'					
					,fields: [
						'Account', 'Fund', 'Class', 'RuleType', 'OverrideAmt', 'OverrideLog', 
						'OverrideChar', 'StopDate', 'StartDate', 'OnlineEWI', 'onlineEWIDesc', 
						'CycleEWI', 'cycleEWIDesc', 'ESGEWI', 'esgEWIDesc', 'ProcessDate', 'ModDate', 
						'UserName', 'ModUser', 'Version', 'ControlsID', 'FundGroup', 'dispAmt', 
						'ruleDesc', 'RuleStatus', 'startDateChar', 'stopDateChar', 'ruleDataType', 
						'fundSponsor', 'ovrdCharDesc', 'UpdateStatus', 'errorDesc', 'reasonCode','reasonCodeDesc'
						,'verifyStatus','assetLevel','assetType','currency','amountType'
					]							
					,listeners: {
						load: function(store, records)
						{
							Ext.each(records, function(record){
								record.data.StartDate = DesktopWeb.Util.getDateDisplayValue(record.data.StartDate);
								record.data.StopDate = DesktopWeb.Util.getDateDisplayValue(record.data.StopDate);
								record.data.startDateChar = DesktopWeb.Util.getDateDisplayValue(record.data.startDateChar);
								record.data.stopDateChar = DesktopWeb.Util.getDateDisplayValue(record.data.stopDateChar);
								record.data.ProcessDate = DesktopWeb.Util.getDateDisplayValue(record.data.ProcessDate);
								record.data.ModDate = DesktopWeb.Util.getDateDisplayValue(record.data.ModDate);
							});
							store.fireEvent('datachanged', store); //to set data in grid again
						}
					}
				}
			)
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true														
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [
					{header: '',renderer: _controller.renderUpdateStatus, width: 27}
					,{header: _translationMap['RuleType'], dataIndex: 'RuleType', renderer: function(value){return _controller.getListDesc('RuleTypeOptions', value)}, width:140} 
					,{header: _translationMap['Account'], dataIndex: 'account', renderer: function(){return _fields['accountNum'].getValue();}, width:90}	
					,{header: _translationMap['Broker'], dataIndex: 'broker', renderer: function(){return _fields['broker'].getRawValue();}, width:90}	
					,{header: _translationMap['Branch'], dataIndex: 'branch', renderer: function(){return _fields['branch'].getRawValue();}, width:90}	
					,{header: _translationMap['SalesRep'], dataIndex: 'slsrep', renderer: function(){return _fields['slsrep'].getRawValue();}, width:90}		
					,{header: _translationMap['FundSponsor'], dataIndex: 'fundSponsor', width:90}
					,{header: _translationMap['Fund'], dataIndex: 'Fund', width:80}
					,{header: _translationMap['Class'], dataIndex: 'Class', width:50}
					,{header: _translationMap['FundGroup'], dataIndex: 'FundGroup', width:100}
					,{header: _translationMap['StartDate'], dataIndex: 'startDateChar', width:70}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDateChar', width:70}
					,{header: _translationMap['OverrideValue'], renderer: _controller.renderOverrideValue, width:100}
					,{header: _translationMap['OnlineEWI'], dataIndex: 'onlineEWIDesc', width:70}
					,{header: _translationMap['CycleEWI'],dataIndex: 'cycleEWIDesc' , width:70}
					,{header: _translationMap['ESGEWI'],dataIndex: 'esgEWIDesc', width:70}
					,{header: _translationMap['AssetLevel'], dataIndex: 'assetLevel', renderer: function() { return _popups['add'].getField('assetLevel').getValue(); }, width: 90 }
					,{header: _translationMap['AssetType'], dataIndex: 'assetType', renderer: function() { return _popups['add'].getField('assetType').getValue(); }, width: 90 }
					,{header: _translationMap['Currency'], dataIndex: 'currency', renderer: function() { return _popups['add'].getField('currency').getValue(); }, width: 90 }
					,{header: _translationMap['AmountType'], dataIndex: 'amountType', renderer: function() { return _popups['add'].getField('amountType').getValue(); }, width: 90 }
				]
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'commitBtn'								
					,text: _translationMap['Commit']
					,handler: function(){_controller.doAddCommit();}														
				})											
			]
		})				
	}
	
	// **** popups ****
	var _popups = {		
		add: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 630
			,height: 630
			,modal: true
			,title: _translationMap['OverrideLimitationRule'] + " - " + _translationMap['Add']
			,defaults: {border:false}
			,bodyStyle: 'padding:4px;'
			,listeners: {
				show: function(){_popups['add'].init();}
			}	
			,items: [									
				{
					layout: 'form'
					,labelWidth: 95
					,items: [
						new DesktopWeb.Controls.ComboBox({
							itemId: 'ruleType'
							,fieldLabel: _translationMap['RuleType']
							,width: 305
							,allowBlank: false
							,valueField: 'code'
							,displayField: 'value'
							,store: new Ext.data.XmlStore({
													record: 'Element',
													fields: ['code', 'value', 'currency', {name : 'override' , mapping : 'code > @override'}]
	                        })
							,listeners: {
								select: function(){_controller.handleAddRuleTypeChange();}
								,change: function(fld, newValue)
								{
									if (newValue == "")
									{
										_controller.handleAddRuleTypeChange()
									}
								}
							}								
						})
					]
				}					
				,{
					layout: 'column'
					,defaults: {border: false, labelWidth: 95, columnWidth: .5, layout: 'form'}
					,items: [
						{
							items: [
								new DesktopWeb.Controls.DateField({
									itemId: 'startDate'
									,fieldLabel: _translationMap['StartDate']
									,allowBlank: false
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
							]
						}
						,{								
							items: [
								new DesktopWeb.Controls.DateField({
									itemId: 'stopDate'
									,fieldLabel: _translationMap['StopDate']
									,allowBlank: false
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
							]
						}
					]
				}
				,{
					layout: 'form'
					,labelWidth: 95
					,items: [						
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'listBasedOn'									
							,fieldLabel: _translationMap['ListBasedOn']
							,width: 180
							,hideMode: 'offsets'
							,listeners:{
								select: function(){_controller.handleAddListBasedOnChange()}				
								,change: function(fld, newValue)
								{
									if (newValue == "")
									{
										_controller.handleAddListBasedOnChange()
									}
								}				
							}							
							,validator: function(value){		
								if (_popups['add'].getField('listBasedOn').isVisible()									
									&& value == ''
									&& _popups['add'].getField('ruleType').getValue() != '51' && _popups['add'].getField('ruleType').getValue() != '47'
									&& _popups['add'].getField('ruleType').getValue() != '01' && _popups['add'].getField('ruleType').getValue() != '65'
									&& _popups['add'].getField('ruleType').getValue() != '84')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}	
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'fundSponsor'									
							,fieldLabel: _translationMap['FundSponsor']
							,width: 180
							,validator: function(value){		
								if (_popups['add'].getField('fundSponsor').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}						
						})
						,new DesktopWeb.Controls.SuggestField({
							fieldLabel: _translationMap['Fund']
							,itemId: 'fundCode'
							,width: 455
							,smartview: 'fundSearch'				
							,fields: ['displayValue', 'fund', 'class']						
							,valueField: 'displayValue'												
							,addtlSearchParams: [
								{name: 'fundSponsor', valueFn: function(){return _fields['fundSponsor'].getValue();}}
								,{name: 'showAllClassRecords', valueFn: function(){return 'yes';}}
							]	
							,validator: function(value){		
								if (_popups['add'].getField('fundCode').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}			
						})
						,new DesktopWeb.Controls.SMVComboBox({									
							fieldLabel: _translationMap['Class']
							,itemId: 'classCode'
							,width:180
							,validator: function(value){		
								if (_popups['add'].getField('classCode').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}					
						})
						,new DesktopWeb.Controls.SMVComboBox({									
							fieldLabel: _translationMap['FundGroup']
							,width: 180
							,itemId: 'fundGroup'
							,validator: function(value){		
								if (_popups['add'].getField('fundGroup').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}						
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'overrideAmt'
							,width: 180
							,fieldLabel: _translationMap['OverrideValue']
							,validator: function(value){
								if (_popups['add'].getField('overrideAmt').isVisible())
								{
									if (value == '')
									{
										return _translationMap['FldRequired'];
									}
									else if (_popups['add'].getField('ruleType').getValue() == '52'
										&& value != 1.00 && value != 0)
									{
										return _translationMap['Rule52ValidationMsg']										
									}
								}
								return true;
							}
						})
						,new DesktopWeb.Controls.YesNoComboBox({
							itemId: 'overrideLog'		
							,width: 180
							,fieldLabel: _translationMap['OverrideValue']
							,validator: function(value){		
								if (_popups['add'].getField('overrideLog').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}							
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'overrideChar'
							,width: 230
							,fieldLabel: _translationMap['OverrideValue']					
							,validator: function(value){		
								if (_popups['add'].getField('overrideChar').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}							
						})						
						,new DesktopWeb.Controls.SMVComboBox({											
							itemId: 'eligible'									
							,fieldLabel: _translationMap['Eligible']
							,width: 180
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'responsibility'									
							,fieldLabel: _translationMap['Responsibility']
							,width: 180
							,listeners:{
								select: function(){_controller.handleResponsibilityChange(_popups['add'])}
								,change: function(fld, newValue)
								{
									if (newValue == "")
									{
										_controller.handleResponsibilityChange(_popups['add']);
									}
								}
							}
							,validator: function(value){		
								if (_popups['add'].getField('responsibility').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}																		
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'kiidAttested'									
							,fieldLabel: _translationMap['KIIDAttestedWaived']
							,width: 180
							,listeners:{
								select: function(fld){
									_popups['add'].getField('reason').reset();
									if (fld.getValue() == 'W')
									{
										_popups['add'].getField('reason').show();
									}
									else
									{
										_popups['add'].getField('reason').hide();
									}
								}
							}
							,validator: function(value){		
								if (_popups['add'].getField('kiidAttested').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}																
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'reason'									
							,fieldLabel: _translationMap['Reason']
							,width: 180
						})	
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'rdrAdvice'									
							,fieldLabel: ""
							,width: 180
							,listeners: {
								change: function(){
									if (_controller.IS_ACCOUNT_LEVEL)
									{
										DesktopWeb.Util.displayWarning(_translationMap['RDRAcctModifyWarning']);
									}									
								}
							}
							,validator: function(value){		
								if (_popups['add'].getField('rdrAdvice').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'verifystatus'									
							,fieldLabel: _translationMap['VerifyStatus']
							,width: 180
							,disabled: true
							,listeners: {
								change: function(){
									if (_controller.IS_ACCOUNT_LEVEL)
									{
										//DesktopWeb.Util.displayWarning(_translationMap['RDRAcctModifyWarning']);
									}									
								}
							}
							,validator: function(value){		
								if (_popups['add'].getField('verifystatus').isVisible()
									&& value == '')
								{
									return _translationMap['FldRequired'];
								}
								return true;
							}
						})
						, new DesktopWeb.Controls.SMVComboBox({
						    itemId: 'assetLevel'
							, fieldLabel: _translationMap['AssetLevel']
							, width: 180
						})
						, new DesktopWeb.Controls.SMVComboBox({
						    itemId: 'assetType'
							, fieldLabel: _translationMap['AssetType']
							, width: 180
						})
						, new DesktopWeb.Controls.SMVComboBox(
						{
							itemId: 'amountType'
							, fieldLabel: _translationMap['AmountType']
							, width: 180
							, listeners: {
								select: function(fld){
									_popups['add'].setCurrField();
								}
							}
						})
						, new DesktopWeb.Controls.SMVComboBox({
						    itemId: 'currency'
							, fieldLabel: _translationMap['Currency']
							, width: 180
						})
					]
				}																					
				,{
					layout: 'column'																											
						,defaults: {border: false, labelWidth: 95, columnWidth: .5}								
						,items: [
							{			
								layout: 'form'
								,items: [
									new DesktopWeb.Controls.SMVComboBox({											
										itemId: 'onlineEWI'									
										,fieldLabel: _translationMap['OnlineEWI']
										,width: 85
										,allowBlank: false                  
									})
									,new DesktopWeb.Controls.SMVComboBox({
										itemId: 'cycleEWI'									
										,fieldLabel: _translationMap['CycleEWI']
										,width: 85
										,allowBlank: false
									})	
									,new DesktopWeb.Controls.SMVComboBox({
										itemId: 'esgEWI'									
										,fieldLabel: _translationMap['ESGEWI']
										,width: 85
										,allowBlank: false                  
									})																																																								
								]
							}
							,{
								bodyStyle: 'height:90px'	
								,defaults: {layout: 'auto'}				
								,items: [
									new Ext.form.Label({																														
										html: '<div style="padding-bottom:5px">' + _translationMap['IfExistingRuleFound'] + '</div>'
										,itemId: 'radioLabel'
									})
									,new DesktopWeb.Controls.Radio({
										boxLabel: _translationMap['ExcludeFromUpdate']
										,itemId: 'excludeRule'
										,name: 'existingRuleOpt'
										,checked: true
									})
									,new DesktopWeb.Controls.Radio({
										boxLabel: _translationMap['StopExistingRule']
										,itemId: 'stopRule'
										,name: 'existingRuleOpt'
									})
									,new DesktopWeb.Controls.ActionButton({
										text: _translationMap['Lookup']
										,id: 'lookupBtn'
										,style: 'position:absolute; top: 62px; right:64px'
										,handler: function()
										{
											if (_popups['add'].isValid())
											{
												_controller.doAddLookup();
											}
										}								
									})
									,new DesktopWeb.Controls.ActionButton({
										text: _translationMap['Reset']
										,id: 'resetLookupBtn'
										,style: 'position:absolute; top: 62px; right:0px'
										,handler: function(){_popups['add'].reset();}
									})
								]
							}																	
						]
					}
				,{
					xtype: 'fieldset'
					,border: true
					,title: _translationMap['PendingUpdates']
					,width: 598
					,items: _grids['addRules']
					,style: 'padding-bottom:0px;'
				}								
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Done']
					,handler: function(){_popups['add'].hide();}							
				})					
			]
			,init: function()
			{		
				this.enableAllFields();
				var searchRuleType = _fields['ruleType'].getValue();			
				 _grids['addRules'].clearData();
				this.getField('ruleType').reset();        				
				_controller.handleEWIForRule(searchRuleType,this);

				_popups['add'].getField('verifystatus').hide();				
				_popups['add'].getField('verifystatus').setValue('02'); //Unverified

				if (searchRuleType.toUpperCase() != 'ALL') {
					this.getField('ruleType').setValue(searchRuleType);
					this.getField('ruleType').disableField();
				}
				else
				{
					this.getField('ruleType').enableField();
				}
				_controller.handleAddRuleTypeChange();
				
				//Set Default value on add popup screen
				this.getField('startDate').setValue(_controller.getDefaultValue('startDate'));
				this.getField('stopDate').setValue(_controller.getDefaultValue('stopDate'));
				this.getField('onlineEWI').setValue('E');
				this.getField('cycleEWI').setValue('E');
				this.getField('esgEWI').setValue('E');
				
				Ext.getCmp('lookupBtn').enable();
				Ext.getCmp('resetLookupBtn').disable();
			}
			,reset: function()
			{				
				this.init();
			}
			,setCurrField: function()
			{
				var ruleType = _popups['add'].getField('ruleType').getValue();

				if(_popups['add'].getField('amountType').getValue() == 'D'){
					_popups['add'].getField('currency').show();
				}
				// Amounttype is Units or not show currency field
				else{
					_popups['add'].getField('currency').reset();
					_popups['add'].getField('currency').hide();
				}
				
				// render popup
				if (_popups['add'].rendered)
					_popups['add'].syncShadow();
			}
		})	
		
		,modify: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 600
			,modal: true
			,title: _translationMap['OverrideLimitationRule'] + ' - ' + _translationMap['Modify']
			,defaults: {border:false}
			,bodyStyle: 'padding:4px;'
			,listeners: {
				show: function(){this.init();}
			}
			,items: [
				{
					layout: 'column'																											
					,defaults: {border: false, layout: 'form'}
					,items: [					
						{	
							columnWidth: .62
							,labelWidth: 100		
							,items: [
								new DesktopWeb.Controls.Label({
									itemId: 'ruleType'									
									,fieldLabel: _translationMap['RuleType']
								})
								,new DesktopWeb.Controls.DateField({
									itemId: 'stopDate'
									,fieldLabel: _translationMap['StopDate']
									,allowBlank: false									
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
								, new DesktopWeb.Controls.SMVComboBox({
									itemId: 'assetLevel'
									, fieldLabel: _translationMap['AssetLevel']
									, width: 180
								})
								, new DesktopWeb.Controls.SMVComboBox({
									itemId: 'assetType'
									, fieldLabel: _translationMap['AssetType']
									, width: 180
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'overrideAmt'
									,width: 100
									,hidden: true									
									,fieldLabel: _translationMap['OverrideValue']
									,validator: function(value){
										if (_popups['modify'].getField('overrideAmt').isVisible())
										{
											if (value == '')
											{
												return _translationMap['FldRequired'];
											}
											else if (_popups['add'].getField('ruleType').getValue() == '52'
												&& value != 1.00 && value != 0)
											{
												return _translationMap['Rule52ValidationMsg']												
											}
										}
										return true;
									}
								})
								, new DesktopWeb.Controls.SMVComboBox(
								{
									itemId: 'amountType'
									, fieldLabel: _translationMap['AmountType']
									, width: 180
									, listeners: {
										select: function(fld){
											_popups['modify'].setCurrField();
										}
									}
								})
								, new DesktopWeb.Controls.SMVComboBox({
									itemId: 'currency'
									, fieldLabel: _translationMap['Currency']
									, width: 180
								})
								,new DesktopWeb.Controls.YesNoComboBox({
									itemId: 'overrideLog'
									,hidden: true
									,fieldLabel: _translationMap['OverrideValue']
									,validator: function(value){		
										if (_popups['modify'].getField('overrideLog').isVisible()
											&& value == '')
										{
											return _translationMap['FldRequired'];
										}
										return true;
									}							
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'overrideChar'
									,width: 230
									,hidden: true
									,fieldLabel: _translationMap['OverrideValue']
									,validator: function(value){		
										if (_popups['modify'].getField('overrideChar').isVisible()
											&& value == '')
										{
											return _translationMap['FldRequired'];
										}
										return true;
									}									
								})						
								,new DesktopWeb.Controls.SMVComboBox({											
									itemId: 'eligible'									
									,fieldLabel: _translationMap['Eligible']
									,hidden: true
									,width: 100
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'responsibility'									
									,fieldLabel: _translationMap['Responsibility']
									,width: 100
									,hidden: true
									,listeners:{
										select: function(){_controller.handleResponsibilityChange(_popups['modify'])}
										,change: function(fld, newValue)
										{
											if (newValue == "")
											{
												_controller.handleResponsibilityChange(_popups['modify']);
											}
										}
									}
									,validator: function(value){		
										if (_popups['modify'].getField('responsibility').isVisible()
											&& value == '')
										{
											return _translationMap['FldRequired'];
										}
										return true;
									}														
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'kiidAttested'									
									,fieldLabel: _translationMap['KIIDAttestedWaived']
									,width: 100
									,hidden: true
									,listeners:{
										select: function(fld, record)										
										{
											_popups['modify'].getField('reason').reset();
											if (record.data.code == 'W')
											{
												_popups['modify'].getField('reason').show();
												if (_popups['modify'].rendered)
													_popups['modify'].syncShadow();
											}
											else
											{
												_popups['modify'].getField('reason').hide();
												if (_popups['modify'].rendered)
													_popups['modify'].syncShadow();
											}
										}
									}
									,validator: function(value){		
										if (_popups['modify'].getField('kiidAttested').isVisible()
											&& value == '')
										{
											return _translationMap['FldRequired'];
										}
										return true;
									}
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'reason'									
									,fieldLabel: _translationMap['Reason']
									,width: 250
									,hidden: true
									,validator: function(value){		
										if (_popups['modify'].getField('reason').isVisible()
											&& value == '')
										{
											return _translationMap['FldRequired'];
										}
										return true;
									}	
								})
								,new DesktopWeb.Controls.SMVComboBox({											
									itemId: 'tmpOver'		//Hidden variable to store OverideChar in cache							
									,hidden: true
								})	
								,new DesktopWeb.Controls.SMVComboBox({											
									itemId: 'tmpReasonCode'	//Hidden variable to store ReasonCode in cache							
									,hidden: true
								})			
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'rdrAdvice'									
									,fieldLabel: ""
									,hidden: true									
									,width: 180
									,listeners: {										
										change: function(){
											if (_controller.IS_ACCOUNT_LEVEL)
											{
												DesktopWeb.Util.displayWarning(_translationMap['RDRAcctModifyWarning']);
											}
											else
											{
												DesktopWeb.Util.displayWarning(_translationMap['RDRBrkModifyWarning']);	
											}
										}
									}
									,validator: function(value){		
										if (_popups['modify'].getField('rdrAdvice').isVisible()
											&& value == '')
										{
											return _translationMap['FldRequired'];
										}
										return true;
									}			
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'verifystatus'									
									,fieldLabel: _translationMap['VerifyStatus']
									,width: 150
									,disabled: true
									,listeners: {
										change: function(){
											if (_controller.IS_ACCOUNT_LEVEL)
											{
												//DesktopWeb.Util.displayWarning(_translationMap['RDRAcctModifyWarning']);
											}									
										}
									}
									,validator: function(value){		
										if (_popups['modify'].getField('verifystatus').isVisible()
											&& value == '')
										{
											return _translationMap['FldRequired'];
										}
										return true;
									}
								})	//B-A
								,new DesktopWeb.Controls.Label({
									itemId: 'broker'
									,fieldLabel: _translationMap['Broker']
								})	
								,new DesktopWeb.Controls.Label({
									itemId: 'branch'
									,fieldLabel: _translationMap['Branch']
								})	
								,new DesktopWeb.Controls.Label({
									itemId: 'slsrep'
									,fieldLabel: _translationMap['SalesRep']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'accountNum'
									,fieldLabel: _translationMap['Account']
								})
							]
						}
						,{
							columnWidth: .38
							,labelWidth: 80
							,items: [
								new DesktopWeb.Controls.SMVComboBox({											
									itemId: 'onlineEWI'
									,width: 100
									,allowBlank: false
									,fieldLabel: _translationMap['OnlineEWI']
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'cycleEWI'
									,width: 100
									,allowBlank: false
									,fieldLabel: _translationMap['CycleEWI']
								})	
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'esgEWI'
									,width: 100
									,allowBlank: false
									,fieldLabel: _translationMap['ESGEWI']
								})							
							]
						}																	
					]
				}			
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['modify'].isValid()
							&& _controller.doUpdate(_controller.MOD, _popups['modify'].getData()))
						{
							_popups['modify'].hide();
						}
					}								
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['modify'].hide();}					
				})
			]			
			,init: function()
			{																			
				this.clearAllFields();
				this.getField('stopDate').enable();
				var rec = _grids['ovrdRules'].getSelectedRecord();	
				
				this.getField('tmpOver').setValue(rec.data['OverrideChar']);
				this.getField('tmpReasonCode').setValue(rec.data['reasonCode']);

				var ruleType = rec.data['RuleType'];
				var dataType = _controller.getRuleDataType(ruleType)

				this.getField('ruleType').setValue(ruleType + " - " + _controller.getListDesc('RuleTypeOptions', ruleType));
				this.getField('stopDate').setValue(rec.data['stopDateChar']);
				this.getField('onlineEWI').setValue(rec.data['OnlineEWI']);
				this.getField('cycleEWI').setValue(rec.data['CycleEWI']);
				this.getField('esgEWI').setValue(rec.data['ESGEWI']);
				this.getField('broker').setValue(_fields['broker'].getRawValue());
				this.getField('branch').setValue(_fields['branch'].getRawValue());
				this.getField('slsrep').setValue(_fields['slsrep'].getRawValue());
				this.getField('accountNum').setValue(_fields['accountNum'].getValue());
				
				// need to dynamic displaying broker/branch/rep info
				_controller.handleEWIForRule(ruleType, this); 
				
				this.getField('verifystatus').setValue(rec.data['verifyStatus'])
				this.getField('verifystatus').hide();

				var conditionalFields = ['overrideAmt', 'overrideLog', 'overrideChar', 'eligible', 'responsibility',
					'reason', 'kiidAttested', 'rdrAdvice', 'amountType', 'currency', 'assetLevel', 'assetType'];

				for (var i = 0; i < conditionalFields.length; i++)
				{
					this.getField(conditionalFields[i]).reset();
					this.getField(conditionalFields[i]).hide();
				}	
				
				_controller.setListByRuleType(this, "AssetLevelList" + ruleType, 'assetLevel');
				_controller.setListByRuleType(this, "AssetTypeList" + ruleType, 'assetType');
				
				this.getField('assetLevel').setValue(rec.data['AssetLevel']);
				this.getField('assetType').setValue(rec.data['AssetType']);

		        		
				if (dataType == 'overrideDec') {
					this.getField('overrideAmt').setValue(rec.data['OverrideAmt']);
					this.getField('overrideAmt').show();
					
					_controller.setListByRuleType(this, "AmountTypeList" + ruleType, 'amountType');
					this.getField('amountType').setValue(rec.data['AmountType']);
					
					if (this.getField('amountType').store.getCount() == 1) {
		            	this.getField('amountType').disable();
		      }
					
					this.setCurrField();
				}
				else if (dataType == 'overrideLog')
				{
					_controller.setOverrideLogFieldForRule(ruleType,this); //Set logic value & non-editable 
					
					this.getField('overrideLog').setValue(rec.data['OverrideLog']);
					this.getField('overrideLog').show();
				}
				else if (dataType == 'overrideChar')
				{
					if (_controller.overrideCharList.indexOf(ruleType) >= 0)
					{					
						this.getField('overrideChar').loadData(_controller.getList('OverrideListRule' + ruleType));
						this.getField('overrideChar').setValue(rec.data['OverrideChar']);
						this.getField('overrideChar').show();
					}
					else if (ruleType == '51')
					{
						this.getField('stopDate').disable();
						this.getField('verifystatus').show();
						//Enable the Verify status drop down only if it is different user
						if(rec.data['sameUser'] =='N')
						{
							this.getField('verifystatus').enable();
						}
						else 
						{
							this.getField('verifystatus').disable();
						}
						if (_controller.IS_ACCOUNT_LEVEL)
						{							
							if (_controller.IS_PERSISTENT)
							{
								this.getField('kiidAttested').loadData(_controller.getList('KIIDComboList'));
							}
							else
							{
								if (rec.data['Class'] != "")
								{
									this.getField('kiidAttested').loadData(_controller.getList('KIIDAttestationList'));
								}
								else
								{
									this.getField('kiidAttested').loadData(_controller.getList('KIIDWaiverList'));							
								}
							}							
							this.getField('kiidAttested').setValue(rec.data['OverrideChar']);
							this.getField('kiidAttested').show();

							if (rec.data['OverrideChar'] == 'W')
							{
								this.getField('reason').setValue(rec.data['reasonCode']);
								this.getField('reason').show();	
							}							
						}
						else
						{
							this.getField('responsibility').setValue(rec.data['OverrideChar']);
							this.getField('responsibility').show();	
							_controller.handleResponsibilityChange(_popups['modify']);
							this.getField('reason').setValue(rec.data['reasonCode']);
							this.getField('reason').show();								
						}						
					}
					else if (ruleType == '53')
					{
						this.getField('rdrAdvice').setValue(rec.data['OverrideChar']);
						this.getField('rdrAdvice').show();
					}
				}

				// Need to re-size the popUp screen for shadow fields
				if (this.rendered)
					this.syncShadow();
			}
			,getData: function()
			{					
				var rec = _grids['ovrdRules'].getSelectedRecord();
				var ruleType = rec.data['RuleType'];
				var dataType = _controller.getRuleDataType(rec.data['RuleType']);

				rec.data['StopDate'] = 	this.getField('stopDate').getDisplayDateString();
				rec.data['OnlineEWI'] = this.getField('onlineEWI').getValue();
				rec.data['CycleEWI'] = this.getField('cycleEWI').getValue();
				rec.data['ESGEWI'] = this.getField('esgEWI').getValue();
				rec.data['AssetLevel'] = this.getField('assetLevel').getValue();
				rec.data['AssetType'] = this.getField('assetType').getValue();

				if (dataType == 'overrideDec')
				{
					rec.data['OverrideAmt'] = this.getField('overrideAmt').getValue();
					rec.data['AmountType'] = this.getField('amountType').getValue();
					rec.data['Currency'] = this.getField('currency').getValue();
				}
				else if (dataType == 'overrideLog')
				{
					rec.data['OverrideLog'] = this.getField('overrideLog').getValue();
				}
				else if (dataType == 'overrideChar')
				{
					if (ruleType == '51')
					{
						if (_controller.IS_ACCOUNT_LEVEL)
						{
							rec.data['OverrideChar'] = this.getField('kiidAttested').getValue();
						}
						else
						{
							rec.data['OverrideChar'] = this.getField('responsibility').getValue();
						}						
						rec.data['reasonCode'] = this.getField('reason').getValue();	
					}
					else if (ruleType == '53')
					{
						rec.data['OverrideChar'] = this.getField('rdrAdvice').getValue();
					}
					else
					{
						rec.data['OverrideChar'] = this.getField('overrideChar').getValue();	
					}
				}
			
				//Compare the KIID specific data in chache and set the appropriate value of verifyStatus
				rec.data['verifyStatus'] = _controller.getVerifyStatus(this.getField('tmpOver').getValue(),this.getField('tmpReasonCode').getValue(),rec,this.getField('verifystatus').getValue())
				return rec.data;						
			}
			,setCurrField: function()
			{
				var rec = _grids['ovrdRules'].getSelectedRecord();

				// Amounttype is Dollar and also have currency field
				if(_popups['modify'].getField('amountType').getValue() == 'D'
					&& _controller.isEnabledCurrency(rec.data['RuleType'])){
					_popups['modify'].getField('currency').show();
					_popups['modify'].getField('currency').setValue(rec.data['Currency']);
				}
				// Amounttype is Units or not show currency field
				else{
					_popups['modify'].getField('currency').reset();
					_popups['modify'].getField('currency').hide();
				}
				
				// render popup
				if (_popups['modify'].rendered)
					_popups['modify'].syncShadow();
			}
		})
		
		,del: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 560
			,modal: true
			,title: _translationMap['OverrideLimitationRule'] + " - " + _translationMap['Delete']
			,defaults: {border:false}
			,bodyStyle: 'padding:4px;'
			,listeners: {
				show: function(){_popups['del'].init();}
			}	
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center; padding-bottom: 10px'
				}														
				,{
					layout: 'column'
					,defaults: {border: false, labelWidth: 90, layout: 'form'}
					,items: [
						{
							columnWidth: .6
							,items: [
								new DesktopWeb.Controls.Label({
									itemId: 'ruleType'
									,fieldLabel: _translationMap['RuleType']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'fund'
									,fieldLabel: _translationMap['Fund']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'class'
									,fieldLabel: _translationMap['Class']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'fundGroup'
									,fieldLabel: _translationMap['FundGroup']
								})		
								// display Broker/Branch/Rep or Account info
								,new DesktopWeb.Controls.Label({
									itemId: 'broker'
									,fieldLabel: _translationMap['Broker']
								})	
								,new DesktopWeb.Controls.Label({
									itemId: 'branch'
									,fieldLabel: _translationMap['Branch']
								})	
								,new DesktopWeb.Controls.Label({
									itemId: 'slsrep'
									,fieldLabel: _translationMap['SalesRep']
								})		
								,new DesktopWeb.Controls.Label({
									itemId: 'accountNum'
									,fieldLabel: _translationMap['Account']
								})									
							]
						}							
						,{		
							columnWidth: .4
							,items: [								
								new DesktopWeb.Controls.Label({
									itemId: 'fundSponsor'
									,fieldLabel: _translationMap['FundSponsor']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'startDate'
									,fieldLabel: _translationMap['StartDate']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'stopDate'
									,fieldLabel: _translationMap['StopDate']
								})								
							]
						}																	
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: 'OK'
					,handler: function(){
						if (_popups['del'].isValid()
							&& _controller.doUpdate(_controller.DEL, _popups['del'].getData()))
						{
							_popups['del'].hide();
						}
					}								
				})
				,new DesktopWeb.Controls.ActionButton({
					text: 'Cancel'	
					,handler: function(){_popups['del'].hide();}					
				})
			]
			,init: function()
			{															
				this.clearAllFields();
				var rec = _grids['ovrdRules'].getSelectedRecord();	
				this.getField('fund').setValue(rec.data['Fund']);
				this.getField('class').setValue(rec.data['Class']);
				this.getField('fundGroup').setValue(rec.data['FundGroup']);
				this.getField('fundSponsor').setValue(rec.data['fundSponsor']);
				this.getField('ruleType').setValue(rec.data['RuleType'] + " - " + _controller.getListDesc('RuleTypeOptions', rec.data['RuleType']));
				this.getField('startDate').setValue(rec.data['StartDate']);
				this.getField('stopDate').setValue(rec.data['stopDateChar']);
				this.getField('broker').setValue(_fields['broker'].getRawValue());
				this.getField('branch').setValue(_fields['branch'].getRawValue());
				this.getField('slsrep').setValue(_fields['slsrep'].getRawValue());
				this.getField('accountNum').setValue(_fields['accountNum'].getValue());
								
				
				// Need to re-size the popUp screen for shadow fields
				if (this.rendered)
					this.syncShadow();
			}
			,getData: function()
			{					
				var rec = _grids['ovrdRules'].getSelectedRecord();	
				rec.data['StopDate'] = rec.data['stopDateChar']
				return rec.data;						
			}														
		
		})
		
		,admin: new DesktopWeb.AdvancedControls.PopupWindow({								
			width: 395				
			,closeAction: 'hide'
			,title: _translationMap['OverrideLimitationRule'] + " - " + _translationMap['Admin']
			,modal: true
			,defaults: {border:false}
			,items: [										
				{						
					layout: 'column'																		
					,style: 'padding:4px'
					,defaults: {border: false, labelWidth:80}						
					,items: [
						{
							width: 185
							,layout: 'form'
							,defaults: {width:80}																					
							,items: [
								new DesktopWeb.Controls.Label({											
									itemId: 'userName'
									,fieldLabel: _translationMap['Username']
								})
								,new DesktopWeb.Controls.Label({											
									itemId: 'modUser'
									,fieldLabel: _translationMap['ModUser']
								})																					
							]
						}							
						,{
							width: 185
							,layout: 'form'
							,defaults: {width: 80}																							
							,items: [
								new DesktopWeb.Controls.Label({											
									itemId: 'procDate'
									,fieldLabel: _translationMap['ProcessDate']
								})
								,new DesktopWeb.Controls.Label({											
									itemId: 'modDate'
									,fieldLabel: _translationMap['ModDate']
								})																					
							]
						}
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){_popups['admin'].hide();}
				})
			]
			,init: function()
			{
				this.clearAllFields();
				var rec = _grids['ovrdRules'].getSelectedRecord();					
				this.getField('procDate').setValue(rec.data['ProcessDate']);
				this.getField('modDate').setValue(rec.data['ModDate']);
				this.getField('userName').setValue(rec.data['UserName']);
				this.getField('modUser').setValue(rec.data['ModUser']);	
			}	
		})
	
		,details: new DesktopWeb.AdvancedControls.PopupWindow({								
			width: 300				
			,closeAction: 'hide'
			,title: _translationMap['OverrideLimitationRule'] + " - " + _translationMap['Details']
			,modal: true
			,defaults: {border:false}
			,items: [										
				{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 95
					,items: [
						new DesktopWeb.Controls.Label({											
							fieldLabel: _translationMap['Status']
							,itemId: 'status'
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'assetLevel'
							,fieldLabel: _translationMap['AssetLevel']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'assetType'
							,fieldLabel: _translationMap['AssetType']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'overrideValue'
							,fieldLabel: _translationMap['OverrideValue']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'amountType'
							,fieldLabel: _translationMap['AmountType']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'currency'
							,fieldLabel: _translationMap['Currency']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'responsibility'
							,fieldLabel: _translationMap['Responsibility']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'kiidAttested'
							,fieldLabel: _translationMap['KIIDAttestedWaived']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'reason'
							,fieldLabel: _translationMap['Reason']
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'rdrAdvice'
							,fieldLabel: ""
						})								
						,new DesktopWeb.Controls.Label({											
							fieldLabel: _translationMap['OnlineEWI']
							,itemId: 'onlineEWI'
						})
						,new DesktopWeb.Controls.Label({											
							fieldLabel: _translationMap['CycleEWI']
							,itemId: 'cycleEWI'
						})
						,new DesktopWeb.Controls.Label({											
							fieldLabel: _translationMap['ESGEWI']
							,itemId: 'esgEWI'
						})	
						// display Broker/Branch/Rep or Account info
						,new DesktopWeb.Controls.Label({
							itemId: 'broker'
							,fieldLabel: _translationMap['Broker']
						})	
						,new DesktopWeb.Controls.Label({
							itemId: 'branch'
							,fieldLabel: _translationMap['Branch']
						})	
						,new DesktopWeb.Controls.Label({
							itemId: 'slsrep'
							,fieldLabel: _translationMap['SalesRep']
						})		
						,new DesktopWeb.Controls.Label({
							itemId: 'accountNum'
							,fieldLabel: _translationMap['Account']
						})															
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){_popups['details'].hide();}
				})
			]
			,init: function()
			{
				this.clearAllFields();

				var rec = _grids['ovrdRules'].getSelectedRecord();								
				var ruleType = rec.data['RuleType'];
				var dataType = _controller.getRuleDataType(rec.data['RuleType']);

				this.getField('broker').setValue(_fields['broker'].getRawValue());
				this.getField('branch').setValue(_fields['branch'].getRawValue());
				this.getField('slsrep').setValue(_fields['slsrep'].getRawValue());
				this.getField('accountNum').setValue(_fields['accountNum'].getValue());

				var conditionalFields = ['overrideValue', 'responsibility', 'kiidAttested', 'reason', 'rdrAdvice', 'amountType', 
										 'assetType', 'assetLevel', 'currency'];

				for (var i = 0; i < conditionalFields.length; i++){
					this.getField(conditionalFields[i]).hide();
				}

				this.getField('status').setValue(rec.data['RuleStatus']);				
				this.getField('onlineEWI').setValue(rec.data['onlineEWIDesc']);
				this.getField('cycleEWI').setValue(rec.data['cycleEWIDesc']);
				this.getField('esgEWI').setValue(rec.data['esgEWIDesc']);
				
				var assetLevelDesc = _controller.getListDesc("AssetLevelList" + ruleType, rec.data['AssetLevel']);
				if (assetLevelDesc != '') {
					this.getField('assetLevel').show();
					this.getField('assetLevel').setValue(assetLevelDesc);
				}

				var assetTypeDesc = _controller.getListDesc("AssetTypeList" + ruleType, rec.data['AssetType']);
				if (assetTypeDesc != '') {
					this.getField('assetType').show();
					this.getField('assetType').setValue(assetTypeDesc);
				}

				if (dataType == 'overrideDec')
				{
					this.getField('overrideValue').setValue(rec.data['OverrideAmt']);
					this.getField('overrideValue').show();
					var amountTypeDesc = _controller.getListDesc("AmountTypeList" + ruleType, rec.data['AmountType']);
					if (amountTypeDesc != '') {
						this.getField('amountType').show();
						this.getField('amountType').setValue(amountTypeDesc);
					}
					this.setCurrField();
					
				}
				else if (dataType == 'overrideLog')
				{
					this.getField('overrideValue').setValue(rec.data['OverrideLog']);
					this.getField('overrideValue').show();	
				}
				else if (dataType == 'overrideChar')
				{					
					if (ruleType == '51')
					{
						if (_controller.IS_ACCOUNT_LEVEL)
						{
							this.getField('kiidAttested').setValue(rec.data['OverrideChar']);
							this.getField('kiidAttested').show();
							if (rec.data['OverrideChar'] == 'W')
							{
								this.getField('reason').setValue(_controller.getListDesc('KIIDWaiverReasonList', rec.data['reasonCode']));
								this.getField('reason').show();
							}							
						}
						else
						{
							this.getField('responsibility').setValue(rec.data['OverrideChar']);
							this.getField('responsibility').show();
							if (rec.data['OverrideChar'] == 'R')
							{
								this.getField('reason').setValue(_controller.getListDesc('KIIDResponsibleBrkList', rec.data['reasonCode']));
							}
							else if (rec.data['OverrideChar'] == 'U')
							{
								this.getField('reason').setValue(_controller.getListDesc('KIIDResponsibleNonBrkList', rec.data['reasonCode']));
							}
							this.getField('reason').show();
						}												
					}
					else if (ruleType == '53')
					{
						this.getField('rdrAdvice').setValue(_controller.getListDesc('RDRRuleList', rec.data['OverrideChar']));
						this.getField('rdrAdvice').show();
					}
					else if (_controller.overrideCharList.indexOf(ruleType) >= 0)
					{					
						this.getField('overrideValue').setValue(_controller.getListDesc('OverrideListRule' + ruleType, rec.data['OverrideChar']));
						this.getField('overrideValue').show();	
					}
				}
		
				// Need to re-size the popUp screen for shadow fields
				if (this.rendered)
					this.syncShadow();
			}
			,setCurrField: function()
			{
				var rec = _grids['ovrdRules'].getSelectedRecord();
				
				// Amounttype is Dollar and also have currency field
				if(rec.data['AmountType'] == 'D' && _controller.isEnabledCurrency(rec.data['RuleType'])){
					_popups['details'].getField('currency').show();
					_popups['details'].getField('currency').setValue(rec.data['Currency']);
				}
				// Amounttype is Units or not show currency field
				else{
					_popups['details'].getField('currency').hide();
				}
			}
		})
	    , history: new DesktopWeb.AdvancedControls.HistoryPopup()
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
					layout: 'form'																								
					,labelWidth: 90
					,items: [
						_fields['ruleType']
						,_fields['broker']
						,_fields['branch']
						,_fields['slsrep']
						,_fields['accountNum']
						,_fields['fundSponsor']								
					]
				}
				,{
					layout: 'column'						
					,items: [
						{								
							layout: 'form'
							,labelWidth: 90															
							,width: 575							
							,items: [
								_fields['fund']																															
							]
						}
						,{
							layout: 'form'
							,width: 125										
							,labelWidth: 45
							,items: [
								_fields['classCode']																								
							]
						}
					]
				}
				,{
					layout: 'column'						
					,items: [
						{								
							layout: 'form'
							,labelWidth: 90															
							,width: 275							
							,items: [										
								_fields['fundGroup']																					
							]
						}
						,{
							layout: 'form'
							,width: 435
							,height: 35									
							,labelWidth: 100
							,items: [
								_fields['showOnlyActiveRecords']
								,new DesktopWeb.Controls.ActionButton({																						
									text: _translationMap['Search']
									,id: 'searchBtn'
									,handler: function(){
										if (_controller.allowSearch())
										{
											_controller.doReload(false);
										}
									}
									,style: 'position:absolute; right:65px; top:10px;'
								})
								,new DesktopWeb.Controls.ActionButton({																						
									text: _translationMap['Reset']
									,id: 'resetBtn'									
									,handler: function(){_controller.doReset();}
									,style: 'position:absolute; right:0px; top:10px;'
									,disabled: true										 																			
								})																								
							]
						}
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['OverrideLimitationRules']
					,width: _layoutWidth
					,items: _grids['ovrdRules']
					,style: "padding-top:10px"
				}										
			]																				
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Close']
				,handler: function(){
					if (_controller.updatesFlag)
					{
						DesktopWeb.Util.closeScreenWithDialog();
					}
					else
					{
						DesktopWeb.Util.cancelScreen();
					}
				}
			})
		]				
	}
}