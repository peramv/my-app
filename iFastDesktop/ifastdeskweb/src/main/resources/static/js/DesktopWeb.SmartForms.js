/*********************************************************************************************
 * @file	DesktopWeb.Main.js
 * @author	Rod Walker 
 * @desc	Main javascript file for DesktopWeb screen, builds wrapper then 
 * 			initializes and loads screen specific code
 *********************************************************************************************/

// required by ExtJS library for screen to render correctly
Ext.BLANK_IMAGE_URL = DesktopWeb._SRC_PATH + 'extjs/resources/images/gray/s.gif';

var SmartFormsApp = new (Ext.extend(Ext.util.Observable, {
	constructor: function()
	{
		this.addEvents({
			'init' : true			
			,'run' : true
		});
		Ext.util.Observable.constructor.call(this);
	}
}))();

SmartFormsApp.FormName = null;
SmartFormsApp.DataStore = null;
SmartFormsApp.API = null;
SmartFormsApp.ToolBar =  null;
SmartFormsApp.PageNavigator = null;
SmartFormsApp.ContentViewer = null;
SmartFormsApp.Footer = null;
SmartFormsApp.AccountLookup = null;

SmartFormsApp.load = function(api, form, source, formLayout, altFormList)
{
	Ext.QuickTips.init();
	
	SmartFormsApp.FormName = (form != null ? form.name : null);
	SmartFormsApp.API = api;	
	SmartFormsApp.DataStore = new FormDataStore(api);
	
	var formTitlebar = new FormTitlebar({formDetails: form, sourceDetails: source, altFormList: altFormList});
	
	SmartFormsApp.ContentViewer = new ContentViewer({form: form, formLayout: formLayout, source: source});
		
	SmartFormsApp.Toolbar = new FormToolbar({showAWDTools: source != null});
		
	SmartFormsApp.Footer = new Footer();
	
	SmartFormsApp.AccountLookup = new AccountLookup();		
	
	SmartFormsApp.PageNavigator = new PageNavigator({form:form, source:source});
	SmartFormsApp.PageNavigator.on('pageselected', 
									function(pageInfo){
										if(pageInfo.pageIndex != null)
										{
											SmartFormsApp.ContentViewer.showPage(pageInfo.pageType, pageInfo.pageIndex)
										}
									});
		
	SmartFormsApp.Viewport = new Ext.Viewport(
		{
			layout: 'border'					
			,items: [
				new Ext.Container(
					{
						region: 'north'
						,border:false
						,height:0						
						,items: [
							formTitlebar
							,SmartFormsApp.Toolbar
						]
					}
				) 
				,SmartFormsApp.PageNavigator 				
				,SmartFormsApp.ContentViewer
				,SmartFormsApp.Footer
			]		
		}
	);
	
	SmartFormsApp.init();
};


SmartFormsApp.init = function()
{	
	SmartFormsApp.fireEvent('init');
	var requestXML = IFDS.Xml.stringToXML("<data><gnInit/></data>");
	var gnInitNode = IFDS.Xml.getNode(requestXML, 'gnInit');
	
	var listNode = IFDS.Xml.addSingleNode(gnInitNode, "List");
	IFDS.Xml.addSingleNode(listNode, 'levelIDType', 'A');
	IFDS.Xml.addSingleNode(listNode, 'levelIDValue', 'gnAcctSetup');
	
	if (SmartFormsApp.API.gnOrderRequest)
	{
		listNode = IFDS.Xml.addSingleNode(gnInitNode, "List");
		IFDS.Xml.addSingleNode(listNode, 'levelIDType', 'A');
		IFDS.Xml.addSingleNode(listNode, 'levelIDValue', 'gnOrder');					
	}
	
	if (SmartFormsApp.API.gnPACSWPRequest)
	{
		listNode = IFDS.Xml.addSingleNode(gnInitNode, "List");
		IFDS.Xml.addSingleNode(listNode, 'levelIDType', 'A');
		IFDS.Xml.addSingleNode(listNode, 'levelIDValue', 'gnPACSWP');					
	}
	
	if (SmartFormsApp.API.gnCotSetupRequest)
	{
		listNode = IFDS.Xml.addSingleNode(gnInitNode, "List");
		IFDS.Xml.addSingleNode(listNode, 'levelIDType', 'A');
		IFDS.Xml.addSingleNode(listNode, 'levelIDValue', 'gnCotSetup');					
	}
	
	if (SmartFormsApp.API.gnLIFRRIFRequest)
	{
		listNode = IFDS.Xml.addSingleNode(gnInitNode, "List");
		IFDS.Xml.addSingleNode(listNode, 'levelIDType', 'A');
		IFDS.Xml.addSingleNode(listNode, 'levelIDValue', 'gnLIFRRIF');					
	}
	
	if (SmartFormsApp.API.gnATRRequest)
	{
		listNode = IFDS.Xml.addSingleNode(gnInitNode, "List");
		IFDS.Xml.addSingleNode(listNode, 'levelIDType', 'A');
		IFDS.Xml.addSingleNode(listNode, 'levelIDValue', 'gnATR');					
	}
	
	if (SmartFormsApp.API.gnDividendRequest)
	{
		listNode = IFDS.Xml.addSingleNode(gnInitNode, "List");
		IFDS.Xml.addSingleNode(listNode, 'levelIDType', 'A');
		IFDS.Xml.addSingleNode(listNode, 'levelIDValue', 'gnDividend');					
	}
	
	DesktopWeb.Ajax.doAPIAjax("gnInit", {serviceType: "INQUIRY", dataMode: 'inquire'}, requestXML, initCallback, 'Loading ...');
	
	function initCallback(responseXML)
	{
		if (IFDS.Xml.getNode(responseXML, '/APIResponse/Error') == null)
		{			
			DesktopWeb._SCREEN_PARAM_MAP['sessionId'] = IFDS.Xml.getNodeValue(responseXML, "/APIResponse/sessionId");
					
			var initResponse = new APIResponse('gnInit', IFDS.Xml.getNode(responseXML, "/*/gnInitResponse"));		
			if (initResponse.getStatus() == 'Accepted')
			{			
				SmartFormsApp.initViewXML = responseXML;				
				SmartFormsApp.run();							
			}
			else
			{
				Notifications.error(initResponse.getErrors());
			}			
		}
		else
		{
			DesktopWeb.Util.displayError(IFDS.Xml.getNodeValue(responseXML, '/APIResponse/Error/text'));
		}
		
			
	}	
}

