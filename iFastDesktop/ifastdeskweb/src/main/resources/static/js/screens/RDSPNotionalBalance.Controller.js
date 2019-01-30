DesktopWeb.ScreenController = function(){
	
	var _resources          = null;
	var _self               = null;
	var _inceptionDate      = null;
	var _accountNumber = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _cycleDate;
	var incpDate;
	var _cycleDate;
		
	function validateAsOfDate(value){
		var valueDate=DesktopWeb.Util.stringToDate(value,'dmy');
		var inceptionDate=DesktopWeb.Util.stringToDate(this._inceptionDate,'dmy'); 
		if(valueDate != null && valueDate < inceptionDate) {
			return 'As of Date must be on or after Inception Date!';
		}
		return true;
	}
	
	function getNotionalBalance(screenLoad) {
		this._accountNumber = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		var contextPath="notional";
		var routePath="user/" + DesktopWeb._SCREEN_PARAM_MAP['ruserId'] + "/balance/"+this._accountNumber;
		
		var _service = "NotionalBalance";
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler, responseHandlerFailure);
        
		function responseHandler(success, responseXML) {
			if(screenLoad) {
				setIntials(success.responseXML);
			} 
			setNotionalBalance(success.responseXML);
		}
		setCycleDate(_cycleDate);
		
		function responseHandlerFailure(response, options) {
			DesktopWeb.Util.displayError( " Data not found . Please contact Administrator!!", callbackFn);
			
			function callbackFn(buttonId){
				if(buttonId == 'ok'){
		setCycleDate(_cycleDate);
				}
			}
 	 	}
		
	}
	
	function setIntials(response) {
		_resources.fields['beneficaryName'].setValue(IFDS.Xml.getNodeValue(response, '//beneName'));
		_resources.fields['period'].loadData(IFDS.Xml.getNode(response, "//list[@listName='periodList']"));	
		this._inceptionDate = IFDS.Xml.getNodeValue(response, '//inceptionDate');
		incpDate = this._inceptionDate;
        _resources.fields['asOfDate'].minValue = DesktopWeb.Util.stringToDate(this._inceptionDate,'dmy');
	}
	
	function setMarketValues(response) {
        _resources.fields['marketValue'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//marketValue')));
        _resources.fields['income'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//income')));
        _resources.fields['aha'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//assistanceHoldBack')));
	}
	
	function setAnnualAmounts(response) {
        _resources.fields['taxExemptionBalance'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//taxExemptionBalance')));
        _resources.fields['taxableRedemptions'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//taxableRedemptions')));
        _resources.fields['sdspMaximum'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//sdspMaxTaxablePortion')));
        _resources.fields['jan1FMV'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//jan1Fmv')));
        _resources.fields['ldapMaximum'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//ldapMax')));
        _resources.fields['pgap'].setValue(IFDS.Xml.getNodeValue(response, '//pgap'));
        _resources.fields['pgapMaximum'].setValue(getCurrencyValue(IFDS.Xml.getNodeValue(response, '//pgapMax')));
	}
	
	function setNotionalBalance(response) {
		_resources.grids['contributionCategory'].getStore().loadData(IFDS.Xml.getNodes(response, '//contributionsList'),false);
		_resources.grids['grantBondCategory'].getStore().loadData(IFDS.Xml.getNodes(response, '//grantsBondsList'),false);
		_resources.grids['limitsDetail'].getStore().loadData(IFDS.Xml.getNodes(response, '//limitsList'),false);
		 setMarketValues(response);
	     setAnnualAmounts(response);
	}
	
	function initScreenValue() {
		JRDSP.Util.sendRequestToDesktopWeb("configService","getConfiguration",null,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler,responseHandlerFailure);
		
 	 	function responseHandler(success, responseXML) {       
	 	 	var configList = IFDS.Xml.getNodes(success.responseXML, '//configList/configuration');
	 	 	var cycleDateFromService;
	 	 	for(var i=0;i<configList.length;i++){
		 	 	if(configList[i].childNodes[0].childNodes[0].data == 'NEXT-NR'){
		 	 		cycleDateFromService = configList[i].childNodes[1].childNodes[0].data;
		 	 	}
	 	 	}
	 	 	
	 	 	_cycleDate = JRDSP.Util.convertStringToDate(cycleDateFromService);
		JRDSP.Util.sendRequestToDesktopWeb("configService","getConfiguration",null,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler,responseHandlerFailure);
 	 	function responseHandler(success, responseXML)
 	 	{       
 	 	var configList = IFDS.Xml.getNodes(success.responseXML, '//configList/configuration');
 	 	var cycleDateFromService;
 	 	for(var i=0;i<configList.length;i++){
 	 	if(configList[i].childNodes[0].childNodes[0].data == 'NEXT-NR'){
 	 		cycleDateFromService = configList[i].childNodes[1].childNodes[0].data;
 	 	}
 	 	}
 	 	_cycleDate = JRDSP.Util.convertStringToDate(cycleDateFromService);
	 	 	 _resources.fields['period'].enable();
	         _resources.fields['periodRadio'].enable();
	         _resources.fields['asOfRadio'].enable();
	         _resources.fields['periodRadio'].setValue(true);
	         _resources.fields['period'].setValue("Life to Date");
	         _resources.fields['annualAmounts'].setFieldLabel(_translationMap['AnnualAmounts'] + getYearFromDate(_cycleDate));
	         
	         Ext.get('Annual_Amounts').setStyle('backgroundColor','#dddddd');
	         
	         DesktopWeb._SCREEN_PARAM_MAP['toDate'] = "Life to Date";
	         DesktopWeb._SCREEN_PARAM_MAP['cycleDate'] = _cycleDate;
	         getNotionalBalance(true);
 	 	}
 	 	function responseHandlerFailure(response, options)
		{
			DesktopWeb.Util.displayError( " Data not found . Please contact Administrator!!", callbackFn);
 	 	
 	 	function responseHandlerFailure(response, options) {
			DesktopWeb.Util.displayError( " Data not found . Please contact Administrator!!", callbackFn);
			
			function callbackFn(buttonId){
				if(buttonId == 'ok')
				{
				goToScreen();
				}
			}
 	 	}
	}
	
			function callbackFn(buttonId){
				if(buttonId == 'ok')
				{
				goToScreen();
				}
			}
 	 	}
       
	}
	
	function getAccountNumber () {
		this._accountNumber = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		return this._accountNumber;
	}
	
	function getYearFromDate(date){
		var dateParts = date.split("/");
		var year=parseInt(dateParts[2],10);
		return year;
	}
	
	function getYearFromCurrentPeriod(date) {
		var year;
		if(date != 'Life to Date') {
			var dateParts = date.split("-");
			year = dateParts[1].trim();
		} else {
			year = getYearFromDate(_cycleDate);
		}
		return year;
	}
	
	function getYearFromAsOf(date) {
		var dateParts = date.split("/");
		return dateParts[2].trim();
	}
	
	function refresh() {
		var searchValid;
		var periodChecked = _resources.fields['periodRadio'].checked; 
        if (periodChecked) {
            searchValid = _resources.fields['period'].isValid();
        } else{
            searchValid = _resources.fields['asOfDate'].isValid();
        }
        if(searchValid) {
        	if (_resources.fields['periodRadio'].checked) {
        		DesktopWeb._SCREEN_PARAM_MAP['toDate']=_resources.fields['period'].getSelectedRecord().get("code");
        	} else {
        		DesktopWeb._SCREEN_PARAM_MAP['toDate'] = getSMVDateString(_resources.fields['asOfDate'].getValue());
        	}
        	updateYearOfAnnualAmount(periodChecked);
    		clearNotionals();
    		getNotionalBalance(false);
        }
        
	}
	
	function updateYearOfAnnualAmount(periodChecked) {
		var year;
		
		if(periodChecked) {
			year = getYearFromCurrentPeriod(_resources.fields['period'].getValue());
		} else {
			year = getYearFromAsOf(DesktopWeb._SCREEN_PARAM_MAP['toDate']);
			
		}
        _resources.fields['annualAmounts'].setFieldLabel(_translationMap['AnnualAmounts'] + year);
	}
	
	function clearNotionals() {
        _resources.grids['contributionCategory'].getStore().removeAll();
        _resources.grids['grantBondCategory'].getStore().removeAll();
        _resources.grids['limitsDetail'].getStore().removeAll();
	}
	
    function goToScreen(screenName, params) {
    	if(params == null || params == 'undefined') {
    		params = {};
    	}
        params['fromScreen'] = 'RDSPNotionalBalance';
        params['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		DesktopWeb.Util.goToScreen(screenName, params);
    }

    function setCycleDate(date){
    	_resources.fields['asOfDate'].maxValue = DesktopWeb.Util.stringToDate(date,'dmy');
    }
    
    function clickHandle_RdspNotionalLotDetail(notionalCategory, transactionType) {
		var params = {};
		if(notionalCategory == 'true-Regular_Contributions') {
			notionalCategory = '03';
		}
		else if(notionalCategory == 'true-Retirement_Savings_Rollovers') {
			notionalCategory = '04';
		}
		else if(notionalCategory == 'true-Reg_Education_Savings_Rollovers') {
			notionalCategory = '05';
		}
		if(notionalCategory == 'true-Bond') {
			notionalCategory = '01';
		}
		else if(notionalCategory == 'true-Grant') {
			notionalCategory = '02';
		}
		if(transactionType == "Received" || transactionType == "Purchases") {
			transactionType = 'ED';
		} else if(transactionType == "PaidOut" || transactionType == "Redemptions") {
			transactionType = "PW";
		} else if(transactionType == "Returned") {
			transactionType = "RT";
		} else if(transactionType == "Repayments") {
			transactionType = "RP";
		}
		var fromDate = incpDate;
		var toDate = DesktopWeb._SCREEN_PARAM_MAP['toDate'];
		var today = DesktopWeb.Util.getDateString(new Date(),'dmy');
		
		if(toDate!=null && toDate!="" && toDate!='undefined') {
			if(toDate == "Life to Date") {
				toDate = today;
			} else if(toDate.substring(0,6) == "Annual"){
				var year = toDate.substring(toDate.length-4);
				fromDate ="01/01/"+ year;
				toDate ="31/12/"+ year;
			} else {
			}
			
		}
		if(DesktopWeb.Util.stringToDate(toDate) > DesktopWeb.Util.stringToDate(today)) {
			toDate = today;
		}
		if(DesktopWeb.Util.stringToDate(fromDate) > DesktopWeb.Util.stringToDate(toDate)) {
			fromDate = incpDate;
		}

		params['NotionalCategory'] = notionalCategory; 
		params['TransactionType'] = transactionType; 	
		params['toDate'] = toDate;
		params['fromDate'] = fromDate;
		params['screen'] = 'RDSPNotionalLotInquiry';
		goToScreen('RDSPNotionalLotInquiry', params);
	}
    
   function getCurrencyValue(value) {
    	return Ext.util.Format.number(value, '0,000.00'); 
    }
    
    function getSMVDateString(value) {
		return value.format(DesktopWeb.Util.parseSMVDateFormat('dmy')).trim();
	}
    
    function setCycleDate(date){
    	_resources.fields['asOfDate'].maxValue = DesktopWeb.Util.stringToDate(date,'dmy');
    }
    
	return {
		init: function(res) {
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			initScreenValue();
			
		},
        goToScreen:goToScreen,	
		initScreenValue : initScreenValue, 
		getNotionalBalance:getNotionalBalance,
		toggleFilterFields: function () {
            if (_resources.fields['periodRadio'].getValue()) {
                _resources.fields['period'].enable();
                _resources.fields['period'].allowBlank = false;
                _resources.fields['period'].setValue("Life to Date");
                _resources.fields['asOfDate'].disable();
                _resources.fields['asOfDate'].reset();
            } else {
                _resources.fields['asOfDate'].enable();
                _resources.fields['asOfDate'].allowBlank = false;
                _resources.fields['period'].disable();
                _resources.fields['period'].reset();
            }
        },
        validateAsOfDate:validateAsOfDate,
        getAccountNumber:getAccountNumber,
        refresh:refresh,
        clickHandle_ActivityBtn : function () {
        	goToScreen("RDSPNotionalActivity", null); 
        },
    	
        addHyperLinkContrib : function (value, metadata, record) {
        	var newValue;
        	var category = record.get('contCategory');
        	newValue = Ext.util.Format.number(value, '0,000.00');
    		if(category != null) {
    			var isALink = category.split("-")[0];
    			if(isALink==="true") {        	
    				var newvalue = Ext.util.Format.number(value, '0,000.00');
    				return '<a href="javascript:DesktopWeb._SCREEN_CONTROLLER.clickHandle_RdspNotionalLotDetail(\'' + record.data.contCategory + '\',\'' + metadata.id + '\');">' + newvalue + '</a>';
    			} 

    		}
    		return newValue;
        },
        
        addCategoryTitle : function (value) {
    		var newvalue;
    		if(value != null) {
    			var category = value.split("-")[1];
   				newvalue = _translationMap[category];
    		}
    		return newvalue;
    	},
    	
        addHyperLink : function (value) {
    		var newvalue;
    		if(value != null) {
    			var isALink = value.split("-")[0];
    			var category = value.split("-")[1];
    			if(isALink==="true") {
    				newvalue = "<a href='' >" + _translationMap[category] + "</a>";
    			} else {
    				newvalue = _translationMap[category];
    			}
    		}
    		return newvalue;
    	},
    	
    	numberRenderer : function (value) {
    		return Ext.util.Format.number(value, '0,000.00'); 
    	},
 	
    	numberRendererAndHyperLink : function (value, metadata, record) {
    		var newvalue = Ext.util.Format.number(value, '0,000.00');
			return '<a href="javascript:DesktopWeb._SCREEN_CONTROLLER.clickHandle_RdspNotionalLotDetail(\'' + record.data.category + '\',\'' + metadata.id + '\');">' + newvalue + '</a>';
    	},
    	setCycleDate:setCycleDate,
    	clickHandle_RdspNotionalLotDetail:clickHandle_RdspNotionalLotDetail
    	},
    	setCycleDate:setCycleDate
	}

};
