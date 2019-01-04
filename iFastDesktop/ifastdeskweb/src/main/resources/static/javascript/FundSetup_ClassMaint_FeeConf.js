var _ADD = 'add';
var _MOD = 'mod';

var _feeScalePopupErrorMap = null;
var _errorMap = null;

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
	IFDSTableManager.getTable( "FeeScales_Table" ).setOnRowSelectedFunction( selectHandler_FeeScalesTable );
	
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );
	
	ClassDataManager.initScreen( "FeeConfiguration", "FeeConf" );
	
	
	if (UTL.getElem('BackEndLoadDiv'))
	{		
		var belFeeTypeFld = UTL.getElem('belFeeTypeFld');
		var belBasedOnFld = UTL.getElem('belBasedOnFld');
		
		if (belFeeTypeFld.value == "")
		{
			belFeeTypeFld.value = 2;
		}
		
		if (belBasedOnFld.value == "")
		{
			belBasedOnFld.value = 4;
		}	
	}
	
	_feeScalePopupErrorMap = {};	
	_errorMap = {};
}


// FEE DETAIL SCALE

//******************************************************
function clickHandler_addFeeDetailScaleBtn()
{
	openFeeDetailScalePopup( _ADD )
}

//******************************************************
function clickHandler_modFeeDetailScaleBtn()
{
	openFeeDetailScalePopup( _MOD )
}

//******************************************************
function clickHandler_delFeeDetailScaleBtn()
{
	deleteFeeScale();
}

//******************************************************
function openFeeDetailScalePopup( mode )
{	
	var caption = "Fund Detail Scale";
	switch ( mode )
	{
		case _ADD:
		{
			clearFeeScaleTableSelection();
			
			caption += " - Add";
			break;
		}
		case _MOD:
		{
			caption += " - Modify";
			populateFeeScalePopup( IFDSTableManager.getTable( "FeeScales_Table" ).getSelectedRowIndex() );
			break;
		}		
		default:
		{
			alert( "FUNCTION ERROR - unknown popup mode" );
		}
	}
	
	Desktop.showPopup( "feeScalePopupDiv", caption );
	UTL.getElem( "feeScalePopupDiv" ).mode = mode; 
}

//******************************************************
function deleteFeeScale()
{
	var tableRef = IFDSTableManager.getTable( "FeeScales_Table" ); 
	ClassDataManager.deleteRecordInTable( UTL.getElem( "FeeScales_Table" ), tableRef.getSelectedRowIndex() );
	
	clearFeeScaleTableSelection();		
	ClassDataManager.setScreenUpdated();		
}

//******************************************************
function clearFeeScaleTableSelection()
{
	IFDSTableManager.getTable( "FeeScales_Table" ).clearSelectedRowIndex();
	UTL.getElem( "FeeScaleModBtn" ).disabled = true;
	UTL.getElem( "FeeScaleDelBtn" ).disabled = true;	
}

//******************************************************
function clearFeeScalePopup()
{
	UTL.getElem( "feeScalePopup_feeCodeFld" ).value = "";
	UTL.getElem( "feeScalePopup_levelFld" ).value = "";
	UTL.getElem( "feeScalePopup_UUIDFld" ).value = "";
	UTL.getElem( "feeScalePopup_lowerFld" ).value = "";
	UTL.getElem( "feeScalePopup_upperFld" ).value = "";	
	UTL.getElem( "feeScalePopup_rateFld" ).value = "";
	UTL.getElem( "feeScalePopup_deffFld" ).value = "";
	
	for ( var i in _feeScalePopupErrorMap )
	{
		_feeScalePopupErrorMap[i].hide();
	}	 
}

//******************************************************
function populateFeeScalePopup( rowIndex )
{
	var table = UTL.getElem( "FeeScales_Table" );
	var row = table.lastChild.childNodes[rowIndex];
	
	UTL.getElem( "feeScalePopup_feeCodeFld" ).value = row.feeCode;
	UTL.getElem( "feeScalePopup_levelFld" ).value = row.level;
	UTL.getElem( "feeScalePopup_UUIDFld" ).value = row.scaleUUID;
	UTL.getElem( "feeScalePopup_lowerFld" ).value = row.lower;
	UTL.getElem( "feeScalePopup_upperFld" ).value = row.upper;	
	UTL.getElem( "feeScalePopup_rateFld" ).value = row.rate;
	UTL.getElem( "feeScalePopup_deffFld" ).value = row.deff;	 	 
}

//******************************************************
function clickHandler_feeScalePopupOKBtn()
{
	if ( updateFeeScaleTable( UTL.getElem( "feeScalePopupDiv" ).mode ) )
	{
		clearFeeScalePopup();
		Desktop.hidePopup( "feeScalePopupDiv" );		
	}	
}

//******************************************************
function clickHandler_feeScalePopupCancelBtn()
{
	clearFeeScalePopup();
	Desktop.hidePopup( "feeScalePopupDiv" );	
}

