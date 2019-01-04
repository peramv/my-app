/*********************************************************************************************
 * @file	IFDS.Xml.js
 * @author 	Rod Walker 
 * @desc	Javascript library for working with XML   
 *********************************************************************************************/

IFDS.Xml = {
	
	/*********************************************************************************************
	 * Browser portable function to create an empty xml document object with 
	 * a rootTag, if provided.
     *
     * @param 	rootTagName - tag name given to root node
     * @return 	xml document 
	 *********************************************************************************************/	
    newDocument: function(rootTagName)
    {
		var doc = null;
		rootTagName = (rootTagName == null ? "" : rootTagName);
        // standard method
        if ( document.implementation && document.implementation.createDocument )
        {
            doc = document.implementation.createDocument( "", rootTagName, null );
        }
        // IE specific method
        else
        {
            doc = new ActiveXObject( "MSXML2.DOMDocument" );

            if( rootTagName.length > 0 )
            {
                doc.loadXML( "<" + rootTagName + "/>" );
            }
        }
		return doc;
    }
	
	/*********************************************************************************************
	 * Creates clone xml document. 
     *
     * @param 	xmlDoc - xml document to clone 
     * @return 	xml document 
	 *********************************************************************************************/	
	,cloneDocument: function(xmlDoc)
	{
		return IFDS.Xml.stringToXML(IFDS.Xml.serialize(xmlDoc));	
	}
	
	/*********************************************************************************************
	 * Creates string in xml node format. 
     *
     * @param 	tagName
     * @param 	tagValue  
     * @return 	string 
	 *********************************************************************************************/
	,createNodeString: function(tagName, tagValue)
	{
		return "<" + tagName + ">" + tagValue + "</" + tagName + ">";	
	}
	
	/*********************************************************************************************
	 * Serialize xml node to a string (browser portable)
     *
     * @param 	node - xml node to serialize to string      
     * @return 	string 
	 *********************************************************************************************/			
    ,serialize: function(node)
    {
		var xmlStr = null;
        if ( typeof XMLSerializer != "undefined" )
        {
            xmlStr = ( new XMLSerializer() ).serializeToString( node );
        }
        else if ( node.xml )
        {
            xmlStr = node.xml;
        }
        else
        {
            throw new Error ( "XML.serialize is not supported" );
        }
		return xmlStr;
    }
	
	/*********************************************************************************************
	 * Generate xml document from xml formatted string (browser portable)
     *
     * @param 	xmlStr - xml formatted string      
     * @return 	xml document
	 *********************************************************************************************/			
    ,stringToXML: function(xmlStr)
    {
		var xmlDoc = null;
        // standard (MOZ) method
        if ( typeof DOMParser != "undefined" )
        {
            // MOZ will throw error if xml is invalid
            xmlDoc = ( new DOMParser() ).parseFromString( xmlStr, "application/xml" );          
        }
        // IE method
        else if ( typeof ActiveXObject != "undefined" )
        {
            // create empty doc
            xmlDoc = IFDS.Xml.newDocument();
            xmlDoc.loadXML( xmlStr );
            // IE doesn't cause error directly, so test for documentElement
            if ( !xmlDoc.documentElement )
            {
                throw new Error("xml string is not valid");
            }            
        }
        // not supported
        else
        {
            throw new Error("XML parsing not supported");
        }
		return xmlDoc;
    }
	
	/*********************************************************************************************
	 * Return first XML node specified by xpath expression, relative to 
	 * the context (xml document or node)
     *
     * @param	context - xml node or xml document
     * @param 	xpathExpr - xpath expression      
     * @return 	xml node
	 *********************************************************************************************/			
	,getNode: function(context, xpathExpr)
    {		
        var xmldoc = null;
        var contextNode = null;
		
		if (context == null)
		{
			throw new Error("Specified context is null");
		}

        // context is a document
        if ( context.documentElement )
        {
            xmldoc = context;
            contextNode = context.firstChild;
        }
        // context is a node
        else
        {
            xmldoc = context.ownerDocument;
            contextNode = context;
        }

        // MOZ
        if( document.evaluate )
        {
        	var xpathExprObj = xmldoc.createExpression( xpathExpr, function(){return "";} );
        	var result = xpathExprObj.evaluate( contextNode, XPathResult.FIRST_ORDERED_NODE_TYPE, null );            
            return result.singleNodeValue;
        }
        // IE
        else
        {
            try
            {
            	xmldoc.setProperty( "SelectionLanguage", "XPath" );
                return contextNode.selectSingleNode( xpathExpr );
            }
            catch(e)
            {
                throw new Error("Invalid xpath expression, or xpath not supported");
            }
        }
    }
	
	/*********************************************************************************************
     * Return array of xml nodes specified by the xpath expression, within the given context.
     * 
     * @param 	context - xml node or xml document
     * @param 	xpathExpr - xpath expression     
     * @return	array
     *********************************************************************************************/
    ,getNodes: function(context, xpathExpr)
    {
        var xmldoc = null;
        var contextNode = null;
		
		if (context == null)
		{
			throw new Error("Specified context is null");
		}
        
        // context is a document
        if ( context.documentElement )
        {
            xmldoc = context;
            contextNode = context.documentElement;
        }
        // context is a node
        else
        {
            xmldoc = context.ownerDocument;
            contextNode = context;
        }
		
		var nodeArray = null;

        // MOZ
        if (document.evaluate )
        {
        	var xpathExprObj = xmldoc.createExpression( xpathExpr, function(){return "";} );
            var result = xpathExprObj.evaluate( contextNode, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null );
            var nodeArray = new Array( result.snapshotLength );
            for ( var i = 0; i < result.snapshotLength; i++ )
            {
                nodeArray[i] = result.snapshotItem( i );
            }            
        }
        // IE
        else
        {
            try
            {
            	xmldoc.setProperty( "SelectionLanguage", "XPath" );            	
                nodeArray = contextNode.selectNodes( xpathExpr );
            }
            catch(e)
            {
                throw new Error("Invalid xpath expression, or xpath not supported");
            }
        }
		
		return nodeArray;
    }
	
	/*********************************************************************************************
	 * Return string value in the node specified by the xpat expression
     *
     * @param	context - xml node or xml document
     * @param 	xpathExpr - (optional) xpath expression, defaults to current node      
     * @return 	string
	 *********************************************************************************************/			
	,getNodeValue: function(context, xpathExpr)
    {
		xpathExpr = (xpathExpr ? xpathExpr : ".");
						
		var value = "";
		var node = IFDS.Xml.getNode(context, xpathExpr);		
        if (node != null && node.firstChild != null)
		{
			value = node.firstChild.nodeValue;
		}
		return value;
    }

	/*********************************************************************************************
	 * Set value of specified xml node. Node must be leaf (ie. element node with no children)
     *
     * @param 	node - xml node
     * @param 	value - string value           
	 *********************************************************************************************/				 
    ,setNodeValue: function(node, value)
    {		
        if (node)
        {
            var xmlDoc = node.ownerDocument;
            if ( !node.firstChild )
            {
                node.appendChild( xmlDoc.createTextNode( value ) );
            }
            else if ( node.childNodes.length == 1 && node.firstChild.nodeType == 3 )  // TEXT NODE
            {
                node.firstChild.nodeValue = value;
            }     
			else
			{
				throw new Error("Cannot set value of specified node");
			}
        }
        else
        {
            throw new Error("Specified node is null");
        }
    }
    
    /*********************************************************************************************
     * Adds a node to the xmlDoc, based on given xpath expression and specified context. 
     * Returns reference to the newly added node.
     *
     * @param	context - xml document or node     
     * @param	nodeName - name of new node
     * @param	value - (optional) value of the new node
     * @return	xml node
     *********************************************************************************************/
    ,addSingleNode: function(context, nodeName, value)
    {
        var xmlDoc = null;
        var contextNode = null;
		
		if (context == null)
		{
			throw new Error("Specified context is null");
		}
		if (nodeName == null || nodeName.length == 0) 
		{
			throw new Error("Specified nodeName is invalid");
		}

        // context is a document
        if (context.documentElement)
        {
            xmlDoc = context;
            contextNode = context.firstChild;
        }
        // context is a node
        else
        {
            xmlDoc = context.ownerDocument;
            contextNode = context;
        }
		
		var newNode = contextNode.appendChild(xmlDoc.createElement(nodeName));
		
		if (value != null)
		{
			IFDS.Xml.setNodeValue(newNode, value);
		}
		
		return newNode;
    }
		
	/*********************************************************************************************
     * Adds a node to the xmlDoc if not already exists and then sets values.
     *
     * @param	context - xml document or node     
     * @param	nodeName - name of new node
     * @param	value - (optional) value of the new node
     * @return	xml node
     *********************************************************************************************/
	,replaceSingleNode: function(context, nodeName, nodeValue)
	{
		var node = IFDS.Xml.getNode(context, nodeName);
		if (node == null)
		{
			IFDS.Xml.addSingleNode(context, nodeName, nodeValue);
		}
		else
		{
			IFDS.Xml.setNodeValue(node, nodeValue);
		}
	}
         
    /*********************************************************************************************
     * Adds an attribute with given name and value to specified node
     *          
     * @param	node - xml node
     * @param 	attrName - attribute name
	 * @param 	attrVal - attribute value     
     *********************************************************************************************/
    ,addAttribute: function(node, attrName, attrVal)
    {
    	if (node != null)
    	{
    		if (attrName)    	
    		{
    			node.setAttribute(attrName, attrVal);
    		}
    		else
    		{
    			throw new Error("Specified attribute name is invalid");
    		}    	
    	}
    	else
    	{
    		throw new Error("Specified node is null");
    	}    	
    }
    /*********************************************************************************************
     * Remove attribute with given name  to specified node
     *          
     * @param	node - xml node
     * @param 	attrName - attribute name
     *********************************************************************************************/
	
	,removeAttribute: function(node, attrName)
    {
    	if (node != null)
    	{
    		if (attrName)    	
    		{
    			node.removeAttribute(attrName);
    		}
    		else
    		{
    			throw new Error("Specified attribute name is invalid");
    		}    	
    	}
    	else
    	{
    		throw new Error("Specified node is null");
    	}   
    }
	
	 /*********************************************************************************************
     * Deletes specified node from xml document
     *          
     * @param	node - xml node
     * @return 	xml node         
     *********************************************************************************************/
	,deleteNode: function(node)
	{		
		return node.parentNode.removeChild(node);
	}
	
	 /*********************************************************************************************
     * Appends specified node to xml document
     *          
     * @param	node - xml node
     * @return 	xml node         
     *********************************************************************************************/
	,appendNode: function(context, toBeAppended)
	{
		var xmlDoc = null;
        var contextNode = null;
		var toBeAppendedNode = null;
		
		if (context == null)
		{
			throw new Error("Specified context is null");
		}
		if (toBeAppended == null) 
		{
			throw new Error("Specified toBeAppended is invalid");
		}

        // context is a document
        if (context.documentElement)
        {
            xmlDoc = context;
            contextNode = context.firstChild;
        }
        // context is a node
        else
        {
            xmlDoc = context.ownerDocument;
            contextNode = context;
        }
		
		// toBeAppended is a document
		if (toBeAppended.documentElement)
		{
			toBeAppendedNode = toBeAppended.firstChild;
		}
		else
		{
			toBeAppendedNode = toBeAppended;
		}
		
		var newNode = null;
		// MOZ Method
		if ( typeof DOMParser != "undefined" )
        {
			var mozToBeAppeneded = xmlDoc.importNode(toBeAppendedNode, true);
			newNode = contextNode.appendChild(mozToBeAppeneded);
        }
        // IE method
        else if ( typeof ActiveXObject != "undefined" )
		{
			newNode = contextNode.appendChild(toBeAppendedNode);
		}					
		return newNode;
	}

    /*********************************************************************************************
	 * Return string value in the node specified by the xpat expression
     *
     * @param	context - xml node or xml document
     * @param 	xpathExpr - (optional) xpath expression, defaults to current node      
     * @return 	string
	 *********************************************************************************************/
	, getAttributeValue: function (context, xpathExpr) {
	    xpathExpr = (xpathExpr ? xpathExpr : ".");

	    var value = "";
	    var node = IFDS.Xml.getNode(context, xpathExpr);
	    if (node != null) {
	        value = node.nodeValue;
	    }
	    return value;
	}
}