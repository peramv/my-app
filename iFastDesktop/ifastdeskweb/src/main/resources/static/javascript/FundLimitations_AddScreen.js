function setUpdatesCompleted()
{
	_updatesCompleted = true;
}


function isUpdatesCompleted()
{
	return _updatesCompleted;
}


//*********************************************************************
function setSelectedRuleType( ruleTypeCode )
{
	var ruleTypeDropdown = document.getElementById( "ruleTypeDropdown" );
	for ( var i = 0; i < ruleTypeDropdown.options.length; i++ )
	{
		if ( ruleTypeDropdown.options[i].value == ruleTypeCode )
		{
			ruleTypeDropdown.selectedIndex = i; 
		}
	}
	
	// need to run the change handler
	onRuleTypeChange( ruleTypeDropdown );
}

//*********************************************************************
function disableInputFields()
{
  document.getElementById("ruleTypeDropdown").disabled = true;
  document.getElementById("startDate").disable(true);
  document.getElementById("endDate").disable(true);

  document.getElementById("basedOnShowFormId").disabled = true;

  document.getElementById("fundSponsor_fundSponsorDropdown").disabled = true;
  document.getElementById("fundSponsor_amt").disabled = true;
  document.getElementById("fundSponsor_allow").disabled = true;
  document.getElementById("fundSponsor_onlineewi").disabled = true;
  document.getElementById("fundSponsor_cycleewi").disabled = true;
  document.getElementById("fundSponsor_esgewi").disabled = true;
  document.getElementById("fundSponsor_exclude").disabled = true;
  document.getElementById("fundSponsor_stop").disabled = true;
  document.getElementById("fundSponsor_addLimitationsBtn").disabled = true;

  document.getElementById("fund_fundSponsorDropdown").disabled = true;
  document.getElementById("fund_fundName").disabled = true;
  document.getElementById("fund_amt").disabled = true;
  document.getElementById("fund_allow").disabled = true;
  document.getElementById("fund_onlineewi").disabled = true;
  document.getElementById("fund_cycleewi").disabled = true;
  document.getElementById("fund_esgewi").disabled = true;
  document.getElementById("fund_exclude").disabled = true;
  document.getElementById("fund_stop").disabled = true;
  document.getElementById("fund_addLimitationsBtn").disabled = true;

  document.getElementById("class_fundSponsorDropdown").disabled = true;
  document.getElementById("class_classBox").disabled = true;
  document.getElementById("class_amt").disabled = true;
  document.getElementById("class_allow").disabled = true;
  document.getElementById("class_onlineewi").disabled = true;
  document.getElementById("class_cycleewi").disabled = true;
  document.getElementById("class_esgewi").disabled = true;
  document.getElementById("class_exclude").disabled = true;
  document.getElementById("class_stop").disabled = true;
  document.getElementById("class_addLimitationsBtn").disabled = true;
  
  
  document.getElementById("fundGroup_fundGroupDropdown").disabled = true;
  document.getElementById("fundGroup_amt").disabled = true;
  document.getElementById("fundGroup_allow").disabled = true;
  document.getElementById("fundGroup_onlineewi").disabled = true;
  document.getElementById("fundGroup_cycleewi").disabled = true;
  document.getElementById("fundGroup_esgewi").disabled = true;
  document.getElementById("fundGroup_exclude").disabled = true;
  document.getElementById("fundGroup_stop").disabled = true;
  document.getElementById("fundGroup_addLimitationsBtn").disabled = true;
}

//*********************************************************************
function enableInputFields()
{
  document.getElementById("ruleTypeDropdown").disabled = false;
  document.getElementById("startDate").disable(false);
  document.getElementById("endDate").disable(false);

  document.getElementById("basedOnShowFormId").disabled = false;

  document.getElementById("fundSponsor_fundSponsorDropdown").disabled = false;
  document.getElementById("fundSponsor_amt").disabled = false;
  document.getElementById("fundSponsor_allow").disabled = false;
  document.getElementById("fundSponsor_onlineewi").disabled = false;
  document.getElementById("fundSponsor_cycleewi").disabled = false;
  document.getElementById("fundSponsor_esgewi").disabled = false;
  document.getElementById("fundSponsor_exclude").disabled = false;
  document.getElementById("fundSponsor_stop").disabled = false;
  document.getElementById("fundSponsor_addLimitationsBtn").disabled = false;

  document.getElementById("fund_fundSponsorDropdown").disabled = false;
  document.getElementById("fund_fundName").disabled = false;
  document.getElementById("fund_amt").disabled = false;
  document.getElementById("fund_allow").disabled = false;
  document.getElementById("fund_onlineewi").disabled = false;
  document.getElementById("fund_cycleewi").disabled = false;
  document.getElementById("fund_esgewi").disabled = false;
  document.getElementById("fund_exclude").disabled = false;
  document.getElementById("fund_stop").disabled = false;
  document.getElementById("fund_addLimitationsBtn").disabled = false;

  document.getElementById("class_fundSponsorDropdown").disabled = false;
  document.getElementById("class_classBox").disabled = false;
  document.getElementById("class_amt").disabled = false;
  document.getElementById("class_allow").disabled = false;
  document.getElementById("class_onlineewi").disabled = false;
  document.getElementById("class_cycleewi").disabled = false;
  document.getElementById("class_esgewi").disabled = false;
  document.getElementById("class_exclude").disabled = false;
  document.getElementById("class_stop").disabled = false;
  document.getElementById("class_addLimitationsBtn").disabled = false;
  
  document.getElementById("fundGroup_fundGroupDropdown").disabled = false;
  document.getElementById("fundGroup_amt").disabled = false;
  document.getElementById("fundGroup_allow").disabled = false;
  document.getElementById("fundGroup_onlineewi").disabled = false;
  document.getElementById("fundGroup_cycleewi").disabled = false;
  document.getElementById("fundGroup_esgewi").disabled = false;
  document.getElementById("fundGroup_exclude").disabled = false;
  document.getElementById("fundGroup_stop").disabled = false;
  document.getElementById("fundGroup_addLimitationsBtn").disabled = false;
}

