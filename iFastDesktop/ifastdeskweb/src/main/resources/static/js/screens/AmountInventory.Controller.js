/*********************************************************************************************
 * @file    AmountInventory.Controller.js
 * @author  Matira Thanetkulabut
 * @desc    Controller JS file for Amount Inventory screen
 *********************************************************************************************/
/*
 *  Navigate: Menu > Account > Historical Market Value > Invest Info
 *            Menu > Account > Transaction History > Invest Info
 *  
 *  History : 
 *  
 *  9-Nov-2016 Matira Thanetkulabut P0256533 T84110 MSF - Desktop
 *              - Initial
 *
 *  24-Jan-2017 Matira Thanetkulabut P0256533 T84653 DFT0071266 MSF - Desktop
 *              - More button
 */
 
DesktopWeb.ScreenController = function(){

    // PRIVATE VARIABLES *************************************
    var _self = null;
    var _resources = null;
    var _translationMap = DesktopWeb.Translation.getTranslationMap();
    
    var _inqView = 'dtAmountInventoryInq';
    var _inqMode = "";
    var _initXML = null;
    var _mstrXML = null;
    var _currentSearchCriteria	= new Array();
    var _isFndClsDisable = false;
	var _indInv = 0;
	var _indDetl = 0;
    var _nextStartRecNum = 0;
    var _requestRecNum = 25;
    var _nextStartRecNumDtl = 0; 
	
	function populateFirst()
	{			
		var invType = IFDS.Xml.getNode(_initXML, "//List[@listName = 'InvestType']");
		var sortBy = IFDS.Xml.getNode(_initXML, "//List[@listName = 'SortBy']");
		
		if (invType != null)
        {
            _resources.fields['invTypeFld'].loadData(invType);		
			
        }
		if (sortBy != null)
        {
            _resources.fields['sortByFld'].loadData(sortBy);
        }
		
		setInqMode(_inqMode);
		setDefaultValue();
	}
	
	function setDefaultValue()
    {
		var invType = IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/selInvestType');
		var fndCls = IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/selFundCode') 
					   + "/" + IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/selClassCode');
		var fndGrp = IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/selFundGroup');
		var activeFlag = IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/selActiveOnly') == 'yes' ? true: false;
		var descFlag = IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/selDescending') == 'yes' ? true: false;
		var sortBy = IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/selSortBy');
		var inqMode = IFDS.Xml.getNodeValue(_initXML,'//DefaultValues/inqMode');
		var group = IFDS.Xml.getNodeValue(_initXML,"//List[@listName = 'InvestType']/Element[code='"+invType+"']/groupType");
		
		_resources.fields['invTypeFld'].setValue(invType);
		_self.populateDropdowns(group);
		
		if(_isFndClsDisable){
			_resources.fields['fndGrpFld'].setValue(fndGrp);
		}else{
			_resources.fields['fndClssFld'].setValue(fndCls);
		}
		
		_resources.fields['selectedInvType'].setValue(getNodeValue("InvestType",invType));
		_resources.fields['selectedFndCls'].setValue(getNodeValue("FundClassList"+group,fndCls));
		_resources.fields['selectedFndGrp'].setValue(getNodeValue("FundGroupList"+group,fndGrp));
		
		_resources.fields['sortByFld'].setValue(sortBy);
		_resources.fields['orderBox'].setValue(descFlag);
		
		if(_inqMode == ""){
			_resources.fields['modeLabel'].setValue(inqMode);
		}
		
		if(activeFlag){
			_resources.fields['modeSrch'].setValue('optActive',true);
		}else{
			_resources.fields['modeSrch'].setValue('optAll',true);
		}
    }
	
    function getNodeValue(listName, code)
    {	
		return IFDS.Xml.getNodeValue(_initXML, "//List[@listName = '" + listName + "']/Element[code = '" + code + "']/value");
    }
	
	function getNodeCode(listName, value)
    {	
        return IFDS.Xml.getNodeValue(_initXML, "//List[@listName = '" + listName + "']/Element[value = '" + value + "']/code");
    }
	
	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	function setInqMode(name)
	{
		_inqMode = name;
		_resources.fields['modeLabel'].setValue(_inqMode);
		
		if(_inqMode == "transaction"){
			_resources.fields['modeSrch'].disable();
		}else{
			_resources.fields['modeSrch'].enable();
		}
	}
	
	function setMoreDetlBtn(node)
	{
		var vIsMoreExists = IFDS.Xml.getNodeValue(node, 'recordsExists').toLowerCase() == 'yes';
		
		if(vIsMoreExists){
			_resources.grids['details'].enableButton('moreBtn');
		}else{
			_resources.grids['details'].disableButton('moreBtn');
		}
	}
	
	function doSearch(runMode,append)
	{
        // build parameter xml
		var requestXML = IFDS.Xml.newDocument('data');
    
		if(runMode == 'init'){
			IFDS.Xml.addSingleNode(requestXML, 'runMode', 'init');	
			IFDS.Xml.addSingleNode(requestXML, 'inqMode', _inqMode);
			IFDS.Xml.addSingleNode(requestXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
			IFDS.Xml.addSingleNode(requestXML, 'investType');	
			IFDS.Xml.addSingleNode(requestXML, 'fundCode', DesktopWeb._SCREEN_PARAM_MAP['Fund']);	
			IFDS.Xml.addSingleNode(requestXML, 'classCode', DesktopWeb._SCREEN_PARAM_MAP['Class']);	
			IFDS.Xml.addSingleNode(requestXML, 'fundGroup');	
			IFDS.Xml.addSingleNode(requestXML, 'transId', DesktopWeb._SCREEN_PARAM_MAP['TransId']);	
			IFDS.Xml.addSingleNode(requestXML, 'activeOnly');	
			IFDS.Xml.addSingleNode(requestXML, 'orderByDESC');	
			IFDS.Xml.addSingleNode(requestXML, 'sortBy');	
			IFDS.Xml.addSingleNode(requestXML, 'investId');	
		}else{
			IFDS.Xml.addSingleNode(requestXML, 'runMode', runMode);	
			IFDS.Xml.addSingleNode(requestXML, 'inqMode', _inqMode);
			IFDS.Xml.addSingleNode(requestXML, 'accountNum', DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);	
			IFDS.Xml.addSingleNode(requestXML, 'investType', _currentSearchCriteria['invType']);
			IFDS.Xml.addSingleNode(requestXML, 'fundCode', _currentSearchCriteria['fund']);	
			IFDS.Xml.addSingleNode(requestXML, 'classCode', _currentSearchCriteria['class']);	
			IFDS.Xml.addSingleNode(requestXML, 'fundGroup', _currentSearchCriteria['fundGroup']);	
			IFDS.Xml.addSingleNode(requestXML, 'transId', DesktopWeb._SCREEN_PARAM_MAP['TransId']);	
			IFDS.Xml.addSingleNode(requestXML, 'activeOnly', _currentSearchCriteria['activeOnly']);	
			IFDS.Xml.addSingleNode(requestXML, 'orderByDESC', _currentSearchCriteria['orderByDESC'] == 0 ? _self.NO:_self.YES);
			IFDS.Xml.addSingleNode(requestXML, 'sortBy', _currentSearchCriteria['sortBy']);	
			IFDS.Xml.addSingleNode(requestXML, 'investId', _currentSearchCriteria['investId']);	
		}
		
		var startRecNum = 1;
		if (append){
			if (runMode == 'reload'){
				startRecNum = _nextStartRecNum;
			}else{
				startRecNum = _nextStartRecNumDtl;
			}
		}
		
		IFDS.Xml.addSingleNode(requestXML, 'startRecNum', startRecNum);	
        IFDS.Xml.addSingleNode(requestXML, 'requestRecNum', _requestRecNum);	
		
		DesktopWeb.Ajax.doSmartviewAjax(_inqView, null, requestXML, responseHandler, _translationMap['ProcMsg_Searching'])
        
		function responseHandler(success, responseXML)
		{						
            if (success)
            {
				
				if (runMode == 'init'){
					_initXML = responseXML;
					populateFirst();
					_mstrXML = _initXML;
				}
				
                if (append)
                {
					if(runMode == "reload"){
						// User clicks summary More button
						var mstrXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(responseXML, "//Investments"));
						var invsXML = IFDS.Xml.getNodes(mstrXML, '//Investment');
						Ext.each(invsXML, function(inv){
							IFDS.Xml.appendNode(IFDS.Xml.getNode(_mstrXML, '//Investments'), inv);
						});
						_resources.grids['summary'].appendData(IFDS.Xml.cloneDocument(IFDS.Xml.getNode(responseXML, '//Investments')));
						_resources.grids['summary'].setSelectedRecord(_nextStartRecNum - 1);
					}else{
						// User clicks detail More button
						var mstrXML = IFDS.Xml.cloneDocument(IFDS.Xml.getNode(responseXML, "//InvestmentDetls"));
						var invDetlsXML = IFDS.Xml.getNodes(mstrXML, '//InvestmentDetl');
						Ext.each(invDetlsXML, function(invDetl){
							IFDS.Xml.appendNode(IFDS.Xml.getNode(_mstrXML, '//InvestmentDetls'), invDetl);
						});
						
						_resources.grids['details'].appendData(IFDS.Xml.cloneDocument(IFDS.Xml.getNode(responseXML, '//InvestmentDetls')));
						_resources.grids['details'].setSelectedRecord(_nextStartRecNumDtl - 1);
						
						// Replace node for control more button
						var selInvNode = IFDS.Xml.getNode(_mstrXML, '//Investments/Investment['+ _indInv +']/InvestmentDetls');
						var newStartRec = IFDS.Xml.getNodeValue(responseXML, '//Investments/Investment/InvestmentDetls/StartRecNum');
						var newRecExists = IFDS.Xml.getNodeValue(responseXML, '//Investments/Investment/InvestmentDetls/recordsExists');
						IFDS.Xml.replaceSingleNode(selInvNode, 'StartRecNum', newStartRec);
						IFDS.Xml.replaceSingleNode(selInvNode, 'recordsExists', newRecExists);
						setMoreDetlBtn(selInvNode);
					}              
                }else{
                    _mstrXML = IFDS.Xml.cloneDocument(responseXML);
                    _resources.grids['summary'].loadData(_mstrXML);
                }
            }
			
			setInqMode(_inqMode);
			
			if(runMode == 'reload' || runMode == 'init'){
				_nextStartRecNum = DesktopWeb.Ajax.getSmartviewNextStartRecNum(responseXML);
				if (_nextStartRecNum){
					_resources.grids['summary'].enableButton('moreBtn');
				}else{
					_resources.grids['summary'].disableButton('moreBtn');
				}
			}
		}
	}
	
	
		
	// PUBLIC ITEMS *************************************
	return {	
		YES: 'yes', NO: 'no'
		
	,init: function(res)
	{
		_resources = res;
        _self = DesktopWeb._SCREEN_CONTROLLER;

		if (DesktopWeb._SCREEN_PARAM_MAP['TransId'] == null){
			_inqMode = 'account';
		}else{
			_inqMode = 'transaction';
		}
		
        doSearch('init',false);
        function responseHandler1(success, responseXML)
        {				
            if (success)
            {
                _initXML = responseXML;
                populateFirst();
				_mstrXML = _initXML;
				_resources.grids['summary'].loadData(_mstrXML);
            }
        }
	}

	,search: function()
    {
        // Store search criteria; they would be used for more button
        _currentSearchCriteria['invType'] = _self.getValueDesc('invTypeFld');
        _currentSearchCriteria['fund'] = _self.getFund(_self.getValueDesc('fndClssFld'));
        _currentSearchCriteria['class'] = _self.getClass(_self.getValueDesc('fndClssFld'));
        _currentSearchCriteria['fundGroup'] = _self.getValueDesc('fndGrpFld');
        _currentSearchCriteria['sortBy'] = _resources.fields['sortByFld'].getValue();
        _currentSearchCriteria['orderByDESC'] = _resources.fields['orderBox'].getValue(); // true = desc
		_currentSearchCriteria['investId'] = "";
		_inqMode = "account";
	
        // Clear data in grid before do actual search
        clearGrid('summary');
        clearGrid('details');
        _self.clearInfo();
        
        // Call doSearch
        doSearch('reload',false);  
    }
	
	,getValueDesc: function(field)
	{
		if(_resources.fields[field].getValueDesc() == null){
			return _resources.fields[field].getValue();
		}else{
			return _resources.fields[field].getValueDesc();
		}
	}
	
	,getDetailsListXML: function(listName)
    {
        return IFDS.Xml.getNode(_initXML, "//List[@listName = '" + listName + "']");
    }
	
	,populateDropdowns: function(invCode)
    {
        var fundClass = "FundClassList" + invCode;
        _resources.fields['fndClssFld'].setValue("");
		_resources.fields['fndClssFld'].enable();
		
		if(this.getDetailsListXML(fundClass) == null){
			_isFndClsDisable = true;
			_resources.fields['fndClssFld'].disable();
		}else{
			_resources.fields['fndClssFld'].enable();
			_resources.fields['fndClssFld'].loadData(this.getDetailsListXML(fundClass));
		}
		
        var fundGrp = "FundGroupList" + invCode;
        _resources.fields['fndGrpFld'].setValue("");
		_resources.fields['fndGrpFld'].enable();
		
		if(this.getDetailsListXML(fundGrp) == null){
			_isFndClsDisable = false;
			_resources.fields['fndGrpFld'].disable();
		}else{
			_resources.fields['fndGrpFld'].enable();
			_resources.fields['fndGrpFld'].loadData(this.getDetailsListXML(fundGrp));
		}
        
    }
	
	,clearFilter: function()
	{
		_resources.fields['fndClssFld'].setValue("");
		_resources.fields['fndGrpFld'].setValue("");
		_resources.fields['fndClssFld'].enable();
		_resources.fields['fndGrpFld'].enable();
		_resources.fields['selectedInvType'].setValue("");
		_resources.fields['selectedFndCls'].setValue("");
		_resources.fields['selectedFndGrp'].setValue("");
	}
	
	,clearInfo: function()
    {
        _resources.fields['invIDLabel'].setValue("");
        _resources.fields['statLabel'].setValue("");
        _resources.fields['lastActivityDateLabel'].setValue("");
        _resources.fields['origInvIDLabel'].setValue("");
        _resources.fields['origFndLabel'].setValue("");
        _resources.fields['origClsLabel'].setValue("");
        _resources.fields['unitLabel'].setValue("");
        _resources.fields['fundLabel'].setValue("");
        _resources.fields['classLabel'].setValue("");
        _resources.fields['aggBalLabel'].setValue("");
        
        _resources.grids['summary'].disableButton('withHoldBtn');
    }
	
	,getFund: function(fundClass)
	{
		if(fundClass == null)
			return "";
		return fundClass.substring(0, fundClass.indexOf('/'));
	}
	
	,getClass: function(fundClass)
	{
		if(fundClass == null)
			return "";
		return fundClass.substring(fundClass.indexOf('/')+1, fundClass.length);
	}
	
	,populateDetails: function(rec)
    {
        if(rec)
        {
			_resources.fields['invIDLabel'].setValue(rec.data['investId']);
			_resources.fields['statLabel'].setValue(rec.data['investStat']);
			_resources.fields['lastActivityDateLabel'].setValue(rec.data['lastActivityDate']);
			_resources.fields['origInvIDLabel'].setValue(rec.data['origInvestId']);
			_resources.fields['origFndLabel'].setValue(rec.data['origFund']);
			_resources.fields['origClsLabel'].setValue(rec.data['origClass']);
			_resources.fields['unitLabel'].setValue(rec.data['unitCost']);
			_resources.fields['fundLabel'].setValue(rec.data['fundCode']);
			_resources.fields['classLabel'].setValue(rec.data['classCode']);
			
			if(_isFndClsDisable){
				_resources.fields['aggBalLabel'].setValue(rec.data['aggrBalance']);
				_resources.fields['aggBalLabel'].show();
			}else{
				_resources.fields['aggBalLabel'].hide();
			}
			
			this.setWithHoldBtn(rec.data['enableWithHoldTax'] == this.YES ? true: false);
		
			
        }
    }
	
	,openPopup: function(name,selectedRec)
    {
        var title = "";
        switch(name)
        {
            case 'withHold':
                title = _translationMap['WithHoldTax'];
				_resources.popups[name].init(title,selectedRec.data);
                break;		
            case 'redem':
                title = _translationMap['RedDetl'];
				_resources.popups[name].init(title);
				_resources.grids['redemGrid'].loadData(IFDS.Xml.getNode(_mstrXML, '//InvestmentDetl['+ _indDetl +']/RedeemDetls'));
                break;		
            case 'fee':
                title = _translationMap['Fee'];
				_resources.popups[name].init(title);
				_resources.grids['feeGrid'].loadData(IFDS.Xml.getNode(_mstrXML, '//Investment[' + _indInv + ']/InvestmentDetls/InvestmentDetl['+ _indDetl +']/InvestmentFees'));
				break;				
        }		
		
        _resources.popups[name].show();
    }
	
	,clickHandle_moreBtn: function()
	{
		// Store search criteria; they would be used for more button
        _currentSearchCriteria['invType'] = _self.getValueDesc('invTypeFld');
        _currentSearchCriteria['fundGroup'] = _self.getValueDesc('fndGrpFld');
        _currentSearchCriteria['sortBy'] = _resources.fields['sortByFld'].getValue();
        _currentSearchCriteria['orderByDESC'] = _resources.fields['orderBox'].getValue(); // true = desc
		
		_inqMode = "account";
		
		doSearch('reload', true);
	}
	
	,clickHandle_moreBtnDetl: function()
	{
		// Store search criteria; they would be used for more button
        _currentSearchCriteria['invType'] = _self.getValueDesc('invTypeFld');
        _currentSearchCriteria['fundGroup'] = _self.getValueDesc('fndGrpFld');
        _currentSearchCriteria['sortBy'] = _resources.fields['sortByFld'].getValue();
        _currentSearchCriteria['orderByDESC'] = _resources.fields['orderBox'].getValue(); // true = desc
		_currentSearchCriteria['investId'] = _resources.fields['invIDLabel'].getValue();
		
		// update record number
		var grid = _resources.grids['summary'];
		var selectedInd = grid.getRecordIndex(grid.getSelectedRecord()) + 1;
		_nextStartRecNumDtl = IFDS.Xml.getNodeValue(_mstrXML, '//Investment[' + selectedInd + ']/InvestmentDetls/StartRecNum');
		
		doSearch('reloadDetl', true);
	}
	
	,clickHandle_link: function(transId)
	{
		runMode = "reload"
		_inqMode = "transaction";
		DesktopWeb._SCREEN_PARAM_MAP['TransId'] = transId;
		doSearch('reload', false);
	}
	
	,changeHandle_ModeSrch: function()
	{
		if(_inqMode == 'account'){
			_currentSearchCriteria['activeOnly'] = _resources.fields['modeSrch'].getValue().getGroupValue() == 'true' ? _self.YES: _self.NO;
		}else{
			_currentSearchCriteria['activeOnly'] = "";
		}
	}
	
	,setWithHoldBtn: function(flag)
	{
		if(flag){
			_resources.grids['summary'].enableButton('withHoldBtn');
		}else{
			_resources.grids['summary'].disableButton('withHoldBtn');
		}		
	}
	
	,setFeeBtn: function(name,flag)
	{
		if(flag){
			_resources.grids['details'].enableButton(name);
		}else{
			_resources.grids['details'].disableButton(name);
		}		
	}

	,buildDetls: function(ind)
	{
		if(ind){
			_indInv = ind;
			_resources.grids['details'].loadData(IFDS.Xml.getNode(_mstrXML, '//Investment['+ _indInv +']/InvestmentDetls'));
			setMoreDetlBtn(IFDS.Xml.getNode(_mstrXML, '//Investment[' + _indInv + ']/InvestmentDetls'));
		}
	}
	
	,buildButtons: function(record,ind)
	{
		this.setFeeBtn('feeBtn',record.data['enableFee'] == this.YES ? true: false);
		this.setFeeBtn('redDetlBtn',record.data['enableRedDetl'] == this.YES ? true: false);
		_indDetl = ind;
	}
	
	}
}	