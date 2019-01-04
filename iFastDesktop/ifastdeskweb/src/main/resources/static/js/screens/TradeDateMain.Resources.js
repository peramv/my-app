/*********************************************************************************************
 * @file	TradeDateMain.Resources.js
 * @author	Kittichai Sopitwetmontree
 * @desc	Resources JS file for Trade Date Maintenance screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();	
	// content dimensions
	var _layoutHeight = 365;
	var _layoutWidth = 715;
	
	// **** fields ****
	var _fields = {	
		cboFundClass: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['FundClass']
			,smartview: 'fundClassSearch'				
			,fields: ['fndClsDisp', 'fundCode', 'classCode']
			,valueField: 'fndClsDisp'
			,displayField: 'fndClsDisp'		
			,addtlSearchParams: [{name: 'api', valueFn: function(){return 'dtTradeSchdMntInit'}}]
			,width: 420												
		})

		, cboSearchFor: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['SearchFor']
				, width: 120	
				, editable: false
				, lastQuery: ''
				, listeners:{ 				
					
				}
			}
		)
		, dtpStartDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['StartDate']			
				, width: 120
				, validateOnChange: false				
				, validateOnBlur: false
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		, dtpEndDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['EndDate']			
				, width: 120
				, validateOnChange: false				
				, validateOnBlur: false
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)	
		, dtpValuationDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['ValuationDate']			
				, width: 150
				, validateOnChange: false				
				, validateOnBlur: false
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		, cboTransType: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['TransType']
				, width: 150	
				, editable: false
				, lastQuery: ''
				, listeners:{ 				
					
				}
			}
		)
		, dtpTradeDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['TradeDate']			
				, width: 150
				, validateOnChange: false				
				, validateOnBlur: false
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		, dtpSettlementDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['SettlementDate']			
				, width: 150
				, validateOnChange: false				
				, validateOnBlur: false
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		, dtpCutOffDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['CutOffDate']			
				, width: 150
				, validateOnChange: false				
				, validateOnBlur: false
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
	}
	
	// **** buttons ****
	var _buttons = {
		
		cmdSearch: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnSearch']
				, handler: function() {_controller.doSearch(false);}						
			}
		)
		, cmdAddTradeSchd: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnAdd']
				, id: 'cmdAddTradeSchd'
				, handler: function(){_controller.openActionPopup('frmAddModTradeSchd', _controller.ADD);}						
			}
		)
		, cmdModTradeSchd: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnMod']
				, id: 'cmdModTradeSchd'
				, handler: function(){_controller.openActionPopup('frmAddModTradeSchd', _controller.MOD);}						
			}
		)
		, cmdDelTradeSchd: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnDel']
				, id: 'cmdDelTradeSchd'
				, handler: function(){_controller.openActionPopup('frmAddModTradeSchd', _controller.DEL);}						
			}
		)
		, cmdMoreTradeSchd: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnMore']
				, id: 'cmdMoreTradeSchd'
				, handler: function() {_controller.doSearch(true);}			
			}
		)
		, cmdSubmitTradeSchd: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnOk']
			}
		)
		, cmdCancelTradeSchd: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnCancel']
			}
		)
		, cmdAddModTradeSchdSubmit: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnOk']
				, handler: function(){
					if (_popups['frmAddModTradeSchd'].isValid())
					{						
						_controller.doValidate(_popups['frmAddModTradeSchd'].action, _popups['frmAddModTradeSchd'].getData());
					}
				}
			}
		)
		, cmdAddModTradeSchdCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['BtnCancel']
				, handler: function(){
					if (_popups['frmAddModTradeSchd'].isValid())
					{
						_popups['frmAddModTradeSchd'].hide();
					}
				}
			}
		)		
	}
	
	// **** grids ****
	var _grids = {
		grdTradeSchd: new DesktopWeb.AdvancedControls.GridPanel
		(
			{
				width: _layoutWidth
				, style: "margin-bottom:15px"
				, autoScroll: true
				, height: 250
				, store: new Ext.data.XmlStore
				(
					{
						record: 'TradeSchd'
						, fields: [ 'recIDTradeSchd',
									'valuationDate', 
									'transType',
									'tradeDate',
									'settlementDate',
									'cutOffDate',
									'allowMod',
									'allowDel',
									'runMode',									
									'version',
									'errMsg']
						, listeners: {
							load: function(store, records) {
								Ext.each(records, function(record){
									record.data.valuationDate = DesktopWeb.Util.getDateDisplayValue(record.data.valuationDate);
									record.data.tradeDate = DesktopWeb.Util.getDateDisplayValue(record.data.tradeDate);
									record.data.settlementDate = DesktopWeb.Util.getDateDisplayValue(record.data.settlementDate);
									record.data.cutOffDate = DesktopWeb.Util.getDateDisplayValue(record.data.cutOffDate);									
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
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.updateTradeSchedButtons(record);
								}
							}
						}
					}
				)
				, colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [	
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }, width: 25 }
							, {header: _translationMap['ValuationDate'], dataIndex: 'valuationDate', width:150}
							, {header: _translationMap['TransType'], dataIndex: 'transType', renderer: function(val) {return (val ? _controller.translateTransType(val) : ''); }
							, width: 150 }							
							, {header: _translationMap['TradeDate'], dataIndex: 'tradeDate', width:150}
							, {header: _translationMap['SettlementDate'], dataIndex: 'settlementDate', width:150}				
							, {header: _translationMap['CutOffDate'], dataIndex: 'cutOffDate', width:150}
						]
					}
				)
				
				, buttons: [					
					_buttons['cmdAddTradeSchd']
					, _buttons['cmdModTradeSchd']
					, _buttons['cmdDelTradeSchd']	
					, _buttons['cmdMoreTradeSchd']
				]
			}		
		)	
	}
	
	// **** popups ****
	var _popups = {	
		frmAddModTradeSchd: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 700
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
				    {
						html: _translationMap['DeleteRecord']
						, style: 'text-align:center'		
						, defaults: {border:false}						
					}
					,{
						layout: 'form'
						, defaults: {border: false, labelWidth:50}
						, items: [
							{
								layout: 'column'								
								, style: 'padding:4px'
								, defaults: {border: false}
								,items: [ 
									{
										width: 300
										, layout: 'form'
										, labelWidth: 120
										, defaults: {border: false}										
										, items: [ 

											_fields['dtpValuationDate'] 
											, _fields['dtpTradeDate'] 
										]
									}
									, 
									{
										width: 300
										, layout: 'form'
										, labelWidth: 120
										, defaults: {border: false}										
										, items: [
											_fields['cboTransType']	
											, _fields['dtpSettlementDate']
											, _fields['dtpCutOffDate']
										]
									}
								]
							}
														
						]
						
					}
				]
				,buttons: [
					_buttons['cmdAddModTradeSchdSubmit']
					, _buttons['cmdAddModTradeSchdCancel']				
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
							this.setTitle(_translationMap['TitleAdd']);
							this.enableAllFields();
							_controller.setDefaultNewTradeSchd();
							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['TitleMod']);
							this.enableAllFields();
							_controller.populateTradeSchd();
							break;
						}
						case _controller.DEL:
						{							
							this.setTitle(_translationMap['TitleDel']);
							this.disableAllFields();
							_controller.populateTradeSchd();
							this.get(0).show();
							break;
						}						
					}					
				}
				, getData: function()
				{
					var data = {};
					data["valuationDate"] =  _fields['dtpValuationDate'].getSMVDateString();
					data["tradeDate"] =  _fields['dtpTradeDate'].getSMVDateString();
					data["settlementDate"] =  _fields['dtpSettlementDate'].getSMVDateString();
					data["cutOffDate"] =  _fields['dtpCutOffDate'].getSMVDateString();
					data["transType"] = _fields['cboTransType'].getValue();	
					
					return data;
				}
				, disableAllFields: function()
				{
					_fields['dtpValuationDate'].disableField();
					_fields['dtpTradeDate'].disableField();
					_fields['dtpSettlementDate'].disableField();
					_fields['dtpCutOffDate'].disableField();
					_fields['cboTransType'].disableField();
				}
				, enableAllFields: function()
				{
					_fields['dtpValuationDate'].enableField();
					_fields['dtpTradeDate'].enableField();
					_fields['dtpSettlementDate'].enableField();
					_fields['dtpCutOffDate'].enableField();
					_fields['cboTransType'].enableField();
				}
			}		
		)	
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
				,items: [
					{
						layout: 'form'
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 100}	
						,items: [
							{
								width: _layoutWidth
								, layout: 'form'
								//, labelWidth: 70
								, items: [
									_fields['cboFundClass']
								]
							}
							, {
							
								width: _layoutWidth
								, layout: 'form'								
								, items: [
									_fields['cboSearchFor']
								]
							}
							, {
								
								width: _layoutWidth 
								, layout: 'column'
								, items: [
									{
										width: 300
										, layout: 'form'										
										, items: [_fields['dtpStartDate']]
																			
									}
									, {
									
										width: 300
										, layout: 'form'										
										, items: [_fields['dtpEndDate']]
									}						
									, {

										width: 80
									
										, items: [
											{
												width: 80
												, layout: 'form'
												, style: "text-align:left"
												, items: [_buttons['cmdSearch']]
																	
											}

										]
									}									
								
								]
							}

						]
					}
					,{
						items: [_grids['grdTradeSchd']]
					
					}
										
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: 'OK'
					,handler: function(){DesktopWeb.Util.commitScreen()}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'Cancel'
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}