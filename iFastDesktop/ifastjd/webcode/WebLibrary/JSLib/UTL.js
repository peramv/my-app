/** 
 * @fileoverview Contains basic JS helper and utility functions wrapped in UTL object.
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b>
 *  
 * @author walkerro
 */

/**
 * Static class - constructor not permitted
 *  
 * @class Static class used to hold utility functions
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b> 
 */
var UTL = new function()
{
	/** 	 
	 * @type string  
	 */
	this.GET_ELEM_SEARCH_TYPE_ID = "ID";	
	/** 
	 * @type string  
	 */
	this.GET_ELEM_SEARCH_TYPE_TAGNAME = "TAGNAME";
	/** 
	 * @type string 
	 */
	this.GET_ELEM_SEARCH_TYPE_NAME = "NAME";
	
	
	/** 
	 * @type string 
	 */
	this.COMPARE_NUMERIC = "numeric";
	/** 
	 * @type string 
	 */
	this.COMPARE_CURRENCY = "currency";
	/** 
	 * @type string 
	 */
	this.COMPARE_DATE = "date";
	/** 
	 * @type string 
	 */
	this.COMPARE_STRING = "string";
	/** 
	 * @type string 
	 */
	this.COMPARE_STRING_IGNORE_CASE = "string no case";
	
	
	
	/**
	 * Wrapper function for the various document.getElement(s)By functions. 
	 *  - getElementById (searchType = "ID" or not specified, ie. default)
	 *  - getElementsByTagName (searchType = "TAGNAME")
	 *  - getElementsByName (searchType = "NAME")
	 * 
	 * @param {string} searchVal String used to lookup element in the document.
	 * @param {string} searchType Optional string specify lookup type - "ID" is used if not given.
	 * @return {document} element reference
	 */
	this.getElem = function( searchVal, searchType )
	{
		if( !searchVal )
		{
			throw new Error( Err.genErrMsg( "searchVal not provided", "UTL.getElem()", "UTL.js" ) );
		}
		
		var searchType = ( searchType ) ? searchType : this.GET_ELEM_SEARCH_TYPE_ID;    
		 					  
			
		switch ( searchType )
		{
			case this.GET_ELEM_SEARCH_TYPE_ID:
			{
				return document.getElementById( searchVal );				
			}
			case this.GET_ELEM_SEARCH_TYPE_TAGNAME:
			{
				return document.getElementsByTagName( searchVal );
			}
			case this.GET_ELEM_SEARCH_TYPE_NAME:
			{
				return document.getElementsByName( searchVal );
			}				
		}
		
		throw new Error( Err.genErrMsg( "Invalid search type", "UTL.getElem()", "UTL.js" ) );
	}

	
	/**
	 * Browser portable function for getting array of all the elements in the DOM
	 * 
	 * @return {Node Array}
	 */
	this.getAllElem = function()
	{
		if ( document.all )
		{
			return document.all;
		}
		else
		{
			return document.getElementsByTagName("*");
		}
	}
	
	
	
	/**
	 * Removes whitespace from the given string. Able to specify triming of only front or back
	 * using the optional trimStart, trimEnd parameters
	 *	 
	 * @param {string} str The string to be trimmed	 
	 * @param {boolean} trimStart (optional) indicates str is to be front-trimmed, defaults to true
	 * @param {boolean} trimEnd (optional) indicates str is to be end-trimmed, defaults to true
	 * @return {string} 
	 */
	this.trimString = function( str, trimStart, trimEnd )
	{
	  	if ( typeof str != "string" )
	  	{
			throw new Error( Err.genErrMsg( "str is not a string", "trimString()", "UTL.js" ) );	  	
	  	}
	  	
	  	if ( typeof trimStart != "boolean" )
	  	{
	  		trimStart = true;
	  	}
	  	
	  	if ( typeof trimEnd != "boolean" )
	  	{
	  		trimEnd = true;
	  	}
	  	
	  	str = trimStart ? str.replace( /^\s+/g, '' ) : str;
	  	str = trimEnd ? str.replace( /\s+$/g, '' ) : str
	  	return str;
	}
	
	
	
	/**
	 * Returns a function object, suitable for comparing (ascending/descending) values
	 * as specified by the compareType string (ie. UTL.COMPARE_STRING, etc.)
	 *	 
	 * @param {string} compareType type of comparison function required (use defined types).	 	
	 * @param {boolean} descending (optional) whether function should compare descending. Defaults to false.  	 
	 * @return {function} 
	 */
	this.getCompareFn = function( compareType, descending )
	{
		// this is the base function - all returned functions make use of this
		// note: for descending, we just call baseFn with reversed parameters
		var baseFn = function( v1, v2 )
		{
			if ( v1 > v2 ) return 1;
			else if ( v1 == v2 ) return 0;
			return -1;	
		}
				
		switch( compareType )
		{
			case this.COMPARE_CURRENCY:
			{		
				var f = function( v1, v2 )
				{
					v1 = parseFloat( v1.replace( /[^0-9.]/g, '' ) );
					v2 = parseFloat( v2.replace( /[^0-9.]/g, '' ) );					
					return ( descending ) ? baseFn( v2, v1 ) : baseFn( v1, v2 );						
				}
				return f;								
			}
			case this.COMPARE_NUMERIC:
			{
				var f = function( v1, v2 )
				{
					var temp = parseFloat( v1 );
					v1 = isNaN( temp ) ? 0 : temp;
					temp = parseFloat( v2 );
					v2 = isNaN( temp ) ? 0 : temp;
					return ( descending ) ? baseFn( v2, v1 ) : baseFn( v1, v2 );	
				}
				return f;				
			}
			case this.COMPARE_STRING_IGNORE_CASE:
			{
				var f = function( v1, v2 )
				{
					v1 = v1.toLowerCase();
					v2 = v2.toLowerCase();
					return ( descending ) ? baseFn( v2, v1 ) : baseFn( v1, v2 );
				}
				return f;				
			}
			case this.COMPARE_DATE:
			{
				var f = function( v1, v2 )
				{
					if ( !v1.getTime || !v2.getTime )
						throw new Error( Err.genErrMsg( "not date values", "getCompareFn()", "UTL.js" ) );
					return ( descending ) ? baseFn( v2, v1 ) : baseFn( v1, v2 );
				}
				return f;				 
			}
			case this.COMPARE_STRING:
			{
				var f = function( v1, v2 )
				{				
					return ( descending ) ? baseFn( v2, v1 ) : baseFn( v1, v2 );
				}	
				return f;				 
			}			
			default:
			{
				throw new Error( Err.genErrMsg( "unknown compare type", "getCompareFn()", "UTL.js" ) );
			}			
		} 
	}
	
	
	/**
	 * Builds a string with "{key:value}" format representing the given object by iterating 
	 * thru the key/value pairs in the object. Will handle nested objects. When called an a non-object
	 * just returns "" string.
	 *
	 * @param {object} obj Object to build string for
	 * @return {string} 
	 */
	this.objToString = function( obj )
	{			
		if ( typeof obj == "object" )
		{
			var s = "{ ";
			for( var i in obj )
			{
				if( typeof obj[i] == "object" )
				{
					s += i + ":" + UTL.objToString( obj[i] ) + ", ";
				}
				else
				{
					s += i + ":" + obj[i] + ", ";
				}		
			}
			if ( s.length > 2 )
			{
				return s.substring( 0, s.length - 2 ) + " }";
			}
			else
			{
				return s + "}";			
			}
		}
		
		return "";				
	}
	
	
	this.isIEEventModel = function()
	{
		return ( document.attachEvent != null )
	}
	
	
	this.isMOZEventModel = function()
	{
		return ( document.addEventListener != null )
	}
	
	this.isArray = function( obj )
	{					
		if ( UTL.isObject( obj ) )
		{			
			return ( obj.constructor.toString().indexOf( "Array" ) != -1 );
		}
		else
		{
			return false;
		}
	}
	
	this.isObject = function( obj )
	{
		return ( ( typeof( obj ) ).toLowerCase() == "object" ); 
	}	
}
