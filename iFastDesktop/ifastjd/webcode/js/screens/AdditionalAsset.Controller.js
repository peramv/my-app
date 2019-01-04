/*
 * Procedure: AdditionAsset.Controller.js
 *
 * Purpose  : 
 *             
 * Notes    : Open screens by 
 *                Menu -> MF and MFR Maintenance -> Additional Assets
 *				  Menu -> System Maintenance -> Holding Company -> Additional Assets
 *
 * History  : 
 *	
 *		05 Mar 2013 Gomoot T. PETP0206635 FN01 T53252 MFR MFI Enhancements 
 *			- Created
 *
 *		07 May 2013 Gomoot T. PETP0206635 FN01 IN3316087 T53522
 *			- Fix the prepopulate  screen when launching from Main Menu by 
 *			The Prepopulate will be
 *			1)Holding Company must be editable.
 *			2)There is any data on grid so the pre-populate of holding company 
 *              on Add screen is follow the selected record.
 *			3)There is no data on Grid so the pre-populate of holding company 
 *              on Add screen is follow the Holding Company Search criteria if this field is not blank
 *			4)Otherwise there is no pre-populate on Add screen
 *
 *		23 May 2013 Gomoot T. PETP0206635 FN01 IN3330320 T53597
 *			- When launching screen from Holding Company, the As Of Date has to set 
 *            and there is no error message on initiate screen.
 *          - Fix Sub Advised Asset screen to not able to search when  
 *            either effective or stop date is blank.
 *
 *		29 May 2013 Gomoot T. PETP0206635 FN01 IN3338220 T53638
 *          - Change the update state by
 *          1) Call with  validation mode
 *          2) if there is no error, call commit screen which will make the update to database.
 *          - Add ignoreErrorCode#15 for Sub Advise Asset popup screen when initiate screen.
 *
 *      12 Nov 2013 N. Kanjanawaikoon PP0181067 FN01 CHG0034430 T54444
 *          - Getting the date format from DesktopWeb.Util.getDateDisplayValue to show
 *            all date with correct format from registry field
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _nextStartRecNum = null;
	var _requestRecNum = 25;	//The number of record display on gri
	var _additionCounter = 0;

	var _inqView = 'dtAddiAssetInq';
	var _updateView = 'dtAddiAssetUpd';
	var _historyService = 'dtHistoricalInfo';
	var _subAdviseInit = 'dtFeeIDAssetValInit';
		
	var _vars = {};	
	var _listXMLs = {};
	var _permissionsMap = {};
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	
	var _CADD = 'addBtn';
	var _CMOD = 'modBtn';
	var _CDEL = 'delBtn';
	var _CMORE= 'moreBtn';
	var _CSUBADVISED = 'subAdviseBtn';
	var _CADMIN = 'adminBtn';
	var _CHISTORY = 'historicalBtn';
		
	
	// PRIVATE METHODS ****************************************	
	// Operate on XMLs
	/*Step1*/
	function createListXML(xml)
	{
		var listXMLArr = IFDS.Xml.getNodes(xml, "/*//List");
		
		Ext.each(listXMLArr, function(listXML){
			controlName = listXML.getAttribute('listName');
			_listXMLs[controlName] = listXML;
		});
	}
	/*Step 2*/
	function storePermissions(xml)
	{	
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(xml, '/*//Permissions/inqPerm').toLowerCase() == _self.YES;
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(xml, '/*//Permissions/addPerm').toLowerCase() == _self.YES;
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(xml, '/*//Permissions/modPerm').toLowerCase() == _self.YES;
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(xml, '/*//Permissions/delPerm').toLowerCase() == _self.YES;		
	}		
	/*Step 3*/
	function storeDefaultValues(xml)
	{		
		_vars['EffectiveDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '/*//DefaultValues/effectiveDate'));
		_vars['StopDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '/*//DefaultValues/stopDate'));	
	}
	
	function storeHoldingEntityValues(xml)
	{		
		_vars['holdingEntityCode'] = IFDS.Xml.getNodeValue(xml, '/*//holdingEntityDisp/holdingEntityCode');			
		_vars['holdingEntityDesc'] = IFDS.Xml.getNodeValue(xml, '/*//holdingEntityDisp/holdingEntityDesc');	
		_vars['holdingEntityValue'] = IFDS.Xml.getNodeValue(xml, '/*//holdingEntityDisp/displayValue');		
	}
	
	function setHoldingEntityValues()
	{		
		var record  = _resources.fields['holdingCompanySrch'].selectedRecord;
		
		if (record != null)
		{
			_vars['holdingEntityCode'] = record.data['holdingCompanyCode'];		
			_vars['holdingEntityDesc'] = record.data['holdingCompanyDesc'];
			_vars['holdingEntityValue'] = record.data['displayValue'];	
		}
		else
			_self.clearHoldingCompany();
	}
	
	function loadAdditionAsset(xml, append)
	{		
		var acctAsscXMLArr = IFDS.Xml.getNodes(xml, '/*//AdditionAssets');		
		if (acctAsscXMLArr != null && acctAsscXMLArr != undefined && acctAsscXMLArr.length > 0)
			_resources.grids['grdAdditionalAsset'].getStore().loadData(IFDS.Xml.getNode(xml, '/*//AdditionAssets'), append);
		
	}		
	
	function getInitRequest()
	{
		var requestXML = IFDS.Xml.newDocument("data");	
					
		if (_vars['holdingEntityCode'] != _self.BLANK && _vars['holdingEntityCode'] != undefined)
		{
			IFDS.Xml.addSingleNode(requestXML, "holdingEntityCode", _vars['holdingEntityCode']);
			_resources.fields['holdingCompanySrch'].disableField()
		}
		
		IFDS.Xml.addSingleNode(requestXML, "startRecNum", 1);
		IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);
		IFDS.Xml.addSingleNode(requestXML, "runMode", "init");
		
		return requestXML;
	}
	
	function getReloadRequest(more)
	{
		var requestXML = IFDS.Xml.newDocument("data");
		if (_resources.fields['holdingCompanySrch'].getValue() != _self.BLANK)
			IFDS.Xml.addSingleNode(requestXML, "holdingEntityCode"
				, _resources.fields['holdingCompanySrch'].getValue());	
					
		if (_resources.fields['assetTypeSrch'].getRawValue() != null)
			IFDS.Xml.addSingleNode(requestXML, "assetType"
				, _resources.fields['assetTypeSrch'].getValue());
		

		if (!_resources.fields['optSelectAll'].getValue())
			IFDS.Xml.addSingleNode(requestXML, "effectiveDate"
				, DesktopWeb.Util.getDateString(_resources.fields['asOfDate'].getValue()
				, DesktopWeb._SCREEN_PARAM_MAP['dateFormat']));
			
			
		IFDS.Xml.addSingleNode(requestXML, "startRecNum", (more ? _nextStartRecNum : 1));
		IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);
		
		IFDS.Xml.addSingleNode(requestXML, "runMode", "reload");
		return requestXML;
	}
	
	function getUpdateRequest(mode)
	{		
		var updateXML = IFDS.Xml.newDocument('data');
		
		var AdditionAll = IFDS.Xml.addSingleNode(updateXML, 'AdditionAssets');
		IFDS.Xml.addSingleNode(AdditionAll, 'runMode', mode);
		var store = _resources.grids['grdAdditionalAsset'].getStore();

		var delRecords = store.query('runMode', _self.DEL);
		delRecords.each(addToXML);
		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToXML);
		var newRecords = store.query('runMode', _self.ADD);
		newRecords.each(addToXML);
		
		return updateXML;
		
		function addToXML(item)
		{
			var recordXML = IFDS.Xml.addSingleNode(AdditionAll, 'AdditionAssetDetail');
			IFDS.Xml.addAttribute(recordXML, 'RecordSource', item.data['feeAggrID']);
			IFDS.Xml.addSingleNode(recordXML, 'runMode', item.data['runMode']);
			
			IFDS.Xml.addSingleNode(recordXML, 'feeAggrID', item.data['feeAggrID']);
			IFDS.Xml.addSingleNode(recordXML, 'holdingEntityCode', item.data['holdingEntityCode']);
			IFDS.Xml.addSingleNode(recordXML, 'assetTypeCode', item.data['assetTypeCode']);
			IFDS.Xml.addSingleNode(recordXML, 'version', item.data['version']);
			IFDS.Xml.addSingleNode(recordXML, 'identifier', item.data['identifier']);
			if (item.data['identifier2'] !== "" || item.data['identifier2'] !== undefined)
				IFDS.Xml.addSingleNode(recordXML, 'identifier2', item.data['identifier2']);
			IFDS.Xml.addSingleNode(recordXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(item.data['stopDate']));
			IFDS.Xml.addSingleNode(recordXML, 'effectiveDate', DesktopWeb.Util.getSMVDateValue(item.data['effectiveDate']));
		}
	}	
	
	function getUpdatedRecordCount()
	{		
		var store = _resources.grids['grdAdditionalAsset'].getStore();
		var newRecords = store.query('runMode', _self.ADD);
		var modRecords = store.query('runMode', _self.MOD);
		var delRecords = store.query('runMode', _self.DEL);
		
		return newRecords.length + modRecords.length + delRecords.length 
	}
	
	//Add for generate new record on grid
	function storeContextErrors(errorNodes)
	{
		clearContextErrors();
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var feeAggrID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			
			// Update Grid
			var recordIndex = _resources.grids['grdAdditionalAsset'].getStore().find('feeAggrID', feeAggrID);
			var additionalAssetRecord = _resources.grids['grdAdditionalAsset'].getStore().getAt(recordIndex);
			if (additionalAssetRecord !== undefined)
			{
				additionalAssetRecord.set('errMsg', errMsg);
				_resources.grids['grdAdditionalAsset'].getStore().commitChanges();
				if(firstErrRecIndex == -1)
					firstErrRecIndex = recordIndex;
			}
		}
		if(firstErrRecIndex==-1)
		{
			_resources.grids['grdAdditionalAsset'].getSelectionModel().selectFirstRow();
		}else{
			_resources.grids['grdAdditionalAsset'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['grdAdditionalAsset'].focusRow(firstErrRecIndex);
		}
	}
	
	function clearContextErrors(feeAggrID)
	{
		if ( feeAggrID && feeAggrID.length > 0 )
		{
			var recordIndex = _resources.grids['grdAdditionalAsset'].getStore().find('feeAggrID', feeAggrID);
			var additionalAssetRecord = _resources.grids['grdAdditionalAsset'].getStore().getAt(recordIndex);
			additionalAssetRecord.set('errMsg', errMsg);
		}else{
			var errAdditionalAssetRecords = _resources.grids['grdAdditionalAsset'].getStore().queryBy(
				function(record, id){            
					return ( record.get('errMsg') != null && record.get('errMsg') != "" );
				}
			);
			
			errAdditionalAssetRecords.each( function resetError(item) { item.set('errMsg', '') });
		}
	}
	
	/*Start SubAdvise operation*/
	function getSubAdviseRequest(state)
	{
		var requestXML = IFDS.Xml.newDocument("data");
		
		var xml = _resources.grids['grdAdditionalAsset'].getSelectedRecord();
		
		if (xml != null && xml != undefined)
		{
			IFDS.Xml.addSingleNode(requestXML, "assetCode", xml.data[ 'identifier']);	
		    if (state != undefined && state) 
			{
			    if (_resources.fields['subAdviseStartDate'].getValue() != _self.BLANK)
					IFDS.Xml.addSingleNode(requestXML, "startDate", _resources.fields['subAdviseStartDate'].getSMVDateString());
				if (_resources.fields['subAdviseStopDate'].getValue() != _self.BLANK)
					IFDS.Xml.addSingleNode(requestXML, "endDate", _resources.fields['subAdviseStopDate'].getSMVDateString());	
			}
			
		}

		return requestXML;
	}
	
	function loadSubAdvise(xml)
	{	
		var subXML = IFDS.Xml.getNodes(xml, '/*//AssetValues');
				
		if (subXML != null && subXML != undefined && subXML.length > 0)
			_resources.grids['grdSubAdvise'].loadData(IFDS.Xml.getNode(xml, '/*//AssetValues'), null);
	}
	
	function setInitSubAdvise(xml)
	{
		_resources.fields['subAdviseName'].setValue(IFDS.Xml.getNodeValue(xml, '/*//dtFeeIDAssetValInitResponse/assetCode'));
		_resources.fields['subAdviseName'].setRawValue(IFDS.Xml.getNodeValue(xml, '/*//dtFeeIDAssetValInitResponse/assetName'));
		_resources.fields['subAdviseName'].disableField();
		
		var subAdviseStartDate = IFDS.Xml.getNodeValue(xml, '/*//dtFeeIDAssetValInitResponse/startDate');
		if (subAdviseStartDate)
		{
			_resources.fields['subAdviseStartDate'].setValue(DesktopWeb.Util.getDateDisplayValue(subAdviseStartDate));
		}
		
		var subAdviseStopDate = IFDS.Xml.getNodeValue(xml, '/*//dtFeeIDAssetValInitResponse/endDate');
		if (subAdviseStopDate)
		{
			_resources.fields['subAdviseStopDate'].setValue(DesktopWeb.Util.getDateDisplayValue(subAdviseStopDate));
		}
	}
	
	/*End SubAdvise operation*/
	
	function checkRequireField(data)
	{
		var success = true;
		if (data['holdingEntityCode'] == undefined || data['holdingEntityCode'] == '')
		{
			success = false;
			_resources.fields['holdingCompanyPopUp'].markInvalid(_translationMap['Error_HoldingCompanyRequire']);
		}
		
		if (data['assetTypeCode'] === undefined || data['assetTypeCode']  == '')
		{
			success = false;
			_resources.fields['assetTypePopup'].markInvalid(_translationMap['Error_AssetTypeRequire']);
		}
		
		if (data['identifier'] === undefined || data['identifier']  == '')
		{
			success = false;
			if (data['assetTypeCode'] == _self.ACCOUNT)
				_resources.fields['accountPopup'].markInvalid(_translationMap['Error_AccountRequire']);
			else if (data['assetTypeCode'] == _self.BROKER)
				_resources.fields['brokerPopup'].markInvalid(_translationMap['Error_BrokerRequire']);
			else if (data['assetTypeCode'] == _self.SUBADV)
				_resources.fields['subAdvisedPopup'].markInvalid(_translationMap['Error_SubAdviseRequire']);
			else if (data['assetTypeCode'] == _self.SALERESP)
			{
				_resources.fields['saleRespPopup'].markInvalid(_translationMap['Error_SalesRespRequire']);
				
				if (data['identifier2'] == undefined || data['identifier2']  == '')	
					_resources.fields['brokerPopup'].markInvalid(_translationMap['Error_BrokerRequire']);
			}
		}
		
		if (data['assetTypeCode'] == _self.SALERESP && (data['identifier2'] === undefined || data['identifier2']  == ''))
		{
			success = false;
			_resources.fields['brokerPopup'].markInvalid(_translationMap['Error_BrokerRequire']);
		}
		
		return success;
	}
	
	function setDefaultHoldingCompanySearch()
	{
		_resources.fields['holdingCompanySrch'].disableField();
	
		var xml = IFDS.Xml.newDocument("data");
		var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
			
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['holdingCompanySrch'].valueField, _vars['holdingEntityCode']);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['holdingCompanySrch'].displayField, _vars['holdingEntityValue']);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, "holdingCompanyDesc" , _vars['holdingEntityDesc']);
		
		_resources.fields['holdingCompanySrch'].getStore().loadData(xml);
		_resources.fields['holdingCompanySrch'].setValue(_vars['holdingEntityCode']);
	}
	
	function setDefaultHoldingCompanyPopup(obj)
	{	
		var code = "";
		var dispValue = "";
		var desc = "";
		
		_resources.fields['holdingCompanyPopUp'].reset();				
		if (obj)
		{
			code = obj.holdingEntityCode;
			dispValue = obj.holdingEntityCode + " - " + obj.holdingEntityDesc;
			desc = obj.holdingEntityDesc;
			_resources.fields['holdingCompanyPopUp'].disableField();
		}
		else
		{
			var selectedRecord = _self.getSelectedAdditionalAsset();
			if (selectedRecord)
			{
				code      = selectedRecord.holdingEntityCode ;
				dispValue = selectedRecord.holdingEntityCode + " - " + selectedRecord.holdingEntityDesc;
				desc      = selectedRecord.holdingEntityDesc;
			}
			else
			{
				code      = _vars['holdingEntityCode'];
				dispValue = _vars['holdingEntityValue'];
				desc      = _vars['holdingEntityDesc'];
			}

		}
		
		
		
		if ( code != "")
		{
			var xml = IFDS.Xml.newDocument("data");
			var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');

			IFDS.Xml.addSingleNode(possibleMatchXML
				, _resources.fields['holdingCompanyPopUp'].valueField, code);
			IFDS.Xml.addSingleNode(possibleMatchXML
				, _resources.fields['holdingCompanyPopUp'].displayField, dispValue);
			IFDS.Xml.addSingleNode(possibleMatchXML
				, "holdingCompanyDesc" , desc);
			
			_resources.fields['holdingCompanyPopUp'].getStore().loadData(xml);
			_resources.fields['holdingCompanyPopUp'].setValue(code);
		}
		else
			_resources.fields['holdingCompanyPopUp'].reset();
	}
	

	function setDefaultAccountPopup(obj)
	{	
		_resources.fields['accountPopup'].disableField();
		var dispValue = obj.identifier + " - " + obj.name;

		var xml = IFDS.Xml.newDocument("data");
		var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
			
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['accountPopup'].valueField, obj.identifier);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['accountPopup'].displayField, dispValue);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, "accountDesc" , obj.name);	
		
		_resources.fields['accountPopup'].getStore().loadData(xml);
		_resources.fields['accountPopup'].setValue(obj.identifier);
	}
	
	function setDefaultBrokerPopup(obj)
	{
		_resources.fields['brokerPopup'].disableField();
		var dispValue = obj.identifier + " " + obj.name;

		var xml = IFDS.Xml.newDocument("data");
		var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
			
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['brokerPopup'].valueField, obj.identifier);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['brokerPopup'].displayField, dispValue);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, "brokerDesc" , obj.name);	
		
		_resources.fields['brokerPopup'].getStore().loadData(xml);
		_resources.fields['brokerPopup'].setValue(obj.identifier);
	}
	
	function setDefaultSaleRespPopup(obj)
	{
		_resources.fields['saleRespPopup'].disableField();	
		var dispValue = obj.identifier + " " + obj.name;	
		var dispValue2 = obj.identifier2 + " " + obj.name2;	

		var xml = IFDS.Xml.newDocument("data");
		var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
			
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['saleRespPopup'].valueField, obj.identifier);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['saleRespPopup'].displayField, dispValue);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, "saleRespDesc" , obj.name);
		
		_resources.fields['saleRespPopup'].getStore().loadData(xml);
		_resources.fields['saleRespPopup'].setValue(obj.identifier);
		
		_resources.fields['brokerPopup'].disableField();
		var dispValue = obj.identifier + " " + obj.name;

		var xml = IFDS.Xml.newDocument("data");
		var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');
			
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['brokerPopup'].valueField, obj.identifier2);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, _resources.fields['brokerPopup'].displayField, dispValue2);
		IFDS.Xml.addSingleNode(possibleMatchXML
			, "brokerDesc" , obj.name2);
		
		_resources.fields['brokerPopup'].getStore().loadData(xml);
		_resources.fields['brokerPopup'].setValue(obj.identifier2);	
	}
	
	
	function setVisibleAllContentPopup(visible, assetTypeCode)
	{
		_resources.fields['accountPopup'].setVisible(visible);
		_resources.fields['brokerPopup'].setVisible(visible)
		_resources.fields['saleRespPopup'].setVisible(visible);
		_resources.fields['subAdvisedPopup'].setVisible(visible);
		
		if (!visible)
		{
			if (assetTypeCode == _self.ACCOUNT)
				_resources.fields['accountPopup'].setVisible(!visible);
			else if (assetTypeCode == _self.BROKER)
				_resources.fields['brokerPopup'].setVisible(!visible);
			else if (assetTypeCode == _self.SALERESP)
			{
				_resources.fields['brokerPopup'].setVisible(!visible)
				_resources.fields['saleRespPopup'].setVisible(!visible);
			}
			else if (assetTypeCode == _self.SUBADV)
				_resources.fields['subAdvisedPopup'].setVisible(!visible);
				
			_resources.popups['frmAdditionalAsset'].syncSize();
		}
	}

	// PUBLIC ITEMS *************************************
	// Operate on Objects
	return {				
		ADD: 'Add'
		, DEL: 'Del'
		, MOD: 'Mod'		
		, YES: 'yes'
		, NO: 'no'
		, BLANK: ''		
		, updatesFlag: false
		, ACCOUNT : "AC"
		, BROKER : "AG"
		, SALERESP : "SR"
		, SUBADV : "EA"
		, NEW : "NEWADDA"
		
		, init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;		
			
			_vars['fromHoldingScreen'] = false;
			_vars['holdingEntityCode']  = DesktopWeb._SCREEN_PARAM_MAP['HoldingEntityCode'];
			
			if ((_vars['holdingEntityCode']  === undefined || _vars['holdingEntityCode'] == null))
				_vars['holdingEntityCode'] = '';
			else 
				_vars['fromHoldingScreen'] = true; 							
			
			DesktopWeb.Ajax.doSmartviewAjax(_inqView, {ignoreErrorCode: '15'}, getInitRequest(), responseHandler, _translationMap['Loading']);
			
			function responseHandler(success, responseXML)
			{
				createListXML(responseXML);
				storePermissions(responseXML);
				storeDefaultValues(responseXML);
				storeHoldingEntityValues(responseXML);
				_self.enablePermButtons();
				_self.populateDropdowns();
				_self.setDefaultSearch();
				_self.enableSearch();

				if (success)
				{
					loadAdditionAsset(responseXML, false);
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					_self.enableMoreButton(_nextStartRecNum);
					_self.refreshGrdAdditionalAsset(0);	
				}
				
			}
		}
		
		, populateDropdowns: function()
		{
			if (_listXMLs["subAdvisedAssets"] !== undefined)
				_resources.fields['subAdvisedPopup'].getStore().loadData(_listXMLs["subAdvisedAssets"]);
				
			if (_listXMLs["assetType"] !== undefined)
			{
				_resources.fields['assetTypePopup'].getStore().loadData(_listXMLs["assetType"]);
				
				var tempSearch = IFDS.Xml.newDocument('List');
				var elementBlank = IFDS.Xml.addSingleNode(tempSearch ,'Element');
				IFDS.Xml.addSingleNode(elementBlank ,'code', '');
				IFDS.Xml.addSingleNode(elementBlank ,'value', '');
				
				_listXMLs['assetTypeSearch'] = tempSearch;
				IFDS.Xml.appendNode(_listXMLs['assetTypeSearch'], IFDS.Xml.cloneDocument(_listXMLs['assetType']));
				
				_resources.fields['assetTypeSrch'].getStore().loadData(_listXMLs["assetTypeSearch"]);
			}
			_self.disableAllAssetType();
			
		}
		
		, setDefaultSearch: function()
		{
			if (_vars['holdingEntityCode'] != _self.BLANK)
				setDefaultHoldingCompanySearch();

			_resources.fields['optSelectAsOfDate'].setValue(true);
			_resources.fields['optSelectAll'].setValue(false);
			_resources.fields['asOfDate'].setValue(_vars['EffectiveDate']);	
		}
		
		, openActionPopup: function(popupName, action)
		{
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();
			this.populateAdditionalAsset(action);
			
		}
		, deleteSelectedRecord: function()
		{		
			var tempRecord = _resources.grids['grdAdditionalAsset'].getSelectedRecord();
			var index  = _resources.grids['grdAdditionalAsset'].store.indexOf(tempRecord)
			
			var hasChanged  = false;
					
			if (tempRecord.data['runMode'] == _self.ADD)
			{
				_resources.grids['grdAdditionalAsset'].removeSelectedRecord();
			}
			else
			{
				tempRecord.data['runMode'] = _self.DEL;
				tempRecord.commit();
				
				_resources.grids['grdAdditionalAsset'].store.filterBy(function(record) {
					return record.data.runMode != _self.DEL;
				});
			}
			
			_self.refreshGrdAdditionalAsset(index - 1 <= 0 ? 0 : index - 1);
			
			this.updatesFlag = (getUpdatedRecordCount() > 0);
			_self.enableButtons();
		}
		, clearHoldingCompany: function()
		{
		    if (_vars['holdingEntityCode'] != '')
			{
				_vars['holdingEntityCode'] = '';
				_vars['holdingEntityDesc'] = '';
				_vars['holdingEntityValue'] = '';
			}
		}
		
		, setHoldingCompany: function(code, desc, value)
		{
			_vars['holdingEntityCode'] = code.trim() ; 
			_vars['holdingEntityDesc'] = desc.trim(); 
			_vars['holdingEntityValue'] = value.trim(); 
		}
		
		,doValidateSearch: function()
		{
			var isSuccess = true;
			/* Search Button */
			if (_resources.fields['holdingCompanySrch'].getValue() == _self.BLANK)
			{
				_resources.fields['holdingCompanySrch'].markInvalid(_translationMap['Error_HoldingCompanyRequire']);
				isSuccess = false;
			}
			
			/* All and AsOfDate */
			if (_resources.fields['optSelectAsOfDate'].checked && _resources.fields['asOfDate'].getValue() == _self.BLANK)
			{
				_resources.fields['asOfDate'].markInvalid(_translationMap['Error_EffectiveDateRequire']);
				isSuccess = false;
			}
			return isSuccess;
		}
		
		, doSearch: function(more)
		{		 
			if (_resources.fields['holdingCompanySrch'].getValue() == _self.BLANK)
				_resources.fields['holdingCompanySrch'].markInvalid(_translationMap['Error_HoldingCompanyRequire']);
			else
			{
				if (_self.updatesFlag && !more)
				{
					DesktopWeb.Util.displayDiscardPrompt(callback)
				}
				else
				{
					callback(true);
				}
				
				function callback(discard)
				{
					if (discard)
					{
						DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, 
							getReloadRequest(more), responseHandler, 
							_translationMap['ProcMsg_Searching']);

						function responseHandler(success, responseXML)
						{
							if (! more)
								_self.updatesFlag  = false;
							
							if (success)
							{
								loadAdditionAsset(responseXML, more);
								_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
								_self.refreshGrdAdditionalAsset(0);						
								_self.enableMoreButton(_nextStartRecNum);

								if (_vars['holdingEntityCode'] === _self.BLANK)
								{
									storeHoldingEntityValues(responseXML);
								}
							}
							else
							{
								_self.clearGrdAdditionalAsset();
								
								if (!_vars['fromHoldingScreen'] )
									setHoldingEntityValues();
							}
						}
					}
				}
			}
		}

		, doUpdate: function (mode)
		{		
			var updateStatus = null;

			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest(mode), responseHandler, _translationMap['ProcMsg_Saving']);

			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;					
				}
				else
				{
					updateStatus = DesktopWeb._FAIL 
					storeContextErrors(contextErrors);
				}
			}
			return updateStatus;
		}
		
		,doValidateCommitScreen : function()
		{			
			if (_self.doUpdate('validate') == DesktopWeb._SUCCESS)
				DesktopWeb.Util.commitScreen();
		}
		
		, forcebuildUpdateXML : function()
		{
			getUpdateRequest();
		}
		

		//Call when press ok on popup screen
		, doValidatePopUpScreen: function (action, data)
		{
			var gridIndex = "";
			var obj = null;
			var success = true;
			
			if (data['effectiveDate'] == undefined)
			{
				success = false;
				_resources.fields['effectiveDate'].markInvalid(_translationMap['FldRequired']);
			}
			if ((data['stopDate'] == undefined ))
			{
				success = false;
				_resources.fields['stopDate'].markInvalid(_translationMap['FldRequired']);
			}
			
			if (data['effectiveDate'] > data['stopDate'])
			{
				success = false;
				_resources.fields['effectiveDate'].markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
			}

			data['effectiveDate'] = _resources.fields['effectiveDate'].getDisplayDateString();
			data['stopDate']      = _resources.fields['stopDate'].getDisplayDateString();
			
			if (success)
			{
				if (action == _self.ADD)
				{
					success = checkRequireField(data);
					if (success)
					{
						data['runMode'] = this.ADD;
						data['feeAggrID'] = this.NEW + _additionCounter++;
						data['gridIndex'] = data['feeAggrID'];
						data['version'] = 0;

						
						_resources.grids['grdAdditionalAsset'].addRecord(data);
						_resources.grids['grdAdditionalAsset'].selectLastRecord();
					}
				}
				else 
				{
					// Case mod/ delete the new record
					var tempRecord = _resources.grids['grdAdditionalAsset'].getSelectedRecord();
					var hasChanged  = false;
					
					if (tempRecord.data['runMode'] == _self.ADD)
					{
						if (action == this.DEL)
						{
							_resources.grids['grdAdditionalAsset'].removeSelectedRecord();
						}
						else
						{
							success = checkRequireField(data);
							
							if (success)
							{
								data['runMode'] = this.ADD;	
								for (var i in tempRecord.data)
								{
									if (tempRecord.data[i] !== data[i] && data[i]  != undefined)
									{
										tempRecord.data[i] = data[i];
									}
								}

								tempRecord.commit(); 
							}
						}	
					}
					else
					{
						//Mod mode
						for (var i in tempRecord.data)
						{
							if (tempRecord.data[i] !== data[i] && data[i]  != undefined)
							{
								if (i == 'effectiveDate' || i === 'stopDate' || i === 'runMode')
									tempRecord.data[i] = data[i];
								hasChanged  = true;
							}
						}	
						if (hasChanged)
						{
							tempRecord.data['errMsg'] = "";
							tempRecord.commit(); 
						}
					}
				}
			}
			
			this.updatesFlag  = (getUpdatedRecordCount() > 0);
			if (success) 
				_self.enableButtons();
				
			return success;
		}	

		, enablePermButtons: function ()
		{
			(_permissionsMap['add']) 
				? _resources.grids['grdAdditionalAsset'].enableButton(_CADD) 
				: _resources.grids['grdAdditionalAsset'].disableButton(_CADD);
			_resources.grids['grdAdditionalAsset'].disableButton(_CMOD); 
			_resources.grids['grdAdditionalAsset'].disableButton(_CDEL); 
			_resources.grids['grdAdditionalAsset'].disableButton(_CSUBADVISED); 
			_resources.grids['grdAdditionalAsset'].disableButton(_CADMIN); 
			
			_resources.grids['grdAdditionalAsset'].disableButton(_CHISTORY); 
		}
		
		,enableButtons : function()
		{		  
			var selectedRecord = this.getSelectedAdditionalAsset();
			
			if (selectedRecord)
			{
				(selectedRecord.assetTypeCode == _self.SUBADV) ? 
					_resources.grids['grdAdditionalAsset'].enableButton(_CSUBADVISED) :
					_resources.grids['grdAdditionalAsset'].disableButton(_CSUBADVISED);
					
				if (selectedRecord.runMode == _self.ADD)
				{
					_resources.grids['grdAdditionalAsset'].disableButton(_CADMIN); 
					_resources.grids['grdAdditionalAsset'].disableButton(_CHISTORY); 
				}
				else
				{
					_resources.grids['grdAdditionalAsset'].enableButton(_CADMIN); 
					_resources.grids['grdAdditionalAsset'].enableButton(_CHISTORY); 
				}
				
				
				(_permissionsMap['mod']) ? 
				_resources.grids['grdAdditionalAsset'].enableButton(_CMOD) 
				: _resources.grids['grdAdditionalAsset'].disableButton(_CMOD); 
				
				(_permissionsMap['del']) ? 
				_resources.grids['grdAdditionalAsset'].enableButton(_CDEL)
				: _resources.grids['grdAdditionalAsset'].disableButton(_CDEL); 
			}	
			else
				this.enablePermButtons();
		}

		, enableMoreButton: function (moreRec)
		{		
			(moreRec) 
				? _resources.grids['grdAdditionalAsset'].enableButton(_CMORE) 
				: _resources.grids['grdAdditionalAsset'].disableButton(_CMORE);
		}
		
		, disableMoreButton: function (moreRec)
		{	
			_nextStartRecNum = 1;
			_resources.grids['grdAdditionalAsset'].disableButton(_CMORE);
		}
		
		, refreshGrdAdditionalAsset: function (index)
		{
			_resources.grids['grdAdditionalAsset'].setSelectedRecord(index);
		}

		, getSelectedAdditionalAsset: function()
		{
		    var record = _resources.grids['grdAdditionalAsset'].getSelectedRecord();
			if (record) 
			{				
				return {
					node : record,
					feeAggrID : record.data['feeAggrID'],
					holdingEntityCode : record.data[ 'holdingEntityCode'],
					holdingEntityDesc : record.data[ 'holdingEntityDesc'],
					identifier : record.data[ 'identifier'],
					identifier2 : record.data[ 'identifier2'],
					name : record.data[ 'name'],
					name2 : record.data[ 'name2'],
					assetTypeCode : record.data[ 'assetTypeCode'],
					assetTypeDesc : record.data[ 'assetTypeDesc'],
					effectiveDate : record.data[ 'effectiveDate'],
					stopDate : record.data[ 'stopDate'],
					runMode : record.data[ 'runMode'],
					gridIndex : record.data[ 'gridIndex'],
					createDate : record.data[ 'processdate'],
					createUser: record.data[ 'userName'],
					modifyDate : record.data[ 'modDate'],
					modifyUser : record.data[ 'modUser']
				};
			} 
			else
				return null;

		}

		, setSelectedAdditionalAsset: function(gridIndex)
		{	
			_self.enablePermButtons();
			_self.enableButtons();
		}
		
		, populateAdditionalAsset: function(action)
		{		
			_self.clearAllAssetType();

			if (action == _self.ADD)
			{
				setDefaultHoldingCompanyPopup(null);
				
				_resources.fields['effectiveDate'].setValue(_vars['EffectiveDate']);
				_resources.fields['stopDate'].setValue(_vars['StopDate']);
				_resources.fields['assetTypePopup'].setValue(_resources.fields['assetTypePopup'].store.getAt(0).get('code'));
				_resources.fields['assetTypePopup'].selectedIndex  = 0;
				_resources.popups['frmAdditionalAsset'].syncSize();	
				_self.enableFields(action);				
			}
			else
			{
				var obj = this.getSelectedAdditionalAsset();

				if (obj)
				{
					setDefaultHoldingCompanyPopup(obj);
					
					_resources.fields['assetTypePopup'].setValue(obj.assetTypeCode);
					
					_resources.fields['effectiveDate'].setValue(obj.effectiveDate);
					_resources.fields['stopDate'].setValue(obj.stopDate);

					if (obj.assetTypeCode == _self.ACCOUNT)
						setDefaultAccountPopup(obj);
					else if (obj.assetTypeCode == _self.BROKER)
						setDefaultBrokerPopup(obj);
					else if (obj.assetTypeCode == _self.SALERESP)
						setDefaultSaleRespPopup(obj);
					
					else if (obj.assetTypeCode == _self.SUBADV)
					{
						_resources.fields['subAdvisedPopup'].setValue(obj.identifier);
						_resources.fields['subAdvisedPopup'].disableField();
					}	
					
					if (obj.runMode == _self.ADD)
						_self.enableFields(_self.ADD);
					else 
						_self.enableFields(action);
						
					setVisibleAllContentPopup(false, obj.assetTypeCode);
				}
			}
		}
		
		, enableFields: function(action)
		{	
			switch (action)
			{
				case _self.ADD:
				{
					if (!_vars['fromHoldingScreen'])
						 _resources.fields['holdingCompanyPopUp'].enableField();
					else 
						_resources.fields['holdingCompanyPopUp'].disableField();
					
					_resources.fields['assetTypePopup'].enableField();
					_resources.fields['effectiveDate'].enableField();
					_resources.fields['stopDate'].enableField();
					_self.populateAssetType(_resources.fields['assetTypePopup'].getValue());
					
					break;
				}
				case _self.MOD:
				{	
					_resources.fields['holdingCompanyPopUp'].disableField();
					_resources.fields['assetTypePopup'].disableField();
					_resources.fields['effectiveDate'].enableField();
					_resources.fields['stopDate'].enableField();
					this.disableAllAssetType();
					break;
				}
				otherwise:
				{
					_resources.fields['holdingCompanyPopUp'].disableField();
					_resources.fields['assetTypePopup'].disableField();
					_resources.fields['effectiveDate'].disableField();
					_resources.fields['stopDate'].disableField();
					this.disableAllAssetType();
					break;
				}
			}	
		}
				
		, doSrchCheck: function ()
		{
			if (_resources.fields['optSelectAll'].getValue())
			{
				_resources.fields['asOfDate'].disableField();
				_resources.fields['asOfDate'].clearInvalid();
			}
			else
			{
				_resources.fields['asOfDate'].enableField();
			}
			
			this.disableMoreButton();
		}

		, enableSearch: function()
		{			
			this.disableMoreButton();
		
			
			if ( _resources.fields['holdingCompanySrch'].selectedRecord == null &&
				(_resources.fields['holdingCompanySrch'].getValue() == _self.BLANK ||
				_resources.fields['holdingCompanySrch'].getRawValue() == _self.BLANK))
			{
				_resources.buttons['cmdSearch'].disable();	
				this.clearHoldingCompany();
			}
			else if (_permissionsMap['inq']) 
			{
				_resources.buttons['cmdSearch'].enable();
				setHoldingEntityValues();
			}		
		}
		

		, clearGrdAdditionalAsset: function()
		{
			_resources.grids['grdAdditionalAsset'].clearData();
			_self.enablePermButtons();	
		}
		
		//Popup screen
		, disableAllAssetType : function()
		{
			_resources.fields['accountPopup'].disableField();
			_resources.fields['brokerPopup'].disableField();
			_resources.fields['saleRespPopup'].disableField();
			_resources.fields['subAdvisedPopup'].disableField();

		}
		, clearAllAssetType : function()
		{		
			_resources.fields['accountPopup'].reset();
			_resources.fields['brokerPopup'].reset();
			_resources.fields['saleRespPopup'].reset();
			_resources.fields['subAdvisedPopup'].reset();
			
			
			_resources.fields['accountPopup'].setRawValue('');
			_resources.fields['brokerPopup'].setRawValue('');
			_resources.fields['saleRespPopup'].setRawValue('');
			_resources.fields['subAdvisedPopup'].setRawValue('');

			var accountValue = _resources.fields['accountPopup'].getRawValue();
			if (typeof accountValue === 'undefined' || accountValue === null || accountValue === '')
				_resources.fields['accountPopup'].clearValue();
				
			var brokerValue = _resources.fields['brokerPopup'].getRawValue();        
			if (typeof brokerValue === 'undefined' || brokerValue === null || brokerValue === '')
				_resources.fields['brokerPopup'].clearValue();

			var saleRespValue = _resources.fields['saleRespPopup'].getRawValue();        
			if (typeof saleRespValue === 'undefined' || saleRespValue === null || saleRespValue === '')
				_resources.fields['saleRespPopup'].clearValue();
				
			var subAdvisedValue = _resources.fields['subAdvisedPopup'].getRawValue();        
			if (typeof subAdvisedValue === 'undefined' || subAdvisedValue === null || subAdvisedValue === '')
				_resources.fields['subAdvisedPopup'].clearValue();

		}
		
		, enableSaleRepAllowed : function()
		{
			return _resources.fields['assetTypePopup'].getValue() == _self.SALERESP ?
				true : false;
		}
		
		, populateAssetType : function(assetType)
		{			
			if (assetType == _self.ACCOUNT)
			{
				_resources.fields['accountPopup'].enableField();
				_resources.fields['brokerPopup'].disableField();
				_resources.fields['saleRespPopup'].disableField();
				_resources.fields['subAdvisedPopup'].disableField();
			}
			else if (assetType == _self.BROKER)
			{
				_resources.fields['accountPopup'].disableField();
				_resources.fields['brokerPopup'].enableField();
				_resources.fields['saleRespPopup'].disableField();
				_resources.fields['subAdvisedPopup'].disableField();
			}
			else if (assetType == _self.SALERESP)
			{
				_resources.fields['accountPopup'].disableField();
				_resources.fields['brokerPopup'].enableField();
				_resources.fields['saleRespPopup'].enableField();
				_resources.fields['subAdvisedPopup'].disableField();
			}
			else if (assetType == _self.SUBADV)
			{
				_resources.fields['accountPopup'].disableField();
				_resources.fields['brokerPopup'].disableField();
				_resources.fields['saleRespPopup'].disableField();
				_resources.fields['subAdvisedPopup'].enableField();
			}
			else
			{
				_resources.fields['accountPopup'].disableField();
				_resources.fields['brokerPopup'].disableField();
				_resources.fields['saleRespPopup'].disableField();
				_resources.fields['subAdvisedPopup'].disableField();
			}
			
			setVisibleAllContentPopup(false, assetType);
		}
		
		/*SubAdvise Screen*/
		,openSubAdvisePopup: function()
		{			
			var titleName = _translationMap['AdditionalAsset']+ ' - ' +_translationMap['SubAdvised'];
			_resources.popups['subAdviseWindow'].init(titleName);
			_resources.popups['subAdviseWindow'].show();
		}
		
		,doValidateSubAdviseSearch: function()
		{
			var isSuccess = true;
			var startDate = _resources.fields['subAdviseStartDate'].getValue();
			var endDate = _resources.fields['subAdviseStopDate'].getValue();
			
			/* Search Button */				
			isSuccess = _resources.fields['subAdviseStartDate'].isValid() && isSuccess ;
			isSuccess = _resources.fields['subAdviseStopDate'].isValid() && isSuccess ;
			
			if (isSuccess && (new Date(startDate) > new Date(endDate)))
			{
				isSuccess = false;
				_resources.fields['subAdviseStartDate'].markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
			}		
			
			return isSuccess;
		}
		
		, doSubAdviseSearch : function(state)
		{
			DesktopWeb.Ajax.doSmartviewAjax(_subAdviseInit, state ? null : {ignoreErrorCode: '15'}
				, getSubAdviseRequest(state), responseHandler
				, _translationMap['ProcMsg_Searching']);

			function responseHandler(success, responseXML)
			{
				setInitSubAdvise(responseXML);
				if (success)
				{
					loadSubAdvise(responseXML);
					_resources.grids['grdSubAdvise'].setSelectedRecord(0);
				}
				else
				{					
					_self.clearSubAdvisedGrid();
				}
			}
			
		}
		
		, clearSubAdvisedGrid: function()
		{
			_resources.grids['grdSubAdvise'].clearData();
		}
		
		
		/*History popup screen*/
		,openHistoryPopup: function()
		{
			var viewParam = {};
			var historyName = null;
			
			viewParam['auditType'] = 'FeeAggregation';
			viewParam['searchValue1'] = this.getSelectedAdditionalAsset().feeAggrID;
			historyName = _translationMap['AdditionalAsset'] + ' - ' +_translationMap['History'];
			
			_resources.popups['history'].init(historyName, _historyService, viewParam, true);
			_resources.popups['history'].show();
			
		}
		
		/*Admin popup screen*/
		,openAdminPopup: function()
		{
			var title = null;
			var xml = null;
			
			title = _translationMap['AdditionalAsset']+ ' - ' +_translationMap['Admin']
			xml = this.getSelectedAdditionalAsset();
			if (xml != null || xml != undefined)
			{
				var adminData = {};
				adminData['createUser'] = xml.createUser;
				adminData['createDate'] = xml.createDate;
				adminData['modifyUser'] = xml.modifyUser;
				adminData['modifyDate'] = xml.modifyDate;
				
				_resources.popups['admin'].init(title, adminData);
				_resources.popups['admin'].show();
			}
		}
	}
}