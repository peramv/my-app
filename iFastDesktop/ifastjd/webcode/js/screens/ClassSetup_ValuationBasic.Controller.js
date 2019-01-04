/*********************************************************************************************
 * @file	ClassSetup_ValuationBasic.Controller.js
 * @author	Cherdsak Sangkasen
 * @desc	Controller JS file for Valuation Detail screen	
 *********************************************************************************************/
 /*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54443
 *          - Fix display date format follows dateFormatDisplay parameter
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
	var _globalValues = {};
	var _screenId = "ValuationBasic";
	
	var _reloadView = "dtValnDetlReload";
	var _procView = "dtValnDetlProc";
	var _templatePDF = "DSKValuationDateDetails";
	var _outputPDF = "VALNDEIL";
	var _smvDateFormat = "mdy";
	var _jobDateFormat = "dmy";
	
	
	// PRIVATE METHODS ****************************************	
	function genInnerHTML(fieldName, formula, calculation)
	{
		return '<div style="cursor: pointer;text-decoration:underline;" ext:qtip="Formula: ' + formula + '<br>Calculation: ' + calculation + '">' + fieldName + '</div>';
	}	
	
	function storeGlobalValues(xml)
	{
		_globalValues['allowCanValn'] = IFDS.Xml.getNodeValue(xml, '//Valn/allowCanValn');
		if (IFDS.Xml.getNode(xml, "//Valn/CrysDetl")) 
		{
			_globalValues['allowDefHWM'] = IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/allowDefHWM');		
			_globalValues['allowCanCrys'] = IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/allowCanCrys');
		}
		else
		{
			_globalValues['allowDefHWM'] = _self.NO;
			_globalValues['allowCanCrys'] = _self.NO;
		}
		_globalValues['nav'] = IFDS.Xml.getNodeValue(xml, '//Valn/nav');
		_globalValues['clsAdjHWM'] = IFDS.Xml.getNodeValue(xml, '//Valn/clsAdjHWM');
	}
	
	function gotoEventMain()
	{
		var urlParams = {};
		urlParams['jobname'] = 'DisplayScreen';
		urlParams['screen'] = 'ClassSetup_EvenMain';
		urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
		urlParams['dateFormat'] = _self._smvDateFormat;
		urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
		urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		urlParams['prevScreen'] = _screenId;		
		urlParams['fund'] = _globalValues['fund'];		
		urlParams['class'] = _globalValues['class'];	
		urlParams['fndClsDisp'] = _globalValues['fndClsDisp'];		
		urlParams['startDate'] = _globalValues['startDate'];		
		urlParams['endDate'] = _globalValues['endDate'];			
		urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];
		urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];	
									
		if ("EvenMain" == DesktopWeb._SCREEN_PARAM_MAP['prevScreen'])
		{
			DesktopWeb.Util.goToScreen('ClassSetup_EvenMain', urlParams);
		}
		else
		{
			DesktopWeb.Util.cancelScreen();
		}
	}
	
	function populateDetl(xml)
	{
//prompt('',xml.xml);		
		_resources.fields['dtpValnDate'].setValue(DesktopWeb.Util.getDateDisplayValue(_globalValues['valnDate']));
		_resources.fields['crysFlag'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/crysFlag'));	
		_resources.fields['distFlag'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/distFlag'));
		_resources.fields['gav'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/gav'));
		_resources.fields['distRate'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/distRate'));
		_resources.fields['clsHWM'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/clsHWM'));
		_resources.fields['calcBasis'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/calcBasis'));
		_resources.fields['lossCarrFwOptn'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/lossCarrFwOptn'));
		_resources.fields['divTreatOptn'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/divTreatOptn'));
		_resources.fields['clsHWMDate'].setText(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(xml, '//Valn/clsHWMDate')));
		_resources.fields['calcPrec'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/calcPrec'));
		_resources.fields['numDays'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/numDays'));
		_resources.fields['pfPrec'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/pfPrec'));
		_resources.fields['valStatus'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/valStatus'));
		
		if (IFDS.Xml.getNodeValue(xml, '//Valn/divAdjGav') != _self.BLANK) 
		{		
			_resources.fields['divAdjGav'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/divAdjGav'));
			_resources.fields['lblDivAdjGav'].setText(genInnerHTML(_translationMap['DivAdjGav'], IFDS.Xml.getNodeValue(xml, '//Valn/divAdjGavFML'), IFDS.Xml.getNodeValue(xml, '//Valn/divAdjGavFMLval')), false);
		}
		else
		{
			_resources.fields['divAdjGav'].setText(_self.BLANK);
			_resources.fields['lblDivAdjGav'].setText(_translationMap['DivAdjGav']);
		}	
		
		if (IFDS.Xml.getNodeValue(xml, '//Valn/nav') != _self.BLANK) 
		{		
			_resources.fields['nav'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/nav'));
			_resources.fields['lblNav'].setText(genInnerHTML(_translationMap['Nav'], IFDS.Xml.getNodeValue(xml, '//Valn/navFML'), IFDS.Xml.getNodeValue(xml, '//Valn/navFMLval')), false);
		}
		else
		{
			_resources.fields['nav'].setText(_self.BLANK);
			_resources.fields['lblNav'].setText(_translationMap['Nav']);
		}
		
		if (IFDS.Xml.getNodeValue(xml, '//Valn/pfPerShare') != _self.BLANK) 
		{		
			_resources.fields['pfPerShare'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/pfPerShare'));
			_resources.fields['lblPfPerShare'].setText(genInnerHTML(_translationMap['PfPerShare'], IFDS.Xml.getNodeValue(xml, '//Valn/pfPerShareFML'), IFDS.Xml.getNodeValue(xml, '//Valn/pfPerShareFMLval')), false);
		}
		else
		{
			_resources.fields['pfPerShare'].setText(_self.BLANK);
			_resources.fields['lblPfPerShare'].setText(_translationMap['PfPerShare']);
		}
		
		if (IFDS.Xml.getNodeValue(xml, '//Valn/clsAdjHWM') != _self.BLANK) 
		{		
			_resources.fields['clsAdjHWM'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/clsAdjHWM'));
			_resources.fields['lblClsAdjHWM'].setText(genInnerHTML(_translationMap['ClsAdjHWM'], IFDS.Xml.getNodeValue(xml, '//Valn/clsAdjHWMFML'), IFDS.Xml.getNodeValue(xml, '//Valn/clsAdjHWMFMLval')), false);
		}
		else
		{
			_resources.fields['clsAdjHWM'].setText(_self.BLANK);
			_resources.fields['lblClsAdjHWM'].setText(_translationMap['ClsAdjHWM']);
		}

		if (IFDS.Xml.getNodeValue(xml, '//Valn/effHurdle') != _self.BLANK) 
		{		
			_resources.fields['effHurdle'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/effHurdle'));
			_resources.fields['lblEffHurdle'].setText(genInnerHTML(_translationMap['EffHurdle'], IFDS.Xml.getNodeValue(xml, '//Valn/effHurdleFML'), IFDS.Xml.getNodeValue(xml, '//Valn/effHurdleFMLval')), false);
		}
		else
		{
			_resources.fields['effHurdle'].setText(_self.BLANK);
			_resources.fields['lblEffHurdle'].setText(_translationMap['EffHurdle']);
		}		
	
		// Hurdles
		if (IFDS.Xml.getNode(xml, "//Valn/Hurdles")) 
		{
			_resources.grids['grdHurdle'].loadData(IFDS.Xml.getNode(xml, "//Valn/Hurdles"));		
		}
		else 
		{
			_resources.grids['grdHurdle'].clearData();
		}
		
		// PF Crystalisation Details
		if (IFDS.Xml.getNode(xml, "//Valn/CrysDetl")) 
		{		
			_resources.fields['valEqCr'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/valEqCr'));
			_resources.fields['valEqRed'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/valEqRed'));
			_resources.fields['totEqPurTxn'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/totEqPurTxn'));
			_resources.fields['totEqRedTxn'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/totEqRedTxn'));			
			_resources.fields['crysStatus'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/crysStatus'));
			
			if (IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/newClsHWM') != _self.BLANK) 
			{		
				_resources.fields['newClsHWM'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/newClsHWM'));
				_resources.fields['lblNewClsHWM'].setText(genInnerHTML(_translationMap['NewClsHWM'], IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/newClsHWMFML'), IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/newClsHWMFMLval')), false);
			}
			else
			{
				_resources.fields['newClsHWM'].setText(_self.BLANK);
				_resources.fields['lblNewClsHWM'].setText(_translationMap['NewClsHWM']);
			}
			
			if (IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/totPfAmt') != _self.BLANK) 
			{		
				_resources.fields['totPfAmt'].setText(IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/totPfAmt'));
				_resources.fields['lblTotPfAmt'].setText(genInnerHTML(_translationMap['TotPfAmt'], IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/totPfAmtFML'), IFDS.Xml.getNodeValue(xml, '//Valn/CrysDetl/totPfAmtFMLval')), false);
			}
			else
			{
				_resources.fields['totPfAmt'].setText(_self.BLANK);
				_resources.fields['lblTotPfAmt'].setText(_translationMap['TotPfAmt']);
			}
			
			if (_globalValues['allowDefHWM'] == _self.YES)
			{
				Ext.getCmp('cmdUserDefHWM').enable();
			}
			else
			{
				Ext.getCmp('cmdUserDefHWM').disable();
			}
			
			if (_globalValues['allowCanValn'] == _self.YES)
			{
				Ext.getCmp('cmdValnCancel').enable();
			}
			else
			{
				Ext.getCmp('cmdValnCancel').disable();
			}
			
			if (_globalValues['allowCanCrys'] == _self.YES)
			{
				Ext.getCmp('cmdCrysCancel').enable();
			}
			else
			{
				Ext.getCmp('cmdCrysCancel').disable();
			}			
			
			Ext.getCmp('crystalisation_fieldset').show();
		}
		else 
		{
			_resources.fields['newClsHWM'].setText(_self.BLANK);
			_resources.fields['valEqCr'].setText(_self.BLANK);
			_resources.fields['valEqRed'].setText(_self.BLANK);
			_resources.fields['totEqPurTxn'].setText(_self.BLANK);
			_resources.fields['totEqRedTxn'].setText(_self.BLANK);
			_resources.fields['totPfAmt'].setText(_self.BLANK);
			_resources.fields['crysStatus'].setText(_self.BLANK);
			
			Ext.getCmp('crystalisation_fieldset').hide();
		}		
	}
	
	function clearScreen()
	{		
		_resources.fields['crysFlag'].setText(_self.BLANK);	
		_resources.fields['distFlag'].setText(_self.BLANK);
		_resources.fields['gav'].setText(_self.BLANK);
		_resources.fields['distRate'].setText(_self.BLANK);
		_resources.fields['clsHWM'].setText(_self.BLANK);
		_resources.fields['calcBasis'].setText(_self.BLANK);
		_resources.fields['lossCarrFwOptn'].setText(_self.BLANK);
		_resources.fields['divTreatOptn'].setText(_self.BLANK);
		_resources.fields['clsHWMDate'].setText(_self.BLANK);
		_resources.fields['calcPrec'].setText(_self.BLANK);
		_resources.fields['numDays'].setText(_self.BLANK);
		_resources.fields['pfPrec'].setText(_self.BLANK);
		_resources.fields['valStatus'].setText(_self.BLANK);
		
		_resources.fields['divAdjGav'].setText(_self.BLANK);
		_resources.fields['lblDivAdjGav'].setText(_translationMap['DivAdjGav']);
		
		_resources.fields['nav'].setText(_self.BLANK);
		_resources.fields['lblNav'].setText(_translationMap['Nav']);
		
		_resources.fields['pfPerShare'].setText(_self.BLANK);
		_resources.fields['lblPfPerShare'].setText(_translationMap['PfPerShare']);
		
		_resources.fields['clsAdjHWM'].setText(_self.BLANK);
		_resources.fields['lblClsAdjHWM'].setText(_translationMap['ClsAdjHWM']);
		
		_resources.fields['effHurdle'].setText(_self.BLANK);
		_resources.fields['lblEffHurdle'].setText(_translationMap['EffHurdle']);
		
		Ext.getCmp('cmdValnCancel').disable();
		_resources.grids['grdHurdle'].clearData();
		
		_resources.fields['newClsHWM'].setText(_self.BLANK);
		_resources.fields['valEqCr'].setText(_self.BLANK);
		_resources.fields['valEqRed'].setText(_self.BLANK);
		_resources.fields['totEqPurTxn'].setText(_self.BLANK);
		_resources.fields['totEqRedTxn'].setText(_self.BLANK);
		_resources.fields['totPfAmt'].setText(_self.BLANK);
		_resources.fields['crysStatus'].setText(_self.BLANK);
		
		Ext.getCmp('crystalisation_fieldset').hide();
		
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		BLANK: ''
		, YES: 'yes'
		, NO: 'no'
		
		, init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			
			_self._smvDateFormat = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
			_self._jobDateFormat = "dmy";
			
			Ext.QuickTips.init();
			Ext.apply(Ext.QuickTips.getQuickTip(), { maxWidth: 800, minWidth: 100, showDelay: 50, trackMouse: true }); 
						
			_globalValues['fund'] = DesktopWeb._SCREEN_PARAM_MAP['fund'];
			_globalValues['class'] = DesktopWeb._SCREEN_PARAM_MAP['class'];
			_globalValues['fndClsDisp'] = DesktopWeb._SCREEN_PARAM_MAP['fndClsDisp'];
			//valnDate parameter is sent in SMV format.
			_globalValues['valnDate'] = DesktopWeb._SCREEN_PARAM_MAP['valnDate'];
			_globalValues['valnDateDMY'] = DesktopWeb.Util.convertDateStringFormat(_globalValues['valnDate'], "mdy", "dmy");
			_globalValues['startDate'] = DesktopWeb._SCREEN_PARAM_MAP['startDate'];
			_globalValues['endDate'] = DesktopWeb._SCREEN_PARAM_MAP['endDate'];
			_globalValues['bfValnDate'] = "";
			
			_resources.fields['header'].setText(_self.getHeader());
			
			_self.doSearch();
			
		}
		
		, doSearch: function()
		{
			DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _self._smvDateFormat;	
			
			var requestXML = IFDS.Xml.newDocument("data");	
			IFDS.Xml.addSingleNode(requestXML, "fund", _globalValues['fund']);	
			IFDS.Xml.addSingleNode(requestXML, "class", _globalValues['class']);	
			IFDS.Xml.addSingleNode(requestXML, "valnDate", _globalValues['valnDate']);
			
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, requestXML, responseHandler, _translationMap['Load']);
			
			function responseHandler(success, responseXML)
			{
				if (success)
				{																							
					storeGlobalValues(responseXML)
					populateDetl(responseXML);					
				}
				else
				{				
					clearScreen();
				}
			}
		}
		
		, doReload: function()
		{
			_globalValues['valnDate'] = _resources.fields['dtpValnDate'].getSMVDateString();
			_globalValues['valnDateDMY'] = DesktopWeb.Util.convertDateStringFormat(
								_globalValues['valnDate']
						, _self._smvDateFormat
						, _self._jobDateFormat); //DMY format
			
			_self.doSearch();
		}
		
		, doProcess: function(data)
		{
			var proc;
			
			switch (data["proc"])
			{
				case "CancelValn":
				{
					proc = "CanValn";
					break;
				}
				case "CancelCrys":
				{
					proc = "CanCrys";
					break;
				}
				case "UserDefHWM":
				{
					proc = "SetHWM";
					break;
				}
			}
			
			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, "procMode", proc);	
			IFDS.Xml.addSingleNode(requestXML, "fund", _globalValues['fund']);	
			IFDS.Xml.addSingleNode(requestXML, "class", _globalValues['class']);	
			IFDS.Xml.addSingleNode(requestXML, "valnDate", _globalValues['valnDateDMY']);
			
			IFDS.Xml.addSingleNode(requestXML, "newClsHWM", data["newClsHWM"]);	
			IFDS.Xml.addSingleNode(requestXML, "nav", _globalValues['nav']);	
			IFDS.Xml.addSingleNode(requestXML, "clsAdjHWM", _globalValues['clsAdjHWM']);
								
			DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _self._jobDateFormat;	

			DesktopWeb.Ajax.doSmartviewUpdate(_procView, null, requestXML, responseHandler, _translationMap['Update']);			
			
			function responseHandler(success, responseXML, contextErrors)
			{
				DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _self._smvDateFormat;
				if (success)
				{
					updateStatus = DesktopWeb._SUCCESS;
					
					if (_resources.popups['frmProcCancel'].isValid())
					{
						_resources.popups['frmProcCancel'].hide();
					}
					if (_resources.popups['frmNewHWM'].isValid())
					{
						_resources.popups['frmNewHWM'].hide();
					}
					
					if (data["proc"] == "CancelCrys" || data["proc"] == "CancelValn") 
					{
						_self.goEventMain();
					}
					else
					{	
						_self.doSearch();
					}
				}
				else 
				{
					updateStatus = DesktopWeb._FAIL; 	
				}
			}	
		}
		
		, populateProcess: function(proc)
		{
			_resources.fields['txtValnDate'].setValue(_globalValues['valnDate']);	
			_resources.fields['txtCrysFlag'].setValue(_resources.fields['crysFlag'].text);
			_resources.fields['txtDistFlag'].setValue(_resources.fields['distFlag'].text);
			if (proc == 'CancelValn')
			{
				_resources.fields['txtStatus'].setValue(_resources.fields['valStatus'].text);
			}
			else
			{
				_resources.fields['txtStatus'].setValue(_resources.fields['crysStatus'].text);
			}
		}
		
		, populateNewHWN: function()
		{
			_resources.fields['txtNewHWM'].setValue("");	
		}
				
		, openActionPopup: function(popupName, proc)
		{
			_resources.popups[popupName].init(proc);
			_resources.popups[popupName].show();
		}
		
		, goEventMain: function()
		{
			gotoEventMain();
		}
		
		, exportPDF: function()
		{
			DesktopWeb.Util.displayPrompt(_translationMap['DoExportConfirm'], callback);					
			
			function callback(buttonId)
			{
				if (buttonId == 'ok') 
				{
					DesktopWeb._SCREEN_PARAM_MAP['dateFormat'] = _self._smvDateFormat;
			
					var requestXML = IFDS.Xml.newDocument("data");	
					IFDS.Xml.addSingleNode(requestXML, "fund", _globalValues['fund']);	
					IFDS.Xml.addSingleNode(requestXML, "class", _globalValues['class']);	
					IFDS.Xml.addSingleNode(requestXML, "valnDate", _globalValues['valnDate']);
					
					DesktopWeb.Ajax.doBuildPDFReport(_reloadView, _templatePDF, _outputPDF, requestXML)	;
				}
			}
		}
		
		, getHeader: function()
		{
			return _translationMap['ValuationDetails'] + " - Fund: " + _globalValues['fund'] + ", Class: " + _globalValues['class'] ;
		}
	}	
}	