var _accountNum = null;
var _respBenefId = null;

var _ACES = "ACES";
var _QESI = "QESI";
var _CLB = "CLB";
var _CESG = "AddCESG";

var _ADD = "add";
var _MOD = "mod";

var _statusMap = null;

var _CESGCurStat = null;
var _CESGVersion = null;

var _CLBCurStat = null;
var _CLBVersion = null;

var _genRT511 = null;

var _updatesFlag = false;

var _errorFlagMap = null;

var _addPerm = null;
var _modPerm = null;

//******************************************************
function loading()
{
	IFDSTableManager.init();
	if ( UTL.getElem( "QESIList_Table" ) )
	{	
		IFDSTableManager.getTable( "QESIList_Table" ).setOnRowSelectedFunction( selectHandler_QESITable );
		if ( !_addPerm )
		{
			disableQESIAddBtn();
		}
	}
	if ( UTL.getElem( "ACESList_Table" ) )
	{
		IFDSTableManager.getTable( "ACESList_Table" ).setOnRowSelectedFunction( selectHandler_ACESTable );
		if ( !_addPerm )
		{
			disableACESAddBtn();		
		}
		
	}
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );
	
	populateStatusListFld( UTL.getElem( "CESGStatusFld" ), 
							( _CESGCurStat == "Not Requested" ? _statusMap[_CESG]["Blank"] : _statusMap[_CESG][_CESGCurStat] ) );
							
	populateStatusListFld( UTL.getElem( "CLBStatusFld" ), 
							( _CLBCurStat == "Not Requested" ? _statusMap[_CLB]["Blank"] : _statusMap[_CLB][_CLBCurStat] ) );
							
	if ( _genRT511 == "no" )
	{
		UTL.getElem( "genRT511Fld" ).value = "no";
		disableGenRT511Fld();
		disableCutOffDateFld();		
	}
	
	_errorFlagMap = {};
}

//******************************************************
function changeHandler_CLBFld()
{
	UTL.getElem( "CLB_runModeFld" ).value = "mod";
	setChangesFlag();
}

//******************************************************
function changeHandler_CESGFld()
{
	UTL.getElem( "CESG_runModeFld" ).value = "mod";
	setChangesFlag();
}

//******************************************************
function changeHandler_CESGStatusFld()
{	
	// if curStat = requested, and user selects requested, don't register the change
	if ( !( UTL.getElem( "CESGStatusFld" ).value == "Requested"
			&& _CESGCurStat == "Requested" ) ) 
	{
		changeHandler_CESGFld();
	}
	
	if ( UTL.getElem( "CESGStatusFld" ).value == "Requested" )
	{
		enableGenRT511Fld();
		enableCutOffDateFld();
	}
	else
	{
		disableGenRT511Fld();
		disableCutOffDateFld();
	}
}

//******************************************************
function enableGenRT511Fld()
{
	UTL.getElem( "genRT511Fld" ).disabled = false;	
}

//******************************************************
function disableGenRT511Fld()
{
	UTL.getElem( "genRT511Fld" ).disabled = true;
	UTL.getElem( "genRT511Fld" ).value = "no";
}

//******************************************************
function enableCutOffDateFld()
{
	IFDSDatepickerManager.getDatepicker( "cutoffDateFld" ).enable();	
}

