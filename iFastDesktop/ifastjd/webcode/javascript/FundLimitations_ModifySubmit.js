var _httpRequestModify = null;

//******************************************************************
function SubmitModify()
{
  var url = document.getElementById("fldServletPath").value
  + "?cz=" + document.getElementById("fldCZ").value
  + "&envName=" + document.getElementById("fldEnvName").value
  + "&dateFormat=" + document.getElementById("fldDateFormat").value
  + "&companyCode=" + document.getElementById("fldCompanyCode").value
  + "&ruserId=" + document.getElementById("fldRUserId").value
  + "&sessionId=" + document.getElementById("fldSessionId").value;

  url += "&jobname=FundLimitations_ModifyCommit";

  var parameters = "&account=" +_accountNumber;
  parameters += "&broker="     +_broker;
  parameters += "&branch="     +_branch;
  parameters += "&slsrep="     +_salesRep;
  parameters += "&ruletype="   +_ruleTypeCode;
  parameters += "&startdate="  +_startDate;
  parameters += "&stopdate="   + document.getElementById('endDateInput').value;
  parameters += "&controlsid=" +_controlsId;
  parameters += "&version="    +_version;

  parameters += "&fund="       +_fund;
  parameters += "&class="      +_class;
  parameters += "&fundgroup="  +_fundgroup;

  if ( document.getElementById("overrideAmtInput") != null )
  {
    parameters += "&overrideamt=" + document.getElementById("overrideAmtInput").value;
    parameters += "&overridelog=" + "";
  }
  else
  {
    parameters += "&overrideamt=" + "";
    parameters += "&overridelog=yes";
  }

  if ( document.getElementById("overrideCharSelect") != null )
  {
    parameters += "&overridechar=yes";
  }
  else
  {
    parameters += "&overridechar=" + "";
  }

  parameters += "&onlineewi=" + document.getElementById('onlineSelectBox').value;
  parameters += "&cycleewi="  + document.getElementById('cycleSelectBox').value;
  parameters += "&esgewi="    + document.getElementById('esgSelectBox').value;

  _httpRequestModify = new ActiveXObject("MSXML2.XMLHTTP");
  _httpRequestModify.open("POST", url + parameters, false);
  _httpRequestModify.onreadystatechange = handleModifyResponse;
  _httpRequestModify.send();
}

//******************************************************************
function handleModifyResponse()
{
  if ( _httpRequestModify.readyState == 4 )
  {

    if ( _httpRequestModify.status == 200 )
    {
      var returnMessage = _httpRequestModify.responseText;
      returnMessage = returnMessage.substring( returnMessage.indexOf( '<response>' ) + 10, returnMessage.indexOf( '</response>' ) );

      alert( returnMessage );

      if ( returnMessage == "Successfully Modified" )
      {
        parent.closeModifyIframe("yes");
      }
    }
    else
    {
      alert("HTTP error: " + _httpRequestModify.status);
    }
  }
}

//******************************************************************
function validateNumeric(fld)
{
  var k = window.event.keyCode;

  if ( isLeftArrow(k) || isRightArrow(k) )
  {
    return true;
  }
  else if ( isBackspace(k) )
  {
    // need to ensure they don't delete the "."
    var origValue = fld.value;
    var textRange = document.selection.createRange();
    var origRangeText= textRange.text
    textRange.text = origRangeText + "#";

    var testString = fld.value.substring(0, fld.value.indexOf("#"));

    textRange.moveStart("character", (0 - origRangeText.length - 1));

    textRange.text = origRangeText;

    return(testString.indexOf(".") == -1) || (testString.indexOf(".") != testString.length - 1);
  }
  else if ( isDelete(k) )
  {
    // need to ensure they don't delete the "."
    var origValue = fld.value;
    var textRange = document.selection.createRange();
    var origRangeText= textRange.text
    textRange.text = origRangeText + "#";

    var testString;
    if ( fld.value.indexOf("#") == fld.value.length - 1 )
    {
      testString = fld.value.substring(0, fld.value.indexOf("#"));
    }
    else
    {
      testString = fld.value.substring(0, fld.value.indexOf("#") + 2)
    }

    textRange.moveStart("character", (0 - origRangeText.length - 1));

    textRange.text = origRangeText;

    return(testString.indexOf(".") != testString.length - 1);
  }
  else if ( isNum(k) )
  {
    var origValue = fld.value;

    var textRange = document.selection.createRange();
    var origRangeText = textRange.text
    textRange.text = origRangeText + "#";

    var testString = fld.value.substring(0, fld.value.indexOf("#"));

    textRange.moveStart("character", (0 - origRangeText.length - 1));

    textRange.text = origRangeText;

    // entering before decimal
    if ( testString.indexOf(".") == -1 )
    {
      return fld.value.substring(0, fld.value.indexOf(".")).length < 13;
    }
    // after decimal
    else
    {
      var s = fld.value.substring(fld.value.indexOf(".") + 1, fld.value.length);
      return s.length < 2;
    }

    fld.value = origValue;
    return true;
  }

  return false;
}


//******************************************************************
function isChar(keyCode)
{
  // a = 65 .... z = 90
  return(keyCode >= 65 && keyCode <= 90)
}

//******************************************************************
function isNum(keyCode)
{
  // 0 = 48 .... 9 = 57 (using top numeric keys)... 0 = 96 ... 9 = 105 (using keypad)
  return((keyCode >= 48 && keyCode <= 57) || (keyCode >= 96 && keyCode <= 105))
}

//******************************************************************
function isTab(keyCode)
{

  // a = 65 .... z = 90
  return(keyCode == 9);
}

//******************************************************************
function isDelete(keyCode)
{
  return(keyCode == 46);
}

//******************************************************************
function isBackspace(keyCode)
{
  return(keyCode == 8);
}

//******************************************************************
function isUpArrow(keyCode)
{
  return(keyCode == 38);
}

//******************************************************************
function isDownArrow(keyCode)
{
  return(keyCode == 40);
}

//******************************************************************
function isRightArrow(keyCode)
{
  return(keyCode == 39);
}

//******************************************************************
function isLeftArrow(keyCode)
{
  return(keyCode == 37);
}

//******************************************************************
function isEnter(keyCode)
{
  return(keyCode == 13)
}

//******************************************************************
function isDecimal(keyCode)
{
  return(keyCode == 110 || keyCode == 190);
}

