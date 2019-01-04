/*********************************************************************************************
 * @file	TrailerFeeInquiry.Resources.js	
 * @author	Narin Suanlamyai
 * @desc	Resources JS file file for Trailer Fee Inquiry screen
 *********************************************************************************************/
/*
 * Procedure: TrailerFeeInquiry.Resources.js
 *
 * Purpose  : Resources JS file file for Trailer Fee Inquiry screen
 *             
 * Notes    : System Maintenance --> Trailer Fee Inquiry
 *
 * History  :  
 *		07 May 2014 N. Suanlamyai P0225140 T55105
 *					- Created
 *
 *		02 Jun 2014 N. Suanlamyai P0225140 DFT0034605 T55222
 *					- Fixed Start Date and End Date fields are not accepting February.
 *
 *		19 Aug 2014 N. Suanlamyai P0225140 DFT0039094 T55596
 *					- Once account number is entered, Broker/Branch/Rep option selection could not available.
 *
 *		12 Sept 2014 N. Suanlamyai P0225140 DFT0040634 T55671
 *					- Allow user to search combination of Broker/Bran/Rep and Account and Fund/Class.
 *
 */
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 590;
	var _layoutWidth = 625;
	
	var _suggestFieldWidth = 335
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,handler: function(){
				if (_controller.searchIsValid())
				{
					_controller.doSearch();
				}
			}
			,style: 'position:relative; left:75'
		})
	}
	
	// **** fields ****
	var _fields = {
		brokerFld: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Broker']
			,smartview: 'brokerSearch'
			,addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'no';}}]
			,fields: ['displayValue', 'agencyCode']
			,valueField: 'agencyCode'
			,width: _suggestFieldWidth
			,allowBlank: false
			,listeners:{
				populated: function(){
					if (_controller.salesRepByBranch)
					{
						_fields['branchFld'].reset();
						_fields['branchFld'].enable();						 
					}else{
						_fields['slsrepFld'].reset();
						_fields['slsrepFld'].enable();
					}
					
				}
				,cleared: function(){
					if (_controller.salesRepByBranch){
						_fields['branchFld'].reset();
						_fields['branchFld'].disable();
					}
					_fields['slsrepFld'].reset();
					_fields['slsrepFld'].disable();

				}
			}
		})

		,branchFld: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Branch']
			,smartview: 'branchSearch'				
			,fields: ['displayValue', 'branch']
			,addtlSearchParams: [
				{name: 'agencyCode', valueFn: function(){return _fields['brokerFld'].getValue();}}
				,{name: 'onlyActive', valueFn: function(){return 'no';}}
			]
			,valueField: 'branch'
			,width: _suggestFieldWidth
			,disabled: true
			,allowBlank: false
			,listeners:{
				populated: function(){
					_fields['slsrepFld'].reset();
					_fields['slsrepFld'].enable();
				}
				,cleared: function(){						 
					_fields['slsrepFld'].reset();
					_fields['slsrepFld'].disable();
				}
			}
		})

		,slsrepFld: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['SalesRep']
			,smartview: 'salesRepSearch'
			,fields: ['displayValue', 'agentCode']
			,addtlSearchParams: [
				{name: 'agencyCode', valueFn: function(){return _fields['brokerFld'].getValue();}}
				,{name: 'branch', valueFn: function(){return _fields['branchFld'].getValue();}}
				,{name: 'onlyActive', valueFn: function(){return 'no';}}
			]
			,valueField: 'agentCode'
			,width: _suggestFieldWidth
			,disabled: true
			,allowBlank: false
		})
		,acctFld: new DesktopWeb.Controls.SuggestField({
            fieldLabel: _translationMap['Account']
            ,smartview: 'accountSearch'
            ,addtlSearchParams: [
				{name: 'incAllStat', valueFn: function(){return 'yes';}}
			]
			,fields: ['displayValue', 'acctNum']
            ,valueField: 'acctNum'
            ,width: _suggestFieldWidth
		})
		,fundFld: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Fund']
			,smartview: 'fundOnlySearch'
			,addtlSearchParams: [
				{name: 'inclInactive', valueFn: function(){return 'yes'}}
			]
			,fields: ['fndDisp', 'fundCode']
			,valueField: 'fundCode'
			,displayField: 'fndDisp'
			,width: 235 
			,listeners:{
				populated: function(fld, record){
					_controller.handleFundPopulated(record.data['fundCode']);
				}
				,cleared: function(){
					_fields['classFld'].reset();
					_fields['classFld'].disable();
				}
			}
		})		
		,classFld: new DesktopWeb.Controls.ComboBox({
			fieldLabel: _translationMap['Class']
			,width: 50
			,autoSelect: true
			,disabled: true
			,store: new Ext.data.XmlStore({
				record: 'ClassInfo'
				,fields: ['classCode']
				,listeners: {
					load: function(store, records){
						if (records.length > 0){ 
							_fields['classFld'].setValue(records[0].data['classCode']);
						}
					}
				}	
			})
			,valueField: 'classCode'
			,displayField: 'classCode'
		})
		,startDateFld: new Ext.form.DateField({
			fieldLabel: _translationMap['StartDate']
			,width: 80
			,allowBlank: false
			,format: 'm/y'
			,emptyText: 'MM/YY'
			,plugins: 'monthPickerPlugin'
		})
		,endDateFld: new Ext.form.DateField({
			fieldLabel: _translationMap['EndDate']
			,width: 80
			,allowBlank: false
			,format: 'm/y'
			,emptyText: 'MM/YY'
			,plugins: 'monthPickerPlugin'
		})
	}
	
	// **** grids ****
	var _grids = {
		trlSumGrid: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true							
			,height: 175
			,autoExpandColumn: 'fund'				
			,store: new Ext.data.XmlStore({
				record: 'TrailerFee'
				,fields: [
						  'recordID'
						  ,'fund' 
						  ,'class'
						  ,'totAmtByFund'
						  ]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.handleSummaryRecordSelectChange(record.data['fund'], record.data['class']);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{id: 'fund', header: _translationMap['Fund'], dataIndex: 'fund'}
					,{header: _translationMap['Class'], dataIndex: 'class', width: 225}
					,{header: _translationMap['PaidAmount'], dataIndex: 'totAmtByFund', width:200}
				]
			})				
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,disabled: true
					,handler: function(){_controller.doReload()}
				})
			]			
		})
		,trlDetlGrid: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true							
			,height: 150
			,autoExpandColumn: 'paymentDate'				
			,store: new Ext.data.XmlStore({
				record: 'TrailerFeeDetl'
				,fields: [
						  'detlId'
						  ,'paymentDate' 
						  ,'paidAmount'
				]
				,listeners: {
					load: function(store, records)
					{
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					//rowselect: function(selModel, index, record){_controller.handleRecordSelectChange(record.data['detlId']);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{id: 'paymentDate', header: _translationMap['PaymentDate'], dataIndex: 'paymentDate'}
					,{header: _translationMap['PaidAmount'], dataIndex: 'paidAmount', width:200}
				]
			})				
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,disabled: true
					,handler: function(){_controller.loadMoreDetailsTable()}
				})
			]			
		})
	}
	
	// **** popups ****
	var _popups = {} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,buttons: _buttons
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth				
			,items: [					
				{
					layout: 'column'
					,defaults: {
						layout: 'form'
						,labelWidth: 75
					}
					,items: [
						{								
							columnWidth: 0.71
							,items: [
								_fields['brokerFld']
								,_fields['branchFld']
								,_fields['slsrepFld']
								,_fields['acctFld']
							]
						}
						,{
							columnWidth: 0.29
							,labelWidth: 75
							,items: [
								_fields['startDateFld']
								,_fields['endDateFld']
							]
						}
						,{								
							columnWidth: 0.53
							,items: [
								_fields['fundFld']
							]
						}
						,{								
							columnWidth: 0.17
							,labelWidth: 30
							,items: [
								_fields['classFld']
							]
						}
						,{
							columnWidth: 0.3
							,labelWidth: 65
							,items: [
								_buttons['searchBtn']
							]
						}
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['SummaryByFundClass']
					,width: _layoutWidth
					,items: _grids['trlSumGrid']
					,style: "padding-top:10px"
				}										
				,{
					xtype: 'fieldset'
					,title: _translationMap['DetailsByPaymentDate']
					,width: _layoutWidth
					,items: _grids['trlDetlGrid']
					,style: "padding-top:10px"
				}										
			]																				
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Close']
				,handler: function(){
					DesktopWeb.Util.cancelScreen();
				}
			})
		]				
	}
}