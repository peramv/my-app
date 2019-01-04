/*********************************************************************************************
 * @file	ClassSetup_EvenMain.Controller.js
 * @author	Cherdsak Sangkasen
 * @desc	Controller JS file for Event Schedule Maintenance screen 
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54443
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  07 May 2018 Pao - Supareuk S.
 *  		In goToScreen function, we changed a way to show the page from window.location 
 *  		using buildURL to DesktopWeb.Util.goToScreen. This is to solve an issue when 
 *  		user's profile has too many slot attached. If the session is included, the page
 *  		will be broken as too large.	
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _mstrXML = null;
	var _originalXML = null;
	var _initView = "dtEventMaintInit";
	var _allowedG1G2 = null;
	var _reloadView = "dtEventMaintReload";
	var _vldtView = "dtEventMaintProc";
	var _updateView = "dtEventMaintProc";
	var _eventCounter = 0;
	var _defaultValues = {};
	var _nextStartRecNum = null;
	var _requestRecNum = 30; 
	var _screenId = "EvenMain";
	var _listMap = null;
	
	// PRIVATE METHODS ****************************************	
	function populateDropdowns(responseXML)
	{
		_initView = IFDS.Xml.getNode(responseXML, "/SmartviewResponse/dtEventMaintInitResponse/EventList");
		
		if(_initView!= null) {
			_resources.fields['eventType'].loadData(IFDS.Xml.getNode(_initView, "List[@id = 'EventTypeList']"));
			_resources.fields['eventType'].enable();
			_resources.fields['eventType'].show();
		} else {
			_resources.fields['eventType'].disable();
			_resources.fields['eventType'].hide();
		}
		
	}

	function loadDropdowns(initViewXML)
	{	
		_listMap = {};		
		var listNodes = IFDS.Xml.getNodes(initViewXML, '/*//List');
		for (var i = 0; i < listNodes.length; i++)
		{
			var listName = IFDS.Xml.getNodeValue(listNodes[i], '@listName');
			if (!listName)
			{
				listName = IFDS.Xml.getNodeValue(listNodes[i], '@id');
			}			
			_listMap[listName] = listNodes[i];
		}
		
		if(_listMap['distribTypeListVal']) {
			_resources.fields['distributionType'].loadData(_listMap['distribTypeListVal']);
			_resources.fields['distributionIndicator'].loadData(_listMap['distribIndicatorListVal']);
			
			_defaultValues['distribType'] = IFDS.Xml.getNodeValue(initViewXML, "/*//ListSelection[@id = 'distribTypeListVal']");
			_defaultValues['distribIndicator'] = IFDS.Xml.getNodeValue(initViewXML, "/*//ListSelection[@id = 'distribIndicatorListVal']");
		}
		
	}
	
	function storeDefaultValues(xml)
	{
		_resources.fields['dtpStartDate'].setValue(null);
		_resources.fields['dtpEndDate'].setValue(null);
		
		_defaultValues['valnDate'] = "";		
		_defaultValues['crysFlag'] = false;
		_defaultValues['distFlag'] = false;
		_defaultValues['grdEnable'] = true;
		
		_defaultValues['eventDate'] = "";
		_defaultValues['exDate'] = "";
		_defaultValues['payDate'] = "";
		_defaultValues['reinvDate'] = "";
		_defaultValues['distribType'] = "";
		_defaultValues['distribIndicator'] = "";
		_defaultValues['grdEnableG1G2'] = true;
	}
	
	function createMstrXML(xml, more)
	{	
		if (!_mstrXML || !more)
		{			
			_mstrXML = IFDS.Xml.newDocument("Events");
		}		
		
		var eventXMLArr = IFDS.Xml.getNodes(xml, '//Events/Event');
		var valnXML = null;
		var crysXML = null;
		
		
		Ext.each(eventXMLArr, function(eventXML){
			IFDS.Xml.addSingleNode(eventXML, 'runMode', _self.UNCH);
			IFDS.Xml.addSingleNode(eventXML, 'updSeq', _self.SEQUNCH);
			IFDS.Xml.addSingleNode(eventXML, "eventType", _defaultValues['eventType']);

				if(!isValuationEvent()){ 
					IFDS.Xml.addSingleNode(eventXML, 'nodeID', "EXIST" + IFDS.Xml.getNodeValue(eventXML, 'eventDate'));
					IFDS.Xml.addSingleNode(eventXML, 'nodeID', "EXIST" + IFDS.Xml.getNodeValue(eventXML, 'exDate'));
					IFDS.Xml.addSingleNode(eventXML, 'nodeID', "EXIST" + IFDS.Xml.getNodeValue(eventXML, 'payDate'));
					IFDS.Xml.addSingleNode(eventXML, 'nodeID', "EXIST" + IFDS.Xml.getNodeValue(eventXML, 'reinvDate'));
					IFDS.Xml.addSingleNode(eventXML, 'nodeID', "EXIST" + IFDS.Xml.getNodeValue(eventXML, 'distribType'));
					IFDS.Xml.addSingleNode(eventXML, 'nodeID', "EXIST" + IFDS.Xml.getNodeValue(eventXML, 'distribIndicator'));
					IFDS.Xml.addSingleNode(eventXML, 'oldEventDate',IFDS.Xml.getNodeValue(eventXML, 'eventDate'));
					IFDS.Xml.addSingleNode(eventXML, 'version', IFDS.Xml.getNodeValue(eventXML, 'version'));
			
				} else 
				{
					IFDS.Xml.addSingleNode(eventXML, 'nodeID', "EXIST" + IFDS.Xml.getNodeValue(eventXML, 'valnDate'));
				
					if (!IFDS.Xml.getNode(eventXML, "ValnDetl")) 
					{
						IFDS.Xml.addSingleNode(eventXML, 'viewValnDetl', _self.NO);
						valnXML = IFDS.Xml.newDocument("ValnDetl");				
						IFDS.Xml.addSingleNode(valnXML, 'gav');	
						IFDS.Xml.addSingleNode(valnXML, 'nav');
						IFDS.Xml.addSingleNode(valnXML, 'clsHWM');
						IFDS.Xml.addSingleNode(valnXML, 'clsHWMdate');
						IFDS.Xml.addSingleNode(valnXML, 'numDay');
						IFDS.Xml.addSingleNode(valnXML, 'effHurdle');
						IFDS.Xml.addSingleNode(valnXML, 'clsAdjHWM');
						IFDS.Xml.addSingleNode(valnXML, 'pfPerShare');
						IFDS.Xml.appendNode(eventXML, valnXML);
					}
					else 
					{
						IFDS.Xml.addSingleNode(eventXML, 'viewValnDetl', _self.YES);
					}
					
					if (!IFDS.Xml.getNode(eventXML, "CrysDetl")) 
					{
						IFDS.Xml.addSingleNode(eventXML, 'viewCrysDetl', _self.NO);
						crysXML = IFDS.Xml.newDocument("CrysDetl");				
						IFDS.Xml.addSingleNode(crysXML, 'gav');	
						IFDS.Xml.addSingleNode(crysXML, 'clsHWM');
						IFDS.Xml.appendNode(eventXML, crysXML);
					}
					else
					{
						IFDS.Xml.addSingleNode(eventXML, 'viewCrysDetl', _self.YES);
					}
				}
			
			IFDS.Xml.appendNode(_mstrXML, eventXML);				
		});
	}
	
	function isValuationEvent ()
	{
		  if (_initView != null && (_defaultValues['eventType'] != '01')) {
				return false;
		  }
		  else {
				return true;
		  }
	}
	
	function getEvent(xml, nodeID)
	{
		var index = 0;		
		var eventXMLArr = IFDS.Xml.getNodes(xml, '//Events/Event');
		for (var i = 0; i < eventXMLArr.length; i++)
		{			
			if (IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID') == nodeID)
			{		
				return {
					node : eventXMLArr[i], 
					index : index,
					runMode : IFDS.Xml.getNodeValue(eventXMLArr[i], 'runMode'),
					nodeID : IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID'),
					valnDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(eventXMLArr[i], 'valnDate')),
					crysFlag : IFDS.Xml.getNodeValue(eventXMLArr[i], 'crysFlag'),
					distFlag : IFDS.Xml.getNodeValue(eventXMLArr[i], 'distFlag'),
					priceExist : IFDS.Xml.getNodeValue(eventXMLArr[i], 'priceExist'),
					viewValnDetl : IFDS.Xml.getNodeValue(eventXMLArr[i], 'viewValnDetl'),
					viewCrysDetl : IFDS.Xml.getNodeValue(eventXMLArr[i], 'viewCrysDetl'),
					valnGav : IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/gav'),
					valnNav : IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/nav'),
					valnClsHWM : IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/clsHWM'),
					valnClsHWMDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/clsHWMdate')),
					valnNumDay : IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/numDay'),
					valnEffHurdle : IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/effHurdle'),
					valnClsAdjHWM : IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/clsAdjHWM'),
					valnPfPerShare : IFDS.Xml.getNodeValue(eventXMLArr[i], 'ValnDetl/pfPerShare'),
					crysGav : IFDS.Xml.getNodeValue(eventXMLArr[i], 'CrysDetl/gav'),
					crysClsHWM : IFDS.Xml.getNodeValue(eventXMLArr[i], 'CrysDetl/clsHWM'),
					allowUpd : IFDS.Xml.getNodeValue(eventXMLArr[i], 'allowUpd'),
					version : IFDS.Xml.getNodeValue(eventXMLArr[i], 'version')
				};
			}
			if (IFDS.Xml.getNodeValue(eventXMLArr[i], 'runMode') != _self.DEL)
			{
				index += 1;
			}
		}			
	}
	
	function getEventG1G2(xml, nodeID)
	{
		var index = 0;		
		var eventXMLArr = IFDS.Xml.getNodes(xml, '//Events/Event');
      
		for (var i = 0; i < eventXMLArr.length; i++)
		{		
			if (IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID') == nodeID)
			{				
				return {
					node : eventXMLArr[i], 
					index : index,
					runMode : IFDS.Xml.getNodeValue(eventXMLArr[i], 'runMode'),
					nodeID : IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID'),
					eventDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(eventXMLArr[i], 'eventDate')),
					exDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(eventXMLArr[i], 'exDate')),
					payDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(eventXMLArr[i], 'payDate')),
					reinvDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(eventXMLArr[i], 'reinvDate')),
					distribType : IFDS.Xml.getNodeValue(eventXMLArr[i], 'distribType'),
					distribIndicator : IFDS.Xml.getNodeValue(eventXMLArr[i], 'distribIndicator'),
					allowUpd : IFDS.Xml.getNodeValue(eventXMLArr[i], 'allowUpd'),
					allowUpdAttrb : IFDS.Xml.getNodeValue(eventXMLArr[i], 'allowUpdAttrb'),
					eventType : IFDS.Xml.getNodeValue(eventXMLArr[i], 'eventType'),
					oldEventDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(eventXMLArr[i], 'oldEventDate')),
					version : IFDS.Xml.getNodeValue(eventXMLArr[i], 'version')
				};
				
			}
			if (IFDS.Xml.getNodeValue(eventXMLArr[i], 'runMode') != _self.DEL)
			{
				index += 1;
			}
			
		}			
	}
	
	function getValidateEventRequest (obj, action, data)
	{
		var requestXML = IFDS.Xml.newDocument("data");
	
		IFDS.Xml.addSingleNode(requestXML, "procMode", "validation");
		IFDS.Xml.addSingleNode(requestXML, "fund", _defaultValues['fund']);
		IFDS.Xml.addSingleNode(requestXML, "class", _defaultValues['class']);

		var eventsXML = IFDS.Xml.newDocument("Events");
		var eventXML = IFDS.Xml.newDocument("Event");
		IFDS.Xml.addSingleNode(eventXML, "updMode", action);
		IFDS.Xml.addSingleNode(eventXML, "updSeq");
		IFDS.Xml.addSingleNode(eventXML, "eventType", _defaultValues['eventType']);

		if (!isValuationEvent()) {
			IFDS.Xml.addSingleNode(eventXML, "eventDate", data['eventDate']);
			IFDS.Xml.addSingleNode(eventXML, "oldEventDate", data['eventDate']);
			IFDS.Xml.addSingleNode(eventXML, "ExDate", data['exDate']);
			IFDS.Xml.addSingleNode(eventXML, "PayDate", data['payDate']);
			IFDS.Xml.addSingleNode(eventXML, "RnvstdDate", data['reinvDate']);
			IFDS.Xml.addSingleNode(eventXML, "DistribType", data['distribType']);
			IFDS.Xml.addSingleNode(eventXML, "DistribIndctr", data['distribIndicator']);
		} else {
		
			IFDS.Xml.addSingleNode(eventXML, "valnDate", data['valnDate']);
			IFDS.Xml.addSingleNode(eventXML, "crysFlag", (data['crysFlag'] ? _self.YES : _self.NO));
			IFDS.Xml.addSingleNode(eventXML, "distFlag", (data['distFlag'] ? _self.YES : _self.NO));
		}
		
		IFDS.Xml.addSingleNode(eventXML, "version", data['version']);

		IFDS.Xml.appendNode(eventsXML,eventXML);
		return IFDS.Xml.appendNode(requestXML, eventsXML);


	}
	
	function getUpdateRequest()
	{		
		var requestXML = IFDS.Xml.newDocument("data");
		var newEvent = null;
		var runMode = null;
		var updEventXML = null;
	
		IFDS.Xml.addSingleNode(requestXML, "procMode", "process");
		IFDS.Xml.addSingleNode(requestXML, "fund", _defaultValues['fund']);
		IFDS.Xml.addSingleNode(requestXML, "class", _defaultValues['class']);

		var xml = IFDS.Xml.newDocument("Events");
		var event = null;
		
		var eventXMLArr = IFDS.Xml.getNodes(_mstrXML, '//Events/Event');				
		for (var i = 0; i < eventXMLArr.length; i++)
		{				
			runMode = IFDS.Xml.getNodeValue(eventXMLArr[i], 'runMode');
			
			if (IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID').indexOf("NEWEVENT") > -1)
			{
				newEvent = true;
			}
			else 
			{
				newEvent = false;
				
				if (isValuationEvent()) {
					originalEvent = getEvent(_originalXML, IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID'));
				} else {
					originalEvent = getEventG1G2(_originalXML, IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID'));
				}
				
				if (originalEvent.crysFlag == IFDS.Xml.getNodeValue(eventXMLArr[i], 'crysFlag') &&
					originalEvent.distFlag == IFDS.Xml.getNodeValue(eventXMLArr[i], 'distFlag') &&
					runMode != _self.DEL)
				{
					runMode = _self.UNCH;
				}
			}			
					
			if  (!(newEvent && runMode == _self.DEL) && 
				!(runMode == _self.UNCH))
			{
				updEventXML = IFDS.Xml.newDocument("Event");				
				IFDS.Xml.addAttribute(IFDS.Xml.getNode(updEventXML, "."), 'RecordSource', IFDS.Xml.getNodeValue(eventXMLArr[i], 'nodeID'));
				
				if (newEvent)
				{
					IFDS.Xml.addSingleNode(updEventXML, 'updMode', _self.ADD);
					IFDS.Xml.addSingleNode(updEventXML, 'updSeq', _self.SEQADD);
					IFDS.Xml.addSingleNode(updEventXML, "eventType", _defaultValues['eventType']);
					IFDS.Xml.addSingleNode(updEventXML, 'version', IFDS.Xml.getNodeValue(eventXMLArr[i], 'version'));
				}
				else
				{
					IFDS.Xml.addSingleNode(updEventXML, 'updMode', runMode);
					IFDS.Xml.addSingleNode(updEventXML, 'updSeq', IFDS.Xml.getNodeValue(eventXMLArr[i], 'updSeq'));		
					IFDS.Xml.addSingleNode(updEventXML, "eventType", _defaultValues['eventType']);
					IFDS.Xml.addSingleNode(updEventXML, 'oldEventDate', IFDS.Xml.getNodeValue(eventXMLArr[i], 'eventDate'));
					IFDS.Xml.addSingleNode(updEventXML, 'version',  IFDS.Xml.getNodeValue(eventXMLArr[i], 'version'));
				}
				//g1g2 
				if (!isValuationEvent()) 
				{
					IFDS.Xml.addSingleNode(updEventXML, 'eventDate', IFDS.Xml.getNodeValue(eventXMLArr[i], 'eventDate'));
					IFDS.Xml.addSingleNode(updEventXML, 'ExDate', IFDS.Xml.getNodeValue(eventXMLArr[i], 'exDate'));
					IFDS.Xml.addSingleNode(updEventXML, 'PayDate', IFDS.Xml.getNodeValue(eventXMLArr[i], 'payDate'));
					IFDS.Xml.addSingleNode(updEventXML, 'RnvstdDate', IFDS.Xml.getNodeValue(eventXMLArr[i], 'reinvDate'));
					IFDS.Xml.addSingleNode(updEventXML, 'DistribType', IFDS.Xml.getNodeValue(eventXMLArr[i], 'distribType'));
					IFDS.Xml.addSingleNode(updEventXML, 'DistribIndctr', IFDS.Xml.getNodeValue(eventXMLArr[i], 'distribIndicator'));
					
				}else {
					IFDS.Xml.addSingleNode(updEventXML, 'valnDate', IFDS.Xml.getNodeValue(eventXMLArr[i], 'valnDate'));
					IFDS.Xml.addSingleNode(updEventXML, 'crysFlag', IFDS.Xml.getNodeValue(eventXMLArr[i], 'crysFlag'));
					IFDS.Xml.addSingleNode(updEventXML, 'distFlag', IFDS.Xml.getNodeValue(eventXMLArr[i], 'distFlag'));	
				}
							
				IFDS.Xml.appendNode(xml, updEventXML);
			}
		}
		return IFDS.Xml.appendNode(requestXML, xml);
		
	}
	
	function addNewEventToMstrXML(data)
	{
		var mObj;
		var oObj;
		var oObjG1G2;
		
		if (!_mstrXML)
		{			
			_mstrXML = IFDS.Xml.newDocument("Events");
		}		
		
		oObj = getEvent(_originalXML, "EXIST" + data['valnDate']);
		oObjG1G2 = getEventG1G2(_originalXML, "EXIST" + data['eventDate']);
		
		if (oObj)
		{
			mObj = getEvent(_mstrXML, "EXIST" + data['valnDate']);
			if (mObj.runMode = _self.DEL)
			{
				updateEventToMstr(mObj.nodeID, data);
			}
		} else if (oObjG1G2) 
		{
			mObj = getEventG1G2(_mstrXML, "EXIST" + data['eventDate']);
			if (mObj.runMode = _self.DEL)
			{
				updateEventToMstr(mObj.nodeID, data);
			}
		}
		else
		{
			_eventCounter += 1;
			var newEventXML = IFDS.Xml.newDocument("Event");	
			
			IFDS.Xml.addSingleNode(newEventXML, 'runMode', _self.ADD);
			IFDS.Xml.addSingleNode(newEventXML, 'updSeq', _self.SEQADD);
			IFDS.Xml.addSingleNode(newEventXML, 'nodeID', "NEWEVENT" + _eventCounter);
			IFDS.Xml.addSingleNode(newEventXML, 'valnDate', data['valnDate']);
			IFDS.Xml.addSingleNode(newEventXML, 'allowUpd', _self.YES);
			IFDS.Xml.addSingleNode(newEventXML, 'crysFlag', (data['crysFlag'] ? _self.YES : _self.NO));
			IFDS.Xml.addSingleNode(newEventXML, 'distFlag', (data['distFlag'] ? _self.YES : _self.NO));
			IFDS.Xml.addSingleNode(newEventXML, 'priceExist', _self.NO);
			IFDS.Xml.addSingleNode(newEventXML, 'version', '1');
			IFDS.Xml.addSingleNode(newEventXML, 'viewValnDetl', _self.NO);
			IFDS.Xml.addSingleNode(newEventXML, 'viewCrysDetl', _self.NO);
			IFDS.Xml.addSingleNode(newEventXML, "eventType", _defaultValues['eventType']);
	
			if(!isValuationEvent()) {
				IFDS.Xml.addSingleNode(newEventXML, 'eventDate', data['eventDate']);
				IFDS.Xml.addSingleNode(newEventXML, 'exDate', data['exDate']);
				IFDS.Xml.addSingleNode(newEventXML, 'payDate', data['payDate']);
				IFDS.Xml.addSingleNode(newEventXML, 'reinvDate', data['reinvDate']);
				IFDS.Xml.addSingleNode(newEventXML, 'distribType', data['distribType']);
				IFDS.Xml.addSingleNode(newEventXML, 'distribIndicator', data['distribIndicator']);
			}
			
			var newValnDetl = IFDS.Xml.newDocument("ValnDetl");
			IFDS.Xml.addSingleNode(newValnDetl, 'gav');	
			IFDS.Xml.addSingleNode(newValnDetl, 'nav');
			IFDS.Xml.addSingleNode(newValnDetl, 'clsHWM');
			IFDS.Xml.addSingleNode(newValnDetl, 'clsHWMdate');
			IFDS.Xml.addSingleNode(newValnDetl, 'numDay');
			IFDS.Xml.addSingleNode(newValnDetl, 'effHurdle');
			IFDS.Xml.addSingleNode(newValnDetl, 'clsAdjHWM');
			IFDS.Xml.addSingleNode(newValnDetl, 'pfPerShare');
			IFDS.Xml.appendNode(newEventXML, newValnDetl);
			
			var newCrysDetl = IFDS.Xml.newDocument("CrysDetl");
			IFDS.Xml.addSingleNode(newCrysDetl, 'gav');
			IFDS.Xml.addSingleNode(newCrysDetl, 'clsHWM');
			IFDS.Xml.appendNode(newEventXML, newCrysDetl);
			
			IFDS.Xml.appendNode(_mstrXML, newEventXML);
		
		}
		_self.updatesFlag = true;
	}
	
	function updateEventToMstr(nodeID, data)
	{
		var event = null;
		if(isValuationEvent()) {
			event = getEvent(_mstrXML, nodeID);
		} else {
			event = getEventG1G2(_mstrXML, nodeID);	
		}
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'runMode'), _self.MOD);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'updSeq'), _self.SEQMOD);
		
		if(!isValuationEvent()) {
		   IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'eventDate'),  data['eventDate']);
		   IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'exDate'),  data['exDate']);
		   IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'payDate'),  data['payDate']);
		   IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'reinvDate'),  data['reinvDate']);
		   IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'distribType'),  data['distribType']);
		   IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'distribIndicator'),  data['distribIndicator']);
		   IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'eventType'), _defaultValues['eventType']);
		} else {
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'crysFlag'), (data['crysFlag'] ? _self.YES : _self.NO));
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'distFlag'), (data['distFlag'] ? _self.YES : _self.NO));
      }
		_self.updatesFlag = true;	
		
		return event.index;
	}
	
	function deleteEventFromMstr(nodeID)
	{		
		var event = null;
		if(isValuationEvent()) {
			event = getEvent(_mstrXML, nodeID);	
		} else {
			event = getEventG1G2(_mstrXML, nodeID);	
        }			
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'runMode'), _self.DEL);				
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'updSeq'), _self.SEQDEL);
		_self.updatesFlag = true;
	}
	
	function storeContextErrors(errorNodes)
	{
		clearErrMsg();
		var focusIdx = 0;
		
		for (var i = 0; i < errorNodes.length; i++)
		{		
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			
			var nodeID = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');			
			
			var event = null;
			if(isValuationEvent()) {
				event = getEvent(_mstrXML, nodeID);	
			} else {
				event = getEventG1G2(_mstrXML, nodeID);	
			}
			if (!IFDS.Xml.getNode(event.node, 'errMsg'))		
			{				
				IFDS.Xml.addSingleNode(event.node, 'errMsg', errMsg);		
			}
			if (event.runMode == _self.DEL)
			{
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'runMode'), _self.UNCH);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(event.node, 'updSeq'), _self.SEQUNCH);
			}
			if (focusIdx == 0)
			{
				focusIdx = event.index;
			}
		}

		_self.refreshGrdEvent(focusIdx);		
	}
	
	function clearErrMsg()
	{
		var eventXMLArr = IFDS.Xml.getNodes(_mstrXML, '//Events/Event');
		for (var i = 0; i < eventXMLArr.length; i++)
		{
			if (IFDS.Xml.getNode(eventXMLArr[i], 'errMsg'))		
			{				
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(eventXMLArr[i], 'errMsg'));
			}			
		}
	}
	
	function gotoDetailscreen(vFund, vClass, vFndClsDisp, vValnDate, vStartDate, vEndDate)
	{
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_ValuationBasic';
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		urlParams['prevScreen'] = _screenId;
		urlParams['fund'] = vFund;
		urlParams['class'] = vClass;
		urlParams['fndClsDisp'] = vFndClsDisp;
    	urlParams['valnDate'] = DesktopWeb.Util.getSMVDateValue(vValnDate);
		urlParams['startDate'] = vStartDate;
		urlParams['endDate'] = vEndDate;
		urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
									
		DesktopWeb.Util.goToScreen('ClassSetup_ValuationBasic', urlParams);
	}
	
	function loadDefaultFundClass(vFund, vClass, vFndClsDisp)
	{
		var newDataXML = IFDS.Xml.newDocument("data");	
		var possibleMatchXML = IFDS.Xml.addSingleNode(newDataXML, 'PossibleMatch');
		
		IFDS.Xml.addSingleNode(possibleMatchXML, 'fndClsDisp', vFndClsDisp);
		IFDS.Xml.addSingleNode(possibleMatchXML, 'fundCode', vFund);
		IFDS.Xml.addSingleNode(possibleMatchXML, 'classCode', vClass);
		
		_resources.fields['cboFundClass'].getStore().loadData(newDataXML);
		_resources.fields['cboFundClass'].setValue(vFndClsDisp);
	}
	
	function setG1G2GridButtons(vSelectedRow)
	{
		if ((vSelectedRow.allowUpd != null && vSelectedRow.allowUpd == _self.YES) && 
			(vSelectedRow.allowUpdAttrb != null && vSelectedRow.allowUpdAttrb == _self.YES)) {
				_self.enableButtonsG1G2(_self.YES);
		} else if ((vSelectedRow.allowUpd != null && vSelectedRow.allowUpd == _self.NO) && 
			(vSelectedRow.allowUpdAttrb != null && vSelectedRow.allowUpdAttrb == _self.YES)) {
			_self.enableButtonsG1G2(_self.PARTIAL);
		} else {
			_self.enableButtonsG1G2(_self.NO);
		}
	}
	
	function disableRecordDateField()
	{
		_resources.fields['dtpRecordDate'].disable();
		
		if (_resources.popups['frmAddModEventG1G2'].action ==_self.ADD ) {
					_resources.fields['dtpRecordDate'].enable();
		} 
	}
	
	// PUBLIC ITEMS *************************************
	return {	
		ADD: 'add'
		, MOD: 'mod'
		, DEL: 'del'
		, UNCH: 'unch'	
		, SEQADD: '3'
		, SEQMOD: '2'
		, SEQDEL: '1'
		, SEQUNCH: '0'
		, YES: 'yes'
		, NO: 'no'
		, NONE: 'none'
		, ALL: 'all'
		, PARTIAL: 'partial'
		, updatesFlag: false			
		, init: function(res)
		{	
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_resources.grids['grdEvent'].hide();
			_resources.grids['grdEventG1G2'].hide();
					
			
			var requestXML = IFDS.Xml.newDocument("data");			
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['Load']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{																							
					populateDropdowns(responseXML);
					storeDefaultValues(responseXML);
					_self.enableButtons(_self.NONE);
					_self.enableButtonsG1G2(_self.NONE);
					_self.enableMoreButton(_nextStartRecNum);
					Ext.getCmp('valuation_fieldset').hide();
					Ext.getCmp('crystalisation_fieldset').hide();
					Ext.getCmp('expand').hide();
					
					loadDropdowns(responseXML);	
					
					if (DesktopWeb._SCREEN_PARAM_MAP['prevScreen'])
					{						
						_resources.fields['dtpStartDate'].setValue(DesktopWeb._SCREEN_PARAM_MAP['startDate']);
						_resources.fields['dtpEndDate'].setValue(DesktopWeb._SCREEN_PARAM_MAP['endDate']);
						_resources.fields['dtpRecordDate'].setValue(DesktopWeb._SCREEN_PARAM_MAP['eventDate']);
						loadDefaultFundClass(DesktopWeb._SCREEN_PARAM_MAP['fund'], DesktopWeb._SCREEN_PARAM_MAP['class'], DesktopWeb._SCREEN_PARAM_MAP['fndClsDisp']);
						_self.doSearch(false);
					}
				}
			}
		}
		
		, doSearch: function(more)
		{
		
			if (_self.readyToSearch())
			{
				_defaultValues['fund'] = _resources.fields['cboFundClass'].selectedRecord.get('fundCode');
				_defaultValues['class'] = _resources.fields['cboFundClass'].selectedRecord.get('classCode');							
				_defaultValues['fndClsDisp'] = _resources.fields['cboFundClass'].selectedRecord.get('fndClsDisp');	
				_defaultValues['eventType'] = _resources.fields['eventType'].getValue();	
			
				_defaultValues['startDate'] = _resources.fields['dtpStartDate'].getDisplayDateString();
				_defaultValues['endDate'] = _resources.fields['dtpEndDate'].getDisplayDateString();					
				
				var requestXML = IFDS.Xml.newDocument("data");		
				IFDS.Xml.addSingleNode(requestXML, "fund", _defaultValues['fund']);	
				IFDS.Xml.addSingleNode(requestXML, "class", _defaultValues['class']);
				IFDS.Xml.addSingleNode(requestXML, "startDate", _resources.fields['dtpStartDate'].getSMVDateString());
				IFDS.Xml.addSingleNode(requestXML, "endDate", _resources.fields['dtpEndDate'].getSMVDateString());
				IFDS.Xml.addSingleNode(requestXML, "startRecNum", (more ? _nextStartRecNum : 1));
				IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);		
				IFDS.Xml.addSingleNode(requestXML, "eventType", _defaultValues['eventType']);
				
				if (requestXML)
				{
					DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['Search']);

					function responseHandler(success, responseXML)
					{
						if (success)
						{		
							if (isValuationEvent())
							{
								_resources.grids['grdEvent'].enable();	
								_resources.grids['grdEvent'].show();
								_defaultValues['grdEnable'] = true;
								Ext.getCmp('valuation_fieldset').hide();
								Ext.getCmp('crystalisation_fieldset').hide();
								_resources.grids['grdEventG1G2'].disable();	
								_resources.grids['grdEventG1G2'].hide();
								_defaultValues['grdEnableG1G2'] = false;
							} else {
								_allowedG1G2 = IFDS.Xml.getNodeValue(responseXML, "//eventDateAddAllowed");
								if (_allowedG1G2 == _self.NO) {
									_resources.grids['grdEventG1G2'].disable();	
									_resources.grids['grdEventG1G2'].show();
								} else {
									_defaultValues['grdEnableG1G2'] = true;
									_resources.grids['grdEventG1G2'].enable();	
									_resources.grids['grdEventG1G2'].show();
								}
								_resources.grids['grdEvent'].disable();	
								_resources.grids['grdEvent'].hide();
								_defaultValues['grdEnable'] = false;
							}
							
							createMstrXML(responseXML, more);			
							_defaultValues['perfFee'] = IFDS.Xml.getNodeValue(responseXML, '//perfFee');
							_originalXML = IFDS.Xml.cloneDocument(_mstrXML);
							_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
							_self.refreshGrdEvent(0);	
							_self.enableMoreButton(_nextStartRecNum);
						
							if (isValuationEvent())
							{
								if(!_resources.grids['grdEvent'].getSelectedRecord()) {
									_self.enableButtons(_self.NONE);
								}
							} else {
								var selectReordG1G2 = _resources.grids['grdEventG1G2'].getSelectedRecord();

								if (!selectReordG1G2 && !isValuationEvent())
								{
									_self.enableButtonsG1G2(_self.NONE);
								} else {
									_self.enableButtonsG1G2(_self.YES);
									var obj = _self.getSelectedEventG1G2();
									setG1G2GridButtons(obj);
								}
							}
						}
					}
				}	
			}
		}
		
		, openActionPopup: function(popupName, action)
		{
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();
			disableRecordDateField();
		}
		
		, readyToSearch: function()
		{
			var retVal = true;

			if ( _resources.fields['cboFundClass'].getValue() != "" &&
					_resources.fields['dtpStartDate'].getValue() != "" &&
					_resources.fields['dtpEndDate'].getValue() != "" )
			{
				if(_initView != null && _resources.fields['eventType'].getValue() == "") {
					retVal = false;
				} else {
					retVal = true;
				}
			}
			else
			{
				if (_resources.fields['cboFundClass'].getValue() == "" ) { _resources.fields['cboFundClass'].markInvalid("This field is required"); } 
				if (_resources.fields['dtpStartDate'].getValue() == "" ) { _resources.fields['dtpStartDate'].markInvalid("This field is required"); } 
				if (_resources.fields['dtpEndDate'].getValue() == "" ) { _resources.fields['dtpEndDate'].markInvalid("This field is required"); } 
				if (_resources.fields['eventType'].getValue() == "" ) { _resources.fields['eventType'].markInvalid("This field is required"); } 
				retVal = false;
			}
			
			return retVal;
		}
		
		, refreshGrdEvent: function(index)
		{	
			if(isValuationEvent()) {
				_resources.grids['grdEvent'].loadData(_mstrXML);
				_resources.grids['grdEvent'].setSelectedRecord(index);	
			} else {		
				_resources.grids['grdEventG1G2'].loadData(_mstrXML);
				_resources.grids['grdEventG1G2'].setSelectedRecord(index);
			}
		}
		
		, setSelectedEvent: function(nodeID) 
		{
			var event = getEvent(_mstrXML, nodeID);
			
			if(!isValuationEvent()) {
				event = getEventG1G2(_mstrXML, nodeID);
			} 
			
			if (event) 
			{
				if (event.viewValnDetl == _self.YES) 
				{
					if (_defaultValues['perfFee'] == _self.YES && event.priceExist == _self.YES)
					{
						_self.populateValnDetl(event);
						Ext.getCmp('valuation_fieldset').show();
						Ext.getCmp('expand').show();
					}
					else
					{
						Ext.getCmp('valuation_fieldset').hide();
						Ext.getCmp('expand').hide();
					}
				}
				else 
				{
					Ext.getCmp('valuation_fieldset').hide();
					if (event.priceExist == _self.YES)
					{
						Ext.getCmp('expand').show();
					}
					else 
					{
						Ext.getCmp('expand').hide();
					}
				}

				if (event.viewCrysDetl == _self.YES) 
				{
					_self.populateCrysDetl(event);
					Ext.getCmp('crystalisation_fieldset').show();
				}
				else 
				{
					Ext.getCmp('crystalisation_fieldset').hide();
				}	

				if(isValuationEvent()) {
					_self.enableButtons(event.allowUpd);	
				} else {
					setG1G2GridButtons(event);
				}				
			}
			else
			{
				Ext.getCmp('valuation_fieldset').hide();
				Ext.getCmp('crystalisation_fieldset').hide();
				Ext.getCmp('expand').hide();
				_self.enableButtons(_self.NO);	
				_self.enableButtonsG1G2(_self.NO);	
			}
		}
		
		, populateValnDetl: function(event)
		{
			_resources.fields['valnGav'].setText(event.valnGav);
			_resources.fields['valnNav'].setText(event.valnNav);
			_resources.fields['valnClsHWM'].setText(event.valnClsHWM);
			_resources.fields['valnClsHWMDate'].setText(event.valnClsHWMDate);
			_resources.fields['valnNumDay'].setText(event.valnNumDay);
			_resources.fields['valnEffHurdle'].setText(event.valnEffHurdle);
			_resources.fields['valnClsAdjHWM'].setText(event.valnClsAdjHWM);
			_resources.fields['valnPfPerShare'].setText(event.valnPfPerShare);
		}
		
		, populateCrysDetl: function(event)
		{
			_resources.fields['crysClsHWM'].setText(event.crysClsHWM);
			_resources.fields['crysGav'].setText(event.crysGav);
		}
		
		, enableButtons: function(flag)
		{
			switch (flag)
			{
				case _self.NONE:
				{
					_resources.grids['grdEvent'].disableButton(0);
					_resources.grids['grdEvent'].disableButton(1);
					_resources.grids['grdEvent'].disableButton(2);
					break;
				}
				case _self.YES:
				{
					_resources.grids['grdEvent'].enableButton(0);
					_resources.grids['grdEvent'].enableButton(1);
					_resources.grids['grdEvent'].enableButton(2);
					break;
				}
				case _self.NO:
				{
					_resources.grids['grdEvent'].enableButton(0);
					_resources.grids['grdEvent'].disableButton(1);
					_resources.grids['grdEvent'].disableButton(2);
					break;
				}
				case _self.ALL:
				{	
					_resources.grids['grdEvent'].enableButton(0);
					_resources.grids['grdEvent'].enableButton(1);
					_resources.grids['grdEvent'].enableButton(2);
					break;
				}
			}
		}

		
		, enableButtonsG1G2: function(flag)
		{
			switch (flag)
			{
				case _self.NONE:
				{
					_resources.grids['grdEventG1G2'].enableButton(0);
					_resources.grids['grdEventG1G2'].disableButton(1);
					_resources.grids['grdEventG1G2'].disableButton(2);
					break;
				}
				case _self.YES:
				{
					_resources.grids['grdEventG1G2'].enableButton(0);
					_resources.grids['grdEventG1G2'].enableButton(1);
					_resources.grids['grdEventG1G2'].enableButton(2);
					break;
				}
				case _self.NO:
				{
					_resources.grids['grdEventG1G2'].enableButton(0);
					_resources.grids['grdEventG1G2'].disableButton(1);
					_resources.grids['grdEventG1G2'].disableButton(2);
					break;
				}
				case _self.ALL:
				{	
					_resources.grids['grdEventG1G2'].enableButton(0);
					_resources.grids['grdEventG1G2'].enableButton(1);
					_resources.grids['grdEventG1G2'].enableButton(2);
					break;
				}
				case _self.PARTIAL:
				{	
					_resources.grids['grdEventG1G2'].enableButton(0);
					_resources.grids['grdEventG1G2'].enableButton(1);
					_resources.grids['grdEventG1G2'].disableButton(2);
					break;
				}
			}
		}
		
		, enableMoreButton: function (moreRec)
		{
			if (moreRec)
			{
				if(isValuationEvent()) {
					_resources.grids['grdEvent'].enableButton(3);
				} else {
					_resources.grids['grdEventG1G2'].enableButton(3);
				}
			}
			else
			{
				if(isValuationEvent()) {
					_resources.grids['grdEvent'].disableButton(3);
				} else {
					_resources.grids['grdEventG1G2'].disableButton(3);
				}
			}	
		}
		
		, setDefaultNewEvent: function()
		{
			_resources.fields['dtpValudationDate'].setValue(_defaultValues['valnDate']);
			_resources.fields['chkCrystalisation'].setValue(_defaultValues['crysFlag']);		
			_resources.fields['chkDistribution'].setValue(_defaultValues['distFlag']);
				
			_resources.fields['dtpRecordDate'].setValue(_defaultValues['eventDate']);
			_resources.fields['dtpExDate'].setValue(_defaultValues['exDate']);
			_resources.fields['dtpPayDate'].setValue(_defaultValues['payDate']);
			_resources.fields['dtpReinvestDate'].setValue(_defaultValues['reinvDate']);
			_resources.fields['distributionType'].setValue(_defaultValues['distribType']);
			_resources.fields['distributionIndicator'].setValue(_defaultValues['distribIndicator']);

			if (_defaultValues['perfFee'] == _self.YES)
			{
				_resources.fields['chkCrystalisation'].enableField();
			}
			else
			{
				_resources.fields['chkCrystalisation'].disableField();
			}
		}
		
		, populateEvent: function()
		{
			var obj = _self.getSelectedEvent();
			if (obj)
			{		

				_resources.fields['dtpValudationDate'].setValue(obj.valnDate);
				
				_resources.fields['dtpValudationDate'].setReadOnly((obj.nodeID.indexOf("NEWEVENT") > -1) ? false : true);
				_resources.fields['chkCrystalisation'].setValue((obj.crysFlag == _self.YES) ? true : false);
				
				
				if (_defaultValues['perfFee'] == _self.YES)
				{
					_resources.fields['chkCrystalisation'].enableField();
				}
				else
				{
					_resources.fields['chkCrystalisation'].disableField();
				}
				
				_resources.fields['chkDistribution'].setValue((obj.distFlag == _self.YES) ? true : false);
			}
		}
		
		, populateDelEvent: function()
		{
			var obj = _self.getSelectedEvent();
			if (obj)
			{		
				_resources.fields['txtDelValuationDate'].setValue(obj.valnDate);				
				_resources.fields['txtDelCrystalisation'].setValue(obj.crysFlag);
				_resources.fields['txtDelDistribution'].setValue(obj.distFlag);
			}
		}
		
		
		, populateEventG1G2: function()
		{
			var obj = _self.getSelectedEventG1G2();
			if (obj){		
				_resources.fields['dtpRecordDate'].setValue(obj.eventDate);
				_resources.fields['dtpExDate'].setValue(obj.exDate);
				_resources.fields['dtpPayDate'].setValue(obj.payDate);
				_resources.fields['dtpReinvestDate'].setValue(obj.reinvDate);
				_resources.fields['distributionType'].setValue(obj.distribType);
				_resources.fields['distributionIndicator'].setValue(obj.distribIndicator);
			}
		}
		
		, populateDelEventG1G2: function()
		{
			var obj = _self.getSelectedEventG1G2();
			
			if (obj) {
				_resources.fields['txtDeLRecordDate'].setValue(obj.eventDate);
				_resources.fields['txtDeLExDate'].setValue(obj.exDate);
				_resources.fields['txtDeLPayDate'].setValue(obj.payDate);
				_resources.fields['txtDeLReinvestDate'].setValue(obj.reinvDate);
				_resources.fields['txtDeLDistributionType'].setValue(this.getOptionDescription('distribTypeListVal', obj.distribType));
				_resources.fields['txtDeLDistributionIndicator'].setValue(this.getOptionDescription('distribIndicatorListVal', obj.distribIndicator));
			}
		}
		
		, getSelectedEvent: function()
		{
			if (_resources.grids['grdEvent'].getSelectedRecord()) 
			{
				return getEvent(_mstrXML, _resources.grids['grdEvent'].getSelectedRecord().get("nodeID"));
			} 
			else 
			{
				return null;
			}
		}
		
		, getSelectedEventG1G2: function()
		{
			if (_resources.grids['grdEventG1G2'].getSelectedRecord()) {
				return getEventG1G2(_mstrXML, _resources.grids['grdEventG1G2'].getSelectedRecord().get("nodeID"));
			}
			else {
				return null;
			}
		}
		
		,getOptionDescription: function(listName, value)
		{
			return IFDS.Xml.getNodeValue(_listMap[listName], 'Element[code = "' + value + '"]/value');
		}
		
		, doValidate: function(action, data)
		{			
			var passValidate = false;
			var mObj;
			var oObj;
			var obj;
			var oObjG1G2;
			var iNodeId;
			
			
			if (isValuationEvent()) {
				iNodeId = "EXIST" + data['valnDate'];
			} else {
				iNodeId = "EXIST" + data['eventDate'];
			}
			var nDistFlag = false;
			var nCrysFlag = false;
			var sendAction = action;
			
			if (action != _self.ADD) 
			{
				if (isValuationEvent()) {
					obj = _self.getSelectedEvent();
				} else {
					obj = _self.getSelectedEventG1G2();
				}
			}

			if (obj && obj.nodeID.indexOf("NEWEVENT") > -1 && action == _self.DEL)
			{
				passValidate = true;
			}
			
			oObj = getEvent(_originalXML, iNodeId);
			
			if (oObj)
			{

				mObj = getEvent(_mstrXML, iNodeId);
				if ((action == _self.ADD) && (mObj.runMode == _self.DEL))
				{
					nCrysFlag = (data['crysFlag'] == true) ? _self.YES : _self.NO;
					nDistFlag = (data['distFlag'] == true) ? _self.YES : _self.NO;
					
					if ((oObj.crysFlag == nCrysFlag) && (oObj.distFlag == nDistFlag))
					{
						passValidate = true;
					}
					else
					{
						sendAction = _self.MOD;
					}
				}
			}
			
			oObjG1G2 = getEventG1G2(_originalXML, iNodeId);
			
			if (oObjG1G2)
			{
				mObj = getEventG1G2(_mstrXML, iNodeId);

				if ((action == _self.ADD) && (mObj.runMode == _self.DEL))
				{
						passValidate = true;
						sendAction = _self.MOD;
				}
			}
			
			if (passValidate)
			{
				_self.saveUpdateToMstrXML(action, data);
			}
			else 
			{
			   DesktopWeb.Ajax.doSmartviewAjax(_vldtView, null, getValidateEventRequest(obj, sendAction, data), responseHandler, _translationMap['Validate']);
			}
			
			function responseHandler(success, responseXML) 
			{
				if (success) 
				{
					_self.saveUpdateToMstrXML(action, data);
				}
				else 
				{
					var contextErrors = IFDS.Xml.getNodes(responseXML, '//Errors/Error');
					Ext.each(contextErrors, function(contextError){
						var errorCode = IFDS.Xml.getNodeValue(contextError, 'errorCode');
						var errorText = IFDS.Xml.getNodeValue(contextError, 'text');
					});
				}
			}
		}	
		
		, doUpdate: function ()
		{
			var updateStatus = null;	
						
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest(), responseHandler, _translationMap['Update']);			
			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
					_self.doSearch(false);
				}
				else 
				{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL; 	
				}
			}	

			return updateStatus;
		}
		
		, saveUpdateToMstrXML: function(action, data)
		{
			if (action == _self.ADD)
			{					
				addNewEventToMstrXML(data);
				
				if (isValuationEvent()) {
					_self.refreshGrdEvent(_resources.grids['grdEvent'].getStore().getCount());		
					_resources.popups['frmAddModEvent'].hide();
				} else {
					_self.refreshGrdEvent(_resources.grids['grdEventG1G2'].getStore().getCount());	
					_resources.popups['frmAddModEventG1G2'].hide();	
			    }
				_self.enableButtonsG1G2(_self.YES);	
				
			}
			else if (action == _self.MOD)
			{
				var index = 0;
				if(!isValuationEvent()) {
					index = updateEventToMstr(_self.getSelectedEventG1G2().nodeID, data);
				}else{
					index = updateEventToMstr(_self.getSelectedEvent().nodeID, data);
				}

				_self.refreshGrdEvent(index);
				_resources.popups['frmAddModEvent'].hide();
				_resources.popups['frmAddModEventG1G2'].hide();
			}
			else if (action == _self.DEL)
			{
				if(!isValuationEvent()) {
					deleteEventFromMstr(this.getSelectedEventG1G2().nodeID);
				} else {
					deleteEventFromMstr(this.getSelectedEvent().nodeID);
				}
				_self.refreshGrdEvent(0);	
				_resources.popups['frmDelEvent'].hide();
				_resources.popups['frmDelEventG1G2'].hide();
			}
			else 
			{
				alert ("ERROR: Undefined action");
			}
		}
		
		, freezeGrid: function(fundCode, classCode)
		{
			if (_defaultValues['fund'] && _defaultValues['class'])
			{
				var current = _defaultValues['fund'] + "/" + _defaultValues['class'];			
				if (fundCode != _defaultValues['fund'] || classCode != _defaultValues['class']) 
				{
					if (isValuationEvent()) {
						_resources.grids['grdEvent'].disable();
						_resources.grids['grdEvent'].hide();
						_defaultValues['grdEnable'] = false;
					} else
					{
						_resources.grids['grdEventG1G2'].disable();
						_resources.grids['grdEventG1G2'].hide();
						_defaultValues['grdEnableG1G2'] = false;
					}
				}
				else
				{
					if (isValuationEvent()) {
						_resources.grids['grdEvent'].enable();
						_defaultValues['grdEnable'] = true;
						_resources.grids['grdEventG1G2'].disable();
						_resources.grids['grdEventG1G2'].hide();
					} else
					{
						_resources.grids['grdEventG1G2'].enable();
						_defaultValues['grdEnableG1G2'] = true;
						_resources.grids['grdEvent'].disable();
						_resources.grids['grdEvent'].hide();
					}
				}
			}
		}
		
		, isFrontValid: function()
		{
			if (isValuationEvent()) {
				if (!_defaultValues['grdEnable']) {
					return false;
				} else {
					return true;
				}
			} else {
				if (!_defaultValues['grdEnableG1G2']){
						return false;
				} else {
						return true;
				}
			} 
		}
		
		, goToDetail: function()
		{
			var obj = _self.getSelectedEvent();
			if (obj)
			{
				gotoDetailscreen(_defaultValues['fund'], _defaultValues['class'], _defaultValues['fndClsDisp'], obj.valnDate, _defaultValues['startDate'], _defaultValues['endDate']);
			}
		}
		
		, parseSMVDateFormat: function(smvDateFormat)
		{
			var dateFormat = "";
			switch(smvDateFormat.toLowerCase())
			{
				case 'dmy':
				{
					dateFormat = 'DD/MM/YYYY';
					break;
				}
				case 'mdy':
				{
					dateFormat = 'MM/DD/YYYY'
					break;
				}
			}		
			return dateFormat;
		}
	}		
}	