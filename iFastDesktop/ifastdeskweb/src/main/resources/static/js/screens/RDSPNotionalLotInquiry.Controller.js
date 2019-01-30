/*********************************************************************************************
 * @file	RDSPNotionalLotInquiry.Controller.js
 * @author	Usha S
 * @desc	Controller JS file for NotionalLotDetailsInquiry.
 *********************************************************************************************/
DesktopWeb.ScreenController = function(){
	var _resources          = null;
	var _self               = null;
	var notionalCategory;
	var transactionType;
	var accountNum;
	var toDate;
	var fromDate;
	var inceptionDate;
	
	var transTypeList,transTypeGrBdList,transactionTypeListAll,notionalCategoryList;

	/** Load All Dropdown Lists **/
	function populateDropdownList(dom){
		transactionTypeListAll = IFDS.Xml.getNode(dom, "//List[@listName='transactionTypeAll']");
		notionalCategoryList=IFDS.Xml.getNode(dom, "//List[@listName='notionalCategory']");
		
		if (transactionTypeListAll)
		{
			_resources.fields['TransactionTypeField'].loadData(transactionTypeListAll);
		}
		
		if (notionalCategoryList)
		{
			_resources.fields['NotionalCategoryField'].loadData(notionalCategoryList);
			
		}
		transTypeGrBdList=IFDS.Xml.getNode(dom, "//List[@listName='transactionTypeGrBd']");
		transTypeList=IFDS.Xml.getNode(dom, "//List[@listName='transactionType']");

		if(notionalCategory!=null && notionalCategory!="" && notionalCategory!='undefined') {
			_resources.fields['NotionalCategoryField'].setValue(notionalCategory);
			_resources.fields['TransactionTypeField'].setValue(transactionType);
			
		} else {
			_resources.fields['TransactionTypeField'].setValue('All');
			_resources.fields['NotionalCategoryField'].setValue('All');
		}
		if(toDate){
			_resources.fields['ToField'].setValue(toDate);
		}
		_resources.fields['FromField'].setValue(fromDate);
		
		
		getNotionalLotActivityDetails(0,_resources.pageSize);
	}
	
	function setTransTypeList(code){
		_resources.fields['TransactionTypeField'].getStore().removeAll();
		if(code == '01' || code == '02'){
			_resources.fields['TransactionTypeField'].loadData(transTypeGrBdList);
		}
		else if(code == '03' || code == '04' || code == '05')
		{
			_resources.fields['TransactionTypeField'].loadData(transTypeList);
		}
		else 
		{
			_resources.fields['TransactionTypeField'].loadData(transactionTypeListAll);
		}
	}
	
	function validateFromDate(value){
		var incDate = DesktopWeb.Util.stringToDate(inceptionDate,'dmy');
		var valueFromDate=DesktopWeb.Util.stringToDate(value,'dmy');
		if(_resources) {
		var valueToDate=DesktopWeb.Util.stringToDate(_resources.fields['ToField'].getDisplayDateString(),'dmy');
		//  change this to real inception date
		
		if(valueToDate < valueFromDate)
		{
			return 'Trade From Date cannot be later than Trade To Date';
		}	
		if(incDate > valueFromDate)
			{
			return 'Trade From Date must not be prior to Account Inception date';
			}		
		}
		return true;
	}
	function validateToDate(value){
		var incDate = DesktopWeb.Util.stringToDate(inceptionDate,'dmy');
		var valueToDate=DesktopWeb.Util.stringToDate(value,'dmy');
		if(_resources == undefined || _resources == null || _resources == "") {
		} else {
			var valueFromDate=DesktopWeb.Util.stringToDate(_resources.fields['FromField'].getDisplayDateString(),'dmy');
	
			if(valueToDate < valueFromDate)
			{
				return 'Trade To Date cannot be prior to Trade From Date';
			}	
			if(incDate > valueToDate)
				{
				return 'Trade To Date must not be prior to Account Inception date';
				}		
		}
		return true;
	}
	
	function getNotionalLotActivityDetails(start, count){
		var transNum = _resources.fields['TransactionNumberField'].getValue();
		var lotId = _resources.fields['LotIDField'].getValue();

		if(transNum!=null && transNum !="" && transNum!='undefined') { 
			DesktopWeb._SCREEN_PARAM_MAP.TransactionNumber = transNum;
			DesktopWeb._SCREEN_PARAM_MAP.NotionalCategory="";
			DesktopWeb._SCREEN_PARAM_MAP.TransactionType="";
			DesktopWeb._SCREEN_PARAM_MAP.FromDate="";
			DesktopWeb._SCREEN_PARAM_MAP.ToDate="";
			DesktopWeb._SCREEN_PARAM_MAP.LotId="";
		}

		else if(lotId!=null && lotId !="" && lotId!='undefined') {
			DesktopWeb._SCREEN_PARAM_MAP.LotId = lotId;
			DesktopWeb._SCREEN_PARAM_MAP.NotionalCategory="";
			DesktopWeb._SCREEN_PARAM_MAP.TransactionType="";
			DesktopWeb._SCREEN_PARAM_MAP.FromDate="";
			DesktopWeb._SCREEN_PARAM_MAP.ToDate="";
			DesktopWeb._SCREEN_PARAM_MAP.TransactionNumber="";
		} else { 
			DesktopWeb._SCREEN_PARAM_MAP.LotId = "";
			DesktopWeb._SCREEN_PARAM_MAP.TransactionNumber = "";
			DesktopWeb._SCREEN_PARAM_MAP.NotionalCategory=_resources.fields['NotionalCategoryField'].getValue();
			DesktopWeb._SCREEN_PARAM_MAP.TransactionType=_resources.fields['TransactionTypeField'].getValue();
			DesktopWeb._SCREEN_PARAM_MAP.FromDate=_resources.fields['FromField'].getDisplayDateString();
			DesktopWeb._SCREEN_PARAM_MAP.ToDate=_resources.fields['ToField'].getDisplayDateString();
		}
		DesktopWeb._SCREEN_PARAM_MAP.start = start;
		DesktopWeb._SCREEN_PARAM_MAP.count = count;
		var contextPath="notional";
		var routePath="lotActivity";
		
		JRDSP.Util.sendRequestToDesktopWeb('notional',routePath,'','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandlerSuccess, responseHandlerFailure);
		
		var records;
		function responseHandlerSuccess(success, responseXML) {
			var grid = _resources.grids['RDSPTransactionDetailsGrid'];
			inceptionDate = IFDS.Xml.getNodeValue(success.responseXML, '//inceptionDate');
			if(_resources.fields['FromField'].getValue()==null || _resources.fields['FromField'].getValue()=="") {
				_resources.fields['FromField'].setValue(inceptionDate);
			}
			var records_count;
			if(start) {
				var store = grid.getStore();
				records = IFDS.Xml.getNodes(success.responseXML, '//notionalLotActivityDetails');
				records_count = start+records.length;

				for (var i = 0; i < records.length; i++) {
					var record = {};
					
					for(var j = 0; j < records[i].childNodes.length; ++j) {
						record[records[i].childNodes[j].nodeName] = records[i].childNodes[j].nodeTypedValue;
						record.checked = false;
						record.changed = false;
					}

					store.add(new store.recordType(record));
				}
			}
			else {
				var store = grid.getStore();
				records = IFDS.Xml.getNodes(success.responseXML, '/NotionalLotActivityDetailsResponse');
				store.loadData(records, false);
				grid.getSelectionModel().selectRow(0);
				records_count = store.getCount();
			}
			if (records_count < _resources.pageSize || records.length ==0) {
				_resources.buttons['moreBtn'].disable();
			}
			else {
				_resources.buttons['moreBtn'].enable();
			}	
		}

        function responseHandlerFailure(failure, responseXML) {
            DesktopWeb.Util.displayError("No RDSP Notional Lot details found. Please contact Administrator!");
		}
	}

	function goToScreen()
	{
		var params = {};
	
		params['NotionalCategory'] = ""; 
		params['TransactionType'] = ""; 	
		params['toDate'] = "";
		params['fromDate'] = "";		
		params['fromScreen'] = DesktopWeb._SCREEN_PARAM_MAP['fromScreen'];
		params['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
	
		if(DesktopWeb._SCREEN_PARAM_MAP['fromScreen']){
			DesktopWeb.Util.goToScreen(DesktopWeb._SCREEN_PARAM_MAP['fromScreen'],params);
		}else{
			DesktopWeb.Util.cancelScreen();
		}				
	}
	
	function refresh() {
        _resources.grids['RDSPTransactionDetailsGrid'].getStore().removeAll();
        getNotionalLotActivityDetails();
	}
	
	function getLotIdBalances(data) {
		var routePath="getLotIdBalances/"+data['lotId'];
		JRDSP.Util.sendRequestToDesktopWeb('notional',routePath,'','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandlerSuccess);
		
		var records;
		function responseHandlerSuccess(success, responseXML) {
			_resources.fields['OriginalAmountLabel'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//purchase'));
			_resources.fields['DepletedAmountLabel'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//redemption'));
			_resources.fields['BalanceLabel'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//balance'));
			_resources.fields['LotIdLabel'].setValue(IFDS.Xml.getNodeValue(success.responseXML, '//lotId'));
		}
      /*  function responseHandlerFailure(failure, responseXML) {
            DesktopWeb.Util.displayError("No RDSP Notional Lot ID Balances found. Please contact Administrator!");
		}*/
		
	}
	
	return {
		init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			JRDSP.Util.sendRequestToDesktopWeb('notional','getNotionalLotConfig','','POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,dropDownResponseHandler);
			notionalCategory = DesktopWeb._SCREEN_PARAM_MAP['NotionalCategory'];
			transactionType = DesktopWeb._SCREEN_PARAM_MAP['TransactionType'];
			accountNum = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
			toDate = DesktopWeb._SCREEN_PARAM_MAP['ToDate'];
			fromDate = DesktopWeb._SCREEN_PARAM_MAP['FromDate'];

			function dropDownResponseHandler(success, responseXML){
				populateDropdownList(success.responseXML);
			}

		},
		setTransTypeList:setTransTypeList,
		populateDropdownList:populateDropdownList,
		validateFromDate:validateFromDate,
		validateToDate:validateToDate,
		getNotionalLotActivityDetails:getNotionalLotActivityDetails,
		goToScreen:goToScreen,
		refresh:refresh,
		getLotIdBalances:getLotIdBalances
	}
};