//******************************************************
function disableCutOffDateFld()
{
	IFDSDatepickerManager.getDatepicker( "cutoffDateFld" ).disable();
	UTL.getElem( "cutoffDateFld" ).value = "";	
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

//****************************************************
function populateStatusListFld( fld, statusList )
{
	clearStatusListFld( fld );
	
	for ( var i in statusList )
	{
		var option = document.createElement( "option" );
		option.value = i;
		option.text = statusList[i];
		
		fld.add( option );
	}
}


//****************************************************
function clearStatusListFld( fld )
{
	while( fld.options.length > 0 )
	{
		fld.remove( 0 );
	}
}

//****************************************************
function clickHandler_addGrantBtn( grantType )
{		
	switch( grantType )
	{
		case _ACES:
		{
			openACESPopup( _ADD );	
			break;
		}
		case _QESI:
		{
			openQESIPopup( _ADD );	
			break;	
		}
		default:
		{
			alert( "FUNCTION ERROR - unknown grant type" );
		}
	}	
}

//****************************************************
function clickHandler_modGrantBtn( grantType )
{		
	switch( grantType )
	{
		case _ACES:
		{
			openACESPopup( _MOD );	
			break;
		}
		case _QESI:
		{
			openQESIPopup( _MOD );	
			break;	
		}
		default:
		{
			alert( "FUNCTION ERROR - unknown grant type" );
		}
	}	
}

//****************************************************
function clickHandler_delGrantBtn( grantType )
{		
	switch( grantType )
	{
		case _ACES:
		{
			var selectedIndex = IFDSTableManager.getTable( "ACESList_Table" ).getSelectedRowIndex();
			var selectedRow = UTL.getElem( "ACESList_Table" ).lastChild.childNodes[selectedIndex];
			selectedRow.parentNode.removeChild( selectedRow );
			IFDSTableManager.reInitTable( "ACESList_Table" );
			disableACESDelBtn();	
			break;
		}
		case _QESI:
		{
			var selectedIndex = IFDSTableManager.getTable( "QESIList_Table" ).getSelectedRowIndex();
			var selectedRow = UTL.getElem( "QESIList_Table" ).lastChild.childNodes[selectedIndex];
			selectedRow.parentNode.removeChild( selectedRow );
			IFDSTableManager.reInitTable( "QESIList_Table" );
			disableQESIDelBtn();			
			break;	
		}
		default:
		{
			alert( "FUNCTION ERROR - unknown grant type" );
		}		
	}	
}

//****************************************************
function clickHandler_grantPopupOKBtn( grantType )
{		
	switch( grantType )
	{
		case _ACES:
		{
			doACESValidate();			
			break;
		}
		case _QESI:
		{
			doQESIValidate();			
			break;	
		}
		default:
		{
			alert( "FUNCTION ERROR - unknown grant type" );
		}
	}	
}

//****************************************************
function clickHandler_grantPopupCancelBtn( grantType )
{		
	switch( grantType )
	{
		case _ACES:
		{
			Desktop.hidePopup( "ACESPopupDiv" );
			break;
		}
		case _QESI:
		{
			Desktop.hidePopup( "QESIPopupDiv" );	
			break;	
		}
		default:
		{
			alert( "FUNCTION ERROR - unknown grant type" );
		}
	}	
}




//******************************************************
function buildRow( stat, year, desc )
{
	var row = document.createElement( "tr" );
	
	row.runMode = "add";
	
	var statCell = row.appendChild( document.createElement( "td" ) );
	statCell.innerHTML = stat;
	row.stat = stat;
	
	var yearCell = row.appendChild( document.createElement( "td" ) );
	yearCell.innerHTML = desc;
	row.year = year;
	
	var createdByCell = row.appendChild( document.createElement( "td" ) );
	
	var procDateCell = row.appendChild( document.createElement( "td" ) );
	
	var modUserCell = row.appendChild( document.createElement( "td" ) );
	
	var modDateCell = row.appendChild( document.createElement( "td" ) );
	
	return row;
}

//******************************************************
function updateRow( row, stat, year, desc )
{
	if ( row.runMode == "" )
	{
		row.runMode = "mod";
	}
	
	row.stat = stat;
	row.childNodes[0].innerHTML = stat;
		
	row.year = year;
	row.childNodes[1].innerHTML = desc;
}

//******************************************************
function buildQESIRow( stat, year, desc, stopReason, stopReasonDesc )
{
	var row = document.createElement( "tr" );
	
	row.runMode = "add";
	
	var statCell = row.appendChild( document.createElement( "td" ) );
	statCell.innerHTML = stat;
	row.stat = stat;
	
	var yearCell = row.appendChild( document.createElement( "td" ) );
	yearCell.innerHTML = desc;
	row.year = year;
	
	var stopReasonCell = row.appendChild( document.createElement( "td" ) );
	stopReasonCell.innerHTML = stopReasonDesc;
	row.stopReason = stopReason;
	
	var createdByCell = row.appendChild( document.createElement( "td" ) );
	
	var procDateCell = row.appendChild( document.createElement( "td" ) );
	
	var modUserCell = row.appendChild( document.createElement( "td" ) );
	
	var modDateCell = row.appendChild( document.createElement( "td" ) );
	
	return row;
}

//******************************************************
function updateQESIRow( row, stat, year, desc, stopReason, stopReasonDesc )
{
	if ( row.runMode == "" )
	{
		row.runMode = "mod";
	}
	
	row.stat = stat;
	row.childNodes[0].innerHTML = stat;
		
	row.year = year;
	row.childNodes[1].innerHTML = desc;
	
	row.stopReason = stopReason;
	row.childNodes[2].innerHTML = stopReasonDesc;
}


//******************************************************
function sendValidateRequest( updateXML, callbackFn )
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
			alert( "FUNCTION ERROR: sendSaveRequest error caught: " + e.description ); 		
		}
		
		callbackFn( isValid );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPGrantInfo_Validate";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );			
	req.setCallbackFunction( sendValidateRequest_callback );	

	//prompt( "", XML.serialize( updateXML ) );
	req.send( XML.serialize( updateXML ) );		
}
 
