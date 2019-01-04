var _initFundCode = null;
var _fundFld = null;


//******************************************************
function loading()
{
	_fundFld = UTL.getElem( "fundFld" );
		
	IFDSTableManager.init();
	IFDSTableManager.getTable( "ClassList_Table" ).setOnRowSelectedFunction( selectHandler_ClassListTable );
	
	disableClassLookupBtn();
	disableAddBtn();
	disableViewBtn();
	disableOverrideBtn();
	
	if ( _initFundCode )
	{
		_fundFld.initialValue = _initFundCode;
		SuggestFieldManager.reInit( _fundFld );
		doClassLookup( _initFundCode );		
	}	
}

//******************************************************
function clickHandler_classLookupBtn()
{	
	if ( _fundFld._suggestDataObj )
	{	
		doClassLookup( _fundFld._suggestDataObj["fundCode"] );
	}
	else
	{
		alert( "FUNCTION ERROR: no fund specified" );
	}
}

//******************************************************
function keyupHandler_fundFld()
{	
	if ( KeyMap.getKeyDesc( window.event.keyCode, KeyMap.KEYUP ) == KeyMap.ENTER && fundFld._suggestDataObj )				
	{		
		doClassLookup( _fundFld._suggestDataObj["fundCode"] );
	}
}

//******************************************************
function updateHandler_fundFld()
{	
	disableViewBtn();
	disableOverrideBtn();		
	
	if ( _fundFld._suggestDataObj )
	{
		if ( _permissionsMap["add"] == "yes" )
		{
			enableAddBtn();
		}
		enableClassLookupBtn();		
	}
	else
	{
		disableAddBtn();
		disableClassLookupBtn();		
	}
}

//******************************************************
function clickHandler_addBtn()
{		
	goToAddScreen();	
}

function clickHandler_limitOverrideBtn()
{
	goToLimitOverrideScreen();	
}

//******************************************************
function clickHandler_viewBtn()
{
	goToViewScreen();
}

//******************************************************
function selectHandler_ClassListTable( rowIndex )
{
	if ( rowIndex != null )
	{
		if ( _permissionsMap["inq"] == "yes" )
		{		
			enableViewBtn();
			enableLimitOverrideBtn();
		}
	}
	else
	{
		alert( "FUNCTION ERROR: rowIndex is null" );
	}	
}

//******************************************************
function enableClassLookupBtn()
{
	UTL.getElem( "classLookupBtn" ).disabled = false;	
}

//******************************************************
function disableClassLookupBtn()
{
	UTL.getElem( "classLookupBtn" ).disabled = true;	
}

//******************************************************
function enableAddBtn()
{	
	UTL.getElem( "addBtn" ).disabled = false;	
}

//******************************************************
function disableAddBtn()
{
	UTL.getElem( "addBtn" ).disabled = true;	
}

//******************************************************
function enableViewBtn()
{
	UTL.getElem( "viewBtn" ).disabled = false;	
}

//******************************************************
function disableViewBtn()
{
	UTL.getElem( "viewBtn" ).disabled = true;	
}

//******************************************************
function enableOverrideBtn()
{
	UTL.getElem( "limitOverrideBtn" ).disabled = false;	
}

//******************************************************
function disableOverrideBtn()
{
	UTL.getElem( "limitOverrideBtn" ).disabled = true;	
}

//******************************************************
function disableLimitOverrideBtn()
{
	UTL.getElem( "limitOverrideBtn" ).disabled = true;	
}

