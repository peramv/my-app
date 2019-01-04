/*********************************************************************************************
 * @file	FundBrokerLinkage.Resources.js
 * @author	Winnie Cheng
 * @desc	Resources JS file for Fund Group screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Fund Group Linkage
 *				
 *  History : 
 *
 *  23 Sep 2016 Winnie Cheng. P0256381  T83741 CHG0045765 Fund Broker Linkage for Germany
 *					- Created.
 *
 *  13 Oct 2016 Winnie Cheng. P0256381  T83939 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, layout adjustment and bug fixing
 *
 *  20 Oct 2016 Winnie Cheng. P0256381  T84056 CHG0045765 Fund Broker Linkage for Germany
 *					- few changes, imp. Delete error handing for fund broker linage
 *                  - Adding duplication validation in popUp stage
 *
 *  28 Oct 2016 Winnie Cheng. P0256381  T84097 DFT0068689 CHG0045765 Fund Broker Linkage for Germany
 *                  - Rewritten duplication validation by using store.queryBy
 *
 *  8 Nov 2016 Winnie Cheng. P0256381  T84187 DFT0069088 CHG0045765 Fund Broker Linkage for Germany
 *                  - change one column lable name
 *
 *  20 Nov 2016 Winnie Cheng. P0256381   CHG0045765 Fund Group for Germany
 *                  - Fund Group popUp added
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 550;
	var _layoutWidth = 740;
	
		// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({
			id: 'searchBtn'	
			,text: _translationMap['Search']
			,listeners: {
				click: function(){_controller.clickHandle_searchBtn();}
			}
		})	
		,resetBtn: new DesktopWeb.Controls.ActionButton({																						
			id: 'resetBtn'	
			,text: _translationMap['Reset']							
			,handler: function(){_controller.doReset();}
			,disabled: true										 																			
		})			
	}
	
	// **** fields ****
	var _fields = {
		acctGrpSearchBy: new DesktopWeb.Controls.SMVComboBox({ //Account/Grp Searchby dropdown
			itemId: 'acctGrpSearchBy'
			,fieldLabel: _translationMap['AcctGrpSearchBy']
			,labelStyle: 'white-space:nowrap;'					
			,width: 160
			,editable: true
			,allowBlank: true
			,listeners: {
				select: function(fld, record, index){ 
					var code = record.data['code'];
					if (code.length > 0){
						_fields['searchByAccts'].enable();
						_fields['searchByAcctGrp'].enable();
						_controller.handleAcctsGrpsSearchChange(code); 
						_controller.setAcctGroupCriterias(code, fld); 
					} else {
						_controller.resetFields('acctGrpSearchBy');
						_controller.resetFields('searchByAccts');
						_controller.resetFields('searchByAcctGrp');
						_controller.disableFields('searchByAccts');
						_controller.disableFields('searchByAcctGrp');
					}
				}
			}
		})
		
		,searchByAccts: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByAccts'
			,hideLabel: true
			,allowBlank: true
			,width: 420
			,smartview: 'accountSearch' 
			,fields: ['displayValue', 'acctNum', 'othRef']
			,valueField: 'acctNum'	
			,displayField: 'displayValue'	
			,hidden: false	
			,listeners: {
				select: function(fld, rec){
					_controller.getAcctOtherRefNumber(rec); 
				}	
			}
		}) 
		
		,searchByAcctGrp: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByAcctGrp'
			,hideLabel: true
			,allowBlank: true
			,width: 420
			,smartview: 'acctGroupSearch' 
			,addtlSearchParams: [{name: 'acctGroupType', valueFn: function(){return 'ACBRLK'}}]
			,fields: ['displayValue', 'acctGroupType', 'acctGroupCode', 'acctGroupDesc' ]
			,valueField: 'acctGroupCode'
			,displayField: 'displayValue'
			,hidden: true
			,listeners: {
				select: function(fld, rec){
					_controller.getAcctGrpDesc(rec); 
				}	
			}
		})
		
		//Fund Group Google search
		,fundGrpClassSearchBy: new DesktopWeb.Controls.SMVComboBox({ //Fund/Grp Searchby dropdown
			itemId: 'fundGrpClassSearchBy'
			,fieldLabel: _translationMap['FundGrpClassSearchBy']
			,labelStyle: 'white-space:nowrap'
			,width: 160			
			,allowBlank: true
			,listeners: {
				select: function(fld, record, index){ 
					var code = record.data['code'];
					if (code.length > 0){
						_fields['searchByFundClass'].enable();
						_fields['searchByFundGrp'].enable();
						_controller.handleFundGrpClassSearchChange(code);
						_controller.setFundGroupCriterias(); 
					} else {
						_controller.disableFields('searchByFundClass');
						_controller.disableFields('searchByFundGrp');
						_controller.resetFields('fundGrpClassSearchBy');
						_controller.resetFields('searchByFundClass');
						_controller.resetFields('searchByFundGrp');
						_controller.currentSearch['fund'] == '';
						_controller.currentSearch['class']  = '';
					}
				}
			}
		})
		
		,searchByFundClass: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFundClass'
			,hideLabel: true
			,allowBlank: true
			,width: 420
			,smartview: 'fundSearch'		
			,fields: ['displayValue', 'fund', 'class','isin', 'wkn']						
			,valueField: 'displayValue'
			,hidden: false
			,listeners: {
				select: function(fld, rec){ 
					_controller.getFundClassSuggestFields(rec); 
				}
			}
		})
		
		,searchByFundGrp: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFundGrp'
			,hideLabel: true
			,allowBlank: true
			,width: 420
			,smartview: 'fundGroupSearch'
			,addtlSearchParams: [{name: 'fundGroupType', valueFn: function(){return 'FNBRLK'}}]
			,fields: ['displayValue', 'fundGroupType', 'fundGroupCode','fundGroupDesc' ]
			,valueField: 'fundGroupCode'
			,hidden: true			
			,listeners: {
				select: function(fld, rec){
					_controller.getFundGrpDesc(rec); 
				}	
			}
		})
		
		,fundBrokerSearchBy: new DesktopWeb.Controls.SMVComboBox({//FundBroker Searchby dropdown
			itemId: 'fundBrokerSearchBy'
			,fieldLabel: _translationMap['FundBrokerSearchBy']
			,labelStyle: 'white-space:nowrap'
			,width: 160			
			,allowBlank: true
			,listeners: {
				select: function(fld, record, index){ 
					var code = record.data['code'];
					if (code.length > 0){
						_fields['searchByFundBroker'].enable();
						_controller.setFundBrokerCriterias(); 
					} else {
						_controller.resetFields('fundBrokerSearchBy');
						_controller.resetFields('searchByFundBroker');
						_controller.disableFields('searchByFundBroker');
					}
				}
			}
		})
		,searchByFundBroker: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFundBroker'
			,hideLabel: true
			,allowBlank: true
			,width: 420
			,smartview: 'fundBrokerSearch'
			,addtlSearchParams: [{name: 'EntityWhereUsed', valueFn: function(){return '01'}}, 
								 {name: 'Relationship', valueFn: function(){return '01'}}]
			,fields: ['displayValue', 'whereUseKey']
			,valueField: 'whereUseKey'	
			,displayField: 'displayValue'		
			,fields: ['whereUseKey', 'displayValue']
		})
	}
	
	// **** grids ****
	var _grids = {
		fndBrkLinkage: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth - 20
			,autoScroll: true							
			,height: _layoutHeight - 190
			,autoExpandColumn: 'acctGrpDesc'
			,autoExpandColumn: 'fundGrpDesc'
			,autoExpandColumn: 'fundBrokerName'
			,features: [{
				ftype: 'summary'
			}]
			,store: new Ext.data.XmlStore({
				record: 'FundBrokerElig'					
				,fields: [
					'errMsg', 'acctGroupID', 'acctGrpDesc', 'fundGroup', 'fundGrpDesc', 'fundBrokerCode', 'fundBrokerName', 
					'fundBrokerEligID', 'runMode']							
				,listeners: {
					load: function(store, records) {
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
						store.fireEvent('datachanged', store); //to set data in grid again
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
							_controller.selectlinkedFundBrk(record);
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
					,{header: _translationMap['AcctGroupID'], dataIndex: 'acctGroupID', width: 100}
					,{header: _translationMap['AcctGrpDesc'], id:'acctGrpDesc', dataIndex: 'acctGrpDesc', width: 130}
					,{header: _translationMap['FundGroupColn'], dataIndex: 'fundGroup', width: 100}
					,{header: _translationMap['FundGrpDesc'], id:'fundGrpDesc', dataIndex: 'fundGrpDesc', width: 130}
					,{header: _translationMap['FundBrokerCode'], dataIndex: 'fundBrokerCode', width: 100}
					,{header: _translationMap['FundBrokerName'], id:'fundBrokerName', dataIndex: 'fundBrokerName', width: 100}																							
				]							
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup(_controller.ADD);}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.openActionPopup( _controller.DEL);}
					,disabled: true
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'viewFundGroupBtn'
					,text: _translationMap['ViewFundGroup']
					,handler: function(){_controller.clickHandle_ViewFundGrpBtn();}
					,disabled: true
				})		
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,handler: function(){_controller.clickHandle_moreBtn()}
					,disabled: true
				})												
			]
		})							
	}
	
	// **** popups ****
	var _popups = {	
			fundGrpPopup: new DesktopWeb.AdvancedControls.PopupWindow({
            width: 678,
			height: 558,
			title: _translationMap['ViewFundGroup'],
            closeAction: 'hide',
            modal: true,
            defaults: {border:false, layout: 'fit'},
            items: [
                {
					xtype : "component",
					autoEl : {
						tag : "iframe",
						name: "iframePopup",
						width: "100%",
						height: "100%"
					}
				}
			],
            buttons: [
                new DesktopWeb.Controls.ActionButton({                                                                                        
                    itemId: 'closeFundGrpPopup',
                    text: _translationMap['Close'],
                    listeners: {
                        click: function () {
                            _popups['fundGrpPopup'].hide();
                        }
                    }                                                                                                                                                                                     
                })        
            ]
		})
		,fundBrkLink: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,width: 560
			,style: 'padding:5px'
			,closeAction: 'hide'	
			,autoHeight: true				
			,modal: true
			,defaults: {border:false}	
			,items: [{
					layout: 'form'					
					,style: 'padding:10px'
					,defaults: {border: true}
					,labelWidth: 90
					,items: [ 
						new DesktopWeb.Controls.SuggestField({
							itemId: 'acctGroupID'
							,fieldLabel: _translationMap['AccountGroup']
							,labelStyle: 'white-space:nowrap;'	
							,smartview: 'acctGroupSearch'	
										,addtlSearchParams: [{name: 'acctGroupType', valueFn: function(){return 'ACBRLK'}}]
							,valueField: 'acctGroupCode'
							,fields: ['displayValue', 'acctGroupCode', 'acctGroupType']
							,width: 390
							,editable: true
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'fundGroup'
							,fieldLabel: _translationMap['FundGroup']
							,labelStyle: 'white-space:nowrap;'	
							,smartview: 'fundGroupSearch'
							,addtlSearchParams: [{name: 'fundGroupType', valueFn: function(){return 'FNBRLK'}}]
							,valueField: 'fundGroupCode'	
							,fields: ['displayValue', 'fundGroupType', 'fundGroupCode' ]
							,width: 390
						}) 
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'fundBrokerCode'
							,fieldLabel: _translationMap['FundBroker']
							,labelStyle: 'white-space:nowrap;'	
							,smartview: 'fundBrokerSearch'				
							,addtlSearchParams: [{name: 'EntityWhereUsed', valueFn: function(){return '01'}}, {name: 'Relationship', valueFn: function(){return '01'}}]
							,fields: ['displayValue', 'whereUseKey']
							,valueField: 'whereUseKey'	
							,displayField: 'displayValue'						
							,width: 390
						})
					]						
				}													
			]
			
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						if (_popups['fundBrkLink'].isValid()) {
							_controller.validatefndBrkLinage(_popups['fundBrkLink'].getData(), _popups['fundBrkLink'].action);
						}
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'canBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['fundBrkLink'].hide();} 
				})
			]
			
			,init: function(action) {
				// initialize popup based on action
				var popup = _popups['fundBrkLink'];
				popup.action = action;
				switch(action)
				{
					case _controller.ADD: {
						popup.setTitle(_translationMap['TitlePopUp'] + ' - ' + _translationMap['Add']);
						popup.populate(action); 
						break;
					}

					case _controller.DEL: {
						popup.setTitle(_translationMap['TitlePopUp'] + ' - ' + _translationMap['Delete']);
						popup.populate(action);
						popup.disableAllFields();
						break;
					}
				}
			}
			
			,populate: function(action) {
				var popup = _popups['fundBrkLink'];
				popup.enableAllFields();
				
				switch(action) {
					case _controller.ADD: {
						popup.uuid = _controller.getNewFndBrkLinageUUID(); 
						popup.getField('acctGroupID').setValue('');
						popup.getField('fundGroup').setValue('');
						popup.getField('fundBrokerCode').setValue('');
						popup.get(0).show();
						
						break;
					}
					case _controller.DEL: {
						var selectedFndBrkLinkGrp = _grids['fndBrkLinkage'].getSelectedRecord();
						popup.uuid = selectedFndBrkLinkGrp.data['fundBrokerEligID'];
						popup.getField('acctGroupID').setValue(selectedFndBrkLinkGrp.data['acctGroupID']);
						popup.getField('fundGroup').setValue(selectedFndBrkLinkGrp.data['fundGroup']);
						popup.getField('fundBrokerCode').setValue(selectedFndBrkLinkGrp.data['fundBrokerCode']);
						
						popup.get(0).hide();
						_controller.validatefndBrkLinage(_popups['fundBrkLink'].getData(), _popups['fundBrkLink'].action);
						
						break;
					}
				}
				if (popup.rendered) popup.syncSize();
			}
			
			,isValid: function() {
				var valid = true;
				var popup = _popups['fundBrkLink'];
				
				if (popup.getField('acctGroupID').getValue().length < 1 ) {
					popup.getField('acctGroupID').markInvalid(_translationMap['FldRequired']);
					return false;
				} 
				if (popup.getField('fundGroup').getValue().length < 1 ) {
					popup.getField('fundGroup').markInvalid(_translationMap['FldRequired']);
					return false;
				} 
				if (popup.getField('fundBrokerCode').getValue().length < 1 ) {
					popup.getField('fundBrokerCode').markInvalid(_translationMap['FldRequired']);
					return false;
				} 
				
				//Germany client need validate the linkage in popUp stage
				if (_popups['fundBrkLink'].action == _controller.ADD) {
				
					var  fndBrkLinkageInvalid = false;

					var nDupFundLink = _grids['fndBrkLinkage'].getStore().queryBy(function(record){
						return (record.get('acctGroupID') == popup.getField('acctGroupID').getValue()
								&& record.get('fundGroup') == popup.getField('fundGroup').getValue()
								&& record.get('fundBrokerCode') == popup.getField('fundBrokerCode').getValue());
					});

					if (nDupFundLink.length > 0 ) {
						popup.getField('fundBrokerCode').markInvalid(_translationMap['ERR_DUPLICATED_FUNDBRKLINKAGE']);
						fndBrkLinkageInvalid = true;
					}
					if (fndBrkLinkageInvalid) {
						return false;
					}
				}
				
				return valid;
			}
			
			,getData: function() {
				var popup = _popups['fundBrkLink']; 
				var data = {};
				data['fundBrokerEligID'] = popup.uuid;
				data['acctGroupID'] = popup.getField('acctGroupID').getValue();
				data['fundGroup'] = popup.getField('fundGroup').getValue();
				data['fundBrokerCode'] = popup.getField('fundBrokerCode').getValue();
				return data;
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
		,buttons: _buttons
		
		,layout: new Ext.Container({
			height: _layoutHeight
			, width: _layoutWidth
			,style: 'padding-left:5px; padding-right:5px;'
			, items: [{
					xtype: 'fieldset'
					,title: _translationMap['Search']
					,items: [{
							// Search section
							layout: 'column'
							,defaults: {
								layout: 'form'
							}
							,items: [{
										columnWidth: 0.44
										,style: 'text-align: right'
										,items: [
											_fields['acctGrpSearchBy']
											,_fields['fundGrpClassSearchBy'] 
											,_fields['fundBrokerSearchBy']
									]}  
									,{
										columnWidth: 0.56
										,style: 'text-align: right'
										,items: [
											_fields['searchByAccts'], _fields['searchByAcctGrp']
											,_fields['searchByFundClass'], _fields['searchByFundGrp']
											,_fields['searchByFundBroker']
									]}
							]}
							,{
								layout: 'column'
								,defaults: {
									layout: 'form'
									,height: 30	
									,style: 'text-align:right;'
							}
							,items: [{								
									columnWidth: 0.90
									,items: [
										_buttons['searchBtn']
									]}
								,{								
									columnWidth: 0.1
									,items: [
										_buttons['resetBtn']
									]}
							]}
					]}
			 ,{
				xtype: 'fieldset'
				,title: 'Search Result'
				,width: _layoutWidth - 10
				,items: _grids['fndBrkLinkage']
			  }
			]
		})
		,screenButtons: {
			items:[
				new DesktopWeb.Controls.ScreenButton( {
						text: _translationMap['OK']
						,itemId: 'okBtn'
						,handler: function(){
							if (_controller.updatesFlag)
								_controller.doCommitValidate();
							else
								DesktopWeb.Util.cancelScreen();
						}
					}
				)
				,new DesktopWeb.Controls.ScreenButton( {
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
				})
			]
		}
	}
}