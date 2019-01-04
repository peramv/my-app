var _popupDiv          = null;
var _disableDiv        = null;
var _searchIndicator   = null;
var _selectedRow       = null;


function loading()
{
    _popupDiv         = UTL.getElem( "popupDiv" );
    _disableDiv       = UTL.getElem( "disableDiv" );
    _searchIndicator  = UTL.getElem( "searchIndicatorDiv" );    
}



function getAccountSearchURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]             = _vCZ;
    paramMap["jobname"]        = "General_AccountSearch";
    paramMap["companyCode"]    = _companyCode;
    paramMap["ruserId"]        = _ruserId;
    paramMap["sessionId"]      = _sessionId;
    paramMap["envName"]        = _envName;
         
    if ( nextRecNum )
    {
        paramMap["startRecordNum"] = nextRecNum;
    }
    paramMap["searchData"] = searchStr;
     
    return HTTP.buildURL( _vServletPath, paramMap );;    
}



function getFundSearchURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]                       = _vCZ;
    paramMap["jobname"]                  = "General_FundSuggest";
    paramMap["companyCode"]              = _companyCode;
    paramMap["ruserId"]                  = _ruserId;
    paramMap["sessionId"]                = _sessionId;
    paramMap["envName"]                  = _envName;
    paramMap["showAllClassRecords"]      = "no";
         
    if ( nextRecNum )
    {
        paramMap["startRecordNum"] = nextRecNum;
    }
    paramMap["searchData"] = searchStr;
     
    return HTTP.buildURL( _vServletPath, paramMap );;    
}



function buildXML( dataMap )
{
    var xml = "";
    for( var i in dataMap )
    {
        xml += XML.createNodeStr( i, dataMap[i] );
    }    
    return XML.createNodeStr( "Data", xml );
    
}



function getSearchDataMap( dataMap )
{
    if ( dataMap == null ) dataMap = {};
    
    dataMap["searchValue"]         			= UTL.getElem( "search_ValueFld" ).value;
    dataMap["searchStartDate"]              = UTL.getElem( "search_StartDateFld" ).value;
	dataMap["searchEndDate"]                = UTL.getElem( "search_StopDateFld" ).value;
	    
    var fundFld = UTL.getElem( "search_FundFld" );
    if ( fundFld._suggestDataObj )
    {
        dataMap["searchFundCode"]             = fundFld._suggestDataObj["fund"];
        dataMap["searchClassCode"]            = fundFld._suggestDataObj["class"];
    } 
    else
    {
        dataMap["searchFundCode"]             = "";
        dataMap["searchClassCode"]            = "";
    }
    
    return dataMap;    
}



function search()
{
     var dataMap = getSearchDataMap()

     _disableDiv.style.display = "block";
    
    _searchIndicator.style.left = 225;
    _searchIndicator.style.top= 100
    _searchIndicator.style.display = "block";
    
    UTL.getElem( "accountBal_ListContentsDiv" ).innerHTML = "";     
           
    var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "AccountBalanceOverride_Reload";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
	paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;        
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
    
    HTTP.postText( url, search_callback, buildXML( dataMap ), true );    
}



function search_callback( responseText )
{
    _disableDiv.style.display = "none";
    _searchIndicator.style.display = "none";
    
    var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/error", responseXML );
    
    if ( errorNode )
    {
    	// check if any searchMatchDetails were returned
    	var searchMatchDetailsNode = XML.getNode( "/responseContents/searchMatchDetails", responseXML );
    	if ( searchMatchDetailsNode )
    	{
    		setSearchMatchDetails( responseXML );
    	}
    	
        alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
        return;
    }
    else
    {
    	var searchMatchDetailsNode = XML.getNode( "/responseContents/searchMatchDetails", responseXML );
    	if ( searchMatchDetailsNode )
    	{
    		setSearchMatchDetails( responseXML );
    	}
    
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
                
        // set the inner html to the html contents within updatedHTMLNode
        // note: the html contents are treated as xml within the xml dom                      
        UTL.getElem( "accountBal_ListContentsDiv" ).innerHTML = updatedHTMLNode.firstChild.xml;
        
        setResultsScrolling();
    }
}




function selectRow( row )
{
    if ( _selectedRow )
    {
        unselectRow(); 
    }
    
    highlightRow( row );
    _selectedRow = row;    
}




function unselectRow()
{
    unhighlightRow( _selectedRow );
    _selectedRow = null;        
}




function highlightRow( row )
{
	for( var i = 0; i < row.childNodes.length; i++ )
	{	
	 	row.childNodes[i].style.background = "url(" + _vURL + "images/rowHighlight.png)";    
	    row.childNodes[i].style.backgroundRepeat = "repeat-x";
	}    
}




