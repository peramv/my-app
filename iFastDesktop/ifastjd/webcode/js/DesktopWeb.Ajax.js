/*********************************************************************************************
 * @file	DesktopWeb.Ajax.js
 * @author 	Rod Walker 
 * @desc	Contains methods for doing Ajax calls within DesktopWeb   
 * @history
 * 	31 Jul 2014 Narin Suanlamyai P0220132 FN03 DFT0037461 T55508
 *			- Add fixASCIICodeDisplay function to convert undisplayable characters to displayable characters.
 *			- Call fixASCIICodeDisplay in reponseHandler of doSynchServiceCall function
 *
 *  17 Nov 2014 Narin Suanlamyai P0222874 FN00 DFT0044245 T56034
 *			- Update doBuildSmartPDF function to prevent error message about tidx is invalid.
 *
 *  09 Jan 2015 Aurkarn Mongkonrat P0234765 FN01 DFT0046281 T80142
 *			- Update doSmartviewAjax to be able to pass any custom buttons.
 *
 *  11 Dec 2015 Narin Suanlamyai    P0241773 FN00 DFT0056951 T81879
 *          - Call fixASCIICodeDisplay in reponseHandler of doSmartviewAjax function
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *			- Fixed screens don't response when user's profile has too many slots attached.
 *
 *	14 Jun 2016 Watchara Th. P0241773 CHG0045794 DFT0064894 T83084
 *			- Update Ajax call functions to ignore error code.
 *
 *  07 May 2018 Pao - Supareuk S.
 *  		In doBuildPDFReport function, we changed a way to show the page
 *  		using buildURL to form submittion. This is to solve an issue when 
 *  		user's profile has too many slot attached. If the session is included, the page
 *  		will be broken as too large.
 *
 *********************************************************************************************/

 function fixASCIICodeDisplay(xml)
 {
	if (xml == null) return;
	
	/*
	 * Define undisplayable and displayable charecters 
	 * 	- 1st item: undisplayable charactor
	 *	- 2nd item: displayable charactor
	 */
	var asciiCode = [['156', '339']];
	var xmlStr = IFDS.Xml.serialize(xml);
	
	if (xmlStr == null || xmlStr.length <= 0) return;
	
	for (i=0; i<asciiCode.length; i++)
	{
		var regEx = new RegExp(String.fromCharCode(asciiCode[i][0]), 'g');
		xmlStr = xmlStr.replace(regEx, String.fromCharCode(asciiCode[i][1]));
	}
	return IFDS.Xml.stringToXML(xmlStr);	
 }
 
