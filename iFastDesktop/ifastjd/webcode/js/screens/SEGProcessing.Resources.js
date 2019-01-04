/*********************************************************************************************
 * @file	SEGProcessing.Resources.js	
 * @author	Rod Walker
 * @desc	Resources JS file for SEG Processing screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 280;
	var _layoutWidth = 715;
	
	// **** fields ****
	var _fields = {
	}
	
	// **** grids ****
	var _grids = {
		eventSchedule: new DesktopWeb.AdvancedControls.GridPanel({
			width: 700
			,style: "padding-top:5px; padding-left:5px"
			,autoScroll: true
			,height: 240
			,store: new Ext.data.XmlStore({
				record: 'Detl'
				,fields: ['eventType'
						  ,'eventTypeDesc'
						  ,'eventTypeSched'
						  ,'cycleSeq'
						  ,'nextEventDt'
						  ,'elig'
						  ,'effectDt'
						  ,'stopDt'						  
						  ,'stat'
						  ,'statDesc'
						  ,'createdOn'
						  ,'schType'
						  ,'guarSelect'
						  ,'guarSelectDesc'						  
						  ,'finishDate'
						  ,'modDate'
						  ,'modUser'
						  ,'createdBy'
						  ,'eventMstrID'
						  ,'eventSchedID'
						  ,'polEventID'
						  ,'runMode'
						  ,'allowCanc'
						  ,'allowDel'
						  ,'allowProc'
						  ,'allowMod'
						  ,'newCMD']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.nextEventDt = DesktopWeb.Util.getDateDisplayValue(record.data.nextEventDt);
							record.data.effectDt = DesktopWeb.Util.getDateDisplayValue(record.data.effectDt);
							record.data.finishDate = DesktopWeb.Util.getDateDisplayValue(record.data.finishDate);		
							record.data.createdOn = DesktopWeb.Util.getDateDisplayValue(record.data.createdOn);			
							record.data.newCMD = DesktopWeb.Util.getDateDisplayValue(record.data.newCMD);							
						});

						store.fireEvent('datachanged', store); //to set data in grid again
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});																																		
					}
					,update: function(store)
					{												
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.updateActionButtons()}						
					,rowdeselect: function(){_controller.updateActionButtons()}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['EventDescription'], dataIndex: 'eventTypeSched', width:160}
					,{header: _translationMap['EventType'], dataIndex: 'eventType', width:70}
					,{header: _translationMap['CycleSeq'], dataIndex: 'cycleSeq', width:65}
					,{header: _translationMap['GuaranteeSelect'], dataIndex: 'guarSelectDesc', width:225}
					,{header: _translationMap['NextEventDate'], dataIndex: 'nextEventDt', width:90}
					,{header: _translationMap['Eligibility'], dataIndex: 'elig', width:60}
					,{header: _translationMap['EffDate'], dataIndex: 'effectDt', width:90}
					,{header: _translationMap['CreateDate'], dataIndex: 'createdOn', width:90}
					,{header: _translationMap['SchType'], dataIndex: 'schType', width:90}
					,{header: _translationMap['FinishDate'], dataIndex: 'finishDate', width:90}
					,{header: _translationMap['Status'], dataIndex: 'statDesc', width:75}
					,{header: _translationMap['NewCMD'], dataIndex: 'newCMD', width:90}
				]							
			})			
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']						
					,handler: function(){_controller.openEventSchPopup(_controller.ADD);}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openEventSchPopup(_controller.MOD);}
					,disabled: true							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openEventSchPopup(_controller.DEL);}
					,disabled: true							
				})				
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_controller.openEventSchPopup(_controller.CANCEL);}
					,disabled: true							
				})				
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'procBtn'
					,text: _translationMap['Process']
					,handler: function(){_controller.openEventSchPopup(_controller.PROCESS);}
					,disabled: true							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup();}
					,disabled: true
				})
			]			
		})
		
		,recalc: new DesktopWeb.AdvancedControls.GridPanel({
			width: 700
			,style: 'padding-left:5px; padding-top:5px'
			,autoScroll: true
			,height: 240
			,autoExpandColumn: 'stat'
			,store: new Ext.data.XmlStore({
				record: 'Detl'
				,fields: ['stat', 'recalcDate', 'createdBy', 'reason', 'guarImpact']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.recalcDate = DesktopWeb.Util.getDateDisplayValue(record.data.recalcDate);						
						});

						store.fireEvent('datachanged', store); //to set data in grid again																																		
					}
				}					
			})
			,disableSelection: true
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['RecalcStatus'], id: 'stat', dataIndex: 'stat'}
					,{header: _translationMap['RecalcDate'], dataIndex: 'recalcDate', width:100}
					,{header: _translationMap['CreatedBy'], dataIndex: 'createdBy', width:125}
					,{header: _translationMap['Reason'], dataIndex: 'reason', width:150}
					,{header: _translationMap['GuaranteeImpacted'], dataIndex: 'guarImpact', width:150}
				]							
			})			
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'processBtn'
					,text: _translationMap['Process']
					,disabled: true
					,handler: function(){_controller.doRecalcProcess();}							
				})
			]			
		})
	}
	
	// **** popups ****
	var _popups = {
		eventSchedulePopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 575
			,defaults: {border:false}
			,modal: true
			,listeners: {
				beforeShow: function(){_popups['eventSchedulePopup'].init()}
				,show: function(){_popups['eventSchedulePopup'].populateFields()}
			}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center'
				}
				,{
					html: _translationMap['CancelConfirmMsg']
					,style: 'text-align:center'
				}
				,{
					html: _translationMap['ProcessConfirmMsg']
					,style: 'text-align:center'
				}
				,{
					layout: 'column'
					,style: 'padding-left:4px; padding-top: 4px;'																							
					,items: [
						{
							layout: 'form'
							,width: 350
							,labelWidth: 115
							,border: false
							,items: [
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'eventType'
									,width: 180
									,fieldLabel: _translationMap['EventDescription']
									,allowBlank: false
									,listeners: {
										change: function(fld) {_controller.handleEventTypeChangeInPopup()}
										,select: function(fld) {_controller.handleEventTypeChangeInPopup()}
									}
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'eventTypeSched'
									,width: 180
									,fieldLabel: _translationMap['EventType']																		
								})										
								,new DesktopWeb.Controls.DateField({
									itemId: 'nextEventDate'
									,allowBlank: false
									,width: 100
									,fieldLabel: _translationMap['NextEventDate']
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})								
								,new DesktopWeb.Controls.DateField({
									itemId: 'newCMD'
									,width: 100
									,fieldLabel: _translationMap['NewCMD']
									,validator: function(val){																			
										if (!this.disabled && val == "")
										{											
											return _translationMap['FldRequired'];
										}										
										return true;										
									}
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
							]
						}
						,{
							layout: 'form'
							,width: 200
							,labelWidth: 90
							,border: false
							,items: [
								new DesktopWeb.Controls.Label({
									itemId: 'createDate'
									,width: 100
									,fieldLabel: _translationMap['CreateDate']									
								})									
								,new DesktopWeb.Controls.Label({
									itemId: 'schType'
									,width: 100									
									,fieldLabel: _translationMap['SchType']
								})
								,new DesktopWeb.Controls.Label({
									itemId: 'stat'
									,width: 100									
									,fieldLabel: _translationMap['Status']														
								})
							]
						}						
					]												
				}
				,{
					layout: 'form'					
					,labelWidth: 115
					,style: 'padding-left:4px'				
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'guarSelect'									
							,width: 375
							,fieldLabel: _translationMap['GuaranteeSelect']
							,validator: function(val){
								if (!this.disabled && val == "")
								{
									return _translationMap['FldRequired'];
								}
								return true;										
							}
						})
					]
				}			
			]			
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['eventSchedulePopup'].isValid())
						{
							_controller.saveEventSchPopup(_popups['eventSchedulePopup'].action, _popups['eventSchedulePopup'].getData());							
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){
						_popups['eventSchedulePopup'].hide();
					}
				})				
			]			
			,init: function()
			{																		
				this.get(0).hide(); //hide delete message				
				this.get(1).hide(); //hide cancel message
				this.get(2).hide(); //hide process message
				
				switch(this.action)
				{
					case _controller.ADD:
					{									
						this.setTitle(_translationMap["SEGEventSchedule"] + " - " + _translationMap["Add"]);																
						break;
					}
					case _controller.MOD:
					{												
						this.setTitle(_translationMap["SEGEventSchedule"] + " - " +  _translationMap["Modify"]);													
						break;
					}
					case _controller.DEL:
					{						
						this.setTitle(_translationMap["SEGEventSchedule"] + " - " + _translationMap["Delete"]);
						this.get(0).show(); //show delete message											
						break;
					}
					case _controller.CANCEL:
					{						
						this.setTitle(_translationMap["SEGEventSchedule"] + " - " + _translationMap["Cancel"]);
						this.get(1).show(); //show cancel message													
						break;
					}										
					case _controller.PROCESS:
					{						
						this.setTitle(_translationMap["SEGEventSchedule"] + " - " + _translationMap["Process"]);
						this.get(2).show(); //show process message													
						break;
					}														
				}												
			}
			,populateFields: function()
			{
				this.clearPopupFields();								
				switch(this.action)
				{
					case _controller.ADD:
					{
						this.enablePopupFields();																								
						this.populateWithDefaultValues();
						this.getField('guarSelect').disable();
						this.getField('newCMD').disable();
						break;
					}
					case _controller.MOD:
					{
						this.enablePopupFields();																											
						this.populateWithSelectedRecord();
						_controller.handleEventTypeChangeInPopup()
						this.populateWithSelectedRecord();
						break;
					}
					case _controller.DEL:
					{						
						this.disablePopupFields();							
						this.populateWithSelectedRecord();						
						break;
					}
					case _controller.CANCEL:
					{						
						this.disablePopupFields();							
						this.populateWithSelectedRecord();
						break;
					}
					case _controller.PROCESS:
					{						
						this.disablePopupFields();							
						this.populateWithSelectedRecord();
						break;
					}					
				}				
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['eventSchedule'].getSelectedRecord();				
				this.getField('eventType').setValue(rec.data['eventType']);
				if (rec.data['runMode'] == _controller.ADD)
				{
					this.getField('eventType').enable();
				}
				else
				{
					this.getField('eventType').disable();	
				}

				this.getField('eventTypeSched').setValue(rec.data['eventTypeSched']);
				this.getField('nextEventDate').setValue(rec.data['nextEventDt']);
				this.getField('stat').setValue(rec.data['statDesc']);
				this.getField('stat').statCode = rec.data['stat']
				this.getField('schType').setValue(rec.data['schType']);							
				this.getField('guarSelect').setValue(rec.data['guarSelect']);
				this.getField('newCMD').setValue(rec.data['newCMD']);
				this.getField('createDate').setValue(rec.data['createdOn']);
			}
			,populateWithDefaultValues: function()
			{
				var defaultValues = _controller.getDefaultValues()
				this.getField('createDate').setValue(defaultValues['createDate']);
				this.getField('nextEventDate').setValue(defaultValues['nextEventDt']);
				this.getField('schType').setValue(defaultValues['schType']);
				this.getField('stat').setValue(defaultValues['statDesc']);
				this.getField('stat').statCode = defaultValues['stat'];					
				this.getField('guarSelect').setValue(defaultValues['guarSelect']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['eventType'] = this.getField('eventType').getValue();				
				data['eventTypeSched'] = this.getField('eventTypeSched').getValue();
				data['nextEventDt'] = this.getField('nextEventDate').getDisplayDateString();
				data['stat'] = this.getField('stat').statCode;
				data['statDesc'] = this.getField('stat').getValue();
				data['schType'] = this.getField('schType').getValue();
				data['guarSelect'] = this.getField('guarSelect').getValue();
				data['guarSelectDesc'] = (data['guarSelect'] ? this.getField('guarSelect').getSelectedRecord().data['value'] : "");				
				data['newCMD'] = this.getField('newCMD').getDisplayDateString();
				data['createdOn'] = this.getField('createDate').getValue();
				
				if (this.action == _controller.ADD)
				{
					var defaultValues = _controller.getDefaultValues()
					data['effectDt'] = defaultValues['effectDt'];
					data['elig'] = defaultValues['elig']; 
				}
				else
				{
					var rec = _grids['eventSchedule'].getSelectedRecord();
					data['cycleSeq'] = rec.data['cycleSeq'];
					data['elig'] = rec.data['elig'];
					data['effectDt'] = rec.data['effectDt'];
					data['stopDt'] = rec.data['stopDt'];		
					data['finishDate'] = rec.data['finishDate'];				
					data['eventMstrID'] = rec.data['eventMstrID'];					
					data['eventSchedID'] = rec.data['eventSchedID'];
					data['polEventID'] = rec.data['polEventID'];					
				}	
				
				return data;
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
				this.getField('procDate').setValue(data['createdOn']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['createdBy']);
				this.getField('modUser').setValue(data['modUser']);	
			}
		})
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
						region: 'center'
						,xtype: 'tabpanel'
						,height: 275
						,activeTab: 'eventSchd'
						,style: 'padding-left:5px'
						,items: [
							{
								title: _translationMap['EventSchedule']
								,id: 'eventSchd'
								,items: [
									_grids['eventSchedule']									
								]
							}
							,{
								title: _translationMap['RecalculationRequest']
								,id: 'recalcReq'
								,items: [
									_grids['recalc']
								]
							}
						]
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){DesktopWeb.Util.commitScreen()}
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