function unhighlightRow( row )
{
	for( var i = 0; i < row.childNodes.length; i++ )
	{
		row.childNodes[i].style.background = "none";
	}          
}





function openPopup( mode )
{
    if ( mode == "add" )
    {
        UTL.getElem( "popup_AddBtn" ).style.display = "inline";     
    }
    else
    { 
        if ( !_selectedRow )
        {
            alert( "Please select a record" );
            return;            
        }
        else if ( _selectedRow.updAllowed.toLowerCase() != "yes" )
        {
        	alert( "The selected record cannot be updated" );
        	return;		
        }
        
        if ( mode == "modify" )        
        {
            UTL.getElem( "popup_ModifyBtn" ).style.display = "inline";         
        }
        else
        {
            UTL.getElem( "popup_DeleteBtn" ).style.display = "inline";      
        }             
    }
    
    _disableDiv.style.display = "block";

    _popupDiv.style.left = 65;
    _popupDiv.style.top= 80
    _popupDiv.style.display = "block";
    
    initPopupFields( mode );           
}




function closePopup()
{
    resetPopup();
    
    _disableDiv.style.display = "none";    
    _popupDiv.style.display = "none";
}



function getPopupDataMap( dataMap )
{
    if ( !dataMap ) dataMap = {};
        
    dataMap["acctNum"]           = UTL.getElem( "popup_AccountFld")._suggestDataObj["acctNum"];
    
    var fundFld = UTL.getElem( "popup_FundFld" );
    dataMap["fundCode"]          = fundFld._suggestDataObj["fund"];
    dataMap["classCode"]         = fundFld._suggestDataObj["class"];        
    
    dataMap["units"]             = UTL.getElem( "popup_UnitsFld").value;
    dataMap["effDate"]           = UTL.getElem( "popup_EffDateFld").value;
    
    return dataMap;
}




function initPopupFields( mode )
{
    if ( mode == "add" )
    {
        var accountFld = UTL.getElem( "popup_AccountFld" );    
        accountFld.disabled = false;
        accountFld.focus();
          
        var fundFld = UTL.getElem( "popup_FundFld" );
        fundFld.disabled = false;
    
        UTL.getElem( "popup_EffDateFld" ).disable( false );
        
        UTL.getElem( "popup_UnitsFld" ).disabled = false;  
    }
    else
    {
        var accountFld = UTL.getElem( "popup_AccountFld" );            
        accountFld.initialValue = _selectedRow.acctRowID;
        SuggestFieldManager.reInit( accountFld );
        accountFld.disabled = true;
          
        var fundFld = UTL.getElem( "popup_FundFld" );                
        fundFld.initialValue = _selectedRow.fundRowID;
        SuggestFieldManager.reInit( fundFld );
        fundFld.disabled = true;
    
        var effDateFld = UTL.getElem( "popup_EffDateFld" );
        effDateFld.disable( true );
        effDateFld.value = _selectedRow.effDate;
        
        var unitsFld = UTL.getElem( "popup_UnitsFld" );        
        unitsFld.value = _selectedRow.units;
        
        if ( mode == "modify" )
        {    
            unitsFld.disabled = false;
        }
        else
        {
            unitsFld.disabled = true;
        }  
    }
}


function resetPopup()
{
    var accountFld = UTL.getElem( "popup_AccountFld" );
    accountFld.value = "";
    accountFld._suggestDataObj = null
    
    var fundFld = UTL.getElem( "popup_FundFld" );
    fundFld.value = "";
    fundFld._suggestDataObj = null    
    
    UTL.getElem( "popup_EffDateFld" ).value = "";
    
    UTL.getElem( "popup_UnitsFld" ).value = "";
    
    UTL.getElem( "popup_AddBtn" ).style.display = "none";
    UTL.getElem( "popup_ModifyBtn" ).style.display = "none";
    UTL.getElem( "popup_DeleteBtn" ).style.display = "none";      
}



function addAccountBal()
{
    if ( validatePopupData() )
    {
        var dataMap = getPopupDataMap();
        dataMap = getSearchDataMap( dataMap );
        dataMap["action"]  = "add";
        dataMap["version"] = "";
        
        var xml = buildXML( dataMap );
        
        var paramMap = {}
        paramMap["cz"]                = _vCZ;
        paramMap["jobname"]           = "AccountBalanceOverride_Process";    
        paramMap["companyCode"]       = _companyCode;
        paramMap["ruserId"]           = _ruserId;
        paramMap["sessionId"]         = _sessionId;
        paramMap["envName"]           = _envName;
        paramMap["dateFormat"]        = _dateFormat;        
               
        var url = HTTP.buildURL( _vServletPath, paramMap );
        
        HTTP.postText( url, accountBalUpdate_callback, xml, true );
    }       
}



