/*********************************************************************************************
 * @file	ClassSetup_FeeConfig.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Fee Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_FeeConfig.Controller.js
 *
 * Purpose  : Fee Configuration screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Fee Configuration screens
 *
 * History  : 
 *
 *  25 Nov 2012 H.Sartsangchan P0207062 FN01 MF/MFR Enhancement
 *          - Rearrange Screen Transfer fee , Management Fee
 *          - Add new Management Fee Rebate panel
 *          - Add new 5 SMVComboobox Fields
 *
 *  02 May 2013 G.Thawornwachirakun P0181067 IN3297463 T53495
 *          - Update to set dynamic allowBlank on Acquisition Based on 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  21 May 2014 Narin Suanlamyai P0201832 FN01 DFT0033660 --> CHG0034984 T55158 
 *             - Fixed date format displaying of IWT section
 *
 *  24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *             - Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration.
 *
 *  07 May 2018 Pao - Supareuk S.
 *  		In goToScreen function, we changed a way to show the page from window.location 
 *  		using buildURL to DesktopWeb.Util.goToScreen. This is to solve an issue when 
 *  		user's profile has too many slot attached. If the session is included, the page
 *  		will be broken as too large.
 */
DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
		
	var _addMode = null;
	var _screenId = "FeeConfig";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	var _loadType = null;
	var _perfFeeChangeToApplicable = false;
	
	
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
			_resources.fields['tfrFeeType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'FeeTypeList']"));		
			_resources.fields['tfrBasedOn'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'BasedOnBELTFRList']"));
			_resources.fields['howPaid'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'HowPaidList']"));
			_resources.fields['iwt']['deminimisOpt'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'deminimisOptsList']"));
			_resources.fields['iwt']['mfrTaxOpt'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'mfrTaxOptList']"));
			_resources.fields['fel']['feeType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'FeeTypeList']"));
			_resources.fields['fel']['basedOn'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'BasedOnList']"));
			_resources.fields['fel']['howPaid'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'HowPaidList']"));
			_resources.fields['bel']['feeType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'FeeTypeList']"));
			_resources.fields['bel']['basedOn'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'BasedOnBELTFRList']"));
			_resources.popups['feeScale'].getField('feeCode').loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'FeeCodeList']"));			
		}
		catch(e){throw new Error("Error loading data from init XML - " + e.description)}
	}	
	
	function populateScreen()
	{
		var feeConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration');
		if (_addMode)
		{
			_loadType = IFDS.Xml.getNodeValue(_updatedClassDataXML, 'ClassBasic/loadType');
		}
		else
		{
			_loadType = IFDS.Xml.getNodeValue(_existingClassDataXML, 'ClassBasic/loadType');
		}
		
		for (var i in _resources.fields)
		{
			if (i != 'fel' && i != 'bel' && i != 'iwt')
			{
				setInitialFieldValue(_resources.fields[i], IFDS.Xml.getNodeValue(feeConfigXML, i));		
			}
		}
		
		if (IFDS.Xml.getNodeValue(_initDataXML, 'Controls/tfrApplicable') == 'yes')
		{
			_resources.fields['tfRebate'].enableField();
		}else{
			_resources.fields['tfRebate'].disableField();
		}
		
		var feeScalesXML = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration/FeeDetlScales');
		setInitialFieldValue(_resources.popups['feeScale'].getField('feeCode'), IFDS.Xml.getNodeValue(feeScalesXML, 'feeCode'));
		setInitialFieldValue(_resources.popups['feeScale'].getField('level'), IFDS.Xml.getNodeValue(feeScalesXML, 'level'));
		setInitialFieldValue(_resources.popups['feeScale'].getField('lower'), IFDS.Xml.getNodeValue(feeScalesXML, 'lower'));
		setInitialFieldValue(_resources.popups['feeScale'].getField('upper'), IFDS.Xml.getNodeValue(feeScalesXML, 'upper'));
		setInitialFieldValue(_resources.popups['feeScale'].getField('rate'), IFDS.Xml.getNodeValue(feeScalesXML, 'rate'));
		setInitialFieldValue(_resources.popups['feeScale'].getField('deff'),  DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(feeScalesXML, 'deff')));		
		
		if (_loadType != 'NOL' && _loadType != 'GI' && _loadType != 'CB')		
		{
			Ext.getCmp('loadtype_container').show();
			
			if (_loadType == 'FEL')
			{
				var frontEndLoadXML = IFDS.Xml.getNode(feeConfigXML, 'FrontEndLoad');
				Ext.getCmp('fel_fieldset').show();
				
				if (frontEndLoadXML)
				{
					for (var i in _resources.fields['fel'])
					{
						setInitialFieldValue(_resources.fields['fel'][i], IFDS.Xml.getNodeValue(frontEndLoadXML, i));
					}

					var reqACQBasedon = IFDS.Xml.getNodeValue(_initDataXML, "//reqACQBasedon");				
					if (reqACQBasedon !== 'undefined' && (reqACQBasedon == 'E' || reqACQBasedon == 'e'))
						_resources.fields['fel']['basedOn'].allowBlank = false;
					else
						_resources.fields['fel']['basedOn'].allowBlank = true;
				}
				else
				{
					IFDS.Xml.addSingleNode(feeConfigXML, 'FrontEndLoad');
				}		
			}
			else if (_loadType != 'FEL' && _loadType != 'NOL')
			{
				var backEndLoadXML = IFDS.Xml.getNode(feeConfigXML, 'BackEndLoad');					
				Ext.getCmp('bel_fieldset').show();
				if (backEndLoadXML)
				{
					for (var i in _resources.fields['bel'])
					{
						setInitialFieldValue(_resources.fields['bel'][i], IFDS.Xml.getNodeValue(backEndLoadXML, i));	
					}
				}
				else
				{
					IFDS.Xml.addSingleNode(feeConfigXML, 'BackEndLoad');
				}
				
				_resources.fields['bel']['feeType'].setValue(2);
				_resources.fields['bel']['feeType'].disableField();
				_resources.fields['bel']['basedOn'].setValue(4);
				_resources.fields['bel']['basedOn'].disableField();
			}
		}
		
		var displayIWT = null;
		
		if (_addMode)
		{
			var isIWTDomiciledFund = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//IWTDomiciledFund').toLowerCase() == 'yes';
			var isIWTEnabled = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//IWTEnabled').toLowerCase() == 'yes';
			displayIWT = isIWTDomiciledFund && isIWTEnabled;
		}
		else
		{
			displayIWT = (IFDS.Xml.getNodeValue(feeConfigXML, 'IWTDomiciledFund').toLowerCase() == 'yes' &&	
							  IFDS.Xml.getNodeValue(feeConfigXML, 'IWTEnabled').toLowerCase() == 'yes')
		}
			
		if (displayIWT)
		{
			Ext.getCmp('iwt_container').show();
			Ext.getCmp('feeScales_fieldset2').add(_resources.grids['feeScale']);
			Ext.getCmp('feeScales_fieldset2').doLayout();

			if(_addMode)
			{
				var strIWTNode = '<IWT></IWT>';
				IFDS.Xml.appendNode(feeConfigXML, IFDS.Xml.stringToXML(strIWTNode));

				var iwtXMLNodeInit = IFDS.Xml.getNode(feeConfigXML, 'IWT');
				var deemedDate1 = IFDS.Xml.getNodeValue(feeConfigXML, 'deemedDate1');
				var deemedDate2 = IFDS.Xml.getNodeValue(feeConfigXML, 'deemedDate2');
				IFDS.Xml.addSingleNode(iwtXMLNodeInit, 'deemedDate1', deemedDate1);
				IFDS.Xml.addSingleNode(iwtXMLNodeInit, 'deemedDate2', deemedDate2);
			}

			var iwtXMLNode = IFDS.Xml.getNode(feeConfigXML, 'IWT');

			for (var i in _resources.fields['iwt'])
			{
				setInitialFieldValue(_resources.fields['iwt'][i], IFDS.Xml.getNodeValue(iwtXMLNode, i));	
			}
		}
		else
		{
			Ext.getCmp('feeScales_fieldset1').show();
			Ext.getCmp('feeScales_fieldset1').add(_resources.grids['feeScale']);
			Ext.getCmp('feeScales_fieldset1').doLayout();
		}
		
        if(IFDS.Xml.getNode(feeConfigXML, 'perfFeeFlag') && IFDS.Xml.getNodeValue(feeConfigXML, 'perfFeeFlag')!=''){			
			Ext.getCmp('perfFeeFlag_fieldset').show();
			setInitialFieldValue(_resources.fields['perfFeeFlag'],IFDS.Xml.getNodeValue(feeConfigXML, 'perfFeeFlag'));
		}		
		else{			
			Ext.getCmp('perfFeeFlag_fieldset').hide();		 
		}		
		
		_resources.grids['feeScale'].loadData(IFDS.Xml.getNode(feeConfigXML, 'FeeDetlScales'));
		
				
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
			if (i != 'bel' && i != 'fel' && i != 'iwt')
			{
				addHandler(_resources.fields[i]);
			}
		}
		
		for ( var i in _resources.fields['bel'])
		{
			addHandler(_resources.fields['bel'][i]);
		}
		
		for ( var i in _resources.fields['fel'])
		{
			addHandler(_resources.fields['fel'][i]);
		}
		
		for ( var i in _resources.fields['iwt'])
		{
			addHandler(_resources.fields['iwt'][i]);
		}
		
		/*************************************************
		 ** Special for Performance Fee Flag
		 ** Add flag to redirect to performance fee screen
		 *************************************************/
		if(_resources.fields['perfFeeFlag'])
		{
			 _resources.fields['perfFeeFlag'].addListener('change', function(combo, newVal, oldVal){
				if(oldVal == 'no' && newVal == 'yes')
				{
					_perfFeeChangeToApplicable = true;
				}else{
					_perfFeeChangeToApplicable = false;
				}
			 })
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
		var feeConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration');
		
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
			if (i != 'bel' && i != 'fel' && i != 'iwt')
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
		}
		
		if (_loadType != 'NOL' && _loadType != 'GI' && _loadType != 'CB')		
		{
			if (_loadType == "FEL")
			{
				for (var i in _resources.fields['fel'])
				{
					xmlWriteFn(i, _resources.fields['fel'][i].getValue(), IFDS.Xml.getNode(feeConfigXML, 'FrontEndLoad'));		
				}
				removeLoadTypeNode(feeConfigXML, 'BackEndLoad');
			}
			
			if (_loadType != 'FEL')
			{
				for (var i in _resources.fields['bel'])
				{
					xmlWriteFn(i, _resources.fields['bel'][i].getValue(), IFDS.Xml.getNode(feeConfigXML, 'BackEndLoad'));		
				}
				removeLoadTypeNode(feeConfigXML, 'FrontEndLoad');
			}
		}else{
			removeLoadTypeNode(feeConfigXML, 'FrontEndLoad');
			removeLoadTypeNode(feeConfigXML, 'BackEndLoad');
		}
		
		var scaleDetlNodes = IFDS.Xml.getNodes(feeConfigXML, 'FeeDetlScales/FeeScale');
		for (var i = 0; i < scaleDetlNodes.length; i++)
		{
			IFDS.Xml.deleteNode(scaleDetlNodes[i]);
		}				
		Ext.each(_resources.grids['feeScale'].getAllRecords(), function(rec){addScaleRecordToXML(rec)})

		if (_addMode)
		{
			var strIWTNode = '<IWT></IWT>';
			IFDS.Xml.appendNode(feeConfigXML, IFDS.Xml.stringToXML(strIWTNode));
		}
			
		for (var i in _resources.fields['iwt'])
		{
			var iwtContext = IFDS.Xml.getNode(feeConfigXML, 'IWT');

			if (_resources.fields['iwt'][i] instanceof DesktopWeb.Controls.DateField)
			{			
				xmlWriteFn(i, _resources.fields['iwt'][i].getSMVDateString(), iwtContext);
			}
			else
			{
				xmlWriteFn(i, _resources.fields['iwt'][i].getValue(), iwtContext);		
			}
		}
		
		// Remove PerfFeeConfig object from XML when perfFeeFlag is 'NO'
		if(_resources.fields['perfFeeFlag'].getValue()!='yes')
		{
			var perfFeeConfigNode = IFDS.Xml.getNode(_updatedClassDataXML, 'PerfFeeConfig');
			if(perfFeeConfigNode)IFDS.Xml.deleteNode(perfFeeConfigNode);
		}
		
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? feeConfigXML : context);
			
			var node = IFDS.Xml.getNode(context, fldName);
			
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{			
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? feeConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}	
		
		function addScaleRecordToXML(rec)
		{
			var feeDetlScalesNode = IFDS.Xml.getNode(feeConfigXML, 'FeeDetlScales');
			var recordNode = IFDS.Xml.addSingleNode(feeDetlScalesNode, 'FeeScale');			
			IFDS.Xml.addSingleNode(recordNode, 'runMode', rec.data['runMode']);
			IFDS.Xml.addSingleNode(recordNode, 'scaleUUID', rec.data['scaleUUID']);
			IFDS.Xml.addSingleNode(recordNode, 'level', rec.data['level']);
			IFDS.Xml.addSingleNode(recordNode, 'deff', DesktopWeb.Util.getSMVDateValue(rec.data['deff']));
			IFDS.Xml.addSingleNode(recordNode, 'feeCode', rec.data['feeCode']);			
			IFDS.Xml.addSingleNode(recordNode, 'lower', rec.data['lower']);
			IFDS.Xml.addSingleNode(recordNode, 'upper', rec.data['upper']);
			IFDS.Xml.addSingleNode(recordNode, 'rate', rec.data['rate']);
		}
		
		function removeLoadTypeNode(contextXML, loadType)
		{
			var loadTypeNode = IFDS.Xml.getNode(contextXML, loadType);
			if (loadTypeNode)
			{
				IFDS.Xml.deleteNode(loadTypeNode);
			}
		}
	}
	
	function updateBreadcrumb()
	{
		if(_resources.fields['perfFeeFlag'].getValue()!='yes')
		{
			//remove item from screen def
			var perfFeeConfig = IFDS.Xml.getNode(_screenDefListXML, "Screen[id='PerformanceFee']");
			if(perfFeeConfig)
			{
				IFDS.Xml.deleteNode(perfFeeConfig);
				DesktopWeb.Ajax.doUpdateCache({ScreenDefList: _screenDefListXML}, function(){});
				DesktopWeb.Ajax.doUpdateCache({ScreenDefList: _screenDefListXML}, function(){});
			}
			_resources.breadCrumbList.removeItem('PerformanceFee');
		}else{
			//insert item 
			var feeConfigNode = IFDS.Xml.getNode(_screenDefListXML, "Screen[id='FeeConfig']");
			var perfFeeConfigNode = IFDS.Xml.getNode(_screenDefListXML, "Screen[id='PerformanceFee']");
			if(feeConfigNode && !perfFeeConfigNode)
			{
				var screenXML = IFDS.Xml.newDocument("Screens");
				perfFeeConfigNode = IFDS.Xml.addSingleNode(screenXML, "Screen");
				IFDS.Xml.addSingleNode(perfFeeConfigNode, "id", "PerformanceFee");
				IFDS.Xml.addSingleNode(perfFeeConfigNode, "label", _translationMap['PerfFeeConfig']);	
				feeConfigNode.parentNode.insertBefore(perfFeeConfigNode, feeConfigNode.nextSibling);
				DesktopWeb.Ajax.doUpdateCache({ScreenDefList: _screenDefListXML}, function(){});
				DesktopWeb.Ajax.doUpdateCache({ScreenDefList: _screenDefListXML}, function(){});
				_resources.breadCrumbList.insertItem('PerformanceFee', _translationMap['PerfFeeConfig'], _resources.breadCrumbList.getItemIndex('FeeConfig') + 1);
				if(!_addMode)_resources.breadCrumbList.enableItem('PerformanceFee');
			}							
		}
		_resources.breadCrumbList.doLayout();
	}
	
	function validateScreen()
	{				
		var isValid = true;		
		for (var i in _resources.fields)
		{						
			if (_resources.fields[i] == _resources.fields['iwt'])			
				continue;
						
			if (_resources.fields[i].isValid)
			{
				isValid = _resources.fields[i].isValid() && isValid;
			}								
		}
		
		if (_loadType == "FEL")
		{
			for (var i in _resources.fields['fel'])
			{			
				if (_resources.fields['fel'][i].isValid)
				{
					isValid = _resources.fields['fel'][i].isValid() && isValid;
				}								
			}
			
			if (_resources.fields['fel']['feeType'].getValue() == 2 &&
				_resources.grids['feeScale'].getAllRecords().length == 0)
			{
				DesktopWeb.Util.displayError(_translationMap["Error_NoFeeScale"]);
				isValid = false
			}
		}
		
		if (_loadType != 'FEL' && _loadType != 'NOL' && _loadType != 'GI' && _loadType != 'CB')
		{
			for (var i in _resources.fields['bel'])
			{			
				if (_resources.fields['bel'][i].isValid)
				{
					isValid = _resources.fields['bel'][i].isValid() && isValid;
				}								
			}
			
			if (_resources.fields['bel']['feeType'].getValue() == 2 &&
				_resources.grids['feeScale'].getAllRecords().length == 0)
			{
				DesktopWeb.Util.displayError(_translationMap["Error_NoFeeScale"]);
				isValid = false;
			}
		}
		var feeConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration');
		
		if(IFDS.Xml.getNode(feeConfigXML, 'perfFeeFlag') && IFDS.Xml.getNodeValue(feeConfigXML, 'perfFeeFlag')!=''){
			if (_resources.fields['perfFeeFlag'].getValue() == "")
			{				
				_resources.fields['perfFeeFlag'].markInvalid(_translationMap['FldRequired']);
				isValid = false;
			}
		}
				
		return isValid;
	}
	
	function askToPerfFeeScreen()
	{
		DesktopWeb.Util.displayPrompt(_translationMap['RedirectMsg'], callback);
		
		function callback(redirect)
		{
			if (redirect=='ok')
			{
				goToScreen('PerformanceFee');
			}
		}
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
									
		DesktopWeb.Util.goToScreen('ClassSetup_' + screenName, urlParams);
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
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'FeeConfiguration')));
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
		
		,getListValueDesc: function(listName, value)
		{
			var valueDesc = null
			valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "List[@id = '" + listName + "']/Element[code = '" + value + "']/value");			
			if (valueDesc == null)
			{
				valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");
			}
			return valueDesc;
		}
		
		,updateScaleActionButtons: function()
		{
			var selectedRecord = _resources.grids['feeScale'].getSelectedRecord();	
			
			if (selectedRecord)
			{
				_resources.grids['feeScale'].enableButton('modBtn');
				_resources.grids['feeScale'].enableButton('delBtn');				
			}
			else
			{
				_resources.grids['feeScale'].disableButton('modBtn');
				_resources.grids['feeScale'].disableButton('delBtn');
			}		
		}
		
		,openScalePopup: function(action)
		{
			if (action == this.ADD)
			{
				_resources.grids['feeScale'].clearSelectedRecord();
			}
			_resources.popups['feeScale'].init(action);
			_resources.popups['feeScale'].show();
		}
		
		,closeScalePopup: function()
		{
			_resources.popups['feeScale'].hide();
		}
		
		,saveFeeScale: function(action, data)
		{
			if (action == this.ADD)
			{
				_resources.grids['feeScale'].addRecord(data);				
				_resources.grids['feeScale'].selectLastRecord();				
			}
			else
			{
				// annoying case where mod/del a brand new record
				if (_resources.grids['feeScale'].getSelectedRecord().data['runMode'] == this.ADD)
				{
					if (action == this.DEL)
					{
						_resources.grids['feeScale'].removeSelectedRecord();						
					}
					else
					{
						data['runMode'] = this.ADD
						_resources.grids['feeScale'].updateSelectedRecord(data);
					}					
				}
				else
				{
					_resources.grids['feeScale'].updateSelectedRecord(data);
					_self.updateScaleActionButtons();									
				}
			}					
			setChangeFlag();	
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
					if(_perfFeeChangeToApplicable && screenName != 'PerformanceFee')
					{
						askToPerfFeeScreen();
					}else{
						goToScreen(screenName);
					}
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
				if(_perfFeeChangeToApplicable) askToPerfFeeScreen();
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