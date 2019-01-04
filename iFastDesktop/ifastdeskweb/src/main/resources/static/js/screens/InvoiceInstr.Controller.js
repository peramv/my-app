/*
 * Procedure: InvoiceInstr.Controller.js
 *
 * Purpose  : Invoice Instruction screens manage invoice information data		  
 *             
 * Notes    : Open screens by Menu -> MF and MFR Maintenance -> Invoice Instruction
 *							  Menu -> System Maintenance -> Holding Company -> Invoice Instructions
 *
 * History  : 
 *	
 *		5 Mar 2013 Supareuk Sukjaitham PETP0206635 FN01 MFR MFI Enhancments
 *			- Created
 *
 *		2 May 2013 Supareuk Sukjaitham PETP0206635 FN01 IN3318278
 *			- Fixed issues for some validation of mandatory field, pre-populated field and error of compositefield
 *
 *		15 May 2013 Supareuk Sukjaitham PETP0206635 FN01 IN3328724
 *			- Corrected logic to suggest and pre-populated holding and invoice id
 *          - Display updated holding and invoice id when user submitted pop-up screen
 *
 *	    21 May 2013 Supareuk Sukjaitham PETP0206635 FN01 IN3331655
 *	        - Ignore error 15 - Nodata found
 *          - Trim invoice name before concatenate between name 1 and 2
 *
 *	    27 May 2013 Supareuk Sukjaitham PETP0206635 FN01 T53618 IN3336672
 *			- Reset flag updatesFlag after discarding the changes on doSearch
 *			- Enable Account List for submitting Invoice record
 *			- Create and send new runMode (validate or update)
 *			- Create doValidateCommitScreen function to call CommitScreen
 *			- Display warning message when changing both Effective and Stop date
 *			- Change assignment of delete permission (delPerm)
 *
 *		13 Jun 2013 Pannarasi Wongpakdee PETP0206635 FN01 T53714 IN3346061
 *          - Display message dialog (Error_WarningChangedDate) before closing popup screen
 *          - Remove assignment logic of master XML to support more functionality
 *
 *		05 Aug 2013 Gomoot Thawornwachirakun PETP0206635 FN01 DFT0012847 T53963
 *          - Add ability to set dynamic mandatory PSTL field on selected country
 *          - Remove allowBlank from PSTL field
 *
 *    11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *		24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *			- Fixed screens don't response when user's profile has too many slots attached. 
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;

	var _inqView = 'dtInvoiceInstrInq';
	var _updView = 'dtInvoiceInstrUpd';
	var _historyService = 'dtHistoricalInfo';
	var _invoiceInstrCounter = 0;
	
	var _permissionsMap = {};
	var _mstrXML = null;
	var _inqInvoiceInstrXML = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	var _nextStartRecNum = null;
	var _requestRecNum = 25;
	
	var _listXMLs = {};
	var _vars = {};
	// PRIVATE METHODS ****************************************	
	// Operate on XMLs
	
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/inqPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/addPerm').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/modPerm').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '/*//Permissions/delPerm').toLowerCase() == 'yes';
	}
	
	function storeDefaultValues(xml)
	{
		_vars['DefalutHoldingCode'] = IFDS.Xml.getNodeValue(xml, '//holdingEntityDisp/holdingEntityCode');
		_vars['DefalutHoldingDesc'] = IFDS.Xml.getNodeValue(xml, '//holdingEntityDisp/holdingEntityDesc');
		_vars['DefalutHoldingDisp'] = IFDS.Xml.getNodeValue(xml, '//holdingEntityDisp/holdingEntityDisplay');
		
		_vars['DefalutEffectiveDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DefaultValues/asOfDate'));
		_vars['DefalutDeff'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DefaultValues/deff'));
		_vars['DefaultStopDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//DefaultValues/stopDate'));
		_vars['DefaultProvConuntry'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/provCountry');
		_vars['DefaultFrequency'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/frequency');
		_vars['DefaultChargeOption'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/chargeOption');
		_vars['DefaultTermPymtType'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/termPymtType');
		_vars['DefaultCurrency'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/currency');
		_vars['DefaultLang'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/lang');
		_vars['DefaultBrandingType'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/brandingType');
		_vars['DefaultTaxApplies'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/taxApplies');
		_vars['DefaultSuppInfoReq'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/suppInfoReq');
		_vars['DefaultTermPymt'] = IFDS.Xml.getNodeValue(xml, '//DefaultValues/termPymt');
		
		_resources.grids['grdInvoiceInstr'].disableButton(0);
		_resources.grids['grdInvoiceInstr'].disableButton(1);
		_resources.grids['grdInvoiceInstr'].disableButton(2);
		_resources.grids['grdInvoiceInstr'].disableButton(3);
		_resources.grids['grdInvoiceInstr'].disableButton(4);
		_resources.grids['grdInvoiceInstr'].disableButton(5);
		Ext.getCmp('InvoiceAdj').disable();
		Ext.getCmp('AccountList').disable();
	}
	
	function loadDropdownList(xml){
		_resources.popups['frmInvoiceDetl'].getField('frequencyDetl').loadData(IFDS.Xml.getNode(xml, "//List[@listName = 'frequencies']"));
		_resources.popups['frmInvoiceDetl'].getField('paymentOptnDetl').loadData(IFDS.Xml.getNode(xml, "//List[@listName = 'chargeOptions']"));
		Ext.getCmp('termOfPaymentTypeDetl').loadData(IFDS.Xml.getNode(xml, "//List[@listName = 'termDayTypes']"));
		_resources.popups['frmInvoiceDetl'].getField('currencyDetl').loadData(IFDS.Xml.getNode(xml, "//List[@listName = 'currencyList']"));
		_resources.popups['frmInvoiceDetl'].getField('languageDetl').loadData(IFDS.Xml.getNode(xml, "//List[@listName = 'languages']"));
		_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').loadData(IFDS.Xml.getNode(xml, "//List[@listName = 'brandingTypes']"));
		_resources.popups['frmInvoiceDetl'].getField('countryDetl').loadData(IFDS.Xml.getNode(xml, "//List[@listName = 'provCountries']"));
	}
	
	function createMstrXML(xml, more)
	{	
		if (!_mstrXML || !more){			
			_mstrXML = IFDS.Xml.newDocument("InvoiceInstrDetls");
		}		
		
		var invoiceInstrXML = IFDS.Xml.getNodes(xml, '//InvoiceInstrDetls/InvoiceInstrDetl');
		
		Ext.each(invoiceInstrXML, function(invoiceXML){
			IFDS.Xml.addSingleNode(invoiceXML, 'runMode', _self.INQ);
			IFDS.Xml.addSingleNode(invoiceXML, 'updSeq', _self.SEQINQ);
			IFDS.Xml.addSingleNode(invoiceXML, 'errMsg', '');
			IFDS.Xml.addSingleNode(invoiceXML, 'gridIndex', IFDS.Xml.getNodeValue(invoiceXML, 'billInstrID'));
			IFDS.Xml.appendNode(_mstrXML, invoiceXML);
		});
	}
	
	function getReloadRequest(more)
	{
		var requestXML = IFDS.Xml.newDocument("data");
		var holding = null;
		
		/*** Check Default Code, It should be available if come from HoldingCompany screen ***/
		if (_vars['DefalutHoldingCode'] != null && _vars['DefalutHoldingCode'] != "" && _self.enableholdingFlag == false){
			holding = _vars['DefalutHoldingCode'];
		}else{
			holding = _resources.fields['holdingCompanySrch'].getValue();
		}
		
		IFDS.Xml.addSingleNode(requestXML, "holdingEntityCode", holding);
		IFDS.Xml.addSingleNode(requestXML, "invoiceID", _resources.fields['invoiceSrch'].getValue());
		
		if(_resources.fields['optSelectAsOfDate'].getValue()){
			IFDS.Xml.addSingleNode(requestXML, "asOfDate", _resources.fields['asOfDate'].getSMVDateString());
		}
		
		IFDS.Xml.addSingleNode(requestXML, "runMode", 'reload');
		IFDS.Xml.addSingleNode(requestXML, "startRecNum", (more ? _nextStartRecNum : 1));
		IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);
		
		_self.lastSearchHolding = holding;
		_self.lastSearchInvoice = _resources.fields['invoiceSrch'].getValue();
		_self.lastSearchInvoiceDisp = _resources.fields['invoiceSrch'].getRawValue();
		_self.lastSearchOption = _resources.fields['optSelectAsOfDate'].getValue();
		_self.lastSearchAsOf = _resources.fields['asOfDate'].getDisplayDateString();

		return requestXML;
	}
	
	function getInvoiceInstr(gridIndex){
		var index = 0;		
		var invoiceInstrXMLArr = IFDS.Xml.getNodes(_mstrXML, '//InvoiceInstrDetls/InvoiceInstrDetl');
		for (var i = 0; i < invoiceInstrXMLArr.length; i++){			
			if (IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'gridIndex') == gridIndex){
				return {
					node : invoiceInstrXMLArr[i], 
					index : index,
					runMode : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'runMode'),
					billInstrID : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'billInstrID'),
					holdingEntityCode : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'holdingEntityCode'),
					holdingEntityDesc : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'holdingEntityDesc'),
					deff : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'deff'),
					stopDate : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'stopDate'),
					invoiceID : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'invoiceID'),
					invoiceName : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'invoiceName'),
					invoiceName2 : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'invoiceName2'),
					delivName1 : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'delivName1'),
					delivName2 : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'delivName2'),
					addrLine1 : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'addrLine1'),
					addrLine2 : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'addrLine2'),
					addrLine3 : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'addrLine3'),
					addrLine4 : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'addrLine4'),
					city : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'city'),
					provCountry : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'provCountry'),
					pstl : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'pstl'),
					taxApplies : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'taxApplies'),
					suppInfoReq : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'suppInfoReq'),
					frequency : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'frequency'),
					chargeOption : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'chargeOption'),
					termPymt : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'termPymt'),
					termPymtType : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'termPymtType'),
					currency : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'currency'),
					lang : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'lang'),
					brandingType : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'brandingType'),
					gbcd : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'gbcd'),
					allowDel : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'allowDel'),
					acctAsso : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'acctAsso'),
					userName : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'userName'),
					processDate : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'processDate'),
					modUser : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'modUser'),
					modDate : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'modDate'),
					version : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'version'),
					gridIndex : IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'gridIndex')
				};
			}
			if (IFDS.Xml.getNodeValue(invoiceInstrXMLArr[i], 'runMode') != _self.DEL){
				index += 1;
			}
		}			
	}
	
	function addNewInvoiceInstr(data){
		if (!_mstrXML){			
			_mstrXML = IFDS.Xml.newDocument("InvoiceInstrDetls");
		}		
		_invoiceInstrCounter += 1;
		var newInvoiceInstrXML = IFDS.Xml.newDocument("InvoiceInstrDetl");	
		
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'runMode', _self.ADD);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'updSeq', _self.SEQADD);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'errMsg', '');
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'allowDel', 'yes');
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'acctAsso', 'no');
		
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'billInstrID', 0);
		
		var record = _resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').selectedRecord;
		if (record){
			IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'holdingEntityCode', record.data['holdingCompanyCode']);
			IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'holdingEntityDesc', record.data['holdingCompanyDesc']);
		}
		
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'invoiceID', _resources.popups['frmInvoiceDetl'].getField('invoiceSrchDetl').getValue());
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'invoiceName', data['invoiceName']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'invoiceName2', data['invoiceName2']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'deff', data['deff']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'stopDate', data['stopDate']);
		
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'delivName1', data['delivName1']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'delivName2', data['delivName2']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'addrLine1', data['addrLine1']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'addrLine2', data['addrLine2']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'addrLine3', data['addrLine3']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'addrLine4', data['addrLine4']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'city', data['city']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'provCountry', data['provCountry']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'pstl', data['pstl']);
		
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'frequency', data['frequency']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'chargeOption', data['chargeOption']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'termPymt', data['termPymt']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'termPymtType', data['termPymtType']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'currency', data['currency']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'taxApplies', data['taxApplies']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'lang', data['lang']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'suppInfoReq', data['suppInfoReq']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'brandingType', data['brandingType']);
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'version', 0);
		
		IFDS.Xml.addSingleNode(newInvoiceInstrXML, 'gridIndex', "tmpBillInstrID" + _invoiceInstrCounter);
		IFDS.Xml.appendNode(_mstrXML, newInvoiceInstrXML);
		
		_self.updatesFlag = true;
	}
	
	function updateInvoiceInstr(gridIndex, data)
	{
		var invoiceInstr = getInvoiceInstr(gridIndex);
		
		if (IFDS.Xml.getNodeValue(invoiceInstr.node, 'gridIndex').indexOf("tmpBillInstrID") > -1 == false){
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'runMode'), _self.MOD);
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'updSeq'), _self.SEQMOD);
		}
        else{
			var record = _resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').selectedRecord;
			/*if ((record) && (record.data['holdingCompanyCode'].length > 0 && record.data['holdingCompanyDesc'].length > 0)){*/
			if(record){
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'holdingEntityCode'), record.data['holdingCompanyCode']);
				IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'holdingEntityDesc'), record.data['holdingCompanyDesc']);
			}
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'invoiceID'), data['invoiceID']);
		}
		
		/*** Clear only error record ***/
		if (IFDS.Xml.getNode(invoiceInstr.node, 'errMsg') != null){
			IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'errMsg'), '');
		}
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'deff'), data['deff']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'stopDate'), data['stopDate']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'invoiceName'), data['invoiceName']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'invoiceName2'), data['invoiceName2']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'delivName1'), data['delivName1']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'delivName2'), data['delivName2']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'addrLine1'), data['addrLine1']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'addrLine2'), data['addrLine2']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'addrLine3'), data['addrLine3']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'addrLine4'), data['addrLine4']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'city'), data['city']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'provCountry'), data['provCountry']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'pstl'), data['pstl']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'frequency'), data['frequency']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'chargeOption'), data['chargeOption']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'termPymt'), data['termPymt']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'termPymtType'), data['termPymtType']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'currency'), data['currency']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'taxApplies'), data['taxApplies']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'suppInfoReq'), data['suppInfoReq']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'lang'), data['lang']);
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'brandingType'), data['brandingType']);

		_self.updatesFlag = true;	
		
		return invoiceInstr.index;
	}
	
	function deleteInvoiceInstr(gridIndex)
	{		
		var invoiceInstr = getInvoiceInstr(gridIndex);
		
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'runMode'), _self.DEL);				
		IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'updSeq'), _self.SEQDEL);	
		
		_self.updatesFlag = true;
	}
	
	function getUpdateRequest(mode){
		var requestXML = IFDS.Xml.newDocument("data");
		var xml = IFDS.Xml.newDocument("InvoiceInstrDetls");
		var invoiceInstrXML = IFDS.Xml.getNodes(_mstrXML, '//InvoiceInstrDetls/InvoiceInstrDetl');
		var updInvoiceInstrXML;
		var runMode;
		var newInvoiceInstr;
		
		// New runMode for back-end validation
		if (mode == 'validate'){
			IFDS.Xml.addSingleNode(xml, 'runMode', 'validate');
		}else{
			IFDS.Xml.addSingleNode(xml, 'runMode', 'update');
		}
		
		
		for (var i = 0; i < invoiceInstrXML.length; i++){				
			runMode = IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'runMode');
			
			if (IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'gridIndex').indexOf("tmpBillInstrID") > -1){
				   newInvoiceInstr = true;
			}else{ newInvoiceInstr = false;}
					
			// DISCARD 1) Unchanged record 2) Deletion of new buffer record
			if  (!(newInvoiceInstr && runMode == _self.DEL) && !(runMode == _self.INQ)){
				updInvoiceInstrXML = IFDS.Xml.newDocument("InvoiceInstrDetl");
				
				IFDS.Xml.addAttribute(IFDS.Xml.getNode(updInvoiceInstrXML, "."), 'RecordSource', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'gridIndex'));
				
				if (newInvoiceInstr){
					IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'runMode', _self.ADD);
					IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'updSeq', _self.SEQADD);
				}else{
					IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'runMode', runMode);
					if (runMode == _self.MOD){	
						IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'updSeq', _self.SEQMOD);
					}
					if (runMode == _self.DEL){
						IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'updSeq', _self.SEQDEL);
					}
				}
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'holdingEntityCode', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'holdingEntityCode'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'billInstrID', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'billInstrID'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'invoiceID', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'invoiceID'));				
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'deff', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'deff'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'stopDate', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'stopDate'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'invoiceName', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'invoiceName'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'invoiceName2', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'invoiceName2'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'delivName1', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'delivName1'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'delivName2', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'delivName2'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'addrLine1', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'addrLine1'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'addrLine2', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'addrLine2'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'addrLine3', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'addrLine3'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'addrLine4', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'addrLine4'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'city', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'city'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'provCountry', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'provCountry'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'pstl', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'pstl'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'frequency', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'frequency'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'chargeOption', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'chargeOption'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'termPymt', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'termPymt'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'termPymtType', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'termPymtType'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'currency', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'currency'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'taxApplies', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'taxApplies'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'suppInfoReq', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'suppInfoReq'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'lang', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'lang'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'brandingType', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'brandingType'));
				IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'version', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'version'));
				//IFDS.Xml.addSingleNode(updInvoiceInstrXML, 'gridIndex', IFDS.Xml.getNodeValue(invoiceInstrXML[i], 'gridIndex'));
			
				IFDS.Xml.appendNode(xml, updInvoiceInstrXML);
			}
		}
			
		return IFDS.Xml.appendNode(requestXML, xml);
	}
	
	function goToScreen(screenName,billInstrID,billInstrCode,holdingEntityCode,invoiceID,invoiceDisp,enableholdingFlag,asOfDate,optSelectAsOfDate,rowSelectedIndex)
	{
		var params = {};
		
		this.updatesFlag = false;
		
		params['prevScreen'] = 'InvoiceInstr';//_screenId;		
		params['billInstrID'] = billInstrID;
		
		if (screenName == 'InvoiceAdj' || screenName == 'AcctAssociate'){
			if (screenName == 'AcctAssociate'){
				params['billInstrCode'] = billInstrCode;
				params['from_screen'] = "InvoiceInstr";				
			}
			params['holdingEntityCode'] = holdingEntityCode;
			params['invoiceID'] = invoiceID;
			params['invoiceDisp'] = invoiceDisp;
			params['enableholdingFlag'] = enableholdingFlag;
			params['asOfDate'] = asOfDate;
			params['optSelectAsOfDate'] = optSelectAsOfDate; 
			params['rowSelectedIndex'] = rowSelectedIndex;
		}
		
		if (screenName == "Search"){
			params['createCache'] = 'true';	
		}
		else{
			params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		}
		DesktopWeb.Util.goToScreen(screenName, params);
	}
	
	function storeContextErrors(errorNodes)
	{
		clearContextErrors();
		var firstErrRecIndex = -1;
		for (var i = 0; i < errorNodes.length; i++)
		{
			var invoiceInstrIndex = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');			
			// Update Grid
			var recordIndex = _resources.grids['grdInvoiceInstr'].getStore().find('gridIndex', invoiceInstrIndex);
			var invoiceErrRecord = _resources.grids['grdInvoiceInstr'].getStore().getAt(recordIndex);
			
			if (invoiceErrRecord !== undefined)
			{
				invoiceErrRecord.set('errMsg', errMsg);
				_resources.grids['grdInvoiceInstr'].getStore().commitChanges();
				if(firstErrRecIndex==-1)
					firstErrRecIndex = recordIndex;
			}
		}
			
		if(firstErrRecIndex==-1)
		{
			_resources.grids['grdInvoiceInstr'].getSelectionModel().selectFirstRow();
		}else{
			_resources.grids['grdInvoiceInstr'].getSelectionModel().selectRow(firstErrRecIndex);
			_resources.grids['grdInvoiceInstr'].focusRow(firstErrRecIndex);
		}
		var focusIdx = 0;
		
		for (var i = 0; i < errorNodes.length; i++)
		{		
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			if (table)
			{
				var invoiceInstrGridIndex = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
				var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');			
				
				var invoiceInstr = getInvoiceInstr(invoiceInstrGridIndex);	
				if (!IFDS.Xml.getNode(invoiceInstr.node, 'errMsg'))		
				{				
					IFDS.Xml.addSingleNode(invoiceInstr.node, 'errMsg', errMsg);		
				}
				if (invoiceInstr.runMode == _self.DEL)
				{
					IFDS.Xml.setNodeValue(IFDS.Xml.getNode(invoiceInstr.node, 'runMode'), _self.UNCH);
				}
				if (focusIdx == 0)
				{
					focusIdx = invoiceInstr.index;
				}
			}
		}
				
		_self.refreshGrdInvoiceInstr(focusIdx);	
	}
	
	function clearContextErrors()
	{
		var invoiceInstrXMLArr = IFDS.Xml.getNodes(_mstrXML, '//InvoiceInstrDetls/InvoiceInstrDetl');
		for (var i = 0; i < invoiceInstrXMLArr.length; i++)
		{
			if (IFDS.Xml.getNode(invoiceInstrXMLArr[i], 'errMsg'))		
			{				
				IFDS.Xml.deleteNode(IFDS.Xml.getNode(invoiceInstrXMLArr[i], 'errMsg'));
			}
		}
	}
		
	function loadDefaultHoldingCompanySearch(code, desc, assetAggrMethod, displayValue, isPopup)
	{
		if (code != _self.BLANK)
		{
			var suggestfield = null;
			if (isPopup){
				suggestfield = _resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl');
			}else{
				suggestfield = _resources.fields['holdingCompanySrch'];
			}
			
			var xml = IFDS.Xml.newDocument("data");
			var possibleMatchXML = IFDS.Xml.addSingleNode(IFDS.Xml.addSingleNode(xml, 'PossibleMatches'), 'PossibleMatch');

			suggestfield.prepopulate(code, displayValue);
			suggestfield.prevSearchVal = code;
			
			IFDS.Xml.addSingleNode(possibleMatchXML, 'holdingCompanyCode', code);
			IFDS.Xml.addSingleNode(possibleMatchXML, 'displayValue', displayValue);		
			IFDS.Xml.addSingleNode(possibleMatchXML, 'holdingCompanyDesc', desc);			
			suggestfield.store.loadData(xml);
			suggestfield.setValue(code);	
		}
	}
	
	// PUBLIC ITEMS *************************************
	// Operate on Objects
	return {				
		INQ: 'i'
		,ADD: 'a'
		,DEL: 'd'
		,MOD: 'm'
		,SEQADD: '3'
		,SEQMOD: '2'
		,SEQDEL: '1'
		,SEQINQ: '0'
		,BLANK: ''
		,updatesFlag: false
		,enableholdingFlag: true
		,isFromInvoiceScreen: false
		,lastSearchHolding: ''
		,lastSearchInvoice: ''
		,lastSearchInvoiceDisp: ''
		,lastSearchOption: ''
	    ,lastSearchAsOf: ''
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			var requestXML = IFDS.Xml.newDocument("data");
			var billInstrID = (DesktopWeb._SCREEN_PARAM_MAP['billInstrID'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['billInstrID']:_self.BLANK;
			var holdingCode = (DesktopWeb._SCREEN_PARAM_MAP['HoldingEntityCode'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['HoldingEntityCode']:_self.BLANK;
			var invoiceID = (DesktopWeb._SCREEN_PARAM_MAP['invoiceID'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['invoiceID']:_self.BLANK;
			var invoiceDisp = (DesktopWeb._SCREEN_PARAM_MAP['invoiceDisp'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['invoiceDisp']:_self.BLANK;
			var enableholdingFlag = (DesktopWeb._SCREEN_PARAM_MAP['enableholdingFlag'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['enableholdingFlag']:_self.BLANK;
			var asOfDate = (DesktopWeb._SCREEN_PARAM_MAP['asOfDate'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['asOfDate']:_self.BLANK;
			var optSelectAsOfDate = (DesktopWeb._SCREEN_PARAM_MAP['optSelectAsOfDate'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['optSelectAsOfDate']:'true';
			var rowSelectedIndex = (DesktopWeb._SCREEN_PARAM_MAP['rowSelectedIndex'] != undefined)?DesktopWeb._SCREEN_PARAM_MAP['rowSelectedIndex']:0;
			
			if(billInstrID != undefined && billInstrID != _self.BLANK){
				_self.isFromInvoiceScreen = true;
			}else{
				_self.isFromInvoiceScreen = false;
			}

			if (_self.isFromInvoiceScreen){
				if(enableholdingFlag == 'false'){ _self.enableholdingFlag = false; }
				else{ _self.enableholdingFlag = true; }

				IFDS.Xml.addSingleNode(requestXML, "holdingEntityCode", holdingCode);	
				IFDS.Xml.addSingleNode(requestXML, "invoiceID", invoiceID);
				if (optSelectAsOfDate == 'true' && asOfDate != _self.BLANK){
					IFDS.Xml.addSingleNode(requestXML, "asOfDate", DesktopWeb.Util.getSMVDateValue(asOfDate));
				}
				IFDS.Xml.addSingleNode(requestXML, "runMode", 'init2');
			}else{
				if (holdingCode != _self.BLANK && holdingCode.length > 0){
					_self.enableholdingFlag = false;
					IFDS.Xml.addSingleNode(requestXML, "holdingEntityCode", holdingCode);
				}else { _self.enableholdingFlag = true; }
				
				IFDS.Xml.addSingleNode(requestXML, "runMode", 'init');
			}

			IFDS.Xml.addSingleNode(requestXML, "startRecNum", 1);
			IFDS.Xml.addSingleNode(requestXML, "requestRecNum", _requestRecNum);
			
			DesktopWeb.Ajax.doSmartviewAjax(_inqView, {ignoreErrorCode: '15'}, requestXML, responseHandler, _translationMap['Loading']);
			
			function responseHandler(success, responseXML){
				_inqInvoiceInstrXML = IFDS.Xml.cloneDocument(responseXML);
				
				storeDefaultValues(responseXML);
				storePermissions(responseXML);
				_self.setDefaultHoldingSearch(_vars['DefalutHoldingCode'],_vars['DefalutHoldingDesc'],_vars['DefalutHoldingDisp'],_self.enableholdingFlag);

				if (!_self.isFromInvoiceScreen){
					_self.lastSearchHolding = _vars['DefalutHoldingCode'];
					_self.lastSearchInvoice = '';
					_self.lastSearchInvoiceDisp = '';
					_self.lastSearchOption = 'true';
					_self.lastSearchAsOf = _vars['DefalutEffectiveDate'];
				}else{
					_self.lastSearchHolding = holdingCode;
					_self.lastSearchInvoice = invoiceID;
					_self.lastSearchInvoiceDisp = invoiceDisp;
					_self.lastSearchOption = optSelectAsOfDate;
					_self.lastSearchAsOf = asOfDate;
				}
				
				_self.setDefaultSearch();
				_self.enablePermButtons();
				loadDropdownList(responseXML);
				
				if (success){
					createMstrXML(responseXML, false);
					_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
					
					_self.enableMoreButton(_nextStartRecNum);
					
					if (_self.isFromInvoiceScreen){
						_self.refreshGrdInvoiceInstr(rowSelectedIndex);	
					}else{
						_self.refreshGrdInvoiceInstr(0);
					}
					
				}
			}
		}
		
		, enablePermButtons: function (){
			
			if (_permissionsMap[_self.INQ]){ _resources.buttons['cmdSearch'].enable(); }
									   else{ _resources.buttons['cmdSearch'].disable();}
				
			if (_permissionsMap[_self.ADD]){ _resources.grids['grdInvoiceInstr'].enableButton(0); } 
									   else{ _resources.grids['grdInvoiceInstr'].disableButton(0);}
										   
			var selectedRecord = _resources.grids['grdInvoiceInstr'].getSelectedRecord();
			var gridIndex = '';
			
			Ext.getCmp('AccountList').disable();
			Ext.getCmp('InvoiceAdj').disable();
			
			if (selectedRecord){
				_resources.grids['grdInvoiceInstr'].enableButton(4);
				_resources.grids['grdInvoiceInstr'].enableButton(5);
			
				if (_permissionsMap[_self.MOD]){ _resources.grids['grdInvoiceInstr'].enableButton(1); } 
										   else{ _resources.grids['grdInvoiceInstr'].disableButton(1);}	
				
				if (_permissionsMap[_self.DEL]){ _resources.grids['grdInvoiceInstr'].enableButton(2); } 
										   else{ _resources.grids['grdInvoiceInstr'].disableButton(2);}

				gridIndex = selectedRecord.data['gridIndex'];

				if((gridIndex != _self.BLANK) && (gridIndex.indexOf("tmpBillInstrID") > -1 == false)){
					Ext.getCmp('InvoiceAdj').enable();
					Ext.getCmp('AccountList').enable();
					_resources.grids['grdInvoiceInstr'].enableButton(4);
				    _resources.grids['grdInvoiceInstr'].enableButton(5);
				}else{
					Ext.getCmp('InvoiceAdj').disable();
					Ext.getCmp('AccountList').disable();
					_resources.grids['grdInvoiceInstr'].disableButton(4);
				    _resources.grids['grdInvoiceInstr'].disableButton(5);
				}
			}
		}
		
		,enableMoreButton: function (moreRec){
			if (moreRec){_resources.grids['grdInvoiceInstr'].enableButton(3);}
					else{_resources.grids['grdInvoiceInstr'].disableButton(3);}			
		}
		
		,setDefaultHoldingSearch: function(code, desc, disp, flag){
			loadDefaultHoldingCompanySearch(code, desc, "", disp, false);
						
			if (flag == false) {
				_resources.fields['holdingCompanySrch'].disableField();
				_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').disableField();
			}else{
				_resources.fields['holdingCompanySrch'].enableField();
				_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').enableField();
			}
		}
		
		,setDefaultSearch: function(){
			if (_self.isFromInvoiceScreen){
				_resources.fields['invoiceSrch'].setValue(_self.lastSearchInvoice);
				_resources.fields['invoiceSrch'].setRawValue(_self.lastSearchInvoiceDisp);
				_resources.fields['asOfDate'].setRawValue(_self.lastSearchAsOf);

				if (_self.lastSearchOption == 'true'){
					_resources.fields['optSelectAsOfDate'].setValue(true);
					_resources.fields['optSelectAll'].setValue(false);
				}else{
					_resources.fields['optSelectAsOfDate'].setValue(false);
					_resources.fields['optSelectAll'].setValue(true);
				}
			}else{
				_resources.fields['optSelectAsOfDate'].setValue(true);
				_resources.fields['optSelectAll'].setValue(false);
				_resources.fields['asOfDate'].setValue(_vars['DefalutEffectiveDate']);
			}
		}
		
		,doSrchCheck: function(){
			if (_resources.fields['optSelectAll'].getValue()){
				_resources.fields['asOfDate'].disable();
				_resources.fields['asOfDate'].clearInvalid();
			}else{
				_resources.fields['asOfDate'].enable();
			}
		}
		
		,doSrchValid: function(event){
			var rtnVal = true;
			_resources.fields['holdingCompanySrch'].clearInvalid();
			_resources.fields['invoiceSrch'].clearInvalid();
			
			if (_resources.fields['optSelectAll'].getValue() == false){
				if (_resources.fields['asOfDate'].getRawValue() == ''){
					_resources.fields['asOfDate'].markInvalid(_translationMap['Error_EffectiveDateRequire']);
					rtnVal = false;
				}
			}
			
			if (_resources.fields['asOfDate'].isValid() == false){
				rtnVal = false;
			}
	
			if(event != 'focus' && _resources.fields['holdingCompanySrch'].getValue() == '' && _resources.fields['invoiceSrch'].getValue() == ''){
				_resources.fields['holdingCompanySrch'].markInvalid(_translationMap['Error_EitherHoldComOrInvoiceInstr']);
				_resources.fields['invoiceSrch'].markInvalid(_translationMap['Error_EitherHoldComOrInvoiceInstr']);
				rtnVal = false;
			}else{
				_resources.fields['holdingCompanySrch'].clearInvalid();
				_resources.fields['invoiceSrch'].clearInvalid();
			}
			
			return rtnVal;
		}
		
		,doSearch: function(more){
			if (_self.doSrchValid()){
				
				if(this.updatesFlag && !more){
					DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg)
					function handlePromptMsg(btn){
						if(btn){
							_self.updatesFlag = false;
							DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, getReloadRequest(more), responseHandler, _translationMap['Searching']);
						}
					}
				}else{
					DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, getReloadRequest(more), responseHandler, _translationMap['Searching']);
				}
				
				function responseHandler(success, responseXML){
					this.updatesFlag = false;
					
					if (success){
						
						createMstrXML(responseXML, more);						
						_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
						_self.refreshGrdInvoiceInstr(0);
						_self.enableMoreButton(_nextStartRecNum);					
					}
					else{
						_mstrXML = null;
						_self.clearGrdInvoiceInstr();
					}
				}
			}
		}
		
		,refreshGrdInvoiceInstr: function (index){		
			_resources.grids['grdInvoiceInstr'].loadData(_mstrXML);
			_resources.grids['grdInvoiceInstr'].setSelectedRecord(index);
		}
		
		,clearGrdInvoiceInstr: function (){		
			_resources.grids['grdInvoiceInstr'].clearData();
			_resources.fields['invoiceName1'].setValue('');
			/*_resources.fields['invoiceName2'].setValue('');*/
			_resources.fields['deliveryName1'].setValue('');
			_resources.fields['deliveryName2'].setValue('');
			_resources.fields['addr1'].setValue('');
			_resources.fields['addr2'].setValue('');
			_resources.fields['addr3'].setValue('');
			_resources.fields['addr4'].setValue('');
			_resources.fields['city'].setValue('');
			_resources.fields['country'].setValue('');
			_resources.fields['pstl'].setValue('');
								
			/*** Logical value ***/
			_resources.fields['taxApply'].setValue('');
			_resources.fields['supplementReq'].setValue('');
								
			/*** List value ***/
			_resources.fields['frequency'].setValue('');
			_resources.fields['paymentOptn'].setValue('');
			_resources.fields['termOfPayment'].setValue('');
			_resources.fields['currency'].setValue('');
			_resources.fields['language'].setValue('');				
			_resources.fields['brandingType'].setValue('');

			_self.enablePermButtons();
		}
		
		,updateContent: function(){
			var obj = this.getSelectedInvoiceInstr();
			if (obj){
				/*** Original value ***/
				_resources.fields['invoiceName1'].setValue(obj.invoiceName.trim() + obj.invoiceName2.trim());
				_resources.fields['deliveryName1'].setValue(obj.delivName1);
				_resources.fields['deliveryName2'].setValue(obj.delivName2);
				_resources.fields['addr1'].setValue(obj.addrLine1);
				_resources.fields['addr2'].setValue(obj.addrLine2);
				_resources.fields['addr3'].setValue(obj.addrLine3);
				_resources.fields['addr4'].setValue(obj.addrLine4);
				_resources.fields['city'].setValue(obj.city);
				_resources.fields['country'].setValue(_self.getListDisplay('provCountries',obj.provCountry));
				_resources.fields['pstl'].setValue(obj.pstl);
								
				/*** Logical value ***/
				_resources.fields['taxApply'].setValue(_self.getLogicalDisplay(obj.taxApplies));
				_resources.fields['supplementReq'].setValue(_self.getLogicalDisplay(obj.suppInfoReq));
								
				/*** List value ***/
				_resources.fields['frequency'].setValue(_self.getListDisplay('frequencies',obj.frequency));
				_resources.fields['paymentOptn'].setValue(_self.getListDisplay('chargeOptions',obj.chargeOption));
				_resources.fields['termOfPayment'].setValue(obj.termPymt + " " + _self.getListDisplay('termDayTypes',obj.termPymtType));
				_resources.fields['currency'].setValue(_self.getListDisplay('currencyList',obj.currency));
				_resources.fields['language'].setValue(_self.getListDisplay('languages',obj.lang));				
				_resources.fields['brandingType'].setValue(_self.getListDisplay('brandingTypes',obj.brandingType));
				
				_self.enablePermButtons();
				
				if(_permissionsMap[_self.DEL] && obj.allowDel.toLowerCase() == 'yes'){
					  _resources.grids['grdInvoiceInstr'].enableButton(2);
				}else{_resources.grids['grdInvoiceInstr'].disableButton(2);}
				
			}
		}
		
		,getLogicalDisplay: function(val){
			var returnVal = null;
			if (val != null && val.length > 0){
				returnVal = val.toLowerCase();
				if (returnVal == 'y' || returnVal == 'yes'){returnVal = 'Yes';}
				else{returnVal = 'No';}
			}else{ returnVal = '';}
			return returnVal;
		}
		
		,getListDisplay: function(listName, code){
			var listNode = IFDS.Xml.getNode(_inqInvoiceInstrXML, "//List[@listName = '" + listName + "']/Element[code='" + code + "']");
			return (listNode)?IFDS.Xml.getNodeValue(listNode, 'value'):code;
		}
		
		,openActionPopup: function(popupName, action){
			if (popupName == 'InvoiceAdj' || popupName == 'AcctAssociate'){
				var selectedRecord = _resources.grids['grdInvoiceInstr'].getSelectedRecord();
				var invoiceInstrObj = getInvoiceInstr(_resources.grids['grdInvoiceInstr'].getSelectedRecord().get("gridIndex"));
				var indexObj = 0;
				if (invoiceInstrObj){indexObj = invoiceInstrObj.index;}
				
				if(this.updatesFlag){
					DesktopWeb.Util.displayDiscardPrompt(handlePromptMsg);
					function handlePromptMsg(btn){
					if(btn){
						goToScreen(popupName,
								   selectedRecord.data['billInstrID'],
								   selectedRecord.data['invoiceID'], /**billInstrCode**/
								   _self.lastSearchHolding,
								   _self.lastSearchInvoice,
								   _self.lastSearchInvoiceDisp,
								   _self.enableholdingFlag,
								   _self.lastSearchAsOf,
								   _self.lastSearchOption,
								   indexObj ////rowSelectedIndex
								   );
						}
					}
				}else{
					goToScreen(popupName,
							   selectedRecord.data['billInstrID'],
							   selectedRecord.data['invoiceID'], /**billInstrCode**/
							   _self.lastSearchHolding,
							   _self.lastSearchInvoice,
							   _self.lastSearchInvoiceDisp,
							   _self.enableholdingFlag,
							   _self.lastSearchAsOf,
							   _self.lastSearchOption,
							   indexObj ////rowSelectedIndex
							   );
				}
			}else{
				if(action != _self.DEL){
					_resources.popups[popupName].init(action);
					_resources.popups[popupName].show();
					_self.clearPopupInfo();
				}
				_self.populateInvoiceInstr(action);
			}
		}
		
		,clearPopupInfo: function(){
			_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('invoiceSrchDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('effectiveDateDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('stopDateDetl').reset();
			
			_resources.popups['frmInvoiceDetl'].getField('invoiceName1Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('invoiceName2Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('deliveryName1Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('deliveryName2Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('addr1Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('addr2Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('addr3Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('addr4Detl').reset();
			_resources.popups['frmInvoiceDetl'].getField('cityDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('countryDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('pstlDetl').reset();
			
			_resources.popups['frmInvoiceDetl'].getField('frequencyDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('paymentOptnDetl').reset();
			Ext.getCmp('termOfPaymentDetl').reset();
			Ext.getCmp('termOfPaymentTypeDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('currencyDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('taxApplyDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('languageDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('supplementReqDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').reset();
			_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').clearInvalid();
		}
		
		,populateInvoiceInstr: function(action){
			switch (action){
				case _self.ADD:{
					if (_vars['DefalutHoldingCode'] != _self.BLANK && _self.enableholdingFlag == false){
						loadDefaultHoldingCompanySearch(_vars['DefalutHoldingCode'], _vars['DefalutHoldingDesc'], "", _vars['DefalutHoldingDisp'], false);
						loadDefaultHoldingCompanySearch(_vars['DefalutHoldingCode'], _vars['DefalutHoldingDesc'], "", _vars['DefalutHoldingDisp'], true);
						_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').disableField();
					}else{
						var selectedRecord = _resources.grids['grdInvoiceInstr'].getSelectedRecord();
						if (selectedRecord){
							loadDefaultHoldingCompanySearch(selectedRecord.data['holdingEntityCode'], selectedRecord.data['holdingEntityDesc'], "",selectedRecord.data['holdingEntityCode'] + " - " + selectedRecord.data['holdingEntityDesc'], true);
						}else{
							/*** SMVCombo will pre-populate blank value for first init screen ***/
							var record = _resources.fields['holdingCompanySrch'].selectedRecord;
							if (record){
								loadDefaultHoldingCompanySearch(record.data['holdingCompanyCode'], record.data['holdingCompanyDesc'], "",record.data['holdingCompanyCode'] + " - " + record.data['holdingCompanyDesc'], true);
							}
						}
						_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').enableField();
					}
					_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').clearInvalid();
					_resources.popups['frmInvoiceDetl'].getField('invoiceSrchDetl').enableField();
					_resources.popups['frmInvoiceDetl'].getField('effectiveDateDetl').setValue(_vars['DefalutDeff']);
					_resources.popups['frmInvoiceDetl'].getField('stopDateDetl').setValue(_vars['DefaultStopDate']);
					
					_resources.popups['frmInvoiceDetl'].getField('frequencyDetl').setValue(_vars['DefaultFrequency']);
					_resources.popups['frmInvoiceDetl'].getField('frequencyDetl').setRawValue(_self.getListDisplay('frequencies',_vars['DefaultFrequency']));
					
					_resources.popups['frmInvoiceDetl'].getField('paymentOptnDetl').setValue(_vars['DefaultChargeOption']);
					_resources.popups['frmInvoiceDetl'].getField('paymentOptnDetl').setRawValue(_self.getListDisplay('chargeOptions',_vars['DefaultChargeOption']));
					
					Ext.getCmp('termOfPaymentDetl').setValue(_vars['DefaultTermPymt']);
					Ext.getCmp('termOfPaymentTypeDetl').setValue(_vars['DefaultTermPymtType']);
					Ext.getCmp('termOfPaymentTypeDetl').setRawValue(_self.getListDisplay('termDayTypes',_vars['DefaultTermPymtType']));
					
					_resources.popups['frmInvoiceDetl'].getField('currencyDetl').setValue(_vars['DefaultCurrency']);
					_resources.popups['frmInvoiceDetl'].getField('currencyDetl').setRawValue(_self.getListDisplay('currencyList',_vars['DefaultCurrency']));
					
					_resources.popups['frmInvoiceDetl'].getField('taxApplyDetl').setValue(_vars['DefaultTaxApplies']);
					_resources.popups['frmInvoiceDetl'].getField('taxApplyDetl').setRawValue(_self.getLogicalDisplay(_vars['DefaultTaxApplies']));
					
					_resources.popups['frmInvoiceDetl'].getField('languageDetl').setValue(_vars['DefaultLang']);
					_resources.popups['frmInvoiceDetl'].getField('languageDetl').setRawValue(_self.getListDisplay('languages',_vars['DefaultLang']));
					
					_resources.popups['frmInvoiceDetl'].getField('supplementReqDetl').setValue(_vars['DefaultSuppInfoReq']);
					_resources.popups['frmInvoiceDetl'].getField('supplementReqDetl').setRawValue(_self.getLogicalDisplay(_vars['DefaultSuppInfoReq']));
					
					_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').reset();
					_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').setValue('');
					_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').setValue('');
					_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').clearInvalid();
					break;
				}
				
				case _self.MOD:{
					var obj = this.getSelectedInvoiceInstr();
					var objIndex = '';
					if (obj){
						/**MOD MODE -> Not update billingInstrID**/
						loadDefaultHoldingCompanySearch(obj.holdingEntityCode, obj.holdingEntityDesc, "", obj.holdingEntityCode + " - " + obj.holdingEntityDesc, true);
						_resources.popups['frmInvoiceDetl'].getField('invoiceSrchDetl').setValue(obj.invoiceID);
						
						objIndex = obj.gridIndex;
						/** Check if user is modifying a new record ***/
						if((objIndex != _self.BLANK) && (objIndex.indexOf("tmpBillInstrID") > -1 == false)){
							_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').disableField();
							_resources.popups['frmInvoiceDetl'].getField('invoiceSrchDetl').disableField();
						}
						else{
							/*** come from Holding Company Screen ***/
							if (_vars['DefalutHoldingCode'] != null && _vars['DefalutHoldingCode'] != "" && _self.enableholdingFlag == false){
								_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').disableField();
							}else{
								_resources.popups['frmInvoiceDetl'].getField('holdingCompanySrchDetl').enableField();
							}
							_resources.popups['frmInvoiceDetl'].getField('invoiceSrchDetl').enableField();
						}
						
						_resources.popups['frmInvoiceDetl'].getField('effectiveDateDetl').setValue(obj.deff);
						_resources.popups['frmInvoiceDetl'].getField('stopDateDetl').setValue(obj.stopDate);
						_resources.popups['frmInvoiceDetl'].getField('invoiceName1Detl').setValue(obj.invoiceName);
						_resources.popups['frmInvoiceDetl'].getField('invoiceName2Detl').setValue(obj.invoiceName2);
						_resources.popups['frmInvoiceDetl'].getField('deliveryName1Detl').setValue(obj.delivName1);
						_resources.popups['frmInvoiceDetl'].getField('deliveryName2Detl').setValue(obj.delivName2);
						_resources.popups['frmInvoiceDetl'].getField('addr1Detl').setValue(obj.addrLine1);
						_resources.popups['frmInvoiceDetl'].getField('addr2Detl').setValue(obj.addrLine2);
						_resources.popups['frmInvoiceDetl'].getField('addr3Detl').setValue(obj.addrLine3);
						_resources.popups['frmInvoiceDetl'].getField('addr4Detl').setValue(obj.addrLine4);
						_resources.popups['frmInvoiceDetl'].getField('cityDetl').setValue(obj.city);
						
						_resources.popups['frmInvoiceDetl'].getField('countryDetl').setValue(obj.provCountry);
						_resources.popups['frmInvoiceDetl'].getField('countryDetl').setRawValue(_self.getListDisplay('provCountries',obj.provCountry));
												
						_resources.popups['frmInvoiceDetl'].getField('pstlDetl').setValue(obj.pstl);
						
						_resources.popups['frmInvoiceDetl'].getField('frequencyDetl').setValue(obj.frequency);
						_resources.popups['frmInvoiceDetl'].getField('frequencyDetl').setRawValue(_self.getListDisplay('frequencies',obj.frequency));
						
						_resources.popups['frmInvoiceDetl'].getField('paymentOptnDetl').setValue(obj.chargeOption);
						_resources.popups['frmInvoiceDetl'].getField('paymentOptnDetl').setRawValue(_self.getListDisplay('chargeOptions',obj.chargeOption));
						
						Ext.getCmp('termOfPaymentDetl').setValue(obj.termPymt);
						Ext.getCmp('termOfPaymentTypeDetl').setValue(obj.termPymtType);
						Ext.getCmp('termOfPaymentTypeDetl').setRawValue(_self.getListDisplay('termDayTypes',obj.termPymtType));
						
						_resources.popups['frmInvoiceDetl'].getField('currencyDetl').setValue(obj.currency);
						_resources.popups['frmInvoiceDetl'].getField('currencyDetl').setRawValue(_self.getListDisplay('currencyList',obj.currency));
						
						_resources.popups['frmInvoiceDetl'].getField('taxApplyDetl').setValue(obj.taxApplies);
						_resources.popups['frmInvoiceDetl'].getField('taxApplyDetl').setRawValue(_self.getLogicalDisplay(obj.taxApplies));
						
						_resources.popups['frmInvoiceDetl'].getField('supplementReqDetl').setValue(obj.suppInfoReq);
						_resources.popups['frmInvoiceDetl'].getField('supplementReqDetl').setRawValue(_self.getLogicalDisplay(obj.suppInfoReq));
						
						_resources.popups['frmInvoiceDetl'].getField('languageDetl').setValue(obj.lang);
						_resources.popups['frmInvoiceDetl'].getField('languageDetl').setRawValue(_self.getListDisplay('languages',obj.lang));
						
						_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').setValue(obj.brandingType);
						_resources.popups['frmInvoiceDetl'].getField('brandingTypeDetl').setRawValue(_self.getListDisplay('brandingTypes',obj.brandingType));
					}
					break;
				}
				
				case _self.DEL:{
					_self.doSave(_self.DEL, null);
				}
			}
		}
		
		,getSelectedInvoiceInstr: function(){
			if (_resources.grids['grdInvoiceInstr'].getSelectedRecord()){
				return getInvoiceInstr(_resources.grids['grdInvoiceInstr'].getSelectedRecord().get("gridIndex"));
			}else{
				return null;
			}
		}
		
		,doValidatePopup: function (action, data){
			var isSuccess = true;
			var warningMsg = null;
			if (data['deff'] == undefined || (data['stopDate'] == undefined )){
				isSuccess = false;
				_resources.popups['frmInvoiceDetl'].getField('effectiveDateDetl').markInvalid(_translationMap['Error_StartDateOrEndDateIsBlank']);
			}
			else if (data['deff'] > data['stopDate']){
				isSuccess = false;
				_resources.popups['frmInvoiceDetl'].getField('effectiveDateDetl').markInvalid(_translationMap['Error_StartDateNotPriorEndDate']);
			}
			
			
			
			var provRecord = _resources.popups['frmInvoiceDetl'].getField('countryDetl').getSelectedRecord()
			var reqField = (provRecord && provRecord != undefined) ?
				provRecord.data['requirePSTL'] :'';
			if (reqField == 'yes' && data['pstl'] == '')
			{
				isSuccess = false;
				_resources.popups['frmInvoiceDetl'].getField('pstlDetl').allowBlank = false;
				_resources.popups['frmInvoiceDetl'].getField('pstlDetl').validate();
			}
			else
			{
				_resources.popups['frmInvoiceDetl'].getField('pstlDetl').allowBlank = true;
				_resources.popups['frmInvoiceDetl'].getField('pstlDetl').clearInvalid();
			}
			
			if (isSuccess && action == _self.MOD){
				var vBollIngInstr = _resources.grids['grdInvoiceInstr'].getSelectedRecord().data['billInstrID'];
				var vStopDateOld = _resources.grids['grdInvoiceInstr'].getSelectedRecord().data['stopDate'];
				var vStopDateNew = _resources.popups['frmInvoiceDetl'].getField('stopDateDetl').getDisplayDateString(); 
				var vDeffDateOld = _resources.grids['grdInvoiceInstr'].getSelectedRecord().data['deff'];
				var vDeffDateNew = _resources.popups['frmInvoiceDetl'].getField('effectiveDateDetl').getDisplayDateString();
				var vAcctAsso = _resources.grids['grdInvoiceInstr'].getSelectedRecord().data['acctAsso'];
				
				if(vBollIngInstr.indexOf("tmpBillInstrID") > -1 == false){
					if ( (vAcctAsso == 'yes') && ( (vDeffDateOld != vDeffDateNew) || (vStopDateOld != vStopDateNew) ) ){
						isSuccess = false;
						warningMsg = _translationMap['Error_WarningChangedDate'];
					}
				}
			}
			
			data['deff'] = _resources.popups['frmInvoiceDetl'].getField('effectiveDateDetl').getSMVDateString();
			data['stopDate'] = _resources.popups['frmInvoiceDetl'].getField('stopDateDetl').getSMVDateString();
			if (!isSuccess && warningMsg)
			{
				DesktopWeb.Util.displayWarning(warningMsg, msgCallback);
				function msgCallback()
				{
					_self.doSave(action, data);
				}
			}
			return isSuccess;
		}
		
		,doSave: function(action, data){
			if (action == _self.ADD){					
				addNewInvoiceInstr(data);
				_self.refreshGrdInvoiceInstr(_resources.grids['grdInvoiceInstr'].getStore().getCount());
				_self.clearPopupInfo();				
				_resources.popups['frmInvoiceDetl'].hide();
			}
			else if (action == _self.MOD){
				var index = updateInvoiceInstr(_self.getSelectedInvoiceInstr().gridIndex, data);
				_self.refreshGrdInvoiceInstr(index);
				_self.clearPopupInfo();
				_resources.popups['frmInvoiceDetl'].hide();
			}
			else if (action == _self.DEL){
				deleteInvoiceInstr(_self.getSelectedInvoiceInstr().gridIndex);
				_self.refreshGrdInvoiceInstr(0);
				if(_resources.grids['grdInvoiceInstr'].getStore().getCount() == 0){
					_resources.grids['grdInvoiceInstr'].enableButton(0);
					_resources.grids['grdInvoiceInstr'].disableButton(1);
					_resources.grids['grdInvoiceInstr'].disableButton(2);
					_resources.grids['grdInvoiceInstr'].disableButton(3);
					_resources.grids['grdInvoiceInstr'].disableButton(4);
					_resources.grids['grdInvoiceInstr'].disableButton(5);
					Ext.getCmp('InvoiceAdj').disable();
					if (_self.lastSearchHolding != _self.BLANK){
						Ext.getCmp('AccountList').enable();
					}else{ Ext.getCmp('AccountList').disable();}
				}
			}
		}
		
		,doUpdate: function (mode){
			var updateStatus = null;
			DesktopWeb.Ajax.doSmartviewUpdate(_updView, null, getUpdateRequest(mode), responseHandler, _translationMap['Updating']);			

			function responseHandler(success, responseXML, contextErrors){
				if (success){
					updateStatus = DesktopWeb._SUCCESS;									
				}else{
					storeContextErrors(contextErrors);
					updateStatus = DesktopWeb._FAIL; 	
				}
			}	
			return updateStatus;
		}
				
		,doValidateCommitScreen : function()
		{			
			// All validation should be done before confirmation screen
			if (_self.doUpdate('validate') == DesktopWeb._SUCCESS){
				DesktopWeb.Util.commitScreen();
			}
		}
		
		,openAdminPopup: function()
		{
			title = _translationMap['InvoiceInstr']+ ' - ' +_translationMap['Admin']			
			selectrecord = _resources.grids['grdInvoiceInstr'].getSelectedRecord();
					
			var adminData = {};
			adminData['userName'] = selectrecord.data['username'];
			adminData['procDate'] = selectrecord.data['processDate'];
			adminData['modUser'] = selectrecord.data['modUser'];
			adminData['modDate'] = selectrecord.data['modDate'];
			_resources.popups['admin'].init(title,adminData);
			_resources.popups['admin'].show();
		}
		
		,openHistoryPopup: function(){
			var viewParam = {};
			var historyName = null;
			var tempRecord  = _resources.grids['grdInvoiceInstr'].getSelectedRecord();
			
			if (tempRecord != undefined && tempRecord != null)
			{
				viewParam['auditType'] = 'InvoiceInstr';
				viewParam['searchValue1'] = _resources.grids['grdInvoiceInstr'].getSelectedRecord().data['billInstrID'];
				historyName = _translationMap['InvoiceInstr']+ ' - ' +_translationMap['History'];
				
				_resources.popups['history'].init(historyName, _historyService, viewParam, true);
				_resources.popups['history'].show();
			}
		}
		
	}	
	
	
}	