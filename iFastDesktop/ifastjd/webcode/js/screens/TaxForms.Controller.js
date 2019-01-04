/*********************************************************************************************
 * @file	TaxForms.Controller.js
 * @author 	Narin Suanlamyai
 * @desc	Controller JS file for Tax Forms scree
 *********************************************************************************************/
/*
 * Procedure: TaxForms.Controller.js
 *
 * Purpose  : Controller of Tax Forms screen
 *             
 * Notes    : Open screens by COA -> Attributes Box -> Tax Forms
 *
 * History  : 
 *      12 Sep 2014 Narin Suanlamyai P0222874 - eDocs on iFastDesktop. 
 *                  - Created
 *                                    
 *      31 Oct 2014 Narin Suanlamyai P0222874 DFT0043504 T55930. 
 *                  - Send interface name to smartview to override error message. 
 *                                    
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;	
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _ADD = 'add';
	var _MOD = 'mod';
	var _DEL = 'del';
	var _INQ = 'inq';

	var _requestRecNum = 25;
	var _nextStartRecNum = null;
	var _initXML = null;
	var _pdfInfoXML = null;

	var _permissionsMap = {};

	var _lastSearchCriteria = {};

	var _dtTaxFormInquiryService = "dtTaxFormInq";
	
	// PRIVATE METHODS ****************************************	
	/** Store user permission **/
	function storePermissions(initViewXML)
	{
		_permissionsMap[_self.INQ] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/inq').toLowerCase() == 'yes';
		_permissionsMap[_self.ADD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/add').toLowerCase() == 'yes';
		_permissionsMap[_self.MOD] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/mod').toLowerCase() == 'yes';	
		_permissionsMap[_self.DEL] = IFDS.Xml.getNodeValue(initViewXML, '//Permissions/del').toLowerCase() == 'yes';
	}
	
	function populateDropdownList(initViewXML)
	{
		_resources.fields['taxYear'].loadData(IFDS.Xml.getNode(initViewXML, "//List[@listName = 'TaxYear']"));
	}	
	
	function loadDefaultSearchCriteria()
	{
		var desiredYear = IFDS.Xml.getNodeValue(_initXML, "//ListSelection[@id='TaxYear']");
		if (desiredYear && desiredYear.length > 0)
		{
			_resources.fields['taxYear'].setValue(desiredYear);
			_lastSearchCriteria['taxYear'] = desiredYear;
		}
	}
	
	function doSearch(runMode, append)
	{
		var paramXML = IFDS.Xml.newDocument('data');

		if (_lastSearchCriteria['taxYear'] && _lastSearchCriteria['taxYear'].length > 0) IFDS.Xml.addSingleNode(paramXML, 'taxYear', _lastSearchCriteria['taxYear']);
		IFDS.Xml.addSingleNode(paramXML, 'acct', DesktopWeb._SCREEN_PARAM_MAP['AccountNum'] );
		IFDS.Xml.addSingleNode(paramXML, 'runMode', runMode);
		IFDS.Xml.addSingleNode(paramXML, 'startRecNum', (append)?_nextStartRecNum:'1');
		IFDS.Xml.addSingleNode(paramXML, 'requestRecNum', _requestRecNum);
		
		DesktopWeb.Ajax.doSmartviewAjax(_dtTaxFormInquiryService
							, (runMode == 'init' ? {ignoreErrorCode: '15'} : null)
							, paramXML
							, responseHandler
							, _translationMap['ProcMsg_Searching']);

		function responseHandler(success, responseXML)
		{			
			if (success)
			{
				if (runMode == 'init')
				{ 
					storePermissions(responseXML);
					populateDropdownList(responseXML);
					if (_permissionsMap[_INQ])
					{
						_initXML = IFDS.Xml.cloneDocument(responseXML);
						loadDefaultSearchCriteria();
						loadTaxFormList(responseXML, append);
					}else{
						disableScreen();
					}
				}else{
					loadTaxFormList(responseXML, append);
				}
			}else{
				if (runMode == 'init')
				{
					disableScreen();
				}
			}
		}
	}
	
	function selectTaxFormByTaxPComRid(txPComRid)
	{
		if (txPComRid)
		{
			var store = _resources.grids['taxForms'].getStore();
			if ( store.getTotalCount() > 0 )
			{
				var selectIndex = store.findExact('txPComRid', txPComRid);
				if (selectIndex >= 0)
				{
					_resources.grids['taxForms'].setSelectedRecord(selectIndex);
				}else{
					_resources.grids['taxForms'].selectFirstRecord();
				}
			}
		}else{
			_resources.grids['taxForms'].selectFirstRecord();
		}
	}
	
	function loadTaxFormList(responseXML, append)
	{
		var taxFormsListXML = IFDS.Xml.getNode(responseXML, "//TaxFormsList")
		if (taxFormsListXML)
		{
			_resources.grids['taxForms'].loadData(taxFormsListXML, append);
			selectTaxFormByTaxPComRid(DesktopWeb._SCREEN_PARAM_MAP['txPComRid']);
			
			// Looking for more records
			var moreRecNode = IFDS.Xml.getNode(responseXML, "//moreRecordsExist");
			if (moreRecNode)
			{
				var moreRec = IFDS.Xml.getNodeValue(moreRecNode, ".");
				if(moreRec == 'yes')
				{
					_nextStartRecNum = IFDS.Xml.getNodeValue(IFDS.Xml.getNode(responseXML, "//rangeStartForNext"), ".");
					_resources.grids['taxForms'].enableButton('moreBtn');
				}else{
					_nextStartRecNum = null;
					_resources.grids['taxForms'].disableButton('moreBtn');
				}
			}
		}
	}
	
	function disableScreen()
	{
		_resources.fields['taxYear'].disable();
		_resources.buttons['searchBtn'].disable();
		_resources.grids['taxForms'].disableAllButtons();	
	}

	function validateSearchCriteria()
	{
		return _resources.fields['taxYear'].isValid();
	}

	function clearGrid(name)
	{
		_resources.grids[name].getStore().removeAll();
		_resources.grids[name].disableAllButtons();
	}
	
	// PUBLIC ITEMS *************************************
	return {				
		ADD: _ADD
		,MOD: _MOD
		,DEL: _DEL
		,INQ: _INQ
		
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			DesktopWeb._SCREEN_PARAM_MAP['interfaceName'] = 'ifds.dt.Account.TaxForms';
			
			var taxYear = DesktopWeb._SCREEN_PARAM_MAP['taxYear'];
			
			if (taxYear && taxYear.length > 0)
			{
				_lastSearchCriteria['taxYear'] = taxYear;
			}
			
			doSearch('init', false);
		}

		,selectTaxForm: function(record)
		{
			_resources.grids['taxForms'].enableButton('pdfBtn');
		}
		
		,clickHandle_searchBtn: function()
		{
			if (validateSearchCriteria()){
				clearGrid('taxForms');
				_nextStartRecNum = 1;
				_lastSearchCriteria['taxYear'] = _resources.fields['taxYear'].getValue();
				doSearch('reload', false);
			}
		}

		,clickHandle_pdfBtn: function(form)
		{
			var selectedTaxForm = _resources.grids['taxForms'].getSelectedRecord();
			DesktopWeb.Ajax.doBuildSmartPDF('TaxForm', {taxYear: _lastSearchCriteria['taxYear']
														,txPComRid: selectedTaxForm.data['txPComRid']
														,formType: 	selectedTaxForm.data['formType']
														,formLink: 	selectedTaxForm.data['formLink']
														,isManual:  selectedTaxForm.data['isManual']
														,AccountNum:	DesktopWeb._SCREEN_PARAM_MAP['AccountNum']
														,srcScreen: 'TaxForms'
														});
		}

		,clickHandle_moreBtn: function()
		{
			doSearch('reload', true);
		}
	}	
}	