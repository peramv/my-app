var _accountNum = null;
var _respBenId = null;
var _reasonCode = null;
var _depositType = null;
var _redCode = null;
			
var _moreRecordsExist = null;
var _rangeStartForNext = null;

//******************************************************
function loading()
{
	IFDSTableManager.init();
	
	IFDSTableManager.getTable( "GrantContrib_Table" ).setOnRowSelectedFunction( selectHandler_GrantContibTable );
	
	if ( _moreRecordsExist )
	{
		UTL.getElem( "moreBtn" ).disabled = false;
	}						
	else
	{
		UTL.getElem( "moreBtn" ).disabled = true;
	}
}

//******************************************************
function selectHandler_GrantContibTable()
{
	enableOKBtn();	
}

//******************************************************
function enableOKBtn()
{
	UTL.getElem( "btnOK" ).disabled = false;
}

//******************************************************
function clickHandler_moreBtn()
{
	reload();
}

//******************************************************
function reload()
{
	sendReloadRequest( reload_callback );
	
	function reload_callback( grantContribXML )
	{
		if ( grantContribXML )
		{
			updateGrantContribTable( grantContribXML );		
			
			if ( !_moreRecordsExist )
			{
				UTL.getElem( "moreBtn" ).disabled = true;
			}
		}	
	}
}

//******************************************************
function sendReloadRequest( callbackFn )
{
	function sendReloadRequest_callback( responseText )
	{		
		Desktop.hideProcessingIndicator();
		
		var dataXML = null;
		var moreExist = null;
		var nextStartNum = null;
		
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
					dataXML = XML.getNode( "/responseContents/GrantContribData", responseXML );
					
					_moreRecordsExist = ( XML.getNode( "/responseContents/RecordRange/moreRecordsExist", responseXML ).firstChild.xml == 'yes' );					
					if ( _moreRecordsExist )
					{
						_rangeStartForNext = XML.getNode( "/responseContents/RecordRange/rangeStartForNext", responseXML ).firstChild.xml;
					}
					else
					{
						_rangeStartForNext = null;
					}
				}
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendReloadRequest error caught: " + e.description ); 		
		}
		
		callbackFn( dataXML );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "GrantContrib_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;    
    
	paramMap["AccountNum"] = _accountNum;
	paramMap["RESPBenID"] = _respBenId;
	paramMap["ReasonCode"] = _reasonCode;
	paramMap["DepositType"] = _depositType;
	paramMap["RedCode"] = _redCode;
	
	paramMap["startRecNum"] = _rangeStartForNext;	
	            
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getGETRequest( url );			
	req.setCallbackFunction( sendReloadRequest_callback );	
	Desktop.showProcessingIndicator();
	req.send();		
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
function updateGrantContribTable( dataXML )
{
	var table = UTL.getElem( "GrantContrib_Table" );
	
	var dataRecords = XML.getNodes( "GrantContribRec", dataXML );
	
	for ( var i = 0; i < dataRecords.length; i++ )
	{
		var row = buildGrantContribTableRow( dataRecords[i] );
		table.lastChild.appendChild( row ); 
	}
	
	IFDSTableManager.reInitTable( "GrantContrib_Table" );
}	

//******************************************************
function buildGrantContribTableRow( recordXML )
{
	var row = document.createElement( "tr" );	
		
	var entNameCell = row.appendChild( document.createElement( "td" ) );
	entNameCell.innerHTML = XML.getNode( "entName", recordXML ).firstChild.nodeValue;
	
	row.entityID = XML.getNode( "entityID", recordXML ).firstChild.nodeValue;
	
	var transIdCell = row.appendChild( document.createElement( "td" ) );
	transIdCell.innerHTML = XML.getNode( "transID", recordXML ).firstChild.nodeValue;
	row.transID = transIdCell.innerHTML;
	
	var hrdcTransIdCell = row.appendChild( document.createElement( "td" ) );
	hrdcTransIdCell.innerHTML = XML.getNode( "hrdcTransID", recordXML ).firstChild.nodeValue;
	
	var tradeDateCell = row.appendChild( document.createElement( "td" ) );
	tradeDateCell.innerHTML = XML.getNode( "tradeDt", recordXML ).firstChild.nodeValue;
	
	var transTypeCell = row.appendChild( document.createElement( "td" ) );
	transTypeCell.innerHTML = XML.getNode( "transType", recordXML ).firstChild.nodeValue;
	
	var redDepCodeCell = row.appendChild( document.createElement( "td" ) );
	redDepCodeCell.innerHTML = XML.getNode( "redDepCode", recordXML ).firstChild.nodeValue;
	
	var ucAmtCell = row.appendChild( document.createElement( "td" ) );
	ucAmtCell.innerHTML = XML.getNode( "ucAmt", recordXML ).firstChild.nodeValue;
	
	var acAmtCell = row.appendChild( document.createElement( "td" ) );
	acAmtCell.innerHTML = XML.getNode( "acAmt", recordXML ).firstChild.nodeValue;
	
	var grossAmtCell = row.appendChild( document.createElement( "td" ) );
	grossAmtCell.innerHTML = XML.getNode( "grossAmt", recordXML ).firstChild.nodeValue;
	
	var grantAmtCell = row.appendChild( document.createElement( "td" ) );
	grantAmtCell.innerHTML = XML.getNode( "grantAmt", recordXML ).firstChild.nodeValue;
	
	var rcvdGrantCell = row.appendChild( document.createElement( "td" ) );
	rcvdGrantCell.innerHTML = XML.getNode( "rcvdAmt", recordXML ).firstChild.nodeValue;
	
	return row;
}	

//******************************************************
function getResult()
{
	var selectedRowIndex = IFDSTableManager.getTable( "GrantContrib_Table" ).getSelectedRowIndex();
	var selectedRow = UTL.getElem( "GrantContrib_Table" ).lastChild.childNodes[selectedRowIndex];
	
	var retString = "";
	
	retString += "EntityID=" + selectedRow.entityID;
	retString += ";"
	retString += "TransID=" + selectedRow.transID;
	
	return retString;
}
	