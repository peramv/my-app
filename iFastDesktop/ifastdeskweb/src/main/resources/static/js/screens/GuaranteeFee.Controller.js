/*********************************************************************************************
 * @file	GuaranteeFee.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for GuaranteeFee screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *        - Fix display date format follows dateFormatDisplay parameter
 *
 *  07 Apr 2015 T. Kornnika P0181067 CHG0040053 T80639
 *        - Modified to solve when user adding a manual guarantee fees for a specific series, 
 *          the display of the manual collection funds shows all FUND and CLASS for all series 
 *          and not only the one related to the series selected to add a manual fees.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached. 
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************1
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = 'dtGuarFeeInit';
	var _reloadView = 'dtGuarFeeReload';
	var _detlView = 'dtGuarFeeDetl'
	var _updateView = 'dtGuarFeeUpd'
	var _calcValdtnView = 'dtGuarFeeCalcVal';
	var _collectValdtnView = 'dtGuarFeeCollectVal';
	var _permissions = null;
	var _initDataXML = null;

		
	
	// PRIVATE METHODS ****************************************
	function loadDropdowns()
	{
		_resources.fields['contractType'].loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName="ContractTypeList"]'));
		_resources.popups['manualColl'].getField('acCode').loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName="acCodeList"]'));		
		_resources.popups['cancelColl'].getField('rvcd').loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName="RVCDList"]'));
	}

	function storePermissions()
	{
		_permissions = {};
		_permissions[_self.ADD] = IFDS.Xml.getNodeValue(_initDataXML, '*/Permissions/add') == "yes";
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(_initDataXML, '*/Permissions/mod') == "yes";
		_permissions[_self.DEL] = IFDS.Xml.getNodeValue(_initDataXML, '*/Permissions/del') == "yes";
		_permissions[_self.RECALC] = IFDS.Xml.getNodeValue(_initDataXML, '*/Permissions/recalc') == "yes";
		_permissions[_self.CANCEL] = IFDS.Xml.getNodeValue(_initDataXML, '*/Permissions/canc') == "yes";
		_permissions[_self.CANCEL_COLLECT] = IFDS.Xml.getNodeValue(_initDataXML, '*/Permissions/cancCollect') == "yes";
		_permissions[_self.REBOOK] = IFDS.Xml.getNodeValue(_initDataXML, '*/Permissions/rebook') == "yes";
	}

	function sendCalcValidationRequest(data, callback)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.fields['contractType'].getValue());
		IFDS.Xml.addSingleNode(dataXML, "feeType", _resources.fields['feeType'].getValue());
		var calcsXML = IFDS.Xml.addSingleNode(dataXML, "Calculations");
		var calcRecXML = IFDS.Xml.addSingleNode(calcsXML, "Calculation");

		var calcRec = _resources.grids['calculations'].getSelectedRecord();	
		if (calcRec)
		{	
			IFDS.Xml.addSingleNode(calcRecXML, 'guarFeeSummID', calcRec.data['guarFeeSummID']);		
		}				
		for (var i in data)
		{
			if( i == 'deff' )
			{
				IFDS.Xml.addSingleNode(calcRecXML, i, DesktopWeb.Util.getSMVDateValue(data[i]));
			}
			else
			{
				IFDS.Xml.addSingleNode(calcRecXML, i, data[i]);
			}
		}
				
		DesktopWeb.Ajax.doSmartviewAjax(_calcValdtnView, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])

		function responseHandler(success, responseXML)			
		{			
			if (success)
			{				
				callback(true, responseXML);				
			}				
		}
	}
	
	function sendCalcCancelValidationRequest(callback)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.fields['contractType'].getValue());
		IFDS.Xml.addSingleNode(dataXML, "feeType", _resources.fields['feeType'].getValue());
		var calcsXML	 = IFDS.Xml.addSingleNode(dataXML, "Calculations");
		var calcRecXML = IFDS.Xml.addSingleNode(calcsXML, "Calculation");

		var calcRec = _resources.grids['calculations'].getSelectedRecord();		
		IFDS.Xml.addSingleNode(calcRecXML, 'guarFeeSummID', calcRec.data['guarFeeSummID']);
		IFDS.Xml.addSingleNode(calcRecXML, 'runMode', 'cancel-calc');
				
		DesktopWeb.Ajax.doSmartviewAjax(_calcValdtnView, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])

		function responseHandler(success, responseXML)			
		{						
			if (success)
			{
				callback(true);
			}				
		}
	}
	
	function sendRecalcValidationRequest(callback)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.fields['contractType'].getValue());
		IFDS.Xml.addSingleNode(dataXML, "feeType", _resources.fields['feeType'].getValue());
		var calcsXML	 = IFDS.Xml.addSingleNode(dataXML, "Calculations");
		var calcRecXML = IFDS.Xml.addSingleNode(calcsXML, "Calculation");

		var calcRec = _resources.grids['calculations'].getSelectedRecord();		
		IFDS.Xml.addSingleNode(calcRecXML, 'guarFeeSummID', calcRec.data['guarFeeSummID']);
		IFDS.Xml.addSingleNode(calcRecXML, 'runMode', 'recalc');
				
		DesktopWeb.Ajax.doSmartviewAjax(_calcValdtnView, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])

		function responseHandler(success, responseXML)			
		{						
			if (success)
			{
				callback(true);
			}				
		}
	}
	
	function sendCollRebookValidationRequest(callback)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.fields['contractType'].getValue());
		IFDS.Xml.addSingleNode(dataXML, "feeType", _resources.fields['feeType'].getValue());
		var calcsXML	 = IFDS.Xml.addSingleNode(dataXML, "Calculations");
		var calcRecXML = IFDS.Xml.addSingleNode(calcsXML, "Calculation");

		var calcRec = _resources.grids['calculations'].getSelectedRecord();		
		IFDS.Xml.addSingleNode(calcRecXML, 'guarFeeSummID', calcRec.data['guarFeeSummID']);

		var collsXML = IFDS.Xml.addSingleNode(calcRecXML, 'Collections');

		var collRec = _resources.grids['collections'].getSelectedRecord();
		var collXML = IFDS.Xml.addSingleNode(collsXML, 'Collection');
		IFDS.Xml.addSingleNode(collXML, 'runMode', 'rebook');
		IFDS.Xml.addSingleNode(collXML, 'guarFeeSummID', collRec.data['guarFeeSummID']);
		IFDS.Xml.addSingleNode(collXML, 'gwbFeeCollectionID', collRec.data['gwbFeeCollectionID']);
		IFDS.Xml.addSingleNode(collXML, 'gwbFeeCollectAllocUUID', collRec.data['gwbFeeCollectAllocUUID']);		
		
		DesktopWeb.Ajax.doSmartviewAjax(_collectValdtnView, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])

		function responseHandler(success, responseXML)			
		{						
			if (success)
			{
				callback(true);
			}				
		}
	}

	function sendCollCancelValidationRequest(data, callback)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.fields['contractType'].getValue());
		IFDS.Xml.addSingleNode(dataXML, "feeType", _resources.fields['feeType'].getValue());
		var calcsXML	 = IFDS.Xml.addSingleNode(dataXML, "Calculations");
		var calcRecXML = IFDS.Xml.addSingleNode(calcsXML, "Calculation");

		var calcRec = _resources.grids['calculations'].getSelectedRecord();		
		IFDS.Xml.addSingleNode(calcRecXML, 'guarFeeSummID', calcRec.data['guarFeeSummID']);

		var collRec = _resources.grids['collections'].getSelectedRecord();		
		var collsXML = IFDS.Xml.addSingleNode(calcRecXML, 'Collections');
		
		var collXML = IFDS.Xml.addSingleNode(collsXML, 'Collection');
		IFDS.Xml.addSingleNode(collXML, 'runMode', 'cancel-collect');
		IFDS.Xml.addSingleNode(collXML, 'gwbFeeCollectionID', collRec.data['gwbFeeCollectionID']);
		for (var i in data)
		{
			IFDS.Xml.addSingleNode(collXML, i, data[i]);
		}
		
		DesktopWeb.Ajax.doSmartviewAjax(_collectValdtnView, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])

		function responseHandler(success, responseXML)			
		{						
			if (success)
			{
				callback(true);
			}				
		}
	}

	function getAllCalcRecords()
	{
		var store = _resources.grids['calculations'].getStore();
		var records = [];
		
		if (store.getTotalCount() > 0)
		{
			var fieldName = store.fields.keys[0];
						
			var results = store.query(fieldName, /.*/)
			for (var i = 0; i < results.getCount(); i++)
			{
				records.push(results.itemAt(i));
			}
		}		
		return records;		
	}


	function buildUpdateXML()
	{
		var updateXML = IFDS.Xml.newDocument('data');
		var calcsXML = IFDS.Xml.addSingleNode(updateXML, 'Calculations');		
		var calcRecords = getAllCalcRecords();
		var calcXML;
		var collRecords;

		IFDS.Xml.addSingleNode(updateXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(updateXML, "contractType", _resources.fields['contractType'].getValue());
		IFDS.Xml.addSingleNode(updateXML, "feeType", _resources.fields['feeType'].getValue());

		for (var i = 0; i < calcRecords.length; i++)
		{
			calcXML = null; 
			collRecords = null;

			if (calcRecords[i].data['runMode'])
			{
				calcXML = IFDS.Xml.addSingleNode(calcsXML, 'Calculation');				
			}
			else
			{
				collRecords = _resources.grids['collections'].getStore().queryBy(function (record){
					return ((record.data['guarFeeSummID'] === calcRecords[i].data['guarFeeSummID']) && record.data['runMode']);
				});

				if (collRecords && collRecords.length > 0)
				{					
					calcXML = IFDS.Xml.addSingleNode(calcsXML, 'Calculation');
				}
			}

			if (calcXML)
			{
				for (var item in calcRecords[i].data)
				{				
					if( item == 'deff' || item == 'processDate')
					{
						IFDS.Xml.addSingleNode(calcXML, item, DesktopWeb.Util.getSMVDateValue(calcRecords[i].data[item]));
					}
					else
					{
						IFDS.Xml.addSingleNode(calcXML, item, calcRecords[i].data[item]);
					}
				}

				var collsXML = IFDS.Xml.addSingleNode(calcXML, 'Collections');									
				collRecords = _resources.grids['collections'].getStore().queryBy(function (record){
					return ((record.data['guarFeeSummID'] === calcRecords[i].data['guarFeeSummID']));
				});

				collRecords.each(function (rec){
					var collXML = IFDS.Xml.addSingleNode(collsXML, 'Collection');
					for (var item in rec.data)
					{				
						if( item == 'collectionDate' || item == 'modDate')					
							IFDS.Xml.addSingleNode(collXML, item, DesktopWeb.Util.getSMVDateValue(rec.data[item]));
						else					
							IFDS.Xml.addSingleNode(collXML, item, rec.data[item]);								
					}
				});								
			}		
		}		
		return updateXML;
	}
	
		
	// PUBLIC ITEMS *************************************
	return {				
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		,RECALC: 'recalc'
		,CANCEL: 'canc'
		,CANCEL_COLLECT: 'cancel-collect'
		,REBOOK: 'rebook'


		,updatesFlag: false

		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
						
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);			

			function responseHandler(success, responseXML)			
			{											
				if (success)
				{
					_initDataXML = responseXML;
					loadDropdowns();										
					storePermissions();
				}				
			}
		}

		,getDefaultDate: function(){
			return DesktopWeb.Util.getDateDisplayValue(
				IFDS.Xml.getNodeValue(_initDataXML, '*/EffectiveDate/deff'));
		}
		
		,handleContractTypeUpdate: function()
		{
			var contractType = _resources.fields['contractType'].getValue();
			if (contractType)
			{
				_resources.fields['feeType'].enable();			
				if (IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "GuarFeeTypeList_' + contractType + '"]') != null)
				{				
					_resources.fields['feeType'].loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "GuarFeeTypeList_' + contractType + '"]'));
				}
				else
				{
					throw new Error('No fee type list found for ' + contractType);
				}
			}
			else
			{
				_resources.fields['feeType'].reset();
				_resources.fields['feeType'].disable();
			}				
		}

		,doSearch: function()
		{
			if (_resources.fields['contractType'].isValid() && _resources.fields['feeType'].isValid())
			{			
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
				IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.fields['contractType'].getValue());
				IFDS.Xml.addSingleNode(dataXML, "feeType", _resources.fields['feeType'].getValue());
								
				DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
				
				function responseHandler(success, responseXML)
				{										
					if (success)
					{
						_resources.grids['calculations'].loadData(IFDS.Xml.getNode(responseXML, '*/Calculations'));
						_resources.grids['collections'].loadData(IFDS.Xml.getNode(responseXML, '*/Calculations'));
					}			
					_resources.fields['contractType'].disable();	
					_resources.fields['feeType'].disable();
					_resources.buttons['search'].disable();

					if (_permissions[_self.ADD])
					{
						_resources.grids['calculations'].enableButton('addBtn');
					}
				}
			}			
		}

		,doReset: function()
		{
			_resources.fields['contractType'].reset();
			_resources.fields['contractType'].enable();

			_resources.fields['feeType'].reset();
			_resources.fields['feeType'].enable();

			_resources.grids['calculations'].clearData();			
			_resources.grids['collections'].clearData();

			_resources.buttons['search'].enable();
			_self.updatesFlag = false;
		}

		,handleCalcSelectionChange: function()
		{
			var selectedCalcRecord = _resources.grids['calculations'].getSelectedRecord();

			// mod btn
			if (selectedCalcRecord && _permissions[_self.MOD] && selectedCalcRecord.data['modPerm'] == 'yes')
			{
				_resources.grids['calculations'].enableButton('modBtn');	
			}
			else
			{
				_resources.grids['calculations'].disableButton('modBtn');		
			}

			// del btn
			if (selectedCalcRecord && _permissions[_self.DEL] && selectedCalcRecord.data['delPerm'] == 'yes')
			{
				_resources.grids['calculations'].enableButton('delBtn');	
			}
			else
			{
				_resources.grids['calculations'].disableButton('delBtn');		
			}

			// cancel btn
			if (selectedCalcRecord && _permissions[_self.CANCEL] && selectedCalcRecord.data['cancPerm'] == 'yes')
			{
				_resources.grids['calculations'].enableButton('cancelBtn');	
			}
			else
			{
				_resources.grids['calculations'].disableButton('cancelBtn');		
			}

			// recalc btn
			if (selectedCalcRecord && _permissions[_self.RECALC] && selectedCalcRecord.data['recalcPerm'] == 'yes')
			{
				_resources.grids['calculations'].enableButton('recalcBtn');	
			}
			else
			{
				_resources.grids['calculations'].disableButton('recalcBtn');		
			}

			// details btn
			if (selectedCalcRecord && selectedCalcRecord.data['runMode'] != _self.ADD)
			{
				_resources.grids['calculations'].enableButton('detailsBtn');	
			}
			else
			{
				_resources.grids['calculations'].disableButton('detailsBtn');		
			}

			_resources.grids['collections'].getStore().filterBy(function(rec){
				return selectedCalcRecord && rec.data['guarFeeSummID'] == selectedCalcRecord.data['guarFeeSummID'];
			});
			_resources.grids['collections'].selectFirstRecord();
		}

		,openManualCollPopup: function(action)
		{
			if (action == _self.ADD)
			{
				_resources.grids['calculations'].clearSelectedRecord();
			}
			_resources.popups['manualColl'].action = action;
			_resources.popups['manualColl'].show();
		}

		,deleteAutomaticCalc: function()
		{
			DesktopWeb.Util.displayPrompt("Are you sure you wish to delete selected calculation?", callback);

			function callback(btn)
			{				
				if (btn == 'ok')
				{
					_self.saveManualColl(_self.DEL, {runMode: _self.DEL});
				}
			}
		}

		,getFundList: function(contractType)
		{
			return IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "FundList_' + contractType + '"]');
		}

		,handleFundChange: function()
		{
			var fund = _resources.popups['manualColl'].getField('fund').getValue();
			if (fund)
			{						
				_resources.popups['manualColl'].getField('class').loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "ClassList_' + _resources.fields['contractType'].getValue() + '_' + fund + '"]'))		
				_resources.popups['manualColl'].getField('class').enableField();
			}
			else
			{
				_resources.popups['manualColl'].getField('class').reset();
				_resources.popups['manualColl'].getField('class').disableField();	
			}
		}		

		,saveManualColl: function(action, data)
		{
			var selectedCalcRecord = _resources.grids['calculations'].getSelectedRecord();
			var selectedCollRecord = _resources.grids['collections'].getSelectedRecord();

			var reqValidation = true;
			if (selectedCalcRecord && selectedCalcRecord.data['runMode'] == _self.ADD)
			{
				if (action == _self.MOD)
				{
					data['runMode'] = _self.ADD;
				}
				else if (action == _self.DEL)
				{
					_resources.grids['collections'].removeSelectedRecord();
					_resources.grids['calculations'].removeSelectedRecord();
					_resources.popups['manualColl'].hide();
					_self.updatesFlag = true;
					reqValidation = false;
				}
			}

			if (reqValidation)
			{
				sendCalcValidationRequest(data, callback);
			}

			function callback(success, responseXML)
			{
				if (success)
				{					
					if (action == _self.ADD)
					{
						_resources.grids['calculations'].appendData(IFDS.Xml.getNode(responseXML, '*/Calculations'));
						_resources.grids['collections'].appendData(IFDS.Xml.getNode(responseXML, '*/Calculations'));

						_resources.grids['calculations'].selectLastRecord();
						var calcRec = _resources.grids['calculations'].getSelectedRecord();
						calcRec.data['runMode'] = data['runMode'];
						calcRec.commit();
						var collRec = _resources.grids['collections'].getSelectedRecord();
						collRec.data['runMode'] = _self.ADD;
						collRec.commit();
					}
					else if (action == _self.MOD)
					{						
						var nodes = IFDS.Xml.getNodes(responseXML, '*/Calculations/Calculation/Collections/Collection/*');
						for (var i = 0; i < nodes.length; i++)
						{							
							if (selectedCollRecord.data[nodes[i].nodeName])
							{
								if (nodes[i].nodeName == 'collectionDate'
										|| nodes[i].nodeName == 'modDate')
									selectedCollRecord.data[nodes[i].nodeName] = DesktopWeb.Util.getDateDisplayValue(nodes[i].text);
								else
									selectedCollRecord.data[nodes[i].nodeName] = nodes[i].text;
							} 							
						}												
						selectedCollRecord.commit();

						var nodes = IFDS.Xml.getNodes(responseXML, '*/Calculations/Calculation/*');						
						for (var i = 0; i < nodes.length; i++)
						{							
							if (selectedCalcRecord.data[nodes[i].nodeName])
							{
								if (nodes[i].nodeName == 'deff' || nodes[i].nodeName == 'processDate')
									selectedCalcRecord.data[nodes[i].nodeName] = DesktopWeb.Util.getDateDisplayValue(nodes[i].text);
								else
									selectedCalcRecord.data[nodes[i].nodeName] = nodes[i].text;
							} 							
						}												
						if (selectedCalcRecord.data['runMode'] != _self.ADD)
						{
							selectedCalcRecord.data['runMode'] = _self.MOD;
						}
						selectedCalcRecord.commit();
					}
					else if (action == _self.DEL)
					{																											
						selectedCalcRecord.data['runMode'] = _self.DEL;												
						selectedCalcRecord.commit();						
					}
					_resources.popups['manualColl'].hide();
					_self.updatesFlag = true;
				}
			}
		}
		
		,doCalculationCancel: function()
		{			
			sendCalcCancelValidationRequest(callback);
			
			function callback(success)
			{
				if (success)
				{					
					var selectedCalcRecord = _resources.grids['calculations'].getSelectedRecord();											
					selectedCalcRecord.data['statDesc'] = _translationMap['CancelRequested'];
					selectedCalcRecord.data['runMode'] = 'cancel-calc';
					selectedCalcRecord.commit();
					_self.updatesFlag = true;
				}
			}
		}
		
		,doCalculationRecalc: function()
		{			
			sendRecalcValidationRequest(callback);
			
			function callback(success)
			{
				if (success)
				{
					var selectedCalcRecord = _resources.grids['calculations'].getSelectedRecord();						
					selectedCalcRecord.data['statDesc'] = _translationMap['RecalcRequested'];
					selectedCalcRecord.data['runMode'] = 'recalc';
					selectedCalcRecord.commit();
					_self.updatesFlag = true;
				}
			}
		}		

		,populateDetails: function()
		{			
			var selectedRecord = _resources.grids['calculations'].getSelectedRecord();
			if (selectedRecord)
			{
				var dataXML = IFDS.Xml.newDocument('data');
				IFDS.Xml.addSingleNode(dataXML, "guarFeeSummID", selectedRecord.data['guarFeeSummID']);			
				
				DesktopWeb.Ajax.doSmartviewAjax(_detlView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
				
				function responseHandler(success, responseXML)
				{								
					if (success)
					{
						_resources.grids['month'].loadData(IFDS.Xml.getNode(responseXML, '*/Details'));											
						_resources.grids['detl'].loadData(IFDS.Xml.getNode(responseXML, '*/Details'));						
					}				
				}
			}
			else
			{
				throw new Error('no calculation record selected');
			}
		}
		
		,handleDetlSelectionChange: function()
		{
			var selectedDetlRecord = _resources.grids['detl'].getSelectedRecord();			
			_resources.grids['month'].getStore().filterBy(function(rec){
				var parentDetlNode = rec.node.parentNode.parentNode;		
				return selectedDetlRecord && IFDS.Xml.getNodeValue(parentDetlNode, 'guarFeeDetlID') == selectedDetlRecord.data['guarFeeDetlID'];
			});			
		}
		
		,handleCollSelectionChange: function()
		{
			var selectedCollRecord = _resources.grids['collections'].getSelectedRecord();

			// cancel btn
			if (selectedCollRecord && _permissions[_self.CANCEL_COLLECT] && selectedCollRecord.data['cancCollectPerm'] == 'yes')
			{				
				_resources.grids['collections'].enableButton('cancelBtn');
			}
			else
			{
				_resources.grids['collections'].disableButton('cancelBtn');	
			}

			// rebook btn
			if (selectedCollRecord && _permissions[_self.REBOOK] && selectedCollRecord.data['rebookPerm'] == 'yes')
			{				
				_resources.grids['collections'].enableButton('rebookBtn');
			}
			else
			{
				_resources.grids['collections'].disableButton('rebookBtn');	
			}
		}

		,doCollectionCancel: function()
		{			
			_resources.popups['cancelColl'].show();
		}

		,saveCollCancel: function(data)
		{			
			sendCollCancelValidationRequest(data, callback);			
			
			function callback(success)
			{
				if (success)
				{
					if (data) // Automatic
					{
						var selectedCalcRecord = _resources.grids['calculations'].getSelectedRecord();
						var selectedCollRecord = _resources.grids['collections'].getSelectedRecord();
						_resources.grids['collections'].getStore().each(function(rec){							
							if (rec.data['guarFeeSummID'] === selectedCalcRecord.data['guarFeeSummID']
								&& rec.data['collectionDate'] === selectedCollRecord.data['collectionDate']
								&& rec.data['cancCollectPerm'] === 'yes')
							{
								rec.data['statDesc'] = _translationMap['CancelRequested'];
								rec.data['runMode'] = 'cancel-collect';
								rec.data['stmt'] = data['stmt'];
								rec.data['rvcd'] = data['rvcd'];
								rec.data['conf'] = data['conf'];
								rec.data['cancPymnt'] = data['cancPymnt'];
								rec.data['remarks1'] = data['remarks1'];
								rec.data['remarks2'] = data['remarks2'];
								rec.data['remarks3'] = data['remarks3'];
								rec.commit();
							}							
						});
					}
					else 
					{
						var selectedCollRecord = _resources.grids['collections'].getSelectedRecord();
						selectedCollRecord.data['statDesc'] = _translationMap['CancelRequested'];
						selectedCollRecord.data['runMode'] = 'cancel-collect';	
						selectedCollRecord.commit();					
					}
					_resources.popups['cancelColl'].hide();
					_self.updatesFlag = true;
				}
			}
		}
		
		,doCollectionRebook: function()
		{			
			sendCollRebookValidationRequest(callback);			
			
			function callback(success)
			{
				if (success)
				{
					var selectedCalcRecord = _resources.grids['calculations'].getSelectedRecord();
					var selectedCollRecord = _resources.grids['collections'].getSelectedRecord();

					_resources.grids['collections'].getStore().each(function(rec) {
						if (rec.data['guarFeeSummID'] === selectedCalcRecord.data['guarFeeSummID']
								&& rec.data['collectionDate'] === selectedCollRecord.data['collectionDate']
								&& rec.data['rebookPerm'] === 'yes')
						{							
							rec.data['statDesc'] = _translationMap['RebookRequested'];
							rec.data['runMode'] = 'rebook';
							rec.commit();
							_self.updatesFlag = true;
						}
					});
				}
			}
		}

		,doUpdate: function()
		{
			var updateStatus = null;
			
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler, null);

			function responseHandler(success, responseXML)
			{								
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{					
					updateStatus = DesktopWeb._FAIL					
				}				
			}
			return updateStatus;
		}
	}	
}	
