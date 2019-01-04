/*************************************************************************************
 * getBaseNavURL()
 *************************************************************************************/
function getBaseNavURL()
{	
	return document.getElementById("fldServletPath").value 
		+ "?cz=" + document.getElementById("fldCZ").value 
		+ "&envName=" + document.getElementById("fldEnvName").value
		+ "&companyCode=" + document.getElementById("fldCompanyCode").value
		+ "&ruserId=" + document.getElementById("fldRUserId").value 
		+ "&sessionId=" + document.getElementById("fldSessionId").value;
		
}



/*************************************************************************************
 * goToAddPage()
 *************************************************************************************/
function goToAddPage() 
{
	
	var option = document.getElementById("fldOption").value;
	
	if(option == "account")
	{
		var accountNum = document.getElementById("fldAccountNum").value;
		if(accountNum.length > 0)
		{
			window.location.href = getBaseNavURL() + "&jobname=FundLimitations_MainScreen2&option=account&accountNum=" + accountNum + "&updateStatus=" + getUpdateStatus();
		}
		else
		{
			alert("Error: Account number received");
		} 	
	}
	// option = brokerBranchRep
	else
	{
		var broker = document.getElementById("brokerBox").code;
		var branch = "";
		var rep = "";
		if(broker.length > 0)
		{			
			branch = document.getElementById("branchBox").code;
			if(branch.length > 0)
			{
				rep = document.getElementById("repBox").code;				
			}
			window.location.href = getBaseNavURL() + "&jobname=FundLimitations_MainScreen2&option=brokerBranchRep" + "&broker=" + broker + "&branch=" + branch + "&salesRep=" + rep + "&updateStatus=" + getUpdateStatus();
		}
		else
		{
			alert("Must enter valid Broker information.")
		}	
	}
}



/*************************************************************************************
 * goToModifyPage()
 *************************************************************************************/
