/*********************************************************************************************
 * @file	RegStd.Resources.js
 * @author	Manoj Kumar
 * @desc	Resources JS file for Regulatory Standards screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	17 Oct 2013 N. Suanlamyai P0193400 DFT0022411 T54302
 *					- Add band permission to the screen.
 *
 *  24 Jan 2014 G. Thawornwachirakun P0223930 FN01 
 *          - Support French Translation
 *
 *  8 Feb 2014 Winnie Cheng P0223057 T77753
 *                  - Added new fields and logic for CDOT FATCA
 *                    back-end sent a lists and save new fields values
 *                    back-end sent an error node in returned response xml
 *
 *  20 Feb 2014 Winnie Cheng P0223057 T77795
 *                  - Remove Country disable line of code
 *                    change set Report To Country with code, not description
 *          
 *  28 Feb 2014 Winnie Cheng P0223057 T77807 DFT0029706
 *                  - Deletion should follow the CDOT rule without affecting US FATCA
 *                    
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  18 Nov 2014 Winnie Cheng P0234088 T78496 
 *             - Restrict complyCode to 4 char, description field to 200 char.
 *
 *  6 Dec 2014 Winnie Cheng P0234088 T78497 
 *             - Replace special char.(horizontal Tab, double inverted commas) 
 *               of description field as a space.
 *
 *  18 Nov 2014 Winnie Cheng P0247899  T81687 
 *             - Desktop Screen Regulatory Standard modification to allow the user filter records
 *             - Be able to retrive more records by providing "More" button.
 *    
 *  3 Feb 2017  Winnie Cheng P0259672  T84745
 *			  - Enhance the screen for CRS Report regulation rule and Jurisdisction records
 *
 *  23 March 2017  Winnie Cheng P0259672  T85110
 *			  - fixing an existing issue
 *
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 720;
	var _layoutWidth = 700;
	
	// **** fields ****
	var _fields = {
		regulationRule: new DesktopWeb.Controls.SMVComboBox({			
			fieldLabel: _translationMap['regulationRule']
			,width: 180
		})
		,validTaxTypes: new DesktopWeb.Controls.TextField({
			readOnly: true
			,width: 200
		})
		,validAcctType: new DesktopWeb.Controls.TextField({
			readOnly: true
			,width: 200
		})	
		,validAcctDesignation: new DesktopWeb.Controls.TextField({
			readOnly: true
			,width: 170
		})	
		,countryFilter: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['country']
			,width: 180			
			,allowBlank: true
		}) 		
		,status: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['Status']
			,width: 180		
			,allowBlank: true
		})
	};
	
	// **** buttons ****
	var _buttons = {
		search: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,handler: function(){
				_controller.populateGrid('search', false);
			}
		})
	}
		
	var _expander = new Ext.ux.grid.RowExpander({
		listeners: {
			beforeexpand : function( expander, record, body, rowIndex) {
				_grids['regStdInfo'].setSelectedRecord(rowIndex)				
            }
		}
        ,tpl : new Ext.XTemplate(			
        	'<div class="DetailsSectionDiv">'
				,'<table>'
					,'<tpl if="regRule != &quot;CC&quot;">'
						,'<tr>'
						,'<td>{[this.fieldNames("investorType")]}:</td>'
						,'<td>{investorTypeDesc}</td>'
						,'<td>{[this.fieldNames("investOnBehalfOfTP")]}:</td>'
						,'<td>{[this.investFor3rdPartyValue()]}</td>'
					,'</tr>'
					,'</tpl>'					
					,'<tr>'
						,'<td>{[this.fieldNames("EffectiveDate")]}:</td>'
						,'<td>{effDate}</td>'
						,'<td>{[this.fieldNames("StopDate")]}:</td>'
						,'<td>{stopDate}</td>'
					,'</tr>'
					,'<tr>'
						,'<td>{[this.fieldNames("province")]}:</td>'
						,'<td>{provinceDesc}</td>'
						,'<td>{[this.fieldNames("taxTypes")]}:</td>'
						,'<td>{[this.taxTypes()]}</td>'
						,'<td>{[this.fieldNames("acctType")]}:</td>'
						,'<td>{[this.acctType()]}</td>'
					,'</tr>'
				,'</table>'
				,'<div class="x-DocListDiv ">'
					,'<table>'
						,'<thead>'
							,'<tr>'
								,'<td style= "width: 100px">{[this.fieldNames("docCode")]}</td>'
								,'<td style= "width: 1000px">{[this.fieldNames("description")]}</td>'
							,'</tr>'
						,'</thead>'
						,'<tbody>'
							,'<tpl for="this.docList()">'
								,'<tr><td>{.:this.docCodeSplit()}</td><td>{.:this.documentSplit()}</td></tr>'
							,'</tpl>'
						,'</tbody>'
					,'</table>'
				,'</div>'				
			,'</div>'	
			,{
					taxTypes: function()
					{
						return _controller.taxTypesCode();
					}										
					,acctType: function()
					{
						return _controller.acctTypeCode();
					}										
					,investFor3rdPartyValue : function()
					{
						return _controller.getInvestFor3rdPartyValue();
					}
					,docList: function()
					{												
						return _controller.docList('xTemplate');
					}
					,fieldNames: function(fieldName)
					{
						return _translationMap[fieldName];
					}
					,docCodeSplit: function(str)
					{						
						return str.split('~')[0];
					}
					,documentSplit: function(str)
					{
						return str.split('~')[1];
					}
			}	
        )
    });
	
	// **** grids ****
	var _grids = {
		regStdInfo: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth
			,style: "margin-bottom:15px"
			,autoScroll: true							
			,height: 620
			,autoExpandColumn: 'stdDesc'											
			,store: new Ext.data.XmlStore({
				record: 'RegStandard'					
				,fields: ['regStandardId', 'countryCode', 'countryDesc', 'provinceCode', 'provinceDesc', 'regRule', 'regRuleDesc', 'complyCode', 'description', 'investorType', 'investorTypeDesc', 'investFor3rdParty', 'effDate', 'stopDate', 'acctType', 'acctTypeDesc', 'actionCode', 'actCodeDesc', 'lowerBound', 'upperBound', 'fundCategory', 'fundCategoryDesc', 'docList', 'TaxTypes', 'regModel', 'regModelDesc', 'acctDesignation', 'fatcaCode','rptToCntry','rptToCntryDesc', 'rptJuris','inActDeff']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							Ext.data.Record.id(record);
							
							record.data.effDate = DesktopWeb.Util.getDateDisplayValue(record.data.effDate);
							record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);							
						});
						
						store.fireEvent('datachanged', store); //to set data in grid again
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
					_expander
					,{header: _translationMap['country'], dataIndex: 'countryDesc', width:120}					
					,{header: _translationMap['regulationRule'], dataIndex: 'regRuleDesc', width:120}
					,{header: _translationMap['regulatoryCode'], dataIndex: 'complyCode', width:120}
					,{header: _translationMap['description'], id:'stdDesc', dataIndex: 'description'}			
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
					,handler: function(){_controller.openActionPopup(_controller.DEL);}							
				})	
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,disabled: true
					,handler: function(){_controller.populateGrid('more',true)} 
				})	
			]
			,plugins: _expander			
		})	
		//CRS Jurisdiction grid
		,taxJurisGrid: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth - 180
			,style: "margin-bottom:5px"
			,autoScroll: true							
			,height: _layoutHeight - 450
			,autoExpandColumn: 'jurisDesc'											
			,store: new Ext.data.XmlStore({
				record: 'ComplyRptJurisListItem'					
				,fields: ['errMsg', 'complyRptJurisUUID', 'jurisdictions', 'cntryCode','startDate', 'endDate','countryDesc']
				,listeners: {
					load: function(store, records) {
						Ext.each(records, function(record){
							record.data.startDate = DesktopWeb.Util.getDateDisplayValue(record.data.startDate);
							record.data.endDate = DesktopWeb.Util.getDateDisplayValue(record.data.endDate);							
						});
						
						store.fireEvent('datachanged', store); //to set data in grid again
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.selectCRSJuris(record);
						}
					}
				}						
			})			
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [{
						id: 'errMsg'
						,width: 25
						,renderer: function(val){
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}
					,{header: _translationMap['jurisdictionGridHeading'],id:'jurisDesc', dataIndex: 'countryDesc', width:160}					
					,{header: _translationMap['startDate'], dataIndex: 'startDate', width:110}
					,{header: _translationMap['StopDate'], dataIndex: 'endDate', width:110}			
				]							
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']							
					,handler: function(){
						_controller.openActionCRSJurisPopup(_controller.ADD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){
						_controller.openActionCRSJurisPopup(_controller.MOD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,handler: function(){
						_controller.clickHandle_moreBtn();
					}
				})
			]	
		})
	}
	// **** ItemSelector ****
	var _selectors = {
		docListSelector: new DesktopWeb.AdvancedControls.ItemSelector(
			{
				height: 125
				,width: 565				
				,availableGridProperties: {
					title: ''
					,width: 220
					,autoExpandColumn: 'desc'
					,store: new Ext.data.XmlStore(
						{
							record: 'Element'
							,fields: ['docCode', 'description']							
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{header: _translationMap['docCode'], dataIndex: 'docCode', width: 75}
								,{id: 'desc', header: _translationMap['description'], dataIndex: 'description'}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true
						}
					)
				}
				,selectedGridProperties: {
					width: 250
					,autoExpandColumn: 'desc'				
					,store: new Ext.data.XmlStore(
						{
							record: 'docListItem'
							,fields: ['docItemId','docCode','description']	
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true
							}
							,columns: [
								{header: _translationMap['docCode'], dataIndex: 'docCode', width: 75}
								,{id: 'desc', header: _translationMap['description'], dataIndex: 'description'}
							]							
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							singleSelect: true													
						}
					)					
				}
			}
		)
	}
	
	// **** popups ****
	var _popups = {		
		regulatoryStandardsPopup: new DesktopWeb.AdvancedControls.PopupWindow({				
				width:  620			
				,style: 'padding-top:20'
				,action: null
				,modal: true
				,defaults: {border:false}
				,items: [
					{
					html: _translationMap['DeleteConfirmMsg']						
					,style: {'text-align':'center','padding-top':'4px'}	
					}
					,{
						layout: 'column'
						,style: 'padding-top:6px'
						,defaults: {border:false}
						,items: [
							{
								columnWidth: 0.5
								,style: 'padding-left:6px'
								,defaults: {border:false}
								,items: [
									{
										layout: 'form'
										,defaults: {border:false}
										,items: [
											new DesktopWeb.Controls.SMVComboBox({	
												itemId: 'regulationRule'
												,width: 150
												,fieldLabel: _translationMap['regulationRule']
												,allowBlank: false
												,listeners:{
													select : function(fld, rec, index){
														if(rec.data.value == '')
														{
															_fields['validTaxTypes'].setValue('');
															_fields['validAcctType'].setValue('');
															_fields['validAcctDesignation'].setValue('');
															_popups['regulatoryStandardsPopup'].getField('province').setValue('');
															_controller.selectorGridClearData();
															_controller.docListSelectorPopulation();
															_popups['regulatoryStandardsPopup'].disableAllFields();
															Ext.getCmp('taxTypesEdit').disable();
															Ext.getCmp('acctTypeEdit').disable();
															Ext.getCmp('acctDesignateEdit').disable();
															_selectors['docListSelector'].availableGrid.disable();
															_popups['regulatoryStandardsPopup'].getField('regulationRule').enableField();
														}
														else
														{
															_popups['regulatoryStandardsPopup'].enableAllFields();

															if(rec.data.code == 'FA' || rec.data.code == 'FT'){
																_controller.populateFatcaValues(rec.data.code);
															} else {
																_controller.showHideCDOTFields(rec.data.code);
															}
															_controller.setReportableJurisFields(rec.data.code, '');

															_fields['validTaxTypes'].setValue(_translationMap['All']);
															_fields['validAcctType'].setValue(_translationMap['All']);
															_fields['validAcctDesignation'].setValue(_translationMap['All']);
															Ext.getCmp('taxTypesEdit').enable();
															Ext.getCmp('acctTypeEdit').enable();
															Ext.getCmp('acctDesignateEdit').enable();

															if(rec.data.code != 'CC'){
																_selectors['docListSelector'].availableGrid.enable();
																_popups['regulatoryStandardsPopup'].getField('regulatoryCode').clearField();
															} else {
																_controller.selectorGridClearData();
																_controller.docListSelectorPopulation();
																_selectors['docListSelector'].availableGrid.disable();
																_popups['regulatoryStandardsPopup'].getField('regulatoryCode').setValue('00');
																_popups['regulatoryStandardsPopup'].getField('regulatoryCode').disableField();
																_popups['regulatoryStandardsPopup'].getField('investorType').disableField();
																_popups['regulatoryStandardsPopup'].getField('investOnBehalfOfTP').disableField();
															}
															_controller.updateFatcaFields(rec.data.code);
															_controller.updateAcctRegistFields(rec.data.code);
															_controller.updateAcctDesignationFields(rec.data.code);
														}
													}													
												}
											})
										]
									}
								]
							}
							,{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [
										{
											layout: 'form'
											,defaults: {border:false}
												,items: [
													new DesktopWeb.Controls.SMVComboBox({						
														itemId: 'fatcaRegulation'
														,labelStyle: 'white-space:nowrap'
														,width: 158
														,fieldLabel: _translationMap['FATCARegulation']
														,allowBlank: false
														,listeners:{
															select : function(fld, rec, index){
																_controller.setCryList(rec.data.code);
															}
														}
												})
											]
										}
									]
							}	
						]
					}
					,{
						layout: 'column'
						,style: 'padding-left:6px'
						,defaults: {border:false}
						,items: [{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [{
										layout: 'form'
										,defaults: {border:false}
										,items: [
											new DesktopWeb.Controls.TextField({				
												itemId: 'regulatoryCode'
												,width: 150
												,fieldLabel: _translationMap['regulatoryCode']
												,allowBlank: false
												,autoCreate: {tag: 'input', type: 'text', maxlength: '4'}
											})
										]
									}
								]
							}
							,{
								columnWidth: 0.4
								,defaults: {border:false}
								,items: [{
									layout: 'form'
									,style: 'text-align:left;white-space:nowrap;'
									,items: [
										new DesktopWeb.Controls.TextField({
											itemId: 'reportableJuris'
											,width: 90
											,editable: false
											,fieldLabel: _translationMap['reportableJurisdisctions']
										})
										,new DesktopWeb.Controls.TextField({
											itemId: 'crsJurisList'	
											,hidden: true													
										})
									]
								}]
							}	
							,{
								columnWidth: 0.1
								,defaults: {border:false}
								,items: [{
									layout: 'form'
									,items: [
										new DesktopWeb.Controls.ActionButton({
											text: _translationMap['Edit']
											,id: 'repJurisEdit'	
											,style: 'padding-left:10px'
											,width: 30
											,listeners:{
												click : function(fld, rec, index){
													var popup = _popups['regulatoryStandardsPopup']; 
													if (popup.isValidJurisdiction()) {
														_controller.validateRegulationPopup(popup.getData(),popup.action); 
													}
												}
											}														
										})
									]
								}]
							}	
						]
					}
					,{
						layout: 'column'
						,style: 'padding-left:6px'
						,defaults: {border:false}
						,items: [
							{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [
										{
										layout: 'form'
										,defaults: {border:false}
										,items: [
												new DesktopWeb.Controls.SMVComboBox({						
												itemId: 'country'
												,width: 150
												,fieldLabel: _translationMap['country']
											})
										]
									}
								]
							}
							,{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [{	
									layout: 'form'
									,defaults: {border:false}
									,items: [
											new DesktopWeb.Controls.SMVComboBox({						
											itemId: 'reportToCountry'
											,labelStyle: 'white-space:nowrap'
											,width: 148
											,fieldLabel: _translationMap['reportToCountry']
											,allowBlank: false
											
										})
									]
								}]
										
							}	
						]
					}
				
					,{
						layout: 'form'
						,style: 'padding-left:6px'
						,defaults: {border:false}
						,items: [
								new DesktopWeb.Controls.SMVComboBox({						
								itemId: 'province'
								,width: 150
								,fieldLabel: _translationMap['province']
								,allowBlank: true
							})
						]
					}
					,{
							layout: 'form'
							,style: 'padding-left:6px'
							,defaults: {border:false}
							,items: [
									new DesktopWeb.Controls.TextField({						
									itemId: 'description'
									,width: 430
									,maxLength: 200
									,fieldLabel: _translationMap['description']
									,allowBlank: false
									,listeners: {
										change: function(fld, newVal, oldVal)
										{
											var convertedStr = _controller.getReplacedString(newVal);
											fld.setValue(convertedStr);
										}
									}
								})
							]
					}
					,{
						layout: 'column'
						,style: 'padding-left:6px'
						,defaults: {border:false}
						,items: [
							{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [
										{
											layout: 'form'
											,defaults: {border:false}
											,items: [
													new DesktopWeb.Controls.DateField({						
													itemId: 'effectiveDate'
													,width: 150
													,fieldLabel: _translationMap['EffectiveDate']
													,allowBlank: false
													,format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
													})
											]
									}
									,{
											layout: 'form'
											,defaults: {border:false}
											,items: [
													new DesktopWeb.Controls.SMVComboBox({						
													itemId: 'investorType'
													,width: 150
													,fieldLabel: _translationMap['investorType']
													,allowBlank: true
													})
											]
									}
									,{
											layout: 'form'
											,defaults: {border:false}
											,items: [
												new DesktopWeb.Controls.TextField({				
													itemId: 'lowerBound'
													,width: 150
													,fieldLabel: _translationMap['lowerBound']
												})
											]
									}
									,{
											layout: 'form'
											,defaults: {border:false}
											,items: [
													new DesktopWeb.Controls.SMVComboBox({
													itemId: 'fundCategory'
													,width: 150
													,fieldLabel: _translationMap['fundCategory']
													,allowBlank: true
													})
											]
									}
								]
							}
							,{
								columnWidth: 0.5
								,defaults: {border:false}
								,items: [
											{
												layout: 'form'
												,defaults: {border:false}
												,items: [
														new DesktopWeb.Controls.DateField({						
														itemId: 'stopDate'
														,width: 150
														,fieldLabel: _translationMap['StopDate']
														,allowBlank: false
														,format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
														})
												]
										}
										,{
												layout: 'form'
												,defaults: {border:false}
												,items: [
														new DesktopWeb.Controls.YesNoComboBox({						
														itemId: 'investOnBehalfOfTP'
														,width: 150
														,fieldLabel: _translationMap['investOnBehalfOfTP']
														,allowBlank: true
														})
												]
										}
										,{
												layout: 'form'
												,defaults: {border:false}
												,items: [
													new DesktopWeb.Controls.TextField({				
														itemId: 'upperBound'
														,width: 150
														,fieldLabel: _translationMap['upperBound']
													})
												]
										}
								]
							}
								
						]						
					}
					,{
						layout: 'form'
						,style: 'padding-left:6px'
						,defaults: {border:false}
						,items: [
							{
								xtype: 'compositefield'	
								,itemId: 'taxTypes'									
								,fieldLabel: _translationMap['taxTypes']												
								,items: [													
									_fields['validTaxTypes'],
									new DesktopWeb.Controls.ActionButton({
										text: _translationMap['Edit']
										,id: 'taxTypesEdit'	
										,width: 35
										,handler: function(){_controller.editValidTaxTypes()}														
									})
								]
							}
							
							,{
								xtype: 'compositefield'	
								,itemId: 'acctType'									
								,fieldLabel: _translationMap['acctType']
								,items: [													
									_fields['validAcctType'],
									new DesktopWeb.Controls.ActionButton({
										text: _translationMap['Edit']
										,id: 'acctTypeEdit'	
										,width: 35
										,handler: function(){_controller.editValidAcctType()}														
									})
								]
							}
							//CRS change this text field as checkbox
							,{
								xtype: 'compositefield'	
								,itemId: 'acctDesignation'	
								,labelStyle: 'white-space:nowrap'									
								,fieldLabel: _translationMap['acctDesignation']
								,width: 300
								,style: 'padding-left:40px'
								,items: [													
									_fields['validAcctDesignation'],
									new DesktopWeb.Controls.ActionButton({
										text: _translationMap['Edit']
										,id: 'acctDesignateEdit'	
										,width: 35
										,handler: function(){_controller.editValidAcctDesignation()}														
									})
								]
							}
							,{
								layout: 'form'
								,defaults: {border:false}
								,items: [
										new DesktopWeb.Controls.SMVComboBox({
										itemId: 'actionCode'
										,width: 150
										,fieldLabel: _translationMap['actionCode']
										,allowBlank: true
										})
								]
							}
							,{
								layout: 'form'
								,defaults: {border:false}
								,items: [
										new DesktopWeb.Controls.SMVComboBox({
										itemId: 'regModel'
										,width: 150
										,editable: false
										,fieldLabel: _translationMap['ModelCode']
										,allowBlank: true
										})
								]
							}
						]	
					}
					,{
						layout: 'form'						
						,defaults: {border:false}
						,style: 'padding-left:6px'
						,items: _selectors['docListSelector']
					}
				]		
				,buttons: [
					new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['OK']
							,handler: function(){								
								if (_popups['regulatoryStandardsPopup'].isValid())								
								{
									 _controller.savePopup(_popups['regulatoryStandardsPopup'].action, _popups['regulatoryStandardsPopup'].getData());
								}
							}
						}
					)
					,new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['Cancel']
							,style: 'margin-right: 200px'
							,handler: function(){
								_popups['regulatoryStandardsPopup'].hide();
							}
						}
					)
				]
			,init: function()
			{										
				this.get(0).hide(); //hide delete message
				
				switch(this.action)
				{
					case _controller.ADD:
					{
						this.setTitle(_translationMap['regulatoryStandard'] + ' - ' + _translationMap['Add']);
						this.disableAllFields();
						_controller.selectorGridClearData();	
						this.getField('regulationRule').enableField();
						Ext.getCmp('taxTypesEdit').disable();
						Ext.getCmp('acctTypeEdit').disable();
						Ext.getCmp('acctDesignateEdit').disable();
						_controller.docListSelectorPopulation();												
						this.getField('regulationRule').focus();
						_controller.showHideCDOTFields('');	
						this.getField('effectiveDate').enable();
						//setup CRS Report Regulatory defaults
						_controller.setReportableJurisFields('', _controller.ADD);
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['regulatoryStandard'] + ' - ' + _translationMap['Modify']);
						this.enableAllFields();
						_controller.selectorGridClearData();
						Ext.getCmp('taxTypesEdit').enable();
						Ext.getCmp('acctTypeEdit').enable();
						Ext.getCmp('acctDesignateEdit').enable();
						_controller.docListSelectorPopulation();						
						this.populateWithSelectedRecord();
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['regulatoryStandard'] + ' - ' + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();
						_controller.selectorGridClearData();
						Ext.getCmp('taxTypesEdit').disable();
						Ext.getCmp('acctTypeEdit').disable();
						Ext.getCmp('acctDesignateEdit').disable();
						this.populateWithSelectedRecord();
						break;
					}
				}														
			}	
			,listeners: {
				'show': {
					fn: function(){
						this.init();	
						if(this.action != _controller.MOD)
							_selectors['docListSelector'].availableGrid.disable();
						else{	
							var rec = _grids['regStdInfo'].getSelectedRecord();	
							if(this.action == _controller.MOD){
								_selectors['docListSelector'].availableGrid.enable();
								if(rec.data['regRule'] == 'CC' || rec.data['regRule'] == _controller.REGULATIONCODECRSRP)
									_selectors['docListSelector'].availableGrid.disable();
							}
						}
						
					}
				}
			}	
			,isValidJurisdiction: function() {
				var popup = _popups['regulatoryStandardsPopup'];

				// Validate all input fields before business checking
				var valid = popup.getField('regulationRule').isValid();
				valid = popup.getField('regulatoryCode').isValid() && valid;
				if(popup.getField('country').getValue() == '') {
					popup.getField('country').markInvalid(_translationMap['FldRequired']);
					return false;
				}
				return valid;
			}
			,populateWithSelectedRecord: function()
			{

				var rec = _grids['regStdInfo'].getSelectedRecord();

				if(this.action == _controller.MOD){
					this.getField('regulationRule').disableField();
					this.getField('regulatoryCode').disableField();
					if(rec.data['regRule'] == 'CC'){												
						this.getField('investorType').disableField();
						this.getField('investOnBehalfOfTP').disableField();						
					}
					if(rec.data['regRule'] != 'FT' || rec.data['regRule'] != 'FA'){
						_controller.updateFatcaFields(rec.data['regRule']);
					}
					_controller.updateAcctRegistFields(rec.data['regRule']);	
					_controller.updateAcctDesignationFields(rec.data['regRule']);	
				} 
				
				this.getField('regulationRule').setValue(rec.data['regRule']);
				this.getField('regulatoryCode').setValue(rec.data['complyCode']);
				_controller.showHideCDOTFields(rec.data['regRule']);	
				//disable Effective Date when the rule's filling is done
				if(this.action == _controller.MOD) {
					if (rec.data['inActDeff'] == _controller.YES) {
						this.getField('effectiveDate').disable();
					} else {
						this.getField('effectiveDate').enable();
					}
				}

				//CDOT FATCA
				regulationIndex = _controller.getRecordIndex('fatcaRegulation', rec.data['fatcaCode']);
				if (regulationIndex < 0) {
					this.getField('fatcaRegulation').setValue('');
				}else {
					var selectedFatcacode = this.getField('fatcaRegulation').getStore().getAt(regulationIndex).get('code');
					this.getField('fatcaRegulation').setValue(selectedFatcacode);
					_controller.setCryList(selectedFatcacode);
					this.getField('reportToCountry').setValue(rec.data['rptToCntry']);
				}
				
				countryIndex =_controller.getRecordIndex('country', rec.data['countryCode']);
				if(countryIndex<0){this.getField('country').setValue('');
				}else{
					this.getField('country').setValue(this.getField('country').getStore().getAt(countryIndex).get('code'));
				}
				provinceIndex = _controller.getRecordIndex('province', rec.data['provinceCode']);
				if(provinceIndex<0){this.getField('province').setValue('');
				}else{
				if(rec.data['provinceDesc'] != ''){	
					this.getField('province').setValue(this.getField('province').getStore().getAt(provinceIndex).get('code'));
				}
				else{
					this.getField('province').setValue(rec.data['provinceDesc'])
				}
				}	

				this.getField('description').setValue(rec.data['description']);
				this.getField('effectiveDate').setValue(rec.data['effDate']);
				
				investorTypeIndex = _controller.getRecordIndex('investorType', rec.data['investorType']);
				if(investorTypeIndex<0){this.getField('investorType').setValue('');
				}else{
				if(rec.data['investorTypeDesc'] != ''){
					this.getField('investorType').setValue(this.getField('investorType').getStore().getAt(investorTypeIndex).get('code'));
				}
				else{				
					this.getField('investorType').setValue(rec.data['investorTypeDesc']);
				}
				}
				this.getField('lowerBound').setValue(rec.data['lowerBound']);
				this.getField('upperBound').setValue(rec.data['upperBound']);
				this.getField('fundCategory').setValue(rec.data['fundCategory']);
				this.getField('stopDate').setValue(rec.data['stopDate']);
				this.getField('investOnBehalfOfTP').setValue(rec.data['investFor3rdParty']);			
				_fields['validTaxTypes'].setValue(_controller.taxTypesCode());
				this.getField('actionCode').setValue(rec.data['actCodeDesc']);
				_fields['validAcctType'].setValue(_controller.acctTypeCode());
				//set Account Designation
				this.getField('acctDesignation').setValue(rec.data['acctDesignation']);
				_fields['validAcctDesignation'].setValue(_controller.acctDesignCode());
				//set CRS Report field value
				if(rec.data['rptJuris'] == null) {
					this.getField('reportableJuris').setValue('');
				} else {
					this.getField('reportableJuris').setValue(rec.data['rptJuris']);
				}

				this.getField('regModel').setValue(rec.data['regModel']);
				_controller.populateDocList();	
				_controller.setReportableJurisFields(rec.data['regRule'], this.action);					
			}
			
			,getData: function()
			{	
				var data = {};				
				data['runMode'] = this.action;
				data['countryCode'] = this.getField('country').getValue();
				data['countryDesc'] = this.getField('country').getValueDesc();
				data['provinceCode'] = this.getField('province').getValue();
				data['provinceDesc'] = this.getField('province').getValueDesc();
				data['regRule'] = this.getField('regulationRule').getValue();
				data['regRuleDesc'] = this.getField('regulationRule').getValueDesc();
				data['complyCode'] = this.getField('regulatoryCode').getValue();
				data['description'] = this.getField('description').getValue();
				data['rptJuris'] = this.getField('reportableJuris').getValue();
				
				//CDOT FATCA
				data['fatcaRegulation'] = this.getField('fatcaRegulation').getValue();
				var regRule = this.getField('regulationRule').getValue();
				if(regRule == _controller.REGULATIONCODECRSRP) {
					data['reportToCountry'] = '';//ignore 'reportToCountry' for CRSRP
				} else {
					data['reportToCountry'] = this.getField('reportToCountry').getValue();
				}
				
				data['investorType'] = this.getField('investorType').getValue();
				data['lowerBound'] = this.getField('lowerBound').getValue();
				data['upperBound'] = this.getField('upperBound').getValue();
				data['fundCategory'] = this.getField('fundCategory').getValue();
				data['investorTypeDesc'] = this.getField('investorType').getValueDesc();
				data['investFor3rdParty'] = this.getField('investOnBehalfOfTP').getValue();
				data['effDate'] = this.getField('effectiveDate').getDisplayDateString();
				data['stopDate'] = this.getField('stopDate').getDisplayDateString();
				data['TaxTypes'] = _fields['validTaxTypes'].getValue();
				data['AccountType'] = _fields['validAcctType'].getValue();
				data['AcctDesignation'] = _fields['validAcctDesignation'].getValue();
				data['actionCode'] = this.getField('actionCode').getValue();
				data['regModel'] = this.getField('regModel').getValue();
				data['regModelDesc'] = this.getField('regModel').getValueDesc();
				data['docList'] = _selectors['docListSelector'].getSelectedRecords();
				return data;
			}
		})
		
		//CRS Tax Jurisdictions popup layout
		,crsReportPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: _layoutWidth - 160
			,height: _layoutHeight - 330
			,modal: true
			,autoHeight: true
			,title: _translationMap['reportableJurisdisctions']
			,defaults: {border:false}
			,rangeStartForNext: 1
			,moreRecordsExist: _controller.NO
			,jurisUpdateFlag: false
			,searchedFlag: false
			,discardFlag: false
			,isError: false
			,items: [{											
				layout: 'form'	
				,style: 'padding:5px'
				,items: [
					new DesktopWeb.Controls.TextField({
						itemId: 'crsCountry'
						,fieldLabel: _translationMap['country']
						,disabled: true
						,width: 250
					}) 
					,{
						layout: 'column'
						,border: false,
							defaults: {border: false}
						,items: [{
								columnWidth: 0.8
								,defaults: {border:false}
								,items: [{
									layout: 'form'
									,items: [
										new DesktopWeb.Controls.SMVComboBox({
											itemId: 'taxJurisdictions'	
											,width: 250
											,fieldLabel: _translationMap['taxJurisdictions']
											,allowBlank: false
										})
									]}
								]
							}
							,{
								columnWidth: 0.2
								,items: [
										new DesktopWeb.Controls.ActionButton({
										text: _translationMap['Search']
										,handler: function() {
											_controller.clickHandle_searchTaxJurisBtn('reload', false);
										}
									})
								]
							}
						]
					}
					,_grids['taxJurisGrid']
				]}
			]		
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function() {
						_controller.updatedCRSJurisGridRecords();
						_popups['crsReportPopup'].discardFlag = false;
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function() {
						if (_popups['crsReportPopup'].discardFlag){
							DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
						} else {
							cancelScreen(true);
						}
						function cancelScreen(confirm){
							if (confirm) {
								_popups['crsReportPopup'].hide();
								_popups['crsReportPopup'].discardFlag = false;
								if (_popups['crsReportPopup'].isError) {
									_popups['crsReportPopup'].jurisUpdateFlag = false;
									_popups['crsReportPopup'].isError = false;
								}
							}
						}
					}
				})
			]
			,init: function(action)	{									
				// initialize popup based on action
				var popup = _popups['crsReportPopup'];
				popup.action = action;
				popup.getField('taxJurisdictions').clearInvalid();
			}
			,populate: function() {
				var popup = _popups['crsReportPopup'];
				popup.getField('crsCountry').setValue(_popups['regulatoryStandardsPopup'].getField('country').getValueDesc());
				
				if(!popup.jurisUpdateFlag && !popup.searchedFlag) {
					popup.getField('taxJurisdictions').setValue(popup.getField('taxJurisdictions').getStore().getAt(0).get('code'));
				}
			}												
		})
		//CRS popUp by adding/Modify Tax Jurisdictions
		,crsJurisPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,itemId: 'crsReportPopup'
			,width: 495
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
			,defaults: {border:false}
			,items: [{
					layout: 'form'																		
					,style: 'padding:10px'
					,defaults: {border: true}
					,labelWidth: 120
					,items: [ 
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'jurisdictions'
							,fieldLabel: _translationMap['jurisdictions']
							,width: 250
							,editable: true
							,allowBlank: false
							,listeners:{
								select : function(fld, rec, index){
									_popups['crsJurisPopup'].getField('startDate').clearInvalid();
									_popups['crsJurisPopup'].getField('endDate').clearInvalid();
								}
							}
						})
						,new DesktopWeb.Controls.DateField({	
							itemId: 'startDate'
							,fieldLabel: _translationMap['startDate']
							,width: 150
							,allowBlank: false
							,format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						}) 
						,new DesktopWeb.Controls.DateField({	
							itemId: 'endDate'
							,fieldLabel: _translationMap['StopDate']
							,width: 150
							,allowBlank: false
							,format : DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						}) 
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['crsJurisPopup'].isValid()){
							_controller.validateCRSJurisPopUp(_popups['crsJurisPopup'].getData(), _popups['crsJurisPopup'].action);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['crsJurisPopup'].hide();}
				})
			]
			,init: function(action) {
				// initialize popup based on action
				var popup = _popups['crsJurisPopup'];
				popup.action = action;
				_controller.setDefaultReportableJurisDates();
				
				switch(action) {
					case _controller.ADD:{
						popup.setTitle(_translationMap['reportableJurisdisction'] + ' - ' + _translationMap['Add']); 
						popup.populate(action);
						break;
					}
					case _controller.MOD:{
						popup.setTitle(_translationMap['reportableJurisdisction'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						break;
					}
				}
			}
			,populate: function(action) {
				var popup = _popups['crsJurisPopup'];

				popup.enableAllFields();
				popup.getField('jurisdictions').clearField();
				
				switch(action) {
					case _controller.ADD:{
						popup.uuid = _controller.getNewCRSJurisUUID();	
						this.setTitle(_translationMap['reportableJurisdisction'] + ' - ' + _translationMap['Add']);	
						break;
					}
					case _controller.MOD: {
						var selectedCRSJuris = _grids['taxJurisGrid'].getSelectedRecord();
						popup.uuid = selectedCRSJuris.data['complyRptJurisUUID'];

						popup.getField('jurisdictions').setValue(selectedCRSJuris.data['cntryCode']);
						popup.getField('startDate').setValue(selectedCRSJuris.data['startDate']);
						popup.getField('endDate').setValue(selectedCRSJuris.data['endDate']);
						popup.getField('jurisdictions').disableField();
						popup.getField('startDate').disableField();
						
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function() {
				var popup = _popups['crsJurisPopup']; 

				var valid = popup.getField('jurisdictions').isValid();
				valid = popup.getField('startDate').isValid() && valid;
				valid = popup.getField('endDate').isValid() && valid;
				
				//validate duplication in memeory
				if (popup.action == _controller.ADD) {
					var  crsJurisInvalid = false;
					var nDupRecord = _grids['taxJurisGrid'].getStore().queryBy(function(record){
						var newPopupSD = DesktopWeb.Util.stringToDate(popup.getField('startDate').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
						var newPopupED = DesktopWeb.Util.stringToDate(popup.getField('endDate').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
						var gridRecSD = DesktopWeb.Util.stringToDate(record.get('startDate'), DesktopWeb.Util.getDateDisplayFormat());
						var gridRecED =DesktopWeb.Util.stringToDate(record.get('endDate'), DesktopWeb.Util.getDateDisplayFormat());
						//check overlapping country/StartDate/StopDate
						return (record.get('cntryCode') == popup.getField('jurisdictions').getValue()
						     && !(newPopupSD >= gridRecED || newPopupED <= gridRecSD))
					});

					if (nDupRecord.length > 0 ) {
						popup.getField('jurisdictions').markInvalid(_translationMap['ERR_DUPLICATED_CRSJURISDICTION']);
						popup.getField('startDate').markInvalid(_translationMap['OVERLAPPINGDATESERROR']);
						crsJurisInvalid = true;
					}
					if (crsJurisInvalid) {
						return false;
					}
				}
				return valid;
			}
			,getData: function() {
				var popup = _popups['crsJurisPopup'];
				var data = {};
				data['complyRptJurisUUID'] = popup.uuid;
				data['cntryCode'] = popup.getField('jurisdictions').getValue();
				data['countryDesc'] = popup.getField('jurisdictions').getValueDesc();
				data['startDate'] = popup.getField('startDate').getDisplayDateString();
				data['endDate'] = popup.getField('endDate').getDisplayDateString();
				data['runMode'] = popup.action;

				return data;
			}
		})		
		//Tax Types popup
		,validTaxTypesPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 520
			,modal: true
			,title: _translationMap['ValidTaxTypes']+ ' - '  +_translationMap['Edit']
			,defaults: {border:false, style: 'padding: 4px;'}
			,taxTypesCheckboxes: {}				
			,items: [									
				{						
					layout: 'form'
					,labelWidth: 110
											
					,items: [
						new DesktopWeb.Controls.ComboBox({
							itemId: 'inclExclTaxType'			
							,width: 110
							,fieldLabel: _translationMap['Chooseoptionsto']
							,allowBlank: false
							,store: new Ext.data.ArrayStore({
				        		id: 0,
				        		fields: [
				            		'myId',
				            		'displayText'
				        		],
				        	data: [['include', _translationMap['Include']], ['exclude', _translationMap['Exclude']]]
				    		})				
				    		,valueField: 'myId'
				    		,displayField: 'displayText'
						})
					]				
				}

				,{						
					layout: 'column'
					,defaults: {
						layout: 'auto'
						,columnWidth: 0.33
						,border: false						
					}						
					,items: [
						{id: 'taxTypesList_0'}
						,{id: 'taxTypesList_1'}
						,{id: 'taxTypesList_2'}
					]				
				}				
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['OK']
						,handler: function(){
							_controller.updateValidTaxTypes()							
							_popups['validTaxTypesPopup'].hide();
						}	
					}
				)
				,new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['Cancel']
						,handler: function(){_popups['validTaxTypesPopup'].hide();}
					}
				)
			]
			,init: function(taxTypesListXML)			
			{										
				var taxTypeNodes = IFDS.Xml.getNodes(taxTypesListXML, 'Element');		
				this.getField("inclExclTaxType").setValue('exclude');
				
				for (var i = 0; i < taxTypeNodes.length; i++)
				{					
					this.taxTypesCheckboxes[IFDS.Xml.getNodeValue(taxTypeNodes[i], 'code')] = new DesktopWeb.Controls.Checkbox({						
						boxLabel: IFDS.Xml.getNodeValue(taxTypeNodes[i], 'value')
					});
					Ext.getCmp('taxTypesList_' + (i - 0) % 3).add(this.taxTypesCheckboxes[IFDS.Xml.getNodeValue(taxTypeNodes[i], 'code')]);
				}														
			}
			,populate: function()
			{
				var selectedTaxTypes = _fields['validTaxTypes'].getValue();
				if(selectedTaxTypes.indexOf(_translationMap['All'])=='0'){
					this.getField("inclExclTaxType").setValue('exclude');	
				}
				else{
					this.getField("inclExclTaxType").setValue('include');		
				}
				for (var i in this.taxTypesCheckboxes)
				{																							
					if(selectedTaxTypes.split(',').length > 1){
						var selectedTaxTypesArray = selectedTaxTypes.split(',');
						this.taxTypesCheckboxes[i].setValue(false);
						for (var k=0; k<selectedTaxTypesArray.length; k++) {
							if (selectedTaxTypesArray[k].replace("!","") == i) {	
								this.taxTypesCheckboxes[i].setValue(true);
							}
						}
					}
					else {
						this.taxTypesCheckboxes[i].setValue(selectedTaxTypes == i)
					}
				}
			}
			,getData: function()
			{
				var selectedTaxTypes = "";								
				if (this.getField("inclExclTaxType").getValue() == "include"){

					for (var i in this.taxTypesCheckboxes)
					{
						if (this.taxTypesCheckboxes[i].getValue())
						{
							if (selectedTaxTypes.length > 0)
							{
									selectedTaxTypes += ","
							}
							selectedTaxTypes += i;
						}					 
					}
				}
				else{
					selectedTaxTypes= _translationMap['All'];
					for (var i in this.taxTypesCheckboxes)
					{

						if (this.taxTypesCheckboxes[i].getValue())
						{
							if (selectedTaxTypes.length > 0)
							{
									selectedTaxTypes += ","
							}
							selectedTaxTypes += '!'+i;
						}					 
					}
				}
				return selectedTaxTypes;
			}														
		})

		,validAcctTypePopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 520
			,modal: true
			,title: _translationMap['ValidAcctType']+ ' - '  +_translationMap['Edit']
			,defaults: {border:false, style: 'padding: 4px;'}
			,acctTypeCheckboxes: {}				
			,items: [

				{
					layout: 'form'					
					,labelWidth: 110																						
					,items: [
						new DesktopWeb.Controls.ComboBox({
							itemId: 'inclExclAcctType'			
							,width: 110
							,fieldLabel: _translationMap['Chooseoptionsto']
							,allowBlank: false
							,store: new Ext.data.ArrayStore({
				        		id: 0,
				        		fields: [
				            		'myId',
				            		'displayText'
				        		],
				        	data: [['include', _translationMap['Include']], ['exclude', _translationMap['Exclude']]]
				    		})				
				    		,valueField: 'myId'
				    		,displayField: 'displayText'
						})				

					]

				}

				,{						
					layout: 'column'
					,defaults: {
						layout: 'auto'
						,columnWidth: 0.33
						,border: false						
					}						
					,items: [
						{id: 'acctTypeList_0'}
						,{id: 'acctTypeList_1'}
						,{id: 'acctTypeList_2'}
					]				
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['OK']
						,handler: function(){
							_controller.updateValidAcctType()							
							_popups['validAcctTypePopup'].hide();
						}	
					}
				)
				,new DesktopWeb.Controls.ActionButton(
					{
						text: _translationMap['Cancel']
						,handler: function(){_popups['validAcctTypePopup'].hide();}
					}
				)
			]
			,init: function(acctTypeListXML)			
			{										
				var acctTypeNodes = IFDS.Xml.getNodes(acctTypeListXML, 'Element');
				this.getField("inclExclAcctType").setValue('exclude');
				

				for (var i = 0; i < acctTypeNodes.length; i++)
				{	
					this.acctTypeCheckboxes[IFDS.Xml.getNodeValue(acctTypeNodes[i], 'code')] = new DesktopWeb.Controls.Checkbox({
						boxLabel: IFDS.Xml.getNodeValue(acctTypeNodes[i], 'value')
					});
					Ext.getCmp('acctTypeList_' + (i - 0) % 3).add(this.acctTypeCheckboxes[IFDS.Xml.getNodeValue(acctTypeNodes[i], 'code')]);
				}														
			}
			,populate: function()
			{
				var selectedAcctType = _fields['validAcctType'].getValue();
				if(selectedAcctType.indexOf(_translationMap['All'])=='0'){
					this.getField("inclExclAcctType").setValue('exclude');	
				}
				else{
					this.getField("inclExclAcctType").setValue('include');		
				}
				for (var i in this.acctTypeCheckboxes)
				{																			
					if(selectedAcctType.split(',').length > 1)
						this.acctTypeCheckboxes[i].setValue(selectedAcctType.indexOf(i) != -1)
					else
						this.acctTypeCheckboxes[i].setValue(selectedAcctType == i)
				}
			}
			,getData: function()
			{
				var selectedAcctType = "";
				if (this.getField("inclExclAcctType").getValue() == "include"){

					for (var i in this.acctTypeCheckboxes)
					{
						if (this.acctTypeCheckboxes[i].getValue())
						{
							if (selectedAcctType.length > 0)
							{
									selectedAcctType += ","
							}
							selectedAcctType += i;
						}					 
					}
				}
				else{
					selectedAcctType = _translationMap['All'];
					for (var i in this.acctTypeCheckboxes)
					{

						if (this.acctTypeCheckboxes[i].getValue())
						{
							if (selectedAcctType.length > 0)
							{
									selectedAcctType += ","
							}
							selectedAcctType += '!'+i;
						}					 
					}
				}
				return selectedAcctType;
			}														
		})
		//Make account designation as a checkbox popup
		,validAcctDesignationPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 520
			,modal: true
			,title: _translationMap['acctDesignation']+ ' - '  +_translationMap['Edit']
			,defaults: {border:false, style: 'padding: 4px;'}
			,acctDesigntionCheckboxes: {}				
			,items: [{
					layout: 'form'					
					,labelWidth: 110																						
					,items: [
						new DesktopWeb.Controls.ComboBox({
							itemId: 'inclExclAcctDesignation'			
							,width: 110
							,fieldLabel: _translationMap['Chooseoptionsto']
							,allowBlank: false
							,store: new Ext.data.ArrayStore({
				        		id: 0,
				        		fields: [
				            		'myId',
				            		'displayText'
				        		],
								data: [['include', _translationMap['Include']], ['exclude', _translationMap['Exclude']]]
				    		})				
				    		,valueField: 'myId'
				    		,displayField: 'displayText'
						})		
					]
				}
				,{						
					layout: 'column'
					,defaults: {
						layout: 'auto'
						,columnWidth: 0.20
						,border: false						
					}						
					,items: [
						{id: 'acctDesignationList_0'}
						,{id: 'acctDesignationList_1'}
						,{id: 'acctDesignationList_2'}
					]				
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function() {
						_controller.updateValidAcctDesignation();						
						_popups['validAcctDesignationPopup'].hide();
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['validAcctDesignationPopup'].hide();}
				})
			]
			,init: function(acctDesignationListXML)	{											
				var acctDesignationNodes = IFDS.Xml.getNodes(acctDesignationListXML, 'Element');
				this.getField("inclExclAcctDesignation").setValue('exclude');
			
				for (var i = 0; i < acctDesignationNodes.length; i++) {
					this.acctDesigntionCheckboxes[IFDS.Xml.getNodeValue(acctDesignationNodes[i], 'code')] = new DesktopWeb.Controls.Checkbox({
						boxLabel: IFDS.Xml.getNodeValue(acctDesignationNodes[i], 'value')
					});
					Ext.getCmp('acctDesignationList_' + (i - 0) % 3).add(this.acctDesigntionCheckboxes[IFDS.Xml.getNodeValue(acctDesignationNodes[i], 'code')]);
				}														
			}
			,populate: function() {
				var selectedAcctDesignation = _fields['validAcctDesignation'].getValue();
				if (selectedAcctDesignation.indexOf(_translationMap['All'])=='0') {
					this.getField("inclExclAcctDesignation").setValue('exclude');	
				} else {
					this.getField("inclExclAcctDesignation").setValue('include');		
				}
				for (var i in this.acctDesigntionCheckboxes) {																
					if(selectedAcctDesignation.split(',').length > 1) {
						this.acctDesigntionCheckboxes[i].setValue(selectedAcctDesignation.indexOf(i) != -1)
					} else {
						this.acctDesigntionCheckboxes[i].setValue(selectedAcctDesignation == i)
					}
				}
			}
			,getData: function() {
				var selectedAcctDesignation = "";
				if (this.getField("inclExclAcctDesignation").getValue() == "include") {
					for (var i in this.acctDesigntionCheckboxes) {
						if (this.acctDesigntionCheckboxes[i].getValue()) {
							if (selectedAcctDesignation.length > 0) {
								selectedAcctDesignation += ","
							}
							selectedAcctDesignation += i;
						}					 
					}
				} else {
					selectedAcctDesignation = _translationMap['All'];
					for (var i in this.acctDesigntionCheckboxes) {
						if (this.acctDesigntionCheckboxes[i].getValue()) {
							if (selectedAcctDesignation.length > 0) {
								selectedAcctDesignation += ","
							}
							selectedAcctDesignation += '!'+i;
						}					 
					}
				}
				return selectedAcctDesignation;
			}														
		})
	} 		 
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		
		,layoutHeight: _layoutHeight
		
		,fields: _fields

		,expander: _expander
	
		,grids: _grids
		
		,selectors: _selectors
		
		,popups: _popups
		
		,buttons: _buttons
	
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					{
						layout: 'form'
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 100}	
						,items: [
							{
								layout: 'column'
								, items: [
									{
										width: 300
										,layout: 'form'										
										,items: [_fields['regulationRule']]								
									}
									, {
										width: 300
										, layout: 'form'										
										,items: [_fields['countryFilter']]
									}	
								]
							}
							, {
								layout: 'column'
								, items: [
									{
										width: 330
										,layout: 'form'										
										,items: [_fields['status']]								
									}	
									, {
										width: 100
										,layout: 'form'
										,items: [_buttons['search']]				
									}									
								]
							}
						]
					}
					,{
						items: [_grids['regStdInfo']]
					}				
				]																				
			}
		)//Filter section end
	
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}