//*********************************************************************
function reset()
{
  document.getElementById("ruleTypeDropdown").disabled = false;
  document.getElementById("ruleTypeDropdown").selectedIndex = 0;

  document.getElementById("startDate").value = document.getElementById("startDate").defaultValue;
  document.getElementById("endDate").value = document.getElementById("endDate").defaultValue;

  document.getElementById("basedOnShowFormId").selectedIndex = 0;
  showHideDiv('enterSponsor', 'hide');
  showHideDiv('enterFund', 'hide');
  showHideDiv('enterClass', 'hide');


  document.getElementById("fundSponsor_fundSponsorDropdown").selectedIndex = 0;
  document.getElementById("divFundSponsor_amt").style.display = "block";
  document.getElementById("fundSponsor_amt").value = document.getElementById("fundSponsor_amt").defaultValue;
  document.getElementById("divFundSponsor_allow").style.display = "none";
  document.getElementById("fundSponsor_onlineewi").selectedIndex = 0;
  document.getElementById("fundSponsor_cycleewi").selectedIndex = 0;
  document.getElementById("fundSponsor_esgewi").selectedIndex = 0;
  document.getElementById("fundSponsor_exclude").checked = true;


  document.getElementById("fund_fundSponsorDropdown").selectedIndex = 0;
  document.getElementById("fund_fundName").value = "ALL";
  document.getElementById("fund_fundName").code = "ALL";
  document.getElementById("divFund_amt").style.display = "block";
  document.getElementById("fund_amt").value = document.getElementById("fund_amt").defaultValue;
  document.getElementById("divFund_allow").style.display = "none";
  document.getElementById("fund_onlineewi").selectedIndex = 0;
  document.getElementById("fund_cycleewi").selectedIndex = 0;
  document.getElementById("fund_esgewi").selectedIndex = 0;
  document.getElementById("fund_exclude").checked = true;


  document.getElementById("class_fundSponsorDropdown").selectedIndex = 0;
  document.getElementById("class_classBox").value = "";
  document.getElementById("divClass_amt").style.display = "block"
  document.getElementById("class_amt").style.display = "block";
  document.getElementById("class_amt").value = document.getElementById("class_amt").defaultValue;
  document.getElementById("divClass_allow").style.display = "none";
  document.getElementById("class_onlineewi").selectedIndex = 0;
  document.getElementById("class_cycleewi").selectedIndex = 0;
  document.getElementById("class_esgewi").selectedIndex = 0;
  document.getElementById("class_exclude").checked = true;
  
  
  document.getElementById("fundGroup_fundGroupDropdown").selectedIndex = 0;  
  document.getElementById("divFundGroup_amt").style.display = "block"
  document.getElementById("fundGroup_amt").style.display = "block";
  document.getElementById("fundGroup_amt").value = document.getElementById("class_amt").defaultValue;
  document.getElementById("divFundGroup_allow").style.display = "none";
  document.getElementById("fundGroup_onlineewi").selectedIndex = 0;
  document.getElementById("fundGroup_cycleewi").selectedIndex = 0;
  document.getElementById("fundGroup_esgewi").selectedIndex = 0;
  document.getElementById("fundGroup_exclude").checked = true;

  document.getElementById("lblStoppedRecords").innerHTML = "";
  document.getElementById("lblNewRecords").innerHTML = "";
}

//*********************************************************************
function enableButtons()
{
  document.getElementById("deleteBtn").disabled = false;
  document.getElementById("commitBtn").disabled = false;
}

//*********************************************************************
function disableButtons()
{
  document.getElementById("deleteBtn").disabled = true;
  document.getElementById("commitBtn").disabled = true;
}

