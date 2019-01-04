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

/**
 * Variable Declartion
*/
var _consolidatedList = null;
var _paymentList = null;
var _transactionList = null;
var selectedRow = null;
var transDetailsRow = null;
var listId = null;
var transType = null;
var accountNum = null;
var transNum = null;
var transId = null;
var FundCode = null;
var ClassCode = null;
var _btnSearch = null;
var requestURL = "";
var _httpRequest = null;

/**
 * Initial loading Function
*/
function loading()
{
  var servletPath = document.getElementById("fldServletPath").value;
  var cz = document.getElementById("fldCZ").value;
  var companyCode = document.getElementById("fldCompanyCode").value;
  var envName = document.getElementById("fldEnvName").value;
  var ruserid = document.getElementById("fldRUserId").value;
  var sessionId = document.getElementById("fldSessionId").value;
  var guiCaller = document.getElementById("GUICaller").value;

  limitSearchFields();

  _brokerSuggest   = new BrokerSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);
  _branchSuggest   = new BranchSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);
  _salesrepSuggest = new SalesRepSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);

  _consolidatedList = new Grid('consolidatedPaymentList');
  _paymentList      = new Grid('paymentList');
  _transactionList  = new Grid('transactionList');

  /**
   * Checking to see if this page is being loaded from transaction Details
   * If so then highlight first row in consolidated payment list right away
   */
  if ( document.getElementById("consolidatedPayments").style.display != "none" )
  {
    onRowClick(_consolidatedList.getRow(1));
    _consolidatedList.setOnRowClickFunction(onRowClick);
  }

  /**
   * If this page is loaded from Main Menu
   * Focus first on Search Type Combo Box
   */
  if ( document.getElementById("transNumValue").value=="" )
  {
    document.getElementById("cmbSearchType").focus();
  }
  else
  {
    // If we entered into here with a TransNum then we automatically fetch
    // and display the information...
    var searchType = document.getElementById("cmbSearchType");
    searchType.value = 'transNum';

    changeDiv();

    getResults( 1, recordsPerPage);
  }
  
  /**
  * Checking to see if this page is being loaded from transaction Details
  * If so then disable the Details button coz the details shown in Desktop 
  **/
  if( guiCaller == "TransactionHistoryDlg")
 {
   document.getElementById("btnTransactionDetails").disabled = true;
 } 
 else
 {
   document.getElementById("btnTransactionDetails").disabled = false;
  }

  /**
   * Anytime if enter is pressed it will get results
   * Same functionality as clicking the Search Button
   */
  document.onkeypress= handler;
  //document.onkeydown = function(){if (event.keyCode==82) refreshPage()};
}

/** When Search Type Changes, different fields appear */
function changeDiv()
{
  var searchType = document.getElementById("cmbSearchType");
  var text = searchType.options[searchType.selectedIndex].innerHTML;

  undisplayPaymentForDiv();
  undisplayAccountDiv();
  undisplayPaymentDateDiv();
  undisplayPaymentIdDiv();
  undisplayPayEntityDiv();
  undisplayTransNumDiv();

  if ( text == "Payment For" )
  {
    displayPaymentForDiv();
  }
  if ( text == "Account Number" )
  {
    displayAccountDiv();
  }
  if ( text=="Payment Date" )
  {
    displayPaymentDateDiv();
  }
  if ( text=="Payment ID" )
  {
    displayPaymentIdDiv();
  }
  if ( text=="Pay Entity" )
  {
    displayPayEntityDiv();
  }
  if ( text =="Transaction Number" )
  {
    displayTransNumDiv();
  }
}

/** Hide or Show different DIVS */
function displayPaymentForDiv()
{
  document.getElementById("paymentForDiv").style.display = "inline";
}
function undisplayPaymentForDiv()
{
  document.getElementById("paymentForDiv").style.display = "none";
}

function displayAccountDiv()
{
  document.getElementById("accountDiv").style.display = "inline";
}

function undisplayAccountDiv()
{
  document.getElementById("accountDiv").style.display = "none";
}

function displayPaymentDateDiv()
{
  document.getElementById("paymentDateDiv").style.display = "inline";
}
function undisplayPaymentDateDiv()
{
  document.getElementById("paymentDateDiv").style.display = "none";
}

function displayPaymentIdDiv()
{
  document.getElementById("paymentIdDiv").style.display = "inline";
}
function undisplayPaymentIdDiv()
{
  document.getElementById("paymentIdDiv").style.display = "none";
}
function displayPayEntityDiv()
{
  document.getElementById("payEntityDiv").style.display = "inline";

}
function undisplayPayEntityDiv()
{
  document.getElementById("payEntityDiv").style.display = "none";
}

