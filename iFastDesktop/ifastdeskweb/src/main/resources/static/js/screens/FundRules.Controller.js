/*********************************************************************************************
 * @file    FundRules.Controller.js
 * @author  Matira Thanetkulabut
 * @desc    Controller JS file for FundRules screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Fund Level Maintenance > Fund Rules Maintenance
 *
 *  History : 
 *
 *  01-Feb-2016 Matira Thanetkulabut P0250394 T82268
 *              - Initial (allow user to maintain the rule type setup)
 *
 *  03-Mar-2016 Matira Thanetkulabut P0250394 DFT0060514 T82372
 *              - Fix error when create multiple record
 *				- Application category
 *				- Details Button
 *
 *  07-Mar-2016 Matira Thanetkulabut P0250394 DFT0060866 T82383 
 *				- Modify the Historical,Details button.
 *              - Fix cannot create new record after error message is show.
 *              - Change order sequence.
 *
 *  11-Mar-2016 Matira Thanetkulabut P0250394 DFT0060896 T82439   
 *              - hide column OverrideValue when rule type is nonOverride.
 *              - fix processing message after add/modify/delete record.
 *
 *  18-Mar-2016 Matira Thanetkulabut P0250394 DFT0061192 T82487
 *              - improve logic to check permission add/mod/delete the records.
 *              - fix rule level options display incorrect after create new record.
 *              - improve details screen.
 *              - add filterOptions function.
 *
 *  25-Mar-2016 Matira Thanetkulabut P0250394 DFT0061365 T82478
 *              - add new column baycom and class description for fund/class level.
 *
 *  22-Nov-2016 Zeljko Bajic P0257851 T84326 CHG0047691_MinInvestment
 *              - Added new implementation as required.
 *
 *  25-Apr-2017 Nopphawan Hatthaseriphong P0264164 T85370 Diamond Share Class Restriction
 *			    - Removed hard-coding _withCurr, _withAmtType, _withAssetLv, _withAssetType
 *
 *  27-Jun-2017 Gomoot T. P0264164 T85780 
 *          - Fix unconsistant behavior when user save data.
 *          
 * 	11-Dec-2017 Sreejith A 	P0274726 P0266789-1871
 * 			   - Added Reason and remarks fields
 *
 * 	13-Feb-2018 Sreejith A 	P0274726 P0274726-83
 * 			   - Removed Reason and remarks fields
 */
 
