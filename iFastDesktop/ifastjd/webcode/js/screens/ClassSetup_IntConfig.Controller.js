/*********************************************************************************************
 * @file	ClassSetup_IntConfig.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Interest Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 */ 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _addMode = null;
	var _screenId = "IntConfig";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;	
	var _intCalcMthd = null;
	var _intRateInqView = 'dtFundIntRateInq';
	var _intRateDataXML = null;	
	
	
	// PRIVATE METHODS ****************************************
	function setHeader()
	{
		var fundCode = null;
		var classCode = null;
		if (_addMode)
		{
			fundCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundCode');
			classCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//classCode');			
			if (classCode == "")
			{
				classCode = "*NEW*";
			}
			else 
			{
				classCode = "*" + classCode + "*";
			}
		}
		else
		{
			fundCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundCode');
			classCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'classCode');	
		}
		
		var screenLabel = IFDS.Xml.getNodeValue(_screenDefListXML, 'Screen[id = "' + _screenId + '"]/label')		
		_resources.header.setText(screenLabel + ' - ' + _translationMap['Fund'] 
									+ ' : ' + fundCode 
									+ ', ' + _translationMap['Class'] 
									+ ': ' + classCode);
	}
	
	function populateBreadCrumbList()
	{
		var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
				
		for (var i = 0; i < screenDefNodes.length; i++)
		{
			var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id');			
			_resources.breadCrumbList.addItem(id, IFDS.Xml.getNodeValue(screenDefNodes[i], 'label'));
			
			if (id == _screenId)
			{
				_screenIndex = i;
			}							
		}		
		
		if (_addMode)
		{
			_resources.breadCrumbList.disableAll();
			for (var i = 0; i <= _screenIndex; i++)
			{	
				 var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id') 
				_resources.breadCrumbList.enableItem(id);										
			}
		}
		else
		{						
			_resources.breadCrumbList.enableAll();
		}
		_resources.breadCrumbList.setActiveItem(_screenId);
	}
	
	function displayScreenButtons()
	{
		if (_addMode)
		{			
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			if (_screenIndex != 0)
			{
				//not the first
				Ext.getCmp('prevBtn').enable();
			}
			
			if (_screenIndex < screenDefNodes.length - 1)
			{				
				Ext.getCmp('nextBtn').setText(_translationMap['Next']);
			}
			else
			{
				Ext.getCmp('nextBtn').setText(_translationMap['Summary']);
			}
			Ext.getCmp('prevBtn').show();
			Ext.getCmp('cancelBtn').show();
			Ext.getCmp('nextBtn').show();			
		}
		else
		{
			Ext.getCmp('summaryBtn').show();
		}
	}
	
	function populateDropdowns()
	{		
		try{
			_resources.fields['simIRCode'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'SimIntRateConfigList']"));
			_resources.fields['comIRCode'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'ComIntRateConfigList']"));					
		}	
		catch(e){throw new Error("Error loading data from XML - " + e.description)}
	}
	
	function populateScreen()
	{	
		if (IFDS.Xml.getNode(_updatedClassDataXML, 'GIAAttributes'))
		{
			_intCalcMthd = IFDS.Xml.getNodeValue(_updatedClassDataXML, 'GIAAttributes/intCalcMthd');
		}
		else if (_existingClassDataXML != null && IFDS.Xml.getNode(_existingClassDataXML, 'GIAAttributes'))
		{
			_intCalcMthd = IFDS.Xml.getNodeValue(_existingClassDataXML, 'GIAAttributes/intCalcMthd');
		}
		
		// GIAAttributes is not available for DIF funds
		if (!_intCalcMthd)
		{
			_intCalcMthd = 'S';
		}
		
		var intCommConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'IntConfig');
		try{
			if (_intCalcMthd == 'S' || _intCalcMthd == 'B')
			{
				setInitialFieldValue(_resources.fields['simIRCode'], IFDS.Xml.getNodeValue(intCommConfigXML, "simIRCode"));
				_self.updateInterestRateGrid('sim');
				_resources.grids['simInterestRate'].enable();
			}
			else
			{
				_resources.fields['simIRCode'].disableField();
				_resources.grids['simInterestRate'].disable();
			}
			
			if (_intCalcMthd == 'C' || _intCalcMthd == 'B')
			{
				setInitialFieldValue(_resources.fields['comIRCode'], IFDS.Xml.getNodeValue(intCommConfigXML, "comIRCode"));
				_self.updateInterestRateGrid('com');
				_resources.grids['comInterestRate'].enable();
			}
			else
			{
				_resources.fields['comIRCode'].disableField();
				_resources.grids['comInterestRate'].disable();
			}								
		}	
		catch(e){throw new Error("Error loading data from XML - " + e.description)}
		
		
		function setInitialFieldValue(fld, val)
		{			
			if (val != "") 
			{		
				fld.setValue(val);
			}
			else
			{
				fld.reset();
			}	
		}	
	} 
	
	function addChangeHandlers()
	{
		for (var i in _resources.fields)
		{			
			addHandler(_resources.fields[i]);		
		}
		
		function addHandler(fld)
		{
			if (fld instanceof Ext.form.Checkbox)
			{
				fld.addListener('check', function(){setChangeFlag()})
			}
			else if (fld instanceof DesktopWeb.Controls.ComboBox)
			{
				fld.addListener('select', function(){setChangeFlag()})
			}
			else
			{
				fld.addListener('change', function(){setChangeFlag()})
			}
		}				
	}
	
	function setChangeFlag()
	{
		_changeFlag = true;
		Ext.getCmp('resetBtn').enable();
		Ext.getCmp('saveBtn').enable();
	}
	
	function clearChangeFlag()
	{
		_changeFlag = false;
		Ext.getCmp('resetBtn').disable();
		Ext.getCmp('saveBtn').disable();
	}
	
	function updateXML()
	{
		var intConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'IntConfig');
		
		var xmlWriteFn = null; 
		if (_addMode)
		{
			writeNewValueToXML('runMode', _self.ADD);			
			xmlWriteFn = writeNewValueToXML;
		}
		else
		{
			writeNewValueToXML('runMode', _self.MOD);
			xmlWriteFn = writeUpdatedValueToXML;
		}
		
		xmlWriteFn('simIRCode', _resources.fields['simIRCode'].getValue());
		xmlWriteFn('comIRCode', _resources.fields['comIRCode'].getValue());
						
			
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? intConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? intConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}				
	}
	
	function validateScreen()
	{
		var isValid = true;
				
		if ((_intCalcMthd == "S" || _intCalcMthd == "B") 
			&& _resources.fields['simIRCode'].getValue() == "")
		{
			_resources.fields['simIRCode'].markInvalid(_translationMap['FldRequired']);
			isValid = false;
		}
		
		if ((_intCalcMthd == "C" || _intCalcMthd == "B") 
			&& _resources.fields['comIRCode'].getValue() == "")
		{
			_resources.fields['comIRCode'].markInvalid(_translationMap['FldRequired']);
			isValid = false;
		}
		return isValid;
	}		
	
	function goToScreen(screenName)
	{
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_' + screenName;
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		urlParams['prevScreen'] = _screenId;
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
		
		if (screenName == "Search")
		{
			urlParams['createCache'] = 'true';	
		}
		else
		{
			urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		}			
									
		window.location = DesktopWeb.Ajax.buildURL(urlParams);
	}
		
	// PUBLIC ITEMS *************************************
	return {				
		ADD: 'a', MOD: 'm', DEL: 'd'		
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ScreenDefList', 'ExistingClassData', 'UpdatedClassData']
						, responseHandler1
						, _translationMap['ProcMsg_Loading']);
			 								
			function responseHandler1(responseXML)
			{													
				_initDataXML = IFDS.Xml.getNode(responseXML, 'InitData/*');
				_screenDefListXML = IFDS.Xml.getNode(responseXML, 'ScreenDefList/*');	
				_existingClassDataXML = IFDS.Xml.getNode(responseXML, 'ExistingClassData/*');				
				_updatedClassDataXML = IFDS.Xml.getNode(responseXML, 'UpdatedClassData/data');				
				
				if (_initDataXML == null || _screenDefListXML == null || _updatedClassDataXML == null)
				{
					throw new Error("Error retrieving cached data");
				}

				_addMode = (_existingClassDataXML == null);
				if (_addMode)
				{
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'IntConfig'))
					{
						IFDS.Xml.addSingleNode(_updatedClassDataXML, 'IntConfig');
					}
				}
				else
				{
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'IntConfig'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'IntConfig')));
					}
				}
								
				DesktopWeb.Ajax.doSmartviewCall(_intRateInqView
						, null, null
						, responseHandler2, _translationMap['ProcMsg_Loading'])
								
				function responseHandler2(responseXML)
				{														
					var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _intRateInqView + 'Response'));
				 
					if (smartviewResults.successful)
					{
						_intRateDataXML = IFDS.Xml.getNode(responseXML, '//InterestRateConfigInfo');						
												
						setHeader();
						populateBreadCrumbList();
						displayScreenButtons();
						populateDropdowns();
						addChangeHandlers();				
						populateScreen();
						clearChangeFlag();								
					}					
				}
			}		
		}
		
		,updateInterestRateGrid: function(type)
		{		
			var intCode = null;
			var grid = null;			
			if (type == 'sim')
			{
				intCode = _resources.fields['simIRCode'].getValue();
				grid = _resources.grids['simInterestRate'];
			}
			else
			{
				intCode = _resources.fields['comIRCode'].getValue();
				grid = _resources.grids['comInterestRate'];
			}
			
			if (intCode != "")
			{			
				var rateDataNode = IFDS.Xml.getNode(_intRateDataXML, '//IntRateConfigMstr[intCode = "' + intCode + '"]');
				if (rateDataNode)
				{					
					grid.loadData(rateDataNode);
					if (IFDS.Xml.getNodeValue(rateDataNode, "active").toLowerCase() != "yes")
					{
						DesktopWeb.Util.displayWarning(intCode + _translationMap['IsNoLongerActiveCode']);
					}				
				}
				else
				{
					DesktopWeb.Util.displayError(_translationMap['InterestRateDataNotFound'] + intCode);
				}
			}										
		}
		
		,changeScreen: function(screenName)		
		{
			if (screenName != _screenId)
			{			
				if (_changeFlag)
				{
					DesktopWeb.Util.displayDiscardPrompt(callback)
				}
				else
				{
					goToScreen(screenName)
				}
			}
			
			function callback(buttonId)
			{
				if (buttonId)
				{
					goToScreen(screenName);
				}
			}
		}
		
		,previous: function()		
		{
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex - 1], 'id'));	
		}
		
		,next: function()		
		{
			if (validateScreen())
			{
				if (_changeFlag)
				{		
					updateXML();					
					DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}
						, callback
						, _translationMap['ProcMsg_Saving']);
				}
				else
				{
					callback();
				}
			}						
			
			function callback()
			{
				clearChangeFlag();
				var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
				if (_screenIndex < screenDefNodes.length - 1)
				{				
					goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex + 1], 'id'));
				}
				else
				{
					goToScreen('Summary');
				}	
			}	
		}
		
		,reset: function()
		{
			DesktopWeb.Util.displayDiscardPrompt(callback)
			
			function callback(buttonId)
			{
				if (buttonId)
				{
					populateScreen();
					clearChangeFlag();
				}
			}
		}
		
		,save: function()
		{			
			if (validateScreen())
			{		
				updateXML();					
				DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}
					, callback, _translationMap['ProcMsg_Saving']);
			}
			
			function callback()
			{
				clearChangeFlag();	
			}			
		}	
		
		,cancel: function()
		{
			DesktopWeb.Util.displayDiscardPrompt(callback);
			
			function callback(buttonId)
			{
				if (buttonId)
				{
					goToScreen('Search');
				}
			}
		}		
	}	
}