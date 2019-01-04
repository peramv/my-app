/*********************************************************************************************
 * @file	RESPInterfaceFile.Controller.js
 * @author	Narin Suanlamyai
 * @desc	Controller JS file for Interface File screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  24 Jan 2014 C. Daecha, CHG0033576 - RESP Interface File Issue.
 *          - Fix record picking logic for RESP interface files which have the same file name
 *
 *  20 May 2014 Narin SuanlamyaiP0220132 FN03 T55087
 *						  - Enhanced for CCS - SAGES RESP Program
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *			- Fixed screens don't response when user's profile has too many slots attached.  
 *
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	var _modPerm = null;
	var _delPerm = null;
	var _runPerm = null;
	
	var _accountNum = null;
	var _nextRecNum = null;
	var _requestRecNum = 50;
	
	var _currFileType = null;
	var _currSearchObj = new Object;
	
	var _interfaceFileXML = null;
	var _interfaceFileReloadXML = null;

	var _dtInterfaceFileInitService = "dtInterfaceFileInit";
	var _dtInterfaceFileReloadService = "dtInterfaceFileReload";
	
	// PRIVATE METHODS ****************************************	
	function interfaceFileInit()
	{
		var paramXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(paramXML, 'AccountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		
		clearGrid('fileListGrid');
		clearGrid('fieldSetGrid');
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtInterfaceFileInitService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{
			if (success)
			{			
				_interfaceFileXML = responseXML;
			}
			else
			{
				_interfaceFileXML = null;
			}
			
			if(_interfaceFileXML)
			{
				setPermission(IFDS.Xml.getNode(_interfaceFileXML, '//userPermissions'));
				
				displayInterfaceFileSearchBox();			
			}
		}

	}
	
	function interfaceFileReInit()
	{
		var paramXML = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(paramXML, 'AccountNum', _accountNum);
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtInterfaceFileInitService, null, paramXML, responseHandler, _translationMap['ProcMsg_Loading']);

		function responseHandler(success, responseXML)
		{	
			if (success)
			{
				_interfaceFileXML = responseXML;
			}
			else
			{
				_interfaceFileXML = null;
			}
			
			if(_interfaceFileXML)
			{
				setPermission(IFDS.Xml.getNode(_interfaceFileXML, '//userPermissions'));
				
				updateFilter();
			}
		}

	}
	
	function displayInterfaceFileSearchBox()
	{
		_accountNum = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
		if(_accountNum && _accountNum.toUpperCase() != 'ALL')
		{
			_resources.fields['acctFld'].setValue(_accountNum + " - " + IFDS.Xml.getNodeValue(IFDS.Xml.getNode(_interfaceFileXML, "//ownerNam") , "."));
			_resources.layout.get('mainLayout').get('chkboxLayout').hide();
		}else{
			// Show 'All' checkbox
			_resources.layout.get('mainLayout').get('chkboxLayout').show();
		}
		
		updateFilter();
	}
	
	function updateFilter()
	{
		loadSMVComboBox('benList', 'BeneficiaryList');
		loadSMVComboBox('fileTypeList', 'FileTypeList');
		loadSMVComboBox('taxYearList', 'TaxYearList');
		
		// Default SMV combo boxes
		var firstRec = _resources.fields['benList'].getStore().getAt(0);
		if(firstRec)_resources.fields['benList'].setValue(firstRec.get('code'));
		firstRec = _resources.fields['fileTypeList'].getStore().getAt(0);
		if(firstRec)_resources.fields['fileTypeList'].setValue(firstRec.get('code'));
		firstRec = _resources.fields['taxYearList'].getStore().getAt(0);
		if(firstRec)_resources.fields['taxYearList'].setValue(firstRec.get('code'));
		loadRecordType(_resources.fields['fileTypeList'].getValue());
	}
	
	function loadRecordType(fileType)
	{
		_resources.fields['recTypeList'].clearValue();
		if(fileType && fileType!="")
		{
			loadSMVComboBox('recTypeList', fileType + 'RecTypeList');
			var firstRec = _resources.fields['recTypeList'].getStore().getAt(0);
			if(firstRec)_resources.fields['recTypeList'].setValue(firstRec.get('code'));
		}
	}
	
	function loadTaxYear(fileType)
	{
		_resources.fields['taxYearList'].clearValue();
		if(fileType && fileType!="")
		{
			var listYearName = fileType + 'TaxYearList';
			var nodeExist  = IFDS.Xml.getNode(_interfaceFileXML, "//List[@listName='" + listYearName + "']")
			
			if (nodeExist)
				loadSMVComboBox('taxYearList', listYearName);
			else
				loadSMVComboBox('taxYearList', 'TaxYearList');
			var firstRec = _resources.fields['taxYearList'].getStore().getAt(0);
			if (firstRec)
				_resources.fields['taxYearList'].setValue(firstRec.get('code'));
		}
	}
	
	function validateFilter()
	{
		var isValid = true;
		var taxYear = _resources.fields['taxYearList'].getValue();
		if ( taxYear == null || taxYear.length != 4 || isNaN(taxYear) || parseInt(taxYear) > 9999)
		{		
			_resources.fields['taxYearList'].markInvalid(_translationMap["fldRequired"]);
			isValid = false;
		}
		
		if(DesktopWeb._SCREEN_PARAM_MAP['AccountNum'].toUpperCase() == 'ALL')
		{
			if(_resources.fields['allChkbox'].getValue())
			{
				_accountNum = "ALL";
			}else{
				var _accountNum = _resources.fields['acctFld'].getValue();
				if(_accountNum == null || _accountNum.length <=0)
				{
					_resources.fields['acctFld'].markInvalid(_translationMap["fldRequired"]);
					_accountNum = null;
					isValid = false;
				}
			}
		}
		
		
		return isValid;
	}
	
	function doReload(appendMode)
	{
		DesktopWeb.Ajax.doSmartviewAjax(_dtInterfaceFileReloadService, null, buildReloadXML(appendMode), responseHandler, _translationMap['ProcMsg_Loading']);
					
		function responseHandler(success, responseXML)
		{
			if (success)
			{
				reloadCallback(responseXML,appendMode);
			}
		}
	}
	
	function reloadCallback(respXML,appendMode)
	{
		if(!appendMode) {
			_interfaceFileReloadXML = respXML;

			var nodes = IFDS.Xml.getNodes(_interfaceFileReloadXML, "//InterfaceFileInfo/FileDetail");
			
			for(var i=0;i<nodes.length;i++)
			{
				IFDS.Xml.addSingleNode(nodes[i],'recID',i);
			}
		} else {
			var nodesOld = IFDS.Xml.getNodes(_interfaceFileReloadXML, "//InterfaceFileInfo/FileDetail");
			var nodesNew = IFDS.Xml.getNodes(respXML, "//InterfaceFileInfo/FileDetail");
			var numNodesOld = nodesOld.length;
			var numNodesNew = nodesNew.length;
			
			for(var i=0;i<numNodesNew;i++)
			{
				IFDS.Xml.addSingleNode(nodesNew[i],'recID',i+numNodesOld);
				IFDS.Xml.appendNode(IFDS.Xml.getNode(_interfaceFileReloadXML, "//InterfaceFileInfo"),nodesNew[i]);
			}
			
			var strBackupResp = "<InterfaceFileInfo>";
			for(var i=0;i<numNodesNew;i++)
			{
				strBackupResp += IFDS.Xml.serialize(nodesNew[i]);
			}
			strBackupResp += "</InterfaceFileInfo>";
			
			var backupResp = IFDS.Xml.stringToXML(strBackupResp);
			if(backupResp)
			{
				IFDS.Xml.appendNode(respXML,backupResp);
			}
			
			var moreRecNodeNew = IFDS.Xml.getNode(respXML, "//moreRecordsExist");
			if(moreRecNodeNew)
			{
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(_interfaceFileReloadXML, "//moreRecordsExist"),
									IFDS.Xml.getNodeValue(IFDS.Xml.getNode(respXML, "//moreRecordsExist")));
			}
			var rangeStartForNextNew = IFDS.Xml.getNode(respXML, "//rangeStartForNext");
			if(rangeStartForNextNew)
			{
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(_interfaceFileReloadXML, "//rangeStartForNext"),
									IFDS.Xml.getNodeValue(IFDS.Xml.getNode(respXML, "//rangeStartForNext")));
			}
		}
		
		var moreRecNode = IFDS.Xml.getNode(_interfaceFileReloadXML, "//moreRecordsExist");
		var moreRec = IFDS.Xml.getNodeValue(moreRecNode, ".");
		if(moreRec == 'yes')
		{
			_nextRecNum = IFDS.Xml.getNodeValue(IFDS.Xml.getNode(_interfaceFileReloadXML, "//rangeStartForNext"), ".");
			_resources.grids['fileListGrid'].enableButton('moreBtn');
		}else{
			_nextRecNum = null;
			_resources.grids['fileListGrid'].disableButton('moreBtn');
		}
		
		loadFileList(respXML,appendMode);
	}
	
	function loadFileList(respXML,appendMode)
	{
		_resources.grids['fileListGrid'].getStore().loadData(respXML, appendMode);
	}
	
	function loadFieldSet(fieldSetXML)
	{
		_resources.grids['fieldSetGrid'].getStore().loadData(fieldSetXML, false);
	}
	
	function prepareFieldSet(origFileRecsXML)
	{
		var xml = IFDS.Xml.newDocument('data');
		var fileRecsXML = IFDS.Xml.addSingleNode(xml, "FileRecords");
		var origFileRecXMLs = IFDS.Xml.getNodes(origFileRecsXML, "//fileRecord");
		
		for(i=0; i<origFileRecXMLs.length;)
		{
			var fieldName1 = (origFileRecXMLs[i])?IFDS.Xml.getNodeValue(origFileRecXMLs[i], "fieldNam"):"";
			var fieldValue1 = (origFileRecXMLs[i])?IFDS.Xml.getNodeValue(origFileRecXMLs[i], "fieldVal"):"";
			++i;
			var fieldName2 = (origFileRecXMLs[i])?IFDS.Xml.getNodeValue(origFileRecXMLs[i], "fieldNam"):"";
			var fieldValue2 = (origFileRecXMLs[i])?IFDS.Xml.getNodeValue(origFileRecXMLs[i], "fieldVal"):"";
			++i
			var fileRecXML = IFDS.Xml.addSingleNode(fileRecsXML, "fileRecord");
			IFDS.Xml.addSingleNode(fileRecXML, "fieldNam1", fieldName1);
			IFDS.Xml.addSingleNode(fileRecXML, "fieldVal1", fieldValue1);
			IFDS.Xml.addSingleNode(fileRecXML, "fieldNam2", fieldName2);
			IFDS.Xml.addSingleNode(fileRecXML, "fieldVal2", fieldValue2);
		}
		return xml;
	}
	
	function buildReloadXML(appendMode)
	{
		if(!appendMode)
		{
			_currSearchObj['AccountNum'] = _accountNum;
			_currSearchObj['RESPBenefID'] = _resources.fields['benList'].getValue();
			_currSearchObj['fileType'] = _resources.fields['fileTypeList'].getValue();
			_currSearchObj['taxYear'] = _resources.fields['taxYearList'].getValue();
			_currSearchObj['recType'] = _resources.fields['recTypeList'].getValue();
			_nextRecNum = "1";
		}
		
		var xml = IFDS.Xml.newDocument('data');
		
		IFDS.Xml.addSingleNode(xml, "AccountNum", _currSearchObj['AccountNum'] );
		IFDS.Xml.addSingleNode(xml, "RESPBenefID", _currSearchObj['RESPBenefID'] );
		IFDS.Xml.addSingleNode(xml, "fileType", _currSearchObj['fileType'] );
		IFDS.Xml.addSingleNode(xml, "taxYear", _currSearchObj['taxYear'] );
		IFDS.Xml.addSingleNode(xml, "recType", _currSearchObj['recType'] );
		IFDS.Xml.addSingleNode(xml, "startRecNum", _nextRecNum );
		IFDS.Xml.addSingleNode(xml, "requestRecNum", _requestRecNum );
		
		return xml;
	}
	
	function loadSMVComboBox(name, listName)
	{
		_resources.fields[name].clearValue();
		_resources.fields[name].getStore().loadData(IFDS.Xml.getNode(_interfaceFileXML, "//List[@listName='" + listName + "']"));
	}
	
	function checkAllCheckBox(checked)
	{
		var accountFld = _resources.fields['acctFld'];
		if ( checked )
		{
			_accountNum = "ALL";
			accountFld.setValue("");
			accountFld.clearInvalid();
			accountFld.setDisabled(true);
			interfaceFileReInit();
		}
		else
		{
			_accountNum = null;
			accountFld.setDisabled(false);
			accountFld.focus();
		}
	}

	function setPermission(permNode)
	{
		if(permNode)
		{
			_modPerm = IFDS.Xml.getNodeValue(permNode, 'modPerm');
			_delPerm = IFDS.Xml.getNodeValue(permNode, 'delPerm');
			_runPerm = IFDS.Xml.getNodeValue(permNode, 'runPerm');
		}
	}
	
	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}

	// PUBLIC ITEMS *************************************
	return {
		init: function(res)
		{
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			interfaceFileInit();
		}
		
		,selectFileTypeList: function(val)
		{
			loadRecordType(val);
			loadTaxYear(val);
		}
		
		,selectFileList: function(record)
		{
			loadFieldSet(prepareFieldSet(IFDS.Xml.stringToXML(record.fileRecords)));
		}
		
		,getInterfaceFileInfoXML: function(recID)
		{
			return IFDS.Xml.getNode(_interfaceFileReloadXML, "//InterfaceFileInfo/FileDetail[recID='" + recID + "']");
		}
		
		,getFileRecordsXML: function(recID)
		{
			return IFDS.Xml.getNode(_interfaceFileReloadXML, "//InterfaceFileInfo/FileDetail[recID='" + recID + "']/FileRecords");
		}
		
		,clickHandle_searchBtn: function()
		{
			if(validateFilter()){
				clearGrid('fieldSetGrid');
				clearGrid('fileListGrid');
				doReload(false);
			}
		}
		
		,clickHandle_moreBtn: function()
		{
			doReload(true);
		}
		
		,checkHandle_allChkbox: function(checked)
		{
			checkAllCheckBox(checked);
		}
		
		,changeHandler_acctFld: function(val)
		{
			_accountNum = val;
			interfaceFileReInit();
		}
		
	}	
}	