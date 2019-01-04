var _errorFlagMap = null;
var _accountNum = null;
var _moreRecordsExist = null;
var _rangeStartForNext = null;
var _recTypeLists = null;

//******************************************************
function loading()
{
	IFDSTableManager.init();
	_errorFlagMap = {};
		
	IFDSTableManager.getTable( "FileList_Table" ).setOnRowSelectedFunction( selectHandler_FileListTable );
	updateFilter();
}

//******************************************************
function clickHandler_allFld()
{
	var allFld = UTL.getElem( "allFld" );
	var accountFld = UTL.getElem( "accountFld" );
	if ( allFld.checked )
	{
		_accountNum = "ALL";
		accountFld.value = "";
		accountFld.disabled = true;
		updateFilter();
	}
	else
	{
		_accountNum = null;
		accountFld.disabled = false;
		accountFld.focus();
	}
}

//******************************************************
function changeHandler_fileTypeFld()
{
	updateFilterFld(UTL.getElem('recordTypeFld'), _recTypeLists[UTL.getElem('fileTypeFld').value]);
}

//******************************************************
function selectHandler_FileListTable()
{
	var selectedIndex = IFDSTableManager.getTable( "FileList_Table" ).getSelectedRowIndex();
	var selectedRow = UTL.getElem( "FileList_Table" ).lastChild.childNodes[selectedIndex];
	clearFieldTable();
	populateFieldTable( selectedRow.fields );	
}

//******************************************************
function populateFieldTable( fieldArray )
{		
	var fieldListTable = UTL.getElem( "FieldList_Table" );
	var curRow = null;
	for ( var i = 0; i < fieldArray.length; i++ )
	{		
		if (i % 2 == 0) 
		{
			curRow = document.createElement("tr");			
		}			
		
		var fieldNameCell = curRow.appendChild( document.createElement( "td" ) );
		fieldNameCell.innerHTML = fieldArray[i].fieldNam;
		fieldNameCell.title = fieldArray[i].fieldNam; 	
		var fieldValCell = curRow.appendChild( document.createElement( "td" ) );
		fieldValCell.innerHTML = fieldArray[i].fieldVal;
		fieldValCell.title = fieldArray[i].fieldVal;
		
		if ( i % 2 != 0 )
		{
			fieldListTable.lastChild.appendChild( curRow );
		}
	}
	
	IFDSTableManager.reInitTable( "FieldList_Table" );		
}

//******************************************************
function clearFieldTable()
{
	var fieldListTable = UTL.getElem( "FieldList_Table" );
	while( fieldListTable.lastChild.lastChild )
	{
		fieldListTable.lastChild.removeChild( fieldListTable.lastChild.lastChild);
	}
}

//******************************************************
function clickHandler_searchBtn()
{
	if ( validateFilter() )
	{
		doReload( false );
	}
}

//******************************************************
function clickHandler_moreBtn()
{
	doReload( true );	
}

//******************************************************
function validateFilter()
{
	var isValid = true;
	var taxYear = UTL.getElem( "taxYearFld" ).value;
	if ( taxYear == null || taxYear.length != 4 || isNaN(taxYear) || parseInt(taxYear) > 9999)
	{		
		Desktop.paintFieldErrorFlag( _errorFlagMap, "taxYearFld", "Invalid input" );
		isValid = false;
	}
	
	return isValid;
}

