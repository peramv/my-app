 /*********************************************************************************************
 * @file	IntRateMain.Resources.js
 * @author	Cherdsak Sangkasen
 * @desc	Resources JS file for Interest Rate for Investment screen
 *********************************************************************************************/
 /*
 *  History :
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  14 Jun 2017 Gomoot T. P0263240 CHG0048754 T85926
 *					- Enhance DYN DIF project - Add RateSplit
 */

DesktopWeb.ScreenResources = function(ctrlr)
{
	var _controller = ctrlr;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// content dimensions
	var _layoutHeight = 555;
	var _layoutWidth = 800;

	// **** fields ****
	var _fields = {
		fundCategorySrchSc : new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['InvestmentCategory']
				,width: 200
			}
		)
		, rateCodeTypeSrchSc: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel: _translationMap['RateCodeType']
				,width: 200
			}
		)
		, rateEntitySrc: new DesktopWeb.Controls.SMVComboBox(
			{
				fieldLabel:'tempSrc'
				,width: 200
			}
		)
		, fromDate: new DesktopWeb.Controls.DateField(
			{
				fieldLabel: _translationMap['FromDate']
				,width: 200
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
		, toDate : new DesktopWeb.Controls.DateField(
			{
				fieldLabel:  _translationMap['ToDate']
				, width: 200
				,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
			}
		)
			, userName: new DesktopWeb.Controls.Label(
			{
				fieldLabel:  _translationMap['Username']
			}
		)
		, modUser: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['ModUser']
			}
		)
		, procDate: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['ProcessDate']
			}
		)
		, modDate: new DesktopWeb.Controls.Label(
			{
				fieldLabel: _translationMap['ModDate']
			}
		)
	}

	// **** buttons ****
	var _buttons = {
		cmdAddIntRate: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Add']
				,itemId: 'addBtn'
				, handler: function(){_controller.openActionPopup('frmIntRate', _controller.ADD);}
			}
		)
		, cmdModIntRate: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Modify']
				,itemId: 'modBtn'
				, handler: function(){_controller.openActionPopup('frmIntRate', _controller.MOD);}
			}
		)
		, cmdDelIntRate: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Delete']
				,itemId: 'delBtn'
				, handler: function() {_controller.openActionPopup('frmIntRate', _controller.DEL);}
			}
		)
		, cmdMoreIntRate: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['More']
				,itemId: 'moreBtn'
				, handler: function() {_controller.doSearch(true);}
			}
		)
		, cmdIntRateAdmin: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Admin']
				 ,itemId: 'adminBtn'
				, handler: function(){
					_controller.openAdminPopup('intRate');
				}
			}
		)
		, cmdIntRateHist: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Historical']
				 ,itemId: 'historicalBtn'
				, handler: function(){
					_controller.openHistoryPopup('intRate');
				}
			}
		)
		, cmdAddIntRateScale: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Add']
				,itemId: 'addBtn'
				, handler: function(){_controller.openActionPopup( 'frmIntRateScale', _controller.ADD);}
			}
		)
		, cmdModIntRateScale: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Modify']
				 ,itemId: 'modBtn'
				, handler: function(){_controller.openActionPopup('frmIntRateScale', _controller.MOD);}
			}
		)
		, cmdDelIntRateScale: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Delete']
				,itemId: 'delBtn'
				, handler: function() {_controller.openActionPopup('frmIntRateScale', _controller.DEL);}
			}
		)
		, cmdIntRateScaleAdmin: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Admin']
				,itemId: 'adminBtn'
				, handler: function(){
					_controller.openAdminPopup('intRateScale');
				}
			}
		)
		, cmdIntRateScaleHist: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Historical']
				,itemId: 'historicalBtn'
				, handler: function(){
					_controller.openHistoryPopup('intRateScale');
				}
			}
		)

		, cmdSearch: new DesktopWeb.Controls.ActionButton(
			{
				text: _translationMap['Search']
				, handler: function(){
					_controller.doSearch(false);
				}
			}
		)
	}

	// **** grids ****
	var _grids = {
		grdIntRate: new DesktopWeb.AdvancedControls.GridPanel
		(
			{
				width: _layoutWidth
				,style: "margin-bottom:15px"
				,autoScroll: true
				,height: 250
				,store: new Ext.data.XmlStore
				(
					{
						record: 'InterestRate'
						,fields: ['interestRateUUID',
									'fundCategory',
									'fundCategoryDesc',
									'intCalcMthd',
									'intCalcMthdDesc',
									'rateCode',
									'rateCodeDesc',
									'rateCodeType',
									'rateCodeTypeDesc',
									'deff',
									'sequence',
									'intTerm',
									'intTermDesc',
									'rateType',
									'rateChange',
									'rateTypeDesc',
									'rateTypeChange',
									{name: 'rate', mapping: 'Scales > Scale > rate'}, /*Percent*/
									{name: 'interestRateScaleUUID', mapping: 'Scales > Scale > interestRateScaleUUID'}, /*Percent*/
									{name: 'scaleversion', mapping: 'Scales > Scale > version'}, /*Percent*/
									//{name: 'key', mapping: 'interestRateUUID'},
									'verified',
									'runMode',
									'version',
									'errMsg',
									'userName',
									'procDate',
									'modUser',
									'modDate',
									'updSeq',
									'ScalesNode'
									]
						,listeners: {
							load: function(store, records) {
								Ext.each(records, function(record){
											record.data.rateTypeChange = '';
											record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
											record.data.ScalesNode = IFDS.Xml.getNode(store.reader.xmlData,
														"/*//InterestRate[interestRateUUID='" + record.data.interestRateUUID
																+ "']/Scales");
											if (record.data.rateType != 'Percent')
												record.data.rate = '';
								});

								store.fireEvent('datachanged', store); //to set data in grid again

								store.filterBy(function(record){
										return (record.data.runMode != _controller.DEL);
									}
								)
							}
						}
					}
				)
				,origStore: new Ext.data.XmlStore
				(
					{
						record: 'InterestRate'
						,fields: ['interestRateUUID',
									'fundCategory',
									'fundCategoryDesc',
									'intCalcMthd',
									'intCalcMthdDesc',
									'rateCode',
									'rateCodeDesc',
									'rateCodeType',
									'rateCodeTypeDesc',
									'deff',
									'sequence',
									'intTerm',
									'rateType',
									'rateTypeDesc',
									{name: 'rate', mapping: 'Scales > Scale > rate'}, /*Percent*/
									{name: 'interestRateScaleUUID', mapping: 'Scales > Scale > interestRateScaleUUID'}, /*Percent*/
									{name: 'scaleversion', mapping: 'Scales > Scale > version'}, /*Percent*/
									'verified',
									'runMode',
									'version',
									'errMsg',
									'userName',
									'procDate',
									'modUser',
									'modDate',
									'updSeq',
									'ScalesNode'
									]
						,listeners: {
							load: function(origStore, records) {
								Ext.each(records, function(record){

											record.data.deff = DesktopWeb.Util.getDateDisplayValue(record.data.deff);
											var node = IFDS.Xml.getNode(origStore.reader.xmlData,
														"/*//InterestRate[interestRateUUID='" + record.data.interestRateUUID
																+ "']/Scales");
											if (record.data.rateType.toLowerCase() != 'percent')
												record.data.rate = '';
											//record.data.ScalesXML = (node != null) ? IFDS.Xml.serialize(node) : _controller.BLANK;

											record.data.ScalesNode = node;
								});
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel
				(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record)
							{
								_controller.setSelectedIntRate(record);
							}
							,rowdeselect: function(){
								_grids['grdIntRateScale'].clearData();
								_grids['grdRateSplit'].clearData();
							}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
							 , width: 25 }
							,{header: _translationMap['InvestmentCategory'], dataIndex: 'fundCategoryDesc', width:120}
							,{header: _translationMap['InterestCalculationMethod'], dataIndex: 'intCalcMthdDesc', width:150}
							,{header: _translationMap['RateCodeType'], dataIndex: 'rateCodeTypeDesc', width:100}
							,{header: _translationMap['RateCode'], dataIndex: 'rateCodeDesc', width:150}
							,{header: _translationMap['EffectiveDate'], dataIndex: 'deff', width:100}
							,{header: _translationMap['Sequence'], dataIndex: 'sequence', width:50}
							,{header: _translationMap['Term'], dataIndex: 'intTermDesc', width:100}
							,{header: _translationMap['RateType'], dataIndex: 'rateTypeDesc', width:80}
							,{header: _translationMap['Rate'], dataIndex: 'rate', width:80 }
							 // ,
								 // renderer: function(val){
									// var temp = DesktopWeb.Util.toDecimalFormat(val, DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator'],DesktopWeb._SCREEN_PARAM_MAP['thouSep']);
									// return (isNaN(parseFloat(temp))) ? '' : parseFloat(temp).toFixed(4).replace(".", DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator']);
								// } }
							]
					}
				)
				,getOrigStore : function() {
					return this.origStore;
				}
				,buttons: [
					_buttons['cmdAddIntRate']
					, _buttons['cmdModIntRate']
					, _buttons['cmdDelIntRate']
					, _buttons['cmdMoreIntRate']
					, _buttons['cmdIntRateAdmin']
					, _buttons['cmdIntRateHist']
				]
			}
		)
		, grdIntRateScale: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: '100%'
				,style: "margin:10px"
				,autoScroll: true
				,height: 150
				,store: new Ext.data.XmlStore(
					{
						record: 'Scale'
						,fields: ['interestRateScaleUUID',
								//  {name: 'id', mapping: 'interestRateScaleUUID'},
								  'runMode',
								  'updSeq',
								  'lower',
								  'upper',
								  'rate',
								  'rateType',
								  'version',
								  'userName',
								  'procDate',
								  'modUser',
								  'modDate',
								  'errMsg',
									'RateSplitNode',
									'interestRateUUID'
									]
						,listeners: {
							load: function(store, records) {
								Ext.each(records, function(record){
											var node = IFDS.Xml.getNode(store.reader.xmlData,
														"/*//Scale[interestRateScaleUUID='" + record.data.interestRateScaleUUID
																+ "']/RateSplitList");
											record.data.RateSplitNode = node;
								});

								store.fireEvent('datachanged', store); //to set data in grid again

								store.filterBy(function(record){
										return (record.data.runMode != _controller.DEL && record.data.rateType != 'Percent');
									}
								)
							}
						}
					}
				)
				,selModel: new Ext.grid.RowSelectionModel(
					{
						singleSelect: true
						,listeners: {
							rowselect: function(selModel, index, record)
							{
								_controller.setSelectedIntRateScale(record);
							}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
							 , width: 25 }
							//,{header: 'UUID', dataIndex: 'interestRateScaleUUID', width:300}
							//,{header: 'runMode', dataIndex: 'runMode', width:50}
							 ,{header: _translationMap['Lower'], dataIndex: 'lower', width:100}
									// ,renderer: function(val){
									// var temp = DesktopWeb.Util.toDecimalFormat(val,  DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator'],DesktopWeb._SCREEN_PARAM_MAP['thouSep']);
									// return (isNaN(parseFloat(temp))) ? '' : parseFloat(temp).toFixed(2).replace(".", DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator']);
								// } }
							 ,{header: _translationMap['Upper'], dataIndex: 'upper', width:100 }
									// ,renderer: function(val){
									// var temp = DesktopWeb.Util.toDecimalFormat(val,  DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator'],DesktopWeb._SCREEN_PARAM_MAP['thouSep']);
									// return (isNaN(parseFloat(temp))) ? '' : parseFloat(temp).toFixed(2).replace(".", DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator']);
								// }}
							 ,{header: _translationMap['Rate'], dataIndex: 'rate', width:100}
									 // ,renderer: function(val){
									// var temp = DesktopWeb.Util.toDecimalFormat(val,  DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator'],DesktopWeb._SCREEN_PARAM_MAP['thouSep']);
									// return (isNaN(parseFloat(temp))) ? '' : parseFloat(temp).toFixed(4).replace(".", DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator']);
								// } }
						]
					}
				)
				,buttons: [
					_buttons['cmdAddIntRateScale']
					, _buttons['cmdModIntRateScale']
					, _buttons['cmdDelIntRateScale']
					, _buttons['cmdIntRateScaleAdmin']
					, _buttons['cmdIntRateScaleHist']
				]
			}//grid

		)//grid
		, grdRateSplit: new DesktopWeb.AdvancedControls.GridPanel(
			{
				width: '100%'
				,style: "margin:10px"
				,autoScroll: true
				,height: 150
				,store: new Ext.data.XmlStore(
					{
						record: 'RateSplit'
						,fields: ['rateSplitUUID',
								 // {name: 'key', mapping: 'rateSplitUUID'},
									'interestRateScaleUUID',
								  'runMode',
								  'rateEntityType',
								  'rateEntityTypeDesc',
								  'rate',
								  'version',
								  'userName',
								  'procDate',
								  'modUser',
								  'modDate',
								  'errMsg'
									]
						,listeners: {
							load: function(store, records) {

								store.fireEvent('datachanged', store); //to set data in grid again

								store.filterBy(function(record){
										return (record.data.runMode != _controller.DEL);
									}
								)
							}
						}
					}
				)
				,colModel: new Ext.grid.ColumnModel(
					{
						defaults: {
							menuDisabled: true
						}
						,columns: [
							{dataIndex: 'errMsg', renderer: function(val) {return (val ? DesktopWeb.Util.buildErrorFlag(val) : ''); }
							 , width: 25 }
							,{header: _translationMap['Type'], dataIndex: 'rateEntityTypeDesc', width:150}
							,{header: _translationMap['Rate'], dataIndex: 'rate', width:50  }
									// ,renderer: function(val){
									// var temp = DesktopWeb.Util.toDecimalFormat(val,  DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator'],DesktopWeb._SCREEN_PARAM_MAP['thouSep']);
									// return (isNaN(parseFloat(temp))) ? '' : parseFloat(temp).toFixed(4).replace(".", DesktopWeb._SCREEN_PARAM_MAP['decimalSeparator']);
							 // }}
						]
					})
				,buttons: [
					 new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['Admin']
							,itemId: 'RateAdminBtn'
							, handler: function(){
								_controller.openAdminPopup('RateSplit');
							}
						}
					)

					, new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['Historical']
							,itemId: 'RateHistoricalBtn'
							, handler: function(){
								_controller.openHistoryPopup('RateSplit');
							}
						}
					)
				]
			}
		)//grid
	}

	// **** popups ****
	var _popups = {
		frmIntRate: new DesktopWeb.AdvancedControls.PopupWindow({
				action: null
				,rateType: null
				, width: 700
				, closeAction: 'hide'
				, modal: true
				, defaults: {border:false}
				, items: [
					{
						html: _translationMap['DeleteConfirmMsg']
						, style: 'text-align:center'
						, defaults: {border:false}
					}
					,{
						layout: 'form'
						,defaults: {border: false, labelWidth:50}
						,style: 'padding:5px;'
						,id: 'mainform'
						,items: [
							{
								layout: 'column'
								,id: 'mainColumn'
								, defaults: {border:false}
								,items: [
									{
										width: 350
										,layout: 'form'
										,id: 'col1'
										,labelWidth: 120
										,defaults: {border: false}
										,items: [
											new DesktopWeb.Controls.SMVComboBox({
												fieldLabel: _translationMap['InvestmentCategory']
												, itemId  : 'fundCategory'
												, allowBlank: false
												, editable: false
												, width: 200
												, lastQuery: ''
												, listeners:{
													select: function(combo, record, index) {
														_controller.populateDropdownsRule("fundCategory", record.data.code , false);
													}
												}
											})//fundCategory
											, new DesktopWeb.Controls.SMVComboBox({
												fieldLabel: _translationMap['InterestCalculationMethod']
												, itemId  : 'intCalcMthd'
												, allowBlank: false
												, editable: false
												, width: 200
												, lastQuery: ''
												, listeners:{
													select: function(combo, record, index) {
														_controller.populateDropdownsRule("intCalcMthd",  record.data.code, false);
													}
												}
											})	//intCalcMthd
											, new DesktopWeb.Controls.SMVComboBox({
												fieldLabel: _translationMap['RateCodeType']
												, itemId  : 'rateCodeType'
												, allowBlank: false
												, editable: false
												, width: 200
												, lastQuery: ''
												, listeners:{
													select: function(combo, record, index) {
														_controller.populateDropdownsRule("rateCodeType", record.data.code , false);
													}
												}}) //rateCodeType
											, new DesktopWeb.Controls.SMVComboBox({
												fieldLabel: _translationMap['RateCode']
												, itemId  : 'rateCode'
												, allowBlank: false
												, editable: false
												, width: 200
												, lastQuery: ''
												, listeners:{
													select: function(combo, record, index) {
														_controller.populateDropdownsRule("rateCode", record.data.code, false);
													}
												}
											})
										, new DesktopWeb.Controls.SMVComboBox(
											{
												fieldLabel: _translationMap['RateType']
												, itemId  : 'rateType'
												, allowBlank: false
												, editable: false
												, width: 200
												, lastQuery: ''
												, listeners:{
													select: function(combo, record, index) {
														_controller.populateDropdownsRule("rateType", record.data.code, false);
													}
												}
											})
										]
									}
									,{
										layout: 'form'
										,labelWidth: 120
										,defaults: {border: false}
										,id : 'col2'
										,items: [
											new DesktopWeb.Controls.DateField({
												fieldLabel: _translationMap['EffectiveDate']
												, itemId  : 'deff'
												, editable: false
												, width: 150
												,format: DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat())
											})
											, new DesktopWeb.Controls.SMVComboBox({
												fieldLabel: _translationMap['Term']
												, itemId  : 'intTerm'
												, editable: false
												, width: 150
												, lastQuery: ''
											})
											, new DesktopWeb.Controls.NumberField({
												fieldLabel: _translationMap['Rate']
												, itemId  : 'rateInt'
												, editable: false
												, width: 150
												, uuid :""
												, decimalPrecision: 4
												, minValue: 0
												, maxValue :100
												, setDefault : function() {
														uuid = "";
														version = 0;
														this.setValue('');
												}
											})
										, {
												//layout: 'form'
												xtype: 'fieldset'
												,id: 'rateSplitPercent'
												,labelWidth: 112
												,border: true
												,title: _translationMap['RateSplit']
												,items: []
											}
										]
									}
								]
							}
						]
					}
				]
				, buttons: [
					 new DesktopWeb.Controls.ActionButton({
							text: _translationMap['OK']
							, itemId : 'cmdIntRateSubmit'
							, handler: function(){
								if (_popups['frmIntRate'].isValid())
									_controller.doValidate("frmIntRate", _popups['frmIntRate'].action, _popups['frmIntRate'].getData());
							}
					})
					, new DesktopWeb.Controls.ActionButton({
						 text: _translationMap['Cancel']
						 ,itemId : 'cmdIntRateCancel'
						 , handler: function(){ _popups['frmIntRate'].hide();}
					})
				]
				, init: function(action)
				{
					this.get(0).hide();
					this.action = action;

					this.enableAllFields();
					this.clearPopupFields();
					this.clearAllFields();

					switch(action)
					{
						case _controller.ADD: {
							this.setTitle(_translationMap['InterestRateMaint']  + ' - ' + _translationMap['Add']);
							_controller.populateDropdownsRule("init", "", false);
							_controller.setDefaultNewIntRate();


							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['InterestRateMaint']  + ' - ' + _translationMap['Modify']);
							_controller.populateDropdownsRule("init", "", false);
							_controller.populateIntRate();

							break;
						}
						case _controller.DEL:
						{
							this.setTitle(_translationMap['InterestRateMaint']  + ' - ' + _translationMap['Delete']);
							this.disableAllFields();
							_controller.populateIntRate();
							this.get(0).show();
							break;
						}
					}
					this.rateType = this.getField('rateType').getValue();
				}
				, getData: function()
				{
					var data = {};
					data["fundCategory"] = this.getField('fundCategory').getValue();
					data["fundCategoryDesc"] = this.getField('fundCategory').getRawValue();
					data["intCalcMthd"]      = this.getField('intCalcMthd').getValue();
					data["intCalcMthdDesc"]  = this.getField('intCalcMthd').getRawValue();
					data["rateCodeType"]     = this.getField('rateCodeType').getValue();
					data["rateCodeTypeDesc"] = this.getField('rateCodeType').getRawValue();
					data["rateCode"]         = this.getField('rateCode').getValue();
					data["rateCodeDesc"]     = this.getField('rateCode').getRawValue();
					data["rateType"]         = this.getField('rateType').getValue();
					data["rateTypeDesc"]     = this.getField('rateType').getRawValue();
					data["deff"]             = this.getField('deff').getDisplayDateString();
					data["intTerm"]          = this.getField('intTerm').getValue();
					data["intTermDesc"]      = this.getField('intTerm').getRawValue();
					data["rate"] =  '';

					//Add || mod

					if (!this.getField('rateInt').disabled ) {
						data["rate"]  = this.getField('rateInt').getValue();

						data["rate"]  = isNaN(parseFloat(data["rate"])) ? 0 : data["rate"];
						data.Scale = {};
						data.RateSplit = {};
						if (	data["rateType"] == "Percent") {
							 data.Scale.interestRateScaleUUID = this.getField('rateInt').uuid;
							 data.Scale.version = this.getField('rateInt').version;
							 data.Scale.rateType = data["rateType"];
							 data.Scale.lower =  _controller.defaultValues['lower'];
							 data.Scale.upper =  _controller.defaultValues['upper'];
							 data.Scale.rate = data["rate"];
						}

						if( !_controller.disableRateSplit && !!_fields['rateEntitySrc'].getStore() ){
							_fields['rateEntitySrc'].getStore().each(function(record) {

								var localField = Ext.getCmp('frmIntRate' +record.data.code);
							 // if (localField.getValue() > 0) {
									var rateSplit = {};
									//data.RateSplitList.RateSplit[localField.code] = {}
									rateSplit.rateSplitUUID = localField.uuid;
									rateSplit.rateEntityType = localField.code;
									rateSplit.rateEntityTypeDesc = localField.fieldLabel;
									rateSplit.rate = isNaN(parseFloat(localField.getValue())) ? 0 : localField.getValue();
									data.RateSplit[localField.code] = rateSplit;
							//  }
							});
						}
					}
					else
						 data.Scale = null;

					return data;
				}
			}
		)

		, frmIntRateScale: new DesktopWeb.AdvancedControls.PopupWindow(
			{
				action: null
				,width: 370
				,rateType : ''
				,closeAction: 'hide'
				,id :'frmIntRateScale'
				,modal: true
				,defaults: {border:false}
				,items: [
					{
						html: _translationMap['DeleteConfirmMsg']
						, style: 'text-align:center'
					}
					, {
						layout: 'form'
						,width: 400
						,style: 'padding:4px'
						,labelWidth: 108
						,items: [
							new DesktopWeb.Controls.NumberField(
								{
									fieldLabel: _translationMap['Lower']
									, itemId  : 'lower'
									, allowBlank: false
									, width: 200
									, maxLength: 50
									, enforceMaxLength : true
									, minValue: 0
									, maxValue :9999999999.99
								}
							)
							, new DesktopWeb.Controls.NumberField(
								{
									fieldLabel: _translationMap['Upper']
									, itemId  : 'upper'
									, allowBlank: false
									, width: 200
									, maxLength: 50
									, enforceMaxLength : true
									, minValue: 0
									, maxValue :9999999999.99
								}
							)
							, new DesktopWeb.Controls.NumberField(
								{
									fieldLabel: _translationMap['Rate']
									, itemId  : 'rateScale'
									, allowBlank: false
									, idth: 200
									, decimalPrecision: 4
									, minValue: 0
									, maxValue :100
								}
							)
						]
					}
					, {
						xtype: 'fieldset'
						,style: 'padding:5px;margin:5px;'
						,id: 'rateSplit'
						,border: true
						,title: _translationMap['RateSplit']
						,items: []
					}
				 ]

				,buttons: [
						new DesktopWeb.Controls.ActionButton(
						{
							text: _translationMap['OK']
							, itemId : 'cmdIntRateScaleSubmit'
							, handler: function(){
								if (_popups['frmIntRateScale'].isValid())
								{
									_controller.doValidate("frmIntRateScale", _popups['frmIntRateScale'].action, _popups['frmIntRateScale'].getData());
								}
							}
						}
					)
					, new DesktopWeb.Controls.ActionButton({
							text: _translationMap['Cancel']
							, itemId : 'cmdIntRateScaleCancel'
							, handler: function(){
									_popups['frmIntRateScale'].hide();
							}
						})
				]
				, init: function(action)
				{
					this.action = action;
					this.get(0).hide();
					this.enableAllFields();

					this.clearAllFields();
					switch(action)
					{
						case _controller.ADD:
						{
							this.setTitle(_translationMap['InterestRate'] + " " + _controller.getRateType() + ' - ' + _translationMap['Add']);
							_controller.setDefaultNewIntRateScale();
							break;
						}
						case _controller.MOD:
						{
							this.setTitle(_translationMap['InterestRate'] + " " + _controller.getRateType() + ' - ' + _translationMap['Modify']);
							_controller.populateIntRateScale();
							break;
						}
						case _controller.DEL:
						{
							this.setTitle(_translationMap['InterestRate'] + " " + _controller.getRateType() + ' - ' + _translationMap['Delete']);
							this.disableAllFields();
							_controller.populateIntRateScale();
							this.get(0).show();
							break;
						}
					}
				}
				, getData: function() {
					var data = {};
					data.Scale = {};
					data.Scale.lower = data["lower"] =  this.getField('lower').getValue();
					data.Scale.upper = data["upper"] =  this.getField('upper').getValue();
					data.Scale.rate = data["rate"]   = this.getField('rateScale').getValue();
					data.Scale.rateType = this.rateType;

					if(!_controller.disableRateSplit && !!_fields['rateEntitySrc'].getStore()) {
						 data.RateSplit = {};
						_fields['rateEntitySrc'].getStore().each(function(record) {
							var rateSplit = {};
							var localField = Ext.getCmp('frmIntRateScale' + record.data.code);
							rateSplit.rateSplitUUID = localField.uuid;
							rateSplit.rateEntityType = localField.code;
							rateSplit.rateEntityTypeDesc = localField.fieldLabel;
							rateSplit.rate = isNaN(parseFloat(localField.getValue())) ? 0 : localField.getValue();
							data.RateSplit[localField.code] = rateSplit;

						});
					}

					return data;
				}
			}
		)

		, frmAdmin: new DesktopWeb.AdvancedControls.PopupWindow({
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
									_fields['userName']
									, _fields['modUser']
								]
							}
							,{
								width: 185
								,layout: 'form'
								,defaults: {width: 80}
								,items: [
									_fields['procDate']
									, _fields['modDate']
								]
							}
						]
					}
				]
				,buttons: [
					new DesktopWeb.Controls.ActionButton({
							text: _translationMap['OK']
							,handler: function(){_popups['frmAdmin'].hide();}
						})
				]
				,init: function(title, data){
					this.setTitle(title);
					_fields['userName'].setValue(data['userName']);
					_fields['procDate'].setValue(data['procDate']);
					_fields['modDate'].setValue(data['modDate']);
					_fields['modUser'].setValue(data['modUser']);
				}
			}
		)
		, frmHistory: new DesktopWeb.AdvancedControls.HistoryPopup()
	}

	// PUBLIC ITEMS
	return {
		layoutWidth: _layoutWidth
		,layoutHeight: _layoutHeight
		,fields: _fields
		,grids: _grids
		,popups: _popups
		,buttons: _buttons
		,layout: new Ext.Container(
			{
				height: _layoutHeight
				,width: _layoutWidth
				,layout: 'form'
				,items: [
					{
						layout: 'column'
						,style: "margin-bottom:10px;"
						,defaults: {labelWidth: 80}
						,items: [
							{
								width: 320
								, layout: 'form'
								, labelWidth: 100
								, items: [
									_fields['fromDate']
									, _fields['fundCategorySrchSc']
									, _fields['rateCodeTypeSrchSc']
								]
							}
							, {
								width: 320
								, layout: 'form'
								, labelWidth: 100
								, items: [
									_fields['toDate']
								]
							}
							, _buttons['cmdSearch']
						]
					}
					,{
						layout: 'form'
						,items: [
							_grids['grdIntRate']
						]
					}
					, {
							layout: 'column',
							id: 'item1',
							border: false,
							defaults: {
								layout: 'form',
								border: false
							},
							items: [
							{columnWidth: 0.5,  items: [_grids['grdIntRateScale'] ]},
							{columnWidth: 0.5,  items: [_grids['grdRateSplit'] ] }

									] // items
						}
				]
			}
		)

		,screenButtons: [
			new DesktopWeb.Controls.ScreenButton({
					text: _translationMap['OK']
					,handler: function(){
						DesktopWeb.Util.commitScreen();
					}
			})
			,new DesktopWeb.Controls.ScreenButton(
				{
					text: _translationMap['Cancel']
					,handler: function(){
						if(_controller.updatesFlag){
							DesktopWeb.Util.displayPrompt(_translationMap['PromptMsg'], handlePromptMsg);
							function handlePromptMsg(btn){
								if(btn == 'ok'){
									DesktopWeb.Util.cancelScreen();
								}
							}
						}else{
							DesktopWeb.Util.cancelScreen();
						}
					}
				}
			)
		]
	}
}