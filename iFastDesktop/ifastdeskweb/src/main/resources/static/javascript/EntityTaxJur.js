var _ADD = "add";
var _MOD = "mod";
var _DEL = "del";

var _allowAdd = null;
var _allowMod = null;
var _allowDel = null;

var _entityId = null;

var _errorMap = null;

var _updates = false;

//******************************************************
function loading()
{
	IFDSTableManager.init();
	IFDSTableManager.getTable( "TaxJur_Table" ).setOnRowSelectedFunction( selectHandler_TaxJurTable );
	
	IFDSDatepickerManager.init( _dateFormat, "calendarHolder", "calendarBtn", setDatepickerCalendarPosition );
	
	_errorMap = {};
	
	if ( !_allowAdd )
	{
		UTL.getElem( "addBtn" ).disabled = true;
	}
}

//******************************************************
function clickHandler_addBtn()
{
	openPopup( _ADD );	
}

//******************************************************
function changeHandler_taxJurPopupEffDateFld()
{
	if ( _errorMap["TaxJurPopup_effDateFld"] )
	{
		_errorMap["TaxJurPopup_effDateFld"].hide();
	}
}

//******************************************************
function clickHandler_modBtn()
{
	openPopup( _MOD );
}

//******************************************************
function selectHandler_TaxJurTable()
{
	var selectedRowIndex = IFDSTableManager.getTable( "TaxJur_Table" ).getSelectedRowIndex();
	var selectedRow = UTL.getElem( "TaxJur_Table" ).lastChild.childNodes[selectedRowIndex];
	if( selectedRow.runMode == _ADD )
	{
		enableModBtn();
		enableDelBtn();	
	}
	else
	{
		if( selectedRow.allowUpd == "yes" )
		{
			enableModBtn();		
		}
		else
		{
			disableModBtn();		
		}
		
		if( selectedRow.allowDel == "yes" )
		{
			enableDelBtn();		
		}
		else
		{
			disableDelBtn();		
		}
	}
}

//******************************************************
function openPopup( mode )
{
	var draggable = true;
	switch( mode )
	{
		case _ADD:
		{
			populatePopup( _ADD );
			IFDSTableManager.getTable( "TaxJur_Table" ).clearSelectedRowIndex();
			disableModBtn();
			disableDelBtn();
			Desktop.showPopup( "TaxJurPopup", "Entity Tax History - Add", draggable );			
			break;
		}
		case _MOD:
		{
			populatePopup( _MOD, IFDSTableManager.getTable( "TaxJur_Table" ).getSelectedRowIndex() );
			Desktop.showPopup( "TaxJurPopup", "Entity Tax History - Modify", draggable );
			break;
		}
		case _DEL:
		{
			populatePopup( _DEL, IFDSTableManager.getTable( "TaxJur_Table" ).getSelectedRowIndex() );
			Desktop.showPopup( "TaxJurPopup", "Entity Tax History - Delete", draggable );
			break;
		}	
	}
}

//******************************************************
function populatePopup( runMode, selectedRowIndex )
{
	UTL.getElem( "TaxJurPopup_runModeFld" ).value = runMode;
	switch( runMode )
	{	
		case _ADD:
		{					
			UTL.getElem( "deleteConfirmationDiv" ).style.display = "none";
			UTL.getElem( "TaxJurPopup_taxJurFld" ).selectedIndex = 0;
			UTL.getElem( "TaxJurPopup_taxJurFld" ).disabled = false;
			UTL.getElem( "TaxJurPopup_effDateFld" ).value = "";
			UTL.getElem( "TaxJurPopup_effDateFld" ).disabled = false;
			break;
		}
		case _MOD:
		{
			var row = UTL.getElem( "TaxJur_Table" ).lastChild.childNodes[selectedRowIndex];
			UTL.getElem( "deleteConfirmationDiv" ).style.display = "none";			
			UTL.getElem( "TaxJurPopup_taxJurFld" ).value = row.taxJuris;
			UTL.getElem( "TaxJurPopup_taxJurFld" ).disabled = false;			
			UTL.getElem( "TaxJurPopup_effDateFld" ).value = row.effDate;
			UTL.getElem( "TaxJurPopup_effDateFld" ).disabled = false;
			break;
		}
		case _DEL:
		{
			var row = UTL.getElem( "TaxJur_Table" ).lastChild.childNodes[selectedRowIndex];
			UTL.getElem( "deleteConfirmationDiv" ).style.display = "block";			
			UTL.getElem( "TaxJurPopup_taxJurFld" ).value = row.taxJuris;
			UTL.getElem( "TaxJurPopup_taxJurFld" ).disabled = true;			
			UTL.getElem( "TaxJurPopup_effDateFld" ).value = row.effDate;
			UTL.getElem( "TaxJurPopup_effDateFld" ).disabled = true;
			break;
		}
	}
}

