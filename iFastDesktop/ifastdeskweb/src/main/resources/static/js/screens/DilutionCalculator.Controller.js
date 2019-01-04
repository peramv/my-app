/*********************************************************************************************
 * @file	DilutionCalculator.Controller.js
 * @author	
 * @desc	Controller JS file for DilutionCalculator screen
 *********************************************************************************************/

/*
 *  History : 
 *
 *  15 Nov 2013 C. Daecha P0181067 CHG0034430 T54444
 *        - Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _calcProcView = 'dtDilutionCalcProc';
	var _initView = 'dtDilutionCalcInit';
	var _calcView = 'dtDilutionCalculate';
	var _initDataXML = null;	
	
	var _fundCode = '';
	var _classCode = '';
	
	// PRIVATE METHODS ****************************************		
	function loadDropdown()
	{		
		_resources.fields['transType'].loadData(IFDS.Xml.getNode(_initDataXML, "*/List[@listName = 'TransactionTypeOptions']"));	
	}
	
	function buildCalcXML()
	{
		var dataXML = IFDS.Xml.newDocument('data');
		var selectedRecord = _resources.grids['transactions'].getSelectedRecord();
		
		var store = _resources.grids['transactions'].getStore();
		store.each(buildXML);
		
		return dataXML;

		function buildXML(item)
		{
			var mstrXML = IFDS.Xml.newDocument('dilutiontxn');
			IFDS.Xml.addSingleNode(mstrXML, 'grossAmt', item.data['tradeGrossAmt']);
			IFDS.Xml.addSingleNode(mstrXML, 'gainLoss', item.data['gainLoss']);
			IFDS.Xml.appendNode(dataXML, mstrXML);
		}		
	}
	
	function validateSearchFields()
	{
		var isValid = true;
		isValid = _resources.fields['account'].isValid() && isValid;
		isValid = _resources.fields['fund'].isValid() && isValid;
		isValid = _resources.fields['transType'].isValid() && isValid;
		isValid = _resources.fields['transNum'].isValid() && isValid;
		isValid = _resources.fields['grossAmt'].isValid() && isValid;
		isValid = _resources.fields['tradeDate'].isValid() && isValid;
		isValid = _resources.fields['calcDate'].isValid() && isValid;
		
		return isValid;
	}
	
	function sendTransactionLookup()
	{												
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'accountNum', _resources.fields['account'].getValue());
		IFDS.Xml.addSingleNode(dataXML, 'fund', _fundCode);
		IFDS.Xml.addSingleNode(dataXML, 'class', _classCode);
		IFDS.Xml.addSingleNode(dataXML, 'grossAmt', _resources.fields['grossAmt'].getValue());

		var tradeDate = _resources.fields['tradeDate'].getSMVDateString();
		IFDS.Xml.addSingleNode(dataXML, 'tradeDate', tradeDate);

		IFDS.Xml.addSingleNode(dataXML, 'transactionType', _resources.fields['transType'].getValue());

		var calcDate = _resources.fields['calcDate'].getSMVDateString();
		IFDS.Xml.addSingleNode(dataXML, 'dilutionCalcDate', calcDate);
		
		DesktopWeb.Ajax.doSmartviewAjax(_calcProcView, null, dataXML, responseHandler, _translationMap['ProcMsg_Searching']);
		
		function responseHandler(success, responseXML)
		{							
			if (success)
			{				
				_resources.grids['transactions'].appendData(responseXML);
			}
		}
	}
	
	
	// PUBLIC ITEMS *************************************
	return {				
		init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, null, responseHandler, "Searching ...");
			
			function responseHandler(success, responseXML)
			{									
				if (success)
				{
					_initDataXML = responseXML;
					loadDropdown();
				}
			}
		}
		,addTransactions: function()
		{
			if (validateSearchFields())
			{
				sendTransactionLookup();
			}
		}
		
		,updateTransactionButtons: function()
		{
			if (_resources.grids['transactions'].getAllRecords().length > 0)
			{
				_resources.grids['transactions'].enableButton('calcBtn');
				_resources.grids['transactions'].enableButton('clearAllBtn');
			}
			else
			{
				_resources.grids['transactions'].disableButton('calcBtn');
				_resources.grids['transactions'].disableButton('clearAllBtn');
			}
			
			if (_resources.grids['transactions'].getSelectedRecord())
			{
				_resources.grids['transactions'].enableButton('removeBtn');
			}
			else
			{
				_resources.grids['transactions'].disableButton('removeBtn');
			}						
		}
		
		,getElementDescription: function(code)
		{			
			return IFDS.Xml.getNodeValue(_initDataXML, '//List[@listName="TransactionTypeOptions"]/Element[code="' + code + '"]/value'); 
		}
		
		,calculateDilution: function()
		{
			DesktopWeb.Ajax.doSmartviewAjax(_calcView, null, buildCalcXML(), responseHandler, _translationMap['ProcMsg_Processing']);
			
			function responseHandler(success, responseXML)
			{								
				if (success)
				{
					_resources.fields['totalGrossAmt'].setValue(IFDS.Xml.getNodeValue (responseXML, '*/DilutionTotal/totGrossAmt'));
					_resources.fields['befDistribtion'].setValue(IFDS.Xml.getNodeValue (responseXML, '*/DilutionTotal/totGainLoss'));					
					_resources.fields['distDilution'].setValue("0.00");
					_resources.fields['distDilution'].enable();
					_resources.fields['totalDilution'].setValue("0.00");
				}
			}
		}
		
		,calcTotal: function()
		{
			var total = parseInt( (Number(_resources.fields['totalGrossAmt'].getValue())
				+ Number(_resources.fields['befDistribtion'].getValue())
				+ Number(_resources.fields['distDilution'].getValue())) * 100)/100
		
			_resources.fields['totalDilution'].setValue(total.toFixed(2));
		}
		
		,resetForm: function()
		{
			_resources.fields['account'].reset();
			_resources.fields['fund'].reset();
			_resources.fields['transType'].reset();
			_resources.fields['transNum'].reset();
			_resources.fields['grossAmt'].reset();
			_resources.fields['tradeDate'].reset();
			_resources.fields['calcDate'].reset();						
		}
		
		,clearAll: function()
		{
			_resources.grids['transactions'].clearData();
		}
		
		,remove: function()
		{
			var selectedRecords = _resources.grids['transactions'].getSelectionModel().getSelections();			
			for (var i = 0; i < selectedRecords.length; i++)
			{
				_resources.grids['transactions'].getStore().remove(selectedRecords[i]);
			}
			_self.updateTransactionButtons();
		}
		,selectFund: function(fld, rec, index)
		{
			_fundCode = rec.data['fundCode'];
			_classCode = rec.data['classCode'];
		}
	}
	
	
}	