function undisplayTransNumDiv()
{
  document.getElementById("transNumDiv").style.display ="none";
}
function displayTransNumDiv()
{
  document.getElementById("transNumDiv").style.display = "inline";
}


function limitSearchFields()
{
    try
    {
        var currentPaymentFor = document.getElementById("cmbPaymentForPaymentFor").options[document.getElementById("cmbPaymentForPaymentFor").selectedIndex].innerHTML;
        var currentPayType = document.getElementById("cmbPaymentForPayType").options[document.getElementById("cmbPaymentForPayType").selectedIndex].innerHTML;

        //Check for Status Field
        if (currentPayType == "EFT" || currentPayType == "All")
        {
            document.getElementById("cmbPaymentForStatus").style.display = "inline";
        }
        else
        {
            document.getElementById("cmbPaymentForStatus").style.display = "none";
        }

        if (currentPaymentFor == "Distribution" || currentPaymentFor == "Redemption")
        {
            document.getElementById("paymentForAccountField").style.display = "inline";
        }
        else
        {
            document.getElementById("paymentForAccountField").style.display = "none";
        }
    }
    catch (e)
    {
        alert("Initial values not available, check listener.");
    }
}




function validDate(dateFld)
{
  return(dateFld.value.length > 0) && dateFld.validDate;
}

function submitChanges()
{
    requestURL = buildBaseURL("PaymentSearch_SubmitChanges");
    requestURL = appendParam(requestURL, "searchType", document.getElementById("cmbSearchType").options[document.getElementById("cmbSearchType").selectedIndex].value);
    requestURL = appendParam(requestURL, "pymtFor", document.getElementById("cmbPaymentForPaymentFor").value);

    if (document.getElementById("paymentForBrokerBox").code == "")
        document.getElementById("paymentForBrokerBox").code = "all";

    if (document.getElementById("paymentForBranchBox").code == "")
        document.getElementById("paymentForBranchBox").code = "all";

    if (document.getElementById("paymentForRepBox").code == "")
        document.getElementById("paymentForRepBox").code = "all";

    requestURL = appendParam(requestURL, "broker", document.getElementById("paymentForBrokerBox").code);
    requestURL = appendParam(requestURL, "branch", document.getElementById("paymentForBranchBox").code);
    requestURL = appendParam(requestURL, "slsRep", document.getElementById("paymentForRepBox").code);
    requestURL = appendParam(requestURL, "payType", document.getElementById("cmbPaymentForPayType").options[document.getElementById("cmbPaymentForPayType").selectedIndex].value);
    requestURL = appendParam(requestURL, "searchStatus", document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].value);
    requestURL = appendParam(requestURL, "accountNum", document.getElementById("paymentForAccountField").value);
    requestURL = appendParam(requestURL, "fromDate", document.getElementById("paymentForPaymentDateFrom").value);
    requestURL = appendParam(requestURL, "toDate", document.getElementById("paymentForPaymentDateTo").value);

    requestURL = appendParam(requestURL, "verifyAll", verifySend);
    requestURL = appendParam(requestURL, "stopAll", stopSend);
    requestURL = appendParam(requestURL, "approveAll", approveSend);

    //var consolidatedTable = document.getElementById("consolidatedPaymentList");
    var rowToCheck = null; // Build the XML for the specific changes, then append it to a node

    //if (document.getElementById("verifyAll").value


    var expectedValue = null;
    if (verifySend == "yes")
    {
        expectedValue = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML  + " Verified";
    }
    else if (approveSend == "yes")
    {
        expectedValue = "Approved";
    }
    else if (stopSend == "yes")
    {
        expectedValue = "Stopped";
    }
    else
    {
        expectedValue = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML;
    }

    var xmlToAdd = "<outerXMLNode>";
    var y = 0;
    var total_rows = document.getElementById('consolidatedPaymentList').rows.length;
    while(y < total_rows)
    {
	    if(document.getElementById("row" + y + "col1") != null)
	    {
	        valueInSelect = document.getElementById("row" + y + "col1").options[document.getElementById("row" + y + "col1").selectedIndex].innerHTML;

	        if (valueInSelect != expectedValue)
	        {
	             xmlToAdd = xmlToAdd
		              + "<PaymentUpdate><vrecid>" + _vrecid[y]
			      + "</vrecid><version>" + _versionList[y]
			      + "</version><newStatus>" + document.getElementById("row" + y + "col1").options[document.getElementById("row" + y + "col1").selectedIndex].value
			      + "</newStatus></PaymentUpdate>";
	        }
	    }
        y = Number(y)+1;
    }
    xmlToAdd = xmlToAdd + "</outerXMLNode>";
    //requestURL = appendParam(requestURL, "PayUpdateText", xmlToAdd);
    //callJobAndEval(requestURL);

    _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
    _httpRequest.open("POST", requestURL, false);
    _httpRequest.onreadystatechange = submitChangesHandler;
    _httpRequest.send(xmlToAdd);

}

