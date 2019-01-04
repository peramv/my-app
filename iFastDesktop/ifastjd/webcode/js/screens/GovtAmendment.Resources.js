/*********************************************************************************************
 * @file	GovtAmendment.Resources.js
 * @author	Rod Walker
 * @desc	Resources JS file for Government Filing and Amendment screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	// content dimensions
	var _layoutHeight = 325;
	var _layoutWidth = 760;
	
	// **** fields ****
	var _fields = {
	}
	
	// **** grids ****
	var _grids = {
		mstrs: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth
				,style: "margin-bottom:15px"
				,autoScroll: true							
				,height: 150
				,autoExpandColumn: 'reqStatus'							
				,store: new Ext.data.XmlStore(
					{
						record: 'Mstr'					
						,fields: ['mstrErrorMsg', 'mstrRunMode', 'beneName', 'acctName', 'filingTypeDesc', 'deff', 'reqTypeDesc', 'reqStatDesc']
						,listeners: {
							load: function(store, records)
							{
								// add xml node index reference to each record, for use with setting selected record,	
								// can't just rely on record index because items for deletion are filtered								
								for (var r = 0; r < records.length; r++)
								{
									records[r].xmlIndex = r + 1;
									records[r].data.deff = DesktopWeb.Util.getDateDisplayValue(records[r].data.deff);
								}								
								store.filterBy(function(record){
									return record.data.mstrRunMode != _controller.DEL});
							}												
						}						
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){_controller.setSelectedMstr(record.xmlIndex);}
							,rowdeselect: function(){_controller.clearSelectedMstr();}
						}						
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{width: 25
							, mapping: 'mstrErrorMsg'
							, renderer: function(val){
									return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
								}
							}
							,{header: _translationMap['BeneficiaryName'], dataIndex: 'beneName', width:275}
							,{header: _translationMap['AccountOwnerName'], dataIndex: 'acctName', width:275}
							,{header: _translationMap['FilingType'], dataIndex: 'filingTypeDesc', width:75}
							,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width:100}
							,{header: _translationMap['RequestType'], dataIndex: 'reqTypeDesc', width:100}
							,{id: 'reqStatus', header: _translationMap['RequestStatus'], dataIndex: 'reqStatDesc'}
						]							
					}
				)
				,buttons: [					
					new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'addBtn'								
							,text: _translationMap['Add']
							,handler: function(){_controller.openActionPopup( 'mstr', _controller.ADD);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'modBtn'
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup('mstr', _controller.MOD);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'delBtn'
							,text: _translationMap['Delete']
							,handler: function(){_controller.openActionPopup('mstr', _controller.DEL);}							
						}
					)				
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'adminBtn'
							,text: _translationMap['Admin']
							,handler: function(){_controller.openAdminPopup('mstr');}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'historicalBtn'
							,text: _translationMap['Historical']
							,handler: function(){_controller.openHistoricalPopup('mstr');}
						}
					)
				]			
			}
		)
		,detls: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: 345
				,style: "margin-bottom:15px"				
				,autoScroll: true							
				,height: 150			
				,autoExpandColumn: 'reason'				
				,store: new Ext.data.XmlStore(
					{
						record: 'Detl'				
						,fields: ['detlErrorMsg', 'dtlRunMode', 'reasonDesc', 'fromDeff']
						,listeners: {
							load: function(store, records)
							{
								// add xml node index reference to each record, for use with setting selected record,	
								// can't just rely on record index because items for deletion are filtered								
								for (var r = 0; r < records.length; r++)
								{
									records[r].xmlIndex = r + 1;
									records[r].data.fromDeff = DesktopWeb.Util.getDateDisplayValue(records[r].data.fromDeff);
								}								
								store.filterBy(function(record){
									return record.data.dtlRunMode != _controller.DEL})
							}
						}						
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{					
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record){_controller.setSelectedDetl(record.xmlIndex);}								
							,rowdeselect: function(){_controller.clearSelectedDetl()}
						}									
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{width: 25, dataIndex:'detlErrorMsg', renderer: function(val){return (val ? DesktopWeb.Util.buildErrorFlag(val) : '')}}
							,{id: 'reason', header: _translationMap['Reason'], dataIndex: 'reasonDesc'}							
							,{header: _translationMap['FromDate'], dataIndex: 'fromDeff', width:100}																																		
						]		
					}
				)
				,buttons: [					
					new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'addBtn'								
							,text: _translationMap['Add']
							,handler: function(){_controller.openActionPopup( 'detl', _controller.ADD);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'modBtn'
							,text: _translationMap['Modify']
							,handler: function(){_controller.openActionPopup( 'detl', _controller.MOD);}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'delBtn'
							,text: _translationMap['Delete']
							,handler: function(){_controller.openActionPopup( 'detl', _controller.DEL);}
						}
					)				
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'adminBtn'
							,text: _translationMap['Admin']
							,handler: function(){_controller.openAdminPopup('detl');}
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'historicalBtn'
							,text: _translationMap['Historical']
							,handler: function(){_controller.openHistoricalPopup('detl')}
						}
					)
				]			
			}
		)
		,fileProcs: new DesktopWeb.AdvancedControls.GridPanel(
			{										
				width: 400
				,style: "margin-bottom:15px"
				,autoScroll: true							
				,height: 110
				,autoExpandColumn: 'procStat'
				,disableSelection: true
				,trackMouseOver: false							
				,store: new Ext.data.XmlStore(
					{
						record: 'FileProc'					
						,fields: ['taxYear', 'docTypeDesc', 'procStatDesc', 'extractDate', 'submissionDate', 'verDesc']		
						,listeners: {
							load: function(store, records)
							{															
								Ext.each(records, function(record){
									record.data.procStatDesc = DesktopWeb.Util.getDateDisplayValue(record.data.procStatDesc);
									record.data.extractDate = DesktopWeb.Util.getDateDisplayValue(record.data.extractDate);
									record.data.submissionDate = DesktopWeb.Util.getDateDisplayValue(record.data.submissionDate);
								});

								store.fireEvent('datachanged', store); //to set data in grid again
							}
						}							
					}
				)				
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{header: _translationMap['TaxYear'], dataIndex: 'taxYear', width:60}							
							,{header: _translationMap['DocType'], dataIndex: 'docTypeDesc', width:55}																																		
							,{header: _translationMap['Version'], dataIndex: 'verDesc', width:85}
							,{id: 'procStat', header: _translationMap['ProcessStatus'], dataIndex: 'procStatDesc'}
							,{header: _translationMap['ExtractionDate'], dataIndex: 'extractDate', width:65}
							,{header: _translationMap['SubmissionDate'], dataIndex: 'submissionDate', width:65}
						]		
					}
				)						
			}
		)
	}
	
	// **** popups ****
	var _popups = {
		mstr: new DesktopWeb.AdvancedControls.PopupWindow(
			{				
				action: null
				,width: 670
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						html: "Are you sure you want to delete this record?"							
						,style: 'text-align:center'														
					}						
					,{						
						layout: 'column'																		
						,style: 'padding:4px'
						,defaults: {border: false, labelWidth:100}						
						,items: [
							{
								width: 415
								,layout: 'form'																					
								,items: [
									new DesktopWeb.Controls.SMVComboBox(
										{											
											itemId: 'benefID'
											,fieldLabel: _translationMap['RESPBeneficiary']
											,width:185
											,allowBlank: false							
											,hiddenField: true
										}
									)											
									,new Ext.form.TextField(
										{
											itemId: 'acctName'
											,width:285
											,fieldLabel: _translationMap['AccountOwner']
											,hiddenField: true
											,disabledField: true
										}
									)
									,new DesktopWeb.Controls.SMVComboBox(
										{
											itemId: 'reqType'
											,fieldLabel: _translationMap['RequestType']
											,width: 185
											,allowBlank: false							
										}
									)
									,new DesktopWeb.Controls.DateField(
										{
											itemId: 'deff'
											,fieldLabel: _translationMap['EffectiveDate']
											,allowBlank: false
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										}
									)
								]
							}							
							,{
								width: 230
								,layout: 'form'
								,defaults: {width: 105}															
								,items: [									
									new DesktopWeb.Controls.SMVComboBox(
										{
											itemId: 'filingType'
											,fieldLabel: _translationMap['FilingType']
											,allowBlank: false									
										}
									)
									,new DesktopWeb.Controls.SMVComboBox(
										{
											itemId: 'reqStat'
											,fieldLabel: _translationMap['RequestStatus']
											,allowBlank: false									
										}
									)																													
								]
							}
						]						
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['OK']
							,handler: function(){
								if (_popups['mstr'].isValid())
								{
									_controller.saveUpdate('mstr', _popups['mstr'].action, _popups['mstr'].getData())								
								}
							}
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['Cancel']
							,handler: function(){_popups['mstr'].hide();}
						}
					)
				]
				,init: function(action)
				{
					this.action = action					
					this.clearAllFields();
					this.get(0).hide(); //hide delete message	

					var acctTaxType = _controller.getAccountTaxType();

					if( acctTaxType.toLowerCase() == '9' || acctTaxType.toLowerCase() == 'm' )
					{
						this.getField('benefID').showField();
						this.getField('acctName').hideField();
					}
					else
					{											
						this.getField('benefID').hideField();
						this.getField('acctName').showField();	
					}
					
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle(_translationMap['AmendmentRequestAdd']);
							this.populateDefaultValues();												
							this.enableAllFields();
							this.getField('reqStat').disableField();					
							if( acctTaxType.toLowerCase() == 'v')
							{
								this.getField('acctName').disableField();
							}
							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['AmendmentRequestModify']);							
							this.populate();
							if (this.getField('reqType').getValue() == '3')
							{
								this.disableAllFields();
								this.getField('reqStat').enableField();

								if( acctTaxType.toLowerCase() == 'v')
								{
									this.getField('acctName').disableField();
								}
							}
							else
							{
								this.enableAllFields();
								if( acctTaxType.toLowerCase() == '9' || acctTaxType.toLowerCase() == 'm' )
								{
									this.getField('benefID').disableField();
								}

								if( acctTaxType.toLowerCase() == 'v')
								{
									this.getField('acctName').disableField();
								}
							}
							break;
						}
						case _controller.DEL:
						{
							this.setTitle(_translationMap['AmendmentRequestDelete']);
							this.get(0).show(); //show delete message
							this.disableAllFields();
							this.populate();
							break;
						}
					}						
				}
				,populateDefaultValues: function()
				{
					var defaultValues = _controller.getDefaultValues();
					var defaultAcctName = defaultValues['acctName'];
					this.getField('benefID').setValue(defaultValues['benefID']);										
					
					if( defaultAcctName == '' )
					{
						defaultAcctName = DesktopWeb._SCREEN_PARAM_MAP['AccountOwnerName'];
					}
					
					this.getField('acctName').setValue(defaultAcctName);

					this.getField('reqType').setValue(defaultValues['reqType']);
					this.getField('reqStat').setValue(defaultValues['reqStat']);
					this.getField('filingType').setValue(defaultValues['filingType']);
					this.getField('deff').setValue(defaultValues['fromDeff']);
						
				}
				,populate: function()
				{
					var mstrXML = _controller.getSelectedMstr();
					this.getField('benefID').setValue(IFDS.Xml.getNodeValue(mstrXML, 'benefID'));

					var acctTaxType = _controller.getAccountTaxType();

					if( acctTaxType == 'v' )
					{
						var acctOwnername = _controller.getTFSAAccountOwnerName();
						if( acctOwnername == '' )
						{
							acctOwnername = DesktopWeb._SCREEN_PARAM_MAP['AccountOwnerName'];
						}
						this.getField('acctName').setValue(acctOwnername);
					}

					this.getField('reqType').setValue(IFDS.Xml.getNodeValue(mstrXML, 'reqType'));
					this.getField('deff').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(mstrXML, 'deff')));
					this.getField('filingType').setValue(IFDS.Xml.getNodeValue(mstrXML, 'filingType'));
					this.getField('reqStat').setValue(IFDS.Xml.getNodeValue(mstrXML, 'reqStat'));
				}
				,getData: function()
				{
					var data = {};
					data['benefID'] = this.getField('benefID').getValue();
					data['acctName'] = this.getField('acctName').getValue();
					data['beneName'] = this.getField('benefID').getValueDesc();
					data['reqType'] = this.getField('reqType').getValue();
					data['reqTypeDesc'] = this.getField('reqType').getValueDesc();					
					data['filingType'] = this.getField('filingType').getValue();					
					data['filingTypeDesc'] = this.getField('filingType').getValueDesc();					
					data['reqStat'] = this.getField('reqStat').getValue();
					data['reqStatDesc'] = this.getField('reqStat').getValueDesc();
					data['deff'] = this.getField('deff').getSMVDateString();
					return data;
				}				
			}
		)
		
		,detl: new DesktopWeb.AdvancedControls.PopupWindow(
			{				
				width: 340
				,action: null
				,closeAction: 'hide'					
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						html: "Are you sure you want to delete this record?"							
						,style: 'text-align:center'														
					}						
					,{						
						layout: 'form'																		
						,style: 'padding:4px'
						,labelWidth: 80
						,items: [
							new DesktopWeb.Controls.SMVComboBox(
								{
									itemId: 'reasonCode'
									,width: 212
									,fieldLabel: _translationMap['Reason']
									,allowBlank: false
									,listeners: {
										change: function(fld, newValue)
										{
											if (newValue == '06' || newValue == '07')
											{												
												_popups['detl'].getField('fromDeff').setValue(_controller.getDefaultValues()['fromDeff_06_07']);
											}
											else
											{
												_popups['detl'].getField('fromDeff').setValue(_controller.getDefaultValues()['fromDeff']);
											}
										}
									}														
								}
							)											
							,new DesktopWeb.Controls.DateField(
								{
									itemId: 'fromDeff'
									,fieldLabel: _translationMap['FromDate']
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								}
							)
						]												
					}													
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['OK']
							,handler: function(){
								if (_popups['detl'].isValid())
								{
									_controller.saveUpdate('detl', _popups['detl'].action, _popups['detl'].getData())
								}
							}
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['Cancel']
							,handler: function(){_popups['detl'].hide();}
						}
					)
				]
				,init: function(action)
				{					
					this.action = action					
					this.clearAllFields();
					this.get(0).hide(); //hide delete message	
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle(_translationMap['AmendmentDetailAdd']);
							this.enableAllFields();
							this.populateDefaultValues();							
							this.getField('reasonCode').focus();				
							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['AmendmentDetailModify']);
							this.disableAllFields();
							this.getField('fromDeff').enableField();							
							this.populate();
							break;
						}
						case _controller.DEL:
						{
							this.setTitle(_translationMap['AmendmentDetailDelete']);
							this.get(0).show(); //show delete message
							this.disableAllFields();
							this.populate();
							break;
						}
					}						
				}
				,populateDefaultValues: function()
				{
					var defaultValues = _controller.getDefaultValues();
					this.getField('fromDeff').setValue(defaultValues['fromDeff']);
					if (defaultValues['reasonCode'])
					{
						this.getField('reasonCode').setValue(defaultValues['reasonCode']);
					}
				}
				,populate: function()
				{					
					var detlXML = _controller.getSelectedDetl();					
					this.getField('reasonCode').setValue(IFDS.Xml.getNodeValue(detlXML, 'reasonCode'));
					this.getField('fromDeff').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(detlXML, 'fromDeff')));
				}
				,getData: function()
				{
					var data = {};
					data['reasonCode'] = this.getField('reasonCode').getValue();
					data['reasonDesc'] = this.getField('reasonCode').getValueDesc();
					data['fromDeff'] = this.getField('fromDeff').getSMVDateString();
					return data;
				}							
			}
		)
		
		,admin: new DesktopWeb.AdvancedControls.PopupWindow(
			{								
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
									new DesktopWeb.Controls.Label(
										{											
											itemId: 'userName'
											,fieldLabel: _translationMap['Username']
										}
									)
									,new DesktopWeb.Controls.Label(
										{											
											itemId: 'modUser'
											,fieldLabel: _translationMap['ModUser']
										}
									)																					
								]
							}							
							,{
								width: 185
								,layout: 'form'
								,defaults: {width: 80}																							
								,items: [
									new DesktopWeb.Controls.Label(
										{											
											itemId: 'procDate'
											,fieldLabel: _translationMap['ProcessDate']
										}
									)
									,new DesktopWeb.Controls.Label(
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
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['OK']
							,handler: function(){_popups['admin'].hide();}
						}
					)
				]
				,init: function(title, data)
				{
					this.setTitle(title);
					this.getField('procDate').setValue(data['procDate']);
					this.getField('modDate').setValue(data['modDate']);
					this.getField('userName').setValue(data['userName']);
					this.getField('modUser').setValue(data['modUser']);	
				}										
			}					
		)
		,history: new DesktopWeb.AdvancedControls.HistoryPopup()
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
					_grids['mstrs']
					,{
						layout: 'column'
						,items:[
							{
								width: 355
								,items: [
									_grids['detls']
								]
							}
							,{
								width: _layoutWidth - 355
								,items: [
									_grids['fileProcs']
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
					text: _translationMap['OK']
					,handler: function(){DesktopWeb.Util.commitScreen()}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}