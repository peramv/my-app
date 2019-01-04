APIResponse = Ext.extend(Object, {
	constructor: function(name, xmlNode, description)
	{				
		APIResponse.superclass.constructor.call(this);
		this.xmlNode = xmlNode;		
		this.apiName = name;
		this.description = description;			
	}
	
	,getError_Warnings: function(type)
	{
		var error_warnings = [];
		var errorNodes = IFDS.Xml.getNodes(this.xmlNode, 'RequestStatus/Errors/Error');
		
		if (errorNodes != null)
		{
			for (var i = 0; i < errorNodes.length; i++)
			{
				if (IFDS.Xml.getNodeValue(errorNodes[i], 'errorSeverity').toLowerCase() == type)
				{
					error_warnings[error_warnings.length] = {
						errorCode: IFDS.Xml.getNodeValue(errorNodes[i], 'errorCode')
						,text: IFDS.Xml.getNodeValue(errorNodes[i], 'text')							
					};
				}
			}
		}
		return error_warnings;
	}		
	
	,getStatus: function()
	{		
		return IFDS.Xml.getNodeValue(this.xmlNode, 'RequestStatus/status');
	}		
	
	,getErrors: function()
	{
		return this.getError_Warnings('error');
	}
	
	,getWarnings: function()
	{
		return this.getError_Warnings('warning');
	}
	
	,getNode: function(path)
	{
		return IFDS.Xml.getNode(this.xmlNode, path);
	}
	
	,getNodes: function(path)
	{
		return IFDS.Xml.getNodes(this.xmlNode, path);
	}
})

PackageResponse = Ext.extend(APIResponse, {
	constructor: function(xml)
	{				
		PackageResponse.superclass.constructor.call(this, 'gnPackage', IFDS.Xml.getNode(xml, "//gnPackageResponse"), 'Package');		
	}
	
	,getAPINode: function(apiName)
	{
		for (var i = 0; i < this.xmlNode.childNodes.length; i++)
		{
			if (this.xmlNode.childNodes[i].nodeName == apiName + "Response")
			{								
				return this.xmlNode.childNodes[i];
			}
		}
		return null;					
	}
	
	,getAPINodes: function(apiName)
	{
		var nodes = [];
		for (var i = 0; i < this.xmlNode.childNodes.length; i++)
		{
			if (this.xmlNode.childNodes[i].nodeName == apiName + "Response")
			{								
				nodes.push(this.xmlNode.childNodes[i]);				
			}
		}
		return nodes;				
	}
});

AcctSetupResponse = Ext.extend(APIResponse, {
	constructor: function(xmlNode)
	{			
		AcctSetupResponse.superclass.constructor.call(this, 'gnAcctSetup', xmlNode, 'Account Setup');
	}
	
	,getAccountNum: function()
	{
		return IFDS.Xml.getNodeValue(this.xmlNode, 'Response/iFastAcct');
	}
	
	,getShareholderNum: function()
	{
		return IFDS.Xml.getNodeValue(this.xmlNode, 'Response/iFastPrKey');
	}
}); 


