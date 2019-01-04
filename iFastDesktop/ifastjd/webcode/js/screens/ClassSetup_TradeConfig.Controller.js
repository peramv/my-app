/*********************************************************************************************
 * @file	ClassSetup_TradeConfig.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Trade Configuration screen, part of Class Setup flow
 *********************************************************************************************/
 /*
 * Procedure: ClassSetup_TradeDayCtrls.Resources.js
 *
 * Purpose  : Trade Configuration screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Trade Configuration screens
 *
 * History  : 
 *  12 Nov 2012 H.Sartsangchan Created. 
 *          IN3135980 Load type validation does not work properly on Class setup
 *          - Update Class Dropdownlist when Fund Dropdownlist has changed
 *
 *  25 Apr 2012 C. Sangkasen P0212170 Master Account & AMS
 *          - Introduced field AMS Model Type.
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *          
 *   3 Feb 2016 Winnie Cheng P0251001 CHG0043877 T82126
 *          - Adding one dropdown field for Partial Redemption Indicator - Red. Gross/Net
 *          
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
   
	
	var _addMode = null;
	var _screenId = "TradeConfig";
	var _classSearchView = 'classSearch';
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
		_resources.fields['ordType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'OrdTypeList']"));
		_resources.fields['eligICTIn'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'EligICTInList']"));
		_resources.fields['eligICTOut'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'EligICTOutList']"));
		_resources.fields['freeRollFund'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'Funds']"));				
		_resources.fields['freeRollPUD'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'PUDList']"));
		_resources.fields['calcMethods']['purAgingRule'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'PurAgingRuleList']"));
		_resources.fields['calcMethods']['pShipUnitAsmt'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'PShipUnitAsmtList']"));
		_resources.fields['calcMethods']['freeConsol'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'FreeConsolList']"));
		_resources.fields['calcMethods']['gainLossMthd'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'GainLossMthdList']"));
		_resources.fields['erisaOptn'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'ERISAList']"));
		_resources.fields['amsModelType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'AMSModelTypeList']"));	
		_resources.fields['redGrossNetDefault'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'RedGrossNetList']"));
	}	
	
	function populateScreen()
	{
		var tradeConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'TradeConfiguration');
		setInitialFieldValue(_resources.fields['wireElig'], IFDS.Xml.getNodeValue(tradeConfigXML, 'wireElig') == 'yes');				
		setInitialFieldValue(_resources.fields['ordType'], IFDS.Xml.getNodeValue(tradeConfigXML, 'ordType'));
		
		var classEligXML = IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility');
		setInitialFieldValue(_resources.fields['rrsp'], IFDS.Xml.getNodeValue(classEligXML, 'rrsp') == 'yes');
		setInitialFieldValue(_resources.fields['rrif'], IFDS.Xml.getNodeValue(classEligXML, 'rrif') == 'yes');
		setInitialFieldValue(_resources.fields['esop'], IFDS.Xml.getNodeValue(classEligXML, 'esop') == 'yes');
		setInitialFieldValue(_resources.fields['nscCompliant'], IFDS.Xml.getNodeValue(classEligXML, 'nscCompliant') == 'yes');
		setInitialFieldValue(_resources.fields['ams'], IFDS.Xml.getNodeValue(classEligXML, 'ams') == 'yes');
		_self.doAMSCheck(IFDS.Xml.getNodeValue(classEligXML, 'ams') == 'yes');			
		setInitialFieldValue(_resources.fields['marginAllowed'], IFDS.Xml.getNodeValue(classEligXML, 'marginAllowed') == 'yes');
		setInitialFieldValue(_resources.fields['cssErrCorr'], IFDS.Xml.getNodeValue(classEligXML, 'cssErrCorr') == 'yes');
		setInitialFieldValue(_resources.fields['freeRoll'], IFDS.Xml.getNodeValue(classEligXML, 'freeRoll') == 'yes');
		setInitialFieldValue(_resources.fields['eligICTIn'], IFDS.Xml.getNodeValue(classEligXML, 'eligICTIn'));
		setInitialFieldValue(_resources.fields['eligICTOut'], IFDS.Xml.getNodeValue(classEligXML, 'eligICTOut'));
		setInitialFieldValue(_resources.fields['amsModelType'], IFDS.Xml.getNodeValue(classEligXML, 'amsModelType'));			
		
		var fundERISAOptn = IFDS.Xml.getNodeValue((_addMode)?_updatedClassDataXML:_existingClassDataXML, 'fundERISAOptn');
		var fundERISACalcLevel = IFDS.Xml.getNodeValue((_addMode)?_updatedClassDataXML:_existingClassDataXML, 'fundERISACalcLevel');
		/**
		 ** ERISA Allowed field is enable when 
		 ** ERISA Eligible at fund level (02)
		 **/
		if (fundERISAOptn == '02') 
		{
			_resources.fields['erisaOptn'].enableField();
			setInitialFieldValue(_resources.fields['erisaOptn'], IFDS.Xml.getNodeValue(classEligXML, 'erisaOptn'));
			
			/** 
			 ** ERISA Class Group level will be enable when 
			 ** ERISA Eligible at class level (02) 
			 **/
			if (IFDS.Xml.getNodeValue(classEligXML, 'erisaOptn') == '02') 
			{
				_resources.fields['erisaClassGroup'].enableField();
				setInitialFieldValue(_resources.fields['erisaClassGroup'], IFDS.Xml.getNodeValue(classEligXML, 'erisaClassGroup'));
			}else{
				_resources.fields['erisaClassGroup'].reset();
				_resources.fields['erisaClassGroup'].disableField();
			}
		}else{
			_resources.fields['erisaOptn'].setValue('01'); // Default to Not Applicable (01)
			_resources.fields['erisaOptn'].disableField();
			_resources.fields['erisaClassGroup'].reset();
			_resources.fields['erisaClassGroup'].disableField();
		}
		
		setInitialFieldValue(_resources.fields['freeRollFund'], IFDS.Xml.getNodeValue(classEligXML, 'freeRollFund'));
		if (IFDS.Xml.getNodeValue(classEligXML, 'freeRollFund') != "")
		{					
			_self.updateClassList(IFDS.Xml.getNodeValue(classEligXML, 'freeRollFund'),IFDS.Xml.getNodeValue(classEligXML, 'freeRollCl'));
		}
		
		setInitialFieldValue(_resources.fields['freeRollPUD'], IFDS.Xml.getNodeValue(classEligXML, 'freeRollPUD'));
		setInitialFieldValue(_resources.fields['freeRollQualPrd'], IFDS.Xml.getNodeValue(classEligXML, 'freeRollQualPrd'));
		
		var calcMethodsXML = IFDS.Xml.getNode(tradeConfigXML, 'CalcMethods');
		for (var i in _resources.fields['calcMethods'])
		{
			setInitialFieldValue(_resources.fields['calcMethods'][i], IFDS.Xml.getNodeValue(calcMethodsXML, i));
		}		
			
		var minMaxAmountsXML = IFDS.Xml.getNode(tradeConfigXML, 'MinMaxAmounts');
		for (var i in _resources.fields['minMax'])
		{
			setInitialFieldValue(_resources.fields['minMax'][i], IFDS.Xml.getNodeValue(minMaxAmountsXML, i));
		}
		
		var stopFlagsXML = IFDS.Xml.getNode(tradeConfigXML, 'StopFlags');
		for (var i in _resources.fields['stopFlags'])
		{
			setInitialFieldValue(_resources.fields['stopFlags'][i], IFDS.Xml.getNodeValue(stopFlagsXML, i) == 'yes');	
		}
		
		setInitialFieldValue(_resources.fields['redGrossNetDefault'], IFDS.Xml.getNodeValue(tradeConfigXML, 'redGrossNetDefault'));
		
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
			if (i == 'minMax')
			{
				for (var j in _resources.fields['minMax'])
				{
					addHandler(_resources.fields['minMax'][j]);
				}
			}
			else if (i == 'calcMethods')
			{
				for (var j in _resources.fields['calcMethods'])
				{
					addHandler(_resources.fields['calcMethods'][j]);
				}
			}
			else if (i == 'stopFlags')
			{
				for (var j in _resources.fields['stopFlags'])
				{
					addHandler(_resources.fields['stopFlags'][j]);
				}
			}						
			else
			{
				addHandler(_resources.fields[i]);
			}							
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
		var tradeConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'TradeConfiguration');
		
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
		
		xmlWriteFn('wireElig', 
			(_resources.fields['wireElig'].getValue() ? 'yes' : 'no'), 
			tradeConfigXML);		
		xmlWriteFn('ordType', 
			_resources.fields['ordType'].getValue(),
			tradeConfigXML);
		xmlWriteFn('redGrossNetDefault',
			_resources.fields['redGrossNetDefault'].getValue(),
			tradeConfigXML);
		xmlWriteFn('rrsp', 
			(_resources.fields['rrsp'].getValue() ? 'yes' : 'no'), 
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));		
		xmlWriteFn('rrif', 
			(_resources.fields['rrif'].getValue() ? 'yes' : 'no'), 
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('esop', 
			(_resources.fields['esop'].getValue() ? 'yes' : 'no'), 
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('nscCompliant', 
			(_resources.fields['nscCompliant'].getValue() ? 'yes' : 'no'), 
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('ams', 
			(_resources.fields['ams'].getValue() ? 'yes' : 'no'), 
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('marginAllowed', 
			(_resources.fields['marginAllowed'].getValue() ? 'yes' : 'no'),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('cssErrCorr', 
			(_resources.fields['cssErrCorr'].getValue() ? 'yes' : 'no'),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));			
		xmlWriteFn('freeRoll', 
			(_resources.fields['freeRoll'].getValue() ? 'yes' : 'no'),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		
		xmlWriteFn('freeRollFund', 
			_resources.fields['freeRollFund'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('freeRollCl', 
			_resources.fields['freeRollCl'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('freeRollPUD', 
			_resources.fields['freeRollPUD'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		xmlWriteFn('freeRollQualPrd', 
			_resources.fields['freeRollQualPrd'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));		
		
		xmlWriteFn('eligICTIn', 
			_resources.fields['eligICTIn'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));	
		xmlWriteFn('eligICTOut', 
			_resources.fields['eligICTOut'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));	
		xmlWriteFn('erisaOptn', 
			_resources.fields['erisaOptn'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));	
		xmlWriteFn('erisaClassGroup', 
			_resources.fields['erisaClassGroup'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));	
		xmlWriteFn('amsModelType', 
			_resources.fields['amsModelType'].getValue(),
			IFDS.Xml.getNode(tradeConfigXML, 'ClassEligibility'));
		
		for (var i in _resources.fields['minMax'])
		{
			xmlWriteFn(i, _resources.fields['minMax'][i].getValue(), IFDS.Xml.getNode(tradeConfigXML, 'MinMaxAmounts'));	
		}
		
		for (var i in _resources.fields['stopFlags'])
		{
			xmlWriteFn(i, (_resources.fields['stopFlags'][i].getValue() ? 'yes' : 'no'), IFDS.Xml.getNode(tradeConfigXML, 'StopFlags'));	
		}
		
		for (var i in _resources.fields['calcMethods'])
		{
			xmlWriteFn(i, _resources.fields['calcMethods'][i].getValue(), IFDS.Xml.getNode(tradeConfigXML, 'CalcMethods'));	
		}
				
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? tradeConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (!node) node = IFDS.Xml.addSingleNode(context, fldName);
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? tradeConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}			
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
		
		for (var i in _resources.fields['minMax'])
		{			
			if (_resources.fields['minMax'][i].isValid)
			{
				isValid = _resources.fields['minMax'][i].isValid() && isValid;
			}								
		}
		
		for (var i in _resources.fields['calcMethods'])
		{			
			if (_resources.fields['calcMethods'][i].isValid)
			{
				isValid = _resources.fields['calcMethods'][i].isValid() && isValid;
			}								
		}
		
		var fundERISAOptn = IFDS.Xml.getNodeValue((_addMode)?_updatedClassDataXML:_existingClassDataXML, 'fundERISAOptn');
		var fundERISACalcLevel = IFDS.Xml.getNodeValue((_addMode)?_updatedClassDataXML:_existingClassDataXML, 'fundERISACalcLevel');
			
		if (isValid)
		{
			if (fundERISAOptn == '02' // ERISA Eligible at Fund level
				&& fundERISACalcLevel == '03' // ERISA Calculation Level is Class Group
				&& _resources.fields['erisaOptn'].getValue() == '02' // ERISA Allowed (screen) is ERISA Eligible
				&& _resources.fields['erisaClassGroup'].getValue() == '') // ERISA Classes Group (screen) is blank
			{
				_resources.fields['erisaClassGroup'].markInvalid(_translationMap['FldRequired']);
				isValid = false;
			}
		}
		
		if (_resources.fields['ams'].getValue() && _resources.fields['amsModelType'].getValue() == "")
		{
			_resources.fields['amsModelType'].markInvalid(_translationMap['FldRequired']);
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
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'TradeConfiguration'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'TradeConfiguration')));
					}
				}
				
				//Partial redemption, set default description
				var redGrossNetDefaultValue = IFDS.Xml.getNode(_initDataXML, "List[@id = 'RedGrossNetList']/Element[1]/value");
				IFDS.Xml.setNodeValue(redGrossNetDefaultValue, _translationMap['NotApplicable']);

				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateDropdowns();
				addChangeHandlers();				
				populateScreen();
				clearChangeFlag();			
			}		
		}
		
		,selectERISAOptnHandler: function(fld)
		{
			var fundERISAOptn = IFDS.Xml.getNodeValue((_addMode)?_updatedClassDataXML:_existingClassDataXML, 'fundERISAOptn');
			/**
			 ** ERISA Eligible at fund level (02) and
			 ** ERISA Eligible at class level (02)
			 **/
			if (fundERISAOptn == '02' && fld.getValue() == '02') // ERISA Eligible
			{
				_resources.fields['erisaClassGroup'].reset();
				_resources.fields['erisaClassGroup'].enableField();
			}else{ 
				if (fundERISAOptn != '02' && fld.getValue() == '02'){
					DesktopWeb.Util.displayError(_translationMap['ClassCannotBeERISA']);
					fld.setValue(fld.oldValue);
				}
				_resources.fields['erisaClassGroup'].reset();
				_resources.fields['erisaClassGroup'].disableField();
			}
		}
      
		,updateClassList: function(fundcode,classcode)
		{				
		var dataXML = IFDS.Xml.newDocument('data');		
		IFDS.Xml.addSingleNode(dataXML, 'fundCode', fundcode);
		 //do Ajax Call for get Class List
		 DesktopWeb.Ajax.doSmartviewCall(_classSearchView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])
			
			function responseHandler(responseXML)
			{										
				var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _classSearchView + 'Response')); 
				if (smartviewResults.successful)
				{							
					_resources.fields['freeRollCl'].loadData(IFDS.Xml.getNode(responseXML, '//Classes'), null);					
					if (classcode != null) _resources.fields['freeRollCl'].setValue(classcode);
					else _resources.fields['freeRollCl'].reset();
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
				if (_changeFlag)
				{		
					updateXML();					
					DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
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
				updateXML();									
				DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
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

		, doAMSCheck: function(val)
		{			
			if (val)
			{
				_resources.fields['amsModelType'].enable();		
				_resources.fields['amsModelType'].reset();				
			}
			else
			{
				_resources.fields['amsModelType'].disable();
				_resources.fields['amsModelType'].setValue("00");	
			}
		}		
	}	
}	