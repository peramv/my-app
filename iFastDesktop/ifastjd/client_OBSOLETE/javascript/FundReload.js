
function getBaseReloadURL()
{	
	return document.getElementById("fldServletPath").value 
		+ "?cz=" + document.getElementById("fldCZ").value 
		+ "&envName=" + document.getElementById("fldEnvName").value
		+ "&companyCode=" + document.getElementById("fldCompanyCode").value
		+ "&ruserId=" + document.getElementById("fldRUserId").value 
		+ "&sessionId=" + document.getElementById("fldSessionId").value;
		
}


function populateClassList(fundSponsorFld)
{
	var classListStr = fundSponsorFld.options[fundSponsorFld.selectedIndex].fundSponsorClassList;
	var classListArray = classListStr.substring(0, classListStr.length - 2).split(",");
	
	document.getElementById("classBox").innerHTML = "";
	
	var emptyOpt = document.createElement("option");
	emptyOpt.value = "";
	emptyOpt.text = "";
	document.getElementById("classBox").add(emptyOpt);
		
	for(var i = 0; i < classListArray.length; i++)
	{
		var opt = document.createElement("option");
		opt.value = classListArray[i];
		opt.text = classListArray[i];
		document.getElementById("classBox").add(opt);
	}
	
}


var _httpRequest = null;
var moreCounter = 1;
var requestRecNum = 0;
var funder;
var classfinal;
var moreflag=0;

function FundReload(isIt)
{
	
	
	var option;
	var searchtype;
	var broker;
	var branch;
	var salesRep;
	var account_number;
	if (document.getElementById('mainAccountNumber')!= null && document.getElementById('mainAccountNumber').innerHTML != null) {option="account"; searchtype="ACCOUNT";}
	else {option="brokerBranchRep"; searchtype="BROKER";}
	if (document.getElementById('brokerBox') != null && document.getElementById('brokerBox').code != null) {broker=document.getElementById('brokerBox').code;}
	else {broker="";}
	if (document.getElementById('branchBox') != null && document.getElementById('branchBox').code != null) {branch=document.getElementById('branchBox').code;}
	else {branch="";}
	if (document.getElementById('repBox') != null && document.getElementById('repBox').code != null) {salesRep=document.getElementById('repBox').code;}
	else {salesRep="";}
	if (document.getElementById('mainAccountNumber') != null && document.getElementById('mainAccountNumber').innerHTML != null) {account_number=document.getElementById('fldAccountNum').value;}
	else {account_number="";}
	
	funder = document.getElementById('fundBox').code;		
	if (funder == null || funder == 'undefined' || document.getElementById('fundBox').value== null || document.getElementById('fundBox').value== 'undefined' || document.getElementById('fundBox').value== "" ||  document.getElementById('fundBox').value== " ") { funder = ""; }
	
	classfinal = document.getElementById('fundBox').fundClass;				
	if (classfinal == null || classfinal == 'undefined' || classfinal =='*' || classfinal =="" || document.getElementById('fundBox').value=="") {
		classfinal = document.getElementById('classBox').value; 
	}
	else {	
		document.getElementById('classBox').disabled=true;
	}
	
	//---check if the more button was clicked
	
	if (isIt == 'more') {
		moreCounter = Number(parseInt(moreCounter) + 100); moreflag=1;
	}
	else { moreCounter = 1; requestRecNum = 0; moreflag=0;}
	
	var url = getBaseReloadURL() + "&jobname=FundLimitations_Reload";
	_httpRequest = new ActiveXObject("MSXML2.XMLHTTP");	
			
	//send the request
	
	document.getElementById('loadingBar3').style.display='block';
	showLoading();


	if (document.getElementById('mainAccountNumber') != null && document.getElementById('mainAccountNumber').innerHTML != null) 
	{
		_httpRequest.open("POST", url + "&option=" +option+ "&searchtype=" +searchtype+ "&AccountNum=" +account_number+ "&broker=" +broker+  "&branch=" +branch+ "&slsrep=" +salesRep+  "&fund=" + funder + "&fundsponsor=" + document.getElementById("fundSponsorDropdown").value + "&class="+classfinal+"&ruletype="+document.getElementById('ruleTypeDropdown').value+"&active="+document.getElementById('onlyActiveBox').checked  + "&moreCounter=" + moreCounter, true);
		_httpRequest.onreadystatechange = handleResponse;		
		_httpRequest.send();
	}
	else if (document.getElementById('brokerBox').value !=null && document.getElementById('brokerBox').value !="") 
	{
		_httpRequest.open("POST", url + "&option=" +option+ "&searchtype=" +searchtype+ "&AccountNum=" +account_number+ "&broker=" +broker+  "&branch=" +branch+ "&slsrep=" +salesRep+ "&fund=" + funder + "&fundsponsor=" + document.getElementById("fundSponsorDropdown").value + "&class="+classfinal+"&ruletype="+document.getElementById('ruleTypeDropdown').value+"&active="+document.getElementById('onlyActiveBox').checked  + "&moreCounter=" + moreCounter, true);
		_httpRequest.onreadystatechange = handleResponse;		
		_httpRequest.send();			
	}
	else 
	{
		alert('The broker branch and rep fields have not been properly filled in or the account number was not filled in.');
	}					
}