//******************************************************
function enableLimitOverrideBtn()
{
	UTL.getElem( "limitOverrideBtn" ).disabled = false;	
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
function goToAddScreen()
{
	if ( _fundFld._suggestDataObj )
	{
		var initialClassDataXMLDoc = XML.newDocument( "UpdatesToSave" );		
		XML.addNodeWithValue( "fundCode", initialClassDataXMLDoc, _fundFld._suggestDataObj["fundCode"] );
		XML.addNodeWithValue( "fundName", initialClassDataXMLDoc, _fundFld._suggestDataObj["fndDisp"] );	
				
		var form = UTL.getElem( "screenForm" );
		
		form.action = _vServletPath;
		
		UTL.getElem( "czFld" ).value     		= _vCZ;
		UTL.getElem( "jobnameFld" ).value       = "FundSetup_ClassMaint_InitEdit";    
		UTL.getElem( "companyCodeFld" ).value   = _companyCode;
		UTL.getElem( "ruserIdFld" ).value       = _ruserId;
		UTL.getElem( "sessionIdFld" ).value     = _sessionId;
		UTL.getElem( "envNameFld" ).value       = _envName;
		UTL.getElem( "dateFormatFld" ).value    = _dateFormat;
		UTL.getElem( "bgcolorFld" ).value       = _vDesktopColor;
		UTL.getElem( "tidxFld" ).value        	= _tidx;    
		UTL.getElem( "screenToLoadFld" ).value  = _editScreenNameArray[0];
		
		UTL.getElem( "data" ).value = XML.serialize( initialClassDataXMLDoc );
		
		Desktop.showProcessingIndicator();
		
		form.submit();
	}
	else
	{
		alert( "FUNCTION ERROR: fundFld not populated" );
	}
}

//******************************************************
function goToViewScreen()
{
	if ( _fundFld._suggestDataObj )
	{
		var selectedRowIndex = IFDSTableManager.getTable( "ClassList_Table" ).getSelectedRowIndex();		
		if ( selectedRowIndex != null )
		{		
			var paramMap = {}
		    paramMap["cz"]                = _vCZ;
		    paramMap["jobname"]           = "FundSetup_ClassMaint_Inquiry";    
		    paramMap["companyCode"]       = _companyCode;
		    paramMap["ruserId"]           = _ruserId;
		    paramMap["sessionId"]         = _sessionId;
		    paramMap["envName"]           = _envName;
		    paramMap["dateFormat"]        = _dateFormat;
		    paramMap["bgcolor"]       	  = _vDesktopColor;    
		    paramMap["tidx"]       	  	  = _tidx;
		    paramMap["fundCode"]	      = _fundFld._suggestDataObj.fundCode;	    	   
			paramMap["classCode"] 		  = UTL.getElem( "ClassList_Table" ).lastChild.childNodes[selectedRowIndex].classCode;
			
			var url = HTTP.buildURL( _vServletPath, paramMap );		
			window.location = url;   
		}
		else
		{
			alert( "FUNCTION ERROR: no class row selected" );
		}
	}
	else
	{
		alert( "FUNCTION ERROR: fundFld not populated" );
	}
}

//******************************************************
function goToLimitOverrideScreen()
{
	if ( _fundFld._suggestDataObj )
	{
		var selectedRowIndex = IFDSTableManager.getTable( "ClassList_Table" ).getSelectedRowIndex();		
		if ( selectedRowIndex != null )
		{		
			var paramMap = {}
		    paramMap["cz"]                = _vCZ;
		    paramMap["jobname"]           = "FundSetup_ClassMaint_LtOvrd_Init";    
		    paramMap["companyCode"]       = _companyCode;
		    paramMap["ruserId"]           = _ruserId;
		    paramMap["sessionId"]         = _sessionId;
		    paramMap["envName"]           = _envName;
		    paramMap["dateFormat"]        = _dateFormat;
		    paramMap["bgcolor"]       	  = _vDesktopColor;    
		    paramMap["tidx"]       	  	  = _tidx;
		    paramMap["fundCode"]	      = _fundFld._suggestDataObj.fundCode;	    	   
			paramMap["classCode"] 		  = UTL.getElem( "ClassList_Table" ).lastChild.childNodes[selectedRowIndex].classCode;
			
			var url = HTTP.buildURL( _vServletPath, paramMap );		
			window.location = url;   
		}
		else
		{
			alert( "FUNCTION ERROR: no class row selected" );
		}
	}
	else
	{
		alert( "FUNCTION ERROR: fundFld not populated" );
	}
}

//******************************************************
function doClassLookup( fundCode )
{	
	sendClassLookupRequest( fundCode, doClassLookup_callback );			
}

//******************************************************
function doClassLookup_callback( classListXML )
{	
	if ( classListXML )
	{
		reloadClassListTable( classListXML );																						
	}
}

//******************************************************
function sendClassLookupRequest( fundCode, callbackFn )
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
    paramMap["jobname"]           = "FundSetup_ClassMaint_Lookup";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;    
    
	paramMap["fundCode"] = fundCode;	
            
    var url = HTTP.buildURL( _vServletPath, paramMap );   
                		    	 
	var req = HTTP.getGETRequest( url );			
	req.setCallbackFunction( sendClassLookupRequest_callback );	
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
function reloadClassListTable( classListXML )
{			
	var classListTableHTML = classListXML.firstChild.xml;
	
	var classListTableDiv = UTL.getElem( "ClassList_TableDiv" );
	classListTableDiv.removeChild( classListTableDiv.firstChild );
	classListTableDiv.innerHTML = classListTableHTML;
		
	IFDSTableManager.reInitTable( "ClassList_Table" );
	
	disableViewBtn();
	disableLimitOverrideBtn();	
}

