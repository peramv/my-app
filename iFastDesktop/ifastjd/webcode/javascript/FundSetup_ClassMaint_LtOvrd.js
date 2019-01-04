var _updatesMade = false;

var detailOvrdData = new Array();
var itemToMove = new Array();
var curDirection = "";

var _fundCode;
var _classCode;
var _TaxJurisList = {};
var _AcctTypeList = {};
var _TaxTypeList = {};
var _AcctDesignationList = {};
var _ProvResList = {};
var _RuleTypeMap = {};

//******************************************************
function loading()
{
	populateTable();
	
	resetEWILists();
	disableEWILists();
}

//******************************************************
function resetEWILists()
{
	var ewiListFlds = UTL.getElem( "EWIList", UTL.GET_ELEM_SEARCH_TYPE_NAME );
	for ( var i = 0; i < ewiListFlds.length; i++ )
	{
		ewiListFlds[i].selectedIndex = -1;
	}
}


//******************************************************
function fundLimitOverrideData(ruleType, ruleTypeDesc, overrideDec, overrideLog, taxJurisDecl, provResDecl, accountTypeDecl, taxTypeDecl, acctDesigDecl, onlineEWI, cycleEWI, esgEWI, fundLtOvrdRID, runMode)
{
	this.ruleType = ruleType;
	this.ruleTypeDesc = ruleTypeDesc;
	this.overrideDec = overrideDec;
	this.overrideLog = overrideLog;
	this.taxJurisDecl = taxJurisDecl;
	this.provResDecl = provResDecl;
	this.accountTypeDecl = accountTypeDecl;
	this.taxTypeDecl = taxTypeDecl;
	this.acctDesigDecl = acctDesigDecl;
	this.onlineEWI = onlineEWI;
	this.cycleEWI = cycleEWI;
	this.esgEWI = esgEWI;
	this.fundLtOvrdRID = fundLtOvrdRID;
	this.runMode = runMode;
}

//******************************************************
function reloadData()
{
	document.getElementsByName("RuleTypeList")[0].selectedIndex = 0;
	clearScreenFields();
	ruleTypeInquiry();
	
}

//******************************************************
function getDataTable()
{
	return UTL.getElem("LtOvrdTable").lastChild;
}

//******************************************************
function createDataRow(cell0Text, cell1Text)
{
	var newRow = document.createElement("tr");
	var cell0 = document.createElement("td");
	var cell1 = document.createElement("td");
	
	cell0.innerHTML = cell0Text;
	cell1.innerHTML = cell1Text;
	
	newRow.appendChild(cell0);
	newRow.appendChild(cell1);
	
	return newRow;
}

//******************************************************
function populateTable()
{
	var tblObj = getDataTable();
	
	//load data from detailOvrdData
	for(var i = 0; i < detailOvrdData.length; ++i)
	{
		var newRow = createDataRow(formatRuleType(detailOvrdData[i].ruleType.toString(), detailOvrdData[i].ruleTypeDesc), formatOverrideType(detailOvrdData[i]));
		tblObj.appendChild(newRow);
	}
	
	IFDSTableManager.init();
	setTableSelectHandler();	//we only have one select handler for this table, so hardcoded it inside the function
}

//******************************************************
function appendTableRow(cell0Text, cell1Text, selectedRowIndex)
{
	var tblObj = getDataTable();
	var newRow = createDataRow(cell0Text, cell1Text);
	tblObj.appendChild(newRow);
	
	IFDSTableManager.reInitTable( "LtOvrdTable" );
	setTableSelectHandler();
	
	if(selectedRowIndex >= 0)
	{
		IFDSTableManager.getTable("LtOvrdTable").setSelectedRowIndex(selectedRowIndex);
	}
}

//******************************************************
function setTableSelectHandler()
{
	IFDSTableManager.getTable("LtOvrdTable").setOnRowSelectedFunction(selectHandler_LtOvrdTable);
}

