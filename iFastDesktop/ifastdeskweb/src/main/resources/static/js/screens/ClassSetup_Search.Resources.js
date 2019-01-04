/*********************************************************************************************
 * @file	ClassSetup_Search.Resources.js	
 * @author	Rod Walker
 * @desc	Resources file for Search screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05-Mar-2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *          - Add ability to display French
 *          
 *  14-Nov-2017 Sreejith A P0266789-1615
 *  		- Search by APIR and APIR column in class results 
 *  
 *  1 Feb 2018	Sreejith.A P0274726 P0274726-49
 *			- Added new Popup for remarks setup
 * 
 *   2 Mar 2018	Sreejith.A P0274726 P0274726-88
 *			- Tuning and consolidating remarks section
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750;
	
	// **** buttons ****
	var _buttons = {
		lookup: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['LookupClasses']
			,handler: function(){
				_controller.doLookup();
			}
			,style: "position:absolute; right:45px; top:0px;"
			,disabled: true
		})
	}
	
	
	
	// **** fields ****
	var _fields = {		
		fund: new DesktopWeb.Controls.SuggestField({
			fieldLabel: _translationMap['Fund']					
			,smartview: 'fundOnlySearch'				
			,fields: ['fndDisp', 'fundCode', 'fundCategory', 'sponsor', 'fundName', 'IWTDomiciledFund', 'IWTEnabled', 'fundERISAOptn', 'fundERISACalcLevel']
			,valueField: 'fundCode'
			,displayField: 'fndDisp'								
			,width: 550
			,emptyText: _translationMap['emptyTextSearch']
			,listeners: {
				populated: function()
				{											
					_buttons['lookup'].enable();
					_controller.updateActionButtons();														
				}
				,cleared: function()
				{
					_buttons['lookup'].disable();
					_controller.updateActionButtons();														
				}				
			}																										
		})	
	}
	// **** grids ****
	var _grids = {
		classes: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth
				,style: "margin-top:30px"
				,autoScroll: true							
				,height: 550
				,autoExpandColumn: 'classCode'						
				,store: new Ext.data.XmlStore(
					{
						record: 'ClassInfo'					
						,fields: ['classCode', 'dateEff', 'extFundId', 'cusip', 'isin', 'wkn','apir', 'fundLoadGrp']
						,listeners: {
							load: function(store, records)
							{
								Ext.each(records, function(record){
									record.data.dateEff = DesktopWeb.Util.getDateDisplayValue(record.data.dateEff);
								});

								store.fireEvent('datachanged', store); //to set data in grid again
								
							}
						}
					}
				)
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
						{header: _translationMap['Class'], id:'classCode', dataIndex: 'classCode'}
						,{header: _translationMap['EffectiveDate'], dataIndex: 'dateEff', width:100}
						,{header: _translationMap['ISIN'], dataIndex: 'isin', width:80}																				
						,{header: _translationMap['CUSIP'], dataIndex: 'cusip', width:90}
						,{header: _translationMap['WKNFundId'], dataIndex: 'wkn', width:90}
						,{header: _translationMap['APIR'], dataIndex: 'apir', width:90}
						,{header: _translationMap['ExternalFundId'], dataIndex: 'extFundId', width:120}
						,{header: _translationMap['FundLoadGroup'], dataIndex: 'fundLoadGrp', width:100}
					]		
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'addBtn'								
							,text: _translationMap['AddClass']
							,disabled: true
							,handler: function()
							{
								_controller.addClass();
							}															
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'viewBtn'								
							,text: _translationMap['ViewClassDetails']
							,disabled: true
							,handler: function()
							{
								_controller.viewClassDetails();
							}														
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'limitOvrdBtn'								
							,text: _translationMap['LimitationOverride']
							,disabled: true
							,handler: function()
							{
								_controller.limitationOverride();
							}														
						}
					)
					,new DesktopWeb.Controls.ActionButton(		
							{
								itemId: 'remarksBtn'								
								,text: _translationMap['Remarks']
								,disabled: true
								,handler: function()
								{	
									_popups['RemarksMainPopup'].setTitle(_translationMap['Remarks'] + ' - ' 
											+ _translationMap['Fund'] + ': ' + _fields['fund'].getValue() + ', '
											+ _translationMap['Class'] + ': ' + _grids['classes'].getSelectedRecord().data['classCode']);
									_controller.loadFundClsRemarks();
									_popups['RemarksMainPopup'].show();
									
								}														
							}
						)
				]
				,listeners: {
					rowdblclick: function(){_controller.viewClassDetails()}
					,keypress: function(e){
						if (e.getKey() == 13 && _grids['classes'].getSelectionModel().getSelected() != null)
						{
							_controller.viewClassDetails()
						}						
					}
				}			
			}
		)
		,grdRemarks: new DesktopWeb.AdvancedControls.GridPanel({
			style: "margin-top:15px;margin-bottom:15px;"
			,autoScroll: true
			,height: 250
			,store: new Ext.data.XmlStore({
				record: 'Remark'
				,fields: ['errMsg','fundDetlRemarksUUID','remarkTyp','reason','remarks','effDate','runMode','userName','processedDate','modUser','modDate']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.effDate = DesktopWeb.Util.getDateDisplayValue(record.data.effDate);
						});
						store.fireEvent('datachanged', store); //to set data in grid again
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL}
						);
					}
					,update: function(store, records) {
						store.filterBy(function(record){
						return record.data.runMode != _controller.DEL});
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
						menuDisabled: true
				}
				,columns: [
					{
						id: 'errMsg'
						,width: 25
						,renderer: function(val){
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}
					,{
						header: _translationMap['RemarkType'],
						dataIndex: 'remarkTyp',
						width: 125,
						renderer: function(val){
							return (_controller.getDisplay('RemarksTypeList', val));
						}
					}
					,{
						header: _translationMap['Reason'],
						dataIndex: 'reason',
						width:125,
						renderer: function(val){
							return (_controller.getDisplay('ReasonList', val));
						}
					}
					,{header: _translationMap['Remarks'], dataIndex: 'remarks', width:250}
					,{header: _translationMap['EffectiveDate'], dataIndex: 'effDate', width:80}
				]
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.updateGridBtns(record);
						}
					}
				}
			})
			,buttons: [	
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Add']
					,itemId: 'addBtn'
					,handler: function() {
						_controller.openRemarkPopup(_controller.ADD);
					}
				})		
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Modify']
					,itemId: 'modBtn'
					,disabled: true
					,handler: function() {
						_controller.openRemarkPopup(_controller.MOD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Delete']
					,itemId: 'delBtn'
					,disabled: true
					,handler: function() {
						_controller.openRemarkPopup(_controller.DEL);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Historical']
					,itemId: 'hisBtn'
					,disabled: true
					,handler: function() {
						_controller.openHistoryPopup();
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Admin']
					,itemId: 'adminBtn'
					,disabled: true
					,handler: function() {
						_controller.openAdminPopup();
					}
				})
			 ]
		})
	}
	
    // **** popups ****
	var _popups = {
		//Main popup to show remarks grid
		RemarksMainPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 640
			,closeAction: 'hide'					
			,modal: true
			,defaults: {border:false}
			,title : _translationMap['Remarks']
			,items: [
				_grids['grdRemarks']
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function() {
						_controller.doCommitValidate();
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function() {_popups['RemarksMainPopup'].hide();}
				})
			]
		})
		//Popup to Add/Modify/Delete remarks
		,RemarkModifyPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 440
			,closeAction: 'hide'					
			,modal: true
			,defaults: {border:false}
			,title : _translationMap['Remarks']
			,items: [{
						html: _translationMap['DeleteConfirmMsg']
						,style: 'text-align:center;font-weight:bold; font-size:12px; padding:4px'
						,hidden:true
					}
					,{
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 120
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							fieldLabel: _translationMap['RemarkType']
						    ,itemId: 'remarkType'
							,allowBlank: false
							,editable: true
							,width: 270
						})
						,new DesktopWeb.Controls.SMVComboBox({
							fieldLabel: _translationMap['Reason']
						    ,itemId: 'reason'
						    ,editable: true
						    ,width: 270
						    ,listeners: {
						    	select: function(fld, record, index) {
						    		 _popups['RemarkModifyPopup'].getField('remarks').clearInvalid();
								}
							}
						})
						,new Ext.form.TextArea({
							fieldLabel: _translationMap['Remarks']
							,itemId: 'remarks'	
							,autoScroll: true
							,width: 270
							,height: 55
							,maxLength: 100	
							,listeners: {
								change: function(fld, newVal) {
									 _popups['RemarkModifyPopup'].getField('reason').clearInvalid();
								}
							}
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'effectiveDate'
							,fieldLabel: _translationMap['EffectiveDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
					]						
			}]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function() {
						if (_popups['RemarkModifyPopup'].isValid()) {
							_controller.validateRemarkPopUp(_popups['RemarkModifyPopup'].action, _popups['RemarkModifyPopup'].getData());
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function() {_popups['RemarkModifyPopup'].hide();}
				})
			]
			,init: function(action) {						
			    var popup = _popups['RemarkModifyPopup'];
				this.action = action;	
				popup.get(0).hide();
				
				switch(action) {
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['Remarks'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.getField('effectiveDate').setValue(_controller.getDefaultEffDate());
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['Remarks'] + ' - ' + _translationMap['Modify']);
						popup.populate();
						popup.getField('remarkType').disableField();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['Remarks'] + ' - ' + _translationMap['Delete']);
						popup.get(0).show();
						popup.populate();
						popup.disableAllFields();
					}
				}	
			}
			,getData: function() {
				popup =  _popups['RemarkModifyPopup'];
				var data = {};
				data['remarkTyp'] = popup.getField('remarkType').getValue();
				data['fundDetlRemarksUUID'] = popup.uuid;
				data['reason'] = popup.getField('reason').getValue();
				data['remarks'] = popup.getField('remarks').getValue();
				data['effDate']  = popup.getField('effectiveDate').getDisplayDateString();
				return data;
			}
			,populate: function(action) {
				var popup = _popups['RemarkModifyPopup'];
				popup.enableAllFields();
				if (action == _controller.ADD) {
					_controller.populateDropdowns();
					popup.uuid = _controller.getNewRemarksUUID();
					popup.getField('remarks').setValue('');
				} else {
					var selectedRemark = _grids['grdRemarks'].getSelectedRecord();
					popup.getField('remarkType').setValue(selectedRemark.data['remarkTyp']);
					popup.uuid = selectedRemark.data['fundDetlRemarksUUID'];
					popup.getField('reason').setValue(selectedRemark.data['reason']);
					popup.getField('remarks').setValue(selectedRemark.data['remarks']);
					popup.getField('effectiveDate').setValue(selectedRemark.data['effDate']);
				}
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
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth				
				,items: [
					{
						width: _layoutWidth
						,style: 'margin-top: 10px'						
						,layout: 'form'
						,labelWidth: 50																		
						,items: [
							_fields['fund']
							,_buttons['lookup']																																			
						]
					}
					,_grids['classes']				
				]																			
			}
		)


		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['Close']									
				,handler: function(){DesktopWeb.Util.cancelScreen()}					
			})
		]			
	}
}