SmartFormsApp.run = function()
{	
	if (SmartFormsApp.ContentViewer.getSourcePageCount() != null 
		&& SmartFormsApp.ContentViewer.getFormPageCount() != null)
	{
		if (SmartFormsApp.ContentViewer.getSourcePageCount() < SmartFormsApp.ContentViewer.getFormPageCount())
		{
			Notifications.warning(Notifications.buildMissingSourcePageDisplay(), done);
		}
		else if (SmartFormsApp.ContentViewer.getSourcePageCount() > SmartFormsApp.ContentViewer.getFormPageCount())
		{
			Notifications.info(Notifications.buildExtraSourcePageDisplay(), done);	
		}	
		else
		{
			done();
		}  
	}
	else
	{
		done();
	}
	
	function done()
	{
		if (SmartFormsApp.ContentViewer.getFormPageCount() != null)
		{
			SmartFormsApp.PageNavigator.setSelectedPage('form', 0);			
		}			
	}
	
	SmartFormsApp.fireEvent('run');	
}

SmartFormsApp.validate = function()
{	
	try
	{	
		eval(SmartFormsApp.FormName + ".onBeforeValidation()");	
	}
	catch(e){throw e}
	
	
	var isValid = true;
	var dataErrors = SmartFormsApp.DataStore.validate();
	
	var formErrors = [];
	try
	{	
		formErrors = eval(SmartFormsApp.FormName + ".validateForm()");	
	}
	catch(e){throw e}	
		
	var errors = dataErrors.concat(formErrors);	
	if (errors.length > 0)
	{
		Notifications.error(Notifications.buildFailedValidationDisplay(errors));		
		isValid = false;
	}
	
	return isValid;		
}

