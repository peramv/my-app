var _MODIFY = "mod";
var _DELETE = "del";
var _CANCEL = "canc";

var _action = null;

var _accountNum = null;
var _respBenefId = null;
var _selectedRowIndex = null;
var _moreRecordsExist = null;
var _rangeStartForNext = null;

var _errorFlagMap = null;

var _updatesFlag = false;

var _modPerm = null;
var _delPerm = null;


//******************************************************
function loading()
{
	IFDSTableManager.init();
	IFDSTableManager.getTable( "EntryList_Table" ).setOnRowSelectedFunction( rowSelectedHandler );
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );
	disableActionBtns();
	
	//UTL.getElem( "MoreBtn" ).disabled = !_moreRecordsExist;
	
	_errorFlagMap = {};				
}

//******************************************************
function enableActionBtns()
{
	var selectedRow = UTL.getElem( "EntryList_Table" ).lastChild.childNodes[_selectedRowIndex];
	
	if (_modPerm) {
		if (selectedRow.runMode == _CANCEL) {
			UTL.getElem("ModifyBtn").disabled = true;
			UTL.getElem("CancelBtn").disabled = true;
		}
		else {
			if (selectedRow.reported.toLowerCase() == "yes") {
				UTL.getElem("ModifyBtn").disabled = true;
				UTL.getElem("CancelBtn").disabled = false;
			}
			else {
				UTL.getElem("ModifyBtn").disabled = false;
				UTL.getElem("CancelBtn").disabled = true;
			}
		}
	}
	
	if ( _delPerm ) 
	{
		if ( selectedRow.reported.toLowerCase() == 'yes' )
		{
			UTL.getElem("DeleteBtn").disabled = true;
		}
		else
		{
			UTL.getElem("DeleteBtn").disabled = false;
		}
	}
	
	UTL.getElem( "ExpandBtn" ).disabled = false;	
}

//******************************************************
function disableActionBtns()
{
	UTL.getElem( "ExpandBtn" ).disabled = true;	
	UTL.getElem( "ModifyBtn" ).disabled = true;
	UTL.getElem( "DeleteBtn" ).disabled = true;
	UTL.getElem( "CancelBtn" ).disabled = true;
}

//******************************************************
function rowSelectedHandler()
{
	_selectedRowIndex = IFDSTableManager.getTable( "EntryList_Table" ).getSelectedRowIndex();
	enableActionBtns();	
}

//******************************************************
function clickHandler_ExpandBtn()
{
	var selectedRowIndex = IFDSTableManager.getTable( "EntryList_Table" ).getSelectedRowIndex();
	if ( selectedRowIndex != null )
	{
		populateDetailsPopup( selectedRowIndex );
		Desktop.showPopup( "DetailsPopupDiv" );	
	}
}

//******************************************************
function populateDetailsPopup( rowIndex )
{
	var row = UTL.getElem( "EntryList_Table" ).lastChild.childNodes[rowIndex];
	UTL.getElem( "DetailsPopup_CESGFld" ).innerHTML = row.cesg;
	UTL.getElem( "DetailsPopup_CLBFld" ).innerHTML = row.clb;
	UTL.getElem( "DetailsPopup_PGrantFld" ).innerHTML = row.pGrant;			
}

//******************************************************
function clickHandler_UpdateBtn( action )
{	
	if ( _selectedRowIndex != null )
	{
		doEntryModify( action );			
	}
}

//******************************************************
function doEntryModify( action )
{	
	populateActionPopup( action );
	var popupCaption = "RESP Account Termination - ";
	if ( action == _DELETE )
	{
		popupCaption += "Delete Entry";
	}
	else if ( action == _CANCEL )
	{
		popupCaption += "Cancel Entry";
	}
	else
	{
		popupCaption += "Modify Entry";
	}
	Desktop.showPopup( "ActionPopupDiv", popupCaption );					
				
}

