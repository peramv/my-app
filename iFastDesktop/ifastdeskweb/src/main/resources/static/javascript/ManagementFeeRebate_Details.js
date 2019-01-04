_selectedAccount = null;


var _maxWindowSize = 500;


var popupType = null;
var popupMode = null;
var _ignoreWarnings = "no";

var orgDesc = null;
var orgCalSche = null;


// ********************* GENERIC ************************

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



function updateGrayDiv()
{
     grayDiv.style.height = parseInt(document.getElementById("fundsFieldset").clientHeight) + parseInt(document.getElementById("accountsFieldset").clientHeight) + 10;
}



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



function getDateString( dateObj )
{
	var dateStr = "";
	if ( _dateFormat == "dmy" )
	{
		dateStr = dateObj.getDate() + "/" + ( dateObj.getMonth() + 1 ) + "/" + dateObj.getFullYear(); 
	}
	else
	{
		dateStr = ( dateObj.getMonth() + 1 ) + "/" + dateObj.getDate() + "/" + dateObj.getFullYear();
	}
	return dateStr;
}

function encodeSpecialChar( html )
{
	var findReplace = [[/&/g, "&amp;"], [/</g, "&lt;"], [/>/g, "&gt;"]]; 
	for(var item in findReplace) {      
		html = html.replace(findReplace[item][0], findReplace[item][1]); 
	} 
	return html;
	
}

function decodeSpecialChar( html )
{
	var findReplace = [[/&amp;/g, "&"], [/&lt;/g, "<"], [/&gt;/g, ">"]]; 
	for(var item in findReplace) {      
		html = html.replace(findReplace[item][0], findReplace[item][1]); 
	} 
	return html;
	
}








// **************** FEE ID INFORMATION ****************** 

function modifyDescription()
{
	document.getElementById("modifyDescriptionTable").style.display = "block";	
	document.getElementById("modifiedDescInput").value = decodeSpecialChar(originalDescription);
	document.getElementById("descriptionTable").style.display = "none";
	orgDesc = null;
	orgCalSche = null;
	if( !_newFeeModel )
	{
		UTL.getElem( "feeIDCodeInput" ).disabled = true;
		
	}
	
	var curCalcMethod = UTL.getElem( "calcMethodLabel" ).innerHTML;	
	var calcMethodFld = UTL.getElem( "calcMethodFld" );
	for ( var i = 0; i < calcMethodFld.options.length; i++ )
	{
	    if ( calcMethodFld.options[i].text == curCalcMethod )
	    {
	        calcMethodFld.selectedIndex = i;
	    }   
	}
	
	if (_isMFRCalc == "yes")
	{
		var curScheduleCode = UTL.getElem( "scheduleCodeLabel" ).innerHTML;	
		var scheduleCodeFld = UTL.getElem( "scheduleCodeFld" );
		for ( var i = 0; i < scheduleCodeFld.options.length; i++ )
		{
			if ( scheduleCodeFld.options[i].text == curScheduleCode )
			{
				scheduleCodeFld.selectedIndex = i;
			}   
		}
	}
	
	if ( _screenMode == "add" )
	{
		UTL.getElem( "deleteDescBtn" ).style.display = "none";
		UTL.getElem( "closeDescModifyBtn" ).style.display = "none";		
	}
	else
	{
		UTL.getElem( "deleteDescBtn" ).style.display = "inline";
		UTL.getElem( "closeDescModifyBtn" ).style.display = "inline";		
		orgDesc = document.getElementById("modifiedDescInput").value;
		orgCalSche = "";
		if (_isMFRCalc == "yes")
		{
			orgCalSche = UTL.getElem( "scheduleCodeFld" ).options[UTL.getElem(  "scheduleCodeFld" ).selectedIndex].text;
		}
	}
	
	
	var grayDiv = UTL.getElem("grayDiv");
	grayDiv.style.height = UTL.getElem( "accountsFieldset" ).offsetHeight + UTL.getElem( "fundsFieldset" ).offsetHeight;
	grayDiv.style.display = "block";	
	
	
	UTL.getElem("modifyDescBtn").style.display = "none";
}



function saveDescription()
{
	updateFundInformation();
}



function closeDescription()
{
	document.getElementById("descriptionTable").style.display = "block";
	document.getElementById("modifyDescriptionTable").style.display = "none";
	document.getElementById("grayDiv").style.display = "none";
	
	document.getElementById("modifyDescBtn").style.display = "inline";
	document.getElementById("deleteDescBtn").style.display = "inline";
}



function deleteRebateFeeID()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["ignoreWarnings"]	  = _ignoreWarnings;    
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildDeleteFundInfoXML(); 	  
    HTTP.postText( url, deleteFundInformation_callback, xml, true );   
}



function buildDeleteFundInfoXML ()
{	
	var XML = "<Data><updFeeID>";
	if (_screenMode == "add")
	{
		XML += "<feeModelCode>" + document.getElementById("feeIDCodeInput").value + "</feeModelCode>";
		XML += "<action>add</action>";   
	}
	else
	{
	 	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";
	 	XML += "<action>delete</action>";   
	}
	
	XML += "<version>" + _feeModelVersion + "</version>";
	XML += "<description>" + encodeSpecialChar(document.getElementById("modifiedDescInput").value) + "</description>";      
    XML += "<mfrCalcMethod>" + document.getElementById("calcMethodLabel").code + "</mfrCalcMethod>";
	
	if (_isMFRCalc == "yes")
	{
		XML += "<scheduleCode>" + document.getElementById("scheduleCodeFld").code + "</scheduleCode>";
	} 
	else      
	{
		XML += "<scheduleCode></scheduleCode>";
	}	

   	XML += "</updFeeID></Data>";
   	
	return (XML);
}