SmartFormsApp.submit = function()
{	
	DesktopWeb.Ajax.doAPIAjax("gnPackage", {serviceType: "APIUPDATE", dataMode: "create"}, SmartFormsApp.DataStore.buildXML(), submitCallback, 'Processing ...');	
	
	function submitCallback(responseXML)
	{		
		if (IFDS.Xml.getNode(responseXML, '/APIResponse/Error') == null)		
		{
			DesktopWeb._SCREEN_PARAM_MAP['sessionId'] = IFDS.Xml.getNodeValue(responseXML, "/APIResponse/sessionId");
			
			var packageResponse = new PackageResponse(responseXML);				
			if (packageResponse.getStatus() == 'Accepted')
			{
				var acctSetupResponse = new AcctSetupResponse(packageResponse.getAPINode('gnAcctSetup'));
				
				// account setup failed									
				if (acctSetupResponse.getStatus().indexOf('Accepted') == -1)
				{
					Notifications.error(Notifications.buildErrorsDisplay(acctSetupResponse.getErrors()));					
											SmartFormsApp.Footer.setMode('resubmit_cancel');					
				}
				// account set up successful
				else
				{	
					SmartFormsApp.ContentViewer.disableControlsForAPI('gnAcctSetup');
					SmartFormsApp.DataStore.setAPINodeReadOnly('gnAcctSetup');							
														
					SmartFormsApp.newAccount = {
						acctNum: acctSetupResponse.getAccountNum()
						,shrNum: acctSetupResponse.getShareholderNum()
					};
					
					var accountSetupMsg = "";					
					if (acctSetupResponse.getStatus() == 'Accepted')
					{
						accountSetupMsg += Notifications.buildAccoutSetupDisplay(SmartFormsApp.newAccount.acctNum, SmartFormsApp.newAccount.shrNum);											
					}
					else if (acctSetupResponse.getStatus() == 'Accepted with warnings')
					{	
						accountSetupMsg += Notifications.buildAccoutSetupWithWarningsDisplay(SmartFormsApp.newAccount.acctNum, 
												SmartFormsApp.newAccount.shrNum, acctSetupResponse.getWarnings());																		
					}
					 					
					var secondaryAPIResponses = {};					
					for (var i in SmartFormsApp.API)
					{						
						if (i != 'gnAcctSetupRequest' && i != 'apiTemp')
						{
							var apiName = i.slice(0, i.length - 7); //trim off the 'Request'
							var nodes = packageResponse.getAPINodes(apiName);							
							
							secondaryAPIResponses[apiName] = [];
							for (var n = 0; n < nodes.length; n++)																		
							{
								secondaryAPIResponses[apiName].push(new APIResponse(apiName, nodes[n], SmartFormsApp.API[i].description));
							}																				
						}
					}					
					SmartFormsApp.DataStore.setAccountNumberInSecondaryAPIs(SmartFormsApp.newAccount.acctNum);					
					
					var errorDetails = "";
					var errorDetailsCount = 0;
					var warningDetails = "";
					var warningDetailsCount = 0;
					for (var apiName in secondaryAPIResponses)
					{											
						for (var n = 0; n < secondaryAPIResponses[apiName].length; n++)
						{
							// secondary api failed	- "reject" status										
							if (secondaryAPIResponses[apiName][n].getStatus().indexOf('Accepted') == -1)
							{						
								errorDetailsCount++;	
								errorDetails += Notifications.buildSecondryAPIErrorsDisplay(errorDetailsCount, secondaryAPIResponses[apiName][n].description, 
												secondaryAPIResponses[apiName][n].getErrors(), secondaryAPIResponses[apiName][n].getWarnings());							
							}
							else if ( secondaryAPIResponses[apiName][n].getStatus() == 'Accepted with warnings' )
							{
								warningDetailsCount++;	
								warningDetails += Notifications.buildSecondryAPIWarningsDisplay(warningDetailsCount, secondaryAPIResponses[apiName][n].description, 
												secondaryAPIResponses[apiName][n].getWarnings());	
								
								SmartFormsApp.ContentViewer.disableControlsForAPI(apiName, n);
								SmartFormsApp.DataStore.setAPINodeReadOnly(apiName, n);		
							}
							else
							{
								SmartFormsApp.ContentViewer.disableControlsForAPI(apiName, n);
								SmartFormsApp.DataStore.setAPINodeReadOnly(apiName, n);																								
							}
						}
					}
											
					if (errorDetailsCount > 0)
					{
						if (warningDetailsCount > 0)
						{
							errorDetails += Notifications.buildSecondaryAPIWarningDisplay(warningDetails);
						} 
						Notifications.info(accountSetupMsg, function(){
							Notifications.error(Notifications.buildSecondaryAPIErrorDisplay(errorDetails));
						});
						SmartFormsApp.Footer.setMode('resubmit_done');
					}
					else if ( warningDetailsCount > 0)
					{
						Notifications.info(accountSetupMsg, function(){
							Notifications.warning(Notifications.buildSecondaryAPIWarningDisplay(warningDetails), SmartFormsApp.goToDSKConfirm);
						});
					}
					else
					{
						Notifications.info(accountSetupMsg, SmartFormsApp.goToDSKConfirm);
					}
				}				
			}
			else
			{
				Notifications.error(Notifications.buildErrorsDisplay(packageResponse.getErrors()));				
				SmartFormsApp.Footer.setMode('resubmit_cancel');
			}
		}
		else
		{
			Notifications.error(IFDS.Xml.getNodeValue(responseXML, '/APIResponse/Error/text'));					
		}
	}
}

