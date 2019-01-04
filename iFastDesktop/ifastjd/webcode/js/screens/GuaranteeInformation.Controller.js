/*********************************************************************************************
 * @file	GuaranteeInformation.Controller.js 
 * @author	Danny Xu
 * @desc	Controller JS file for Guarantee Information screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  15 Nov 2013 Kittichai S. P0181067 CHG0034430 T54443
 *        - Fix display date format follows dateFormatDisplay parameter
 *  23 Jul 2014 A. Mongkonrat P0232147 DFT0034027 T55476              
 *              On the Income base detail screen, Election date and date of birth format are wrong. 
 *              Should be DD/MM/YYY. 
 *  06 Aug 2014 A. Mongkonrat P0232147 DFT0034027 T55489            
 *              On the Income base detail screen, Election date and date of birth format are wrong. 
 *              Should be DD/MM/YYY. 
 *
 *	25 Aug 2014 P. Wongpakdee P0232147 DFT0038714 T55606
 *		  - Fixed logic to ignore no data found error only when
 *			launching the screen
 *
 *  27 Aug 2014 A. Mongkonrat P0232147 DFT0038716 T55600 In 'Gurantee Information' screen, 
 *              script err displayed -'IncomeBaseDetail'button.
 *
 *  02 Sep 2014 A. Mongkonrat P0232147 DFT0038716 T55662 In 'Gurantee Information' screen, 
 *              'IncomeBaseDetail'button is disabled.
 *
 *	25 Sep 2014 P. Wongpakdee P0233151 INA Cayenne Day2 T55815
 *				- populate new fields contractTypeDIA and versionDIA
 *				- check flag allowFundRate to show/hide fund column
 * 
 *  22 Oct 2014 P. Wongpakdee P0233151 DFT0042593 T55904
 *				- Fix not to display script error when populate DIA Info and 
 *				  Income Base Detail screens
 *
 *  30 Oct 2014 P. Wongpakdee P0233151 DFT0038255 T55947 
 *			    - Get and send SegGuarDetlUUID when open Income Base Detail screen;
 *				  both access from DIA Info and Guarantee Info screens
 *
 *	20 Nov 2014 P. Wongpakdee P0233151 DFT0044246 T56076
 *				- Send diaAsOfDate for filing SEG Transaction (DIA Info)
 *
 *	09 Apr 2015 A. Mongkonrat P0232343 T80576 Fox Project B Payout Contract Type
 *              - Support R1 and R2 transaction types.
 *              - ELWA Impact pop up.
 *              - Hypothetical Election pop up.
 *
 *	19 Jun 2015 A. Mongkonrat P0232343 T80996 DFT0051854 Fox Project B Payout Contract Type
 *              - All existing accounts & New Account show that Exceeded LWA Limit = Yes
 *
 *  13 Aug 2015 Aurkarn M. - P0243676 T81232 Dollar For Dollar Guarantee Reductions
 *              - New Deplete Limit button and popup
 *
 *  08 Sep 2015 Aurkarn M. - P0243676 T81368 DFT0053687 Dollar For Dollar Guarantee Reductions
 *              - DL Screen in desktop showing values as zero after Year end.
 *
 *  21 Sep 2015 Aurkarn M. - P0243676 T81419 DFT0054026 Dollar For Dollar Guarantee Reductions
 *              - "Depletion Limit" button in iFast Desktop is throwing Java Error
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached. 
 *
 *	11 Oct 2016 Matira T. P0256533 T84091 MFS - Desktop
 *              - Added PBG.
 *
 *	04 Nov 2016 Matira T. P0256533 T84110 MFS - Desktop
 *              - Changed logic on exiting guarantee(DBG,DMG) and all new guarantees.
 *
 *  02-Mar-2017 Matira T. P0257694 T85094 INA - Triennial Reset for NMCR 17.4
 *              - New label Total LWA Base and new column lwaBase.
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _guarInfoReloadView = 'dtSegGuarInfoReload';
	var _txnEventsReloadView = 'dtSegTxnEventsReload';
	var _addTxnReloadView = 'dtSegAddTxnReload';
	var _txnVldtnsView = 'dtSegForceTxnVldtns';
	var _cancelRolloverValidationView = 'dtSegCxlMRCMVldtns';
	var _canTxnReloadView = 'dtSegCxlTxnReload';	
	var _segTxnUpdateView = 'dtSegForceTxnUpd';
	var _segCxlCMUpdView = 'dtSegCxlCMUpd';
	var _segCxlMRUpdView = 'dtSegCxlMRUpd';
	var _segIncmBaseReloadView = 'dtSegIncmBaseReload';
	var _segDIAInfoReloadView = 'dtSegDIAInfoReload';
	var _segDIATransactionReloadView = 'dtSegDIATxnReload';
	var _hypoElectionView = 'dtHypoElection';
	var _elwaImpactView = 'dtEligibleLWA';
	var _depleteLimView = 'dtDepleteLim';
	var _segIncmBaseXML = null;	
	var _segDIAInfoXML = null;
	var _segDIATransactionXML = null;
	var _updateXML = IFDS.Xml.newDocument('Data');
	var _mstrReloadXML = null;
	var _recordRangeXML = null;
	var _enableGMWB;
	var _addDataXML = null;
	var _nextStartRecNum = null;
	var _mstrID = 1;
	var _permissionsMap = {};
	var _GATransUpdate = false
	var _MR_CM_cancel = false;
	var _incCreditApp;
	var _isNMCRContract;
	var _isElected;
	var _firstDPAAge;
	var _firstDPAYear;
	var _defaultAsOfDate = false;
	var _asOfDate = false;
	var _actionScreen = null;
	var _segGuarInfoReloadXML = null;
	// PRIVATE METHODS ****************************************	
	
	function storePermissions(initViewXML)
	{				
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '/*//SegForcePermission/allowSegForceAdd').toLowerCase() == 'yes';		
		_permissionsMap[_self.CANC] = IFDS.Xml.getNodeValue(initViewXML, '/*//SegForcePermission/allowSegForceCxl').toLowerCase() == 'yes';	
	}
	
	function populateGuaranteeInfo(responseXML)
	{
		var xml = IFDS.Xml.getNode(responseXML, "//GuaranteeInfo")
		
		_resources.fields['guarMKV'].setValue(IFDS.Xml.getNodeValue(xml, "guarMKV"));
		_resources.fields['guarDBG'].setValue(IFDS.Xml.getNodeValue(xml, "guarDBG"));
		_resources.fields['guarDMG'].setValue(IFDS.Xml.getNodeValue(xml, "guarDMG"));
		_resources.fields['guarGWB'].setValue(IFDS.Xml.getNodeValue(xml, "guarGWB"));
		_resources.fields['guarBonus'].setValue(IFDS.Xml.getNodeValue(xml, "guarBonus"));
		_resources.fields['guarGWA'].setValue(IFDS.Xml.getNodeValue(xml, "guarGWA"));
		_resources.fields['guarLWA'].setValue(IFDS.Xml.getNodeValue(xml, "guarLWA"));
		_resources.fields['guarAdjGWA'].setValue(IFDS.Xml.getNodeValue(xml, "guarAdjGWA"));
		_resources.fields['guarAdjLWA'].setValue(IFDS.Xml.getNodeValue(xml, "guarAdjLWA"));
		_resources.fields['guarRemGWA'].setValue(IFDS.Xml.getNodeValue(xml, "guarRemGWA"));
		_resources.fields['guarRemLWA'].setValue(IFDS.Xml.getNodeValue(xml, "guarRemLWA"));
		_resources.fields['guarGWADef'].setValue(IFDS.Xml.getNodeValue(xml, "guarGWADef"));
		_resources.fields['guarRemGWADef'].setValue(IFDS.Xml.getNodeValue(xml, "guarRemGWADef"));
		_resources.fields['guarDBGTopup'].setValue(IFDS.Xml.getNodeValue(xml, "dbgTopupAmt"));
		_resources.fields['guarDMGTopup'].setValue(IFDS.Xml.getNodeValue(xml, "dmgTopupAmt"));
		_resources.fields['guarIncCredit'].setValue(IFDS.Xml.getNodeValue(xml, "guarIncCreditAmt"));	
		_resources.fields['guarIncBaseLWA'].setValue(IFDS.Xml.getNodeValue(xml, "guarIncBaseLWA"));		
		_resources.fields['guarDPAAtAge'].setValue(IFDS.Xml.getNodeValue(xml, "guarFirstDPAAmt"));
		_resources.fields['guarLWAEntitlement'].setValue(IFDS.Xml.getNodeValue(xml, "guarLWAEntitlement"));
		_resources.fields['guarPBG'].setValue(IFDS.Xml.getNodeValue(xml, "guarPBG"));
	}
	
	function clearGuaranteeInfo()
	{
		_resources.fields['guarMKV'].reset();
		_resources.fields['guarDBG'].reset();
		_resources.fields['guarDMG'].reset();
		_resources.fields['guarGWB'].reset();
		_resources.fields['guarBonus'].reset();
		_resources.fields['guarGWA'].reset();
		_resources.fields['guarLWA'].reset();
		_resources.fields['guarAdjGWA'].reset();
		_resources.fields['guarAdjLWA'].reset();
		_resources.fields['guarRemGWA'].reset();
		_resources.fields['guarRemLWA'].reset();
		_resources.fields['guarLWAExceeded'].reset();
		_resources.fields['guarGWADef'].reset();
		_resources.fields['guarRemGWADef'].reset();
		_resources.fields['guarDBGTopup'].reset();
		_resources.fields['guarDMGTopup'].reset();
		_resources.fields['guarIncCredit'].reset();
		_resources.fields['guarIncBaseLWA'].reset();
		_resources.fields['guarDPAAtAge'].reset();
		_resources.fields['guarLWAEntitlement'].reset();
	}
	
	function populateListOfTerms(responseXML)
	{
		_resources.grids['listOfTerms'].loadData(IFDS.Xml.getNode(responseXML, "//ListOfTerms"));
		
		maturityID=(IFDS.Xml.getNodeValue(_mstrReloadXML,"//ListOfTerms/TermDetails/maturityID"));
		_enableGMWB = (IFDS.Xml.getNodeValue(_mstrReloadXML,"//ListOfTerms/TermDetails/enableGMWB"));
		_incCreditApp = (IFDS.Xml.getNodeValue(_mstrReloadXML,"//ListOfTerms/TermDetails/incCreditApp"));
		_isNMCRContract = (IFDS.Xml.getNodeValue(_mstrReloadXML,"//ListOfTerms/TermDetails/isNMCRContract"));
		_isElected = (IFDS.Xml.getNodeValue(_mstrReloadXML,"//ListOfTerms/TermDetails/isElected"));
		_firstDPAAge = (IFDS.Xml.getNodeValue(_mstrReloadXML,"//ListOfTerms/TermDetails/firstDPAAge"));
		_firstDPAYear = (IFDS.Xml.getNodeValue(_mstrReloadXML,"//ListOfTerms/TermDetails/firstDPAYear"));			
		
		if (_incCreditApp.toUpperCase() == "YES")
		{
			_resources.fields['guarIncCredit'].show();
		}
		else
		{
			_resources.fields['guarIncCredit'].hide();
		}						

		if (_isNMCRContract.toUpperCase() == "YES")
		{
			_resources.fields['guarIncBaseLWA'].show();			
		}
		else
		{
			_resources.fields['guarIncBaseLWA'].hide();
		}
		
		if (_isNMCRContract.toUpperCase() == "YES" && _isElected.toUpperCase() == "NO")
		{
			_resources.fields['guarDPAAtAge'].show();
			_resources.fields['guarLWAEntitlement'].hide();
		}
		else
		{
			_resources.fields['guarDPAAtAge'].hide();				
			if (_isNMCRContract.toUpperCase() == "YES" && _isElected.toUpperCase() == "YES") 
			{
				_resources.fields['guarLWAEntitlement'].show();
			} else {
				_resources.fields['guarLWAEntitlement'].hide();
			}
		}
		
		if((maturityID == null) || (maturityID == "")){		
			Ext.getCmp('YearlyGWB').setDisabled(true);
		}
		
		if (_resources.grids['listOfTerms'].getAllRecords().length > 0)
		{
			if (IFDS.Xml.getNodeValue(responseXML, "//GuaranteeInfo/GWAEWALabel").toUpperCase() == "EWA")
			{
				_resources.grids['listOfTerms'].setColumnHeaderText(_resources.grids['listOfTerms'].getColumnModel().getColumnCount() - 2, _translationMap['TransRemEWA']);
				_resources.grids['transaction'].getColumnModel().setColumnHeader(_resources.grids['transaction'].getColumnModel().getColumnCount() - 2, _translationMap['TransRemEWA']);
				
				_resources.popups['transPopup'].getField('GAGwaEwa').setFieldLabel(_translationMap['GuaranteeAdjEWA']);
				_resources.popups['transPopup'].getField('GAAdjustedGwaEwa').setFieldLabel(_translationMap['GuaranteeAdjEWAAdjusted']);
				_resources.popups['transPopup'].getField('GARemainingGwaEwa').setFieldLabel(_translationMap['GuaranteeAdjEWARemaining']);
				//_resources.popups['transPopup'].getField('GAGWADeferral').setFieldLabel(_translationMap['GuaranteeAdjEWADeferral']);
				//_resources.popups['transPopup'].getField('GARemainingGWADeferral').setFieldLabel(_translationMap['GuaranteeAdjEWARemainingDeferrel']);
				
				_resources.fields['guarAdjGWA'].setFieldLabel(_translationMap['GuarAdjEWA']);
				_resources.fields['guarRemGWA'].setFieldLabel(_translationMap['GuarRemEWA']);
				_resources.fields['guarDPAAtAge'].setFieldLabel(_translationMap['GuarDPAAtAge'] + " " + _firstDPAAge + " (" + _firstDPAYear + ")");
			}

			//defaults GWA label					
		}
	}
	
	function clearListOfTerms()
	{
		_resources.grids['listOfTerms'].clearData();
	}
	
	function populateTransaction(responseXML, more)
	{		
		if (more)
		{
			_resources.grids['transaction'].appendData(IFDS.Xml.getNode(responseXML, "//TxnEventList"));
		}
		else
		{
			_resources.grids['transaction'].loadData(IFDS.Xml.getNode(responseXML, "//TxnEventList"));
		}
	}
	
	function clearTransaction()
	{
		_resources.grids['transaction'].clearData();
	}
	
	function populateGuaranteeImpact(responseXML)
	{
        _resources.grids['guaranteeImpact'].loadData(responseXML);
	}
	
	function clearGuaranteeImpact()
	{
		_resources.grids['guaranteeImpact'].clearData();
	}
	
	function populateDropdowns(responseXML)
	{
		_resources.fields['contractType'].loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName = 'ContractTypeList']"));
		_resources.fields['filterTransactions'].loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName = 'TransactionOptions']"));
		_resources.fields['filterValue'].loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName = 'SegTransTypeList']"));
		_resources.fields['guaranteeToDate'].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/guarAsOfDate")));
		_resources.fields['contractType'].setValue(IFDS.Xml.getNodeValue(responseXML, "//ListSelection[@id = 'ContractTypeList']"));
		_resources.fields['filterTransactions'].setValue(IFDS.Xml.getNodeValue(responseXML, "//ListSelection[@id = 'TransactionOptions']"));
		
		_segGuarInfoReloadXML = responseXML;
	}
	
	function populateAddPopup(responseXML)
	{
		var popup = _resources.popups['transPopup'];
		
		var fundListXML = IFDS.Xml.getNode(responseXML, '*/List[@listName = "FundList"]');
		popup.getField('fundType').loadData(fundListXML);
		
		popup.getField('classType').classLists = {};
		var fundElementNodes = IFDS.Xml.getNodes(fundListXML, 'Element');		
		for (var i = 0; i < fundElementNodes.length; i++)
		{
			var fundCode = IFDS.Xml.getNodeValue(fundElementNodes[i], 'code');
			popup.getField('classType').classLists[fundCode] = IFDS.Xml.getNode(responseXML, '*/List[@listName = "Classes' + fundCode + '"]');
		}
		
		popup.getField('reason').loadData(IFDS.Xml.getNodes(responseXML, "//List[@listName = 'ReasonCodeList']"));
		
		popup.getField('fundType').setValue("");
		popup.getField('classType').setValue("");
		popup.getField('reason').setValue("");
		popup.getField('remarks').setValue("");
		
		popup.getField('account').setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		popup.getField('contractType').setValue(_resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
		popup.getField('settleDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/settleDate")));
		popup.getField('tradeDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/tradeDate")));
		popup.getField('units').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/units"));
		popup.getField('guarDBGPopup').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/dbgAmt"));
		popup.getField('guarDMGPopup').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/dmgAmt"));

		popup.getField('GAGWB').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/gwbAmt"));
		popup.getField('GAGwaEwa').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/calcGWAChgAmt"));
		popup.getField('GAAdjustedGwaEwa').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/gwaOpenChgAmt"));
		popup.getField('GARemainingGwaEwa').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/gwaRemChgAmt"));
		popup.getField('GAGWADeferral').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/gwaDeferOpenBal"));
		popup.getField('GABonusBase').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/bonusChgAmt"));
		popup.getField('GALWA').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/calcLWAChgAmt"));
		popup.getField('GAAdjustedLWA').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/lwaOpenChgAmt"));
		popup.getField('GARemainingLWA').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/lwaRemChgAmt"));
		popup.getField('GARemainingGWADeferral').setValue(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/gwaDeferRemChgAmt"));
	
		popup.getField('guarPBGPopup').setValue('0.00');
		popup.getField('GAGMVBase').setValue('0.00');
		popup.getField('GAGMV').setValue('0.00');
		popup.getField('GASumOfAWDGMV').setValue('0.00');
		popup.getField('GADepleteLimit').setValue('0.00');
		popup.getField('GAGDVBase').setValue('0.00');
		popup.getField('GAGDV').setValue('0.00');
		popup.getField('GASumOfAWDGDV').setValue('0.00');
		popup.getField('GARemDepleteLimit').setValue('0.00');
		
		if (IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/allowFundUpd") == 'no')
		{
			popup.getField('fundType').disableField();
		}
		if (IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/allowClassUpd") == 'no')
		{
			popup.getField('classType').disableField();
		}
		if (IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/allowUnitsUpd") == 'no')
		{
			popup.getField('units').disableField();
		}
		if(_resources.grids['listOfTerms'].getSelectedRecord().data['enableGMWB'].toLowerCase() !="yes")
		{
			popup.getField('GAGWB').disableField();
			popup.getField('GAGwaEwa').disableField();
			popup.getField('GAAdjustedGwaEwa').disableField();
			popup.getField('GARemainingGwaEwa').disableField();
			popup.getField('GAGWADeferral').disableField();
			popup.getField('GABonusBase').disableField();
			popup.getField('GALWA').disableField();
			popup.getField('GAAdjustedLWA').disableField();
			popup.getField('GARemainingLWA').disableField();
			popup.getField('GARemainingGWADeferral').disableField();
		}
		if (IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/allowGWADefer") == 'no')
		{
			popup.getField('GAGWADeferral').disableField();
			popup.getField('GARemainingGWADeferral').disableField();
		}
		
		if(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applDBG") == 'yes')
		{
			popup.getField('guarDBGPopup').enableField();
		}else{
			popup.getField('guarDBGPopup').disableField();
		}
		if(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applDMG") == 'yes')
		{
			popup.getField('guarDMGPopup').enableField();
		}else{
			popup.getField('guarDMGPopup').disableField();
		}
		if(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applPBG") == 'yes')
		{
			popup.getField('guarPBGPopup').enableField();
		}else{
			popup.getField('guarPBGPopup').disableField();
		}
		
		if(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/calcDBG") == 'yes')
		{
			popup.getField('GAGDV').addListener('change', function(){calcDBG()});
			popup.getField('GASumOfAWDGDV').addListener('change', function(){calcDBG()});
		}			
		if(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/calcDMG") == 'yes')
		{
			popup.getField('GAGMV').addListener('change', function(){
				popup.getField('guarDMGPopup').setValue(popup.getField('GAGMV').getValue());
			});
		}			
		if(IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/calcPBG") == 'yes')
		{
			popup.getField('GAGMV').addListener('change', function(){calcPBG()});
			popup.getField('GASumOfAWDGMV').addListener('change', function(){calcPBG()});
		}
		
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applGMVBase") == 'no' ? popup.getField('GAGMVBase').disableField() : popup.getField('GAGMVBase').enableField();
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applGMV") == 'no' ? popup.getField('GAGMV').disableField() : popup.getField('GAGMV').enableField();
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applSumOfAWDGMV") == 'no' ? popup.getField('GASumOfAWDGMV').disableField() : popup.getField('GASumOfAWDGMV').enableField();
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applGDVBase") == 'no' ? popup.getField('GAGDVBase').disableField() : popup.getField('GAGDVBase').enableField();
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applGDV") == 'no' ? popup.getField('GAGDV').disableField() : popup.getField('GAGDV').enableField();
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applSumOfAWDGDV") == 'no' ? popup.getField('GASumOfAWDGDV').disableField() : popup.getField('GASumOfAWDGDV').enableField();
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applDepletingLimit") == 'no' ? popup.getField('GADepleteLimit').disableField() : popup.getField('GADepleteLimit').enableField();
		IFDS.Xml.getNodeValue(responseXML, "//DefaultValues/applRemDepletingLimit") == 'no' ? popup.getField('GARemDepleteLimit').disableField() : popup.getField('GARemDepleteLimit').enableField();
		
		function calcDBG()
		{
			var DBG = popup.getField('GAGDV').getValue() - popup.getField('GASumOfAWDGDV').getValue();
			popup.getField('guarDBGPopup').setValue(DBG);
		}
		function calcPBG()
		{
			var PBG = popup.getField('GAGMV').getValue() - popup.getField('GASumOfAWDGMV').getValue();
			popup.getField('guarPBGPopup').setValue(PBG);
		}
	}
	
	function populateCanPopup(responseXML)
	{
		var popup = _resources.popups['transPopup'];
	
		popup.getField('account').setValue(DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
		popup.getField('contractType').setValue(_resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
		popup.getField('fundType').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/fund"));
		popup.getField('classType').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/class"));
		popup.getField('settleDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/settleDate")));
		popup.getField('tradeDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/deff")));
		popup.getField('units').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/units"));
		popup.getField('guarDBGPopup').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/dbgAmt"));
		popup.getField('guarDMGPopup').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/dmgAmt"));

		popup.getField('GAGWB').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/gwbChgAmt"));
		popup.getField('GAGwaEwa').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/calcGWAChgAmt"));
		popup.getField('GAAdjustedGwaEwa').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/gwaOpenChgAmt"));
		popup.getField('GARemainingGwaEwa').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/gwaRemChgAmt"));
		popup.getField('GAGWADeferral').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/gwaDeferOpenBal"));
		popup.getField('GABonusBase').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/bonusChgAmt"));
		popup.getField('GALWA').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/calcLWAChgAmt"));
		popup.getField('GAAdjustedLWA').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/lwaOpenChgAmt"));
		popup.getField('GARemainingLWA').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/lwaRemChgAmt"));
		popup.getField('GARemainingGWADeferral').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/gwaDeferRemChgAmt"));
		
		popup.getField('guarPBGPopup').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/PBGChgAmt"));
		popup.getField('GAGMVBase').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/GMVBaseChgAmt"));
		popup.getField('GAGMV').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/GMVChgAmt"));
		popup.getField('GASumOfAWDGMV').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/SumOfAWDGMVChgAmt"));
		popup.getField('GADepleteLimit').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/DepletionLimitChgAmt"));
		popup.getField('GAGDVBase').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/GDVBaseChgAmt"));
		popup.getField('GAGDV').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/GDVChgAmt"));
		popup.getField('GASumOfAWDGDV').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/SumOfAWDGDVChgAmt"));
		popup.getField('GARemDepleteLimit').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/RemDepletionLimitChgAmt"));
        
		popup.getField('reason').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/reasonDesc"));
		popup.getField('remarks').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/remarks"));
		
		popup.getField('stat').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/stat"));
		popup.getField('userName').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/userName"));		
		popup.getField('modDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/modDate")));

		popup.getField('modUser').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/modUser"));
		popup.getField('processDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/processDate")));
		popup.getField('processTime').setValue(IFDS.Xml.getNodeValue(responseXML, "//TxnDetail/processTime"));
	}
	
	function populateGWBYearlyPopup(responseXML)
	{				
		if(IFDS.Xml.getNodeValue(responseXML, "//Mstr/IsEWA") == 'yes')
		{
			Ext.getCmp('GWA').setTitle(_translationMap['EWA']);
			if(IFDS.Xml.getNodeValue(responseXML, "//Mstr/LEselect") == 'yes')
			{
				Ext.getCmp('GWA').setDisabled(true);
				Ext.getCmp('LWA').setDisabled(false);
				Ext.getCmp('GWB').setActiveTab(1);
				_resources.grids['lwa'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'LWAList']"));
			}
			else
			{				
				Ext.getCmp('GWA').setDisabled(false);
				Ext.getCmp('LWA').setDisabled(true);
				Ext.getCmp('GWB').setActiveTab(0);
				_resources.grids['gwa'].getColumnModel().setColumnHeader(1,_translationMap['CalcEWA']);
				_resources.grids['gwa'].getColumnModel().setColumnHeader(3,_translationMap['GuarAdjEWA']);
				_resources.grids['gwa'].getColumnModel().setColumnHeader(4,_translationMap['RemainEWA']);
				_resources.grids['gwa'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'GWAList']"));
			}														
		}	
		else if(IFDS.Xml.getNodeValue(responseXML, "//Mstr/IsGWA") == 'yes')
		{
			Ext.getCmp('GWA').setTitle(_translationMap['GuarGWA']);
			if(IFDS.Xml.getNodeValue(responseXML, "//Mstr/LEselect") == 'yes')
			{
				Ext.getCmp('LWA').setDisabled(false);				
				gwaTab(responseXML);
				_resources.grids['lwa'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'LWAList']"));
			}
			else
			{
				Ext.getCmp('LWA').setDisabled(true);				
				gwaTab(responseXML);
			}			
		}
		else
		{
			if(IFDS.Xml.getNodeValue(responseXML, "//Mstr/LEselect") == 'yes')
			{
				Ext.getCmp('LWA').setDisabled(false);				
				Ext.getCmp('GWA').setDisabled(true);
				Ext.getCmp('GWB').setActiveTab(1);
				_resources.grids['lwa'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'LWAList']"));
			}
		}				
	}
	
	function gwaTab(responseXML)
	{
		Ext.getCmp('GWA').setDisabled(false);
		Ext.getCmp('GWB').setActiveTab(0);								
		_resources.grids['gwa'].getColumnModel().setColumnHeader(1,_translationMap['CalcGWA']);
		_resources.grids['gwa'].getColumnModel().setColumnHeader(3,_translationMap['GuarAdjGWA']);
		_resources.grids['gwa'].getColumnModel().setColumnHeader(4,_translationMap['RemainGWA']);
		_resources.grids['gwa'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName = 'GWAList']"));
	}
	
	function formatGuaranteeRuleXML(xml)
	{
		var mstrXMLNodes = IFDS.Xml.getNodes(xml, 'TxnDetails');
		
		for (var m = 0; m < mstrXMLNodes.length; m++)
		{
			IFDS.Xml.addAttribute(mstrXMLNodes[m], 'recordSource', m + 1);
			
			var detlXMLNodes = IFDS.Xml.getNodes(mstrXMLNodes[m], 'GuaranteeImpactDetl/ImpactDetl');
			IFDS.Xml.addSingleNode(mstrXMLNodes[m], 'num', detlXMLNodes.length);
			
			for (var d = 0; d < detlXMLNodes.length; d++)
			{
				IFDS.Xml.addAttribute(detlXMLNodes[d], 'recordSource', (m + 1) + ":" + (d + 1));
				IFDS.Xml.addSingleNode(detlXMLNodes[d], 'num', m+1);
			}
		}
		return xml;
	}
	
	function getUpdatedRecordCount(grid)
	{
		if (_resources.grids[grid] == null || _resources.grids[grid].getStore() == null)
		{
			return 0;
		}
		var store = _resources.grids[grid].getStore();
		var newRecords = store.query('runMode', _self.ADD);	
		var modRecords = store.query('runMode', _self.CANC);		
		var delRecords = store.query('runMode', _self.DEL);
		return newRecords.length + modRecords.length + delRecords.length;
	}
	
	function sendCancelRolloverValidationRequest(segGuarAdjustID, callback)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, "segGuarDetlUUID", segGuarAdjustID);
		
		DesktopWeb.Ajax.doSmartviewAjax(_cancelRolloverValidationView, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])
		
		function responseHandler(success, responseXML)
		{							
			callback(success); 					
		}
	}
	
	function populateIncomeBaseDetlPopup(responseXML)
	{
		var popup = _resources.popups['incomeBaseDetlPopup'];					
		
		var title = _translationMap['TransIncBaseDetlTitle'] + ": " + DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] + " " + DesktopWeb._SCREEN_PARAM_MAP['EntityName'];
						
		popup.init(title);		
		
		popup.getField('taxTypeDesc').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseInfo/taxTypeDesc"));																
		popup.getField('transTypeDesc').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseInfo/transTypeDesc"));
		popup.getField('tradeDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseInfo/tradeDate")));					
		popup.getField('transNumber').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseInfo/transNumber"));		
		popup.getField('guarPayOptDesc').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseInfo/guarPayOptDesc"));		
		popup.getField('electionAge').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseInfo/electionAge"));							
		popup.getField('electionDate').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseInfo/electionDate")));																
		popup.getField('nameMeasure').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/nameMeasure"));							
		popup.getField('ageMeasure').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/ageMeasure"));
		popup.getField('statMeasure').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/statMeasure"));
		popup.getField('dofbMeasure').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/dofbMeasure")));	
		popup.getField('nameElection').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/nameElection"));																											 									
		popup.getField('ageElection').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/ageElection"));		
		popup.getField('statElection').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/statElection"));	
		popup.getField('dofbElection').setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, "//SegIncmBaseList/SegIncmBaseDetl/dofbElection")));
					
		_resources.grids['SegIncmBaseGrid'].getStore().removeAll();														
		_resources.grids['SegIncmBaseGrid'].getStore().loadData(IFDS.Xml.getNode(responseXML, "//SegIncmBaseList"));		
													
		popup.show();				
		
		if(_resources.grids['SegIncmBaseGrid'].getStore().getCount() > 0) 
		{			
			_resources.grids['SegIncmBaseGrid'].selectFirstRecord();																																	
		}																										
	} 				
	
	function populateDeferredIncDetlPopup(responseXML)
	{
		var popup = _resources.popups['deferredIncDetlPopup'];
		
		var title = _translationMap['DefIncDetlTitle'] + ": " + DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] + " " + _translationMap['Shareholder'] + ": " + DesktopWeb._SCREEN_PARAM_MAP['EntityName'];
				
		popup.init(title);		
		
		_resources.grids['SegDIAGrid'].getStore().removeAll();	
		_resources.grids['SegPenIncmBaseGrid'].getStore().removeAll();
		_resources.grids['SegDIATransactionGrid'].getStore().removeAll();
		
		if (_defaultAsOfDate) {		
			// No need to convert the format from Guaranteetodate as it is already the display format
			_resources.fields['asOfDate'].setValue(_resources.fields['guaranteeToDate'].getValue());
		}

		_asOfDate = _resources.fields['asOfDate'].getDisplayDateString();														

		popup.getField('nmcrIncmCr').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/nmcrIncmCr"));																
		popup.getField('nmcrMKV').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/nmcrMKV"));

		popup.getField('nonNMCRInmCr').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/nonNMCRInmCr"));		
		popup.getField('nonNMCRMKV').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/nonNMCRMKV"));		

		popup.getField('totIncmBase').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/totIncmBase"));						
		popup.getField('totLWABase').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/totLWABase"));						
																
		popup.getField('contractTypeDIA').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/contractTypeDIA"));
		popup.getField('versionDIA').setValue(IFDS.Xml.getNodeValue(responseXML, "//SegDIAInfo/versionDIA"));
		
		_resources.grids['SegDIAGrid'].getStore().loadData(IFDS.Xml.getNode(responseXML, "//SegDIAList"));
		
		popup.show();					
		
		if(_resources.grids['SegDIAGrid'].getStore().getCount() > 0) 
		{			
			_resources.grids['SegDIAGrid'].selectFirstRecord();	
		}										

		if (_resources.grids['listOfTerms'].getSelectedRecord().data['isNMCRContract'].toUpperCase() == "NO")
		{
			popup.disableButton('incBaseDetlBtn');						
			_resources.grids['SegPenIncmBaseGrid'].hide();
			_resources.grids['SegDIATransactionGrid'].hide();
			return;
							
		} 
		else 
		{					
			if (_resources.grids['transaction'].getStore().getCount() > 0)
			{
				popup.enableButton('incBaseDetlBtn');
			}
			else
			{
				popup.disableButton('incBaseDetlBtn');
			}

			if (_resources.grids['listOfTerms'].getSelectedRecord().data['isElected'].toUpperCase() == "YES") {			
				_resources.grids['SegPenIncmBaseGrid'].getColumnModel().setColumnHeader(5, _translationMap['Dialwa'].split('/')[1]);
			}
			_self.loadSegPenIncmBaseGrid();	
			_resources.grids['SegPenIncmBaseGrid'].show();
			_self.populateSegDIATransactionGrid();											
			_resources.grids['SegDIATransactionGrid'].show();						
		}			
		
	}		
	
	function loadSegDIATransactionGrid(responseXML)
	{		
		_resources.grids['SegDIATransactionGrid'].getStore().loadData(IFDS.Xml.getNode(responseXML, "//SegDIATransactions"));

		if(_resources.grids['SegDIATransactionGrid'].getStore().getCount() > 0) 
		{			
			_resources.grids['SegDIATransactionGrid'].selectFirstRecord();										
		}

	}
		
	 
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'mod'
		,DEL: 'del'
		,CANC: 'canc'
		
		,updatesFlag: false
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			_actionScreen = 'init';
			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, "account", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);																		
					
			DesktopWeb.Ajax.doSmartviewAjax(_guarInfoReloadView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])
			
			function responseHandler(success, responseXML)
			{															
				if (success)
				{
					storePermissions(responseXML);
					populateDropdowns(responseXML);
					_self.doLookupMstr();
					_resources.fields['filterTransactions'].setDisabled(false);
					_resources.buttons['filterButton'].setDisabled(false);
				}
				else{
					Ext.getCmp('YearlyGWB').setDisabled(true);
				}
			}
		}
		
		,doLookupMstr: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');
			_self.updatesFlag = false;
			_GATransUpdate = false;
			_MR_CM_cancel = false;
			_resources.grids['transaction'].enableButton('addBtn');
			IFDS.Xml.addSingleNode(dataXML, "account", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, 'guarAsOfDate', DesktopWeb.Util.getSMVDateValue(_resources.fields['guaranteeToDate'].getDisplayDateString()));
			IFDS.Xml.addSingleNode(dataXML, 'contractType', _resources.fields['contractType'].getValue());
			
			DesktopWeb.Ajax.doSmartviewAjax(_guarInfoReloadView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])				
			
			function responseHandler(success, responseXML)			
			{								
				if (success)
				{
					_mstrReloadXML = responseXML;
					populateGuaranteeInfo(responseXML);
					populateListOfTerms(responseXML);
				}
				else
				{
					Ext.getCmp('YearlyGWB').setDisabled(true);
					clearGuaranteeInfo();
					clearListOfTerms();
				}
			}
		}
		
		,getDefaultYear: function()
		{
			return IFDS.Xml.getNodeValue(_mstrReloadXML, "//DefaultValues/defaultYear");
		}
		
		,doLookupDetl: function(more)
		{
			if (!_resources.grids['listOfTerms'].getSelectedRecord())
			{
				return;
			}			
		
			_self.updatesFlag = false;
			_GATransUpdate = false;
			_MR_CM_cancel = false;
			_resources.grids['transaction'].enableButton('addBtn');
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, 'contractType', _resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
			IFDS.Xml.addSingleNode(dataXML, 'contractTypeID', _resources.grids['listOfTerms'].getSelectedRecord().data['contractTypeID']);
			IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
			IFDS.Xml.addSingleNode(dataXML, 'searchBy', _resources.fields['filterTransactions'].getValue());
			IFDS.Xml.addSingleNode(dataXML, 'transType', _resources.fields['filterValue'].getValue());
			IFDS.Xml.addSingleNode(dataXML, 'guarAsOfDate', DesktopWeb.Util.getSMVDateValue(_resources.fields['guaranteeToDate'].getDisplayDateString()));
			if (_resources.fields['filterDate'].getValue() == "")
			{
				IFDS.Xml.addSingleNode(dataXML, 'txnYear', "0");
			}
			else
			{
				IFDS.Xml.addSingleNode(dataXML, 'txnYear', _resources.fields['filterDate'].getValue());
			}
			IFDS.Xml.addSingleNode(dataXML, 'startRecNum', (more ? _nextStartRecNum : 1));
			IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', 100);			
			
			_resources.grids['transaction'].disableButton('cancBtn');
			_resources.grids['transaction'].disableButton('delBtn');

			_resources.grids['transaction'].clearData();						

			/* Use flag to ignore an error 'No data found' while launching the screen */
			if (_actionScreen == 'init')
			{
				DesktopWeb.Ajax.doSmartviewAjax(_txnEventsReloadView, {ignoreErrorCode: '15'}, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
				_actionScreen = null;
			}
			else
			{
				DesktopWeb.Ajax.doSmartviewAjax(_txnEventsReloadView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
			}			
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					if (!more)
					{
						_updateXML = IFDS.Xml.newDocument('Data');
					}
					var infoXML = IFDS.Xml.getNode (responseXML, "//TxnEventList");
					if (infoXML != null)
					{
						formatGuaranteeRuleXML(infoXML);
						populateTransaction(responseXML, more);
						populateGuaranteeImpact(responseXML);
						if (IFDS.Xml.getNodeValue(responseXML, '/*//RecordRange/moreRecordsExist').toLowerCase() == 'yes')
						{
							_resources.grids['transaction'].enableButton('moreBtn');
							_nextStartRecNum = IFDS.Xml.getNodeValue(responseXML, '/*//RecordRange/rangeStartForNext');						
						}
						else
						{
							_resources.grids['transaction'].disableButton('moreBtn');
							_nextStartRecNum = null;
						}						
						if (_permissionsMap[_self.ADD])
						{							
							_resources.grids['transaction'].enableButton('addBtn');
						}
						
						if (_resources.grids['transaction'].getStore().getCount() == 0)
						{
							_resources.grids['transaction'].disableButton('incBaseDetlBtn');
						}
					}
				}
				else
				{
					_resources.grids['transaction'].loadData(IFDS.Xml.newDocument('TxnEventList'));
					_resources.grids['guaranteeImpact'].loadData(IFDS.Xml.newDocument('GuaranteeImpactDetl'));
					_resources.grids['transaction'].enableButton('addBtn');
				}
			}
								
			if (_resources.grids['listOfTerms'].getSelectedRecord().data['isNMCRContract'].toUpperCase() == "YES")
			{		
				_resources.fields['guarIncBaseLWA'].show();				
				_resources.grids['transaction'].enableButton('incBaseDetlBtn');				
			} else {
				_resources.fields['guarIncBaseLWA'].hide();
				_resources.grids['transaction'].disableButton('incBaseDetlBtn');	
			}
					
			if (_resources.grids['listOfTerms'].getSelectedRecord().data['isNMCRContract'].toUpperCase() == "YES" && 
		    		_resources.grids['listOfTerms'].getSelectedRecord().data['isElected'].toUpperCase() == "NO")
			{
				_resources.fields['guarDPAAtAge'].setFieldLabel(
					_translationMap['GuarDPAAtAge'] + " " +  
					_resources.grids['listOfTerms'].getSelectedRecord().data['firstDPAAge'] + " (" + 
					_resources.grids['listOfTerms'].getSelectedRecord().data['firstDPAYear'] + ")");
				_resources.fields['guarDPAAtAge'].show();

				_resources.fields['guarLWAEntitlement'].hide();	
			}
			else
			{
				_resources.fields['guarDPAAtAge'].hide();

				if (_resources.grids['listOfTerms'].getSelectedRecord().data['isNMCRContract'].toUpperCase() == "YES" && 
		    		    _resources.grids['listOfTerms'].getSelectedRecord().data['isElected'].toUpperCase() == "YES") 				   
				{
					_resources.fields['guarLWAEntitlement'].show();
				} else {
					_resources.fields['guarLWAEntitlement'].hide();
				}
			}

			if (_resources.grids['listOfTerms'].getSelectedRecord().data['incCreditApp'].toUpperCase() == "YES") 
			{			
				_resources.fields['guarIncCredit'].show();
			}
			else
			{
				_resources.fields['guarIncCredit'].hide();
			}	
		}
		
		,clearDetails: function()
		{
			clearTransaction();
			clearGuaranteeImpact();
		}
		
		,doLookupAddBtn: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, "account", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, 'contractType', _resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
			IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
						
			DesktopWeb.Ajax.doSmartviewAjax(_addTxnReloadView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])
			
			function responseHandler(success, responseXML)
			{							
				if (success)
				{
					_addDataXML = responseXML;				
					populateAddPopup(responseXML);
				}
				else
				{
					_resources.popups['transPopup'].hide();
				}
			}
		}
		
		,saveAddTransaction: function(action)
		{
			var updateStatus = false;
			if (action == this.ADD)
			{
				var dataXML = IFDS.Xml.newDocument('Txn');
				IFDS.Xml.addSingleNode(dataXML, "runMode", action);
				IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.popups['transPopup'].getField('contractType').getValue());
				IFDS.Xml.addSingleNode(dataXML, "account", _resources.popups['transPopup'].getField('account').getValue());
				IFDS.Xml.addSingleNode(dataXML, "tradeDate", 
					DesktopWeb.Util.getSMVDateValue(_resources.popups['transPopup'].getField('tradeDate').getDisplayDateString()));
				IFDS.Xml.addSingleNode(dataXML, "fund", _resources.popups['transPopup'].getField('fundType').getValue());
				IFDS.Xml.addSingleNode(dataXML, "class", _resources.popups['transPopup'].getField('classType').getValue());
				IFDS.Xml.addSingleNode(dataXML, "settleDate", 
					DesktopWeb.Util.getSMVDateValue(_resources.popups['transPopup'].getField('tradeDate').getDisplayDateString()));
				IFDS.Xml.addSingleNode(dataXML, "dbgAmt", _resources.popups['transPopup'].getField('guarDBGPopup').getValue());
				IFDS.Xml.addSingleNode(dataXML, "dmgAmt", _resources.popups['transPopup'].getField('guarDMGPopup').getValue());
				
				IFDS.Xml.addSingleNode(dataXML, "gwbChgAmt", _resources.popups['transPopup'].getField('GAGWB').getValue());
				IFDS.Xml.addSingleNode(dataXML, "gwaOpenChgAmt", _resources.popups['transPopup'].getField('GAAdjustedGwaEwa').getValue());
				IFDS.Xml.addSingleNode(dataXML, "calcGWAChgAmt", _resources.popups['transPopup'].getField('GAGwaEwa').getValue());
				IFDS.Xml.addSingleNode(dataXML, "gwaRemChgAmt", _resources.popups['transPopup'].getField('GARemainingGwaEwa').getValue());								
				IFDS.Xml.addSingleNode(dataXML, "gwaDeferOpenBal", _resources.popups['transPopup'].getField('GAGWADeferral').getValue());
				IFDS.Xml.addSingleNode(dataXML, "bonusChgAmt", _resources.popups['transPopup'].getField('GABonusBase').getValue());
				IFDS.Xml.addSingleNode(dataXML, "lwaOpenChgAmt", _resources.popups['transPopup'].getField('GAAdjustedLWA').getValue());
				IFDS.Xml.addSingleNode(dataXML, "calcLWAChgAmt", _resources.popups['transPopup'].getField('GALWA').getValue());
				IFDS.Xml.addSingleNode(dataXML, "lwaRemChgAmt", _resources.popups['transPopup'].getField('GARemainingLWA').getValue());
				IFDS.Xml.addSingleNode(dataXML, "gwaDeferRemChgAmt", _resources.popups['transPopup'].getField('GARemainingGWADeferral').getValue());

				IFDS.Xml.addSingleNode(dataXML, "gmvBaseChgAmt", _resources.popups['transPopup'].getField('GAGMVBase').getValue());
				IFDS.Xml.addSingleNode(dataXML, "gmvChgAmt", _resources.popups['transPopup'].getField('GAGMV').getValue());
				IFDS.Xml.addSingleNode(dataXML, "sumOfAWDGMVChgAmt", _resources.popups['transPopup'].getField('GASumOfAWDGMV').getValue());
				IFDS.Xml.addSingleNode(dataXML, "pbgChgAmt", _resources.popups['transPopup'].getField('guarPBGPopup').getValue());
				IFDS.Xml.addSingleNode(dataXML, "gdvBaseChgAmt", _resources.popups['transPopup'].getField('GAGDVBase').getValue());								
				IFDS.Xml.addSingleNode(dataXML, "gdvChgAmt", _resources.popups['transPopup'].getField('GAGDV').getValue());
				IFDS.Xml.addSingleNode(dataXML, "sumOfAWDGDVChgAmt", _resources.popups['transPopup'].getField('GASumOfAWDGDV').getValue());
				IFDS.Xml.addSingleNode(dataXML, "depleteLimitChgAmt", _resources.popups['transPopup'].getField('GADepleteLimit').getValue());
				IFDS.Xml.addSingleNode(dataXML, "remDepleteLimitChgAmt", _resources.popups['transPopup'].getField('GARemDepleteLimit').getValue());
				
				IFDS.Xml.addSingleNode(dataXML, "units", _resources.popups['transPopup'].getField('units').getValue());
				IFDS.Xml.addSingleNode(dataXML, "reason", _resources.popups['transPopup'].getField('reason').getValue());
				IFDS.Xml.addSingleNode(dataXML, "remarks", _resources.popups['transPopup'].getField('remarks').getValue());
				IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
				IFDS.Xml.addSingleNode(dataXML, 'num',_mstrID);
				
			}
			else
			{
				var dataXML = IFDS.Xml.newDocument('Txn');
				IFDS.Xml.addSingleNode(dataXML, "runMode", action);
				IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.popups['transPopup'].getField('contractType').getValue());
				IFDS.Xml.addSingleNode(dataXML, "account", _resources.popups['transPopup'].getField('account').getValue());
				IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
				IFDS.Xml.addSingleNode(dataXML, 'segGuarAdjustID', _resources.grids['transaction'].getSelectedRecord().data['segGuarAdjustID']);
				IFDS.Xml.addSingleNode(dataXML, "remarks", _resources.popups['transPopup'].getField('remarks').getValue());
				IFDS.Xml.addSingleNode(dataXML, "modRemarks", _resources.popups['transPopup'].getField('modRemarks').getValue());			
			}
			
			DesktopWeb.Ajax.doSmartviewUpdate(_txnVldtnsView, null, dataXML, responseHandler, _translationMap['ProcMsg_Processing'])
			return updateStatus;
			
			function responseHandler(success, responseXML)
			{
				updateStatus = success;
				if (success)
				{
					_GATransUpdate = true;
					IFDS.Xml.appendNode (_updateXML, dataXML);
				}
			}
		}
		
		,doUpdate: function()
		{			
			var updateStatus = false;
			if (_MR_CM_cancel)
			{								
				var dataXML = IFDS.Xml.newDocument('data');
				var transRecordIndex = _resources.grids['transaction'].getStore().findExact('runMode', _self.CANC);
				var transRecord = _resources.grids['transaction'].getStore().getAt(transRecordIndex);
				var view = (transRecord.data['transType'] == "MR" ? _segCxlMRUpdView : _segCxlCMUpdView );
				DesktopWeb.Ajax.doSmartviewUpdate(view, null, 
					IFDS.Xml.stringToXML("<data><segGuarDetlUUID>" + transRecord.data['segGuarDetlUUID'] + "</segGuarDetlUUID></data>"), 
					responseHandler1, null);
			}
			
			if (_GATransUpdate)			
			{
				DesktopWeb.Ajax.doSmartviewUpdate(_segTxnUpdateView, null, _updateXML, responseHandler2, null)
			}
			
			function responseHandler1(success, responseXML)
			{				
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{
					updateStatus = DesktopWeb._FAIL
				}
			}			
			function responseHandler2(success, responseXML)
			{				
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}
				else
				{
					updateStatus = DesktopWeb._FAIL
				}
			}
			return updateStatus;
		}
		
		,getPermission: function(value)
		{
			return _permissionsMap[value];
		}
		
		,doCommitAddBtn: function()
		{			
			var dataXML = IFDS.Xml.newDocument('Txn');
			IFDS.Xml.addSingleNode(dataXML, "runMode", 'add');
			IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.popups['transPopup'].getField('contractType').getValue());
			IFDS.Xml.addSingleNode(dataXML, "account", _resources.popups['transPopup'].getField('account').getValue());
			IFDS.Xml.addSingleNode(dataXML, "tradeDate", 
				DesktopWeb.Util.getSMVDateValue(_resources.popups['transPopup'].getField('tradeDate').getDisplayDateString()));
			IFDS.Xml.addSingleNode(dataXML, "fund", _resources.popups['transPopup'].getField('fundType').getValue());
			IFDS.Xml.addSingleNode(dataXML, "class", _resources.popups['transPopup'].getField('classType').getValue());
			IFDS.Xml.addSingleNode(dataXML, "settleDate", 
				DesktopWeb.Util.getSMVDateValue(_resources.popups['transPopup'].getField('tradeDate').getDisplayDateString()));
			IFDS.Xml.addSingleNode(dataXML, "dbgAmt", _resources.popups['transPopup'].getField('guarDBGPopup').getValue());
			IFDS.Xml.addSingleNode(dataXML, "dmgAmt", _resources.popups['transPopup'].getField('guarDMGPopup').getValue());
			IFDS.Xml.addSingleNode(dataXML, "units", _resources.popups['transPopup'].getField('units').getValue());
			IFDS.Xml.addSingleNode(dataXML, "reason", _resources.popups['transPopup'].getField('reason').getValue());
			IFDS.Xml.addSingleNode(dataXML, "remarks", _resources.popups['transPopup'].getField('remarks').getValue());
			IFDS.Xml.addSingleNode(dataXML, "modRemarks", _resources.popups['transPopup'].getField('modRemarks').getValue());
			IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
			
			DesktopWeb.Ajax.doSmartviewAjax(_txnVldtnsView, null, dataXML, responseHandler, "Searching ...")
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					_resources.popups['transPopup'].hide();
				}
			}
		}
		
		,doLookupCanBtn: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, "account", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, 'contractType', _resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
			IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
			IFDS.Xml.addSingleNode(dataXML, 'segGuarAdjustID', _resources.grids['transaction'].getSelectedRecord().data['segGuarAdjustID']);
						
			DesktopWeb.Ajax.doSmartviewAjax(_canTxnReloadView, null, dataXML, responseHandler, _translationMap["ProcMsg_Loading"]);
			
			function responseHandler(success, responseXML)
			{				
				if (success)
				{
					populateCanPopup(responseXML);
				}
			}
		}
		
		,openActionPopup: function(action, grid, popup)
		{
			if (action == this.ADD)
			{
				_resources.grids[grid].clearSelectedRecord();
			}
			
			_resources.popups[popup].init(action);
			_resources.popups[popup].show();
		}
		
		,savePopup: function(action, data, grid)
		{
			var success = true;

			if (action == this.ADD)
			{
				_resources.grids[grid].addRecord(data);
				_resources.grids[grid].selectLastRecord();
			}
			
			else if (action == this.CANC)
			{
				data['adjustStat'] = _translationMap["CancelRequested"];
				_resources.grids[grid].updateSelectedRecord(data);
			}
			else
			{
				var tempXML = IFDS.Xml.getNode(_updateXML, "//Txn[num = '" + _resources.grids[grid].getSelectedRecord().data['num'] +"']");
				IFDS.Xml.deleteNode (tempXML);
				_resources.grids[grid].removeSelectedRecord();
				_resources.grids[grid].selectFirstRecord();
			}
			this.updatesFlag = (getUpdatedRecordCount('transaction') > 0);
			return success;
		}
		
		,openGWBYearlyPopup: function(more)
		{
			var dataXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(dataXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, 'contractType', _resources.grids['listOfTerms'].getSelectedRecord().data['contract']);			
			IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);			
			IFDS.Xml.addSingleNode(dataXML, 'startRecNum', (more ? _nextStartRecNum : 1));
			IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', 100);
			
			DesktopWeb.Ajax.doSmartviewAjax('dtGWBYearlyReload', null, dataXML, responseHandler, "Searching ...")
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					populateGWBYearlyPopup(responseXML);
				}
			}			
		}
		
		,handleTransRecordSelectionChange: function()
		{
			var transRecord = _resources.grids['transaction'].getSelectedRecord();
			if (transRecord)
			{
				_resources.grids['guaranteeImpact'].getStore().filterBy(function(rec){
					if (_self.isAppGuarImpact(rec))
					{
						return rec.data.recordSource.split(":", 1) == transRecord.data.recordSource;
					}
					else
					{
						return false;
					}
				});
				
				if (transRecord.data.runMode == _self.ADD)
				{
					_resources.grids['transaction'].enableButton('delBtn');
				}
				else
				{
					_resources.grids['transaction'].disableButton('delBtn');
				}
				
				
				if (transRecord.data.enableCanc == 'yes' 
					&& _self.getPermission(_self.CANC)
					&& transRecord.data['segGuarAdjustID'] != ""
					&& (!_self.updatesFlag || (_GATransUpdate && transRecord.data['transType'] == 'GA')))					
				{
					_resources.grids['transaction'].enableButton('cancBtn');
				}
				else
				{
					_resources.grids['transaction'].disableButton('cancBtn');
				}
			}
			else
			{
				_resources.grids['transaction'].disableButton('cancBtn');
				_resources.grids['transaction'].disableButton('delBtn');
				_resources.grids['guaranteeImpact'].getStore().filterBy(function(rec){return false});			
			}

			_resources.grids['guaranteeImpact'].selectFirstRecord();
		}
		
		,clearAllFields: function()
		{
			populateAddPopup(_addDataXML);
		}
		
		,emptyUpdateXML: function()
		{
			_updateXML = IFDS.Xml.newDocument('Data');
		}
		
		,getNum: function()
		{
			_mstrID ++;
			return _mstrID - 1;
		}
		
		,updateFilterFields: function()
		{
			var filterTransType = _resources.fields['filterTransactions'].getValue();		
			if (filterTransType == "TType")
			{
				_resources.fields['filterValue'].show();
				_resources.fields['filterDate'].hide();
				_resources.fields['filterDate'].reset();
			}
			else if (filterTransType == "Year")
			{
				_resources.fields['filterDate'].setValue(_self.getDefaultYear());
				_resources.fields['filterValue'].hide();
				_resources.fields['filterDate'].show();
				_resources.fields['filterValue'].reset();
			}
			else
			{
				_resources.fields['filterValue'].hide();
				_resources.fields['filterDate'].hide();
				_resources.fields['filterValue'].reset();
				_resources.fields['filterDate'].reset();
			}			
		}
		
		,filterGuaranteeImpact: function()
		{
			_resources.grids['guaranteeImpact'].getStore.filterBy(function(record){
				return record.data.num == _grids['transaction'].getSelectedRecord().data['recordSource']
			});
		}
		
		,cancelTxn: function()
		{
			var selectedTransRecord = _resources.grids['transaction'].getSelectedRecord();
			if (selectedTransRecord)
			{
				if (selectedTransRecord.data['transType'] == 'GA')
				{
					_self.openActionPopup(_self.CANC, 'transaction', 'transPopup');
				}
				else
				{
					sendCancelRolloverValidationRequest(selectedTransRecord.data['segGuarDetlUUID'], rolloverCallback)
				}
			}
			else
			{
				throw new Error("No transaction record selected");
			}
			
			function rolloverCallback(successful)
			{
				if (successful)
				{
					_self.updatesFlag = true;
					_MR_CM_cancel = true;									
					selectedTransRecord.data['adjustStat'] = _translationMap["CancelRequested"];
					selectedTransRecord.data['runMode'] = _self.CANC;
					_resources.grids['transaction'].updateSelectedRecord(selectedTransRecord.data);
					_self.handleTransRecordSelectionChange();
					_resources.grids['transaction'].disableButton('addBtn');
				}
			}
		}
		,disableGAFields: function(){

			_resources.popups['transPopup'].getField('guarDBGPopup').setValue('0.0');
			_resources.popups['transPopup'].getField('guarDMGPopup').setValue('0.0');
			_resources.popups['transPopup'].getField('guarPBGPopup').setValue('0.0');
			_resources.popups['transPopup'].getField('GAGWB').setValue('0.0');
			_resources.popups['transPopup'].getField('GAGwaEwa').setValue('0.0');
			_resources.popups['transPopup'].getField('GAAdjustedGwaEwa').setValue('0.0');
			_resources.popups['transPopup'].getField('GARemainingGwaEwa').setValue('0.0');
			_resources.popups['transPopup'].getField('GAGWADeferral').setValue('0.0');
			_resources.popups['transPopup'].getField('GABonusBase').setValue('0.0');
			_resources.popups['transPopup'].getField('GALWA').setValue('0.0');
			_resources.popups['transPopup'].getField('GAAdjustedLWA').setValue('0.0');
			_resources.popups['transPopup'].getField('GARemainingLWA').setValue('0.0');
			_resources.popups['transPopup'].getField('GARemainingGWADeferral').setValue('0.0');
			_resources.popups['transPopup'].getField('GAGMVBase').setValue('0.0');
			_resources.popups['transPopup'].getField('GAGMV').setValue('0.0');
			_resources.popups['transPopup'].getField('GASumOfAWDGMV').setValue('0.0');
			_resources.popups['transPopup'].getField('GADepleteLimit').setValue('0.0');
			_resources.popups['transPopup'].getField('GAGDVBase').setValue('0.0');
			_resources.popups['transPopup'].getField('GAGDV').setValue('0.0');
			_resources.popups['transPopup'].getField('GASumOfAWDGDV').setValue('0.0');
			_resources.popups['transPopup'].getField('GARemDepleteLimit').setValue('0.0');
	
			_resources.popups['transPopup'].getField('guarDBGPopup').disableField();
			_resources.popups['transPopup'].getField('guarDMGPopup').disableField();
			_resources.popups['transPopup'].getField('guarPBGPopup').disableField();
			_resources.popups['transPopup'].getField('GAGWB').disableField();
			_resources.popups['transPopup'].getField('GAGwaEwa').disableField();
			_resources.popups['transPopup'].getField('GAAdjustedGwaEwa').disableField();
			_resources.popups['transPopup'].getField('GARemainingGwaEwa').disableField();
			_resources.popups['transPopup'].getField('GAGWADeferral').disableField();
			_resources.popups['transPopup'].getField('GABonusBase').disableField();
			_resources.popups['transPopup'].getField('GALWA').disableField();
			_resources.popups['transPopup'].getField('GAAdjustedLWA').disableField();
			_resources.popups['transPopup'].getField('GARemainingLWA').disableField();
			_resources.popups['transPopup'].getField('GARemainingGWADeferral').disableField();
			_resources.popups['transPopup'].getField('GAGMVBase').disableField();
			_resources.popups['transPopup'].getField('GAGMV').disableField();
			_resources.popups['transPopup'].getField('GASumOfAWDGMV').disableField();
			_resources.popups['transPopup'].getField('GADepleteLimit').disableField();
			_resources.popups['transPopup'].getField('GAGDVBase').disableField();
			_resources.popups['transPopup'].getField('GAGDV').disableField();
			_resources.popups['transPopup'].getField('GASumOfAWDGDV').disableField();
			_resources.popups['transPopup'].getField('GARemDepleteLimit').disableField();
		}	

		, isAppGuarImpact: function (rec)
		{
			if (rec.data.name == "Income Credit" && 
				!(_isNMCRContract.toUpperCase() == "YES" || _incCreditApp.toUpperCase() == "YES"))
			{
				return false;
			}
			else {
				return true;
			}
		}		
		
		,openIncomeBaseDetlPopup: function(electionAge, transID, SegGuarDetlUUID)
		{						
			var dataXML = IFDS.Xml.newDocument('data');								

			IFDS.Xml.addSingleNode(dataXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);								
			IFDS.Xml.addSingleNode(dataXML, 'electionAge', electionAge);
			IFDS.Xml.addSingleNode(dataXML, 'transID', transID);											
			IFDS.Xml.addSingleNode(dataXML, 'SegGuarDetlUUID', SegGuarDetlUUID);
								
			DesktopWeb.Ajax.doSmartviewAjax(_segIncmBaseReloadView , null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);							

			function responseHandler(success, responseXML)
			{
				DesktopWeb.Util.debugXML(responseXML);
				if (success)
				{						
					_segIncmBaseXML = responseXML;
					populateIncomeBaseDetlPopup(responseXML);										
				}
			}				
		}

		,populateWithSelectedSegIncmBaseRecord: function()
		{			
			var selectedRecord = _resources.grids['SegIncmBaseGrid'].getSelectedRecord();								

			if (selectedRecord) 
			{
				var recordIndex = _resources.grids['SegIncmBaseGrid'].getRecordIndex(selectedRecord);												
				var rec = _resources.grids['SegIncmBaseGrid'].getStore().getAt(recordIndex);				
				
				if (rec) 
				{										
					var popup = _resources.popups['incomeBaseDetlPopup'];	
																													
					popup.getField('nameMeasure').setValue(selectedRecord.data['nameMeasure']);									
					popup.getField('ageMeasure').setValue(selectedRecord.data['ageMeasure']);		
					popup.getField('statMeasure').setValue(selectedRecord.data['statMeasure']);		
					popup.getField('dofbMeasure').setValue(DesktopWeb.Util.getDateDisplayValue(selectedRecord.data['dofbMeasure']));																												 									
					popup.getField('nameElection').setValue(selectedRecord.data['nameElection']);		
					popup.getField('ageElection').setValue(selectedRecord.data['ageElection']);		
					popup.getField('statElection').setValue(selectedRecord.data['statElection']);		
					popup.getField('dofbElection').setValue(DesktopWeb.Util.getDateDisplayValue(selectedRecord.data['dofbElection']));						
				}

				_resources.grids['SegIncmBaseGrid'].focusRow(recordIndex);						
			}

										
		}	

		,openIncomeBaseDetlPopupFromGuarInfo: function()
		{
			var electionAge = _resources.grids['listOfTerms'].getSelectedRecord().data['firstDPAAge'];			
			var transID = _resources.grids['transaction'].getSelectedRecord().data['transID'];	
			var SegGuarDetlUUID = _resources.grids['transaction'].getSelectedRecord().data['segGuarDetlUUID'];			

			_self.openIncomeBaseDetlPopup (electionAge, transID, SegGuarDetlUUID);
		}
	
		,openIncomeBaseDetlPopupFromDeferInc: function()
		{
			var txnIncm = IFDS.Xml.getNodes(_segDIATransactionXML, "//SegDIATransactions/SegDIATxnDetls");

			var transID = 0;
			var SegGuarDetlUUID = null;
			var electionAge = _resources.grids['SegDIAGrid'].getSelectedRecord().data.electAge;
			
			if (txnIncm.length > 0){	
				transID = _resources.grids['SegDIATransactionGrid'].getSelectedRecord().data.transID;
				SegGuarDetlUUID = _resources.grids['SegDIATransactionGrid'].getSelectedRecord().data.SegGuarDetlUUID;
			}
			
			_self.openIncomeBaseDetlPopup (electionAge, transID, SegGuarDetlUUID);
		}												

		,loadDeferredIncData: function(asOfDate)
		{		
			var dataXML = IFDS.Xml.newDocument('data');																		
						
			IFDS.Xml.addSingleNode(dataXML, 'maturityid', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
			IFDS.Xml.addSingleNode(dataXML, 'asofdate', DesktopWeb.Util.getSMVDateValue(asOfDate));											
								
			DesktopWeb.Ajax.doSmartviewAjax(_segDIAInfoReloadView , null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);										

			function responseHandler(success, responseXML)
			{
				DesktopWeb.Util.debugXML(responseXML);				
				if (success)
				{				
					_segDIAInfoXML = responseXML;		
					populateDeferredIncDetlPopup(responseXML);
				} 				
			}						
		}

		,openDeferredIncDetlPopup: function()
		{	
			_defaultAsOfDate = true;					
			_self.loadDeferredIncData(_resources.fields['guaranteeToDate'].getDisplayDateString());			
		}
		
		
		
		,openELWAImpactPopup: function()
		{	
			var popup = _resources.popups['elwaImpactPopup'];
			var dataXML = IFDS.Xml.newDocument('data');	
			
			var listNode = IFDS.Xml.getNode(_segGuarInfoReloadXML, "//List[@listName = 'SegTransTypeList']/Element[code='" + _resources.grids['transaction'].getSelectedRecord().data['transType'] + "']");
			listNode = (listNode) ? listNode:IFDS.Xml.getNode(_segGuarInfoReloadXML, "//List[@id = 'SegTransTypeList']/Element[code='" + _resources.grids['transaction'].getSelectedRecord().data['transType'] + "']");
			var vTransTypeDesc = (listNode) ? IFDS.Xml.getNodeValue(listNode, 'value') : code;
					
			IFDS.Xml.addSingleNode(dataXML, "account", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
			IFDS.Xml.addSingleNode(dataXML, "contractVer", _resources.grids['listOfTerms'].getSelectedRecord().data['contractVer']);
			IFDS.Xml.addSingleNode(dataXML, "tradeDate", DesktopWeb.Util.getSMVDateValue(_resources.grids['transaction'].getSelectedRecord().data['tradeDate']));
			IFDS.Xml.addSingleNode(dataXML, "transID", _resources.grids['transaction'].getSelectedRecord().data['transID']);
			IFDS.Xml.addSingleNode(dataXML, "segGuarDetlUUID", _resources.grids['transaction'].getSelectedRecord().data['segGuarDetlUUID']);
			IFDS.Xml.addSingleNode(dataXML, "currentDate", IFDS.Xml.getNodeValue(_segGuarInfoReloadXML, "//DefaultValues/guarAsOfDate"));
			
			DesktopWeb.Ajax.doSmartviewAjax(_elwaImpactView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{
				popup.init();
				popup.populate(responseXML, vTransTypeDesc);
				popup.show();	

				DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _elwaImpactView + 'Response')); 
			}	
		}
		
		,openHypoElectionPopup: function()
		{	
			var popup = _resources.popups['hypoElectPopup'];
			var dataXML = IFDS.Xml.newDocument('data');	
			
			IFDS.Xml.addSingleNode(dataXML, "account", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
			IFDS.Xml.addSingleNode(dataXML, "contractVer", _resources.grids['listOfTerms'].getSelectedRecord().data['contractVer']);
			IFDS.Xml.addSingleNode(dataXML, "currentDate", IFDS.Xml.getNodeValue(_segGuarInfoReloadXML, "//DefaultValues/guarAsOfDate"));
			
			DesktopWeb.Ajax.doSmartviewAjax(_hypoElectionView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{	
				popup.init();
				popup.populate(responseXML);
				popup.show();
				
				DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _hypoElectionView + 'Response'));
			}
		}

		,reloadDeferredIncData: function()
		{		
			// The dates are controlled on front-end will be the display format, no need to convert and can be compared
			var asOfDate = _resources.fields['asOfDate'].getDisplayDateString();																											
			var currentBusDate = _resources.fields['guaranteeToDate'].getDisplayDateString();		

			_defaultAsOfDate = false;

			if (asOfDate < currentBusDate) 
			{																		
				DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("AsOfDateEarlierThanCurrentBusDateErrMsg"));	
				_resources.fields['asOfDate'].setValue(_asOfDate);			
			} else {							
				_self.loadDeferredIncData(_resources.fields['asOfDate'].getDisplayDateString());
			}		
		}

		,loadSegPenIncmBaseGrid: function()
		{							
			var electAge = _resources.grids['SegDIAGrid'].getSelectedRecord().data.electAge;

			_diaInfoXML = IFDS.Xml.cloneDocument(_segDIAInfoXML);

			var penIncmXML = IFDS.Xml.getNodes(_diaInfoXML,"//SegPenIncmBaseList/SegPenIncmDetl");

			var allowFundRate = IFDS.Xml.getNodeValue(_diaInfoXML,"//SegDIAInfo/allowFundRate");

			for(var i=0; i<penIncmXML.length; i++)
			{
				if (penIncmXML[i].childNodes.length > 0)
				{
					var gprRateByAge = 'RateListByAge/gpr' + electAge + '/rate';
					var rate = IFDS.Xml.getNodeValue(penIncmXML[i], gprRateByAge);	

					var gprDIAlwaByAge = 'RateListByAge/gpr' + electAge + '/dialwa';
					var dialwa = IFDS.Xml.getNodeValue(penIncmXML[i], gprDIAlwaByAge);														

					var gprLWABaseByAge = 'RateListByAge/gpr' + electAge + '/lwaBase';
					var lwaBase = IFDS.Xml.getNodeValue(penIncmXML[i], gprLWABaseByAge);
					
					IFDS.Xml.deleteNode(IFDS.Xml.getNode(penIncmXML[i], 'RateListByAge'));									

					IFDS.Xml.addSingleNode(penIncmXML[i], 'rate', rate);
					IFDS.Xml.addSingleNode(penIncmXML[i], 'dialwa', dialwa);													
					IFDS.Xml.addSingleNode(penIncmXML[i], 'lwaBase', lwaBase);													
				}
			}							
			
			if (allowFundRate.toUpperCase() == "NO")
            {
				_resources.grids['SegPenIncmBaseGrid'].hideColumn(6);
            }
			else
            {
				_resources.grids['SegPenIncmBaseGrid'].showColumn(6);
            }			
												
			_resources.grids['SegPenIncmBaseGrid'].getStore().loadData(IFDS.Xml.getNode(_diaInfoXML, "//SegPenIncmBaseList"));			
		 
			if(_resources.grids['SegPenIncmBaseGrid'].getStore().getCount() > 0) 
			{			
				_resources.grids['SegPenIncmBaseGrid'].selectFirstRecord();																										
			}			
										
		}					
		
		,populateSegDIATransactionGrid: function()
		{			
			var dataXML = IFDS.Xml.newDocument('data');	
			var penIncm = IFDS.Xml.getNodes(_segDIAInfoXML,"//SegPenIncmBaseList/SegPenIncmDetl");

			if (penIncm.length > 0)
			{
				IFDS.Xml.addSingleNode(dataXML, 'penID', _resources.grids['SegPenIncmBaseGrid'].getSelectedRecord().data.penID);																
				IFDS.Xml.addSingleNode(dataXML, 'account', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);				
				IFDS.Xml.addSingleNode(dataXML, 'electionage', _resources.grids['SegDIAGrid'].getSelectedRecord().data.electAge);
				IFDS.Xml.addSingleNode(dataXML, 'diaAsOfDate', DesktopWeb.Util.getSMVDateValue(_resources.fields['asOfDate'].getDisplayDateString()));
									
				DesktopWeb.Ajax.doSmartviewAjax(_segDIATransactionReloadView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);										

				function responseHandler(success, responseXML) 
				{
					DesktopWeb.Util.debugXML(responseXML);				

					if (success)
					{				
						_segDIATransactionXML = responseXML;
						loadSegDIATransactionGrid(responseXML);							
					} 				
				}	
			}
		}		
				
		,openDepleteLimPopup: function()
		{	
			var popup = _resources.popups['depleteLimPopup'];
			var dataXML = IFDS.Xml.newDocument('data');
            var guarToDate = _resources.fields['guaranteeToDate'].getDisplayDateString();
            
			IFDS.Xml.addSingleNode(dataXML, "runMode", 'init');
			IFDS.Xml.addSingleNode(dataXML, "account", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);
			IFDS.Xml.addSingleNode(dataXML, "contractType", _resources.grids['listOfTerms'].getSelectedRecord().data['contract']);
			IFDS.Xml.addSingleNode(dataXML, "contractVer", _resources.grids['listOfTerms'].getSelectedRecord().data['contractVer']);
			IFDS.Xml.addSingleNode(dataXML, "asOfDate", DesktopWeb.Util.getSMVDateValue(guarToDate));
			IFDS.Xml.addSingleNode(dataXML, 'maturityID', _resources.grids['listOfTerms'].getSelectedRecord().data['maturityID']);
            
			DesktopWeb.Ajax.doSmartviewAjax(_depleteLimView, null, dataXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{	
				if(success){
					popup.init();
					popup.populate(responseXML);
					popup.show();
					
					DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _depleteLimView + 'Response'));
				}
			}
		}
		
	}
}	