function updateFundInformation_callback( responseText )
{
	var responseXML = XML.parseToXML( responseText );
    var errorNode = XML.getNode( "/responseContents/error", responseXML );    
	var newCalSche = "";
	
    if ( errorNode )
    {
        alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
        return;
    }
	
    if(_screenMode == "add")
    {
			UTL.getElem( "feeIDCode").innerHTML = UTL.getElem( "feeIDCodeInput").value;
			_newFeeModel = false;
	}
	UTL.getElem( "descriptionTable").style.display = "block";
	UTL.getElem( "descriptionField").innerHTML = encodeSpecialChar(UTL.getElem( "modifiedDescInput").value);

	originalDescription = document.getElementById("modifiedDescInput").value;	
    UTL.getElem( "calcMethodLabel" ).innerHTML = UTL.getElem( "calcMethodFld" ).options[UTL.getElem(  "calcMethodFld" ).selectedIndex].text;
	
	if (_isMFRCalc == "yes")
	{
		UTL.getElem( "scheduleCodeLabel" ).innerHTML = UTL.getElem( "scheduleCodeFld" ).options[UTL.getElem(  "scheduleCodeFld" ).selectedIndex].text;
		_scheduleCode = UTL.getElem( "scheduleCodeFld" ).options[UTL.getElem(  "scheduleCodeFld" ).selectedIndex].value;					
		newCalSche = UTL.getElem( "scheduleCodeFld" ).options[UTL.getElem(  "scheduleCodeFld" ).selectedIndex].text;		
		updateAccount_callback( responseText );				 
	}
	
    if ( UTL.getElem( "calcMethodFld" ).value != "TR" )
    {
        UTL.getElem( "fundsFieldset" ).style.display = "none";
    }
    else
    {        
        UTL.getElem( "fundsFieldset" ).style.display = "block";
    }
	
	UTL.getElem( "accountsFieldset" ).style.display = "block";
	UTL.getElem( "modifyDescriptionTable").style.display = "none";
	UTL.getElem( "grayDiv").style.display = "none";	
	UTL.getElem( "modifyDescBtn").style.display = "inline";
	UTL.getElem( "deleteDescBtn").style.display = "inline";

	if (_screenMode == "add")
	{
		_feeModelVersion++;
	}
	var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML/div/input", responseXML );
	if ((_screenMode == "modify") &&
		(( orgDesc != UTL.getElem( "modifiedDescInput").value ) ||
		 (orgCalSche != newCalSche) ||
		 (updatedHTMLNode.getAttribute('value') != "no"))
		)
	{
		_feeModelVersion++;
	}

	_screenMode = "modify";	
}



function deleteFundInformation_callback( responseText )
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
        parent.closeFeeIDScreen( true );
    }  	
}



function updateFundInformation()
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );	
	var xml = buildFundInfoXML ();	
    
    HTTP.postText( url, updateFundInformation_callback, xml, true );    
}



function buildFundInfoXML()
{	
	var XML = "<Data><updFeeID>";
	if ( _screenMode == "add" )
	{
		XML += "<feeModelCode>" + document.getElementById("feeIDCodeInput").value + "</feeModelCode>";
		XML += "<action>add</action>";   
	}
	else
	{
	 	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";
	 	XML += "<action>modify</action>";   
	}
	
	XML += "<version>" + _feeModelVersion + "</version>";   
	XML += "<description>" + encodeSpecialChar(document.getElementById("modifiedDescInput").value) + "</description>";      
    XML += "<mfrCalcMethod>" + document.getElementById("calcMethodFld").value + "</mfrCalcMethod>";
	
	if (_isMFRCalc == "yes")
	{
		XML += "<scheduleCode>" + document.getElementById("scheduleCodeFld").value + "</scheduleCode>";
	}
	else 
	{
		XML += "<scheduleCode></scheduleCode>";
	}
       
   	XML += "</updFeeID></Data>"
   	
	return (XML);
}



function convertToAddMode()
{
  	document.getElementById("feeIDCodeModify").innerHTML = '<input id="feeIDCodeInput"/>';	
}










// *************************** ACCOUNT  ************************

function showAccountHistory( acctNum, accountListDiv, btnToHide, btnToShow )
{
    var histRecCount = 0;
           
    for ( var i = 0; i < accountListDiv.childNodes.length; i++ )
    {              
        var acctRec = accountListDiv.childNodes[i];
         
        if ( acctRec.acctNum == acctNum && acctRec.rcdStat == "historical" )
        {
            histRecCount++;
            acctRec.style.display = "block";
        }
    }
    
    if ( histRecCount > 0 )
    {
        btnToHide.style.display = "none";
        btnToShow.style.display = "inline";
    }
    else
    {
        alert( "No historical records available" );
    }
}



function hideAccountHistory( acctNum, accountListDiv, btnToHide, btnToShow )
{
    var accounts_ListDiv = UTL.getElem( "accounts_ListDiv" );
    
    for ( var i = 0; i < accountListDiv.childNodes.length; i++ )
    {              
        var acctRec = accountListDiv.childNodes[i];
          
        if ( acctRec.acctNum == acctNum && acctRec.rcdStat == "historical" )
        {            
            acctRec.style.display = "none";
        }
    }
        
    btnToHide.style.display = "none";
    btnToShow.style.display = "inline";
}



function alertAccountSuggestOptions()
{
    var msgStr = "Search by: \n";
    msgStr += "- Account Number \n";
    msgStr += "- Partial Last Name \n";
    msgStr += "- Partial Last Name <space> Parital First Name \n";
    msgStr += "- Broker Account Number \n";
    msgStr += "- Broker Code <space> Broker Account Number \n";
    msgStr += "- SIN (no spaces or hyphens) \n";
    msgStr += "- Any Owner Identifier Number \n";
    alert( msgStr );
}



function selectAccount( row )
{    
    if ( _selectedAccount )
    {
        unselectRow( row );
    }
    
    highlightRow( row );
    _selectedAccount = row;   
}



