/*********************************************************************************************
 * @file	ClassSetup_PriceInfo.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Price Information screen, part of Class Setup flow
 *********************************************************************************************/
 /*
 * Procedure: ClassSetup_PriceInfo.Controller.js
 *
 * Purpose  : Price information screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Price information screens
 *
 * History  : 
 *  12 Nov 2012 H.Sartsangchan Created. 
 *          IN3135980 Load type validation does not work properly on Class setup
 *          - Add value to Fund Load Group depend on “FundLoadGrouping” Generic Control 
 *          - Can't Modify Fund Load Group in Edit Mode
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  10 Dec 2015 Winnie Cheng P0248498 CHG0043235 T81863
 *          - Adding one dropdown field : capstock rate type
 *           
 *  30 Mar 2018 Winnie Cheng P0275379-35 MMFR R18.4
 *          - Adding validation for fixed Rate based on fixed price flag
 *
 *  07 May 2018 Pao - Supareuk S.
 *  		In goToScreen function, we changed a way to show the page from window.location 
 *  		using buildURL to DesktopWeb.Util.goToScreen. This is to solve an issue when 
 *  		user's profile has too many slot attached. If the session is included, the page
 *  		will be broken as too large.
 *  
 *  03 July 2018 Sreejith.A P0277704 P0277704-3
 *  		- Added Custom valuation schedule validation	
 *  
 *  23 July 2018 Winnie Cheng P0277183-158 Intraday Pricing R18.5
 *          - Allowing to set up intraday pricing set when applicable
 *      
 *  16 Aug 2018 Winnie Cheng P0275379-220 MMFR R18.4 DFT0085747
 *  		FixRate validation allow zero value when FixPrice is Yes
 *     
 *  17 Aug 2018 Winnie Cheng P0277138-220 MMFR R18.5 DFT0085748
 *  		Intraday PopUp pricePoint field layout is not aligned with Price Code field
 *          
 *  22 Aug 2018 Winnie Cheng P0275379-221 MMFR R18.5 DFT0085956
 *  		Intraday PopUp pricePoint field values needs to be reset if one of value is blank 
 */

DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _addMode = null;
	var _screenId = "PriceInfo";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	
	var _intradayPricingDataXML = null;
	var _nextUUID = 1;
	var _valIntraDayPricing = 'dtIntraDayVal';//Intraday API
	
	// PRIVATE METHODS ****************************************
	function setHeader()
	{
		var fundCode = null;
		var classCode = null;
		if (_addMode)
		{
			fundCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundCode');
			classCode = IFDS.Xml.getNodeValue(_updatedClassDataXML, '//classCode');			
			if (classCode == "")
			{
				classCode = "*" + _translationMap['New'].toUpperCase() + "*";
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
		}
		
		var screenLabel = IFDS.Xml.getNodeValue(_screenDefListXML, 'Screen[id = "' + _screenId + '"]/label')
		_resources.header.setText(screenLabel + ' - ' + _translationMap['Fund'] + ': ' + fundCode + ', ' + _translationMap['Class'] + ': ' + classCode);
	}
	
	function populateBreadCrumbList()
	{
		var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
				
		for (var i = 0; i < screenDefNodes.length; i++)
		{
			var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id');			
			_resources.breadCrumbList.addItem(id, IFDS.Xml.getNodeValue(screenDefNodes[i], 'label'));
			
			if (id == _screenId)
			{
				_screenIndex = i;
			}							
		}		
		
		if (_addMode)
		{
			_resources.breadCrumbList.disableAll();
			for (var i = 0; i <= _screenIndex; i++)
			{	
				 var id = IFDS.Xml.getNodeValue(screenDefNodes[i], 'id') 
				_resources.breadCrumbList.enableItem(id);										
			}
		}
		else
		{						
			_resources.breadCrumbList.enableAll();
		}
		_resources.breadCrumbList.setActiveItem(_screenId);
	}
	
	function displayScreenButtons()
	{
		if (_addMode)
		{			
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			if (_screenIndex != 0)
			{
				//not the first
				Ext.getCmp('prevBtn').enable();
			}
			
			if (_screenIndex < screenDefNodes.length - 1)
			{				
				Ext.getCmp('nextBtn').setText(_translationMap['Next']);
			}
			else
			{
				Ext.getCmp('nextBtn').setText(_translationMap['Summary']);
			}
			Ext.getCmp('prevBtn').show();
			Ext.getCmp('cancelBtn').show();
			Ext.getCmp('nextBtn').show();			
		}
		else
		{
			Ext.getCmp('summaryBtn').show();
		}
	}
	
	function populateDropdowns()
	{
		_resources.fields['currency'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'CurrencyList']"));				
		_resources.fields['schedTransType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'SchedTransTypeList']"));
		_resources.fields['priceVarType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'PriceVarTypeList']"));
		if (IFDS.Xml.getNode(_initDataXML, "List[@id = 'FundLoadGrpList']") != null)
		{         
		 _resources.fields['loadGrp'].setVisible(true);
		 _resources.fields['loadGrp'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'FundLoadGrpList']"));		   
		}
		else
		{         
		 _resources.fields['loadGrp'].setVisible(false);        
		}    
		_resources.fields['unitsCalc'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'UnitCalcList']"));
		_resources.fields['allocType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'AllocTypeList']"));
		_resources.fields['gavApply'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'gavApply']"));
		
		_resources.popups['validSettleCurr'].init(IFDS.Xml.getNode(_initDataXML, "List[@id = 'CurrencyList']"));	
		//CPF
		_resources.fields['roundFlag'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'RoundFlagList']"));
		//Capstock FX rate type
		_resources.fields['capstockRateType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'ERTypeList']"));
		
		//set next business day and cut off time
		var intraDayPricingNode = IFDS.Xml.getNode(_initDataXML, '//PriceInfo/intraDayPricings');
		if(intraDayPricingNode != null) {
			var nextBusDayRaw = IFDS.Xml.getNodeValue(intraDayPricingNode, 'nextBusDay') ;
	 	    var cutOffTimeRaw = IFDS.Xml.getNodeValue(intraDayPricingNode, 'cutOffTime');
	 	    _resources.popups['pricePointPopUp'].nextBusDay = nextBusDayRaw;
			_resources.popups['pricePointPopUp'].cutOffTime = cutOffTimeRaw.substring(0, 2) + ':' + cutOffTimeRaw.substring(2,4);
		}
		//price points dropdown dynamic
		if (IFDS.Xml.getNode(_initDataXML, "List[@id = 'intraDayPricePoints']") != null) {
			_resources.popups['pricePointPopUp'].setDropDownData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'intraDayPricePoints']"));
			_resources.popups['pricePointPopUp'].createPointRows();
		}
	}	
	
	function populateScreen()
	{
		var priceInfoXML = IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo');
		
		for (var i in _resources.fields)
		{
			setInitialFieldValue(_resources.fields[i], IFDS.Xml.getNodeValue(priceInfoXML, i));	
		}
		
		if (_addMode && IFDS.Xml.getNodeValue(priceInfoXML, 'gavApply') == '')
		{
			_resources.fields['gavApply'].setValue(IFDS.Xml.getNodeValue(_initDataXML, "ListSelection[@id = 'gavApply']"));
		}
		//cpf
		if (_addMode && IFDS.Xml.getNodeValue(priceInfoXML, 'roundFlag') == '')
		{
			_resources.fields['roundFlag'].setValue(IFDS.Xml.getNodeValue(_initDataXML, "ListSelection[@id = 'RoundFlagList']"));
		}
		
		if (!_addMode)
		{
		 _resources.fields['loadGrp'].disableField();
		}     
		
		function setInitialFieldValue(fld, val)
		{			
			if (val != "") 
			{		
				fld.setValue(val);
			}
			else
			{
				fld.reset();
			}	
		}
		//validating/formatting fixedRate data
		_self.validatefixPriceRateflds(_self.YES);
		
		//IntraDayPricing enable from a function controls
		if (IFDS.Xml.getNodeValue(_initDataXML, '//intraDayPricing') == 'yes') {
			Ext.getCmp('intradayExist').show();
			
			var intraPriceAct = IFDS.Xml.getNodeValue(priceInfoXML, '//intraPriceAct');
			if (intraPriceAct != null && intraPriceAct != '') {  
				_resources.field['intraPriceAct'].setValue(intraPriceAct);
			}
			
			if(IFDS.Xml.getNodeValue(_initDataXML, '//intraDayPricings/cutOffTime') != '') {
				populateIntradayGrids();
			} else {
				_resources.grids['intradayPricing'].disableButton('addBtn');
			}
		} else {
			Ext.getCmp('intradayExist').hide();
		}
	}
	
	function updateIntraDayPricingButtons(record) {
		if(record != null) {
			var recStopDT = DesktopWeb.Util.stringToDate(record.data['endDate'], DesktopWeb.Util.getDateDisplayFormat());
			var nextbussDate = DesktopWeb.Util.stringToDate(_resources.popups['pricePointPopUp'].nextBusDay, 'mdy');
			var recDeffDate = DesktopWeb.Util.stringToDate(record.data['startDate'], DesktopWeb.Util.getDateDisplayFormat());

			if (recStopDT < nextbussDate){
				_resources.grids['intradayPricing'].disableButton('modBtn'); 
				_resources.grids['intradayPricing'].disableButton('delBtn');
			} else {
				_resources.grids['intradayPricing'].enableButton('modBtn'); 
				if(recDeffDate < nextbussDate) {
					_resources.grids['intradayPricing'].disableButton('delBtn');
				} else {
					_resources.grids['intradayPricing'].enableButton('delBtn');
				}
			}
		}
		if (record == null || record.data == null || record.data < 1) {
			_resources.grids['intradayPricing'].disableButton('adminBtn');
			_resources.grids['intradayPricing'].disableButton('moreBtn');
			_resources.grids['intradayPricing'].disableButton('delBtn');
		} else {
			if (record.data['runMode'] == _self.ADD) {
				_resources.grids['intradayPricing'].disableButton('adminBtn'); 
			} else {
				_resources.grids['intradayPricing'].enableButton('adminBtn');
			}
		}
	}
	
	// Populate Intraday price point grid
	function populateIntradayGrids() {
		//intradayPricing pricePoint
		var intraDayPricingNode = null;//this will be the grid final records
		var existingIntraDayPricingNode = IFDS.Xml.getNode(_existingClassDataXML, '//PriceInfo/intraDayPricings');
		var updatedIntraDayPricingNode = IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo/intraDayPricings');
		var runMode =  IFDS.Xml.getNodeValue(updatedIntraDayPricingNode, '//intraDayPricing/runMode');
		
		if (runMode != null && runMode != '') {
			if(updatedIntraDayPricingNode) {
				intraDayPricingNode = updatedIntraDayPricingNode;
			} else {//populate all existing records
				intraDayPricingNode = existingIntraDayPricingNode;
			}
			//concatenate existing records
			if(existingIntraDayPricingNode) {
				var existingPricings = IFDS.Xml.getNodes(existingIntraDayPricingNode, "intraDayPricing");
				if(existingPricings) { //excluding modify record
					Ext.each(existingPricings, function(existingPricing) {
						var existingPricingUUID = IFDS.Xml.getNodeValue(existingPricing, "intraDayPricingUUID");
						//compare this UUID with all updated records
						var foundMatch = false;
						var updatedPricings = IFDS.Xml.getNodes(updatedIntraDayPricingNode, "intraDayPricing");
						if(updatedPricings) {
							Ext.each(updatedPricings, function(updatedPricing) {
								var updatedPricingUUID = IFDS.Xml.getNodeValue(updatedPricing, "intraDayPricingUUID");
								if(existingPricingUUID == updatedPricingUUID) {
									foundMatch = true;
								}
							});
							//Append existing record
							if(!foundMatch) {
								var lastNode = IFDS.Xml.getNode(intraDayPricingNode, '//intraDayPricings');
								IFDS.Xml.appendNode(intraDayPricingNode, IFDS.Xml.cloneDocument(existingPricing));
							}
						}
					});
				}
			}
		} else {
			intraDayPricingNode = existingIntraDayPricingNode;
		}

 	   	_intradayPricingDataXML = intraDayPricingNode;
 
		_resources.grids['intradayPricing'].loadData(intraDayPricingNode);

		//get pricing nodes 
		var pricings = IFDS.Xml.getNodes(intraDayPricingNode, "intraDayPricing");
		if(pricings) {
			Ext.each(pricings, function(pricing) { 
				var pricingPointsNode = IFDS.Xml.getNode(pricing, "intraDayPricingPoints");
				var pointsXMLStr = IFDS.Xml.serialize(pricingPointsNode);
				var pricingUUID = IFDS.Xml.getNodeValue(pricing, "intraDayPricingUUID");
				var priceRecords = _resources.grids['intradayPricing'].getStore().queryBy(function(record){ 
					return record.get('intraDayPricingUUID') == pricingUUID});
				//generated points XML
				priceRecords.itemAt(0).set('intraDayPricingPoints', pointsXMLStr);
			});
		}
		_resources.grids['intradayPricing'].selectFirstRecord();
	}
			
	function clearGrid(name) {
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function disableCustValuation() {
	
		var settleDayCtrlsXML = null;
		settleDayCtrlsXML = IFDS.Xml.getNode(_updatedClassDataXML,'SettleDayControls');
		if (settleDayCtrlsXML == null) {
			settleDayCtrlsXML = IFDS.Xml.getNode(_existingClassDataXML,'SettleDayControls');
		}
		if (settleDayCtrlsXML != null) {
			checkSettleDayControl('PurStlmtDays/PurSettDays/amountDays');
			checkSettleDayControl('PurStlmtDays/DiffSettCurr/amountDays');
			checkSettleDayControl('PurStlmtDays/DiffSettCurr/unitDays');
			checkSettleDayControl('RedSettDays/amountDays');
			checkSettleDayControl('ExInSettDays/amountDays');
			checkSettleDayControl('ExOutSettDays/amountDays');
			checkSettleDayControl('XferInSettDays/amountDays');
			checkSettleDayControl('XferOutSettDays/amountDays');
		}

		function checkSettleDayControl(xPath) {
			if (IFDS.Xml.getNodeValue(settleDayCtrlsXML, xPath) != '') {
				_resources.fields['schedTransType'].disableField();
			}
		}
	}
	
	function addChangeHandlers()
	{		
		for (var i in _resources.fields)
		{
			addHandler(_resources.fields[i]);									
		}
		
		
		function addHandler(fld)
		{
			if (fld instanceof Ext.form.Checkbox)
			{
				fld.addListener('check', function(){setChangeFlag()})
			}
			else if (fld instanceof DesktopWeb.Controls.ComboBox)
			{
				fld.addListener('select', function(){setChangeFlag()})
			}
			else
			{
				fld.addListener('change', function(){setChangeFlag()})
			}
		}		
	}
	
	function setChangeFlag()
	{
		_changeFlag = true;
		Ext.getCmp('resetBtn').enable();
		Ext.getCmp('saveBtn').enable();
	}
	
	function clearChangeFlag()
	{
		_changeFlag = false;
		Ext.getCmp('resetBtn').disable();
		Ext.getCmp('saveBtn').disable();
	
		if(_resources.grids['intradayPricing'].store.getCount() == 0) {
			clearGrid('intraDayPricingPoint');
		}
	}
	
	function updateXML()
	{
		var priceInfoXML = IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo');
		
		var xmlWriteFn = null; 
		if (_addMode)
		{
			writeNewValueToXML('runMode', _self.ADD);			
			xmlWriteFn = writeNewValueToXML;
		}
		else
		{
			writeNewValueToXML('runMode', _self.MOD);
			xmlWriteFn = writeUpdatedValueToXML;
		}
		
		for (var i in _resources.fields)
		{
			xmlWriteFn(i, _resources.fields[i].getValue());	
		}

		//Intraday Pricing set
		var intradayDetlNodes = IFDS.Xml.getNodes(priceInfoXML, 'intraDayPricings');
		if(intradayDetlNodes != null) {
			for (var i = 0; i < intradayDetlNodes.length; i++) {
			  IFDS.Xml.deleteNode(intradayDetlNodes[i]);
			}	
			var intraDayPricingsNode = IFDS.Xml.addSingleNode(priceInfoXML, 'intraDayPricings');
			Ext.each(_resources.grids['intradayPricing'].getAllRecords(), function(rec) {
				addIntradayRecordToXML(rec)
			})
			
			function addIntradayRecordToXML(rec) {
				if(rec.get('runMode') != '') {
					var intraDayPricingNode = IFDS.Xml.addSingleNode(intraDayPricingsNode, 'intraDayPricing');
					IFDS.Xml.addSingleNode(intraDayPricingNode, 'runMode', rec.get('runMode'));
		 		    IFDS.Xml.addSingleNode(intraDayPricingNode, 'intraDayPricingUUID', rec.get('intraDayPricingUUID'));
					IFDS.Xml.addSingleNode(intraDayPricingNode, 'startDate', DesktopWeb.Util.getSMVDateValue(rec.get('startDate')));
					IFDS.Xml.addSingleNode(intraDayPricingNode, 'endDate', DesktopWeb.Util.getSMVDateValue(rec.get('endDate')));
					IFDS.Xml.addSingleNode(intraDayPricingNode, 'pricePointCnt', rec.get('pricePointCnt'));
					
					var intraDayPricingPointsStr = rec.get('intraDayPricingPoints');	
					if (intraDayPricingPointsStr != null && intraDayPricingPointsStr.length > 0) {
						//convert XML string to XML nodes
						var intraDayPricingPointsXMLInGrid = IFDS.Xml.stringToXML(intraDayPricingPointsStr);
						var intraDayPricingPointsInGrid = IFDS.Xml.getNodes(intraDayPricingPointsXMLInGrid, "intraDayPricingPoint");
						//insert the parent node of all points node
						var intraDayPricingPointsNode = IFDS.Xml.addSingleNode(intraDayPricingNode, 'intraDayPricingPoints');
						Ext.each(intraDayPricingPointsInGrid, function(intraDayPricingPointInGrid){
							buildUpdateLinkedAcctXML(intraDayPricingPointInGrid, intraDayPricingPointsNode)});
						
						function buildUpdateLinkedAcctXML(intraDayPricingPointInGrid, context) {
							var intraDayPricingPointXML = IFDS.Xml.addSingleNode(context, 'intraDayPricingPoint');
							IFDS.Xml.addSingleNode(intraDayPricingPointXML, 'intraDayPriceInstrUUID', rec.get('intraDayPricingUUID'));
							IFDS.Xml.addSingleNode(intraDayPricingPointXML, 'priceCode', IFDS.Xml.getNodeValue(intraDayPricingPointInGrid, 'priceCode'));
							IFDS.Xml.addSingleNode(intraDayPricingPointXML, 'timePoint', IFDS.Xml.getNodeValue(intraDayPricingPointInGrid, 'timePoint'));
							IFDS.Xml.addSingleNode(intraDayPricingPointXML, 'usedForDivPricing', IFDS.Xml.getNodeValue(intraDayPricingPointInGrid, 'usedForDivPricing'));
		               }//build pricePoints xml
					}
				}
			}
		}
		
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? priceInfoXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? priceInfoXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}			
	}
	
	function validateScreen()
	{
		var isValid = true;
		for (var i in _resources.fields)
		{		
			//additional validation need for the field that marks as invalid
			var isMarkInvalid = _resources.fields['fixRate'].isMarkInvalid;
			if(isMarkInvalid != null && isMarkInvalid == true) {
				isValid = false;
			}
			if (_resources.fields[i].isValid)
			{
				isValid =  _resources.fields[i].isValid() && isValid;
			}								
		}
		return isValid;
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
		urlParams['prevScreen'] = _screenId;
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
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'a', MOD: 'm', DEL: 'd', YES: 'yes'
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			DesktopWeb.Ajax.doRetrieveCache(['InitData', 'ScreenDefList', 'ExistingClassData', 'UpdatedClassData'], responseHandler, _translationMap['ProcMsg_Loading'])
			 								
			function responseHandler(responseXML)
			{													
				_initDataXML = IFDS.Xml.getNode(responseXML, 'InitData/*');
				_screenDefListXML = IFDS.Xml.getNode(responseXML, 'ScreenDefList/*');	
				_existingClassDataXML = IFDS.Xml.getNode(responseXML, 'ExistingClassData/*');				
				_updatedClassDataXML = IFDS.Xml.getNode(responseXML, 'UpdatedClassData/data');
				
				if (_initDataXML == null || _screenDefListXML == null || _updatedClassDataXML == null)
				{
					throw new Error("Error retrieving cached data");
				}				
				
				_addMode = (_existingClassDataXML == null);
				if (_addMode)
				{
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo'))
					{
						IFDS.Xml.addSingleNode(_updatedClassDataXML, 'PriceInfo');
					}
				}
				else
				{
					if (!IFDS.Xml.getNode(_updatedClassDataXML, 'PriceInfo'))
					{										
						IFDS.Xml.appendNode(_updatedClassDataXML, 
							IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'PriceInfo')));
					}	
				}							
				
				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateDropdowns();
				addChangeHandlers();				
				populateScreen();
				disableCustValuation();
				clearChangeFlag();									
			}
		}
		
		,editValidSettleCurr: function()
		{
			_resources.popups['validSettleCurr'].populate();
			_resources.popups['validSettleCurr'].show();	
		}

		,openPointsPopup: function(action) {
			_resources.popups['pricePointPopUp'].init(action);
			_resources.popups['pricePointPopUp'].show();
		}
		
		,getIntradayUUID: function() {
			return "TMPINTRADAY" + (_nextUUID++);
		}
		
		,selectIntradayPrice: function(record) {
			updateIntraDayPricingButtons(record);
			clearGrid('intraDayPricingPoint');
			if (record.data['intraDayPricingPoints'] && record.data['intraDayPricingPoints'].length > 0) {
				var pricePointsXML = IFDS.Xml.stringToXML(record.data['intraDayPricingPoints']);
				_resources.grids['intraDayPricingPoint'].loadData(pricePointsXML);
			} 
		}
		
		,valIntradayPricing: function(action, data) {
			var dataXML = IFDS.Xml.newDocument('data');
			var popup = _resources.popups['pricePointPopUp'];
			var intradayXML = IFDS.Xml.addSingleNode(dataXML, 'intraDayPricing');
			
			var runMode = action;
			if (action == this.MOD) {
				var selectedIntradayRecord = _resources.grids['intradayPricing'].getSelectedRecord();
				if (selectedIntradayRecord.data['runMode'] == this.ADD) runMode = this.ADD;
			}
			
			IFDS.Xml.addSingleNode(intradayXML, 'runMode', runMode);
			IFDS.Xml.addSingleNode(intradayXML, 'intraDayPricingUUID', data['intraDayPricingUUID']);
			IFDS.Xml.addSingleNode(intradayXML, 'startDate', DesktopWeb.Util.getSMVDateValue(popup.getField('effectiveDateFrom').getDisplayDateString()));
			IFDS.Xml.addSingleNode(intradayXML, 'endDate', DesktopWeb.Util.getSMVDateValue(popup.getField('effectiveDateTo').getDisplayDateString()));
			IFDS.Xml.addSingleNode(intradayXML, 'fundCode', IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundCode'));
			IFDS.Xml.addSingleNode(intradayXML, 'classCode', IFDS.Xml.getNodeValue(_updatedClassDataXML, '//classCode'));
			
			var pricePointsXML = IFDS.Xml.addSingleNode(intradayXML, 'intraDayPricingPoints');
			var pricePointsRecords = data['pointsRecords'];
			
			for (var i = 0; i < pricePointsRecords.length; i++) {
				var pricePointRecord = pricePointsRecords[i];
				var princePointXML = IFDS.Xml.addSingleNode(pricePointsXML, 'intraDayPricingPoint');
				IFDS.Xml.addSingleNode(princePointXML, 'pricingPointUUID', pricePointRecord['pricingPointUUID']);
				IFDS.Xml.addSingleNode(princePointXML, 'timePoint', pricePointRecord['timePoint']);
				IFDS.Xml.addSingleNode(princePointXML, 'priceCode', pricePointRecord['priceCode']);
				var priceCode = pricePointRecord['priceCode'];
				var selected = 'no';
				if(priceCode == data['pricePointsOpts']) {
					selected = 'yes';
				}
				IFDS.Xml.addSingleNode(princePointXML, 'usedForDivPricing', selected);
			}
			//popUp validating
			DesktopWeb.Ajax.doSmartviewAjax(_valIntraDayPricing, null, dataXML, responseHandler, _translationMap['Validating']);
			function responseHandler(success, responseXML, contextErrors, contextWarnings) {
				if (success) {
					_self.saveIntraDayPricing(action, data);
					_resources.popups['pricePointPopUp'].hide();
				}
			}
		 }
		
		,saveIntraDayPricing: function(action, data) {
			if (action != this.DEL) {
				var dataXML = IFDS.Xml.newDocument('data');				
				//point option
				var pointParentXML = IFDS.Xml.addSingleNode(dataXML, 'intraDayPricingPoints');
				var pricePointsOpts = data['pricePointsOpts']

				var pointsRecords = data['pointsRecords'];
				for(var i = 0; i < pointsRecords.length; i++) {
					var pointXML = IFDS.Xml.addSingleNode(pointParentXML, 'intraDayPricingPoint');
					var priceCode = pointsRecords[i]['priceCode'];
					IFDS.Xml.addSingleNode(pointXML, 'priceCode', priceCode);
					IFDS.Xml.addSingleNode(pointXML, 'timePoint', pointsRecords[i]['timePoint']);
					var selected = 'no';
					if(priceCode == pricePointsOpts) {
						selected = 'yes';
					}
					IFDS.Xml.addSingleNode(pointXML, 'usedForDivPricing', selected);
				}
				
				_resources.grids['intraDayPricingPoint'].loadData(pointParentXML);
				
				var pointsXMLStr = IFDS.Xml.serialize(pointParentXML);
				
				data['intraDayPricingPoints'] = pointsXMLStr;
				if(action == this.ADD) {
					_resources.grids['intradayPricing'].addRecord(data);
					_resources.grids['intradayPricing'].selectLastRecord();
				} else {
					_resources.grids['intradayPricing'].updateSelectedRecord(data);
				}
			} else {
				var intradaySet = _resources.grids['intradayPricing'].getSelectedRecord();
				// annoying case where mod/del a brand new record
				if (_resources.grids['intradayPricing'].getSelectedRecord().data['runMode'] == this.ADD) {
					if (action == this.DEL) {
						_resources.grids['intradayPricing'].removeSelectedRecord();
						clearGrid('intraDayPricingPoint');
					} 					
				} else {
					_resources.grids['intradayPricing'].updateSelectedRecord(data);
					clearGrid('intraDayPricingPoint');
					_resources.grids['intradayPricing'].selectLastRecord();							
				}
			}					
			setChangeFlag();	
		}
		
		,closePricePointPopUp: function() {
			_resources.popups['pricePointPopUp'].hide();
		}
		
		,openAdminPopup: function() {			
			var title = null;	
			var selectedRecord = null;

			selectedRecord = _resources.grids['intradayPricing'].getSelectedRecord();
			title = _translationMap['IntradayPricing'] + ' - ' + _translationMap['Admin']

			var adminData = {};
			adminData['userName'] = selectedRecord.get('userName');
			adminData['procDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('processDate'));
			adminData['modUser'] = selectedRecord.get('modUser');
			adminData['modDate'] = DesktopWeb.Util.getDateDisplayValue(selectedRecord.get('modDate'));
			
			_resources.popups['admin'].init(title, adminData);
			_resources.popups['admin'].show();			
		}
		
		,updateValidSettleCurr: function()
		{
			_resources.fields['validSettleCurr'].setValue(_resources.popups['validSettleCurr'].getData());
			setChangeFlag();	
		}

		//fixed price and fixed rate validation and data formatting
		,validatefixPriceRateflds: function(init) {
			var localeVar = DesktopWeb._SCREEN_PARAM_MAP['locale']
			var priceFldVal = _resources.fields['fixPrice'].getValue();
			var rateFld = _resources.fields['fixRate'];
			var rateFldVal = rateFld.getValue();
			//initialization data formatting
			if(init == _self.YES) {
				if(localeVar == 'enUS') {//23,456.0000
					if(rateFldVal.indexOf(',') >= 0) {
						rateFld.setValue(rateFldVal.replace(',', ''));
					} 
				} else {//frCA
					if(rateFldVal.indexOf(' ') >= 0) {// 23 456,0000
						rateFld.setValue(rateFldVal.replace(' ', ''));
					}
					rateFld.setValue(rateFld.getValue().replace(',', '.'));
				}
			} 
			//modifying FixedPrice field YES/NO
			if (priceFldVal == _self.YES) {
				rateFld.enableField();
				if(parseFloat(rateFld.getValue()) == 0) {//0.0000
					rateFld.markInvalid(_translationMap['fixRateRequired']);
					rateFld.isMarkInvalid = true;
				}
			} else {
				rateFld.setValue('0.0000');
				rateFld.disableField();
				if(init != _self.YES) {
					DesktopWeb.Util.displayWarning(_translationMap['fixRateResetZero']);
					rateFld.isMarkInvalid = false;
				}
			}
		}
		
		//pattern only numerical allowed
		,isPatternMatched: function(fixRateValue) {
			var strPattern = /^[0-9,]*\.?[0-9,]*$/
			return strPattern.test(fixRateValue);
	    }
		
		//ignore few keys
		,isKeycodeAccept: function(keycode) {
			//left/right arrow, home/end keys
			var notAcceptKeys = [35,36,37,39];
			if(notAcceptKeys.indexOf(keycode) > 0) {
				return false;
			}
			return true;
	    }
		
		//keyUp and onChange data formating and validation
		,fixRateDataUpdate: function(fixRateValue) {
			var fixratePrice = _resources.fields['fixPrice'].getValue();
			var fixRateFld = _resources.fields['fixRate'];
			
			if(fixratePrice == _self.YES && fixRateValue != '') {
				if (_self.isPatternMatched(fixRateValue)) {
					var dotPositon=fixRateValue.indexOf('.');
					var beforeDot = '';
					var afterDot = '';
					var valLengthExceeded = false;
					
					if(dotPositon >= 0) { //if dot found
						beforeDot = parseFloat(fixRateValue.substring(0, dotPositon)); 
						beforeDot = beforeDot + '';//re-assign string var
						afterDot = fixRateValue.substring((dotPositon+1), fixRateValue.length);
						
						if (beforeDot != null && beforeDot != '' && beforeDot.length > 5) {
							beforeDot = beforeDot.substring(0,5); //5 digits
							valLengthExceeded = true;
						}
						if (afterDot != null && afterDot != '' && afterDot.length > 4) {
							afterDot = afterDot.substring(0, 4); //4 decimals
							valLengthExceeded = true;
						}
						
						if(beforeDot != '' && valLengthExceeded) {//setvalue
							fixRateFld.setValue(parseFloat(beforeDot) + '.' + afterDot);
						} else if (valLengthExceeded) {
							fixRateFld.setValue('0.' + afterDot);
						}
						
						if(parseFloat(fixRateFld.getValue()) == 0 ||fixRateFld.getValue() == '.' ) {
							fixRateFld.markInvalid(_translationMap['fixRateRequired']);
							fixRateFld.isMarkInvalid = true;
						}
					} else {// only digits
						if (parseFloat(fixRateFld.getValue()) == 0) {
							fixRateFld.markInvalid(_translationMap['fixRateRequired']);
							fixRateFld.isMarkInvalid = true;
						} else {
							if (fixRateValue != '' && fixRateValue.length > 5) {
								fixRateValue = parseFloat(fixRateValue.substring(0, 5));
							}
							fixRateFld.setValue(fixRateValue);
						}
					}
				} else {
					fixRateFld.markInvalid(fixRateValue + " " + _translationMap['isInValidNumber']);
				}
			} else {
				if(fixratePrice == _self.YES) {
					fixRateFld.markInvalid(_translationMap['FldRequired']);
				}
			}
	    }

		,changeScreen: function(screenName)		
		{
			if (screenName != _screenId)
			{			
				if (_changeFlag)
				{
					DesktopWeb.Util.displayDiscardPrompt(callback)
				}
				else
				{
					goToScreen(screenName)
				}
			}
			
			function callback(discard)
			{
				if (discard)
				{
					goToScreen(screenName);
				}
			}
		}
		
		,previous: function()		
		{
			var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
			goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex - 1], 'id'));	
		}
		
		,next: function()		
		{
			if (validateScreen())
			{
				if (_changeFlag)
				{		
					updateXML();					
					DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
				}
				else
				{
					callback();
				}
			}						
			
			function callback()
			{
				clearChangeFlag();
				var screenDefNodes = IFDS.Xml.getNodes(_screenDefListXML, 'Screen');
				if (_screenIndex < screenDefNodes.length - 1)
				{				
					goToScreen(IFDS.Xml.getNodeValue(screenDefNodes[_screenIndex + 1], 'id'));
				}
				else
				{
					goToScreen('Summary');
				}	
			}	
		}
		
		,reset: function()
		{
			DesktopWeb.Util.displayDiscardPrompt(callback);
			
			function callback(discard)
			{
				if (discard)
				{
					populateScreen();
					clearChangeFlag();
				}
			}
		}
		
		,save: function()
		{			
			if (validateScreen())
			{		
				updateXML();	
				DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
			}
			
			function callback()
			{
				clearChangeFlag();	
			}			
		}	
		
		,cancel: function()
		{
			DesktopWeb.Util.displayDiscardPrompt(callback);
			
			function callback(discard)
			{
				if (discard)
				{
					goToScreen('Search');
				}
			}
		}				
	}
}