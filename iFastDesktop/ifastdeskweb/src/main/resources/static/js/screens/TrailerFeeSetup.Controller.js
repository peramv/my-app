/*********************************************************************************************
 * @file	TrailerFeeSetup.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for TrailerFeeSetup screen 
 *********************************************************************************************/
/*
 *  History : 
 *
 *  09 Oct 2013 G. Thawornwachirakun P0217718 T54332
 *					 DFT0022359: Fix status of scale-detl when add and then modify data
 *						, mode must be add.
 *					 DFT0023048: Revert code to be able to modify fields
 *						[Account level] Fund Group, Fund, and Class are disabled.
 *						[System level and BrokerBranceSlsRep] Fund Group, Fund, Class 
 *							, broker, branch, and slsrep fields are disabled.
 *
 *  01 Nov 2013 G. Thawornwachirakun P0217718 T54434
 *					 DFT0023321: When user input broker, branch, slsrep, the MaxFee 
 *											will be gray-out.
 *					 DFT0023316: Change dateformat display follows dateFormatDisplay
 *
 *  11 Nov 2013 G. Thawornwachirakun P0217718 T54441
 *           DFT0023571: Fix Front to auto populate to model 
 *               when user input Fund-Class or Fund Group; and gray-out model
 *               when user input broker,  branch,or slsrep
 *
 *  27 Nov 2013 G. Thawornwachirakun P0217718 T54442
 *           DFT0024910 : Fix DateField to not auto rotate date by system.
 *           DFT0024880 : StopDate column is hidden in account level
 *
 *  20 Dec 2013 G. Thawornwachirakun P0217718 DFT0026649 T54632 
 *           Data in Trailer Fee Detail must not be reset 
 *              when user does not change its model.
 *
 *  23 Dec 2013 G. Thawornwachirakun P0217718 DFT0026749 T54640 
 *           Override Field is incorrect default value and it should be disabled
 *              on BBR Overriden level.
 */
 
 
