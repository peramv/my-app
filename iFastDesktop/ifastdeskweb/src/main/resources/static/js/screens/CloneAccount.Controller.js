/*********************************************************************************************
 * @file	CloneAccount.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for Clone Account screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.   
 *
 *	14 Jun 2016 Watchara Th. P0241773 CHG0045794 DFT0064894 T83084
 *					- Ignored unexpected error message when saving the update.
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initDataXML = null;
	var _updateView = 'dtAcctAutoCopyProc';
	var _initView = 'dtAcctAutoCopyInit';	
	var _newSalesRep = false;
	var _allowBrUpd = false;
	var _newAcctNum = null;
	var _newShrNum = null
	var _taxTypeOptionsMap = null;	
	
	// PRIVATE METHODS ****************************************	
	
	function buildUpdateXML()
	{
		var recordXML = IFDS.Xml.newDocument('Data');
		
		IFDS.Xml.addSingleNode(recordXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(recordXML, 'broker', _resources.fields['broker'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'branch', _resources.fields['branch'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'slsrep', _resources.fields['slsrep'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'acctDesignation', _resources.fields['acctDesig'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'taxType', _resources.fields['taxType'].getValue());
		
		IFDS.Xml.addSingleNode(recordXML, 'effectiveDate', _resources.fields['effDate'].getSMVDateString());
		IFDS.Xml.addSingleNode(recordXML, 'altAcct', _resources.fields['altAcct'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'intermCode', _resources.fields['intermCode'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'intermAcctNum', _resources.fields['intermAcct'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'cloneDistribInfo', _resources.fields['distributionInfo'].getValue() ?  'yes' : 'no');
		IFDS.Xml.addSingleNode(recordXML, 'clonebankInfo', _resources.fields['bankInfo'].getValue() ? 'yes' : 'no');
		IFDS.Xml.addSingleNode(recordXML, 'cloneallEntities', _resources.fields['allEntities'].getValue() ? 'yes' : 'no'); 
		
		IFDS.Xml.addSingleNode(recordXML, 'regAgentAcctNum', _resources.fields['regAgentAcctNum'].getValue());
		IFDS.Xml.addSingleNode(recordXML, 'regAgent', _resources.fields['regAgent'].getValue());
		
		
		IFDS.Xml.addSingleNode(recordXML, 'createSlsRep', _newSalesRep ? 'yes' : 'no');			
			
		return recordXML;
	}
	
	function buildTaxTypeOptionsMap()
	{
		_taxTypeOptionsMap = {};		
		
		var taxTypeValidAcctDesigNodes = IFDS.Xml.getNodes(_initDataXML, '*/List[@listName = "TaxTypeValidAcctDesignation"]/Element');
		for (var i = 0; i < taxTypeValidAcctDesigNodes.length; i++)
		{
			var taxType = IFDS.Xml.getNodeValue(taxTypeValidAcctDesigNodes[i], 'code');
			var acctDesig = IFDS.Xml.getNodeValue(taxTypeValidAcctDesigNodes[i], 'value');
			
			if (!_taxTypeOptionsMap[acctDesig])
			{
				_taxTypeOptionsMap[acctDesig] = IFDS.Xml.newDocument('List');
			}			
			IFDS.Xml.appendNode(_taxTypeOptionsMap[acctDesig], 
				IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "TaxTypeOptions"]/Element[code = "' + taxType + '"]')));
		}	
	}
	
	function populateAgentSDropdowns(taxTypeOption)//CPF 12.4
	{

		if (taxTypeOption == 'OA'){
			_resources.fields['regAgent'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'RegAgentOAOptions']"));
	
		}else if (taxTypeOption == 'SA'){
			_resources.fields['regAgent'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'RegAgentSAOptions']"));

		}else if (taxTypeOption == 'SR'){
			_resources.fields['regAgent'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'RegAgentSRSOptions']"));

		}

		if (taxTypeOption == 'OA' || taxTypeOption == 'SA' || taxTypeOption == 'SR'){
		
			_resources.fields['regAgent'].setDisabled(false);
			_resources.fields['regAgentAcctNum'].setDisabled(false);
		}

	}

	function populateDropdowns()
	{		
		_resources.fields['acctDesig'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'AcctDesignationsOptions']"));		
		_resources.fields['taxType'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'TaxTypeOptions']"));
		_resources.fields['intermCode'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'IntermediaryOptions']"));

		var dataXML = IFDS.Xml.getNode(_initDataXML, "*/DefaultValues");
		populateAgentSDropdowns(IFDS.Xml.getNodeValue(dataXML, "taxType"));
	}
	
	function populateData ()
	{
		var dataXML = IFDS.Xml.getNode(_initDataXML, "*/DefaultValues");
		
		_resources.fields['broker'].prepopulate(IFDS.Xml.getNodeValue(dataXML, "broker"),
			IFDS.Xml.getNodeValue(dataXML, "broker") + " - " + IFDS.Xml.getNodeValue(dataXML, "brokerName"));		
						
		_resources.fields['branch'].prepopulate(IFDS.Xml.getNodeValue(dataXML, "branch"),		
			IFDS.Xml.getNodeValue(dataXML, "branch") + " - " + IFDS.Xml.getNodeValue(dataXML, "branchName"), IFDS.Xml.getNodeValue(dataXML, "branch"));		
			
		_allowBrUpd = IFDS.Xml.getNodeValue(dataXML, "allowBrUpd") == "yes";	
		if (_allowBrUpd)
		{	
			_resources.fields['branch'].enable();
		}
		else
		{
			_resources.fields['branch'].disable();
		}
				
		_resources.fields['slsrep'].prepopulate(IFDS.Xml.getNodeValue(dataXML, "slsRep"),
			IFDS.Xml.getNodeValue(dataXML, "slsRep") + " - " + IFDS.Xml.getNodeValue(dataXML, "slsRepName"));
		_resources.fields['slsrep'].enable();		
		
		setInitialValue('altAcct', IFDS.Xml.getNodeValue(dataXML, "altAcct"));
		setInitialValue('taxType', IFDS.Xml.getNodeValue(dataXML, "taxType"));
				
		setInitialValue('intermCode', IFDS.Xml.getNodeValue(dataXML, "intermCode"));
		setInitialValue('intermAcct', IFDS.Xml.getNodeValue(dataXML, "intermAcct"));
		setInitialValue('acctDesig', IFDS.Xml.getNodeValue(dataXML, "acctDesig"));
		var tempEffDate = IFDS.Xml.getNodeValue(dataXML, "effectDt");
		tempEffDate = (tempEffDate != "") ? DesktopWeb.Util.getDateDisplayValue(tempEffDate) : "";
		setInitialValue('effDate', tempEffDate);
		
		if (IFDS.Xml.getNodeValue(_initDataXML, "*/CopyOptions/cloneDistInfo") == 'yes')
		{
			_resources.fields['distributionInfo'].enable();
			_resources.fields['distributionInfo'].setValue(true);
		}	
		if (IFDS.Xml.getNodeValue(_initDataXML, "*/CopyOptions/cloneBnkInfo") == 'yes')
		{
			_resources.fields['bankInfo'].enable();
			_resources.fields['bankInfo'].setValue(true);
		}
		if (IFDS.Xml.getNodeValue(_initDataXML, "*/CopyOptions/cloneAllEnt") == 'yes')
		{
			_resources.fields['allEntities'].enable();
			_resources.fields['allEntities'].setValue(true);
		}	
		
		function setInitialValue(fldName, value)
		{
			if (value != "")
			{
				_resources.fields[fldName].setValue(value);
			}					
		}
	}
	
	function filterTaxTypes(acctDesig)
	{
		var curValue = _resources.fields['taxType'].getValue();
		_resources.fields['taxType'].reset();		
		if (_taxTypeOptionsMap[acctDesig] && IFDS.Xml.getNodes(_taxTypeOptionsMap[acctDesig], 'Element').length > 0)
		{
			_resources.fields['taxType'].loadData(_taxTypeOptionsMap[acctDesig]);
			_resources.fields['taxType'].enable();
			if (IFDS.Xml.getNode(_taxTypeOptionsMap[acctDesig], 'Element[code = "' + curValue + '"]'))
			{
				_resources.fields['taxType'].setValue(curValue);
			}
		}
		else
		{
			_resources.fields['taxType'].disable();
		}		
	}	
	
	
	// PUBLIC ITEMS *************************************
	return {
		updatesFlag: true //always want to execute the update, regardless of changes on screen
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;

			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler);
			
			function responseHandler(success, responseXML)
			{	
				if (success)
				{					
					_initDataXML = responseXML;
					buildTaxTypeOptionsMap();
					populateDropdowns();					
					populateData();					
					_self.handleAcctDesigChange();					
				}				
			}	
		}
		
		,handleAcctDesigChange: function()
		{
			var acctDesig = _resources.fields['acctDesig'].getValue();
			if (acctDesig == 3) //3 = Intermediary
			{
				_resources.fields['intermCode'].enable();
			}
			else
			{
				_resources.fields['intermCode'].reset();
				_resources.fields['intermCode'].disable();				
			}
			_self.handleIntermCodeChange();
			
			filterTaxTypes(acctDesig);
		}
		
		,handleIntermCodeChange: function()
		{
			var intermCode = _resources.fields['intermCode'].getValue();
			if (intermCode != "")
			{
				_resources.fields['intermAcct'].enable();
			}
			else
			{
				_resources.fields['intermAcct'].reset();
				_resources.fields['intermAcct'].disable();
			}
		}
		
		,setNewSalesRep: function(value)
		{
			_newSalesRep = value;			
		}

		,populateAgentDropdowns: function(taxTypeOption)
		{
			populateAgentSDropdowns(taxTypeOption);

		}


		,toggleRegAgentField: function(taxType)
		{
			if (taxType == "OA" || taxType == "SA" || taxType == "SR")
			{
				_resources.fields['regAgent'].enable();	
			}
			else
			{
				_resources.fields['regAgent'].reset();				
				_resources.fields['regAgent'].disable();	
			}
		}
		
		,toggleRegAgentAcctNumField: function(taxType)
		{
			if (taxType == "OA" || taxType == "SA" || taxType == "SR")
			{
				_resources.fields['regAgentAcctNum'].enable();		
			}
			else
			{
				_resources.fields['regAgentAcctNum'].reset();				
				_resources.fields['regAgentAcctNum'].disable();		
			}
		}

		,isBranchUpdateAllowed: function()
		{
			return _allowBrUpd;
		}
		
		,validateInput: function()
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
		
		,doUpdate: function()
		{						
			var updateStatus = null;
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler, null, ['00281']);			
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{					
					_newAcctNum = IFDS.Xml.getNodeValue(responseXML, '*/ClonedAccountDetails/newAcctNum');
					_newShrNum = IFDS.Xml.getNodeValue(responseXML, '*/ClonedAccountDetails/newShrNum');
					
					var msgText = _translationMap['CloneSuccessful'] 
						+ "\n\n"
						+ _translationMap['NewAcctNum'] + " = " + _newAcctNum
						+ "\n"
						+ _translationMap['NewShrNum'] + " = " + _newShrNum;
					
					if (IFDS.Xml.getNode(responseXML, '*/RequestStatus/Errors'))
					{
						msgText += "\n\n" + _translationMap["Warning"] + ": " + IFDS.Xml.getNodeValue(responseXML, '*/RequestStatus/Errors/Error/text');  						
					}

					// have to use alert() here to prevent window from 
					// being closed before user sees new account details											
					alert(msgText)						
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{					
					updateStatus = DesktopWeb._FAIL
				}
			}
			return updateStatus;			
		}
		
		,getResult: function()
		{
			var result = "AccountNum=" + _newAcctNum + ";ShareholderNum=" + _newShrNum; 			
			return result;	 
		}			
	}
}	