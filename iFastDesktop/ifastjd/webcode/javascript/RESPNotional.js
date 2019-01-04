var _selectedInfoLevel = null;
var _periodOptionsMap = null;
var _accountNum = null;

var _fieldFlagMap = null;

var _updatesFlag = null;

var _updatesSaved = false;

var _modPermission = null; 


//******************************************************
function loading()
{
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );
	_fieldFlagMap = {};	
	
	UTL.getElem( "infoLevelFld" ).selectedIndex = 0;
	UTL.getElem( "period_dateFilterRadioBtn" ).checked = true;	
	_selectedInfoLevel = UTL.getElem( "infoLevelFld" ).value;
	populatePeriodFld();
}

//******************************************************
function changeHandler_infoLevelFld()
{
	_selectedInfoLevel = UTL.getElem( "infoLevelFld" ).value;
	clickHandler_refreshBtn();
	populatePeriodFld();
}

//******************************************************
function clickHandler_dateFilterRadioBtn( selection )
{	
	if ( selection == "period" )
	{
		disableAsOfFld();
		enablePeriodFld();
	}
	else
	{
		disablePeriodFld();
		enableAsOfFld();
	}
}

//******************************************************
function disableAsOfFld()
{
	UTL.getElem( "asOfDateFld" ).value = "";
	
	IFDSDatepickerManager.getDatepicker( "asOfDateFld" ).disable();
}

//******************************************************
function enableAsOfFld()
{	
	IFDSDatepickerManager.getDatepicker( "asOfDateFld" ).enable();
}

//******************************************************
function disablePeriodFld()
{
	clearPeriodFld();
	UTL.getElem( "periodFld" ).disabled = true;
}

//******************************************************
function enablePeriodFld()
{
	populatePeriodFld();	
	UTL.getElem( "periodFld" ).disabled = false;
}

//******************************************************
function enableOKBtn()
{	
	if ( _modPermission == 'yes' )
	{
		UTL.getElem( "btnOK" ).disabled = false;
	}
}

//******************************************************
function disableOKBtn()
{	
	UTL.getElem( "btnOK" ).disabled = true;
}

//******************************************************
function resetDateFilterRadioBtn()
{
	UTL.getElem( "period_dateFilterRadioBtn" ).checked = true;
	clickHandler_dateFilterRadioBtn( UTL.getElem( "period_dateFilterRadioBtn" ).value );
}

//******************************************************
function clearAsOfDateFld()
{
	UTL.getElem( "asOfDateFld" ).value = "";
}

//******************************************************
function clearPeriodFld()
{
	var periodFld = UTL.getElem( "periodFld" );
	while( periodFld.options.length > 0 )
	{
		periodFld.remove( periodFld.options.length - 1 );
	}
}