function submitChangesHandler()
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


/**
 * Get Consolidated List
 * Depending on the search type different request URL's are built
 *
 *
 * @param: startRec: Where to start the records from
 *        endRec: Where to end the result set
 */
function getResults(startRec, endRec)
{

  _consolidatedList.deleteAllRows();


  showLoadingDisplay("consolidatedLoadingDiv");

  var searchType = document.getElementById("cmbSearchType").value;
  document.getElementById("recordStart").value = startRec;
  document.getElementById("recordEnd").value = endRec;

  requestURL = buildBaseURL("PaymentSearch_ConsolidatedList");
  requestURL = appendParam(requestURL, "rangeStart", startRec);
  requestURL = appendParam(requestURL, "rangeEnd", endRec);



  if ( searchType == "paymentfor" )
  {
    requestURL = appendParam(requestURL, "searchType", "paymentFor");
    requestURL = appendParam(requestURL, "searchValue",  document.getElementById("cmbPaymentForPaymentFor").value);
    requestURL = appendParam(requestURL, "pymtFor",  document.getElementById("cmbPaymentForPaymentFor").value);

    if ( !validDate(document.getElementById("paymentForPaymentDateFrom")) )
    {
      alert("Invalid 'From Date'");
      return;
    }
    requestURL = appendParam(requestURL, "fromDate", document.getElementById("paymentForPaymentDateFrom").value);

    if ( !validDate(document.getElementById("payEntityPaymentDateTo")) )
    {
      alert("Invalid 'To Date'");
      return;
    }
    requestURL = appendParam(requestURL, "toDate", document.getElementById("paymentForPaymentDateTo").value);

    /*if ( document.getElementById("paymentForAccountField").value == "")
    {
        requestURL = appendParam(requestURL, "accountValue", "All");
    }
    else
    {   */

        requestURL = appendParam(requestURL, "accountValue", document.getElementById("paymentForAccountField").value);
    //}
    requestURL = appendParam(requestURL, "broker", document.getElementById("paymentForBrokerBox").code);
    requestURL = appendParam(requestURL, "branch", document.getElementById("paymentForBranchBox").code);
    requestURL = appendParam(requestURL, "slsRep", document.getElementById("paymentForRepBox").code);
    requestURL = appendParam(requestURL, "payType", document.getElementById("cmbPaymentForPayType").value);
    requestURL = appendParam(requestURL, "status", document.getElementById("cmbPaymentForStatus").value);


  }

  else if ( searchType == "payEntity" )
  {
    requestURL = appendParam(requestURL, "searchType", "payEntity");
    requestURL = appendParam(requestURL, "searchValue",  document.getElementById("cmbPayEntityPaymentFor").value);
    requestURL = appendParam(requestURL, "pymtFor",  document.getElementById("cmbPayEntityPaymentFor").value);
    if ( !validDate(document.getElementById("payEntityPaymentDateFrom")) )
    {
      alert("Invalid 'From Date'");
      return;
    }
    requestURL = appendParam(requestURL, "fromDate", document.getElementById("payEntityPaymentDateFrom").value);

    if ( !validDate(document.getElementById("payEntityPaymentDateTo")) )
    {
      alert("Invalid 'To Date'");
      return;
    }
    requestURL = appendParam(requestURL, "toDate", document.getElementById("payEntityPaymentDateTo").value);

    requestURL = appendParam(requestURL, "broker", document.getElementById("payEntityBrokerBox").code);
    requestURL = appendParam(requestURL, "branch", document.getElementById("payEntityBranchBox").code);
    requestURL = appendParam(requestURL, "slsRep", document.getElementById("payEntityRepBox").code);
  }



  else if ( searchType == "paymentDate" )
  {
    requestURL = appendParam(requestURL, "searchType", "paymentDate");
    requestURL = appendParam(requestURL, "searchValue", document.getElementById("cmbPaymentFor").value);
    requestURL = appendParam(requestURL, "pymtFor",  document.getElementById("cmbPaymentFor").value);

    if ( !validDate(document.getElementById("paymentDateFrom")) )
    {
      alert("Invalid 'From Date'");
      return;
    }
    requestURL = appendParam(requestURL, "fromDate", document.getElementById("paymentDateFrom").value);

    if ( !validDate(document.getElementById("paymentDateTo")) )
    {
      alert("Invalid 'To Date'");
      return;
    }
    requestURL = appendParam(requestURL, "toDate", document.getElementById("paymentDateTo").value);
  }

  else if ( searchType == "account" )
  {
    requestURL = appendParam(requestURL, "searchType", "account");
    requestURL = appendParam(requestURL, "searchValue", document.getElementById("accountValue").value);

    if ( !validDate(document.getElementById("accountPaymentDateFrom")) )
    {
      alert("Invalid 'From Date'");
      return;
    }
    requestURL = appendParam(requestURL, "fromDate", document.getElementById("accountPaymentDateFrom").value);

    if ( !validDate(document.getElementById("accountPaymentDateTo")) )
    {
      alert("Invalid 'To Date'");
      return;
    }
    requestURL = appendParam(requestURL, "toDate", document.getElementById("accountPaymentDateTo").value);
  }

  else if ( searchType == "paymentId" )
  {
    requestURL = appendParam(requestURL, "searchType", "paymentId");
    requestURL = appendParam(requestURL, "searchValue", document.getElementById("paymentValue").value);
  }

  else if ( searchType == "transNum" )
  {
    requestURL = appendParam(requestURL, "searchType", "TransNumber");
    requestURL = appendParam(requestURL, "searchValue", document.getElementById("transNumValue").value);
  }

  document.getElementById("consolidatedPayments").style.visibility="visible";
  document.getElementById("consolidatedPayments").style.display = "inline";

  disableAll();
  callJob(requestURL, getResultsEval);
}