//******************************************************
function getSelectedInfo(ddlControl)
{
	var rtnVal = {};
	
	rtnVal.value = ddlControl.options[ddlControl.selectedIndex].value.toString();
	rtnVal.text = ddlControl.options[ddlControl.selectedIndex].text.toString();
	
	return rtnVal;
}

//******************************************************
function formatRuleType(inNum, inTxt)
{
	return inNum + "&nbsp;" + inTxt;
}

//******************************************************
function formatOverrideType(inObj)
{
	if (_RuleTypeMap[inObj.ruleType] == 'overrideDec')
	{
		return inObj.overrideDec;
	}
	else
	{
		return inObj.overrideLog;
	}	
}

//******************************************************
function getSelectedRowIndex()
{
	return IFDSTableManager.getTable("LtOvrdTable").getSelectedRowIndex();
}

//******************************************************
function ruleTypeInquiry()
{
	var ruleType = getSelectedInfo(document.getElementsByName("RuleTypeList")[0]);
	
	ruleType = "<LtOvrdInq><ruleType>" + ruleType.value + "</ruleType></LtOvrdInq>"
	
	function getPostbackStatus(responseText)
	{
		var responseXML = null;
		try 
		{
			responseXML = XML.parseToXML( responseText );
			
			if(responseXML.getElementsByTagName("status")[0].text == "Accepted")
			{
				var tblObj = getDataTable();

				var ovrdRules = responseXML.getElementsByTagName("FundLtOvrd");
				
				for(var i = 0; i < ovrdRules.length; ++i)
				{
					var newData = new fundLimitOverrideData(ovrdRules[i].getElementsByTagName("ruleType")[0].text,
															ovrdRules[i].getElementsByTagName("ruleTypeDesc")[0].text,
															ovrdRules[i].getElementsByTagName("overrideDec")[0].text,
															ovrdRules[i].getElementsByTagName("overrideLog")[0].text,
															ovrdRules[i].getElementsByTagName("taxJurisDecl")[0].text,
															ovrdRules[i].getElementsByTagName("provResDecl")[0].text,
															ovrdRules[i].getElementsByTagName("accountTypeDecl")[0].text,
															ovrdRules[i].getElementsByTagName("taxTypeDecl")[0].text,
															ovrdRules[i].getElementsByTagName("acctDesigDecl")[0].text,
															ovrdRules[i].getElementsByTagName("onlineEWI")[0].text,
															ovrdRules[i].getElementsByTagName("cycleEWI")[0].text,
															ovrdRules[i].getElementsByTagName("esgEWI")[0].text,
															ovrdRules[i].getElementsByTagName("fundLtOvrdRID")[0].text, 
															"");
					detailOvrdData.push(newData);
					
					//didnt use populateTable here to avoid a second loop
					var newRow = createDataRow(formatRuleType(newData.ruleType.toString(), newData.ruleTypeDesc), formatOverrideType(newData));
					tblObj.appendChild(newRow);
				}
				
				IFDSTableManager.reInitTable( "LtOvrdTable" );
				setTableSelectHandler();
			}
			else
			{
				alert("Getting Inquiry Data Failed\n\n" + responseXML.getElementsByTagName("text")[0].text);
			}
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: getting inquiry data error: " + e.description ); 		
		}
	}
	
	var paramMap = {}
	paramMap["cz"]                = _vCZ;
	paramMap["jobname"]           = "FundSetup_ClassMaint_LtOvrd_Inq";
	paramMap["envName"]           = _envName;
	paramMap["ruserId"]           = _ruserId;
	paramMap["bgcolor"]       	  = _vDesktopColor;
	paramMap["sessionId"]         = _sessionId;
	paramMap["dateFormat"]		  = _dateFormat;
	paramMap["fundCode"]		  = _fundCode;
	paramMap["classCode"]		  = _classCode;
	
	var url = HTTP.buildURL(_vServletPath, paramMap);

	var req = HTTP.getPOSTRequest(url);
	req.setCallbackFunction( getPostbackStatus );
	req.setAsynch(false);
	req.send(ruleType);
}

