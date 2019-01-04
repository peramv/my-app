/*********************************************************************************************
 * @file	RegAcctInfoRev.Resources.js
 * @author	Matira T.
 * @desc	Resources JS file for Reportable Account Review screen
 *********************************************************************************************/
/*
 *	Navigate: Menu > Account Level Maintenance > Reportable Account Review
 *
 *	History : 
 *
 *	20-Nov-2017 Matira Thanetkulabut P0268205-34 FATCA-CRS Enhancement 18.2
 *				- Initial
 *
 *	08-Dec-2017 Matira Thanetkulabut P0268205-60 FATCA-CRS 18.2 QV2
 *				- Displayed regulation on account grid
 *				- Added description for TIN Type and RFI Level
 *
 *	25-Dec-2017 Matira Thanetkulabut P0268205-88 DFT0079829
 *				- Display Error message
 *
 *	22-Jan-2018 Matira Thanetkulabut P0268206-125
 *				- Support Add, Refresh, Correct, Suppress, UnSuppress functionalities
 *
 *	05-Feb-2018 Matira Thanetkulabut P0268206-130 DFT0081020
 *				- Only Allowed to add an account with CRS regulation. 
 *
 *	27-Mar-2018 Matira Thanetkulabut P0268206-183 DFT0082940
 *				- Add flags for controlling button
 *
 *	05-Sep-2018 Umamaheswara Rao P0277568-261 R19.1 P0277784-75
 *				- Support Add, Modify, Delete for beneficiary payments
 *
 *	05-Oct-2018 Umamaheswara Rao P0277784-97 DFT0086561 P0277784-134 DFT0086559 19.1 QV1
 *				- Support PayType description and RFI Domicile for beneficiary payments
 *  
 *  09-Oct-2018 Umamaheswara Rao P0277786-25 R19.2
 *  		    - Support Admin and More functionalities 
 *
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 720;
	var _layoutWidth = 750;

	// **** buttons ****
	var _buttons = {	
		searchBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,handler: function(){_controller.doSearch("reload",false,null);}
		})
		,moreBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['More']
			,disabled: true
			,handler: function(){_controller.doMore("reload",true,null);}		
		})
		,addBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Add']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.openPopup("addAcct");}
		})
		,refreshBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Refresh']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.doAction("refresh");}
		})
		,correctBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Correct']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.doAction("correct");}
		})
		,supBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Suppress']
			,style: "margin-right: 5px"
			,disabled: true
			,handler: function(){_controller.doAction("suppress");}
		})
	}
	
	// **** fields ****
	var _fields = {		
		acctFld: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['Account']
			,width: 120
			,allowDecimals: false
			,tabIndex: 4
		})
		,acctTypeFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['AcctType']
			,width: 100
			,editable: true
			,listeners:{}
			,tabIndex: 5
		})
		,statFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['Status']
			,width: 135
			,editable: true
			,listeners:{}
			,tabIndex: 6
		})
		,regulationFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['Regulation']
			,width: 120
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
			,width: 135
			,editable: true
			,allowBlank: true
			,tabIndex: 3
		})	
		,reportingYearFld: new DesktopWeb.Controls.SMVComboBox(
		{
			fieldLabel: _translationMap['ReportingYear']
			,width: 100
			,editable: true
			,allowBlank: false	
			,tabIndex: 2
		})
	}
	
	// **** grids ****
	var _grids = {
		acct: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 20
			,autoScroll: true
			,height: 110
			,store: new Ext.data.XmlStore({
				record: 'regExtrAcct'
				,fields: ['errMsg', 'regulation', 'account', 'acctType', 'acctStat', 'acctRecordType', 'acctRecordID', 'acctRecordStat', 'correctedID', 'isEnableCor', 'isEnableRef', 'isEnableAdd', 'isEnableSup', {name: 'regExtrAcctUUID', mapping: '@regExtrAcctUUID'}]
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['correctedID'] = (record.data['correctedID'] == 0 ? "": record.data['correctedID']);
						});	
						store.fireEvent('datachanged', store);
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.setSelected("acct",record)
						}
					}
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
					,{header: _translationMap['Regulation'], dataIndex: 'regulation', width: 90,
						renderer: function(value){ return (_controller.getDesc('regulations', value))}}
					,{header: _translationMap['Account'], dataIndex: 'account', width: 100}
					,{header: _translationMap['AcctType'], dataIndex: 'acctType', width: 80,
						renderer: function(value){ return (_controller.getDesc('acctType', value))}}
					,{header: _translationMap['AcctStat'], dataIndex: 'acctStat', width: 90,
						renderer: function(value){ return (_controller.getDesc('acctStat', value))}}
					,{header: _translationMap['RecType'], dataIndex: 'acctRecordType', width: 80,
						renderer: function(value){ return (_controller.getDesc('acctRecordType', value))}}
					,{header: _translationMap['RecID'], dataIndex: 'acctRecordID', width: 60}
					,{header: _translationMap['AcctRecordStat'], dataIndex: 'acctRecordStat', width: 80,
						renderer: function(value){ return (_controller.getDesc('acctRecordStat', value))}}
					,{header: _translationMap['CorrectedRecID'], dataIndex: 'correctedID', width: 100}
					
				]
			})
		})
		,acctEnt: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 20		
			,autoScroll: true
			,height: 150
			,store: new Ext.data.XmlStore({
				record: 'regExtrEntity'
				,fields: ['errMsg','entityID', 'entityType', 'entityName', 'actHldTypeCode', 'ctrlPersTypeCode', 'recordType', 'entRecordStat', {name: 'regExtrEntityUUID', mapping: '@regExtrEntityUUID'}]
				,listeners: {
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.setSelected("acctEnt",record)
						}
					}
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
							return _controller.getDisplayNumberWithError('entity', val, record);
						}}
					,{header: _translationMap['EntityID'], dataIndex: 'entityID', width: 100}
					,{header: _translationMap['EntityType'], dataIndex: 'entityType', width: 120,
						renderer: function(value){ return (_controller.getDesc('entityType', value))}}
					,{header: _translationMap['Name'], dataIndex: 'entityName', width: 120}
					,{header: _translationMap['CRS100'], dataIndex: 'actHldTypeCode', width: 90,
						renderer: function(value){ return (_controller.getDesc('CRS100', value))}}
					,{header: _translationMap['CRS800'], dataIndex: 'ctrlPersTypeCode', width: 90,
						renderer: function(value){ return (_controller.getDesc('CRS800', value))}}
					,{header: _translationMap['CorrectionType'], dataIndex: 'recordType', width: 80,
						renderer: function(value){ return (_controller.getDesc('recordType', value))}}
					,{header: _translationMap['AcctRecordStat'], dataIndex: 'entRecordStat', width: 80,
						renderer: function(value){ return (_controller.getDesc('entRecordStat', value))}}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Payment']
					,itemId: 'paymentBtn'
					,disabled: true
					,handler: function(){
						_controller.loadBenPymt();
						}
				})
			]
		})
		,taxPayerJuris: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 20
			,autoScroll: true
			,height: 110
			,store: new Ext.data.XmlStore({
				record: 'regExtrJuris'
				,fields: ['errMsg','TIN', 'taxResCntryCode', 'taxPayerStatus', 'TINIssuedCntry', 'noTINReasonCode', 'TINType', {name: 'regExtrJurisUUID', mapping: '@regExtrJurisUUID'}]
				,listeners: {
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [
					{id: 'errMsg', width: 25,
						renderer: function(val, metaData, record){
							return _controller.getDisplayNumberWithError('juris', val, record);
						}}
					,{header: _translationMap['TaxRes'], dataIndex: 'taxResCntryCode', width: 100,
						renderer: function(value){ return (_controller.getDesc('taxResCntryCode', value))}}
					,{header: _translationMap['TaxPayerStat'], dataIndex: 'taxPayerStatus', width: 120,
						renderer: function(value){ return (_controller.getDesc('taxPayerStatus', value))}}
						,{header: _translationMap['TINType'], dataIndex: 'TINType', width: 80,
						renderer: function(value){ return (_controller.getDesc('TINType', value))}}
					,{header: _translationMap['TINIssuedCntry'], dataIndex: 'TINIssuedCntry', width: 100,
						renderer: function(value){ return (_controller.getDesc('taxResCntryCode', value))}}
					,{header: _translationMap['TaxIdenNum'], dataIndex: 'TIN', width: 150}
					,{header: _translationMap['NoTIN'], dataIndex: 'noTINReasonCode', width: 130,
						renderer: function(value){ return (_controller.getDesc('noTINReasonCode', value))}}
				]
			})
		})
		,beneficiaryPymtGrid: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 30
			,autoScroll: true
			,height: 200
			,store: new Ext.data.XmlStore({
				record: 'payEntityItem'
				,fields: ['errMsg','FILevel', 'FICode', 'FIName', 'payType', 'PayAmount', 'payCurrency', 'domicileCntry', 'payRecType', 'regExtrAmtUUID','allowMod','allowDel', 'userName', 'processDate', 'modUser', 'modDate']
				,listeners: {
					load: function(store, record)
					{	
						_controller.handleBenPaymentBtns(record[0]);
					}
				}			
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.handleBenPaymentBtns(record);
						}
					}
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
						return _controller.getDisplayNumberWithError('PayAmount', val, record);
						}}
					,{header: _translationMap['RFILevel'], dataIndex: 'FILevel', width: 80,
						renderer: function(value){ return (_controller.getDesc('FILevel', value))}}
					,{header: _translationMap['RFICode'], dataIndex: 'FICode', width: 60}
					,{header: _translationMap['Name'], dataIndex: 'FIName', width: 170}
					,{header: _translationMap['Domicile'], dataIndex: 'domicileCntry', width: 80,
						renderer: function(value){ return (_controller.getDesc('taxResCntryCode', value))}}
					,{header: _translationMap['PayType'], dataIndex: 'payType', width: 80,
						renderer: function(value){ return (_controller.getDesc('amountType', value))}}
					,{header: _translationMap['Amount'], dataIndex: 'PayAmount', width: 80}
					,{header: _translationMap['Curr'], dataIndex: 'payCurrency', width: 60}
					,{header: _translationMap['CorrectionType'], dataIndex: 'payRecType', width: 60}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Add']
					,itemId: 'addBtn'
					,handler: function() {
						_controller.openPaymentPopup(_controller.ADD);
					}
				})		
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Modify']
					,itemId: 'modBtn'
					,disabled: true
					,handler: function() {
						_controller.openPaymentPopup(_controller.MOD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Delete']
					,itemId: 'delBtn'
					,disabled: true
					,handler: function() {
						_controller.openPaymentPopup(_controller.DEL);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Admin']
					,itemId: 'adminBtn'
					,disabled: true
					,handler: function() {
						_controller.openAdminPopup();
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['More']
					,itemId: 'morePaymentBtn'
					,handler: function() {
						_controller.fetchBenPymtData(true);
					}
				})
			]
		})
		,balNPaym: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 20
			,autoScroll: true
			,height: 120
			,store: new Ext.data.XmlStore({
				record: 'regExtrAmt'
				,fields: ['errMsg','FILevel', 'FICode', 'FIName', 'amountType', 'amount', 'currency', 'cntryCode', 'recordType', {name: 'regExtrAmtUUID', mapping: '@regExtrAmtUUID'}]
				,listeners: {
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [
					{id: 'errMsg', width: 25,
						renderer: function(val, metaData, record){
							return _controller.getDisplayNumberWithError('amount', val, record);
						}}
					,{header: _translationMap['RFILevel'], dataIndex: 'FILevel', width: 60,
						renderer: function(value){ return (_controller.getDesc('FILevel', value))}}
					,{header: _translationMap['RFICode'], dataIndex: 'FICode', width: 60}
					,{header: _translationMap['Name'], dataIndex: 'FIName', width: 120}
					,{header: _translationMap['Domicile'], dataIndex: 'cntryCode', width: 110,
						renderer: function(value){ return (_controller.getDesc('taxResCntryCode', value))}}
					,{header: _translationMap['Amount'] + " " + _translationMap['Type'], dataIndex: 'amountType', width: 100,
						renderer: function(value){ return (_controller.getDesc('amountType', value))}}
					,{header: _translationMap['Amount'], dataIndex: 'amount', width: 90}
					,{header: _translationMap['Curr'], dataIndex: 'currency', width: 60}
					,{header: _translationMap['CorrectionType'], dataIndex: 'recordType', width: 80,
						renderer: function(value){ return (_controller.getDesc('recordType', value))}}
				]
			})
		})
	}
	
	// **** popups ****
	var _popups = {
		addAcct: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 310
			,closeAction: 'hide'
			,modal: true
			,autoHeight: true
			,defaults: {border: false}
			,bodyStyle: 'padding:4px'
			,items:[{
				layout: 'form'
				,labelWidth: 110
				,items: [
					new DesktopWeb.Controls.NumberField({
						itemId: 'filReqAccountNum'
						,fieldLabel: _translationMap['Account']
						,width: 150
						,allowBlank: false
						,allowDecimals: false
					})
					,new DesktopWeb.Controls.SMVComboBox({
						itemId: 'filReqRegulation'
						,fieldLabel: _translationMap['Regulation']
						,width: 150
						,allowBlank: false
						,disabled: true
						,listeners:{
							select: function(){_controller.loadDropdown(this.getValue(),"popup");}
						}
					})
					,new DesktopWeb.Controls.SMVComboBox({
						itemId: 'filReqReportingYear'
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
				]
			}]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if(_popups['addAcct'].isValid()){
							_controller.addAccount("valAddAcct", _popups['addAcct'].getData());
						}
					}
				})
			]
			,init: function()
			{
				var popup = _popups['addAcct'];
				popup.setTitle(_translationMap['Add']);
				popup.clearAllFields();
			}
			,getData: function()
			{
				var popup = _popups['addAcct'];
				var data = {};
				var runMode = popup.action;
				
				data["runMode"] = runMode;
				data["account"] = this.getField('filReqAccountNum').getValue();
				data["reportingYear"] = this.getField('filReqReportingYear').getValue();
				data["regulation"] = this.getField('filReqRegulation').getValue();
				data["domicileCntry"] = this.getField('filReqRFIDomicile').getValue();
				
				return data;
			}
		})
		,beneficiaryPymtPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,autoScroll: true
			,width: _layoutWidth
			,height: 300
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
			,bodyStyle: 'padding:4px'
			,defaults: {border:true}
			,title: _translationMap['BeneficiaryPayments']
			,items: [
				{
					itemId: 'header'
					,layout: 'column'
					,style: 'padding-top:8px;'
					,defaults: {border: false}
					,items: [
						{
							layout: 'form'
							,columnWidth: 0.29
							,labelWidth: 60
							,style: 'padding-top:8px;padding-left:4px;'
							,items: [ 
								new DesktopWeb.Controls.NumberField({
									itemId: 'Account'
									,fieldLabel: _translationMap['Account']
									,width: 120
									,allowBlank: false
									,allowDecimals : false
									,disabled: true
								}) 
							]
						}
						,{
							layout: 'form'
							,columnWidth: 0.29
							,labelWidth: 60
							,style: 'padding-top:8px;'
							,items: [ 
								new DesktopWeb.Controls.NumberField({
									itemId: 'entityID'
									,fieldLabel: _translationMap['EntityID']
									,width: 120
									,allowBlank: false
									,disabled: true
								}) 
							]
						}
						,{
							layout: 'form'
							,columnWidth: 0.42
							,labelWidth: 75
							,style: 'padding-top:8px;'
							,items: [ 
								new DesktopWeb.Controls.TextField({
									itemId: 'entityTypeTest'
									,fieldLabel: _translationMap['EntityType']
									,width: 215
									,allowBlank: false
									,disabled: true
								}) 
							]
						} 
					]
				}
		    	,{
		    		xtype: 'fieldset'
		    		,title: _translationMap['PaymentByRFI']
					,style: 'padding-top:15px'
					,defaults: {border: false}
					,items: [{
							layout: 'column'
							,items: [ _grids['beneficiaryPymtGrid'] ]
					}]
				} 
		    ]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function() {						
						_popups['beneficiaryPymtPopup'].hide();
					}
				}) 
			]
		})
		,payPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 550
			,closeAction: 'hide'
			,modal: true
			,autoScroll: true			
			,autoHeight: true
			,defaults: {border: false}
			,bodyStyle: 'padding:4px'
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
			    	,style: 'text-align:center;font-weight:bold; font-size:12px; padding:10px;' 
				}
				,{				
					style: 'padding-bottom:5px;padding-top:5px;'
					,defaults: {border: false}
					,layout: 'form'
					,items: [
						{
							layout: 'column'					
							,defaults: {border: false}
							,labelWidth: 90
							,items: [ 
								{
									layout: 'form'
									,columnWidth: 0.50
									,labelWidth: 90
									,style: 'padding-left:4px;'
									,items: [
										new DesktopWeb.Controls.NumberField({
											itemId: 'payPopupAccountNum'
											,fieldLabel: _translationMap['Account']
											,width: 150
											,allowBlank: false
										}) 
									]
								}
								,{
									layout: 'form'
									,columnWidth: 0.50
									,labelWidth: 90
									,items: [
										new DesktopWeb.Controls.NumberField({
											itemId : 'payPopupEntity'
											,fieldLabel : _translationMap['EntityID']
											,width : 150
											,allowBlank : false
										}) 
									]
								}
							] 
						} 
						,{
							layout: 'form'					
							,labelWidth: 90
							,style: 'padding-left:4px;'
							,items: [
								new DesktopWeb.Controls.TextField({
									itemId: 'payPopupEntityType'
									,fieldLabel: _translationMap['EntityType']
									,width : 410
									,allowBlank : false
								}) 
							]
						}
					]
				}
				,{
					layout: 'form'
					,columnWidth: 0.50
					,labelWidth: 90
					,style: 'borderTop : solid 2px lightgrey ;padding-top:10px;padding-left:4px '
					,defaults: {border: false}
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'payPopupRFILevel'
							,fieldLabel: _translationMap['RFILevel']
							,width: 220
							,allowBlank: false
							,listeners: {
								select: function(){_popups['payPopup'].getField('payPopupRFILevelDesc').clearValue ()}
						   		,click: function(){_popups['payPopup'].getField('payPopupRFILevelDesc').clearValue ()}
							}
						})
						,new DesktopWeb.Controls.SuggestField({
							fieldLabel: _translationMap['RFIDescription']
							,itemId : 'payPopupRFILevelDesc'					
							,smartview: 'RFISearch'
							,addtlSearchParams: [
							    {name: 'FILevel', valueFn: function(){return _popups['payPopup'].getField('payPopupRFILevel').getValue()}}
								,{name: 'complyRule', valueFn: function(){return _grids['acct'].getSelectedRecord().data['regulation']}}
								,{name: 'RFIDomicile', valueFn: function(){return _fields['rfiDomicileFld'].getValue()}}
							]
							,fields: ['displayValue','FICode']
							,valueField: 'FICode'
							,displayField: 'displayValue'
							,width: 410
							,allowBlank: false
						})
					]								
				}
				,{	
				    style: 'padding-top:10px;padding-bottom:10px;'
					,defaults: {border: true}
					,layout: 'form'
					,items: [
						{ 							
							defaults: {border: false}						
							,layout: 'form'					
							,items: [
								{
									layout: 'form'
									,defaults: {border: false}					
									,labelWidth : 90
									,style:'padding-left:4px;'
									,items: [{	
										layout: 'form'	
										,style: 'padding-top:8px;'
										,labelWidth: 90
										,items: [ 
											new DesktopWeb.Controls.SMVComboBox({
												itemId: 'payPopupPaymentType'
												,fieldLabel: _translationMap['PayType']
												,width: 410
												,allowBlank: false
											}) 
										]
									}] 
								} 
								,{
									layout: 'column'						
									,defaults: {border: false}	
									,items: [{
											layout: 'form'
											,columnWidth: 0.50									
											,labelWidth: 90
											,style:'padding-left:4px;'
											,items: [
												new DesktopWeb.Controls.NumberField({
													fieldLabel: _translationMap['Amount']
													,itemId: 'payPopupAmount'
													,allowBlank: false
													,allowNegative: false								
													,decimalPrecision: 2
													,minValue: 0.01
													,maxLength: 17										
												})
											]
										}
										,{
											layout: 'form'
											,columnWidth: 0.50
											,style: 'padding-left:1px;'
											,labelWidth: 90
											,items: [ 
												new DesktopWeb.Controls.SMVComboBox({
													itemId: 'payPopupCurrency'
													,fieldLabel: _translationMap['Currency']
													,width: 150
													,allowBlank: false
												}) 
											]
										}
									]
								}
							]
						}
					]		
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
				itemId: 'okBtn'
				,text: _translationMap['OK']
				,handler: function() {
					if(_popups['payPopup'].isValid()) {
						_controller.doCommitBenPymt(_popups['payPopup'].getData(_popups['payPopup'].action),_popups['payPopup'].action);
					}
				}
			  })
				,new DesktopWeb.Controls.ActionButton({
				itemId: 'canBtn'
				,text: _translationMap['Cancel']
				,handler: function() {
					_popups['payPopup'].getField('payPopupAmount').setValue("");
					_popups['payPopup'].hide();
				}
			 })
			]
			,init: function(action) {
				var popup = _popups['payPopup'];
				this.action = action;
				switch(action) {
					case _controller.ADD:
					{
						popup.get(0).hide();
						popup.setTitle( _translationMap['BeneficiaryPayment'] + ' - ' + _translationMap['Add']);
						popup.getField('payPopupAmount').clearField();
                        popup.getField('payPopupRFILevelDesc').clearField();
						popup.populate(action);						
						break;
					}
					case _controller.MOD:
					{
						popup.get(0).hide();
						popup.setTitle( _translationMap['BeneficiaryPayment'] + ' - ' +_translationMap['Modify']);
						popup.populate(action);						
						break;
					}
					case _controller.DEL:
					{
						popup.get(0).show();
						popup.setTitle( _translationMap['BeneficiaryPayment'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
					}
				}
			}
			,getData: function(action) {
				var popup = _popups['payPopup'];
				var data = {};
				data["runMode"] = action;
				if (action == _controller.ADD) {
					data["regExtrAmtUUId"] = _controller.getEntityPayAmtUUID();
				} else {
					data["regExtrAmtUUId"] = _grids['beneficiaryPymtGrid'].getSelectedRecord().data['regExtrAmtUUID'];
				}
				data["payPopupAccountNum"] = this.getField('payPopupAccountNum').getValue();
				data["payPopupEntity"] = this.getField('payPopupEntity').getValue();
				data["payPopupEntityType"] = this.getField('payPopupEntityType').getValue();
				data["payPopupRFILevel"] = this.getField('payPopupRFILevel').getValue();
				data["payPopupRFILevelDesc"] = this.getField('payPopupRFILevelDesc').getValue();
				data["payPopupPaymentType"] = this.getField('payPopupPaymentType').getValue();
				data["payPopupAmount"] = this.getField('payPopupAmount').getValue();
				data["payPopupCurrency"] = this.getField('payPopupCurrency').getValue();
				
				return data;
			}
			,populate: function(action) {
					var popup = _popups['payPopup'];
					popup.enableAllFields();
					popup.clearAllFields();
					switch(action) {
					case _controller.ADD: {
						popup.getField('payPopupAccountNum').setValue(_grids['acct'].getSelectedRecord().data['account']);
						popup.getField('payPopupEntity').setValue(_grids['acctEnt'].getSelectedRecord().data['entityID']);
						popup.getField('payPopupEntityType').setValue(_controller.getDesc('entityType', _grids['acctEnt'].getSelectedRecord().data['entityType']));
						_controller.loadDropdownRFIDescription();		
						_controller.enablePayPopupFields(popup);
						break;
					}
					case _controller.MOD: {
						popup.getField('payPopupAccountNum').setValue(_grids['acct'].getSelectedRecord().data['account']);
						popup.getField('payPopupEntity').setValue(_grids['acctEnt'].getSelectedRecord().data['entityID']);
						popup.getField('payPopupEntityType').setValue(_controller.getDesc('entityType', _grids['acctEnt'].getSelectedRecord().data['entityType']));
						_controller.loadDropdownRFIDescription();
						popup.getField('payPopupCurrency').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['payCurrency']);
						popup.getField('payPopupPaymentType').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['payType']);
						if (_grids['beneficiaryPymtGrid'].getSelectedRecord()!= null) {
						    popup.getField('payPopupAmount').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['PayAmount']);
						    popup.getField('payPopupRFILevelDesc').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['FICode']);
						    popup.getField('payPopupRFILevel').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['FILevel']);
						}
						_controller.disablePayPopupFields(popup);
						popup.getField('payPopupAmount').enableField();
						break;
					}
					case _controller.DEL: {
						popup.getField('payPopupAccountNum').setValue(_grids['acct'].getSelectedRecord().data['account']);
						popup.getField('payPopupEntity').setValue(_grids['acctEnt'].getSelectedRecord().data['entityID']);
						popup.getField('payPopupEntityType').setValue(_controller.getDesc('entityType', _grids['acctEnt'].getSelectedRecord().data['entityType']));
						_controller.loadDropdownRFIDescription();	
						popup.getField('payPopupCurrency').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['payCurrency']);
						popup.getField('payPopupPaymentType').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['payType']);
						if(_grids['beneficiaryPymtGrid'].getSelectedRecord() != null) {
							popup.getField('payPopupAmount').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['PayAmount']);
							popup.getField('payPopupRFILevelDesc').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['FICode']);
							popup.getField('payPopupRFILevel').setValue(_grids['beneficiaryPymtGrid'].getSelectedRecord().data['FILevel']);
						}
						_controller.disablePayPopupFields(popup);
					}
				 }
			}
			,isValid: function() {
				var popup = _popups['payPopup'];
				var valid = true;
				valid = popup.getField('payPopupAmount').isValid() && valid;
				valid = popup.getField('payPopupRFILevelDesc').isValid() && valid;
				
				if(popup.getField('payPopupAmount').getValue() < 0) {
					popup.getField('payPopupAmount').markInvalid( _translationMap['invalidMinAmount']);
					valid = false;
				}
				return valid;
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
                    			})
                    		]
                		}
                	]
               }
            ]
            ,buttons: [
                new DesktopWeb.Controls.ActionButton({
                    text: _translationMap['OK']
                    ,handler: function() {
                        _popups['admin'].hide();
                    }
                })
            ]
            ,init: function(title, data) {
                this.setTitle(title);
                this.getField('procDate').setValue(data['procDate']);
                this.getField('modDate').setValue(data['modDate']);
                this.getField('userName').setValue(data['userName']);
                this.getField('modUser').setValue(data['modUser']);
            }
        })
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
                ,style: 'padding-left:5px; padding-right:5px;'
				,items: [
				{
					itemId: 'header'
					,layout: 'column'
					,items: [
					{
						layout: 'form'
						,columnWidth: 0.28
						,labelWidth: 60
						,items: [
							_fields['regulationFld']
							,_fields['acctFld']
						]
					}
					,{	
						layout: 'form'
						,columnWidth: 0.30
						,labelWidth: 90
						,items: [
							_fields['reportingYearFld']
							,_fields['acctTypeFld']
						]
					}
					,{		
						layout: 'form'
						,columnWidth: 0.32
						,labelWidth: 75
						,items: [
							_fields['rfiDomicileFld']
							,_fields['statFld']
						]
					}
					,{		
						layout: 'form'
						,columnWidth: 0.1
						,items: [
							_buttons['searchBtn']
						]
					}
				]}
				,{
					xtype: 'fieldset'
					,title: _translationMap['Accts']
					,items: [
					{
						layout: 'column'
						,items: [_grids['acct']]
					}
					,{
						layout: 'column'
						,style: 'padding-top:5px;'
						,items: [
						{
							layout: 'form'
							,columnWidth: 0.53
							,items :[
							]
						}
						,{
							layout: 'column'
							,columnWidth: 0.47
							,items :[
								_buttons['addBtn']
								,_buttons['refreshBtn']
								,_buttons['correctBtn']
								,_buttons['supBtn']
								,_buttons['moreBtn']
							]
						}]      
					}]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['AcctEnts']	
					,items: [
					{
						layout: 'column'
						,items: [_grids['acctEnt']]
					}]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['TaxPayerJuris']
					,items: [
					{
						layout: 'column'
						,items: [_grids['taxPayerJuris']]
					}]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['BalNPays']
					,items: [
					{
						layout: 'column'
						,items: [_grids['balNPaym']]
					}]
				}
				]
			}
		)
		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					_controller.goToScreen();
				}
			})
		]			
	}
}
