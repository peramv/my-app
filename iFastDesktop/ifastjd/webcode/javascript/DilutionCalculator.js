var _transCount = null;
var _disableDiv = null;
var _processingDiv = null;


/**
 * intialize screen elements
 */
function initDilutionCalc()
{
	_transCount = 0;
		
	UTL.getElem( "transTableDiv" ).onscroll = scrollHandler
	UTL.getElem( "transTable" ).lastChild.appendChild( buildNoRecordsRow() );

	// add evt handler to the Add Trans btn		
	EvtHandler.add( UTL.getElem( "btnAddTrans" ), "click", sendAddTransRequest );		
		
	// add evt handler to the clear btn
	EvtHandler.add( UTL.getElem( "btnClearFields" ), "click", clearAllInputs );
	
	// add evt handler to the clear btn
	EvtHandler.add( UTL.getElem( "btnClearTrans" ), "click", clearTrans );
	
	// add evt handler to the calculate btn
	EvtHandler.add( UTL.getElem( "btnCalcDilution" ), "click", sendCalcRequest );
	
	// build divs for "showProcessing"
	_disableDiv = buildDisableDiv();
	_processingDiv = buildProcessingDiv();	
}     



/**
 * build the page disable div
 */
function buildDisableDiv()
{
	var d = document.body.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";	
	d.style.left = 0;	
	d.style.top = 0;
	d.style.width = "100%";
	d.style.height = "100%";
	d.style.zIndex = 1000;
	d.style.display = "none";
	d.style.background = "black";
	d.style.filter = "alpha(opacity=20)";
	
	return d;	   
}



/**
 * build the "processing" div
 */
function buildProcessingDiv()
{
	var d = document.body.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";	
	d.style.left = 450;	
	d.style.top = 225;
	d.style.width = 200;
	d.style.height = 50;
	d.style.zIndex = 1001;
	d.style.paddingTop = 10;
	d.style.textAlign = "center";
	d.style.display = "none";	
	d.style.border = "2px solid black";
	d.style.background = "white";
	d.style.fontSize = "14px";
	d.style.fontStyle = "italic";
	d.innerHTML = "Processing ...";
	
	return d;
}



/**
 * Do some validating of the AddTrans params
 */
function validateParam( paramMap )
{
	var valid = true;
	
	// check trans num doesn't contain any non-numeric characters
	if ( paramMap["transNum"].match( /\D/g ) )
	{
		alert( "Transaction number is invalid" );
		valid = false;
	}
	
	// check trade date is valid (if entered)
	if ( paramMap["tradeDate"].length > 0 && !isValidDateStr( paramMap["tradeDate"] ) )
	{
		alert( "Trade Date is invalid" );
		valid = false;
	}
	
	// check calc date is valid (if entered)
	if ( paramMap["calcDate"].length > 0 && !isValidDateStr( paramMap["calcDate"] ) )
	{
		alert( "Calculation Date is invalid" );
		valid = false;
	}
	 	
	return valid;
}



/**
 * helper function for checking dateStr is valid, based on _dateFormat
 */
function isValidDateStr( dateStr )
{
	var valid = true;
	
	var datePartArray = [];
	if ( dateStr.indexOf( "/" ) != -1 )
	{	
		datePartArray = dateStr.split( "/" );
	}	
	else
	{
		valid = false;
	}
	
	if ( datePartArray.length > 0 )
	{
		var dayStr = "";
		var monStr = "";
		var yearStr = "";
		switch ( _dateFormat.toUpperCase() )
		{
			case "DMY":
			{
				dayStr	 	= datePartArray[0];
				monStr 		= datePartArray[1];
				yearStr 	= datePartArray[2];
				break;	
			}
			case "MDY":
			{
				dayStr	 	= datePartArray[1];
				monStr 		= datePartArray[0];
				yearStr 	= datePartArray[2];
				break;
			}
			default:
			{
				throw new Error( "Invalid date format" );
			}	
		}
		
		var dayVal = null; 
		if( !dayStr.match(/\D/g) && ( dayStr.length == 2 || dayStr.length == 1 ) )
		{
			var temp = ( dayStr.charAt(0) == "0" ) ? parseInt( dayStr.charAt(1) ) : parseInt( dayStr ); 
			dayVal = ( temp >= 1 ) ? temp : null;
		}		
		
		var monVal = null;		 
		if( !monStr.match(/\D/g) && ( monStr.length == 2 || monStr.length == 1 ) )
		{
			var temp = ( monStr.charAt(0) == "0" ) ? parseInt( monStr.charAt(1) ) : parseInt( monStr );
			monVal = ( temp >= 1 && temp <= 12 ) ?  temp - 1 :  null;
		}
			
		var yearVal = null; 
		if( yearStr && !yearStr.match(/\D/g) && yearStr.length == 4 )
		{
			var temp = parseInt( yearStr );
			yearVal = ( temp >= 1 && temp <= 9999 ) ? temp : null; 
		}
		
		if ( dayVal != null && monVal != null && yearVal != null )
		{				
			if ( dayVal <= getNumDaysInMonth( monVal, yearVal ) )
			{
				valid = true;
			}
			else
			{
				valid = false;
			}
		} 	
	}
	
	return valid;
}



