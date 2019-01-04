//****************************************************************************
function getSubmitURL()
{
  return document.getElementById("fldServletPath").value
      + "?cz=" + document.getElementById("fldCZ").value
      + "&envName=" + document.getElementById("fldEnvName").value
      + "&companyCode=" + document.getElementById("fldCompanyCode").value
      + "&ruserId=" + document.getElementById("fldRUserId").value
      + "&sessionId=" + document.getElementById("fldSessionId").value
      + "&dateFormat=" + document.getElementById("fldDateFormat").value
      + "&jobname=" + "CloneAccount_Submit";
}

//****************************************************************************
var _newAccountNum = null;
var _newShrNum = null;
var _SubmitHttpRequest = null;


//****************************************************************************
function update()
{
  var url = getSubmitURL();

  var dataStr = "";
  dataStr += "&broker=" + document.getElementById("brokerBox").value;
  dataStr += "&branch=" + document.getElementById("branchBox").value;
  dataStr += "&slsrep=" + document.getElementById("repBox").value;
  dataStr += "&acctDesignation=" + document.getElementById("cmbAcctDesign").value;
  dataStr += "&taxType=" + document.getElementById("cmbTaxType").value;
  dataStr += "&effectiveDate=" + document.getElementById("EffectiveDate").value;
  dataStr += "&altAcct=" + document.getElementById("AltAcctNbr").value;
  dataStr += "&intermCode=" + document.getElementById("cmbIntermCode").value;
  dataStr += "&intermAcctNum=" + document.getElementById("IntermAcctNbr").value;

  if( document.getElementById("DistInfoBox").checked )
  {
    dataStr += "&CloneDistribInfo=" +  "yes";
  }
  else
  {
    dataStr += "&CloneDistribInfo=" +  "no";
  }

  if( document.getElementById("BankInfoBox").checked )
  {
    dataStr += "&clonebankInfo=" + "yes";
  }
  else
  {
    dataStr += "&clonebankInfo=" + "no";
  }

  if( document.getElementById("AllEntityBox").checked )
  {
    dataStr += "&cloneallEntities=" + "yes";
  }
  else
  {
    dataStr += "&cloneallEntities=" + "no";
  }

  dataStr += "&accountNum=" + document.getElementById("fldAccountNum").value;
  dataStr += "&createSlsRep=" + document.getElementById("fldCreateSaleRep").value;

  _SubmitHttpRequest = new ActiveXObject("MSXML2.XMLHTTP");
  _SubmitHttpRequest.open("POST", url + dataStr, false);
  _SubmitHttpRequest.onreadystatechange = handleSubmitResponse;

  _SubmitHttpRequest.send();
  
  if ( _newAccountNum != null )
  {
  	return Desktop.SUCCESS;
  }
  else
  {
  	return Desktop.FAIL;
  }
}

//****************************************************************************
function getUpdateStatus()
{
  return( false );
}

//****************************************************************************
function LaunchConfirm()
{
  return( true );
}

//****************************************************************************
function handleSubmitResponse()
{
  if ( _SubmitHttpRequest.readyState == 4)
  {
    if( _SubmitHttpRequest.status == 200)
    {
      var response = _SubmitHttpRequest.responseText.substring(_SubmitHttpRequest.responseText.indexOf("<dtAcctAutoCopyProcResponse>")+28, _SubmitHttpRequest.responseText.indexOf("</dtAcctAutoCopyProcResponse>"));      	  
	  
      if(response.length == 0)
      {
        alert("submit error: no response");
      }
      else
      {
        var responseStatus = response.substring(response.indexOf("<status>") + 8, response.indexOf("</status"));

        if( responseStatus.toLowerCase() == "accepted" )
        {
        	//set new account number and new shareholder number
          	_newAccountNum = response.substring(response.indexOf("<newAcctNum>") + 12, response.indexOf("</newAcctNum"));
          	_newShrNum = response.substring(response.indexOf("<newShrNum>") + 11, response.indexOf("</newShrNum"));
          	
          	var msg = "Cloned account successfully.\n";
	  		msg += "\nNew Account Number = " + _newAccountNum;
	  		msg += "\nNew Shareholder Number = " + _newShrNum;
        
        	if( response.indexOf( "Errors" ) == -1 )
        	{        		
          		alert( msg );	
        	}
        	// warning occurred
        	else
        	{
        		var warningMsg = response.substring( response.indexOf( "<text>" ) + 6, response.indexOf( "</text" ) );
        		msg += "\n\nWarning: " +  warningMsg;
        		alert( msg );        		
        	}
        }
        else
        {
          var errorCode = response.substring(response.indexOf("<errorCode>") + 11, response.indexOf("</errorCode"));
          var errormessage = response.substring(response.indexOf("<text>") + 6, response.indexOf("</text"));
          alert("Clone Account failed: \nError Code = " + errorCode + "\nError Message = " + errormessage );
        }
      }
    }
    else
    {
      alert( "Http Request Error: " + _SubmitHttpRequest.status  + " - " + _SubmitHttpRequest.statusText );
    }
  }
}

//****************************************************************************
function getNewAccountNum()
{
  return( _newAccountNum );
}

//****************************************************************************
function getNewShrNum()
{
  return( _newShrNum );
}