function goToModifyPage() {
	var option;
	var x = document.getElementById('fldAccountNum');

	//if there is account number
	if (curRuleArray[0] != null) 
	{

		var modifyIframe = document.getElementById('modifyIframe');
		document.getElementById("mainBorderCover").style.display = "block";
		modifyIframe.src = "javascript:'Loading...'";
		modifyIframe.style.display = "block";
				
		if (x != null && x.innerHTML != null) 
		{
			option="account";
			accountNum=x.value;
							
			modifyIframe.src= getBaseNavURL() + "&jobname=FundLimitations_ModifyScreen&option=" +option+ "&accountNum=" +accountNum+ "&ruleType=" +curRuleArray[0].childNodes[3].innerHTML+ "&startDate=" +curRuleArray[0].childNodes[4].innerHTML+ "&endDate=" +curRuleArray[0].childNodes[5].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&fundLimitationType=" +ruleTypeDropdown.value+ "&minInitPurchase=" +curRuleArray[0].childNodes[6].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&onlineEWI=" +curRuleArray[0].childNodes[8].innerHTML+ "&cycleEWI=" +curRuleArray[0].childNodes[9].innerHTML+ "&ESGEWI=" +curRuleArray[0].childNodes[10].innerHTML+ "&ruleTypeCode=" +curRuleArray[0].childNodes[12].innerHTML+ "&overridelog=" + curRuleArray[0].childNodes[14].innerHTML + "&fund=" +curRuleArray[0].childNodes[1].innerHTML+ "&class=" +curRuleArray[0].childNodes[2].innerHTML + "&controlsid=" +curRuleArray[0].childNodes[13].innerHTML+ "&version=" + curRuleArray[0].childNodes[17].innerHTML;		
		}		
		//if there is broker info in the box
		else if (document.getElementById('brokerBox').code !=null && document.getElementById('brokerBox').code !="") 
		{		
			option="brokerBranchRep";
			broker=document.getElementById('brokerBox').code;
			//if there is branch info		
			if (document.getElementById('branchBox').code != null && document.getElementById('branchBox').code != "") 
			{
				branch=document.getElementById('branchBox').code;
				//if we have broker branch and rep
				if (document.getElementById('repBox').code != null && document.getElementById('repBox').code != "") 
				{
					salesRep = document.getElementById('repBox').code;					
					modifyIframe.src= getBaseNavURL() + "&jobname=FundLimitations_ModifyScreen&option=" +option+ "&broker=" +broker+ "&branch=" +branch+ "&salesRep=" +salesRep+  "&ruleType=" +curRuleArray[0].childNodes[3].innerHTML+ "&startDate=" +curRuleArray[0].childNodes[4].innerHTML+ "&endDate=" +curRuleArray[0].childNodes[5].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&fundLimitationType=" +ruleTypeDropdown.value+ "&minInitPurchase=" +curRuleArray[0].childNodes[6].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&onlineEWI=" +curRuleArray[0].childNodes[8].innerHTML+ "&cycleEWI=" +curRuleArray[0].childNodes[9].innerHTML+ "&ESGEWI=" +curRuleArray[0].childNodes[10].innerHTML+ "&ruleTypeCode=" +curRuleArray[0].childNodes[12].innerHTML+ "&overridelog=" + curRuleArray[0].childNodes[14].innerHTML + "&fund=" +curRuleArray[0].childNodes[1].innerHTML+ "&class=" +curRuleArray[0].childNodes[2].innerHTML + "&controlsid=" +curRuleArray[0].childNodes[13].innerHTML+ "&version=" + curRuleArray[0].childNodes[17].innerHTML;
				}
				//we only have broker and branch
				else 
				{					
					modifyIframe.src= getBaseNavURL() + "&jobname=FundLimitations_ModifyScreen&option=" +option+ "&broker=" +broker+ "&branch=" +branch+  "&ruleType=" +curRuleArray[0].childNodes[3].innerHTML+ "&startDate=" +curRuleArray[0].childNodes[4].innerHTML+ "&endDate=" +curRuleArray[0].childNodes[5].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&fundLimitationType=" +ruleTypeDropdown.value+ "&minInitPurchase=" +curRuleArray[0].childNodes[6].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&onlineEWI=" +curRuleArray[0].childNodes[8].innerHTML+ "&cycleEWI=" +curRuleArray[0].childNodes[9].innerHTML+ "&ESGEWI=" +curRuleArray[0].childNodes[10].innerHTML+ "&ruleTypeCode=" +curRuleArray[0].childNodes[12].innerHTML+ "&overridelog=" + curRuleArray[0].childNodes[14].innerHTML + "&fund=" +curRuleArray[0].childNodes[1].innerHTML+ "&class=" +curRuleArray[0].childNodes[2].innerHTML + "&controlsid=" +curRuleArray[0].childNodes[13].innerHTML+ "&version=" + curRuleArray[0].childNodes[17].innerHTML;
				}
			}
			//we only have broker
			else 
			{				
				modifyIframe.src= getBaseNavURL() + "&jobname=FundLimitations_ModifyScreen&option=" +option+ "&broker=" +broker+ "&salesRep=" +salesRep+  "&ruleType=" +curRuleArray[0].childNodes[3].innerHTML+ "&startDate=" +curRuleArray[0].childNodes[4].innerHTML+ "&endDate=" +curRuleArray[0].childNodes[5].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&fundLimitationType=" +ruleTypeDropdown.value+ "&minInitPurchase=" +curRuleArray[0].childNodes[6].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&onlineEWI=" +curRuleArray[0].childNodes[8].innerHTML+ "&cycleEWI=" +curRuleArray[0].childNodes[9].innerHTML+ "&ESGEWI=" +curRuleArray[0].childNodes[10].innerHTML+ "&ruleTypeCode=" +curRuleArray[0].childNodes[12].innerHTML+ "&overridelog=" + curRuleArray[0].childNodes[14].innerHTML + "&fund=" +curRuleArray[0].childNodes[1].innerHTML+ "&class=" +curRuleArray[0].childNodes[2].innerHTML + "&controlsid=" +curRuleArray[0].childNodes[13].innerHTML+ "&version=" + curRuleArray[0].childNodes[17].innerHTML;
			}
		}
		//if there is no broker info in box
		else 
		{
			alert('The broker branch and rep fields have not been properly filled in or the account number was not filled in.');
		}	
	}
	else 
	{
		alert('Please select a rule to modify');
	}
}