//******************************************************
function populatePeriodFld()
{		
	clearPeriodFld();
	var periodOptions = _periodOptionsMap[_selectedInfoLevel];
	var periodFld = UTL.getElem( "periodFld" );
	for ( var i in periodOptions )
	{
		var option = document.createElement( "option" );
		option.value = i;
		option.text = periodOptions[i];
		periodFld.add( option );	
	}
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

//******************************************************
function changeHandler_entryFld( entryFld, dataRowNum )
{
	if(UTL.trimString(entryFld.value) == "")
	{
		entryFld.value = "0.00";
	}
	
	if ( validateDataRowFields( dataRowNum ) )
	{
		if ( isBalanceUpdatable( dataRowNum ) )
		{
			updateBalance( dataRowNum );
		}
		
		if ( entryFld.id == 'qPurACContrib' || entryFld.id == 'qPurUCContrib' )
		{			
			var newPurContribVal = Number( getFldValue( UTL.getElem( 'qPurACContrib' ) ) ) 
									+ Number( getFldValue( UTL.getElem( 'qPurUCContrib' ) ) );
												
			UTL.getElem( 'qPurContrib' ).innerHTML = newPurContribVal.toFixed( 2 );
			
			var newBalTotContribVal = newPurContribVal - Number( UTL.getElem( 'qRedContrib' ).innerHTML );
			UTL.getElem( 'balQTotContrib' ).innerHTML = newBalTotContribVal.toFixed( 2 );																									
		}
		
		if ( entryFld.id == 'qRedACContrib' || entryFld.id == 'qRedUCContrib' )
		{			
			var newRedContribVal = Number( getFldValue( UTL.getElem( 'qRedACContrib' ) ) ) 
									+ Number( getFldValue( UTL.getElem( 'qRedUCContrib' ) ) );
												
			UTL.getElem( 'qRedContrib' ).innerHTML = newRedContribVal.toFixed( 2 );
			
			var newBalTotContribVal = Number( UTL.getElem( 'qPurContrib' ).innerHTML ) - newRedContribVal
			UTL.getElem( 'balQTotContrib' ).innerHTML = newBalTotContribVal.toFixed( 2 );																									
		}
		
		if ( entryFld.id == 'grantBasicPur' || entryFld.id == 'grantAddlPur' )
		{
			var newTotalQESIVal = Number( getFldValue( UTL.getElem( 'grantBasicPur' ) ) ) 
									+ Number( getFldValue( UTL.getElem( 'grantAddlPur' ) ) );
												
			UTL.getElem( 'totQGrant' ).innerHTML = newTotalQESIVal.toFixed( 2 );
			
			var newBalTotalQESIVal = Number( UTL.getElem( 'totQGrant' ).innerHTML ) 
										- Number( getFldValue( UTL.getElem( 'grantRed' ) ) ) 
										-  Number( getFldValue( UTL.getElem( 'grantRepymt' ) ) )
			UTL.getElem( 'balGrant' ).innerHTML = newBalTotalQESIVal.toFixed( 2 );					
		}
		
		setUpdatesFlag();
	}
}

//******************************************************
function setUpdatesFlag()
{
	_updatesFlag = true;	
	//enableOKBtn();
}

//******************************************************
function clearUpdatesFlag()
{
	_updatesFlag = false;	
	//disableOKBtn();
}

//****************************************************
function validateDataRowFields( dataRowNum )
{
	var isValid = true;
	var dataRow = UTL.getElem( "dataRow:" + dataRowNum );
	var purFld = UTL.getElem( dataRow.purFldName );
	isValid = isValid && validateDataField( purFld );
	var redFld = UTL.getElem( dataRow.redFldName );
	isValid = isValid && validateDataField( redFld );
	var rpyFld = UTL.getElem( dataRow.rpyFldName );
	isValid = isValid && validateDataField( rpyFld );
	
	return isValid;	
}

//******************************************************
function validateDataField( fld )
{
	var isValid = true;
	if ( fld.type && fld.type == "text" )
	{
		if ( isNaN( fld.value ) )
		{		
			window.setTimeout( "Desktop.paintFieldErrorFlag( _fieldFlagMap, '" + fld.id + "', 'Invalid entry' )", 25 );
			window.setTimeout( "UTL.getElem( '" + fld.id + "' ).focus()" , 50 );			
			isValid = false;			
		}
	}
	return isValid;
}

//******************************************************
function isBalanceUpdatable( dataRowNum )
{
	var dataRow = UTL.getElem( "dataRow:" + dataRowNum );
	var balFld = UTL.getElem( dataRow.balFldName );
	return ( balFld.innerHTML != "N/A" );
}

//******************************************************
function updateBalance( dataRowNum )
{
	var dataRow = UTL.getElem( "dataRow:" + dataRowNum );
	var purFld = UTL.getElem( dataRow.purFldName );	
	var redFld = UTL.getElem( dataRow.redFldName );	
	var rpyFld = UTL.getElem( dataRow.rpyFldName );
	var balFld = UTL.getElem( dataRow.balFldName );
	
	balFld.innerHTML = Number( getFldValue( purFld ) - getFldValue( redFld ) - getFldValue( rpyFld ) ).toFixed( 2 );
}

//******************************************************
function getFldValue( fld )
{
	if ( fld.type && fld.type == "text" )
	{
		return Number( fld.value ).valueOf();
	}
	else if ( fld.innerHTML != 'N/A' )
	{
		return Number( fld.innerHTML ).valueOf();
	}
	else
	{
		return 0;
	}
}

//******************************************************
function clickHandler_refreshBtn()
{
	if ( !_updatesFlag || confirm( "Unsaved changes will be lost. Do you wish to proceed?" ) )
	{
		if ( UTL.getElem( "period_dateFilterRadioBtn" ).checked 
			|| ( UTL.getElem( "asof_dateFilterRadioBtn" ).checked 
					&& IFDSDatepicker.isValidDateValue( UTL.getElem( "asOfDateFld" ).value, _dateFormat ) ) )
		{
			doRefresh();
		}
		else if( UTL.getElem( "asOfDateFld" ).value == "" ||
				 !IFDSDatepicker.isValidDateValue( UTL.getElem( "asOfDateFld" ).value, _dateFormat ) )
		{
			alert( "Valid date must be entered, when selecting 'As of' option." );
		}
	}
}

//******************************************************
function doRefresh()
{
	sendRefreshRequest( doRefresh_callback );
	
	function doRefresh_callback( notionalDataXML )
	{
		if ( notionalDataXML )
		{
			UTL.getElem( "NotionalDataDiv" ).innerHTML = "";
			UTL.getElem( "NotionalDataDiv" ).innerHTML = notionalDataXML.firstChild.xml;
			clearUpdatesFlag();					
		}
	}	
}

//******************************************************
function sendRefreshRequest( callbackFn )
{
	function sendRefreshRequest_callback( responseText )
	{		
		Desktop.hideProcessingIndicator();
		
		var notionalDataHTML = null;
		var responseXML = null;
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
					notionalDataHTML = XML.getNode( "/responseContents/notionalDataHTML", responseXML );
				}
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendRefreshRequest error caught: " + e.description ); 		
		}
		
		callbackFn( notionalDataHTML );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPNotional_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
	paramMap["AccountNum"] = _accountNum;	
	if ( UTL.getElem( "infoLevelFld" ).selectedIndex == 0 )
	{
		paramMap["notlLevel"] = "acct";		
	}
	else
	{
		paramMap["notlLevel"] = "ben";
		paramMap["benefID"] = UTL.getElem( "infoLevelFld" ).value;		
	}
	
	if ( !UTL.getElem( "periodFld" ).disabled )
	{	
		paramMap["period"] = UTL.getElem( "periodFld" ).value;
	}
	
	if ( !UTL.getElem( "asOfDateFld" ).disabled )
	{	
		paramMap["asOfDate"] = UTL.getElem( "asOfDateFld" ).value;
	}
            
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getGETRequest( url );			
	req.setCallbackFunction( sendRefreshRequest_callback );	
	Desktop.showProcessingIndicator();
	req.send();		
}

