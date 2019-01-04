var _selectedRowMap = {};
_selectedRowMap["aggAccount"]     = null;
_selectedRowMap["aggBroker"]      = null;
_selectedRowMap["aggSalesRep"]    = null;
_selectedRowMap["aggAsset"]       = null;
_selectedRowMap["feeID"]          = null;
_selectedRowMap["invoiceID"]      = null;
_selectedRowMap["account"]        = null;



function toggleHistoryDetailsDisplay( div )
{
	// show details
	if ( div.nextSibling.style.display == "none" )
	{
		div.nextSibling.style.display = "block";
		div.firstChild.src = _vURL + "images/minus.png";
	}
	else
	{
		div.nextSibling.style.display = "none";
		div.firstChild.src = _vURL + "images/plus.png";
	}
}                                  


function toggleDiv (divId)
{
	if (document.getElementById(divId).style.display == "none")
	{
		document.getElementById(divId).style.display = "block";
		_treeStructure[divId] = 1;
	}
	else
	{
		document.getElementById(divId).style.display = "none";
		_treeStructure[divId] = 0;
	}
}




function togglePlusMinus (img)
{
	if (img.nameProp == "plus.png")
		img.src = _vURL + "images/minus.png";
	else
		img.src = _vURL + "images/plus.png";
}