//*********************************************************************
function fundSponsorOnChange(fundSponsorFld)
{
  if ( fundSponsorFld.selectedIndex != 0 )
  {
    document.getElementById("fund_fundName").value = "";
    document.getElementById("fund_fundName").code = "";
  }
  else
  {
    document.getElementById("fund_fundName").value = "ALL";
    document.getElementById("fund_fundName").code = "ALL";
  }
}

//*********************************************************************
function populateClassList(fundSponsorFld)
{
  var classListStr = fundSponsorFld.options[fundSponsorFld.selectedIndex].fundSponsorClassList;
  var classListArray = classListStr.substring(0, classListStr.length - 2).split(",");

  document.getElementById("class_classBox").innerHTML = "";

  var emptyOpt = document.createElement("option");
  emptyOpt.value = "";
  emptyOpt.text = "";
  document.getElementById("class_classBox").add(emptyOpt);

  for ( var i = 0; i < classListArray.length; i++ )
  {
    var opt = document.createElement("option");
    opt.value = classListArray[i];
    opt.text = classListArray[i];
    document.getElementById("class_classBox").add(opt);
  }

}

//*********************************************************************
function getCurPendingRulesXML()
{
  var rulesXML = "";
  var pendingRulesTableContents = document.getElementById("ruleList").firstChild;

  // skip the header row
  for ( var i = 1; i < pendingRulesTableContents.childNodes.length; i++ )
  {
    var curRow = pendingRulesTableContents.childNodes[i];

    var singleRuleXML = "";
    singleRuleXML += XML_Lib.createXMLStr("fundSponsor", curRow.childNodes[0].innerHTML);
    singleRuleXML += XML_Lib.createXMLStr("fund", curRow.childNodes[1].innerHTML);
    singleRuleXML += XML_Lib.createXMLStr("class", curRow.childNodes[2].innerHTML);    

    rulesXML += XML_Lib.createXMLStr("PendingRule", singleRuleXML);
  }

  return XML_Lib.createXMLStr("PendingRules", rulesXML);
}

//*********************************************************************
function validateNumeric(fld)
{
  // return true lets it go through, false stops it
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

    if ( origRangeText.length > 0 )
    {
      if ( origRangeText.indexOf(".") == -1 )
      {
        return true;
      }
      else
      {
        return false;
      }
    }

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

    if ( origRangeText.length > 0 )
    {
      if ( origRangeText.indexOf(".") == -1 )
      {
        return true;
      }
      else
      {
        return false;
      }
    }

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
      if ( origRangeText.length > 0 && origRangeText.indexOf(".") == -1 )
      {
        return true;
      }
      return fld.value.substring(0, fld.value.indexOf(".")).length < 13;
    }
    // after decimal
    else
    {

      if ( origRangeText.length > 0 && origRangeText.indexOf(".") == -1 )
      {
        return true;
      }

      var s = fld.value.substring(fld.value.indexOf(".") + 1, fld.value.length);

      return s.length < 2;
    }


    fld.value = origValue;
    return true;
  }
  else if ( isTab(k) )
  {
    // Gives a javascript error, but its the only way I found to make it work
    // (Not sure what the js error is actually referring to)
    // window.getSelection().removeAllRanges();
    return true;
  }
  else if ( isHome(k) || isEnd(k) )
  {
    return true;
  }

  return false;
}