function getResultsEval ()
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


                _consolidatedList.setOnRowClickFunction(onRowClick);


            }
            catch (e)
            {
                alert("ERROR : " + e.description + " ");
                alert("**** DEBUG INFORMATION **** \n" + js);
            }
        }
        else
        {
            prompt( 'got response error - ', _httpRequest.responseText );
        }
    }
}

/**
 * Highlight the selected row for
 * transaction list and/or paymentList
 */
function highlightRow(row)
{
  _paymentList.highlightRow(row);
  _transactionList.highlightRow(row);
  transDetailsRow  = row;
}

/**
 * highlight the selected row in the
 * consolidated Payment List
 * From the highlighted row the next
 * job is called and it either pops up the payment list
 * or transaction list depending on the PaymentFor field
 */
function onRowClick(row)
{
  if (currentSelectedRow != row.rowPosition)
  {
      _consolidatedList.highlightRow(row);
      selectedRow = row;
      currentSelectedRow = row.rowPosition;

      listId = _consolidatedList.getCell(selectedRow,1).innerHTML;
      clearList(document.getElementById("transactionList"));
      clearList(document.getElementById("paymentList"));

      var startRec = document.getElementById("recordStart").value;
      var endRec = document.getElementById("recordEnd").value;

      var text = row.pymtFor;

      // FIX VIEWS to understand these!
      if ( text.toLowerCase() == 'commission' )
      {
        text = 'co';
      }
      if ( text.toLowerCase() == 'trailer fee' )
      {
        text = 'tf';
      }
      if ( text.toLowerCase() == 'distribution' )
      {
        text = 'id';
      }
      if ( text.toLowerCase() == 'redemption' )
      {
        text = 'pw';
      }
      document.getElementById("paymentForId").value = text;

      // Initial Values to pass in to obtaining records
      // Can be changed to return however many records you want
      // For paymentList or transactionList
      getList(1, recordsPerPage);
  }
}

/**
 * Calls job for obtaining transactionList
 * or paymentList, depending on paymentFor field
 * If paymentFor = commissions or trailer Fees
 *             paymentList is returned
 * If paymentFor = redemptions or distributions
 *           transactionList is returned
 */
