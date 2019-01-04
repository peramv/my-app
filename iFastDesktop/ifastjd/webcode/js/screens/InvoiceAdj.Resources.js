 /**********************************************************************************************
 *
 * Procedure: InvoiceAdj.Resources.js
 *
 * Purpose  : Invoice Adjustment screen for adjusting the Payments of Invoice			  
 *
 * Notes	: Open screen by -> Invoice Instructions screen (Invoice Button) 
 *
 * History  : 
 *	
 *		5 Mar 2013 Pannarasi Wongpakdee PETP0206635 FN01 MFR MFI Enhancments
 *			- Created
 *
 *		27 May 2013 Pannarasi Wongpakdee PETP0206635 FN01 T53618 IN3336672
 *			- Added more three fields into grid
 *
 *		13 Jun 2013 Pannarasi Wongpakdee PETP0206635 FN01 T53714 IN3346061
 *			- Displayed OffeSetAmount as blank for new payment (status 05-Approved Verified)
 *		
 *    19 Aug 2013  G. Thawornwachirakun PETP0206635 FN01 T54037 DFT0013578
 *          - Modify split comment from the number of character to split by enter
 *  
 *    11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *    19 Dec 2013 G. Thawornwachirakun P0181067 CHG0034430 DFT0026446 T54629
 *          - Fix incorrect display on payment date column 
 **********************************************************************************************/
 
  DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 370;
	var _layoutWidth = 715;
	
	// **** fields ****
	var _fields = 
	{	
		offsetAmount: new DesktopWeb.Controls.NumberField
		(
			{
				fieldLabel: _translationMap['OffsetAmount']
				,width: 150	
				,editable: false			
			}
		)
		,adjmentDate: new DesktopWeb.Controls.DateField
		(
			{
				fieldLabel: _translationMap['AdjmentDate']
				,width: 150	
				,editable: false
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		,comment: new Ext.form.TextArea
		(
			{
				fieldLabel: _translationMap['Comment']
				,autoScroll: true
				,width: 335
				,height: 105
				,maxLength: 320
				,editable: false
				,allowBlank: true
			}
		)
	}
	
	// **** buttons ****
	var _buttons = 	{		
	}
	
	// **** grids ****
	var _grids = 
	{
		grdInvAdj: new DesktopWeb.AdvancedControls.GridPanel
		(
			{							
				width: _layoutWidth
				,title: ''
				,autoScroll: true
				,height: 200
				,autoExpandColumn: 'payFor'				
				,store: new Ext.data.XmlStore
				(
					{
						record: 'PaymentDetail'
						, fields: [ 'billInstrID', 'invoiceID', 'pymtId', 'payFor', 'payPeriodStart', 'payPeriodEnd',
									'payDate', 'amount', 'currency', 'status', 'version', 'allowAdjust', 'offsetAmount', 
									'adjustDate', 'comment1','comment2', 'comment3','comment4',
									'username', 'processDate', 'modUser', 'modDate', 'gridIndex', 
									'runMode', 'errMsg', 'isChgOffsetAmt', 'isChgAdjustDate', 'isChgComment']	
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									record.data.payDate = DesktopWeb.Util.getDateDisplayValue(record.data.payDate);
									record.data.adjustDate = DesktopWeb.Util.getDateDisplayValue(record.data.adjustDate);
									record.data.processDate = DesktopWeb.Util.getDateDisplayValue(record.data.processDate);
									record.data.payPeriodStart = DesktopWeb.Util.getDateDisplayValue(record.data.payPeriodStart);
									record.data.payPeriodEnd = DesktopWeb.Util.getDateDisplayValue(record.data.payPeriodEnd);
									record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
								});

								store.fireEvent('datachanged', store); //to set data in grid again
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel
				(
					{
						singleSelect: true
						,listeners: 
						{
							rowselect: function(selModel, index, record)
							{
								if(selModel)
								{
									_controller.setSelectedInvoiceAdj(record, index);
								}
							}
							,rowdeselect: function()
							{
								_controller.setDeselectedInvoiceAdj();
							}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel
				(
					{
						defaults: 
						{
							menuDisabled: true
							,width: 110
							,sortable: false
						}
						,columns: 
						[
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }, width: 25 }
							, {header: _translationMap['PaymentFor'], id: 'payFor',dataIndex: 'payFor'}
							, {header: _translationMap['PaymentPeriod'], dataIndex: 'payPeriodStart', width:140, 
								renderer: function(val, metaData, record){
									return (record.data['payPeriodStart'] + ' - ' + record.data['payPeriodEnd'])}}
							, {header: _translationMap['PaymentDate'], dataIndex: 'payDate', width:80}
							, {header: _translationMap['Amount'], dataIndex: 'amount', width:80}
							, {header: _translationMap['Currency'], dataIndex: 'currency', width:80}
							, {header: _translationMap['Status'], dataIndex: 'status', renderer: function(val) {return (_controller.getListDisplay('status', val));}, width:100}
							, {header: _translationMap['InvoiceId'], dataIndex: 'invoiceID', width:80}
						]							
					}	
				)
				,buttons: 
				[			
					new DesktopWeb.Controls.ActionButton
					(
						{
							itemId: 'btnPrintIV'	
							,text: _translationMap['PrintIV']							
							,handler: function(){_controller.doPrint(true)}
						}
					)
					,new DesktopWeb.Controls.ActionButton
					(
						{
							itemId: 'btnAdjDetail'
							,text: _translationMap['AdjDetail']
							,handler: function(){_controller.openActionPopup("frmInvAdj", _controller.MOD);}
						}
					)							
					,new DesktopWeb.Controls.ActionButton
					(		
						{
							itemId: 'cmdInvAdjMore'
							,text: _translationMap['More']
							,handler: function(){_controller.doReload(true)}
						}
					)
					,new DesktopWeb.Controls.ActionButton
					(
						{
							itemId: 'cmdInvAdjAdmin'
							,text: _translationMap['Admin']
							,handler: function(){_controller.openAdminPopup('PaymentDetail');}
						}
					)
				]
			}
		)
	}			
	
	// **** popups ****
	var _popups = 
	{
		frmInvAdj: new DesktopWeb.AdvancedControls.PopupWindow
		(
			{
				action: null
				,width: 500
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border:false}
				,items: 				
				[
					{
						layout: 'form'																		
						,style: 'padding:4px'
						,defaults: {border: true}
						,labelWidth: 120
						,items: 
						[ 
							new DesktopWeb.Controls.NumberField
							(
								{
									itemId: 'offsetAmountDetl'
									,fieldLabel: _translationMap['OffsetAmount']
									,width: 150	
									,editable: true
									,allowBlank: true
									,allowNegative: true
									,maxValue: 999999999.99
									,minValue: -999999999.99
									,decimalPrecision: 2
									}
							) 
							,new DesktopWeb.Controls.DateField
							(
								{
									itemId: 'adjmentDateDetl'
									,fieldLabel: _translationMap['AdjmentDate']
									,width: 150	
									,editable: true	
									,allowBlank: true
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								}
							)
							,new Ext.form.TextArea
							(
								{
									itemId: 'commentDetl'
									,fieldLabel: _translationMap['Comment']
									,autoScroll: true
									,width: 335
									,height: 105
									,maxLength: 320
									,editable: true
									,allowBlank: true									
									,style: "word-wrap: normal; overflow-x: scroll;"
								}
							)
						]						
					}													
				]
				,buttons: 
				[	
					new DesktopWeb.Controls.ActionButton
					(	
						{
							itemId: 'cmdInvAdjSubmit'
							,text: _translationMap['Ok']
							,handler: function()
							{
								if (_popups['frmInvAdj'].isValid())
								{
									_controller.invoiceAdjUpdate(_popups['frmInvAdj'].action, _popups['frmInvAdj']);
								}
							}
						}
					) 
					,new DesktopWeb.Controls.ActionButton
					(
						{
							itemId: 'cmdInvAdjCancel'
							,text: _translationMap['Cancel']
							,handler: function(){_popups['frmInvAdj'].hide();}
						}
					)
				]
				,init: function(action)
				{
					// initialize popup based on action
					var popup = _popups['frmInvAdj'];
					popup.action = action
					
					switch(action)
					{
						case _controller.MOD:
						{
							popup.setTitle(_translationMap['InvoiceAdj']);
							popup.populate(action);
							break;
						}
					}
				}
				,populate: function(action)
				{
					var popup = _popups['frmInvAdj'];	
					popup.clearAllFields();
					popup.enableAllFields();
					
					var selectedInvoice = _controller.getSelectedInvoiceAdj();
			
					// Display OffeSetAmount as blank for new payment with status 05-Approved Verified
					if ( (selectedInvoice.get('status') == '05') && (selectedInvoice.get('offsetAmount') == 0) &&
						 (selectedInvoice.get('isChgOffsetAmt') != 'yes') )
					{
						popup.getField('offsetAmountDetl').setValue('');
					}
					else
					{
						popup.getField('offsetAmountDetl').setValue(selectedInvoice.get('offsetAmount'));
					}

					popup.getField('adjmentDateDetl').setValue(selectedInvoice.get('adjustDate'));
					
					var allComment = selectedInvoice.get('comment1') + _controller.NEWLINE						 
						+ selectedInvoice.get('comment2') + _controller.NEWLINE
						+ selectedInvoice.get('comment3') + _controller.NEWLINE
						+ selectedInvoice.get('comment4');
						
					popup.getField('commentDetl').setValue(allComment.trim());
				}
			}
		)		
		,admin: new DesktopWeb.AdvancedControls.PopupWindow
		(
			{								
				width: 395				
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border:false}
				,items: 
				[
					{						
						layout: 'column'																		
						,style: 'padding:4px'
						,defaults: {border: false, labelWidth:80}						
						,items: 
						[
							{
								width: 185
								,layout: 'form'
								,defaults: {width:80}																					
								,items: 
								[
									new DesktopWeb.Controls.Label
									(
										{											
											itemId: 'modUser'		
											,fieldLabel: _translationMap['ModUser']														
										}
									)		
									,new DesktopWeb.Controls.Label
									(
										{											
											itemId: 'procDate'
											,fieldLabel: _translationMap['ProcessDate']																
										}
									)									
								]
							}							
							,{
								width: 185
								,layout: 'form'
								,defaults: {width: 80}																							
								,items: 
								[	
									new DesktopWeb.Controls.Label
									(
										{											
											itemId: 'modDate'
											,fieldLabel: _translationMap['ModDate']
											,value: 'test'					
										}
									)	
								]
							}
						]						
					}													
				]
				,buttons: 
				[
					new DesktopWeb.Controls.ActionButton
					(
						{
						text: _translationMap['Ok']
						,handler: function(){_popups['admin'].hide();}
						}
					)
				]
				,init: function(title, data)
				{
					this.setTitle(title);
					this.getField('procDate').setValue(data['procDate']);
					this.getField('modDate').setValue(data['modDate']);
					this.getField('modUser').setValue(data['modUser']);	
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
		
		,layout: new Ext.Container
		(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: 
				[
					_grids['grdInvAdj']
					, {
						layout: 'form'
						,labelWidth: 120
						, items: 
						[
							_fields['offsetAmount']
							, _fields['adjmentDate']
							, _fields['comment']
						]
					}
				]																			
			}
		)
		,screenButtons: 
		[	
			new DesktopWeb.Controls.ScreenButton
			(
				{
					text: _translationMap['Ok']
					,handler: function(){_controller.doUpdate(true)}					
				}
			)
			,new DesktopWeb.Controls.ScreenButton
			(
				{
					text: _translationMap['Cancel']
					,handler: function()
					{
						if(_controller.updatesFlag)
						{
							DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
													
							function handlePromptMsg(btn)
							{
								if(btn)
								{
									_controller.goScreen();
								}
							}
						}
						else
						{
							_controller.goScreen();
						}
					}
				}
			)
		]			
	}
}	