//******************************************************
function ddlChangeHandler_RuleTypeList(inCtrl)
{
	Desktop.disableScreen();
	
	clearScreenFields();
	ruleTypeInquiry();

	Desktop.undisableScreen();
}

//******************************************************
function ddlChangeHandler_EWIList(inCtrl)
{
	detailOvrdData[getSelectedRowIndex()][inCtrl.parentNode.id] = inCtrl.options[inCtrl.selectedIndex].value;
	detailOvrdData[getSelectedRowIndex()].runMode = (detailOvrdData[getSelectedRowIndex()].runMode == "A") ? "A" : "M";
	setUpdatesMade();
}

//******************************************************
function ddlChangeHandler_ieSelect()
{
	var selectedInfo = getSelectedInfo(UTL.getElem("ieSelect"));
	updateSelectedListTitle(selectedInfo.text);
	
	clearItemToMove();
	
	var listCtrl = (selectedInfo.value == "e") ? UTL.getElem("allList") : UTL.getElem("selList");
	
	for(var i = 0; i < listCtrl.childNodes.length; ++i)
	{
		if(listCtrl.childNodes[i].value == "*")
		{
			listSelect(listCtrl.childNodes[i], selectedInfo.value);
			moveItem();
			break;
		}
	}
}

//******************************************************
function clickHandler_canBtn()
{
	returnToMainScreen();
}

//******************************************************
function clickHandler_resBtn()
{
	reloadData();
}

//******************************************************
function clickHandler_okBtn()
{
	var xmlStr = buildUpdateInfo();		
	
	var updateStatus = sendUpdate(xmlStr);	
	
	if(updateStatus == true)
	{
		returnToMainScreen();
	}
	else
	{
		//stay on the page and notify user
		alert(updateStatus);
		return false;
	}	
}

//******************************************************
function clickHandler_popupSaveAddBtn()
{
	var selectedRuleType = getSelectedInfo(UTL.getElem("Popup_ruleTypeSelect"));
	var overrideDec = '0.00';
	var overrideLog = 'no';
	if (_RuleTypeMap[selectedRuleType.value] == 'overrideDec') {
		
		overrideDec = UTL.getElem("overrideDecFld").value;
	}
	else
	{
		overrideLog = 'yes'	
	}
	
	var newData = new fundLimitOverrideData(selectedRuleType.value.toString(),
											selectedRuleType.text,
											overrideDec,
											overrideLog,
											"*","*","*","*","*","E","E","E","","A");
	detailOvrdData.push(newData);
	
	appendTableRow(formatRuleType(newData.ruleType.toString(), newData.ruleTypeDesc), formatOverrideType(newData), detailOvrdData.length - 1);
	
	//enable edit buttons
	enableEditBtns();
	enableEWILists();
	
	setUpdatesMade();
	
	Desktop.hidePopup("ruleTypePopupDiv");	
}

//******************************************************
function clickHandler_popupCancelAddBtn()
{
	Desktop.hidePopup("ruleTypePopupDiv");
}

//******************************************************
function editField(inStrField)
{
	if(inStrField && inStrField != "")
	{
		var caption = "";
		var valueField = "";
		
		//populate data according to inStrField
		switch(inStrField)
		{
			case "TaxJurisList":
				caption = "Tax Jurisdiction";
				valueField = "taxJurisDecl";
				populateTaxJurisList();
				break;
			case "AcctTypeList":
				caption = "Account Type";
				valueField = "accountTypeDecl";
				populateAcctTypeList();
				break;
			case "AcctDesignationList":
				caption = "Account Designation";
				valueField = "acctDesigDecl";
				populateAcctDesignationList();
				break;
			case "TaxTypeList":
				caption = "Tax Type";
				valueField = "taxTypeDecl";
				populateTaxTypeList();
				break;
			case "ProvResList":
				caption = "Province of Residence";
				valueField = "provResDecl";
				populateProvResList();
			default:
				//alert user and return false;
				break;
		}
				
		UTL.getElem("whichPopup").value = valueField;
		
		Desktop.showPopup("appToPopupDiv", "Limitation Override Modify - " + caption);
	}
}