//*********************************************************************
function onRuleTypeChange(ruleSelectBox)
{
  if ( ruleSelectBox.value == "40" )
  {  	
  	document.getElementById( "divFundSponsor_amt" ).style.display = "none";    
    document.getElementById( "divFundSponsor_allow" ).style.display = "block"
    document.getElementById( "fundSponsor_exclude" ).checked = true;
    document.getElementById( "fundSponsor_exclude" ).disabled = true;
    document.getElementById( "fundSponsor_stop" ).disabled = true;
    

    document.getElementById("divFund_amt").style.display = "none";    
    document.getElementById("divFund_allow").style.display = "block";
    document.getElementById( "fund_exclude" ).checked = true;
    document.getElementById( "fund_exclude" ).disabled = true;
    document.getElementById( "fund_stop" ).disabled = true;

    document.getElementById("divClass_amt").style.display = "none";    
    document.getElementById("divClass_allow").style.display = "block";
    document.getElementById( "class_exclude" ).checked = true;
    document.getElementById( "class_exclude" ).disabled = true;
    document.getElementById( "class_stop" ).disabled = true;
    
    document.getElementById("divFundGroup_amt").style.display = "none";       
    document.getElementById("divFundGroup_allow").style.display = "block"
    document.getElementById( "fundGroup_exclude" ).checked = true;
    document.getElementById( "fundGroup_exclude" ).disabled = true;
    document.getElementById( "fundGroup_stop" ).disabled = true;
    
    var basedOnSelectBox = document.getElementById( "basedOnShowFormId" );    
    if ( basedOnSelectBox.options.length < 5 )
    {
    	var option = document.createElement( "option" );    	
    	option.value = "specificFundGroup";
    	option.text = "Specific Fund Group";
    	basedOnSelectBox.add( option );
    }    
  }	
  else if ( ruleSelectBox.value == "01" || ruleSelectBox.value == "02" || ruleSelectBox.value == "16" )
  {
    document.getElementById("divFundSponsor_amt").style.display = "block";    
    document.getElementById("divFundSponsor_allow").style.display = "none"
    document.getElementById( "fundSponsor_exclude" ).disabled = false;
    document.getElementById( "fundSponsor_stop" ).disabled = false;

    document.getElementById("divFund_amt").style.display = "block";    
    document.getElementById("divFund_allow").style.display = "none";
    document.getElementById( "fund_exclude" ).disabled = false;
    document.getElementById( "fund_stop" ).disabled = false;

    document.getElementById("divClass_amt").style.display = "block";    
    document.getElementById("divClass_allow").style.display = "none";
    document.getElementById( "class_exclude" ).disabled = false;
    document.getElementById( "class_stop" ).disabled = false;
    
    document.getElementById("divFundGroup_amt").style.display = "block";    
    document.getElementById("divFundGroup_allow").style.display = "none"
    document.getElementById( "fundGroup_exclude" ).disabled = false;
    document.getElementById( "fundGroup_stop" ).disabled = false;
    
    var basedOnSelectBox = document.getElementById( "basedOnShowFormId" );
    if ( basedOnSelectBox.options.length == 5 )
    {
    	basedOnSelectBox.remove( 4 );
    }
  }
  else
  {
    document.getElementById("divFundSponsor_amt").style.display = "none";    
    document.getElementById("divFundSponsor_allow").style.display = "block"
    document.getElementById( "fundSponsor_exclude" ).disabled = false;
    document.getElementById( "fundSponsor_stop" ).disabled = false;

    document.getElementById("divFund_amt").style.display = "none";    
    document.getElementById("divFund_allow").style.display = "block"
    document.getElementById( "fund_exclude" ).disabled = false;
    document.getElementById( "fund_stop" ).disabled = false;

    document.getElementById("divClass_amt").style.display = "none";    
    document.getElementById("divClass_allow").style.display = "block"
    document.getElementById( "class_exclude" ).disabled = false;
    document.getElementById( "class_stop" ).disabled = false;
    
    document.getElementById("divFundGroup_amt").style.display = "none";    
    document.getElementById("divFundGroup_allow").style.display = "block"
    document.getElementById( "fundGroup_exclude" ).disabled = false;
    document.getElementById( "fundGroup_stop" ).disabled = false;
    
    var basedOnSelectBox = document.getElementById( "basedOnShowFormId" );
    if ( basedOnSelectBox.options.length == 5 )
    {
    	basedOnSelectBox.remove( 4 );
    }
  }
  
  
}

//********************************************************************
var _limitationsLookupHttpRequest = null;

//*********************************************************************
function getLookupURL()
{
  return document.getElementById("fldServletPath").value
  + "?cz=" + document.getElementById("fldCZ").value
  + "&envName=" + document.getElementById("fldEnvName").value
  + "&dateFormat=" + document.getElementById("fldDateFormat").value
  + "&companyCode=" + document.getElementById("fldCompanyCode").value
  + "&ruserId=" + document.getElementById("fldRUserId").value
  + "&sessionId=" + document.getElementById("fldSessionId").value
  + "&jobname=" + "FundLimitations_AddLookup"
  + "&bgcolor=" + document.getElementById("bgcolor").value;
}

//*********************************************************************
function getSubmitURL()
{
  return document.getElementById("fldServletPath").value
  + "?cz=" + document.getElementById("fldCZ").value
  + "&envName=" + document.getElementById("fldEnvName").value
  + "&dateFormat=" + document.getElementById("fldDateFormat").value
  + "&companyCode=" + document.getElementById("fldCompanyCode").value
  + "&ruserId=" + document.getElementById("fldRUserId").value
  + "&sessionId=" + document.getElementById("fldSessionId").value
  + "&jobname=" + "FundLimitations_AddSubmit"
  + "&bgcolor=" + document.getElementById("bgcolor").value;
}

//*********************************************************************
function getMainScreenURL()
{
  return document.getElementById("fldServletPath").value
  + "?cz=" + document.getElementById("fldCZ").value
  + "&envName=" + document.getElementById("fldEnvName").value
  + "&dateFormat=" + document.getElementById("fldDateFormat").value
  + "&companyCode=" + document.getElementById("fldCompanyCode").value
  + "&ruserId=" + document.getElementById("fldRUserId").value
  + "&sessionId=" + document.getElementById("fldSessionId").value
  + "&jobname=" + "FundLimitations_Main"
  + "&bgcolor=" + document.getElementById("bgcolor").value;
}

