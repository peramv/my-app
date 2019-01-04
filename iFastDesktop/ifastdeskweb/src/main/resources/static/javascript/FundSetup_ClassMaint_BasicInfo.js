var _shareGroupPopupFlags = null;
var _fundIdentifierPopupFlags = null;

var _ADD = 'add';
var _MOD = 'mod';


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
	
	IFDSTableManager.init();	
	IFDSTableManager.getTable( "FundIdentifiers_Table" ).setOnRowSelectedFunction( selectHandler_FundIdentifiersTable );
	IFDSTableManager.getTable( "ShareGroups_Table" ).setOnRowSelectedFunction( selectHandler_ShareGroupsTable );
	
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );	
		
	ClassDataManager.initScreen( "ClassBasic", "BasicInfo" );
	
	initFundClassFields();
	initSubCatCheckboxes();	
	
	_shareGroupPopupFlags = {};
	_fundIdentifierPopupFlags = {};
}


//******************************************************
function initFundClassFields()
{
	UTL.getElem( "fundCodeFld" ).value = ClassDataManager.getCurrentData( "fundCode" );
	UTL.getElem( "classCodeFld" ).value = ( ClassDataManager.getCurrentData( "classCode" ) != null ? ClassDataManager.getCurrentData( "classCode" ) : "" ); 
	
	if ( ClassDataManager.getOrigData( "classCode" ) != null )
	{		
		UTL.getElem( "classCodeFld" ).disabled = true;
		UTL.getElem( "loadTypeFld" ).disabled = true;
	}
	else
	{
		UTL.getElem( "classCodeFld" ).disabled = false;
		UTL.getElem( "loadTypeFld" ).disabled = false;
	}
	
}

//******************************************************
function changeHandler_classCodeFld()
{
	UTL.getElem( "hiddenClassCodeFld" ).value = UTL.getElem( "classCodeFld" ).value;
	ClassDataManager.setScreenUpdated();
}


// SUB CATEGORY

//******************************************************
function clickHandler_subCatCheckbox( checkbox )
{
	var subCat = checkbox.subCat;
	updateSubCategoryTable( subCat, ( checkbox.checked ? 'yes' : 'no' ) );	
}

//******************************************************
function initSubCatCheckboxes()
{
	var subCatTable = UTL.getElem( "SubCategories_Table" );	
	
	var subCatRecords = subCatTable.lastChild.childNodes;	
	for ( var i = 0; i < subCatRecords.length; i++ )
	{
		var subCatRecord = subCatRecords[i];
		UTL.getElem( "subCat" + subCatRecord.subCat + "Cbox" ).checked = ( subCatRecord.subCatFlag == 'yes' ? true :  false );				
	}
}

//******************************************************
function updateSubCategoryTable( subCat, value )
{	
	var subCatTable = UTL.getElem( "SubCategories_Table" );	
	
	var subCatRecords = subCatTable.lastChild.childNodes;
		
	for ( var i = 0; i < subCatRecords.length; i++ )
	{
		var subCatRecord = subCatRecords[i];
		if ( subCatRecord.subCat == subCat )
		{
			subCatRecord.status = "mod";					
			subCatRecord.subCatFlag = value;
			break;
		}		
	}
	
	ClassDataManager.setScreenUpdated();
}



// FUND IDENTIFIER
//****************************************************
function selectHandler_FundIdentifiersTable()
{
	UTL.getElem( "FundIdentifierModBtn" ).disabled = false;
	UTL.getElem( "FundIdentifierDelBtn" ).disabled = false;
}

//****************************************************
function clickHandler_addFundIdentifierBtn()
{		
	openFundIdentifierPopup( _ADD );	
}

//******************************************************
function clickHandler_modFundIdentifierBtn()
{
	openFundIdentifierPopup( _MOD );
}

//******************************************************
function clickHandler_delFundIdentifierBtn()
{
	deleteFundIdentifier();
}

//******************************************************
function openFundIdentifierPopup( mode )
{	
	var caption = "Fund Identifier";
	switch ( mode )
	{
		case _ADD:
		{
			clearFundIdentifierTableSelection();
			
			caption += " - Add";
			break;
		}
		case _MOD:
		{
			caption += " - Modify";
			populateFundIdentifierPopup( IFDSTableManager.getTable( "FundIdentifiers_Table" ).getSelectedRowIndex() );
			break;
		}	
		default:
		{
			alert( "FUNCTION ERROR - unknown popup mode" );
		}
	}
	
	Desktop.showPopup( "fundIdentifierPopupDiv", caption );
	UTL.getElem( "fundIdentifierPopupDiv" ).mode = mode;
}