DesktopWeb.ScreenController = function(){
    
    // PRIVATE VARIABLES *************************************
    var _self = null;
    var _resources = null;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    var _changeFlag = false;
    var _inqView = 'dtFundRulesInq';
    var _validateView = 'dtFundRulesVal';
    var _updateView = 'dtFundRulesProc';
    
    var _initDataXML = null;
    var _fundRuleXML = null;
    var _detailXML = null;
    var _currentSearchCriteria	= new Array();
    var _nextUUID = 1;
    var _permissionsMap = {};
    
    var _nextStartRecNum = 0;
    var _requestRecNum = 25;
    var _nextStartRecNumDtl = 0;

    var _defaultValue = {};

    function doSearch(append)
	{
        // build parameter xml
		var dataXML = IFDS.Xml.newDocument('data');
    
        IFDS.Xml.addSingleNode(dataXML, 'runMode', 'reload');
    
		IFDS.Xml.addSingleNode(dataXML, 'ruleType', _currentSearchCriteria['ruleType']);
		IFDS.Xml.addSingleNode(dataXML, 'ruleLevel', _currentSearchCriteria['ruleLevel']);
		IFDS.Xml.addSingleNode(dataXML, 'fundGroup', _currentSearchCriteria['fundGroup']);
		IFDS.Xml.addSingleNode(dataXML, 'fund', _currentSearchCriteria['fund']);
		IFDS.Xml.addSingleNode(dataXML, 'class', _currentSearchCriteria['class']);
		IFDS.Xml.addSingleNode(dataXML, 'activeOnly', _currentSearchCriteria['activeOnly']);
		IFDS.Xml.addSingleNode(dataXML, 'fundSponsor', _currentSearchCriteria['fundSponsor']);

		IFDS.Xml.addSingleNode(dataXML, 'startRecNum', append?_nextStartRecNum:1);
		IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);
		
		DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{						

            if (success)
            {
                if (append)
                {
                    // User clicks More button
                    _resources.grids['fundRule'].appendData(responseXML);
                    _resources.grids['fundRule'].setSelectedRecord(_nextStartRecNum - 1);
                }
                else
                {
                    _resources.grids['fundRule'].loadData(responseXML);
                }
                hideCol();
            }else   _self.enablePermButtons();
            // control more button
			_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
			if (_nextStartRecNum)
            {
				_resources.grids['fundRule'].enableButton('moreBtn');
			}
			else
            {
				_resources.grids['fundRule'].disableButton('moreBtn');
			}
		}
	}
  
	
	function buildApplicationCategoryXML(fundRuleXML)
	{
		var appCateXML = IFDS.Xml.newDocument("AppCates");
		
		var appCateNode = IFDS.Xml.addSingleNode(appCateXML, "AppCate");
		IFDS.Xml.addSingleNode(appCateNode, "cateCode", "taxJuris");
		IFDS.Xml.addSingleNode(appCateNode, "cateDesc", _translationMap['TaxJurisdiction']);
		IFDS.Xml.addSingleNode(appCateNode, "value", fundRuleXML.data["taxJuris"]);
		
		appCateNode = IFDS.Xml.addSingleNode(appCateXML, "AppCate");
		IFDS.Xml.addSingleNode(appCateNode, "cateCode", "provRes");
		IFDS.Xml.addSingleNode(appCateNode, "cateDesc", _translationMap['ProvinceofResidence']);
		IFDS.Xml.addSingleNode(appCateNode, "value",  fundRuleXML.data["provRes"]);
		
		appCateNode = IFDS.Xml.addSingleNode(appCateXML, "AppCate");
		IFDS.Xml.addSingleNode(appCateNode, "cateCode", "acctType");
		IFDS.Xml.addSingleNode(appCateNode, "cateDesc", _translationMap['AccountType']);
		IFDS.Xml.addSingleNode(appCateNode, "value",  fundRuleXML.data["acctType"]);
		
		appCateNode = IFDS.Xml.addSingleNode(appCateXML, "AppCate");
		IFDS.Xml.addSingleNode(appCateNode, "cateCode", "taxType");
		IFDS.Xml.addSingleNode(appCateNode, "cateDesc", _translationMap['TaxType']);
		IFDS.Xml.addSingleNode(appCateNode, "value",  fundRuleXML.data["taxType"]);
		
		appCateNode = IFDS.Xml.addSingleNode(appCateXML, "AppCate");
		IFDS.Xml.addSingleNode(appCateNode, "cateCode", "acctDesignation");
		IFDS.Xml.addSingleNode(appCateNode, "cateDesc", _translationMap['AccountDesignation']);
		IFDS.Xml.addSingleNode(appCateNode, "value",  fundRuleXML.data["acctDesignation"]);
		
		return appCateXML;
	}
	
	function loadApplicationCategory(rec)
	{
		if(rec){
			_resources.grids['appCate'].loadData(buildApplicationCategoryXML(rec));
        }
	} 
  
    function setDefaultValue()
    {
        var startDate = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/startDate');
        startDate = new Date(startDate).format(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()));
        var stopDate = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/stopDate');
        stopDate = new Date(stopDate).format(DesktopWeb.Util.parseSMVDateFormat(DesktopWeb.Util.getDateDisplayFormat()));
        var ruleType = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/ruleType');
        var ruleLevel = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/ruleLevel');
        var assetLevel = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/assetLevel');
        var onlineEWI = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/onlineEWI');
        var cycleEWI = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/cycleEWI');
        var esgEWI = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/esgEWI');
    
        _defaultValue['amountType'] = IFDS.Xml.getNodeValue(_initDataXML,'//DefaultValues/amountType');
    
        if(ruleType)
        {
            _resources.fields['ruleType'].setValue(ruleType);
            _resources.popups['fundRule'].getField('ruleType').setValue(ruleType);
        }
        
        if(ruleLevel)
        {
            _resources.fields['ruleLevel'].setValue(ruleLevel);
            _resources.popups['fundRule'].getField('ruleLevel').setValue(ruleLevel);
        }
        
        if(assetLevel) _resources.popups['fundRule'].getField('assetLevel').setValue(assetLevel);      
        if(startDate)  _resources.popups['fundRule'].getField('startDate').setValue(startDate);                     
        if(stopDate)   _resources.popups['fundRule'].getField('stopDate').setValue(stopDate);                     
        if(onlineEWI)  _resources.popups['fundRule'].getField('onlineEWI').setValue(onlineEWI);
        if(cycleEWI)   _resources.popups['fundRule'].getField('cycleEWI').setValue(cycleEWI);
        if(esgEWI)     _resources.popups['fundRule'].getField('esgEWI').setValue(esgEWI);
    }
  
    function storeContextErrors(errorNodes)
	{
		for (var i = 0; i < errorNodes.length; i++)
		{
			var table = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/xmlElementName');
			var elementSource = IFDS.Xml.getNodeValue(errorNodes[i], 'recordSource/source/elementSource');
			var errMsg = IFDS.Xml.getNodeValue(errorNodes[i], 'text');
			
			var recordIndex = _resources.grids['fundRule'].getStore().find('uuid', elementSource);
            var record = _resources.grids['fundRule'].getStore().getAt(recordIndex);
			
			record.set('errMsg', errMsg);
			_resources.grids['fundRule'].getStore().commitChanges();
		}
	}	
  
    function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
  
    function clearField(name)
	{
        _resources.fields[name].reset();
        _resources.fields[name].disable();
	}
  
    function populateFirst()
	{			
        if (IFDS.Xml.getNode(_initDataXML, "//List[@id = 'RuleTypeList']") != null)
        {
            _resources.fields['ruleType'].loadData(IFDS.Xml.getNode(_initDataXML, "//List[@id = 'RuleTypeList']"));				
            setDefaultValue();
            _resources.popups['fundRule'].getField('ruleType').loadData(IFDS.Xml.getNode(_initDataXML, "//List[@id = 'RuleTypeList']"));
            _resources.popups['fundRule'].getField('onlineEWI').loadData(IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'EWIList']"));
            _resources.popups['fundRule'].getField('cycleEWI').loadData(IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'EWIList']"));
            _resources.popups['fundRule'].getField('esgEWI').loadData(IFDS.Xml.getNode(_initDataXML, "//List[@listName = 'EWIList']"));
            _resources.popups['fundRule'].getField('currency').loadData(IFDS.Xml.getNode(_initDataXML, "//List[@id = 'CurrencyList']"));
        }
    }
    
    function storePermissions(xml)
	{
		_permissionsMap['inq'] = IFDS.Xml.getNodeValue(xml, '//Permissions/inqPerm').toLowerCase() == _self.YES;
		_permissionsMap['add'] = IFDS.Xml.getNodeValue(xml, '//Permissions/addPerm').toLowerCase() == _self.YES;
		_permissionsMap['mod'] = IFDS.Xml.getNodeValue(xml, '//Permissions/modPerm').toLowerCase() == _self.YES;
		_permissionsMap['del'] = IFDS.Xml.getNodeValue(xml, '//Permissions/delPerm').toLowerCase() == _self.YES;
    }
  
    function buildUpdateXML(runMode)
	{
		var updateXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(updateXML, 'runMode', runMode);
		var fundRulesXML = IFDS.Xml.addSingleNode(updateXML, 'FundRules');		
		var store = _resources.grids['fundRule'].getStore();

		var newRecords = store.query('runMode', _self.ADD);
		newRecords.each(addToXML);				
		var modRecords = store.query('runMode', _self.MOD);
		modRecords.each(addToXML);				
		var delRecords = store.query('runMode', _self.DEL);
		delRecords.each(addToXML);			
        return updateXML;
		
		function addToXML(item)
		{
			var recordXML = IFDS.Xml.addSingleNode(fundRulesXML, 'FundRule');
			IFDS.Xml.addAttribute(recordXML, 'RecordSource', item.data['uuid']);
			for (var i in item.data)
			{
                if(i == 'startDate')
                {
                    IFDS.Xml.addSingleNode(recordXML, i, DesktopWeb.Util.getSMVDateValue(item.data[i]));
                }
                else if(i == 'stopDate')
                {
                    IFDS.Xml.addSingleNode(recordXML, i, DesktopWeb.Util.getSMVDateValue(item.data[i]));
                }
                else
                {
                    IFDS.Xml.addSingleNode(recordXML, i, item.data[i]);
                }
			}			
		}		
	}
  
    function getUpdatedRecordCount()
	{		
		var store = _resources.grids['fundRule'].getStore();
		var newRecords = store.query('runMode', _self.ADD);	
		var modRecords = store.query('runMode', _self.MOD);		
		var delRecords = store.query('runMode', _self.DEL);
        
		return newRecords.length + modRecords.length + delRecords.length 
	}
    
    function hideCol()
    {
        var grid = _resources.grids['fundRule'];
        var store = grid.getStore();
        var selectedRecord = grid.getSelectedRecord();
        
        if(selectedRecord != null && selectedRecord != undefined)
        {
            var ovrType = _self.getRuleTypeOverrideType(selectedRecord.data['ruleType']);
            var ovrValueIdx = grid.getColumnModel().getIndexById('value');
            
            if(ovrType == 'nonOverride'){
                // hide column override value
                grid.hideColumn(ovrValueIdx);
            }else{
                grid.showColumn(ovrValueIdx);
            }
        }
        
        var baycomIdx = grid.getColumnModel().getIndexById('baycom');
        var classEIdx = grid.getColumnModel().getIndexById('classE');
        
        // hide column baycom and classDesc
        grid.hideColumn(baycomIdx);
        grid.hideColumn(classEIdx);
        
        var records = store.queryBy(function(record){return record.data['runMode'] != _self.DEL});
        
        for (var i = 0; i < records.getCount(); i++)
        {
            var record = records.itemAt(i);
            if(record.data['ruleLevel'] == '01'){
                grid.showColumn(baycomIdx);
                grid.showColumn(classEIdx);
                break;
            }
        } 	
    }
    
    function buildDetlXml(searchValue,searchFor,ruleType,append)
    {
        // build parameter xml
        var dataXML = IFDS.Xml.newDocument('data');

        IFDS.Xml.addSingleNode(dataXML, 'searchValue', searchValue);
        IFDS.Xml.addSingleNode(dataXML, 'api');
        IFDS.Xml.addSingleNode(dataXML, 'addParam1', _self.getFndGrpType('RuleTypeList',ruleType));
        IFDS.Xml.addSingleNode(dataXML, 'searchFor', searchFor);
        IFDS.Xml.addSingleNode(dataXML, 'activeOnly', _self.NO);
        IFDS.Xml.addSingleNode(dataXML, 'startRecordNum', append?_nextStartRecNumDtl:1);
        IFDS.Xml.addSingleNode(dataXML, 'requestRecNum', _requestRecNum);
        
        DesktopWeb.Ajax.doSmartviewAjax('fundClassSearch', null, dataXML, responseHandler, _translationMap['ProcMsg_Loading'])
        
        function responseHandler(success, responseXML)
        {		
            if (success)
            {
                if(append)
                {
                    _resources.grids['fndClsDisp'].appendData(responseXML);
                }
                else
                {
                    _resources.grids['fndClsDisp'].loadData(responseXML);
                }
                
            }
            
            _nextStartRecNumDtl = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
            
            if(_nextStartRecNumDtl)
            {
                buildDetlXml(searchValue,searchFor,ruleType,true);
            }
        }
    }

    function filterOptions()
	{
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "TaxJurisList"]/Element[code = "*"]'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "AcctTypeList"]/Element[code = "*"]'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "TaxTypeList"]/Element[code = "*"]'));
		IFDS.Xml.deleteNode(IFDS.Xml.getNode(_initDataXML, '*/List[@id = "AcctDesignationList"]/Element[code = "*"]'));		
	}
    
    // PUBLIC ITEMS *************************************
	return {	
        ADD: 'add', MOD: 'mod', DEL: 'del', YES: 'yes', NO: 'no'
        , updatesFlag: false
        , defaultValue: _defaultValue
    
    ,init: function(res)
    {	
        _resources = res;
        _self = DesktopWeb._SCREEN_CONTROLLER;

        var requestXML = IFDS.Xml.newDocument('data');
        IFDS.Xml.addSingleNode(requestXML, 'runMode', 'init');	
        IFDS.Xml.addSingleNode(requestXML, 'ruleType');	
        IFDS.Xml.addSingleNode(requestXML, 'ruleLevel');	
        IFDS.Xml.addSingleNode(requestXML, 'fundGroup');	
        IFDS.Xml.addSingleNode(requestXML, 'fundSponsor');
        IFDS.Xml.addSingleNode(requestXML, 'fund');
        IFDS.Xml.addSingleNode(requestXML, 'class');	
        IFDS.Xml.addSingleNode(requestXML, 'activeOnly');	
        IFDS.Xml.addSingleNode(requestXML, 'startRecNum');	
        IFDS.Xml.addSingleNode(requestXML, 'requestRecNum');	
    
        DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, requestXML, responseHandler1, _translationMap['ProcMsg_Loading']);

        function responseHandler1(success, responseXML)
        {				
            if (success)
            {
                _initDataXML = responseXML;
                filterOptions();
                populateFirst();
                storePermissions(_initDataXML);
                _self.enablePermButtons();
            }
        }
    }
      
    ,openActionPopup: function(action)
    {
        if (action == this.ADD)
        {
            _resources.grids['fundRule'].clearSelectedRecord();
        }
            _resources.popups['fundRule'].setAction(action);
            _resources.popups['fundRule'].show();
    }
    
    ,closePopup: function(popupName)
    {
        _resources.popups[popupName].hide();
    }
    
    ,openDetailsPopup: function(field)
    {
        var list = null;
        switch(field)
        {
            case 'taxJuris':
                list = "TaxJurisList";
                break;		
            case 'provRes':
                list = "TaxJurisList";
                break;		
            case 'acctType':
                list = "AcctTypeList";
                break;		
            case 'taxType':
                list = "TaxTypeList";
                break;		
            case 'acctDesignation':
                list = "AcctDesignationList";
                break;		
        }
        
        _resources.popups['appCate'].setEditDetails(field, list);						
        _resources.popups['appCate'].show();
    }
    
    ,getRuleTypeOverrideType: function(ruleType)
    {
        return IFDS.Xml.getAttributeValue(_initDataXML, "//List[@id = 'RuleTypeList']/Element[code = '" + ruleType + "']/code/@override");
    }

    ,getRuleTypeCurrencyDisplay: function(ruleType)
    {
        return IFDS.Xml.getNodeValue(_initDataXML, "//List[@id = 'RuleTypeList']/Element[code = '" + ruleType + "']/currency");
    }

    ,getNodeValue: function(listName, value)
    {	
        return IFDS.Xml.getNodeValue(_initDataXML, "//List[@id = '" + listName + "']/Element[code = '" + value + "']/value");
    }
    
	,getFndGrpType: function(listName, value)
    {	
        return IFDS.Xml.getNodeValue(_initDataXML, "//List[@id = '" + listName + "']/Element[code = '" + value + "']/fndgrptype");
    }
	
    ,getListValueDesc: function(listName, value, ruleType)
    {
        if(listName == 'RuleTypeList'){ 
            var listName2 = listName;    
        }
        else{
            var listName2 = listName + ruleType;
        }
        
        return this.getNodeValue(listName2,value);
    }
    
    ,getDetailsListXML: function(listName)
    {
        return IFDS.Xml.getNode(_initDataXML, "//List[@id = '" + listName + "']");
    }
	
    ,isDataExist: function(listName)
    {
    	return IFDS.Xml.getNode(_initDataXML, "//List[@id = '" + listName + "']/Element") != null;
    }
	
	,removeBlankRuleLv: function(listName)
	{
		var lists = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(_initDataXML, "//List[@id = '" + listName + "']"));
		Ext.each(lists, function(elmXML){	
			var node = IFDS.Xml.getNode(elmXML,"Element");
			if(IFDS.Xml.getNodeValue(node,'code') == '')
				IFDS.Xml.deleteNode(node);	
		});
		return lists;
	}
	
    ,populateDropdowns: function(newValue)
    {
        
        var ruleLv = "RuleLevelList" + newValue;
        _resources.fields['ruleLevel'].setValue("");
        _resources.fields['ruleLevel'].loadData(this.getDetailsListXML(ruleLv));
        
        var fundGrp = "FundGroupList" + newValue;
        _resources.fields['fundGroup'].setValue("");
        _resources.fields['fundGroup'].loadData(this.getDetailsListXML(fundGrp));

        _resources.fields['fundSponsor'].setValue();
        _resources.fields['fundSponsor'].loadData(IFDS.Xml.getNode(_initDataXML, "//List[@id = 'FundSponsorList']"));
    }

    ,populateDataList: function (popupsName, fieldName, listName) {
    	if (_self.isDataExist(listName)) {
    		_resources.popups[popupsName].getField(fieldName).reset();
            _resources.popups[popupsName].getField(fieldName).loadData(this.getDetailsListXML(listName));
            _resources.popups[popupsName].getField(fieldName).showField();
        }
    }

    ,populateDetails: function(rec)
    {
        if(rec)
        {
            _self.enablePermButtons(rec);
            // set severity data
            _resources.fields['onlineEWI'].setValue(rec.data['onlineEWI']);
            _resources.fields['cycleEWI'].setValue(rec.data['cycleEWI']);
            _resources.fields['esgEWI'].setValue(rec.data['esgEWI']);
    
            loadApplicationCategory(rec); // set applicable data
        }
    }
    
    ,enablePermButtons: function (rec)
	{
        if(_permissionsMap['inq']) { 
            _resources.buttons['searchBtn'].enable(); 
        }else{ 
            _resources.buttons['searchBtn'].disable(); 
        }
        
        if(_permissionsMap['add']){ 
            _resources.grids['fundRule'].enableButton('addBtn');
        }else{ 
            _resources.grids['fundRule'].disableButton('addBtn');
        }
        
        if(rec)
        {
            if(_permissionsMap['mod']){ 
                _resources.grids['fundRule'].enableButton('modBtn');
                _resources.grids['appCate'].enableButton('edit'); 
            }else{ 
                _resources.grids['fundRule'].disableButton('modBtn');
                _resources.grids['appCate'].disableButton('edit');
            }	

            if(_permissionsMap['del']){
                _resources.grids['fundRule'].enableButton('delBtn');
            }else{
                _resources.grids['fundRule'].disableButton('delBtn');
            }
            
            if (rec.data['ruleLevel'] == '01'){
                _resources.grids['fundRule'].disableButton('dtlBtn');
            }else{
                _resources.grids['fundRule'].enableButton('dtlBtn');
            } 
            
            if(rec.data['runMode'] == _self.ADD){
                _resources.grids['fundRule'].disableButton('historicalBtn');
                _resources.grids['fundRule'].disableButton('adminBtn');
            }else{
                _resources.grids['fundRule'].enableButton('historicalBtn');
                _resources.grids['fundRule'].enableButton('adminBtn');
            }
        }
    }
    
    ,isPopulatedByControl: function(controlName, code)
    {
        var retVal = false;
        var elmXMLArr = IFDS.Xml.getNodes(_initDataXML,"//ControlList[@id = '" + controlName + "']/Codes/code");		
    
        Ext.each(elmXMLArr, function(elmXML){				
            if (code == IFDS.Xml.getNodeValue(elmXML, "."))
            {					
                retVal = true;
            }
        });	
        return retVal;	
    }
    
    ,openHistoryPopup: function()
    {
        var viewParam = {};
        var historyName = null;
        var selectedRecord  = _resources.grids['fundRule'].getSelectedRecord();
        
        if (selectedRecord != undefined && selectedRecord != null)
        {
            switch ( selectedRecord.data['ruleLevel'] )
            {
                // fund class level
                case '01':
                {
                    viewParam['auditType'] = 'FundLimitOverride'; 
                    viewParam['searchValue1'] = selectedRecord.data['fund'];
                    viewParam['searchValue2'] = selectedRecord.data['class'];
                    viewParam['searchValue3'] = selectedRecord.data['ruleType'];
                    viewParam['searchValue4'] = selectedRecord.data['seqNo'];
                    break;
                }    
                // fund level
                case '02': 
                {
                    viewParam['auditType'] = 'FundRules';
                    viewParam['searchValue1'] = selectedRecord.data['uuid'];
                    break;
                }   
                // fund group level
                case '03': 
                {
                    viewParam['auditType'] = 'FundRules';
                    viewParam['searchValue1'] = selectedRecord.data['uuid'];
                    break;
                }
                    // fund sponsor level
                case '05':
                    {
                        viewParam['auditType'] = 'FundRules';
                        viewParam['searchValue1'] = selectedRecord.data['uuid'];
                        break;
                    }
            }
            
            historyName = _translationMap['FundRule'] + ' - ' + _translationMap['History'];
            
            _resources.popups['history'].init(historyName, 'dtHistoricalInfo', viewParam, true);
            _resources.popups['history'].show();
        }
    }
    
    ,openAdminPopup: function()
    {
        var title = null;
        var xml = null;
    
        title = _translationMap['adminBtn'];
        xml = _resources.grids['fundRule'].getSelectedRecord();
    
        if (xml && xml != undefined)
        {
            var adminData = {};
            adminData['userName'] = xml.data['userName'];
            adminData['procDate'] = xml.data['processDate'];
            adminData['modUser'] = xml.data['modUser'];
            adminData['modDate'] = xml.data['modDate'];
    
            _resources.popups['admin'].init(title, adminData);
            _resources.popups['admin'].show();
        }
    }
    
    ,onChangeMainRuleLv: function()
    {
        clearField('fundGroup');
        clearField('fundFld');
        clearField('classFld');
        clearField('fundSponsor');
        var ruleLv = _resources.fields['ruleLevel'].getValue();

        switch(ruleLv)
        {
            // fund class level
            case "01":
                _resources.fields['fundFld'].enable(); 
                _resources.fields['classFld'].enable();  
                break;
                
            // fund level
            case "02": 
                _resources.fields['fundFld'].enable(); 
                break;
                
            // fund group level
            case "03":
                _resources.fields['fundGroup'].enable(); 
                break;

            // fund sponsor level
            case "05":
                _resources.fields['fundSponsor'].enable();
                break;
        }
    }
    
    ,clearDetails: function()
    {
        _resources.grids['appCate'].clearData();
        
        _resources.fields['onlineEWI'].setValue("");
        _resources.fields['cycleEWI'].setValue("");
        _resources.fields['esgEWI'].setValue("");
        
        _resources.grids['fundRule'].disableButton('modBtn');
        _resources.grids['fundRule'].disableButton('delBtn');
        _resources.grids['fundRule'].disableButton('dtlBtn');
        _resources.grids['fundRule'].disableButton('historicalBtn');
        _resources.grids['fundRule'].disableButton('adminBtn');
    }
    
    ,loadClass: function(fundCode,popup)
    {
        var dataXML = IFDS.Xml.newDocument('data');
        IFDS.Xml.addSingleNode(dataXML, 'fundCode', fundCode);
                        
        DesktopWeb.Ajax.doSmartviewAjax('classSearch', null, dataXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
        function responseHandler(success, responseXML)
        {										
            if (success)
            {
                if(popup == null)
                {
                    _resources.fields['classFld'].enable();
                    _resources.fields['classFld'].loadData(IFDS.Xml.getNode(responseXML, '/*//Classes'));
                }
                else
                {
                    _resources.popups[popup].getField('classItem').enable();
                    _resources.popups[popup].getField('classItem').loadData(IFDS.Xml.getNode(responseXML, '/*//Classes'));
                }
            }
        }
    }

    ,search: function()
    {
        // Store search criteria; they would be used for more button
        _currentSearchCriteria['ruleType'] = _resources.fields['ruleType'].getValue();
        _currentSearchCriteria['ruleLevel'] = _resources.fields['ruleLevel'].getValue();
        _currentSearchCriteria['fundGroup'] = _resources.fields['fundGroup'].getValue();
        _currentSearchCriteria['fund'] = _resources.fields['fundFld'].getValue();
        _currentSearchCriteria['class'] = _resources.fields['classFld'].getValue();
        _currentSearchCriteria['fundSponsor'] = _resources.fields['fundSponsor'].getValue();
        _currentSearchCriteria['activeOnly'] = _resources.fields['activeBox'].getValue() == 0 ? _self.NO : _self.YES;
    
        // Clear data in grid before do actual search
        clearGrid('fundRule');
        _self.clearDetails();
        
        // Call doSearch
        doSearch(false);  
    }
    
    ,doReload: function()
    {					
        // Call doSearch with append and more
        doSearch(true);
    }
    
    ,doValidateFundRule: function(action, data)
    {   
        if (_resources.popups['fundRule'].getField('stopDate').getValue() < _resources.popups['fundRule'].getField('startDate').getValue()) 
        { 
            _resources.popups['fundRule'].getField('startDate').markInvalid(_translationMap['DeffBeforeStop']); 
            _resources.popups['fundRule'].getField('stopDate').markInvalid(_translationMap['DeffBeforeStop']); 
        }
        else
        {
            if(action == _self.MOD)
            {
                var bfMode = _resources.grids['fundRule'].getSelectedRecord().data['runMode'];
                
                if(bfMode == _self.ADD && data['runMode'] == _self.MOD){
                    data['runMode'] =  _self.ADD;
                }
            }
            
            var dataXML = IFDS.Xml.newDocument('data');
            var fundRuleXML = IFDS.Xml.addSingleNode(dataXML, 'FundRule');
            IFDS.Xml.addSingleNode(fundRuleXML, 'uuid', data['uuid']);
            IFDS.Xml.addSingleNode(dataXML, 'runMode', data['runMode']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'ruleType', data['ruleType']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'ruleLevel', data['ruleLevel']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'fundGroup', data['fundGroup']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'fund', data['fund']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'class', data['class']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'fundSponsor', data['fundSponsor']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'startDate', DesktopWeb.Util.getSMVDateValue(data['startDate']));
            IFDS.Xml.addSingleNode(fundRuleXML, 'stopDate', DesktopWeb.Util.getSMVDateValue(data['stopDate']));
            IFDS.Xml.addSingleNode(fundRuleXML, 'overrideDec', data['overrideDec']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'overrideLog', data['overrideLog']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'overrideChar', data['overrideChar']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'assetLevel', data['assetLevel']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'onlineEWI', data['onlineEWI']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'cycleEWI', data['cycleEWI']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'esgEWI', data['esgEWI']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'taxJuris', data['taxJuris']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'provRes', data['provRes']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'acctType', data['acctType']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'taxType', data['taxType']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'acctDesignation', data['acctDesignation']);
            IFDS.Xml.addSingleNode(fundRuleXML, 'version', data['version']);	
            
            DesktopWeb.Ajax.doSmartviewAjax(_validateView, null, dataXML, responseHandler, _translationMap['ProcMsg_Saving'])
                        
            function responseHandler(success, responseXML, contextErrors, warnings)
            {		
                if (success)
                {       
                    if (action == _self.ADD)
                    {
                        _resources.grids['fundRule'].addRecord(data);				
                        _resources.grids['fundRule'].selectLastRecord();
                    }
                    else if (action == _self.MOD)
                    {
                        _resources.grids['fundRule'].updateSelectedRecord(data);
                    }
                    else if (action == _self.DEL)
                    {
                        if (_resources.grids['fundRule'].getSelectedRecord().data['runMode'] == _self.ADD)
                        {					
                            _resources.grids['fundRule'].removeSelectedRecord();
                            _resources.grids['fundRule'].selectFirstRecord();                            
                        }else{
                            _resources.grids['fundRule'].updateSelectedRecord(data);
                            _resources.grids['fundRule'].clearSelectedRecord();
                            _self.clearDetails();
                        }
                    }
                    _self.updatesFlag = (getUpdatedRecordCount() > 0);
                    _resources.popups['fundRule'].hide();
                    _self.closePopup('fundRule');
                    hideCol();
                }
            }
        }
    }	
    
    ,doUpdate: function()
    {
        var updateStatus = null;	
        DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, buildUpdateXML('update'), responseHandler,null);

        function responseHandler(success, responseXML, contextErrors, warnings, btn)
        {
            if (success)
            {
                updateStatus = DesktopWeb._SUCCESS;
            }
            else
            {
                alert("Errors occured during setup fund rule. Operation could not be completed.");
                storeContextErrors(contextErrors);
                updateStatus = DesktopWeb._FAIL 	
            }
        }
        return updateStatus;
    }
  
    ,saveDetailsUpdate: function(field, value)
    {
        var record = _resources.grids['fundRule'].getSelectedRecord();
        if (!record.data['runMode'])
        {
            record.data['runMode'] = _self.MOD;
            _self.updatesFlag = true;
        }
        record.data[field] = value;
        this.populateDetails(_resources.grids['fundRule'].getSelectedRecord());
	}
    
    ,getNewUUID: function()
    {
        return "TMPUUID" + (_nextUUID++);
    }
    
    ,doValidate: function()
    {
        DesktopWeb.Ajax.doSmartviewAjax(_updateView, null, buildUpdateXML('validation'), responseHandler, _translationMap['ProcMsg_Saving']);			

        function responseHandler(success, responseXML, contextErrors, warnings)
        {
            if (success)
            {	
                DesktopWeb.Util.commitScreen();
            }
            else 
            {
                storeContextErrors(contextErrors);
            }
        }
    }
    
    ,openFundClassPopup: function()
    {
        var xml = null;
        var title = null;
        var searchValue = null;
        var searchFor = null;
        xml = _resources.grids['fundRule'].getSelectedRecord();
    
        if (xml && xml != undefined)
        {
            switch (xml.data['ruleLevel'])
            {
                // fund level
                case '02':
                    searchValue = xml.data['fund'];
                    searchFor = "fundCode";
                    title = _translationMap['Fund'] + " - " + searchValue + " - " + _translationMap['Details'];
                    break;
                 
                // fund group level
                case '03':
                    searchValue = xml.data['fundGroup'];
                    searchFor = "fundGroup";
                    title = _translationMap['FundGroup'] + " - " + searchValue + " - " + _translationMap['Details'];
                    break;
            }
            buildDetlXml(searchValue,searchFor,xml.data['ruleType'],false);
            _resources.popups['detail'].init(title);
            _resources.popups['detail'].show();
        }
    }
  }  
}