function maintainAccountHeight()
{
	var accountListDiv = document.getElementById("accounts_ListDiv");
	var scrollableAccountDiv = document.getElementById("scrollableAccountsDiv");
	
	if(accountListDiv.offsetHeight >= 100)
	{
		if (_isMFRCalc == 'yes')
		{
			scrollableAccountDiv.style.height = 120;
		}
		else
		{
			scrollableAccountDiv.style.height = 100;
		}
		scrollableAccountDiv.style.overflowY = "scroll";		
	}
	else
	{		
		if (_isMFRCalc == 'yes')
		{
			scrollableAccountDiv.style.height = accountListDiv.offsetHeight + 20;
		}
		else
		{
			scrollableAccountDiv.style.height = accountListDiv.offsetHeight;
		}
		scrollableAccountDiv.style.overflowY = "auto";		
	}
	
	if (_isMFRCalc == 'yes')
	{
		if (accountListDiv.offsetWidth >= 750)
		{
			scrollableAccountDiv.style.width = 750;
			scrollableAccountDiv.style.overflowX = "scroll";
		}
		else
		{		
			scrollableAccountDiv.style.width = accountListDiv.offsetWidth;		
			scrollableAccountDiv.style.overflowX = "auto";		
		}
	}	
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



function unselectRow(  )
{
    unhighlightRow( _selectedAccount );
    _selectedAccount = null;
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



function handleAccountActionSelectChange ()
{	
    var accountActionSelect = UTL.getElem( "accountActionSelect" );
    var action = accountActionSelect.options[accountActionSelect.selectedIndex].value;
        
    if ( action == "" )
    {
    	return;
    }
    else if ( action == "ShowHistory" )
    {
    	sendHistoryRequest( "MFRAccounts" );
    }
    else if ( action == "Add" )
	{
		openAccountPopup();
		initAccountPopup( action );
	}            
    else
    {
    	if ( !_selectedAccount )
	    {
	        alert( "Please select an account" );
	    }
    	else
    	{ 
	    	if ( _selectedAccount.gbcd != "Bad" )
	    	{
	    		if ( action == "Delete" )
	    		{
			    	if ( confirm( "Are you sure you wish to delete this record?" ) )
			    	{
			    		deleteAccount();
			    	}		    	
	    		}
	    		else
		    	{
	    			openAccountPopup();
	    			initAccountPopup( action );
		    	}
	    	}
	    	else
	    	{
	    		alert( "Cannot update a 'Bad' record" );
	    	}
    	}
    }
          
}



function openAccountPopup()
{
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	var popupDiv = UTL.getElem( "account_PopupDiv" );
	popupDiv.style.display = "block";	
	var popupIframe = UTL.getElem( "account_PopupIframe" );
	popupIframe.style.display = "block";
}



function closeAccountPopup()
{
    UTL.getElem( "disableDiv" ).style.display = "none";	
	UTL.getElem( "account_PopupDiv" ).style.display = "none";
	UTL.getElem( "account_PopupIframe" ).style.display = "none";		
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



function initAccountPopup( action )
{
    EvtHandler.remove( UTL.getElem( "accountPopup_SaveBtn" ), "click", addAccount );    
    EvtHandler.remove( UTL.getElem( "accountPopup_SaveBtn" ), "click", modifyAccount );    

    switch ( action )
    {
        case "Add":
        {
            // all fields empty and enabled
        
            var acctFld = UTL.getElem( "accountPopup_AccountFld" );
            acctFld.disabled = false;
            acctFld._suggestDataObj = null;
            acctFld.value = "";
            acctFld.focus();
             
            if (_isMFRCalc == "yes")
			{
				var freqFld = UTL.getElem( "accountPopup_FreqFld" );
				var curFreqCode = _scheduleCode;
				for ( var i = 0; i < freqFld.options.length; i++ )
				{
					if ( curFreqCode == freqFld.options[i].value )
					{	
						freqFld.selectedIndex = i
					}    
				}
				freqFld.disabled = true;			
			}
			else
			{
				var freqFld = UTL.getElem( "accountPopup_FreqFld" );
				freqFld.selectedIndex = -1;
				freqFld.disabled = false;
			}	    
            
            var effDateFld = UTL.getElem( "accountPopup_EffDateFld" );
            effDateFld.value = "";
            effDateFld.disable( false );
                        
            var stopDateFld = UTL.getElem( "accountPopup_StopDateFld" );
            if ( _dateFormat == "dmy" )
            {
                stopDateFld.value = "31/12/9999";
            }
            else
            {
                stopDateFld.value = "12/31/9999"
            }            
            stopDateFld.disable( false );
                

			if (_isMFRCalc == "yes")
			{       
				var lastAccrualDateFld = UTL.getElem( "accountPopup_LastAccrualDateFld" );
				lastAccrualDateFld.value = _lastAccrualDate;
				lastAccrualDateFld.disabled = true;
			
				var nextMFRDateFld = UTL.getElem( "accountPopup_NextMFRDateFld" );
				nextMFRDateFld.value = _nextMFRDate;	            
				nextMFRDateFld.disabled = true;	
			}
		
			EvtHandler.add( UTL.getElem( "accountPopup_SaveBtn" ), "click", addAccount );
            break;
        }        
        case "Modify":
        {
            // all fields prepopulated - eff/stop date fields enabled          
        
            var acctFld = UTL.getElem( "accountPopup_AccountFld" );                                   
            acctFld.initialValue = _selectedAccount.acctRowID;
            SuggestFieldManager.reInit( acctFld );                  
            acctFld.disabled = true;
            
            var freqFld = UTL.getElem( "accountPopup_FreqFld" );
            var curFreqCode = _selectedAccount.freqCode;
            for ( var i = 0; i < freqFld.options.length; i++ )
            {
                if ( curFreqCode == freqFld.options[i].value )
                {
                    freqFld.selectedIndex = i
                }    
            }
            if (_isMFRCalc == "yes")
			{
				freqFld.disabled = true;
			}
			else
			{
				freqFld.disabled = false;
			}
        
            var effDateFld = UTL.getElem( "accountPopup_EffDateFld" );
            effDateFld.value = _selectedAccount.effDate;
            effDateFld.disable( false );
            
            var stopDateFld = UTL.getElem( "accountPopup_StopDateFld" );
            stopDateFld.value = _selectedAccount.stopDate;
            stopDateFld.disable( false );
            
			if (_isMFRCalc == "yes")
			{       					
				var lastAccrualDateFld = UTL.getElem( "accountPopup_LastAccrualDateFld" );
				lastAccrualDateFld.value = _selectedAccount.lastAccrualDate;
				lastAccrualDateFld.disabled = true;
			
				var nextMFRDateFld = UTL.getElem( "accountPopup_NextMFRDateFld" );
				nextMFRDateFld.value = _selectedAccount.nextMFRDate;	            
				nextMFRDateFld.disabled = true;	
			}		

            EvtHandler.add( UTL.getElem( "accountPopup_SaveBtn" ), "click", modifyAccount );
            break;
        }       
    }
}



function validateAccountPopupFields()
{
    var noErrors = true;
    noErrors = ( noErrors && UTL.getElem( "accountPopup_AccountFld" )._suggestDateObj );
    noErrors = ( noErrors && UTL.getElem( "accountPopup_FreqFld" ).selectedIndex != -1 );    
    noErrors = ( noErrors && UTL.getElem( "accountPopup_EffDateFld" ).value.length > 0 );
    noErrors = ( noErrors && UTL.getElem( "accountPopup_StopDateFld" ).value.length > 0 );
    
    return noErrors;
}



function buildAccountUpdXML( action, xmlFldValueMap )
{
    var xml = "";
    xml += XML.createNodeStr( "action", action );
    
    for( var i in xmlFldValueMap )
    {
        xml += XML.createNodeStr( i, xmlFldValueMap[i] );
    }
    
    return XML.createNodeStr( "Data", XML.createNodeStr( "UpdMFRAccount", xml ) );
}



function getAccountPopupData()
{
    var xmlFldValueMap = {};    
    xmlFldValueMap["account"]     	= ( UTL.getElem( "accountPopup_AccountFld" )._suggestDataObj ? UTL.getElem( "accountPopup_AccountFld" )._suggestDataObj["acctNum"] : "" );
    xmlFldValueMap["frequencyCode"] = UTL.getElem( "accountPopup_FreqFld" ).value;                                   
    xmlFldValueMap["effDate"]    	= UTL.getElem( "accountPopup_EffDateFld" ).value;
    xmlFldValueMap["stopDate"]   	= UTL.getElem( "accountPopup_StopDateFld" ).value;
	if (_isMFRCalc == "yes")
	{
		xmlFldValueMap["nextMFRDate"] 	= UTL.getElem( "accountPopup_NextMFRDateFld" ).value;
		xmlFldValueMap["lastAccrualDate"] 	= UTL.getElem( "accountPopup_lastAccrualDateFld" ).value;
	}
    return xmlFldValueMap;
}



function postAccountUpdateRequest( xml )
{
    var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
	
	HTTP.postText( url, updateAccount_callback, xml, true );    
}



function updateAccount_callback( responseText )
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
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
        
        // clear the current inner html
        UTL.getElem("accounts_ListDiv").innerHTML = "";
        // set the inner html to the html contents within updatedHTMLNode
        // note: the html contents are treated as xml within the xml dom
        UTL.getElem("accounts_ListDiv").innerHTML = updatedHTMLNode.firstChild.xml;
		
		if (UTL.getElem("nextMFRDateHid"))
		{
			_nextMFRDate = UTL.getElem("nextMFRDateHid").value;
		}
		if (UTL.getElem("lastAccrualDateHid"))
		{
			_lastAccrualDate = UTL.getElem("lastAccrualDateHid").value;
		}
		
        closeAccountPopup();
        maintainAccountHeight();
        _selectedAccount = null;        
    } 
}



function addAccount()
{	
    var accountDataMap = getAccountPopupData();
    accountDataMap["feeModelCode"] = UTL.getElem( "feeIDCode" ).innerHTML;
    var addAccountXML = buildAccountUpdXML( "add", accountDataMap );               
    postAccountUpdateRequest( addAccountXML );           
}



function deleteAccount()
{
    var accountDataMap = {};
    accountDataMap["account"]     	= _selectedAccount.acctNum;
    accountDataMap["frequencyCode"] = _selectedAccount.freqCode;                                   
    accountDataMap["effDate"]    	= _selectedAccount.effDate;
    accountDataMap["stopDate"]   	= _selectedAccount.stopDate;	
	accountDataMap["nextMFRDate"]   	= _selectedAccount.nextMFRDate;
    accountDataMap["feeModelCode"] = UTL.getElem( "feeIDCode" ).innerHTML;
    accountDataMap["shrAcctFeeID"] = _selectedAccount.shrAcctFeeID;
    accountDataMap["version"] = _selectedAccount.version;

    var deleteAccountXML = buildAccountUpdXML( "delete", accountDataMap );	           
    postAccountUpdateRequest( deleteAccountXML );
                   
}



function modifyAccount()
{
    var accountDataMap = getAccountPopupData();
    accountDataMap["feeModelCode"] = UTL.getElem( "feeIDCode" ).innerHTML;
    accountDataMap["shrAcctFeeID"] = _selectedAccount.shrAcctFeeID;
    accountDataMap["version"] = _selectedAccount.version;

    var modifyAccountXML = buildAccountUpdXML( "modify", accountDataMap );
            
    postAccountUpdateRequest( modifyAccountXML );           
}



function correctAccount()
{
    var accountDataMap = getAccountPopupData();
    accountDataMap["feeModelCode"] = UTL.getElem( "feeIDCode" ).innerHTML;
    accountDataMap["shrAcctFeeID"] = _selectedAccount.shrAcctFeeID;
    accountDataMap["version"] = _selectedAccount.version;

    var correctAccountXML = buildAccountUpdXML( "correct", accountDataMap );
            
    postAccountUpdateRequest( correctAccountXML );           
}

























// ********************* FUND **********************

function maintainFundHeight()
{
	var fundListDiv = document.getElementById("fund_ListDiv");
	var scrollableFundDiv = document.getElementById("scrollableFundsDiv");
    
	if(fundListDiv.offsetHeight >= _maxWindowSize)
	{
		scrollableFundDiv.style.height = _maxWindowSize;
		scrollableFundDiv.style.overflowY = "scroll";
	}
	else
	{		
		scrollableFundDiv.style.height = fundListDiv.offsetHeight;
		scrollableFundDiv.style.overflowY = "auto";
	}
}



/*function selectFund( div, selectType )
{	
    if ( div.style.background == "" || div.style.background == "none transparent scroll repeat 0% 0%" )            
    {
      div.style.background =  "url(" + _vURL + "images/rowHighlight.png)";
      div.style.backgroundRepeat =  "repeat-x";
      if ( _selectedFund != null )
      {
        _selectedFund.style.background = "transparent";
      }
      if ( selectType == "rate" )
      {
      	div.style.backgroundPosition = "0px 3px";
      }
      else
      {
      	div.style.backgroundPosition = "0px 0px";
      }
      _selectedFund = div;
    }
    else
    {
      div.style.background = "transparent";
      _selectedFund = null;	  
    }         
}*/



function toggleHistory(fundNumber, button)
{
	var counter = 2;
	var currentHistoric = document.getElementById("fund" + fundNumber + "stopped" + counter);	

	while (currentHistoric != null && currentHistoric != undefined)
	{
		if (currentHistoric.style.display == "none")
			currentHistoric.style.display = "block";
		else
		{
			currentHistoric.style.display = "none";
		}
			
		counter++;
		currentHistoric = document.getElementById("fund" + fundNumber + "stopped" + counter);		
	}
	
	if (button.firstChild.nextSibling.firstChild.innerHTML == "Show Hist.")
		button.firstChild.nextSibling.firstChild.innerHTML = "Hide Hist.";
	else
		button.firstChild.nextSibling.firstChild.innerHTML = "Show Hist.";			
	
	maintainFundHeight();	
	window.event.cancelBubble = true;
}



function handleFundActionSelectChange ()
{	
	switch (document.getElementById("fundActionSelect").options[document.getElementById("fundActionSelect").selectedIndex].value)
	{
		case("ShowAll"):
		{
			showAllFundDetails();
			break;
		}
		case("HideAll"):
		{
			hideAllFundDetails();
			break;		
		} 
		case("UpdateRates"):
		{
			if ( _selectedRateSet )
			{		
				loadFundModifyScreen( "updaterates", "updaterates", false, _selectedFund );
				populateModifyScreen( "rate", _selectedRateSet, true );			
				UTL.getElem( "stopDateFld" ).value = ( _dateFormat == "dmy" ? "31/12/9999" : "12/31/9999" );
			}
			else
			{
				throw new Error( "No rateSet selected" );
			}										
							
			break;
		}
		case("CorrectRate"):
		{	
			if ( _selectedRateSet )
			{
				loadFundModifyScreen( "correctrate", "rate", false, _selectedFund );
				populateModifyScreen( "rate", _selectedRateSet, true );
				UTL.getElem( "effDateFld" ).disable( true );
				UTL.getElem( "stopDateFld" ).disable( true );
			}
			else
			{
				throw new Error( "No rateSet selected" );
			}		
			
			break;
		}
		case("DeleteRate"):
		{			
			if ( _selectedRateSet )
			{
				if( confirm("Are you sure you want to delete the selected set of rates?") )
				{
					deleteRate();
				}
			}
			else
			{
				throw new Error( "No rateSet selected" );
			}		
				
				
			break;
		}
		case("AddFund"):
		{
			loadFundModifyScreen ("addfund", "addfund", true, _selectedFund );
			document.getElementById("ratesFund").style.width = "100%";
			document.getElementById("ratesFund").disabled = false;
			document.getElementById("effDateFld").value = "";
			document.getElementById("effDateFld").disable( false );
			if (_dateFormat == "dmy")
				document.getElementById("stopDateFld").value = "31/12/9999";
			else 
				document.getElementById("stopDateFld").value = "12/31/9999";
			document.getElementById("stopDateFld").disable( true );		
						
			if (_allowTierChanges == "yes")
			{
				for (var i = 0; i < 4; i++)
					addRow();
			}
			else
			{
				populateDefaultTiers();
			}
									
			break;
		}
		case("StopFund"):
		{			
			if ( _selectedFund != null )
			{							
				UTL.getElem( "ratesTableHeader" ).style.display = "none";
				document.getElementById( "stopDateFld" ).disable( false );
				loadFundModifyScreen( "stopfund", "fund", false, _selectedFund );
				populateModifyScreen( "fund", _selectedFund, false );
				
				var today = new Date();										
				stopDateFld.value = getDateString( today );
															
				var ratesFundFld = UTL.getElem( "ratesFund" );				
		    	ratesFundFld.initialValue = _selectedFund.uuid;
				SuggestFieldManager.reInit( ratesFundFld );
				ratesFundFld.disabled = true;
			}
			else
			{
				throw new Error( "No fund selected" );
			}	
			
			break;
		}
		case ( "ShowHistory" ):
		{
			sendFundHistoryRequest();
			break;
		}
		case ( "UnStopFund" ):
		{
			if ( _selectedFund )
			{
				if ( confirm( "Are you sure you want to un-stop the selected fund?" ) )
				{
					unstopFund();
				}
			}			
			break;
		}					
	}
}



/*  loadFundModifyScreen -> used to open up the modify fund/rate popup 
 * 
 *  mode -> add, modify, delete, stop, etc... (based on what you're going to be using the popup for)
 *  type -> rate or fund
 *  fundModify -> true or false depending on whether the fund field should be modifiable
 *  fund -> the selected fund or rate
 * 
 *  note: the parent of the selected fund or rate has all of the information in CSS fields 
*/
function loadFundModifyScreen( mode, type, fundModify, fund )
{
	popupType = type;
	popupMode = mode;
	
	openRatePopup();
	
	if (type == "rate")
	{
	    var ratesFundFld = UTL.getElem( "ratesFund" );
		ratesFundFld.initialValue = fund.uuid;
		SuggestFieldManager.reInit( ratesFundFld );
		ratesFundFld.disabled = true;
		UTL.getElem( "ratesTableHeader" ).style.display = "block";
				
		if ( _aggrLink == "yes" )
		{
			UTL.getElem( "aggrLinkRow" ).style.display = "block";
		}	
		if ( _allowTierChanges == "yes" )
		{
			UTL.getElem( "addTierBtn" ).style.display = "block";					
		}
			
		UTL.getElem( "effDateFld" ).disable( false );
	}
	else if ( type == "addfund" )
	{
		var ratesFundFld = UTL.getElem( "ratesFund" );
		ratesFundFld.value = "";
		ratesFundFld._suggestDataObj = null;
		
		if ( _aggrLink == "yes" )
		{
			UTL.getElem( "aggrLinkRow" ).style.display = "block";
		}
		if ( _allowTierChanges == "yes" )
		{		
			UTL.getElem( "addTierBtn" ).style.display = "block";	
			UTL.getElem( "ratesTableHeader" ).style.display = "block";			
		}
	}
	else if (type == "updaterates")
	{
		var ratesFundFld = UTL.getElem( "ratesFund" );
		ratesFundFld.initialValue = fund.uuid;
		SuggestFieldManager.reInit( ratesFundFld );
		ratesFundFld.disabled = true;
		
		// show the rates table header
		UTL.getElem( "ratesTableHeader" ).style.display = "block";
		
		if (_aggrLink == "yes")
		{
			UTL.getElem( "aggrLinkRow" ).style.display = "block";
		}
		
		if ( _allowTierChanges == "yes" )
		{		
			UTL.getElem( "addTierBtn" ).style.display = "block";		
		}
		
		// disable effDate, enable stopDate 
		UTL.getElem( "effDateFld" ).disable( false );
		UTL.getElem( "stopDateFld" ).disable( true );
	}
	// correctrates
	else
	{
		UTL.getElem( "aggrLinkRow" ).style.display = "none";
		if ( _allowTierChanges == "yes" )
		{		
			UTL.getElem( "addTierBtn" ).style.display = "none";
			UTL.getElem( "ratesTableHeader" ).style.display = "none";
		}
		
		
		if (fundModify == false && fund != null)
		{							
			document.getElementById("effDateFld").disable(true);
		}
		else 
		{
			document.getElementById("effDateFld").disable(false);			
			document.getElementById("ratesFund").disabled = false;
		}
	}		
}



function addRow(modifiable)
{	
	var table = document.getElementById("ratesTable");
	var row = null;
	var col = null;
	var input = null;
	
	if (modifiable == false)
		var disabled = true;
	
	row = document.createElement("tr");	
	col = document.createElement("td");
	col.colspan = "2";
	input = document.createElement("input");	
	input.style.width = "132";
		
	if (_allowTierChanges == "no")
		input.disabled = true;
	else
		input.disabled = disabled;
		
	col.appendChild (input);
	row.appendChild (col);
	
	col = document.createElement("td");
	col.innerHTML = "-";
	col.style.textAlign = "center";
	row.appendChild (col);
	
	col = document.createElement("td");
	input = document.createElement("input");
	input.style.width = "132";
	if (_allowTierChanges == "no")
		input.disabled = true;
	else
		input.disabled = disabled;
	col.appendChild (input);
	row.appendChild (col);
	
	col = document.createElement("td");	
	input = document.createElement("input");
	input.style.width = "55";
	input.disabled = disabled;
	col.appendChild(input);
	col.innerHTML += "%";
	
	row.appendChild (col);
	
	table.firstChild.appendChild(row);
	return row;
}



/*  populateModifyScreen -> used to populate the modify fund/rate popup 
 * 
 *  fund -> the selected fund or rate
 *  modifiable -> true or false depending on whether the fund field should be modifiable
 * 
 *  note: the parent of the selected fund or rate has all of the information in CSS fields 
*/
function populateModifyScreen( type, src, modifiable )
{	
	//var fundDiv = fund.parentNode;
	
	if ( type == "rate" )
	{	 
		var rateTable = src;
			 		
		document.getElementById( "effDateFld" ).value = rateTable.effDate;
		document.getElementById( "stopDateFld" ).value = rateTable.stopDate;
		
		if ( _aggrLink == "yes" )
		{
			document.getElementById("aggrLink").value = rateTable.aggrLink;
		}
		
		var currentRow = rateTable.lastChild.firstChild;		
		var addedRow = null;
	
		while (currentRow != null)
		{	
			addedRow = addRow( modifiable );			
			addedRow.childNodes[0].firstChild.value = currentRow.lowerBound;
			addedRow.childNodes[2].firstChild.value = currentRow.upperBound;
			addedRow.childNodes[3].firstChild.value = currentRow.rate;
			currentRow = currentRow.nextSibling;
		}
	}
	else
	{
		document.getElementById("effDateFld").value = src.effDate;
		document.getElementById("stopDateFld").value = src.stopDate;
		document.getElementById("aggrLinkRow").style.display = "none";		
	}
}



function populateDefaultTiers()
{	
	var addedRow = null;
		
	for (each in _defaultTiers)
	{
		
		addRow();
		addedRow = document.getElementById("ratesTable").firstChild.lastChild;
		addedRow.firstChild.firstChild.value = _defaultTiers[each].lower;
		addedRow.lastChild.previousSibling.firstChild.value = _defaultTiers[each].upper;
	}
}



function showAllFundDetails()
{
	var fund_ListDiv = UTL.getElem( "fund_ListDiv" );
	var fund_ListContentsDiv = fund_ListDiv.firstChild; 		
	for (var i = 0; i < fund_ListContentsDiv.childNodes.length; i++)
	{ 
		var fundDiv = fund_ListContentsDiv.childNodes[i];
		// set +/- image to -
		fundDiv.firstChild.firstChild.src = _vURL + "images/minus.png";
		// hide ratesDiv
		fundDiv.lastChild.style.display = "block";
	} 
	maintainFundHeight();
}



function hideAllFundDetails()
{
	var fund_ListDiv = UTL.getElem( "fund_ListDiv" );	
	var fund_ListContentsDiv = fund_ListDiv.firstChild;		
	for (var i = 0; i < fund_ListContentsDiv.childNodes.length; i++)
	{ 
		var fundDiv = fund_ListContentsDiv.childNodes[i];
		// set +/- image to +
		fundDiv.firstChild.firstChild.src = _vURL + "images/plus.png";
		// hide ratesDiv
		fundDiv.lastChild.style.display = "none";
	} 
	maintainFundHeight();	
}



function fundDescClickHandler( fundId )
{		
	selectFund( fundId );
}



function unselectFund( fundId )
{
	if ( _selectedRateSet )
	{
		unselectRateSet( _selectedRateSet.rateSetId ); 
	}

	var fundDiv = UTL.getElem( "fundDiv_" + fundId );
	var fundDescSpan = UTL.getElem( "fundDesc_" + fundId );
	
	fundDiv.selected = "false";
	fundDescSpan.style.background = "transparent";
	_selectedFund = null;
		
	updateFundActionMenu();
}



function selectFund( fundId, rateSetId )
{	
	var fundDiv = UTL.getElem( "fundDiv_" + fundId );
	var fundDescSpan = UTL.getElem( "fundDesc_" + fundId );
		
	if ( _selectedFund )
	{		
		unselectFund( _selectedFund.uuid );
	}

	_selectedFund = fundDiv;
	fundDiv.selected = "true";	
  	  
  	if ( rateSetId )
  	{
  		selectRateSet( rateSetId );
  	}
  	else
  	{		
		fundDescSpan.style.background =  "url(" + _vURL + "images/rowHighlight.png)";
	  	fundDescSpan.style.backgroundRepeat =  "repeat-x";
	  	fundDescSpan.style.backgroundPosition = "0px 0px";
  	}
  	
  	updateFundActionMenu();
}



function rateSetClickHandler( fundId, rateSetId )
{		 
	selectFund( fundId, rateSetId )		
}



function unselectRateSet( rateSetId )
{
	var rateSetTable = UTL.getElem( "rateSetTable_" + rateSetId );
	
	rateSetTable.selected = "false";
	rateSetTable.style.background = "transparent";
	_selectedRateSet = null;
	
	updateFundActionMenu();	
}



function selectRateSet( rateSetId )
{
	// dont' need to clear _selectedRateSet, since selecting Fund will do that for us
	var rateSetTable = UTL.getElem( "rateSetTable_" + rateSetId );
	_selectedRateSet = rateSetTable
	rateSetTable.selected = "true";
	rateSetTable.style.background =  "url(" + _vURL + "images/rowHighlight.png)";
  	rateSetTable.style.backgroundRepeat =  "repeat-x";
  	rateSetTable.style.backgroundPosition = "0px 3px";
  	
  	updateFundActionMenu();
}



function openRatePopup()
{
	UTL.getElem( "disableDiv" ).style.display = "block";	
	UTL.getElem( "ratesDiv" ).style.display = "block";
	UTL.getElem( "ratesIframe" ).style.display = "block";
	
	UTL.getElem( "fundActionSelect" ).style.visibility = "hidden";	
}



function closeRatePopup()
{
	deleteAllRows();
	
	UTL.getElem( "aggrLink" ).value = "";
	UTL.getElem( "effDateFld" ).value = "";
	UTL.getElem( "stopDateFld" ).value = "";
	
	UTL.getElem( "ratesDiv" ).style.display = "none";
	UTL.getElem( "disableDiv" ).style.display = "none";	
	UTL.getElem( "ratesIframe" ).style.display = "none";	
	UTL.getElem( "fundActionSelect" ).style.visibility = "visible";
}



function deleteAllRows()
{
	if(document.getElementById("ratesTable").innerHTML == "<TBODY></TBODY>")
		return;
		
	var row = document.getElementById("ratesTable").firstChild.firstChild;
	var nextRow = row.nextSibling;
	
	while (row != null)
	{
	  row.removeNode (true);
	  row = nextRow;
	  try{nextRow = nextRow.nextSibling;}
	  catch(e){}
	}
}



function updateFundActionMenu()
{
	var actionSelect = UTL.getElem( "fundActionSelect" );
	var optionsArray = actionSelect.options;
	
	// clear all
	for ( var i = optionsArray.length; i >= 0; i-- )
	{
		actionSelect.remove( i );
	}
	
	actionSelect.add( buildActionOption( "none" ) );
	if ( _allowUpdates == "yes" )
	{
		actionSelect.add( buildActionOption( "AddFund" ) );
		if ( _selectedFund )
		{
			if ( _selectedFund.rcdStat == "Active" )
			{ 
				actionSelect.add( buildActionOption( "StopFund" ) );				
			}
			else
			{
				actionSelect.add( buildActionOption( "UnStopFund" ) );
			}
			
			if ( _selectedRateSet )
			{
				actionSelect.add( buildActionOption( "UpdateRates" ) );
				actionSelect.add( buildActionOption( "CorrectRate" ) ); 				
			}
		}		
	}
	
	actionSelect.add( buildActionOption( "ShowAll" ) );
	actionSelect.add( buildActionOption( "HideAll" ) );
	actionSelect.add( buildActionOption( "ShowHistory" ) );
	
	actionSelect.selectedIndex = 0;	
}



function buildActionOption( id )
{
	var option = document.createElement( "option" );
	option.value = id;
	option.text = _actionSelectMap[id];
	return option;
}



function toggleRatesHistory( ratesDivId, buttonRef )
{
	var ratesDiv = UTL.getElem( ratesDivId );
	var showAllFlag = buttonRef.firstChild.nextSibling.firstChild.innerHTML == "Show Hist.";
	  
	for ( var i = 0; i < ratesDiv.childNodes.length; i++ )
	{
		var rateDiv = ratesDiv.childNodes[i];
		rateDiv.style.display = ( showAllFlag ? "block" : "none" );
	}
	
	if ( showAllFlag )
	{
		buttonRef.firstChild.nextSibling.firstChild.innerHTML = "Hide Hist."		
	} 
	else
	{
		buttonRef.firstChild.nextSibling.firstChild.innerHTML = "Show Hist."
		ratesDiv.firstChild.style.display = "block";
	}
	
	maintainFundHeight();	
	window.event.cancelBubble = true;
}







function updateFeeID()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["ignoreWarnings"]	  = _ignoreWarnings;    
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildFeeIDXML (popupMode);
	HTTP.postText( url,  function(responseText){postUpdateRequest_callback(responseText, updateFeeID)}, xml );   
}



