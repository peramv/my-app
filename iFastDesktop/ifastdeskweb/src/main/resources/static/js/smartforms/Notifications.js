Notifications = {
	errorMessages: {
		requiredField: "This field is required"
	}
	
	,buildErrorsDisplay: function(errors)
	{			
		var html = "";
		html += "<div>Following error(s) occured:</div>"
		html += "<br/>";		
		for (var i = 0; i < errors.length; i++)
		{
			html += "<div>&bull; " + errors[i].text + "</div>";
			html += "<br/>"
		}				
		
		return html;
	}
	
	,buildWarningsDisplay: function(warnings)
	{		
		var html = "";
		html += "<div>Following warning(s) occured:</div>"
		html += "<br/>";		
		for (var i = 0; i < warnings.length; i++)
		{
			html += "<div>&bull; " + warnings[i].text + "</div>";
			html += "<br/>"
		}				
		
		return html;
	}
	
	,buildFailedValidationDisplay: function(errors)
	{
		var html = "";
		html += "<div>All errors must be resolved before submitting.</div>"
		html += "<br/>";
		html += this.buildErrorsDisplay(errors);
		
		return html;
	}
	
	
	,buildAccountDetailsDisplay: function(acctNum, shrNum)
	{		
		var html = "";
		html += "<div>&bull; Account Number: " + acctNum + "</div>";
		html += "<br/>";
		html += "<div>&bull; Shareholder Number: " + shrNum + "</div>";		
		
		return html;
	}
	
	,buildAccoutSetupDisplay: function(acctNum, shrNum)
	{		
		var html = "";
		html += "<div>New account setup successfully completed.</div>";
		html += "<br/>";
		html += this.buildAccountDetailsDisplay(acctNum, shrNum);	
		
		return html;
	}
	
	,buildAccoutSetupWithWarningsDisplay: function(acctNum, shrNum, warnings)
	{		
		var html = "";
		html += "<div>New account setup completed, but with warnings.</div>";
		html += "<br/>";
		html += this.buildAccountDetailsDisplay(acctNum, shrNum);
		html += "<br/>";
		html += "<br/>";
		html += this.buildWarningsDisplay(warnings);
		
		return html;
	}
	
	,buildSecondryAPIErrorsDisplay: function(num, apiDesc, errors, warnings)
	{
		var html = "";
		html += "<div>" + num + ") " + apiDesc + " processing could not be completed.</div>";
		html += "<br/>";
		html += this.buildErrorsDisplay(errors);		
		if (warnings.length > 0)
		{
			html += this.buildWarningsDisplay(warnings);		
		}
		html += "<br/>";
		return html;
	}
	
	,buildSecondryAPIWarningsDisplay: function(num, apiDesc, warnings)
	{
		var html = "";
		html += "<div>" + num + ") " + apiDesc + " processing completed, but with warnings.</div>";
		html += "<br/>";
		html += this.buildWarningsDisplay(warnings);		
		html += "<br/>";
		
		return html;
	}
	
	,buildChangeFormWarningDisplay: function()
	{
		var html = "";
		html += "Changing forms will result in loss of entered data."
		html += "<br/><br/>"
		html += "Are you sure you wish to continue?"
		
		return html;
	}
	
	,buildDoneWarningDisplay: function()
	{
		var html = "";
		html += "Supplementary processing remains outstanding.";
		html += "<br/><br/>";
		html += "Closing now will require this to be completed outside of SmartForms."
		html += "<br/><br/>"
		html += "Are you sure you wish to continue?"
		
		return html;
	}
	
	,buildSecondaryAPIErrorDisplay: function(errorDetails)
	{
		var html = "";
		html += "Errors occured during supplementary processing:"
		html += "<br/><br/>";
		html += errorDetails;
		
		return html;			
	}
	
	,buildSecondaryAPIWarningDisplay: function(warningDetails)
	{
		var html = "";
		html += "Warnings occured during supplementary processing:"
		html += "<br/><br/>";
		html += warningDetails;
		
		return html;			
	}
	
	,buildResubmitSuccessDisplay: function()
	{
		var html = "";
		html += "Supplementary processing successfully completed."		
		
		return html;			
	}
	
	,buildMissingSourcePageDisplay: function()
	{
		var html = "";
		html += "Source item contains <u>fewer</u> pages than found in the current form."
		html += "<br/><br/>";
		html += "May need to change to an alternate form, or process work item outside of SmartForms."
		
		return html;
	}
	
	,buildExtraSourcePageDisplay: function()
	{
		var html = "";
		html += "Source item contains <u>more</u> pages than found in the current form."
		html += "<br/><br/>";
		html += "Please review the source pages and de-select the unnecessary pages, or change to an alternate form."
		
		return html;
	}
	
	,error: function(contents, callbackFn)
	{
		DesktopWeb.Util.displayError(contents, callbackFn);
	}
	
	,warning: function(contents, callbackFn)
	{
		DesktopWeb.Util.displayWarning(contents, callbackFn);
	}
	
	,info: function(contents, callbackFn)
	{
		DesktopWeb.Util.displayInfo(contents, callbackFn);
	}
	
	,prompt: function(contents, callbackFn)
	{
		DesktopWeb.Util.displayPrompt(contents, callbackFn);
	}
}
