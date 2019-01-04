var _disableDiv = null;
var _processingDiv = null;

var _actionFieldMap = null;

function initReleaseFrozenAcct()
{
	_actionFieldMap = {};
	_actionFieldMap["RmStmtDateList"] = UTL.getElem( "rmStmtDateFld" )
	_actionFieldMap["StopNFUList"] = UTL.getElem( "stopNFUFld")
	_actionFieldMap["StopPurchaseList"] = UTL.getElem( "stopPurchaseFld")
	_actionFieldMap["StopRedempList"] = UTL.getElem( "stopRedempFld")
	_actionFieldMap["StopTransferInList"] = UTL.getElem( "stopTransferInFld")
	_actionFieldMap["StopTransferOutList"] = UTL.getElem("stopTransferOutFld")
	_actionFieldMap["ReactivePACSWPList"] = UTL.getElem("reactivePACSWPFld")
	
	EvtHandler.add( UTL.getElem( "accountFld" ), "keydown", keydownHandler_AccountFld );
	
	enableActions( false, false );
	
	// build divs for "showProcessing"
	_disableDiv = buildDisableDiv();
	_processingDiv = buildProcessingDiv();
}


//function enableLookup( enableBtn )
//{
//	if ( enableBtn )
//	{
//		UTL.getElem( "btnLookup" ).disabled = false;
//	}
//	else
//	{
//		UTL.getElem( "btnLookup" ).disabled = true;
//	}
//}


function enableActions( enableSection, enableUpd )
{
	if ( enableSection )
	{
		UTL.getElem( "ActionsSectionDiv" ).disabled = false;
		
		if ( enableUpd )
		{
			UTL.getElem( "btnUpdate" ).disabled = false;
		}
		else
		{
			UTL.getElem( "btnUpdate" ).disabled = true;
		}
	}
	else
	{
		clearActionFields();
		
		UTL.getElem( "ActionsSectionDiv" ).disabled = true;		
	}
}


function clearActionFields()
{
	for ( var i in _actionFieldMap )
	{
		for ( var optionIndex = _actionFieldMap[i].options.length - 1; optionIndex >= 0; optionIndex-- )
		{
			_actionFieldMap[i].remove( optionIndex );
		}
	}	
}


function populateActionFields( actionFieldOptionMap )
{
	for ( var actionFieldId in _actionFieldMap )
	{		
		var actionField = _actionFieldMap[actionFieldId];
		var optionArray = actionFieldOptionMap[actionFieldId];
		for ( var i = 0; i < optionArray.length; i++ )
		{
			var option = document.createElement( "option" );
			option.value = optionArray[i].value;
			option.text = optionArray[i].text;
			actionField.add( option );
		}
	}
}


function setActionFieldValues( actionFieldValueMap )
{
	for ( var actionFieldId in _actionFieldMap )
	{		
		var actionField = _actionFieldMap[actionFieldId];
		var actionFieldValue = actionFieldValueMap[actionFieldId];
		actionField.value = actionFieldValue;
	}
}


function keydownHandler_AccountFld( evt )
{	
	if ( KeyMap.getKeyDesc( evt.keyCode, KeyMap.KEYDOWN ) == KeyMap.ENTER )
	{
		sendLookupRequest();		
	}	
}


function clickHandler_LookupBtn()
{	
	sendLookupRequest();
}


function clickHandler_UpdateBtn()
{
	sendUpdateRequest();
}


function sendLookupRequest()
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ReleaseFrozenAcct_Lookup";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
    var accountFld = UTL.getElem( "accountFld" )
    var account = UTL.trimString( accountFld.value );
    if( account.length == 0 || account.search( /\D/g ) != -1 )
    {
    	alert( "Account Number is missing or not formatted properly" );
    	return;
    }
    paramMap["account"] = account;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );        		    	  
	
	var req = HTTP.getGETRequest( url );
	req.setCallbackFunction( sendLookupRequest_callback );
	
	displayProcessing();
	req.send();	     
}


function sendLookupRequest_callback( responseText )
{
	//prompt( "", responseText );
	var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "Release Frozen Account", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}    	       
    }
    else
    {
    	UTL.getElem( "accountLbl" ).innerHTML = UTL.getElem( "accountFld" ).value;
    	UTL.getElem( "accountFld" ).value = "";
    	
    	var actionFieldOptionMap = {};
    	var actionFieldValueMap = {};
    	for ( var actionFieldId  in _actionFieldMap )
    	{    	    		
    		actionFieldOptionMap[actionFieldId] = buildOptionArray( XML.getNode( "/responseContents/List[@listName = '" + actionFieldId + "']", responseXML ) );
    		actionFieldValueMap[actionFieldId] = XML.getNode( "/responseContents/ListSelection[@id = '" + actionFieldId + "']", responseXML ).firstChild.nodeValue;    		    		    
    	}    	
    	populateActionFields( actionFieldOptionMap );    	
    	setActionFieldValues( actionFieldValueMap );
    	enableActions( true, XML.getNode( "/responseContents/Permissions/updPerm", responseXML ).firstChild.nodeValue.toLowerCase() == "yes" );
    }
	
	hideProcessing( false ); 
}