function buildFeeIDXML (action)
{
	var XML = "<Data><updFeeIDFund>";
	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";   
    XML += "<action>" + action + "</action>";    
    
    if (popupType == "fund")
    {
    	XML += "<fund>" + ( document.getElementById("ratesFund")._suggestDataObj ? document.getElementById("ratesFund")._suggestDataObj["fund"] : "" ) + "</fund>";
    	XML += "<class>" + ( document.getElementById("ratesFund")._suggestDataObj ? document.getElementById("ratesFund")._suggestDataObj["class"] : "" ) + "</class>";
    }
    else if (popupType =="addfund")
    {
    	XML += "<fund>" + ( document.getElementById("ratesFund")._suggestDataObj ? document.getElementById("ratesFund")._suggestDataObj["fund"] : "" ) + "</fund>";
    	XML += "<class>" + ( document.getElementById("ratesFund")._suggestDataObj ? document.getElementById("ratesFund")._suggestDataObj["class"] : "" ) + "</class>";
    	if (_aggrLink == "yes")
    	{
    		XML += "<aggrLink>" + document.getElementById("aggrLink").value + "</aggrLink>";
    	}
    	var currentRow = document.getElementById("ratesTable").firstChild.firstChild;
		var nextRow = document.getElementById("ratesTable").firstChild.firstChild.nextSibling;
	
    	
    	while (currentRow != null)
		{		
			XML += "<Tier>";
			XML += "<lower>" + currentRow.firstChild.firstChild.value + "</lower>";
			XML += "<upper>" + currentRow.lastChild.previousSibling.firstChild.value + "</upper>";
			XML += "<rate>" + currentRow.lastChild.firstChild.value + "</rate>";
			XML += "</Tier>";
			
			if(nextRow == null || nextRow.firstChild.firstChild.value == "")
				break;
				
			currentRow = nextRow;
			nextRow = nextRow.nextSibling;	
		}	
    }
    else
    {
    	XML += "<fund>" + _selectedFund.fund + "</fund>";
    	XML += "<class>" + _selectedFund.classCd + "</class>";
    	if (_aggrLink == "yes")
    	{
    		XML += "<aggrLink>" + document.getElementById("aggrLink").value + "</aggrLink>";
    	}
    	var currentRow = document.getElementById("ratesTable").firstChild.firstChild;
		var nextRow = document.getElementById("ratesTable").firstChild.firstChild.nextSibling;
	
    	
    	while (currentRow != null)
		{		
			XML += "<Tier>";
			XML += "<lower>" + currentRow.firstChild.firstChild.value + "</lower>";
			XML += "<upper>" + currentRow.lastChild.previousSibling.firstChild.value + "</upper>";
			XML += "<rate>" + currentRow.lastChild.firstChild.value + "</rate>";
			XML += "</Tier>";
			
			if(nextRow == null || nextRow.firstChild.firstChild.value == "")
				break;
				
			currentRow = nextRow;
			nextRow = nextRow.nextSibling;	
		}	
    } 
    XML += "<effDate>" + document.getElementById("effDateFld").value + "</effDate>";
    XML += "<stopDate>" + document.getElementById("stopDateFld").value + "</stopDate>";   
       
	XML += "</updFeeIDFund></Data>"
	return (XML);
}