//*********************************************************************
function getBaseData()
{
  if ( document.getElementById("fldUpdateLevel").value.toLowerCase() == "brokerbranchrep" )
  {
    var s = "";
    s += "&updatelevel=BROKER";
    s += "&broker=" + document.getElementById("fldBroker").value;
    s += "&branch=" + document.getElementById("fldBranch").value;
    s += "&slsrep=" + document.getElementById("fldSalesRep").value;
    return s;
  }
  else
  {
    var s = "";
    s += "&updatelevel=ACCOUNT";
    s += "&account=" + document.getElementById("fldAccount").value;
    return s;
  }
}

//*********************************************************************
function getRuleData()
{
  var s = "";
  s += "&ruletype=" + document.getElementById("ruleTypeDropdown").value;
  s += "&startdate=" + document.getElementById("startDate").value;
  s += "&stopdate=" + document.getElementById("endDate").value;

  return s;
}

//*********************************************************************
function validStartDate()
{
  var startDateFld = document.getElementById("startDate");
  return(startDateFld.value.length != 0) && (startDateFld.validDate) && (startDateFld.value != "31/12/9999");
}

//*********************************************************************
function validStopDate()
{
  var stopDateFld = document.getElementById("endDate");
  return(stopDateFld.value.length != 0) && (stopDateFld.validDate);
}


/*******************************************************************************
 * FUND SPONSOR - LIMITATIONS LOOKUP
 *******************************************************************************/
function fundSponsorLimitationsLookup()
{
  if ( !validStartDate() )
  {
    alert("Invalid Start date");
    document.getElementById("startDate").focus;
    return;
  }
  else if ( !validStopDate() )
  {
    alert("Invalid End date");
    document.getElementById("endDate").focus;
    return;
  }

  var url = getLookupURL();

  var lookupStr = getBaseData();
  lookupStr += getRuleData();

  if ( document.getElementById("fundSponsor_fundSponsorDropdown").value.length <= 1 )
  {
    alert("No Fund Sponsor selected.")
    return;
  }
  lookupStr += "&fundsponsor=" + document.getElementById("fundSponsor_fundSponsorDropdown").value;

  if ( document.getElementById("divFundSponsor_amt").style.display == "block" )
  {
    lookupStr += "&overrideamt=" + document.getElementById("fundSponsor_amt").value;
    lookupStr += "&overridelog=no";
  }
  else
  {
  	lookupStr += "&overridelog=" + document.getElementById("fundSponsor_allow").value;
  }

  lookupStr += "&onlineewi=" + document.getElementById("fundSponsor_onlineewi").value;
  lookupStr += "&cycleewi=" + document.getElementById("fundSponsor_cycleewi").value;
  lookupStr += "&esgewi=" + document.getElementById("fundSponsor_esgewi").value;

  if ( document.getElementById("fundSponsor_exclude").checked )
  {
    lookupStr += "&excluderule=yes";
  }
  if ( document.getElementById("fundSponsor_stop").checked )
  {
    lookupStr += "&stoprule=yes";
  }

  disableInputFields();

  document.getElementById('loadingBar3').style.display='block';
  showLoading();


  _limitationsLookupHttpRequest = new ActiveXObject("MSXML2.XMLHTTP");
  _limitationsLookupHttpRequest.open("POST", url + lookupStr, true);
  _limitationsLookupHttpRequest.onreadystatechange = handleLimitationsLookupResponse;

  _limitationsLookupHttpRequest.send(getCurPendingRulesXML());
}

/*******************************************************************************
 * FUND - LIMITATIONS LOOKUP
 *******************************************************************************/
function fundLimitationsLookup()
{
  if ( !validStartDate() )
  {
    alert("Invalid Start date");
    return;
  }
  else if ( !validStopDate() )
  {
    alert("Invalid End date");
    return;
  }

  var url = getLookupURL();

  var lookupStr = getBaseData();
  lookupStr += getRuleData();

  lookupStr += "&fundsponsor=" + document.getElementById("fund_fundSponsorDropdown").value;

  if ( document.getElementById("fund_fundName").code == "" )
  {
    alert("Invalid Fund.")
    return;
  }
  lookupStr += "&fund=" + document.getElementById("fund_fundName").code;

  if ( document.getElementById("fund_fundName").fundClass == "*" )
  {
    lookupStr += "&class=";
  }
  else
  {
    lookupStr += "&class=" + document.getElementById("fund_fundName").fundClass;
  }

  if ( document.getElementById("divFund_amt").style.display == "block" )
  {
    lookupStr += "&overrideamt=" + document.getElementById("fund_amt").value;
    lookupStr += "&overridelog=no";
  }
  else
  {
  	lookupStr += "&overridelog=" + document.getElementById("fund_allow").value;
  }

  lookupStr += "&onlineewi=" + document.getElementById("fund_onlineewi").value;
  lookupStr += "&cycleewi=" + document.getElementById("fund_cycleewi").value;
  lookupStr += "&esgewi=" + document.getElementById("fund_esgewi").value;

  if ( document.getElementById("fund_exclude").checked )
  {
    lookupStr += "&excluderule=yes";
  }
  if ( document.getElementById("fund_stop").checked )
  {
    lookupStr += "&stoprule=yes";
  }

  disableInputFields()

  document.getElementById('loadingBar3').style.display='block';
  showLoading();

  _limitationsLookupHttpRequest = new ActiveXObject("MSXML2.XMLHTTP");
  _limitationsLookupHttpRequest.open("POST", url + lookupStr, true);
  _limitationsLookupHttpRequest.onreadystatechange = handleLimitationsLookupResponse;

  _limitationsLookupHttpRequest.send(getCurPendingRulesXML());
}

