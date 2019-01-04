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
		fileScreenButton: new DesktopWeb.Controls.ScreenButton(
				{
					text: 'TBD'
					,handler: function(){

					}
				}
			)
		,okScreenButton :new DesktopWeb.Controls.ScreenButton(
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
		,width: 150
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
				
				var selectedDropDownValue=_fields['ElectionTypeDropDownFilter'].getValue();
				var  rdspElectionsGridStore= _grids['rdspElectionsGrid'].getStore();
				rdspElectionsGridStore.clearFilter(false);
				if(rdspElectionsGridStore.data.length > 0)
				{

				var electionType=rdspElectionsGridStore.data.items[0].data.type;
				var electionReportingStatus=rdspElectionsGridStore.data.items[0].data.reportingStatus;
				var electionFlag=rdspElectionsGridStore.data.items[0].data.elected;
				if(electionFlag == 'Yes')
					{
					this.store.removeAll();

					
					var defaultData = {
						    code: _controller.getElectionTypeCode(electionType),
						    value: electionType
						};
					
						var r = new this.store.recordType(defaultData); // create new record
						this.store.insert(0, r);
					}
				
				rdspElectionsGridStore.filter('type', _controller.getElectionType(selectedDropDownValue));		
				
				}

				
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
		,fieldLabel: _translationMap["ElectionType"]
		,editable: false
		,width: 110
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
						'periodEnd', 'uuid', 'effective', 'status','runMode'
					]
		
				}
			)
		
		,selModel: new Ext.grid.RowSelectionModel(
			{
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){
						if(selModel){
							_controller.enableButtons(record);
						}
					}
				}
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
				,{header: _translationMap['ElectionType'], id:'type', dataIndex: 'type',width: 300

				}
				,{header: _translationMap['Elected'], id:'elected', dataIndex: 'elected', width: 300
				}
				,{header: _translationMap['CertificationDate'], id:'certificationDate', dataIndex: 'certificationDate', width: 400 }
				,{header: _translationMap['TransactionDate'], id:'transactionDate', dataIndex: 'transactionDate', width: 400
					
				}
				,{header: _translationMap['ReportingStatus'], id:'reportingStatus', dataIndex: 'reportingStatus', width: 400
				}
				,{header: _translationMap['PeriodStart'], id:'periodStart', dataIndex: 'periodStart',width: 400 }
				,{header: _translationMap['PeriodEnd'], id:'periodEnd', dataIndex: 'periodEnd',width: 400 }
				
			]
		})
		,buttons: [
			new DesktopWeb.Controls.ActionButton({
				itemId: 'addBtn'
				,text: _translationMap['Add']
				,handler: function(){_controller.openActionPopup(_controller.ADD, _controller.popupList['AddElection'],_fields['DTCEligibleCurrLabel'].getValue());}
			})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'modBtn'
				,text: _translationMap['Modify']
			,handler: function(){
				_controller.openActionPopup(
						_controller.MOD, _controller.popupList['AddElection']);
				}
			})
			,new DesktopWeb.Controls.ActionButton({
				itemId: 'delBtn'
				,text: _translationMap['Delete']
				,handler: function(){
					_grids['rdspElectionsGrid'].enableButton('addBtn');
					_grids['rdspElectionsGrid'].disableButton('modBtn');	
					_grids['rdspElectionsGrid'].disableButton('delBtn');	
					_controller.deleteSelectedElectionRecord();
					//setting certDate and transDate flag to 0 as it is a delete
					_flagCertDate=0;
					_flagTransDate=0;
					if(_controller.updatesFlag ||_controller.getUpdateFlags() ||_controller.checkFlagsForModification(_flagIncepDate,_flagReportESDC,_flagGrant,_flagBond,_flagTransferred,_flagCertDate,_flagTransDate))
						_buttons['okScreenButton'].enable();
					else
						_buttons['okScreenButton'].disable();
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
									,defaults: {width:100,layout: 'form'}
									,items: [
										_fields['ElectionTypeDropDown']
										,_fields['ElectedDropDown']
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
							
						}
						

					}
					,getData : function(action){
						var data={};
							
							data['type']=_fields['ElectionTypeDropDown'].getValue();
							data['elected']=_fields['ElectedDropDown'].getValue();
							data['certificationDate']=_fields['CertificationDatePicker'].getDisplayDateString();
							data['transactionDate']=_fields['TransactionDatePicker'].getDisplayDateString();
							data['reportingStatus'] ='No';
							data['periodStart'] ='';
							data['periodEnd'] ='';
							data['runMode'] = action;
							
							if(data['type']==3)
							{
		
							data['periodStart'] =data['certificationDate'];
							
							
							
							if(data['elected'] == 'Yes')
							{
								var dateParts = data['certificationDate'].split("/");
								
								var year=parseInt(dateParts[2])+5;
								var month=parseInt(dateParts[1]);
								var date=parseInt(dateParts[0]);
								
								var dateObject = new Date(year, month, date); // month is 0-based

							data['periodEnd'] ="31/12/"+dateObject.getFullYear();
							}
							else
								{
							data['periodEnd'] =data['transactionDate'];
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
								this.getField('pElectedDropDown').enable();
								this.getField('pCertificationDatePicker').disable();
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
									this.getField('pElectedDropDown').disable();
									var type = selectedElection.data['type'];
									var elected = selectedElection.data['elected'];
									var certificationDate = selectedElection.data['certificationDate'];
									var transactionDate = selectedElection.data['transactionDate'];
															
									
									this.getField('pElectionTypeDropDown').setValue(type);
									this.getField('pElectedDropDown').setValue(elected);
									this.getField('pCertificationDatePicker').setValue(certificationDate);//.setRawValue(selectedFFI.get('displayValue'));
									this.getField('pTransactionDatePicker').setValue(transactionDate);
									
									
									if(elected == 'Yes')
										{
										this.getField('pCertificationDatePicker').enable();
										this.getField('pTransactionDatePicker').disable();

										if(_startValueCertDate == null)
											{
										_startValueCertDate=certificationDate;
											}
										}
									
									if(elected == 'No')
									{
										this.getField('pCertificationDatePicker').disable();
									}
									if(_startValueTransDate == null)
									{
									_startValueTransDate=transactionDate;
									}

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
							,labelWidth: 150
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
						,title: _translationMap['ElectionsAndSpecifiedYear']
						,items:[
							{
							layout: 'column'
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
				_buttons['fileScreenButton']
				
					,_buttons['okScreenButton']
				,_buttons['cancelScreenButton']
			]
		}
	}
}