//******************************************************
function doEntrySave()
{	
	if ( !IFDSDatepicker.isValidDateValue( UTL.getElem( "ActionPopup_TransDateFld" ).value, _dateFormat ) )
	{
		Desktop.paintFieldErrorFlag( _errorFlagMap, "ActionPopup_TransDateFld", "Invalid value" );
		return;
	}
	
	sendValidateRequest( buildValidateXMLFromPopup(), doEntrySave_callback )
	
	function doEntrySave_callback( isValid )
	{
		if ( isValid )
		{
			updateSelectedRow();
			Desktop.hidePopup( "ActionPopupDiv" );
			
			if ( UTL.getElem( "ActionPopup_RunModeFld" ).value != _MODIFY )
			{
				IFDSTableManager.getTable( "EntryList_Table" ).clearSelectedRowIndex();
				disableActionBtns();	
			}
			_updatesFlag = true;
		}
	}			
}

//******************************************************
function sendValidateRequest( validateXML, callbackFn )
{
	function sendValidateRequest_callback( responseText )
	{				
		var responseXML = null;
		try 
		{
			responseXML = XML.parseToXML( responseText );
			var isValid = true;			
			if ( responseXML )
			{
				if ( responseErrorFound( responseXML ) )
				{
					displayResponseError( responseXML );
					isValid = false;	
				}						
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendValidateRequest error caught: " + e.description ); 		
		}
		
		callbackFn( isValid );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPAcctTermInfo_Validate";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );
	req.setAsynch( false );			
	req.setCallbackFunction( sendValidateRequest_callback );	
	req.send( XML.serialize( validateXML ) );		
}


//******************************************************
function buildValidateXMLFromPopup()
{	
	var xml = XML.newDocument( "data" );
	XML.addNodeWithValue( "accountNum", xml, _accountNum );
	XML.addNodeWithValue( "respBenefId", xml, _respBenefId );
	XML.addNodeWithValue( "runMode", xml, UTL.getElem( "ActionPopup_RunModeFld" ).value );
	XML.addNodeWithValue( "transType", xml, UTL.getElem( "ActionPopup_TransTypeFld" ).value );
	XML.addNodeWithValue( "transDate", xml, UTL.getElem( "ActionPopup_TransDateFld" ).value );
	XML.addNodeWithValue( "hrdcTransID", xml, UTL.getElem( "ActionPopup_HRDCTransIDFld" ).value );
	XML.addNodeWithValue( "dateSent", xml, UTL.getElem( "ActionPopup_DateSentFld" ).value );
	XML.addNodeWithValue( "amt", xml, UTL.getElem( "ActionPopup_AmtFld" ).value );
	XML.addNodeWithValue( "reported", xml, UTL.getElem( "ActionPopup_ReportedFld" ).value );
	XML.addNodeWithValue( "normalRvrse", xml, UTL.getElem( "ActionPopup_NormalReverseFld" ).value );
	
	return xml;	
}

//******************************************************
function populateActionPopup( runMode )
{
	var row = UTL.getElem( "EntryList_Table" ).lastChild.childNodes[_selectedRowIndex];
	UTL.getElem( "ActionPopup_TransTypeFld" ).value = row.transType;
	UTL.getElem( "ActionPopup_TransDateFld" ).value = row.transDate;
	UTL.getElem( "ActionPopup_HRDCTransIDFld" ).value = row.hrdcTransId;
	UTL.getElem( "ActionPopup_DateSentFld" ).value = row.dateSent;
	UTL.getElem( "ActionPopup_AmtFld" ).value = row.amt;
	UTL.getElem( "ActionPopup_ReportedFld" ).value = row.reported;
	UTL.getElem( "ActionPopup_NormalReverseFld" ).value = row.normalRvrse;
	
	UTL.getElem( "ActionPopup_TransTypeLbl" ).innerHTML = row.transType;
	
	UTL.getElem( "ActionPopup_RunModeFld" ).value = runMode;
	if ( runMode == _CANCEL )
	{
		UTL.getElem( "DeleteConfirm" ).style.display = "none";
		UTL.getElem( "CancelConfirm" ).style.display = "block";
		IFDSDatepickerManager.getDatepicker( "ActionPopup_TransDateFld" ).disable();			
	}
	else if ( runMode == _DELETE )
	{
		UTL.getElem( "DeleteConfirm" ).style.display = "block";
		UTL.getElem( "CancelConfirm" ).style.display = "none";
		IFDSDatepickerManager.getDatepicker( "ActionPopup_TransDateFld" ).disable();	
	}
	else
	{
		UTL.getElem( "DeleteConfirm" ).style.display = "none";
		UTL.getElem( "CancelConfirm" ).style.display = "none";		
		IFDSDatepickerManager.getDatepicker( "ActionPopup_TransDateFld" ).enable();
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
function updateSelectedRow()
{
	var row = UTL.getElem( "EntryList_Table" ).lastChild.childNodes[_selectedRowIndex];
	row.runMode = UTL.getElem( "ActionPopup_RunModeFld" ).value;
	row.transDate = UTL.getElem( "ActionPopup_TransDateFld" ).value;
	row.childNodes[1].innerHTML = row.transDate;
	
	if ( row.runMode == _DELETE )
	{
		row.style.display = "none";
	}	
	else
	{
		row.lastChild.innerHTML = row.runMode; 
	}
		
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
function clickHandler_ActionPopupCancelBtn()
{
	if ( _errorFlagMap["ActionPopup_TransDateFld"] )
	{
		_errorFlagMap["ActionPopup_TransDateFld"].hide();
	}
	Desktop.hidePopup( "ActionPopupDiv" );
}

//******************************************************
function changeHandler_transDateFld()
{
	if (_errorFlagMap["ActionPopup_TransDateFld"]) 
	{
		_errorFlagMap["ActionPopup_TransDateFld"].hide();
	}
}

//******************************************************
function clickHandler_ActionPopupOKBtn()
{
	doEntrySave();
}

//******************************************************
function update()
{
	var updateStatus = null;
	sendUpdateRequest( buildUpdateXML(), update_callback );
		
	function update_callback( success )
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
		
	return updateStatus;
}

//******************************************************
function buildUpdateXML()
{
	var xml = XML.newDocument( "data" );
	
	var rowsArray = UTL.getElem( "EntryList_Table" ).lastChild.childNodes;
	for ( var i = 0 ; i < rowsArray.length; i++ )
	{
		if ( rowsArray[i].runMode && rowsArray[i].runMode != "" )
		{
			var recordXML = XML.addNode( "TermintnUpd", xml );
			XML.addNodeWithValue( "runMode", recordXML, rowsArray[i].runMode );
			XML.addNodeWithValue( "accountNum", recordXML, _accountNum );
			XML.addNodeWithValue( "respBenefId", recordXML, _respBenefId );
			XML.addNodeWithValue( "transType", recordXML, rowsArray[i].transType );
			XML.addNodeWithValue( "transDate", recordXML, rowsArray[i].transDate );
			XML.addNodeWithValue( "hrdcTransId", recordXML, rowsArray[i].hrdcTransId );
			XML.addNodeWithValue( "dateSent", recordXML, rowsArray[i].dateSent );
			XML.addNodeWithValue( "amt", recordXML, rowsArray[i].amt );
			XML.addNodeWithValue( "reported", recordXML, rowsArray[i].reported );
			XML.addNodeWithValue( "normalRvrse", recordXML, rowsArray[i].normalRvrse );			 
			XML.addNodeWithValue( "cesg", recordXML, rowsArray[i].cesg );
			XML.addNodeWithValue( "clb", recordXML, rowsArray[i].clb );
			XML.addNodeWithValue( "pGrant", recordXML, rowsArray[i].pGrant );
		}
	}
	
	return xml;	
}

//******************************************************
function sendUpdateRequest( updateXML, callbackFn )
{
	function sendUpdateRequest_callback( responseText )
	{		
		Desktop.hideProcessingIndicator();
				
		var responseXML = null;
		try 
		{
			responseXML = XML.parseToXML( responseText );
			var success = true;			
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
			alert( "FUNCTION ERROR: sendUpdateRequest error caught: " + e.description ); 		
		}
		
		callbackFn( success );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPAcctTermInfo_Update";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );
	req.setAsynch( false );			
	req.setCallbackFunction( sendUpdateRequest_callback );	
	Desktop.showProcessingIndicator();
	//prompt( "", XML.serialize( updateXML ) )	
	req.send( XML.serialize( updateXML ) );		
}

//******************************************************
function clickHandler_MoreBtn()
{
	reload();
}

//******************************************************
function reload()
{
	sendReloadRequest( reload_callback );
	
	function reload_callback( entryXML )
	{
		if ( entryXML )
		{
			updateEntryTable( entryXML );		
			
			if ( !_moreRecordsExist )
			{
				UTL.getElem( "MoreBtn" ).disabled = true;
			}
		}	
	}
}

//******************************************************
function sendReloadRequest( callbackFn )
{
	function sendReloadRequest_callback( responseText )
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
					dataXML = XML.getNode( "/responseContents/TerminationData", responseXML );
					
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
    paramMap["jobname"]           = "RESPAcctTermInfo_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;    
    
	paramMap["AccountNum"] = _accountNum;
	paramMap["RESPBenefID"] = _respBenefId;	
	
	paramMap["startRecNum"] = _rangeStartForNext;	
	            
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getGETRequest( url );			
	req.setCallbackFunction( sendReloadRequest_callback );	
	Desktop.showProcessingIndicator();
	req.send();		
}

//******************************************************
function updateEntryTable( dataXML )
{
	var table = UTL.getElem( "EntryList_Table" );
	
	var dataRecords = XML.getNodes( "TerminationDetail", dataXML );
	
	for ( var i = 0; i < dataRecords.length; i++ )
	{
		var row = buildEntryRow( dataRecords[i] );
		table.lastChild.appendChild( row ); 
	}
	
	IFDSTableManager.reInitTable( "EntryList_Table" );
}	

//******************************************************
function buildEntryRow( recordXML )
{
	var row = document.createElement( "tr" );	
		
	var transTypeCell = row.appendChild( document.createElement( "td" ) );
	transTypeCell.innerHTML = XML.getNode( "transType", recordXML ).firstChild.nodeValue;
	row.transType = transTypeCell.innerHTML;
	
	var transDateCell = row.appendChild( document.createElement( "td" ) );
	transDateCell.innerHTML = XML.getNode( "transDate", recordXML ).firstChild.nodeValue;
	row.transDate = transDateCell.innerHTML;
	
	var hrdcTransIdCell = row.appendChild( document.createElement( "td" ) );
	hrdcTransIdCell.innerHTML = XML.getNode( "hrdcTransId", recordXML ).firstChild.nodeValue;
	row.hrdcTransId = hrdcTransIdCell.innerHTML;
	
	var dateSentCell = row.appendChild( document.createElement( "td" ) );
	dateSentCell.innerHTML = XML.getNode( "dateSent", recordXML ).firstChild.nodeValue;
	row.dateSent = dateSentCell.innerHTML;
	
	var amtCell = row.appendChild( document.createElement( "td" ) );
	amtCell.innerHTML = XML.getNode( "amt", recordXML ).firstChild.nodeValue;
	row.amt = amtCell.innerHTML;
	
	var reportedCell = row.appendChild( document.createElement( "td" ) );
	reportedCell.innerHTML = XML.getNode( "reported", recordXML ).firstChild.nodeValue;
	row.reported = reportedCell.innerHTML;
	
	row.runMode = "";
	row.cesg = XML.getNode( "cesg", recordXML ).firstChild.nodeValue;
	row.clb = XML.getNode( "clb", recordXML ).firstChild.nodeValue;
	row.pGrant = XML.getNode( "pGrant", recordXML ).firstChild.nodeValue;
	row.normalRvrse = XML.getNode( "normalRvrse", recordXML ).firstChild.nodeValue;
	
	return row;
}	

//******************************************************
function LaunchConfirm()
{
	return _updatesFlag;
}
