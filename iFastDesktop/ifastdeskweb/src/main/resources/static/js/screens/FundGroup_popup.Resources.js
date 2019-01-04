/*********************************************************************************************
 * @file	FundGroup_popup.Resources.js
 * @author	Winnie Cheng
 * @desc	Resources JS file for Fund Group PopUp screen
 *********************************************************************************************/
/*	
 *	Navigate:	System Level: Menu > System Maintenance > Fund Group Linkage  > ViewFundGroup button
 * 
 *  History : 
 *
 *  20 Nov 2016 Winnie Cheng. P0256381   CHG0045765 Fund Group for Germany
 *                  - Fund Group popUp view
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 558;
	var _layoutWidth = 678;
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,listeners: {
				click: function(){_controller.clickHandle_searchBtn();}
			}
		})	
		,resetBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Reset']							
			,handler: function(){_controller.doReset();}
			,disabled: true										 																			
		})			
	}
	
	// **** fields ****
	var _fields = {		
		grpType: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['GroupType']
			,width: 170
			,editable: true
			,allowBlank: false
			,disabled: false
			,listeners:{
				select: function() {
					_controller.doReset();
				}
				,blur: function(){
					var grpType = _fields['grpType'].getValue();
					if (grpType == null || grpType.length < 1) {
						_buttons['searchBtn'].disable();
					} else {
						_buttons['searchBtn'].enable();
					}
				}
				,change: function(){
					var grpType = _fields['grpType'].getValue();
					if (grpType == null || grpType.length < 1) {
						_buttons['searchBtn'].disable();
					} else {
						_buttons['searchBtn'].enable();
					}

				}
			}
		})
		,searchFor: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['SearchFor']
			,width: 170
			,editable: true
			,allowBlank: true
			,listeners:{
				select: function(fld, record, index) {
					var code = record.data['code'];
					if (code.length > 0){
						_controller.handleFundGrpClassSearchChange(code);
					}
					_controller.setSearchValueField();
				}
				,blur: function(){
					_controller.setSearchValueField();
				}
			}
		})
		
		,searchByFundGrp: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFundGrp'
			,hideLabel: true
			,allowBlank: true
			,width: 250
			,smartview: 'fundGroupSearch'
			,addtlSearchParams: [{name: 'fundGroupType', valueFn: function(){return 'FNBRLK'}}]
			,fields: ['displayValue', 'fundGroupType', 'fundGroupCode' ]
			,valueField: 'fundGroupCode'
			,displayField: 'displayValue'
			,hidden: false
			,listeners:{					
				focus: function() { 
					if (_fields['searchFor'].getValue() == '') {
						_fields['searchByFundGrp'].disable();
					} else {
						_fields['searchByFundGrp'].enable();
						_fields['searchByFundClass'].enable();
					}
				}
				,populated: function(fld, rec){
					_controller.currentSearch['fund'] = '';
					_controller.currentSearch['class'] = '';
				}
			}	
		})
		
		,searchByFundClass: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFundClass'
			,hideLabel: true
			,allowBlank: true
			,width: 250
			,smartview: 'fundSearch'
			,fields: ['displayValue', 'fund', 'class']
			,valueField: 'displayValue'
			,displayField: 'displayValue'
			,hidden: true
			,listeners:{					
				focus: function(){ 
					if (_fields['searchFor'].getValue() == '') {
						_fields['searchByFundClass'].disable();
					} else {
						_fields['searchByFundClass'].enable();
						_fields['searchByFundGrp'].enable();
					}
				}
				,populated: function(fld, rec){
					_controller.currentSearch['fund'] = rec.data['fund'];
					_controller.currentSearch['class'] = rec.data['class'];	
					_fields['searchByFundGrp'].reset();
				}				
			}	
		})
	}
	
	// **** grids ****
	var _grids = {
		fundGrp: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 40	
				,autoScroll: true
				,height: 120
				,autoExpandColumn: 'grpDesc'
				,store: new Ext.data.XmlStore({
					record: 'FundGrp'
					,fields: ['errMsg', 'fundGrpUUID', 'grpType', 'fundGroup', 'grpDesc', 'deff', 'stopDate'
							 ,'version', 'runMode', 'hasMorelinkedFundClasss', 'nextStartRecordNumlinkedFundClass'
							 ]
					,listeners: {
						load: function(store, records) {
							store.filterBy(function(record){return record.data.runMode != _controller.DEL});
							store.fireEvent('datachanged', store);//to set data in grid again	
						}
						,update: function(store, records) {
							store.filterBy(function(record){
							return record.data.runMode != _controller.DEL});
						}
					}
				})
				,selModel: new Ext.grid.RowSelectionModel({
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.selectFundGrp(record);
							}
						}
					}
				})
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
						,sortable: false
					}
					,columns: [{
							id: 'errMsg'
							,width: 25
							,renderer: function(val){
								return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
							}
						}
						,{header: _translationMap['GroupCode'], dataIndex: 'fundGroup', width: 110}
						,{header: _translationMap['GroupDesc'], id: 'grpDesc', dataIndex: 'grpDesc', width: 270}
					]
				})
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'
						,text: _translationMap['Add']
						,disabled: true
						,handler: function(){_controller.openActionPopup("fundGrpPopup", _controller.ADD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,disabled: true
						,handler: function(){_controller.openActionPopup("fundGrpPopup", _controller.MOD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,disabled: true
						,handler: function(){_controller.openActionPopup("fundGrpPopup", _controller.DEL);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'moreBtn'
						,text: _translationMap['More']
						,disabled: true
						,handler: function(){_controller.clickHandle_moreBtn();}
					})
				]
			}
		)
		,linkedFundClass: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 40
			,autoScroll: true
			,height: 205
			,autoExpandColumn: 'fundName'
			,features: [{
				ftype: 'summary'
			}]
			,store: new Ext.data.XmlStore({
				record: 'LnkFund'
				,fields: ['errMsg', 'lnkFundUUID', 'fund', 'class', 'fundName', 'isin', 'wkn', 'version', 'runMode']
				,listeners: {
					load: function(store, records) {
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
						store.fireEvent('datachanged', store); //to apply the changes to grid
					}
					,update: function(store, records) {
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
					}	
				}
			})
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.selectlinkedFundClass(record);
						}
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [{
						id: 'errMsg'
						,width: 25
						,renderer: function(val){
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}
					,{header: _translationMap['Fund'], dataIndex: 'fund', width: 50}
					,{header: _translationMap['Class'], dataIndex: 'class', width: 50}
					,{header: _translationMap['FundName'], id: 'fundName', dataIndex: 'fundName', width: 120}
					,{header: _translationMap['ISIN'], dataIndex: 'isin', width: 100} 
					,{header: _translationMap['WKN'], dataIndex: 'wkn', width: 60}
				]							
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,disabled: true
					,handler: function(){_controller.openActionPopup("linkedFundPopup", _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,disabled: true
					,handler: function(){_controller.openActionPopup("linkedFundPopup", _controller.DEL);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,disabled: true
					,handler: function(){_controller.clickHandle_moreBtnDetl();}
				})
			]
		})
	}
	
	// **** popups ****
	var _popups = {
		fundGrpPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 495
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
			,defaults: {border:false}
			,items: [{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center;font-weight:bold;font-size:12;padding:5px'	
				}
				,{
					layout: 'form'																		
					,style: 'padding:10px'
					,defaults: {border: true}
					,labelWidth: 120
					,items: [ 
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'grpType'
							,fieldLabel: _translationMap['GroupType']
							,width: 170
							,editable: true
							,allowBlank: false
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'fundGroup'
							,fieldLabel: _translationMap['GroupCode']
							,width: 170
							,maxLength: 6
							,allowBlank: false
						}) 
						,new DesktopWeb.Controls.TextField({
							itemId: 'grpDesc'
							,fieldLabel: _translationMap['GroupDesc']
							,width: 300
							,allowBlank: false
							,maxLength: 40
						}) 
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['fundGrpPopup'].isValid()){
							_controller.validateFundGrp(_popups['fundGrpPopup'].getData(), _popups['fundGrpPopup'].action);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['fundGrpPopup'].hide();}
				})
			]
			,init: function(action) {
				// initialize popup based on action
				var popup = _popups['fundGrpPopup'];
				popup.action = action;
				switch(action) {
					case _controller.ADD:{
						popup.setTitle(_translationMap['FundGroup'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:{
						popup.setTitle(_translationMap['FundGroup'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:{
						popup.setTitle(_translationMap['FundGroup'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action) {
				var popup = _popups['fundGrpPopup'];
				popup.clearAllFields();
				popup.enableAllFields();
				switch(action) {
					case _controller.ADD:{
						popup.uuid = _controller.getNewFundGrpUUID();						
						popup.getField('grpType').setValue(_fields['grpType'].getValue());
						popup.getField('grpType').disableField();

						break;
					}
					case _controller.MOD: {
						var selectedFundGrp = _grids['fundGrp'].getSelectedRecord();
						popup.uuid = selectedFundGrp.data['fundGrpUUID'];
						popup.getField('grpType').setValue(selectedFundGrp.data['grpType']);
						popup.getField('grpType').disableField();
						popup.getField('fundGroup').setValue(selectedFundGrp.data['fundGroup']);
						popup.getField('fundGroup').disableField();
						popup.getField('grpDesc').setValue(selectedFundGrp.data['grpDesc']);

						break;
					}
					case _controller.DEL: {
						var selectedFundGrp = _grids['fundGrp'].getSelectedRecord();
						popup.uuid = selectedFundGrp.data['fundGrpUUID'];

						popup.getField('fundGroup').setValue(selectedFundGrp.data['fundGroup']);
						popup.getField('fundGroup').disableField();
						popup.getField('grpType').setValue(selectedFundGrp.data['grpType']);
						popup.getField('grpType').disableField();
						
						popup.getField('grpDesc').setValue(selectedFundGrp.data['grpDesc']);
						popup.getField('grpDesc').disableField();
						
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function() {
			
				var popup = _popups['fundGrpPopup'];

				// Validate all input fields before business checking
				var valid = popup.getField('grpType').isValid();
				valid = popup.getField('fundGroup').isValid() && valid;
				valid = popup.getField('grpDesc').isValid() && valid;
				
				//Germany client need fundGrp Description and GrpID to be unique
				if (_popups['fundGrpPopup'].action != _controller.DEL) {

					var  grpIDInvalid = false;
					var  grpDescInvalid = false;
					var  popupUUID = _popups['fundGrpPopup'].uuid;
					
					//compare uniqueness fundGrpType&GrpID
					if(_popups['fundGrpPopup'].action == _controller.ADD) {
						var nDupTypeID = _grids['fundGrp'].getStore().queryBy(function(record){
								return (record.get('grpType') == popup.getField('grpType').getValue()
								&& record.get('fundGroup') == popup.getField('fundGroup').getValue().trim());
						});
						if (nDupTypeID.length > 0 ) {
							popup.getField('fundGroup').markInvalid(_translationMap['ERR_DUPLICATED_FUNDGRP']);
							grpIDInvalid = true;
						}
					}
					//compare uniqueness fundGrpType&Desc
					var nDupTypeDesc = _grids['fundGrp'].getStore().queryBy(function(record){
								return (record.get('grpType') == popup.getField('grpType').getValue()
								&& record.get('grpDesc') == popup.getField('grpDesc').getValue().trim()
								&& record.get('fundGrpUUID') != popupUUID);
					});
					if (nDupTypeDesc.length > 0 ) {
						popup.getField('grpDesc').markInvalid(_translationMap['ERR_DUPLICATED_FUNDGRPDESC']);
						grpDescInvalid = true;
					}
					if (grpIDInvalid  || grpDescInvalid) {
						return false;
					}
				}
				return valid;
			}
			,getData: function() {
				var popup = _popups['fundGrpPopup'];
				var data = {};
				data['fundGrpUUID'] = popup.uuid;
				data['grpType']   = popup.getField('grpType').getValue();
				data['fundGroup'] = popup.getField('fundGroup').getValue().trim();
				data['grpDesc'] = popup.getField('grpDesc').getValue().trim();
				data['runMode'] = popup.action;
				return data;
			}
		})		
		
		,linkedFundPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: _layoutWidth - 80
			,closeAction: 'hide'	
			,autoHeight: true				
			,modal: true
			,defaults: {border:false}
			,items: [ {
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center;font-weight:bold;padding:4px;font-size:12'	
				}
				,{
					layout: 'form'																		
					,style: 'padding:10px'
					,defaults: {border: true}
					,labelWidth: 110
					,items: [ 
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'grpType'
							,fieldLabel: _translationMap['GroupType']
							,width: 470
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'fundGroup'
							,fieldLabel: _translationMap['GroupCode']
							,width: 470
						}) 
						,new DesktopWeb.Controls.TextField({
							itemId: 'grpDesc'
							,fieldLabel: _translationMap['GroupDesc']
							,width: 470
						}) 
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'fundclass'
							,fieldLabel: _translationMap['FundClass']
							,smartview: 'fundSearch'				
							,fields: ['displayValue', 'fund', 'class', 'isin', 'wkn']
							,valueField: 'displayValue'		
							,displayField: 'displayValue'							
							,width: 470
							,allowBlank: false
							,listeners: {
								populated: function(fld, rec){
									var popup = _popups['linkedFundPopup'];
									popup.enableButton('okBtn');
									_controller.resetLinkedFundPopUp('isin', 'wkn', 'class');
									if (rec.data['fund'].length > 0) {
										popup.getField('isin').setValue(rec.data['isin']);
										popup.getField('wkn').setValue(rec.data['wkn']);
										popup.getField('class').setValue(rec.data['class']);
										fld.valueField = 'fund';
									}
								} 
								,cleared: function(){
									var popup = _popups['linkedFundPopup'];
									popup.disableButton('okBtn');
								}
							}
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'class'
							,hideLabel: true
							,allowBlank: true
							,hidden: true
						}) 
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'isin'
							,fieldLabel: _translationMap['ISIN']
							,smartview: 'fundSearch'				
							,fields: ['displayValue', 'fund', 'class', 'isin', 'wkn']
							,displayValue: 'isin'	
							,valueField: 'displayValue'								
							,width: 470
							,allowBlank: true
							,listeners: {
								populated: function(fld, rec){
									var popup = _popups['linkedFundPopup'];
									popup.enableButton('okBtn');
									_controller.resetLinkedFundPopUp('fundclass', 'class', 'wkn');
									if (rec.data['isin'].length >= 0){
										popup.getField('fundclass').setValue(rec.data['fund']);
										popup.getField('fundclass').setRawValue(rec.data['displayValue']);
										popup.getField('wkn').setValue(rec.data['wkn']);
										popup.getField('class').setValue(rec.data['class']);
										popup.getField('isin').setValue(rec.data['isin']);
									} 
								}
								,cleared: function(){
									var popup = _popups['linkedFundPopup'];
									popup.disableButton('okBtn');
								}
							}
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'wkn'
							,fieldLabel: _translationMap['WKN']
							,smartview: 'fundSearch'				
							,fields: ['displayValue', 'fund', 'class', 'isin', 'wkn']
							,valueField: 'displayValue'
							,displayValue: 'wkn'								
							,width: 470
							,allowBlank: true
							,listeners: {
								populated: function(fld, rec){
									var popup = _popups['linkedFundPopup'];
									popup.enableButton('okBtn');
									_controller.resetLinkedFundPopUp('fundclass', 'class', 'isin');
									if (rec.data['wkn'].length >= 0 ){
										popup.getField('fundclass').setValue(rec.data['fund']);
										popup.getField('fundclass').setRawValue(rec.data['displayValue']);
										popup.getField('wkn').setValue(rec.data['wkn']);
										popup.getField('class').setValue(rec.data['class']);
										popup.getField('isin').setValue(rec.data['isin']);
									}
								}
								,cleared: function(){
									var popup = _popups['linkedFundPopup'];
									popup.disableButton('okBtn');
								}
							}
						})
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['linkedFundPopup'].isValid()){
							_controller.validatelinkedFund(_popups['linkedFundPopup'].getData(), _popups['linkedFundPopup'].action);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['linkedFundPopup'].hide();}
				})
			]
			,init: function(action) {
				// initialize popup based on action
				var popup = _popups['linkedFundPopup'];
				popup.action = action;
				switch(action) {
					case _controller.ADD: {
						popup.setTitle(_translationMap['FundClass'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD: {
						popup.setTitle(_translationMap['FundClass'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL: {
						popup.setTitle(_translationMap['FundClass'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action) {
				var popup = _popups['linkedFundPopup'];
				popup.clearAllFields();
				popup.enableAllFields();
				
				var selectedGrp = _grids['fundGrp'].getSelectedRecord();
				
				switch(action) {
					case _controller.ADD: {
						popup.uuid = _controller.getNewLinkedFundUUID();
						popup.getField('grpType').setValue(selectedGrp.data['grpType']);
						popup.getField('grpType').disableField();
						popup.getField('fundGroup').setValue(selectedGrp.data['fundGroup']);
						popup.getField('fundGroup').disableField();
						popup.getField('grpDesc').setValue(selectedGrp.data['grpDesc']);
						popup.getField('grpDesc').disableField();
						break;
					}
					
					case _controller.DEL: {
						var selectedlinkedFundClass = _grids['linkedFundClass'].getSelectedRecord();
						popup.uuid = selectedlinkedFundClass.data['lnkFundUUID'];
						popup.getField('grpType').setValue(selectedGrp.data['grpType']);
						popup.getField('fundGroup').setValue(selectedGrp.data['fundGroup']);
						popup.getField('grpDesc').setValue(selectedGrp.data['grpDesc']);

						popup.getField('fundclass').setValue(selectedlinkedFundClass.data['fund']);
						popup.getField('fundclass').allowblank = true;
						popup.getField('isin').setValue(selectedlinkedFundClass.data['isin']);
						popup.getField('wkn').setValue(selectedlinkedFundClass.data['wkn']);
						popup.getField('class').setValue(selectedlinkedFundClass.data['class']);
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function() {
				var valid = true;
				var popup = _popups['linkedFundPopup'];
				var fundclass = popup.getField('fundclass').getValue();
				
				//Validate duplicated fund/class in popUp stage
				if (_popups['linkedFundPopup'].action != _controller.DEL) {
					var  fundClassInvalid = false;

					var nDupFundClass = _grids['linkedFundClass'].getStore().queryBy(function(record){
						return (record.get('fund') == fundclass
								&& record.get('class') == popup.getField('class').getValue());
					});

					if (nDupFundClass.length > 0 ) {
						popup.getField('fundclass').markInvalid(_translationMap['ERR_DUPLICATED_FUNDGRPMEMBER']);
						fundClassInvalid = true;
					}
					if (fundClassInvalid) {
						return false;
					}
				}

				if (!popup.getField('fundclass').isValid() || !fundclass || fundclass.length <= 0 ) {
					return false;
				} 
				return valid;
			}
			,getData: function() {
				var popup = _popups['linkedFundPopup'];
				var data = {};
				data['lnkFundUUID'] = popup.uuid;
				data['grpType'] = popup.getField('grpType').getValue();
				data['fundGroup'] = popup.getField('fundGroup').getValue();
				data['grpDesc'] = popup.getField('grpDesc').getValue();
				data['fund'] = popup.getField('fundclass').getValue();
				data['class'] = popup.getField('class').getValue();
				data['isin'] = popup.getField('isin').getValue();
				data['wkn'] = popup.getField('wkn').getValue();
				data['runMode'] = popup.action;
				return data;
			}
		})		
	}
	
	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth - 28
		
		,layoutHeight: _layoutHeight - 112
		
		,buttons: _buttons
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth - 26
				,style: 'padding-left:3px; padding-right:3px;'
				,items: [
					{
						xtype: 'fieldset'
						,title: _translationMap['Search']
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
								columnWidth: 1.5
								,items: [
									_fields['grpType']
								]
							}
							,{								
								columnWidth: 0.40
								,items: [
									_fields['searchFor']
								]
							}
							,{								
								columnWidth: 0.40
								,items: [
									_fields['searchByFundGrp']
									,_fields['searchByFundClass']
								]
							}
							,{								
								columnWidth: 0.10
								,style: 'text-align:right;'
								,items: [
									_buttons['searchBtn']
								]
							}
							,{								
								columnWidth: 0.10
								,style: 'text-align:right;'
								,items: [
									_buttons['resetBtn']
								]
							}
						]
						
					}
				]	
			}
			,{
				xtype: 'fieldset'
				,title: _translationMap['FundGroup']
				,width: _layoutWidth - 30					
				,items:[
					_grids['fundGrp']
				]
			}
			,{
				xtype: 'fieldset'
				,title: _translationMap['FundClass']
				,width: _layoutWidth - 30	
				,height: _layoutHeight - 333		
				,items:[
					_grids['linkedFundClass']
				]
			}
		   ]																				
		 }
		)
		,screenButtons: [			
			// Need one dummy button, prevent error from ExtJS
            new DesktopWeb.Controls.ScreenButton({
				text: 'View Fund Group PopUp',
                hidden: true
			})
		]			
	}
}