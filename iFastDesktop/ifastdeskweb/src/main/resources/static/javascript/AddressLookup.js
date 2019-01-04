var _searchBtn = null;
var _postalCodeFld = null;
var _addressDisplayFlag = null;

var _selectedAddressType = null
var _selectedAddressRow = null;

var _addressListMap = null;
var _addressEntryFieldMap = null;
var _oddEvenMap = null;

//******************************************************
function loading()
{	
	_searchBtn = UTL.getElem( "searchBtn" );
	_postalCodeFld = UTL.getElem( "postalCodeLookupFld" );
	
	initAddressEntryFieldMap();
	disableAllAddressEntryFields();	
	
	initAddressListMap();			
	initAddressListTables();
	
	initOddEvenMap();
	hideOddEvenWarning();
	
	if ( _postalCodeFld.value != "" )
	{
		enableSearchBtn();
		doAddressLookup();	
	}
	else
	{
		disableSearchBtn();
	}	
}

//******************************************************
function initAddressListMap()
{
	_addressListMap = {};
	
	_addressListMap[_CIVIC] = {};	
	_addressListMap[_CIVIC]["selectHandler"] = selectHandler_CivicAddressTable;
	_addressListMap[_CIVIC]["applicableFlds"] = [_STREET_NUM, _SUFFIX, _UNIT_NUM, _UNIT_DESC];
	
	_addressListMap[_PO_BOX] = {};	
	_addressListMap[_PO_BOX]["selectHandler"] = selectHandler_POBoxAddressTable;
	_addressListMap[_PO_BOX]["applicableFlds"] = [_PO_BOX_NUM];
	
	_addressListMap[_GENERAL] = {};	
	_addressListMap[_GENERAL]["selectHandler"] = selectHandler_GeneralAddressTable;
	_addressListMap[_GENERAL]["applicableFlds"] = [];
	
	_addressListMap[_RURAL_ROUTE] = {};	
	_addressListMap[_RURAL_ROUTE]["selectHandler"] = selectHandler_RuralRouteAddressTable;
	_addressListMap[_RURAL_ROUTE]["applicableFlds"] = [];
	
	_addressListMap[_ST_ROUTE] = {};	
	_addressListMap[_ST_ROUTE]["selectHandler"] = selectHandler_StRouteAddressTable;
	_addressListMap[_ST_ROUTE]["applicableFlds"] = [_STREET_NUM, _SUFFIX];
}

//******************************************************
function initAddressEntryFieldMap()
{
	_addressEntryFieldMap = {};
	//streetNum
	_addressEntryFieldMap[_STREET_NUM] 					= {};
	_addressEntryFieldMap[_STREET_NUM]["lbl"] 			= UTL.getElem( _STREET_NUM + "Lbl" );
	_addressEntryFieldMap[_STREET_NUM]["fld"] 			= UTL.getElem( _STREET_NUM + "Fld" );	
	_addressEntryFieldMap[_STREET_NUM]["flag"] 			= null;
	_addressEntryFieldMap[_STREET_NUM]["validateFn"] 	= validateStreetNumFld;
	EvtHandler.add( _addressEntryFieldMap[_STREET_NUM]["fld"], "change", changeHandler_streetNumFld );
	//suffix
	_addressEntryFieldMap[_SUFFIX] 						= {};
	_addressEntryFieldMap[_SUFFIX]["lbl"] 				= UTL.getElem( _SUFFIX + "Lbl" );
	_addressEntryFieldMap[_SUFFIX]["fld"] 				= UTL.getElem( _SUFFIX + "Fld" );	
	_addressEntryFieldMap[_SUFFIX]["flag"] 				= null;
	_addressEntryFieldMap[_SUFFIX]["validateFn"] 		= null;
	EvtHandler.add( _addressEntryFieldMap[_SUFFIX]["fld"], "change", changeHandler_suffixFld );
	//unitNum	
	_addressEntryFieldMap[_UNIT_NUM] 					= {};
	_addressEntryFieldMap[_UNIT_NUM]["lbl"] 			= UTL.getElem( _UNIT_NUM + "Lbl" );
	_addressEntryFieldMap[_UNIT_NUM]["fld"] 			= UTL.getElem( _UNIT_NUM + "Fld" );	
	_addressEntryFieldMap[_UNIT_NUM]["flag"]			= null;
	_addressEntryFieldMap[_UNIT_NUM]["validateFn"] 		= validateUnitNumFld;
	EvtHandler.add( _addressEntryFieldMap[_UNIT_NUM]["fld"], "change", changeHandler_unitNumFld );
	//unit desc	
	_addressEntryFieldMap[_UNIT_DESC] 					= {};
	_addressEntryFieldMap[_UNIT_DESC]["lbl"] 			= UTL.getElem( _UNIT_DESC + "Lbl" );
	_addressEntryFieldMap[_UNIT_DESC]["fld"] 			= UTL.getElem( _UNIT_DESC + "Fld" );	
	_addressEntryFieldMap[_UNIT_DESC]["flag"]			= null;
	_addressEntryFieldMap[_UNIT_DESC]["validateFn"] 	= null;
	EvtHandler.add( _addressEntryFieldMap[_UNIT_DESC]["fld"], "change", changeHandler_unitDescFld );
	//po box
	_addressEntryFieldMap[_PO_BOX_NUM] 					= {};
	_addressEntryFieldMap[_PO_BOX_NUM]["lbl"] 			= UTL.getElem( _PO_BOX_NUM + "Lbl" );
	_addressEntryFieldMap[_PO_BOX_NUM]["fld"] 			= UTL.getElem( _PO_BOX_NUM + "Fld" );		
	_addressEntryFieldMap[_PO_BOX_NUM]["flag"] 			= null;
	_addressEntryFieldMap[_PO_BOX_NUM]["validateFn"] 	= validatePOBoxFld;
	EvtHandler.add( _addressEntryFieldMap[_PO_BOX_NUM]["fld"], "change", changeHandler_poBoxFld );	
}