function getList(startRec, endRec)
{

  _paymentList.deleteAllRows();
  _transactionList.deleteAllRows();

  requestURL = null;
  var searchType = document.getElementById("cmbSearchType");
  var text = searchType.options[searchType.selectedIndex].innerHTML;
  var paymentForText = document.getElementById("paymentForId").value;

  if ( text == "Payment For" )
  {
    var payFor = document.getElementById("cmbPaymentFor");
    var payText = payFor.options[payFor.selectedIndex].innerHTML;

    if ( paymentForText == "id" || paymentForText =="ID" )
    {
        initTransactionList();
    }
    else if ( paymentForText=="pw" || paymentForText =="PW" )
    {
        initTransactionList();
    }

    else if ( paymentForText == "co" || paymentForText =="CO" )
    {
        initPaymentList();
    }

    else if ( paymentForText =="tf" || paymentForText =="TF" )
    {
        initPaymentList();
    }

    var broker = document.getElementById("paymentForBrokerBox");
    var brokerName = broker.value;

    var branch = document.getElementById("paymentForBranchBox");
    var branchName = branch.value;

    var rep = document.getElementById("paymentForRepBox");
    var repName = rep.value;

    requestURL = appendParam(requestURL, "pymtId", listId);
    requestURL = appendParam(requestURL, "agencyCode", document.getElementById("paymentForBrokerBox").code);
    requestURL = appendParam(requestURL, "agencyName", brokerName);
    requestURL = appendParam(requestURL, "agentCode", document.getElementById("paymentForBranchBox").code);
    requestURL = appendParam(requestURL, "agentName", repName);
    requestURL = appendParam(requestURL, "branchCode", document.getElementById("paymentForRepBox").code);
    requestURL = appendParam(requestURL, "branchName", branchName);
    requestURL = appendParam(requestURL, "fromDt", document.getElementById("paymentForPaymentDateFrom").value);
    requestURL = appendParam(requestURL, "toDt", document.getElementById("paymentForPaymentDateTo").value);
    requestURL = appendParam(requestURL, "paymentFor", document.getElementById("paymentForId").value);

  }

  else if ( text == "Payment Date" )
  {
    var payFor = document.getElementById("cmbPaymentFor");
    var payText = payFor.options[payFor.selectedIndex].innerHTML;

    if ( paymentForText == "id" || paymentForText =="ID" )
    {
        initTransactionList();
    }
    else if ( paymentForText=="pw" || paymentForText =="PW" )
    {
        initTransactionList();
    }
    else if ( paymentForText == "co" || paymentForText =="CO" )
    {
        initPaymentList();
    }
    else if ( paymentForText =="tf" || paymentForText =="TF" )
    {
        initPaymentList();
    }
    requestURL = appendParam(requestURL, "pymtId", listId);
    requestURL = appendParam(requestURL, "paymentFor", document.getElementById("paymentForId").value);
    requestURL = appendParam(requestURL, "toDt", document.getElementById("paymentDateTo").value);
    requestURL = appendParam(requestURL, "frmDt", document.getElementById("paymentDateFrom").value);
  }

  else if ( text == "Pay Entity" )
  {
    var payFor = document.getElementById("cmbPaymentFor");
    var payText = payFor.options[payFor.selectedIndex].innerHTML;
    if ( paymentForText == "id" || paymentForText =="ID" )
    {
        initTransactionList();
    }
    else if ( paymentForText=="pw" || paymentForText =="PW" )
    {
        initTransactionList();
    }
    else if ( paymentForText == "co" || paymentForText =="CO" )
    {
        initPaymentList();
    }
    else if ( paymentForText =="tf" || paymentForText =="TF" )
    {
        initPaymentList();
    }
    var broker = document.getElementById("payEntityBrokerBox");
    var brokerName = broker.value;
    var branch = document.getElementById("payEntityBranchBox");
    var branchName = branch.value;
    var rep = document.getElementById("payEntityRepBox");
    var repName = rep.value;

    requestURL = appendParam(requestURL, "pymtId", listId);
    requestURL = appendParam(requestURL, "agencyCode", document.getElementById("payEntityBrokerBox").code);
    requestURL = appendParam(requestURL, "agencyName", brokerName);
    requestURL = appendParam(requestURL, "agentCode", document.getElementById("payEntityBranchBox").code);
    requestURL = appendParam(requestURL, "agentName", repName);
    requestURL = appendParam(requestURL, "branchCode", document.getElementById("payEntityRepBox").code);
    requestURL = appendParam(requestURL, "branchName", branchName);
    requestURL = appendParam(requestURL, "fromDt", document.getElementById("payEntityPaymentDateFrom").value);
    requestURL = appendParam(requestURL, "toDt", document.getElementById("payEntityPaymentDateTo").value);
    requestURL = appendParam(requestURL, "paymentFor", document.getElementById("paymentForId").value);
  }

  else if ( text =="Account Number" )
  {
    if ( paymentForText == "id" || paymentForText =="ID" )
    {
        initTransactionList();
    }
    else if ( paymentForText=="pw" || paymentForText =="PW" )
    {
        initTransactionList();
    }
    else if ( paymentForText == "co" || paymentForText =="CO" )
    {
        initPaymentList();
    }
    else if ( paymentForText =="tf" || paymentForText =="TF" )
    {
        initPaymentList();
    }
    requestURL = appendParam(requestURL, "pymtId", listId);
    requestURL = appendParam(requestURL, "accountNumber", document.getElementById("accountValue").value);
    requestURL = appendParam(requestURL, "toDt", document.getElementById("accountPaymentDateTo").value);
    requestURL = appendParam(requestURL, "fromDt", document.getElementById("accountPaymentDateFrom").value);
    requestURL = appendParam(requestURL, "paymentFor", document.getElementById("paymentForId").value);
  }

  else if ( text =="Payment ID" )
  {
    if ( paymentForText == "id" || paymentForText =="ID" )
    {
        initTransactionList();
    }
    else if ( paymentForText=="pw" || paymentForText == "PW" )
    {
        initTransactionList();
    }
    else if ( paymentForText == "co" || paymentForText =="CO" )
    {
        initPaymentList();
    }
    else if ( paymentForText =="TF" || paymentForText == "tf" )
    {
        initPaymentList();
    }

    requestURL = appendParam(requestURL, "pymtId", document.getElementById("paymentValue").value);
    requestURL = appendParam(requestURL, "paymentFor", document.getElementById("paymentForId").value);
  }

  else if ( text == "Transaction Number" )
  {
    if ( paymentForText == "id" || paymentForText =="ID" )
    {
        initTransactionList();
    }
    else if ( paymentForText=="pw" || paymentForText =="PW" )
    {
        initTransactionList();
    }
    else if ( paymentForText == "co" || paymentForText =="CO" )
    {
        initPaymentList();
    }
    else if ( paymentForText =="tf" || paymentForText == "TF" )
    {
        initPaymentList();
    }
    requestURL = appendParam(requestURL, "pymtId", listId);
    requestURL = appendParam(requestURL, "transNum", document.getElementById("transNumValue").value);
    requestURL = appendParam(requestURL, "paymentFor", document.getElementById("paymentForId").value);
  }
  requestURL = appendParam(requestURL, "rangeStart", startRec);
  requestURL = appendParam(requestURL, "rangeEnd", endRec);

  callJob(requestURL, getListEval);
  document.onkeydown = keyHandler;
}
/**
 * Functions used inside the getList function (just above)
 * Just combines a lot of repeating code into one line
 */