//****************************************************
function isDuplicateGrant( grantType, year )
{
	var isDuplicate = false;
	
	var grantTable = UTL.getElem( grantType + "List_Table" );
	var grantRows = grantTable.lastChild.childNodes;
	for ( var i = 0; i < grantRows.length; i++ )
	{
		var row = grantRows[i];
		if ( row.runMode == "add" && row.year == year )
		{
			isDuplicate = true;
			break;
		}
	}
	
	return isDuplicate;
}

// ACES
//****************************************************
function selectHandler_ACESTable()
{
	var selectedIndex = IFDSTableManager.getTable( "ACESList_Table" ).getSelectedRowIndex();
	var selectedRow = UTL.getElem( "ACESList_Table" ).lastChild.childNodes[selectedIndex];
	if ( selectedRow.runMode == _ADD )
	{
		enableACESDelBtn();
		disableACESModBtn();
	}
	else if( !_modPerm )
	{
		disableACESDelBtn();
		disableACESModBtn();
	}
	else
	{
		disableACESDelBtn();
		if ( selectedRow.allowUpd == 'yes' )
		{
			enableACESModBtn();
		}
		else if ( selectedRow.allowUpd == 'no' )
		{
			disableACESModBtn();
		}
	}
}

//****************************************************
function enableACESAddBtn()
{
	UTL.getElem( "ACESAddBtn" ).disabled = false;
}

//****************************************************
function disableACESAddBtn()
{
	UTL.getElem( "ACESAddBtn" ).disabled = true;
}

//****************************************************
function enableACESDelBtn()
{
	UTL.getElem( "ACESDelBtn" ).disabled = false;
}

//****************************************************
function disableACESDelBtn()
{
	UTL.getElem( "ACESDelBtn" ).disabled = true;
}

//****************************************************
function enableACESModBtn()
{
	UTL.getElem( "ACESModBtn" ).disabled = false;
}

//****************************************************
function disableACESModBtn()
{
	UTL.getElem( "ACESModBtn" ).disabled = true;
}

//******************************************************
function openACESPopup( mode )
{	
	var caption = "Grant Type:ACES";
	UTL.getElem( "ACESPopup_modeFld" ).value = mode;
	switch ( mode )
	{
		case _ADD:
		{
			IFDSTableManager.getTable( "ACESList_Table" ).clearSelectedRowIndex();
			disableACESModBtn();
			disableACESDelBtn();
			populateACESPopup();
			UTL.getElem( "ACESPopup_yearFld" ).disabled = false;
			caption += " - Add";
			break;
		}
		case _MOD:
		{
			populateACESPopup( IFDSTableManager.getTable( "ACESList_Table" ).getSelectedRowIndex() );
			UTL.getElem( "ACESPopup_yearFld" ).disabled = true;
			caption += " - Modify";			
			break;
		}	
		default:
		{
			alert( "FUNCTION ERROR - unknown popup mode" );
		}
	}
	
	Desktop.showPopup( "ACESPopupDiv", caption );	
}

