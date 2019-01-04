/*********************************************************************************************
 * @file	AcctBalOvrd.Controller.js
 * @author	
 * @desc	Controller JS file for Account Balance Override screen
 *********************************************************************************************/
/*
 *  History : 
 *
 *  11 Nov 2013 G. Thawornwachirakun P0181067 CHG0034430 T54444
 *					- Fix display date format follows dateFormatDisplay parameter
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.  
 */
 
DesktopWeb.ScreenController = function(){	
	
	// PRIVATE VARIABLES *************************************
	var _self = null;
	var _resources = null;
	var _translationMap = DesktopWeb.Translation.getTranslationMap();
	
	var _initView = 'dtAcctBalORInit';
	var _reloadView = 'dtAcctBalORReload'
	var _processView = 'dtAcctBalORProcessing'
	
	// PRIVATE METHODS ****************************************	
	function getPopupDataMap(data)
	{
		var dataXML = IFDS.Xml.newDocument('data');
		IFDS.Xml.addSingleNode(dataXML, 'acctNum', data['acctNum']);
		IFDS.Xml.addSingleNode(dataXML, 'fundCode', data['fundCode']);
		IFDS.Xml.addSingleNode(dataXML, 'classCode', data['classCode']);
		IFDS.Xml.addSingleNode(dataXML, 'units', data['units']);
		IFDS.Xml.addSingleNode(dataXML, 'effDate', DesktopWeb.Util.getSMVDateValue(data['effDate']));
		return dataXML;
	}
	
	function getSearchDataMap(searchXML)
	{
		var xml = searchXML;
		IFDS.Xml.addSingleNode(xml, 'searchValue', _resources.fields['searchValue'].getValue());

		IFDS.Xml.addSingleNode(xml, 'searchStartDate', _resources.fields['startDate'].getSMVDateString());
		IFDS.Xml.addSingleNode(xml, 'searchEndDate', _resources.fields['endDate'].getSMVDateString());
		if(_resources.fields['fund'].getValue())
		{
			var record = _resources.fields['fund'].findRecord(_resources.fields['fund'].valueField, _resources.fields['fund'].getValue());
			IFDS.Xml.addSingleNode(xml, 'searchFundCode', record.data['fund']);
			IFDS.Xml.addSingleNode(xml, 'searchClassCode', record.data['class']);					
		}
		else
		{
			IFDS.Xml.addSingleNode(xml, 'searchFundCode', '');
			IFDS.Xml.addSingleNode(xml, 'searchClassCode', '');
		}
			
		return xml;
	}
	
	function doUpdateSmartViewCall(requestXML, action)
	{
		DesktopWeb.Ajax.doSmartviewUpdate(_processView, null, requestXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
		function responseHandler(success, responseXML)
		{	
			if (success)
			{								
				setSearchMatchDetails(responseXML);
				updateSearchFields(responseXML);
				_resources.grids['acctBalOvrd'].loadData(IFDS.Xml.getNode(responseXML, '//AccountBalances'));
				_self.closeActionPopup();								
			}			
		}
	}
	
	function setSearchMatchDetails(responseXML)
	{
		var searchMatchDetailsLbl = _resources.fields['account'];
		//_resources.fields['account'].showField();
		isValidSearchValue = false;
		var acctNumNode = IFDS.Xml.getNodeValue(responseXML, '/*//SearchMatchDetails/acctNum');		
		if ( acctNumNode )
		{						
			searchMatchDetailsLbl.setFieldLabel("AcctNum/Name:"); 
			var acctNameNode = acctNumNode+ ' - ' +IFDS.Xml.getNodeValue(responseXML, '/*//SearchMatchDetails/acctName')
			searchMatchDetailsLbl.setValue(acctNameNode);
			isValidSearchValue = true;
		}
		
		var invIDCodeNode = IFDS.Xml.getNodeValue(responseXML, "/*//SearchMatchDetails/invIDCode");
		if ( invIDCodeNode )
		{			
			searchMatchDetailsLbl.setFieldLabel("InvoiceID/Name:"); 
			var invNameNode = invIDCodeNode+ ' - ' +IFDS.Xml.getNodeValue(responseXML, '/*//SearchMatchDetails/invName')
			searchMatchDetailsLbl.setValue(invNameNode);
			isValidSearchValue = true;
		}
				
		var feeModelCodeNode = IFDS.Xml.getNodeValue(responseXML, "/*//SearchMatchDetails/feeModelCode");
		if ( feeModelCodeNode )
		{			
			searchMatchDetailsLbl.setFieldLabel("Fee ID/MFR ID:"); 
			var feeModelDescNode = feeModelCodeNode+ ' - ' +IFDS.Xml.getNodeValue(responseXML, '/*//SearchMatchDetails/feeModelDesc')
			searchMatchDetailsLbl.setValue(feeModelDescNode);
			isValidSearchValue = true;
		}
		
		var holdEntCodeNode = IFDS.Xml.getNodeValue(responseXML, "/*//SearchMatchDetails/holdEntCode");
		if ( holdEntCodeNode )
		{			
			searchMatchDetailsLbl.setFieldLabel("Holding Entity Code/Name:"); 
			var holdEntNameNode = holdEntCodeNode+ ' - ' +IFDS.Xml.getNodeValue(responseXML, '/*//SearchMatchDetails/holdEntName')
			searchMatchDetailsLbl.setValue(holdEntNameNode);
			isValidSearchValue = true;
		}

		if(isValidSearchValue)	{
			_resources.fields['account'].showField();
		}
		
	}

	function updateSearchFields(responseXML)
	{
		var searchValueNode = IFDS.Xml.getNodeValue(responseXML, '/*//SearchValues/searchValue');
		if (searchValueNode)
		{ 
			_resources.fields['searchValue'].setValue(searchValueNode);                
		}
		
		var fundSearchValueNode = IFDS.Xml.getNodeValue(responseXML, '/*//SearchValues/fundSearchValue');
		if (fundSearchValueNode)
		{				
			_self.fundSearch(fundSearchValueNode, true);
			_resources.grids['acctBalOvrd'].clearData();
			_self.updateActionButtons();
		}
			   
		var searchStartDateNode = IFDS.Xml.getNodeValue(responseXML, '/*//SearchValues/searchStartDate');
		if (searchStartDateNode)
		{
			_resources.fields['startDate'].setValue(DesktopWeb.Util.getDateDisplayValue(searchStartDateNode));
		}
	  
		var searchEndDateNode = IFDS.Xml.getNodeValue(responseXML, '/*//SearchValues/searchEndDate');
		if (searchEndDateNode)
		{
			_resources.fields['endDate'].setValue(DesktopWeb.Util.getDateDisplayValue(searchEndDateNode)); 
		}
	}
		
	// PUBLIC ITEMS *************************************
	return {
		ADD: 'add'
		,MOD: 'modify'
		,DEL: 'delete'	
		
		,updatesFlag: false		
			
		,init: function(res)
		{				
			_resources = res;
			_self = DesktopWeb._SCREEN_CONTROLLER;									
			
			DesktopWeb.Ajax.doSmartviewAjax(_initView, null, null, responseHandler, _translationMap['ProcMsg_Loading']); 		
						
			function responseHandler(success, responseXML)
			{							
				if (success)
				{
					_resources.fields['account'].hideField();
					_self.updateActionButtons();
				}
			}
		}
		
		,updateActionButtons: function()
		{			
			var selectedRecord = _resources.grids['acctBalOvrd'].getSelectedRecord();	
			
			if (selectedRecord)
			{					
				_resources.grids['acctBalOvrd'].enableButton('addBtn');
				if(selectedRecord.data.UpdAllowed.toLowerCase() != "yes"){					
					_resources.grids['acctBalOvrd'].disableButton('modBtn');						
				}	
				else{					
					_resources.grids['acctBalOvrd'].enableButton('modBtn');						
				}	
				_resources.grids['acctBalOvrd'].enableButton('delBtn');												
			}
			else
			{				
				_resources.grids['acctBalOvrd'].enableButton('addBtn');
				_resources.grids['acctBalOvrd'].disableButton('modBtn');
				_resources.grids['acctBalOvrd'].disableButton('delBtn');
			}		
		}	
		
		,openActionPopup: function(action)
		{
			if (action == this.ADD)
			{
				_resources.grids['acctBalOvrd'].clearSelectedRecord();
			}
			_resources.popups['acctBalOvrdPopup'].init(action);
			_resources.popups['acctBalOvrdPopup'].show();
		}
		
		,closeActionPopup: function()
		{
			_resources.popups['acctBalOvrdPopup'].clearAllFields();
			_resources.popups['acctBalOvrdPopup'].hide();						
		}
		
		,savePopup: function(action, data)
		{			
			if (action == this.ADD)
			{				
				var addXML = getPopupDataMap(data);
				addXML = getSearchDataMap(addXML);
				IFDS.Xml.addSingleNode(addXML, 'action', 'add');
				IFDS.Xml.addSingleNode(addXML, 'version', '');
				doUpdateSmartViewCall(addXML, action);
			}
			else if(action == this.MOD)
			{
				var modifyXML = getPopupDataMap(data);
				modifyXML = getSearchDataMap(modifyXML);
				IFDS.Xml.addSingleNode(modifyXML, 'action', 'modify');
				var rec = _resources.grids['acctBalOvrd'].getSelectedRecord();
				IFDS.Xml.addSingleNode(modifyXML, 'version', rec.data.version);
				
				doUpdateSmartViewCall(modifyXML, action);
				
			}
			else if (action == this.DEL)
			{
				var deleteXML = getPopupDataMap(data);
				modifyXML = getSearchDataMap(deleteXML);
				IFDS.Xml.addSingleNode(deleteXML, 'action', 'delete');
				var rec = _resources.grids['acctBalOvrd'].getSelectedRecord();
				IFDS.Xml.addSingleNode(modifyXML, 'version', rec.data.version);
				
				doUpdateSmartViewCall(deleteXML, action);
				
				_resources.grids['acctBalOvrd'].removeSelectedRecord();												
			}
			_self.updateActionButtons();	
			this.updatesFlag = true;															
		}
		
		,searchAcctBalOvrd: function(ReloadXML, action)
		{									
			var ReloadXML = IFDS.Xml.newDocument('data');
			ReloadXML = getSearchDataMap(ReloadXML);
			_resources.grids['acctBalOvrd'].clearData();
			DesktopWeb.Ajax.doSmartviewAjax(_reloadView, null, ReloadXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{					
				if (success)
				{										
					setSearchMatchDetails(responseXML);
					_resources.grids['acctBalOvrd'].loadData(IFDS.Xml.getNode(responseXML, '//AccountBalances'));
				}
				setSearchMatchDetails(responseXML);
				_self.updateActionButtons();					
			}
		}
		
		,fundSearch: function(fundSearchValue, gridFundSearch)
		{		
			var fundXML = IFDS.Xml.newDocument('data');
			IFDS.Xml.addSingleNode(fundXML, 'fundSponsor', '');
			IFDS.Xml.addSingleNode(fundXML, 'searchValue', fundSearchValue);
			IFDS.Xml.addSingleNode(fundXML, 'maxRecords', 11);
			IFDS.Xml.addSingleNode(fundXML, 'showAllClassRecords', 'no');
				
			DesktopWeb.Ajax.doSmartviewAjax('fundSearch', null, fundXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{					
				if (success)
				{
					if(gridFundSearch)
					{
						_resources.fields['fund'].getStore().loadData(IFDS.Xml.getNode(responseXML, '/*//PossibleMatches'));
						_resources.fields['fund'].setValue(IFDS.Xml.getNodeValue(responseXML, '/*//displayValue'));
					}
					else
					{
						_resources.popups['acctBalOvrdPopup'].getField('fundFld').getStore().loadData(IFDS.Xml.getNode(responseXML, '/*//PossibleMatches'));
						_resources.popups['acctBalOvrdPopup'].getField('fundFld').setValue(IFDS.Xml.getNodeValue(responseXML, '/*//displayValue'));
					}					
				}			
			}				
		}
		
		,accountSearch: function(accountSearchValue)
		{
			var accountXML = IFDS.Xml.newDocument('data');			
			IFDS.Xml.addSingleNode(accountXML, 'searchValue', accountSearchValue);
			IFDS.Xml.addSingleNode(accountXML, 'startRecordNum', '');
			IFDS.Xml.addSingleNode(accountXML, 'maxRecords', 14);			
				
			DesktopWeb.Ajax.doSmartviewAjax('AccountSearch', null, accountXML, responseHandler, _translationMap['ProcMsg_Loading']);
			
			function responseHandler(success, responseXML)
			{					
				if (success)
				{
					_resources.popups['acctBalOvrdPopup'].getField('accountFld').getStore().loadData(IFDS.Xml.getNode(responseXML, '/*//PossibleMatches'));
					_resources.popups['acctBalOvrdPopup'].getField('accountFld').setValue(IFDS.Xml.getNodeValue(responseXML, '/*//displayValue'));
				}			
			}
		}
		
		,alertSearchOptions: function()
		{
			var msgString = "<b>Search by one of:</b><br/>";
			msgString += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Holding Entity Code<br/>";
			msgString += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Account Number<br/>";
			msgString += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Invoice ID<br/>";
			msgString += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- MFR ID<br/>";
			msgString += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- MF ID";						
			return msgString;	
		}

		,alertAccountSuggestOptions: function()
		{
			var msgStr = "<b>Search by one of:</b><br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Account Number <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Partial Last Name <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Partial Last Name <space> Parital First Name <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Broker Account Number <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Broker Code <space> Broker Account Number <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- SIN (no spaces or hyphens) <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Any Owner Identifier Number <br/>";			
			return msgStr;			
		}

		,alertFundSuggestOptions: function()
		{
			var msgStr = "<b>Search by one of: </b><br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Fund Number <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Fund Code <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Fund Code <space> Class Code <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Fund Name <br/>";
			msgStr += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Any Fund Identifier <br/>";    			
			return msgStr;	
		}
		
		,accountSuggestOptionQuickTip: function()
		{
			Ext.QuickTips.unregister(_resources.popups['acctBalOvrdPopup'].getField('accountFld').id);
			Ext.QuickTips.register({
				target: _resources.popups['acctBalOvrdPopup'].getField('accountFld').id
				,width: 225
				,showDelay: 0
				,dismissDelay: 0
				,text: _self.alertAccountSuggestOptions()
			})
		}
		,fundSuggestOptionQuickTip: function()
		{
			Ext.QuickTips.unregister(_resources.popups['acctBalOvrdPopup'].getField('fundFld').id);
			Ext.QuickTips.register({
				target: _resources.popups['acctBalOvrdPopup'].getField('fundFld').id
				,width: 175
				,showDelay: 0
				,dismissDelay: 0				
				,text: _self.alertFundSuggestOptions()
			})
		}
		,accountSuggestDetails: function(action)
		{
			var record = _resources.popups['acctBalOvrdPopup'].getField('accountFld').findRecord(_resources.popups['acctBalOvrdPopup'].getField('accountFld').valueField, _resources.popups['acctBalOvrdPopup'].getField('accountFld').getValue());			
			if(record != undefined){
				Ext.QuickTips.unregister(_resources.popups['acctBalOvrdPopup'].getField('accountFld').id);
				if(action == this.ADD){
					 Ext.QuickTips.register({
						target: _resources.popups['acctBalOvrdPopup'].getField('accountFld').id						
						,width: 475
						,getTargetXY: function(){
							return [0,0];
						}						
						,dismissDelay: 0						
						,text: '<div class="DetailsSection">'
							+'<table>'
								+'<tr>'
									+'<td><b>AcctNum:</b></td>'
									+'<td>'+record.data.acctNum+'</td>'
									+'<td><b>BrokerAcct:</b></td>'
									+'<td>'+record.data.brkAcct+'</td>'
								+'</tr>'
								+'<tr>'
									+'<td><b>Broker:</b></td>'
									+'<td>'+record.data.broker+'</td>'
									+'<td>'+record.data.brokerName+'</td>'
								+'</tr>'
								+'<tr>'
									+'<td><b>Branch:</b></td>'
									+'<td>'+record.data.branch+'</td>'
									+'<td>'+record.data.brnName+'</td>'
								+'</tr>'
								+'<tr>'
									+'<td><b>SalesRep:</b></td>'
									+'<td>'+record.data.salesRep+'</td>'
									+'<td>'+record.data.slsrepName+'</td>'
								+'</tr>'
								+'<tr>'
									+'<td><b>Address:</b></td>'
									+'<td>'+record.data.addr1+record.data.addr2+record.data.addr3+record.data.addr4+record.data.addr5+'</td>'
								+'</tr>'
							+'</table>'
						+'</div>'							
					})
				}
			}		
		}
	}
}	