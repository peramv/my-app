var _popupDivId 	= "classPopupDiv";

var _fromFundFld 	= null;
var _toFundFld 		= null;
var _popupFieldMap 	= null;
var _fieldFlagMap	= null;


//******************************************************
function loading()
{
	_fromFundFld = UTL.getElem( "fromFundFld" );
	_toFundFld = UTL.getElem( "toFundFld" );
	
	_popupFieldMap = {};	
	_popupFieldMap["fromClassCode"] = UTL.getElem( "Popup_fromClassCodeFld" );	
	_popupFieldMap["classCode"] = UTL.getElem( "Popup_classCodeFld" );	
	_popupFieldMap["deff"] = UTL.getElem( "Popup_deffFld" );
	_popupFieldMap["isin"] = UTL.getElem( "Popup_isinFld" );
	_popupFieldMap["cusip"] = UTL.getElem( "Popup_cusipFld" );
	_popupFieldMap["wkn"] = UTL.getElem( "Popup_wknFld" );
	_popupFieldMap["extID"] = UTL.getElem( "Popup_extIDFld" );
	_popupFieldMap["fundLoadGrp"] = UTL.getElem( "Popup_fundLoadGrpFld" );
	
	_fieldFlagMap = {};	
	 	
	IFDSTableManager.init();
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn" );
	IFDSTableManager.getTable( "classList_Table" ).setOnRowSelectedFunction( selectHandler_ClassLookupResultsTable );
	IFDSTableManager.getTable( "classList_Table" ).setOnRowExecuteFunction( openModifyPopup );
	
	disableClassLookupBtn();
	disableAddBtn();
	disableModifyBtn();
	disableClearAllBtn();
	disableExcludeAllCheckbox();	
}

//******************************************************
function clickHandler_addBtn()
{
	openAddPopup();
}

//******************************************************
function clickHandler_modifyBtn()
{
	openModifyPopup();
}

//******************************************************
function clickHandler_cancelPopupBtn()
{
	for(var i in _fieldFlagMap)
	{
		if (i != _fromFundFld.id && i != _toFundFld.id)
		{
			_fieldFlagMap[i].hide();
		}
	}
	Desktop.hidePopup( _popupDivId );	
}

//******************************************************
function clickHandler_savePopupBtn()
{	
	doClassRecordSave();
}

//******************************************************
function clickHandler_classLookupBtn()
{
	doClassLookup();
}

//******************************************************
function clickHandler_okBtn()
{
	doCopyClassUpdates();
}

//******************************************************
function clickHandler_excludeCheckbox( checkbox )
{	
	if ( checkbox.checked )
	{
		excludeClass( checkbox.rowNum );
	}
	else
	{
		includeClass( checkbox.rowNum );				
	}
	
	window.event.cancelBubble = true;
}

//******************************************************
function clickHandler_clearAllBtn()
{
	clearClassListTable();
}

//******************************************************
function updateHandler_fromFundFld()
{
	if ( _fromFundFld._suggestDataObj )
	{		
		enableClassLookupBtn();
	}
	else
	{	
		disableClassLookupBtn();
	}
		
	if ( _fieldFlagMap[_fromFundFld.id] )
	{
		_fieldFlagMap[_fromFundFld.id].hide();
	}
	
	var classListRows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	if ( classListRows.length > 0 )
	{
		clearClassListTable();
		return false;
	}
}

//******************************************************
function updateHandler_toFundFld()
{
	IFDSTableManager.getTable( "classList_Table" ).clearSelectedRowIndex();
	disableModifyBtn();		
	
	if ( _toFundFld._suggestDataObj )
	{
		enableAddBtn();		
	}
	else
	{
		disableAddBtn();		
	}
			
	if ( _fieldFlagMap[_toFundFld.id] )
	{
		_fieldFlagMap[_toFundFld.id].hide();
	}
}

//******************************************************
function keyupHandler_fromFundFld()
{	
	if ( KeyMap.getKeyDesc( window.event.keyCode, KeyMap.KEYUP ) == KeyMap.ENTER
			&& _fromFundFld._suggestDataObj )	 
	{
		doClassLookup();
	}
}

