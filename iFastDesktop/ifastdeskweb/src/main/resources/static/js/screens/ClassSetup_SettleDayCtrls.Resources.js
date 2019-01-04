/**********************************************************************
 * @file ClassSetup_SettleDayCtrls.Resources.js
 * @author wp040510
 * @desc Resource file for Settle day controls,Part of Class Setup flow
 **********************************************************************/
/*
 *  Navigate: Menu > Fund class Maintenance > Add/View class details > Settle day controls
 *
 *  History : 
 *  
 *  18-Dec-2017 Sreejith A P0274727-1
 *  			- New screen for Settle day controls
 *  
 *	12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 */
DesktopWeb.ScreenResources = function(ctrlr){
	
    var _controller = ctrlr;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();

    // content dimensions
    var _layoutHeight = 670;
    var _layoutWidth  = 750;
    
	var _header = new DesktopWeb.Controls.Label({															
		style: 'font-weight: bold; font-size: 13px; padding-bottom: 8px;'
		,height: 15
	})	
	
	var _breadCrumbList = new DesktopWeb.AdvancedControls.BreadCrumbList({						
		height: 45							
		,listeners:{
			itemclicked: function(id) {_controller.changeScreen(id)}
		}
	})
    
    // **** fields **** 
    var _fields = {
    		purStlmtDays: {
    			purchaseStlmtDays: {
    				AmountType: new DesktopWeb.Controls.Checkbox({
    					boxLabel: _translationMap['AmountType']
    					,checked:true
    					,width: 120
    					,listeners: {
    						check: function(fld) {
    							_controller.onAmountTypeChange(this.getValue(),_fields['purStlmtDays']['purchaseStlmtDays']);
    						}
    					}
    				})
        			,UnitDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 35
						,readOnly: true
        			})
    				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['purStlmtDays']['purchaseStlmtDays']);
							}
						}
    				})
					,AmountDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 60
						,readOnly: true
						,value: _translationMap['AmountDays']
					})
    				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['purStlmtDays']['purchaseStlmtDays']);
							}
						}
    				})
    			},
    			diffStlmtCurrency: {
    				AmountType: new DesktopWeb.Controls.Checkbox({
    					boxLabel: _translationMap['AmountType']
    					,width: 120
    					,checked:true
        				,listeners: {
        					check: function() {
        						_controller.onAmountTypeChange(this.getValue(),_fields['purStlmtDays']['diffStlmtCurrency']);
        					}
        				}
    				})
    				,UnitDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 35
						,readOnly: true
	        		})
    				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange (_fields['purStlmtDays']['diffStlmtCurrency']);
							}
						}
    				})
					,AmountDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 60
						,readOnly: true
						,value: _translationMap['AmountDays']
					})
    				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['purStlmtDays']['diffStlmtCurrency']);
							}
						}
    				})
    			}
    		},
    		otherSettleDays: {
    			redemptionStlmtDays: {
    				AmountType: new DesktopWeb.Controls.Checkbox({
    					boxLabel: _translationMap['AmountType']
    					,width: 120
    					,checked:true
        				,listeners: {
        					check: function() {
        						_controller.onAmountTypeChange(this.getValue(),_fields['otherSettleDays']['redemptionStlmtDays']);
        					}
        				}
    				})
		    		,UnitDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 35
						,readOnly: true
					})
    				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['redemptionStlmtDays'], newVal.toString());
							}
						}
    				})
					,AmountDaysLabel: new DesktopWeb.Controls.TextField ({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 60
						,readOnly: true
						,value: _translationMap['AmountDays']
					})
    				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['redemptionStlmtDays'], newVal.toString());
							}
						}
    				})
    			},
    			exchangeInStlmtDays: {
    				AmountType: new DesktopWeb.Controls.Checkbox({
    					boxLabel: _translationMap['AmountType']
    					,checked:true
    					,width: 120
        				, listeners: {
        					check: function() {
        						_controller.onAmountTypeChange(this.getValue(),_fields['otherSettleDays']['exchangeInStlmtDays']);
        					}
        				}
    				})
	    			,UnitDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 35
						,readOnly: true
	    			})
    				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['exchangeInStlmtDays']);
							}
						}
    				})
					,AmountDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 60
						,readOnly: true
						,value: _translationMap['AmountDays']
					})
    				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange (_fields['otherSettleDays']['exchangeInStlmtDays']);
							}
						}	
    				})
    			},
    			exchangeOutStlmtDays: {
    				AmountType: new DesktopWeb.Controls.Checkbox ({
    					boxLabel: _translationMap['AmountType']
    					,checked:true
    					,width: 120
        				,listeners: {
        					check: function() {
        						_controller.onAmountTypeChange(this.getValue(),_fields['otherSettleDays']['exchangeOutStlmtDays']);
        					}
        				}
    				})
	    			,UnitDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 35
						,readOnly: true
	    			})
    				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['exchangeOutStlmtDays']);
							}
						}
    				})
					,AmountDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 60
						,readOnly: true
						,value: _translationMap['AmountDays']
					})
    				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['exchangeOutStlmtDays']);
							}
						}	
    				})
    			},
    			transferInStlmtDays: {
    				AmountType: new DesktopWeb.Controls.Checkbox({
    					boxLabel: _translationMap['AmountType']
    					,checked:true
    					,width: 120
        				,listeners: {
        					check: function() {
        						_controller.onAmountTypeChange(this.getValue(),_fields['otherSettleDays']['transferInStlmtDays']);
        					}
        				}
    				})
	    			,UnitDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 35
						,readOnly: true
	    			})
    				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['transferInStlmtDays']);
							}
						}
    				})
					,AmountDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 60
						,readOnly: true
						,value: _translationMap['AmountDays']
					})
    				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['transferInStlmtDays']);
							}
						}
    				})
    			},
    			transferOutStlmtDays: {
    				AmountType: new DesktopWeb.Controls.Checkbox({
    					boxLabel: _translationMap['AmountType']
    					,checked:true
    					,width: 120
        				,listeners: {
        					check: function() {
        						_controller.onAmountTypeChange(this.getValue(),_fields['otherSettleDays']['transferOutStlmtDays']);
        					}
        				}
    				})
	    			,UnitDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 35
						,readOnly: true
	    			})
    				,UnitDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['transferOutStlmtDays']);
							}
						}
    				})
					,AmountDaysLabel: new DesktopWeb.Controls.TextField({
						style: 'border: none; text-transform: none; background:transparent;'
						,width: 60
						,readOnly: true
						,value: _translationMap['AmountDays']
					})
    				,AmountDays: new DesktopWeb.ScreenResources.NumberField({
    					listeners: {
							change: function(fld, newVal) {
								_controller.onDaysChange(_fields['otherSettleDays']['transferOutStlmtDays']);
							}
						}
    				})
    			}
    		}	
    }
    
    // PUBLIC ITEMS
    return {
        layoutWidth: _layoutWidth

        ,layoutHeight: _layoutHeight
        
		,header: _header
		
		,breadCrumbList: _breadCrumbList

        ,fields: _fields
        
        ,layout: new Ext.Container({
        	height: _layoutHeight
            ,width: _layoutWidth
            ,items: [
    				_header
    				,_breadCrumbList
                    ,new Ext.Container({
    					style: 'padding-left:12px; padding-right:10px'
    					,items: [{
    								layout: 'column'
    								,style: 'margin-bottom:10px;'
    								,items: [{
    										xtype: 'fieldset'
    										,style: 'margin-left:3px; padding-left:10px;'
    										,title:  _translationMap['PurchaseSettlementDays']	
    										,width: 725
    										,items: [{
    												layout: 'form'
    												,labelWidth: 190
    												,defaults: {
    													msgTarget: 'side'
    												}
    												,items: [{
    														xtype: 'compositefield'
    														,fieldLabel: _translationMap['PurchaseSettlementDays']
    														,width : 335
    										                ,msgTarget: 'side'
    										                ,invalidClass: ''
    														,items: [	
    															_fields['purStlmtDays']['purchaseStlmtDays']['AmountType']
    															,_fields['purStlmtDays']['purchaseStlmtDays']['UnitDaysLabel']
    															,_fields['purStlmtDays']['purchaseStlmtDays']['UnitDays']
    															,_fields['purStlmtDays']['purchaseStlmtDays']['AmountDaysLabel']
    															,_fields['purStlmtDays']['purchaseStlmtDays']['AmountDays']
    														]
    														}
    														,{
	    														xtype: 'compositefield'
	    														,fieldLabel: _translationMap['DifferentSettlementCurrency']
	    														,width : 335
	    														,invalidClass: ''
	    														,items: [	
	    															_fields['purStlmtDays']['diffStlmtCurrency']['AmountType']
	    															,_fields['purStlmtDays']['diffStlmtCurrency']['UnitDaysLabel']
	    															,_fields['purStlmtDays']['diffStlmtCurrency']['UnitDays']
	    															,_fields['purStlmtDays']['diffStlmtCurrency']['AmountDaysLabel']
	    															,_fields['purStlmtDays']['diffStlmtCurrency']['AmountDays']		
	    														]
    														}
    												]	
    											}
    										]
    									}
    								]
    							},
    							{
									xtype: 'fieldset'
									,style: 'margin-left:3px; padding-left:10px;padding-top:10px;'	
									,width: 728
									,items: [{
											layout: 'form'
											,labelWidth: 190
											,defaults: {
												msgTarget: 'side'
											}
											,items: [{
													xtype: 'compositefield'
													,fieldLabel: _translationMap['RedemptionSettlementDays']
													,invalidClass: ''
													,width : 335
													,items: [	
														_fields['otherSettleDays']['redemptionStlmtDays']['AmountType']
														,_fields['otherSettleDays']['redemptionStlmtDays']['UnitDaysLabel']
														,_fields['otherSettleDays']['redemptionStlmtDays']['UnitDays']
														,_fields['otherSettleDays']['redemptionStlmtDays']['AmountDaysLabel']
														,_fields['otherSettleDays']['redemptionStlmtDays']['AmountDays']
													]
													}
													,{
													xtype: 'compositefield'
													,fieldLabel: _translationMap['ExchangeInSettlementDays']
													,width : 335
													,invalidClass: ''
													,items: [	
														_fields['otherSettleDays']['exchangeInStlmtDays']['AmountType']
														,_fields['otherSettleDays']['exchangeInStlmtDays']['UnitDaysLabel']
														,_fields['otherSettleDays']['exchangeInStlmtDays']['UnitDays']
														,_fields['otherSettleDays']['exchangeInStlmtDays']['AmountDaysLabel']
														,_fields['otherSettleDays']['exchangeInStlmtDays']['AmountDays']
													]
													}
													,{
													xtype: 'compositefield'
													,fieldLabel: _translationMap['ExchangeOutSettlementDays']
													,width : 335
													,invalidClass: ''
													,items: [
														_fields['otherSettleDays']['exchangeOutStlmtDays']['AmountType']
														,_fields['otherSettleDays']['exchangeOutStlmtDays']['UnitDaysLabel']
														,_fields['otherSettleDays']['exchangeOutStlmtDays']['UnitDays']
														,_fields['otherSettleDays']['exchangeOutStlmtDays']['AmountDaysLabel']
														,_fields['otherSettleDays']['exchangeOutStlmtDays']['AmountDays']
													]
													}
													,{
													xtype: 'compositefield'
													,fieldLabel: _translationMap['TransferInSettlementDays']
													,width : 335
													,invalidClass: ''
													,items: [
														_fields['otherSettleDays']['transferInStlmtDays']['AmountType']
														,_fields['otherSettleDays']['transferInStlmtDays']['UnitDaysLabel']
														,_fields['otherSettleDays']['transferInStlmtDays']['UnitDays']
														,_fields['otherSettleDays']['transferInStlmtDays']['AmountDaysLabel']
														,_fields['otherSettleDays']['transferInStlmtDays']['AmountDays']
													]
													}
													,{
													xtype: 'compositefield'
													,fieldLabel: _translationMap['TransferOutSettlementDays']
													,width : 335
													,invalidClass: ''
													,items: [
														_fields['otherSettleDays']['transferOutStlmtDays']['AmountType']
														,_fields['otherSettleDays']['transferOutStlmtDays']['UnitDaysLabel']
														,_fields['otherSettleDays']['transferOutStlmtDays']['UnitDays']
														,_fields['otherSettleDays']['transferOutStlmtDays']['AmountDaysLabel']
														,_fields['otherSettleDays']['transferOutStlmtDays']['AmountDays']
													]
												}
											]
											
										}
									]
								}
    						]
                    	})
                    ]
         })
    
		,screenButtons : [
			new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Previous'],
				hidden : true,
				disabled : true,
				id : 'prevBtn',
				handler : function() {
					_controller.previous();
				}
			}), new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Save'],
				id : 'saveBtn',
				disabled : true,
				handler : function() {
					_controller.save();
				}
			}), new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Reset'],
				id : 'resetBtn',
				disabled : true,
				handler : function() {
					_controller.reset();
				}
			}), new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['Cancel'],
				hidden : true,
				id : 'cancelBtn',
				handler : function() {
					_controller.cancel();
				}
			}), new DesktopWeb.Controls.ScreenButton({
				text : '',
				hidden : true,
				id : 'nextBtn',
				handler : function() {
					_controller.next();
				}
			}), new DesktopWeb.Controls.ScreenButton({
				text : _translationMap['ReturntoSummary'],
				hidden : true,
				id : 'summaryBtn',
				handler : function() {
					_controller.changeScreen('Summary');
				}
			})
		]
    }

}
DesktopWeb.ScreenResources.NumberField = Ext.extend( DesktopWeb.Controls.NumberField, {
	width: 50
	,allowDecimals: false
	,allowNegative: false
});