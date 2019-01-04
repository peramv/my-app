/*********************************************************************************************
 * @file	CommRed.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Commission Reduction screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  04 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _ADD = 'ADD'
	var _MOD = 'MOD'
	var _DEL = 'DEL';
	
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var _selectedCommRed = null;
	var _selectedCommRedIndex = null;
	var _selectedCommRedDetl = null;
	var _commRedXML = null;
	var _commRedDetlXML = null;
	var _commRedReqXML = null;

	var _defaultObject = null
	
	var _commRedInitService = 'dtCommReductionInit';
	var _commRedReloadService = 'dtCommReductionReload';
	var _commRedProcessService = 'dtCommReductionProc';
	var _commRedValidateService = 'dtCommRedMstrVld';
	var _commRedDetlValidateService = 'dtCommRedDetlVld';
	var _historyService = 'dtHistoricalInfo';
	
	var _runningCommRedId = 0;
	var _runningCommRedDetlId = 0;
	
	var _nextStartRecNum = null;
	var _requestRecNum = 25;
	
	// PRIVATE METHODS ****************************************	
	function loadCommRed()
	{
		var paramXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', _nextStartRecNum);
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

		DesktopWeb.Ajax.doSmartviewAjax(_commRedInitService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{	
			if (success)
			{
				_commRedXML = responseXML;
			}else{
				_commRedXML = null;
			}
			if(_commRedXML)
			{
				loadDefaultObject(IFDS.Xml.getNode(_commRedXML, '//Default'));
				loadAddOnCommRedElements(_commRedXML);
				displayCommRed();
			}
		}		
	}
	
	function loadCommRedDetl(commRedUUID)
	{
		_commRedDetlXML = getCommRedDetlsXML(commRedUUID);
		
		_selectedCommRedDetl = null;

		if(_commRedDetlXML)
		{
			_resources.grids['commRedDetlGrid'].getStore().loadData(_commRedDetlXML);
		}
		updateCommRedDetlButtons();
		
	}
	
	function displayCommRed()
	{
		clearGrid('commRedGrid');
		
		if(_commRedXML){
			_resources.grids['commRedGrid'].getStore().loadData(_commRedXML);
			_resources.grids['commRedGrid'].getSelectionModel().selectFirstRow();
			_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(_commRedXML);
			if (_nextStartRecNum)
			{
				_resources.grids['commRedGrid'].enableButton('moreBtn');
			}
			else
			{
				_resources.grids['commRedGrid'].disableButton('moreBtn');
			}
		}
		updateCommRedButtons();
	}
	
	function displayCommRedDetl()
	{
		clearGrid('commRedDetlGrid');
		loadCommRedDetl(_selectedCommRed.get('commRedUUID'));
	}
	
	function updateCommRedButtons()
	{
		var grid = _resources.grids['commRedGrid'];
		if(_selectedCommRed)
		{
			if(isStopped(_selectedCommRed.get('stopDate'))){
				grid.disableButton('modBtn');
				grid.disableButton('delBtn');
			}else{
				grid.enableButton('modBtn');
				grid.enableButton('delBtn');
			}
			
			if(_selectedCommRed.get('updMode') == _ADD)
			{
				grid.disableButton('adminBtn');
				grid.disableButton('historicalBtn');
			}else{
				grid.enableButton('adminBtn');
				grid.enableButton('historicalBtn');
			}
		}else{
			grid.disableButton('modBtn');
			grid.disableButton('delBtn');
			grid.disableButton('historicalBtn');
		}
		grid.enableButton('addBtn');
	}
	
	function updateCommRedDetlButtons()
	{
		var grid = _resources.grids['commRedDetlGrid'];
		if(_selectedCommRed.get('inUsed') == 'no' && !isStopped(_selectedCommRed.get('stopDate')))
		{
			if(_selectedCommRedDetl)
			{
				grid.enableButton('modBtn');
				grid.enableButton('delBtn');
				
				if(_selectedCommRedDetl.get('updMode') == _ADD)
				{
					grid.disableButton('adminBtn');
					grid.disableButton('historicalBtn');
				}else{
					grid.enableButton('adminBtn');
					grid.enableButton('historicalBtn');
				}
				
			}else{
				grid.disableButton('modBtn');
				grid.disableButton('delBtn');
			}
			grid.enableButton('addBtn');
		}else{
			grid.disableButton('addBtn');
			grid.disableButton('modBtn');
			grid.disableButton('delBtn');
			if(_selectedCommRedDetl)
			{
				if(_selectedCommRedDetl.get('updMode') == _ADD)
				{
					grid.disableButton('adminBtn');
					grid.disableButton('historicalBtn');
				}else{
					grid.enableButton('adminBtn');
					grid.enableButton('historicalBtn');
				}
			}
		}
	}
	
	function isStopped(dateStr)
	{
		return DesktopWeb.Util.stringToDate(dateStr) < DesktopWeb.Util.stringToDate(_defaultObject['deff']);
	}
	
	function loadDefaultObject(defaultXML)
	{
		if(defaultXML)
		{
			if(!_defaultObject) _defaultObject = new Object;
			_defaultObject['deff'] = IFDS.Xml.getNodeValue(defaultXML, 'defDeff');
			_defaultObject['stopDate'] = IFDS.Xml.getNodeValue(defaultXML, 'defStopDate');
			_defaultObject['commRedRate'] = '0.0000';
			_defaultObject['intIncRate'] = '0.0000';
		}
	}
	
	function loadAddOnCommRedElements(xml)
	{
		// Build additional element
	}
	
	function validateCommRedUpdate(action, popup)
	{
		var xml = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(xml, 'updMode', action);
		IFDS.Xml.addSingleNode(xml, 'commRedUUID', (action!=_ADD)?_selectedCommRed.get('commRedUUID'):'tmpCommRedUUID' + (++_runningCommRedId));
		IFDS.Xml.addSingleNode(xml, 'commRedCode', popup.getField('commRedCodeFld').getValue());
		IFDS.Xml.addSingleNode(xml, 'deff', DesktopWeb.Util.dateToString(popup.getField('effDateFld').getValue()));
		IFDS.Xml.addSingleNode(xml, 'stopDate', DesktopWeb.Util.dateToString(popup.getField('stopDateFld').getValue()));
		IFDS.Xml.addSingleNode(xml, 'version', (action==_ADD)?'0':_selectedCommRed.get('version'));
		
		var validateXML = IFDS.Xml.cloneDocument(xml);
		if(_commRedReqXML)
		{
			if(action!=_ADD)
			{
				var currCommRedReqXML = IFDS.Xml.getNode(_commRedReqXML, "//CommReds/CommRed[commRedUUID='" + _selectedCommRed.get('commRedUUID') + "']");
				if(currCommRedReqXML)
				{
					currUpdMode = IFDS.Xml.getNodeValue(currCommRedReqXML, "updMode");
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
		}
		
		sendValidation(_commRedValidateService, validateXML, successHandler, errorHandler);
		
		function successHandler()
		{
			commRedUpdateLayout(buildCommRedXML(xml));
			popup.hide();
		}
		
		function errorHandler(responseXML)
		{
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
						if(popup.getField('commRedCodeFld').isValid()) popup.getField('commRedCodeFld').markInvalid(errorText);
						break;
				}
			});	
		}

	}
	
	function buildCommRedXML(xml)
	{
		var updMode = IFDS.Xml.getNodeValue(xml, '//updMode');
		var dataXML = IFDS.Xml.newDocument('data');
		var commRedXML = IFDS.Xml.addSingleNode(dataXML, 'CommRed');
		IFDS.Xml.addSingleNode(commRedXML, 'updMode', updMode);
		IFDS.Xml.addSingleNode(commRedXML, 'updSeq', (updMode==_ADD)?'3':(updMode==_MOD)?'2':(updMode==_DEL)?'1':'0');
		IFDS.Xml.addSingleNode(commRedXML, 'commRedUUID', IFDS.Xml.getNodeValue(xml, '//commRedUUID'));
		IFDS.Xml.addAttribute(commRedXML, 'RecordSource', IFDS.Xml.getNodeValue(xml, '//commRedUUID'));
		
		if(updMode==_ADD)
		{
			IFDS.Xml.addSingleNode(commRedXML, 'inUsed', 'no');
		}

		IFDS.Xml.addSingleNode(commRedXML, 'commRedCode', IFDS.Xml.getNodeValue(xml, '//commRedCode'));
		IFDS.Xml.addSingleNode(commRedXML, 'deff', IFDS.Xml.getNodeValue(xml, '//deff'));
		IFDS.Xml.addSingleNode(commRedXML, 'stopDate', IFDS.Xml.getNodeValue(xml, '//stopDate'));
		IFDS.Xml.addSingleNode(commRedXML, 'version', IFDS.Xml.getNodeValue(xml, '//version'));
		IFDS.Xml.addSingleNode(commRedXML, 'CommRedDetls');

		return dataXML;
	}
	
	function commRedUpdateLayout(xml)
	{
		var updMode = IFDS.Xml.getNodeValue(xml, '//updMode');
		switch(updMode)
		{
			case _ADD:
			{
				// Update main XML
				IFDS.Xml.addSingleNode(xml, 'CommRedDetls');
				IFDS.Xml.appendNode(IFDS.Xml.getNode(_commRedXML, "//CommReds"), IFDS.Xml.cloneDocument(IFDS.Xml.getNode(xml, '//CommRed')));
				
				// Update commRedGrid
				_resources.grids['commRedGrid'].getStore().loadData(xml, true);
				_resources.grids['commRedGrid'].getSelectionModel().selectLastRow(false);
				_resources.grids['commRedGrid'].focusRow(_selectedCommRedIndex);
				break;
			}
			case _MOD:
			{
				var commRedCode = IFDS.Xml.getNodeValue(xml, 'CommRed/commRedCode');
				var deff = IFDS.Xml.getNodeValue(xml, 'CommRed/deff');
				var stopDate = IFDS.Xml.getNodeValue(xml, 'CommRed/stopDate');
				
				// Update main XML
				var commRedXML = IFDS.Xml.getNode(_commRedXML, "//CommReds/CommRed[commRedUUID='" + _selectedCommRed.get('commRedUUID') + "']");
				IFDS.Xml.replaceSingleNode(commRedXML, 'commRedCode', commRedCode);
				IFDS.Xml.replaceSingleNode(commRedXML, 'deff', deff);
				IFDS.Xml.replaceSingleNode(commRedXML, 'stopDate', stopDate);
				
				// Update commRedGrid
				_selectedCommRed.set('commRedCode', commRedCode);
				_selectedCommRed.set('deff', DesktopWeb.Util.getDateDisplayValue(deff));
				_selectedCommRed.set('stopDate', DesktopWeb.Util.getDateDisplayValue(stopDate));
				_resources.grids['commRedGrid'].getStore().commitChanges();
				break;
			}
			case _DEL:
			{
				var inused = _selectedCommRed.get('inUsed');
				// Update main XML
				var commRedXML = IFDS.Xml.getNode(_commRedXML, "//CommReds/CommRed[commRedUUID='" + _selectedCommRed.get('commRedUUID') + "']");
				if(inused == 'yes')
				{
					// Just change a stop date to a default deff
					IFDS.Xml.replaceSingleNode(commRedXML, 'stopDate', _defaultObject['deff']);
				}else{
					IFDS.Xml.deleteNode(commRedXML);
				}
				
				// Update commRedGrid
				if(inused == 'yes')
				{
					// Just change a stop date to a default deff
					_selectedCommRed.set('stopDate', _defaultObject['deff']);
					_resources.grids['commRedGrid'].getStore().commitChanges();
				}else{
					_resources.grids['commRedGrid'].getStore().remove(_selectedCommRed);

					// Clear current object that related to the commRed
					_selectedCommRed = null;
					clearGrid('commRedDetlGrid');
					if(_resources.grids['commRedGrid'].getStore().getCount() > 0)
					{
						_resources.grids['commRedGrid'].getSelectionModel().selectFirstRow();
					}
				}
				
				break;
			}
		}
		
		updateCommRedButtons();

		addCommRedXMLRequest(IFDS.Xml.getNode(xml, '//CommRed'));
		
	}
	
	function addCommRedXMLRequest(xml)
	{
		if(_commRedReqXML==null)
		{
			_commRedReqXML = IFDS.Xml.stringToXML('<data/>');
			IFDS.Xml.addSingleNode(_commRedReqXML, 'CommReds');	
		}
		
		var newUpdatedCommRedUUID = IFDS.Xml.getNodeValue(xml, 'commRedUUID');
		
		var currCommRedReqXML = IFDS.Xml.getNode(_commRedReqXML, "//CommReds/CommRed[commRedUUID='" + newUpdatedCommRedUUID + "']");
		
		if(currCommRedReqXML)
		{
			var newUpdatedCommRedAction = IFDS.Xml.getNodeValue(xml, 'updMode');
			var currUpdatedCommRedAction = IFDS.Xml.getNodeValue(currCommRedReqXML, 'updMode');
			
			if(newUpdatedCommRedAction==_DEL)
			{
				IFDS.Xml.deleteNode(currCommRedReqXML);
				if(currUpdatedCommRedAction!=_ADD)
				{
					IFDS.Xml.appendNode(IFDS.Xml.getNode(_commRedReqXML, "//CommReds"), IFDS.Xml.cloneDocument(xml));
				}
			}else{
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currCommRedReqXML, 'commRedCode'), IFDS.Xml.getNodeValue(xml, 'commRedCode'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currCommRedReqXML, 'deff'), IFDS.Xml.getNodeValue(xml, 'deff'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currCommRedReqXML, 'stopDate'), IFDS.Xml.getNodeValue(xml, 'stopDate'));
			}
		}else{
			IFDS.Xml.appendNode(IFDS.Xml.getNode(_commRedReqXML, "//CommReds"), IFDS.Xml.cloneDocument(xml));
		}
		updateUpdatesFlag();
	}
	
	function validateCommRedDetlUpdate(action, popup)
	{
		var xml = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(xml, 'updMode', action);
		IFDS.Xml.addSingleNode(xml, 'commRedDetlUUID', (action!=_ADD)?_selectedCommRedDetl.get('commRedDetlUUID'):'tmpCommRedDetlUUID' + (++_runningCommRedDetlId));
		
		if(action!=_DEL)
		{
			IFDS.Xml.addSingleNode(xml, 'commRedRate', popup.getField('commRedRateFld').getValue());
			IFDS.Xml.addSingleNode(xml, 'intIncRate', popup.getField('intIncRateFld').getValue());
		}
		IFDS.Xml.addSingleNode(xml, 'version', (action==_ADD)?'0':_selectedCommRedDetl.get('version'));
		
		var validateXML = IFDS.Xml.cloneDocument(xml);
		if(_commRedReqXML)
		{
			if(action != _ADD)
			{
				var currCommRedDetlReqXML = IFDS.Xml.getNode(_commRedReqXML, "//CommReds/CommRed[commRedUUID='" + _selectedCommRed.get('commRedUUID') + "']/CommRedDetls/CommRedDetl[commRedDetlUUID='" + _selectedCommRedDetl.get('commRedDetlUUID') + "']");
				if(currCommRedDetlReqXML)
				{
					currUpdMode = IFDS.Xml.getNodeValue(currCommRedDetlReqXML, "updMode");
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
		}
		
		sendValidation(_commRedDetlValidateService, IFDS.Xml.cloneDocument(validateXML), successHandler, errorHandler);
		
		function successHandler()
		{
			commRedDetlUpdateLayout(buildCommRedDetlXML(xml));
			popup.hide();
		}
		
		function errorHandler(responseXML)
		{
			
		}
		
	}
	
	function buildCommRedDetlXML(xml)
	{
		var updMode = IFDS.Xml.getNodeValue(xml, '//updMode');
		var dataXML = IFDS.Xml.newDocument('data');
		var commRedDetlXML = IFDS.Xml.addSingleNode(dataXML, 'CommRedDetl');
		IFDS.Xml.addSingleNode(commRedDetlXML, 'updMode', updMode);
		IFDS.Xml.addSingleNode(commRedDetlXML, 'updSeq', (updMode==_ADD)?'3':(updMode==_MOD)?'2':(updMode==_DEL)?'1':'0');
		IFDS.Xml.addSingleNode(commRedDetlXML, 'commRedDetlUUID', IFDS.Xml.getNodeValue(xml, '//commRedDetlUUID'));
		IFDS.Xml.addAttribute(commRedDetlXML, 'RecordSource', IFDS.Xml.getNodeValue(xml, '//commRedDetlUUID'));
		if(updMode!=_DEL)
		{
			IFDS.Xml.addSingleNode(commRedDetlXML, 'commRedRate', IFDS.Xml.getNodeValue(xml, '//commRedRate'));
			IFDS.Xml.addSingleNode(commRedDetlXML, 'intIncRate', IFDS.Xml.getNodeValue(xml, '//intIncRate'));
		}
		IFDS.Xml.addSingleNode(commRedDetlXML, 'version', IFDS.Xml.getNodeValue(xml, '//version'));

		return dataXML;

	}
	
	function commRedDetlUpdateLayout(xml)
	{
		var updMode = IFDS.Xml.getNodeValue(xml, '//updMode');
		var commRedDetlUpdatedXML = null;
		var commRedXML = IFDS.Xml.getNode(_commRedXML, "//CommRed[commRedUUID='" + _selectedCommRed.get('commRedUUID') + "']");
		switch(updMode)
		{
			case _ADD:
			{
				// Update main XML
				IFDS.Xml.appendNode(IFDS.Xml.getNode(commRedXML, "CommRedDetls"), IFDS.Xml.cloneDocument(IFDS.Xml.getNode(xml, '//CommRedDetl')));
				
				// Update commRedDetlGrid
				_resources.grids['commRedDetlGrid'].getStore().loadData(xml, true);
				_resources.grids['commRedDetlGrid'].getSelectionModel().selectLastRow(false);
				break;
			}
			case _MOD:
			{
				// Update main XML
				var commRedDetlXML = IFDS.Xml.getNode(commRedXML, "CommRedDetls/CommRedDetl[commRedDetlUUID='" + _selectedCommRedDetl.get('commRedDetlUUID') + "']");
				var commRedRate = IFDS.Xml.getNodeValue(xml, '//commRedRate');
				var intIncRate = IFDS.Xml.getNodeValue(xml, '//intIncRate');
				IFDS.Xml.replaceSingleNode(commRedDetlXML, 'commRedRate', commRedRate);
				IFDS.Xml.replaceSingleNode(commRedDetlXML, 'intIncRate', intIncRate);
				
				// Update commRedDetlGrid
				_selectedCommRedDetl.set('commRedRate', commRedRate);
				_selectedCommRedDetl.set('intIncRate', intIncRate);
				_resources.grids['commRedDetlGrid'].getStore().commitChanges();
				break;
			}
			case _DEL:
			{
				// Update main XML
				var commRedDetlXML = IFDS.Xml.getNode(commRedXML, "CommRedDetls/CommRedDetl[commRedDetlUUID='" + _selectedCommRedDetl.get('commRedDetlUUID') + "']");
				IFDS.Xml.deleteNode(commRedDetlXML);
				
				// Update commRedGrid
				_resources.grids['commRedDetlGrid'].getStore().remove(_selectedCommRedDetl);
				
				// Clear current object that related to the commRed
				_selectedCommRedDetl = null;
				
				if(_resources.grids['commRedDetlGrid'].getStore().getCount()>0)
				{
					_resources.grids['commRedDetlGrid'].getSelectionModel().selectFirstRow();
				}

				break;
			}
		}

		updateCommRedDetlButtons();

		addCommRedDetlXMLRequest(IFDS.Xml.getNode(xml, '//CommRedDetl'), _selectedCommRed.get('commRedUUID'));
		
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

	function getCommRedXML(commRedUUID)
	{
		return IFDS.Xml.getNode(_commRedXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']");
	}
	
	function getCommRedsXML()
	{
		return IFDS.Xml.getNode(_commRedXML, '//CommReds');
	}
	
	function getCommRedDetlXML(commRedUUID, commRedDetlUUID)
	{
		return IFDS.Xml.getNode(_commRedXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']/CommRedDetls/CommRedDetl[commRedDetlUUID='" + commRedDetlUUID + "']");
	}
	
	function getCommRedDetlsXML(commRedUUID)
	{
		return IFDS.Xml.getNode(_commRedXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']/CommRedDetls");
	}
	
	function clearGrid(name)
	{
		if(name=='commRedGrid')
		{
			_selectedCommRed = null;
			clearGrid('commRedDetlGrid');
		}else if(name=='commRedDetlGrid'){
			_selectedCommRedDetl = null;
		}
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function addCommRedDetlXMLRequest(xml, commRedUUID)
	{
		if(_commRedReqXML==null)
		{
			_commRedReqXML = IFDS.Xml.stringToXML('<data/>');
			IFDS.Xml.addSingleNode(_commRedReqXML, 'CommReds');	
		}
		
		var currUpdatedCommRedXML = IFDS.Xml.getNode(_commRedReqXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']");
		
		if(!currUpdatedCommRedXML)
		{
			var newCommRedXML = IFDS.Xml.stringToXML('<CommRed RecordSource=\"' + commRedUUID + '\"><updMode>UNCH</updMode><commRedUUID>' + commRedUUID + '</commRedUUID><CommRedDetls/></CommRed>');
			
			IFDS.Xml.appendNode(IFDS.Xml.getNode(_commRedReqXML, "//CommReds"), IFDS.Xml.cloneDocument(newCommRedXML));
		}
		
		var newUpdatedCommRedDetlUUID = IFDS.Xml.getNodeValue(xml, 'commRedDetlUUID');
		var currUpdatedCommRedDetlXML = IFDS.Xml.getNode(_commRedReqXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']/CommRedDetls/CommRedDetl[commRedDetlUUID='" + newUpdatedCommRedDetlUUID + "']");
		
		if(currUpdatedCommRedDetlXML)
		{
			var newUpdatedCommRedDetlAction = IFDS.Xml.getNodeValue(xml, 'updMode');
			var currUpdatedCommRedDetlAction = IFDS.Xml.getNodeValue(currUpdatedCommRedDetlXML, 'updMode');
			
			if(newUpdatedCommRedDetlAction==_DEL)
			{
				IFDS.Xml.deleteNode(currUpdatedCommRedDetlXML);
				if(currUpdatedCommRedDetlAction!=_ADD)
				{
					IFDS.Xml.appendNode(IFDS.Xml.getNode(_commRedReqXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']/CommRedDetls"), IFDS.Xml.cloneDocument(xml));
				}
			}else{
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currUpdatedCommRedDetlXML, 'commRedRate'), IFDS.Xml.getNodeValue(xml, 'commRedRate'));
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(currUpdatedCommRedDetlXML, 'intIncRate'), IFDS.Xml.getNodeValue(xml, 'intIncRate'));
			}
		}else{
			IFDS.Xml.appendNode(IFDS.Xml.getNode(_commRedReqXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']/CommRedDetls"), IFDS.Xml.cloneDocument(xml));
		}
		updateUpdatesFlag();
	}
	
	function updateUpdatesFlag()
	{
		var commRedUpdates = IFDS.Xml.getNodes(_commRedReqXML, "//CommReds/CommRed[updMode!='UNCH']");
		var commRedDetlUpdates = IFDS.Xml.getNodes(_commRedReqXML, "//CommRedDetls/CommRedDetl[updMode!='UNCH']");
		if(commRedUpdates.length == 0 && commRedDetlUpdates.length == 0)
		{
			_self.updatesFlag = false;
		}else{
			_self.updatesFlag = true;
		}
	}
	
	function storeContextErrors(errorNodes)
	{
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			if(table == 'CommRed')
			{
				var commRedUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				
				// Update main XML
				var commRedXML = IFDS.Xml.getNode(_commRedXML, "//CommReds/CommRed[commRedUUID='" + commRedUUID + "']");
				IFDS.Xml.addSingleNode(commRedXML, 'commRedErrMsg', errMsg);
				
				// Update commRedGrid
				var recordIndex = _resources.grids['commRedGrid'].getStore().find('commRedUUID', commRedUUID);
				var commRedRecord = _resources.grids['commRedGrid'].getStore().getAt(recordIndex);
				commRedRecord.set('commRedErrMsg', errMsg);
				_resources.grids['commRedGrid'].getStore().commitChanges();
				if(firstErrRecIndex==-1)firstErrRecIndex = recordIndex;
			}else{
				var commRedDetlUUID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
				
				// Update main XML
				var commRedDetlXML = IFDS.Xml.getNode(_commRedXML, "//CommRedDetl[commRedDetlUUID='" + commRedDetlUUID + "']");
				IFDS.Xml.addSingleNode(commRedDetlXML, 'commRedDetlErrMsg', errMsg);
				
				// Looking for commRed
				var commRedXML = commRedDetlXML.parentNode.parentNode;
				var commRedErrMsg = IFDS.Xml.getNodeValue(commRedXML, 'commRedErrMsg');
				if(commRedErrMsg == '')
				{
					// Update main XML
					IFDS.Xml.addSingleNode(commRedXML, 'commRedErrMsg', 'Errors present in Commission Reduction Detail');
					
					// Update commRedGrid
					var commRedUUID = IFDS.Xml.getNodeValue(commRedXML, 'commRedUUID');
					var recordIndex = _resources.grids['commRedGrid'].getStore().find('commRedUUID', commRedUUID);
					var commRedRecord = _resources.grids['commRedGrid'].getStore().getAt(recordIndex);
					commRedRecord.set('commRedErrMsg', 'Errors present in Commission Reduction Detail');
					_resources.grids['commRedGrid'].getStore().commitChanges();
					if(firstErrRecIndex==-1)firstErrRecIndex = recordIndex;
				}
			}
		}
		if(firstErrRecIndex==-1)
		{
			_resources.grids['commRedGrid'].getSelectionModel().selectFirstRow();
		}else{
			_resources.grids['commRedGrid'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['commRedGrid'].focusRow(firstErrRecIndex);
		}
		loadCommRedDetl(_selectedCommRed.get('commRedUUID'));
	}

	function loadMoreCommRed(moreCommRedXML)
	{
		var cloneMoreCommRedXML = IFDS.Xml.cloneDocument(moreCommRedXML);
		var intRateCfgsNode = IFDS.Xml.getNode(_commRedXML, "//CommReds");
		var moreCommRedNodes = IFDS.Xml.getNodes(moreCommRedXML, "//CommRed");
		Ext.each(moreCommRedNodes, function(moreCommRedNode){
			IFDS.Xml.appendNode(intRateCfgsNode, moreCommRedNode);
		});
		_resources.grids['commRedGrid'].getStore().loadData(cloneMoreCommRedXML, true);
		_resources.grids['commRedGrid'].focusRow(_selectedCommRedIndex);
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
			
			loadCommRed();

		}
		
		,setSelectedCommRed: function(record, index)
		{
			_selectedCommRed = record;
			_selectedCommRedIndex = index;
			
			loadCommRedDetl(record.get('commRedUUID'));
			
			updateCommRedButtons();
			
		}
		
		,setDeselectedCommRed: function()
		{
			_selectedCommRed = null;
			_selectedCommRedDetl = null;
			clearGrid('commRedDetlGrid');
		}
		
		,setSelectedCommRedDetl: function(record)
		{
			_selectedCommRedDetl = record;
			
			updateCommRedDetlButtons();
		}
		
		,setDeselectedCommRedDetl: function()
		{
			_selectedCommRedDetl = null;
		}
		
		,openActionPopup: function(name, action)
		{		
			if(action == _DEL && _selectedCommRed.get('inUsed') == 'yes' && isStopped(_selectedCommRed.get('stopDate'))){
				DesktopWeb.Util.displayError(_translationMap['RecordTermMsg']);
			}else{
				var popup = _resources.popups[name];	
				popup.show();					
				popup.init(action);			
				updateCommRedButtons();
			}
		}
		
		,openHistoryPopup: function(recType)
		{
			var viewParam = {};
			var historyName = null;
			if (recType == 'commRed')
			{
				viewParam['auditType'] = 'CommReduction';
				viewParam['searchValue1'] = _selectedCommRed.get('commRedUUID');
				historyName = _translationMap['CommRed']+ ' - ' +_translationMap['History'];
			}
			else
			{
				viewParam['auditType'] = 'CommReductionDetl';
				viewParam['searchValue1'] = _selectedCommRedDetl.get('commRedDetlUUID');		
				historyName = _translationMap['CommRedDetails']+ ' - ' +_translationMap['History'];		
			}
			_resources.popups['history'].init(historyName, _historyService, viewParam, true);
			_resources.popups['history'].show();
			
		}
		
		,openAdminPopup: function(recType)
		{					
			var title = null;	
			var xml = null;
			if (recType == 'commRed')
			{
				title = _translationMap['CommRed']+ ' - ' +_translationMap['Admin']
				xml = this.getSelectedCommRedXML();
			}
			else
			{
				title = _translationMap['CommRedDetails']+ ' - ' +_translationMap['Admin']
				xml = this.getSelectedCommRedDetlXML();
			}
			var adminData = {};
			adminData['userName'] = IFDS.Xml.getNodeValue(xml, 'userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'procDate'));
			adminData['modUser'] = IFDS.Xml.getNodeValue(xml, 'modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}
		
		,commRedUpdate: function(action, popup)
		{
			validateCommRedUpdate(action, popup);
		}
		
		,commRedDetlUpdate: function(action, popup)
		{
			validateCommRedDetlUpdate(action, popup);
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;		
			DesktopWeb.Ajax.doSmartviewUpdate(_commRedProcessService, null, IFDS.Xml.cloneDocument(_commRedReqXML), responseHandler, _translationMap['ProcMsg_Saving']);			
			
			function responseHandler(success, responseXML, contextErrors)
			{	
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
					_commRedReqXML = null;
					loadCommRed();
				}else{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}
		
		,doReload: function(more)
		{
		}
		
		,setCommRedButtons: function()
		{
			updateCommRedButtons();
		}
		
		,setCommRedDetlButtons: function()
		{
			updateCommRedDetlButtons();
		}
		
		,doReloadCommRed: function()
		{
			loadCommRed();
		}
		
		,doReloadCommRedDetl: function()
		{
			loadCommRedDetl(_selectedCommRed.get('commRedUUID'));
		}
		
		,getSelectedCommRedXML: function()
		{
			return getCommRedXML(_selectedCommRed.get('commRedUUID'));
		}
		
		,getSelectedCommRed: function()
		{
			return _selectedCommRed;
		}

		,getSelectedCommRedDetlXML: function()
		{
			return getCommRedDetlXML(_selectedCommRed.get('commRedUUID'), _selectedCommRedDetl.get('commRedDetlUUID'));
		}
		
		,getSelectedCommRedDetl: function()
		{
			return _selectedCommRedDetl;
		}
		
		,getDefault: function(fieldName)
		{
			return _defaultObject[fieldName];
		}
		,doReload: function()
		{
			var paramXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(paramXML, 'startRecNum', _nextStartRecNum);
			IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);

			DesktopWeb.Ajax.doSmartviewAjax(_commRedReloadService, null, paramXML, responseHandler, "Loading ...");

			function responseHandler(success, responseXML)
			{	
				if (success)
				{
					loadMoreCommRed(responseXML);
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					if (_nextStartRecNum)
					{
						_resources.grids['commRedGrid'].enableButton('moreBtn');
					}
					else
					{
						_resources.grids['commRedGrid'].disableButton('moreBtn');
					}
				}
			}
		}
	}	
}	
