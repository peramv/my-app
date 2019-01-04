 /*********************************************************************************************
 * @file	AcctAssociate.Controller.js
 * @author	Cherdsak Sangkasen
 * @desc	Controller JS file for Account Fee Model Association screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  20 Aug 2014 P. Wongpakdee P0181067 DFT0038386 T55605
 *			- Added validation to not allow blank Effective and Stop date
 *
 *  28 Aug 2014 A. Mongkonrat P0212180 DFT0038413 T55638
 *              Java Error on Account Association Screen.
 *
 *  24 Sep 2014 A. Mongkonrat P0212180 DFT0038413 T55776
 *              A record isn't updated when changing account number.
 *
 *  11 Sep 2014 A. Mongkonrat P0234765 I0 T55984
 *              MSF backdated account linking enhancements.
 *
 *  09 Jan 2015 Aurkarn Mongkonrat P0234765 FN01 DFT0046281 T80142
 *              Users should be able to accept a warning message or cancel.
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *		  	- Fixed screens don't response when user's profile has too many slots attached. 
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _nextStartRecNum = null;
	var _requestRecNum = 25;	
	var _acctAsscCounter = 0;
	var _initView = 'dtAcctFeeModAsscInit';
	var _reloadView = 'dtAcctFeeModAsscReload';
	var _updateView = 'dtAcctFeeModAsscUpd';	
	var _validateView =  'dtAcctFeeModAsscVal';
	var _historyView = 'dtHistoricalInfo';
	var _accountSearchView = 'AccountSearch';
	var _feeModelSearchView = 'FeeModelCodeSearch';
	var _holdCompSearchView = 'HoldingCompanySearch';
	var _invInstrSearchView = 'InvoiceInstrSearch'; 
	var _rptGrpSearchView = 'ReportGroupSearch';
	var _vars = {};
	var _mstrXML = null;
	var _listXMLs = {};
	var _permissionsMap = {};
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _defaultAsOfDate = null;
	var _defaultStopDate = null;
	
	var _ACCOUNT = "account";
	var _HOLDCOMP = "holdcomp";
	var _FEEMODEL = "feemodel";
	var _INVINSTR = "invinstr";
	var _RPTGRP = "rptgrp";
	var _MENU = "menu";
	
	// PRIVATE METHODS ****************************************	
	// Operate on XMLs
	
	function createListXML(xml)
	{
		var listXMLArr = IFDS.Xml.getNodes(xml, "//DropDowns/List");	
		Ext.each(listXMLArr, function(listXML){
			controlName = listXML.getAttribute('listName');
			_listXMLs[controlName] = listXML;			
		});		
	}
	
	function getDefaultModelType()
	{
		var retVal = "";				
		var count = 0;
		var elmXMLArr = IFDS.Xml.getNodes(_listXMLs["FeeModelTypeOptions"], "Element/code");		
		Ext.each(elmXMLArr, function(elmXML){				
			count += 1;
			if (count == 1)
			{
				retVal = IFDS.Xml.getNodeValue(elmXML, ".");				
			}
		});	
		if (count > 1)
		{
			return "";
		}
		else
		{
			return retVal;
		}			
	}
	
	function storePermissions(xml)
	{
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(xml, '//Permissions/inqPerm').toLowerCase() == _self.YES;
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(xml, '//Permissions/addPerm').toLowerCase() == _self.YES;
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(xml, '//Permissions/modPerm').toLowerCase() == _self.YES;
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(xml, '//Permissions/delPerm').toLowerCase() == _self.YES;
	}		
	
	function storeDefaultValues(xml)
	{
		_vars['EffectiveDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DatesDefaults/EffectiveDate'));
		_defaultAsOfDate = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DatesDefaults/EffectiveDate'));
		_vars['StopDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DatesDefaults/StopDate'));
		_defaultStopDate = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DatesDefaults/StopDate'));
		_vars['AutoGenFeeModelCode'] = IFDS.Xml.getNodeValue(xml, '//AutoGenCode/autoGenCode').toLowerCase() == _self.YES;
		_vars['AllowNewFeeModel'] = IFDS.Xml.getNodeValue(xml, '//CreateFromAcctAssoc/createFeeModel').toLowerCase() == _self.YES;
		_vars['DefApplFeeModelType'] = getDefaultModelType();
		_vars['DefFeeModelCode'] = _self.BLANK;
		_vars['InvInstrApp'] = IFDS.Xml.getNodeValue(xml, '//InvoiceAppl/invoiceAppl').toLowerCase() == _self.YES;
		_vars['RptGrpApp'] = IFDS.Xml.getNodeValue(xml, '//RptGroupAppl/rptGroupAppl').toLowerCase() == _self.YES;
		_vars['HoldCompApp'] = IFDS.Xml.getNodeValue(xml, '//HoldingEntAppl/holdingEntAppl').toLowerCase() == _self.YES;		
				
		_vars['AccountNum'] = 0;
		_vars['HoldCompCode'] = _self.BLANK;
		_vars['FeeModelCode'] = _self.BLANK;
		_vars['InvInstrCode'] = _self.BLANK;
		_vars['RptGrpId'] = _self.BLANK;
		
		_vars['FeeModelType'] = "";
		
		switch (DesktopWeb._SCREEN_PARAM_MAP['from_screen'])
		{
			case 'AccountDetailsDlg':
			{
				_vars["FromScreen"] = _ACCOUNT;
				_vars['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];	
				break;
			}
			case 'COADlg':
			{
				_vars["FromScreen"] = _ACCOUNT;
				_vars['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];	
				break;
			}
			case 'HoldingCompDlg':
			{
				_vars["FromScreen"] = _HOLDCOMP;
				_vars['HoldCompCode'] = DesktopWeb._SCREEN_PARAM_MAP['HoldingEntityCode'];	
				break;
			}
			case 'FeeModelDlg':
			{
				_vars["FromScreen"] = _FEEMODEL;
				_vars['FeeModelCode'] = DesktopWeb._SCREEN_PARAM_MAP['FeeModelCode'];	
				break;
			}
			case 'InvoiceInstr':
			{
				_vars["FromScreen"] = _INVINSTR;
				_vars['InvInstrCode'] = DesktopWeb._SCREEN_PARAM_MAP['billInstrCode'];	
				break;
			}
			case 'ReportGroup':
			{
				_vars["FromScreen"] = _RPTGRP;
				var url_vars = getUrlVars();
				for(var i in url_vars)
				{				
					 if (i == 'ReportGroupId' || i == 'ReportGroupSearch')
						DesktopWeb._SCREEN_PARAM_MAP[i] = url_vars[i] ;
				} 
				 
				_vars['RptGrpId'] = DesktopWeb._SCREEN_PARAM_MAP['ReportGroupId'];
				break;
			}
			default:
			{
				_vars["FromScreen"] = _MENU;
				break;
			}
		}
		
		_vars["InitWithSearch"] = _vars["FromScreen"] != _MENU;
		_vars['IsAllowAccessAcctDetail'] = IFDS.Xml.getNodeValue(xml, '//Permissions/AllowAccessAcctDetail').toLowerCase() == _self.YES;
		_vars['HoldCompRestrict'] = IFDS.Xml.getNodeValue(xml, '//Permissions/holdingCompRestrict').toLowerCase() == _self.YES;
		
	}
	
	function getUrlVars()
     {
         var vars = [], hash;
         var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
         for(var i = 0; i < hashes.length; i++)
         {
             hash = hashes[i].split('=');                        
             vars[hash[0]] = hash[1];
         }
         return vars;
     }

     
	
	function createMstrXML(xml, more)
	{	
		if (!_mstrXML || !more)
		{			
			_mstrXML = IFDS.Xml.newDocument("AcctFeeModel");
		}		
		
		var acctAsscXMLArr = IFDS.Xml.getNodes(xml, '//AcctFeeModel/AcctFeeModelDetl');
		Ext.each(acctAsscXMLArr, function(acctAsscXML){
			IFDS.Xml.addSingleNode(acctAsscXML, 'runMode', _self.UNCH);
			IFDS.Xml.addSingleNode(acctAsscXML, 'updSeq', _self.SEQUNCH);
			IFDS.Xml.addSingleNode(acctAsscXML, 'errMsg', '');
			IFDS.Xml.addSingleNode(acctAsscXML, 'gridIndex', IFDS.Xml.getNodeValue(acctAsscXML, 'shrAcctFeeId'));
			IFDS.Xml.addSingleNode(acctAsscXML, 'holdingEnt', IFDS.Xml.getNodeValue(acctAsscXML, 'holdingEntCode') + " - " + IFDS.Xml.getNodeValue(acctAsscXML, 'holdingEntName'));
			IFDS.Xml.addSingleNode(acctAsscXML, 'agency', IFDS.Xml.getNodeValue(acctAsscXML, 'agencyCode') + " - " + IFDS.Xml.getNodeValue(acctAsscXML, 'agencyName'));
			IFDS.Xml.addSingleNode(acctAsscXML, 'agent', IFDS.Xml.getNodeValue(acctAsscXML, 'agentCode') + " - " + IFDS.Xml.getNodeValue(acctAsscXML, 'agentName'));
			IFDS.Xml.addSingleNode(acctAsscXML, 'invoice', IFDS.Xml.getNodeValue(acctAsscXML, 'invoiceId') + " - " + IFDS.Xml.getNodeValue(acctAsscXML, 'invoiceName'));
			IFDS.Xml.addSingleNode(acctAsscXML, 'report', IFDS.Xml.getNodeValue(acctAsscXML, 'reportId') + " - " + IFDS.Xml.getNodeValue(acctAsscXML, 'reportName'));
			IFDS.Xml.appendNode(_mstrXML, acctAsscXML);	
		});
	}	
	
	function findAccountName(accountNum, displayValue)
	{
		var accountName = "";
		
		if (accountNum != null)
		{
			var acctAsscXMLArr = IFDS.Xml.getNodes(_mstrXML, '//AcctFeeModel/AcctFeeModelDetl');
			for (var i = 0; i < acctAsscXMLArr.length; i++)
			{			
				if (IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'accountNum') == accountNum)
				{
					accountName = IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'name');
				}
			}	
			return _self.BLANK;
		}
		
		if (displayValue != null)
		{
			accountName = displayValue.split("-")[1].trim();
		}
		
		return accountName;
	}
	
	function getAcctAssc(gridIndex)
	{
		var index = 0;		
		var acctAsscXMLArr = IFDS.Xml.getNodes(_mstrXML, '//AcctFeeModel/AcctFeeModelDetl');
		for (var i = 0; i < acctAsscXMLArr.length; i++)
		{			
			if (IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'gridIndex') == gridIndex)
			{
				return {
					node : acctAsscXMLArr[i], 
					index : index,
					shrAcctFeeId : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'shrAcctFeeId'),
					runMode : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'runMode'),
					accountNum : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'accountNum'),
					name : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'name'),
					agencyCode : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'agencyCode'),
					agencyName : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'agencyName'),
					agency : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'agency'),
					agentCode : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'agentCode'),
					agentName : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'agentName'),
					agent : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'agent'),
					feeModelCode : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'feeModelCode'),
					feeModelDesc : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'feeModelDesc').trim(),
					feeModelType : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'feeModelType'),
					feeModelTypeDesc : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'feeModelTypeDesc'),
					effectiveDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'effectiveDate')),
					stopDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'stopDate')),
					shrAcctFeeConfigVer : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'shrAcctFeeConfigVer'),
					modDelPerm : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'ModDelPerm'),
					gridIndex : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'gridIndex'),
					holdingEntCode : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'holdingEntCode'),
					holdingEntName : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'holdingEntName'),	
					holdingEnt : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'holdingEnt'),
					invInstrId : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'invoiceId'),
					invInstrName : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'invoiceName'),
					invInstr : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'invoice'),
					rptGrpId : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'reportId'),
					rptGrpName : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'reportName'),
					rptGrp : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'report'),
					userName : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'userName'),
					modUser : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'modUser'),
					procDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'processDate')),
					modDate : DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'modDate')),
					errMsg : IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'errMsg')
				};
			}
			if (IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'runMode') != _self.DEL)
			{
				index += 1;
			}
		}			
	}
	
	function getInitRequest()
	{
		var requestXML = IFDS.Xml.newDocument("data");		
		IFDS.Xml.addSingleNode(requestXML, "searchAccountNum", 0);		
		IFDS.Xml.addSingleNode(requestXML, "startRecNum", 1);
		IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);	
		return requestXML;
	}
	
	function getReloadRequest(more)
	{
		var requestXML = IFDS.Xml.newDocument("data");			
		
		if (_resources.fields['accountNumSrch'].selectedRecord != null)
		{
			IFDS.Xml.addSingleNode(requestXML, "searchAccountNum", _resources.fields['accountNumSrch'].selectedRecord.get('acctNum'));	
		}
		else
		{
			IFDS.Xml.addSingleNode(requestXML, "searchAccountNum", _vars['AccountNum']);	
		}
		
		if (_resources.fields['feeModelSrch'].selectedRecord != null)
		{
			IFDS.Xml.addSingleNode(requestXML, "searchFeeModelCode", _resources.fields['feeModelSrch'].selectedRecord.get('feeModelCode'));
		}
		else
		{
			IFDS.Xml.addSingleNode(requestXML, "searchFeeModelCode", _vars['FeeModelCode']);			
		}
		
		if (_resources.fields['holdCompSrch'].selectedRecord != null)
		{
			IFDS.Xml.addSingleNode(requestXML, "searchHoldCompany", _resources.fields['holdCompSrch'].selectedRecord.get('holdingCompanyCode'));			
		}
		else
		{
			IFDS.Xml.addSingleNode(requestXML, "searchHoldCompany", _vars['HoldCompCode']);			
		}
		
		if (_resources.fields['invInstrSrch'].selectedRecord != null)
		{
			IFDS.Xml.addSingleNode(requestXML, "searchInvoiceId", _resources.fields['invInstrSrch'].selectedRecord.get('billInstrCode'));
		}
		else
		{
			IFDS.Xml.addSingleNode(requestXML, "searchInvoiceId", _vars['InvInstrCode']);
		}
		
		if (_resources.fields['rptGrpSrch'].selectedRecord != null)
		{
			IFDS.Xml.addSingleNode(requestXML, "searchRptGroupId", _resources.fields['rptGrpSrch'].selectedRecord.get('reportGroupID'));		
		}
		else
		{		
			IFDS.Xml.addSingleNode(requestXML, "searchRptGroupId", _vars['RptGrpId']);			
		}
		
		IFDS.Xml.addSingleNode(requestXML, "searchType", _resources.fields['searchBy'].getValue());		
		IFDS.Xml.addSingleNode(requestXML, "searchEffectiveDate", _resources.fields['asOfDate'].getSMVDateString());	
		IFDS.Xml.addSingleNode(requestXML, "searchAll", (_resources.fields['optSelectAll'].getValue() ? _self.YES : _self.NO));
		IFDS.Xml.addSingleNode(requestXML, "startRecNum", (more ? _nextStartRecNum : 1));
		IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);
		
		return requestXML;
	}
	
	function getValidateRequest(obj, action, data)
	{	
		var requestXML = IFDS.Xml.newDocument("data");
		var xml = IFDS.Xml.newDocument("AcctFeeModelDetl");
		if (obj) 
		{
			if (obj.gridIndex.indexOf("NEWASSC") > -1 )
			{
				IFDS.Xml.addSingleNode(xml, "runMode", _self.ADD);
				IFDS.Xml.addSingleNode(xml, "shrAcctFeeId", 0);	
				IFDS.Xml.addSingleNode(xml, "shrAcctFeeConfigVer", 0);	
			}
			else
			{
				IFDS.Xml.addSingleNode(xml, "runMode", action);
				IFDS.Xml.addSingleNode(xml, "shrAcctFeeId", obj.shrAcctFeeId);	
				IFDS.Xml.addSingleNode(xml, "shrAcctFeeConfigVer", obj.shrAcctFeeConfigVer);	
			}
		}
		else
		{
			IFDS.Xml.addSingleNode(xml, "runMode", _self.ADD);
			IFDS.Xml.addSingleNode(xml, "shrAcctFeeId", 0);				
		}
		
		IFDS.Xml.addSingleNode(xml, "accountNum", data['accountNum']);
		IFDS.Xml.addSingleNode(xml, "feeModelType", data['feeModelType']);
		IFDS.Xml.addSingleNode(xml, "feeModelCode", data['feeModelCode']);
		IFDS.Xml.addSingleNode(xml, "feeModelDesc", data['feeModelDesc']);
		IFDS.Xml.addSingleNode(xml, "effectiveDate", data['effectiveDate']);
		IFDS.Xml.addSingleNode(xml, "stopDate", data['stopDate']);
		IFDS.Xml.addSingleNode(xml, "invoiceId", data['invoiceId']);
		IFDS.Xml.addSingleNode(xml, "reportId", data['reportId']);
			
		return IFDS.Xml.appendNode(requestXML, xml);
	}
	
	function getValidateDelete(obj)
	{	
		var requestXML = IFDS.Xml.newDocument("data");
		var xml = IFDS.Xml.newDocument("AcctFeeModelDetl");
		
		if (obj) 
		{
			IFDS.Xml.addSingleNode(xml, "runMode", _self.DEL);
			IFDS.Xml.addSingleNode(xml, "shrAcctFeeId", obj.shrAcctFeeId);	
			IFDS.Xml.addSingleNode(xml, "accountNum", obj.accountNum);
			IFDS.Xml.addSingleNode(xml, "feeModelCode", obj.feeModelCode);
			IFDS.Xml.addSingleNode(xml, "effectiveDate", DesktopWeb.Util.getSMVDateValue(obj.effectiveDate));
			IFDS.Xml.addSingleNode(xml, "feeModelType", obj.feeModelType);
		}
			
		return IFDS.Xml.appendNode(requestXML, xml);
	}
	
	function getUpdateRequest(mode)
	{		
		var requestXML = IFDS.Xml.newDocument("data");
		IFDS.Xml.addSingleNode(requestXML, 'runMode', mode);
		var xml = IFDS.Xml.newDocument("AcctFeeModelDetls");
		var acctAsscXMLArr = IFDS.Xml.getNodes(_mstrXML, '//AcctFeeModel/AcctFeeModelDetl');
		var updAcctAsscXML;
		var runMode;
		var newAcctAssc;
		
		for (var i = 0; i < acctAsscXMLArr.length; i++)
		{				
			runMode = IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'runMode');
			
			if (IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'gridIndex').indexOf("NEWASSC") > -1)
			{
				newAcctAssc = true;
			}
			else 
			{
				newAcctAssc = false;
			}
					
			// DISCARD 1) Unchanged record 2) Deletion of new buffer record
			if  (!(newAcctAssc && runMode == _self.DEL) && 
				!(runMode == _self.UNCH))
			{
				updAcctAsscXML = IFDS.Xml.newDocument("AcctFeeModelDetl");				
				IFDS.Xml.addAttribute(IFDS.Xml.getNode(updAcctAsscXML, "."), 'RecordSource', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'gridIndex'));
				
				if (newAcctAssc)
				{
					IFDS.Xml.addSingleNode(updAcctAsscXML, 'runMode', _self.ADD);
					//IFDS.Xml.addSingleNode(updAcctAsscXML, 'updSeq', _self.SEQADD);	
				}
				else
				{
					IFDS.Xml.addSingleNode(updAcctAsscXML, 'runMode', runMode);
					//IFDS.Xml.addSingleNode(updAcctAsscXML, 'updSeq', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'updSeq'));		
				}
								
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'accountNum', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'accountNum'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'FeeModelType', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'feeModelType'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'FeeModelCode', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'feeModelCode'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'FeeModelDesc', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'feeModelDesc'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'InvoiceId', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'invoiceId'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'ReportId', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'reportId'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'EffectiveDate', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'effectiveDate'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'StopDate', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'stopDate'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'shrAcctFeeId', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'shrAcctFeeId'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'shrAcctFeeConfigVer', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'shrAcctFeeConfigVer'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'gridIndex', IFDS.Xml.getNodeValue(acctAsscXMLArr[i], 'gridIndex'));
				IFDS.Xml.addSingleNode(updAcctAsscXML, 'newFeeModelCode', _self.isNewFeeModel() ? _self.YES : _self.NO);
			
				IFDS.Xml.appendNode(xml, updAcctAsscXML);
			}
		}
			
		return IFDS.Xml.appendNode(requestXML, xml);
	}	
	
	function addNewAcctAssc(data)
	{
		if (!_mstrXML)
		{			
			_mstrXML = IFDS.Xml.newDocument("AcctFeeModel");
		}		
		_acctAsscCounter += 1;
		var newAcctAsscXML = IFDS.Xml.newDocument("AcctFeeModelDetl");	
		
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'runMode', _self.ADD);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'updSeq', _self.SEQADD);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'shrAcctFeeId', 0);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'accountNum', data['accountNum']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'name', data['name']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'agencyCode', data['agencyCode']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'agencyName', data['agencyName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'agency', data['agencyCode'] + " - " + data['agencyName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'agentCode', data['agentCode']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'agentName', data['agentName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'agent', data['agentCode'] + " - " + data['agentName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'feeModelType', data['feeModelType']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'feeModelTypeDesc', data['feeModelTypeDesc']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'feeModelCode', data['feeModelCode']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'feeModelDesc', data['feeModelDesc']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'holdingEntCode', data['holdingEntCode']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'holdingEntName', data['holdingEntName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'holdingEnt', data['holdingEntCode'] + " - " + data['holdingEntName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'invoiceId', data['invInstrId']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'invoiceName', data['invInstrName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'invoice', data['invInstrId'] + " - " + data['invInstrName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'reportId', data['rptGrpId']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'reportName', data['rptGrpName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'report', data['rptGrpId'] + " - " + data['rptGrpName']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'effectiveDate', data['effectiveDate']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'stopDate', data['stopDate']);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'shrAcctFeeConfigVer', 0);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'modDelPerm', _self.YES);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'gridIndex', "NEWASSC" + _acctAsscCounter);
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'userName');
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'modUser');
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'procDate');
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'modDate');
		IFDS.Xml.addSingleNode(newAcctAsscXML, 'errMsg');
		
		IFDS.Xml.appendNode(_mstrXML, newAcctAsscXML);
		
		_self.updatesFlag = true;	
		
	}
	
	function updateAcctAssc(gridIndex, data)
	{
		var acctAssc = getAcctAssc(gridIndex);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'runMode'), _self.MOD);
		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'updSeq'), _self.SEQMOD);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'feeModelCode'), data['feeModelCode']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'feeModelDesc'), data['feeModelDesc']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'feeModelType'), data['feeModelType']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'feeModelTypeDesc'), data['feeModelTypeDesc']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'holdingEntCode'), data['holdingEntCode']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'holdingEntName'), data['holdingEntName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'holdingEnt'), data['holdingEntCode'] + " - " + data['holdingEntName']);		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'invoiceId'), data['invInstrId']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'invoiceName'), data['invInstrName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'invoice'), data['invInstrId'] + " - " + data['invInstrName']);		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'reportId'), data['rptGrpId']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'reportName'), data['rptGrpName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'report'), data['rptGrpId'] + " - " + data['rptGrpName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'effectiveDate'), data['effectiveDate']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'stopDate'), data['stopDate']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'accountNum'), data['accountNum']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'name'), data['name']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'agencyCode'), data['agencyCode']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'agencyName'), data['agencyName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'agency'), data['agencyCode'] + " - " + data['agencyName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'agentCode'), data['agentCode']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'agentName'), data['agentName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'agent'), data['agentCode'] + " - " + data['agentName']);
		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'errMsg'), data['errMsg']);
	
		_self.updatesFlag = true;	
		
		return acctAssc.index;		
	}	
	
	function deleteAcctAssc(gridIndex)
	{		
		var acctAssc = getAcctAssc(gridIndex);
		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'runMode'), _self.DEL);				
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'updSeq'), _self.SEQDEL);	
		
		_self.updatesFlag = true;
	}

	function storeContextErrors(errorNodes)
	{
		clearErrMsg();
		var focusIdx = 0;
		
		for (var i = 0; i < errorNodes.length; i++)
		{		
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			if (table)
			{
				var acctAsscGridIndex = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');			
				
				var acctAssc = getAcctAssc(acctAsscGridIndex);	
				if (!IFDS.Xml.getNode(acctAssc.node, 'errMsg'))		
				{				
					IFDS.Xml.addSingleNode(acctAssc.node, 'errMsg', errMsg);		
				}
				else
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'errMsg'), errMsg);
				}
				
				if (acctAssc.runMode == _self.DEL)
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'runMode'), _self.UNCH);
					//IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAssc.node, 'updSeq'), _self.SEQUNCH);
				}
				if (focusIdx == 0)
				{
					focusIdx = acctAssc.index;
				}
			}
		}
				
		_self.refreshGrdAcctAssc(focusIdx);		
	}	
	
	function clearErrMsg()
	{
		var acctAsscXMLArr = IFDS.Xml.getNodes(_mstrXML, '//AcctFeeModel/AcctFeeModelDetl');
		for (var i = 0; i < acctAsscXMLArr.length; i++)
		{
			if (IFDS.Xml.getNode(acctAsscXMLArr[i], 'errMsg'))		
			{				
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(acctAsscXMLArr[i], 'errMsg'), "");
			}
		}
	}
	
	function goToScreen(screen)
	{
		var params = {};
		var screenName = '';
		
		params['prevScreen'] = 'AcctAssociate';
		params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		
		switch (screen)
		{
			case _INVINSTR:
			{
				screenName = 'InvoiceInstr';
				params['BrowserTitle'] = 'Invoice Instruction Maintenance';
				params['HoldingEntityCode'] = DesktopWeb._SCREEN_PARAM_MAP['holdingEntityCode'];
				params['invoiceID'] = DesktopWeb._SCREEN_PARAM_MAP['invoiceID'];
				params['invoiceDisp'] = DesktopWeb._SCREEN_PARAM_MAP['invoiceDisp'];
				params['enableholdingFlag'] = DesktopWeb._SCREEN_PARAM_MAP['enableholdingFlag'];
				params['asOfDate'] = DesktopWeb._SCREEN_PARAM_MAP['asOfDate'];
				params['optSelectAsOfDate'] = DesktopWeb._SCREEN_PARAM_MAP['optSelectAsOfDate'];
				params['rowSelectedIndex'] = DesktopWeb._SCREEN_PARAM_MAP['rowSelectedIndex'];	
				params['billInstrID'] = DesktopWeb._SCREEN_PARAM_MAP['billInstrID'];
				params['billInstrCode'] = DesktopWeb._SCREEN_PARAM_MAP['billInstrCode'];				
				break;
			}
			case _RPTGRP:
			{
				screenName = 'ReportGroup';
				params['BrowserTitle'] = 'Report Group Maintenance';
				params['HoldingEntityCode'] = DesktopWeb._SCREEN_PARAM_MAP['HoldingEntityCode'];
				params['ReportGroupId'] = DesktopWeb._SCREEN_PARAM_MAP['ReportGroupId'];
				params['Readonly'] = DesktopWeb._SCREEN_PARAM_MAP['Readonly'];
				params['ReportGroupSearch'] = DesktopWeb._SCREEN_PARAM_MAP['ReportGroupSearch'];				
				params['asOfDate'] = DesktopWeb._SCREEN_PARAM_MAP['asOfDate'];
				params['optSelectAsOfDate'] = DesktopWeb._SCREEN_PARAM_MAP['optSelectAsOfDate'];
				break;
			}
		}
		DesktopWeb.Util.goToScreen(screenName, params);
	}
	
	// PUBLIC ITEMS *************************************
	// Operate on Objects
	return {				
		ADD: 'Add'
		, DEL: 'Delete'
		, MOD: 'Modify'
		, UNCH: 'Unch'
		, VEW: 'View'
		, YES: 'yes'
		, NO: 'no'
		, BLANK: ''
		, SEQADD: '3'
		, SEQMOD: '2'
		, SEQDEL: '1'
		, SEQUNCH: '0'
		, updatesFlag: false
		, MF: 'MF'
		, MFR: 'MFR'
		, DF: 'DF'
		, commitValFlag: false
		, defaultAsOfDate : _defaultAsOfDate
		, defaultStopDate : _defaultStopDate
		
		, init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			DesktopWeb._SCREEN_PARAM_MAP['interfaceName'] = 'ifds.dt.Account.AcctFeeModelAssoc';
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, getInitRequest(), responseHandler, _translationMap['Loading']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{																		
					createListXML(responseXML);
					storePermissions(responseXML);
					storeDefaultValues(responseXML);	
					createMstrXML(responseXML, false);
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					_self.enablePermButtons();
					_self.populateDropdowns();
					_self.refreshGrdAcctAssc(0);
					_self.hideColumns();
					_self.enableMoreButton(_nextStartRecNum);	

					if (_vars['InitWithSearch'])
					{
						_self.setSearchField(_self.doSearch, false);						
					}
					else
						_self.setSearchField(null,false);
					
					
				}
			}	
		}
		
		, populateDropdowns: function()
		{
			_resources.fields['feeModelType'].getStore().loadData(_listXMLs["FeeModelTypeOptions"]);	
			_resources.fields['feeModelType'].clearValue();
			_resources.fields['feeModelType'].getStore().filterBy(
				function fn(record){
					var retVal = true;							
					if (record.get('code') == _self.MF && _vars['HoldCompRestrict'])
					{
						retVal = false;
					}
					return retVal;	
				}
			);
			
			_resources.fields['searchBy'].getStore().loadData(_listXMLs["SearchByOptions"]);
			_resources.fields['searchBy'].clearValue();
			_resources.fields['searchBy'].getStore().filterBy(
				function fn(record){
					var retVal = true;							
					if ( (record.get('code') == _HOLDCOMP && (!_vars['HoldCompApp'] || _vars['HoldCompRestrict'])) ||
						 (record.get('code') == _INVINSTR && (!_vars['InvInstrApp'] || _vars['HoldCompRestrict'])) ||
						 (record.get('code') == _RPTGRP && !_vars['RptGrpApp']))
					{
						retVal = false;
					}
					return retVal;	
				}
			);
		}

		, setSearchField: function(callBackfn, flag)
		{
			var isSuccess = null;
			switch (_vars['FromScreen'])
			{
				case _ACCOUNT:
				{
					_self.populateSearchField(_ACCOUNT);
					_self.setSuggestValue(_accountSearchView , _vars["AccountNum"], null, null, "accountNumSrch", callBackfn, flag);
					_self.enableSearchField(false);
					break;
				}
				case _FEEMODEL:
				{
					_self.populateSearchField(_FEEMODEL);
					_self.setSuggestValue(_feeModelSearchView , _vars["FeeModelCode"], null, null, "feeModelSrch", callBackfn, flag);
					_self.enableSearchField(false);
					break;
				}
				case _HOLDCOMP:
				{
					_self.populateSearchField(_HOLDCOMP);
					_self.setSuggestValue(_holdCompSearchView , _vars["HoldCompCode"], null, null, "holdCompSrch", callBackfn, flag);
					_self.enableSearchField(false);
					break;
				}
				case _INVINSTR:
				{
					_self.populateSearchField(_INVINSTR);
					_self.setSuggestValue(_invInstrSearchView , _vars["InvInstrCode"], "holdingCompanyCode", _vars["HoldCompCode"], "invInstrSrch", callBackfn, flag);
					_self.enableSearchField(false);
					break;
				}
				case _RPTGRP:
				{
					_self.populateSearchField(_RPTGRP);
					_self.setSuggestValue(_rptGrpSearchView , _vars["RptGrpId"], "holdingEntityCode", _vars["HoldCompCode"], "rptGrpSrch", callBackfn, flag);
					_self.enableSearchField(false);
					break;
				}
				default:
				{
					_self.populateSearchField(_ACCOUNT);
					_resources.fields['accountNumSrch'].setValue(_self.BLANK);
					_self.enableSearchField(true);
					
					if (callBackfn && callBackfn != undefined)
						callBackfn( flag );
					
					break;
				}
			}
			
			_resources.fields['optSelectAsOfDate'].setValue(true);
			_resources.fields['optSelectAll'].setValue(false);
			_resources.fields['asOfDate'].setValue(_vars['EffectiveDate']);				
		}
		
		, openActionPopup: function(popupName, action)
		{
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();
		}
		
		, doSearch: function(more)
		{					
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, {ignoreErrorCode: '15'}, getReloadRequest(more), responseHandler, _translationMap['ProcMsg_Searching']);			

			function responseHandler(success, responseXML)
			{
				if (success)
				{						
					createMstrXML(responseXML, more);						
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					_self.saveSearchValue();
					_self.refreshGrdAcctAssc(0);
					_self.enableMoreButton(_nextStartRecNum);		
					_self.enablePermButtons();
					_self.updatesFlag = false;
				}
				else
				{
					_self.clearGrdAcctAssc();
				}
			}			
		}
		
		, doUpdate: function ()
		{
			var updateStatus = null;	
			
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest("update"), responseHandler, _translationMap['Processing']);			

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
		
		, doCommitValidate: function()
		{
			DesktopWeb.Ajax.doSmartviewAjax(_updateView, null, getUpdateRequest("validation"), responseHandler, _translationMap['Processing'], Ext.Msg.OKCANCEL);			

			function responseHandler(success, responseXML, contextErrors, warnings, btn)
			{
				if (success)
				{					
					if (btn == null || btn == 'ok') {
						DesktopWeb.Util.commitScreen();
					}
				}
				else 
				{
					storeContextErrors(contextErrors);
				}
			}
		}
		
		, doFrontValidate: function(action)
		{
			var pass = true;
			
			if (_resources.fields['stopDate'].getValue() < _resources.fields['effectiveDate'].getValue()) 
			{ 
				_resources.fields['stopDate'].markInvalid(_translationMap['DeffBeforeStop']); 
				_resources.fields['effectiveDate'].markInvalid(_translationMap['DeffBeforeStop']); 
				pass = false;
			}
			
			if (_resources.fields['effectiveDate'].getRawValue() == "")
			{ 
				_resources.fields['effectiveDate'].markInvalid(_translationMap['FldRequired']); 
				pass = false;
			}	

			if (_resources.fields['stopDate'].getRawValue() == "")
			{ 
				_resources.fields['stopDate'].markInvalid(_translationMap['FldRequired']); 
				pass = false;
			}			
			
			if (action == _self.ADD)
			{
				if (_self.allowNewFeeModel())
				{
					if (_resources.fields['optNewFeeModel'].getValue())	
					{
						if (_resources.fields['feeModelAddNewCode'].getValue == null)
						{
							_resources.fields['feeModelAddNewCode'].markInvalid(_translationMap['FldRequired']); 
							pass = false;
						}
					}
					else
					{
						if (_resources.fields['feeModelAddExistCode'].selectedRecord == null || _resources.fields['feeModelAddExistCode'].getRawValue() == "")
						{
							_resources.fields['feeModelAddExistCode'].markInvalid(_translationMap['FldRequired']); 
							pass = false;
						}
					}
				}
				else
				{
					if (_resources.fields['feeModelCode'].selectedRecord == null || _resources.fields['feeModelCode'].getRawValue() == "")
					{
						_resources.fields['feeModelCode'].markInvalid(_translationMap['FldRequired']); 
						pass = false;
					}
				}
			}
			else
			{
				if (_resources.fields['feeModelCode'].selectedRecord == null || _resources.fields['feeModelCode'].getRawValue() == "")
				{
					_resources.fields['feeModelCode'].markInvalid(_translationMap['FldRequired']); 
					pass = false;
				}
			}
			
			if ((_resources.fields['accountNum'].selectedRecord == null && _resources.fields['accountNum'].isValid()) || (_resources.fields['accountNum'].getRawValue() == "")) 
			{ 
				_resources.fields['accountNum'].markInvalid(_translationMap['FldRequired']); 
				pass = false;
			}
			
			if (_resources.fields['feeModelType'].getValue() == null && _resources.fields['feeModelType'].isValid()) 
			{ 
				_resources.fields['feeModelType'].markInvalid(_translationMap['FldRequired']); 
				pass = false;
			}
			
			if (_resources.fields['feeModelType'].getValue() == _self.MF && _resources.fields['invInstr'].selectedRecord == null && _vars['InvInstrApp'])
			{
				_resources.fields['invInstr'].markInvalid(_translationMap['FldRequired']); 
				pass = false;
			}
			
			return pass;
		}
		
		, doValidate: function (action, data)
		{
			if (action == _self.VEW)
			{								
				_resources.popups['frmAcctAssc'].hide();
				return true;
			}
			
			var gridIndex = "";
			var obj = null;
			if (action != _self.ADD) 
			{
				obj = this.getSelectedAcctAssc();
			}
			
			if (_self.doFrontValidate(action))
			{
			
				DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, getValidateRequest(obj, action, data), responseHandler, _translationMap['Validating'], Ext.Msg.OKCANCEL);			

				function responseHandler(success, responseXML, contextErrors, warnings, btn)
				{
					if (success)
					{
						if (btn == null || btn == 'ok')
							_self.doSave(action, data);
					}
					else 
					{
						var contextErrors = IFDS.Xml.getNodes(responseXML, '//Errors/Error');
						Ext.each(contextErrors, function(contextError){
							var errorCode = IFDS.Xml.getNodeValue(contextError, 'errorCode');
							var errorText = IFDS.Xml.getNodeValue(contextError, 'text');
							switch (errorCode)
							{
								case '1394': 
								{
									break;
								}
								case '1395':
								{
									break;
								}
							}																
						});
					}
				}	
			}
		}
		
		, doSave: function(action, data)
		{
			if (action == _self.ADD)
			{					
				addNewAcctAssc(data);
				_self.refreshGrdAcctAssc(_resources.grids['grdAcctAssc'].getStore().getCount());										
				_resources.popups['frmAcctAssc'].hide();
			}
			else if (action == _self.MOD)
			{
				var index = updateAcctAssc(_self.getSelectedAcctAssc().gridIndex, data);
				_self.refreshGrdAcctAssc(index);						
				_resources.popups['frmAcctAssc'].hide();
			}
			else if (action == _self.DEL)
			{					
				deleteAcctAssc(_self.getSelectedAcctAssc().gridIndex);
				_self.refreshGrdAcctAssc(0);				
				_resources.popups['frmAcctAssc'].hide();
			}
		}
		
		, enablePermButtons: function ()
		{			
			if (_permissionsMap['inq']) 
			{ 
				_resources.buttons['cmdSearch'].enable(); 
			} 
			else 
			{ 
				_resources.buttons['cmdSearch'].disable(); 
			}
			
			if (_permissionsMap['add']) 
			{ 
				_resources.grids['grdAcctAssc'].enableButton(1); 
			} 
			else 
			{ 
				_resources.grids['grdAcctAssc'].disableButton(1); 
			}

			if (_permissionsMap['mod']) 
			{ 
				_resources.grids['grdAcctAssc'].enableButton(2); 
			} 
			else 
			{ 
				_resources.grids['grdAcctAssc'].disableButton(2); 
			}			
								
			var acctAssc = this.getSelectedAcctAssc();
			if (acctAssc)		
			{
				if (acctAssc.gridIndex.indexOf("NEWASSC") > -1) 
				{
					_resources.grids['grdAcctAssc'].enableButton(2);
					_resources.grids['grdAcctAssc'].enableButton(3);
					_resources.grids['grdAcctAssc'].disableButton(5);
					_resources.grids['grdAcctAssc'].disableButton(6);
				}
				else
				{
					/* Variable acctAssc.modDelPerm is indicated only "Delete" permission base on IN whihsh is allowed user to modify assocation */
					if (acctAssc.modDelPerm.toLowerCase() == _self.YES)
					{
						if (_permissionsMap['del']) { _resources.grids['grdAcctAssc'].enableButton(3); } else { _resources.grids['grdAcctAssc'].disableButton(3); }
					}
					else
					{
						_resources.grids['grdAcctAssc'].disableButton(3);						
					}
					_resources.grids['grdAcctAssc'].enableButton(5);
					_resources.grids['grdAcctAssc'].enableButton(6);
				}
			}				
			else
			{
				_resources.grids['grdAcctAssc'].disableButton(2);
				_resources.grids['grdAcctAssc'].disableButton(3);
				_resources.grids['grdAcctAssc'].disableButton(5);
				_resources.grids['grdAcctAssc'].disableButton(6);
			}		
						
			if (_vars['FromScreen'] == _ACCOUNT)
			{
				_resources.grids['grdAcctAssc'].disableButton(0);
			}
			else
			{
				if (_vars['IsAllowAccessAcctDetail'] && _resources.grids['grdAcctAssc'].getSelectedRecord())
				{
					_resources.grids['grdAcctAssc'].enableButton(0);
				}
				else
				{
					_resources.grids['grdAcctAssc'].disableButton(0);
				}
			}
		}

		, enableMoreButton: function (moreRec)
		{
			if (moreRec)
			{
				_resources.grids['grdAcctAssc'].enableButton(4);
			}
			else
			{
				_resources.grids['grdAcctAssc'].disableButton(4);
			}			
		}
		
		, refreshGrdAcctAssc: function (index)
		{		
			_resources.grids['grdAcctAssc'].loadData(_mstrXML);
			_resources.grids['grdAcctAssc'].setSelectedRecord(index);
		}

		, getSelectedAcctAssc: function()
		{
			if (_resources.grids['grdAcctAssc'].getSelectedRecord()) 
			{
				return getAcctAssc(_resources.grids['grdAcctAssc'].getSelectedRecord().get("gridIndex"));
			} 
			else 
			{
				return null;
			}
		}

		, setSelectedAcctAssc: function(gridIdnex)		
		{			
			_self.enablePermButtons();	
		}
		
		, populateAcctAssc: function(action)
		{			
			var holdingComp = null;
			_vars['mode'] = action;
			
			if (_resources.fields['holdComp'].selectedRecord != null) 
			{
				holdingComp = _resources.fields["holdComp"].selectedRecord.get('holdingcompanyCode');
			}			
			
			switch (action)
			{
				case _self.ADD:
				{
					if (_vars["AccountNum"] != _self.BLANK && _vars["FromScreen"] != _MENU)
					{
						_self.setSuggestValue(_accountSearchView , _vars["AccountNum"], null, holdingComp, "accountNum");
					}
					else
					{
						_resources.fields['accountNum'].setValue(_self.BLANK);
					}
					
					_resources.fields['holdComp'].setValue(_self.BLANK);
					
					if (_vars["FeeModelCode"] != _self.BLANK && _vars["FromScreen"] != _MENU)
					{
						_self.setSuggestValue(_feeModelSearchView , _vars["FeeModelCode"], "searchHoldCompany" , holdingComp, "feeModelCode");
						_self.setSuggestValue(_feeModelSearchView , _vars["FeeModelCode"], "searchHoldCompany" , holdingComp, "feeModelAddExistCode");	
					}
					else
					{
						_resources.fields['feeModelCode'].setValue(_self.BLANK);
						_resources.fields['feeModelAddExistCode'].setValue(_self.BLANK);
						_resources.fields['feeModelDesc'].setValue(_self.BLANK);
					}
					
					if (_vars["DefApplFeeModelType"] != _self.BLANK && _vars["FromScreen"] != _MENU)
					{
						_resources.fields['feeModelType'].setValue(_vars['DefApplFeeModelType']);
					}
					else
					{
						_resources.fields['feeModelType'].setValue(_self.getFeeModelType());
					}
					
					if (_vars["InvInstrCode"] != _self.BLANK && _vars["FromScreen"] != _MENU)
					{
						_self.setSuggestValue(_invInstrSearchView , _vars["InvInstrCode"], "holdingEntityCode", holdingComp, "invInstr");
					}
					else
					{
						_resources.fields['invInstr'].setValue(_self.BLANK);
					}
					
					if (_vars["RptGrpId"] != _self.BLANK && _vars["FromScreen"] != _MENU)
					{
						_self.setSuggestValue(_rptGrpSearchView , _vars["RptGrpId"], "holdingEntityCode" , holdingComp, "rptGrp");
					}
					else
					{
						_resources.fields['rptGrp'].setValue(_self.BLANK);
					}
					
					_self.populateHoldComp(_vars["FromScreen"]);
					
					_resources.fields['feeModelAddNewCode'].setValue(_self.BLANK);
					_resources.fields['feeModelAddDesc'].setValue(_self.BLANK);	
					_resources.fields['effectiveDate'].setValue(_vars['EffectiveDate']);
					_resources.fields['stopDate'].setValue(_vars['StopDate']);
					_defaultStopDate = _vars['StopDate'];
					_defaultAsOfDate = _vars['EffectiveDate'];
					
					break;
				}
				
				case _self.MOD:
				{								
					var obj = this.getSelectedAcctAssc();
					if (obj)
					{								
						if (obj.accountNum != _self.BLANK)
						{
							_self.setSuggestValue(_accountSearchView , obj.accountNum, null, null, "accountNum");
						}
						else
						{
							_resources.fields['accountNum'].setValue(_self.BLANK);
						}
						
						if (obj.holdingEntCode != _self.BLANK)
						{
							_self.setSuggestValue(_holdCompSearchView ,obj.holdingEntCode, null, null, "holdComp");
						}
						else
						{
							_resources.fields['holdComp'].setValue(_self.BLANK);
						}
						
						if (obj.feeModelCode != _self.BLANK)
						{
							_self.setSuggestValue(_feeModelSearchView , obj.feeModelCode, "searchHoldCompany", obj.holdingEntCode, "feeModelCode");
						}
						else
						{
							_resources.fields['feeModelCode'].setValue(_self.BLANK);
						}
						
						if (obj.invInstrId != _self.BLANK)
						{
							_self.setSuggestValue(_invInstrSearchView , obj.invInstrId, "holdingEntityCode", obj.holdingEntCode, "invInstr");
						}
						else
						{
							_resources.fields['invInstr'].setValue(_self.BLANK);
						}
						
						if (obj.rptGrpId != _self.BLANK)
						{
							_self.setSuggestValue(_rptGrpSearchView , obj.rptGrpId, "holdingEntityCode", obj.holdingEntCode, "rptGrp");
						}
						else
						{
							_resources.fields['rptGrp'].setValue(_self.BLANK);
						}
						
						_resources.fields['feeModelType'].setValue(obj.feeModelType);
						_resources.fields['feeModelDesc'].setValue(obj.feeModelDesc);						
						_resources.fields['effectiveDate'].setValue(obj.effectiveDate);
						_resources.fields['stopDate'].setValue(obj.stopDate);						
						_defaultStopDate = obj.stopDate;
						_defaultAsOfDate = obj.effectiveDate;
					}
					break;
				}
				
				case _self.DEL:
				{
					/* Populate warning message do delete */
					
					break;
				}
				
				case _self.VEW:
				{
					var obj = this.getSelectedAcctAssc();
					if (obj)
					{								
						if (obj.accountNum != _self.BLANK)
						{
							_self.setSuggestValue(_accountSearchView , obj.accountNum, null, null, "accountNum");
						}
						else
						{
							_resources.fields['accountNum'].setValue(_self.BLANK);
						}
						
						if (obj.holdingEntCode != _self.BLANK)
						{
							_self.setSuggestValue(_holdCompSearchView , obj.holdingEntCode, null, null, "holdComp");
						}
						else
						{
							_resources.fields['holdComp'].setValue(_self.BLANK);
						}
						
						if (obj.feeModelCode != _self.BLANK)
						{
							_self.setSuggestValue(_feeModelSearchView , obj.feeModelCode, "searchHoldCompany", obj.holdingEntCode, "feeModelCode");
						}
						else
						{
							_resources.fields['feeModelCode'].setValue(_self.BLANK);
						}
						
						if (obj.invInstrId != _self.BLANK)
						{
							_self.setSuggestValue(_invInstrSearchView , obj.invInstrId, "holdingCompanyCode", obj.holdingEntCode, "invInstr");
						}
						else
						{
							_resources.fields['invInstr'].setValue(_self.BLANK);
						}
						
						if (obj.rptGrpId != _self.BLANK)
						{
							_self.setSuggestValue(_rptGrpSearchView , obj.rptGrpId, "holdingEntityCode", obj.holdingEntCode, "rptGrp");
						}
						else
						{
							_resources.fields['rptGrp'].setValue(_self.BLANK);
						}
						
						_resources.fields['feeModelType'].setValue(obj.feeModelType);
						_resources.fields['feeModelDesc'].setValue(obj.feeModelDesc);						
						_resources.fields['effectiveDate'].setValue(obj.effectiveDate);
						_resources.fields['stopDate'].setValue(obj.stopDate);
						_defaultStopDate = obj.stopDate;
						_defaultAsOfDate = obj.effectiveDate;
					}
					break;
				}
			}			
		}				
		
		, displayFields: function (action)
		{
			if (!_vars["HoldCompApp"])
			{
				_resources.fields['holdComp'].hide();
			}
			else
			{
				_resources.fields['holdComp'].show();
			}

			if (!_vars["InvInstrApp"])
			{
				_resources.fields['invInstr'].hide();
			}
			else
			{
				_resources.fields['invInstr'].show();
			}
			
			if (!_vars["RptGrpApp"])
			{
				_resources.fields['rptGrp'].hide();
			}
			else
			{
				_resources.fields['rptGrp'].show();
			}
		}
		
		, enableFields: function(action)
		{						
			var obj = this.getSelectedAcctAssc();
			if (obj && obj.gridIndex.indexOf("NEWASSC") > -1)		
			{
				action = _self.ADD;
				_vars["mode"] = _self.ADD;
			}
			
			switch (action)
			{
				case _self.ADD:
				{	
					if (_vars["FromScreen"] == _ACCOUNT)
					{
						_resources.fields['accountNum'].disable();
					}
					else
					{
						_resources.fields['accountNum'].enable();
					}
					
					if (_vars["FromScreen"] == _ACCOUNT || _vars["FromScreen"] == _MENU)
					{
						_resources.fields['feeModelType'].enable();
					}
					else
					{
						_resources.fields['feeModelType'].disable();
					}
					_self.selectFeeModelType(_resources.fields['feeModelType'].getValue(), _self.getMode());
					
					if (_vars["FromScreen"] == _INVINSTR || _vars["FromScreen"] == _RPTGRP || _vars["FromScreen"] == _ACCOUNT || _vars['FromScreen'] == _MENU)
					{
						_resources.fields['invInstr'].disable();
						_resources.fields['rptGrp'].disable();
					}
										
					if (_vars["AllowNewFeeModel"])
					{
						if (_vars["FromScreen"] == _FEEMODEL)
						{
							_resources.fields['feeModelAddExistCode'].disable();
						}
						else
						{
							_resources.fields['feeModelAddExistCode'].enable();						
						}
						
						Ext.getCmp('feeModelExist').hide();	
						Ext.getCmp('feeModelAdd').show();

						_resources.fields['optExistFeeModel'].setValue(true);
						_resources.fields['optNewFeeModel'].setValue(false);											
						
						_self.doOptCheck();
						
						_resources.fields['effectiveDate'].enable();
						_resources.fields['stopDate'].enable();
					}
					else
					{
						if (_vars["FromScreen"] == _FEEMODEL)
						{
							_resources.fields['feeModelCode'].disable();
						}
						else
						{
							_resources.fields['feeModelCode'].enable();
						}
						_resources.fields['feeModelDesc'].disable();
						
						Ext.getCmp('feeModelExist').show();	
						Ext.getCmp('feeModelAdd').hide();							
					}
					
					_resources.fields['effectiveDate'].enable();
					_resources.fields['stopDate'].enable();
					
					break;
				}
				case _self.MOD:
				{	
					Ext.getCmp('feeModelExist').show();	
					Ext.getCmp('feeModelAdd').hide();		
					_resources.fields['accountNum'].disable()
					_resources.fields['feeModelType'].disable();
					_resources.fields['feeModelCode'].disable();
					_resources.fields['feeModelDesc'].disable();
					_resources.fields['invInstr'].disable();
					_resources.fields['rptGrp'].disable();
					
					if (obj.modDelPerm.toLowerCase() == _self.NO)
					{
						_resources.fields['effectiveDate'].disable();
					}
					else
					{
						_resources.fields['effectiveDate'].enable();
					}
					_resources.fields['stopDate'].enable();
					
					break;
				}
				case _self.DEL:
				{
					/* Populate warning message do delete */
					break;
				}
				case _self.VEW:
				{
					Ext.getCmp('feeModelExist').show();	
					Ext.getCmp('feeModelAdd').hide();		
					_resources.fields['accountNum'].disable();
					_resources.fields['feeModelType'].disable();
					_resources.fields['feeModelCode'].disable();
					_resources.fields['feeModelDesc'].disable();
					_resources.fields['effectiveDate'].disable();
					_resources.fields['stopDate'].disable();					
					_resources.fields['invInstr'].disable();
					_resources.fields['rptGrp'].disable();					
					break;
				}
			}	
		}
		
		, isNewFeeModel: function()
		{
			return _resources.fields['optNewFeeModel'].getValue();
		}
		
		, doSrchCheck: function ()
		{
			if (_resources.fields['optSelectAll'].getValue())
			{
				_resources.fields['asOfDate'].disable();
			}
			else
			{
				_resources.fields['asOfDate'].enable();
			}
		}

		, doOptCheck: function ()
		{					
			if (_self.isNewFeeModel())
			{
				_resources.fields['feeModelAddExistCode'].hide();
				_resources.fields['feeModelAddNewCode'].show();				
				if (_vars['AutoGenFeeModelCode'])
				{
					_resources.fields['feeModelAddNewCode'].disable();
					_resources.fields['feeModelAddNewCode'].setValue(_self.BLANK);
				}
				else
				{
					_resources.fields['feeModelAddNewCode'].enable();
					_resources.fields['feeModelAddNewCode'].setValue(_self.BLANK);
				}
				_resources.fields['feeModelAddDesc'].enable();
				_resources.fields['feeModelAddDesc'].setValue(_self.BLANK);
			}
			else
			{
				_resources.fields['feeModelAddExistCode'].show();
				_resources.fields['feeModelAddNewCode'].hide();
				_resources.fields['feeModelAddExistCode'].enable();
				_resources.fields['feeModelAddNewCode'].setValue(_self.BLANK);
				_resources.fields['feeModelAddDesc'].disable();
			}
		}
		
		, enableSearch: function()
		{
			/*
			if (_vars['CurrentSearch'] != _resources.fields['searchBy'].getValue())
			{
				_resources.buttons['cmdSearch'].enable();	
			}
			else
			{
				_resources.buttons['cmdSearch'].disable();	
			}*/
		}
		
		, populateFeeDesc: function(panel)
		{
			if (panel != 'feeModelExist')
			{
				if (_resources.fields['feeModelAddExistCode'].selectedRecord != null)
				{
					_resources.fields['feeModelAddDesc'].setValue(_resources.fields['feeModelAddExistCode'].selectedRecord.get('feeModelDesc'));
				}
				else
				{
					_resources.fields['feeModelAddDesc'].setValue(_self.BLANK);
				}
			}
			else
			{
				if (_resources.fields['feeModelCode'].selectedRecord != null)
				{
					_resources.fields['feeModelDesc'].setValue(_resources.fields['feeModelCode'].selectedRecord.get('feeModelDesc'));
				}
				else
				{
					_resources.fields['feeModelDesc'].setValue(_self.BLANK);
				}
			}
		}
		
		, populateHoldComp: function(vFrom)
		{
			if (vFrom == 'feeModelAdd')
			{
				if (_resources.fields['feeModelAddExistCode'].selectedRecord != null && _resources.fields['feeModelAddExistCode'].selectedRecord.get('holdingEntityCode') != "")
				{
					if (_resources.fields['holdComp'].selectedRecord != null)
					{
						if (_resources.fields['feeModelAddExistCode'].selectedRecord.get('holdingEntityCode') != 
							_resources.fields['holdComp'].selectedRecord.get('holdingCompanyCode'))
						{
							_resources.fields['invInstr'].setValue(_self.BLANK);
							_resources.fields['rptGrp'].setValue(_self.BLANK);
						}
					}
					
					if (_resources.fields['feeModelAddExistCode'].selectedRecord.get('holdingEntityCode') != "")
					{
						_self.setSuggestValue(_holdCompSearchView , _resources.fields['feeModelAddExistCode'].selectedRecord.get('holdingEntityCode'), null, null, "holdComp");
					}
					else
					{
						_resources.fields['holdComp'].setValue(_self.BLANK);
					}
				}
				else
				{
					_resources.fields['holdComp'].setValue(_self.BLANK);
				}
			}
			
			if (vFrom == 'feeModelExist' || vFrom == _FEEMODEL)
			{
				if (_resources.fields['feeModelCode'].selectedRecord != null && _resources.fields['feeModelCode'].selectedRecord.get('holdingEntityCode') != "")
				{
					if (_resources.fields['holdComp'].selectedRecord != null)
					{
						if (_resources.fields['feeModelCode'].selectedRecord.get('holdingEntityCode') != 
							_resources.fields['holdComp'].selectedRecord.get('holdingCompanyCode'))
						{
							_resources.fields['invInstr'].setValue(_self.BLANK);
							_resources.fields['rptGrp'].setValue(_self.BLANK);
						}
					}
					
					if (_resources.fields['feeModelCode'].selectedRecord.get('holdingEntityCode') != "")
					{
						_self.setSuggestValue(_holdCompSearchView , _resources.fields['feeModelCode'].selectedRecord.get('holdingEntityCode'), null, null, "holdComp");
					}
					else
					{
						_resources.fields['holdComp'].setValue(_self.BLANK);
					}
				}
				else
				{
					_resources.fields['holdComp'].setValue(_self.BLANK);
				}
			}
			
			if (vFrom == _INVINSTR)
			{
				if (_resources.fields['invInstr'].selectedRecord != null)
				{					
					if (_resources.fields['invInstr'].selectedRecord.get('holdingEntityCode') != "")
					{
						_self.setSuggestValue(_holdCompSearchView , _resources.fields['invInstr'].selectedRecord.get('holdingEntityCode'), null, null, "holdComp");
					}
					else
					{
						_resources.fields['holdComp'].setValue(_self.BLANK);
					}
				}
				else
				{
					_resources.fields['holdComp'].setValue(_self.BLANK);
				}
			}
			
			if (vFrom == _RPTGRP)
			{
				if (_resources.fields['rptGrp'].selectedRecord != null)
				{
					if (_resources.fields['rptGrp'].selectedRecord.get('holdingEntityCode') != "")
					{
						_self.setSuggestValue(_holdCompSearchView , _resources.fields['rptGrp'].selectedRecord.get('holdingEntityCode'), null, null, "holdComp");
					}
					else
					{
						_resources.fields['holdComp'].setValue(_self.BLANK);
					}
				}	
				else
				{
					_resources.fields['holdComp'].setValue(_self.BLANK);
				}				
			}

			if (vFrom == _HOLDCOMP)
			{
				_self.setSuggestValue(_holdCompSearchView , _vars['HoldCompCode'], null, null, "holdComp");
			}		
		}
		
		, getAccountNameByNumber: function(accountNum)
		{
			return findAccountName(accountNum, null);
		}
		
		, getAccountNameBySearch: function(displayValue)
		{
			return findAccountName(null, displayValue);
		}
		
		, accessAcctDetail: function()
		{
			var obj;
			if(_self.updatesFlag)
			{
				DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg);
				function handlePromptMsg(btn){
					if(btn){
						obj = _self.getSelectedAcctAssc();
						if (obj)
						{
							document.getElementById('btnAcctDetail').click();
						}
					}
				}
			}
			else
			{
				obj = _self.getSelectedAcctAssc();
				if (obj)
				{
					document.getElementById('btnAcctDetail').click();
				}	
			}
		}
		
		, getAccountNum: function()
		{
			var obj = _self.getSelectedAcctAssc();
			if (obj)
			{												
				return obj.accountNum;
			}
			else
			{			
				return "0";
			}
		}
		
		, clearGrdAcctAssc: function()
		{
			_resources.grids['grdAcctAssc'].clearData();		
			_self.enablePermButtons();	
		}

		,doParseDate: function(pCtrlType)
		{
			var pattern = /^(\d{2})[\/](\d{2})[\/](\d{4})$/;
			switch(pCtrlType)
			{
				case 'asOfDate':
				{
					if(pattern.test(_resources.fields['asOfDate'].getRawValue())) {     
						_resources.fields['asOfDate'].setValue(_defaultAsOfDate);
					}
					break;
				}
				case 'stopDate':
				{
					if(pattern.test(_resources.fields['stopDate'].getRawValue())) {     
						_resources.fields['stopDate'].setValue(_defaultStopDate);
					}
					break
				}
				case 'effectiveDate':
				{
					if(pattern.test(_resources.fields['effectiveDate'].getRawValue())) {     
						_resources.fields['effectiveDate'].setValue(_defaultAsOfDate);
					}
					break
				}
			}
		}
		
		, openAdminPopup: function()
		{					
			var title = null;	
			var obj = this.getSelectedAcctAssc();			
			var adminData = {};
			adminData['userName'] = obj.userName; 
			adminData['procDate'] = obj.procDate; 
			adminData['modUser'] = obj.modUser;  
			adminData['modDate'] = obj.modDate; 
			title = "Account Association - Admin";	
			_resources.popups['frmAdmin'].init(title, adminData);
			_resources.popups['frmAdmin'].show();			
		}
		
		, openHistoryPopup: function()
		{
			var title = null;
			var viewParam = {};
			viewParam['auditType'] = 'ShrAcctFeeConfig';
			viewParam['searchValue1'] = this.getSelectedAcctAssc().shrAcctFeeId;
			title = 'Account Association - History';			
			_resources.popups['frmHistory'].init(title, _historyView, viewParam, true);
			_resources.popups['frmHistory'].show();		
		}
		
		, saveSearchValue: function()
		{
			_vars['CurrentSearch'] = _resources.fields['searchBy'].getValue();
			if (_resources.fields['accountNumSrch'].selectedRecord != null)
			{
				_vars['AccountNum'] = _resources.fields['accountNumSrch'].selectedRecord.get('acctNum');
			}
			if (_resources.fields['holdCompSrch'].selectedRecord != null)
			{
				_vars['HoldCompCode'] = _resources.fields['holdCompSrch'].selectedRecord.get('holdingCompanyCode');
			}
			if (_resources.fields['feeModelSrch'].selectedRecord != null)
			{
				_vars['FeeModelCode'] = _resources.fields['feeModelSrch'].selectedRecord.get('feeModelCode');
				_vars['HoldCompCode'] = _resources.fields['feeModelSrch'].selectedRecord.get('holdingEntityCode');
			}
			if (_resources.fields['invInstrSrch'].selectedRecord != null)
			{
				_vars['InvInstrCode'] = _resources.fields['invInstrSrch'].selectedRecord.get('billInstrCode');
				_vars['HoldCompCode'] = _resources.fields['invInstrSrch'].selectedRecord.get('holdingEntityCode');
			}
			if (_resources.fields['rptGrpSrch'].selectedRecord != null)
			{
				_vars['RptGrpId'] = _resources.fields['rptGrpSrch'].selectedRecord.get('reportGroupID');
				_vars['HoldCompCode'] = _resources.fields['rptGrpSrch'].selectedRecord.get('holdingEntityCode');
			}
		}
	
		, enableSearchField: function(fromMenu)
		{
			if (fromMenu)
			{
				_resources.fields['searchBy'].enable();
				_resources.fields['accountNumSrch'].enable();
				_resources.fields['feeModelSrch'].enable();
				_resources.fields['holdCompSrch'].enable();
				_resources.fields['invInstrSrch'].enable();
				_resources.fields['rptGrpSrch'].enable();
				_resources.buttons['cmdSearch'].enable();	
			}
			else 
			{
				_resources.fields['searchBy'].disable();
				_resources.fields['accountNumSrch'].disable();
				_resources.fields['feeModelSrch'].disable();
				_resources.fields['holdCompSrch'].disable();
				_resources.fields['invInstrSrch'].disable();
				_resources.fields['rptGrpSrch'].disable();
				_resources.buttons['cmdSearch'].disable();					
			}
		}
	
		, populateSearchField: function(searchField)
		{
			_resources.fields['searchBy'].setValue(searchField);
			switch(searchField)
			{
				case _ACCOUNT:
				{
					_resources.fields['accountNumSrch'].show();
					_resources.fields['feeModelSrch'].hide();
					_resources.fields['holdCompSrch'].hide();
					_resources.fields['invInstrSrch'].hide();
					_resources.fields['rptGrpSrch'].hide();
					break;
				}
				case _HOLDCOMP:
				{
					_resources.fields['accountNumSrch'].hide();
					_resources.fields['feeModelSrch'].hide();
					_resources.fields['holdCompSrch'].show();
					_resources.fields['invInstrSrch'].hide();
					_resources.fields['rptGrpSrch'].hide();
					break;
				}
				case _FEEMODEL:
				{
					_resources.fields['accountNumSrch'].hide();
					_resources.fields['feeModelSrch'].show();
					_resources.fields['holdCompSrch'].hide();
					_resources.fields['invInstrSrch'].hide();
					_resources.fields['rptGrpSrch'].hide();
					break;
				}				
				case _INVINSTR:
				{
					_resources.fields['accountNumSrch'].hide();
					_resources.fields['feeModelSrch'].hide();
					_resources.fields['holdCompSrch'].hide();
					_resources.fields['invInstrSrch'].show();
					_resources.fields['rptGrpSrch'].hide();
					break;
				}
				case _RPTGRP:
				{
					_resources.fields['accountNumSrch'].hide();
					_resources.fields['feeModelSrch'].hide();
					_resources.fields['holdCompSrch'].hide();
					_resources.fields['invInstrSrch'].hide();
					_resources.fields['rptGrpSrch'].show();
					break;
				}
				default:
				{
					_resources.fields['accountNumSrch'].show();
					_resources.fields['feeModelSrch'].hide();
					_resources.fields['holdCompSrch'].hide();
					_resources.fields['invInstrSrch'].hide();
					_resources.fields['rptGrpSrch'].hide();
					break;
				}
			}			
		}
		
		, setSuggestValue: function(smartview, searchValue, searchHoldCompField, searchHoldCompValue, field, callBackfn, flag)
		{		
			if (searchValue != _self.BLANK)
			{
				var xml = IFDS.Xml.newDocument('data');			
				IFDS.Xml.addSingleNode(xml, 'searchValue', searchValue);
				
				if (searchHoldCompValue != null)
				{
					IFDS.Xml.addSingleNode(xml, searchHoldCompField, searchHoldCompValue);
				}
				
				if (field == "accountNum" || field == "accountNumSrch")
				{
					IFDS.Xml.addSingleNode(xml, 'incAllStat', 'yes');
				}
				
				IFDS.Xml.addSingleNode(xml, 'startRecordNum', '1');
				IFDS.Xml.addSingleNode(xml, 'maxRecords', 1);
				IFDS.Xml.addSingleNode(xml, 'requestRecNum', 1);
				
				
				DesktopWeb.Ajax.doSmartviewAjax(smartview, {ignoreErrorCode: '199'}, xml, responseHandler, "");			

				function responseHandler(success, responseXML)
				{
					if (success)
					{						
						_resources.fields[field].getStore().loadData(IFDS.Xml.getNode(responseXML, '/*//PossibleMatches'));
						_resources.fields[field].setValue(IFDS.Xml.getNodeValue(responseXML, '/*//displayValue'));
												
						if (field == "feeModelSrch" || field == "feeModelAddExistCode" || field == "feeModelCode")
						{
							if (_resources.fields[field].selectedRecord != null)
							{
								if (_resources.fields[field].selectedRecord.get("feeModelType") != null)
								{
									_vars["FeeModelType"] = _resources.fields[field].selectedRecord.get("feeModelType"); 
									//_resources.field['feeModelType'].setValue(_resources.fields[field].selectedRecord.get("feeModelType"));
								}
								else
								{
									_vars["FeeModelType"] = _self.BLANK;
									//_resources.field['feeModelType'].setValue(_self.BLANK);
								}
								
								if (_resources.fields[field].selectedRecord.get("holdingEntityCode") != null)
								{
									_vars["HoldCompCode"] = _resources.fields[field].selectedRecord.get("holdingEntityCode"); 
									//_self.setSuggestValue(_holdCompSearchView ,_resources.fields[field].selectedRecord.get("holdingEntityCode"), null, null, "holdComp");
								}
								else
								{
									_vars["HoldCompCode"] = _self.BLANK;
									//_resources.field['holdComp'].setValue(_self.BLANK);
								}
							}
						}
						
						if (field == "holdCompSrch" || field == "holdComp")
						{
							if (_resources.fields[field].selectedRecord != null)
							{
								if (_resources.fields[field].selectedRecord.get("coUsage") != null)
								{
									_vars["FeeModelType"] = _resources.fields[field].selectedRecord.get("coUsage"); 
								}
								else
								{
									_vars["FeeModelType"] = _self.BLANK;
								}
							}
						}
						
						if (field == "invInstr" || field == "invInstrSrch" || field == "rptGrp" || field == "rptGrpSrch")
						{
					
							if (_resources.fields[field].selectedRecord != null)
							{
								if (_resources.fields[field].selectedRecord.get("holdingEntityCode") != null)
								{								
									_vars["HoldCompCode"] = _resources.fields[field].selectedRecord.get("holdingEntityCode"); 
									if (field == "invInstr")
									{
										_self.populateHoldComp(_INVINSTR);
									}
									
									if (field == "rptGrp")
									{
										_self.populateHoldComp(_RPTGRP);										
									}
								}
							}
						}
						
						if (field == "accountNumSrch" || field == "accountNum")
						{
							if (_resources.fields[field].selectedRecord != null)
							{
								if (_resources.fields[field].selectedRecord.get("displayValue") != null)
								{
									_vars["AccountName"] = _self.getAccountNameBySearch(_resources.fields[field].selectedRecord.get("displayValue"));
								}
							}
						}
						
						if (callBackfn && callBackfn != undefined)
							callBackfn(flag);
					} //success
					else if (callBackfn && callBackfn != undefined)
							callBackfn(flag);
					
				}	
			} //if (searchValue != _self.BLANK)
			else if (callBackfn && callBackfn != undefined)
				callBackfn(flag);
		}

		, allowNewFeeModel: function()
		{
			return _vars['AllowNewFeeModel'];
		}
		
		, selectFeeModelType: function(value, action)
		{
			if (_vars["FromScreen"] == _INVINSTR || _vars["FromScreen"] == _RPTGRP)
			{
				_resources.fields['invInstr'].disable();
				_resources.fields['rptGrp'].disable();
			}
			else
			{				
				if (value == _self.DF)
				{
					if (_self.isHoldCompAppl(value).toLowerCase() == _self.NO)
					{
						_resources.fields['holdComp'].hide();
						_resources.fields['invInstr'].hide();
						_resources.fields['rptGrp'].hide();
					} 
					else
					{
						_resources.fields['holdComp'].show();
						_resources.fields['invInstr'].show();
						_resources.fields['rptGrp'].show();
					}
				}
				if (value == _self.MF)
				{
					if (_self.isHoldCompAppl(value).toLowerCase() == _self.NO)
					{
						_resources.fields['holdComp'].hide();
					}
					else 
					{
						_resources.fields['holdComp'].show();
					}
					if ((_vars['InvInstrApp'] || _vars['InvInstrApp'] != _self.BLANK) && action == _self.ADD)
					{
						_resources.fields['invInstr'].enable();
					}
					else
					{
						_resources.fields['invInstr'].disable();
					}
					_resources.fields['rptGrp'].disable();
					_resources.fields['rptGrp'].setValue(_self.BLANK);
				}
				if (value == _self.MFR)
				{
					if (_self.isHoldCompAppl(value).toLowerCase() == _self.NO)
					{
						_resources.fields['holdComp'].hide();
					}
					else 
					{
						_resources.fields['holdComp'].show();
					}
					if ((_vars['RptGrpApp'] || _vars['RptGrpApp'] != _self.BLANK) && action == _self.ADD) 
					{
						_resources.fields['rptGrp'].enable();
					}
					else
					{
						_resources.fields['rptGrp'].disable();
					}
					_resources.fields['invInstr'].disable();
					_resources.fields['invInstr'].setValue(_self.BLANK);
				}
			}
		}
		
		, doDelete: function()
		{	
			var obj = this.getSelectedAcctAssc();
			
			if (obj) 
			{
				DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, getValidateDelete(obj), responseHandler, _translationMap['Validating'], Ext.Msg.OKCANCEL);			

				function responseHandler(success, responseXML, contextErrors, warnings, btn)
				{
					if (success)
					{
						if (btn == null || btn == 'ok')
							_self.doSave(_self.DEL, null);
					}
				}
			} 
		}
		
		, hideColumns: function()
		{
			if (!_vars["HoldCompApp"])
			{
				_resources.grids['grdAcctAssc'].hideColumn (1);
			}
			
			if (!_vars["InvInstrApp"])
			{
				_resources.grids['grdAcctAssc'].hideColumn (7);
			}
			
			if (!_vars["RptGrpApp"])
			{
				_resources.grids['grdAcctAssc'].hideColumn (8);
			}
		}
		
		, doBackToScr: function()
		{
			var backToScr = '';
			if (_vars['FromScreen'] == _INVINSTR || _vars['FromScreen'] == _RPTGRP)
			{
				backToScr = _vars['FromScreen']
			}			
			return backToScr;
		}
		
		, toScreen: function(screen)
		{
			goToScreen(screen);
		}
		
		, getHoldComp: function()
		{
			if (_resources.fields['holdComp'].selectedRecord != null && _resources.fields['holdComp'].getRawValue() != "")
			{
				return _resources.fields['holdComp'].selectedRecord.get('holdingCompanyCode');
			}
			else
			{
				return _self.BLANK;
			}
		}		
		
		, getFeeModelType: function()
		{
			var feeModelType = "";
			switch (_vars['FromScreen'])
			{
				case _INVINSTR:
				{
					feeModelType = _self.MF;
					break;
				}
				case _RPTGRP:
				{
					feeModelType = _self.MFR;
					break;
				}
				case _HOLDCOMP:
				{
					if (_resources.fields['holdComp'].selectedRecord != null)
					{
						if (_resources.fields['holdComp'].selectedRecord.get('coUsage') == _self.MF ||
								_resources.fields['holdComp'].selectedRecord.get('coUsage') == _self.MFR ) 
						{
							feeModelType = _resources.fields['holdComp'].selectedRecord.get('coUsage');
						}
					} 
					feeModelType = _vars['FeeModelType'];
					break;
				}
				case _FEEMODEL:
				{
					if (_resources.fields['feeModelAddExistCode'].selectedRecord != null)
					{
						if (_resources.fields['feeModelAddExistCode'].selectedRecord.get('feeModelType') == _self.MF ||
								_resources.fields['feeModelAddExistCode'].selectedRecord.get('feeModelType') == _self.MFR ) 
						{
							feeModelType = _resources.fields['feeModelAddExistCode'].selectedRecord.get('feeModelType');
						}
					}
					if (_resources.fields['feeModelCode'].selectedRecord != null)
					{
						if (_resources.fields['feeModelCode'].selectedRecord.get('feeModelType') == _self.MF ||
								_resources.fields['feeModelCode'].selectedRecord.get('feeModelType') == _self.MFR ) 
						{
							feeModelType = _resources.fields['feeModelCode'].selectedRecord.get('feeModelType');
						}
					}
					feeModelType = _vars['FeeModelType'];
					break;
				}
				case _MENU:
				{
					feeModelType = "";
					break;
				}
			}
			
			return feeModelType;
		}
		
		, populateFeeModelType: function (from)
		{
			if (from == 'feeModelAdd')
			{
				if (_resources.fields['feeModelAddExistCode'].selectedRecord != null)
				{
					if (_resources.fields['feeModelAddExistCode'].selectedRecord.get('feeModelType') != "")
					{
						_resources.fields['feeModelType'].setValue(_resources.fields['feeModelAddExistCode'].selectedRecord.get('feeModelType'));
					}
				}
			}	
			
			if (from == 'feeModelExist')
			{
				if (_resources.fields['feeModelCode'].selectedRecord != null)
				{
					if (_resources.fields['feeModelCode'].selectedRecord.get('feeModelType') != "")
					{
						_resources.fields['feeModelType'].setValue(_resources.fields['feeModelCode'].selectedRecord.get('feeModelType'));
					}
				}
			}
			
			_self.selectFeeModelType(_resources.fields['feeModelType'].getValue(), _self.getMode());
		}
		
		, isHoldCompSolid: function ()
		{
			if (_vars["FromScreen"] == _HOLDCOMP || _vars["FromScreen"] == _FEEMODEL || _vars["FromScreen"] == _INVINSTR || _vars["FromScreen"] == _RPTGRP)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		, getMode: function()
		{
			return _vars['mode'];
		}
		
		, isHoldCompAppl: function(feeModelType)
		{
			var retVal;
			var elmXMLArr = IFDS.Xml.getNodes(_listXMLs["FeeModelTypeOptions"], "Element");		
			Ext.each(elmXMLArr, function(elmXML){				
				if (IFDS.Xml.getNodeValue(elmXML, "code") == feeModelType)
				{
					retVal = IFDS.Xml.getNodeValue(elmXML, "holdingEntityAppl");
				}
			});
			return retVal;
		}
	}	
}	
