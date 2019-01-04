/*********************************************************************************************
 * @file	ClassSetup_GIAAttributes.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for GIA Attributes screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French
 *
 *  20 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030808 T54932 
 *             - Apply Scrollable when screen reach the maximum of layout 
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 685;
	var _layoutWidth = 750;
	
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px;'
		,height: 15
	})	
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({						
		height: 40						
		,listeners: {
			itemclicked: function(id){_controller.changeScreen(id)}
		}
	})	
	
	// **** fields ****
	var _fields = {
		intCalcMthd_sim: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['SimpleInterest']
		})
		,simTermList: new DesktopWeb.AdvancedControls.ItemSelector({
			height: 120
			,width: 270
			,style: 'margin-left:20px; margin-bottom: 10px'		
			,allowReordering: false						
			,availableGridProperties: {
				width: 90				
				,autoExpandColumn: 'term'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value']														
				})						
				,columns: [
					{id: 'term', header: _translationMap['Terms'], dataIndex: 'value'}								
				]	
			}
			,selectedGridProperties: {
				width: 90
				,autoExpandColumn: 'term'							
				,store: new Ext.data.XmlStore(
					{
						record: 'Element'					
						,fields: ['code', 'value', 'rate']														
					}
				)
				,columns: [
					{id: 'term', header: _translationMap['Terms'], dataIndex: 'value'}								
				]
			}						
		})
		,simCredFreq: new DesktopWeb.AdvancedControls.ItemSelector({
			height: 95
			,width: 270
			,style: 'margin-left:20px; margin-bottom: 10px'		
			,allowReordering: false						
			,availableGridProperties: {
				width: 90				
				,autoExpandColumn: 'freq'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value']														
				})						
				,columns: [
					{id: 'freq', header: _translationMap['Frequencies'], dataIndex: 'value'}								
				]	
			}
			,selectedGridProperties: {
				width: 90
				,autoExpandColumn: 'freq'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value', 'rate']														
				})
				,columns: [
					{id: 'freq', header: _translationMap['Frequencies'], dataIndex: 'value'}								
				]
			}						
		})
		
		
		,intCalcMthd_com: new DesktopWeb.Controls.Checkbox({
			boxLabel: _translationMap['CompoundInterest']
		})
		,comTermList: new DesktopWeb.AdvancedControls.ItemSelector({
			height: 120
			,width: 270
			,style: 'margin-left:20px; margin-bottom: 10px'		
			,allowReordering: false						
			,availableGridProperties: {
				width: 90				
				,autoExpandColumn: 'term'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value']														
				})						
				,columns: [
					{id: 'term', header: _translationMap['Terms'], dataIndex: 'value'}								
				]	
			}
			,selectedGridProperties: {
				width: 95
				,autoExpandColumn: 'term'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value', 'rate']														
				})
				,columns: [
					{id: 'term', header: _translationMap['Terms'], dataIndex: 'value'}								
				]
			}						
		})					
		,comCredFreq: new DesktopWeb.AdvancedControls.ItemSelector({
			height: 95
			,width: 270
			,style: 'margin-left:20px; margin-bottom: 10px'		
			,allowReordering: false						
			,availableGridProperties: {
				width: 90				
				,autoExpandColumn: 'freq'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value']														
				})						
				,columns: [
					{id: 'freq', header: _translationMap['Frequencies'], dataIndex: 'value'}								
				]	
			}
			,selectedGridProperties: {
				width: 90
				,autoExpandColumn: 'freq'							
				,store: new Ext.data.XmlStore({
					record: 'Element'					
					,fields: ['code', 'value', 'rate']														
				})
				,columns: [
					{id: 'freq', header: _translationMap['Frequencies'], dataIndex: 'value'}								
				]
			}						
		})							
									
		,defRenewInstr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['DefaultRenewableOption']
			,allowBlank: false
		})
		,redemOrder: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['RedemptionOrder']
			,allowBlank: false			
		})
		,mvaCurrMktRate: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['CurrentMarketInterestRate']
			,allowBlank: false					
		})		
		,mvaGLOff: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['GainLossOffset']
			,width: 90
			,allowBlank: false
		})				
		,mvaPayNetGain: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['PayNetGain']
			,width: 90
			,allowBlank: false
		})				
		,mvaEmpAcct: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['AdjustmentonEmploymentAgentAcct']
			,width: 90
			,allowBlank: false
		})		
		,adjustFee: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['AdjustmentFeePercentage']
			,width: 90
			,minValue: 0
			,maxValue: 100
		})
		,adjustFeeDate: new DesktopWeb.Controls.DateField({
			fieldLabel: _translationMap['EffectiveDate']
			,width: 90
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
		})
		
		,adminFeeApply: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['ChargesApplyTo']
			,allowBlank: false			
		})
		,feeTypeAttr: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['FeeType']
			,listeners: {
				select: function(){_controller.handleAdminFeeTypeUpdate(); _fields['adminFee'].clearInvalid()}
			}			
		})		 			
		,adminFee: new DesktopWeb.Controls.NumberField({
			fieldLabel: _translationMap['Fee']
			,width: 90
			,maxValue: 100
			,minValue: 0
			,validator: function(val){
				if (_fields['feeTypeAttr'].getValue() == '1' && val == "")
				{
					return _translationMap['FldRequired'];
				}
				else
				{
					return true;
				}
			}						
		})
		,adminFeeDate: new DesktopWeb.Controls.DateField({		
			fieldLabel: _translationMap['EffectiveDate']
			,width: 90
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,altFormats: DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			,listeners: {
				change: function(){_controller.handlerAdminFeeDateChange()}
			}			
		})		 			
		
	}
	
	// **** grids ****
	var _grids = {
		feeScale: new DesktopWeb.AdvancedControls.GridPanel({															
			autoScroll: true									
			,height: 120
			,autoExpandColumn: 'rate'			
			,enableHdMenu: false											
			,store: new Ext.data.XmlStore({
				record: 'ScaleDetl'					 				
				,fields: ['lower', 'upper', 'rate', 'runMode', 'scaleID']
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
			})
			,columns: [
				{header:  _translationMap['Lower'], dataIndex: 'lower', width:100}
				,{header: _translationMap['Upper'], dataIndex: 'upper', width:100}
				,{id:'rate', header: _translationMap['Rate'], dataIndex: 'rate'}				
			]
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.updateScaleActionButtons();}
					,rowdeselect: function(){_controller.updateScaleActionButtons();}
				}						
			})
			,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'								
						,text: _translationMap['Add']
						,handler: function(){
							_controller.openScalePopup(_controller.ADD);
						}																
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,handler: function(){
							_controller.openScalePopup(_controller.MOD);
						}						
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,handler: function(){
							_controller.openScalePopup(_controller.DEL);
						}
					})
				]
		})
	}

	
	// **** popups ****
	var _popups = {		
		feeScale: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 240
			,action: null
			,scaleID: null						
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap["DeleteConfirmMsg"]
					,style: 'text-align:center'
				}						
				,{						
					layout: 'form'
					,style: 'padding:4px'
					,labelWidth: 85
					,items: [
						new DesktopWeb.Controls.NumberField({
							itemId: 'lower'
							,fieldLabel: _translationMap['Lower']
							,allowBlank: false
							,width: 90
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'upper'
							,fieldLabel: _translationMap['Upper']
							,allowBlank: false
							,width: 90
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'rate'
							,fieldLabel: _translationMap['Rate']
							,allowBlank: false
							,width: 90
							,minValue: 0
							,maxValue: 100
						})				
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['feeScale'].isValid())
						{
							var upper = Number(_popups['feeScale'].getField('upper').getValue())
							var lower = Number(_popups['feeScale'].getField('lower').getValue())
							if (lower < upper)
							{
								_controller.saveFeeScale(_popups['feeScale'].action, _popups['feeScale'].getData());					
								_controller.closeScalePopup();
							}
							else
							{
								_popups['feeScale'].getField('upper').markInvalid("Upper value must be greater than lower");
							}		
						}
					}							
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_controller.closeScalePopup()}
				})
			]
			,init: function(action)
			{										
				this.action = action
				if (this.rendered)
				{					
					this.clearAllFields();
				}
				this.get(0).hide(); //hide delete message
				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['FeeScale'] + " - " + _translationMap['Add']);
						this.enableAllFields();																			
						this.getField('lower').clearInvalid();
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['FeeScale'] + " - " + _translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['FeeScale'] + " - " + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();
						this.populateWithSelectedRecord();
						break;
					}
				}
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['feeScale'].getSelectedRecord();				
				this.scaleID = rec.data['scaleID'];											
				this.getField('lower').setValue(rec.data['lower']);
				this.getField('upper').setValue(rec.data['upper']);
				this.getField('rate').setValue(rec.data['rate']);					
			}
			,getData: function()
			{
				var data = {};					
				data['runMode'] = this.action;
				data['scaleID'] = this.scaleID;				
				data['lower'] = this.getField('lower').getValue();
				data['upper'] = this.getField('upper').getValue();
				data['rate'] = this.getField('rate').getValue();					
				return data;
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
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(
			{
				height: _layoutHeight
				,width: _layoutWidth - 18
				,items: [
					_header
					,_breadCrumbList
					,new Ext.Container({
						style: 'padding-left:12px; padding-right:10px;'
						,height: 600						
						,items: [
							{
								layout: 'column'
								,items: [
									{
										xtype: 'fieldset'
										,checkboxToggle: true
										,id: 'simpleInterest'
										,collapsed: true
										,title: _translationMap['SimpleInterest']
										,columnWidth: .5
										,style: 'margin-right: 5px'
										,items: [
											{
												layout: 'form'
												,items: [
													_fields['simTermList']
													,_fields['simCredFreq']
												]
											}
										]										
										,listeners: {
											beforecollapse: function(){return false}
											,render: function(){
												_fields['intCalcMthd_sim'] = this.el.dom.firstChild.firstChild;
											}
										}
									}
									,{
										xtype: 'fieldset'
										,columnWidth: .5
										,title: _translationMap['CompoundInterest']
										,checkboxToggle: true
										,collapsed: true
										,id: 'compoundInterest'
										,style: 'margin-left: 5px'					
										,items: [
											{
												layout: 'form'
												,items: [
													_fields['comTermList']
													,_fields['comCredFreq']
												]
											}
										]
										,listeners: {
											beforecollapse: function(){return false}
											,render: function(){
												_fields['intCalcMthd_com'] = this.el.dom.firstChild.firstChild;
											}
										}								
									}
								]						
							}
							,{
								layout: 'column'
								,style: 'padding-top:10px;'
								,items: [
									{
										layout: 'form'
										,columnWidth: .55
										,labelWidth: 185
										,items: [
											_fields['defRenewInstr']
										]
									}
									,{
										layout: 'form'
										,columnWidth: .45
										,labelWidth: 135
										,items: [
											_fields['redemOrder']
										]
									}
								]
							}
							,{
								xtype: 'fieldset'
								,style: 'padding-left: 10px'
								,title: _translationMap['MVAAttributes']
								,items: [
									{
										layout: 'column'
										,items: [
											{
												layout: 'form'
												,labelWidth: 225
												,columnWidth: .60
												,items: [
													_fields['mvaCurrMktRate']
													,_fields['mvaEmpAcct']
													,_fields['adjustFee']
												]
											}
											,{
												layout: 'form'
												,columnWidth: .40
												,labelWidth: 125
												,items: [
													_fields['mvaGLOff']
													,_fields['mvaPayNetGain']
													,_fields['adjustFeeDate']
												]
											}
										]
									}
								]							
							}
							,{
								xtype: 'fieldset'
								,title: _translationMap['AdminFee']
								,items: [
									{
										layout: 'column'
										,defaults: {
											columnWidth: 0.5
										}
										,items: [
											{
												layout: 'form'
												,labelWidth: 120
												,items: [
													_fields['adminFeeApply']
													,_fields['adminFeeDate']
													,_fields['feeTypeAttr']
													,_fields['adminFee']
												]
											}
											,_grids['feeScale']
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