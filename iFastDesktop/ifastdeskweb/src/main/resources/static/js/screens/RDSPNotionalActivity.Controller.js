/*********************************************************************************************
 * @file	RDSPNotionalActivity.Controller.js
 * @author	Tomasz Przada
 * @desc	Controller JS file for RDSPNotionalActivity.
 *********************************************************************************************/

DesktopWeb.ScreenController = function(){
	// PRIVATE VARIABLES *************************************
	
	var _translationMap     = DesktopWeb.Translation.getTranslationMap();
	var _self               = null;
	var _resources          = null;
	var _popupList		     = {};
	
	var _beneDOB ;
	var _incepDate;
	var _minDate;
	var _dropDownResponse;
	
	
	var depositDescList,redemptionDescList,descriptionList,transferInDescList,refileSuppressList;

	/** Load All Dropdown Lists **/
	function populateDropdownList(dom){
		var transactionTypeListNode = IFDS.Xml.getNode(dom, "//List[@listName='transactionType']");
		if (transactionTypeListNode)
		{
			_resources.fields['TransactionTypeField'].loadData(transactionTypeListNode);


		}
		descriptionList=IFDS.Xml.getNode(dom, "//List[@listName='description']");
		depositDescList=IFDS.Xml.getNode(dom, "//List[@listName='descriptionDeposit']");
		redemptionDescList=IFDS.Xml.getNode(dom, "//List[@listName='descriptionRedemption']");
		transferInDescList=IFDS.Xml.getNode(dom, "//List[@listName='descriptionTransferIn']");
		
		
		if (descriptionList)
		{
			_resources.fields['DescriptionField'].loadData(descriptionList);
			
		}

		_resources.fields['TransactionTypeField'].setValue('All');
		_resources.fields['DescriptionField'].setValue('All');
		
		refileSuppressList=IFDS.Xml.getNode(dom, "//List[@listName='refilesupress']");
		_resources.fields['refileSuppressField'].loadData(refileSuppressList);
		
	}

	function initResources(){
		_resources.buttons['fileScreenButton'].disable();
		_resources.buttons['okScreenButton'].disable();
		
	}

	function clickHandle_RdspTransfer() {
		var params = {};
		params['TransactionId'] = DesktopWeb._SCREEN_PARAM_MAP['TransactionId']; 
		params['screen'] = 'RDSPTransferIn';
		goToScreen('RDSPTransferIn', params);
	}
	
	function clickHandle_RdspNotionalBalance() {
		var params = {};
		params['screen'] = 'RDSPNotionalBalance';
		goToScreen('RDSPNotionalBalance', params);
	}
	
	function clickHandle_RdspNotionalLotDetail(){
		var params = {};
		params['screen'] = 'RDSPNotionalLotInquiry';
		goToScreen('RDSPNotionalLotInquiry', params);
	}
	
	function goToScreen(screenName, params)
	{    
		params['fromScreen'] = 'RDSPNotionalActivity';
		params['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		
		DesktopWeb.Util.goToScreen(screenName, params);
	}
	
	function getTransactionDetails(){
		var accountId= DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		var contextPath="accountService";
		var routePath="transactions/"+accountId;

		var TransactionNumber= DesktopWeb._SCREEN_PARAM_MAP['TransNum'];
		var NotionalCategory= DesktopWeb._SCREEN_PARAM_MAP['NotionalCategory'];
		var TransactionType=DesktopWeb._SCREEN_PARAM_MAP['TransactionType'];
		
		var Description=DesktopWeb._SCREEN_PARAM_MAP['Description'];
		
		var FromDate=DesktopWeb._SCREEN_PARAM_MAP['FromDate'];
		var ToDate=DesktopWeb._SCREEN_PARAM_MAP['ToDate'];
		
		
		
		var _service = "AcctInq";
		
		JRDSP.Util.sendRequestToDesktopWeb('notional',routePath,'','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);

		//JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);
		
		function responseHandler(success, responseXML)
		{
			
			_resources.fields['BeneficaryNameLabel'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//beneficiaryName'));
			if (TransactionNumber) {
			_resources.fields['TransactionNumberField'].setValue(TransactionNumber);
			
			_resources.fields['TransactionTypeField'].disable();
			_resources.fields['DescriptionField'].disable();
			_resources.fields['FromField'].disable();
			_resources.fields['ToField'].disable();
			
			
			}
			
			_resources.grids['RDSPTransactionHistoryDetailsGrid'].getStore().loadData(IFDS.Xml.getNodes(success.responseXML, '//transactions'),true);
		}
	}
	
	
	function getNotionalDetails(data){
		
		//TODO : add acct Num to hidden

		var accountId= DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		var contextPath="notionalActivityService";
		var routePath="activity/"+accountId +"/"+data['transactionId'] ;

		DesktopWeb._SCREEN_PARAM_MAP['TransactionId']= data['transactionId']; 
	
		JRDSP.Util.sendRequestToDesktopWeb('notional',routePath,'','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);

		//JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);
		
		function responseHandler(success, responseXML)
		{
			var redemption = IFDS.Xml.getNodeValue(success.responseXML,'//rdspTransactionTypeCode') == '07' ;
			
			_resources.fields['ContributionAmount'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//contributionAmount'));
			_resources.fields['GrantAmount'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//grantAmount'));
			_resources.fields['BondAmount'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//bondAmount'));
			_resources.fields['RspAmount'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//rspAmount'));
			_resources.fields['RespAmount'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//respAmount'));
			_resources.fields['RolloverAmount'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//totalRolloverAmount'));
			_resources.fields['BondPaymentDate'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//bondPaymentDate'));
			_resources.fields['AssociatedGrantTransactionNumber'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//transNumber'));
			_resources.fields['AssociatedGrantAmount'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//amount'));
			_resources.fields['PaymentDate'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//paymentDate'));
			_resources.fields['GrantPaymentDate'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//grantPaymentDate'));
			_resources.fields['RepaymentReason'].setValue(_translationMap[IFDS.Xml.getNodeValue(success.responseXML, '//repaymentReason')]);
			var rdspTransactionTypeCode = IFDS.Xml.getNodeValue(success.responseXML, '//rdspTransactionTypeCode');
		    var hasAssocGrant = false;
		    
		    if (_resources.fields['AssociatedGrantAmount'].getValue()) {
		    	hasAssocGrant = true;
		    }		    
		
			switch(rdspTransactionTypeCode) {

			case "19":
				//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		    	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    
		    	//Money-In Purchase with Grant Rec'd
		    	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(false);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(false);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    		
		    		_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
			    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
			    	_resources.fields['PaymentDate'].setVisible(false);
		        break;
		    case "01":
		    	
		    	
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		    	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    
		    	//Money-In Purchase with Grant Rec'd
		    	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(true);
		    	_resources.fields['GrantPaymentDate'].setVisible(true);
		    	_resources.fields['BondAmount'].setVisible(false);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	
		    	if (hasAssocGrant === true) {
		    		
		    		Ext.getCmp('assocGrantFieldSet').setVisible(true);
		    				    		
		    		_resources.fields['AssociatedGrantTransactionNumber'].setVisible(true);
			    	_resources.fields['AssociatedGrantAmount'].setVisible(true);
			    	_resources.fields['PaymentDate'].setVisible(true);
		    	} else {
		    		_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
			    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
			    	_resources.fields['PaymentDate'].setVisible(false);
		    	}
		    	
		    	
		    
		    	
		        break;
		    case "02":
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    	
		    	//Money-In Purchase with Grant Rec'd
		    	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(true);
		    	_resources.fields['GrantPaymentDate'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondAmount'].setVisible(false);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    	
		    	
		   
		    	break;
		    case "22":
		    case "03":
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    	
		    	
		    	// Money In Bond Purchase
		    	_resources.fields['ContributionAmount'].setVisible(false);
		    	_resources.fields['GrantAmount'].setVisible(false);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(true);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    
		     	
		     	break; 
		    case "21":
		    case "15":
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    	
		    	// Money In Grant Purchase
		    	_resources.fields['ContributionAmount'].setVisible(false);
		    	_resources.fields['GrantAmount'].setVisible(true);
		    	_resources.fields['GrantPaymentDate'].setVisible(true);
		    	_resources.fields['BondAmount'].setVisible(false);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(true);
		    	
		    	
		     	
		        break;
		    case "23":
		    case "17":
		    	
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].enable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    	
		    	// Money-In RDSP External Transfer In
		     	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(true);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(true);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    
		    	
		    	break;
		    case "07":
		    	
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    	
		    	// Money-Out Redemption (DAP/LDAP) with AHA
		       	_resources.fields['ContributionAmount'].setVisible(false);
		    	_resources.fields['GrantAmount'].setVisible(true);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    	
		    	
		    	
		        break;
		    case "18":
		    	
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].enable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    	
		    	// Money-Out RDSP External Transfer Out
		    	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(true);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(true);
		    	_resources.fields['RespAmount'].setVisible(true);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		     	_resources.fields['PaymentDate'].setVisible(false);
		    	
		     	
		        break;
		    case "09":
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    
		    	// Money-Out Redemption (DAP/LDAP)
		    	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(true);
		     	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(true);
		    	_resources.fields['RespAmount'].setVisible(true);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    	
		    	
		   
		        break;
		    case "10":
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		   
		    	// Money-Out Redemption (DAP/LDAP)
		    	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(true);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(true);
		    	_resources.fields['RespAmount'].setVisible(true);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    
		    	
		        break;    
		    case "13":
		    	
		    	//RESP
		    	
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		   
		    	_resources.fields['ContributionAmount'].setVisible(false);
		    	_resources.fields['GrantAmount'].setVisible(false);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(false);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(true);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    
		    	
		        break;
		    case "05":
		    	
		    	//RSP
		    	
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		   
		    	_resources.fields['ContributionAmount'].setVisible(false);
		    	_resources.fields['GrantAmount'].setVisible(false);
		    	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(false);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(true);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    
		    	
		        break;  
		    case "20":
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    
		    	// Money-Out Redemption (Termination Withdrawl)
		    	_resources.fields['ContributionAmount'].setVisible(true);
		    	_resources.fields['GrantAmount'].setVisible(true);
		     	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(true);
		    	_resources.fields['RespAmount'].setVisible(true);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    	
		    	
		   
		        break;
		    case "24":
		    	//enable button
		    	_resources.buttons['rdspTransferScreenButton'].disable();
		       	Ext.getCmp('notionalDetailsFieldSet').setVisible(true);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
		    
		    	// Money-Out Redemption (Termination Adjustment  Grant & Bond)
		    	_resources.fields['ContributionAmount'].setVisible(false);
		    	_resources.fields['GrantAmount'].setVisible(true);
		     	_resources.fields['GrantPaymentDate'].setVisible(false);
		    	_resources.fields['BondAmount'].setVisible(true);
		    	_resources.fields['RepaymentReason'].setVisible(redemption);
		    	_resources.fields['BondPaymentDate'].setVisible(false);
		    	_resources.fields['RspAmount'].setVisible(false);
		    	_resources.fields['RespAmount'].setVisible(false);
		    	_resources.fields['RolloverAmount'].setVisible(false);
		    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
		    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
		    	_resources.fields['PaymentDate'].setVisible(false);
		    	
		    	
		   
		        break;
		    default:
			    Ext.getCmp('notionalDetailsFieldSet').setVisible(false);
		    	Ext.getCmp('assocGrantFieldSet').setVisible(false);
			    	
			_resources.fields['ContributionAmount'].setVisible(false);
	    	_resources.fields['GrantAmount'].setVisible(false);
	    	_resources.fields['GrantPaymentDate'].setVisible(false);
	    	_resources.fields['BondAmount'].setVisible(false);
	    	_resources.fields['RepaymentReason'].setVisible(redemption);
	    	_resources.fields['BondPaymentDate'].setVisible(false);
	    	_resources.fields['RspAmount'].setVisible(false);
	    	_resources.fields['RespAmount'].setVisible(false);
	    	_resources.fields['RolloverAmount'].setVisible(false);
	    	_resources.fields['AssociatedGrantTransactionNumber'].setVisible(false);
	    	_resources.fields['AssociatedGrantAmount'].setVisible(false);
	    	_resources.fields['PaymentDate'].setVisible(false);
			
		}
		}
	}
	
	function getUpdatedRecordCount()
	{
		var store = _resources.grids['rdspElectionsGrid'].getStore();
		
		var result =
			store.query('runMode', _self.ADD).length +
			store.query('runMode', _self.MOD).length +
			store.query('runMode', _self.DEL).length;
		return result;
	}
	
	function filterGrid(){
		
		
		
		var transNumber=_resources.fields['TransactionNumberField'].getValue();
		var transType= _resources.fields['TransactionTypeField'].getValue();
		var description = _resources.fields['DescriptionField'].getValue();
		var fromDate = _resources.fields['FromField'].getValue();
		var toDate=_resources.fields['ToField'].getValue();
		
		
		
		var accountId= DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		var contextPath="accountService";
		var routePath="transactions/"+accountId;

		DesktopWeb._SCREEN_PARAM_MAP['TransNum']=transNumber;
		DesktopWeb._SCREEN_PARAM_MAP['NotionalCategory']=1;
		
		DesktopWeb._SCREEN_PARAM_MAP['TransactionType']=transType;
		DesktopWeb._SCREEN_PARAM_MAP['Description']=description;
		DesktopWeb._SCREEN_PARAM_MAP['FromDate']=_resources.fields['FromField'].getDisplayDateString();
		DesktopWeb._SCREEN_PARAM_MAP['ToDate']=_resources.fields['ToField'].getDisplayDateString();
		
		if(transType == 'All' ){

			DesktopWeb._SCREEN_PARAM_MAP['TransactionType'] = "";
		}
			
		if(description == 'All' ){
			
			DesktopWeb._SCREEN_PARAM_MAP['Description'] = "";
		}
		
		var _service = "AcctInq";
		
		JRDSP.Util.sendRequestToDesktopWeb('notional',routePath,'','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);

		//JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);
		
		function responseHandler(success, responseXML)
		{
			_resources.grids['RDSPTransactionHistoryDetailsGrid'].getStore().removeAll();
			 _resources.grids['RDSPTransactionHistoryDetailsGrid'].getStore().loadData(IFDS.Xml.getNodes(success.responseXML, '//transactions'),true);
		}
	}
	
	
	function getTransactionTypeValue(code){
		switch(code){
			case "ED":
				return "Purchase";
			case "PW":
			case "AW":	
				return "Redemption";
			case "TI":
				return "Transfer-In";
			default:
				return code;
		}
		
		
				
	}
	
	function getDescription(record){
		var descCode=record.data.iFastTransactionType;
		if(record.data.depositCode != null)
			descCode=descCode+record.data.depositCode;
		if(record.data.redemptionCode != null)
			descCode=descCode+record.data.redemptionCode;
		return _translationMap[descCode];
		
	}
	
	
	function getTransTypeValue(code){
		
		switch (code){
		case 'ALL':
			return 'All';
		case 'ED':
			return 'Purchases';
		default :
			return code;
	}	
		
	}

	
	function getTransactionStatusDescription(transactionStatus) {
		
		switch (transactionStatus){
		case '01':
			return _translationMap['Processed'];
		case '02':
			return _translationMap['Pending'];
		case '03':
			return _translationMap['Cancelled'];	
		case '04':
			return _translationMap['Reversed'];	
		default :
			return transactionStatus;
	}	
	}	
		
	function getEsdcTransStatusDescription(esdcTransStatus) {
		if (esdcTransStatus) {
            return _translationMap[esdcTransStatus];
        } else {
			return '';
        }
	}
	
	function setDescList(code){
		if(code == 'ED'){
			_resources.fields['DescriptionField'].getStore().removeAll();
			_resources.fields['DescriptionField'].loadData(depositDescList);
			
			
		}
	else if(code == 'PW'){
		_resources.fields['DescriptionField'].getStore().removeAll();
		_resources.fields['DescriptionField'].loadData(redemptionDescList);
		}
	else if(code == 'TI'){
		_resources.fields['DescriptionField'].getStore().removeAll();
		_resources.fields['DescriptionField'].loadData(transferInDescList);
		}
	else
		{
		_resources.fields['DescriptionField'].getStore().removeAll();
		_resources.fields['DescriptionField'].loadData(descriptionList);
		
		}
	}
	



function updateCdspRegistraion() {
    var contextPath="notionalActivityService";
	var refileSupress = _resources.fields['refileSuppressField'].getValue();
	var gridRecords=_resources.grids['RDSPTransactionHistoryDetailsGrid'].getStore();
	gridRecords.clearFilter(false);
    var transIds = [];
		if (gridRecords.data.items.length > 0) {
			for (var i = 0; i < gridRecords.data.items.length; i++) {
				if (gridRecords.data.items[i].data.checked) {
					if(gridRecords.data.items[i].data.ESDCTransStatus != 'SENT'){
						transIds.push(gridRecords.data.items[i].data.transactionId);
					} else {
						DesktopWeb.Util.displayError('Action not allowed');
						return;
					}
					
				}
			}
		}
		var routePath="updateCdspRegistraion/"+refileSupress +"/"+transIds ;

		JRDSP.Util.sendRequestToDesktopWeb('notional',routePath,'','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);
		function responseHandler(success, responseXML){
			if(success){
				DesktopWeb.Util.displayInfo('Refile/Suppress Successful');
			} else {
				DesktopWeb.Util.displayError('Error occured. Please try again');
			}
		}
	}

	// PUBLIC ITEMS *************************************
	return {
		 ADD				: 'a'
		,MOD				: 'm'
		,DEL				: 'd'
		,UNCHANGE			: 'u'
		,INQ				: 'inq'
		,VAL				: 'val'
		,UPD				: 'upd'
		,ERROR				: 'error'
		,BLANK				: ''
		,FUND_LEVEL			: '01'
		,FUNDGROUP_LEVEL	: '02'
		,LEGALENTITY_LEVEL	: '03'
		,BROKER_LEVEL		: '04'
		,INTERMEDIARY_LEVEL	: '05'
		,YES				: 'yes'
		,NO					: 'no'
		,SEPERATOR			: ';'
		,NO_REPORTINGFFI    : '03'
		,YES_REPORTINGFFI	: '02'
		,DEFAULT_ENV_REPORTINGFFI : '01'
		,REPORTING_UNIT_REPORTINGFFI: '04'
		,FI_SPONSOR			: '05'
		,NO_THRESHOLD	    : '02'
		,updatesFlag		: false
		,NEWFFI				: 'NEWFFI'
		,NEWIDEN			: 'NEWIDEN'
		,REGULATIONCODECRSRP: 'CRSRP'
		,REGULATIONCODEFATCA: 'FA'
		,GROUPTYPECRSRP		: 'CRS'
		,GROUPTYPEFATCA		: 'FATCA'
		,minDate:_minDate
		,dropDownResponse: _dropDownResponse


		,init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			JRDSP.Util.sendRequestToDesktopWeb('notional','getConfig','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);

			function responseHandler(success, responseXML){
				_dropDownResponse=success.responseXML;
				populateDropdownList(_dropDownResponse);
			}
			getTransactionDetails();

		}
		,cdspUpdate: updateCdspRegistraion
		,goToScreen:goToScreen
		,getTransactionDetails:getTransactionDetails
		,getNotionalDetails:getNotionalDetails
		,filterGrid:filterGrid
		,clickHandle_RdspTransfer:clickHandle_RdspTransfer
		,clickHandle_RdspNotionalBalance:clickHandle_RdspNotionalBalance
		,getTransactionStatusDescription: getTransactionStatusDescription
		,getTransactionTypeValue: getTransactionTypeValue
		,getDescription :getDescription
		,getEsdcTransStatusDescription: getEsdcTransStatusDescription
		,setDescList:setDescList
		,depositDescList:depositDescList
		,redemptionDescList:redemptionDescList
		,transferInDescList:transferInDescList
		,clickHandle_RdspNotionalLotDetail : clickHandle_RdspNotionalLotDetail
	}
};