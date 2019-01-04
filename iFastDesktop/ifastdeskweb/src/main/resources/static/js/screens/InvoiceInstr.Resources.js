/*
 * Procedure: InvoiceInstr.Resources.js
 *
 * Purpose  : Invoice Instruction screens manage invoice information data			  
 *             
 * Notes    : Open screens by Menu -> MF and MFR Maintenance -> Invoice Instruction
 *							  Menu -> System Maintenance -> Holding Company -> Invoice Instructions
 *
 * History  : 
 *	
 *    5 Mar 2013 Supareuk Sukjaitham PETP0206635 FN01 MFR MFI Enhancments
 *          - Created
 *
 *    2 May 2013 Supareuk Sukjaitham PETP0206635 FN01 IN3318278
 *          - Fixed issues for some validation of mandatory field, pre-populated field and error of compositefield
 *
 *    21 May 2013 Supareuk Sukjaitham PETP0206635 FN01 IN3331655
 *          - Expand screen
 *          - Wrapping text under BillingEntity group
 *
 *    27 May 2013 Pannarasi Wongpakdee PETP0206635 FN01 T53618 IN3336672
 *          - Call doValidateCommitScreen function when updatesFlag
 *
 *      23-Jun-2013 S. Sukjaitham   PETP0206635 FN01 T53755 IN3346035
 *          - Correct an input parameter name from holdingCompanyCode to holdingEntityCode
 *
 *    10 Jul 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3359189 T53824
 *          - Update width of city and province
 *
 *    05 Aug 2013 Gomoot Thawornwachirakun PETP0206635 FN01 DFT0012847 T53963
 *          - Add ability to set dynamic mandatory PSTL field on selected country
 *          - Remove allowBlank from PSTL field
 *
 *    11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter 
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	
	// content dimensions
	var _layoutHeight = 700;
	var _layoutWidth = 750;
	var _layoutHeadingControlWidth = 250;
	var _layoutLabelWidth = 125;
	var _layoutControlWidth = 230;
	var _layoutLabelDetlWidth = 102;
	var _layoutControlDetlWidth = 200;
	var _layoutControlDetlWidth2 = 185;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// **** fields ****
	var _fields = {
		holdingCompanySrch: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['HoldingCompany']
			,width: _layoutHeadingControlWidth	
			,smartview: 'holdingCompanySearch'
			,addtlSearchParams: [{name: 'coUsage', valueFn: function(){return 'MF'}}]
			,fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'assetAggrMethod', 'displayValue']
			,valueField: 'holdingCompanyCode'
			,displayField: 'displayValue'
			,listeners: {
				focus: function(){
					_controller.doSrchValid('focus');
				}
				,validator: function(){
					_controller.doSrchValid();
				}
			}
		})
		,invoiceSrch: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['InvoiceLabel']
			,width: _layoutHeadingControlWidth		
			,smartview: 'invoiceInstrSearch'				
			,fields: ['billInstrID', 'billInstrCode', 'invoiceName', 'displayValue']
			,valueField: 'billInstrCode'
			,displayField: 'displayValue'
			,addtlSearchParams: [{name: 'holdingEntityCode', 
				valueFn: function()
				{
					return _fields['holdingCompanySrch'].getValue() != '' ? _fields['holdingCompanySrch'].getValue() : '' ;											
				}
			}] 			
			,listeners: {
				focus: function(){
					_controller.doSrchValid('focus');
				}
				,validator: function(){
					_controller.doSrchValid();
				}
			}	
		})
		,optSelectAll: new DesktopWeb.Controls.Radio({
			boxLabel: _translationMap['All']
			,width: 40
			,name:'filterBy'
			,handler: function() {_controller.doSrchCheck();}
		})
		,optSelectAsOfDate: new DesktopWeb.Controls.Radio({
			boxLabel: _translationMap['EffectiveAsOf']
			,width: 100
			,name:'filterBy'
			,handler: function() {_controller.doSrchCheck();}
		})
		,asOfDate: new DesktopWeb.Controls.DateField({
			fieldLabel: ""
			,allowBlank: false
			,width: 100
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
		})
		
		/***** Billing Entity *****/
		,invoiceName1: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['InvoiceName1']
			,width: _layoutControlWidth
		})
		,deliveryName1: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['DeliveryName']
			,width: _layoutControlWidth
		})
		,deliveryName2: new DesktopWeb.Controls.Label({
			fieldLabel: " "
			,labelSeparator: ""
			,width: _layoutControlWidth
		})
		,addr1: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Address']
			,width: _layoutControlWidth
		})
		,addr2: new DesktopWeb.Controls.Label({
			fieldLabel: " "
			,labelSeparator: ""
			,width: _layoutControlWidth
		})
		,addr3: new DesktopWeb.Controls.Label({
			fieldLabel: " "
			,labelSeparator: ""
			,width: _layoutControlWidth
		})
		,addr4: new DesktopWeb.Controls.Label({
			fieldLabel: " "
			,labelSeparator: ""
			,width: _layoutControlWidth
		})
		,city: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['City']
			,width: _layoutControlWidth
		})
		,country: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Country']
			,width: _layoutControlWidth
		})
		,pstl: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['PSTL']
			,width: _layoutControlWidth
		})
		
		/***** Billing Details *****/
		,frequency: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Frequency']
			,width: _layoutControlWidth
		})
		,paymentOptn: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['PaymentOption']
			,width: _layoutControlWidth
		})
		,termOfPayment: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TermOfPayment']
			,width: _layoutControlWidth
		})
		,currency: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Currency']
			,width: _layoutControlWidth
		})
		,taxApply: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TaxApply']
			,width: _layoutControlWidth
		})
		,language: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Language']
			,width: _layoutControlWidth
		})
		,supplementReq: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['SupplementReq']
			,width: _layoutControlWidth
		})
		,brandingType: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['BrandingType']
			,width: _layoutControlWidth
		})
	}
	
	// **** _buttons ****
	var _buttons = {
		cmdSearch: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			, handler: function() {_controller.doSearch(false);}	
		})
		,cmdInvoiceInstrAdd: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Add']
			, handler: function(){_controller.openActionPopup( 'frmInvoiceDetl', _controller.ADD);}
		})
		, cmdInvoiceInstrMod: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Modify']
			, handler: function(){_controller.openActionPopup( 'frmInvoiceDetl', _controller.MOD);}
		})
		, cmdInvoiceInstrDel: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Delete']
			, handler: function(){_controller.openActionPopup( 'frmInvoiceDetl', _controller.DEL);}
		})
		, cmdInvoiceInstrMore: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['More']
			,handler: function(){_controller.doSearch(true, null);}
		})
		,cmdInvoiceInstrHistory: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Historical']
			,handler: function(){_controller.openHistoryPopup();}
		})
		,cmdInvoiceInstrAdmin: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Admin']
			,handler: function(){_controller.openAdminPopup();}	
		})
		,cmdInvoiceDetlSubmit: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['OK']
			, handler: function(){
				var tempdata   = _popups['frmInvoiceDetl'].getData(_popups['frmInvoiceDetl'].action);
				var isValid    = _popups['frmInvoiceDetl'].isValid();
				var isValidate = _controller.doValidatePopup(_popups['frmInvoiceDetl'].action, tempdata);
				
				if (isValid && isValidate){
					_controller.doSave(_popups['frmInvoiceDetl'].action, tempdata)
				}
			}
		})
		, cmdInvoiceDetlCancel: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Cancel']
			, handler: function(){
				_controller.clearPopupInfo();
				_popups['frmInvoiceDetl'].hide();
			}
		})
	}
	
	// **** grids ****
	var _grids = {
		grdInvoiceInstr: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: _layoutWidth
				, style: "margin-top:15px;margin-bottom:5px;"
				, autoScroll: true
				, height: 200
				, autoExpandColumn: 'invoiceName'
				, store: new Ext.data.XmlStore(
					{
						record: 'InvoiceInstrDetl'
						,fields: ['billInstrID', 'holdingEntityDesc', 'holdingEntityCode','invoiceID','invoiceName',
								  'invoiceName2','frequency','deff','stopDate','runMode',
								  'errMsg','gridIndex','version', 'acctAsso',
								  'processDate','username','modDate','modUser'
								]
						, listeners: {
							load: function(store, records) {		
								Ext.each(records, function(record){
									record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
									record.data.stopDate    = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
									record.data.processDate = DesktopWeb.Util.getDateDisplayValue(record.data.processDate);
									record.data.modDate     = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
								});
						
								store.filterBy(function(record){
										return (record.data.runMode != _controller.DEL);										
									}
								)								
							}
						}
					}
				)
				
				,selModel: new Ext.grid.RowSelectionModel({					
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){_controller.updateContent();}
					}
				})
				
				, colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						, columns: [	
							{dataIndex: 'errMsg'
								, renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
								, width: 25
							}
							,{	header: _translationMap['HoldingCompany']
								,dataIndex: 'holdingEntityDesc'
								,width:100
								,renderer: function(val, metaData, record){return (record.data['holdingEntityCode'] + ' - ' + record.data['holdingEntityDesc'])}
							}
							, {header: _translationMap["InvoiceId"], dataIndex: 'invoiceID', width:100}
							, {id: 'invoiceName'
							   , header: _translationMap["InvoiceName"]
							   , dataIndex: 'invoiceName'
							   , renderer: function(val, metaData, record){
								    return (record.data['invoiceName'] + record.data['invoiceName2'])
							     } 
							}
							, {header: _translationMap['Frequency'], dataIndex: 'frequency'
								, renderer: function(val){
									return (_controller.getListDisplay('frequencies', val));
								}, width: 100}
							, {header: _translationMap['EffectiveDate'], dataIndex: 'deff', width:100}
							, {header: _translationMap['StopDate'], dataIndex: 'stopDate', width:100}
						]
					}
				)
				, buttons: [
					_buttons['cmdInvoiceInstrAdd']
					,_buttons['cmdInvoiceInstrMod']
					,_buttons['cmdInvoiceInstrDel']
					,_buttons['cmdInvoiceInstrMore']
					,_buttons['cmdInvoiceInstrAdmin']
					,_buttons['cmdInvoiceInstrHistory']
				]
			}
		)
	}
	
	// **** popups ****
	var _popups = {		
		frmInvoiceDetl: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,border: false
				,width: 715
				,closeAction: 'hide'
				,modal: true
				,defaults: {border: false}
				,items: [
					{
						xtype: 'fieldset'
						,border: true
						,title: _translationMap['InvoiceInformation']
						,style: 'margin-left:5px;margin-right:5px;margin-bottom:5px;margin-top:5px;'
						,defaults: {border: false,labelWidth:_layoutLabelDetlWidth}
						, items: [
							/*******************************
							 ***** Invoice Instruction *****
							 *******************************/
							{
								layout: 'column'
								,style: 'margin-left:5px;margin-right:5px;margin-top:5px;'
								,defaults: {border: false}
								,items: [
									{	columnWidth: 0.5
										,layout: 'form'
										,labelWidth: _layoutLabelDetlWidth
										,items: [
											new DesktopWeb.Controls.SuggestField({
												itemId: 'holdingCompanySrchDetl'
												,fieldLabel: _translationMap['HoldingCompany']
												,width: _layoutControlDetlWidth
												,smartview: 'holdingCompanySearch'
												,addtlSearchParams: [{name: 'coUsage', valueFn: function(){return 'MF'}}]
												,fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'assetAggrMethod', 'displayValue']
												,valueField: 'holdingCompanyCode'
												,displayField: 'displayValue'
												,allowBlank: false
											})
										]
									}
									,{	columnWidth: 0.5
										,layout: 'form'
										,labelWidth: _layoutLabelDetlWidth
										,items: [
											new DesktopWeb.Controls.TextField({
												itemId: 'invoiceSrchDetl'
												,fieldLabel: _translationMap['InvoiceId']
												,width: _layoutControlDetlWidth
												,maxLength: 10
												,allowBlank: false				
											})
										]
									}
								]
							}
							,{
								layout: 'column'
								,style: 'margin-left:5px;margin-right:5px'
								,defaults: {border: false}
								,items: [
									{	columnWidth: 0.5
										,layout: 'form'
										,labelWidth: _layoutLabelDetlWidth
										,items: [
											new DesktopWeb.Controls.TextField({
												itemId: 'invoiceName1Detl'
												,fieldLabel: _translationMap['InvoiceName1']
												,width: _layoutControlDetlWidth
												,maxLength: 60
												,allowBlank: false
											})
										]
									}
									,{	columnWidth: 0.5
										,layout: 'form'
										,labelWidth: _layoutLabelDetlWidth
										,items: [
											new DesktopWeb.Controls.DateField({
												itemId: 'effectiveDateDetl'
												,fieldLabel: _translationMap['EffectiveDate']
												,width: 105
												,allowBlank: false
												,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											})
										]
									}
								]
							}
							,{
								layout: 'column'
								,style: 'margin-left:5px;margin-right:5px'
								,defaults: {border: false}
								,items: [
									{	columnWidth: 0.5
										,layout: 'form'
										,labelWidth: _layoutLabelDetlWidth
										,items: [
											new DesktopWeb.Controls.TextField({
												itemId: 'invoiceName2Detl'
												,fieldLabel: " "
												,labelSeparator: ""
												,width: _layoutControlDetlWidth
												,maxLength: 60
												,allowBlank: true
											})
										]
									}
									,{	columnWidth: 0.5
										,layout: 'form'
										,labelWidth: _layoutLabelDetlWidth
										,items: [
											new DesktopWeb.Controls.DateField({
												itemId: 'stopDateDetl'
												,fieldLabel: _translationMap['StopDate']
												,width: 105
												,allowBlank: false
												,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											})
										]
									}
								]
							}

						]
					}
					,{
						layout: 'column'
						,style: 'margin-left:5px;margin-right:5px;margin-top:5px;'
						,defaults: {border: false}
						,items: [
							{	columnWidth: 0.5
								,layout: 'form'
								,defaults: {border: false, labelWidth:_layoutLabelDetlWidth}
								,items: [
									/**************************
									 ***** Billing Entity *****
									 **************************/
									{
									layout: 'column'
									, items: [
										{	
											columnWidth: 1
											,xtype: 'fieldset'
											,height: 335
											,style: 'margin-right:5px;'
											,title: _translationMap['BillingEntityTitle']
											,labelWidth: 100
											, items:[
													new DesktopWeb.Controls.TextField({
														itemId: 'deliveryName1Detl'
														,fieldLabel: _translationMap['DeliveryName']
														,width: _layoutControlDetlWidth
														,maxLength: 40
														,allowBlank: false
													})
													,new DesktopWeb.Controls.TextField({
														itemId: 'deliveryName2Detl'
														,fieldLabel: ""
														,width: _layoutControlDetlWidth
														,maxLength: 40
														,allowBlank: true
													})
													,new DesktopWeb.Controls.TextField({
														itemId: 'addr1Detl'
														,fieldLabel: _translationMap['Address']
														,width: _layoutControlDetlWidth
														,maxLength: 40
														,allowBlank: false
													})
													,new DesktopWeb.Controls.TextField({
														itemId: 'addr2Detl'
														,fieldLabel: ""
														,width: _layoutControlDetlWidth
														,maxLength: 40
														,allowBlank: true
													})
													,new DesktopWeb.Controls.TextField({
														itemId: 'addr3Detl'
														,fieldLabel: ""
														,width: _layoutControlDetlWidth
														,maxLength: 40
														,allowBlank: true
													})
													,new DesktopWeb.Controls.TextField({
														itemId: 'addr4Detl'
														,fieldLabel: ""
														,width: _layoutControlDetlWidth
														,maxLength: 40
														,allowBlank: true
													})
													,new DesktopWeb.Controls.TextField({
														itemId: 'cityDetl'
														,fieldLabel: _translationMap['City']
														,width: _layoutControlDetlWidth
														,maxLength: 30
														,allowBlank: false
													})
													,new DesktopWeb.Controls.ComboBox({
														itemId: 'countryDetl'
														,fieldLabel: _translationMap['Country']
														,width: _layoutControlDetlWidth
														,allowBlank: false
														,valueField: 'code'
														,displayField: 'value'
														,store: new Ext.data.XmlStore(
														{
															record: 'Element'
															,fields: ['code', 'value', 'requirePSTL']
														})
														,listeners: {
															select: function(combo, record, index){
																_popups['frmInvoiceDetl'].getField('pstlDetl').clearInvalid();
															}
														}
													})
													,new DesktopWeb.Controls.TextField({
														itemId: 'pstlDetl'
														,fieldLabel: _translationMap['PSTL']
														,width: 105
														,maxLength: 9
														,allowBlank: true
													})
											]
										}
									]
									}
								]
							}
							,{	columnWidth: 0.5
								,layout: 'form'
								,defaults: {border: false, labelWidth:_layoutLabelDetlWidth}
								,items: [
									/**************************
									 ***** Billing Details *****
									 **************************/
									{
									layout: 'column'
									, items: [
										{	
											columnWidth: 1
											,xtype: 'fieldset'
											,height: 300
											,title: _translationMap['BillingDetail']
											,labelWidth: _layoutLabelWidth
											,items: [
													new DesktopWeb.Controls.SMVComboBox({
														itemId: 'frequencyDetl'
														,fieldLabel: _translationMap['Frequency']
														,width: _layoutControlDetlWidth2
														,allowBlank: false
													})
													,new DesktopWeb.Controls.SMVComboBox({
														itemId: 'paymentOptnDetl'
														,fieldLabel: _translationMap['PaymentOption']
														,width: _layoutControlDetlWidth2
														,allowBlank: false
													})
													,{  xtype: 'compositefield'
														,itemId: 'paymentDetl'
														,combineErrors: true
														,width: 185
														,msgTarget: 'side'
														,fieldLabel: _translationMap['TermOfPayment']
														,items: [
															new DesktopWeb.Controls.NumberField({
																itemId: 'termOfPaymentDetl'
																,name: _translationMap['Termdays']
																,id: 'termOfPaymentDetl'
																,fieldLabel: ""
																,width: 55
																,allowDecimals: false
																,allowBlank: false
																,minValue: 1
																,allowNegative: false
															})
															,new DesktopWeb.Controls.SMVComboBox({
																itemId: 'termOfPaymentTypeDetl'
																,id: 'termOfPaymentTypeDetl'
																,name: _translationMap['TermdaysType']
																,fieldLabel: ""
																,width: 125
																,allowBlank: false
															})
														]
													}
													,new DesktopWeb.Controls.SMVComboBox({
														itemId: 'currencyDetl'
														,fieldLabel: _translationMap['Currency']
														,width: _layoutControlDetlWidth2
														,allowBlank: false
													})
													,new DesktopWeb.Controls.YesNoComboBox({
														itemId: 'taxApplyDetl'
														,fieldLabel: _translationMap['TaxApply']
														,width: _layoutControlDetlWidth2
														,allowBlank: false
													})
													,new DesktopWeb.Controls.SMVComboBox({
														itemId: 'languageDetl'
														,fieldLabel: _translationMap['Language']
														,width: _layoutControlDetlWidth2
														,allowBlank: false
													})
													,new DesktopWeb.Controls.YesNoComboBox({
														itemId: 'supplementReqDetl'
														,fieldLabel: _translationMap['SupplementReq']
														,width: _layoutControlDetlWidth2
														,allowBlank: false
													})
													,new DesktopWeb.Controls.SMVComboBox({
														itemId: 'brandingTypeDetl'
														,fieldLabel: _translationMap['BrandingType']
														,width: _layoutControlDetlWidth2
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
				, buttons: [
					_buttons['cmdInvoiceDetlSubmit']
					, _buttons['cmdInvoiceDetlCancel']
				]
				
				,init: function(action){
					this.action = action;	
					switch(action){
						case _controller.ADD:{
							this.setTitle(_translationMap['InvoiceInstrDetl'] + " - " + _translationMap['Add']);
							break;
						}
						case _controller.MOD:{
							this.setTitle(_translationMap['InvoiceInstrDetl'] + " - " + _translationMap['Modify']);
							break;
						}
						case _controller.DEL:{
							this.setTitle(_translationMap['InvoiceInstrDetl'] + " - " + _translationMap['Delete']);
							break;
						}
					}
				}
				
				, getData: function(action){									
					var data = {};
					data['errMsg'] = "";
					data['holdingEntityCode'] = this.getField('holdingCompanySrchDetl').getValue();
					data['invoiceID'] = this.getField('invoiceSrchDetl').getValue();
					data['deff'] = this.getField('effectiveDateDetl').getValue();
					data['stopDate'] = this.getField('stopDateDetl').getValue()
					data['invoiceName'] = this.getField('invoiceName1Detl').getValue();
					data['invoiceName2'] = this.getField('invoiceName2Detl').getValue();
					
					data['delivName1'] = this.getField('deliveryName1Detl').getValue();
					data['delivName2'] = this.getField('deliveryName2Detl').getValue();
					data['addrLine1'] = this.getField('addr1Detl').getValue();
					data['addrLine2'] = this.getField('addr2Detl').getValue();
					data['addrLine3'] = this.getField('addr3Detl').getValue();
					data['addrLine4'] = this.getField('addr4Detl').getValue();
					data['city'] = this.getField('cityDetl').getValue();
					data['provCountry'] = this.getField('countryDetl').getValue();
					data['pstl'] = this.getField('pstlDetl').getValue().trim();
					this.getField('pstlDetl').setValue(data['pstl']);
					
					data['frequency'] = this.getField('frequencyDetl').getValue();
					data['chargeOption'] = this.getField('paymentOptnDetl').getValue();
					data['termPymt'] = Ext.getCmp('termOfPaymentDetl').getValue();
					data['termPymtType'] = Ext.getCmp('termOfPaymentTypeDetl').getValue();
					data['currency'] = this.getField('currencyDetl').getValue();
					data['taxApplies'] = this.getField('taxApplyDetl').getValue();
					data['suppInfoReq'] = this.getField('supplementReqDetl').getValue();
					data['lang'] = this.getField('languageDetl').getValue();
					data['brandingType'] = this.getField('brandingTypeDetl').getValue();
					return data;
				}
			}
		)
		
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
		
		,fields: _fields
		
		,grids: _grids
		
		,buttons: _buttons
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				, width: _layoutWidth
				, layout: 'form'
				, style: 'margin-top:10px'
				, items: [
					{
						layout: 'column'	
						, items: [
							{
								columnWidth: 0.5
								,layout: 'form'
								,labelWidth: 102
								,items: [_fields['holdingCompanySrch']]
							}
							,{
								columnWidth: 0.5
								,layout: 'form'
								,labelWidth: 99
								,items: [_fields['invoiceSrch']]
							}
						]
					}
					, {
						layout: 'auto'
						,items: [
							{
								layout: 'column'
								,labelWidth: 1
								,items: [
									{
										columnWidth: 0.7
										,layout: 'hbox'
										,items: [
											_fields['optSelectAll']
											,_fields['optSelectAsOfDate']
											,_fields['asOfDate']
										]
									}
									, {
										columnWidth: 0.3
										,layout: 'form'
										, style: 'text-align:right; padding-right:16px'
										, items: [
											_buttons['cmdSearch']
										]	
									}
								]
							}	
						]
					}
					, {					
						layout: 'form'
						, items: [
							_grids['grdInvoiceInstr']
						]
					}
					,{					
						layout: 'column'
						, items: [
							{	
								columnWidth: 0.5
								,xtype: 'fieldset'
								,height: 380
								,title: _translationMap['BillingEntityTitle']
								,labelWidth: 105
								,style: 'word-wrap:break-word;verical-align:top;margin-right:15px;'
								, items:[	_fields['invoiceName1']
											,_fields['deliveryName1']
											,_fields['deliveryName2']
											,_fields['addr1']
											,_fields['addr2']
											,_fields['addr3']
											,_fields['addr4']
											,_fields['city']
											,_fields['country']
											,_fields['pstl']
										]
							}
							,{
								columnWidth: 0.5
								,xtype: 'fieldset'
								,height: 380
								,title: _translationMap['BillingDetail']
								,labelWidth: _layoutLabelWidth
								,style: 'word-wrap:break-word;verical-align:top;'
								, items:[	
										_fields['frequency']
										,_fields['paymentOptn']
										,_fields['termOfPayment']													
										,_fields['currency']
										,_fields['taxApply']
										,_fields['language']
										,_fields['supplementReq']
										,_fields['brandingType']						
								]
							}
						]
					}
				]				
			}
		)
		,screenButtons: {
			buttonAlign : 'left'
			,items: [
				new DesktopWeb.Controls.ScreenButton({
					id: 'InvoiceAdj'
					,text: _translationMap['Invoice']
					,handler: function(){_controller.openActionPopup('InvoiceAdj',null);}
				})
				,new DesktopWeb.Controls.ScreenButton({
					id: 'AccountList'
					,text: _translationMap['AccountList']
					,handler: function(){_controller.openActionPopup('AcctAssociate',null);}
				})
				, '->'
				,new DesktopWeb.Controls.ScreenButton({
					text: _translationMap['OK']
					,handler: function(){
						if(_controller.updatesFlag){
							_controller.doValidateCommitScreen();
						}else{
							DesktopWeb.Util.commitScreen();
						}
					}
				})
				,new DesktopWeb.Controls.ScreenButton({
					text: _translationMap['Cancel']
					,handler: function(){
						if(_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
														
							function handlePromptMsg(btn){
								if(btn){
									DesktopWeb.Util.cancelScreen();
								}
							}
						}else{
							DesktopWeb.Util.cancelScreen();
						}
					}
				})
			]
		}
	}
}