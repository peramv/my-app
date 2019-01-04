var _updatesSubmitted = null;

//******************************************************
function loading()
{
	IFDSTableManager.init();
}

//******************************************************
function clickHandler_closeBtn()
{
	UTL.getElem( "btnConfirmDlg" ).click();
}

//******************************************************
function clickHandler_updateBtn()
{
	var updateXML = buildUpdateXML();
	
	//dont need this if check anymore since update button won't be enabled unless there is a update
	/*if(updateXML != "")
	{*/
		//alert(updateXML);
		
		function getUpdateResponse(responseText)
		{
			//alert(responseText);
			var responseXML = null;
			try 
			{
				responseXML = XML.parseToXML( responseText );
				
				if(responseXML.text == "S")
				{
					//alert("Update Succeeded");
					reloadPage();
				}
				else
				{
					alert("Update Failed\n\n" + responseXML.text);
				}
			}
			catch( e )
			{ 
				alert( "FUNCTION ERROR: update error caught: " + e.description ); 		
			}
		}
		
		var paramMap = {}
		paramMap["cz"]                = _vCZ;
		paramMap["jobname"]           = "AccountStaticDataVerify_Process";
		paramMap["envName"]           = _envName;
		paramMap["ruserId"]           = _ruserId;
		paramMap["bgcolor"]       	  = _vDesktopColor;
		paramMap["sessionId"]         = _sessionId;
		paramMap["AccountNum"]		  = _AccountNum;
		
		var url = HTTP.buildURL(_vServletPath, paramMap);

		var req = HTTP.getPOSTRequest(url);
		req.setCallbackFunction( getUpdateResponse );
		req.setAsynch(false);
		req.send(updateXML);
		
	/*}
	else
	{
		alert("Nothing to update");
	}*/
}

//******************************************************
function reloadPage()
{
	var paramMap = {}
	paramMap["cz"]                = _vCZ;
	paramMap["jobname"]           = "AccountStaticDataVerify_Main";
	paramMap["envName"]           = _envName;
	paramMap["ruserId"]           = _ruserId;
	paramMap["bgcolor"]       	  = _vDesktopColor;
	paramMap["sessionId"]         = _sessionId;
	paramMap["AccountNum"]		  = _AccountNum;
	paramMap["updatesSubmitted"]  = "true";
	
	var url = HTTP.buildURL(_vServletPath, paramMap);
	
	window.location = url;
}

/*
function clickHandler_closeBtn()
{	
	//do close
	alert("close clicked\nthen?");
}
*/
//******************************************************
function buildUpdateXML()
{
	var verifiedEntities = "";
	
	var verifyStatus = document.getElementsByName("verifyStat");
	for(var i = 0; i < verifyStatus.length; ++i)
	{
		if(verifyStatus[i].options[verifyStatus[i].selectedIndex].value == "Verified" && verifyStatus[i].disabled == false)
		{
			var entityID = verifyStatus[i].parentNode.nextSibling.firstChild.nodeValue;
			verifiedEntities += XML.createNodeStr("entityID", entityID);
		}
	}
	
	
	var rtnXML = "";
	
	if(verifiedEntities != "")
	{
		rtnXML += "<EntityVerifyUpdReq>";
		rtnXML += verifiedEntities;
		rtnXML += "</EntityVerifyUpdReq>";
	}
	
	return rtnXML;
}

//******************************************************
function ddlChangeHandler_verifyStat()
{
	if(isUpdated())
	{
		document.getElementById("btnUpdate").disabled = false;
	}
	else
	{
		document.getElementById("btnUpdate").disabled = true;
	}
}

//******************************************************
function isUpdated()
{
	var verifyStatus = document.getElementsByName("verifyStat");
	for(var i = 0; i < verifyStatus.length; ++i)
	{
		if(verifyStatus[i].options[verifyStatus[i].selectedIndex].value == "Verified" && verifyStatus[i].disabled == false)
		{
			return true;
		}
	}
	return false;
}

//******************************************************
function getUpdateStatus()
{	
	return _updatesSubmitted;	
}