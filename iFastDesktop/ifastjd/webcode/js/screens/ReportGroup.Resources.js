/*
 * Procedure: ReportGroup.Resources.js
 *
 * Purpose  : ReportGroup screens manage reportgroup data		  
 *             
 * Notes    : Open screens by Menu -> MF and MFR Maintenance -> Report Group
 *							  Menu -> System Maintenance -> Holding Company -> Report Groups
 *
 * History  : 
 *	
 *		 5 Mar 2013 Hirun Sartsangchan PETP0206635 FN01 MFR MFI Enhancments
 *			- Created
 *
 *		23 May 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3330320 T53597
 *			- Modify Delivery Name for displaying label as 2 lines
 *		
 *		29 May 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3338220 T53638
 *          - Change the update state by
 *          1) Call with  validation mode
 *          2) if there is no error, call commit screen which will make the update to database.
 *
 *		10 Jun 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3343398 T53727
 *          - Fix the inititate screen when screen is launch back from Account Associate.
 *          - Table is not set the selected record the same as before launching screen.
 *          - On Modify Pppup screen:The holding company must not be allowed to modify.
 *
 *		10 Jul 2013 Gomoot Thawornwachirakun PETP0206635 FN01 IN3359189 T53824
 *          - Update width of city and province
 *
 *		05 Aug 2013 Gomoot Thawornwachirakun PETP0206635 FN01 DFT0012847 T53963
 *          - Add ability to set dynamic mandatory PSTL field on selected country
 *          - Remove allowBlank from PSTL field
 *
 *    11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 */
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
		
	var _layoutHeight = 580;
	var _layoutWidth = 800;
	var _reportType = 'MFR';
	
	// **** fields ****/
	var _fields = {	
	
		holdingCompanySrch: new DesktopWeb.Controls.SuggestField({
										fieldLabel: _translationMap['HoldingCompany']
										,smartview: 'holdingCompanySearch'
										,fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'displayValue' ]
										,valueField: 'holdingCompanyCode'
										,displayField: 'displayValue'	
										,addtlSearchParams: [{name: 'coUsage', valueFn: function(){return _reportType;}}] 
										,width: 240
										,listeners: {
											change: function()
											{
												_controller.updateHoldingAndReportGroupSearchText();
												_grids['reportGroupInfo'].disableButton('moreBtn');
											}
											,cleared: function()
											{
												_grids['reportGroupInfo'].disableButton('moreBtn');
											}											
										}
									})
		,reportGroup: new DesktopWeb.Controls.SuggestField({
										fieldLabel: _translationMap['ReportGroup']
										,smartview: 'reportGroupSearch'
										,fields: ['displayValue', 'reportGroupID', 'holdingEntityCode'
										           , 'reportGroupUUID', 'reportGroupDesc'
												   , 'reportGroupName1', 'reportGroupName2']
										,valueField: 'reportGroupUUID'
										,displayField: 'displayValue'
										,addtlSearchParams: [{name: 'holdingEntityCode', 
											valueFn: function()
											{
												return _fields['holdingCompanySrch'].getValue() != '' ? _fields['holdingCompanySrch'].getValue() : '' ;											
											}
										}] 
										,width: 240
										, listeners: {
											change: function()
											{
												_controller.updateHoldingAndReportGroupSearchText();
											}
											,cleared: function()
											{
												_grids['reportGroupInfo'].disableButton('moreBtn');
											}				
										}										
									})
		,optSelectAll: new DesktopWeb.Controls.Radio({
										boxLabel: _translationMap['All']
										,name:'filterBy'
										,handler: function() {_controller.selectopt();_grids['reportGroupInfo'].disableButton('moreBtn');}	
									})
		,optSelectAsOfDate: new DesktopWeb.Controls.Radio({
										boxLabel: _translationMap['EffectiveAsOf']										
										,labelWidth: 100
										,name:'filterBy'
										,handler: function() {_controller.selectopt();_grids['reportGroupInfo'].disableButton('moreBtn');}	
									})
		,asOfDate: new DesktopWeb.Controls.DateField({	
										width: 100
										,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										,listeners: {
											change: function(){
												_grids['reportGroupInfo'].disableButton('moreBtn');												
											}
										}
									})
		,reportGroupID: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['ReportGroupID']
										,width: 100
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		
		,reportGroupName: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['Name']
										,width: 250
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		
		,deliveryName1: new Ext.form.TextArea({
										fieldLabel: _translationMap['DeliveryName']
										,width: 250
										,anchor		: '100%'
										,grow		: true
										,growMin	: 0
										,autoScroll	: true
										,readOnly	: true
										,growAppend	: ''
										,style: 'background:none;border:none'
									})	

		,address: new Ext.form.TextArea({
										fieldLabel: _translationMap['Address']
										,width: 250
										,anchor		: '100%'
										,style: 'background:none;border:none'
										,grow		: true
										,growMin	: 0
										,autoScroll	: true
										,readOnly	: true
										,growAppend	: ''
										
									})
		,city: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['City']
										,width: 250
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		,province: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['Province']
										,width: 200
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		,pstl: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['PostalZipCode']
										,width: 200
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		,effectiveDate: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['EffectiveDate']
										,width: 150
										,readOnly: true										
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		,stopDate: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['StopDate']
										,width: 150
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		,language: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['Language']
										,width: 150
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})
		,supplyInfoReq: new DesktopWeb.Controls.Label({
										fieldLabel: _translationMap['SupplyInfoReq']
										,width: 150
										,readOnly: true
										,style: 'word-wrap:break-word;verical-align:top;'
									})		
	}
	
	var _buttons = {
		btnSearch: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Search']
				,handler: function() {_controller.clickHandleSearchBtn();}	
			}
		)
		,btnAccountList: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['AccountList']
				,handler: function() {_controller.clickHandleSearchBtn();}	
			}
		)
	}
	
	// **** grids ****
	var _grids = {
		reportGroupInfo: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth - 10
			
			,autoScroll: true							
			,height: 175
			,autoExpandColumn: 'reportgroupname'											
			,store: new Ext.data.XmlStore({
				record: 'ReportGroupDetl'					
				,fields: ['errMsg','runMode', 'reportGroupIndex', 'reportGroupID', 
				'reportGroupName', 'reportGroupName2',
				'holdingEntityCode', 'holdingEntityDesc', 'effectiveDate', 'stopDate', 
						  'deliveryName1','deliveryName2',
						  'address1','address2','address3','address4',
						  'city','province','pstl','langCode',  'supplyInfoReq',
						  'allowDelete', 'version','createUser','createDate','modifyUser','modifyDate',
						  'hasAcctAsso']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.effectiveDate = DesktopWeb.Util.getDateDisplayValue(record.data.effectiveDate);
							record.data.stopDate      = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
							record.data.createDate    = DesktopWeb.Util.getDateDisplayValue(record.data.createDate);
							record.data.modifyDate    = DesktopWeb.Util.getDateDisplayValue(record.data.modifyDate);
						});
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});																																		
					}
				}					
			})
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.updateActionButtons();}					
				}						
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}

				,columns: [													
					{	dataIndex: 'errMsg'
						,width: 25
						,renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
					}					
					,{	header: _translationMap['HoldingCompany']
						,dataIndex: 'holdingEntityDesc'
						,width:100
						,renderer: function(val, metaData, record){return (record.data['holdingEntityCode'] + ' - ' + record.data['holdingEntityDesc'])}
					}
					,{	header: _translationMap['ReportGroupID']
						,id:'reportgroupid' 
						,dataIndex: 'reportGroupID'
					}					
					,{	header: _translationMap['Name']
						,id:'reportgroupname'
						,dataIndex: 'reportGroupName'
						,width:150 
						,renderer: function(val, metaData, record){return (record.data['reportGroupName'] + record.data['reportGroupName2'])} 
					}
					,{	header: _translationMap['EffectiveDate']
						,dataIndex: 'effectiveDate'
						,width:150
					}
					,{	header: _translationMap['StopDate']
						,dataIndex: 'stopDate'
						,width:150
					}
					
					
				]							
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']							
					,handler: function(){_controller.openActionPopup(_controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.deleteSelectedRecord();}						
				})					
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,handler: function(){_controller.clickHandleMoreBtn();}							
				})					
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup();}							
				})
				, new DesktopWeb.Controls.ActionButton({
					itemId: 'historicalBtn'
					,text:_translationMap['Historical']
					,handler: function(){_controller.openHistoryPopup();}
				})
			]				
		})		
	}
	
	// **** popups ****
	var _popups = {			
		reportGroup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 430
			,action: null						
			,modal: true
			,defaults: {border:false}			
			,items: [
				{						
					layout: 'form'																		
					,style: 'padding:4px'
					,labelWidth: 110					
					,items: [						
						new DesktopWeb.Controls.SuggestField({
							itemId: 'holdingCompanySrchPopup'
							,fieldLabel: _translationMap['HoldingCompany']
							,smartview: 'holdingCompanySearch'
							,fields: ['holdingCompanyCode', 'holdingCompanyDesc', 'displayValue']
							,valueField: 'holdingCompanyCode'
							,displayField: 'displayValue'	
							,addtlSearchParams: [{name: 'coUsage', valueFn: function(){return _reportType;}}] 
							,width: 240	
							,allowBlank: false
							
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'reportGroupID'							
							,fieldLabel: _translationMap['ReportGroupID']
							,maxLength: 10
							,allowBlank: false
						})	
						,new DesktopWeb.Controls.TextField({
							itemId: 'reportGroupName'
							,width: 270
							,fieldLabel: _translationMap['Name']	
							,allowBlank: false	
							,maxLength: 60
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'reportGroupName2'
							,width: 270
							,maxLength: 60
						})						
						,{
							layout: 'column'
							,border:false
							,labelWidth: 30
							,defaults: {
								layout: 'form'								
								,border:false
							}
							,items:[
								{		
									labelWidth: 110									
									,columnWidth:0.55
									,items:[									
										new DesktopWeb.Controls.DateField({
										itemId: 'effectiveDate'
										,width: 90
										,fieldLabel: _translationMap['EffectiveDate']
										,allowBlank: false	
										,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())										
										})		
									]
								}
								,{	
									labelWidth: 63
									,columnWidth:0.45
									,style: 'padding-left:3px'
									,items:[	
										new DesktopWeb.Controls.DateField({
										itemId: 'stopDate'
										,width: 90
										,fieldLabel: _translationMap['StopDate']
										,allowBlank: false
										,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										})
									]
								}
							]
						 }
						,new DesktopWeb.Controls.TextField({
							itemId: 'deliveryName1'
							,width: 270
							,fieldLabel: _translationMap['DeliveryName']
							,maxLength: 40
							,allowBlank: false														
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'deliveryName2'
							,maxLength: 40
							,width: 270																				
						})
					
						,new DesktopWeb.Controls.TextField({
							itemId: 'address1'
							,width: 270
							,fieldLabel: _translationMap['Address']
							,allowBlank: false	
							,maxLength: 40
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'address2'
							,width: 270							
							,maxLength: 40												
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'address3'
							,width: 270
							,maxLength: 40														
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'address4'
							,width: 270
							,maxLength: 40													
						})							
						,new DesktopWeb.Controls.TextField({
							itemId: 'city'
							,width: 270
							,fieldLabel: _translationMap['City']
							,allowBlank: false
							,maxLength: 30							
						})
						,new DesktopWeb.Controls.ComboBox({
							itemId: 'province'
							,width: 270
							,fieldLabel: _translationMap['Province']
							,allowBlank: false	
							,valueField: 'code'
							,displayField: 'value'
							,store: new Ext.data.XmlStore(
							{
								record: 'Element'
								,fields: ['code', 'value', 'requirePSTL']
							})
							,listeners: {
								select: function(combo, record, index){
									_popups['reportGroup'].getField('pstl').clearInvalid();
								}
							}
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'pstl'
							,width: 180
							,fieldLabel: _translationMap['PostalZipCode']
							,maxLength: 9
							,allowBlank: true
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'language'
							,width: 180
							,fieldLabel: _translationMap['Language']
							,allowBlank: false								
						})
						,new DesktopWeb.Controls.YesNoComboBox({
							itemId: 'supplyInfoReq'
							,width: 180
							,fieldLabel: _translationMap['SupplyInfoReq']
							,allowBlank: false								
						})												
					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						var isValid			= _popups['reportGroup'].isValid();
						var tempdata		= _popups['reportGroup'].getData(_popups['reportGroup'].action);
						var validateResult	= _controller.doValidatePopup(_popups['reportGroup'].action
											,tempdata)
						
						if (isValid && validateResult)
						{
							_controller.checkHasAcctAsso(_popups['reportGroup'].action,tempdata);
							_controller.savePopup(_popups['reportGroup'].action,tempdata);
							_popups['reportGroup'].hide();
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){
						_controller.updateActionButtons();
						_popups['reportGroup'].hide();						
					}
				})
			]
			,init: function(action)
			{							
				this.action = action					
				this.clearAllFields();
				
				
				switch(action)
				{
					case _controller.ADD:
					{	
						this.setTitle(_translationMap['ReportGroupMaintenance'] + ' - ' + _translationMap['Add']);
						this.enableAllFields();
						break;
					}
					case _controller.MOD:
					{						
						this.setTitle(_translationMap['ReportGroupMaintenance'] + ' - ' + _translationMap['Modify']);
						this.enableAllFields();
						break;
					}				
				}				
			}
			,getData: function(action)
			{
				var data = {};				
				data['runMode'] = action;
				data['errMsg'] = "";

				record  = this.getField('holdingCompanySrchPopup').selectedRecord;
				if (record)
				{
					data['holdingEntityCode'] = record.data['holdingCompanyCode'];
					data['holdingEntityDesc'] = record.data['holdingCompanyDesc'];
				}				
				data['reportGroupID'] = this.getField('reportGroupID').getValue();
				data['reportGroupName'] = this.getField('reportGroupName').getValue();
				data['reportGroupName2'] = this.getField('reportGroupName2').getValue();
								
				data['effectiveDate'] = this.getField('effectiveDate').getValue();
				data['stopDate']      = this.getField('stopDate').getValue();
				
				data['deliveryName1'] = this.getField('deliveryName1').getValue();
				data['deliveryName2'] = this.getField('deliveryName2').getValue();
				
				data['address1'] = this.getField('address1').getValue();
				data['address2'] = this.getField('address2').getValue();
				data['address3'] = this.getField('address3').getValue();
				data['address4'] = this.getField('address4').getValue();				
								
				data['city'] = this.getField('city').getValue();
				data['province'] = this.getField('province').getValue();
				
				data['pstl'] = this.getField('pstl').getValue().trim();
				this.getField('pstl').setValue(data['pstl']);
				
				data['langCode'] = this.getField('language').getValue();

				data['supplyInfoReq'] = this.getField('supplyInfoReq').getValue();

				if (this.action == _controller.ADD )
				{
					data['version'] = 0;
					data['reportGroupIndex'] = _controller.NEWRECORD + _controller.cnewitem++;
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
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,buttons: _buttons
		
		,layout: new Ext.Container(			
			{						
				height: _layoutHeight
				,width: _layoutWidth	
				,style: 'margin-right:3px; padding-left:0px;'				
				,items: [				
					new Ext.Container({
						layout:'column'							
						,style:'padding-left:12px; margin-bottom:5px;padding-right:5px'	
						,labelWidth:120	
						,width: _layoutWidth						
						,items: [							
							{								
								layout:'column'								
								,columnWidth: 1
								,defaults: { layout:'form'}
								,items:[
									{
										columnWidth: 0.5
										,items:[
											_fields['holdingCompanySrch']
										]
									}	
									,{
										columnWidth: 0.5
										,items:[
											_fields['reportGroup']
										]
									}
								]
							}
							,{
								columnWidth: 0.05								
								,items:[
									_fields['optSelectAll']										
								]							
							}							
							,{	
								columnWidth: 0.15
								,items:[
									_fields['optSelectAsOfDate']
								]							
							}
							,{
								columnWidth: 0.2
								,items:[
									_fields['asOfDate']
								]							
							}
							,{
								columnWidth: 0.6
								,style: 'text-align:right;margin-right:20px'
								,items:[
									_buttons['btnSearch']
								]							
							}
							
						]
					})
					,{
						xtype: 'fieldset'
						,title: _translationMap['ReportGroupDetail']						
						,width: _layoutWidth
						,items: _grids['reportGroupInfo']
					}
					,{	xtype: 'fieldset'
						,title: _translationMap['ReportGroupInfo']
						,items: [
							new Ext.Container({
								layout:'column'							
								,style:'padding-left:12px; padding-right:12px;overflow-y:auto'	
								,labelWidth:120	
								,defaults: {
										layout:'form'
										}
								,items: [		
									{								
										columnWidth: 0.5
										,items: [
											_fields['reportGroupID']
											,_fields['reportGroupName']
											,_fields['deliveryName1']
											,_fields['language']
											,_fields['supplyInfoReq']	
										]								
									}
									,{
										columnWidth: 0.5
										,items: [
											_fields['effectiveDate']
											,_fields['stopDate']
											,_fields['address']
											,_fields['city']
											,_fields['province']
											,_fields['pstl']
										]								
									}
									
								]
							})
						]
					}
										
				]				
			}
		)
		
		,screenButtons: {
			buttonAlign: 'left'
			,items:[
				new DesktopWeb.Controls.ScreenButton(
					{
						id:'AccountList'
						,text: _translationMap['AccountList']
						,handler: function(){	
												if(_controller.updatesFlag){
													DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
																				
													function handlePromptMsg(btn){
														if(btn){
															_controller.clickHandleAccountListBtn();
														}
													}
												}else{
												_controller.clickHandleAccountListBtn();
												}
												
											}
					}
				)
				,'->'
				,new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['OK']
						,handler: function(){ 
							if(_controller.updatesFlag)
								_controller.doValidateCommitScreen();
							else
								DesktopWeb.Util.commitScreen();
						}
					}
				)
				,new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['Cancel']
						,handler: function(){
							if(_controller.updatesFlag){
								DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
															
								function handlePromptMsg(btn){
									if(btn){
										DesktopWeb.Util.cancelScreen();
									}
								}
							}else{
							DesktopWeb.Util.cancelScreen();
							}
						}
					}
				)
			]
		}

	}
}
