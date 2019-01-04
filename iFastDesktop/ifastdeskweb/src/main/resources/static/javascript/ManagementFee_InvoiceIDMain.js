
var ignoreWarnings = "no";
var actionParameter = "add";

function maintainFundHeight()
{
	var fundDiv = document.getElementById("fundsDiv");
	var scrollableFundDiv = document.getElementById("scrollableFundsDiv");

	if(scrollableFundDiv.offsetHeight >= _maxWindowSize)
	{
		fundDiv.style.height = _maxWindowSize;
		fundDiv.style.overflowY = "scroll";
	}
	else
	{		
		fundDiv.style.height = scrollableFundDiv.offsetHeight;
		fundDiv.style.overflowY = "auto";
	}
}

function handleInvoiceActionChange ()
{	
	
	if ( document.getElementById( "gbcd" ).value != "Bad" )
	{		
		switch (document.getElementById("actionSelect").value)
		{
			case("Update"):
			{
				
				setAllFieldsTo(false);					
				document.getElementById("stopDate").disable(true);					
				
				actionParameter = "update";
				
				break;
			}
			case("Correct"):
			{
				setAllFieldsTo(false);
				document.getElementById("effectiveDate").disable(true);
				document.getElementById("stopDate").disable(true);
				
				actionParameter = "correct";
				
				break;
			} 
			case("Stop"):
			{
				//Change only stop date
				setAllFieldsTo(true);
				document.getElementById("stopDate").disable (false);
				
				actionParameter = "stop";
						
				break;
			}
			case("Delete"):
			{	
				
				if(confirm("Are you sure you want to delete this invoice?"))
				{
					actionParameter = "delete";
					deleteInvoiceID();
				}
				break;
			}
		}
	}
	else
	{
		alert( "Cannot update a 'Bad' record" );
		document.getElementById("actionSelect").selectedIndex = -1;
	}
}

function modifyInvoiceID()
{			
	setAllFieldsTo (false);			
}

function deleteInvoiceID()
{
	document.getElementById("invoiceTable").style.display = "block";
	document.getElementById("effectiveDateField").innerHTML = document.getElementById("effectiveDateInput").value;
	document.getElementById("stopDateField").innerHTML = document.getElementById("stopDateInput").value;

	//document.getElementById("grayDiv").style.display = "none";	
}

function setAllFieldsTo(state)
{	
	
	if(_screenMode == "add")
	{
		document.getElementById("invoiceIDCode").disabled = state;
	}	
	
	document.getElementById("invoiceName").disabled = state;
	document.getElementById("effectiveDate").disable(state);
	document.getElementById("stopDate").disable (state);			
	//document.getElementById("billEntName").disabled = state;
	document.getElementById("addrLine1").disabled = state;
	document.getElementById("addrLine2").disabled = state;
	document.getElementById("addrLine3").disabled = state;
	document.getElementById("addrLine4").disabled = state;
	document.getElementById("city").disabled = state;
	document.getElementById("country").disabled = state;
	document.getElementById("pstl").disabled = state;
	document.getElementById("delivName1").disabled = state;
	document.getElementById("delivName2").disabled = state;
	document.getElementById("frequency").disabled = state;
	document.getElementById("chargeOption").disabled = state;
	document.getElementById("gstApplies").disabled = state;
	document.getElementById("brandingType").disabled = state;			
	
}

function deleteInvoiceID()
{   
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "ManagementFee_InvoiceIDProcess";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]       	  = _envName;
    paramMap["dateFormat"] 	      = _dateFormat;
    paramMap["ignoreWarnings"]    = ignoreWarnings;
           
    var url = HTTP.buildURL( _vServletPath, paramMap );
	
	var xml = buildDeleteInvoiceIDXML ();
    //alert(xml);
    HTTP.postText( url, function(responseText){postUpdateRequest_callback(responseText, deleteInvoiceID)}, xml, true );   
}

function buildDeleteInvoiceIDXML ()
{
	var XML = "<Data>";
    XML += "<action>" + actionParameter + "</action>";    
	XML += "<holdingEntityID>" + document.getElementById("holdingEntityID").value + "</holdingEntityID>";
	XML += "<billInstrID>" + document.getElementById("billInstrID").value + "</billInstrID>";
	XML += "<invoiceID>" + document.getElementById("invoiceIDCode").value + "</invoiceID>";
	XML += "<version>" + document.getElementById("version").value + "</version>";
	XML += "</Data>"
	return (XML);
}