//******************************************************
function initAddressListTables()
{
	for ( var addressType in _addressListMap )
	{
		var table = UTL.getElem( addressType + "_AddressList_Table" );		
		if ( table != null )
		{
			IFDSTableManager.addTable( addressType + "_AddressList_Table" );
			IFDSTableManager.getTable( addressType + "_AddressList_Table" ).setOnRowSelectedFunction( _addressListMap[addressType]["selectHandler"] );			 		
		}
	}
}

//******************************************************
function initOddEvenMap()
{
		_oddEvenMap = {};
		_oddEvenMap["odd"] = {};
		_oddEvenMap["odd"]["lbl"] = UTL.getElem( "oddOnlyLabel" );
		_oddEvenMap["odd"]["flag"] = UTL.getElem( "oddOnlyFlag" );
		
		_oddEvenMap["even"] = {};
		_oddEvenMap["even"]["lbl"] = UTL.getElem( "evenOnlyLabel" );
		_oddEvenMap["even"]["flag"] = UTL.getElem( "evenOnlyFlag" );
}

//******************************************************
function hideOddEvenWarning()
{
	_oddEvenMap["odd"]["lbl"].style.display = "none";
	_oddEvenMap["odd"]["flag"].style.display = "none";
	
	_oddEvenMap["even"]["lbl"].style.display = "none";
	_oddEvenMap["even"]["flag"].style.display = "none";
}

//******************************************************
function showOddEvenWarning( type )
{	
	hideOddEvenWarning();
	
	if ( type != null )
	{
		_oddEvenMap[type]["lbl"].style.display = "block";
		_oddEvenMap[type]["flag"].style.display = "block";
	}
}

//******************************************************
function showProcessingIndicator()
{
	disableScreen();
	UTL.getElem( "DesktopScreenProcessingIndicatorDiv" ).style.visibility = "visible";	
}

//******************************************************
function hideProcessingIndicator()
{	
	UTL.getElem( "DesktopScreenProcessingIndicatorDiv" ).style.visibility = "hidden"
	undisableScreen();
}

//******************************************************
function disableScreen()
{
	document.body.className = "Desktop_DisabledBackground";
	UTL.getElem( "DesktopScreenDisablerDiv" ).style.visibility = "visible"; 
}

//******************************************************
function undisableScreen()
{
	document.body.className = "Desktop_Background";
	UTL.getElem( "DesktopScreenDisablerDiv" ).style.visibility = "hidden"; 
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
		DesktopError.displayProcessingError( "Address Lookup", errorMsg );  
	}
	else
	{
		alert( errorMsg );
	}
}

