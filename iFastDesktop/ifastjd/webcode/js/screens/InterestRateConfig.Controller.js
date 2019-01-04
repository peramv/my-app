/*********************************************************************************************
 * @file	InterestRateConfig.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Interest Rate Configuration
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  22Aug 2017 Gomoot T. P0263240 CHG0048754 T86111 DFT0076496 
 *					- To protect display description as blank on grid ,
 *             the table will get desc from Inquiry service instead.
 *          - Fix incorrect dateformat 
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();	
	
	var _ADD = 'ADD';
	var _MOD = 'MOD';
	var _INQ = 'INQ';
	var _DEL = 'DEL';
	var _UNCH = 'UNCH';
	
	var _MVDisplayValue = _translationMap['MVDisplayValue'];

	var _selectedIntRate = null;
	var _selectedIntRateIndex = 0;
	var _intRateXML = null;
	var _intSegXML = null;
	var _selectedSegment = null;
	
	var _fundCatsMapping = null;
	var _calcMthdsMapping = null;
	var _intSegsMapping = null;
	var _configValuesMapping = null;
	var _configCodesMapping = null;
	var _commRedsMapping = null;
	var _listSelsMapping = null;
	var _defaultObject = null;
	var _permissions = {};
	
	var _intRateReqXML = null;
	var _runningIntRateUUID = 0;
	var _runningIntRateDetlUUID = 0;
	var _nextStartRecNum = 1;
	var _requestRecNum = 25;
	
	var _intRateInitService = 'dtIntRateConfigInit';
	var _intRateReloadService = 'dtIntRateConfigReload';
	var _intRateVldService = 'dtIntRateCfgMstrVld';
	var _intRateDetlVldService = 'dtIntRateCfgDetlVld';
	var _intRateProcessService = 'dtIntRateConfigProc';
	var _historyService = 'dtHistoricalInfo';
	
	var _errInIntSeg = _translationMap['ErrInIntSeg'];

	// PRIVATE METHODS ****************************************	
	function loadIntRate()
	{
		var paramXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', _nextStartRecNum);
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

		clearSelector('intSegSelector');
		clearGrid('intRateCfgGrid');
		
		DesktopWeb.Ajax.doSmartviewAjax(_intRateInitService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{	
			if (success)
			{
				_intRateXML = responseXML;
				_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
				if (_nextStartRecNum)
				{
					_resources.grids['intRateCfgGrid'].enableButton('moreBtn');
				}
				else
				{
					_resources.grids['intRateCfgGrid'].disableButton('moreBtn');
				}
			}else{
				_intRateXML = null;
			}
			
			if(_intRateXML)
			{
				loadDefaultObject(IFDS.Xml.getNode(_intRateXML, '//Default'));
				
				loadMapping();
				storePermissions(_intRateXML);
				
				loadAddOnIntRateCfgElements(_intRateXML);
				_resources.popups['intRateCfgUpdate'].getField('fundCategoryFld').getStore().loadData(getList('FundCategory'));
				
				if (_permissions[_INQ]) {
					_resources.grids['intRateCfgGrid'].getStore().loadData(_intRateXML);
					_resources.grids['intRateCfgGrid'].getSelectionModel().selectFirstRow();
				}
				
				updateIntRateButtons();
				
				// Add listener to control the buttons (remove, moveUp, moveDown, and Edit)
				_resources.selectors['intSegSelector'].selectedGrid.getSelectionModel().addListener('selectionchange', updateSegmentButtons);
				_resources.selectors['intSegSelector'].addBtn.addListener('click', addSegment);
				_resources.selectors['intSegSelector'].removeBtn.addListener('click', removeSegment);
				_resources.selectors['intSegSelector'].moveUpBtn.addListener('click', moveUpSegment);
				_resources.selectors['intSegSelector'].moveDownBtn.addListener('click', moveDownSegment);
			}
		}
	}
	
	/** Store user permission **/
	function storePermissions(initViewXML)
	{	
		_permissions[_INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissions[_ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissions[_MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissions[_DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function loadDefaultObject(defaultXML)
	{
		if(defaultXML)
		{
			if(!_defaultObject) _defaultObject = new Object;
			_defaultObject['deff'] = IFDS.Xml.getNodeValue(defaultXML, 'defDeff');
			_defaultObject['stopDate'] = IFDS.Xml.getNodeValue(defaultXML, 'defStopDate');
			_defaultObject['deffDateObj'] =  DesktopWeb.Util.stringToDate(_defaultObject['deff']);
		}
	}
	
	function addSegment()
	{ 
		var store = _resources.selectors['intSegSelector'].selectedGrid.getStore();
		var addedSeg = store.getAt(store.getCount()-1);
		var selectedIntSegsXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']/IntRateCfgDetls");
		var selectedIntSegXML = IFDS.Xml.getNode(selectedIntSegsXML, "IntRateCfgDetl[detlUUID='" + addedSeg.get('detlUUID') + "']");
		if(selectedIntSegXML){
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(selectedIntSegXML, 'updMode'), _MOD);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(selectedIntSegXML, 'seq'), store.getCount());
		}else{
			var newSegXML = createSegmentXML(_ADD, addedSeg);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(newSegXML, 'seq'), store.getCount());
			IFDS.Xml.appendNode(selectedIntSegsXML, newSegXML);
		}
		
		addedSeg.set('seq', store.getCount());
		addedSeg.set('configValue', "");
		addedSeg.set('configValueDisplay', (addedSeg.get('code')=="MV")?_MVDisplayValue:"");
		store.commitChanges();
		
		var intRateXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
		updateIntRateCfgUpdMode(intRateXML);
		_self.updatesFlag = true;
	}
	
	function removeSegment()
	{
		var store = _resources.selectors['intSegSelector'].selectedGrid.getStore();
		
		var selectedIntSegsXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']/IntRateCfgDetls");
		var selectedIntSegXML = IFDS.Xml.getNode(selectedIntSegsXML, "IntRateCfgDetl[detlUUID='" + _selectedSegment.get('detlUUID') + "']");
		var updMode = IFDS.Xml.getNodeValue(selectedIntSegXML, 'updMode');
		if(updMode == _ADD){
			IFDS.Xml.deleteNode(selectedIntSegXML);
		}else{
			var updModeNode = IFDS.Xml.getNode(selectedIntSegXML, 'updMode');
			if(updModeNode == null){
				IFDS.Xml.addSingleNode(selectedIntSegXML, 'updMode', _DEL);
			}else{
				IFDS.Xml.setNodeValue(updModeNode, _DEL);
			}
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(selectedIntSegXML, 'configValue'), "");
		}
		
		// Update below segments
		var begin =  parseInt(_selectedSegment.get('seq')) - 1;
		for(i=begin;i<store.getCount();i++){
			var intSegRecord = store.getAt(i);
			updateSequenceSegment(intSegRecord, (i + 1));
		}
		
		var intRateXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
		updateIntRateCfgUpdMode(intRateXML);
		_self.updatesFlag = true;
	}
	
	function moveUpSegment()
	{
		var store = _resources.selectors['intSegSelector'].selectedGrid.getStore();
		var selectedIndex = store.indexOf(_selectedSegment);
		var moveDownSegment = store.getAt(selectedIndex + 1);
		updateSequenceSegment(_selectedSegment, selectedIndex + 1);
		updateSequenceSegment(moveDownSegment, selectedIndex + 2);
		
		var intRateXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
		updateIntRateCfgUpdMode(intRateXML);
		_self.updatesFlag = true;
	}
	
	function moveDownSegment()
	{
		var store = _resources.selectors['intSegSelector'].selectedGrid.getStore();
		var selectedIndex = store.indexOf(_selectedSegment);
		var moveDownSegment = store.getAt(selectedIndex - 1);
		updateSequenceSegment(_selectedSegment, selectedIndex + 1);
		updateSequenceSegment(moveDownSegment, selectedIndex);

		var intRateXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
		updateIntRateCfgUpdMode(intRateXML);
		_self.updatesFlag = true;
	}
	
	function updateSequenceSegment(segment, sequence)
	{
		segment.set('seq', sequence);
		_resources.selectors['intSegSelector'].selectedGrid.getStore().commitChanges();
		
		var segmentXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']/IntRateCfgDetls/IntRateCfgDetl[detlUUID='" + segment.get('detlUUID') + "']");
		var updMode = IFDS.Xml.getNodeValue(segmentXML, 'updMode');
		if(!updMode)
		{
			IFDS.Xml.addSingleNode(segmentXML, "updMode", _MOD);
		}
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(segmentXML, 'seq'), sequence);
	}
	
	function createSegmentXML(action, segment)
	{
		var segXML = IFDS.Xml.newDocument("IntRateCfgDetl");
		IFDS.Xml.addSingleNode(segXML, 'detlUUID', segment.get('detlUUID'));
		IFDS.Xml.addSingleNode(segXML, 'intSegment', segment.get('code'));
		IFDS.Xml.addSingleNode(segXML, 'seq', segment.get('seq'));
		IFDS.Xml.addSingleNode(segXML, 'valueType', segment.get('valueType'));
		IFDS.Xml.addSingleNode(segXML, 'configValue', segment.get('configValue'));
		IFDS.Xml.addSingleNode(segXML, 'version', segment.get('version'));
		IFDS.Xml.addSingleNode(segXML, 'updMode', action);
		return segXML
	}
	
	function createIntRateCfgXML(xml)
	{
		var updMode = IFDS.Xml.getNodeValue(xml, 'updMode');
		
		var intRateXML = IFDS.Xml.newDocument("IntRateCfg");
		IFDS.Xml.addSingleNode(intRateXML, 'intRateCfgUUID', IFDS.Xml.getNodeValue(xml, 'intRateCfgUUID'));
		IFDS.Xml.addSingleNode(intRateXML, 'intRateCfgCode', IFDS.Xml.getNodeValue(xml, 'intRateCfgCode'));
		IFDS.Xml.addSingleNode(intRateXML, 'fundCategory', IFDS.Xml.getNodeValue(xml, 'fundCategory'));
		IFDS.Xml.addSingleNode(intRateXML, 'fundCategoryDesc', IFDS.Xml.getNodeValue(xml, 'fundCategoryDesc'));
		IFDS.Xml.addSingleNode(intRateXML, 'intCalcMthd', IFDS.Xml.getNodeValue(xml, 'intCalcMthd'));
		IFDS.Xml.addSingleNode(intRateXML, 'intCalcMthdDesc', IFDS.Xml.getNodeValue(xml, 'intCalcMthdDesc'));
		IFDS.Xml.addSingleNode(intRateXML, 'deff', IFDS.Xml.getNodeValue(xml, 'deff'));
		IFDS.Xml.addSingleNode(intRateXML, 'stopDate', IFDS.Xml.getNodeValue(xml, 'stopDate'));
		IFDS.Xml.addSingleNode(intRateXML, 'version', '0');
		IFDS.Xml.addSingleNode(intRateXML, 'inUsed', 'no');
		IFDS.Xml.addSingleNode(intRateXML, 'updMode', IFDS.Xml.getNodeValue(xml, 'updMode'));
		
		var intRateDetlsXML = IFDS.Xml.addSingleNode(intRateXML, 'IntRateCfgDetls');
		var intRateDetlXML = IFDS.Xml.addSingleNode(intRateDetlsXML, 'IntRateCfgDetl');
		
		IFDS.Xml.addSingleNode(intRateDetlXML, 'detlUUID', 'tmpDetlUUID' + (++_runningIntRateDetlUUID));
		IFDS.Xml.addSingleNode(intRateDetlXML, 'intSegment', 'BR');
		IFDS.Xml.addSingleNode(intRateDetlXML, 'seq', '1');
		IFDS.Xml.addSingleNode(intRateDetlXML, 'valueType', 'Code');
		IFDS.Xml.addSingleNode(intRateDetlXML, 'configValue', '');
		IFDS.Xml.addSingleNode(intRateDetlXML, 'version', '0');
		IFDS.Xml.addSingleNode(intRateDetlXML, 'updMode', _ADD);
		
		return intRateXML
	}
	
	function loadAddOnIntRateCfgElements(xml)
	{
	}
	
	function loadMapping()
	{
		// Load Fund Category
		_fundCatsMapping = new Object;
		var fundCatXMLs = IFDS.Xml.getNodes(_intRateXML, "//List[@listName='FundCategory']/Element");
		Ext.each(fundCatXMLs, function(fundCatXML){
			_fundCatsMapping[IFDS.Xml.getNodeValue(fundCatXML, "code")] = IFDS.Xml.getNodeValue(fundCatXML, "value");
		});
		
		// Load CalcMthds Mapping
		_calcMthdsMapping = new Object;
		var calcMthdXMLs = IFDS.Xml.getNodes(_intRateXML, "//List[@listName='IntCalcMthds']/Element");
		Ext.each(calcMthdXMLs, function(calcMthdXML){
			_calcMthdsMapping[IFDS.Xml.getNodeValue(calcMthdXML, "code")] = IFDS.Xml.getNodeValue(calcMthdXML, "value");
		});
		
		// Load IntSegments Mapping
		_intSegsMapping = new Object;
		var intSegXMLs = IFDS.Xml.getNodes(_intRateXML, "//List[@listName='IntSegments']/Element");
		Ext.each(intSegXMLs, function(intSegXML){
			_intSegsMapping[IFDS.Xml.getNodeValue(intSegXML, "code")] = IFDS.Xml.getNodeValue(intSegXML, "value");
		});
		
		// Load ConfigValue Mapping
		_configValuesMapping = new Object;
		_configCodesMapping = new Object;
		var configValueXMLs = IFDS.Xml.getNodes(_intRateXML, "//List[@listName='ConfigValues']/Element");
		_configCodesMapping[''] = '';
		Ext.each(configValueXMLs, function(configValueXML){
			_configValuesMapping[IFDS.Xml.getNodeValue(configValueXML, "code").toLowerCase()] = IFDS.Xml.getNodeValue(configValueXML, "value");
			_configCodesMapping[IFDS.Xml.getNodeValue(configValueXML, "code").toLowerCase()] = IFDS.Xml.getNodeValue(configValueXML, "code");
		});
		
		// Load CommRed Mapping
		_commRedsMapping = new Object;
		var commRedXMLs = IFDS.Xml.getNodes(_intRateXML, "//List[@listName='ConfigValues-CR']/Element");
		Ext.each(commRedXMLs, function(commRedXML){
			_commRedsMapping[IFDS.Xml.getNodeValue(commRedXML, "code")] = IFDS.Xml.getNodeValue(commRedXML, "value");
			_configCodesMapping[IFDS.Xml.getNodeValue(commRedXML, "code").toLowerCase()] = IFDS.Xml.getNodeValue(commRedXML, "code");
		});
		
		// Load List Selection
		_listSelsMapping = new Object;
		var listSelXMLs = IFDS.Xml.getNodes(_intRateXML, "//ListSelection");
		Ext.each(listSelXMLs, function(listSelXML){
			_listSelsMapping[listSelXML.getAttribute('id')] = IFDS.Xml.getNodeValue(listSelXML, ".");
		});
		
	}
	
	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function clearSelector(name)
	{
		_resources.selectors[name].availableGrid.getStore().removeAll();
		_resources.selectors[name].availableGrid.disableAllButtons();
		_resources.selectors[name].selectedGrid.getStore().removeAll();
		_resources.selectors[name].selectedGrid.disableAllButtons();
		_resources.selectors[name].intRateCfgUUID = null;
	}
	
	function updateIntRateButtons()
	{
		var grid = _resources.grids['intRateCfgGrid'];
		if(_selectedIntRate)
		{
			if(isStopped(_selectedIntRate.get('stopDate'))){
				grid.disableButton('modBtn');
				grid.disableButton('delBtn');
			}else{
				if (_permissions[_MOD] )
					grid.enableButton('modBtn');
				
				if (_permissions[_DEL])
					grid.enableButton('delBtn');
			}
			if(_selectedIntRate.get('updMode') == _ADD){
				grid.disableButton('adminBtn');
				grid.disableButton('historyBtn');
				grid.enableButton('modBtn');
				grid.enableButton('delBtn');
				
			}else{
				grid.enableButton('adminBtn');
				grid.enableButton('historyBtn');
			}
		}else{
			grid.disableButton('modBtn');
			grid.disableButton('delBtn');
			grid.disableButton('adminBtn');
			grid.disableButton('historyBtn');
		}
		
		if (_permissions[_ADD])
			grid.enableButton('addBtn');
	}
	
	function updateSegmentButtons(selModel)
	{
		var record = selModel.getSelected();
		var store = _resources.selectors['intSegSelector'].selectedGrid.getStore();
		var index = store.indexOf(record);
		
		if(index==0)
		{ 
			// User is not allowed to move down the Base Rate segment
			_resources.selectors['intSegSelector'].removeBtn.disable();
			_resources.selectors['intSegSelector'].moveDownBtn.disable();
		}
		if(index==1) _resources.selectors['intSegSelector'].moveUpBtn.disable();

		// Edit button
		if(record && (record.get('valueType')!='' || record.get('code')=='MV'))
		{
			_resources.selectors['intSegSelector'].selectedGrid.enableButton('edtBtn');
		}else{
			_resources.selectors['intSegSelector'].selectedGrid.disableButton('edtBtn');
		}
	}
	
	function loadItemSelector(selectedIntRate)
	{	
		var intRateCfgUUID = selectedIntRate.get('intRateCfgUUID');
		var selector = _resources.selectors['intSegSelector'];

		clearSelector('intSegSelector');

		selector.loadAvailableData(
			filterElemntByControl(getList('IntSegments'), getControl('IntSegments-' + selectedIntRate.get('fundCategory')))
		);
		
		var selectedIntSegXMLs = IFDS.Xml.getNodes(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + intRateCfgUUID + "']/IntRateCfgDetls/IntRateCfgDetl");
		if(selectedIntSegXMLs)
		{
			Ext.each(selectedIntSegXMLs, function(selectedIntSegXML){
				var segCode = IFDS.Xml.getNodeValue(selectedIntSegXML, 'intSegment');
				var updMode = IFDS.Xml.getNodeValue(selectedIntSegXML, 'updMode');
				var records = selector.availableGrid.getAllRecords();
				var matched = false;
				for (var r = 0; r < records.length; r++){
					if(segCode == records[r].get('code'))
					{
						records[r].set("detlUUID", IFDS.Xml.getNodeValue(selectedIntSegXML, 'detlUUID'));
						records[r].set("seq", IFDS.Xml.getNodeValue(selectedIntSegXML, 'seq'));
						records[r].set("valueType", IFDS.Xml.getNodeValue(selectedIntSegXML, 'valueType'));
						records[r].set("configValue", IFDS.Xml.getNodeValue(selectedIntSegXML, 'configValue'));
						records[r].set("configValueDisplay", getConfigValueDisplay(selectedIntRate.get('fundCategory'), segCode, IFDS.Xml.getNodeValue(selectedIntSegXML, 'configValue')));
						records[r].set("version", IFDS.Xml.getNodeValue(selectedIntSegXML, 'version'));
						records[r].set("updMode", updMode);
						records[r].set("errMsg", IFDS.Xml.getNodeValue(selectedIntSegXML, 'errMsg'));
						if(updMode != _DEL)
						{ 
							selector.addToSelected([records[r]]);
							matched = true;
						}
						break;
					}
				}
				if(!matched){
					var updModeNode = IFDS.Xml.getNode(selectedIntSegXML, 'updMode');
					if(!updModeNode){
						IFDS.Xml.addSingleNode(selectedIntSegXML, 'updMode', _DEL);
					}else{
						IFDS.Xml.setNodeValue(updModeNode, _DEL);
					}
				}
			})
		}else{
			// Load default segments
			var segCode = 'BR'; //default segment
			var records = selector.availableGrid.getAllRecords();
			for (var r = 0; r < records.length; r++){
				if(segCode == records[r].get('code'))
				{
					records[r].set("detlUUID", 'tmpDetlUUID' + (++_runningIntRateDetlUUID));
					records[r].set("seq", "1");
					records[r].set("valueType", "Code");
					records[r].set("configValue", "");
					records[r].set("version", "0");
					records[r].set("updMode", _ADD);
					records[r].set("errMsg", "");
					selector.addToSelected([records[r]]);
					break;
				}
			}
		}
		
		// Load default value to available grid
		var records = selector.availableGrid.getAllRecords();
		Ext.each(records, function(record){
			if(!record.selected && record.get('detlUUID')=="")
			{
				record.set("detlUUID", 'tmpDetlUUID' + (++_runningIntRateDetlUUID));
				record.set("seq", "0");
				record.set("valueType", getValueType(record.get('code')));
				record.set("configValue", (record.get('code')=="MV")?_MVDisplayValue:"");
				record.set("version", "0");
				record.set("updMode", _UNCH);
				record.set("errMsg", "");
			}
		});
		
		selector.availableGrid.getStore().commitChanges();
		selector.selectedGrid.getStore().commitChanges();
		selector.selectedGrid.getStore().sort('seq', 'ASC');

		if (_permissions[_ADD] || _permissions[_MOD] || _permissions[_DEL]) 
		{
		  if (_selectedIntRate.get('inUsed')=='yes' || isStopped(_selectedIntRate.get('stopDate'))){			
				selector.availableGrid.getSelectionModel().lock();
				selector.selectedGrid.getSelectionModel().lock();
			}
			else{			
				selector.availableGrid.getSelectionModel().unlock();
				selector.selectedGrid.getSelectionModel().unlock();		
				if (selector.availableGrid.getStore().getCount() > 0)
						selector.availableGrid.getSelectionModel().selectFirstRow();
					
				if (selector.selectedGrid.getStore().getCount() > 0)
						selector.selectedGrid.getSelectionModel().selectFirstRow();	
			}	
		}
		else  {
			selector.availableGrid.getSelectionModel().lock();
			selector.selectedGrid.getSelectionModel().lock();
		}
			
	}
	
	function filterElemntByControl(list, control)
	{
		var xml = IFDS.Xml.cloneDocument(list);
		var eleXMLs = IFDS.Xml.getNodes(list, 'Element');
		var codeXMLs = IFDS.Xml.getNodes(control, 'code');
		var matched = false;
		Ext.each(eleXMLs, function(eleXML){
			var eleCode = IFDS.Xml.getNodeValue(eleXML, 'code');
			matched = false;
			for(i=0; i<codeXMLs.length; i++){
				var conCode = IFDS.Xml.getNodeValue(codeXMLs[i], '.');
				if(eleCode == conCode){
					matched = true;
					break;
				}
			}
			if(!matched){
				var remNode = IFDS.Xml.getNode(xml, "//Element[code='" + eleCode + "']");
				IFDS.Xml.deleteNode(remNode);
			}
		});

		return xml;
	}
	
	function isStopped(dateStr)
	{		
		return (DesktopWeb.Util.stringToDate(dateStr,DesktopWeb.Util.getDateDisplayFormat()) < _defaultObject['deffDateObj']);
	}

	function getConfigValueDisplay(fundCat, segment, value)
	{
		
		switch (segment)
		{
			case 'MV': return _MVDisplayValue; // Value type is blank
			case 'AR':
			case 'EB':
			case 'AB':
			case 'CR':
				return value; // Value type is Dec
			case 'VB':
			case 'AM':
				return _configValuesMapping[value.toLowerCase()]==null ? '': _configValuesMapping[value.toLowerCase()];
			/*
			case 'CR':
				return _commRedsMapping[value]==null ? '': _commRedsMapping[value];
			*/
			case 'BR':
				var brCodes = value.split(",");
				var display = "";
				Ext.each(brCodes, function(brCode){
					display += _configValuesMapping[brCode.toLowerCase()]==null ? "": _configValuesMapping[brCode.toLowerCase()] + ",";
				});
				display = display.substring(0, display.length-1);
				return display;
			default:
				return _translationMap['SegNotAvlbMsg'];
		}
	}
	
	function validateIntRateCfgUpdate(action, popup)
	{
		var xml = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(xml, 'updMode', action);
		IFDS.Xml.addSingleNode(xml, 'intRateCfgUUID', (action!=_ADD)?_selectedIntRate.get('intRateCfgUUID'):'tmpIntRateUUID' + (++_runningIntRateUUID));
		
		if(action!=_DEL)
		{
			IFDS.Xml.addSingleNode(xml, 'intRateCfgCode', popup.getField('intRateCfgCodeFld').getValue());
			IFDS.Xml.addSingleNode(xml, 'fundCategory', popup.getField('fundCategoryFld').getValue());			
			IFDS.Xml.addSingleNode(xml, 'intCalcMthd', popup.getField('intCalcTypeFld').getValue());			
			IFDS.Xml.addSingleNode(xml, 'deff', DesktopWeb.Util.dateToString(popup.getField('effDateFld').getValue()));
			IFDS.Xml.addSingleNode(xml, 'stopDate', DesktopWeb.Util.dateToString(popup.getField('stopDateFld').getValue()));
		}
		IFDS.Xml.addSingleNode(xml, 'version', (action==_ADD)?'0':_selectedIntRate.get('version'));
		
		var validateXML = IFDS.Xml.cloneDocument(xml);

		if(action!=_ADD)
		{
			var currIntRateXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
			if(currIntRateXML)
			{
				currUpdMode = IFDS.Xml.getNodeValue(currIntRateXML, "updMode");
				if(currUpdMode == _ADD)
				{
					if(action==_DEL)
					{
						successHandler();
						return;
					}else{
						IFDS.Xml.setNodeValue(IFDS.Xml.getNode(validateXML, 'updMode'), _ADD);
					}
				}
			}
		}

		sendValidation(_intRateVldService, validateXML, successHandler, errorHandler);
		
		function successHandler()
		{
			IFDS.Xml.addSingleNode(xml, 'fundCategoryDesc', popup.getField('fundCategoryFld').getValueDesc());
			IFDS.Xml.addSingleNode(xml, 'intCalcMthdDesc', popup.getField('intCalcTypeFld').getValueDesc());
			updateIntRateCfgLayout(xml);
			popup.hide();
		}
		
		function errorHandler(responseXML)
		{
			var popup = _resources.popups['intRateCfgUpdate'];	
			var contextErrors = IFDS.Xml.getNodes(responseXML, '//Errors/Error');
			Ext.each(contextErrors, function(contextError){
				var errorCode = IFDS.Xml.getNodeValue(contextError, 'errorCode');
				var errorText = IFDS.Xml.getNodeValue(contextError, 'text');
				switch (errorCode)
				{
					case '454': // 
						if(popup.getField('stopDateFld').isValid()) popup.getField('stopDateFld').markInvalid(errorText);
						break;
					case '1010':
						if(popup.getField('intRateCfgCodeFld').isValid()) popup.getField('intRateCfgCodeFld').markInvalid(errorText);
						break;
				}
			});	
		}
	}
	
	function validateIntRateCfgDetlUpdate(popup)
	{
		var configValue = '';
		switch(_selectedSegment.get('code'))
		{
			case 'BR':
				var configValueRecords = _resources.selectors['BRSegSelector'].getSelectedRecords();
				Ext.each(configValueRecords, function(record){
					configValue += record.get('code') + ',';
				});
				configValue = configValue.substring(0, configValue.length - 1);
				break;
			case 'VB':
			case 'AM':
			case 'CR':
				configValue = _resources.popups['intSegCodeUpdate'].getField('segCodeFld').getValue();
				break;
			case 'AR':
				configValue = _resources.popups['intSegDecUpdate'].getField('segDecFld').getValue();
				break;
			case 'EB':
			case 'AB':
				configValue = _resources.popups['intSegPerUpdate'].getField('segPerFld').getValue();
				break;
		}
		
		var xml = IFDS.Xml.newDocument('data');
		var updMode = _selectedSegment.get('updMode');
		
		if(!updMode || updMode.length<=0){ 
			updMode = 'MOD';
		}
		
		IFDS.Xml.addSingleNode(xml, 'updMode', updMode);
		IFDS.Xml.addSingleNode(xml, 'intRateCfgUUID', _selectedIntRate.get('intRateCfgUUID'));
		IFDS.Xml.addSingleNode(xml, 'detlUUID', _selectedSegment.get('detlUUID'));
		IFDS.Xml.addSingleNode(xml, 'seq', _selectedSegment.get('seq'));
		IFDS.Xml.addSingleNode(xml, 'intSegment', _selectedSegment.get('code'));
		IFDS.Xml.addSingleNode(xml, 'valueType', _selectedSegment.get('valueType'));
		IFDS.Xml.addSingleNode(xml, 'configValue', configValue);
		IFDS.Xml.addSingleNode(xml, 'version', _selectedSegment.get('version'));
		IFDS.Xml.addSingleNode(xml, 'fundCategory', _selectedIntRate.get('fundCategory'));
		
		var validateXML = IFDS.Xml.cloneDocument(xml);

		sendValidation(_intRateDetlVldService, validateXML, successHandler, errorHandler);
		
		function successHandler()
		{
			updateIntRateCfgDetlLayout(xml);
			popup.hide();
		}
		
		function errorHandler(responseXML)
		{
			// Error Handling
		}
	}
	
	function sendValidation(api, xml, successCallback, errorCallback)
	{

		DesktopWeb.Ajax.doSmartviewAjax(api, null, xml, responseHandler, _translationMap['ProcMsg_Validating']);
					
		function responseHandler(success, responseXML, contextErrors)
		{
			if (success)
			{
				successCallback();
			}
			else
			{												
				errorCallback(responseXML);				
			}			
		}
	}

	function updateIntRateCfgLayout(xml)
	{
		var updMode = IFDS.Xml.getNodeValue(xml, 'updMode');
		switch(updMode)
		{
			case _ADD:
				var newIntRateCfgsXML = IFDS.Xml.newDocument("IntRateCfgs");
				var newIntRateCfgXML = createIntRateCfgXML(xml);
				var intRateCfgsXML = IFDS.Xml.getNode(_intRateXML, '//IntRateCfgs');
				IFDS.Xml.appendNode(intRateCfgsXML, IFDS.Xml.cloneDocument(newIntRateCfgXML));
				
				IFDS.Xml.appendNode(newIntRateCfgsXML, newIntRateCfgXML);
				_resources.grids['intRateCfgGrid'].getStore().loadData(newIntRateCfgsXML, true);
				_resources.grids['intRateCfgGrid'].getSelectionModel().selectLastRow(false);
				_resources.grids['intRateCfgGrid'].focusRow(_selectedIntRateIndex);

				break;
			
			case _MOD: 
				var intRateXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
				var fundCategory = IFDS.Xml.getNodeValue(intRateXML, 'fundCategory');
				var newFundCategory = IFDS.Xml.getNodeValue(xml, 'fundCategory');
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'intRateCfgCode'), IFDS.Xml.getNodeValue(xml, 'intRateCfgCode'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'fundCategory'), IFDS.Xml.getNodeValue(xml, 'fundCategory'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'fundCategoryDesc'), IFDS.Xml.getNodeValue(xml, 'fundCategoryDesc'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'intCalcMthd'), IFDS.Xml.getNodeValue(xml, 'intCalcMthd'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'intCalcMthdDesc'), IFDS.Xml.getNodeValue(xml, 'intCalcMthdDesc'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'deff'), IFDS.Xml.getNodeValue(xml, 'deff'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'stopDate'), IFDS.Xml.getNodeValue(xml, 'stopDate'));
				
				var currUpdMode = IFDS.Xml.getNodeValue(intRateXML, 'updMode');
				if(currUpdMode)
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'updMode'), (currUpdMode==_ADD)?_ADD:_MOD);
				}else{
					IFDS.Xml.addSingleNode(intRateXML, 'updMode', _MOD);
				}
				
				clearSelectedIntRateErrMsg(intRateXML);
				
				_selectedIntRate.set('intRateCfgCode', IFDS.Xml.getNodeValue(xml, 'intRateCfgCode'));
				_selectedIntRate.set('fundCategory', IFDS.Xml.getNodeValue(xml, 'fundCategory'));
				_selectedIntRate.set('fundCategoryDesc', IFDS.Xml.getNodeValue(xml, 'fundCategoryDesc'));
				_selectedIntRate.set('intCalcMthd', IFDS.Xml.getNodeValue(xml, 'intCalcMthd'));
				_selectedIntRate.set('intCalcMthdDesc', IFDS.Xml.getNodeValue(xml, 'intCalcMthdDesc'));
				_selectedIntRate.set('deff', DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'deff')));
				_selectedIntRate.set('stopDate', DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'stopDate')));
				
				_resources.grids['intRateCfgGrid'].getStore().commitChanges();
				
				if(fundCategory!=newFundCategory){
					// Clear all configValue of segments
					var intRateCfgDetlXMLs = IFDS.Xml.getNodes(intRateXML, "IntRateCfgDetls/IntRateCfgDetl");
					Ext.each(intRateCfgDetlXMLs, function(intRateCfgDetlXML){
						var intSegment = IFDS.Xml.getNodeValue(intRateCfgDetlXML, "intSegment");
						var updModeDetlNode = IFDS.Xml.getNode(intRateCfgDetlXML, "updMode");
						IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateCfgDetlXML, 'configValue'), "");
						if(!updModeDetlNode){
							IFDS.Xml.addSingleNode(intRateCfgDetlXML, "updMode", (intSegment != 'BR')?_DEL:_MOD);
						}else{
							var updModeDetl = IFDS.Xml.getNodeValue(updModeDetlNode, ".");
							IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateCfgDetlXML, 'updMode'), (intSegment != 'BR')?_DEL:IFDS.Xml.getNodeValue(updModeDetlNode, "."));
						}
					});
					loadItemSelector(_selectedIntRate);
				}
				if(_selectedIntRate.get('inUsed')=='yes' || isStopped(_selectedIntRate.get('stopDate'))){
					_resources.selectors['intSegSelector'].availableGrid.getSelectionModel().lock();
					_resources.selectors['intSegSelector'].selectedGrid.getSelectionModel().lock();
				}else{
					_resources.selectors['intSegSelector'].availableGrid.getSelectionModel().unlock();
					_resources.selectors['intSegSelector'].selectedGrid.getSelectionModel().unlock();
				}
				
				break;
				
			case _DEL:
				var intRateXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
				var updMode = IFDS.Xml.getNodeValue(intRateXML, 'updMode');
				if(updMode)
				{
					if(updMode==_ADD)
					{
						IFDS.Xml.deleteNode(intRateXML);
					}else{
						IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'updMode'), _DEL);
					}
				}else{
					IFDS.Xml.addSingleNode(intRateXML, 'updMode', _DEL);
				}
				
				var inUsed = _selectedIntRate.get('inUsed');
				if(inUsed=='yes'){
					_selectedIntRate.set('stopDate', DesktopWeb.Util.getDateDisplayValue(_defaultObject['deff']));
					_resources.grids['intRateCfgGrid'].getStore().commitChanges();
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'stopDate'), _defaultObject['deff']);
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateXML, 'updMode'), _MOD);
				}else{
					_resources.grids['intRateCfgGrid'].getStore().remove(_selectedIntRate);
					_selectedIntRate = null;
					clearSelector('intSegSelector');
					_resources.grids['intRateCfgGrid'].getSelectionModel().selectFirstRow();
				}
				
				break;
		}
		updateUpdatesFlag();
	}
	
	function clearSelectedIntRateErrMsg(intRateCfgXML){
		var errMsgNode = IFDS.Xml.getNode(intRateCfgXML, "errMsg");
		if(errMsgNode){
			var errMsgDetlNodes = IFDS.Xml.getNodes(intRateCfgXML, "IntRateCfgDetls/IntRateCfgDetl/errMsg");
			if(errMsgDetlNodes.length>0){
				IFDS.Xml.setNodeValue(errMsgNode, _errInIntSeg);
				_selectedIntRate.set("errMsg", _errInIntSeg);
			}else{
				IFDS.Xml.deleteNode(errMsgNode);
				_selectedIntRate.set("errMsg", "");
			}
			_resources.grids['intRateCfgGrid'].getStore().commitChanges();
		}
	}
	
	function updateIntRateCfgDetlLayout(xml)
	{
		var currIntRateCfgXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
		var currIntRateCfgDetlXML = IFDS.Xml.getNode(currIntRateCfgXML, "IntRateCfgDetls/IntRateCfgDetl[detlUUID='" + _selectedSegment.get('detlUUID') + "']");
		var updMode = IFDS.Xml.getNodeValue(currIntRateCfgDetlXML, 'updMode');
		if(!updMode) IFDS.Xml.addSingleNode(currIntRateCfgDetlXML, 'updMode', _MOD);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currIntRateCfgDetlXML, 'configValue'), IFDS.Xml.getNodeValue(xml, 'configValue'));
		
		var errMsgDetlNode = IFDS.Xml.getNode(currIntRateCfgDetlXML, "errMsg");
		if(errMsgDetlNode)IFDS.Xml.deleteNode(errMsgDetlNode);
		
		updateIntRateCfgUpdMode(currIntRateCfgXML);
		
		_selectedSegment.set('configValue', IFDS.Xml.getNodeValue(xml, 'configValue'));
		_selectedSegment.set("configValueDisplay", getConfigValueDisplay(_selectedIntRate.get('fundCategory'), IFDS.Xml.getNodeValue(xml, 'intSegment'), IFDS.Xml.getNodeValue(xml, 'configValue')));
		_selectedSegment.set('errMsg', "");
		_resources.selectors['intSegSelector'].selectedGrid.getStore().commitChanges();
		
		clearSelectedIntRateErrMsg(currIntRateCfgXML);
		
		updateUpdatesFlag();
	}
	
	function updateIntRateCfgUpdMode(intRateCfgXML)
	{
		var updMode = IFDS.Xml.getNode(intRateCfgXML, 'updMode');
		if(!updMode){ 
			IFDS.Xml.addSingleNode(intRateCfgXML, 'updMode', _UNCH);
		}else{
			if(IFDS.Xml.getNodeValue(updMode, '.')=='')IFDS.Xml.setNodeValue(updMode, _UNCH);
		}
	}
	
	function loadBRSelector()
	{
		var selector = _resources.selectors['BRSegSelector'];
		clearSelector('BRSegSelector');

		selector.loadAvailableData(
			filterElemntByControl(getList('ConfigValues'), getControl('ConfigValues-' + _selectedIntRate.get('fundCategory') + 'BR'))
		);
		
		var brConfigValues = _selectedSegment.get('configValue');
		var brCodes = brConfigValues.split(",");
		var records = selector.availableGrid.getAllRecords();
		Ext.each(brCodes, function(brCode){
			for(var i=0; i<records.length; i++)
			{
				if(brCode.toLowerCase() == records[i].get('code').toLowerCase()){ 
					selector.addToSelected([records[i]]);
					break;
				}
			}
		});
	}
	
	function buildRequestXML()
	{
		var cloneDoc = null;
		var intRateCfgs = null;
		var intRateCfgDetls = null;
		var data = IFDS.Xml.newDocument("data");
		var requestXML = IFDS.Xml.addSingleNode(data, "IntRateCfgs");
		intRateCfgs = IFDS.Xml.getNodes(_intRateXML, "//IntRateCfgs/IntRateCfg[updMode='" + _DEL + "']");
		if(intRateCfgs)
		{
			Ext.each(intRateCfgs, function(intRateCfg){
				IFDS.Xml.addAttribute(intRateCfg, 'RecordSource', IFDS.Xml.getNodeValue(intRateCfg, 'intRateCfgUUID'));
				cloneDoc = IFDS.Xml.cloneDocument(intRateCfg);
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "intRateCfgCode"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "fundCategory"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "intCalcMthd"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "deff"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "stopDate"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "userName"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "modUser"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "modDate"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "inUsed"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "IntRateCfgDetls"));
				IFDS.Xml.appendNode(requestXML, cloneDoc);
			});
		}

		intRateCfgs = IFDS.Xml.getNodes(_intRateXML, "//IntRateCfgs/IntRateCfg[updMode='" + _MOD + "']");
		if(intRateCfgs)
		{
			Ext.each(intRateCfgs, function(intRateCfg){
				IFDS.Xml.addAttribute(intRateCfg, 'RecordSource', IFDS.Xml.getNodeValue(intRateCfg, 'intRateCfgUUID'));
				cloneDoc = IFDS.Xml.cloneDocument(intRateCfg);
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "userName"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "modUser"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "modDate"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "inUsed"));
				intRateCfgDetls = IFDS.Xml.getNodes(cloneDoc, "IntRateCfgDetls/IntRateCfgDetl[not(updMode)]");
				Ext.each(intRateCfgDetls, function(intRateCfgDetl){
					IFDS.Xml.deleteNode(intRateCfgDetl);
				});
				intRateCfgDetls = IFDS.Xml.getNodes(cloneDoc, "IntRateCfgDetls/IntRateCfgDetl");
				Ext.each(intRateCfgDetls, function(intRateCfgDetl){
					IFDS.Xml.addAttribute(intRateCfgDetl, 'RecordSource', IFDS.Xml.getNodeValue(intRateCfgDetl, 'detlUUID'));
				});
				IFDS.Xml.appendNode(requestXML, cloneDoc);
			});
		}

		intRateCfgs = IFDS.Xml.getNodes(_intRateXML, "//IntRateCfgs/IntRateCfg[updMode='" + _ADD + "']");
		if(intRateCfgs)
		{
			Ext.each(intRateCfgs, function(intRateCfg){
				IFDS.Xml.addAttribute(intRateCfg, 'RecordSource', IFDS.Xml.getNodeValue(intRateCfg, 'intRateCfgUUID'));
				cloneDoc = IFDS.Xml.cloneDocument(intRateCfg);
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "inUsed"));
				intRateCfgDetls = IFDS.Xml.getNodes(cloneDoc, "IntRateCfgDetls/IntRateCfgDetl");
				Ext.each(intRateCfgDetls, function(intRateCfgDetl){
					IFDS.Xml.addAttribute(intRateCfgDetl, 'RecordSource', IFDS.Xml.getNodeValue(intRateCfgDetl, 'detlUUID'));
				});
				IFDS.Xml.appendNode(requestXML, cloneDoc);
			});
		}

		intRateCfgs = IFDS.Xml.getNodes(_intRateXML, "//IntRateCfgs/IntRateCfg[updMode='" + _UNCH + "']");
		if(intRateCfgs)
		{
			Ext.each(intRateCfgs, function(intRateCfg){
				IFDS.Xml.addAttribute(intRateCfg, 'RecordSource', IFDS.Xml.getNodeValue(intRateCfg, 'intRateCfgUUID'));
				cloneDoc = IFDS.Xml.cloneDocument(intRateCfg);
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "intRateCfgCode"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "fundCategory"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "intCalcMthd"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "deff"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "stopDate"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "userName"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "modUser"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "modDate"));
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(cloneDoc, "inUsed"));
				intRateCfgDetls = IFDS.Xml.getNodes(cloneDoc, "IntRateCfgDetls/IntRateCfgDetl[not(updMode)]");
				Ext.each(intRateCfgDetls, function(intRateCfgDetl){
					IFDS.Xml.deleteNode(intRateCfgDetl);
				});
				intRateCfgDetls = IFDS.Xml.getNodes(cloneDoc, "IntRateCfgDetls/IntRateCfgDetl");
				Ext.each(intRateCfgDetls, function(intRateCfgDetl){
					IFDS.Xml.addAttribute(intRateCfgDetl, 'RecordSource', IFDS.Xml.getNodeValue(intRateCfgDetl, 'detlUUID'));
					var updMode = IFDS.Xml.getNodeValue(intRateCfgDetl, 'updMode');
					if(updMode==_DEL){
						IFDS.Xml.deleteNode(IFDS.Xml.getNode(intRateCfgDetl, "seq"));
						IFDS.Xml.deleteNode(IFDS.Xml.getNode(intRateCfgDetl, "valueType"));
						IFDS.Xml.deleteNode(IFDS.Xml.getNode(intRateCfgDetl, "configValue"));
					}
					if(updMode==_MOD || updMode==_DEL){
						IFDS.Xml.deleteNode(IFDS.Xml.getNode(intRateCfgDetl, "userName"));
						IFDS.Xml.deleteNode(IFDS.Xml.getNode(intRateCfgDetl, "modUser"));
						IFDS.Xml.deleteNode(IFDS.Xml.getNode(intRateCfgDetl, "modDate"));
					}
				});
				IFDS.Xml.appendNode(requestXML, cloneDoc);
			});
		}
		return data;
	}
	
	function getValueType(intSegment)
	{
		var valueType = '';
		switch (intSegment)
		{
			case 'BR': 
			case 'VB': 
			case 'AM':
			case 'CR':
				valueType = 'Code';
				break;
			case 'AR':
			case 'EB':
			case 'AB':
				valueType = 'Dec';
				break;
			default:
				valueType = '';
		}
		return valueType
	}
	
	function getList(listName)
	{
		return IFDS.Xml.getNode(_intRateXML, "//List[@listName='" + listName + "']");
	}
	
	function getControl(controlName)
	{
		return IFDS.Xml.getNode(_intRateXML, "//Control[@controlName='" + controlName + "']");
	}

	function storeContextErrors(errorNodes)
	{
		var firstIntRateErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			if(table == 'IntRateCfg')
			{
				var intRateCfgUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				
				// Update main XML
				var intRateCfgXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + intRateCfgUUID + "']");
				var errMsgNode = IFDS.Xml.getNode(intRateCfgXML, "errMsg");
				if(!errMsgNode){
					IFDS.Xml.addSingleNode(intRateCfgXML, 'errMsg', errMsg);
				}else{
					IFDS.Xml.setNodeValue(errMsgNode, errMsg);
				}
				
				// Update intRateCfgGrid
				var intRateCfgStore = _resources.grids['intRateCfgGrid'].getStore();
				var recordIndex = intRateCfgStore.find('intRateCfgUUID', intRateCfgUUID);
				if(recordIndex!=-1){
					var intRateCfgRecord = intRateCfgStore.getAt(recordIndex);
					intRateCfgRecord.set('errMsg', errMsg);
					intRateCfgStore.commitChanges();
					if(firstIntRateErrRecIndex==-1)firstIntRateErrRecIndex = recordIndex;
				}else{
					var errIntRateXML = IFDS.Xml.newDocument("IntRateCfgs");
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(intRateCfgXML, "updMode"), "");
					IFDS.Xml.appendNode(errIntRateXML, IFDS.Xml.cloneDocument(intRateCfgXML));
					intRateCfgStore.loadData(errIntRateXML, true);
					if(firstIntRateErrRecIndex==-1)firstIntRateErrRecIndex = intRateCfgStore.getCount - 1;
				}
			}else{
				var detlUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				
				// Update main XML
				var intRateCfgDetlXML = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgDetl[detlUUID='" + detlUUID + "']");
				IFDS.Xml.addSingleNode(intRateCfgDetlXML, 'errMsg', errMsg);
				
				var intRateCfgXML = intRateCfgDetlXML.parentNode.parentNode;
				var errMsg = IFDS.Xml.getNodeValue(intRateCfgXML, 'errMsg');
				if(errMsg == '')
				{
					// Update main XML
					IFDS.Xml.addSingleNode(intRateCfgXML, 'errMsg', _errInIntSeg);
					
					// Update intRateCfgGrid
					var intRateCfgUUID = IFDS.Xml.getNodeValue(intRateCfgXML, 'intRateCfgUUID');
					var intRateCfgStore = _resources.grids['intRateCfgGrid'].getStore();
					var recordIndex = intRateCfgStore.find('intRateCfgUUID', intRateCfgUUID);
					var intRateCfgRecord = intRateCfgStore.getAt(recordIndex);
					intRateCfgRecord.set('errMsg', _errInIntSeg);
					intRateCfgStore.commitChanges();
					if(firstIntRateErrRecIndex==-1)firstIntRateErrRecIndex = recordIndex;
				}
			}
		}
		if(firstIntRateErrRecIndex==-1)
		{
			_resources.grids['intRateCfgGrid'].getSelectionModel().selectFirstRow();
		}else{
			_resources.grids['intRateCfgGrid'].getSelectionModel().selectRow(firstIntRateErrRecIndex);
			_resources.grids['intRateCfgGrid'].focusRow(_selectedIntRateIndex);
		}
	}
	
	function updateUpdatesFlag()
	{
		var updModeNodes = IFDS.Xml.getNodes(_intRateXML, "//updMode");
		if(updModeNodes.length == 0)
		{
			_self.updatesFlag = false;
		}else{
			_self.updatesFlag = true;
		}
	}
	
	function clearContextErrors(intRateCfgUUID, intRateCfgDetlUUID){
		var intRateStore = _resources.grids['intRateCfgGrid'].getStore();
		if(intRateCfgUUID){
			if(!intRateCfgDetlUUID){
				
			}else{
			}
		}else{
			var errMsgNodes = IFDS.Xml.getNodes(_intRateXML, "//errMsg");
			Ext.each(errMsgNodes, function(errMsgNode){
				IFDS.Xml.deleteNode(errMsgNode);
			});
			_resources.grids['intRateCfgGrid'].getStore().loadData(_intRateXML);
		}
	}
	
	function loadMoreIntRate(moreIntRateXML)
	{
		var cloneMoreIntRateXML = IFDS.Xml.cloneDocument(moreIntRateXML);
		var intRateCfgsNode = IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs");
		var moreIntRateNodes = IFDS.Xml.getNodes(moreIntRateXML, "//IntRateCfg");
		Ext.each(moreIntRateNodes, function(moreIntRateNode){
			IFDS.Xml.appendNode(intRateCfgsNode, moreIntRateNode);
		});
		_resources.grids['intRateCfgGrid'].getStore().loadData(cloneMoreIntRateXML, true);
		_resources.grids['intRateCfgGrid'].focusRow(_selectedIntRateIndex);
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			loadIntRate();
		}
		
		,intRateCfgUpdate: function(action, popup)
		{
			validateIntRateCfgUpdate(action, popup);
		}
				
		,intRateCfgDetlUpdate: function(popup)
		{
			validateIntRateCfgDetlUpdate(popup);
		}
				
		,doUpdate: function()
		{
			clearContextErrors();
			var updateStatus = null;
			var requestXML = buildRequestXML();
			DesktopWeb.Ajax.doSmartviewUpdate(_intRateProcessService, null, IFDS.Xml.cloneDocument(requestXML), responseHandler, _translationMap['ProcMsg_Saving']);			
			
			function responseHandler(success, responseXML, contextErrors)
			{	
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}else{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}
		
		,setSelectedIntRate: function(record, index)
		{
			_selectedIntRate = record;
			_selectedIntRateIndex = index;
			
			updateIntRateButtons();
			
			loadItemSelector(record);
		}
		
		,setDeselectedIntRate: function()
		{
		}
		
		,setSelectedSegment: function(record, index)
		{
			_selectedSegment = record;
			
		}
		
		,setDeselectedSegment: function()
		{
		}
		
		,getIntRateXML: function()
		{
			return _intRateXML;
		}

		,getSelectedIntRate: function()
		{
			return _selectedIntRate;
		}

		,getSelectedIntRateXML: function()
		{
			return IFDS.Xml.getNode(_intRateXML, "//IntRateCfgs/IntRateCfg[intRateCfgUUID='" + _selectedIntRate.get('intRateCfgUUID') + "']");
		}

		,getSelectedSegment: function()
		{
			return _selectedSegment;
		}
		
		,getDisplay: function(type, value)
		{
			/**
			 *	_fundCatMapping: Fund Category Collection
			 *	_calcMthdsMapping: Calculation Method Collection
			 *	_intSegsMapping: Interest Segment Collection
			 *	_listSelMapping: List Selection Collection
			 *
			 **/
			switch (type)
			{
				case 'FundCategory':
					return _fundCatsMapping[value]==null ? '': _fundCatsMapping[value];
				case 'IntCalcType':
					return _calcMthdsMapping[value]==null ? '': _calcMthdsMapping[value];
				case 'IntSegment':
					return _intSegsMapping[value]==null ? '': _intSegsMapping[value];
				default:
					return _translationMap['TypeNotAvlbMsg'];
			}
		}
		
		,loadIntCalcMthdList: function(fundCategoryCode)
		{
			var popup = _resources.popups['intRateCfgUpdate'];	
			popup.getField('intCalcTypeFld').clearValue();
			popup.getField('intCalcTypeFld').getStore().loadData(
				filterElemntByControl(getList('IntCalcMthds'), getControl('IntCalcMthds-' + fundCategoryCode))
			);
		}
				
		,openActionPopup: function(name, action)
		{
			if(action == _DEL && _selectedIntRate.get('inUsed')=='yes' && isStopped(_selectedIntRate.get('stopDate'))){
				DesktopWeb.Util.displayError(_translationMap['IntRateConfigTrmMsg']);
			}else{
				var popup = _resources.popups[name];	
				popup.show();					
				popup.init(action);			
				updateIntRateButtons();
			}
		}
		
		,openSegmentEditPopup: function()
		{
			var popupName = null;
			switch (_selectedSegment.get('code'))
			{
				case 'BR':
					popupName = 'intSegBRUpdate';
					break;
				case 'VB':
				case 'AM':
				case 'CR':
				case 'MV':
					popupName = 'intSegCodeUpdate';
					break;
				case 'AR':
					popupName = 'intSegDecUpdate';
					break;
				case 'EB':
				case 'AB':
					popupName = 'intSegPerUpdate';
					break;
			}
			
			var popup = _resources.popups[popupName];	
			popup.show();
			popup.init(_selectedSegment);
		}
		
		,getDefaultCalcMthd: function()
		{
			return IFDS.Xml.getNodeValue(_intRateXML, "//ListSelection[@id='IntCalcMthds']");
		}
		
		,getValueList: function(listName)
		{
			return getList(listName);
		}
		
		,getDefault: function(fieldName)
		{
			return _defaultObject[fieldName];
		}
		
		,getCodeMapping: function(code)
		{
			return _configCodesMapping[code.toLowerCase()];
		}
		
		,loadBRDetail: function()
		{
			loadBRSelector();
		}
		
		,loadConfigValueList: function(comboFld, fundCategory, segmentCode)
		{
			var configValueList = null;
			if(segmentCode == 'CR'){
				configValueList = getList('ConfigValues-CR');
			}else if(segmentCode == 'MV'){
				configValueList = IFDS.Xml.stringToXML("<List listName='MVSegment'><Element><code></code><value>" + _MVDisplayValue + "</value></Element></List>");
			}else{
				configValueList = filterElemntByControl(getList('ConfigValues'), getControl('ConfigValues-' + fundCategory + segmentCode));
			}
			comboFld.getStore().loadData(configValueList);
		}
		
		,openHistoryPopup: function(recType)
		{
			var viewParam = {};
			var historyName = null;
			viewParam['auditType'] = 'IntRateConfig';
			viewParam['searchValue1'] = _selectedIntRate.get('intRateCfgUUID');
			historyName = _translationMap['InterestRateConfig']+ ' - ' +_translationMap['History'];
			_resources.popups['history'].init(historyName, _historyService, viewParam, true);
			_resources.popups['history'].show();
			
		}
		
		,openAdminPopup: function(recType)
		{					
			var title = _translationMap['InterestRateConfig']+ ' - ' +_translationMap['Admin']
			var xml = this.getSelectedIntRateXML();
			var adminData = {};
			adminData['userName'] = IFDS.Xml.getNodeValue(xml, 'userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'procDate'));
			adminData['modUser'] = IFDS.Xml.getNodeValue(xml, 'modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}
		,doReload: function()
		{
			var paramXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(paramXML, 'startRecNum', _nextStartRecNum);
			IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

			DesktopWeb.Ajax.doSmartviewAjax(_intRateReloadService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

			function responseHandler(success, responseXML)
			{	
				if (success)
				{
					loadMoreIntRate(responseXML);
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					if (_nextStartRecNum)
					{
						_resources.grids['intRateCfgGrid'].enableButton('moreBtn');
					}
					else
					{
						_resources.grids['intRateCfgGrid'].disableButton('moreBtn');
					}
				}
			}
		}
	}	
}	