//******************************************************
function populateACESPopup( selectedRowIndex )
{
	if ( selectedRowIndex != null )
	{		
		var row = UTL.getElem( "ACESList_Table" ).lastChild.childNodes[selectedRowIndex];
		
		UTL.getElem( "ACESPopup_yearFld" ).value = row.year;
		UTL.getElem( "ACESPopup_grantInfoIdFld" ).value = row.grantInfoId;
		UTL.getElem( "ACESPopup_versionFld" ).value = row.version;		
		populateStatusListFld( UTL.getElem( "ACESPopup_statusFld" ), _statusMap[_ACES][row.stat] );		
	}
	else
	{
		UTL.getElem( "ACESPopup_yearFld" ).value = "";
		UTL.getElem( "ACESPopup_grantInfoIdFld" ).value = "";
		UTL.getElem( "ACESPopup_versionFld" ).value = "";
		populateStatusListFld( UTL.getElem( "ACESPopup_statusFld" ), _statusMap[_ACES]["Blank"] );
	}
}

//******************************************************
function doACESValidate()
{	
	var mode = UTL.getElem( "ACESPopup_modeFld" ).value;
	
	if ( UTL.getElem( "ACESPopup_yearFld" ).value == "" )
	{		
		Desktop.paintFieldErrorFlag( _errorFlagMap, "ACESPopup_yearFld", "Mandatory field" );
		return;
	}
	
	var fldMap = {};
	fldMap["grantType"] = _ACES;
	fldMap["stat"] = UTL.getElem( "ACESPopup_statusFld" ).value;
	var grantOptFld = UTL.getElem( "ACESPopup_yearFld" );
	fldMap["grantOpt"] = grantOptFld.value;
	fldMap["grantOptDesc"] = grantOptFld.options[grantOptFld.selectedIndex].text;
	fldMap["grantInfoID"] = UTL.getElem( "ACESPopup_grantInfoIdFld" ).value;
		
	var validateXML = buildGrantXML( XML.newDocument( "data" ), mode, fldMap ); 	
	sendValidateRequest(validateXML, doACESValidate_callback );
		
	function doACESValidate_callback( isValid )
	{
		if ( isValid )
		{			
			if ( mode == _ADD && isDuplicateGrant( _ACES, fldMap["grantOpt"] ) )
			{
				alert( "Cannot add duplicate Grant Option." );
			}
			else
			{				
				if ( mode == _ADD )
				{							
					var newRow = buildRow( fldMap["stat"], fldMap["grantOpt"], fldMap["grantOptDesc"] );
					UTL.getElem( "ACESList_Table" ).lastChild.appendChild( newRow );
					IFDSTableManager.reInitTable( "ACESList_Table" );			
				}
				else
				{			
					var selectedRowIndex = IFDSTableManager.getTable( "ACESList_Table" ).getSelectedRowIndex();
					var row = UTL.getElem( "ACESList_Table" ).lastChild.childNodes[selectedRowIndex];									
					updateRow( row, fldMap["stat"], fldMap["grantOpt"], fldMap["grantOptDesc"] );				
				}				
				Desktop.hidePopup( "ACESPopupDiv" );
				setChangesFlag();
			}
		}
	}
}


// QESI
//****************************************************
function selectHandler_QESITable()
{
	var selectedIndex = IFDSTableManager.getTable( "QESIList_Table" ).getSelectedRowIndex();
	var selectedRow = UTL.getElem( "QESIList_Table" ).lastChild.childNodes[selectedIndex];
	if ( selectedRow.runMode == _ADD )
	{
		enableQESIDelBtn();
	}
	else if ( !_modPerm )
	{
		disableQESIDelBtn();
		disableQESIModBtn();
	}
	else
	{
		disableQESIDelBtn();
		if ( selectedRow.allowUpd == 'yes' )
		{
			enableQESIModBtn();
		}
		else if ( selectedRow.allowUpd == 'no' )
		{
			disableQESIModBtn();
		}
	}
}

