var _disableDiv = null;
var _processingDiv = null;
var _updatesMade = false;


/**
 * init LIF screen elements 
 */
function initLIFGainLoss()
{	
	UTL.getElem( "TransDiv" ).onscroll = scrollHandler;
	
	// build divs for "showProcessing"
	_disableDiv = buildDisableDiv();
	_processingDiv = buildProcessingDiv();		
}


/**
 * EVENT HANDLER - click handler for the refresh button 
 */
function clickHandler_refreshBtn()
{
	var yearVal = UTL.getElem( "lifPrevYear" ).value;
	sendLIFGainLossReloadRequest( _accountNum, yearVal );	
}


/**
 * EVENT HANDLER - click handler for the save button on the update popup 
 */
function clickHandler_saveUpdateBtn()
{
	var transNum = UTL.getElem( "transNumFld" ).value;	
	var newGainLoss = parseToFloat( UTL.getElem( "gainLossFld" ).value );
	
	if ( newGainLoss == null )
	{
		alert( "Gain/Loss entry is not a valid numeric value" );
	}
	else
	{		
		sendLIFGainLossUpdateRequest( transNum, newGainLoss );
	}
}


/**
 * EVENT HANDLER - click handler for the save button on the update popup 
 */
function clickHandler_cancelUpdateBtn()
{
	hideUpdatePopup();
}


/**
 * display the update updated, with the details from the given row index 
 */
function displayUpdatePopup( transRowIndex )
{	
	populatePopup( transRowIndex );
	
	displayDisabler();
	UTL.getElem( "PopupIframe" ).style.display = "block";
	UTL.getElem( "GainLossPopup" ).style.display = "block";
}


/**
 * hides the update popup 
 */
function hideUpdatePopup()
{
	clearPopup();
	
	_disableDiv.style.display = "none";
	UTL.getElem( "PopupIframe" ).style.display = "none";
	UTL.getElem( "GainLossPopup" ).style.display = "none";		
}


/**
 * populate the popup fields with values from the given row 
 */
function populatePopup( transRowIndex )
{
	var transTable = UTL.getElem( "TransTable" );
	
	var transNumColIndex = 0;
	UTL.getElem( "transNumFld" ).value = WebTools.getTableCell( transTable, transRowIndex, transNumColIndex ).txnNum;
	var effDateColIndex = 1;
	UTL.getElem( "effDateFld" ).value = WebTools.getTableCell( transTable, transRowIndex, effDateColIndex ).deff;
	var gainLossColIndex = 5;		
	UTL.getElem( "gainLossFld" ).value = WebTools.getTableCell( transTable, transRowIndex, gainLossColIndex ).gainLoss;
}


/**
 * clear the popup fields 
 */
function clearPopup()
{		
	UTL.getElem( "transNumFld" ).value = "";
	UTL.getElem( "effDateFld" ).value = "";
	UTL.getElem( "gainLossFld" ).value = "";
}



/**
 * send Reload request 
 */
function sendLIFGainLossReloadRequest( accountNum, yearVal )
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "LIFGainLoss_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    paramMap["AccountNum"] = accountNum;
    paramMap["lifPrevYear"] = yearVal;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );        
	    	    
	displayProcessing();
	    
	HTTP.getText( url, function( responseText ){ sendLIFGainLossRequest_callback( responseText, false /*hide popup*/ ) } );    
}


/**
 * send update request 
 */
function sendLIFGainLossUpdateRequest( transNum, newGainLoss )
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "LIFGainLoss_Process";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    paramMap["transNum"] = transNum;
    paramMap["gainLoss"] = newGainLoss;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );        		    	  
	displayProcessing();
	    
	HTTP.getText( url, function( responseText ){ sendLIFGainLossRequest_callback( responseText, true /*hide popup*/) } );		   
}


/**
 * clear the ransaction table 
 */
function clearTable()
{
	var transDiv = UTL.getElem( "TransDiv" );
	var transTable = UTL.getElem( "TransTable" );
	
	transDiv.removeChild( transTable );	
}


/**
 * callback function for the update/reload request 
 */
function sendLIFGainLossRequest_callback( responseText, isUpdate )
{	
	
	var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "LIF Gain/Loss", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}        
    }
    else
    {   
    	// update the trans table
    	var tableUpdateNode = XML.getNode( "/responseContents/tableUpdate", responseXML );
    	var tableHTML = tableUpdateNode.firstChild.xml;    	
    	clearTable();
    	UTL.getElem( "TransDiv" ).innerHTML = tableHTML;
    	
    	// update the tot gain/loss
    	var totalGainLossNode = XML.getNode( "/responseContents/totalGainLoss", responseXML );
    	var totalGainLossVal = totalGainLossNode.firstChild.nodeValue;
    	UTL.getElem( "totalGainLossVal" ).innerHTML = totalGainLossVal;
    	
    	if ( isUpdate )
		{
			_updatesMade = true;
		}    	
    }
    
    hideProcessing();
    if ( isUpdate )
	{		
		hideUpdatePopup();
	}    	
}


/**
 * converts the given string to a two decimal float value, or returns
 * null if the given string cannot be converted
 * 
 * @param {string} numericStr
 */
function parseToFloat( numericStr )
{
	var floatVal = numericStr.replace( /,| /g, "" );	
	if ( !isNaN( floatVal ) )
	{
		return parseFloat( floatVal ).toFixed( 2 );
	}
	else
	{
		return null
	}
}


/**
 * build the page disable div
 */
function buildDisableDiv()
{
	document.onresize = resizeDisabler;
	
	var d = document.body.appendChild( document.createElement( "div" ) );	
	d.style.position = "absolute";	
	d.style.left = 0;	
	d.style.top = 0;		
	d.style.zIndex = 1000;
	d.style.display = "none";
	d.style.background = "black";
	d.style.filter = "alpha(opacity=20)";
	
	return d;	   
}


/**
 * resize the disabler div, as screen is resized
 */
function resizeDisabler()
{
	if ( _disableDiv.style.display == "block" )
	{
		displayDisabler();
	}
}


/**
 * build the "processing" div
 */
function buildProcessingDiv()
{
	var d = document.body.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";	
	d.style.left = 380;	
	d.style.top = 150;
	d.style.width = 200;
	d.style.height = 50;
	d.style.zIndex = 1001;
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
	_disableDiv.style.width = Math.max( document.body.clientWidth, document.body.scrollWidth );
	_disableDiv.style.height = Math.max( document.body.clientHeight, document.body.scrollHeight );
	_disableDiv.style.display = "block";
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
function hideProcessing()
{
	_disableDiv.style.display = "none";
	_processingDiv.style.display = "none";
}


/**
 * scroll handler
 */
function scrollHandler()
{
	var TransDiv = UTL.getElem( "TransDiv" );
	
	var TransTable = UTL.getElem( "TransTable" );
	TransTable.firstChild.firstChild.style.position = "relative";
	TransTable.firstChild.firstChild.style.zIndex = 1000;	
	TransTable.firstChild.firstChild.style.top = TransDiv.scrollTop;
}


function clickHandler_closeBtn()
{
	UTL.getElem( "btnConfirmDlg" ).click();
}


/**
 * returns true/false depending on whether updates have been done
 */
function getUpdateStatus()
{	
	return _updatesMade;	
}