DesktopWeb.Ajax = {
	
	buildBaseURL: function()
	{
		var url = DesktopWeb._SERVLET_PATH + "?"
			+ "cz=" + DesktopWeb._SCREEN_PARAM_MAP['cz'];
			
		return url;
	}
	
	,buildURL: function(params)
	{
		var url = this.buildBaseURL();
		for (var i in params)
		{
			url += "&" + i + "=" + params[i];
		}		
		return url; 	
	}
	
	,buildServiceCallURL: function(serviceType, serviceName, additionalParams)
	{
		var urlParams = (additionalParams != null ? additionalParams : {});
		urlParams["jobName"] = "CallService";				
		urlParams["envName"] = DesktopWeb._SCREEN_PARAM_MAP['envName'];
		urlParams["sessionId"] = DesktopWeb._SCREEN_PARAM_MAP['sessionId'];
		
		if (DesktopWeb._SCREEN_PARAM_MAP['tidx'])
		{
			urlParams["tidx"] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];
		}
		
		urlParams["serviceType"] = serviceType;
		urlParams["serviceName"] = serviceName;
		 
		return this.buildURL(urlParams);			
	}
	
	,doServiceCall: function(serviceType, serviceName, urlParams, xml, callbackFn, processingMsg)
	{
		if (processingMsg)
		{
			DesktopWeb.Util.displayProcessing(processingMsg);
		}
		
		var serviceRequestXML = IFDS.Xml.newDocument("ServiceRequest");		
		IFDS.Xml.appendNode(serviceRequestXML, IFDS.Xml.cloneDocument(xml));
				
		Ext.Ajax.request(
			{
				url: this.buildServiceCallURL(serviceType, serviceName, urlParams)				
				,success: responseHandler
				,method: 'POST'
				,timeout: 90000
				,xmlData: serviceRequestXML											
			}	
		)
		
		function responseHandler(response)
		{			
			if (processingMsg)
			{
				DesktopWeb.Util.hideProcessing();
			}	
			
			var responseXML = fixASCIICodeDisplay(response.responseXML);
			
			if (IFDS.Xml.getNode(responseXML, '//RequestStatus') == null)
			{				
				DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("ServiceCallFailed") 
					+ "<br/><br/>["
					+ DesktopWeb.Translation.getTranslation('Service') + "=" + serviceName + ", "
					+ DesktopWeb.Translation.getTranslation('Environment') + "=" + DesktopWeb._SCREEN_PARAM_MAP['envName'] + "]");					
			}
			else
			{
				callbackFn(responseXML);
			}
		}
	}
	
	,doSynchServiceCall: function(serviceType, serviceName, urlParams, xml, callbackFn, processingMsg)
	{
		if (processingMsg)
		{
			DesktopWeb.Util.displayProcessing(processingMsg);
		}
		
		var serviceRequestXML = IFDS.Xml.newDocument("ServiceRequest");		
		IFDS.Xml.appendNode(serviceRequestXML, IFDS.Xml.cloneDocument(xml));
				
		var httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
        httpRequest.open("POST", this.buildServiceCallURL(serviceType, serviceName, urlParams), false /* Updates are SYNCHRONOUS */);
    	httpRequest.onreadystatechange = responseHandler;    	    	
    	httpRequest.send(serviceRequestXML);
		
			
		function responseHandler(response)
		{
			if (httpRequest.readyState == 4 && httpRequest.status == 200)
			{			
				if (processingMsg)
				{
					DesktopWeb.Util.hideProcessing();
				}
				
				var responseXML = fixASCIICodeDisplay(httpRequest.responseXML);
				
				if (IFDS.Xml.getNode(responseXML, '//RequestStatus') == null)
				{				
					DesktopWeb.Util.displayError(DesktopWeb.Translation.getTranslation("ServiceCallFailed") 
					+ "<br/><br/>["
					+ DesktopWeb.Translation.getTranslation('Service') + "=" + serviceName + ", "
					+ DesktopWeb.Translation.getTranslation('Environment') + "=" + DesktopWeb._SCREEN_PARAM_MAP['envName'] + "]");	
				}
				else
				{
					callbackFn(responseXML);
				}
			}
		}
	}
	
	,doSmartviewCall: function(apiName, urlParams, dataXML, callbackFn, processingMsg)
	{
		this.doServiceCall('INQUIRY', 
			apiName, 
			urlParams, 
			this.buildSmartviewXML(apiName, dataXML),
			callbackFn,
			processingMsg);
	}
	
	,doSmartviewUpdateCall: function(apiName, urlParams, dataXML, callbackFn, processingMsg)
	{
		this.doSynchServiceCall('INQUIRY', 
			apiName, 
			urlParams, 
			this.buildSmartviewXML(apiName, dataXML),
			callbackFn,
			processingMsg);
	}
	
	,buildSmartviewXML: function(apiName, dataXML)
	{
		var xml = IFDS.Xml.newDocument(apiName + "Request");
		
		//request header
		var reqHeader = IFDS.Xml.addSingleNode(xml, 'RequestHeader');
		IFDS.Xml.addSingleNode(reqHeader, 'apiName', apiName);		
		IFDS.Xml.addSingleNode(reqHeader, 'envName', DesktopWeb._SCREEN_PARAM_MAP['envName']);
		IFDS.Xml.addSingleNode(reqHeader, 'companyCode', DesktopWeb._SCREEN_PARAM_MAP['companyCode']);
		IFDS.Xml.addSingleNode(reqHeader, 'ruserId', DesktopWeb._SCREEN_PARAM_MAP['ruserId']);
		IFDS.Xml.addSingleNode(reqHeader, 'sessionId', DesktopWeb._SCREEN_PARAM_MAP['sessionId']);
		IFDS.Xml.addSingleNode(reqHeader, 'dateFormat', DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
		IFDS.Xml.addSingleNode(reqHeader, 'dataMode', 'inquire'); 
		IFDS.Xml.addSingleNode(reqHeader, 'locale',  DesktopWeb._SCREEN_PARAM_MAP['locale']);
		IFDS.Xml.addSingleNode(reqHeader, 'interfaceName',  'ifds.desktop');
		IFDS.Xml.addSingleNode(reqHeader, 'language',  DesktopWeb._SCREEN_PARAM_MAP['locale'].substring(0, 2));
		
		if (dataXML)
		{
			IFDS.Xml.appendNode(xml, IFDS.Xml.cloneDocument(dataXML));
		}
		
		return xml;
	}
	
	,parseSmartviewResponse: function(smartviewResponseXML, errorsToIgnore)
	{
		var errorsToIgnoreString = (errorsToIgnore ? errorsToIgnore.join("|") + "|" : "");;
		
		var results = {};		
		results.warnings = [];
		results.genericErrors = [];
		results.contextErrors = [];
		 
		var errorNodes = IFDS.Xml.getNodes(smartviewResponseXML, 'RequestStatus/Errors/Error');
		
		for (var i = 0; i < errorNodes.length; i++)
		{
			if (errorsToIgnoreString.indexOf(IFDS.Xml.getNodeValue(errorNodes[i], 'errorCode') + "|") == -1)
			{			
				if (IFDS.Xml.getNodeValue(errorNodes[i], 'errorSeverity') == 'error')
				{
					if (IFDS.Xml.getNode(errorNodes[i], 'recordSource') != null)
					{
						results.contextErrors[results.contextErrors.length] = errorNodes[i];
					}
					else
					{
						results.genericErrors[results.genericErrors.length] = errorNodes[i];
					}				
				}
				else
				{
					results.warnings[results.warnings.length] = errorNodes[i];
				}
			}
		}		
		results.successful = (results.genericErrors.length == 0 && results.contextErrors.length == 0);
		
		if (results.genericErrors.length > 0)
		{
			DesktopWeb.Ajax.displaySmartviewErrors(results.genericErrors);
		}
		else if (results.warnings.length > 0)   //only display warnings if no generic errors found
		{
			DesktopWeb.Ajax.displaySmartviewWarnings(results.warnings);
		}
		
		return results;
	}
	
	,displaySmartviewErrors: function(errorNodes)
	{							
		var msg = IFDS.Xml.getNodeValue(errorNodes[0], 'text');							
		for (var i = 1; i < errorNodes.length; i++)
		{
			msg += "<br/><br/>" + IFDS.Xml.getNodeValue(errorNodes[i], 'text');		
		}		
		if (msg != null)
		{		
			DesktopWeb.Util.displayError(msg);
		}
	}
			
	,displaySmartviewWarnings: function(warningNodes)
	{				
		var msg = IFDS.Xml.getNodeValue(warningNodes[0], 'text');				
		for (var i = 1; i < warningNodes.length; i++)
		{
			msg += "<br/><br/>" + IFDS.Xml.getNodeValue(warningNodes[i], 'text')
		}		
		DesktopWeb.Util.displayWarning(msg);
	}
	
	,doUpdateCache: function(cacheDataMap, callbackFn, processingMsg)
	{
		if (processingMsg)
		{
			DesktopWeb.Util.displayProcessing(processingMsg);
		}
					
		Ext.Ajax.request(
			{
				url: this.buildURL({jobname: 'UpdateCache', tidx: DesktopWeb._SCREEN_PARAM_MAP['tidx']})				
				,success: responseHandler
				,method: 'POST'
				,timeout: 90000
				,xmlData: this.buildUpdateCacheRequestXML(cacheDataMap)											
			}	
		)
		
		function responseHandler(response)
		{			
			if (processingMsg)
			{
				DesktopWeb.Util.hideProcessing();
			}	
			
			callbackFn(response.responseXML);
		}
	}
	
	,buildUpdateCacheRequestXML: function(cacheDataMap)
	{
		var xml = IFDS.Xml.newDocument("UpdateCacheRequest");
		
		for (var i in cacheDataMap)
		{
			var toBeCachedNode = IFDS.Xml.addSingleNode(xml, "ToBeCached");
			IFDS.Xml.addAttribute(toBeCachedNode, 'cacheKey', i);
			IFDS.Xml.appendNode(toBeCachedNode, IFDS.Xml.cloneDocument(cacheDataMap[i]));
		}
		
		return xml;
	}
	
	,doRetrieveCache: function(cacheKeys, callbackFn, processingMsg)
	{
		if (processingMsg)
		{
			DesktopWeb.Util.displayProcessing(processingMsg);
		}
					
		Ext.Ajax.request(
			{
				url: this.buildURL({jobname: 'RetrieveCache', tidx: DesktopWeb._SCREEN_PARAM_MAP['tidx'] })				
				,success: responseHandler
				,method: 'POST'
				,timeout: 90000
				,xmlData: this.buildRetrieveCacheRequestXML(cacheKeys)											
			}	
		)
		
		function responseHandler(response)
		{			
			if (processingMsg)
			{
				DesktopWeb.Util.hideProcessing();
			}	
			
			callbackFn(response.responseXML);
		}
	}
	
	,buildRetrieveCacheRequestXML: function(cacheKeys)
	{
		var xml = IFDS.Xml.newDocument("RetrieveCacheRequest");
		
		for (var i = 0; i < cacheKeys.length; i++)
		{
			IFDS.Xml.addSingleNode(xml, "cacheKey", cacheKeys[i]);
		}
		
		return xml;
	}
		
	,doBuildPDFReport: function(apiName, template, report, dataXML)
	{		
		var dataFld = document.getElementById("BuildPDFReport-data");
		dataFld.value = IFDS.Xml.serialize(this.buildSmartviewXML(apiName, dataXML));
		
		var form = document.getElementById("BuildPDFReport-form");		
		DesktopWeb.Util.addHiddenToForm(form, 'jobname', "BuildPDFReport");
		DesktopWeb.Util.addHiddenToForm(form, 'cz', DesktopWeb._SCREEN_PARAM_MAP['cz']);
		DesktopWeb.Util.addHiddenToForm(form, 'envName', DesktopWeb._SCREEN_PARAM_MAP['envName']);
		DesktopWeb.Util.addHiddenToForm(form, 'sessionId', DesktopWeb._SCREEN_PARAM_MAP['sessionId']);
		DesktopWeb.Util.addHiddenToForm(form, 'template', template);
		DesktopWeb.Util.addHiddenToForm(form, 'report', report);
		DesktopWeb.Util.addHiddenToForm(form, 'serviceName', apiName);
		//form.action = this.buildURL(urlParams);
		form.submit();				
	}
	
	,doBuildSmartPDF: function(pdfType, params)
	{
		var _params = {};
		if (DesktopWeb._SCREEN_PARAM_MAP['tidx'])
		{
			_params['tidx'] = DesktopWeb._SCREEN_PARAM_MAP['tidx'];
		}
		
		_params['pdfType'] = pdfType;
		
		for (var i in params) {
			_params[i] = params[i];
		}

			DesktopWeb.Util.goToScreen('PDFViewer', _params);
		
	}
	
	//***************************************************************
	
	
	
	
	/*********************************************************************************************
	 * Builds URL for doing Smartview AJAX call, which will include default parameters
	 *
	 * @param 	params - map of parameters to be used, specific to the smartview being called 
	 *********************************************************************************************/
	,buildSmartviewAjaxURL: function(smartview, params)
	{
		var url = DesktopWeb._SERVLET_PATH + "?"
			+ "cz=" + DesktopWeb._SCREEN_PARAM_MAP['cz']
			+ "&jobname=" + "SmartviewAjax"		
			+ "&envName=" + DesktopWeb._SCREEN_PARAM_MAP['envName']
			+ "&smartview=" + smartview
			
		// add URL specific parameters (NOTE: won't be included in actual smartview request)	 
		for (var i in params)
		{
			url += "&" + i + "=" + params[i];
		}		
		return url; 			
	}
	
	/*********************************************************************************************
	 * Builds URL for doing Smartview AJAX call, which will include default parameters
	 *
	 * @param 	params - map of parameters to be used, specific to the smartview being called 
	 *********************************************************************************************/
	,buildSmartviewRequestXML: function(smartview, requestDataXML)
	{
		var xml = IFDS.Xml.newDocument("SmartviewRequest");
		
		var header = IFDS.Xml.addSingleNode(xml, 'header');
		IFDS.Xml.addSingleNode(header, 'apiName', smartview);		
		IFDS.Xml.addSingleNode(header, 'envName', DesktopWeb._SCREEN_PARAM_MAP['envName']);
		IFDS.Xml.addSingleNode(header, 'companyCode', DesktopWeb._SCREEN_PARAM_MAP['companyCode']);
		IFDS.Xml.addSingleNode(header, 'ruserId', DesktopWeb._SCREEN_PARAM_MAP['ruserId']);
		IFDS.Xml.addSingleNode(header, 'sessionId', DesktopWeb._SCREEN_PARAM_MAP['sessionId']);
		IFDS.Xml.addSingleNode(header, 'dateFormat', DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
		IFDS.Xml.addSingleNode(header, 'locale',  DesktopWeb._SCREEN_PARAM_MAP['locale']);
		
		var interfaceName = DesktopWeb._SCREEN_PARAM_MAP['interfaceName'];
		if (!interfaceName || interfaceName.length <= 0) interfaceName = 'ifds.desktop';
		
		IFDS.Xml.addSingleNode(header, 'interfaceName',  interfaceName);
		IFDS.Xml.addSingleNode(header, 'language',  DesktopWeb._SCREEN_PARAM_MAP['locale'].substring(0, 2));
		
		var body = IFDS.Xml.addSingleNode(xml, 'body');
		if (requestDataXML != null) {
			var dataXMLFields = IFDS.Xml.getNodes(requestDataXML, '/*/*');						
			for (var i = 0; i < dataXMLFields.length; i++) {				
				IFDS.Xml.appendNode(body, IFDS.Xml.cloneDocument(dataXMLFields[i]));
			}
		}
		return xml;		
	}
		
	/*********************************************************************************************
	 * Displays MessageBox containing error details found in xml returned from Smartview AJAX call
	 * 
	 * @param 	responseXML - xml containing error details	 
	 *********************************************************************************************/
	,displaySmartviewAjaxErrors: function(errorNodes)
	{							
		var msg = IFDS.Xml.getNodeValue(errorNodes[0], 'text');
							
		for (var i = 1; i < errorNodes.length; i++)
		{
			msg += "<br/><br/>" + IFDS.Xml.getNodeValue(errorNodes[i], 'text');		
		}
		
		if (msg != null)
		{		
			DesktopWeb.Util.displayError(msg);
		}
	}
		
	/*********************************************************************************************
	 * Displays MessageBox containing warning details found in xml returned from 
	 * Smartview AJAX call. This makes the assumption that all errors found will be 
	 * warnings, because if not they should have been displayed in Error dialog.
	 * 
	 * @param 	responseXML - xml containing warning details	
	 * @param   callbackFn  - method to be called
	 * @param   btn - custom button
	 *********************************************************************************************/
	,displaySmartviewAjaxWarnings: function(warningNodes, callbackFn, btn)
	{				
		var msg = IFDS.Xml.getNodeValue(warningNodes[0], 'text');				
		for (var i = 1; i < warningNodes.length; i++)
		{
			msg += "<br/><br/>" + IFDS.Xml.getNodeValue(warningNodes[i], 'text')
		}		
		DesktopWeb.Util.displayWarning(msg, callbackFn, btn);
	}
		
	/*********************************************************************************************
	 * Executes AJAX call to specified Smartview, executes callbackFn when 
	 * AJAX call returns
	 * 
	 * @param 	smartview - smartview API to be called
	 * @param 	params - map of parameters required by smartview
	 * @param 	xml - xml to be posted, if necessary
	 * @param 	callbackFn - method to be executed when AJAX call returns
	 * @param 	processingMsg - text to display in 'processing' banner	 
	 * @param   btn - custom button
	 * @param	errorsToIgnore -Array of error code to ignore
	 *********************************************************************************************/
	,doSmartviewAjax: function(smartview, urlParams, smartviewRequestBodyXML, callbackFn, processingMsg, btn, errorsToIgnore)
	{
		if (processingMsg)
		{
			DesktopWeb.Util.displayProcessing(processingMsg);
		}		
		Ext.Ajax.request(
			{
				url: DesktopWeb.Ajax.buildSmartviewAjaxURL(smartview, urlParams)				
				,success: responseHandler
				,method: 'POST'
				,timeout: 90000
				,xmlData: DesktopWeb.Ajax.buildSmartviewRequestXML(smartview, smartviewRequestBodyXML)											
			}	
		)
		
		
		function responseHandler(response)
		{
			var results = DesktopWeb.Ajax.parseSmartviewAjaxResponse(fixASCIICodeDisplay(response.responseXML), errorsToIgnore);
			var dispWarning = !urlParams || ( urlParams != undefined && !urlParams.ignoreWarning);
		
			if (results.genericErrors.length > 0)
			{
				DesktopWeb.Ajax.displaySmartviewAjaxErrors(results.genericErrors);
			}
			else if (results.warnings.length > 0 && dispWarning)   //only display warnings if no generic errors found
			{
				DesktopWeb.Ajax.displaySmartviewAjaxWarnings(results.warnings, responseBtn, btn);
			}
						
			if (processingMsg)
			{
				DesktopWeb.Util.hideProcessing();
			}		
				
			if (results.genericErrors.length > 0 || !(results.warnings.length > 0 && dispWarning))
			{
				responseBtn(null);
			}
			
			function responseBtn(resultBtn)
			{
				callbackFn(results.success, response.responseXML, results.contextErrors, results.warnings, resultBtn);
			}
		}
	}
	
	/*********************************************************************************************
	 * Executes SYNCHRONOUS AJAX call to specified Smartview, executes callbackFn when 
	 * AJAX call returns. Only intended for updates launched Desktop C++ integration.
	 * 
	 * @param 	smartview - smartview API to be called
	 * @param 	params - map of parameters required by smartview
	 * @param 	xml - xml to be posted, if necessary
	 * @param 	callbackFn - method to be executed when AJAX call returns	 
	 * @param 	processingMsg - text to display in 'processing' banner
	 * @param	errorsToIgnore -Array of error code to ignore
	 *********************************************************************************************/
	,doSmartviewUpdate: function(smartview, params, smartviewRequestBodyXML, callbackFn, processingMsg, errorsToIgnore)
	{		
		if (processingMsg)
		{
			DesktopWeb.Util.displayProcessing(processingMsg);
		}
		
		var httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
		httpRequest.open("POST", DesktopWeb.Ajax.buildSmartviewAjaxURL(smartview, params), false /* Updates are SYNCHRONOUS */);
		httpRequest.onreadystatechange = responseHandler;
		// prompt("", DesktopWeb.Ajax.buildSmartviewRequestXML(smartview, smartviewRequestBodyXML).xml);    	
		httpRequest.send(DesktopWeb.Ajax.buildSmartviewRequestXML(smartview, smartviewRequestBodyXML));
		
		function responseHandler()
		{
			if (httpRequest.readyState == 4 && httpRequest.status == 200)
			{			
				var results = DesktopWeb.Ajax.parseSmartviewAjaxResponse(httpRequest.responseXML, errorsToIgnore);
				
				if (results.genericErrors.length > 0)
				{
					DesktopWeb.Ajax.displaySmartviewAjaxErrors(results.genericErrors);
				}
				else if (results.warnings.length > 0)   //only display warnings if no generic errors found
				{
					DesktopWeb.Ajax.displaySmartviewAjaxWarnings(results.warnings);
				}
							
				if (processingMsg)
				{
					DesktopWeb.Util.hideProcessing();
				}	
				
				callbackFn(results.success, httpRequest.responseXML, results.contextErrors);
			}
		}
	}
	
	/*********************************************************************************************
	 * Parse response XML from AJAX call, building results object to store errors, warnings, etc.	 
	 * 
	 * @param 	responseXML - xml doc returned from AJAX call
	 * @return	object 
	 *********************************************************************************************/
	,parseSmartviewAjaxResponse: function(responseXML, errorsToIgnore)
	{
		var results = {};
		results.warnings = [];
		results.genericErrors = [];
		results.contextErrors = [];
		
		var errorsToIgnoreString = (errorsToIgnore ? errorsToIgnore.join("|") + "|" : "");
		 
		var errorNodes = IFDS.Xml.getNodes(responseXML, '/SmartviewResponse/Errors/Error');
		
		for (var i = 0; i < errorNodes.length; i++)
		{
			if(errorsToIgnoreString.indexOf(IFDS.Xml.getNodeValue(errorNodes[i], 'errorCode') + "|") == -1) 
			{
				if (IFDS.Xml.getNodeValue(errorNodes[i], 'errorSeverity') == 'error')
				{
					if (IFDS.Xml.getNode(errorNodes[i], '//source') != null)
					{
						results.contextErrors[results.contextErrors.length] = errorNodes[i];
					}
					else
					{
						results.genericErrors[results.genericErrors.length] = errorNodes[i];
					}
				}
				else
				{
					results.warnings[results.warnings.length] = errorNodes[i];
				}
			}
		}
		
		results.success = (results.genericErrors.length == 0 && results.contextErrors.length == 0);
		
		return results;
	}
	
	/*********************************************************************************************
	 * Retrieves nextStartRecNum value from Smartview XML, returns null if not applicable
	 * 
	 * @param 	smartviewXML	 
	 *********************************************************************************************/
	,getSmartviewNextStartRecNum: function(smartviewXML)
	{
		var recNum = null;
		var moreRecordsNode = IFDS.Xml.getNode(smartviewXML, '//RecordRange/moreRecordsExist');
		if (moreRecordsNode != null && IFDS.Xml.getNodeValue(moreRecordsNode).toLowerCase() == 'yes') 			
		{
			recNum = IFDS.Xml.getNodeValue(smartviewXML, '//RecordRange/rangeStartForNext');
		}
		return recNum;
	}
	
	/*********************************************************************************************
	 * Determines if Smartview AJAX call resulted in error
	 * 
	 * @param 	responseXML - xml returned by Smartview AJAX call	 
	 *********************************************************************************************/
	,isSmartviewAjaxSuccessful: function(responseXML)	
	{		
		return IFDS.Xml.getNodeValue(responseXML, "/SmartviewResponse/status").toLowerCase() == "success";									
	}
	
	/*********************************************************************************************
	 * @desc	Determines if Smartview AJAX call returned warning(s)
	 * 
	 * @param 	responseXML - xml returned by Smartview AJAX call	 
	 *********************************************************************************************/
	,foundSmartviewAjaxWarnings: function(responseXML)	
	{											
		var errorNode = IFDS.Xml.getNode(responseXML, '/SmartviewResponse/Errors/Error');
		return (errorNode != null && IFDS.Xml.getNodeValue(errorNode, "errorSeverity").toLowerCase() == "warning");		
	}
	
	/*********************************************************************************************
	 * Builds URL for doing API AJAX call, which will include default parameters
	 *
	 * @param 	apiName
	 * @param 	params - map of parameters to be used, specific to the smartview being called 
	 *********************************************************************************************/
	,buildAPIAjaxURL: function(apiName, params)
	{
		var url = DesktopWeb._SERVLET_PATH + "?"
			+ "cz=" + DesktopWeb._SCREEN_PARAM_MAP['cz']
			+ "&jobname=" + "APIAjax"		
			+ "&envName=" + DesktopWeb._SCREEN_PARAM_MAP['envName']
			+ "&apiName=" + apiName
			
		if (DesktopWeb._SCREEN_PARAM_MAP['useDebug']
			&& DesktopWeb._SCREEN_PARAM_MAP['useDebug'].toLowerCase() == 'true')
		{
			url += "&useDebug=true"	
		} 
		
		// add URL specific parameters (NOTE: won't be included in actual smartview request)	 
		for (var i in params)
		{
			url += "&" + i + "=" + params[i];
		}		
		return url; 			
	}
	
	/*********************************************************************************************
	 * Builds URL for doing API AJAX call, which will include default parameters
	 *
	 * @param 	params - map of parameters to be used, specific to the api being called 
	 *********************************************************************************************/
	,buildAPIRequestXML: function(apiName, requestDataXML)
	{
		var xml = IFDS.Xml.newDocument("APIRequest");
		
		var header = IFDS.Xml.addSingleNode(xml, 'header');
		IFDS.Xml.addSingleNode(header, 'apiName', apiName);				
		IFDS.Xml.addSingleNode(header, 'companyCode', DesktopWeb._SCREEN_PARAM_MAP['companyCode']);
		IFDS.Xml.addSingleNode(header, 'envName', DesktopWeb._SCREEN_PARAM_MAP['envName']);
		IFDS.Xml.addSingleNode(header, 'ruserId', DesktopWeb._SCREEN_PARAM_MAP['ruserId']);
		IFDS.Xml.addSingleNode(header, 'sessionId', DesktopWeb._SCREEN_PARAM_MAP['sessionId']);
		IFDS.Xml.addSingleNode(header, 'locale',  DesktopWeb._SCREEN_PARAM_MAP['locale']);
		IFDS.Xml.addSingleNode(header, 'interfaceName',  'ifds.desktop');
		IFDS.Xml.addSingleNode(header, 'language',  DesktopWeb._SCREEN_PARAM_MAP['locale'].substring(0, 2));		
		
		var body = IFDS.Xml.addSingleNode(xml, 'body');
		if (requestDataXML != null) {
			var dataXMLFields = IFDS.Xml.getNodes(requestDataXML, '/*/*');						
			for (var i = 0; i < dataXMLFields.length; i++) {				
				IFDS.Xml.appendNode(body, IFDS.Xml.cloneDocument(dataXMLFields[i]));
			}
		}
		return xml;		
	}
	
	/*********************************************************************************************
	 * Executes AJAX call to specified API, executes callbackFn when 
	 * AJAX call returns
	 * 
	 * @param 	apiName - API to be called
	 * @param 	params - map of parameters required by smartview
	 * @param 	xml - xml to be posted
	 * @param 	callbackFn - method to be executed when AJAX call returns
	 * @param 	processingMsg - text to display in 'processing' banner	 
	 *********************************************************************************************/
	,doAPIAjax: function(apiName, urlParams, xml, callbackFn, processingMsg)
	{
		if (processingMsg)
		{
			DesktopWeb.Util.displayProcessing(processingMsg);
		}
				
		Ext.Ajax.request(
			{
				url: DesktopWeb.Ajax.buildAPIAjaxURL(apiName, urlParams)				
				,success: responseHandler
				,method: 'POST'
				,timeout: 90000
				,xmlData: DesktopWeb.Ajax.buildAPIRequestXML(apiName, xml)											
			}	
		)
		
		function responseHandler(response)
		{
			if (processingMsg)
			{
				DesktopWeb.Util.hideProcessing();
			}	
			
			callbackFn(response.responseXML);
		}
	}
}