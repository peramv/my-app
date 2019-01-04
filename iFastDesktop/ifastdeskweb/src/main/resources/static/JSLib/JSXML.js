/** 
 * @fileoverview Contains wrapper functions for operands not available in XML, due
 * to special character restrictions in XML syntax.
 * <br/>
 * REQUIRES: @link Err.js
 *  
 * @author walkerro
 * @version 0.1 
 */

/** 
 * Static class - no constructor permitted
 * 
 * @class Static class used to hold functions to be used in XML files directly, where
 * special character operators are not permitted. 
 */
var JSXML = new function()
{
	/**
	 * A constant allowing use of "&amp;" inside strings 	 
	 * @type string  
	 */
	this.AMP = "&";
	this.LT = "<";
	this.GT = ">";
	
	/**
	 * Function replacing "&lt;" operator
	 * 
	 * @param {number} lhVal Value representing left-side of a less-than expression
	 * @param {number} rhVal Value representing right-side of a less-than expression
	 * @return {boolean}
	 */	
	this.lt = function( lhVal, rhVal )
	{
		if ( isNaN( lhVal ) )
		{
			throw new Error( Err.genErrMsg( "lhVal is NaN", "lt()", "JSXML.js" ) );				
		}
		
		if ( isNaN( rhVal ) )
		{
			throw new Error( Err.genErrMsg( "rhVal is NaN", "lt()", "JSXML.js" ) );			
		}
		
		return lhVal < rhVal;	
	}
	
	
	/**
	 * Function replacing "&lt;=" operator
	 * 
	 * @param {number} lhVal Value representing left-side of a less-than-equal-to expression
	 * @param {number} rhVal Value representing right-side of a less-than-equal-to expression
	 * @return {boolean}
	 */	
	this.lte = function( lhVal, rhVal )
	{
		if ( isNaN( lhVal ) )
		{
			throw new Error( Err.genErrMsg( "lhVal is NaN", "lte()", "JSXML.js" ) );				
		}
		
		if ( isNaN( rhVal ) )
		{
			throw new Error( Err.genErrMsg( "rhVal is NaN", "lte()", "JSXML.js" ) );			
		}
		
		return lhVal <= rhVal;	
	}
	
	
	
	/**
	 * Function replacing "&gt;" operator
	 * 
	 * @param {number} lhVal Value representing left-side of a greater-than expression
	 * @param {number} rhVal Value representing right-side of a greater-than expression
	 * @return {boolean}
	 */	
	this.gt = function( lhVal, rhVal )
	{
		if ( isNaN( lhVal ) )
		{
			throw new Error( Err.genErrMsg( "lhVal is NaN", "gt()", "JSXML.js" ) );				
		}
		
		if ( isNaN( rhVal ) )
		{
			throw new Error( Err.genErrMsg( "rhVal is NaN", "gt()", "JSXML.js" ) );			
		}
		
		return lhVal > rhVal;	
	}
	
	
	/**
	 * Function replacing "&gt;=" operator
	 * 
	 * @param {number} lhVal Value representing left-side of a greater-than-equal-to expression
	 * @param {number} rhVal Value representing right-side of a greater-than-equal-to expression
	 * @return {boolean}
	 */	
	this.gte = function( lhVal, rhVal )
	{
		if ( isNaN( lhVal ) )
		{
			throw new Error( Err.genErrMsg( "lhVal is NaN", "gte()", "JSXML.js" ) );				
		}
		
		if ( isNaN( rhVal ) )
		{
			throw new Error( Err.genErrMsg( "rhVal is NaN", "gte()", "JSXML.js" ) );			
		}
		
		return lhVal >= rhVal;	
	}
	
	
	/**
	 * Function replacing "&amp;" operator
	 * 
	 * @param {boolean} lhVal Value representing left-side of an AND expression
	 * @param {boolean} rhVal Value representing right-side of a AND expression
	 * @return {boolean}
	 */	
	this.and = function( lhVal, rhVal )
	{
		return lhVal && rhVal;	
	}
	
	
	
}	