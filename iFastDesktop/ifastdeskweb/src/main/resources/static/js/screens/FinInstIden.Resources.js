/*********************************************************************************************
 * @file	FinInstIden.Resources.js	
 * @author	Narin Suanlamyai	
 * @desc	Resources JS file for Identification Maintenance screen.
 *********************************************************************************************/
/*
 * Procedure: FinInstIden.Resources.js
 *
 * Purpose  : Resources file for Financial Institution Identification screen
 *             
 * Notes    : Setup Financial Institution Identification
 *            - Open screen from 
 *               Menu -> System Maintenance -> Financial Institution Identification
 *
 * History  :  
 *		18 Jul 2013 N. Suanlamyai P0193400 T53802
 *					- Created
 *
 *		23 Aug 2013 G. Thawornwachirakun P0193400 DFT0014730 T54066
 *					- Remove validate GIIN format
 *          - Add warnMsg and display warning message on grid
 *
 *    09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// content dimensions
	var _layoutHeight = 400;
	var _layoutWidth = 660;
	var _searchIDFieldWidth = 275;
	var _searchIDFieldPopupWidth = 275;
	var _labelDetlWidth = 200;
	
	var _runningTmpIdentUUID = 0;
	
	// **** buttons ****
	var _buttons = {
		searchBtn: new DesktopWeb.Controls.ActionButton({																						
			text: _translationMap['Search']
			,style: "position:absolute; right:0px; top:0px;"
			,listeners: {
				click: function(){
					if( _controller.screenHasChanged() ){
						DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
													
						function handlePromptMsg(btn){
							if(btn){
								_controller.updatesFlag = false;
								_controller.clickHandle_searchBtn();
							}
						}
					}else{
						_controller.clickHandle_searchBtn();
					}
				}
			}
		})		
	}
	
	// **** fields ****
	var _fields = {
		searchFor: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'searchID'
			,fieldLabel: _translationMap["SearchFor"]
			,editable: false
			,width: 120
			,listeners: {
				select: function(combo, record, index){
					_controller.selectHandle_LevelField(record.data.code);
				}
			}
		})
		,searchByFund: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFund'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'fundOnlySearch'
			,addtlSearchParams: [{name: 'inclInactive', valueFn: function(){return 'yes'}}]
			,fields: ['fundCode', 'fndDisp' ]
			,valueField: 'fundCode'
			,displayField: 'fndDisp'
			,emptyText: _translationMap["SearchByFund"]
		})
		,searchByFundGroup: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFundGroup'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'fundGroupSearch'
			,addtlSearchParams: [{name: 'fundGroupType', valueFn: function(){return 'FATCA'}}]
			,fields: ['fundGroupCode', 'fundGroupType', 'displayValue' ]
			,valueField: 'fundGroupCode'
			,displayField: 'displayValue'
			,emptyText: _translationMap["SearchByFundGroup"]
		})
		,searchByLegalEntity: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByLegalEntity'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'entWhereUsedSearch'
			,addtlSearchParams: [{name: 'entityWhereused', valueFn: function(){return '15'}}]
			,fields: ['whereUseKey', 'displayValue']
			,valueField: 'whereUseKey'
			,displayField: 'displayValue'	
			,emptyText: _translationMap["SearchByLegalEntity"]
		})
		,searchByBroker: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByBroker'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'brokerSearch'
			,fields: ['agencyCode', 'displayValue' ]
			,valueField: 'agencyCode'
			,displayField: 'displayValue'
			,emptyText: _translationMap["SearchByBroker"]
		})
		,searchByIntermediary: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByIntermediary'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'intrSearch'
			,fields: ['intrCode', 'displayValue' ]
			,valueField: 'intrCode'
			,displayField: 'displayValue'
			,emptyText: _translationMap["SearchByIntermediary"]
		})
		,levelLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Level']
			,width: _labelDetlWidth
		})
		,identifierLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Code']
			,width: _labelDetlWidth
		})
		,idTypeLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['IDType']
			,width: _labelDetlWidth + 50
		})
		,idValueLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['IDValue']
			,width: _labelDetlWidth
		})
		,deffLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['EffectiveDate']
			,width: _labelDetlWidth - 20
		})
		,stopDateLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['StopDate']
			,width: _labelDetlWidth - 20
		})
		
		,cntryLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['CountryOfIssue']
			,width: _labelDetlWidth - 20
		})
		,statusLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Status']
			,width: _labelDetlWidth -20
		})
	}
	
	// **** grids ****
	var _grids = {
		identGrd: new DesktopWeb.AdvancedControls.GridPanel({							
			width: _layoutWidth
			,autoScroll: true							
			,height: 175
			,autoExpandColumn: 'code'
			,store: new Ext.data.XmlStore({
				record: 'Identification'					
				,fields: ['uuid', 'level','code', 'displayValue', 'groupType', 'idType','idValue','cntryOfIssue'
							,'deff','stopDate','idStat','allowMod', 'allowDel', 'version'
							,'errmsg', 'runMode', 'userName', 'processDate', 'modUser', 'modDate'
							,'warnMsg'
						]
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							Ext.data.Record.id(record);
							
							record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
							record.data.stopDate = DesktopWeb.Util.getDateDisplayValue(record.data.stopDate);
							record.data.processDate = DesktopWeb.Util.getDateDisplayValue(record.data.processDate);
							record.data.modDate = DesktopWeb.Util.getDateDisplayValue(record.data.modDate);
						});
						
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
						_grids['identGrd'].selectFirstRecord();
					}
					,update: function(store)
					{
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
					}	
					,add: function(store, records, index)
					{
						Ext.each(records, function(record){Ext.data.Record.id(record)});
					}
					,clear: function(store, records)
					{
						_controller.selectIdentification(null);
					}
				}					
			})
			,selModel: new Ext.grid.RowSelectionModel({					
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.selectIdentification(record);}					
				}				
			})
			,colModel: new Ext.grid.ColumnModel({
				defaults: {
					menuDisabled: true
				}

				,columns: [
					{width: 25
						,renderer: function(val, metaData, record) 
							{
								if (record.data['errMsg'] )
									return DesktopWeb.Util.buildErrorFlag(record.data['errMsg'] );
								else if (record.data['warnMsg'] )
									return DesktopWeb.Util.buildWarningFlag(record.data['warnMsg'] )
								else return '';
							}
					}
					,{header: _translationMap['Level'], dataIndex: 'level', width: 65
						,renderer: function(val, metaData, record){return _controller.getListDisplay('levelList', val)}
					}
					,{header: _translationMap['Code'], id:'code', dataIndex: 'code'}					
					,{header: _translationMap['IDType'], dataIndex: 'idType', width: 80
						,renderer: function(val, metaData, record){return _controller.getIDTypeDisplay(record.get('level'), val)}
					}
					,{header: _translationMap['IDValue'], dataIndex: 'idValue', width: 80}
					,{header: _translationMap['CountryOfIssue'], dataIndex: 'cntryOfIssue', width: 100
						,renderer: function(val, metaData, record){return _controller.getListDisplay('cntryOfIssueList', val)}
					}
					,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width: 80}
					,{header: _translationMap['StopDate'], dataIndex: 'stopDate', width: 80}					
					,{header: _translationMap['Status'], dataIndex: 'idStat', width: 75
						,renderer: function(val, metaData, record){return _controller.getListDisplay('idStatusList', val)}
					}
				]							
			})
			,buttons: [					
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'								
					,text: _translationMap['Add']
					,handler: function(){_controller.clickHandle_openActionPopup(_popups['identPopup'], _controller.ADD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,disabled: true
					,handler: function(){_controller.clickHandle_openActionPopup(_popups['identPopup'], _controller.MOD);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,disabled: true
					,handler: function(){_controller.clickHandle_deleteBtnIdenGrd();}						
				})					
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,disabled: true
					,handler: function(){_controller.clickHandle_moreBtn();}							
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,disabled: true
					,handler: function(){_controller.openAdminPopup();}							
				})
				, new DesktopWeb.Controls.ActionButton({
					itemId: 'historicalBtn'
					,text:_translationMap['Historical']
					,disabled: true
					,handler: function(){_controller.openHistoryPopup();}
				})
			]				
		})		
	}
	
	// **** popups ****
	var _popups = {					
		identPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,uuid: null
			,allowMod: null
			,allowDel: null
			,version: null
			,runMode: null
			,width: 425
			,closeAction: 'hide'
			,title: ''
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					layout: 'form'																		
					,style: 'padding:4px'
					,defaults: {border: true}
					,labelWidth: 100
					,items: [
						new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pLevelFld'
							,fieldLabel: _translationMap['Level']
							,allowBlank: false
							,editable: true
							,width: 120
							,listeners: {
								select: function(combo, record, index){
									_controller.selectHandle_LevelFieldPopup(record.data.code);
								}
							}
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'pFundFld'
							,fieldLabel: _translationMap["Code"]
							,width: _searchIDFieldPopupWidth
							,smartview: 'fundOnlySearch'
							,addtlSearchParams: [{name: 'inclInactive', valueFn: function(){return 'yes'}}]
							,fields: ['fundCode', 'fndDisp' ]
							,valueField: 'fundCode'
							,displayField: 'fndDisp'
							,emptyText: _translationMap["EmptyText_Fund"]
							,allowBlank: false
							,hidden: true
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pFundGroupFld'
							,fieldLabel: _translationMap['Code']
							,allowBlank: false
							,editable: false
							,width: _searchIDFieldPopupWidth
							,allowBlank: false
							,emptyText: _translationMap["EmptyText_FundGroup"]
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'pLegalEntityFld'
							,fieldLabel: _translationMap["Code"]
							,width: _searchIDFieldPopupWidth
							,smartview: 'entWhereUsedSearch'
							,addtlSearchParams: [{name: 'entityWhereused', valueFn: function(){return '15'}}]
							,fields: ['whereUseKey', 'displayValue']
							,valueField: 'whereUseKey'
							,displayField: 'displayValue'	
							,emptyText: _translationMap["EmptyText_LegalEntity"]
							,allowBlank: false
							,hidden: true
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'pBrokerFld'
							,fieldLabel: _translationMap["Code"]
							,width: _searchIDFieldPopupWidth
							,smartview: 'brokerSearch'
							,fields: ['agencyCode', 'displayValue' ]
							,valueField: 'agencyCode'
							,displayField: 'displayValue'
							,emptyText: _translationMap["EmptyText_Broker"]
							,allowBlank: false
							,hidden: true
						})
						,new DesktopWeb.Controls.SuggestField({
							itemId: 'pIntermediaryFld'
							,fieldLabel: _translationMap["Code"]
							,width: _searchIDFieldPopupWidth
							,smartview: 'intrSearch'
							,fields: ['intrCode', 'displayValue' ]
							,valueField: 'intrCode'
							,displayField: 'displayValue'
							,emptyText: _translationMap["EmptyText_Intermediary"]
							,allowBlank: false
							,hidden: true
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pIdTypeFld'
							,fieldLabel: _translationMap['IDType']
							,allowBlank: false
							,editable: true
							,width: _searchIDFieldPopupWidth
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'pIdValueFld'
							,fieldLabel: _translationMap['IDValue']
							,width: _searchIDFieldPopupWidth
							,allowBlank: false
						})
						,{
							layout: 'column'
							,border: false
							,defaults: {
								layout: 'form'
								,border: false
							}
							,items: [
								{
									// Col#1
									columnWidth: 0.55
									,items :[
										new DesktopWeb.Controls.DateField({
											itemId: 'pDeffFld'
											,fieldLabel: _translationMap['EffectiveDate']
											,allowBlank: false
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										})
									]
								}
								,{
									// Col#2
									columnWidth: 0.45
									,labelWidth: 65
									,items :[
										new DesktopWeb.Controls.DateField({
											itemId: 'pStopDateFld'
											,fieldLabel: _translationMap['StopDate']
											,allowBlank: false
											,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
										})
									]
								}
							]
						}
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pCntryFld'
							,fieldLabel: _translationMap['CountryOfIssue']
							,width: _searchIDFieldPopupWidth
							,editable: true
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pStatusFld'
							,fieldLabel: _translationMap['Status']
							,width: 120
							,allowBlank: false
							,editable: true
						})
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){
						_controller.clickHandle_okBtnOnIdenPopup(_popups['identPopup']);
					}
				}) 
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['identPopup'].hide();}
				})
			]
			,init: function(action)
			{
				this.action = action;	
				this.uuid = null;
				this.version = null;
				this.allowMod = null;
				this.allowDel = null;
				this.runMode = null;
				switch(action){
					case _controller.ADD:{
						this.setTitle(_translationMap['IdentificationDetails'] + " - " + _translationMap['Add']);
						break;
					}
					case _controller.MOD:{
						this.setTitle(_translationMap['IdentificationDetails'] + " - " + _translationMap['Modify']);
						break;
					}
					case _controller.DEL:{
						this.setTitle(_translationMap['IdentificationDetails'] + " - " + _translationMap['Delete']);
						break;
					}
				}
				this.reset();
			}
			,reset: function()
			{
				this.clearAllFields();
				this.enableAllFields();
				this.action = null;
				this.uuid = null;
				this.version = null;
				this.allowMod = null;
				this.allowDel = null;
				this.runMode = null;
				if ( this.rendered )
				{
					this.getField('pLevelFld').setValue('');
					this.getField('pFundFld').setValue('');
					this.getField('pFundGroupFld').setValue('');
					this.getField('pLegalEntityFld').setValue('');
					this.getField('pBrokerFld').setValue('');
					this.getField('pIntermediaryFld').setValue('');
					this.getField('pIdTypeFld').setValue('');
					this.getField('pIdValueFld').setValue('');
					this.getField('pDeffFld').setValue(_controller.defaultValues['deff']);
					this.getField('pStopDateFld').setValue(_controller.defaultValues['stopDate']);
					this.getField('pCntryFld').setValue('');
					this.getField('pStatusFld').setValue('');
					this.clearInvalid();
				}
			}
			,populate: function(record, action)
			{
				this.reset();
				this.action = action;
				if ( action == _controller.ADD ) {
					// Set default values
					this.uuid = 'tmpIdentUUID' + (++_runningTmpIdentUUID);
					this.version = '1';
					this.allowMod = 'yes';
					this.allowDel = 'yes';
					this.runMode = _controller.ADD;

					var selectedRecord = _grids['identGrd'].getSelectedRecord();
					var level = _controller.defaultValues['level'];
					var idType = _controller.defaultValues['idType'];
					var searchFor = _fields['searchFor'].getValue();
					if ( selectedRecord )
					{
						level = selectedRecord.get('level');
					}else if ( searchFor && searchFor.length > 0 ){
						level = searchFor;
					}
					this.getField('pLevelFld').setValue(level);
					_controller.selectHandle_LevelFieldPopup(level);
					this.getField('pDeffFld').setValue(_controller.defaultValues['deff']);
					this.getField('pStopDateFld').setValue(_controller.defaultValues['stopDate']);
				} 
        else if ( action == _controller.MOD ) 
        {
					this.uuid = record.get('uuid');
					this.version = record.get('version');
					this.allowMod = record.get('allowMod');
					this.allowDel = record.get('allowDel');
					this.runMode = ( record.get('runMode') == _controller.ADD )?_controller.ADD:_controller.MOD;
					this.getField('pLevelFld').setValue(record.get('level'));
					_controller.selectHandle_LevelFieldPopup(record.get('level'));
					_controller.loadSuggestFieldPopup(record.get('level'), record.get('code'), record.get('displayValue'));
					this.getField('pIdTypeFld').setValue(record.get('idType'));
					this.getField('pIdValueFld').setValue(record.get('idValue'));
					this.getField('pDeffFld').setValue(record.get('deff'));
					this.getField('pStopDateFld').setValue(record.get('stopDate'));
					this.getField('pCntryFld').setValue(record.get('cntryOfIssue'));
					this.getField('pStatusFld').setValue(record.get('idStat'));
					
					if ( record.get('runMode') != _controller.ADD ){
						this.getField('pLevelFld').disableField();
						this.getField('pFundFld').disableField();
						this.getField('pFundGroupFld').disableField();
						this.getField('pLegalEntityFld').disableField();
						this.getField('pBrokerFld').disableField();
						this.getField('pIntermediaryFld').disableField();
					}
				}
			}
			,clearInvalid: function()
			{
				this.getField('pLevelFld').clearInvalid();
				this.getField('pFundFld').clearInvalid();
				this.getField('pFundGroupFld').clearInvalid();
				this.getField('pLegalEntityFld').clearInvalid();
				this.getField('pBrokerFld').clearInvalid();
				this.getField('pIntermediaryFld').clearInvalid();
				this.getField('pIdTypeFld').clearInvalid();
				this.getField('pIdValueFld').clearInvalid();
				this.getField('pDeffFld').clearInvalid();
				this.getField('pStopDateFld').clearInvalid();
				this.getField('pCntryFld').clearInvalid();
				this.getField('pStatusFld').clearInvalid();
			}
			,isValid: function()
			{
				var valid = true;
				var level = this.getField('pLevelFld').getValue();
				
				this.clearInvalid();
				
				valid = this.getField('pLevelFld').isValid();
				
				switch ( level )
				{
					case _controller.IDENTLEVEL_FUND:
						valid = this.getField('pFundFld').isValid() && valid;
						break;
					case _controller.IDENTLEVEL_FUNDGROUP:
						valid = this.getField('pFundGroupFld').isValid() && valid;
						break;
					case _controller.IDENTLEVEL_LEGALENTITY:
						valid = this.getField('pLegalEntityFld').isValid() && valid;
						break;
					case _controller.IDENTLEVEL_BROKER:
						valid = this.getField('pBrokerFld').isValid() && valid;
						break;
					case _controller.IDENTLEVEL_INTERMEDIARY:
						valid = this.getField('pIntermediaryFld').isValid() && valid;
						break;
					default:
						valid = false;
				}
				valid = this.getField('pIdTypeFld').isValid() && valid;
				valid = this.getField('pIdValueFld').isValid() && valid;				

				valid = this.getField('pDeffFld').isValid() && valid;
				valid = this.getField('pStopDateFld').isValid() && valid;
				
				if ( this.getField('pDeffFld').isValid() && this.getField('pStopDateFld').isValid() )
				{
					if ( this.getField('pDeffFld').getValue() > this.getField('pStopDateFld').getValue() )
					{
						this.getField('pStopDateFld').markInvalid(_translationMap['ERROR_StopDateNotPriorEffectiveDate']);
						valid = false;
					}
				}
				
				valid = this.getField('pCntryFld').isValid() && valid;
				valid = this.getField('pStatusFld').isValid() && valid;
				
				return valid;
			}
			,getData: function()
			{
				var data = {};
				data['errMsg'] = "";
				data['warnMsg'] = "";
				
				data['uuid'] = this.uuid;
				data['version'] = this.version;
				data['allowDel'] = this.allowDel;
				data['allowMod'] = this.allowMod;
				data['level'] = this.getField('pLevelFld').getValue();
				switch ( this.getField('pLevelFld').getValue() )
				{
					case _controller.IDENTLEVEL_FUND:
						data['code'] = this.getField('pFundFld').getValue();
						data['displayValue'] = getDisplayValue(this.getField('pFundFld'), this.getField('pFundFld').getValue());
						data['groupType'] = _controller.BLANK;
						break;
					case _controller.IDENTLEVEL_FUNDGROUP:
						data['code'] = this.getField('pFundGroupFld').getValue();
						data['displayValue'] = this.getField('pFundGroupFld').getValueDesc();
						data['groupType'] = 'FATCA';
						break;
					case _controller.IDENTLEVEL_LEGALENTITY:
						data['code'] = this.getField('pLegalEntityFld').getValue();
						data['displayValue'] = getDisplayValue(this.getField('pLegalEntityFld'), this.getField('pLegalEntityFld').getValue());
						data['groupType'] = _controller.BLANK;
						break;
					case _controller.IDENTLEVEL_BROKER:
						data['code'] = this.getField('pBrokerFld').getValue();
						data['displayValue'] = getDisplayValue(this.getField('pBrokerFld'), this.getField('pBrokerFld').getValue());
						data['groupType'] = _controller.BLANK;
						break;
					case _controller.IDENTLEVEL_INTERMEDIARY:
						data['code'] = this.getField('pIntermediaryFld').getValue();
						data['displayValue'] = getDisplayValue(this.getField('pIntermediaryFld'), this.getField('pIntermediaryFld').getValue());
						data['groupType'] = _controller.BLANK;
						break;
					default:
						data['code'] = this.getField('pFundFld').getValue();
						data['displayValue'] = getDisplayValue(this.getField('pFundFld'), this.getField('pFundFld').getValue());
						data['groupType'] = _controller.BLANK;
				}
				data['idType'] = this.getField('pIdTypeFld').getValue();
				data['idValue'] = this.getField('pIdValueFld').getValue();
				
				data['deff']     = this.getField('pDeffFld').getDisplayDateString();				
				data['stopDate'] = this.getField('pStopDateFld').getDisplayDateString();
				
				data['cntryOfIssue'] = this.getField('pCntryFld').getValue();
				data['idStat'] = this.getField('pStatusFld').getValue();
				data['runMode'] = this.runMode;
				return data;

				function getDisplayValue(obj, code){
					var record = obj.findRecord(obj.valueField, code);		
					return (record != null ? record.get(obj.displayField) : null);
				}
			}
		})
		,admin: new DesktopWeb.AdvancedControls.PopupWindow({								
			width: 395				
			,closeAction: 'hide'			
			,modal: true
			,title: _translationMap['IdentificationDetails']+ ' - ' +_translationMap['Admin']
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
			,init: function(data)
			{
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
		
		,buttons: _buttons
		
		,popups: _popups
		
		,layout: new Ext.Container(
			{
				height: _layoutHeight
				,width: _layoutWidth
				,items: [
					{
						xtype: 'fieldset'
						,title: _translationMap['Search']
						,layout: 'column'
						,width: _layoutWidth
						,labelWidth: 65
						,defaults: {
							layout: 'form'
							,autoHeight:true
						}
						,items: [
							{
								// Row#1 Col#1
								columnWidth: 0.35
								,items :[
									_fields['searchFor']
								]
							}
							,{
								// Row#1 Col#2
								columnWidth: 0.65
								,items: [
									_fields['searchByFund']
									,_fields['searchByFundGroup']
									,_fields['searchByLegalEntity']
									,_fields['searchByBroker']
									,_fields['searchByIntermediary']
									,_buttons['searchBtn']
								]
							}
						]
					}
					,_grids['identGrd']
					,{
						xtype:'fieldset'
						,title: _translationMap['IdentificationDetails']
						,layout: 'column'
						,width: _layoutWidth
						,items: [
							{
								// Col#1
								layout: 'form'
								,columnWidth: 0.55
								,autoHeight:true
								,labelWidth: 60
								,items :[
									_fields['levelLabel']
									,_fields['identifierLabel']
									,_fields['idTypeLabel']
									,_fields['idValueLabel']
								]
							}
							,{
								// Col#2
								layout: 'form'
								,columnWidth: 0.45
								,autoHeight:true
								,labelWidth: 100
								,items :[
									_fields['deffLabel']
									,_fields['stopDateLabel']
									,_fields['cntryLabel']
									,_fields['statusLabel']
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
					,handler: function(){
						if( _controller.screenHasChanged() ){
							_controller.updatesFlag = true;
							_controller.doValidate();
						}else{
							_controller.updatesFlag = false;
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){
					if( _controller.screenHasChanged() ){
						DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
													
						function handlePromptMsg(btn){
							if(btn){
								_controller.updatesFlag = false;
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