/*********************************************************************************************
 * @file	GuaranteeInformation.Resources.js 
 * @author	Danny Xu
 * @desc	Resources JS file for Guarantee Information screen
 *********************************************************************************************/

/*
 *  History : 
 *
 *  15 Nov 2013 Kittichai S. P0181067 CHG0034430 T54443
 *        - Fix display date format follows dateFormatDisplay parameter
 *
 *	25 Sep 2014 P. Wongpakdee P0233151 INA Cayenne Day2 T55815
 *		  - Add a new column fundAtGPR and fields contractTypeDIA,
 *			versionDIA
 *
 *  30 Oct 2014 P. Wongpakdee P0233151 DFT0038255 T55947
 *		  - Add a new field SegGuarDetlUUID in grid SegDIATxnDetls
 *
 *  17 Dec 2014 P. Wongpakdee P0233151 DFT0045159 T80045
 *		  - Add new field Projection and change fields label
 *			(NMCR and Non NMCR fields) 
 *
 *  12 Jan 2014 C. Sangkasen INA Cayenne Day 2 P0233151 DFT0046378/DFT0046391 T80155
 *	      - DIA Screen layout change to fix DFT0046378/DFT0046391.
 *
 *	09 Apr 2015 A. Mongkonrat P0232343 T80576 Fox Project B Payout Contract Type
 *              - Support R1 and R2 transaction types.
 *              - ELWA Impact pop up.
 *              - Hypothetical Election pop up.
 *
 *	07 May 2015 A. Mongkonrat P0232343 T80678 Fox Project B Payout Contract Type
 *       - Extend label space.
 *
 *	28 May 2015 A. Mongkonrat P0232343 T80913 DFT0051374 Fox Project B Payout Contract Type
 *       - Date generated in Hypothetical election screen is in MM-DD-YY format.
 *
 *	19 Jun 2015 A. Mongkonrat P0232343 T80996 DFT0051854 Fox Project B Payout Contract Type
 *              - All existing accounts & New Account show that Exceeded LWA Limit = Yes
 *
 *  13 Aug 2015 Aurkarn M. - P0243676 T81232 Dollar For Dollar Guarantee Reductions
 *              - New Deplete Limit button and popup
 *
 *  28 Sep 2015 Aurkarn M. - P0243676 T81452 DFT0053167 Dollar For Dollar
 *              - Depletion Limit Button will be enabled based on backend flag.
 *
 *	06 Oct 2015 A. Mongkonrat P0232343 T81497 CHG0042702 INC0025968 Fox Project B Payout Contract Type
 *              - Assign default value for enableELWA when adding a new GA transaction to the grid.
 *
 *	11 Oct 2016 Matira T. P0256533 T84091 MFS - Desktop
 *              - Added PBG.
 *
 *	04 Nov 2016 Matira T. P0256533 T84110 MFS - Desktop
 *              - Changed logic on exiting guarantee(DBG,DMG) and all new guarantees.
 *
 *  02-Mar-2017 Matira T. P0257694 T85094 INA - Triennial Reset for NMCR 17.4
 *				- added field Total LWA Base.
 *				- added column LWA Base, LWA Base Chg, LWA Base Bal and LWA Base Chg.
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 680;
	var _layoutWidth = 725;
	
	// **** buttons ****
	var _buttons = {
		
		searchButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['SearchButton']
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
						_controller.doLookupMstr();
						_fields['filterTransactions'].setDisabled(false);
						_buttons['filterButton'].setDisabled(false);
					}
				}
			}
		})
		,filterButton: new DesktopWeb.Controls.ActionButton({																						
			style: 'margin-bottom: 3px'
			,text: _translationMap['FilterButton']
			,disabled: true
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
						var filtertype = _fields['filterTransactions'].getValue();
						if (filtertype == 'TType' && _fields['filterValue'].isValid())
						{
							_controller.doLookupDetl();
						}
						
						if (filtertype == 'Year' && _fields['filterDate'].isValid())
						{
							_controller.doLookupDetl();
						}
						
						if (filtertype == 'All')
						{
							_controller.doLookupDetl();
						}
					}
				}					
			}
		})
	}
	
	// **** fields ****
	var _fields = {
		guaranteeToDate: new DesktopWeb.Controls.DateField({
			width: 100
			,fieldLabel: _translationMap['GuaranteeToDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,listeners: {
				change: function(fld, newValue, oldValue){
					_buttons['searchButton'].setDisabled(newValue == '' || _fields['contractType'].getValue() == '');
				}
			}
		})
		,contractType: new DesktopWeb.Controls.SMVComboBox({
			width: 100
			,fieldLabel: _translationMap['ContractType']
			,listeners: {
				change: function(fld, newValue, oldValue){
					if (newValue == '')
					{
						fld.setValue ("All");							
					}
				}
			}
		})
		,filterTransactions: new DesktopWeb.Controls.SMVComboBox({
			width: 100
			,fieldLabel: _translationMap['FilterTransactions']
			,disabled: true
			,allowBlank: false
			,listeners: {
				select : function(fld, rec, index){
					_controller.updateFilterFields();					
				}
				,change: function()
				{
					_controller.updateFilterFields();
				}				
			}
		})
		,filterValue: new DesktopWeb.Controls.SMVComboBox({
			width: 280
			,fieldLabel: _translationMap['TransType']
			,allowBlank: false
			,hidden: true							
		})
		,filterDate: new DesktopWeb.Controls.NumberField({
			width: 100
			,fieldLabel: _translationMap['FilterDate']
			,allowDecimals: false
			,allowBlank: false
			,hidden: true						
		})
		,guarMKV: new DesktopWeb.Controls.Label({
			width: 90 
			,fieldLabel: _translationMap['GuarMKV']
		})
		,guarDBG: new DesktopWeb.Controls.Label({
			width: 120
			,fieldLabel: _translationMap['GuarDBG']
		})
		,guarDMG: new DesktopWeb.Controls.Label({
			width: 120
			,fieldLabel: _translationMap['GuarDMG']
		})
        ,guarPBG: new DesktopWeb.Controls.Label({
			width: 120
			,fieldLabel: _translationMap['GuarPBG']
		})
		,guarDBGTopup: new DesktopWeb.Controls.Label({
			width: 80 
			,fieldLabel: _translationMap['GuarDBGTopup']
		})
		,guarDMGTopup: new DesktopWeb.Controls.Label({
			width: 80 
			,fieldLabel: _translationMap['GuarDMGTopup']
		})
		,guarGWB: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarGWB']
		})
		,guarBonus: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarBonus']
		})
		,guarGWA: new DesktopWeb.Controls.Label({
			width: 80
			,fieldLabel: _translationMap['GuarGWA']
		})
		,guarLWA: new DesktopWeb.Controls.Label({
			width: 80
			,fieldLabel: _translationMap['GuarLWA']
		})
		,guarAdjGWA: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarAdjGWA']
		})
		,guarRemGWA: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarRemGWA']
		})
		,guarAdjLWA: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarAdjLWA']
		})
		,guarRemLWA: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarRemLWA']
		})
		,guarLWAExceeded: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarLWAExceeded']
		})
		,guarGWADef: new DesktopWeb.Controls.Label({
			width: 50
			,fieldLabel: _translationMap['GuarGWADef']
		})
		,guarRemGWADef: new DesktopWeb.Controls.Label({
			width: 50
			,fieldLabel: _translationMap['GuarRemGWADef']
		})
		,guarIncCredit: new DesktopWeb.Controls.Label({
			width: 80
			,fieldLabel: _translationMap['GuarIncCredit']
		})
		,guarIncBaseLWA: new DesktopWeb.Controls.Label({
			width: 60
			,fieldLabel: _translationMap['GuarIncBaseLWA']
		})
		,guarDPAAtAge: new DesktopWeb.Controls.Label({
			width: 50
			,fieldLabel: _translationMap['GuarDPAAtAge']
		})
		,asOfDate: new DesktopWeb.Controls.DateField({
			width: 100
			,fieldLabel: _translationMap['AsOfDate']
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		,guarLWAEntitlement: new DesktopWeb.Controls.Label({
			width: 50
			,fieldLabel: _translationMap['GuarLWAEntitlement']
		})
		,pbgPeriodEndDate: new DesktopWeb.Controls.Label({
			width: 100
			,fieldLabel: _translationMap['DLEnfPeriodEndDate']
            ,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
	}
	
	// **** grids ****
	var _grids = {
		listOfTerms: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 16				
			,autoScroll: true				
			,height: 120
			,store: new Ext.data.XmlStore({
				record: 'TermDetails'
				,fields: ['contract'
						 ,'contractTypeID'
						 ,'contractVer'
						 ,'GWAEWALabel'
					 	 ,'policyYr'
					 	 ,'policyTerm'
						 ,'issueDate'
						 ,'matureDate'
						 ,'termMKV'
						 ,'termDBG'
						 ,'termDMG'
						 ,'termGWB'
						 ,'termBonus'
						 ,'termLWA'
						 ,'termGWA'
						 ,'termAdjLWA'
						 ,'termAdjGWA'
						 ,'termRemLWA'
						 ,'termRemGWA'
						 ,'termGWADef'
						 ,'termGWARem'
						,'termPBG'
						 ,'maturityID'
						 ,'enableGMWB'
						 ,'incCreditApp'
						 ,'isNMCRContract'
						 ,'isElected'
						 ,'firstDPAAge'
						 ,'firstDPAYear'
						 ,'enableDIA'
						 ,'enableHypoElect'
						 ,'exceedLWALimit'
						 ,'enableDepleteLim']
				,listeners: {
					load: function(store, records)
					{
						/************************************************************************************************* 
							getDateDisplayValue is the method to convert smartview date string into displayed date string.
						    When data load from smartview, it is host format, 
							getDateDisplayValue convert the date to display as displayformat
						*************************************************************************************************/
						Ext.each(records, function(record){
						record.data.issueDate = DesktopWeb.Util.getDateDisplayValue(record.data.issueDate);
						record.data.matureDate = DesktopWeb.Util.getDateDisplayValue(record.data.matureDate);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
		
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						_fields['filterTransactions'].setValue('All');						
						_controller.updateFilterFields();
						_controller.doLookupDetl();
						Ext.getCmp('GMWB').setDisabled (record.data.enableGMWB.toLowerCase() != "yes");
						Ext.getCmp('YearlyGWB').setDisabled (record.data.enableGMWB.toLowerCase() != "yes");
						Ext.getCmp('diaInfoBtn').setDisabled (record.data.enableDIA.toLowerCase() != "yes");
						Ext.getCmp('hypoElectBtn').setDisabled (record.data.enableHypoElect.toLowerCase() != "yes");
						Ext.getCmp('DepleteLimBtn').setDisabled (record.data.enableDepleteLim.toLowerCase() != "yes");
						_fields['guarLWAExceeded'].setValue(record.data.exceedLWALimit == "0" ? _translationMap['No']:_translationMap['Yes']);
						_controller.emptyUpdateXML();						
					}
					,rowdeselect: function(selModel, index, record){
						_fields['filterTransactions'].setValue('All');						
						_controller.updateFilterFields();
						_controller.clearDetails();
						Ext.getCmp('GMWB').disable();
						_controller.emptyUpdateXML();											
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['ContractType'], id:'contract', dataIndex: 'contract', width:80}
					,{header: _translationMap['Version'], id:'contractVer', dataIndex: 'contractVer', width:60}
					,{header: _translationMap['PolicyYear'], id:'policyYr',  dataIndex: 'policyYr', width:70}
					,{header: _translationMap['PolicyTerm'], id:'policyTerm', dataIndex: 'policyTerm', width:70}
					,{header: _translationMap['IssueDate'], id:'issueDate', dataIndex: 'issueDate', width:80}
					,{header: _translationMap['MatureDate'], id:'matureDate', dataIndex: 'matureDate', width:80}
					,{header: _translationMap['MarketValue'], id:'termMKV', dataIndex: 'termMKV', width:80}
					,{header: _translationMap['GuarDBG'], id:'termDBG', dataIndex: 'termDBG', width:70}
					,{header: _translationMap['GuarDMG'], id:'termDMG', dataIndex: 'termDMG', width:70}
					,{header: _translationMap['GuarGWB'], id:'termGWB', dataIndex: 'termGWB', width:70}
					,{header: _translationMap['GuarBonus'], id:'termBonus', dataIndex: 'termBonus', width:70}
					,{header: _translationMap['TransRemLWA'], id:'termRemLWA', dataIndex: 'termRemLWA', width:70}
					,{header: _translationMap['TransRemGWA'], id:'termRemGWA', dataIndex: 'termRemGWA', width:70}
					,{header: _translationMap['GuarPBG'], id:'termPBG', dataIndex: 'termPBG', width:70}
				]							
			})
			
			,buttons: [
			]			
		})
		
		,transaction: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 16				
			,autoScroll: true				
			,height: 155
			,store: new Ext.data.XmlStore({
				record: 'TxnDetails'
				,fields: ['transType'
						,'tradeDate'
						,'transID'
						,'baycom'
						,'adjustStat'
						,'fund'
						,'class'
						,'tradeAmt'
						,'txnDMG'
						,'txnDBG'
						,'txnGWB'
						,'txnRemLWA'
						,'txnRemGWA'
						,'txnPBG'
						,'enableCanc'
						,'segGuarAdjustID'
						,'segGuarDetlUUID'
						,'num'
						,'units'
						,'runMode'
						,{name: 'recordSource', mapping: '@recordSource'}
						,'settleDate'
						,'reason'						
						,'remarks'
						,'txnMKV'
						,'frFund'
						,'frClass'
						,'frbaycom'
						,'enableELWA'
						,'GMVBaseChgAmt'
						,'GMVChgAmt'
						,'SumOfAWDGMVChgAmt'
						,'DepletionLimitChgAmt'
						,'GDVBaseChgAmt'
						,'GDVChgAmt'
						,'SumOfAWDGDVChgAmt'
						,'RemDepletionLimitChgAmt']
				,listeners: {
					load: function(store, records)
					{
						/************************************************************************************************* 
							getDateDisplayValue is the method to convert smartview date string into displayed date string.
						    When data load from smartview, it is host format, 
							getDateDisplayValue convert the date to display as displayformat
						*************************************************************************************************/
						Ext.each(records, function(record){
						record.data.tradeDate = DesktopWeb.Util.getDateDisplayValue(record.data.tradeDate);
						record.data.settleDate = DesktopWeb.Util.getDateDisplayValue(record.data.settleDate);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
		
					}
				}						
						
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						_controller.handleTransRecordSelectionChange();
						Ext.getCmp('ELWAImpactBtn').setDisabled (record.data.enableELWA.toLowerCase() != "yes");						
					}
					,rowdeselect: function(){
						_controller.handleTransRecordSelectionChange();
					}									
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['TransType'], id:'transType', dataIndex: 'transType', width:80}
					,{header: _translationMap['TradeDate'], id:'tradeDate', dataIndex: 'tradeDate', width:100}
					,{header: _translationMap['TransID'], id:'transID',  dataIndex: 'transID', width:80}
					,{header: _translationMap['AdjustStat'], id:'adjustStat',  dataIndex: 'adjustStat', width:75}
					,{header: _translationMap['Baycom'], id:'baycom',  dataIndex: 'baycom', width:70}
					,{header: _translationMap['Fund'], id:'fund', dataIndex: 'fund', width:60}
					,{header: _translationMap['Class'], id:'class', dataIndex: 'class', width:60}
					,{header: _translationMap['FromBaycom'], id:'frbaycom',  dataIndex: 'frbaycom', width:70}
					,{header: _translationMap['FromFund'], id:'frFund', dataIndex: 'frFund', width:60}
					,{header: _translationMap['FromClass'], id:'frClass', dataIndex: 'frClass', width:60}
					,{header: _translationMap['Units'], id:'units', dataIndex: 'units', width:75}
					,{header: _translationMap['TradeAmt'], id:'tradeAmt', dataIndex: 'tradeAmt', width:100}
					,{header: _translationMap['GuarMKV'], id:'txnMKV', dataIndex: 'txnMKV', width:75}
					,{header: _translationMap['GuarDBG'], id:'txnDBG', dataIndex: 'txnDBG', width:75}
					,{header: _translationMap['GuarDMG'], id:'txnDMG', dataIndex: 'txnDMG', width:75}
					,{header: _translationMap['GuarGWB'], id:'txnGWB', dataIndex: 'txnGWB', width:75}
					,{header: _translationMap['TransRemLWA'], id:'txnRemLWA', dataIndex: 'txnRemLWA', width:75}
					,{header: _translationMap['TransRemGWA'], id:'txnRemGWA', dataIndex: 'txnRemGWA', width:75}						
					,{header: _translationMap['GuarPBG'], id:'txnPBG', dataIndex: 'txnPBG', width:75}					
				]							
			})
			
			,buttons: [	
				new DesktopWeb.Controls.ActionButton({
					itemId: 'incBaseDetlBtn'								
					,text: _translationMap['IncomeBaseDetlButton']
					,disabled: true	
					,handler: function(){_controller.openIncomeBaseDetlPopupFromGuarInfo()}	
				})					
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,disabled: true							
					,handler: function(){
						_controller.openActionPopup(_controller.ADD, 'transaction', 'transPopup');
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,disabled: true
					,handler: function(){
						_controller.openActionPopup(_controller.DEL, 'transaction', 'transPopup');
						}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancBtn'
					,text: _translationMap['CancBtn']
					,disabled: true
					,handler: function(){
						_controller.cancelTxn();						
					}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,disabled: true
					,handler: function(){_controller.doLookupDetl(true)}							
				})
			]			
		})
		
		,guaranteeImpact: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 16
			,autoScroll: true							
			,height: 95
			,style: 'margin-bottom: 10px;'
			,autoExpandColumn: 'name'								
			,store: new Ext.data.XmlStore({
				record: 'ImpactDetl'
				,fields: ['name'
						 ,'bef'
						 ,'chg'
						 ,'aft'
						 ,'num'
						 ,{name: 'recordSource', mapping: '@recordSource'}]
				,listeners: {
					load: function(store, records)
					{											
						Ext.each(records, function(record){							
							
							if(record.data.name == 'Maturity Date')
							{															
								record.data.bef = DesktopWeb.Util.getDateDisplayValue(record.data.bef);
								record.data.aft = DesktopWeb.Util.getDateDisplayValue(record.data.aft);
							}
									
						});

						store.fireEvent('datachanged', store); //to set data in grid again					
						
						this.filterBy(function(record){
							if (_controller.isAppGuarImpact(record))
							{
								return record.data.num == _grids['transaction'].getSelectedRecord().data['recordSource'];
							}
							else
							{
								return false;
							}
						});																																							
					}																							
				}	
			})			
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: '', id:'name', dataIndex: 'name'}
					,{header: _translationMap['GuarBefore'], id:'bef', dataIndex: 'bef', width:180}
					,{header: _translationMap['GuarChange'], id:'chg',  dataIndex: 'chg', width:180}
					,{header: _translationMap['GuarAfter'], id:'aft', dataIndex: 'aft', width:180}
				]							
			})			
		})
		
		,lwa: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: 520
				,height: 150
				,autoScroll: true
				,style: 'margin: 10px'
				,disableSelection: true	
				,store: new Ext.data.XmlStore(
					{
						record: 'Element'
						,fields:['year','calcLWA','rifMin','adjLWA','remLWA']
					}
				)				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns:[
						{header: _translationMap['Year'], dataIndex: 'year'}
						,{header: _translationMap['CalcLWA'], dataIndex: 'calcLWA'}
						,{header: _translationMap['RIFMin'], dataIndex: 'rifMin'}						
						,{header: _translationMap['GuarAdjLWA'], dataIndex: 'adjLWA'}
						,{header: _translationMap['RemainLWA'], dataIndex: 'remLWA'}
					]
				})
			}
		)
		
		,gwa: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: 520
				,height: 150
				,autoScroll: true
				,style: 'margin: 10px'
				,disableSelection: true	
				,store: new Ext.data.XmlStore(
					{
						record: 'Element'
						,fields:['year','calcGWA','rifMin','adjGWA','remGWA']
					}
				)				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns:[
						{header: _translationMap['Year'], dataIndex: 'year'}
						,{header: '', dataIndex: 'calcGWA'}
						,{header: _translationMap['RIFMin'], dataIndex: 'rifMin'}						
						,{header: '', dataIndex: 'adjGWA'}
						,{header: '', dataIndex: 'remGWA'}
					]
				})
			}
		)
		
		,depLimDMG: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: 520
				,height: 150
				,autoScroll: true
				,style: 'margin: 10px'
				,disableSelection: true	
				,store: new Ext.data.XmlStore(
					{
						record: 'Period'
						,fields:['startDate','endDate','openingLim','carryoverLim','usedAmtLim','remainingLim']
						,listeners: 
						{
							load: function(store, records)
							{		
								Ext.each(records, function(record)
								{
									record.data.startDate = DesktopWeb.Util.getDateDisplayValue(record.data.startDate);
									record.data.endDate = DesktopWeb.Util.getDateDisplayValue(record.data.endDate);
								});
								store.fireEvent('datachanged', store);
							}
						} 
					}
				)				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns:[
						{header: _translationMap['StartDate'], dataIndex: 'startDate'}
						,{header: _translationMap['EndDate'], dataIndex: 'endDate'}
						,{header: _translationMap['OpeningAmt'], dataIndex: 'openingLim'}						
						,{header: _translationMap['CarryOverAmt'], dataIndex: 'carryoverLim'}
						,{header: _translationMap['AmtUsed'], dataIndex: 'usedAmtLim'}
						,{header: _translationMap['RemAmt'], dataIndex: 'remainingLim'}
					]
				})
			}
		)
		
		,depLimDBG: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: 520
				,height: 150
				,autoScroll: true
				,style: 'margin: 10px'
				,disableSelection: true	
				,store: new Ext.data.XmlStore(
					{
						record: 'Period'
						,fields:['startDate','endDate','openingLim','carryoverLim','usedAmtLim','remainingLim']
						,listeners: 
						{
							load: function(store, records)
							{		
								Ext.each(records, function(record)
								{
									record.data.startDate = DesktopWeb.Util.getDateDisplayValue(record.data.startDate);
									record.data.endDate = DesktopWeb.Util.getDateDisplayValue(record.data.endDate);
								});
								store.fireEvent('datachanged', store);
							}
						} 
					}
				)				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns:[
						{header: _translationMap['StartDate'], dataIndex: 'startDate'}
						,{header: _translationMap['EndDate'], dataIndex: 'endDate'}
						,{header: _translationMap['OpeningAmt'], dataIndex: 'openingLim'}						
						,{header: _translationMap['CarryOverAmt'], dataIndex: 'carryoverLim'}
						,{header: _translationMap['AmtUsed'], dataIndex: 'usedAmtLim'}
						,{header: _translationMap['RemAmt'], dataIndex: 'remainingLim'}
					]
				})
			}
		)
		
		,depLimPBG: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: 520
				,height: 130
				,autoScroll: true
				,style: 'margin: 10px'
				,disableSelection: true	
				,store: new Ext.data.XmlStore(
					{
						record: 'Period'
						,fields:['startDate','endDate','openingLim','carryoverLim','usedAmtLim','remainingLim']
						,listeners: 
						{
							load: function(store, records)
							{		
								Ext.each(records, function(record)
								{
									record.data.startDate = DesktopWeb.Util.getDateDisplayValue(record.data.startDate);
									record.data.endDate = DesktopWeb.Util.getDateDisplayValue(record.data.endDate);
								});
								store.fireEvent('datachanged', store);
							}
						}  
					}
				)				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns:[
						{header: _translationMap['StartDate'], dataIndex: 'startDate'}
						,{header: _translationMap['EndDate'], dataIndex: 'endDate'}
						,{header: _translationMap['OpeningAmt'], dataIndex: 'openingLim'}						
						,{header: _translationMap['CarryOverAmt'], dataIndex: 'carryoverLim'}
						,{header: _translationMap['AmtUsed'], dataIndex: 'usedAmtLim'}
						,{header: _translationMap['RemAmt'], dataIndex: 'remainingLim'}
					]
				})
			}
		)
		
        
		,SegIncmBaseGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 15
				,title: ''
				,autoScroll: true
				,height: 200
				,style: 'margin-top: 5px'
				,autoExpandColumn: 'incmCrChange'
				,deferRowRender: false
				,store: new Ext.data.XmlStore(
					{
						record: 'SegIncmBaseDetl'
						,fields: ['penIncmID'
							  	,'incmCrChange'
							  	,'mkvChg'
							  	,'incmBaseChange'
							  	,'gprate'
							  	,'diaChange'
							  	,'nameMeasure'
							  	,'ageMeasure'
							  	,'statMeasure'
							  	,'dofbMeasure'
							  	,'nameElection'
							  	,'ageElection'
							  	,'statElection'
							  	,'dofbElection'
							  	,'lwaBaseChg'
							  ]
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){Ext.data.Record.id(record)});								
							}
						}																																		
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({
						singleSelect: true
						,listeners: {														
							rowselect: function() {
								_controller.populateWithSelectedSegIncmBaseRecord();							
							}																																						
						}
				})				
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true													
						}
						,columns: [							
							{header: _translationMap['PenIncmID'], id: 'penIncmID', dataIndex: 'penIncmID', width: 90}
							,{header: _translationMap['IncmCrChange'], id: 'incmCrChange', dataIndex: 'incmCrChange', width: 140}
							,{header: _translationMap['MkvChg'], id: 'mkvChg', dataIndex: 'mkvChg', width: 140}
							,{header: _translationMap['IncmBaseChange'], id: 'incmBaseChange', dataIndex: 'incmBaseChange', width: 140}
							,{header: _translationMap['Gprate'], id: 'gprate', dataIndex: 'gprate', width: 96}
							,{header: _translationMap['DiaChange'], id: 'diaChange', dataIndex: 'diaChange', width: 90}
							,{header: _translationMap['LWABaseChg'], id: 'lwaBaseChg', dataIndex: 'lwaBaseChg', width: 90}
						]							
					}
				)
				,buttons: [																
				]					
			}
		)
															
		,SegDIAGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 40
				,title: ''
				,autoScroll: true
				,height: 140
				,style: 'margin-top: 5px'
				,deferRowRender: false			
				,store: new Ext.data.XmlStore(
					{
						record: 'SegDIADetls'
						,fields: ['electAge'
							  	,'electYear'
							  	,'diaAmt'
							  	,'projDIA'
							  	,'totProjDIA'
								,'segGuarProjUUID'							  	
							  ]						
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({
						singleSelect: true
						,listeners: {
							rowselect: function(){
								if (_grids['listOfTerms'].getSelectedRecord().data['isNMCRContract'].toUpperCase() == "YES")
									_controller.loadSegPenIncmBaseGrid();							
							}																																						
						}
				})				
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true														
						}
						,columns: [							
							{header: _translationMap['ElectAge'], id: 'electAge', dataIndex: 'electAge', width: 125}
							,{header: _translationMap['ElectYear'], id: 'electYear', dataIndex: 'electYear', width: 125}
							,{header: _translationMap['DiaAmt'], id: 'diaAmt', dataIndex: 'diaAmt', width: 140}
							,{header: _translationMap['ProjDIA'], id: 'projDIA', dataIndex: 'projDIA', width: 140}
							,{header: _translationMap['TotProjDIA'], id: 'totProjDIA', dataIndex: 'totProjDIA', width: 140}													
						]							
					}
				)
				,buttons: [																
				]					
			}
		)			
		
		,SegPenIncmBaseGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 40
				,title: ''
				,autoScroll: true
				,height: 140
				,style: 'margin-top: 5px'
				,deferRowRender: false				
				,store: new Ext.data.XmlStore(
					{
						record: 'SegPenIncmDetl'
						,fields: ['penID'
							  	,'measureAge'							  	
							  	,'incmCRAmt'							  	
							  	,'mkvAmt'
							  	,'rate'
							  	,'dialwa'							  	
								,'fundAtGPR'
								,'lwaBase'
							  ]						
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({
						singleSelect: true
						,listeners: {
							rowselect: function(){
								if (_grids['listOfTerms'].getSelectedRecord().data['isNMCRContract'].toUpperCase() == "YES")
									_controller.populateSegDIATransactionGrid();							
							}																																							
						}
				})				
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true							
							,sortable: false
						}
						,columns: [							
							{header: _translationMap['PenID'], id: 'penID', dataIndex: 'penID', width: 100}
							,{header: _translationMap['MeasureAge'], id: 'measureAge', dataIndex: 'measureAge', width: 50}							
							,{header: _translationMap['IncmCRAmt'], id: 'incmCRAmt', dataIndex: 'incmCRAmt', width: 125}							
							,{header: _translationMap['MkvAmt'], id: 'mkvAmt', dataIndex: 'mkvAmt', width: 125}							
							,{header: _translationMap['Rate'], id: 'rate', dataIndex: 'rate', width: 78}							
							,{header: _translationMap['Dialwa'].split('/')[0], id: 'DIACalcLWA', dataIndex: 'dialwa', width: 130}
							,{header: _translationMap['FundAtGPR'], id: 'fundAtGPR', dataIndex: 'fundAtGPR', width: 60}
							,{header: _translationMap['LWABase'], id: 'lwaBase', dataIndex: 'lwaBase', width: 60}
						]							
					}
				)
				,buttons: [																
				]					
			}
		)
		
		,SegDIATransactionGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 40
				,title: ''
				,autoScroll: true
				,height: 140
				,style: 'margin-top: 5px'
				,store: new Ext.data.XmlStore(
					{
						record: 'SegDIATxnDetls'
						,fields: ['transType'							  	
							  	,'tradeDate'
								,'transNumber'
								,'transID'
							  	,'grossAmt'
							  	,'incmBaseChg'
							  	,'incmBaseBal'
							  	,'diaChg'
							  	,'diaBal'
								,'SegGuarDetlUUID'						  	
								,'lwaBaseChg'						  	
								,'lwaBaseBal'						  	
							  ]	
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									record.data.tradeDate = DesktopWeb.Util.getDateDisplayValue(record.data.tradeDate);
								});
								store.fireEvent('datachanged', store); //to set data in grid again		
							}
						}									
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({
						singleSelect: true						
				})				
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true							
							,sortable: false
						}
						,columns: [							
							{header: _translationMap['TransType'], id: 'transType', dataIndex: 'transType', width: 60}
							,{header: _translationMap['TradeDate'], id: 'tradeDate', dataIndex: 'tradeDate', width: 70}							
							,{header: _translationMap['TransNum'], id: 'transNumber', dataIndex: 'transNumber', width: 60}																					
							,{header: _translationMap['GrossAmt'], id: 'grossAmt', dataIndex: 'grossAmt', width: 70}							
							,{header: _translationMap['IncmBaseChg'], id: 'incmBaseChg', dataIndex: 'incmBaseChg', width: 90}
							,{header: _translationMap['IncmBaseBal'], id: 'incmBaseBal', dataIndex: 'incmBaseBal', width: 90}							
							,{header: _translationMap['DIAChg'], id: 'diaChg', dataIndex: 'diaChg', width: 88}
							,{header: _translationMap['DIABal'], id: 'diaBal', dataIndex: 'diaBal', width: 88}																																															
							,{header: _translationMap['LWABaseChg'], id: 'lwaBaseChg', dataIndex: 'lwaBaseChg', width: 88}																																															
							,{header: _translationMap['LWABaseBal'], id: 'lwaBaseBal', dataIndex: 'lwaBaseBal', width: 88}																																															
						]							
					}
				)
				,buttons: [																
				]					
			}
		)
		,elwaImpactGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: 420
				,height: 150
				,autoScroll: true
				,style: 'margin: 5px'
				,disableSelection: true	
				,store: new Ext.data.XmlStore(
					{
						record: 'ImpactDetl'
						,fields:['age','year','bef','chg','aft']
					}
				)				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns:[
						{header: _translationMap['ELWAAge'], id: 'age', dataIndex: 'age', width: 50}
						,{header: _translationMap['ELWAYear'], id: 'year', dataIndex: 'year', width: 65}							
						,{header: _translationMap['ELWABefore'], id: 'bef', dataIndex: 'bef', width: 95}																					
						,{header: _translationMap['ELWAChangeAmount'], id: 'chg', dataIndex: 'chg', width: 95}							
						,{header: _translationMap['ELWAAfter'], id: 'aft', dataIndex: 'aft', width: 95}
					]
				})
			}
		)		
	}
		
	var _tabs = {
		depleteLimPanel: new Ext.TabPanel({
			itemId: 'depleteLimPanel'
			,activeTab: 0
			,border: false
			,plain: true
			,defaults: {
				layout: 'form'
				,border: true
				,autoHeight: true
			}
			,items: []
		})
	}
	
	// **** tabs ****
	var _panels = {
		DMGPanel: new Ext.Panel({
			title: _translationMap['GuarDMG']
			,height: 160
			,items: [_grids['depLimDMG']]
		})
		,PBGPanel: new Ext.Panel({
			title: _translationMap['GuarPBG']
			,height: 160
			,defaults: {
				layout: 'form'
				,border: false
			}
			,items: [
			{
				width: 555
				,labelWidth: 190
				,style: 'margin-top: 5px; margin-left: 10px; margin-bottom: -10px'
				,items:[
					_fields['pbgPeriodEndDate']
				]
			}, _grids['depLimPBG']]
		})
		,DBGPanel: new Ext.Panel({
			title: _translationMap['GuarDBG']
			,height: 160
			,items: [_grids['depLimDBG']]
		})
	}
	// **** popups ****
	var _popups = {
		yearlyGWBPopup: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				width: 555
				,defaults: {border: false}
				,modal: true
				,title: _translationMap['GWBYearly']
				,items:[
					{
						xtype: 'tabpanel'
						,id: 'GWB'
						,activeItem: 'LWA'
						,style: 'padding-bottom:10px'
						,items:[
							{
								id: 'GWA'
								,title: _translationMap['GuarGWA']
								,height: 160
								,items: _grids['gwa']
							}
							,{
								id: 'LWA'
								,title: _translationMap['GuarLWA']
								,height: 160
								,items: _grids['lwa']
							}							
						]
					}						
				]
				,buttons:[
					new DesktopWeb.Controls.ScreenButton(
						{
							text: _translationMap['Close']
							,handler: function(){
								_popups['yearlyGWBPopup'].hide();
							}
						}
					)
				]
			}
		)
		
		,transPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 610
			,defaults: {border:false}
			,modal: true
			,items: [
				{
					layout: 'column'																		
					,style: 'padding:4px'
					,items: [
						{
							layout: 'form'
							,columnWidth: 0.53
							,labelWidth: 120
							,border: false
							,items: [
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'contractType'
									,width: 150
									,fieldLabel: _translationMap['ContractType']
								})
								,new DesktopWeb.Controls.DateField({
									itemId: 'tradeDate'
									,width: 150
									,fieldLabel: _translationMap['TradeDate']
									,allowBlank: false
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})									
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'fundType'
									,width: 150
									,fieldLabel: _translationMap['Fund']
									,editable: false
									,listeners: {
										select: function(){
											_popups['transPopup'].getField('classType').loadData(_popups['transPopup'].getField('classType').classLists[_popups['transPopup'].getField('fundType').getValue()])
											_controller.disableGAFields();
										}
									}
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'classType'									
									,width: 150
									,fieldLabel: _translationMap['Class']
								})
								,new DesktopWeb.Controls.TextField({
									itemId: 'units'
									,width: 150
									,fieldLabel: _translationMap['Units']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAGWB'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjGWB']
								})								

								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAGwaEwa'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjGWA']
								})								

								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAAdjustedGwaEwa'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjGWAAdjusted']
								})								

								,new DesktopWeb.Controls.NumberField({
									itemId: 'GARemainingGwaEwa'
									,width: 150
									,allowNegative: true
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjGWARemaining']
								})								
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAGWADeferral'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjGWADeferral']
								})								
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAGMVBase'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugGMVBase']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAGMV'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugGMV']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GASumOfAWDGMV'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugSumOfAWDGMV']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GADepleteLimit'
									,width: 150
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugDepleteLimit']
								})
							]
						}
						,{
							layout: 'form'
							,columnWidth: 0.47
							,labelWidth: 150
							,border: false
							,items: [
								new DesktopWeb.Controls.TextField({
									itemId: 'account'
									,width: 100
									,fieldLabel: _translationMap['Account']
								})								
								,new DesktopWeb.Controls.DateField({
									itemId: 'settleDate'
									,width: 100
									,fieldLabel: _translationMap['SettleDate']
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'guarDBGPopup'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuarDBG']														
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'guarDMGPopup'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuarDMG']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'guarPBGPopup'
									,width: 100
									,editable: false
									,allowNegative: true
									,fieldLabel: _translationMap['GuarPBG']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GABonusBase'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjBonusBase']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GALWA'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjLWA']
								})								
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAAdjustedLWA'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjLWAAdjusted']
								})								
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GARemainingLWA'
									,width: 100
									,allowNegative: true
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjLWARemaining']
								})								
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GARemainingGWADeferral'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteeAdjGWARemainingDeferrel']
								})								
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAGDVBase'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugGDVBase']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GAGDV'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugGDV']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GASumOfAWDGDV'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugSumOfAWDGDV']
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'GARemDepleteLimit'
									,width: 100
									,allowNegative: true
									,fieldLabel: _translationMap['GuaranteePlugRemDepleteLimit']
								})
							]
						}
						
					]												
				}
				,{
					layout: 'form'
					,border: false
					,style: 'padding-left:4px'
					,labelWidth: 120
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'reason'
							,width: 441
							,fieldLabel: _translationMap['Reason']
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'remarks'
							,width: 441
							,fieldLabel: _translationMap['Remarks']
						})
						,{
							layout: 'form'
							,border: false
							,labelWidth: 120
							,hidden: true
							,id: 'modRemarks'																																						
							,items: [
								new DesktopWeb.Controls.TextField({
									itemId: 'modRemarks'
									,width: 400
									,fieldLabel: _translationMap['ModRemarks']
								})
							]
						}
					]
				}
				,{
					layout: 'column'																		
					,style: 'padding:4px'
					,items: [
						{
							layout: 'form'
							,columnWidth: 0.55
							,labelWidth: 125
							,border: false
							,items: [
								new DesktopWeb.Controls.TextField({
									itemId: 'userName'
									,width: 150
									,fieldLabel: _translationMap['UserName']
								})
								,new DesktopWeb.Controls.TextField({
									itemId: 'modDate'
									,width: 150
									,fieldLabel: _translationMap['ModDate']
								})									
								,new DesktopWeb.Controls.TextField({
									itemId: 'modUser'
									,width: 150
									,fieldLabel: _translationMap['ModUser']
								})
							]
						}
						,{
							layout: 'form'
							,columnWidth: 0.45
							,labelWidth: 100
							,border: false
							,items: [
								new DesktopWeb.Controls.TextField({
									itemId: 'stat'
									,width: 150
									,fieldLabel: _translationMap['Stat']
								})								
								,new DesktopWeb.Controls.TextField({
									itemId: 'processDate'
									,width: 150
									,fieldLabel: _translationMap['ProcessDate']
								})
								,new DesktopWeb.Controls.TextField({
									itemId: 'processTime'
									,width: 150
									,fieldLabel: _translationMap['ProcessTime']
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
						if (_popups['transPopup'].action == _controller.DEL ||
							_popups['transPopup'].isValid() 
							&& _controller.saveAddTransaction(_popups['transPopup'].action))
						{
							_controller.savePopup(_popups['transPopup'].action, _popups['transPopup'].getData(), 'transaction');
							_popups['transPopup'].hide();
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){
						_popups['transPopup'].hide();
						_grids['transaction'].selectFirstRecord();
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Reset']
					,id: 'resetBtn'
					,handler: function(){_controller.clearAllFields('transPopup');
					}
				})
			]
			,init: function(action)
			{
	
				this.action = action;
				this.clearAllFields();
				this.get(2).hide();
				Ext.getCmp('modRemarks').hide();
				Ext.getCmp('resetBtn').hide();

				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['AddTrans']);
						this.enableAllFields();
						this.getField('contractType').disableField();
						this.getField('account').disableField();
						this.getField('settleDate').disableField();
						Ext.getCmp('resetBtn').show();
						_controller.doLookupAddBtn();

						break;
					}
					case _controller.CANC:
					{
						this.setTitle(_translationMap['CancTrans']);
						this.disableAllFields();
						this.getField('modRemarks').enableField();
						this.get(2).show();
						Ext.getCmp('modRemarks').show();
						_controller.doLookupCanBtn();
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['DelTrans']);
						this.disableAllFields();
						this.populateWithSelectedRecord();
					}
				}
				
			}

			,populateWithSelectedRecord: function()
			{
				var rec = _grids['transaction'].getSelectedRecord();
				this.getField('contractType').setValue(_grids['listOfTerms'].getSelectedRecord().data['contract']);
				this.getField('tradeDate').setValue(rec.data['tradeDate']);
				this.getField('fundType').setValue(rec.data['fund']);
				this.getField('classType').setValue(rec.data['class']);
				this.getField('account').setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
				this.getField('guarDBGPopup').setValue(rec.data['txnDBG']);
				this.getField('guarDMGPopup').setValue(rec.data['txnDMG']);
				
				this.getField('GAGWB').setValue(rec.data['txnGWB']);
				this.getField('GAGwaEwa').setValue(rec.data['txnGAGwaEwa']);
				this.getField('GAAdjustedGwaEwa').setValue(rec.data['txnGAAdjustedGwaEwa']);
				this.getField('GARemainingGwaEwa').setValue(rec.data['txnRemGWA']);
				this.getField('GAGWADeferral').setValue(rec.data['txnGAGWADeferral']);
				this.getField('GABonusBase').setValue(rec.data['txnGABonusBase']);
				this.getField('GALWA').setValue(rec.data['txnGALWA']);
				this.getField('GAAdjustedLWA').setValue(rec.data['txnGAAdjustedLWA']);
				this.getField('GARemainingLWA').setValue(rec.data['txnRemLWA']);
				this.getField('GARemainingGWADeferral').setValue(rec.data['txnGARemainingGWADeferral']);

				this.getField('guarPBGPopup').setValue(rec.data['txnPBG']);
				this.getField('GAGMVBase').setValue(rec.data['GMVBaseChgAmt']);
				this.getField('GAGMV').setValue(rec.data['GMVChgAmt']);
				this.getField('GASumOfAWDGMV').setValue(rec.data['SumOfAWDGMVChgAmt']);
				this.getField('GADepleteLimit').setValue(rec.data['DepletionLimitChgAmt']);
				this.getField('GAGDVBase').setValue(rec.data['GDVBaseChgAmt']);
				this.getField('GAGDV').setValue(rec.data['GDVChgAmt']);
				this.getField('GASumOfAWDGDV').setValue(rec.data['SumOfAWDGDVChgAmt']);
				this.getField('GARemDepleteLimit').setValue(rec.data['RemDepletionLimitChgAmt']);
				
				this.getField('units').setValue(rec.data['units']);
				this.getField('remarks').setValue(rec.data['remarks']);
				this.getField('reason').setValue(rec.data['reason']);
				this.getField('settleDate').setValue(rec.data['settleDate']);
			}
			
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['transType'] = "GA";
				
				data['tradeDate'] = this.getField('tradeDate').getDisplayDateString();
				data['fund'] = this.getField('fundType').getValue();
				data['class'] = this.getField('fundType').getValue();
				data['txnDMG'] = this.getField('guarDMGPopup').getValue();
				data['txnDBG'] = this.getField('guarDBGPopup').getValue();

				data['txnGWB'] = this.getField('GAGWB').getValue();
				data['txnGAGwaEwa'] = this.getField('GAGwaEwa').getValue();
				data['txnGAAdjustedGwaEwa'] = this.getField('GAAdjustedGwaEwa').getValue();
				data['txnRemGWA'] = this.getField('GARemainingGwaEwa').getValue();
				data['txnGAGWADeferral'] = this.getField('GAGWADeferral').getValue();
				data['txnGABonusBase'] = this.getField('GABonusBase').getValue();
				data['txnGALWA'] = this.getField('GALWA').getValue();
				data['txnGAAdjustedLWA'] = this.getField('GAAdjustedLWA').getValue();
				data['txnRemLWA'] = this.getField('GARemainingLWA').getValue();
				data['txnGARemainingGWADeferral'] = this.getField('GARemainingGWADeferral').getValue();

				data['txnPBG'] = this.getField('guarPBGPopup').getValue();
				data['GMVBaseChgAmt'] = this.getField('GAGMVBase').getValue();
				data['GMVChgAmt'] = this.getField('GAGMV').getValue();
				data['SumOfAWDGMVChgAmt'] = this.getField('GASumOfAWDGMV').getValue();
				data['DepletionLimitChgAmt'] = this.getField('GADepleteLimit').getValue();
				data['GDVBaseChgAmt'] = this.getField('GAGDVBase').getValue();
				data['GDVChgAmt'] = this.getField('GAGDV').getValue();
				data['SumOfAWDGDVChgAmt'] = this.getField('GASumOfAWDGDV').getValue();
				data['RemDepletionLimitChgAmt'] = this.getField('GARemDepleteLimit').getValue();

				data['units'] = this.getField('units').getValue();
				data['enableCanc'] = "";
				data['num'] = _controller.getNum();
				data['remarks'] = this.getField('remarks').getValue();
				data['reason'] = this.getField('reason').getValue();
				data['settleDate'] = this.getField('settleDate').getDisplayDateString();
				
				if (this.action == _controller.ADD) {
					data['enableELWA'] = 'no';
				}
			
				return data;
			}												
		})
		
		,incomeBaseDetlPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 700
			,height: 620				
			,defaults: {border: false}
			,modal: true
			,items: [
					{								
						layout:'column'						
						,style: 'padding:10px'										
						,columnWidth: 1
						,defaults: {
								layout:'form'
								,border: false
						}						
						,items:[
							{																
								columnWidth: 0.45							
								,labelWidth: 150								
								,items:[									
									new DesktopWeb.Controls.Label({
										itemId: 'taxTypeDesc'
										,fieldLabel: _translationMap['TaxTypeDesc']
										,width: 120
									})																		
									,new DesktopWeb.Controls.Label({
										itemId: 'transTypeDesc'
										,fieldLabel: _translationMap['TransTypeDesc']
										,width: 140	
									})									
									,new DesktopWeb.Controls.Label({
										itemId: 'tradeDate'
										,fieldLabel: _translationMap['TradeDate']
										,width: 90												
									})																		
									,new DesktopWeb.Controls.Label({
										itemId: 'transNumber'
										,fieldLabel: _translationMap['TransNumber']
										,width: 90
										,allowDecimals: false			
									})																										
								]										
							}																								
							,{								
								columnWidth: 0.55								
								,labelWidth: 200														
								,items:[							 		
							 		new DesktopWeb.Controls.Label({
										itemId: 'guarPayOptDesc'
										,fieldLabel: _translationMap['GuarPayOptDesc']
										,width: 150			
									})																		
									,new DesktopWeb.Controls.Label({
										itemId: 'electionAge'
										,fieldLabel: _translationMap['ElectionAge']
										,width: 90
										,allowDecimals: false			
									})									
									,new DesktopWeb.Controls.Label({
										itemId: 'electionDate'
										,fieldLabel: _translationMap['ElectionDate']
										,width: 90			
									})																		
								]							
							}
						]
					}
					,{		
						xtype: 'fieldset'
						,style: 'margin-top: 5px; margin-bottom: 5px;'					
						,items: [
							_grids['SegIncmBaseGrid']
							]						
					}						
					,{														
						xtype: 'fieldset'										
						,title: _translationMap['AnnuOfMeasAge']
						,layout: 'column'
						,style: 'padding:5px; text-align:left'					
						,columnWidth: 1					
						,defaults: {
							layout: 'form'
							,border: false											
						}
						,items:[																				
							{
								columnWidth: 0.6
								,labelWidth: 120 
								,items:[									
									new DesktopWeb.Controls.Label({
										itemId: 'nameMeasure'
										,fieldLabel: _translationMap['NameMeasure']
										,width: 250 				
									})									
									,new DesktopWeb.Controls.Label({
										itemId: 'ageMeasure'
										,fieldLabel: _translationMap['AgeMeasure']
										,width: 80 			
									})																
								]										
							}																								
							,{
								columnWidth: 0.4
								,labelWidth: 100 
								,items:[									
									new DesktopWeb.Controls.Label({
										itemId: 'statMeasure'
										,fieldLabel: _translationMap['StatMeasure']
										,width: 90 
									})									
									,new DesktopWeb.Controls.Label({
										itemId: 'dofbMeasure'
										,fieldLabel: _translationMap['DofbMeasure']
										,width: 90 		
									})																										
								]							
							}
						]
					}
					,{														
						xtype: 'fieldset'				
						,title: _translationMap['AnnuOfElect']
						,layout: 'column'
						,style: 'padding:5px; text-align:left'						
						,columnWidth: 1						
						,defaults: {
							layout: 'form'
							,border: false											
						}
						,items:[																			
							{
								columnWidth: 0.6
								,labelWidth: 120 
								,items:[									
									new DesktopWeb.Controls.Label({
										itemId: 'nameElection'
										,fieldLabel: _translationMap['NameElection']
										,width: 250			
									})									
									,new DesktopWeb.Controls.Label({
										itemId: 'ageElection'
										,fieldLabel: _translationMap['AgeElection']
										,width: 90			
									})																									
								]										
							}																								
							,{
								columnWidth: 0.4
								,labelWidth: 100								
								,items:[									
									new DesktopWeb.Controls.Label({
										itemId: 'statElection'
										,fieldLabel: _translationMap['StatElection']
										,width: 90			
									})									
									,new DesktopWeb.Controls.Label({
										itemId: 'dofbElection'
										,fieldLabel: _translationMap['DofbElection']
										,width: 90			
									})																																			
								]							
							}
						]
					}														
				]				

			,buttons:[
					new DesktopWeb.Controls.ScreenButton(
						{
							text: _translationMap['Close']
							,handler: function(){
								_popups['incomeBaseDetlPopup'].hide();
							}
						}
					)					
				]					
						
			,init: function(title)
			{						
				this.setTitle(title);																	
				this.clearAllFields();											
			}

			,clearAllFields: function()
			{						
				this.getField('taxTypeDesc').setValue('');
				this.getField('transTypeDesc').setValue('');
				this.getField('transNumber').setValue('');
				this.getField('guarPayOptDesc').setValue('');	
				this.getField('electionAge').setValue('');
				this.getField('tradeDate').setValue('');
				this.getField('electionDate').setValue('');									
				this.getField('nameMeasure').setValue('');
				this.getField('ageMeasure').setValue('');
				this.getField('statMeasure').setValue('');
				this.getField('dofbMeasure').setValue('');					
				this.getField('nameElection').setValue('');
				this.getField('ageElection').setValue('');
				this.getField('statElection').setValue('');					
				this.getField('dofbElection').setValue('');														
			}																																			
		})								

		,deferredIncDetlPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 700
			,height: 680				
			,defaults: {border: false}
			,modal: true
			,items: [
					{								
						layout:'column'
						,style: 'padding:10px'
						,border: false								
						,columnWidth: 1
						,defaults: {
								layout:'form'
								,border: false
						}
						,items:[
							{
								columnWidth: 0.25
								, labelWidth: 100
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'contractTypeDIA'
										,fieldLabel: _translationMap['ContractType']
									})
								]
							}
							, {
								columnWidth: 0.25
								, labelWidth: 100
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'versionDIA'
										,fieldLabel: _translationMap['Version']
									})
								]
							}
							, {
								columnWidth: 0.35
								, labelWidth: 100
								, items:[
									_fields ['asOfDate']
								]
							}
							, {
								columnWidth: 0.15
								, style: 'text-align:right;'
								,items:[
									new DesktopWeb.Controls.ActionButton(		
										{
											itemId: 'refreshBtn'
											,text: _translationMap['RefreshButton']						
											,handler: function(){_controller.reloadDeferredIncData();}
										}
									)
								]
							}
							, {
								columnWidth: 0.5
								, labelWidth: 200
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'totIncmBase'
										,fieldLabel: _translationMap['TotIncmBase']
										,width: 100	
										,style: 'font-weight:bold;'
										,labelStyle: 'font-weight:bold;'										
									})									
								]
							}							
							, {
								columnWidth: 0.5
								, labelWidth: 250
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'ProjFromAccumSerie'
										,fieldLabel: _translationMap['ProjFromAccumSerie']
										,width: 10	
										,labelStyle: 'font-weight:bold;'
									})									
								]
							}							
							, {
								columnWidth: 0.5
								, labelWidth: 200
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'nmcrIncmCr'
										,fieldLabel: _translationMap['NMCRIncmCr']
										,width: 100			
									})									
								]
							}							
							, {
								columnWidth: 0.5
								, labelWidth: 200
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'nonNMCRInmCr'
										,fieldLabel: _translationMap['NonNMCRInmCr']
										,width: 100			
									})									
								]
							}							
							, {
								columnWidth: 0.5
								, labelWidth: 200
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'nmcrMKV'
										,fieldLabel: _translationMap['NMCRMKV']
										,width: 100			
									})									
								]
							}
							, {
								columnWidth: 0.5
								, labelWidth: 200
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'nonNMCRMKV'
										,fieldLabel: _translationMap['NonNMCRMKV']
										,width: 100			
									})
								]
							}
							, {
								columnWidth: 0.5
								, labelWidth: 200
								, items:[
									new DesktopWeb.Controls.Label({
										itemId: 'totLWABase'
										,fieldLabel: _translationMap['TotLWABase']
										,width: 100			
									})									
								]
							}
						]																	
					}
					,{		
						xtype: 'fieldset'
						,style: 'margin-top: 5px; margin-bottom: 5px;'					
						,items: [
							_grids['SegDIAGrid']
							]						
					}							
					,{		
						xtype: 'fieldset'
						,style: 'margin-top: 5px; margin-bottom: 5px;'					
						,items: [
							_grids['SegPenIncmBaseGrid']
							]						
					}	
					,{		
						xtype: 'fieldset'
						,style: 'margin-top: 5px; margin-bottom: 5px;'					
						,items: [
							_grids['SegDIATransactionGrid']
							]						
					}																																
				]				

			,buttons:[										
					new DesktopWeb.Controls.ScreenButton(
						{
							itemId: 'incBaseDetlBtn'								
							,text: _translationMap['IncomeBaseDetlButton']										
							,handler: function(){_controller.openIncomeBaseDetlPopupFromDeferInc()}							
						}
					)
					,new DesktopWeb.Controls.ScreenButton(
						{
							text: _translationMap['Close']
							,handler: function(){
								_popups['deferredIncDetlPopup'].hide();
							}
						}
					)																																
				]					
						
			,init: function(title)
			{						
				this.setTitle(title);																	
				this.clearAllFields();															
			}
			,clearAllFields: function()
			{																	
				this.getField('nmcrIncmCr').setValue('');				
				this.getField('nmcrMKV').setValue('');				
				this.getField('nonNMCRInmCr').setValue('');					
				this.getField('nonNMCRMKV').setValue('');				
				this.getField('totIncmBase').setValue('');																									
				this.getField('totLWABase').setValue('');																									
			}
			,populateRateDialwa: function()
			{
				var rec = _grids['SegPenIncmBaseGrid'].getSelectedRecord();

				this.getField('contractType').setValue(_grids['listOfTerms'].getSelectedRecord().data['contract']);
				this.getField('tradeDate').setValue(rec.data['tradeDate']);
				this.getField('fundType').setValue(rec.data['fund']);
				this.getField('classType').setValue(rec.data['class']);
				this.getField('account').setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
				this.getField('guarDBGPopup').setValue(rec.data['txnDBG']);
				this.getField('guarDMGPopup').setValue(rec.data['txnDMG']);
				
				this.getField('GAGWB').setValue(rec.data['txnGWB']);
				this.getField('GAGwaEwa').setValue(rec.data['txnGAGwaEwa']);
				this.getField('GAAdjustedGwaEwa').setValue(rec.data['txnGAAdjustedGwaEwa']);
				this.getField('GARemainingGwaEwa').setValue(rec.data['txnRemGWA']);
				this.getField('GAGWADeferral').setValue(rec.data['txnGAGWADeferral']);
				this.getField('GABonusBase').setValue(rec.data['txnGABonusBase']);
				this.getField('GALWA').setValue(rec.data['txnGALWA']);
				this.getField('GAAdjustedLWA').setValue(rec.data['txnGAAdjustedLWA']);
				this.getField('GARemainingLWA').setValue(rec.data['txnRemLWA']);
				this.getField('GARemainingGWADeferral').setValue(rec.data['txnGARemainingGWADeferral']);

				this.getField('units').setValue(rec.data['units']);
				this.getField('remarks').setValue(rec.data['remarks']);
				this.getField('reason').setValue(rec.data['reason']);
				this.getField('settleDate').setValue(rec.data['settleDate']);
			}			
																																			
		})	
		,hypoElectPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 280
			,height: 270	
			,title: _translationMap['HypoElect']			
			,defaults: {border: false}
			,modal: true
			,items: [
				{								
					layout:'column'
					,style: 'padding:10px'
					,border: false								
					,columnWidth: 1
					,defaults: {
							layout:'form'
							,border: false
					}
					,items:[
						{
							columnWidth: 1
							, labelWidth: 130
							, items:[
								new DesktopWeb.Controls.Label({
									itemId: 'account'
									,fieldLabel: _translationMap['Account']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'contractType'
									,fieldLabel: _translationMap['ContractType']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'currentDate'
									,fieldLabel: _translationMap['CurBusDate']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'curAge'
									,fieldLabel: _translationMap['CurAge']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'curELWA'
									,fieldLabel: _translationMap['CurELWA']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'todayELWA'
									,fieldLabel: _translationMap['TodayELWA']
								})
							]
						}
					]
				}
			]
			,buttons:[
				new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['Close']
						,handler: function(){
							_popups['hypoElectPopup'].hide();
						}
					}
				)
			]
			,init: function()
			{														
			}
			,populate: function(responseXML)
			{
				this.getField("account").setValue(IFDS.Xml.getNodeValue(responseXML, '//HypoElection/account'));
				this.getField("contractType").setValue(IFDS.Xml.getNodeValue(responseXML, '//HypoElection/contractType'));
				this.getField("currentDate").setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, '//HypoElection/currentDate')));
				this.getField("curAge").setValue(IFDS.Xml.getNodeValue(responseXML, '//HypoElection/curAge'));
				this.getField("curELWA").setValue(IFDS.Xml.getNodeValue(responseXML, '//HypoElection/curELWA'));
				this.getField("todayELWA").setValue(IFDS.Xml.getNodeValue(responseXML, '//HypoElection/todayELWA'));
			}
		})
		,elwaImpactPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 460
			,height: 300
			,title: _translationMap['ELWAImpactTitle']			
			,defaults: {border: false}
			,modal: true
			,items: [
				{								
					layout:'column'
					,style: 'padding:10px'
					,border: false								
					,columnWidth: 1
					,defaults: {
							layout:'form'
							,border: false
					}
					,items:[
						{
							columnWidth: 0.5
							, labelWidth: 90
							, items:[
								new DesktopWeb.Controls.Label({
									itemId: 'account'
									,fieldLabel: _translationMap['Account']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'contractType'
									,fieldLabel: _translationMap['ContractType']
								})
							]
						}
						,{
							columnWidth: 0.5
							, labelWidth: 90
							, items:[
								new DesktopWeb.Controls.Label({
									itemId: 'transTypeDesc'
									,fieldLabel: _translationMap['TransTypeDesc']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'tradeDate'
									,fieldLabel: _translationMap['TradeDate']
								})
							]
						}
						,{
							columnWidth: 1
							, labelWidth: 180
							, items:[
								_grids['elwaImpactGrid']
							]
						}
					]
				}
			]
			,buttons:[
				new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['Close']
						,handler: function(){
							_popups['elwaImpactPopup'].hide();
						}
					}
				)
			]
			,init: function()
			{														
			}
			,populate: function(responseXML, vTransTypeDesc)
			{
				this.getField("account").setValue(IFDS.Xml.getNodeValue(responseXML, '//acct'));
				this.getField("contractType").setValue(IFDS.Xml.getNodeValue(responseXML, '//contractType'));
				this.getField("tradeDate").setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, '//tradeDate')));
				this.getField("transTypeDesc").setValue(vTransTypeDesc);
				
				_grids['elwaImpactGrid'].getStore().loadData(responseXML);
			}
		})	
		
		,depleteLimPopup: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				width: 555
				,defaults: {border: false}
				,modal: true
				,title: _translationMap['DepleteLim']
				,items:[ _tabs['depleteLimPanel']]
				,buttons:[
					new DesktopWeb.Controls.ScreenButton(
						{
							text: _translationMap['Close']
							,handler: function(){
								_popups['depleteLimPopup'].hide();
							}
						}
					)
				]
				,init: function()
				{														
				}
				,populate: function(responseXML)
				{
					var isDBGDMGDepleteLim = IFDS.Xml.getNodeValue(responseXML, '//isDBGDMGDepleteLim') == 'yes';
					var depLimDBG = IFDS.Xml.getNode(responseXML, '//DBGDepleteLim');
					var depLimDMG = IFDS.Xml.getNode(responseXML, '//DMGDepleteLim');
					var depLimPBG = IFDS.Xml.getNode(responseXML, '//PBGDepleteLim');
					
					if(isDBGDMGDepleteLim){
						_grids['depLimDMG'].getStore().loadData(IFDS.Xml.getNode(responseXML, '//DMGDepleteLim')); 
						_tabs['depleteLimPanel'].add(_panels['DMGPanel']);
					}else{
						_fields['pbgPeriodEndDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, '//DLEnfPeriodEndDate')));
						_grids['depLimPBG'].getStore().loadData(IFDS.Xml.getNode(responseXML, '//PBGDepleteLim'));
						_tabs['depleteLimPanel'].add(_panels['PBGPanel']);
					}
					
					if(depLimDBG){
						_grids['depLimDBG'].getStore().loadData(IFDS.Xml.getNode(responseXML, '//DBGDepleteLim'));
						_tabs['depleteLimPanel'].add(_panels['DBGPanel']);
					}
				}
			}
		)		
	} 
	
	
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,buttons: _buttons
		
		,grids: _grids
		
		,panels: _panels
		
		,tabs: _tabs
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				{
					layout: 'column'
					,style: 'padding-left: 10px;padding-bottom: 2px'
					,defaults: {
						layout: 'form'
					}
					,items: [
						{
							width: 300
							,labelWidth: 125
							,items:[
								_fields ['guaranteeToDate']
							]
						}
						,{
							width: 225
							,labelWidth: 100
							,items: [
								_fields ['contractType']

							]
						}
						,{
							width: 100									
							,items: [
								_buttons ['searchButton']
							]
						}
							
					]
				}
			,{
				xtype: 'tabpanel'
				,activeTab: 'Guarantee'
				,style: 'padding-bottom: 10px'
				,items: [
					{
						layout: 'column'
						,height: 82
						,title: _translationMap['Guarantee']
						,id: 'Guarantee'
						,defaults: {
							layout: 'form'
							,style: 'margin: 5px'
						}
						,items: [
							{
								columnWidth: 0.30
								,labelWidth: 90
								,items:[
									_fields ['guarMKV']
									, _fields ['guarIncCredit']
								]
							}
							,{
								columnWidth: 0.30
								,labelWidth: 60
								,items: [
									_fields ['guarDBG']
									,_fields ['guarDMG']
									,_fields ['guarPBG']
								]
							}
							,{
								columnWidth: 0.40
								,labelWidth: 150
								,items: [
									_fields ['guarDBGTopup']
									,_fields ['guarDMGTopup']
								]
							}
						]
					}
					,{
						layout: 'column'
						,height: 112
						,title: _translationMap['GMWB']
						,id: 'GMWB'
						,defaults: {
							layout: 'form'
							,style: 'margin: 5px'
						}
						,items: [
							{
								columnWidth: 0.32
								,labelWidth: 110
								,items:[
									_fields ['guarGWB']
									,_fields ['guarAdjGWA']
									,_fields ['guarAdjLWA']
									,_fields ['guarLWAEntitlement'] 									
								]
							}
							,{
								columnWidth: 0.32
								,labelWidth: 130
								,items: [
									_fields ['guarBonus']
									,_fields ['guarRemGWA']
									,_fields ['guarRemLWA']
									,_fields ['guarLWAExceeded']
								]
							}							
							,{
								columnWidth: 0.35
								,labelWidth: 140
								,items: [									
									_fields ['guarGWADef']
									,_fields ['guarRemGWADef']
									,_fields ['guarIncBaseLWA']
									,_fields ['guarDPAAtAge']
								]
							}							
						]
					}
				]
			}
			,{
				xtype: 'fieldset'
				,title: _translationMap['ListOfTerms']
				,items: [
					_grids['listOfTerms']
				]
			}
			,{
				xtype: 'fieldset'
				,title: _translationMap['TxnEvents']
				,items: [
					{
						layout: 'column'
						,style: 'padding-left:10px; padding-bottom:6px'
						,defaults: {
							layout: 'form'								
						}
						,items: [
							{
								width: 240
								,labelWidth: 110
								,items:[
									_fields ['filterTransactions']
								]
							}
							,{
								width: 385
								,labelWidth: 70
								,items: [										
									{
										layout: 'form'
										,trackLabels: true																																																																													
										,items: [
											_fields ['filterDate']
											,_fields ['filterValue']
										]
									}										
								]
								
							}
							,{
								width: 65									
								,items: [
									_buttons ['filterButton']
								]
							}
								
						]
					}
					,_grids['transaction']
				]
			}
			,{
				xtype: 'fieldset'					
				,title: _translationMap['GuarImpact']
				,items: [
					_grids['guaranteeImpact']
				]
			}
			
			]																				
		})
		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton(
				{
					id: 'ELWAImpactBtn'
					,text: _translationMap['ELWAImpact']
					,handler: function(){_controller.openELWAImpactPopup()}
					,disabled: true
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					id: 'hypoElectBtn'								
					,text: _translationMap['HypoElectBtn']					
					,handler: function(){_controller.openHypoElectionPopup()}
					,disabled: true					
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					id: 'DepleteLimBtn'
					,text: _translationMap['DepleteLim']
					,handler: function(){_controller.openDepleteLimPopup()}
					,disabled: true	
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					id: 'diaInfoBtn'								
					,text: _translationMap['DIAInfoButton']					
					,handler: function(){_controller.openDeferredIncDetlPopup()}							
				}
			)				
			,new DesktopWeb.Controls.ScreenButton(
				{
					id: 'YearlyGWB'
					,text: _translationMap['YearlyGWB']
					,handler: function(){
						_controller.openGWBYearlyPopup();
						_popups['yearlyGWBPopup'].show();
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function(){						
						DesktopWeb.Util.commitScreen()}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}