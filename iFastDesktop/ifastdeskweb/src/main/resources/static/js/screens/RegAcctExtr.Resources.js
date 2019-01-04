
/*********************************************************************************************
 * @file	RegAcctExtr.Resources.js
 * @author	Matira Thanetkulabut
 * @desc	Resources file for Reportable Accounts Extract screen
 *********************************************************************************************/
/*
 *	Navigate: Menu > System Maintenance > Reportable Accounts Extract
 *	
 *	History : 
 *	
 *	20-Nov-2017 Matira Thanetkulabut P0268205-34 FATCA-CRS Enhancement 18.2
 *				- Initial
 *
 *	08-Dec-2017 Matira Thanetkulabut P0268205-60 FATCA-CRS 18.2 QV2
 *				- Approve, detail functionality and fix some issues
 *
 *	25-Dec-2017 Matira Thanetkulabut P0268205-88 DFT0079829
 *				- Display Error message
 *
 *	09-Jan-2018 Matira Thanetkulabut P0268205-108 DFT0080147
 *				- Fix display incorrectly in options popup
 *
 *	22-Jan-2018 Matira Thanetkulabut P0268206-125
 *				- Move Add, Refresh, Correct, Suppress, UnSuppress functionalities to Review screen
 *
 *	07-Feb-2018 Matira Thanetkulabut P0268206-130 DFT0081020
 *				- Support new request status "Correction Pending"
 *
 *  14-Mar-2018 Matira Thanetkulabut P0268206-161 DFT0082239
 *				- Display error/warning flag at Account level to indicate that on sub-level has some error/warning
 *
 *  7-Aug-2018  Sadia Imtiaz P0277308-213 DFT0085314 
 *  			- field "Regulation" was overriding reporting year for Modify popup due to change listener on it 	
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth  = 750;

	// **** fields **** 
	var _fields = {
		regulationFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['Regulation']
			,width: 150
			,editable: true
			,allowBlank: false
			,tabIndex: 1
			,listeners:{
				select: function(){_controller.loadDropdown(this.getValue(),"init");}
			}
		})
		,rfiDomicileFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['RFIDomicile']
			,width: 150
			,editable: true
			,allowBlank: true
			,tabIndex: 2
		})
		,reportingYearFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['ReportingYear']
			,width: 150
			,editable: true
			,allowBlank: false
			,tabIndex: 3
		})
		,extractStatFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['RequestStat']
			,width: 150
			,editable: true
			,tabIndex: 4
		})
	}

	// **** buttons ****
	var _buttons = {	
        searchBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,handler: function(){_controller.doSearch();}
		})
		,extractBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Extract']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.doExtract("extract");}
		})
		,optBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Options']
			,style: "margin-right: 5px"
			,listeners: {}
		})
		,approveBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Approve']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.doExtract("approve");}
		})
		,addBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Add']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.openPopup("snapReqPopup", _controller.ADD);}
		})
		,modBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Modify']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.openPopup("snapReqPopup", _controller.MOD);}
		})
		,delBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Delete']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.openPopup("snapReqPopup", _controller.DEL);}
		})
		,detlBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Details']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.moreDetl();}
		})
		,reviewBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Review']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){
				var selected = _grids['reportAccts'].getSelectedRecord();
				_controller.goToScreen("RegAcctInfoRev",selected);
				
			}
		})
		,rfiDetlBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['RFIDetail']
			,disabled: true
			,handler: function(){
				var selected = _grids['RFIs'].getSelectedRecord();
				_controller.goToScreen("FinanInst",selected);
			}
		})
		,moreBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['More']
			,disabled: true
			,handler: function(){_controller.getMore();}
		})
	}
  
	// **** grids ****
	var _grids = {
		regulation: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 20
			,autoScroll: true
			,height: 145
			,store: new Ext.data.XmlStore({
				record: 'regExtrMstr'
				,fields: ['hasErrorAtSubLvl', 'errMsg', 'regulation', 'reportingYear', 'domicileCntry', 'TPSEffDate', 'extractStat', 'regExtrMstrUUID']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['TPSEffDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['TPSEffDate']);
						});	
						store.fireEvent('datachanged', store);
					}
					,update: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['TPSEffDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['TPSEffDate']);
						});	
					}
					,add: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['TPSEffDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['TPSEffDate']);
						});	
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.setSelected("regulation",record);}
					,rowdeselect: function(){_controller.setSelected("regulation",null);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [
					{id: 'errMsg', width: 25,
						renderer: function(val, metaData, record){
							return _controller.getDisplayNumberWithError('mstr', val, record);
						}}
					,{header: _translationMap['Regulation'], dataIndex: 'regulation', width: 100,
						renderer: function(value){ return (_controller.getDesc('regulations', value))}}
					,{header: _translationMap['ReportingYear'], dataIndex: 'reportingYear', width: 100}
					,{header: _translationMap['RFIDomicile'], dataIndex: 'domicileCntry', width: 200,
						renderer: function(value){ return (_controller.getDesc('RFIDomiciles', value))}}
					,{header: _translationMap['TPSEffDate'], dataIndex: 'TPSEffDate', width: 150}
					,{header: _translationMap['RequestStat'], dataIndex: 'extractStat', width: 120,
						renderer: function(value){ return (_controller.getDesc('extractStat', value))}}
				]
			})
		})
		,reportAccts: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 30
			,autoScroll: true
			,height: 160
			,store: new Ext.data.XmlStore({
				record: 'regExtrAcct'
				,fields: ['errMsg', 'regExtrAcctUUID', 'account', 'acctType', 'acctStat', 'acctRecordType', 'acctRecordID', 'acctRecordMethod', 'acctRecordStat', 'hasErrorAtSubLvl']
				,listeners: {}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.setSelected("reportAccts",record);}
					,rowdeselect: function(){_controller.setSelected("reportAccts",null);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [
					{id: 'errMsg', width: 25,
						renderer: function(val, metaData, record){
							return _controller.getDisplayNumberWithError('account', val, record);
						}}
					,{header: _translationMap['Account'], dataIndex: 'account', width: 120}
					,{header: _translationMap['AcctType'], dataIndex: 'acctType', id: 'accountType', width: 100,
						renderer: function(value){ return (_controller.getDesc('acctType', value))}}
					,{header: _translationMap['AcctStat'], dataIndex: 'acctStat', width: 80,
						renderer: function(value){ return (_controller.getDesc('acctStat', value))}}
					,{header: _translationMap['RecType'], dataIndex: 'acctRecordType', width: 80,
						renderer: function(value){ return (_controller.getDesc('acctRecordType', value))}}
					,{header: _translationMap['RecSeq'], dataIndex: 'acctRecordID', width: 60}
					,{header: _translationMap['AcctRecordStat'], dataIndex: 'acctRecordStat', width: 100,
						renderer: function(value){ return (_controller.getDesc('acctRecordStat', value))}}
					,{header: _translationMap['ExtractMethod'], dataIndex: 'acctRecordMethod', width: 100,
						renderer: function(value){ return (_controller.getDesc('acctRecordMethod', value))}}
					
				]
			})
		})
		,RFIs: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 30
			,autoScroll: true
			,height: 120
			,store: new Ext.data.XmlStore({
				record: 'regExtrRFI'
				,fields: ['errMsg', 'FILevel', 'FICode', 'FIName', 'domicileCntry']
				,listeners: {}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.setSelected("RFIs",record);}
					,rowdeselect: function(){_controller.setSelected("RFIs",null);}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [
					{header: _translationMap['RFILevel'], dataIndex: 'FILevel', width: 150,
						renderer: function(value){ return (_controller.getDesc('FILevel', value))}}
					,{header: _translationMap['RFICode'], dataIndex: 'FICode', width: 60}
					,{header: _translationMap['Name'], dataIndex: 'FIName', width: 250}
					,{header: _translationMap['Domicile'], dataIndex: 'domicileCntry', width: 150,
						renderer: function(value){ return (_controller.getDesc('RFIDomiciles', value))}}
				]
			})
		})
	}

	// **** popups ****
	var _popups = {
		snapReqPopup: new DesktopWeb.AdvancedControls.PopupWindow(
		{
			width: 310
			,action: null
			,closeAction: 'hide'
			,modal: true
			,autoHeight: true
			,defaults: {border:false}
			,items: [ 
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center;font-weight:bold;'	
				}
				,{
					layout: 'form'
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 115
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqRegulation'
							,fieldLabel: _translationMap['Regulation']
							,width: 150
							,editable: true
							,allowBlank: false
							,disable: true
							,listeners:{
								select: function(){_controller.loadDropdown(this.getValue(),"popup");}
							}
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqreportingYear'
							,fieldLabel: _translationMap['ReportingYear']
							,width: 150
							,allowBlank: false
							,listeners:{}
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqRFIDomicile'
							,fieldLabel: _translationMap['RFIDomicile']
							,width: 150
							,editable: true
							,allowBlank: false 
							,listeners:{
							}
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'filReqTPSEffDate'
							,fieldLabel: _translationMap['TPSEffDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})	
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if(_popups['snapReqPopup'].isValid()){
							if(_popups['snapReqPopup'].action == _controller.MOD){
								var oldVal = _grids['regulation'].getSelectedRecord().data['TPSEffDate'];
								var newVal = DesktopWeb.Util.convertDateStringFormat(
															_popups['snapReqPopup'].getField('filReqTPSEffDate')
															.getSMVDateString(),"dmy","mdy");
								
								if(oldVal != newVal){
									if(_popups['snapReqPopup'].isValid()){
										_controller.doUpdateRegulation(_popups['snapReqPopup'].getData(), 
																	   _popups['snapReqPopup'].action);
									}
								}else{
									_popups['snapReqPopup'].hide();
								}
							}else{
									_controller.doUpdateRegulation(_popups['snapReqPopup'].getData(), 
																   _popups['snapReqPopup'].action);
							}
						}
					}
				})
			   ,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function()
					{
						_popups['snapReqPopup'].hide();
					}
			   })
			]
			,init: function(action)
			{
				var popup = _popups['snapReqPopup'];
				popup.action = action;
				switch(action)
				{
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['SnapshotReq'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['SnapshotReq'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['SnapshotReq'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action)
			{
				var popup = _popups['snapReqPopup'];
				popup.clearAllFields();
				popup.enableAllFields();

				if(action == _controller.MOD || action == _controller.DEL)
				{
					var selected = _grids['regulation'].getSelectedRecord();
					popup.uuid = selected.data['regExtrMstrUUID'];

					popup.getField('filReqRegulation').setValue(selected.data['regulation']);
					_controller.loadDropdown(selected.data['regulation'],"popup");
					popup.getField('filReqreportingYear').setValue(selected.data['reportingYear']);
					popup.getField('filReqTPSEffDate').setValue(selected.data['TPSEffDate']);
					popup.getField('filReqRFIDomicile').setValue(selected.data['domicileCntry']);
					
					// allow to modify only filReqTPSEffDate field
					popup.getField('filReqRegulation').disableField();;
					popup.getField('filReqreportingYear').disableField();
					popup.getField('filReqRFIDomicile').disableField();
				}
				
				if (popup.rendered) popup.syncSize();
			}
			,getData: function()
			{
				var popup = _popups['snapReqPopup'];
				var data = {};
				var runMode = popup.action;
				var rec = _grids['regulation'].getSelectedRecord();
				
				data["runMode"] = runMode;
				
				data["regulation"] = this.getField('filReqRegulation').getValue();
				data["reportingYear"] = this.getField('filReqreportingYear').getValue();
				data["TPSEffDate"] =  this.getField('filReqTPSEffDate').getSMVDateString();
				data["domicileCntry"] =  this.getField('filReqRFIDomicile').getValue();
				
				if (popup.action == _controller.ADD){
					data["extractStat"] = _controller.extractStat['ExtractPending'];
					data["regExtrMstrUUID"] = _controller.getNewRegulationUUID();
				}else{
					data["extractStat"] =  rec.data['extractStat'];
					data["regExtrMstrUUID"] = rec.data['regExtrMstrUUID'];
				}
				
				return data;
			}
		})
		,detailPopup: new DesktopWeb.AdvancedControls.PopupWindow(
		{
			width: 480
			,closeAction: 'hide'
			,modal: true
			,autoHeight: true
			,defaults: {border: false}
			,bodyStyle: 'padding:4px'
			,items: [ 
				{
					layout: 'form'
					,items: [
					{
						layout: 'column'
						,defaults: {border: false, columnWidth: .5, layout: 'form', padding: '5px'}
						,items: [
						{
							labelWidth: 80
							,items :[
								new DesktopWeb.Controls.TextField(
								{
									itemId: 'dtlRegulationFld'
									,fieldLabel: _translationMap['Regulation']
									,width: 130
									,readOnly: true
								})
								,new DesktopWeb.Controls.TextField(
								{
									itemId: 'dtlRFIDomicileFld'
									,fieldLabel: _translationMap['RFIDomicile']
									,width: 130
									,readOnly: true
								})
								,new DesktopWeb.Controls.TextField(
								{
									itemId: 'dtlExtractStatFld'
									,fieldLabel: _translationMap['RequestStat']
									,width: 130
									,readOnly: true
								})
							]
						}
						,{
							labelWidth: 120
							,items :[
								new DesktopWeb.Controls.TextField(
								{
									itemId: 'dtlReportingYearFld'
									,fieldLabel: _translationMap['ReportingYear']
									,width: 80
									,readOnly: true
								})
								,new DesktopWeb.Controls.TextField(
								{
									itemId: 'dtlTPSEffDateFld'
									,fieldLabel: _translationMap['TPSEffDate']
									,width: 80
									,readOnly: true
								})
							]
						}]
					}
					,{
						xtype: 'fieldset'
						,title: _translationMap['Summary'] + " By " + _translationMap['Domicile']
						,style: 'padding-top:5px;' 
						,items: [
						{
							layout: 'column'
							,items: [
								new DesktopWeb.AdvancedControls.GridPanel({
									itemId: 'summary'
									,width: 480
									,autoScroll: true
									,height: 120
									,store: new Ext.data.XmlStore({
										record: 'summary'
										,fields: ['domicileCntry', 'noOfRFIs', 'noOfAccts', 'noOfErrs']
										,listeners: {
										}
									})
									,selModel: new Ext.grid.RowSelectionModel({
										singleSelect: true
									})
									,colModel: new Ext.grid.ColumnModel({
										defaults: {
											menuDisabled: true
											,sortable: false
										}
										,columns: [
											{header: _translationMap['RFIDomicile'], dataIndex: 'domicileCntry', width: 120}
											,{header: "# of " + _translationMap['RFIs'], dataIndex: 'noOfRFIs', width: 80}
											,{header: "# of " + _translationMap['Account'], dataIndex: 'noOfAccts', width: 80}
											,{header: "# with " + _translationMap['Error'], dataIndex: 'noOfErrs', width: 80}
											
										]
									})
								})
							]
						}]
					}
					,{
						layout: 'form'
						,style: 'padding: 4px; border:none'
						,labelWidth: 80
						,defaults: {border:false}
						,items: [
						{
							layout: 'column'
							,defaults: {border: false, labelWidth: 100, columnWidth: 0.35, layout: 'form'}
							,items: [
							{
								style: 'padding: 20px auto'
								,items :[
									new DesktopWeb.Controls.Label(
									{
										fieldLabel: _translationMap['Options']
										,width: 100
									})
								]
							}
							,{
								layout: 'column'
								,columnWidth: 0.4
								,labelWidth: 100
								,style: 'font-size: 1.05em; padding: 4px 0'
								,items :[
									new DesktopWeb.Controls.Checkbox(
									{
										itemId: 'validateRpt'
										,boxLabel: _translationMap['ListingFile']
										,width: 120
									})
									,new DesktopWeb.Controls.Checkbox(
									{
										itemId: 'errorRpt'
										,boxLabel: _translationMap['ErrorLog']
										,width: 120
									})
									,new DesktopWeb.Controls.Checkbox(
									{
										itemId: 'submissionRpt'
										,boxLabel: _translationMap['SubmissionFile']
										,width: 120
									})
								]
							}
							,{
								layout: 'column'
								,columnWidth: 0.25
								,labelWidth: 150
								,style: 'padding: 20px auto'
								,items :[
									new DesktopWeb.Controls.ActionButton(
									{
										itemId: 'genBtn'
										,text: _translationMap['Generate']
										,handler: function(){
											var isChecked = false;
											var data = "";
											var checkList = ["validateRpt","errorRpt","submissionRpt"];
											
											for(var i in checkList){
												if(_popups['detailPopup'].getField(checkList[i])){
													
													if(_popups['detailPopup'].getField(checkList[i]).getValue()){
														isChecked = true;
														data += checkList[i] + ",";
													}
												}
											}
											
											if(isChecked){
												_controller.genReport("options", data);
											}
											
										}
									})
								]
							}]
						}] 
					}
					,{
						xtype: 'fieldset'
						,title: _translationMap['Action'] + _translationMap['sTaken']
						,style: 'padding-top:5px;' 
						,items: [
						{
							layout: 'column'
							,items: [
								new DesktopWeb.AdvancedControls.GridPanel({
									itemId: 'regExtrActHist'
									,width: 480
									,autoScroll: true
									,height: 80
									,store: new Ext.data.XmlStore({
										record: 'regExtrActHist'
										,fields: ['actionType', 'processTimeStamp', 'userName']
										,listeners: {
											load: function(store, records)
											{
												Ext.each(records, function(record){
													record.data['processTimeStamp'] = DesktopWeb.Util.getDateDisplayValue(record.data['processTimeStamp']);
												});	
												store.fireEvent('datachanged', store);
											}
										}
									})
									,selModel: new Ext.grid.RowSelectionModel({
									})
									,colModel: new Ext.grid.ColumnModel({
										defaults: {
											menuDisabled: true
											,sortable: false
										}
										,columns: [
											{header: _translationMap['Action'], dataIndex: 'actionType', width: 100}
											,{header: _translationMap['ProcessDate'], dataIndex: 'processTimeStamp', width: 120}
											,{header: _translationMap['Username'], dataIndex: 'userName', width: 100}
											
										]
									})
								})
							]
						}]
					}]
				}]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						_popups['detailPopup'].hide();
					}
				})
			]
			,init: function(action)
			{
				var popup = _popups['detailPopup'];
				popup.action = action;
				popup.setTitle(_translationMap['Options']);
				
				var selected = _grids['regulation'].getSelectedRecord();
				popup.getField('dtlRegulationFld').setValue(_controller.getDesc('regulations',selected.data['regulation']));
				popup.getField('dtlRFIDomicileFld').setValue(_controller.getDesc('RFIDomiciles', selected.data['domicileCntry']));
				popup.getField('dtlReportingYearFld').setValue(selected.data['reportingYear']);
				popup.getField('dtlTPSEffDateFld').setValue(selected.data['TPSEffDate']);
				popup.getField('dtlExtractStatFld').setValue(_controller.getDesc('extractStat',selected.data['extractStat']));
			}
		})
	} 
 
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth

		,layoutHeight: _layoutHeight

		,fields: _fields

		,grids: _grids

		,popups: _popups

		,buttons: _buttons

		,layout: new Ext.Container(
		{
			height: _layoutHeight
			,width: _layoutWidth
			,style: 'padding-left:5px; padding-right:10px'
			,items: [
			{
				itemId: 'mainLayout1'
				 ,layout: 'column'
				,items: [
				{
					layout: 'form'
					,columnWidth: 0.45
					,labelWidth: 100
					,items :[
						_fields['regulationFld']
						,_fields['reportingYearFld']
					]
				}
				,{
					layout: 'form'
					,columnWidth: 0.45
					,labelWidth: 100
					,items :[
						_fields['rfiDomicileFld']
						,_fields['extractStatFld']
					]
				}
				,{
					layout: 'form'
					,columnWidth: 0.1
					,items :[
						_buttons['searchBtn']
					]
				}]          
			}
			,_grids['regulation']
			,{
				itemId: 'menuLayout1'
				,layout: 'column'
				,style: 'padding-top:5px;' 
				,items: [
				{
					layout: 'column'
					,columnWidth: 0.64
					,items :[
						_buttons['extractBtn']
						,_buttons['approveBtn']
					]
				}
				,
				{
					layout: 'column'
					,columnWidth: 0.36
					,items :[
						_buttons['addBtn']
						,_buttons['modBtn']
						,_buttons['delBtn']
						,_buttons['detlBtn']
					]
				}]      
			}
			,{
				xtype: 'fieldset'
				,title: _translationMap['ReportableAccts']
				,style: 'padding-top:10px;' 
				,items: [
				{
					layout: 'column'
					,items: [
						_grids['reportAccts']
					]
				}
				,{
					itemId: 'menuLayout2'
					 ,layout: 'column'
					 ,style: 'padding-top:5px;'
					,items: [
					{
						layout: 'form'
						,columnWidth: 0.82
						,items :[
						]
					}
					,
					{
						layout: 'column'
						,columnWidth: 0.18
						,items :[
							_buttons['reviewBtn']
							,_buttons['moreBtn']
						]
					}]      
				}]
			}
			
			,{
				xtype: 'fieldset'
				,title: _translationMap['RFIs']
				,style: 'padding-top:10px;'
				,items: [
				{
					layout: 'column'
					,items: [_grids['RFIs']]
				}
				,{
					itemId: 'menuLayout3'
					 ,layout: 'column'
					 ,style: 'padding-top:5px;'
					,items: [
					{
						layout: 'form'
						,columnWidth: 0.91
						,items :[
						]
					}
					,{
						layout: 'column'
						,columnWidth: 0.09
						,items :[
							_buttons['rfiDetlBtn']
						]
					}]      
				}]
			}]
			
		})
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					DesktopWeb.Util.cancelScreen();
				}
			})
		]
	}
}