/*********************************************************************************************
 * @file	GrantContrib.Controller.js	
 * @author	Rod Walker
 * @desc	Controller JS file for Grant Contributions screen
 *********************************************************************************************/

/*
 *  History : 
 *
 *  18 Nov 2015 Narin Suanlamyai P0241773 DFT0056449 T81754
 *      - Fixed JavaScript error when user click Cancel button. 
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _reloadView = 'dtGrantContribReload';
	var _nextStartRecNum = null;
	var _requestRecNum = 25;	
	var _taxType;
	
	// PRIVATE METHODS ****************************************	
	function populateGrantContrib(dataXML, more)
	{
		_taxType=IFDS.Xml.getNodeValue(dataXML, '//dtGrantContribReloadResponse/GrantContributionInfo/taxtype');
		_resources.grids['grantContrib'].getColumnModel().setHidden(2, true);
		if(_taxType == 'RS'){
			_resources.grids['grantContrib'].getColumnModel().setHidden(1, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(2, false);
			_resources.grids['grantContrib'].getColumnModel().setHidden(3, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(4, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(8, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(9, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(10, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(11, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(12, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(13, true);
			_resources.grids['grantContrib'].getColumnModel().setHidden(14, true);
			
		}
		if (more)
		{
			_resources.grids['grantContrib'].appendData(dataXML);
		}
		else
		{
			_resources.grids['grantContrib'].loadData(dataXML);
		}
				
		_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(dataXML);		
		if (_nextStartRecNum)
		{
			_resources.grids['grantContrib'].enableButton('moreBtn');
		}
		else
		{
			_resources.grids['grantContrib'].disableButton('moreBtn');
		}
	}

	
	// PUBLIC ITEMS *************************************
	return {
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_self.doReload(false);
		}
		
		,doReload: function(more)
		{
			var requestXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(requestXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(requestXML, 'respBenID', DesktopWeb._SCREEN_PARAM_MAP['RESPBenID']);
			IFDS.Xml.addSingleNode(requestXML, 'reasonCode', DesktopWeb._SCREEN_PARAM_MAP['ReasonCode']);
			IFDS.Xml.addSingleNode(requestXML, 'depositType', DesktopWeb._SCREEN_PARAM_MAP['DepositType']);
			IFDS.Xml.addSingleNode(requestXML, 'redCode', DesktopWeb._SCREEN_PARAM_MAP['RedCode']);
			IFDS.Xml.addSingleNode(requestXML, 'grAmount', DesktopWeb._SCREEN_PARAM_MAP['GRAmount']);
			IFDS.Xml.addSingleNode(requestXML, 'tradeDate', DesktopWeb._SCREEN_PARAM_MAP['TradeDate']);
			IFDS.Xml.addSingleNode(requestXML, 'startRecNum', (more ? _nextStartRecNum : 1));
			IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _requestRecNum);
			IFDS.Xml.addSingleNode(requestXML, 'PaymentDate', DesktopWeb._SCREEN_PARAM_MAP['PaymentDate']);

			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);			
			
			function responseHandler(success, responseXML)
			{
				DesktopWeb.Util.debugXML(responseXML);
				if (success)
				{
					populateGrantContrib(responseXML, more);
					
					
				}
			}
		}
		
		,getResult: function()
		{
			var selectedRecord = _resources.grids['grantContrib'].getSelectedRecord();
			var retString = "";
			
			if (selectedRecord) {
				retString += "EntityID=" + selectedRecord.data['entityID'];
				retString += ";"
					if(_taxType == 'RS'){
						retString += "TransID=" +selectedRecord.data['transNumber'];		
					}else{
						retString += "TransID=" + selectedRecord.data['transID'];
					}
				
			}
			
			return retString;
		}
	}	
}	