//******************************************************
function dblclickHandler_classListRow()
{	
	openModifyPopup();	
}

//******************************************************
function clickHandler_cancelBtn()
{	
	var allowCancel = true;
	var classListRows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	if ( classListRows.length > 0 )
	{
		allowCancel = confirm( "The fund class list has unsaved changes.\n\nDo you wish to proceed?" );				
	}
	
	if ( allowCancel )
	{
		UTL.getElem( "btnCancel" ).click();
	}
}

//******************************************************
function clickHandler_excludeAllCheckbox( checkbox )
{	
	if ( checkbox.checked )
	{
		excludeAllClasses();
	}
}

//******************************************************
function openAddPopup()
{	
	IFDSTableManager.getTable( "classList_Table" ).clearSelectedRowIndex();
	clearPopupFields();
	Desktop.showPopup( _popupDivId, "Add Copy Class" );	
}

//******************************************************
function openModifyPopup()
{	
	var selectedRowIndex = IFDSTableManager.getTable( "classList_Table" ).getSelectedRowIndex();
	 
	if ( selectedRowIndex != null )
	{
		var selectedRow = UTL.getElem( "classList_Table" ).lastChild.childNodes[selectedRowIndex];
		_popupFieldMap["fromClassCode"].value = selectedRow.fromClassCode;
		_popupFieldMap["classCode"].value = selectedRow.classCode;
		_popupFieldMap["deff"].value = selectedRow.deff;
		_popupFieldMap["isin"].value = selectedRow.isin;
		_popupFieldMap["cusip"].value = selectedRow.cusip;
		_popupFieldMap["wkn"].value = selectedRow.wkn;
		_popupFieldMap["extID"].value = selectedRow.extID;
		_popupFieldMap["fundLoadGrp"].value = selectedRow.fundLoadGrp;
						
		Desktop.showPopup( _popupDivId, "Modify Copy Class" );
	}
	else
	{
		alert( "FUNCTION ERROR: no record selected to modify" );
	}	
}

//******************************************************
function clearPopupFields()
{
	for ( var i in _popupFieldMap )
	{
		_popupFieldMap[i].value = "";
		if ( _fieldFlagMap[_popupFieldMap[i].id] )
		{
			_fieldFlagMap[_popupFieldMap[i].id].hide();
		}
	}	
}

//******************************************************
function getFundOnlySuggestURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]         = _vCZ;
    paramMap["jobname"]    = "General_FundOnlySuggest";
    paramMap["ruserId"]    = _ruserId;
    paramMap["sessionId"]  = _sessionId;
	paramMap["envName"]    = _envName;    
    
    if ( nextRecNum )
    {
       paramMap["startRecordNum"] = nextRecNum;        
    }
    paramMap["searchData"] = searchStr;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );    
    return url;        
}

//******************************************************
function doClassLookup()
{	
	if ( _fromFundFld._suggestDataObj )
	{			
		sendClassLookupRequest( doClassLookup_callback );		
	}
	else
	{
		alert( "FUNCTION ERRROR: From Fund is required" );
	}
}

//******************************************************
function doClassLookup_callback( classListXML )
{	
	if ( classListXML )
	{
		reloadClassListTable( classListXML );					
		disableModifyBtn();
	
		if( isClassListTableEmpty() )
		{						
			disableClearAllBtn();
			disableExcludeAllCheckbox(); 
		}
		else
		{		
			enableClearAllBtn();
			enableExcludeAllCheckbox();								
		}																
	}
}

