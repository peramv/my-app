/*********************************************************************************************
 * @file	AcctStDataVerify.Controller.js
 * @author	
 * @desc	Controller JS file for Account Static Data Verification screen
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.
 *
 *  23 Jan 2018 Umamahesh PBSGEALV-181 & PBSGEALV-177
 *					- User verification Shareholder,Broker,Branch and Sales Rep
 */

DesktopWeb.ScreenController = function(){
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _initXml = null;
	var _initView = 'dtEntityFldVrfyInit';
	var _updateView = 'dtEntityFldVrfyUpd';
	
	// PRIVATE METHODS ****************************************

	function updateVerifyButton(responseXML)
	{
		var selectedVerifyRecord = _resources.grids['acctStDataVerifyGrid'].getSelectedRecord();
		Ext.getCmp('verifyButton').setDisabled(true);
		
		if(selectedVerifyRecord != null) {
			var loginUser = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
			var modUser = selectedVerifyRecord.data.modUser;
			var verifyStat = selectedVerifyRecord.data.verifyStat;			
			if( modUser != loginUser && verifyStat=='Unverified') {
				Ext.getCmp('verifyButton').setDisabled(false);
			}
		}

	}

	function doUpdate(updateXML)
	{
		DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, updateXML, updateResponseHandler, null);
		function updateResponseHandler(success, responseXML)
		{					
			if (success)
			{
				populateRecords();
			}
		}			

	}
	function populateRecords(){
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML,"accountNum",DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					_initXml = responseXML;
					_resources.grids['acctStDataVerifyGrid'].loadData(IFDS.Xml.getNode(responseXML, '//*/EntityInfo'));
					//updateVerifyButton();
				}
			}
	}	
	// PUBLIC ITEMS *************************************
	return {
			
		init: function(res){
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			populateRecords();
		}

	
		,recordsList: function () {

			var selectedRecord = _resources.grids['acctStDataVerifyGrid'].getSelectedRecord();
			var recordsReturnValue = []
			var nodeArray = IFDS.Xml.getNodes(_initXml,'//*/EntityInfo/EntityInfo');

			for(var i=0; i< nodeArray.length; i++){
				var changedFieldsNodeArray = IFDS.Xml.getNodes(IFDS.Xml.cloneDocument(nodeArray[i]),'//fieldInfo');

				if(((selectedRecord.data.modTime == IFDS.Xml.getNodeValue(nodeArray[i], "modTime")) ) 
					&& ((DesktopWeb.Util.getSMVDateValue(selectedRecord.data.modDate) == IFDS.Xml.getNodeValue(nodeArray[i], "modDate")))){
					for(var j=0; j< changedFieldsNodeArray.length; j++){
							recordsReturnValue[j] = IFDS.Xml.getNodeValue(changedFieldsNodeArray[j], 'fldLabel')
							+ '~' + IFDS.Xml.getNodeValue(changedFieldsNodeArray[j], 'oldVal')
							+ '~' + IFDS.Xml.getNodeValue(changedFieldsNodeArray[j], 'newVal');
					}
				}
			}
			return recordsReturnValue;	
		}

		,verifyStaticDataChanges: function() {
			var _updateXML = IFDS.Xml.newDocument('VerifyRequestUpdate');
			var selectedRecord = _resources.grids['acctStDataVerifyGrid'].getSelectedRecord();
			var entityId = selectedRecord.data.entityId;
			var VerifyRequestUUID = selectedRecord.data.VerifyRequestUUID;
			IFDS.Xml.addSingleNode(_updateXML, "entityId", entityId);
			IFDS.Xml.addSingleNode(_updateXML, "VerifyRequestUUID", VerifyRequestUUID);
			doUpdate(_updateXML);
		}
		
		,checkVerifyButton : function() {
			updateVerifyButton();
		}
	}
}