/**
 * helper for determining numDays in a given month/year - used in validating a dateStr
 */
function getNumDaysInMonth( monVal, yearVal )
{
	var max = 31;
	var min = 28;
	var d = new Date( yearVal, monVal, min );
	for ( var i = min + 1; i < max + 1; i++ )
	{
		d.setDate( i )
		if ( d.getMonth() != monVal )
		{
			return i - 1;
		}
	}
	return i;		
}


/**
 * Send Add Trans request
 */
function sendAddTransRequest()
{
    var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "DilutionCalculator_AddTrans";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    // get input values
    var accountFld = UTL.getElem( "suggestAccountField" );    
    paramMap["account"]           = ( accountFld._suggestDataObj ? accountFld._suggestDataObj["acctNum"] : "" );
    
    var fundFld = UTL.getElem( "suggestFundField" );
    paramMap["fundCode"]          = ( fundFld._suggestDataObj ? fundFld._suggestDataObj["fund"] : "" );  
    paramMap["fundClass"]         = ( fundFld._suggestDataObj ? fundFld._suggestDataObj["class"] : "" );
                   
    paramMap["transType"]         = UTL.getElem( "transTypeField" ).value;
    paramMap["transNum"]          = UTL.getElem( "transNumField" ).value;
    paramMap["grossAmt"]          = UTL.getElem( "grossAmountField" ).value;
    paramMap["calcDate"]          = UTL.getElem( "calcDateField" ).value;
    paramMap["tradeDate"]         = UTL.getElem( "tradeDateField" ).value;
    
    // only send if the entered params are valid
    if ( validateParam( paramMap ) )
    {
	    var url = HTTP.buildURL( _vServletPath, paramMap );
	    	    
	    displayProcessing();
	    
	    HTTP.getText( url, sendAddTransRequest_callback );        
    }    	
}



/**
 * AddTrans request call back 
 */
function sendAddTransRequest_callback( responseText )
{	
	hideProcessing();
	
    var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "Dilution Calculator", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}
        return;
    }
    else
    {
    	var dilutionDetailsNodeArray = XML.getNodes( "/responseContents/DilutionTransactions/DilutionDetails", responseXML );
    	var transTable = UTL.getElem( "transTable" );
    	
    	clearAllInputs();
    	
    	// clear the "no records" label 
    	if ( dilutionDetailsNodeArray.length > 0 && _transCount == 0)
    	{
    		transTable.lastChild.removeChild( transTable.lastChild.lastChild );
		}

		_transCount += dilutionDetailsNodeArray.length;			   	    	    	    	
    	for ( var i = 0; i < dilutionDetailsNodeArray.length; i++ )
    	{    		
    		var transTableRow = buildTransTableRow( dilutionDetailsNodeArray[i] );
    		transTableRow.className = ( transTable.lastChild.childNodes.length % 2 == 0 ? "TransRow_even" : "TransRow_odd" );    		    		    	
    		transTable.lastChild.appendChild( transTableRow );    		
    	}    	   	
    }
 
}



/**
 * Generates a row for the Trans table based on a DilutionDetails record returned
 * by the view call 
 */
