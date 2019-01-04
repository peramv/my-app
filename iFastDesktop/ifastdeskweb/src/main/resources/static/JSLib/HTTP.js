/** 
 * @fileoverview Contains browser portable code for doing HTTP (AJAX) requests
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b>
 *   
 * @author walkerro 
 */


/**
 * Static class - constructor not permitted
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b>
 *  
 * @class Static class used to hold HTTP-AJAX functions
 */
var HTTP = new function()
{
	/**
	 * Constant used to identify "POST" requests
	 * @type string
	 */
	this.POST 	= "POST";
	
	
	/**
	 * Constant used to identify "GET" requests
	 * @type string
	 */
	this.GET 	= "GET";


	/**
	 * @private
	 */
	var _factory = null;


	/**
	 * @private
	 */
	var _factories = [
		function(){ return new XMLHttpRequest(); },
		function(){ return new ActiveXObject( "Msxml2.XMLHTTP" ); },
		function(){ return new ActiveXObject( "Microsoft.XMLHTTP" ); }
	];
	
	
	/**
	 * @private
	 */
	var _newRequest = function()
	{
		// already determined correct factory on previous call		
		if ( _factory != null ) 
		{
			return _factory();
		}
		
		for ( var i = 0; i < _factories.length; i++ )
		{
			try
			{
				var factory = _factories[i];
				var request = factory();
				if ( request != null)
				{
					_factory = factory;
					return request;
				}
			}
			catch( e )
			{
				continue;
			}
		}
		
		_factory = function(){ throw new Error( Err.genErrMsg( "XMLHttpRequest not supported", "newRequest()", "HTTP.js" ) ); }
		
		_factory(); 	 	
	}
	// in case any existing screens are calling this directly (they shouldn't be)
	this.newRequest = _newRequest();

		
	/**
	 * @private
	 * Deprecated
	 */
	var _performRequest = function(url, callbackFunc, requestType, sendData, responseType, asynch, debugOn )
    {  	
        var request = _newRequest();
        var callbackWrap = function()
        				{
        					if ( request.readyState == 4 && request.status == 200)
        					{
        						if ( debugOn )
        						{
        							prompt( "HTTP request response:", request.responseText );
        						}			        																					
        						callbackFunc( responseType == "text" ? request.responseText : request.responseXML );
        					}
        				}
        request.onreadystatechange = callbackWrap;
        
        if ( asynch == null )
        {
            asynch = true;
        }
        request.open( requestType, url, asynch );
        request.send( sendData );
  	}
  	
  	
  	/**
     * Takes requestObj, and data (only for POST) and creates/executes http request.
     * <br/>
     * Note: this should not be called directly, instead use send() method of the AJAX Request object.
     *
     * @param {object} requestObj AJAX.Request object
     * @param {string} data string to be sent with request, used only with POST requests      
     */
	this._performRequest_new = function( requestObj, data )
	{
		var httpReq = _newRequest();
		httpReq.open( requestObj.getType(), requestObj.getURL(), requestObj.isAsynch() );
		
		if ( requestObj.getHeaders() )
		{
			var headersMap = requestObj.getHeaders();
			for ( var i in headersMap )
			{
				httpReq.setRequestHeader( i, headersMap[i] );
			}
		} 
		
		var callbackFn = requestObj.getCallbackFunction();
		var callbackWrapper = null;
		if ( callbackFn )
		{
			callbackWrapper = function()
			{			
				if ( httpReq.readyState == 4 && httpReq.status == 200 && !requestObj.isCancelled() )
				{				
					callbackFn( httpReq.responseText ); 
				}
				else if ( httpReq.readyState == 4 && httpReq.status != 200 )
				{
					alert( "HTTP error: " + httpReq.status + " - " + httpReq.statusText );							
				}			
			}
		}
		
		if ( requestObj.isAsynch() )
		{			
			httpReq.onreadystatechange = callbackWrapper;
			httpReq.send( data );
		}
		else
		{
			httpReq.send( data );
			if ( callbackWrapper )
			{			
				callbackWrapper();
			}
		}
	}	

	
	
    /**
     * Creates a url string (ie. "servletPath?name1=val1&name2=val2 ...")
     * 
     * @param {string} servletPath
     * @param {object} paramMap
     * @return {string}
     */	
	this.buildURL = function( servletPath, paramMap )
	{
	    return servletPath + "?" + this.buildURLParamString( paramMap );
	}


	
	/**
     * Creates a string of url parameters (name=val), where the name/values
     * pairs are taken from the key/value items in the paramMap
     *
     * @param {object} paramMap   
     * @return {string}  
     */
	this.buildURLParamString = function( paramMap )
	{
		var s = "";
		for ( var i in paramMap )
		{			
			s = ( ( s.length > 0 ) ? s + "&" : "" ) + i + "=" + paramMap[i];  
		}
		return s;
	}
	


	/**
     * Creates a param string from the paramMap 
     * and appends to the existing URL
     *
     * @param {string} urlStr
     * @param {object} paramMap   
     * @return {string}  
     */	
	this.appendParamToURL = function( urlStr, paramMap )
	{
		return urlStr + "&" + this.buildURLParamString( paramMap)
	}

	
	    
    /**
     * <b>**Deprecated</b>
     * <br/>
     * Makes HTTP request object, and issues GET to given url, and calls callbackFunc
     * as part of the response handler,passing the response as a string parameter          
     *
     * @param {string} url url to send GET request
     * @param {function} callbackFunc function reference, that should be expecting response string as a parameter
     * @param {boolean} asynch (optional) boolean flag indicating whether to perform Ajax call asynchronous or synchronous,
     * default is true
     * @param {boolean} debugOn (optional) boolean flag to indicate whether to display  prompt is given containing the HTTP response text,
     * default is false 
     */
    this.getText = function( url, callbackFunc, asynch, debugOn )
    {            	
    	_performRequest( url, callbackFunc, "GET", null, "text", asynch, debugOn );
    }
    
    
    
    /**
     * Makes HTTP request object, and issues GET to given url, and calling callbackFunc
     * as part of the response handler and passing the response as an XML DOM object parameter.
     * @param {string} url url to send GET request to
     * @param {function} callbackFunc reference, expecting response XML DOM as a parameter
     * @param {boolean} asynch (optional) boolean flag indicating whether to perform Ajax call asynchronous or synchronous,
     * default is true
     * @param {boolean} debugOn (optional) boolean flag to indicate if a debug prompt is given containing the HTTP response text,
     * default is false 
     */
    this.getXML = function( url, callbackFunc, asynch, debugOn )
    {	
    	_performRequest( url, callbackFunc, "GET", null, "xml", asynch, debugOn );
    }
    
    
    
    /**
     * <b>**Deprecated</b>
     * <br/>
     * Makes HTTP request object, and issues POST to given url, and calling callbackFunc
     * as part of the response handler and passing the response as a string parameter.
     * 
     * @param {string} url url to send GET request to
     * @param {function} callbackFunc reference, expecting response string as a parameter
     * @param {boolean} asynch (optional) boolean flag indicating whether to perform Ajax call asynchronous or synchronous,
     * default is true
     * @param {boolean} debugOn (optional) boolean flag to indicate if a debug prompt is given containing the HTTP response text,
     * default is false 
     */
    this.postText = function( url, callbackFunc, data, asynch, debugOn )
    {    	
    	_performRequest( url, callbackFunc, "POST", data, "text", asynch, debugOn );
    }
    
    
    /**
     * Makes HTTP request object, and issues POST to given url, and calling callbackFunc
     * as part of the response handler and passing the response as an XML DOM parameter.
     * @param {string} url url to send GET request to
     * @param {function} callbackFunc reference, expecting response XML DOM as a parameter
     * @param {boolean} asynch (optional) boolean flag indicating whether to perform Ajax call asynchronous or synchronous,
     * default is true
     * @param {boolean} debugOn (optional) boolean flag to indicate if a debug prompt is given containing the HTTP response text,
     * default is false 
     */
    this.postXML = function( url, callbackFunc, data, asynch, debugOn )
    {
    	_performRequest( url, callbackFunc, "POST", data, "xml", asynch, debugOn );
    }
}



