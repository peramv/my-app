var _fundCode = null;
var _classCode = null;


//******************************************************
function loading()
{
	if ( UTL.getElem( "ClassData" ) )
	{			
		ClassDataManager.init( XML.parseToXML( UTL.getElem( "ClassData" ).xml ) );
	}
	
	if ( UTL.getElem( "UpdatedClassData" ) )
	{		
		ClassDataManager.loadExistingUpdates( XML.parseToXML(  UTL.getElem( "UpdatedClassData" ).xml ) );
	}
					
	IFDSTableManager.init();
	initSectionDetailsMap();
	
	collapseAllDetailsSections();
	
	var updatesAvailable = false;
	if ( ClassDataManager.getUpdateData( "ClassBasic" ) )
	{		
		expandDetailsSection( "BasicInfo" );
		updatesAvailable = true;
	}
	if ( ClassDataManager.getUpdateData( "TradeConfiguration" ) )
	{
		expandDetailsSection( "TradeConf" );
		updatesAvailable = true;
	}
	if ( ClassDataManager.getUpdateData( "DistributionConfig" ) )
	{
		expandDetailsSection( "DistrConf" );
		updatesAvailable = true;
	}
	if ( ClassDataManager.getUpdateData( "PriceInfo" ) )
	{
		expandDetailsSection( "PriceInfo" );
		updatesAvailable = true;
	}
	if ( ClassDataManager.getUpdateData( "FeeConfiguration" ) )
	{
		expandDetailsSection( "FeeConf" );
		updatesAvailable = true;
	}
	if ( ClassDataManager.getUpdateData( "TradeDayControls" ) )
	{
		expandDetailsSection( "TradeDayCtrls" );
		updatesAvailable = true;
	}
	
	if ( updatesAvailable )
	{
		UTL.getElem( "submitBtn" ).disabled = false;
	}	
}

//******************************************************
function initSectionObj( sectionName )
{
	var obj = {};	
	obj["sectionDiv"] 	= UTL.getElem( sectionName + "SectionDiv" );
	obj["headerDiv"] 	= UTL.getElem( sectionName + "DetailsHeaderDiv" );
	obj["contentDiv"] 	= UTL.getElem( sectionName + "DetailsContentDiv" );
	obj["detailsTable"] = UTL.getElem( sectionName + "Details_Table" );
	obj["expandBtn"] 	= UTL.getElem( sectionName + "DetailsExpandBtn" );
	obj["collapseBtn"] 	= UTL.getElem( sectionName + "DetailsCollapseBtn" );	
	
	return obj;
}

//******************************************************
function clickHandler_expandAllBtn()
{
	expandAllDetailsSections();
}

//******************************************************
function clickHandler_collapseAllBtn()
{
	collapseAllDetailsSections();
}

//******************************************************
function clickHandler_collapseSectionBtn( sectionName )
{
	collapseDetailsSection( sectionName );
}

//******************************************************
function clickHandler_expandSectionBtn( sectionName )
{
	expandDetailsSection( sectionName );
}

//******************************************************
function clickHandler_sectionLabel( sectionName )
{
	if ( _detailsSectionMap[sectionName].expandBtn.style.display == "none" )
	{
		collapseDetailsSection( sectionName );
	}
	else
	{
		expandDetailsSection( sectionName );
	} 
}

//******************************************************
function initSectionDetailsMap()
{
	for ( var i in _detailsSectionMap )
	{
		_detailsSectionMap[i] = initSectionObj( i );
	}										
}

//******************************************************
function clickHandler_editBtn( sectionName )
{
	initEditScreen( sectionName );
}	

//******************************************************
function collapseAllDetailsSections()
{
	for ( var i in _detailsSectionMap )
	{
		collapseDetailsSection( i )
	}
}

//******************************************************
function expandAllDetailsSections()
{
	for ( var i in _detailsSectionMap )
	{
		expandDetailsSection( i )
	}
}

//******************************************************
function expandDetailsSection( name )
{
	_detailsSectionMap[name].contentDiv.style.display = "block";
	_detailsSectionMap[name].contentDiv.style.height = _detailsSectionMap[name].detailsTable.offsetHeight;
	
	_detailsSectionMap[name].collapseBtn.style.display = "inline";
	_detailsSectionMap[name].expandBtn.style.display = "none";
}

