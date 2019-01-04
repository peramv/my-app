var popupType = null;
var popupMode = null;
var ignoreWarnings = "no";


// ********************* GENERIC ************************
function toggleDiv( divId )
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



function updateGrayDiv()
{
     grayDiv.style.height = parseInt(document.getElementById("fundsFieldset").clientHeight);
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










// **************** FEE ID INFORMATION ****************** 

function modifyFeeIDInfo()
{
	modifyDescription();	
	document.getElementById("modifiedDescInput").disabled = false;	
}



function updateFundInformation()
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]    		  = _envName;
    paramMap["dateFormat"] 		  = _dateFormat;
    paramMap["ignoreWarnings"]	  = ignoreWarnings;
    paramMap["holdingEntityID"]	  = document.getElementById("holdingEntityID").value;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
	
	var xml = buildFundInfoXML ();
    HTTP.postText( url,  function(responseText){postUpdateRequest_callback(responseText, updateFundInformation)}, xml, true );    
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
	XML += "<description>" + document.getElementById("modifiedDescInput").value + "</description>";            
   	XML += "</updFeeID></Data>"
   	
	return (XML);
}



function deleteFeeID()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]   		  = _envName;
    paramMap["dateFormat"] 		  = _dateFormat;
    paramMap["ignoreWarnings"]	  = ignoreWarnings;
    paramMap["holdingEntityID"]	  = document.getElementById("holdingEntityID").value;
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildDeleteFeeIDXML (popupMode);    
    HTTP.postText( url, function(responseText){postUpdateRequest_callback(responseText, deleteFeeID, true)}, xml, true );   
}



function buildDeleteFeeIDXML (action)
{	 
	var XML = "<Data><updFeeID>";
	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";   
    XML += "<action>delete</action>";   
   	XML += "<version>" + _feeModelVersion + "</version>"; 
	XML += "</updFeeID></Data>"
	return (XML);
}



function modifyDescription()
{
	document.getElementById("modifyDescriptionTable").style.display = "block";	
	document.getElementById("modifiedDescInput").value = originalDescription;	
	document.getElementById("descriptionTable").style.display = "none";
	updateGrayDiv();
	document.getElementById("grayDiv").style.display = "block";
		
	if ( _screenMode == "add" )
	{
		UTL.getElem( "closeDescBtn" ).style.display = "none";
	}
	else
	{
		UTL.getElem( "closeDescBtn" ).style.display = "inline";	
		UTL.getElem( "feeIDCodeInput" ).disabled = true;
	} 	
	
	UTL.getElem( "modifyDescBtn" ).style.display = "none";
	UTL.getElem( "deleteDescBtn" ).style.display = "none";
	
}



function saveDescription()
{
	updateFundInformation();
}



function closeDescription()
{
	UTL.getElem( "descriptionTable").style.display = "block";
	UTL.getElem( "modifyDescriptionTable").style.display = "none";
	UTL.getElem( "grayDiv").style.display = "none";
	
	if (_allowUpdates == "yes")
	{
		UTL.getElem( "modifyDescBtn").style.display = "inline";
		UTL.getElem( "deleteDescBtn").style.display = "inline";
	}
}








// ******************* FUNDS *********************

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
		// init the fund fld of the popup, and then disable
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
			var ratesFundFld = UTL.getElem( "ratesFund" );
			ratesFundFld.initialValue = fund.uuid;
			SuggestFieldManager.reInit( ratesFundFld );
			ratesFundFld.disabled = true;
			document.getElementById("effDateFld").disable(true);
		}
		else 
		{						
			document.getElementById("effDateFld").disable(false);			
			document.getElementById("ratesFund").disabled = false;
		}
	}		
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
	//var fundDiv = fund;
	
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
	
		while ( currentRow != null )
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
	
	UTL.getElem( "ratesTableHeader" ).style.display = "block";
	
	for (each in _defaultTiers)
	{
		addRow();
		addedRow = document.getElementById("ratesTable").firstChild.lastChild;
		addedRow.firstChild.firstChild.value = _defaultTiers[each].lower;
		addedRow.lastChild.previousSibling.firstChild.value = _defaultTiers[each].upper;
	}
}



