 /*********************************************************************************************
 * @file	AcctAssociate.Resources.js
 * @author	Cherdsak Sangkasen
 * @desc	Resources JS file for Account Fee Model Association screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *	21 July 2014 C. Sangkasen P0212180 Advisor Flex Fee T55481 
 *			- Support Broker/Sales Rep displaying.
 *
 *  24 Sep 2014 A. Mongkonrat P0212180 DFT0038413 T55776
 *              A record isn't updated when changing account number.
 */
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	
	// content dimensions
	var _layoutHeight = 505;
	var _layoutWidth = 715;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// **** fields ****
	var _fields = {				
		accountNumSrch: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['AccountNum']
				, width: 400	
				, hidden: true
				, allowBlank: true
				, smartview: 'accountSearch'				
				, fields: ['displayValue', 'acctNum']
				, valueField: 'acctNum'
				, displayField: 'displayValue'	
				, addtlSearchParams: [{name: 'incAllStat', valueFn: function(){return 'yes'}}]	
			}
		)
		, feeModelSrch: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['FeeModel']
				, style: 'position: relative'
				, width: 400	
				, hidden: true
				, allowBlank: true				
				, smartview: 'feeModelCodeSearch'				
				, fields: ['feeModelCode', 'feeModelDesc', 'displayValue', 'holdingEntityCode', 'feeModelType']
				, valueField: 'feeModelCode'
				, displayField: 'displayValue'	
				, addtlSearchParams: [
					{name: 'searchFeeModelType', valueFn: function(){return ''}}
					, {name: 'searchHoldCompany', valueFn: function(){return ''}}
				]				
			}
		)
		, holdCompSrch: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['HoldingCompany']
				, style: 'position: relative'
				, width: 400	
				, hidden: true
				, allowBlank: true	
				, smartview: 'holdingCompanySearch'				
				, fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'assetAggrMethod', 'displayValue', 'coUsage']
				, valueField: 'holdingCompanyCode'
				, displayField: 'displayValue'	
				, addtlSearchParams: [
					{name: 'assetsAggrMethod', valueFn: function(){return ''}}
					, {name: 'coUsage', valueFn: function(){return ''}}
				]				
			}
		)
		, invInstrSrch: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['InvoiceInstruction']
				, style: 'position: relative'
				, width: 400	
				, hidden: true
				, allowBlank: true	
				, smartview: 'invoiceInstrSearch'				
				, fields: ['billInstrID', 'billInstrCode', 'invoiceName', 'holdingEntityCode', 'displayValue']
				, valueField: 'billInstrCode'
				, displayField: 'displayValue'	
				, addtlSearchParams: [{name: 'holdingEntityCode', valueFn: function(){return ''}}]				
			}
		)
		, rptGrpSrch: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['ReportGroup']
				, style: 'position: relative'
				, width: 400	
				, hidden: true
				, allowBlank: true	
				, smartview: 'reportGroupSearch'				
				, fields: ['reportGroupID', 'reportGroupDesc', 'holdingEntityCode', 'displayValue']
				, valueField: 'reportGroupID'
				, displayField: 'displayValue'	
				, addtlSearchParams: [{name: 'holdingEntityCode', valueFn: function(){return ''}}]				
			}
		)
		, optSelectAll: new DesktopWeb.Controls.Radio(
			{
				boxLabel: _translationMap['All']
				, name: 'periodSrch'
				, width: 50		
				, listeners:{          
					check: function(ctl, val) {
						if (val) {
							_controller.doSrchCheck();
						}
					}
				}		
			}
		)
		, optSelectAsOfDate: new DesktopWeb.Controls.Radio(
			{
				boxLabel: _translationMap['EffectiveAsOf']
				, name: 'periodSrch'
				, width: 100		
				, listeners:{          
					check: function(ctl, val) {
						if (val) {
							_controller.doSrchCheck();
						}
					}
				}			
			}
		)				
		, asOfDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['EffectiveAsOf']
				,width: 200
				,safeParse: function(b,c){
				
					if(/[gGhH]/.test(c.replace(/(\\.)/g,""))){	
						return Date.parseDate(b,c)
					}else{
						var a=Date.parseDate(b+" "+this.initTime,c+" "+this.initTimeFormat,true);
						if(a){
							return a.clearTime()
						}else {						
							_controller.doParseDate('asOfDate');
						}
					}
				}				
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		) 
		, accountNum: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['AccountNum']
				, width: 400	
				, smartview: 'accountSearch'				
				, fields: ['displayValue', 'acctNum', 'broker', 'brokerName', 'salesRep', 'slsrepName']
				, valueField: 'acctNum'
				, displayField: 'displayValue'	
				, addtlSearchParams: [{name: 'incAllStat', valueFn: function(){return 'yes'}}]	
			}
		)
		, feeModelType : new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['FeeModelType']
				, editable: false	
				, lastQuery: ''				
				, width: 400
				, listeners:{ 				
					select: function() {					
						_controller.selectFeeModelType(_fields['feeModelType'].getValue(), _controller.getMode());	
						_fields['feeModelAddNewCode'].setValue('');
						_fields['feeModelAddExistCode'].setValue('');
						_fields['feeModelAddDesc'].setValue('');
						_fields['feeModelCode'].setValue('');
						_fields['feeModelDesc'].setValue('');	
						_fields['holdComp'].setValue('');	
					}
					, change: function(fld, newValue, oldValue)
					{
						_controller.selectFeeModelType(_fields['feeModelType'].getValue(), _controller.getMode());	
						_fields['feeModelAddNewCode'].setValue('');
						_fields['feeModelAddExistCode'].setValue('');
						_fields['feeModelAddDesc'].setValue('');
						_fields['feeModelCode'].setValue('');
						_fields['feeModelDesc'].setValue('');	
						_fields['holdComp'].setValue('');							
					}
				}
			}
		)
		, optExistFeeModel: new DesktopWeb.Controls.Radio(
			{
				boxLabel: _translationMap['ExistFeeModel']	 	
				, style: 'margin-left:5px; padding-left:5px;'
				, name: 'feeModel'
				, width: 150		
				, listeners:{          
					check: function(ctl, val) {
						if (val) {
							_controller.doOptCheck();
						}
					}
				}				
			}
		)
		, optNewFeeModel: new DesktopWeb.Controls.Radio(
			{
				boxLabel: _translationMap['NewFeeModel']
				, style: 'margin-left:5px; padding-left:5px;'
				, name: 'feeModel'
				, width: 150	
				, listeners:{          
					check: function(ctl, val) {
						if (val) {
							_controller.doOptCheck();
						}
					}
				}				
			}
		)
		, feeModelAddExistCode: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['FeeModelCode']
				, style: 'padding-left:5px;'
				, width: 400	
				, smartview: 'feeModelCodeSearch'				
				, fields: ['feeModelCode', 'feeModelDesc', 'displayValue', 'holdingEntityCode', 'feeModelType']
				, valueField: 'feeModelCode'
				, displayField: 'displayValue'		
				, addtlSearchParams: [
					{name: 'searchFeeModelType', valueFn: function(){return _fields['feeModelType'].getValue();}}
					, {name: 'searchHoldCompany', valueFn: function(){return _controller.getHoldComp();}}
				]				
				, listeners: {
					populated: function()
					{
						_controller.populateFeeDesc('feeModelAdd');
						_controller.populateHoldComp('feeModelAdd');
						_controller.populateFeeModelType('feeModelAdd');
					}
					,cleared: function()
					{
						_controller.populateFeeDesc('feeModelAdd');
						if (!_controller.isHoldCompSolid())
						{
							_controller.populateHoldComp('feeModelAdd');
						}
						_controller.populateFeeModelType('feeModelAdd');
					}				
				}	
			}
		)
		, feeModelAddNewCode: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['FeeModelCode']
				, style: 'padding-left:5px;'
				, maxLength: 6
				, width: 200																										
			}
		)		
		, feeModelAddDesc: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['FeeModelDesc']
				, style: 'padding-left:5px;'
				, width: 400																										
			}
		)
		, feeModelCode: new DesktopWeb.Controls.SuggestField( 
			{
				fieldLabel: _translationMap['FeeModelCode']
				, style: 'padding-left:5px;'
				, width: 400
				, smartview: 'feeModelCodeSearch'				
				, fields: ['feeModelCode', 'feeModelDesc', 'displayValue', 'holdingEntityCode', 'feeModelType']
				, valueField: 'feeModelCode'
				, displayField: 'displayValue'		
				, addtlSearchParams: [
					{name: 'searchFeeModelType', valueFn: function(){return _fields['feeModelType'].getValue();}}
					, {name: 'searchHoldCompany', valueFn: function(){return _controller.getHoldComp();}}
				]				
				, listeners: {
					populated: function()
					{						
						_controller.populateFeeDesc('feeModelExist');
						_controller.populateHoldComp('feeModelExist');
						_controller.populateFeeModelType('feeModelExist');
					}
					,cleared: function()
					{
						_controller.populateFeeDesc('feeModelExist');
						if (!_controller.isHoldCompSolid())
						{
							_controller.populateHoldComp('feeModelExist');
						}
						_controller.populateFeeModelType('feeModelExist');
					}				
				}				
			}
		)		
		, feeModelDesc: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['FeeModelDesc']
				, style: 'padding-left:5px;'
				, width: 400																										
			}
		)
		, holdComp: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['HoldingCompany']
				, style: 'position: relative'
				, width: 400	
				, allowBlank: true	
				, editable: false
				, disabled: true				
				, smartview: 'holdingCompanySearch'				
				, fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'assetAggrMethod', 'displayValue', 'coUsage']
				, valueField: 'holdingCompanyCode'
				, displayField: 'displayValue'	
				, addtlSearchParams: [
					{name: 'assetsAggrMethod', valueFn: function(){return ''}}
					, {name: 'coUsage', valueFn: function(){return ''}}
				]				
			}
		)
		, invInstr: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['InvoiceInstruction']
				, width: 400	
				, smartview: 'invoiceInstrSearch'				
				, fields: ['billInstrID', 'billInstrCode', 'invoiceName', 'holdingEntityCode', 'displayValue']
				, valueField: 'billInstrCode'
				, displayField: 'displayValue'	
				, addtlSearchParams: [{name: 'holdingEntityCode', valueFn: function(){return _controller.getHoldComp();}}]		
				, listeners: {
					populated: function()
					{						
						_controller.populateHoldComp('invinstr');
					}
					,cleared: function()
					{
						/*if (!_controller.isHoldCompSolid())
						{
							_controller.populateHoldComp('invinstr');
						}*/
					}	
				}				
			}
		)		
		, rptGrp: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['ReportGroup']
				, width: 400	
				, smartview: 'reportGroupSearch'				
				, fields: ['reportGroupID', 'reportGroupDesc', 'holdingEntityCode', 'displayValue']
				, valueField: 'reportGroupID'
				, displayField: 'displayValue'	
				, addtlSearchParams: [{name: 'holdingEntityCode', valueFn: function(){return _controller.getHoldComp();}}]		
				, listeners: {
					populated: function()
					{						
						_controller.populateHoldComp('rptgrp');
					}
					,cleared: function()
					{
						/*if (!_controller.isHoldCompSolid())
						{
							_controller.populateHoldComp('rptgrp');
						}*/
					}				
				}				
			}
		)
		, effectiveDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['EffectiveDate']
				,width: 200
				, allowBlank: false
				,safeParse:function(b,c){
					if(/[gGhH]/.test(c.replace(/(\\.)/g,""))){	
						return Date.parseDate(b,c)
					}else{
						var a=Date.parseDate(b+" "+this.initTime,c+" "+this.initTimeFormat,true);
						if(a){
							return a.clearTime()
						}else {_controller.doParseDate('effectiveDate');}
					}
				}
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
		, stopDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['StopDate']
				,width: 200
				, allowBlank: false
				,safeParse:function(b,c){
					if(/[gGhH]/.test(c.replace(/(\\.)/g,""))){	
						return Date.parseDate(b,c)
					}else{
						var a=Date.parseDate(b+" "+this.initTime,c+" "+this.initTimeFormat,true);
						if(a){
							return a.clearTime()
						}else {_controller.doParseDate('stopDate');}
					}
				}
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
		, userName: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['Username']
			}
		)	
		, modUser: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['ModUser']
			}
		)
		, procDate: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['ProcessDate']
			}
		)
		, modDate: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['ModDate']
			}
		)
		, searchBy : new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['SearchBy']
				, editable: false			
				, lastQuery: ''
				, width: 400
				, listeners:{ 				
					select: function() {					
						_controller.populateSearchField(_fields['searchBy'].getValue());	
						_controller.enableSearch();
					}
				}
			}
		)
	}
	
	var _buttons = {
		cmdSearch: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Search']
				, handler: function(){
						if(_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg);
							function handlePromptMsg(btn){
								if(btn){
									_controller.doSearch(false);
								}
							}
						}else{
							_controller.doSearch(false);
						}
					}
			}
		)
		, cmdAcctAsscAdd: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Add']
				, handler: function(){_controller.openActionPopup( 'frmAcctAssc', _controller.ADD);}	
			}
		)
		, cmdAcctAsscMod: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Modify']
				, handler: function(){_controller.openActionPopup( 'frmAcctAssc', _controller.MOD);}
			}
		)
		, cmdAcctAsscDel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Delete']
				, handler: function(){_controller.doDelete();}
			}
		)
		, cmdAcctAsscMore: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['More']
				, handler: function() {_controller.doSearch(true);}	
			}
		)
		, cmdAcctAsscSubmit: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['OK']
				, handler: function(){
					if (_popups['frmAcctAssc'].isValid())
					{						
						_controller.doValidate(_popups['frmAcctAssc'].action, _popups['frmAcctAssc'].getData(_popups['frmAcctAssc'].action));
					}
				}
			}
		)
		, cmdAcctAsscCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					if (_popups['frmAcctAssc'].isValid())
					{
						_popups['frmAcctAssc'].hide();
					}
				}
			}
		)
		, cmdAcctAsscHist: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['History']
				, handler: function() {_controller.openHistoryPopup();}	
			}
		)
		, cmdAcctAsscAdmin: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Admin']
				, handler: function() {_controller.openAdminPopup();}	
			}
		)
		, btnAcctDetail: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['AccountDetail']
				, id : 'btnAcctDetail'
				, name : 'btnAcctDetail'
				, handler: function(){
					_controller.accessAcctDetail();					
				}
			}
		)
	}	
	
	// **** grids ****
	var _grids = {
		grdAcctAssc: new DesktopWeb.AdvancedControls.GridPanel
		(
			{
				width: _layoutWidth
				, style: "margin-top:15px;margin-bottom:15px;"
				, autoScroll: true
				, height: 250
				, store: new Ext.data.XmlStore
				(
					{
						record: 'AcctFeeModelDetl'
						, fields: ['accountNum', 
									'name',
									'feeModelCode',
									'feeModelDesc',
									'feeModelType',
									'feeModelTypeDesc', 
									'agencyCode',
									'agencyName',
									'agency',
									'agentCode',
									'agentName',
									'agent',
									'holdingEntCode',
									'holdingEntName',
									'holdingEnt',
									'invoiceId',
									'invoiceName',
									'invoice',
									'reportId',
									'reportName',
									'report',
									'effectiveDate', 
									'stopDate', 
									'shrAcctFeeId', 
									'shrAcctFeeConfigVer', 
									'gridIndex', 
									'runMode',
									'errMsg']
						, listeners: {
							load: function(store, records) {	
								Ext.each(records, function(record){
									record.data['effectiveDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['effectiveDate']);
									record.data['stopDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['stopDate']);
								});
								
								store.filterBy(function(record){
										return (record.data.runMode != _controller.DEL);										
									}
								)								
							}
						}
					}				
				)
				, selModel: new Ext.grid.RowSelectionModel
				(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record)
							{
								_controller.setSelectedAcctAssc(record.get("gridIndex"));
							}					
						}
					}
				)
				, colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						, columns: [	
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
							 , width: 25 }
							, {header: _translationMap['HoldingCompany'], dataIndex: 'holdingEnt', width: 150}
							, {header: _translationMap['Account'], dataIndex: 'accountNum', width:100}
							, {header: _translationMap['Name'], dataIndex: 'name', width:100}
							, {header: _translationMap['FeeModelType'], dataIndex: 'feeModelTypeDesc', width:150}
							, {header: _translationMap['FeeModelCode'], dataIndex: 'feeModelCode', width:100}
							, {header: _translationMap['FeeModelDesc'], dataIndex: 'feeModelDesc', width:150}
							, {header: _translationMap['AgencyCode'], dataIndex: 'agency', width:100}
							, {header: _translationMap['AgentCode'], dataIndex: 'agent', width:100}
							, {header: _translationMap['InvoiceInstruction1'], dataIndex: 'invoice', width: 150}
							, {header: _translationMap['ReportGroup1'], dataIndex: 'report', width: 150}
							, {header: _translationMap['EffectiveDate'], dataIndex: 'effectiveDate', width:100}
							, {header: _translationMap['StopDate'], dataIndex: 'stopDate', width:100}
						]
					}
				)
				, listeners:
				{
					rowdblclick: function(grid, rowindex, e)
					{
						_controller.openActionPopup( 'frmAcctAssc', _controller.VEW);
					}	
				}
				, buttons: [		
					_buttons['btnAcctDetail']
					, _buttons['cmdAcctAsscAdd']
					, _buttons['cmdAcctAsscMod']
					, _buttons['cmdAcctAsscDel']	
					, _buttons['cmdAcctAsscMore']
					, _buttons['cmdAcctAsscHist']
					, _buttons['cmdAcctAsscAdmin']
				]
			}
		)
	}
		
