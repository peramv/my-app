/*********************************************************************************************
 * @file	RESPZeroRpymt.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for RESP Zero Grant Repayment screen	
 *********************************************************************************************/
/*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 375;
	var _layoutWidth = 600;
	
	// **** fields ****
	var _fields = {
		planNumber: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['PlanNumber']
			,width: 100
		})
		,matureDate: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['MatureDate']
			,width: 100
		})
		,grandfathered: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Grandfathered']
			,width: 100
		})
		,reportedToHRDC: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ReportedToHRDC']
			,width: 100
		})
		,preContribution: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Pre98Contributions']
			,width: 100
		})
		,respStatus: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['RESPStatus']
			,width: 100
		})
		,inceptionDate: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['InceptionDate']
			,width: 100
		})
		,siblingOnly: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['SiblingOnly']
			,width: 100
		})
		,reportingRequired: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ReportingRequired']
			,width: 100
		})
	}
	
	// **** grids ****
	var _grids = {
		grantPayment: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 13				
			,autoScroll: true							
			,height: 175				
			,store: new Ext.data.XmlStore({
				record: 'GrantRpymtDetail'
				,fields: ['runMode' 
						  ,'transType' 
						  ,'transDate'
						  ,'hrdcIDDisp'
						  ,'dateSent'
						  ,'reported' 						  
						  ,'normalRvrse'
						  ,'hrdcTransId'
						  ,'status' 
						  ,'amt']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.transDate = DesktopWeb.Util.getDateDisplayValue(record.data.transDate);			
							record.data.dateSent = DesktopWeb.Util.getDateDisplayValue(record.data.dateSent);							
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
					rowselect: function(selModel, index, record){_controller.updateActionButtons();}
					,rowdeselect: function(){_controller.updateActionButtons();}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['TransType'], id:'transType', dataIndex: 'transType', width:150}
					,{header: _translationMap['TransDate'], id:'transDate',  dataIndex: 'transDate', width: 80}
					,{header: _translationMap['HRDCTransId'], id:'hrdcTransId', dataIndex: 'hrdcIDDisp', width:100}
					,{header: _translationMap['DateSent'], id:'dateSent', dataIndex: 'dateSent', width:80}
					,{header: _translationMap['Amount'], id:'amount', dataIndex: 'amt', width:100}
					,{header: _translationMap['Reported'], id:'reported', dataIndex: 'reported', width:80}
					,{header: _translationMap['Status'], id:'status', dataIndex: 'runMode', width:80}
				]							
			})				
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup(_controller.DEL);}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'								
					,text: _translationMap['Cancel']					
					,handler: function(){_controller.openActionPopup(_controller.CANCEL);}
				})
			]			
		})
	}
	
	// **** popups ****
	var _popups = {
		repaymentPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 300
			,action: null						
			,modal: true				
			,defaults: {border:false, style:'padding-top:4px; padding-left:4px;'}
			,listeners: {
				beforeshow: function(){_popups['repaymentPopup'].init()}
				,show: function(){_popups['repaymentPopup'].populateFields()}
			}
			,items: [
				{
					html: _translationMap['DeleteConfirm']								
					,style: 'text-align:center'														
				}
				,{
					html: _translationMap['CancelConfirm']							
					,style: 'text-align:center'														
				}						
				,{
					layout: 'form'					
					,labelWidth: 90					
					,items: [
						new DesktopWeb.Controls.Label({
							itemId: 'transType'
							,width: 175
							,fieldLabel: _translationMap['TransType']																		
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'transDate'									
							,width: 100
							,fieldLabel: _translationMap['TransDate']	
							,allowBlank: false	
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())							
						})								
					]
				}						
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						if (_popups['repaymentPopup'].isValid())
						{
							_controller.savePopup(_popups['repaymentPopup'].action, _popups['repaymentPopup'].getData());							
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){
						_popups['repaymentPopup'].hide();
					}
				})
			]
			,init: function()
			{																		
				this.get(0).hide(); //hide delete message				
				this.get(1).hide(); //hide cancel message				
				
				switch(this.action)
				{					
					case _controller.MOD:
					{												
						this.setTitle(_translationMap['GrantRepayment'] + " - " +  _translationMap["Modify"]);													
						break;
					}
					case _controller.DEL:
					{						
						this.setTitle(_translationMap['GrantRepayment'] +  " - " + _translationMap["Delete"]);
						this.get(0).show(); //show delete message											
						break;
					}
					case _controller.CANCEL:
					{						
						this.setTitle(_translationMap['GrantRepayment'] +  " - " + _translationMap["Cancel"]);
						this.get(1).show(); //show cancel message													
						break;
					}									
				}												
			}																
			,populateFields: function()
			{
				this.clearPopupFields();
				this.populateWithSelectedRecord();				
				this.disablePopupFields();
				
				if (this.action == _controller.MOD)
				{
					this.getField('transDate').enable();
				}							
			}
			,populateWithSelectedRecord: function()
			{
				var rec = _grids['grantPayment'].getSelectedRecord();				
				this.getField('transType').setValue(rec.data['transType']);
				this.getField('transDate').setValue(rec.data['transDate']);				
			}
			,getData: function()
			{
				var data = {};
				data['runMode'] = this.action;				
				data['transDate'] = this.getField('transDate').getDisplayDateString();
				return data;
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
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				{
					xtype: 'fieldset'
					,layout: 'column'
					,title: 'RESP Account Information'
					,defaults: {
						layout: 'form'
						,columnWidth: 0.5
						,labelWidth: 125
					}
					,items: [
						{
							items:[
								_fields ['planNumber']
								,_fields ['matureDate']
								,_fields ['grandfathered']
								,_fields ['reportedToHRDC']
								,_fields ['preContribution']
							]
						}
						,{
							items: [
								_fields ['respStatus']
								,_fields ['inceptionDate']
								,_fields ['siblingOnly']
								,_fields ['reportingRequired']
							]
						}
						
					]
				}
				,{
					xtype: 'fieldset'
					,title: _translationMap['ZeroGrantRepaymentEntries']
					,items: [
						_grids ['grantPayment']
					]
				}
			]
		})
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: 'OK'
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