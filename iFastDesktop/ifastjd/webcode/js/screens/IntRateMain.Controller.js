 /*********************************************************************************************
 * @file	IntRateMain.Controller.js
 * @author	Cherdsak Sangkasen
 * @desc	Controller JS file for Interest Rate for Investment screen
 *********************************************************************************************/
 /*
 *  History :
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  14 Jun 2017 Gomoot T. P0263240 CHG0048754 T85926
 *					- Enhance DYN DIF project - Add RateSplit
 *
 *  04 Sep 2017 Gomoot T. P0263240 CHG0048754 DFT0076839 T86200
 *            - When ratesplit is turned on and broker portion > 0,
 *            all scale rate values must be the same.
 *
 *	19 Oct 2017 Matira T. P0263240-59 DFT0078086
 *				- Allow warning popup with cancel button.
 */

DesktopWeb.ScreenController = function(){

	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var _resources = null;
	var _initView = 'dtIntRateMainInit';
	var _reloadView = 'dtIntRateMainReload';
	var _updateView = 'dtIntRateMainUpd';
	var _vldtnRateView =  'dtIntRateMainVldtn';
	var _vldtnScaleView =  'dtIntRateScaleVldtn';
	var _historyView = 'dtHistoricalInfo';
	var _ADDBTN = 'addBtn';
	var _MODBTN = 'modBtn';
	var _DELBTN = 'delBtn';
	var _MOREBTN = 'moreBtn';
	var _ADMINBTN = 'adminBtn';
	var _HISBTN = 'historicalBtn';

	var _popScale = null;
	var _popInte = null;
	var _SEPERATOR	= ';';

	var _defaultValues = {};
	var _blankDocument;
	var _mstrXML = null;
	var _intRateCounter = 0;
	var _intRateScaleCounter = 0;
	var _SPCounter = 0;
	var _originXML;
	var _blank = "";
	var _rateSplitEntity = {};

	var _permissionsMap = {};
	var _listXMLs = {};
	var _listMstrXMLs = {};
	var _ctrlMstrXMLs = {};
	var _myDebug = false;
	var _nextStartRecNum = null;
	var _requestRecNum = 25;
	var SEQ = {};
	var ADD   = 'add' ;
	var MOD   = 'mod' ;
	var DEL   = 'del' ;
	var UNCH  = 'unch';


	// PRIVATE METHODS ****************************************
	function funcInit(res) {
		initResource(res);
		_self = DesktopWeb._SCREEN_CONTROLLER;

		var requestXML = IFDS.Xml.newDocument("data");

		DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{
			if (success) {
				createControlMstrXML(responseXML);
				storePermissions(responseXML);
				storeDefaultValues(responseXML);
				createListMstrXML(responseXML);
				populateDropdowns(responseXML);
				setDefaultSearch();
			}
			initPerm();
		}
	}	//function funcInit

	function initResource(res) {
		_resources = res;
		_popScale = _resources.popups['frmIntRateScale'];
		_popInte = _resources.popups['frmIntRate'];

		SEQ[ADD] = '3';
		SEQ[MOD]= '2';
		SEQ[DEL]= '1';
		SEQ[UNCH]= '0';
	} //function initResource

	function initPerm() {
		if (_permissionsMap['inq'])
			_resources.buttons['cmdSearch'].enable();
		else
			_resources.buttons['cmdSearch'].disable();

		_resources.grids['grdIntRate'].disableAllButtons();
		_resources.grids['grdIntRateScale'].disableAllButtons();
		_resources.grids['grdRateSplit'].disableAllButtons();
		if (_permissionsMap['add'])
			_resources.grids['grdIntRate'].enableButton(_ADDBTN);
	} //function initPerm

	function setDefaultSearch() {
		_resources.fields['fromDate'].setValue(_defaultValues['fromDate']);
		_resources.fields['toDate'].setValue(_defaultValues['toDate']);
		_resources.fields['rateCodeTypeSrchSc'].setValue(_defaultValues['rateCodeTypeSrchSc']);
		_resources.fields['fundCategorySrchSc'].setValue(_defaultValues['fundCategorySrchSc']);
	} // function setDefaultSearch

	function createListMstrXML(xml)	{
		var listMstrXMLArr = IFDS.Xml.getNodes(xml, "//List");
		Ext.each(listMstrXMLArr, function(listMstrXML){
			controlName = listMstrXML.getAttribute('listName');
			_listMstrXMLs[controlName] = listMstrXML;
		});
	} //function createListMstrXML

	function createControlMstrXML(xml) {
		var ctrlXMLArr = IFDS.Xml.getNodes(xml, "//Control");
		Ext.each(ctrlXMLArr, function(ctrlXML){
			_ctrlMstrXMLs[ctrlXML.getAttribute('controlName')] = ctrlXML;
		});
	}	//function createControlMstrXML

	function storePermissions(xml) 	{
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(xml, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(xml, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(xml, '//Permissions/modPerm').toLowerCase() == 'yes';
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(xml, '//Permissions/delPerm').toLowerCase() == 'yes';
	} //function storePermissions

	function populateDropdowns(xml)	{

		_resources.fields['fundCategorySrchSc'].getStore().loadData(_listMstrXMLs["FundCategorySrchSc"]);
		_resources.fields['rateCodeTypeSrchSc'].getStore().loadData(_listMstrXMLs["RateCodeTypeSrchSc"]);
		_popInte.getField('fundCategory').getStore().loadData(_listMstrXMLs["FundCategory"]);

		_popInte.getField('intCalcMthd').getStore().loadData(_listMstrXMLs["IntCalcMthd"]);
		_popInte.getField('rateCodeType').getStore().loadData(_listMstrXMLs["RateCodeType"]);
		_popInte.getField('rateCode').getStore().loadData(_listMstrXMLs["RateCode"]);
		_popInte.getField('rateType').getStore().loadData(_listMstrXMLs["RateType"]);
		_popInte.getField('intTerm').getStore().loadData(_listMstrXMLs["IntTerm"]);
		if (!!_listMstrXMLs["RateSplitList"])
			_resources.fields['rateEntitySrc'].getStore().loadData(_listMstrXMLs["RateSplitList"]);


		_popScale.getField('lower').maxValue = _defaultValues['upper'];
		_popScale.getField('upper').maxValue = _defaultValues['upper'];
		

		createRateSplitControl();

	}	//function populateDropdowns

	function createRateSplitControl() {

		if (_defaultValues['enableRateSplit'] && !!_resources.fields['rateEntitySrc'].getStore()) {

			_resources.fields['rateEntitySrc'].getStore().each(function(record) {
				_rateSplitEntity[record.data.code] = record.data.value;
				_popScale.get('rateSplit').add(
							new DesktopWeb.Controls.NumberField({
								fieldLabel: record.data.value
								, width: 200
								,id : 'frmIntRateScale' + record.data.code
								,code :record.data.code
								,uuid :''
								,decimalPrecision: 4
								,minValue : 0
								,maxValue : 100
							}));

				 _popInte.get('mainform').get('mainColumn').get('col2').get('rateSplitPercent').add(
							new DesktopWeb.Controls.NumberField({
								fieldLabel: record.data.value
								, id : 'frmIntRate'+record.data.code
								, width: 150
								, code :record.data.code
								, uuid :''
								, decimalPrecision: 4
								, minValue : 0
								, maxValue : 100
							})); //add
					_popInte.get('mainform').get('mainColumn').get('col2').get('rateSplitPercent').hide();
			});
		}// if (_defaultValues['enableRateSplit']    && !!_resources.fields['rateEntitySrc'].getStore())
		else {
			_self.disableRateSplit = true;

			 _resources.grids['grdRateSplit'].hide();
			 _resources.layout.items.itemAt(2).items.itemAt(0).columnWidth = 1.0;
			 _resources.layout.items.itemAt(2).doLayout();

			 _popInte.get('mainform').get('mainColumn').get('col2').get('rateSplitPercent').hide();
			 _popScale.get('rateSplit').hide();
			 _popScale.get('rateSplit').setTitle('');
		}
	} //function createRateSplitControl()

	function isPopulatedByControl(controlName, code)
	{
		var retVal = false;
		if (!!_ctrlMstrXMLs[controlName]) {
			var elmXMLArr = IFDS.Xml.getNodes(_ctrlMstrXMLs[controlName], "Codes/code");
			Ext.each(elmXMLArr, function(elmXML){
				if (code == IFDS.Xml.getNodeValue(elmXML, "."))
					retVal = true;
			});
		} //if (!!_ctrlMstrXMLs[controlName])
		return retVal;
	} //function isPopulatedByControl

	function funcPopulateDropdownsRule(fieldName, code, recursive)
	{
		var controlName;

		switch (fieldName)
		{
			case "init":
			{
				_popInte.getField('intCalcMthd').getStore().filterBy( function fn(record){ return false; } );
				_popInte.getField('rateCodeType').getStore().filterBy( function fn(record){ return false; } );
				_popInte.getField('rateCode').getStore().filterBy( function fn(record){ return false; } );
				_popInte.getField('rateType').getStore().filterBy( function fn(record){ return false; } );
				_popInte.getField('intTerm').getStore().filterBy( function fn(record){ return false; } );
				_popInte.getField("intTerm").disable();

				break;
			}
			case "fundCategory":
			{
				_popInte.getField('intCalcMthd').clearValue();
				_popInte.getField('rateCodeType').clearValue();
				_popInte.getField('rateCode').clearValue();
				_popInte.getField('rateType').clearValue();
				_popInte.getField('intTerm').clearValue();

				_popInte.getField('intCalcMthd').clearInvalid();
				_popInte.getField('rateCodeType').clearInvalid();
				_popInte.getField('rateCode').clearInvalid();
				_popInte.getField('rateType').clearInvalid();
				_popInte.getField('intTerm').clearInvalid();


				_popInte.getField('intCalcMthd').getStore().filterBy(
					function fn(record){
						controlName = "IntCalcMthd-" + code;
						return isPopulatedByControl(controlName, record.get('code'));
					}
				);

				_popInte.getField('rateCodeType').getStore().filterBy(
					function fn(record){
						controlName = "RateCodeType-" + code;
						return isPopulatedByControl(controlName, record.get('code'));
					}
				);

				_popInte.getField('rateCode').getStore().filterBy( function fn(record){	return false; } );
				_popInte.getField('rateType').getStore().filterBy( function fn(record){	return false; } );
				_popInte.getField('intTerm').getStore().filterBy( function fn(record){	return false; } );
				_popInte.getField('intTerm').disable();
				funcPopulateDropdownsRule("rateType", '',  false);

				break;
			}
			case "rateCodeType":
			{
				_popInte.getField('rateCode').clearValue();
				_popInte.getField('rateType').clearValue();
				_popInte.getField('intTerm').clearValue();

				_popInte.getField('rateCode').clearInvalid();
				_popInte.getField('rateType').clearInvalid();
				_popInte.getField('intTerm').clearInvalid();

				_popInte.getField('rateCode').getStore().filterBy(
					function fn(record){
						controlName = "RateCode-" + _popInte.getField('fundCategory').getValue() + code;
						return isPopulatedByControl(controlName, record.get('code'));
					}
				);

				_popInte.getField('rateType').getStore().filterBy( function fn(record){	return false; } );
				_popInte.getField('intTerm').getStore().filterBy( function fn(record){	return false; } );
				_popInte.getField('intTerm').disable();
				funcPopulateDropdownsRule("rateType", '',  false);
				break;
			}
			case "rateCode":
			{
				_popInte.getField('rateType').clearValue();
				_popInte.getField('rateType').clearInvalid();
				funcPopulateDropdownsRule("rateType", '',  false);
				_popInte.getField('rateType').getStore().filterBy(

					function fn(record){
						controlName = "RateType-" + code;
						return isPopulatedByControl(controlName, record.get('code'));
					}
				);
				if (_popInte.getField('intCalcMthd').getValue() != "")
				{
					funcPopulateDropdownsRule("intCalcMthd", _popInte.getField('intCalcMthd').getValue(), true);
				}
				break;
			}
			case "rateType":
			{
				_popInte.get('mainform').get('mainColumn').get('col2').get('rateSplitPercent').hide();
				if (code == 'Percent') {
						_popInte.getField('rateInt').enable();
						_popInte.getField('rateInt').setValue(0);
						if (!_self.disableRateSplit) {
							_popInte.get('mainform').get('mainColumn').get('col2').get('rateSplitPercent').show();
							resetRateSplitPopup('frmIntRate');
						}
				} else {
						_popInte.getField('rateInt').setDefault();
						_popInte.getField('rateInt').disable();

				}
			}
			case "intCalcMthd":
			{
				_popInte.getField('intTerm').clearValue();
				if (_popInte.getField('rateCode').getValue() != "TrmBase")
				{
					_popInte.getField('intTerm').getStore().filterBy( function fn(record){	return false; } );
					if (!recursive)
					{
						_popInte.getField('intTerm').disable();
					}
				}
				else
				{
					if (code == "S")
					{
						_popInte.getField('intTerm').getStore().filterBy( function fn(record){	return true; } );
					}
					else
					{
						_popInte.getField('intTerm').getStore().filterBy(
							function fn(record){
								controlName = "IntTerm-B";
								return isPopulatedByControl(controlName, record.get('code'));
							}
						);
					}
					_popInte.getField('intTerm').enable();
				}
				break;
			}
		}
	} //function funcPopulateDropdownsRule

	function storeDefaultValues(xml) {
		_defaultValues['fundCategorySrchSc'] = IFDS.Xml.getNodeValue(xml, "//ListSelection[@id='FundCategorySrchSc']");
		_defaultValues['rateCodeTypeSrchSc'] = IFDS.Xml.getNodeValue(xml, "//ListSelection[@id='RateCodeTypeSrchSc']");
		_defaultValues['fromDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DefaultValues/fromDate'));
		_defaultValues['toDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DefaultValues/toDate'));
		_defaultValues['deff'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DefaultValues/deff'));
		_defaultValues['deffDateObj'] =  DesktopWeb.Util.stringToDate(_defaultValues['deff'],DesktopWeb.Util.getDateDisplayFormat());
		_defaultValues['enableRateSplit'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/enableRateSplit').toLowerCase() == 'yes';
		_defaultValues['lower'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/lower');
		_defaultValues['upper'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/upper');
		_defaultValues['interestRateVerify'] = IFDS.Xml.getNodeValue(xml, '//InterestRateVerify');

		_defaultValues['intCalcMthd'] = "";
		_defaultValues['rateCodeType'] = "";
		_defaultValues['rateCode'] = "";
		_defaultValues['rateType'] = "";
		_defaultValues['intTerm'] = "";
		_defaultValues['rateInt'] = "";
		_defaultValues['rateScale'] = "";
	} //function storeDefaultValues


	function funcSearch(more)	{
		var requestXML = IFDS.Xml.newDocument("data");

		IFDS.Xml.addSingleNode(requestXML, "fundCategory", _resources.fields['fundCategorySrchSc'].getValue());
		IFDS.Xml.addSingleNode(requestXML, "rateCodeType", _resources.fields['rateCodeTypeSrchSc'].getValue());
		IFDS.Xml.addSingleNode(requestXML, "fromDate", _resources.fields['fromDate'].getSMVDateString());
		IFDS.Xml.addSingleNode(requestXML, "toDate", _resources.fields['toDate'].getSMVDateString());
		IFDS.Xml.addSingleNode(requestXML, "startRecNum", (more ? _nextStartRecNum : 1));
		IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);

		if (requestXML)
		{
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['ProcMsg_Searching']);

			function responseHandler(success, responseXML)
			{
				if (success)
				{
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					_resources.grids['grdIntRate'].getStore().loadData(responseXML,more);
					_resources.grids['grdIntRate'].getOrigStore().loadData(responseXML, more);
					_resources.grids['grdIntRate'].setSelectedRecord(0);

					if (_nextStartRecNum)
						_resources.grids['grdIntRate'].enableButton(_MOREBTN);
					else
						_resources.grids['grdIntRate'].disableButton(_MOREBTN);
				}
				else {
					
					_resources.grids['grdRateSplit'].clearData();
					_resources.grids['grdIntRateScale'].clearData();
					_resources.grids['grdIntRate'].clearData();
					initPerm();
				}
					
			}
		}
	} //function funcSearch

	function enablePermButtons()
	{
		var intRate = getSelectedIntRate();

		if (!!intRate)
		{

			if (intRate.runMode === ADD )
			{
				_resources.grids['grdIntRate'].enableButton(_MODBTN); //mod
				_resources.grids['grdIntRate'].enableButton(_DELBTN); //delete
				_resources.grids['grdIntRate'].disableButton(_ADMINBTN); //admin
				_resources.grids['grdIntRate'].disableButton(_HISBTN); //dhitory
			}
			else
			{
				var recDate = DesktopWeb.Util.stringToDate(intRate.deff,DesktopWeb.Util.getDateDisplayFormat());

				if (_permissionsMap['mod'] &&
					recDate >= _defaultValues['deffDateObj'] &&
					_defaultValues['interestRateVerify'] == 1)
						_resources.grids['grdIntRate'].enableButton(_MODBTN);
				else
					_resources.grids['grdIntRate'].disableButton(_MODBTN);

				_resources.grids['grdIntRate'].disableButton(_DELBTN);
				_resources.grids['grdIntRate'].enableButton(_ADMINBTN);
				_resources.grids['grdIntRate'].enableButton(_HISBTN);
			}

			if (intRate.rateType.toLowerCase() != "percent")
			{
				if (_permissionsMap['add'])
					_resources.grids['grdIntRateScale'].enableButton(_ADDBTN);
				else
					_resources.grids['grdIntRateScale'].disableButton(_ADDBTN);

				var intRateScale =  getSelectedIntRateScale();
				if (!!intRateScale)
				{
					if (intRateScale.runMode === ADD)
					{
						_resources.grids['grdIntRateScale'].enableButton(_MODBTN);
						_resources.grids['grdIntRateScale'].enableButton(_DELBTN);
						_resources.grids['grdIntRateScale'].disableButton(_ADMINBTN);
						_resources.grids['grdIntRateScale'].disableButton(_HISBTN);
					}
					else
					{
						if (_permissionsMap['mod'])
							_resources.grids['grdIntRateScale'].enableButton(_MODBTN);
						else
							_resources.grids['grdIntRateScale'].disableButton(_MODBTN);

						if (_permissionsMap['del'])
							_resources.grids['grdIntRateScale'].enableButton(_DELBTN);
						else
							_resources.grids['grdIntRateScale'].disableButton(_DELBTN);

						_resources.grids['grdIntRateScale'].enableButton(_HISBTN);
						_resources.grids['grdIntRateScale'].enableButton(_ADMINBTN);
					}
				} //if (!!intRateScale)
			}

			var rateSplitRecord =  _resources.grids['grdRateSplit'].getSelectedRecord();
			if (!!rateSplitRecord) {
				if (rateSplitRecord.data.runMode === ADD)
					_resources.grids['grdRateSplit'].disableAllButtons();
				else
					_resources.grids['grdRateSplit'].enableAllButtons();;

			}
		} //if (selectedRecord.data.rateType == "Scale")
		else {
				_resources.grids['grdIntRate'].disableAllButtons();
				_resources.grids['grdIntRateScale'].disableAllButtons();
				_resources.grids['grdRateSplit'].disableAllButtons();
				if (_permissionsMap['add'])
					_resources.grids['grdIntRate'].enableButton(_ADDBTN);
		}
	}

	function getSelectedIntRate() {

		if (!!_resources.grids['grdIntRate'].getSelectedRecord())
			return _resources.grids['grdIntRate'].getSelectedRecord().data;
		else
			return null;
	} //function getSelectedIntRate

	function getSelectedIntRateScale()
	{
		if (!!_resources.grids['grdIntRateScale'].getSelectedRecord())
			return _resources.grids['grdIntRateScale'].getSelectedRecord().data;
		else
			return null;
	}	//function getSelectedIntRateScale

	function setSelectedIntRate(record)
	{
		if (record == null || record === undefined)
			record = _resources.grids['grdIntRate'].getSelectedRecord();

		if (!!record && !!record.data.ScalesNode) {
			_resources.grids['grdIntRateScale'].clearData();
			_resources.grids['grdIntRateScale'].getStore().loadData(record.data.ScalesNode);
			_resources.grids['grdIntRateScale'].selectFirstRecord(); // Will populate rate split via rowselect

			if (record.data.rateType === 'Percent') { //setSelectedIntRate
				 if (_resources.grids['grdIntRateScale'].getStore().snapshot &&
					_resources.grids['grdIntRateScale'].getStore().snapshot.items.length > 0)
					setSelectedIntRateScale(_resources.grids['grdIntRateScale'].getStore().snapshot.items[0]);
			}
			else
				enablePermButtons();
		}
		else {
			_resources.grids['grdRateSplit'].clearData();
			_resources.grids['grdIntRateScale'].clearData();
			enablePermButtons();
		}
	} //function setSelectedIntRate

	function setSelectedIntRateScale(record)
	{
		if (!!record == null)
			record = _resources.grids['grdIntRateScale'].getSelectedRecord();

		_resources.grids['grdRateSplit'].clearData();
		if (!!record && !!record.data.RateSplitNode) {
			_resources.grids['grdRateSplit'].getStore().loadData(record.data.RateSplitNode);
			_resources.grids['grdRateSplit'].selectFirstRecord();
		}
		enablePermButtons();
	} //function setSelectedIntRateScale

	function genXMLString(gridName,parentTag, parentListTag)
	{
		var xml = '';
		var recordList = null;
		if (_resources.grids[gridName].getStore().snapshot)
			recordList = _resources.grids[gridName].getStore().snapshot.items;
		else
			recordList = _resources.grids[gridName].getStore().data.items;

		for(var i = 0; i <= recordList.length-1; i++){
			xml += "<"+ parentTag +">";
			for (var name in recordList[i].data){
				if (name == 'RateSplitNode') {
					if (!!recordList[i].data[name])
						xml += IFDS.Xml.serialize(recordList[i].data[name]);
				}
				else
				xml += "<" + name + ">"
				    + recordList[i].data[name]
				    + "</" + name + ">";
			}
			xml += "</" + parentTag +">";
		}

		if (xml.length > 0)
			xml = "<"+parentListTag+">" + xml +"</"+parentListTag+">";

		return xml;
	} //function genXMLString

	function initRateSplit (popupName) {
		if (!_self.disableRateSplit) {
			_resources.fields['rateEntitySrc'].getStore().each(function(record) {
				 var localField = Ext.getCmp(popupName +record.data.code);
				 localField.uuid = '';//record.data.rateSplitUUID;
				 localField.code = record.data.code;
				 localField.fieldLabel = record.data.value;
				 localField.setValue(_defaultValues['rateInt']);
				 if (_resources.popups[popupName].action == DEL)
					 localField.disableField();
				 else
					 localField.enableField();
			});//each
		}
	} //function initRateSplit


	function setDefaultNewIntRate() {
		var fields = _popInte.findBy(function (cmp){
			return (cmp.itemId != null && cmp.itemId.length != 0);
		});
		for (var i = 0; i < fields.length; i++){
			if (fields[i].rendered)
				fields[i].setValue('');

			fields[i].clearInvalid()
		}

		_popInte.getField('rateInt').setDefault();
		_popInte.getField('rateInt').setValue(_defaultValues['rateInt']);

		_popInte.getField('deff').setValue(_defaultValues['deff']);
		initRateSplit('frmIntRate');

	} //function setDefaultNewIntRate

	function setDefaultNewIntRateScale()
	{
		var fields = _popScale.findBy(function (cmp){
			return (cmp.itemId != null && cmp.itemId.length != 0);
		});

		for (var i = 0; i < fields.length; i++) {
			if (fields[i].rendered)
				fields[i].setValue('');

			fields[i].clearInvalid()
		}

		initRateSplit('frmIntRateScale');
	} //setDefaultNewIntRateScale

	function funcPopulateIntRate()
	{
		var obj = getSelectedIntRate();
		if (obj)
		{
			funcPopulateDropdownsRule("fundCategory", obj.fundCategory, false);
			_popInte.getField('fundCategory').setValue(obj.fundCategory);

			funcPopulateDropdownsRule("intCalcMthd", obj.intCalcMthd, false);
			_popInte.getField('intCalcMthd').setValue(obj.intCalcMthd);

		 	funcPopulateDropdownsRule("rateCodeType", obj.rateCodeType, false);
			_popInte.getField('rateCodeType').setValue(obj.rateCodeType);

			funcPopulateDropdownsRule("rateCode", obj.rateCode, false);
			_popInte.getField('rateCode').setValue(obj.rateCode);

			funcPopulateDropdownsRule("rateType", obj.rateType, false);
			_popInte.getField('rateType').setValue(obj.rateType);
			_popInte.getField('deff').setValue(obj.deff);

			if ( !_popInte.getField('intTerm').disabled)
				_popInte.getField('intTerm').setValue(obj.intTerm);

			if (!!obj && !_popInte.getField('rateType').disabled) {
				_popInte.getField('rateInt').setValue(obj.rate);
				_popInte.getField('rateInt').uuid = obj.interestRateScaleUUID;
				_popInte.getField('rateInt').version = obj.scaleversion;
			}

			initRateSplit('frmIntRate');
			if (obj.rateType == 'Percent')
				populateRateSplitPopup('frmIntRate');

		} //obj
	} //function funcPopulateIntRate

	function funcPopulateIntRateScale()	{
		_popScale.rateType = getSelectedIntRate().rateType;
		var obj = getSelectedIntRateScale();
		if (obj) {

			_popScale.getField('lower').setValue(obj.lower);
			_popScale.getField('upper').setValue(obj.upper);
			_popScale.getField('rateScale').setValue(obj.rate);
			initRateSplit('frmIntRateScale');

			populateRateSplitPopup('frmIntRateScale');
		}
	} //function funcPopulateIntRateScale

	function populateRateSplitPopup(popupName) {
		if (!_self.disableRateSplit
			&& _resources.popups[popupName].action != ADD
			&& _resources.grids['grdRateSplit'].getStore().getCount() > 0) {

			_resources.grids['grdRateSplit'].getStore().each(function(record) {
				 var localField = Ext.getCmp(popupName + record.data.rateEntityType);
				 if (!!localField) {
					 localField.uuid = record.data.rateSplitUUID;
					 localField.code = record.data.rateEntityType;
					 localField.fieldLabel = record.data.rateEntityTypeDesc;
					 localField.setValue(record.data.rate);
				}});
		}
	} //function populateRateSplitPopup

	function resetRateSplitPopup(popupName) {
		if (!_self.disableRateSplit) {
			_resources.fields['rateEntitySrc'].getStore().each(function(record) {
				 var localField = Ext.getCmp(popupName +record.data.code);
				 localField.setValue(0);
				});//each
		}
	}  //function resetRateSplitPopup

	function getRunMode(gridName, action) {
		 var record = _resources.grids[gridName].getSelectedRecord();
		 if (action === ADD || (!!record && record.data.runMode === ADD))
			 return ADD;
		 else
			 return action;
	} //function getRunMode

	function getValIntRateRequest(data) {
		var requestXML = IFDS.Xml.newDocument("data");
		var xml = IFDS.Xml.addSingleNode(requestXML, "InterestRate");
		var popupAction = data['runMode'];

		var tempAction = getRunMode('grdIntRate', data['runMode']);
		var preRateType = "";
		var currentRecord = getSelectedIntRate();

		if (tempAction  == ADD)
		{
			IFDS.Xml.addSingleNode(xml, "verified");
			IFDS.Xml.addSingleNode(xml, "version");

			if (data['runMode'] == tempAction) {
				data['interestRateUUID'] = "NEWINTRATE" + ++_intRateCounter;
			}
			else if (!!currentRecord){
				data['interestRateUUID'] = currentRecord.interestRateUUID;
			}

			data['verified'] = "no";
			data['version'] = 0;
		}
		else {

			IFDS.Xml.addSingleNode(xml, "verified", currentRecord.verified);
			IFDS.Xml.addSingleNode(xml, "version", currentRecord.version);
			data['interestRateUUID'] = currentRecord.interestRateUUID;
			preRateType = currentRecord.rateType;
		}
		data['runMode'] = tempAction;
		IFDS.Xml.addSingleNode(xml, "runMode",tempAction);
		IFDS.Xml.addSingleNode(xml, "interestRateUUID", data['interestRateUUID']);
		IFDS.Xml.addSingleNode(xml, "fundCategory", data['fundCategory']);
		IFDS.Xml.addSingleNode(xml, "intCalcMthd", data['intCalcMthd']);
		IFDS.Xml.addSingleNode(xml, "rateCode", data['rateCode']);
		IFDS.Xml.addSingleNode(xml, "rateCodeType", data['rateCodeType']);
		IFDS.Xml.addSingleNode(xml, "rateType", data['rateType']);
		IFDS.Xml.addSingleNode(xml, "deff", DesktopWeb.Util.getSMVDateValue(data['deff']));
		IFDS.Xml.addSingleNode(xml, "intTerm", data['intTerm']);

		if (!!data.Scale) //Percent Type
			generateScale(xml, popupAction, data);
		return requestXML ;
	} //function getValIntRateRequest

	function generateScale(parentNode, popupAction, data, uuid) {

		var xml = IFDS.Xml.newDocument("Scale");
		var cloneScale = IFDS.Xml.newDocument("Scale");
		var tempAction = popupAction;

		var intRateRecord = getSelectedIntRate();
		if (tempAction === ADD)	{
			data.Scale.interestRateScaleUUID = "NEWINTRATESCALE" + ++_intRateScaleCounter;
			data.Scale.version = 0;
			data.Scale.runMode =  ADD;
		}
		else {
			if (!!intRateRecord && intRateRecord.runMode == ADD
				|| (!!data.rateType && intRateRecord.rateType !== data.rateType))
				data.Scale.runMode =  ADD;
			else
				data.Scale.runMode = tempAction;

			var scaleRecord = getSelectedIntRateScale();
			if (!!scaleRecord && scaleRecord.rateType == data.Scale.rateType) {
				data.Scale.version = scaleRecord.version;
				data.Scale.interestRateScaleUUID = scaleRecord.interestRateScaleUUID;
				data.Scale.userName = scaleRecord.userName;
				data.Scale.prodDate = scaleRecord.prodDate;
				data.Scale.modUser = scaleRecord.modUser;
				data.Scale.modDate = scaleRecord.modDate;
			}
			else if (_resources.grids['grdIntRateScale'].getStore().snapshot.items.length > 0
			&& _resources.grids['grdIntRateScale'].getStore().snapshot.items[0].data.rateType == data.Scale.rateType ){ //generateScale
				//There is no scale record in table.
				//Percent update
				var record = _resources.grids['grdIntRateScale'].getStore().snapshot.items[0].data;
				data.Scale.version =  record.version;
				data.Scale.interestRateScaleUUID = record.interestRateScaleUUID;
				data.Scale.userName = record.userName;
				data.Scale.prodDate = record.prodDate;
				data.Scale.modUser = record.modUser;
				data.Scale.modDate = record.modDate;
			}
			else {
			 //New Scale record but mode not set as add
			 data.Scale.interestRateScaleUUID = "NEWINTRATESCALE" + ++_intRateScaleCounter;
			 data.Scale.version = 0;
			 data.Scale.runMode =  ADD;
			}
		} //else

		IFDS.Xml.addSingleNode(xml, "rateType", data.Scale.rateType);
		IFDS.Xml.addSingleNode(xml, "runMode", data.Scale.runMode);
		IFDS.Xml.addSingleNode(xml, "version", data.Scale.version);
		IFDS.Xml.addSingleNode(xml, "interestRateScaleUUID", data.Scale.interestRateScaleUUID);
		IFDS.Xml.addSingleNode(xml, "lower", data.Scale.lower);
		IFDS.Xml.addSingleNode(xml, "upper", data.Scale.upper);
		IFDS.Xml.addSingleNode(xml, "rate", data.Scale.rate);
		for (var name in data.Scale) {
			//prepare data to apply to grid
			IFDS.Xml.addSingleNode(cloneScale, name,  data.Scale[name]);
		}

		var rateSplitListXml = IFDS.Xml.newDocument("RateSplitList");
		generateRateSplit(rateSplitListXml, tempAction, data);
		IFDS.Xml.appendNode(xml, rateSplitListXml);

		IFDS.Xml.appendNode(cloneScale, IFDS.Xml.stringToXML(IFDS.Xml.serialize(data.Scale.RateSplitNode)));
		//Data to apply to grid
		data.ScalesNode = IFDS.Xml.stringToXML( "<Scales>"+ IFDS.Xml.serialize(cloneScale) + "</Scales>" );

		IFDS.Xml.appendNode(parentNode, xml);


	} //generateScale

	function generateRateSplit(parentNode, tempAction, data) {

		var cloneParent = IFDS.Xml.cloneDocument(parentNode);
		for (var code in data.RateSplit ) {

			var rateSplit = data.RateSplit[code];
			rateSplit.interestRateScaleUUID = data.Scale.interestRateScaleUUID;

				//Add mode
			if ("" ==  rateSplit.rateSplitUUID || rateSplit.rateSplitUUID.length == 0) //null == nodes || nodes.length === 0)
			{
				rateSplit['rateSplitUUID'] = "NEWSP" + ++_SPCounter;
				rateSplit['version'] = 0;
				rateSplit['runMode'] =  ADD;
			}
			else {
				var tempRecord =  getSelectedIntRate();
				var obj = null;
				if (!!tempRecord)
					obj = tempRecord.ScalesNode;

					var nodes = !!obj ?IFDS.Xml.getNodes(obj, "/*//RateSplit[rateSplitUUID = '" + rateSplit.rateSplitUUID + "']") : null;
					var tempRate = 0;
					var splitMode = "";
					for (var iCount = 0; iCount < nodes.length; iCount++)
					{
						rateSplit.version = IFDS.Xml.getNodeValue(nodes[iCount],'version');
						rateSplit.procDate = IFDS.Xml.getNodeValue(nodes[iCount],'procDate');
						rateSplit.userName = IFDS.Xml.getNodeValue(nodes[iCount],'userName');
						rateSplit.modDate = IFDS.Xml.getNodeValue(nodes[iCount],'modDate');
						rateSplit.modUser = IFDS.Xml.getNodeValue(nodes[iCount],'modUser');
						tempRate = IFDS.Xml.getNodeValue(nodes[iCount],'rate');
						splitMode = IFDS.Xml.getNodeValue(nodes[iCount],'runMode');
						rateSplit['runMode'] = (!!splitMode && splitMode == ADD) ?  ADD : tempAction;
					}
			}

			var xml = IFDS.Xml.addSingleNode(parentNode, "RateSplit");
			IFDS.Xml.addSingleNode(xml, "interestRateScaleUUID",data.Scale.interestRateScaleUUID);
			IFDS.Xml.addSingleNode(xml, "runMode", rateSplit.runMode);
			IFDS.Xml.addSingleNode(xml, "rate",rateSplit.rate);
			IFDS.Xml.addSingleNode(xml, "version", rateSplit.version);
			IFDS.Xml.addSingleNode(xml, "rateSplitUUID", rateSplit.rateSplitUUID);
			IFDS.Xml.addSingleNode(xml, "rateEntityType", rateSplit.rateEntityType);


			var xmlClone = IFDS.Xml.addSingleNode(cloneParent,  "RateSplit");
			IFDS.Xml.addSingleNode(xmlClone, "interestRateScaleUUID",data.Scale.interestRateScaleUUID);
			for (var name in rateSplit) {
				IFDS.Xml.addSingleNode(xmlClone, name, rateSplit[name]);
			}
		}
		//Data apply to grid
		data.Scale.RateSplitNode = IFDS.Xml.stringToXML(IFDS.Xml.serialize(cloneParent));

	 return parentNode;
	} // function generateRateSplit


	function getValIntRateScaleRequest(action, data)
	{
		var parentNode = IFDS.Xml.newDocument("data");

		generateScale(parentNode, getRunMode('grdIntRateScale', action), data);
		return parentNode;
	} //function getValIntRateScaleRequest

	function funcDoValidate (popupName, action, data) //Called from popup
	{
		if (popupName === "frmIntRate" )
			doValidateIntRate(action, data);
		else
			doValidateIntRateScale(action, data);
	}	// function funcDoValidate

	function doValidateIntRate(action, data) {
		if (action == DEL && getSelectedIntRate().runMode ==  ADD) {
			var index = _resources.grids['grdIntRate'].getSelectionModel().last;
			_resources.grids['grdIntRate'].removeSelectedRecord();

			if (_resources.grids['grdIntRate'].getStore().getCount() >= index - 1 )
				_resources.grids['grdIntRate'].setSelectedRecord(index - 1 );
		 _popInte.hide();
		}
		else {
			data['runMode'] = action;

			DesktopWeb.Ajax.doSmartviewAjax(_vldtnRateView, null,
				getValIntRateRequest(data),
				responseHandler, _translationMap['Validating'], Ext.Msg.OKCANCEL);
		
			function responseHandler(success, responseXML, contextErrors, warnings, btn) {
				if (success) {
					if (btn == null || btn == 'ok') {
						saveUpdateToMstrXML('frmIntRate', action, data);
					}
				}
				else {
					var contextErrors = IFDS.Xml.getNodes(responseXML, '//Errors/Error');
					Ext.each(contextErrors, function(contextError){
						var errorCode = IFDS.Xml.getNodeValue(contextError, 'errorCode');
						var errorText = IFDS.Xml.getNodeValue(contextError, 'text');
						var severity = IFDS.Xml.getNodeValue(contextError, 'errorSeverity');
						switch (errorCode) {
							case '1053': {
								if (_popInte.getField('rateType').isValid()) { _popInte.getField('rateType').markInvalid(errorText); }
								break;
							}
							case '977':
							{
								if (_popInte.getField('rateType').isValid()) { _popInte.getField('rateType').markInvalid(errorText); }
								break;
							}
							 case '1749' :  {
								_resources.fields['rateEntitySrc'].getStore().each(function(record) {
									var localField = Ext.getCmp('frmIntRate' +record.data.code);
									localField.isValid() ? localField.markInvalid(errorText) : '';
								});
								break;
							}
							case '1750' : {
								if (severity.toLowerCase() == 'error') {
									if (_popInte.getField('rateInt').isValid() && _popInte.getField('rateInt').getValue() == 0) {
										_popInte.getField('rateInt').markInvalid(errorText);
									}
									var localField = Ext.getCmp('frmIntRate' + '01');
									localField.isValid() ? localField.markInvalid(errorText) : '';
								}
								break;
							}
						}	// switch (errorCode)
					});
				}
			} //function
		} //else

	} // function doValidateIntRate

	function doValidateIntRateScale(action, data) {

		if (action == DEL && getSelectedIntRateScale().runMode ==  ADD) {
			var rec = _resources.grids['grdIntRate'].getSelectedRecord();
			var index = _resources.grids['grdIntRate'].getRecordIndex(rec);
			var indexScale = _resources.grids['grdIntRateScale'].getSelectionModel().last;
			_resources.grids['grdIntRateScale'].removeSelectedRecord();
			var xmlString =  genXMLString('grdIntRateScale', 'Scale', 'Scales');
			//prompt("Scale", xmlString);
			rec.data['ScalesNode'] =  !!xmlString ? IFDS.Xml.stringToXML(xmlString) : null;
			rec.commit();

			_resources.grids['grdIntRate'].setSelectedRecord(index);

			if (_resources.grids['grdIntRateScale'].getStore().getCount() >= indexScale - 1 )
				_resources.grids['grdIntRateScale'].setSelectedRecord(indexScale - 1 );

			_popScale.hide();
		}
		else  {

			DesktopWeb.Ajax.doSmartviewAjax(_vldtnScaleView, null,
					getValIntRateScaleRequest(action, data), responseHandler, _translationMap['Validating']);

			function responseHandler(success, responseXML)
			{
				if (success) {
					saveUpdateToMstrXML('frmIntRateScale', action, data);
				}
				else {
					var contextErrors = IFDS.Xml.getNodes(responseXML, '//Errors/Error');

					Ext.each(contextErrors, function(contextError){
						var errorCode = IFDS.Xml.getNodeValue(contextError, 'errorCode');
						var errorText = IFDS.Xml.getNodeValue(contextError, 'text');
						var severity = IFDS.Xml.getNodeValue(contextError, 'errorSeverity');
						switch (errorCode)
						{
							case '1049':{
								if (_popScale.getField('rateScale').isValid()) _popScale.getField('rateScale').markInvalid(errorText);
								break;
							}
							case '979':
							case '1052':
							case '1199':{
								if ( _popScale.getField('lower').isValid())  _popScale.getField('lower').markInvalid(errorText);
								if ( _popScale.getField('upper').isValid())  _popScale.getField('upper').markInvalid(errorText);
								break;
							}
							case '1197':{
								if ( _popScale.getField('lower').isValid()) _popScale.getField('lower').markInvalid(errorText);
								break;
							}
							case '1198':{
								if ( _popScale.getField('upper').isValid()) _popScale.getField('upper').markInvalid(errorText);
								break;
							}
							case '1749' :  {
								_resources.fields['rateEntitySrc'].getStore().each(function(record) {
									var localField = Ext.getCmp('frmIntRateScale' +record.data.code);
									localField.isValid() ? localField.markInvalid(errorText) : '';
								});
								break;
							}
							case '1750' : {
								if (severity.toLowerCase() == 'error') {
									var localField = Ext.getCmp('frmIntRateScale' + '01');
									localField.isValid() ? localField.markInvalid(errorText) : '';
								}
								break;
							}

						}	 // switch (errorCode)
					});
				}
			}
		}
	} // FUNCTION doValidateIntRateScale

	function applyToGridIntRate(action, data) {
		_self.updatesFlag = true;
		var index = 0;
		data.errMsg = '';
		if (action == ADD) {
			 _resources.grids['grdIntRate'].addRecord(data);
			 _resources.grids['grdIntRate'].selectLastRecord();

			 _popInte.hide();
		 }
		 else if (action == MOD) {
			 var record = _resources.grids['grdIntRate'].getSelectedRecord();
			 index = _resources.grids['grdIntRate'].getSelectionModel().last ;
			 //_resources.grids['grdIntRate'].getRecordIndex(record);

			 if (record.data.rateType !== data.rateType) {
				 data.rateTypeChange = '1';

				 //Reset Scale table when change rateType
				 if (!!!data.ScalesNode)
					 data.ScalesNode = null;
			 }

			 _resources.grids['grdIntRate'].updateSelectedRecord(data);
			 _resources.grids['grdIntRate'].setSelectedRecord(index);

			 _popInte.hide();
		 }
		 else if (action == DEL) {
			 _resources.grids['grdIntRate'].updateSelectedRecord(data);
			 _resources.grids['grdIntRate'].selectFirstRecord();
			 index = 0;

			 _popInte.hide();
		 }
	}

	function applyToGridScale(action, data) {
		_self.updatesFlag = true;
		var rec = _resources.grids['grdIntRate'].getSelectedRecord();
		var index = _resources.grids['grdIntRate'].getSelectionModel().last;

		//rec.data.errMsg = '';
		data.Scale.errMsg = '';
		var scaleRecindex = 0;
		if (action == _self.ADD)
		{
			_resources.grids['grdIntRateScale'].addRecord(data.Scale);

			if (rec.data['runMode'] != ADD)
				rec.data['runMode'] = MOD;
		}
		else {
			//var scaleRec = _resources.grids['grdIntRateScale'].getSelectedRecord();
			scaleRecindex = _resources.grids['grdIntRateScale'].getSelectionModel().last;

			_resources.grids['grdIntRateScale'].updateSelectedRecord(data.Scale);

			if (!!!rec.data['runMode'] && rec.data['runMode'] == '')
				rec.data['runMode'] = MOD;
		}

		var xmlString =  genXMLString('grdIntRateScale', 'Scale', 'Scales');
		// prompt("Scale", xmlString);

		rec.data['ScalesNode'] =  !!xmlString ? IFDS.Xml.stringToXML(xmlString) : null;
		rec.commit();
		_resources.grids['grdIntRate'].setSelectedRecord(index);

		if (action == MOD )
			_resources.grids['grdIntRateScale'].setSelectedRecord(scaleRecindex);
		else
			_resources.grids['grdIntRateScale'].selectLastRecord();

		_popScale.hide();
	}

	function saveUpdateToMstrXML(popupName, action, data)
	{
		_self.updatesFlag = true;
		if (popupName == "frmIntRate")
			applyToGridIntRate(action, data);
		else if (popupName == "frmIntRateScale")
			applyToGridScale(action, data);

		enablePermButtons();
	}

	function getUpdateRequest(mode) {
		var updateXML = IFDS.Xml.newDocument('data');
		var allNode = IFDS.Xml.addSingleNode(updateXML, 'InterestRates');

		var store = _resources.grids['grdIntRate'].getStore();
		var modes =  [_self.DEL, _self.MOD, _self.ADD];

		for (var iRateMode = 0; iRateMode < modes.length ; iRateMode++) {
			store.query('runMode',modes[iRateMode]).each(addToInterestRateXML);
		}
		return updateXML;

		function addToInterestRateXML(item)
		{
			var data = item.data;

			var intRateXML = IFDS.Xml.addSingleNode(allNode, 'InterestRate');

			IFDS.Xml.addAttribute(intRateXML, 'RecordSource', data.interestRateUUID);
			IFDS.Xml.addSingleNode(intRateXML, 'runMode', data.runMode);
			IFDS.Xml.addSingleNode(intRateXML, 'updSeq', SEQ[data.runMode]);
			IFDS.Xml.addSingleNode(intRateXML, 'interestRateUUID', data.interestRateUUID);
			IFDS.Xml.addSingleNode(intRateXML, 'fundCategory', data.fundCategory);
			IFDS.Xml.addSingleNode(intRateXML, 'intCalcMthd', data.intCalcMthd);
			IFDS.Xml.addSingleNode(intRateXML, 'rateCode', data.rateCode);
			IFDS.Xml.addSingleNode(intRateXML, 'rateCodeType', data.rateCodeType);
			IFDS.Xml.addSingleNode(intRateXML, 'deff', DesktopWeb.Util.getSMVDateValue(data.deff));
			IFDS.Xml.addSingleNode(intRateXML, 'sequence', data.sequence);
			IFDS.Xml.addSingleNode(intRateXML, 'intTerm', data.intTerm);
			IFDS.Xml.addSingleNode(intRateXML, 'rateType', data.rateType);
			IFDS.Xml.addSingleNode(intRateXML, 'verified', data.verified);
			IFDS.Xml.addSingleNode(intRateXML, 'version',data.version);

			var scalesNode = IFDS.Xml.addSingleNode(intRateXML, 'Scales');
			//alert(data.rateTypeChange + !!data.rateTypeChange && data.rateTypeChange === '1');
			if (!!data.rateTypeChange && data.rateTypeChange === '1') {
					var origRecord = _resources.grids['grdIntRate'].getOrigStore().query('interestRateUUID',data.interestRateUUID);
					origRecord.each(function getScale(origItem){
						if (origItem.data.rateType === data.rateType && !!origItem.data.ScalesNode) {
							var temp = IFDS.Xml.stringToXML(IFDS.Xml.serialize(origItem.data.ScalesNode));
							var listNodes = IFDS.Xml.getNodes(temp, "/*//Scale");
							addToScaleXML(listNodes, scalesNode, data.interestRateUUID, DEL );
						}
					});
			}

			//Generate Identifications
			if (!!data['ScalesNode'])
			{
				for (var iMode = 0; iMode < modes.length ; iMode++) {
					addToScaleXML(IFDS.Xml.getNodes(data.ScalesNode, "/*//Scale[runMode = '" + modes[iMode] + "']"),
						scalesNode, data.interestRateUUID);
				}
				/*Require for new validataion */
				addToScaleXML(IFDS.Xml.getNodes(data.ScalesNode, "/*//Scale[runMode = '']"),
						scalesNode, data.interestRateUUID);
			}
		} // internal function addToInterestRateXML
		function addToScaleXML(nodes, parentNode, key , mode)	{
		  if (!!nodes) {
				// prompt("addToScaleXML nodes",  IFDS.Xml.serialize(nodes) );
				for (var iCount = 0; iCount < nodes.length; iCount++){
					var node = nodes[iCount];
					// prompt("addToScaleXML node",  IFDS.Xml.serialize(node) );
					var updIntRateScaleXML = IFDS.Xml.addSingleNode(parentNode, 'Scale');
					var scaleUUID =  IFDS.Xml.getNodeValue(node, 'interestRateScaleUUID');

					IFDS.Xml.addAttribute(updIntRateScaleXML, 'RecordSource', key + _SEPERATOR  + scaleUUID);
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'interestRateScaleUUID',scaleUUID);
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'interestRateUUID',key);
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'runMode',!!mode ? mode : IFDS.Xml.getNodeValue(node, 'runMode'));
				  IFDS.Xml.addSingleNode(updIntRateScaleXML, 'updSeq', SEQ[!!mode ? mode : IFDS.Xml.getNodeValue(node, 'runMode')]);
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'lower', IFDS.Xml.getNodeValue(node, 'lower'));
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'upper', IFDS.Xml.getNodeValue(node, 'upper'));
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'rate', IFDS.Xml.getNodeValue(node, 'rate'));
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'version', IFDS.Xml.getNodeValue(node, 'version'));

					var rateSplitNode = IFDS.Xml.getNode(node,
														"/*//Scale[interestRateScaleUUID='" + scaleUUID + "']/RateSplitList");

					if (!!rateSplitNode) {
						var tempNodes = IFDS.Xml.stringToXML( IFDS.Xml.serialize(rateSplitNode) );
						var rateSplitListNode = IFDS.Xml.addSingleNode(updIntRateScaleXML, 'RateSplitList');

						if (mode == DEL)
							addToRateSplitXML(IFDS.Xml.getNodes(tempNodes, "/*//RateSplit"), rateSplitListNode, key + _SEPERATOR + scaleUUID ,scaleUUID, mode)
						else {
							addToRateSplitXML(IFDS.Xml.getNodes(tempNodes, "/*//RateSplit"),
									rateSplitListNode, key + _SEPERATOR + scaleUUID,scaleUUID);
							
					 }
					}
				} //for
			} //  if (!!nodes)
		} // internal function addToScaleXML

		function addToRateSplitXML(nodes, parentNode, key, scaleUUID, mode){
		  if (!!nodes) {
				for (var iCount = 0; iCount < nodes.length; iCount++){
					var node = nodes[iCount];
					var updIntRateScaleXML = IFDS.Xml.addSingleNode(parentNode, 'RateSplit');
					var rateSplitUUID =  IFDS.Xml.getNodeValue(node, 'rateSplitUUID');

					IFDS.Xml.addAttribute(updIntRateScaleXML, 'RecordSource', key + _SEPERATOR + rateSplitUUID);
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'interestRateScaleUUID',scaleUUID);
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'rateSplitUUID',rateSplitUUID);
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'runMode',!!mode ? mode : IFDS.Xml.getNodeValue(node, 'runMode'));
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'updSeq', SEQ[!!mode ? mode : IFDS.Xml.getNodeValue(node, 'runMode')]);
				  IFDS.Xml.addSingleNode(updIntRateScaleXML, 'rateEntityType', IFDS.Xml.getNodeValue(node, 'rateEntityType'));
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'rate', IFDS.Xml.getNodeValue(node, 'rate'));
					IFDS.Xml.addSingleNode(updIntRateScaleXML, 'version', IFDS.Xml.getNodeValue(node, 'version'));
				}
			}
		} //internal function addToRateSplitXML(
	} //getUpdateRequest

	function clearErrMsg()	{
		_resources.grids['grdIntRate'].getStore().queryBy(function(record, id){
					return (record.get('errMsg') != "");
			}
		).each(function clear(record) {
			var item = record.data;

			if (!!record.data.ScalesNode) {
        
        updateErrorMsg(IFDS.Xml.getNodes(record.data.ScalesNode,
													"/*//Scale/*//RateSplit")
													,_blank);
                  
				var listNodes = IFDS.Xml.getNodes(record.data.ScalesNode, "/*//Scale/errMsg");
				if (listNodes) {
					for (var i = 0; i < listNodes.length; i++)
					{
						var node = IFDS.Xml.getNode(listNodes[i], '.');
						if (!!node)
							IFDS.Xml.setNodeValue(node,_blank);
            
					}
 
					record.set('ScalesNode', record.data.ScalesNode);
				}
			}
			record.set('errMsg', _blank);
			record.commit();
		});

	}

	/*
	* Called by storeContextErrors
	*/
	function updateErrorMsg(nodeList,errMsg) {
		if (!!nodeList) {
		 for (var i = 0; i < nodeList.length; i++){
			 var node = IFDS.Xml.getNode(nodeList[i], 'errMsg');
      
			 if (!!node)
				 IFDS.Xml.setNodeValue(node,errMsg);
			 else
				 IFDS.Xml.addSingleNode(nodeList[i], 'errMsg', errMsg);
		 } //for
		}
	}  //function updateErrorMsg

	function cleanDelMode(nodeList) {
		if (!!nodeList) {
			var rateNodesList = null;
			for (var i = 0; i < nodeList.length; i++) {
				var runMode = IFDS.Xml.getNode(nodeList[i], 'runMode');
				var interestRateScaleUUID = IFDS.Xml.getNodeValue(nodeList[i], 'interestRateScaleUUID');

				if (!!runMode) {
					var runModeType = IFDS.Xml.getNodeValue(runMode, '.');
					if (runModeType == DEL) {
						IFDS.Xml.setNodeValue(runMode, _blank);
						rateNodesList = IFDS.Xml.getNodes(nodeList[i],
							"/*//RateSplit[interestRateScaleUUID = '" + interestRateScaleUUID + "']");

						if (!!rateNodesList)
							 cleanDelMode(rateNodesList);
					} //if (runModeType == DEL)
				} //for
			}
		}
	} //function cleanDelMode

	function storeContextErrors(errorNodes)	{
		//alert("storeContextErrors");
		clearErrMsg();
		var firstErrRecIndex = -1;

		Ext.each(errorNodes, function(errorNode){
			var errMsg = IFDS.Xml.getNodeValue(errorNode, 'text');
			var allKeys = IFDS.Xml.getNodeValue(errorNode, 'recordSource/source/elementSource');
			var keyArray = {};

			if (allKeys.indexOf(_SEPERATOR) != -1)
				keyArray = allKeys.split(_SEPERATOR);
			else
				keyArray[0] = allKeys;

			var recordIndex = _resources.grids['grdIntRate'].getStore().find('interestRateUUID', keyArray[0]);
			var errRecord = _resources.grids['grdIntRate'].getStore().getAt(recordIndex);

			if (!!errRecord ){
				if (keyArray.length > 1) {
					var xmlDoc = errRecord.data.ScalesNode;
					errRecord.set('errMsg',  _translationMap['InvalidScale']);

					var scalesNodes = IFDS.Xml.getNodes(xmlDoc, "/*//Scale[interestRateScaleUUID = '" + keyArray[1] + "']");

					var rateNodes  = null;
					//Mark error on  RateSplit table
					if (!!scalesNodes) {
						if (keyArray.length == 3) {
							updateErrorMsg(IFDS.Xml.getNodes(xmlDoc,
													"/*//Scale[interestRateScaleUUID = '" + keyArray[1] + "']//RateSplit[rateSplitUUID = '" + keyArray[2] + "']")
													, errMsg);
							errMsg =  _translationMap['InvalidRateSplit'];
							errRecord.set('errMsg', errMsg);
						} // if (keyArray.length == 3)

						 updateErrorMsg(scalesNodes,errMsg);
						 cleanDelMode(scalesNodes);

						errRecord.set('ScalesNode', xmlDoc);
					} // if (!!scalesNodes)
					errRecord.commit();
				} //if (hasScaleError) keyArray.length  > 1
				else	{
					errRecord.set('errMsg', errMsg);
					errRecord.commit();
				}

				var errRecordIndex = _resources.grids['grdIntRate'].getRecordIndex(errRecord);
				if ( firstErrRecIndex == -1 || firstErrRecIndex > errRecordIndex )
					firstErrRecrIndex = errRecordIndex;

			} //if (!!errRecord )
		}); //Ext.each(

		_resources.grids['grdIntRate'].getSelectionModel().selectRow(firstErrRecIndex);
		_resources.grids['grdIntRate'].focusRow(firstErrRecIndex);
		setSelectedIntRate();
	} //function storeContextErrors

	function funcAdminPopup(recType) {
		var title = null;
		var obj = null;
		switch (recType) {
			case 'intRate' : {
				title = _translationMap['InterestRate']  + ' - ' + _translationMap['Admin'];
				obj = getSelectedIntRate();
				break;
			}
			case 'intRateScale' : {
				title =  _translationMap['InterestRate']  + " " + getSelectedRateType() + ' - ' + _translationMap['Admin'];
				obj = getSelectedIntRateScale();
				break;
			}
			case 'RateSplit' : {
				title =  _translationMap['RateSplit']  + ' - ' + _translationMap['Admin'];
				obj =  _resources.grids['grdRateSplit'].getSelectedRecord().data;
        break;
		 }
		}
		var adminData = {};
		adminData['userName'] = obj.userName;
		adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(obj.procDate);
		adminData['modUser'] = obj.modUser;
		adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(obj.modDate);

		_resources.popups['frmAdmin'].init(title, adminData);
		_resources.popups['frmAdmin'].show();
	} //  function funcAdminPopup

	function funcHistoryPopup(recType) 	{
		var title = null;
		var viewParam = {};
		var historyService = _historyView;
		if (recType == 'intRate')
		{
			viewParam['auditType'] = 'InterestRate';
			var rec = getSelectedIntRate();
			viewParam['searchValue1'] = rec.interestRateUUID;
			if (rec.rateType.toLowerCase() === 'percent') {
				historyService = "dtHistoricalList";
				viewParam['searchValue1'] = viewParam['searchValue1'] + "," + rec.interestRateScaleUUID;
			}
			title = _translationMap['InterestRate']  + ' - ' + _translationMap['History'];

		}
		else if (recType == 'intRateScale')
		{
			viewParam['auditType'] = 'InterestRateScale';
			viewParam['searchValue1'] = getSelectedIntRateScale().interestRateScaleUUID;
			title = _translationMap['InterestRate'] + " " + getSelectedRateType() + ' - ' + _translationMap['History'];
		}
		else if (recType == 'RateSplit')
		{
			var data = _resources.grids['grdRateSplit'].getSelectedRecord().data;
			if (!!data) {
				viewParam['auditType'] = 'RateSplit';
				viewParam['searchValue1'] = _resources.grids['grdRateSplit'].getSelectedRecord().data.rateSplitUUID;
				title =  _translationMap['RateSplit']  + ' - ' + _translationMap['History'];
			}
		}
		_resources.popups['frmHistory'].init(title, historyService, viewParam, true);
		_resources.popups['frmHistory'].show();
	}//function funcHistoryPopup

	function openActionPopup (popupName, action){
		_resources.popups[popupName].init(action);

		_resources.popups[popupName].show();
	} //function openActionPopup

	function doUpdate()	{
		/* Backup */
		var updateStatus = null;

		DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest(), responseHandler, _translationMap['Updating']);

		function responseHandler(success, responseXML, contextErrors)	{
			if (success)
				updateStatus = DesktopWeb._SUCCESS;
			else{
				storeContextErrors(contextErrors);
				updateStatus = DesktopWeb._FAIL;
			}
		}

		return updateStatus;
	}	 //function doUpdate()

	function getSelectedRateType(){
		return getSelectedIntRate().rateType;
	}

	// PUBLIC ITEMS *************************************
	return {
		ADD: ADD
		, MOD: MOD
		, DEL: DEL
		, UNCH: UNCH
		, updatesFlag: false
		, disableRateSplit: false
		, init : funcInit
		, defaultValues : _defaultValues
		, doSearch : funcSearch
		, setSelectedIntRate: setSelectedIntRate
		, setSelectedIntRateScale: setSelectedIntRateScale
		, openActionPopup: openActionPopup
		, setDefaultNewIntRate: setDefaultNewIntRate
		, setDefaultNewIntRateScale: setDefaultNewIntRateScale
		, populateIntRate: funcPopulateIntRate
		, populateIntRateScale: funcPopulateIntRateScale
		, doUpdate: doUpdate
		, populateDropdownsRule: funcPopulateDropdownsRule
		, doValidate: funcDoValidate
		, openAdminPopup: funcAdminPopup
		, openHistoryPopup: funcHistoryPopup
		, getRateType: getSelectedRateType
	} // return
}