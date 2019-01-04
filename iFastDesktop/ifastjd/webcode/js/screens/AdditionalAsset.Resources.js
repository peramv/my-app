/*
 * Procedure: AdditionAsset.Resource.js
 *
 * Purpose  :  			  
 *             
 * Notes    : Open screens by 
 *                Menu -> MF and MFR Maintenance -> Additional Assets
 *			      Menu -> System Maintenance -> Holding Company -> Additional Assets
 *
 * History  : 
 *	
 *		05 Mar 2013 Gomoot T. PETP0206635 FN01 T53252 MFR MFI Enhancements
 *			- Created
 *	
 *		07 May 2013 Gomoot T. PETP0206635 FN01 IN3316087 T53522
 *			- Modify Additional Asset-Sub Advised Asset to display Currency Column
 *
 *		23 May 2013 Gomoot T. PETP0206635 FN01 IN3330320 T53597
 *          - Fix Sub Advised Asset screen to not able to search when  
 *            either effective or stop date is blank.
 *
 *		29 May 2013 Gomoot T. PETP0206635 FN01 IN3338220 T53638
 *          - Change the update state by
 *          1) Call with  validation mode
 *          2) if there is no error, call commit screen which will make the update to database.
 *
 *		15 Aug 2013 G. Thawornwachirakun P0193400 T54018
 *			- Add onlyActive param to broker and slsRep search
 *
 *      12 Nov 2013 N. Kanjanawaikoon PP0181067 FN01 CHG0034430 T54444
 *          - Getting the date format from DesktopWeb.Util.getDateDisplayValue to show
 *            all date with correct format from registry field
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	
	// content dimensions
	var _layoutHeight = 405;
	var _layoutWidth = 700;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _assetsAggrMethod = 'TGA';
	
	// **** fields ****
	var _fields = {		
	
		holdingCompanySrch: new DesktopWeb.Controls.SuggestField(
			{
				fieldLabel: _translationMap['HoldingCompany']
				, width: 250	
				, smartview: 'holdingCompanySearch'				
				, fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'displayValue' ]
				, valueField: 'holdingCompanyCode'
				, descValue : 'holdingCompanyDesc'
				, displayField: 'displayValue'					
				, addtlSearchParams: [{name: 'assetsAggrMethod', valueFn: function() {return _assetsAggrMethod} }]				
				, listeners: {
					populated: function()
					{						
						_controller.enableSearch();
					}
					,cleared: function()
					{
						_controller.enableSearch();						
					}					
				}
				
			}
		)
		, assetTypeSrch: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['AssetType']
				, allowBlank: true
				, editable: false			
				, width: 150
				, listeners: {
					select: function()
					{
						_controller.disableMoreButton();						
					}
				}
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
				,name: 'periodSrch'
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
				width: 100	
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,listeners: {
						change: function(){
							_controller.doSrchCheck();											
						}
					}
			}
		)	
		, holdingCompanyPopUp: new DesktopWeb.Controls.SuggestField( 
			{
				fieldLabel: _translationMap['HoldingCompany']
				, style: 'padding-left:5px;'
				, width: 300				
				, fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'displayValue' ]
				, smartview: 'holdingCompanySearch'
				, valueField: 'holdingCompanyCode'
				, displayField: 'displayValue'					
				, addtlSearchParams: [{name: 'assetsAggrMethod', valueFn: function() {return _assetsAggrMethod} }]	
				, allowBlank: false				
			}
		)
		, assetTypePopup : new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['AssetType']
				, editable: false			
				, width: 300
				, allowBlank : false				
				, listeners:{          					
					select: function(record) {
						_controller.clearAllAssetType();
						_controller.populateAssetType(record.getValue());						
					}
				}	
			}
		)
		, accountPopup: new DesktopWeb.Controls.SuggestField( 
			{
				fieldLabel: _translationMap['Account']
				, style: 'padding-left:5px;'
				, width: 300
				, displayField: 'displayValue'	
				, smartview: 'accountSearch'				
				, fields: ['displayValue', 'acctNum', 'accountDesc']
				, valueField: 'acctNum'					
				, addtlSearchParams: [{name: 'incAllStat', valueFn: function(){return 'yes'}}]
				, allowBlank: true					
			}
		)
		, brokerPopup: new DesktopWeb.Controls.SuggestField( 
			{
				fieldLabel: _translationMap['Broker']
				, style: 'padding-left:5px;'
				, width: 300
				, smartview: 'brokerSearch'	
				, addtlSearchParams: [{name: 'onlyActive', valueFn: function(){return 'yes';}}]
				, fields: ['displayValue', 'agencyCode', 'brokerDesc' ]
				, valueField: 'agencyCode'
				, allowBlank: true
				, listeners:{
					populated: function(){
						if (_controller.enableSaleRepAllowed())
						{
							_fields['saleRespPopup'].enable();
						}
					
					}
					, cleared: function(){						 
						_fields['saleRespPopup'].reset();														 							
						_fields['saleRespPopup'].disable();						 
					}
				}					
						
			}
		)
		, saleRespPopup: new DesktopWeb.Controls.SuggestField( 
			{
				fieldLabel: _translationMap['SaleResp']
				, style: 'padding-left:5px;'
				, width: 300
				, smartview: 'salesRepSearch'				
				, fields: ['displayValue', 'agentCode', 'branch', 'saleRespDesc']
				, forceSelection: false
				, addtlSearchParams: [
					{name: 'agencyCode', valueFn: function() { return _fields['brokerPopup'].getValue();}}
					,{name: 'onlyActive', valueFn: function(){return 'yes';}}					
				  ]
				, valueField: 'agentCode'								
			}
		)	
		, subAdvisedPopup : new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['SubAdvised']
				, editable: false			
				, style: 'padding-left:5px;'
				, forceSelection: false
				, width: 300
			}
		)

		, effectiveDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['EffectiveDate']
				, allowBlank: false
				, width: 100
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		, stopDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['StopDate']
				, allowBlank: false
				, width: 100
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())				
			}
		)
		, subAdviseName: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['Asset']
				, width: 150
				, disable: true
				, readOnly: true
			}
		)
		, subAdviseStartDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['EffectiveDate']
				, allowBlank: false
				, width: 150
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())				
			}
		)
		, subAdviseStopDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['StopDate']
				, allowBlank: false
				, width: 150
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())				
			}
		)
	}
	
	var _buttons = {
		cmdSearch: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Search']
				, handler: function() { if (_controller.doValidateSearch())
											_controller.doSearch(false);
									  }	
			}
		)
		, cmdAdditionalAssetAdd: new DesktopWeb.Controls.ActionButton(
			{
				itemId: 'addBtn'
				, text: _translationMap['Add']
				, handler: function(){_controller.openActionPopup( 'frmAdditionalAsset', _controller.ADD);}	
			}
		)
		, cmdAdditionalAssetMod: new DesktopWeb.Controls.ActionButton(
			{
				itemId: 'modBtn'
				, text: _translationMap['Modify']
				, handler: function(){_controller.openActionPopup( 'frmAdditionalAsset', _controller.MOD);}
			}
		)
		, cmdAdditionalAssetDel: new DesktopWeb.Controls.ActionButton(
			{
				itemId: 'delBtn'
				, text: _translationMap['Delete']
				, handler: function(){_controller.deleteSelectedRecord();}
			}
		)
		, cmdAdditionalAssetMore: new DesktopWeb.Controls.ActionButton(
			{
				itemId: 'moreBtn'
				, text: _translationMap['More']
				, handler: function() {_controller.doSearch(true);}	
			}
		)
		, cmdAdditionalAssetAdmin: new DesktopWeb.Controls.ActionButton({
				itemId: 'adminBtn'
				, text: _translationMap['Admin']
				, handler: function(){_controller.openAdminPopup('AdditionalAsset');}
			})
		, cmdAdditionalAssetHistory: new DesktopWeb.Controls.ActionButton({
			itemId: 'historicalBtn'
			, text:_translationMap['Historical']
			, handler: function(){_controller.openHistoryPopup('AdditionalAsset');}
		})
		
		, cmdAdditionalAssetSubmit: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['OK']
				, handler: function(){
					
					if (_popups['frmAdditionalAsset'].isValid())
					{						
						if (_controller.doValidatePopUpScreen(_popups['frmAdditionalAsset'].action
						, _popups['frmAdditionalAsset'].getData(_popups['frmAdditionalAsset'].action))
						)
							_popups['frmAdditionalAsset'].hide();
					}
				}
			}
		)
		, cmdAdditionalAssetCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					if (_popups['frmAdditionalAsset'].isValid())
					{
						_popups['frmAdditionalAsset'].hide();
					}
				}
			}
		)
		, cmdAdditionalAssetSubAdvise: new DesktopWeb.Controls.ActionButton({
			itemId: 'subAdviseBtn'
			, text : _translationMap['Assets']
			, handler: function(){_controller.openSubAdvisePopup('AdditionalAsset');}
		})
		, cmdSubAdvisedSearch: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Search']
				, handler: function() {
					if (_controller.doValidateSubAdviseSearch())
						_controller.doSubAdviseSearch(true);
				}	
			}
		)		
	}	
	
	// **** grids ****
	var _grids = {
		grdAdditionalAsset: new DesktopWeb.AdvancedControls.GridPanel({
				width: _layoutWidth - 10
				, style: "margin-top:15px;margin-bottom:15px;"
				, autoScroll: true
				, height: 250	
				, autoExpandColumn: name			
				, store: new Ext.data.XmlStore({
					record: 'AdditionAssetDetail'						
					, fields: ['holdingEntityCode', 'holdingEntityDesc'
								,'identifier', 'identifier2'
								,'name', 'name2' , 'salerepDetail'
								,'assetTypeCode',  'assetTypeDesc'
								,'effectiveDate',  'stopDate'
								,'version', 'feeAggrID'
								,'runMode', 'errMsg', 'updSeq'
								,'gridIndex'
								,'userName'
								,'processdate'
								,'modUser'
								,'modDate'
							]
					, listeners: {
						load: function(store, records) {
							Ext.each(records, function(record){
								record.data['effectiveDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['effectiveDate']);	
								record.data['stopDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['stopDate']);	
								record.data['processdate'] = DesktopWeb.Util.getDateDisplayValue(record.data['processdate']);
								record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);												
							});						
							store.filterBy(function(record){
									return (record.data.runMode != _controller.DEL);										
								}
							)								
						}
					}
				})
				, selModel: new Ext.grid.RowSelectionModel({
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record)
						{
							_controller.setSelectedAdditionalAsset(record.get("gridIndex"));								
						}					
					}
				})
				, colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					, columns: [	
						{
							dataIndex: 'errMsg'
							, width: 25
							, renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
						 }				
						, {header: _translationMap['HoldingCompany'], width:120
							, renderer: function(val, metaData, record){return (record.data['holdingEntityCode'] + ' - ' + record.data['holdingEntityDesc'])}}
						, {header: _translationMap['AssetType'], dataIndex: 'assetTypeDesc', width:100}
						, {header: _translationMap['Identifier'], dataIndex: 'identifier', width:80}
						, {header: 
							_translationMap['Name']
							, id : name 
							, dataIndex: 'name'
							, width:180
							, renderer: function(val, metaData, record){											
								return (record.data['salerepDetail'] != _controller.BLANK && 
										record.data['salerepDetail'] != undefined) ? 												
										record.data['salerepDetail'] + ' ' + record.data['name'] 
										: record.data['name'];
										}
						  }							
						, {header: _translationMap['EffectiveDate'], dataIndex: 'effectiveDate', width:80}
						, {header: _translationMap['StopDate'], dataIndex: 'stopDate', width:80}
					]
				})				
				, buttons: [		
					 _buttons['cmdAdditionalAssetSubAdvise']
					, _buttons['cmdAdditionalAssetAdd']
					, _buttons['cmdAdditionalAssetMod']
					, _buttons['cmdAdditionalAssetDel']	
					, _buttons['cmdAdditionalAssetMore']					
					, _buttons['cmdAdditionalAssetAdmin']
					, _buttons['cmdAdditionalAssetHistory']
				]
		})		
		,grdSubAdvise: new DesktopWeb.AdvancedControls.GridPanel({					
			width: 370			
			, autoScroll: true								
			, height: 220
			, autoExpandColumn: 'assetValue'
			, store: new Ext.data.XmlStore({			
				record: 'AssetValue'
				,fields: [ 'assetDate', 'assetValue', 'currency']
				, listeners: {
						load: function(store, records) 
						{
							Ext.each(records, function(record){
								record.data['assetDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['assetDate']);												
							});
							
							store.fireEvent('datachanged', store); //to set data in grid again					        								
						}
					}	
			})	
			
			, colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				, columns: [													
					
					{header: _translationMap['Date'], id: 'assetDate', dataIndex: 'assetDate', width:90}
					,{header: _translationMap['Values'], id: 'assetValue',dataIndex: 'assetValue'}
					,{header:  _translationMap['Currency'], id: 'currency',dataIndex: 'currency', width:80}
				]							
			})	
										
		})
		
		
	}
		
// **** popups ****
	var _popups = {		
		frmAdditionalAsset: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				, width: 500
				, closeAction: 'hide'
				, autoHeight: true
				, modal: true
				, defaults: {border:false}				
				, items: [
					 {
						layout: 'form'
						, defaults: {border: false, labelWidth:140}
						, style: 'margin-left:5px;margin-top:5px;,margin-bottom:5px;'
						, labelWidth: 140
						, items: [
							_fields['holdingCompanyPopUp']
							, _fields['assetTypePopup']							
							, _fields['accountPopup']
							, _fields['brokerPopup']
							, _fields['saleRespPopup']
							, _fields['subAdvisedPopup']
							, _fields['effectiveDate']							
							, _fields['stopDate']
						]
					}
				]			
				, buttons: [
					_buttons['cmdAdditionalAssetSubmit']
					, _buttons['cmdAdditionalAssetCancel']
					
				]
				, init: function(action)
				{								
					this.action = action;		
					
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle("Additional Asset - Add");							
							break;
						}
						case _controller.MOD:
						{
							this.setTitle("Additional Asset - Modify");
												
							break;
						}
						case _controller.DEL:
						{							
							this.setTitle("Additional Asset - Delete");							
							this.get(0).show();
							break;
						}						
						
					}	
				}
				,enableAllFields: function()
				{}
				,disableAllFields: function()
				{}
				, getData: function(action)
				{									
					var data = {};	
					var n = '';
					var record = null;
					data['name'] = "";
					data['identifier'] = "";
					data['name2'] = "";
					data['identifier2'] = "";
					data['errMsg'] = "";
					data['runMode'] = action;
					data['holdingEntityCode'] = '';
					data['holdingEntityDesc'] = '';
					
					if (_fields['effectiveDate'].getValue() != "" )						
						data['effectiveDate'] = _fields['effectiveDate'].getValue();			
					
					if (_fields['stopDate'].getValue() != "" )
						data['stopDate'] = _fields['stopDate'].getValue();
													
					record  = _fields['holdingCompanyPopUp'].selectedRecord;
					if (record && _fields['holdingCompanyPopUp'].getRawValue().trim() != '')
					{
						data['holdingEntityCode'] = record.data['holdingCompanyCode'];
						data['holdingEntityDesc'] = record.data['holdingCompanyDesc'];
					}
					
					
					data['assetTypeCode'] = _fields['assetTypePopup'].getValue().trim();
					data['assetTypeDesc'] = _fields['assetTypePopup'].getRawValue().trim();
					
					if (data['assetTypeCode'] == _controller.ACCOUNT)
					{							
						record  = _fields['accountPopup'].selectedRecord;
						
						if (record)
						{
							data['identifier'] = record.data['acctNum'];							
							
							if (record.data['accountDesc'] == '' || record.data['accountDesc'] == undefined)
							{
								n = record.data['displayValue'].trim().indexOf("-"); 
								data['name'] = record.data['displayValue'].trim().substring(n + 1).trim();
							}
							else
								data['name'] = record.data['accountDesc'];
						}						
					}
					else if (data['assetTypeCode'] == _controller.BROKER)
					{
						record  = _fields['brokerPopup'].selectedRecord;
						if (record)
						{
							data['identifier'] = record.data['agencyCode'];
							
							if (record.data['brokerDesc'] == '' || record.data['brokerDesc'] == undefined)
							{
								n = record.data['displayValue'].trim().indexOf(" "); 
								data['name'] = record.data['displayValue'].trim().substring(n + 1).trim();
							}
							else
								data['name'] = record.data['brokerDesc'];
						}						
					}
					else if (data['assetTypeCode'] == _controller.SALERESP)
					{						
						data['identifier'] = _fields['saleRespPopup'].getValue().trim();
						
						n = _fields['saleRespPopup'].getRawValue().trim().indexOf(" "); 
						data['name'] = _fields['saleRespPopup'].getRawValue().trim().substring(n + 1).trim();	
						
						record  = _fields['brokerPopup'].selectedRecord;
						if (record)
						{
							data['identifier2'] = record.data['agencyCode'];
							
							if (record.data['brokerDesc'] == '' || record.data['brokerDesc'] == undefined)
							{
								n = record.data['displayValue'].trim().indexOf(" "); 
								data['name2'] = record.data['displayValue'].trim().substring(n + 1).trim();
							}
							else
								data['name2'] = record.data['brokerDesc'];
						}	

						record  = _fields['saleRespPopup'].selectedRecord;
						if (record)
						{
							data['identifier'] = record.data['agentCode'];
							
							if (record.data['saleRespDesc'] == '' || record.data['saleRespDesc'] == undefined)
							{
								n = record.data['displayValue'].trim().indexOf(" "); 
								data['name'] = record.data['displayValue'].trim().substring(n + 1).trim();
							}
							else
								data['name'] = record.data['saleRespDesc'];
								
							if (record.data['branch'] != '')
								data['salerepDetail'] = data['identifier2'] + '-' + record.data['branch'] + '-' + data['identifier'];
						}
					}
					else if (data['assetTypeCode'] == _controller.SUBADV)
					{
						data['identifier'] = _fields['subAdvisedPopup'].getValue().trim();
						data['name'] = _fields['subAdvisedPopup'].getRawValue().trim();
					}	
					
					return data;
				}
				
			}
		)	
		
		,subAdviseWindow: new DesktopWeb.AdvancedControls.PopupWindow({								
			width: 400				
			, closeAction: 'hide'					
			, modal: true
			, border : false
			, defaults: {border:false}
			, items: [										
				{						
					layout: 'form'																		
					, style: 'padding:4px'
					, border:false 
					, defaults: {border: false, labelWidth:100}						
					, items: [
						{
							width:  370
							, layout: 'form'
							, defaults: {border: false}																				
							, items: [
								{	
									xtype: 'fieldset'
									, border: true
									, style: 'margin-top:5px;margin-button:15px'
									, title: _translationMap['AssetValue']
									, items: [										
										_fields['subAdviseName']
										, _fields['subAdviseStartDate']										
										, 	{
											layout: 'column'
											, border : false
											, style: 'margin-left:0px;border:none'
											, items: [
												{
													xtype: 'form'
													, border : false
													,columnWidth: 0.80	
													,labelWidth: 100
													,items:	[	
														 _fields['subAdviseStopDate']	
													]
												}									
												,{
													xtype: 'form'
													, border : false
													,columnWidth: 0.20
													,items:	_buttons['cmdSubAdvisedSearch']	
												}	
											]
										}
									]									
								}	
															
								, {					
									layout: 'form'
									, style: 'margin-top:5px;'
									, items: [
										_grids['grdSubAdvise']
									]
								}
							]
						}							
						
					]						
				}													
			]
			,buttons:[
				 new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Close']
					, handler: function(){_popups['subAdviseWindow'].hide();}
				})	
			]
			
			,init: function(title, data)
			{
				this.setTitle(title);
				_fields['subAdviseStartDate'].reset();
				_fields['subAdviseStopDate'].reset()

				_controller.doSubAdviseSearch(false);
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
				this.getField('procDate').setValue(data['createDate']);
				this.getField('modDate').setValue(data['modifyDate']);
				this.getField('userName').setValue(data['createUser']);
				this.getField('modUser').setValue(data['modifyUser']);	
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
						, defaults: {labelWidth: 120}							
						, items: [
							{
								layout: 'column'
								, defaults: {labelWidth: 120}	
								, width : _layoutWidth							
								, items: [
									{
										columnWidth: 0.60
										, labelWidth: 120
										, layout: 'form'
										, items: _fields['holdingCompanySrch']
										
									}
									,{
										columnWidth: 0.40	
										, labelWidth: 80										
										, layout: 'form'										
										, items: _fields['assetTypeSrch']
									}
								]
							}
							, {
								layout: 'column'								
								, width : _layoutWidth
								//, defaults: {labelWidth: 80}									
								, items: [
									{
										layout: 'hbox'
										,columnWidth: 0.85										
										,items:	[											
											_fields['optSelectAll']
											, _fields['optSelectAsOfDate']	
											, _fields['asOfDate']
										]
									}									
									,{
										columnWidth: 0.15
										,layout: 'form'
										,items:	_buttons['cmdSearch']	
									}	
								]

							}
						]
					}					
					, {					
						layout: 'form'
						, items: [
							_grids['grdAdditionalAsset']
						]
					}
				]				
			}
		)
		
		,screenButtons: [		
				new DesktopWeb.Controls.ScreenButton(
					{						
						text: _translationMap['OK']
						, handler: function(){ 
							if (_controller.updatesFlag)
								_controller.doValidateCommitScreen();
							else
								DesktopWeb.Util.commitScreen();
						}
					}
				)
				,new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['Cancel']
						,handler: function(){
							if (_controller.updatesFlag)
							{
								DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
															
								function handlePromptMsg(btn)
								{
									if (btn) DesktopWeb.Util.cancelScreen();
									
								}
							}else
							{
								DesktopWeb.Util.cancelScreen();
							}
						}
					}
				)			
			]	
			
	}
}