/*********************************************************************************************
 * @file	
 * @author	
 * @desc	
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  22 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54443
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  13 Dec 2017 Narin Suanlamyai P0266360 DFT0078343 
 *  				- Display ID Type description instead of ID Type code. 
 *  				- Add mode, default value of ID Type field will be blank.
 *  				- Save id type code to database instead of description. 
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 290;
	var _layoutWidth = 612;

	// **** fields ****
	var _fields = {		
	}
	
	// **** grids ****
	var _grids = {
	
		accountIdentifierDetails: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 12
			,autoScroll: true				
			,height: 250
			,style: 'margin-top: 5px'
			,store: new Ext.data.XmlStore({
				record: 'AcctIdentDetail'
				,fields: ['idType'
						,'idValue'
						,'idDesc'
						,'effectDt'
						,'stopDt'
						,'userName'
						,'procDate'
						,'modUser'
						,'modDate'
						,'ver'
						,'acctIDUUID'
						]
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.effectDt = DesktopWeb.Util.getDateDisplayValue(record.data.effectDt);
							record.data.stopDt = DesktopWeb.Util.getDateDisplayValue(record.data.stopDt);
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
							record.data.procDate = DesktopWeb.Util.getDateDisplayValue(record.data.procDate);
						});

						store.fireEvent('datachanged', store); //to set data in grid again																																	
					}
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(){
						_controller.handleAccIdentRecordSelectionChange()					
					}
					,rowdeselect: function(){
						_controller.handleAccIdentRecordSelectionChange()
					}									
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}
				,columns: [													
					{header: _translationMap['IDType'], id:'idType', dataIndex: 'idType', width:236
						, renderer: function(val){
							return (_controller.getIDTypeDescription(val));
						}
					}
					,{header: _translationMap['IDValue'], id:'idValue', dataIndex: 'idValue', width:120}
					,{header: _translationMap['EffectiveDate'], id:'effectDt',  dataIndex: 'effectDt', width:120}
					,{header: _translationMap['StopDate'], id:'stopDt',  dataIndex: 'stopDt', width:120}
				]							
			})
			
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,disabled: false							
					,handler: function(){
						_controller.openActionPopup(_controller.ADD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modifyBtn'
					,text: _translationMap['Modify']
					,disabled: true
					,handler: function(){
						_controller.openActionPopup(_controller.MOD);
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,disabled: true
					,handler: function(){
						_controller.openActionPopup(_controller.DEL);
						}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,disabled: true
					,handler: function(){_controller.openAdminPopup()}							
				})
			]	
		})
	}
	
	// **** popups ****
	var _popups = {			

		accIdentifierPopup: new DesktopWeb.AdvancedControls.PopupWindow({				
			width: 480
			,action: null
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
					,labelWidth: 150
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'comboBoxIDType'							
							,width: 280
							,fieldLabel: _translationMap['IDType']
							,allowBlank: true
							,editable: false							
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'textFieldIDValue'							
							,width: 280
							,maxLength: 15
							,blankText: 'This field cannot be empty'
							,maxLengthText: _translationMap['IDValueTextBoxMaxChar']
						    ,maskRe: /[a-z0-9_]/i
							,regex: /^[a-zA-Z0-9_]+$/
							,regexText: 'Only alphanumeric characters allowed'							
							//,allowBlank: false
							,fieldLabel: _translationMap['IDValue']
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'dateTimeEffectiveDate'	
							,width: 280
							,fieldLabel: _translationMap['EffectiveDate']
							,disabled : false
							,allowBlank: true														
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'dateTimeStopDate'	
							,width: 280
							,fieldLabel: _translationMap['StopDate']
							,disabled : false
							,allowBlank: true														
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})

					]												
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					text: _translationMap['OK']
					,handler: function(){
						_popups['accIdentifierPopup'].getField('comboBoxIDType').allowBlank = false;
						_popups['accIdentifierPopup'].getField('comboBoxIDType').validate();
						_popups['accIdentifierPopup'].getField('dateTimeEffectiveDate').allowBlank = false;
						_popups['accIdentifierPopup'].getField('dateTimeEffectiveDate').validate();
						_popups['accIdentifierPopup'].getField('dateTimeStopDate').allowBlank = false;
						_popups['accIdentifierPopup'].getField('dateTimeStopDate').validate();

						if (_popups['accIdentifierPopup'].isValid())
						{
							if (_popups['accIdentifierPopup'].action == _controller.ADD ||
								_popups['accIdentifierPopup'].action == _controller.MOD)
							{
								if (!_popups['accIdentifierPopup'].isPopupInputValid(_popups['accIdentifierPopup'].action))
								{
									return;
								}
							}
						
							_controller.savePopup(_popups['accIdentifierPopup'].action, _popups['accIdentifierPopup'].getData())
						}
					}	
				})
				,new DesktopWeb.Controls.ActionButton({
					text: _translationMap['Cancel']
					,handler: function(){_popups['accIdentifierPopup'].hide();}
				})
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
						this.setTitle(_translationMap['AccountIdentifierDetails'] + ' - ' + _translationMap['Add']);
						this.enableAllFields();													
						this.getField('comboBoxIDType').focus();				
						this.clearAllFields();													
						this.populateAddNewRecord();
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(_translationMap['AccountIdentifierDetails'] + ' - ' + _translationMap['Modify']);
						this.enableAllFields();
						this.populateModifySelectedRecord();													
						this.getField('comboBoxIDType').focus();				
						break;
					}
					case _controller.DEL:
					{
						this.setTitle(_translationMap['AccountIdentifierDetails'] + ' - ' + _translationMap['Delete']);
						this.get(0).show();  
						this.disableAllFields();							
						this.populateWithSelectedRecord();												
						break;
					}
				}

				this.getField('comboBoxIDType').allowBlank = true;
				this.getField('comboBoxIDType').validate();
				this.getField('textFieldIDValue').allowBlank = true;
				this.getField('textFieldIDValue').validate();
				this.getField('dateTimeEffectiveDate').allowBlank = true;
				this.getField('dateTimeEffectiveDate').validate();
				this.getField('dateTimeStopDate').allowBlank = true;
				this.getField('dateTimeStopDate').validate();
			}
			,clearAllFields: function()
			{
				this.getField('comboBoxIDType').setValue('');
				this.getField('textFieldIDValue').setValue('');
				this.getField('dateTimeEffectiveDate').setValue('');
				this.getField('dateTimeStopDate').setValue('');
			}
			,populateAddNewRecord: function()
			{
				this.getField('comboBoxIDType').setValue("");
				this.getField('dateTimeEffectiveDate').setValue(_controller.getDefaultDate());
				this.getField('dateTimeStopDate').setValue(DesktopWeb.Util.convertDateStringFormat('12/31/9999', "mdy", DesktopWeb.Util.getDateDisplayFormat()));
			}
			,populateModifySelectedRecord: function()
			{
				var selectedRecord = _grids['accountIdentifierDetails'].getSelectedRecord();

				this.getField('comboBoxIDType').setValue(selectedRecord.data.idType);
				this.getField('textFieldIDValue').setValue(selectedRecord.data.idValue);
				this.getField('dateTimeEffectiveDate').setValue(selectedRecord.data.effectDt);
				this.getField('dateTimeStopDate').setValue(selectedRecord.data.stopDt);
			}
			,populateWithSelectedRecord: function()
			{
				var selectedRecord = _grids['accountIdentifierDetails'].getSelectedRecord();

				this.getField('comboBoxIDType').setValue(selectedRecord.data.idType);
				this.getField('textFieldIDValue').setValue(selectedRecord.data.idValue);
				this.getField('dateTimeEffectiveDate').setValue(selectedRecord.data.effectDt);
				this.getField('dateTimeStopDate').setValue(selectedRecord.data.stopDt);
			}
			,getData: function()
			{
				var data = {};				

				data['runMode'] = this.action;
				
				data['idType'] = this.getField('comboBoxIDType').getValue();
				data['idValue'] = this.getField('textFieldIDValue').getValue();
				
				data['effectDt'] = this.getField('dateTimeEffectiveDate').getDisplayDateString();
				data['stopDt'] = this.getField('dateTimeStopDate').getDisplayDateString();
				
				var selectedRecord = _grids['accountIdentifierDetails'].getSelectedRecord();
				
				switch(this.action)
				{
					case _controller.ADD:
					{
						var comboBox = this.getField('comboBoxIDType');
						
						data['runMode'] = 'A';
						data['version'] = '';
						data['acctIDUUID'] = '';
						data['selectedItemText'] = this.getField('comboBoxIDType').lastSelectionText;
						break;
					}
					case _controller.MOD:
					{
						data['runMode'] = 'M';
						data['version'] = selectedRecord.data.ver;
						data['acctIDUUID'] = selectedRecord.data.acctIDUUID;
						data['idDesc'] = selectedRecord.data.idDesc;
						break;
					}
					case _controller.DEL:
					{
						data['runMode'] = 'D';
						data['version'] = selectedRecord.data.ver;
						data['acctIDUUID'] = selectedRecord.data.acctIDUUID;
						data['idDesc'] = selectedRecord.data.idDesc;
						break;
					}
				}														

				return data;
			}
			,isPopupInputValid: function(action)
			{
				var idTypeComboBoxValue = this.getField('comboBoxIDType').getValue();
				var idValueTextBox = this.getField('textFieldIDValue').getValue();

				var effDate = this.getField('dateTimeEffectiveDate').getValue().format(DesktopWeb.Util.getDateFieldDisplayFormatString());				
				var stopDate = this.getField('dateTimeStopDate').getValue().format(DesktopWeb.Util.getDateFieldDisplayFormatString());				
				
				if (action == _controller.ADD)
				{
					if (idTypeComboBoxValue.search('INSFLG') != -1 &&
						_controller.getIsInsuranceFlagAlreadyPresent())
					{
						DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("InsuranceFlagIsAlreadyPresent"));
						return false;
					}
				}
				
				if (this.getField('dateTimeEffectiveDate').getValue() > this.getField('dateTimeStopDate').getValue())
				{
					DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("EffDateGreaterThanStopDateError"));
					return false;
				}
				
/*				if (_controller.getIsInsuranceNumberAlreadyPresent())
				{
					var obj = _controller.getEffAndStopDateFromExistingInsuranceNumber();
					
					if (obj != null)
					{
						dfEffDate = new Ext.form.DateField({value: obj.effDate, format: DesktopWeb.Util.getDateFieldDisplayFormatString()});
						dfStopDate = new Ext.form.DateField({value: obj.stopDate, format: DesktopWeb.Util.getDateFieldDisplayFormatString()});
						
						if ((dfEffDate.value >= effDate && dfEffDate.value <= stopDate) ||
							(dfStopDate.value <= stopDate && dfStopDate.value >= effDate))
						{
							DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("OverlappingDatesError"));
							return false;
						}
					}
				}
*/				
				if (idTypeComboBoxValue.search('EMPID') != -1 &&
					idValueTextBox == "")
				{
					DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("IDValueTextBoxEmptyErrorMsg"));
					this.getField('textFieldIDValue').allowBlank = false;
					this.getField('textFieldIDValue').validate();
					return false;
				}

				if (idValueTextBox.length > 15)
				{
					DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("IDValueTextBoxMaxChar"));
					return false;
				}

				if (idTypeComboBoxValue.search('INSFLG') != -1 &&
					idValueTextBox.toUpperCase() != "NO" &&
					idValueTextBox.toUpperCase() != "YES")
				{
					DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("InsuredFlagValuesErrorMsg"));
					return false;
				}
				
				if (idTypeComboBoxValue.search('INSFLG') != -1 &&
					idValueTextBox.toUpperCase() == "NO" &&
					_controller.getIsInsuranceNumberNotEmpty())
				{
					DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("InsuredFlagErrorMsg"));
					return false;
				}
				if (idTypeComboBoxValue.search('INSNO') != -1 &&
					_controller.getIsInsuranceFlagNO() &&
					idValueTextBox != "")
				{
					DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("InsuranceNumberErrorMsg"));
					return false;
				}
				else
				{
					return true;	
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
						xtype: 'fieldset'
						,style: 'margin-top: 10px; margin-bottom: 5px;'
						,title: _translationMap['AccountIdentifierDetails']
						,items: [
							_grids['accountIdentifierDetails']
						]
					}
				
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton(
				{
					text: 'OK'
					,handler: function()
					{
						if (_controller.submitDataOnOK())
						{
							DesktopWeb.Util.commitScreen();
							DesktopWeb.Util.closeScreenWithDialog();
						}
						else
						{
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: 'Cancel'
					,handler: function(){DesktopWeb.Util.cancelScreen()}
				}
			)
		]			
	}
}