//******************************************************
function updateFeeScaleTable( action )
{	
	var success = true;
	
	var feeCodeFld = UTL.getElem( "feeScalePopup_feeCodeFld" );
	var levelFld = UTL.getElem( "feeScalePopup_levelFld" );
	var UUIDFld = UTL.getElem( "feeScalePopup_UUIDFld" );
	var lowerFld = UTL.getElem( "feeScalePopup_lowerFld" );
	var upperFld = UTL.getElem( "feeScalePopup_upperFld" );	
	var rateFld = UTL.getElem( "feeScalePopup_rateFld" );
	var deffFld = UTL.getElem( "feeScalePopup_deffFld" );
	
	if ( feeCodeFld.value && levelFld.value
		&& lowerFld.value && upperFld.value 		
		&& rateFld.value && deffFld.value )
	{
		var feeScaleRecord = {};
		feeScaleRecord['feeCodeDesc'] = feeCodeFld.options[feeCodeFld.selectedIndex].text;
		feeScaleRecord['feeCode'] = feeCodeFld.value;		
		feeScaleRecord['level'] = levelFld.value;
		feeScaleRecord['lower'] = lowerFld.value;
		feeScaleRecord['upper'] = upperFld.value;	
		feeScaleRecord['rate'] = rateFld.value;
		feeScaleRecord['deff'] = deffFld.value;	
		feeScaleRecord['scaleUUID'] = UUIDFld.value;
		feeScaleRecord['runMode'] = ( action == _ADD? "A" : "M" );
	}
	else
	{
		success = false;
		if( !feeCodeFld.value )
		{
			Desktop.paintFieldErrorFlag( _feeScalePopupErrorMap, feeCodeFld.id, "Required field" );
		}
		if( !levelFld.value )
		{
			Desktop.paintFieldErrorFlag( _feeScalePopupErrorMap, levelFld.id, "Required field" );
		}
		if( !lowerFld.value )
		{
			Desktop.paintFieldErrorFlag( _feeScalePopupErrorMap, lowerFld.id, "Required field" );
		}
		if( !upperFld.value )
		{
			Desktop.paintFieldErrorFlag( _feeScalePopupErrorMap, upperFld.id, "Required field" );
		}
		if( !rateFld.value )
		{
			Desktop.paintFieldErrorFlag( _feeScalePopupErrorMap, rateFld.id, "Required field" );
		}
		if( !deffFld.value )
		{
			Desktop.paintFieldErrorFlag( _feeScalePopupErrorMap, deffFld.id, "Required field" );
		}
	}
	
	if ( success )
	{
		switch( action )
		{
			case _ADD:
			{
				ClassDataManager.addRecordToTable( UTL.getElem( "FeeScales_Table" ), feeScaleRecord );
				IFDSTableManager.reInitTable( "FeeScales_Table" );		
				break;
			}
			case _MOD:
			{
				ClassDataManager.modifyRecordInTable( UTL.getElem( "FeeScales_Table" ), IFDSTableManager.getTable( "FeeScales_Table" ).getSelectedRowIndex(), feeScaleRecord );
				break;
			}			
		}		
		if ( _errorMap['FeeScales_TableDiv'] != null )
		{			
			_errorMap['FeeScales_TableDiv'].hide();
		}
		ClassDataManager.setScreenUpdated();		
	}
	return success;
}

//******************************************************
function selectHandler_FeeScalesTable()
{
	UTL.getElem( "FeeScaleModBtn" ).disabled = false;
	UTL.getElem( "FeeScaleDelBtn" ).disabled = false;
}

//******************************************************
function clickHandler_reviewChangesBtn()
{
	ClassDataManager.saveChangesAndViewSummary();
}

//******************************************************
function clickHandler_resetScreenBtn()
{
	if ( confirmReset() )
	{
		ClassDataManager.resetScreen();
	}	
}

//******************************************************
function changeHandler_feeScaleDeffFld()
{	
	if ( _feeScalePopupErrorMap["feeScalePopup_deffFld"] )
	{
		setTimeout( "_feeScalePopupErrorMap[\"feeScalePopup_deffFld\"].hide();", 100 );
		
	}
}

//******************************************************
function changeHandler_felFeeTypeFld()
{	
	if (UTL.getElem('felFeeTypeFld').value != 2 && _errorMap['FeeScales_TableDiv']) 
	{
		_errorMap['FeeScales_TableDiv'].hide();
	}
}

//******************************************************
function validateFeeScales()
{	
	var isValid = true;
	// Fee Type = 2 -> Scale
	if ( ( UTL.getElem('BackEndLoadDiv') && UTL.getElem('belFeeTypeFld').value == 2 )
		|| ( UTL.getElem('FrontEndLoadDiv') && UTL.getElem('felFeeTypeFld').value == 2 ) )
	{				
		isValid = activeFeeScalesExist()
		
		if (!isValid)
		{
			Desktop.paintFieldErrorFlag( _errorMap, 'FeeScales_TableDiv', "Fee Scales are mandatory for Fee Type = Scale" );
		}
	}
	return isValid;
}

//******************************************************
function activeFeeScalesExist()
{
	var rows = UTL.getElem('FeeScales_Table').lastChild.childNodes		
	var activeRows = false;		
	for ( var i = 0; i < rows.length; i++ )
	{			
		activeRows = activeRows || rows[i].status != 'del';			
	}
	return activeRows;
}
