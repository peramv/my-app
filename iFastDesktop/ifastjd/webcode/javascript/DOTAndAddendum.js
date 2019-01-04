var _disableDiv = null;
var _processingDiv = null;


/**
 * init DOT screen elements 
 */
function initDOT()
{
	// add prev/next btn event handlers
	EvtHandler.add( UTL.getElem( "prevBtn" ), "click", clickHandler_prevBtn );
	EvtHandler.add( UTL.getElem( "nextBtn" ), "click", clickHandler_nextBtn );
	
	UTL.getElem( "DOTTableDiv" ).onscroll = scrollHandler;
	
	// build divs for "showProcessing"
	_disableDiv = buildDisableDiv();
	_processingDiv = buildProcessingDiv();
}



/**
 * EVENT HANDLER - click handler on the prev btn 
 */
function clickHandler_prevBtn( evt )
{
	var curFirstRec = parseInt( UTL.getElem( "recordRange_start" ).rangeStart );
	var startRecNum = ( curFirstRec - _requestRecNum > 0 ? curFirstRec - _requestRecNum : 1 ) ;	
	sendDOTRequest( startRecNum );
}



/**
 * EVENT HANDLER - click handler on the next btn 
 */
function clickHandler_nextBtn( evt )
{
	var curLastRec = parseInt( UTL.getElem( "recordRange_end" ).rangeEnd );
	var startRecNum = curLastRec + 1;
	sendDOTRequest( startRecNum );
}



/**
 * send DOTRequest
 */
function sendDOTRequest( startRecNum )
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "DOTAndAddendum_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    paramMap["AccountNum"] = _accountNum;
    paramMap["requestRecNum"] = _requestRecNum;    
    paramMap["startRecNum"] = startRecNum;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );    
	    	    
	displayProcessing();
	    
	HTTP.getText( url, sendDOTRequest_callback );    
}



/**
 * callback function for DOTRequest
 */
function sendDOTRequest_callback( responseText )
{
	hideProcessing();
	
	var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "DOT And Addendum", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}
        return;
    }
    else
    {   
    	try
    	{
	    	// get the outputAction nodes and convert to JSON
	    	var outputActionNodeArray = XML.getNodes( "/responseContents/OutputActionList/OutputAction", responseXML );
	    	var recordMapArray = new Array( outputActionNodeArray.length );    	
	    	for ( var i = 0; i < outputActionNodeArray.length; i++ )
	    	{    		
	    		recordMapArray[i] = XML.buildJSON( outputActionNodeArray[i] );    		
	    	}
	    	
	    	// populate DOT table with records
	    	populateDOTTable( recordMapArray );
	    	
	    	// update the record range values
	    	var rangeStartNode = XML.getNode( "/responseContents/RecordRange/rangeStart", responseXML );
	    	var rangeStart = rangeStartNode.firstChild.nodeValue;
	    	var rangeEndNode = XML.getNode( "/responseContents/RecordRange/rangeEnd", responseXML );
	    	var rangeEnd = rangeEndNode.firstChild.nodeValue;
	    	var moreRecordsExistNode = XML.getNode( "/responseContents/RecordRange/moreRecordsExist", responseXML );
	    	var moreRecordsExist = ( moreRecordsExistNode.firstChild.nodeValue.toLowerCase() == "yes" ? true : false );
	    	updateRecordRange( rangeStart, rangeEnd, moreRecordsExist );
	    	
	    }
	    catch( error )
	    {
	    	alert( "Error parsing response: " + error );
	    }    	
    }	
}



/**
 * populate the DOT Table with the recordMapArray
 */
function populateDOTTable( recordMapArray )
{
	var DOTTable = UTL.getElem( "DOTTable" );
	// clear any existing records
	clearDOTTable();
	
	for ( var i = 0; i < recordMapArray.length; i++ )
	{
		DOTTable.lastChild.appendChild( buildDOTTableRow( recordMapArray[i], i ) );
	}
}



/**
 * remove all existing records in DOT Table
 */
function clearDOTTable()
{
	var DOTTable = UTL.getElem( "DOTTable" );
	while ( DOTTable.lastChild.lastChild )
	{
		DOTTable.lastChild.removeChild( DOTTable.lastChild.lastChild );
	}
}



/**
 * build a DOT Table row, in response to reload request
 */
function buildDOTTableRow( recordMap, rowIndex )
{
	var tr = document.createElement( "tr" );
	tr.className = ( rowIndex % 2 == 0 ? "DOTRow_even" : "DOTRow_odd" );
	
	tr.fileType = recordMap.fileType;
	tr.fileTypeDesc = recordMap.fileTypeDesc;
	tr.Deff = recordMap.Deff;
	tr.userName = recordMap.userName;
	
	// file type td
	var fileTypeTD = tr.appendChild( document.createElement( "td" ) );
	fileTypeTD.className = "DOTDataItem";
	fileTypeTD.innerHTML = recordMap.fileTypeDesc;
	
	// Deff td
	var deffTD = tr.appendChild( document.createElement( "td" ) );
	deffTD.className = "DOTDataItem";
	deffTD.innerHTML = recordMap.Deff;
	
	// userName td
	var userNameTD = tr.appendChild( document.createElement( "td" ) );
	userNameTD.className = "DOTDataItem";
	userNameTD.innerHTML = recordMap.userName;
	
	return tr;	
}



/**
 * update record range fields in response to reload
 */
function updateRecordRange( rangeStartVal, rangeEndVal, moreRecordsExist )
{
	var recordRangeStartFld = UTL.getElem( "recordRange_start" );
	recordRangeStartFld.rangeStart = rangeStartVal;
	recordRangeStartFld.innerHTML = rangeStartVal;
	
	var recordRangeEndFld = UTL.getElem( "recordRange_end" );
	recordRangeEndFld.rangeEnd = rangeEndVal;
	recordRangeEndFld.innerHTML = rangeEndVal;
	
	// disable prev/next buttons accordingly
	if ( rangeStartVal != 1 )
	{
		UTL.getElem( "prevBtn" ).disabled = false;
	}
	else
	{
		UTL.getElem( "prevBtn" ).disabled = true;
	}
	
	if ( moreRecordsExist )
	{
		UTL.getElem( "nextBtn" ).disabled = false;
	}
	else
	{
		UTL.getElem( "nextBtn" ).disabled = true;
	}
}



/**
 * scroll handler
 */
function scrollHandler()
{
	var DOTTableDiv = UTL.getElem( "DOTTableDiv" );
	
	var DOTTable = UTL.getElem( "DOTTable" );
	DOTTable.firstChild.firstChild.style.position = "relative";
	DOTTable.firstChild.firstChild.style.zIndex = 1000;	
	DOTTable.firstChild.firstChild.style.top = DOTTableDiv.scrollTop;
}



/**
 * build the page disable div
 */
function buildDisableDiv()
{
	var d = document.body.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";	
	d.style.left = 0;	
	d.style.top = 0;
	d.style.width = "100%";
	d.style.height = "100%";
	d.style.zIndex = 1000;
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
	var d = document.body.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";	
	d.style.left = 250;	
	d.style.top = 225;
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
 * disables the screen and displays "processing" msg 
 */
function displayProcessing()
{
	_disableDiv.style.display = "block";
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