//******************************************************
function deleteFundIdentifier()
{
	var tableRef = UTL.getElem( "FundIdentifiers_Table" )
	var rowIndex = IFDSTableManager.getTable( tableRef.id ).getSelectedRowIndex();
	tableRef.lastChild.childNodes[rowIndex].runMode = "D"; 
	ClassDataManager.deleteRecordInTable( tableRef, rowIndex );
	
	clearFundIdentifierTableSelection();	
	ClassDataManager.setScreenUpdated();		
}

//******************************************************
function clearFundIdentifierPopup()
{
	for ( var i in _fundIdentifierPopupFlags )
	{
		_fundIdentifierPopupFlags[i].hide();
	}
	
	UTL.getElem( "fundIdentPopup_idTypeFld" ).value = "";
	UTL.getElem( "fundIdentPopup_idValueFld" ).value = ""; 
}

//******************************************************
function clearFundIdentifierTableSelection()
{
	IFDSTableManager.getTable( "FundIdentifiers_Table" ).clearSelectedRowIndex();
	UTL.getElem( "FundIdentifierModBtn" ).disabled = true;
	UTL.getElem( "FundIdentifierDelBtn" ).disabled = true;
}

//******************************************************
function populateFundIdentifierPopup( rowIndex )
{
	var table = UTL.getElem( "FundIdentifiers_Table" );
	var row = table.lastChild.childNodes[rowIndex];
	
	UTL.getElem( "fundIdentPopup_idTypeFld" ).value = row.idType;
	UTL.getElem( "fundIdentPopup_idValueFld" ).value = row.idValue; 
}

//******************************************************
function clickHandler_fundIdentifierPopupOKBtn()
{
	if ( updateFundIdentifierTable( UTL.getElem( "fundIdentifierPopupDiv" ).mode ) )
	{
		clearFundIdentifierPopup();
		Desktop.hidePopup( "fundIdentifierPopupDiv" );		
	}		
}

//******************************************************
function clickHandler_fundIdentifierPopupCancelBtn()
{
	clearFundIdentifierPopup();
	Desktop.hidePopup( "fundIdentifierPopupDiv" );	
}

//******************************************************
function updateFundIdentifierTable( action )
{	
	var success = true;
	
	var idTypeFld = UTL.getElem( "fundIdentPopup_idTypeFld" );
	var idValueFld = UTL.getElem( "fundIdentPopup_idValueFld" );
		
	if ( validateFundIdentifierPopup() )
	{
		var idRecord = {};
		idRecord["idType"] = idTypeFld.value;
		idRecord["idTypeDesc"] = idTypeFld.options[idTypeFld.selectedIndex].text;
		idRecord["idValue"] = idValueFld.value;
		idRecord["fundIDVer"] = UTL.getElem( "fundIdentPopup_fundIDVerFld" ).value;	
		idRecord["fundIDUUID"] = UTL.getElem( "fundIdentPopup_fundIDUUIDFld" ).value;
	}
	else
	{
		success = false;
	}
	
	if ( success )
	{
		switch( action )
		{
			case _ADD:
			{
				idRecord["runMode"] = "A";
				ClassDataManager.addRecordToTable( UTL.getElem( "FundIdentifiers_Table" ), idRecord );
				IFDSTableManager.reInitTable( "FundIdentifiers_Table" );		
				break;
			}
			case _MOD:
			{
				idRecord["runMode"] = "M";
				ClassDataManager.modifyRecordInTable( UTL.getElem( "FundIdentifiers_Table" ), IFDSTableManager.getTable( "FundIdentifiers_Table" ).getSelectedRowIndex(), idRecord );
				break;
			}			
		}		
		ClassDataManager.setScreenUpdated();
	}
	return success;
}

function validateFundIdentifierPopup()
{	
	var errorsFound = false;
	if( UTL.getElem( "fundIdentPopup_idTypeFld" ).value == "" )
	{
		Desktop.paintFieldErrorFlag( _fundIdentifierPopupFlags, "fundIdentPopup_idTypeFld", "Missing mandatory field" );
		errorsFound = true;
	}
	
	return !errorsFound; 
}


// SHARE GROUP
//****************************************************
function selectHandler_ShareGroupsTable()
{
	UTL.getElem( "ShareGroupModBtn" ).disabled = false;
	UTL.getElem( "ShareGroupDelBtn" ).disabled = false;
}

//****************************************************
function clickHandler_addShareGroupBtn()
{
	openShareGroupPopup( _ADD );
}

//******************************************************
function clickHandler_modShareGroupBtn()
{
	openShareGroupPopup( _MOD );
}

//******************************************************
function clickHandler_delShareGroupBtn()
{
	deleteShareGroup();
}

//******************************************************
function clearShareGroupTableSelection()
{
	IFDSTableManager.getTable( "ShareGroups_Table" ).clearSelectedRowIndex();
	UTL.getElem( "ShareGroupModBtn" ).disabled = true;
	UTL.getElem( "ShareGroupDelBtn" ).disabled = true;	
}

