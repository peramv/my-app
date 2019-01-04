var _sessionToken = null;

/* These sessionToken functions need to be at global level to work with Desktop-C++ */
//**************************************************************
function setSessionToken( st )
{
	_sessionToken = st;
}

//**************************************************************
function getSessionToken()
{
	return _sessionToken;
}


//**************************************************************
var Desktop = new function()
{	
	this.SUCCESS = "success";
	this.FAIL = "fail";
	
	this.showProcessingIndicator = function()
	{
		this.disableScreen();
		UTL.getElem( "DesktopScreenProcessingIndicatorDiv" ).style.visibility = "visible";	
	}

	this.hideProcessingIndicator = function()
	{	
		UTL.getElem( "DesktopScreenProcessingIndicatorDiv" ).style.visibility = "hidden"
		this.undisableScreen();
	}
	
	this.disableScreen = function()
	{
		document.body.className = "Desktop_DisabledBackground";
		UTL.getElem( "DesktopScreenDisablerDiv" ).style.visibility = "visible"; 
	}
	
	this.undisableScreen = function()
	{
		document.body.className = "Desktop_Background";
		UTL.getElem( "DesktopScreenDisablerDiv" ).style.visibility = "hidden"; 
	}
		
	this.showPopup = function( popupId, caption, draggable )
	{
		UTL.getElem( popupId ).style.display = "block";
		
		if ( caption )
		{
			UTL.getElem( popupId + "_caption" ).innerHTML = caption;	
		}
		this.disableScreen();
		
		if ( draggable )
		{
			UTL.getElem( popupId + "_caption" ).onmousedown = mouseDownHandler;
			UTL.getElem( popupId + "_caption" ).style.cursor = "move";
			function mouseDownHandler() 
			{
				WebTools.dragElement(window.event, UTL.getElem( popupId + "_caption" ), UTL.getElem( popupId ), "move");
			}			
		} 
	}
	
	this.hidePopup = function( popupId )
	{
		UTL.getElem( popupId ).style.display = "none";
		this.undisableScreen(); 
	}
	
	this.paintFieldErrorFlag = function( flagMap, fldId, desc )
	{	
		var fld = UTL.getElem( fldId );
		
		var posMap = WebTools.calcElemPos( fld );
		var width = parseInt( WebTools.getComputedStyle( fld, "width" ) );
		if (fld.ifdsDatepicker == "true" )
		{
			width += 25; 	
		}	
		
		var flag = new DesktopFlag( fldId + "_flag", DesktopFlag.ERROR, desc );
		flag.setFieldAssoc( fldId );
		
		flag.setPosition( posMap.top, posMap.left + width + 2 );	
		flag.show();
		
		flagMap[fldId] = flag;
	}
		
	var _openHistoricalPopupId = null;
	
	this.closeHistoricalPopup = function()
	{
		Desktop.hidePopup( _openHistoricalPopupId );	
	}
	
	this.displayHistorical = function( popupDivId, jobname, params )
	{
		_openHistoricalPopupId = popupDivId;
		UTL.getElem( popupDivId + "_caption" ).style.cursor = "move";
		
		var paramMap = {}
	    paramMap["cz"]                = _vCZ;
	    paramMap["jobname"]           = jobname;    
	    paramMap["companyCode"]       = _companyCode;
	    paramMap["ruserId"]           = _ruserId;
	    paramMap["sessionId"]         = _sessionId;
	    paramMap["envName"]           = _envName;
	    paramMap["dateFormat"]        = _dateFormat;
	    
	    for( var i in params )
	    {
	    	paramMap[i] = params[i];
	    }
	    	       
	    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
		var req = HTTP.getGETRequest( url );
		req.setAsynch( false );			
		req.setCallbackFunction( displayHistorical_callback );				
		req.send();		
		
				
		function displayHistorical_callback( responseText )
		{		
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
						if ( IFDSTableManager.getTable( popupDivId + "_table" ) )
						{								
							IFDSTableManager.removeTable( popupDivId + "_table" );													
						}
						
						var historicalDetailsContentDiv = UTL.getElem( popupDivId + "_content" ).firstChild.firstChild;
						historicalDetailsContentDiv.innerHTML = "";
						historicalDetailsContentDiv.innerHTML = XML.getNode( "/responseContents", responseXML ).firstChild.firstChild.xml;						
						var tableDiv = historicalDetailsContentDiv.firstChild;						
						tableDiv.id = popupDivId + "_tableDiv";
						var table = tableDiv.firstChild;
						
						table.id = popupDivId + "_table";
																		
						IFDSTableManager.addTable( table.id );
								
						Desktop.showPopup( popupDivId );
						UTL.getElem( "HistoryPopupDiv_caption" ).onmousedown = mousedownHandler;		
					}									
				}														
			}
			catch( e )
			{ 
				alert( "FUNCTION ERROR: displayHistorical error caught: " + e.description ); 		
			}
		}
		
		function mousedownHandler()
		{
			WebTools.dragElement( window.event, UTL.getElem( "HistoryPopupDiv_caption" ), UTL.getElem( "HistoryPopupDiv" ), "move" );
		}	
	}	
}


