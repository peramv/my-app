FormDataStore = Ext.extend(Ext.data.Tree,{
	constructor: function(api){
		this.pathSeparator = ".";				
		FormDataStore.superclass.constructor.apply(this);
		
		var rootNode = new Ext.data.Node({id: 'data'});
		rootNode.isRequired = function(){return true;}		 		
				
		for (var i in api)
		{	
			if (api[i].repeatCount)
			{
				for (var r = 0; r < api[i].repeatCount; r++)
				{		
					rootNode.appendChild(new FormDataStoreNode({
						name: i 
						,apiReference: api[i]
						,index:r											
					}));
				}
			}
			else
			{
				rootNode.appendChild(new FormDataStoreNode({
					name: i
					,apiReference: api[i]										
				}));
			}			 
		}
		this.setRootNode(rootNode);					
	}
	
	,validate: function()
	{
		var errors = [];
		var rootNode = this.getRootNode();
		for (var i = 0; i < rootNode.childNodes.length; i++)
		{
			rootNode.childNodes[i].validate(errors);
		}
		return errors;		
	}
	
	,buildXML: function()
	{
		var xmlDoc = IFDS.Xml.newDocument('root');
		var rootNode = this.getRootNode();
		for (var i = 0; i < rootNode.childNodes.length; i++)
		{
			if (rootNode.childNodes[i].id != 'apiTemp')
			{
				rootNode.childNodes[i].buildXML(xmlDoc);
			}
		}		
		return xmlDoc;
	}
	
	,getChildNodes: function()
	{
		return this.getRootNode().childNodes;
	}
	
	,getNode: function(path){
		var pathSteps = path.split(".")
		var firstStep = pathSteps[0];					
		if (pathSteps.length > 1)
		{				
			pathSteps.shift();
			return this.getRootNode().findChild("id", firstStep, false).getNode(pathSteps.join("."));
		}
		else if (pathSteps.length == 1)
		{	
			return this.getRootNode().findChild("id", firstStep, false);
		}	
	}
	
	,setNodeValue: function(path, value)
	{
		var node = this.getNode(path);
		node.setValue(value);
	}
	
	,getNodeValue: function(path)
	{
		return this.getNode(path).getValue();
	}
	
	,copyNodeValue: function(srcPath, destPath)
	{
		var srcNode = this.getNode(srcPath);
		var destNode = this.getNode(destPath);
		destNode.setValue(srcNode.getValue());
	}
	
	,setAPINodeReadOnly: function(apiName, index)
	{
		var nodes = this.getRootNode().childNodes;
		for (var i = 0; i < nodes.length; i++)
		{
			if (nodes[i].name == apiName + "Request" && nodes[i].hasData())
			{											
				if (index == 0 || index == null)
				{
					nodes[i].setReadOnly(true);
					break;
				}
				else
				{
					index--;
				}		
			}
		}			
	}
	
	,setAccountNumberInSecondaryAPIs: function(acctNum)
	{
		var nodes = this.getRootNode().childNodes;
		for (var i = 0; i < nodes.length; i++)
		{
			if (nodes[i].name.indexOf('gnAcctSetup') == -1				
				&& nodes[i].hasData())
			{
				if (nodes[i].name.indexOf('gnOrder') != -1)
				{											
					nodes[i].getNode('Order.accountIDType').setValue('iFAST');
					nodes[i].getNode('Order.accountIDValue').setValue(acctNum);	
				}
				else
				{
					var accountInfoNode = nodes[i].findChild('id', 'accountidtgroup', true);
					if (accountInfoNode != null)
					{					
						accountInfoNode.getNode('accountIDType').setValue('iFAST');
						accountInfoNode.getNode('accountIDValue').setValue(acctNum);
					}
				}
			}
		}			
	}
	
	,isAPIAvailable: function(dataMapping)
	{		
		var apiName = dataMapping.split(".")[0];
		apiName = (apiName.indexOf("[") != -1 ? apiName.substring(0, apiName.indexOf("[")) : apiName);		
		
		var childNodes = this.getChildNodes();
		for (var i = 0; i < childNodes.length; i++)
		{
			if (childNodes[i].name.indexOf(apiName) != -1)
			{
				return true;
			}
		}
		return false;
	}
});

