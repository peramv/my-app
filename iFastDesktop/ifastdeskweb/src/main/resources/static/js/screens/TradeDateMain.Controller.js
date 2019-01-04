/*********************************************************************************************
 * @file	TradeDateMain.Controller.js
 * @author	Kittichai Sopitwetmontree
 * @desc	Controller JS file for Trade Date Maintenance screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _mstrXML = null;
	var _originalXML = null;
	var _initView = "dtTradeSchdMntInit";
	var _reloadView = "dtTradeSchdMntReload";
	var _vldtView = "dtTradeSchdMntProc";
	var _updateView = "dtTradeSchdMntProc";
	var _tradeSchdCounter = 0;
	var _defaultValues = {};
	var _nextStartRecNum = null;
	var _requestRecNum = 30; 
	var _transTypeXML = {};
	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	// PRIVATE METHODS ****************************************	
	function populateDropdowns(xml)
	{
		_resources.fields['cboSearchFor'].loadData(IFDS.Xml.getNode(xml, "//List[@listName='SearchTypes']"));
		_resources.fields['cboTransType'].loadData(IFDS.Xml.getNode(xml, "//List[@id='TransTypeList']"));		
	}	
	
	function storeDefaultValues(xml)
	{
		_defaultValues['SearchTypes'] = IFDS.Xml.getNodeValue(xml, "//ListSelection[@id='SearchTypes']");
		_defaultValues['startDate'] =  DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, "//DefaultDates/startDate"));		
		_defaultValues['endDate'] =  DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DefaultDates/endDate'));
		
	}
	function storeTransType(xml)
	{
		var listMstrXMLArr = IFDS.Xml.getNodes(xml, "//List");	
		var controlName;
		
		Ext.each(listMstrXMLArr, function(listMstrXML){
			controlName = listMstrXML.getAttribute('id');
			if(controlName != null)
			{
				if(controlName = "TransTypeList")
				{					
					_transTypeXML[controlName] = listMstrXML;				
				}
			}
		});	

	}
	function createMstrXML(xml, more)
	{	
		if (!_mstrXML || !more)
		{			
			_mstrXML = IFDS.Xml.newDocument("TradeSchds");
		}		
		
		var tradeSchdXMLArr = IFDS.Xml.getNodes(xml, '//TradeSchds/TradeSchd');
		var valnXML = null;
		var crysXML = null;
		
		Ext.each(tradeSchdXMLArr, function(tradeSchdXML){
			IFDS.Xml.addSingleNode(tradeSchdXML, 'runMode', _self.UNCH);
			IFDS.Xml.addSingleNode(tradeSchdXML, 'updSeq', _self.SEQUNCH);
			IFDS.Xml.appendNode(_mstrXML, tradeSchdXML);	
			
		});	
	}	
	function getTradeSchd(pRecIDTradeSchd)
	{
		var index = 0;		
		var tradeSchdXMLArr = IFDS.Xml.getNodes(_mstrXML, '//TradeSchds/TradeSchd');
		for (var i = 0; i < tradeSchdXMLArr.length; i++)
		{			
			if (IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'recIDTradeSchd') == pRecIDTradeSchd)
			{
				return {
					node : tradeSchdXMLArr[i], 
					index : index,
					recIDTradeSchd : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'recIDTradeSchd'),
					runMode : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'runMode'),
					valuationDate : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'valuationDate'),
					transType : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'transType'),
					tradeDate : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'tradeDate'),
					settlementDate : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'settlementDate'),
					cutOffDate : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'cutOffDate'),
					version : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'version'),
					modDate : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'modDate'),
					modUser : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'modUser'),
					userName : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'userName'),
					procDate : IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'procDate')
				};
			}
			if (IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'runMode') != _self.DEL)
			{
				index += 1;
			}
		}			
	}	
	
	function addNewTradeSchdToMstrXML(data)
	{
		if (!_mstrXML)
		{			
			_mstrXML = IFDS.Xml.newDocument("TradeSchds");
		}		
		_tradeSchdCounter += 1;
		
		var newTradeSchdXML = IFDS.Xml.newDocument("TradeSchd");	
		
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'runMode', _self.ADD);
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'updSeq', _self.SEQADD);
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'recIDTradeSchd', "NEWRECIDTRADESCHD" + _tradeSchdCounter);
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'valuationDate', data['valuationDate']);
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'transType', data['transType']);
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'tradeDate', data['tradeDate']);
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'settlementDate', data['settlementDate']);	
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'cutOffDate', data['cutOffDate']);
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'allowMod', 'yes');
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'allowDel', 'yes');
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'version');
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'userName');
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'procDate');
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'modUser');
		IFDS.Xml.addSingleNode(newTradeSchdXML, 'modDate');
				
		IFDS.Xml.appendNode(_mstrXML, newTradeSchdXML);		
		_self.updatesFlag = true;		

	}	
	function getValidateTradeSchdRequest (obj, action, data)
	{
		var requestXML = IFDS.Xml.newDocument("data");

		IFDS.Xml.addSingleNode(requestXML, "procMode", "validation");
		IFDS.Xml.addSingleNode(requestXML, 'fund', _resources.fields['cboFundClass'].selectedRecord.get('fundCode'));
		IFDS.Xml.addSingleNode(requestXML, 'class', _resources.fields['cboFundClass'].selectedRecord.get('classCode'));
		
		var tradeSchdsXML = IFDS.Xml.newDocument("TradeSchds");
		var tradeSchdXML = IFDS.Xml.newDocument("TradeSchd");

		IFDS.Xml.addSingleNode(tradeSchdXML, "runMode", action);
		IFDS.Xml.addSingleNode(tradeSchdXML, "updSeq");
		if (action != _self.ADD)
			IFDS.Xml.addSingleNode(tradeSchdXML, "recIDTradeSchd", obj.recIDTradeSchd);
		else
			IFDS.Xml.addSingleNode(tradeSchdXML, "recIDTradeSchd", 0);
			
		IFDS.Xml.addSingleNode(tradeSchdXML, "valuationDate", data['valuationDate']);
		IFDS.Xml.addSingleNode(tradeSchdXML, "transType", data['transType']);
		IFDS.Xml.addSingleNode(tradeSchdXML, "tradeDate", data['tradeDate']);
		IFDS.Xml.addSingleNode(tradeSchdXML, "settlementDate", data['settlementDate']);		
		IFDS.Xml.addSingleNode(tradeSchdXML, "cutOffDate", data['cutOffDate']);				
		IFDS.Xml.addSingleNode(tradeSchdXML, "version");
		
		IFDS.Xml.appendNode(tradeSchdsXML,tradeSchdXML);
		return IFDS.Xml.appendNode(requestXML, tradeSchdsXML);
	}	
	function getUpdateRequest()
	{		
		var requestXML = IFDS.Xml.newDocument("data");
		var xml = IFDS.Xml.newDocument("TradeSchds");
		var xmlScales;
		
		var tradeSchdXMLArr = IFDS.Xml.getNodes(_mstrXML, '//TradeSchds/TradeSchd');
		var updTradeSchdXML;
		var tradeSchdRunMode;
		var newTradeSchd;
		
		IFDS.Xml.addSingleNode(requestXML, "procMode", "process");		
		IFDS.Xml.addSingleNode(requestXML, 'fund', _resources.fields['cboFundClass'].selectedRecord.get('fundCode'));
		IFDS.Xml.addSingleNode(requestXML, 'class', _resources.fields['cboFundClass'].selectedRecord.get('classCode'));		
	
		var tradeSchdXMLArr = IFDS.Xml.getNodes(_mstrXML, '//TradeSchds/TradeSchd');
		

		
		for (var i = 0; i < tradeSchdXMLArr.length; i++)
		{				
			tradeSchdRunMode = IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'runMode');
			
			if (IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'recIDTradeSchd').indexOf("NEWRECIDTRADESCHD") > -1)
			{
				newTradeSchd = true;
			}
			else 
			{
				newTradeSchd = false;
			}
					
			/* DISCARD 1) Unchanged  2) Deleted of created  */
			
			if  (!(newTradeSchd && tradeSchdRunMode == _self.DEL) && 
				!(tradeSchdRunMode == _self.UNCH))
			{
				
				updTradeSchdXML = IFDS.Xml.newDocument("TradeSchd");				
				IFDS.Xml.addAttribute(IFDS.Xml.getNode(updTradeSchdXML, "."), 'RecordSource', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'recIDTradeSchd'));
				
				if (newTradeSchd)
				{
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'runMode', _self.ADD);
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'updSeq', _self.SEQADD);		
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'recIDTradeSchd', 0);		// send 0 to SMV, just dummy.				
				}
				else
				{
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'runMode', tradeSchdRunMode);
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'updSeq', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'updSeq'));		
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'recIDTradeSchd', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'recIDTradeSchd'));						
				}				
				
				IFDS.Xml.addSingleNode(updTradeSchdXML, 'valuationDate', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'valuationDate'));
				IFDS.Xml.addSingleNode(updTradeSchdXML, 'transType', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'transType'));
				IFDS.Xml.addSingleNode(updTradeSchdXML, 'tradeDate', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'tradeDate'));
				IFDS.Xml.addSingleNode(updTradeSchdXML, 'settlementDate', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'settlementDate'));
				IFDS.Xml.addSingleNode(updTradeSchdXML, 'cutOffDate', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'cutOffDate'));

				
				if (newTradeSchd)
				{
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'version');				
				}
				else
				{
					IFDS.Xml.addSingleNode(updTradeSchdXML, 'version', IFDS.Xml.getNodeValue(tradeSchdXMLArr[i], 'version'));
				}
				
			
				IFDS.Xml.appendNode(xml, updTradeSchdXML);
			}
		}
			
		return IFDS.Xml.appendNode(requestXML, xml);
	}
	
	function storeContextErrors(errorNodes)
	{
		clearErrMsg();
		var focusIdx = 0;
		
		for (var i = 0; i < errorNodes.length; i++)
		{		
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
							
			var recIDTradeSchd = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');			
				
			var tradeSchd = getTradeSchd(recIDTradeSchd);	
			if (!IFDS.Xml.getNode(tradeSchd.node, 'errMsg'))		
			{				
				IFDS.Xml.addSingleNode(tradeSchd.node, 'errMsg', errMsg);		
			}
			if (tradeSchd.runMode == _self.DEL)
			{
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'runMode'), _self.UNCH);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'updSeq'), _self.SEQUNCH);
			}
			if (focusIdx == 0)
			{
				focusIdx = tradeSchd.index;
			}		
		}
				
		_self.refreshGrdTradeSchd(focusIdx);		
	}
	function clearErrMsg()
	{
		
		var tradeSchdXMLArr = IFDS.Xml.getNodes(_mstrXML, '//TradeSchds/TradeSchd');
		for (var i = 0; i < tradeSchdXMLArr.length; i++)
		{
			if (IFDS.Xml.getNode(tradeSchdXMLArr[i], 'errMsg'))		
			{				
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(tradeSchdXMLArr[i], 'errMsg'));
			}

		}
	}	
	function updateTradeSchdToMstr(pRecIDTradeSchd, data)
	{
		var tradeSchd = getTradeSchd(pRecIDTradeSchd);
		if(pRecIDTradeSchd.indexOf("NEWRECIDTRADESCHD") > -1)
		{
			// Modify the add record, the mode should still be add.
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'runMode'), _self.ADD);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'updSeq'), _self.SEQADD);
		}
		else
		{
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'runMode'), _self.MOD);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'updSeq'), _self.SEQMOD);
		}		

		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'valuationDate'), data['valuationDate']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'transType'), data['transType']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'tradeDate'), data['tradeDate']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'settlementDate'), data['settlementDate']);	
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'cutOffDate'), data['cutOffDate']);
		
		_self.updatesFlag = true;	
		
		return tradeSchd.index;	
	}
	function deleteTradeSchdFromMstr(pRecIDTradeSchd)
	{		
		var tradeSchd = getTradeSchd(pRecIDTradeSchd);
		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'runMode'), _self.DEL);				
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(tradeSchd.node, 'updSeq'), _self.SEQDEL);	
		
		_self.updatesFlag = true;	
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
		, updatesFlag: false	
		, init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var requestXML = IFDS.Xml.newDocument("data");
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['DoLoading']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{	
				
					populateDropdowns(responseXML);
					storeTransType(responseXML);
					storeDefaultValues(responseXML);
					_self.initDefaultValues();
					
					// disable all action buttons.
					_self.updateTradeSchedButtons();
					_self.enableMoreButton(_nextStartRecNum);

				}
			}
		}
		, initDefaultValues: function()
		{
			_resources.fields['cboSearchFor'].setValue(_defaultValues['SearchTypes']);		
			_resources.fields['dtpStartDate'].setValue(_defaultValues['startDate']);	
			_resources.fields['dtpEndDate'].setValue(_defaultValues['endDate']);		
			
		}
		, openActionPopup: function(popupName, action)
		{
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();
		}
		, setDefaultNewTradeSchd: function()
		{
			// default values				
			_resources.fields['dtpValuationDate'].setValue(_defaultValues['valuationDate']);
			_resources.fields['cboTransType'].setValue("");				
			_resources.fields['dtpTradeDate'].setValue("");
			_resources.fields['dtpSettlementDate'].setValue("");
			_resources.fields['dtpCutOffDate'].setValue("");
		}
		, doSearch: function(more)
		{
			if (_self.readyToSearch())
			{
				
				_defaultValues['fund'] = _resources.fields['cboFundClass'].selectedRecord.get('fundCode');
				_defaultValues['class'] = _resources.fields['cboFundClass'].selectedRecord.get('classCode');
				
				var requestXML = IFDS.Xml.newDocument("data");		
				IFDS.Xml.addSingleNode(requestXML, "fund", _defaultValues['fund']);	
				IFDS.Xml.addSingleNode(requestXML, "class", _defaultValues['class']);
				IFDS.Xml.addSingleNode(requestXML, "searchType", _resources.fields['cboSearchFor'].getValue());
				IFDS.Xml.addSingleNode(requestXML, "startDate", _resources.fields['dtpStartDate'].getSMVDateString());
				IFDS.Xml.addSingleNode(requestXML, "endDate", _resources.fields['dtpEndDate'].getSMVDateString());
				IFDS.Xml.addSingleNode(requestXML, "startRecNum", (more ? _nextStartRecNum : 1));
				IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);
				
				if (requestXML)
				{
					DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['DoSearching']);

					function responseHandler(success, responseXML)
					{
						if (success)
						{						
							_resources.grids['grdTradeSchd'].enable();	
							createMstrXML(responseXML, more);			
							_originalXML = IFDS.Xml.cloneDocument(_mstrXML);
							_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
							_self.refreshGrdTradeSchd(0);	
							_self.enableMoreButton(_nextStartRecNum);							
							
							// default valuation date
							_defaultValues['valuationDate'] = DesktopWeb.Util.getDateDisplayValue(
									IFDS.Xml.getNodeValue(responseXML, '//Defaults/valuationDtDef'));
						}else{
							_resources.grids['grdTradeSchd'].clearData();
						}
					}
				}
			
			}
		}
		, readyToSearch: function()
		{
			var retVal = true;
			
			if ( _resources.fields['cboFundClass'].getValue() != "" &&
				 _resources.fields['cboSearchFor'].getValue() != "" &&
				 _resources.fields['dtpStartDate'].getValue() != "" &&
				 _resources.fields['dtpEndDate'].getValue() != "" )
			{
				retVal = true;
			}
			else
			{
				if (_resources.fields['cboFundClass'].getValue() == "" ) { _resources.fields['cboFundClass'].markInvalid(_translationMap['ErrFieldRequired']); } 
				if (_resources.fields['cboSearchFor'].getValue() == "" ) { _resources.fields['cboSearchFor'].markInvalid(_translationMap['ErrFieldRequired']); } 
				if (_resources.fields['dtpStartDate'].getValue() == "" ) { _resources.fields['dtpStartDate'].markInvalid(_translationMap['ErrFieldRequired']); } 
				if (_resources.fields['dtpEndDate'].getValue() == "" ) { _resources.fields['dtpEndDate'].markInvalid(_translationMap['ErrFieldRequired']); } 
				retVal = false;
			}
			
			return retVal;
		}
		, doValidate: function(action, data)
		{			
			var obj = null;
			var passValidate = false;
			var mObj;
			var oObj;
			var nDistFlag = false;
			var nCrysFlag = false;
			var sendAction = action;
			
			
			
			obj = _self.getSelectedTradeSchd();
						
			if (obj && obj.recIDTradeSchd.indexOf("NEWRECIDTRADESCHD") > -1 && (action == _self.DEL || action == _self.MOD))
			{
				// in case of modify or delete the new record.
				
				DesktopWeb.Ajax.doSmartviewAjax(_vldtView, null, getValidateTradeSchdRequest(obj, _self.ADD, data), responseHandler, _translationMap['DoValidation']);
			}
			else 
			{
				DesktopWeb.Ajax.doSmartviewAjax(_vldtView, null, getValidateTradeSchdRequest(obj, action, data), responseHandler, _translationMap['DoValidation']);
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

		
		}		/* end doValidate function */
		, refreshGrdTradeSchd: function(index)
		{	
			_resources.grids['grdTradeSchd'].loadData(_mstrXML);
			_resources.grids['grdTradeSchd'].setSelectedRecord(index);			
		}
		, clearSelectedTradeSchd: function()
		{
			_resources.grids['grdTradeSchd'].clearData();		
		}
		, saveUpdateToMstrXML: function(action, data)
		{			
			
			if (action == _self.ADD)
			{			
				addNewTradeSchdToMstrXML(data);
				_self.refreshGrdTradeSchd(_resources.grids['grdTradeSchd'].getStore().getCount());										
				_resources.popups['frmAddModTradeSchd'].hide();
			}
			else if (action == _self.MOD)
			{
			
				var index = updateTradeSchdToMstr(this.getSelectedTradeSchd().recIDTradeSchd, data);
				_self.refreshGrdTradeSchd(index);						
				_resources.popups['frmAddModTradeSchd'].hide();
			}
			else if (action == _self.DEL)
			{	
			
				deleteTradeSchdFromMstr(this.getSelectedTradeSchd().recIDTradeSchd);
				_self.refreshGrdTradeSchd(0);				
				_resources.popups['frmAddModTradeSchd'].hide();
			}

		}
		, translateTransType: function(pCode)
		{	
			var retVal = "";

			var elmXMLArr = IFDS.Xml.getNodes(_transTypeXML["TransTypeList"], "Element");		
			Ext.each(elmXMLArr, function(elmXML){				
				if (pCode == IFDS.Xml.getNodeValue(elmXML, "code"))
				{					
					retVal = IFDS.Xml.getNodeValue(elmXML, "value");
				}
			});	
			return retVal==""?pCode:retVal;		
		}
		, doUpdate: function ()
		{
			/* Backup */
			var backupXML = IFDS.Xml.cloneDocument(_mstrXML);
			var updateStatus = null;	
					
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest(), responseHandler, _translationMap['DoUpdate']);			

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
		, populateTradeSchd: function()
		{			
			var obj = this.getSelectedTradeSchd();
			
			if (obj)
			{								
			
				_resources.fields['dtpValuationDate'].setValue(DesktopWeb.Util.getDateDisplayValue(obj.valuationDate));			
				_resources.fields['cboTransType'].setValue(obj.transType);	
				_resources.fields['dtpTradeDate'].setValue(DesktopWeb.Util.getDateDisplayValue(obj.tradeDate));					
				_resources.fields['dtpSettlementDate'].setValue(DesktopWeb.Util.getDateDisplayValue(obj.settlementDate));					
				_resources.fields['dtpCutOffDate'].setValue(DesktopWeb.Util.getDateDisplayValue(obj.cutOffDate));					
			}
		}
		, getSelectedTradeSchd: function()
		{
			if (_resources.grids['grdTradeSchd'].getSelectedRecord()) 
			{
				return getTradeSchd(_resources.grids['grdTradeSchd'].getSelectedRecord().get("recIDTradeSchd"));
			} 
			else 
			{
				return null;
			}
		}	
		, updateTradeSchedButtons: function(record)
		{
			if (record)
			{
				_resources.grids['grdTradeSchd'].enableButton('cmdAddTradeSchd');
				if (record.get('allowMod') == 'yes')
				{
					_resources.grids['grdTradeSchd'].enableButton('cmdModTradeSchd');
				}else{
					_resources.grids['grdTradeSchd'].disableButton('cmdModTradeSchd');
				}
				if (record.get('allowDel') == 'yes')
				{
					_resources.grids['grdTradeSchd'].enableButton('cmdDelTradeSchd');
				}else{
					_resources.grids['grdTradeSchd'].disableButton('cmdDelTradeSchd');
				}
			}else{
				_resources.grids['grdTradeSchd'].disableButton('cmdAddTradeSchd');
				_resources.grids['grdTradeSchd'].disableButton('cmdModTradeSchd');
				_resources.grids['grdTradeSchd'].disableButton('cmdDelTradeSchd');
			}
		}
		
		, enableMoreButton: function (moreRec)
		{
			if (moreRec)
			{
				Ext.getCmp('cmdMoreTradeSchd').enable();
			}
			else
			{
				Ext.getCmp('cmdMoreTradeSchd').disable();
			}	
		}
	
	}	
}	