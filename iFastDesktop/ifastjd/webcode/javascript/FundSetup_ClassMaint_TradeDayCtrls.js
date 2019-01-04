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
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );
	
	ClassDataManager.initScreen( "TradeDayControls", "TradeDayCtrls" );
}

//******************************************************
function clickHandler_resetScreenBtn()
{
	if ( confirmReset() )
	{
		ClassDataManager.resetScreen();
	}
}