function addRow( modifiable )
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



function handleActionSelectChange ()
{	
	var action = UTL.getElem( "actionSelect").options[UTL.getElem( "actionSelect").selectedIndex].value;
	
	switch ( action )
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
				var stopDateFld = UTL.getElem( "stopDateFld" );
				stopDateFld.disable( false );
				loadFundModifyScreen ("stopfund", "fund", false, _selectedFund);
				populateModifyScreen ("fund", _selectedFund, false);
				
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
		
	updateActionMenu();
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
  	
  	updateActionMenu();
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
	
	updateActionMenu();	
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
  	
  	updateActionMenu();
}



function openRatePopup()
{
	document.getElementById("disableDiv").style.display = "block";	
	var div = document.getElementById("ratesDiv");
	div.style.display = "block";	
	
	UTL.getElem( "ratesIframe" ).style.display = "block";
}



function closeRatePopup()
{
	deleteAllRows();
	
	if (_aggrLink == "yes")
	document.getElementById("aggrLink").value = "";
	document.getElementById("effDateFld").value = "";
	document.getElementById("stopDateFld").value = "";
	UTL.getElem( "ratesIframe" ).style.display = "none";
	document.getElementById("ratesDiv").style.display = "none";
	document.getElementById("disableDiv").style.display = "none";	
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



function updateActionMenu()
{
	var actionSelect = UTL.getElem( "actionSelect" );
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
    paramMap["jobname"]           = "ManagementFee_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]    		  = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    paramMap["ignoreWarnings"]	  = ignoreWarnings;
    paramMap["holdingEntityID"]	  = document.getElementById("holdingEntityID").value;
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildFeeIDXML( popupMode );	   
    HTTP.postText( url,  function(responseText){postUpdateRequest_callback(responseText, updateFeeID)}, xml, true );   
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
    	XML += "<aggrLink>" + document.getElementById("aggrLink").value + "</aggrLink>";
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



function deleteFund()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]    		  = _envName;
    paramMap["dateFormat"] 		  = _dateFormat;
    paramMap["ignoreWarnings"]	  = ignoreWarnings;
    paramMap["holdingEntityID"]	  = document.getElementById("holdingEntityID").value;
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	var xml = buildDeleteFundXML (popupMode);    
    HTTP.postText( url, function(responseText){postUpdateRequest_callback(responseText, deleteFund)}, xml, true );   
}



function buildDeleteFundXML (action)
{	
	var XML = "<Data><updFeeIDFund>";
	XML += "<feeModelCode>" + document.getElementById("feeIDCode").innerHTML + "</feeModelCode>";   
    XML += "<action>delete</action>";    
	XML += "<fund>" + _selectedFund.fund + "</fund>";
	XML += "<class>" + _selectedFund.classCd + "</class>";
	XML += "</updFeeIDFund></Data>"
	return (XML);
}



function deleteRate()
{   	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]    		  = _envName;
    paramMap["dateFormat"] 		  = _dateFormat;
    paramMap["ignoreWarnings"]	  = ignoreWarnings;
    paramMap["holdingEntityID"]	  = document.getElementById("holdingEntityID").value;
           
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
    paramMap["jobname"]           = "ManagementFee_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]    		  = _envName;
    paramMap["dateFormat"] 		  = _dateFormat;
    paramMap["ignoreWarnings"]	  = ignoreWarnings;
    paramMap["holdingEntityID"]	  = document.getElementById("holdingEntityID").value;
           
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