//******************************************************
function disableSearchBtn()
{
	_searchBtn.disabled = true;
}

//******************************************************
function enableSearchBtn()
{
	_searchBtn.disabled = false;
}

//******************************************************
function enableAddressEntryField( fldName )
{
	_addressEntryFieldMap[fldName]["lbl"].style.color = "black";
	_addressEntryFieldMap[fldName]["fld"].disabled = false; 
}

//******************************************************
function disableAddressEntryField( fldName )
{
	_addressEntryFieldMap[fldName]["lbl"].style.color = "gray";
	_addressEntryFieldMap[fldName]["fld"].disabled = true; 
}

//******************************************************
function clearAddressEntryField( fldName )
{
	_addressEntryFieldMap[fldName]["fld"].value = "";	
	if ( _addressEntryFieldMap[fldName]["flag"] )
	{
		_addressEntryFieldMap[fldName]["flag"].hide();		
	}
}

//******************************************************
function disableAllAddressEntryFields()
{
	for ( var fldName in _addressEntryFieldMap )
	{
		disableAddressEntryField( fldName );
	}	
}

//******************************************************
function clearAllAddressEntryFields()
{
	for ( var fldName in _addressEntryFieldMap )
	{	
		clearAddressEntryField( fldName );		
	}		
}

//******************************************************
function clickHandler_searchBtn()
{
	doAddressLookup();	
}

//******************************************************
function keydownHandler_postalCodeFld()
{
	if ( KeyMap.getKeyDesc( window.event.keyCode, KeyMap.KEYUP ) == KeyMap.ENTER
			&& _postalCodeFld.value != "" )	 
	{
		doAddressLookup();
	}
}

//******************************************************
function keyupHandler_postalCodeFld()
{
	if ( _postalCodeFld.value != "" )
	{
		enableSearchBtn();
	}
	else
	{
		disableSearchBtn();
	}
}

//******************************************************
function clickHandler_postalCodeFld()
{
	if ( _postalCodeFld.value != "" )
	{
		enableSearchBtn();
	}
	else
	{
		disableSearchBtn();
	}
}

//******************************************************
function selectHandler_StRouteAddressTable( rowIndex )
{		
	setSelectedAddressRecord( _ST_ROUTE, rowIndex );	
}

//******************************************************
function selectHandler_CivicAddressTable( rowIndex )
{
	setSelectedAddressRecord( _CIVIC, rowIndex );
}

//******************************************************
function selectHandler_RuralRouteAddressTable( rowIndex )
{	
	setSelectedAddressRecord( _RURAL_ROUTE, rowIndex );
}

//******************************************************
function selectHandler_GeneralAddressTable( rowIndex )
{
	setSelectedAddressRecord( _GENERAL, rowIndex );
}

//******************************************************
function selectHandler_POBoxAddressTable( rowIndex )
{	
	setSelectedAddressRecord( _PO_BOX, rowIndex );
}

//******************************************************
function changeHandler_streetNumFld()
{	
	if ( validateStreetNumFld() )
	{
		updateAddressDisplay( _selectedAddressType, _selectedAddressRow );		
	}		
}

//******************************************************
function changeHandler_suffixFld()
{	
	updateAddressDisplay( _selectedAddressType, _selectedAddressRow );	
}

//******************************************************
function changeHandler_unitNumFld()
{	
	if ( validateUnitNumFld() )
	{
		updateAddressDisplay( _selectedAddressType, _selectedAddressRow );
	}
}

//******************************************************
function changeHandler_unitDescFld()
{		
	updateAddressDisplay( _selectedAddressType, _selectedAddressRow );		
}

//******************************************************
function changeHandler_poBoxFld()
{		
	if ( validatePOBoxFld() )	
	{
		updateAddressDisplay( _selectedAddressType, _selectedAddressRow );
	}
}

//******************************************************
function clickHandler_okBtn()
{	
	if ( validateAddress() )
	{				
		UTL.getElem( "btnOK" ).click();
	}
}

//******************************************************
function clickHandler_cancelBtn()
{	
	UTL.getElem( "btnCancel" ).click();
}

