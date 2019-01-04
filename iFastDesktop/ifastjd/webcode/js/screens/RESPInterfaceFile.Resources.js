/*********************************************************************************************
 * @file	RESPInterfaceFile.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Interface File screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 C. Daecha P0181067 CHG0034430 T54333
 *                        - Fix display date format follows dateFormatDisplay parameter
 *
 *  24 Jan 2014 C. Daecha, CHG0033576 - RESP Interface File Issue.
 *                        - Fix record picking logic for RESP interface files which have the same file name
 *
 *  20 May 2014 Narin SuanlamyaiP0220132 FN03 T55087
 *						  - Enhanced for CCS - SAGES RESP Program
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 485;
	var _layoutWidth = 750;
	var _labelWidth = 85;
	
	// **** fields ****
	var _fields = {		
		acctFld: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['Account']
				,smartview: 'accountSearch'				
				,fields: ['displayValue', 'acctNum']						
				,valueField: 'acctNum'								
				,width: 525				
				,allowBlank: false	
				,disabled: true
				,listeners:{
					change: function(){
						if (this.getValue() != "")
						{
							_controller.changeHandler_acctFld(this.getValue());
						}
					}
				}
			}
		)
		,allChkbox: new DesktopWeb.Controls.Checkbox(
			{
				fieldLabel: _translationMap['All']
				,checked: true
				,hideLabel: false
				,listeners:{
					check: function(fld, checked){
						_controller.checkHandle_allChkbox(checked);
					}
				}
			}
		)
		,benList: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['Beneficiary']
				,width: 175
				,editable: false
				,autoSelect: true
			}
		)
		,fileTypeList: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['fileType']
				,width: 175
				,editable: false
				,autoSelect: true
				,listeners: {
					select: function(combo, record, index){
						_controller.selectFileTypeList(record.get('code'));
					}
				}
			}
		)
		,taxYearList: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['taxYear']
				,width: 100
				,editable: false
				,autoSelect: true
			}
		)
		,recTypeList: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['recType']
				,width: 175
				,editable: false
				,autoSelect: true
			}
		)
	}
	
	// **** grids ****
	var _grids = {
		fileListGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: _layoutWidth - 12
				,autoScroll: true
				,height: 150
				,autoExpandColumn: 'fileName'
				,store: new Ext.data.XmlStore(
					{
						record: 'FileDetail'
						,fields: ['recID','fileNam', 'acct', 'benName', 'recTyp', 'taxYear', 'procDate', 'NEQ']
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									var fileRecordsXML = _controller.getFileRecordsXML(record.data['recID']);

									record.data['procDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['procDate']);
									record.fileRecords = IFDS.Xml.serialize(fileRecordsXML);
								});
								store.fireEvent('datachanged', store);
								_grids['fileListGrid'].getSelectionModel().selectFirstRow();
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
									_controller.selectFileList(record);
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
							{id: 'fileName', header: _translationMap['fileName'], dataIndex: 'fileNam', width: 170}
							,{header: _translationMap['Account'], dataIndex: 'acct', width: 100}
							,{header: _translationMap['Beneficiary'], dataIndex: 'benName', width: 165}
							,{header: _translationMap['recType'], dataIndex: 'recTyp', width: 100}
							,{header: _translationMap['procDate'], dataIndex: 'procDate', width: 100}
							,{header: _translationMap['neq'], dataIndex: 'NEQ', width: 75}
						]
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'moreBtn'
							,text: _translationMap['More']
							,handler: function(){_controller.clickHandle_moreBtn();}
						}
					)
				]
			}
		)
		,fieldSetGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: _layoutWidth - 12
				,title: ''
				,autoScroll: true
				,height: 175
				,store: new Ext.data.XmlStore(
					{
						record: 'fileRecord'
						,fields: ['fieldNam1', 'fieldVal1', 'fieldNam2', 'fieldVal2']
						,listeners: {
							load: function(store, records)
							{
								_grids['fieldSetGrid'].getSelectionModel().lock();
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
									_controller.setSelectedEntry(record);
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
							{header: _translationMap['fieldName'], dataIndex: 'fieldNam1', width: 195}
							,{header: _translationMap['fieldValue'], dataIndex: 'fieldVal1', width: 160}
							,{header: _translationMap['fieldName'], dataIndex: 'fieldNam2', width: 195}
							,{header: _translationMap['fieldValue'], dataIndex: 'fieldVal2', width: 160}
						]
					}
				)
				,buttons: [
				]
			}
		)

	}

	// **** popups ****
	var _popups = {
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
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
						,title: _translationMap['titleSearchResult']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth
						,items: [
							{
								// Row#1
								layout: 'form'
								,columnWidth: 0.9
								,autoHeight:true
								,labelWidth: _labelWidth
								,items :[
									_fields['acctFld']
								]
							}
							,{
								// Row#2
								itemId: 'chkboxLayout'
								,layout: 'form'
								,columnWidth: 0.1
								,autoHeight:true
								,labelWidth: 20
								,style: 'padding-left:10px;'
								,items :[
									_fields['allChkbox']
								]
							}
							,{
								// Column#1
								layout: 'form'
								,columnWidth: 0.45
								,autoHeight:true
								,labelWidth: _labelWidth
								,items :[
									_fields['benList']
									,_fields['taxYearList']
								]
							}
							,{
								// Column#2
								layout: 'form'
								,columnWidth: 0.45
								,autoHeight:true
								,labelWidth: _labelWidth
								,items :[
									_fields['fileTypeList']
									,_fields['recTypeList']
								]
							}
							,{
								// Column#3
								layout: 'form'
								,columnWidth: 0.10
								,autoHeight:true
								,labelWidth: _labelWidth
								,items :[
									new DesktopWeb.Controls.Label(
										{
											fieldLabel: ' '
											,labelSeparator: ''
										}
									)
									,new DesktopWeb.Controls.ActionButton(
										{
											itemId: 'searchBtn'
											,text: _translationMap['Search']
											,handler: function(){_controller.clickHandle_searchBtn();}
										}
									)
								]
							}
						]
					}
					,{
						xtype:'fieldset'
						,title: _translationMap['SearchResults']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth
						,items: [
							_grids['fileListGrid']
							,_grids['fieldSetGrid']
						]
					}
				]
			}
		)
		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){DesktopWeb.Util.commitScreen()}
				}
			)
		]
	}
}