//******************************************************
function doReload( appendRecords )
{
	sendReloadRequest( doReload_callback );
	
	function doReload_callback( resultsXML )
	{
		if ( resultsXML )
		{
			//prompt( "", resultsXML.xml );
			populateFileTable( resultsXML, appendRecords );		
						
			if ( _moreRecordsExist )
			{
				UTL.getElem( "moreBtn" ).disabled = false;
			}
			else
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
		//prompt("", responseText)			
		Desktop.hideProcessingIndicator();
		
		var dataXML = null;		
		
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
					dataXML = XML.getNode( "/responseContents/InterfaceFileData", responseXML );
					
					if ( XML.getNode( "/responseContents/RecordRange/moreRecordsExist", responseXML ) )
					{					
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
					else
					{
						_moreRecordsExist = null;
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
    paramMap["jobname"]           = "RESPInterfaceFile_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
	       
	paramMap["accountNum"] = _accountNum;
	paramMap["RESPBenefID"] = UTL.getElem( "respBenefFld" ).value;
	paramMap["taxYear"] = UTL.getElem( "taxYearFld" ).value;
	paramMap["fileType"] = UTL.getElem( "fileTypeFld" ).value;	
	paramMap["recType"] = UTL.getElem( "recordTypeFld" ).value;
	
	if ( _rangeStartForNext != null ) {
		paramMap["startRecNum"] = _rangeStartForNext;
	}	
	            
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getGETRequest( url );			
	req.setCallbackFunction( sendReloadRequest_callback );	
	Desktop.showProcessingIndicator();
	req.send();		
}

//******************************************************
function clearFileTable()
{
	var table = UTL.getElem( "FileList_Table" );
	while( table.lastChild.lastChild )
	{
		table.lastChild.removeChild( table.lastChild.lastChild );
	}
	
	clearFieldTable();
}

//******************************************************
function populateFileTable( dataXML, appendRecords )
{
	if (!appendRecords) {
		clearFileTable();
	}
	
	var table = UTL.getElem( "FileList_Table" );	
	
	var fileDetailNodes = XML.getNodes( "FileDetail", dataXML );	
	
	for ( var i = 0; i < fileDetailNodes.length; i++ )
	{
		var row = buildResultRow( fileDetailNodes[i] );
		
		var fileRecordsNodes = XML.getNodes( "FileRecords", fileDetailNodes[i] );
		for ( var j = 0; j < fileRecordsNodes.length; j++ )
		{	
			row.fields = buildFieldArray( XML.getNodes( "fileRecord", fileRecordsNodes[j] ) ); 		 
		}
				
		table.lastChild.appendChild( row ); 
	}
	
		
	IFDSTableManager.reInitTable( "FileList_Table" );
}

//******************************************************
function buildFieldArray( fileRecordNodes )
{
	var fieldArray = [];
	for( var i = 0; i < fileRecordNodes.length; i++ )
	{
		fieldArray[i] = {};
		fieldArray[i].fieldNam = XML.getNode( "fieldNam", fileRecordNodes[i] ).firstChild.nodeValue;
		var fieldValNode = XML.getNode( "fieldVal", fileRecordNodes[i] ).firstChild;
		fieldArray[i].fieldVal = ( fieldValNode ? fieldValNode.nodeValue : "" );		
	}
	return fieldArray;
}	

//******************************************************
function buildResultRow( recordXML )
{
	var row = document.createElement( "tr" );	
		
	var fileNameCell = row.appendChild( document.createElement( "td" ) );
	var fileNamNode = XML.getNode( "fileNam", recordXML ).firstChild;	
	fileNameCell.innerHTML = ( fileNamNode ? fileNamNode.nodeValue : "" );
	fileNameCell.title = fileNameCell.innerHTML;	
	
	var acctCell = row.appendChild( document.createElement( "td" ) );
	var acctNode = XML.getNode( "acct", recordXML ).firstChild;
	acctCell.innerHTML = (acctNode ? acctNode.nodeValue : "" );
	acctCell.title = acctCell.innerHTML; 	 
	
	var benNameCell = row.appendChild( document.createElement( "td" ) );
	var benNameNode = XML.getNode( "benName", recordXML ).firstChild;
	benNameCell.innerHTML = ( benNameNode ? benNameNode.nodeValue : "" );
	benNameCell.title = benNameCell.innerHTML;	
	
	var recTypeCell = row.appendChild( document.createElement( "td" ) );
	var recTypeNode = XML.getNode( "recTyp", recordXML ).firstChild;	
	recTypeCell.innerHTML = ( recTypeNode ? recTypeNode.nodeValue : "" );
	recTypeCell.title = recTypeCell.innerHTML;
	row.recType = recTypeCell.innerHTML;
		
	var procDateCell = row.appendChild( document.createElement( "td" ) );
	var procDateNode = XML.getNode( "procDate", recordXML ).firstChild;
	procDateCell.innerHTML = ( procDateNode ? procDateNode.nodeValue : "" )
	procDateCell.title = procDateCell.innerHTML;	
	
	var NEQCell = row.appendChild( document.createElement( "td" ) );
	var NEQDateNode = XML.getNode( "NEQ", recordXML ).firstChild;
	NEQCell.innerHTML = (NEQDateNode ? NEQDateNode.nodeValue : "" );
	NEQCell.title = NEQCell.innerHTML;	
		
	
	return row;
}	

//******************************************************
function getAccountSuggestURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]         = _vCZ;
    paramMap["jobname"]    = "General_AccountSearch";
    paramMap["ruserId"]    = _ruserId;
    paramMap["sessionId"]  = _sessionId;
	paramMap["envName"]    = _envName;    
	paramMap["maxRecords"] = 10;
    
    if ( nextRecNum )
    {
       paramMap["startRecordNum"] = nextRecNum;        
    }
    paramMap["searchData"] = searchStr;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );    
    return url;        
}

//*****************************************************
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
		DesktopError.displayProcessingError( "RESP Account Termination Information", errorMsg );  
	}
	else
	{
		alert( errorMsg );
	}
}

