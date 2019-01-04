/*********************************************************************************************
 * @file	ClassSetup_PerfFeeConfig.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller file for Performance Fee Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
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
	var _screenId = "PerformanceFee";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	var _trackingType = null;
	
	var _selectedHurdle = null;
	var _hurdleRunningNumber = 0;
	
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
		_resources.fields['feeMethod'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'feeMethod']"));
		_resources.fields['calcBasis'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'calcBasis']"));
		_resources.fields['lossCarryForward'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'lossCarryForward']"));
		_resources.fields['divAddBack'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'divAddBack']"));
		_resources.fields['lotRedMethod'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'lotRedMethod']"));
		
		var popup = _resources.popups['updHurdle'];
		popup.getField('benchmarkType').loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'benchmarkType']"));
		popup.getField('benchmarkIndex').loadData(IFDS.Xml.getNode(_initDataXML, "MktIndexes"));
		popup.getField('daysBasis').loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'daysBasis']"));
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
	
	function populateScreen()	
	{
		var perfFeeNode = IFDS.Xml.getNode(_updatedClassDataXML, 'PerfFeeConfig');
		if(perfFeeNode)
		{
			setInitialFieldValue(_resources.fields['feeMethod'], IFDS.Xml.getNodeValue(perfFeeNode, 'feeMethod'));
			setInitialFieldValue(_resources.fields['calcBasis'], IFDS.Xml.getNodeValue(perfFeeNode, 'calcBasis'));
			setInitialFieldValue(_resources.fields['lossCarryForward'], IFDS.Xml.getNodeValue(perfFeeNode, 'lossCarryForward'));
			setInitialFieldValue(_resources.fields['divAddBack'], IFDS.Xml.getNodeValue(perfFeeNode, 'divAddBack'));
			setInitialFieldValue(_resources.fields['lotRedMethod'], IFDS.Xml.getNodeValue(perfFeeNode, 'lotRedMethod'));
			setInitialFieldValue(_resources.fields['perfFeeCalcPrecision'], IFDS.Xml.getNodeValue(perfFeeNode, 'perfFeeCalcPrecision'));
			setAllowedDecrease(_resources.fields['perfFeeCalcPrecision']
				, (_addMode)?'0':IFDS.Xml.getNodeValue(_existingClassDataXML, 'PerfFeeConfig/perfFeeCalcPrecision')
				, IFDS.Xml.getNode(perfFeeNode, 'perfFeeCalcPrecision'));
				
			setInitialFieldValue(_resources.fields['perfFeePrecision'], IFDS.Xml.getNodeValue(perfFeeNode, 'perfFeePrecision'));
			setAllowedDecrease(_resources.fields['perfFeePrecision']
				, (_addMode)?'0':IFDS.Xml.getNodeValue(_existingClassDataXML, 'PerfFeeConfig/perfFeePrecision')
				, IFDS.Xml.getNode(perfFeeNode, 'perfFeePrecision'));
				
			setInitialFieldValue(_resources.fields['gavRate'], IFDS.Xml.getNodeValue(perfFeeNode, 'gavRate'));
			
			var gavRateNode = IFDS.Xml.getNode(perfFeeNode, 'gavRate');
            var classHWMRateNode = IFDS.Xml.getNode(perfFeeNode, 'classHWMRate');
			var classHWMResetDateNode = IFDS.Xml.getNode(perfFeeNode, 'classHWMResetDate');			
			var allowedResetGAV = (gavRateNode)?gavRateNode.getAttribute('allowedReset'):'yes';
			var allowedResetHWM = 'no';  //Set this to be 'no' for always disable 'Initial HWM Rate' field.
			var allowedResetHWMDate = (classHWMResetDateNode)?classHWMResetDateNode.getAttribute('allowedReset'):'yes';
			
			if(!allowedResetGAV || allowedResetGAV == 'no')
			{
				_resources.fields['gavRate'].disableField();
			}else{
				_resources.fields['gavRate'].enableField();
			}
			
			if(!allowedResetHWM || allowedResetHWM == 'no')
			{
				_resources.fields['classHWMRate'].disableField();
			}else{
				_resources.fields['classHWMRate'].enableField();
			}
			
			if(!allowedResetHWMDate || allowedResetHWMDate == 'no')
			{
				_resources.fields['classHWMResetDate'].disableField();
			}else{
				_resources.fields['classHWMResetDate'].enableField();
			}
			
			setInitialFieldValue(_resources.fields['classHWMRate'], IFDS.Xml.getNodeValue(perfFeeNode, 'classHWMRate'));
			setInitialFieldValue(_resources.fields['classHWMResetDate'], DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(perfFeeNode, 'classHWMResetDate')));
			setInitialFieldValue(_resources.fields['hurdleApply'], IFDS.Xml.getNodeValue(perfFeeNode, 'hurdleApply'));
			var hurdleApplied = IFDS.Xml.getNodeValue(perfFeeNode, 'hurdleApply');
			if(hurdleApplied == 'yes')
			{
				_resources.fields['hurdleApply'].setValue(true);
				_resources.grids['hurdleConfig'].clearData();
				_resources.grids['hurdleConfig'].getStore().loadData(IFDS.Xml.getNode(perfFeeNode, 'PerfFeeHurdleConfigs'));
				_resources.grids['hurdleConfig'].show();
				if(_resources.grids['hurdleConfig'].getStore().getCount() > 0)
				{
					_resources.grids['hurdleConfig'].getSelectionModel().selectFirstRow();
				}
				updateHurdleButtons();
			}else{
				_resources.fields['hurdleApply'].setValue(false);
				_resources.grids['hurdleConfig'].hide();
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

			function setAllowedDecrease(fld, origVal, precisionNode)
			{
				if(precisionNode)
				{
					fld.originalValue = (origVal == "")?0:origVal;
					var allowedDecrease = precisionNode.getAttribute("allowedDecrease");
					fld.allowedDecrease = (!allowedDecrease)?"no":allowedDecrease;
				}else{
					fld.originalValue = 0;
					fld.allowedDecrease = "no";
				}
			}
		}
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
	
	function getMktIndexDescFromList(indexCode)
	{
		var desc = IFDS.Xml.getNodeValue(_initDataXML, 'MktIndexes/MktIndex[indexCode = "' + indexCode + '"]/indexName');
		return desc;
	}
	
	function validateSaveHurdle(action, popup)
	{
		var valid = true;
		var tmpValid = true;
		if(action != _self.DEL)
		{
			var benchmarkType = popup.getField('benchmarkType').getValue();
			
			if(benchmarkType == '01') // Benchmark Type is Fixed
			{
				tmpValid = validateRequiredField(popup.getField('fixRate'));
				valid = tmpValid && validatePositiveField(popup.getField('fixRate'), false) && valid;
				
				valid = validateRequiredField(popup.getField('daysBasis')) && valid;

				tmpValid = validateRequiredField(popup.getField('weighting'));
				valid = tmpValid && validatePositiveField(popup.getField('weighting'), false) && valid;
				
				if(valid)
				{
					var records = _resources.grids['hurdleConfig'].getStore().queryBy(
						function(record)
						{
							return (record.get('runMode') != _self.DEL 
									&& record.get('benchmarkType') == '01' 
									&& record.get('hurdleConfigUUID') != popup.hurdleConfigUUID)?record:null;
						}
					);

					if (records.getCount()>0)
					{
						DesktopWeb.Util.displayError(_translationMap['hurdle'] 
														+ " '"
														+ getValueDescFromList('benchmarkType', '01').replace(" ", "")
														+ "' "
														+ _translationMap['alreadyExists']);
						valid = false;
					}
				}
				
			}else{ // benchmarkType == '02'
				valid = validateRequiredField(popup.getField('benchmarkIndex')) && valid;
				
				valid = validateRequiredField(popup.getField('benchmarkAdjRate')) && valid;
				
				tmpValid = validateRequiredField(popup.getField('weighting'));
				valid = tmpValid && validatePositiveField(popup.getField('weighting'), false) && valid;

				if(valid)
				{
					var records = _resources.grids['hurdleConfig'].getStore().queryBy(
						function(record)
						{
							return (record.get('runMode') != _self.DEL 
									&& record.get('benchmarkType') == '02' 
									&& record.get('indexCode') == popup.getField('benchmarkIndex').getValue()
									&& record.get('hurdleConfigUUID') != popup.hurdleConfigUUID)?record:null;
						});
					if (records.getCount() > 0)
					{
						DesktopWeb.Util.displayError(_translationMap['hurdle'] 
														+ " '"
														+ getValueDescFromList('benchmarkType', '02')
														+ "', '"
														+ getValueDescFromList('benchmarkIndex', popup.getField('benchmarkIndex').getValue())
														+ "' "
														+ _translationMap['alreadyExists']);
						valid = false;
					}
				}
			}
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
	
	function validatePositiveField(f, allowZero)
	{
		allowZero = (allowZero)?allowZero:false;
		if(allowZero)
		{
			if(parseFloat(f.getValue()) < 0)
			{
				f.markInvalid(_translationMap['negativeValueNotAllowed']);
				return false;
			}
		}else{
			if(parseFloat(f.getValue()) <= 0)
			{
				f.markInvalid(_translationMap['requiredGreaterThanZero']);
				return false;
			}
		}
		return true;
	}
	
	function validateScreen()
	{
		var isValid = true;
		
		isValid = _resources.fields['feeMethod'].isValid() && isValid;
		
		var feeMethod = _resources.fields['feeMethod'].getValue();
		if (feeMethod == '01')
		{
			var calcBasis = _resources.fields['calcBasis'].getValue();
			if(!(calcBasis=='01' || calcBasis=='02'))
			{
				_resources.fields['calcBasis'].markInvalid(_translationMap['onlyRelativeAndAbsoluteErrMsg']);
				isValid = false;
			}
		}
		
		isValid = _resources.fields['lossCarryForward'].isValid() && isValid;
		isValid = _resources.fields['divAddBack'].isValid() && isValid;
		isValid = _resources.fields['lotRedMethod'].isValid() && isValid;
		isValid = _resources.fields['perfFeeCalcPrecision'].isValid() && isValid;
		isValid = _resources.fields['perfFeePrecision'].isValid() && isValid;
		
		isValid = _resources.fields['gavRate'].isValid() && isValid;
		isValid = _resources.fields['classHWMResetDate'].isValid() && isValid;
		
		var hurdleApplied = _resources.fields['hurdleApply'].getValue();
		if(hurdleApplied)
		{
			var records = _resources.grids['hurdleConfig'].getStore().queryBy(function(record){return record.get('runMode') != _self.DEL?record:null;});
			if (records.getCount()>0)
			{
				var totalWeight = 0;
				for(i = 0; i < records.getCount(); i++)
				{
					totalWeight += parseFloat(records.itemAt(i).get('weighting'));
				}
				if(totalWeight != 100)
				{
					DesktopWeb.Util.displayError(_translationMap['weightingErrMsg']);
					isValid = false;
				}
			}else{
				// Display error
				DesktopWeb.Util.displayError(_translationMap['hurldeConfigErrMsg']);
				isValid = false;
			}
		}
		
		return isValid;
	}
	
	function updateHurdle(action, data)
	{
		if (action == _self.ADD)
		{
			_resources.grids['hurdleConfig'].getStore().loadData(data, true);
			_resources.grids['hurdleConfig'].getSelectionModel().selectLastRow(false);
		}
		else
		{
			// annoying case where mod/del a brand new record
			if (_selectedHurdle.get('runMode') == _self.ADD)
			{
				if (action == _self.DEL)
				{
					_resources.grids['hurdleConfig'].removeSelectedRecord();
				}
				else
				{
					updateSelectedHurdleRecord(_self.ADD, data);
				}					
			}
			else
			{
				updateSelectedHurdleRecord(IFDS.Xml.getNodeValue(data, 'PerfFeeHurdleConfig/runMode'), data);
			}
		}
		if(!_resources.grids['hurdleConfig'].getSelectedRecord() 
			&& _resources.grids['hurdleConfig'].getStore().getCount() > 0)
		{
			_resources.grids['hurdleConfig'].getSelectionModel().selectFirstRow();
		}else{
			updateHurdleButtons();
		}
		setChangeFlag();
	}
	
	function updateHurdleButtons()
	{
		var grid = _resources.grids['hurdleConfig'];
		if(grid.getSelectedRecord())
		{
			grid.enableButton('modBtn');
			grid.enableButton('delBtn');
		}else{
			grid.disableButton('modBtn');
			grid.disableButton('delBtn');
		}
		grid.enableButton('addBtn');
	}
	
	function updateSelectedHurdleRecord(action, xml)
	{
		var hurdleConfig = IFDS.Xml.getNode(xml, 'PerfFeeHurdleConfig')
		_selectedHurdle.set('runMode', action);
		_selectedHurdle.set('benchmarkType', IFDS.Xml.getNodeValue(hurdleConfig, 'benchmarkType'));
		_selectedHurdle.set('fixedRate', IFDS.Xml.getNodeValue(hurdleConfig, 'fixedRate'));
		_selectedHurdle.set('indexCode', IFDS.Xml.getNodeValue(hurdleConfig, 'indexCode'));
		_selectedHurdle.set('adjRate', IFDS.Xml.getNodeValue(hurdleConfig, 'adjRate'));
		_selectedHurdle.set('daysBasis', IFDS.Xml.getNodeValue(hurdleConfig, 'daysBasis'));
		_selectedHurdle.set('weighting', IFDS.Xml.getNodeValue(hurdleConfig, 'weighting'));
		_resources.grids['hurdleConfig'].getStore().commitChanges();
	}
	
	function disableScreen()
	{
		for (var i in _resources.fields)
		{			
			_resources.fields[i].disableField();
		}
	}
	
	function addChangeHandlers()
	{		
		for (var i in _resources.fields)
		{			
			addHandler(_resources.fields[i]);
		}
		
		_resources.fields['gavRate'].addListener('change', gavRateChangeHandler);
		
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
	
	function gavRateChangeHandler()
	{
		if(_resources.fields['gavRate'].isValid())
		{
			_resources.fields['classHWMRate'].setValue(_resources.fields['gavRate'].getValue());
		}	
	}
	
	function setGAVRatePrecision()
	{
		var ratePreNode = IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo/ratePrecision');
		if(!ratePreNode && !_addMode)
		{
			ratePreNode = IFDS.Xml.getNode(_existingClassDataXML, 'PriceInfo/ratePrecision');
		}
		
		var ratePreTxt = (ratePreNode)?IFDS.Xml.getNodeValue(ratePreNode, '.'):'10';
		var ratePre = (ratePreTxt)?parseInt(ratePreTxt):10;
		
		_resources.fields['gavRate'].decimalPrecision = (ratePre>10)?10:ratePre;
		_resources.fields['classHWMRate'].decimalPrecision = (ratePre>10)?10:ratePre;
	}
	
	function isPerfFee()
	{
		var perfFeeFlagNode = IFDS.Xml.getNode(_updatedClassDataXML, 'FeeConfiguration/perfFeeFlag');
		if(!perfFeeFlagNode && !_addMode)
		{
			perfFeeFlagNode = IFDS.Xml.getNode(_existingClassDataXML, 'FeeConfiguration/perfFeeFlag');
		}
		
		var perfFeeFlagTxt = (perfFeeFlagNode)?IFDS.Xml.getNodeValue(perfFeeFlagNode, '.'):'no';
		return (perfFeeFlagTxt == 'yes');
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
		var perfFeeConfigXML = IFDS.Xml.getNode(_updatedClassDataXML, 'PerfFeeConfig');

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
		
		xmlWriteFn('feeMethod', _resources.fields['feeMethod'].getValue());
		xmlWriteFn('calcBasis', _resources.fields['calcBasis'].getValue());
		xmlWriteFn('lossCarryForward', _resources.fields['lossCarryForward'].getValue());
		xmlWriteFn('divAddBack', _resources.fields['divAddBack'].getValue());
		xmlWriteFn('lotRedMethod', _resources.fields['lotRedMethod'].getValue());
		xmlWriteFn('perfFeeCalcPrecision', _resources.fields['perfFeeCalcPrecision'].getValue());
		xmlWriteFn('perfFeePrecision', _resources.fields['perfFeePrecision'].getValue());
		xmlWriteFn('gavRate', _resources.fields['gavRate'].getValue());
		xmlWriteFn('classHWMRate', _resources.fields['classHWMRate'].getValue());
		xmlWriteFn('classHWMResetDate', _resources.fields['classHWMResetDate'].getSMVDateString());
		if (_addMode)
		{
			var gavRateNode = IFDS.Xml.getNode(perfFeeConfigXML, 'gavRate');
			IFDS.Xml.addAttribute(gavRateNode, "allowedReset", 'yes');
			var classHWMNode = IFDS.Xml.getNode(perfFeeConfigXML, 'classHWMRate');
			IFDS.Xml.addAttribute(classHWMNode, "allowedReset", 'no');
			var classHWMResetDateNode = IFDS.Xml.getNode(perfFeeConfigXML, 'classHWMResetDate');
			IFDS.Xml.addAttribute(classHWMResetDateNode, "allowedReset", 'yes');
		}
		
		if(_resources.fields['hurdleApply'].getValue())
		{
			xmlWriteFn('hurdleApply', 'yes');
			var hurdleNodes = IFDS.Xml.getNodes(perfFeeConfigXML, 'PerfFeeHurdleConfigs/PerfFeeHurdleConfig');
			for (var i = 0; i < hurdleNodes.length; i++)
			{
				IFDS.Xml.deleteNode(hurdleNodes[i]);
			}				
			Ext.each(_resources.grids['hurdleConfig'].getAllRecords(), function(rec){addHurdleRecordToXML(rec)});
		}else{
			xmlWriteFn('hurdleApply', 'No');
			var hurdleNodes = IFDS.Xml.getNodes(perfFeeConfigXML, 'PerfFeeHurdleConfigs/PerfFeeHurdleConfig');
			for (var i = 0; i < hurdleNodes.length; i++)
			{
				writeNewValueToXML('runMode', _self.DEL, hurdleNodes[i]);
			}
		}

		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? perfFeeConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if(!node)
			{
				node = IFDS.Xml.addSingleNode(context, fldName, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}else
			if(fldName=="gavRate" || fldName=="classHWMRate"){
				if (IFDS.Xml.getNodeValue(node, '.').replace(/,/gi, '') != value)
				{
					IFDS.Xml.setNodeValue(node, value);
					IFDS.Xml.addAttribute(node, "status", _self.MOD);
				}
			}else
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? perfFeeConfigXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}		
		
		function addHurdleRecordToXML(rec)
		{
			var hurdlesNode = IFDS.Xml.getNode(perfFeeConfigXML, 'PerfFeeHurdleConfigs');
			if(!hurdlesNode){
				hurdlesNode = IFDS.Xml.addSingleNode(perfFeeConfigXML, 'PerfFeeHurdleConfigs');
			}
			var recordNode = IFDS.Xml.addSingleNode(hurdlesNode, 'PerfFeeHurdleConfig');			
			IFDS.Xml.addSingleNode(recordNode, 'runMode', rec.data['runMode']);
			IFDS.Xml.addSingleNode(recordNode, 'hurdleConfigUUID', rec.data['hurdleConfigUUID']);
			IFDS.Xml.addSingleNode(recordNode, 'benchmarkType', rec.data['benchmarkType']);
			IFDS.Xml.addSingleNode(recordNode, 'fixedRate', rec.data['fixedRate']);
			IFDS.Xml.addSingleNode(recordNode, 'indexCode', rec.data['indexCode']);			
			IFDS.Xml.addSingleNode(recordNode, 'adjRate', rec.data['adjRate']);
			IFDS.Xml.addSingleNode(recordNode, 'daysBasis', rec.data['daysBasis']);
			IFDS.Xml.addSingleNode(recordNode, 'weighting', rec.data['weighting']);
			IFDS.Xml.addSingleNode(recordNode, 'version', rec.data['version']);
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

			DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ScreenDefList', 'ExistingClassData', 'UpdatedClassData'], responseHandler, _translationMap['ProcMsg_Loading']);
			 								
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
					if (IFDS.Xml.getNode(_updatedClassDataXML, 'PerfFeeConfig') == null)				
					{
						if(IFDS.Xml.getNode(_existingClassDataXML, 'PerfFeeConfig') != null)
						{
							IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'PerfFeeConfig')));				
						}else{
							IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_initDataXML, '//DefaultValues/PerfFeeConfig')));
							DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, doNothing, _translationMap['ProcMsg_saving']);
						}
					}
				}else{
					if (IFDS.Xml.getNode(_updatedClassDataXML, 'PerfFeeConfig') == null)
					{
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_initDataXML, '//DefaultValues/PerfFeeConfig')));
						DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, doNothing, _translationMap['ProcMsg_saving']);
					}
				}
				
				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateDropdowns();
				addChangeHandlers();
				setGAVRatePrecision();
				if(isPerfFee())
				{
					populateScreen();
				}else{
					disableScreen();
				}
				clearChangeFlag();
				function doNothing(){}
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
		
		,changeGAVRate: function(fld)
		{
			validateGAVRate(fld);
		}
		
		,openHurdlePopup: function(action)
		{
			var popup;
			if (action == this.DEL)
			{
				popup = _resources.popups['delHurdle'];
			}else{
				popup = _resources.popups['updHurdle'];
			}
			popup.init(action);
			popup.show();
		}
		
		,closeHurdlePopup: function(action)
		{
			if (action == this.DEL)
			{
				_resources.popups['delHurdle'].hide();
			}else{
				_resources.popups['updHurdle'].hide();
			}
		}
		
		,selectBenchmarkType: function(benchmarkType)
		{
			var popup = _resources.popups['updHurdle'];
			if (benchmarkType == '01') //Benchmark Type = Fixed
			{
				popup.getField('fixRate').setValue('0');
				popup.getField('daysBasis').setValue('01');
				popup.getField('weighting').setValue('0');
				popup.getField('benchmarkIndex').setValue('');
				popup.getField('benchmarkAdjRate').setValue('');
				popup.getField('benchmarkIndex').disableField();
				popup.getField('benchmarkAdjRate').disableField();
				popup.getField('fixRate').enableField();
				popup.getField('daysBasis').enableField();
				popup.getField('weighting').enableField();
			}else{
				popup.getField('fixRate').setValue('');
				popup.getField('benchmarkIndex').setValue('');
				popup.getField('benchmarkAdjRate').setValue('0');
				popup.getField('daysBasis').setValue('');
				popup.getField('weighting').setValue('0');
				popup.getField('fixRate').disableField();
				popup.getField('daysBasis').disableField();
				popup.getField('benchmarkIndex').enableField();
				popup.getField('benchmarkAdjRate').enableField();
				popup.getField('weighting').enableField();
			}
		}
		
		,selectBenchmarkIndex: function(record)
		{
			_resources.popups['updHurdle'].getField('daysBasis').setValue(record.get('daysBasis'));
		}
		
		,checkedHurdle: function(checked)
		{
			if (checked) 
			{
				_resources.grids['hurdleConfig'].show();
				updateHurdleButtons();
			}else{
				_resources.grids['hurdleConfig'].hide();
			}
		}
		
		,selectHurdle: function(record)
		{
			_selectedHurdle = record;
		}
		
		,saveHurdle: function(action, popup)
		{
			if (validateSaveHurdle(action, popup))
			{
				var data = IFDS.Xml.newDocument('data');
				var hurdleXML = IFDS.Xml.addSingleNode(data, 'PerfFeeHurdleConfig');
				IFDS.Xml.addSingleNode(hurdleXML, 'runMode', action);
				if(action != this.DEL)
				{
					IFDS.Xml.addSingleNode(hurdleXML, 'hurdleConfigUUID', (action==this.ADD)?++_hurdleRunningNumber:popup.hurdleConfigUUID);
					IFDS.Xml.addSingleNode(hurdleXML, 'benchmarkType', popup.getField('benchmarkType').getValue());
					IFDS.Xml.addSingleNode(hurdleXML, 'fixedRate', popup.getField('fixRate').getValue());
					IFDS.Xml.addSingleNode(hurdleXML, 'indexCode', popup.getField('benchmarkIndex').getValue());
					IFDS.Xml.addSingleNode(hurdleXML, 'adjRate', popup.getField('benchmarkAdjRate').getValue());
					IFDS.Xml.addSingleNode(hurdleXML, 'daysBasis', popup.getField('daysBasis').getValue());
					IFDS.Xml.addSingleNode(hurdleXML, 'weighting', popup.getField('weighting').getValue());
				}else{
					IFDS.Xml.addSingleNode(hurdleXML, 'hurdleConfigUUID', _selectedHurdle.hurdleConfigUUID);
					IFDS.Xml.addSingleNode(hurdleXML, 'benchmarkType', _selectedHurdle.get('benchmarkType'));
					IFDS.Xml.addSingleNode(hurdleXML, 'fixedRate', _selectedHurdle.get('fixedRate'));
					IFDS.Xml.addSingleNode(hurdleXML, 'indexCode', _selectedHurdle.get('indexCode'));
					IFDS.Xml.addSingleNode(hurdleXML, 'adjRate', _selectedHurdle.get('adjRate'));
					IFDS.Xml.addSingleNode(hurdleXML, 'daysBasis', _selectedHurdle.get('daysBasis'));
					IFDS.Xml.addSingleNode(hurdleXML, 'weighting', _selectedHurdle.get('weighting'));
				}
				updateHurdle(action, data);
				this.closeHurdlePopup(action);
			}
		}
		
		,getValueDescFromList: function(listId, val)
		{
			return getValueDescFromList(listId, val);
		}
		
		,getMktIndexDescFromList: function(val)
		{
			return getMktIndexDescFromList(val);
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