/*******************************************************************************
 * CLASS - LIMITATIONS LOOKUP
 *******************************************************************************/
function classLimitationsLookup()
{
  if ( !validStartDate() )
  {
    alert("Invalid Start date");
    return;
  }
  else if ( !validStopDate() )
  {
    alert("Invalid End date");
    return;
  }

  var url = getLookupURL();

  var lookupStr = getBaseData();
  lookupStr += getRuleData();

  lookupStr += "&fundsponsor=" + document.getElementById("class_fundSponsorDropdown").value;

  if ( document.getElementById("class_classBox").value.length == 0 )
  {
    alert("Class not entered");
    return;
  }
  lookupStr += "&class=" + document.getElementById("class_classBox").value;

  if ( document.getElementById("divClass_amt").style.display == "block" )
  {
    lookupStr += "&overrideamt=" + document.getElementById("class_amt").value;
    lookupStr += "&overridelog=no";
  }
  else
  {
  	lookupStr += "&overridelog=" + document.getElementById("class_allow").value;
  }

  lookupStr += "&onlineewi=" + document.getElementById("class_onlineewi").value;
  lookupStr += "&cycleewi=" + document.getElementById("class_cycleewi").value;
  lookupStr += "&esgewi=" + document.getElementById("class_esgewi").value;

  if ( document.getElementById("class_exclude").checked )
  {
    lookupStr += "&excluderule=yes";
  }
  if ( document.getElementById("class_stop").checked )
  {
    lookupStr += "&stoprule=yes";
  }

  disableInputFields();

  document.getElementById('loadingBar3').style.display='block';
  showLoading();

  _limitationsLookupHttpRequest = new ActiveXObject("MSXML2.XMLHTTP");
  _limitationsLookupHttpRequest.open("POST", url + lookupStr, true);
  _limitationsLookupHttpRequest.onreadystatechange = handleLimitationsLookupResponse;

  _limitationsLookupHttpRequest.send(getCurPendingRulesXML());
}


/*******************************************************************************
 * FUND GROUP - LIMITATIONS LOOKUP
 *******************************************************************************/
function fundGroupLimitationsLookup()
{
  if ( !validStartDate() )
  {
    alert("Invalid Start date");
    return;
  }
  else if ( !validStopDate() )
  {
    alert("Invalid End date");
    return;
  }

  var url = getLookupURL();

  var lookupStr = getBaseData();
  lookupStr += getRuleData();

  lookupStr += "&fundGroup=" + document.getElementById("fundGroup_fundGroupDropdown").value;
  
  if ( document.getElementById("divFundGroup_amt").style.display == "block" )
  {
    lookupStr += "&overrideamt=" + document.getElementById("fundGroup_amt").value;
    lookupStr += "&overridelog=no";
  }
  else
  {
    lookupStr += "&overridelog=" + document.getElementById("fundGroup_allow").value;
  }

  lookupStr += "&onlineewi=" + document.getElementById("fundGroup_onlineewi").value;
  lookupStr += "&cycleewi=" + document.getElementById("fundGroup_cycleewi").value;
  lookupStr += "&esgewi=" + document.getElementById("fundGroup_esgewi").value;

  if ( document.getElementById("fundGroup_exclude").checked )
  {
    lookupStr += "&excluderule=yes";
  }
  if ( document.getElementById("fundGroup_stop").checked )
  {
    lookupStr += "&stoprule=yes";
  }

  disableInputFields();

  document.getElementById('loadingBar3').style.display='block';
  showLoading();

  _limitationsLookupHttpRequest = new ActiveXObject("MSXML2.XMLHTTP");
  _limitationsLookupHttpRequest.open("POST", url + lookupStr, true);
  _limitationsLookupHttpRequest.onreadystatechange = handleLimitationsLookupResponse;

  _limitationsLookupHttpRequest.send(getCurPendingRulesXML());
}


