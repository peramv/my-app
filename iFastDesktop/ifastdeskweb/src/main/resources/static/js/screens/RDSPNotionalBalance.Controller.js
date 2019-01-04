/**
 * 
 */
DesktopWeb.ScreenController = function(){
	
	var _resources          = null;
	var _self               = null;
	var _inceptionDate      = null;
	var _accountNumber = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
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
		
		JRDSP.Util.sendRequestToDesktopWeb(contextPath,routePath,_service,'POST_Inquiry',DesktopWeb._SCREEN_PARAM_MAP,null,responseHandler);
        
		function responseHandler(success, responseXML) {
			if(screenLoad) {
				setIntials(success.responseXML);
			} 
			setNotionalBalance(success.responseXML);
		}
		setCycleDate(_cycleDate);
	}
	
	function setIntials(response) {
		_resources.fields['beneficaryName'].setValue(IFDS.Xml.getNodeValue(response, '//beneName'));
		_resources.fields['period'].loadData(IFDS.Xml.getNode(response, "//list[@listName='periodList']"));	
		this._inceptionDate = IFDS.Xml.getNodeValue(response, '//inceptionDate');
        _resources.fields['asOfDate'].minValue = DesktopWeb.Util.stringToDate(this._inceptionDate,'dmy'); 
	}
	
	function setNotionalBalance(response) {
		_resources.grids['contributionCategory'].getStore().loadData(IFDS.Xml.getNodes(response, '//contributionsList'),false);
		_resources.grids['grantBondCategory'].getStore().loadData(IFDS.Xml.getNodes(response, '//grantsBondsList'),false);
		_resources.grids['limitsDetail'].getStore().loadData(IFDS.Xml.getNodes(response, '//limitsList'),false);
	}
	
	function initScreenValue() {
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
         DesktopWeb._SCREEN_PARAM_MAP['toDate'] = "Life to Date";
         DesktopWeb._SCREEN_PARAM_MAP['cycleDate'] = _cycleDate;
         getNotionalBalance(true);
 	 	}
 	 	function responseHandlerFailure(response, options)
		{
			DesktopWeb.Util.displayError( " Data not found . Please contact Administrator!!", callbackFn);
			
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
	
	function refresh() {
        if (_resources.fields['periodRadio'].checked) {
            searchValid = _resources.fields['period'].isValid();
        } else{
            searchValid = _resources.fields['asOfDate'].isValid();
        }
        if(searchValid) {
        	if (_resources.fields['periodRadio'].checked) {
        		DesktopWeb._SCREEN_PARAM_MAP['toDate']=_resources.fields['period'].getSelectedRecord().get("code");
        	} else {
        		DesktopWeb._SCREEN_PARAM_MAP['toDate']=_resources.fields['asOfDate'].getSMVDateString();
        	}
    		clearNotionals();
    		getNotionalBalance(false);
        }
	}
	
	function clearNotionals() {
        _resources.grids['contributionCategory'].getStore().removeAll();
        _resources.grids['grantBondCategory'].getStore().removeAll();
        _resources.grids['limitsDetail'].getStore().removeAll();
	}
	
    function goToScreen(screenName) {
    	var params = {};
        params['fromScreen'] = 'RDSPNotionalBalance';
        params['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		DesktopWeb.Util.goToScreen(screenName, params);
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
        	goToScreen("RDSPNotionalActivity"); 
        },
    	
    	
        addHyperLinkContrib : function (value) {
    		var newvalue;
    		if(value != null) {
    			var isALink = value.split("-")[0];
    			var category = value.split("-")[1];
    			if(isALink==="true") {
    				newvalue = "<a class='grid-cell-hyper' href='' >" + _translationMap[category] + "</a>";
    			} else {
    				newvalue = _translationMap[category];
    			}
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
    	setCycleDate:setCycleDate
	}
};