//****************************************************
function enableQESIAddBtn()
{
	UTL.getElem( "QESIAddBtn" ).disabled = false;
}

//****************************************************
function disableQESIAddBtn()
{
	UTL.getElem( "QESIAddBtn" ).disabled = true;
}

//****************************************************
function enableQESIDelBtn()
{
	UTL.getElem( "QESIDelBtn" ).disabled = false;
}

//****************************************************
function disableQESIDelBtn()
{
	UTL.getElem( "QESIDelBtn" ).disabled = true;
}

//****************************************************
function enableQESIModBtn()
{
	UTL.getElem( "QESIModBtn" ).disabled = false;
}

//****************************************************
function disableQESIModBtn()
{
	UTL.getElem( "QESIModBtn" ).disabled = true;
}

//******************************************************
function openQESIPopup( mode )
{	
	var caption = "Grant Type:QESI";
	UTL.getElem( "QESIPopup_modeFld" ).value = mode;
	switch ( mode )
	{
		case _ADD:
		{			
			IFDSTableManager.getTable( "QESIList_Table" ).clearSelectedRowIndex();
			disableQESIModBtn();
			disableQESIDelBtn();
			populateQESIPopup();			
			UTL.getElem( "QESIPopup_yearFld" ).style.display = "inline";			
			UTL.getElem( "QESIPopup_yearStaticFld" ).style.display = "none";			
			caption += " - Add";
			break;
		}
		case _MOD:
		{		
			populateQESIPopup( IFDSTableManager.getTable( "QESIList_Table" ).getSelectedRowIndex() );
			UTL.getElem( "QESIPopup_yearFld" ).style.display = "none";			
			UTL.getElem( "QESIPopup_yearStaticFld" ).style.display = "inline";			
			caption += " - Modify";			
			break;
		}	
		default:
		{
			alert( "FUNCTION ERROR - unknown popup mode" );
		}
	}
	
	if (UTL.getElem('QESIPopup_statusFld').value == 'Stopped')
	{
		UTL.getElem('QESIPopup_stopReasonFld').disabled = false;		
	}
	else
	{
		UTL.getElem('QESIPopup_stopReasonFld').disabled = true;
	}
	
	Desktop.showPopup( "QESIPopupDiv", caption );	
}


//******************************************************
function populateQESIPopup( selectedRowIndex )
{
	if ( selectedRowIndex != null )
	{		
		var row = UTL.getElem( "QESIList_Table" ).lastChild.childNodes[selectedRowIndex];
		
		UTL.getElem( "QESIPopup_grantInfoIdFld" ).value = row.grantInfoId;
		UTL.getElem( "QESIPopup_yearFld" ).value = row.year;
		UTL.getElem( "QESIPopup_yearStaticFld" ).value = row.year;
		UTL.getElem( "QESIPopup_stopReasonFld" ).value = row.stopReason;
		UTL.getElem( "QESIPopup_versionFld" ).value = row.version;		
		populateStatusListFld( UTL.getElem( "QESIPopup_statusFld" ), _statusMap[_QESI][row.stat] );
		UTL.getElem( "QESIPopup_statusFld" ).value = row.stat;
	}
	else
	{
		UTL.getElem( "QESIPopup_stopReasonFld" ).value = "";
		UTL.getElem( "QESIPopup_yearFld" ).value = "";
		populateStatusListFld( UTL.getElem( "QESIPopup_statusFld" ), _statusMap[_QESI]["Blank"] );
	}
}