// request call back - handles both fund actions, and fee id updates
function postUpdateRequest_callback( responseText, initialFunction, closeScreen )
{ 

    var responseXML = XML.parseToXML( responseText );
    //prompt( "", responseText );
    var errorNode = XML.getNode( "/responseContents/error", responseXML );
    
    if ( errorNode )
    {	
    	var errorSeverity = XML.getNode( "/responseContents/errorSeverity", responseXML );
    	if ( UTL.trimString( errorSeverity.firstChild.nodeValue ) == "warning")
    	{
    		if (confirm("Warning: " +  UTL.trimString( errorNode.firstChild.nodeValue ) + ". \nWould you like to continue?" ))
			{
				ignoreWarnings = "yes";
				initialFunction();
				ignoreWarnings = "no";  
			}  		
    	}    	
    	else
    	{
        	alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
    	}
        return;
    }
    else if (document.getElementById("modifyDescriptionTable").style.display == "block")
    {
    	if(_screenMode == "add")
			UTL.getElem( "feeIDCode").innerHTML = document.getElementById("feeIDCodeInput").value;
		UTL.getElem( "descriptionTable").style.display = "block";
		UTL.getElem( "descriptionField").innerHTML = UTL.getElem( "modifiedDescInput").value;
		originalDescription = UTL.getElem( "modifiedDescInput").value;
		
		UTL.getElem( "modifyDescriptionTable").style.display = "none";
		UTL.getElem( "grayDiv").style.display = "none";	
		
		if(_allowUpdates == "yes")
		{		
			UTL.getElem( "modifyDescBtn").style.display = "inline";
			UTL.getElem( "deleteDescBtn").style.display = "inline";
		}
		
		_feeModelVersion++;
		
		_screenMode = "modify";
		document.getElementById("actionSelect").disabled = false;
		
		UTL.getElem( "fundsFieldset" ).style.display = "block";
    }
    else
    {
    	var refreshNode = XML.getNode( "/responseContents/refreshNode", responseXML );    	
    	if (refreshNode.firstChild.xml == "yes")
    		document.location.reload();
    	
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

    if(closeScreen)
    	parent.closeFeeIDScreen( true );

}



function getFundSearchURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]         = _vCZ;
    paramMap["jobname"]    = "General_FundSuggest";
    paramMap["ruserId"]    = _ruserId;
    paramMap["sessionId"]  = _sessionId;
    paramMap["envName"]    = _envName;
    paramMap["dateFormat"] = _dateFormat;
    paramMap["showAllClassRecords"]  = "no";
    
    if ( nextRecNum )
    {
       paramMap["startRecordNum"] = nextRecNum;        
    }
    paramMap["searchData"] = searchStr;
     
    return HTTP.buildURL( _vServletPath, paramMap );        
}






// ****************** HISTORY **********************

function sendFundHistoryRequest( startDate, endDate )
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_FeeIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    
    var url = HTTP.buildURL( _vServletPath, paramMap );
	
	var xml = "<Data><FeeParmHistoryReq>";
	xml += "<feeModelCode>" + UTL.getElem( "feeIDCode" ).innerHTML + "</feeModelCode>"
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
        	
	displayHistoryPopup();	
}



function filterFundHistory()
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
	
	sendFundHistoryRequest( startDate, endDate );
	// display "refreshing" in hisotry contents
	UTL.getElem( "fundHistory_contents" ).innerHTML = "";
	UTL.getElem( "fundHistory_contents" ).innerHTML = "Refreshing ...";
}



function displayHistoryPopup()
{
	UTL.getElem( "disableDiv" ).style.display = "block";
	
	var popupDiv = UTL.getElem( "fundHistoryDiv" );
	popupDiv.style.display = "block";	
	var popupIframe = UTL.getElem( "fundHistoryIframe" );
	popupIframe.style.display = "block";
		
}



function closeHistoryPopup()
{
	UTL.getElem( "disableDiv" ).style.display = "none";
	
	var popupDiv = UTL.getElem( "fundHistoryDiv" );
	popupDiv.style.display = "none";	
	var popupIframe = UTL.getElem( "fundHistoryIframe" );
	popupIframe.style.display = "none";
	
	// clear filters date fields
	UTL.getElem( "historyFilter_startDateFld" ).value = "";;
	UTL.getElem( "historyFilter_endDateFld" ).value = "";
}