/*************************************************************************************
 * stopLimitations()
 *************************************************************************************/
var _httpRequestStop = null;
var _stopLimitationsRuleCount = null;
function stopLimitations() 
{
	var option;
	var broker;
	var branch;
	var salesRep;
	var account_number;
	
	if (document.getElementById('mainAccountNumber')!= null && document.getElementById('mainAccountNumber').innerHTML != null) 
	{
		option="account";
	}
	else 
	{
		option="brokerBranchRep";
	}
	
	if (document.getElementById('brokerBox') != null && document.getElementById('brokerBox').code != null) 
	{
		broker=document.getElementById('brokerBox').code;
	}
	else 
	{
		broker="";
	}
	
	if (document.getElementById('branchBox') != null && document.getElementById('branchBox').code != null) 
	{
		branch=document.getElementById('branchBox').code;
	}
	else 
	{
		branch="";
	}
	
	if (document.getElementById('repBox') != null && document.getElementById('repBox').code != null) 
	{
		salesRep=document.getElementById('repBox').code;
	}
	else 
	{
		salesRep="";
	}
	
	if (document.getElementById('mainAccountNumber') != null && document.getElementById('mainAccountNumber').innerHTML != null) 
	{
		account_number=document.getElementById('fldAccountNum').value;
	}
	else 
	{
		account_number="";
	}
	
	var funder = document.getElementById('fundBox').code;			
	if (funder == null || funder == 'undefined') 
	{
		funder = "";
	}
	
	var rulesXML = "";
	var rulesTable = document.getElementById("accountList");
	var rulesTableRows = rulesTable.firstChild.childNodes;
	
	// keep track of num rules submitted (ie. num of rows in table, minus header)
	_stopLimitationsRuleCount = rulesTableRows.length - 1;
	for(var i = 1; i < rulesTableRows.length; i++)
	{
		var cols = rulesTableRows[i].childNodes;
		var ruleXMLStr = "";
		
		ruleXMLStr += XML_Lib.createXMLStr("controlsid", cols[13].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("ruleType", cols[12].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("fund", cols[1].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("class", cols[2].innerHTML);		
		ruleXMLStr += XML_Lib.createXMLStr("startdate", cols[4].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("stopdate", cols[5].innerHTML);		
		ruleXMLStr += XML_Lib.createXMLStr("overridelog", cols[14].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("overrideamt", cols[15].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("overridechar", cols[16].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("onlineewi", cols[8].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("cycleewi", cols[9].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("esgewi", cols[10].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("version", cols[17].innerHTML);
		ruleXMLStr += XML_Lib.createXMLStr("updateStatus", "");
		ruleXMLStr += XML_Lib.createXMLStr("errorDesc", "");
		ruleXMLStr += XML_Lib.createXMLStr("rowIndex", i);
		
		ruleXMLStr += XML_Lib.createXMLStr("searchtype", option);
		ruleXMLStr += XML_Lib.createXMLStr("mainfund", funder);
		ruleXMLStr += XML_Lib.createXMLStr("fundsponsor", document.getElementById("fundSponsorDropdown").value);
		ruleXMLStr += XML_Lib.createXMLStr("mainclass", document.getElementById('classBox').value);
		ruleXMLStr += XML_Lib.createXMLStr("mainruletype", document.getElementById('ruleTypeDropdown').value);
		ruleXMLStr += XML_Lib.createXMLStr("active", document.getElementById('onlyActiveBox').checked);
		ruleXMLStr += XML_Lib.createXMLStr("moreCounter", 1);
		
		// wrap up the rule
		rulesXML += XML_Lib.createXMLStr("PendingRule", ruleXMLStr);	
	}
	// wrap up the rules
	rulesXML = XML_Lib.createXMLStr("PendingRules", rulesXML);
		
	if(confirm ("Are you sure you want to stop all these records?"))
	{
		
		var url = getBaseNavURL()  + "&jobname=FundLimitations_StopLimitations&option=" +option+ "&AccountNum=" +account_number+ "&broker=" +broker+  "&branch=" +branch+ "&slsrep=" +salesRep;
					
		_httpRequestStop = new ActiveXObject("MSXML2.XMLHTTP");
							
		_httpRequestStop.open("POST", url, false);
	
		_httpRequestStop.onreadystatechange = handleStopLimitationsResponse;
		
		_httpRequestStop.send(rulesXML);
	
	}	
}



/*************************************************************************************
 * handleStopLimitationsResponse()
 *************************************************************************************/
function handleStopLimitationsResponse() 
{    
	if (_httpRequestStop.readyState == 4)
    {    
		if (_httpRequestStop.status == 200)
	   	{	   
	   	    var response = _httpRequestStop.responseText.substring(18, _httpRequestStop.responseText.indexOf("</responseContents>"));	   	    
	   	    if(response.length == 0)
        	{
        		alert("Error: no response");        		
        	}
        	else if (_httpRequestStop.responseText.indexOf("</Rejected>") !=-1) 
        	{
        		alert('Rejected: Data could not be found to match your request.');
        	}
        	else 
        	{
		   		document.getElementById('FundRuleTable').innerHTML=response;
		   		if (document.getElementById('accountList').firstChild != null && document.getElementById('accountList').firstChild.childNodes[1] != null) 
		   		{
		   			onAccountSelect(document.getElementById('accountList').firstChild.childNodes[1]);
		   		}
		   		
		   		//if at least one rule was stopped - set update status
		   		var errorCount = document.getElementById("accountList").firstChild.childNodes - 1
		   		if(_stopLimitationsRuleCount > errorCount)
		   		{
		   			setUpdateStatus();
		   		}
	   		}
	   	}
	   	else
       	{
        	alert("HTTP error: " + _httpRequestStop.status);
	   	}
	}	   
}



/*************************************************************************************
 * showAdminDates()
 *************************************************************************************/
function showAdminDates() 
{
	var stringOut = "";
	if (curRuleArray[0] != null) 
	{
		
		stringOut = "Processed Date: \t" + curRuleArray[0].childNodes[19].innerHTML + "\t   ";
		stringOut = stringOut + "User Name: \t" + curRuleArray[0].childNodes[21].innerHTML + "\n";
		stringOut = stringOut + "Mod Date: \t" + curRuleArray[0].childNodes[18].innerHTML + "\t   ";
		stringOut = stringOut + "Mod User: \t" + curRuleArray[0].childNodes[20].innerHTML + "\n";
	
	}
	else 
	{
		stringOut = "Please select an existing rule."
	}
    alert(stringOut);
}




/*************************************************************************************
 * deleteRow()
 *************************************************************************************/
function deleteRow() 
{
	var option;
	var broker;
	var branch;
	var salesRep;
	var account_number;
	if (document.getElementById('mainAccountNumber')!= null && document.getElementById('mainAccountNumber').innerHTML != null) 
	{
		option="account";
	}
	else 
	{
		option="brokerBranchRep";
	}
	
	if (document.getElementById('brokerBox') != null && document.getElementById('brokerBox').code != null) 
	{
		broker=document.getElementById('brokerBox').code;
	}
	else 
	{	
		broker="";
	}
	
	if (document.getElementById('branchBox') != null && document.getElementById('branchBox').code != null) 
	{
		branch=document.getElementById('branchBox').code;
	}
	else 
	{
		branch="";
	}
	
	if (document.getElementById('repBox') != null && document.getElementById('repBox').code != null) 
	{
		salesRep=document.getElementById('repBox').code;
	}
	else 
	{
		salesRep="";
	}
	
	if (document.getElementById('mainAccountNumber') != null && document.getElementById('mainAccountNumber').innerHTML != null) 
	{
		account_number=document.getElementById('fldAccountNum').value;
	}
	else 
	{
		account_number="";
	}
	
	if(curRuleArray != null)
	{
		for (var i = 0;  i<curRuleArray.length; i++) 
		{		
			var answer = confirm ("Are you sure you want to delete this record?");
			if (answer) 
			{
				var url = getBaseNavURL() + "&jobname=FundLimitations_Delete&option=" +option+ "&AccountNum=" + account_number + "&broker=" +broker+ "&branch=" +branch+ "&salesRep=" +salesRep+ "&fund=" +curRuleArray[0].childNodes[1].innerHTML+ "&class=" +curRuleArray[0].childNodes[2].innerHTML+ "&ruleType=" +curRuleArray[0].childNodes[3].innerHTML+ "&startDate=" +curRuleArray[0].childNodes[4].innerHTML+ "&endDate=" +curRuleArray[0].childNodes[5].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&fund=" +fundBox.value+ "&class=" +classBox.value+ "&fundLimitationType=" +curRuleArray[0].childNodes[12].innerHTML+ "&minInitPurchase=" +curRuleArray[0].childNodes[6].innerHTML+ "&fundSponsor=" +fundSponsorDropdown.value+ "&onlineEWI=" +curRuleArray[0].childNodes[8].innerHTML+ "&cycleEWI=" +curRuleArray[0].childNodes[9].innerHTML+ "&ESGEWI=" +curRuleArray[0].childNodes[10].innerHTML+ "&controlsid=" +curRuleArray[0].childNodes[13].innerHTML + "&overridelog=" +curRuleArray[0].childNodes[14].innerHTML+ "&overrideamt=" +curRuleArray[0].childNodes[15].innerHTML+ "&overridechar=" +curRuleArray[0].childNodes[16].innerHTML+ "&Version=" +curRuleArray[0].childNodes[17].innerHTML+ "&rowIndex=" +i;			
				_httpRequest = new ActiveXObject("MSXML2.XMLHTTP");					
				_httpRequest.open("POST", url, false);
				_httpRequest.onreadystatechange = handleDeleteResponse;	
				_httpRequest.send();				
			}
		}
	}	
}


/*************************************************************************************
 * handleDeleteResponse()
 *************************************************************************************/
function handleDeleteResponse() 
{
	if (_httpRequest.readyState == 4)
    {
		if (_httpRequest.status == 200)    		
	   	{       	   		
	   		var deletedRowIndex = _httpRequest.responseText.substring( _httpRequest.responseText.indexOf("<rowIndex>")+10,  _httpRequest.responseText.indexOf("</rowIndex>"));
	   		
	   		// error occurred    	   		     	   		
	   		if (_httpRequest.responseText.indexOf("<errorDesc>") != -1) 
	   		{
	   			alert('Error: '+ _httpRequest.responseText.substring( _httpRequest.responseText.indexOf("<errorDesc>")+11,  _httpRequest.responseText.indexOf("</errorDesc>")));    	   		
	   			curRuleArray[deletedRowIndex].childNodes[10].innerHTML='Error: '+ _httpRequest.responseText.substring( _httpRequest.responseText.indexOf("<errorDesc>")+11,  _httpRequest.responseText.indexOf("</errorDesc>"));
	   			curRuleArray[deletedRowIndex].style.color="red";	   		
	   		}
	   		// delete successful
	   		else 
	   		{
	   			alert(_httpRequest.responseText.substring( _httpRequest.responseText.indexOf("<updateStatus>")+14,  _httpRequest.responseText.indexOf("</updateStatus>")));
	   			curRuleArray[deletedRowIndex].parentNode.removeChild(curRuleArray[deletedRowIndex]);    	   			
	   			onAccountSelect(document.getElementById('accountList').firstChild.childNodes[1]);
	   			
	   			// updateStatus - for desktop confirmation
	   			setUpdateStatus();
	   			
	   			// if we deleted the only rule in the table, disable buttons
				if(document.getElementById("accountList").firstChild.childNodes.length == 1)
				{
					disableRuleActionButtons();
				}
	   		}
	   	}
    	else
        {
	       	alert("HTTP error: " + _httpRequest.status);
    	}
	}	   
}



/*************************************************************************************
 * closeModifyIframe()
 *************************************************************************************/
function closeModifyIframe(modified)
{
	var modifyIframe = document.getElementById('modifyIframe');
	modifyIframe.style.display = 'none';
	modifyIframe.src = "javascript:'Loading...'";
	document.getElementById("mainBorderCover").style.display = "none";
		
	if (modified == "yes")
	{ 
		FundReload();
		
		// set update status
		setUpdateStatus();
	}	
}