function buildTransTableRow( dilutionDetailsNode )
{
	var tr = document.createElement( "tr" );
	
	// excl. dheckbox
	var excl_td = tr.appendChild( document.createElement( "td" ) );
	excl_td.className = "TransDataItem";
	var excl_checkbox = document.createElement( "input" );
	excl_checkbox.type = "checkbox";
	excl_checkbox.className = "ExclCheckbox";
	excl_td.appendChild( excl_checkbox );
		
	// account
	 var account_td = tr.appendChild( document.createElement( "td" ) );
	 account_td.className = "TransDataItem";
	 var acctNode = XML.getNode( "acct", dilutionDetailsNode );
	 var acctVal = "";
	 if ( acctNode && acctNode.firstChild )
	 {
	 	acctVal = acctNode.firstChild.nodeValue;
	 }	 
	 account_td.innerHTML = acctVal;
	 tr.acct = acctVal;
	 
	 // fund/class
	 var fundClass_td = tr.appendChild( document.createElement( "td" ) );
	 fundClass_td.className = "TransDataItem";
	 var fundNode = XML.getNode( "fund", dilutionDetailsNode );
	 var classNode = XML.getNode( "class", dilutionDetailsNode );
	 var fundVal = "";
	 var classVal = "";
	 if ( fundNode && fundNode.firstChild && classNode && classNode.firstChild )
	 {
	 	fundVal = fundNode.firstChild.nodeValue;
	 	classVal = classNode.firstChild.nodeValue;
	 }  	 	
	 fundClass_td.innerHTML = fundVal + " " + classVal;
	 tr.fund = fundVal;
	 tr.classCode = classVal;
	 
	 //trans type
	 var transType_td = tr.appendChild( document.createElement( "td" ) );
	 transType_td.className = "TransDataItem";
	 var transTypeNode = XML.getNode( "transType", dilutionDetailsNode );
	 var transTypeVal = "&nbsp;";
	 if ( transTypeNode && transTypeNode.firstChild )
	 {
	 	transTypeVal = transTypeNode.firstChild.nodeValue;
	 	tr.transType = transTypeVal;
	 }
	 transType_td.innerHTML = transTypeVal;
	 
	 // trans num
	 var transNum_td = tr.appendChild( document.createElement( "td" ) );
	 transNum_td.className = "TransDataItem"; 	 	 	 
	 var transNumNode = XML.getNode( "transNum", dilutionDetailsNode );
	 var transNumVal = "&nbsp;";	 
	 if ( transNumNode && transNumNode.firstChild )
	 { 	  	 	
	 	transNumVal = transNumNode.firstChild.nodeValue;
	 	tr.transNum = transNumVal;
	 }
	 transNum_td.innerHTML = transNumVal;
	 
	 // gross amt
	 var grossAmt_td = tr.appendChild( document.createElement( "td" ) );
	 grossAmt_td.className = "TransDataItem";
	 var grossAmtNode = XML.getNode( "tradeGrossAmt", dilutionDetailsNode );
	 var grossAmtVal = "";
	 if ( grossAmtNode && grossAmtNode.firstChild )
	 {
	 	grossAmtVal = grossAmtNode.firstChild.nodeValue;
	 } 	 
	 grossAmt_td.innerHTML = grossAmtVal;
	 tr.grossAmt = grossAmtVal; 
	 	 
	 // units
	 var units_td = tr.appendChild( document.createElement( "td" ) );
	 units_td.className = "TransDataItem";
	 var unitsNode = XML.getNode( "units", dilutionDetailsNode );
	 var unitsVal = ""; 
	 if ( unitsNode && unitsNode.firstChild )
	 {
	 	unitsVal = unitsNode.firstChild.nodeValue;
	 }	 
	 units_td.innerHTML = unitsVal;
	 tr.units = unitsVal;
	 
	 // trade date
	 var tradeDate_td = tr.appendChild( document.createElement( "td" ) );
	 tradeDate_td.className = "TransDataItem";
	 var tradeDateNode = XML.getNode( "tradeDate", dilutionDetailsNode );
	 var tradeDateVal = "";
	 if ( tradeDateNode && tradeDateNode.firstChild )
	 {
	 	tradeDateVal = tradeDateNode.firstChild.nodeValue;
	 }	 
	 tradeDate_td.innerHTML = tradeDateVal;
	 tr.tradeDate = tradeDateVal;
	 
	 // trade rate
	 var tradeRate_td = tr.appendChild( document.createElement( "td" ) );
	 tradeRate_td.className = "TransDataItem";
	 var tradeRateNode =  XML.getNode( "tdRate", dilutionDetailsNode );
	 var tradeRateVal = "";
	 if ( tradeRateNode && tradeRateNode.firstChild )
	 {	
	 	tradeRateVal = tradeRateNode.firstChild.nodeValue;
	 }
	 tradeRate_td.innerHTML = tradeRateVal;
	 tr.tradeRate = tradeRateVal;
	 
	 // calc date
	 var calcDate_td = tr.appendChild( document.createElement( "td" ) );
	 calcDate_td.className = "TransDataItem";
	 var calcDateNode =  XML.getNode( "calcDate", dilutionDetailsNode );
	 var calcDateVal = "";
	 if ( calcDateNode && calcDateNode.firstChild )
	 {	
	 	calcDateVal = calcDateNode.firstChild.nodeValue;
	 }	 
	 calcDate_td.innerHTML = calcDateVal;
	 tr.calcDate = calcDateVal;
	 
	 // calc rate
	 var calcRate_td = tr.appendChild( document.createElement( "td" ) );
	 calcRate_td.className = "TransDataItem";
	 var calcRateAvail = XML.getNode( "calcRateAvail", dilutionDetailsNode ).firstChild.nodeValue;	 
	 if ( calcRateAvail.toLowerCase() == "yes" )
	 {
		var calcRateVal = XML.getNode( "calcRate", dilutionDetailsNode ).firstChild.nodeValue;		
	 	calcRate_td.innerHTML = calcRateVal;
	 	tr.calcRate = calcRateVal;
	 }
	 else
	 {
	 	calcRate_td.innerHTML = "n/a";
	 	tr.calcRate = "n/a";
	 } 
	 
	 // gainLoss date
	 var gainLoss_td = tr.appendChild( document.createElement( "td" ) );
	 gainLoss_td.className = "TransDataItem";
	 var gainLossVal = XML.getNode( "gainLoss", dilutionDetailsNode ).firstChild.nodeValue;
	 gainLoss_td.innerHTML = gainLossVal;
	 tr.gainLoss = gainLossVal;
	 
	 return tr;
}



