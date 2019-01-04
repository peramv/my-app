/*********************************************************************************************
 * @file	
 * @author	
 * @desc	
 *********************************************************************************************/
  /*
 *  History : 
 *
 *  22 Nov 2013 A. Mongkonrat P0181067 CHG0034430 T54443
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.
 *
 *  13 Dec 2017 Narin Suanlamyai P0266360 DFT0078343 
 *  				- Display ID Type description instead of ID Type code. 
 *  				- Add mode, default value of ID Type field will be blank.
 *  				- Save id type code to database instead of description. 
 *  
 *  23 Mar 2018 Nopphawan H. CHG0054255 INC0040935
 *					- Fixed JS error when add/modify a record in French mode.
 *						(use idTypeCode as the parameter to get idTypeValue (description))
 *					- Display "idTypeCode - idTypeValue" instead of idTypeValue (description)
 */

DesktopWeb.ScreenController = function () {

	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _updatesFlag = false;
	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _initDataXML = null;
	var _permissionsMap = {};

	var _acctIdentifierReloadView = 'dtAcctIdentifierReload';
	var _acctIdentifierValidationService = 'dtAcctIdentifierVldtns';
	var _acctIdentifierUpdateView = 'dtAcctIdentifierUpdate';

	
	// PRIVATE METHODS ****************************************	
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/add').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/mod').toLowerCase() == 'yes';
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//userPermissions/del').toLowerCase() == 'yes';
	}

	function formatAccountIdentifierFieldsXML(xml)
	{
		var acctIdentDetailNodes = IFDS.Xml.getNodes(xml, 'AcctIdentDetail');

		for (var i = 0; i < acctIdentDetailNodes.length; i++)
		{
			var strIDType = acctIdentDetailNodes[i].childNodes[0].nodeTypedValue;	
			var strIDDescription = acctIdentDetailNodes[i].childNodes[2].nodeTypedValue;	
			
			var strCodeDescription = strIDType + " - " + strIDDescription;
			acctIdentDetailNodes[i].childNodes[0].nodeTypedValue = strCodeDescription;
		}
		
		return xml;
	}
	
	function populateAccountIdentifierGrid(responseXML)
	{		
		var _acctIdentifierXML = IFDS.Xml.getNode(responseXML, "//AcctIdentifier");
		_resources.grids['accountIdentifierDetails'].loadData(_acctIdentifierXML);
	}

	function getPopupDataMap(data)
	{
		var dataType = data['idType'];
		
		if (dataType.search('INSNO') != -1)
		{
			data['idType'] = 'INSNO';
		}
		else if (dataType.search('INSFLG') != -1)
		{
			data['idType'] = 'INSFLG';
		}
		else if (dataType.search('EMPID') != -1)
		{
			data['idType'] = 'EMPID';
		}
		
		return data;
	}
	
	function getPopupDataMapAsXML(data)
	{
		var updateXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(updateXML, "AccountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		IFDS.Xml.addSingleNode(updateXML, "AcctIdent");

		var updateNodeXML = IFDS.Xml.addSingleNode(IFDS.Xml.getNode(updateXML, 'AcctIdent'), 'AcctIdentUpd');			
		
		var dataType = data['idType'];
		
		if (dataType.search('INSNO') != -1)
		{
			data['idType'] = 'INSNO';
		}
		else if (dataType.search('INSFLG') != -1)
		{
			data['idType'] = 'INSFLG';
		}
		else if (dataType.search('EMPID') != -1)
		{
			data['idType'] = 'EMPID';
		}
		
		IFDS.Xml.addSingleNode(updateNodeXML, "runMode", data['runMode']);
		IFDS.Xml.addSingleNode(updateNodeXML, "acctIDUUID", data['acctIDUUID']);
		IFDS.Xml.addSingleNode(updateNodeXML, "idType", data['idType']);
		IFDS.Xml.addSingleNode(updateNodeXML, "idValue", data['idValue']);
		IFDS.Xml.addSingleNode(updateNodeXML, "deff", DesktopWeb.Util.getSMVDateValue(data['effectDt']));
		IFDS.Xml.addSingleNode(updateNodeXML, "stopDate", DesktopWeb.Util.getSMVDateValue(data['stopDt']));
		IFDS.Xml.addSingleNode(updateNodeXML, "version", data['version']);
		
		return updateXML;
	}
	
	function doUpdate(_updateXML)
	{
		DesktopWeb.Ajax.doSmartviewUpdate(_acctIdentifierUpdateView, null, _updateXML, responseHandler, _translationMap['ProcMsg_Processing']);
						
		function responseHandler(success, responseXML)
		{
			updateStatus = success;
			if (success)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	function updateAccountIdentifier(action, data)
	{
		var dataUpdate = getPopupDataMap(data);
		var updateNode = IFDS.Xml.addSingleNode(IFDS.Xml.getNode(_updateXML, 'AcctIdent'), 'AcctIdentUpd');			
		IFDS.Xml.addSingleNode(updateNode, "runMode", dataUpdate['runMode']);
		IFDS.Xml.addSingleNode(updateNode, "acctIDUUID", dataUpdate['acctIDUUID']);
		IFDS.Xml.addSingleNode(updateNode, "idType", dataUpdate['idType']);
		IFDS.Xml.addSingleNode(updateNode, "idValue", dataUpdate['idValue']);
		IFDS.Xml.addSingleNode(updateNode, "deff", DesktopWeb.Util.getSMVDateValue(dataUpdate['effectDt']));
		IFDS.Xml.addSingleNode(updateNode, "stopDate", DesktopWeb.Util.getSMVDateValue(dataUpdate['stopDt']));
		IFDS.Xml.addSingleNode(updateNode, "version", dataUpdate['version']);
			
		if (action == "add")
		{				
			_resources.grids['accountIdentifierDetails'].addRecord(data);
		}
		else if (action == "modify")
		{
			_resources.grids['accountIdentifierDetails'].updateSelectedRecord(data);
		}
		else if (action == "delete")
		{
			_resources.grids['accountIdentifierDetails'].removeSelectedRecord();												
		}
	}
	
	function buildIDTypeDropdownList(idTypeListXML)
	{
		var idTypeNodes = IFDS.Xml.getNodes(idTypeListXML, 'Element');
		var newIDTypeListXML = IFDS.Xml.newDocument("List");
					
		Ext.each(idTypeNodes, function(idTypeNode){
			var eleNode = IFDS.Xml.addSingleNode(newIDTypeListXML, "Element");
			var idTypeCode = IFDS.Xml.getNodeValue(idTypeNode, "code");
			var idTypeValue = IFDS.Xml.getNodeValue(idTypeNode, "value");

			if (idTypeCode.length > 0 && idTypeValue.search(idTypeCode) == -1)
				idTypeValue = idTypeCode + " - " + idTypeValue;
			
			IFDS.Xml.addSingleNode(eleNode, "code", idTypeCode);
			IFDS.Xml.addSingleNode(eleNode, "value", idTypeValue);
		});
		
		_resources.popups['accIdentifierPopup'].getField('comboBoxIDType').loadData(newIDTypeListXML);
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		ADD: 'add'
	   ,MOD: 'modify'
	   ,DEL: 'delete'
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, "AccountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
			DesktopWeb.Ajax.doSmartviewAjax(_acctIdentifierReloadView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					_initDataXML = responseXML;
					storePermissions(responseXML);
					buildIDTypeDropdownList(IFDS.Xml.getNode(responseXML, '//List[@listName=\'IDTypeList\']'));
					populateAccountIdentifierGrid(responseXML);
				}											
			}

			_updateXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(_updateXML, "AccountNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
			IFDS.Xml.addSingleNode(_updateXML, "AcctIdent");			
		}
		
		,getDefaultDate: function()
		{
			try
			{
				return DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(_initDataXML, '*/DefaultDate/defaultDt'));	
			}
			catch (e)
			{
				return null;
			}
		}
		
		,openActionPopup: function(action)
		{
			_resources.popups['accIdentifierPopup'].init(action);
			_resources.popups['accIdentifierPopup'].show();
		}
		
		,openAdminPopup: function()
		{					
			var title = null;	
			var xml = null;

			title = _translationMap['AccountIdentifierDetails']+ ' - ' +_translationMap['Admin']
			
			var selectedRecord = _resources.grids['accountIdentifierDetails'].getSelectedRecord();
			
			var adminData = {};
			adminData['userName'] = selectedRecord.data.userName;
			adminData['procDate'] = selectedRecord.data.procDate;
			adminData['modUser'] = selectedRecord.data.modUser;
			adminData['modDate'] = selectedRecord.data.modDate;
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}

		,getIDValueComboBoxValues: function()
		{
			try
			{
				var xmlListNode = IFDS.Xml.getNode(_initDataXML, '//List[@listName=\'InsuredFlagList\']');

				return xmlListNode;
			}
			catch (e)
			{
				return null;
			}
		}
		
		,getIsInsuranceNumberNotEmpty: function()
		{
			var numberOfRows = _resources.grids['accountIdentifierDetails'].getStore().getCount();
			
			for (var i = 0; i < numberOfRows; i++)
			{
				var strIdType = _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.idType;
				
				if (strIdType.search('INSNO') != -1)
				{
					var strIdValue = _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.idValue;
					
					if (strIdValue != "")
					{
						return true;	
					}
				}
			}
			
			return false;
		}

		,getIsInsuranceFlagAlreadyPresent: function()
		{
			var numberOfRows = _resources.grids['accountIdentifierDetails'].getStore().getCount();
		
			for (var i = 0; i < numberOfRows; i++)
			{
				var strIdType = _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.idType;
				
				if (strIdType.search('INSFLG') != -1)
				{
					return true;	
				}
			}
			
			return false;
		}
		
		,getIsInsuranceNumberAlreadyPresent: function()
		{
			var numberOfRows = _resources.grids['accountIdentifierDetails'].getStore().getCount();
		
			for (var i = 0; i < numberOfRows; i++)
			{
				var strIdType = _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.idType;
				
				if (strIdType.search('INSNO') != -1)
				{
					return true;	
				}
			}
			
			return false;
		}
		
		,getEffAndStopDateFromExistingInsuranceNumber: function()
		{
			var numberOfRows = _resources.grids['accountIdentifierDetails'].getStore().getCount();
		
			for (var i = 0; i < numberOfRows; i++)
			{
				var strIdType = _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.idType;
				
				if (strIdType.search('INSNO') != -1)
				{
					var obj = 
					{
						 effDate: _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.effectDt,
						 stopDate: _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.stopDt
					}
					
					return obj;
				}
			}
			
			return null;
		}
		
		,getIsInsuranceFlagNO: function()
		{
			var numberOfRows = _resources.grids['accountIdentifierDetails'].getStore().getCount();
		
			for (var i = 0; i < numberOfRows; i++)
			{
				var strIdType = _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.idType;
				
				if (strIdType.search('INSFLG') != -1)
				{
					var strIdValue = _resources.grids['accountIdentifierDetails'].getStore().getAt(i).data.idValue;
					
					if (strIdValue.toUpperCase() == "NO")
					{
						return true;	
					}
				}
			}
			
			return false;
		}
		
		,handleAccIdentRecordSelectionChange: function()
		{
			var selectedRecord = _resources.grids['accountIdentifierDetails'].getSelectedRecord();
			
			if (selectedRecord)
			{
				_resources.grids['accountIdentifierDetails'].enableButton('addBtn');
				_resources.grids['accountIdentifierDetails'].enableButton('modifyBtn');
				_resources.grids['accountIdentifierDetails'].enableButton('delBtn');
				_resources.grids['accountIdentifierDetails'].enableButton('adminBtn');
			}
			else
			{
				_resources.grids['accountIdentifierDetails'].enableButton('addBtn');
				_resources.grids['accountIdentifierDetails'].disableButton('modifyBtn');
				_resources.grids['accountIdentifierDetails'].disableButton('delBtn');
				_resources.grids['accountIdentifierDetails'].disableButton('adminBtn');
			}
		}
	
		,savePopup: function(action, data)
		{
			var dataXML = getPopupDataMapAsXML(data);
			
			DesktopWeb.Ajax.doSmartviewAjax(_acctIdentifierValidationService, null, dataXML, responseHandler);
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					updateAccountIdentifier(action, data);
					doUpdate(dataXML);
					_resources.popups['accIdentifierPopup'].hide();
					DesktopWeb.Util.closeScreenWithDialog();
					_updatesFlag = true;
					
					return true;
				}											
				else
				{
					return false;
				}
			}
		}		
		
		,submitDataOnOK: function()
		{
			if (_updatesFlag)
			{
				return doUpdate(_updateXML);
			}
			else
			{
				return false;
			}
		}
		
		,getIDTypeDescription: function(idTypeCode)
		{
			var idTypeNode  = IFDS.Xml.getNode(_initDataXML, "//List[@listName='IDTypeList']/Element[code='" + idTypeCode + "']");
			var idTypeValue = "";
			
			if (idTypeNode) {
				idTypeValue = IFDS.Xml.getNodeValue(idTypeNode, 'value');
				if (idTypeCode.length > 0 && idTypeValue.search(idTypeCode) == -1)
					idTypeValue = idTypeCode + " - " + idTypeValue;
				return idTypeValue
			} else {
				return idTypeCode;
			}
		}
	}	
}	