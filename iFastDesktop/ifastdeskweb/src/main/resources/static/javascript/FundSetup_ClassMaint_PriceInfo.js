var _fundListsMap = null;

//******************************************************
function loading()
{
	if ( UTL.getElem( "ClassData" ) )
	{			
		ClassDataManager.init( XML.parseToXML( UTL.getElem( "ClassData" ).xml ) );
	}
	
	if ( UTL.getElem( "UpdatedClassData" ) )
	{		
		ClassDataManager.loadExistingUpdates( XML.parseToXML(  UTL.getElem( "UpdatedClassData" ).xml ) );
	}
		
	ClassDataManager.initScreen( "PriceInfo", "PriceInfo" );	
}

//******************************************************
function clickHandler_editSettleCurrencyBtn()
{
	openSettleCurrencyPopup();	
}

//******************************************************
function openSettleCurrencyPopup()
{		
	populateSettleCurrencyPopup();
	Desktop.showPopup( "settleCurrencyPopupDiv", "Edit Valid Settle Currency List" );	
}

//******************************************************
function populateSettleCurrencyPopup()
{	
	var currListArray = UTL.getElem( "validSettleCurrFld" ).value.split( "," );
	var currListMap = {};
	for ( var i = 0; i < currListArray.length; i++ )
	{
		currListMap[currListArray[i]] = true;
	}
	
	var currCheckboxArray = UTL.getElem( "currencyCheckbox", UTL.GET_ELEM_SEARCH_TYPE_NAME );
	for ( var i = 0; i < currCheckboxArray.length; i++ )
	{
		var checkbox = currCheckboxArray[i];
		var curr = checkbox.value;
		if ( currListMap[curr] != null )
		{
			checkbox.checked = true;	
		}
		
		if ( currListMap["*"] != null && checkbox.value != "*")
		{
			checkbox.disabled = true;
		}		
	}
}

//******************************************************
function clickHandler_allCurrCheckbox( allCurrCheckbox )
{
	var allCurrSelected = allCurrCheckbox.checked;
	
	var currCheckboxArray = UTL.getElem( "currencyCheckbox", UTL.GET_ELEM_SEARCH_TYPE_NAME );
	for ( var i = 0; i < currCheckboxArray.length; i++ )
	{
		if ( allCurrSelected && currCheckboxArray[i] != allCurrCheckbox )
		{
			currCheckboxArray[i].disabled = true;
			currCheckboxArray[i].checked = false;
		}		
		else
		{
			currCheckboxArray[i].disabled = false;
		}
	}
}

//******************************************************
function saveSettleCurrencyChanges()
{
	var currStr = "";
	var currCheckboxArray = UTL.getElem( "currencyCheckbox", UTL.GET_ELEM_SEARCH_TYPE_NAME );
	for ( var i = 0; i < currCheckboxArray.length; i++ )
	{
		var checkbox = currCheckboxArray[i];
		if ( checkbox.checked )
		{
			currStr += ( currStr.length > 0 ? "," : "" ) + checkbox.value;	
		}	
	}
	 
	if ( UTL.getElem( "validSettleCurrFld" ).value != currStr )
	{
		UTL.getElem( "validSettleCurrFld" ).value = currStr;
		ClassDataManager.setScreenUpdated();
	}	
	
	Desktop.hidePopup( "settleCurrencyPopupDiv" );
}

//******************************************************
function clickHandler_settleCurrencyPopupCancelBtn()
{
	Desktop.hidePopup( "settleCurrencyPopupDiv" );
}

//******************************************************
function clickHandler_settleCurrencyPopupOKBtn()
{
	saveSettleCurrencyChanges();
	Desktop.hidePopup( "settleCurrencyPopupDiv" );
}

//******************************************************
function clickHandler_resetScreenBtn()
{
	if ( confirmReset() )
	{
		ClassDataManager.resetScreen();		
	}
}
