/*********************************************************************************************
 * @file	ClassSetup_FeeModelConfig.Controller.js	
 * @author	Aurkarn Mongkonrat
 * @desc	Controller file for Fee Model Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_FeeModelConfig.Controller.js
 *
 * Purpose  : Fee Model Configuration screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Fee Model Configuration screens
 *
 * History  : 24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *            Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration.    
 * 
 */
 
 DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
		
	var _addMode = null;
	var _screenId = "FeeModelConfig";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	
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
				classCode = "*" + _translationMap['New'].toUpperCase() + "*";
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
		_resources.header.setText(screenLabel + ' - ' + _translationMap['Fund'] + ': ' + fundCode + ', ' + _translationMap['Class'] + ': ' + classCode);
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
			_resources.fields['mgmtFeePayOpt'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'MgmtFeePayOptionList']"));
			_resources.fields['mgmtFeeAcctAggr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'AcctAggrList']"));
			_resources.fields['mgmtFeeFundAggr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'FundAggrList']"));
			_resources.fields['mgmtFeeProrateOpt'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'ProrateList']"));
			_resources.fields['mfrAcctAggr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'AcctAggrList']"));
			_resources.fields['mfrFundAggr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'FundAggrList']"));
			_resources.fields['advAcctAggr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'AcctAggrList']"));
			_resources.fields['advFundAggr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'FundAggrList']"));
			
		}
		catch(e){throw new Error("Error loading data from init XML - " + e.description)}
	}	
	
	function populateScreen()
	{
		var feeModelConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeModelConfiguration');
		
		for (var i in _resources.fields)
		{
			setInitialFieldValue(_resources.fields[i], IFDS.Xml.getNodeValue(feeModelConfigXML, i));	
		}
		
		function setInitialFieldValue(fld, val)
		{			
			if (val != "") 
			{		
				if (fld instanceof DesktopWeb.Controls.DateField)
					val = DesktopWeb.Util.getDateDisplayValue(val);
				
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
		var feeModelConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeModelConfiguration');
		
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
		
		for (var i in _resources.fields)
		{		
			if (_resources.fields[i] instanceof DesktopWeb.Controls.DateField)
			{
				xmlWriteFn(i, _resources.fields[i].getSMVDateString());	
			}
			else
			{
				xmlWriteFn(i, _resources.fields[i].getValue());	
			}
		}
		
		
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? feeModelConfigXML : context);
			
			var node = IFDS.Xml.getNode(context, fldName);
			
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? feeModelConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}
	}
	
	function updateBreadcrumb()
	{
		_resources.breadCrumbList.doLayout();
	}
	
	function validateScreen()
	{				
		var isValid = true;		
		for (var i in _resources.fields)
		{						
			if (_resources.fields[i].isValid)
			{
				isValid = _resources.fields[i].isValid() && isValid;
			}								
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
			
			DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ScreenDefList', 'ExistingClassData', 'UpdatedClassData'], responseHandler, _translationMap['ProcMsg_Loading'])
			 								
			function responseHandler(responseXML)
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
				if (!_addMode)
				{							
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'FeeModelConfiguration'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'FeeModelConfiguration')));
					}
				}
				
				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateDropdowns();
				addChangeHandlers();
				populateScreen();
				clearChangeFlag();
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
					goToScreen(screenName);
				}
			}
			
			function callback(discard)
			{
				if (discard)
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
				updateBreadcrumb();
				updateXML();					
				DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
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
			DesktopWeb.Util.displayDiscardPrompt(callback);
			
			function callback(discard)
			{
				if (discard)
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
				updateBreadcrumb();
				updateXML();					
				DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_saving']);
			}
			
			function callback()
			{
				clearChangeFlag();
			}			
		}
		
		,cancel: function()
		{
			DesktopWeb.Util.displayDiscardPrompt(callback);
			
			function callback(discard)
			{
				if (discard)
				{
					goToScreen('Search');
				}
			}
		}				
	}	
}