//******************************************************
function clickHandler_ruleBtns(inStrOp)
{
	switch (inStrOp)
	{
		case "add":
			Desktop.showPopup("ruleTypePopupDiv", "Limitation Override - Add");
			UTL.getElem('Popup_ruleTypeSelect').selectedIndex = 0;
			changeHandler_PopupRuleSelect(UTL.getElem('Popup_ruleTypeSelect'))			
			break;
		case "del":
			DeleteData(detailOvrdData[getSelectedRowIndex()]);
			ClassDataManager.deleteRecordInTable(UTL.getElem("LtOvrdTable"), getSelectedRowIndex());
			setUpdatesMade();
			break;
		default:
			break;
	}
	
	IFDSTableManager.getTable("LtOvrdTable").clearSelectedRowIndex();
	UTL.getElem("btnRuleDel").disabled = true;
	clearAppDiv();
	disableEditBtns();
	disableEWILists();
}

//******************************************************
function selectHandler_LtOvrdTable()
{
	UTL.getElem("btnRuleDel").disabled = false;
	enableEditBtns();
	enableEWILists();
	
	var dataObj = detailOvrdData[getSelectedRowIndex()];
	
	//populate data into AppTo div
	for (obj in dataObj)
	{
		var control = UTL.getElem(obj);
		
		if(control && control != null)
		{
			if(control.id.indexOf("EWI") > 2)
			{
				var allOptions = control.firstChild.options;
				for(var i = 0; i < allOptions.length; ++i)
				{
					if(allOptions[i].value == dataObj[obj])
					{
						allOptions[i].setAttribute("selected", "selected");
						break;
					}
				}
			}
			else
			{
				control.innerHTML = dataObj[obj].toString().replace( /,/g, ", " );
			}
		}
	}
}

//******************************************************
function updateSelectedListTitle(inTitle)
{
	UTL.getElem("listTitle").innerHTML = inTitle;
}

//******************************************************
function buildUpdateInfo()
{
	var rtnStr = "<FundLtOvrds>";
	for(var i = 0; i < detailOvrdData.length; ++i)
	{
		rtnStr += "<FundLtOvrd>";
		rtnStr += getDetailData(detailOvrdData[i]);
		rtnStr += "</FundLtOvrd>";
	}
	rtnStr += "</FundLtOvrds>";
	
	return rtnStr;
}

//******************************************************
function sendUpdate(inXMLStr)
{
	var rtnVal = false;
	
	function getUpdateStatus(responseText)
	{
		//alert(responseText);
		var responseXML = null;
		try 
		{
			responseXML = XML.parseToXML( responseText );
			
			if(responseXML.text == "S")
			{
				rtnVal = true;
			}
			else
			{
				rtnVal = "update Failed\n\n" + responseXML.text;
			}
		}
		catch( e )
		{
			rtnVal = "update error caught: " + e.description;
		}
	}
	
	var paramMap = {}
	paramMap["cz"]                = _vCZ;
	paramMap["jobname"]           = "FundSetup_ClassMaint_LtOvrd_Upd";
	paramMap["envName"]           = _envName;
	paramMap["ruserId"]           = _ruserId;
	paramMap["bgcolor"]       	  = _vDesktopColor;
	paramMap["sessionId"]         = _sessionId;
	paramMap["dateFormat"]		  = _dateFormat;
	paramMap["fundCode"]		  = _fundCode;
	paramMap["classCode"]		  = _classCode;
	
	var url = HTTP.buildURL(_vServletPath, paramMap);

	var req = HTTP.getPOSTRequest(url);
	req.setCallbackFunction( getUpdateStatus );
	req.setAsynch(false);
	req.send(inXMLStr);
	
	return rtnVal;
}

//******************************************************
function enableEditBtns()
{
	var btns = document.getElementsByName("fldEditBtn");
	for(var i = 0; i < btns.length; ++i)
	{
		btns[i].disabled = false;
	}
}

//******************************************************
function disableEditBtns()
{
	var btns = document.getElementsByName("fldEditBtn");
	for(var i = 0; i < btns.length; ++i)
	{
		btns[i].disabled = true;
	}
}