function handleResponse() {
	if (_httpRequest.readyState == 4)
	    {
    		if (_httpRequest.status == 200)
    	   	{    	 
	    	   	var a = _httpRequest.responseText.indexOf('>UserName</th></tr>');
	    	   	var b = _httpRequest.responseText.indexOf('</table></div>');    	   		
    	   		requestRecNum = document.getElementById('accountList').requestRecNum;    	   		    	   		
    	   		if (_httpRequest.responseText.substring( a+19,  b) == null || _httpRequest.responseText.substring( a+19,  b) == "" || _httpRequest.responseText.substring( a+19,  b) == "<websrvXML><reques") {    	   			
    	   			if (moreflag == 0) { 
	    	   			//clear table
	    	   			
	    	   			document.getElementById('FundRuleTable').innerHTML=_httpRequest.responseText;
      	   			    alert('There are no records to be returned.');
      	   			    disableRuleActionButtons();      	   			        	   			   			
    	   			}    	 
    	   			else 
    	   			{
						alert("There are no more records to be returned.");
    	   			}    	   			
    	   		}
    	   		else {    	   		
    	   			document.getElementById('FundRuleTable').innerHTML=_httpRequest.responseText;
    	   			onAccountSelect(document.getElementById('accountList').firstChild.childNodes[1]);
    	   			enableRuleActionButtons();
    	   		}
    	   	}
    	   	else
           	{           		
	        	alert("HTTP error: " + _httpRequest.status);
    	   	}
    	   	hideLoading(); 	   	
		}
	else{	 
	 //window.setTimeout("showLoading();", 500);
	}			
}

function enableRuleActionButtons()
{
	document.getElementById("modifyBtn").disabled = false;
	document.getElementById("deleteBtn").disabled = false;
	document.getElementById("stopLimitationsBtn").disabled = false;
	document.getElementById("adminDatesBtn").disabled = false;
	document.getElementById("moreBtn").disabled = false;			
}


function disableRuleActionButtons()
{
	document.getElementById("modifyBtn").disabled = true;
	document.getElementById("deleteBtn").disabled = true;
	document.getElementById("stopLimitationsBtn").disabled = true;
	document.getElementById("adminDatesBtn").disabled = true;
	document.getElementById("moreBtn").disabled = true;			
}

function handleOnKeydown (row)
{
	    var keyCode = event.keyCode;
		
		var currentRowId = "row" + Number(parseInt(_currentRow)); 			
		var nextRowId = "row" + Number(parseInt(_currentRow)+1);
		var previousRowId = "row" + Number(parseInt(_currentRow)-1);
		
		// Distance from top of table to top of selected row
		var rowPosition = document.getElementById(currentRowId).offsetTop;
		// Distance from top of table to top of visible part of div
		var scrollTop = document.getElementById("accountListDiv").scrollTop;
		// Height of the visible div
		var visibileDivHeight = document.getElementById("accountListDiv").clientHeight; 

		if(isUpArrow(keyCode) && _currentRow > 1)
        {	
   			if (rowPosition<scrollTop+38 && rowPosition< scrollTop + 48){
        	  
        	   	for (var i = 0; i < 15; i++)
        	   		document.getElementById("accountListDiv").scrollTop--;
      	    }    
      	    
            onAccountSelect(document.getElementById(previousRowId));
            document.getElementById(previousRowId).focus();
			event.returnValue = true;

        }
        else if(isDownArrow(keyCode) && document.getElementById(nextRowId)!=null)
        {	
        	if ((rowPosition) > (scrollTop + visibileDivHeight - 25) && (rowPosition) > (scrollTop + visibileDivHeight - 35)){
        	   	for (var i = 0; i < 15; i++)
        	   		document.getElementById("accountListDiv").scrollTop++;
      	    }    
      	        	
            onAccountSelect(document.getElementById(nextRowId));
            document.getElementById(nextRowId).focus();
			event.returnValue = true;
            
        }
        else if(isEnter(keyCode))
        {
        	// Pressing enter currently doesn't do anything
        }

        event.returnValue = false;
	
}






