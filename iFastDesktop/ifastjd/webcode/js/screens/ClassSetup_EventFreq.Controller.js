/*********************************************************************************************
 * @file	ClassSetup_EventSched.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller file for Event Schedule Setup screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  30 July 2014 Winnie Cheng P0232644 FN01 T78216
 *             - A new field added from Event Schedule screen for AIFMD enhancement
 *  
 *  09 Nov 2018 Winnie C. R19.2
 *  		P0278169-69 Project Spring:SSII-7422 PIMCO DCCS Trading 
 *			Adding NSCC offset field as minutes within 24 hours
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _addMode = null;
	var _screenId = "EventFreq";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	var _selectedDealing = null;
	var _tmpDealingSchedUUIDRunning = 0;
	var _perfFeeFlag = false;
	var _valnNotiFlag = false;
	var _divNotiFlag = false;
	var _valnValidateFlag = true;
	
	var _fundClassListService = "dtClassSetupInit";
	var _valnSchedValidateService = "dtClassSetupUpd";
	
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
	
	function populateDropdowns()
	{
		_resources.fields['valn']['fundGroup'].loadData(getActiveValuationFundGroupList());
		addAddNewFundGroupItem(_resources.fields['valn']['fundGroup'], 'valn');
		_resources.fields['divs']['fundGroup'].loadData(getActiveDividendFundGroupList());
		addAddNewFundGroupItem(_resources.fields['divs']['fundGroup'], 'divs');
		_resources.fields['valn']['busDayCode'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'busDayCode']"));
		_resources.fields['valn']['holidayCode'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'holidayCode']"));
		_resources.fields['valn']['settleHolidayCode'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'settleHolidayCode']"));
		_resources.fields['valn']['additionalDayCode'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'additionalDayCode']"));
		_resources.fields['valn']['stlCurHldy'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'stlCurHldy']"));
		_resources.fields['valn']['freq'].loadData(
			IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqOn']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqType']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqDay']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqMonth']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqEndOf']")
		);
		_resources.fields['valn']['cutOffTimeZone'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'cutOfftimeZone']"));
		_resources.fields['divs']['freq'].loadData(
			IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqOn']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqType']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqDay']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqMonth']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqEndOf']")
		);
		_resources.fields['crys']['freq'].loadData(
			IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqOn']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqType']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqDay']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqMonth']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqEndOf']")
		);
		
		_resources.selectors['transType'].loadAvailableData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'dealTransType']"));

		_resources.popups['dealingUpd'].getField('dealingFreq').loadData(
			IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqOn']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqType']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqDay']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqMonth']")
			,IFDS.Xml.getNode(_initDataXML, "List[@listName = 'freqEndOf']")
		);
		
		_resources.fields['redemptionDealingFreq'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'RedDealFreqList']"));
	}
	
	function addChangeHandlers()
	{		
		for (var i in _resources.fields)
		{			
			if (i != 'valn' && i != 'divs' && i != 'crys')
			{
				addHandler(_resources.fields[i]);
			}							
		}

		for ( var i in _resources.fields['valn'])
		{ 	
			if (i != 'freq' && i != 'nsccOffSet')//nsccOffset must use separated listener
			{
				addHandler(_resources.fields['valn'][i]);
			} else if (i == 'freq'){
				_resources.fields['valn'][i].addFrequencyListener('select', function(){setChangeFlag()});
			}
		}
		
		for ( var i in _resources.fields['divs'])
		{
			if (i != 'freq')
			{
				addHandler(_resources.fields['divs'][i]);
			}else if (i == 'freq'){
				_resources.fields['divs'][i].addFrequencyListener('select', function(){setChangeFlag()});
			}
		}
		
		for ( var i in _resources.fields['crys'])
		{
			if (i != 'freq')
			{
				addHandler(_resources.fields['crys'][i]);
			}else if (i == 'freq'){
				_resources.fields['crys'][i].addFrequencyListener('select', function(){setChangeFlag()});
			}
		}
		
		_resources.fields['valn']['newFundGroup'].addListener('change', function(fld){
			_resources.fields['valn']['fundListTxt'].setValue(fld.getValue());
		});
		_resources.fields['divs']['newFundGroup'].addListener('change', function(fld){
			_resources.fields['divs']['fundListTxt'].setValue(fld.getValue());
		});

		// Time Change: 
		_resources.fields['valn']['cutOffFundGrp'].addListener('change', function(fld, newVal, oldVal){handleChangedTimeField(fld, newVal)});
		_resources.fields['valn']['cutOffClient'].addListener('change', function(fld, newVal, oldVal){handleChangedTimeField(fld, newVal)});
		_resources.fields['valn']['cutOffAggregate'].addListener('change', function(fld, newVal, oldVal){handleChangedTimeField(fld, newVal)});
		_resources.fields['valn']['cutOffMarket'].addListener('change', function(fld, newVal, oldVal){handleChangedTimeField(fld, newVal)});
		
		// Valuation Change
		_resources.fields['valn']['busDayCode'].addListener('select', function(){valuationChange()});
		_resources.fields['valn']['holidayCode'].addListener('select', function(){valuationChange()});
		_resources.fields['valn']['settleHolidayCode'].addListener('select', function(){valuationChange()});
		_resources.fields['valn']['additionalDayCode'].addListener('select', function(){valuationChange()});
		_resources.fields['valn']['stlCurHldy'].addListener('select', function(){valuationChange()});
		_resources.fields['valn']['freq'].addFrequencyListener('select', function(){valuationChange()});
		_resources.fields['valn']['cutOffFundGrp'].addListener('change', function(){valuationChange()});
		_resources.fields['valn']['cutOffClient'].addListener('change', function(){valuationChange()});
		_resources.fields['valn']['cutOffAggregate'].addListener('change', function(){valuationChange()});
		_resources.fields['valn']['cutOffMarket'].addListener('change', function(){valuationChange()});
		_resources.fields['valn']['cutOffTimeZone'].addListener('select', function(){valuationChange()});
		
		_resources.fields['divs']['freq'].addFrequencyListener('select', function(){dividendChange(true)});
		
		if (_perfFeeFlag)
		{
			// Require the validation if it's PF.
			_resources.fields['valn']['busDayCode'].addListener('select', function(){requireValuationValidation()});
			_resources.fields['valn']['holidayCode'].addListener('select', function(){requireValuationValidation()});
			_resources.fields['valn']['settleHolidayCode'].addListener('select', function(){requireValuationValidation()});
			_resources.fields['valn']['additionalDayCode'].addListener('select', function(){requireValuationValidation()});
			_resources.fields['valn']['stlCurHldy'].addListener('select', function(){requireValuationValidation()});
			_resources.fields['valn']['freq'].addFrequencyListener('select', function(){requireValuationValidation()});
			_resources.fields['valn']['cutOffFundGrp'].addListener('change', function(){requireValuationValidation()});
			_resources.fields['valn']['cutOffClient'].addListener('change', function(){requireValuationValidation()});
			_resources.fields['valn']['cutOffAggregate'].addListener('change', function(){requireValuationValidation()});
			_resources.fields['valn']['cutOffMarket'].addListener('change', function(){requireValuationValidation()});
			_resources.fields['valn']['cutOffTimeZone'].addListener('select', function(){requireValuationValidation()});
		}else{
			// Repopulate dividend frequency immediately if it's not PF.
			_resources.fields['valn']['freq'].addFrequencyListener('select', function(){repopulateValidFrequency('divs')});
		}
		
		function addHandler(fld)
		{
			if (fld instanceof Ext.form.Checkbox)
			{
				fld.addListener('check', function(){setChangeFlag()});
			}
			else if (fld instanceof DesktopWeb.Controls.ComboBox)
			{
				fld.addListener('select', function(){setChangeFlag()});
			}
			else
			{
				fld.addListener('change', function(){setChangeFlag()});
			}
		}
	}
	
	function populateScreen()	
	{
		_resources.tabs['scheduleTab'].add(_resources.panels['dividendSchedPanel']);

		if (_perfFeeFlag)
		{
			_resources.tabs['scheduleTab'].add(_resources.panels['crystalSchedPanel']);
			_resources.tabs['scheduleTab'].add(_resources.panels['dealingSchedPanel']);
			_resources.buttons['validateBtn'].show();
		}
		_resources.tabs['scheduleTab'].setActiveTab(0);
		
		var EventFreqNode = IFDS.Xml.getNode(_updatedClassDataXML, 'EventFreqConfig');
		
		if (IFDS.Xml.getNodeValue(EventFreqNode, 'ValnSched/fundGroup') == '')
		{
			initScreen();
		}else{
			loadDataSchedule();
		}

		if (IFDS.Xml.getNodeValue(EventFreqNode, 'redDealFreq') != null) {
			_resources.fields['redemptionDealingFreq'].setValue(IFDS.Xml.getNodeValue(EventFreqNode, 'redDealFreq'));
		}
	}  
	
	function initScreen()
	{
		/****************************************************************************************************
		 * Initial the event schedule screen to ready for entering new data
		 *	- Clear/Reset/Disable all components of Valuation Schedule panel excepts fund code group
		 *	- Clear/Reset/Disable all components of Dividend Schedule panel
		 *	- if it is PF fund class
		 *		- Clear/Reset/Disable all components of Crystalisation Schedule panel
		 *		- Clear/Reset/Disable all components of Dealing Schedule panel
		 ****************************************************************************************************/
		initValuationSchedulePanel();
		initDividendSchedulePanel();
		if (_perfFeeFlag)
		{
			initCrystalisationSchedulePanel();
			initDealingSchedulePanel();
		}
	}
	
	function loadDataSchedule()
	{
		var EventFreqNode = IFDS.Xml.getNode(_updatedClassDataXML, 'EventFreqConfig');
		loadValuationSchedulePanel(IFDS.Xml.getNode(EventFreqNode, 'ValnSched'), 
									(IFDS.Xml.getNodeValue(EventFreqNode, 'ValnSched/runMode') == _self.ADD));
		
		if (IFDS.Xml.getNodeValue(EventFreqNode, 'DivSched/fundGroup') == '')
		{
			enableDividendCheck();
			clearDividendCheck();
			resetDividendSchedulePanel();
			disableDividendSchedulePanel();
		}else{
			enableDividendCheck();
			checkDividendCheck();
			resetDividendSchedulePanel();
			enableDividendSchedulePanel();
			loadDividendSchedulePanel(IFDS.Xml.getNode(EventFreqNode, 'DivSched'), 
									(IFDS.Xml.getNodeValue(EventFreqNode, 'DivSched/runMode') == _self.ADD));
		}
		
		if (_perfFeeFlag)
		{
			var crysNode = initCrystalisationScheduleNode(EventFreqNode);
			loadCrystalisationSchedulePanel(crysNode);
			
			loadDealingSchedulePanel(IFDS.Xml.getNode(EventFreqNode, 'DealSched/DealSchedDetls'));
		}
		reenableFrequency('all');
	}
	
	function initValuationSchedulePanel()
	{
		readyValuationSchedulePanel();
	}
	
	function readyValuationSchedulePanel()
	{
		resetValuationSchedulePanel();
		var valnObj = _resources.fields['valn'];
		Ext.getCmp("valnSchedForm").disable();
		valnObj['newFundGroup'].disableField();
		valnObj['fundListCb'].disableField();
		valnObj['fundGroupDesc'].disableField();
		valnObj['busDayCode'].disableField();
		valnObj['holidayCode'].disableField();
		valnObj['settleHolidayCode'].disableField();
		valnObj['stlCurHldy'].disableField();
		valnObj['additionalDayCode'].disableField();
		valnObj['cutOffFundGrp'].disableField();
		valnObj['cutOffClient'].disableField();
		valnObj['cutOffAggregate'].disableField();
		valnObj['cutOffMarket'].disableField();
		valnObj['cutOffTimeZone'].disableField();
		valnObj['nsccOffSet'].disableField();
		valnObj['freq'].disableAllFrequencies();
		_resources.buttons['fundListBtn'].disable();
		
		if (_perfFeeFlag)
		{
			_resources.buttons['validateBtn'].disable();
		}
	}
	
	function resetValuationSchedulePanel()
	{
		var valnObj = _resources.fields['valn'];
		valnObj['fundGroup'].reset();
		
		valnObj['newFundGroup'].reset();
		valnObj['fundListTxt'].reset();
		_resources.forms['valnNewFundGroupForm'].hide();

		valnObj['fundListCb'].reset();
		valnObj['fundListCb'].getStore().removeAll();
		_resources.forms['valnFundGroupForm'].show();
		
		valnObj['fundGroupDesc'].reset();
		valnObj['busDayCode'].reset();
		valnObj['holidayCode'].reset();
		valnObj['settleHolidayCode'].reset();
		valnObj['stlCurHldy'].reset();
		valnObj['additionalDayCode'].reset();
		valnObj['freq'].clearFrequency();

		valnObj['cutOffFundGrp'].reset();
		valnObj['cutOffClient'].reset();
		valnObj['cutOffAggregate'].reset();
		valnObj['cutOffMarket'].reset();
		valnObj['cutOffTimeZone'].reset();
		valnObj['nsccOffSet'].reset();
	}
	
	function enableValuationSchedulePanel(newFundGroup)
	{
		var valnObj = _resources.fields['valn'];
		Ext.getCmp("valnSchedForm").enable();
		valnObj['newFundGroup'].enableField();
		valnObj['fundListCb'].enableField();
		
		if (newFundGroup)
		{
			_resources.forms['valnFundGroupForm'].hide();
			_resources.forms['valnNewFundGroupForm'].show();
			valnObj['fundGroupDesc'].enableField();
			_resources.buttons['fundListBtn'].disable();
		}else{
			_resources.forms['valnNewFundGroupForm'].hide();
			_resources.forms['valnFundGroupForm'].show();
			valnObj['fundGroupDesc'].disableField();
			_resources.buttons['fundListBtn'].enable();
		}
		
		valnObj['busDayCode'].enableField();
		valnObj['holidayCode'].enableField();
		valnObj['settleHolidayCode'].enableField();
		valnObj['stlCurHldy'].enableField();
		valnObj['additionalDayCode'].enableField();
		valnObj['cutOffFundGrp'].enableField();
		valnObj['cutOffClient'].enableField();
		valnObj['cutOffAggregate'].enableField();
		valnObj['cutOffMarket'].enableField();
		valnObj['cutOffTimeZone'].enableField();
		valnObj['nsccOffSet'].enableField();
		valnObj['freq'].enableAllFrequencies();
		
		if (_perfFeeFlag)
		{
			_resources.buttons['validateBtn'].enable();
		}
	}
	
	function loadValuationSchedulePanel(valnSchedNode, newFundGroup)
	{
		enableValuationSchedulePanel(newFundGroup);
		loadXMLToValuationFields(valnSchedNode);
		var valnObj = _resources.fields['valn'];
		var action = IFDS.Xml.getNodeValue(valnSchedNode, 'runMode');
		if(newFundGroup || action == _self.ADD){
			valnObj['fundGroup'].action = _self.ADD;
			setInitialFieldValue(valnObj['newFundGroup'], IFDS.Xml.getNodeValue(valnSchedNode, 'fundGroup'));
			setInitialFieldValue(valnObj['fundGroup'], _translationMap['AddNewFundGrp']);
			setInitialFieldValue(valnObj['fundListTxt'], IFDS.Xml.getNodeValue(valnSchedNode, 'fundList'));
		}else{
			valnObj['fundGroup'].action = _self.MOD;
			setInitialFieldValue(valnObj['fundGroup'], IFDS.Xml.getNodeValue(valnSchedNode, 'fundGroup'));
			loadValnFundList(IFDS.Xml.getNodeValue(valnSchedNode, 'fundGroup'));
			setInitialFieldValue(valnObj['fundListCb'], IFDS.Xml.getNodeValue(valnSchedNode, 'fundList'));
		}

		function loadValnFundList(fundGroup)
		{
			var fundList = IFDS.Xml.getNodeValue(_initDataXML, 'ValnFundGroupList/ValnFundGroup[fundGroup="' + fundGroup + '"]/fundLists');
			var fundListItems = fundList.split(',');
			var store = _resources.fields['valn']['fundListCb'].getStore();
			var fundListArray = [];
			Ext.each(fundListItems, function(fundListItem){
				if (fundListItem.substring(0, 1) != '!')
				{
					var data = [fundListItem, fundListItem];
					fundListArray.push(data);
				}
			});
			_resources.fields['valn']['fundListCb'].loadData(fundListArray);
			_resources.fields['valn']['fundListCb'].setValue(fundListItems[0]);
		}

		function loadXMLToValuationFields(xml)
		{
			var flds = _resources.fields['valn'];
			xml = (xml)?xml:valnSchedNode;
			for (var i in flds)
			{			
				if (i != 'freq' && i != 'fundGroup' && i != 'newFundGroup')
				{
					if (i != 'cutOffFundGrp' && i != 'cutOffClient' && i != 'cutOffMarket' && i != 'cutOffAggregate')
					{
						setInitialFieldValue(flds[i], IFDS.Xml.getNodeValue(xml, i));
					}else{
						setInitialFieldValue(flds[i], stringToTime(IFDS.Xml.getNodeValue(xml, i)));
					}
				}else if (i == 'freq'){
					flds[i].setFrequency(
						IFDS.Xml.getNodeValue(xml, 'ValnSchedFreq/freqOn')
						,IFDS.Xml.getNodeValue(xml, 'ValnSchedFreq/freqType')
						,IFDS.Xml.getNodeValue(xml, 'ValnSchedFreq/freqDay')
						,IFDS.Xml.getNodeValue(xml, 'ValnSchedFreq/freqMonth')
						,IFDS.Xml.getNodeValue(xml, 'ValnSchedFreq/freqEndOf')
					);
				}
			}
		}
		
		function stringToTime(val)
		{
			if(val && val.length == 4)
			{
				return val.substring(0,2) + ':' + val.substring(2);
			}
			return '';
		}
	}
	
	function initDividendSchedulePanel()
	{
		clearDividendCheck();
		disableDividendCheck();
		resetDividendSchedulePanel();
		disableDividendSchedulePanel();
	}
	
	function resetDividendSchedulePanel()
	{
		_resources.panels['dividendSchedPanel'].resetPanel();
	}
	
	function enableDividendSchedulePanel(state)
	{
		var divsObj = _resources.fields['divs'];
		_resources.panels['dividendSchedPanel'].enablePanel();
		if (state == 'new')
		{
			_resources.forms['divsFundGroupForm'].hide();
			_resources.forms['divsNewFundGroupForm'].show();
			divsObj['fundGroupDesc'].enableField();
			_resources.buttons['fundList2Btn'].disable();
		}else if (state == 'existing'){
			_resources.forms['divsNewFundGroupForm'].hide();
			_resources.forms['divsFundGroupForm'].show();
			divsObj['fundGroupDesc'].disableField();
			_resources.buttons['fundList2Btn'].enable();
		}
	}
	
	function clearInvalidDividendSchedulePanel()
	{
		_resources.panels['dividendSchedPanel'].clearInvalid();
	}
	
	function disableDividendSchedulePanel()
	{
		_resources.panels['dividendSchedPanel'].disablePanel();
	}
	
	function readyDividendSchedulePanel()
	{
		_resources.panels['dividendSchedPanel'].readyPanel();
	}
	
	function loadDividendSchedulePanel(divsSchedNode, newFundGroup)
	{
		enableDividendSchedulePanel(newFundGroup?'new':'existing');
		var divsObj = _resources.fields['divs'];
		var action = IFDS.Xml.getNodeValue(divsSchedNode, 'runMode');
		if(newFundGroup || action == _self.ADD){
			divsObj['fundGroup'].action = _self.ADD;
			setInitialFieldValue(divsObj['newFundGroup'], IFDS.Xml.getNodeValue(divsSchedNode, 'fundGroup'));
			setInitialFieldValue(divsObj['fundGroup'], _translationMap['AddNewFundGrp']);
			setInitialFieldValue(divsObj['fundListTxt'], IFDS.Xml.getNodeValue(divsSchedNode, 'fundList'));
		}else{
			divsObj['fundGroup'].action = _self.MOD;
			setInitialFieldValue(divsObj['fundGroup'], IFDS.Xml.getNodeValue(divsSchedNode, 'fundGroup'));
			loadDivsFundList(IFDS.Xml.getNodeValue(divsSchedNode, 'fundGroup'));
			setInitialFieldValue(divsObj['fundListCb'], IFDS.Xml.getNodeValue(divsSchedNode, 'fundList'));
		}
		
		setInitialFieldValue(divsObj['fundGroupDesc'], IFDS.Xml.getNodeValue(divsSchedNode, 'fundGroupDesc'));
		if (newFundGroup)
		{
			populateFrequencyByValuationFrequency(_resources.fields['divs']['freq']);
		}else{
			divsObj['freq'].setFrequency(
				IFDS.Xml.getNodeValue(divsSchedNode, 'DivSchedFreq/freqOn')
				,IFDS.Xml.getNodeValue(divsSchedNode, 'DivSchedFreq/freqType')
				,IFDS.Xml.getNodeValue(divsSchedNode, 'DivSchedFreq/freqDay')
				,IFDS.Xml.getNodeValue(divsSchedNode, 'DivSchedFreq/freqMonth')
				,IFDS.Xml.getNodeValue(divsSchedNode, 'DivSchedFreq/freqEndOf')
			);
		}
		
		repopulateValidFrequency('divs');

		function loadDivsFundList(fundGroup)
		{
			var fundList = IFDS.Xml.getNodeValue(_initDataXML, 'DivsFundGroupList/DivsFundGroup[fundGroup="' + fundGroup + '"]/fundLists');
			var fundListItems = fundList.split(',');
			var store = _resources.fields['divs']['fundListCb'].getStore();
			var fundListArray = [];
			Ext.each(fundListItems, function(fundListItem){
				if (fundListItem.substring(0, 1) != '!')
				{
					var data = [fundListItem, fundListItem];
					fundListArray.push(data);
				}
			});
			_resources.fields['divs']['fundListCb'].loadData(fundListArray);
			_resources.fields['divs']['fundListCb'].setValue(fundListItems[0]);
		}

	}
	
	function checkDividendCheck()
	{
		_resources.fields['divs']['dividendSchedCheck'].setValue(true);
	}
	
	function clearDividendCheck()
	{
		_resources.fields['divs']['dividendSchedCheck'].setValue(false);
	}
	
	function enableDividendCheck()
	{
		_resources.fields['divs']['dividendSchedCheck'].enableField();
	}
	
	function disableDividendCheck()
	{
		_resources.fields['divs']['dividendSchedCheck'].disableField();
	}
	
	function isCheckedDividendCheck()
	{
		return _resources.fields['divs']['dividendSchedCheck'].getValue();
	}
	
	function initCrystalisationSchedulePanel()
	{
		resetCrystalisationSchedulePanel();
		disableCrystalisationSchedulePanel();
	}
	
	function loadCrystalisationSchedulePanel(crysSchedNode)
	{
		resetCrystalisationSchedulePanel();
		enableCrystalisationSchedulePanel();
		_resources.fields['crys']['freq'].setFrequency(
			IFDS.Xml.getNodeValue(crysSchedNode, 'CrysSchedFreq/freqOn')
			,IFDS.Xml.getNodeValue(crysSchedNode, 'CrysSchedFreq/freqType')
			,IFDS.Xml.getNodeValue(crysSchedNode, 'CrysSchedFreq/freqDay')
			,IFDS.Xml.getNodeValue(crysSchedNode, 'CrysSchedFreq/freqMonth')
			,IFDS.Xml.getNodeValue(crysSchedNode, 'CrysSchedFreq/freqEndOf')
		);
	}
	
	function initCrystalisationScheduleNode(EventFreqNode)
	{
		var crysNode = IFDS.Xml.getNode(EventFreqNode, 'CrysSched');
		if (!crysNode) crysNode = IFDS.Xml.addSingleNode(EventFreqNode, 'CrysSched');
		var freqNode = IFDS.Xml.getNode(crysNode, 'CrysSchedFreq');
		if (!freqNode) freqNode = IFDS.Xml.addSingleNode(crysNode, 'CrysSchedFreq');
		var freqOnNode = IFDS.Xml.getNode(freqNode, 'freqOn');
		if (!freqOnNode) freqOnNode = IFDS.Xml.addSingleNode(freqNode, 'freqOn', IFDS.Xml.getNodeValue(EventFreqNode, 'ValnSched/ValnSchedFreq/freqOn'));
		var freqTypeNode = IFDS.Xml.getNode(freqNode, 'freqType');
		if (!freqTypeNode) freqTypeNode = IFDS.Xml.addSingleNode(freqNode, 'freqType', IFDS.Xml.getNodeValue(EventFreqNode, 'ValnSched/ValnSchedFreq/freqType'));
		var freqDayNode = IFDS.Xml.getNode(freqNode, 'freqDay');
		if (!freqDayNode) freqDayNode = IFDS.Xml.addSingleNode(freqNode, 'freqDay', IFDS.Xml.getNodeValue(EventFreqNode, 'ValnSched/ValnSchedFreq/freqDay'));
		var freqMonthNode = IFDS.Xml.getNode(freqNode, 'freqMonth');
		if (!freqMonthNode) freqMonthNode = IFDS.Xml.addSingleNode(freqNode, 'freqMonth', IFDS.Xml.getNodeValue(EventFreqNode, 'ValnSched/ValnSchedFreq/freqMonth'));
		var freqEndOfNode = IFDS.Xml.getNode(freqNode, 'freqEndOf');
		if (!freqEndOfNode) freqEndOfNode = IFDS.Xml.addSingleNode(freqNode, 'freqEndOf', IFDS.Xml.getNodeValue(EventFreqNode, 'ValnSched/ValnSchedFreq/freqEndOf'));
		return crysNode;
	}
	
	function resetCrystalisationSchedulePanel()
	{
		_resources.panels['crystalSchedPanel'].resetPanel();
	}
	
	function disableCrystalisationSchedulePanel()
	{
		_resources.panels['crystalSchedPanel'].disablePanel();
	}
	
	function enableCrystalisationSchedulePanel()
	{
		_resources.panels['crystalSchedPanel'].enablePanel();
	}
	
	function initDealingSchedulePanel()
	{
		resetDealingSchedulePanel();
		disableDealingSchedulePanel();
	}
	
	function loadDealingSchedulePanel(dealingSchedNode)
	{
		if(dealingSchedNode)
		{
			_resources.grids['dealingSched'].getStore().loadData(dealingSchedNode);
			updateDealingSchedButtons();
		}
	}

	function updateDealingSchedButtons()
	{
		var grid = _resources.grids['dealingSched'];
		grid.enableButton('addBtn');
		if(grid.getSelectedRecord())
		{
			grid.enableButton('delBtn');
			grid.enableButton('modBtn');
		}else{
			grid.disableButton('modBtn');
			grid.disableButton('delBtn');
		}
	}
	
	function resetDealingSchedulePanel()
	{
		_resources.panels['dealingSchedPanel'].resetPanel();
	}
	
	function enableDealingSchedulePanel()
	{
		_resources.panels['dealingSchedPanel'].enablePanel();
	}
	
	function disableDealingSchedulePanel()
	{
		_resources.panels['dealingSchedPanel'].disablePanel();
	}
	
	function addAddNewFundGroupItem(fld, type)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		var fundGrpXML = IFDS.Xml.addSingleNode(dataXML, (type=='valn')?'ValnFundGroup':'DivsFundGroup');
		IFDS.Xml.addSingleNode(fundGrpXML, 'fundGroup', _translationMap['AddNewFundGrp']);
		IFDS.Xml.addSingleNode(fundGrpXML, 'fundGroupDesc', '');
		IFDS.Xml.addSingleNode(fundGrpXML, 'fundLists', '');
		IFDS.Xml.addSingleNode(fundGrpXML, 'action', 'a'); //Add a new fund group action
		fld.getStore().loadData(dataXML, true);
	}

	function valuationChange() {
		if ( (_resources.fields['valn']['fundGroup'].getValue() != '' 
				&& _resources.fields['valn']['fundGroup'].action != _self.ADD)) {
			if (!_valnNotiFlag) {
				_valnNotiFlag = true;
				DesktopWeb.Util.displayWarning(_translationMap['ModifyValuationWarning']);
			}
		}
	}
	
	function requireValuationValidation()
	{
		_valnValidateFlag = false;
		disableDividendCheck();
		clearInvalidDividendSchedulePanel();
		disableDividendSchedulePanel();
		disableCrystalisationSchedulePanel();
		disableDealingSchedulePanel();
	}
	
	function updateScheduleTabs(validValn, validFreq, newDividendFundGroup)
	{
		if (_perfFeeFlag)
		{
			if (validFreq)
			{
				enableDividendCheck();
				enableDividendSchedulePanel();
				enableCrystalisationSchedulePanel();
				enableDealingSchedulePanel();
			}else{
				disableDividendCheck();
				disableDividendSchedulePanel();
				disableCrystalisationSchedulePanel();
				disableDealingSchedulePanel();
			}
		}else{
			if (validValn)
			{
				enableDividendCheck();
				if (isCheckedDividendCheck())
				{
					if (_resources.fields['divs']['fundGroup'].getValue() == '')
					{
						readyDividendSchedulePanel();
					}else{
						enableDividendSchedulePanel();
					}
				}else{
					disableDividendSchedulePanel();
				}
			}else{
				disableDividendCheck();
				disableDividendSchedulePanel();			
			}
		}
	}
	
	function dividendChange()
	{
		if (_resources.fields['divs']['fundGroup'].action != _self.ADD)
		{
			if (!_divNotiFlag)
			{
				_divNotiFlag = true;
				DesktopWeb.Util.displayWarning(_translationMap['ModifyDividendWarning']);
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
		_valnNotiFlag = false;
		_divNotiFlag = false;
		Ext.getCmp('resetBtn').disable();
		Ext.getCmp('saveBtn').disable();
	}
	
	function validateScreen()
	{
		var isValid = true;
		if(_perfFeeFlag && !_valnValidateFlag)
		{
			isValid = false;
			DesktopWeb.Util.displayError(_translationMap['RequiredValidateValuation']);
		}
		
		if (isValid)
		{
			isValid = validateValuationSchedule() && isValid;
			isValid = validateDividendSchedule() && isValid;

			if(isValid && _perfFeeFlag)
			{
				isValid = validateCrystalisationSchedule() && isValid;
				isValid = validateDealingSchedule() && isValid;
			}
			
			if (isValid)
			{
				isValid  = validateAllFrequencies();
			}
		}
		return isValid
	}
	
	function validateValuationSchedule()
	{
		var isValid = true;
		var valnObj = _resources.fields['valn'];
		if (!valnObj['fundGroup'].isValid()) return false;
		if (valnObj['fundGroup'].action != _self.ADD)
		{
			isValid = validateRequiredField(valnObj['fundGroup']) && isValid;
			isValid = validateRequiredField(valnObj['fundListCb']) && isValid;
		} else {
			isValid = valnObj['newFundGroup'].isValid() && validateRequiredField(valnObj['newFundGroup']) && isValid;
			isValid = valnObj['fundListTxt'].isValid() && validateRequiredField(valnObj['fundListTxt']) && isValid;
		}
		isValid = valnObj['fundGroupDesc'].isValid() && validateRequiredField(valnObj['fundGroupDesc']) && isValid;
		isValid = validateRequiredField(valnObj['busDayCode']) && isValid;
		isValid = validateRequiredField(valnObj['holidayCode']) && isValid;
		isValid = validateRequiredField(valnObj['stlCurHldy']) && isValid;
		isValid = valnObj['cutOffFundGrp'].isValid() && validateRequiredField(valnObj['cutOffFundGrp']) && isValid;
		isValid = valnObj['cutOffClient'].isValid() && validateRequiredField(valnObj['cutOffClient']) && isValid;
		isValid = valnObj['cutOffAggregate'].isValid() && validateRequiredField(valnObj['cutOffAggregate']) && isValid;
		isValid = valnObj['cutOffMarket'].isValid() && validateRequiredField(valnObj['cutOffMarket']) && isValid;
		isValid = validateRequiredField(valnObj['cutOffTimeZone']) && isValid;
		isValid = validateRequiredField(valnObj['freq'].getFrequencyOn()) && isValid;
		isValid = validateRequiredField(valnObj['freq'].getFrequencyType()) && isValid;
		isValid = validateRequiredField(valnObj['freq'].getFrequencyDay()) && isValid;
		isValid = validateRequiredField(valnObj['freq'].getFrequencyMonth()) && isValid;
		
		return isValid;
	}
	
	function validateDividendSchedule()
	{
		var isValid = true;
		var divObj = _resources.fields['divs'];
		if (divObj['dividendSchedCheck'].getValue())
		{
			if (divObj['fundGroup'].action != _self.ADD)
			{
				isValid = validateRequiredField(divObj['fundGroup']) && isValid;
				isValid = validateRequiredField(divObj['fundListCb']) && isValid;
			} else {
				isValid = divObj['newFundGroup'].isValid() && validateRequiredField(divObj['newFundGroup']) && isValid;
				isValid = divObj['fundListTxt'].isValid() && validateRequiredField(divObj['fundListTxt']) && isValid;
			}
			if (divObj['fundGroup'].getValue() != '')
			{
				isValid = divObj['fundGroupDesc'].isValid() && validateRequiredField(divObj['fundGroupDesc']) && isValid;
				isValid = validateRequiredField(divObj['freq'].getFrequencyOn()) && isValid;
				isValid = validateRequiredField(divObj['freq'].getFrequencyType()) && isValid;
				isValid = validateRequiredField(divObj['freq'].getFrequencyDay()) && isValid;
				isValid = validateRequiredField(divObj['freq'].getFrequencyMonth()) && isValid;
			}
		}
		return isValid;
	}
	
	function validateCrystalisationSchedule()
	{
		var isValid = true;
		var cryObj = _resources.fields['crys'];
		isValid = validateRequiredField(cryObj['freq'].getFrequencyOn()) && isValid;
		isValid = validateRequiredField(cryObj['freq'].getFrequencyType()) && isValid;
		isValid = validateRequiredField(cryObj['freq'].getFrequencyDay()) && isValid;
		isValid = validateRequiredField(cryObj['freq'].getFrequencyMonth()) && isValid;
		return isValid;
	}
	
	function validateDealingSchedule()
	{
		var isValid = true;
		var dealingSchedGrid = _resources.grids['dealingSched'];
		var records = dealingSchedGrid.getStore().queryBy(
			function(record){
				return (record.get('runMode') != _self.DEL)?record:null;
			}
		);
		
		if(records.length > 0)
		{
			var transTypesInGrid = '';
			for(i = 0; i < records.length; i++)
			{
				transTypesInGrid += ',' + records.itemAt(i).get('transType');
			}
			transTypesInGrid = transTypesInGrid.substring(1);
			var transTypeListInGrid = transTypesInGrid.split(',');
			
			var transTypesInList = '';
			var transTypeNodes = IFDS.Xml.getNodes(_initDataXML, "//List[@listName='dealTransType']/Element/code");
			Ext.each(transTypeNodes, function(transTypeNode){
				transTypesInList += ',' + IFDS.Xml.getNodeValue(transTypeNode, '.');
			});
			transTypesInList = transTypesInList.substring(1);
			var transTypeListInList = transTypesInList.split(',');
			
			if(transTypeListInGrid.length < transTypeListInList.length){
				DesktopWeb.Util.displayError(_translationMap['RequiredAllTransTypes']);
				isValid = false;
			}
			
		}else{
			DesktopWeb.Util.displayError(_translationMap['RequiredDealingSchedule']);
			isValid = false;
		}
		return isValid;
	}
	
	function validateAllFrequencies()
	{
		var isValid = true;
		var weekDayList = ",02,03,04,05,06,07,08,";
		var validTypeList = ",01,02,03,04,05,06,";
		var valnFreq = _resources.fields['valn']['freq'].getFrequency();
		var divFreq = _resources.fields['divs']['freq'].getFrequency();
		var cryFreq = _resources.fields['crys']['freq'].getFrequency();

		if (_resources.fields['divs']['dividendSchedCheck'].getValue())
		{
			if ( !(valnFreq['type'] == '01' && valnFreq['day'] == '01') )
			{
				var freqValid = true;
				if (valnFreq['on'] != divFreq['on'])
				{
					_resources.fields['divs']['freq'].getFrequencyOn().markInvalid(
						geSubstituteTranslation(_translationMap['OnlyValid'], 
						getValueDescFromList('freqOn', valnFreq['on'])));
					freqValid = false;
				}
				
				if ( valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1 )
				{
					if (validTypeList.indexOf(divFreq['type']) == -1)
					{
						_resources.fields['divs']['freq'].getFrequencyType().markInvalid(
							geSubstituteTranslation(_translationMap['OnlyValid'], 
							getValueDescFromList('freqType', valnFreq['type'])));
						freqValid = false;
					}
				}else{
					if (valnFreq['type'] != divFreq['type'])
					{
						_resources.fields['divs']['freq'].getFrequencyType().markInvalid(
							geSubstituteTranslation(_translationMap['OnlyValid'], 
							getValueDescFromList('freqType', valnFreq['type'])));
						freqValid = false;
					}
				}
				
				if (valnFreq['day'] != divFreq['day'])
				{
					_resources.fields['divs']['freq'].getFrequencyDay().markInvalid(
						geSubstituteTranslation(_translationMap['OnlyValid'], 
						getValueDescFromList('freqDay', valnFreq['day'])));
					freqValid = false;
				}
				
				if (valnFreq['endOf'] != divFreq['endOf'])
				{
					_resources.fields['divs']['freq'].getFrequencyEndOf().markInvalid(
						geSubstituteTranslation(_translationMap['OnlyValid'], 
						getValueDescFromList('freqEndOf', valnFreq['endOf'])));
					freqValid = false;
				}
				if (!freqValid)
				{
					isValid = false;
					DesktopWeb.Util.displayError(_translationMap['DividendFrequencyNotMatch']);
				}
			}
		}

		if ( isValid && _perfFeeFlag )
		{
			if ( !(valnFreq['type'] == '01' && valnFreq['day'] == '01') )
			{
				if ( valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1 )
				{
					if (validTypeList.indexOf(cryFreq['type']) == -1)
					{
						isValid = false;
						_resources.fields['crys']['freq'].getFrequencyType().markInvalid(_translationMap['CrystalisationFrequencyNotMatch']);
						DesktopWeb.Util.displayError(_translationMap['CrystalisationFrequencyNotMatch']);
					}
				}
				
				if (isValid)
				{
					var dealingRecords = _resources.grids['dealingSched'].getStore().queryBy(
						function(record){
							return (record.get('runMode') != _self.DEL)?record:null;
						}
					);
					
					for (i = 0; i < dealingRecords.length; i++)
					{
						if ( valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1 )
						{
							if (validTypeList.indexOf(dealingRecords.itemAt(i).get('freqType')) == -1)
							{
								isValid = false;
								DesktopWeb.Util.displayError(_translationMap['DealingFrequencyNotMatch']);
								break;
							}
						}
					}
				}
			}
		}
		
		if (isValid)
		{
			/********************************************************************************************************************************* 
			 ***** Dividend, Crystalisation, and Dealing frequencies cannot be occurred more frequently than the valuation frequency set *****
			 *********************************************************************************************************************************/
			var errMsg = '';
			var validMonth = IFDS.Xml.getNodeValue(_initDataXML, "SchedSets/SchedSet[month='" + _resources.fields['valn']['freq'].getFrequencyMonth().getValue() + "']/validMonth");
			// Dividend
			if (validMonth.indexOf(_resources.fields['divs']['freq'].getFrequencyMonth().getValue()) < 0)
			{
				isValid = false;
				_resources.fields['divs']['freq'].getFrequencyMonth().markInvalid(_translationMap['DivFreqMoreThanValnFreq']);
				errMsg += _translationMap['DivFreqMoreThanValnFreq'];
			}
			
			if (_perfFeeFlag)
			{
				// Crystalisation
				if (validMonth.indexOf(_resources.fields['crys']['freq'].getFrequencyMonth().getValue()) < 0)
				{
					isValid = false;
					if (errMsg != '') errMsg += '<br/><br/>';
					errMsg += _translationMap['CryFreqMoreThanValnFreq'];
				}
				
				// Dealing
				var dealingRecords = _resources.grids['dealingSched'].getStore().queryBy(
					function(record){
						return (record.get('runMode') != _self.DEL)?record:null;
					}
				);

				for (i = 0; i < dealingRecords.length; i++)
				{
					if (validMonth.indexOf(dealingRecords.itemAt(i).get('freqMonth')) < 0)
					{
						isValid = false;
						if (errMsg != '') errMsg += '<br/><br/>';
						errMsg += _translationMap['DealFreqMoreThanValnFreq'];
					}
				}
				
				if (errMsg != '') DesktopWeb.Util.displayError(errMsg);
			}
		}
		
		return isValid;
		
		function geSubstituteTranslation(msg, values)
		{
			if (Ext.isArray(values))
			{
				for (i = 0; i < values.length; i++)
				{
					msg.replace('%' + (i+1) + '%', values[i]);
				}
				return msg;
			}else{
				return msg.replace('%1%', values);
			}
		}
	}
	
	function validateDealing(action)
	{
		var valid = true;
		if(action != _self.DEL)
		{
			if(_resources.selectors['transType'].getSelectedRecords().length <= 0){
				DesktopWeb.Util.displayError(_translationMap['RequiredAtLeastOne']);
				valid = false;
			}
		
			valid = validateRequiredField(_resources.popups['dealingUpd'].getField('dealingFreq').getFrequencyOn()) && valid;
		}
		return valid;
	}
	
	function validateRequiredField(f)
	{
		if (f.getValue().length <= 0)
		{
			f.markInvalid(_translationMap['requiredFieldErrMsg']);
			return false;
		}
		return true;
	}
	
	function updateXML()
	{
		var eventFreqXML = IFDS.Xml.getNode(_updatedClassDataXML, 'EventFreqConfig');

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
		
		var valnObj = _resources.fields['valn'];
		var valnNode = IFDS.Xml.getNode(eventFreqXML, 'ValnSched');
		if(!valnNode) valnNode = IFDS.Xml.addSingleNode(eventFreqXML, 'ValnSched');
		if(valnObj['fundGroup'].action == _self.ADD)
		{
			xmlWriteFn('runMode', _self.ADD, valnNode);
			xmlWriteFn('fundGroup', valnObj['newFundGroup'].getValue(), valnNode);
			xmlWriteFn('fundList', valnObj['fundListTxt'].getValue(), valnNode);
		}else{
			xmlWriteFn('runMode', _self.MOD, valnNode);
			xmlWriteFn('fundGroup', valnObj['fundGroup'].getValue(), valnNode);
			xmlWriteFn('fundList', valnObj['fundListCb'].getValue(), valnNode);
		}
		xmlWriteFn('processingMode', 'update', valnNode);
		xmlWriteFn('fundGroupDesc', valnObj['fundGroupDesc'].getValue(), valnNode);
		xmlWriteFn('busDayCode', valnObj['busDayCode'].getValue(), valnNode);
		xmlWriteFn('holidayCode', valnObj['holidayCode'].getValue(), valnNode);
		xmlWriteFn('settleHolidayCode', valnObj['settleHolidayCode'].getValue(), valnNode);
		xmlWriteFn('additionalDayCode', valnObj['additionalDayCode'].getValue(), valnNode);
		xmlWriteFn('stlCurHldy', valnObj['stlCurHldy'].getValue(), valnNode);
		xmlWriteFn('cutOffFundGrp', timeToString(valnObj['cutOffFundGrp'].getValue()), valnNode);
		xmlWriteFn('cutOffClient', timeToString(valnObj['cutOffClient'].getValue()), valnNode);
		xmlWriteFn('cutOffMarket', timeToString(valnObj['cutOffMarket'].getValue()), valnNode);
		xmlWriteFn('nsccOffSet', valnObj['nsccOffSet'].getValue(), valnNode);
		xmlWriteFn('cutOffAggregate', timeToString(valnObj['cutOffAggregate'].getValue()), valnNode);
		xmlWriteFn('cutOffTimeZone', valnObj['cutOffTimeZone'].getValue(), valnNode);

		xmlWriteFn('redDealFreq', _resources.fields['redemptionDealingFreq'].getValue());

		var valnFreqNode = IFDS.Xml.getNode(valnNode, 'ValnSchedFreq');
		if(!valnFreqNode) valnFreqNode = IFDS.Xml.addSingleNode(valnNode, 'ValnSchedFreq');
		writeFrequencyToXML(valnObj['freq'], valnFreqNode);
		
		// Dividend Schedule
		var divsObj = _resources.fields['divs'];
		if(divsObj['dividendSchedCheck'].getValue())
		{
			xmlWriteFn('divSchedFlag', 'yes', valnNode);
			var divNode = IFDS.Xml.getNode(eventFreqXML, 'DivSched');
			if(!divNode) divNode = IFDS.Xml.addSingleNode(eventFreqXML, 'DivSched');
			if(divsObj['fundGroup'].action == _self.ADD)
			{
				xmlWriteFn('runMode', _self.ADD, divNode);
				xmlWriteFn('fundGroup', divsObj['newFundGroup'].getValue(), divNode);
				xmlWriteFn('fundList', divsObj['fundListTxt'].getValue(), divNode);
			}else{
				xmlWriteFn('runMode', _self.MOD, divNode);
				xmlWriteFn('fundGroup', divsObj['fundGroup'].getValue(), divNode);
				xmlWriteFn('fundList', divsObj['fundListCb'].getValue(), divNode);
			}
			xmlWriteFn('fundGroupDesc', divsObj['fundGroupDesc'].getValue(), divNode);

			var divFreqNode = IFDS.Xml.getNode(divNode, 'DivSchedFreq');
			if(!divFreqNode) divFreqNode = IFDS.Xml.addSingleNode(divNode, 'DivSchedFreq');
			writeFrequencyToXML(divsObj['freq'], divFreqNode);
		}else{
			xmlWriteFn('divSchedFlag', 'no', valnNode);
			var divNode = IFDS.Xml.getNode(eventFreqXML, 'DivSched');
			if (divNode) IFDS.Xml.deleteNode(divNode);
		}
		
		if (_perfFeeFlag)
		{
			// PF Crystalisation Schedule
			var cryNode = IFDS.Xml.getNode(eventFreqXML, 'CrysSched');
			if (!cryNode) cryNode = IFDS.Xml.addSingleNode(eventFreqXML, 'CrysSched');
			var cryFreqNode = IFDS.Xml.getNode(cryNode, 'CrysSchedFreq');
			if (!cryFreqNode) cryFreqNode = IFDS.Xml.addSingleNode(cryNode, 'CrysSchedFreq');
			writeFrequencyToXML(_resources.fields['crys']['freq'], cryFreqNode);
			xmlWriteFn('runMode', (_addMode)?_self.ADD:_self.MOD, cryFreqNode);
			
			// Dealing Schedule
			var dealRecords = _resources.grids['dealingSched'].getAllRecords();
			var gridFlds = _resources.grids['dealingSched'].getStore().fields;
			var dealNode = IFDS.Xml.getNode(eventFreqXML, 'DealSched');
			if (!dealNode) dealNode = IFDS.Xml.addSingleNode(eventFreqXML, 'DealSched');
			var dealDetlsNode = IFDS.Xml.getNode(dealNode, 'DealSchedDetls');
			if (!dealDetlsNode) dealDetlsNode = IFDS.Xml.addSingleNode(dealNode, 'DealSchedDetls');
			Ext.each(dealRecords, function(dealRecord){
				var dealDetlNode = IFDS.Xml.getNode(dealDetlsNode, "DealSchedDetl[freqUUID='" + dealRecord.get('freqUUID') + "']");
				if (!dealDetlNode) dealDetlNode = IFDS.Xml.addSingleNode(dealDetlsNode, 'DealSchedDetl');
				for (i = 0; i < gridFlds.length; i++)
				{
					xmlWriteFn(gridFlds.itemAt(i).name, dealRecord.get(gridFlds.itemAt(i).name), dealDetlNode);
				}
			});
		}
		
		function timeToString(val)
		{
			if(val) return val.replace(':', '');
		}
		
		function writeFrequencyToXML(freqObj, context)
		{
			context = (context == null ? eventFreqXML : context);
			var freq = freqObj.getFrequency();
			xmlWriteFn('freqOn', freq['on'], context);
			xmlWriteFn('freqType', freq['type'], context);
			xmlWriteFn('freqDay', freq['day'], context);
			xmlWriteFn('freqMonth', freq['month'], context);
			xmlWriteFn('freqEndOf', freq['endOf'], context);
		}

		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? eventFreqXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if(!node)
			{
				node = IFDS.Xml.addSingleNode(context, fldName, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}else
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? eventFreqXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}		
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
	
	function setInitialFieldValue(fld, val)
	{
		fld.reset();
		if (val != "") 
		{		
			fld.setValue(val);
		}
		else
		{
			fld.reset();
		}	
	}

	function handleChangedTimeField(fld, val)
	{
		if (fld.isValid() && val.length > 0)
		{
			if (val.indexOf(':') > -1)
			{
				if (val.length == 4)
				{
					val = '0' + val;
				}
			}else{
				if (val.length == 3)
				{
					val = '0' + val;
				}
				String.prototype.splice = function( idx, rem, s ) { return (this.slice(0,idx) + s + this.slice(idx + Math.abs(rem))); }; 
				val = val.splice(2, 0, ':');
			}
			fld.setValue(val);
		}
	}

	function populateFrequencyByValuationFrequency(freqObj)
	{
		var valnFreq = _resources.fields['valn']['freq'].getFrequency();
		freqObj.setFrequency(
			valnFreq['on']
			,valnFreq['type']
			,valnFreq['day']
			,valnFreq['month']
			,valnFreq['endOf']
		);
	}
	
	function repopulateValidFrequency(freqList)
	{
		var valnFreq = _resources.fields['valn']['freq'].getFrequency();
		var validMonthList = IFDS.Xml.getNodeValue(_initDataXML, "SchedSets/SchedSet[month='" + valnFreq['month'] + "']/validMonth");
		var weekDayList = ",02,03,04,05,06,07,08,";
		var validTypeList = ",01,02,03,04,05,06,";
		freqList = (!freqList)?'all':freqList;
		
		if (freqList == 'all' || freqList == 'divs')
		{
			if (valnFreq['type'] == '01' && valnFreq['day'] == '01')
			{
				_resources.fields['divs']['freq'].getFrequencyOn().getStore().clearFilter(false);
				_resources.fields['divs']['freq'].getFrequencyType().getStore().clearFilter(false);
				_resources.fields['divs']['freq'].getFrequencyDay().getStore().clearFilter(false);
				
				_resources.fields['divs']['freq'].getFrequencyMonth().getStore().filterBy(function(record){
					return (validMonthList.indexOf(record.get('code')) != -1);
				});
				_resources.fields['divs']['freq'].getFrequencyEndOf().getStore().clearFilter(false);
			}else if (valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1) 
			{
				_resources.fields['divs']['freq'].getFrequencyOn().getStore().filter('code', valnFreq['on']);
				
				_resources.fields['divs']['freq'].getFrequencyType().getStore().filterBy(function(record){
					return (validTypeList.indexOf(record.get('code')) != -1);
				});
				_resources.fields['divs']['freq'].getFrequencyDay().getStore().filter('code', valnFreq['day']);
				
				_resources.fields['divs']['freq'].getFrequencyMonth().getStore().filterBy(function(record){
					return (validMonthList.indexOf(record.get('code')) != -1);
				});
				_resources.fields['divs']['freq'].getFrequencyEndOf().getStore().filter('code', valnFreq['endOf']);
			}else{
				_resources.fields['divs']['freq'].getFrequencyOn().getStore().filter('code', valnFreq['on']);
				_resources.fields['divs']['freq'].getFrequencyType().getStore().filter('code', valnFreq['type']);
				_resources.fields['divs']['freq'].getFrequencyDay().getStore().filter('code', valnFreq['day']);
				
				_resources.fields['divs']['freq'].getFrequencyMonth().getStore().filterBy(function(record){
					return (validMonthList.indexOf(record.get('code')) != -1);
				});
				_resources.fields['divs']['freq'].getFrequencyEndOf().getStore().filter('code', valnFreq['endOf']);
			}
		}
		
		if (_perfFeeFlag && (freqList == 'all' || freqList == 'crys'))
		{
			_resources.fields['crys']['freq'].disableFrequencies(false, false, false, false, false);
			_resources.fields['crys']['freq'].getFrequencyMonth().getStore().filterBy(function(record){
				return (validMonthList.indexOf(record.get('code')) != -1);
			});
			if (valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1)
			{
				_resources.fields['crys']['freq'].getFrequencyType().getStore().filterBy(function(record){
					return (validTypeList.indexOf(record.get('code')) != -1);
				});
			}else{
				_resources.fields['crys']['freq'].getFrequencyType().getStore().clearFilter(false);
			}
		}
		
		if (_perfFeeFlag && (freqList == 'all' || freqList == 'dealing'))
		{
			_resources.popups['dealingUpd'].getField('dealingFreq').getFrequencyMonth().getStore().filterBy(function(record){
				return (validMonthList.indexOf(record.get('code')) != -1);
			});
			if (valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1)
			{
				_resources.popups['dealingUpd'].getField('dealingFreq').getFrequencyType().getStore().filterBy(function(record){
					return (validTypeList.indexOf(record.get('code')) != -1);
				});
			}else{
				_resources.popups['dealingUpd'].getField('dealingFreq').getFrequencyType().getStore().clearFilter(false);
			}
		}
	}
	
	function reenableFrequency(freqList)
	{
		var valnFreq = _resources.fields['valn']['freq'].getFrequency();
		var weekDayList = ",02,03,04,05,06,07,08,";
		freqList = (!freqList)?'all':freqList;

		if (_perfFeeFlag && (freqList == 'all' || freqList == 'crys'))
		{
			if (valnFreq['type'] == '01' && valnFreq['day'] == '01')
			{
				_resources.fields['crys']['freq'].disableFrequencies(false, false, false, false, false);
			}else if (valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1){
				_resources.fields['crys']['freq'].disableFrequencies(true, false, true, false, true);
			}else{
				_resources.fields['crys']['freq'].disableFrequencies(true, true, true, false, true);
			}
		}

		if (_perfFeeFlag && (freqList == 'all' || freqList == 'dealing'))
		{
			if (valnFreq['type'] == '01' && valnFreq['day'] == '01')
			{
				_resources.popups['dealingUpd'].getField('dealingFreq').disableFrequencies(false, false, false, false, false);
			}else if (valnFreq['type'] == '01' && weekDayList.indexOf(valnFreq['day']) != -1){
				_resources.popups['dealingUpd'].getField('dealingFreq').disableFrequencies(true, false, true, false, true);
			}else{
				_resources.popups['dealingUpd'].getField('dealingFreq').disableFrequencies(true, true, true, false, true);
			}
		}
	}
	
	function updateDealingFrequencyByValuationFrequency()
	{
		var dealingSchedNodes = IFDS.Xml.getNodes(_updatedClassDataXML, 'EventFreqConfig/DealSched/DealSchedDetls/DealSchedDetl');
		var valnFreq = _resources.fields['valn']['freq'].getFrequency();
		Ext.each(dealingSchedNodes, function(dealingSchedNode){
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(dealingSchedNode, 'freqOn'), valnFreq['on']);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(dealingSchedNode, 'freqType'), valnFreq['type']);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(dealingSchedNode, 'freqDay'), valnFreq['day']);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(dealingSchedNode, 'freqEndOf'), valnFreq['endOf']);
			var runMode = IFDS.Xml.getNodeValue(dealingSchedNode, 'runMode');
			if (runMode && runMode.length == 0) IFDS.Xml.setNodeValue(IFDS.Xml.getNode(dealingSchedNode, 'runMode'), _self.MOD);
			if (!runMode) IFDS.Xml.addSingleNode(dealingSchedNode, 'runMode', _self.MOD);
		});
		loadDealingSchedulePanel(IFDS.Xml.getNode(_updatedClassDataXML, 'EventFreqConfig/DealSched/DealSchedDetls'));
	}
	
	function buildValnSchedXML()
	{
		var xml = IFDS.Xml.newDocument('data');
		var eventNode = IFDS.Xml.addSingleNode(xml, 'EventFreqConfig');
		var valnSchedNode = IFDS.Xml.addSingleNode(eventNode, 'ValnSched');
		var valnObj = _resources.fields['valn'];
		IFDS.Xml.addSingleNode(valnSchedNode, 'processingMode', 'validate');
		if(valnObj['fundGroup'].action == _self.ADD)
		{
			IFDS.Xml.addSingleNode(valnSchedNode, 'runMode', _self.ADD);
			IFDS.Xml.addSingleNode(valnSchedNode, 'fundGroup', valnObj['newFundGroup'].getValue());
		}else{
			IFDS.Xml.addSingleNode(valnSchedNode, 'runMode', _self.MOD, valnSchedNode);
			IFDS.Xml.addSingleNode(valnSchedNode, 'fundGroup', valnObj['fundGroup'].getValue());
		}
		IFDS.Xml.addSingleNode(valnSchedNode, 'fundGroupDesc', valnObj['fundGroupDesc'].getValue());
		IFDS.Xml.addSingleNode(valnSchedNode, 'busDayCode', valnObj['busDayCode'].getValue());
		IFDS.Xml.addSingleNode(valnSchedNode, 'holidayCode', valnObj['holidayCode'].getValue());
		IFDS.Xml.addSingleNode(valnSchedNode, 'settleHolidayCode', valnObj['settleHolidayCode'].getValue());
		IFDS.Xml.addSingleNode(valnSchedNode, 'stlCurHldy', valnObj['stlCurHldy'].getValue());
		IFDS.Xml.addSingleNode(valnSchedNode, 'additionalDayCode', valnObj['additionalDayCode'].getValue());
		IFDS.Xml.addSingleNode(valnSchedNode, 'cutOffFundGrp', valnObj['cutOffFundGrp'].getValue().replace(':', ''));
		IFDS.Xml.addSingleNode(valnSchedNode, 'cutOffClient', valnObj['cutOffClient'].getValue().replace(':', ''));
		IFDS.Xml.addSingleNode(valnSchedNode, 'cutOffMarket', valnObj['cutOffMarket'].getValue().replace(':', ''));
		IFDS.Xml.addSingleNode(valnSchedNode, 'cutOffAggregate', valnObj['cutOffAggregate'].getValue().replace(':', ''));
		IFDS.Xml.addSingleNode(valnSchedNode, 'cutOffTimeZone', valnObj['cutOffTimeZone'].getValue());
		IFDS.Xml.addSingleNode(valnSchedNode, 'nsccOffSet', valnObj['nsccOffSet'].getValue());
		
		var valnFreqNode = IFDS.Xml.addSingleNode(valnSchedNode, 'ValnSchedFreq');
		var freq = valnObj['freq'].getFrequency();
		IFDS.Xml.addSingleNode(valnFreqNode, 'freqOn', freq['on']);
		IFDS.Xml.addSingleNode(valnFreqNode, 'freqType', freq['type']);
		IFDS.Xml.addSingleNode(valnFreqNode, 'freqDay', freq['day']);
		IFDS.Xml.addSingleNode(valnFreqNode, 'freqMonth', freq['month']);
		IFDS.Xml.addSingleNode(valnFreqNode, 'freqEndOf', freq['endOf']);		
		
		// add header
		if (_addMode)
		{
			IFDS.Xml.addSingleNode(xml, 'processingMode', 'validate');
			IFDS.Xml.addSingleNode(xml, 'runMode', 'v');			
			IFDS.Xml.addSingleNode(xml, 'fundCode', IFDS.Xml.getNodeValue(_updatedClassDataXML, 'fundCode'));
			IFDS.Xml.addSingleNode(xml, 'classCode', IFDS.Xml.getNodeValue(_updatedClassDataXML, 'classCode'));
		}
		else
		{
			IFDS.Xml.addSingleNode(xml, 'processingMode', 'validate');
			IFDS.Xml.addSingleNode(xml, 'runMode', 'v');
			IFDS.Xml.addSingleNode(xml, 'fundCode', IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundCode'));
			IFDS.Xml.addSingleNode(xml, 'classCode', IFDS.Xml.getNodeValue(_existingClassDataXML, 'classCode'));
		}
		
		return xml;
	}

	function getValueDescFromList(listId, value)
	{
		var desc = IFDS.Xml.getNodeValue(_initDataXML, 'List[@id = "' + listId + '"]/Element[code = "' + value + '"]/value');
		// if @id didn't work, try @listName
		if (!desc)
		{
			desc = IFDS.Xml.getNodeValue(_initDataXML, 'List[@listName = "' + listId + '"]/Element[code = "' + value + '"]/value');
		}
		return desc;
	}
	
	function getActiveValuationFundGroupList()
	{
		var valnFundGroupListNode = IFDS.Xml.newDocument("data");
		var nodes = IFDS.Xml.getNodes(_initDataXML, 'ValnFundGroupList/ValnFundGroup[fundLists != ""]');
		for (var i = 0; i < nodes.length; i++)
		{
			IFDS.Xml.appendNode(valnFundGroupListNode, IFDS.Xml.cloneDocument(nodes[i]));
		}		
		return valnFundGroupListNode;
	}
	
	function getActiveDividendFundGroupList()
	{
		var valnFundGroupListNode = IFDS.Xml.newDocument("data");
		var nodes = IFDS.Xml.getNodes(_initDataXML, 'DivsFundGroupList/DivsFundGroup[fundLists != ""]');
		for (var i = 0; i < nodes.length; i++)
		{
			IFDS.Xml.appendNode(valnFundGroupListNode, IFDS.Xml.cloneDocument(nodes[i]));
		}		
		return valnFundGroupListNode;
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
					if (IFDS.Xml.getNode(_updatedClassDataXML, 'EventFreqConfig') == null)				
					{
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'EventFreqConfig')));				
					}
				}

				var feeNode = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration');
				if(!feeNode)feeNode = IFDS.Xml.getNode(_existingClassDataXML, 'FeeConfiguration');
				_perfFeeFlag = (IFDS.Xml.getNodeValue(feeNode, 'perfFeeFlag')=='yes');

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
		
		,getValueDescFromList: function(listId, val)
		{
			return getValueDescFromList(listId, val);
		}
		
		,selectFundGroup: function(record, sched)
		{
			var obj = _resources.fields[sched];

			if (sched == 'valn')
			{
				if (record.get('action') == this.ADD)
				{
					var valnSchedNode = IFDS.Xml.getNode(_initDataXML, 'DefaultValues/EventFreqConfig/ValnSched');
					resetValuationSchedulePanel();
					loadValuationSchedulePanel(valnSchedNode, true);
					obj['newFundGroup'].focus(false, true);
					updateScheduleTabs(true, false);
				}else{
					if (obj['fundGroup'].getValue() == '')
					{
						readyValuationSchedulePanel();
						obj['fundGroup'].action = '';
						updateScheduleTabs(false, false);
					}else{
						var fundGrpNode = IFDS.Xml.getNode(_initDataXML, "ValnFundGroupList/ValnFundGroup[fundGroup='" + record.get('fundGroup') + "']");
						resetValuationSchedulePanel();
						loadValuationSchedulePanel(fundGrpNode, false);
						updateScheduleTabs(true, false);
					}
				}
			}
			
			if (sched == 'divs')
			{
				if (record.get('action') == this.ADD)
				{
					var divsSchedNode = IFDS.Xml.getNode(_initDataXML, 'DefaultValues/EventFreqConfig/DivSched');
					resetDividendSchedulePanel();
					loadDividendSchedulePanel(divsSchedNode, true);
					obj['newFundGroup'].focus(false, true);
				}else{
					if (obj['fundGroup'].getValue() == '')
					{
						readyDividendSchedulePanel();
						obj['fundGroup'].action = '';
					}else{
						var divsSchedNode = IFDS.Xml.getNode(_initDataXML, "DivsFundGroupList/DivsFundGroup[fundGroup='" + record.get('fundGroup') + "']");
						resetDividendSchedulePanel();
						loadDividendSchedulePanel(divsSchedNode, false);
					}
				}
			}
		}
		,validateOffsetmins: function(nsccOffsetMins) {
			var intValue = parseInt(nsccOffsetMins);
			if (isNaN(intValue) || intValue < -1439 || intValue > 1439) {
				_resources.fields['valn']['nsccOffSet'].markInvalid(_translationMap['ValuationInvalidNSCCOffset']);
				_resources.fields['valn']['nsccOffSet'].isMarkInvalid = true;
				_changeFlag = false;
				Ext.getCmp('resetBtn').disable();
				Ext.getCmp('saveBtn').disable();
			} else {
				DesktopWeb.Util.displayWarning(_translationMap['ModifyValuationWarning']);
				setChangeFlag();
			}
		}
		
		,validateValuationFrequency: function()
		{
			DesktopWeb.Ajax.doSmartviewAjax(_valnSchedValidateService, null, buildValnSchedXML(), responseHandler, _translationMap['ProcMsg_Loading']);

			function responseHandler(success, responseXML)
			{	
				if (success)
				{
					_valnValidateFlag = true;
					enableDividendCheck();
					clearInvalidDividendSchedulePanel();
					if (isCheckedDividendCheck())
					{
						enableDividendSchedulePanel((_resources.fields['divs']['fundGroup'].action == 'a')?'new':'existing');
					}else{
						disableDividendSchedulePanel();
					}
					
					enableCrystalisationSchedulePanel();
					enableDealingSchedulePanel();
					repopulateValidFrequency('all');
					reenableFrequency('all');
					populateFrequencyByValuationFrequency(_resources.fields['crys']['freq']);
					updateDealingFrequencyByValuationFrequency();
					DesktopWeb.Util.displayInfo(_translationMap['PassedValidate']);
				}else{
					_valnValidateFlag = false;
					disableDividendCheck();
					disableDividendSchedulePanel();
					disableCrystalisationSchedulePanel();
					disableDealingSchedulePanel();
				}
			}
		}
		
		,checkDividend: function(checked)
		{
			if(checked)
			{
				readyDividendSchedulePanel();
			}else{
				resetDividendSchedulePanel();
				disableDividendSchedulePanel();
			}
		}
		
		,openActionPopup: function(popup, action)
		{
			popup.show();					
			popup.init(action);
			repopulateValidFrequency('dealing');
		}
		
		,openFundListPopup: function(schedType)
		{
			var popup = _resources.popups['fundClassList'];
			popup.show();
			popup.init(schedType);
			
			var xml = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(xml, 'infoType', 'All');
			IFDS.Xml.addSingleNode(xml, 'groupType', schedType);
			IFDS.Xml.addSingleNode(xml, 'fundGroup', _resources.fields[schedType]['fundGroup'].getValue());

			DesktopWeb.Ajax.doSmartviewAjax(_fundClassListService, null, xml, responseHandler, _translationMap['ProcMsg_Loading']);

			function responseHandler(success, responseXML)
			{	
				if (success)
				{
					_resources.grids['fundClassList'].getStore().loadData(IFDS.Xml.getNode(responseXML, '//FundDetls'));
				}else{
					alert('Error occurs while retrieve fund class information.');
				}
			}
		}

		,saveDealingFrequency: function(popup, data)
		{
			if(validateDealing(popup.action))
			{
				var dealingSchedGrid = _resources.grids['dealingSched'];
				switch (popup.action)
				{
					case this.ADD:
					case this.MOD:
						var existingRecords = dealingSchedGrid.getStore().queryBy(
							function(record){
								return (record.get('runMode') != _self.DEL && record.get('freqUUID') != popup.dealingSchedUUID)?record:null;
							}
						);
						
						var updatedExisting = false;
						for(i = 0; i < existingRecords.length; i++)
						{
							if(data['freqOn'] == existingRecords.itemAt(i).get('freqOn')
								&& data['freqType'] == existingRecords.itemAt(i).get('freqType')
								&& data['freqDay'] == existingRecords.itemAt(i).get('freqDay')
								&& data['freqMonth'] == existingRecords.itemAt(i).get('freqMonth')
								&& data['freqEndOf'] == existingRecords.itemAt(i).get('freqEndOf'))
							{
								existingRecords.itemAt(i).set('transType', existingRecords.itemAt(i).get('transType') + ',' + data['transType']);
								dealingSchedGrid.getStore().commitChanges();
								updatedExisting = true;
								break;
							}
						}
						if(!updatedExisting)
						{
							if(popup.action == this.ADD)
							{
								dealingSchedGrid.addRecord(data);
								dealingSchedGrid.selectLastRecord();
							}else{
								var selectedRecord = dealingSchedGrid.getSelectedRecord();
								if(selectedRecord.get('runMode') == this.ADD)
								{	
									data['runMode'] = this.ADD;
								}
								dealingSchedGrid.updateSelectedRecord(data);
							}
						}else{
							// Treat it as a removed item
							if(popup.action == this.MOD)
							{
								var selectedRecord = _resources.grids['dealingSched'].getSelectedRecord();
								if(selectedRecord.get('runMode') == this.ADD)
								{	
									dealingSchedGrid.removeSelectedRecord();
								}else{
									data['runMode'] = this.DEL;
									dealingSchedGrid.updateSelectedRecord(data);
								}
							}
						}
						break;
					case this.DEL:
						var selectedRecord = dealingSchedGrid.getSelectedRecord();
						if(selectedRecord.get('runMode') == this.ADD)
						{	
							dealingSchedGrid.removeSelectedRecord();
						}else{
							data['runMode'] = this.DEL;
							dealingSchedGrid.updateSelectedRecord(data);
						}
						break;
				}
				updateDealingSchedButtons();
				popup.hide();
				setChangeFlag();
			}
		}
		
		,selectDealing: function(record)
		{
			_selectedDealing = record;
			updateDealingSchedButtons();
		}
		
		,loadAvailableTransTypeSelector: function()
		{
			_resources.selectors['transType'].loadAvailableData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'dealTransType']"));
		}
		
		,populateFrequencyByValuationFrequency: function(freqObj)
		{
			populateFrequencyByValuationFrequency(freqObj);
		}
		
		,updateDealingSchedButtons: function()
		{
			updateDealingSchedButtons();
		}
		
		,getNextTempDealingUUID: function()
		{
			return ++_tmpDealingSchedUUIDRunning;
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