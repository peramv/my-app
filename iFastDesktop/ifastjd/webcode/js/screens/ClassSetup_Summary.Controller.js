/*********************************************************************************************
 * @file	ClassSetup_Summary.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Summary screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_Summary.Controller.js
 *
 * Purpose  : Summary information screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Summary information screens
 *
 * History  : 
 *  12 Nov 2012 H.Sartsangchan Created. 
 *          IN3135980 Load type validation does not work properly on Class setup
 *          - Add logic to validate Fund Load Group display
 *          - Change Rolloverclass display value
 *                                    
 *  25 Nov 2012 H.Sartsangchan P0207062 FN01 MF/MFR Enhancement
 *          - Add new 5 fields on Fee Configuration
 *
 *  12 Dec 2012 G. Thawarnwachirakun P0181067 IN3170857,3170865 T52846
 *          - Fixed on incorrect display in Performance Fee section 
 *          (Don't display benchmark index column) and Trade Configuration 
 *          section (missing StopRedeem and StopAutoTransIn)
 *          - Add StopRedeem and StopAutoTransIn 
 *          - Add getValueDescFromMktIndex to get the correct market index value
 *
 *  25 Apr 2012 C. Sangkasen P0212170 Master Account & AMS
 *          - Introduced field AMS Model Type. 
 *
 *  27 Jun 2013 N. Suanlamyai P0214690 T53774
 *          - Display 2 new distribution types
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  30 July 2014 Winnie Cheng P0232644 FN01 T78216
 *             - A new field added from Event Schedule screen for AIFMD enhancement
 *
 *	26 July 2014 C. Sangkasen P0212180 T55481
 *			   - Added Advisor Fee Applicable. 
 *
 *  24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *          - Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration.
 *
 *	21 May 2015 Winnie Cheng P0241128 T80810
 *          - Added one field - Redemption Notice Period to "Trade Days Controls". 
 *
 *  24 July 2015 Winnie Cheng P0242521 FN01 T81053 R15.5
 *          - Added Prorated Transfer field to support MFS Proportional Transfers
 *
 *  10 Dec 2015 Winnie Cheng P0248498 CHG0043235 T81863
 *          - Adding one dropdown field for Price Information : capstock rate type
 *          
 *   3 Feb 2016 Winnie Cheng P0251001 CHG0043877 T82126
 *          - Adding one dropdown field for Trade Configuration - Redemption Red. Gross/Net
 *          
 *	 8 Jan 2018	Sreejith A P0274727 P0274727-1
 *			- Added new tab "settle day controls"
 *
 *	23 Jan 2018	Sreejith.A P0274733 P0274733-156
 *			- Added MFR payment lead days
 *
 *	14 Mar 2018 Sreejith.A P0274727-83 DFT0082401
 *			- Different settlement currency value display
 *
 *	22 Mar 2018 Sreejith.A P0274727 P0274727-88
 *			- T+0 Project P0274727 changes revert from 18.3
 *
 *  07 May 2018 Pao - Supareuk S.
 *  		In goToScreen function, we changed a way to show the page from window.location 
 *  		using buildURL to DesktopWeb.Util.goToScreen. This is to solve an issue when 
 *  		user's profile has too many slot attached. If the session is included, the page
 *  		will be broken as too large.
 *  
 * 	12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 *   
 *  23 July 2018 Winnie Cheng P0277183-158 Intraday Pricing R18.5
 *          - Displaying intraday pricing set when applicable
 *  
 *  09 Nov 2018 Winnie C. R19.2
 *  		P0278169-69 Project Spring:SSII-7422 PIMCO DCCS Trading 
 *			Adding NSCC offset field for network NSCC setUp
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _addMode = null;
	var _initView = "dtClassSetupInit";
	var _updateView = "dtClassSetupUpd";	
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;
	var _loadType = null;		
	var _perfFeeFlag = false;
	var _allowVerify = null;
	var _verifyFlag = false;
	
	// PRIVATE METHODS ****************************************		
	function buildScreenDefListXML()
	{
		var listXML = IFDS.Xml.newDocument("Screens");		
		var screenXML = null;
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'ClassBasic/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "BasicInfo");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['BasicInfo']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'TradeConfiguration/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "TradeConfig");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['TradeConfig']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'DistributionConfig/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "DistConfig");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['DistConfig']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'PriceInfo/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "PriceInfo");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['PriceInfo']);
		}
				
		if (IFDS.Xml.getNode(_existingClassDataXML, 'FeeConfiguration/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "FeeConfig");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['FeeConfig']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'FeeModelConfiguration/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "FeeModelConfig");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['FeeModelConfig']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'FeeConfiguration/perfFeeFlag'))
		{
			if(IFDS.Xml.getNodeValue(_existingClassDataXML, 'FeeConfiguration/perfFeeFlag')=="yes"){
				var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
				IFDS.Xml.addSingleNode(screenXML, "id", "PerformanceFee");
				IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['PerformanceFee']);
			}
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'EventFreqConfig/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "EventFreq");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['EventFreq']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'TradeDayControls/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "TradeDayCtrls");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['TradeDayCtrls']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'SettleDayControls/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "SettleDayCtrls");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['SettleDayCtrls']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'GIAAttributes/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "GIAAttributes");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['GIAAttributes']);
		}
		
		if (IFDS.Xml.getNode(_existingClassDataXML, 'IntConfig/*'))
		{
			var screenXML = IFDS.Xml.addSingleNode(listXML, "Screen");
			IFDS.Xml.addSingleNode(screenXML, "id", "IntConfig");
			IFDS.Xml.addSingleNode(screenXML, "label", _translationMap['IntConfig']);
		}
		
		return listXML;
	}
	
	function setHeader()
	{			
		var fundCode = null;
		var classCode = null;
		var fundName = null;
		var sponsor = null;
		if (_addMode)
		{
			fundCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundCode');
			fundName = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundName');
			sponsor = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//sponsor');
			classCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//classCode');			
			if (classCode == "")
			{
				classCode = "*" + _translationMap['NEW'] + "*";
			}
			else 
			{
				classCode = "*" + classCode + "*";
			}
		}
		else
		{
			fundCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundCode');
			classCode = IFDS.Xml.getNodeValue(_existingClassDataXML, 'classCode');
			fundName = IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundName');
			sponsor = IFDS.Xml.getNodeValue(_existingClassDataXML, 'sponsor');	
		}
				
		var headerText = _translationMap['ClassSummaryFund'];
		headerText += fundCode;
		headerText += ", " + _translationMap['Class'] + ": ";					
		headerText += classCode;
		_resources.fields['header'].setText(headerText);
		
		_resources.fields['fund'].setText(fundName);
		_resources.fields['fundSponsor'].setText(sponsor);		
	}
	
	function populateScreen()
	{
		var screenNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
		var dataPanelContainer = Ext.getCmp('dataPanelContainer'); 
		
		var initialDataPanelToExpand = null;		
		for (var i = 0; i < screenNodes.length; i++)
		{						
			var dataPanel = new DesktopWeb.ScreenResources.DataPanel({
				title: IFDS.Xml.getNodeValue(screenNodes[i], 'label')
				,id: IFDS.Xml.getNodeValue(screenNodes[i], 'id')	
				,listeners: {
					edit: function(id){_self.edit(id);}
					,expand: function(panel){panel.el.scrollIntoView("DataPanelContainer");}
				}		
			});
			dataPanel.hideEditLink(IFDS.Xml.getNodeValue(_initDataXML, 'Permissions/mod')=="no");
			dataPanelContainer.add(dataPanel);
			
			if (IFDS.Xml.getNodeValue(screenNodes[i], 'id') == DesktopWeb._SCREEN_PARAM_MAP['prevScreen'])
			{
				initialDataPanelToExpand = dataPanel;
			}				
			
			switch(IFDS.Xml.getNodeValue(screenNodes[i], 'id'))
			{
				case 'BasicInfo':
				{
					populateBasicInfo(dataPanel);
					break;
				}
				case 'TradeConfig':
				{
					populateTradeConfig(dataPanel);
					break;
				}				
				case 'DistConfig':
				{
					populateDistConfig(dataPanel);
					break;
				}
				case 'PriceInfo':
				{
					populatePriceInfo(dataPanel);
					break;
				}
				case 'FeeConfig':
				{
					populateFeeConfig(dataPanel);
					break;
				}
				case 'FeeModelConfig':
				{
					populateFeeModelConfig(dataPanel);
					break;
				}
				case 'EventFreq':
				{
					populateEventFreq(dataPanel);
					break;
				}
				case 'TradeDayCtrls':
				{
					populateTradeDayCtrls(dataPanel);
					break;
				}
				case 'SettleDayCtrls':
				{
					populateSettleDayCtrls(dataPanel);
					break;
				}
				case 'GIAAttributes':
				{
					populateGIAAttributes(dataPanel);
					break;
				}
				case 'IntConfig':
				{
					populateIntConfig(dataPanel);
					break;
				}
				case 'PerformanceFee':
				{
					populatePerfFeeConfig(dataPanel);
					break;
				}
				default:
				{
					break;
				}
			}
			dataPanel.doLayout();
		}
		
		dataPanelContainer.doLayout();		
		if (initialDataPanelToExpand == null)
		{
			initialDataPanelToExpand = dataPanelContainer.get(0);
		}
		
		initialDataPanelToExpand.expand();		
	}
	
	function populateBasicInfo(dataPanel)
	{
		try{
			var basicInfoXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML, 'ClassBasic') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'ClassBasic') : 
				IFDS.Xml.getNode(_existingClassDataXML,'ClassBasic'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
		
		dataPanel.addField(_translationMap['EngDesc'], 
			IFDS.Xml.getNodeValue(basicInfoXML, 'classE'),
			IFDS.Xml.getNodeValue(basicInfoXML, 'classE/@status'));		
		dataPanel.addField(_translationMap['FrDesc'],
			IFDS.Xml.getNodeValue(basicInfoXML, 'classF'),
			IFDS.Xml.getNodeValue(basicInfoXML, 'classF/@status'));
		dataPanel.addField(_translationMap['Status'], 
			getValueDescFromList('StatusList', IFDS.Xml.getNodeValue(basicInfoXML, 'stat')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'stat/@status'));
		dataPanel.addDateField(_translationMap['StatusDate'], 
			IFDS.Xml.getNodeValue(basicInfoXML, 'statDate'),
			IFDS.Xml.getNodeValue(basicInfoXML, 'statDate/@status'));
			
		dataPanel.addDateField(_translationMap['EffectiveDate'], 
			IFDS.Xml.getNodeValue(basicInfoXML, 'deff'),
			IFDS.Xml.getNodeValue(basicInfoXML, 'deff/@status'));
		dataPanel.addDateField(_translationMap['StopDate'], 
			IFDS.Xml.getNodeValue(basicInfoXML, 'stopDate'),
			IFDS.Xml.getNodeValue(basicInfoXML, 'stopDate/@status'));
			
		dataPanel.addField(_translationMap['LoadType'], 
			getValueDescFromList('LoadTypeList', IFDS.Xml.getNodeValue(basicInfoXML, 'loadType')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'loadType/@status'));
		_loadType = IFDS.Xml.getNodeValue(basicInfoXML, 'loadType');	
		dataPanel.addField(_translationMap['ESCCompCode'], 
			getValueDescFromList('CompanyCodeList', IFDS.Xml.getNodeValue(basicInfoXML, 'company')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'company/@status'));
		dataPanel.addField(_translationMap['BareTrustee'], 
			getValueDescFromList('BareTrusteeList', IFDS.Xml.getNodeValue(basicInfoXML, 'bareTrustee')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'bareTrustee/@status'));
		dataPanel.addField(_translationMap['RiskRating'], 
			getValueDescFromList('RiskRatingList', IFDS.Xml.getNodeValue(basicInfoXML, 'riskRating')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'riskRating/@status'));
		dataPanel.addField(_translationMap['FundClassCurrHol'], 
			getValueDescFromList('FundCurHldyOptList', IFDS.Xml.getNodeValue(basicInfoXML, 'FundCurHldyOpt')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'FundCurHldyOpt/@status'));
		dataPanel.addField(_translationMap['InventoryCategory'], 
			getValueDescFromList('InventoryCategoryList', IFDS.Xml.getNodeValue(basicInfoXML, 'cdicInvCat')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'cdicInvCat/@status'));
		dataPanel.addField(_translationMap['TrailerPaymentFrequency'], 
			getValueDescFromList('TrfPayFreqList', IFDS.Xml.getNodeValue(basicInfoXML, 'trfPayFreq')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'trfPayFreq/@status'));
		dataPanel.addField(_translationMap['ProratedTransfer'], 
			getValueDescFromList('ProratedXferList', IFDS.Xml.getNodeValue(basicInfoXML, 'proratedXfer')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'proratedXfer/@status'));
		if (IFDS.Xml.getNode(_initDataXML, "List[@id = 'TrackingTypeList']"))		
		{
			dataPanel.addField(_translationMap['TrackingType'], 
				getValueDescFromList('TrackingTypeList', IFDS.Xml.getNodeValue(basicInfoXML, 'trackingType')),
				IFDS.Xml.getNodeValue(basicInfoXML, 'trackingType/@status'));
		}else{
			dataPanel.addSpacer();
		}

		
		dataPanel.addSubHeader(_translationMap['InventoryTracking']);				
		dataPanel.addSubField(_translationMap['Applicable'], 
			IFDS.Xml.getNodeValue(basicInfoXML, 'InventoryTracking/applicable'),
			IFDS.Xml.getNodeValue(basicInfoXML, 'InventoryTracking/applicable/@status'));
		dataPanel.addSubField(_translationMap['BasedOn'], 
			getValueDescFromList('BasedOnInvTrackList', IFDS.Xml.getNodeValue(basicInfoXML, 'InventoryTracking/basedOn')),
			IFDS.Xml.getNodeValue(basicInfoXML, 'InventoryTracking/basedOn/@status'));					
		
		dataPanel.addSubHeader(_translationMap['FundSubCate']);
		var fundSubCatNodes = IFDS.Xml.getNodes(basicInfoXML, 'FundSubCategories/FundSubCat');
		for (var i = 0; i < fundSubCatNodes.length; i++)
		{
			dataPanel.addSubField(getValueDescFromList('FundSubCatList', IFDS.Xml.getNodeValue(fundSubCatNodes[i], 'subCat')), 
				IFDS.Xml.getNodeValue(fundSubCatNodes[i], 'subCatFlag'),
				IFDS.Xml.getNodeValue(fundSubCatNodes[i], 'subCatFlag/@status'));		
		}
		if (fundSubCatNodes.length % 2 != 0)
		{
			dataPanel.addSpacer();
		}
		
		dataPanel.addSubHeader(_translationMap['FundIdentifiers']);
		var fundIDNodes = IFDS.Xml.getNodes(basicInfoXML, 'FundIdentifiers/FundIdentifier');
		for (var i = 0; i < fundIDNodes.length; i++)
		{
			dataPanel.addSubField(getValueDescFromList('FundIdentifierList', IFDS.Xml.getNodeValue(fundIDNodes[i], 'idType')),
				 IFDS.Xml.getNodeValue(fundIDNodes[i], 'idValue'),
				 IFDS.Xml.getNodeValue(fundIDNodes[i], 'runMode'));		
		}		
		if (fundIDNodes.length % 2 != 0)
		{
			dataPanel.addSpacer();
		}
		
		dataPanel.addSubHeader(_translationMap['ShareGroups']);
		var shrGrpNodes = IFDS.Xml.getNodes(basicInfoXML, 'ShareGroups/ShareGroup');
		for (var i = 0; i < shrGrpNodes.length; i++)
		{
			var mode = IFDS.Xml.getNodeValue(shrGrpNodes[i], 'active');
			var tempValue = mode.toLowerCase();
		
			if (tempValue == 'yes')
				mode = _translationMap['Yes'];
			else if (tempValue == 'no')
				mode = _translationMap['No'];
			
			dataPanel.addSubFieldDate(getValueDescFromList('ShGroupList', IFDS.Xml.getNodeValue(shrGrpNodes[i], 'shGroup')), 
				IFDS.Xml.getNodeValue(shrGrpNodes[i], 'deff') 
					+ " (" + _translationMap['Active'] 
					+ ": " 
					+ mode
					+ ")",
				IFDS.Xml.getNodeValue(shrGrpNodes[i], 'runMode'));		
		}		
		if (shrGrpNodes.length % 2 != 0)
		{
			dataPanel.addSpacer();
		}	
		
		if (IFDS.Xml.getNode(basicInfoXML, 'LotInformations/*'))
		{
			dataPanel.addSubHeader(_translationMap['LotTypeInformation']);
			var lotTypeNodes = IFDS.Xml.getNodes(basicInfoXML, 'LotInformations/LotInformation');
			for (var i = 0; i < lotTypeNodes.length; i++)
			{
				dataPanel.addSubField(IFDS.Xml.getNodeValue(lotTypeNodes[i], 'lotType'),
				 IFDS.Xml.getNodeValue(lotTypeNodes[i], 'redemptionOrder'),
				 IFDS.Xml.getNodeValue(lotTypeNodes[i], 'redemptionOrder/@status'));		
			}	
			if (lotTypeNodes.length % 2 != 0)
			{
				dataPanel.addSpacer();
			}	
		}
	}
	
	function populateTradeConfig(dataPanel)
	{
		try {
			var tradeConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'TradeConfiguration') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'TradeConfiguration') : 
				IFDS.Xml.getNode(_existingClassDataXML,'TradeConfiguration'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
						
		dataPanel.addField(_translationMap['WireOrderAllowed'], IFDS.Xml.getNodeValue(tradeConfigXML, 'wireElig'));
		dataPanel.addField(_translationMap['OrderType'], getValueDescFromList('OrdTypeList', IFDS.Xml.getNodeValue(tradeConfigXML, 'ordType')));
		
		dataPanel.addSubHeader(_translationMap['ClassElig']);						
		dataPanel.addSubField(_translationMap['RRSP'],
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/rrsp'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/rrsp/@status'));			
		dataPanel.addSubField(_translationMap['RRIF'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/rrif'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/rrif/@status'));	
		dataPanel.addSubField(_translationMap['ESOP'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/esop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/esop/@status'));			
		dataPanel.addSubField(_translationMap['NSCCompliant'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/nscCompliant'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/nscCompliant/@status'));	
		dataPanel.addSubField(_translationMap['AMS'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/ams'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/ams/@status'));	
		dataPanel.addSubField(_translationMap['MarginAllowed'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/marginAllowed'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/marginAllowed/@status'));	
		dataPanel.addSubField(_translationMap['RolloverAllowed'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRoll'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRoll/@status'));	
		dataPanel.addSubField(_translationMap['CSSErrCorrect'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/cssErrCorr'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/cssErrCorr/@status'));	
		dataPanel.addSubField(_translationMap['EligICTIn'], 
			getValueDescFromList('EligICTInList', IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/eligICTIn')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/eligICTIn/@status'));	
		dataPanel.addSubField(_translationMap['EligICTOut'], 
			getValueDescFromList('EligICTOutList', IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/eligICTOut')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/eligICTOut/@status'));			
		dataPanel.addSubField(_translationMap['ERISAAllowed'], 
			getValueDescFromList('ERISAList', IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/erisaOptn')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/erisaOptn/@status'));	
		dataPanel.addSubField(_translationMap['ERISAClsGrp'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/erisaClassGroup'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/erisaClassGroup/@status'));	
		dataPanel.addSubField(_translationMap['AMSModelType'], 
			getValueDescFromList('AMSModelTypeList', IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/amsModelType')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/amsModelType/@status'));
		
		dataPanel.addSubHeader(_translationMap['RolloverDetails']);
		dataPanel.addSubField(_translationMap['RolloverFund'], 
			getValueDescFromList('Funds', IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRollFund')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRollFund/@status'));
		dataPanel.addSubField(_translationMap['RolloverClass'], IFDS.Xml.getNodeValue(tradeConfigXML,'ClassEligibility/freeRollCl'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRollCl/@status'));	
		dataPanel.addSubField(_translationMap['RolloverAmtType'], 
			getValueDescFromList('PUDList', IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRollPUD')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRollPUD/@status'));	
		dataPanel.addSubField(_translationMap['QualPeriod'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRollQualPrd'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'ClassEligibility/freeRollQualPrd/@status'));	
		
		dataPanel.addSubHeader(_translationMap['StopFlags']);
		dataPanel.addSubField(_translationMap['StopCommRebate'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/commRebStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/commRebStop/@status'));
		dataPanel.addSubField(_translationMap['StopPAC'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/pacStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/pacStop/@status'));
		dataPanel.addSubField(_translationMap['StopSWP'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/swpStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/swpStop/@status'));
		dataPanel.addSubField(_translationMap['StopPurchase'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/purStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/purStop/@status'));
    	dataPanel.addSubField(_translationMap['StopRedeem'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/redStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/redStop/@status'));
		dataPanel.addSubField(_translationMap['StopAutoTransIn'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/autoXferInStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/autoXferInStop/@status'));		
		dataPanel.addSubField(_translationMap['StopAutoTransOut'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/autoXferOutStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/autoXferOutStop/@status'));
		dataPanel.addSubField(_translationMap['StopTransIn'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/xferInStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/xferInStop/@status'));
		dataPanel.addSubField(_translationMap['StopTransOut'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/xferOutStop'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'StopFlags/xferOutStop/@status'));
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['PurchaseMinAmt']);
		dataPanel.addSubField(_translationMap['MinInitAmt'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minInit'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minInit/@status'));
		dataPanel.addSubField(_translationMap['MinSubAmt'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minSub'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minSub/@status'));
		
		dataPanel.addSubHeader(_translationMap['RedempMinAmt']);
		dataPanel.addSubField(_translationMap['MinInitAmt'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/redMinInit'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/redMinInit/@status'));
		dataPanel.addSubField(_translationMap['MinSubAmt'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/redMinSub'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/redMinSub/@status'));
		
		dataPanel.addSubHeader(_translationMap['SysMinAmt']);
		dataPanel.addSubField(_translationMap['SWPMinAmt'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/swpMin'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/swpMin/@status'));
		dataPanel.addSubField(_translationMap['PACMinAmt'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/pacMin'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/pacMin/@status'));
		
		dataPanel.addSubHeader(_translationMap['MinBalAmt']);
		dataPanel.addSubField(_translationMap['MinFundClassBal'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minFundClBal'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minFundClBal/@status'));
		dataPanel.addSubField(_translationMap['MinAcctBal'], 
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minAcctBal'),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'MinMaxAmounts/minAcctBal/@status'));
		
		dataPanel.addSubHeader(_translationMap['CalMethd']);
		dataPanel.addSubField(_translationMap['PurchaseAgingRule'], 
			getValueDescFromList('PurAgingRuleList', IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/purAgingRule')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/purAgingRule/@status'));
		dataPanel.addSubField(_translationMap['GainLossMethd'], 
			getValueDescFromList('GainLossMthdList', IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/gainLossMthd')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/gainLossMthd/@status'));
		dataPanel.addSubField(_translationMap['FeeConsolidation'], 
			getValueDescFromList('FreeConsolList', IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/freeConsol')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/freeConsol/@status'));
		dataPanel.addSubField(_translationMap['PartnerUnitAssign'], 
			getValueDescFromList('PShipUnitAsmtList', IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/pShipUnitAsmt')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'CalcMethods/pShipUnitAsmt/@status'));
		//Redemption Partial indicator
		dataPanel.addSubField(_translationMap['RedemptionGrossNet'], 
			getValueDescFromList('RedGrossNetList', IFDS.Xml.getNodeValue(tradeConfigXML, 'redGrossNetDefault')),
			IFDS.Xml.getNodeValue(tradeConfigXML, 'redGrossNetDefault/@status'));
	}
	
	function populateDistConfig(dataPanel)
	{
		try{
			var distConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'DistributionConfig') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'DistributionConfig') : 
				IFDS.Xml.getNode(_existingClassDataXML,'DistributionConfig'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}	
		
		if (IFDS.Xml.getNodeValue(distConfigXML, 'id') == 'yes')
		{
			dataPanel.addSubHeader(_translationMap['IncomeDistribution']);
			dataPanel.addSubField(_translationMap['DefaultInvestment'],
				IFDS.Xml.getNodeValue(distConfigXML, 'idDefInvestOpt'),
				IFDS.Xml.getNodeValue(distConfigXML, 'idDefInvestOpt/@status'));
			dataPanel.addSubField(_translationMap['OverrideOption'],
				IFDS.Xml.getNodeValue(distConfigXML, 'idOverrideOpt'),
				IFDS.Xml.getNodeValue(distConfigXML, 'idOverrideOpt/@status'));
		}
		
		if (IFDS.Xml.getNodeValue(distConfigXML, 'cd') == 'yes')
		{
			dataPanel.addSubHeader(IFDS.Xml.getNodeValue(distConfigXML, 'cdDesc'));
			dataPanel.addSubField(_translationMap['DefaultInvestment'],
				IFDS.Xml.getNodeValue(distConfigXML, 'cdDefInvestOpt'),
				IFDS.Xml.getNodeValue(distConfigXML, 'cdDefInvestOpt/@status'));
			dataPanel.addSubField(_translationMap['OverrideOption'],
				IFDS.Xml.getNodeValue(distConfigXML, 'cdOverrideOpt'),
				IFDS.Xml.getNodeValue(distConfigXML, 'cdOverrideOpt/@status'));
		}	
		
		dataPanel.addSubHeader(_translationMap['DistribOptions']);
		dataPanel.addSubField(_translationMap['DistribMode'],
			getValueDescFromList('DistribModeList', IFDS.Xml.getNodeValue(distConfigXML, 'distribMode')),
			IFDS.Xml.getNodeValue(distConfigXML, 'distribMode/@status'));
		dataPanel.addSubFieldDate(_translationMap['NextRecordDate'],
			IFDS.Xml.getNodeValue(distConfigXML, 'nextRecDate'),
			IFDS.Xml.getNodeValue(distConfigXML, 'nextRecDate/@status'));
		dataPanel.addSubField(_translationMap['DistribRateEdit'],
			getValueDescFromList('DistribRateEditList', IFDS.Xml.getNodeValue(distConfigXML, 'distribRateEdit')),
			IFDS.Xml.getNodeValue(distConfigXML, 'distribRateEdit/@status'));
		dataPanel.addSubField(_translationMap['DistribAdjustApply'],
			getValueDescFromList('AdjustIDFlagList', IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag')),
			IFDS.Xml.getNodeValue(distConfigXML, 'adjustIDFlag/@status'));
		
		if (IFDS.Xml.getNode(distConfigXML, 'nxtDistribNmbr'))
		{
			dataPanel.addSubField(_translationMap['NextDistribNumber'],
				IFDS.Xml.getNodeValue(distConfigXML, 'nxtDistribNmbr'),
				IFDS.Xml.getNodeValue(distConfigXML, 'nxtDistribNmbr/@status'));
			dataPanel.addSpacer();
		}
		if (IFDS.Xml.getNode(distConfigXML, 'grpTrType'))
		{
			dataPanel.addSubField(_translationMap['G1G2InventoryTracking'],
				getValueDescFromList('GrpTrTypeList', IFDS.Xml.getNodeValue(distConfigXML, 'grpTrType')),
				IFDS.Xml.getNodeValue(distConfigXML, 'grpTrType/@status'));
			dataPanel.addSpacer();
		}

		if (IFDS.Xml.getNodeValue(distConfigXML, 'id') == 'yes')
		{
			if (IFDS.Xml.getNodeValue(distConfigXML, 'idCI') == 'yes')
			{
				dataPanel.addSubHeader(_translationMap['CapitalGainIncome']);
				dataPanel.addSubFieldDate(_translationMap['LastDividendDate'],
					IFDS.Xml.getNodeValue(distConfigXML, 'idCILastDivDt'),
					IFDS.Xml.getNodeValue(distConfigXML, 'idCILastDivDt/@status'));
				dataPanel.addSubFieldDate(_translationMap['AllocationType'],
					IFDS.Xml.getNodeValue(distConfigXML, 'idCIAllocType'),
					IFDS.Xml.getNodeValue(distConfigXML, 'idCIAllocType/@status'));
			}
			
			if (IFDS.Xml.getNodeValue(distConfigXML, 'idSI') == 'yes')
			{
				dataPanel.addSubHeader(_translationMap['SupplementaryIncome']);
				dataPanel.addSubFieldDate(_translationMap['LastDividendDate'],
					IFDS.Xml.getNodeValue(distConfigXML, 'idSILastDivDt'),
					IFDS.Xml.getNodeValue(distConfigXML, 'idSILastDivDt/@status'));
				dataPanel.addSubField(_translationMap['AllocationType'],
					IFDS.Xml.getNodeValue(distConfigXML, 'idSIAllocType'),
					IFDS.Xml.getNodeValue(distConfigXML, 'idSIAllocType/@status'));
			}
		}
	}
	
	function populatePriceInfo(dataPanel)
	{
		try{
			var priceInfoXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'PriceInfo') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'PriceInfo') : 
				IFDS.Xml.getNode(_existingClassDataXML,'PriceInfo'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
		
		dataPanel.addField(_translationMap['NAVCurrency'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'currency'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'currency/@status'));
		dataPanel.addField(_translationMap['ValidSettleCurrency'],
			IFDS.Xml.getNodeValue(priceInfoXML, 'validSettleCurr'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'validSettleCurr/@status'));
		dataPanel.addField(_translationMap['CustomValuation'], 
			getValueDescFromList('SchedTransTypeList',IFDS.Xml.getNodeValue(priceInfoXML, 'schedTransType')),
			IFDS.Xml.getNodeValue(priceInfoXML, 'schedTransType/@status'));
		dataPanel.addField(_translationMap['ESGPriceSuppress'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'esgPriceSuppress'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'esgPriceSuppress/@status'));
		
		dataPanel.addSubHeader(_translationMap['NAV']);
		dataPanel.addSubField(_translationMap['GAVPricing'], 
			getValueDescFromList('gavApply', IFDS.Xml.getNodeValue(priceInfoXML, 'gavApply')),
			IFDS.Xml.getNodeValue(priceInfoXML, 'gavApply/@status'));
		dataPanel.addSpacer();
		dataPanel.addSubField(_translationMap['FixedPrice'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'fixPrice'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'fixPrice/@status'));
		dataPanel.addSubField(_translationMap['FixedRate'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'fixRate'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'fixRate/@status'));
		dataPanel.addSubField(_translationMap['RatePrecision'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'ratePrecision'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'ratePrecision/@status'));
		dataPanel.addSubField(_translationMap['CapStockFXRateType'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'capstockRateType'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'capstockRateType/@status'));
		dataPanel.addSubField(_translationMap['PriceVarAmt'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'priceVarAmt'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'priceVarAmt/@status'));
		dataPanel.addSubField(_translationMap['PriceVarType'], 
			getValueDescFromList('PriceVarTypeList',IFDS.Xml.getNodeValue(priceInfoXML, 'priceVarType')),
			IFDS.Xml.getNodeValue(priceInfoXML, 'priceVarType/@status'));
			
		// FundLoadGrpList list will not generate if set Generic Control FundLoadGrouping->Fundsetup to no 
		if (IFDS.Xml.getNode(_initDataXML, "List[@id = 'FundLoadGrpList']"))
		{
			dataPanel.addSubField(_translationMap['LoadGroup'], 
				getValueDescFromList('FundLoadGrpList',IFDS.Xml.getNodeValue(priceInfoXML, 'loadGrp')),
				IFDS.Xml.getNodeValue(priceInfoXML, 'loadGrp/@status'));
		}else{
			dataPanel.addSpacer();
		}
		
		dataPanel.addSubHeader(_translationMap['Unit']);
		dataPanel.addSubField(_translationMap['CalculationMethod'], 
			getValueDescFromList('UnitCalcList',IFDS.Xml.getNodeValue(priceInfoXML, 'unitsCalc')),
			IFDS.Xml.getNodeValue(priceInfoXML, 'unitsCalc/@status'));
		dataPanel.addSubField(_translationMap['RoundingFlag'], 
			getValueDescFromList('RoundFlagList',IFDS.Xml.getNodeValue(priceInfoXML, 'roundFlag')),
			IFDS.Xml.getNodeValue(priceInfoXML, 'roundFlag/@status'));	
		dataPanel.addSubField(_translationMap['UnitPrecision'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'unitsPrecision'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'unitsPrecision/@status'));	
		dataPanel.addSubField(_translationMap['FractionalShare'], 
			IFDS.Xml.getNodeValue(priceInfoXML, 'fractionalShr'),
			IFDS.Xml.getNodeValue(priceInfoXML, 'fractionalShr/@status'));
		dataPanel.addSubField(_translationMap['AllocationType'], 
			getValueDescFromList('AllocTypeList',IFDS.Xml.getNodeValue(priceInfoXML, 'allocType')),
			IFDS.Xml.getNodeValue(priceInfoXML, 'allocType/@status'));		

		dataPanel.addSpacer();
		
		//Price Points
		if(_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'PriceInfo')) {

			var existingIntraDayPricingNode = IFDS.Xml.getNode(_existingClassDataXML, '//PriceInfo/intraDayPricings');
			var updatedIntraDayPricingNode = IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo/intraDayPricings');
			var intrapriceNode = IFDS.Xml.getNode(priceInfoXML, 'intraDayPricings');
			//concatenate existing records
			if(intrapriceNode) {
				var existingPricings = IFDS.Xml.getNodes(existingIntraDayPricingNode, "intraDayPricing");
				if(existingPricings) { //excluding modify record
					Ext.each(existingPricings, function(existingPricing) {
						var existingPricingUUID = IFDS.Xml.getNodeValue(existingPricing, "intraDayPricingUUID");
						var foundMatch = false;
						var updatedPricings = IFDS.Xml.getNodes(updatedIntraDayPricingNode, "intraDayPricing");
	
						if(updatedPricings) {
							Ext.each(updatedPricings, function(updatedPricing) {
								var updatedPricingUUID = IFDS.Xml.getNodeValue(updatedPricing, "intraDayPricingUUID");
								var delRecord = IFDS.Xml.getNodeValue(updatedPricing, "runMode");
								if (existingPricingUUID == updatedPricingUUID) {
									foundMatch = true;
								}
							});
							//Append existing record
							if(!foundMatch) {
								IFDS.Xml.appendNode(intrapriceNode, IFDS.Xml.cloneDocument(existingPricing));
							}
						}
					});
				}
			 }
		}
		//Intraday price set
		var intradayNodes = IFDS.Xml.getNodes(priceInfoXML, 'intraDayPricings/intraDayPricing');
			dataPanel.addSubHeader(_translationMap['IntradayPricing']);
			dataPanel.addSpacer();
		for (var i = 0; i < intradayNodes.length; i++) {
			if(IFDS.Xml.getNodeValue(intradayNodes[i], 'runMode') != 'd') {
				var endDate = IFDS.Xml.getNodeValue(intradayNodes[i], 'endDate')
				var nowDataObj = new Date();
				var endDataObj = DesktopWeb.Util.stringToDate(endDate,'mdy');

				if(endDataObj > nowDataObj) {
					dataPanel.addSubField(_translationMap['EffectiveFrom'],
						 DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(intradayNodes[i], 'startDate')),
						 IFDS.Xml.getNodeValue(intradayNodes[i], 'startDate/@status'));
					dataPanel.addSubField(_translationMap['NumOfPoints'],
						 IFDS.Xml.getNodeValue(intradayNodes[i], 'pricePointCnt'),
						 IFDS.Xml.getNodeValue(intradayNodes[i], 'pricePointCnt/@status'));	
				}
			}
		}
	}
	
	function populateFeeConfig(dataPanel)
	{
		try{
			var feeConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'FeeConfiguration') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'FeeConfiguration') : 
				IFDS.Xml.getNode(_existingClassDataXML,'FeeConfiguration'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
			
		dataPanel.addSubHeader(_translationMap['TrailerFee']);
		dataPanel.addSubFieldDate(_translationMap['TrailerFeeDate'], 
			IFDS.Xml.getNodeValue(feeConfigXML, 'trlFeeDate'),
			IFDS.Xml.getNodeValue(feeConfigXML, 'trlFeeDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['TrailerFeeGrandFatherDate'], 
			IFDS.Xml.getNodeValue(feeConfigXML, 'trlGrandFathDate'),
			IFDS.Xml.getNodeValue(feeConfigXML, 'trlGrandFathDate/@status'));
		
		dataPanel.addSubHeader(_translationMap['MaturityDays']);
		dataPanel.addSubField(_translationMap['EarlyMaturityDays'], 
			IFDS.Xml.getNodeValue(feeConfigXML, 'earlyMatDays'),
			IFDS.Xml.getNodeValue(feeConfigXML, 'earlyMatDays/@status'));
		dataPanel.addSubField(_translationMap['ShortTermTradingMaturityDays'], 
			IFDS.Xml.getNodeValue(feeConfigXML, 'sttrMatDays'),
			IFDS.Xml.getNodeValue(feeConfigXML, 'sttrMatDays/@status'));
		
		dataPanel.addSubHeader(_translationMap['TransferFee']);
		dataPanel.addSubField(_translationMap['TransferFeeApplicable'], 
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfrFee'),
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfrFee/@status'));
		dataPanel.addSubField(_translationMap['TransferFeeRate'], 
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfrFeeRate'),
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfrFeeRate/@status'));
		dataPanel.addSubField(_translationMap['TransferFeeType'], 
			getValueDescFromList('FeeTypeList', IFDS.Xml.getNodeValue(feeConfigXML, 'tfrFeeType')),
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfrFeeType/@status'));
		dataPanel.addSubField(_translationMap['TransferFeeBasedOn'], 
			getValueDescFromList('BasedOnBELTFRList', IFDS.Xml.getNodeValue(feeConfigXML, 'tfrBasedOn')),
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfrBasedOn/@status'));
		dataPanel.addSubField(_translationMap['Paid'], 
			getValueDescFromList('HowPaidList', IFDS.Xml.getNodeValue(feeConfigXML, 'howPaid')),
			IFDS.Xml.getNodeValue(feeConfigXML, 'howPaid/@status'));
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['TrailerFeeRebate']);
		dataPanel.addSubField(_translationMap['TFRApplicable'], 
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfRebate'),
			IFDS.Xml.getNodeValue(feeConfigXML, 'tfRebate/@status'));
		dataPanel.addSpacer();

		if(IFDS.Xml.getNode(feeConfigXML, 'perfFeeFlag') && IFDS.Xml.getNodeValue(feeConfigXML, 'perfFeeFlag')!='')	{
			dataPanel.addSubHeader(_translationMap['PerformanceFee']);
			dataPanel.addSubField(_translationMap['PerformanceFeeApplicable'], 
				IFDS.Xml.getNodeValue(feeConfigXML, 'perfFeeFlag'),
				IFDS.Xml.getNodeValue(feeConfigXML, 'perfFeeFlag/@status'));
			dataPanel.addSpacer();
	    }

		
		if (_loadType == 'FEL')
		{
			var FELNode = IFDS.Xml.getNode(feeConfigXML, 'FrontEndLoad');
			if (FELNode)
			{
				dataPanel.addSubHeader(_translationMap['FrontEndLoad']);
				dataPanel.addSubField(_translationMap['AcquisitionFeeType'], 
					getValueDescFromList('FeeTypeList', IFDS.Xml.getNodeValue(FELNode, 'feeType')),
					IFDS.Xml.getNodeValue(feeConfigXML, 'feeType/@status'));			
				dataPanel.addSubField(_translationMap['AcquisitionPaid'], 
					getValueDescFromList('HowPaidList', IFDS.Xml.getNodeValue(FELNode, 'howPaid')),
					IFDS.Xml.getNodeValue(feeConfigXML, 'howPaid/@status'));
				dataPanel.addSubField(_translationMap['AcquisitionRate'], 
					IFDS.Xml.getNodeValue(FELNode, 'rate'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'rate/@status'));
				dataPanel.addSubField(_translationMap['AcquisitionBasedOn'], 
					getValueDescFromList('BasedOnBELTFRList', IFDS.Xml.getNodeValue(FELNode, 'basedOn')),
					IFDS.Xml.getNodeValue(feeConfigXML, 'basedOn/@status'));
				dataPanel.addSubField(_translationMap['MaxFeeRate'], 
					IFDS.Xml.getNodeValue(FELNode, 'maxRate'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'maxRate/@status'));
				dataPanel.addSubField(_translationMap['MinFeeRate'], 
					IFDS.Xml.getNodeValue(FELNode, 'minRate'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'minRate/@status'));
				dataPanel.addSubField(_translationMap['WithholdRate'], 
					IFDS.Xml.getNodeValue(FELNode, 'withHoldRate'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'withHoldRate/@status'));
				dataPanel.addSpacer();			
			}
		}
		
		if (_loadType != 'FEL' && _loadType != 'NOL')
		{
			var BELNode = IFDS.Xml.getNode(feeConfigXML, 'BackEndLoad');
			if (BELNode)
			{
				dataPanel.addSubHeader(_translationMap['BackEndLoad']);
				dataPanel.addSubField(_translationMap['FeeType'], 
					getValueDescFromList('FeeTypeList', IFDS.Xml.getNodeValue(BELNode, 'feeType')),
					IFDS.Xml.getNodeValue(feeConfigXML, 'feeType/@status'));		
				dataPanel.addSubField(_translationMap['BelBasedOn'], 
					getValueDescFromList('BasedOnBELTFRList', IFDS.Xml.getNodeValue(BELNode, 'basedOn')),
					IFDS.Xml.getNodeValue(feeConfigXML, 'basedOn/@status'));
				dataPanel.addSubField(_translationMap['BrokerCommision'], 
					IFDS.Xml.getNodeValue(BELNode, 'brokerComm'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'brokerComm/@status'));
				dataPanel.addSubField(_translationMap['WithholdRate'], 
					IFDS.Xml.getNodeValue(BELNode, 'withHoldRate'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'withHoldRate/@status'));
				dataPanel.addSubField(_translationMap['DSCBasedRate'], 
					IFDS.Xml.getNodeValue(BELNode, 'dscBasedRate'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'dscBasedRate/@status'));
				dataPanel.addSubField(_translationMap['MinVarDSC'], 
					IFDS.Xml.getNodeValue(BELNode, 'minVarDsc'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'minVarDsc/@status'));			
				dataPanel.addSubField(_translationMap['DSCOverride'], 
					IFDS.Xml.getNodeValue(BELNode, 'dscOverride'),
					IFDS.Xml.getNodeValue(feeConfigXML, 'dscOverride/@status'));		
				dataPanel.addSpacer();			
			}
		}
		
		dataPanel.addSubHeader(_translationMap['FeeDetlScales']);
		var feeScaleNodes = IFDS.Xml.getNodes(feeConfigXML, 'FeeDetlScales/FeeScale');
		for (var i = 0; i < feeScaleNodes.length; i++)
		{
			dataPanel.addSubField("&#8805;" + IFDS.Xml.getNodeValue(feeScaleNodes[i], 'lower') + "   &lt;" + IFDS.Xml.getNodeValue(feeScaleNodes[i], 'upper'),
				IFDS.Xml.getNodeValue(feeScaleNodes[i], 'rate') + "%",
				IFDS.Xml.getNodeValue(feeScaleNodes[i], 'runMode'));
		}
		if (feeScaleNodes.length % 2 != 0)
		{
			dataPanel.addSpacer();
		}
		
		var displayIWT = null;
		
		if (_addMode)
		{
			var isIWTDomiciledFund = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//IWTDomiciledFund').toLowerCase() == 'yes';
			var isIWTEnabled = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//IWTEnabled').toLowerCase() == 'yes';
			displayIWT = isIWTDomiciledFund && isIWTEnabled;
		}
		else
		{
			displayIWT = (IFDS.Xml.getNodeValue(feeConfigXML, 'IWTDomiciledFund').toLowerCase() == 'yes' &&	
							  IFDS.Xml.getNodeValue(feeConfigXML, 'IWTEnabled').toLowerCase() == 'yes')
		}
		
		if(displayIWT)
		{
			dataPanel.addSubHeader(_translationMap['IWTFee']);
	
			var iwtXMLNode = IFDS.Xml.getNode(feeConfigXML,'IWT');
	
			dataPanel.addSubField(_translationMap['EighthAnnivDeMinimusOption'],
				getValueDescFromList('deminimisOptsList', IFDS.Xml.getNodeValue(iwtXMLNode, 'deminimisOpt')),
				IFDS.Xml.getNodeValue(iwtXMLNode, 'deminimisOpt/@status'));
				
			dataPanel.addSubField(_translationMap['MFRPaidBy'],
				 getValueDescFromList('mfrTaxOptList', IFDS.Xml.getNodeValue(iwtXMLNode, 'mfrTaxOpt')),
				 IFDS.Xml.getNodeValue(iwtXMLNode, 'mfrTaxOpt/@status'));
		
			dataPanel.addSubFieldDate(_translationMap['FirstDeemedDisposalDate'],
				IFDS.Xml.getNodeValue(iwtXMLNode, 'deemedDate1'),
				IFDS.Xml.getNodeValue(iwtXMLNode, 'deemedDate1/@status'));

			dataPanel.addSubFieldDate(_translationMap['SecondDeemedDisposalDate'],
				IFDS.Xml.getNodeValue(iwtXMLNode, 'deemedDate2'),
				IFDS.Xml.getNodeValue(iwtXMLNode, 'deemedDate2/@status'));		
			dataPanel.addSpacer();
		}
		
	}
	
	function populateFeeModelConfig(dataPanel)
	{
		try{
			var feeModelConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'FeeModelConfiguration') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'FeeModelConfiguration') : 
				IFDS.Xml.getNode(_existingClassDataXML,'FeeModelConfiguration'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
		
		dataPanel.addSubHeader(_translationMap['ManagementFee']);
		dataPanel.addSubField(_translationMap['ManagementFeeApplicable'], 
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFee'),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFee/@status'));
		dataPanel.addSubField(_translationMap['ManagementFeePayOption'], 
			getValueDescFromList('MgmtFeePayOptionList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeePayOpt')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeePayOpt/@status'));
		dataPanel.addSubField(_translationMap['ManagementFeeBrokerPortion'], 
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeBroker'),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeBroker/@status'));
		dataPanel.addSubField(_translationMap['ManagementFeeBrokerChange'], 
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeBrokChg'),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeBrokChg/@status'));		
		dataPanel.addSubField(_translationMap['AcctAggr'], 
			getValueDescFromList('AcctAggrList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeAcctAggr')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeAcctAggr/@status'));					
		dataPanel.addSubField(_translationMap['FundAggr'], 
			getValueDescFromList('FundAggrList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeFundAggr')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeFundAggr/@status'));					
		dataPanel.addSubField(_translationMap['ProrateOpt'], 
			getValueDescFromList('ProrateList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeProrateOpt')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mgmtFeeProrateOpt/@status'));
		dataPanel.addSpacer();
			
		dataPanel.addSubHeader(_translationMap['ManagementFeeRebate']);
		dataPanel.addSubField(_translationMap['MFRApplicatble'], 
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mfrRebate'),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mfrRebate/@status'));	
		dataPanel.addSubField(_translationMap['AcctAggr'], 
			getValueDescFromList('AcctAggrList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'mfrAcctAggr')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mfrAcctAggr/@status'));
		dataPanel.addSubField(_translationMap['FundAggr'], 
			getValueDescFromList('FundAggrList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'mfrFundAggr')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'mfrFundAggr/@status'));		
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['AdvisorFee']);
		dataPanel.addSubField(_translationMap['AdvisorFeeAppl'], 
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'advFee'),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'advFee/@status'));
		dataPanel.addSubField(_translationMap['AcctAggr'], 
			getValueDescFromList('AcctAggrList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'advAcctAggr')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'advAcctAggr/@status'));
		dataPanel.addSubField(_translationMap['FundAggr'], 
			getValueDescFromList('FundAggrList', IFDS.Xml.getNodeValue(feeModelConfigXML, 'advFundAggr')),
			IFDS.Xml.getNodeValue(feeModelConfigXML, 'advFundAggr/@status'));
		dataPanel.addSpacer();
		
	}
	
	function populateTradeDayCtrls(dataPanel)
	{
		try{
			var tradeDayCtrlsXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'TradeDayControls') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'TradeDayControls') : 
				IFDS.Xml.getNode(_existingClassDataXML,'TradeDayControls'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
			
		dataPanel.addSubHeader(_translationMap['AutoForceCancelDays']);
		dataPanel.addSubField(_translationMap['Purchase'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'purAutoCancDays'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'purAutoCancDays/@status'));
		dataPanel.addSubField(_translationMap['Redemption'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'redAutoCancDays'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'redAutoCancDays/@status'));
		dataPanel.addSubField(_translationMap['Exchange'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'exchAutoCancDays'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'exchAutoCancDays/@status'));
		dataPanel.addSubField(_translationMap['Transfer'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tfrAutoCancDays'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tfrAutoCancDays/@status'));
		
		dataPanel.addSubHeader(_translationMap['CutOffDays']);
		dataPanel.addSubField(_translationMap['Purchase'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/Purchase/numDays') + " (" + getValueDescFromList('DayTypes', IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/Purchase/dayType')) + ")",
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/Purchase/numDays/@status'));
		
		var redCutOffTime = IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/Redemption/cutOffTime');
		if (_perfFeeFlag && redCutOffTime != "")
		{
			String.prototype.splice = function( idx, rem, s ) { return (this.slice(0,idx) + s + this.slice(idx + Math.abs(rem))); }; 
			redCutOffTime = " (" + redCutOffTime.splice(2, 0, ':') + ")";
		}else{
			redCutOffTime = "";
		}
		dataPanel.addSubField(_translationMap['Redemption'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/Redemption/numDays') + " (" + getValueDescFromList('DayTypes', IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/Redemption/dayType')) + ") " + redCutOffTime,
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/Redemption/numDays/@status'));
		dataPanel.addSubField(_translationMap['ExchangeIn'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/ExchangeIn/numDays') + " (" + getValueDescFromList('DayTypes', IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/ExchangeIn/dayType')) + ")",
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/ExchangeIn/numDays/@status'));
		dataPanel.addSubField(_translationMap['ExchangeOut'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/ExchangeOut/numDays') + " (" + getValueDescFromList('DayTypes', IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/ExchangeOut/dayType')) + ")",
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'CutOffDays/ExchangeOut/numDays/@status'));
		
		dataPanel.addSubHeader(_translationMap['TradeLeadDays']);
		dataPanel.addSubField(_translationMap['TradeLeadDays'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tradeLeadDays'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tradeLeadDays/@status'));
		dataPanel.addSubField(_translationMap['Purchase'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tradeLeadDaysPur'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tradeLeadDaysPur/@status'));
		dataPanel.addSubField(_translationMap['Redemption'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tradeLeadDaysRed'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'tradeLeadDaysRed/@status'));
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['Miscellaneous']);
		dataPanel.addSubFieldDate(_translationMap['LastSettleDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastSetlDate'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastSetlDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['NextSettleDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'nextSetlDate'),			
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'nextSetlDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['LastValuationDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastValDate'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastValDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['NextValuationDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'nextValDate'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'nextValDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['LastCycleDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastNR'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastNR/@status'));
		dataPanel.addSubFieldDate(_translationMap['NextCycleDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'nextNR'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'nextNR/@status'));
		dataPanel.addSubFieldDate(_translationMap['LastMgmtFeeDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastMFeeDate'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastMFeeDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['LastMFRDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastMFRDate'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastMFRDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['LastTFRDate'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastTFRDate'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastTFRDate/@status'));
		dataPanel.addSubField(_translationMap['NAVCalcDays'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'navCalcDays'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'navCalcDays/@status'));
		dataPanel.addSubField(_translationMap['PymtLeadDays'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'pymtLeadDays') + " (" + getValueDescFromList('DayTypes', 'B') + ")",
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'pymtLeadDays/@status'));
		dataPanel.addSubField(_translationMap['MfrPymtLeadDays'], 
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'mfrPymtLeadDays') + " (" + getValueDescFromList('DayTypes', 'B') + ")",
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'mfrPymtLeadDays/@status'));
		dataPanel.addSubFieldDate(_translationMap['LastDividendDate'], 
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastDivdDate'),
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastDivdDate/@status'));
		
		if (_perfFeeFlag)
		{
			dataPanel.addSubFieldDate(_translationMap['LastCrystalisationDate'], 
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastCrysDate'),
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'lastCrysDate/@status'));
		}else{
			dataPanel.addSpacer();
		}
		dataPanel.addSubField(_translationMap['TradeDayDelay'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'TradeDayDelay/numDays') + " (" + getValueDescFromList('DayTypes', IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'TradeDayDelay/dayType')) + ")",
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'TradeDayDelay/numDays/@status'));
		dataPanel.addSubField(_translationMap['RedemptionNoticePeriod'], 
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'redNoticePeriod'),
			IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'redNoticePeriod/@status'));
		
		dataPanel.addSubHeader(_translationMap['PurPymtLeadDays']);
		dataPanel.addSubField(_translationMap['PurPymtLeadUnitDays'], 
				getPurDaysVal('PurchaseDays/PurPymtLeadDays/unitDays','PurchaseDays/PurPymtLeadDays/unitDayType'),
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/PurPymtLeadDays/unitDays/@status'));
		//if amount type is * , unit days values is showed in summary as amount days
		if(IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/PurPymtLeadDays/amountType')=='*') {
			dataPanel.addSubField(_translationMap['PurPymtLeadAmtDays'], 
					getPurDaysVal('PurchaseDays/PurPymtLeadDays/unitDays','PurchaseDays/PurPymtLeadDays/unitDayType'),
					IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/PurPymtLeadDays/unitDays/@status'));
		} else {
			dataPanel.addSubField(_translationMap['PurPymtLeadAmtDays'], 
					getPurDaysVal('PurchaseDays/PurPymtLeadDays/amountDays','PurchaseDays/PurPymtLeadDays/amountDayType'),
					IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/PurPymtLeadDays/amountDays/@status'));
		}
		dataPanel.addSubField(_translationMap['DiffSettleCurrUnitDays'], 
				getPurDaysVal('PurchaseDays/DiffSettleCurr/unitDays','PurchaseDays/DiffSettleCurr/unitDayType'),
				IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/DiffSettleCurr/unitDays/@status'));
		//if amount type is * , unit days values is showed in summary as amount days
		if(IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/DiffSettleCurr/amountType')=='*') {
			dataPanel.addSubField(_translationMap['DiffSettleCurrAmtDays'], 
					getPurDaysVal('PurchaseDays/DiffSettleCurr/unitDays','PurchaseDays/DiffSettleCurr/unitDayType'),
					IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/DiffSettleCurr/unitDays/@status'));
		} else {
			dataPanel.addSubField(_translationMap['DiffSettleCurrAmtDays'], 
					getPurDaysVal('PurchaseDays/DiffSettleCurr/amountDays','PurchaseDays/DiffSettleCurr/amountDayType'),
					IFDS.Xml.getNodeValue(tradeDayCtrlsXML, 'PurchaseDays/DiffSettleCurr/amountDays/@status'));
		}
		
		function getPurDaysVal(days,dayType){
			var value = '';
			if(IFDS.Xml.getNodeValue(tradeDayCtrlsXML, days)!='') {
				value = IFDS.Xml.getNodeValue(tradeDayCtrlsXML, days) + " (" + getValueDescFromList('DayTypes',
					IFDS.Xml.getNodeValue(tradeDayCtrlsXML, dayType)) + ")";
			}
			return value;
		}
	}
	
	function populateSettleDayCtrls(dataPanel){
		try{
			var settleDayCtrlsXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'SettleDayControls') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'SettleDayControls') : 
				IFDS.Xml.getNode(_existingClassDataXML,'SettleDayControls'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
		
		dataPanel.addSubField(_translationMap['PurchaseSettlementDays'], 
				getDaysVal('PurStlmtDays/PurSettDays'),getStatus('PurStlmtDays/PurSettDays'));
		dataPanel.addSubField(_translationMap['DifferentSettlementCurrency'], 
				getDaysVal('PurStlmtDays/DiffSettCurr'),getStatus('PurStlmtDays/DiffSettCurr'));
		
		dataPanel.addSubField(_translationMap['RedemptionSettlementDays'], 
				getDaysVal('RedSettDays'),getStatus('RedSettDays'));

		dataPanel.addSubField(_translationMap['ExchangeInSettlementDays'], 
				getDaysVal('ExInSettDays'),getStatus('ExInSettDays'));
		
		dataPanel.addSubField(_translationMap['ExchangeOutSettlementDays'], 
				getDaysVal('ExOutSettDays'),getStatus('ExOutSettDays'));
		
		dataPanel.addSubField(_translationMap['TransferInSettlementDays'], 
				getDaysVal('XferInSettDays'),getStatus('XferInSettDays'));
		
		dataPanel.addSubField(_translationMap['TransferOutSettlementDays'], 
				getDaysVal('XferOutSettDays'),getStatus('XferOutSettDays'));
		dataPanel.addSpacer();
		
		function getDaysVal(node){
			var unitDaysVal = IFDS.Xml.getNodeValue(settleDayCtrlsXML, node +'/unitDays');
			var amtDaysVal = IFDS.Xml.getNodeValue(settleDayCtrlsXML, node +'/amountDays');
			var amtTypVal = IFDS.Xml.getNodeValue(settleDayCtrlsXML, node +'/amountType'); 
			if (amtTypVal=='*' || (unitDaysVal== '' && amtDaysVal == '')){
				return unitDaysVal;
			}else{
				return _translationMap['Unit'] +": "+ unitDaysVal+" , "+_translationMap['Amount']+": "+amtDaysVal;
			}
		}
		
		function getStatus(node){
			var unitStatus = IFDS.Xml.getNodeValue(settleDayCtrlsXML, node +'/unitDays/@status');
			var amtStaus = IFDS.Xml.getNodeValue(settleDayCtrlsXML, node +'/amountDays/@status'); 
			if (unitStatus=='m' || amtStaus=='m'){
				return 'm';
			}
			return '';
		}
	}
	
	function populateGIAAttributes(dataPanel)
	{
		try{
			var giaAttributesXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML, 'GIAAttributes') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'GIAAttributes') : 
				IFDS.Xml.getNode(_existingClassDataXML,'GIAAttributes'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
						
		dataPanel.addField(_translationMap['IntCalcMethod'], 
			getValueDescFromList("IntCalcMethodList", IFDS.Xml.getNodeValue(giaAttributesXML, 'intCalcMthd')), 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'intCalcMthd/@status'));
		dataPanel.addField(_translationMap['SimpleIntTerms'], 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'simTermList'), 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'simTermList/@status'));
		var simCredFreqDesc = IFDS.Xml.getNodeValue(giaAttributesXML, 'simCredFreq').split(",");
		for (var i = 0; i < simCredFreqDesc.length; i++)
		{
			simCredFreqDesc[i] = getValueDescFromList('SimpleCreditFreq', simCredFreqDesc[i]);
		}
		dataPanel.addField(_translationMap['SimpleCreditFreq'], 
			simCredFreqDesc, 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'simCredFreq/@status'));
			
		dataPanel.addField(_translationMap['CompoundIntTerms'], 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'comTermList'), 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'comTermList/@status'));
		var comCredFreqDesc = IFDS.Xml.getNodeValue(giaAttributesXML, 'comCredFreq').split(",");
		for (var i = 0; i < comCredFreqDesc.length; i++)
		{
			comCredFreqDesc[i] = getValueDescFromList('CompoundCreditFreq', comCredFreqDesc[i]);
		}
		dataPanel.addField(_translationMap['CompoundCreditFreq'], 
			comCredFreqDesc, 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'comCredFreq/@status'));
			
		dataPanel.addField(_translationMap['DefaultRenewOption'], 
			getValueDescFromList('DefRenewList', IFDS.Xml.getNodeValue(giaAttributesXML, 'defRenewInstr')), 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'defRenewInstr/@status'));			
		dataPanel.addField(_translationMap['RedemptionOrder'], 
			getValueDescFromList('RedemOrderList', IFDS.Xml.getNodeValue(giaAttributesXML, 'redemOrder')),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'redemOrder/@status'));			
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['MVAAttributes']);
		dataPanel.addSubField(_translationMap['CurrMktIntRate'], 
			getValueDescFromList('MVACurrMktRate', IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaCurrMktRate')),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaCurrMktRate/@status'));
		dataPanel.addSubField(_translationMap['GainLossOffset'], 
			getValueDescFromList('MVAGLOffset', IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaGLOff')),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaGLOff/@status'));
		dataPanel.addSubField(_translationMap['PayNetGain'], 
			getValueDescFromList('MVAPayNetGain', IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaPayNetGain')),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaPayNetGain/@status'));
		dataPanel.addSubField(_translationMap['AdjEmpAcct'], 
			getValueDescFromList('MVAonEmpAcct', IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaEmpAcct')),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'mvaEmpAcct/@status'));
		dataPanel.addSubField(_translationMap['AdjFee'], 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'adjustFee'),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'adjustFee/@status'));
		dataPanel.addSubFieldDate(_translationMap['EffectiveDate'], 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'adjustFeeDate'),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'adjustFeeDate/@status'));
		
		dataPanel.addSubHeader(_translationMap['AdminFee']);
		dataPanel.addSubField(_translationMap['ChargesApplyTo'], 
			getValueDescFromList('AdminFeeApplyTo', IFDS.Xml.getNodeValue(giaAttributesXML, 'adminFeeApply')),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'adminFeeApply/@status'));
		dataPanel.addSubField(_translationMap['FeeType'], 
			getValueDescFromList('AttrFeeTypeList', IFDS.Xml.getNodeValue(giaAttributesXML, 'feeTypeAttr')),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'feeTypeAttr/@status'));
		dataPanel.addSubFieldDate(_translationMap['EffectiveDate'], 
			IFDS.Xml.getNodeValue(giaAttributesXML, 'adminFeeDate'),
			IFDS.Xml.getNodeValue(giaAttributesXML, 'adminFeeDate/@status'));
		if (IFDS.Xml.getNodeValue(giaAttributesXML, 'feeTypeAttr') == '1')
		{
			dataPanel.addSubField(_translationMap['Fee'], 
				IFDS.Xml.getNodeValue(giaAttributesXML, 'adminFee'),
				IFDS.Xml.getNodeValue(giaAttributesXML, 'adminFee/@status'));	
		}
		else
		{
			dataPanel.addSpacer();
			dataPanel.addSubHeader(_translationMap['FeeScales']);
			var feeScaleNodes = IFDS.Xml.getNodes(giaAttributesXML, 'ScaleDetl');
			for (var i = 0; i < feeScaleNodes.length; i++)
			{
				dataPanel.addSubField("&#8805;" + IFDS.Xml.getNodeValue(feeScaleNodes[i], 'lower') + "   &lt;" + IFDS.Xml.getNodeValue(feeScaleNodes[i], 'upper'),
					IFDS.Xml.getNodeValue(feeScaleNodes[i], 'rate') + "%",
					IFDS.Xml.getNodeValue(feeScaleNodes[i], 'runMode'));
			}
			if (feeScaleNodes.length % 2 != 0)
			{
				dataPanel.addSpacer();
			}		
		}
	}
	
	function populateIntConfig(dataPanel)
	{
		try{
			var intConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML, 'IntConfig') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'IntConfig') : 
				IFDS.Xml.getNode(_existingClassDataXML,'IntConfig'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
			
		dataPanel.addField(_translationMap['SimpleIntRateCode'], 
			IFDS.Xml.getNodeValue(intConfigXML, 'simIRCode'),
			IFDS.Xml.getNodeValue(intConfigXML, 'simIRCode/@status'));					
		dataPanel.addField(_translationMap['CompoundIntRateCode'], 
			IFDS.Xml.getNodeValue(intConfigXML, 'comIRCode'),
			IFDS.Xml.getNodeValue(intConfigXML, 'comIRCode/@status'));						
	}
	
	function populatePerfFeeConfig(dataPanel)
	{
		try{
			var perfFeeConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML, 'PerfFeeConfig') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'PerfFeeConfig') : 
				IFDS.Xml.getNode(_existingClassDataXML,'PerfFeeConfig'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
		
		dataPanel.addField(_translationMap['PerformanceFeeMethod'], 
			getValueDescFromList('feeMethod', IFDS.Xml.getNodeValue(perfFeeConfigXML, 'feeMethod')),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'feeMethod/@status'));
		dataPanel.addField(_translationMap['CalcBasis'], 
			getValueDescFromList('calcBasis', IFDS.Xml.getNodeValue(perfFeeConfigXML, 'calcBasis')),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'calcBasis/@status'));
		dataPanel.addField(_translationMap['LossCarryForwardOption'], 
			getValueDescFromList('lossCarryForward', IFDS.Xml.getNodeValue(perfFeeConfigXML, 'lossCarryForward')),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'lossCarryForward/@status'));
		dataPanel.addField(_translationMap['DividendAddedBack'], 
			getValueDescFromList('divAddBack', IFDS.Xml.getNodeValue(perfFeeConfigXML, 'divAddBack')),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'divAddBack/@status'));
		dataPanel.addField(_translationMap['DefaultLotReductionMethod'], 
			getValueDescFromList('lotRedMethod', IFDS.Xml.getNodeValue(perfFeeConfigXML, 'lotRedMethod')),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'lotRedMethod/@status'));
		dataPanel.addField(_translationMap['CalcPrecision'], 
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'perfFeeCalcPrecision'),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'perfFeeCalcPrecision/@status'));
		dataPanel.addField(_translationMap['PerfFeePrecision'], 
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'perfFeePrecision'),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'perfFeePrecision/@status'));
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['InitialValues']);
		dataPanel.addSubField(_translationMap['InitialGAV'], 
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'gavRate'),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'gavRate/@status'));
		dataPanel.addSubField(_translationMap['InitialHWMPerShare'], 
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'classHWMRate'),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'classHWMRate/@status'));
		dataPanel.addSubFieldDate(_translationMap['FirstValuationdate'], 
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'eventDate'),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'eventDate/@status'));
		dataPanel.addSubFieldDate(_translationMap['InitialHWMDate'], 
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'classHWMResetDate'),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'classHWMResetDate/@status')
			);
		
		dataPanel.addField(_translationMap['HurdleApplicable'], 
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'hurdleApply'),
			IFDS.Xml.getNodeValue(perfFeeConfigXML, 'hurdleApply/@status'));
		dataPanel.addSpacer();
		
		var hurdleApplied = IFDS.Xml.getNodeValue(perfFeeConfigXML, 'hurdleApply');
		if (hurdleApplied == 'yes')
		{
			var hurdleGrid = new DesktopWeb.AdvancedControls.GridPanel(
				{							
					title: ''
					,autoScroll: true
					,height: 130
					,autoExpandColumn: 'fixedRate'
					,store: new Ext.data.XmlStore(
						{
							record: 'PerfFeeHurdleConfig'
							,fields: ['hurdleConfigUUID', 'benchmarkType', 'fixedRate', 'indexCode', 'adjRate', 'daysBasis', 'weighting', 'runMode']
							,listeners: {
								load: function(store, records)
								{
									store.filterBy(function(record){return record.data.runMode != 'd'});
									hurdleGrid.getSelectionModel().lock();
								}
							}
						}
					)
					,selModel: new Ext.grid.RowSelectionModel(
						{
							
						}
					)
					,colModel: new Ext.grid.ColumnModel(
						{
							defaults: {
								menuDisabled: true							
								,sortable: false
							}
							,columns: [
								{header: _translationMap['BenchmarkType'], dataIndex: 'benchmarkType', width: 100
									,renderer: function(val){return getValueDescFromList('benchmarkType', val);}}
								,{id: 'fixedRate', header: _translationMap['FixRate'], dataIndex: 'fixedRate'
									,renderer: function(val){return (val && val.length>0)?val + '%':val;}}
								,{header: _translationMap['BenchmarkIndex'], dataIndex: 'indexCode', width: 125
									,renderer: function(val){return getValueDescFromMktIndex('indexCode', val);}}
								,{header: _translationMap['BenchmarkAdjRate'], dataIndex: 'adjRate', width: 175
									,renderer: function(val){return (val && val.length>0)?val + '%':val;}}
								,{header: _translationMap['DayBasis'], dataIndex: 'daysBasis', width: 100
									,renderer: function(val){return getValueDescFromList('daysBasis', val);}}
								,{header: _translationMap['Weight'], dataIndex: 'weighting', width: 100
									,renderer: function(val){return (val && val.length>0)?val + '%':val;}}
							]							
						}
					)
					,buttons: [
					]
				}
			)
			hurdleGrid.getStore().loadData(IFDS.Xml.getNode(perfFeeConfigXML, "PerfFeeHurdleConfigs"));
			dataPanel.add(hurdleGrid);
			dataPanel.doLayout();
		}
	}
	
	function populateEventFreq(dataPanel)
	{
		try{
			var eventFreqConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML, 'EventFreqConfig') ? 
				IFDS.Xml.getNode(_updatedClassDataXML,'EventFreqConfig') : 
				IFDS.Xml.getNode(_existingClassDataXML,'EventFreqConfig'));
		}catch(e){throw new Error("Error retreiving cached data " + e.desc)}
		
		dataPanel.addField(_translationMap['FundGroupCode'], 
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/fundGroup'),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/fundGroup/@status'));
		dataPanel.addField(_translationMap['HolidayCode'], 
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/holidayCode'),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/holidayCode/@status'));
		dataPanel.addField(_translationMap['Description'], 
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/fundGroupDesc'),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/fundGroupDesc/@status'));
		dataPanel.addField(_translationMap['SettlementHolidayCode'], 
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/settleHolidayCode'),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/settleHolidayCode/@status'));
		dataPanel.addField(_translationMap['BusinessDayCode'], 
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/busDayCode'),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/busDayCode/@status'));
		dataPanel.addField(_translationMap['AdditionalDayListCode'], 
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/additionalDayCode'),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/additionalDayCode/@status'));
		dataPanel.addField(_translationMap['StlCurHldy'], 
			getValueDescFromList('stlCurHldy', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/stlCurHldy')),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/stlCurHldy/@status'));
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['CutOffTime']);
		dataPanel.addSubField(_translationMap['FundGroupLevel'], 
			stringToTime(IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffFundGrp')),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffFundGrp/@status'));
		dataPanel.addSubField(_translationMap['TimeZone'], 
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffTimeZone'),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffTimeZone/@status'));
		dataPanel.addSubField(_translationMap['ClientLevel'], 
			stringToTime(IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffClient')),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffClient/@status'));
		dataPanel.addSubField(_translationMap['AggregationLevel'], 
			stringToTime(IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffAggregate')),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffAggregate/@status'));
		dataPanel.addSubField(_translationMap['MarketLevel'], 
			stringToTime(IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffMarket')),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/cutOffMarket/@status'));
		dataPanel.addSubField(_translationMap['NSCCOffset'], 
				IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/nsccOffSet'),
				IFDS.Xml.getAttributeValue(eventFreqConfigXML, 'ValnSched/nsccOffSet/@status'));
		dataPanel.addSpacer();
		
		dataPanel.addSubHeader(_translationMap['ValuationFrequency']);
		dataPanel.addFieldValue(
			getValueDescFromList('freqOn', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqOn'))
			,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqOn/@status')
			,getValueDescFromList('freqType', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqType'))
			,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqType/@status'));
		dataPanel.addFieldValue(
			getValueDescFromList('freqDay', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqDay'))
			,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqDay/@status')
			,getValueDescFromList('freqMonth', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqMonth'))
			,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'ValnSched/ValnSchedFreq/freqMonth/@status'));
		
		var divFundGroupCode = IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/fundGroup');
		if(divFundGroupCode)
		{
			dataPanel.addField(_translationMap['FundGroupCode'], 
				IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/fundGroup'),
				IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/fundGroup/@status'));
			dataPanel.addSpacer();
			dataPanel.addField(_translationMap['Description'], 
				IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/fundGroupDesc'),
				IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/fundGroupDesc/@status'));
			dataPanel.addSpacer();
			
			dataPanel.addSubHeader(_translationMap['DividendFrequency']);
			dataPanel.addFieldValue(
				getValueDescFromList('freqOn', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqOn'))
				,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqOn/@status')
				,getValueDescFromList('freqType', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqType'))
				,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqType/@status'));
			dataPanel.addFieldValue(
				getValueDescFromList('freqDay', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqDay'))
				,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqDay/@status')
				,getValueDescFromList('freqMonth', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqMonth'))
				,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'DivSched/DivSchedFreq/freqMonth/@status'));
		}
		
		if (_perfFeeFlag)
		{
			var crysNode = IFDS.Xml.getNode(eventFreqConfigXML, 'CrysSched');
			if(crysNode)
			{
				dataPanel.addSubHeader(_translationMap['CrystalisationFrequency']);
				dataPanel.addFieldValue(
					getValueDescFromList('freqOn', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqOn'))
					,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqOn/@status')
					,getValueDescFromList('freqType', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqType'))
					,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqType/@status'));
				dataPanel.addFieldValue(
					getValueDescFromList('freqDay', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqDay'))
					,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqDay/@status')
					,getValueDescFromList('freqMonth', IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqMonth'))
					,IFDS.Xml.getNodeValue(eventFreqConfigXML, 'CrysSched/CrysSchedFreq/freqMonth/@status'));
			}
			
			var dealingNode = IFDS.Xml.getNode(eventFreqConfigXML, 'DealSched/DealSchedDetls/DealSchedDetl');
			if(dealingNode)
			{
				dataPanel.addSubHeader(_translationMap['DealingFrequency']);
				var dealFreqNodes = IFDS.Xml.getNodes(eventFreqConfigXML, 'DealSched/DealSchedDetls/DealSchedDetl');
				Ext.each(dealFreqNodes, function(dealFreqNode){
					if (IFDS.Xml.getNodeValue(dealFreqNode, 'runMode') != 'd')
					{
						dataPanel.addField(getTransTypeDisplay(IFDS.Xml.getNodeValue(dealFreqNode, 'transType')), '', '');
						dataPanel.addSpacer();
						dataPanel.addFieldValue(
							getValueDescFromList('freqOn', IFDS.Xml.getNodeValue(dealFreqNode, 'freqOn'))
							,IFDS.Xml.getNodeValue(dealFreqNode, 'freqOn/@status')
							,getValueDescFromList('freqType', IFDS.Xml.getNodeValue(dealFreqNode, 'freqType'))
							,IFDS.Xml.getNodeValue(dealFreqNode, 'freqType/@status'));
							//,true);
						dataPanel.addDateFieldValue(
							getValueDescFromList('freqDay', IFDS.Xml.getNodeValue(dealFreqNode, 'freqDay'))
							,IFDS.Xml.getNodeValue(dealFreqNode, 'freqDay/@status')
							,getValueDescFromList('freqMonth', IFDS.Xml.getNodeValue(dealFreqNode, 'freqMonth'))
							,IFDS.Xml.getNodeValue(dealFreqNode, 'freqMonth/@status'));
					}
				});
			}
		}	
		
		var redemDealingFreqNode = IFDS.Xml.getNodeValue(eventFreqConfigXML, 'redDealFreq');
		if(redemDealingFreqNode) {
			dataPanel.addSubField(_translationMap['RedemptionDealingFreq'], 
			getValueDescFromList('RedDealFreqList', redemDealingFreqNode),
			IFDS.Xml.getNodeValue(eventFreqConfigXML, 'redDealFreq/@status'));
			dataPanel.addSpacer();		
		}

		function getTransTypeDisplay(val)
		{
			var display = ''
			if(val)
			{
				var transTypes = val.split(',');
				Ext.each(transTypes, function(transType){
					display += getValueDescFromList('dealTransType', transType) + ",";
				});
				display = display.substring(0, display.length-1);
			}
			return display;
		}

		function stringToTime(val)
		{
			if(val && val.length == 4)
			{
				return val.substring(0,2) + ':' + val.substring(2);
			}
			return '';
		}
	}
	
	function goToScreen(screenName)
	{
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_' + screenName;
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
		
		if (screenName == "Search")
		{
			urlParams['createCache'] = 'true';	
		}
		else
		{
			urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];	
		}			
				
		window.location = DesktopWeb.Ajax.buildURL(urlParams);
	}
	
	function getValueDescFromList(listId, value)
	{
		var desc = IFDS.Xml.getNodeValue(_initDataXML, 'List[@id = "' + listId + '"]/Element[code = "' + value + '"]/value');
		// if @id didn't work, try @listName
		if (!desc)
		{
			desc = IFDS.Xml.getNodeValue(_initDataXML, 'List[@listName = "' + listId + '"]/Element[code = "' + value + '"]/value');
		}
		return desc;
	}
	
	function getValueDescFromMktIndex(listId, value)
	{
		var mktIdxNodes = IFDS.Xml.getNode(_initDataXML, '//MktIndexes');
		var mktIdxList = IFDS.Xml.getNodes(mktIdxNodes, 'MktIndex');
			
		for (var i = 0; i < mktIdxList.length; i++)
		{
			var mktIndex = mktIdxList[i];
			var indexCode = IFDS.Xml.getNodeValue(mktIndex, 'indexCode');
			if ( indexCode == value)
			{
				var desc = IFDS.Xml.getNodeValue(mktIndex, 'indexName');
				return desc;
			}
		}
		
		return value;
	}
	function submitUpdatedClassData(action)
	{
		addHeaderToUpdatedClassData(action);
		
		DesktopWeb.Ajax.doSmartviewCall(_updateView, null, _updatedClassDataXML, responseHandler, _translationMap["ProcMsg_Processing"]);
		
		function responseHandler(responseXML)
		{
			var smartviewResults = DesktopWeb.Ajax.parseSmartviewResponse(IFDS.Xml.getNode(responseXML, _updateView + 'Response'));
			 
			if (smartviewResults.successful)
			{					
				DesktopWeb.Util.displayInfo(_translationMap["infoSuccess"], function(){goToScreen('Search')});					
			}
		}
	}
	
	function addHeaderToUpdatedClassData(action)
	{
		if (_addMode)
		{
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'processingMode', 'update');
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'runMode', _self.ADD);		
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'verifyFlag', 'no');	
		}
		else
		{
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'processingMode', 'update');
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'runMode', _self.MOD);
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'fundCode', IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundCode'));
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'classCode', IFDS.Xml.getNodeValue(_existingClassDataXML, 'classCode'));
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'fundDetlVer', IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundDetlVer'));
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'fundInfoVer', IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundInfoVer'));
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'feeDetlVer', IFDS.Xml.getNodeValue(_existingClassDataXML, 'feeDetlVer'));
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'feeDetlRID', IFDS.Xml.getNodeValue(_existingClassDataXML, 'feeDetlRID'));
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'fundCategory', IFDS.Xml.getNodeValue(_existingClassDataXML, 'fundCategory'));
			IFDS.Xml.addSingleNode(_updatedClassDataXML, 'verifyFlag', (action=='verify') ? 'yes' : 'no');
		}
	}
	
	function updateVerifyToUpdatedClassData()
	{
		if (_addMode)
		{
			//var deff = DesktopWeb.Util.stringToDate(IFDS.Xml.getNodeValue(_updatedClassDataXML, '//ClassBasic/deff'), "mdy");
			//var stopDate = deff;		
			//stopDate.setDate(deff.getDate() - 1);
			
			
			//IFDS.Xml.setNodeValue(IFDS.Xml.getNode(_updatedClassDataXML, '//ClassBasic/stat'), "04");
			//IFDS.Xml.setNodeValue(IFDS.Xml.getNode(_updatedClassDataXML, '//ClassBasic/stopDate'), DesktopWeb.Util.dateToString(stopDate, "mdy"));			
		}
		else
		{
			
		}
	}
	
	function populateVerifyObj()
	{
		if (_addMode)
		{
			Ext.getCmp("verify").hide();
			Ext.getCmp("verifyStatus").hide();
		}
		else
		{
			if (_allowVerify)
			{
				Ext.getCmp("verify").show();
			}
			else
			{
				Ext.getCmp("verify").hide();
			}
			
			if (_verifyFlag)
			{
				Ext.getCmp("verifyStatus").hide();
			}
			else
			{
				Ext.getCmp("verifyStatus").show();
			}
		}
	}
	
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'a', MOD: 'm', DEL: 'd'


		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
						
			DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ExistingClassData', 'ScreenDefList', 'UpdatedClassData'], responseHandler, _translationMap['ProcMsg_Loading'])
			 								
			function responseHandler(responseXML)
			{	
				_initDataXML = IFDS.Xml.getNode(responseXML, "InitData/*");
				_screenDefListXML = IFDS.Xml.getNode(responseXML, "ScreenDefList/*");				
				_existingClassDataXML = IFDS.Xml.getNode(responseXML, "ExistingClassData/*");				
				_updatedClassDataXML = IFDS.Xml.getNode(responseXML, "UpdatedClassData/*");

				_addMode = (_existingClassDataXML == null);
				
				if (!_addMode && !_screenDefListXML)
				{	
					_screenDefListXML = buildScreenDefListXML();	
					_updatedClassDataXML = IFDS.Xml.stringToXML("<data></data>");					
					DesktopWeb.Ajax.doUpdateCache({ScreenDefList: _screenDefListXML, UpdatedClassData: _updatedClassDataXML}, function(){});	
				}
				
				try{

					var feeConfigXML = (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML,'FeeConfiguration') ? 
						IFDS.Xml.getNode(_updatedClassDataXML,'FeeConfiguration') : 
						IFDS.Xml.getNode(_existingClassDataXML,'FeeConfiguration'));

					_perfFeeFlag = (IFDS.Xml.getNodeValue(feeConfigXML, 'perfFeeFlag') == 'yes');
					
				}catch(e){throw new Error("Error getting Performance Fee Flag: " + e.desc )}
							
				try{
					var _verifyActive = _existingClassDataXML && (IFDS.Xml.getNodeValue(_existingClassDataXML, '//Admin/verifyActive') == "yes");
					_verifyFlag = _verifyActive && (_existingClassDataXML && IFDS.Xml.getNodeValue(_existingClassDataXML, '//ClassBasic/stat') == "04") ? false : true;
					_allowVerify = _verifyActive && (_existingClassDataXML && IFDS.Xml.getNodeValue(_existingClassDataXML,'//Admin/allowVerify') == 'yes') ? true : false;					
				}catch(e){throw new Error("Error getting Verify Flag: " + e.desc)}
				
				setHeader();
				populateScreen();
				populateVerifyObj();
			}
		}
		
		,collapseAllDataPanels: function()
		{	
			var container = Ext.getCmp("dataPanelContainer");			
			for (var i  = 0; i < container.items.getCount(); i++)
			{
				container.get(i).collapse();
			}
		}
		
		,expandAllDataPanels: function()
		{
			var container = Ext.getCmp("dataPanelContainer");			
			for (var i  = 0; i < container.items.getCount(); i++)
			{
				container.get(i).expand();
			}
		}
		
		,edit: function(screenName)
		{
			DesktopWeb.Util.displayProcessing(_translationMap['ProcMsg_Loading']);
			goToScreen(screenName);			
		}
		
		,ok: function()
		{			
			if (_updatedClassDataXML.xml != "" && IFDS.Xml.getNode(_updatedClassDataXML, '*'))
			{
				if (!_verifyFlag && _allowVerify)
				{					
					var stopDate = "12/31/9999";
					if (_updatedClassDataXML && IFDS.Xml.getNode(_updatedClassDataXML, 'ClassBasic'))
					{
						if (IFDS.Xml.getNodeValue(_updatedClassDataXML, 'ClassBasic/stopDate') != IFDS.Xml.getNodeValue(_existingClassDataXML, 'ClassBasic/stopDate'))
						{
							stopDate = IFDS.Xml.getNodeValue(_updatedClassDataXML, 'ClassBasic/stopDate') ;
						}
					}
					
					DesktopWeb.Util.displayYesNo(_translationMap['AskVerifyAfterChanged'] + stopDate, callback);
					
					function callback(buttonId)
					{								
						if (buttonId == 'no')
						{
							submitUpdatedClassData();
						}
					}
				}
				else
				{
					submitUpdatedClassData();
				}
			}
			else
			{
				goToScreen('Search');
			}			
		}
		
		,cancel: function()
		{
			goToScreen('Search');
		}
		
		,verify: function()
		{
			DesktopWeb.Util.displayPrompt(_translationMap['ConfirmVerify'], callback);
			
			function callback(buttonId)
			{		
				if (buttonId == 'ok')
				{
					submitUpdatedClassData('verify');
				}
			}			
		}
	}	
}
