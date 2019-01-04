/*********************************************************************************************
 * @file	AcctTaxAlloc.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Account Holding Allocation by Tax Jurisdiction screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  09 Oct 2013 G. Thawornwachirakun P0193400 DFT0020328 T54301
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  16 Oct 2013 N. Suanlamyai P0193400 DFT0020392 T54325
 *					- Add band permission to the screen. 
 *
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'ADD'
	var _MOD = 'MOD'
	var _DEL = 'DEL';
	
	var _permissionsMap = {};

	var _nextStartRecNum = null;
	var _requestRecNum = 50;

	var _taxAllocXML = null;
	var _selectedTaxAlloc = null;
	var _initTaxAllocXML = null;
	
	var _runningAcctTaxAllocUUID = 0;
	
	var _taxAllocInitService = 'dtAcctTaxAllocInq';
	var _taxAllocReloadService = 'dtAcctTaxAllocInq';
	var _taxAllocUpdateService = 'dtAcctTaxAllocUpd';
	var _taxAllocValidateService = 'dtAcctTaxAllocVal';
	var _historyService = 'dtHistoricalInfo';
	
	// PRIVATE METHODS ****************************************	
	/** Store user permission **/
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function loadTaxAlloc(account, append, runMode)
	{
		var paramXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(paramXML, 'account', account);
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', (append)?_nextStartRecNum:'1');
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

		DesktopWeb.Ajax.doSmartviewAjax(_taxAllocInitService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{	
			if (success)
			{
				_taxAllocXML = responseXML;
				
				if (runMode == 'init')
				{	
					_initTaxAllocXML = IFDS.Xml.cloneDocument(_taxAllocXML);
					storePermissions(_initTaxAllocXML);
					updateTaxAllocButtons();
				}

			}else{	
				_taxAllocXML = null;
			}
			if(_taxAllocXML)
			{
				populateDropdownList();
				if (_permissionsMap[_self.INQ]){
					displayTaxAlloc(_taxAllocXML, append);
				}else{
					DesktopWeb.Util.displayError(_translationMap['Error_NoAuthoriseToView']);
				}
			}
		}		
	}
	
	function updateTaxAllocButtons()
	{
		var grid = _resources.grids['taxAllocGrid'];
		
		if (_permissionsMap[_self.ADD])
		{
			grid.enableButton('addBtn');
		}else{
			grid.disableButton('addBtn');
		}
		if (_selectedTaxAlloc)
		{
			if (_permissionsMap[_self.MOD] || _selectedTaxAlloc.get('runMode') == _ADD)
			{
				grid.enableButton('modBtn');
			}else{
				grid.disableButton('modBtn');
			}
			if (_permissionsMap[_self.DEL] || _selectedTaxAlloc.get('runMode') == _ADD)
			{
				grid.enableButton('delBtn');
			}else{
				grid.disableButton('delBtn');
			}
			if (_permissionsMap[_self.INQ] && _selectedTaxAlloc.get('runMode') != _ADD)
			{
				grid.enableButton('historicalBtn');
			}else{
				grid.disableButton('historicalBtn');
			}
		}else{
			grid.disableButton('modBtn');
			grid.disableButton('delBtn');
			grid.disableButton('historicalBtn');
		}
	}
	
	function populateDropdownList()
	{
		if (_initTaxAllocXML)
		{
			_resources.popups['taxAllocUpdate'].getField('pComplyCodeFld').loadData(IFDS.Xml.getNode(_initTaxAllocXML, "//List[@id = 'ComplyCode']"));
			_resources.popups['taxAllocUpdate'].getField('pTaxJurisFld').loadData(IFDS.Xml.getNode(_initTaxAllocXML, "//List[@id = 'TaxJuris']"));
		}
	}
	
	function displayTaxAlloc(taxAllocXML, append)
	{
		if (taxAllocXML)
		{
			if (!append)
			{			
				_selectedTaxAlloc = null;
				
				_resources.grids['taxAllocGrid'].getStore().removeAll();
				_resources.grids['taxAllocGrid'].disableAllButtons();
				
			}		
			_resources.grids['taxAllocGrid'].getStore().loadData(taxAllocXML, append);
		}
	}
	
	function validatePopup(action, data)
	{
		if ( action != _DEL )
		{
			// Check duplicate on screen
			var taxAllocRecords = _resources.grids['taxAllocGrid'].getStore().queryBy(
				function(record, id){
					return ( ( (action == _ADD) || (action == _MOD && record.get('taxAllocUUID') != _selectedTaxAlloc.get('taxAllocUUID')) ) 
							&& (record.get('runMode') != _DEL)
							&& (record.get('effDate') == data['effDate'])
              && (record.get('complyCode') == data['complyCode'])
              && (record.get('taxJuris') == data['taxJuris']));
				}
			);
			if (taxAllocRecords && taxAllocRecords.length > 0)
			{
				DesktopWeb.Util.displayError(_translationMap['Error_DuplicateCheckFailed']);
				return;
			}
		}
		
		if ( action == _DEL && _selectedTaxAlloc.get('runMode') == _ADD ) 
		{
			// No need to do the validation, user is deleting the added record.
			if ( updateTaxAlloc(action, data) )
			{
				_resources.popups['taxAllocUpdate'].hide();
			}
			return;
		}
		
		DesktopWeb.Ajax.doSmartviewAjax(_taxAllocValidateService, null, buildValidationXML(), responseHandler);
					
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				if ( updateTaxAlloc(action, data) )
				{
					_resources.popups['taxAllocUpdate'].hide();
				}
			}			
		}

		function buildValidationXML()
		{
			var dataXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(dataXML, 'account', data['account']);
			if ( action != _ADD )
			{
				if ( _selectedTaxAlloc.get('runMode') == _ADD )
				{
					IFDS.Xml.addSingleNode(dataXML, 'runMode', _ADD);
				}else{
					IFDS.Xml.addSingleNode(dataXML, 'taxAllocUUID', _selectedTaxAlloc.get('taxAllocUUID'));
					IFDS.Xml.addSingleNode(dataXML, 'runMode', data['runMode']);
				}
			}else{
				IFDS.Xml.addSingleNode(dataXML, 'runMode', _ADD);
			}
			if ( action != _DEL )
			{
				IFDS.Xml.addSingleNode(dataXML, 'effDate', DesktopWeb.Util.getSMVDateValue(data['effDate']));
				IFDS.Xml.addSingleNode(dataXML, 'complyCode', data['complyCode']);
				IFDS.Xml.addSingleNode(dataXML, 'taxJuris', data['taxJuris']);
				IFDS.Xml.addSingleNode(dataXML, 'ownershipPrcnt', data['ownershipPrcnt']);
				IFDS.Xml.addSingleNode(dataXML, 'taxablePrcnt', data['taxablePrcnt']);
			}
			return dataXML;
		}
	}
	
	function updateTaxAlloc(action, data)
	{
		var store = _resources.grids['taxAllocGrid'].getStore();
		if ( action == _ADD )
		{
			data['taxAllocUUID'] = 'tmpAcctTaxAllocUUID' + (++_runningAcctTaxAllocUUID);
			_resources.grids['taxAllocGrid'].addRecord(data);
			_resources.grids['taxAllocGrid'].selectLastRecord();
		}else{
			if ( _selectedTaxAlloc.get('runMode') == _ADD )
			{
				if ( action == _DEL )
				{
					_selectedTaxAlloc = null;
					_resources.grids['taxAllocGrid'].removeSelectedRecord();
				}else{
					data['runMode'] = _ADD;
					_resources.grids['taxAllocGrid'].updateSelectedRecord(data);
				}
			}else{
				if ( action == _DEL ) _selectedTaxAlloc = null;
				_resources.grids['taxAllocGrid'].updateSelectedRecord(data);
			}
		}
		_self.updatesFlag = true;
		return true;
	}
		
	function buildUpdateXML()
	{
		var updateDoc = IFDS.Xml.newDocument('data');
		var updateXML = IFDS.Xml.addSingleNode(updateDoc, "AcctTaxAllocUpdDetails");
		var modAcctTaxAllocRecords = _resources.grids['taxAllocGrid'].getStore().queryBy(
			function(record, id){
				return (record.get('runMode') == _DEL);
			}
		);
		buildAcctTaxAllocUpd(modAcctTaxAllocRecords);
		
		modAcctTaxAllocRecords = _resources.grids['taxAllocGrid'].getStore().queryBy(
			function(record, id){
				return (record.get('runMode') == _MOD);
			}
		);
		buildAcctTaxAllocUpd(modAcctTaxAllocRecords);
		
		modAcctTaxAllocRecords = _resources.grids['taxAllocGrid'].getStore().queryBy(
			function(record, id){
				return (record.get('runMode') == _ADD);
			}
		);
		buildAcctTaxAllocUpd(modAcctTaxAllocRecords);
		
		function buildAcctTaxAllocUpd(records)
		{
			if (records)
			{
				for(i = 0; i < records.length; i++)
				{
					var record = records.itemAt(i);
					var acctTaxAllocUpd = IFDS.Xml.addSingleNode(updateXML, "AcctTaxAllocUpdDetail");
					IFDS.Xml.addAttribute(acctTaxAllocUpd, 'RecordSource', record.get('taxAllocUUID'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "account", record.get('account'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "runMode", record.get('runMode'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "version", record.get('version'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "taxAllocUUID", record.get('taxAllocUUID'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "effDate", DesktopWeb.Util.getSMVDateValue(record.get('effDate')));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "complyCode", record.get('complyCode'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "taxJuris", record.get('taxJuris'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "ownershipPrcnt", record.get('ownershipPrcnt'));
					IFDS.Xml.addSingleNode(acctTaxAllocUpd, "taxablePrcnt", record.get('taxablePrcnt'));
				}
			}
		}
		
		return updateDoc;
	}

	function storeContextErrors(errorNodes)
	{
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var taxAllocUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			
			// Update Grid
			var recordIndex = _resources.grids['taxAllocGrid'].getStore().find('taxAllocUUID', taxAllocUUID);
			var taxAllocRecord = _resources.grids['taxAllocGrid'].getStore().getAt(recordIndex);
			taxAllocRecordecord.set('errMsg', errMsg);
			_resources.grids['taxAllocGrid'].getStore().commitChanges();
			if(firstErrRecIndex==-1)firstErrRecIndex = recordIndex;
		}
		if(firstErrRecIndex==-1)
		{
			_resources.grids['taxAllocGrid'].getSelectionModel().selectFirstRow();
		}else{
			_resources.grids['taxAllocGrid'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['taxAllocGrid'].focusRow(firstErrRecIndex);
		}
	}
	
	function clearContextErrors(taxAllocUUID)
	{
		if ( taxAllocUUID && taxAllocUUID.length > 0 )
		{
			var recordIndex = _resources.grids['taxAllocGrid'].getStore().find('taxAllocUUID', taxAllocUUID);
			var taxAllocRecord = _resources.grids['taxAllocGrid'].getStore().getAt(recordIndex);
			taxAllocRecordecord.set('errMsg', errMsg);
		}else{
			var errAcctTaxAllocRecords = _resources.grids['taxAllocGrid'].getStore().queryBy(
				function(record, id){
					return (record.get('errMsg') != "");
				}
			);
			Ext.each(errAcctTaxAllocRecords, function(record){
				record.set('errMsg', '');
			});
		}
	}

	// PUBLIC ITEMS *************************************
	return {				
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		
		,updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			loadTaxAlloc(DesktopWeb._SCREEN_PARAM_MAP['AccountNum'], false, 'init');
		}
		
		,setSelectedTaxAlloc: function(record)
		{
			_selectedTaxAlloc = record;
			updateTaxAllocButtons();
		}
		
		,openActionPopup: function(action)
		{
			var popup = _resources.popups['taxAllocUpdate'];
			popup.show();	
			if ( action == _ADD )
			{
				_resources.grids['taxAllocGrid'].clearSelectedRecord();
				popup.init(action, null);
			}else{
				popup.init(action, _selectedTaxAlloc);
			}				
		}
		
		,getDisplay: function(listName, code)
		{
			var listNode = IFDS.Xml.getNode(_initTaxAllocXML, "//List[@id = '" + listName + "']/Element[code='" + code + "']");
			return (listNode)?IFDS.Xml.getNodeValue(listNode, 'value'):code;
		}
		
		,taxAllocUpdate: function(action, data)
		{
			validatePopup(action, data);
		}
		
		,getSelectedTaxAlloc: function()
		{
			return _selectedTaxAlloc;
		}
		
		,clickHandle_historyBtn: function()
		{
			var viewParam = {};
			var historyName = null;
			viewParam['auditType'] = 'AcctOwnershipAlloc';
			viewParam['searchValue1'] = _selectedTaxAlloc.get('taxAllocUUID');
			historyName = _translationMap['title']+ ' - ' +_translationMap['History'];
			
			_resources.popups['history'].init(historyName, _historyService, viewParam, true);
			_resources.popups['history'].show();
		}
		
		,controlButton: function()
		{
		    updateTaxAllocButtons();
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;	
			
			DesktopWeb.Ajax.doSmartviewUpdate(_taxAllocUpdateService, null, buildUpdateXML(), responseHandler, _translationMap['Updating']);			

			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else 
				{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL; 
				}
			}	

			return updateStatus;	
		}
	}	
}	