//******************************************************
function LaunchConfirm()
{
	return _updates;
}

//******************************************************
function disableModBtn()
{
	UTL.getElem( "ModBtn" ).disabled = true;
}

//******************************************************
function enableModBtn()
{
	if ( _allowAdd )
	{
		UTL.getElem( "ModBtn" ).disabled = false;
	}
}

//******************************************************
function disableDelBtn()
{
	UTL.getElem( "DelBtn" ).disabled = true;
}

//******************************************************
function enableDelBtn()
{	
	if ( _allowDel )
	{
		UTL.getElem( "DelBtn" ).disabled = false;
	}
}

//******************************************************
function setDatepickerCalendarPosition( datepickerFld )
{
    var datepickerFldPosObj = WebTools.calcElemPos( datepickerFld );

	var calendarPosObj = {};
	calendarPosObj["top"] = parseInt( datepickerFldPosObj.top ) + datepickerFld.offsetHeight + 3;
	calendarPosObj["left"] = parseInt( datepickerFldPosObj.left ) +  parseInt( datepickerFld.offsetWidth );
	calendarPosObj["container"] = document.body;
	calendarPosObj["zIndex"] = 101;
    return calendarPosObj;
}

//******************************************************
function clickHandler_TaxJurPopupCancelBtn()
{
	clearErrors();
	Desktop.hidePopup( "TaxJurPopup" );
}

//******************************************************
function clearErrors()
{
	for ( var i in _errorMap )
	{
		_errorMap[i].hide();
	}
}

//******************************************************
function update()
{
	var updateData = buildUpdateData();
	var updateStatus = null;
	if ( updateData != null )
	{		
		sendUpdateRequest( updateData, doUpdate_callback );
	}
	return updateStatus;
	
	function doUpdate_callback( success )
	{
		if ( success )
		{
			updateStatus = Desktop.SUCCESS;
		}		
		else
		{
			updateStatus = Desktop.FAIL;
		}
	}
}

//******************************************************
function buildUpdateData()
{
	var xmlDoc = XML.newDocument( "data" )
	
	var rows = UTL.getElem( "TaxJur_Table" ).lastChild.childNodes;
	updateCount = 0;
	for ( var i = 0; i < rows.length; i++ )
	{
		var row = rows[i];
	
		if ( row.runMode != "" )
		{
			var recordXML = XML.addNode( "EntTaxHistUpd", xmlDoc );
			XML.addNodeWithValue( "runMode", recordXML, row.runMode );
			XML.addNodeWithValue( "entityID", recordXML, _entityId );
			XML.addNodeWithValue( "taxJuris", recordXML, row.taxJuris );
			XML.addNodeWithValue( "taxJurisDeff", recordXML, row.effDate );
			XML.addNodeWithValue( "entTaxHistID", recordXML, row.entTaxHistID );
			XML.addNodeWithValue( "version", recordXML, row.version );
			updateCount++;
		}
	}
	
	if ( updateCount > 0 )
	{
		return xmlDoc;
	}
	else
	{
		return null;
	}
}	

//******************************************************
function sendUpdateRequest( updateXML, callbackFn )
{
	function sendUpdateRequest_callback( responseText )
	{		
		Desktop.hideProcessingIndicator();
				
		var responseXML = null;
		try 
		{
			responseXML = XML.parseToXML( responseText );
			var successful = true;			
			if ( responseXML )
			{
				if ( responseErrorFound( responseXML ) )
				{
					displayResponseError( responseXML );
					successful = false;	
				}						
			}										
		}
		catch( e )
		{ 
			alert( "FUNCTION ERROR: sendSaveRequest error caught: " + e.description ); 		
		}
		
		callbackFn( successful );
	}
	
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "EntityTaxJur_Update";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
        
    var url = HTTP.buildURL( _vServletPath, paramMap );                   		    	
	var req = HTTP.getPOSTRequest( url );
	req.setAsynch( false );			
	req.setCallbackFunction( sendUpdateRequest_callback );	
	Desktop.showProcessingIndicator();
	//prompt( "", XML.serialize( updateXML ) );
	req.send( XML.serialize( updateXML ) );		
}