//******************************************************
function validateStreetNumFld()
{
	var streetNumStr = _addressEntryFieldMap[_STREET_NUM]["fld"].value;	
	var errorMsg = null;
	
	if ( UTL.trimString( streetNumStr ) == "" )
	{
		errorMsg = "Street number cannot be blank";
	}
	else 	
	{
		if ( isNaN( streetNumStr ) )
		{
			errorMsg = "Street number value is not a number";
		}		
		else
		{
			var streetNum = parseInt( streetNumStr );
			var lowerLimit = parseInt( _selectedAddressRow.stFrom );
			var upperLimit = parseInt( _selectedAddressRow.stTo );
			
			if ( streetNum < lowerLimit || streetNum > upperLimit )
			{
				errorMsg = "Street number value is not within range";
			}
			else if ( _selectedAddressRow.oddeven )
			{
				if ( _selectedAddressRow.oddeven.toLowerCase() == "odd" && streetNum % 2 == 0 )
				{
					errorMsg = "Street number value must be odd";
				}
				else if ( _selectedAddressRow.oddeven.toLowerCase() == "even" && streetNum % 2 == 1 )
				{
					errorMsg = "Street number value must be even";
				}
			}						
		}
	}
	
	if ( errorMsg != null )
	{
		if ( _addressEntryFieldMap[_STREET_NUM]["flag"] != null )
		{
			_addressEntryFieldMap[_STREET_NUM]["flag"].hide();	
		}
		_addressEntryFieldMap[_STREET_NUM]["flag"] = paintAddressEntryFieldErrorFlag( _STREET_NUM, errorMsg )
	}	
	
	return ( errorMsg == null );
}

//******************************************************
function validateUnitNumFld()
{
	var unitNumStr = UTL.trimString( _addressEntryFieldMap[_UNIT_NUM]["fld"].value );	
	var errorMsg = null;
	if ( unitNumStr == "" && _selectedAddressRow.unitFrom != "")
	{
		errorMsg = "Unit number cannot be blank";
	}	
	
	if ( errorMsg != null )
	{
		if ( _addressEntryFieldMap[_UNIT_NUM]["flag"] != null )
		{
			_addressEntryFieldMap[_UNIT_NUM]["flag"].hide();	
		}
		_addressEntryFieldMap[_UNIT_NUM]["flag"] = paintAddressEntryFieldErrorFlag( _UNIT_NUM, errorMsg )
	}	
	
	return ( errorMsg == null );
}

//******************************************************
function validatePOBoxFld()
{
	var poBoxNumStr = _addressEntryFieldMap[_PO_BOX_NUM]["fld"].value;	
	var errorMsg = null;
	if ( UTL.trimString( poBoxNumStr ) == "" )
	{
		errorMsg = "PO Box cannot be blank";
	}
	else 	
	{
		if ( isNaN( poBoxNumStr ) )
		{
			errorMsg = "PO Box value is not a number";
		}		
		else
		{
			var poBoxNum = parseInt( poBoxNumStr );
			var lowerLimit = parseInt( _selectedAddressRow.pobFrom );
			var upperLimit = parseInt( _selectedAddressRow.pobTo );
			
			if ( poBoxNum < lowerLimit || poBoxNum > upperLimit )
			{
				errorMsg = "PO Box value is not within range";
			}						
		}
	}	
	
	if ( errorMsg != null )
	{
		if ( _addressEntryFieldMap[_PO_BOX_NUM]["flag"] != null )
		{
			_addressEntryFieldMap[_PO_BOX_NUM]["flag"].hide();	
		}
		_addressEntryFieldMap[_PO_BOX_NUM]["flag"] = paintAddressEntryFieldErrorFlag( _PO_BOX_NUM, errorMsg )
	}	
	
	return ( errorMsg == null );
}

//******************************************************
function validateAddress()
{
	var noErrors = true;
	if ( _selectedAddressType )
	{
		var applicableFieldsArray = _addressListMap[_selectedAddressType]["applicableFlds"];
		for ( var i = 0; i < applicableFieldsArray.length; i++ )
		{
			var fldName = applicableFieldsArray[i];
			validationFn = _addressEntryFieldMap[fldName]["validateFn"];
			if ( validationFn )
			{
				noErrors = noErrors && validationFn();
			}
		}		
	}
	else
	{
		_addressDisplayFlag = paintAddressDisplayErrorFlag( "No address details provided" );
		noErrors = false;
	}
	
	return noErrors;
}

