/*********************************************************************************************
 * @file	RESPAcctTermInfo.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for RESP Account Termination Entries screen.
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  30 Apr 2014 G. Thawornwachirakun P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *  30 May 2014 Narin Suanlamyai P0220132 FN03 DFT0034351 T55198
 *					- Disable SAGES fields for non-SAGES environment
 *
 *  21 Jul 2014 Narin Suanlamyai P0220132 FN03 DFT0037101 T55450
 *					- Hide SAGES section for non-SAGES environment.
 *
 *  12 Nov 2015 Aurkarn Mongkonrat P0241773 FN01 T81710 DFT0056104 
 *					- Fix to show BCTESG on RESP Termination Adjustment screen.
 *
 *	29 Jan 2018 Simona Pop P0275389 
 *  				- RESP Phase 3 enhancements - RESP Termination.
 *
 *  20 Mar 2018 Simona Pop P0275389
 *                  - Description change for Reversal record
 *                  - Display qesi amount for Special Tax Repayment records
 *
 *
 *  21 Mar 2018 Simona Pop P0275389 
 *  				- New TerminationDetail field - financial.
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 400;
	var _layoutWidth = 725;	
	
	// **** fields ****
	var _fields = {		
		planNo: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['planNo']
				,style: {textAlign: 'right'}
			}
		)
		,matureDt: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['matureDt']
				,style: {textAlign: 'right'}
			}
		)
		,grandFather: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['grandFather']
				,style: {textAlign: 'right'}
			}
		)
		,repHRDC: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['repHRDC']
				,style: {textAlign: 'right'}
			}
		)
		,pre98Contr: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['pre98Contr']
				,style: {textAlign: 'right'}
			}
		)
		,respStat: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['respStat']
				,style: {textAlign: 'right'}
			}
		)
		,incepDt: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['incepDt']
				,style: {textAlign: 'right'}
			}
		)
		,siblingOnly: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['siblingOnly']
				,style: {textAlign: 'right'}
			}
		)
		,repReqd: new Ext.form.DisplayField(
			{
				fieldLabel: _translationMap['repReqd']
				,style: {textAlign: 'right'}
			}
		)
		,termDate: new Ext.form.DisplayField(
			{
			    fieldLabel: _translationMap['termDate']
				, style: { textAlign: 'right' }
			}
		)
	}
	
	// **** grids ****
	var _grids = {
		termDetlGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 12
				,title: ''
				,autoScroll: true
				,height: 173
				,autoExpandColumn: 'transType'
				,store: new Ext.data.XmlStore(
					{
						record: 'TerminationDetail'
						,fields: ['transType', 'transDate', 'hrdcIDDisp', 'hrdcTransId', 'dateSent', 'amt', 'reported', 'normalRvrse', 'cesg', 'clb', 'pGrant', 'runMode'
							, 'sages', 'bctesg', 'eventDetlUUID', 'financial']
						,listeners: {
							load: function(store, records)
							{
								_grids['termDetlGrid'].getSelectionModel().selectFirstRow();
								Ext.each(records, function(record){
									record.data.transDate = DesktopWeb.Util.getDateDisplayValue(record.data.transDate);
									record.data.dateSent = DesktopWeb.Util.getDateDisplayValue(record.data.dateSent);
								});

								store.fireEvent('datachanged', store); //to set data in grid again
								
							}
							,update: function(store)
							{
								store.filterBy(function(record){return record.get('runMode') != _controller.DELETE});
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){
								if(selModel){
									_controller.setSelectedEntry(record);
								}
							}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
							,sortable: false
						}
						,columns: [
							{id: 'transType', header: _translationMap['transType'], dataIndex: 'transType'}
							,{header: _translationMap['transDate'], dataIndex: 'transDate', width: 85}
							,{header: _translationMap['hrdcTransId'], dataIndex: 'hrdcIDDisp', width: 100}
							,{header: _translationMap['dateSent'], dataIndex: 'dateSent', width: 85}
							,{header: _translationMap['Amount'], dataIndex: 'amt', width: 85}
							,{header: _translationMap['reported'], dataIndex: 'reported', width: 85}
							,{header: _translationMap['Status'], dataIndex: 'runMode'
								,renderer: function(val){
									switch (val){
										case _controller.DELETE:   return _translationMap['deleted'];
										case _controller.MODIFY:   return _translationMap['modified'];
										case _controller.CANCEL:   return _translationMap['cancelled'];
										case _controller.REVERSED: return _translationMap['reversed'];
										default: return '';
									}
								}
								, width: 85
							}
						]							
					}
				)
				,buttons: [					
					new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'ExpandBtn'	
							,text: _translationMap['expand']
							,handler: function(){_controller.openActionPopup("detailsPopup");}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'ModifyBtn'
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup("actionPopup", _controller.MODIFY);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'DeleteBtn'
							,text: _translationMap['Delete']
							,handler: function(){_controller.openActionPopup("actionPopup", _controller.DELETE);}							
						}
					)									
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'CancelBtn'
							,text: _translationMap['Cancel']
							,handler: function(){_controller.openActionPopup("actionPopup", _controller.CANCEL);}
						}
					)
				]
			}
		)
	}
	
	// **** popups ****
	var _popups = {					
		detailsPopup: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				title: _translationMap['respAcctDetl']
				,width: 275
				,closeAction: 'hide'
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						layout: 'form'
						,id: 'detlSec'
						,style: {padding: '4px', width: '90%', marginLeft: '30px'} 
						,defaults: {border: true}
						,defaultType: 'displayfield'
						,labelWidth: 130
						,items :[
							{
								itemId: 'cesg'
								,fieldLabel: _translationMap['cesg']
								,style: {textAlign: 'right'}
							}
							,{
								itemId: 'clb'
								,fieldLabel: _translationMap['clb']
								,style: {textAlign: 'right'}
							}
							,{
								itemId: 'pGrant'
								,fieldLabel: _translationMap['pGrant']
								,style: {textAlign: 'right'}
							}
							,{
								xtype: 'fieldset'
								,layout: 'form'
								,id: 'sagesSec'
								,hidden: true
								,border: false
								,autoHeight: true
								,style: 'margin:0px; padding:0px;'
								,items :[
									new Ext.form.DisplayField({
										itemId: 'sages'
										,fieldLabel: _translationMap['sages']
										,style: {textAlign: 'right'}
									})
								]
							} 
                            ,{
								xtype: 'fieldset'
								,layout: 'form'
								,id: 'bctesgSec'
								,hidden: true
								,border: false
								,autoHeight: true
								,style: 'margin:0px; padding:0px;'
								,items :[
									new Ext.form.DisplayField({
										itemId: 'bctesg'
										,fieldLabel: _translationMap['bctesg']
										,style: {textAlign: 'right'}
									})
								]
                            }
                            ,{
                                itemId: 'amt'
								, fieldLabel: _translationMap['qesi']
								, style: { textAlign: 'right' }
                            }                                           
						]
					}
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){_popups['detailsPopup'].hide();}
						}
					)
				]
				,init: function(action)
				{
					var popup = _popups['detailsPopup'];
					popup.populate();
				}
				,populate: function()
				{
					var popup = _popups['detailsPopup'];
					popup.clearAllFields();
					popup.enableAllFields();
					
					var selectedItem = _controller.getSelectedEntry();
					popup.getField('cesg').setValue(selectedItem.get('cesg'));
					popup.getField('clb').setValue(selectedItem.get('clb'));
					popup.getField('pGrant').setValue(selectedItem.get('pGrant'));
					popup.getField('sages').setValue(selectedItem.get('sages'));
					popup.getField('bctesg').setValue(selectedItem.get('bctesg'));
					popup.getField('amt').setValue(selectedItem.get('amt'));
				
					if ((selectedItem.get('transType')).substring(0, 2) == _controller.SPECIAL_TAX_REPAYMENT)
					{
					    popup.getField('cesg').hide();
					    popup.getField('clb').hide();
					    popup.getField('pGrant').hide();
					    popup.getField('sages').hide();
					    popup.getField('bctesg').hide();
					    popup.getField('amt').show();
					}
					else
					{
					    popup.getField('cesg').show();
					    popup.getField('clb').show();
					    popup.getField('pGrant').show();
					    popup.getField('sages').show();
					    popup.getField('bctesg').show();
					    popup.getField('amt').hide();
					}
				}
			}
		)		
		,actionPopup: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				width: 300
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						itemId: 'deleteMsg'
						,html: _translationMap['DeleteConfirmMsg']
						,style: 'text-align:center;font-weight:bold;'										
					}
					,{
						itemId: 'cancelMsg'
						,html: _translationMap['CancelConfirmMsg']
						,style: 'text-align:center;font-weight:bold;'
					}
					,{
						layout: 'form'
						,style: 'padding:4px'
						,defaults: {border: true}
						,labelWidth: 110
						,items: [ 
							new Ext.form.DisplayField(
										{
											itemId: 'transTypeFld'
											,fieldLabel: _translationMap['transType']
										}
							)
							,new DesktopWeb.Controls.DateField(
										{
											itemId: 'transDateFld'
											,fieldLabel: _translationMap['transDate']
											,allowBlank: false
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										}
							)
							,new DesktopWeb.Controls.NumberField(
									{
										itemId: 'amtFld'
										,width: 95										
										,allowNegative: true
										,allowDecimal: true
										,decimalPrecision: 2
										,decimalSeparator: '.'
										,fieldLabel: _translationMap['qesiAmt']
									}
							)													
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								if (_popups['actionPopup'].isValid()){
									_controller.entryUpdate(_popups['actionPopup']);
								}
							}
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							itemId: 'canBtn'
							,text: _translationMap['Cancel']
							,handler: function(){_popups['actionPopup'].hide();}
						}
					)
				]
				,init: function(action)
				{
					// initialize popup based on action
					var popup = _popups['actionPopup'];
					popup.action = action
					switch(action)
					{
						case _controller.CANCEL:
						{
							popup.setTitle(_translationMap['popupCancelEntry']);
							popup.populate(action);
							popup.get('cancelMsg').show();
							popup.get('deleteMsg').hide();							
							break;
						}
						case _controller.MODIFY:
						{
							popup.setTitle(_translationMap['popupModifyEntry']);
							popup.populate(action);
							popup.get('cancelMsg').hide();
							popup.get('deleteMsg').hide();							
							break;
						}
						case _controller.DELETE:
						{
							popup.setTitle(_translationMap['popupDeleteEntry']);
							popup.populate(action);
							popup.disableAllFields();
							popup.get('cancelMsg').hide();
							popup.get('deleteMsg').show();							
							break;
						}
					}
				}
				,populate: function(action)
				{
					var popup = _popups['actionPopup'];
					popup.enableAllFields();
					
					var selectedItem = _controller.getSelectedEntry();
					popup.getField('transTypeFld').setValue(selectedItem.get('transType'));
					popup.getField('transDateFld').setValue(selectedItem.get('transDate'));
					popup.getField('amtFld').setValue(selectedItem.get('amt'));
					popup.getField('amtFld').show();
					
					if ( action == _controller.CANCEL || action == _controller.DELETE )
					{
						popup.getField('transDateFld').disableField();
						popup.getField('amtFld').hide();
					}
					else if (action == _controller.MODIFY && (selectedItem.get('transType')).substring(0, 2) != _controller.SPECIAL_TAX_REPAYMENT)
					{
						popup.getField('amtFld').hide();
					}
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
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					{
						xtype:'fieldset'
						,title: _translationMap['titleAcctInfo']
						,layout: 'column'
						,style: 'margin-bottom:20px'
						,width: _layoutWidth
						,items: [{
								// Column#1
								layout: 'form'
								,columnWidth: 0.42
								,autoHeight:true
								,labelWidth: 150
								,defaultType: 'displayfield'
								,items :[
									_fields['planNo']
									,_fields['matureDt']
									,_fields['grandFather']
									,_fields['repHRDC']
									,_fields['pre98Contr']
								]
							}
							,{
								// Column#2 - Empty column
								layout: 'form'
								,columnWidth: 0.06
								,autoHeight:true
								,labelWidth: 150
								,defaultType: 'displayfield'
								,items :[
								]
							} 
							,{
								// Column#3
								layout: 'form'
								,columnWidth: 0.42
								,autoHeight:true
								,labelWidth: 200
								,defaultType: 'displayfield'
								,items :[
									_fields['respStat']
									,_fields['incepDt']
									,_fields['siblingOnly']
									,_fields['repReqd']
									,_fields['termDate']
								]
							}
						]
					}
					,{
						xtype: 'fieldset'
						,title: _translationMap['titleTermEntry']
						,style: "margin-bottom:20px"
						,width: _layoutWidth
						,items: _grids['termDetlGrid']
					}
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['OK']
					,handler: function(){DesktopWeb.Util.commitScreen()}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){
						if(_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
						}else{
							cancelScreen(true);
						}
						function cancelScreen(discard){
							if(discard){
								DesktopWeb.Util.cancelScreen();
							}
						}
					}
				}
			)
		]			
	}
}