function initTransactionList()
{
  requestURL = buildBaseURL("General_TransactionList");
  document.getElementById("transactionDetails").style.display = "inline";
  document.getElementById("transactionDetails").style.visibility = "visible";
  showLoadingDisplay("transactionLoadingDiv");
  document.getElementById("paymentDetails").style.display = "none";
}
function initPaymentList()
{
  requestURL = buildBaseURL("DesktopGeneral_PaymentList");
  document.getElementById("paymentDetails").style.display = "inline";
  document.getElementById("paymentDetails").style.visibility = "visible";
  showLoadingDisplay("paymentLoadingDiv");
  document.getElementById("transactionDetails").style.display = "none";
}

function getListEval ()
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

                if ( document.getElementById("paymentDetails").style.display!="none" )
                {
                  _paymentList.setOnRowClickFunction(highlightRow);
                }
                else if ( document.getElementById("transactionDetails").style.display !="none" )
                {
                  _transactionList.setOnRowClickFunction(highlightRow);
                }
            }
            catch (e)
            {

                alert("ERROR : " + e.description + " ");
                alert("**** DEBUG INFORMATION **** \n" + js);
            }
        }
        else
        {
            prompt( 'got response error - ', _httpRequest.responseText );
        }
    }
}


/**
 * RefreshPage function
 * called when refresh button is pressed
 */
function refreshPage()
{
  //gotoJob("DesktopGeneral_Handler", "PaymentSearch_MainScreen");

  enableAll();

  currentSelectedRow = -1;
  massStatus = null;

  _consolidatedList.deleteAllRows();
  _paymentList.deleteAllRows();
  _transactionList.deleteAllRows();

  document.getElementById("verifyAll").checked=false;
  document.getElementById("verifyAllDiv").style.display = "none";
  document.getElementById("approveAll").checked=false;
  document.getElementById("approveAllDiv").style.display = "none";
  document.getElementById("stopAll").checked=false;
  document.getElementById("stopAllDiv").style.display = "none";

  document.getElementById("counterDiv").innerHTML = "0 - 0 of 0";
  document.getElementById("transactionCounterDiv").innerHTML = "0 - 0 of 0";
  document.getElementById("paymentCounterDiv").innerHTML = "0 - 0 of 0";

  document.getElementById("btnPrevPaymentRecords").disabled = true;
  document.getElementById("btnNextPaymentRecords").disabled = true;
  document.getElementById("btnPrevTransactionRecords").disabled = true;
  document.getElementById("btnNextTransactionRecords").disabled = true;
  document.getElementById("btnPrevConsPaymentRecords").disabled = true;
  document.getElementById("btnNextConsPaymentRecords").disabled = true;

  document.getElementById("consolidatedPayments").style.display = "none";

  //+++ PMI 16th May 20007 - Retrofitted Petko's refresh button fix
  document.getElementById("transactionDetails").style.display = "none";
  document.getElementById("paymentDetails").style.display     = "none";
  //---


  if ( selectedRow != null )
  {
    _consolidatedList.unhighlightRow(selectedRow);
  }
}