DesktopWeb.ScreenController = function(){
		
	// PRIVATE VARIABLES *************************************	
	var _ADD = 'add'
	var _MOD = 'modify'
	var _DEL = 'delete';
	
	var _resources = null;
	var _self = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
		
	var _initView = "dtTrailerFeeSetupInit";
	var _reloadView = "dtTrailerFeeSetReload";
	var _validateView = "dtTrailerFeeSetupProc";
	var _updateView = "dtTrailerFeeSetupUpd";
	var _feeParmHistoryView = "dtHistTrlFee";
	var _feeParmDetailHistoryView = "dtHistTrlFeeDetl";
	var _scaleDetailHistoryView = "dtHistoricalInfo";
	var _grandfatherInitView = "dtTrailerFeeGFInit";
	
	var _nextStartRecNum = null;
	var _requestRecNum = 25;
	
	var _defaultValues = {};	
	var _trailerFeesXML = null;
	var _selectedFeeParmIndex = null;
	var _selectedFeeParmDetailIndex = null;
	var _selectedScaleDetailIndex = null;
	var _grandFatherXMLOptions = null;
	var _accountLevel = false;
	var _rulesList = null;

	var _brokerBranchRepOverride = false;
	var _allowBranch = false;
	var _lastFeeID   =0;
	var _currentModel="";
	var _isModelChanged = false;
	var _initDataXML = null;
	
	
	// PRIVATE METHODS ****************************************	
	function updatePopupDropdowns(xml)
	{				
		_resources.popups['feeParms'].getField('fundGroup').getStore().loadData(Ext.DomQuery.selectNode("List[listName=FundGroupOptions]", xml));
		_resources.popups['feeParms'].getField('aggFundGroup').getStore().loadData(Ext.DomQuery.selectNode("List[listName=AggFundGroupOptions]", xml));	
		_resources.popups['feeParms'].getField('distribChannel').getStore().loadData(Ext.DomQuery.selectNode("List[listName=DistribChannelOptions]", xml));	
		_resources.popups['feeParms'].getField('model').getStore().loadData(Ext.DomQuery.selectNode("TrailerFeeModels", xml));
		if (!_accountLevel)
		{		
			_resources.popups['feeParms'].getField('OverAllowed').getStore().loadData(Ext.DomQuery.selectNode("List[listName=OverrideList]", xml));
		}
		_resources.popups['feeParmDetails'].getField('SplitBy').getStore().loadData(Ext.DomQuery.selectNode("List[listName=SplitByOptions]", xml));
		_resources.popups['feeParmDetails'].getField('AssetType').getStore().loadData(Ext.DomQuery.selectNode("List[listName=AssetTypeOptions]", xml));
		_resources.popups['feeParmDetails'].getField('FeeType').getStore().loadData(Ext.DomQuery.selectNode("List[listName=FeeTypeOptions]", xml));
		
	}
	
	function hideAllSearchFields()
	{
		_resources.fields['searchFundGroup'].hideField();
		_resources.fields['searchFundCode'].hideField();
		_resources.fields['searchClassCode'].hideField();
		_resources.fields['searchBrokerCode'].hideField();
		_resources.fields['searchBranchCode'].hideField();
		_resources.fields['searchSlsRepCode'].hideField();
		_resources.fields['searchDistribChannel'].hideField();
	}
	
	function setDefaultValues(xml)
	{
		
		_defaultValues['maxFee']            = '00.0000';
		_defaultValues['effDate']           = DesktopWeb.Util.getDateDisplayValue(Ext.DomQuery.selectValue('DatesDefaults EffectDate', xml));
		_defaultValues['stopDate']          = DesktopWeb.Util.getDateDisplayValue(Ext.DomQuery.selectValue('DatesDefaults StopDate', xml));
		_defaultValues['distribChannelApp'] = Ext.DomQuery.selectValue('DistribChannelApp', xml);
		
		_defaultValues['brokerCode']        = "";
		_defaultValues['branchCode']        = "";
		_defaultValues['slsRepCode']        = "";
		_defaultValues['model']             = ""; //Ext.DomQuery.selectValue('model', xml);
		_defaultValues['fundGroup']         = ""; //Ext.DomQuery.selectValue('fundGroup', xml);
		_defaultValues['fundCode']          = "";
		_defaultValues['classCode']         = "";
		_defaultValues['aggFundGroup']      = ""; //Ext.DomQuery.selectValue('aggFundGroup', xml);
		_defaultValues['OverAllowed']       = ""; //Ext.DomQuery.selectValue('OverAllowed', xml);
		
	}
	
	function storeRuleList(xml)
	{
		_rulesList = Ext.DomQuery.selectNode("List[listName=RuleOptions]", xml)
	}
	
	function setTrailerFeesXML(xml, more)
	{
		if (more)
		{
			var xmlStr = "<TrailerFee>";
			var feeParmXMLNodes = Ext.DomQuery.jsSelect('FeeParms', _trailerFeesXML);
			for (var i = 0; i < feeParmXMLNodes.length; i++)
			{
				xmlStr += IFDS.Xml.serialize(feeParmXMLNodes[i]);
			}
			var feeParmXMLNodes = Ext.DomQuery.jsSelect('FeeParms', xml);
			for (var i = 0; i < feeParmXMLNodes.length; i++)
			{
				xmlStr += IFDS.Xml.serialize(feeParmXMLNodes[i]);
			}
			xmlStr += "</TrailerFee>"								
			_trailerFeesXML = IFDS.Xml.stringToXML(xmlStr);
		}
		else
		{
			_trailerFeesXML = Ext.DomQuery.selectNode("TrailerFee", xml);
		}
		
		var feeParmXMLs = IFDS.Xml.getNodes(_trailerFeesXML, 'FeeParms');
		var feeParmDetailXMLs = null;
		var ruleXMLs = null;
		var rulesString = null;
		Ext.each(feeParmXMLs, function(feeParmXML){
			rulesString = "";
			ruleXMLs = IFDS.Xml.getNodes(feeParmXML, 'FeeParmsRules');
			Ext.each(ruleXMLs, function(ruleXML){
				rulesString += IFDS.Xml.getNodeValue(ruleXML, 'ruleCode') + " - " + IFDS.Xml.getNodeValue(ruleXML, 'ruleDesc') + " ,";				
			});
			rulesString = rulesString.replace(/(^,)|(,$)/g, ""); 
			IFDS.Xml.addSingleNode(feeParmXML, 'trailerRulesDisp', rulesString);
			
			feeParmDetailXMLs = IFDS.Xml.getNodes(feeParmXML, 'FeeParmsDetail');
			Ext.each(feeParmDetailXMLs, function(feeParmDetailXML){
				if(Ext.DomQuery.selectValue('SplitBy', feeParmDetailXML) != 'DSC')
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'AssetType'), 'All');
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'AssetTypeDesc'), 'All');
				}
			});
		});
		
		displayFeeParms(_trailerFeesXML, 0);		
	}
	
	function displayFeeParms(xml, index)
	{
		_resources.grids['feeParms'].getStore().loadData(xml);
		if (index != null)
		{ 
			_resources.grids['feeParms'].getSelectionModel().selectRow(index);
			_resources.grids['feeParms'].getView().focusRow(index)			
		}
	}
	
	function displayFeeParmDetails(xml, action)
	{
		var gridFeeParmDetls = _resources.grids['feeParmDetails'];
		var index = gridFeeParmDetls.getRecordIndex(gridFeeParmDetls.getSelectedRecord());
		
		gridFeeParmDetls.getStore().loadData(xml);		
		if(action == _MOD || action == _DEL)
		{
			if(index < gridFeeParmDetls.getStore().getCount())
			{
				gridFeeParmDetls.setSelectedRecord(index);
			}
			else
			{
				gridFeeParmDetls.selectLastRecord();
			}
		}
		else if(action == _ADD)
		{
			gridFeeParmDetls.selectLastRecord();
		}
	}
	
	function displayScaleDetails(xml, action)
	{	
		var gridScaleDetails = _resources.grids['scaleDetails'];
		var index = gridScaleDetails.getRecordIndex(gridScaleDetails.getSelectedRecord());
		
		displayFeeParmDetails(xml, _MOD);	
		
		if(action == _MOD || action == _DEL)
		{
			if(index < gridScaleDetails.getStore().getCount())
			{
				gridScaleDetails.setSelectedRecord(index);
			}
			else
			{
				gridScaleDetails.selectLastRecord();
			}
		}
		else if (action == _ADD)
		{
			gridScaleDetails.selectLastRecord();
		}
	}
	
	function setFeeParmAction(feeParmXML, popupAction)
	{	
		var actionNode = Ext.DomQuery.selectNode('/action', feeParmXML);		
		if (actionNode == null)
		{
			IFDS.Xml.addSingleNode(feeParmXML, 'action', popupAction);
		}
		else
		{
			var curAction = Ext.DomQuery.selectValue('/action', feeParmXML);
			// special case where modify a newly added record
			if (popupAction == _MOD && curAction == _ADD)
			{
				IFDS.Xml.setNodeValue(actionNode, _ADD);			
			}
			else
			{
				IFDS.Xml.setNodeValue(actionNode, popupAction);
			}
		}		
	}
	
	function setFeeParmRuleAction (feeParmXML, feeParmRuleXML, popupAction)
	{
		setFeeParmAction(feeParmXML, _MOD);
		var actionNode = Ext.DomQuery.selectNode('ruleAction', feeParmRuleXML);	
		if (actionNode == null)
		{
			IFDS.Xml.addSingleNode(feeParmRuleXML, 'ruleAction', popupAction);
		}
		else
		{
			IFDS.Xml.setNodeValue(actionNode, popupAction);
		}
	}
	
	function setFeeParmDetailAction(feeParmXML, feeParmDetailXML, popupAction)
	{		
		setFeeParmAction(feeParmXML, _MOD);
		var actionNode = Ext.DomQuery.selectNode('action', feeParmDetailXML);		
		if (actionNode == null)
		{
			IFDS.Xml.addSingleNode(feeParmDetailXML, 'action', popupAction);
		}
		// if action already set, then won't ever change it		
	}
	
	function setScaleDetailAction(feeParmXML, feeParmDetailXML, scaleDetailXML, popupAction)
	{
		setFeeParmDetailAction(feeParmXML, feeParmDetailXML, _MOD);
		var actionNode = Ext.DomQuery.selectNode('action', scaleDetailXML);		
		if (actionNode == null)
		{
			IFDS.Xml.addSingleNode(scaleDetailXML, 'action', popupAction);
		}
		else
		{
			var curAction = Ext.DomQuery.selectValue('action', scaleDetailXML);
			// special case where modify a newly added record
			if (popupAction == _MOD && curAction == _ADD)
			{
				IFDS.Xml.setNodeValue(actionNode, _ADD);				
			}
			else
			{
				IFDS.Xml.setNodeValue(actionNode, popupAction);
			}
		}		
	}
	
	function addFeeParm(tfXML, popup)
	{
	  var tmpFeeID      = _self.getNextTmpFeeID(); 
		var newFeeParmXML = IFDS.Xml.addSingleNode(tfXML, 'FeeParms');							
		setFeeParmAction(newFeeParmXML, _ADD);											
		IFDS.Xml.addSingleNode(newFeeParmXML, 'fundGroup', popup.getField('fundGroup').getValue());				
		IFDS.Xml.addSingleNode(newFeeParmXML, 'fundCode', popup.getField('fundCode').getValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'classCode', popup.getField('classCode').getValue());		
		IFDS.Xml.addSingleNode(newFeeParmXML, 'effDate', popup.getField('effDate').getSMVDateString());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'stopDate', popup.getField('stopDate').getSMVDateString());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'aggFundGroup', popup.getField('aggFundGroup').getValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'distribChannel', popup.getField('distribChannel').getValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'distribChannelDesc', popup.getField('distribChannel').getRawValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'brokerCode', popup.getField('brokerCode').getRawValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'branchCode', popup.getField('branchCode').getRawValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'slsRepCode', popup.getField('slsRepCode').getRawValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'model', popup.getField('model').getRawValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'feeID', tmpFeeID); 
		

		var trailerRecords = _resources.selectors['trailerRules'].getSelectedRecords();
		var rulesString = "";
		Ext.each(trailerRecords, function(record){
			rulesString += record.get('code') + " - " + record.get('value') + " ,";	
			newRule = IFDS.Xml.newDocument("FeeParmsRules");			
			IFDS.Xml.addSingleNode(newRule, 'linkLevel', "01");
			IFDS.Xml.addSingleNode(newRule, 'linkUUID');
			IFDS.Xml.addSingleNode(newRule, 'ruleCode', record.get('code'));
			IFDS.Xml.addSingleNode(newRule, 'ruleDesc', record.get('value'));
			setFeeParmRuleAction(newFeeParmXML, newRule, _ADD);	
			IFDS.Xml.appendNode(newFeeParmXML, newRule);	
		});
		IFDS.Xml.addSingleNode(newFeeParmXML, 'trailerRulesDisp', rulesString.replace(/(^,)|(,$)/g, ""));
		
		var selectedModel = popup.getField('model').getSelectedRecord();
		IFDS.Xml.addSingleNode(newFeeParmXML, 'AvgType', (selectedModel!=null?selectedModel.data['AvgType']:''));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'BalAsOf', (selectedModel!=null?selectedModel.data['BalAsOf']:''));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'BalType', (selectedModel!=null?selectedModel.data['BalType']:''));
		
		if (!_accountLevel)
		{		
			IFDS.Xml.addSingleNode(newFeeParmXML, 'maxFee', popup.getField('maxFee').getValue());
			if (popup.getField('OverAllowed').getValue() != null && popup.getField('OverAllowed').getValue() != undefined)
			  IFDS.Xml.addSingleNode(newFeeParmXML, 'OverAllowed', popup.getField('OverAllowed').getValue());
				
			if (popup.getField('OverAllowed').getValueDesc() != null && popup.getField('OverAllowed').getValueDesc() != undefined)
				IFDS.Xml.addSingleNode(newFeeParmXML, 'OverAllowedDesc', popup.getField('OverAllowed').getValueDesc());
			
		}		
				
		return newFeeParmXML;
	}
	
	function modFeeParm(feeParmXML, popup)
	{		
		var modFeeParmXML = feeParmXML;
		setFeeParmAction(feeParmXML, _MOD);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'fundGroup'), popup.getField('fundGroup').getValue());
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'fundCode'), popup.getField('fundCode').getValue());
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'classCode'), popup.getField('classCode').getValue());		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'effDate'), popup.getField('effDate').getSMVDateString());
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'stopDate'), popup.getField('stopDate').getSMVDateString());
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'aggFundGroup'), popup.getField('aggFundGroup').getValue());	
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'distribChannel'), popup.getField('distribChannel').getValue());	
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'distribChannelDesc'), popup.getField('distribChannel').getRawValue());			
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'brokerCode'), popup.getField('brokerCode').getValue());		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'branchCode'), popup.getField('branchCode').getValue());			
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'slsRepCode'), popup.getField('slsRepCode').getValue());
		
		if(IFDS.Xml.getNode(modFeeParmXML, 'model') == null)
		{
			IFDS.Xml.addSingleNode(modFeeParmXML, 'model', popup.getField('model').getValue());
		}
		else
		{
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'model'), popup.getField('model').getValue());
		}
		if(IFDS.Xml.getNode(modFeeParmXML, '//FeeParmsDetail/ModelID') !=null)
		{
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, '//FeeParmsDetail/ModelID'), popup.getField('model').getValue());
		}
		
		var trailerRecords = _resources.selectors['trailerRules'].getSelectedRecords();
		var ruleXMLs = IFDS.Xml.getNodes(modFeeParmXML, 'FeeParmsRules');
	
		var rulesString = "";
		var existfound = null;
		var updatefound = null;
		var existflag = null;
		
		var elmXMLArr = IFDS.Xml.getNodes(_rulesList, "Element");		
		Ext.each(elmXMLArr, function(elmXML){				
			updatefound = false; 
			rulesString = "";
			Ext.each(trailerRecords, function(record){
				if (record.get('code') == IFDS.Xml.getNodeValue(elmXML, "code"))
				{
					updatefound = true;
				}
				rulesString += record.get('code') + " - " + record.get('value') + " ,";
			});
			
			existfound = false;
			existflag = "";
			Ext.each(ruleXMLs, function(ruleXML){
				if (IFDS.Xml.getNodeValue(ruleXML, 'ruleCode') == IFDS.Xml.getNodeValue(elmXML, "code"))
				{
					existflag = (IFDS.Xml.getNodeValue(ruleXML, 'ruleAction') ?  IFDS.Xml.getNodeValue(ruleXML, 'ruleAction') : "");
					existfound = true;
					if (existflag == _DEL) 
					{
						if (updatefound) 
						{
							setFeeParmRuleAction(modFeeParmXML, ruleXML, _MOD);
						}
					}
					else
					{
						if (!updatefound) 
						{
							setFeeParmRuleAction(modFeeParmXML, ruleXML, _DEL); //existfound && !updatefound ==> deleted
						}
					}
				}
			});
			
			if (!existfound && updatefound && existflag != _DEL) // ==> added
			{
				newRule = IFDS.Xml.newDocument("FeeParmsRules");	
				IFDS.Xml.addSingleNode(newRule, 'linkLevel', "01");
				IFDS.Xml.addSingleNode(newRule, 'linkUUID');
				IFDS.Xml.addSingleNode(newRule, 'ruleCode', IFDS.Xml.getNodeValue(elmXML, "code"));
				IFDS.Xml.addSingleNode(newRule, 'ruleDesc', IFDS.Xml.getNodeValue(elmXML, "value"));
				setFeeParmRuleAction(modFeeParmXML, newRule, _ADD);	
				IFDS.Xml.appendNode(modFeeParmXML, newRule);		
			}
			
		});
		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'trailerRulesDisp'), rulesString.replace(/(^,)|(,$)/g, ""));			
		
		var selectedModel = popup.getField('model').getSelectedRecord();
		if (IFDS.Xml.getNode(modFeeParmXML, 'AvgType')) 
		{ 
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'AvgType'), (selectedModel!=null?selectedModel.data['AvgType']:'')); 
		}
		else 
		{ 
			IFDS.Xml.addSingleNode(modFeeParmXML, 'AvgType', (selectedModel!=null?selectedModel.data['AvgType']:'')); 
		}
		if (IFDS.Xml.getNode(modFeeParmXML, 'BalAsOf')) 
		{ 
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'BalAsOf'), (selectedModel!=null?selectedModel.data['BalAsOf']:'')); 
		}
		else 
		{ 
			IFDS.Xml.addSingleNode(modFeeParmXML, 'BalAsOf', (selectedModel!=null?selectedModel.data['BalAsOf']:'')); 
		}
		if (IFDS.Xml.getNode(modFeeParmXML, 'BalType')) 
		{ 
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'BalType'), (selectedModel!=null?selectedModel.data['BalType']:'')); 
		}
		else 
		{ 
			IFDS.Xml.addSingleNode(modFeeParmXML, 'BalType', (selectedModel!=null?selectedModel.data['BalType']:'')); 
		}		
		
		if (!_accountLevel)
		{		
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'maxFee', modFeeParmXML), popup.getField('maxFee').getValue());	
			if (popup.getField('OverAllowed').getValue() != null && popup.getField('OverAllowed').getValue() != undefined)
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'OverAllowed'), popup.getField('OverAllowed').getValue());
						
			if (popup.getField('OverAllowed').getValueDesc() != null && popup.getField('OverAllowed').getValueDesc() != undefined)
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(modFeeParmXML, 'OverAllowedDesc'), popup.getField('OverAllowed').getValueDesc());
		}
		return modFeeParmXML;
	}
	
	function delFeeParm(tfXML, feeParmXML)
	{		
		var delFeeParmXML = feeParmXML;
		if (Ext.DomQuery.selectValue('action', delFeeParmXML) == _ADD)
		{
			delFeeParmXML.parentNode.removeChild(delFeeParmXML);
			delFeeParmXML = null;			
		}
		else
		{
			setFeeParmAction(feeParmXML, _DEL);	
		}		
		return delFeeParmXML;		
	}
	
	function addFeeParmDetails(feeParmXML, feeParamAction)
	{		
		doGrandFatherLookup(feeParmXML, responseCallback);
		function responseCallback(success, responseXML)
		{   
			if (success)
			{				
				var grandFatherXMLOptions = Ext.DomQuery.jsSelect("GrandFatherEnd", responseXML);				
				for( var i = 0; i < grandFatherXMLOptions.length; i++)
				{
					var newFeeParmDetailXML = IFDS.Xml.addSingleNode(feeParmXML, 'FeeParmsDetail');
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'action', _ADD);
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'GrandFthrEnd', Ext.DomQuery.selectValue('grandFthrEnd', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'FundProcDatesID', Ext.DomQuery.selectValue('fundProcDatesID', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'AvgType', Ext.DomQuery.selectValue('AvgType', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'AvgTypeDesc', Ext.DomQuery.selectValue('AvgTypeDesc', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'BalAsOf', Ext.DomQuery.selectValue('BalAsOf', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'BalAsOfDesc', Ext.DomQuery.selectValue('BalAsOfDesc', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'BalType', Ext.DomQuery.selectValue('BalType', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'BalTypeDesc', Ext.DomQuery.selectValue('BalTypeDesc', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'SplitBy', Ext.DomQuery.selectValue('SplitBy', grandFatherXMLOptions[i]));					
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'SplitByDesc', Ext.DomQuery.selectValue('SplitByDesc', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'AssetType', Ext.DomQuery.selectValue('AssetType', grandFatherXMLOptions[i]));					
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'AssetTypeDesc', Ext.DomQuery.selectValue('AssetTypeDesc', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'FeeType', Ext.DomQuery.selectValue('FeeType', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'FeeTypeDesc', Ext.DomQuery.selectValue('FeeTypeDesc', grandFatherXMLOptions[i]));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'FeeRate', Ext.DomQuery.selectValue('FeeRate', grandFatherXMLOptions[i]));					
					
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'ModelID', Ext.DomQuery.selectValue( 'model', feeParmXML));
					IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'model', Ext.DomQuery.selectValue('model', feeParmXML));

					
					var scaleDetailXMLNodes = Ext.DomQuery.jsSelect('scaleDetail', grandFatherXMLOptions[i]);
					for (var j = 0; j < scaleDetailXMLNodes.length; j++)
					{						
						var newScaleDetailXML = IFDS.Xml.addSingleNode(newFeeParmDetailXML, 'scaleDetail');
						IFDS.Xml.addSingleNode(newScaleDetailXML, 'action', _ADD);
						IFDS.Xml.addSingleNode(newScaleDetailXML, 'lowBand', Ext.DomQuery.selectValue('lowBand', scaleDetailXMLNodes[j]));
						IFDS.Xml.addSingleNode(newScaleDetailXML, 'uprBand', Ext.DomQuery.selectValue('uprBand', scaleDetailXMLNodes[j]));
						IFDS.Xml.addSingleNode(newScaleDetailXML, 'rate', Ext.DomQuery.selectValue('rate', scaleDetailXMLNodes[j]));
					}
				}
						
				if (feeParamAction == _ADD)
					displayFeeParms(_trailerFeesXML, Ext.DomQuery.jsSelect("FeeParms", _trailerFeesXML).length - 1);
				else
					displayFeeParms(_trailerFeesXML, _selectedFeeParmIndex - 1);
			}
		}
	}
	
	function doGrandFatherLookup(feeParmXML, callbackFn)
	{		
		var viewParamXML = IFDS.Xml.newDocument('data');
		var fundGroup = (Ext.DomQuery.selectValue('fundGroup', feeParmXML) ? Ext.DomQuery.selectValue('fundGroup', feeParmXML) : ""); 				
		if (fundGroup != null && fundGroup != "")
		{
			IFDS.Xml.addSingleNode(viewParamXML, 'searchValue', 'FundGroup');		
		}
		else
		{
			IFDS.Xml.addSingleNode(viewParamXML, 'searchValue', 'FundClass');			
		}
		
		IFDS.Xml.addSingleNode(viewParamXML, 'searchFundGroup', fundGroup);
		IFDS.Xml.addSingleNode(viewParamXML, 'searchFundCode', 
				(Ext.DomQuery.selectValue('fundCode', feeParmXML) ? Ext.DomQuery.selectValue('fundCode', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'searchClassCode', 
				(Ext.DomQuery.selectValue('classCode', feeParmXML) ? Ext.DomQuery.selectValue('classCode', feeParmXML) : ""));
				
		IFDS.Xml.addSingleNode(viewParamXML, 'searchBrokerCode', 
			(Ext.DomQuery.selectValue('brokerCode', feeParmXML) ? Ext.DomQuery.selectValue('brokerCode', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'searchBranchCode', 
			(Ext.DomQuery.selectValue('branchCode', feeParmXML) ? Ext.DomQuery.selectValue('branchCode', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'searchSlsRepCode', 
			(Ext.DomQuery.selectValue('slsRepCode', feeParmXML) ? Ext.DomQuery.selectValue('slsRepCode', feeParmXML) : ""));
			
		IFDS.Xml.addSingleNode(viewParamXML, 'effDate', 
			(Ext.DomQuery.selectValue('effDate', feeParmXML) ? Ext.DomQuery.selectValue('effDate', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'stopDate', 
			(Ext.DomQuery.selectValue('stopDate', feeParmXML) ? Ext.DomQuery.selectValue('stopDate', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'avgType', 
			(Ext.DomQuery.selectValue('AvgType', feeParmXML) ? Ext.DomQuery.selectValue('AvgType', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'balAsOf', 
			(Ext.DomQuery.selectValue('BalAsOf', feeParmXML) ? Ext.DomQuery.selectValue('BalAsOf', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'balType', 
			(Ext.DomQuery.selectValue('BalType', feeParmXML) ? Ext.DomQuery.selectValue('BalType', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'distribChannel', 
			(Ext.DomQuery.selectValue('distribChannel', feeParmXML) ? Ext.DomQuery.selectValue('distribChannel', feeParmXML) : ""));
		IFDS.Xml.addSingleNode(viewParamXML, 'searchAccountNum', 
			(DesktopWeb._SCREEN_PARAM_MAP['AccountNum'].toLowerCase() == 'all' ? '0' : DesktopWeb._SCREEN_PARAM_MAP['AccountNum']));

			
		DesktopWeb.Ajax.doSmartviewAjax(_grandfatherInitView, null, viewParamXML, callbackFn);
	}
	
	function addFeeParmDetailXml(feeParmXML, feeParmDetlXML, popup)
	{		
		var newFeeParmXML = IFDS.Xml.addSingleNode(feeParmXML, 'FeeParmsDetail');
		
		setFeeParmDetailAction(feeParmXML, newFeeParmXML, _ADD);
		
		IFDS.Xml.addSingleNode(newFeeParmXML, 'SplitBy', popup.getField('SplitBy').getValue());						
		IFDS.Xml.addSingleNode(newFeeParmXML, 'SplitByDesc', popup.getField('SplitBy').getValueDesc());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'AssetType', popup.getField('AssetType').getValue());						
		IFDS.Xml.addSingleNode(newFeeParmXML, 'AssetTypeDesc', popup.getField('AssetType').getValueDesc());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'FeeType', popup.getField('FeeType').getValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'FeeTypeDesc', popup.getField('FeeType').getValueDesc());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'FeeRate', popup.getField('FeeRate').getValue());
		
		IFDS.Xml.addSingleNode(newFeeParmXML, 'GrandFthrEnd', Ext.DomQuery.selectValue('GrandFthrEnd', feeParmDetlXML));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'AvgType', Ext.DomQuery.selectValue('AvgType', feeParmDetlXML));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'AvgTypeDesc', Ext.DomQuery.selectValue('AvgTypeDesc', feeParmDetlXML));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'BalAsOf', Ext.DomQuery.selectValue('BalAsOf', feeParmDetlXML));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'BalAsOfDesc', Ext.DomQuery.selectValue('BalAsOfDesc', feeParmDetlXML));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'BalType', Ext.DomQuery.selectValue('BalType', feeParmDetlXML));
		IFDS.Xml.addSingleNode(newFeeParmXML, 'BalTypeDesc', Ext.DomQuery.selectValue('BalTypeDesc', feeParmDetlXML));
		
		
		return feeParmXML;
	}
	
	function modFeeParmDetail(feeParmXML, feeParmDetailXML, popup)
	{		
		setFeeParmDetailAction(feeParmXML, feeParmDetailXML, _MOD);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'SplitBy'), popup.getField('SplitBy').getValue());						
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'SplitByDesc'), popup.getField('SplitBy').getValueDesc());

		if(Ext.DomQuery.selectValue('SplitBy', feeParmDetailXML) == 'DSC')
		{
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'AssetType'), popup.getField('AssetType').getValue());						
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'AssetTypeDesc'), popup.getField('AssetType').getValueDesc());
		}
		else
		{
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'AssetType'), 'All');						
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'AssetTypeDesc'), 'All');
		}
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'FeeType'), popup.getField('FeeType').getValue());
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'FeeTypeDesc'), popup.getField('FeeType').getValueDesc());
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(feeParmDetailXML, 'FeeRate'), popup.getField('FeeRate').getValue());
		
		return feeParmXML;
	}
	
	function addScaleDetail(feeParmXML, feeParmDetailXML, popup)
	{
		var newScaleDetailXML = IFDS.Xml.addSingleNode(feeParmDetailXML, 'scaleDetail');	
		setScaleDetailAction(feeParmXML, feeParmDetailXML, newScaleDetailXML, _ADD);			
		IFDS.Xml.addSingleNode(newScaleDetailXML, 'lowBand', popup.getField('lowBand').getValue());
		IFDS.Xml.addSingleNode(newScaleDetailXML, 'uprBand', popup.getField('uprBand').getValue());
		IFDS.Xml.addSingleNode(newScaleDetailXML, 'rate', popup.getField('rate').getValue());
		return feeParmXML;
	}
	
	function modScaleDetail(feeParmXML, feeParmDetailXML, scaleDetailXML, popup)
	{
		var updatedScaleDetailXML = scaleDetailXML;
		setScaleDetailAction(feeParmXML, feeParmDetailXML, updatedScaleDetailXML, _MOD);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(updatedScaleDetailXML, 'lowBand'), popup.getField('lowBand').getValue());						
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(updatedScaleDetailXML, 'uprBand'), popup.getField('uprBand').getValue());
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(updatedScaleDetailXML, 'rate'), popup.getField('rate').getValue());
		return feeParmXML;				
	}
	
	function delScaleDetail(feeParmXML, feeParmDetailXML, scaleDetailXML)
	{
		var delScaleDetailXML = scaleDetailXML;
		var updatedFeeParmXML = null;
		if (Ext.DomQuery.selectValue('action', delScaleDetailXML) == _ADD)
		{
			delScaleDetailXML.parentNode.removeChild(delScaleDetailXML);					
		}
		else
		{
			
			setScaleDetailAction(feeParmXML, feeParmDetailXML, scaleDetailXML, _DEL);
			updatedFeeParmXML = feeParmXML;	
		}		
		
		return updatedFeeParmXML;		
	}
	
	function loadSelector(xml)
	{
		var ruleXMLs;
		var selector;
		var records;
		
		clearSelector();
		selector = _resources.selectors["trailerRules"];
		selector.loadAvailableData(_rulesList);		
		records = selector.availableGrid.getAllRecords();
		
		if (xml) 
		{
			ruleXMLs = IFDS.Xml.getNodes(xml, 'FeeParmsRules');
			Ext.each(ruleXMLs, function(ruleXML){							
				for(var i=0; i<records.length; i++)
				{
					if(IFDS.Xml.getNodeValue(ruleXML, 'ruleCode').toLowerCase() == records[i].get('code').toLowerCase() && IFDS.Xml.getNodeValue(ruleXML, 'ruleAction') != _DEL)
					{
						selector.addToSelected([records[i]]);
						break;
					}					
				}
			});
		}
	}
	
	function clearSelector()
	{
		_resources.selectors["trailerRules"].availableGrid.getStore().removeAll();
		_resources.selectors["trailerRules"].availableGrid.disableAllButtons();
		_resources.selectors["trailerRules"].selectedGrid.getStore().removeAll();
		_resources.selectors["trailerRules"].selectedGrid.disableAllButtons();
	}
	
	function enableDistribChannel()
	{
		if (_defaultValues['distribChannelApp'] == 'yes')
		{
			_resources.popups['feeParms'].getField('distribChannel').enable();
		}
		else
		{
			_resources.popups['feeParms'].getField('distribChannel').disable();
		}
	}
	
	function sendValidation(xml, successCallback, errorCallback)
	{
		IFDS.Xml.addSingleNode(xml, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, xml, responseHandler);
					
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				successCallback();
			}
			else
			{												
				errorCallback();				
			}			
		}
	}
	function storeContextErrors(errorNodes)
	{
		clearContextErrors();
		for (var i = 0; i < errorNodes.length; i++)
		{
			var elementSource = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			var feeParmsStore = _resources.grids['feeParms'].getStore();
			var recordIndex = feeParmsStore.find('feeID', elementSource);

			if(recordIndex!=-1){
				var feeParmsRecord = feeParmsStore.getAt(recordIndex);
				feeParmsRecord.set('errMsg', errMsg);
				feeParmsStore.commitChanges();
			}
		}
	}	
	
	function clearContextErrors()
	{
		var errRecords = _resources.grids['feeParms'].getStore().queryBy(function(record){ return record.get('errMsg') != "" });
		
		for(i = 0; i < errRecords.length; i++)
		{
			errRecords.itemAt(i).set('errMsg', "");
			errRecords.itemAt(i).commit();
		}
	}
	
	
	function clearErrMsg()
	{
		var acctAsscXMLArr = IFDS.Xml.getNodes(_mstrXML, '//AcctFeeModel/AcctFeeModelDetl');
		for (var i = 0; i < acctAsscXMLArr.length; i++)
		{
			if (IFDS.Xml.getNode(acctAsscXMLArr[i], 'errMsg'))		
			{				
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(acctAsscXMLArr[i], 'errMsg'));
			}
		}
	}
	function buildUpdateXML(isValidating)
	{
		var xmlStr = "";
		var feeParmXMLArray = Ext.DomQuery.jsSelect("FeeParms", _trailerFeesXML);
		for (var i = 0; i< feeParmXMLArray.length; i++)
		{			
			if(Ext.DomQuery.selectNode('action', feeParmXMLArray[i]) 
				&& Ext.DomQuery.selectValue('action', feeParmXMLArray[i]) != "" )
			{
				var tmpFeeParamXML=feeParmXMLArray[i];
				IFDS.Xml.addAttribute (tmpFeeParamXML, 'RecordSource', IFDS.Xml.getNodeValue(tmpFeeParamXML, "feeID"));
				xmlStr += IFDS.Xml.serialize(tmpFeeParamXML);
			}
		}
		xmlStr = "<data><accountNum>" 
		         + DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] 
				 + "</accountNum><runMode>"
				 + (isValidating?'validate':'updating')
				 + "</runMode><TrailerFee>" 
				 + xmlStr 
				 + "</TrailerFee></data>";		
		return IFDS.Xml.stringToXML(xmlStr);	
	}
	
	function generateFeeParmsXML(popup)
	{
		var modelXML = IFDS.Xml.newDocument('data');
		var newFeeParmXML = IFDS.Xml.addSingleNode(modelXML, 'FeeParms');							
	
		IFDS.Xml.addSingleNode(newFeeParmXML, 'fundGroup', popup.getField('fundGroup').getValue());				
		IFDS.Xml.addSingleNode(newFeeParmXML, 'fundCode', popup.getField('fundCode').getRawValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'classCode', popup.getField('classCode').getRawValue());		
		IFDS.Xml.addSingleNode(newFeeParmXML, 'effDate', popup.getField('effDate').getSMVDateString());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'stopDate', popup.getField('stopDate').getSMVDateString());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'aggFundGroup', popup.getField('aggFundGroup').getValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'distribChannel', popup.getField('distribChannel').getValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'distribChannelDesc', popup.getField('distribChannel').getRawValue());
		IFDS.Xml.addSingleNode(newFeeParmXML, 'brokerCode', "Dummy");
		IFDS.Xml.addSingleNode(newFeeParmXML, 'model', popup.getField('model').getRawValue());
		
				
		return modelXML;
	}
	
	function getModel()
	{	
		var fundGroup = _resources.popups['feeParms'].getField('fundGroup').getValue();
		var fundCode = _resources.popups['feeParms'].getField('fundCode').getRawValue();
		var classCode = _resources.popups['feeParms'].getField('classCode').getRawValue();
		var beforeModel = _resources.popups['feeParms'].getField('model').getValue();
		
		
		if (fundGroup != "" ||(fundCode != "" &&  classCode != ""))
		{
			var newFeeParmXML = generateFeeParmsXML(_resources.popups['feeParms']);
			
			doGrandFatherLookup(newFeeParmXML, responseCallback);
			function responseCallback(success, responseXML)
			{   
				if (success)
				{				
					var grandFatherXMLOptions = Ext.DomQuery.jsSelect("GrandFatherEnd", responseXML);	
					var modelId  = "";
					
					if (grandFatherXMLOptions.length > 0)
					{
					//ModelID
							modelId = Ext.DomQuery.selectValue('ModelID', grandFatherXMLOptions[0]);
							if (modelId !=  beforeModel)
							{
								_resources.popups['feeParms'].getField('model').setValue(modelId);
								_resources.popups['feeParms'].getField('model').setRawValue(modelId);
							}
					}
					else 
					{			
						if (_resources.popups['feeParms'].getField('brokerCode').getRawValue().trim() != ""
						|| _resources.popups['feeParms'].getField('branchCode').getRawValue().trim() != ""
						|| _resources.popups['feeParms'].getField('slsRepCode').getRawValue().trim() != ""			
						)	{
							_resources.popups['feeParms'].getField('model').reset();
							_resources.popups['feeParms'].getField('model').setValue('');
							_resources.popups['feeParms'].getField('model').setRawValue('');
						} else 
							_resources.popups['feeParms'].getField('model').setValue(beforeModel);
					}
				}
			}
			
			if (_accountLevel)
				_resources.popups['feeParms'].getField('model').disableField();
		}
		else if (_accountLevel)
				_resources.popups['feeParms'].getField('model').enableField();
		
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
			_accountLevel = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'].toLowerCase() != 'all';

			_resources.grids['feeParms'].colModel.setHidden(_resources.grids['feeParms'].colModel.findColumnIndex('distribChannelDesc'), _accountLevel);
			_resources.grids['feeParms'].colModel.setHidden(_resources.grids['feeParms'].colModel.findColumnIndex('maxFee'), _accountLevel);
			
			var initViewXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(initViewXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, initViewXML, responseHandler, "Loading ...");			
			
			var doReloadRef = this.doReload;
			function responseHandler(success, responseXML)
			{	
				if (success)
				{
					_initDataXML = responseXML;
					_resources.fields['searchValue'].getStore().loadData(Ext.DomQuery.selectNode("List[listName=SearchByList]", responseXML));					
					_resources.fields['searchFundGroup'].getStore().loadData(Ext.DomQuery.selectNode("List[listName=FundGroupOptions]", responseXML));	
					_resources.fields['searchDistribChannel'].getStore().loadData(Ext.DomQuery.selectNode("List[listName=DistribChannelOptions]", responseXML));						
					
					_brokerBranchRepOverride = IFDS.Xml.getNodeValue(responseXML,'//brokerBranchRepOverride');
					_allowBranch             = IFDS.Xml.getNodeValue(responseXML,'//allowBranch');
					_lastFeeID               = IFDS.Xml.getNodeValue(responseXML,'//lastFeeID');
					
					
					var tempFlag = Ext.DomQuery.selectValue('brokerApplicable', responseXML);
					_defaultValues['brokerApplicable']    = (tempFlag == undefined || tempFlag == null)	? false : (tempFlag.toLowerCase() == 'yes');

					tempFlag = Ext.DomQuery.selectValue('branchApplicable', responseXML);					
					_defaultValues['branchApplicable']    = (tempFlag == undefined || tempFlag == null)	? false : (tempFlag.toLowerCase() == 'yes');
					
					tempFlag = Ext.DomQuery.selectValue('salesRepApplicable', responseXML);
					_defaultValues['salesRepApplicable']  = (tempFlag == undefined || tempFlag == null)	? false : (tempFlag.toLowerCase() == 'yes');
					
					doReloadRef(false);    
				}								
			}
			this.clearGrid('feeParms');												
		}
		
		,isAccountLevel: function()
		{
			return _accountLevel;
		}
		
		,isBrokerBranchRepOverride: function()
		{
			_brokerBranchRepOverride= (_brokerBranchRepOverride==undefined) ? '' : _brokerBranchRepOverride;
			_brokerBranchRepOverride=_brokerBranchRepOverride.replace(/^\s+|\s+$/g,'');
			_brokerBranchRepOverride=_brokerBranchRepOverride.toLowerCase();
			return (_brokerBranchRepOverride=='yes');
		}
		,isNewRecord: function()
		{
			return _resources.grids['feeParms'].getSelectedRecord().data['action'] == _ADD;
		}
		,isAllowBranch: function()
		{
			_allowBranch= (_allowBranch==undefined) ? '' : _allowBranch;
			_allowBranch=_allowBranch.replace(/^\s+|\s+$/g,'');
			_allowBranch=_allowBranch.toLowerCase();
			return (_allowBranch=='yes');
		}
		,getNextTmpFeeID:function()
		{
			return _lastFeeID++;
		}
		,getListValueDesc: function(listName, value)
		{
			var valueDesc = null;
			valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "*/List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");
			if (valueDesc == null || valueDesc == "")
			{
				valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "*/List[@id = '" + listName + "']/Element[code = '" + value + "']/value");
			}
			return valueDesc;
		}
		
		,enableDisablefields:function(popup,enableFlag)
		{
			if(enableFlag)
			{
				popup.getField('fundGroup').enableField();
				popup.getField('fundCode').enableField();
				popup.getField('classCode').enableField();
				popup.getField('brokerCode').enableField();
				if (this.isAllowBranch()){
					popup.getField('branchCode').enable();
				}	
				popup.getField('slsRepCode').enableField();
				popup.getField('effDate').enableField();
				popup.getField('model').enableField();
				popup.getField('aggFundGroup').enableField();
				popup.getField('OverAllowed').enableField();
			}
			else
			{
				popup.getField('fundGroup').disableField();
				popup.getField('fundCode').disableField();
				popup.getField('classCode').disableField();
				
				popup.getField('brokerCode').disableField();
				popup.getField('branchCode').disableField();
				popup.getField('slsRepCode').disableField();
			}
			
			if (!this.isAccountLevel())
					this.checkDisableField(popup);
			else
			{
				var fundGroup = popup.getField('fundGroup').getValue();
				var fundCode = popup.getField('fundCode').getRawValue();
				var classCode = popup.getField('classCode').getRawValue();
								
				if (fundGroup != "" ||(fundCode != "" &&  classCode != ""))
				{
						popup.getField('model').disableField();
				}
		
			}
			
					
			return true;
		}
		
		, doValidate: function ()
		{
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(true), responseHandler, 'validate');			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					DesktopWeb.Util.commitScreen();
				}
				else 
				{
					storeContextErrors(contextErrors);
					_self.updatesFlag = DesktopWeb._FAIL; 
				}
			}	

			return _self.updatesFlag;	
		}	
		
		,setCurrentModel:function(model)
		{
			_currentModel= model;
		}
		
		,getCurrentModel:function(model)
		{
			return _currentModel.toUpperCase();
		}
		
		,isModelChanged:function()
		{			
			return _isModelChanged;
		}
		
		,onChangeModel: function(selectedValue)
		{
			_isModelChanged = (selectedValue.toUpperCase() != this.getCurrentModel()) ;		
		}		
		
		,checkDisableField : function(popup)
		{		
			var popup = (popup) ? popup : _resources.popups['feeParms'];
			
			if (popup.getField('brokerCode').getRawValue().trim() != ""
			|| popup.getField('branchCode').getRawValue().trim() != ""
			|| popup.getField('slsRepCode').getRawValue().trim() != ""			
			)				
			{
				if (popup.action == _ADD)
				{
					popup.getField('maxFee').setValue(0);					
				}
				
				popup.getField('maxFee').disableField();				
				popup.getField('model').disableField();	
				popup.getField('OverAllowed').disableField();				
			}
			else 
			{
				popup.getField('maxFee').enableField();
				popup.getField('model').enableField();	
				popup.getField('OverAllowed').enableField();
			}
		}
		
		,setModel: function()
		{
			if (_resources.popups['feeParms'].action == _ADD
			|| (this.isNewRecord() && _resources.popups['feeParms'].action == _MOD))
				getModel();
		}
		
		,clearGrid: function(name)
		{
			_resources.grids[name].getStore().removeAll();
			_resources.grids[name].disableAllButtons();
		}
		
		,getTrailerFeesXML: function()
		{
			return _trailerFeesXML;
		}
		
		,setSelectedFeeParm: function(index)
		{
			_selectedFeeParmIndex = index;			
			_resources.grids['feeParms'].enableButton('modBtn');
			_resources.grids['feeParms'].enableButton('delBtn');
			var feeParmXML = this.getSelectedFeeParm();
			if (Ext.DomQuery.selectNode('feeParmsRecId', feeParmXML) != null)
			{			
				_resources.grids['feeParms'].enableButton('historicalBtn');
			}			
			_resources.grids['feeParmDetails'].getStore().loadData(feeParmXML);
		}
		
		,getSelectedFeeParm: function()
		{
			var vFeeParmXML = Ext.DomQuery.selectNode("FeeParms:nth(" + _selectedFeeParmIndex + ")", _trailerFeesXML);

			if(IFDS.Xml.getNode(vFeeParmXML, 'model') == null)
			{
				IFDS.Xml.addSingleNode(vFeeParmXML, 'model', IFDS.Xml.getNodeValue(vFeeParmXML, '//ModelID'));
			}
			else
			{			
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(vFeeParmXML, 'model'), IFDS.Xml.getNodeValue(vFeeParmXML, 'model'));
			}
		
			return vFeeParmXML;
		}
		
		,clearSelectedFeeParm: function()
		{
			_selectedFeeParmIndex = null;
			_resources.grids['feeParms'].disableButton('modBtn');
			_resources.grids['feeParms'].disableButton('delBtn');
			_resources.grids['feeParms'].disableButton('historicalBtn');
			this.clearGrid('feeParmDetails');			
		}
		
		,setSelectedFeeParmDetail: function(index)
		{
			_selectedFeeParmDetailIndex = index;			
			_resources.grids['feeParmDetails'].enableButton('modBtn');
			
			var feeParmDetailXML = this.getSelectedFeeParmDetail();
			if (Ext.DomQuery.selectNode("detlRecId", feeParmDetailXML) != null)
			{
				_resources.grids['feeParmDetails'].enableButton('historicalBtn');
			}
			
			if (Ext.DomQuery.selectValue('FeeType', feeParmDetailXML) == '2')
			{
				_resources.grids['scaleDetails'].getStore().loadData(feeParmDetailXML);
				_resources.grids['scaleDetails'].enableButton('addBtn');	
			}			
			else
			{
				this.clearGrid('scaleDetails');	
			}
			
			if(Ext.DomQuery.selectValue('SplitBy', feeParmDetailXML) == 'DSC')
			{			
				_resources.grids['feeParmDetails'].enableButton('addBtn');
			}
			else
			{	
				_resources.grids['feeParmDetails'].disableButton('addBtn');
			}
		}
		
		,getSelectedFeeParmDetail: function()
		{
			var feeParmXML = this.getSelectedFeeParm();			
			return Ext.DomQuery.selectNode("FeeParmsDetail:nth(" + _selectedFeeParmDetailIndex + ")", feeParmXML);
		}
		
		,clearSelectedFeeParmDetail: function()
		{
			_selectedFeeParmDetailIndex = null;
			_resources.grids['feeParmDetails'].disableButton('modBtn');
			this.clearGrid('scaleDetails');
		}
		
		,setSelectedScaleDetail: function(index)
		{					
			_selectedScaleDetailIndex = index;			
			_resources.grids['scaleDetails'].enableButton('modBtn')
			_resources.grids['scaleDetails'].enableButton('delBtn')
			var scaleDetailXML = this.getSelectedScaleDetail();
			if (Ext.DomQuery.selectNode('scaleRecId', scaleDetailXML) != null)
			{
				_resources.grids['scaleDetails'].enableButton('historicalBtn');
			}
		}
		
		,getSelectedScaleDetail: function()
		{			
			var feeParmDetailXML = this.getSelectedFeeParmDetail();			
			return Ext.DomQuery.selectNode("scaleDetail:nth(" + _selectedScaleDetailIndex + ")", feeParmDetailXML);
		}
		,
		removeAllAssociatedScaleDetails:function(gridName,recordName)
		{
			var store= _resources.grids[gridName].getStore();
			while (store.getCount()>0)
			{
			  var recordNode = Ext.DomQuery.selectNode(recordName + ":nth(1)", _self.getSelectedFeeParm());
			  recordNode.parentNode.removeChild(recordNode);
  			  store.removeAt(0);
			}		
		}
		,clearSelectedScaleDetail: function()
		{
			_selectedScaleDetailIndex = null;
			_resources.grids['scaleDetails'].disableButton('modBtn');
			_resources.grids['scaleDetails'].disableButton('delBtn');			
		}
		
		,showSearchFields: function()
		{
			hideAllSearchFields();
			var	searchBy = _resources.fields['searchValue'].getValue();			
			if (searchBy == 'FundGroup')
			{
				_resources.fields['searchFundGroup'].showField();			
			}
			else if (searchBy == 'FundClass')
			{				
				_resources.fields['searchFundCode'].showField();			
				_resources.fields['searchClassCode'].showField();
			}			
			else if (searchBy == 'BrokerCode')
			{				
				_resources.fields['searchBrokerCode'].showField();							
			}
			else if (searchBy == 'BranchCode')
			{				
				_resources.fields['searchBrokerCode'].showField();							
				_resources.fields['searchBranchCode'].showField();
				this.enableDisableSearchFields('searchBranchCode',this.isAllowBranch());
			}
			else if (searchBy == 'SlsRepCode')
			{
				_resources.fields['searchBrokerCode'].showField();							
				_resources.fields['searchBranchCode'].showField();
				_resources.fields['searchSlsRepCode'].showField();
				this.enableDisableSearchFields('searchBranchCode',this.isAllowBranch());
			}
			else if (searchBy == 'DistribChannel')
			{
				_resources.fields['searchDistribChannel'].showField();							
			}
		}
		,
		enableDisableSearchFields:function(fieldName,enableFlag)
		{
			if(_resources.fields[fieldName] !=null)
			{
			   return (enableFlag?_resources.fields[fieldName].enable():_resources.fields[fieldName].disable());
			}
			return true;
		}
		,doReload: function(more)
		{
			_resources.grids['feeParms'].colModel.setHidden(_resources.grids['feeParms'].colModel.findColumnIndex('brokerCode')
					, (_self.isAccountLevel() || !_self.isBrokerBranchRepOverride())); 
			_resources.grids['feeParms'].colModel.setHidden(_resources.grids['feeParms'].colModel.findColumnIndex('branchCode')
					, (_self.isAccountLevel() || !_self.isBrokerBranchRepOverride()));
			_resources.grids['feeParms'].colModel.setHidden(_resources.grids['feeParms'].colModel.findColumnIndex('slsRepCode')
					, (_self.isAccountLevel() || !_self.isBrokerBranchRepOverride()));
					
			var viewParamXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(viewParamXML, 'searchValue', _resources.fields['searchValue'].getValue());
			IFDS.Xml.addSingleNode(viewParamXML, 'searchAccountNum',
				(DesktopWeb._SCREEN_PARAM_MAP['AccountNum'].toLowerCase() == 'all' ? '0' : DesktopWeb._SCREEN_PARAM_MAP['AccountNum']));
			IFDS.Xml.addSingleNode(viewParamXML, 'searchFundGroup', 
				(_resources.fields['searchFundGroup'].isVisible() ? _resources.fields['searchFundGroup'].getValue() : ""));				 						
			IFDS.Xml.addSingleNode(viewParamXML, 'searchFundCode', 
				(_resources.fields['searchFundCode'].isVisible() ? _resources.fields['searchFundCode'].getValue() : ""));
			IFDS.Xml.addSingleNode(viewParamXML, 'searchClassCode', 
				(_resources.fields['searchClassCode'].isVisible() ? _resources.fields['searchClassCode'].getValue() : ""));
			IFDS.Xml.addSingleNode(viewParamXML, 'searchBrokerCode', 
				(_resources.fields['searchBrokerCode'].isVisible() ? _resources.fields['searchBrokerCode'].getValue() : ""));
			IFDS.Xml.addSingleNode(viewParamXML, 'searchBranchCode', 
				(_resources.fields['searchBranchCode'].isVisible() ? _resources.fields['searchBranchCode'].getValue() : ""));
			IFDS.Xml.addSingleNode(viewParamXML, 'searchSlsRepCode', 
				(_resources.fields['searchSlsRepCode'].isVisible() ? _resources.fields['searchSlsRepCode'].getValue() : ""));
			IFDS.Xml.addSingleNode(viewParamXML, 'searchDistribChannel', 
				(_resources.fields['searchDistribChannel'].isVisible() ? _resources.fields['searchDistribChannel'].getValue() : ""));
			IFDS.Xml.addSingleNode(viewParamXML, 'startRecNum', (more ? _nextStartRecNum : 1));
			IFDS.Xml.addSingleNode(viewParamXML, 'requestRecNum', _requestRecNum);
												
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, {ignoreErrorCode: '15'}, viewParamXML , responseHandler)
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					if (!more)
					{
						setDefaultValues(responseXML);										
						updatePopupDropdowns(responseXML);
						storeRuleList(responseXML);
					}
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					if (_nextStartRecNum)
					{
						_resources.grids['feeParms'].enableButton('moreBtn');
					}
					else
					{
						_resources.grids['feeParms'].disableButton('moreBtn');
					}
					setTrailerFeesXML(responseXML, more);	
					enableDistribChannel(); 
				}				
			}
		}
		
		,openActionPopup: function(name, action)
		{		
		
			var popup = _resources.popups[name];						
			popup.init(action);			
			popup.show();
		}
		
		,openHistoryPopup: function(name)
		{
			this.doHistoryCall(name, 1, successHandler);
			
			function successHandler(xml)
			{
				_resources.popups['history'].init(name);		
				_resources.popups['history'].populate(xml, false);					
				_resources.popups['history'].show();			
			}
		}
		
		,doHistoryCall: function(name, startRecNum, successCallback)
		{
			var viewParamXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(viewParamXML, 'startRecNum', startRecNum);
			IFDS.Xml.addSingleNode(viewParamXML, 'requestRecNum', _requestRecNum);
			
			var view = "";
			switch(name)
			{
				case 'feeParms':
				{
					view = _feeParmHistoryView;
					IFDS.Xml.addSingleNode(viewParamXML, 'auditType', 'FEEPRM');					
					var feeParmXML = this.getSelectedFeeParm();					
					IFDS.Xml.addSingleNode(viewParamXML, 'auditRecId', Ext.DomQuery.selectValue("feeParmsRecId", feeParmXML));					
					break;
				}
				case 'feeParmDetails':
				{				
					view = _feeParmDetailHistoryView;
					IFDS.Xml.addSingleNode(viewParamXML, 'auditType', 'FEEPRMDTL');					
					var feeParmDetailXML = this.getSelectedFeeParmDetail();					
					IFDS.Xml.addSingleNode(viewParamXML, 'auditRecId', Ext.DomQuery.selectValue("detlRecId", feeParmDetailXML));					
					break;
				}
				case 'scaleDetails':
				{				
					view = _scaleDetailHistoryView;
					IFDS.Xml.addSingleNode(viewParamXML, 'auditType', 'Scales');					
					var scaleDetailXML = this.getSelectedScaleDetail();
					IFDS.Xml.addSingleNode(viewParamXML, 'auditRecId', Ext.DomQuery.selectValue("scaleRecId", scaleDetailXML));										
					break;
				}
			}
			
			DesktopWeb.Ajax.doSmartviewAjax(view, null, viewParamXML, responseHandler);
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					successCallback(responseXML);							
				}							
			}		
		}
				
		,getDefaultValue: function(field)
		{
			return _defaultValues[field];
		}
		
		,validateFeeParmUpdate: function(action)
		{					
			var popup = _resources.popups['feeParms'];
			var backupTrailerFeesXML = IFDS.Xml.cloneDocument(_trailerFeesXML);
			var brokerBranchRep = (	popup.getField('brokerCode').getRawValue().trim() != "" || 
									popup.getField('branchCode').getRawValue().trim() != "" ||
									popup.getField('slsRepCode').getRawValue().trim() != "" );
									
			var hasFundGroupFundClass =  ( popup.getField('fundGroup').getValue().trim() != "" 
											||  popup.getField('fundCode').getValue().trim() != ""					
											|| popup.getField('classCode').getValue().trim() != "" );
			
			var validationXML = null;
			switch(action)
			{
				case _ADD:
				{
					var newFeeParmXML = addFeeParm(_trailerFeesXML, popup);
					validationXML = IFDS.Xml.stringToXML("<data><TrailerFee>" + IFDS.Xml.serialize(newFeeParmXML) + "</TrailerFee></data>");
					break;
				}
				case _MOD:
				{
					var updatedFeeParmXML = modFeeParm(this.getSelectedFeeParm(), popup);
					IFDS.Xml.removeAttribute(updatedFeeParmXML,"RecordSource");
					validationXML = IFDS.Xml.stringToXML("<data><TrailerFee>" + IFDS.Xml.serialize(updatedFeeParmXML) + "</TrailerFee></data>");					
					break;
				}
				case _DEL:
				{					
					var deletedFeeParmXML = delFeeParm(_trailerFeesXML, this.getSelectedFeeParm());
					if (deletedFeeParmXML != null)
					{						
						validationXML = IFDS.Xml.stringToXML("<data><TrailerFee>" + IFDS.Xml.serialize(deletedFeeParmXML) + "</TrailerFee></data>");
					}					
					else
					{
						validationXML = null;	
					}										
					break;
				}
			}
			if (validationXML != null)
			{
				sendValidation(validationXML, successHandler, errorHandler);
			}
			else
			{
				successHandler();	
			}
			
			function successHandler()
			{
				backupTrailerFeesXML = null;
				switch(action)
				{
					case _ADD:
					{
						addFeeParmDetails(newFeeParmXML, action);
						break;
					}
					case _MOD:
					{						
						if (_self.isModelChanged() 
							&& ((!_self.isAccountLevel() && !brokerBranchRep)			/*System level*/
							|| (_self.isAccountLevel() && !hasFundGroupFundClass)) /*Account Level*/
							)
						{
							_self.removeAllAssociatedScaleDetails('scaleDetails','scaleDetail');
							_self.removeAllAssociatedScaleDetails('feeParmDetails','FeeParmsDetail');
							
							addFeeParmDetails(updatedFeeParmXML, action);
							
						}
						else
							displayFeeParms(_trailerFeesXML, _selectedFeeParmIndex - 1);
						break;
					}
					case _DEL:
					{
						displayFeeParms(_trailerFeesXML);
					}					
				}
				_self.updatesFlag = true;								
				popup.hide();				
			}
			
			function errorHandler()
			{				
				_trailerFeesXML = backupTrailerFeesXML;
			}
			
		}
		
		,validateFeeParmDetailUpdate: function(action)
		{
			var popup = _resources.popups['feeParmDetails'];
			var backupTrailerFeesXML = IFDS.Xml.cloneDocument(_trailerFeesXML);	

			var updatedFeeParmXML = null;
			
			if(action == _ADD)
			{
				updatedFeeParmXML = addFeeParmDetailXml(this.getSelectedFeeParm(), this.getSelectedFeeParmDetail(), popup);
			}
			else if (action == _MOD)
			{
				updatedFeeParmXML = modFeeParmDetail(this.getSelectedFeeParm(), this.getSelectedFeeParmDetail(), popup);
			}
			
			var validationXML = IFDS.Xml.stringToXML("<data><TrailerFee>" + IFDS.Xml.serialize(updatedFeeParmXML) + "</TrailerFee></data>");
			
			sendValidation(validationXML, successHandler, errorHandler);
			
			function successHandler()
			{
				backupTrailerFeesXML = null;
				displayFeeParmDetails(updatedFeeParmXML, action);				
				popup.hide();
				_self.updatesFlag = true;
			}
			
			function errorHandler()
			{
				_trailerFeesXML = backupTrailerFeesXML;								
			}
		}
		
		,validateScaleDetailUpdate: function(action)
		{
			var popup = _resources.popups['scaleDetails'];
			var backupTrailerFeesXML = IFDS.Xml.cloneDocument(_trailerFeesXML);					
			var validationXML = null
			var updatedFeeParmXML = null;
			
			switch(action)
			{
				case _ADD:
				{
					updatedFeeParmXML = addScaleDetail(this.getSelectedFeeParm(), this.getSelectedFeeParmDetail(), popup);
					validationXML = IFDS.Xml.stringToXML("<data><TrailerFee>" + IFDS.Xml.serialize(updatedFeeParmXML) + "</TrailerFee></data>");
					break;	
				}
				case _MOD:
				{
					var scaleDetailXML=this.getSelectedScaleDetail();
					var mode = IFDS.Xml.getNodeValue(scaleDetailXML, 'action');
					if (mode == null)
						IFDS.Xml.setNodeValue(IFDS.Xml.getNode(scaleDetailXML, 'action'), action);
						
					updatedFeeParmXML = modScaleDetail(this.getSelectedFeeParm(), this.getSelectedFeeParmDetail(),scaleDetailXML , popup);
					validationXML = IFDS.Xml.stringToXML("<data><TrailerFee>" + IFDS.Xml.serialize(updatedFeeParmXML) + "</TrailerFee></data>");
					break;
				}
				case _DEL:
				{
					var scaleDetailXML=this.getSelectedScaleDetail();
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(scaleDetailXML, 'action'), action);				
					updatedFeeParmXML = delScaleDetail(this.getSelectedFeeParm(), this.getSelectedFeeParmDetail(), scaleDetailXML, popup);
					if (updatedFeeParmXML != null)
					{
						validationXML = IFDS.Xml.stringToXML("<data><TrailerFee>" + IFDS.Xml.serialize(updatedFeeParmXML) + "</TrailerFee></data>");
					}										
					break;
				}				
			}
			if (validationXML != null)
			{
				sendValidation(validationXML, successHandler, errorHandler);
			}
			else
			{
				successHandler();	
			}
			
			function successHandler()
			{
				backupTrailerFeesXML = null;
				
				displayScaleDetails(updatedFeeParmXML, action);
				
				_self.updatesFlag = true;
				popup.hide();
			}
			
			function errorHandler()
			{				
				_trailerFeesXML = backupTrailerFeesXML;								
			}
		}
		
		,doUpdate: function()
		{
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(false), responseHandler, null);
			function responseHandler(success, responseXML, contextErrors)
			{
				_self.updatesFlag = (success ? DesktopWeb._SUCCESS:DesktopWeb._FAIL);
			}	
			return _self.updatesFlag;			
		}
		, loadSelector: function(xml)
		{
			loadSelector(xml);
		}
		
		, getDateFormatTemplate: function(inputDateFormat)
		{
			var dateFormat = "";
			switch(inputDateFormat.toLowerCase())
			{
				case 'dmy':
				{
					dateFormat = 'DD/MM/YYYY';
					break;
				}
				case 'mdy':
				{
					dateFormat = 'MM/DD/YYYY'
					break;
				}
			}		
			return dateFormat;
		}
	}	
}	