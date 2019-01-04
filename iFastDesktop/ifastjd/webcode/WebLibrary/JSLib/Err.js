/** 
 * @fileoverview Contains error handlng code. Sets window.onerror handler to a custom function
 *  
 * @author walkerro
 * @version 0.1 
 */


/**
 * Static class - no constructor permitted
 *  
 * @class Static class used to hold javascript error handling code.
 * <br/>
 * NOTE: window.onerror event handler is set to a customized function (errHandler) within.
 */
var Err = new function()
{
	
	/**
	 * OnError handler function. This is assigned to window.onerror and called automatically
	 * (with the appropriate param) when an error is uncaught.
	 * IE - displays an alert box with error details, including custom information if avail.
	 * MOZ - displays a simple alert box directing user to the JavaScript console.
	 * 
	 * @param {string} message User or default specified error description
	 * @param {string} url Location the browser detected the error
	 * @return {string} line Line number the browser deted the error
	 */
	this.errHandler = function ( message, url, line )
	{
		var errOutput = "** JAVASCRIPT ERROR **\n\n";
			
		// MOZ	
		if ( window.navigator.appName.toUpperCase().indexOf( "MICROSOFT" ) == -1 )
		{
			errOutput += "Please see JavaScript Console for details ...";
			
			alert( errOutput );
			return false;
		}
		// IE
		else
		{		
			
			var errInfo = Err.parseMessage( message );
			errOutput += "Msg:\t" + errInfo.message + "\n\n";
			
			if ( errInfo.src )
			{
				errOutput += "Src:\t" + errInfo.src + "\n\n";
			}
			
			errOutput += "Url:\t " + url + "\n\n";
			errOutput += "Line:\t " + line + "\n\n";
			 	
		 	alert( errOutput );
		 			 	
			return false;
		}
	}
	
	// set window.onerror to errHandler function defined above
	//window.onerror = this.errHandler;
	
		
	/**
	 * Wraps the given parameters in a string formatted as 
	 * "message text &lt;srcFunction [srcFile]&gt;"
	 * 
	 * @param {string} message Error description message
	 * @param {string} string specifying function in which error occurs
	 * @param {string} string specifying file in which error occurs
	 * @return {string}
	 */
	this.genErrMsg = function( message, srcFunction, srcFile )
	{
		return message + " <SRC: " + srcFunction + " [" + srcFile + "]>";
	}


	/**
	 * Deconstructs the message string, into message string, and src string (if found)
	 * 
	 * @param {string} message Error description message, and possibly a src string.	 
	 * @return {object} errInfo errInfo.message = error description string;
	 * errInfo.src = source information (only if found in message param)
	 */
	this.parseMessage = function( message )
	{
		var errInfo = {};
		if( message.indexOf( "<SRC" ) != -1 )
		{
			errInfo.message = message.slice( 0, message.indexOf( "<SRC:" ) );
			errInfo.src = message.slice( message.indexOf( "<SRC:" ) + 6, message.lastIndexOf( ">" ) ); 
		}
		else
		{
			errInfo.message = message;
		}
		return errInfo;		
	}
}	