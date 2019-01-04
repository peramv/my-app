/*********************************************************************************************
 * @file	RESPGrantInfo.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for RESP Grant Information screen.
 *
 * History: Supareuk S. PETP0181067 FN01 CHG0034430 T54333
 *          - Getting the date format from DesktopWeb.Util.getDateDisplayValue to show
 *            all date with correct format from registry field
 *
 *  30 Apr 2014 G. Thawornwachirakun P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *  23 May 2014 Narin Suanlamyai P0220132 FN03 T55087
 *					- Set From Date and To Date fields as mandatory fields
 *
 *  10 July 2014 Narin Suanlamyai P0220132 FN03 DFT0036690 T55410
 *					- Fix validate From Date/To Date against SAGES Request transaction.
 *
 *  21 Jul 2014 Narin Suanlamyai P0220132 FN03 DFT0037101 T55450
 *					- Hide SAGES section for non-SAGES environment.
 *
 *  15 Aug 2014 Narin Suanlamyai P0220132 FN03 DFT0037927 T55561
 *					- Restriction to authorized users for SAGES Grant fields.
 *
 *  20 Nov 2015 Aurkarn Mongkonrat P0241773 T81771 DFT0055645
 *					  - Separate the redesigned screen to a new program.
 *
 *********************************************************************************************/

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 680;
	
	// **** buttons ****
	var _buttons = {
		sages: {
			cancelRequestBtn: new DesktopWeb.Controls.ActionButton({
				text: _translationMap['CancelRequest']
				,handler: function() {
					_controller.openActionPopup('sagesCancelRequest');
				}
			}) 
		}
	}
	
	// **** fields ****
	var _fields = {
		sin: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['SIN']
			,width: 100			
		})
		,dob: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['DateOfBirth']
			,width: 100			
		})
		,taxjuris: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TaxJurisdiction']
			,width: 100			
		})		
		,taxTypeDesc: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['TaxType']
			,width: 100			
		})
		,siblingOnly: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['SiblingOnly']
			,width: 100			
		})
		,specimenNum: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['SpecimenNum']
			,width: 100			
		})
		,beneAddr: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Address']
			,width: 400			
		}) 
		
		,pcgName: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Name']			
			,width: 200			
		})
		,pcgSINBN: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['SIN_BN']
			,width: 75			
		})
		
		,cesg: {
			currStat: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['CurrentStatus']
				,width: 100			
			}) 
			,newStat: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['NewStatus']
				,width: 100
				,listeners: {
					select: function(){_controller.handleCESGStatusChange()}						
					,blur: function(){_controller.handleCESGStatusChange()}
					,change: function(){_controller.handleCESGChange()}
				}			
			})
			,genRT511: new DesktopWeb.Controls.YesNoComboBox({
				fieldLabel: _translationMap['GenerateRT511']
				,width: 100
				,listeners: {
					change: function(){_controller.handleCESGChange()}	
				}									
			})
			,cutOffDate: new DesktopWeb.Controls.DateField({
				fieldLabel: _translationMap['CutOffDate']
				,width: 100
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,listeners: {
					change: function(){_controller.handleCESGChange()}	
				}						
			})
			,createdby: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['CreatedBy']
				,width: 100			
			})
			,procdate: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['ProcessDate']
				,width: 100			
			})
			,moduser: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['ModUser']
				,width: 100			
			})
			,moddate: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['ModDate']
				,width: 100			
			})
		}
		
		,clb: {
			currStat: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['CurrentStatus']
				,width: 100			
			}) 
			,newStat: new DesktopWeb.Controls.SMVComboBox({
				fieldLabel: _translationMap['NewStatus']
				,width: 100
				,listeners: {
					change: function(){_controller.handleCLBChange()}	
				}			
			})			
			,createdby: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['CreatedBy']
				,width: 100			
			})
			,procdate: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['ProcessDate']
				,width: 100			
			})
			,moduser: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['ModUser']
				,width: 100			
			})
			,moddate: new DesktopWeb.Controls.Label({
				fieldLabel: _translationMap['ModDate']
				,width: 100			
			})
		}
		
		,sages: {
			requestFlag: new DesktopWeb.Controls.YesNoComboBox({
				fieldLabel: _translationMap['SAGESRequest']
				,allowBlank: false
				,width: 50
				,tabIndex : 1
				, listeners:{
					select: function(record) {
						_controller.handleSAGESRequestFlagChange(record.getValue());
					}
				}
			})			
			,applicationDate: new DesktopWeb.Controls.DateField({
				fieldLabel: _translationMap['SAGESApplicationDate']
				,width: 100
				,tabIndex : 2
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,maxText: _translationMap['ERR_APPDATE_CANNOT_GREATER_THAN_SYSDATE']
				,minText: _translationMap['ERR_APPDATE_CANNOT_LESS_THAN_SAGESDEFF']
				,blankText: _translationMap['ERR_APPDATE_CANNOT_BLANK_FLAG_YES']
			})
			,stopDate: new Ext.form.DisplayField({
				fieldLabel: _translationMap['StopDate']
				,width: 50
				,value : ''
			})
			,fromDate: new Ext.form.DisplayField({
				fieldLabel: _translationMap['CancelRequest'] + ' ' + _translationMap['FromDate']
				,labelStyle: 'color:red'
				,style: 'color:red; border:none; background-color:transparent;'
				,value: ''
				,hideMode: 'visibility'
				,hidden: true
			})			
			,toDate: new Ext.form.DisplayField({
				fieldLabel: _translationMap['ToDate']
				,labelStyle: 'color:red'
				,style: 'color:red; border:none; background-color:transparent;'
				,value: ''
				,hideMode: 'visibility'
				,hidden: true
			})			
		}
	}
		
	// **** grids ****
	var _grids = {
		aces: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 50 
			,autoScroll: true							
			,height: 115
			,autoExpandColumn: 'currStatDesc'				
			,store: new Ext.data.XmlStore({
				record: 'ACESRecord'
				,fields: ['runMode', 
						  'grantType', 
						  'stat', 
						  'currStatDesc',
						  'newStat',
						  'newStatDesc', 
						  'grantOpt', 
						  'grantDesc', 
						  'grantInfoID',
						  'createdBy',
						  'procDate',
						  'modDate',
						  'modUser',
						  'version',
						  'allowStatUpd']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);
							record.data['procDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['procDate']);							
						});
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
					rowselect: function(selModel, index, record){_controller.handleRecordSelectChange('aces');}
					,rowdeselect: function(){_controller.handleRecordSelectChange('aces');}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{id: 'currStatDesc', header: _translationMap['CurrentStatus'], dataIndex: 'currStatDesc'}
					,{header: _translationMap['NewStatus'], dataIndex: 'newStatDesc', width: 110}
					,{header: _translationMap['GrantOption'], dataIndex: 'grantDesc', width: 110}
					,{header: _translationMap['CreatedBy'], dataIndex: 'createdBy', width:75}
					,{header: _translationMap['ProcessDate'], dataIndex: 'procDate', width:80}
					,{header: _translationMap['ModUser'], dataIndex: 'modUser', width:75}
					,{header: _translationMap['ModDate'], dataIndex: 'modDate', width:80}					
				]							
			})				
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup('aces', _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,disabled: true
					,handler: function(){_controller.openActionPopup('aces', _controller.MOD);}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'								
					,text: _translationMap['Delete']
					,disabled: true							
					,handler: function(){_controller.openActionPopup('aces', _controller.DEL);}
				})
			]			
		})
		,qesi: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 50
			,autoScroll: true							
			,height: 115
			,autoExpandColumn: 'currStatDesc'				
			,store: new Ext.data.XmlStore({
				record: 'QESIRecord'
				,fields: ['runMode', 
						  'grantType', 
						  'stat', 
						  'currStatDesc',
						  'newStat',
						  'newStatDesc',						  
						  'grantOpt', 
						  'grantYr', 
						  'grantInfoID',
						  'createdBy',
						  'procDate',
						  'modDate',
						  'modUser',
						  'version',
						  'allowStatUpd',
						  'stopReason',
						  'stopReasonDesc']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);
							record.data['procDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['procDate']);							
						});
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
					rowselect: function(selModel, index, record){_controller.handleRecordSelectChange('qesi');}
					,rowdeselect: function(){_controller.handleRecordSelectChange('qesi');}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{id: 'currStatDesc', header: _translationMap['CurrentStatus'], dataIndex: 'currStatDesc'}
					,{header: _translationMap['NewStatus'], dataIndex: 'newStatDesc', width: 100}
					,{header: _translationMap['Year'], dataIndex: 'grantYr', width: 50}
					,{header: _translationMap['StopReason'], dataIndex: 'stopReasonDesc', width: 100}
					,{header: _translationMap['CreatedBy'], dataIndex: 'createdBy', width:75}
					,{header: _translationMap['ProcessDate'], dataIndex: 'procDate', width:80}
					,{header: _translationMap['ModUser'], dataIndex: 'modUser', width:75}
					,{header: _translationMap['ModDate'], dataIndex: 'modDate', width:80}					
				]							
			})				
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup('qesi', _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,disabled: true
					,handler: function(){_controller.openActionPopup('qesi', _controller.MOD);}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'								
					,text: _translationMap['Delete']
					,disabled: true							
					,handler: function(){_controller.openActionPopup('qesi', _controller.DEL);}
				})
			]			
		})		
	}
	
	var _popups = {
		aces: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 290
			,action: null						
			,modal: true			
			,defaults: {border:false}
			,grantInfoID: null
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']							
					,style: 'text-align:center'														
				}						
				,{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 90
					,items: [						
						new DesktopWeb.Controls.Label({
							itemId: 'curStat'
							,width: 150
							,fieldLabel: _translationMap['CurrentStatus']
							,allowBlank: false														
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'newStat'
							,width: 150
							,fieldLabel: _translationMap['NewStatus']
							,allowBlank: false														
						})											
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'grantOption'
							,width: 150									
							,fieldLabel: _translationMap['GrantOption']
							,allowBlank: false														
						})							
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['aces'].isValid())
						{
							_controller.saveACESPopup(_popups['aces'].action, _popups['aces'].getData());
						}
					}							
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['aces'].hide();}
				})
			]
			,setAction: function(action)
			{
				this.action = action;
			}
			,init: function(action)
			{
				this.action = action;																		
				this.clearAllFields();
				this.get(0).hide(); //hide delete message				
				switch(this.action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['GrantType_ACES'] + ' - ' + _translationMap['Add']);											
						this.enableAllFields();
						this.getField('newStat').loadData(_controller.getStatusOptions('ACES', "Blank"));
						this.getField('curStat').hide();
						this.getField('newStat').show();																					
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['GrantType_ACES'] + ' - ' + _translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();
						this.getField('grantOption').disableField();
						this.getField('curStat').show();
						this.getField('newStat').show();																						
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['GrantType_ACES'] + ' - ' + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();
						this.getField('curStat').hide();
						this.getField('newStat').show();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['aces'].getSelectedRecord();
				this.grantInfoID = rec.data['grantInfoID'];				
				this.getField('grantOption').setValue(rec.data['grantOpt']);			
				this.getField('curStat').setValue(rec.data['currStatDesc']);				
				this.getField('newStat').loadData(_controller.getStatusOptions('ACES', (rec.data['stat'] ? rec.data['stat'] : "Blank")));
				if (rec.data['newStat'])
				{
					this.getField('newStat').setValue(rec.data['newStat']);
				}				
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;	
				data['grantInfoID'] = this.grantInfoID;			
				data['newStat'] = this.getField('newStat').getValue();
				data['newStatDesc'] = this.getField('newStat').getValueDesc();					
				data['grantOpt'] = this.getField('grantOption').getValue();				
				data['grantDesc'] = this.getField('grantOption').getValueDesc();
				return data;
			}		
		})
		,sagesCancelRequest: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 235
			,modal: true			
			,title: _translationMap['CancelRequest']
			,defaults: {border:false}
			,items: [
				{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 90
					,items: [						
						new DesktopWeb.Controls.DateField({
							itemId: 'fromDate'
							,fieldLabel: _translationMap['FromDate']
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
							,allowBlank: false
							,width: 100
							,maxText: _translationMap['ERR_DATE_CANNOT_GREATER_THAN_CURDATE']
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'toDate'
							,fieldLabel: _translationMap['ToDate']
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
							,allowBlank: false
							,width: 100
							,maxText: _translationMap['ERR_DATE_CANNOT_GREATER_THAN_CURDATE']
						})
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_controller.validateSAGESCancelRequest())
						{
							_controller.saveSAGESCancelRequest(_popups['sagesCancelRequest'].getData());
						}
					}							
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['sagesCancelRequest'].hide();}
				})
			]
			,init: function()
			{
				this.clearAllFields();
				this.enableAllFields();
				this.populate();
			}
			,populate: function()
			{
				// set from/to date fields if user already provided.
				_controller.populateCancelRequestPoupup();
			}
			,getData: function()
			{
				var data = {};
				data['fromDate'] = this.getField('fromDate').getValue();
				data['toDate'] = this.getField('toDate').getValue();					
				return data;
			}		
		})
		,qesi: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 400
			,action: null						
			,modal: true			
			,defaults: {border:false}
			,grantInfoID: null
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']							
					,style: 'text-align:center'														
				}						
				,{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 90
					,items: [
						new DesktopWeb.Controls.Label({
							itemId: 'curStat'
							,width: 150
							,fieldLabel: _translationMap['CurrentStatus']
							,allowBlank: false														
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'newStat'
							,width: 150
							,fieldLabel: _translationMap['NewStatus']
							,allowBlank: false
							,listeners: {
								select: function(){									
									if (_popups['qesi'].getField('newStat').getValue() == 'Stopped')
									{
										_popups['qesi'].getField('stopReason').enableField();
									}
									else
									{
										_popups['qesi'].getField('stopReason').reset();
										_popups['qesi'].getField('stopReason').disableField();
									}
								}
							}														
						})											
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'year'
							,width: 85									
							,fieldLabel: _translationMap['Year']
							,allowBlank: false														
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'stopReason'
							,width: 265									
							,fieldLabel: _translationMap['StopReason']
							,validator: function(){
								if (_popups['qesi'].getField('newStat').getValue() == 'Stopped'
									&& _popups['qesi'].getField('stopReason').getValue() == "")
								{
									return _translationMap['FldRequired'];
								}
								else
								{
									return true;
								}
							}																				
						})		
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['qesi'].isValid())
						{
							_controller.saveQESIPopup(_popups['qesi'].action, _popups['qesi'].getData());
						}
					}							
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['qesi'].hide();}
				})
			]
			,setAction: function(action)
			{
				this.action = action;
			}
			,init: function(action)
			{
				this.action = action;																		
				this.clearAllFields();
				this.get(0).hide(); //hide delete message				
				switch(this.action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['GrantType_QESI'] + ' - ' + _translationMap['Add']);											
						this.enableAllFields();
						this.getField('newStat').loadData(_controller.getStatusOptions('QESI', "Blank"));
						this.getField('curStat').hide();
						this.getField('stopReason').hide();
						this.getField('newStat').show();																					
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['GrantType_QESI'] + ' - ' + _translationMap['Modify']);
						this.enableAllFields();
						this.populateWithSelectedRecord();
						this.getField('year').disableField();
						this.getField('stopReason').disableField();
						this.getField('curStat').show();
						this.getField('newStat').show();																						
						this.getField('stopReason').show();
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['GrantType_QESI'] + ' - ' + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();
						this.getField('curStat').hide();
						this.getField('newStat').show();
						this.getField('stopReason').hide();																							
						break;
					}
				}														
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['qesi'].getSelectedRecord();
				this.grantInfoID = rec.data['grantInfoID'];										
				this.getField('curStat').setValue(rec.data['currStatDesc']);				
				this.getField('newStat').loadData(_controller.getStatusOptions('QESI', (rec.data['stat'] ? rec.data['stat'] : "Blank")));
				if (rec.data['newStat'])
				{
					this.getField('newStat').setValue(rec.data['newStat']);
				}
				this.getField('year').setValue(rec.data['grantYr']);
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;
				data['grantInfoID'] = this.grantInfoID;
				data['newStat'] = this.getField('newStat').getValue();
				data['newStatDesc'] = this.getField('newStat').getValueDesc();					
				data['grantYr'] = this.getField('year').getValue();
				data['stopReason'] = this.getField('stopReason').getValue();								
				data['stopReasonDesc'] = this.getField('stopReason').getValueDesc();
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
		
		,buttons : _buttons
		
		,grids: _grids
		
		,popups: _popups			
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,style: 'padding-left:5px; padding-right:5px;overflow-y:auto;'
			,autoScroll: true
			,defaults: {width: _layoutWidth - 40}			
			,items: [
				{
					xtype: 'fieldset'				
					,title: _translationMap['RESPBeneficiary']
					,id: 'beneFieldset'
					
					,items: [
						{
							layout: 'column'					
							,defaults: {
								layout: 'form'								
								,columnWidth: 0.33
							}
							,items: [
								{
									labelWidth: 65
									,items: [
										_fields['sin']										
										,_fields['taxTypeDesc']
									]							
								}
								,{
									labelWidth: 80
									,items: [
										_fields['dob']										
										,_fields['siblingOnly']
										
									]							
								}
								,{
									labelWidth: 90
									,items: [
										_fields['taxjuris']
										,_fields['specimenNum']										
									]							
								}
							]
						}
						,{
							layout: 'form'
							,labelWidth: 65
							,items: [
								_fields['beneAddr']
							]
						}						
					]
				}
				,{
					xtype: 'fieldset'				
					,title: _translationMap['PrimaryCareGiver_PCG']
					,layout: 'column'
					,defaults: {
						layout: 'form'
						,labelWidth: 65						
					}
					,items: [
						{
							width: 440 
							,items: [_fields['pcgName']]
						}
						,{
							width: 200
							,items: [_fields['pcgSINBN']]
						}
					]
				}
				,{
					xtype: 'fieldset'				
					,title: _translationMap['AdditionalCESG']
					,layout: 'column'					
					,defaults: {
						layout: 'form'											
					}
					,items: [
						{
							columnWidth: 0.4
							,labelWidth: 100
							,items: [
								_fields['cesg']['currStat']								
								,_fields['cesg']['newStat']								
								,_fields['cesg']['genRT511']
																						
							]							
						}
						,{
							columnWidth: 0.3
							,labelWidth: 80
							,items: [							
								_fields['cesg']['createdby']
								,_fields['cesg']['moduser']
								,_fields['cesg']['cutOffDate']	
							]							
						}
						,{
							columnWidth: 0.3
							,labelWidth: 80
							,items: [								
								_fields['cesg']['procdate']
								,_fields['cesg']['moddate']								
							]							
						}
					]
				}
				,{
					xtype: 'fieldset'				
					,title: _translationMap['CanadianLearningBond_CLB']
					,layout: 'column'					
					,defaults: {
						layout: 'form'											
					}
					,items: [
						{
							columnWidth: 0.4
							,labelWidth: 100
							,items: [
								_fields['clb']['currStat']
								,_fields['clb']['newStat']																															
							]							
						}
						,{
							columnWidth: 0.3
							,labelWidth: 80
							,items: [							
								_fields['clb']['createdby']
								,_fields['clb']['moduser']
							]							
						}
						,{
							columnWidth: 0.3
							,labelWidth: 80
							,items: [								
								_fields['clb']['procdate']
								,_fields['clb']['moddate']								
							]							
						}
					]					
				}
				,{
					xtype: 'fieldset'				
					,title: _translationMap['GrantType_ACES']
					,id: 'acesFieldSet'					
					,hidden: true
					,items: [
						_grids['aces']
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['GrantType_SAGES']
					,layout: 'column'
					,defaults: {
						layout: 'form'
					}
					,id: 'sagesFieldSet'					
					,hidden: false
					,items: [
						{
							columnWidth: 0.30
							,labelWidth: 95
							,items: [
								  _fields['sages']['requestFlag']
							]
						}
						,{ 
							columnWidth: 0.45
							,labelWidth: 140
							,items: [	
								_fields ['sages']['applicationDate']
							]
						}
						,{ 
							columnWidth: 0.25
							,labelWidth: 75
							,items: [	
								_fields ['sages']['stopDate']
							  
							]
						}
						,{
							columnWidth: 0.4
							,labelWidth: 155
							,items: [
								_fields['sages']['fromDate']
							]							
						}
						,{
							columnWidth: 0.35
							,labelWidth: 100
							,items: [							
								_fields['sages']['toDate']
							]							
						}
						,{
							columnWidth: 0.25
							,labelWidth: 70
							,items: [
								_buttons['sages']['cancelRequestBtn']
							]							
						}
					]
				} // sagesFieldSet
				,{
					xtype: 'fieldset'				
					,title: _translationMap['GrantType_QESI']
					,id: 'qesiFieldSet'
					,hidden: true
					,items: [
						_grids['qesi']
					]
				}
			]			
		})
		
		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({		
				text: _translationMap['Historical']
				,handler: function(){_controller.openHistoricalPopup()}
			})
			,new DesktopWeb.Controls.ScreenButton({		
				text: _translationMap['OK'] 
				,handler: function(){
					if (_controller.validateScreen())
						_controller.confirmAndCommitScreen();
					}
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