//******************************************************
function disableEWILists()
{
	var lists = document.getElementsByName("EWIList");
	for(var i = 0; i < lists.length; ++i)
	{
		lists[i].disabled = true;
	}
}

//******************************************************
function enableEWILists()
{
	var lists = document.getElementsByName("EWIList");
	for(var i = 0; i < lists.length; ++i)
	{
		lists[i].disabled = false;
	}
}

//******************************************************
function getDetailData(inData)
{
	var rtnStr = "";
	
	for (obj in inData)
	{
		rtnStr += "<" + obj + ">";
		rtnStr += inData[obj];
		rtnStr += "</" + obj + ">";
	}
	
	return rtnStr;
}

//******************************************************
function DeleteData(inData)
{
	if(inData.runMode == "A")
	{
		detailOvrdData = removeFromArray(detailOvrdData, inData);
	}
	else
	{
		inData.runMode = "D";
	}
}

//******************************************************
function clickHandler_popupCancelBtn()
{
	Desktop.hidePopup('appToPopupDiv');
}

//******************************************************
function clickHandler_popupSaveBtn()
{
	var dataObj = detailOvrdData[getSelectedRowIndex()];
	
	var listItems = UTL.getElem("selList").childNodes;
	var isInclude = (getSelectedInfo(UTL.getElem("ieSelect")).value == "i") ? true : false;
	var updatedValue = "";
	
	for(var i = 0; i < listItems.length; ++i)
	{
		if(isInclude)
		{
			updatedValue += "," + listItems[i].value.toString();
		}
		else
		{
			if(listItems[i].value == "*")
			{
				updatedValue += "," + listItems[i].value.toString();
			}
			else
			{
				updatedValue += ",!" + listItems[i].value.toString();
			}
		}
	}
	
	updatedValue = updatedValue.substring(1);
	
	//update detailOvrdData array
	dataObj[UTL.getElem("whichPopup").value] = updatedValue;
	if(dataObj.runMode != "A")
	{
		dataObj.runMode = "M";
	}
	
	//updateUI
	UTL.getElem(UTL.getElem("whichPopup").value).innerHTML = updatedValue;
	
	setUpdatesMade();
	Desktop.hidePopup('appToPopupDiv');
}

//******************************************************
function listSelect(inObj, mode)
{
	if(curDirection != mode)
	{
		UTL.getElem("iMoveBtn").disabled = true;
		UTL.getElem("eMoveBtn").disabled = true;
		
		clearItemToMove();
		
		curDirection = mode;
	}
	
	if(inObj.className == "listNormal")
	{
		inObj.className = "listSelected";
		itemToMove.push(inObj);
		UTL.getElem(mode + "MoveBtn").disabled = false;
	}
	else
	{
		inObj.className = "listNormal";
		itemToMove = removeFromArray(itemToMove, inObj);
		if(itemToMove.length == 0)
		{
			UTL.getElem("iMoveBtn").disabled = true;
			UTL.getElem("eMoveBtn").disabled = true;
		}
	}
}

//******************************************************
function clearItemToMove()
{
	while(itemToMove.length > 0)
	{
		var obj = itemToMove.pop();
		obj.className = "listNormal";
	}
}

//******************************************************
function removeFromArray(inArray, inObj)
{
	var rtnArray = new Array();
	var itemCount = inArray.length;
	for(var i = 0; i < itemCount; ++i)
	{
		if(inArray[i] != inObj)
		{
			rtnArray.push(inArray[i]);
		}
	}
	return rtnArray;
}

//******************************************************
function moveItem()
{
	var sourceDiv;
	var destDiv;
	
	if(curDirection == "e")
	{
		sourceDiv = UTL.getElem("allList");
		destDiv = UTL.getElem("selList");
	}
	else
	{
		sourceDiv = UTL.getElem("selList");
		destDiv = UTL.getElem("allList");
	}
	
	var newDir = (curDirection == "e") ? "i" : "e";
	
	if(sourceDiv != null && destDiv != null)
	{
		for(var i = 0; i < itemToMove.length; ++i)
		{
			destDiv.appendChild(itemToMove[i]);
			
			itemToMove[i].setAttribute("onclick", function(){listSelect(this,newDir);});
		}
		
		clearItemToMove();
		
		UTL.getElem("iMoveBtn").disabled = true;
		UTL.getElem("eMoveBtn").disabled = true;
	}
}

