var _searchOptMap = {};
_searchOptMap["fund"] 		= null;
_searchOptMap["asset"] 		= null;
_searchOptMap["subasset"] 	= null;

var _contentsDiv			= null;
var _searchIndicator 		= null;
var _pageDisabler			= null; 


function loading()
{
	_searchOptMap["fund"] 		= UTL.getElem( "fundOpt" );	
	_searchOptMap["asset"] 		= UTL.getElem( "assetOpt" );
	_searchOptMap["subasset"] 	= UTL.getElem( "subassetOpt" );		
	_searchOptMap[_searchType].checked = true;
	
	for( var i in _searchOptMap )
	{
		EvtHandler.add( _searchOptMap[i], "click", clickHandler_searchOpt )
	}
		
	_contentsDiv 		= UTL.getElem( "contentsDiv" );
	_searchIndicator	= UTL.getElem( "searchIndicatorDiv" );
	_pageDisabler		= UTL.getElem( "disableDiv" );	
}


function clickHandler_searchOpt( e )
{
	var opt = e.currentTarget;	
	if ( opt.value != _searchType )
	{
		reload( opt.value );
	}
}

function showSearchIndicator()
{
	_pageDisabler.style.top = _contentsDiv.offsetTop;
	_pageDisabler.style.top = _contentsDiv.offsetLeft;
	_pageDisabler.style.width = _contentsDiv.offsetWidth;
	_pageDisabler.style.height = _contentsDiv.offsetHeight + 10;
	
	_pageDisabler.style.display = "block";
	_searchIndicator.style.display = "block";
}

function hideSearchIndicator()
{
	_pageDisabler.style.display = "none";
	_searchIndicator.style.display = "none";
}


function buildBaseURL()
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;       
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
    return HTTP.buildURL( _vServletPath, paramMap ); 
}


function reload( searchType )
{
	showSearchIndicator();
	
	var paramMap = {};
	paramMap["jobname"] 	= "AMSAssetInfo_Reload";
	paramMap["AccountNum"]  = _accountNum;
	paramMap["searchType"] 	= searchType;
	
	var url = HTTP.appendParamToURL( buildBaseURL(), paramMap );
	HTTP.getText( url, reload_callback )	
}


function reload_callback( responseText )
{	
    var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/error", responseXML );
        
    if ( errorNode )
    {
        alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
        return;
    }
    else
    {
    	var searchTypeNode = XML.getNode( "/responseContents/searchType", responseXML );
    	_searchType = searchTypeNode.firstChild.nodeValue.toLowerCase();
    
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
        
        // clear the current inner html
        var listContentsDiv = UTL.getElem( "listContentsDiv" );
        listContentsDiv.innerHTML = "";        
        listContentsDiv.innerHTML = updatedHTMLNode.firstChild.xml;
        
        IFDSTableManager.tableMap["listContentsTable"].init( UTL.getElem( "listContentsTable" ) );       
    }
    
    hideSearchIndicator();
}