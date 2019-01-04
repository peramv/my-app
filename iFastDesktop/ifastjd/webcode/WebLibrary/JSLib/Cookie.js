/** 
 * @fileoverview Contains Cookie class - for creating and using web page cookies
 *  
 * @author walkerro
 * @version 0.1 
 */




/**
 * Creates Cookie object with the given name. Looks in the document.cookie for any pre-existing
 * cookie with this name, and if so loads the content in the data map (_data)
 * @param {string} name name of the Cookie to be created/loaded
 *   
 * @class Class for retrieving, storing and removing cookies from web page. Once object has been
 * created, individual name/value pairs can be added and retreived.
 */
function Cookie( name )
{
	this._name = name;
	this._data = {};
	
	// look to see if cookie already stored
	var allcookies = document.cookie;
	
	// no cookies at all found
	if ( allcookies == "" ) return;
	
	
	var cookiesArray = allcookies.split( ";" );	
	var cookie = null;
	for ( var i = 0; i < cookiesArray.length; i++ )
	{	    	     
		if ( UTL.trimString( cookiesArray[i].substring( 0, name.length + 2 ) ) == ( name + "=" ) )
		{			    
			cookie = cookiesArray[i];
			break;
		}
	}
	
	// cookie not found
	if ( cookie == null ){ return;}
	
	// get the values out of the stored cookie, store in map object	
	var cookieVal = cookie.substring( name.length + 1 );
	var nameValuePairsArray = cookieVal.split( "&" );
	for ( var i = 0; i < nameValuePairsArray.length; i++ )
	{
		var nameValuePair = nameValuePairsArray[i].split( ":" );
		// decode the value here, and encode it when storing		
		this._data[nameValuePair[0]] = decodeURIComponent( nameValuePair[1] );
	} 	
}



/**
 * Method for adding a name/value pair to the cookie object
 * @param {string} name 
 * @param {string} value
 */
Cookie.prototype.add = function( name, value )
{
	if ( !name || name.length == 0 ) 
		throw new Error( Err.genErrMsg( "invalid name", "add()", "Cookie.js" ) );
		
	if ( !value || value.length == 0 ) 
		throw new Error( Err.genErrMsg( "invalid value", "add()", "Cookie.js" ) );
		
	this._data[name] = value; 
}



/**
 * Method for retreiving a value from a name/value pair stored in this cookie object
 * @param {string} name  
 */
Cookie.prototype.get = function( name )
{	
	if ( !name || name.length == 0 )
		throw new Error( Err.genErrMsg( "invalid name", "get()", "Cookie.js" ) );
		
	return this._data[name];	
}



/**
 * Method for storing the cookie data to the web page (document.cookie) 
 * @param {integer} daysToLive (optional) number of days this cookie should be stored.
 * If no value specified, cookie will only persist for this session.
 * @param {string} path (optional) specifies which web pages the cookie will be associated
 * If no value specified, cookie will only work for the page in which created
 * @param {string} domain (optional) further specification of which web pages the cookie will be associated
 * If no value specified, cookie will only work for the path specified
 * @param {boolean} secure (optional) specify how the data should be transmitted
 * If no value specified, cookie is not securely transmitted  
 */
Cookie.prototype.store = function( daysToLive, path, domain, secure )
{
	var cookieVal = "";
	for( var prop in this._data )
	{
		if( cookieVal != "" )
		{
			cookieVal += "&";
		}
		cookieVal += prop + ":" + encodeURIComponent( this._data[prop] ); 
	}
	
	var cookie = this._name + "=" + cookieVal;
	
	if ( daysToLive || daysToLive == 0 )
	{
		if( isNaN( daysToLive ) )
		{
			throw new Error( Err.genErrMsg( "daysToLive is not a number", "store()", "Cookie.js" ) );
		}	
		// max-age actually 
		cookie += "; max-age=" + ( daysToLive * 24 * 60 * 60 );
	}
	
	if ( path )
	{
		cookie += "; path=" + path;		
	}
	
	if ( domain )
	{
		cookie += "; domain=" + domain;		
	}
	
	if ( secure )
	{
		cookie += "; secure";
	}
	
	document.cookie = cookie;	
}



/**
 * Method for removing a stored cookie - stores it for 0 days
 * @param {string} path value matching the currently stored cookie
 * @param {string} domain value matching the currently stored cookie
 * @param {boolean} secure value matching the currently stored cookie  
 */
Cookie.prototype.remove = function( path, domain, secure )
{
	// clear out this._data
	for( var i in this._data )
	{
		delete this._data[i];
	}
	// removed stored cookie - store the cookie with 0 lifetime
	this.store( 0, path, domain, secure );
}



/**
 * Static method for testing Cookie functionality in the current browser  
 */
Cookie.enabled = function()
{
	// not all browsers have cookieEnabled feature
	if ( navigator.cookieEnabled != undefined )
	{
		return navigator.cookieEnabled;
	}
	
	// other alternative is to save a 'test' cookie or use our cached result if called previously
	if( Cookie.enabled.cacheResult != undefined )
	{
		return Cookie.enabled.cacheResult;
	}
	
	// create cookie
	document.cookie = "testcookie=test; max-age=10000";
	// test it was saved
	var cookies = document.cookie;
	if ( cookies.indexOf( "testcookie=test" ) == -1 )
	{
		// not saved - no cookies
		return Cookie.enabled.cacheResult = false;		
	}
	else
	{
		// saved - delete (ie. set max-age to 0) testcookie before returning
		document.cookie = "testcookie=test; max-age=0";
		return Cookie.enabled.cacheResult = true;
	}	
}