/**
 * Clear all the input fields 
 */
function clearAllInputs()
{	
    var accountFld = UTL.getElem( "suggestAccountField" );    
	accountFld._suggestDataObj = null;
	accountFld.value = ""; 
    
    var fundFld = UTL.getElem( "suggestFundField" );
    fundFld._suggestDatabObj = null;
    fundFld.value = "";
                   
    UTL.getElem( "transTypeField" ).selectedIndex = -1;
    UTL.getElem( "transNumField" ).value = "";
    UTL.getElem( "grossAmountField" ).value = "";
    UTL.getElem( "calcDateField" ).value = "";
    UTL.getElem( "tradeDateField" ).value = ""; 
}



/**
 * Generates the url for calling the Account Suggest 
 */
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



/**
 * Generates the url for calling the Fund Suggest 
 */
function getFundSearchURL( searchStr, nextRecNum )
{
    var paramMap = {};
    paramMap["cz"]         = _vCZ;
    paramMap["jobname"]    = "General_FundSuggest";
    paramMap["ruserId"]    = _ruserId;
    paramMap["sessionId"]  = _sessionId;
	paramMap["envName"]    = _envName;
    paramMap["showAllClassRecords"]  = "no";
    
    if ( nextRecNum )
    {
       paramMap["startRecordNum"] = nextRecNum;        
    }
    paramMap["searchData"] = searchStr;
     
    return HTTP.buildURL( _vServletPath, paramMap );        
}



/**
 * Updates the total dilution, using user entered Distribution Dilution value. 
 */
function updateTotalDilution()
{
	var distrDilutionFld = UTL.getElem( "results_distrDilutionFld" );
	var distrDilutionFldValue = Number( distrDilutionFld.value );
	var gainLossBeforeDistFld = UTL.getElem( "results_gainLossBeforeDistrFld" );
	var gainLossBeforeDistValue = Number( gainLossBeforeDistFld.innerHTML );
		
	if ( !isNaN( distrDilutionFldValue ) )
	{
		var totalDilutionFld = UTL.getElem( "results_totalDilutionFld" );			
		totalDilutionFld.innerHTML = ( distrDilutionFldValue + gainLossBeforeDistValue ).toFixed( 2 );
	}
	else
	{
		alert( "Gain/Loss incl. Distribution value is not valid" );
	}
}



/**
 * handler function - keeps the transTable header in place when scrolling 
 */
function scrollHandler()
{
	var transTableDiv = UTL.getElem( "transTableDiv" );
	
	var transTable = UTL.getElem( "transTable" );
	transTable.firstChild.firstChild.style.position = "relative";
	transTable.firstChild.firstChild.style.zIndex = 1000;	
	transTable.firstChild.firstChild.style.top = transTableDiv.scrollTop;
}



/**
 * Builds the row to display when no transactions added 
 */
