/*********************************************************************************************
 * @file	DesktopWeb.Util.js
 * @author 	Rod Walker
 * @desc	Common helper functions used throughout DesktopWeb screens
 *********************************************************************************************/
 /*
 *  History :
 *
 *	24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328
 *					- Fixed screens don't response when user's profile has too many slots attached.  
 *
 *	17 Nov 2016 Narin Tong P0256381  T84279 DFT0069397 CHG0045765 Fund Broker Linkage for Germany
 *					- goToScreen, a new parameter for iframe
 */

DesktopWeb.Util = {

	/*********************************************************************************************
	 * Builds error flag image
	 *
	 * @param	msg - message to be included with the tool tip of the error flag
	 *********************************************************************************************/
	buildErrorFlag: function(msg)
	{
		return '<img qtip="' + msg + '" qclass="x-form-invalid-tip" src="' + DesktopWeb._SRC_PATH + 'images/error.png" />'
	}

	/*********************************************************************************************
	 * Builds warning flag image
	 *
	 * @param	msg - message to be included with the tool tip of the warning flag
	 *********************************************************************************************/
	,buildWarningFlag: function(msg)
	{
		return '<img qtip="' + msg + '" qclass="x-form-warning-tip" src="' + DesktopWeb._SRC_PATH + 'images/warning.png" />'
	}

	/*********************************************************************************************
	 * Calculates the screen width, based on the layout contents
	 *********************************************************************************************/
	,calcScreenWidth: function()
	{
		var width = null;
		if (DesktopWeb._SCREEN_RESOURCES && DesktopWeb._SCREEN_RESOURCES.layoutWidth)
		{
			width = DesktopWeb._SCREEN_RESOURCES.layoutWidth + 14;  //horizontal padding req'd for frame
		}
		else
		{
			width = Ext.getBody().getWidth();
		}
		return width;
	}

	/*********************************************************************************************
	 * Calculates the screen height, based on the layout contents
	 *********************************************************************************************/
	,calcScreenHeight: function()
	{
		var height = null;
		if (DesktopWeb._SCREEN_RESOURCES && DesktopWeb._SCREEN_RESOURCES.layoutHeight)
		{
			height = DesktopWeb._SCREEN_RESOURCES.layoutHeight + 46;  //horizontal padding req'd for frame
		}
		else
		{
			height = Ext.getBody().getHeight();
		}
		return height;
	}

	/*********************************************************************************************
	 * Closes DesktopWeb screen, by 'clicking' the (hidden) Cancel button,
	 * to which C++ code is hooked
	 *********************************************************************************************/
	,cancelScreen: function()
	{
		document.getElementById('btnCancel').click();
	}

	/*********************************************************************************************
	 * Closes DesktopWeb screen, by 'clicking' the (hidden) OK button, to which C++ code
	 * is hooked, displaying Confirm Dialog, and then calling doUpdate if requested
	 *********************************************************************************************/
	,commitScreen: function()
	{
		if (DesktopWeb._SCREEN_PARAM_MAP['debug'] == 'true')
		{
			DesktopWeb._SCREEN_CONTROLLER.doUpdate();
		}
		else
		{
			document.getElementById('btnOK').click();
		}
	}

	/*********************************************************************************************
	 * Closes DesktopWeb screen, by 'clicking' the (hidden) ConfirmDialog button,
	 * to which C++ code is hooked, dispalying Confirm Dialog but with no option to cancel.
	 * This is used when screen has already committed updates, but still want to see Dialog when
	 * closing the screen.
	 *********************************************************************************************/
	,closeScreenWithDialog: function()
	{
		// little hackish to put this here, but the confirm dialog hook to C++ is rather confusing
		DesktopWeb._SCREEN_CONTROLLER.doUpdate = function(){return DesktopWeb._SUCCESS}
		DesktopWeb._SCREEN_CONTROLLER.updateStatus = true;

		document.getElementById('btnConfirmDlg').click();
	}

	/*********************************************************************************************
	 * Converts date object to string based on DesktopWeb date format specified
	 *
	 * @param 	dateObj - date object to convert to string
	 * @param 	format (optional) - string specifying date format, uses value provided in SCREEN_PARAM_MAP as default
	 *********************************************************************************************/
	,dateToString: function(dateObj, format)
	{
		format = (format ? format: DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
		var dateStr = "";
		if (dateObj)
		{
			var dayStr = (dateObj.getDate() < 10 ? "0" + dateObj.getDate() : dateObj.getDate() );
			var monStr = (dateObj.getMonth()+1 < 10 ? "0" + (dateObj.getMonth()+1) : dateObj.getMonth()+1);
			var yearStr = dateObj.getFullYear();
			switch(format)
			{
				case 'dmy':
				{
					dateStr = dayStr + "/" + monStr + "/" + yearStr;
					break;
				}
				case 'mdy':
				{
					dateStr = monStr + "/" + dayStr + "/" + yearStr;
					break;
				}
			}
		}
		return dateStr;
	}

	/*********************************************************************************************
	 * Converts string of date which has '/'as separator to date object based on DesktopWeb date format specified
	 *
	 * @param 	dateString - date string to be converted to date object
	 * @param 	format (optional) - string specifying date format, uses value provided in SCREEN_PARAM_MAP as default
	 *********************************************************************************************/
	,stringToDate: function(dateStr, format)
	{
		format = (format ? format: DesktopWeb._SCREEN_PARAM_MAP['dateFormat']);
		if (dateStr)
		{
			var strDateSplit = dateStr.split("/");
			switch(format)
			{
				case 'dmy':
				{
					var dateObj = new Date(strDateSplit[2],strDateSplit[1]-1,strDateSplit[0]);
					return dateObj;
				}
				case 'mdy':
				{
					var dateObj = new Date(strDateSplit[2],strDateSplit[0]-1,strDateSplit[1]);
					return dateObj;
				}
				case 'ymd':
				{
					var dateObj = new Date(strDateSplit[0],strDateSplit[1]-1,strDateSplit[2]);
					return dateObj;
				}
			}
		}
	}

	/*********************************************************************************************
	 * Check that date will falling in period between date 1 and date 2 or not
	 *
	 * @param 	dateObjStart start of period to check
	 * @param 	dateObjEnd   end of period to check
	 * @param 	dateObj      date will being checked
	 *********************************************************************************************/
	,isDateBetween : function(dateObjStart, dateObjEnd, dateObj)
	{
		if( dateObjStart != null && dateObjEnd != null && dateObj != null )
		{
			if( ((dateObj <  dateObjEnd) && (dateObj >  dateObjStart)) ||
			    ((dateObj == dateObjEnd) || (dateObj == dateObjStart)) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	/*********************************************************************************************
	 * Check overlapping between date 1 and date 2
	 *
	 * @param 	dateObjStart1 start of date 1
	 * @param 	dateObjEnd1   end of date 1
	 * @param 	dateObjStart2 start of date 2
	 * @param 	dateObjEnd2   end of date 2
	 *********************************************************************************************/
	,dateRangesOverlap : function(dateObjStart1, dateObjEnd1, dateObjStart2, dateObjEnd2 )
	{
		if( dateObjStart1 != null && dateObjEnd1 != null && dateObjStart2 != null && dateObjEnd2 != null )
		{
			var isStartDate1InDate2 = DesktopWeb.Util.isDateBetween(dateObjStart2,dateObjEnd2,dateObjStart1);
			var isEndDate1InDate2 = DesktopWeb.Util.isDateBetween(dateObjStart2,dateObjEnd2,dateObjEnd1);
			var isStartDate2InDate1 = DesktopWeb.Util.isDateBetween(dateObjStart1,dateObjEnd1,dateObjStart2);
			var isEndDate2InDate1 = DesktopWeb.Util.isDateBetween(dateObjStart1,dateObjEnd1,dateObjEnd2);

			if( isStartDate1InDate2 || isEndDate1InDate2 || isStartDate2InDate1 || isEndDate2InDate1 )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	/*********************************************************************************************
	 * Displays Error MessageBox containing given errorMsg
	 *
	 * @param 	errorMsg
	 * @param 	callbackFn
	 *********************************************************************************************/
	,displayError: function(errorMsg, callbackFn)
	{
		Ext.Msg.show(
			 {
			    title:'iFAST/Desktop ' + DesktopWeb.Translation.getTranslation('Error')
			     ,msg: errorMsg
			     ,buttons: Ext.Msg.OK
			     ,icon: Ext.MessageBox.ERROR
				 ,minWidth:400
				 ,fn: callbackFn
		     }
		);
	}

	/*********************************************************************************************
	 * Displays Warning MessageBox containing given warningMsg
	 *
	 * @param 	warningMsg
	 * @param 	callbackFn
	 *********************************************************************************************/
	,displayWarning: function(warningMsg, callbackFn, button)
	{
	    if (button == null || button == undefined)
			button = Ext.Msg.OK;
		Ext.Msg.show(
			 {
			     title:'iFAST/Desktop ' + DesktopWeb.Translation.getTranslation('Warning')
			     ,msg: warningMsg
			     ,buttons: button
			     ,icon: Ext.MessageBox.WARNING
				 ,minWidth:400
				 ,fn: callbackFn
		     }
		);
	}

	/*********************************************************************************************
	 * Displays Warning MessageBox containing given warningMsg
	 *
	 * @param 	infoMsg
	 * @param 	callbackFn
	 *********************************************************************************************/
	,displayInfo: function(infoMsg, callbackFn)
	{
		Ext.Msg.show(
			 {
			     title:'iFAST/Desktop ' + DesktopWeb.Translation.getTranslation('Information')
			     ,msg: infoMsg
			     ,buttons: Ext.Msg.OK
			     ,icon: Ext.MessageBox.INFO
				 ,minWidth:400
				 ,fn: callbackFn
		     }
		);
	}

	/*********************************************************************************************
	 * Displays prompt containing given message
	 *
	 * @param 	promptMsg
	 * @param 	callbackFn
	 *********************************************************************************************/
	,displayPrompt: function(promptMsg, callbackFn)
	{
		Ext.Msg.show(
			 {
			     title:'iFAST/Desktop ' + DesktopWeb.Translation.getTranslation('Information')
			     ,msg: promptMsg
			     ,buttons: Ext.Msg.OKCANCEL
			     ,icon: Ext.MessageBox.QUESTION
				 ,minWidth:400
				 ,fn: callbackFn
		     }
		);
	}

	/*********************************************************************************************
	 * Displays Yes/No containing given message
	 *
	 * @param 	promptMsg
	 * @param 	callbackFn
	 *********************************************************************************************/
	,displayYesNo: function(promptMsg, callbackFn)
	{
		Ext.Msg.show(
			 {
			     title:'iFAST/Desktop ' + DesktopWeb.Translation.getTranslation('Information')
			     ,msg: promptMsg
			     ,buttons: Ext.Msg.YESNO
			     ,icon: Ext.MessageBox.QUESTION
				 ,minWidth:400
				 ,fn: callbackFn
		     }
		);
	}

	/*********************************************************************************************
	 * Displays specific prompt to warn user that changes are being discarded (similar to what
	 * is displayed in regular Desktop)
	 *
	 * @param 	callbackFn
	 *********************************************************************************************/
	,displayDiscardPrompt: function(callbackFn)
	{
		Ext.Msg.show(
			 {
			     title:'iFAST/Desktop ' + DesktopWeb.Translation.getTranslation('Warning')
			     ,msg: DesktopWeb.Translation.getTranslation('DiscardQuestion')
				 	+ "<br/><br/>" + DesktopWeb.Translation.getTranslation('DiscardWarning')
			     ,buttons: Ext.Msg.YESNO
			     ,icon: Ext.MessageBox.WARNING
				 ,minWidth:400
				 ,fn: callback
		     }
		);

		function callback(buttonId)
		{
			callbackFn(buttonId == 'yes');
		}
	}



	/*********************************************************************************************
	 * Displays processing indicator on screen, and disables screen
	 *********************************************************************************************/
	,displayProcessing: function(msg)
	{
		document.getElementById("DesktopWeb-Processing-Mask").style.display = "block";
		var processingDiv = document.getElementById('DesktopWeb-Processing');
		processingDiv.style.left = (DesktopWeb.Util.calcScreenWidth() / 2) - 150; //offset values based on CSS of processing div
		processingDiv.style.top = (DesktopWeb.Util.calcScreenHeight() / 2) - 50;
		processingDiv.lastChild.innerHTML = msg;
		processingDiv.style.display = 'block';
	}

	/*********************************************************************************************
	 * Clears processing indicator, and re-enables screen
	 *********************************************************************************************/
	,hideProcessing: function()
	{
		document.getElementById("DesktopWeb-Processing-Mask").style.display = "none";
		document.getElementById('DesktopWeb-Processing').style.display = 'none';
	}

	/*********************************************************************************************
	 * Returns dateformat string appropriate to ExtJS library, based on dateformat
	 * used by Smartviews
	 *
	 * @param 	smvDateFormat - dateformat string as used by Smartviews
	 *********************************************************************************************/
	,parseSMVDateFormat: function(smvDateFormat)
	{
		var dateFormat = "";
		switch(smvDateFormat.toLowerCase())
		{
			case 'dmy':
			{
				dateFormat = 'd/m/Y';
				break;
			}
			case 'mdy':
			{
				dateFormat = 'm/d/Y'
				break;
			}
		}
		return dateFormat;
	}

	/*********************************************************************************************
	 * Returns alternate date formats (that user can type) based on ExtJS masking dateformat
	 *
	 * @param 	dateFormat - dateformat string as used by ExtJS masking
	 *********************************************************************************************/
	,getAltDateFormats: function(dateFormat)
	{
		var altFormats = '';
		switch(dateFormat)
		{
			case 'd/m/Y':
			{
				altFormats = 'j/n/Y';
				break;
			}
			case 'm/d/Y':
			{
				altFormats = 'n/j/Y'
				break;
			}
		}
		return altFormats;
	}

	/*********************************************************************************************
	 * Builds date string from date object using specified date format
	 *
	 * @param	dateObj - date object
	 * @param 	smvDateFormat - dateformat string as used by Smartviews
	 *********************************************************************************************/
	,getDateString: function(dateObj, smvDateFormat)
	{
		if (dateObj)
		{
			var dayStr = (dateObj.getDate() < 10 ? "0" + dateObj.getDate() : dateObj.getDate());
			var monthVal = dateObj.getMonth() + 1
			var monStr = (monthVal < 10 ? "0" + monthVal : monthVal);
			var yearStr = dateObj.getFullYear();
			switch(smvDateFormat.toLowerCase())
			{
				case 'dmy':
				{
					return dayStr + "/" + monStr + "/" + yearStr;
				}
				case 'mdy':
				{
					return monStr + "/" + dayStr + "/" + yearStr;
				}
				case 'ymd':
				{
					return "" + yearStr + monStr + dayStr;
				}
			}
		}
		return '';
	}

	/*********************************************************************************************
	 * Helpful debug/dev tool to view contents of XML node, but will only execute if
	 * URL contains debug=true parameter (ie. won't happen when running screen in Desktop itself)
	 *
	 * @param	xml node
	 * @param 	comment
	 *********************************************************************************************/
	,debugXML: function(xmlNode, comment)
	{
		if (DesktopWeb._SCREEN_PARAM_MAP['debug'] == 'true')
		{
			prompt('DEBUG XML' + (comment ? ' - ' + comment : ""), xmlNode.xml);
		}
	}

	/*********************************************************************************************
	 * Converts date string format from mm/dd/yyyy to dd/mm/yyyy.
	 *
	 * @param 	strDateFormat - dateformat string in mm/dd/yyyy format
	 *********************************************************************************************/
	,convertDateString: function(strDateFormat)
	{
		var myDate = strDateFormat;
		var chunks = myDate.split('/');
		var formattedDate = [chunks[1],chunks[0],chunks[2]].join("/");
		return formattedDate;
	}

	/*********************************************************************************************
	 * Returns date string format for dateField controls according to date format passed from
	 * Desktop application (C++ side).
	 *********************************************************************************************/
	,getDateFieldDisplayFormatString: function()
	{
		var dateFormatDisplay = (DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'] == 'dd/mm/yyyy') ? 'd/m/Y' : 'm/d/Y';
		return dateFormatDisplay;
	}

	/*********************************************************************************************
	 * Return date display format by getting format from dateFormatDisplay passed from C++
	 * The result returns to caller without "/" to work the same behaviour as dateFormat parameter
	 *********************************************************************************************/

	,getDateDisplayFormat: function()
	{
		var resultDateFormat = '';
		var displayFormat = DesktopWeb._SCREEN_PARAM_MAP['dateFormatDisplay'].toLowerCase();

		switch (displayFormat)
		{
				case 'dd/mm/yyyy':
				case 'd/m/y':
				{
						resultDateFormat = 'dmy';
						break;
				}
				case 'mm/dd/yyyy':
				case 'm/d/y':
				{
						resultDateFormat = 'mdy';
						break;
				}
				case 'yyyy/mm/dd':
				case 'y/m/d':
				{
						resultDateFormat = 'ymd';
						break;
				}
				default :
					resultDateFormat = 'mdy';
		}

		return resultDateFormat;
	}

	 /*********************************************************************************************
	 * Return smartview date format by getting format from dateFormat passed from C++
	 *********************************************************************************************/

	,getDateSmartviewFormat: function()
	{
		return DesktopWeb._SCREEN_PARAM_MAP['dateFormat'].toLowerCase();
	}

	/*********************************************************************************************
	 * Convert smartview date string into displayed date string
	 *
	 * @param : strSMVDate -  smartview date string which prefers to convert to display date string
	 *********************************************************************************************/
	,getDateDisplayValue: function(strSMVDate)
	{
		return this.convertDateStringFormat(strSMVDate, this.getDateSmartviewFormat(), this.getDateDisplayFormat());
	}

	/*********************************************************************************************
	 * Convert displayed date string into smartview date string
	 *
	 * @param : strDisplayDate -  display date string which prefers to convert to smartview date string.
	 *********************************************************************************************/
	,getSMVDateValue: function(strDisplayDate)
	{
		return this.convertDateStringFormat(strDisplayDate, this.getDateDisplayFormat(), this.getDateSmartviewFormat());
	}

	/*********************************************************************************************
	 * Convert date string input from "fromFormat" to "toFormat"
	 *
	 * @param : dateString -  date string which prefers to convert
	 * @param : fromFormat -  format of the input dateString
	 * @param : toFormat   -  format which prefer to convert to
	 *********************************************************************************************/
	,convertDateStringFormat : function(dateString, fromFormat , toFormat)
	{
		if (dateString == null || dateString == 'undefined' || dateString.trim() == "") return "";

		var splitChar = '/';
		var resultDateFormat = '';
		var strDateSplit = dateString.split(splitChar);

		if (strDateSplit.length != 3)
			return dateString;

		var fromDateFormat = ((fromFormat === undefined || fromFormat == '')
					? this.getDateSmartviewFormat() : fromFormat);

		var toDateFormat = ((toFormat === undefined || toFormat == '')
					? this.getDateDisplayFormat() : toFormat);

		if (fromDateFormat == toDateFormat)
		{
			resultDateFormat = dateString;
		}
		else if (fromDateFormat == 'mdy')
		{
			if (toDateFormat == 'dmy')   //mm/dd/yyyy -> dd/mm/yyyy
				resultDateFormat = [strDateSplit[1],strDateSplit[0],strDateSplit[2]].join(splitChar);
			else if (toDateFormat == 'ymd') //mm/dd/yyyy -> yyyy/mm/dd
				resultDateFormat = [strDateSplit[2],strDateSplit[0],strDateSplit[1]].join(splitChar);
			else
				resultDateFormat = dateString;
		}
		else if ( fromDateFormat == 'dmy')
		{
			if (toDateFormat == 'mdy')      //dd/mm/yyyy -> mm/dd/yyyy
				resultDateFormat = [strDateSplit[1],strDateSplit[0],strDateSplit[2]].join(splitChar);
			else if (toDateFormat == 'ymd') //dd/mm/yyyy -> yyyy/mm/dd
				resultDateFormat = [strDateSplit[2],strDateSplit[1],strDateSplit[0]].join(splitChar);
			else
				resultDateFormat = dateString;
		}
		else if ( fromDateFormat == 'ymd')
		{
			if (toDateFormat == 'mdy')      //yyyy/mm/dd -> mm/dd/yyyy
				resultDateFormat =[strDateSplit[1],strDateSplit[0],strDateSplit[2]].join(splitChar);
			else if (toDateFormat == 'dmy') //yyyy/mm/dd -> dd/mm/yyyy
				resultDateFormat = [strDateSplit[2],strDateSplit[1],strDateSplit[0]].join(splitChar);
			else
				resultDateFormat = strSMVDate;
		}
		else
			resultDateFormat = dateString;

	  return resultDateFormat;
	}

	/*********************************************************************************************
	 * Return date format string from input dateFormat
	 *
	 * @param : inputDateFormat -  date string format
	 *********************************************************************************************/

	, getDateFormatTemplate: function(inputDateFormat)
	{
		var dateFormat = "";
		switch(inputDateFormat.toLowerCase())
		{
			case 'dmy':
			case 'd/m/y':
			{
				dateFormat = 'DD/MM/YYYY';
				break;
			}
			case 'mdy':
			case 'm/d/y':
			{
				dateFormat = 'MM/DD/YYYY'
				break;
			}
		}
		return dateFormat;
	}

	,addHiddenToForm: function(form, name, value)
	{
		if (!form.elements.namedItem(name))
		//if (form.name === undefined)
		{
			var input = document.createElement("input");
			input.setAttribute("type", "hidden");
			input.setAttribute("id", name);
			input.setAttribute("name", name);
			input.setAttribute("value", value);
			form.appendChild(input);
		}else{
			form.elements.namedItem(name).value = value;
		}
	}
	
	/*********************************************************************************************
	 * Submit form and navigate to next screen.
	 * @param : screen - Screen name which prefers to navigate.  
	 * @param : params - Additional parameters which are posted to the next screen.
	 * @param : target - iFrame name which is used for rendering a screen in iFrame (eg.popup)
	 *********************************************************************************************/	 
	,goToScreen: function(screen, params, target) 
	{
		var form = document.getElementById("GoToScreen-form");
		DesktopWeb.Util.addHiddenToForm(form, 'jobname', 'DisplayScreen');
		DesktopWeb.Util.addHiddenToForm(form, 'screen', screen);
		
		for (var i in params) 
		{
			DesktopWeb.Util.addHiddenToForm(form, i, params[i]);
		}

		form.target = Ext.isEmpty(target)?'_self':target;
		form.submit();
	}
}