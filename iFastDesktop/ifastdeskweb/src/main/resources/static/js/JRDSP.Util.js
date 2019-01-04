Ext.namespace("JRDSP");
JRDSP.Util = {
	sendRequestToDesktopWeb : function(_contextController, _routePath,
			_service, method, params,requestXML,callbackfnSuccess,callbackfnFailure) {
		if(method!='POST_Inquiry')
			{
		Ext.Ajax.request({
			//async: false,
			url : JRDSP.Util.buildJRDSPviewAjaxURL(_contextController, _routePath,
					_service, params),
			success : callbackfnSuccess,
			method : method,
			timeout : 90000,
			xmlData : JRDSP.Util.buildSmartviewRequestXML(_service, requestXML),
			failure: callbackfnFailure
			 
		});
			}
		else
			{
			Ext.Ajax.request({
				url : JRDSP.Util.buildJRDSPviewAjaxURL(_contextController, _routePath,
						_service, params),
				success : callbackfnSuccess,
				method : 'POST',
				timeout : 90000,
				xmlData : null,
				 headers: {
				        'Content-Type': 'text/xml'
				    }
				,failure: callbackfnFailure
			});
			
			}
			
	},
	buildJRDSPviewAjaxURL : function(contextController, routePath, smartview,
			params) {
		var url = contextController +"/"+ routePath + "/" + "?" + "&envName="
				+ DesktopWeb._SCREEN_PARAM_MAP['envName'] + "&smartview="
				+ smartview;
		

		// add URL specific parameters (NOTE: won't be included in actual
		// smartview request)
		for ( var i in params) {
			if(i == 'sessionId')
				{
				continue;
				}
			url += "&" + i + "=" + params[i];
		}

		
		return url;
	}
	,buildSmartviewRequestXML : function(smartview, requestDataXML) {
		var xml = IFDS.Xml.newDocument(smartview+'Request');

		//var apiHeader = IFDS.Xml.addSingleNode(xml, smartview + 'Request');

	/*	var header = IFDS.Xml.addSingleNode("", 'RequestHeader');
		IFDS.Xml.addSingleNode(header, 'apiName', smartview);
		IFDS.Xml.addSingleNode(header, 'envName',
				DesktopWeb._SCREEN_PARAM_MAP['envName']);
		IFDS.Xml.addSingleNode(header, 'companyCode',
				DesktopWeb._SCREEN_PARAM_MAP['companyCode']);
		IFDS.Xml.addSingleNode(header, 'ruserId',
				DesktopWeb._SCREEN_PARAM_MAP['ruserId']);
		IFDS.Xml.addSingleNode(header, 'sessionId',
				DesktopWeb._SCREEN_PARAM_MAP['sessionId']);
		IFDS.Xml.addSingleNode(header, 'dateFormat',
				DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
		IFDS.Xml.addSingleNode(header, 'locale',
				DesktopWeb._SCREEN_PARAM_MAP['locale']);
		IFDS.Xml.addSingleNode(header, 'dataMode', 'inquire');

		var interfaceName = DesktopWeb._SCREEN_PARAM_MAP['interfaceName'];
		if (!interfaceName || interfaceName.length <= 0)
			interfaceName = 'ifds.desktop';

		IFDS.Xml.addSingleNode(header, 'interfaceName', interfaceName);
		IFDS.Xml.addSingleNode(header, 'language',
				DesktopWeb._SCREEN_PARAM_MAP['locale'].substring(0, 2));*/

		//var body = IFDS.Xml.addSingleNode(xml, 'data');
		if (requestDataXML != null) {
			var dataXMLFields = IFDS.Xml.getNodes(requestDataXML, '/*/*');
			for (var i = 0; i < dataXMLFields.length; i++) {
				IFDS.Xml.appendNode(xml, IFDS.Xml
						.cloneDocument(dataXMLFields[i]));
			}
		}
		return xml;
	},
	responseHandler : function(success, responseXML) {
		
		return responseXML;
		
	}
	
,convertDate: function(date){
	
	var dateParts = date.split("/");
	
	var year=parseInt(dateParts[2],10);
	var month=parseInt(dateParts[1],10);
	var date=parseInt(dateParts[0],10);
	
	var dateObject = new Date(year, month, date); // month is 0-based
	
	return dateObject;
}
,convertDateToStringFormat: function(date){
	
	var dateParts = date.split("/");
	var year=parseInt(dateParts[2],10);
	var month=parseInt(dateParts[1],10);
	var day=parseInt(dateParts[0],10);


if (month < 10) month = '0' + month;
if (day < 10) day = '0' + day;

return [year, month, day].join('-');
}
,convertStringToDate : function(date){
	

	var dateParts = date.split("-");
	var year=parseInt(dateParts[0],10);
	var month=parseInt(dateParts[1],10);
	var day=parseInt(dateParts[2],10);
	
	if (month < 10) month = '0' + month;
	if (day < 10) day = '0' + day;
	
	return [day, month, year].join('/');
	
	
}

/* clearComponentDetails() method is used to clear existing details from dynamically populating component to load new data */
,clearComponentDetails : function(componentId) {
	Ext.getCmp(componentId).removeAll(); 
	Ext.getCmp(componentId).update();
	Ext.getCmp(componentId).doLayout();
}

	
	
}