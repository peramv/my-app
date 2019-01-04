/*********************************************************************************************
 * @file	FATCAFilingDetl.Resources.js
 * @author	Pannarasi Wongpakdee
 * @desc	Resources JS file for FATCA Filing Detail screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > FATCA Filing Detail
 *				
 *  History : 
 *
 *  24 Dec 2014 P. Wongpakdee P0205605 T80214
 *					- Created.
 *
 *	05 Feb 2015 P. Wongpakdee P0205605 T80264
 *					- Adjustment section
 *
 *	16 Feb 2015 P. Wongpakdee P0205605 T80349
 *					- Additional requirement (Create dummy record(s)
 *					  at Reporting Unit level for Adjustment)
 *
 *	26 Mar 2015 P. Wongpakdee P0205605 T80536
 *					- Assign data['assocDocRefID'] with value Correct Doc Ref ID
 *					  instead of Doc Ref ID at Slip level for validation.
 *
 *	18 Nov 2015 Narin Suanlamyai P0241558 DFT0051314 T80917
 *					- Adding slip should allow user to search account regardless status of account.
 *					  The incAllStat parameter of accountSearch service is changed to 'all'.
 *
 *	08 Jan 2016 A. Mongkonrat P0241558 T81995 DFT0058373
 *					- Add Country Of Domicile and remove As of Date.
 *
 *	18 Jan 2016 A. Mongkonrat P0241558 T82072 DFT0058919 
 *					- Remove 'As of Date' from modify cases. 
 *
 *  04 Feb 2016 Aurkarn M. P0241558 T82184 DFT0059297 FATCA Reporting Enhancement
 *					- Expand 'Add' popup width.
 *                  - Fix issue where user is unable to add filing request if there is a record of previous tax year.
 *
 *	23 Mar 2016 A. Mongkonrat P0241558 T82490 DFT0060792 
 *					- Fix issue where unable to 'Delete' a record in the pending status on 'FATCA Filing Detail'. 
 *
 *	10 Jan 2017 Matira T. P0259672 T84599 CRS Enhancement Phase2
 *					- Add new field RFI Domicile to support CRS. 
 *					- Add new column Entity Type to Slip level.
 *
 *	01 Feb 2017 Matira T. P0259672 T84754 DFT0071968 CRS Enhancement Phase2
 *					- Disabled TPS Eff.Date field while modifying
 *					- Disabled Regulation field while modifying or adding
 *
 *	16 Feb 2017 Matira T. P0259672 T84920 DFT0072303 CRS Enhancement Phase2
 *					- Changed logic to set default tax year and TPSDate field.
 *
 *	12 Jun 2018 Ravindra Gadde P0277308 DFT0082529
 *					- Fix code for origFATCARptFileUUID and origFATCARptFileDetlUUID required for smartview.
 */
 
 DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 760;
	var _layoutWidth = 830;	
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,listeners: {
				click: function(){_controller.clickHandle_searchBtn();}
			}
		})
		,searchSilpBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,listeners: {
				click: function(){_controller.clickHandle_searchSlipBtn();}
			}
		})
	}
	
	// **** fields ****
	var _fields = {		
		regulationFld: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['Regulation']
				,width: 120
				,editable: true
				,allowBlank: false
				,listeners:{
					select: function(){
						_fields['rfiDomicileFld'].hide();
						if(this.getValue() == _controller.CRS)
						{
							_fields['rfiDomicileFld'].show();
						}
						_controller.selectHandle_regulationFld(this.getValue());
					}
				}
			}
		)
		,taxYearFld: new DesktopWeb.Controls.NumberField(
			{
				fieldLabel: _translationMap['TaxYear']
				,width: 120
				,editable: true
				,allowBlank: false
				,decimalPrecision: 0
				,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '4'}
			}
		)

		,msgIDFld: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['MsgIDSrch']
				,width: 120
				,editable: true
				,allowBlank: true
			}
		)
		,docRefIDFld: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['DocumentRefID']
				,width: 120
				,editable: true
				,allowBlank: true
			}
		)
		,slipIDFld: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['SlipID']
				,width: 120
				,editable: true
				,allowBlank: true
			}
		)		
		,genOutput: new DesktopWeb.Controls.Checkbox(
			{
				boxLabel: _translationMap['GenOutput']
				,listeners: {
					check: function(cb, checked)
					{
						_controller.checkedGenOutput(checked);
					}
				}				
			}
		)
        ,rfiDomicileFld: new DesktopWeb.Controls.SMVComboBox(
        {
            fieldLabel: _translationMap['RFIDomicile']
            ,width: 120
            ,editable: true
            ,allowBlank: false	
			,hidden: true
        })
	}
	
	// **** grids ****
	var _grids = {
		submissionGrid: new DesktopWeb.AdvancedControls.GridPanel(							
			{							
				width: _layoutWidth - 12
				,autoScroll: true
				,height: 150
				,autoExpandColumn: 'FATCACode'
				,store: new Ext.data.XmlStore(
					{
						record: 'Submission'				
						,fields: ['FATCARptMstrUUID', 'FATCACode', 'FILevel', 'FICode', 'asOfDate', 'TPSDeff', 'submissionType',
								  'submissionSeq', 'runMode', 'rptFile', 'rptUnit', 'runDate', 'stat', 'allowMod', 'allowDel',
								  'procDate', 'userName', 'modDate', 'modUser', 'version', 'errMsg', 'genOutput', 'action',
								  'hasMoreLinkedRptUnit', 'nextStartRecordNumLinkedRptUnit', 'taxYear', 'origFATCARptMstrUUID', 'countryOfDomicile']
						,listeners: {
							load: function(store, records)
							{
								store.filterBy(function(record){return record.data.action != _controller.DEL});
								
								Ext.each(records, function(record){
									record.data['asOfDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['asOfDate']);
									record.data['TPSDeff'] = DesktopWeb.Util.getDateDisplayValue(record.data['TPSDeff']);
									record.data['runDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['runDate']);
								});	
								store.fireEvent('datachanged', store); //to set data in grid again
							}							
							,update: function(store, records)
							{
								store.filterBy(function(record){return record.data.action != _controller.DEL});
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
									_controller.selectSubmission(record, index);
								}
							}
                            ,beforerowselect: function(selModel, index, keepExisting) {
                                return _controller.validateSlips();
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
							{dataIndex: 'errMsg', id: 'errMsg', width: 25,
								renderer: function(val){return (val ? _controller.buildErrorFlag(val) : '');}}						
							,{header: _translationMap['Regulation'], dataIndex: 'FATCACode', id: 'FATCACode',
								renderer: function(value){ return (_controller.getListValueDesc('regulations', value))}}
                            ,{header: _translationMap['RFIDomicile'], dataIndex: 'countryOfDomicile', id: 'countryOfDomicile',
								renderer: function(value){ return (_controller.getListValueDesc('RFIDomicile', value))}}
							,{header: _translationMap['AsOfDate'], dataIndex: 'asOfDate', id: 'asOfDate', width: 80}
							,{header: _translationMap['TPSEffDate'], dataIndex: 'TPSDeff', id: 'TPSDeff', width: 80}
							,{header: _translationMap['SubmissionType'], dataIndex: 'submissionType', id: 'submissionType', width: 105,
								renderer: function(value){ return (_controller.getListValueDesc('submissionType', value))}}
							,{header: _translationMap['RunMode'], dataIndex: 'runMode', id: 'runMode', width: 75,
								renderer: function(value){ return (_controller.getListValueDesc('runMode', value))}}
							,{header: _translationMap['ReportFile'], dataIndex: 'rptFile', id: 'rptFile', width: 130,
								renderer: function(value){ return (_controller.getListValueDesc('reportFile', value))}}
							,{header: _translationMap['RunDate'], dataIndex: 'runDate', id: 'runDate', width: 80}
							,{header: _translationMap['MsgStatus'], dataIndex: 'stat', id: 'stat', width: 110,
								renderer: function(value){ return (_controller.getListValueDesc('statusRpt', value))}}
						]						
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'
						,text: _translationMap['Add']
						,disabled: true
						,handler: function(){_controller.openActionPopup("filingReqPopup", _controller.ADD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,disabled: true
						,handler: function(){_controller.openActionPopup("filingReqPopup", _controller.MOD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,disabled: true
						,handler: function(){_controller.openActionPopup("filingReqPopup", _controller.DEL);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'historyBtn'
						,text: _translationMap['Historical']
						,disabled: true
						,handler: function(){_controller.openHistoryPopup('Submission');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'adminBtn'
						,text: _translationMap['Admin']
						,disabled: true
						,handler: function(){_controller.openAdminPopup('Submission');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'moreBtn'
						,text: _translationMap['More']
						,disabled: true
						,handler: function(){_controller.clickHandle_moreBtn();}
					})
				]				
			}
		)
		,reportingUnitGrid: new DesktopWeb.AdvancedControls.GridPanel(							
			{							
				width: _layoutWidth - 12
				,autoScroll: true
				,height: 150
				,autoExpandColumn: 'rptUnitLevelDesc'
				,store: new Ext.data.XmlStore(
					{
						record: 'RptUnit'
						,fields: ['FATCARptFileUUID', 'FATCARptFileDetlUUID', 'rptUnitFILevel', 'rptUnitFICode', 'rptUnitName',
								  'msgID', 'FATCARptFileVer', 'numRFFI', 'reportingFFI', 'docRefID', 'assocDocRefID', 'numSlip',
								  'numSlipErr', 'stat', 'errMsg', 'allowMod', 'procDate', 'userName', 'modDate', 'modUser',
								  'FATCARptFileDetlVer', 'govTaxAgency', 'action', 'version', 'rptUnitLevelDesc', 'reportingFFILevel',
								  'reportingFFICode', 'hasMoreLinkedSlip', 'nextStartRecordNumLinkedSlip', 'origFATCARptFileUUID',
								  'origFATCARptFileDetlUUID']
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.selectReportingUnit(record, index);
								}
							}
                            ,beforerowselect: function(selModel, index, keepExisting) {
                                return _controller.validateSlips();
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
							{dataIndex: 'errMsg', id: 'errMsg', width: 25,
								renderer: function(val){return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');}}						
							,{header: _translationMap['RptUnitLevel'], dataIndex: 'rptUnitLevelDesc', id: 'rptUnitLevelDesc'}
							,{header: _translationMap['RptUnitName'], dataIndex: 'rptUnitName', id: 'rptUnitName', width: 100}
							,{header: _translationMap['MsgID'], dataIndex: 'msgID', id: 'msgID', width: 75
								,renderer: function(val, metaData, record){
									return _controller.getDisplayNumberWithError('rptUnit', val, record);
								}
							}							
							,{header: _translationMap['GovTaxAgency'], dataIndex: 'govTaxAgency', id: 'govTaxAgency', width: 45}
							,{header: _translationMap['NumOfRFFI'], dataIndex: 'numRFFI', id: 'numRFFI', width: 45}
							,{header: _translationMap['ReportingFFI'], dataIndex: 'reportingFFI', id: 'reportingFFI', width: 100}
							,{header: _translationMap['DocRefID'], dataIndex: 'docRefID', id: 'docRefID', width: 75
								,renderer: function(val, metaData, record){
									return _controller.getDisplayNumberWithError('rffi', val, record);
								}
							}
							,{header: _translationMap['CorrectedDocRefID'], dataIndex: 'assocDocRefID', id: 'assocDocRefID', width: 75}
							,{header: _translationMap['NumOfSlip'], dataIndex: 'numSlip', id: 'numSlip', width: 40}
							,{header: _translationMap['NumOfSlipWarnErr'], dataIndex: 'numSlipErr', id: 'numSlipErr', width: 65}
							,{header: _translationMap['FileStatus'], dataIndex: 'stat', id: 'stat', width: 60}
						]							
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
						itemId: 'adjustmentBtn'
						,text: _translationMap['AdjustmentBtn']
						,disabled: true
						,handler: function()
						{
							_controller.openActionPopup("adjustPopup", _controller.ADJ);
							
							// Call Inq service to get list of RFFI/Unit when adjustment
							_controller.loadReportingRFFIList();
						}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'historyBtn'
						,text: _translationMap['Historical']
						,disabled: true
						,handler: function(){_controller.openHistoryPopup('ReportingUnit');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'adminBtn'
						,text: _translationMap['Admin']
						,disabled: true
						,handler: function(){_controller.openAdminPopup('ReportingUnit');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'moreBtn'
						,text: _translationMap['More']
						,disabled: true
						,handler: function(){_controller.clickHandle_moreBtnRptUnit();}
					})
				]				
			}
		)
		
		,slipGrid: new DesktopWeb.AdvancedControls.GridPanel(							
			{							
				width: _layoutWidth - 12
				,autoScroll: true
				,height: 150
				,autoExpandColumn: 'entityName'
				,store: new Ext.data.XmlStore(
					{
						record: 'Slip'
						,fields: ['FATCARptFileDetlUUID', 'FATCARptSlipUUID', 'reportingFFI', 'account', 'entityID',
								  'entityName', 'slipID', 'assocSlipID', 'submissionType', 'errMsg', 'allowAdd', 'allowMod',
								  'allowDel', 'userName', 'procDate', 'modUser', 'modDate', 'version', 'action',
								  'entityType']
						,listeners: {
							load: function(store, records)
							{
								store.filterBy(function(record){return record.data.action != _controller.DEL});
							}
							,update: function(store, records)
							{
								store.filterBy(function(record){return record.data.action != _controller.DEL});
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
									_controller.selectSlip(record, index);
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
							{dataIndex: 'errMsg', id: 'errMsg', width: 25,
								renderer: function(val){return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');}}						
							,{header: _translationMap['ReportingFFI'], dataIndex: 'reportingFFI', id: 'reportingFFI', width: 100}
							,{header: _translationMap['AccountNum'], dataIndex: 'account', id: 'account', width: 110}
							,{header: _translationMap['EntityName'], dataIndex: 'entityName', id: 'entityName'}
							,{header: _translationMap['EntityType'], dataIndex: 'entityType', id: 'entityType', width: 80}
							,{header: _translationMap['SlipID'], dataIndex: 'slipID', id: 'slipID', width: 120
								,renderer: function(val, metaData, record){
									return _controller.getDisplayNumberWithError('slip', val, record);
								}
							}							
							,{header: _translationMap['CorrectedSlipID'], dataIndex: 'assocSlipID', id: 'assocSlipID', width: 120}
							,{header: _translationMap['SlipType'], dataIndex: 'submissionType', id: 'submissionType', width: 105,
								renderer: function(value){ return (_controller.getListValueDesc('submissionType', value))}}
						]
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'
						,text: _translationMap['Add']
						,disabled: true 
						,handler: function(){_controller.openActionPopup("acctReqPopup", _controller.ADD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,disabled: true
						,handler: function(){_controller.openActionPopup("acctReqPopup", _controller.MOD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,disabled: true
						,handler: function(){_controller.openActionPopup("acctReqPopup", _controller.DEL);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'historyBtn'
						,text: _translationMap['Historical']
						,disabled: true
						,handler: function(){_controller.openHistoryPopup('slipFullPopup');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'detailBtn'
						,text: _translationMap['DetailBtn']
						,disabled: true
						,handler: function(){
							_controller.openActionPopup("slipFullPopup", _controller.INQ);
							_controller.clickHandle_searchSlipBtn();
						}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'adminBtn'
						,text: _translationMap['Admin']
						,disabled: true
						,handler: function(){_controller.openAdminPopup('Slip');}						
					})
				]				
			}
		)
		,accountGrid: new DesktopWeb.AdvancedControls.GridPanel(							
			{							
				width: _layoutWidth - 165
				,autoScroll: true
				,height: 400
				,autoExpandColumn: 'entityName'
				,store: new Ext.data.XmlStore(
					{
						record: 'Slip'
						,fields: ['FATCARptFileDetlUUID', 'FATCARptSlipUUID', 'reportingFFI', 'account', 'entityID',
								  'entityName', 'slipID', 'assocSlipID', 'submissionType', 'errMsg', 'allowAdd', 'allowMod',
								  'allowDel', 'userName', 'procDate', 'modUser', 'modDate', 'version', 'action',
								  'entityType']
					}					
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.selectSlipFullView(record, index);
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
							{header: _translationMap['ReportingFFI'], dataIndex: 'reportingFFI', id: 'reportingFFI', width: 100}
							,{header: _translationMap['AccountNum'], dataIndex: 'account', id: 'account', width: 100}
							,{header: _translationMap['EntityName2'], dataIndex: 'entityName', id: 'entityName'}
							,{header: _translationMap['EntityType'], dataIndex: 'entityType', id: 'entityType', width: 80}
							,{header: _translationMap['SlipID'], dataIndex: 'slipID', id: 'slipID', width: 100
								,renderer: function(val, metaData, record){
									return _controller.getDisplayNumberWithError('slip', val, record);
								}
							}								
							,{header: _translationMap['CorrectedSlipID'], dataIndex: 'assocSlipID', id: 'assocSlipID', width: 100}
							,{header: _translationMap['SlipType2'], dataIndex: 'submissionType', id: 'submissionType', width: 105,
								renderer: function(value){ return (_controller.getListValueDesc('submissionType', value))}}
						]
					}
				)
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
						itemId: 'moreBtn'
						,text: _translationMap['More']
						,disabled: true
						,handler: function(){_controller.clickHandle_moreBtnSlipFullView();}
					})				
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'adminBtn'
						,text: _translationMap['Admin']
						,disabled: true
						,handler: function(){_controller.openAdminPopup('Slip');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'closeBtn'
						,text: _translationMap['Close']
						,disabled: true
						,handler: function(){_popups['slipFullPopup'].hide();}
					})
				]				
			}
		)		
	}
	
	// **** popups ****
	var _popups = {
		filingReqPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 310
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
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
							,disabled: true
                            ,listeners:{					
                                select: function(){
                                   _popups['filingReqPopup'].displayFieldByReg();
                                }
                            }
						})
                        ,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqRFIDomicile'
							,fieldLabel: _translationMap['RFIDomicile']
							,width: 150
							,editable: true
							,allowBlank: false		
                            ,hidden: true                         
						}) 
						,new DesktopWeb.Controls.NumberField({
							itemId: 'filReqTaxYear'
							,fieldLabel: _translationMap['TaxYear']
							,width: 150
							,allowBlank: false
							,decimalPrecision: 0
							,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '4'}
                            ,listeners:{
								change: function(fld, newValue, oldValue)
								{
									if (fld.isValid() && _popups['filingReqPopup'].action == _controller.ADD)
									{
										_popups['filingReqPopup'].getField('filReqAsofDate').setValue(DesktopWeb.Util.getDateDisplayValue('12/31/' + newValue));
                                        
                                        // reset reporting unit drop down if As of Date has been changed
										_controller.resetReportingUnitDropDown(newValue, oldValue);
										
										// re-load reporting unit drop down based on As of Date
										_controller.selectReportFile(_popups['filingReqPopup'].getField('filReqReportFile').getValue());
									}
								}
							}
						}) 	
						,new DesktopWeb.Controls.DateField({
							itemId: 'filReqAsofDate'
							,fieldLabel: _translationMap['AsOfDate']
							,allowBlank: false
                            ,hidden: true
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
							,listeners:{
								change: function(fld, newValue, oldValue)
								{
									if (fld.isValid())
									{
										// reset reporting unit drop down if As of Date has been changed
										_controller.resetReportingUnitDropDown(newValue, oldValue);
										
										// re-load reporting unit drop down based on As of Date
										_controller.selectReportFile(_popups['filingReqPopup'].getField('filReqReportFile').getValue());
									}
								}
							}
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'filReqTPSEffDate'
							,fieldLabel: _translationMap['TPSEffDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqSubmission'
							,fieldLabel: _translationMap['SubmissionType']
							,width: 150
							,editable: true
							,allowBlank: false
						}) 		
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqRunMode'
							,fieldLabel: _translationMap['RunMode']
							,width: 150
							,editable: true
							,allowBlank: false
							,listeners:{
								select: function(fld, record, index){
									_controller.validateSubmissionPopupByRunMode(fld.getValue());
								}
							}
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqReportFile'
							,fieldLabel: _translationMap['ReportFile']
							,width: 150
							,editable: true
							,allowBlank: false
							,listeners:{
								select: function(fld, record, index)
								{
                                    _popups['filingReqPopup'].getField('filReqCountryOfDomicile').hideField();
                                    _popups['filingReqPopup'].getField('filReqReportFFI').hideField();
                                    _popups['filingReqPopup'].syncSize();
                                    if (fld.getValue() == _controller.REPORTFILE_CntyOfDomicile) {
                                        _popups['filingReqPopup'].getField('filReqCountryOfDomicile').showField();
                                    
                                        _popups['filingReqPopup'].getField('filReqCountryOfDomicile').setValue('');
                                        _popups['filingReqPopup'].getField('filReqReportFFI').setValue('');
                                    }
                                    else {
                                        _popups['filingReqPopup'].getField('filReqReportFFI').showField();
                                        
                                        // reset reporting unit drop down if Reporting File has been changed
                                        var selectedSubmission = _grids['submissionGrid'].getSelectedRecord();
                                        if (selectedSubmission){
                                            _controller.resetReportingUnitDropDown(fld.getValue(), selectedSubmission.data['rptFile']);
                                        }else{
                                            _controller.resetReportingUnitDropDown(fld.getValue(), _controller.BLNK);
                                        }
                                        
                                        // re-load reporting unit drop down based on selected Reporting File
                                        _controller.selectReportFile(fld.getValue());
                                        
                                        _popups['filingReqPopup'].getField('filReqCountryOfDomicile').setValue('');
                                    }
								}								
							}
						})
						,new DesktopWeb.Controls.ComboBox({
							itemId: 'filReqReportFFI'
							,fieldLabel: _translationMap['RptUnit']
							,width: 150
							,editable: true
							,allowBlank: true
							,valueField: 'FIDesc'
							,displayField: 'FIDesc'
							,FILevel: 'FILevel'
							,FICode: 'FICode'
							,store: new Ext.data.XmlStore({
								record: 'Element'
								,fields: ['FICode', 'FILevel', 'FIDesc']
							})
							,getFILevel: function(){
								var rec = this.getSelectedRecord();
								var result = "";
								if (rec)
									result = rec.data[this.FILevel];
								return result;
							}
							,getFICode : function(){
								var rec = this.getSelectedRecord();
								var result = "";
								if (rec) 
									result = rec.data[this.FICode];
								return result;
							}					
						})			
                        ,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'filReqCountryOfDomicile'
							,fieldLabel: _translationMap['CountryOfDomicile']
							,width: 150
							,editable: true
							,allowBlank: true	
                            ,hidden: true                         
						})	                    
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['filingReqPopup'].isValid()){
							_controller.validateSubmission(_popups['filingReqPopup'].getData(), _popups['filingReqPopup'].action);
						}
					}
				})				
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['filingReqPopup'].hide();}
				})				
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['filingReqPopup'];
				popup.action = action;
				switch(action)
				{
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['FilingReq'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['FilingReq'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['FilingReq'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action)
			{
				var selectedSubmission = _grids['submissionGrid'].getSelectedRecord();
				var popup = _popups['filingReqPopup'];
				popup.clearAllFields();
				popup.enableAllFields();

				switch(action)
				{					
					case _controller.ADD:
					{
						popup.uuid = _controller.getNewSubmissionUUID();
						popup.getField('filReqRegulation').setValue(_controller.getCurrentSearch('regulationFld'));
						popup.getField('filReqTaxYear').setValue(_controller.getDefault(popup.getField('filReqRegulation').getValue()+'TaxYearFld'));
						popup.getField('filReqAsofDate').setValue(_controller.getDefault('asOfDate'));
                        popup.getField('filReqCountryOfDomicile').setValue('');
						popup.getField('filReqCountryOfDomicile').hideField();
                        popup.getField('filReqRFIDomicile').setValue(_fields['rfiDomicileFld'].getValue());
                        popup.getField('filReqReportFFI').showField();
						
						// default As Of Date with the same year as Tax Year (case tax year that no data found)
						var defaultAsOfDate = popup.getField('filReqAsofDate').getValue();						
						var year = popup.getField('filReqTaxYear').getValue();
						var month = defaultAsOfDate.getMonth();
						var date = defaultAsOfDate.getDate();

						var asOfDateByTaxYear = new Date();
						asOfDateByTaxYear.setYear(year);
						asOfDateByTaxYear.setMonth(month);
						asOfDateByTaxYear.setDate(date);

						popup.getField('filReqAsofDate').setValue(asOfDateByTaxYear);
						popup.getField('filReqTPSEffDate').setValue(_controller.getDefault(popup.getField('filReqRegulation').getValue()+'TPSDeff'));	

						// Ensure to add ORG-Original back to Submission List (It's removed after modify Submission level of adjustment)
						var filterSubmissionType = _controller.BLNK;
						if (selectedSubmission){
							filterSubmissionType = selectedSubmission.data['submissionType'];
						}
						_controller.toFilterSubmissionTypeOfAdjustment(action, filterSubmissionType);
						popup.getField('filReqSubmission').setValue(_controller.ORG);
						
						popup.getField('filReqRunMode').setValue(_controller.RUNMODE_Test);
						
						// Submission Type = Original & Run Mode = Test
						popup.getField('filReqSubmission').disableField();	
						popup.getField('filReqRunMode').disableField();
						
						// Reset reporting unit drop down for everytime open popup with ADD mode
						popup.getField('filReqReportFFI').reset();
						popup.getField('filReqReportFFI').getStore().removeAll();

                        this.displayFieldByReg();
						break;
					}
					
					case _controller.MOD:
					{
						popup.uuid = selectedSubmission.data['FATCARptMstrUUID'];					
				
						popup.getField('filReqRegulation').setValue(selectedSubmission.data['FATCACode']);
						popup.getField('filReqTaxYear').setValue(selectedSubmission.data['taxYear']);
						popup.getField('filReqAsofDate').setValue(selectedSubmission.data['asOfDate']);
						popup.getField('filReqTPSEffDate').setValue(selectedSubmission.data['TPSDeff']);
						
						// Ensure to add ORG-Original back to Submission List (It's removed after modify Submission level of adjustment)
						_controller.toFilterSubmissionTypeOfAdjustment(action, selectedSubmission.data['submissionType']);							
						popup.getField('filReqSubmission').setValue(selectedSubmission.data['submissionType']);	
						
						popup.getField('filReqRunMode').setValue(selectedSubmission.data['runMode']);
						popup.getField('filReqReportFile').setValue(selectedSubmission.data['rptFile']);
                        popup.getField('filReqCountryOfDomicile').setValue(selectedSubmission.data['countryOfDomicile']);
                        popup.getField('filReqRFIDomicile').setValue(selectedSubmission.data['countryOfDomicile']);

						// #1 Validation on Submission level
						if (selectedSubmission.data['action'] == _controller.ADD) // New record adding
						{
							// disable Submissiont Type (Original) & Run Mode (Test)
							popup.getField('filReqSubmission').disableField();	
							popup.getField('filReqRunMode').disableField();
						}
						else if (selectedSubmission.data['submissionType'] != _controller.ORG) // Adjustment record
						{
							// disable all fields except Submission Type
							popup.disableAllFields();
							popup.getField('filReqSubmission').enableField();	
							
							// Remove ORG-Original from Submission List when modify Submission level of adjustment
							_controller.toFilterSubmissionTypeOfAdjustment(action, selectedSubmission.data['submissionType']);
							
							// Popup of Adjustment case needs to behave same as Orignal Type
							_controller.validateSubmissionPopupByRunMode(popup.getField('filReqRunMode').getValue());
						}
						else{ // Existing record (data)
							_controller.validateSubmissionPopupByRunMode(popup.getField('filReqRunMode').getValue());
						}
						
						// #2 To display reporting unit desc based on rptFile: 01-ALL, 02-Single FFI, 03-Single Report Unit
                        var listName = _controller.BLNK;
                        popup.getField('filReqReportFFI').showField();
                        popup.getField('filReqCountryOfDomicile').hideField();
						
                        if (popup.getField('filReqReportFile').getValue() == _controller.REPORTFILE_CntyOfDomicile) {
                            popup.getField('filReqReportFFI').hideField();
                            popup.getField('filReqCountryOfDomicile').showField();
                        }
                        else if (popup.getField('filReqReportFile').getValue() == _controller.REPORTFILE_SingleRFFI)
                        {
                            if (selectedSubmission.data['submissionType'] != _controller.ORG){
                                // New reporting unit list for adjustment case
                                listName = _controller.ALLREPORTING;
                            }else{
                                listName = _controller.REPORTINGFFI;
                            }
                        }
                        else if (popup.getField('filReqReportFile').getValue() == _controller.REPORTFILE_SingleUnit)
                        {
                            listName = _controller.REPORTINGUNIT;
                        }
                        else{
                            // #3 To disable reporting unit field if report file = 01-ALL (both new & existing record)
                            popup.getField('filReqReportFFI').disableField();
                        }
                        
                        // #4 To populate reporting unit drop down list based on report file (click on list)
                        if (listName != _controller.BLNK){
                            _controller.toPopulateDropdownListReporting(listName);
                            popup.getField('filReqReportFFI').showField();
                            /**
                               To disable Reporting Unit drop down list in case of adjustment or RunMode is Production
                               since Reporting Unit drop down will get enable after populating list
                             **/
                            if ( (selectedSubmission.data['submissionType'] != _controller.ORG) ||	
                                (selectedSubmission.data['runMode'] == _controller.RUNMODE_Production) )
                            {
                                popup.getField('filReqReportFFI').disableField();
                            }
                        }
						
						// #5 To populate reporting unit value
						var dispReportingUnitLabel = _controller.getDisplayReportingUnit(listName, selectedSubmission.data['FICode'], selectedSubmission.data['FILevel']);
						this.getField('filReqReportFFI').setValue(dispReportingUnitLabel);
                        
						if (selectedSubmission.data['FATCACode'] == _controller.CRS)
						{
							this.displayFieldByReg();
							popup.getField('filReqTaxYear').disableField();
							popup.getField('filReqRFIDomicile').disableField();
							popup.getField('filReqTPSEffDate').disableField();
						}else{
							popup.getField('filReqRFIDomicile').hideField();
							popup.getField('filReqReportFile').showField();
							popup.getField('filReqTPSEffDate').enableField();
						}
						break;
					}

					case _controller.DEL:
					{
						popup.uuid = selectedSubmission.data['FATCARptMstrUUID'];					
						
						popup.getField('filReqRegulation').setValue(selectedSubmission.data['FATCACode']);
						popup.getField('filReqTaxYear').setValue(selectedSubmission.data['taxYear']);
						popup.getField('filReqAsofDate').setValue(selectedSubmission.data['asOfDate']);
						popup.getField('filReqTPSEffDate').setValue(selectedSubmission.data['TPSDeff']);
                        popup.getField('filReqCountryOfDomicile').setValue(selectedSubmission.data['countryOfDomicile']);
						popup.getField('filReqRFIDomicile').setValue(selectedSubmission.data['countryOfDomicile']);
                        
						// Ensure to add ORG-Original back to Submission List (It's removed after modify Submission level of adjustment)
						_controller.toFilterSubmissionTypeOfAdjustment(action, selectedSubmission.data['submissionType']);						
						popup.getField('filReqSubmission').setValue(selectedSubmission.data['submissionType']);	
						
						popup.getField('filReqRunMode').setValue(selectedSubmission.data['runMode']);
						popup.getField('filReqReportFile').setValue(selectedSubmission.data['rptFile']);
						
						// rptFile: 01-ALL, 02-Single FFI, 03-Single Report Unit
						var listName = _controller.BLNK;
						popup.getField('filReqReportFFI').showField();
                        popup.getField('filReqCountryOfDomicile').hideField();
						
                        if (popup.getField('filReqReportFile').getValue() == _controller.REPORTFILE_CntyOfDomicile) {
                            popup.getField('filReqReportFFI').hideField();
                            popup.getField('filReqCountryOfDomicile').showField();
                        }
						
						if (selectedSubmission.data['rptFile'] == _controller.REPORTFILE_SingleRFFI){
							if (selectedSubmission.data['submissionType'] != _controller.ORG && selectedSubmission.data['stat'] == _controller.MSGSTAT_Pending){
								// New reporting unit list for adjustment case
								listName = _controller.ALLREPORTING;
							}else{
								listName = _controller.REPORTINGFFI;
							}
						}
						else if (selectedSubmission.data['rptFile'] == _controller.REPORTFILE_SingleUnit){
							listName = _controller.REPORTINGUNIT;
						}
						
						var dispReportingUnitLabel = _controller.getDisplayReportingUnit(listName, selectedSubmission.data['FICode'], selectedSubmission.data['FILevel']);
						this.getField('filReqReportFFI').setValue(dispReportingUnitLabel);						
						
						popup.disableAllFields();
						if (selectedSubmission.data['FATCACode'] == _controller.CRS)
						{
							this.displayFieldByReg();
						}else{
							popup.getField('filReqRFIDomicile').hideField();
							popup.getField('filReqReportFile').showField();
						}
						
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function()
			{
				var popup = _popups['filingReqPopup'];
				
				// Validate all input fields before business checking
				var valid = popup.getField('filReqRegulation').isValid();
				valid = popup.getField('filReqTaxYear').isValid() && valid;
				valid = popup.getField('filReqAsofDate').isValid() && valid;
				valid = popup.getField('filReqTPSEffDate').isValid() && valid;
				valid = popup.getField('filReqSubmission').isValid() && valid;				
				valid = popup.getField('filReqRunMode').isValid() && valid;	
				valid = popup.getField('filReqReportFile').isValid() && valid;	
				valid = popup.getField('filReqReportFFI').isValid() && valid;
				
				if (valid)
				{
					// #1 Tax Year & Year of AsOfDate need to be the same
					var taxYear = popup.getField('filReqTaxYear').getValue();
					var asOfDate = popup.getField('filReqAsofDate').getValue();
					var yearAsOfDate = asOfDate.getYear();
					if (taxYear != yearAsOfDate){
						popup.getField('filReqTaxYear').markInvalid(_translationMap['ERR_TAXYEAR_NOT_SAME_YEAROFASOFDATE']);
						valid = false;
					}
					
					// #2 Reporting Unit is required if Report File is Single FFI or Single Report Unit
					var rptFile = popup.getField('filReqReportFile').getValue();
					var FICode = popup.getField('filReqReportFFI').getFICode();
					var FILevel = popup.getField('filReqReportFFI').getFILevel();
					
					if ( (rptFile == _controller.REPORTFILE_SingleRFFI || rptFile == _controller.REPORTFILE_SingleUnit) && popup.action != _controller.DEL){
						if (FICode == _controller.BLNK && FILevel == _controller.BLNK){
							popup.getField('filReqReportFFI').markInvalid(_translationMap['ERR_REPORTUNIT_IS_REQUIRED']);
							valid = false;
						}
					}
					
					// #3 No Reporting Unit list (All or Single Reporting File or Single Reporting Unit) returns as per selected AsOfDate
					if (_controller.isErrorOfEffRptListByAsOfDate){
                        popup.getField('filReqTaxYear').markInvalid(_translationMap['ERR_REPORTUNIT_IS_STOPPED']);
						valid = false;
					}
                    
                    // #4 It should be invalid when user enters tax year greater than current tax year
                    //    Relevant date determined by system date,
                    //    e.g. – if 10 Jan 2016, prior year is 31.12.2014 and current year is 31.12.2015. 
                    //    Future date would be 31.12.2016
                    var currentBusDate = new Date(_controller.getDefault('runDate'));

                    if (taxYear >= currentBusDate.getYear() && popup.getField('filReqRunMode').getValue() != _controller.RUNMODE_Test) {
                        popup.getField('filReqTaxYear').markInvalid(
                                                            _translationMap['ERR_TAXYEAR_GREATER_THAN_SYSTEM_TAXYEAR']);
                        valid = false;
                    }
				}
				
				return valid;
			}
			,getData: function()
			{
				var popup = _popups['filingReqPopup'];
				var data = {};
				var selectedSubmission = _grids['submissionGrid'].getSelectedRecord();
				var runMode = popup.action;
				var version = 1;
				var submissionSeq = 1;
				
				// Assign value for new record adding
				if (popup.action != _controller.ADD) // MOD & DEL
				{
					if (selectedSubmission){
						// Need to send original action for new record adding & adjusting
						if (selectedSubmission.data['action'] == _controller.ADD){
							runMode = _controller.ADD;
						}
						else if (selectedSubmission.data['action'] == _controller.ADJ){
							runMode = _controller.ADJ;
						}
						
						version = selectedSubmission.data['version'];
						submissionSeq = selectedSubmission.data['submissionSeq'];
						
						data['runDate'] = selectedSubmission.data['runDate'];	
						
						if(selectedSubmission.data['FATCACode'] == _controller.CRS)
						{
							data['FILevel'] = selectedSubmission.data['FILevel'];
							data['FICode'] = selectedSubmission.data['FICode'];	
						}
						// If any changes with Submission (Run Mode = Test); Msg status will be Pending
						if ( selectedSubmission.data['runMode'] == _controller.RUNMODE_Test &&
							 ( (selectedSubmission.data['FATCACode'] != popup.getField('filReqRegulation').getValue()) ||
							   (selectedSubmission.data['taxYear'] != popup.getField('filReqTaxYear').getValue()) ||
							   (selectedSubmission.data['asOfDate'] != popup.getField('filReqAsofDate').getDisplayDateString()) ||
							   (selectedSubmission.data['TPSDeff'] != popup.getField('filReqTPSEffDate').getDisplayDateString()) ||
							   (selectedSubmission.data['submissionType'] != popup.getField('filReqSubmission').getValue()) ||
							   (selectedSubmission.data['runMode'] != popup.getField('filReqRunMode').getValue()) ||
							   (selectedSubmission.data['rptFile'] != popup.getField('filReqReportFile').getValue()) ||
							   (selectedSubmission.data['FILevel'] != popup.getField('filReqReportFFI').getFILevel()) ||
							   (selectedSubmission.data['FICode'] != popup.getField('filReqReportFFI').getFICode()) )
						   )
						{
							data['msgStat'] = _controller.MSGSTAT_Pending; // Pending
						}else{
							data['msgStat'] = selectedSubmission.data['stat'];					
						}						
					}				
				}
				else{ // ADD
					data['msgStat'] = _controller.MSGSTAT_Pending; // Pending				
				}
				
				data['actionSub'] = runMode;
				data['submissionSeq'] = submissionSeq;
				data['version'] = version;
			
				data['FATCARptMstrUUID'] = popup.uuid;	
				data['origFATCARptMstrUUID'] = _controller.BLNK;				
				
				data['FATCACode'] = popup.getField('filReqRegulation').getValue();
				data['taxYear'] = popup.getField('filReqTaxYear').getValue();
				data['asOfDate'] = popup.getField('filReqAsofDate').getDisplayDateString();
				data['TPSDeff'] = popup.getField('filReqTPSEffDate').getDisplayDateString();
				data['submissionType'] = popup.getField('filReqSubmission').getValue();
				data['runMode'] = popup.getField('filReqRunMode').getValue();
				data['rptFile'] = popup.getField('filReqReportFile').getValue();					
				
				data['FILevel'] = popup.getField('filReqReportFFI').getFILevel();
				data['FICode'] = popup.getField('filReqReportFFI').getFICode();	
				data['countryOfDomicile'] = popup.getField('filReqCountryOfDomicile').getValue();
				
				if(data['FATCACode'] == _controller.CRS)
				{
					data['countryOfDomicile'] = popup.getField('filReqRFIDomicile').getValue(); 
				}
				return data;
			}
			// hide/show field controller
            ,displayFieldByReg: function()
            {
                var popup = _popups['filingReqPopup'];
                var reg = popup.getField('filReqRegulation').getValue();
                
                if(reg == _controller.CRS)
                {	
					popup.getField('filReqCountryOfDomicile').hideField();
                    popup.getField('filReqRFIDomicile').showField();
                    popup.getField('filReqReportFile').hideField();   
					popup.getField('filReqReportFFI').hideField();					
                }else{
					if(popup.action != _controller.MOD){
						popup.getField('filReqReportFFI').showField();
					}
					popup.getField('filReqReportFile').showField();
					popup.getField('filReqRFIDomicile').hideField();
				}
                if (popup.rendered) popup.syncSize();
            }
		})	
		,adjustPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 330
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 150
					,items: [ 
						new DesktopWeb.Controls.ComboBox({
							itemId: 'adjReqRptUnitName' 
							,fieldLabel: _translationMap['RptUnitNameAdj']
							,width: 130
							,editable: true
							,allowBlank: false
							,valueField: 'FIDesc'
							,displayField: 'FIDesc'
							,store: new Ext.data.XmlStore({
								record: 'Element'
								,fields: ['FICode', 'FILevel', 'FIDesc', 'SingleRFFI']
							})
							,getAllValues : function(value){
								var rec = this.getSelectedRecord();
								var result = "";
								if (rec)
									result = rec.data[value];
								return result;							
							}
						})					
						,new DesktopWeb.Controls.NumberField({
							itemId: 'adjReqTaxYear'
							,fieldLabel: _translationMap['TaxYear']
							,width: 130
							,allowBlank: false
							,decimalPrecision: 0
							,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '4'}
						})
                        ,new DesktopWeb.Controls.YesNoComboBox({
                            itemId: 'adjReptFFIChange'
                            ,width: 130
                            ,fieldLabel: _translationMap['ReportingFFIChange']
                            ,allowBlank: false
                        })
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'adjReqSubmission'
							,fieldLabel: _translationMap['SubmissionType']
							,width: 130
							,editable: true
							,allowBlank: false
						}) 							
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'adjReqRunMode'
							,fieldLabel: _translationMap['RunMode']
							,width: 130
							,editable: true
							,allowBlank: false
						})
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['adjustPopup'].isValid()){
							_controller.validateRptUnit(_popups['adjustPopup'].getData(), _popups['adjustPopup'].action);
						}
					}
				})				
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['adjustPopup'].hide();}
				})				
			]			
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['adjustPopup'];
				popup.action = action;
				
				popup.setTitle(_translationMap['AdjustmentReq']);
				popup.populate(action);
			}
			,populate: function(action)
			{
				var selectedSubmission = _grids['submissionGrid'].getSelectedRecord();
				var selectedRptUnit = _grids['reportingUnitGrid'].getSelectedRecord();
				
				var popup = _popups['adjustPopup'];
				popup.clearAllFields();
				popup.enableAllFields();				
				
				switch(action)
				{
					case _controller.ADJ:
					{
						// New UUID is required for creating a new Reporting Unit record
						popup.uuid1 = _controller.getNewRptFileUUID();
						popup.uuid2 = _controller.getNewRptFileDetlUUID();
						popup.uuid3 = _controller.getNewSubmissionUUID();

						// Set to populate the Reporting Unit/RFFI from grid; find from Reporting FFI list first and then Reporting Unit list				
						var listName = _controller.REPORTINGFFI;
						var dispReportingUnitLabel = _controller.getDisplayReportingUnit(listName, selectedRptUnit.data['rptUnitFICode'], selectedRptUnit.data['rptUnitFILevel']);
						if (dispReportingUnitLabel == _controller.BLNK)
						{
							listName = _controller.REPORTINGUNIT;
							dispReportingUnitLabel = _controller.getDisplayReportingUnit(listName, selectedRptUnit.data['rptUnitFICode'], selectedRptUnit.data['rptUnitFILevel']);
						}					
						this.getField('adjReqRptUnitName').setValue(dispReportingUnitLabel);
						
						
						popup.getField('adjReqTaxYear').setValue(selectedSubmission.data['taxYear']);
						
						// Run Mode is always default as 02 - Test
						popup.getField('adjReqRunMode').setValue(_controller.RUNMODE_Test);						

						// Run Mode is read only
						popup.getField('adjReqRunMode').disableField();
						
						// Tax Year & AsofDAte is not allowed to modify for adjustment
						popup.getField('adjReqTaxYear').disableField();
						 
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function()
			{
				var popup = _popups['adjustPopup'];
				
				// Validate all input fields before business checking
				var valid = popup.getField('adjReqSubmission').isValid() && 
                            popup.getField('adjReptFFIChange').isValid();
				
				return valid;
			}
			,getData: function()
			{
				var popup = _popups['adjustPopup'];
				var data = {};
				var runMode = popup.action;

				var selectedSubmission = _grids['submissionGrid'].getSelectedRecord();
				var selectedRptUnit = _grids['reportingUnitGrid'].getSelectedRecord();
				
				/***** To be used in Submission Level *****/
				data['actionSub'] = runMode; // adj
				data['FATCARptMstrUUID'] = popup.uuid3; // new UUID
				data['origFATCARptMstrUUID'] = selectedSubmission.data['FATCARptMstrUUID'];	
				data['FATCACode'] = selectedSubmission.data['FATCACode'];
				
				data['FILevel'] = popup.getField('adjReqRptUnitName').getAllValues('FILevel');
				data['FICode'] = popup.getField('adjReqRptUnitName').getAllValues('FICode');
				
				data['taxYear'] = popup.getField('adjReqTaxYear').getValue();
				data['asOfDate'] = selectedSubmission.data['asOfDate'];
				data['TPSDeff'] = selectedSubmission.data['TPSDeff'];
				data['submissionType'] = popup.getField('adjReqSubmission').getValue();
				data['submissionSeq'] = selectedSubmission.data['submissionSeq'];
				data['runMode'] = popup.getField('adjReqRunMode').getValue();
                data['reptFFIChange'] = popup.getField('adjReptFFIChange').getValue();
				
				// Column rptFile at submission level need to show Single report FFI or Single report Unit when adjustment
				var isSingleRFFI = popup.getField('adjReqRptUnitName').getAllValues('SingleRFFI');
				if (isSingleRFFI == 'yes') 
				{
					data['rptFile'] = _controller.REPORTFILE_SingleRFFI; // Single reporting RFFI
				}else{
					data['rptFile'] = _controller.REPORTFILE_SingleUnit; // Single reporting Unit
				}
				
				data['version'] = 1; // add new
				// Run Date will assign after finishing job
				data['msgStat'] = _controller.MSGSTAT_Pending; // Pending - add new
				
				/***** To be used in Reporting Unit Level *****/
				data['actionRpt'] = runMode; // adj
				data['FATCARptFileUUID'] = popup.uuid1; // new UUID
				data['FATCARptFileDetlUUID'] = popup.uuid2; // new UUID
				data['origFATCARptFileUUID'] = selectedRptUnit.data['FATCARptFileUUID'];
				data['origFATCARptFileDetlUUID'] = selectedRptUnit.data['FATCARptFileDetlUUID'];				
				data['FATCARptFileVer'] = 1;
				data['FATCARptFileDetlVer'] = 1;
				
				/***** To be used to show new Reporting Unit Level *****/
				data['rptUnitLevelDesc'] = selectedRptUnit.data['rptUnitLevelDesc'];
				data['rptUnitName'] = selectedRptUnit.data['rptUnitName'];
				data['govTaxAgency'] = selectedRptUnit.data['govTaxAgency'];
				data['numRFFI'] = selectedRptUnit.data['numRFFI'];
				
				data['reportingFFI'] = popup.getField('adjReqRptUnitName').getAllValues('FIDesc');
				
				// Copy Doc Ref ID of adjustmented to Correct Doc Ref ID of a new record
				data['assocDocRefID'] = selectedRptUnit.data['docRefID'];
				//data['fileStat'] = _controller.MSGSTAT_Pending; // Pending - add new
				//data['fileStat'] = selectedRptUnit.data['stat']; // fix as Good/Bad per TP team
				data['fileStat'] =  _controller.BLNK; // leave as blank for now
				
				// Assign additional fields; not show when adjusting
				data['msgID'] = _controller.BLNK;
				data['docRefID'] = _controller.BLNK;
				data['numSlip'] = _controller.BLNK;
				data['numSlipErr'] = _controller.BLNK;					

				return data;				
			}
		})
		,acctReqPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 330
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
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
					,labelWidth: 100
					,items: [ 
						new DesktopWeb.Controls.SuggestField({
							itemId: 'actReqAccount'
							,fieldLabel: _translationMap['AccountNumReq']
							,width: 180
							,allowBlank: false
							,smartview: 'accountSearch'
							,fields: ['displayValue', 'acctNum']
							,valueField: 'acctNum'	
							,addtlSearchParams: [{name: 'incAllStat', valueFn: function(){return 'all'}}]
							,listeners:{
								populated: function(fld, record) {
									_controller.loadEntityName(record.data['acctNum']);			
								}
								,cleared: function(){
									_popups['acctReqPopup'].getField('actReqEntName').reset();
									_popups['acctReqPopup'].getField('actReqEntName').getStore().removeAll();
								}
							}							
						})						
						,new DesktopWeb.Controls.ComboBox({
							itemId: 'actReqEntName'
							,fieldLabel: _translationMap['EntityName']
							,width: 180
							,editable: true
							,allowBlank: false
							,valueField: 'entityName'
							,displayField: 'entityName'
							,entityID: 'entityID'
							,entityType: 'entityType'
							,store: new Ext.data.XmlStore({
								record: 'Element'
								,fields: ['entityID', 'entityType', 'entityName']
							})
							,getEntityID: function(){
								var rec = this.getSelectedRecord();
								var result = "";
								if (rec)
									result = rec.data[this.entityID];
								return result;
							}
							,getEntityType: function(){
								var rec = this.getSelectedRecord();
								var result = "";
								if (rec)
									result = rec.data[this.entityType];
								return result;
							}
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'actReqReportingFFI'
							,fieldLabel: _translationMap['ReportingFFI']
							,width: 180
							,allowBlank: false
						}) 	
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'actReqSubmission'
							,fieldLabel: _translationMap['SubmissionType']
							,width: 180
							,editable: true
							,allowBlank: false
						}) 						
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['acctReqPopup'].isValid()){
							_controller.validateSlip(_popups['acctReqPopup'].getData(), _popups['acctReqPopup'].action);
						}
					}
				})				
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['acctReqPopup'].hide();}
				})				
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['acctReqPopup'];
				popup.action = action;
				switch(action)
				{
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['AccountReq'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['AccountReq'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['AccountReq'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action)
			{
				var selectedSubmission = _grids['submissionGrid'].getSelectedRecord();
				var selectedRptUnit = _grids['reportingUnitGrid'].getSelectedRecord();
				var selectedSlip = _grids['slipGrid'].getSelectedRecord();
				
				var popup = _popups['acctReqPopup'];
				popup.clearAllFields();
				popup.enableAllFields();
				
				switch(action)
				{					
					case _controller.ADD:
					{
						popup.uuid = _controller.getNewSlipUUID();
						popup.getField('actReqReportingFFI').setValue(selectedRptUnit.data['reportingFFI']);
						popup.getField('actReqAccount').reset();
						popup.getField('actReqReportingFFI').disableField();
						
						break;
					}
					
					case _controller.MOD:
					{	  
						popup.uuid = selectedSlip.data['FATCARptSlipUUID'];					
						
						_controller.loadAccountSuggestField(selectedSlip.data['account']); // Suggested field
						popup.getField('actReqEntName').setValue(selectedSlip.data['entityName']);
						popup.getField('actReqReportingFFI').setValue(selectedSlip.data['reportingFFI']);
						
						popup.getField('actReqSubmission').setValue(selectedSlip.data['submissionType']);
						
						popup.getField('actReqReportingFFI').disableField();	
						
						// disable fields only for MOD & DEL existing record
						if (selectedSlip.data['action'] != _controller.ADD){
							popup.getField('actReqAccount').disableField();
							popup.getField('actReqEntName').disableField();
						}					

						break;
					}

					case _controller.DEL:
					{
						popup.uuid = selectedSlip.data['FATCARptSlipUUID'];	
						
						_controller.loadAccountSuggestField(selectedSlip.data['account']); // Suggested field
						popup.getField('actReqEntName').setValue(selectedSlip.data['entityName']);
						popup.getField('actReqReportingFFI').setValue(selectedSlip.data['reportingFFI']);
						popup.getField('actReqSubmission').setValue(selectedSlip.data['submissionType']);
						popup.disableAllFields();
						
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function()
			{
				var popup = _popups['acctReqPopup'];
				
				// Validate all input fields before business checking
				var valid = popup.getField('actReqAccount').isValid();
				valid = popup.getField('actReqEntName').isValid() && valid;
				valid = popup.getField('actReqSubmission').isValid() && valid;
				
                var selectedSubmissionType = _grids['submissionGrid'].getSelectedRecord().data['submissionType'];
                var slipSubmissionType = popup.getField('actReqSubmission').getValue();
                var slipUUID = popup.uuid;
                var foundCanclSlip = _grids['slipGrid'].getStore()
                                                       .queryBy(function(record) {
                                                          return record.data['submissionType'] == _controller.CAN &&
                                                                 record.data['FATCARptSlipUUID'] != slipUUID;
                                                       })
                                                       .getCount() > 0;
                                                       
                var foundAmendSlip = _grids['slipGrid'].getStore()
                                                       .queryBy(function(record) {
                                                          return record.data['submissionType'] == _controller.AMD &&
                                                                 record.data['FATCARptSlipUUID'] != slipUUID;
                                                       })
                                                       .getCount() > 0;
                
                if ((popup.action == _controller.ADD || popup.action == _controller.MOD) &&
                    selectedSubmissionType == _controller.AMD &&
                    ((foundCanclSlip && slipSubmissionType != _controller.CAN) ||
                     (foundAmendSlip && slipSubmissionType != _controller.AMD)) ) {
                      
                      DesktopWeb.Util.displayError(_translationMap['ERR_MIXING_SUBMISSION_TYPE']);
                      valid = false;
                }
                    
                
				return valid;
			}
			,getData: function()
			{
				var popup = _popups['acctReqPopup'];
				var data = {};	

				var selectedSubmission = _grids['submissionGrid'].getSelectedRecord();
				var selectedRptUnit = _grids['reportingUnitGrid'].getSelectedRecord();
				var selectedSlip = _grids['slipGrid'].getSelectedRecord();
				
				var runModeParent = _controller.UNCG;
				var runMode = popup.action;
				
				var version = 1;

				/***** To be used in Submission Level *****/

				// Check if no changes at Submission level ; run mode should always be ADJ
				if (selectedSubmission.data['action'] == _controller.ADJ) runModeParent = _controller.ADJ;
				data['actionSub'] = runModeParent;
				
				data['FATCARptMstrUUID'] = selectedSubmission.data['FATCARptMstrUUID'];
				
				// Assign Original UUID
				if (runModeParent == _controller.ADJ){
					// UUID will be TEMPUUID; original UUID is assigned from adjustment state
					data['origFATCARptMstrUUID'] = selectedSubmission.data['origFATCARptMstrUUID'];	
				}
				/* For adding of Slip level data during Amendment, needs to send origFATCARptFileUUID and 
				   origFATCARptFileUUID of selected RptUnit to smartview.
				*/
				else if (selectedSubmission.data['submissionType'] == _controller.AMD){
					data['origFATCARptMstrUUID'] = selectedSubmission.data['FATCARptMstrUUID'];
				}else{
					data['origFATCARptMstrUUID'] = _controller.BLNK;
				}
				
				data['FATCACode'] = selectedSubmission.data['FATCACode'];
				data['FILevel'] = selectedSubmission.data['FILevel'];
				data['FICode'] = selectedSubmission.data['FICode'];
				data['taxYear'] = selectedSubmission.data['taxYear'];	
				data['asOfDate'] = selectedSubmission.data['asOfDate'];	
				data['TPSDeff'] = selectedSubmission.data['TPSDeff'];	
				data['submissionType'] = selectedSubmission.data['submissionType'];	
				data['submissionSeq'] = selectedSubmission.data['submissionSeq'];	
				data['runMode'] = selectedSubmission.data['runMode'];	
				data['rptFile'] = selectedSubmission.data['rptFile'];	
				data['version'] = selectedSubmission.data['version'];	
				data['runDate'] = selectedSubmission.data['runDate'];
				data['msgStat'] = selectedSubmission.data['stat'];

				// Update Msg Status to 01-Pending if adding Slip for Submission (Submission Type: AMD-Amendment, RunMode: 02-Test, MsgStat: 02-Processed)
				if (selectedSubmission.data['submissionType'] == _controller.AMD && 
				    selectedSubmission.data['runMode'] == _controller.RUNMODE_Test &&
					selectedSubmission.data['stat'] == _controller.MSGSTAT_Processed && 
					popup.action == _controller.ADD)
				{
					data['msgStat'] = _controller.MSGSTAT_Pending; // Pending
				}
			
				/***** To be used in Reporting Unit Level *****/

				// Check if no changes at Reporting Unit level ; run mode should always be ADJ
				if(selectedRptUnit.data['action'] == _controller.ADJ) runModeParent = _controller.ADJ;
				data['actionRpt'] = runModeParent;
				
				data['FATCARptFileUUID'] = selectedRptUnit.data['FATCARptFileUUID'];	
				data['FATCARptFileDetlUUID'] = selectedRptUnit.data['FATCARptFileDetlUUID'];
				
				// Assign Original UUID
				if (runModeParent == _controller.ADJ){
					// UUID will be TEMPUUID; original UUID is assigned from adjustment state
					data['origFATCARptFileUUID'] = selectedRptUnit.data['origFATCARptFileUUID'];
					data['origFATCARptFileDetlUUID'] = selectedRptUnit.data['origFATCARptFileDetlUUID'];
				}
				/* For adding of Slip level data during Amendment, needs to send origFATCARptFileUUID and 
				   origFATCARptFileUUID of selected RptUnit to smartview.
				*/
				else if (selectedSubmission.data['submissionType'] == _controller.AMD){
					data['origFATCARptFileUUID'] = selectedRptUnit.data['FATCARptFileUUID'];
					data['origFATCARptFileDetlUUID'] = selectedRptUnit.data['FATCARptFileDetlUUID'];					
				}else{
					data['origFATCARptFileUUID'] = _controller.BLNK;
					data['origFATCARptFileDetlUUID'] = _controller.BLNK;
				}
				
				data['FATCARptFileVer'] = selectedRptUnit.data['FATCARptFileVer'];
				data['FATCARptFileDetlVer'] = selectedRptUnit.data['FATCARptFileDetlVer'];
				
				/***** To be used in to show new Reporting Unit Level *****/
				data['rptUnitLevelDesc'] = selectedRptUnit.data['rptUnitLevelDesc'];
				data['rptUnitName'] = selectedRptUnit.data['rptUnitName'];
				data['govTaxAgency'] = selectedRptUnit.data['govTaxAgency'];
				data['numRFFI'] = selectedRptUnit.data['numRFFI'];
				data['reportingFFI'] = selectedRptUnit.data['reportingFFI'];

 				/* For validation of Slip level, needs to send Correct Doc Ref ID of selected RptUnit
				   to smartview. This won't effect to the copying Doc Ref ID to Correct Doc Ref ID
				   - Adding Slip can be done only for adjustment
				   - Doc Ref ID = blank, Correct Doc Ref ID <> blank for adjustment.
				*/
				data['assocDocRefID'] = selectedRptUnit.data['assocDocRefID'];
				
				data['fileStat'] = selectedRptUnit.data['stat'];

				// Assign additional fields; show blank value when adjusting
				if (runModeParent == _controller.ADJ){
					data['msgID'] = _controller.BLNK;
					data['docRefID'] = _controller.BLNK;
					data['numSlip'] = _controller.BLNK;
					data['numSlipErr'] = _controller.BLNK;				
				}else{
					data['msgID'] = selectedRptUnit.data['msgID'];
					data['docRefID'] = selectedRptUnit.data['docRefID'];
					data['numSlip'] = selectedRptUnit.data['numSlip'];
					data['numSlipErr'] = selectedRptUnit.data['numSlipErr'];
				}
				
				/***** To be used in Slip Level *****/
				
				// Check if no changes at Reporting Unit level ; run mode should always be ADJ
				if (selectedSlip){
					if (selectedSlip.data['action'] == _controller.ADD) runMode = _controller.ADD;
					if (popup.action != _controller.ADD) version = selectedSlip.data['version'];
				}

				data['actionSlip'] = runMode;
				data['version'] = version;
				
				data['FATCARptSlipUUID'] = popup.uuid; // new UUID
				data['reportingFFI'] = popup.getField('actReqReportingFFI').getValue();
				data['account'] = popup.getField('actReqAccount').getValue();
				data['slipType'] = popup.getField('actReqSubmission').getValue();
				
				data['entityID'] = popup.getField('actReqEntName').getEntityID();
				data['entityType'] = popup.getField('actReqEntName').getEntityType();	
				data['entityName'] = popup.getField('actReqEntName').getValue();

				return data;				
			}
		})
		,slipFullPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 700
			,closeAction: 'hide'
			,autoHeight: true
			,autoScroll: false
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					layout: 'form'
					,itemId: 'popup_SilpFullView'
					,style: 'padding:4px'
					,border:false
					,items: [
						{
							itemId: 'mainLayout5'
							,xtype: 'fieldset'
							,title: _translationMap['SearchTitle']
							,items: [
								{
									layout: 'column'
									,border: false
									,defaults: {
										layout: 'form'
										,border: false
									}
									,items: [
										{
											columnWidth: 0.40
											,items: [
												new DesktopWeb.Controls.Label({											
													itemId: 'detlReportingFFI'
													,fieldLabel: _translationMap['ReportingFFI']																			
												})
												,new DesktopWeb.Controls.Checkbox({
													itemId: 'detlErrorOnly'
													,boxLabel: _translationMap['ErrorOnly']
												})
											]
										}
										,{
											columnWidth: 0.10
											,items: [
												_buttons['searchSilpBtn']
											]
										}
									]
								}
							]
						}
						,{
							itemId: 'mainLayout6'
							,xtype: 'fieldset'
							,title: _translationMap['AccountTitle']
							,items: [
								{
									layout: 'column'
									,border: false
									,defaults: {
										layout: 'form'
										,border: false
									}
									,items: [
										_grids['accountGrid']
									]
								}
							]
						}
					]
				}												
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['slipFullPopup'];
				popup.action = action;
				
				popup.setTitle(_translationMap['SlipFullView']);
				popup.populate(action);
			}
			,populate: function(action)
			{
				var selectedSlipFull = _grids['slipGrid'].getSelectedRecord();
				
				var popup = _popups['slipFullPopup'];
				popup.enableAllFields();
				
				switch(action)
				{					
					case _controller.INQ:
					{
						popup.getField('detlReportingFFI').setValue(selectedSlipFull.data['reportingFFI']);
						popup.getField('detlErrorOnly').reset();
						
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
		})		
		,admin: new DesktopWeb.AdvancedControls.PopupWindow({								
			width: 395				
			,closeAction: 'hide'					
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
									,value: 'test'					
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
			,init: function(title, data)
			{
				this.setTitle(title);
				this.getField('procDate').setValue(data['procDate']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['userName']);
				this.getField('modUser').setValue(data['modUser']);
			}										
		})
		,history: new DesktopWeb.AdvancedControls.HistoryPopup()		
	}
	
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
						itemId: 'mainLayout1'
						,xtype:'fieldset'
						,title: _translationMap['SearchTitle']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth
						,items: [
							{
								// Col#1
								layout: 'form'
								,columnWidth: 0.40
								,labelWidth: 80
								,items :[
									_fields['regulationFld']
									,_fields['taxYearFld']
                                    ,_fields['rfiDomicileFld']
								]
							}
							,{
								// Col#2
								layout: 'form'
								,columnWidth: 0.40
								,labelWidth: 110
								,items :[
									_fields['msgIDFld']
									,_fields['docRefIDFld']
									,_fields['slipIDFld']
								]
							}
							,{
								// Col#3
								layout: 'form'
								,columnWidth: 0.10
								,items :[
									_buttons['searchBtn']
								]
							}							
						]
					}
					,{
						itemId: 'mainLayout2'
						,xtype:'fieldset'
						,title: _translationMap['SubmissionTitle']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth
						,items: [
							_grids['submissionGrid']
						]
					}
					,{
						itemId: 'mainLayout3'
						,xtype:'fieldset'
						,title: _translationMap['ReportingTitle']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth						
						,items: [
							_grids['reportingUnitGrid']							
						]
					}
					,{
						itemId: 'mainLayout4'
						,xtype:'fieldset'
						,title: _translationMap['SlipTitle']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth						
						,items: [
							_grids['slipGrid']
						]
					}
					,_fields['genOutput']
				]																				
			}
		)		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function(){
						
						// To final checking if any action on screen
						_controller.checkUpdatesFlag();
						
						if (_controller.updatesFlag){
                            if (_controller.validateSlips()) {
                                _controller.clearContextErrors();
                                DesktopWeb.Util.commitScreen();
                            }
						}else{
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){
						if (_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
						}else{
							cancelScreen(true);
						}
						function cancelScreen(confirm){
							if (confirm) DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
		]			
	}	
}