//******************************************************
function initAddressDisplay( addressType, addressRow )
{	
	if ( _addressDisplayFlag != null )
	{
		_addressDisplayFlag.hide();
	}
	
	switch( addressType )
	{
		case _PO_BOX:
		{
			setAddressLineOneDisplay( buildAddressLine( ["PO Box", "", addressRow.delArea, addressRow.routeInfo] ) );					 
			break;			
		}
		case _RURAL_ROUTE:
		{	
			setAddressLineOneDisplay( buildAddressLine( [addressRow.delArea, addressRow.routeInfo] ) );
			break;			
		}
		case _GENERAL:
		{
			setAddressLineOneDisplay( buildAddressLine( [addressRow.delArea, addressRow.delInstall] ) );		
			break;			
		}
		case _CIVIC:
		{
			setAddressLineOneDisplay( buildAddressLine( [addressRow.stName] ) );
			break;
		}
		case _ST_ROUTE:
		{
			setAddressLineOneDisplay( buildAddressLine( ["", "", addressRow.stName, addressRow.routeInfo] ) );									
			break;			
		}		
	}
	
	setCityDisplay( addressRow.city );
}

//******************************************************
function updateAddressDisplay( addressType, addressRow )
{	
	switch( addressType )
	{
		case _PO_BOX:
		{
			var poBoxNum = _addressEntryFieldMap[_PO_BOX_NUM]["fld"].value;
			setAddressLineOneDisplay( buildAddressLine( ["PO Box", poBoxNum, addressRow.delArea, addressRow.routeInfo] ) );					 
			break;			
		}
		case _RURAL_ROUTE:
		{	
			setAddressLineOneDisplay( buildAddressLine( [addressRow.delArea, addressRow.routeInfo] ) );
			break;			
		}
		case _GENERAL:
		{
			setAddressLineOneDisplay( buildAddressLine( [addressRow.delArea, addressRow.delInstall] ) );		
			break;			
		}
		case _CIVIC:
		{
			var strNum = _addressEntryFieldMap[_STREET_NUM]["fld"].value;							
			var suffix = _addressEntryFieldMap[_SUFFIX]["fld"].value.toUpperCase();
			var unitNum = _addressEntryFieldMap[_UNIT_NUM]["fld"].value.toUpperCase();
			var unitDesc = _addressEntryFieldMap[_UNIT_DESC]["fld"].value.toUpperCase();
			if ( unitDesc == "" && unitNum == "" )
			{
				setAddressLineOneDisplay( buildAddressLine( [strNum, suffix, addressRow.stName] ) );
			}
			else if ( unitDesc == "" && unitNum != "" ) 
			{
				setAddressLineOneDisplay( buildAddressLine( [unitNum + "-" + strNum, suffix, addressRow.stName] ) );
			}
			else
			{
				setAddressLineOneDisplay( buildAddressLine( [strNum, suffix, addressRow.stName, unitDesc, unitNum] ) );
			}
			break;
		}
		case _ST_ROUTE:
		{
			var strNum = _addressEntryFieldMap[_STREET_NUM]["fld"].value;							
			var suffix = _addressEntryFieldMap[_SUFFIX]["fld"].value.toUpperCase();
			setAddressLineOneDisplay( buildAddressLine( [strNum, suffix, addressRow.stName, addressRow.routeInfo] ) );									
			break;			
		}		
	}	
}

