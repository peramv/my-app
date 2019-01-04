/**
 * Class used for displaying standardized errors in Desktop-browser screens when
 * environment error (ie. listener down) occurs, or screen fails to load properly.
 * 
 */
var DesktopError = new function()
{
	var _baseMsg = "iFAST Desktop Error\n============";
	var _contactMsg = "Please contact administrator for support.";
	
	
	/**
	 * Display error message when screen has failed to load. This should be called
	 * only from the General_DesktopLoadingError.xsl
	 */	
	this.displayLoadingError = function( screenName, details )
	{
		var msg = _baseMsg + "\n";
		msg += "\n" + screenName + " failed to load.\n";
		msg += _contactMsg + "\n";
			
		msg += "\nDetails:\n";
		msg += details;
		
		alert( msg ); 
	}
	
	
	/**
	 * Display error message when screen has fails to process a request
	 * (ie. ajax call fails).
	 */
	this.displayProcessingError = function( screenName, details )
	{
		var msg = _baseMsg + "\n";
		msg += "\n" + screenName + " processing failed.\n";
		msg += _contactMsg + "\n";
			
		msg += "\nDetails:\n";
		msg += details;
		
		alert( msg ); 
	}
} 