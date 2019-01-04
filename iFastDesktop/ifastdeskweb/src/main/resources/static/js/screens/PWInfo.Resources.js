/*********************************************************************************************
 * @file	PWInfo.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Private Wealth Information screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Private Wealth Information
 *				
 *  History : 
 *
 *  25 Aug 2014 Narin S. P0233553 T55642
 *					- Created.
 *
 *  03 Sept 2014 Narin S. P0233553 T55678
 *					- Complete modify and assessment functionalities.
 *
 *  18 Sept 2014 Narin S. P0233553 DFT0041241 T55739
 *					- Always enable search value field.
 *					- Remove listeners of search criteria fields to make screen simple.
 *					- Fix modifying grace period stop date field.
 *					- Remove Group ID field from Private Wealth Information section.
 *
 *	25 Sept 2014 Narin S. P0233553 DFT0041354 DFT0041356 T55772
 *					- Remove Admin button at bottom of account details section
 *					- Add Account Private Wealth History button
 *
 *	29 Sept 2014 Narin S. P0233553 DFT0041894 T55792
 *					- Adjust Layout for new label.
 *
 *	02 Oct 2014 Narin S. P0233553 DFT0042004 T55823
 *					- Stop Date cannot be future date.
 *
 *	09 Oct 2014 Narin S. P0233553 DFT0042265 T55852
 *					- Add a new column, Eligible, to identify that 
 *						the linked account is not eligible to Private Wealth program.
 *
 *	16 Oct 2014 Narin S. P0233553 DFT0042698 T55888
 *					- Update tag name from LinkedAcct to LnkAcct
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 462;
	var _layoutWidth = 720;
	
	var _PWInfoFieldWidth = 80;
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Search']
			,listeners: {
				click: function(){_controller.clickHandle_searchBtn();}
			}
		})		
		,PWModBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Modify']
			,disabled: true
			,listeners: {
				click: function(){_controller.openActionPopup("PWInfoPopup", _controller.MOD);}
			}
		})		
		,PWAssessBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Assessment']
			,disabled: true
			,listeners: {
				click: function(){
					DesktopWeb.Util.displayYesNo(_translationMap['CONFIRM_PERFORM_ASSESSMENT'], callback);
					function callback(button){
						if (button == 'yes')
						{
							_controller.doAssessment();
						}
					}
				}
			}
		})		
		,PWHistoryBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Historical']
			,disabled: true
			,listeners: {
				click: function(){_controller.openHistoryPopup('PWInfo');}
			}
		})		
		,PWAdminBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Admin']
			,disabled: true
			,listeners: {
				click: function(){_controller.openAdminPopup('PWInfo');}
			}
		})		
	}
	
	// **** fields ****
	var _fields = {		
		searchFor: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['SearchFor']
			,width: 150
			,editable: true
			,allowBlank: false
			,listeners:{
				select: function(fld, record, index){
					_fields['searchValue'].reset();
				}
				,blur: function(fld){
					if (fld.getValue().length <=0){
						_fields['searchValue'].reset();
					}
				}
			}
		})
		,searchValue: new DesktopWeb.Controls.TextField({
			hideLabel: true
			,width: 150
			,allowBlank: false
		})
		,PWID: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['PWID']
			,width: _PWInfoFieldWidth
		})
		,PWLevelThreshold: new DesktopWeb.Controls.Label({
			hideLabel: true
			,width: _PWInfoFieldWidth + 40
			,style: 'text-decoration: underline; color:blue; padding-top:5px'
			,text: _translationMap['AssetLevelThreshold']
		})
		,PWLevel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['PWLevel']
			,width: _PWInfoFieldWidth
		})
		,PWStatus: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['PWStatus']
			,width: _PWInfoFieldWidth - 10
		})
		,deff: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['EffectiveDate']
			,width: _PWInfoFieldWidth
		})
		,stopDate: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['StopDate']
			,width: _PWInfoFieldWidth
		})
		,graceStartDate: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['GracePeriodActivationDate']
			,width: _PWInfoFieldWidth
		})
		,graceEndDate: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['GracePeriodEndDate']
			,width: _PWInfoFieldWidth
		})
		,lastAssessedDate: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['LastAssessmentDate']
			,width: _PWInfoFieldWidth
		})
		,lastAssessedTime: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['LastAssessmentTime']
			,width: _PWInfoFieldWidth
		})
		,adjustCost: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['CostAtLastLevelStatusChange']
			,width: _PWInfoFieldWidth
		})
		,marketValue: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['MarketValueAtLastLevelStatusChange']
			,width: _PWInfoFieldWidth
		})
		,threshold: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Threshold']
			,width: _PWInfoFieldWidth
		})
		,thresholdLev1: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ThresholdLevel1']
			,width: _PWInfoFieldWidth
		})
		,thresholdLev2: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ThresholdLevel2']
			,width: _PWInfoFieldWidth
		})
		,thresholdLev3: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ThresholdLevel3']
			,width: _PWInfoFieldWidth
		})
		,currency: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ThresholdLevel3']
			,width: _PWInfoFieldWidth + 100
			,style: 'padding:10px;'
			,text: _translationMap['Currency'] + ": "
		})
		,aggregatedValue: new DesktopWeb.Controls.Label({
			text: _translationMap['AggregatedValue'] + ":"
			,width: _PWInfoFieldWidth + 100
			,style: 'padding:10px;'
		})
		,aggMV: new DesktopWeb.Controls.Label({
			width: _PWInfoFieldWidth + 100
			,style: 'padding:10px;'
		})
		,aggBV: new DesktopWeb.Controls.Label({
			width: _PWInfoFieldWidth + 100
			,style: 'padding:10px;'
		})
	}
	
	// **** grids ****
	var _grids = {
		PWAcct: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth - 12				
			,autoScroll: true
			,height: 190
			,autoExpandColumn: 'account'
			,store: new Ext.data.XmlStore({
				record: 'LnkAcct'
				,fields: ['lnkAcctUUID', 'acct', 'name', 'broker', 'branch', 'slsrep'
							, 'grpID', 'deff', 'stopDate', 'name', 'mv', 'bv', 'userName'
							, 'processDate', 'modUser', 'modDate', 'version', 'elig']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
						
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL}
						);
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.selectPWAcct(record);
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
					{id: 'account', header: _translationMap['Account'], dataIndex: 'acct'}
					,{header: _translationMap['Broker'], dataIndex: 'broker', width: 70}
					,{header: _translationMap['Branch'], dataIndex: 'branch', width: 70}
					,{header: _translationMap['SalesRep'], dataIndex: 'slsrep', width: 70}
					,{header: _translationMap['GroupID'], dataIndex: 'grpID', width: 60}
					,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width: 80}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width: 80}
					,{header: _translationMap['MarketValue'], dataIndex: 'mv', width: 90}
					,{header: _translationMap['AdjustCost'], dataIndex: 'bv', width: 90}
					,{header: _translationMap['Eligible'], dataIndex: 'elig', width: 50}
				]
			})
			,bbar: [
				new Ext.Toolbar.TextItem({
					id: 'bb_shareholderName'
					,text: _translationMap['ShareholderName'] + ":"
				})
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'PWAcctHistBtn'
					,text: _translationMap['AccountPWHistory']
					,disabled: true
					,handler: function(){_controller.openPWAcctHistPopup('PWAcct');}
				})
			]
		})
		,PWAcctHist: new DesktopWeb.AdvancedControls.GridPanel({							
			width: 550 - 12				
			,autoScroll: true
			,height: 190
			,autoExpandColumn: 'account'
			,store: new Ext.data.XmlStore({
				record: 'PWAcctHist'
				,fields: ['acct', 'PWID', 'grpID', 'deff', 'stopDate']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [
					{id: 'account', header: _translationMap['Account'], dataIndex: 'acct'}
					,{header: _translationMap['PWID'], dataIndex: 'PWID', width: 100}
					,{header: _translationMap['GroupID'], dataIndex: 'grpID', width: 100}
					,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width: 100}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width: 100}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){_popups['PWAcctHistPopup'].hide();}
				})
			]
		})
	}
	
	// **** popups ****
	var _popups = {
		PWInfoPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 305
			,closeAction: 'hide'					
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 170
					,items: [ 
						new DesktopWeb.Controls.Label({
							itemId: 'PWID'
							,fieldLabel: _translationMap['PWID']
							,width: _PWInfoFieldWidth
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'PWLevel'
							,fieldLabel: _translationMap['PWLevel']
							,width: _PWInfoFieldWidth
						}) 
						,new DesktopWeb.Controls.Label({
							itemId: 'deff'
							,fieldLabel: _translationMap['EffectiveDate']
							,width: _PWInfoFieldWidth
						}) 
						,new DesktopWeb.Controls.DateField({
							itemId: 'stopDate'
							,fieldLabel: _translationMap['StopDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.Label({
							itemId: 'graceStartDate'
							,fieldLabel: _translationMap['GracePeriodActivationDate']
							,width: _PWInfoFieldWidth
						}) 
						,new DesktopWeb.Controls.Label({
							itemId: 'graceEndDate'
							,fieldLabel: _translationMap['GracePeriodEndDate']
							,width: _PWInfoFieldWidth
						}) 
						,new DesktopWeb.Controls.DateField({
							itemId: 'graceEndDateFld'
							,fieldLabel: _translationMap['GracePeriodEndDate']
							,allowBlank: true
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['PWInfoPopup'].isValid()){
							_controller.validatePWInfo(_popups['PWInfoPopup'].getData(), _popups['PWInfoPopup'].action);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['PWInfoPopup'].hide();}
				})
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['PWInfoPopup'];
				popup.action = action;
				switch(action)
				{
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['PrivateWealthInformation'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						break;
					}
				}
			}
			,populate: function(action)
			{
				var popup = _popups['PWInfoPopup'];
				popup.clearAllFields();
				popup.enableAllFields();
				switch(action)
				{
					case _controller.MOD:
					{
						var PWInfoObj = _controller.getPWInfoObject();
						popup.uuid = PWInfoObj['PWUUID'];
						popup.getField('PWID').setText(PWInfoObj['PWID']);
						popup.getField('PWLevel').setText(PWInfoObj['PWLevel'] + ' (' + PWInfoObj['PWStatus'] + ')');
						popup.getField('deff').setText(PWInfoObj['deff']);
						popup.getField('stopDate').setValue(PWInfoObj['stopDate']);
						if (PWInfoObj['graceStartDate'] && PWInfoObj['graceStartDate'].length > 0)
						{
							popup.getField('graceStartDate').setText(PWInfoObj['graceStartDate']);
							popup.getField('graceEndDateFld').setValue(PWInfoObj['graceEndDate']);
							popup.getField('graceEndDateFld').allowBlank = false;
							popup.getField('graceEndDateFld').show();
							popup.getField('graceEndDate').setText('');
							popup.getField('graceEndDate').hide();
						}else{
							popup.getField('graceStartDate').setText(_translationMap['NA']);
							popup.getField('graceEndDate').setText(_translationMap['NA']);
							popup.getField('graceEndDate').show();
							popup.getField('graceEndDateFld').allowBlank = true;
							popup.getField('graceEndDateFld').setValue('');
							popup.getField('graceEndDateFld').hide();
						}
						break;
					}
				}
			}
			,isValid: function()
			{
				var valid = true;
				var popup = _popups['PWInfoPopup'];
				
				valid = popup.getField('stopDate').isValid();
				
				var PWInfoObj = _controller.getPWInfoObject();
				if (PWInfoObj['graceStartDate'] && PWInfoObj['graceStartDate'].length > 0)
					valid = popup.getField('graceEndDateFld').isValid();
				
				var stopDate = popup.getField('stopDate').getValue();
				var graceEndDate = popup.getField('graceEndDateFld').getValue();
				var curBusDate = DesktopWeb.Util.stringToDate(_controller.getDefault('curBusDate'), DesktopWeb.Util.getDateDisplayFormat());
				var lastStopDate = DesktopWeb.Util.stringToDate(_controller.getDefault('stopDate'), DesktopWeb.Util.getDateDisplayFormat());
				if (stopDate < curBusDate){
					popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDATE']);
					valid = false;
				}else if (stopDate > curBusDate && stopDate < lastStopDate){
					popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_FUTUREDATE']);
					valid = false;
				}
				
				if (graceEndDate)
				{
					if (graceEndDate < curBusDate){
						popup.getField('graceEndDateFld').markInvalid(_translationMap['ERR_GRACEENDDATE_CANNOT_LESS_THAN_CURBUSDATE']);
						valid = false;
					}
				}
				return valid;
			}
			,getData: function()
			{
				var popup = _popups['PWInfoPopup'];
				var data = {};
				data['PWUUID'] = popup.uuid;
				data['stopDate'] = popup.getField('stopDate').getDisplayDateString();
				
				var PWInfoObj = _controller.getPWInfoObject();
				if (PWInfoObj['graceStartDate'] && PWInfoObj['graceStartDate'].length > 0)
					data['graceEndDate'] = popup.getField('graceEndDateFld').getDisplayDateString();
					
				return data;
			}
		})		
		,PWAcctHistPopup: new DesktopWeb.AdvancedControls.PopupWindow({								
			width: 550				
			,closeAction: 'hide'					
			,modal: true
			,defaults: {border:false}
			,title: _translationMap['AccountPWHistory']
			,items: [										
				_grids['PWAcctHist']													
			]
			,buttons: [
			]
			,init: function(title, data)
			{
				_grids['PWAcctHist'].getStore().removeAll();
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
				this.getField('procDate').setValue(data['procDate']);
				this.getField('modDate').setValue(data['modDate']);
				this.getField('userName').setValue(data['userName']);
				this.getField('modUser').setValue(data['modUser']);	
			}										
		})
		,history: new DesktopWeb.AdvancedControls.HistoryPopup()
	}
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,buttons: _buttons
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,style: 'padding-left:5px; padding-right:5px;'
				,items: [
					{
						// Search section
						layout: 'column'
						,defaults: {
							layout: 'form'
							,labelWidth: 75
						}
						,items: [
							{								
								columnWidth: 0.37
								,items: [
									_fields['searchFor']
								]
							}
							,{								
								columnWidth: 0.25
								,items: [
									_fields['searchValue']
								]
							}
							,{
								columnWidth: 0.30
								,items: [
									_buttons['searchBtn']
								]
							}
							,{
								columnWidth: 0.08
								,items: [
									_fields['PWLevelThreshold']
								]
							}
						]
					}
					,new Ext.Panel({
						layout: 'form'
						,id: 'PWInfoSection'
						,autoWidth: true
						,autoHeight: true
						,items:[
							{
								xtype: 'fieldset'
								,items: [
									{
										layout: 'column'
										,defaults: {
											layout: 'form'
										}
										,items: [
											{
												columnWidth: 1.00
												,labelWidth: 120
												,items: [
													_fields['PWID']
												]
											}
											,{								
												columnWidth: 0.50
												,labelWidth: 120
												,items: [
													_fields['PWLevel']
													,_fields['deff']
													,_fields['stopDate']
												]
											}
											,{								
												columnWidth: 0.40
												,labelWidth: 170
												,items: [
													_fields['PWStatus']
													,_fields['graceStartDate']
													,_fields['graceEndDate']
												]
											}
											,{								
												columnWidth: 0.50
												,labelWidth: 225
												,items: [
													_fields['marketValue']
													,_fields['adjustCost']
												]
											}
											,{								
												columnWidth: 0.40
												,labelWidth: 170
												,items: [
													_fields['lastAssessedDate']
													,_fields['lastAssessedTime']
												]
											}
										]
									}
								]
							}
						]
						,buttons: [
							_buttons['PWModBtn']
							,_buttons['PWAssessBtn']
							,_buttons['PWHistoryBtn']
							,_buttons['PWAdminBtn']
						]
					})
					,{
						// Top bar of linked account section
						layout: 'column'
						,defaults: {
							layout: 'form'
						}
						,items: [
							{								
								columnWidth: 0.48
								,items: [
									_fields['currency']
								]
							}
							,{								
								columnWidth: 0.16
								,items: [
									_fields['aggregatedValue']
								]
							}
							,{								
								columnWidth: 0.13
								,items: [
									_fields['aggMV']
								]
							}
							,{								
								columnWidth: 0.23
								,items: [
									_fields['aggBV']
								]
							}
						]
					}
					,_grids['PWAcct']
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					if (_controller.updatesFlag){
						DesktopWeb.Util.commitScreen();
					}else{
						DesktopWeb.Util.cancelScreen();
					}
				}
			})
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){
						DesktopWeb.Util.cancelScreen();
					}
				}
			)
		]			
	}
}