function deleteFeeID()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["ignoreWarnings"]	  = _ignoreWarnings;    
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildDeleteFeeIDXML (popupMode);    
    HTTP.postText( url, function(responseText){postUpdateRequest_callback(responseText, deleteFeeID)}, xml, true );   
}



function buildDeleteFeeIDXML (action)
{ 
	var XML = "<Data><updFeeID>";
	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";
	XML += "<calculationMethod>" + document.getElementById( "calcMethodLabel" ).code + "</calculationMethod>";   
    XML += "<action>delete</action>";    
	XML += "</updFeeID></Data>"
	return (XML);
}



function deleteFund()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["ignoreWarnings"]	  = _ignoreWarnings;
    
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildDeleteFundXML (popupMode);    
    HTTP.postText( url, function(responseText){postUpdateRequest_callback(responseText, deleteFund)}, xml, true );   
}



function buildDeleteFundXML (action)
{ 
	var XML = "<Data><updFeeIDFund>";
	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";   
    XML += "<action>delete</action>";    
	XML += "<fund>" + _selectedFund.parentNode.id + "</fund>";
	XML += "<class>" + _selectedFund.parentNode.classCd + "</class>";
	XML += "</updFeeIDFund></Data>"
	return (XML);
}



function deleteRate()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["ignoreWarnings"]	  = _ignoreWarnings;
    
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildDeleteRateXML (popupMode);
	unselectFund( _selectedFund.uuid );    
    HTTP.postText( url,  function(responseText){postUpdateRequest_callback(responseText, deleteRate)}, xml, true );   
}