function updateInvoiceID()
{   
	if ( !document.getElementById( "actionSelect" )  || document.getElementById("actionSelect").value != "" )   	 			
	{
		var paramMap = {}
	    paramMap["cz"]                = _vCZ;
	    paramMap["jobname"]           = "ManagementFee_InvoiceIDProcess";    
	    paramMap["companyCode"]       = _companyCode;
	    paramMap["ruserId"]           = _ruserId;
	    paramMap["sessionId"]         = _sessionId;
	    paramMap["envName"]       	  = _envName;
	    paramMap["dateFormat"] 	      = _dateFormat;
	    paramMap["ignoreWarnings"]    = ignoreWarnings;
	           
	    var url = HTTP.buildURL( _vServletPath, paramMap );
		
		var xml = buildInvoiceIDXML();		
	    //alert(xml);
	    HTTP.postText( url, function(responseText){postUpdateRequest_callback(responseText, updateInvoiceID)}, xml, true );   
	}
	else
	{
		alert( "Please select an action to perform" ); 
		
	}
}

function buildInvoiceIDXML ()
{
	
	var gstApplies = "no";
	if 	(document.getElementById("gstApplies").checked == true)
		gstApplies = "yes";
	
	var XML = "<Data>";
    XML += "<action>" + actionParameter + "</action>";    
	XML += "<holdingEntityID>" + encode( document.getElementById("holdingEntityID").value ) + "</holdingEntityID>";
	XML += "<billInstrID>" + encode( document.getElementById("billInstrID").value ) + "</billInstrID>";
	XML += "<invoiceID>" + encode( document.getElementById("invoiceIDCode").value ) + "</invoiceID>";
	XML += "<invoiceName>" + encode( document.getElementById("invoiceName").value ) + "</invoiceName>";
	XML += "<frequencyCode>" + encode( document.getElementById("frequency").options[document.getElementById("frequency").selectedIndex].value ) + "</frequencyCode>";
	XML += "<effDate>" + encode( document.getElementById("effectiveDate").value ) + "</effDate>";
	XML += "<stopDate>" + encode( document.getElementById("stopDate").value ) + "</stopDate>";
	XML += "<addressLine1>" + encode( document.getElementById("addrLine1").value )+ "</addressLine1>";
	XML += "<addressLine2>" + encode( document.getElementById("addrLine2").value ) + "</addressLine2>";
	XML += "<addressLine3>" + encode( document.getElementById("addrLine3").value ) + "</addressLine3>";
	XML += "<addressLine4>" + encode( document.getElementById("addrLine4").value ) + "</addressLine4>";
	XML += "<city>" + encode( document.getElementById("city").value ) + "</city>";
	XML += "<province>" + encode( document.getElementById("country").options[document.getElementById("country").selectedIndex].value ) + "</province>";
	XML += "<postalCode>" + encode( document.getElementById("pstl").value ) + "</postalCode>";
	XML += "<chargeOption>" + encode( document.getElementById("chargeOption").options[document.getElementById("chargeOption").selectedIndex].value ) + "</chargeOption>";	
	XML += "<gstApplies>" + gstApplies + "</gstApplies>";
	XML += "<brandingType>" + encode( document.getElementById("brandingType").options[document.getElementById("brandingType").selectedIndex].value ) + "</brandingType>";
	XML += "<delivName1>" + encode( document.getElementById("delivName1").value ) + "</delivName1>";  
	XML += "<delivName2>" + encode( document.getElementById("delivName2").value ) + "</delivName2>";
	XML += "<version>" + encode( document.getElementById("version").value ) + "</version>";
	XML += "</Data>"
	return (XML);
}


function postUpdateRequest_callback( responseText, initialFunction )
{ 
	
    var responseXML = XML.parseToXML( responseText );
    var errorNode = XML.getNode( "/responseContents/error", responseXML );
	
	//alert(errorNode + "    " + UTL.trimString( errorNode.firstChild.nodeValue ));
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
    else
    {	
    	parent.closeInvoiceIDScreen( true );
    	//_screenMode = "modify";
    	//document.getElementById("actionSelect").disabled = true;
    	parent.closeInvoiceIDScreen( true );
    }
    /*else
    {
        var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
        
        // clear the current inner html
        UTL.getElem("scrollableFundsDiv").innerHTML = "";
        // set the inner html to the html contents within updatedHTMLNode
        // note: the html contents are treated as xml within the xml dom
        
        UTL.getElem("scrollableFundsDiv").innerHTML = updatedHTMLNode.firstChild.xml;
        
        closeRatePopup();
      
    } */
}

function convertToAddMode()
{
	
}
	
function setTextFldValues( _textFldValueMap )
{
	for ( var i in _textFldValueMap )
	{
		UTL.getElem( i ).value = _textFldValueMap[i];
	}
}

function encode( text )
{
	var encodedText = text;
	// note: order we do the following is important!!
	encodedText = encodedText.replace( /&/g, "&amp;" );	
	encodedText = encodedText.replace( /</g, "&lt;" );
	encodedText = encodedText.replace( />/g, "&gt;" );	
	return encodedText;	 
}

function unencode( text )
{
	var unencodedText = text;
	// note: order we do the following is important!!
	unencodedText = unencodedText.replace( /&lt;/g, "<" );
	unencodedText = unencodedText.replace( /&gt;/g, ">" );
	unencodedText = unencodedText.replace( /&amp;/g, "&" );	
		
	return unencodedText;	 
}  		
	

