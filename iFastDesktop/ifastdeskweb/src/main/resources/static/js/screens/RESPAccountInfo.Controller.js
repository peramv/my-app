/*********************************************************************************************
 * @file	RESPAccountInfo.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for RESP Account Information screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  20 May 2014 Narin Suanlamyai P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.   
 *
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _modPerm = null;
	var _delPerm = null;
	var _runPerm = null;
	
	var _RESPAcctInfoXML = null;
	
	var _origMatureDate = null;
	var _taxType = null;
	var _version = null;
	var _siblingSeverity = null;
	var _siblingMsg = null;
	var _DTCResponse = null;
	
	var _dtRESPAcctInfoInitService = "dtRESPAcctInfoInit";
	var _dtRESPAcctVldtnService = "dtRESPAcctVldtn";
	var _dtRESPAcctInfoUpdService = "dtRESPAcctInfoUpd";
	var _historyService = 'dtHistRESPAcct';
	//var _historyService = 'dtHistoricalInfo';
	
	// PRIVATE METHODS ****************************************	
	function loadRESPAccountInfo(){
		var paramXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(paramXML, 'AccountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		
		clearGrid('regInfoGrid');
		clearGrid('benDetlGrid');
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtRESPAcctInfoInitService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{			
			if (success)
			{				
				_RESPAcctInfoXML = responseXML;
			}
			else
			{
				_RESPAcctInfoXML = null;
			}
			
			if(_RESPAcctInfoXML)
			{
				loadGlobalObject();
				
				displayRESPAcctInfo();
				
				enableFields();
			}
		}
	}
	
	function loadGlobalObject()
	{
		setPermission(IFDS.Xml.getNode(_RESPAcctInfoXML, '//Permission'));
		_origMatureDate = IFDS.Xml.getNodeValue(IFDS.Xml.getNode(_RESPAcctInfoXML, '//RESPAccountInfo'), 'origMatureDt');
		_taxType = IFDS.Xml.getNodeValue(IFDS.Xml.getNode(_RESPAcctInfoXML, '//RESPAccountInfo'), 'taxType');
		_version = IFDS.Xml.getNodeValue(IFDS.Xml.getNode(_RESPAcctInfoXML, '//RESPAccountInfo'), 'version');
		
	}
	
	function displayRESPAcctInfo()
	{
		loadSMVComboBox('repHRDC', 'RepHRDCOpt');
		loadSMVComboBox('pre98Contr', 'Pre98ContribOpt');
		loadSMVComboBox('respStat', 'RESPStatOpt');
		loadSMVComboBox('siblingOnly', 'SiblingOnlyOpt');
		loadSMVComboBox('repReqd', 'RepReqdOpt');
		
		displayRESPAccountInfo(IFDS.Xml.getNode(_RESPAcctInfoXML, '//RESPAccountInfo'));
		
		_resources.grids['benDetlGrid'].getStore().loadData(_RESPAcctInfoXML);
		_resources.grids['regInfoGrid'].getStore().loadData(_RESPAcctInfoXML);
	}
	
	function enableFields()
	{
		if (_modPerm == 'yes')
		{
			_resources.fields['matureDt'].enable();
			_resources.fields['repHRDC'].enable();
			_resources.fields['pre98Contr'].enable();
			_resources.fields['respStat'].enable();
			_resources.fields['incepDt'].enable();
			_resources.fields['siblingOnly'].enable();
			_resources.fields['repReqd'].enable();
		}
		else
		{
			_resources.fields['matureDt'].disable();
			_resources.fields['repHRDC'].disable();
			_resources.fields['pre98Contr'].disable();
			_resources.fields['respStat'].disable();
			_resources.fields['incepDt'].disable();
			_resources.fields['siblingOnly'].disable();
			_resources.fields['repReqd'].disable();	
		}
	}
			
	function displayRESPAccountInfo(acctInfoXML)
	{
		if(acctInfoXML)
		{
			// First column
			_resources.fields['planNo'].setValue(IFDS.Xml.getNodeValue(acctInfoXML, 'planNo'));
			_resources.fields['matureDt'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(acctInfoXML, 'matureDt')));
			_resources.fields['grandFather'].setValue(IFDS.Xml.getNodeValue(acctInfoXML, 'grandFather'));
			_resources.fields['repHRDC'].setValue(IFDS.Xml.getNodeValue(acctInfoXML, 'repHRDC'));
			_resources.fields['pre98Contr'].setValue(IFDS.Xml.getNodeValue(acctInfoXML, 'pre98Contr'));
			
			// Second column
			_resources.fields['respStat'].setValue(IFDS.Xml.getNodeValue(acctInfoXML, 'respStat'));
			_resources.fields['incepDt'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(acctInfoXML, 'incepDt')));
			_resources.fields['siblingOnly'].setValue(IFDS.Xml.getNodeValue(acctInfoXML, 'siblingOnly'));
			_resources.fields['repReqd'].setValue(IFDS.Xml.getNodeValue(acctInfoXML, 'repReqd'));
		}
	}
	
	function validateSiblingOnly()
	{
		sendValidation( _dtRESPAcctVldtnService, buildValidateXML(), successHandler, errorHandler);
		
		function successHandler(responseXML)
		{
			var acctValNode = IFDS.Xml.getNode(responseXML, "//RESPAcctValidations");
			var siblingWarningNodes = IFDS.Xml.getNodes(acctValNode, "SiblingQuestns/SiblingQuestn[severity='W']");
			var siblingErrorNodes = IFDS.Xml.getNodes(acctValNode, "SiblingQuestns/SiblingQuestn[severity='E']");
			var amendWarningNodes = IFDS.Xml.getNodes(responseXML, "//AmendmentWarning/warnMsg");
			
			_siblingSeverity = "";
			
			displayQuestionsAndWarnings();
			
			function displayQuestionsAndWarnings()
			{
				displaySiblingQuestions();
			}
			
			function displaySiblingQuestions()
			{
				displaySiblingWarnings();
			}
			
			function displaySiblingWarnings()
			{
				if(siblingWarningNodes.length > 0)
				{
					var siblingWarningMsg = "";
					siblingWarningMsg = IFDS.Xml.getNodeValue(siblingWarningNodes[0], "questn");
					for( i=1; i<siblingWarningNodes.length; i++){
						siblingWarningMsg += "<br/><br/>" + IFDS.Xml.getNodeValue(siblingWarningNodes[i], "questn");
					}
					DesktopWeb.Util.displayWarning(siblingWarningMsg, displaySiblingErrors);
					_siblingSeverity = IFDS.Xml.getNodeValue(siblingWarningNodes[0], "severity");
				}else{
					displaySiblingErrors();
				}
			}

			function displaySiblingErrors()
			{
				if(siblingErrorNodes.length > 0)
				{
					var siblingErrorMsg = "";
					siblingErrorMsg = IFDS.Xml.getNodeValue(siblingErrorNodes[0], "questn");
					for( i=1; i<siblingErrorNodes.length; i++){
						siblingErrorMsg += "<br/><br/>" + IFDS.Xml.getNodeValue(siblingErrorNodes[i], "questn");
					}
					DesktopWeb.Util.displayError(siblingErrorMsg, displayAmendmentWarnings);
					_siblingSeverity = IFDS.Xml.getNodeValue(siblingErrorNodes[0], "severity");
				}else{
					displayAmendmentWarnings();
				}
			}
			
			function displayAmendmentWarnings()
			{
				if(amendWarningNodes.length > 0)
				{
					var amendWarningMsg = "";
					amendWarningMsg = IFDS.Xml.getNodeValue(amendWarningNodes[0], ".");
					for( i=1; i<amendWarningNodes.length; i++){
						amendWarningMsg += "<br/><br/>" + IFDS.Xml.getNodeValue(amendWarningNodes[i], ".");
					}
					DesktopWeb.Util.displayWarning(amendWarningMsg);
				}
			}
		}
		
		function errorHandler(responseXML)
		{
			// Error Handling
		}
	}
	
	function requestQuestionPrompt()
	{
		if(!_resources.fields['matureDt'].isValid() || !_resources.fields['matureDt'].isValid()) return false;
		
		sendValidation( _dtRESPAcctVldtnService, buildValidateXML(), successHandler, errorHandler);
		
		function successHandler(responseXML)
		{
			var acctValNode = IFDS.Xml.getNode(responseXML, "//RESPAcctValidations");
			var displayQuestion = IFDS.Xml.getNodeValue(acctValNode, "promptDTC");
			var questionMsg = IFDS.Xml.getNodeValue(acctValNode, "dtcQuestn");
			
			if(displayQuestion == "yes"){
				openDTCPrompt(questionMsg);
			}else{				
				doAccountInfoUpdate();
			}
			
		}
		
		function errorHandler(responseXML)
		{
			// Error Handling
		}
	}

	function openDTCPrompt(msg)
	{
		displayDTCPrompt(msg, handlePromptMsg);
		function handlePromptMsg(btn){
			_DTCResponse = btn;
			doAccountInfoUpdate();
		}
	}
	
	function buildValidateXML()
	{
		var xml = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(xml, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] );
		IFDS.Xml.addSingleNode(xml, "siblingOnly", _resources.fields['siblingOnly'].getValue() );
		IFDS.Xml.addSingleNode(xml, "matureDt", _resources.fields['matureDt'].getSMVDateString() );
		IFDS.Xml.addSingleNode(xml, "origMatureDt", _origMatureDate );
		IFDS.Xml.addSingleNode(xml, "taxType", _taxType );
		
		return xml;
	}
	
	function buildAccountInfoData()
	{
		var xml = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(xml, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] );
		IFDS.Xml.addSingleNode(xml, "siblingOnly", _resources.fields['siblingOnly'].getValue() );
		IFDS.Xml.addSingleNode(xml, "matureDt", _resources.fields['matureDt'].getSMVDateString() );
		IFDS.Xml.addSingleNode(xml, "repHRDC", _resources.fields['repHRDC'].getValue() );
		IFDS.Xml.addSingleNode(xml, "pre98Contr", _resources.fields['pre98Contr'].getValue() );
		IFDS.Xml.addSingleNode(xml, "repReqd", _resources.fields['repReqd'].getValue() );
		IFDS.Xml.addSingleNode(xml, "incepDt", _resources.fields['incepDt'].getSMVDateString() );
		IFDS.Xml.addSingleNode(xml, "repStat", _resources.fields['respStat'].getValue() );
		IFDS.Xml.addSingleNode(xml, "version", _version );
		IFDS.Xml.addSingleNode(xml, "siblingSeverity", (_siblingSeverity!=null)?_siblingSeverity:"" );

		if( _DTCResponse != null )
		{
			IFDS.Xml.addSingleNode(xml, "promptDTC", _DTCResponse );
			_DTCResponse = null;
		}
		return xml;
	}
	function sendValidation(api, xml, successCallback, errorCallback)
	{
		DesktopWeb.Ajax.doSmartviewAjax(api, null, xml, responseHandler, _translationMap['ProcMsg_Validating']);
					
		function responseHandler(success, responseXML)
		{
			if (success)
			{		
				successCallback(responseXML);
			}
			else
			{												
				errorCallback(responseXML);				
			}			
		}
	}
	
	function doAccountInfoUpdate()
	{
		DesktopWeb.Util.commitScreen();
	}

	function loadSMVComboBox(name, listName)
	{
		_resources.fields[name].getStore().loadData(IFDS.Xml.getNode(_RESPAcctInfoXML, "//List[@listName='" + listName + "']"));
	}

	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function setPermission(permNode)
	{
		if(permNode)
		{
			_modPerm = IFDS.Xml.getNodeValue(permNode, 'modPerm');
			_delPerm = IFDS.Xml.getNodeValue(permNode, 'delPerm');
			_runPerm = IFDS.Xml.getNodeValue(permNode, 'runPerm');
		}
	}
	
	function displayDTCPrompt(promptMsg, callbackFn)
	{
		Ext.Msg.show(
			 {
			     title:'iFAST/Desktop ' + _translationMap['Information']
			     ,msg: promptMsg		 			
			     ,buttons: Ext.Msg.YESNO		
			     ,icon: Ext.MessageBox.QUESTION
				 ,minWidth:400
				 ,fn: callbackFn
		     }
		);
	}
	
	function updateUpdatesFlag(val)
	{
		_self.updatesFlag = val;
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			loadRESPAccountInfo();
		}
		
		,getOriginalMatualDate: function()
		{
			return _origMatureDate;
		}
		
		,doSiblingOnlyValidation: function()
		{
			validateSiblingOnly();
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
			var requestXML = buildAccountInfoData();
			DesktopWeb.Ajax.doSmartviewUpdate(_dtRESPAcctInfoUpdService, null, IFDS.Xml.cloneDocument(requestXML), responseHandler, _translationMap['ProcMsg_Saving']);
			
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
		
		,openHistoryPopup: function(acctNum)
		{
			var viewParam = {};
			var historyName = null;
			viewParam['auditType'] = "RESPAcct";
			viewParam['searchValue1'] = acctNum;
			historyName = _translationMap['Historical'] + " " + _translationMap['Information'];
			_resources.popups['history'].init(historyName, _historyService, viewParam, true);
			_resources.popups['history'].show();
			
		}
		
		,doQuestionPrompt: function()
		{
			requestQuestionPrompt();
		}
		
		,activeUpdatesFlag: function()
		{
			updateUpdatesFlag(true);
		}
		
		,screenModified: function()
		{
			return _self.updatesFlag;
		}
		
	}	
}	