//*********************************************************************
function handleLimitationsLookupResponse()
{
  if ( _limitationsLookupHttpRequest.readyState == 4 )
  {
    if ( _limitationsLookupHttpRequest.status == 200 )
    {
      //alert(_limitationsLookupHttpRequest.responseText);

      var response = _limitationsLookupHttpRequest.responseText.substring(18, _limitationsLookupHttpRequest.responseText.indexOf("</responseContents>"));

      if ( response.length == 0 )
      {
        alert("Lookup error: no response");
        enableInputFields();
        onRuleTypeChange( document.getElementById( "ruleTypeDropdown" ) )
      }
      else if ( response.indexOf("<error>") != -1 )
      {
        var msg = response.substring(7, response.indexOf("</error>"));
        alert("Lookup error: " + msg);
        enableInputFields();
        onRuleTypeChange( document.getElementById( "ruleTypeDropdown" ) );
      }
      else
      {
        clearGrid("ruleList");
        var newRuleCount = response.substring(response.indexOf("<newRuleCount>") + 14, response.indexOf("</newRuleCount>"));
        document.getElementById("lblNewRecords").innerHTML = newRuleCount
        var stoppedRuleCount = response.substring(response.indexOf("<stoppedRuleCount>") + 18, response.indexOf("</stoppedRuleCount>"));
        document.getElementById("lblStoppedRecords").innerHTML = stoppedRuleCount

        document.getElementById("FundRuleTable").innerHTML = response;

        var ruleListTbl = document.getElementById("ruleList");
        if ( ruleListTbl.firstChild.childNodes.length > 1 )
        {
          onRuleSelect(ruleListTbl.firstChild.childNodes[1]);
          enableButtons();
        }
      }

      hideLoading();
    }
  }
}

//*********************************************************************
var _rulesArray = new Array();

//*********************************************************************
function onRuleSelect(row)
{
  _currentRow = Number(row.id.substr(3, (row.id.length-3)));

  if ( row != null )
  {
    if ( window.event && window.event.ctrlKey )
    {
      _rulesArray[_rulesArray.length] = row;
      highlightRow(null, row);
    }
    else
    {
      highlightRow(_rulesArray, row);
      delete _rulesArray;
      _rulesArray = new Array();
      _rulesArray[0] = row;
    }
  }
}

//*********************************************************************
function highlightRow(prevSel, newSel)
{
  if( prevSel != null )
  {
    for (var i = 0;  i<prevSel.length; i++)
    {
      prevSel[i].style.background = 'white';
      prevSel[i].style.color = 'black';
    }
  }

  newSel.style.background = "darkBlue";
  newSel.style.color = "white";
}

//*********************************************************************
function clearGrid(tableId)
{
  var grid = document.getElementById(tableId).firstChild;
  var gridRows = grid.childNodes;

  // don't delete the row header
  for ( var i = gridRows.length - 1; i > 0; i-- )
  {
    grid.removeChild(gridRows[i]);
  }
}

//*********************************************************************
function deleteRules()
{
  for ( var i = _rulesArray.length - 1; i >= 0; i-- )
  {
    _rulesArray[i].parentNode.removeChild(_rulesArray[i]);
    delete _rulesArray[i];
  }
  _rulesArray = new Array();

  // check see if deleted only rule in list - disable buttons if so
  var ruleTable = document.getElementById("ruleList");
  if ( ruleTable.firstChild.childNodes.length < 2 )
  {
    disableButtons();
  }
}

//*********************************************************************
var _ruleSubmitHttpRequest = null;
var _addRuleCount = null;

