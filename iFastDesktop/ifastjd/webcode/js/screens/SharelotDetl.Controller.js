/*********************************************************************************************
 * @file	SharelotDetl.Controller.js
 * @author	Haroon Chaudhry
 * @desc	Control JS file for Sharelot Detail screen
 *********************************************************************************************/
/*
 * Procedure: SharelotDetl.Controller.js
 *
 * Purpose  : Control JS file for Sharelot Details screen
 *             
 * Notes    : 
 *
 * History  :  
 *		15 Feb 2011 Haroon Chaudhry
 *				- Initial created for Performance Fee Project
 *
 *
 *		21 Nov 2013 Winnie Cheng. P0216756 FN01  T77441
 *					- Performance Fee SOC 2/3 Project
 *					- ActiveOnly and TransID value need to be passed.
 *
 * 		21 Nov 2013 Supareuk S. PETP0181067 FN01 CHG0034430 T54443
 *            		- Correct the format of all date fields based on registry edit
 *              	  ,called displayMark
 *              
 *  07 May 2018 Pao - Supareuk S.
 *  		We changed a way to get xml response from smartview service from doSmartviewCall
 *  		to doSmartviewAjax function. This is to solve an issue when user's profile has 
 *  		too many slot attached. If the session is included, the page will be broken as 
 *  		too large.	
 */
	
Ext.QuickTips.init();
Ext.apply(Ext.QuickTips.getQuickTip(), {
    maxWidth: 200,
    minWidth: 100,
    showDelay: 50,
    trackMouse: true
});


DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _initDataXML = null;
	var _initView = 'sharelotDetails';
	var _asOfDate='';
	var _translationMap = DesktopWeb.Translation.getTranslationMap();

	// PRIVATE METHODS ****************************************
	function setLabelTextFromNode(label,doc,node){
		if(IFDS.Xml.getNode(doc, node)){
			if ((label == 'tradeDT') || (label == 'lotHWMDT')){
				_resources.fields[label].setText(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(doc, node)));
			}
			else{
				_resources.fields[label].setText(IFDS.Xml.getNodeValue(doc, node));
			}
		}
	}
	
	function setValueFromNode(field,doc,node){
		if(IFDS.Xml.getNode(doc, node)){
			if (field == 'valuationDT'){
				_resources.fields[field].setValue(DesktopWeb.Util.getDateDisplayValue(IFDS.Xml.getNodeValue(doc, node)));
			}
			else{
				_resources.fields[field].setValue(IFDS.Xml.getNodeValue(doc, node));
			}
		}
	}
		
	function populateLabelText(dataXML){
		
		setValueFromNode('valuationDT',dataXML,'//SharelotDetail/valuationDate');
				
		setLabelTextFromNode('transType',dataXML,'//SharelotDetail/transType');
		setLabelTextFromNode('transNum',dataXML,'//SharelotDetail/transNumber');
		setLabelTextFromNode('tradeDT',dataXML,'//SharelotDetail/tradeDate');
		setLabelTextFromNode('origUnits',dataXML,'//SharelotDetail/origUnits');
		setLabelTextFromNode('change',dataXML,'//SharelotDetail/unitChange');
		setLabelTextFromNode('unitBal',dataXML,'//SharelotDetail/unitBalPreCrys');
		setLabelTextFromNode('lotHWM',dataXML,'//SharelotDetail/lotHWM');
		setLabelTextFromNode('lotHWMDT',dataXML,'//SharelotDetail/lotHWMDate');
		setLabelTextFromNode('numOfDays',dataXML,'//SharelotDetail/noOfDaysValn');
		setLabelTextFromNode('lotEffHurd',dataXML,'//SharelotDetail/lotEffHurdle');
		
		setLabelTextFromNode('lotEQmv',dataXML,'//SharelotDetail/lotEQmvPer');
		
		setLabelTextFromNode('lotEQpot',dataXML,'//SharelotDetail/lotEQpotPer');
		
		setLabelTextFromNode('lotPFFee',dataXML,'//SharelotDetail/lotPFShare');
		setLabelTextFromNode('lotShrVal',dataXML,'//SharelotDetail/lotShareValue');
		setLabelTextFromNode('lotVal',dataXML,'//SharelotDetail/totLotValue');
		
		setLabelTextFromNode('pfTotalPayable',dataXML,'//SharelotDetail/lotTTPayPerTotal');
				
		setLabelTextFromNode('lotClassPFTotal',dataXML,'//SharelotDetail/lotClsTotal');
		
		
		setLabelTextFromNode('closingBal',dataXML,'//SharelotDetail/unitBalPostCrys');
		
		//REMOVED		
		//setLabelTextFromNode('lotTotPF',dataXML,'//SharelotDetail/lotTTPayPerShare');
		//setLabelTextFromNode('lossCarFwd',dataXML,'//SharelotDetail/eQLostPerShare');
		//setLabelTextFromNode('lotClassPF',dataXML,'//SharelotDetail/lotClsPerShare');
		

		
		setLabelTextFromNode('lotEQmvTotal',dataXML,'//SharelotDetail/lotEQmvTotal');
		setLabelTextFromNode('lotEQpotTotal',dataXML,'//SharelotDetail/lotEQpotTotal');
		setLabelTextFromNode('lossCryFwdTotal',dataXML,'//SharelotDetail/eQLostTotal');
		
		setLabelTextFromNode('classNAV',dataXML,'//SharelotDetail/ClassPreCrys/nav');
		setLabelTextFromNode('classGAV',dataXML,'//SharelotDetail/ClassPreCrys/gav');
		setLabelTextFromNode('pfPerShare',dataXML,'//SharelotDetail/ClassPreCrys/perfFeePerShare');
		
		setLabelTextFromNode('lotAdjHWM',dataXML,'//SharelotDetail/lotAdjHWM');

		
		var crystalisationNode = IFDS.Xml.getNode(dataXML,'//SharelotDetail/Crystallization');
		var crystalisationTrans = IFDS.Xml.getNode(dataXML,'//SharelotDetail/Crystallization/transNumber');
		var crystalisationTransValue = 0;
		if(crystalisationTrans)
			crystalisationTransValue = IFDS.Xml.getNodeValue(dataXML,'//SharelotDetail/Crystallization/transNumber');
		if(crystalisationNode){
			setLabelTextFromNode('eqAmount',dataXML,'//SharelotDetail/Crystallization/eqAmount');
			setLabelTextFromNode('transitionType',dataXML,'//SharelotDetail/Crystallization/transType');
			setLabelTextFromNode('NAV',dataXML,'//SharelotDetail/Crystallization/nav');
			setLabelTextFromNode('transNumber',dataXML,'//SharelotDetail/Crystallization/transNumber');
			setLabelTextFromNode('numOfUnit',dataXML,'//SharelotDetail/Crystallization/units');
			setLabelTextFromNode('newLotHWM',dataXML,'//SharelotDetail/Crystallization/newLotHWM');

			Ext.getCmp('PFCrystInfo_fieldset').doLayout();

			Ext.getCmp('PFCrystInfo_fieldset').show();

		}else{
			Ext.getCmp('PFCrystInfo_fieldset').hide();
			_resources.fields['eqAmount'].setText('');
			_resources.fields['transitionType'].setText('');
			_resources.fields['NAV'].setText('');
			_resources.fields['transNumber'].setText('');
			_resources.fields['numOfUnit'].setText('');
		}		
	}	
	
	function registerFormulaTip(field,node){
		if(node){
			Ext.QuickTips.unregister(_resources.fields[field].id);
			Ext.QuickTips.register({
			    target: _resources.fields[field].id,
			    title: IFDS.Xml.getNodeValue(node, 'description'),
			    text: '<br/>'+IFDS.Xml.getNodeValue(node, 'form')+'<br/><br/>'+IFDS.Xml.getNodeValue(node, 'value'),
			    width: 250,
			    dismissDelay: 5000
			});
		}
		// else
			// alert('Null node for field '+field);
	}
	
	function addFormulaTips(dataXML){
		
		
		
		registerFormulaTip('pfTotalPayable',IFDS.Xml.getNode(dataXML, 'LotTotPFAmt'));
		
		registerFormulaTip('lotEffHurd',IFDS.Xml.getNode(dataXML, 'LotEffHurdle'));
		
		registerFormulaTip('lotClassPFTotal',IFDS.Xml.getNode(dataXML, 'LotClPFAmt'));

		registerFormulaTip('lotHWM',IFDS.Xml.getNode(dataXML, 'LotHWM'));
		
		if(IFDS.Xml.getNode(dataXML, 'LotHWM')){
			Ext.getDom(_resources.fields['lotHWM']).getEl().setStyle('color','blue');
		}else{
			Ext.getDom(_resources.fields['lotHWM']).getEl().setStyle('color','black');
		}
		
		registerFormulaTip('lotEQmv',IFDS.Xml.getNode(dataXML, 'LotEQmvsh'));
		registerFormulaTip('lotEQmvTotal',IFDS.Xml.getNode(dataXML, 'LotEQmvAmt'));
		registerFormulaTip('lotEQpot',IFDS.Xml.getNode(dataXML, 'LotEQpotsh'));
		registerFormulaTip('lotEQpotTotal',IFDS.Xml.getNode(dataXML, 'LotEQpotAmt'));
		
		registerFormulaTip('lossCryFwdTotal',IFDS.Xml.getNode(dataXML, 'LossCalc'));

		registerFormulaTip('lotPFFee',IFDS.Xml.getNode(dataXML, 'LotPFsh'));
		
		registerFormulaTip('lotAdjHWM',IFDS.Xml.getNode(dataXML, 'LotAdjHWM'));
		
		registerFormulaTip('lotPFFee',IFDS.Xml.getNode(dataXML, 'LotPFPerSh'));
		
		registerFormulaTip('newLotHWM',IFDS.Xml.getNode(dataXML, 'LotResetHWM'));
		
		registerFormulaTip('lotShrVal',IFDS.Xml.getNode(dataXML, 'LotShareAmt'));
		
		registerFormulaTip('lotVal',IFDS.Xml.getNode(dataXML, 'TotalLoteAmt'));
	}
		
	// PUBLIC ITEMS *************************************	
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			_asOfDate=DesktopWeb._SCREEN_PARAM_MAP['AsOfDate'];
			_self.loadInitData(_asOfDate);
		}
		, prepareRequest:function(asOfDate){
			var requestXML = IFDS.Xml.newDocument("data");
			IFDS.Xml.addSingleNode(requestXML, "acctNum", DesktopWeb._SCREEN_PARAM_MAP['AccountNum']);			
			IFDS.Xml.addSingleNode(requestXML, "fund", DesktopWeb._SCREEN_PARAM_MAP['Fund']);
			IFDS.Xml.addSingleNode(requestXML, "class",DesktopWeb._SCREEN_PARAM_MAP['Class']);
			IFDS.Xml.addSingleNode(requestXML, "lotID",DesktopWeb._SCREEN_PARAM_MAP['lotID']);
			_asOfDate=asOfDate;
			
			IFDS.Xml.addSingleNode(requestXML, "asOfDate", asOfDate);
			
			return requestXML;
		}
		, loadInitData:function(asOfDate){
			var requestXML = _self.prepareRequest(asOfDate);
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			function responseHandler(success, responseXML)
			{
				if (success) {													
					_initDataXML = IFDS.Xml.getNode(responseXML, '//'+_initView+'Response');
								
					if(_initDataXML){				
						populateLabelText(_initDataXML);
					if(IFDS.Xml.getNode(responseXML, '//ShareLotCalcDetail'))
						addFormulaTips(IFDS.Xml.getNode(responseXML, '//ShareLotCalcDetail'));
					}
				}
			}
			
		}
		, createPDF:function(){
				
			DesktopWeb.Ajax.doBuildPDFReport(_initView, 'SharelotDetails', 'SharelotDetails', _self.prepareRequest(_asOfDate));
		}
		,loadSharelotSummary:function(){
							//DesktopWeb.Util.cancelScreen()
							var urlParams = {};
							urlParams['jobname'] = 'DisplayScreen';
							urlParams['screen'] = 'SharelotSummary';
							urlParams['envName'] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
							urlParams['ruserId'] = DesktopWeb._SCREEN_PARAM_MAP['ruserId'];
							urlParams['dateFormat'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormat'];
							urlParams['sessionId'] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
							urlParams['prevScreen'] = 'SharelotDetlSharelotDetl';
							urlParams['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];

							urlParams['AccountNum'] = DesktopWeb._SCREEN_PARAM_MAP['AccountNum'];
							urlParams['Fund'] = DesktopWeb._SCREEN_PARAM_MAP['Fund'];
							urlParams['Class'] = DesktopWeb._SCREEN_PARAM_MAP['Class'];
							urlParams['AsOfDate'] = DesktopWeb._SCREEN_PARAM_MAP['AsOfDate'];
							urlParams['ActiveOnly'] = DesktopWeb._SCREEN_PARAM_MAP['ActiveOnly'];
							urlParams['TransId'] = DesktopWeb._SCREEN_PARAM_MAP['TransId'];
							urlParams['locale'] = DesktopWeb._SCREEN_PARAM_MAP['locale'];
							urlParams['dateFormatDisplay'] = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'];
							
							DesktopWeb.Util.goToScreen('SharelotSummary', urlParams);
		}
	};
};	