//******************************************************
function collapseDetailsSection( name )
{
	_detailsSectionMap[name].contentDiv.style.display = "none";
	_detailsSectionMap[name].collapseBtn.style.display = "none";
	_detailsSectionMap[name].expandBtn.style.display = "inline";
}

//******************************************************
function clickHandler_detailsLink( detailsCell )
{
	displayRecordDetails( detailsCell.data );
}

//******************************************************
function clickHandler_popupCloseBtn()
{
	Desktop.hidePopup( "feeScalePopupDiv" );
}

//******************************************************
function displayRecordDetails( dataString )
{
	var fieldArray = dataString.split( ";" );
	
	for ( var i = 0; i < fieldArray.length; i++ )
	{
		var nameValueArray = fieldArray[i].split( "=" );
		try {
			UTL.getElem("popup_" + nameValueArray[0] + "Fld").innerHTML = nameValueArray[1];
		}catch(err){}	
	}
		
	Desktop.showPopup( "feeScalePopupDiv" );
}

//******************************************************
function clickHandler_cancelBtn()
{
	if ( UTL.getElem( "submitBtn").disabled 
		 || confirm( "Are you sure you wish to discard updates?" ) )
	{
		ClassDataManager.returnToMainScreen();
	}
}


//******************************************************
function initEditScreen( screenName )
{
	var paramMap = {}
	paramMap["cz"]                = _vCZ;
	paramMap["jobname"]           = "FundSetup_ClassMaint_InitEdit";    
	paramMap["companyCode"]       = _companyCode;
	paramMap["tidx"]	          = _tidx;
	paramMap["ruserId"]           = _ruserId;
	paramMap["sessionId"]         = _sessionId;
	paramMap["envName"]           = _envName;
	paramMap["dateFormat"]        = _dateFormat;
	paramMap["bgcolor"]       	  = _vDesktopColor;	 
	paramMap["screenToLoad"]      = screenName;	
	
	var url = HTTP.buildURL( _vServletPath, paramMap );	
	window.location = url;
}

//******************************************************
function clickHandler_submitBtn()
{
	doFundClassUpdateSubmit();
}

//******************************************************
function doFundClassUpdateSubmit()
{	
	var updateXML = XML.serialize( ClassDataManager.getUpdateXMLDoc() );
	//prompt( "", updateXML );
	sendFundClassUpdateSubmitRequest( updateXML, doFundClassUpdateSubmit_callback );	
}

//******************************************************
function doFundClassUpdateSubmit_callback( success )
{
	if ( success )
	{
		alert( "Class update submitted successfully." )
		ClassDataManager.returnToMainScreen();
	}
}

//******************************************************
function sendFundClassUpdateSubmitRequest( updateXML, callbackFn )
{		
	function sendFundClassUpdateSubmitRequest_callback( responseText )
	{
		//prompt( "", responseText );
		Desktop.hideProcessingIndicator();
		
		var success = true;
		var responseXML = null;				
		try 
		{
			responseXML = XML.parseToXML( responseText );										
		}
		catch( e )
		{ 
			alert( "sendFundClassUpdate error caught: " + e.description ); 		
		}
		
		if ( responseXML != null )
		{
			if ( responseErrorFound( responseXML ) )
			{
				displayResponseError( responseXML );
				success = false;			
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
    paramMap["jobname"]           = "FundSetup_ClassMaint_Update";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    paramMap["tidx"]	          = _tidx;
			        
    var url = HTTP.buildURL( _vServletPath, paramMap );                    		    	
	    	   
	var req = HTTP.getPOSTRequest( url );	
	req.setCallbackFunction( sendFundClassUpdateSubmitRequest_callback );
	Desktop.showProcessingIndicator();
	//prompt( "", updateXML );
	req.send( updateXML )
}

//******************************************************
function displayResponseError( responseXML )
{
	var errorNode = XML.getNode( "/responseContents/Error", responseXML );
	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
	if ( errorType.toLowerCase() == "environment" )
	{
		DesktopError.displayProcessingError( "Fund Setup - Class Update", errorMsg );  
	}
	else
	{
		alert( errorMsg );
	}
}

//******************************************************
function responseErrorFound( responseXML )
{
	return XML.getNode( "/responseContents/Error", responseXML ) != null
}