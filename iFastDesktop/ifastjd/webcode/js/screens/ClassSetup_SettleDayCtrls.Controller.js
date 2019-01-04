/************************************************************************************
 * @file ClassSetup_SettleDayCtrls.Controller.js
 * @author wp040510
 * @desc Controller file for Settle day controls,Part of Class Setup flow
 ************************************************************************************/
/*
 *  Navigate: Menu > Fund class Maintenance > Add/View class details > Settle day controls
 *
 *  History : 
 *  
 *  18-Dec-2017 Sreejith A P0274727-1
 *  			- New screen for Settle day controls
 *  
 *	12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 *  
 *  03 July 2018 Sreejith.A P0277704 P0277704-3
 *  		- Added Custom valuation schedule validation	
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _changeFlag = false;
	var _screenDefListXML = null;
	var _screenIndex = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;
	var _screenId = "SettleDayCtrls";
	var _addMode = null;
	
	// PRIVATE METHODS ****************************************
	function setChangeFlag() {
		_changeFlag = true;
		Ext.getCmp('resetBtn').enable();
		Ext.getCmp('saveBtn').enable();
	}
	
	function clearChangeFlag() {
		_changeFlag = false;
		Ext.getCmp('resetBtn').disable();
		Ext.getCmp('saveBtn').disable();
	}
	
	//To populate values from service to screen 
	function populateScreen() {
		var settleDayCtrlsXML = IFDS.Xml.getNode(_updatedClassDataXML, 'SettleDayControls');
		
		if(settleDayCtrlsXML != undefined){
			setInitialFieldValues(_resources.fields['purStlmtDays']['purchaseStlmtDays'], IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/PurSettDays'));
			setInitialFieldValues(_resources.fields['purStlmtDays']['diffStlmtCurrency'], IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/DiffSettCurr'));
			setInitialFieldValues(_resources.fields['otherSettleDays']['redemptionStlmtDays'], IFDS.Xml.getNode(settleDayCtrlsXML, 'RedSettDays'));
			setInitialFieldValues(_resources.fields['otherSettleDays']['exchangeInStlmtDays'], IFDS.Xml.getNode(settleDayCtrlsXML, 'ExInSettDays'));
			setInitialFieldValues(_resources.fields['otherSettleDays']['exchangeOutStlmtDays'], IFDS.Xml.getNode(settleDayCtrlsXML, 'ExOutSettDays'));
			setInitialFieldValues(_resources.fields['otherSettleDays']['transferInStlmtDays'], IFDS.Xml.getNode(settleDayCtrlsXML, 'XferInSettDays'));
			setInitialFieldValues(_resources.fields['otherSettleDays']['transferOutStlmtDays'], IFDS.Xml.getNode(settleDayCtrlsXML, 'XferOutSettDays'));
		}
		
		function setInitialFieldValues(fld, values) {
			if(_addMode) {
				fld['UnitDaysLabel'].setValue('');
				fld['AmountDays'].hide();
				fld['AmountDaysLabel'].hide();
				fld['AmountType'].setValue(true);
			}
			
			if (values != undefined) {		
				fld['UnitDays'].setValue(IFDS.Xml.getNodeValue(values, 'unitDays'));
				fld['AmountDays'].setValue(IFDS.Xml.getNodeValue(values, 'amountDays'));
				var amtTypVal =  IFDS.Xml.getNodeValue(values, 'amountType');
				
				//if amount type value is * , amount type check box should be checked and amount days should be shown
				if (amtTypVal=='*') {	
					fld['AmountType'].setValue(true);
					fld['AmountDays'].hide();
					fld['AmountDaysLabel'].hide();
					fld['UnitDaysLabel'].setValue('');
				} else {
					fld['AmountType'].setValue(false);
					fld['AmountDays'].show();
					fld['AmountDaysLabel'].show();
					fld['UnitDaysLabel'].setValue(_translationMap['UnitDays']);
				}
			}	
		}
	}
	
	function disableCustValuation() {
		var priceInfoXML = null;
		priceInfoXML = IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo');
		if (priceInfoXML==null) {
			priceInfoXML = IFDS.Xml.getNode(_existingClassDataXML, 'PriceInfo');
		}
		if (priceInfoXML!= null) {
			var customValuation = IFDS.Xml.getNodeValue(priceInfoXML, 'schedTransType');
			if(customValuation !="") {
				checkAndDisable(_resources.fields['purStlmtDays']['purchaseStlmtDays']);
				checkAndDisable(_resources.fields['purStlmtDays']['diffStlmtCurrency']);
				_resources.fields['purStlmtDays']['diffStlmtCurrency']['UnitDays'].setValue('');
				_resources.fields['purStlmtDays']['diffStlmtCurrency']['UnitDays'].disable();
				checkAndDisable(_resources.fields['otherSettleDays']['redemptionStlmtDays']);
				checkAndDisable(_resources.fields['otherSettleDays']['exchangeInStlmtDays']);
				checkAndDisable(_resources.fields['otherSettleDays']['exchangeOutStlmtDays']);
				checkAndDisable(_resources.fields['otherSettleDays']['transferInStlmtDays']);
				checkAndDisable(_resources.fields['otherSettleDays']['transferOutStlmtDays']);
			}
		}
		
		function checkAndDisable(fld) {
			fld['AmountType'].setValue(true);
			fld['AmountType'].disable();
		}
	}
	
	function goToScreen(screenName) {
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_' + screenName;
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		urlParams['prevScreen'] = _screenId;
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
		
		if (screenName == "Search") {
			urlParams['createCache'] = 'true';	
		} else {
			urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		}			
									
		window.location = DesktopWeb.Ajax.buildURL(urlParams);
	}
	
	//To update xml with updated values from screen before passing to service
	function updateXML() {
		var settleDayCtrlsXML = IFDS.Xml.getNode(_updatedClassDataXML, 'SettleDayControls');
		
		var xmlWriteFn = null; 
		if (_addMode) {
			writeNewValueToXML('runMode', _self.ADD);			
			xmlWriteFn = writeNewValueToXML;
		} else {
			writeNewValueToXML('runMode', _self.MOD);
			xmlWriteFn = writeUpdatedValueToXML;
		}
		
		xmlWriteFn('unitDays', _resources.fields['purStlmtDays']['purchaseStlmtDays']['UnitDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/PurSettDays'));
		xmlWriteFn('amountDays', _resources.fields['purStlmtDays']['purchaseStlmtDays']['AmountDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/PurSettDays'));
		xmlWriteFn('amountType', getAmtTypVal(_resources.fields['purStlmtDays']['purchaseStlmtDays']), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/PurSettDays'));
		
		xmlWriteFn('unitDays', _resources.fields['purStlmtDays']['diffStlmtCurrency']['UnitDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/DiffSettCurr'));
		xmlWriteFn('amountDays', _resources.fields['purStlmtDays']['diffStlmtCurrency']['AmountDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/DiffSettCurr'));
		xmlWriteFn('amountType', getAmtTypVal(_resources.fields['purStlmtDays']['diffStlmtCurrency']), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'PurStlmtDays/DiffSettCurr'));
		
		xmlWriteFn('unitDays', _resources.fields['otherSettleDays']['redemptionStlmtDays']['UnitDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'RedSettDays'));
		xmlWriteFn('amountDays', _resources.fields['otherSettleDays']['redemptionStlmtDays']['AmountDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'RedSettDays'));
		xmlWriteFn('amountType', getAmtTypVal(_resources.fields['otherSettleDays']['redemptionStlmtDays']), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'RedSettDays'));
		
		xmlWriteFn('unitDays', _resources.fields['otherSettleDays']['exchangeInStlmtDays']['UnitDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'ExInSettDays'));
		xmlWriteFn('amountDays', _resources.fields['otherSettleDays']['exchangeInStlmtDays']['AmountDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'ExInSettDays'));
		xmlWriteFn('amountType', getAmtTypVal(_resources.fields['otherSettleDays']['exchangeInStlmtDays']), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'ExInSettDays'));
		
		xmlWriteFn('unitDays', _resources.fields['otherSettleDays']['exchangeOutStlmtDays']['UnitDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'ExOutSettDays'));
		xmlWriteFn('amountDays', _resources.fields['otherSettleDays']['exchangeOutStlmtDays']['AmountDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'ExOutSettDays'));
		xmlWriteFn('amountType', getAmtTypVal(_resources.fields['otherSettleDays']['exchangeOutStlmtDays']), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'ExOutSettDays'));
		
		xmlWriteFn('unitDays', _resources.fields['otherSettleDays']['transferInStlmtDays']['UnitDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'XferInSettDays'));
		xmlWriteFn('amountDays', _resources.fields['otherSettleDays']['transferInStlmtDays']['AmountDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'XferInSettDays'));
		xmlWriteFn('amountType', getAmtTypVal(_resources.fields['otherSettleDays']['transferInStlmtDays']), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'XferInSettDays'));

		xmlWriteFn('unitDays', _resources.fields['otherSettleDays']['transferOutStlmtDays']['UnitDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'XferOutSettDays'));
		xmlWriteFn('amountDays', _resources.fields['otherSettleDays']['transferOutStlmtDays']['AmountDays'].getRawValue(), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'XferOutSettDays'));
		xmlWriteFn('amountType', getAmtTypVal(_resources.fields['otherSettleDays']['transferOutStlmtDays']), 
				IFDS.Xml.getNode(settleDayCtrlsXML, 'XferOutSettDays'));

		function writeUpdatedValueToXML(fldName, value, context) {
			context = (context == null ? settleDayCtrlsXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (!node) node = IFDS.Xml.addSingleNode(context, fldName, '');
			if (IFDS.Xml.getNodeValue(node, '.') != value) {
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context) {
			context = (context == null ? settleDayCtrlsXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}
		
		//Amount type should be * if check box is checked otherwise blank
		function getAmtTypVal (fld) {
			if(fld['AmountType'].getValue()== true) {
				return '*';
			} else {
				return '';
			}
		}
	}
	
	function setHeader() {
		var fundCode = null;
		var classCode = null;
		
		if (_addMode) {
			fundCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundCode');
			classCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//classCode');			
			if (classCode == "") {
				classCode = "*" + _translationMap['New'].toUpperCase() + "*";
			} else {
				classCode = "*" + classCode + "*";
			}
		} else {
			fundCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundCode');
			classCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'classCode');	
		}
		
		var screenLabel = IFDS.Xml.getNodeValue(_screenDefListXML, 'Screen[id = "' + _screenId + '"]/label')
		_resources.header.setText(screenLabel + ' - ' + _translationMap['Fund'] + ': ' + fundCode + ', ' + _translationMap['Class'] + ': ' + classCode);
	}
	
	function populateBreadCrumbList() {
		var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
				
		for (var i = 0; i < screenDefNodes.length; i++) {
			var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id');			
			_resources.breadCrumbList.addItem(id, IFDS.Xml.getNodeValue(screenDefNodes[i], 'label'));
			
			if (id == _screenId) {
				_screenIndex = i;
			}							
		}		
		
		if (_addMode) {
			_resources.breadCrumbList.disableAll();
			for (var i = 0; i <= _screenIndex; i++) {	
				 var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id') 
				_resources.breadCrumbList.enableItem(id);										
			}
		} else {						
			_resources.breadCrumbList.enableAll();
		}
		_resources.breadCrumbList.setActiveItem(_screenId);
	}
	
	function displayScreenButtons() {
		if (_addMode) {			
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			if (_screenIndex != 0) {
				//not the first
				Ext.getCmp('prevBtn').enable();
			}
			
			if (_screenIndex < screenDefNodes.length - 1) {				
				Ext.getCmp('nextBtn').setText(_translationMap['Next']);
			} else {
				Ext.getCmp('nextBtn').setText(_translationMap['Summary']);
			}
			Ext.getCmp('prevBtn').show();
			Ext.getCmp('cancelBtn').show();
			Ext.getCmp('nextBtn').show();			
		} else {
			Ext.getCmp('summaryBtn').show();
		}
	}
	
	function validateScreen() {
		var isValid = true;
		
		amountTypVldn(_resources.fields['purStlmtDays']['purchaseStlmtDays']);
		amountTypVldn(_resources.fields['purStlmtDays']['diffStlmtCurrency']);
		amountTypVldn(_resources.fields['otherSettleDays']['redemptionStlmtDays']);
		amountTypVldn(_resources.fields['otherSettleDays']['exchangeInStlmtDays']);
		amountTypVldn(_resources.fields['otherSettleDays']['exchangeOutStlmtDays']);
		amountTypVldn(_resources.fields['otherSettleDays']['transferInStlmtDays']);
		amountTypVldn(_resources.fields['otherSettleDays']['transferOutStlmtDays']);
		
		return isValid;
		
		function amountTypVldn(fields){
			
			var amtDaysVal = fields['AmountDays'].getRawValue();
			var unitDaysVal = fields['UnitDays'].getRawValue();
			
			if(fields['AmountType'].getValue()== false) {
				if(unitDaysVal =='' && amtDaysVal!='') {
					fields['UnitDays'].markInvalid(_translationMap['FldRequired']);
					isValid = false;
				}
				if(amtDaysVal=='' && unitDaysVal !='') {
					fields['AmountDays'].markInvalid(_translationMap['FldRequired']);
					isValid = false;
				}
			}
		}	
	}
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'a', MOD: 'm'	
						
		,init: function(res) {				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ScreenDefList', 'ExistingClassData', 'UpdatedClassData'], responseHandler, _translationMap['ProcMsg_Loading'])
				
			function responseHandler(responseXML) {
				_initDataXML = IFDS.Xml.getNode(responseXML, 'InitData/*');
				_screenDefListXML = IFDS.Xml.getNode(responseXML, 'ScreenDefList/*');	
				_existingClassDataXML = IFDS.Xml.getNode(responseXML, 'ExistingClassData/*');				
				_updatedClassDataXML = IFDS.Xml.getNode(responseXML, 'UpdatedClassData/data');
				
				if (_initDataXML == null || _screenDefListXML == null || _updatedClassDataXML == null) {
					throw new Error("Error retrieving cached data");
				}				
								
				_addMode = (_existingClassDataXML == null);								
					
				if (!_addMode) {												
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'SettleDayControls')) {										
						IFDS.Xml.appendNode(_updatedClassDataXML, 
							IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'SettleDayControls')));
					}
				}

				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateScreen();
				disableCustValuation();
				clearChangeFlag();
			}
		}
	
		//To hide/show Amount days field and change labels
		,onAmountTypeChange : function(value,fld) {
			setChangeFlag();
			if(value) {
				fld['AmountDays'].hide();
				fld['UnitDays'].clearInvalid();
				fld['AmountDays'].setValue('');
				fld['AmountDaysLabel'].hide();
				fld['UnitDaysLabel'].setValue('');
			} else {
				fld['AmountDays'].show();
				fld['AmountDaysLabel'].show();
				fld['UnitDaysLabel'].setValue(_translationMap['UnitDays']);
			}
		}
		
		,onDaysChange : function(fld) {
			setChangeFlag();
			fld['UnitDays'].clearInvalid();
			fld['AmountDays'].clearInvalid();
		}
		
		,changeScreen : function(screenName) {
			if (screenName != _screenId) {
				if (_changeFlag) {
					DesktopWeb.Util.displayDiscardPrompt(callback)
				} else {
					goToScreen(screenName)
				}
			}

			function callback(discard) {
				if (discard) {
					goToScreen(screenName);
				}
			}
		}

		,previous : function() {
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex - 1], 'id'));
		}

		,next : function() {
			if (validateScreen()) {
				if (_changeFlag) {
					updateXML();
					DesktopWeb.Ajax.doUpdateCache({
						UpdatedClassData : _updatedClassDataXML},
						callback, _translationMap['ProcMsg_Saving']);
				} else {
					callback();
				}

				function callback() {
					clearChangeFlag();
					var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
					if (_screenIndex < screenDefNodes.length - 1) {
						goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex + 1], 'id'));
					} else {
						goToScreen('Summary');
					}
				}
			}
		}

		,reset : function() {
			DesktopWeb.Util.displayDiscardPrompt(callback);

			function callback(discard) {
				if (discard) {
					populateScreen();
					clearChangeFlag();
				}
			}
		}

		,save : function() {
			if (validateScreen()) {
				updateXML();
				DesktopWeb.Ajax.doUpdateCache({
					UpdatedClassData : _updatedClassDataXML},
					callback, _translationMap['Saving']);

				function callback() {
					clearChangeFlag();
				}
			}
		}

		,cancel : function() {
			DesktopWeb.Util.displayDiscardPrompt(callback);

			function callback(discard) {
				if (discard) {
					goToScreen('Search');
				}
			}
		}
	}
}