FormDataStoreNode = Ext.extend(Ext.data.Node, {
	constructor: function(attributes){
		this.apiReference = attributes.apiReference		
		this.value = (this.apiReference.defaultValue ? this.apiReference.defaultValue : null);		
		this.name = attributes.name;
		this.index = attributes.index;		
		this.readOnly = false;
		
		var config = {
			id: attributes.name + (attributes.index != null ? "[" + attributes.index + "]" : "")			
			,leaf: (this.apiReference.type == 'field')			
		}
							
		FormDataStoreNode.superclass.constructor.call(this, config);		
				
		for (var i in this.apiReference.contents)
		{	
			if (this.apiReference.contents[i].repeatCount)
			{
				for( var r = 0; r < this.apiReference.contents[i].repeatCount; r++)
				{
					this.appendChild(new FormDataStoreNode({
						name: i 
						,apiReference: this.apiReference.contents[i] 
						,index: r
						,parentIsRequired: this.isRequired
					}));
				}
			}		
			else
			{
				this.appendChild(new FormDataStoreNode({
					name: i 
					,apiReference: this.apiReference.contents[i]
					,parentIsRequired: this.isRequired
				}));
			}			
		}
		
		if (this.isLeaf())
		{
			this.addEvents('updated');
			this.addEvents('validated');
		}
	}
	
	,isRequired: function()
	{		
		if (this.apiReference.isRequired && this.apiReference.isRequired(this))
		{
			return this.parentNode.isRequired();
		}
		return false;
	}
	
	,validate: function(errors)
	{
		if (this.isLeaf())
		{			
			if (this.isRequired() && !this.hasData())
			{
				var error = {
					text: Notifications.errorMessages.requiredField + " (" + this.getAbsoluteDescription() + ")"					
				}						
				errors.push(error);
				this.fireEvent('failedvalidation', error);
			}						
		}
		else
		{
			for (var i = 0; i < this.childNodes.length; i++)
			{										
				this.childNodes[i].validate(errors);				
			}
		}		
	}
	
	,buildXML: function(xmlContext)
	{				
		if (this.hasData() && !this.readOnly)
		{
			if (this.isLeaf())
			{
				IFDS.Xml.addSingleNode(xmlContext, this.name, this.value);			
			}
			else
			{								
				var node = IFDS.Xml.addSingleNode(xmlContext, this.name);
				for (var i = 0; i < this.childNodes.length; i++)
				{										
					this.childNodes[i].buildXML(node);				
				}
			}
		}
	}
	
	,setReadOnly: function(makeReadOnly)
	{
		this.readOnly = makeReadOnly
		if (!this.isLeaf)
		{			
			for (var i = 0; i < this.childNodes.length; i++)
			{										
				this.childNodes[i].setReadOnly(makeReadOnly);				
			}
		}
	}
	
	,hasData: function()
	{
		var dataFound = false;
		if (this.isLeaf())
		{
			dataFound = (this.value != null && this.value != "");
		}
		else
		{			
			for (var i = 0; i < this.childNodes.length; i++)
			{
				if (this.childNodes[i].hasData())
				{
					dataFound = true;
					break;
				}		
			}
		}
		return dataFound;	
	}
	
	,clearData: function()
	{
		if (this.isLeaf() && !this.readOnly)
		{
			this.setValue('');
		}
		else
		{
			for (var i = 0; i < this.childNodes.length; i++)
			{
				this.childNodes[i].clearData();					
			}
		}
	}
	
	,getValue: function()
	{
		return this.value;		
	}
	
	,setValue: function(newValue)
	{
		if (this.isLeaf() && !this.readOnly)
		{
			this.value = newValue;
			this.fireEvent('updated', this);
		}
		else
		{
			if (!this.isLeaf())
			{			
				throw new Error("FormDataStore: cannot set value of non-leaf node");
			}
			else
			{
				throw new Error("FormDataStore: cannot set value of read-only node");
			}
		}
	}
	
	,getChildNodes: function()
	{
		return this.childNodes;
	}
	
	,getNode: function(path){
		var pathSteps = path.split(".")
		var firstStep = pathSteps[0];					
		if (pathSteps.length > 1)
		{				
			pathSteps.shift();
			try
			{
				return this.findChild('id', firstStep).getNode(pathSteps.join("."));
			}
			catch(e)
			{
				throw new Error('Error getting node [' + path + ']');
			}
		}
		else if (pathSteps.length == 1)
		{	
			return this.findChild('id', firstStep);
		}	
	}
	
	,getNodeValue: function(path)
	{
		var node = this.getNode(path)
		return node.getValue();
	}
	
	,getAbsoluteDescription: function()
	{
		var parentDesc = ""
		if (this.parentNode && this.parentNode.getAbsoluteDescription)
		{
			parentDesc = this.parentNode.getAbsoluteDescription();  
		}
		var nodeDesc = ""
		if (this.apiReference.description)
		{
			nodeDesc = this.apiReference.description
			if (this.index != null)
			{
				nodeDesc += '[' + (this.index + 1) + ']'; 
			}
		}		
		return parentDesc + (parentDesc != "" && nodeDesc != "" ? "/" : "") + nodeDesc;
	}
});