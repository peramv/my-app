/*********************************************************************************************
 * @file	
 * @author	
 * @desc	
 *********************************************************************************************/
 /*
 *  History :
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.  
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _searchView = "AccountSearch"	
	var _envSearchList = null;		
	var _collectTrackId = null;
	var _curSelection = null;
		
			
	// PRIVATE METHODS ***************************************
	function buildEnvSearchList()
	{
		_envSearchList = {};
		var envIdList = DesktopWeb._SCREEN_PARAM_MAP['envList'].split(";");
		for (var i = 0; i < envIdList.length; i++)
		{
			_envSearchList[envIdList[i]] = {status: null, resultsSet: null, resultsCount: null, rangeStartForNext: null, searchStr: null};	
		}
	}
	
	function initEnvSearchList()
	{
		var resultsContainer = Ext.getCmp('searchResultsContainer')
		resultsContainer.removeAll();
		for (var i in _envSearchList)
		{			
			_envSearchList[i].status = _self.SEARCHING;
			_envSearchList[i].searchStr = _resources.fields['searchValue'].getValue();
			_envSearchList[i].resultsSet = new DesktopWeb.ScreenResources.EnvResultsSet({
				envId: i				
				,columnModel: Ext.getCmp('searchResultsHeader').getColumnModel()
				,listeners: {
					select: function(envId, selection){updateCurSelection(envId, selection)}
					,more: function(envId){sendMoreRequest(envId)}
					,expand: function(panel){panel.el.scrollIntoView("searchResultsContainer");}
				}				
			})			
			_envSearchList[i].resultsSet.setStatusText('searching');
			resultsContainer.add(_envSearchList[i].resultsSet);			
		}
		resultsContainer.doLayout();
	}
			
	function sendSearchRequest(searchStr)
	{	
		_collectTrackId = null;
		var sprayerRequestXML = IFDS.Xml.newDocument("SprayerRequest");
		for (var i in _envSearchList)
		{
			IFDS.Xml.addSingleNode(sprayerRequestXML, 'EnvId', i);	
		}
		IFDS.Xml.addSingleNode(sprayerRequestXML, 'RequestPayload');

		var dataXML = IFDS.Xml.newDocument("data");
		IFDS.Xml.addSingleNode(dataXML, "searchValue", searchStr);
		IFDS.Xml.addSingleNode(dataXML, "maxRecords", "20");		
		var viewRequestXML = DesktopWeb.Ajax.buildSmartviewXML(_searchView, dataXML);			
							
		IFDS.Xml.appendNode(IFDS.Xml.getNode(sprayerRequestXML, 'RequestPayload'), viewRequestXML);
							
		DesktopWeb.Ajax.doServiceCall("SPRAY", null, null, sprayerRequestXML, responseHandler); 		
					
		function responseHandler(responseXML)
		{
			//prompt("SPRAY RESPONSE", responseXML.xml);
			if (IFDS.Xml.getNode(responseXML, 'SprayerResponse/RequestStatus/status') != null)
			{
				if (IFDS.Xml.getNodeValue(responseXML, 'SprayerResponse/RequestStatus/status') == 'Accepted')
				{
					_collectTrackId = IFDS.Xml.getNodeValue(responseXML, "SprayerResponse/TrackId");							
					fetchSearchResults()		
				}
				else
				{
					DesktopWeb.Util.displayError(_translationMap['ErrorProcessingSearchRequest']);
				}
			}
			else
			{
				DesktopWeb.Util.displayError(_translationMap['SearchRequestFailed']);
			}
		}
	}
	
	function fetchSearchResults()
	{		
		var collectRequestXML = IFDS.Xml.stringToXML("<CollectorRequest><trackId>" + _collectTrackId + "</trackId></CollectorRequest>");						
		DesktopWeb.Ajax.doServiceCall("COLLECT", null, null, collectRequestXML, responseHandler); 		
					
		function responseHandler(responseXML)
		{			
			//prompt("COLLECT RESPONSE", responseXML.xml);			
			if (IFDS.Xml.getNode(responseXML, 'CollectorResponse/RequestStatus/status') != null)
			{
				if (IFDS.Xml.getNodeValue(responseXML, 'CollectorResponse/RequestStatus/status').toLowerCase() == 'accepted')
				{					
					parseResults(IFDS.Xml.getNode(responseXML, 'CollectorResponse'));		
				}
				else
				{
					DesktopWeb.Util.displayError(_translationMap['FetchResultsError']);
				}
			}
			else
			{
				DesktopWeb.Util.displayError(_translationMap['FetchResultsFailed']);
			}
		}
	}
	
	function parseResults(responseXML)
	{		
		var outstandingResponses = false;
		for (var i in _envSearchList)
		{			
			if (_envSearchList[i].status == _self.SEARCHING)
			{
				var envResponseNode = IFDS.Xml.getNode(responseXML, 'Response[EnvId = "' + i + '"]');							
				if (envResponseNode != null)
				{
					_envSearchList[i].status = _self.RETURNED;
					var accountSearchResponseXML = IFDS.Xml.getNode(envResponseNode, 'ResponsePayLoad/AccountSearchResponse');
					if (accountSearchResponseXML)
					{							
						updateEnvSearch(i, accountSearchResponseXML, false);	
					}
					else
					{															
						_envSearchList[i].resultsSet.setStatusText(_translationMap['Error'].toLowerCase() + ': ' + _translationMap['ErrorStatus'].toLowerCase());						
					}						
				}
				else
				{
					outstandingResponses = true
				}
			}	
		}
		
		if (outstandingResponses)
		{
			fetchSearchResults.defer(250);
		}
	}
	
	function updateEnvSearch(envId, accountSearchResponseXML, appendResults)
	{						
		if (IFDS.Xml.getNodeValue(accountSearchResponseXML, 'RequestStatus/status').toLowerCase() == 'accepted')
		{																	
			if (IFDS.Xml.getNodeValue(accountSearchResponseXML, 'RecordRange/moreRecordsExist').toLowerCase() == 'yes')
			{
				_envSearchList[envId].rangeStartForNext = IFDS.Xml.getNodeValue(accountSearchResponseXML, 'RecordRange/rangeStartForNext');
				_envSearchList[envId].resultsSet.populate(accountSearchResponseXML, appendResults, true);	
			}
			else
			{
				_envSearchList[envId].rangeStartForNext = null;
				_envSearchList[envId].resultsSet.populate(accountSearchResponseXML, appendResults, false);
			}					
		}
		else
		{
			var errorNode = IFDS.Xml.getNode(accountSearchResponseXML, 'RequestStatus/Errors/Error'); 
			if (IFDS.Xml.getNodeValue(errorNode, 'errorCode') == '199')
			{
				_envSearchList[envId].resultsSet.setStatusText('no matches found');
			}
			else
			{
				_envSearchList[envId].resultsSet.setStatusText(_translationMap['Error'].toLowerCase() + ': ' + _translationMap['NoMatchesFound'].toLowerCase());	
			}				
		}						
	}
	
	function updateCurSelection(envId, record)
	{		
		if (_curSelection != null && _curSelection.envId != envId)
		{
			_envSearchList[_curSelection.envId].resultsSet.clearSelection();
		}
		
		_curSelection = {envId: envId, record: record};
	}

	function sendMoreRequest(envId)
	{
		var moreRequestXML = IFDS.Xml.newDocument("data");
		IFDS.Xml.addSingleNode(moreRequestXML, 'searchValue', _envSearchList[envId].searchStr);
		IFDS.Xml.addSingleNode(moreRequestXML, 'maxRecords', 20);
		IFDS.Xml.addSingleNode(moreRequestXML, 'startRecordNum', _envSearchList[envId].rangeStartForNext);

		var existingEnvName = DesktopWeb._SCREEN_PARAM_MAP['envName']
		DesktopWeb._SCREEN_PARAM_MAP['envName'] = envId;

		DesktopWeb.Ajax.doSmartviewAjax(_searchView, null, moreRequestXML, responseHandler);
		
		function responseHandler(success, responseXML)
		{													
			updateEnvSearch(envId, IFDS.Xml.getNode(responseXML, 'AccountSearchResponse'), true)
			DesktopWeb._SCREEN_PARAM_MAP['envName'] = existingEnvName;											
		}		
	}
	
	// PUBLIC ITEMS ******************************************
	return {
		SEARCHING: 1, RETURNED: 2
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			buildEnvSearchList();							
		}
		
		,doSearch: function()
		{			
			initEnvSearchList();
			sendSearchRequest(_resources.fields['searchValue'].getValue());
		}
		
		,getMore: function(envId)
		{
			sendMoreRequest(envId);
		}
		
		,getResult: function()
		{
			var result = "AccountNum=" + _curSelection.record.data['acctNum'] + ";Env=" + _curSelection.envId; 			
			return result;		
		}
		
		,getCurrentSelection: function()
		{
			return _curSelection;
		}	
	}	
}	