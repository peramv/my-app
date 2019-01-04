/*********************************************************************************************
 * @file	GuaranteeFee.Resources.js
 * @author	Suchit Majumdar
 * @desc	Resources JS file for GuaranteeFee screen
 *********************************************************************************************/
 
/*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *        - Fix display date format follows dateFormatDisplay parameter
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _layoutWidth = 715;
	var _layoutHeight = 500;
	
	var _fields = {
		contractType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ContractType']
			,width: 140
			,allowBlank: false
			,listeners: {
				change: function(){_controller.handleContractTypeUpdate()}
				,select: function(){_controller.handleContractTypeUpdate()} 
			} 			
		})		 	
		,feeType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FeeType']
			,width: 140
			,allowBlank: false
			,disabled: true
		})
	}

	var _buttons = {
		search: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,style: 'float:left; margin-right: 5px;'
			,handler: function(){_controller.doSearch()}
		})
		,reset: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Reset']
			,style: 'float:left'
			,handler: function(){_controller.doReset()}
		})
	}
	
	var _grids = {
		calculations: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 15
			,height: 200
			,store: new Ext.data.XmlStore({
				record: 'Calculation'
				,fields: ['guarFeeSummID'
						,'runMode'
						,'deff'
						,'GWBatCalcAmt'
						,'mktValue'
						,'feeCalcAmt'
						,'feeCollectAmt'
						,'feeType'
						,'feeTypeDesc'
						,'stat'
						,'statDesc'
						,'UserName'
						,'batch'
						,'trace'
						,'modPerm'
						,'delPerm'
						,'cancPerm'
						,'recalcPerm'
						,'processDate']
				,listeners: {
					load: function(store, records){
						Ext.each(records, function(record){
							record.data['deff'] = DesktopWeb.Util.getDateDisplayValue(record.data['deff']);
							record.data['processDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['processDate']);
						});
						store.fireEvent('datachanged', store);
					}
					,update: function(store){
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
						_controller.handleCalcSelectionChange();
					}
				}	
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns:[
					{header:_translationMap['CalcDate'], width: 85, dataIndex: 'deff'}
					,{header:_translationMap['GWBCalc'], width: 100, dataIndex: 'GWBatCalcAmt'}
					,{header:_translationMap['MarketValueCalc'], width: 110, dataIndex: 'mktValue'}
					,{header:_translationMap['FeeAmtCalculated'], width: 110, dataIndex: 'feeCalcAmt'}
					,{header:_translationMap['FeeAmtCollected'], width: 110, dataIndex: 'feeCollectAmt'}
					,{header:_translationMap['FeeType'], width: 100, dataIndex: 'feeTypeDesc'}
					,{header:_translationMap['Status'], width: 90, dataIndex: 'statDesc'}
				]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(){_controller.handleCalcSelectionChange()}
					,rowdeselect: function(){_controller.handleCalcSelectionChange()}
				}
			})
			,buttons:[
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,disabled: true
					,text: _translationMap['Add']
					,handler: function(){
						_controller.openManualCollPopup(_controller.ADD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,disabled: true
					,text: _translationMap['Modify']
					,handler: function(){
						_controller.openManualCollPopup(_controller.MOD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,disabled: true
					,text: _translationMap['Delete']
					,handler: function(){
						var selectedCalcRec = _grids['calculations'].getSelectedRecord();
						if (selectedCalcRec.data['feeType'] == '01')
						{
							_controller.deleteAutomaticCalc();
						}
						else
						{
							_controller.openManualCollPopup(_controller.DEL);
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'
					,disabled: true
					,text: _translationMap['Cancel']
					,handler: function(){_controller.doCalculationCancel();}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'recalcBtn'
					,disabled: true
					,text: _translationMap['ReCalc']
					,handler: function(){_controller.doCalculationRecalc();}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'detailsBtn'
					,disabled: true
					,text: _translationMap['Details']
					,handler: function(){_popups['details'].show()}
				})				
			]
		})
				
		,collections: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 15
			,height: 200
			,store: new Ext.data.XmlStore({
				record: 'Collection'
				,fields: [
					'guarFeeSummID'
					,'gwbFeeCollectionID'
					,'gwbFeeCollectionUUID'
					,'gwbFeeCollectAllocUUID'
					,'runMode'
					,'collectionDate'
					,'fund'
					,'class'
					,'calcAmt'
					,'collectAmt'
					,'totalFee'
					,'transId'
					,'transNumber'
					,'rebookPerm'
					,'cancCollectPerm'
					,'acCode'
					,'createdBy'
					,'stat'
					,'statDesc'
					,'modUser'
					,'modDate'
					,'stmt'
					,'rvcd'
					,'conf'
					,'cancPayment'
					,'remarks1'
					,'remarks2'
					,'remarks3']
				,listeners: {
					load: function(store, records){
					
						Ext.each(records, function(record){
							record.data['collectionDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['collectionDate']);
							record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);
						});
						store.fireEvent('datachanged', store);
						_controller.handleCalcSelectionChange();
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(){_controller.handleCollSelectionChange()}
					,rowdeselect: function(){_controller.handleCollSelectionChange()}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns:[
					{header:_translationMap['Date'], width: 75, dataIndex: 'collectionDate'}
					,{header:_translationMap['Fund'], width: 60, dataIndex: 'fund'}					
					,{header:_translationMap['Class'], width: 60, dataIndex: 'class'}
					,{header:_translationMap['FCCalcAmount'], width: 110, dataIndex: 'calcAmt'}
					,{header:_translationMap['FCCollectAmount'], width: 110, dataIndex: 'collectAmt'}
					,{header:_translationMap['TotalFee'], width: 85, dataIndex: 'totalFee'}
					,{header:_translationMap['TransID'], width: 85, dataIndex: 'transId'}
					,{header:_translationMap['TransNumber'], width: 85, dataIndex: 'transNumber'}
					,{header:_translationMap['CreatedBy'], width: 85, dataIndex: 'createdBy'}
					,{header:_translationMap['Status'], width: 100, dataIndex: 'statDesc'}
				]
			})
			,buttons:[
				new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'
					,disabled: true
					,text: _translationMap['Cancel']
					,handler: function(){_controller.doCollectionCancel();}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'rebookBtn'
					,disabled: true
					,text: _translationMap['ReBook']
					,handler: function(){_controller.doCollectionRebook();}
				})				
			]
		})
		
		,detl: new DesktopWeb.AdvancedControls.GridPanel({
			width: 475
			,height: 115
			,autoExpandColumn: 'FCFeeAmt'
			,store: new Ext.data.XmlStore({
				record: 'Detl'
				,fields: ['guarFeeDetlID'
						 ,'guarFeeSummID'
						 ,'fund'
						 ,'class'
						 ,'FCFeeAmt'
						 ,'rate'
						 ,'PMVPct'
						 ,'calcDate'
						 ,'GWBatCalcAmt'
						 ,'mktValue'
						 ,'feeCalcAmt']
				,listeners: {
					load: function(store, records){
						Ext.each(records, function(record){
							record.data['calcDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['calcDate']);
						});
						store.fireEvent('datachanged', store);
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(){
						_controller.handleDetlSelectionChange();
					}
					,rowdeselect: function(){
						_controller.handleDetlSelectionChange();
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns:[
					{header:_translationMap['Fund'], dataIndex: 'fund', width: 65}
					,{header:_translationMap['Class'], dataIndex: 'class', width: 65}
					,{header:_translationMap['FCFeeAmount'], dataIndex: 'FCFeeAmt', id: 'FCFeeAmt'}
					,{header:_translationMap['FeeRate'], dataIndex: 'rate', width: 100}
					,{header:_translationMap['AvgMEPMV'], dataIndex: 'PMVPct', width: 100}
				]
			})
		})
		,month: new DesktopWeb.AdvancedControls.GridPanel({
			width: 456
			,height: 80
			,autoExpandColumn: 'month'
			,style: 'padding-bottom: 5px;'
			,disableSelection: true
			,store: new Ext.data.XmlStore({
				record: 'Month'
				,fields: ['month'
						 ,'fundClassMV'
						 ,'contractMV'
						 ,'PMVPct']
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns:[
					{header:_translationMap['Month'], dataIndex: 'month', id: 'month'}
					,{header:_translationMap['FCMVCatCalc'], dataIndex: 'fundClassMV', width: 100}
					,{header:_translationMap['ContractMV'], dataIndex: 'contractMV', width: 100}
					,{header:_translationMap['AvgMEPMV'], dataIndex: 'PMVPct', width: 100}
				]
			})
		})
	}
	
// **** popups ****
	var _popups = {
		manualColl: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 480
			,closeAction: 'hide'
			,modal: true
			,bodyStyle: 'padding-top:4px; padding-left:4px'
			,defaults: {border:false}
			,action: null
			,listeners: {
				show: function(){_popups['manualColl'].init()}
			}
			,items:[
				{
					layout: 'column'
					,defaults: {border:false, layout: 'form'}
					,items: [
						{
							width: 250
							,labelWidth: 95
							,items: [
								new DesktopWeb.Controls.TextField({
									itemId: 'feeType'
									,width: 120
									,fieldLabel: _translationMap['FeeType']
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'fund'
									,width: 90
									,fieldLabel: _translationMap['Fund']
									,listeners: {
										select: function(){_controller.handleFundChange()}
										,change: function(){_controller.handleFundChange()}
									}
								})
								,new DesktopWeb.Controls.NumberField({
									itemId: 'collectAmt'
									,width: 90
									,fieldLabel: _translationMap['CollectAmount']
								})
							]
						}
						,{
							width: 205
							,labelWidth: 80
							,items: [
								new DesktopWeb.Controls.DateField({
									itemId: 'deff'
									,width: 95
									,fieldLabel: _translationMap['TradeDate']
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'class'
									,width: 90
									,fieldLabel: _translationMap['Class']
								})
							]
						}
						,{	
							layout: 'form'
							,labelWidth: 95
							,items: [
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'acCode'
									,width: 235
									,fieldLabel: _translationMap['Accountability']
								})
							]
						}
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						_controller.saveManualColl(_popups['manualColl'].action, _popups['manualColl'].getData());
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'
					,text: _translationMap['Cancel']
					,handler: function(){
						_popups['manualColl'].hide();
					}
				})
			]

			,init: function()
			{
				this.clearAllFields();
				this.enableAllFields();
				this.getField('feeType').setValue(_fields['feeType'].getValueDesc());
				this.getField('feeType').disableField();
				this.getField('fund').loadData(_controller.getFundList(_fields['contractType'].getValue()));

				switch (this.action)
				{
					case _controller.ADD: {
						this.setTitle(_translationMap['ManualCollection'] + " - " + _translationMap['Add']);
						this.getField('deff').setValue(_controller.getDefaultDate());
						this.getField('class').disableField();
						break;
					}
					case _controller.MOD: {
						this.setTitle(_translationMap['ManualCollection'] + " - " + _translationMap['Modify']);
						this.populateFromSelectedRecord();
						break;
					}
					case _controller.DEL: {
						this.setTitle(_translationMap['ManualCollection'] + " - " + _translationMap['Delete']);
						this.populateFromSelectedRecord();
						this.disableAllFields();
						break;
					}
				}
			}

			,populateFromSelectedRecord: function()
			{
				var selectedCalcRec = _grids['calculations'].getSelectedRecord();
				var selectedCollRec = _grids['collections'].getSelectedRecord();
				this.getField('deff').setValue(selectedCalcRec.data['deff']);
				this.getField('fund').setValue(selectedCollRec.data['fund']);
				_controller.handleFundChange();
				this.getField('class').setValue(selectedCollRec.data['class']);
				this.getField('collectAmt').setValue(selectedCollRec.data['collectAmt']);
				this.getField('acCode').setValue(selectedCollRec.data['acCode']);
			}

			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['deff'] = this.getField('deff').getDisplayDateString();
				data['fund'] = this.getField('fund').getValue();
				data['class'] = this.getField('class').getValue();
				data['collectAmt'] = this.getField('collectAmt').getValue();
				data['acCode'] = this.getField('acCode').getValue();
				return data;
			}
		})

		,details: new DesktopWeb.AdvancedControls.PopupWindow({
			title: _translationMap['CalculationDetails']
			,width: 490
			,closeAction: 'hide'
			,modal: true
			,defaults: {border:false, style: 'padding:4px'}
			,listeners: {
				show: function(){_popups['details'].init()}
			}
			,items:[
				_grids['detl']
				,{
					layout: 'form'
					,items: [
						{		
							xtype: 'fieldset'
							,title: _translationMap['Months']
							,items: [
								_grids['month']
							]
						}
					]
				}
			]			
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['Close']
					,handler: function(){
						_popups['details'].hide();
					}
				})
			]
			,init: function()
			{
				_grids['detl'].clearData();
				_grids['month'].clearData();
				_controller.populateDetails();
			}
		})
		
		,cancelColl: new DesktopWeb.AdvancedControls.PopupWindow({
			title: _translationMap['Collection'] + " - " + _translationMap['Cancel']
			,width: 490
			,closeAction: 'hide'
			,modal: true
			,bodyStyle: 'padding-top:4px; padding-left:4px'
			,defaults: {border:false}
			,listeners: {
				show: function(){_popups['cancelColl'].init()}
			}
			,items:[
				{
					layout: 'column'
					,defaults: {border:false, layout: 'form'}
					,items: [
						{
							width: 235
							,labelWidth: 100
							,items: [
								new DesktopWeb.Controls.YesNoComboBox({
									itemId: 'conf'
									,fieldLabel: _translationMap['RequireConfirm']
								})
								,new DesktopWeb.Controls.YesNoComboBox({
									itemId: 'cancPymnt'
									,fieldLabel: _translationMap['CancelPayment']
								})
							]
						}
						,{
							width: 220
							,labelWidth: 120
							,items: [
								new DesktopWeb.Controls.YesNoComboBox({
									itemId: 'stmt'
									,fieldLabel: _translationMap['ShowOnStatement']
								})
							]
						}
					]
				}
				,{
					layout: 'form'
					,labelWidth: 100
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'rvcd'
							,fieldLabel: _translationMap['ReversalCode']
							,width: 285
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'remarks1'
							,fieldLabel: _translationMap['Remarks']
							,width: 345
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'remarks2'
							,fieldLabel: ''
							,width: 345
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'remarks3'
							,fieldLabel: ''
							,width: 345
						})
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['cancelColl'].isValid())
						{
							_controller.saveCollCancel(_popups['cancelColl'].getData());
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['cancelColl'].hide()}
				})
			]
			,init: function()
			{
				this.clearAllFields();
			}
			,getData: function()
			{
				var data = {};
				var selectedCalcRec = _grids['calculations'].getSelectedRecord();
				var selectedCollRec = _grids['collections'].getSelectedRecord();
				data['guarFeeSummID'] = selectedCollRec.data['guarFeeSummID'];
				data['gwbFeeCollectionID'] = selectedCollRec.data['gwbFeeCollectionID'];
				data['gwbFeeCollectAllocUUID'] = selectedCollRec.data['gwbFeeCollectAllocUUID'];
				data['transNumber'] = selectedCollRec.data['transNumber'];
				data['stmt'] = _popups['cancelColl'].getField('stmt').getValue();
				data['rvcd'] = _popups['cancelColl'].getField('rvcd').getValue();
				data['conf'] = _popups['cancelColl'].getField('conf').getValue();
				data['cancPymnt'] = _popups['cancelColl'].getField('cancPymnt').getValue();
				data['batch'] = selectedCalcRec.data['batch'];
				data['trace'] = selectedCalcRec.data['trace'];
				data['remarks1'] = _popups['cancelColl'].getField('remarks1').getValue();
				data['remarks2'] = _popups['cancelColl'].getField('remarks2').getValue();
				data['remarks3'] = _popups['cancelColl'].getField('remarks3').getValue();
				return data;
			}
		})
	}
			
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields
		
		,buttons: _buttons

		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items:[
				{
					layout: 'column'
					,defaults: {layout: 'form'}
					,items:[
						{
							width: 285
							,labelWidth: 95
							,items: [
								_fields['contractType']
							]
						}
						,{
							width: 290
							,labelWidth: 75
							,items: [
								_fields['feeType']
							]
						}
						,{	
							width: 130
							,style: 'position:relative'
							,items: [
								_buttons.search, _buttons.reset
							]
						}
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['Calculations']
					,items: [
						_grids['calculations']
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['Collections']
					,items: [
						_grids['collections']
					]
				}
			]
		})
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){DesktopWeb.Util.commitScreen();}
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,handler: function(){
					if (_controller.updatesFlag)
					{
						DesktopWeb.Util.displayDiscardPrompt(callback)
					}
					else
					{
						callback(true);
					}
					
					function callback(discard)
					{
						if (discard)
						{
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			})
		]
	}
}