function sendUpdateRequest()
{
	var paramMap = {}
    paramMap["cz"]              = _vCZ;
    paramMap["jobname"]         = "ReleaseFrozenAcct_Update";    
    paramMap["companyCode"]     = _companyCode;
    paramMap["ruserId"]         = _ruserId;
    paramMap["sessionId"]       = _sessionId;
    paramMap["envName"]         = _envName;
	paramMap["dateFormat"] 		= _dateFormat;
        
	paramMap["account"] 		= UTL.getElem( "accountLbl" ).innerHTML;
    paramMap["rmStmtDate"] 		= UTL.getElem( "rmStmtDateFld" ).value;
    paramMap["stopNFU"] 		= UTL.getElem( "stopNFUFld" ).value;
    paramMap["stopPurchase"] 	= UTL.getElem( "stopPurchaseFld" ).value;
    paramMap["stopRedemp"] 		= UTL.getElem( "stopRedempFld" ).value;
    paramMap["stopTransferIn"] 	= UTL.getElem( "stopTransferInFld" ).value;
    paramMap["stopTransferOut"] = UTL.getElem( "stopTransferOutFld" ).value;
    paramMap["reactivePACSWP"] 	= UTL.getElem( "reactivePACSWPFld" ).value;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );        		    	  
	
	var req = HTTP.getGETRequest( url );
	req.setCallbackFunction( sendUpdateRequest_callback );
	
	displayProcessing();
	req.send();	     
}


function sendUpdateRequest_callback( responseText )
{
	//prompt( "", responseText );
	var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "Release Frozen Account", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}
    	hideProcessing( false );    	       
    }
    else
    {
    	hideProcessing( false );
    	alert( "Account " + UTL.getElem( "accountLbl" ).innerHTML + " updated successfully" );
    }
	
	 
}


function buildOptionArray( optionListNode )
{	
	var optionArray = [];	
	var elementNodeArray = XML.getNodes( "Element", optionListNode );    	
	for ( var i = 0; i < elementNodeArray.length; i++ )
	{	
		var optionMap = {};
		optionMap["value"] = XML.getNode( "code", elementNodeArray[i] ).firstChild.nodeValue;		
		optionMap["text"] = XML.getNode( "value", elementNodeArray[i] ).firstChild.nodeValue;		
		optionArray[i] = optionMap;
	}	
	return optionArray; 
}


/**
 * build the page disable div
 */
function buildDisableDiv()
{
	var screenDiv = UTL.getElem( "ScreenDiv" );
	var d = screenDiv.appendChild( document.createElement( "div" ) );	
	d.style.position = "absolute";	
	d.style.left = 0;	
	d.style.top = 0;
	d.style.width = screenDiv.offsetWidth; 		
	d.style.height = screenDiv.offsetHeight;
	d.style.zIndex = 1;
	d.style.display = "none";
	d.style.background = "black";
	d.style.filter = "alpha(opacity=20)";
	
	return d;	   
}


/**
 * build the "processing" div
 */
function buildProcessingDiv()
{
	var screenDiv = UTL.getElem( "ScreenDiv" );
	var d = screenDiv.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";
	
	var width = 200;
	var height = 50;
	
	d.style.width = width;
	d.style.height = height
		
	d.style.left = ( screenDiv.offsetWidth - width ) / 2;	
	d.style.top = ( screenDiv.offsetHeight - height ) / 2;
	
	d.style.zIndex = 4;
	d.style.paddingTop = 10;
	d.style.textAlign = "center";
	d.style.display = "none";	
	d.style.border = "2px solid black";
	d.style.background = "white";
	d.style.fontSize = "14px";
	d.style.fontStyle = "italic";
	d.innerHTML = "Processing ...";
	
	return d;
}


/**
 * display the disabler div
 */
function displayDisabler()
{
	_disableDiv.style.display = "block";
	
	// rather than re-drawing the disableDiv to cover the whole browser 
	// screen (whose size may vary), we just have it cover the screenDiv 
	// and make the rest of the document background a matching color 
	document.body.style.backgroundColor = "#BCBABE";	
}


/**
 * remove disabler div
 */
function hideDisabler()
{
	document.body.style.backgroundColor = _desktopColor;
	_disableDiv.style.display = "none";
}


/**
 * disables the screen and displays "processing" msg 
 */
function displayProcessing()
{
	displayDisabler();
	_processingDiv.style.display = "block";
}


/**
 * re-enables the screen and hides the "processing" msg 
 */
function hideProcessing( popupOpen )
{
	if ( !popupOpen )
	{
		hideDisabler();
	}
	_processingDiv.style.display = "none";
}