//******************************************************
function doQESIValidate()
{	
	var mode = UTL.getElem( "QESIPopup_modeFld" ).value;
	
	if ( mode == _ADD && UTL.getElem( "QESIPopup_yearFld" ).value == "" )
	{		
		Desktop.paintFieldErrorFlag( _errorFlagMap, "QESIPopup_yearFld", "Mandatory field" );
		return;
	}
	
	var fldMap = {};
	fldMap["grantType"] = _QESI;
	fldMap["grantInfoID"] = UTL.getElem( "QESIPopup_grantInfoIdFld" ).value;
	fldMap["newStat"] = UTL.getElem( "QESIPopup_statusFld" ).value;
	var grantYrFld = ( mode == _ADD ? UTL.getElem( "QESIPopup_yearFld" ) : UTL.getElem( "QESIPopup_yearStaticFld" ) ); 
	fldMap["grantYr"] = grantYrFld.value;
	fldMap["grantYrDesc"] = grantYrFld.value;
	var stopReasonFld = UTL.getElem( "QESIPopup_stopReasonFld" );
	fldMap["stopReason"] = stopReasonFld.value;
	fldMap["stopReasonDesc"] = (stopReasonFld.value != "" ? stopReasonFld.options[stopReasonFld.selectedIndex].text : "");
	
	var validateXML = buildGrantXML( XML.newDocument( "data"), mode, fldMap );	
	sendValidateRequest( validateXML, saveQESIValidate_callback );
		
	function saveQESIValidate_callback( isValid )
	{
		if ( isValid )
		{
			if ( mode == _ADD && isDuplicateGrant( _QESI, fldMap["grantYr"] ) )
			{
				alert( "Cannot add duplicate grant." );
			}
			else
			{
				if ( mode == _ADD )
				{
					var newRow = buildQESIRow( fldMap["newStat"], fldMap['grantYr'], fldMap["grantYrDesc"], fldMap["stopReason"], fldMap["stopReasonDesc"] );
					UTL.getElem( "QESIList_Table" ).lastChild.appendChild( newRow );
					IFDSTableManager.reInitTable( "QESIList_Table" );
				}
				else
				{
					var selectedRowIndex = IFDSTableManager.getTable( "QESIList_Table" ).getSelectedRowIndex();
					var row = UTL.getElem( "QESIList_Table" ).lastChild.childNodes[selectedRowIndex];
					updateQESIRow( row, fldMap["newStat"], fldMap["grantYr"], fldMap["grantYrDesc"], fldMap["stopReason"], fldMap["stopReasonDesc"] );				
				}
				Desktop.hidePopup( "QESIPopupDiv" );
				setChangesFlag();
			}
		}
	}
}

//******************************************************
function buildGrantXML( xmlContext, mode, fldMap )
{	
	XML.addNodeWithValue( "runMode", xmlContext, mode );
	XML.addNodeWithValue( "accountNum", xmlContext, _accountNum );
	XML.addNodeWithValue( "respBenefID", xmlContext, _respBenefId );
	for ( var i in fldMap )
	{
		XML.addNodeWithValue( i, xmlContext, fldMap[i] );
	}
	return xmlContext;	
}