function buildNoRecordsRow()
{
	var tr = document.createElement( "tr" );
	var td = tr.appendChild( document.createElement( "td" ) );
	td.className = "TransDataEmpty"; 
	td.colSpan = "12";
	td.innerHTML = "No Transactions Added";
	
	return tr;
}



/**
 * Removes all the added transaction records, and displays the "noRecords" row 
 */
function clearTrans()
{
	var transTable = UTL.getElem( "transTable" );
	while( transTable.lastChild.lastChild )
	{
		transTable.lastChild.removeChild( transTable.lastChild.lastChild );
	}
	
	transTable.lastChild.appendChild( buildNoRecordsRow() );
	
	_transCount = 0;
	
	resetTotals();
}



/**
 * Resets the totals section 
 */
function resetTotals()
{	    
	UTL.getElem( "results_totalGrossAmtFld" ).innerHTML = ""; 
       	
	UTL.getElem( "results_gainLossBeforeDistrFld" ).innerHTML = "";

    UTL.getElem( "results_distrDilutionFld" ).disabled = true;
   	UTL.getElem( "results_distrDilutionFld" ).value = "";

	UTL.getElem( "results_totalDilutionFld" ).innerHTML = "";
    
    UTL.getElem( "updateTotalDilutionBtn" ).disabled = true;
}



/**
 * sends the calculate request 
 */
function sendCalcRequest()
{
    var requestXMLStr = "";     
         
    if ( _transCount > 0 )
    {    	
	    var transTable = UTL.getElem( "transTable" );
	    var transRowArray = transTable.lastChild.childNodes;
    	for ( var i = 0; i < transRowArray.length; i++ )
    	{
    		var exclCheckbox = transRowArray[i].firstChild.firstChild;     	
    		if ( !exclCheckbox.checked )
    		{
	    		var grossAmtNode = XML.createNodeStr( "grossAmt", transRowArray[i].grossAmt );
	    		var gainLossNode = XML.createNodeStr( "gainLoss", transRowArray[i].gainLoss );
	    		requestXMLStr += XML.createNodeStr( "dilutiontxn", grossAmtNode + gainLossNode );
	    	}
    	}
    	if ( requestXMLStr.length > 0 )
    	{
    		requestXMLStr = XML.createNodeStr( "dilutionCalcRequest", requestXMLStr );
    	}
    }
           
    // only send if there are trans records available (could have all been excluded)
    if ( requestXMLStr.length > 0 )
    {
	    var paramMap = {}
	    paramMap["cz"]                = _vCZ;
	    paramMap["jobname"]           = "DilutionCalculator_Calculate";    
	    paramMap["companyCode"]       = _companyCode;
	    paramMap["ruserId"]           = _ruserId;
	    paramMap["sessionId"]         = _sessionId;
	    paramMap["envName"]           = _envName;
	    paramMap["dateFormat"]        = _dateFormat;
	    
	    var url = HTTP.buildURL( _vServletPath, paramMap );
	    
	    displayProcessing();
	    
	    HTTP.postText( url, sendCalcRequest_callback, requestXMLStr );	
    }
    else
    {
    	alert( "No transaction records are available to calculate dilution." );    	
    }  
}



/**
 * calculate callback function 
 */
function sendCalcRequest_callback( responseText )
{	
	hideProcessing();
	
	var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "Dilution Calculator", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}
        return;
    }
    else
    {   
    	var totGrossAmtNode = XML.getNode( "/responseContents/DilutionTotal/totGrossAmt", responseXML );    	
    	UTL.getElem( "results_totalGrossAmtFld" ).innerHTML = totGrossAmtNode.firstChild.nodeValue; 
        
       	var gainLossNode = XML.getNode( "/responseContents/DilutionTotal/totGainLoss", responseXML );
		UTL.getElem( "results_gainLossBeforeDistrFld" ).innerHTML = gainLossNode.firstChild.nodeValue;

        UTL.getElem( "results_distrDilutionFld" ).disabled = false;
       	UTL.getElem( "results_distrDilutionFld" ).value = "";

		UTL.getElem( "results_totalDilutionFld" ).innerHTML = gainLossNode.firstChild.nodeValue;
        
        UTL.getElem( "updateTotalDilutionBtn" ).disabled = false;
    }	
}



/**
 * disables the screen and displays "processing" msg 
 */
function displayProcessing()
{
	_disableDiv.style.display = "block";
	_processingDiv.style.display = "block";
}



/**
 * re-enables the screen and hides the "processing" msg 
 */
function hideProcessing()
{
	_disableDiv.style.display = "none";
	_processingDiv.style.display = "none";
}