//******************************************************
function setSelectedAddressRecord( addressType, rowIndex )
{	
	if ( _selectedAddressType != null && _selectedAddressType != addressType )
	{
		clearSelectedAddressRecord();	
	}
	
	clearAddressDetails();
	
	_selectedAddressType = addressType;
	_selectedAddressRow = UTL.getElem( addressType + "_AddressList_Table" ).lastChild.childNodes[rowIndex];
	
	initAddressDisplay( addressType, _selectedAddressRow );
	
	for ( var i = 0; i < _addressListMap[addressType]["applicableFlds"].length; i++ )
	{
		enableAddressEntryField( _addressListMap[addressType]["applicableFlds"][i] );
	}
	
	if ( _selectedAddressRow.oddeven )
	{
		showOddEvenWarning( _selectedAddressRow.oddeven.toLowerCase() );		
	}
	else
	{
		hideOddEvenWarning();
	}
	
	if ( ( _selectedAddressRow.stFrom && _selectedAddressRow.stTo )
		&& ( _selectedAddressRow.stFrom == _selectedAddressRow.stTo ) )	 
	{
		_addressEntryFieldMap[_STREET_NUM]["fld"].value = _selectedAddressRow.stFrom;
		changeHandler_streetNumFld(); 	
	}
	
	if ( ( _selectedAddressRow.pobFrom && _selectedAddressRow.pobTo )
		&& ( _selectedAddressRow.pobFrom == _selectedAddressRow.pobTo ) )
	{
		_addressEntryFieldMap[_PO_BOX_NUM]["fld"].value = _selectedAddressRow.pobFrom;
		changeHandler_poBoxFld();
	}
}

//******************************************************
function clearAddressDetails()
{
	clearAddressLineOneDisplay();
	clearCityDisplay();
		
	clearAllAddressEntryFields();
	disableAllAddressEntryFields();
	
	hideOddEvenWarning();
	
	if ( _addressDisplayFlag )
	{
		_addressDisplayFlag.hide();
	}
}

//******************************************************
function clearSelectedAddressRecord()
{
	if ( _selectedAddressType != null )
	{
		IFDSTableManager.getTable( _selectedAddressType + "_AddressList_Table" ).clearSelectedRowIndex();
	}
	
	_selectedAddressType = null;
	_selectedAddressRow = null;	
}

//******************************************************
function setProvDisplay( prov, cntryCode, pstlCode )
{
	var provLbl = UTL.getElem( "provLabel" ); 
	provLbl.innerHTML = prov;
	provLbl.prov = prov;
	provLbl.cntryCode = cntryCode;
	provLbl.pstlCode = pstlCode;	
}

//******************************************************
function getProv()
{
	return UTL.getElem( "provLabel" ).prov;
}

//******************************************************
function getCntryCode()
{
	return UTL.getElem( "provLabel" ).cntryCode;
}

//******************************************************
function getPstlCode()
{
	return UTL.getElem( "provLabel" ).pstlCode;
}

//******************************************************
function getProvCode()
{
	return UTL.getElem( "provLabel" ).provCode;
}

//******************************************************
function clearProvDisplay()
{
	var provLbl = UTL.getElem( "provLabel" ); 
	provLbl.innerHTML = "";
	provLbl.provCode = "";
}

//******************************************************
function setAddressLineOneDisplay( text )
{
	var addrLineOneLbl = UTL.getElem( "addressLineOneLabel" ); 
	addrLineOneLbl.innerHTML = text	
}

//******************************************************
function getAddressLineOneDisplay()
{
	return UTL.getElem( "addressLineOneLabel" ).innerHTML;
}

//******************************************************
function clearAddressLineOneDisplay()
{
	var addrLineOneLbl = UTL.getElem( "addressLineOneLabel" ); 
	addrLineOneLbl.innerHTML = "";	
}

//******************************************************
function setCityDisplay( text )
{
	var cityLbl = UTL.getElem( "cityLabel" ); 
	cityLbl.innerHTML = text;	
}

//******************************************************
function getCityDisplay()
{	
	return UTL.getElem( "cityLabel").innerHTML;
}

//******************************************************
function clearCityDisplay()
{
	var cityLbl = UTL.getElem( "cityLabel" ); 
	cityLbl.innerHTML = "";	
}

//******************************************************
function buildAddressLine( itemArray )
{
	var addressLine = "";
	for ( var i = 0; i < itemArray.length; i++ )
	{
		addressLine += itemArray[i];
		if ( i < itemArray.length - 1 )
		{
			addressLine += " ";
		}
	}
	
	return addressLine;
}

//******************************************************
function doAddressLookup()
{
	if ( _postalCodeFld.value != "" )
	{
		clearProvDisplay();
		clearSelectedAddressRecord();
		clearAddressListTables();										
		clearAddressDetails();		
		sendAddressLookupRequest( doAddressLookup_callback );		
	}
	else
	{
		alert( "FUNCTION ERRROR: PostalCode is required" );
	}
}