SmartFormsApp.resubmit = function()
{	
	DesktopWeb.Ajax.doAPIAjax("gnPackage", {serviceType: "APIUPDATE", dataMode: "create"}, SmartFormsApp.DataStore.buildXML(), resubmitCallback, 'Processing ...');
	
	function resubmitCallback(responseXML)
	{
		if (IFDS.Xml.getNode(responseXML, '/APIResponse/Error') == null)		
		{
			DesktopWeb._SCREEN_PARAM_MAP['sessionId'] = IFDS.Xml.getNodeValue(responseXML, "/APIResponse/sessionId");
			
			var packageResponse = new PackageResponse(responseXML);				
			if (packageResponse.getStatus() == 'Accepted')
			{
				var secondaryAPIResponses = {};					
				for (var i in SmartFormsApp.API)
				{						
					if (i != 'gnAcctSetupRequest' && i != 'apiTemp')
					{
						var apiName = i.slice(0, i.length - 7); //trim off the 'Request'																			
						var nodes = packageResponse.getAPINodes(apiName);														
						
						secondaryAPIResponses[apiName] = [];
						for (var n = 0; n < nodes.length; n++)																		
						{
							secondaryAPIResponses[apiName].push(new APIResponse(apiName, nodes[n], SmartFormsApp.API[i].description));
						}																				
					}
				}				
				
				var errorDetails = "";
				var errorDetailsCount = 0;
				var warningDetails = "";
				var warningDetailsCount = 0;
				for (var apiName in secondaryAPIResponses)
				{											
					for (var n = 0; n < secondaryAPIResponses[apiName].length; n++)
					{
						// secondary api failed											
						if (secondaryAPIResponses[apiName][n].getStatus().indexOf('Accepted') == -1)
						{						
							errorDetailsCount++;	
							errorDetails += Notifications.buildSecondryAPIErrorsDisplay(errorDetailsCount, secondaryAPIResponses[apiName][n].description, 
											secondaryAPIResponses[apiName][n].getErrors(), secondaryAPIResponses[apiName][n].getWarnings());	
						}
						else if ( secondaryAPIResponses[apiName][n].getStatus() == 'Accepted with warnings' )
						{
							warningDetailsCount++;	
							warningDetails += Notifications.buildSecondryAPIWarningsDisplay(warningDetailsCount, secondaryAPIResponses[apiName][n].description, 
											secondaryAPIResponses[apiName][n].getWarnings());	
							
							SmartFormsApp.ContentViewer.disableControlsForAPI(apiName, n);
							SmartFormsApp.DataStore.setAPINodeReadOnly(apiName, n);	
						}
						else
						{
							SmartFormsApp.ContentViewer.disableControlsForAPI(apiName, n);
							SmartFormsApp.DataStore.setAPINodeReadOnly(apiName, n);																								
						}
					}
				}
										
				if (errorDetailsCount > 0)
				{
					if (warningDetailsCount > 0)
					{
						errorDetails += Notifications.buildSecondaryAPIWarningDisplay(warningDetails);
					} 
					Notifications.error(Notifications.buildSecondaryAPIErrorDisplay(errorDetails));
					SmartFormsApp.Footer.setMode('resubmit_done');
				}
				else if (warningDetailsCount > 0)
				{
					Notifications.warning(Notifications.buildSecondaryAPIWarningDisplay(warningDetails), function(){
						Notifications.info(Notifications.buildResubmitSuccessDisplay(), SmartFormsApp.goToDSKConfirm);
					});
				}
				else
				{
					Notifications.info(Notifications.buildResubmitSuccessDisplay(), SmartFormsApp.goToDSKConfirm);				
				}				
			}
			else
			{
				Notifications.error(Notifications.buildErrorsDisplay(packageResponse.getErrors()));								
			}
		}
		else
		{
			Notifications.error(IFDS.Xml.getNodeValue(responseXML, '/APIResponse/Error/text'));					
		}
	}
}

SmartFormsApp.done = function()
{
	Notifications.prompt(Notifications.buildDoneWarningDisplay(), callbackFn);
	var self = this;
	function callbackFn(buttonId)
	{
		if (buttonId == 'ok')
		{
			SmartFormsApp.goToDSKConfirm();
		}
	}
}


// code below required for call from Desktop to load the confirmation dialog - VERY CONFUSING!
var _updateStatus = false
SmartFormsApp.goToDSKConfirm = function()
{		
	DesktopWeb._SCREEN_CONTROLLER = {
		updatesFlag: true
		,doUpdate: function(){return DesktopWeb._SUCCESS}
		,updateStatus: true		
	};
		
	document.getElementById('btnConfirmDlg').click();
}

function getNewAccountNum()
{	
  	return SmartFormsApp.newAccount.acctNum;
}

function getNewShrNum()
{
  	return SmartFormsApp.newAccount.shrNum;
}