//******************************************************
function isExclude(inArray)
{
	var rtnVal = false;
	var iterCount = (inArray.length < 2) ? inArray.length : 2;
	
	for(var i = 0; i < iterCount; ++i)
	{
		if(inArray[i].charAt(0) == "!")
		{
			rtnVal = true;
			break;
		}
	}
	
	return rtnVal;
}

//******************************************************
function dataMassage(inArray)
{
	var rtnArray = inArray;
	
	for(var i = 0; i < rtnArray.length; ++i)
	{
		if(rtnArray[i].charAt(0) == "!")
		{
			rtnArray[i] = rtnArray[i].substring(1);
		}
	}
	
	return rtnArray;
}

//******************************************************
//may need validation check on inInt
function setIEselect(inInt)
{
	UTL.getElem("ieSelect").selectedIndex = inInt;
	UTL.getElem("listTitle").innerHTML = (inInt == 0) ? "Include" : "Exclude";
}

function clone(inObj)
{
	var rtnVal = {};
	
	for (var obj in inObj)
	{
		rtnVal[obj] = inObj[obj];
	}
	
	return rtnVal;
}

//******************************************************
function buildLists(inListMap, inSelectedArray)
{
	var rtnVal = {};
	
	var list = new clone(inListMap);	//make sure pass by value, not reference
	var selected = {};

	for(var i = 0; i < inSelectedArray.length; ++i)
	{
		selected[inSelectedArray[i]] = list[inSelectedArray[i]];
		delete list[inSelectedArray[i]];
	}
	
	rtnVal.list = list;
	rtnVal.selected = selected;
	
	return rtnVal;
}

//******************************************************
function populateTaxJurisList()
{
	var selectArray = detailOvrdData[getSelectedRowIndex()].taxJurisDecl.split(",");
	
	if(isExclude(selectArray))
	{
		selectArray = dataMassage(selectArray);
		setIEselect(1);
	}
	else
	{
		setIEselect(0);
	}
	
	var lists = buildLists(_TaxJurisList, selectArray);
	
	populateList(UTL.getElem("allList"), lists.list, "e");
	populateList(UTL.getElem("selList"), lists.selected, "i");
}

//******************************************************
function populateAcctTypeList()
{
	var selectArray = detailOvrdData[getSelectedRowIndex()].accountTypeDecl.split(",");
	
	if(isExclude(selectArray))
	{
		selectArray = dataMassage(selectArray);
		setIEselect(1);
	}
	else
	{
		setIEselect(0);
	}
	
	var lists = buildLists(_AcctTypeList, selectArray);
	
	populateList(UTL.getElem("allList"), lists.list, "e");
	populateList(UTL.getElem("selList"), lists.selected, "i");
}

//******************************************************
function populateAcctDesignationList()
{
	var selectArray = detailOvrdData[getSelectedRowIndex()].acctDesigDecl.split(",");
	
	if(isExclude(selectArray))
	{
		selectArray = dataMassage(selectArray);
		setIEselect(1);
	}
	else
	{
		setIEselect(0);
	}
	
	var lists = buildLists(_AcctDesignationList, selectArray);
	
	populateList(UTL.getElem("allList"), lists.list, "e");
	populateList(UTL.getElem("selList"), lists.selected, "i");
}

//******************************************************
function populateTaxTypeList()
{
	var selectArray = detailOvrdData[getSelectedRowIndex()].taxTypeDecl.split(",");
	
	if(isExclude(selectArray))
	{
		selectArray = dataMassage(selectArray);
		setIEselect(1);
	}
	else
	{
		setIEselect(0);
	}
	
	var lists = buildLists(_TaxTypeList, selectArray);
	
	populateList(UTL.getElem("allList"), lists.list, "e");
	populateList(UTL.getElem("selList"), lists.selected, "i");
}