function modifyAccountBal()
{
	if ( validatePopupData() )
    {
        var dataMap = getPopupDataMap();
        dataMap = getSearchDataMap( dataMap );    
        dataMap["action"]  = "modify";
        dataMap["version"] = _selectedRow.version;
        
        var xml = buildXML( dataMap );
        
        var paramMap = {}
        paramMap["cz"]                = _vCZ;
        paramMap["jobname"]           = "AccountBalanceOverride_Process";    
        paramMap["companyCode"]       = _companyCode;
        paramMap["ruserId"]           = _ruserId;
        paramMap["sessionId"]         = _sessionId;
        paramMap["envName"]           = _envName;
        paramMap["dateFormat"]        = _dateFormat;        
               
        var url = HTTP.buildURL( _vServletPath, paramMap );
        
        HTTP.postText( url, accountBalUpdate_callback, xml );
    }	
}


function deleteAccountBal()
{
    if ( validatePopupData() )
    {
        var dataMap = getPopupDataMap();
        dataMap = getSearchDataMap( dataMap );
        dataMap["action"]  = "delete";
        dataMap["version"] = _selectedRow.version;
        
        var xml = buildXML( dataMap );
        
        var paramMap = {}
        paramMap["cz"]                = _vCZ;
        paramMap["jobname"]           = "AccountBalanceOverride_Process";    
        paramMap["companyCode"]       = _companyCode;
        paramMap["ruserId"]           = _ruserId;
        paramMap["sessionId"]         = _sessionId;
        paramMap["envName"]           = _envName;
        paramMap["dateFormat"]        = _dateFormat;        
               
        var url = HTTP.buildURL( _vServletPath, paramMap );
        
        HTTP.postText( url, accountBalUpdate_callback, xml );
    }       
}




function accountBalUpdate_callback( responseText )
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
    	var searchMatchDetailsNode = XML.getNode( "/responseContents/searchMatchDetails", responseXML );
    	if ( searchMatchDetailsNode )
    	{
    		setSearchMatchDetails( responseXML );
    	}
            
        var updatedSearchValuesNode = XML.getNode( "/responseContents/updatedSearchValues", responseXML );
        if ( updatedSearchValuesNode )
        {            
            updateSearchFields( responseXML );
        }       
    
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
                
        // clear the current inner html
        UTL.getElem( "accountBal_ListContentsDiv" ).innerHTML = "";
        // set the inner html to the html contents within updatedHTMLNode
        // note: the html contents are treated as xml within the xml dom
                       
        UTL.getElem( "accountBal_ListContentsDiv" ).innerHTML = updatedHTMLNode.firstChild.xml;
                
        closePopup();
        
        setResultsScrolling();                               
    }
}


function setSearchMatchDetails( responseXML )
{
	var searchMatchDetailsLbl = UTL.getElem( "searchMatchDetailsLbl" );
	var searchMatchDetailsFld = UTL.getElem( "searchMatchDetailsFld" );

	var acctNumNode = XML.getNode( "/responseContents/searchMatchDetails/acctNum", responseXML );
	if ( acctNumNode )
	{
		searchMatchDetailsLbl.innerHTML = "AcctNum/Name:"; 
		var acctNameNode = XML.getNode( "/responseContents/searchMatchDetails/acctName", responseXML );
		searchMatchDetailsFld.innerHTML = acctNumNode.firstChild.nodeValue + " - " + acctNameNode.firstChild.nodeValue;
		return;
	}
	
	var invIDCodeNode = XML.getNode( "/responseContents/searchMatchDetails/invIDCode", responseXML );
	if ( invIDCodeNode )
	{
		searchMatchDetailsLbl.innerHTML = "InvoiceID/Name:";
		var invNameNode = XML.getNode( "/responseContents/searchMatchDetails/invName", responseXML );
		searchMatchDetailsFld.innerHTML = invIDCodeNode.firstChild.nodeValue + " - " + invNameNode.firstChild.nodeValue;
		return;
	}
	
	var feeModelCodeNode = XML.getNode( "/responseContents/searchMatchDetails/feeModelCode", responseXML );
	if ( feeModelCodeNode )
	{
		searchMatchDetailsLbl.innerHTML = "Fee ID/MFR ID:";
		var feeModelDescNode = XML.getNode( "/responseContents/searchMatchDetails/feeModelDesc", responseXML );
		searchMatchDetailsFld.innerHTML = feeModelCodeNode.firstChild.nodeValue + " - " + feeModelDescNode.firstChild.nodeValue;
		return;
	}
	
	var holdEntCodeNode = XML.getNode( "/responseContents/searchMatchDetails/holdEntCode", responseXML );
	if ( holdEntCodeNode )
	{
		searchMatchDetailsLbl.innerHTML = "Holding Entity Code/Name:";
		var holdEntNameNode = XML.getNode( "/responseContents/searchMatchDetails/holdEntName", responseXML );
		searchMatchDetailsFld.innerHTML =  holdEntCodeNode.firstChild.nodeValue + " - " + holdEntNameNode.firstChild.nodeValue;
		return;
	}
}



