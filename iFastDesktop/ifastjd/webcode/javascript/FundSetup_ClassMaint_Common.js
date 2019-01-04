var _isAddMode = null;

//******************************************************
function confirmReset()
{
	return confirm( "Unsaved changes will be undone. Are you sure you wish to proceed?" );	
}

//******************************************************
function clickHandler_saveChangesBtn()
{
	if ( ClassDataManager.validateMandatoryFields() )
	{
		ClassDataManager.save( ClassDataManager.buildUpdateXMLDoc() );
	}	
}

//******************************************************
function clickHandler_nextEditScreenBtn()
{
	if ( ClassDataManager.validateMandatoryFields() )
	{
		ClassDataManager.saveAndLoadScreen( _editScreenNameArray[_currentEditScreenIndex + 1], ClassDataManager.buildUpdateXMLDoc() );
	} 	
}

//******************************************************
function clickHandler_prevEditScreenBtn()
{		
	if ( ClassDataManager.isUnsavedChanges() && confirm( "Do you wish to save changes?" ) )
	{
		if ( ClassDataManager.validateMandatoryFields() )
		{
			ClassDataManager.saveAndLoadScreen( _editScreenNameArray[_currentEditScreenIndex - 1], ClassDataManager.buildUpdateXMLDoc() );
		} 
	}
	else
	{
		ClassDataManager.loadScreen( _editScreenNameArray[_currentEditScreenIndex - 1] );
	}			
}

//******************************************************
function clickHandler_summaryBtn()
{	
	if ( ClassDataManager.isUnsavedChanges()
		&& confirm( "Do you wish to save changes?" ) )
	{
		ClassDataManager.saveAndLoadScreen( "Summary", ClassDataManager.buildUpdateXMLDoc() );			
	}
	else
	{
		ClassDataManager.loadScreen( "Summary" );
	}	
}

//******************************************************
function clickHandler_addSummaryBtn()
{	
	if ( ClassDataManager.validateMandatoryFields() )
	{
		ClassDataManager.saveAndLoadScreen( "Summary", ClassDataManager.buildUpdateXMLDoc() );
	} 	
}

//******************************************************
function clickHandler_breadCrumbItem( item )
{
	if ( ClassDataManager.isUnsavedChanges()
	&& confirm( "Do you wish to save changes?" ) )
	{
		ClassDataManager.saveAndLoadScreen( item.screenName, ClassDataManager.buildUpdateXMLDoc() );		
	}
	else
	{
		ClassDataManager.loadScreen( item.screenName );			
	}
}

//******************************************************
function clickHandler_cancelAddBtn()
{
	if ( confirm ( "Are you sure you wish to discard all changes?" ) )
	{			
		ClassDataManager.returnToMainScreen();
	}	
}

//******************************************************
function goToNextEditScreen()
{
	if ( _currentEditScreenIndex < _editScreenNameArray.length - 1 )
	{
		goToScreen( _editScreenNameArray[_currentEditScreenIndex + 1] );
	}	
}

