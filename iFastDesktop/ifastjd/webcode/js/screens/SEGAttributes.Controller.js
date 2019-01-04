/*********************************************************************************************
 * @file	SEGAttributes.Controller.js
 * @author	Danny Xu
 * @desc	Controller JS file for SEG Attributes screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *        - Fix display date format follows dateFormatDisplay parameter
 * 
 * 	03 Sep 2014 P. Wongpakdee P0232147 DFT0038250 T55659
 *		  - Fixed a script error when XML (_updateXML, _inquiryXML) is blank
 *			at Initial state. This is effected to all drop downs, Text boxes
 *			Admin button and OK button in Adding pop up screens (DMG, DBG)
 *
 * 	25 Sep 2014 P. Wongpakdee P0233151 INA Cayenne Day 2 T55815
 *		  - set show/hide fields under panels CMD, DBG, DMG, GWB
 *		  - fix to validate only show up panels on screen in updateValidate
 *		  - assign flags updatesFlag and searchState
 *		  - add functions callupdatesFlagStatus and updatesFlagStatus
 *		  - add function validateSearchCriteria for searching
 *
 * 	Oct 15 2014 P. Wongpakdee P0233151 DFT0042592 T55878
 *		  - fix to display TaxType and Jurisdiction without Java
 *			Script error
 *
 *	09 Apr 2015 A. Mongkonrat P0232343 T80576 Fox Project B Payout Contract Type
 *              - Add Allow Negative LWA checkbox.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *		  - Fixed screens don't response when user's profile has too many slots attached.   
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = 'dtSEGAttribReload';
	var _classSearchView = 'dtSEGAttribReload';
	var _updateView = 'dtSEGAttribUpd';	
	var _initDataXML = null;
	var _inquiryXML = null;
	var data = {};
	var mstr = {};
	var _permissionsMap = {};
	var _updateXML = null;
	var _taxTypeInq;
	var _jurisdictionInq;
	var newRecNum = 0;
	
	// PRIVATE METHODS ****************************************
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, "//Mstr[attribType = 'DBG']/addPerm").toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, "//Mstr[attribType = 'DBG']/modPerm").toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, "//Mstr[attribType = 'DBG']/delPerm").toLowerCase() == 'yes';
		
		_permissionsMap[_self.ADD] = true
		_permissionsMap[_self.MOD] = true
		_permissionsMap[_self.DEL] = true
	}
	
	function loadGridData(classSearchXML, grid, string)
	{		
		_resources.grids[grid].loadData(IFDS.Xml.getNode(classSearchXML, '/*//' + string), null);
	}
	
	function addChangeHandlers()
	{		
		_resources.fields['newContractAllowed'].onclick = _self.handleCheckBoxes;
		_resources.fields['newMoneyAllowed'].onclick = _self.handleCheckBoxes;
	}
	
	function populateDropdowns(initViewXML)
	{		
		_resources.fields['contractType'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'ContractTypeList']"));
		_resources.fields['maturityInstruction'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'DfltMatInstrList']"));
		
		_resources.fields['cmdBasedOn'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'CMDBasedOn']"));
		_resources.fields['defaultCMDBasedOn'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'DfltCMDBasedOn']"));
		
		_resources.fields['lwaAvailability'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'LWAAvailiabilityList']"));
		_resources.fields['lwaGprMeth'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'LWAGPRMethList']"));
		
		_resources.fields['contractOnlineEWI'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'EWIList']"));
		_resources.fields['contractEsgEWI'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'EWIList']"));
		_resources.fields['moneyOnlineEWI'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'EWIList']"));
		_resources.fields['moneyEsgEWI'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'EWIList']"));
		
		_resources.fields['taxType'].loadAvailableData(IFDS.Xml.getNode(initViewXML, "*/List[@listName = 'TaxTypeList']"));
		_resources.fields['jurisdiction'].loadAvailableData(IFDS.Xml.getNode(initViewXML, "*/List[@listName = 'PensionList']"));
		

		_resources.grids['dbgGrid'].disableButton('modBtn');
		_resources.grids['dbgGrid'].disableButton('delBtn');
		_resources.grids['dmgGrid'].disableButton('modBtn');
		_resources.grids['dmgGrid'].disableButton('delBtn');
	}
	
	function loadData (initViewXML)
	{
		
		var cmdXML = IFDS.Xml.getNode(initViewXML, "//Mstr[attribType = 'CMD']");
		if (cmdXML != null)
		{
			_resources.fields['cmdBasedOn'].setValue(IFDS.Xml.getNodeValue(cmdXML, "*/Detl[attribCode = 'CMDBaseOn']/attribValue"));
			_resources.fields['cmdBasedOn'].disable();
			_resources.fields['maxMDAge'].setValue(IFDS.Xml.getNodeValue(cmdXML, "*/Detl[attribCode = 'MaxAge']/attribValue"));
			_resources.fields['minMDAge'].setValue(IFDS.Xml.getNodeValue(cmdXML, "*/Detl[attribCode = 'MinAge']/attribValue"));
			_resources.fields['minTerm'].setValue(IFDS.Xml.getNodeValue(cmdXML, "*/Detl[attribCode = 'MinTerm']/attribValue"));
			_resources.fields['defaultCMDBasedOn'].setValue(IFDS.Xml.getNodeValue(cmdXML, "*/Detl[attribCode = 'DfCMDBaseOn']/attribValue"));
			_resources.fields['defaultCMDBasedOn'].disable();
			Ext.getCmp('CMD').show();
			
			/* Set fields to be shown if the parent panel CMD is shown  */			
			_resources.fields['cmdBasedOn'].show();
			_resources.fields['dmdBasedOn'].show();
			_resources.fields['maxMDAge'].show();
			_resources.fields['minMDAge'].show();
			_resources.fields['minTerm'].show();
			_resources.fields['defaultCMDBasedOn'].show();
		}
		else
		{
			Ext.getCmp('CMD').hide();
			
			/* Set fields to be hidden if the parent panel CMD is hided  */			
			_resources.fields['cmdBasedOn'].hide();
			_resources.fields['dmdBasedOn'].hide();
			_resources.fields['maxMDAge'].hide();
			_resources.fields['minMDAge'].hide();
			_resources.fields['minTerm'].hide();
			_resources.fields['defaultCMDBasedOn'].hide();			
		}
		
		var dbgXML = IFDS.Xml.getNode(initViewXML, "//Mstr[attribType = 'DBG']");
		if (dbgXML != null)
		{
			_resources.fields['dbgRate'].setValue(IFDS.Xml.getNodeValue(dbgXML, "*/Detl[attribCode = 'Rate']/attribValue"));
			_resources.fields['dbgRateAfterClosing'].setValue(IFDS.Xml.getNodeValue(dbgXML, "*/Detl[attribCode = 'RtAfCls']/attribValue"));
			if (IFDS.Xml.getNode(dbgXML, '*/Reductions')!= null && IFDS.Xml.getNodeValue (dbgXML, '*/Reductions') != "")
			{
				_resources.grids['dbgGrid'].loadData(IFDS.Xml.getNode(dbgXML, '*/Reductions'));
				_resources.grids['dbgGrid'].enableButton('modBtn');
				_resources.grids['dbgGrid'].enableButton('delBtn');
			}
			else
			{
				_resources.grids['dbgGrid'].clearData();
				_resources.grids['dbgGrid'].enableButton('addBtn');
			}
			Ext.getCmp('DBG').show();
			
			/* Set fields to be shown if the parent panel DBG is shown  */			
			_resources.fields['dbgRate'].show();
			_resources.fields['dbgRateAfterClosing'].show();			
		}
		else
		{
			Ext.getCmp('DBG').hide();
			
			/* Set fields to be hidden if the parent panel DBG is hided  */			
			_resources.fields['dbgRate'].hide();
			_resources.fields['dbgRateAfterClosing'].hide();
		}
		
		var dmgXML = IFDS.Xml.getNode(initViewXML, "//Mstr[attribType = 'DMG']");
		if (dmgXML != null)
		{
			_resources.fields['dmgRate'].setValue(IFDS.Xml.getNodeValue(dmgXML, "*/Detl[attribCode = 'Rate']/attribValue"));
			_resources.fields['dmgRateAfterClosing'].setValue(IFDS.Xml.getNodeValue(dmgXML, "*/Detl[attribCode = 'RtAfCls']/attribValue"));
			if (IFDS.Xml.getNode(dmgXML, '*/Reductions')!= null && IFDS.Xml.getNodeValue (dmgXML, '*/Reductions') != "")
			{
				_resources.grids['dmgGrid'].loadData(IFDS.Xml.getNode(dmgXML, '*/Reductions'));
				_resources.grids['dmgGrid'].enableButton('modBtn');
				_resources.grids['dmgGrid'].enableButton('delBtn');
			}
			else
			{
				_resources.grids['dmgGrid'].clearData();
				_resources.grids['dmgGrid'].enableButton('addBtn');
			}
			Ext.getCmp('DMG').show();
			
			/* Set fields to be shown if the parent panel DMG is shown  */			
			_resources.fields['dmgRate'].show();
			_resources.fields['dmgRateBeforeCDDate'].show();	
			_resources.fields['dmgRateAfterCDDate'].show();
			_resources.fields['dmgRateAfterClosing'].show();			
		}
		else
		{
			Ext.getCmp('DMG').hide();
			
			/* Set fields to be hidden if the parent panel DMG is hided  */			
			_resources.fields['dmgRate'].hide();
			_resources.fields['dmgRateBeforeCDDate'].hide();	
			_resources.fields['dmgRateAfterCDDate'].hide();
			_resources.fields['dmgRateAfterClosing'].hide();
		}
		
		var gwbXML = IFDS.Xml.getNode(initViewXML, "//Mstr[attribType = 'GWB']");
		if (gwbXML != null)
		{
			_resources.fields['bonusBasePercent'].setValue(IFDS.Xml.getNodeValue(gwbXML, "*/Detl[attribCode = 'BonusBase']/attribValue"));
			_resources.fields['bonusRate'].setValue(IFDS.Xml.getNodeValue(gwbXML, "*/Detl[attribCode = 'BonusRate']/attribValue"));
			_resources.fields['gwaRate'].setValue(IFDS.Xml.getNodeValue(gwbXML, "*/Detl[attribCode = 'GWARate']/attribValue"));
			_resources.fields['lwaAvailability'].setValue(IFDS.Xml.getNodeValue(gwbXML, "*/Detl[attribCode = 'LWAAvailability']/attribValue"));
			_resources.fields['lwaGprMeth'].setValue(IFDS.Xml.getNodeValue(gwbXML, "*/Detl[attribCode = 'LWAGPRMeth']/attribValue"));
			var immBenefEligChk = IFDS.Xml.getNodeValue(gwbXML, "*/Detl[attribCode = 'ImmBenefElig']/attribValue");
			var allowNegativeLWAChk = IFDS.Xml.getNodeValue(gwbXML, "*/Detl[attribCode = 'RemLWA']/attribValue");
			_resources.fields['immBenefElig'].setValue(immBenefEligChk != null && immBenefEligChk.toLowerCase() == 'yes');
			_resources.fields['allowNegativeLWA'].setValue(allowNegativeLWAChk != null && allowNegativeLWAChk.toLowerCase() == 'yes');
			Ext.getCmp('GWB').show();
			
			/* Set fields to be shown if the parent panel GWB is shown  */			
			_resources.fields['gwaRate'].show();
			_resources.fields['bonusRate'].show();	
			_resources.fields['bonusBasePercent'].show();
			_resources.fields['lwaAvailability'].show();
			_resources.fields['lwaGprMeth'].show();			
			_resources.fields['immBenefElig'].show();	
			_resources.fields['allowNegativeLWA'].show();
		}
		else
		{
			Ext.getCmp('GWB').hide();
			
			/* Set fields to be hidden if the parent panel GWB is hided  */			
			_resources.fields['gwaRate'].hide();
			_resources.fields['bonusRate'].hide();	
			_resources.fields['bonusBasePercent'].hide();
			_resources.fields['lwaAvailability'].hide();
			_resources.fields['lwaGprMeth'].hide();			
			_resources.fields['immBenefElig'].hide();
			_resources.fields['allowNegativeLWA'].hide();
		}
		
		var genXML = IFDS.Xml.getNode(initViewXML, "//Mstr[attribType = 'GEN']");
		var checkBox1 = IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'NewContract']/attribValue");
		var checkBox2 = IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'NewMoney']/attribValue");
		_resources.fields['newContractAllowed'].checked = (checkBox1 != null && checkBox1.toLowerCase() == 'yes');
		_resources.fields['newMoneyAllowed'].checked = (checkBox2 != null && checkBox2.toLowerCase() == 'yes');
		_resources.fields['revPerThd'].setValue(IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'RevPerThd']/attribValue"));
		
		if (!_resources.fields['newContractAllowed'].checked)
		{
			_resources.fields['contractOnlineEWI'].setValue(IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'NewContract']/onLineEWI"));
			_resources.fields['contractEsgEWI'].setValue(IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'NewContract']/eSGEWI"));
		}

		if (!_resources.fields['newMoneyAllowed'].checked)
		{
			_resources.fields['moneyOnlineEWI'].setValue(IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'NewMoney']/onLineEWI"));
			_resources.fields['moneyEsgEWI'].setValue(IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'NewMoney']/eSGEWI"));
		}
		
		_resources.fields['maturityInstruction'].setValue(IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'DefMurInstr']/attribValue"));		
		_resources.fields['clsPrdTerm'].setValue(IFDS.Xml.getNodeValue(genXML, "*/Detl[attribCode = 'ClsPrdTerm']/attribValue"));
		_resources.fields['taxType'].removeAllFromSelected();
		_resources.fields['jurisdiction'].removeAllFromSelected();
		
		if (IFDS.Xml.getNodeValue(genXML, "taxType") != null && IFDS.Xml.getNodeValue(genXML, "taxType") != "")
		{	
			var selector = _resources.fields['taxType'];
			var records = selector.availableGrid.getAllRecords();			
			
			_taxTypeInq = IFDS.Xml.getNodeValue(genXML, "taxType").replace(/,+$/, '').split(",");
			
			Ext.each(_taxTypeInq, function(taxtype){
				for(var i = 0; i < records.length; i++)
				{
					if(taxtype.toLowerCase() == records[i].get('code').toLowerCase()){ 
						selector.addToSelected([records[i]]);
						break;
					}
				}
			});
		}
		else
		{
			_taxTypeInq = [];
		}
		
		if (IFDS.Xml.getNodeValue(genXML, "pensionJuris") != null && IFDS.Xml.getNodeValue(genXML, "pensionJuris") != "")
		{
			var selector = _resources.fields['jurisdiction'];
			var records = selector.availableGrid.getAllRecords();			
			
			_jurisdictionInq = IFDS.Xml.getNodeValue(genXML, "pensionJuris").split(",");
			
			Ext.each(_jurisdictionInq, function(jurisdiction){
				for(var i = 0; i < records.length; i++)
				{
					if(jurisdiction.toLowerCase() == records[i].get('code').toLowerCase()){ 
						selector.addToSelected([records[i]]);
						break;
					}
				}
			});
		}
		else
		{
			_jurisdictionInq = [];
		}
		
		for (var i in _resources.fields)
		{
			if (i == 'taxType' || i == 'jurisdiction' || i == 'newContractAllowed' || i == 'newMoneyAllowed');
			else
				_resources.fields[i].clearInvalid();
		}
		
		_updateXML = IFDS.Xml.getNode (_inquiryXML, "//Mstrs");
	}
	
	function isNewRecord(record)
	{
		return record.data['runMode'] == _self.ADD
	}
	
	function getUpdatedRecordCount(grid)
	{		
		var store = _resources.grids[grid].getStore();
		var newRecords = store.query('runMode', _self.ADD);	
		var modRecords = store.query('runMode', _self.MOD);		
		var delRecords = store.query('runMode', _self.DEL);
		return newRecords.length + modRecords.length + delRecords.length 
	}
	
	
	function initBuildXML(responseXML)
	{
		data['cmdBasedOn'] = 'CMDBaseOn';
		data['maxMDAge'] = 'MaxAge';
		data['minMDAge'] = 'MinAge';
		data['minTerm'] = 'MinTerm';
		data['defaultCMDBasedOn'] = 'DfCMDBaseOn';
		data['dbgRate'] = 'Rate';
		data['dbgRateAfterClosing'] = 'RtAfCls';
		data['dmgRate'] = 'Rate';
		data['dmgRateAfterClosing'] = 'RtAfCls';
		data['bonusBasePercent'] = 'BonusBase';
		data['bonusRate'] = 'BonusRate';
		data['gwaRate'] = 'GWARate';
		data['lwaAvailability'] = 'LWAAvailability';
		data['lwaGprMeth'] = 'LWAGPRMeth';
		data['immBenefElig'] = 'ImmBenefElig';
		data['allowNegativeLWA'] = 'RemLWA';
		data['maturityInstruction'] = 'DefMurInstr';
		data['revPerThd'] ='RevPerThd';
		data['contractOnlineEWI'] = 'NewContract';
		data['contractEsgEWI'] = 'NewContract';
		data['moneyOnlineEWI'] = 'NewMoney';
		data['moneyEsgEWI'] = 'NewMoney';
		
		mstr['cmdBasedOn'] = 'CMD';
		mstr['maxMDAge'] = 'CMD';
		mstr['minMDAge'] = 'CMD';
		mstr['minTerm'] = 'CMD';
		mstr['defaultCMDBasedOn'] = 'CMD';
		mstr['dbgRate'] = 'DBG';
		mstr['dbgRateAfterClosing'] = 'DBG';
		mstr['dmgRate'] = 'DMG';
		mstr['dmgRateAfterClosing'] = 'DMG';
		mstr['bonusBasePercent'] = 'GWB';
		mstr['bonusRate'] = 'GWB';
		mstr['gwaRate'] = 'GWB';
		mstr['lwaAvailability'] = 'GWB';
		mstr['lwaGprMeth'] = 'GWB';
		mstr['immBenefElig'] = 'GWB';
		mstr['allowNegativeLWA'] = 'GWB';
		mstr['maturityInstruction'] = 'GEN';
		mstr['revPerThd'] = 'GEN';
		mstr['contractOnlineEWI'] = 'GEN';
		mstr['contractEsgEWI'] = 'GEN';
		mstr['moneyOnlineEWI'] = 'GEN';
		mstr['moneyEsgEWI'] = 'GEN';
		
	}
	
	function updateValidate()
	{
		var flag = true;
		for (var i in _resources.fields)
		{
			if (_resources.fields[i].hidden);
			else{
				callbackFn_updateValidate(i);
			}
		}
		
		function callbackFn_updateValidate(valField)
		{
			if (_resources.fields[valField].isValid && !_resources.fields[valField].isValid())
			{			
				if (flag)
				{
					Ext.getCmp('accordionLayout').layout.setActiveItem(mstr[valField]);
					flag = false;
				}
			}
		}
		return flag;
	}
	
	
	function buildUpdateXml()
		{
			var _newXML = IFDS.Xml.newDocument('Mstrs');
			
			var taxTypeSelections = [];			
			Ext.each(_resources.fields['taxType'].getSelectedRecords(), function(rec){taxTypeSelections.push(rec.data.code)});
			var jurisdictionSelections = [];			
			Ext.each(_resources.fields['jurisdiction'].getSelectedRecords(), function(rec){jurisdictionSelections.push(rec.data.code)});
			if (taxTypeSelections.toString() != _taxTypeInq.toString() || jurisdictionSelections.toString() != _jurisdictionInq.toString())
			{
				var _genXML = IFDS.Xml.getNode (_updateXML, "//Mstr[attribType = 'GEN']");
				IFDS.Xml.replaceSingleNode (_genXML, 'runMode', _self.MOD);
				if (taxTypeSelections.toString() != _taxTypeInq.toString())
					IFDS.Xml.replaceSingleNode (_genXML, 'taxType', taxTypeSelections);
				if (jurisdictionSelections.toString() != _jurisdictionInq.toString())
					IFDS.Xml.replaceSingleNode (_genXML, 'pensionJuris', jurisdictionSelections);
			}
			
			var checkBox1 = _resources.fields['newContractAllowed'].checked;
			var checkBox2 = _resources.fields['newMoneyAllowed'].checked;
			var currentCheckBox1 = IFDS.Xml.getNodeValue(_updateXML, "//Mstr[attribType = 'GEN']/Detls/Detl[attribCode = 'NewContract']/attribValue");
			var currentCheckBox2 = IFDS.Xml.getNodeValue(_updateXML, "//Mstr[attribType = 'GEN']/Detls/Detl[attribCode = 'NewMoney']/attribValue");
			if (currentCheckBox1 == null || checkBox1 != (currentCheckBox1.toLowerCase() == 'yes'))
			{
				var tempXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = 'GEN']/Detls/Detl[attribCode = 'NewContract']");
				IFDS.Xml.replaceSingleNode(tempXML, 'runMode', 'mod');
				IFDS.Xml.replaceSingleNode(tempXML, 'attribValue', checkBox1 ? 'yes' : 'no');
				var mstrXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = 'GEN']");
				IFDS.Xml.replaceSingleNode(mstrXML, 'runMode', 'mod');
			}
			
			if (currentCheckBox2 == null || checkBox2 != (currentCheckBox2.toLowerCase() == 'yes'))
			{
				var tempXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = 'GEN']/Detls/Detl[attribCode = 'NewMoney']");
				IFDS.Xml.replaceSingleNode(tempXML, 'runMode', 'mod');
				IFDS.Xml.replaceSingleNode(tempXML, 'attribValue', checkBox2 ? 'yes' : 'no');
				var mstrXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = 'GEN']");
				IFDS.Xml.replaceSingleNode(mstrXML, 'runMode', 'mod');
			}
			
			var mstrXML = IFDS.Xml.getNodes(_updateXML, "//Mstr");
			for (var i = 0; i < mstrXML.length; i++)
			{
				if (IFDS.Xml.getNodeValue(mstrXML[i], "runMode") == "mod")
				{
					var _tempNodeXML = IFDS.Xml.cloneDocument(mstrXML[i]);
					IFDS.Xml.appendNode(_newXML, _tempNodeXML);
				}
			}
			
			var tempXML = IFDS.Xml.getNodes(_newXML, "//Detl");
			for (var i = 0; i < tempXML.length; i++)
			{
				if (IFDS.Xml.getNode(tempXML[i], "runMode") == null || IFDS.Xml.getNodeValue(tempXML[i], "runMode") == "")
					IFDS.Xml.deleteNode(tempXML[i]);
			}
			
			var reductionXML = IFDS.Xml.getNodes(_newXML, "//Reduction");
			for (var i = 0; i < reductionXML.length; i++)
			{
				if (IFDS.Xml.getNode(reductionXML[i], "runMode") == null || IFDS.Xml.getNodeValue(reductionXML[i], "runMode") == "")
					IFDS.Xml.deleteNode(reductionXML[i]);
			}			
			
			return _newXML;
		}
		
		function addNewGridXml(grid, data)
		{
			var _newXML = IFDS.Xml.newDocument('Reduction');
			IFDS.Xml.addSingleNode (_newXML, 'runMode', "add");
			IFDS.Xml.addSingleNode (_newXML, 'num', data['num']);
			IFDS.Xml.addSingleNode (_newXML, 'cotAttribMstrID', "");
			IFDS.Xml.addSingleNode (_newXML, 'redAgeAttribUUID', "");
			IFDS.Xml.addSingleNode (_newXML, 'redAgeAttribCode', "");
			IFDS.Xml.addSingleNode (_newXML, 'redAgeAttribValue', data['redAgeAttribValue']);
			IFDS.Xml.addSingleNode (_newXML, 'redAgeAttribDesc', "");
			IFDS.Xml.addSingleNode (_newXML, 'rtAfAttribUUID', "");
			IFDS.Xml.addSingleNode (_newXML, 'rtAfAttribCode', "");
			IFDS.Xml.addSingleNode (_newXML, 'rtAfAttribValue', data['rtAfAttribValue']);
			IFDS.Xml.addSingleNode (_newXML, 'rtAfAttribDesc', "");
			
			if (grid == "dbgGrid")
				newGrid = "DBG";
			else newGrid = "DMG";

			/** _updateXML is assgined from SEARCH action but be blank while INITIAL; caused a script error **/
			if (_updateXML != null)
			{
				var mstrXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + newGrid + "']");
				var reductionXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + newGrid + "']/Detls/Reductions");
				IFDS.Xml.appendNode (reductionXML, _newXML);
				IFDS.Xml.replaceSingleNode(mstrXML, 'runMode', _self.MOD);
			}			
		}
		
		function appendToGridXml(grid, action)
		{
			var selectedRecord = _resources.grids[grid].getSelectedRecord();
			var value;
			if (grid == 'dbgGrid')
				value = 'DBG';
			else if (grid == 'dmgGrid')
				value = 'DMG';
			var tempXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + value + "']/Detls/Reductions/Reduction[redAgeAttribUUID = '" + selectedRecord.data['redAgeAttribUUID'] + "']");
			if (tempXML != null)
			{
				IFDS.Xml.replaceSingleNode(tempXML, 'runMode', action);
			}
			else
			{
				tempXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + value + "']/Detls/Reductions/Reduction[num = '" + selectedRecord.data['num'] + "']");
				if (action == _self.DEL)
				{
					IFDS.Xml.deleteNode (tempXML)
				}
			}
			
			if (action == _self.MOD)
			{
				IFDS.Xml.replaceSingleNode(tempXML, 'redAgeAttribValue', selectedRecord.data['redAgeAttribValue']);
				IFDS.Xml.replaceSingleNode(tempXML, 'rtAfAttribValue', selectedRecord.data['rtAfAttribValue']);
			}
			var tempXML2 = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + value + "']")
			IFDS.Xml.replaceSingleNode(tempXML2, 'runMode', _self.MOD);
		}
		
		function toggleCheckBoxes()
		{
			if (_resources.fields['newContractAllowed'].checked)
			{
				_resources.fields['contractOnlineEWI'].clearValue();
				_resources.fields['contractEsgEWI'].clearValue();
				_resources.fields['contractOnlineEWI'].disable();
				_resources.fields['contractEsgEWI'].disable();
			}
			else
			{
				_resources.fields['contractOnlineEWI'].enable();
				_resources.fields['contractEsgEWI'].enable();
			}
			
			if (_resources.fields['newMoneyAllowed'].checked)
			{
				_resources.fields['moneyOnlineEWI'].clearValue();
				_resources.fields['moneyEsgEWI'].clearValue();
				_resources.fields['moneyOnlineEWI'].disable();
				_resources.fields['moneyEsgEWI'].disable();
			}
			else
			{
				_resources.fields['moneyOnlineEWI'].enable();
				_resources.fields['moneyEsgEWI'].enable();
			}
		}
		
		function displayAlert(responseXML)
		{
			if (IFDS.Xml.getNode (responseXML, '//template') != null)
			{
				DesktopWeb.Util.displayInfo("No attributes found, please fill out the page.");
			}
		}
		
		function updatesFlagStatus(confirm)
		{
			if (confirm){
				return _self.updatesFlag = true;			
			}else{
				return _self.updatesFlag = false;
			}
		}		
	
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'	
		,updatesFlag: false
		,searchState: false
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var viewParamXML = IFDS.Xml.newDocument('data');
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, null, responseHandler, _translationMap['ProcMsg_Loading']);			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					_initDataXML = responseXML;
					initBuildXML(responseXML);
					addChangeHandlers();
					toggleCheckBoxes();
					populateDropdowns(responseXML);
				}											
			}
		}

		
		,doLookup: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'contractType', _resources.fields['contractType'].getValue());
			var version = _resources.fields['versionNumber'].getValue();
			IFDS.Xml.addSingleNode(dataXML, 'contractVer', version == "" ? '0' : version);
						 					
			DesktopWeb.Ajax.doSmartviewAjax(_classSearchView, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching']);
			
			function responseHandler(success, responseXML)
			{				
				if (IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/Is_GUSURR")=='no'){
				_resources.fields['revPerThd'].disable();
				}
				else{
				_resources.fields['revPerThd'].enable();
				}

				_inquiryXML = responseXML;
				if (success)
				{
					displayAlert(responseXML);
					loadData(responseXML);
					toggleCheckBoxes();
					storePermissions(responseXML);
					updatesFlagStatus(false);
					_self.searchState = true;					
				}
			}
		}
		
		,appendToXml: function(value)
		{
			/** _updateXML is assgined from SEARCH action but be blank while INITIAL; caused a script error **/
			if (_updateXML != null)
			{
				var tempXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']/Detls/Detl[attribCode = '" + data[value] + "']");
				IFDS.Xml.replaceSingleNode(tempXML, 'runMode', 'mod');
				if (value == 'immBenefElig' || value == 'allowNegativeLWA')
				{
					IFDS.Xml.replaceSingleNode(tempXML, 'attribValue', _resources.fields[value].checked ? 'Yes' : 'No');
				}
				else 
				{
					IFDS.Xml.replaceSingleNode(tempXML, 'attribValue', _resources.fields[value].getValue());
				}
				if (IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']/runMode") == null || IFDS.Xml.getNodeValue(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']/runMode") == "")
				{
					var mstrXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']");
					IFDS.Xml.replaceSingleNode(mstrXML, 'runMode', 'mod');
				}	
				updatesFlagStatus(true);				
			}
		}
		
		,appendEWIToXml: function(value, save)
		{
			/** _updateXML is assgined from SEARCH action but be blank while INITIAL; caused a script error **/
			if (_updateXML != null)
			{
				var tempXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']/Detls/Detl[attribCode = '" + data[value] + "']");
				IFDS.Xml.replaceSingleNode(tempXML, 'runMode', 'mod');
				IFDS.Xml.replaceSingleNode(tempXML, save, _resources.fields[value].getValue());
				if (IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']/runMode") == null || IFDS.Xml.getNodeValue(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']/runMode") == "")
				{
					var mstrXML = IFDS.Xml.getNode(_updateXML, "//Mstr[attribType = '" + mstr[value] + "']");
					IFDS.Xml.replaceSingleNode(mstrXML, 'runMode', 'mod');
				}
				updatesFlagStatus(true);				
			}
		}
		
		,setNewReductValue: function()
		{
			newRecNum++;
			return newRecNum;
		}
		
		
		,openHistoricalPopup: function(recType)
		{
			var viewParam = {}
			var title = recType + " - History";
			
			viewParam['auditType'] = 'SegAttribDetl';
			viewParam['searchValue1'] = 'cotAttribMstrId';
			viewParam['searchValue2'] = 'attribCode';
			viewParam['searchValue3'] = 'level';
			
			
			_resources.popups['history'].init(title, 'dtHistoricalInfo', viewParam, true);
			_resources.popups['history'].show();
		}
		
		,openAdminPopup: function(recType)
		{
			var title = null;	
			var xml = null;

			title = recType + " - Admin";

			/** _inquiryXML is assgined from SEARCH action but be blank while INITIAL; caused a script error **/
			if (_inquiryXML != null)
			{
				xml = IFDS.Xml.getNode(_inquiryXML, "//Mstr[attribType = '" + recType + "']");
				var adminData = {};
				adminData['userName'] = IFDS.Xml.getNodeValue(xml, 'userName');
				adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'procDate'));
				adminData['modUser'] = IFDS.Xml.getNodeValue(xml, 'modUser');
				adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'modDate'));
				_resources.popups['admin'].init(title, adminData);
			}
			_resources.popups['admin'].show();
		}			
		
		,clearVersionNumber: function()
		{
			_resources.fields['versionNumber'].setValue("");
			_resources.fields['versionNumber'].clearInvalid();
		}
		
		,populateSearchVersionNumber: function(value)
		{
			var versionNum = IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]");
			
			if (versionNum != null)
			{
				var versionNumValue = IFDS.Xml.getNodeValue(_initDataXML, "//List[@listName = 'ContractVerList_" + value + "' ]/Element/value");
				
				if (versionNumValue == '0')
				{
					_resources.fields['versionNumber'].setDisabled(true);
				}
				else
				{
					_resources.fields['versionNumber'].setDisabled(false);
					_resources.fields['versionNumber'].loadData(versionNum);
	
				}
			}
			
			return versionNumValue == '0';
		}
		
		,handleCheckBoxes: function()
		{
			toggleCheckBoxes();
		}
		
		,updateActionButtons: function(grid)
		{
			var selectedRecord = _resources.grids[grid].getSelectedRecord();
			if (selectedRecord)
			{
				if (selectedRecord.data['runMode'] == this.ADD)
				{
					if (_permissionsMap[this.MOD])
					{
						_resources.grids[grid].enableButton('modBtn');
					}
					if (_permissionsMap[this.DEL])	
						_resources.grids[grid].enableButton('delBtn');
				}
				else
				{
					if (_permissionsMap[this.MOD])
					{
						_resources.grids[grid].enableButton('modBtn');
					}
					else
					{
						_resources.grids[grid].disableButton('modBtn');
					}
					
					if (_permissionsMap[this.DEL])		
					{
						_resources.grids[grid].enableButton('delBtn');
					}
					else
					{
						_resources.grids[grid].disableButton('delBtn');
					}
				}
			}
			else
			{
				_resources.grids[grid].disableButton('modBtn');
				_resources.grids[grid].disableButton('delBtn');
			}
		}	
		
		,openActionPopup: function(action, grid, popup)
		{
			if (action == this.ADD)
			{
				_resources.grids[grid].clearSelectedRecord();
			}
			_resources.popups[popup].init(action);
			_resources.popups[popup].show();
		}
		
		,closeActionPopup: function(popup)
		{
			_resources.popups[popup].hide();
		}
		
		,savePopup: function(action, data, grid)
		{
			var success = true;
			if (action == this.ADD)
			{
				_resources.grids[grid].addRecord(data);
				_resources.grids[grid].selectLastRecord();
				addNewGridXml(grid, data);
				updatesFlagStatus(true);				
			}
			else
			{
				// annoying case where mod/del a brand new record
				if (isNewRecord(_resources.grids[grid].getSelectedRecord()))
				{
					if (action == this.DEL)
					{
						var tempXML = IFDS.Xml.getNode(_updateXML, "//Reduction[num = '" + _resources.grids[grid].getSelectedRecord().data['num'] + "']");
						if (tempXML != null)
						{
							IFDS.Xml.deleteNode(tempXML);
						}
						_resources.grids[grid].removeSelectedRecord();
						updatesFlagStatus(false);						
					}
					else
					{
						data['runMode'] = this.ADD
						_resources.grids[grid].updateSelectedRecord(data);
						appendToGridXml (grid, action);
						updatesFlagStatus(true);						
					}				
				}
				else if (action == this.DEL)
				{
					appendToGridXml (grid, action);
					_resources.grids[grid].updateSelectedRecord(data);
					_self.updateActionButtons(grid);
					updatesFlagStatus(true);					
				}
				else
				{
					_resources.grids[grid].updateSelectedRecord(data);
					_self.updateActionButtons(grid);
					appendToGridXml (grid, action);
					updatesFlagStatus(true);					
				}
			}
			this.updatesFlag = (getUpdatedRecordCount(grid) > 0);	
			if (action == this.DEL)
				_resources.grids[grid].selectFirstRecord();
			return success;			
		}
		
		,callUpdateValidate: function()
		{
			return updateValidate();
		}
		
		,validateSearchCriteria: function()	
		{
			return _resources.fields['contractType'].isValid() 
				|| _resources.fields['versionNumber'].isValid();
		}
		
		,callupdatesFlagStatus: function (confirm)
		{
			updatesFlagStatus(confirm);
		}		
		
		,doUpdate: function()
		{
			var updateStatus = null;										
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXml(), responseHandler, null);
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{					
					updateStatus = DesktopWeb._FAIL
				}
			}
			return updateStatus;
		}	 		
	}	
}	