//******************************************************
function sendClassLookupRequest( callbackFn )
{		
	function sendClassLookupRequest_callback( responseText )
	{
		Desktop.hideProcessingIndicator();
		
		var classListXML = null;
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
					classListXML = XML.getNode( "/responseContents/classListResponse", responseXML );
				}
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: getClassList error caught: " + e.description ); 		
		}
		
		callbackFn( classListXML );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "FundSetup_ClassCopy_Lookup";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
	paramMap["fundCode"] = _fromFundFld._suggestDataObj["fundCode"];	
            
    var url = HTTP.buildURL( _vServletPath );   
                		    	 
	var req = HTTP.getPOSTRequest( url );
	var headers = {};
	headers['Content-type'] = "application/x-www-form-urlencoded";
	req.setHeaders(headers);			
	req.setCallbackFunction( sendClassLookupRequest_callback );	
	Desktop.showProcessingIndicator();
	req.send(HTTP.buildURLParamString(paramMap));		
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
function reloadClassListTable( classListXML )
{			
	var resultsTableHTML = classListXML.firstChild.xml;
	
	var resultsTableDiv = UTL.getElem( "ClassList_TableDiv" );
	resultsTableDiv.removeChild( resultsTableDiv.firstChild );
	resultsTableDiv.innerHTML = resultsTableHTML;
		
	IFDSTableManager.reInitTable( "classList_Table" );	
}

//******************************************************
function enableClassLookupBtn()
{
	UTL.getElem( "btnClassLookup" ).disabled = false;	
}

//******************************************************
function disableClassLookupBtn()
{
	UTL.getElem( "btnClassLookup" ).disabled = true;	
}

//******************************************************
function enableClearAllBtn()
{
	UTL.getElem( "btnClearAll" ).disabled = false;
}

//******************************************************
function disableClearAllBtn()
{
	UTL.getElem( "btnClearAll" ).disabled = true;
}

//******************************************************
function enableAddBtn()
{
	UTL.getElem( "btnClassAdd" ).disabled = false;
}

//******************************************************
function disableAddBtn()
{
	UTL.getElem( "btnClassAdd" ).disabled = true;
}

//******************************************************
function enableModifyBtn()
{
	UTL.getElem( "btnClassModify" ).disabled = false;
}

//******************************************************
function disableModifyBtn()
{
	UTL.getElem( "btnClassModify" ).disabled = true;
}

//******************************************************
function disableExcludeAllCheckbox()
{
	UTL.getElem( "excludeAllCheckbox" ).disabled = true;
}

//******************************************************
function enableExcludeAllCheckbox()
{
	UTL.getElem( "excludeAllCheckbox" ).disabled = false;
}

//******************************************************
function isClassListTableEmpty()
{	
	var table = IFDSTableManager.getTable( "classList_Table" );
	return table.getNumRows() == 0;		
}

//******************************************************
function selectHandler_ClassLookupResultsTable( rowIndex )
{
	if ( rowIndex != null )
	{
		if ( _toFundFld._suggestDataObj )
		{		
			enableModifyBtn();
		}
	}
	else
	{
		disableModifyBtn();
	}	
}

//******************************************************
function doClassRecordSave()
{	
	if ( _toFundFld._suggestDataObj )
	{
		if ( !isMissingReqClassFields() )
		{
			sendValidationRequest( doClassRecordSave_callback );
		}		
	}
	else
	{
		alert( "FUNCTION ERROR: 'To Fund' is missing" );		
	}
}

//******************************************************
function doClassRecordSave_callback( validationXML )
{	
	var isValid = true;
	if ( validationXML != null )
	{				
		var validationStatus = XML.getNode( "status", validationXML ).firstChild.nodeValue;
		if ( validationStatus == "Rejected" )
		{
			var errorNodeArray = XML.getNodes( "Errors/Error", validationXML );
			for ( var i = 0; i < errorNodeArray.length; i++ )
			{
				var fld = XML.getNode( "field", errorNodeArray[i] ).firstChild.nodeValue;
				var desc = XML.getNode( "desc", errorNodeArray[i] ).firstChild.nodeValue;
				Desktop.paintFieldErrorFlag( _fieldFlagMap, _popupFieldMap[fld].id, desc );
			}
			isValid = false;
		}
	}
	else
	{
		isValid = false;
	}
	
	if( isValid )
	{
		var table = IFDSTableManager.getTable( "classList_Table" );		
		var selectedRowIndex = table.getSelectedRowIndex();
		if ( selectedRowIndex == null )
		{
			addRecordToClassListTable();
			enableClearAllBtn();
			enableExcludeAllCheckbox();
		}
		else
		{
			updateExistingClassRecord( selectedRowIndex );
		}
		Desktop.hidePopup( _popupDivId );
	}	
}