// **** popups ****
	var _popups = {		
		frmAcctAssc: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				, width: 700
				, closeAction: 'hide'
				, modal: true
				, defaults: {border:false}
				
				, items: [
					{
						html: _translationMap['OK']
						, style: 'text-align:center'		
						, defaults: {border:false}						
					}					
					, {
						layout: 'form'
						, defaults: {border: false, labelWidth:140}
						, style: 'margin-left:5px;margin-top:5px;,margin-bottom:5px;'
						, labelWidth: 140
						, items: [			
							_fields['feeModelType']
							, {
								xtype: 'fieldset'
								, style: 'position:relative; margin-left:0px; padding-left:0px;'
								, id: 'feeModelAdd'	
								, width: 675
								, items: [
									{							
										layout: 'form'
										, defaults: {border: false}
										, style: 'margin-left:5px;'
										,items: [
											{
												width: 600
												, layout: 'column'
												, style: 'margin-top:5px; padding-bottom:5px;font:12px tahoma,arial,helvetica,sans-serif'
												, items: [
													_fields['optExistFeeModel']
													, _fields['optNewFeeModel']
												]
											}
											,{
												width: 600
												, layout: 'form'
												, style: 'margin-top:5px; padding-bottom:5px;margin-left:5px;'
												, labelWidth: 140
												, items: [
													_fields['feeModelAddExistCode']
													, _fields['feeModelAddNewCode']
													, _fields['feeModelAddDesc']
												]
											}											
										]
									}
								]
							}
							, new Ext.Container({
								id: 'feeModelExist'
								, hideMode: 'offsets'
								, hidden: false
								, layout: 'form'	
								, items: [
									_fields['feeModelCode']
									, _fields['feeModelDesc']
								]
							}) 
							, _fields['accountNum']
							, _fields['holdComp']
							, _fields['invInstr']
							, _fields['rptGrp']
							, _fields['effectiveDate']							
							, _fields['stopDate']
						]
					}
				]			
				, buttons: [
					_buttons['cmdAcctAsscSubmit']
					, _buttons['cmdAcctAsscCancel']
				]
				, init: function(action)
				{					
					this.get(0).hide();
					this.action = action;		
					this.enableAllFields();					
					this.clearAllFields();
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle("Account Association - Add");
							_controller.populateAcctAssc(action);
							_controller.enableFields(action);
							_controller.displayFields(action);
							break;
						}
						case _controller.MOD:
						{
							this.setTitle("Account Association - Modify");
							_controller.populateAcctAssc(action);
							_controller.enableFields(action);
							_controller.displayFields(action);
							break;
						}
						case _controller.DEL:
						{							
							/* nothing to de when delete*/
							break;
						}
						case _controller.VEW:
						{
							this.setTitle("Account Association");
							_controller.populateAcctAssc(action);
							_controller.enableFields(action);
							_controller.displayFields(action);
							break;
						}
					}					
				}
				, getData: function(action)
				{									
					var data = {};	
					data['errMsg']  = "";
					
					if (_fields['accountNum'].selectedRecord != null && _fields['accountNum'].getRawValue() != "")
					{
						data['accountNum'] = _fields['accountNum'].selectedRecord.get('acctNum');
						data['agencyCode'] = _fields['accountNum'].selectedRecord.get('broker');
						data['agencyName'] = _fields['accountNum'].selectedRecord.get('brokerName');
						data['agentCode'] = _fields['accountNum'].selectedRecord.get('salesRep');
						data['agentName'] = _fields['accountNum'].selectedRecord.get('slsrepName');
					}
					else
					{
						data['accountNum'] = _controller.BLANK;
					}
					
					if (_fields['feeModelType'].getValue() != "")
					{
						data['feeModelType'] = _fields['feeModelType'].getValue();
						data['feeModelTypeDesc'] = _fields['feeModelType'].getRawValue();
					}
					else
					{
						data['feeModelType'] = _controller.BLANK;
						data['feeModelTypeDesc'] = _controller.BLANK;
					}
					
					if (_fields['effectiveDate'].getValue() != "")
					{						
						data['effectiveDate'] = _fields['effectiveDate'].getSMVDateString();
					}
					else
					{
						data['effectiveDate'] = _controller.BLANK;
					}
					
					if (_fields['stopDate'].getValue() != "")
					{						
						data['stopDate'] = _fields['stopDate'].getSMVDateString();
					}
					else
					{
						data['stopDate'] = _controller.BLANK;
					}
					
					if (action == _controller.ADD && _fields['accountNum'].selectedRecord != null && _fields['accountNum'].getRawValue() != "")
					{
						data['name'] = _controller.getAccountNameBySearch(_fields['accountNum'].selectedRecord.get('displayValue'));
						data['agencyCode'] = _fields['accountNum'].selectedRecord.get('broker');
						data['agencyName'] = _fields['accountNum'].selectedRecord.get('brokerName');
						data['agentCode'] = _fields['accountNum'].selectedRecord.get('salesRep');
						data['agentName'] = _fields['accountNum'].selectedRecord.get('slsrepName');
					}
					else
					{
						data['name'] = _controller.getAccountNameBySearch(_fields['accountNum'].selectedRecord.get('displayValue'));
					}
					
					if (_fields['holdComp'].selectedRecord != null && _fields['holdComp'].getRawValue() != "")
					{
						data['holdingEntCode'] = _fields['holdComp'].selectedRecord.get('holdingCompanyCode');
						data['holdingEntName'] = _fields['holdComp'].selectedRecord.get('holdingCompanyDesc');
					}
					else
					{
						data['holdingEntCode'] = _controller.BLANK;
						data['holdingEntName'] = _controller.BLANK;
					}
					
					if (_fields['invInstr'].selectedRecord != null && _fields['invInstr'].getRawValue() != "")
					{
						data['invInstrId'] = _fields['invInstr'].selectedRecord.get('billInstrCode');
						data['invInstrName'] = _fields['invInstr'].selectedRecord.get('invoiceName');
					}
					else
					{
						data['invInstrId'] = _controller.BLANK;
						data['invInstrName'] = _controller.BLANK;
					}
					
					if (_fields['rptGrp'].selectedRecord != null && _fields['rptGrp'].getRawValue() != "")
					{
						data['rptGrpId'] = _fields['rptGrp'].selectedRecord.get('reportGroupID');
						data['rptGrpName'] = _fields['rptGrp'].selectedRecord.get('reportGroupDesc');
					}
					else
					{
						data['rptGrpId'] = _controller.BLANK;
						data['rptGrpName'] = _controller.BLANK;
					}
					
					
					if (action == _controller.ADD)
					{
						if (_controller.allowNewFeeModel())
						{
							if (_fields['optNewFeeModel'].getValue())
							{
								data['feeModelCode'] = _fields['feeModelAddNewCode'].getValue();	
								data['feeModelDesc'] = _fields['feeModelAddDesc'].getValue();	
							}
							else
							{
								if (_fields['feeModelAddExistCode'].selectedRecord != null && _fields['feeModelAddExistCode'].getRawValue() != "")
								{
									data['feeModelCode'] = _fields['feeModelAddExistCode'].selectedRecord.get('feeModelCode');
								}
								else
								{
									data['feeModelCode'] = '';
								}
								data['feeModelDesc'] = _fields['feeModelAddDesc'].getValue();	
							}
						}
						else
						{
							if (_fields['feeModelCode'].selectedRecord != null && _fields['feeModelCode'].getRawValue() != "")
							{
								data['feeModelCode'] = _fields['feeModelCode'].selectedRecord.get('feeModelCode');
								data['feeModelDesc'] = _fields['feeModelDesc'].getValue();	
							}
							else
							{
								data['feeModelCode'] = '';
								data['feeModelDesc'] = '';
							}
						}
					}
					else
					{
						if (_fields['feeModelCode'].selectedRecord != null && _fields['feeModelCode'].getRawValue() != "")
						{
							data['feeModelCode'] = _fields['feeModelCode'].selectedRecord.get('feeModelCode');
						}
						else
						{
							data['feeModelCode'] = '';
						}
						data['feeModelDesc'] = _fields['feeModelDesc'].getValue();		
					}					
					
					return data;
				}
				, disableAllFields: function()
				{												
				}
				, enableAllFields: function()
				{											
				}
			}
		)

		, frmAdmin: new DesktopWeb.AdvancedControls.PopupWindow(
			{								
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
									_fields['userName']
									, _fields['modUser']							
								]
							}							
							,{
								width: 185
								,layout: 'form'
								,defaults: {width: 80}																							
								,items: [
									_fields['procDate']
									, _fields['modDate']
								]
							}
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['OK']
							,handler: function(){_popups['frmAdmin'].hide();}
						}
					)
				]
				,init: function(title, data)
				{
					this.setTitle(title);
					_fields['userName'].setValue(data['userName']);
					_fields['procDate'].setValue(data['procDate']);
					_fields['modDate'].setValue(data['modDate']);
					_fields['modUser'].setValue(data['modUser']);				
				}										
			}					
		)
		
		, frmHistory: new DesktopWeb.AdvancedControls.HistoryPopup()			
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
				, width: _layoutWidth
				, layout: 'form'
				, items: [
					{
						layout: 'column'
						, style: "margin-bottom:10px;"
						, defaults: {labelWidth: 80}	
						, items: [
							{
								width: 600
								, layout: 'form'
								, labelWidth: 140
								, items: [
									_fields['searchBy']
									, _fields['accountNumSrch']
									, _fields['feeModelSrch']
									, _fields['holdCompSrch']
									, _fields['invInstrSrch']
									, _fields['rptGrpSrch']
									, {
										layout: 'column'
										, style: "margin-bottom:10px;"
										, defaults: {labelWidth: 80}	
										, items: [
											{
												width: 500
												, layout: 'column'
												, labelWidth: 100
												, items: [
													_fields['optSelectAll']
													, _fields['optSelectAsOfDate']	
													, _fields['asOfDate']									
												]
											}
										]
									}
								]
							}
						]
					}
					, {
						layout: 'form'
						, style: 'text-align:right;'
						, items: [
							_buttons['cmdSearch']
						]
					}
					, {					
						layout: 'form'
						, items: [
							_grids['grdAcctAssc']
						]
					}
				]				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: 'OK'
					, handler: function(){
						if(_controller.updatesFlag)
						{
							_controller.doCommitValidate();
						}
						else
						{
							if (_controller.doBackToScr() != '')
							{
								_controller.toScreen(_controller.doBackToScr());
							}
							else
							{
								DesktopWeb.Util.cancelScreen();
							}
						}
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'Cancel'
					, handler: function(){
						if(_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg);
							function handlePromptMsg(btn){
								if(btn){
									if (_controller.doBackToScr() != '')
									{
										_controller.toScreen(_controller.doBackToScr());
									}
									else
									{
										DesktopWeb.Util.cancelScreen();
									}
								}
							}
						}else{
							if (_controller.doBackToScr() != '')
							{
								_controller.toScreen(_controller.doBackToScr());
							}
							else
							{
								DesktopWeb.Util.cancelScreen();
							}
						}
					}
				}
			)
		]			
	}
}