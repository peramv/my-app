/*********************************************************************************************
 * @file	ClassSetup_BasicInfo.Controller.js	
 * @author	Rod Walker
 * @desc	Controller file for Basic Information screen, part of Class Setup flow
 *********************************************************************************************/
/*
 *  History : 
 *
 *  27 Dec 2013 G. Thawornwachirakun P0181067 CHG0035028 T54651
 *          - Fix display date format follows dateFormatDisplay parameter
 *
 *  05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  13 Oct 2014 Supareuk Sukjaitham  P0230233 FNXX T56126
 *          - Add the logic to show a warning message when classNameAutoSyncUp
 *            function control is turn off
 *          - Correct task number
 *
 *  24 July 2015 Winnie Cheng P0242521 FN01 T81053 R15.5
 *          - Added Prorated Transfer field to support MFS Proportional Transfers
 *          
 *   2 Feb 2015 dchatcha P0248860 CHG0043555 FN01 T82168 R16.3
 *          - Adding a new sub-category "GARS" for Manulife GARS and QROPS Reports
 *
 *  10 July 2016 Winnie Cheng P0255686 CHG0045295 FN01 T83008 R16.5
 *          - Adding a new "Allow Negative Balance" sub-category
 *
 *  22 July 2016 Matira T. P0256538 FN01 T83329 R16.5
 *          - Added the logic to show sub-categroy "CustomPayOFnd" and "PortfolioPayOFnd"
 *
 *  08 Nov 2016 Aurkarn M. P0256121 FN01 T84156 R17.2
 *          - Added the logic to show sub-categroy "Target Date Mutual Fund"
 *          
 *  07 Nov 2017 Sreejith A P0266789-1286 R18.2
 *          - Added the logic to show sub-categroy "MCH Assets"
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
	
	var _addMode = null;
	var _screenId = "BasicInfo";
	var _screenIndex = null;
	var _initDataXML = null;
	var _screenDefListXML = null;
	var _existingClassDataXML = null;
	var _updatedClassDataXML = null;	
	var _changeFlag = false;
	var _trackingType = null;
	var _verifyFlag = false;
	var fndClsAutoSyncUpFlg = null;
	
	
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
		_resources.fields['stat'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'StatusList']"));	
		if (!_verifyFlag)
		{
			_resources.fields['stat'].getStore().filterBy(
				function fn(record){ 
					return (record.get('code') == '01' || record.get('code') == '03' || record.get('code') == '04'); 
				}
			);
		}
		else
		{
			_resources.fields['stat'].getStore().filterBy(
				function fn(record){ 
					return (record.get('code') == '01' || record.get('code') == '03'); 
				}
			);
		}

		_resources.fields['company'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'CompanyCodeList']"));
		_resources.fields['bareTrustee'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'BareTrusteeList']"));	
		_resources.fields['loadType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'LoadTypeList']"));	
		if (IFDS.Xml.getNode(_initDataXML, "List[@id = 'TrackingTypeList']"))
		{
			_trackingType = true;
			_resources.fields['trackingType'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'TrackingTypeList']"));
		}
		else
		{
			_trackingType = false;
		}
		_resources.fields['riskRating'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'RiskRatingList']"));
		_resources.fields['FundCurHldyOpt'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'FundCurHldyOptList']"));
		_resources.fields['inventTrk_basedOn'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'BasedOnInvTrackList']"));
		_resources.fields['inventCat'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'InventoryCategoryList']"));
		_resources.fields['trfPayFreq'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@listName = 'TrfPayFreqList']"));
		_resources.fields['proratedXfer'].loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'ProratedXferList']"));
		_resources.popups['fundIdentifier'].getField('idType').loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'FundIdentifierList']"));
		_resources.popups['shareGroup'].getField('shGroup').loadData(IFDS.Xml.getNode(_initDataXML, "List[@id = 'ShGroupList']"));
		
		if (IFDS.Xml.getNodeValue(_initDataXML, "Controls/enableCustomPayout") == 'yes'){
			_resources.fields['fundSubCats']['26'].enableField();
		}else{
			_resources.fields['fundSubCats']['26'].disableField();
		}
		
		if (IFDS.Xml.getNodeValue(_initDataXML, "Controls/enablePortfolioPayout") == 'yes'){
			_resources.fields['fundSubCats']['27'].enableField();
		}else{
			_resources.fields['fundSubCats']['27'].disableField();
		}
		
		if (IFDS.Xml.getNodeValue(_initDataXML, "Controls/enableTargetDateMutualFund") == 'yes'){
			_resources.fields['fundSubCats']['29'].enableField();
		}else{
			_resources.fields['fundSubCats']['29'].disableField();
		}

		if (IFDS.Xml.getNodeValue(_initDataXML, "Controls/enableMCHAssets") == 'yes'){
			_resources.fields['fundSubCats']['32'].enableField();
		}else{
			_resources.fields['fundSubCats']['32'].disableField();
		}
	}
	
	function populateScreen()	
	{			
		if (_addMode)
		{	
			setInitialFieldValue(_resources.fields['fundCode'], IFDS.Xml.getNodeValue(_updatedClassDataXML, '//fundCode'));
			_resources.fields['fundCode'].disableField();
			setInitialFieldValue(_resources.fields['classCode'], IFDS.Xml.getNodeValue(_updatedClassDataXML, '//classCode'));					
			_resources.fields['classCode'].enableField();
		}
		else
		{
			setInitialFieldValue(_resources.fields['fundCode'], IFDS.Xml.getNodeValue(_existingClassDataXML, '//fundCode'));			
			_resources.fields['fundCode'].disableField();
			setInitialFieldValue(_resources.fields['classCode'], IFDS.Xml.getNodeValue(_existingClassDataXML, '//classCode'))				
			_resources.fields['classCode'].disableField();
		}	
		
		var basicInfoXML = IFDS.Xml.getNode(_updatedClassDataXML, 'ClassBasic');

		setInitialFieldValue(_resources.fields['classE'], IFDS.Xml.getNodeValue(basicInfoXML, 'classE'));
		setInitialFieldValue(_resources.fields['classF'], IFDS.Xml.getNodeValue(basicInfoXML, 'classF'));
		setInitialFieldValue(_resources.fields['stat'], IFDS.Xml.getNodeValue(basicInfoXML, 'stat'));
		setInitialFieldValue(_resources.fields['statDate'], 
			DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(basicInfoXML, 'statDate')));
		setInitialFieldValue(_resources.fields['stopDate'],
			DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(basicInfoXML, 'stopDate')));
		setInitialFieldValue(_resources.fields['deff'], 
			DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(basicInfoXML, 'deff')));
		setInitialFieldValue(_resources.fields['loadType'], IFDS.Xml.getNodeValue(basicInfoXML, 'loadType'));
		
		if (!_addMode)
		{
			_resources.fields['loadType'].disableField();
		}
		
		if (_trackingType)
		{		
			Ext.getCmp('trackingTypeField').show();	
			setInitialFieldValue(_resources.fields['trackingType'], IFDS.Xml.getNodeValue(basicInfoXML, 'trackingType'));		
		}	
		
	    setInitialFieldValue(_resources.fields['bareTrustee'], IFDS.Xml.getNodeValue(basicInfoXML, 'bareTrustee'));
		setInitialFieldValue(_resources.fields['riskRating'], IFDS.Xml.getNodeValue(basicInfoXML, 'riskRating'));
		setInitialFieldValue(_resources.fields['company'], IFDS.Xml.getNodeValue(basicInfoXML, 'company'));
		setInitialFieldValue(_resources.fields['FundCurHldyOpt'], IFDS.Xml.getNodeValue(basicInfoXML, 'FundCurHldyOpt'));
		
		setInitialFieldValue(_resources.fields['inventTrk_applicable'], IFDS.Xml.getNodeValue(basicInfoXML, 'InventoryTracking/applicable') == 'yes');		
		setInitialFieldValue(_resources.fields['inventTrk_basedOn'], IFDS.Xml.getNodeValue(basicInfoXML, 'InventoryTracking/basedOn'));		
		setInitialFieldValue(_resources.fields['inventCat'], IFDS.Xml.getNodeValue(basicInfoXML, 'cdicInvCat'));		
		setInitialFieldValue(_resources.fields['trfPayFreq'], IFDS.Xml.getNodeValue(basicInfoXML, 'trfPayFreq'));
		setInitialFieldValue(_resources.fields['proratedXfer'], IFDS.Xml.getNodeValue(basicInfoXML, 'proratedXfer'));
		
		var fundSubCatNodes = IFDS.Xml.getNodes(basicInfoXML, 'FundSubCategories/FundSubCat');
		
		for (var i = 0; i < fundSubCatNodes.length; i++)
		{
			var subCat = IFDS.Xml.getNodeValue(fundSubCatNodes[i], 'subCat'); 			
			var subCatFlag = IFDS.Xml.getNodeValue(fundSubCatNodes[i], 'subCatFlag');
			var subCatdesc = IFDS.Xml.getNodeValue(fundSubCatNodes[i], 'subCatDesc');
			var subCatStatus = IFDS.Xml.getNodeValue(fundSubCatNodes[i], 'active');
			if (!_resources.fields['fundSubCats'][subCat]) continue;
						
			//_resources.fields['fundSubCats'][subCat].setBoxLabel(subCatdesc);
			
			setInitialFieldValue(_resources.fields['fundSubCats'][subCat], subCatFlag == 'yes');
			
			if(subCatStatus != null && subCatStatus == '0') {
				_resources.fields['fundSubCats'][subCat].disableField();
			}
		}
		
		_resources.grids['fundIdentifier'].loadData(IFDS.Xml.getNode(basicInfoXML, 'FundIdentifiers'), ['addBtn']);			
		_resources.grids['shareGroup'].loadData(IFDS.Xml.getNode(basicInfoXML, 'ShareGroups'), ['addBtn']);			
		setInitialFieldValue(_resources.popups['shareGroup'].getField('deff')
			, DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(basicInfoXML, 'ShareGroups/shrDeff')));
		setInitialFieldValue(_resources.popups['shareGroup'].getField('active'), IFDS.Xml.getNodeValue(basicInfoXML, 'ShareGroups/active'));
	
		function setInitialFieldValue(fld, val)
		{			
			if (val != "") 
			{		
				fld.setValue(val);
			}
			else
			{
				if (fld.name != 'status') { fld.reset(); }
			}	
		}		
	}  
	
	function addChangeHandlers()
	{		
		for (var i in _resources.fields)
		{
			if (i != 'fundSubCats')
			{			
				addHandler(_resources.fields[i]);
			}					
		}
		
		for (var i in _resources.fields['fundSubCats'])
		{
			_resources.fields['fundSubCats'][i].addListener('check', function(){setChangeFlag()})
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
	}
	
	function updateXML()
	{
		var basicInfoXML = IFDS.Xml.getNode(_updatedClassDataXML, 'ClassBasic');
	
		var xmlWriteFn = null; 
		if (_addMode)
		{
			writeNewValueToXML('runMode', _self.ADD);
			writeNewValueToXML('classCode', _resources.fields['classCode'].getValue(), _updatedClassDataXML);
			xmlWriteFn = writeNewValueToXML;
		}
		else
		{
			writeNewValueToXML('runMode', _self.MOD);
			xmlWriteFn = writeUpdatedValueToXML;
		}
	
		xmlWriteFn('classE', _resources.fields['classE'].getValue());
		xmlWriteFn('classF', _resources.fields['classF'].getValue());
		xmlWriteFn('stat', _resources.fields['stat'].getValue());
		xmlWriteFn('statDate', _resources.fields['statDate'].getSMVDateString());
		xmlWriteFn('deff', _resources.fields['deff'].getSMVDateString());
		xmlWriteFn('stopDate', _resources.fields['stopDate'].getSMVDateString());
		xmlWriteFn('loadType', _resources.fields['loadType'].getValue());
		
		if (_trackingType) 
		{
			xmlWriteFn('trackingType', _resources.fields['trackingType'].getValue());
		}	
		xmlWriteFn('bareTrustee', _resources.fields['bareTrustee'].getValue());
		xmlWriteFn('riskRating', _resources.fields['riskRating'].getValue());
		xmlWriteFn('FundCurHldyOpt', _resources.fields['FundCurHldyOpt'].getValue());
		xmlWriteFn('company', _resources.fields['company'].getValue())			
		xmlWriteFn('cdicInvCat', _resources.fields['inventCat'].getValue())			
		xmlWriteFn('trfPayFreq', _resources.fields['trfPayFreq'].getValue())	
		xmlWriteFn('proratedXfer', _resources.fields['proratedXfer'].getValue());
		
		xmlWriteFn('applicable', 
			(_resources.fields['inventTrk_applicable'].getValue() ? 'yes' : 'no' ),
			IFDS.Xml.getNode(basicInfoXML, 'InventoryTracking'));		
		xmlWriteFn('basedOn', 
			_resources.fields['inventTrk_basedOn'].getValue(),
			IFDS.Xml.getNode(basicInfoXML, 'InventoryTracking'));			
		
		var subCatNodes = IFDS.Xml.getNodes(basicInfoXML, 'FundSubCategories/FundSubCat');
		for (var i = 0; i < subCatNodes.length; i++)
		{
			IFDS.Xml.deleteNode(subCatNodes[i]);
		}
		for (var i in _resources.fields['fundSubCats'])
		{
			addFundSubCatToXML(i);	
		}
		
							
		var fundIdNodes = IFDS.Xml.getNodes(basicInfoXML, 'FundIdentifiers/FundIdentifier');
		for (var i = 0; i < fundIdNodes.length; i++)
		{
			IFDS.Xml.deleteNode(fundIdNodes[i]);
		}				
		Ext.each(_resources.grids['fundIdentifier'].getAllRecords(), function(rec){addFundIdRecordToXML(rec)})		
		
		var shareGroupNodes = IFDS.Xml.getNodes(basicInfoXML, 'ShareGroups/ShareGroup');
		for (var i = 0; i < shareGroupNodes.length; i++)
		{
			IFDS.Xml.deleteNode(shareGroupNodes[i]);
		}				
		Ext.each(_resources.grids['shareGroup'].getAllRecords(), function(rec){addShareGroupRecordToXML(rec)})					
						
		function writeUpdatedValueToXML(fldName, value, context)
		{
			context = (context == null ? basicInfoXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			if (IFDS.Xml.getNodeValue(node, '.') != value)
			{
				IFDS.Xml.setNodeValue(node, value);
				IFDS.Xml.addAttribute(node, "status", _self.MOD);
			}
		}
		
		function writeNewValueToXML(fldName, value, context)
		{
			context = (context == null ? basicInfoXML : context);
			var node = IFDS.Xml.getNode(context, fldName);
			IFDS.Xml.replaceSingleNode(context, fldName, value);
		}
		
		function addFundSubCatToXML(subCatId)
		{
			var recordNode = IFDS.Xml.addSingleNode(IFDS.Xml.getNode(basicInfoXML, 'FundSubCategories'), 'FundSubCat');
			IFDS.Xml.addSingleNode(recordNode, 'subCat', i);			
			IFDS.Xml.addSingleNode(recordNode, 'subCatFlag', (_resources.fields['fundSubCats'][subCatId].getValue() ? 'yes' : 'no'));
			IFDS.Xml.addSingleNode(recordNode, 'subCatDesc', (_resources.fields['fundSubCats'][subCatId].boxLabel));			
		}
		
		function addFundIdRecordToXML(rec)
		{
			var recordNode = IFDS.Xml.addSingleNode(IFDS.Xml.getNode(basicInfoXML, 'FundIdentifiers'), 'FundIdentifier');			
			IFDS.Xml.addSingleNode(recordNode, 'runMode', rec.data['runMode']);
			IFDS.Xml.addSingleNode(recordNode, 'idType', rec.data['idType']);			
			IFDS.Xml.addSingleNode(recordNode, 'idValue', rec.data['idValue']);
			IFDS.Xml.addSingleNode(recordNode, 'fundIDVer', rec.data['fundIDVer']);
			IFDS.Xml.addSingleNode(recordNode, 'fundIDUUID', rec.data['fundIDUUID']);
		}
		
		function addShareGroupRecordToXML(rec)
		{
			var recordNode = IFDS.Xml.addSingleNode(IFDS.Xml.getNode(basicInfoXML, 'ShareGroups'), 'ShareGroup');			
			IFDS.Xml.addSingleNode(recordNode, 'runMode', rec.data['runMode']);
			IFDS.Xml.addSingleNode(recordNode, 'shGroup', rec.data['shGroup']);			
			IFDS.Xml.addSingleNode(recordNode, 'deff', DesktopWeb.Util.getSMVDateValue(rec.data['deff']));
			IFDS.Xml.addSingleNode(recordNode, 'active', rec.data['active']);
			IFDS.Xml.addSingleNode(recordNode, 'grpFundsRID', rec.data['grpFundsRID']);
		}

	}
	
	function validateScreen()
	{		
		var isValid = true;
		for (var i in _resources.fields)
		{			
			if (_resources.fields[i].isValid)
			{
				isValid = _resources.fields[i].isValid() && isValid;
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
									
		DesktopWeb.Util.goToScreen('ClassSetup_' + screenName, urlParams);	
	}
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'a', MOD: 'm', DEL: 'd'
						
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_resources.grids['fundIdentifier'].disableAllButtons();
			_resources.grids['shareGroup'].disableAllButtons();
						
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
				
				if (!_addMode)
				{	
					if (IFDS.Xml.getNode(_updatedClassDataXML, 'ClassBasic') == null)				
					{
						IFDS.Xml.appendNode(_updatedClassDataXML, IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_existingClassDataXML, 'ClassBasic')));				
					}
				}
				
				try{
					_verifyFlag = (_existingClassDataXML && IFDS.Xml.getNodeValue(_existingClassDataXML, '//ClassBasic/stat') == "04") ? false : true;
				}catch(e){throw new Error("Error getting Verify Flag: " + e.desc)}

				if(IFDS.Xml.getNodeValue(_initDataXML, '//Controls/classNameAutoSyncUp') == 'yes'){
					fndClsAutoSyncUpFlg = true;
				}else{
					fndClsAutoSyncUpFlg = false;
				}
					
				setHeader();
				populateBreadCrumbList();
				displayScreenButtons();
				populateDropdowns();
				addChangeHandlers();				
				populateScreen();
				clearChangeFlag();												
			}		
		}
		
		,getListValueDesc: function(listName, value)
		{
			var valueDesc = null
			valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "List[@id = '" + listName + "']/Element[code = '" + value + "']/value");			
			if (valueDesc == null)
			{
				valueDesc = IFDS.Xml.getNodeValue(_initDataXML, "List[@listName = '" + listName + "']/Element[code = '" + value + "']/value");
			}
			return valueDesc;
		}
		
		,openPopup: function(popupName, action)
		{
			if (action == this.ADD)
			{
				_resources.grids[popupName].clearSelectedRecord();
			}
			_resources.popups[popupName].init(action);
			_resources.popups[popupName].show();
		}
		
		,closePopup: function(popupName)
		{
			_resources.popups[popupName].hide();
		}
		
		,savePopupData: function(popupName, action, data)
		{
			if (action == this.ADD)
			{
				_resources.grids[popupName].addRecord(data);				
				_resources.grids[popupName].selectLastRecord();				
			}
			else
			{
				// annoying case where mod/del a brand new record
				if (_resources.grids[popupName].getSelectedRecord().data['runMode'] == this.ADD)
				{
					if (action == this.DEL)
					{
						_resources.grids[popupName].removeSelectedRecord();						
					}
					else
					{
						data['runMode'] = this.ADD
						_resources.grids[popupName].updateSelectedRecord(data);
					}					
				}
				else
				{
					_resources.grids[popupName].updateSelectedRecord(data);
					_self.updateGridActionButtons(popupName);									
				}
			}					
			setChangeFlag();	
		}
		
		,updateGridActionButtons: function(gridName)
		{			
			var selectedRecord = _resources.grids[gridName].getSelectedRecord();	
			
			if (selectedRecord)
			{										
				_resources.grids[gridName].enableButton('modBtn');
				_resources.grids[gridName].enableButton('delBtn');							
			}
			else
			{
				_resources.grids[gridName].disableButton('modBtn');
				_resources.grids[gridName].disableButton('delBtn');
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
					if(fndClsAutoSyncUpFlg == false){
						DesktopWeb.Util.displayWarning(_translationMap['FndClsNameSyncUpWarning'], confirmWarning);
					
						function confirmWarning(btn){
							if (btn == 'ok'){
								DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
							}
						}
					}
					else{
						DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_Saving']);
					}
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
				DesktopWeb.Ajax.doUpdateCache({UpdatedClassData: _updatedClassDataXML}, callback, _translationMap['ProcMsg_saving']);
				if(fndClsAutoSyncUpFlg == false){
					DesktopWeb.Util.displayWarning(_translationMap['FndClsNameSyncUpWarning']);
				}
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