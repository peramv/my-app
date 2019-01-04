 /*********************************************************************************************
 * @file	ClassSetup_EventGen.Resources.js
 * @author	Cherdsak Sangkasen
 * @desc	Resources JS file for Event Date Generate screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 265;
	var _layoutWidth = 450;
	
	// **** fields ****
	var _fields = {		
		cboFundClass: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['FundClass']
			,smartview: 'fundClassSearch'				
			,fields: ['fndClsDisp', 'fundCode', 'classCode']
			,valueField: 'fndClsDisp'
			,displayField: 'fndClsDisp'
			,allowBlank: false
			,addtlSearchParams: [{name: 'api', valueFn: function(){return 'dtEventDateGenInit'}}]
			,width: 325												
			,listeners: {
				populated: function()
				{
					_controller.doSearch();
				}
				,cleared: function()
				{
					_controller.doSearch();
				}				
			}																										
		})
		, txtYear: new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['Year']
				, width: 100	
				, maskRe: /[0-9]/
				, validator: function(value){         
					var pattern = /^\d\d\d\d$/;
					if(!pattern.test(value)) {    
						_controller.isFrontValid = false;
						return _translationMap['YearErrMsg'];         
					} else {   
						_controller.isFrontValid = true;
						return true;        
					}
				}
				, listeners:{          
					change: function() {
						_controller.doSearch();	
					}
				}
			}
		)		
		, optValidationDate: new DesktopWeb.Controls.Radio(
			{
				boxLabel: _translationMap['ValuationDate']
				,name: 'eventGen'
				,width: 150		
				, listeners:{          
					check: function(ctl, val) {
						if (val) {
							_controller.doOptCheck("Valuation");
						}
					}
				}		
			}
		)
		, optEventTradeDate: new DesktopWeb.Controls.Radio(
			{
				boxLabel: _translationMap['EventTradeDate']
				,name: 'eventGen'
				,width: 150		
				, listeners:{          
					check: function(ctl, val) {
						if (val) {
							_controller.doOptCheck("EventTrade");
						}
					}
				}			
			}
		) 
		, dtpValuationDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['DtpValuationDate']					
				, width: 100
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				
			}
		)
		, chkCrystalisation: new DesktopWeb.Controls.Checkbox(
			{
				boxLabel: _translationMap['ChkCrystalisation']
				, width: 120
				, listeners:{          
					check: function(ctl, val) {
						_controller.doEventCheck("Crystalisation", val);
					}
				}
			}
		)
		, chkDistribution: new DesktopWeb.Controls.Checkbox(
			{
				boxLabel: _translationMap['ChkDistribution']
				, width: 120
				, listeners:{          
					check: function(ctl, val) {
						_controller.doEventCheck("Distribution", val);
					}
				}
			}
		)
		, chkDealing: new DesktopWeb.Controls.Checkbox(
			{
				boxLabel: _translationMap['ChkDealing']
				, width: 120
				, listeners:{          
					check: function(ctl, val) {
						_controller.doEventCheck("Dealing", val);
					}
				}
			}
		)
		, cboCrystalisation: new DesktopWeb.Controls.ComboBox(
			{
				width: 100
				, editable: false
				, autoSelect: true
				, store: new Ext.data.XmlStore(
					{
						record: 'Element'
						,fields: ['code', 'value', 'valueDisplay', 'codeDMY']
						, listeners: {
							load: function(store, records) 
							{
								Ext.each(records, function(record){
									record.data['valueDisplay'] = DesktopWeb.Util.getDateDisplayValue(record.data['value']);
									record.data['codeDMY']     = DesktopWeb.Util.convertDateStringFormat(record.data['code']
									, DesktopWeb._SCREEN_PARAM_MAP['dateFormat'], "dmy");
								});
								
								store.fireEvent('datachanged', store); //to set data in grid again					        								
							}
						}	
						
					}
				)
				, valueField: 'code'
				, displayField: 'valueDisplay'
				, valueDMYField : 'codeDMY'
				, getDMYValue : function()
				{
					var rec = this.getSelectedRecord();
					var result = "";
					if (rec) 
						result = rec.data[this.valueDMYField];
					return result;
				}
			}
		)
		, cboDistribution: new DesktopWeb.Controls.ComboBox(
			{
				width: 100		
				, editable: false		
				, autoSelect: true
				, store: new Ext.data.XmlStore(
					{
						record: 'Element'
						,fields: ['code', 'value', 'valueDisplay', 'codeDMY']
						, listeners: {
							load: function(store, records) 
							{
								Ext.each(records, function(record){
									record.data['valueDisplay'] = DesktopWeb.Util.getDateDisplayValue(record.data['value']);
									record.data['codeDMY']     = DesktopWeb.Util.convertDateStringFormat(record.data['code']
									, DesktopWeb._SCREEN_PARAM_MAP['dateFormat'], "dmy");
								});
								
								store.fireEvent('datachanged', store); //to set data in grid again					        								
							}
						}							
					})
				, valueField: 'code'
				, displayField: 'valueDisplay'
				, valueDMYField : 'codeDMY'
				, getDMYValue : function()
				{
					var rec = this.getSelectedRecord();
					var result = "";
					if (rec) 
						result = rec.data[this.valueDMYField];
					return result;
				}
			}
		)
		, cboDealing: new DesktopWeb.Controls.ComboBox(
			{
				width: 100	
				, editable: false
				, autoSelect: true
				, store: new Ext.data.XmlStore(
					{
						record: 'Element'
						,fields: ['code', 'value', 'valueDisplay', 'codeDMY']
						, listeners: {
							load: function(store, records) 
							{
								Ext.each(records, function(record){
									record.data['valueDisplay'] = DesktopWeb.Util.getDateDisplayValue(record.data['value']);
									record.data['codeDMY']     = DesktopWeb.Util.convertDateStringFormat(record.data['code']
									, DesktopWeb._SCREEN_PARAM_MAP['dateFormat'], "dmy");
								});
								
								store.fireEvent('datachanged', store); //to set data in grid again					        								
							}
						}	
						
					})
				, valueField: 'code'
				, displayField: 'valueDisplay'
				, valueDMYField : 'codeDMY'   //codeDMY is a new field added to grid used to get code in dmy format
				                              //This format is used when call update service which required in job schedule
				, getDMYValue : function()
				{
					var rec = this.getSelectedRecord();
					var result = "";
					if (rec) 
						result = rec.data[this.valueDMYField];
					return result;
				}				
			}
		)
		, lblSchedule1: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['LblSchedule']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: 100
			}
		)
		, lblSchedule2: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['LblSchedule']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: 120
			}
		)
		, lblStartDate1: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['LblStartDate']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: 100
			}
		)	
		, lblStartDate2: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['LblStartDate']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: 100
			}
		)		
	}
	
	// **** grids ****
	var _grids = {
	}
	
	// **** popups ****
	var _popups = {					
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
				,layout: 'form'
				,items: [
					_fields['cboFundClass']
					, _fields['txtYear']
					
					, {
						layout: 'column'
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 80}	
						,items: [
							{
								width: 150
								, layout: 'form'
								, labelWidth: 100
								, items: [_fields['optValidationDate']]							
							}
							, {
								width: 150
								, layout: 'form'
								, labelWidth: 100
								, items: [_fields['optEventTradeDate']]							
							}				
						]
					}
					, {
						xtype: 'fieldset'
						, style: 'position:relative; margin-left:0px; padding-left:10px;'
						, id: 'valuation_fieldset'	
						, title: _translationMap['ValuationDate']
						, hideMode: 'offsets'
						, hidden: true
						, width: 300
						, items: [
							{							
								layout: 'column'
								,items: [
									{
										width: 105
										, layout: 'form'
										, items: [_fields['lblSchedule1']]							
									}
									, {
										width: 120
										, layout: 'form'
										, items: [_fields['lblStartDate1']]							
									}			
								]
							}
							, {
								width: 250
								, style: 'padding-top:5px;'
								, layout: 'form'
								, labelWidth: 95
								, items: [_fields['dtpValuationDate']]	
							}
						]
					}
					, {
						xtype: 'fieldset'
						, style: 'position:relative; margin-left:0px; padding-left:10px;'
						, id: 'eventtrade_fieldset'	
						, title: _translationMap['EventTradeDate']
						, hideMode: 'offsets'
						, hidden: true
						, width: 300
						, items: [
							{							
								layout: 'column'
								, items: [
									{
										width: 125
										, layout: 'form'
										, items: [_fields['lblSchedule2']]							
									}
									, {
										width: 120
										, layout: 'form'
										, items: [_fields['lblStartDate2']]							
									}			
								]
							}
							, {
								xtype: 'compositefield'
								, id: 'fldCrystalization'
								, style: 'padding-top:5px;'	
								, hideLabel: true		
								, items: [													
									_fields['chkCrystalisation']													
									, _fields['cboCrystalisation']
								]
							}
							, {
								xtype: 'compositefield'
								, id: 'fldDistribution'								
								, hideLabel: true		
								, items: [													
									_fields['chkDistribution']													
									, _fields['cboDistribution']
								]
							}
							, {
								xtype: 'compositefield'
								, id: 'fldDealing'
								, hideLabel: true		
								, items: [													
									_fields['chkDealing']													
									, _fields['cboDealing']
								]
							}
						]
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['BtnSubmit']
					,handler: function(){ 
						if (_controller.isFrontValidChk()) { 
							DesktopWeb.Util.displayPrompt(_translationMap['DoUpdateConfirm'], callback);					
							
							function callback(buttonId)
							{
								if (buttonId == 'ok')
								{
									DesktopWeb.Util.commitScreen(); 
								}
							}
						} 
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['BtnCancel']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}