//******************************************************
function doAddressLookup_callback( addressLookupResponseXML )
{
	if ( addressLookupResponseXML )
	{
		loadAddressListTables( XML.getNode( "addressList", addressLookupResponseXML ) );
		
		var prov = XML.getNode( "provDetails/prov", addressLookupResponseXML ).firstChild.nodeValue;
		var cntryCode = XML.getNode( "provDetails/cntryCode", addressLookupResponseXML ).firstChild.nodeValue;
		var pstlCode = XML.getNode( "provDetails/pstlCode", addressLookupResponseXML ).firstChild.nodeValue;
		setProvDisplay( prov, cntryCode, pstlCode );
	}
	else
	{
		alert( "FUNCTION ERRROR: addressLookupResponseXML is null" );
	}
}

//******************************************************
function sendAddressLookupRequest( callbackFn )
{		
	function sendAddressLookupRequest_callback( responseText )
	{		
		hideProcessingIndicator();
		
		var addressXML = null;
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
					addressXML = XML.getNode( "/responseContents/addressLookupResponse", responseXML );
					callbackFn( addressXML );										
				}
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendAddressLookupRequest error caught: " + e.description ); 		
		}
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "AddressLookup_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
	paramMap["pstlCode"] = _postalCodeFld.value;	
            
    var url = HTTP.buildURL( _vServletPath, paramMap );   
                		    	 
	var req = HTTP.getGETRequest( url );			
	req.setCallbackFunction( sendAddressLookupRequest_callback );	
	showProcessingIndicator();
	req.send();		
}

//******************************************************
function loadAddressListTables( addressListXML )
{		
	var resultContentsDiv = UTL.getElem( "ResultContentsDiv" );
	
	// add response results	
	resultContentsDiv.innerHTML = addressListXML.firstChild.xml;	
	initAddressListTables()		
}

//******************************************************
function clearAddressListTables()
{
	var resultContentsDiv = UTL.getElem( "ResultContentsDiv" );
	
	// remove existing results
	for ( var addressType in _addressListMap )
	{
		var table = UTL.getElem( addressType + "_AddressList_Table" );
		if ( table != null )
		{
			IFDSTableManager.removeTable( addressType + "_AddressList_Table" ); 			
		}
	}
	
	if ( resultContentsDiv.firstChild )
	{
		resultContentsDiv.removeChild( resultContentsDiv.firstChild );
	}
}

//******************************************************
function paintAddressEntryFieldErrorFlag( fldName, desc )
{		
	var fld = _addressEntryFieldMap[fldName]["fld"];
	
	var posMap = WebTools.calcElemPos( fld );
	var width = parseInt( WebTools.getComputedStyle( fld, "width" ) );
	if (fld.ifdsDatepicker == "true" )
	{
		width += 25; 	
	}	
	
	var flag = new DesktopFlag( fld.id + "_flag", DesktopFlag.ERROR, desc );
	flag.setFieldAssoc( fld.id );
	
	flag.setPosition( posMap.top, posMap.left + width + 2 );	
	flag.show();	
		
	return flag;
}

//******************************************************
function paintAddressDisplayErrorFlag( desc )
{		
	var div = UTL.getElem( "addressDisplayDiv" );
	
	var posMap = WebTools.calcElemPos( div );	
	var width = parseInt( WebTools.getComputedStyle( div, "width" ) );	
	
	var flag = new DesktopFlag( div + "_flag", DesktopFlag.ERROR, desc );	
	
	flag.setPosition( posMap.top, posMap.left + width + 2 );	
	flag.show();	
	
	return flag;
}

//******************************************************
function getResult()
{
	var resultStr = "";
	resultStr += "AddrLine1=" + getAddressLineOneDisplay() + ";";		
	resultStr += "AddrLine2= ;";
	resultStr += "AddrLine3= ;";
	resultStr += "AddrLine4= ;";
	resultStr += "AddrLine5= ;";
	 
	resultStr += "CountryCode=" + getCntryCode() + ";";
	resultStr += "City=" + getCityDisplay() + ";";
	resultStr += "PostalCode=" + getPstlCode() + ";";
	resultStr += "Province=" + getProv() + ";";
	
	return resultStr;
}
