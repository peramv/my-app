/**
 *
 *  -------------------------------------------------------------------------
 *                                 Copyright
 *
 *               International Financial Data Services Limited 2006
 *                            All rights reserved.
 *
 *  No part of this document may be reproduced, stored in a retrieval system,
 *  or transmitted, in any form or by any means, electronic, mechanical,
 *  photocopying, networking or otherwise, without the prior written permission
 *  of International Financial Data Services Limited. The computer system, procedures,
 *  data bases, and programs created and maintained by International Financial Data
 *  Services Limited are proprietary in nature and as such are confidential.
 *  Any unauthorised use, misuse, or disclosure of such items or information
 *  may result in civil liabilities and may be subject to criminal penalties
 *  under the applicable laws.
 *  -------------------------------------------------------------------------
 *
*/
var requestURL = "";

function loading()
{
	
  	/*var servletPath = document.getElementById("fldServletPath").value;
	var cz = document.getElementById("fldCZ").value;
	var companyCode = document.getElementById("fldCompanyCode").value;
	var envName = document.getElementById("fldEnvName").value;
	var ruserid = document.getElementById("fldRUserId").value;
	var sessionId = document.getElementById("fldSessionId").value;*/

	_paymentBatchList = new Grid('paymentBatchTable');
	_batchDetailsList = new Grid('batchDetailsTable');
	
	//alert(_paymentBatchList.getRow(1));
	if (searchWithResults == "yes" )
	{
		//clickFn(_paymentBatchList.getRow(1));
		_paymentBatchList.setOnRowClickFunction(clickFn);
	}	
}

function sendResetCall()
{	
	hideLoadingDisplay();
	_paymentBatchList.deleteAllRows();
	_batchDetailsList.deleteAllRows();
	
	document.getElementById("counterDiv").innerHTML = "0 - 0 of 0";
	document.getElementById("batchDetailCounterDiv").innerHTML = "0 - 0 of 0";
	
	document.getElementById("btnPrevPayments").disabled = true;
	document.getElementById("btnNextPayments").disabled = true;
	document.getElementById("btnPrevBatchDetails").disabled = true;
	document.getElementById("btnNextBatchDetails").disabled = true;
	document.getElementById("generateBaffButton").disabled = true;	
}


function sendSearchCall(x, y)
{
    _paymentBatchList.deleteAllRows();
    showLoadingDisplay("paymentBatchLoadingDiv"); 
  
    requestURL = buildBaseURL("PaymentRelease_BatchList");
    
	requestURL = appendParam(requestURL, "searchType", document.getElementById("searchType").value);
	requestURL = appendParam(requestURL, "rangeStart", x);
	requestURL = appendParam(requestURL, "requestRangeNum", y);
	requestURL = appendParam(requestURL, "fromDate", document.getElementById("fromDate").value);
	requestURL = appendParam(requestURL, "toDate", document.getElementById("toDate").value);
	
	if (document.getElementById("searchType").value == "paymentFor")
	{
		requestURL = appendParam(requestURL, "searchValue", document.getElementById("paymentFor").value);
		requestURL = appendParam(requestURL, "batchStatus", document.getElementById("batchStatus").value);
	}
	else
	{
		requestURL = appendParam(requestURL, "searchValue", document.getElementById("batchValue").value);
	}
	
	callJob(requestURL, searchCallEval);
	/*var parameters = "";			 
	_httpRequestModify = new ActiveXObject("MSXML2.XMLHTTP");					
	_httpRequestModify.open("POST", url + parameters, true);
	_httpRequestModify.onreadystatechange = handleSearchCall;	
	_httpRequestModify.send();	*/
}

function searchCallEval ()
{
   if ( _httpRequest.readyState == 4)
    {
        if( _httpRequest.status == 200)
        {
            try
            {
                var js = _httpRequest.responseText;
                js = js.substring( js.indexOf( '<responseJS>' ) + 12, js.indexOf( '</responseJS>' ) );
                eval(js);
                _paymentBatchList.setOnRowClickFunction(clickFn);
            }
            catch (e)
            {
                alert("ERROR : " + e.description + " ");
            }
        }
        else
        {
            prompt( 'got response error - ', _httpRequest.responseText );
        }
    }	
}

function clickFn(row)
{
	
	if(_paymentBatchList.getRowCount() > 1)
	{
		_paymentBatchList.highlightRow(row);		
		currentRowBatch = row.rowBatchId;
		currentRowModDate = row.modDate;
        currentRowProcDate = row.procDate;
        currentRowModUser = row.modUser;
        currentRowUserName = row.userName;
		
    	sendBatchPaymentCall(row.rowBatchId, 1, recordsPerPage);
    	
    	if (row.rowStatus.toLowerCase() == "o" && generateBaffPermission == "yes")
    	{
    		document.getElementById("generateBaffButton").disabled = false;
    	}
    	else
    	{
    		document.getElementById("generateBaffButton").disabled = true;
    	}
	}	
}

function sendBatchPaymentCall(batchId, x, y)
{
	
	_batchDetailsList.deleteAllRows();
	showLoadingDisplay("paymentBatchDetailLoadingDiv"); 

	requestURL = buildBaseURL("PaymentRelease_BatchPaymentList");
	requestURL = appendParam(requestURL, "searchType", "batchid");
	requestURL = appendParam(requestURL, "searchValue", currentRowBatch);
	requestURL = appendParam(requestURL, "paymentFor", document.getElementById("paymentFor").options[document.getElementById("paymentFor").selectedIndex].value);
	requestURL = appendParam(requestURL, "fromDate", document.getElementById("fromDate").value);
	requestURL = appendParam(requestURL, "toDate", document.getElementById("toDate").value);
	requestURL = appendParam(requestURL, "rangeStart", x);
	requestURL = appendParam(requestURL, "rangeEnd", y);
	
	
	callJob(requestURL, batchPaymentEval);
}

function batchPaymentEval ()
{
   if ( _httpRequest.readyState == 4)
    {
        if( _httpRequest.status == 200)
        {
            try
            {
                var js = _httpRequest.responseText;
                js = js.substring( js.indexOf( '<responseJS>' ) + 12, js.indexOf( '</responseJS>' ) );
                eval(js);
                
                //clickFn(_paymentBatchList.getRow(1));
                _batchDetailsList.setOnRowClickFunction(highlightRow);
            }
            catch (e)
            {
                alert("ERROR : " + e.description + " ");
            }
        }
        else
        {
            prompt( 'got response error - ', _httpRequest.responseText );
        }
    }	
}

 function highlightRow(row)
{
  _batchDetailsList.highlightRow(row);
}

function sendScheduleCall()
{	
	requestURL = buildBaseURL("PaymentRelease_Schedule");
	requestURL = appendParam(requestURL, "batchId", currentRowBatch);
	document.location = (requestURL);
}

function submitSchedule()
{
        var runNow = "no";
        
        if (document.getElementById("runNow").checked == true)
        	runNow = "yes";
        	
        requestURL = buildBaseURL("PaymentRelease_SubmitSchedule");
        requestURL = appendParam(requestURL, "runOn", document.getElementById("dateField").value);
        requestURL = appendParam(requestURL, "runTime", document.getElementById("timeField").value);
        requestURL = appendParam(requestURL, "runNow", runNow);
        requestURL = appendParam(requestURL, "batchId", document.getElementById("batchId").value);
        
        callJobAndEval(requestURL);
        
        
        
}







