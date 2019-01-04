/*********************************************************************************************
 * @file	ClassSetup_GIAAttributes.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for GIA Attributes screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
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
	var _screenId = "GIAAttributes";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	
	var allowFeeUpdates = false;
	
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
			_resources.fields['simTermList'].loadAvailableData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'SimpleTermList']"))
			_resources.fields['simCredFreq'].loadAvailableData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'SimpleCreditFreq']"));
							
			_resources.fields['comTermList'].loadAvailableData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'CompoundTermList']"))
			_resources.fields['comCredFreq'].loadAvailableData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'CompoundCreditFreq']"));
						
			_resources.fields['defRenewInstr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'DefRenewList']"));			
			_resources.fields['redemOrder'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'RedemOrderList']"));
			_resources.fields['mvaCurrMktRate'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'MVACurrMktRate']"));
			_resources.fields['mvaGLOff'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'MVAGLOffset']"));
			_resources.fields['mvaPayNetGain'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'MVAPayNetGain']"));
			_resources.fields['mvaEmpAcct'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'MVAonEmpAcct']"));
			
			_resources.fields['adminFeeApply'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'AdminFeeApplyTo']"));
			_resources.fields['feeTypeAttr'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'AttrFeeTypeList']"));					
		}
		catch(e){throw new Error("Error loading data from init XML - " + e.description)}		
	}
	
	function populateScreen()
	{		
		var giaAttrXML = IFDS.Xml.getNode(_updatedClassDataXML, 'GIAAttributes');							
		
		var intCalcMthd = IFDS.Xml.getNodeValue(giaAttrXML, 'intCalcMthd');
		_resources.fields['intCalcMthd_sim'].checked = (intCalcMthd == 'B' || intCalcMthd == 'S');
		_resources.fields['simTermList'].removeAllFromSelected();
		if (IFDS.Xml.getNodeValue(giaAttrXML, 'simTermList'))
		{
			_resources.fields['simTermList'].setSelectedByData('code', IFDS.Xml.getNodeValue(giaAttrXML, 'simTermList').split(","));
		}
		_resources.fields['simCredFreq'].removeAllFromSelected();
		if (IFDS.Xml.getNodeValue(giaAttrXML, 'simCredFreq'))
		{		
			_resources.fields['simCredFreq'].setSelectedByData('code', IFDS.Xml.getNodeValue(giaAttrXML, 'simCredFreq').split(","));
		}
				
		_resources.fields['intCalcMthd_com'].checked = (intCalcMthd == 'B' || intCalcMthd == 'C');
		_resources.fields['comTermList'].removeAllFromSelected();
		if (IFDS.Xml.getNodeValue(giaAttrXML, 'comTermList'))
		{		
			_resources.fields['comTermList'].setSelectedByData('code', IFDS.Xml.getNodeValue(giaAttrXML, 'comTermList').split(","));
		}
		_resources.fields['comCredFreq'].removeAllFromSelected();
		if (IFDS.Xml.getNodeValue(giaAttrXML, 'comCredFreq'))
		{
			_resources.fields['comCredFreq'].setSelectedByData('code', IFDS.Xml.getNodeValue(giaAttrXML, 'comCredFreq').split(","));
		}
		
		setInitialFieldValue(_resources.fields['defRenewInstr'], IFDS.Xml.getNodeValue(giaAttrXML, 'defRenewInstr'));
		setInitialFieldValue(_resources.fields['redemOrder'], IFDS.Xml.getNodeValue(giaAttrXML, 'redemOrder'));
		
		setInitialFieldValue(_resources.fields['mvaCurrMktRate'], IFDS.Xml.getNodeValue(giaAttrXML, 'mvaCurrMktRate'));
		setInitialFieldValue(_resources.fields['mvaGLOff'], IFDS.Xml.getNodeValue(giaAttrXML, 'mvaGLOff'));
		setInitialFieldValue(_resources.fields['mvaPayNetGain'], IFDS.Xml.getNodeValue(giaAttrXML, 'mvaPayNetGain'));
		setInitialFieldValue(_resources.fields['mvaEmpAcct'], IFDS.Xml.getNodeValue(giaAttrXML, 'mvaEmpAcct'));
		setInitialFieldValue(_resources.fields['adjustFee'], IFDS.Xml.getNodeValue(giaAttrXML, 'adjustFee'));
		setInitialFieldValue(_resources.fields['adjustFeeDate'], DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(giaAttrXML, 'adjustFeeDate')));
		
		setInitialFieldValue(_resources.fields['adminFee'], IFDS.Xml.getNodeValue(giaAttrXML, 'adminFee'));
		setInitialFieldValue(_resources.fields['adminFeeApply'], IFDS.Xml.getNodeValue(giaAttrXML, 'adminFeeApply'));
		setInitialFieldValue(_resources.fields['adminFeeDate'], DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(giaAttrXML, 'adminFeeDate')));
		setInitialFieldValue(_resources.fields['feeTypeAttr'], IFDS.Xml.getNodeValue(giaAttrXML, 'feeTypeAttr'));
		
		_allowFeeUpdates = (IFDS.Xml.getNodeValue(giaAttrXML, 'currBusDate') == IFDS.Xml.getNodeValue(giaAttrXML, 'adminProcDate'));
		
		_resources.grids['feeScale'].loadData(giaAttrXML);
		if (!_allowFeeUpdates)
		{
			_resources.fields['feeTypeAttr'].disableField();
			_resources.fields['adminFee'].disableField();
			_resources.grids['feeScale'].disable();			
		}
		else
		{
			toggleAdminFeeTypeFlds();
		}		
			
		toggleIntCalcMthdFlds();
		
		
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
			if (i != 'intCalcMthd_com' && i != 'intCalcMthd_sim')
			{
				addHandler(_resources.fields[i]);
			}
		}
		
		_resources.fields['intCalcMthd_sim'].onclick = _self.handleIntCalcMthdUpdate;
		_resources.fields['intCalcMthd_com'].onclick = _self.handleIntCalcMthdUpdate;
		
		
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
	
	function toggleIntCalcMthdFlds()
	{
		if (!_resources.fields['intCalcMthd_sim'].checked)
		{
			_resources.fields['simTermList'].removeAllFromSelected();
			_resources.fields['simTermList'].disable();
			_resources.fields['simCredFreq'].removeAllFromSelected();
			_resources.fields['simCredFreq'].disable();
		}
		else
		{
			_resources.fields['simTermList'].enable();
			_resources.fields['simCredFreq'].enable();
		}
		
		if (!_resources.fields['intCalcMthd_com'].checked)
		{
			_resources.fields['comTermList'].removeAllFromSelected();
			_resources.fields['comTermList'].disable();
			_resources.fields['comCredFreq'].removeAllFromSelected();
			_resources.fields['comCredFreq'].disable();
		}
		else
		{
			_resources.fields['comTermList'].enable();
			_resources.fields['comCredFreq'].enable();
		}
		setChangeFlag();
	}
	
	function toggleAdminFeeTypeFlds()
	{
		if (_resources.fields['feeTypeAttr'].getValue() != 2)
		{
			_resources.fields['adminFee'].enableField();
			_resources.grids['feeScale'].clearData();							
			_resources.grids['feeScale'].disable();			
		}
		else
		{
			_resources.fields['adminFee'].clearField();
			_resources.fields['adminFee'].disableField();						
			_resources.grids['feeScale'].enable();
			_resources.grids['feeScale'].enableButton('addBtn')	;						
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
		var giaAttributesXML = IFDS.Xml.getNode(_updatedClassDataXML, 'GIAAttributes');
		
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
				
		
		var intCalcMthd = "";		
		if (_resources.fields['intCalcMthd_sim'].checked && _resources.fields['intCalcMthd_com'].checked)
		{
			intCalcMthd = 'B'
		}
		else if (_resources.fields['intCalcMthd_sim'].checked)
		{
			intCalcMthd = 'S'
		}
		else if (_resources.fields['intCalcMthd_com'].checked)
		{
			intCalcMthd = 'C'
		}		
		xmlWriteFn('intCalcMthd', intCalcMthd);
		
		var simTermSelections = [];			
		Ext.each(_resources.fields['simTermList'].getSelectedRecords(), function(rec){simTermSelections.push(rec.data.code)} );		
		xmlWriteFn('simTermList', simTermSelections.toString());
		var simCredSelections = [];			
		Ext.each(_resources.fields['simCredFreq'].getSelectedRecords(), function(rec){simCredSelections.push(rec.data.code)} );
		xmlWriteFn('simCredFreq', simCredSelections.toString());
		
		var comTermSelections = [];			
		Ext.each(_resources.fields['comTermList'].getSelectedRecords(), function(rec){comTermSelections.push(rec.data.code)} );		
		xmlWriteFn('comTermList', comTermSelections.toString());
		var comCredSelections = [];			
		Ext.each(_resources.fields['comCredFreq'].getSelectedRecords(), function(rec){comCredSelections.push(rec.data.code)} );
		xmlWriteFn('comCredFreq', comCredSelections.toString());
		
		xmlWriteFn('defRenewInstr', _resources.fields['defRenewInstr'].getValue());
		xmlWriteFn('redemOrder', _resources.fields['redemOrder'].getValue());
		
		xmlWriteFn('mvaCurrMktRate', _resources.fields['mvaCurrMktRate'].getValue());
		xmlWriteFn('mvaGLOff', _resources.fields['mvaGLOff'].getValue());
		xmlWriteFn('mvaPayNetGain', _resources.fields['mvaPayNetGain'].getValue());
		xmlWriteFn('mvaEmpAcct', _resources.fields['mvaEmpAcct'].getValue());
		xmlWriteFn('adjustFee', _resources.fields['adjustFee'].getValue());		
		xmlWriteFn('adjustFeeDate', _resources.fields['adjustFeeDate'].getSMVDateString());
		
		xmlWriteFn('adminFeeApply', _resources.fields['adminFeeApply'].getValue());
		xmlWriteFn('feeTypeAttr', _resources.fields['feeTypeAttr'].getValue());
		xmlWriteFn('adminFee', _resources.fields['adminFee'].getValue());
		xmlWriteFn('adminFeeDate', _resources.fields['adminFeeDate'].getSMVDateString());
		
		var scaleDetlNodes = IFDS.Xml.getNodes(giaAttributesXML, 'ScaleDetl');
		for (var i = 0; i < scaleDetlNodes.length; i++)
		{
			IFDS.Xml.deleteNode(scaleDetlNodes[i]);
		}				
		Ext.each(_resources.grids['feeScale'].getAllRecords(), function(rec){addRecordToXML(rec)})
		
				
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? giaAttributesXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? giaAttributesXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}			
		
		function addRecordToXML(rec)
		{
			var recordNode = IFDS.Xml.addSingleNode(giaAttributesXML, 'ScaleDetl');			
			IFDS.Xml.addSingleNode(recordNode, 'runMode', rec.data['runMode']);
			IFDS.Xml.addSingleNode(recordNode, 'scaleID', rec.data['scaleID']);			
			IFDS.Xml.addSingleNode(recordNode, 'lower', rec.data['lower']);
			IFDS.Xml.addSingleNode(recordNode, 'upper', rec.data['upper']);
			IFDS.Xml.addSingleNode(recordNode, 'rate', rec.data['rate']);
		}
	}
	
	function validateScreen()
	{		
		var isValid = true;
		var errorMsg = "";
		
		for (var i in _resources.fields)
		{			
			if (_resources.fields[i].isValid)
			{
				isValid = _resources.fields[i].isValid() && isValid; 
			}								
		}
		
		if (!_resources.fields['intCalcMthd_sim'].checked && !_resources.fields['intCalcMthd_com'].checked)
		{
			errorMsg = _translationMap["NoInterestCalcMethodSelected"];
			isValid = false;
		}
		else
		{
			if ((_resources.fields['intCalcMthd_sim'].checked			
				&& _resources.fields['simTermList'].getSelectedRecords().length == 0)
				|| (_resources.fields['intCalcMthd_com'].checked 
				&& _resources.fields['comTermList'].getSelectedRecords().length == 0))
			{
				errorMsg += (errorMsg.length > 0 ? "<br/><br/>" : "") + _translationMap["NoTermsSelected"];
				isValid = false;
			}
			
			if ((_resources.fields['intCalcMthd_sim'].checked			
				&& _resources.fields['simCredFreq'].getSelectedRecords().length == 0)
				|| (_resources.fields['intCalcMthd_com'].checked 
				&& _resources.fields['comCredFreq'].getSelectedRecords().length == 0))
			{
				errorMsg += (errorMsg.length > 0 ? "<br/><br/>" : "") + _translationMap["NoFreqSelected"];
				isValid = false;
			}
		}
		
		if (_resources.fields['feeTypeAttr'].getValue() == 2 
			&& _resources.grids['feeScale'].getStore().getCount() == 0)
		{
			errorMsg += (errorMsg.length > 0 ? "<br/><br/>" : "") + _translationMap["NoScales"];
			isValid = false;
		}
		
		if (errorMsg.length > 0)
		{
			DesktopWeb.Util.displayError(errorMsg);
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
									
		DesktopWeb.Util.goToScreen('ClassSetup_' + screenName, urlParams);
	}
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'a'
		,MOD: 'm'
		,DEL: 'd'		
						
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
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'GIAAttributes'))
					{
						IFDS.Xml.addSingleNode(_updatedClassDataXML, 'GIAAttributes');
					}
				}
				else
				{
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'GIAAttributes'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'GIAAttributes')));
					}	
				}		
				
				//prompt("", _initDataXML.xml);									
				
				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateDropdowns();
				addChangeHandlers();				
				populateScreen();
				clearChangeFlag();					
			}		
		}
		
		,handlerAdminFeeDateChange: function()
		{
			_allowFeeUpdates = true;
			_resources.fields['feeTypeAttr'].enableField();
			_resources.grids['feeScale'].clearData();
			toggleAdminFeeTypeFlds();					
		}
		
		,handleAdminFeeTypeUpdate: function()
		{			
			toggleAdminFeeTypeFlds();
		}
		
		,handleIntCalcMthdUpdate: function()
		{
			toggleIntCalcMthdFlds();
		}
		
		,updateScaleActionButtons: function()
		{
			var selectedRecord = _resources.grids['feeScale'].getSelectedRecord();	
			
			if (selectedRecord && _allowFeeUpdates)
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
						, callback, _translationMap['ProcMsg_Saving']);
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