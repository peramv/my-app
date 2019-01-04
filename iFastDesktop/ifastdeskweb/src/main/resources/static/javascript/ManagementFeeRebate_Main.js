var _disableDiv = null;
var _searchIndicator = null;

function loading()
{
    _disableDiv = UTL.getElem( "disableDiv");
    _searchIndicator = UTL.getElem( "searchIndicatorDiv");
}


function toggleDiv( divId )
{
    var div = UTL.getElem( divId )
	if ( div.style.display == "none" )
	{
	    div.style.display = "block";
	}
	else
	{	    
		div.style.display = "none";	
	}
}


function togglePlusMinus( img )
{
	if (img.nameProp == "plus.png")
		img.src = _vURL + "images/minus.png";
	else
		img.src = _vURL + "images/plus.png";
}


function launchDetails( feeModelCode )
{    
   var paramMap = {};
    paramMap["cz"]             = _vCZ;
    paramMap["jobname"]        = "ManagementFeeRebate_Details";
    paramMap["companyCode"]    = _companyCode;
    paramMap["ruserId"]        = _ruserId;
    paramMap["sessionId"]      = _sessionId;
    paramMap["envName"]        = _envName;
    paramMap["dateFormat"]     = _dateFormat;
    if ( feeModelCode )
    {
        paramMap["feeModelCode"]   = feeModelCode;
    }
     
         
    var url = HTTP.buildURL( _vServletPath, paramMap );

	var feeIDFrame = UTL.getElem( "feeID_Frame" );	
	
	// store the default src
	feeIDFrame.defaultSrc = feeIDFrame.src;
	// set new src
	feeIDFrame.src = url;
	
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	if(feeModelCode == null)
	{
		UTL.getElem("searchFld").value = "";
		UTL.getElem( "dataDiv" ).innerHTML = ""; 
	}

	feeIDFrame.style.display = "block";
}


function closeFeeIDScreen( refresh )
{
    var feeIDFrame = UTL.getElem( "feeID_Frame" );	
	
	feeIDFrame.src = "";
	
	feeIDFrame.style.display = "none";
	
	if ( refresh )
	{
	    _upatedOccured = true;	   
	}
	
	UTL.getElem( "disableDiv" ).style.display = "none";
	
	// restore the default src
	feeIDFrame.src = feeIDFrame.defaultSrc;
	
	// run search again, so will show any updates that have happened
	search();
}


function deleteFeeID( feeID )
{
    alert( "not yet implemented" );
}



function expandFundDetails( num )
{       
    var fundDetailsDiv = UTL.getElem( "fundDetails_fund" + num );
    fundDetailsDiv.style.display = "block";
    
    // toggle button visibility
    UTL.getElem( "expandBtn_fund" + num ).style.display = "none";
    UTL.getElem( "collapseBtn_fund" + num ).style.display = "inline";
           
}



function collapseFundDetails( num )
{
    var fundDetailsDiv = UTL.getElem( "fundDetails_fund" + num );
    fundDetailsDiv.style.display = "none";    
    
    // toggle button visibility
    UTL.getElem( "expandBtn_fund" + num ).style.display = "inline";
    UTL.getElem( "collapseBtn_fund" + num ).style.display = "none";
}



function search()
{    
    var searchStr = UTL.getElem( "searchFld" ).value;
    if ( searchStr.length > 0 ) 
    {
        _disableDiv.style.display = "block";              
        _searchIndicator.style.display = "block";
           
        var paramMap = {};
        paramMap["cz"]                = _vCZ;
        paramMap["jobname"]           = "ManagementFeeRebate_Reload";    
        paramMap["companyCode"]       = _companyCode;
        paramMap["ruserId"]           = _ruserId;
        paramMap["sessionId"]         = _sessionId;
        paramMap["envName"]       	  = _envName;
    	paramMap["dateFormat"] 	      = _dateFormat;
        paramMap["searchValue"]       = searchStr;
        
        var url = HTTP.buildURL( _vServletPath, paramMap );
            
        HTTP.getText( url, search_callback, true );
    }                  
}



function search_callback( responseText )
{ 	
    var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/error", responseXML );
    
    _disableDiv.style.display = "none";
    _searchIndicator.style.display = "none";
    
    if ( errorNode )
    {
        alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
        return;
    }
    else
    {
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
        
        // clear the current inner html
        var dataDiv = UTL.getElem( "dataDiv" );
        dataDiv.innerHTML = "";        
        dataDiv.innerHTML = updatedHTMLNode.firstChild.xml;     
    }
}    

function handleKeyDownSearch()
{
	if(event.keyCode == 13)
	 	search();
}