function updateSearchFields( responseXML )
{
    var searchValueNode = XML.getNode( "/responseContents/updatedSearchValues/searchValue", responseXML );
    if ( searchValueNode && searchValueNode.firstChild )
    { 
        var searchValueFld = UTL.getElem( "search_ValueFld" );
        searchValueFld.value = searchValueNode.firstChild.nodeValue;                
    }
    
    var fundSearchValueNode = XML.getNode( "/responseContents/updatedSearchValues/fundSearchValue", responseXML );
    if ( fundSearchValueNode && fundSearchValueNode.firstChild )
    {
        var fundFld = UTL.getElem( "search_FundFld" );
        fundFld.initialValue = fundSearchValueNode.firstChild.nodeValue;
        SuggestFieldManager.reInit( fundFld );
    }
           
    var searchStartDateNode = XML.getNode( "/responseContents/updatedSearchValues/searchStartDate", responseXML );
    if ( searchStartDateNode && searchStartDateNode.firstChild)
    {
        UTL.getElem( "search_StartDateFld" ).value = searchStartDateNode.firstChild.nodeValue;
    }
  
    var searchEndDateNode = XML.getNode( "/responseContents/updatedSearchValues/searchEndDate", responseXML );
    if ( searchEndDateNode && searchEndDateNode.firstChild )
    {
        UTL.getElem( "search_StopDateFld" ).value = searchEndDateNode.firstChild.nodeValue;
    }
}



function validatePopupData()
{    
    var noError = true;
    if( !UTL.getElem("popup_AccountFld")._suggestDataObj )
    {
        noError = false;       
    }
    if( !UTL.getElem("popup_FundFld")._suggestDataObj )
    {
        noError = false;       
    }
    if( UTL.getElem("popup_EffDateFld").value == "" )
    {
        noError = false;       
    }
    if( UTL.getElem("popup_UnitsFld").value == "" )
    {
        noError = false;       
    }    
    if ( !noError )
    {
        alert( "Missing required field(s)" );
    }
    return noError; 
}


function alertSearchOptions()
{
	var msgString = "Search by one of:\n";
	msgString += "- Holding Entity Code\n";
	msgString += "- Account Number\n";
	msgString += "- Invoice ID\n";
	msgString += "- MFR ID\n";
	msgString += "- MF ID";
	alert( msgString ); 
}


function alertAccountSuggestOptions()
{
    var msgStr = "Search by one of: \n";
    msgStr += "- Account Number \n";
    msgStr += "- Partial Last Name \n";
    msgStr += "- Partial Last Name <space> Parital First Name \n";
    msgStr += "- Broker Account Number \n";
    msgStr += "- Broker Code <space> Broker Account Number \n";
    msgStr += "- SIN (no spaces or hyphens) \n";
    msgStr += "- Any Owner Identifier Number \n";
    alert( msgStr );
}


function alertFundSuggestOptions()
{
    var msgStr = "Search by one of: \n";
    msgStr += "- Fund Number \n";
    msgStr += "- Fund Code \n";
    msgStr += "- Fund Code <space> Class Code \n";
    msgStr += "- Fund Name \n";
    msgStr += "- Any Fund Identifier \n";    
    alert( msgStr );
}


function setResultsScrolling()
{	
	var resultsTable = UTL.getElem( "accountBal_ListContentsTable" );
	var resultsDiv = UTL.getElem( "accountBal_ListContentsDiv" );		
	// add scrolling if results are returned, and there are more than 10 records in table
	if ( resultsTable && resultsTable.lastChild.childNodes.length > 15 )
	{			
		// max viewable rows * rowHeight
		resultsDiv.style.height = (15 * 16);
		resultsDiv.style.overflowY = "scroll";			
	}
	else
	{
		resultsDiv.style.height = "100%";
		resultsDiv.style.overflowY = "auto";
	}
}