//******************************************************
function isMissingReqClassFields()
{
	var missingFields = false;
	
	if ( _popupFieldMap["fromClassCode"].value == "" )
	{		
		Desktop.paintFieldErrorFlag( _fieldFlagMap, _popupFieldMap["fromClassCode"].id, "From Class is required" );
		missingFields = true;
	}	
	
	if ( _popupFieldMap["classCode"].value == "" )
	{		
		Desktop.paintFieldErrorFlag( _fieldFlagMap, _popupFieldMap["classCode"].id, "New Class Code is required" );
		missingFields = true;
	}
	
	if ( _popupFieldMap["deff"].value == "" )
	{		
		Desktop.paintFieldErrorFlag( _fieldFlagMap, _popupFieldMap["deff"].id, "Effective Date is required" );
		missingFields = true;
	}	
		
	return missingFields;
}

//******************************************************
function sendValidationRequest( callbackFn )
{	
	function sendValidationRequest_callback( responseText )
	{
		var responseXML = null;
		var validationXML = null;
				
		try 
		{
			responseXML = XML.parseToXML( responseText );
			if ( responseXML && responseErrorFound( responseXML ) )
			{
				displayResponseError( responseXML );		
			}
			else
			{
				validationXML = XML.getNode( "/responseContents/validationResponse", responseXML );
			}											
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: isValidFundInfo error caught: " + e.description ); 		
		}
		
		callbackFn( validationXML );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "FundSetup_ClassCopy_Validate";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
	paramMap["fundCode"] = _toFundFld._suggestDataObj["fundCode"];
	paramMap["classCode"] = _popupFieldMap["classCode"].value;
	paramMap["deff"] = _popupFieldMap["deff"].value;
	paramMap["wkn"] = _popupFieldMap["wkn"].value;
	paramMap["isin"] = _popupFieldMap["isin"].value;
	paramMap["cusip"] = _popupFieldMap["cusip"].value;
	paramMap["extID"] = _popupFieldMap["extID"].value;
	paramMap["fundLoadGrp"] = _popupFieldMap["fundLoadGrp"].value;
			        
    var url = HTTP.buildURL( _vServletPath );                    		    	
	    	   
	var req = HTTP.getPOSTRequest( url );
	var headers = {};
	headers['Content-type'] = "application/x-www-form-urlencoded";
	req.setHeaders(headers);
	req.setCallbackFunction( sendValidationRequest_callback );	
	req.send(HTTP.buildURLParamString(paramMap));
}

//******************************************************
function updateExistingClassRecord( rowIndex )
{
	var tr = UTL.getElem( "classList_Table" ).lastChild.childNodes[rowIndex];
	populateRowFromPopup( tr );
	
	tr.firstChild.innerHTML = "";
}

//******************************************************
function addRecordToClassListTable()
{
	var rowNum = UTL.getElem( "classList_Table" ).lastChild.childNodes.length;
	var tr = document.createElement( "TR" );		
	tr.ondblclick = dblclickHandler_classListRow;
	for ( var i = 0; i < 10; i++ )
	{
		tr.appendChild( document.createElement( "TD" ) );
	}
	
	tr.childNodes[1].innerHTML = "<input type='checkbox' onclick='clickHandler_excludeCheckbox( this );' rowNum='" + rowNum + "'/>";
	tr.exclude = "false";
	UTL.getElem( "classList_Table" ).lastChild.appendChild( tr );	
	
	populateRowFromPopup( tr );
	
	IFDSTableManager.reInitTable( "classList_Table" );
}

//******************************************************
function populateRowFromPopup( row )
{	
	row.childNodes[1].firstChild.checked = false;
	
	row.childNodes[2].innerHTML = _popupFieldMap["fromClassCode"].value;
	row.fromClassCode = _popupFieldMap["fromClassCode"].value;

	row.childNodes[3].innerHTML = _popupFieldMap["classCode"].value;;	
	row.classCode = _popupFieldMap["classCode"].value;
	
	row.childNodes[4].innerHTML = _popupFieldMap["deff"].value;;	
	row.deff = _popupFieldMap["deff"].value;
	
	row.childNodes[5].innerHTML = _popupFieldMap["isin"].value;;	
	row.isin = _popupFieldMap["isin"].value;
	
	row.childNodes[6].innerHTML = _popupFieldMap["cusip"].value;;	
	row.cusip = _popupFieldMap["cusip"].value;
	
	row.childNodes[7].innerHTML = _popupFieldMap["wkn"].value;;	
	row.wkn = _popupFieldMap["wkn"].value;
	
	row.childNodes[8].innerHTML = _popupFieldMap["extID"].value;;	
	row.extID = _popupFieldMap["extID"].value;
	
	row.childNodes[9].innerHTML = _popupFieldMap["fundLoadGrp"].value;;	
	row.fundLoadGrp = _popupFieldMap["fundLoadGrp"].value;	
}

//******************************************************
function doCopyClassUpdates()
{	
	if ( _fromFundFld._suggestDataObj && _toFundFld._suggestDataObj )
	{
		var updatesXML = buildCopyClassUpdatesXML();
		if ( updatesXML != null )
		{
			sendCopyClassUpdatesRequest( updatesXML, doCopyClassUpdates_callback );
		}				
	}
	else
	{
		if ( !_fromFundFld._suggestDataObj )
		{
			Desktop.paintFieldErrorFlag( _fieldFlagMap, _fromFundFld.id, "From Fund is required to perform class copy updates" );			
		}
		
		if ( !_toFundFld._suggestDataObj )
		{
			Desktop.paintFieldErrorFlag( _fieldFlagMap, _toFundFld.id, "To Fund is required to perform class copy updates" );			
		}		
	}		
}

//******************************************************
function doCopyClassUpdates_callback( isSuccess )
{
	if ( isSuccess )
	{
		alert( "Fund class copy submitted successfully." );
		UTL.getElem( "btnOK" ).click();
	}
	else
	{
		alert( "Errors occured during fund class copy. Operation could not be completed." )
	}
}

//******************************************************
function sendCopyClassUpdatesRequest( updatesXML, callbackFn )
{		
	function submitCopyClassUpdates_callback( responseText )
	{
		Desktop.hideProcessingIndicator();
		
		var success = true;
		var responseXML = null;				
		try 
		{
			responseXML = XML.parseToXML( responseText );										
		}
		catch( e )
		{ 
			alert( "submitCopyClassUpdates error caught: " + e.description ); 		
		}
		
		if ( responseXML != null )
		{
			if ( responseErrorFound( responseXML ) )
			{
				displayResponseError( responseXML );
				success = false;			
			}
			else
			{
				var updateStatus = XML.getNode( "/responseContents/updateResponse/status", responseXML ).firstChild.nodeValue;
				if ( updateStatus == "Rejected" )
				{
					success = false;
				}
			}
		}
		else
		{
			success = false;
		}
		
		callbackFn( success );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "FundSetup_ClassCopy_Update";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    //paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
			        
    var url = HTTP.buildURL( _vServletPath, paramMap );                    		    	
	    	   
	var req = HTTP.getPOSTRequest( url );	
	req.setCallbackFunction( submitCopyClassUpdates_callback );
	Desktop.showProcessingIndicator();
	var submitXML = XML.createNodeStr("data", XML.createNodeStr("sessionId", _sessionId) + updatesXML);	
	req.send( submitXML );

}

//******************************************************
function buildCopyClassUpdatesXML()
{
	var rowErrorMap = {};
	var rowErrorCount = 0;
	var classRecordCount = 0;
	
	var xml = "";
	xml += XML.createNodeStr( "copyFromFund", _fromFundFld._suggestDataObj["fundCode"] );
	xml += XML.createNodeStr( "copyToFund", _toFundFld._suggestDataObj["fundCode"] );
	xml += XML.createNodeStr( "copyBasicClsInfo", ( UTL.getElem( "basicInfoCheckbox" ).checked ? "yes" : "no" ) );
	xml += XML.createNodeStr( "copyFeeParms", ( UTL.getElem( "feeParmsCheckbox" ).checked ? "yes" : "no" ) );
	xml += XML.createNodeStr( "copyShGrpFunds", ( UTL.getElem( "shGrpFundsCheckbox" ).checked ? "yes" : "no" ) );
	xml += XML.createNodeStr( "copyRegTrustee", ( UTL.getElem( "regTrusteeCheckbox" ).checked ? "yes" : "no" ) );
	xml += XML.createNodeStr( "copyPShip", ( UTL.getElem( "pshipCheckbox" ).checked ? "yes" : "no" ) );
	
	var classListXML = "";
	var classListRows = UTL.getElem( "classList_Table" ).lastChild.childNodes;	
	for ( var i = 0; i < classListRows.length; i++ )
	{
		var row = classListRows[i];			
		if ( row.exclude == "false" )
		{
			var classXML = "";					
			if ( ( row.fromClassCode != "" && row.fromClassCode.length > 0 ) 
			 		&& ( row.classCode != "" && row.classCode.length > 0 )
			 		&& ( row.deff != "" && row.deff.length > 0 ) ) 
			{					
				classXML += XML.createNodeStr( "copyFromClass", row.fromClassCode );
				classXML += XML.createNodeStr( "copyToClass", row.classCode );
				classXML += XML.createNodeStr( "deff", row.deff );
				classXML += XML.createNodeStr( "isin", row.isin );
				classXML += XML.createNodeStr( "cusip", row.cusip );
				classXML += XML.createNodeStr( "wkn", row.wkn );
				classXML += XML.createNodeStr( "extID", row.extID );
				classXML += XML.createNodeStr( "fundLoadGrp", row.fundLoadGrp );
				classXML = "<CopyClassInfo recordSource = '" + i + "'>" + classXML + "</CopyClassInfo>";								
			}
			else
			{
				rowErrorCount++;
				rowErrorMap[i] = "Missing required fields"; 
			}
			
			classRecordCount++;
			classListXML += classXML;
		}			
	}
	
	if ( classRecordCount == 0 )
	{		
		alert( "No class records entered/included for update.")
		xml = null;
	}
	else if ( rowErrorCount > 0 )	
	{
		paintClassListErrors( rowErrorMap );
		xml = null;
	}
	else
	{
		classListXML = XML.createNodeStr( "Classes", classListXML );	
		xml = XML.createNodeStr( "CopyClassXML", xml + classListXML );
	}	

	return xml;		
}

//******************************************************
function clearClassListTable()
{
	var rows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	for ( var i = rows.length - 1; i >= 0; i-- )
	{
		var row = rows[i];
		row.parentNode.removeChild( row );
	}
	
	IFDSTableManager.reInitTable( "classList_Table" );
	
	disableModifyBtn();
	disableClearAllBtn();
	disableExcludeAllCheckbox();		
}

//******************************************************
function clearClassListErrors()
{
	var rows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	for ( var i = 0; i < rows.length; i++ )
	{
		var row = rows[i];
		row.childNodes[0].innerHTML = "";
	}
}

//******************************************************
function paintClassListErrors( rowErrorMap )
{	
	var rows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	for ( var i in rowErrorMap )
	{
		var row = rows[i];
		var td = row.childNodes[0]; 
		td.innerHTML = "<span class='Desktop_ErrorFlag'></span>"; 
		td.title = rowErrorMap[i];
	}
}

//******************************************************
function excludeAllClasses()
{
	var rows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	for ( var i = 0; i < rows.length; i++ )
	{
		var row = rows[i];
		var checkbox = row.childNodes[1].firstChild;
		checkbox.checked = true;
		
		excludeClass( i );		
	}
}

//******************************************************
function excludeClass( rowNum )
{
	var rows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	rows[rowNum].exclude = "true";
	rows[rowNum].firstChild.innerHTML = "";
}

//******************************************************
function includeClass( rowNum )
{
	var rows = UTL.getElem( "classList_Table" ).lastChild.childNodes;
	rows[rowNum].exclude = "false";
	UTL.getElem( "excludeAllCheckbox" ).checked = false;
}	