//******************************************************
function updateHandler_accountFld()
{
	var accountFld = UTL.getElem( "accountFld" );
	if ( accountFld._suggestDataObj )
	{		
		if ( accountFld._suggestDataObj["acctNum"] != _accountNum )
		{
			_accountNum = accountFld._suggestDataObj["acctNum"];
			updateFilter();
		}
	}
	else
	{
		_accountNum = null;
	}	
}

//******************************************************
function updateFilter()
{
	sendReInitRequest( updateFilter_callback );
	
	function updateFilter_callback( initDataXML )
	{
		//prompt( "", initDataXML.xml );
		if (initDataXML != null) {
			updateFilterFld( UTL.getElem( "respBenefFld" ), XML.getNodes( "List[@listName='BeneficiaryList']/Element", initDataXML ) );			
			updateFilterFld( UTL.getElem( "taxYearFld" ), XML.getNodes( "List[@listName='TaxYearList']/Element", initDataXML ) );
			
			var fileTypeNodes = XML.getNodes( "List[@listName='FileTypeList']/Element", initDataXML );
			updateFilterFld( UTL.getElem( "fileTypeFld" ), fileTypeNodes );
			_recTypeLists = {};
			for (var i = 0; i < fileTypeNodes.length; i++) 
			{				
				var fileType = XML.getNode( 'code', fileTypeNodes[i] ).firstChild.nodeValue;
				_recTypeLists[fileType] = XML.getNodes( "List[@listName='" + fileType + "RecTypeList']/Element", initDataXML );
				updateFilterFld( UTL.getElem( "fileTypeFld" ), XML.getNodes( "List[@listName='FileTypeList']/Element", initDataXML ) );
			}
 			updateFilterFld(UTL.getElem('recordTypeFld'), _recTypeLists[UTL.getElem('fileTypeFld').options[0].value]);
		}
	}	
}

//******************************************************
function updateFilterFld( fld, optionXMLNodes )
{	
	while( fld.options.length > 0 )
	{
		fld.remove( 0 );
	}	
		
	for ( var i = 0; i < optionXMLNodes.length; i++ )	
	{
		var newOption = document.createElement( "option" );
		newOption.value = XML.getNode( "code", optionXMLNodes[i] ).firstChild.nodeValue;
		newOption.text = XML.getNode( "value", optionXMLNodes[i] ).firstChild.nodeValue;
		fld.add( newOption );
	}
}

//******************************************************
function sendReInitRequest( callbackFn )
{	
	function sendReInitRequest_callback( responseText )
	{		
		//prompt("", responseText);
		Desktop.hideProcessingIndicator();
		
		var dataXML = null;		
		
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
					dataXML = XML.getNode( "/responseContents/InterfaceFileInitData", responseXML );
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
    paramMap["jobname"]           = "RESPInterfaceFile_ReInit";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
	       
	paramMap["accountNum"] = _accountNum;
	            
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getGETRequest( url );			
	req.setCallbackFunction( sendReInitRequest_callback );	
	Desktop.showProcessingIndicator();
	req.send();		
}

