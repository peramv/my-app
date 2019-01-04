/*********************************************************************************************
 * @file	ClassSetup_EventSched.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources file for Event Schedule Setup screen, part of Class Setup flow
 *********************************************************************************************/
 /*
 * History : 
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    20 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030808 T54932 
 *             - Apply Scrollable when screen reach the maximum of layout
 *
 *  30 July 2014 Winnie Cheng P0232644 FN01 T78216
 *             - A new field added from Event Schedule screen for AIFMD enhancement
 *  
 *  09 Nov 2018 Winnie C. R19.2
 *  		P0278169-69 Project Spring:SSII-7422 PIMCO DCCS Trading 
 *			Adding NSCC offset field as minutes within 24 hours
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 750;
	var _layoutWidth = 750;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 15
	})
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({								
		height: 45									
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id)}
		}
	})	
	
	// **** buttons ****
	var _buttons = {
		fundListBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['FundList']
			,handler: function(){
				_controller.openFundListPopup('valn');
			}
			,disabled: true										 																			
		})
		,validateBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Validate']
			,handler: function(){
				_controller.validateValuationFrequency();
			}
			,style: "float:right;" //Set button to align right
			,hidden: true
		})
		,fundList2Btn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['FundList']
			,handler: function(){
				_controller.openFundListPopup('divs');
			}
			,disabled: true										 																			
		})
	}
	
	// **** fields ****
	var _fields = {		
		valn: {
			fundGroup: new DesktopWeb.Controls.ComboBox({
				fieldLabel: _translationMap['FundGroupCode']
				,allowBlank: false
				,store: new Ext.data.XmlStore(
					{
						record: 'ValnFundGroup'					
						,fields: ['fundGroup', 'fundGroupDesc', 'fundLists', 'action', 'busDayCode', 'holidayCode', 'settleHolidayCode', 'additionalDayCode']
					}
				)
				,valueField: 'fundGroup'
				,displayField: 'fundGroup'
				,editable: false
				,anchor: '-20'
				,lastQuery: ''
				,listeners: {
					select: function(combo, record, index)
					{
						_controller.selectFundGroup(record, 'valn');
					}
				}
			})
			,newFundGroup: new DesktopWeb.Controls.TextField({
				emptyText: _translationMap['EnterNewFundGroup']
				,allowBlank: false
				,anchor: '-20'
				,maxLength: 6
			})
			,fundListCb: new DesktopWeb.Controls.ComboBox({
				fieldLabel: _translationMap['List']
				,store: new Ext.data.ArrayStore({
					fields: ['fundCode', 'fundValue']
				})
				,valueField: 'fundCode'
				,displayField: 'fundCode'
				,editable: false
				,anchor: '-150'
			})
			,fundListTxt: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['List']
				,allowBlank: false
				,anchor: '-20'
				,maxLength: 4
			})
			,fundGroupDesc: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['Description']
				,emptyText: _translationMap['EnterNewFundGroupDesc']
				,allowBlank: false
				,width: 300
				,maxLength: 40
			})
			,busDayCode: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['BusinessDayCode']
				,allowBlank: false
				,editable: false
				,width: 175
				,showCode: true
			})
			,holidayCode: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['HolidayCode']
				,allowBlank: false
				,editable: false
				,width: 175
				,showCode: true
			})
			,settleHolidayCode: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['SettlementHolidayCode']
				,allowBlank: true
				,editable: false
				,width: 175
				,showCode: true
			})					
			,additionalDayCode: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['AdditionalDayListCode']
				,allowBlank: true
				,editable: false
				,width: 175
			})					
			,stlCurHldy: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['StlCurHldy']
				,allowBlank: false
				,editable: false
				,width: 95
				,showCode: true
			})					
			,freq: new DesktopWeb.ScreenResources.Frequency({
				frequencyLabel: _translationMap['Frequency']
				,labelWidth: 150
			})	
			,cutOffFundGrp: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['FundGroupLevel']
				,emptyText: _translationMap['HHMM']
				,regex: /^(?:0?\d|1[0-9]|2[0123]):?[0-5]\d$/
				,regexText: _translationMap['InvalidTimeFormat']
				,allowBlank: false
				,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '5'}
				,width: 75
			})
			,cutOffClient: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['ClientLevel']
				,emptyText: _translationMap['HHMM']
				,regex: /^(?:0?\d|1[0-9]|2[0123]):?[0-5]\d$/
				,regexText: _translationMap['InvalidTimeFormat']
				,allowBlank: false
				,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '5'}
				,width: 75
			})
			,cutOffAggregate: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['AggregationLevel']
				,emptyText: _translationMap['HHMM']
				,regex: /^(?:0?\d|1[0-9]|2[0123]):?[0-5]\d$/
				,regexText: _translationMap['InvalidTimeFormat']
				,allowBlank: false
				,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '5'}
				,width: 75
			})
			,cutOffMarket: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['MarketLevel']
				,emptyText: _translationMap['HHMM']
				,regex: /^(?:0?\d|1[0-9]|2[0123]):?[0-5]\d$/
				,regexText: _translationMap['InvalidTimeFormat']
				,allowBlank: false
				,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '5'}
				,width: 75
			})
			,nsccOffSet: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['NSCCOffset']
				,regex: /^[\-]?\d*$/
				,maskRe:/^[\-]?\d*$/
				,allowBlank: true
				,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '5'}
				,width: 75
				,listeners: {
					change: function(fld) {
						fld.isMarkInvalid = false;
						var nsccoffsetValue = fld.getValue().trim();
						if (nsccoffsetValue != '') {
							_controller.validateOffsetmins(nsccoffsetValue);
						}
					}
				}
			})
			,cutOffTimeZone: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['Timezone']
				,allowBlank: false
				,editable: false
				,width: 260
				,showCode: true
			})
		}
		,divs: {
			dividendSchedCheck: new DesktopWeb.Controls.Checkbox({
				boxLabel: _translationMap['DividendSchedule']				
				,listeners: {
					check: function(cb, checked)
					{
						_controller.checkDividend(checked);
					}
				}
			})
			,fundGroup: new DesktopWeb.Controls.ComboBox({
				fieldLabel: _translationMap['FundGroupCode']
				,store: new Ext.data.XmlStore(
					{
						record: 'DivsFundGroup'					
						,fields: ['fundGroup', 'fundGroupDesc', 'fundLists', 'action']
					}
				)
				,valueField: 'fundGroup'
				,displayField: 'fundGroup'
				,editable: false
				,anchor: '-20'
				,lastQuery: ''
				,listeners: {
					select: function(combo, record, index)
					{
						_controller.selectFundGroup(record, 'divs');
					}
				}
			})
			,newFundGroup: new DesktopWeb.Controls.TextField({
				emptyText: _translationMap['EnterNewFundGroup']
				,allowBlank: false
				,anchor: '-20'
				,maxLength: 6
			})
			,fundListCb: new DesktopWeb.Controls.ComboBox({
				fieldLabel: _translationMap['List']
				,store: new Ext.data.ArrayStore({
					fields: ['fundCode', 'fundValue']
				})
				,valueField: 'fundCode'
				,displayField: 'fundCode'
				,editable: false
				,anchor: '-150'
			})
			,fundListTxt: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['List']
				,allowBlank: false
				,anchor: '-20'
				,maxLength: 4
			})
			,fundGroupDesc: new DesktopWeb.Controls.TextField({
				fieldLabel: _translationMap['Description']
				,emptyText: _translationMap['EnterNewFundGroupDesc']
				,allowBlank: false
				,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '40'}
				,width: 300
			})
			,freq: new DesktopWeb.ScreenResources.Frequency({
				frequencyLabel: _translationMap['DividendFrequency']
				,labelWidth: 150
				,freqOnId: _translationMap['dividendFreqOn']// 'Dividend Frequency On'
				,freqTypeId: _translationMap['dividendFreqType']//'Dividend Frequency Type'
				,freqDayId: _translationMap['dividendFreqDay']//'Dividend Frequency Day'
				,freqMonthId: _translationMap['dividendFreqMonth']//'Dividend Frequency Month'
				,freqEndOfId: _translationMap['dividendFreqEndOf']//'Dividend Frequency EndOf' //'dividendFreqEndOf'// 'Dividend Frequency EndOf'
			})
		}
		,crys: {
			freq: new DesktopWeb.ScreenResources.Frequency({
				frequencyLabel: _translationMap['CrystalisationFrequency']
				,disabledFreqOn: true
				,disabledFreqType: true
				,disabledFreqDay: true
				,disabledFreqMonth: false
				,disabledFreqEndOf: true
				,freqOnId: _translationMap['PFFreqOn'] //'PF Crystalisation Frequency On'
				,freqTypeId: _translationMap['PFFreqType'] //'PF Crystalisation Frequency Type'
				,freqDayId: _translationMap['PFFreqDay'] //'PF Crystalisation Frequency Day'
				,freqMonthId: _translationMap['PFFreqMonth'] //'PF Crystalisation Frequency Month'
				,freqEndOfId: _translationMap['PFFreqEndOf'] //'PF Crystalisation Frequency EndOf'
			})
		}
		
		,redemptionDealingFreq: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['RedemptionDealingFreq']
			,allowBlank: true
			,width: 175
			,showCode: true
		})
	}
	
	// **** forms ****
	var _forms = {
		valnFundGroupForm: new Ext.Container({
			id: 'valnFundGroupForm'
			,layout: 'hbox'
			,width: 300
			,items: [
				{
					layout: 'form'
					,labelWidth: 25
					,items: [
						_fields['valn']['fundListCb']
					]
				}
			]
		})
		,valnNewFundGroupForm: new Ext.Container({
			id: 'valnNewFundGroupForm'
			,layout: 'hbox'
			,hidden: true
			,width: 300
			,items: [
				{
					layout: 'form'
					,hideLabels: true
					,width: 150
					,items: [
						_fields['valn']['newFundGroup']
					]
				}
				,{
					layout: 'form'
					,width: 150
					,labelWidth: 25
					,items: [
						_fields['valn']['fundListTxt']
					]
				}
			]
		})
		,divsFundGroupForm: new Ext.Container({
			id: 'divsFundGroupForm'
			,layout: 'hbox'
			,width: 300
			,items: [
				{
					layout: 'form'
					,labelWidth: 25
					,items: [
						_fields['divs']['fundListCb']
					]
				}
			]
		})
		,divsNewFundGroupForm: new Ext.Container({
			id: 'divsNewFundGroupForm'
			,layout: 'hbox'
			,hidden: true
			,width: 300
			,items: [
				{
					layout: 'form'
					,hideLabels: true
					,width: 150
					,items: [
						_fields['divs']['newFundGroup']
					]
				}
				,{
					layout: 'form'
					,width: 150
					,labelWidth: 25
					,items: [
						_fields['divs']['fundListTxt']
					]
				}
			]
		})
	}


	// **** grids ****
	var _grids = {
		dealingSched: new DesktopWeb.AdvancedControls.GridPanel(
			{														
				autoScroll: true							
				,height: 150
				,hidden: false
				,autoExpandColumn: 'transType'									
				,store: new Ext.data.XmlStore(
					{
						record: 'DealSchedDetl'
						,fields: ['freqUUID', 'transType', 'freqOn', 'freqType', 'freqDay', 'freqMonth', 'freqEndOf', 'runMode', 'version']
						,listeners: {
							load: function(store, records)
							{															
								store.filterBy(function(record){return record.data.runMode != _controller.DEL});
							}
							,update: function(store)
							{								
								store.filterBy(function(record){return record.data.runMode != _controller.DEL});
							}																			
						}			
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.selectDealing(record);
								}
							}
						}
				})				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns: [
						{id: 'transType', header: _translationMap['TransType'], dataIndex: 'transType', width: 100
							,renderer: function(val){
								var display = ''
								if(val)
								{
									var transTypes = val.split(',');
									Ext.each(transTypes, function(transType){
										display += _controller.getValueDescFromList('dealTransType', transType) + ",";
									});
									display = display.substring(0, display.length-1);
								}
								
								return display;
							}
						}
						,{header: _translationMap['Frequency'], dataIndex: 'freqOn'
							,renderer: function(val){
								return (val ? _controller.getValueDescFromList('freqOn', val) : '');
							}
						}
						,{header: '', dataIndex: 'freqType', width: 125
							,renderer: function(val){
								return (val ? _controller.getValueDescFromList('freqType', val) : '');
							}
						}
						,{header: '', dataIndex: 'freqDay', width: 125
							,renderer: function(val){
								return (val ? _controller.getValueDescFromList('freqDay', val) : '');
							}
						}
						,{header: '', dataIndex: 'freqMonth', width: 125
							,renderer: function(val){
								return (val ? _controller.getValueDescFromList('freqMonth', val) : '');
							}
						}
						,{header: '', dataIndex: 'freqEndOf', width: 125
							,renderer: function(val){
								return (val ? _controller.getValueDescFromList('freqEndOf', val) : '');
							}
						}
					]		
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'
						,text: _translationMap['Add']
						,handler: function(){
							_controller.openActionPopup(_popups['dealingUpd'], _controller.ADD)
						}														
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'								
						,text: _translationMap['Modify']
						,handler: function(){
							_controller.openActionPopup(_popups['dealingUpd'], _controller.MOD)
						}													
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'								
						,text: _translationMap['Delete']
						,handler: function(){
							_controller.openActionPopup(_popups['dealingDel'], _controller.DEL)
						}													
					})
				]			
			}
		)
		,fundClassList: new DesktopWeb.AdvancedControls.GridPanel(
			{														
				autoScroll: true							
				,height: 250
				,hidden: false
				,autoExpandColumn: 'name'									
				,store: new Ext.data.XmlStore(
					{
						record: 'FundDetl'
						,fields: ['fundCode', 'classCode', 'fundClassName']
					}
				)
				,selModel: new Ext.grid.RowSelectionModel({					
						singleSelect: true
				})				
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
					}
					,columns: [
						{header: _translationMap['Fund'], dataIndex: 'fundCode', width: 50}
						,{header: _translationMap['Class'], dataIndex: 'classCode', width: 50}
						,{id: 'name', header: _translationMap['Name'], dataIndex: 'fundClassName'}
					]		
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'closeBtn'								
						,text: _translationMap['Close']
						,handler: function(){
							_popups['fundClassList'].hide();
						}													
					})
				]			
			}
		)
	}
	
	// **** selectors ****
	var _selectors = {
		transType: new DesktopWeb.AdvancedControls.ItemSelector(
			{
				height: 150
				,width: 400
				,allowReordering: false
				,availableGridProperties: {
					title: ''
					,width: 140
					,store: new Ext.data.XmlStore(
						{
							record: 'Element'
							,fields: ['code', 'value']
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{id: 'transtype', dataIndex: 'value', width: 115}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true
						}
					)
					
				}
				,selectedGridProperties: {
					width: 140
					,store: new Ext.data.XmlStore(
						{
							record: 'Element'
							,fields: ['code', 'value']
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{id: 'segment', dataIndex: 'value', width: 115}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true
						}
					)
				}
			}
		)
	}

	var _tabs = {
		scheduleTab: new Ext.TabPanel({
			itemId: 'scheduleTab'
			,activeTab: 0
			,border: false
			,plain: true
			,defaults: {
				layout: 'form'
				,border: true
				,autoHeight: true
			}
			,items: []
		})
	}
	
	// **** tabs ****
	var _panels = {
		dividendSchedPanel: new Ext.Panel({
			title: _translationMap['DividendSchedule']
			,layout: 'form'
			,border: true
			,items: [
				{
					xtype: 'fieldset'
					,title: ''
					,height: 150
					,style: 'padding-left: 5px; padding-top: 10px;'
					,items:[
						{
							layout: 'form'
							,id: 'dividendSchedForm'
							,labelWidth: 150
							,items: [
								new Ext.Container({
									id: 'divsFundGroupContainer'										
									,layout: 'hbox'
									,items: [						
										{
											layout: 'form'
											,width: 300
											,labelWidth: 150
											,items: [
												_fields['divs']['fundGroup']
											]
										}
										,{
											layout: 'form'
											,width: 300
											,items: [
												
												_forms['divsFundGroupForm']
												,_forms['divsNewFundGroupForm']
											]
										}
										,{
											layout: 'form'
											,width: 175
											,labelWidth: 25
											,items: [
												_buttons['fundList2Btn']
											]
										}
									]
								})	
								,{
									layout: 'form'
									,id: 'dividendSchedForm2'
									,labelWidth: 150
									,items: [
										_fields['divs']['fundGroupDesc']
										,_fields['divs']['freq']
									]
								}
							]
						}
					]
				}
			]
			,disablePanel: function()
			{
				Ext.getCmp("dividendSchedForm").disable();
				_fields['divs']['fundGroup'].disableField();
				_fields['divs']['newFundGroup'].disableField();
				_fields['divs']['fundListCb'].disableField();
				_buttons['fundList2Btn'].disable();
				_fields['divs']['fundGroupDesc'].disableField();
				_fields['divs']['freq'].disableAllFrequencies();
			}
			,enablePanel: function()
			{
				Ext.getCmp("dividendSchedForm").enable();
				_fields['divs']['fundGroup'].enableField();
				_fields['divs']['newFundGroup'].enableField();
				_fields['divs']['fundListCb'].enableField();
				_buttons['fundList2Btn'].enable();
				_fields['divs']['fundGroupDesc'].enableField();
				_fields['divs']['freq'].enableAllFrequencies();
			}
			,resetPanel: function()
			{
				Ext.getCmp("dividendSchedForm").enable();
				_fields['divs']['fundGroup'].action = '';
				_fields['divs']['fundGroup'].reset();

				_fields['divs']['newFundGroup'].reset();
				_fields['divs']['fundListTxt'].reset();
				_forms['divsNewFundGroupForm'].hide();

				_fields['divs']['fundListCb'].reset();
				_fields['divs']['fundListCb'].getStore().removeAll();
				_forms['divsFundGroupForm'].show();
				
				_buttons['fundList2Btn'].disable();
				_fields['divs']['fundGroupDesc'].reset();
				_fields['divs']['freq'].clearFrequency();
			}
			,clearInvalid: function()
			{
				_fields['divs']['fundGroup'].clearInvalid();
				_fields['divs']['newFundGroup'].clearInvalid();
				_fields['divs']['fundListTxt'].clearInvalid();
				_fields['divs']['fundListCb'].clearInvalid();
				_fields['divs']['fundGroupDesc'].clearInvalid();
				_fields['divs']['freq'].clearInvalidChildren();
			}
			,readyPanel: function()
			{
				this.resetPanel();
				Ext.getCmp("dividendSchedForm").enable();
				_fields['divs']['fundGroup'].enableField();
				_fields['divs']['fundListCb'].disableField();
				_buttons['fundList2Btn'].disable();
				_fields['divs']['fundGroupDesc'].disableField();
				_fields['divs']['freq'].disableAllFrequencies();
			}
		})
		,crystalSchedPanel: new Ext.Panel({
			title: _translationMap['CrystalisationSchedule']
			,layout: 'form'
			,border: false
			,items: [
				{
					xtype: 'fieldset'
					,title: ''
					,height: 100
					,style: 'padding-left: 5px; padding-top: 10px;'
					,items:[
						{
							layout: 'form'
							,id: 'crysSchedForm'
							,labelWidth: 170
							,items: [
								_fields['crys']['freq']
							]
						}
					]
				}
			]
			,disablePanel: function()
			{
				Ext.getCmp("crysSchedForm").disable();
				_fields['crys']['freq'].disableAllFrequencies();
			}
			,enablePanel: function(){
				Ext.getCmp("crysSchedForm").enable();
				_fields['crys']['freq'].disableFrequencies(true, true, true, false, true);
			}
			,resetPanel: function(){
				Ext.getCmp("crysSchedForm").enable();
				_fields['crys']['freq'].clearFrequency();
				_fields['crys']['freq'].disableFrequencies(true, true, true, false, true);
			}
		})
		,dealingSchedPanel: new Ext.Panel({
			title: _translationMap['DealingSchedule']
			,layout: 'form'
			,border: false
			,items: [
				{
					xtype: 'fieldset'
					,title: ''
					,height: 165
					,style: 'padding-left: 5px; padding-top: 10px;'
					,items:[
						{
							layout: 'form'
							,id: 'dealSchedForm'
							,labelWidth: 150
							,items: [
								_grids['dealingSched']
							]
						}
					]
				}
			]
			,disablePanel: function()
			{
				Ext.getCmp("dealSchedForm").disable();
				_grids['dealingSched'].getSelectionModel().lock();
				_grids['dealingSched'].disableAllButtons();
			}
			,enablePanel: function(){
				Ext.getCmp("dealSchedForm").enable();
				_grids['dealingSched'].getSelectionModel().unlock();
				_controller.updateDealingSchedButtons();
			}
			,resetPanel: function(){
				Ext.getCmp("dealSchedForm").enable();
				_grids['dealingSched'].getStore().removeAll();
				_controller.updateDealingSchedButtons();
			}
		})
	}

	
	// **** popups ****
	var _popups = {
		dealingUpd: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,dealingSchedUUID: null
				,title: _translationMap['DealingSchedule']
				,width: 675
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{						
						layout: 'form'
						,defaults: {border: false}
						,labelWidth: 60
						,items: [
							{
								layout: 'column'
								,defaults: {
									layout: 'form'
									,border: false
									,style: 'padding-top:10px; padding-left:10px; padding-bottom:10px;'
								}
								,items: [
									{
										columnWidth: 0.125
										,items: [
											new DesktopWeb.Controls.Label(
												{
													fieldLabel: _translationMap['TransType']
												}
											)
										]
									}
									,{
										columnWidth: 0.875
										,items: [
											_selectors['transType']
										]
									}
								]
							}
							,{
								layout: 'form'
								,border: false
								,style: 'padding-left:10px; padding-bottom:10px;'
								,items: [
									new DesktopWeb.ScreenResources.Frequency({
										itemId: 'dealingFreq'
										,frequencyLabel: _translationMap['Frequency']
										,labelWidth: 75
										,disabledFreqOn: true
										,disabledFreqType: true
										,disabledFreqDay: true
										,disabledFreqMonth: false
										,disabledFreqEndOf: true
										,freqOnId: _translationMap['dealingFreqOn'] //'Dealing Frequency On'
										,freqTypeId: _translationMap['dealingFreqType'] //'Dealing Frequency Type'
										,freqDayId: _translationMap['dealingFreqDay'] //'Dealing Frequency Day'
										,freqMonthId: _translationMap['dealingFreqMonth'] //'Dealing Frequency Month'
										,freqEndOfId: _translationMap['dealingFreqEndOf'] //'Dealing Frequency EndOf'
									})
								]
							}
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: 'OK'
							,handler: function(){
								_controller.saveDealingFrequency(_popups['dealingUpd'], _popups['dealingUpd'].getData());
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: 'Cancel'
							,handler: function(){_popups['dealingUpd'].hide();}
						}
					)
				]
				,init: function(action)
				{
					// initialize popup based on action
					this.action = action;
					this.dealingSchedUUID = (action == _controller.ADD)?'tmpDealingSchedUUID' + _controller.getNextTempDealingUUID():_grids['dealingSched'].getSelectedRecord().get('freqUUID');
					switch (action)
					{
						case _controller.ADD:
							this.setTitle(_translationMap['DealingSchedule'] + ' - ' + _translationMap['Add']);
							break;
						case _controller.MOD:
							this.setTitle(_translationMap['DealingSchedule'] + ' - ' + _translationMap['Modify']);
							break;
					}
					this.populate(action);
				}
				,populate: function(action)
				{
					switch (action)
					{
						case _controller.ADD:
							this.loadTransTypeSelector();
							this.getField('dealingFreq').clearFrequency();
							_controller.populateFrequencyByValuationFrequency(this.getField('dealingFreq'));
							break;
						case _controller.MOD:
							var selectedRecord = _grids['dealingSched'].getSelectedRecord();
							this.loadTransTypeSelector(selectedRecord);
							this.getField('dealingFreq').setFrequency(
								selectedRecord.get('freqOn')
								,selectedRecord.get('freqType')
								,selectedRecord.get('freqDay')
								,selectedRecord.get('freqMonth')
								,selectedRecord.get('freqEndOf')
							);
							break;
					}
				}
				,loadTransTypeSelector: function(selectedRecord)
				{
					_selectors['transType'].availableGrid.clearData();
					_selectors['transType'].selectedGrid.clearData();
					_controller.loadAvailableTransTypeSelector();
					
					if(selectedRecord)
					{
						_selectors['transType'].setSelectedByData('code',  selectedRecord.get('transType').split(','));
					}
					
					var dealingRecords = _grids['dealingSched'].getStore().queryBy(
						function(record){
							return (record.get('runMode') != _controller.DEL && record.get('freqUUID') != _popups['dealingUpd'].dealingSchedUUID);
						}
					);
					for(i = 0; i < dealingRecords.length; i++)
					{
						var transTypes = dealingRecords.itemAt(i).get('transType').split(',');
						Ext.each(transTypes, function(tranType){
							var transTypeRecords = _selectors['transType'].availableGrid.getStore().query('code', tranType);
							for (j = 0; j < transTypeRecords.length; j++){
								_selectors['transType'].availableGrid.getStore().remove(transTypeRecords.itemAt(j));
							}
						});
					}
				}
				,getData: function()
				{
					var data = {};
					var dealingFreq = this.getField('dealingFreq').getFrequency();

					var transTypes = '';
					var selectedTranTypes = _selectors['transType'].getSelectedRecords();
					Ext.each(selectedTranTypes, function(record){
						transTypes += record.get('code') + ',';
					});
					
					transTypes = transTypes.substring(0, transTypes.length - 1);

					data['freqUUID'] = this.dealingSchedUUID;
					data['runMode'] = this.action;
					data['transType'] = transTypes;
					data['freqOn'] = dealingFreq['on'];
					data['freqType'] = dealingFreq['type'];
					data['freqDay'] = dealingFreq['day'];
					data['freqMonth'] = dealingFreq['month'];
					data['freqEndOf'] = dealingFreq['endOf'];
					return data;
				}
			}
		)
		,dealingDel:  new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,title: 'Dealing Schedule - Delete'
				,width: 350
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						html: "Are you sure you want to delete this record?"
						,style: 'text-align:center;font-weight:bold;'
					}
					,{						
						layout: 'form'
						,defaults: {border: false}
						,style: 'padding-top:10px; padding-left:10px; padding-bottom:10px;'
						,labelWidth: 100
						,items: [
							new DesktopWeb.Controls.Label(
								{
									itemId: 'transType'
									,fieldLabel: _translationMap['TransType']
									,width: 175
								}
							)
							,new DesktopWeb.Controls.TextField(
								{
									itemId: 'freqOn'
									,fieldLabel: _translationMap['Frequency']
									,width: 175
									,disabled: true
								}
							)
							,new DesktopWeb.Controls.TextField(
								{
									itemId: 'freqType'
									,fieldLabel: ''
									,width: 175
									,disabled: true
								}
							)
							,new DesktopWeb.Controls.TextField(
								{
									itemId: 'freqDay'
									,fieldLabel: ''
									,width: 175
									,disabled: true
								}
							)
							,new DesktopWeb.Controls.TextField(
								{
									itemId: 'freqMonth'
									,fieldLabel: ''
									,width: 175
									,disabled: true
								}
							)
							,new DesktopWeb.Controls.TextField(
								{
									itemId: 'freqEndOf'
									,fieldLabel: ''
									,width: 175
									,disabled: true
								}
							)
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: 'OK'
							,handler: function(){
								_controller.saveDealingFrequency(_popups['dealingDel'], _popups['dealingDel'].getData());
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: 'Cancel'
							,handler: function(){_popups['dealingDel'].hide();}
						}
					)
				]
				,init: function(action)
				{
					// initialize popup based on action
					this.action = action;
					this.populate(_grids['dealingSched'].getSelectedRecord());
				}
				,populate: function(record)
				{
					var display = '';
					var transTypes = record.get('transType').split(',');
					Ext.each(transTypes, function(transType){
						display += _controller.getValueDescFromList('dealTransType', transType) + ",";
					});
					display = display.substring(0, display.length-1);
					
					this.getField('transType').setValue(display);
					this.getField('freqOn').setValue(_controller.getValueDescFromList('freqOn', record.get('freqOn')));
					this.getField('freqType').setValue(_controller.getValueDescFromList('freqType', record.get('freqType')));
					this.getField('freqDay').setValue(_controller.getValueDescFromList('freqDay', record.get('freqDay')));
					this.getField('freqMonth').setValue(_controller.getValueDescFromList('freqMonth', record.get('freqMonth')));
					this.getField('freqEndOf').setValue(_controller.getValueDescFromList('freqEndOf', record.get('freqEndOf')));
				}
				,getData: function()
				{
					var data = {};
					var dealingRecord = _grids['dealingSched'].getSelectedRecord();
					
					data['runMode'] = this.action;
					data['transType'] = dealingRecord.get('transType');
					data['freqOn'] = dealingRecord.get('freqOn');
					data['freqType'] = dealingRecord.get('freqType');
					data['freqDay'] = dealingRecord.get('freqDay');
					data['freqMonth'] = dealingRecord.get('freqMonth');
					data['freqEndOf'] = dealingRecord.get('freqEndOf');
					return data;
				}
			}
		)
		,fundClassList:  new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,title: 'Fund Classes List'
				,width: 450
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{						
						layout: 'form'
						,defaults: {border: false}
						,style: 'padding-top:5px; padding-left:5px; padding-right:5px;'
						,labelWidth: 100
						,items: [_grids['fundClassList']]	
					}
				]
				,buttons: []
				,init: function(schedType)
				{
					// initialize popup based on action
					var popup = _popups['fundClassList'];
					switch (schedType)
					{
						case 'valn':
							popup.setTitle(_translationMap['FundClassList'] + ' - ' + _fields['valn']['fundGroup'].getValue() + ' ' + _translationMap['ValuationFundGroup']);
							break;
						case 'divs':
							popup.setTitle(_translationMap['FundClassList'] + ' - ' + _fields['divs']['fundGroup'].getValue() + ' ' + _translationMap['DividendFundGroup']);
							break;
						default:
							popup.setTitle(_translationMap['FundClassList'] + ' - ' + _fields['valn']['fundGroup'].getValue());
					}
				}
			}
		)
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,buttons: _buttons
		
		,fields: _fields
		
		,forms: _forms
		
		,grids: _grids
		
		,selectors: _selectors
		
		,tabs: _tabs
		
		,panels: _panels
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth - 18  
				,items: [
					_header
					,_breadCrumbList
					,new Ext.Container({
						style: 'padding-left:12px; padding-right:10px; padding-bottom:50px;overflow-y:auto;'
						,autoScroll: true
						,height: 600
						,labelWidth: 150
						,items: [
							{
								xtype: 'fieldset'
								,title: _translationMap['ValuationSchedule']
								,items: [
									new Ext.Container({
										id: 'fundContainer'										
										,layout: 'hbox'
										,items: [						
											{
												layout: 'form'
												,id: 'fundGroupForm'
												,width: 300
												,items: [
													_fields['valn']['fundGroup']
												]
											}
											,{
												layout: 'form'
												,width: 300
												,items: [
													
													_forms['valnFundGroupForm']
													,_forms['valnNewFundGroupForm']
												]
											}
											,{
												layout: 'form'
												,id: 'fundListForm'
												,width: 175
												,labelWidth: 25
												,items: [
													_buttons['fundListBtn']
												]
											}
										]
									})					
									,{
										layout: 'form'
										,id: 'valnSchedForm'
										,items: [
											_fields['valn']['fundGroupDesc']
											,{
												layout: 'column'
												,defaults: {
													layout: 'form'
													,border: false
													,columnWidth: 0.5
												}
												,items: [
													{
														items: [
															_fields['valn']['busDayCode']
															,_fields['valn']['settleHolidayCode']
															,_fields['valn']['stlCurHldy']
														]
													},
													{
														items: [
															_fields['valn']['holidayCode']
															,_fields['valn']['additionalDayCode']
														]
													}
												]
											}
											,_fields['valn']['freq']
											,{
												xtype: 'fieldset'
												,title: _translationMap["CutOffTime"]
												,style: 'padding-bottom: 10px'
												,items: [
													{
														layout: 'column'
														,defaults: {
															layout: 'form'
															,border: false
														}
														,items: [
															{
																columnWidth: 0.4
																,labelWidth: 145
																,items: [
																	_fields['valn']['cutOffFundGrp']
																	,_fields['valn']['cutOffClient']
																	,_fields['valn']['cutOffMarket']
																]
															}
															,{
																columnWidth: 0.6
																,labelWidth: 125
																,items: [
																	_fields['valn']['cutOffTimeZone']
																	,_fields['valn']['cutOffAggregate']
																	,_fields['valn']['nsccOffSet']
																
																]
															}
														]
													}
												]
											}
											,{
												layout: 'form'
												,border: false
												,style: 'padding-bottom: 10px'
												,items: [
													_buttons['validateBtn']
												]
											}
										]
									}
								]
							}
							,{
								layout: 'form'
								,border: false
								,style: 'padding-bottom: 5px'
								,items: [
									_fields['divs']['dividendSchedCheck']
								]
							}
							,_tabs['scheduleTab']
							,{
								layout: 'form'
								,border: false
								,style: 'padding-bottom: 5px'
								,items: [
									_fields['redemptionDealingFreq']
								]
							}
						]	
					})
				]
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Previous']
				,hidden: true
				,disabled: true				
				,id: 'prevBtn'
				,handler: function(){
					_controller.previous();
				}				
			})				
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Save']
				,id: 'saveBtn'
				,disabled: true
				,handler: function(){
					_controller.save();	
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Reset']
				,id: 'resetBtn'
				,disabled: true
				,handler: function(){
					_controller.reset();	
				}								
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Cancel']
				,hidden: true				
				,id: 'cancelBtn'
				,handler: function(){
					_controller.cancel();
				}				
			})								
			,new DesktopWeb.Controls.ScreenButton({
				text: ''
				,hidden: true				
				,id: 'nextBtn'
				,handler: function(){
					_controller.next();
				}				
			})
			,new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['ReturntoSummary']
				,hidden: true				
				,id: 'summaryBtn'
				,handler: function(){
					_controller.changeScreen('Summary');
				}				
			})
		]			
	}
}

DesktopWeb.ScreenResources.Frequency = Ext.extend( Ext.form.CompositeField, {
	frequencyLabel: 'New Freq'
	,combineErrors: true
	,width: 520
	,msgTarget: 'side'
	,disabledFreqOn: false
	,disabledFreqType: false
	,disabledFreqDay: false
	,disabledFreqMonth: false
	,disabledFreqEndOf: false

	,initComponent: function()
	{
		this.freqOn = new DesktopWeb.Controls.SMVComboBox({
			width: 95
			,id: this.freqOnId
			,editable: false
			,lastQuery: ''
		});
		this.freqType = new DesktopWeb.Controls.SMVComboBox({
			width: 75
			,id: this.freqTypeId
			,editable: false
			,lastQuery: ''
		});
		this.freqDay = new DesktopWeb.Controls.SMVComboBox({
			width: 90
			,id: this.freqDayId
			,editable: false
			,lastQuery: ''
		});
		this.freqMonth = new DesktopWeb.Controls.SMVComboBox({
			width: 110
			,id: this.freqMonthId
			,editable: false
			,lastQuery: ''
		});
		this.freqEndOf = new DesktopWeb.Controls.SMVComboBox({
			width: 110
			,id: this.freqEndOfId
			,editable: false
			,lastQuery: ''
		});
		
		if (this.disabledFreqOn) this.freqOn.disableField();
		if (this.disabledFreqType) this.freqType.disableField();
		if (this.disabledFreqDay) this.freqDay.disableField();
		if (this.disabledFreqMonth) this.freqMonth.disableField();
		if (this.disabledFreqEndOf) this.freqEndOf.disableField();
		
		var config = {
			fieldLabel: this.frequencyLabel
			,items: [
				this.freqOn
				,this.freqType
				,this.freqDay
				,this.freqMonth
				,this.freqEndOf
			]
		}

		Ext.apply(this, Ext.apply(this.initialConfig, config));	
		DesktopWeb.ScreenResources.Frequency.superclass.initComponent.apply(this, arguments);
	}
	
	,onRender: function(ct, position)
	{
		DesktopWeb.ScreenResources.Frequency.superclass.onRender.call(this, ct, position);
	}
	
	,loadData: function(listData1, listData2, listData3, listData4, listData5)
	{
		this.freqOn.loadData(listData1);
		this.freqType.loadData(listData2);
		this.freqDay.loadData(listData3);
		this.freqMonth.loadData(listData4);
		this.freqEndOf.loadData(listData5);
	}
	
	,setFrequency: function(freqOn, freqType, freqDay, freqMonth, freqEndOf)
	{
		setDefaultValue(this.freqOn, freqOn, 'freqOn');
		setDefaultValue(this.freqType, freqType, 'freqType');
		setDefaultValue(this.freqDay, freqDay, 'freqDay');
		setDefaultValue(this.freqMonth, freqMonth, 'freqMonth');
		setDefaultValue(this.freqEndOf, freqEndOf, 'freqEndOf');
		
		function setDefaultValue(obj, val){
			if (obj.getStore().find('code', val) != -1) 
			{
				obj.setValue(val);
			}else{
				obj.setValue('');
			}
		}
	}
	
	,clearFrequency: function()
	{
		this.freqOn.reset();
		this.freqType.reset();
		this.freqDay.reset();
		this.freqMonth.reset();
		this.freqEndOf.reset();
	}
	
	,disableAllFrequencies: function()
	{
		this.freqOn.disableField();
		this.freqType.disableField();
		this.freqDay.disableField();
		this.freqMonth.disableField();
		this.freqEndOf.disableField();
	}
	
	,enableAllFrequencies: function()
	{
		this.freqOn.enableField();
		this.freqType.enableField();
		this.freqDay.enableField();
		this.freqMonth.enableField();
		this.freqEndOf.enableField();
	}
	
	,disableFrequencies: function(freqOnDisable, freqTypeDisable, freqDayDisable, freqMonthDisable, freqEndOfDisable)
	{
		if (freqOnDisable)
		{
			this.freqOn.disableField();
		}else{
			this.freqOn.enableField();
		}
		
		if (freqTypeDisable)
		{
			this.freqType.disableField();
		}else{
			this.freqType.enableField();
		}

		if (freqDayDisable)
		{
			this.freqDay.disableField();
		}else{
			this.freqDay.enableField();
		}

		if (freqMonthDisable)
		{
			this.freqMonth.disableField();
		}else{
			this.freqMonth.enableField();
		}

		if (freqEndOfDisable)
		{
			this.freqEndOf.disableField();
		}else{
			this.freqEndOf.enableField();
		}
		
	}
	
	,getFrequency: function()
	{
		var frequency = {};
		frequency['on'] = this.freqOn.getValue();
		frequency['type'] = this.freqType.getValue();
		frequency['day'] = this.freqDay.getValue();
		frequency['month'] = this.freqMonth.getValue();
		frequency['endOf'] = this.freqEndOf.getValue();
		return frequency;
	}
	
	,addFrequencyListener: function(eventName, handler)
	{
		this.freqOn.addListener(eventName, handler);		
		this.freqType.addListener(eventName, handler);	
		this.freqDay.addListener(eventName, handler);	
		this.freqMonth.addListener(eventName, handler);	
		this.freqEndOf.addListener(eventName, handler);	
	}
	
	,getFrequencyOn: function()
	{
		return this.freqOn;
	}
	
	,getFrequencyType: function()
	{
		return this.freqType;
	}
	
	,getFrequencyDay: function()
	{
		return this.freqDay;
	}
	
	,getFrequencyMonth: function()
	{
		return this.freqMonth;
	}
	
	,getFrequencyEndOf: function()
	{
		return this.freqEndOf;
	}
});
