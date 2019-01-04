/*********************************************************************************************
 * @file	AcctGovFile.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Tax Payer Maintenance screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	20 Jan 2014 Narin Suanlamyai P0223930 FN01 - FATCA 1C
 *					- Remove Modify feature
 *					- Rearrangment screen to support new system design
 *					- Add a new table to display holding details
 *
 *	26 Feb 2014 G. Thawornwachirakun P0223930 DFT0029664 T54848
 *					- Arrange layout follow the relabel from Indicia Status 
 *					to Due Diligence Status
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  17 Jul 2017 Matira T. P0264940 P0264940-50 FATCA - CRS Coc
 *          - Add to support 'CRS' Tax regulation
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 675;
	var _layoutWidth = 720;
	var _labelWidthFirstColumn = 90;
	var _labelWidthSecondColumn = 95;
	var _labelWidthGovFileDetails = 150;
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Search']
			,disabled: true
			,listeners: {
				click: function(){_controller.clickHandle_searchBtn();}
			}
		})		
	}
	
	// **** fields ****
	var _fields = {		
		acctFld: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['Account']
				,smartview: 'accountSearch'				
				,fields: ['displayValue', 'acctNum']
				,valueField: 'acctNum'								
				,width: 275
				,allowBlank: true
				,addtlSearchParams: [{name: 'incAllStat', valueFn: function(){return 'yes'}}]
			}
		)
		,regulationCode: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['Regulation']
				,width: 160
				,editable: true
				,allowBlank: false
		        ,listeners: 
		        {
		            change: function(fld, newValue)
		            {        
		                _controller.clickHandle_Status(newValue);
		                _fields['docStat'].reset();
		            }
		        }
			}
		)
		,docStat: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['Status']
				,width: 160
				,editable: true
				,allowBlank: false
			}
		)
		,entityAcct: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['EntityAccount']
				,width: 175
				,editable: true
				,allowBlank: false
			}
		)
		,startDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['StartDate']
				,width: 100
				,allowBlank: false
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		,endDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['EndDate']
				,width: 100
				,allowBlank: false
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		,taxType: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['TaxType']
				,width: _labelWidthGovFileDetails
				,text: ''
			}
		)
		,acctType: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['AccountType']
				,width: _labelWidthGovFileDetails
				,text: ''
			}
		)
		,acctStat: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['AccountStatus']
				,width: _labelWidthGovFileDetails
				,text: ''
			}
		)
		,acctOpenDate: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['AcctOpenDate']
				,width: 100
				,allowBlank: false
			}
		)
	}
	
	// **** grids ****
	var _grids = {
		govFileGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 12				
				,autoScroll: true
				,height: 160
				,autoExpandColumn: 'account'
				,store: new Ext.data.XmlStore(
					{
						record: 'IndiciaSearchResultDetl'
						,fields: ['FATCADueDiligenceUUID', 'account', 'asOfDate', 'runDate', 'indiciaFound', 'status'
									, 'acctType', 'acctStatus', 'taxType', 'FATCACode', 'acctOpenDate']
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									record.data.asOfDate = DesktopWeb.Util.getDateDisplayValue(record.data.asOfDate);
									record.data.runDate = DesktopWeb.Util.getDateDisplayValue(record.data.runDate);
									record.data.acctOpenDate = DesktopWeb.Util.getDateDisplayValue(record.data.acctOpenDate);
								});
								 store.fireEvent('datachanged', store); //to set data in grid again
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.selectGovFileMstr(record);
								}
							}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
							,sortable: false
						}
						,columns: [
							{id: 'account', header: _translationMap['Account'], dataIndex: 'account'}
							,{header: _translationMap['Regulation'], dataIndex: 'FATCACode'
								, renderer: function(val){
									return (_controller.getDisplay('RegulationList', val));
								}
								, width: 130}
							,{header: _translationMap['IndiciaSearch'], dataIndex: 'indiciaFound', width: 120}
							,{header: _translationMap['Status'], dataIndex: 'status'
								, renderer: function(val){
									return (_controller.getDisplay('RequestStatusALL', val));
								}
								, width: 125}
							,{header: _translationMap['ReviewDate'], dataIndex: 'runDate', width: 100}
							,{header: _translationMap['EffectiveDate'], dataIndex: 'asOfDate', width: 100}
						]							
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'moreBtn'
							,text: _translationMap['More']
							,disabled: true
							,handler: function(){_controller.clickHandle_moreBtn();}
						}
					)
				]
			}
		)
		,entityDetailsGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 12
				,autoScroll: true
				,height: 110
				,autoExpandColumn: 'entityName'
				,store: new Ext.data.XmlStore(
					{
						record: 'EntityDetl'
						,fields: ['indiciaFoundUUID', 'entityID', 'entityType', 'name', 'fieldSource', 'fieldValue', 'cntry']
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
							,sortable: false
						}
						,columns: [
							{id: 'entityType', header: _translationMap['EntityType'], dataIndex: 'entityType', width:125}
							,{header: _translationMap['Name'], id: 'entityName', dataIndex: 'name'}
							,{header: _translationMap['FieldName'], dataIndex: 'fieldSource', width: 125}
							,{header: _translationMap['FieldValue'], dataIndex: 'fieldValue', width: 125}
							,{header: _translationMap['Country'], dataIndex: 'cntry', width: 125}
						]							
					}
				)
				,buttons: [
				]
			}
		)
		,holdingDetlsGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 12
				,autoScroll: true
				,height: 110
				,autoExpandColumn: 'acctOwner'
				,store: new Ext.data.XmlStore(
					{
						record: 'AcctBalanceDetl'
						,fields: ['acctOwner', 'FATCABalanceUUID', 'acctBalId', 'RFFILevel', 'RFFICode'
									, 'cntryOfDomicile', 'holdingBal', 'aggrBal', 'curr']
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
							,sortable: false
						}
						,columns: [
							{id: 'acctOwner', header: _translationMap['AccountOwner'], dataIndex: 'acctOwner'}
							,{id: 'reportingFFI', header: _translationMap['ReportingFFI'], dataIndex: 'entityType', width: 120
								,renderer: function(val, metaData, record){
									return (record.data['RFFILevel'] + ' - ' + record.data['RFFICode'])}
							}
							,{header: _translationMap['CountryOfRFFI'], dataIndex: 'cntryOfDomicile', width: 120}
							,{header: _translationMap['HoldingBalance'], dataIndex: 'holdingBal', width: 110}
							,{header: _translationMap['AggregateBalance'], id: 'aggrBal', dataIndex: 'aggrBal', width: 110}
							,{header: _translationMap['Currency'], dataIndex: 'curr', width: 80}
						]							
					}
				)
				,buttons: [
				]
			}
		)
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
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					{
						itemId: 'mainLayout'
						,xtype:'fieldset'
						,title: _translationMap['title']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth
						,items: [
							{
								// Row#1 Col#1
								layout: 'form'
								,columnWidth: 0.57
								,autoHeight:true
								,labelWidth: _labelWidthFirstColumn
								,items :[
									_fields['acctFld']
									, _fields['entityAcct']
								]
							}
							,{
								// Row#1 Col#2
								layout: 'form'
								,columnWidth: 0.43
								,autoHeight:true
								,labelWidth: _labelWidthSecondColumn + 25
								,items :[
									_fields['regulationCode']
									,_fields['docStat']
								]
							}
							,{
								// Row#3 Col#1
								layout: 'form'
								,columnWidth: 0.57
								,autoHeight:true
								,labelWidth: _labelWidthFirstColumn
								,items :[
									_fields['startDate']
								]
							}
							,{
								// Row#3 Col#2
								layout: 'form'
								,columnWidth: 0.33
								,autoHeight:true
								,labelWidth: _labelWidthSecondColumn + 25
								,items :[
									_fields['endDate']
								]
							}
							,{
								// Row#2 Col#3
								layout: 'form'
								,columnWidth: 0.10
								,autoHeight:true
								,labelWidth: _labelWidthSecondColumn
								,items :[
									_buttons['searchBtn']
								]
							}
						]
					}
					,{
						xtype:'fieldset'
						,title: _translationMap['SearchResult']
						,layout: 'column'
						,style: 'margin-bottom:10px'
						,width: _layoutWidth
						,items: [
							_grids['govFileGrid']
						]
					}
					,{
						xtype:'fieldset'
						,title: ""
						,layout: 'column'
						,style: 'margin-bottom:10px;border:none'
						,width: _layoutWidth
						,items: [
							{
								// Col#1
								layout: 'form'
								,columnWidth: 0.5
								,autoHeight:true
								,labelWidth: _labelWidthFirstColumn + 80
								,items :[
									_fields['taxType']
									,_fields['acctType']
								]
							}
							,{
								// Col#2
								layout: 'form'
								,columnWidth: 0.5
								,autoHeight:true
								,labelWidth: _labelWidthFirstColumn + 80
								,items :[
									_fields['acctOpenDate']
									,_fields['acctStat']
								]
							}
						]
					}
					,{
						xtype:'fieldset'
						,title: _translationMap['IndiciaSearchResult']
						,layout: 'column'
						,style: 'margin-bottom:10px;'
						,width: _layoutWidth
						,autoHeight:true
						,items: [
							_grids['entityDetailsGrid']
						]
					}
					,{
						xtype:'fieldset'
						,title: _translationMap['HoldingDetails']
						,layout: 'column'
						,style: 'margin-bottom:10px;'
						,width: _layoutWidth
						,autoHeight:true
						,items: [
							_grids['holdingDetlsGrid']
						]
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){
						DesktopWeb.Util.cancelScreen();
					}
				}
			)
		]			
	}
}