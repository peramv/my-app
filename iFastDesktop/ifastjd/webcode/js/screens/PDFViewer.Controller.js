/*********************************************************************************************
 * @file	PDFViewer.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for SmartPDF Viewer screen
 *********************************************************************************************
 *  History :
 *
 *  30 Sept 2014 Narin Suanlamyai P0222874 FN00 T55886
 *					- Initialize
 *
 *  15 Oct 2014 Rod Walker P0222874 FN00 T55886
 *					- Fax via AWD
 *
 *  28 Oct 2014 Rod Walker P0222874 FN00 DFT0043432 T55887
 *					- Fix Fax via AWD button is not responsive.
 *
 *  07 Nov 2014 Rod Walker P0222874 FN00 DFT0043554 T55997
 *					- Update Fax via AWD function
 *
 *  17 Nov 2014 Narin Suanlamyai P0222874 FN00 DFT0044245 T56034
 *					- Adding TotalsRow to Tax Form is moved to SmartPDF.jar
 *
 *  24 Nov 2014 Rod Walker P0222874 FN00 DFT0044823 T56125
 *					- Mandatory Fax Input
 *
 *  29 Apr 2015 Aurkarn Mongkonrat P0241174 T80744
 *					- Add Email via AWD functionality.
 *
 *  20 May 2015 Aurkarn Mongkonrat P0241174 DFT0050962 T80845
 *					- Add CRPT parameter.
 * 
 *  29 Apr 2015 Aurkarn Mongkonrat P0241174 T80954 DFT0051578
 *                  - The Send button remains disabled.
 *
 *  21 Aug 2015 Narin Suanlamyai P0241174 T81250 DFT0052808
 *                  - Allow these special characters ('&', '/', '.', '-') for Recipient Name fields.
 *                  - Escape ampersand (&) before request AWD
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached. 
 *
 *  05 Sep 2018 Ravindra Prasad P0275095-180 TC-952
 *					- Changes for RRIF contribution receipt PDF to be viewed via 'View/Inquire in PDF' on YTD contribution window for plantype RIF. 
 *
 *  24 Sept 2018 Sreejith.A CHG0055141
 *					- “use iFast contact info” check box will be disabled and no default information will be populated on screen. 
 *
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){

	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var _PDF_TYPE_TAXFORM 					= 'TaxForm';
	var _PDF_TYPE_RSP_CONTRIBUTION_RECEIPT	= 'ContribRcptRSP';
	var _PDF_TYPE_RIF_CONTRIBUTION_RECEIPT  = 'ContribRcptRIF';
	var _PDF_TAXFORM_SERVICE				= 'dtTaxFormDtls';
	var _PDF_CONTRIBUTION_RECEIPT_SERVICE	= 'dtContribRcptDtls';
	var _ACCT_DETAILS_SERVICE				= "gnAcctDetailsInq";
	var _BROKER_DETAILS_SERVICE				= "gnBrokerInfoInq";
	var _REP_DETAILS_SERVICE				= "gnSlsRepInfoInq";

	var _clientId = null;
	var _dataXML = null;
	var _pdfType = null;
	var _formType = null;
	var _taxYear = null;
	var _locale = null;
	var _contactData = null;

	// PRIVATE METHODS ****************************************

	function getContactData()
	{
		var accountInfo = getAccountInfo();

		if (accountInfo.designation == "1") {
			// Client Account -> use Rep info
			_contactData = getRepContactData(accountInfo);
		} else if (accountInfo.designation == "2" || accountInfo.designation == "3") {
			// Nominee/Intermediate Account -> use Broker info
			_contactData = getBrokerContactData(accountInfo);
		}

		//setContactData();

		function getAccountInfo() {
			var accountInfo = {};
			var paramXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(paramXML, 'acct', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			DesktopWeb.Ajax.doSmartviewUpdate(_ACCT_DETAILS_SERVICE, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading'])

			function responseHandler(success, responseXML) {
				accountInfo.designation = IFDS.Xml.getNodeValue(responseXML, "//acctDsgn");
				accountInfo.brokerCode = IFDS.Xml.getNodeValue(responseXML, "//brokerCode");
				accountInfo.branchCode = IFDS.Xml.getNodeValue(responseXML, "//branchCode");
				accountInfo.repCode = IFDS.Xml.getNodeValue(responseXML, "//slsRepCode");
			}
			return accountInfo;
		}

		function getRepContactData(accountInfo) {
			var contactData = {};
			var paramXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(paramXML, 'brokerCode', accountInfo.brokerCode);
			IFDS.Xml.addSingleNode(paramXML, 'branchCode', accountInfo.branchCode);
			IFDS.Xml.addSingleNode(paramXML, 'slsRepCode', accountInfo.repCode);
			DesktopWeb.Ajax.doSmartviewUpdate(_REP_DETAILS_SERVICE, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading'])

			function responseHandler(success, responseXML) {
				var name = IFDS.Xml.getNodeValue(responseXML, "//slsRepName").split(";");
				contactData.firstName = name[1];
				contactData.lastName = name[0];
				contactData.email = IFDS.Xml.getNodeValue(responseXML, "//email");
				contactData.number = IFDS.Xml.getNodeValue(responseXML, "//busFax").replace(")", "-").replace("(", "")
			}
			return contactData;
		}

		function getBrokerContactData(accountInfo) {
			var contactData = {};
			var paramXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(paramXML, 'brokerCode', accountInfo.brokerCode);
			DesktopWeb.Ajax.doSmartviewUpdate(_BROKER_DETAILS_SERVICE, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading'])

			function responseHandler(success, responseXML) {
				var name = IFDS.Xml.getNodeValue(responseXML, "//contact").split(";");
				contactData.firstName = name[1];
				contactData.lastName = name[0];
				contactData.email = IFDS.Xml.getNodeValue(responseXML, "//email");
				contactData.number = IFDS.Xml.getNodeValue(responseXML, "//busFax").replace(")", "-").replace("(", "");
			}
			return contactData;
		}
	}

	function getTaxFormData(txPComRid, isManual, taxYear)
	{
		var taxFormData = null;
		var paramXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(paramXML, 'acct', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(paramXML, 'txPComRid', txPComRid);
		IFDS.Xml.addSingleNode(paramXML, 'isManual', isManual);
		IFDS.Xml.addSingleNode(paramXML, 'taxYear', taxYear);

		DesktopWeb.Ajax.doSmartviewUpdate(_PDF_TAXFORM_SERVICE, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading'])

		function responseHandler(success, responseXML)
		{
			if (success){
				taxFormData = IFDS.Xml.cloneDocument(responseXML);
			}
		}
		return taxFormData;
	}

	function getContributionReceiptData(year, rcpNum)
	{
		var contribRcptData = null;
		var paramXML = IFDS.Xml.newDocument('data');

		IFDS.Xml.addSingleNode(paramXML, 'acct', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(paramXML, 'year', year);
		IFDS.Xml.addSingleNode(paramXML, 'rcptNum', rcpNum);

		DesktopWeb.Ajax.doSmartviewUpdate(_PDF_CONTRIBUTION_RECEIPT_SERVICE, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading'])

		function responseHandler(success, responseXML)
		{
			// hanldle response
			if (success){
				contribRcptData = IFDS.Xml.cloneDocument(responseXML);

				// Customize for Contribution Receipt
				var contribReceiptNode = IFDS.Xml.getNode(contribRcptData, '//ContribReceipts/ContribReceipt');
				var annuitAddrNode = IFDS.Xml.getNode(contribReceiptNode, 'annuitAddr1');
				var annuitAddr = (annuitAddrNode)?IFDS.Xml.getNodeValue(contribReceiptNode, 'annuitAddr1'):null;
				//var annuitName = IFDS.Xml.getNode(contribReceiptNode, 'annuitName');
				var annuitNameNode = IFDS.Xml.getNode(contribReceiptNode, 'annuitName');
				var annuitName = (annuitNameNode)?IFDS.Xml.getNodeValue(contribReceiptNode, 'annuitName'):null;
				if (annuitName){
					if (annuitAddr && annuitAddr.length > 0) {
						IFDS.Xml.addSingleNode(contribReceiptNode, 'annuitNameNotSame', annuitName);
					} else {
						IFDS.Xml.addSingleNode(contribReceiptNode, 'annuitNameSame', annuitName);
					}
				}
			}
		}
		return contribRcptData;
	}

	function loadPDF()
	{
		if (_dataXML) {
			var xmlStr = IFDS.Xml.serialize(_dataXML);
			try {
				var pdfForm = document.getElementById("SmartPDF-form");
				DesktopWeb.Util.addHiddenToForm(pdfForm, "service", "generate");
				DesktopWeb.Util.addHiddenToForm(pdfForm, "taxDataXML", xmlStr);
				DesktopWeb.Util.addHiddenToForm(pdfForm, "clientId", _clientId);
				DesktopWeb.Util.addHiddenToForm(pdfForm, "formType", _formType);
				DesktopWeb.Util.addHiddenToForm(pdfForm, "taxYear", _taxYear);
				DesktopWeb.Util.addHiddenToForm(pdfForm, "locale", _locale);
				pdfForm.target = "pdfFrame";
				pdfForm.submit();
			} catch(e){}
		}
	}

	function showPDFFrame() {
		document.getElementById("pdfFrame").style.display = "block";
	}

	function hidePDFFrame() {
		document.getElementById("pdfFrame").style.display = "none";
	}
	
	function setContactData() {
		if (_contactData) {
		_resources.fields.fax.firstName.setValue(_contactData.firstName);
		_resources.fields.fax.lastName.setValue(_contactData.lastName);
		_resources.fields.fax.faxNum.setValue(_contactData.number);
		
		_resources.fields.email.firstName.setValue(_contactData.firstName);
		_resources.fields.email.lastName.setValue(_contactData.lastName);
		_resources.fields.email.emailAddr.setValue(_contactData.email);
		
		_self.disableFaxInputs();

		if (_contactData.email == "") {
			_resources.fields['email']['ifastContact'].disable();
			_resources.buttons['email']['sendBtn'].disable();
			_self.enableEmailInputs();
		}
		else {
			_self.disableEmailInputs();
		}
				
		} else {
			_self.enableFaxInputs();
			_self.enableEmailInputs();
			
			_resources.fields['fax']['ifastContact'].disable();
			_resources.buttons['fax']['sendBtn'].disable();
			
			_resources.fields['email']['ifastContact'].disable();
			_resources.buttons['email']['sendBtn'].disable();
		}
	}
	


	// PUBLIC ITEMS *************************************
	return {
		updatesFlag: true //always want to execute the update, regardless of changes on screen

		,init: function(res)
		{
			
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;

			_clientId = DesktopWeb._SCREEN_PARAM_MAP['companyCode'];
			_pdfType = DesktopWeb._SCREEN_PARAM_MAP['pdfType'];
			_taxYear = DesktopWeb._SCREEN_PARAM_MAP['taxYear'];
			_locale = DesktopWeb._SCREEN_PARAM_MAP['locale'];

			if (_pdfType === _PDF_TYPE_TAXFORM) {
				_formType = DesktopWeb._SCREEN_PARAM_MAP['formLink'];
				_dataXML = getTaxFormData(DesktopWeb._SCREEN_PARAM_MAP['txPComRid'],
											DesktopWeb._SCREEN_PARAM_MAP['isManual'], _taxYear);
			} else {
				if (_pdfType === _PDF_TYPE_RSP_CONTRIBUTION_RECEIPT) {
					_formType = 'CR';					
				} else if (_pdfType === _PDF_TYPE_RIF_CONTRIBUTION_RECEIPT) { 
					_formType = 'CRRIF';					
				}
				_dataXML = getContributionReceiptData(DesktopWeb._SCREEN_PARAM_MAP['year'],
										DesktopWeb._SCREEN_PARAM_MAP['rcpNum']);
				_resources.buttons['backBtn'].hide();
			}
			loadPDF();
			getContactData();

			// following timer "hacks" required, because Adobe plugin makes buttons
			// unresponsive while document is loading & rendering
			var timer = window.setInterval(checkPDFLoaded, 100);
			function checkPDFLoaded() {
				var iframe = document.getElementById("pdfFrame");
				var iframeDoc = iframe.document
				if (iframeDoc.readyState == "complete") {
					window.clearInterval(timer);
					window.setTimeout(enableAWDPanel, 1250);
				}
			}

			function enableAWDPanel() {
				_resources.buttons['fax']['faxBtn'].enable();
				_resources.buttons['email']['emailBtn'].enable();
				
				_resources.buttons['fax']['faxBtn'].focus();
			}
		}
		
		,setContactData: function() {
			setContactData();
		}

		// Fax Panel
		,showFaxPrompt: function() {
			document.getElementById("faxPrompt").style.display = "block";
			document.getElementById("pdfFrame").style.height = "345px"; //415 - 70 = 345
		}

		,hideFaxPrompt: function() {
			document.getElementById("faxPrompt").style.display = "none";
			document.getElementById("pdfFrame").style.height = "415px"; //345 + 70= 415
		}

		,enableFaxInputs: function() {
			_resources.fields['fax']['ifastContact'].setValue(false);
			_resources.fields['fax']['firstName'].enable();
			_resources.fields['fax']['lastName'].enable();
			_resources.fields['fax']['faxNum'].enable();
		}

		,disableFaxInputs: function() {
			_resources.fields['fax']['ifastContact'].setValue(true);
			_resources.fields['fax']['firstName'].disable();
			_resources.fields['fax']['lastName'].disable();
			_resources.fields['fax']['faxNum'].disable();
		}
		
		// Email Panel
		,showEmailPrompt: function() {
			document.getElementById("emailPrompt").style.display = "block";
			document.getElementById("pdfFrame").style.height = "345px"; //415 - 70 = 345
		}

		,hideEmailPrompt: function() {
			document.getElementById("emailPrompt").style.display = "none";
			document.getElementById("pdfFrame").style.height = "415px"; //345 + 70= 415
		}

		,enableEmailInputs: function() {
			_resources.fields['email']['ifastContact'].setValue(false);
			_resources.fields['email']['firstName'].enable();
			_resources.fields['email']['lastName'].enable();
			_resources.fields['email']['emailAddr'].enable();
		}

		,disableEmailInputs: function() {
			_resources.fields['email']['ifastContact'].setValue(true);
			_resources.fields['email']['firstName'].disable();
			_resources.fields['email']['lastName'].disable();
			_resources.fields['email']['emailAddr'].disable();
		}

		,returnToTaxSlips: function()
		{
			var params = {};
			var screenName = DesktopWeb._SCREEN_PARAM_MAP['srcScreen'];

			DesktopWeb.Util.goToScreen(screenName, params);
		}

		,updateFaxSendBtn: function() {
			if (_resources.fields['fax']['faxNum'].isValid() &&
				_resources.fields['fax']['lastName'].isValid() &&
				_resources.fields['fax']['firstName'].isValid()) 
            {
				_resources.buttons['fax']['sendBtn'].enable();
			} else 
            {
				_resources.buttons['fax']['sendBtn'].disable();
			}
		}
		
		,updateEmailSendBtn: function() {
			if (_resources.fields['email']['lastName'].isValid() &&
				_resources.fields['email']['firstName'].isValid() &&
				_resources.fields['email']['emailAddr'].isValid())
			{
				_resources.buttons['email']['sendBtn'].enable();
			} 
			else 
			{
				_resources.buttons['email']['sendBtn'].disable();
			}
		}

		,sendAWDRequest: function(serviceType) {
			var params = {};
            var recieptName = _resources.fields[serviceType]['lastName'].getValue() + ";" + _resources.fields[serviceType]['firstName'].getValue();
            recieptName = recieptName.replace(/&/g, '&amp;');
            if (serviceType == 'fax') {
				params = {
							service: serviceType,
							faxNum: _resources.fields['fax']['faxNum'].getValue().replace( /\D/g, ""),
                            faxName: recieptName,
							emailAddr: "",
							RCPT: _formType,
							account: DesktopWeb._SCREEN_PARAM_MAP['AccountNum'],
							envName: DesktopWeb._SCREEN_PARAM_MAP['envName'],
							sessionId: DesktopWeb._SCREEN_PARAM_MAP['sessionId']
				};			
			}
			else if (serviceType == 'email') {
				params = {
							service: serviceType,
							faxNum: "",
                            faxName: recieptName,
							account: DesktopWeb._SCREEN_PARAM_MAP['AccountNum'],
							emailAddr: _resources.fields['email']['emailAddr'].getValue(),
							RCPT: _formType,
							envName: DesktopWeb._SCREEN_PARAM_MAP['envName'],
							sessionId: DesktopWeb._SCREEN_PARAM_MAP['sessionId']
				};
			}
				
			hidePDFFrame();
			DesktopWeb.Util.displayProcessing(_translationMap["ProcMsg_Processing"]);
			Ext.Ajax.request(
				{
					url: "/tf/smartpdf"
					,params: params
					,success: responseHandler
					,failure: errorHandler
					,method: "POST"
					,timeout: 90000
				}
			);

			function responseHandler(response) {
				DesktopWeb.Util.hideProcessing();
				var responseXML = response.responseXML;
                
                var awdObjId = IFDS.Xml.getNodeValue(responseXML, "objId");
				if (awdObjId) {
					DesktopWeb.Util.displayInfo(_translationMap["CreatedAWDObject"], callback);
				} else {
					DesktopWeb.Util.displayError(_translationMap["ErrorCreatingAWDObject"], callback);
				}

				function callback() {				
					showPDFFrame();
				}
			}

			function errorHandler() {
                DesktopWeb.Util.hideProcessing();
				DesktopWeb.Util.displayError(_translationMap["ErrorCreatingAWDObject"], callback);
				function callback() {
					showPDFFrame();
				}
			}
		}
	}
}