//******************************************************
function openShareGroupPopup( mode )
{	
	var caption = "Share Group";
	switch ( mode )
	{
		case _ADD:
		{
			clearShareGroupTableSelection();
			
			caption += " - Add";
			break;
		}
		case _MOD:
		{
			caption += " - Modify";
			populateShareGroupPopup( IFDSTableManager.getTable( "ShareGroups_Table").getSelectedRowIndex() );
			break;
		}	
		default:
		{
			alert( "FUNCTION ERROR - unknown popup mode" );
		}
	}
	
	Desktop.showPopup( "ShareGroupPopupDiv", caption );
	UTL.getElem( "ShareGroupPopupDiv" ).mode = mode;
}

//******************************************************
function deleteShareGroup()
{
	var tableRef = IFDSTableManager.getTable( "ShareGroups_Table" );
	tableRef.lastChild.childNodes[tableRef.getSelectedRowIndex()].runMode = "D"; 
	ClassDataManager.deleteRecordInTable( UTL.getElem( "ShareGroups_Table" ), tableRef.getSelectedRowIndex() );	
	
	clearShareGroupTableSelection();
	ClassDataManager.setScreenUpdated();		
}

//******************************************************
function clearShareGroupPopup()
{
	for ( var i in _shareGroupPopupFlags )
	{
		_shareGroupPopupFlags[i].hide();
	}
	
	UTL.getElem( "shareGroupPopup_groupFld" ).value = ""; 
	UTL.getElem( "shareGroupPopup_deffFld" ).value = "";
	UTL.getElem( "shareGroupPopup_activeFld" ).checked = false;
}

//******************************************************
function populateShareGroupPopup( rowIndex )
{
	var table = UTL.getElem( "ShareGroups_Table" );
	var row = table.lastChild.childNodes[rowIndex];
	
	UTL.getElem( "shareGroupPopup_groupFld" ).value = row.shGroup;	
	UTL.getElem( "shareGroupPopup_deffFld" ).value = row.deff;
	UTL.getElem( "shareGroupPopup_activeFld" ).checked = ( row.active == "yes" ? true : false );
}


//******************************************************
function clickHandler_shareGroupPopupOKBtn()
{
	if ( updateShareGroupTable( UTL.getElem( "ShareGroupPopupDiv" ).mode ) )
	{
		clearShareGroupPopup();
		Desktop.hidePopup( "ShareGroupPopupDiv" );		
	}	
}

//******************************************************
function clickHandler_shareGroupPopupCancelBtn()
{	
	clearShareGroupPopup();
	Desktop.hidePopup( "ShareGroupPopupDiv" );	
}

//******************************************************
function updateShareGroupTable( action )
{	
	var success = true;
		
	var groupFld = UTL.getElem( "shareGroupPopup_groupFld" ); 
	var deffFld = UTL.getElem( "shareGroupPopup_deffFld" );
	var activeFld = UTL.getElem( "shareGroupPopup_activeFld" );
		
	if ( validateShareGroupPopup()  )
	{
		var shGroupRecord = {};		
		shGroupRecord["shGroup"] = groupFld.value;
		shGroupRecord["groupName"] = groupFld.options[groupFld.selectedIndex].text;
		shGroupRecord["deff"] = deffFld.value;
		shGroupRecord["active"] = ( activeFld.checked ? "yes" : "no" ); 			
	}
	else
	{
		success = false;
	}
	
	if ( success )
	{
		switch( action )
		{
			case _ADD:
			{
				shGroupRecord["runMode"] = "A";
				ClassDataManager.addRecordToTable( UTL.getElem( "ShareGroups_Table" ),
												shGroupRecord );
				IFDSTableManager.reInitTable( "ShareGroups_Table" );		
				break;
			}
			case _MOD:
			{
				shGroupRecord["runMode"] = "M";
				ClassDataManager.modifyRecordInTable( UTL.getElem( "ShareGroups_Table" ), 
												IFDSTableManager.getTable( "ShareGroups_Table" ).getSelectedRowIndex(), shGroupRecord );
				break;
			}			
		}	
		ClassDataManager.setScreenUpdated();
	}
	return success;
}

//******************************************************
function validateShareGroupPopup()
{
	var errorsFound = false;
	if( UTL.getElem( "shareGroupPopup_groupFld" ).value == "" )
	{
		Desktop.paintFieldErrorFlag( _shareGroupPopupFlags, "shareGroupPopup_groupFld", "Missing mandatory field" );
		errorsFound = true;
	}
	
	return !errorsFound;
}

//******************************************************
function clickHandler_resetScreenBtn()
{
	if ( confirmReset() )
	{
		ClassDataManager.resetScreen();
		initSubCatCheckboxes();
	}
}