//******************************************************
function populateProvResList()
{
	var selectArray = detailOvrdData[getSelectedRowIndex()].provResDecl.split(",");
	
	if(isExclude(selectArray))
	{
		selectArray = dataMassage(selectArray);
		setIEselect(1);
	}
	else
	{
		setIEselect(0);
	}
	
	var lists = buildLists(_ProvResList, selectArray);
	
	populateList(UTL.getElem("allList"), lists.list, "e");
	populateList(UTL.getElem("selList"), lists.selected, "i");
}

//******************************************************
function populateList(inDiv, inMap, inDirection)
{
	while(inDiv.childNodes.length > 0)
	{
		inDiv.removeChild(inDiv.firstChild);
	}
	
	for (var obj in inMap)
	{
		var listItem = createListItem(obj, inMap[obj], inDirection);
		inDiv.appendChild(listItem);
	}
}

//******************************************************
function createListItem(inValue, inText, inDirection)
{
	var textContent = (inText == "") ? inValue : inText;
	
	var listItem = document.createElement("span");
	
	listItem.className = "listNormal";
	listItem.setAttribute("onclick", function(){listSelect(this, inDirection);});
	listItem.setAttribute("value", inValue);
	if (textContent != '*') {
		listItem.innerHTML = inValue + ' - ' + textContent;
	}
	else {
		listItem.innerHTML = textContent;
	}
	
	return listItem;
}

//******************************************************
function clearScreenFields()
{
	clearTable();
	clearAppDiv();
	disableEditBtns();
	disableEWILists();
	resetEWILists();
	UTL.getElem("btnRuleDel").disabled = true;
	
	while(detailOvrdData.length > 0)
	{
		detailOvrdData.pop();
	}
}

//******************************************************
function clearTable()
{
	var tblObj = getDataTable();
	
	while(tblObj.childNodes.length > 0)
	{
		tblObj.removeChild(tblObj.firstChild);
	}
	
	IFDSTableManager.reInitTable( "LtOvrdTable" );
}

//******************************************************
function clearAppDiv()
{
	UTL.getElem("taxJurisDecl").innerHTML = "";
	UTL.getElem("taxTypeDecl").innerHTML = "";
	UTL.getElem("accountTypeDecl").innerHTML = "";
	UTL.getElem("acctDesigDecl").innerHTML = "";
	UTL.getElem("provResDecl").innerHTML = "";
	
}

//******************************************************
function setUpdatesMade()
{
	_updatesMade = true;
	UTL.getElem( "submitBtn" ).disabled = false;
	UTL.getElem( "resetBtn" ).disabled = false;
}

//******************************************************
function returnToMainScreen()
{													
	var paramMap = {}
	paramMap["cz"]     			 = _vCZ;
	paramMap["jobname"]       = "FundSetup_ClassMaint_Main";    
	paramMap["companyCode"]   = _companyCode;
	paramMap["ruserId"]       = _ruserId;
	paramMap["sessionId"]     = _sessionId;
	paramMap["envName"]       = _envName;
	paramMap["dateFormat"]    = _dateFormat;
	paramMap["bgcolor"]       = _vDesktopColor;		  
	paramMap["fundCode"]  	  = _fundCode; 

	var url = HTTP.buildURL( _vServletPath, paramMap );
	window.location = url; 
}

//******************************************************
function changeHandler_PopupRuleSelect(fld)
{	
	if ( _RuleTypeMap[fld.value] == 'overrideDec' )
	{
		UTL.getElem("overrideDecFld").value = "";
		UTL.getElem("overrideDecFld").style.display = "block";		
		UTL.getElem("overrideLogFld").style.display = "none";
	}
	else
	{
		UTL.getElem("overrideDecFld").value = "";
		UTL.getElem("overrideDecFld").style.display = "none";		
		UTL.getElem("overrideLogFld").style.display = "block";
	}
}