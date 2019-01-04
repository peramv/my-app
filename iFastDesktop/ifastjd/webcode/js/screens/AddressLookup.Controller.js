/*********************************************************************************************
 * @file	AddressLookup.Controller.js	
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Address Lookup screen
 *********************************************************************************************
 * Purpose  : Lookup an address by postal code
 *             
 * Notes    : Account Details Information --> Attributes --> Address/Mailing Assignments --> Shareholder/Entity
 *
 * History  :  
 *		06 Jun 2014 N. Suanlamyai P0231196 - CCS - Postal Code Look-up Enhancement T55248
 *					- Created
 *
 *		19 Sep 2014 N. Suanlamyai P0231196 DFT0041009 T55746
 *					- Fixed caution label is not displayed on Windows 7.
 *
 *		06 Jan 2015 N. Suanlamyai P0231196 DFT0045157 T80120
 *					- Fixed Unit Number is not populating on Address/Mailing Assignment screen.
 *
 *********************************************************************************************/
 
DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    var _lookupService = 'dtPCLookupReload';
	
	var _POBox = 'POBox';
	var _Civic = 'Civic';
	var _General = 'General';
	var _RuralRoute = 'RuralRoute';
	var _StRoute = 'StRoute';
	
	var _currentSearchCriteria	= new Array();
	var _permissionsMap	= new Array();
	var _configurationMap = new Array();
	
	// PRIVATE METHODS ****************************************
	function storePermission(initViewXML)
	{
		/**
		 * Current SmartView Program has not sent Permissions element.
		 * User is able to do a search if Lookup button is enabled.
		 **/
		// _permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == _self.YES;
	}
	
	function loadDefaultSearchCriteria(postalCode)
	{
		_resources.fields['pstlCodeFld'].setValue(postalCode);
	}
	
	function loadConfigurations(initViewXML)
	{
		/**
		 * Current SmartView Program has not sent screen configuration element.
		 **/
	}
	
	function loadAvailableAddressType(searchResultXML)
	{
		
		resetAddrTypeField();
		
		var addrTypeXML = IFDS.Xml.newDocument('AddressType');
		
		var addrTypeNodes = IFDS.Xml.getNodes(searchResultXML, '//PCLookupDetails/*');
		Ext.each(addrTypeNodes, function(addrTypeNode){
			if ( addrTypeNode.nodeName == _POBox
				|| addrTypeNode.nodeName == _Civic
				|| addrTypeNode.nodeName == _General
				|| addrTypeNode.nodeName == _RuralRoute
				|| addrTypeNode.nodeName == _StRoute)
			{
				addAddressType(addrTypeNode.nodeName);
			}
		});
		
		_resources.fields['addrTypeFld'].loadData(addrTypeXML);
		
		var store = _resources.fields['addrTypeFld'].getStore();
		if (store.getTotalCount() > 1) _resources.fields['addrTypeFld'].enableField();
		store.sort('value', 'ASC');
		
		function addAddressType(addrType)
		{
			var elementXML = IFDS.Xml.addSingleNode(addrTypeXML, 'Element');
			IFDS.Xml.addSingleNode(elementXML, 'code', addrType);
			IFDS.Xml.addSingleNode(elementXML, 'value', _translationMap[addrType]);
		}
	}
	
	function loadSearchResult(responseXML)
	{
		var resultNode = IFDS.Xml.getNode(responseXML, '//PCLookupDetails');
		var pstlCode = IFDS.Xml.getNodeValue(resultNode, 'pstlCode');
		var province = IFDS.Xml.getNodeValue(resultNode, 'prov');
		var cntryCode = IFDS.Xml.getNodeValue(resultNode, 'cntryCode');
		
		var addrNodesByType = IFDS.Xml.getNodes(responseXML, '//PCLookupDetails/*');
		var gridName = null;
		Ext.each(addrNodesByType, function(addrNode){
			gridName = addrNode.nodeName + 'Grid';
			if (_resources.grids[gridName])
			{
				_resources.grids[gridName].pstlCode = pstlCode;
				_resources.grids[gridName].province = province;
				_resources.grids[gridName].cntryCode = cntryCode;
				_resources.grids[gridName].loadData(addrNode);
			}
		});
	}
	
	function displaySearchResultByAddressType(addrType)
	{
		//alert('displaySearchResultByAddressType: ' + addrType);
		if (Ext.isEmpty(addrType)) return;
		
		_resources.grids['POBoxGrid'].hide();
		_resources.grids['CivicGrid'].hide();
		_resources.grids['GeneralGrid'].hide();
		_resources.grids['RuralRouteGrid'].hide();
		_resources.grids['StRouteGrid'].hide();
		
		_resources.grids[addrType + 'Grid'].show();
		_resources.grids[addrType + 'Grid'].selectFirstRecord();
	}
	
	function doSearch()
	{
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'pstlCode', _currentSearchCriteria['pstlCode']);
		
		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_lookupService, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{
			//prompt("responseXML", IFDS.Xml.serialize(responseXML));
            // hanldle response
			if (success){
				
				loadAvailableAddressType(responseXML);
				
				loadSearchResult(responseXML);
				
				if (_resources.fields['addrTypeFld'].getStore().getTotalCount() > 0)
				{
					var store = _resources.fields['addrTypeFld'].getStore();
					var firstAddrType = store.getAt(0).get('code');
					
					_resources.fields['addrTypeFld'].setValue(firstAddrType);
					
					displaySearchResultByAddressType(_resources.fields['addrTypeFld'].getValue());
				}
			}
		}
	}
	
	function resetAddrInfo()
	{
		_resources.fields['addr1Fld'].reset();
		_resources.fields['addr2Fld'].reset();
		_resources.fields['addr3Fld'].reset();
		_resources.fields['cityFld'].reset();
		_resources.fields['provinceFld'].reset();
		_resources.fields['cntryCodeFld'].reset();
	}
	
	function loadAddrInfo(addrType, record)
	{
		var addr1 = '';
		switch (addrType)
		{
			case _POBox:
			{
				addr1 = buildAddressLine1( [_translationMap['POBox'], "", record.get('delArea'), record.get('routeInfo')] );
				break;
			}
			case _Civic:
			{
				addr1 = buildAddressLine1( [record.get('stName')] );
				break;
			}
			case _General:
			{
				addr1 = buildAddressLine1( [record.get('delArea'), record.get('delInstall')] );
				break;
			}
			case _RuralRoute:
			{
				addr1 = buildAddressLine1( [record.get('delArea'), record.get('routeInfo')] );
				break;
			}
			case _StRoute:
			{
				addr1 = buildAddressLine1( ["", "", record.get('stName'), record.get('routeInfo')] );
				break;
			}
		}
		resetAddrInfo();
		_resources.fields['addr1Fld'].setValue(addr1);
		_resources.fields['addr2Fld'].setValue('');
		_resources.fields['addr3Fld'].setValue('');
		_resources.fields['cityFld'].setValue(record.get('city'));
		_resources.fields['provinceFld'].setValue(_resources.grids[addrType + 'Grid'].province);
		_resources.fields['cntryCodeFld'].setValue(_resources.grids[addrType + 'Grid'].cntryCode);
	}
	
	function updateAddrInfo(addrType, addAddr)
	{
		switch (addrType)
		{
			case _POBox:
			{
				var selectedRecord = _resources.grids['POBoxGrid'].getSelectedRecord();
				var addr1 = buildAddressLine1( [_translationMap['POBox']
												, addAddr['POBox']
												, selectedRecord.get('delArea')
												, selectedRecord.get('routeInfo')] );
				_resources.fields['addr1Fld'].setValue(addr1);
				break;
			}
			
			case _Civic:
			{
				var selectedRecord = _resources.grids['CivicGrid'].getSelectedRecord();
				var addr1 = '';
				if ( Ext.isEmpty(addAddr['unitNum']) && Ext.isEmpty(addAddr['unitDesc']) )
				{
					addr1 = buildAddressLine1( [addAddr['stNum']
												, addAddr['suffix']
												, selectedRecord.get('stName')] );
				}
				else if ( !Ext.isEmpty(addAddr['unitNum']) && Ext.isEmpty(addAddr['unitDesc']) ) 
				{
					addr1 = buildAddressLine1( [addAddr['unitNum'] + "-" + addAddr['stNum']
												, addAddr['suffix']
												, selectedRecord.get('stName')] );
				}
				else
				{
					addr1 = buildAddressLine1( [addAddr['stNum']
												, addAddr['suffix']
												, selectedRecord.get('stName')
												, addAddr['unitDesc']
												, addAddr['unitNum']] );
				}
				
				_resources.fields['addr1Fld'].setValue(addr1);
				
				break;
			}
			
			case _General: break;
			
			case _RuralRoute: break;
			
			case _StRoute: 
			{
				var selectedRecord = _resources.grids['StRouteGrid'].getSelectedRecord();
				var addr1 = '';
				var stName = (selectedRecord)?selectedRecord.get('stName'):"";
				var routeInfo = (selectedRecord)?selectedRecord.get('routeInfo'):"";
				addr1 = buildAddressLine1( [addAddr['stNum'], addAddr['suffix'], stName, routeInfo] );
				_resources.fields['addr1Fld'].setValue(addr1);
				break;
			}
		}
	}
	
	function buildAddressLine1( itemArray )
	{
		var addressLine = "";
		for ( var i = 0; i < itemArray.length; i++ )
		{
			addressLine += itemArray[i];
			if ( i < itemArray.length - 1 )
			{
				addressLine += " ";
			}
		}
		return addressLine;
	}

	function resetAddrTypeField()
	{
		_resources.fields['addrTypeFld'].reset();
		_resources.fields['addrTypeFld'].disableField();
	}
	
	function resetAllAddAddrInfoFields()
	{
		_resources.fields['stNumFld'].reset();
		_resources.fields['suffixFld'].reset();
		_resources.fields['unitNumFld'].reset();
		_resources.fields['unitDescFld'].reset();
		_resources.fields['POBoxFld'].reset();
		_resources.fields['cautionLabel'].setValue('');
		_resources.fields['stNumFld'].allowBlank = true;
		_resources.fields['unitNumFld'].allowBlank = true;
		_resources.fields['POBoxFld'].allowBlank = true;
		_resources.fields['stNumFld'].oddeven = '';
		_resources.fields['stNumFld'].setFieldLabel(_translationMap['StreetNumber'] + ':');
		_resources.fields['stNumFld'].disableField();
		_resources.fields['suffixFld'].disableField();
		_resources.fields['unitNumFld'].disableField();
		_resources.fields['unitDescFld'].disableField();
		_resources.fields['POBoxFld'].disableField();
		_resources.fields['cautionLabel'].hide();
	}
	
	function updateAddAddrInfoFields(addrType, record)
	{
		resetAllAddAddrInfoFields();
		switch (addrType)
		{
			case _POBox:
			{
				_resources.fields['POBoxFld'].allowBlank = false;
				if ( !Ext.isEmpty(record.get('pobFrom')) ) _resources.fields['POBoxFld'].setMinValue(record.get('pobFrom'));
				if ( !Ext.isEmpty(record.get('pobTo')) ) _resources.fields['POBoxFld'].setMaxValue(record.get('pobTo'));
				if ( record.get('pobFrom') == record.get('pobTo') ) _resources.fields['POBoxFld'].setValue(record.get('pobFrom'));
				_resources.fields['POBoxFld'].enableField();
				break;
			}
			case _Civic:
			{
				//street number
				_resources.fields['stNumFld'].allowBlank = false;
				_resources.fields['stNumFld'].oddeven = record.get('oddeven');
				
				if (!Ext.isEmpty(record.get('oddeven')))
				{
					if (record.get('oddeven').toLowerCase() == 'odd')
					{
						_resources.fields['stNumFld'].setFieldLabel(_translationMap['StreetNumber'] + ':*');
						_resources.fields['cautionLabel'].setValue(_translationMap['NOTE_ONLYODD']);
						_resources.fields['cautionLabel'].show();
					}else if (record.get('oddeven').toLowerCase() == 'even')
					{
						_resources.fields['stNumFld'].setFieldLabel(_translationMap['StreetNumber'] + ':**');
						_resources.fields['cautionLabel'].setValue(_translationMap['NOTE_ONLYEVEN']);
						_resources.fields['cautionLabel'].show();
					}
				}
				if ( !Ext.isEmpty(record.get('stFrom')) ) _resources.fields['stNumFld'].setMinValue(record.get('stFrom'));
				if ( !Ext.isEmpty(record.get('stTo')) ) _resources.fields['stNumFld'].setMaxValue(record.get('stTo'));
				if ( record.get('stFrom') == record.get('stTo') ){
					_resources.fields['stNumFld'].setValue(record.get('stFrom'));
				}
				_resources.fields['stNumFld'].enableField();
				//suffix
				_resources.fields['suffixFld'].enableField();
				//unit number
				if ( !Ext.isEmpty(record.get('unitFrom')) ) _resources.fields['unitNumFld'].allowBlank = false;
				if ( !Ext.isEmpty(record.get('unitFrom')) ) _resources.fields['unitNumFld'].setMinValue(record.get('unitFrom'));
				if ( !Ext.isEmpty(record.get('unitTo')) ) _resources.fields['unitNumFld'].setMaxValue(record.get('unitTo'));
				if ( record.get('unitFrom') == record.get('unitTo') ) _resources.fields['unitNumFld'].setValue(record.get('unitFrom'));
				_resources.fields['unitNumFld'].enableField();
				//unit desc
				_resources.fields['unitDescFld'].enableField();
				break;
			}
			case _General: break;
			case _RuralRoute: break;
			case _StRoute:
			{
				//street number
				_resources.fields['stNumFld'].allowBlank = false;
				_resources.fields['stNumFld'].oddeven = record.get('oddeven');
				
				if (!Ext.isEmpty(record.get('oddeven')))
				{
					if (record.get('oddeven').toLowerCase() == 'odd')
					{
						_resources.fields['stNumFld'].setFieldLabel(_translationMap['StreetNumber'] + ':*');
						_resources.fields['cautionLabel'].setValue(_translationMap['NOTE_ONLYODD']);
						_resources.fields['cautionLabel'].show();
					}else if (record.get('oddeven').toLowerCase() == 'even')
					{
						_resources.fields['stNumFld'].setFieldLabel(_translationMap['StreetNumber'] + ':**');
						_resources.fields['cautionLabel'].setValue(_translationMap['NOTE_ONLYEVEN']);
						_resources.fields['cautionLabel'].show();
					}
				}
				
				if ( !Ext.isEmpty(record.get('stFrom')) ) _resources.fields['stNumFld'].setMinValue(record.get('stFrom'));
				if ( !Ext.isEmpty(record.get('stTo')) ) _resources.fields['stNumFld'].setMaxValue(record.get('stTo'));
				if ( record.get('stFrom') == record.get('stTo') )
				{
					_resources.fields['stNumFld'].setValue(record.get('stFrom'));
				}
				_resources.fields['stNumFld'].enableField();
				//suffix
				_resources.fields['suffixFld'].enableField();
				break;
			}
		}
		updateAddrInfo(addrType, getAddAddrInfo());
	}
	
	function getAddAddrInfo()
	{
		var addAddrInfo = {};
		addAddrInfo['stNum'] = _resources.fields['stNumFld'].getValue();
		addAddrInfo['suffix'] = _resources.fields['suffixFld'].getValue().toUpperCase();
		addAddrInfo['unitNum'] = _resources.fields['unitNumFld'].getValue();
		addAddrInfo['unitDesc'] = _resources.fields['unitDescFld'].getValue().toUpperCase();
		addAddrInfo['POBox'] = _resources.fields['POBoxFld'].getValue();
		return addAddrInfo;
	}
	
	function clearAllGrids()
	{
		clearGrid('POBoxGrid');
		clearGrid('CivicGrid');
		clearGrid('GeneralGrid');
		clearGrid('RuralRouteGrid');
		clearGrid('StRouteGrid');
	}
	
	function clearGrid(name)
	{
		_resources.grids[name].pstlCode = null;
		_resources.grids[name].province = null;
		_resources.grids[name].cntryCode = null;
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function isOdd(val)
	{
		if (!Ext.isNumber(val)) return false;
		return (val % 2 == 1);
	}
	
	function isEven(val)
	{
		if (!Ext.isNumber(val)) return false;
		return (val % 2 == 0);
	}

	function disableScreen()
	{
	}

	// PUBLIC ITEMS *************************************
	return {
		
        updatesFlag: false
		,salesRepByBranch: true
		,YES: 'yes'
		,NO: 'no'

		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;			
			
			resetAddrTypeField();
			resetAllAddAddrInfoFields();

			var pstlCodeParam = DesktopWeb._SCREEN_PARAM_MAP['pstlCode'];
			
			if (!Ext.isEmpty(pstlCodeParam))
			{
				// do pre-search
				loadDefaultSearchCriteria(pstlCodeParam);
				_currentSearchCriteria['pstlCode'] = pstlCodeParam;
				doSearch(); 
			}
		}

		,searchIsValid: function()
		{
			// Clear all invalid
			_resources.fields['pstlCodeFld'].clearInvalid();
			
			// Validate Search Criteria
			var isValid = true;
			isValid = _resources.fields['pstlCodeFld'].isValid();

			return isValid;
		}
		
		,doSearch: function()
		{
			clearAllGrids();
			resetAddrInfo();
			resetAddrTypeField();
			resetAllAddAddrInfoFields();
			
			// Store search criteria; they would be used for more button
			_currentSearchCriteria['pstlCode'] = _resources.fields['pstlCodeFld'].getValue();

			// Call doSearch
			doSearch();
		}
		
		,selectHandler_AddressTypeFld: function(addrType)
		{
			//resetAddrInfo();
			//resetAllAddAddrInfoFields();
			displaySearchResultByAddressType(addrType);
		}
		
		,selectHandle_POBoxGrid: function(record)
		{	
			loadAddrInfo(_POBox, record);
			updateAddAddrInfoFields(_POBox, record);
		}

		,selectHandle_CivicGrid: function(record)
		{	
			loadAddrInfo(_Civic, record);
			updateAddAddrInfoFields(_Civic, record);
		}

		,selectHandle_GeneralGrid: function(record)
		{	
			loadAddrInfo(_General, record);
			updateAddAddrInfoFields(_General, record);
		}

		,selectHandle_RuralRouteGrid: function(record)
		{	
			loadAddrInfo(_RuralRoute, record);
			updateAddAddrInfoFields(_RuralRoute, record);
		}

		,selectHandle_StRouteGrid: function(record)
		{	
			loadAddrInfo(_StRoute, record);
			updateAddAddrInfoFields(_StRoute, record);
		}

		,changeHandle_stNumFld: function(fld, stNumVal)
		{
			var selectedAddrType = _resources.fields['addrTypeFld'].getValue();
			var errMsg = null;
			if (fld.oddeven.toLowerCase() == 'odd' && !isOdd(stNumVal))
			{
				errMsg = _translationMap['ERR_StNumOdd'];
			}else if (fld.oddeven.toLowerCase() == 'even' && !isEven(stNumVal)){
				errMsg = _translationMap['ERR_StNumEven'];
			}
			if (Ext.isEmpty(errMsg)){ 
				updateAddrInfo(selectedAddrType, getAddAddrInfo());
			}else{
				fld.markInvalid(errMsg);
			}
		}
		
		,changeHandle_suffixFld: function()
		{
			var selectedAddrType = _resources.fields['addrTypeFld'].getValue();
			updateAddrInfo(selectedAddrType, getAddAddrInfo());
		}
		
		,changeHandle_unitNumFld: function()
		{
			var selectedAddrType = _resources.fields['addrTypeFld'].getValue();
			updateAddrInfo(selectedAddrType, getAddAddrInfo());
		}
		
		,changeHandle_unitDescFld: function()
		{
			var selectedAddrType = _resources.fields['addrTypeFld'].getValue();
			updateAddrInfo(selectedAddrType, getAddAddrInfo());
		}
		
		,changeHandle_POBoxFld: function(fld, POBoxVal)
		{
			var selectedAddrType = _resources.fields['addrTypeFld'].getValue();
			updateAddrInfo(selectedAddrType, getAddAddrInfo());
		}
		
		,screenIsValid: function()
		{
			var isValid = true;
			var selectedAddrType = _resources.fields['addrTypeFld'].getValue();
			
			if (Ext.isEmpty(selectedAddrType))
			{
				DesktopWeb.Util.displayError(_translationMap['ERR_SelectAddr']);
				return false;
			}
			
			var selectedRecord = _resources.grids[selectedAddrType + 'Grid'].getSelectedRecord();
			if (!selectedRecord)
			{
				DesktopWeb.Util.displayError(_translationMap['ERR_SelectAddr']);
				return false;
			}
			
			isValid = _resources.fields['stNumFld'].isValid() && isValid;
			isValid = _resources.fields['suffixFld'].isValid() && isValid;
			isValid = _resources.fields['unitNumFld'].isValid() && isValid;
			isValid = _resources.fields['unitDescFld'].isValid() && isValid;
			isValid = _resources.fields['POBoxFld'].isValid() && isValid;
			
			return isValid;
		}

		,getResult: function()
		{
			var resultStr = "";
			resultStr += "AddrLine1=" + _resources.fields['addr1Fld'].getValue() + ";";		
			resultStr += "AddrLine2= ;";
			resultStr += "AddrLine3= ;";
			resultStr += "AddrLine4= ;";
			resultStr += "AddrLine5= ;";
			
			var selectedAddrType = _resources.fields['addrTypeFld'].getValue();
			var selectedGrid = _resources.grids[selectedAddrType + 'Grid'];
			var selectedRecord = (selectedGrid)?selectedGrid.getSelectedRecord():null;
			
			if (selectedGrid && selectedRecord)
			{
				resultStr += "CountryCode=" + selectedGrid.cntryCode + ";";
				resultStr += "City=" + selectedRecord.get('city') + ";";
				resultStr += "PostalCode=" + selectedGrid.pstlCode.toUpperCase() + ";";
				resultStr += "Province=" + selectedGrid.province + ";";
			}
			
			return resultStr;
		}
	}
}	