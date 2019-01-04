 /*********************************************************************************************
 * @file	ClassSetup_EvenMain.Resources.js
 * @author	Cherdsak Sangkasen
 * @desc	Resources JS file for Event Schedule Maintenance screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54443
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  20 Jan 2015 Kornnika.T P0181067 CHG0038356 T55786
 *          - The browser base send wrong format of valuation date to smartview. The smartview require date format m/d/y but the browser base send date format d/m/y.
 *          - The browser base display error while delete the record if 'Event Type' is "05 – Record Date Schedule".
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 705;
	var _layoutWidth = 715;
	
	// **** fields ****
	var _fields = {
		cboFundClass: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['FundClass']
			,smartview: 'fundClassSearch'				
			,fields: ['fndClsDisp', 'fundCode', 'classCode']
			,valueField: 'fndClsDisp'
			,displayField: 'fndClsDisp'		
			,addtlSearchParams: [{name: 'api', valueFn: function(){return 'dtEventMaintInit'}}]
			,width: 330												
			,listeners: {
				populated: function()
				{
					_controller.freezeGrid(_fields['cboFundClass'].selectedRecord.get('fundCode'), _fields['cboFundClass'].selectedRecord.get('classCode'));
				}
				,cleared: function()
				{
					_controller.freezeGrid();
				}				
			}																										
		})
		, dtpStartDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['StartDate']			
				, width: 120
				, emptyText: _controller.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)	
		, dtpEndDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['EndDate']			
				, width: 120
				, emptyText: _controller.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
		
		, eventType: new DesktopWeb.Controls.SMVComboBox(
			{
				width: 170
				,fieldLabel: _translationMap['EventType']
				,allowBlank: false
				,autoSelect: true
				,showCode: true	
			}
		)
		, lblValnGav: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['Gav']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnGav: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)
		, lblValnNav: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['Nav']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnNav: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)		
		, lblValnClsHWM: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ClassHWM']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnClsHWM: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)
		, lblValnClsHWMDate: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ClassHWMDate']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnClsHWMDate: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)	
		, lblValnNumDay: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['NumDays']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnNumDay: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)		
		, lblValnPfPerShare: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['PfPerShare']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnPfPerShare: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)		
		, lblValnEffHurdle: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['EffHurdle']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnEffHurdle: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)		
		, lblValnClsAdjHWM: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['ClsAdjHWM']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, valnClsAdjHWM: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)		
		, lblCrysClsHWM: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['CrysClsHWM']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, crysClsHWM: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)
		, lblCrysGav: new DesktopWeb.Controls.Label(
			{
				text: _translationMap['CrysGav']
				, style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) + 20
				, height: 20
			}
		)
		, crysGav: new DesktopWeb.Controls.Label(
			{
				style: 'font:12px tahoma,arial,helvetica,sans-serif'
				, width: (_layoutWidth / 4) - 40
				, height: 20
			}
		)		
		, dtpValudationDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['ValuationDate']	
				, itemId: 'dtpValudationDate'				
				, width: 150
				, emptyText: _controller.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
		, chkCrystalisation: new DesktopWeb.Controls.Checkbox(
			{
				boxLabel: _translationMap['CrystalisationDate']
				, width: 150
			}
		)
		, chkDistribution: new DesktopWeb.Controls.Checkbox(
			{
				boxLabel: _translationMap['DistributionDate']
				, width: 150
			}
		)
		, txtDelValuationDate : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['ValuationDate']	
				, width: 150
			}
		)
		, txtDelCrystalisation : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['CrystalisationDate']
				, width: 150
			}
		)
		, txtDelDistribution : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['DistributionDate']
				, width: 150
			}
		)
		//G1G2
		, txtDeLRecordDate : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['NextRecordDate']	
				, width: 100
				
			}
		)
		, txtDeLExDate : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['ExDate']	
				, width: 100
				
			}
		)
		, txtDeLPayDate : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['PayDate']	
				, width: 100
				
			}
		)
		, txtDeLReinvestDate : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['ReinvestDate']	
				, width: 100
				
			}
		)
		, txtDeLDistributionType : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['DistributionType']	
				, width: 150
				
			}
		)
		, txtDeLDistributionIndicator : new DesktopWeb.Controls.TextField(
			{
				fieldLabel: _translationMap['DistributionIndicator']	
				, width: 150
				
			}
		)
		, distributionType: new DesktopWeb.Controls.SMVComboBox(
			{
				width: 150
				,fieldLabel: _translationMap['DistributionType']
				,allowBlank: true
				,autoSelect: true
				,showCode: true	
			}
		)
		, distributionIndicator: new DesktopWeb.Controls.SMVComboBox(
			{
				width: 150
				,fieldLabel: _translationMap['DistributionIndicator']
				,allowBlank: true
				,autoSelect: true
				,showCode: true	
			}
		)
		, dtpRecordDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['NextRecordDate']	
				, itemId: 'dtpRecordDate'
				, width: 150
				, allowBlank: false
				, emptyText: _controller.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
		, dtpExDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['ExDate']	
				, itemId: 'dtpExDate'				
				, width: 150
				, emptyText: _controller.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
		, dtpPayDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['PayDate']	
				, itemId: 'dtpPayDate'					
				, width: 150
				, emptyText: _controller.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
		, dtpReinvestDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['ReinvestDate']		
				, itemId: 'dtpReinvestDate'		
				, width: 150
				, emptyText: _controller.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				, altFormats : DesktopWeb.Util.getAltDateFormats(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			}
		)
	}
	
	// **** buttons ****
	
	var _buttons = {
		cmdSearch: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Search']
				, handler: function() {_controller.doSearch(false);}						
			}
		)
		, cmdAddEvent: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Add']
				, handler: function(){_controller.openActionPopup('frmAddModEvent', _controller.ADD);}						
			}
		)
		, cmdModEvent: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Mod']
				, handler: function(){_controller.openActionPopup('frmAddModEvent', _controller.MOD);}						
			}
		)
		, cmdDelEvent: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Del']
				, handler: function(){_controller.openActionPopup('frmDelEvent', _controller.DEL);}						
			}
		)
		, cmdMoreEvent: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['More']
				, handler: function() {_controller.doSearch(true);}			
			}
		)
		, cmdSubmitEvent: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Ok']
			}
		)
		, cmdCancelEvent: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
			}
		) 
		, cmdAddModEventSubmit: new DesktopWeb.Controls.ActionButton(
			{
				itemId: 'addBtn'	
				,text: _translationMap['Ok']
				, handler: function(){
					if (_popups['frmAddModEvent'].isValid())
					{						
						_controller.doValidate(_popups['frmAddModEvent'].action, _popups['frmAddModEvent'].getData());
					}
				}
			}
		)
		, cmdAddModEventCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					if (_popups['frmAddModEvent'].isValid())
					{
						_popups['frmAddModEvent'].hide();
					}
				}
			}
		)
		, cmdDelEventSubmit: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Ok']
				, handler: function(){
					if (_popups['frmDelEvent'].isValid())
					{						
						_controller.doValidate(_popups['frmDelEvent'].action, _popups['frmDelEvent'].getData());
					}
				}
			}
		)
		, cmdDelEventCancel: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					if (_popups['frmDelEvent'].isValid())
					{
						_popups['frmDelEvent'].hide();
					}
				}
			}
		)
		, cmdExpand: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Expand']
				, width: 120
				, handler: function(){
					_controller.goToDetail();
				}
			}
		)
		//g1g2 buttons
		, cmdSubmitEventG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Ok']
			}
		)
		, cmdCancelEventG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
			}
		) 
		, cmdAddModEventSubmitG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Ok']
				, handler: function(){
					if (_popups['frmAddModEventG1G2'].isValid()) {
						_controller.doValidate(_popups['frmAddModEventG1G2'].action, _popups['frmAddModEventG1G2'].getData());
					}
				}
			}
		)
		, cmdAddModEventCancelG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					_popups['frmAddModEventG1G2'].hide();	
				}
			}
		)
		, cmdDelEventSubmitG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Ok']
				, handler: function(){

					if (_popups['frmDelEventG1G2'].isValid())
					{						
						_controller.doValidate(_popups['frmDelEventG1G2'].action, _popups['frmDelEventG1G2'].getData());
					}
				}
			}
		)
		, cmdDelEventCancelG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Cancel']
				, handler: function(){
					if (_popups['frmDelEventG1G2'].isValid())
					{
						_popups['frmDelEventG1G2'].hide();
					}
				}
			}
		)
		, cmdAddEventG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Add']
				, handler: function(){_controller.openActionPopup('frmAddModEventG1G2', _controller.ADD);}						
			}
		)
		, cmdModEventG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Mod']
				, handler: function(){_controller.openActionPopup('frmAddModEventG1G2', _controller.MOD);}						
			}
		)
		, cmdDelEventG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Del']
				, handler: function(){_controller.openActionPopup('frmDelEventG1G2', _controller.DEL);}						
			}
		)
		, cmdMoreEventG1G2: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['More']
				, handler: function() {_controller.doSearch(true);}			
			}
		)
	}
	
	// **** grids ****
	var _grids = {
		grdEvent: new DesktopWeb.AdvancedControls.GridPanel
		(
			{
				width: _layoutWidth
				, style: "margin-bottom:15px"
				, autoScroll: true
				, height: 250
				, store: new Ext.data.XmlStore
				(
					{
						record: 'Event'
						, fields: ['valnDate', 
									'crysFlag',
									'distFlag',
									'runMode',
									'nodeID',
									'version',
									'errMsg']
						, listeners: {
							load: function(store, records) {						  
								Ext.each(records, function(record){
									record.data.valnDate = DesktopWeb.Util.getDateDisplayValue(record.data.valnDate);
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
						, listeners: {
							rowselect: function(selModel, index, record)
							{
								_controller.setSelectedEvent(record.get("nodeID"));
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
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
							 , width: 25 }
							, {header: _translationMap['ValuationDate'], dataIndex: 'valnDate', width:200}
							, {header: _translationMap['CrystalisationDate'], dataIndex: 'crysFlag', width:200}
							, {header: _translationMap['DistributionDate'], dataIndex: 'distFlag', width:200}
						]
					}
				)
				, buttons: [					
					_buttons['cmdAddEvent']
					, _buttons['cmdModEvent']
					, _buttons['cmdDelEvent']	
					, _buttons['cmdMoreEvent']
				]
			}
		),

		grdEventG1G2: new DesktopWeb.AdvancedControls.GridPanel
		(
			{
				width: _layoutWidth
				, style: "margin-bottom:15px"
				, autoScroll: true
				, height: 250
				, store: new Ext.data.XmlStore
				(
					{
						record: 'Event'
						, fields: ['eventDate', 
									'exDate',
									'payDate',
									'reinvDate',
									'distribType',
									'distribIndicator',
									'runMode',
									'nodeID',
									'version',
									'errMsg']
						, listeners: {
							load: function(store, records) {								
								Ext.each(records, function(record){
									record.data.eventDate = DesktopWeb.Util.getDateDisplayValue(record.data.eventDate);
									record.data.payDate = DesktopWeb.Util.getDateDisplayValue(record.data.payDate);
									record.data.exDate = DesktopWeb.Util.getDateDisplayValue(record.data.exDate);
									record.data.reinvDate = DesktopWeb.Util.getDateDisplayValue(record.data.reinvDate);
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
						, listeners: {
							rowselect: function(selModel, index, record)
							{
								_controller.setSelectedEvent(record.get("nodeID"));
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
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
							 , width: 25 }
							, {header: _translationMap['RecordDate'], dataIndex: 'eventDate', width:105}
							, {header: _translationMap['ExDate'], dataIndex: 'exDate', width:105}
							, {header: _translationMap['PayDate'], dataIndex: 'payDate', width:105}
							, {header: _translationMap['ReinvestDate'], dataIndex: 'reinvDate', width:105}
							, {header: _translationMap['DistributionType'], dataIndex: 'distribType', renderer: function(value){return _controller.getOptionDescription('distribTypeListVal', value)}, width:125}									
							, {header: _translationMap['DistributionIndicator'], dataIndex: 'distribIndicator', renderer: function(value){return _controller.getOptionDescription('distribIndicatorListVal', value)}, width:125}									
						]
					}
				)
				
			, buttons: [					
					_buttons['cmdAddEventG1G2']
					, _buttons['cmdModEventG1G2']
					, _buttons['cmdDelEventG1G2']	
					, _buttons['cmdMoreEventG1G2']
				]
			}	
		)
	}
	
	// **** popups ****
	var _popups = {	
		frmAddModEvent: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 600
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						layout: 'form'
						, defaults: {border: false, labelWidth:50}
						, items: [
							{
								layout: 'column'								
								, style: 'padding:4px'
								, defaults: {border: false}
								,items: [
									{
										width: 350
										, layout: 'form'
										, labelWidth: 120
										, defaults: {border: false}
										, items: [ 
											_fields['dtpValudationDate'] 
										]
									}
									, {
										layout: 'form'
										, items: [
											_fields['chkCrystalisation']
											, _fields['chkDistribution']
										]
									}
								]
							}
						]
					}
				]
				,buttons: [
					_buttons['cmdAddModEventSubmit']
					, _buttons['cmdAddModEventCancel']				
				]
				, init: function(action)
				{					
					this.action = action;						
					this.enableAllFields();
					this.clearAllFields();
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle(_translationMap['EventDateAdd']);
							_controller.setDefaultNewEvent();
							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['EventDateMod']);
							_controller.populateEvent();
							break;
						}
					}					
				}
				, getData: function()
				{
					var data = {};
					data["valnDate"] =  _fields['dtpValudationDate'].getSMVDateString();
					data["crysFlag"] =  _fields['chkCrystalisation'].getValue();
					data["distFlag"] = _fields['chkDistribution'].getValue();				
					return data;
				}
				, disableAllFields: function()
				{
					_fields['dtpValudationDate'].disableField();
					_fields['chkCrystalisation'].disableField();
					_fields['chkDistribution'].disableField();
				}
				, enableAllFields: function()
				{
					_fields['dtpValudationDate'].enableField();
					_fields['chkCrystalisation'].enableField();
					_fields['chkDistribution'].enableField();
				}
			}		
		)
		, frmDelEvent: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				, width: 600
				, closeAction: 'hide'
				, modal: true
				, defaults: {border:false}
				, items: [
					{
						layout: 'form'
						, defaults: {border: false, labelWidth:50}
						, items: [
							{
								layout: 'column'								
								, style: 'padding:4px'
								, defaults: {border: false}
								,items: [ 
									{
										width: 500
										, layout: 'form'
										, labelWidth: 180
										, defaults: {border: false}
										, items: [ 
											_fields['txtDelValuationDate'] 
											, _fields['txtDelCrystalisation'] 
											, _fields['txtDelDistribution'] 
										]
									}
								]
							}
						]
					}
				]
				, buttons: [
					_buttons['cmdDelEventSubmit']
					, _buttons['cmdDelEventCancel']				
				]
				, init: function(action)
				{					
					this.action = "del";
					this.setTitle(_translationMap['EventDateDel']);
					_controller.populateDelEvent();
					this.disableAllFields();
				}
				, getData: function()
				{
					var data = {};
					data["valnDate"] =  DesktopWeb.Util.getSMVDateValue(_fields['txtDelValuationDate'].getValue());
					data["crysFlag"] =  _fields['txtDelCrystalisation'].getValue();
					data["distFlag"] = _fields['txtDelDistribution'].getValue();				
					return data;
				}
				, disableAllFields: function()
				{
					_fields['txtDelValuationDate'].disableField();
					_fields['txtDelCrystalisation'].disableField();
					_fields['txtDelDistribution'].disableField();
				}
			}
		)
		//G2G2
		,frmAddModEventG1G2: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 600
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
							{
								layout: 'column'	
								,style: 'padding:6px'								
								,defaults: {border: false, layout: 'form'}
								,items: [					
									{	
										columnWidth: .50
										,labelWidth: 100		
										,items: [
											_fields['dtpRecordDate'] 
											,_fields['dtpExDate'] 
											,_fields['dtpPayDate'] 
									 	]
									}
									 
									,{
										columnWidth: .50
										,labelWidth: 120
										,items: [
											_fields['dtpReinvestDate'] 
											,_fields['distributionType'] 	
											,_fields['distributionIndicator'] 												
									]
							}																	
						]
					}			
				]
				,buttons: [
					_buttons['cmdAddModEventSubmitG1G2']
					,_buttons['cmdAddModEventCancelG1G2']				
				]
				, init: function(action)
				{					
					this.action = action;						
					this.enableAllFields();
					this.clearAllFields();
					
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle(_translationMap['EventDateAdd']);
							_controller.setDefaultNewEvent();
							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['EventDateMod']);
							_controller.populateEventG1G2();
							break;
						}
					}					
				}
				, getData: function()
				{
					var data = {};
					
					data["eventDate"] =  _fields['dtpRecordDate'].getSMVDateString();	
					data["exDate"] =  _fields['dtpExDate'].getSMVDateString();
					data["payDate"] =  _fields['dtpPayDate'].getSMVDateString();
					data["reinvDate"] =  _fields['dtpReinvestDate'].getSMVDateString();
					data["distribType"] =  _fields['distributionType'].getValue();
					data["distribIndicator"] =  _fields['distributionIndicator'].getValue();

					return data;
				}
				, disableAllFields: function()
				{
					_fields['dtpRecordDate'].disableField();
				}
				, enableAllFields: function()
				{
					_fields['dtpRecordDate'].enableField();
				}
			}		
		)
		, frmDelEventG1G2: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				width: 600
				,modal: true
				,title: _translationMap['EventSchedule'] + " - " + _translationMap['Delete']
				,defaults: {border:false}
				,bodyStyle: 'padding:4px;'
				,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center; padding-bottom: 10px'														
				}														
				,{
					layout: 'column'																											
					,defaults: {border: false, labelWidth: 120, layout: 'form'}								
					,items: [
						{																						
							columnWidth: .5
							,items: [
								_fields['txtDeLRecordDate']
								,_fields['txtDeLExDate'] 
								,_fields['txtDeLPayDate'] 
							]
						}							
						,{		
							columnWidth: .5
							,items: [								
								_fields['txtDeLReinvestDate']
								,_fields['txtDeLDistributionType'] 
								,_fields['txtDeLDistributionIndicator'] 							
							]
						}																	
					]
				}
			]
				, buttons: [
					_buttons['cmdDelEventSubmitG1G2']
					, _buttons['cmdDelEventCancelG1G2']				
				]
				, init: function(action)
				{					
					this.action = "del";
					this.setTitle(_translationMap['EventDateDel']);
					_controller.populateDelEventG1G2();
					this.disableAllFields();
				}
				, getData: function()
				{
					var data = {};
					data["eventDate"] =  DesktopWeb.Util.parseSMVDateFormat(_fields['txtDeLRecordDate'].getValue());	
					data["exDate"] =  DesktopWeb.Util.parseSMVDateFormat(_fields['txtDeLExDate'].getValue());	
					data["payDate"] =  DesktopWeb.Util.parseSMVDateFormat(_fields['txtDeLPayDate'].getValue());		
					data["reinvDate"] =  DesktopWeb.Util.parseSMVDateFormat(_fields['txtDeLReinvestDate'].getValue());
					data["distribType"] =  _fields['txtDeLDistributionType'].getValue();
					data["distribIndicator"] =  _fields['txtDeLDistributionIndicator'].getValue();					
					return data;
				}
				, disableAllFields: function()
				{
					_fields['txtDeLRecordDate'].disableField();
					_fields['txtDeLExDate'].disableField();
					_fields['txtDeLPayDate'].disableField();
					_fields['txtDeLReinvestDate'].disableField();
					_fields['txtDeLDistributionType'].disableField();
					_fields['txtDeLDistributionIndicator'].disableField();
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
						layout: 'column'
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 80}	
						,items: [
							{
								width: 800
								, layout: 'column'
								, items: [
									{
										width: 420
										, layout: 'form'
										, labelWidth: 65
										, items: [_fields['cboFundClass']]
									}
									, {
										width: 380
										, layout: 'form'
										, labelWidth: 75
										, items: [_fields['eventType']]
									}
								]
							}
							, {
								width: 612
								, layout: 'column'
								, labelWidth: 100
								, items: [
									{
										width: 306
										, layout: 'form'
										, labelWidth: 65
										, items: [_fields['dtpStartDate']]
									}
									, {
										width: 306
										, layout: 'form'
										, labelWidth: 70
										, items: [_fields['dtpEndDate']]
									}
								]
							}
							, _buttons['cmdSearch']						
						]
					}
					,{					
						layout: 'form'
						, items: [
							_grids['grdEvent']
							,_grids['grdEventG1G2']
						]
					}
					, {
						xtype: 'fieldset'
						, style: 'position:relative; margin-left:0px; padding-left:10px;'
						, id: 'valuation_fieldset'	
						, title: _translationMap['Valuation']								
						, hideMode: 'offsets'
						, hidden: false
						, width: _layoutWidth
						, items: [
							{							
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnGav']
													, _fields['valnGav']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnNav']
													, _fields['valnNav']
												]
											}
										]
									}
								]
							}
							, {
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnClsHWM']
													, _fields['valnClsHWM']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnClsHWMDate']
													, _fields['valnClsHWMDate']
												]
											}
										]
									}
								]
							}
							, {
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnNumDay']
													, _fields['valnNumDay']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnPfPerShare']
													, _fields['valnPfPerShare']
												]
											}
										]
									}			
								]
							}
							, {
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnEffHurdle']
													, _fields['valnEffHurdle']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblValnClsAdjHWM']
													, _fields['valnClsAdjHWM']
												]
											}
										]
									}
								]
							}						
						]
					}
					, {
						xtype: 'fieldset'
						, style: 'position:relative; margin-left:0px; padding-left:10px;'
						, id: 'crystalisation_fieldset'	
						, title: _translationMap['Crystalisation']	
						, hideMode: 'offsets'
						, hidden: false
						, width: _layoutWidth
						, items: [
							{							
								layout: 'column'
								,style: "margin-bottom:10px;"
								,items: [
									{
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblCrysClsHWM']
													, _fields['crysClsHWM']
												]
											}
										]
									}
									, {
										width: (_layoutWidth / 2) - 15
										, layout: 'form'
										, items: [
											{
												width: (_layoutWidth / 2) - 15
												, layout: 'form'
												, items: [
													_fields['lblCrysGav']
													, _fields['crysGav']
												]
											}
										]
									}			
								]
							}
						]
					}
					, new Ext.Container({
						id: 'expand'
						, hideMode: 'offsets'
						, hidden: false
						, layout: 'form'	
						, style: 'text-align:right;'
						, items: [
							_buttons['cmdExpand']
						]
					})
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: 'OK'
					, handler: function(){ 
					if (_controller.isFrontValid()) 
					{ 
						DesktopWeb.Util.commitScreen(); } 
					}	
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