function buildDeleteRateXML (action)
{ 
	var XML = "<Data><updFeeIDFund>";
	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";   
    XML += "<action>deleterate</action>";    
	XML += "<fund>" + _selectedFund.fund + "</fund>";
	XML += "<class>" + _selectedFund.classCd + "</class>";
    XML += "<effDate>" + _selectedRateSet.effDate + "</effDate>";
    XML += "<stopDate>" + _selectedRateSet.stopDate + "</stopDate>";   
	XML += "</updFeeIDFund></Data>"
	return (XML);
}



function unstopFund()
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]    		  = _envName;
    paramMap["dateFormat"] 		  = _dateFormat;
    paramMap["ignoreWarnings"]	  = _ignoreWarnings;    
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildUnstopFundXML();		  
    HTTP.postText( url, function( responseText ){ postUpdateRequest_callback( responseText, deleteRate ) }, xml, true );   
}



function buildUnstopFundXML()
{	
	var XML = "<Data><updFeeIDFund>";
	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";   
    XML += "<action>unstopfund</action>";    
	XML += "<fund>" + _selectedFund.fund + "</fund>";
	XML += "<class>" + _selectedFund.classCd + "</class>";
	
	var rateSetTable = UTL.getElem( "rateSetTable_" + _selectedFund.uuid + "_1" );
	XML += "<effDate>" + rateSetTable.effDate + "</effDate>";
	XML += "<stopDate>" + rateSetTable.stopDate + "</stopDate>";	       
	XML += "</updFeeIDFund></Data>"	
	return (XML);
}