/**
 * Wrapper function for creating an HTTP.Request with requestType = POST
 *
 * @param {string} url   
 * @return {HTTP.Request}  
 */
HTTP.getPOSTRequest = function( url )
{
	return new HTTP.Request( HTTP.POST, url );
}


/**
 * Wrapper function for creating an HTTP.Request with requestType = GET
 *
 * @param {string} url   
 * @return {HTTP.Request}  
 */
HTTP.getGETRequest = function( url )
{
	return new HTTP.Request( HTTP.GET, url );
}


/**  
 * @class Represents an Ajax request object
 * 
 * @param {string} requestType
 * @param {string} url 
 */
HTTP.Request = function( requestType, url )
{
	this._type 				= null;
	this._url 				= null;
	this._asynch 			= null;
	this._headersMap 		= null;
	this._callbackFunc		= null;
	this._cancelled         = null;			
	
	switch( requestType.toUpperCase() )
	{
		case HTTP.POST:
		{
			this._type = HTTP.POST;
			break;
		}
		case HTTP.GET:
		{
			this._type = HTTP.GET;
			break;			
		}
		default:
		{
			throw new Error( Err.genErrMsg( "invalid request type", "HTTP.Request()", "HTTP.js" ) );
		}
	}
	
	if ( url && (typeof url).toLowerCase() == "string" )
	{
		this._url = url;
	}
	else
	{
		throw new Error( Err.genErrMsg( "invalid url", "HTTP.Request()", "HTTP.js" ) );
	}
		
	this._asynch 		= true; 	
	this._cancelled     = false;	
}