function showAllBaseDivs (div)
{		
	if(div.firstChild.nextSibling.firstChild.innerHTML == "Show All") // Show All
	{  
		document.getElementById("accountsDiv").style.display = "block";
		document.getElementById("accountsDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["accountsDiv"] = 1;
		
		document.getElementById("aggregationDiv").style.display = "block";
		document.getElementById("aggregationDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["aggregationDiv"] = 1;
		
		document.getElementById("invoiceIDDiv").style.display = "block";
		document.getElementById("invoiceIDDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["invoiceIDDiv"] = 1;
		
		document.getElementById("feeIDDiv").style.display = "block";
		document.getElementById("feeIDDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["feeIDDiv"] = 1;


		div.firstChild.nextSibling.firstChild.innerHTML = "Hide All";
	}
	
	else // Hide All
	{
		document.getElementById("accountsDiv").style.display = "none";
		document.getElementById("accountsDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["accountsDiv"] = 0;
		
		document.getElementById("aggregationDiv").style.display = "none";
		document.getElementById("aggregationDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["aggregationDiv"] = 0;
		
		document.getElementById("invoiceIDDiv").style.display = "none";
		document.getElementById("invoiceIDDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["invoiceIDDiv"] = 0;
		
		document.getElementById("feeIDDiv").style.display = "none";
		document.getElementById("feeIDDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["feeIDDiv"] = 0;
		
		div.firstChild.nextSibling.firstChild.innerHTML = "Show All";
	}
}




function showAllAggregation(div)
{
	if(div.firstChild.nextSibling.firstChild.innerHTML == "Show All") // Show All
	{  
		document.getElementById("aggAccount_ListDiv").style.display = "block";
		document.getElementById("aggAccount_ListDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["aggAccount_ListDiv"] = 1;
		
		document.getElementById("aggBroker_ListDiv").style.display = "block";
		document.getElementById("aggBroker_ListDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["aggBroker_ListDiv"] = 1;
		
		document.getElementById("aggSalesRep_ListDiv").style.display = "block";
		document.getElementById("aggSalesRep_ListDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["aggSalesRep_ListDiv"] = 1;
		
		document.getElementById("aggAsset_ListDiv").style.display = "block";
		document.getElementById("aggAsset_ListDivToggle").src = _vURL + "images/minus.png";
		_treeStructure["aggAsset_ListDiv"] = 1;

		div.firstChild.nextSibling.firstChild.innerHTML = "Hide All";
	}
	
	else // Hide All
	{
		document.getElementById("aggAccount_ListDiv").style.display = "none";
		document.getElementById("aggAccount_ListDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["aggAccount_ListDiv"] = 0;
		
		document.getElementById("aggBroker_ListDiv").style.display = "none";
		document.getElementById("aggBroker_ListDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["aggBroker_ListDiv"] = 0;
		
		document.getElementById("aggSalesRep_ListDiv").style.display = "none";
		document.getElementById("aggSalesRep_ListDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["aggSalesRep_ListDiv"] = 0;
		
		document.getElementById("aggAsset_ListDiv").style.display = "none";
		document.getElementById("aggAsset_ListDivToggle").src = _vURL + "images/plus.png";
		_treeStructure["aggAsset_ListDiv"] = 0;
		
		div.firstChild.nextSibling.firstChild.innerHTML = "Show All";
	}
}




function launchFeeIDScreen( feeModelCode )
{	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_FeeIDMain";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    paramMap["holdingEntityID"]   = _holdingEntityID;
    
    if( feeModelCode )
    {
        paramMap["feeModelCode"]  = feeModelCode;        
    }  
    
    var url = HTTP.buildURL( _vServletPath, paramMap );

	var feeIDFrame = UTL.getElem( "feeID_Frame" );	
	
	// store the default src
	feeIDFrame.defaultSrc = feeIDFrame.src;
	// set new src
	feeIDFrame.src = url;
	
	UTL.getElem( "disableDiv" ).style.display = "block";
	
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
	    UTL.getElem( "refreshIndicatorDiv" ).style.display = "block";	    
	    window.navigate( document.URL );
	}
	else
	{
		UTL.getElem( "disableDiv" ).style.display = "none";
	}	
	
	// restore the default src
	feeIDFrame.src = feeIDFrame.defaultSrc;
}




function launchAssetValuesScreen()
{
	if (_selectedRowMap["aggAsset"] == null)
	{
		alert("Please select an asset")
		return;
	}
    var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_AssetValues";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    paramMap["assetCode"]         = _selectedRowMap["aggAsset"].assetCode;
    paramMap["random"]            = Math.random();    
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
        
	var assetValFrame = UTL.getElem( "assetValues_Frame" );
		
	// store the default src
	assetValFrame.defaultSrc = assetValFrame.src;
	// set new src	
	assetValFrame.src = url;
	
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	assetValFrame.style.display = "block";	
}




function closeAssetValuesScreen()
{
    var assetValFrame = UTL.getElem( "assetValues_Frame" );
    assetValFrame.src = "";
    
	assetValFrame.style.display = "none";
	
	UTL.getElem( "disableDiv" ).style.display = "none";
	
	// restore default iframe src
	assetValFrame.src = assetValFrame.defaultSrc;		
}




function launchInvoiceIDScreen( invIDCode, billInstrID)
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_InvoiceIDMain";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    paramMap["holdingEntityID"]   = _holdingEntityID;
    
    if( invIDCode )
    {
        paramMap["invIDCode"]     = invIDCode;
        paramMap["billInstrID"]   = billInstrID;
    }  
    
    var url = HTTP.buildURL( _vServletPath, paramMap );

	var invFrame = UTL.getElem( "invoiceID_Frame" );	
	
	// store the default src
	invFrame.defaultSrc = invFrame.src;
	// set new src
	invFrame.src = url;
	
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	invFrame.style.display = "block";
}



function closeInvoiceIDScreen( refresh )
{
    var invFrame = UTL.getElem( "invoiceID_Frame" );	
	
	invFrame.src = "";
	
	invFrame.style.display = "none";
	
	if ( refresh )
	{
	    _upatedOccured = true;	    
	    UTL.getElem( "refreshIndicatorDiv" ).style.display = "block";		    
	    window.navigate( document.URL );
	}
	else
	{
		UTL.getElem( "disableDiv" ).style.display = "none";
	}
	
	
	// restore the default src
	invFrame.src = invFrame.defaultSrc;
}


// this gets called from the C++ code, when the FeeID screen is closed
// HoldingEntity screen will always refresh, until Paul can figure out how to pass a dirty flag
function doRefresh()
{
    window.history.go(0);
}





function buildModifiableDivs()
{
	_modifiableDivs[0] = "aggregationDiv";
	_modifiableDivs[1] = "feeIDDiv";
	_modifiableDivs[2] = "invoiceIDDiv";
	_modifiableDivs[3] = "accountsDiv";
	_modifiableDivs[4] = "aggAccount_ListDiv";
	_modifiableDivs[5] = "aggBroker_ListDiv";
	_modifiableDivs[6] = "aggSalesRep_ListDiv";
	_modifiableDivs[7] = "aggAsset_ListDiv";
}




function handleLoadCookie()
{	
    for (var i = 0; i < _modifiableDivs.length; i++)
    {	 
    	//alert(_modifiableDivs[i] + ", " + _structure.get (_modifiableDivs[i]));   	
    	if (_structure.get (_modifiableDivs[i]) == "yes")
    	{    		
    		_treeStructure[_modifiableDivs[i]] = 1;
    		document.getElementById(_modifiableDivs[i]).style.display = "block";	
    		document.getElementById(_modifiableDivs[i] + "Toggle").src = _vURL + "images/minus.png";
    	}
    }
}



    
function handleSaveCookie()
{	
	for( var i = 0; i < _modifiableDivs.length; i++ )
  	{ 
		if (_treeStructure[_modifiableDivs[i]] == undefined)
		{
			_structure.add (_modifiableDivs[i], "no");
		}
		else if(_treeStructure[_modifiableDivs[i]] == 1)
    	{
			_structure.add (_modifiableDivs[i], "yes");
    	}
  		else
  		{
  			_structure.add (_modifiableDivs[i], "no");
  		}
	}
	
  	_structure.store(20);
}




function openPopup( popupType, addMode )
{
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	var popupDiv = UTL.getElem( popupType + "_PopupDiv" );
	popupDiv.style.display = "block";	
	
	switch( popupType )
    {
        case "aggAccount":	        
        {	            
            initAggAccountPopup( addMode );
            break;
        }
        case "aggBroker":
        {
            initAggBrokerPopup( addMode );
            break;
        }
        case "aggSalesRep":
        {
            initAggSalesRepPopup( addMode );
            break;
        }	      
        case "aggAsset":
        {
            initAggAssetPopup( addMode );
            break;
        }
        case "account":
        {            
            initAccountPopup( addMode );
            break;
        }        
    }	      	   
}




function closePopup( popupType )
{
    UTL.getElem( popupType + "_PopupDiv" ).style.display = "none";
    UTL.getElem( "disableDiv" ).style.display = "none";	
}




function clearAnySelectedRows()
{
    for( var i in _selectedRowMap )
    {
        if( _selectedRowMap[i] )
        {
             unselectRow( i );
        }
    }
}




function unselectRow( rowType )
{
    unhighlightRow( _selectedRowMap[rowType] );
    _selectedRowMap[rowType] = null;
}




function selectRow( row, rowType )
{    
    clearAnySelectedRows();
    
    highlightRow( row );
    _selectedRowMap[rowType] = row;   
}




function highlightRow( row )
{
    row.style.background = "url(" + _vURL + "images/rowHighlight.png)";
    row.style.backgroundRepeat = "repeat-x";    
}




function unhighlightRow( row )
{
    row.style.background = "none";       
}




function getAccountSearchURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]              = _vCZ;
    paramMap["jobname"]         = "General_AccountSearch";
    paramMap["companyCode"]     = _companyCode;
    paramMap["ruserId"]         = _ruserId;    
    paramMap["sessionId"]       = _sessionId;
    paramMap["envName"]       	= _envName;
    paramMap["dateFormat"] 	    = _dateFormat;
    
    if ( nextRecNum )
    {
        paramMap["startRecordNum"] = nextRecNum;    
    }
    paramMap["searchData"] = searchStr;
     
    return HTTP.buildURL( _vServletPath, paramMap );    
}




function getBrokerSearchURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]              = _vCZ;
    paramMap["jobname"]         = "General_BrokerSuggest";
    paramMap["companyCode"]     = _companyCode;
    paramMap["ruserId"]         = _ruserId;    
    paramMap["sessionId"]       = _sessionId;
    paramMap["envName"]       	= _envName;
    paramMap["dateFormat"] 	    = _dateFormat;
    
    if ( nextRecNum )
    {
        paramMap["startRecordNum"] = nextRecNum;    
    }
    paramMap["searchData"] = searchStr;
     
    return HTTP.buildURL( _vServletPath, paramMap );
}




function getSalesRepSearchURL( searchStr, nextRecNum)
{
    var paramMap = {};
    paramMap["cz"]              = _vCZ;
    paramMap["jobname"]         = "General_SalesRepSuggest";
    paramMap["companyCode"]     = _companyCode;
    paramMap["ruserId"]         = _ruserId;    
    paramMap["sessionId"]       = _sessionId;
    paramMap["envName"]       	= _envName;
    paramMap["dateFormat"] 	    = _dateFormat;
    
    if ( nextRecNum )
    {
        paramMap["startRecordNum"] = nextRecNum;    
    }
    paramMap["searchData"] = searchStr;
    paramMap["agencyCode"] = ( UTL.getElem("aggSalesRep_BrokerFld")._suggestDataObj ? UTL.getElem("aggSalesRep_BrokerFld")._suggestDataObj["agencyCode"] : "" );
     
    return HTTP.buildURL( _vServletPath, paramMap );
}




function buildXML( updateType, action, xmlFldValueMap )
{
    var xml = "";
    xml += XML.createNodeStr( "action", action );
    
    for( var i in xmlFldValueMap )
    {
        xml += XML.createNodeStr( i, xmlFldValueMap[i] );
    }
    
    return XML.createNodeStr( "Data", XML.createNodeStr( updateType, xml ) );
}




function postUpdateRequest( popupType, xml, popupNotUsed )
{
    var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_HoldingEntityProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["holdingEntityID"]   = _holdingEntityID;    
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
    
    HTTP.postText( url, function( responseText ){ postUpdateRequest_callback( responseText, popupType, popupNotUsed ); }, xml, true );    
}




function postUpdateRequest_callback( responseText, popupType, popupNotUsed )
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
        _updateOccured = true;
        
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
                
        // clear the current inner html
        UTL.getElem( popupType + "_ListContentsDiv" ).innerHTML = "";
        // set the inner html to the html contents within updatedHTMLNode
        // note: the html contents are treated as xml within the xml dom
                
        UTL.getElem( popupType + "_ListContentsDiv" ).innerHTML = updatedHTMLNode.firstChild.xml;
        
        if( !popupNotUsed )
        {
            closePopup( popupType );
        }        
        
        if ( popupType == "account" )
        {        	
            IFDSTableManager.tableMap["accounts_ListTable"].init( UTL.getElem( "accounts_ListTable" ) );
            setAccountsScrolling();
        }
    } 
}



function deleteAgg( aggType )
{    
    if ( _selectedRowMap[aggType] )
    {
        if ( confirm( "Are you sure you want to delete the selected record?") )
        {
            var xml = "";
            switch( aggType )
            {
                case "aggAccount":
                {
                    var dataMap = {};
                    dataMap["acctNum"]   = _selectedRowMap["aggAccount"].acctNum;
                    dataMap["feeAggrID"] = _selectedRowMap["aggAccount"].feeAggrID;
                    dataMap["version"]   = _selectedRowMap["aggAccount"].version;                    
                    xml = buildXML( "UpdAggrAccount", "delete", dataMap );
                    break;
                }
                case "aggBroker":
                {
                    var dataMap = {};
                    dataMap["brkCode"]   = _selectedRowMap["aggBroker"].brkcode;
                    dataMap["feeAggrID"] = _selectedRowMap["aggBroker"].feeAggrID;                    
                    dataMap["version"]   = _selectedRowMap["aggBroker"].version;
                    xml = buildXML( "UpdAggrBroker", "delete", dataMap );
                    break;
                }
                case "aggSalesRep":
                {
                    var dataMap = {};
                    dataMap["brkCode"]   = _selectedRowMap["aggSalesRep"].brkCode;
                    dataMap["feeAggrID"] = _selectedRowMap["aggSalesRep"].feeAggrID;
                    dataMap["repCode"]   = _selectedRowMap["aggSalesRep"].repCode;
                    dataMap["version"]   = _selectedRowMap["aggSalesRep"].version;
                    xml = buildXML( "UpdAggrSalesRep", "delete", dataMap );
                    break;
                }
                case "aggAsset":
                {           
                    var dataMap = {};
                    dataMap["assetCode"] = _selectedRowMap["aggAsset"].assetCode;
                    dataMap["feeAggrID"] = _selectedRowMap["aggAsset"].feeAggrID;
                    dataMap["version"]   = _selectedRowMap["aggAsset"].version;                                        
                    xml = buildXML( "UpdAggrAsset", "delete", dataMap );
                    break;     
                }
            }                       
            postUpdateRequest( aggType, xml, true );            
        }
    }
    else
    {
        alert( "Please select a record to delete" );
    }
}



function alertErrorMsg( errorSummary, errorDetailsArray )
{
	var msg = errorSummary + "\n";
	for ( var i = 0; i < errorDetailsArray.length; i++ )
	{
		msg += "\n- " + errorDetailsArray[i];		
	}
	
	alert( msg );
}
	


function initAggAccountPopup( addMode )
{   
	if ( addMode )
	{
	    var accountFld = UTL.getElem( "aggAccount_AccountFld" );
	    accountFld.value = "";
	    accountFld._suggestDataObj = null;
	    accountFld.disabled = false;
	    	    
	    UTL.getElem( "aggAccount_EffDateFld" ).value = "";
	    UTL.getElem( "aggAccount_StopDateFld" ).value = "";
	    UTL.getElem( "aggAccount_UpdTypeFld" ).value = "add";
	    UTL.getElem( "aggAccount_FeeAggrIdFld" ).value = "";
	    UTL.getElem( "aggAccount_VersionFld" ).value = "";
	    
	        
    	accountFld.focus();
	}
	else
	{
		var accountFld = UTL.getElem( "aggAccount_AccountFld" );                               
        accountFld.initialValue = _selectedRowMap["aggAccount"].acctRowID;
        SuggestFieldManager.reInit( accountFld );
        accountFld.disabled = true;
        
        UTL.getElem( "aggAccount_EffDateFld" ).value = _selectedRowMap["aggAccount"].effDate;
	    UTL.getElem( "aggAccount_StopDateFld" ).value = _selectedRowMap["aggAccount"].stopDate;
	    UTL.getElem( "aggAccount_UpdTypeFld" ).value = "modify";
	    UTL.getElem( "aggAccount_FeeAggrIdFld" ).value = _selectedRowMap["aggAccount"].feeAggrID;
	    UTL.getElem( "aggAccount_VersionFld" ).value = _selectedRowMap["aggAccount"].version;	    
	    
	    UTL.getElem( "aggAccount_EffDateFld" ).focus();     
	}  
}



function getAggAccountData()
{
    var xmlFldValueMap = {};    
    var errorMsgArray = [];
    
    if ( UTL.getElem( "aggAccount_AccountFld" )._suggestDataObj )
    {
    	xmlFldValueMap["acctNum"] = UTL.getElem( "aggAccount_AccountFld" )._suggestDataObj["acctNum"];    	
    }
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Account not entered";
    }
    
    if ( UTL.getElem( "aggAccount_EffDateFld" ).value != "" )
    {
    	xmlFldValueMap["effDate"] = UTL.getElem( "aggAccount_EffDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Effective Date value not entered";
    }
    
    if ( UTL.getElem( "aggAccount_StopDateFld" ).value != "" )
    {
    	xmlFldValueMap["stopDate"] = UTL.getElem( "aggAccount_StopDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Stop Date value not entered";
    }
    
    xmlFldValueMap["feeAggrID"] = UTL.getElem( "aggAccount_FeeAggrIdFld" ).value;
    xmlFldValueMap["version"] = UTL.getElem( "aggAccount_VersionFld" ).value;
	 
	if ( errorMsgArray.length > 0 )
	{
		alertErrorMsg( "Aggregated Account record could not be submitted", errorMsgArray );
		return null;
	}
	else
	{       
    	return xmlFldValueMap;
	}
}



function saveAggAccount()
{
	var aggAccountData = getAggAccountData();
	if ( aggAccountData )	     
    {
    	var updType = UTL.getElem( "aggAccount_UpdTypeFld" ).value;
        var saveAggAccountXML = buildXML( "UpdAggrAccount", updType, aggAccountData )
        //prompt( "", saveAggAccountXML );        
        postUpdateRequest( "aggAccount", saveAggAccountXML );           
    }        
}



function initAggBrokerPopup( addMode )
{
	if ( addMode )
	{    
	    var brokerFld = UTL.getElem( "aggBroker_BrokerFld" );
	    brokerFld.value = "";
	    brokerFld._suggestDataObj = null;
	    brokerFld.disabled = false;
	    
	    UTL.getElem( "aggBroker_EffDateFld" ).value = "";
	    UTL.getElem( "aggBroker_StopDateFld" ).value = "";
	    UTL.getElem( "aggBroker_UpdTypeFld" ).value = "add";
	    UTL.getElem( "aggBroker_FeeAggrIdFld" ).value = "";
	    UTL.getElem( "aggBroker_VersionFld" ).value = "";
	    
	    brokerFld.focus();
	}
	else
	{
		var brokerFld = UTL.getElem( "aggBroker_BrokerFld" );                               
        brokerFld.initialValue = _selectedRowMap["aggBroker"].brkcode;
        SuggestFieldManager.reInit( brokerFld );
        brokerFld.disabled = true;
        
        UTL.getElem( "aggBroker_EffDateFld" ).value = _selectedRowMap["aggBroker"].effDate;
	    UTL.getElem( "aggBroker_StopDateFld" ).value = _selectedRowMap["aggBroker"].stopDate;
	    UTL.getElem( "aggBroker_UpdTypeFld" ).value = "modify";
	    UTL.getElem( "aggBroker_FeeAggrIdFld" ).value = _selectedRowMap["aggBroker"].feeAggrID;
	    UTL.getElem( "aggBroker_VersionFld" ).value = _selectedRowMap["aggBroker"].version;
	    
	    UTL.getElem( "aggBroker_EffDateFld" ).focus;        
	}
}



function getAggBrokerData()
{
    var xmlFldValueMap = {};    
    var errorMsgArray = [];
    
    if ( UTL.getElem( "aggBroker_BrokerFld" )._suggestDataObj )
    {
    	xmlFldValueMap["brkCode"] = UTL.getElem( "aggBroker_BrokerFld" )._suggestDataObj["agencyCode"];    	
    }
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Broker not entered";
    }
    
    if ( UTL.getElem( "aggBroker_EffDateFld" ).value != "" )
    {
    	xmlFldValueMap["effDate"] = UTL.getElem( "aggBroker_EffDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Effective Date value not entered";
    }
    
    if ( UTL.getElem( "aggBroker_StopDateFld" ).value != "" )
    {
    	xmlFldValueMap["stopDate"] = UTL.getElem( "aggBroker_StopDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Stop Date value not entered";
    }
    
    xmlFldValueMap["feeAggrID"] = UTL.getElem( "aggBroker_FeeAggrIdFld" ).value;
    xmlFldValueMap["version"] = UTL.getElem( "aggBroker_VersionFld" ).value;
	 
	if ( errorMsgArray.length > 0 )
	{
		alertErrorMsg( "Aggregated Broker record could not be submitted", errorMsgArray );
		return null;
	}
	else
	{       
    	return xmlFldValueMap;
	}
}



function saveAggBroker()
{	    
   	var aggBrokerData = getAggBrokerData();
	if ( aggBrokerData )	     
    {
    	var updType = UTL.getElem( "aggBroker_UpdTypeFld" ).value
        var saveAggBrokerXML = buildXML( "UpdAggrBroker", updType, aggBrokerData )
        //prompt( "", saveAggBrokerXML );     
        postUpdateRequest( "aggBroker", saveAggBrokerXML );           
    }        
}



function initAggSalesRepPopup( addMode )
{
	if ( addMode )
	{
	    var brokerFld = UTL.getElem( "aggSalesRep_BrokerFld" );
	    brokerFld.value = "";
	    brokerFld._suggestDataObj = null;
	    brokerFld.disabled = false;
	    
	    var salesRepFld = UTL.getElem( "aggSalesRep_SalesRepFld" );
	    salesRepFld.value = "";
	    salesRepFld._suggestDataObj = null;
	    salesRepFld.disabled = false;
	    
	    UTL.getElem( "aggSalesRep_EffDateFld" ).value = "";
	    UTL.getElem( "aggSalesRep_StopDateFld" ).value = "";
	    UTL.getElem( "aggSalesRep_UpdTypeFld" ).value = "add";
	    UTL.getElem( "aggSalesRep_FeeAggrIdFld" ).value = "";
	    UTL.getElem( "aggSalesRep_VersionFld" ).value = "";
	    
	    brokerFld.focus();
	}    
    else
	{
		var brokerFld = UTL.getElem( "aggSalesRep_BrokerFld" );                               
        brokerFld.initialValue = _selectedRowMap["aggSalesRep"].brkCode;
        SuggestFieldManager.reInit( brokerFld );
        brokerFld.disabled = true;
        
        var salesRepFld = UTL.getElem( "aggSalesRep_SalesRepFld" );                               
        salesRepFld.initialValue = _selectedRowMap["aggSalesRep"].repCode;
        SuggestFieldManager.reInit( salesRepFld );
        salesRepFld.disabled = true;
        
        UTL.getElem( "aggSalesRep_EffDateFld" ).value = _selectedRowMap["aggSalesRep"].effDate;
	    UTL.getElem( "aggSalesRep_StopDateFld" ).value = _selectedRowMap["aggSalesRep"].stopDate;
	    UTL.getElem( "aggSalesRep_UpdTypeFld" ).value = "modify";
	    UTL.getElem( "aggSalesRep_FeeAggrIdFld" ).value = _selectedRowMap["aggSalesRep"].feeAggrID;
	    UTL.getElem( "aggSalesRep_VersionFld" ).value = _selectedRowMap["aggSalesRep"].version;
	    
	    UTL.getElem( "aggSalesRep_EffDateFld" ).focus;        
	}    
}

  
  
function getAggSalesRepData()
{
    var xmlFldValueMap = {};    
    var errorMsgArray = [];
    
    if ( UTL.getElem( "aggSalesRep_BrokerFld" )._suggestDataObj )
    {
    	xmlFldValueMap["brkCode"] = UTL.getElem( "aggSalesRep_BrokerFld" )._suggestDataObj["agencyCode"];    	
    }
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Broker not entered";
    }
    
    if ( UTL.getElem( "aggSalesRep_SalesRepFld" )._suggestDataObj )
    {
    	xmlFldValueMap["repCode"] = UTL.getElem( "aggSalesRep_SalesRepFld" )._suggestDataObj["agentCode"];    	
    }
    else
    {
    	errorMsgArray[errorMsgArray.length] = "SalesRep not entered";
    }
    
    if ( UTL.getElem( "aggSalesRep_EffDateFld" ).value != "" )
    {
    	xmlFldValueMap["effDate"] = UTL.getElem( "aggSalesRep_EffDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Effective Date value not entered";
    }
    
    if ( UTL.getElem( "aggSalesRep_StopDateFld" ).value != "" )
    {
    	xmlFldValueMap["stopDate"] = UTL.getElem( "aggSalesRep_StopDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Stop Date value not entered";
    }
    
    xmlFldValueMap["feeAggrID"] = UTL.getElem( "aggSalesRep_FeeAggrIdFld" ).value;
    xmlFldValueMap["version"] = UTL.getElem( "aggSalesRep_VersionFld" ).value;
	 
	if ( errorMsgArray.length > 0 )
	{
		alertErrorMsg( "Aggregated SalesRep record could not be submitted", errorMsgArray );
		return null;
	}
	else
	{       
    	return xmlFldValueMap;
	}
}  



function saveAggSalesRep()
{	
    var addAggSalesRepData = getAggSalesRepData();
	if ( addAggSalesRepData )	     
    {
    	var updType = UTL.getElem( "aggSalesRep_UpdTypeFld" ).value
        var saveAggSalesRepXML = buildXML( "UpdAggrSalesRep", updType, addAggSalesRepData )
        //prompt( "", saveAggSalesRepXML );   
        postUpdateRequest( "aggSalesRep", saveAggSalesRepXML );           
    }        
}



function initAggAssetPopup( addMode )
{
	if ( addMode )
	{
   		UTL.getElem( "aggAsset_AssetFld" ).selectedIndex = 0;
   		UTL.getElem( "aggAsset_AssetFld" ).disabled = false;   
		UTL.getElem( "aggAsset_EffDateFld" ).value = "";
		UTL.getElem( "aggAsset_StopDateFld" ).value = "";
		UTL.getElem( "aggAsset_UpdTypeFld" ).value = "add";
		UTL.getElem( "aggAsset_FeeAggrIdFld" ).value = "";
		UTL.getElem( "aggAsset_VersionFld" ).value = "";
			
		UTL.getElem( "aggAsset_AssetFld" ).focus;
	}
	else
	{
		UTL.getElem( "aggAsset_AssetFld" ).value =  _selectedRowMap["aggAsset"].assetCode;
		UTL.getElem( "aggAsset_AssetFld" ).disabled = true; 
		UTL.getElem( "aggAsset_EffDateFld" ).value = _selectedRowMap["aggAsset"].effDate;
		UTL.getElem( "aggAsset_StopDateFld" ).value = _selectedRowMap["aggAsset"].stopDate;
		UTL.getElem( "aggAsset_UpdTypeFld" ).value = "modify";
		UTL.getElem( "aggAsset_FeeAggrIdFld" ).value = _selectedRowMap["aggAsset"].feeAggrID;
		UTL.getElem( "aggAsset_VersionFld" ).value = _selectedRowMap["aggAsset"].version;
			
		UTL.getElem( "aggAsset_StopDateFld" ).focus;		
	}       
}



function getAggAssetData()
{
    var xmlFldValueMap = {};    
    var errorMsgArray = [];
    
    if ( UTL.getElem( "aggAsset_AssetFld" ).value )
    {
    	//xmlFldValueMap["assetCode"] = UTL.getElem( "aggAsset_AssetFld" ).options[UTL.getElem( "aggAsset_AssetFld" ).selectedIndex].value;
    	xmlFldValueMap["assetCode"] = UTL.getElem( "aggAsset_AssetFld" ).value;    	
    }
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Asset not entered";
    }
    
    if ( UTL.getElem( "aggAsset_EffDateFld" ).value != "" )
    {
    	xmlFldValueMap["effDate"] = UTL.getElem( "aggAsset_EffDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Effective Date value not entered";
    }
    
    if ( UTL.getElem( "aggAsset_StopDateFld" ).value != "" )
    {
    	xmlFldValueMap["stopDate"] = UTL.getElem( "aggAsset_StopDateFld" ).value;	
    }    
    else
    {
    	errorMsgArray[errorMsgArray.length] = "Stop Date value not entered";
    }
    
    xmlFldValueMap["feeAggrID"] = UTL.getElem( "aggAsset_FeeAggrIdFld" ).value;
    xmlFldValueMap["version"] = UTL.getElem( "aggAsset_VersionFld" ).value;
	 
	if ( errorMsgArray.length > 0 )
	{
		alertErrorMsg( "Aggregated Asset record could not be submitted", errorMsgArray );
		return null;
	}
	else
	{       
    	return xmlFldValueMap;
	}
}



function saveAggAsset()
{	   
    var addAggAssetData = getAggAssetData();
	if ( addAggAssetData )	     
    {
    	var updType = UTL.getElem( "aggAsset_UpdTypeFld" ).value;
        var saveAggAssetXML = buildXML( "UpdAggrAsset", updType, addAggAssetData )
        //prompt( "", saveAggAssetXML ); 
        postUpdateRequest( "aggAsset", saveAggAssetXML );           
    }        
}



function initAccountPopup( addMode )
{
    // remove handlers that may have been added
    EvtHandler.remove( UTL.getElem( "account_SaveBtn" ), "click", updateAccount );
    EvtHandler.remove( UTL.getElem( "account_SaveBtn" ), "click", addAccount );    


    var feeIDFld = UTL.getElem( "account_FeeIDFld" );
    // populate the feeIDFld dropdown
    // first clear any existing options
    var existingOptions = feeIDFld.options;
    for( var i = existingOptions.length - 1; i >= 0; i-- )
    {
        feeIDFld.remove( i );
    }
    
    // now populate dropdown with items from feeIDList         
    // (dom structure: table/tbody/rows)
    if ( UTL.getElem("feeID_ListTable") )
    {
	    var feeIDListRows = UTL.getElem("feeID_ListTable").firstChild.childNodes;        
	    for ( var i = 0; i < feeIDListRows.length; i++ )
	    {
	        var opt = document.createElement( "option" );
	        opt.value = feeIDListRows[i].feeModelCode;
	        opt.text = feeIDListRows[i].feeModelCode;
	        feeIDFld.add( opt );
	    }
	    feeIDFld.selectedIndex = -1;    
	}
	            
    var invoiceIDFld = UTL.getElem( "account_InvoiceIDFld" );
    // populate the invoiceIDFld dropdown
    // first clear any existing options
    var existingOptions = invoiceIDFld.options;
    for( var i = existingOptions.length - 1; i >= 0; i-- )
    {
        invoiceIDFld.remove( i );
    }
    
    // now populate dropdown with items from feeIDList         
    // (dom structure: table/tbody/rows)
    if ( UTL.getElem( "invoiceID_ListTable" ) )
    {       
	    var invoiceIDListRows = UTL.getElem("invoiceID_ListTable").firstChild.childNodes;        
	    for ( var i = 0; i < invoiceIDListRows.length; i++ )
	    {
	        // we only include invIDs that have stop date = 31/12/9999 (dateFormat dependent)
	        var validStopDate = ( _dateFormat == "dmy" ) ? "31/12/9999" : "12/31/9999";          
	        if ( invoiceIDListRows[i].stopDate.indexOf( validStopDate ) != -1
	        		&& invoiceIDListRows[i].gbcd != "Bad" )
	        {
	            var opt = document.createElement( "option" );
	            opt.value = invoiceIDListRows[i].invIDCode;
	            opt.text = invoiceIDListRows[i].invIDCode;
	            invoiceIDFld.add( opt );
	        }        
	    }
	    invoiceIDFld.selectedIndex = -1;
	}


    if ( addMode )
    {
        var accountFld = UTL.getElem( "account_AccountFld" )
        accountFld._suggestDataObj = null;
        accountFld.value = "";
        accountFld.disabled = false;
        
        var effDateFld = UTL.getElem( "account_EffDateFld" );
        effDateFld.value = "";
        effDateFld.disable( false );        
        
        var stopDateFld = UTL.getElem( "account_StopDateFld" );
        stopDateFld.value = "";
        stopDateFld.disable( false );
        
        feeIDFld.selectedIndex = -1;
        feeIDFld.disabled = false;
        
        invoiceIDFld.selectedIndex = -1;
        invoiceIDFld.disabled = false;        
        
        UTL.getElem( "actionsDiv" ).style.visibility = "hidden";
                
        EvtHandler.add( UTL.getElem( "account_SaveBtn" ), "click", addAccount );    
    }    
    else
    {   
    	UTL.getElem( "accountActionSelect" ).selectedIndex = -1; 
        UTL.getElem( "actionsDiv" ).style.visibility = "visible";
        
        UTL.getElem( "account_VersionFld" ).value = _selectedRowMap["account"].version;
        UTL.getElem( "account_ShrAcctIDFld" ).value = _selectedRowMap["account"].shrAcctID;
        UTL.getElem( "account_GBCDFld" ).value = _selectedRowMap["account"].gbcd;
        
        var accountFld = UTL.getElem( "account_AccountFld" );                               
        accountFld.initialValue = _selectedRowMap["account"].acctRowID;
        SuggestFieldManager.reInit( accountFld );
        accountFld.disabled = true;
        
        var effDateFld = UTL.getElem( "account_EffDateFld" );
        effDateFld.value = _selectedRowMap["account"].effDate;
        effDateFld.disable( true );
        
        var stopDateFld = UTL.getElem( "account_StopDateFld" );
        stopDateFld.value = _selectedRowMap["account"].stopDate;
        stopDateFld.disable( true );              
        
        for ( var i = 0; i < feeIDFld.options.length; i++ )
        {
            if ( _selectedRowMap["account"].feeModelCode == feeIDFld.options[i].value )
            {
                feeIDFld.selectedIndex = i;
            }
        }
        feeIDFld.disabled = true;        
        
        for ( var i = 0; i < invoiceIDFld.options.length; i++ )
        {                       
            if ( _selectedRowMap["account"].billInstrCode == invoiceIDFld.options[i].value )
            {
                invoiceIDFld.selectedIndex = i;
            }
        }
        invoiceIDFld.disabled = true;
                       
        //EvtHandler.add( UTL.getElem( "account_SaveBtn" ), "click", updateAccount );           
    }
}




function getAccountData( addMode )
{
    var xmlFldValueMap = {};
    xmlFldValueMap["acctNum"]     		= ( UTL.getElem( "account_AccountFld" )._suggestDataObj ? UTL.getElem( "account_AccountFld" )._suggestDataObj["acctNum"] : "" );
    xmlFldValueMap["effDate"]	  		= UTL.getElem( "account_EffDateFld" ).value;
    xmlFldValueMap["stopDate"]	  		= UTL.getElem( "account_StopDateFld" ).value;
    xmlFldValueMap["feeModelCode"]   	= UTL.getElem( "account_FeeIDFld" ).value;
    xmlFldValueMap["billInstrCode"]   	= UTL.getElem( "account_InvoiceIDFld" ).value;
    
    if( !addMode )
    {
        xmlFldValueMap["version"]      = UTL.getElem( "account_VersionFld" ).value;
        xmlFldValueMap["shrAcctID"] = UTL.getElem( "account_ShrAcctIDFld" ).value;
    } 
    
    return xmlFldValueMap;
}




function addAccount()
{
    var addAccountXML = buildXML( "UpdMFAccount", "add", getAccountData( true ) )
    //alert( addAccountXML );              
    postUpdateRequest( "account", addAccountXML );               
}



function updateAccount()
{
    if( UTL.getElem( "accountActionSelect" ).selectedIndex == -1 )
    {
        alert( "Please select an action to perform" );
    }
    else
    {
        var accountFld = UTL.getElem( "account_AccountFld" );        
        var effDateFld = UTL.getElem( "account_EffDateFld" );
        var stopDateFld = UTL.getElem( "account_StopDateFld" );
        var feeIDFld = 	UTL.getElem( "account_FeeIDFld" );
        var invIDFld = 	UTL.getElem( "account_InvoiceIDFld" );

        if ( accountFld._suggestDataObj != null && feeIDFld.selectedIndex != -1 && invIDFld.selectedIndex != -1 && effDateFld.value != "" )
        {
            var actionSelected = UTL.getElem( "accountActionSelect" ).options[UTL.getElem( "accountActionSelect" ).selectedIndex].value;            
            var updAccountXML = buildXML( "UpdMFAccount", actionSelected, getAccountData() );
            //alert( updAccountXML );
            postUpdateRequest( "account", updAccountXML );
        }        
    }           
}


function deleteAccount()
{	
	if ( confirm( "Are you sure you want to delete this account record?") )
  	{
	    var accountFld = UTL.getElem( "account_AccountFld" );
	    var feeIDFld = 	UTL.getElem( "account_FeeIDFld" );
	    var invIDFld = 	UTL.getElem( "account_InvoiceIDFld" );
	    var effDateFld = UTL.getElem( "account_EffDateFld" );
	
	    if ( accountFld._suggestDataObj != null && feeIDFld.selectedIndex != -1 && invIDFld.selectedIndex != -1 && effDateFld.value != "" )
	    {    
	        var actionSelected = UTL.getElem( "accountActionSelect" ).options[UTL.getElem( "accountActionSelect" ).selectedIndex].value;
	        var updAccountXML = buildXML( "UpdMFAccount", "delete", getAccountData() );
	        postUpdateRequest( "account", updAccountXML );
	    }
  	}
}



function handleAccountActionSelectChange()
{
	if ( UTL.getElem( "account_GBCDFld" ).value != "Bad" )
	{
	    var actionSelected = UTL.getElem( "accountActionSelect" ).options[UTL.getElem( "accountActionSelect" ).selectedIndex].value;
	    
	    EvtHandler.remove( UTL.getElem( "account_SaveBtn" ), "click", deleteAccount );
	    EvtHandler.remove( UTL.getElem( "account_SaveBtn" ), "click", updateAccount );
	    
	    switch( actionSelected )
	    {
	        case "Modify":
	        {
	        	UTL.getElem( "account_EffDateFld" ).disable( false );
	        	UTL.getElem( "account_StopDateFld" ).disable( false );
	            UTL.getElem( "account_FeeIDFld" ).disabled = false;
	            UTL.getElem( "account_InvoiceIDFld" ).disabled = false;
	            	            
	            EvtHandler.add( UTL.getElem( "account_SaveBtn" ), "click", updateAccount );
	                                    
	            break;                           
	        }
	        case "Delete":
	        {            
	        	UTL.getElem( "account_EffDateFld" ).disable( true );
	        	UTL.getElem( "account_StopDateFld" ).disable( true );
	            UTL.getElem( "account_FeeIDFld" ).disabled = true;
	            UTL.getElem( "account_InvoiceIDFld" ).disabled = true;
	            
	            EvtHandler.add( UTL.getElem( "account_SaveBtn" ), "click", deleteAccount );

	            break;
	        }
	    }
	}
	else
	{		
		alert( "Cannot update a 'Bad' record" );
		UTL.getElem( "accountActionSelect" ).selectedIndex = -1;
	}
}



function postHoldingEntUpdateRequest( xml )
{
    var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_HoldingEntityProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    paramMap["holdingEntityID"]   = _holdingEntityID;
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
    
    HTTP.postText( url, postHoldingEntUpdateRequest_callback, xml, true );    
}



function postHoldingEntUpdateRequest_callback( responseText )
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
        _updateOccured = true;
        // update labels in description table and version num variable
        _holdingEntityVersionNum++;   
        UTL.getElem( "holdingEntityInfo_EntityCodeLbl" ).innerHTML = UTL.getElem( "holdingEntityInfo_EntityCodeFld" ).value;
        UTL.getElem( "holdingEntityInfo_CalcMethodLbl" ).innerHTML = UTL.getElem( "holdingEntityInfo_CalcMethodFld" ).options[UTL.getElem( "holdingEntityInfo_CalcMethodFld" ).selectedIndex].innerHTML;
        
        if (UTL.getElem( "holdingEntityInfo_CalcMethodFld" ).value == "TGA")
        	document.getElementById("aggregationFieldset").style.display = "block";
       	else
       		document.getElementById("aggregationFieldset").style.display = "none";
       		
		UTL.getElem( "feeIDFieldSet" ).style.display = "block";
		UTL.getElem( "invoiceIDFieldSet" ).style.display = "block";
		UTL.getElem( "accountFieldSet" ).style.display = "block";       		
       		     
        closeEntityModify();
    } 
}



function openEntityModify()
{
	if ( _holdingEntityVersionNum == 0 )
	{
		UTL.getElem( "closeDescBtn" ).style.display = "none";
		UTL.getElem( "holdingEntityInfo_EntityCodeFld" ).disabled = false;
	}
	else
	{
		UTL.getElem( "closeDescBtn" ).style.display = "inline";
		UTL.getElem( "holdingEntityInfo_EntityCodeFld" ).disabled = true;
	}

    UTL.getElem( "modifyEntityBtn").style.display = "none";    
    UTL.getElem( "entityHistoryBtn").style.display = "none";
    UTL.getElem( "holdingEntityInfo_descriptionTable").style.display = "none";
    UTL.getElem( "holdingEntityInfo_modifyDescriptionTable").style.display = "block";
    displayGrayDiv();    
    
    // update the calcMethod select to match the exisiting
    var calcMethodFld = UTL.getElem( "holdingEntityInfo_CalcMethodFld");
    var calcMethodLbl = UTL.getElem( "holdingEntityInfo_CalcMethodLbl");
    for( var i = 0; i < calcMethodFld.options.length; i++)
    {
        if( calcMethodFld.options[i].innerHTML == calcMethodLbl.innerHTML)
        {
            calcMethodFld.selectedIndex = i;
        }
    }
}



function closeEntityModify()
{
	if (_allowUpdates == "yes")
    	UTL.getElem( "modifyEntityBtn" ).style.display = "block";

	UTL.getElem( "entityHistoryBtn").style.display = "block";    	  
    UTL.getElem( "holdingEntityInfo_descriptionTable").style.display = "block";
    UTL.getElem( "holdingEntityInfo_modifyDescriptionTable").style.display = "none";    
    hideGrayDiv();
}



function saveEntityModify()
{  
    var dataMap = {};
    dataMap["holdingEntityCode"] = UTL.getElem( "holdingEntityInfo_EntityCodeFld" ).value;        
    dataMap["mfCalMethod"]       =  UTL.getElem( "holdingEntityInfo_CalcMethodFld").options[UTL.getElem( "holdingEntityInfo_CalcMethodFld" ).selectedIndex].value;
        
    // version = 0 => no holding entity data exists, so action = add
    if ( _holdingEntityVersionNum == 0 ) 
    {                                
        xml = buildXML( "UpdHoldEnt", "add", dataMap );
    }
    else
    {
        // for modify we pass the version        
        dataMap["version"] = "" + _holdingEntityVersionNum;
        xml = buildXML( "UpdHoldEnt", "modify", dataMap );
    }

    postHoldingEntUpdateRequest( xml );     
}


function hideGrayDiv()
{
    UTL.getElem( "grayDiv").style.display = "none";
}

function displayGrayDiv()
{
    var d = UTL.getElem( "grayDiv" );
    
    d.style.height = WebTools.findElemPos( UTL.getElem( "btnCloseWindow" ) )["top"] - 160;
    d.style.display = "block"; 
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


function alertBrokerSuggestOptions()
{
    var msgStr = "Search by one of: \n";
    msgStr += "- Broker Code \n";
    msgStr += "- Broker Name \n";
    alert( msgStr );    
}


function alertSalesRepSuggestOptions()
{    
    var msgStr = "Search by one of: \n";
    msgStr += "- SalesRep Code \n";
    msgStr += "- SalesRep Name \n";   
    alert( msgStr );
}


function hideInvoiceHistory()
{
	var invoiceIDTable = UTL.getElem( "invoiceID_ListTable" );
	if ( invoiceIDTable )
	{
    	for(var i = 0; i < invoiceIDTable.lastChild.childNodes.length; i++)
    	{
    		if (invoiceIDTable.lastChild.childNodes[i].rcdStat != "recent")
    		{
    			invoiceIDTable.lastChild.childNodes[i].style.display = "none";		
    		}
    	}	
    }
}

function showInvoiceHistory()
{
	var invoiceIDTable = UTL.getElem( "invoiceID_ListTable" );
	if ( invoiceIDTable )
	{
    	for(var i = 0; i < invoiceIDTable.lastChild.childNodes.length; i++)
    	{
    		if (invoiceIDTable.lastChild.childNodes[i].rcdStat != "recent")
    		{
    			invoiceIDTable.lastChild.childNodes[i].style.display = "inline";		
    		}
    	}	
    }
}


function setAccountsScrolling()
{	
	var accountTable = UTL.getElem( "accounts_ListTable" );
	// add scrolling if more than 10 records in table
	if ( accountTable.lastChild.childNodes.length > 10 )
	{
		var accountDiv = UTL.getElem( "account_ListContentsDiv" );
		accountTable.firstChild.firstChild.style.top = -2;
		accountDiv.style.height = 200;
		accountDiv.style.overflowY = "scroll";
		accountDiv.onscroll = account_scrollHandler;		
	}
}

function account_scrollHandler()
{
	var accountDiv = UTL.getElem( "account_ListContentsDiv" );
	
	var accountTable = UTL.getElem( "accounts_ListTable" );
	accountTable.firstChild.firstChild.style.position = "relative";
	accountTable.firstChild.firstChild.style.zIndex = 1000;	
	accountTable.firstChild.firstChild.style.top = accountDiv.scrollTop - 2;
}


function sendHistoryRequest( historyType, startDate, endDate )
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_HoldingEntityProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["holdingEntityID"]   = _holdingEntityID;    
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
	
	var xml = "<Data><HistoryReq>";
	xml += "<historyType>" + historyType + "</historyType>";
		
	if ( startDate && endDate )
	{
		xml += "<startDate>" + startDate + "</startDate>";
		xml += "<endDate>" + endDate + "</endDate>";
	}
	xml += "</HistoryReq></Data>";
	
    HTTP.postText( url, function( responseText ){ historyRequest_callback( historyType, responseText ) }, xml, true );
}


function historyRequest_callback( historyType, responseText )
{			
	var responseXML = XML.parseToXML( responseText );	
	
    var errorNode = XML.getNode( "/responseContents/error", responseXML );    
    if ( errorNode )
    {
        alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
        // clear the current inner html
    	UTL.getElem("historyContents").innerHTML = "";
        return;
    }
	
	var responseNode = XML.getNode( "/responseContents", responseXML );        

    // clear the current inner html
    UTL.getElem("historyContents").innerHTML = "";
    // set the inner html to the html contents within updatedHTMLNode
    // note: the html contents are treated as xml within the xml dom
    UTL.getElem("historyContents").innerHTML = responseNode.firstChild.xml;
        	
	displayHistoryPopup( historyType );	
}


function filterHistory()
{
	var startDate = UTL.getElem( "historyFilter_startDateFld" ).value;
	var endDate = UTL.getElem( "historyFilter_endDateFld" ).value;
	
	if ( startDate.length == 0 )
	{
		alert( "Please select a start date" );
		return;
	}
	if ( endDate.length == 0 )
	{
		alert( "Please select an end date" );
		return;
	}
	
	sendHistoryRequest( UTL.getElem( "historyTypeFld").value, startDate, endDate );
	// display "refreshing" in hisotry contents
	UTL.getElem( "historyContents" ).innerHTML = "";
	UTL.getElem( "historyContents" ).innerHTML = "Refreshing ...";
}


function displayHistoryPopup( historyType )
{
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	UTL.getElem( "historyTypeFld" ).value = historyType;
	
	var popupDiv = UTL.getElem( "historyDiv" );
	popupDiv.style.display = "block";	
	var popupIframe = UTL.getElem( "historyIframe" );
	popupIframe.style.display = "block";		
}


function closeHistoryPopup()
{
	UTL.getElem( "disableDiv" ).style.display = "none";
	
	var popupDiv = UTL.getElem( "historyDiv" );
	popupDiv.style.display = "none";	
	var popupIframe = UTL.getElem( "historyIframe" );
	popupIframe.style.display = "none";
	
	// clear filters date fields
	UTL.getElem( "historyTypeFld" ).value = "";
	UTL.getElem( "historyFilter_startDateFld" ).value = "";;
	UTL.getElem( "historyFilter_endDateFld" ).value = "";
}

function isUpdatePermitted( type )
{
	var permitted = true;
	if ( _selectedRowMap[type] )
	{ 
		if ( _selectedRowMap[type].gbcd == "Bad" )
		{
			alert( "Cannot update a 'Bad' record" );
			permitted = false;
		}		
	}
	else
	{ 
		alert( "Please select a record to update" );
		permitted = false; 
	}
	return permitted;
}


function clickHandler_modifyAggAccountBtn()
{
	if ( isUpdatePermitted( "aggAccount" ) )
	{
		openPopup( "aggAccount", false );
	}
}


function clickHandler_deleteAggAccountBtn()
{
	if ( isUpdatePermitted( "aggAccount" ) )
	{
		deleteAgg( "aggAccount" );
	}
}


function clickHandler_modifyAggBrokerBtn()
{
	if ( isUpdatePermitted( "aggBroker" ) )
	{
		openPopup( "aggBroker", false );
	}
}


function clickHandler_deleteAggBrokerBtn()
{
	if ( isUpdatePermitted( "aggBroker" ) )
	{
		deleteAgg( "aggBroker" );
	}
}


function clickHandler_modifyAggSalesRepBtn()
{
	if ( isUpdatePermitted( "aggSalesRep" ) )
	{
		openPopup( "aggSalesRep", false );
	}
}


function clickHandler_deleteAggSalesRepBtn()
{
	if ( isUpdatePermitted( "aggSalesRep" ) )
	{
		deleteAgg( "aggSalesRep" );
	}
}


function clickHandler_modifyAggAssetBtn()
{
	if ( isUpdatePermitted( "aggAsset" ) )
	{
		openPopup( "aggAsset", false );
	}
}


function clickHandler_deleteAggAssetBtn()
{
	if ( isUpdatePermitted( "aggAsset" ) )
	{
		deleteAgg( "aggAsset" );
	}
}



