 /*********************************************************************************************
 * @file	ClassSetup_EventGen.Controller.js
 * @author	Cherdsak Sangkasen
 * @desc	Controller JS file for Event Date Generate screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = 'dtEventDateGenInit';     //mdy
	var _reloadView = 'dtEventDateGenReload'; //mdy
	var _updateView = 'dtEventDateGenProc';	  //dmy
	var _defaultValues = {};
	var _vars = {};	
	var _screenId = "EventGen";
	
	// PRIVATE METHODS ****************************************	
	function populateDropdowns(xml)
	{
	}	
	
	function storeDefaultValues(xml)
	{
		_defaultValues['year'] = IFDS.Xml.getNodeValue(xml, '//defaultYear');
	}
	
	function getUpdateRequest()
	{
		//On update service, we have to set dateformat as dmy.
		//As there is a problem on job scheduler.
		var requestXML = IFDS.Xml.newDocument("data");
		
		IFDS.Xml.addSingleNode(requestXML, 'fund', _vars['fund']);
		IFDS.Xml.addSingleNode(requestXML, 'class', _vars['class']);
		IFDS.Xml.addSingleNode(requestXML, 'year', _resources.fields['txtYear'].getValue());
		
		if (_resources.fields['optValidationDate'].getValue()) {
			IFDS.Xml.addSingleNode(requestXML, 'valnFlag', "yes");
			IFDS.Xml.addSingleNode(requestXML, 'valnStart', _resources.fields['dtpValuationDate'].getValue().format('d/m/Y'));
			IFDS.Xml.addSingleNode(requestXML, 'crystalFlag', "no");
			IFDS.Xml.addSingleNode(requestXML, 'crystalStart', _vars['valnStartDateDMY']);
			IFDS.Xml.addSingleNode(requestXML, 'distribFlag', "no");
			IFDS.Xml.addSingleNode(requestXML, 'distribStart', _vars['valnStartDateDMY']);
			IFDS.Xml.addSingleNode(requestXML, 'dealingFlag', "no");
			IFDS.Xml.addSingleNode(requestXML, 'dealingStart', _vars['valnStartDateDMY']);
		}
		
		if (_resources.fields['optEventTradeDate'].getValue()) {
			IFDS.Xml.addSingleNode(requestXML, 'valnFlag', "no");
			IFDS.Xml.addSingleNode(requestXML, 'valnStart', _vars['valnStartDateDMY']);
			if (_resources.fields['chkCrystalisation'].getValue()) {
				IFDS.Xml.addSingleNode(requestXML, 'crystalFlag', "yes");	
				IFDS.Xml.addSingleNode(requestXML, 'crystalStart', _resources.fields['cboCrystalisation'].getDMYValue());
			}
			else {
				IFDS.Xml.addSingleNode(requestXML, 'crystalFlag', "no");
				IFDS.Xml.addSingleNode(requestXML, 'crystalStart', _vars['valnStartDateDMY']);			
			}
			
			if (_resources.fields['chkDistribution'].getValue()) {
				IFDS.Xml.addSingleNode(requestXML, 'distribFlag', "yes");

				IFDS.Xml.addSingleNode(requestXML, 'distribStart', _resources.fields['cboDistribution'].getDMYValue());
			}
			else {
				IFDS.Xml.addSingleNode(requestXML, 'distribFlag', "no");
				IFDS.Xml.addSingleNode(requestXML, 'distribStart', _vars['valnStartDateDMY']);
			}
					
			if (_resources.fields['chkDealing'].getValue()) {
				IFDS.Xml.addSingleNode(requestXML, 'dealingFlag', "yes");	
				IFDS.Xml.addSingleNode(requestXML, 'dealingStart', _resources.fields['cboDealing'].getDMYValue());			
			}
			else {
				IFDS.Xml.addSingleNode(requestXML, 'dealingFlag', "no");	
				IFDS.Xml.addSingleNode(requestXML, 'dealingStart', _vars['valnStartDateDMY']);			
			}
		}	
		
		return requestXML;		
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
		
		updatesFlag: false		
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;		
			
			var requestXML = IFDS.Xml.newDocument("data");
			var isFrontValid = true;
					
			DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = "mdy";
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['DoLoad']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{
					populateDropdowns(responseXML);
					storeDefaultValues(responseXML);	
					_self.setOption(false, false, false, false);	
					_resources.fields['txtYear'].setValue(_defaultValues['year']);
				}
			}
		}
		
		, doSearch: function()
		{
			if (_resources.fields['cboFundClass'].selectedRecord && _resources.fields['txtYear'].getValue() != "")
			{
				_self.isFrontValid = true;
				_self.doOptCheck("NONE");
				_self.doEventCheck("ALL", false);
								
				var requestXML = IFDS.Xml.newDocument("data");		
				IFDS.Xml.addSingleNode(requestXML, "fund", _resources.fields['cboFundClass'].selectedRecord.get('fundCode'));	
				IFDS.Xml.addSingleNode(requestXML, "class", _resources.fields['cboFundClass'].selectedRecord.get('classCode'));
				IFDS.Xml.addSingleNode(requestXML, "year", _resources.fields['txtYear'].getValue());
				
				if (requestXML)
				{
					DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = "mdy";
					DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['DoSearch']);

					function responseHandler(success, responseXML)
					{
						if (success)
						{						
							var index = 0;
							_vars['fund'] = _resources.fields['cboFundClass'].selectedRecord.get('fundCode');
							_vars['class'] = _resources.fields['cboFundClass'].selectedRecord.get('classCode');
							_vars['firstGen'] = IFDS.Xml.getNodeValue(responseXML, '//firstGen');
							_vars['valnStartDate'] = DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(responseXML, '//valnStartDate'));
							_vars['valnStartDateDMY'] = DesktopWeb.Util.convertDateStringFormat(IFDS.Xml.getNodeValue(responseXML, '//valnStartDate')
									, DesktopWeb._SCREEN_PARAM_MAP['dateFormat'], "dmy");
							_resources.fields['dtpValuationDate'].setValue(_vars['valnStartDate']);
							if (IFDS.Xml.getNode(responseXML, "//List[@listName='ValnDateList']"))
							{
								_resources.fields['cboCrystalisation'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='ValnDateList']"));
								
								_resources.fields['cboCrystalisation'].setValue(_resources.fields['cboCrystalisation'].getStore().getAt(index).get(_resources.fields['cboCrystalisation'].valueField)); 
								
								_resources.fields['cboDistribution'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='ValnDateList']"));
								_resources.fields['cboDistribution'].setValue(_resources.fields['cboDistribution'].getStore().getAt(index).get(_resources.fields['cboDistribution'].valueField));
								
								_resources.fields['cboDealing'].loadData(IFDS.Xml.getNode(responseXML, "//List[@listName='ValnDateList']"));
								_resources.fields['cboDealing'].setValue(_resources.fields['cboDealing'].getStore().getAt(index).get(_resources.fields['cboDealing'].valueField));
							}

							if (_vars['firstGen'] == 'yes')
							{
								_self.setOption(true, false, false, false);
							}
							else {
								_self.setOption(true, true, false, false);
							}
						}
					}
				}
			}	
		}
		
		, clearAll: function()
		{
			_vars['fund'] = "";
			_vars['class'] = "";
			_resources.fields['cboCrystalisation'].clearValue();
			_resources.fields['cboDistribution'].clearValue();
			_resources.fields['cboDealing'].clearValue();
			
			_self.setOption(false, false, false, false);
		}
		
		, setOption: function(enaVDate, enaETDate, chkVDate, chkETDate)
		{
			if (enaVDate) {
				_resources.fields['optValidationDate'].enable();
			}
			else {
				_resources.fields['optValidationDate'].disable();
			}
			
			if (enaETDate) {
				_resources.fields['optEventTradeDate'].enable();
			}
			else {
				_resources.fields['optEventTradeDate'].disable();
			}
			
			if (chkVDate) {
				_resources.fields['optValidationDate'].setValue(true);
			}
			else {
				_resources.fields['optValidationDate'].setValue(false);
			}
			
			if (chkETDate) {
				_resources.fields['optEventTradeDate'].setValue(true);
			}
			else {
				_resources.fields['optEventTradeDate'].setValue(false);
			}		
		}
		
		, doOptCheck: function (panel)
		{		
			if (panel == 'Valuation') {
				Ext.getCmp('valuation_fieldset').show();	
				Ext.getCmp('eventtrade_fieldset').hide();	
			}
			if (panel == 'EventTrade') {
				Ext.getCmp('valuation_fieldset').hide();	
				Ext.getCmp('eventtrade_fieldset').show();	
			} 
			if (panel == 'NONE') {
				_self.clearAll();
				Ext.getCmp('valuation_fieldset').hide();
				Ext.getCmp('eventtrade_fieldset').hide();
			}
		}
		
		, doEventCheck: function (panel, val)
		{
			if (panel == 'Crystalisation') {
				if (val) {
					_resources.fields['cboCrystalisation'].enable();
				}
				else {
					_resources.fields['cboCrystalisation'].disable();
				}
			}
			if (panel == 'Distribution') {
				if (val) {
					_resources.fields['cboDistribution'].enable();
				}
				else {
					_resources.fields['cboDistribution'].disable();
				}
			}
			if (panel == 'Dealing') {
				if (val) {
					_resources.fields['cboDealing'].enable();
				}
				else {
					_resources.fields['cboDealing'].disable();
				}
			}
			if (panel == 'ALL') {
				if (val) {
					_resources.fields['cboCrystalisation'].enable();
					_resources.fields['cboDistribution'].enable();
					_resources.fields['cboDealing'].enable();
				}
				else {
					_resources.fields['cboCrystalisation'].disable();
					_resources.fields['chkCrystalisation'].setValue(false);
					_resources.fields['cboDistribution'].disable();
					_resources.fields['chkDistribution'].setValue(false);
					_resources.fields['cboDealing'].disable();
					_resources.fields['chkDealing'].setValue(false);
				}
			}
		}
		
		, doUpdate: function ()
		{
			/* Need to re-format date to 'mdy' ,since Job scheduler only except this format. 
			   Return to original format 'dmy' when the process is finished.*/
			DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = "dmy";	
			DesktopWeb.Ajax.doSmartviewUpdate(_updateView, null, getUpdateRequest(), responseHandler, _translationMap['DoUpdate']);		
				
			function responseHandler(success, responseXML, contextErrors)
			{
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
				}else{
					updateStatus = DesktopWeb._FAIL 	
				}
			}
			return updateStatus;
		}	

		, isFrontValidChk: function()
		{
			var retVal = true;
			
			if ( _resources.fields['dtpValuationDate'].getValue() != "" && _self.isFrontValid)
			{
				_self.updatesFlag = true;
				retVal = true;
			}
			else
			{
				if (_vars['firstGen'] == 'yes')
				{
					_resources.fields['dtpValuationDate'].markInvalid(_translationMap['ValuationDateGenUndefine']); 
				}
				else {
					_resources.fields['dtpValuationDate'].markInvalid(_translationMap['ValuationDateReGenUndefine']); 
				}
				_self.updatesFlag = false;
				retVal = false;
			}
			
			return retVal;
		}
		
	}	
}	