/**
 * Returns the request type
 *   
 * @return {string}  
 */
HTTP.Request.prototype.getType = function()
{
	return this._type;
}


/**
 * Returns the request url
 *   
 * @return {string}  
 */
HTTP.Request.prototype.getURL = function()
{
	return this._url;
}


/**
 * Sets request to be aynchronous or not
 *   
 * @param {boolean} asynch  
 */
HTTP.Request.prototype.setAsynch = function( asynch )
{
	this._asynch = asynch;
}


/**
 * Returns boolean indicating if request is asynchronous
 *   
 * @return {boolean}  
 */
HTTP.Request.prototype.isAsynch = function()
{
	return this._asynch;
}


/**
 * Sets headers used in the request
 *   
 * @param {object} headersMap  
 */
HTTP.Request.prototype.setHeaders = function( headersMap )
{
	this._headersMap = headersMap;
}


/**
 * Returns header map object
 *   
 * @return {object}  
 */
HTTP.Request.prototype.getHeaders = function()
{
	return this._headersMap;
}


/**
 * Adds a header and value to the request
 *
 * @param {string} headerName
 * @param {string} value    
 */
HTTP.Request.prototype.addHeader = function( headerName, value)
{
	if( !this._headersMap )
	{
		this._headersMap = {};
	}
	
	this._headersMap[headerName] = value;
}


/**
 * Returns the value set for the given header
 *
 * @param {string} headerName
 * @return {string}    
 */
HTTP.Request.prototype.getHeaderValue = function( headerName )
{
	if( this._headersMap )
	{
		return this._headersMap[headerName];	
	}
	
	return undefined;	
}


/**
 * Sets callback function of the request
 *   
 * @param {object} headersMap  
 */
HTTP.Request.prototype.setCallbackFunction = function( callbackFn )
{
	this._callbackFunc = callbackFn;
}


/**
 * Returns reference to callback function
 *   
 * @return {object}  
 */
HTTP.Request.prototype.getCallbackFunction = function()
{
	return this._callbackFunc;
}


HTTP.Request.prototype.cancel = function()
{
    this._cancelled = true;
}


HTTP.Request.prototype.isCancelled = function()
{
    return this._cancelled;
}


/**
 * Sends http request, with given data
 *   
 * @return {string} data (optional)  
 */
HTTP.Request.prototype.send = function( data )
{
	if ( this._type != HTTP.POST && data != null )
	{
		throw new Error( Err.genErrMsg( "unable to send data with " + this._type + " request", "HTTP.Request.send()", "HTTP.js" ) );
	}
	HTTP._performRequest_new( this, data );
}














