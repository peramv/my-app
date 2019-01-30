/*******************************************************************************
 * @file RDSPTransferIn.Controller.js
 * @author Usha S
 * @desc Controller JS file for Transfer In.
 ******************************************************************************/
DesktopWeb.ScreenController = function(){
	var _resources          = null;
	var _self               = null;
	var _extCntNum='',_extSpcmNum='',_nonTaxablePrivateCntbn='',_rollovers='';
	var _cdsGrant='',_cdsBond='',_fmv='',_allGrantBond='',_allCntbn='';
	var _priorNonTaxable='',_priorTaxable='',_currentNonTaxable='',_currentTaxable='';
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	function mandatoryFieldCheck(value){
		var validate="This field is mandatory";
    	if(value=="") {
    		return validate;
    	}
    }
	
	function goToScreen()
	{
		var params = {};
		params['fromScreen'] = 'RDSPNotionalActivity';
		params['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];

		if(DesktopWeb._SCREEN_PARAM_MAP['fromScreen']){
			DesktopWeb.Util.goToScreen(DesktopWeb._SCREEN_PARAM_MAP['fromScreen'],params);
		}else{
			DesktopWeb.Util.cancelScreen();
		}				
	}
	
	function updateTransfers(accountId, transactionId, fields)
	{
		var contextPath="transfers";
		var routePath="update/transaction/"+accountId + "/" + transactionId + "/transfer";
		var _service = "TransferUpdate";		
		var requestXML = IFDS.Xml.newDocument('body');
		
		IFDS.Xml.addSingleNode(requestXML, 'accountNumber', accountId);
		IFDS.Xml.addSingleNode(requestXML, 'transactionId', transactionId);
        IFDS.Xml.addSingleNode(requestXML, 'extRDSPContNum',fields['extRDSPContNum'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'extSpecimenPlanNum',fields['extSpecimenPlanNum'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'internalRDSPContNum',fields['internalRDSPContNum'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'internalSpecimenPlanNum',fields['internalSpecimenPlanNum'].getValue());
        IFDS.Xml.addSingleNode(requestXML, 'nonTaxablePrivateCntbns',numberFormatAmount(fields['nonTaxablePrivateCntbns'].getValue()));       
		IFDS.Xml.addSingleNode(requestXML, 'canadaDisabilitySavingsGrant', numberFormatAmount(fields['canadaDisabilitySavingsGrant'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'taxableReportsRollovers', numberFormatAmount(fields['taxableReportsRollovers'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'canadaDisabilitySavingsBond', numberFormatAmount(fields['canadaDisabilitySavingsBond'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'fairMarketValue', numberFormatAmount(fields['fairMarketValue'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'grantBondsPaid', numberFormatAmount(fields['grantBondsPaid'].getValue()));		
		IFDS.Xml.addSingleNode(requestXML, 'contributions',numberFormatAmount(fields['contributions'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'nonTaxablePriorDapLdap', numberFormatAmount(fields['nonTaxablePriorDapLdap'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'nonTaxablePresentDapLdap', numberFormatAmount(fields['nonTaxablePresentDapLdap'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'taxablePriorDapLdap', numberFormatAmount(fields['taxablePriorDapLdap'].getValue()));
		IFDS.Xml.addSingleNode(requestXML, 'taxablePresentDapLdap', numberFormatAmount(fields['taxablePresentDapLdap'].getValue()));		
		IFDS.Xml.addSingleNode(requestXML, 'esdcSent', fields['esdcSent'].getValue());		
		IFDS.Xml.addSingleNode(requestXML, 'esdcResponse',fields['esdcResponse'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'moneyOutTrade', fields['moneyOutTrade'].getValue());
		IFDS.Xml.addSingleNode(requestXML, 'transferInStatusTypeCode', fields['transferInStatusTypeCode'].getValue());
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST',DesktopWeb._SCREEN_PARAM_MAP,
			requestXML,responseHandlerSuccess,responseHandlerFailure);

		function responseHandlerSuccess(success, responseXML)
		{
			setTransfersDetails(success.responseXML);
			goToScreen();
		}

        function responseHandlerFailure(failure, responseXML) {
            DesktopWeb.Util.displayError("RDSP Transfer not saved. Please contact Administrator!!", callbackFn);
        }
	}
	
	function getTransfersDetails(){ 
		var accountId= DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		var transactionId= DesktopWeb._SCREEN_PARAM_MAP['TransactionId'];
		var contextPath="transfers";
		var routePath="transaction/"+accountId + "/" + transactionId + "/transfer";
		var _service = "TransactionIn";
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,
			null,responseHandlerSuccess,responseHandlerFailure);
        
		function responseHandlerSuccess(success, responseXML)
		{
			setTransfersDetails(success.responseXML);
			if((IFDS.Xml.getNodeValue(success.responseXML, '//rdspTrasactionTypeCode')) == '17' ) { // Enabled only for Transfer in
				_resources.fields['transferInStatusTypeCode'].show();
				}
			if(_resources.fields['formEditableFlag'].getValue() == 'false') {
				formPanel = Ext.getCmp('TransferInLayout');
				if ( (IFDS.Xml.getNodeValue(success.responseXML, '//rdspTrasactionTypeCode')) == '23' ) { // Enabled only for Transfer out
					_resources.fields['extRDSPContNum'].enable();
					_resources.fields['extSpecimenPlanNum'].enable();
				} else {
					_resources.fields['extRDSPContNum'].disable();
					_resources.fields['extSpecimenPlanNum'].disable();
				}				
				_resources.fields['nonTaxablePrivateCntbns'].disable();
				_resources.fields['canadaDisabilitySavingsGrant'].disable();				
				_resources.fields['taxableReportsRollovers'].disable();
				_resources.fields['canadaDisabilitySavingsBond'].disable();				
				_resources.fields['fairMarketValue'].disable();
				_resources.fields['grantBondsPaid'].disable();				
				_resources.fields['contributions'].disable();
				_resources.fields['nonTaxablePriorDapLdap'].disable();
				_resources.fields['nonTaxablePresentDapLdap'].disable();
				_resources.fields['taxablePriorDapLdap'].disable();				
				_resources.fields['taxablePresentDapLdap'].disable();
			}
		}

        function responseHandlerFailure(failure, responseXML) {
            DesktopWeb.Util.displayError("No RDSP Transfer returned. Please contact Administrator!", callbackFn);
		}
	}

    function callbackFn(buttonId){
        if(buttonId === 'ok')
        {
            goToScreen();
        }
    }
	function setTransfersDetails(response){
		_resources.fields['extRDSPContNum'].setValue(IFDS.Xml.getNodeValue(response, '//extRDSPContNum'));
		_resources.fields['extSpecimenPlanNum'].setValue(IFDS.Xml.getNodeValue(response, '//extSpecimenPlanNum'));
		_resources.fields['internalRDSPContNum'].setValue(IFDS.Xml.getNodeValue(response, '//internalRDSPContNum'));
		_resources.fields['internalSpecimenPlanNum'].setValue(IFDS.Xml.getNodeValue(response, '//internalSpecimenPlanNum'));
		_resources.fields['nonTaxablePrivateCntbns'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//nonTaxablePrivateCntbns')));
		_resources.fields['canadaDisabilitySavingsGrant'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//canadaDisabilitySavingsGrant')));
		_resources.fields['taxableReportsRollovers'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//taxableReportsRollovers')));
		_resources.fields['canadaDisabilitySavingsBond'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//canadaDisabilitySavingsBond')));
		_resources.fields['fairMarketValue'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//fairMarketValue')));
		_resources.fields['grantBondsPaid'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//grantBondsPaid')));
		_resources.fields['contributions'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//contributions')));
		_resources.fields['nonTaxablePriorDapLdap'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//nonTaxablePriorDapLdap')));
		_resources.fields['nonTaxablePresentDapLdap'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//nonTaxablePresentDapLdap')));
		_resources.fields['taxablePriorDapLdap'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//taxablePriorDapLdap')));
		_resources.fields['taxablePresentDapLdap'].setValue(commaSeperatedAmount(IFDS.Xml.getNodeValue(response, '//taxablePresentDapLdap')));
		_resources.fields['formEditableFlag'].setValue(IFDS.Xml.getNodeValue(response, '//formEditableFlag'));			
		_resources.fields['esdcSent'].setValue(IFDS.Xml.getNodeValue(response, '//esdcSent'));
		_resources.fields['esdcResponse'].setValue(IFDS.Xml.getNodeValue(response, '//esdcResponse'));
		_resources.fields['moneyOutTrade'].setValue(IFDS.Xml.getNodeValue(response, '//moneyOutTrade'));
		_resources.fields['accountNumber'].setValue(IFDS.Xml.getNodeValue(response, '//accountNumber'));
		_resources.fields['transactionId'].setValue(IFDS.Xml.getNodeValue(response, '//transactionId'));
		
		populateInitialValues();
		setTransferStatus(response);
		
	}
	
	function populateInitialValues() {
		 _extCntNum=_resources.fields['extRDSPContNum'].getValue();
		 _extSpcmNum=_resources.fields['extSpecimenPlanNum'].getValue();
		 _nonTaxablePrivateCntbn=_resources.fields['nonTaxablePrivateCntbns'].getValue();
		 _rollovers=_resources.fields['taxableReportsRollovers'].getValue();
		 _cdsGrant=_resources.fields['canadaDisabilitySavingsGrant'].getValue();
		 _cdsBond=_resources.fields['canadaDisabilitySavingsBond'].getValue();
		 _fmv=_resources.fields['fairMarketValue'].getValue();
		 _allGrantBond=_resources.fields['grantBondsPaid'].getValue();
		 _allCntbn=_resources.fields['contributions'].getValue();
		 _priorNonTaxable=_resources.fields['nonTaxablePriorDapLdap'].getValue();
		 _priorTaxable=_resources.fields['taxablePriorDapLdap'].getValue();
		 _currentNonTaxable=_resources.fields['nonTaxablePresentDapLdap'].getValue();
		 _currentTaxable=_resources.fields['taxablePresentDapLdap'].getValue();
	}
	
	function fieldsUpdated() {
		var _isUpdated = false;
		if(_extCntNum != _resources.fields['extRDSPContNum'].getValue() ||
		 _extSpcmNum != _resources.fields['extSpecimenPlanNum'].getValue() ||
		 _nonTaxablePrivateCntbn != _resources.fields['nonTaxablePrivateCntbns'].getValue() ||
		 _rollovers != _resources.fields['taxableReportsRollovers'].getValue() ||
		 _cdsGrant != _resources.fields['canadaDisabilitySavingsGrant'].getValue() ||
		 _cdsBond != _resources.fields['canadaDisabilitySavingsBond'].getValue() ||
		 _fmv != _resources.fields['fairMarketValue'].getValue() ||
		 _allGrantBond != _resources.fields['grantBondsPaid'].getValue() ||
		 _allCntbn != _resources.fields['contributions'].getValue() ||
		 _priorNonTaxable != _resources.fields['nonTaxablePriorDapLdap'].getValue() ||
		 _priorTaxable != _resources.fields['taxablePriorDapLdap'].getValue() ||
		 _currentNonTaxable != _resources.fields['nonTaxablePresentDapLdap'].getValue() ||
		 _currentTaxable != _resources.fields['taxablePresentDapLdap'].getValue())
		 {
			 _isUpdated = true;
		 }
		 return _isUpdated;
	}
	
	function inValidData() {
		if(_resources.fields['extRDSPContNum'].getValue() == '' ||
				 _resources.fields['extSpecimenPlanNum'].getValue() == '' ||
				 !isPositiveNumber(_resources.fields['nonTaxablePrivateCntbns'].getValue()) ||
				 !isPositiveNumber(_resources.fields['taxableReportsRollovers'].getValue()) ||
				 !isPositiveNumber(_resources.fields['canadaDisabilitySavingsGrant'].getValue()) ||
				 !isPositiveNumber(_resources.fields['canadaDisabilitySavingsBond'].getValue()) ||
				 !isPositiveNumber(_resources.fields['fairMarketValue'].getValue()) ||
				 !isPositiveNumber(_resources.fields['grantBondsPaid'].getValue()) ||
				 !isPositiveNumber(_resources.fields['contributions'].getValue()) ||
				 !isPositiveNumber(_resources.fields['nonTaxablePriorDapLdap'].getValue()) ||
				 !isPositiveNumber(_resources.fields['taxablePriorDapLdap'].getValue()) ||
				 !isPositiveNumber(_resources.fields['nonTaxablePresentDapLdap'].getValue()) ||
				 !isPositiveNumber(_resources.fields['taxablePresentDapLdap'].getValue()) )
		{
			return true;
		}
		return false;
	}
	
	function isPositiveNumber(amount) {
		var isValid = false;
		var decimalValue = null;
		amount = amount.replace(/,/g, '');
		
		if (!isNaN(amount) && amount >= 0)
		{
			if(amount.indexOf(".")!=-1) {
				decimalValue = amount.split(".")[1];
     		    if(decimalValue.length <=2) {
					 isValid = true;
				 }
			} else {
				isValid = true;
			}			
		}
		return isValid;
	}
	
	function numberFormatAmount(amount) {
		return amount.replace(/,/g, '');
	}
	
	function commaSeperatedAmount(amount) {
		return Ext.util.Format.number(amount, '0,000.00');
	}
	function setTransferStatus(response) {
		var statusCode = IFDS.Xml.getNodeValue(response, '//transferInStatusTypeCode');
		var statusField = _resources.fields['transferInStatusTypeCode'];
		if( statusCode == 'COMPLETE'){
			statusField.setValue(_translationMap['complete']);
		}else if(statusCode == 'INCOMPLETE'){
			statusField.setValue(_translationMap['incomplete']);
		}else if(statusCode == 'RECON_FAIL'){
			statusField.setValue(_translationMap['reconFail']);
		}else if(statusCode == 'RECON_REQ'){
			statusField.setValue(_translationMap['reconReq']);
		}else{
			statusField.setValue(_translationMap['incomplete']);
		}
	}
	
	return {
		init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			getTransfersDetails();
		}
		,doUpdate: function() {
			var accountId = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
			var transactionId= DesktopWeb._SCREEN_PARAM_MAP['TransactionId'];
			var fields = _resources.fields;

			updateTransfers(accountId, transactionId, fields);
		}
		,getTransfersDetails:getTransfersDetails
		,mandatoryFieldCheck:mandatoryFieldCheck
		,goToScreen:goToScreen
		,fieldsUpdated:fieldsUpdated
		,inValidData:inValidData
	}
};