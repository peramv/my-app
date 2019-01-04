/*********************************************************************************************
 * @file	AccountGroup.Resources.js
 * @author	Narin Suanlamyai
 * @desc	Resources JS file for Account Group screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Account Group
 *				
 *  History : 
 *
 *  23 Jul 2014 Narin S. P0233553 T55642
 *					- Created.
 *
 *  03 Sept 2014 Narin S. P0233553 T55678
 *					- Add validation for account group and linked account.
 *
 *  18 Sept 2014 Narin S. P0233553 DFT0041280 T55739
 *					- Remove listeners of search criteria fields to make screen simple.
 *					- Stop Date for linked account cannot be future date.
 *
 *	25 Sept 2014 Narin S. P0233553 DFT0041354 T55772
 *					- Change default of effective date to current business date.
 *
 *	02 Oct 2014 Narin S. P0233553 DFT0041999 T55823
 *					- Effective Date cannot be future date of Account Group and Linked Account.
 *
 *  03 Oct 2014 Narin S. P0233553 DFT0041997 T55805
 *					- Hide Group ID field for new record.
 *
 *  16 Oct 2014 Narin S. P0233553 DFT0042580 T55888
 *					- Fixed displaying Group ID field on Account Group popup when AutoGrpID is no.
 *					- Change LinkedAccts tag name to LnkAccts
 *
 *  29 Oct 2014 Narin S. P0233553 DFT0043383 T55939
 *					- Set read-only to effective date field when it is in Modify mode.
 *					- Adjust popup layout
 *
 *  21 Nov 2014 Narin S. P0233553 DFT0044722 T56083
 *					- Fixed account detail is blank while adding an account.
 *
 *  14 jul 2015 Chersak S. P0243346 NCE Householding of Mail T81029
 *                  - New fields: Status and Remark in group level.
 *                  - New fields: Primary in association level.
 *                  - Using configuration table to handle group behavior.
 *
 *  23 Sep. 2016 Winnie Cheng. P0256381 T83741 CHG0045765 Fund Broker Linkage for Germany
 *					- modify.
 *
 *  13 Oct 2016 Winnie Cheng. P0256381  T83939 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, layout adjustment and bug fixing
 *
 *  20 Oct 2016 Winnie Cheng. P0256381  T84056 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, imp. Delete error handing for account and bug fixing for other grouptypes
 *                  - Adding duplication validation in popUp stage
 *
 *  28 Oct 2016 Winnie Cheng. P0256381  T84097 DFT0068689 CHG0045765 Fund Broker Linkage for Germany
 *                  - Rewritten duplication validation by using store.queryBy
 *
 *  8 Nov 2016 Winnie Cheng. P0256381  T84187 DFT0069088 CHG0045765 Fund Broker Linkage for Germany
 *                  - remove additional popUp
 *
 *  17 Nov 2016 Winnie Cheng. P0256381  T84279 DFT0069397 CHG0045765 Fund Broker Linkage for Germany
 *                  - minor fixing for disable AFT 'Modify' button for InActive AcctGrp
 *                  
 *  25 oct 2017 Sreejith A. P0266789-1212 Desktop changes for Account Linkage
 *  		    	- date fields validation enable for CRMREL group type
 *  				- Group id and Description field max length setting from config
 *  		   	 	- Desc field made available in linkage popup for CRMREL group
 *  				- Other config changes for CRMREL group
 */
 

 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 540;
	var _layoutWidth = 720;

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
			,listeners:{
				select: function(fld, record, index) {
					var code = record.data['code'];
					if (code.length > 0){
						_controller.setDefaultDropdownVal(code);
						_controller.setFormForACBRLK(code);
						_controller.loadRequestRecNums(code);
					}					
					_controller.doReset();
				}
			}
		})
		,searchFor: new DesktopWeb.Controls.SMVComboBox({
			fieldLabel: _translationMap['SearchFor']
			,width: 170
			,editable: true
			,allowBlank: true
			,listeners:{
				select: function(fld, record, index){
					var code = record.data['code'];
					if (code.length > 0){
						_fields['searchValue'].allowBlank = false;
					}else {
						_fields['searchFor'].allowBlank = true;
						_fields['searchValue'].allowBlank = true;
						_fields['searchFor'].reset();
						_fields['searchValue'].reset();
					}
				}
				,blur: function(fld){
					if (fld.getValue().length <=0){
						_fields['searchValue'].reset();
						_fields['searchValue'].allowBlank = true;
						_fields['searchFor'].allowBlank = true;
					}
				}
			}
		})
		,searchValue: new DesktopWeb.Controls.TextField({
			hideLabel: true
			,width: 200
			,allowBlank: true
		})
		,acctGrpStat: new DesktopWeb.Controls.RadioGroup({
			hideLabel: true
			,width: 120
			,column: 2
			,items:[
				{
					boxLabel: _translationMap['All']
					,name: 'acctGrpStat'
					,inputValue: 'all'
				},{
					boxLabel: _translationMap['Active']
					,name: 'acctGrpStat'
					,inputValue: 'active'
					,checked: true
				}
			]
			,listeners:{
				change: function( grp, chked ){
					_controller.changeHandle_GrpStat();
				}
			}
		})
		,linkedAcctStat: new DesktopWeb.Controls.RadioGroup({
			hideLabel: true
			,width: 120
			,column: 2
			,items:[
				{
					boxLabel: _translationMap['All']
					,name: 'linkedAcctStat'
					,inputValue: 'all'
				},{
					boxLabel: _translationMap['Active']
					,name: 'linkedAcctStat'
					,inputValue: 'active'
					,checked: true
				}
			]
			,listeners:{
				change: function( grp, chked ){
					_controller.changeHandle_LinkedAcctStat();
				}
			}
		})
	}
	
	// **** grids ****
	var _grids = {
		acctGrp: new DesktopWeb.AdvancedControls.GridPanel(
			{							
				width: _layoutWidth - 20		
				,autoScroll: true
				,height: 200
				,autoExpandColumn: 'grpType'
				,store: new Ext.data.XmlStore({
					record: 'AcctGrp'
					,fields: ['errMsg', 'acctGrpUUID', 'grpType', 'grpId', 'grpDesc', 'deff', 'stopDate'
								, 'allowMod', 'allowDel', 'userName', 'processDate', 'modUser', 'modDate'
								, 'version', 'LinkedAccts', 'runMode', 'hasMoreLinkedAccts', 'nextStartRecordNumLinkedAcct'
								, 'grpStat', 'grpRemark']
					,listeners: {
						load: function(store, records)
						{
							Ext.each(records, function(record){
								record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
								record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
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
				,selModel: new Ext.grid.RowSelectionModel({
					singleSelect: true
					,listeners: {
						rowselect: function(selModel, index, record){
							if(selModel){
								_controller.selectAcctGrp(record);
							}
						}
					}
				})
				,colModel: new Ext.grid.ColumnModel({
					defaults: {
						menuDisabled: true
						,sortable: false
					}
					,columns: [
						{
							id: 'errMsg'
							,width: 25
							,renderer: function(val){
								return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
							}
						}
						,{id: 'grpType', header: _translationMap['GroupType'], dataIndex: 'grpType'
							, renderer: function(val){
								return (_controller.getDisplay('GroupTypeList', val));
							}
						}
						,{header: _translationMap['GroupID'], dataIndex: 'grpId', width: 100}
						,{header: _translationMap['GroupDesc'], dataIndex: 'grpDesc', width: 180}
                        ,{id: 'grpStat', header: _translationMap['GrpStat'], dataIndex: 'grpStat', width: 100
							, renderer: function(val){
								return (_controller.getDisplay('GroupStatusList', val));
							}
						}
						,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width: 80}
						,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width: 80}
					]
				})
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
						itemId: 'addBtn'
						,text: _translationMap['Add']
						,disabled: true
						,handler: function(){_controller.openActionPopup("acctGrpPopup", _controller.ADD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'modBtn'
						,text: _translationMap['Modify']
						,disabled: true
						,handler: function(){_controller.openActionPopup("acctGrpPopup", _controller.MOD);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'delBtn'
						,text: _translationMap['Delete']
						,disabled: true
						,hidden: true
						,handler: function(){_controller.openActionPopup("acctGrpPopup", _controller.DEL);}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'historyBtn'
						,text: _translationMap['Historical']
						,disabled: true
						,handler: function(){_controller.openHistoryPopup('AcctGrp');}
					})
					,new DesktopWeb.Controls.ActionButton({
						itemId: 'adminBtn'
						,text: _translationMap['Admin']
						,disabled: true
						,handler: function(){_controller.openAdminPopup('AcctGrp');}
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
		,linkedAcct: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth - 20
			,autoScroll: true
			,height: 200
			,autoExpandColumn: 'acct'
			,features: [{
				ftype: 'summary'
			}]
			,store: new Ext.data.XmlStore({
				record: 'LnkAcct'
				,fields: ['errMsg', 'lnkAcctUUID', 'acct', 'name', 'dlrOwnership', 'broker'
							, 'branch', 'slsrep', 'deff', 'stopDate', 'allowMod', 'allowDel'
							, 'userName', 'processDate', 'modUser', 'modDate', 'version', 'runMode'
							, 'primaryAcct', 'othRef']
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
						});
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
							_controller.selectLinkedAcct(record);
						}
					}
				}
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
					,sortable: false
				}
				,columns: [
					{
						id: 'errMsg'
						,width: 25
						,renderer: function(val){
							return (val ? DesktopWeb.Util.buildErrorFlag(val) : '');
						}
					}
					,{id: 'acct', header: _translationMap['Account'], dataIndex: 'acct'}
					,{header: _translationMap['DlrOwnerShipNumber'], dataIndex: 'dlrOwnership', width: 80}
					,{header: _translationMap['Broker'], dataIndex: 'broker', width: 75}
					,{header: _translationMap['Branch'], dataIndex: 'branch', width: 75}
					,{header: _translationMap['SalesRep'], dataIndex: 'slsrep', width: 75}
					,{header: _translationMap['PrimaryAcct'], dataIndex: 'primaryAcct', renderer: function(val) {return ((val == 'NO') ? '' : val);}, width: 75}
					,{header: _translationMap['OtherReferenceNumberGrid'], dataIndex: 'othRef', width: 85}
					,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width: 100}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width: 100}
				]							
			})
			,bbar: [
				new Ext.Toolbar.TextItem({
					id: 'bb_shareholderName'
					,text: _translationMap['ShareholderName'] + ":"
				})
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,disabled: true
					,handler: function(){_controller.openActionPopup("linkedAcctPopup", _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,disabled: true
					,handler: function(){_controller.openActionPopup("linkedAcctPopup", _controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,disabled: true
					,hidden: true
					,handler: function(){_controller.openActionPopup("linkedAcctPopup", _controller.DEL);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'historyBtn'
					,text: _translationMap['Historical']
					,disabled: true
					,handler: function(){_controller.openHistoryPopup('LinkedAcct');}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,disabled: true
					,handler: function(){_controller.openAdminPopup('LinkedAcct');}
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
		acctGrpPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 435
			,closeAction: 'hide'
			,autoHeight: true
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center;font-weight:bold; font-size:12px; padding:4px'	
				}
				,{
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 90
					,items: [ 
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'grpType'
							,fieldLabel: _translationMap['GroupType']
							,width: 170
							,editable: true
							,allowBlank: false
							,listeners:{ 				
								select: function(fld, record, index) {		
									_controller.enableGrpId(!(_controller.getConfig(fld.getValue(), "AutoGroupID") == "YES"));
									_controller.enableGrpStatus(_controller.getConfig(fld.getValue(), "GrpStatusApplicable") == "YES");
									_controller.defaultGrpStatus(_controller.getConfig(fld.getValue(), "GrpStatusApplicable") == "YES", _popups['acctGrpPopup'].action, 
									_controller.getConfig(fld.getValue(), "DefaultGroupStatus"));
									_controller.enablePrimaryAcct(parseInt(_controller.getConfig(fld.getValue(), "PrimaryPerGroup")) > 0);
									_controller.populateGrpStatusByGrpType(fld.getValue());	
									_controller.setAcctGrpMaxLengthFromConfig(fld.getValue(),'acctGrpPopup');
									_controller.setStartStopDate(fld.getValue(), 'acctGrpPopup');
									_controller.enableDisableDates(fld.getValue(),'acctGrpPopup');
									_popups['acctGrpPopup'].getField('grpId').reset();
									_popups['acctGrpPopup'].getField('grpDesc').reset();
								}
								,change: function(fld, newValue, oldValue) {
								    _controller.clearGrpStatus(newValue, oldValue); 
									_controller.defaultGrpStatus(_controller.getConfig(fld.getValue(), "GrpStatusApplicable") == "YES", _popups['acctGrpPopup'].action, 
									_controller.getConfig(fld.getValue(), "DefaultGroupStatus"));
								}
							}
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'grpId'
							,fieldLabel: _translationMap['GroupID']
							,width: 170
							,maxLength: 15
						}) 
						,new DesktopWeb.Controls.TextField({
							itemId: 'grpDesc'
							,fieldLabel: _translationMap['GroupDesc']
							,width: 200
							,allowBlank: true
							,maxLength: 40
						}) 
						,new DesktopWeb.Controls.DateField({
							itemId: 'deff'
							,fieldLabel: _translationMap['EffDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'stopDate'
							,fieldLabel: _translationMap['StopDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'grpStat'
							,fieldLabel: _translationMap['GrpStat']
							,width: 137
							,editable: false
						})
						,new Ext.form.TextArea({
							itemId: 'grpRemark'
							,fieldLabel: _translationMap['GrpRemark']
							,width: 137
						}) 
						
					]						
				}													
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['acctGrpPopup'].isValid()){
							_controller.validateAcctGrp(_popups['acctGrpPopup'].getData(), _popups['acctGrpPopup'].action);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['acctGrpPopup'].hide();}
				})
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['acctGrpPopup'];
				popup.action = action;
				switch(action)
				{
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['AccountGroup'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['AccountGroup'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['AccountGroup'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action)
			{
				var popup = _popups['acctGrpPopup'];
				popup.clearAllFields();
				popup.enableAllFields();
				_controller.setAcctGrpMaxLengthFromConfig(_fields['grpType'].getValue(),'acctGrpPopup');
				switch(action)
				{
					case _controller.ADD:
					{
						popup.uuid = _controller.getNewAcctGrpUUID();

						popup.getField('grpId').hide();
						popup.getField('grpStat').hide();
						popup.getField('grpRemark').hide();
						_controller.defaultGrpTypeDrpdwn(_fields['grpType'].getValue());
						//acbrlk - Germany accout group type
						if (_controller.AFTACCTGRPTYPE == _fields['grpType'].getValue()) {
						    _controller.setAcctGrpPopUpForACBRLK();
							_controller.setStartStopDate(_fields['grpType'].getValue(), 'acctGrpPopup');
							_controller.enableDisableDates(_fields['grpType'].getValue(), 'acctGrpPopup');
							popup.getField('grpId').show();
						} else {
							popup.getField('deff').setValue(_controller.getDefault('curBusDate'));
							popup.getField('stopDate').setValue(_controller.getDefault('stopDate'));
							popup.getField('grpType').enable();
						}
						break;
					}
					
					case _controller.MOD:
					{
						var selectedAcctGrp = _grids['acctGrp'].getSelectedRecord();
						popup.uuid = selectedAcctGrp.data['acctGrpUUID'];
						popup.getField('grpType').setValue(selectedAcctGrp.data['grpType']);
						
						if (Ext.isEmpty(selectedAcctGrp.data['grpId']))
						{
							popup.getField('grpId').hide();
						}else{
							popup.getField('grpId').show();
							popup.getField('grpId').setValue(selectedAcctGrp.data['grpId']);
							popup.getField('grpId').disableField();
						}
						
						_controller.enableGrpStatus(_controller.getConfig(popup.getField('grpType').getValue(), "GrpStatusApplicable") == "YES");
						_controller.enablePrimaryAcct(parseInt(_controller.getConfig(popup.getField('grpType').getValue(), "PrimaryPerGroup")) > 0);
						_controller.populateGrpStatusByGrpType(popup.getField('grpType').getValue());	

						popup.getField('grpDesc').setValue(selectedAcctGrp.data['grpDesc']);
						popup.getField('deff').setValue(selectedAcctGrp.data['deff']);
						popup.getField('stopDate').setValue(selectedAcctGrp.data['stopDate']);
						popup.getField('grpStat').setValue(selectedAcctGrp.data['grpStat']);
						popup.getField('grpRemark').setValue(selectedAcctGrp.data['grpRemark']);
						
						_controller.enableDisableDates(selectedAcctGrp.data['grpType'],'acctGrpPopup');		
						
						if (selectedAcctGrp.data['runMode'] != _controller.ADD) 
						{
							popup.getField('grpType').disableField();
							popup.getField('deff').disableField();
						}

						break;
					}

					case _controller.DEL:
					{
						var selectedAcctGrp = _grids['acctGrp'].getSelectedRecord();
						popup.uuid = selectedAcctGrp.data['acctGrpUUID'];
						
						if (Ext.isEmpty(selectedAcctGrp.data['grpId']))
						{
							popup.getField('grpId').hide();
						}else{
							popup.getField('grpId').show();
							popup.getField('grpId').setValue(selectedAcctGrp.data['grpId']);
							popup.getField('grpId').disableField();
						}

						popup.getField('grpType').setValue(selectedAcctGrp.data['grpType']);
						popup.getField('grpId').setValue(selectedAcctGrp.data['grpId']);
						popup.getField('grpId').allowBlank = true;
						popup.getField('grpDesc').setValue(selectedAcctGrp.data['grpDesc']);
						popup.getField('grpDesc').allowBlank = true;
						popup.getField('deff').setValue(selectedAcctGrp.data['deff']);
						popup.getField('stopDate').setValue(selectedAcctGrp.data['stopDate']);
						popup.getField('grpStat').setValue(selectedAcctGrp.data['grpStat']);
						popup.getField('grpRemark').setValue(selectedAcctGrp.data['grpRemark']);
						popup.getField('grpRemark').hide();
						
						_controller.enableGrpStatus(_controller.getConfig(popup.getField('grpType').getValue(), "GrpStatusApplicable") == "YES");
						_controller.enablePrimaryAcct(parseInt(_controller.getConfig(popup.getField('grpType').getValue(), "PrimaryPerGroup")) > 0);
						_controller.populateGrpStatusByGrpType(popup.getField('grpType').getValue());	
			
						popup.getField('grpType').disableField();
						popup.getField('grpDesc').disableField();
						popup.getField('deff').disableField();
						popup.getField('stopDate').disableField();
						popup.getField('grpStat').disableField();
						popup.getField('grpRemark').disableField();
                        break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function()
			{
				var popup = _popups['acctGrpPopup'];
				var deff = popup.getField('deff').getValue();
				var stopDate = popup.getField('stopDate').getValue();

				// Validate all input fields before business checking
				var valid = popup.getField('grpType').isValid();
				valid = popup.getField('grpId').isValid() && valid;
				valid = popup.getField('grpDesc').isValid() && valid;
				valid = popup.getField('deff').isValid() && valid;
				valid = popup.getField('stopDate').isValid() && valid;
				
				//Germany client need acctGrp GrpID to be mandatory
				var grpIdMan =  false;
				var grpTypeVal = popup.getField('grpType').getValue();
				
				if((_controller.getConfig(grpTypeVal, "AcctGrpIDMan") == "YES") || (_controller.getConfig(grpTypeVal, "UniqueGrpDesc") == "YES")){
				    grpIdMan = true;
				}
				
				if (popup.getField('grpId').getValue() == "" && grpIdMan){
					popup.getField('grpId').markInvalid(_translationMap['FIELD_IS_REQUIRED']);
					return false;
				}
				
				if (popup.getField('grpDesc').getValue() == "" && _controller.getConfig(grpTypeVal, "DescMandatory")){
					popup.getField('grpDesc').markInvalid(_translationMap['FIELD_IS_REQUIRED']);
					return false;
				}

	            if (popup.getField('grpStat').getValue() == "" && _controller.getConfig(grpTypeVal, "GrpStatusApplicable")){
					popup.getField('grpStat').markInvalid(_translationMap['FIELD_IS_REQUIRED']);
					return false;
				}
				
				if (stopDate < deff){
					popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_LESS_THAN_DEFF']);
					return false;
				}

				//Germany client need acctGrp Description and GrpID to be unique
				if (_controller.getConfig(grpTypeVal, "UniqueGrpDesc") == "YES"  
					&& _popups['acctGrpPopup'].action != _controller.DEL) {

					var  grpIDInvalid = false;
					var  grpDescInvalid = false;
					var  popupUUID = _popups['acctGrpPopup'].uuid;
					//compare uniqueness acctGrpType&GrpID
					if(_popups['acctGrpPopup'].action == _controller.ADD) {
						var nDupTypeID = _grids['acctGrp'].getStore().queryBy(function(record){
								return (record.get('grpType') == popup.getField('grpType').getValue()
								&& record.get('grpId') == popup.getField('grpId').getValue().trim());
						});
						if (nDupTypeID.length > 0 ) {
							popup.getField('grpId').markInvalid(_translationMap['ERR_DUPLICATED_ACCTGRP']);
							grpIDInvalid = true;
						}
					}
					//compare uniqueness acctGrpType&GrpDesc
					var nDupTypeDesc = _grids['acctGrp'].getStore().queryBy(function(record){
								return (record.get('grpType') == popup.getField('grpType').getValue()
								&& record.get('grpDesc') == popup.getField('grpDesc').getValue().trim()
								&& record.get('acctGrpUUID') != popupUUID);
					});
					if (nDupTypeDesc.length > 0 ) {
						popup.getField('grpDesc').markInvalid(_translationMap['ERR_DUPLICATED_ACCTGRPDESC']);
						grpDescInvalid = true;
					}
					//return invalid for duplication
					if (grpIDInvalid  || grpDescInvalid) {
						return false;
					}
				}
				
				if (valid)
				{
					switch (popup.getField('grpType').getValue()){
						case 'PW': 
						{
							var curBusDate = DesktopWeb.Util.stringToDate(_controller.getDefault('curBusDate'), DesktopWeb.Util.getDateDisplayFormat());
							var defaultStopDate = DesktopWeb.Util.stringToDate(_controller.getDefault('stopDate'), DesktopWeb.Util.getDateDisplayFormat());
							
							var chkDeff = (popup.action == _controller.ADD);
							
							if (!chkDeff && popup.action == _controller.MOD){
								var selectedAcctGrp = _grids['acctGrp'].getSelectedRecord();
								if (selectedAcctGrp.data['runMode'] == _controller.ADD) chkDeff = true;
							}
							
							if (chkDeff){
								if (deff < curBusDate){
									popup.getField('deff').markInvalid(_translationMap['ERR_DEFF_CANNOT_LESS_THAN_CURBUSDATE']);
									valid = false;
								}else if (deff > curBusDate && deff < defaultStopDate){
									popup.getField('deff').markInvalid(_translationMap['ERR_DEFF_CANNOT_FUTUREDATE']);
									valid = false;
								}
							}

							if (stopDate < curBusDate){
								popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDATE']);
								return false;
							}else if (stopDate > curBusDate && stopDate < defaultStopDate){
								popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_FUTUREDATE']);
								return false;
							}
						}
					}
				}
				
				if (_popups['acctGrpPopup'].action == _controller.ADD && _controller.getConfig(grpTypeVal, "GroupIdNumVdln")) {
				    if(!_controller.isNumber(popup.getField('grpId').getValue())){
					popup.getField('grpId').markInvalid(_translationMap['NUMERIC_VALUE_ALLOWED']);
					return false;
				    }
				}
				
				if(_popups['acctGrpPopup'].action == _controller.ADD && _controller.getConfig(grpTypeVal, "UniqueGroupId")) {
					var nDupTypeID = _grids['acctGrp'].getStore().queryBy(function(record){
							return (record.get('grpType') == popup.getField('grpType').getValue()
							&& record.get('grpId') == popup.getField('grpId').getValue().trim());
					});
					if (nDupTypeID.length > 0 ) {
						popup.getField('grpId').markInvalid(_translationMap['ERR_DUPLICATED_ACCTGRP']);
						return false;
					}
				}
				
				return valid;
			}
			,getData: function()
			{
				var popup = _popups['acctGrpPopup'];
				var data = {};
				data['acctGrpUUID'] = popup.uuid;
				data['grpType'] = popup.getField('grpType').getValue();
				data['grpId'] = popup.getField('grpId').getValue().trim();
				data['grpDesc'] = popup.getField('grpDesc').getValue().trim();
				data['deff'] = popup.getField('deff').getDisplayDateString();
				data['stopDate'] = popup.getField('stopDate').getDisplayDateString();
				data['grpStat'] = popup.getField('grpStat').getValue();
				data['grpRemark'] = popup.getField('grpRemark').getValue();
				data['runMode'] = popup.action;
				return data;
			}
		})		
		,linkedAcctPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 450
			,closeAction: 'hide'	
			,autoHeight: true				
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					html: _translationMap['DeleteConfirmMsg']
					,style: 'text-align:center;font-weight:bold; font-size: 12px; padding:4px'	
				}
				,{
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 150
					,items: [ 
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'grpType'
							,fieldLabel: _translationMap['GroupType']
							,width: 170
							,editable: true
							,allowBlank: false
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'grpId'
							,fieldLabel: _translationMap['GroupID']
							,width: 170
							,maxLength: 15
						}) 
						,new DesktopWeb.Controls.TextField({
							itemId: 'grpDesc'
							,fieldLabel: _translationMap['GroupDesc']
							,width: 170
							,maxLength: 40
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'account'
							,fieldLabel: _translationMap['Account']
							,smartview: 'accountSearch'				
							,fields: ['displayValue', 'acctNum', 'othRef']
							,valueField: 'acctNum'	
							,displayField: 'displayValue'								
							,width: 250
							,allowBlank: false
							,addtlSearchParams: [{name: 'incAllStat', valueFn: function(){return 'yes'}}]
							,listeners: {
								populated: function(fld, rec){
									var popup = _popups['linkedAcctPopup'];
									popup.enableButton('okBtn');
									var grpType = popup.getField('grpType').getValue();
									if (_controller.AFTACCTGRPTYPE == grpType) {
									   popup.getField('acctOtherRefNum').reset();
									   if (rec.data['othRef'].length > 0) {
										  popup.getField('acctOtherRefNum').setValue(rec.data['othRef']);
									   }
									}
								}
								,cleared: function(){
									var popup = _popups['linkedAcctPopup'];
									popup.disableButton('okBtn');
								}
							}
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'acctOtherRefNum'
							,fieldLabel: _translationMap['OtherReferenceNumberPopUp']
							,labelStyle: 'white-space:nowrap;'
							,smartview: 'accountSearch'				
							,fields: ['displayValue', 'othRef', 'acctNum']
							,valueField: 'displayValue'	
							,displayField: 'displayValue'							
							,width: 250
							,allowBlank: true
							,listeners: {
								populated: function(fld, rec) {
									var popup = _popups['linkedAcctPopup'];
									popup.enableButton('okBtn');
									popup.getField('account').reset();
									if (rec.data['othRef'].length >= 0) {
										popup.getField('account').setValue(rec.data['acctNum']);
										popup.getField('account').setRawValue(rec.data['displayValue']);
										popup.getField('acctOtherRefNum').setValue(rec.data['othRef']);
									}
								}
								,cleared: function() {
									var popup = _popups['linkedAcctPopup'];
									popup.disableButton('okBtn');
								}
							}
						})
						,new DesktopWeb.Controls.YesNoComboBox({
							itemId: 'primaryAcct'
							,width: 100									
							,fieldLabel: _translationMap['PrimaryAcct']
							,hideLabel: false																				
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'deff'
							,fieldLabel: _translationMap['EffDate']
							,allowBlank: false
							,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
						})
						,new DesktopWeb.Controls.DateField({
							itemId: 'stopDate'
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
						if (_popups['linkedAcctPopup'].isValid()){
							_controller.validateLinkedAcct(_popups['linkedAcctPopup'].getData(), _popups['linkedAcctPopup'].action);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['linkedAcctPopup'].hide();}
				})
			]
			,init: function(action)
			{
				// initialize popup based on action
				var popup = _popups['linkedAcctPopup'];
				popup.action = action;
				switch(action)
				{
					case _controller.ADD:
					{
						popup.setTitle(_translationMap['LinkedAccount'] + ' - ' + _translationMap['Add']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.MOD:
					{
						popup.setTitle(_translationMap['LinkedAccount'] + ' - ' + _translationMap['Modify']);
						popup.populate(action);
						popup.get(0).hide();
						break;
					}
					case _controller.DEL:
					{
						popup.setTitle(_translationMap['LinkedAccount'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						popup.get(0).show();
						break;
					}
				}
			}
			,populate: function(action)
			{
				var popup = _popups['linkedAcctPopup'];
				var primPerGrp = null;
				popup.clearAllFields();
				popup.enableAllFields();
				var selectedGrp = _grids['acctGrp'].getSelectedRecord();
				_controller.setAcctGrpMaxLengthFromConfig(selectedGrp.data['grpType'],'linkedAcctPopup');
				switch(action)
				{
					case _controller.ADD:
					{
						popup.uuid = _controller.getNewLinkedAcctUUID();
						popup.getField('grpType').setValue(selectedGrp.data['grpType']);
						popup.getField('grpType').disableField();
						//ACBRLK Germany account group type
						if (_controller.AFTACCTGRPTYPE == selectedGrp.data['grpType']) {
							_controller.setStartStopDate(selectedGrp.data['grpType'], 'linkedAcctPopup');
						} else {
							popup.getField('deff').setValue(_controller.getDefault('curBusDate'));
						    popup.getField('stopDate').setValue(_controller.getDefault('stopDate'));
						}
						_controller.setLinkedAcctPopUpForACBRLK();
						_controller.enableDisableDates(selectedGrp.data['grpType'],'linkedAcctPopup');
						_controller.enableGrpDesc(selectedGrp.data['grpType'],'linkedAcctPopup');

						if (Ext.isEmpty(selectedGrp.data['grpId']))
						{
							popup.getField('grpId').hide();
						}else{
							popup.getField('grpId').setValue(selectedGrp.data['grpId']);
							popup.getField('grpId').disableField();
						}
						popup.getField('grpDesc').setValue(selectedGrp.data['grpDesc']);
						popup.getField('grpDesc').disableField();
						popup.getField('account').reset();
						popup.getField('acctOtherRefNum').reset();
						
						primPerGrp = _controller.getConfig(popup.getField('grpType').getValue(), "PrimaryPerGroup");
						_controller.enablePrimaryAcct(primPerGrp != "" && (primPerGrp) > 0);	
						
						popup.getField('primaryAcct').setValue(_controller.getDefault('primaryAcct'));	
						
						break;
					}
					
					case _controller.MOD:
					{
						var selectedLinkedAcct = _grids['linkedAcct'].getSelectedRecord();
						popup.uuid = selectedLinkedAcct.data['lnkAcctUUID'];
						popup.getField('grpType').setValue(selectedGrp.data['grpType']);
						if (Ext.isEmpty(selectedGrp.data['grpId']))
						{
							popup.getField('grpId').hide();
						}else{
							popup.getField('grpId').setValue(selectedGrp.data['grpId']);
							popup.getField('grpId').disableField();
						}
						_controller.loadAccountSuggestField(selectedLinkedAcct.data['acct']);

						//ACBRLK Germany account group type
						if (_controller.AFTACCTGRPTYPE == selectedGrp.data['grpType']) {	
							_controller.setStartStopDate(selectedGrp.data['grpType'], 'linkedAcctPopup');
						} else {
							popup.getField('deff').setValue(selectedLinkedAcct.data['deff']);
							popup.getField('stopDate').setValue(selectedLinkedAcct.data['stopDate']);
						}
						_controller.setLinkedAcctPopUpForACBRLK();
						_controller.enableDisableDates(selectedGrp.data['grpType'],'linkedAcctPopup');
						_controller.enableGrpDesc(selectedGrp.data['grpType'],'linkedAcctPopup');
						
						popup.getField('grpDesc').setValue(selectedGrp.data['grpDesc']);
						popup.getField('grpDesc').disableField();
						popup.getField('grpType').disableField();
						if (selectedLinkedAcct.data['runMode'] != _controller.ADD) 
						{
							popup.getField('account').disableField();
							popup.getField('deff').disableField();
						}
						
						primPerGrp = _controller.getConfig(popup.getField('grpType').getValue(), "PrimaryPerGroup");
						_controller.enablePrimaryAcct((primPerGrp != "" && parseInt(primPerGrp) > 0));	
						popup.getField('primaryAcct').setValue(selectedLinkedAcct.data['primaryAcct']);	
						
						break;
					}

					case _controller.DEL:
					{
						var selectedLinkedAcct = _grids['linkedAcct'].getSelectedRecord();
						popup.uuid = selectedLinkedAcct.data['lnkAcctUUID'];
						popup.getField('grpType').setValue(selectedGrp.data['grpType']);
						popup.getField('grpId').setValue(selectedGrp.data['grpId']);
						popup.getField('grpDesc').setValue(selectedGrp.data['grpDesc']);

						popup.getField('account').setValue(selectedLinkedAcct.data['acct']);
						//setValue for otherReferenceNubmer, and dynamic show/hide
						popup.getField('acctOtherRefNum').setValue(selectedLinkedAcct.data['othRef']);
						_controller.setLinkedAcctPopUpForACBRLK();
						_controller.enableGrpDesc(selectedGrp.data['grpType'],'linkedAcctPopup');

						if (selectedLinkedAcct.data['runMode'] != _controller.ADD) 
						{
							popup.getField('primaryAcct').hide();
						}
						_controller.loadAccountSuggestField(selectedLinkedAcct.data['acct']);
						popup.getField('deff').setValue(selectedLinkedAcct.data['deff']);
						popup.getField('stopDate').setValue(selectedLinkedAcct.data['stopDate']);
						
						popup.getField('grpType').disableField();
						popup.getField('account').disableField();
						popup.getField('deff').disableField();
						popup.getField('stopDate').disableField();
						
						primPerGrp = _controller.getConfig(popup.getField('grpType').getValue(), "PrimaryPerGroup");
						_controller.enablePrimaryAcct((primPerGrp != "" && parseInt(primPerGrp) > 0));	
						popup.getField('primaryAcct').setValue(selectedLinkedAcct.data['primaryAcct']);
						popup.getField('primaryAcct').disableField();
						
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			,isValid: function()
			{
				var valid = true;
				var popup = _popups['linkedAcctPopup'];
				var curBusDate = DesktopWeb.Util.stringToDate(_controller.getDefault('curBusDate'), DesktopWeb.Util.getDateDisplayFormat());
				var defaultStopDate = DesktopWeb.Util.stringToDate(_controller.getDefault('stopDate'), DesktopWeb.Util.getDateDisplayFormat());
				var deff = popup.getField('deff').getValue();
				var stopDate = popup.getField('stopDate').getValue();
				var acctNum = popup.getField('account').getValue();
				var primPerGrp = null;

				if (!popup.getField('account').isValid() || !acctNum || acctNum.length <= 0 )
				{
					return false;
				} 

				//Validate duplicated account in popUp stage only for AFT account group
				if (_controller.AFTACCTGRPTYPE == popup.getField('grpType').getValue()) {
					if (_popups['linkedAcctPopup'].action == _controller.ADD) {
						var  acctInvalid = false;
						var nDupAcct = _grids['linkedAcct'].getStore().queryBy(function(record){
							return record.get('acct') == popup.getField('account').getValue();
						});
						if (nDupAcct.length > 0 ) {
							popup.getField('account').markInvalid(_translationMap['ERR_DUPLICATED_ACCTGRPMEMBER']);
							acctInvalid = true;
						}
						if (acctInvalid) {
							return false;
						}
					}
				}
				
				primPerGrp = _controller.getConfig(popup.getField('grpType').getValue(), "PrimaryPerGroup");
	            if (primPerGrp != "" && parseInt(primPerGrp) > 0 && popup.getField('primaryAcct').getValue() == ""){
					popup.getField('primaryAcct').markInvalid(_translationMap['FIELD_IS_REQUIRED']);
					return false;
				}
				
				switch (popup.getField('grpType').getValue()){
					case 'PW': 
					{
						var chkDeff = false;
											
						if (popup.action == _controller.ADD) chkDeff = true;
						
						if (popup.action == _controller.MOD){
							var selectedLinkedAcct = _grids['linkedAcct'].getSelectedRecord();
							chkDeff = (selectedLinkedAcct.data['runMode'] == _controller.ADD);
						}
						
						if (chkDeff){
							if (deff < curBusDate){
								popup.getField('deff').markInvalid(_translationMap['ERR_DEFF_CANNOT_LESS_THAN_CURBUSDATE']);
								valid = false;
							}else if (deff > curBusDate && deff < defaultStopDate){
								popup.getField('deff').markInvalid(_translationMap['ERR_DEFF_CANNOT_FUTUREDATE']);
								valid = false;
							}
						}
						
						if (stopDate < curBusDate){
							popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDATE']);
							valid = false;
						}else if (stopDate > curBusDate && stopDate < defaultStopDate){
							popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_MORE_THAN_CURBUSDATE']);
							valid = false;
						}
						
						if (valid)
						{
							var selectedGrp = _grids['acctGrp'].getSelectedRecord();
							var grpDeff = DesktopWeb.Util.stringToDate(selectedGrp.data['deff'], DesktopWeb.Util.getDateDisplayFormat());
							var grpStopDate = DesktopWeb.Util.stringToDate(selectedGrp.data['stopDate'], DesktopWeb.Util.getDateDisplayFormat());
							if (chkDeff){
								if (deff < grpDeff){
									popup.getField('deff').markInvalid(_translationMap['ERR_ACCT_DEFF_CANNOT_LESS_THAN_GRP_DEFF']);
									valid = false;
								}else if (deff > grpStopDate){
									popup.getField('deff').markInvalid(_translationMap['ERR_ACCT_DEFF_CANNOT_MORE_THAN_GRP_STOPDATE']);
									valid = false;
								}
							}
							if (stopDate > grpStopDate)
							{
								popup.getField('stopDate').markInvalid(_translationMap['ERR_ACCT_STOPDATE_CANNOT_MORE_THAN_GRP_STOPDATE']);
								valid = false;
							}
						}
					}
				}
				
				if (stopDate < deff){
					popup.getField('stopDate').markInvalid(_translationMap['ERR_STOPDATE_CANNOT_LESS_THAN_DEFF']);
					valid = false;
				}
				
				return valid;
			}
			,getData: function()
			{
				var popup = _popups['linkedAcctPopup'];
				var data = {};
				data['lnkAcctUUID'] = popup.uuid;
				data['grpType'] = popup.getField('grpType').getValue();
				data['grpId'] = popup.getField('grpId').getValue();
				data['acct'] = popup.getField('account').getValue();
				data['othRef'] = popup.getField('acctOtherRefNum').getValue();
				data['deff'] = popup.getField('deff').getDisplayDateString();
				data['stopDate'] = popup.getField('stopDate').getDisplayDateString();
				data['primaryAcct'] = popup.getField('primaryAcct').getValue();
				data['runMode'] = popup.action;
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
		
		,buttons: _buttons
		
		,fields: _fields
		
		,grids: _grids
		
		,popups: _popups
		
		
		,layout: new Ext.Container(			
			{
				height: _layoutHeight
				,width: _layoutWidth
                ,style: 'padding-left:5px; padding-right:5px;'
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
								columnWidth: 0.32
								,items: [
									_fields['searchValue']
								]
							}
							,{								
								columnWidth: 0.10
								,items: [
									_buttons['searchBtn']
								]
							}
							,{								
								columnWidth: 0.10
								,items: [
									_buttons['resetBtn']
								]
							}
						]
					}
					,_fields['acctGrpStat']
					,_grids['acctGrp']
					,_fields['linkedAcctStat']
					,_grids['linkedAcct']
				]																				
			}
		)
		
		,screenButtons: [			
			new DesktopWeb.Controls.ScreenButton({
				text: _translationMap['OK']
				,handler: function(){
					if (_controller.updatesFlag){
						_controller.doCommitValidate();
						//DesktopWeb.Util.commitScreen();
					}else{
						DesktopWeb.Util.cancelScreen();
					}
				}
			})
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Close']
					,handler: function(){
						if (_controller.updatesFlag){
							DesktopWeb.Util.displayDiscardPrompt(cancelScreen);
						}else{
							cancelScreen(true);
						}
						function cancelScreen(confirm){
							if (confirm) DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
		]			
	}
}