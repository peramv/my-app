/*********************************************************************************************
 * @file	GovtAmendment.Controller.js
 * @author	Rod Walker
 * @desc	Controller JS file for Government Filing and Amendment screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  01 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54333
 *					- Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();	
	var _initView = 'dtGovtAmendmentInit';
	var _mstrVldtnView = 'dtGovtAmendMstrVldtn';
	var _detlVldtnView = 'dtGovtAmendDtlVldtn';
	var _updateView = 'dtGovtAmendmentUpd';
	var _mstrsXML = null;
	var _permissionsMap = {};
	var _defaultValues = {};	
	var _selectedMstrIndex = null;
	var _selectedDetlIndex = null;	
	var _accountTaxType = null;
	var _accountOwnerName = null;
	var _accountOwnerNameParam = DesktopWeb._SCREEN_PARAM_MAP['AccountOwnerName'];
	
	// PRIVATE METHODS ****************************************
	function storePermissions(initViewXML)
	{
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/modPerm').toLowerCase() == 'yes';
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function storeDefaultValues(initViewXML)
	{		
		var strRequestTypeList = null,
			strStopReasonList = null,
			accountTaxType;

		accountTaxType = IFDS.Xml.getNodeValue(initViewXML, '//taxType'); 

		_defaultValues['benefID'] = IFDS.Xml.getNodeValue(initViewXML, "//List[@listName='BeneficiaryList']/Element/code");				
		_defaultValues['taxType'] = IFDS.Xml.getNodeValue(initViewXML, "//taxType");
		_defaultValues['acctName'] = IFDS.Xml.getNodeValue(initViewXML, "//acctName");

		_defaultValues['reqStat'] = IFDS.Xml.getNodeValue(initViewXML, "//ListSelection[@id='RequestStatList']");
		_defaultValues['filingType'] = IFDS.Xml.getNodeValue(initViewXML, "//ListSelection[@id='FilingTypeList']");			

		if( accountTaxType.toLowerCase() == '9' || accountTaxType.toLowerCase() == 'm' )
		{
			_defaultValues['reasonCode'] = IFDS.Xml.getNodeValue(initViewXML, "//ListSelection[@id='StopReasonListQESI']");
			_defaultValues['reqType'] = IFDS.Xml.getNodeValue(initViewXML, "//ListSelection[@id='RequestTypeListQESI']");	
		}
		else
		{
			_defaultValues['reasonCode'] = IFDS.Xml.getNodeValue(initViewXML, "//ListSelection[@id='StopReasonListTFSA']");
			_defaultValues['reqType'] = IFDS.Xml.getNodeValue(initViewXML, "//ListSelection[@id='RequestTypeListTFSA']");	
		}

		_defaultValues['fromDeff']  = (new Date()).format(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()));
		_defaultValues['fromDeff_06_07']  = (new Date(2007, 1, 21)).format(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()))
			
	}
	
	function populateDropdowns(initViewXML)
	{
		//mstr
		var strFilingTypeList,
			strBeneficiaryList,
			strRequestStatList,
			strRequestTypeList,
			strStopReasonList;
		
		var accountTaxType = IFDS.Xml.getNodeValue(initViewXML, '//taxType');

		if( accountTaxType.toLowerCase() == 'v' )
		{
			strRequestTypeList = "//List[@listName='RequestTypeListTFSA']";
			strStopReasonList = "//List[@listName='StopReasonListTFSA']";
		}
		else
		{
			strRequestTypeList = "//List[@listName='RequestTypeListQESI']";
			strStopReasonList = "//List[@listName='StopReasonListQESI']";
		}
		
		strFilingTypeList = "//List[@listName='FilingTypeList']";
		strBeneficiaryList = "//List[@listName='BeneficiaryList']";
		strRequestStatList = "//List[@listName='RequestStatList']";
		
		_resources.popups['mstr'].getField('benefID').hideField();
		_resources.popups['mstr'].getField('acctName').hideField();
		_resources.popups['mstr'].getField('filingType').getStore().loadData(IFDS.Xml.getNode(initViewXML, strFilingTypeList));
		_resources.popups['mstr'].getField('benefID').getStore().loadData(IFDS.Xml.getNode(initViewXML, strBeneficiaryList));
		_resources.popups['mstr'].getField('reqStat').getStore().loadData(IFDS.Xml.getNode(initViewXML, strRequestStatList));
		_resources.popups['mstr'].getField('reqType').getStore().loadData(IFDS.Xml.getNode(initViewXML, strRequestTypeList));
		_resources.popups['detl'].getField('reasonCode').getStore().loadData(IFDS.Xml.getNode(initViewXML, strStopReasonList));
	}
	
	function setMstrsXML(initViewXML)
	{
		_mstrsXML = IFDS.Xml.getNode(initViewXML, '//Mstrs');		
		_accountTaxType = IFDS.Xml.getNodeValue(initViewXML, '//taxType'); 
		_accountOwnerName = IFDS.Xml.getNodeValue(initViewXML, '//acctName');
		
		if( _accountOwnerName == '' )
		{
			_accountOwnerName = _accountOwnerNameParam;
		}

		_resources.grids['mstrs'].loadData(_mstrsXML, (_permissionsMap['add'] ? ['addBtn'] : null));
		_resources.grids['mstrs'].selectFirstRecord();
		
		if( _accountTaxType.toLowerCase() == '9' || _accountTaxType.toLowerCase() == 'm' )
		{
			_resources.grids['mstrs'].hideColumn (2);
			_resources.grids['mstrs'].showColumn (1);
			_resources.grids['fileProcs'].hideColumn (5);
		}
		else
		{
			_resources.grids['mstrs'].showColumn (2);
			_resources.grids['mstrs'].hideColumn (1);
			_resources.grids['fileProcs'].showColumn (5);
		}
		
	}
	
	function updateMstr(action, data)
	{		
		var mstrXML = null;
		var acctName = null;
		switch(action)
		{
			case _self.ADD:
			{
				mstrXML = IFDS.Xml.addSingleNode(_mstrsXML, 'Mstr');
				IFDS.Xml.addSingleNode(mstrXML, 'mstrRunMode', _self.ADD);
				IFDS.Xml.addSingleNode(mstrXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);				
				for (var i in data)
				{
					IFDS.Xml.addSingleNode(mstrXML, i, data[i]);
				}
				IFDS.Xml.addSingleNode(mstrXML, 'Detls');										
				break;	
			}
			case _self.MOD:
			{				
				mstrXML = _self.getSelectedMstr();
				if (IFDS.Xml.getNode(mstrXML, 'mstrRunMode') == null)
				{
					IFDS.Xml.addSingleNode(mstrXML, 'mstrRunMode', _self.MOD);
				}
				else if (IFDS.Xml.getNodeValue(mstrXML, 'mstrRunMode') == _self.UNCH)
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'mstrRunMode'), _self.MOD);
				}				
				
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'reqType'), data['reqType']);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'reqTypeDesc'), data['reqTypeDesc']);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'filingType'), data['filingType']);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'filingTypeDesc'), data['filingTypeDesc']);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'reqStat'), data['reqStat']);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'reqStatDesc'), data['reqStatDesc']);				
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'deff'), data['deff']);
				IFDS.Xml.replaceSingleNode(mstrXML, 'dtlRecExist', (IFDS.Xml.getNode(mstrXML, 'Detls/Detl') != null ? 'yes' : 'no'))
				
				clearMstrError(mstrXML);
				break;	
			}
			case _self.DEL:
			{
				mstrXML = _self.getSelectedMstr();
				IFDS.Xml.addSingleNode(mstrXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
				if (IFDS.Xml.getNode(mstrXML, 'mstrRunMode') == null)
				{
					IFDS.Xml.addSingleNode(mstrXML, 'mstrRunMode', _self.DEL);
				}
				else if (IFDS.Xml.getNodeValue(mstrXML, 'mstrRunMode') == _self.ADD)
				{
					if(mstrXML != null )
					{
					   mstrXML.parentNode.removeChild(mstrXML);
					   mstrXML = null;
				   }
				}
				else
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(mstrXML, 'mstrRunMode'), _self.DEL);
				}
				
				// have to handle nasty case where user has updated Detl record, and then decides to delete Mstr
				if (mstrXML != null)
				{
					var detlXMLArray = IFDS.Xml.getNodes(mstrXML, 'Detl');

					if(detlXMLArray != null && detlXMLArray.length > 0)
					{
						for (var i = 0; i < detlXMLArray.length; i++)
						{
							var detlXML = detlXMLArray[i];
							if (IFDS.Xml.getNode(detlXML, 'dtlRunMode') != null)
							{
								detlXML.removeChild(IFDS.Xml.getNode(detlXML, 'dtlRunMode'));
							}
						}
					}
				}
									
				break;
			}					
		}						
		return mstrXML;		
	}
	
	function updateDetl(action, data)
	{	
		var mstrXML = _self.getSelectedMstr();
		if (IFDS.Xml.getNode(mstrXML, 'mstrRunMode') == null)
		{
			IFDS.Xml.addSingleNode(mstrXML, 'mstrRunMode', _self.UNCH);
		}
			
		var detlXML = null;
		switch(action)
		{
			case _self.ADD:
			{
				detlXML = IFDS.Xml.addSingleNode(IFDS.Xml.getNode(_self.getSelectedMstr(), "Detls"), 'Detl');
				IFDS.Xml.addSingleNode(detlXML, 'dtlRunMode', _self.ADD);
				IFDS.Xml.addSingleNode(detlXML, 'mstrUUID', IFDS.Xml.getNodeValue(mstrXML, "mstrUUID"));				
				for (var i in data)
				{					
					IFDS.Xml.addSingleNode(detlXML, i, data[i]);
				}										
				break;	
			}
			case _self.MOD:
			{
				detlXML = _self.getSelectedDetl();
				if (IFDS.Xml.getNode(detlXML, 'dtlRunMode') == null)
				{
					IFDS.Xml.addSingleNode(detlXML, 'dtlRunMode', _self.MOD);
				}
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(detlXML, 'fromDeff'), data['fromDeff']);
				
				clearMstrError(mstrXML);
				clearDetlError(detlXML);									
				break;	
			}
			case _self.DEL:
			{
				detlXML = _self.getSelectedDetl();				
				if (IFDS.Xml.getNode(detlXML, 'dtlRunMode') == null)
				{										
					IFDS.Xml.addSingleNode(detlXML, 'dtlRunMode', _self.DEL);
				}
				else if (IFDS.Xml.getNodeValue(detlXML, 'dtlRunMode') == _self.ADD)
				{				
					if(detlXML != null)
					{
						detlXML.parentNode.removeChild(detlXML);
					}
				}
				else
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(detlXML, 'dtlRunMode'), _self.DEL);
				}
				
				clearMstrError(mstrXML);
				break;
			}
		}
		return detlXML;
	}
	
	function sendValidation(view, validationXML, successHandler, errorHandler)
	{		
		DesktopWeb.Ajax.doSmartviewAjax(view, null, validationXML, responseHandler);
		
		function responseHandler(success, responseXML)
		{			
			if (success)
			{
				successHandler();
			}
			else
			{
				errorHandler();
			}
		}
	}
	
	function isNewMstrRecord(mstrXML)
	{				
		return (IFDS.Xml.getNode(mstrXML, 'mstrUUID') == null);		
	}
	
	function isNewDetlRecord(detlXML)
	{
		return (IFDS.Xml.getNode(detlXML, 'dtlUUID') == null);
	}
	
	function buildUpdateXML()
	{
		var xmlDoc = IFDS.Xml.cloneDocument(_mstrsXML);		
		var mstrXMLArray = IFDS.Xml.getNodes(xmlDoc, "Mstr");		
		for (var i = 0; i< mstrXMLArray.length; i++)
		{
			var fileProcsXML = IFDS.Xml.getNode(mstrXMLArray[i], 'FileProcs');
			if (fileProcsXML)
			{
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(mstrXMLArray[i], 'FileProcs'));
			}
										 							
			if(IFDS.Xml.getNode(mstrXMLArray[i], 'mstrRunMode') == null 
				|| IFDS.Xml.getNodeValue(mstrXMLArray[i], 'mstrRunMode') == "" )
			{					
				IFDS.Xml.deleteNode(mstrXMLArray[i]);				
			}
			else
			{
				IFDS.Xml.addAttribute(mstrXMLArray[i], 'RecordSource', (i + 1));
				
				var detlsXML = IFDS.Xml.getNode(mstrXMLArray[i], 'Detls');					
				var detlXMLArray = IFDS.Xml.getNodes(detlsXML, 'Detl');				
				for (var j = 0; j < detlXMLArray.length; j++)
				{
					if (IFDS.Xml.getNode(detlXMLArray[j], 'dtlRunMode') == null
						|| IFDS.Xml.getNodeValue(detlXMLArray[j], 'dtlRunMode') == '')
					{
						IFDS.Xml.deleteNode(detlXMLArray[j]);						
					}
					else
					{
						IFDS.Xml.addAttribute(detlXMLArray[j], 'RecordSource', '' + (i + 1) + ':' + (j + 1));
					}
				}				
			}
		}						
		return IFDS.Xml.stringToXML(IFDS.Xml.createNodeString("data", IFDS.Xml.serialize(xmlDoc)));
	}
	
	function clearDetlError(xmlNode)
	{
		if (IFDS.Xml.getNode(xmlNode, 'detlErrorMsg'))
		{
			IFDS.Xml.deleteNode(IFDS.Xml.getNode(xmlNode, 'detlErrorMsg'));
		}
	}
	
	function clearMstrError(xmlNode)
	{
		if (IFDS.Xml.getNode(xmlNode, 'mstrErrorMsg'))
		{
			IFDS.Xml.deleteNode(IFDS.Xml.getNode(xmlNode, 'mstrErrorMsg'));
		}
	}
	
	function storeContextErrors(errorNodes)
	{		
		for (var i = 0; i < errorNodes.length; i++)
		{
			if (IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName').toLowerCase() == 'mstr')
			{
				var mstrXMLIndex = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var mstrXML = IFDS.Xml.getNode(_mstrsXML, 'Mstr[' + mstrXMLIndex + ']')				
				IFDS.Xml.addSingleNode(mstrXML, 'mstrErrorMsg',  IFDS.Xml.getNodeValue(errorNodes[i], 'text'));												
			}
			else								
			{
				var sources = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource').split(':');
				var mstrXMLIndex = sources[0];				
				var detlXMLIndex = sources[1];
				var mstrXML = IFDS.Xml.getNode(_mstrsXML, 'Mstr[' + mstrXMLIndex + ']');
				if (IFDS.Xml.getNode(mstrXML, 'mstrErrorMsg') == null)
				{
					IFDS.Xml.addSingleNode(mstrXML, 'mstrErrorMsg', 'Errors present in Amendment Detail');
				}
				var detlXML = IFDS.Xml.getNode(mstrXML, 'Detls/Detl[' + detlXMLIndex + ']');
				IFDS.Xml.addSingleNode(detlXML, 'detlErrorMsg',  IFDS.Xml.getNodeValue(errorNodes[i], 'text'));
			}
		}
		_resources.grids['mstrs'].loadData(_mstrsXML, ['addBtn']);
		_resources.grids['mstrs'].setSelectedRecord(_selectedMstrIndex);
	}
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		,UNCH: 'unch'
		
		,updatesFlag: false
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			_resources.grids['mstrs'].disableAllButtons();															
			_resources.grids['detls'].disableAllButtons();
			
			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, "accountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
								
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler,  _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{							
				if (success)
				{					
					storePermissions(responseXML);
					storeDefaultValues(responseXML);
					populateDropdowns(responseXML);
					setMstrsXML(responseXML);
				}
			}
		}
		,getDefaultValues: function()
		{
			return _defaultValues;
		}
		,setSelectedMstr: function(xmlIndex)
		{			
			if (_selectedMstrIndex != null)
			{
				this.clearSelectedMstr();
			}
		
			_selectedMstrIndex = xmlIndex;
			
			var selectedMstrXML = this.getSelectedMstr();
			
			var detlBtnsToEnable = null;						
			if (_permissionsMap['add'] 				
				&& IFDS.Xml.getNodeValue(selectedMstrXML, "reqStat") != "03"
				&& IFDS.Xml.getNodeValue(selectedMstrXML, "reqStat") != "04")	  //not allowed for processed and delete			
			{
				detlBtnsToEnable = ['addBtn'];
			}

			_resources.grids['detls'].loadData(selectedMstrXML, detlBtnsToEnable);
			_resources.grids['detls'].selectFirstRecord();
			_resources.grids['fileProcs'].loadData(selectedMstrXML, null);
			
			if (_permissionsMap['mod']
				&& IFDS.Xml.getNodeValue(selectedMstrXML, "reqStat") != "04" 
				&& IFDS.Xml.getNodeValue(selectedMstrXML, "reqStat") != "05") // not allowed for deleted and ready for extract
			{
				_resources.grids['mstrs'].enableButton('modBtn');
			}
			
			if (isNewMstrRecord(selectedMstrXML))
			{
				_resources.grids['mstrs'].enableButton('delBtn');	
			}
			else
			{
				_resources.grids['mstrs'].disableButton('delBtn');
			}
			
			if (isNewMstrRecord(selectedMstrXML))
			{
				_resources.grids['mstrs'].disableButton('adminBtn');
				_resources.grids['mstrs'].disableButton('historicalBtn');
			}
			else
			{
				_resources.grids['mstrs'].enableButton('adminBtn');
				_resources.grids['mstrs'].enableButton('historicalBtn');
			}
		}
		
		,getSelectedMstr: function()
		{
			return IFDS.Xml.getNode(_mstrsXML, "Mstr[" + _selectedMstrIndex + "]");
		}
		
		,clearSelectedMstr: function()
		{
			_selectedMstrIndex = null;
			
			_resources.grids['detls'].clearData();
			_resources.grids['fileProcs'].clearData();			
			
			_resources.grids['mstrs'].disableButton('modBtn');
			_resources.grids['mstrs'].disableButton('delBtn');
			_resources.grids['mstrs'].disableButton('adminBtn');
			_resources.grids['mstrs'].disableButton('historicalBtn');
		}
		
		,setSelectedDetl: function(xmlIndex)
		{						
			if (_selectedDetlIndex != null)
			{
				this.clearSelectedDetl();
			}
		
			_selectedDetlIndex = xmlIndex;
			
			var mstrXML = this.getSelectedMstr();
			var detlXML = this.getSelectedDetl();
									
			if (IFDS.Xml.getNodeValue(mstrXML, 'reqStat') != '03'
				&& IFDS.Xml.getNodeValue(mstrXML, 'reqStat') != '04'
				&& IFDS.Xml.getNodeValue(mstrXML, 'reqStat') != '05' )		//request status != 'deleted' or processed
																			// or ready to extract
			{
				if (_permissionsMap['add'])
				{
					_resources.grids['detls'].enableButton('addBtn');
				}
				if (_permissionsMap['mod'])
				{
					_resources.grids['detls'].enableButton('modBtn');
				}
				if (_permissionsMap['del'])
				{
					_resources.grids['detls'].enableButton('delBtn');
				}					
			}
			else
			{
				_resources.grids['detls'].disableButton('addBtn');
				_resources.grids['detls'].disableButton('modBtn');
				_resources.grids['detls'].disableButton('delBtn');
			}
			
			if (isNewDetlRecord(detlXML))
			{				
				_resources.grids['detls'].disableButton('adminBtn');
				_resources.grids['detls'].disableButton('historicalBtn');
			}		
			else
			{
				_resources.grids['detls'].enableButton('adminBtn');
				_resources.grids['detls'].enableButton('historicalBtn');
			}
		}
		
		,getSelectedDetl: function()
		{
			var mstr = this.getSelectedMstr();			
			return IFDS.Xml.getNode(mstr, "Detls/Detl[" + _selectedDetlIndex + "]");
		}
		
		,clearSelectedDetl: function()
		{			
			_selectedDetlIndex = null;			
			
			_resources.grids['detls'].disableButton('modBtn');
			_resources.grids['detls'].disableButton('delBtn');
			_resources.grids['detls'].disableButton('adminBtn');
			_resources.grids['detls'].disableButton('historicalBtn');
		}
		
		,openActionPopup: function(popupName, action)
		{			
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();			
		}
		
		,openAdminPopup: function(recType)
		{					
			var title = null;	
			var xml = null;
			if (recType == 'mstr')
			{
				title = _translationMap['AmendmentRequestAdmin']
				xml = this.getSelectedMstr();
			}
			else
			{
				title = _translationMap['AmendmentDetailAdmin']
				xml = this.getSelectedDetl();
			}
			var adminData = {};
			adminData['userName'] = IFDS.Xml.getNodeValue(xml, 'userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'procDate'));
			adminData['modUser'] = IFDS.Xml.getNodeValue(xml, 'modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, 'modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}
		
		,openHistoricalPopup: function(recType)
		{
			var viewParam = {}
			if (recType == 'mstr')
			{
				viewParam['auditType'] = 'GovFileMstr';
				viewParam['searchValue1'] = IFDS.Xml.getNodeValue(this.getSelectedMstr(), "mstrUUID");				
			}
			else
			{
				viewParam['auditType'] = 'GovFileDetl';
				viewParam['searchValue1'] = IFDS.Xml.getNodeValue(this.getSelectedDetl(), "dtlUUID");				
			}
			_resources.popups['history'].init("Amendment Request - History", 'dtHistoricalInfo', viewParam, true);
			_resources.popups['history'].show();
		}
		
		,saveUpdate: function(popupName, action, data)
		{	
			_self.updatesFlag = true;		
			var backupXML = IFDS.Xml.cloneDocument(_mstrsXML);			
			var validationXML = null;
			var view = null;
			if (popupName == 'mstr')
			{
				view = _mstrVldtnView;
				var updateMstrByAction = updateMstr(action, data);
				if(updateMstrByAction != null )
				{
					validationXML = IFDS.Xml.stringToXML(IFDS.Xml.createNodeString("data", IFDS.Xml.serialize(updateMstrByAction)));
				}
			}
			else
			{														
				view = _detlVldtnView
				validationXML = IFDS.Xml.stringToXML(IFDS.Xml.createNodeString("data", IFDS.Xml.serialize(updateDetl(action, data))))				
			}
									
			if (validationXML != null)
			{				
				sendValidation(view, validationXML, successHandler, errorHandler);
			}
			else
			{
				successHandler();
			}
			
			function successHandler()
			{
				backupXML = null;
				if (popupName == 'mstr')
				{
					var mstrRowToHighlight = null;
					if (action == _self.ADD)
					{
						_self.setSelectedMstr(IFDS.Xml.getNodes(_mstrsXML, 'Mstr').length);
						mstrRowToHighlight = _resources.grids['mstrs'].getStore().getCount();											
					}
					else if (action == _self.MOD)
					{
						mstrRowToHighlight = _resources.grids['mstrs'].getStore().indexOf(_resources.grids['mstrs'].getSelectedRecord());
					}
					else
					{
						_self.clearSelectedMstr();
						mstrRowToHighlight = null;
					}
																			
					_resources.grids['mstrs'].loadData(_mstrsXML, ['addBtn']);
					if (mstrRowToHighlight)
					{
						_resources.grids['mstrs'].setSelectedRecord(mstrRowToHighlight);
					}
					_resources.popups['mstr'].hide();
				}
				else
				{	
					var detlRowToHighlight = null;
					if (action == _self.ADD)
					{
						_self.setSelectedDetl(IFDS.Xml.getNodes(_self.getSelectedMstr(), 'Detls/Detl').length);
						detlRowToHighlight = _resources.grids['detls'].getStore().getCount();							
					}
					else if (action == _self.MOD)
					{
						detlRowToHighlight = _resources.grids['detls'].getStore().indexOf(_resources.grids['detls'].getSelectedRecord());					
					}
					else
					{
						_self.clearSelectedDetl();
						detlRowToHighlight = null;
					}
					
					var mstrRecordToSelect = _selectedMstrIndex - 1;					
					_resources.grids['mstrs'].loadData(_mstrsXML, ['addBtn']);					
					_resources.grids['mstrs'].setSelectedRecord(mstrRecordToSelect)
					_resources.grids['detls'].loadData(_self.getSelectedMstr(), ['addBtn']);										
					
					if (detlRowToHighlight)
					{
						_resources.grids['detls'].setSelectedRecord(detlRowToHighlight);
					}					
					_resources.popups['detl'].hide();	
				}				
			}
			
			function errorHandler()
			{				
				_mstrsXML = backupXML;				
			}
		}
		
		,doUpdate: function()
		{						
			var updateStatus = null;		
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML(), responseHandler, null);			
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)				
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL 																			
				}
			}
			return updateStatus;			
		}			
		
		,getAccountTaxType: function()
		{
			var accountTaxType = IFDS.Xml.getNodeValue(_mstrsXML, '//taxType');
				
			return accountTaxType.toLowerCase();
		}
		,getTFSAAccountOwnerName: function()
		{
			var accountOwnerName = IFDS.Xml.getNodeValue(_mstrsXML, '//acctName');
				
			return accountOwnerName;
		}
	}	
}	