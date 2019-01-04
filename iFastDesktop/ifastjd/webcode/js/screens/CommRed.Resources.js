/*********************************************************************************************
 * @file	CommRed.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Commission Reduction screen
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
	var _layoutHeight = 450;
	var _layoutWidth = 454;
	
	// **** fields ****
	var _fields = {		
	}
	
	// **** grids ****
	var _grids = {
		commRedGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth
				,title: ''
				,autoScroll: true
				,height: 200
				,autoExpandColumn: 'code'
				,store: new Ext.data.XmlStore({
					record: 'CommRed'
					,fields: ['commRedUUID', 'commRedCode', 'deff', 'stopDate', 'version', 'inUsed', 'commRedErrMsg', 'updMode']
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
					,listeners: {
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.setSelectedCommRed(record, index);
							}
						}
						,rowdeselect: function(){
							_controller.setDeselectedCommRed();
						}
					}
				})
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
						,width: 110
						,sortable: false
					}
					,columns: [
						{
							dataIndex: 'commRedErrMsg'
							,renderer: function(val){
								return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
							}
							,width: 25
						}
						,{id: 'code', header: _translationMap['Code'], dataIndex: 'commRedCode', width: 175}
						,{header: _translationMap['EffectiveDate'], dataIndex: 'deff'}
						,{header: _translationMap['StopDate'], dataIndex: 'stopDate'}
					]							
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'	
						,text: _translationMap['Add']							
						,handler: function(){_controller.openActionPopup("commRedUpdate", _controller.ADD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,handler: function(){_controller.openActionPopup("commRedUpdate", _controller.MOD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,handler: function(){_controller.openActionPopup("commRedUpdate", _controller.DEL);}							
					})									
					,new DesktopWeb.Controls.ActionButton(		
						{
							itemId: 'moreBtn'
							,text: 'More'
							,handler: function(){_controller.doReload(true)}
						}
					)
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'adminBtn'
						,text: _translationMap['Admin']
						,handler: function(){_controller.openAdminPopup('commRed');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'historicalBtn'
						,text: _translationMap['Historical']
						,handler: function(){_controller.openHistoryPopup('commRed');}
					})
				]
			}
		)
		,commRedDetlGrid: new DesktopWeb.AdvancedControls.GridPanel(
			{											
				autoScroll: true
				,height: 215
				,autoExpandColumn: 'commRed'
				,store: new Ext.data.XmlStore({
					record: 'CommRedDetl'
					,fields: ['commRedDetlUUID', 'commRedRate', 'intIncRate', 'version', 'commRedDetlErrMsg', 'updMode']
					,listeners: {
						load: function(store, records){
							_grids['commRedDetlGrid'].getSelectionModel().selectFirstRow();
						}
						,datachanged: function(store){
							_controller.setCommRedDetlButtons();
						}
					}					
				})
				,selModel: new Ext.grid.RowSelectionModel({					
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.setSelectedCommRedDetl(record);
							}
						}
						,rowdeselect: function(){
							_controller.setDeselectedCommRedDetl();
						}
					}						
				})
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
						,width: 190
						,sortable: true
					}
					,columns: [
						{
							width: 25
							,dataIndex: 'commRedDetlErrMsg'
							,renderer: function(val){
								return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
							}
						}
						,{id: 'commRed', header: _translationMap['CommRedPercent'], dataIndex: 'commRedRate', xtype: 'numbercolumn' ,format: '0,000.0000'}
						,{header: _translationMap['InterestIncPercent'], dataIndex: 'intIncRate', xtype: 'numbercolumn' ,format: '0,000.0000'}
					]							
				})
				,buttons: [					
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'								
						,text: _translationMap['Add']							
						,handler: function(){_controller.openActionPopup("commRedDetlUpdate", _controller.ADD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,handler: function(){_controller.openActionPopup("commRedDetlUpdate", _controller.MOD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,handler: function(){_controller.openActionPopup("commRedDetlUpdate", _controller.DEL);}							
					})									
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'adminBtn'
						,text: _translationMap['Admin']
						,handler: function(){_controller.openAdminPopup('commRedDetl');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'historicalBtn'
						,text:_translationMap['Historical']
						,handler: function(){_controller.openHistoryPopup('commRedDetl');}
					})
				]
			}
		)
	}		
		
	// **** popups ****
	var _popups = {
		commRedUpdate: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 300
			,closeAction: 'hide'					
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center;font-weight:bold;'	
				}
				,{
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 90
					,items: [ 
						new DesktopWeb.Controls.TextField({
							itemId: 'commRedCodeFld'
							,fieldLabel: _translationMap['Code']
							,allowBlank: false
							,maxLength: 15
							,validator: function(val){
								var reg = /^[\w\s-]*$/;
								return reg.test(val);
							}
							,width: 150
						}) 
						,new DesktopWeb.Controls.DateField({
							itemId: 'effDateFld'
							,fieldLabel: _translationMap['EffDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'stopDateFld'
							,fieldLabel: _translationMap['StopDate']
							,allowBlank: false
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
						if (_popups['commRedUpdate'].isValid()){
							_controller.commRedUpdate(_popups['commRedUpdate'].action, _popups['commRedUpdate']);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['commRedUpdate'].hide();}
				})
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['commRedUpdate'];
				popup.action = action
				switch(action)
				{
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['CommRed']+ ' - ' +_translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['CommRed']+ ' - ' +_translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['CommRed']+ ' - ' +_translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action)
			{
				var popup = _popups['commRedUpdate'];	
				popup.clearAllFields();
				popup.enableAllFields();
				if(action == _controller.ADD)
				{
					popup.getField('effDateFld').setValue(_controller.getDefault('deff'));
					popup.getField('stopDateFld').setValue(_controller.getDefault('stopDate'));
				}else{
					var selectedCommRed = _controller.getSelectedCommRed();
					popup.getField('commRedCodeFld').setValue(selectedCommRed.get('commRedCode'));
					popup.getField('effDateFld').setValue(selectedCommRed.get('deff'));
					popup.getField('stopDateFld').setValue(selectedCommRed.get('stopDate'));
					if(action == _controller.MOD && selectedCommRed.get('inUsed')=='yes')
					{
						popup.getField('commRedCodeFld').disableField();
						popup.getField('effDateFld').disableField();
					}
				}
			}
		})		
		,commRedDetlUpdate: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,width: 300
			,closeAction: 'hide'					
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']			
					,style: 'text-align:center'													
				}
				,{						
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 150
					,items: [
						new DesktopWeb.Controls.NumberField({
							itemId: 'commRedRateFld'
							,fieldLabel: _translationMap['CommRedPercent']
							,allowDecimals: true
							,allowNegative: false
							,allowBlank: false
							,decimalPrecision: 4
							,minValue: 0.0000
							,maxValue: 100.0000
							,minText: _translationMap['PercentRequired']
							,maxText: _translationMap['PercentRequired']
							,width:100
						})
						,new DesktopWeb.Controls.NumberField({
							itemId: 'intIncRateFld'
							,fieldLabel: _translationMap['InterestIncPercent']
							,allowDecimals: true
							,allowNegative: false
							,allowBlank: false
							,decimalPrecision: 4
							,minValue: 0.0000
							,maxValue: 100.0000
							,minText: _translationMap['ValueLimit']
							,maxText: _translationMap['ValueLimit']
							,width:100
						})
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['commRedDetlUpdate'].isValid()){
							_controller.commRedDetlUpdate(_popups['commRedDetlUpdate'].action, _popups['commRedDetlUpdate']);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['commRedDetlUpdate'].hide();}
				})
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['commRedDetlUpdate'];
				popup.action = action
				popup.clearAllFields();
				switch(action)
				{
					case _controller.ADD:
					{
						// Deselect what selected
						var grid = _grids['commRedDetlGrid'];
						popup.setTitle(_translationMap['CommRedDetail']+ ' - ' +_translationMap['Add']);
						popup.enableAllFields();
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['CommRedDetail']+ ' - ' +_translationMap['Modify']);
						popup.enableAllFields();
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['CommRedDetail']+ ' - ' +_translationMap['Delete']);
						popup.disableAllFields();
						popup.populate(action);
						popup.get(0).show();
						break;
					}
				}
				popup.getField('commRedRateFld').clearInvalid();
			}
			,populate: function(action)
			{
				var popup = _popups['commRedDetlUpdate'];
				
				if(action == _controller.ADD)
				{
					popup.getField('commRedRateFld').setValue(_controller.getDefault('commRedRate'));
					popup.getField('intIncRateFld').setValue(_controller.getDefault('intIncRate'));
				}else{
					var selectedCommRedDetl = _controller.getSelectedCommRedDetl();
					popup.getField('commRedRateFld').setValue(selectedCommRedDetl.get('commRedRate'));
					popup.getField('intIncRateFld').setValue(selectedCommRedDetl.get('intIncRate'));
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
		
		,layout: new Ext.Container({
			height: _layoutHeight
			,width: _layoutWidth
			,items: [
				_grids['commRedGrid']
				,{
					xtype: 'fieldset'
					,title: _translationMap['CommRedDetails']
					,style: "margin-bottom:20px"
					,width: _layoutWidth
					,items: _grids['commRedDetlGrid']
				}
			]																				
		})
		
		,screenButtons: [	
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){DesktopWeb.Util.commitScreen()}
			})
			,new DesktopWeb.Controls.ScreenButton({
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
			})
		]			
	}
}