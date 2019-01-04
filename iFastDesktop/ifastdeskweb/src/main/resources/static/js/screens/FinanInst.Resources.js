/*********************************************************************************************
 * @file	FinanInst.Resources.js
 * @author	Sukjaitham, Supareuk
 * @desc	Resources JS file for Financial Institution Regulatory screen.
 *********************************************************************************************/
/*
 * Procedure: FinanInst.Resources.js
 *
 * Purpose  : Resources for Financial Institution Regulatory screen
 *             
 * Notes    : - Setup Financial Institution Regulatory
 *            - Open screen from 
 *               Menu -> System Maintenance -> Financial Institution Regulatory
 *				 Menu -> Broker Level Maintenance -> Broker Regulatory
 *				 Menu -> Broker Level Maintenance -> Intermediary Regulatory
 *				 Menu -> Fund Level Maintenance -> Fund Regulatory
 *
 * History  :  
 *		18 Jul 2013 S. Sukjaitham, G. Thawornwachirakun P0193400 T53802
 *					- Creates.
 *
 *		23 Aug 2013 G. Thawornwachirakun P0193400 DFT0014730 T54066
 *					- Add groupType as FATCA for identification popup screen
 *          - Add warnMsg to both grids for support new warning message
 *
 *    09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *    8 Feb 2014 Winnie Cheng P0223057 T77753
 *                  - Added new fields and logic,segeragated FFI search for level
 *                    back-end sent a lists and save new fields values
 *                    back-end sent an error node in returned response xml
 *
 *    28 Feb 2014 Winnie Cheng P0223057 T77807 DFT0029706
 *                  - Identification modify got error due to checking AggregationFFI logic is not complete
 *                    
 *    
 *    7 Mar 2014 Winnie Cheng P0223057 T77835 DFT0030208
 *                  - modify functions for setTitle dynamically
 *
 *
 *    12 Mar 2014 Winnie Cheng P0223057 T77851 DFT0030443
 *       - FFI screens - AggregationFFI show "-" when ReportingFFI changed from "No" to "Environment Default"
 *				
 *    26 Jun 2014 N. Suanlamyai P0223930 T55360 DFT0036362-->CHG0037362
 *       - Fixed date format displaying in search result table if user uses More button.
 *
 *    19 Jan 2015 A. Mongkonrat P0205605 I0 T80201
 *       - FATCA Phase II.
 *
 *    28 Jan 2015 A. Mongkonrat P0205605 I0 T80255
 *                  - FATCA Phase II. Support a new 'Reporting Unit' FFI type.
 *                    Enable Country and Description field for 'Reporting Unit' FFI.
 *                  - Identification Grid doesn't refresh properly.
 *
 *    21 Dec 2015 Watchara Th. P0241558 T81890 FATCA Reporting Enhancement
 *					- Add new tabs (Address and Contact) for
 *					  Fund/Fund Group level and Sponsoring Entity level.
 *
 *    06 Jan 2016 Aurkarn M. P0241558 T81995 DFT0058373 DFT0058365 FATCA Reporting Enhancement 
 *					- Redesign Address/Contact tabs
 *
 *    09 Jan 2016 Aurkarn M. P0241558 T82213 DFT0059298 FATCA Reporting Enhancement 
 *					- Phone format validation isn't required for Lux.
 *                  - Fix issue where PhoneNumber is required
 *                  - Fix issue where Country field is not required when other fields inside 'Address' tab not empty
 *
 *   06 Jul 2016 Matira T. P0255392 T83155 2016 FATCA Reporting Enhancements
 *					- Add new field FISponsor.
 *                  - Contact Phone number for Domestic client use warning msg instead of error msg.
 *
 *   3 Feb 2017  Winnie Cheng P0259672  T84745
 *			  - Enhance the screen for CRS Report regulation rule and FATCA change accordingly
 *
 * 	  29 March 2017  Winnie Cheng P0259672  T85194
 *			  - carrying over RegulationCode when adding a new record when applicable
 *
 * 	  13 April 2017  Winnie Cheng P0262712  T85299
 *			  - calling Fund Group list when carrying over Search values
 *
 *   20 Jun 2017 Matira T. P0264940 P0264940-35 CRS-FATCA Enhancement 17.5
 *					- remove ResponsibilityTab and respGrd
 *
 *   22 Jan 2018 Matira T. P0268206-125 FATCA 18.3
 *					- re-write layout of screen 
 *
 *   7 Nov 2018 Umamahesh. P0277786-178 FATCA 19.2
 *					- Added logic to support FilerCategory for FATCA/CRS.
 *
 */
 
DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 670;
	var _layoutWidth = 750; 
	var _searchIDFieldWidth = 275;
	var _searchIDFieldPopupWidth = 230;
	var _reportingFFIFieldPopupWidth = 310;
	var _respWidth = 125;
	var _MARKET_CANADA = "CANADA";
	var _MARKET_LUX = "LUX";
	var _COUNTRY_CODE  = "0100";

	// **** buttons ****
	var _buttons = {
		cmdSearch: new DesktopWeb.Controls.ActionButton({
			text: _translationMap['Search']
			,style: "position:absolute; right:0px; top:0px;"
			, handler: function() {_controller.doSearch(false);}
		})
	}

	// **** fields ****
	var _fields = {
		regulationSrch: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'regulationSrch'
			,fieldLabel: _translationMap["Regulation"]
			,editable: false
			,width: 150
		})
		,searchForSrch: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'searchForSrch'
			,fieldLabel: _translationMap["SearchFor"]
			,editable: false
			,width: 150
			,listeners: {
				select: function(combo, record, index){
					_controller.setSuggestService(record.data.code,_controller.popupList['SEARCH']);
				}
			}
		})
		,searchByFund: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFund'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'fundOnlySearch'
			,addtlSearchParams: [{name: 'inclInactive', valueFn: function(){return 'yes'}}]
			,fields: ['fundCode', 'fundCategory', 'fndDisp' ]
			,valueField: 'fundCode'
			,displayField: 'fndDisp'
			,hidden: true
			,emptyText: _translationMap["SearchByFund"]
		})
		,searchByFundGroup: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByFundGroup'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'fundGroupSearch'
			,addtlSearchParams: [{name: 'fundGroupType', valueFn: function(){return _controller.getFundGroupType();}}]
			,fields: ['fundGroupCode','fundGroupType' , 'displayValue']
			,valueField: 'fundGroupCode'
			,displayField: 'displayValue'
			,hidden: true
			,emptyText: _translationMap["SearchByFundGroup"]

		})
		,searchByLegalEntity: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByLegalEntity'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'entWhereUsedSearch'
			,addtlSearchParams: [{name: 'entityWhereused', valueFn: function(){return '15'}}]
			,fields: ['whereUseKey', 'displayValue' ]
			,valueField: 'whereUseKey'
			,displayField: 'displayValue'
			,hidden: true
			,emptyText: _translationMap["SearchByLegalEntity"]
		})
		,searchByBroker: new DesktopWeb.Controls.SuggestField({
			itemId: 'searchByBroker'
			,fieldLabel: _translationMap["SearchID"]
			,width: _searchIDFieldWidth
			,smartview: 'brokerSearch'
			, fields: ['displayValue', 'agencyCode', 'brokerDesc' ]
			,valueField: 'agencyCode'
			,displayField: 'displayValue'
			,hidden: true
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
		,regulationLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Regulation']
			,width: 200
		})
		,levelLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Level']
			,width: 200
		})
		,codeLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Code']
			,width: 220
		})
		,reportingFFILabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ReportingFFI']
			,width: 150
			,readOnly: true
		})
		,reportingUnitLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ReportingUnit']
			,width: 120
		})
		,fiSponsorLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['FISponsor']
			,width: 120
		})
		,descriptionLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Description']
			,width: 150
		})
		,applyThresholdLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ApplyThreshold']
			,width: 120
		})
		,applyThresholdDateLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ApplyThresholdDate']
			,width: 120
		})
		,countryLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Country']
			,width: 150
		})
		,aggregationFFILabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['AggregationFFI']
			,width: 150
		})
		,filerCategoryLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['filerCategory']
			,width: 150
		})
		,classificationLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Classification']
			,width: 230
		})
		,fundGroupLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['FundGroup']
			,width: 200
		})
		,deffLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['EffectiveDate']
			,width: 50
		})
		,stopDateLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['StopDate']
			,width: 50
		})
		,ContactNameLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ContactName']
			,width: 300
		})
		,ContactPhoneNumberLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ContactPhoneNumber']
			,width: 160
		})
		,ContactPhoneExtNumberLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ContactPhoneExtNumber']
			,width: 160
		})
		,ContactEmailLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['ContactEmail']
			,width: 300
		})		
		,Address1Label: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Address1']
			,width: 400
		})
		,Address2Label: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Address2']
			,width: 400
		})
		,Address3Label: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Address3']
			,width: 400
		})
		,CityLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['City']
			,width: 100
		})
		,ProvinceLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Province']
			,width: 100
		})
		,PostalCodeLabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['PostalCode']
			,width: 100
		})
		,CountryFFILabel: new DesktopWeb.Controls.Label({
			fieldLabel: _translationMap['Country']
			,width: 100
		})		
		,ContactNameTextField: new DesktopWeb.Controls.TextField({
			itemId: 'ContactNameTextField'
			,fieldLabel: _translationMap['ContactName']
			,width: 180
		})
		,ContactPhoneNumberTextField: new DesktopWeb.Controls.TextField({
			itemId: 'ContactPhoneNumberTextField'			
			,fieldLabel: _translationMap['ContactPhoneNumber']
			,width: 140
            ,allowBlank: true
            ,listeners: {
				change: function(obj, newVal, oldVal) {
					if (DesktopWeb._SCREEN_PARAM_MAP['market'].toUpperCase() == _MARKET_CANADA) {
						newVal = newVal.trim().replace(/-/g, '');
						var isValid = true;
						
						if (!this.allowBlank && newVal == '')
						{
							isValid = false;
						}
						else if (newVal != '') {
							// 10 digits
							var regxPhoneFormat = /^[0-9]{3}-{0,1}[0-9]{3}-{0,1}[0-9]{4}$/;
							isValid = DesktopWeb._SCREEN_PARAM_MAP['market'].toUpperCase() == _MARKET_LUX ||
									  (DesktopWeb._SCREEN_PARAM_MAP['market'].toUpperCase() == _MARKET_CANADA && 
									   regxPhoneFormat.test(newVal));
						}
						
						if (isValid) {
							if (newVal.length == 10) // XXX-XXX-XXXX
								newVal = newVal.substr(0, 3) + '-' + newVal.substr(3, 3) + '-' + newVal.substr(6, 4);
						}else{
							DesktopWeb.Util.displayWarning(_translationMap['PhoneWrnMsg']);
						}
					}
					this.setValue(newVal);
				}
			}
		})
		,ContactPhoneExtNumberTextField: new DesktopWeb.Controls.TextField({
			itemId: 'ContactPhoneExtNumberTextField'			
			,fieldLabel: _translationMap['ContactPhoneExtNumber']
			,width: 140
		})
		,ContactEmailTextField: new DesktopWeb.Controls.TextField({
			itemId: 'ContactEmailTextField'			
			,fieldLabel: _translationMap['ContactEmail']
			,width: 180
		})		
		,Address1TextField: new DesktopWeb.Controls.TextField({
			itemId: 'Address1TextField'			
			,fieldLabel: _translationMap['Address1']
			,width: 220
            ,listeners: {
				change: function(){
					_controller.setCountryRequired();											
				}
			}
		})
		,Address2TextField: new DesktopWeb.Controls.TextField({
			itemId: 'Address2TextField'			
			,fieldLabel: _translationMap['Address2']
			,width: 220
            ,listeners: {
				change: function(){
					_controller.setCountryRequired();											
				}
			}
		})
		,Address3TextField: new DesktopWeb.Controls.TextField({
			itemId: 'Address3TextField'			
			,fieldLabel: _translationMap['Address3']
			,width: 220
            ,listeners: {
				change: function(){
					_controller.setCountryRequired();											
				}
			}
		})
		,CityTextField: new DesktopWeb.Controls.TextField({
			itemId: 'CityTextField'			
			,fieldLabel: _translationMap['City']
			,width: 150
            ,listeners: {
				change: function(){
					_controller.setCountryRequired();											
				}
			}
		})
		,ProvinceTextField: new DesktopWeb.Controls.TextField({
			itemId: 'ProvinceTextField'			
			,fieldLabel: _translationMap['Province']
			,width: 150
            ,listeners: {
				change: function(){
					_controller.setCountryRequired();											
				}
			}
		})
		,PostalCodeTextField: new DesktopWeb.Controls.TextField({
			itemId: 'PostalCodeTextField'			
			,fieldLabel: _translationMap['PostalCode']
			,width: 150
            ,listeners: {
				change: function(){
					_controller.setCountryRequired();											
				}
			}
		})	
		,CountryDropDown: new DesktopWeb.Controls.SMVComboBox({
			itemId: 'CountryDropDown'						
			,fieldLabel: _translationMap['Country']
			,width: 150
		})		
	}

	// **** grids ****
	var _grids = {
		finInstGrd: new DesktopWeb.AdvancedControls.GridPanel({
			width: _layoutWidth
			,autoScroll: true
			,height: 150
			,autoExpandColumn: 'classification'
			,store: new Ext.data.XmlStore({
				record: 'FinanInst'
				,fields: ['errMsg', 'warnMsg','ffiuuid', 'complyRule', 'level', 'code'
								,'displayValue', 'classification', 'reportingFFI', 'description','filerCategory'
								,'complyCode', 'appLowThres', 'appLowThresDate', 'fundGroup', 'deff','aggrFfiCode','countryCode','aggrffiLevel','aggrDisplayValue'
								, 'stopDate', 'idenXML', 'version', 'runMode'
								, 'Responsibility'
								, 'userName', 'processDate', 'modUser', 'modDate'
								, 'allowMod' , 'allowDel', 'inActDeff'
								, 'Identifications'
								, 'rptUnitFILevel', 'rptUnitFICode'
								, 'sponsorFILevel', 'sponsorFICode'
								, {name: 'contactName', mapping: 'ContactInfo > contactName'}
								, {name: 'areaCode', mapping: 'ContactInfo > areaCode'}
								, {name: 'phoneNum', mapping: 'ContactInfo > phoneNum'}
								, {name: 'phoneExt', mapping: 'ContactInfo > phoneExt'}
								, {name: 'email', mapping: 'ContactInfo > email'}
								, {name: 'address1', mapping: 'ContactInfo > address1'}
								, {name: 'address2', mapping: 'ContactInfo > address2'}
								, {name: 'address3', mapping: 'ContactInfo > address3'}
								, {name: 'city', mapping: 'ContactInfo > city'}
								, {name: 'province', mapping: 'ContactInfo > province'}
								, {name: 'postalCode', mapping: 'ContactInfo > postalCode'}
								, {name: 'country', mapping: 'ContactInfo > country'}								
								, {name: 'clntHeldDocTrack', mapping: 'BrokIntrRegDetl > clntHeldDocTrack'}
								, {name: 'clntHeldWholdable', mapping: 'BrokIntrRegDetl > clntHeldWholdable'}
								, {name: 'clntHeldRptable', mapping: 'BrokIntrRegDetl > clntHeldRptable'}
								, {name: 'nomineeDocTrack', mapping: 'BrokIntrRegDetl > nomineeDocTrack'}
								, {name: 'nomineeWholdable', mapping: 'BrokIntrRegDetl > nomineeWholdable'}
								, {name: 'nomineeRptable', mapping: 'BrokIntrRegDetl > nomineeRptable'}
								, {name: 'brokuuid', mapping: 'BrokIntrRegDetl > brokuuid'}
								, {name: 'brokversion', mapping: 'BrokIntrRegDetl > version'}
								
								]
				,listeners: {
					load: function(store, records)
					{
						Ext.each(records, function(record){
							record.data['deff'] = DesktopWeb.Util.getDateDisplayValue(record.data['deff']);
							record.data['stopDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['stopDate']);
							record.data['appLowThresDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['appLowThresDate']);
							record.data['processDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['processDate']);
							record.data['modDate'] = DesktopWeb.Util.getDateDisplayValue(record.data['modDate']);

							record.data['idenXML'] = _controller.getIdentifiersByFFI(record.data['ffiuuid'], record);
							record.data['Responsibility']  = _controller.generateResponsibilities(record.data);
                            
                            if (DesktopWeb._SCREEN_PARAM_MAP['market'].toUpperCase() == _MARKET_CANADA) {
                                var phoneNumber = record.data['phoneNum'].replace(/-/g, '').trim();
                                record.data['phoneNum'] = phoneNumber.substr(0, 3) + '-' + 
                                                          phoneNumber.substr(3, 3) + '-' + 
                                                          phoneNumber.substr(6, 4);
                            }
						});
						
						store.filterBy(function(record){
							return record.data.runMode != _controller.DEL}
						);
						_grids['finInstGrd'].getSelectionModel().selectFirstRow();

					}
				}
			})
			,clearGridData: function()
			{
				if (_grids['finInstGrd'].viewReady)
				{
					_grids['finInstGrd'].clearData();
				}
			}
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
				,listeners: {
					rowselect: function(selModel, index, record){_controller.selectFFI(record);}
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
					,{header: _translationMap['Regulation'], id:'regulation', dataIndex: 'complyRule', width: 100
						,renderer: function(val, metaData, record){return _controller.getDisplay('regulationList',val)}
					}
					,{header: _translationMap['Level'], id:'level', dataIndex: 'level', width: 75
						,renderer: function(val, metaData, record){return _controller.getDisplay('FFILevelList',val)}
					}
					,{header: _translationMap['Code'], id:'code', dataIndex: 'code', width: 75}
					
					,{header: _translationMap['Classification'], id:'classification', dataIndex: 'classification'
						,renderer: function(val){return (_controller.getDisplay('FFIList', val));}
					}
					,{header: _translationMap['ReportingFFI'], id:'reportingFFI', dataIndex: 'reportingFFI', width: 120
						,renderer: function(val){return (_controller.getDisplay('reportingFFIList', val));}
					}
					,{header: _translationMap['EffectiveDate'], id:'effectiveDate', dataIndex: 'deff', width: 80}
					,{header: _translationMap['StopDate'], id:'stopDate', dataIndex: 'stopDate', width: 80}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,handler: function(){_controller.openActionPopup(_controller.ADD, _controller.popupList['FFI']);}
					
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openActionPopup(_controller.MOD, _controller.popupList['FFI']);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.deleteFFISelectedRecord();}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'moreBtn'
					,text: _translationMap['More']
					,handler: function(){_controller.clickHandleMoreBtn();}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'adminBtn'
					,text: _translationMap['Admin']
					,handler: function(){_controller.openAdminPopup();}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'historicalBtn'
					,text:_translationMap['Historical']
					,handler: function(){_controller.openHistoryPopup();}
				})
			]
		})
		,idenGrd: new DesktopWeb.AdvancedControls.GridPanel({
			autoScroll: true
			,height: 175
			,autoExpandColumn: 'idType'
			,store: new Ext.data.XmlStore({
				record: 'Identification'
				,fields: ['key', 'uuid', 'idType', 'idValue', 'deff'
						, 'stopDate', 'idStat', 'cntryOfIssue'
						, 'errMsg', 'warnMsg', 'version', 'runMode', 'level' , 'code'
						, 'displayValue'
						, 'groupType'
						, 'allowMod' , 'allowDel']
				,listeners: {
					load: function(store, records)
					{
						store.filterBy(function(record){return record.data.runMode != _controller.DEL});
						if (_grids['idenGrd'].viewReady)
							_grids['idenGrd'].getSelectionModel().selectFirstRow();
					}
				}
			})
			,listeners: {
				viewready: function(){
					_controller.refreshIdenGrid();
					_grids['idenGrd'].getSelectionModel().selectFirstRow();
					_controller.updateFFIButtonsState();
				}
			}
			,clearGridData: function()
			{
				if (_grids['idenGrd'].viewReady)
				{
					_grids['idenGrd'].clearData();
				}
			}
			,selModel: new Ext.grid.RowSelectionModel({
				singleSelect: true
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
					,{header: _translationMap['IDType'], id: 'idType' ,dataIndex: 'idType'
							,width: 300
							,renderer: function(val, metaData, record)
								{ 
									var type = '';
									if(_grids['finInstGrd'].getSelectedRecord() != null) {
										type = _grids['finInstGrd'].getSelectedRecord().data['level'];
									}

									if (type == _controller.FUND_LEVEL || type == _controller.FUNDGROUP_LEVEL)
										return (_controller.getDisplay('idTypeFIList', val));
									else
										return (_controller.getDisplay('idTypeList', val));
								}
					}
					,{header: _translationMap['IDValue'], id: 'idValue' ,dataIndex: 'idValue', width: 300}
				]
			})
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'addBtn'
					,text: _translationMap['Add']
					,handler: function(){_controller.openIdenActionPopup(_controller.ADD, _controller.popupList['IDEN']);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'modBtn'
					,text: _translationMap['Modify']
					,handler: function(){_controller.openIdenActionPopup(_controller.MOD, _controller.popupList['IDEN']);}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'delBtn'
					,text: _translationMap['Delete']
					,handler: function(){_controller.deleteIdenSelectedRecord();}
				})
			]
		})
	}

	var _popup_tabs = {
		popup_FFITab: new Ext.TabPanel({
			columnWidth: 1
			,labelWidth: 85
			,itemId: 'popup_FFITab'
			,activeTab: 0
			,height: 250
			,border: false
			,plain: true
            ,deferredRender: false
			,defaults: {
				layout: 'form'
				,border: false
				,autoHeight: false
			}
			,style: 'padding-bottom: 5px'
			,items: [
				{
					layout: 'column'
					,title: _translationMap['Address']
					,id: 'popup_AddressTab'
					,border: false					
					,defaults: {
						layout: 'form'
						,border: false
                        ,style: 'padding-left: 5px; padding-top: 5px;'
					}
					,items: [
						{
                            columnWidth: 1
							,labelWidth: 100
							,items:[
								_fields['Address1TextField']
								,_fields['Address2TextField']
								,_fields['Address3TextField']
								,_fields['CityTextField']
                                ,_fields['PostalCodeTextField']
								,_fields['ProvinceTextField']
                                ,_fields['CountryDropDown']
							]
						}
					]
				}			
				,{
					layout: 'column'
					,title: _translationMap['Contact']
					,id: 'popup_ContactTab'
					,border: false
					,defaults: {
						layout: 'form'
						,border: false
                        ,style: 'padding-left: 5px; padding-top: 5px;'
					}
					,items: [
						{
							labelWidth: 140
							,items:[
								_fields['ContactNameTextField']
								,_fields['ContactEmailTextField']
                                ,_fields['ContactPhoneNumberTextField']
								,_fields['ContactPhoneExtNumberTextField']
							]
						}
					]
				}			
			]
		})
	}	

	var _popups = {
		finInstPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			width: 720
			,autoScroll: true
			,action: null
			,closeAction: 'hide'
			,title: ''
			,idenGridSet: null
			,deferredRender: false
			,modal: true
			,defaults: {border:false}
			,items: [
				{
					layout: 'column'
					,items: [
					{
						layout: 'form'
						,itemId: 'popup_main'
						,style: 'padding: 15px 5px;'
						,border:false
						,labelWidth: 85
						,columnWidth: 0.5
						,items: [
							new DesktopWeb.Controls.SMVComboBox({
								itemId: 'pRegulationFld'
								,fieldLabel: _translationMap["Regulation"]
								,width: _searchIDFieldPopupWidth
								,editable: false
								,allowBlank: false
								,listeners:{
									select : function(fld, record, index){
										_controller.setFundGroupList(record.data.code);
										_controller.setSuggestService(_popups['finInstPopup'].getField('pLevelFld').getValue()
											, _controller.popupList['FFI'], '');
									}
								}
							})
							,new DesktopWeb.Controls.SMVComboBox({
								itemId: 'pLevelFld'
								,fieldLabel: _translationMap['Level']
								,width: _searchIDFieldPopupWidth
								,editable: false
								,allowBlank: false
								,listeners: {
									select: function(combo, record, index){
										_controller.setSuggestService(record.data.code
											, _controller.popupList['FFI'], '');
									}
								}
							})
							,new DesktopWeb.Controls.SuggestField({
								itemId: 'pFundFld'
								,fieldLabel: _translationMap["Code"]
								,width: _searchIDFieldPopupWidth
								,smartview: 'fundOnlySearch'
								,addtlSearchParams: [{name: 'inclInactive', valueFn: function(){return 'yes'}}]
								,fields: ['fundCode', 'fundCategory', 'fndDisp' ]
								,valueField: 'fundCode'
								,displayField: 'fndDisp'
								,emptyText: _translationMap['EmptyText_Fund']
								,listeners: {
									select: function(combo, record, index){
										if (_popups[_controller.popupList['FFI']].action == _controller.ADD) {
											_popups[_controller.popupList['FFI']].getField('pAggregationLevelFld').loadData(_controller.getDynamicAggregationList());
										}
										//populate Address/Contacts/Identification for fund 
										if (_controller.validateFields('pFundFld')){
											_controller.searchAddressContactIden(_popups[_controller.popupList['FFI']].getField('pRegulationFld').getValue()
																			 ,_popups[_controller.popupList['FFI']].getField('pLevelFld').getValue()
																			 ,record.data['fundCode'])
										}
									}
								}
							})
							,new DesktopWeb.Controls.SMVComboBox({
								itemId: 'pFundGroupFld'
								,lastQuery: ''
								,fieldLabel: _translationMap["Code"]
								,width: _searchIDFieldPopupWidth
								,editable: false
								,listeners: {
									load: function(store, records) 
									{
										store.filterBy(function(record){return record.get('code') != _controller.BLANK});
									}
									,select: function(combo, record, index){
										if (_popups[_controller.popupList['FFI']].action == _controller.ADD) {
											_popups[_controller.popupList['FFI']].getField('pAggregationLevelFld').loadData(_controller.getDynamicAggregationList());
										}
										//populate Address/Contacts for Fund Group
										if (_controller.validateFields('pFundGroupFld')){
											_controller.searchAddressContactIden(_popups['finInstPopup'].getField('pRegulationFld').getValue()
																			 ,_popups['finInstPopup'].getField('pLevelFld').getValue()
																			 ,_popups['finInstPopup'].getField('pFundGroupFld').getValue())
										}
									}
								}
							})
							,new DesktopWeb.Controls.SuggestField({
								itemId: 'pLegalEntityFld'
								,fieldLabel: _translationMap["Code"]
								,width: _searchIDFieldPopupWidth
								,smartview: 'entWhereUsedSearch'
								,addtlSearchParams: [{name: 'entityWhereused', valueFn: function(){return '15'}}]
								,fields: ['whereUseKey', 'displayValue' ]
								,valueField: 'whereUseKey'
								,displayField: 'displayValue'
								,emptyText: _translationMap['EmptyText_LegalEntity']
								,listeners: {
									select: function(combo, record, index){
										if (_popups[_controller.popupList['FFI']].action == _controller.ADD) {
											_popups[_controller.popupList['FFI']].getField('pAggregationLevelFld').loadData(_controller.getDynamicAggregationList());
										}
										//populate Address/Contacts/Identification for Sponsor
										if (_controller.validateFields('pLegalEntityFld')){
											_controller.searchAddressContactIden(_popups['finInstPopup'].getField('pRegulationFld').getValue()
															,_popups['finInstPopup'].getField('pLevelFld').getValue()
															,_popups['finInstPopup'].getField('pLegalEntityFld').getValue())
										}
									}
								}
							})
							,new DesktopWeb.Controls.SuggestField({
								itemId: 'pBrokerFld'
								,fieldLabel: _translationMap["Code"]
								,width: _searchIDFieldPopupWidth
								,smartview: 'brokerSearch'
								,fields: ['displayValue', 'agencyCode', 'brokerDesc'  ]
								,valueField: 'agencyCode'
								,displayField: 'displayValue'
								,emptyText: _translationMap['EmptyText_Broker']
								,listeners: {
									select: function(combo, record, index){
										if (_popups[_controller.popupList['FFI']].action == _controller.ADD) {
											_popups[_controller.popupList['FFI']].getField('pAggregationLevelFld').loadData(_controller.getDynamicAggregationList());
										}
									}
								}
							})
							,new DesktopWeb.Controls.SuggestField({
								itemId: 'pIntermediaryFld'
								,fieldLabel: _translationMap["Code"]
								,width: _searchIDFieldPopupWidth
								,smartview: 'intrSearch'
								,fields: ['intrCode', 'displayValue' ]
								,valueField: 'intrCode'
								,displayField: 'displayValue'
								,emptyText: _translationMap['EmptyText_Intermediary']
								,listeners: {
									select: function(combo, record, index){
										if (_popups[_controller.popupList['FFI']].action == _controller.ADD) {
											_popups[_controller.popupList['FFI']].getField('pAggregationLevelFld').loadData(_controller.getDynamicAggregationList());
										}
									}
								}
							})
							,{
								id: 'popup_fndGrp'
								,layout: 'form'
								,border: false
								,labelWidth: 85
								,items: [
									new DesktopWeb.Controls.SMVComboBox({
										itemId: 'pFundGroupForLegalEntityFld'
										,fieldLabel: _translationMap["FundGroup"]
										,width: _searchIDFieldPopupWidth
										,editable: false
									})
								]
							}
							,new DesktopWeb.Controls.SMVComboBox({
								itemId: 'pClassificationFld'
								,fieldLabel: _translationMap["Classification"]
								,width: _searchIDFieldPopupWidth
								,editable: false
								,allowBlank: true
							})
							,new DesktopWeb.Controls.DateField({
								itemId: 'pDeffFld'
								,fieldLabel: _translationMap['EffectiveDate']
								,width : 110
								,allowBlank: false
								,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
							})
							,new DesktopWeb.Controls.DateField({
								itemId: 'pStopDateFld'
								,fieldLabel: _translationMap['StopDate']
								,allowBlank: false
								,width : 110
								,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
							})
						]
					},{
						id: 'popup_FFITab'
						,columnWidth: 0.5
						,items:[_popup_tabs['popup_FFITab']]
					}
				]
				},{
					layout: 'form'
					,items:[
						{
							xtype: 'fieldset'
							,id: 'popup_ReportingFFI'
							,title: _translationMap['ReportingFFI']
							,labelWidth: 140
							,bodyStyle: 'padding:4px'
							,items:[
								new DesktopWeb.Controls.SMVComboBox({
									itemId: 'pReportingFFIFld'
									,fieldLabel: _translationMap['ReportingFFI']
									,width: _reportingFFIFieldPopupWidth
									,editable: false
									,allowBlank: false
									,listeners: {
										select: function(combo, record, index){
											if(_popups['finInstPopup'].getField('pRegulationFld').getValue() == _controller.REGULATIONCODECRSRP) {
												_controller.setCRSReportingFFI(record.data.code);
											} else {
												_controller.setReportingFFI(record.data.code);
											}
										}
									}
								})
								,new DesktopWeb.Controls.TextField({
									itemId: 'pDescriptionFld'
									,fieldLabel: _translationMap['Description']
									,width: _reportingFFIFieldPopupWidth
									,maxLength: 60
								})
								, new DesktopWeb.Controls.SMVComboBox({
										itemId: 'pApplyThresholdFld'
										,fieldLabel: _translationMap['ApplyThreshold']
										,width: _reportingFFIFieldPopupWidth
										,editable: false
								})
								, new DesktopWeb.Controls.DateField({
									itemId: 'pApplyThresholdDateFld'
									,fieldLabel: _translationMap['ApplyThresholdDate']
									,width: 120
									,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
								})
								,new DesktopWeb.Controls.SMVComboBox({
									itemId: 'pCountryFld'
									,fieldLabel: _translationMap['Country']
									,editable: true
									,allowBlank: false
									,width: _reportingFFIFieldPopupWidth
									,listeners: {
										select: function() {
											if (_popups['finInstPopup'].getField('pCountryFld').getValue() == _COUNTRY_CODE) {
												_controller.generateFilerDropdown(_popups['finInstPopup']);
											} else {
												_controller.clearFilerCategoryList();
											}
										}
									}
								})
								,new DesktopWeb.Controls.ComboBox({
									itemId: 'pReportingUnitFld'
									,fieldLabel: _translationMap['ReportingUnit']
									,width: _reportingFFIFieldPopupWidth
									,editable: true
									,allowBlank: true
									,valueField: 'FIDesc'
									,displayField: 'FIDesc'
									,FILevel: 'FILevel'
									,FICode: 'FICode'
									,tpl: '<tpl for=".">' + '<div class="x-combo-list-item">' + '{FIDesc}&nbsp;' + '</div></tpl>'
                            		,store: new Ext.data.XmlStore(
				                    {
				                    	record: 'Element'
				                    	,fields: ['FILevel', 'FICode', 'FIDesc']
				                    })									
									, getFILevel : function()
									{
										var rec = this.getSelectedRecord();
										var result = "";
										if (rec) 
											result = rec.data[this.FILevel];
										return result;
									}									
									, getFICode : function()
									{
										var rec = this.getSelectedRecord();
										var result = "";
										if (rec) 
											result = rec.data[this.FICode];
										return result;
									}
								})
								,new DesktopWeb.Controls.ComboBox({
									itemId: 'pFISponsor'
									,fieldLabel: _translationMap['FISponsor']
									,width: _reportingFFIFieldPopupWidth
									,editable: true
									,allowBlank: true
									,valueField: 'FISponsorDesc'
									,displayField: 'FISponsorDesc'
									,FILevel: 'FISponsorLevel'
									,FICode: 'FISponsorCode'
									,tpl: '<tpl for=".">' + '<div class="x-combo-list-item">' + '{FISponsorDesc}&nbsp;' + '</div></tpl>'
									,store: new Ext.data.XmlStore(
				                    {
				                    	record: 'Element'
				                    	,fields: ['FISponsorLevel', 'FISponsorCode', 'FISponsorDesc']
				                    })		
									, getFILevel : function()
									{
										var rec = this.getSelectedRecord();
										var result = "";
										if (rec) 
											result = rec.data[this.FILevel];
										return result;
									}									
									, getFICode : function()
									{
										var rec = this.getSelectedRecord();
										var result = "";
										if (rec) 
											result = rec.data[this.FICode];
										return result;
									}                            
								})
								,{
									layout: 'form'
									,labelWidth: 140
									,border: false
									,items:[
										new DesktopWeb.Controls.SMVComboBox({
											itemId: 'pAggregationLevelFld'
											,fieldLabel: _translationMap['AggregationFFI']
											,width: _reportingFFIFieldPopupWidth
											,editable: true
											,allowBlank: false
										})
									]
								}
								,{
									layout: 'form'
									,labelWidth: 140
									,border: false
									,items:[
										new DesktopWeb.Controls.SMVComboBox({
											itemId: 'pfilerCategoryFld'
											,fieldLabel: _translationMap['filerCategory']
											,width: _reportingFFIFieldPopupWidth
											,editable: true
											,allowBlank: true 
										})
									]
								}//end form
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
						//verify each field of popup
						if (_popups['finInstPopup'].isValid() && _popups['finInstPopup'].isNotDuplicated()){
							var validateResult = _controller.localValidateFFI(_popups['finInstPopup'].action, _popups['finInstPopup'].getData(_popups['finInstPopup'].action));
							if(validateResult) {
								_controller.clickHandle_okBtnOnFinInstPopup(
									_popups['finInstPopup'].action
									, _popups['finInstPopup'].getData(_popups['finInstPopup'].action));
							}
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups['finInstPopup'].hide();}
				})
			]		
					
			,init: function(action)
			{
				this.action = action;
				this.resetAllFields();
				var vTitle = _controller.getServiceTitle(DesktopWeb._SCREEN_PARAM_MAP['From_Menu']);

				switch(action)
				{
					case _controller.ADD:
					{
						this.setTitle(vTitle + ' - ' + _translationMap['Add']);
						this.populate(null, action);
						break;
					}
					case _controller.MOD:
					{
						this.setTitle(vTitle + ' - ' + _translationMap['Modify']);
						this.populate(null, action);
						break;
					}
				}

			}
			,isNotDuplicated: function() {
				var valid = true;
				var popup = _popups['finInstPopup'];
				popup.getField('pRegulationFld').clearInvalid();
				//handle the duplication in memory
				if (popup.action == _controller.ADD) {
					var  regRuleInvalid = false;
					var nDupRegRule = _grids['finInstGrd'].getStore().queryBy(function(record){
						var newPopupRegRule = popup.getField('pRegulationFld').getValue();
						var gridRecRegRule = record.get('complyRule');
						var newPopupLevel = popup.getField('pLevelFld').getValue();
						var gridRecLevel = record.get('level');
						var newPopupCode = popup.getField('pFundFld').getValue();
						//dynamic get Code
						if (newPopupLevel == _controller.FUNDGROUP_LEVEL) {
							newPopupCode = popup.getField('pFundGroupFld').getValue();
						} else if (newPopupLevel == _controller.LEGALENTITY_LEVEL) {
							newPopupCode = popup.getField('pLegalEntityFld').getValue();
						}
						var gridRecCode = record.get('code');
						var newPopupSD = DesktopWeb.Util.stringToDate(popup.getField('pDeffFld').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
						var newPopupED = DesktopWeb.Util.stringToDate(popup.getField('pStopDateFld').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
						var gridRecSD = DesktopWeb.Util.stringToDate(record.get('deff'), DesktopWeb.Util.getDateDisplayFormat());
						var gridRecED =DesktopWeb.Util.stringToDate(record.get('stopDate'), DesktopWeb.Util.getDateDisplayFormat());

						//check overlapping rule/level/code/StartDate/StopDate
						return ( (newPopupRegRule == gridRecRegRule && newPopupLevel == gridRecLevel && newPopupCode == gridRecCode)
								&& !(newPopupSD >= gridRecED || newPopupED <= gridRecSD))
					});
					if (nDupRegRule.length > 0 ) {
						popup.getField('pRegulationFld').markInvalid(_translationMap['ERR_DUPLICATED_RECORD']);
						regRuleInvalid = true;
					}
					if (regRuleInvalid) {
						return false;
					}
				}
				return valid;
			}
			,resetAllFields: function()
			{
				if ( this.rendered )
				{
					for (var name in _controller.ffiFldsList)
					{
						this.getField(_controller.ffiFldsList[name]).reset();
						this.getField(_controller.ffiFldsList[name]).setValue('');
						this.getField(_controller.ffiFldsList[name]).enableField();
						this.getField(_controller.ffiFldsList[name]).clearInvalid();
					}

					for (var name in _controller.ffiFldsCodeList)
					{
						this.getField(_controller.ffiFldsCodeList[name]).reset();
						this.getField(_controller.ffiFldsCodeList[name]).setValue('');
						this.getField(_controller.ffiFldsCodeList[name]).enableField();
						this.getField(_controller.ffiFldsCodeList[name]).clearInvalid();
					}
					//reset address and contacts
					for (var name in _controller.AddressContactFldList) {
						this.getField(_controller.AddressContactFldList[name]).reset();
						this.getField(_controller.AddressContactFldList[name]).setValue('');
						this.getField(_controller.AddressContactFldList[name]).enableField();
						this.getField(_controller.AddressContactFldList[name]).clearInvalid();
					}
					//reset identifications
					for (var name in _controller._idenFldsList) {
						this.getField(_controller._idenFldsList[name]).reset();
						this.getField(_controller._idenFldsList[name]).setValue('');
						this.getField(_controller._idenFldsList[name]).enableField();
						this.getField(_controller._idenFldsList[name]).clearInvalid();
					}
					
					for (var name in _controller.ffiBrokDetlFldsList)
					{
						this.getField(_controller.ffiBrokDetlFldsList[name]).reset();
						this.getField(_controller.ffiBrokDetlFldsList[name]).setValue('');
						this.getField(_controller.ffiBrokDetlFldsList[name]).enableField();
						this.getField(_controller.ffiBrokDetlFldsList[name]).clearInvalid();
					}
				}
			}
			,populate: function(record, action) //FFI
			{			
				switch( action )
				{
					case _controller.ADD:
					{ 
						this.getField('pRegulationFld').setValue(_fields['regulationSrch'].getValue());
						this.getField('pLevelFld').setValue(_fields['searchForSrch'].getValue());
						this.getField('pReportingFFIFld').setValue(_controller.defaultValue['reportingFFIList']);
						if (_fields['regulationSrch'].getValue() != _controller.BLANK) {
							_controller.setFundGroupList(_fields['regulationSrch'].getValue());
						}
						_controller.setSuggestService(_fields['searchForSrch'].getValue(), _controller.popupList['FFI'], '', action);
						
						//The initiate state is set as blank and this field is not allowed to be blank
						//if default is set as blank again ,the validation will be enabled.
						//To protect the error on open screen, we have to check the default first
						if (_controller.defaultValue['FFIList'] != _controller.BLANK)
							this.getField('pClassificationFld').setValue(_controller.defaultValue['FFIList']);
							
						this.getField('pDeffFld').setValue(_controller.defaultValue['effectiveDate']);
						this.getField('pStopDateFld').setValue(_controller.defaultValue['stopDate']);

						_controller.setReportingFFI(this.getField('pReportingFFIFld').getValue());

						break;
					}
					case _controller.MOD:
					{
						var record = _grids['finInstGrd'].getSelectedRecord();
						//Has to set before set each field.

						if (record.data['inActDeff'] == _controller.YES) {
							this.getField('pDeffFld').disable();
						} else {
							this.getField('pDeffFld').enable();
						}

						for (var name in _controller.ffiFldsList)
                        {
                           this.getField(_controller.ffiFldsList[name]).setValue(record.data[name]);
                        }
						
						if (record.data['countryCode'] == _COUNTRY_CODE) {
							_controller.generateFilerDropdown(_popups['finInstPopup']);
                        } 

						_controller.setSuggestService(record.data['level']
							, _controller.popupList['FFI'], record.data['code']
							, _controller.MOD);

						for (var name in _controller.ffiBrokDetlFldsList)
						{
							this.getField(_controller.ffiBrokDetlFldsList[name]).setValue(record.data[name]);
						}

						if (record.data['runMode'] == _controller.ADD)
						{
							this.getField('pLevelFld').enableField();
							this.getField(_controller.ffiFldsCodeList[record.data['level']]).enableField();
							
							if (this.getField('pRegulationFld').store.getCount() <= 1)
								this.getField('pRegulationFld').disableField();
							else
								this.getField('pRegulationFld').enableField();
						}
						else
						{
							this.getField('pRegulationFld').disableField();
							this.getField('pLevelFld').disableField();
						}
		
						var list = _controller.getAggregationFFIList(record.data['level'],record.data['code'], record.data['displayValue']);
						_popups[_controller.popupList['FFI']].getField('pAggregationLevelFld').loadData(list);
						if ((record.data['aggrFfiCode'] != null && record.data['aggrFfiCode'] != '') && _controller.getAggretionApply() == "yes") {
							this.getField('pAggregationLevelFld').setValue(record.data['aggrffiLevel'] + "-" + record.data['aggrFfiCode']);
						}
						
						var dispReporingUnitLabel = _controller.getDisplayReportingUnit(record.data['rptUnitFICode'], record.data['rptUnitFILevel']);
						this.getField('pReportingUnitFld').setValue(dispReporingUnitLabel);
    
						var dispFISponsorLabel = _controller.getDisplayFISponsor(record.data['sponsorFICode'], record.data['sponsorFILevel']);
						this.getField('pFISponsor').setValue(dispFISponsorLabel);
						
						//Populate Contact and Address Data
						for (var name in _controller.AddressContactFldList)
						{
							this.getField(_controller.AddressContactFldList[name]).setValue(record.data[name]);
						}																
						break;
					}
					case _controller.DEL:
					{
						break;
					}
				}
			}
			,getData: function(action)
			{
				var data = {};
				var n = '';
				var record = null;

				data['runMode']             = action;
				
				if (action == _controller.MOD)
				{
					var gRecord = _grids['finInstGrd'].getSelectedRecord();					
					if (gRecord)
					{
						if (gRecord.data['errMsg'] != _translationMap['ERROR_Identification'])
						{
							data['errMsg'] = '';
						}
						
						if (gRecord.data['warnMsg'] != _translationMap['WARNING_Identification'])
							data['warnMsg'] = '';
					}
				}

				for (var name in _controller.ffiFldsList)
				{		
					data[name] = this.getField(_controller.ffiFldsList[name]).getValue();
				}
				
				data['rptUnitFILevel'] = this.getField('pReportingUnitFld').getFILevel();
				data['rptUnitFICode']  = this.getField('pReportingUnitFld').getFICode();
			
				data['sponsorFILevel'] = this.getField('pFISponsor').getFILevel();
				data['sponsorFICode']  = this.getField('pFISponsor').getFICode();
        
				this.getField(_controller.ffiFldsList[name]).getValue();
				
				//CDOT set Aggregation FFI for requestXML
				if (_controller.getAggretionApply() == "yes" && this.getField('pAggregationLevelFld').getValue() != null) {
					var aggrfficode = this.getField('pAggregationLevelFld').getValue();
					var selectedFFILevel = this.getField('pLevelFld').getValue();

					var aggrffilevel = aggrfficode.substring(0, aggrfficode.indexOf('-'));
					aggrfficode = aggrfficode.substring(aggrfficode.indexOf('-')+1,aggrfficode.length);

					data['aggrFfiCode'] = aggrfficode;
					data['aggrffiLevel'] = aggrffilevel;
					data['aggrDisplayValue'] = this.getField('pAggregationLevelFld').getValueDesc();
				}
													
				data['code']  = this.getField(_controller.ffiFldsCodeList[data['level']]).getValue();
				data['displayValue'] = '';
				var selectedCodeRecord = this.getField(_controller.ffiFldsCodeList[data['level']]).getSelectedRecord();
				
				if (selectedCodeRecord && selectedCodeRecord != undefined)
				{
					switch(data['level'] )
					{
						case _controller.FUND_LEVEL      : {data['displayValue'] =  selectedCodeRecord.get('fndDisp'); break;}
						case _controller.FUNDGROUP_LEVEL : {data['displayValue'] =  selectedCodeRecord.get('value'); break;}
						default : {data['displayValue'] =  selectedCodeRecord.get('displayValue');  break;}
					}
					
				}
				
				for (var name in _controller.ffiBrokDetlFldsList)
				{
					data[name] = this.getField(_controller.ffiBrokDetlFldsList[name]).getValue();
				}

				data['Responsibility']    = _controller.generateResponsibilities(data);
				if (data['level'] != _controller.LEGALENTITY_LEVEL)
					data['fundGroup'] = '';

				for (var name in _controller.AddressContactFldList)
				{
					data[name] = this.getField(_controller.AddressContactFldList[name]).getValue();
				}

				return data;

			}

		})
		,idenPopup: new DesktopWeb.AdvancedControls.PopupWindow({
			action: null
			,idenLevel : ''
			,idenCode : ''
			,idenGroupType : ''
			,idenName : ''
			,width: 425
			,closeAction: 'hide'
			,title: ''
			,modal: true
			,deferredRender: false
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
							,editable: false
							,width: _searchIDFieldWidth
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'pCodeFld'
							,fieldLabel: _translationMap["Label_Code"]
							,width: _searchIDFieldWidth
							,allowBlank: false
							,editable: false
							,hidden: false
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pIdTypeFld'
							,fieldLabel: _translationMap['IDType']
							,width: _searchIDFieldWidth
							,allowBlank: true
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pIdTypeFIFld'
							,fieldLabel: _translationMap['IDType']
							,width: _searchIDFieldWidth
							,allowBlank: true
							,editable: true
						})
						,new DesktopWeb.Controls.TextField({
							itemId: 'pIdValueFld'
							,fieldLabel: _translationMap['IDValue']
							,width: _searchIDFieldWidth
							,allowBlank: false
							,emptyText :''
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
							,width: _searchIDFieldWidth
							,allowBlank: true
							,editable: true
						})
						,new DesktopWeb.Controls.SMVComboBox({
							itemId: 'pStatusFld'
							,fieldLabel: _translationMap['Status']
							,width: _searchIDFieldWidth
							,allowBlank: false
						})
					]
				}
			]
			,buttons: [
				new DesktopWeb.Controls.ActionButton({
					itemId: 'okBtn'
					,text: _translationMap['OK']
					,handler: function(){						
						var allData = _popups[_controller.popupList['IDEN']].getData(_popups[_controller.popupList['IDEN']].action);
						var isValid = _popups[_controller.popupList['IDEN']].isValid() ;
						var validateResult = _controller.localValidateIDEN(_popups[_controller.popupList['IDEN']].action, allData);
						
						if (isValid && validateResult && _popups['idenPopup'].isNotDuplicatedIDEN()){							
							_controller.clickHandle_okBtnOnIdenPopup(
								_popups[_controller.popupList['IDEN']].action
								, allData);
						}
					}
				})
				,new DesktopWeb.Controls.ActionButton({
					itemId: 'cancelBtn'
					,text: _translationMap['Cancel']
					,handler: function(){_popups[_controller.popupList['IDEN']].hide();}
				})
			]
			,init: function(action)
			{
				this.resetAllFields();
				this.action = action;

				switch(action){
					case _controller.ADD:{
						this.setTitle(_translationMap['IdentificationDetails'] + " - " + _translationMap['Add']);
						this.populate(null, action);
						break;
					}
					case _controller.MOD:{
						this.setTitle(_translationMap['IdentificationDetails'] + " - " + _translationMap['Modify']);
						this.populate(_grids['idenGrd'].getSelectedRecord(), this.action);
						break;
					}
					case _controller.DEL:{
						this.setTitle(_translationMap['IdentificationDetails'] + " - " + _translationMap['Delete']);
						break;
					}
				}
			}
			
			,isNotDuplicatedIDEN: function() {
				var valid = true;
				var popup = _popups['idenPopup'];
				popup.getField('pIdTypeFIFld').clearInvalid();
				//handle the duplication in memory for identification, IDType/IssueCountry/Dates
				if (popup.action == _controller.ADD) {
					var  regRuleIDENInvalid = false;
					var nDupRegRuleIDEN = _grids['idenGrd'].getStore().queryBy(function(record){
						var newPopupIDType = popup.getField('pIdTypeFIFld').getValue(); 
						var newPopupIssueCnty = popup.getField('pCntryFld').getValue();

						var gridIDty = record.get('idType');
						var gridCntry = record.get('cntryOfIssue');
						var newPopupSD = DesktopWeb.Util.stringToDate(popup.getField('pDeffFld').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
						var newPopupED = DesktopWeb.Util.stringToDate(popup.getField('pStopDateFld').getDisplayDateString(), DesktopWeb.Util.getDateDisplayFormat());
						var gridRecSD = DesktopWeb.Util.stringToDate(record.get('deff'), DesktopWeb.Util.getDateDisplayFormat());
						var gridRecED =DesktopWeb.Util.stringToDate(record.get('stopDate'), DesktopWeb.Util.getDateDisplayFormat());
						//check overlapping IDType/Issuecountry/StartDate/StopDate
						return ( (newPopupIDType == gridIDty && newPopupIssueCnty == gridCntry)
								&& !(newPopupSD >= gridRecED || newPopupED <= gridRecSD))
					});
					if (nDupRegRuleIDEN.length > 0 ) {
						popup.getField('pIdTypeFIFld').markInvalid(_translationMap['ERR_DUPLICATED_IDEN']);
						regRuleIDENInvalid = true;
					}
					if (regRuleIDENInvalid) {
						return false;
					}
				}
				return valid;
			}
			,resetAllFields: function()
			{
				if ( this.rendered )
				{
					for (var name in _controller.idenFldsList)
					{						
						this.getField(_controller.idenFldsList[name]).reset();								
						this.getField(_controller.idenFldsList[name]).setValue('');
						this.getField(_controller.idenFldsList[name]).enableField();
						this.getField(_controller.idenFldsList[name]).clearInvalid();					
					}
					
					
					this.getField('pIdTypeFIFld').reset();
					this.getField('pIdTypeFIFld').setValue('');
					this.getField('pIdTypeFIFld').enableField();
					this.getField('pIdTypeFIFld').clearInvalid();
				}
			}
			
			,populate: function(record, action) //identification
			{
				
				var selectedFFI = _grids['finInstGrd'].getSelectedRecord();
				idenLevel = selectedFFI.get('level');
				idenCode = selectedFFI.get('code');
				idenName = selectedFFI.get('displayValue');
				
				this.getField('pLevelFld').setValue(idenLevel);
				this.getField('pCodeFld').setValue(idenCode);
				this.getField('pCodeFld').setRawValue(selectedFFI.get('displayValue'));
				
				_controller.setSuggestService(
					idenLevel
					, _controller.popupList['IDEN']
					, idenCode);
										
				this.getField('pLevelFld').disableField();
				this.getField('pCodeFld').disableField();

				switch (action)
				{
					case _controller.ADD :

						this.getField('pDeffFld').setValue(_controller.defaultValue['effectiveDate']);

						this.getField('pStopDateFld').setValue(_controller.defaultValue['stopDate']);

						if ( idenLevel == _controller.FUND_LEVEL
							|| idenLevel == _controller.FUNDGROUP_LEVEL)
						{
							this.getField('pIdTypeFld').hide();
							this.getField('pIdTypeFld').allowBlank = true;
							
							
							this.getField('pIdTypeFIFld').show();
							this.getField('pIdTypeFIFld').allowBlank = false;
							
						}

						else
						{
							this.getField('pIdTypeFld').show();							
							this.getField('pIdTypeFld').allowBlank = false;
							
							this.getField('pIdTypeFIFld').hide();													
							this.getField('pIdTypeFIFld').allowBlank = true;
							this.getField('pIdTypeFIFld').validate();
						}

						if (this.rendered)
							this.syncShadow();

						break;
					case _controller.MOD :
						this.getField('pIdValueFld').setValue(record.data['idValue']);
						this.getField('pDeffFld').setValue(DesktopWeb.Util.getDateDisplayValue(record.data['deff']));
						this.getField('pStopDateFld').setValue(DesktopWeb.Util.getDateDisplayValue(record.data['stopDate']));
						this.getField('pCntryFld').setValue(record.data['cntryOfIssue']);
						this.getField('pStatusFld').setValue(record.data['idStat']);
						if (record.data['countryCode'] != null) {
							this.getField('pCountryFld').setValue(record.data['countryCode']);
						}
						//CDOT FATCA
						if (_controller.getAggretionApply() == "yes" && record.data['aggrFfiCode'] != null) {
							this.getField('pAggregationLevelFld').setValue(record.data['aggrFfiCode'] + " " + record.data['aggrffiLevel']);
						}

						
						if (idenLevel == _controller.FUND_LEVEL
							|| idenLevel == _controller.FUNDGROUP_LEVEL)
						{
							this.getField('pIdTypeFld').hide();
							this.getField('pIdTypeFld').allowBlank = true;
							this.getField('pIdTypeFld').validate();
							
							this.getField('pIdTypeFIFld').show();
							this.getField('pIdTypeFIFld').setValue(record.data['idType']);
							this.getField('pIdTypeFIFld').allowBlank = false;
							this.getField('pIdTypeFIFld').validate();
						}
						else
						{
							this.getField('pIdTypeFld').show();
							this.getField('pIdTypeFld').setValue(record.data['idType']);
							this.getField('pIdTypeFld').allowBlank = false;
							this.getField('pIdTypeFld').validate();
							
							this.getField('pIdTypeFIFld').hide();
							this.getField('pIdTypeFIFld').allowBlank = true;
							this.getField('pIdTypeFIFld').validate();
						}

						if (this.rendered)
							this.syncShadow();

						break;
				};
			}
			, getData: function(action)
			{
				var data = {};

				data['errMsg']    = _controller.BLANK;
				data['warnMsg']   = _controller.BLANK;
				data['runMode']   = action;
				data['groupType'] = _controller.BLANK;

				for (var name in _controller.idenFldsList)
				{
					data[name] = this.getField(_controller.idenFldsList[name]).getValue();
				}

				if (idenLevel == _controller.FUND_LEVEL
					|| idenLevel == _controller.FUNDGROUP_LEVEL)
					data['idType'] = this.getField('pIdTypeFIFld').getValue();
				
				var rec = _grids['finInstGrd'].getSelectedRecord();
				if(rec!= null) {
					var groupType = rec.data['complyRule'];
				}
			
				if (idenLevel == _controller.FUNDGROUP_LEVEL) {
					if(groupType == _controller.REGULATIONCODECRSRP) {
						data['groupType'] = _controller.GROUPTYPECRSRP;
					} else {
						data['groupType'] = _controller.GROUPTYPEFATCA;
					}
				}
					
				//reset
				data['code'] = idenCode;
				data['displayValue'] =  idenName;

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
	
	var _tabs = {
		FFITab: new Ext.TabPanel({
			columnWidth: 1
			,labelWidth: 85
			,itemId: 'FFITab'
			,activeTab: 0
			,border: true
			,plain: true
			,defaults: {
				layout: 'form'
				,border: true
				,autoHeight: false
			}
			,style: 'padding-bottom: 5px'
			,items: [
				{
					layout: 'column'
					,height: 175
					,title: _translationMap['ReportingFFI']
					,id: 'ReportingFFITab'
					,defaults: {
							layout: 'form'
							,style: 'margin: 5px'
					}
					,items: [
						{
							columnWidth: 0.50
							,labelWidth: 135
							,items:[
								_fields['reportingFFILabel']
								,_fields['descriptionLabel']
								,_fields['applyThresholdLabel']
								,_fields['applyThresholdDateLabel']
								,_fields['filerCategoryLabel']
							]
						}
						,{
							columnWidth: 0.50
							,labelWidth: 100
							,items:[
								_fields['countryLabel']
								,_fields['aggregationFFILabel']
								,_fields['reportingUnitLabel']
								,_fields['fiSponsorLabel']
							]
						}
					]
				}
				,{
					layout: 'column'
					,height: 175
					,title: _translationMap['Identification']
					,id: 'identificationTab'
					,defaults: {
							layout: 'form'
							,style: 'margin: 5px'
					}
					,items: _grids['idenGrd']
				}
				,{
					layout: 'column'
					,height: 175
					,title: _translationMap['Address']
					,id: 'AddressTab'
					,defaults: {
							layout: 'form'
							,style: 'margin-left: 5px; margin-top: 2px;'
					}
					,items: [
						{
							columnWidth: 1
							,labelWidth: 100
							,items:[
								_fields['Address1Label']
								,_fields['Address2Label']
								,_fields['Address3Label']
							]
						}
                        ,{
                            columnWidth: 0.5
							,labelWidth: 100
							,items:[
                                _fields['CityLabel']
								,_fields['ProvinceLabel']
							]
						}
                        ,{
                            columnWidth: 0.5
							,labelWidth: 100
							,items:[
                                _fields['PostalCodeLabel']
								,_fields['CountryFFILabel']	
							]
						}
					]
				}
				,{
					layout: 'column'
					,height: 175
					,title: _translationMap['Contact']
					,id: 'ContactTab'
					,defaults: {
							layout: 'form'
							,style: 'margin: 5px'
					}
					,items: [
						{
							columnWidth: 1
							,labelWidth: 140
							,items:[
								_fields['ContactNameLabel']
								,_fields['ContactEmailLabel']
                                ,_fields['ContactPhoneNumberLabel']
								,_fields['ContactPhoneExtNumberLabel']
							]
						}
					]
				}
			]
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
		,tabs: _tabs
		,layout: new Ext.Container({
			height: _layoutHeight
			, width: _layoutWidth
			, items: [
				{
					xtype: 'fieldset'
					,title: _translationMap['Search']
					,items: [
						{
							layout: 'column'
							,labelWidth: 65
							,items: [
								{
									columnWidth: 0.40
									,layout: 'form'
									,items: [
										_fields['regulationSrch']
										,_fields['searchForSrch']
									]
								}
								, {
									columnWidth: 0.60
									,layout: 'form'
									,items: [
										_fields['searchByFund']
										,_fields['searchByFundGroup']
										,_fields['searchByLegalEntity']
										,_fields['searchByBroker']
										,_fields['searchByIntermediary']
										,_buttons['cmdSearch']
									]
								}
							]
						}
					]
				}
				,_grids['finInstGrd']
				,{
					xtype: 'fieldset'
					,title: _controller.getServiceTitle(DesktopWeb._SCREEN_PARAM_MAP['From_Menu'])
					,layout: 'column'
					,items: [
						{
							columnWidth: 0.5
							,labelWidth: 80
							,layout: 'form'
							,items: [
								_fields['levelLabel']
								,{
									layout: 'column'
									,items: [
										{
											columnWidth: 1
											,layout: 'form'
											,items: [_fields['codeLabel']]
										}
										,{
											columnWidth: 0.55
											,labelWidth: 85
											,layout: 'form'
											,items: [_fields['deffLabel']]
										}
									]
								}
							]
						}
						,{
							columnWidth: 0.5
							,labelWidth: 85
							,layout: 'form'
							, items: [
								_fields['classificationLabel']
								,{
									id: 'fundGrpSection'
									,layout: 'form'
									,labelWidth: 85
									,items: [
										_fields['fundGroupLabel']
									]
								}
								,{
									layout: 'column'
									,items: [
										{
											columnWidth: 0.45
											,labelWidth: 65
											,layout: 'form'
											,items: [_fields['stopDateLabel']]
										}
									]
								}
							]
						}
						,_tabs['FFITab']
					]
				}
			]
		})


		,screenButtons: {
			items:[
				new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['OK']
						,handler: function(){
							if (_controller.getUpdateFlags())
								_controller.doValidateCommitScreen();
							else
								_controller.goToScreen();
						}
					}
				)
				,new DesktopWeb.Controls.ScreenButton(
					{
						text: _translationMap['Cancel']
						,handler: function(){
							if(_controller.getUpdateFlags()){
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
			]
		}
	}
}