/*********************************************************************************************
 * @file	AcctDelReview.Controller.js
 * @author	
 * @desc	Controller JS file for Account Deletion Review screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  09 October 2017 Winnie Cheng P0272876
 *		- General Data Protection Regulation-GDPR, Allowing to change the account attribute
 */

DesktopWeb.ScreenController = function(){
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'add';
	var _MOD = 'mod';
	var _INQ = 'inq';
	var _RELOAD = 'reload';
	
	var _initXml = null;
	var _currStateCode = null;
	var _permissions = new Array();
	
	var _reloadView = 'dtAcctDelReviewInq';
	var _updateView = 'dtAcctDelReviewProc';

	// PRIVATE METHODS *************************************
	/** Store user permission **/
	function storePermissions(reloadXML){
		_permissions[_self.INQ] = IFDS.Xml.getNodeValue(reloadXML, '//userPermissions/inq').toLowerCase() == 'yes';
		_permissions[_self.MOD] = IFDS.Xml.getNodeValue(reloadXML, '//userPermissions/mod').toLowerCase() == 'yes';	
	}
	//populate data
	function populateRecords(responseXML){
		// main screen, set value
		var currStateDesc = IFDS.Xml.getNodeValue(responseXML, '//*/currStateDesc');
		if (currStateDesc != null) {
			_resources.fields['currentStateDesc'].setValue(currStateDesc);
			_currStateCode = IFDS.Xml.getNodeValue(responseXML, '//*/currState');
		}
		//load the dropdown
		var FutStatesNode = IFDS.Xml.getNode(responseXML, "//List[@listName='FutStates']")
		if (FutStatesNode != null){
			_resources.fields['stateTo'].loadData(FutStatesNode);
			//enableDisable rules
			var optionsCount = _resources.fields['stateTo'].getStore().getCount();
			if (_permissions[_self.MOD] && optionsCount > 1 ) {
				enableDisableFldBtn(true);
			} else {
				enableDisableFldBtn(false); 
			}
		}
		//load grid data
		var acctDelReviewGrid = IFDS.Xml.getNode(responseXML, '//AcctDelStates');
		if (acctDelReviewGrid != null) {
			_resources.grids['acctDelReview'].getStore().loadData(IFDS.Xml.getNode(responseXML, '//AcctDelStates'));
		}
	}	
	//render screen
	function loadAcctDelAttributes(){
		var requestXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(requestXML,"accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(requestXML, 'runMode', _RELOAD);
		
		DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['Loading']);
		
		function responseHandler(success, responseXML){
			if (success) {
				//clear field
				_resources.fields['stateTo'].clearField();
				// Load permission
				storePermissions(responseXML);
				//populate fields
				populateRecords(responseXML);
			} else {
				enableDisableFldBtn(false);
			}
		}
	}
	//reset 
	function enableDisableFldBtn(enableFlag){
		if (enableFlag) {
			_resources.fields['stateTo'].enable();
			_resources.buttons['saveBtn'].enable();
		} else {
			_resources.fields['stateTo'].disable();
			_resources.buttons['saveBtn'].disable();
		}
	}
	//Update account delete attribute
	function updateAcctDelAttribute(){
		//build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(dataXML, 'runMode', _ADD);
		IFDS.Xml.addSingleNode(dataXML, 'prevState',  _currStateCode);
		IFDS.Xml.addSingleNode(dataXML, 'currState', _resources.fields['stateTo'].getValue());
		// call service
		DesktopWeb.Ajax.doSmartviewAjax(_updateView, null, dataXML, responseHandler, _translationMap['ProcMsg_Saving'])

		function responseHandler(success, responseXML){
			// handle response
			if (success){
				_self.updatesFlag = false;
				loadAcctDelAttributes();
			}
		}
	}
	
	// PUBLIC ITEMS *************************************
	return {
		updatesFlag: false
		//init. loading screen
		,init: function(res){
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			//do SMV ajax call
			loadAcctDelAttributes();
		}
		//save delete state data
		,updateAcctDelAttribute: function(){
			updateAcctDelAttribute();
		}
	}
}