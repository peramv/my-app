/*********************************************************************************************
 * @file	ClassSetup_PriceInfo.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Price Information screen, part of Class Setup flow
 *********************************************************************************************/
 /*
 * Procedure: ClassSetup_PriceInfo.Resources.js
 *
 * Purpose  : Price information screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Price information screens
 *
 * History  : 
 *  10 Dec 2015 Winnie Cheng P0248498 CHG0043235 T81863
 *          - Adding one dropdown field : capstock rate type
 *           
 *  30 Mar 2018 Winnie Cheng P0275379-35 MMFR R18.4
 *          - Adding validation for fixed Rate based on fixed price flag
 *          
 *  07 May 2018 Pao - Supareuk S.
 *  		Field alignment adjustment. A load group field was not align with its label
 *
 *  23 July 2018 Winnie Cheng P0277183-158 Intraday Pricing R18.5
 *          - Allowing to set up intraday pricing set when applicable
 *
 *  10 August 2018 Winnie Cheng P0277183-213 DFT0085572 Intraday Pricing R18.5
 *          - APE layout is off
 *     
 *  16 Aug 2018 Winnie Cheng P0275379-220 MMFR R18.4 DFT0085747
 *  		FixRate validation allow zero 0 value when FixPrice is Yes
 *     
 *  17 Aug 2018 Winnie Cheng P0277138-220 MMFR R18.5 DFT0085748
 *  		Intraday PopUp pricePoint field layout is not aligned with Price Code field
 *          
 *  22 Aug 2018 Winnie Cheng P0275379-221 MMFR R18.5 DFT0085956
 *  		Intraday PopUp pricePoint field values needs to be reset if one of value is blank 
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 660;
	var _layoutWidth = 750;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px; padding-bottom: 8px;'
		,height: 15
	})			
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({						
		height: 45				
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id)}
		}
	})			
	
	// **** fields ****
	var _fields = {				
		currency: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['NAVCurrency']
			,allowBlank: false
			,width: 180
			,showCode: true	
		})
		,validSettleCurr: new DesktopWeb.Controls.TextField({
			readOnly: true
			,width: 200		
		})
		,schedTransType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['CustomValuation']
			,width: 100
		})
		,esgPriceSuppress: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['ESGPriceSuppress']
		})
		,gavApply: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['GAVPricing']
			,allowBlank: false
			,autoSelect: true
			,width: 270
			,showCode: true	
		})
		,fixPrice: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['FixedPrice']
			,allowBlank: false
			,width: 75
			,listeners: {
				select: function(fld) {
					_controller.validatefixPriceRateflds('no');
				}
			}			
		})
		,fixRate: new DesktopWeb.Controls.TextField({
			fieldLabel: _translationMap['FixedRate']	
			,allowBlank: false
			,enableKeyEvents: true
		    ,maskRe: /^[0-9,]*\.?[0-9,]*$/ //allowing digits decimal one dot only
			,regex:  /^[0-9,]*\.?[0-9,]*$/ 
			,validationEvent: false
			,isMarkInvalid: false
			,listeners: {
				keyup: function(fld, event) {
					fld.clearInvalid();
					if(_controller.isKeycodeAccept(event.keyCode)) {
						_controller.fixRateDataUpdate(fld.getValue().trim())
					}
				}
				,change: function(fld) {//paste without triggering any key
					fld.isMarkInvalid = false;
					_controller.fixRateDataUpdate(fld.getValue().trim());
				}
			}
		})
		,ratePrecision: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['FixedPrecision']			
			,allowDecimals: false
			,allowBlank: false
			,maxValue: 10
			,width: 50
		})	
		,capstockRateType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['CapStockFXRateType']
			,allowBlank: true
			,autoSelect: true
			,width: 120
			,showCode: true	
		})
		,priceVarAmt: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['VarianceAmount']
			,width: 80
		})
		,priceVarType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['VarianceType']
			,width: 100			
		})		
		,loadGrp: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['LoadGroup']
			,width: 100
            ,showCode: true				
		})
		
		,unitsCalc: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['CalculationMethod']
			,width: 265
			,allowBlank: false
            ,showCode: true				
		})
		,unitsPrecision: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['Precision']
			,allowDecimals: false
			,width: 50
			,allowBlank: false		
			,allowNegative: false
			,minValue: 0
			,maxValue: 4
		})
	
		,roundFlag: new DesktopWeb.Controls.SMVComboBox({
			width: 163
			,fieldLabel: _translationMap['RoundFlag']
			,allowBlank: false
			,autoSelect: true
			,showCode: true	
		})
		,fractionalShr: new DesktopWeb.Controls.YesNoComboBox({
			fieldLabel: _translationMap['FractionalShares']
			,allowBlank: false
		})
		,allocType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AllocatedType']
			,width: 120			
		})	
	}
	
	var _field = {
		intraPriceAct: new DesktopWeb.Controls.TextField({
			itemId: 'intraPriceAct'
			,fieldLabel: _translationMap['PricePointActive']	
			,disabled: true
			,width: 75
		})
	}
	
	// **** grids ****
	var _grids = {
		intradayPricing: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true
			,height: 170
			,store: new Ext.data.XmlStore({
				record: 'intraDayPricing'
				,fields: ['startDate', 'endDate', 'pricePointCnt','intraDayPricingUUID', 'runMode', 'intraDayPricingPoints'
						  ,'userName', 'processDate', 'modUser', 'modDate']
				,listeners: {
					load: function(store, records) {
						Ext.each(records, function(record){
							record.data.startDate = DesktopWeb.Util.getDateDisplayValue(record.data.startDate);
							record.data.endDate = DesktopWeb.Util.getDateDisplayValue(record.data.endDate);
						});

						store.fireEvent('datachanged', store); //to set data in grid again
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL}
						);
					}
					,update: function(store, records) {
						store.filterBy(function(record){
						return record.data.runMode != _controller.DEL});
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({					
					singleSelect: true
					,listeners: {												
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.selectIntradayPrice(record);
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
						{header: _translationMap['EffectiveFrom'], dataIndex: 'startDate', width: 115}						
						,{header: _translationMap['EffectiveTo'], dataIndex: 'endDate', width: 110}
						,{header: _translationMap['NumOfPoints'], dataIndex: 'pricePointCnt', width: 95}
					]		
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']					
					,handler: function(){_controller.openPointsPopup(_controller.ADD);}		
					,disabled: false
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'								
					,text: _translationMap['Modify']	
					,disabled: true
					,handler: function(){_controller.openPointsPopup(_controller.MOD)}													
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'		
					,text: _translationMap['Delete']					
					,handler: function(){_controller.openPointsPopup(_controller.DEL)}	
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'								
					,text: _translationMap['Admin']		
					,disabled: true
					,handler: function(){_controller.openAdminPopup();}										
				})
			]			
		})
		,intraDayPricingPoint: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true
			,height: 160
			,store: new Ext.data.XmlStore({
				record: 'intraDayPricingPoint'
				,fields: ['priceCode', 'timePoint', 'usedForDivPricing', 'intraDayPriceInstrUUID', 'pricingPointUUID']
				,listeners: {
					load: function(store, records) {
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: false
			})		
			,
			colModel: new Ext.grid.ColumnModel({
				defaults: {
						menuDisabled: true
					}
					,columns: [
						{header: _translationMap['PricePointTime'], dataIndex: 'timePoint', width: 110}						
						,{header: _translationMap['PriceCode'], dataIndex: 'priceCode', width: 105}
						,{header: _translationMap['IDPrice'], dataIndex: 'usedForDivPricing', width: 95}
					]		
				}
			)
		})
	}
	
	// **** popups ****
	var _popups = {
		validSettleCurr: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 650
			,modal: true
			,title: _translationMap['ValidSettleCurrencies']+ ' - '  +_translationMap['Edit']
			,defaults: {border:false}
			,currencyCheckboxes: {}				
			,items: [									
				{						
					layout: 'column'
					,defaults: {
						layout: 'auto'
						,columnWidth: 0.33
						,border: false						
					}						
					,items: [
						{id: 'currencyList_0'}
						,{id: 'currencyList_1'}
						,{id: 'currencyList_2'}
					]				
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['OK']
						,handler: function(){
							_controller.updateValidSettleCurr()							
							_popups['validSettleCurr'].hide();
						}	
					}
				)
				,new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['Cancel']
						,handler: function(){_popups['validSettleCurr'].hide();}
					}
				)
			]
			,init: function(currencyListXML)			
			{										
				var currencyNodes = IFDS.Xml.getNodes(currencyListXML, 'Element');
				for (var i = 0; i < currencyNodes.length; i++)
				{					
					this.currencyCheckboxes[IFDS.Xml.getNodeValue(currencyNodes[i], 'code')] = new DesktopWeb.Controls.Checkbox({						
						boxLabel: IFDS.Xml.getNodeValue(currencyNodes[i], 'code') + ' - ' + IFDS.Xml.getNodeValue(currencyNodes[i], 'value')
					});
					Ext.getCmp('currencyList_' + (i % 3)).add(this.currencyCheckboxes[IFDS.Xml.getNodeValue(currencyNodes[i], 'code')]);
				}														
			}
			,populate: function()
			{
				var selectedCurrencies = _fields['validSettleCurr'].getValue();
				for (var i in this.currencyCheckboxes)
				{
					this.currencyCheckboxes[i].setValue(selectedCurrencies.indexOf(i) != -1)
				}
			}
			,getData: function()
			{
				var selectedCurrencies = "";								
				for (var i in this.currencyCheckboxes)
				{
					if (this.currencyCheckboxes[i].getValue())
					{
						if (selectedCurrencies.length > 0)
						{
							selectedCurrencies += ","
						}
						selectedCurrencies += i;
					}					 
				}
				return selectedCurrencies;
			}														
		})	
		//Price point PopUp 
		,pricePointPopUp: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 400
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
			,action: null
			,uuid: null
			,style: 'padding:4px'
			,defaults: {border:true}
			,dropdownData: null
			,nextBusDay: null
			,cutOffTime: null
			,recRunMode: null
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center;font-weight:bold; font-size:12px; padding:10px;'	
				}
				,{
					layout: 'form'
					,defaults: {
						layout: 'auto'
						,border: false						
					}						
					,items: [{
						layout: 'column'
						,border: false	
						,items: [{
							layout: 'form'
							,labelWidth: 120
							,columnWidth: 1.0
							,style: 'padding-left:10px;'
							,border: false					
							,items: [
								new DesktopWeb.Controls.DateField({
									itemId: 'effectiveDateFrom'									
									,fieldLabel: _translationMap['EffectiveFrom']
									,allowBlank: false
									,width: 90
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
									,listeners: {
										change: function(fld, event) {
											fld.clearInvalid();
											var dateFrom = fld.getDisplayDateString();
											var dateFromObj =DesktopWeb.Util.stringToDate(dateFrom, DesktopWeb.Util.getDateDisplayFormat());
											var nextBusDateObj = DesktopWeb.Util.stringToDate(_popups['pricePointPopUp'].nextBusDay, 'mdy');
											if(dateFromObj < nextBusDateObj){
												fld.markInvalid(_translationMap['EffectiveFromLessTD']);
											}
										}
									}
								})
								,new DesktopWeb.Controls.DateField({
									itemId: 'effectiveDateTo'									
									,fieldLabel: _translationMap['EffectiveTo']
									,width: 90
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
									,listeners: {
										change: function(fld, event) {
											var dateTo = DesktopWeb.Util.stringToDate(fld.getDisplayDateString(),DesktopWeb.Util.getDateDisplayFormat());
											var dateFrom = DesktopWeb.Util.stringToDate(_popups['pricePointPopUp'].getField('effectiveDateFrom').getDisplayDateString(),DesktopWeb.Util.getDateDisplayFormat());
											if(dateTo < dateFrom) {
												_popups['pricePointPopUp'].getField('effectiveDateTo').markInvalid(_translationMap['EffectiveToLessFrom']);
												return false;
											}
										}
									}
								})
							]
						}]
				    }] 		
			     }
				,{
					xtype: 'fieldset'
					,defaults: {
						layout: 'auto'
						,style: 'padding-left:10px; padding-top:10px;'
						,border: false	
						,autoHeight: true
					}						
					,items: [{
						layout: 'column'
						,columnWidth: 1
						,style: 'padding-left:10px; padding-top:10px;'
						,items: [
						 {
							layout: 'form'
							,title: _translationMap['PricePoint']
							,columnWidth: 0.3
							,border: false
							,labelWidth: 1
							,items: [
							] 
						}
						,{
							layout: 'form'
							,title: _translationMap['PriceCode']
							,columnWidth: 0.7
							,border: false
							,items: []
						}
					 ]
				  }]		
			  }
			 ,{
				layout: 'form'
					,defaults: {
					layout: 'auto'
						,border: false						
					}						
					,items: [{
						layout: 'column'
						,border: false	
						,style: 'padding-left:10px; padding-top:10px;'
						,items: [{
							layout: 'form'
							,labelWidth: 80
							,columnWidth: 1.0
							,style: 'padding-left:10px;'
							,border: false					
							,items: [
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'pricePointsOpts'
									,fieldLabel: _translationMap['IDPrice']
									,width: 150
								})
						    ]
						}]
				    }] 		
		      }
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,style: 'padding-top:10px; '
					,handler: function() {
						if (_popups['pricePointPopUp'].isValid(_popups['pricePointPopUp'].action)) {
							_controller.valIntradayPricing(_popups['pricePointPopUp'].action, _popups['pricePointPopUp'].getData());
							_controller.closePricePointPopUp();	
						}
					}	
				})
				
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function() {
						_controller.closePricePointPopUp();
					}
				})
			]
			,init: function(action)	{		
				// initialize popup
				var popup = _popups['pricePointPopup']; 
				this.action = action;

				switch(action) {
					case _controller.ADD: {
						this.setTitle(_translationMap['IntradayPricing'] + ' - ' + _translationMap['Add']);
						this.populate(action);
						this.get(0).hide();
						break;
					}
					case _controller.MOD: {
						this.setTitle(_translationMap['IntradayPricing'] + ' - ' + _translationMap['Modify']);
						this.populate(action);
						this.get(0).hide();
						break;
					}
					case _controller.DEL: {
						this.setTitle(_translationMap['IntradayPricing']+ ' - ' + _translationMap['Delete']);
						this.populate(action);
						this.disableAllFields();
						this.get(0).show();
						break;
					}
				}
			}
			,setDropDownData: function(dropdownXML){
				//convert dropdown XML data into array
				var itemXMLNodes = IFDS.Xml.getNodes(dropdownXML, "Element");
				if(itemXMLNodes) {
					var dropdownItem = [];
					Ext.each(itemXMLNodes, function(xmlNode) {
						var code = IFDS.Xml.getNodeValue(xmlNode, "code");
						var value = IFDS.Xml.getNodeValue(xmlNode, "value");
						var item = {"code":code, "value": value};
						dropdownItem.push(item);
					})
					this.dropdownData = dropdownItem;	
				};
			}
			,cleanPointFields: function () {
				var fieldCount = this.dropdownData.length;
				for(i=1; i<=fieldCount; i++) {
					var code = this.dropdownData[i-1].code;
					if(code != 'AV') {
						this.getField('timeP' + i).setValue(_translationMap['HHMM']);
					}
					if(i > 1) {
						this.getField('timeP' + i).disable();
					}
				}
				this.getField('effectiveDateFrom').setValue('');
				this.getField('effectiveDateTo').setValue('');
				this.getField('timeP1').enable();
				this.getField('pricePointsOpts').enable();
			}
			,addAVToOptionDropdown: function(){
				//reset back ID price
				var currIDPrice = this.getField('pricePointsOpts').getValue();
				//set AV at bottom
				for(i=0; i<this.dropdownData.length; i++) {
					var code = this.dropdownData[i].code;
					if(code == 'AV') {
						var value = this.dropdownData[i].value;
						var myArray = new Array();
						myArray['code'] = code;
						myArray['value'] = value;
						var rec = new Ext.data.Record(myArray);
						this.getField('pricePointsOpts').store.add(rec);
						this.getField('pricePointsOpts').setValue(code);
					}
				}
			}
			,setOptionDropdown: function(action) {
				//clear dropdown
				this.getField('pricePointsOpts').store.removeAll();
				
				if(action != _controller.ADD){//for MOD/DEL, insert points
					var allPointRecords = _grids['intraDayPricingPoint'].getAllRecords();
					for(i=0; i < allPointRecords.length; i++) {
						var code = code = this.dropdownData[i].code;
						var value = this.dropdownData[i].value;
						var myArray = new Array();
						myArray['code'] = code;
						myArray['value'] = value;
						var rec = new Ext.data.Record(myArray);
						this.getField('pricePointsOpts').store.add(rec);
					}
				}
				this.addAVToOptionDropdown();
			}
			//reset pricePoints dropdown
			,updateOptionDropdown: function() {
				var currIDPrice = this.getField('pricePointsOpts').getValue();
				this.getField('pricePointsOpts').store.removeAll();
				
				var fieldCount = this.dropdownData.length;
				//change option items based on non-empty point fields
				var selectedDropdownDeleted = true;
				for(i=1; i<=fieldCount; i++) {
					var fieldValue = this.getField('timeP' + i).getValue();
					if(fieldValue != null && fieldValue != '') {
						var value = this.dropdownData[i-1].value;
						var code = this.dropdownData[i-1].code;
						if(code == currIDPrice) {
							selectedDropdownDeleted = false;
						}
						var myArray = new Array();
						myArray['code'] = code;
						myArray['value'] = value;
						
						var rec = new Ext.data.Record(myArray);
						if(code != 'AV') {
							this.getField('pricePointsOpts').store.add(rec);
							this.getField('pricePointsOpts').setValue(code);
						}
					}
				}
				this.addAVToOptionDropdown();
				if(selectedDropdownDeleted) {
					this.getField('pricePointsOpts').setValue('AV');
				} else {
					this.getField('pricePointsOpts').setValue(currIDPrice);
				}
			}
			,populate: function(action) {
				var popup = _popups['pricePointPopup'];
				this.cleanPointFields();
				this.enableAllFields();
				this.setOptionDropdown(action);

				switch(action) {
					case _controller.ADD: {
						this.pricingUUID = _controller.getIntradayUUID();
						this.recRunMode = _controller.ADD;
						this.getField('effectiveDateFrom').setValue(DesktopWeb.Util.getDateDisplayValue(this.nextBusDay))
						break;
					}
					case _controller.MOD: {
						var selectedIntradayPricing = _grids['intradayPricing'].getSelectedRecord();
						var selectedIntradayPricingPoint = _grids['intraDayPricingPoint'].getSelectedRecord();
						this.pricingUUID = selectedIntradayPricing.data['intraDayPricingUUID'];
						this.recRunMode = _controller.MOD;
						//format date as dd/mm/yyyy
						this.getField('effectiveDateFrom').setValue(selectedIntradayPricing.data['startDate']);
						this.getField('effectiveDateTo').setValue(selectedIntradayPricing.data['endDate']);
						this.getField('effectiveDateFrom').disableField();
						var allPointRecords = _grids['intraDayPricingPoint'].getAllRecords();
						
						var dateFromObj =DesktopWeb.Util.stringToDate(selectedIntradayPricing.data['startDate'], DesktopWeb.Util.getDateDisplayFormat());
						var nextBusDateObj = DesktopWeb.Util.stringToDate(_popups['pricePointPopUp'].nextBusDay, 'mdy');
						
						for(i=0; i < allPointRecords.length; i++) {
							var rec = allPointRecords[i];
							this.getField('timeP' + (i+1)).setValue(rec.data['timePoint']);
							if(rec.data['usedForDivPricing'] == 'yes') {
								this.getField('pricePointsOpts').setValue(rec.data['priceCode']);
							}
							if(dateFromObj < nextBusDateObj ) {
								this.getField('timeP' + (i+1)).disable();
								this.getField('pricePointsOpts').disable();
							} else {
								this.getField('timeP' + (i+1)).enable();
								if(this.getField('timeP' + (i+1)) != '') {
									this.getField('timeP' + (allPointRecords.length+1)).enable();
								}
							}
						}
						//AV
						var pointCount = this.dropdownData.length;
						for(var i=1; i<=pointCount; i++) {
							if(this.dropdownData[i-1].code == 'AV') {
								_popups['pricePointPopUp'].getField('timeP'+i).disable();
							}
						}
						//New added record
						if (selectedIntradayPricing.data['runMode'] == _controller.ADD) {
							this.getField('effectiveDateFrom').enableField();
							this.getField('effectiveDateTo').enableField();
							this.recRunMode = _controller.ADD;
						}
						break;
					}
					case _controller.DEL: {
						var selectedIntradayPricing = _grids['intradayPricing'].getSelectedRecord();
						this.pricingUUID = selectedIntradayPricing.data['intraDayPricingUUID'];
						//format date as dd/mm/yyyy
						this.getField('effectiveDateFrom').setValue(selectedIntradayPricing.data['startDate']);
						this.getField('effectiveDateTo').setValue(selectedIntradayPricing.data['endDate']);
						this.recRunMode = _controller.DEL;
						var allPointRecords = _grids['intraDayPricingPoint'].getAllRecords();
						
						for(i=0; i < allPointRecords.length; i++){
							var rec = allPointRecords[i];
							this.getField('timeP' + (i+1)).setValue(rec.data['timePoint']);
							if(rec.data['usedForDivPricing'] == 'yes') {
								this.getField('pricePointsOpts').setValue(rec.data['priceCode']);
							}
						}
						//Not mandatory for deletion
                        break;
					}
				}
				if (this.rendered) this.syncSize();
			}
			,isValid: function(action) {
				if(action != _controller.DEL) {
					var dateFrom = this.getField('effectiveDateFrom').getDisplayDateString();
					//var dataFromSMV = DesktopWeb.Util.getSMVDateValue(dateFrom)
					var dateFromObj = DesktopWeb.Util.stringToDate(dateFrom, DesktopWeb.Util.getDateDisplayFormat());
					var dateTo = this.getField('effectiveDateTo').getDisplayDateString();
					var dateToObj = DesktopWeb.Util.stringToDate(dateTo, DesktopWeb.Util.getDateDisplayFormat());
					var nextBusDateObj = DesktopWeb.Util.stringToDate(this.nextBusDay, 'mdy');
					
					if(dateTo == '') {
						_popups['pricePointPopUp'].getField('effectiveDateTo').markInvalid(_translationMap['FldRequired']);
					}
					if(dateFromObj > dateToObj) {
						_popups['pricePointPopUp'].getField('effectiveDateTo').markInvalid(_translationMap['EffectiveToLessFrom']);
						return false;
					}
					
					//validate start Date
					if((dateFromObj < nextBusDateObj) && action == _controller.ADD) {
						_popups['pricePointPopUp'].getField('effectiveDateFrom').markInvalid(_translationMap['EffectiveFromLessTD']);
						return false;
					}
					
					//validate stop Date
					if((dateToObj < nextBusDateObj) && action == _controller.MOD) {
						_popups['pricePointPopUp'].getField('effectiveDateTo').markInvalid(_translationMap['EffectiveToLessTD']);
						return false;
					}
					//validate all point fields
					var flag = true;
					var isAllEmpty = true;
					for(i=1; i <= this.dropdownData.length; i++) {
						var field = this.getField('timeP'+i)
						var fieldValue = field.getValue();
						var codeAV = this.dropdownData [i-1].code;
						if(fieldValue != null && fieldValue != '' && codeAV != 'AV') {
							isAllEmpty = false;
							if(!_popups['pricePointPopUp'].validatePricingPoints(field)) {
								return  false;
							}
						}
					}
	
					if(isAllEmpty) {
						_popups['pricePointPopUp'].getField('timeP1').markInvalid(_translationMap['AtLeastOnePricePoint']);
						return false;
					}
	
		            if (!dateToObj || !dateFromObj) {
						return false;
					}
			         //intraday set cannot overlap
		            var selectedRecord = _grids['intradayPricing'].getSelectedRecord();
		            var recUUID = null;
		            if(action != _controller.DEL) {
		            	if (action == _controller.ADD) {
		            		recUUID = this.pricingUUID; 
		            	} else {
		            		recUUID = selectedRecord.data['intraDayPricingUUID'];
		            	}
						var nOverlapDate = _grids['intradayPricing'].getStore().queryBy(function(record){
							if(record.data['intraDayPricingUUID'] != recUUID) {
								var newPopupDeff = DesktopWeb.Util.stringToDate(_popups['pricePointPopUp'].getField('effectiveDateFrom').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
								var newPopupEndD = DesktopWeb.Util.stringToDate(_popups['pricePointPopUp'].getField('effectiveDateTo').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
								var gridRecDeff = DesktopWeb.Util.stringToDate(record.data['startDate'], DesktopWeb.Util.getDateDisplayFormat());
								var gridRecEndD =DesktopWeb.Util.stringToDate(record.data['endDate'], DesktopWeb.Util.getDateDisplayFormat());

								var overlapInFlag = ((newPopupDeff <= gridRecEndD && newPopupDeff >= gridRecDeff) ||
										(newPopupEndD <= gridRecEndD && newPopupEndD >= gridRecDeff))
								var overlapOutFlag = (gridRecDeff >= newPopupDeff && gridRecEndD <= newPopupEndD)

								if(overlapInFlag || overlapOutFlag) {
									flag = false;
								}
								return (overlapInFlag || overlapOutFlag);
							}
						});
						if (!flag) {
							_popups['pricePointPopUp'].getField('effectiveDateTo').markInvalid(_translationMap['OverlapPriceset']);
							return false;
						}
		            }
				}
				return true;
			}
			,createPointRows: function() {
				var pointTimeLayout = this.items.get(2).items.get(0).items.get(0).items;
				var pointCodeLayout = this.items.get(2).items.get(0).items.get(1).items;
				var disabled = true;
				for(i=1; i<=this.dropdownData.length; i++) {
					var dropdownItem = this.dropdownData[i-1]
					if(i == 1) {
						disabled = false;
					} else {
						disabled = true;
					}
					var pointField = this.createPointTime(('timeP'+i), i, disabled);
					pointTimeLayout.add(pointField);
					pointCodeLayout.add(this.createPointCode(('codeA'+i), dropdownItem.value));

					if(dropdownItem.code == 'AV') {
						this.getField('timeP'+i).setValue(this.cutOffTime);
					}
				}	
			}
			,createPointCode: function(id, label){
				return new Ext.Toolbar.TextItem({
					id: id
					,style: 'padding:9px'
					,text : label
					,width: 200
				});
			}
			,createPointTime: function(id, index, disabled){
				return new DesktopWeb.Controls.TextField({
					itemId: id	
					,emptyText: _translationMap['HHMM']
					,autoCreate: {tag: 'input', type: 'text', autocomplete: 'off', maxlength: '5'}
					,width: 80
					,border: false
					,disabled: disabled
					,pointIndex: index
					,tabindex: index
					,listeners: {
						change: function(fld, event) {
							_popups['pricePointPopUp'].validatePricingPoints(fld)
							_popups['pricePointPopUp'].updateFieldsAndDropdown(fld);
						}
					}
				})
			}
			//time to string for digit
			,timeToStr: function(val) {
				if(val >= 0 && val < 10) {
					return val = '0' + val;
				} else {
					return val;
				}
			}
			//validate points
			,validatePricingPoints: function(currentField){//validate points
				var currentIndex = currentField.pointIndex;
				var currentTime = currentField.getValue();
				if(currentTime == '') {
					currentTime= '00:00';
				}
				
				var indexOfColumn = currentTime.indexOf(':');
				var currentHour = 0;
				var currentMin = 0;
				//get hh & mm
				if(indexOfColumn < 0) {
					currentHour = parseInt(currentTime, 10);
					if(isNaN(currentHour)){
						currentField.markInvalid(_translationMap['InvalidTimeFormat']);
						return false;
					}
					currentMin = 0;
				} else if (indexOfColumn == 0){//it is minutes (for example :22)
					currentHour = 0;
					var currentMinStr = currentTime.substring(1, currentTime.length);
					currentMin = parseInt(currentMinStr);
					if(isNaN(currentMin)){
						currentField.markInvalid(_translationMap['InvalidTimeFormat']);
						return false;
					}
				} else {
					currentHour = parseInt(currentTime.substring(0, indexOfColumn), 10);
					if(isNaN(currentHour)){
						currentField.markInvalid(_translationMap['InvalidTimeFormat']);
						return false;
					}
					currentMin = parseInt(currentTime.substring((indexOfColumn+1), currentTime.length), 10);
					if(isNaN(currentMin)){
						currentField.markInvalid(_translationMap['InvalidTimeFormat']);
						return false;
					}
				}

				if(currentHour == 0 && currentMin == 0 ) {
					currentField.setValue('');
				} else {
					currentField.setValue(_popups['pricePointPopUp'].timeToStr(currentHour) +':'+ _popups['pricePointPopUp'].timeToStr(currentMin));
					if(currentHour > 23) {
						currentField.markInvalid(_translationMap['ValidateHours']); 
						return false;
					}
					if(currentMin > 59) {
						currentField.markInvalid(_translationMap['ValidateMinutes']);
						return false;
					}
					
				}
				//starting validation
				if(currentIndex > 1) {
					var previousTime = _popups['pricePointPopUp'].getField('timeP'+(currentIndex - 1)).getValue();
					var previousHour = previousTime.substring(0, previousTime.indexOf(':'));
					var previousMin = previousTime.substring((previousTime.indexOf(':')+1), previousTime.length);
					var flag = true;

					if(previousHour == '' && previousMin == '') {
						_popups['pricePointPopUp'].getField(('timeP'+ currentIndex)).markInvalid(_translationMap['IsEmptyPricePoint']);
						return false;
					}
					
					if(previousHour > currentHour) {
						flag = false;
					} else if (previousHour == currentHour) {
						if(previousMin >= currentMin) {
							flag = false;
						}
					} 
					
					if(!flag) {
						if(_popups['pricePointPopUp'].getField(('timeP'+ currentIndex)).getValue() != '') {
							_popups['pricePointPopUp'].getField(('timeP'+ currentIndex)).markInvalid(_translationMap['ValCurrPrevPrice']);
						}
						return false;
					}
				}
				var avTime = this.cutOffTime;
				var avTimeHour = avTime.substring(0, avTime.indexOf(':'));
				var avTimeMin = avTime.substring((avTime.indexOf(':')+1), avTime.length);
				var flag2 = true;
				if(currentHour > avTimeHour) {
					flag2 = false;
				} else if(currentHour == avTimeHour) {
					if(currentMin >= avTimeMin) {
						flag2 = false;
					}
				}
				if(!flag2) {
					_popups['pricePointPopUp'].getField('timeP'+ currentIndex).markInvalid(_translationMap['ValFundCutOffTime']);
					return false;
				}
				return true;
			}
			
			,updateFieldsAndDropdown: function(currentField){
				var pointCount = _popups['pricePointPopUp'].dropdownData.length;
				var currentPointIndex = currentField.pointIndex;
				for(i=1; i<=pointCount; i++){
					var field = _popups['pricePointPopUp'].getField('timeP'+i);
					var index = field.pointIndex;
					
					if(index == (currentPointIndex + 1) && index < pointCount) {
						field.setValue(_translationMap['HHMM']);
						if(currentField.getValue() != ''){
							field.setDisabled(false);
						}else{
							field.disable();
							field.disabled = true;
						}
					}
					
					if(index > (currentPointIndex + 1) && index < pointCount) {
						field.setValue(_translationMap['HHMM']);
						field.disable();
						field.disabled = true;
					}
				}
				_popups['pricePointPopUp'].hide()
				_popups['pricePointPopUp'].show()
				
				this.updateOptionDropdown();
			}
			,getData: function() {
				var data = {};					
				data['runMode'] = this.recRunMode;
				data['intraDayPricingUUID'] = this.pricingUUID;
				data['startDate'] = _popups['pricePointPopUp'].getField('effectiveDateFrom').getDisplayDateString();
				data['endDate'] = _popups['pricePointPopUp'].getField('effectiveDateTo').getDisplayDateString();
				data['pricePointsOpts'] = _popups['pricePointPopUp'].getField('pricePointsOpts').getValue();

				var pointCount = this.dropdownData.length;
				var points = [];
				var cntT = 0; 
				for(var i=1; i<=pointCount; i++) {
					var p = {};		
					p['timePoint'] = _popups['pricePointPopUp'].getField('timeP'+i).getValue();
					p['priceCode'] = this.dropdownData[i-1].code;
					if(p['timePoint'] != null && p['timePoint'] != '' && p['priceCode'] != 'AV') {
						if(_popups['pricePointPopUp'].getField('timeP'+i).getValue() != '') {
							cntT++;
						}
						points.push(p)
					}
				}
				data['pricePointCnt'] = cntT;
				data['pointsRecords'] = points;
				return data;
			}
		})	
		//admin popUp
		,admin: new DesktopWeb.AdvancedControls.PopupWindow({	
			width: 395				
			,closeAction: 'hide'					
			,modal: true
			,defaults: {border:false}
			,items: [{														
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
	} 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,header: _header
		
		,breadCrumbList: _breadCrumbList
		
		,fields: _fields
		
		,field: _field
		
		,grids: _grids
		
		,popups: _popups
		
		,ADD: 'a', MOD: 'm', DEL: 'd'
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					_header
					,_breadCrumbList
					,new Ext.Container({
						style: 'padding-left:12px; padding-right:10px'
						,items: [
							{
								layout: 'column'
								,defaults: {
									layout: 'form'																	
								}
								,items: [
									{
										columnWidth: 0.45
										,labelWidth: 120
										,items: [
											_fields['currency']
											,_fields['schedTransType']
										]
									}
									,{
										labelWidth: 140
										,columnWidth: 0.55
										,items: [
											{
												xtype: 'compositefield'
												,fieldLabel: _translationMap['ValidSettleCurrencies']												
												,items: [													
													_fields['validSettleCurr'],
													new DesktopWeb.Controls.ActionButton({
														text: 'edit'														
														,width: 35
														,handler: function(){_controller.editValidSettleCurr()}														
													})
												]
											}	
											,_fields['esgPriceSuppress']]
									}
								]
							}							
							,{
								xtype: 'fieldset'
								,style: 'padding-left:10px;'
								,title: _translationMap['NAV']
								,items: [
									{
										layout: 'form'
										,labelWidth: 120
										,items: [
											_fields['gavApply']
										]
									}
									,{
										layout: 'column'
										,defaults: {											
											layout: 'form'											
										}
										,items: [
											{
												columnWidth: 0.32
												,labelWidth: 120
												,items: [
													_fields['fixPrice']													
													,_fields['priceVarAmt']
												]
											}
											,{
												columnWidth: 0.33
												,labelWidth: 85
												,items: [
													_fields['fixRate']
													,_fields['priceVarType']													
												]
											}
											,{
												columnWidth: 0.35
												,labelWidth: 120
												,items: [
													_fields['ratePrecision']	
													,_fields['capstockRateType']													
												]
											}
											,{
												layout: 'form'
												,labelWidth: 120
												,items: [
													_fields['loadGrp']
												]
											}
										]
									}
								]
							}
							,{
								xtype: 'fieldset'
								,title: _translationMap['Units']
								,style: 'padding-left:10px;'
								,items: [
									{
										layout: 'column'
										,defaults: {											
											layout: 'form'																						
											,labelWidth: 110
										}
										,items: [
											{
												columnWidth: 0.58
												,items: [
													_fields['unitsCalc']													
													,_fields['fractionalShr']													
												]
											}
											,{
												columnWidth: 0.42
												,items: [
												    _fields['roundFlag']  	
												    ,_fields['unitsPrecision']												
																								
												]
											}	
											,{
												columnWidth: 0.58
												,items: [
												     _fields['allocType']	
													
												]
											}	
										]
									}
								]
							}
							,{
								xtype: 'fieldset'
								,id: 'intradayExist'	
								,style: 'padding-left:10px;'
								,title: _translationMap['IntradayPricing']
								,height: 233
								,items: [
									{
										layout: 'column'
										,columnWidth: 1
										,defaults: {											
											layout: 'form'
										}
										,items: [
											{
												layout: 'form'
												,style: 'padding-left:10px; padding-top:2px;'
												,columnWidth: 0.5
												,items: [
													{
														layout: 'form'
														,style: 'font-weight:bold; font-size:12px;'	
														,labelWidth: 150		
														,items: [										
															_field['intraPriceAct']
														]
													}
													,{
														items: [
															 _grids['intradayPricing']
														]
													}
												]
											}
											,{
												layout: 'form'	
												,style: 'padding-left:20px;padding-top:33px;'
												,columnWidth: 0.5
												,defaults: {border:false}
												,items: [{
													items: [
														_grids['intraDayPricingPoint']
													]}
												]
											}
										]
									}
								
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