//******************************************************
function responseErrorFound( responseXML )
{
	return XML.getNode( "/responseContents/Error", responseXML ) != null
}

//******************************************************
function displayResponseError( responseXML )
{
	var errorNode = XML.getNode( "/responseContents/Error", responseXML );
	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
	if ( errorType.toLowerCase() == "environment" )
	{
		DesktopError.displayProcessingError( "Fund Setup - Class Copy", errorMsg );  
	}
	else
	{
		alert( errorMsg );
	}
}

//******************************************************
function clickHandler_TaxJurPopupOKBtn()
{
	if ( UTL.getElem( "TaxJurPopup_effDateFld" ).value != ""
		&& IFDSDatepicker.isValidDateValue( UTL.getElem( "TaxJurPopup_effDateFld" ).value, _dateFormat ) )
	{
		updateTable( UTL.getElem( "TaxJurPopup_runModeFld" ).value,
						UTL.getElem( "TaxJurPopup_taxJurFld" ).value,
						UTL.getElem( "TaxJurPopup_taxJurFld" ).options[UTL.getElem( "TaxJurPopup_taxJurFld" ).selectedIndex].text,
						UTL.getElem( "TaxJurPopup_effDateFld" ).value );
		Desktop.hidePopup( "TaxJurPopup" );
		_updates = true; 	
	}
	else
	{
		Desktop.paintFieldErrorFlag( _errorMap, "TaxJurPopup_effDateFld", "Invalid date value" );
	}
}

//******************************************************
function updateTable( runMode, taxJur, taxJurDesc, deff )
{
	switch( runMode )
	{
		case _ADD:
		{
			var newRow = document.createElement( "tr" );
			newRow.runMode = _ADD;
			newRow.taxJuris = taxJur;
			newRow.effDate = deff;
			newRow.version = "";
			
			var yearCell = newRow.appendChild( document.createElement( "td" ) );
			var deffObj = new Date( deff );
			yearCell.innerHTML = deffObj.getFullYear();
			var taxJurCell = newRow.appendChild( document.createElement( "td" ) );
			taxJurCell.innerHTML = taxJur + " - " + taxJurDesc;
			var deffCell = newRow.appendChild( document.createElement( "td" ) );
			deffCell.innerHTML = deff;
			var createdOnCell = newRow.appendChild( document.createElement( "td" ) );
			var createdByCell = newRow.appendChild( document.createElement( "td" ) );
			var modeDateCell = newRow.appendChild( document.createElement( "td" ) );
			var modByCell = newRow.appendChild( document.createElement( "td" ) );
			
			UTL.getElem( "TaxJur_Table" ).lastChild.appendChild( newRow );
			IFDSTableManager.reInitTable( "TaxJur_Table" );
			break;
		}
		case _MOD:
		{
			var selectedRowIndex = IFDSTableManager.getTable( "TaxJur_Table" ).getSelectedRowIndex();
			var row = UTL.getElem( "TaxJur_Table" ).lastChild.childNodes[selectedRowIndex];
			row.runMode = ( row.runMode == "" ? _MOD : row.runMode );
			row.taxJuris = taxJur;
			row.childNodes[1].innerHTML = taxJur + " - " + taxJurDesc;					
			row.effDate = deff;
			row.childNodes[2].innerHTML = deff;
			break;  			
		}
		case _DEL:
		{
			var selectedRowIndex = IFDSTableManager.getTable( "TaxJur_Table" ).getSelectedRowIndex();
			var row = UTL.getElem( "TaxJur_Table" ).lastChild.childNodes[selectedRowIndex];
			if ( row.runMode == _ADD )
			{
				row.runMode = "";
			}
			else
			{
				row.runMode = _DEL;
			}
			row.style.display = "none";
			IFDSTableManager.reInitTable( "TaxJur_Table" );
		}
	}
}

//******************************************************
function clickHandler_delBtn()
{
	openPopup( _DEL );
}