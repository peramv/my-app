/**
 * @fileoverview Contains browser portable code for working with XML in Javascript,
 * includes base singleton class XML, and inner classes Transformer (for working with XSLT)
 * and XPathExpression (for working with XPath).
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b>
 *
 * @author walkerro
 */



/**
 * Static class - constructor not required.
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b>
 *
 * @class Static class used to hold cross browser XML handling javascript functions
 */
var XML = new function()
{

    /**
     * Constant used to identify "element" node
     * @type integer
     */
    this.ELEMENT_NODE                   = 1;

    /**
     * Constant used to identify "attribute" node
     * @type integer
     */
    this.ATTRIBUTE_NODE                 = 2;

    /**
     * Constant used to identify "text" node
     * @type integer
     */
    this.TEXT_NODE                      = 3;

    /**
     * Constant used to identify "CDATA" node
     * @type integer
     */
    this.CDATA_SECTION_NODE             = 4;

    /**
     * Constant used to identify "processing instruction" node
     * @type integer
     */
    this.PROCESSING_INSTRUCTION_NODE    = 7;

    /**
     * Constant used to identify "comment" node
     * @type integer
     */
    this.COMMENT_NODE                   = 8;

    /**
     * Constant used to identify "document" node
     * @type integer
     */
    this.DOCUMENT_NODE                  = 9;

    /**
     * Constant used to identify "document type" node
     * @type integer
     */
    this.DOCUMENT_TYPE_NODE             = 10;

    /**
     * Constant used to identify "document fragment" node
     * @type integer
     */
    this.DOCUMENT_FRAGMENT_NODE         = 11;
    


    /**
     * Simple helper function for encoding special xml characters
     *
     * @param {string} origXMLStr
     * @return {string}
     */    
    this.charEncode = function( origXMLStr )
    {
        // replace "&" with "&amp;"
        var encodedXML = origXMLStr.replace( /&/g, "&amp;" );
        // replace "<" with "&lt;"
        encodedXML = encodedXML.replace( /</g, "&lt;" );
        // replace ">" with "&gt;"
        encodedXML = encodedXML.replace( />/g, "&gt;" );
                
        return encodedXML; 
    }
    
    
    
    /**
     * Simple helper function for encoding special xml characters
     *
     * @param {string} origXMLStr
     * @return {string}
     */    
    this.charDecode = function( encodedXMLStr )
    {
        // replace "&" with "&amp;"
        var decodedXML = encodedXMLStr.replace( /&amp;/g, "&" );
        // replace "<" with "&lt;"
        decodedXML = decodedXML.replace( /&lt;/g, "<" );
        // replace ">" with "&gt;"
        decodedXML = decodedXML.replace( /&gt;/g, ">" );
                
        return decodedXML; 
    } 



    /**
     * Simple helper function for constructing an xml element formatted string
     * with given tagName and content, or empty if content not given.
     *
     * @param {string} tagName Tag name used in xml element string
     * @param {string} content (optional) content inside element string
     * @return {string}
     */
    this.createNodeStr = function( tagName, content )
    {
        if( tagName && tagName.length > 0 )
        {
            if( content && content.length > 0)
            {
                return "<" + tagName + ">" + content + "</" + tagName + ">";
            }
            // empty tag
            else
            {
                return "<" + tagName + "/>";
            }
        }
        else
        {
            throw new Error( Err.genErrMsg( "Invalid tag name", "createNodeStr()", "XML.js" ) );
        }
    }



    /**
     * Browser portable function to create an empty xml document object
     * with a rootTag, if provided.
     *
     * @param {string} rootTagName (optional) tag name given to root node
     * @return {document}
     */
    this.newDocument = function( rootTagName )
    {
        // use "" if not specified
        rootTagName = rootTagName ? rootTagName : "";

        // standard method
        if ( document.implementation && document.implementation.createDocument )
        {
            return document.implementation.createDocument( "", rootTagName, null );
        }
        // IE specific method
        else
        {
            var doc = new ActiveXObject( "MSXML2.DOMDocument" );

            if( rootTagName.length > 0 )
            {
                doc.loadXML( "<" + rootTagName + "/>" );
            }

            return doc;
        }
    }



    /**
     * Serialize xml node to a string
     *
     * @param {XML node} node
     * @return {string}
     */
    this.serialize = function( node )
    {
        if ( typeof XMLSerializer != "undefined" )
        {
            return ( new XMLSerializer() ).serializeToString( node );
        }
        else if ( node.xml )
        {
            return node.xml;
        }
        else
        {
            throw new Error ( Err.genErrMsg( "XML.serialize is not supported", "serialize()", "XML.js" ) );
        }
    }



    /**
     * Builds a javascript object from a simple xml, based on the given xmlNode.
     * <br/>
     * Restrictions: xmlNode muste either be Element Node or Document Node. xml can only contain
     * Element Nodes and/or Text Nodes (ie. no attributes or CDATA )
     * <br/> &gt;
     * Example: &lt;xml&gt;&lt;fund&gt;name&lt;details&gt;&lt;code&gt;123&lt;/code&gt;&lt;class&gt;AB&lt;/class&gt;&lt;/details&gt;&lt;/fund&gt;&lt;/xml&gt;
     * generates {fund: {<TEXT>: name, details: { code: 123, class: AB } } }
     *
     * @param {Node} xmlNode root node from which to construct
     * @return {Object}
     */
    this.buildJSON = function( xmlNode )
    {
        if ( xmlNode && xmlNode.nodeType )
        {
            if ( xmlNode.nodeType == XML.DOCUMENT_NODE )
            {
                xmlNode = xmlNode.documentElement;
            }

            if ( xmlNode.nodeType == XML.ELEMENT_NODE )
            {
                var retObj = {};
                for ( var i = 0; i < xmlNode.childNodes.length; i++ )
                {
                    var contentNode = xmlNode.childNodes[i];
                    if ( contentNode.nodeType == XML.ELEMENT_NODE )
                    {
                    	var propName = contentNode.nodeName;
                    	
                    	var propVal = null;
                    	// empty node
                        if ( contentNode.childNodes.length == 0 )
                        {
                            propVal = "";
                        }
                        // simple node
                        else if ( contentNode.childNodes.length == 1 && contentNode.childNodes[0].nodeType == XML.TEXT_NODE )
                        {
                            propVal = contentNode.childNodes[0].nodeValue;
                        }
                        // complex node
                        else
                        {
                            propVal = XML.buildJSON( contentNode );
                        }
                    	
                    	// propName already exists in retObj
                    	if ( retObj[propName] )
                    	{                    		
                    		// and its already an array
							if ( UTL.isArray( retObj[propName] ) )
							{
								var array = retObj[propName];
								array[array.length] = propVal;								
							}
							// not yet an array, need to make it so
							else
							{
								var temp = retObj[propName];
								retObj[propName] = new Array();
								retObj[propName][0] = temp;
								retObj[propName][1] = propVal;
							}							                    	
                    	}
                    	else
                    	{
                    		retObj[propName] = propVal;
                    	}
                    }
                    else if (contentNode.nodeType == XML.TEXT_NODE )
                    {
                        if( retObj["<TEXT>"] )
                        {
                            retObj["<TEXT>"] += contentNode.nodeValue;
                        }
                        else
                        {
                            retObj["<TEXT>"] = contentNode.nodeValue;
                        }
                    }
                    else
                    {
                        throw new Error( Err.genErrMsg( "invalid xml contents", "buildJSON()", "XML.js" ) );
                    }
                }
                return retObj;
            }
        }

        throw new Error( Err.genErrMsg( "invalid xmlNode", "buildJSON()", "XML.js" ) );
    }
    
    this.buildXMLFromJSON = function( parentXMLNode, obj )
    {
    	for ( var i in obj )
    	{    		
    		if ( UTL.isArray( obj[i] ) )
    		{
    			var array = obj[i];
    			for ( var j = 0; j < array.length; j++ )
    			{
    				var childNode = XML.addNode( i, parentXMLNode );
    				this.buildXMLFromJSON( childNode, array[j] );
    			}
    		}	
    		else if ( UTL.isObject( obj[i] ) )    		
    		{
    			var childNode = XML.addNode( i, parentXMLNode );
    			this.buildXMLFromJSON( childNode, obj[i] );
    		}
    		else
    		{
    			var childNode = XML.addNode( i, parentXMLNode );
    			XML.setNodeValue( obj[i], childNode );
    		}
    	}
    }



    /**
     * Browser portable function for generating xml document from xml formatted text string
     *
     * @param {string} text XML formatted text
     * @return {document}
     */
    this.parseToXML = function( text )
    {
        // standard (MOZ) method
        if ( typeof DOMParser != "undefined" )
        {
            // MOZ will throw error if xml is invalid
            var xml = ( new DOMParser() ).parseFromString( text, "application/xml" );
            return xml;
        }
        // IE method
        else if ( typeof ActiveXObject != "undefined" )
        {
            // create empty doc
            var xml = XML.newDocument();
            xml.loadXML( text );
            // IE doesn't cause error directly, so test for documentElement
            if ( !xml.documentElement )
            {
                throw new Error ( Err.genErrMsg( "xml is not valid", "parseToXML()", "XML.js" ) );
            }
            else
            {
                return xml;
            }
        }
        // not supported
        else
        {
            throw new Error( Err.genErrMsg( "XML parsing not supported", "XML.parseToXML()", "XML.js" ) );
        }
    }
    
    
    /**
     * Get the node specified by the xpath expression, within the given context.
     * Note: context must be either Element node or Document node, and the xpathExpr should not reference
     * the root node of the context. Also, if there are multiple matches, will only return the first.
     *
     * @param {string} xpathExpr String representing xpath expression
     * @param {document/Node} context Either document or Node to run expression on, if document
     * then expression is run on root node
     * @return {XML node}
     */
    this.getNode = function( xpathExpr, context )
    {
        var xmldoc = null;
        var contextNode = null;

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
                throw new Error( Err.genErrMsg( "XPath not supported", "getNodes()", "XML.js" ) );
            }
        }
    }


    /**
     * Get the nodes specified by the xpath expression, within the given context.
     * Note: context must be either Element node or Document node, and the xpathExpr should not reference
     * the root node of the context.
     *
     * @param {string} xpathExpr String representing xpath expression
     * @param {document/Node} context Either document or Node to run expression on, if document
     * then expression is run on root node
     * @return {XML node Array}
     */
    this.getNodes = function( xpathExpr, context )
    {
        var xmldoc = null;
        var contextNode = null;
        
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

        // MOZ
        if (document.evaluate )
        {
        	var xpathExprObj = xmldoc.createExpression( xpathExpr, function(){return "";} );
            var result = xpathExprObj.evaluate( contextNode, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null );
            var a = new Array( result.snapshotLength );
            for ( var i = 0; i < result.snapshotLength; i++ )
            {
                a[i] = result.snapshotItem( i );
            }
            return a;
        }
        // IE
        else
        {
            try
            {
            	xmldoc.setProperty( "SelectionLanguage", "XPath" );            	
                return contextNode.selectNodes( xpathExpr );
            }
            catch(e)
            {
                throw new Error( Err.genErrMsg( "XPath not supported", "XML.XpathExpression.getNodes()", "XML.js" ) );
            }
        }
    }



    /**
     * Adds a root node, with given name, to the xmlDoc.
     *
     * @param {string} rootNodeName name to be given to the root node
     * @param {XMLDoc} xmlDoc empty xml document
     * @return {document}
     */
    this.addRootNode = function( rootNodeName, xmlDoc )
    {
        if ( xmlDoc.documentElement || xmlDoc.nodeType == this.DOCUMENT_NODE )
        {
            if ( xmlDoc.firstChild )
            {
                throw new Error( Err.genErrMsg( "root node already exists", "addRootNode()", "XML.js" ) );
            }
            return xmlDoc.appendChild( xmlDoc.createElement( rootNodeName ) );
        }
        else
        {
            throw new Error( Err.genErrMsg( "xmlDoc is not valid", "addRootNode()", "XML.js" ) );
        }
    }


    /**
     * Adds a node to the xmlDoc, based on given xpath expression. Returns reference to the newly added node.
     * Note: xpath expression does not need to specify root node.
     * <br/>
     * Example: "test1/test2" added to <xml/> = &lt;xml&gt;&lt;test1&gt;&lt;test2/&gt;&lt;/test1&gt;&lt;/xml&gt;
     *
     * @param {string} xpathExpr xpath expression of the path and node to be added
     * @param {XML Node} context Either Element node or Document node
     * @return {XML Node}
     */
    this.addNode = function( xpathExpr, context )
    {
        var xmlDoc = null;
        var contextNode = null;

        // context is a document
        if ( context.documentElement || context.nodeType == this.DOCUMENT_NODE )
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

        // look to see if node with same path already exists
        // if so, just add a sibling to it
        var node = this.getNode( xpathExpr, context )
        if ( node )
        {
            return node.parentNode.appendChild( xmlDoc.createElement( node.nodeName ) );
        }
        else
        {
            var parentNode = contextNode;
            if ( parentNode )
            {
                // step thru xpath until reach a node that doesn't already exist
                var xpathExprComponentArray = xpathExpr.split( "/" );
                node = this.getNode( xpathExprComponentArray[0], context );
                var i = 0;
                while ( node )
                {
                    i++;
                    parentNode = node;
                    node = this.getNode( xpathExprComponentArray[i], node );
                }

                // add the nodes which don't already exist
                while( i < xpathExprComponentArray.length )
                {
                    var part = xpathExprComponentArray[i++];

                    // create nodes if needed
                    var iIdxSquareBrkt = part.indexOf( "[" );

                    if ( iIdxSquareBrkt != -1 )
                    {
                      var partNumber = Number( parseInt( part.substring( iIdxSquareBrkt + 1, part.indexOf( "]" ) ) ) );
                      if ( !isNaN( partNumber ) )
                      {   
                      	  // IE is 0 based, MOZ is 1 based                                       
	                      partNumber = ( document.evaluate ? partNumber : partNumber - 1 );	                      
	                      var partName   = part.substring( 0, iIdxSquareBrkt );
						  
	                      var iExisting = this.getNodes( partName, parentNode ).length;
	
	                      for( var iCounter = iExisting; iCounter <= partNumber; iCounter++ )
	                      {
	                        node = parentNode.appendChild( xmlDoc.createElement( partName ) );
	                      }
	
	                      parentNode = node;
	                  }
	                  else
	                  {
	                  	throw new Error( Err.genErrMsg( "invalid node index given in xpathExpr", "addNode()", "XML.js" ) );
	                  }
                    }
                    else
                    {
                      node = parentNode.appendChild( xmlDoc.createElement( part ) );
                      parentNode = node;
                    }
                }
                return node;
            }
            else
            {
                throw new Error( Err.genErrMsg( "context node is null, or document as no root node", "addNode()", "XML.js" ) );
            }
        }
    }
    
    
    /**
     * Sets the value (ie. Text node) of the given Element node. Throws error if node is not simple
     * Element node.
     *
     * @param {string} valueStr value string     
     * @param {XML Node} node Element node to set the value of
     */
    this.setNodeValue = function( valueStr, node )
    {
        if ( node && node.nodeType == this.ELEMENT_NODE )
        {
            var xmlDoc = node.ownerDocument;
            if ( !node.firstChild )
            {
                node.appendChild( xmlDoc.createTextNode( valueStr ) );
            }
            else if ( node.childNodes.length == 1 && node.firstChild.nodeType == this.TEXT_NODE )
            {
                node.firstChild.nodeValue = valueStr;
            }
            else
            {
                throw new Error( Err.genErrMsg( "cannot set value of complex node", "setNodeValue()", "XML.js" ) );
            }
        }
        else
        {
            throw new Error( Err.genErrMsg( "node is invalid", "setNodeValue()", "XML.js" ) );
        }
    }
    
    
    /**
     * Adds an attribute with given name and value to specified node
     *          
     * @param {string} attrName attribute name
     * @param {string} attrVal attribute value
	 * @param {XML Node} node Element node to add the attribute to     
     */
    this.addAttribute = function( attrName, attrVal, node )
    {
    	if ( node != null )
    	{
    		if ( attrName )    	
    		{
    			node.setAttribute( attrName, attrVal );
    		}
    		else
    		{
    			throw new Error( Err.genErrMsg( "invalid attribute name", "getAttribute()", "XML.js" ) );
    		}    	
    	}
    	else
    	{
    		throw new Error( Err.genErrMsg( "node is null", "getAttribute()", "XML.js" ) );
    	}    	
    }
    

    /**
     * Get the value of an attribute with given name on the specified node
     *    
     * @param {string} attrName attribute name
     * @param {XML Node} node Element node to the attribute from          
     */    
    this.getAttrbute = function( attrName, node )
    {
    	if ( node != null )
    	{
    		return node.getAttribute( attrName );
    	}
    	else
    	{
    		throw new Error( Err.genErrMsg( "node is null", "getAttribute()", "XML.js" ) );
    	}
    }
    
    
    this.isLeafNode = function( node )
    {               
        if ( node.nodeType == XML.ELEMENT_NODE )
        {
            if ( node.childNodes.length > 1 )
            {
                return false;
            }
            else if ( node.childNodes.length == 1 )
            {
                return ( node.firstChild.nodeType == XML.TEXT_NODE );
            }
            else
            {
                return true;
            }                       
        }
        else
        {
            return false;
        }        
    }
        
    /**
     * Creates a node and sets the value - combines addNode and setNodeValue
     *          
     * @param {string} xpathExpr xpath expression of the path and node to be added
     * @param {XML Node} context Either Element node or Document node
     * @param {string} node value
     * @return {XML Node}
     */
    this.addNodeWithValue = function( xpathExpr, context, value )
    {
    	var node = XML.addNode( xpathExpr, context );
    	XML.setNodeValue( value, node );
    	
    	return node;
    }
}