/**
 * Disable all fields on form
*/
function disableAll()
{

  document.getElementById("searchButton").disabled = true;

  document.getElementById("accountValue").disabled = true;
  document.getElementById("accountPaymentDateTo").disable(true);
  document.getElementById("accountPaymentDateFrom").disable(true);
  document.getElementById("paymentDateTo").disable(true);
  document.getElementById("paymentDateFrom").disable(true);
  document.getElementById("paymentValue").disabled = true;
  document.getElementById("payEntityPaymentDateTo").disable(true);
  document.getElementById("payEntityPaymentDateFrom").disable(true);

  document.getElementById("paymentForBrokerBox").disabled = true;
  document.getElementById("paymentForBranchBox").disabled = true;
  document.getElementById("paymentForRepBox").disabled = true;
  document.getElementById("payEntityBrokerBox").disabled = true;
  document.getElementById("payEntityBranchBox").disabled = true;
  document.getElementById("payEntityRepBox").disabled = true;

  document.getElementById("cmbPaymentFor").disabled = true;
  document.getElementById("cmbPayEntityPaymentFor").disabled = true;
  document.getElementById("cmbSearchType").disabled = true;
  document.getElementById("transNumValue").disabled = true;

  document.getElementById("cmbPaymentForPaymentFor").disabled = true;
  document.getElementById("cmbPaymentForPayType").disabled = true;
  document.getElementById("cmbPaymentForStatus").disabled = true;
  document.getElementById("paymentForAccountField").disabled = true;
  document.getElementById("paymentForPaymentDateFrom").disable(true);
  document.getElementById("paymentForPaymentDateTo").disable(true);
}

/**
 * Enable all fields on the form
*/
function enableAll()
{
  document.getElementById("searchButton").disabled = false;

  document.getElementById("accountValue").disabled = false;
  document.getElementById("accountPaymentDateTo").disable(false);
  document.getElementById("accountPaymentDateFrom").disable(false);
  document.getElementById("paymentDateTo").disable(false);
  document.getElementById("paymentDateFrom").disable(false);
  document.getElementById("paymentValue").disabled  = false;
  document.getElementById("payEntityPaymentDateTo").disable(false);
  document.getElementById("payEntityPaymentDateFrom").disable(false);

  document.getElementById("paymentForBrokerBox").disabled = false;
  document.getElementById("paymentForBranchBox").disabled = false;
  document.getElementById("paymentForRepBox").disabled = false;
  document.getElementById("payEntityBrokerBox").disabled = false;
  document.getElementById("payEntityBranchBox").disabled = false;
  document.getElementById("payEntityRepBox").disabled = false;

  document.getElementById("cmbPaymentFor").disabled = false;
  document.getElementById("cmbPayEntityPaymentFor").disabled = false;
  document.getElementById("cmbSearchType").disabled = false;
  document.getElementById("transNumValue").disabled = false;

  document.getElementById("cmbPaymentForPaymentFor").disabled = false;
  document.getElementById("cmbPaymentForPayType").disabled = false;
  document.getElementById("cmbPaymentForStatus").disabled = false;
  document.getElementById("paymentForAccountField").disabled = false;
  document.getElementById("paymentForPaymentDateFrom").disable(false);
  document.getElementById("paymentForPaymentDateTo").disable(false);
 //restoreDefaults()
}


/**
 * Try to disable method - but don't blow up
 */
function tryToDisable( controlId )
{
  var controlObj = document.getElementById( controlId );

  if ( controlObj != null )
  {
    controlObj.disable( true );
  }
}

/**
 * Try to disable method - but don't blow up
 */
function tryToEnable( controlId )
{
  var controlObj = document.getElementById( controlId );

  if ( controlObj != null )
  {
    controlObj.disable( false );
  }
}