//******************************************************
function goToPrevEditScreen()
{
	if ( _currentEditScreenIndex > 0 )
	{
		goToScreen( _editScreenNameArray[_currentEditScreenIndex - 1] );
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
var ClassDataManager = new function()
{
	var _currentScreenName = null
	var _currentScreenSectionName = null;
	var _unsavedChanges = false;
	var _origDataXMLDoc = null;
	var _existingUpdateDataXMLDoc = null;
	var _fieldFlagMap = null;
	
	this.init = function( origDataXMLDoc )
	{
		_origDataXMLDoc = origDataXMLDoc;
		_existingUpdateDataXMLDoc = null;						
	}
	
	this.isUnsavedChanges = function()
	{
		return _unsavedChanges;
	}
		
	this.save = function( xmlDoc )
	{
		var paramMap = {}
		paramMap["cz"]                = _vCZ;
		paramMap["jobname"]           = "FundSetup_ClassMaint_Save";    
		paramMap["companyCode"]       = _companyCode;
		paramMap["ruserId"]           = _ruserId;
		paramMap["sessionId"]         = _sessionId;
		paramMap["envName"]           = _envName;
		paramMap["dateFormat"]        = _dateFormat;
		paramMap["tidx"]       	  	  = _tidx;		
		    
		var req = HTTP.getPOSTRequest( HTTP.buildURL( _vServletPath, paramMap ) );		
		req.setCallbackFunction( callback )
		req.setAsynch( true );
		Desktop.showProcessingIndicator();
		//prompt( "", XML.serialize( xmlDoc ) );
		req.send( XML.serialize( xmlDoc ) );
		
		function callback( responseText )
		{										
			Desktop.hideProcessingIndicator();
			
			_unsavedChanges = false;
			initScreenButtons( _currentScreenSectionName, _currentScreenName );
		}
	}
	
	this.saveAndLoadScreen = function( screenToLoad, xmlDoc )
	{
		var form = UTL.getElem( "screenForm" );
		
		form.action = _vServletPath;
		
		UTL.getElem( "czFld" ).value     		= _vCZ;
		UTL.getElem( "jobnameFld" ).value       = "FundSetup_ClassMaint_SaveAndLoadScreen";    
		UTL.getElem( "companyCodeFld" ).value   = _companyCode;
		UTL.getElem( "ruserIdFld" ).value       = _ruserId;
		UTL.getElem( "sessionIdFld" ).value     = _sessionId;
		UTL.getElem( "envNameFld" ).value       = _envName;
		UTL.getElem( "dateFormatFld" ).value    = _dateFormat;
		UTL.getElem( "bgcolorFld" ).value       = _vDesktopColor;
		UTL.getElem( "tidxFld" ).value        	= _tidx;    
		UTL.getElem( "screenToLoadFld" ).value  = screenToLoad;
		
		UTL.getElem( "data" ).value = XML.serialize( xmlDoc );
		
		Desktop.showProcessingIndicator();
		
		form.submit();
	}
	
	this.loadScreen = function( screenToLoad )
	{													
		var form = UTL.getElem( "screenForm" );
		
		form.action = _vServletPath;
		
		UTL.getElem( "czFld" ).value     		= _vCZ;
		UTL.getElem( "jobnameFld" ).value       = "FundSetup_ClassMaint_LoadScreen";    
		UTL.getElem( "companyCodeFld" ).value   = _companyCode;
		UTL.getElem( "ruserIdFld" ).value       = _ruserId;
		UTL.getElem( "sessionIdFld" ).value     = _sessionId;
		UTL.getElem( "envNameFld" ).value       = _envName;
		UTL.getElem( "dateFormatFld" ).value    = _dateFormat;
		UTL.getElem( "bgcolorFld" ).value       = _vDesktopColor;
		UTL.getElem( "tidxFld" ).value        	= _tidx;    
		UTL.getElem( "screenToLoadFld" ).value  = screenToLoad;
			
		Desktop.showProcessingIndicator();			
		form.submit();
	}
	
	this.returnToMainScreen = function()
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
		paramMap["fundCode"]  	 = ClassDataManager.getCurrentData( "fundCode" );

		var url = HTTP.buildURL( _vServletPath, paramMap );
		window.location = url; 
	}
	
	this.setScreenUpdated = function()
	{
		_unsavedChanges = true;
								
		UTL.getElem( "resetBtn" ).disabled = false;
		UTL.getElem( "saveChangesBtn" ).disabled = false;		
		
		if ( _isAddMode )
		{
			UTL.getElem( "nextScreenBtn" ).disabled = false;
		}			
	}
	
	this.loadExistingUpdates = function ( updatesDataXMLDoc )
	{		
		_existingUpdateDataXMLDoc = updatesDataXMLDoc;			
	}
	
	this.buildUpdateXMLDoc = function()
	{
		var updateXMLDoc = XML.newDocument( "UpdatesToSave" );
		buildUpdateXMLFromFields( updateXMLDoc );
		buildUpdateXMLFromTables( updateXMLDoc );
		return updateXMLDoc;		
	}
		
	this.initScreen = function( screenSectionName, screenName )
	{
		_currentScreenName = screenName;
		_currentScreenSectionName = screenSectionName;
		
		_fieldFlagMap = {};
		
		var sourceXMLDoc = null;
		if ( _isAddMode )
		{			
			sourceXMLDoc = _existingUpdateDataXMLDoc;
		}
		else
		{
			sourceXMLDoc = ClassDataManager.getUpdateData( screenSectionName ) != null ? _existingUpdateDataXMLDoc : _origDataXMLDoc;
		}
		
		initAndPopulateScreenFields( sourceXMLDoc );					
		populateScreenTables( sourceXMLDoc );
		
		if ( _isAddMode )
		{
			initBreadCrumbs( screenName );
		}
		initScreenButtons( screenSectionName, screenName )			
	}
	
	function initBreadCrumbs( screenName )
	{

	}
	
	function initScreenButtons( screenSectionName, screenName )
	{
		if ( _isAddMode )
		{
			if ( screenName == "BasicInfo" )
			{				
				UTL.getElem( "prevScreenBtn" ).style.display = "none";
			}
			if ( screenName == "TradeDayCtrls" )
			{
				UTL.getElem( "nextScreenBtn" ).style.display = "none"; 
				UTL.getElem( "viewSummaryBtn" ).style.display = "block";
			}
			else
			{
				UTL.getElem( "nextScreenBtn" ).style.display = "block"; 
				UTL.getElem( "viewSummaryBtn" ).style.display = "none";
			}
			
			UTL.getElem( "nextScreenBtn" ).disabled = false;
			UTL.getElem( "resetBtn" ).disabled = true;
			UTL.getElem( "saveChangesBtn" ).disabled = true;
			UTL.getElem( "cancelAddBtn" ).disabled = false;
			UTL.getElem( "viewSummaryBtn" ).disabled = false;
		}
		else
		{
			UTL.getElem( "resetBtn" ).disabled = true;
			UTL.getElem( "saveChangesBtn" ).disabled = true;			
			UTL.getElem( "returnToSummaryBtn" ).disabled = false;
		}
	}
	
	this.resetScreen = function()
	{
		for ( var i in _fieldFlagMap )
		{
			_fieldFlagMap[i].hide();
		}
		
		var sourceXMLDoc = null;
		if ( _isAddMode )
		{
			sourceXMLDoc = _existingUpdateDataXMLDoc;
		}
		else
		{
			sourceXMLDoc = ClassDataManager.getUpdateData( _currentScreenSectionName ) != null ? _existingUpdateDataXMLDoc : _origDataXMLDoc;
		}
		
		populateScreenFields( sourceXMLDoc );
		populateScreenTables( sourceXMLDoc );
		
		
		UTL.getElem( "resetBtn" ).disabled = true;		
		_unsavedChanges = false;

		initScreenButtons( _currentScreenSectionName, _currentScreenName );
	}
	
	function changeHandler_screenFld( e )
	{
		var fld = e.currentTarget;
		if ( _fieldFlagMap[fld.id] )
		{
			_fieldFlagMap[fld.id].hide();
		}
		ClassDataManager.setScreenUpdated();
	}
	
	function clickHandler_screenCheckbox( e )
	{
		ClassDataManager.setScreenUpdated();
	}
	
	function initAndPopulateScreenFields( xmlDoc )
	{
		var inputArray = UTL.getElem( "input", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );	
		for ( var i = 0; i < inputArray.length; i++ )
		{		
			var input = inputArray[i];				
			if ( input.xpath != null && input.xpath.length > 0 && input.override != "true" )
			{								
				if ( input.type.toLowerCase() == "checkbox" )
				{
					EvtHandler.add( input, 'click', clickHandler_screenCheckbox );
				}
				else
				{
					EvtHandler.add( input, 'change', changeHandler_screenFld );
				}
				populateField( input, xmlDoc );				
			}
		}
	
		var selectArray = UTL.getElem( "select", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );
		for ( var i = 0; i < selectArray.length; i++ )
		{
			var select = selectArray[i];
			if ( select.xpath != null && select.xpath.length > 0 )
			{
				EvtHandler.add( select, 'change', changeHandler_screenFld );
				populateField( select, xmlDoc );
			}
		}
	}
	
	function populateScreenFields( xmlDoc )
	{		
		var inputArray = UTL.getElem( "input", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );	
		for ( var i = 0; i < inputArray.length; i++ )
		{
			var input = inputArray[i];					
			if ( input.xpath != null && input.xpath.length > 0 && input.override != "true" )
			{
				populateField( input, xmlDoc );
			}			
		}
	
		var selectArray = UTL.getElem( "select", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );
		for ( var i = 0; i < selectArray.length; i++ )
		{
			var select = selectArray[i];
			if ( select.xpath != null && select.xpath.length > 0 )
			{
				populateField( select, xmlDoc );
			}
		}		
	}
	
	function populateField( fld, xmlDoc )
	{		
		if ( xmlDoc != null )
		{
			var fldNode = XML.getNode( fld.xpath, xmlDoc );			
			
			if ( fldNode != null )
			{	
				var fldValue = fldNode.text;
				if ( fld.type.toLowerCase() == "checkbox" )
				{
					fld.checked = ( fldValue.toLowerCase() == "yes" ? true : false ); 
				}
				else
				{
					fld.value = fldValue;
					
				}
			}
			else
			{
				if ( fld.type.toLowerCase() == "checkbox" )
				{
					fld.checked = false 
				}
				else
				{
					fld.value = ""
				} 
			}
		}		
	}
	
	function populateScreenTables( xmlDoc )
	{
		var tableArray = UTL.getElem( "table", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );
		
		for ( var i = 0; i < tableArray.length; i++ )
		{
			var table = tableArray[i];
			if ( table.xpath != null && table.xpath.length > 0 )
			{
				populateTable( table, xmlDoc );
			}
		}
	}
	
	function populateTable( table, xmlDoc )
	{
		while( table.lastChild.lastChild )
		{
			table.lastChild.removeChild( table.lastChild.lastChild );
		}
		
		if ( xmlDoc )
		{		
			var recordNodeArray = XML.getNodes( table.xpath, xmlDoc );
			
			for ( var r = 0; r < recordNodeArray.length; r++ )
			{
				appendTableRecord( table, XML.buildJSON( recordNodeArray[r] ) );
				table.lastChild.lastChild.status = XML.getAttrbute( "status", recordNodeArray[r] );
				
				if ( table.lastChild.lastChild.status == "del" )
				{
					table.lastChild.lastChild.style.display = "none";
				}
			}
		}
		
		IFDSTableManager.reInitTable( table.id );
	}
	
	function appendTableRecord( table, recordDataMap )
	{
		var newRow = document.createElement( "tr" );
				
		for ( var f in recordDataMap )
		{
			newRow[f] = recordDataMap[f]; 			
		}		
		
		var displayFieldArray = table.displayFieldList.split( ";" );	
		for ( var i = 0; i < displayFieldArray.length; i++ )
		{
			var cell = document.createElement( "td" );			
			newRow.appendChild( cell );
			cell.title = recordDataMap[displayFieldArray[i]];;
			cell.innerHTML = recordDataMap[displayFieldArray[i]];
		}
		
		table.lastChild.appendChild( newRow );		
	}
	
	this.addRecordToTable = function( table, recordDataMap )
	{		
		appendTableRecord( table, recordDataMap );
		table.lastChild.lastChild.status = "add";
		
	}
	
	this.modifyRecordInTable = function( table, rowIndex, recordDataMap )
	{
		var row = table.lastChild.childNodes[rowIndex];
		row.status = "mod";
		for ( var f in recordDataMap )
		{
			row[f] = recordDataMap[f]; 			
		}		
		
		var displayFieldArray = table.displayFieldList.split( ";" );	
		for ( var i = 0; i < displayFieldArray.length; i++ )
		{
			var cell = row.childNodes[i];						
			cell.title = recordDataMap[displayFieldArray[i]];;
			cell.innerHTML = recordDataMap[displayFieldArray[i]];
		}
	}
	
	this.deleteRecordInTable = function( table, rowIndex )
	{
		var row = table.lastChild.childNodes[rowIndex];
		row.status = "del";
		row.style.display = "none";
		
		IFDSTableManager.reInitTable( table.id );		
	}
	
	function buildUpdateXMLFromFields( updateXML )
	{
		var inputArray = UTL.getElem( "input", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );	
		for ( var i = 0; i < inputArray.length; i++ )
		{
			var input = inputArray[i];
			if ( input.xpath != null && input.xpath.length > 0 )
			{
				buildUpdateXMLFromField( updateXML, input );
			}
		}
	
		var selectArray = UTL.getElem( "select", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );
		for ( var i = 0; i < selectArray.length; i++ )
		{
			var select = selectArray[i];
			if ( select.xpath != null && select.xpath.length > 0 )
			{
				buildUpdateXMLFromField( updateXML, select );
			}
		}
	}
	
	function buildUpdateXMLFromField( updateXML, fld )
	{
		var origDataValue = ClassDataManager.getOrigData( fld.xpath );		
		var fldValue = null;		 
		
		if ( fld.type.toLowerCase() == "checkbox" )
		{
			fldValue = ( fld.checked ? "yes" : "no" ); 			
		}
		else
		{
			fldValue = fld.value;
		}		
		
		var node = XML.addNodeWithValue( fld.xpath, updateXML, fldValue );
		
		if ( origDataValue != fldValue )
		{
			XML.addAttribute( "status", "mod", node );			
		}
		
		if ( fld.descXpath )
		{
			if ( fld.selectedIndex >= 0 )
			{
				XML.addNodeWithValue( fld.descXpath, updateXML, fld.options[fld.selectedIndex].text );
			}
			else
			{
				XML.addNodeWithValue( fld.descXpath, updateXML, "" );
			}
		}
		
	}
			
	function buildUpdateXMLFromTables( updateXML )
	{
		var tableArray = UTL.getElem( "table", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );
		
		for ( var i = 0; i < tableArray.length; i++ )
		{
			var table = tableArray[i];
			if ( table.xpath != null && table.xpath.length > 0 )
			{				
				buildUpdateXMLFromTable( updateXML, table );							
			}			
		}
	}
	
	function buildUpdateXMLFromTable( updateXML, table )
	{
		var rowArray = table.lastChild.childNodes;
		var newDataArray = new Array( rowArray.length );
		var fieldListArray = table.fieldList.split( ";" );
		
		var recordNode = null;
		for ( var r = 0; r < rowArray.length; r++ )
		{
			recordNode = XML.addNode( table.xpath, updateXML );				
			var row = rowArray[r];
			for ( var f = 0; f < fieldListArray.length; f++ )
			{
				var fieldName = fieldListArray[f];
				XML.addNodeWithValue( fieldName, recordNode, row[fieldName] );	
			}
			
			if ( row.status && row.status != "" )
			{
				XML.addAttribute( "status", row.status, recordNode );
			}																				
		}	
	}
	
	this.getOrigData = function( xpath )
	{
		if ( _origDataXMLDoc )
		{
			var node = XML.getNode( xpath, _origDataXMLDoc );
			if ( node != null )
			{
				return node.text;			
			}
		}
		return null; 
	}
	
	this.getUpdateData = function( xpath )
	{
		if ( _existingUpdateDataXMLDoc != null )
		{			
			var node = XML.getNode( xpath, _existingUpdateDataXMLDoc );
			if ( node != null )
			{				
				return node.text;				
			}		
		}
		
		return null;		
	}
	
	this.getCurrentData = function( xpath )
	{
		return ( this.getUpdateData( xpath ) != null ? this.getUpdateData( xpath ) : this.getOrigData( xpath ) );
	}
	
	this.getUpdateXMLDoc = function()
	{
		return _existingUpdateDataXMLDoc;
	}
	
	this.validateMandatoryFields = function()
	{
		for ( var i in _fieldFlagMap )
		{
			_fieldFlagMap[i].hide();
		}
		
		var errorFound = false;		
		var inputArray = UTL.getElem( "input", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );
		for ( var i = 0; i < inputArray.length; i++ )
		{
			var input = inputArray[i];
			if ( input.mandatory && input.mandatory == "true" && input.value == "" )
			{
				Desktop.paintFieldErrorFlag( _fieldFlagMap, input.id, "Missing mandatory field" );
				errorFound = true;
			}
		}
		
		var selectArray = UTL.getElem( "select", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );
		for ( var i = 0; i < selectArray.length; i++ )
		{
			var select = selectArray[i];
			if ( select.mandatory && select.mandatory == "true" && select.value == "" )
			{
				Desktop.paintFieldErrorFlag( _fieldFlagMap, select.id, "Missing mandatory field" );
				errorFound = true;
			}
		}
			
		if ( _currentEditScreenIndex == 4 && !validateFeeScales())  //Fee Conf
		{
			errorFound = true;
		}
		
		return !errorFound;
	}
}