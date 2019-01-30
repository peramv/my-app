/*********************************************************************************************
 * @file	RDSPAccountInfo.Resources.js
 * @author	Balaji Rajendra babu
 * @desc	Resources JS file for RDSPAccountInfo.
 *********************************************************************************************/
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 750;
	var _layoutWidth = 750; 
	var _searchIDFieldWidth = 275;
	var _searchIDFieldPopupWidth = 230;
	var _reportingFFIFieldPopupWidth = 310;
	var _respWidth = 125;
	var _MARKET_CANADA = "CANADA";
	var _MARKET_LUX = "LUX";
	
	var _startValueIncepDate=null,_startValueReportESDC=null,_startValueGrant=null,_startValueBond=null,_startValueTransferred=null;
	var _flagIncepDate=null,_flagReportESDC=null,_flagGrant=null,_flagBond=null,_flagTransferred=null;
	var _startValueCertDate=null, _startValueTransDate=null;
	var _flagCertDate=null,_flagTransDate=null;
	
	
	
	// **** buttons ****
	var _buttons = {
		okScreenButton :new DesktopWeb.Controls.ScreenButton(
				{
					itemId : 'okBtnScreen',
					text: _translationMap['OK']
					,handler: function(){
							/*DesktopWeb.Util.commitScreen();*/
						_controller.doUpdate();
							
					}
				}
			)
	,cancelScreenButton : new DesktopWeb.Controls.ScreenButton(
			{
				text: _translationMap['Cancel']
				,handler: function(){
					if(_controller.updatesFlag || _controller.getUpdateFlags() || _controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate)){
						DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
						function handlePromptMsg(btn){
							if(btn){
								_controller.goToScreen();
							}
						}
						}else{
						_controller.goToScreen();
							
					}
				}
			}
		)
	}
	
	

	// **** fields ****
	var _fields = {
			IncepDateLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['IncepDate'],
			width : 50
		})
		,IncepDate: new DesktopWeb.Controls.DateField({
			itemId: 'pIncepDate'
				,fieldLabel: _translationMap['IncepDate']
				,width : 110
				,allowBlank: false
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
				,validator : function(value){
					var validate=_controller.validateIncepDate(value);
					return validate;
			    }
				,listeners : {
					change : function(oldValue,newValue ){
						if(_startValueIncepDate == null)
							{
							_startValueIncepDate=oldValue.startValue;
							_flagIncepDate=1;
							}
						else 
							{
							if(_startValueIncepDate.getTime() == newValue.getTime())
								{
								_flagIncepDate=0;
								}
							else
								{
								_flagIncepDate=1;	
								}
							}
						
						if(_controller.updatesFlag || _controller.getUpdateFlags() || _controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
							_buttons['okScreenButton'].enable();
						else
							_buttons['okScreenButton'].disable();
					}
				}
			}),
			GrantRequestedLabel : new DesktopWeb.Controls.Label({
				fieldLabel : _translationMap['GrantRequested'],
				width : 50
			}),
			GrantRequested: new DesktopWeb.Controls.SMVComboBox({
				itemId: 'grantRequested'
				,fieldLabel: _translationMap["GrantRequested"]
				,editable: true
				,width: 110
				,originalValue: null
				,setOriginalValue: function(value){
					this.setValue(value);
					this.originalValue = value;
				}
				,listeners : {
					change : function(oldValue,newValue ){
						if(_startValueGrant == null)
							{
							
							_startValueGrant=oldValue.startValue;
							_flagGrant=1;
							
							}
						else 
							{
							if(_startValueGrant == newValue)
								{
								_flagGrant=0;
								}
							else
								{
								_flagGrant=1;
								}
							}
						
						if(_controller.updatesFlag || _controller.getUpdateFlags() ||_controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
							_buttons['okScreenButton'].enable();
						else
							_buttons['okScreenButton'].disable();
						
						_fields['GrantDate'].setValue(new Date());
					}
				}
			}),
		TransferredAccountLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['TransferredAccount'],
			width : 50
		}),
		TransferredAccount: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'transferredAccount'
			,fieldLabel: _translationMap["TransferredAccount"]
			,editable: true
			,width: 110
			,listeners : {
				change : function(oldValue,newValue ){
					if(_startValueTransferred == null)
						{
						_startValueTransferred=oldValue.startValue;
						_flagTransferred=1;
						}
					else 
						{
						if(_startValueTransferred == newValue)
							{
							_flagTransferred=0;
							}
						else
							{
							_flagTransferred=1;
							}
						}
					if(_controller.updatesFlag || _controller.getUpdateFlags() || _controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
						_buttons['okScreenButton'].enable();
					else
						_buttons['okScreenButton'].disable();
				}
			}
		}),
		DTCEligibleCurrLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['DTCEligibleCurr'],
			width : 50
		}),
		SpecifiedYearCurrLabel : new DesktopWeb.Controls.Label({
			fieldLabel : _translationMap['SpecifiedYearCurr'],
			width : 50
		}),
		
		ReportToESDC: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'reportToESDC'
			,fieldLabel: _translationMap["ReportToESDC"]
			,editable: true
			,width: 110
			,listeners : {
				change : function(oldValue,newValue ){
					if(_startValueReportESDC == null)
						{
						
						_startValueReportESDC=oldValue.startValue;
						_flagReportESDC=1;
						
						}
					else 
						{
						if(_startValueReportESDC == newValue)
							{
							_flagReportESDC=0;
							}
						else
							{
							_flagReportESDC=1;
							}
						}
					
					if(_controller.updatesFlag || _controller.getUpdateFlags()|| _controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
						_buttons['okScreenButton'].enable();
					else
						_buttons['okScreenButton'].disable();
				}
			}
		})
	,
	BondRequested: new DesktopWeb.Controls.SMVComboBox({
		itemId: 'bondRequested'
		,fieldLabel: _translationMap["BondRequested"]
		,editable: true
		,width: 110
		,listeners : {
			change : function(oldValue,newValue ){
				if(_startValueGrant == null)
					{
					
					_startValueGrant=oldValue.startValue;
					_flagBond=1;
					
					}
				else 
					{
					if(_startValueGrant == newValue)
						{
						_flagBond=0;
						}
					else
						{
						_flagBond=1;
						}
					}
				if(_controller.updatesFlag || _controller.getUpdateFlags() || _controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
					_buttons['okScreenButton'].enable();
				else
					_buttons['okScreenButton'].disable();
			}
		}
	}),
	
	GrantDateLabel : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['GrantDate'],
		width : 50
	})
	,GrantDate: new DesktopWeb.Controls.DateField({
		itemId: 'pGrantDate'
			,fieldLabel: _translationMap['GrantDate']
			,width : 110
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,listeners : {
				change : function(field, newValue, oldValue){
					var originalFlag = _fields['GrantRequested'].originalValue;
					var currentFlag = _flagGrant == null ? originalFlag : _flagGrant;
					var today = new Date();
					today.setHours(0,0,0,0);
					
					if(currentFlag) {
						if(originalFlag) {
							if(today.getTime() > newValue.getTime()){
								DesktopWeb.Util.displayError("Effective Date cannot be backdated");  
								field.setValue(oldValue);	
							}	
						}			
					}
					else {
						if(!originalFlag) {
							if(today.getTime() > newValue.getTime()){
								DesktopWeb.Util.displayError("Effective Date cannot be backdated");  
								field.setValue(oldValue);	
							}		
						}
					}
				}
			}
		}),
		
		
	ContractRegStatus : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['ContractRegStatus'],
		width : 50
	}),
	DTCElectionCurr : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['DTCElectionCurr'],
		width : 50
	}),
	SDSPElectionCurr : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['SDSPElectionCurr'],
		width : 50
	}),
	BeneName : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['BeneName'],
		width : 200
	}),
	BeneDOB : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['BeneDOB'],
		width : 50
	}),
	ContEndDate : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['ContEndDate'],
		width : 50
	}),
	GrantEligibleEndDate : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['GrantEligibleEndDate'],
		width : 50
	}),
	SpecimenPlanNum : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['SpecimenPlanNum'],
		width : 50
	}),
	DateOfDeath : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['DateOfDeath'],
		width : 50
	}),
	SIN : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['SIN'],
		width : 50
	}),
	BondEligibleEndDate : new DesktopWeb.Controls.Label({
		fieldLabel : _translationMap['BondEligibleEndDate'],
		width : 50
	})
	,ElectionTypeDropDown: new DesktopWeb.Controls.SMVComboBox({
		itemId: 'pElectionTypeDropDown'
		,fieldLabel: _translationMap["ElectionType"]
		//,editable: false
		,width: 160
		,listeners:{
			expand : 	function(){
				
				//check DTC Eligibility before enabling options
				var dtcEligible=_fields['DTCEligibleCurrLabel'].getValue();
				
				if(dtcEligible == 'Yes')
					{
					//display only SDSP and Specified Year
					this.store.removeAll();
					var sdspElection = {
						    code: _controller.getElectionTypeCode('SDSP Election'),
						    value: 'SDSP Election'
						};
					var specifiedYearElection = {
						    code: _controller.getElectionTypeCode('Specified Year'),
						    value: 'Specified Year'
						};
					
						var r = new this.store.recordType(sdspElection); // create new record
						this.store.insert(0, r);
						
						var r1 = new this.store.recordType(specifiedYearElection); // create new record
						this.store.insert(0, r1);
					
					}
				else{
					//display only DTC election
					this.store.removeAll();
					var dtcElection = {
						    code: _controller.getElectionTypeCode('DTC Election'),
						    value: 'DTC Election'
						};
				
					
						var r = new this.store.recordType(dtcElection); // create new record
						this.store.insert(0, r);
						
						
					}
				
				var selectedDropDownValue=_fields['ElectionTypeDropDown'].getValue();
				var  rdspElectionsGridStore= _grids['rdspElectionsGrid'].getStore();
				rdspElectionsGridStore.clearFilter(false);
				
			}
	,select : function( combo, record, index ){
			
		_controller.resetList();
		  _fields['ElectedDropDown'].setDisabled(false);

		  if(combo.getValue() == 1)
		  {
			  var electedStore=_fields['ElectedDropDown'].getStore();
		  var election=_fields['DTCElectionCurr'].getValue();
		  electedStore.removeAt(electedStore.find('value',election));
	
		  }
		  if(combo.getValue() == 2)
		  {
			  var electedStore=_fields['ElectedDropDown'].getStore();
		  var election=_fields['SDSPElectionCurr'].getValue();
		  electedStore.removeAt(electedStore.find('value',election));

		  }
		  if(combo.getValue() == 3)
		  {
			  var electedStore=_fields['ElectedDropDown'].getStore();
		  var election=_fields['SpecifiedYearCurrLabel'].getValue();
		  electedStore.removeAt(electedStore.find('value',election));

		  }


		var rdspElectionsGridStore = _grids['rdspElectionsGrid'].getStore();
		var queryRecords=rdspElectionsGridStore.queryBy(function(record){
			var electionType = _controller.getElectionType(combo.getValue());
			if(record.data.reportingStatus == 'Yes' && record.data.type == electionType )
				{
			return  record;
				}
			
		});
		if(queryRecords.getCount()>0)
			{
		queryRecords.each(function(record){
			record.data.transactionDate=JRDSP.Util.convertDateToStringFormat(record.data.transactionDate);
		});
		
		queryRecords.sort('DESC',function(a,b){
	
			if(a.data.transactionDate > b.data.transactionDate)
				return 1;
			if(a.data.transactionDate < b.data.transactionDate)
				return -1;
			
			return 0;
			
		});
		
		queryRecords.each(function(record){
			record.data.transactionDate=JRDSP.Util.convertStringToDate(record.data.transactionDate);
		});
		

		var minDate=DesktopWeb.Util.stringToDate(queryRecords.get(0).data.transactionDate,'dmy');
		
		
		_fields['TransactionDatePicker'].minValue = minDate;
		
			}
		

		
	}
	
			}
					

		
	})
	,ElectedDropDown: new DesktopWeb.Controls.SMVComboBox({
		itemId: 'pElectedDropDown'
		,fieldLabel: _translationMap["Elected"]
		//,editable: false
		,width: 150
		,listeners: {
			select: function(combo, record, index){
				_controller.setEnableCertDate(combo.getValue());
				
			}
		}
	})
	,CertificationDatePicker: new DesktopWeb.Controls.DateField({
		itemId: 'pCertificationDatePicker'
			,fieldLabel: _translationMap['CertificationDate']
			,width : 110
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,validator : function(value){
				var validate=_controller.validateCertDate(value);
				_controller.enableOKButtonPopUp(validate);
				return validate;
		    }
		,listeners : {
		change : function( newValue, oldValue ){
			
			//okBtnScreen
			
			_buttons['okScreenButton'].enable();
			
		}
	}
			
		})
	,TransactionDatePicker: new DesktopWeb.Controls.DateField({
		itemId: 'pTransactionDatePicker'
			,fieldLabel: _translationMap['TransactionDate']
			,width : 110
			,allowBlank: false
			,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			,validator : function(value){
				var validate=_controller.validateTransactionDate(value);
	        	_controller.enableOKButtonPopUp(validate);
				return validate;
		    }
	,listeners : {
		change : function(oldValue,newValue){
	
			_buttons['okScreenButton'].enable();
			
		}
	}
			
		})
	,ElectionTypeDropDownFilter: new DesktopWeb.Controls.SMVComboBox({
		itemId: 'pElectionTypeDropDownFilter'
		,fieldLabel: _translationMap["EventType"]
		,editable: false
		,width: 120
		,listeners: {
			select: function(combo, record, index){
				
				_controller.setElectionGridBasedOnFilter(combo.getValue());
				
				
			}
		}
	})
	
	,AccountStatus : new Ext.form.Hidden({
		itemId:'pAccountStatus'
		
	})
	,ClosureReasonCode : new Ext.form.Hidden({
		itemId:'pClosureReasonCode'
		
	})
	,ClosureDate : new Ext.form.Hidden({
		itemId:'pClosureDate'
		
	})
	,CreatedBy : new Ext.form.Hidden({
		itemId:'pCreatedBy'
		
	})
    ,AccountUuid: new Ext.form.Hidden({
        itemId: 'accountUuid'
    })
	};

	// **** grids ****
	var _grids = {
	rdspAccountInfoGrid : new DesktopWeb.AdvancedControls.GridPanel({
		width: _layoutWidth
		,title : _translationMap['RDSPAccountHolderOrPCGInformation']
		,height: 150
		,store: new Ext.data.XmlStore(
				{
					record: 'entity'
					,fields: ['entityType','effectiveDate','name','sinOrBn', 'relationToBene']
	
				})
	,viewConfig: { autoFill: true }
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
				,{header: _translationMap['EntityType'], id:'entityType', dataIndex: 'entityType',width: 300
					,renderer: function(val, metaData, record) { 
						if(record.data['entityType'] == '01') {
							return _translationMap['AccountHolder'];
						}
						else if(record.data['entityType'] == "80") {
							return _translationMap['PrimaryCaregiver'];
						}
					}
				}
				,{header: _translationMap['EffectiveDate'], id:'effectiveDate', dataIndex: 'effectiveDate',width: 300
				}
				,{header: _translationMap['AccHolderName'], id:'accHolderName', dataIndex: 'name',width: 300
				}
				,{header: _translationMap['SINorBN'], id:'sinorBN',  dataIndex: 'sinOrBn', width: 300
				}
				,{header: _translationMap['RelationToBene'], id:'relationToBene', dataIndex: 'relationToBene', width: 400 }

			]
		})
	,listeners: {
		viewready: function(){
			_grids['rdspAccountInfoGrid'].getSelectionModel().selectFirstRow();
		}
		
	}
	,clearGridData: function()
	{
		if (_grids['rdspAccountInfoGrid'].viewReady)
		{
			_grids['rdspAccountInfoGrid'].clearData();
		}
	}
	}
	
	
	)
	
	,rdspElectionsGrid : new DesktopWeb.AdvancedControls.GridPanel({
		width: _layoutWidth-15
		,autoScroll: true
		,height: 150
		,store: new Ext.data.XmlStore(
				{
					record: 'election'
					,fields: [
						'id','type', 'elected', 'certificationDate', 'transactionDate','reportingStatus', 'periodStart',
						'periodEnd', 'uuid', 'effective', 'status','runMode','yesElectionId','noElectionId'
					]
		
				}
			)
		
		,selModel: new Ext.grid.RowSelectionModel(
			{
				singleSelect: true
			}
		)
		,viewConfig: { autoFill: true }
		
	
		,colModel: new Ext.grid.ColumnModel({
			defaults: {
				menuDisabled: true
			}

			,columns: [
				{width: 0, id:'electionId', dataIndex: 'id',hidden: true
					
			}
				,{header: _translationMap['EventType'], id:'type', dataIndex: 'type',width: 300
					,
					renderer: function(value, meta, record){
						return _controller.getElectionType(value);
	                }
				}
				,{header: _translationMap['CertificationDate'], id:'certificationDate', dataIndex: 'certificationDate', width: 400 }
				,{header: _translationMap['TransactionDate'], id:'transactionDate', dataIndex: 'transactionDate', width: 400
					
				}
/*				,{header: _translationMap['ReportingStatus'], id:'reportingStatus', dataIndex: 'reportingStatus', width: 400
				}*/
				,{header: _translationMap['PeriodStart'], id:'periodStart', dataIndex: 'periodStart',width: 400 }
				,{header: _translationMap['PeriodEnd'], id:'periodEnd', dataIndex: 'periodEnd',width: 400
					,
					renderer: function(value, meta, record){
						record.data.periodEnd = (record.data.periodEnd)? record.data.periodEnd : '31/12/9999';
						return record.data.periodEnd;
	                }
				}
				
			]
		})
		,buttons: [
			new DesktopWeb.Controls.ActionButton({
				itemId: 'addBtn'
				,text: _translationMap['Add']
				,handler: function(){
					if(_controller.addBtnValidation()){
						if(_controller.checkValidAction(_controller.ADD, _grids['rdspElectionsGrid'].getSelectedRecord())){
							_controller.openActionPopup(_controller.ADD, _controller.popupList['AddElection'],_fields['DTCEligibleCurrLabel'].getValue());
							}else{
								DesktopWeb.Util.displayError(_controller.getButtonErrorMsg(_controller.ADD, _grids['rdspElectionsGrid'].getSelectedRecord()));
							}
					}else{
						DesktopWeb.Util.displayError(_controller.addBtnValidationMsg());
					}
					
				}
			})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'modBtn'
				,text: _translationMap['Modify']
			,handler: function(){
				if(_controller.checkValidAction(_controller.MOD, _grids['rdspElectionsGrid'].getSelectedRecord())){
					_controller.openActionPopup(
							_controller.MOD, _controller.popupList['AddElection']);
					}else{
						DesktopWeb.Util.displayError(_controller.getButtonErrorMsg(_controller.MOD, _grids['rdspElectionsGrid'].getSelectedRecord()));
					}
				
				
				}
			})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'delBtn'
				,text: _translationMap['Delete']
				,handler: function(){
					if(_controller.checkValidAction(_controller.DEL, _grids['rdspElectionsGrid'].getSelectedRecord())){
						_controller.deleteSelectedElectionRecord();
						//setting certDate and transDate flag to 0 as it is a delete
						_flagCertDate=0;
						_flagTransDate=0;
						if(_controller.updatesFlag ||_controller.getUpdateFlags() ||_controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
							_buttons['okScreenButton'].enable();
						else
							_buttons['okScreenButton'].disable();
						
						}else{
							DesktopWeb.Util.displayError(_controller.getButtonErrorMsg(_controller.DEL, _grids['rdspElectionsGrid'].getSelectedRecord()));
						}
				}	
					
			})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'revokeBtn'
					,text: _translationMap['Revoke']
					,handler: function(){
						if(_controller.checkValidAction(_controller.REVOKE, _grids['rdspElectionsGrid'].getSelectedRecord())){
							_controller.openActionPopup(
									_controller.REVOKE, _controller.popupList['AddElection']);
							}else{
								DesktopWeb.Util.displayError(_controller.getButtonErrorMsg(_controller.REVOKE, _grids['rdspElectionsGrid'].getSelectedRecord()));
							}
						
						
						
						}
				})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'histBtn'
				,text: _translationMap['Historical']
				,handler: function(){
					
					
				}
			})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'adminBtn'
				,text: _translationMap['Admin']
				,handler: function(){
					
				}
			})
		]

	,clearGridData: function()
	{
		
	}

	}
	
	
	)
	}
	
	var _popups = {
			AddElection :  new DesktopWeb.AdvancedControls.PopupWindow({
					width: 300,
					//action:null,
					closeAction: 'hide'
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
									,columnWidth: 1
									,defaults: {width:120,layout: 'form'}
									,items: [
										_fields['ElectionTypeDropDown']
										//,_fields['ElectedDropDown']
										,_fields['CertificationDatePicker']
										,_fields['TransactionDatePicker']
									]
								}
								
							]
						}
					]
					,buttons: [
						 new DesktopWeb.Controls.ActionButton({
							 itemId: 'okBtn'
							,text: _translationMap['OK']
							,handler: function(){
								// Add row to grid
								
								if(_popups['AddElection'].isValid())
									{
									var rowData=_popups['AddElection'].getData(_popups['AddElection'].action);	
									_controller.modifyEntityGrid(rowData,_popups['AddElection'].action);
									if(_controller.updatesFlag || _controller.getUpdateFlags() ||_controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
										_buttons['okScreenButton'].enable();
									else
										_buttons['okScreenButton'].disable();

									
									_popups['AddElection'].hide();


							}
							}
						})
						,new DesktopWeb.Controls.ActionButton({
							text: _translationMap['Cancel']
						,handler: function(){
							// Close grid 
							_popups['AddElection'].hide();
						}
					})
					]
					,init: function(action,dtceligible)
					{
						this.action = action;
						
						var vTitle = _controller.getServiceTitle(DesktopWeb._SCREEN_PARAM_MAP['From_Menu']);
						
						//this.setTitle(vTitle);
						
						// only 1 open election per election type

						switch(action)
						{
							case _controller.ADD:
							{
								this.clearAllFields();

								//this.resetAllFields();


								this.setTitle(vTitle + ' - ' + _translationMap['Add']);
								this.populate(action,dtceligible);
								break;
							}
							case _controller.MOD:
							{
								this.setTitle(vTitle + ' - ' + _translationMap['Modify']);
								this.populate(action,dtceligible);
								break;
							}
							case _controller.REVOKE:
							{
								this.setTitle(vTitle + ' - ' + _translationMap['Revoke']);
								this.populate(action,dtceligible);
								break;
							}
							
						}
						

					}
					,getData : function(action){
						var data={};
							
							data['type']=_fields['ElectionTypeDropDown'].getValue();
							if(action == _controller.ADD){
								data['elected']='Yes';
							}
							
							data['certificationDate']=_fields['CertificationDatePicker'].getDisplayDateString();
							data['transactionDate']=_fields['TransactionDatePicker'].getDisplayDateString();
							data['reportingStatus'] ='No';
							data['periodStart'] ='';
							data['periodEnd'] ='';
							data['runMode'] = action;
							
							if(action == _controller.ADD){
							if(data['type']==1)
							{
								var lastDTCYear= _controller.getLastDTCEligibleYear();
								if(lastDTCYear){
									var periodStartYear=lastDTCYear+1;
									data['periodStart'] ="01/01/"+periodStartYear;
									//TODO : Need to get year after last dtc eligible end date
									data['periodEnd'] ="31/12/"+(parseInt(periodStartYear)+5);
								}
							
							}
							if(data['type']==2)
							{
							data['periodStart'] =data['certificationDate'];
							data['periodEnd'] ="31/12/9999";
							}
							
							if(data['type']==3)
							{
							data['periodStart'] =data['certificationDate'];
							if(data['elected'] == 'Yes')
							{
								var dateParts = data['certificationDate'].split("/");
								var year=parseInt(dateParts[2])+5;
								var month=parseInt(dateParts[1]);
								var date=parseInt(dateParts[0]);
								var dateObject = new Date(year, month-1, date); // month is 0-based
							data['periodEnd'] ="31/12/"+dateObject.getFullYear();
							}
							else
								{
							data['periodEnd'] =data['transactionDate'];
								}
							}
							}

							if(action == _controller.MOD){
								
							if(_startValueCertDate!=null && _startValueCertDate != data['certificationDate']){
								_flagCertDate = 1;
							}
							else{
								_flagCertDate = 0;
							}
							if (_startValueTransDate!=null && _startValueTransDate != data['transactionDate']) 
								{
								_flagTransDate = 1;
								}
								else{
									_flagTransDate = 0;
								}

							
							if(_controller.updatesFlag || _controller.getUpdateFlags() ||_controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
								_buttons['okScreenButton'].enable();
							else
								_buttons['okScreenButton'].disable();
							
								
							}
							if(action == _controller.REVOKE){
								var selectedElection = _grids['rdspElectionsGrid'].getSelectedRecord();
								data['certificationDate'] = selectedElection.data['certificationDate'];
								data['periodStart'] = selectedElection.data['periodStart'];
								_startValueTransDate= selectedElection.data['transactionDate'];
								if (_startValueTransDate != data['transactionDate']) 
								{
								_flagTransDate = 1;
								}
								else{
									_flagTransDate = 0;
								}
								if(_controller.updatesFlag || _controller.getUpdateFlags() ||_controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
									_buttons['okScreenButton'].enable();
								else
									_buttons['okScreenButton'].disable();
							}

					return data;
						
					}
					,isValid: function()
					{
						var popup = _popups['AddElection'];
					
						// Validate all input fields before business checking
						var valid = popup.getField('pCertificationDatePicker').isValid();
						valid = popup.getField('pTransactionDatePicker').isValid() && valid;
						
						return valid;
					}
					,resetAllFields: function()
					{
						if ( this.rendered )
						{
							for (var name in _controller.electionModalFldsList)
							{						
								this.getField(_controller.electionModalFldsList[name]).reset();								
								this.getField(_controller.electionModalFldsList[name]).setValue('');
								this.getField(_controller.electionModalFldsList[name]).enableField();
								this.getField(_controller.electionModalFldsList[name]).clearInvalid();					
							}
							

						}
					}

					
					,populate: function(action,dtceligible) //identification
					{
						this.action = action;
						
						this.resetAllFields();

						
						switch (action)
						{
							case _controller.ADD :
								this.resetAllFields();
								this.getField('pElectionTypeDropDown').enable();
								//this.getField('pElectedDropDown').enable();
								this.getField('pCertificationDatePicker').enable();
								_startValueCertDate=null;
								_startValueTransDate=null;
								_flagCertDate=null;
								_flagTransDate=null;
								
								if (this.rendered)
									this.syncShadow();

								break;
							case _controller.MOD :
									var selectedElection = _grids['rdspElectionsGrid'].getSelectedRecord();
									this.getField('pElectionTypeDropDown').disable();
									var type = selectedElection.data['type'];
									var  elected= selectedElection.data['elected'];
									var certificationDate = selectedElection.data['certificationDate'];
									var transactionDate = selectedElection.data['transactionDate'];
									this.getField('pElectionTypeDropDown').setValue(type);
									this.getField('pCertificationDatePicker').setValue(certificationDate);//.setRawValue(selectedFFI.get('displayValue'));
									this.getField('pTransactionDatePicker').setValue(transactionDate);
									if(elected == 'No'){
										this.getField('pCertificationDatePicker').setValue(null);
										this.getField('pCertificationDatePicker').disable();	
									}else{
							
										
										//this.getField('pElectedDropDown').setValue(elected);
										this.getField('pCertificationDatePicker').setValue(certificationDate);//.setRawValue(selectedFFI.get('displayValue'));
										this.getField('pCertificationDatePicker').enable();	
									}
		
									if(_startValueTransDate == null)
									{
									_startValueTransDate=transactionDate;
									}

								if (this.rendered)
									this.syncShadow();

								break;
							case _controller.REVOKE :
								var selectedElection = _grids['rdspElectionsGrid'].getSelectedRecord();
								this.getField('pElectionTypeDropDown').disable();
								this.getField('pCertificationDatePicker').disable();
								//this.getField('pElectedDropDown').disable();
								var type = selectedElection.data['type'];
								this.getField('pElectionTypeDropDown').setValue(type);
								this.getField('pCertificationDatePicker').setValue(null);
								
							if (this.rendered)
								this.syncShadow();

							break;
								
								
						};
						
					}

			})
					}

		


	
	

	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		,layoutHeight: _layoutHeight
		,fields: _fields
		,grids: _grids
		,buttons: _buttons
		,popups: _popups
		,layout: new Ext.Container({
			height: _layoutHeight
			, width: _layoutWidth
			, items: [
				{
					xtype: 'fieldset'
					,title: _translationMap['RDSPAccount']
					,items: [
						{
							layout: 'column'
							,labelWidth: 170
							,items: [
								{
									columnWidth: 0.50
									,layout: 'form'
									,items: [
										_fields['IncepDate']
										,_fields['GrantRequested']
										,_fields['TransferredAccount']
										,_fields['DTCEligibleCurrLabel']
										,_fields['SpecifiedYearCurrLabel']
										,_fields['AccountStatus']
										,_fields['ClosureReasonCode']
										,_fields['ClosureDate']
										,_fields['CreatedBy']
										,_fields['AccountUuid']
									]
								}
								, {
									columnWidth: 0.50
									,layout: 'form'
									,items: [
										_fields['ReportToESDC']
										,_fields['BondRequested']
										,_fields['GrantDate']
										,_fields['ContractRegStatus']
										,_fields['DTCElectionCurr']
										,_fields['SDSPElectionCurr']
									]
								}
								
							]
						,buttons: [
							new DesktopWeb.Controls.ActionButton({
								itemId: 'histBtn'
								,text: _translationMap['Historical']
								,handler: function(){


									}
							})
							,new DesktopWeb.Controls.ActionButton({
								itemId: 'adminBtn'
								,text: _translationMap['Admin']
								,handler: function(){
				

									}
							})
							]
						}
						
					]
				}
				
				,{
					xtype: 'fieldset'
						,title: _translationMap['RDSPBeneInfo']
						,items: [
							{
								layout: 'column'
								,labelWidth: 150
								,items: [
									{
										columnWidth: 0.55
										,layout: 'form'
										,items: [
											_fields['BeneName']
											,_fields['BeneDOB']
											,_fields['ContEndDate']
											,_fields['GrantEligibleEndDate']
										]
									}
									, {
										columnWidth: 0.45
										,layout: 'form'
										,items: [
											_fields['SpecimenPlanNum']
											,_fields['DateOfDeath']
											,_fields['SIN']
											,_fields['BondEligibleEndDate']
										]
									}
								]
							}
						]
					}
				,_grids['rdspAccountInfoGrid']
				,new Ext.Container({
					height: _layoutHeight
					, width: _layoutWidth
					, items: [
						{
						xtype: 'fieldset'
						,title: _translationMap['EventTracking']
						,items:[
							{
							layout: 'form'
							,items: [
								_fields['ElectionTypeDropDownFilter']
								,_grids['rdspElectionsGrid']
								]
							
							}
							]
						
						}
					]
				})
				
		
			]
		})


		,screenButtons: {
			items:[
				_buttons['okScreenButton']
				,_buttons['cancelScreenButton']
			]
		}
	}
}