/**
 * Back to the way the page was originally
*/
function restoreDefaults()
{
  displayPaymentIdDiv();
  undisplayPaymentDateDiv();
  undisplayAccountDiv();
  undisplayPayEntityDiv();
  undisplayTransNumDiv();
}


/**
 * More Button for Consolidated Payments
*/
function getMoreRecords()
{
  var startRec = document.getElementById("recordStart").value;
  var endRec = 25;
  if ( startRec > 1 )
  {
    getResults(startRec, endRec);
  }
}

/**
 * More button for transaction list or Payment List
*/
function moreRecords()
{
  var startRec = document.getElementById("recordStart").value;
  var endRec = 25;
  if ( startRec > 1 )
  {
    getList(startRec, endRec);
  }
}

/**
 * Clears any tables and/or grids
 *
 * @param: listName: name of any table or grid to clear
 */
function clearList(listName)
{
  var list = listName;
  var rows = list.firstChild.childNodes;
  for ( var i=rows.length-1; greaterThan(i,0); i-- )
  {
    rows[i].parentNode.removeChild(rows[i]);
  }
}

/**
 * values in transactionTable
 * used to go to transaction Details page
 */
function dataForTransDetails()
{
  transType = _transactionList.getCell(transDetailsRow,0).innerHTML;
  accountNum = _transactionList.getCell(transDetailsRow,3).innerHTML;
  transNum = _transactionList.getCell(transDetailsRow,5).innerHTML;
  transId = transDetailsRow.transId;
}

function getAccountNum()
{
  accountNum = _transactionList.getCell(transDetailsRow,3).innerHTML;
  return (accountNum);
}

function getTransNum()
{
  transNum = _transactionList.getCell(transDetailsRow,5).innerHTML;
  return (transNum)
}

function getFundCode()
{
  FundCode= _transactionList.getCell(transDetailsRow,8).innerHTML;
  return (FundCode);
}

function getClassCode()
{
  ClassCode = _transactionList.getCell(transDetailsRow,9).innerHTML;
  return (ClassCode);
}

function getTransId()
{
  // remove the commons
  return( transId );
}


function getAuditRecid ()
{
    auditRecid = _vrecid[currentSelectedRow];
    return (auditRecid);
}

/**
 * Handles the up and down arrow key to
 * scroll through the grids with the arrow keys
 */
function keyHandler()
{

  if ( transDetailsRow != null )
  {
    //down arrow
    if ( event.keyCode == 40 )
    {
      moveDown();
      return (false);
    }
    // up arrow
    else if ( event.keyCode == 38 )
    {
      moveUp();
      return (false);
    }
  }
  return (true);
}

function moveDown()
{
  var nextRow = transDetailsRow.nextSibling;

  if ( nextRow != null )
  {
    _transactionList.highlightRow(nextRow);
    _paymentList.highlightRow(nextRow);
    transDetailsRow = nextRow;
  }
}

function moveUp()
{
  var nextRow = transDetailsRow.previousSibling;

  if ( nextRow != transDetailsRow.parentNode.firstChild )
  {
    _transactionList.highlightRow(nextRow);
    _paymentList.highlightRow(nextRow)
    transDetailsRow = nextRow;
  }
}

function handler()
{
  //if ( event.keyCode==13 )
  //{

  //  getResults(1,25);
  //}
  if ( event.keyCode == 19 )
  {
    refreshPage();
  }
}

function modifyAllStatuses (toStatus)
{

    var searchedStatus = massStatus;
    if(searchedStatus == null)
    {
        searchedStatus = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML;
    }

    if (toStatus == "Default")
    {
        toStatus = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML;
        //massStatus = toStatus;
    }
    else if (toStatus == "Verify")
    {
        toStatus = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML + " Verified";
    }


    var optionsArray = null;

    var y = 0;
    while(document.getElementById("row" + y + "col1") != null)
    {
        selectBox = document.getElementById("row" + y + "col1").options;

        if (selectBox.options[selectBox.selectedIndex].innerHTML == searchedStatus)
        {
            for (var x = 0; x < selectBox.options.length; x++)
            {

                if (selectBox.options[x].text == toStatus)
                    selectBox.options[x].selected = true;

            }
        }
        y = Number(y)+1;
    }
}

function resetSelected()
{

    var searchedStatus = searchedStatus = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML;
    var selectBox = document.getElementById("row"+currentSelectedRow+"col1");

    for (var x = 0; x < selectBox.options.length; x++)
    {
        if (selectBox.options[x].text == searchedStatus)
            selectBox.options[x].selected = true;
    }
}

function goToStart()
{
    requestURL = buildBaseURL("PaymentSearch_MainScreen");
    document.location = requestURL;

}


