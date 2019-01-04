/*********************************************************************************************
 * @file	AcctTaxAlloc.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Account Holding Allocation by Tax Jurisdiction screen
 *********************************************************************************************/
/*
 * Procedure: AcctTaxAlloc.Resources.js
 *
 * Purpose  : Resource of Account Ownership Allocation screens
 *             
 * Notes    : Open screens by COA -> Option Box -> Account Ownership Allocation
 *
 * History  : 
 *    28 Sep 2012 H.Sartsangchan Created. 
 *           IN3102195 PETP0179630 FN01 Fatca 
 *           - Change from Direct Text to using TranslationMap
 *  
 *    18 Sep 2013 G.Thawornwachirakun PETP0193400 FN01 DFT0018331 T54203
 *           - Update Tax Juris and Comply Code to be able to editable
 * 
 *    09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 DFT0021169 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *          - The Historical screen of Acct Ownership Alloc 
 *          is not properly displayed
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 300;
	var _layoutWidth = 600;
	
	// **** fields ****
	var _fields = {		
	}
	
	// **** grids ****
	var _grids = {
		taxAllocGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 12
				,title: ''
				,autoScroll: true
				,height: 225
				,autoExpandColumn: 'taxJuris'
				,store: new Ext.data.XmlStore({
					record: 'AcctTaxAllocDetail'
					,idPath: 'taxAllocUUID'
					,fields: ['taxAllocUUID', 'account', 'complyCode', 'effDate', 'taxJuris', 'ownershipPrcnt', 'taxablePrcnt', 'runMode', 'version', 'errMsg']
					,listeners: {
						load: function(store, records)
						{
							Ext.each(records, function(record){
								record.data.effDate = DesktopWeb.Util.getDateDisplayValue(record.data.effDate);
							});
							store.filterBy(function(record){return record.data.runMode != 'delete'})	
							if (records.length > 0) _grids['taxAllocGrid'].getSelectionModel().selectFirstRow();
							_controller.controlButton();
						}
						,update: function(store)
						{								
							store.filterBy(function(record){return record.data.runMode != _controller.DEL});
							_controller.controlButton();
						}			
					}
				})
				,selModel: new Ext.grid.RowSelectionModel({
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.setSelectedTaxAlloc(record);
							}
						}
						,rowdeselect: function(selModel, index, record){
							if(selModel){
								_controller.setSelectedTaxAlloc(null);}
							}
					}
				})
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
						,width: 110
						,sortable: false
					}
					,columns: [
						{
							dataIndex: 'errMsg'
							,renderer: function(val){
								return ((val && val.length > 0) ? DesktopWeb.Util.buildErrorFlag(val) : '');
							}
							,width: 25
						}
						,{header: _translationMap['EffectiveDate'], dataIndex: 'effDate', width: 80}
						,{header: _translationMap['CompliantCode'], dataIndex: 'complyCode'
							, renderer: function(val){
								return (_controller.getDisplay('ComplyCode', val));
							}
							, width: 85
						}
						,{id: 'taxJuris', header: _translationMap['TaxJuris'], dataIndex: 'taxJuris'
							, renderer: function(val){
								return (_controller.getDisplay('TaxJuris', val));
							}
						}
						,{header: _translationMap['OwnershipPrcnt'], dataIndex: 'ownershipPrcnt', width: 75}
						,{header: _translationMap['TaxablePrcnt'], dataIndex: 'taxablePrcnt', width: 75}
					]							
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'	
						,text: _translationMap['Add']		
						,disabled: true				
						,handler: function(){_controller.openActionPopup(_controller.ADD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,disabled: true
						,handler: function(){_controller.openActionPopup(_controller.MOD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,disabled: true
						,handler: function(){_controller.openActionPopup(_controller.DEL);}							
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'historicalBtn'
						,text: _translationMap['Historical']
						,disabled: true
						,handler: function(){_controller.clickHandle_historyBtn();}
					})
				]
			}
		)
	}
	
	// **** popups ****
	var _popups = {					
		taxAllocUpdate: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 300
			,closeAction: 'hide'					
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
						new DesktopWeb.Controls.Label({
							itemId: 'pAccountLabel'
							,fieldLabel: _translationMap['Account']
							,width: 150
							,text: ''
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'pEffDateFld'
							,fieldLabel: _translationMap['EffectiveDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pComplyCodeFld'
							,fieldLabel: _translationMap['CompliantCode']
							,listeners: {
								select: function(combo, record, index)
								{
									if ( combo.getValue() != "" )
									{
										combo.clearInvalid();
										_popups['taxAllocUpdate'].getField('pTaxJurisFld').clearInvalid();
									}
								}
							}
							,validator: function(value){
								if ( value == "" && _popups['taxAllocUpdate'].getField('pTaxJurisFld').getValue() == "" )
								{
									return _translationMap['Error_EitherTaxJurisOrComplyCode'];
								}
								return true;
							}
							,width: 150
							,allowBlank: true
							,editable: true
							,autoSelect: true
							,lastQuery: ''
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pTaxJurisFld'
							,fieldLabel: _translationMap['TaxJuris']
							,listeners: {
								select: function(combo, record, index)
								{
									if ( combo.getValue() != "" )
									{
										combo.clearInvalid();
										_popups['taxAllocUpdate'].getField('pComplyCodeFld').clearInvalid();
									}
								}
							}
							,validator: function(value){
								if ( value == "" && _popups['taxAllocUpdate'].getField('pComplyCodeFld').getValue() == "" )
								{
									return _translationMap['Error_EitherTaxJurisOrComplyCode'];
								}
								return true;
							}
							,width: 150
							,allowBlank: true
							,editable: true
							,autoSelect: true
							,lastQuery: ''
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'pOwnershipPrcntFld'
							,fieldLabel: _translationMap['OwnershipPrcnt']
							,allowBlank: false
							,allowDecimal: true
							,decimalPrecision: 2
							,maxLength: 6
							,width: 150
              ,allowNegative: false
              ,maxValue: 100
              ,minValue: 0
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'pTaxablePrcntFld'
							,fieldLabel: _translationMap['TaxablePrcnt']
							,allowBlank: false
							,allowDecimal: true
							,decimalPrecision: 2
							,maxLength: 6
							,width: 150
              ,allowNegative: false
              ,maxValue: 100
              ,minValue: 0
						})
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['taxAllocUpdate'].isValid()){
							_controller.taxAllocUpdate(_popups['taxAllocUpdate'].action, _popups['taxAllocUpdate'].getData());
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['taxAllocUpdate'].hide();}
				})
			]
			,init: function(action, selectedTaxAlloc)
			{
				// initialize popup based on action
				var popup = _popups['taxAllocUpdate'];
				popup.action = action;
				switch(action)
				{
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['title']+ ' - ' +_translationMap['Add']);
						popup.populate(action, null);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['title']+ ' - ' +_translationMap['Modify']);
						popup.populate(action, selectedTaxAlloc);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['title']+ ' - ' +_translationMap['Delete']);
						popup.populate(action, selectedTaxAlloc);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action, selectedTaxAlloc)
			{
				var popup = _popups['taxAllocUpdate'];	
				popup.clearAllFields();
				popup.enableAllFields();
				popup.getField('pAccountLabel').setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
				if ( action != _controller.ADD )
				{
					popup.getField('pEffDateFld').setValue(selectedTaxAlloc.get('effDate'));
					popup.getField('pComplyCodeFld').setValue(selectedTaxAlloc.get('complyCode'));
					popup.getField('pTaxJurisFld').setValue(selectedTaxAlloc.get('taxJuris'));
					popup.getField('pOwnershipPrcntFld').setValue(selectedTaxAlloc.get('ownershipPrcnt'));
					popup.getField('pTaxablePrcntFld').setValue(selectedTaxAlloc.get('taxablePrcnt'));
					
					if ( popup.getField('pComplyCodeFld').isValid() )
					{
						popup.getField('pComplyCodeFld').clearInvalid();
					}
				}
				if ( action == _controller.DEL )
				{
					popup.getField('pEffDateFld').disableField();
					popup.getField('pComplyCodeFld').disableField();
					popup.getField('pTaxJurisFld').disableField();
					popup.getField('pOwnershipPrcntFld').disableField();
					popup.getField('pTaxablePrcntFld').disableField();
				}
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['account'] = this.getField('pAccountLabel').getValue();
				data['effDate'] = this.getField('pEffDateFld').getDisplayDateString();
				data['complyCode'] = this.getField('pComplyCodeFld').getValue();
				data['taxJuris'] = this.getField('pTaxJurisFld').getValue();
				data['ownershipPrcnt'] = this.getField('pOwnershipPrcntFld').getValue();
				data['taxablePrcnt'] = this.getField('pTaxablePrcntFld').getValue();
				return data;
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
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					{
						xtype:'fieldset'
						,title: _translationMap['title']
						,layout: 'column'
						,style: 'margin-bottom:10px'
						,width: _layoutWidth
						,items: [
							_grids['taxAllocGrid']
						]
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){DesktopWeb.Util.commitScreen();}
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