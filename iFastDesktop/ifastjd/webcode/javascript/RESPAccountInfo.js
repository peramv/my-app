var _origSiblingOnly = null;
var _accountNum = null;
var _origMatureDate = null;
var _taxType = null;
var _DTCResponse = null;
var _siblingSeverity = null;
var _siblingSeverityMsg = null;
var _version = null;
var _allowMod = null;
var _errorFlagMap = null;

//******************************************************
function loading()
{
	IFDSTableManager.init();
	
	_origSiblingOnly = UTL.getElem( "siblingOnlyFld" ).value;
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );
	
	if ( !_allowMod )
	{
		disableScreen();
	}
	
	_errorFlagMap = {};
}

//******************************************************
function getUpdateStatus()
{
	return false;
}

//******************************************************
function disableScreen()
{
	UTL.getElem( "respStatFld" ).disabled = true;
	UTL.getElem( "pre98ContrFld" ).disabled = true;
	UTL.getElem( "reportToHRDCFld" ).disabled = true;
	UTL.getElem( "siblingOnlyFld" ).disabled = true;
	UTL.getElem( "reportingReqFld" ).disabled = true;
	
	IFDSDatepickerManager.getDatepicker( "inceptionDateFld" ).disable();
	IFDSDatepickerManager.getDatepicker( "matureDateFld" ).disable();
	
	UTL.getElem( "okBtn" ).disabled = true;
}

//******************************************************
function changeHandler_matureDateFld()
{
	if ( _errorFlagMap["matureDateFld"] )
	{
		_errorFlagMap["matureDateFld"].hide();
	}
	
	var origMatureDateObj = IFDSDatepicker.buildDateObj( _origMatureDate, _dateFormat );
	var newMatureDateObj = IFDSDatepicker.buildDateObj( UTL.getElem( "matureDateFld" ).value, _dateFormat );
	
	if ( origMatureDateObj && ( origMatureDateObj.getTime() < newMatureDateObj.getTime() ) )
	{
		alert( "Specified mature date is later than original mature date." );
	}	
}

//******************************************************
function changeHandler_inceptionDateFld()
{
	if ( _errorFlagMap["inceptionDateFld"] )
	{
		_errorFlagMap["inceptionDateFld"].hide();
	}
}

//******************************************************
function changeHandler_siblingOnlyFld()
{		
	if ( _errorFlagMap["siblingOnlyFld"] )
	{
		_errorFlagMap["siblingOnlyFld"].hide();
	}
	doSiblingOnlyValidation();
}

//******************************************************
function doSiblingOnlyValidation()
{
	sendSiblingOnlyValidationRequest( buildValidationData(), doSiblingOnlyValidation_callback );
	
	function doSiblingOnlyValidation_callback( siblingSeverity, siblingSeverityMsg, amendWarningNodes )
	{		
		_siblingSeverity = siblingSeverity;
		_siblingSeverityMsg = siblingSeverityMsg;
		if ( siblingSeverity == "E" )
		{
			setTimeout( "Desktop.paintFieldErrorFlag( _errorFlagMap, \"siblingOnlyFld\", _siblingSeverityMsg );", 20 )
			//Desktop.paintFieldErrorFlag( _errorFlagMap, "siblingOnlyFld", siblingSeverityMsg );
		}
		else if ( siblingSeverity == "W" )
		{
			alert( siblingSeverityMsg );
		}
		
		_siblingSeverity = siblingSeverity;
		
		if ( amendWarningNodes != null && amendWarningNodes.length > 0 )
		{
			var msg = amendWarningNodes[0].firstChild.nodeValue;
			for ( var i = 1; i < amendWarningNodes.length; i++)
			{
				msg += "\n\n" + amendWarningNodes[i].firstChild.nodeValue;
			}
			alert(msg);
		}
	}
}

//******************************************************
function buildValidationData()
{
	var xmldoc = XML.newDocument( "data" );
	XML.addNodeWithValue( "accountNum", xmldoc, _accountNum );
	XML.addNodeWithValue( "siblingOnly", xmldoc, UTL.getElem( "siblingOnlyFld" ).value );
	XML.addNodeWithValue( "matureDt", xmldoc, UTL.getElem( "matureDateFld" ).value );
	XML.addNodeWithValue( "origMatureDt", xmldoc, _origMatureDate );
	XML.addNodeWithValue( "taxType", xmldoc, _taxType );
	return xmldoc;
}

