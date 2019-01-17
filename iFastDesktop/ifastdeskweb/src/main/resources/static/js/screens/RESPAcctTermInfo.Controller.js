/*********************************************************************************************
 * @file	RESPAcctTermInfo.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for RESP Account Termination Entries screen.
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *  30 Apr 2014 G. Thawornwachirakun P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *  30 May 2014 Narin Suanlamyai P0220132 FN03 DFT0034351 T55198
 *					- Disable SAGES fields for non-SAGES environment
 *
 *  21 Jul 2014 Narin Suanlamyai P0220132 FN03 DFT0037101 T55450
 *					- Hide SAGES section for non-SAGES environment.
 *
 *  12 Nov 2015 Aurkarn Mongkonrat P0241773 FN01 T81710 DFT0056104 
 *					- Fix to show BCTESG on RESP Termination Adjustment screen.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.   
 *
 *	14 Jun 2016 Watchara Th. P0241773 CHG0045794 DFT0064894 T83084
 *					- Ignored unexpected error message when accessing the screen.
 *
 *  29 Jan 2018 Simona Pop P0275389 
 *  				- RESP Phase 3 enhancements - RESP Termination.
 *
 *  20 Mar 2018 Simona Pop P0275389 
 *                  - Description change for Reversal record
 *
 *
 *  21 Mar 2018 Simona Pop P0275389 
 *  				- Updates to termination adjustment transactions buttons logic.
 *
 *  17 Jan 2019 Alka CHG0057330 
 *  				- Added 'userAction' to capture grid action as 'runMode' is shared with status column on grid. 
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var _MOD = "mod";
	var _DEL = "del";
	var _CANCEL = "canc";
	var _REVERSED = "rvsl";
	
	var _modPerm = null;
	var _delPerm = null;
	var _runPerm = null;
	
	var _selectedEntry = null;
	var _RESPTermInfoXML = null;
	
	var _screenConfigurations = null;
	var _respBenefId = null;

	var _defaultObject = null
	
	var _dtRESPTermintnReloadService = 'dtRESPTermintnReload';
	var _dtRESPTermintnVldtnService = 'dtRESPTermintnVldtn';
	var _dtRESPTermintnUpdService = 'dtRESPTermintnUpd';
	
	var _nextStartRecNum = 1;
	var _requestRecNum = 100;
	
	var _SPECIAL_TAX_REPAYMENT 	= "06";
	var _GRANT_REPAYMENT 		= "21";
	var _TERMINATION_ADJUSTMENT = "22";
		
	// PRIVATE METHODS ****************************************	
	function loadRESPAcctTermInfo(){
		var paramXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(paramXML, 'AccountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(paramXML, 'RESPBenefID');
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', _nextStartRecNum);
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);
		
		clearGrid('termDetlGrid');
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtRESPTermintnReloadService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading'], null, ['00015']);

		function responseHandler(success, responseXML)
		{			
			if (success && IFDS.Xml.getNode(responseXML, '//RESPAccountInfo'))
			{
				_RESPTermInfoXML = responseXML;
			}
			else
			{
				_RESPTermInfoXML = null;
			}
			
			if(_RESPTermInfoXML)
			{
				setPermission(IFDS.Xml.getNode(_RESPTermInfoXML, '//userPermissions'));
				loadScreenConfigurations();
				
				displayRESPAcctTermInfo();
			}
		}
	}
	
	function displayRESPAcctTermInfo(){
		displayRESPAccountInfo(IFDS.Xml.getNode(_RESPTermInfoXML, '//RESPAccountInfo'));
		_resources.popups['detailsPopup'].get('detlSec').get('sagesSec').setVisible(_screenConfigurations['showSAGES']);
        _resources.popups['detailsPopup'].get('detlSec').get('bctesgSec').setVisible(_screenConfigurations['showBCTESG']);
		_resources.grids['termDetlGrid'].getStore().loadData(_RESPTermInfoXML);
	}
	
	function displayRESPAccountInfo(acctInfoXML){
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
			_resources.fields['termDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(acctInfoXML, 'termDate')));
		}
	}
	
	function doEntrySave(popup)
	{
		var validateXml = buildValidateXMLFromPopup(popup);
		
		sendValidation( _dtRESPTermintnVldtnService, validateXml, successHandler, errorHandler);
		
		function successHandler()
		{
			updateTermEntryLayout(popup);
			popup.hide();
		}
		
		function errorHandler(responseXML)
		{
			// Error Handling
		}
	}
	
	function updateTermEntryLayout(popup)
	{
		_selectedEntry.set('userAction', popup.action);	
		_selectedEntry.set('runMode', popup.action);	
		_selectedEntry.set('transDate', popup.getField('transDateFld').getDisplayDateString());
		_selectedEntry.set('amt', popup.getField('amtFld').getValue());
		_resources.grids['termDetlGrid'].getStore().commitChanges();
		if(popup.action = _DEL)
		{
			_selectedEntry = null;
			if(_resources.grids['termDetlGrid'].getStore().getCount() > 0)
			{
				_resources.grids['termDetlGrid'].getSelectionModel().selectFirstRow();
			}
			updateTermEntriesButtons();
		}
		_self.updatesFlag = true;
	}
	
	function updateTermEntriesButtons()
	{
		var grid = _resources.grids['termDetlGrid'];
		if ( _selectedEntry )
		{
			if ( _modPerm && _modPerm == "yes" ) {
				if (_selectedEntry.get('runMode') == _CANCEL) {
					grid.disableButton('ModifyBtn');
					grid.disableButton('CancelBtn');
				}
				else {
				    if (_selectedEntry.get('reported').toLowerCase() == "yes") {
				        grid.disableButton('ModifyBtn');
				        if ( (_selectedEntry.get('transType')).substring(0, 2) == _SPECIAL_TAX_REPAYMENT  || // 06
                             (_selectedEntry.get('transType')).substring(0, 2) == _TERMINATION_ADJUSTMENT || // 22
                             (_selectedEntry.get('runMode')) == _REVERSED)
                        {
				            grid.disableButton('CancelBtn');
				        }
				        else {
				            grid.enableButton('CancelBtn');
				        }
					}
				    else {				       
				        grid.enableButton('ModifyBtn');
				        // allow T06 modification only when the associated non-financial 21 record has been reported
				        if ((_selectedEntry.get('transType')).substring(0, 2) == _SPECIAL_TAX_REPAYMENT) {	// 06			       
				        	if (!enableModify())			    
				        	    grid.disableButton('ModifyBtn');
				        }		

						grid.disableButton('CancelBtn');
				    }
				}
			}
			
			if ( _delPerm && _delPerm == "yes" ) 
			{
				if ( _selectedEntry.get('reported').toLowerCase() == 'yes' )
				{
					grid.disableButton('DeleteBtn');
				}
				else
				{
				    if ( (_selectedEntry.get('transType')).substring(0, 2) == _SPECIAL_TAX_REPAYMENT  || // 06
                         (_selectedEntry.get('transType')).substring(0, 2) == _TERMINATION_ADJUSTMENT || // 22
                         (_selectedEntry.get('runMode')) == _CANCEL)
				    {
				        grid.disableButton('DeleteBtn');
				    }
				    else {
				        grid.enableButton('DeleteBtn');
				    }
				}				
			}

			grid.enableButton('ExpandBtn');
			
			if ((_selectedEntry.get('transType')).substring(0, 2) == _TERMINATION_ADJUSTMENT) { // 22
				grid.disableButton('ModifyBtn');
				grid.disableButton('DeleteBtn');
			    grid.disableButton('CancelBtn');
			    if (enableModify())			    	
			    	grid.enableButton('ModifyBtn');
			}			
			else if ((_selectedEntry.get('transType')).substring(0, 2) == _SPECIAL_TAX_REPAYMENT) { // 06			
				grid.disableButton('ModifyBtn');
			    grid.disableButton('DeleteBtn');
			    grid.disableButton('CancelBtn');			  
			    			 
			    // allow T06 modification only when dateSent is blank and there are 21 records where amount is zero and dateSent is not blank		
			    if (DesktopWeb.Util.getSMVDateValue(_selectedEntry.get('dateSent')) == '')
			    {				    	
			    	if (enableModify())			    
			    		grid.enableButton('ModifyBtn');			    	
			    }					
			}
			
			if ((_selectedEntry.get('runMode')) == _REVERSED) {
				grid.disableButton('CancelBtn');
			} 
			else if ((_selectedEntry.get('runMode')) == _CANCEL) {
				grid.disableButton('ModifyBtn');
				grid.disableButton('DeleteBtn');
			}						
			
		}else{
			grid.disableButton('ExpandBtn');
			grid.disableButton('ModifyBtn');
			grid.disableButton('DeleteBtn');
			grid.disableButton('CancelBtn');
		}
	}
		
	function buildValidateXMLFromPopup(popup)
	{	
		var xml = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(xml, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] );
		IFDS.Xml.addSingleNode(xml, "respBenefId", _respBenefId );
		IFDS.Xml.addSingleNode(xml, "runMode", popup.action );
		IFDS.Xml.addSingleNode(xml, "transType", _selectedEntry.get('transType') );
		IFDS.Xml.addSingleNode(xml, "transDate", popup.getField('transDateFld').getSMVDateString());
		IFDS.Xml.addSingleNode(xml, "hrdcTransId", _selectedEntry.get('hrdcTransId') );
		IFDS.Xml.addSingleNode(xml, "dateSent", DesktopWeb.Util.getSMVDateValue(_selectedEntry.get('dateSent') ));
		IFDS.Xml.addSingleNode(xml, "amt", popup.getField('amtFld').getValue() );		
		IFDS.Xml.addSingleNode(xml, "reported", _selectedEntry.get('reported') );
		IFDS.Xml.addSingleNode(xml, "normalRvrse", _selectedEntry.get('normalRvrse') );
		IFDS.Xml.addSingleNode(xml, "eventlogdetluuid", _selectedEntry.get('eventDetlUUID') );
		
		return xml;	
	}
	
	function buildUpdateXML()
	{
		var store = _resources.grids['termDetlGrid'].getStore();
		var modRecs = store.queryBy(getModifiedRecords);
		
		var updateXml = IFDS.Xml.newDocument('data');
		
		modRecs.each(function(modRec){
			
			var entryXML = IFDS.Xml.addSingleNode( updateXml, "TermintnUpd");
			IFDS.Xml.addSingleNode(entryXML, "runMode", modRec.get('runMode') );
			IFDS.Xml.addSingleNode(entryXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] );
			IFDS.Xml.addSingleNode(entryXML, "respBenefId", _respBenefId );
			IFDS.Xml.addSingleNode(entryXML, "transType", modRec.get('transType') );
			IFDS.Xml.addSingleNode(entryXML, "transDate", DesktopWeb.Util.getSMVDateValue(modRec.get('transDate') ));
			IFDS.Xml.addSingleNode(entryXML, "hrdcTransId", modRec.get('hrdcTransId') );
			IFDS.Xml.addSingleNode(entryXML, "dateSent", DesktopWeb.Util.getSMVDateValue(modRec.get('dateSent') ));
			IFDS.Xml.addSingleNode(entryXML, "amt", modRec.get('amt') );			
			IFDS.Xml.addSingleNode(entryXML, "reported", modRec.get('reported') );
			IFDS.Xml.addSingleNode(entryXML, "normalRvrse", modRec.get('normalRvrse') );
			IFDS.Xml.addSingleNode(entryXML, "cesg", modRec.get('cesg') );
			IFDS.Xml.addSingleNode(entryXML, "clb", modRec.get('clb') );
			IFDS.Xml.addSingleNode(entryXML, "pGrant", modRec.get('pGrant') );
			IFDS.Xml.addSingleNode(entryXML, "sages", modRec.get('sages') );			
			IFDS.Xml.addSingleNode(entryXML, "eventlogdetluuid", modRec.get('eventDetlUUID') );
		});
		
		return updateXml;	
		
		function getModifiedRecords(record)
		{
			return record.get('userAction') != '';		
		}
	}

	function sendValidation(api, xml, successCallback, errorCallback)
	{
		DesktopWeb.Ajax.doSmartviewAjax(api, null, xml, responseHandler, _translationMap['ProcMsg_Validating']);
					
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				successCallback();
			}
			else
			{												
				errorCallback(responseXML);				
			}			
		}
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
	
	function loadScreenConfigurations()
	{
		_screenConfigurations = new Array();
		
		_screenConfigurations['showSAGES'] = IFDS.Xml.getNodeValue(_RESPTermInfoXML, '//showSAGES').toLowerCase() == 'yes';
        _screenConfigurations['showBCTESG'] = IFDS.Xml.getNodeValue(_RESPTermInfoXML, '//showBCTESG').toLowerCase() == 'yes';
	}
	
	function enableModify ()
	{
		var store = _resources.grids['termDetlGrid'].getStore();
		var count = store.getCount();		
		var i = 0;
		while (i < count)
		{			
			if ((store.getAt(i).get('transType')).substring(0, 2) == _GRANT_REPAYMENT) // 21
			{	
			    if (store.getAt(i).get('reported').toLowerCase() == "yes" && store.getAt(i).get('financial').toLowerCase() == "no") // reported non-financial
			    {	
			    	return true;
			    }
			}
			i++;
		}
		
		return false;
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		MODIFY: _MOD
		,DELETE: _DEL
		,CANCEL: _CANCEL
		,REVERSED: _REVERSED
		,SPECIAL_TAX_REPAYMENT: _SPECIAL_TAX_REPAYMENT
		,updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			loadRESPAcctTermInfo();
		}
		
		,openActionPopup: function(name, action)
		{		
			var popup = _resources.popups[name];
			popup.init(action);
			popup.show();
		}
		
		,entryUpdate: function(popup)
		{
			doEntrySave(popup);
		}
		
		,doUpdate: function()
		{
			var updateStatus = null;
			var updateXML = buildUpdateXML();
			
			if(updateXML){
				DesktopWeb.Ajax.doSmartviewUpdate(_dtRESPTermintnUpdService, null, IFDS.Xml.cloneDocument(updateXML), responseHandler, _translationMap['ProcMsg_Saving']);
			}
			
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
		
		,setSelectedEntry: function(record)
		{
			_selectedEntry = record;
			updateTermEntriesButtons();
		}
		
		,getSelectedEntry: function()
		{
			return _selectedEntry;
		}
	}	
}	
