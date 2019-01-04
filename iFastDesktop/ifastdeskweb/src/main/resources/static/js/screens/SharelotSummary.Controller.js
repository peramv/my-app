/*********************************************************************************************
 * @file	SharelotSummary.Controller.js
 * @author	Haroon Chaudhry
 * @desc	Control JS file for Sharelot Summary screen
 *********************************************************************************************/
/*
 * Procedure: SharelotSummary.Controller.js
 *
 * Purpose  : Control JS file for Sharelot Summary screen
 *             
 * Notes    : 
 *
 * History  :  
 *		15 Feb 2011 Haroon Chaudhry
 *				- Initial created for Performance Fee Project
 *
 *
 *		21 Nov 2013 Winnie Cheng. P0216756 FN01  T77441
 *					- Performance Fee SOC 2/3 Project
 *					- ActiveOnly dropdown and All Transactions radio button are not working properly, fixing.
 *
 *  	21 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54443
 *            		- Correct the format of all date fields based on registry edit
 *              	  ,called displayMark
 *
 *  07 May 2018 Pao - Supareuk S.
  *  		- In goToScreen function, we changed a way to show the page from window.location 
 *  		using buildURL to DesktopWeb.Util.goToScreen. 
 *  		- We changed a way to get xml response from smartview service from doSmartviewCall
 *  		to doSmartviewAjax function.
 *  		This is to solve an issue when user's profile has too many slot attached. If the 
 *  		session is included, the page will be broken as too large.
 */
	

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _initDataXML = null;
	var _responseDataXML =null;
	var _changeFlag = false;
	var _initView = 'dtSharelotInit';
	var _reloadView = 'dtSharelotReload';
	var _selectedLotID=null;
	var _transID=null;
	var _asOfDate=null;
	var _activeOnly=null;

	var _screenId = "SharelotSummary";
	var _translationMap = DesktopWeb.Translation.getTranslationMap();	
	// PRIVATE METHODS ****************************************	

	function setInitialFieldValue(fld, val)
	{			
		if (val != "" && _resources.fields[fld]) 
		{		
			_resources.fields[fld].setValue(val);
		}
	}
	
	function populateSummaryGrid(resultXML){
		
		var shareLotSum = IFDS.Xml.getNode(resultXML, '//Sharelots');
		
		if(shareLotSum){
			_resources.grids['shareLotSummary'].loadData(shareLotSum, null);
			
			 var firstShareLotID  = IFDS.Xml.getNodeValue(resultXML, '//Sharelots/Sharelot[1]/lotID');
 			
 			if(firstShareLotID)
				populateDetailsGrid(firstShareLotID);
		}
    }
	
	function populateDetailsGrid(sharelotDetailInfo){
		

		if(sharelotDetailInfo && sharelotDetailInfo.data && sharelotDetailInfo.data['lotID']){
			
			var path="//Sharelots/Sharelot[lotID="+sharelotDetailInfo.data['lotID']+"]/TransDetls";
			var shareLotDetails = IFDS.Xml.getNode(_responseDataXML, path);

			if(shareLotDetails)
				_resources.grids['shareLotDetails'].loadData(shareLotDetails, null);
		}
    }

	function setLabelTextFromNode(label,doc,node){
	    if ((label == 'valuDT') || (label == 'tradeDT')){
			_resources.fields[label].setText(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(doc, node)));
		}
		else{
			_resources.fields[label].setText(IFDS.Xml.getNodeValue(doc, node));				
		}		
		
	}
	function setValueFromNode(field,doc,node){
		if (field == 'asOfDate'){
			_resources.fields[field].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(doc, node)));
		}
		else{
			_resources.fields[field].setValue(IFDS.Xml.getNodeValue(doc, node));
		}				
		
	}
	
	function setComboboxValue(field,value){
		var selectedRecord = _resources.fields[field].findRecord('code',value);
		if(selectedRecord){
			_resources.fields[field].setValue(selectedRecord.get('value'));
		}
	}
	
	function populateFilterInitValues(resultXML){
	
		var shareLotType =_resources.fields['shareLotType'] ;
		shareLotType.loadData(IFDS.Xml.getNode(resultXML, "//List[@id='ShareLotTypeList']"));
		setComboboxValue('shareLotType',IFDS.Xml.getNodeValue(resultXML,'//ListSelection[@id="ShareLotTypeList"]'));		 		

		
	 	_resources.fields['fundClass'].loadData(IFDS.Xml.getNode(resultXML, "//List[@id='FundList']"));
	 	var fund = IFDS.Xml.getNodeValue(resultXML,'//ListSelection[@id="Fund"]/Element/code');
	 	var fundClass = fund +'/' +IFDS.Xml.getNodeValue(resultXML,'//ListSelection[@id="Fund"]/Element/value');
		setComboboxValue('fundClass',fundClass);
			
	 	setValueFromNode('asOfDate',resultXML, "//SharelotInfoInit/asOfDate");
	 	_resources.fields['selectedTrans_all'].setValue(IFDS.Xml.getNodeValue(resultXML, '//SharelotInfoInit/selectedTrans') == 'no');
	 	_resources.fields['selectedTrans_sel'].setValue(IFDS.Xml.getNodeValue(resultXML, '//SharelotInfoInit/selectedTrans') == 'yes');

	}
	
	
	
	function populateGeneralInfo(resultXML){

	
	 	setLabelTextFromNode('valuDT',resultXML, "//PerfFeeEvent/valuationDate");
	 	
		setLabelTextFromNode('gav',resultXML, "//PerfFeeEvent/GAV");				
		setLabelTextFromNode('nav',resultXML, "//PerfFeeEvent/NAV");
		setLabelTextFromNode('unitBal',resultXML, "//PerfFeeEvent/unitBalance");
		setLabelTextFromNode('classValue',resultXML, "//PerfFeeEvent/unitValue");
		setLabelTextFromNode('classHWM',resultXML, "//PerfFeeEvent/classHWM");
		setLabelTextFromNode('classAdjHWM',resultXML, "//PerfFeeEvent/classAdjHWM");
		setLabelTextFromNode('classAdjHWM',resultXML, "//PerfFeeEvent/classAdjHWM");
		
		Ext.getCmp('classlevel_fieldset').doLayout();

	}
	
	function populateTransInfo(resultXML){
		
 		setLabelTextFromNode('transNum',resultXML, "//TransInfo/transNumber");
 		setLabelTextFromNode('transType',resultXML, "//TransInfo/transType");
 		setLabelTextFromNode('tradeDT',resultXML, "//TransInfo/deff");
 		setLabelTextFromNode('units',resultXML, "//TransInfo/units");
 		setLabelTextFromNode('amount',resultXML, "//TransInfo/amount");
 		
 		Ext.getCmp('transInfo_fieldset').doLayout();
	}	
	
	function validateScreen(){
		return true;
	}
	
	function updateXML(){
		
	}
	function callback(x){
			//prompt('',x.xml);
	}
	// PUBLIC ITEMS *************************************
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_transID=DesktopWeb._SCREEN_PARAM_MAP['TransId'];
			
			if(! _transID){
				_transID=DesktopWeb._SCREEN_PARAM_MAP['transId'];
			}
			_asOfDate = DesktopWeb._SCREEN_PARAM_MAP['AsOfDate'];
			
			_activeOnly = DesktopWeb._SCREEN_PARAM_MAP['ActiveOnly'];
			
			_resources.fields['activeOnly'].setValue(_activeOnly);
			
			_self.loadInitData(_initView);
			
		}
		, createPDF:function(){
			
			// Get the hostmark to format the date value instead of hard code
			_asOfDate = _resources.fields['asOfDate'].getSMVDateString();
			var basicRequest = _self.prepareRequest();
			IFDS.Xml.addSingleNode(basicRequest, "lotId", _selectedLotID);
			
			
			if(_transID && _transID > 0){
				DesktopWeb.Ajax.doBuildPDFReport(_reloadView, 'SummarySharelot', 'SummarySharelot', basicRequest );				
				DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, basicRequest, _self.testAjax, _translationMap['ProcMsg_Loading']);
			}else{
				DesktopWeb.Ajax.doBuildPDFReport(_reloadView, 'SummarySharelot', 'SummarySharelot', basicRequest );				
				DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, basicRequest, _self.testAjax, _translationMap['ProcMsg_Loading']);
			}					
		}
		
		
		,testAjax:function(responseXML){
			//prompt('TEST_RESP',responseXML.xml);
		}
		, prepareRequest:function(){

			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, "acctNum",DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			
			IFDS.Xml.addSingleNode(requestXML, "dateFormat", DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
			
			//IFDS.Xml.addSingleNode(requestXML, "lotID", '123');
			
			IFDS.Xml.addSingleNode(requestXML, "asOfDate", _asOfDate);
			var radioValue = "no";
			if (_resources.fields['selectedTrans_all'].getValue() == true) {
				radioValue = "yes"
			}
			IFDS.Xml.addSingleNode(requestXML, "selectedTrans",  radioValue);
			

			IFDS.Xml.addSingleNode(requestXML, "activeOnly", _resources.fields['activeOnly'].getValue());			

			//pick default fund class from screen parameters
			var fund = DesktopWeb._SCREEN_PARAM_MAP['Fund']; 
			var classValue = DesktopWeb._SCREEN_PARAM_MAP['Class'];
			var fundClass = _resources.fields['fundClass'];
			var record = fundClass.findRecord(fundClass.valueField || fundClass.displayField, fundClass.getValue());
			//if we have FundClass drop down initialized with a value use that value instead 
			if(record){
				var codeValue=record.data['code'];
				fund=codeValue.split('/')[0];
				classValue=codeValue.split('/')[1];
			}
			IFDS.Xml.addSingleNode(requestXML, "fund", fund);
			IFDS.Xml.addSingleNode(requestXML, "class", classValue);

		
			var cbox=_resources.fields['shareLotType'];
			var record = cbox.findRecord(cbox.displayField, cbox.getValue());		
			var lotType = (record != null ? record.get(cbox.valueField) : null);
			//if there is no sharelot type defined use 'preffee' as default 			 			
			if(!lotType){
				lotType='perffee';
			}
			IFDS.Xml.addSingleNode(requestXML, "lotType", lotType);
			
			var selectedTrans='no';
			if(_transID && _transID > 0){
				IFDS.Xml.addSingleNode(requestXML, "transId", _transID);
				selectedTrans='yes';
			}
			
			IFDS.Xml.addSingleNode(requestXML, "selectedTrans", selectedTrans);

			return 	requestXML;		
		}
		,loadInitData:function(viewToLoad){
			//DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ScreenDefList', 'ExistingClassData', 'UpdatedClassData'], responseHandler2, "Loading ...");
			var requestXML = _self.prepareRequest();			
			DesktopWeb.Ajax.doSmartviewAjax(viewToLoad, null, requestXML, initResponseHandler, _translationMap['ProcMsg_Loading']);
			
			function initResponseHandler(success, responseXML){
				
				if (success) {
					
					populateFilterInitValues(responseXML);
					
					_initDataXML = responseXML;
					_responseDataXML=responseXML;
					populateGeneralInfo(responseXML);
					populateTransInfo(responseXML);
					populateSummaryGrid(responseXML);
				}
			}
		}
		
		,reloadData:function(){
			//For refresh remove selected Transaction
			
			if (_resources.fields['selectedTrans_all'].getValue() == true) {
				_transID=null;
			}
		
			// Get the hostmark to format the date value instead of hard code
			_asOfDate = _resources.fields['asOfDate'].getSMVDateString();
			
			//alert ("all=" + _resources.fields['selectedTrans_all'].getValue() + " sel= " + _resources.fields['selectedTrans_sel'].getValue());
			/*var selectedTrans_all = _resources.fields['selectedTrans_all'];
			if(selectedTrans_all){
				selectedTrans_all.setValue(true);
			}*/
				
			var requestXML = _self.prepareRequest();
			
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, reloadResponseHandler, _translationMap['ProcMsg_Loading']);
				
			function reloadResponseHandler(success, responseXML){
				//Clear screen before making next request
				var emptyDoc = IFDS.Xml.newDocument("empty");
				populateGeneralInfo(emptyDoc );
				populateTransInfo(emptyDoc );
				
				_resources.grids['shareLotSummary'].loadData(emptyDoc,null);
				_resources.grids['shareLotDetails'].loadData(emptyDoc,null);
				
				if (success) {
					_responseDataXML = responseXML;
			
					populateGeneralInfo(responseXML);
					populateTransInfo(responseXML);
					populateSummaryGrid(responseXML);
				}
			}
			
		}
		
		,basicURLParameters:function(){
			var urlParams = {};
			urlParams['jobname'] = 'DisplayScreen';
			urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
			urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
			urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
			urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
			urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
			urlParams['prevScreen'] = _screenId;
			urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];

			urlParams['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];			
			urlParams['Fund'] = DesktopWeb._SCREEN_PARAM_MAP['Fund'];
			urlParams['Class'] = DesktopWeb._SCREEN_PARAM_MAP['Class'];
			urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
			
			return urlParams; 
		}
		,linkToSelfWithTrans:function(linkParams, tradeDate){
					
			var urlParams = _self.basicURLParameters();
			
			urlParams['screen'] = 'SharelotSummary';
			
			
			var url = DesktopWeb.Ajax.buildURL(urlParams);
			url = url +linkParams;
			return url;
		}
		,openSharelotDetailsScreen:function(){
			
			var urlParams = _self.basicURLParameters();
			
			urlParams['lotID'] = _resources.grids['shareLotSummary'].getSelectedRecord().data['lotID'];
			urlParams['screen'] = 'SharelotDetl';
			// Get the hostmark to format the date value instead of hard code
			_asOfDate = _resources.fields['asOfDate'].getSMVDateString();
			urlParams['AsOfDate'] = _asOfDate;
			urlParams['TransId'] = _transID;
			urlParams['ActiveOnly'] = _resources.fields['activeOnly'].getValue();
			// Send the date format to the detail screen
			urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];

			DesktopWeb.Util.goToScreen('SharelotDetl', urlParams);
			
			// _resources.popups['SharelotDetl']=getPopup(650,700);
// 			 
			// _resources.popups['SharelotDetl'].init(_resources);
// 			
			// _resources.popups['SharelotDetl'].show();
		}
		
		
		
		,sharelotSelected:	function (rowData){
			populateDetailsGrid(rowData);
			_selectedLotID=rowData.data['lotID'];
		}


	}; //returned Controller object
}; //Controller Defination

