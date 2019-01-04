/*********************************************************************************************
 * @file	ClassSetup_DistConfig.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Distribution Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_DistConfig.Controller.js	
 *
 * Purpose  : Controller file for Distribution Configuration screen, part of Class Setup flow
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Distribution Configuration screen
 *
 * History  :  
 *	27 Jun 2013 N. Suanlamyai P0214690 T53774
 *			- Add logic to control two new distribution types
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 */
 
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _addMode = null;
	var _screenId = "DistConfig";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;	
	var _multiDistType = false;
	
	
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
		_resources.fields['distribMode'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DistribModeList']"));
		_resources.fields['distribRateEdit'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'DistribRateEditList']"));
		_resources.fields['adjustIDFlag'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'AdjustIDFlagList']"));
		if(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'GrpTrTypeList']"))
		{
			_resources.fields['grpTrType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'GrpTrTypeList']"));
		}
	}
	
	function populateScreen()
	{
		var distConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'DistributionConfig');
		
		// populate the global variable
		_multiDistType = IFDS.Xml.getNodeValue(distConfigXML, 'multiDistType') == 'yes';
		
		setInitialFieldValue(_resources.fields['id'], IFDS.Xml.getNodeValue(distConfigXML, 'id'));
		setInitialFieldValue(_resources.fields['cd'], IFDS.Xml.getNodeValue(distConfigXML, 'cd'));
		
		_resources.fields['idAdditional_ci'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'idCI') == 'yes');
		_resources.fields['idAdditional_si'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'idSI') == 'yes');
		
		if (IFDS.Xml.getNodeValue(distConfigXML, 'nextRecDate') != '') {
			_resources.fields['nextRecDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(distConfigXML, 'nextRecDate')));
			
		}
		_resources.fields['nextRecDate'].disableField();
			
		if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/enableDistribMode') == 'yes')
		{
			_resources.fields['distribMode'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'distribMode'));
			_resources.fields['distribMode'].enableField();
		}else{
			_resources.fields['distribMode'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'distribMode'));
			_resources.fields['distribMode'].disableField();
		}
		
		
		if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/enableDistribRateEdit') == 'yes')
		{
			_resources.fields['distribRateEdit'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'distribRateEdit'));
			_resources.fields['distribRateEdit'].enableField();
		}else{
			_resources.fields['distribRateEdit'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'distribRateEdit'));
			_resources.fields['distribRateEdit'].disableField();
		}
		
		defaultAdjustIDFlag(false);
		
		if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/enableGrpTrTypeEdit') == 'yes')
		{
				_resources.fields['grpTrType'].setValue(IFDS.Xml.getNodeValue(_initDataXML, 'DefaultValues/DistributionConfig/grpTrType'));
				_resources.fields['grpTrType'].enableField();
				
		}else{
				_resources.fields['grpTrType'].disableField();
		}
		
	
		if (_addMode)
		{			
			if (IFDS.Xml.getNodeValue(distConfigXML, 'id') == 'yes')
			{
				Ext.getCmp("idDetailsForm").enable();
				_resources.fields['idDefInvestOpt_cs'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'idDefInvestOpt') == 'CS');
				_resources.fields['idDefInvestOpt_ri'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'idDefInvestOpt') == 'RI');
				
				var idOverrideOpt = IFDS.Xml.getNodeValue(distConfigXML, 'idOverrideOpt');
				_resources.fields['idOverrideOpt_cs'].setValue(idOverrideOpt.indexOf('CS') != -1);
				_resources.fields['idOverrideOpt_rd'].setValue(idOverrideOpt.indexOf('RD') != -1);
				_resources.fields['idOverrideOpt_ri'].setValue(idOverrideOpt.indexOf('RI') != -1);

				if (_multiDistType)
				{
					Ext.getCmp("idAdditionalDetailsForm").enable();
				}else{
					Ext.getCmp("idAdditionalDetailsForm").disable();
				}
			}
			else
			{
				Ext.getCmp("idDetailsForm").disable();
			}
						
			if (IFDS.Xml.getNodeValue(distConfigXML, 'cd') == 'yes')
			{
				_resources.fields['cdDefInvestOpt_cs'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'cdDefInvestOpt') == 'CS');
				_resources.fields['cdDefInvestOpt_ri'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'cdDefInvestOpt') == 'RI');
				
				var idOverrideOpt = IFDS.Xml.getNodeValue(distConfigXML, 'cdOverrideOpt');
				_resources.fields['cdOverrideOpt_cs'].setValue(idOverrideOpt.indexOf('CS') != -1);
				_resources.fields['cdOverrideOpt_rd'].setValue(idOverrideOpt.indexOf('RD') != -1);
				_resources.fields['cdOverrideOpt_ri'].setValue(idOverrideOpt.indexOf('RI') != -1);
			}
			else
			{
				Ext.getCmp("cdDetailsForm").disable();
			}
			
			if (IFDS.Xml.getNodeValue(distConfigXML, 'grpTrType') != null)
			{
				_resources.fields['grpTrType'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'grpTrType'));
			}
		
		}
		else
		{
			if (IFDS.Xml.getNodeValue(distConfigXML, 'id') == 'yes')
			{
				_resources.fields['id'].disableField();
				_resources.fields['idDefInvestOpt_cs'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'idDefInvestOpt') == 'CS');
				_resources.fields['idDefInvestOpt_ri'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'idDefInvestOpt') == 'RI');
				
				var idOverrideOpt = IFDS.Xml.getNodeValue(distConfigXML, 'idOverrideOpt');
				_resources.fields['idOverrideOpt_cs'].setValue(idOverrideOpt.indexOf('CS') != -1);
				_resources.fields['idOverrideOpt_rd'].setValue(idOverrideOpt.indexOf('RD') != -1);
				_resources.fields['idOverrideOpt_ri'].setValue(idOverrideOpt.indexOf('RI') != -1);

				if (_multiDistType)
				{
					Ext.getCmp("idAdditionalDetailsForm").enable();
				}else{
					Ext.getCmp("idAdditionalDetailsForm").disable();
				}
			}	
			else
			{
				Ext.getCmp('id_fieldset').disable();
				_resources.fields['id'].disableField();			
			}
			
			if (IFDS.Xml.getNodeValue(distConfigXML, 'cd') == 'yes')
			{
				_resources.fields['cd'].disableField();
				_resources.fields['cdDefInvestOpt_cs'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'cdDefInvestOpt') == 'CS');
				_resources.fields['cdDefInvestOpt_ri'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'cdDefInvestOpt') == 'RI');
				
				var cdOverrideOpt = IFDS.Xml.getNodeValue(distConfigXML, 'cdOverrideOpt');
				_resources.fields['cdOverrideOpt_cs'].setValue(cdOverrideOpt.indexOf('CS') != -1);
				_resources.fields['cdOverrideOpt_rd'].setValue(cdOverrideOpt.indexOf('RD') != -1);
				_resources.fields['cdOverrideOpt_ri'].setValue(cdOverrideOpt.indexOf('RI') != -1);
			}	
			else
			{
				Ext.getCmp('cd_fieldset').disable();		
				_resources.fields['cd'].disableField();	
			}
			if (IFDS.Xml.getNodeValue(distConfigXML, 'grpTrType') != null)
			{
				_resources.fields['grpTrType'].setValue(IFDS.Xml.getNodeValue(distConfigXML, 'grpTrType'));
			}
		}
		
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
	
	function defaultAdjustIDFlag(reset)
	{
		var distConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'DistributionConfig');
		
		if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/enableDistribMode') == 'yes')
		{
			if (_resources.fields['distribMode'].getValue() == '01') // Income
			{
				if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/backDateNonNotional') == 'yes')
				{
					_resources.fields['adjustIDFlag'].setValue(reset?'01':IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag'));
					_resources.fields['adjustIDFlag'].enableField();
				}else{
					_resources.fields['adjustIDFlag'].setValue(reset?'01':IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag'));
					_resources.fields['adjustIDFlag'].disableField();
				}
			}else{
				if (_resources.fields['distribMode'].getValue() == '02') // Accumulation
				{
					if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/backDateNotional') == 'yes')
					{
						_resources.fields['adjustIDFlag'].setValue(reset?'01':IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag'));
						_resources.fields['adjustIDFlag'].enableField();
					}else{
						_resources.fields['adjustIDFlag'].setValue(reset?'01':IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag'));
						_resources.fields['adjustIDFlag'].disableField();
					}
				}else{
					_resources.fields['adjustIDFlag'].setValue(reset?'':IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag'));
					_resources.fields['adjustIDFlag'].disableField();
				}
			}
		}else{
			_resources.fields['adjustIDFlag'].setValue(reset?'':IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag'));
			_resources.fields['adjustIDFlag'].disableField();
		}
	}
	
	function addChangeHandlers()
	{		
		for (var i in _resources.fields)
		{
			addHandler(_resources.fields[i]);						
		}
		
		_resources.fields['id'].addListener('select', function(){handleApplicableStatusChange('id')});
		_resources.fields['cd'].addListener('select', function(){handleApplicableStatusChange('cd')});
		
		
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
	
	function handleApplicableStatusChange(type)
	{
		var applicable = _resources.fields[type].getValue();
		if (applicable == 'yes')
		{
			Ext.getCmp(type + "DetailsForm").enable();
			_resources.fields[type + 'DefInvestOpt_cs'].setValue(true);
			
			if (type = 'id')
			{
				if (_multiDistType)
				{
					Ext.getCmp("idAdditionalDetailsForm").enable();
				}else{
					Ext.getCmp("idAdditionalDetailsForm").disable();
				}
			}
		}
		else
		{
			Ext.getCmp(type + "DetailsForm").disable();
			
			_resources.fields[type + 'DefInvestOpt_cs'].setValue(false);
			_resources.fields[type + 'DefInvestOpt_ri'].setValue(false);
			
			_resources.fields[type + 'OverrideOpt_cs'].setValue(false);
			_resources.fields[type + 'OverrideOpt_rd'].setValue(false);
			_resources.fields[type + 'OverrideOpt_ri'].setValue(false);
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
		var distConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'DistributionConfig');
		
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
	
		xmlWriteFn('id', _resources.fields['id'].getValue());
		xmlWriteFn('idDefInvestOpt', (_resources.fields['idDefInvestOpt_cs'].getValue() ? 'CS': 'RI'));
		xmlWriteFn('distribMode', _resources.fields['distribMode'].getValue());
		xmlWriteFn('nextRecDate', _resources.fields['nextRecDate'].getSMVDateString());
		xmlWriteFn('distribRateEdit', _resources.fields['distribRateEdit'].getValue());
		xmlWriteFn('adjustIDFlag', _resources.fields['adjustIDFlag'].getValue());
		
		if ( _multiDistType )
		{
			xmlWriteFn('idCI', _resources.fields['idAdditional_ci'].getValue()?'yes':'no');
			xmlWriteFn('idSI', _resources.fields['idAdditional_si'].getValue()?'yes':'no');
		}else{
			xmlWriteFn('idCI', 'no');
			xmlWriteFn('idSI', 'no');
		}

		if(IFDS.Xml.getNodeValue(_initDataXML, 'Controls/enableGrpTrTypeEdit') == 'yes')
		{
			xmlWriteFn('grpTrType', _resources.fields['grpTrType'].getValue());
		}
		
		var idOverrideOpt = [];
		if (_resources.fields['idOverrideOpt_cs'].getValue())
		{
			idOverrideOpt.push('CS')
		}
		if (_resources.fields['idOverrideOpt_rd'].getValue())
		{
			idOverrideOpt.push('RD')
		}
		if (_resources.fields['idOverrideOpt_ri'].getValue())
		{
			idOverrideOpt.push('RI');
		}
		xmlWriteFn('idOverrideOpt', idOverrideOpt.toString());

		xmlWriteFn('cd', _resources.fields['cd'].getValue());
		xmlWriteFn('cdDefInvestOpt', (_resources.fields['cdDefInvestOpt_cs'].getValue() ? 'CS': 'RI'));
		var cdOverrideOpt = [];
		if (_resources.fields['cdOverrideOpt_cs'].getValue())
		{
			cdOverrideOpt.push('CS')
		}
		if (_resources.fields['cdOverrideOpt_rd'].getValue())
		{
			cdOverrideOpt.push('RD')
		}
		if (_resources.fields['cdOverrideOpt_ri'].getValue())
		{
			cdOverrideOpt.push('RI');
		}
		xmlWriteFn('cdOverrideOpt', cdOverrideOpt.toString());
				

		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? distConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? distConfigXML : context);
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
				if (_addMode)
				{
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'DistributionConfig'))
					{
						IFDS.Xml.addSingleNode(_updatedClassDataXML, 'DistributionConfig');
					}																				
				}
				else
				{
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'DistributionConfig'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'DistributionConfig')));
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
		
		,resetDefaultAdjustIDFlag: function()
		{
			defaultAdjustIDFlag(true);
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
	}	
}	