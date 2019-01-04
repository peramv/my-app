/*********************************************************************************************
 * @file	RESPGrantInfo.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for RESP Grant Information screen.
 *
 * History: Supareuk S. PETP0181067 FN01 CHG0034430 T54333
 *          - Getting the date format from DesktopWeb.Util.getDateDisplayValue to show
 *            all date with correct format from registry field
 *
 *  30 Apr 2014 G. Thawornwachirakun P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *  23 May 2014 Narin Suanlamyai P0220132 FN03 T55087
 *					- Update SAGES Cancel Request validation
 *
 *  30 May 2014 Narin Suanlamyai P0220132 FN03 DFT0034351 T55198
 *					- Disable SAGES fields for non-SAGES environment
 *
 *  12 Jun 2014 Narin Suanlamyai P0220132 FN03 DFT0034936 T55247
 *					- Fix displaying date of SAGES section
 *
 *  10 July 2014 Narin Suanlamyai P0220132 FN03 DFT0036690 T55410
 *					- Fix validate From Date/To Date against SAGES Request transaction.
 *
 *  21 Jul 2014 Narin Suanlamyai P0220132 FN03 DFT0037101 T55450
 *					- Hide SAGES section for non-SAGES environment.
 *
 *  15 Aug 2014 Narin Suanlamyai P0220132 FN03 DFT0037927 T55561
 *					- Restriction to authorized users for SAGES Grant fields.
 *
 *  20 Nov 2015 Aurkarn Mongkonrat P0241773 T81771 DFT0055645
 *					  - Separate the redesigned screen to a new program.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.   
 *
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = "dtRESPGrantInit"
	var _updateView = "dtRESPGrantUpd";
	var _validateView = "dtRESPGrantProc";
	var _initDataXML = null;
	var _cesgCurrStat = null;
	var _cesgRunMode = null;
	var _cesgVersion = null;
	var _clbCurrStat = null;
	var _clbVersion = null;
	var _clbRunMode = null;
	var _acesUpdates = true;
	var _qesiUpdates = true;	
	var _showACES = null;
	var _showQESI = null;	
	
	//SAGES
	var _showSAGES = null;
	var _sagesInitValues = {};
	var _sagesCancelRequestProperty = {};
	var _sagesRunMode = null;
	
	var _addPerm = null;
	var _modPerm = null;
				
		
	// PRIVATE METHODS ****************************************
	function populateScreen()
	{
		_addPerm = IFDS.Xml.getNodeValue(_initDataXML, '//Permission/addPerm').toLowerCase() == 'yes';
		_modPerm = IFDS.Xml.getNodeValue(_initDataXML, '//Permission/modPerm').toLowerCase() == 'yes';		
		
		Ext.getCmp('beneFieldset').setTitle(_translationMap['RESPBeneficiary'] + ':  ' + IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/name'))
		_resources.fields['sin'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/sin'));
		_resources.fields['dob'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/dob')));
		_resources.fields['taxjuris'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/taxjuris'));
		_resources.fields['taxTypeDesc'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/taxTypeDesc'));
		_resources.fields['siblingOnly'].setValue((IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/siblingOnly').toLowerCase() == 'y' 
			? _translationMap['Yes'] : _translationMap['No']));
		_resources.fields['specimenNum'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/specimenNum'));
		_resources.fields['beneAddr'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/addr1')
			+ (IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/addr2') != "" ? ", " : "") + IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/addr2')
			+ (IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/addr3') != "" ? ", " : "") + IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/addr3')
			+ (IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/cntry') != "" ? ", " : "") + IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/cntry')
			+ (IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/pstl') != "" ? ", " : "") + IFDS.Xml.getNodeValue(_initDataXML, '*/BenAddrInfo/pstl'));
			
		_resources.fields['pcgName'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/pcgName'));
		_resources.fields['pcgSINBN'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/pcgSINBN'));					
		
		// CESG
		_cesgVersion = IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/version');
		_resources.fields['cesg']['currStat'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/currStatDesc'));
		_cesgCurrStat = IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/currStat');
		_cesgCurrStat = (_cesgCurrStat == "Not Requested" ? "Blank" : _cesgCurrStat); 							
		if (IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/allowStatUpd') == 'no' || !_modPerm || !_addPerm)
		{
			_resources.fields['cesg']['newStat'].disableField();
		}
		else
		{			
			_resources.fields['cesg']['newStat'].loadData(_self.getStatusOptions('CESG', _cesgCurrStat));
		}
		var genRT511 =  IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/genRT511')	
		_resources.fields['cesg']['genRT511'].setValue(genRT511);
		if (genRT511.toLowerCase() == 'no' || !_modPerm || !_addPerm)
		{
			_resources.fields['cesg']['genRT511'].disable();
			_resources.fields['cesg']['cutOffDate'].disable();
		}
		_resources.fields['cesg']['createdby'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/createdby'));
		_resources.fields['cesg']['procdate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/procdate')));
		_resources.fields['cesg']['moduser'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/modUser'));
		_resources.fields['cesg']['moddate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CESGInformation/modDate')));		
		
		// CLB
		_clbVersion = IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/version');
		_resources.fields['clb']['currStat'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/currStatDesc'));
		_clbCurrStat = IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/currStat');
		_clbCurrStat = (_clbCurrStat == "Not Requested" ? "Blank" : _clbCurrStat);		
		if (IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/allowStatUpd') == 'no' || !_modPerm || !_addPerm)
		{
			_resources.fields['clb']['newStat'].disableField();
		}
		else
		{						
			_resources.fields['clb']['newStat'].loadData(_self.getStatusOptions('CLB', _clbCurrStat));					
		}		
		_resources.fields['clb']['createdby'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/createdby'));
		_resources.fields['clb']['procdate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/procdate')));
		_resources.fields['clb']['moduser'].setValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/modUser'));
		_resources.fields['clb']['moddate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, '*/CLBInformation/modDate')));
		
		_showACES = (IFDS.Xml.getNodeValue(_initDataXML, '*/ShowOtherGrants/showACES').toLowerCase() == 'yes');		
		if (_showACES)
		{	
			_resources.popups['aces'].getField('grantOption').loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "ACESYearOptions"]'));
			Ext.getCmp('acesFieldSet').show();								
			_resources.grids['aces'].loadData(IFDS.Xml.getNode(_initDataXML, '*/ACESInformation'));
			
			var enableAddBtn = IFDS.Xml.getNodeValue(_initDataXML, '*/RESPGrantInfo/siblingOnly').toLowerCase() == 'y' ? true: false;
			if(enableAddBtn && _addPerm)
			{
				_resources.grids['aces'].enableButton('addBtn');
			}
			else
			{
				_resources.grids['aces'].disableButton('addBtn');
			}
			_resources.grids['aces'].doLayout();								
		}
		
		_showQESI = (IFDS.Xml.getNodeValue(_initDataXML, '*/ShowOtherGrants/showQESI').toLowerCase() == 'yes');		
		if (_showQESI)
		{
			_resources.popups['qesi'].getField('year').loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "QESIYearOptions"]'));
			_resources.popups['qesi'].getField('stopReason').loadData(IFDS.Xml.getNode(_initDataXML, '*/List[@listName = "StopReasonList"]'));
			Ext.getCmp('qesiFieldSet').show();			
			_resources.grids['qesi'].loadData(IFDS.Xml.getNode(_initDataXML, '*/QESIInformation'));
			_resources.grids['qesi'].doLayout();
			
			if(_addPerm)
			{
				_resources.grids['qesi'].enableButton('addBtn');
			}
			else
			{
				_resources.grids['qesi'].disableButton('addBtn');
			}
												
		}	

		
		_showSAGES = (IFDS.Xml.getNodeValue(_initDataXML, '*/ShowOtherGrants/showSAGES').toLowerCase() == 'yes');		
		if (_showSAGES)
		{
			var sagesInfo = IFDS.Xml.getNodes(_initDataXML, '*/SAGESInformation');
			var sagesNode = null;
			for (i= 0 ; i < sagesInfo.length ; i++)
			{
				for (var j = 0; j < sagesInfo[i].childNodes.length; j++)
				{
					sagesNode = sagesInfo[i].childNodes[j];
					sagesNodeValues = sagesNode.childNodes[0] ? 
										sagesNode.childNodes[0].nodeValue : "";
					
					_sagesInitValues[sagesNode.nodeName] = sagesNodeValues;
				}
			}
			
			if (_sagesInitValues['requestFlag']  != undefined && _sagesInitValues['requestFlag'].length > 0){
				_resources.fields['sages']['requestFlag'].setValue( _sagesInitValues['requestFlag'] );
			}else{
				_resources.fields['sages']['requestFlag'].setValue('no');
			}
			
			if (_sagesInitValues['applicationDate']  != undefined && _sagesInitValues['applicationDate'].length > 0)
				_resources.fields['sages']['applicationDate'].setValue(DesktopWeb.Util.stringToDate(_sagesInitValues['applicationDate'] ));
			
			if (_sagesInitValues['stopDate']  != undefined  && _sagesInitValues['stopDate'].length > 0)
				_resources.fields['sages']['stopDate'].setValue(DesktopWeb.Util.getDateDisplayValue(_sagesInitValues['stopDate'] ));
				
			if (_sagesInitValues['planStartDate'] != undefined  && _sagesInitValues['planStartDate'].length > 0){
				var planStartDate = DesktopWeb.Util.stringToDate(_sagesInitValues['planStartDate']);
				_resources.fields['sages']['applicationDate'].setMinValue(planStartDate);
				_resources.popups['sagesCancelRequest'].getField('fromDate').setMinValue(planStartDate);
				_resources.popups['sagesCancelRequest'].getField('toDate').setMinValue(planStartDate);
			}
				
			if (_sagesInitValues['curBusDate'] != undefined  && _sagesInitValues['curBusDate'].length > 0){
				var curBusDate = DesktopWeb.Util.stringToDate(_sagesInitValues['curBusDate']);
				_resources.fields['sages']['applicationDate'].setMaxValue(curBusDate);
				_resources.popups['sagesCancelRequest'].getField('fromDate').setMaxValue(curBusDate);
				_resources.popups['sagesCancelRequest'].getField('toDate').setMaxValue(curBusDate);
			}
			
			if (_modPerm){
				setupSAGESSection(_resources.fields['sages']['requestFlag'].getValue());
			}else{
				_resources.fields['sages']['requestFlag'].disable();
				_resources.fields['sages']['applicationDate'].disable(); 
				_resources.buttons['sages']['cancelRequestBtn'].disable();
			}
		}else{
			Ext.getCmp('sagesFieldSet').hide();	
		}
	}
	
	function setupSAGESSection(SAGESRequestFlag)
	{
		if (SAGESRequestFlag == 'no') 
		{
			_resources.fields['sages']['applicationDate'].disable();
			_resources.fields['sages']['applicationDate'].allowBlank = true;
		}else //if (SAGESRequestFlag == 'yes') 
		{
			_resources.fields['sages']['applicationDate'].enable();
			_resources.fields['sages']['applicationDate'].allowBlank = false;
		}
	}
			
	function buildUpdateXML()
	{
		var updateXML = IFDS.Xml.newDocument("data");
		
		// CESG
		if (_cesgRunMode == _self.MOD)
		{	
			var cesgXMLNode = IFDS.Xml.addSingleNode(updateXML, "RESPGrantUpd");
			IFDS.Xml.addSingleNode(cesgXMLNode, 'grantType', 'AddCESG');
			IFDS.Xml.addSingleNode(cesgXMLNode, 'version', _cesgVersion);
			IFDS.Xml.addSingleNode(cesgXMLNode, 'runMode', _self.MOD);
			IFDS.Xml.addSingleNode(cesgXMLNode, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(cesgXMLNode, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
			IFDS.Xml.addSingleNode(cesgXMLNode, 'newStat', _resources.fields['cesg']['newStat'].getValue());
			IFDS.Xml.addSingleNode(cesgXMLNode, 'genRT511', _resources.fields['cesg']['genRT511'].getValue());
			IFDS.Xml.addSingleNode(cesgXMLNode, 'cutOffDt', DesktopWeb.Util.getDateString(_resources.fields['cesg']['cutOffDate'].getValue(), DesktopWeb._SCREEN_PARAM_MAP['dateFormat']));
		}
				
		// CLB
		if (_clbRunMode == _self.MOD)
		{	
			var clbXMLNode = IFDS.Xml.addSingleNode(updateXML, "RESPGrantUpd");
			IFDS.Xml.addSingleNode(clbXMLNode, 'grantType', 'CLB');
			IFDS.Xml.addSingleNode(clbXMLNode, 'version', _clbVersion);
			IFDS.Xml.addSingleNode(clbXMLNode, 'runMode', _self.MOD);
			IFDS.Xml.addSingleNode(clbXMLNode, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(clbXMLNode, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
			IFDS.Xml.addSingleNode(clbXMLNode, 'newStat', _resources.fields['clb']['newStat'].getValue());			
		}
		
		// ACES
		if (_acesUpdates)
		{
			var acesRecords = _resources.grids['aces'].getAllRecords();
			for (var i = 0; i < acesRecords.length; i++)
			{
				if (acesRecords[i].data['runMode'] != "")
				{
					var acesXMLNode = IFDS.Xml.addSingleNode(updateXML, "RESPGrantUpd");
					IFDS.Xml.addSingleNode(acesXMLNode, 'grantType', 'ACES');
					IFDS.Xml.addSingleNode(acesXMLNode, 'version', acesRecords[i].data['version']);
					IFDS.Xml.addSingleNode(acesXMLNode, 'runMode', acesRecords[i].data['runMode']);
					IFDS.Xml.addSingleNode(acesXMLNode, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
					IFDS.Xml.addSingleNode(acesXMLNode, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
					IFDS.Xml.addSingleNode(acesXMLNode, 'newStat', acesRecords[i].data['newStat']); 	
					IFDS.Xml.addSingleNode(acesXMLNode, 'grantOpt', acesRecords[i].data['grantOpt']);
					IFDS.Xml.addSingleNode(acesXMLNode, 'grantInfoID', acesRecords[i].data['grantInfoID']);
				}
			}
		}
		
		// QESI
		if (_qesiUpdates)
		{
			var qesiRecords = _resources.grids['qesi'].getAllRecords();
			for (var i = 0; i < qesiRecords.length; i++)
			{
				if (qesiRecords[i].data['runMode'] != "")
				{
					var qesiXMLNode = IFDS.Xml.addSingleNode(updateXML, "RESPGrantUpd");
					IFDS.Xml.addSingleNode(qesiXMLNode, 'grantType', 'QESI');
					IFDS.Xml.addSingleNode(qesiXMLNode, 'version', qesiRecords[i].data['version']);
					IFDS.Xml.addSingleNode(qesiXMLNode, 'runMode', qesiRecords[i].data['runMode']);
					IFDS.Xml.addSingleNode(qesiXMLNode, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
					IFDS.Xml.addSingleNode(qesiXMLNode, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
					IFDS.Xml.addSingleNode(qesiXMLNode, 'newStat', qesiRecords[i].data['newStat']); 	
					IFDS.Xml.addSingleNode(qesiXMLNode, 'grantYr', qesiRecords[i].data['grantYr']);
					IFDS.Xml.addSingleNode(qesiXMLNode, 'stopReason', qesiRecords[i].data['stopReason']);
					IFDS.Xml.addSingleNode(qesiXMLNode, 'grantInfoID', qesiRecords[i].data['grantInfoID']);
				}
			}
		}
		
		// SAGES
		if (_sagesRunMode == _self.MOD)
		{	
			var segesNode = IFDS.Xml.addSingleNode(updateXML, "RESPGrantUpd");
			IFDS.Xml.addSingleNode(segesNode, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(segesNode, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
			
			IFDS.Xml.addSingleNode(segesNode, 'grantType', _sagesInitValues['grantType']);
			IFDS.Xml.addSingleNode(segesNode, 'version', _sagesInitValues['version']);
			IFDS.Xml.addSingleNode(segesNode, 'runMode', _self.MOD);
			
			IFDS.Xml.addSingleNode(segesNode, 'applicationDate', _resources.fields['sages']['applicationDate'].getSMVDateString());
			IFDS.Xml.addSingleNode(segesNode, 'requestFlag', _resources.fields['sages']['requestFlag'].getValue());
			
			if (!Ext.isEmpty(_sagesCancelRequestProperty['fromDate'])){
				var cancelRequestNode = IFDS.Xml.addSingleNode(segesNode, "SAGESCancelRequest");
				IFDS.Xml.addSingleNode(cancelRequestNode, 'fromDate', 
					DesktopWeb.Util.getDateString(_sagesCancelRequestProperty['fromDate'], DesktopWeb.Util.getDateSmartviewFormat())
				);
				IFDS.Xml.addSingleNode(cancelRequestNode, 'toDate', 
					DesktopWeb.Util.getDateString(_sagesCancelRequestProperty['toDate'], DesktopWeb.Util.getDateSmartviewFormat())
				);
			}
		}		
		
		return updateXML;			
	}
	
	function sendACESValidateRequest(data, callback)
	{
		var viewParamXML = IFDS.Xml.newDocument("data");
		IFDS.Xml.addSingleNode(viewParamXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(viewParamXML, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
		IFDS.Xml.addSingleNode(viewParamXML, 'runMode', data['runMode']);
		IFDS.Xml.addSingleNode(viewParamXML, 'grantType', 'ACES');
		IFDS.Xml.addSingleNode(viewParamXML, 'stat', data['newStat']);
		IFDS.Xml.addSingleNode(viewParamXML, 'grantOpt', data['grantOpt']);
		IFDS.Xml.addSingleNode(viewParamXML, 'grantInfoID', data['grantInfoID']);
				
		DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Processing']);
		
		function responseHandler(success, responseXML)
		{			
			callback(success);														
		}												
	}
	
	function sendQESIValidateRequest(data, callback)
	{
		var viewParamXML = IFDS.Xml.newDocument("data");
		IFDS.Xml.addSingleNode(viewParamXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(viewParamXML, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
		IFDS.Xml.addSingleNode(viewParamXML, 'runMode', data['runMode']);
		IFDS.Xml.addSingleNode(viewParamXML, 'grantType', 'QESI');
		IFDS.Xml.addSingleNode(viewParamXML, 'newStat', data['newStat']);
		IFDS.Xml.addSingleNode(viewParamXML, 'grantYr', data['grantYr']);
		IFDS.Xml.addSingleNode(viewParamXML, 'grantInfoID', data['grantInfoID']);
		IFDS.Xml.addSingleNode(viewParamXML, 'stopReason', data['stopReason']);
				
		DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Processing']);
		
		function responseHandler(success, responseXML)
		{			
			callback(success);														
		}												
	}

	function sendCancelRequestSAGESValidateRequest(data, callback)
	{
		var viewParamXML = IFDS.Xml.newDocument("data");
		IFDS.Xml.addSingleNode(viewParamXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(viewParamXML, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
		IFDS.Xml.addSingleNode(viewParamXML, 'runMode', 'CancelRequest');
		IFDS.Xml.addSingleNode(viewParamXML, 'grantType', 'SAGES');
		IFDS.Xml.addSingleNode(viewParamXML, 'fromDate', DesktopWeb.Util.dateToString(data['fromDate']));
		IFDS.Xml.addSingleNode(viewParamXML, 'toDate', DesktopWeb.Util.dateToString(data['toDate']));
				
		DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Processing']);
		
		function responseHandler(success, responseXML)
		{			
			callback(success);														
		}												
	}

	function validateSAGES()
	{
		
		var isValid = true;
		if ( !Ext.getCmp('sagesFieldSet').hidden )
		{
			_self.handleSAGESChange();
			_resources.fields['sages']['fromDate'].clearInvalid();
			_resources.fields['sages']['toDate'].clearInvalid();
			
			isValid  = _resources.fields['sages']['applicationDate'].isValid()
		}
		
		return isValid;
	}	

	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		,sagesInitValues : _sagesInitValues
		
		,updatesFlag: false
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var viewParamXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(viewParamXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(viewParamXML, 'RESPBenefID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID']);
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, viewParamXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					_initDataXML = responseXML;					
					populateScreen();
				}											
			}															
		}
		
		,handleCESGChange: function()
		{
			_cesgRunMode = _self.MOD;
			_self.updatesFlag = true;
		}
		
		,handleCLBChange: function()
		{
			_clbRunMode = _self.MOD;
			_self.updatesFlag = true;
		}
		
		,getStatusOptions: function(grantType, curStat)
		{
			var listName = grantType.toUpperCase() + curStat;
			var listNode = IFDS.Xml.getNode(_initDataXML, '*/StatusOptions/List[@listName="' + listName + '"]')
			if (listNode)
			{
				return listNode
			}
			else
			{
				throw Error("No status list found for grant=" + grantType + ", curStat=" + curStat);
			}
		}
		
		,handleCESGStatusChange: function()
		{
			if (!(_resources.fields['cesg']['newStat'].getValue() == 'Requested'
				&& _cesgCurrStat == 'Requested'))
			{
				_self.handleCESGChange();
			}
			
			if (_resources.fields['cesg']['newStat'].getValue() == "Requested")
			{
				_resources.fields['cesg']['genRT511'].enable();
				_resources.fields['cesg']['cutOffDate'].enable();				
			}
			else
			{
				_resources.fields['cesg']['genRT511'].disable();
				_resources.fields['cesg']['genRT511'].setValue('no');				
				_resources.fields['cesg']['cutOffDate'].reset();
				_resources.fields['cesg']['cutOffDate'].disable();
			}
		}
		
		,handleRecordSelectChange: function(grantType)
		{
			var selectedRecord = _resources.grids[grantType].getSelectedRecord();
			if (selectedRecord)
			{				
				if (selectedRecord.data['runMode'] == _self.ADD)
				{
					_resources.grids[grantType].enableButton('delBtn');
				}
				else if (selectedRecord.data['allowStatUpd'] == 'yes' && _modPerm)
				{
					_resources.grids[grantType].enableButton('modBtn');
				}
			}
			else
			{
				_resources.grids[grantType].disableButton('modBtn');
				_resources.grids[grantType].disableButton('delBtn');
			}
		}
		
		,openActionPopup: function(grantType, action)
		{
			if (action == _self.ADD)
			{
				_resources.grids[grantType].clearSelectedRecord();
			}
			_resources.popups[grantType].init(action);
			_resources.popups[grantType].show();
		}
		
		,saveACESPopup: function(action, data)
		{			
			if (action == this.DEL)
			{
				callback(true);
			}
			else
			{
				sendACESValidateRequest(data, callback);
			}
						
			function callback(success)
			{
				if (success)
				{
					_acesUpdates = true;										
					_self.updatesFlag = true;
					
					if (action == _self.ADD)
					{
						_resources.grids['aces'].addRecord(data);				
						_resources.grids['aces'].selectLastRecord();			
					}
					else if (action == _self.MOD)
					{
						_resources.grids['aces'].updateSelectedRecord(data);
					}
					else
					{
						_resources.grids['aces'].removeSelectedRecord();	
					} 
					_resources.popups['aces'].hide();	
				}
			}										
		}
		
		,saveQESIPopup: function(action, data)
		{					
			if (action == this.DEL)
			{
				callback(true);
			}
			else
			{
				sendQESIValidateRequest(data, callback);
			}
						
			function callback(success)
			{
				if (success)
				{
					_qesiUpdates = true;										
					_self.updatesFlag = true;
					
					if (action == _self.ADD)
					{
						_resources.grids['qesi'].addRecord(data);				
						_resources.grids['qesi'].selectLastRecord();			
					}
					else if (action == _self.MOD)
					{
						_resources.grids['qesi'].updateSelectedRecord(data);
					}
					else
					{
						_resources.grids['qesi'].removeSelectedRecord();	
					} 
					_resources.popups['qesi'].hide();	
				}
			}										
		}
		
		,handleSAGESRequestFlagChange: function(requestFlag)
		{
			if (requestFlag == 'no') 
			{
				_resources.fields['sages']['applicationDate'].disable();
				_resources.fields['sages']['applicationDate'].clearInvalid();
				_resources.fields['sages']['applicationDate'].allowBlank = true;
				_resources.fields['sages']['applicationDate'].setValue(DesktopWeb.Util.stringToDate(_self.sagesInitValues['applicationDate']));
				
				_resources.fields['sages']['stopDate'].setValue(DesktopWeb.Util.getDateDisplayValue(_self.sagesInitValues['stopDate']));
			}
			else //if (requestFlag == 'yes') 
			{
				_resources.fields['sages']['applicationDate'].enable();
				_resources.fields['sages']['applicationDate'].allowBlank = false;
				
				if (!Ext.isEmpty(_self.sagesInitValues['requestFlag']) && _self.sagesInitValues['requestFlag'].toLowerCase() == 'yes')
				{
					_resources.fields['sages']['applicationDate'].setValue(DesktopWeb.Util.stringToDate(_self.sagesInitValues['applicationDate']));
					_resources.fields['sages']['stopDate'].setValue(DesktopWeb.Util.getDateDisplayValue(_self.sagesInitValues['stopDate']));
				}else{
					_resources.fields['sages']['applicationDate'].reset();
					_resources.fields['sages']['stopDate'].reset();
				}
			}
		}
		
		,handleSAGESChange: function()
		{
			for (var name in _resources.fields['sages']) 
			{
				if (_resources.fields['sages'][name] != _sagesInitValues[name])
				{
					_sagesRunMode = _self.MOD;
					_self.updatesFlag = true;
				}
			}
		}

		,validateScreen : function()
		{
			var isValid = validateSAGES();
			
			return isValid;
		}
		
		,validateSAGESCancelRequest: function()
		{
			var isValid = true;
			
			// Clear invalid before do validation
			_resources.popups['sagesCancelRequest'].getField('fromDate').clearInvalid();
			_resources.popups['sagesCancelRequest'].getField('toDate').clearInvalid();
			
			if(_resources.popups['sagesCancelRequest'].isValid()){
				var cancelRequestData = _resources.popups['sagesCancelRequest'].getData();
				if (cancelRequestData['fromDate'] > cancelRequestData['toDate']){
					_resources.popups['sagesCancelRequest'].getField('toDate').markInvalid(_translationMap['ERR_TODATE_CANNOT_LESS_THAN_FROMDATE']);
					isValid = false;
				}
			}else{
				isValid = false;
			}
			return isValid;
		}
		
		,saveSAGESCancelRequest: function(data)
		{
			sendCancelRequestSAGESValidateRequest(data, callback);
			
			function callback(success)
			{
				if (success)
				{
					_sagesRunMode = _self.MOD;
					_sagesCancelRequestProperty['fromDate'] = data['fromDate'];
					_sagesCancelRequestProperty['toDate'] = data['toDate'];
					
					if ( _sagesCancelRequestProperty['fromDate'] && _sagesCancelRequestProperty['toDate'] )
					{
						_resources.fields['sages']['fromDate'].setValue(
							DesktopWeb.Util.getDateString(_sagesCancelRequestProperty['fromDate'], DesktopWeb.Util.getDateDisplayFormat())
						);
						_resources.fields['sages']['toDate'].setValue(
							DesktopWeb.Util.getDateString(_sagesCancelRequestProperty['toDate'], DesktopWeb.Util.getDateDisplayFormat())
						);
						_resources.fields['sages']['fromDate'].show();
						_resources.fields['sages']['toDate'].show();
					}else{
						_resources.fields['sages']['fromDate'].reset();
						_resources.fields['sages']['toDate'].reset();
						_resources.fields['sages']['fromDate'].hide();
						_resources.fields['sages']['toDate'].hide();
						_sagesCancelRequestProperty['fromDate'] = null;
						_sagesCancelRequestProperty['toDate'] = null;
					}
					_resources.popups['sagesCancelRequest'].hide();
				}
			}
		}
		
		,populateCancelRequestPoupup: function()
		{
			if ( _sagesCancelRequestProperty['fromDate'] && _sagesCancelRequestProperty['toDate'] )
			{
				_resources.popups['sagesCancelRequest'].getField('fromDate').setValue(_sagesCancelRequestProperty['fromDate']);
				_resources.popups['sagesCancelRequest'].getField('toDate').setValue(_sagesCancelRequestProperty['toDate']);
			}else{
				_resources.popups['sagesCancelRequest'].getField('fromDate').reset();
				_resources.popups['sagesCancelRequest'].getField('toDate').reset();
			}
		}
		
		,openHistoricalPopup: function()
		{
			var viewParam = {};
			viewParam['auditType'] = 'RESPGrant';
			viewParam['searchValue1'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
			viewParam['searchValue2'] = DesktopWeb._SCREEN_PARAM_MAP['RESPBenefID'];
			var title = _translationMap['GrantInformation'] + "-" + _translationMap['History']
			
			_resources.popups['history'].init(title, 'dtHistRESPGrant', viewParam, true);			
			_resources.popups['history'].show();
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
									
			var updateXML = buildUpdateXML();
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, updateXML, responseHandler, null);
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
		
		,confirmAndCommitScreen: function()
		{
			if (_sagesCancelRequestProperty['fromDate'] && _sagesCancelRequestProperty['toDate'])
			{
				DesktopWeb.Util.displayPrompt(_translationMap['NOTI_CANCEL_REQUEST_CONFIRM'], confirmCancelRequest);
			}else{
				DesktopWeb.Util.commitScreen();
			}
			
			function confirmCancelRequest(buttonId)
			{
				if (buttonId == 'ok')
				{
					DesktopWeb.Util.commitScreen();
				}
			}
		}
	}	
}	