function postUpdateRequest_callback( responseText, initialFunction )
{ 
    var responseXML = XML.parseToXML( responseText );
    var errorNode = XML.getNode( "/responseContents/error", responseXML );    
    
    if ( errorNode )
    {	
    	var errorSeverity = XML.getNode( "/responseContents/errorSeverity", responseXML );
    	if ( UTL.trimString( errorSeverity.firstChild.nodeValue ) == "warning")
    	{
    		if (confirm("Warning: " +  UTL.trimString( errorNode.firstChild.nodeValue ) + ". \nWould you like to continue?" ))
			{
				_ignoreWarnings = "yes";
				initialFunction();
				_ignoreWarnings = "no";  
			}  		
    	}    	
    	else
    	{
        	alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
    	}
        return;
    }    
    else
    {
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        

        // clear the current inner html
        UTL.getElem("fund_ListDiv").innerHTML = "";
        // set the inner html to the html contents within updatedHTMLNode
        // note: the html contents are treated as xml within the xml dom
        UTL.getElem("fund_ListDiv").innerHTML = updatedHTMLNode.firstChild.xml;
        
        maintainFundHeight();
        closeRatePopup();
        
        if ( _selectedFund )
        {
        	unselectFund( _selectedFund.uuid );
        }
    } 
}




function getFundSearchURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]              = _vCZ;
    paramMap["jobname"]         = "General_FundSuggest";
    paramMap["companyCode"]     = _companyCode;
    paramMap["ruserId"]         = _ruserId;    
    paramMap["sessionId"]       = _sessionId;
    paramMap["envName"]       	= _envName;
    paramMap["dateFormat"] 	    = _dateFormat;
    paramMap["showAllClassRecords"]  = "no";        
    
    if ( nextRecNum )
    {
        paramMap["startRecordNum"] = nextRecNum;    
    }
    paramMap["searchData"] = searchStr;
       
    return HTTP.buildURL( _vServletPath, paramMap );
}










// ******************* FUND HISTORY (separate from other history) ****************

function sendFundHistoryRequest( startDate, endDate )
{	
	var paramMap = {};    
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
	
	var xml = "<Data><FeeParmHistoryReq>";
	xml += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>"
	if ( startDate && endDate )
	{
		xml += "<startDate>" + startDate + "</startDate>";
		xml += "<endDate>" + endDate + "</endDate>";
	}
	xml += "</FeeParmHistoryReq></Data>";
	
    HTTP.postText( url, fundHistoryRequest_callback, xml, true );
}



function fundHistoryRequest_callback( responseText )
{		
	var responseXML = XML.parseToXML( responseText );	
	
    var errorNode = XML.getNode( "/responseContents/error", responseXML );    
    if ( errorNode )
    {
        alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
        // clear the current inner html
    	UTL.getElem("fundHistory_contents").innerHTML = "";
        return;
    }
	
	var responseNode = XML.getNode( "/responseContents", responseXML );        

    // clear the current inner html
    UTL.getElem("fundHistory_contents").innerHTML = "";
    // set the inner html to the html contents within updatedHTMLNode
    // note: the html contents are treated as xml within the xml dom
    UTL.getElem("fundHistory_contents").innerHTML = responseNode.firstChild.xml;
        	
	displayFundHistoryPopup();	
}



function filterFundHistory()
{
	var startDate = UTL.getElem( "fundHistoryFilter_startDateFld" ).value;
	var endDate = UTL.getElem( "fundHistoryFilter_endDateFld" ).value;
	
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
	
	sendFundHistoryRequest( startDate, endDate );
	// display "refreshing" in hisotry contents
	UTL.getElem( "fundHistory_contents" ).innerHTML = "";
	UTL.getElem( "fundHistory_contents" ).innerHTML = "Refreshing ...";
}



function displayFundHistoryPopup()
{
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	var popupDiv = UTL.getElem( "fundHistoryDiv" );
	popupDiv.style.display = "block";	
	var popupIframe = UTL.getElem( "fundHistoryIframe" );
	popupIframe.style.display = "block";
}



function closeFundHistoryPopup()
{
	UTL.getElem( "disableDiv" ).style.display = "none";
	
	var popupDiv = UTL.getElem( "fundHistoryDiv" );
	popupDiv.style.display = "none";	
	var popupIframe = UTL.getElem( "fundHistoryIframe" );
	popupIframe.style.display = "none";
	// clear filters date fields
	UTL.getElem( "fundHistoryFilter_startDateFld" ).value = "";;
	UTL.getElem( "fundHistoryFilter_endDateFld" ).value = "";
}


//************** update history (excluding FUND) ***********//
function sendHistoryRequest( historyType, startDate, endDate )
{
 	var paramMap = {};    
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFeeRebate_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
	
	var xml = "<Data><HistoryReq>";
	xml += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";
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