//******************************************************
function update()
{
	var updateStatus = null;
	sendGrantUpdateRequest( buildGrantUpdateXML(), doGrantUpdate_callback );
		
	function doGrantUpdate_callback( success )
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
function buildGrantUpdateXML()
{
	var updateXML = XML.newDocument( "data" );
	
	if ( UTL.getElem( "CESG_runModeFld" ).value == _MOD )
	{
		// CESG
		var CESGXMLNode = XML.addNode( "RESPGrantUpd", updateXML );
		var fldMap = {};
		fldMap["grantType"] = _CESG;
		fldMap["newStat"] = UTL.getElem( "CESGStatusFld" ).value;
		fldMap["genRT511"] = UTL.getElem( "genRT511Fld" ).value;
		fldMap["cutOffDt"] = UTL.getElem( "cutoffDateFld" ).value;
		fldMap["version"] = _CESGVersion;		
		buildGrantXML( CESGXMLNode, _MOD, fldMap );
	}
			
	if ( UTL.getElem( "CLB_runModeFld" ).value == _MOD )
	{
		// CLB
		var CLBXMLNode = XML.addNode( "RESPGrantUpd", updateXML );
		var fldMap = {};
		fldMap["grantType"] = _CLB;
		fldMap["newStat"] = UTL.getElem( "CLBStatusFld" ).value;
		fldMap["version"] = _CLBVersion;
		buildGrantXML( CLBXMLNode, _MOD, fldMap );
	}
	
	if ( UTL.getElem( "ACESList_Table" ) )
	{	
		// ACES
		var ACESCount = UTL.getElem( "ACESList_Table" ).lastChild.childNodes.length;
		for ( var i = 0; i < ACESCount; i++ )
		{
			var ACESrow = UTL.getElem( "ACESList_Table" ).lastChild.childNodes[i];
			if( ACESrow.runMode != "" )
			{		
				var ACESXMLNode = XML.addNode( "RESPGrantUpd", updateXML );
				var fldMap = {};
				fldMap["grantType"] = _ACES;
				fldMap["grantInfoID"] = ACESrow.grantInfoId;
				fldMap["newStat"] = ACESrow.stat				
				fldMap["grantOpt"] = ACESrow.year;			
				fldMap["version"] = ACESrow.version
				buildGrantXML( ACESXMLNode, ACESrow.runMode, fldMap );
			}
		}
	}
	
	if ( UTL.getElem( "QESIList_Table" ) )
	{
		// QESI
		var QESICount = UTL.getElem( "QESIList_Table" ).lastChild.childNodes.length;
		for ( var i = 0; i < QESICount; i++ )
		{
			var QESIrow = UTL.getElem( "QESIList_Table" ).lastChild.childNodes[i];
			if( QESIrow.runMode != "" )
			{		
				var QESIXMLNode = XML.addNode( "RESPGrantUpd", updateXML );
				var fldMap = {};
				fldMap["grantType"] = _QESI;
				fldMap["grantInfoID"] = QESIrow.grantInfoId;
				fldMap["newStat"] = QESIrow.stat;
				fldMap["grantYr"] = QESIrow.year;
				fldMap["version"] = QESIrow.version;
				fldMap["stopReason"] = QESIrow.stopReason;
				buildGrantXML( QESIXMLNode, QESIrow.runMode, fldMap );
			}
		}
	}
	
	//prompt( "", XML.serialize( updateXML ) );
	return updateXML;	
}

//******************************************************
function sendGrantUpdateRequest( updateXML, callbackFn )
{	
	function sendGrantUpdateRequest_callback( responseText )
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
			alert( "FUNCTION ERROR: sendSaveRequest error caught: " + e.description ); 		
		}
		
		callbackFn( success );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RESPGrantInfo_Update";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );
	req.setAsynch( false );			
	req.setCallbackFunction( sendGrantUpdateRequest_callback );	
	Desktop.showProcessingIndicator();
	//prompt( "", XML.serialize( updateXML ) );
	req.send( XML.serialize( updateXML ) );		
}

//******************************************************
function setChangesFlag()
{
	_updatesFlag = true;
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
function LaunchConfirm()
{
	return _updatesFlag;
}

//******************************************************
function clickHandler_okBtn()
{	
	if ( !IFDSDatepicker.isValidDateValue( UTL.getElem( "cutoffDateFld" ).value, _dateFormat ) )
	{
		Desktop.paintFieldErrorFlag( _errorFlagMap, "cutoffDateFld", "Invalid value" );		
		return
	}
	
	UTL.getElem( "btnOK" ).click();
}

//******************************************************
function changeHandler_cutoffDateFld()
{
	if( _errorFlagMap['cutoffDateFld'] )
	{
		_errorFlagMap['cutoffDateFld'].hide();
	}
}

//******************************************************
function changeHandler_QESIStatusFld()
{	
	if(UTL.getElem('QESIPopup_statusFld').value == 'Stopped')
	{
		UTL.getElem('QESIPopup_stopReasonFld').disabled = false;
	}
	else
	{
		UTL.getElem('QESIPopup_stopReasonFld').value = "";
		UTL.getElem('QESIPopup_stopReasonFld').disabled = true;	
	}
}	

		