//******************************************************
function sendSiblingOnlyValidationRequest( requestXML, callbackFn )
{
	function sendSiblingOnlyValidationRequest_callback( responseText )
	{		
		var responseXML = null;
				
		var siblingSeverity = null;
		var siblingSeverityMsg = null;
		
		try 
		{			
			responseXML = XML.parseToXML( responseText );					
			if ( responseXML )
			{
				if ( responseErrorFound( responseXML ) )
				{
					displayResponseError( responseXML );				
				}
				else
				{					
					var siblingSeverityNode = XML.getNode( "/responseContents/siblingSeverity", responseXML ).firstChild;										
					siblingSeverity = ( siblingSeverityNode ? siblingSeverityNode.nodeValue : "" );
					siblingSeverityMsg = ( siblingSeverity != "" ? XML.getNode( "/responseContents/siblingQuestn", responseXML ).firstChild.nodeValue : "" );
					
					var amendWarningNodes = XML.getNodes( "/responseContents/AmendmentWarning/warnMsg", responseXML ); 																
				}						
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendSiblingOnlyWarningRequest error caught: " + e.description ); 		
		}
		
		callbackFn( siblingSeverity, siblingSeverityMsg, amendWarningNodes );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPAccountInfo_Validate";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );
	req.setAsynch( false );			
	req.setCallbackFunction( sendSiblingOnlyValidationRequest_callback );		
	req.send( XML.serialize( requestXML ) );		
}

//******************************************************
function responseErrorFound( responseXML )
{
	return XML.getNode( "/responseContents/Error", responseXML ) != null
}

//******************************************************
function displayResponseError( responseXML )
{
	var errorNode = XML.getNode( "/responseContents/Error", responseXML );
	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
	if ( errorType.toLowerCase() == "environment" )
	{
		DesktopError.displayProcessingError( "Fund Setup - Class Copy", errorMsg );  
	}
	else
	{
		alert( errorMsg );
	}
}

//******************************************************
function clickHandler_okBtn()
{
	if ( !IFDSDatepicker.isValidDateValue( UTL.getElem( "matureDateFld" ).value, _dateFormat ) )
	{
		Desktop.paintFieldErrorFlag( _errorFlagMap, "matureDateFld", "Invalid value" );
		return;
	}
	
	if ( !IFDSDatepicker.isValidDateValue( UTL.getElem( "inceptionDateFld" ).value, _dateFormat ) )
	{
		Desktop.paintFieldErrorFlag( _errorFlagMap, "inceptionDateFld", "Invalid value" );
		return;
	}
	
	if ( _siblingSeverity == "E" )
	{		
		return;
	}
	
	doQuestionPrompt( doAccountInfoUpdate );	
}

//******************************************************
function doQuestionPrompt()
{
	sendQuestionPromptRequest( buildValidationData(), doQuestionPrompt_callback );
	
	function doQuestionPrompt_callback( displayQuestion, questionMsg )
	{
		if ( displayQuestion )
		{
			displayDTCPrompt( questionMsg );
		}
		else
		{
			doAccountInfoUpdate();
		}
	}	
}

//******************************************************
function displayDTCPrompt( questionMsg )
{
	UTL.getElem( "DTCPopup_QuestionLbl" ).innerHTML = questionMsg;
	Desktop.showPopup( "DTCPopupDiv", "RESP Account Information" );
}

//******************************************************
function sendQuestionPromptRequest( requestXML, callbackFn )
{
	function sendQuestionPromptRequest_callback( responseText )
	{		
		//Desktop.hideProcessingIndicator();
				
		var responseXML = null;
		var displayQuestion = false;
		var questionMsg = null;
		
		try 
		{
			responseXML = XML.parseToXML( responseText );					
			if ( responseXML )
			{
				if ( responseErrorFound( responseXML ) )
				{
					displayResponseError( responseXML );				
				}
				else
				{
					displayQuestion = XML.getNode( "/responseContents/promptDTC", responseXML ).firstChild.nodeValue == "yes";
					if ( displayQuestion )
					{
						questionMsg = XML.getNode( "/responseContents/dtcQuestn", responseXML ).firstChild.nodeValue;
					}
					
				}						
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendQuestionPromptRequest error caught: " + e.description ); 		
		}
		
		callbackFn( displayQuestion, questionMsg );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPAccountInfo_Validate";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );			
	req.setCallbackFunction( sendQuestionPromptRequest_callback );	
	//Desktop.showProcessingIndicator();
	//prompt( "", XML.serialize( requestXML ) );
	req.send( XML.serialize( requestXML ) );
}

//******************************************************
function doAccountInfoUpdate()
{
	UTL.getElem( "btnOK" ).click();
}

//******************************************************
function LaunchConfirm()
{
	return true;
}

//******************************************************
function update()
{
	var updateStatus = null;
	sendAccountInfoUpdateRequest( buildAccountInfoData(), doAccountInfoUpdate_callback );
	return updateStatus;
	
	function doAccountInfoUpdate_callback( success, responseXML )
	{
		if ( success )
		{
			updateStatus = Desktop.SUCCESS;			
		}
		else
		{
			updateStatus = Desktop.FAIL;
		}
	}
}

//******************************************************
function sendAccountInfoUpdateRequest( updateXML, callbackFn )
{
	function sendAccountInfoUpdateRequest_callback( responseText )
	{		
		Desktop.hideProcessingIndicator();
				
		var responseXML = null;
		var success = true;
		try 
		{
			responseXML = XML.parseToXML( responseText );					
			if ( responseXML )
			{
				if ( responseErrorFound( responseXML ) )
				{
					displayResponseError( responseXML );
					success = false;				
				}									
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendAccountInfoUpdateRequest error caught: " + e.description ); 		
		}
		
		callbackFn( success, responseXML );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPAccountInfo_Update";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );
	req.setAsynch( false );			
	req.setCallbackFunction( sendAccountInfoUpdateRequest_callback );	
	Desktop.showProcessingIndicator();
	//prompt( "", XML.serialize( updateXML ) );
	req.send( XML.serialize( updateXML ) );		
}

//******************************************************
function buildAccountInfoData()
{
	var xmldoc = XML.newDocument( "data" );
	XML.addNodeWithValue( "accountNum", xmldoc, _accountNum );
	XML.addNodeWithValue( "siblingOnly", xmldoc, UTL.getElem( "siblingOnlyFld" ).value );
	XML.addNodeWithValue( "matureDt", xmldoc, UTL.getElem( "matureDateFld" ).value );	
	XML.addNodeWithValue( "repHRDC", xmldoc, UTL.getElem( "reportToHRDCFld" ).value );
	XML.addNodeWithValue( "pre98Contr", xmldoc, UTL.getElem( "pre98ContrFld" ).value );
	XML.addNodeWithValue( "repReqd", xmldoc, UTL.getElem( "reportingReqFld" ).value );
	XML.addNodeWithValue( "incepDt", xmldoc, UTL.getElem( "inceptionDateFld" ).value );
	XML.addNodeWithValue( "repStat", xmldoc, UTL.getElem( "respStatFld" ).value );
	XML.addNodeWithValue( "version", xmldoc, _version );		
	XML.addNodeWithValue( "siblingSeverity", xmldoc, ( _siblingSeverity != null ? _siblingSeverity : "" ) );

	if( _DTCResponse != null )
	{
		XML.addNodeWithValue( "promptDTC", xmldoc, _DTCResponse );
	}
	return xmldoc;
}

//******************************************************
function clickHandler_DTCResponseBtn( response )
{
	_DTCResponse = response;
	Desktop.hidePopup( "DTCPopupDiv" );
	doAccountInfoUpdate();
}

//******************************************************
function setDatepickerCalendarPosition( datepickerFld )
{
    var datepickerFldPosObj = WebTools.calcElemPos( datepickerFld );

	var calendarPosObj = {};
	calendarPosObj["top"] = parseInt( datepickerFldPosObj.top ) + datepickerFld.offsetHeight + 3;
	calendarPosObj["left"] = parseInt( datepickerFldPosObj.left ) +  parseInt( datepickerFld.offsetWidth );
	calendarPosObj["container"] = document.body;
	calendarPosObj["zIndex"] = 101;
    return calendarPosObj;
}