//******************************************************
function clickHandler_closeBtn()
{
	if ( _updatesSaved )
	{		
		UTL.getElem( "btnConfirmDlg" ).click();
	}
	else
	{
		UTL.getElem( "btnCancel" ).click();	
	}
}

//******************************************************
function LaunchConfirm()
{
	return _updatesFlag;
}

//******************************************************
function update()
{
	sendSaveRequest( doSave_callback );
	var updateStatus = null;
	
	function doSave_callback( status )
	{
		if ( status && status == "success" )
		{			
			updateStatus = Desktop.SUCCESS;				
		}
		else
		{
			updateStatus = Desktop.FAIL;
		}
	}	
	
	return updateStatus;
}

//******************************************************
function sendSaveRequest( callbackFn )
{
	function sendSaveRequest_callback( responseText )
	{		
		Desktop.hideProcessingIndicator();
				
		var responseXML = null;
		try 
		{
			responseXML = XML.parseToXML( responseText );
			var status = null;			
			if ( responseXML )
			{
				if ( responseErrorFound( responseXML ) )
				{
					displayResponseError( responseXML );	
				}
				else
				{
					status = XML.getNode( "status", responseXML ).firstChild.nodeValue;
				}				
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendSaveRequest error caught: " + e.description ); 		
		}
		
		callbackFn( status );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPNotional_Update";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
    var updateXML = buildUpdateXML();
    //prompt( "", XML.serialize( updateXML ) );    
            
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );			
	req.setCallbackFunction( sendSaveRequest_callback );	
	Desktop.showProcessingIndicator();
	req.send( XML.serialize( updateXML ) );		
}

//******************************************************
function buildUpdateXML()
{
	var updateXML = XML.newDocument( "NotionalUpdate" );
		
	XML.addNodeWithValue( "AccountNum", updateXML, _accountNum );
	XML.addNodeWithValue( "versionNotl", updateXML, UTL.getElem( "versionNotlFld" ).value );
	XML.addNodeWithValue( "versionPNotl", updateXML, UTL.getElem( "versionPNotlFld" ).value );
	
	if ( UTL.getElem( "infoLevelFld" ).selectedIndex == 0 )
	{
		XML.addNodeWithValue( "notlLevel", updateXML, "acct" );			
	}
	else
	{
		XML.addNodeWithValue( "notlLevel", updateXML, "ben" );
		XML.addNodeWithValue( "benefID", updateXML, UTL.getElem( "infoLevelFld" ).value );			
	}
	
	if ( !UTL.getElem( "periodFld" ).disabled )
	{	
		XML.addNodeWithValue( "period", updateXML, UTL.getElem( "periodFld" ).value );		
	}
	
	if ( !UTL.getElem( "asOfDateFld" ).disabled )
	{	
		XML.addNodeWithValue( "asOfDate", updateXML, UTL.getElem( "asOfDateFld" ).value );
	}
	
	var rowNum = 1;		
	var dataRow = UTL.getElem( "dataRow:" + rowNum ); 
	while( dataRow != null )
	{
		var purFld = UTL.getElem( dataRow.purFldName );
		if ( purFld.type && purFld.type == "text" )
		{
			XML.addNodeWithValue( purFld.id, updateXML, purFld.value );
		}
		
		var redFld = UTL.getElem( dataRow.redFldName );
		if ( redFld.type && redFld.type == "text" )
		{
			XML.addNodeWithValue( redFld.id, updateXML, redFld.value );
		}
				
		var rpyFld = UTL.getElem( dataRow.rpyFldName );
		if ( rpyFld.type && rpyFld.type == "text" )
		{
			XML.addNodeWithValue( rpyFld.id, updateXML, rpyFld.value );
		}		
				
		rowNum++;
		dataRow = UTL.getElem( "dataRow:" + rowNum );
	}
	
	return updateXML;
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
		DesktopError.displayProcessingError( "RESP Notional", errorMsg );  
	}
	else
	{
		alert( errorMsg );
	}
}

//******************************************************
function getHistoricalSearchParam()
{
	var paramMap = {};
	paramMap["searchValue1"] = UTL.getElem( "respNotlInfoIdFld" ).value;
	
	return paramMap;
}

//******************************************************
function clickHandler_OKBtn()
{	
	if ( _updatesFlag )
	{
		UTL.getElem("btnOK").click();
	}
	else
	{
		UTL.getElem("btnCancel").click();
	}
}