//*********************************************************************
function submitRules()
{
  var url = getSubmitURL();

  var dataStr = "";
  dataStr += "&account=" + document.getElementById("fldAccount").value;
  dataStr += "&broker=" + document.getElementById("fldBroker").value;
  dataStr += "&branch=" + document.getElementById("fldBranch").value;
  dataStr += "&slsrep=" + document.getElementById("fldSalesRep").value;
  dataStr += "&ruletype=" + document.getElementById("ruleTypeDropdown").value;

  var rulesXML = "";
  var rulesTable = document.getElementById("ruleList");
  var rulesTableRows = rulesTable.firstChild.childNodes;

  showLoading("Updating");

  // not interested in header row
  _addRuleCount = rulesTableRows.length - 1;
  for ( var i = 1; i < rulesTableRows.length; i++ )
  {
    var cols = rulesTableRows[i].childNodes;
    var ruleXMLStr = "";
    ruleXMLStr += XML_Lib.createXMLStr("fund", cols[1].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("class", cols[2].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("fundGroup", cols[3].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("overridelog", cols[8].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("overrideamt", cols[15].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("overridechar", "");
    ruleXMLStr += XML_Lib.createXMLStr("onlineewi", cols[9].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("cycleewi", cols[10].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("esgewi", cols[11].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("updateStatus", "");
    ruleXMLStr += XML_Lib.createXMLStr("errorDesc", "");
    ruleXMLStr += XML_Lib.createXMLStr("controlsid", cols[13].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("version", cols[14].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("startdate", cols[5].innerHTML);
    ruleXMLStr += XML_Lib.createXMLStr("stopdate", cols[6].innerHTML);

    // wrap up the rule
    rulesXML += XML_Lib.createXMLStr("PendingRule", ruleXMLStr);
  }
  // wrap up the rules
  rulesXML = XML_Lib.createXMLStr("PendingRules", rulesXML);

  _ruleSubmitHttpRequest = new ActiveXObject("MSXML2.XMLHTTP");
  _ruleSubmitHttpRequest.open("POST", url + dataStr, true);
  _ruleSubmitHttpRequest.onreadystatechange = handleRuleSubmitResponse;

  _ruleSubmitHttpRequest.send(rulesXML);
}

//*********************************************************************
function handleRuleSubmitResponse()
{
  if ( _ruleSubmitHttpRequest.readyState == 4 )
  {
    if ( _ruleSubmitHttpRequest.status == 200 )
    {
      //alert(_ruleSubmitHttpRequest.responseText);

      // response text is of the form "<responseContents> .... </responseContents>"
      var response = _ruleSubmitHttpRequest.responseText.substring(18, _ruleSubmitHttpRequest.responseText.indexOf("</responseContents>"));

      if ( response.length == 0 )
      {
        alert("Rule submit error: no response");
      }
      else
      {
        var responseStatus = response.substring(response.indexOf("<responseStatus>") + 16, response.indexOf("</responseStatus"));

        if ( responseStatus.toLowerCase() == "accepted" )
        {
          alert("Rules updated successfully.")
          clearGrid("ruleList");
          reset();
          enableInputFields();

          // set updateStatus - for desktop confirmation
          setUpdatesCompleted();
        }
        else
        {
          clearGrid("ruleList");
          document.getElementById("FundRuleTable").innerHTML = response.substring(response.indexOf("<errorDisp>") + 11, response.indexOf("</errorDisp>"));

          var errorCount = document.getElementById("ruleList").firstChild.childNodes.length - 1;

          //if any rule went through correctly, setUpdateStatus
          if ( errorCount < _addRuleCount )
          {
            setUpdatesCompleted();
          }
          enableInputFields();
        }
        disableButtons();
      }
    }
    else
    {
      alert("Http Request Error: " + _ruleSubmitHttpRequest.status);
    }
    hideLoading();
  }
}

//*********************************************************************
function cancel()
{
  var confirmed = true;

  // check is any pending rules
  if ( document.getElementById("ruleList").firstChild.childNodes.length - 1 > 0 )
  {
    confirmed = confirm("Are you sure you want to discard changes?");
  }

  if ( confirmed )
  {
    window.location.href = getMainScreenURL() + "&option=" + document.getElementById("fldUpdateLevel").value
    + "&AccountNum=" + document.getElementById("fldAccount").value
    + "&broker=" + document.getElementById("fldBroker").value
    + "&branch=" + document.getElementById("fldBranch").value
    + "&salesRep=" + document.getElementById("fldSalesRep").value
    + "&updateStatus=" + isUpdatesCompleted()
    + "&bgcolor=" + document.getElementById("bgcolor").value;
  }
}

//*********************************************************************
function addHandleOnKeydown( divName )
{
  var keyCode = event.keyCode;

  var currentRowId  = "row" + Number(parseInt(_currentRow));
  var nextRowId     = "row" + Number(parseInt(_currentRow)+1);
  var previousRowId = "row" + Number(parseInt(_currentRow)-1);

  // Distance from top of table to top of selected row
  var rowPosition = document.getElementById(currentRowId).offsetTop;

  // Distance from top of table to top of visible part of div
  var scrollTop = document.getElementById( divName ).scrollTop;

  // Height of the visible div
  var visibleDivHeight = document.getElementById( divName ).clientHeight;

  if ( isUpArrow(keyCode) && _currentRow > 1 )
  {
    if ( rowPosition<scrollTop+38 && rowPosition< scrollTop + 48 )
    {

      for ( var i = 0; i < 15; i++ )
        document.getElementById( divName ).scrollTop--;
    }

    onRuleSelect(document.getElementById(previousRowId));
    document.getElementById(previousRowId).focus();
    event.returnValue = true;

  }
  else if ( isDownArrow(keyCode) && document.getElementById(nextRowId)!=null )
  {
    if ( (rowPosition) > (scrollTop + visibleDivHeight - 25) && (rowPosition) > (scrollTop + visibleDivHeight - 35) )
    {
      for ( var i = 0; i < 15; i++ )
        document.getElementById( divName ).scrollTop++;
    }

    onRuleSelect(document.getElementById(nextRowId));
    document.getElementById(nextRowId)  .focus();
    event.returnValue = true;

  }
  else if ( isEnter(keyCode) )
  {
    // Pressing enter currently doesn't do anything
  }

  event.returnValue = false;
}
