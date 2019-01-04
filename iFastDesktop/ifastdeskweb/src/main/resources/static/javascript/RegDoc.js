var _disableDiv = null;
var _processingDiv = null;
var _updatesMade = false;

var _docListTable = null;
var _selectedRow = null;

var _ADD_MODE = 0;
var _MODIFY_MODE = 1;
var _DELETE_MODE = 2;

var _popupMode = null;



/**
 * init Regulatory Documents screen 
 */
function initRegDoc()
{
	IFDSTableManager.init();
	_docListTable = IFDSTableManager.getTable( "DocListTable" );
	_docListTable.setOnRowSelectedFunction( selectHandler_DocListTable )
		
	// build divs for "showProcessing"
	_disableDiv = buildDisableDiv();
	_processingDiv = buildProcessingDiv();
	
	setActionButtonsState( false );		
}


/**
 * row select handler for DocList table 
 */
function selectHandler_DocListTable( rowIndex )
{	
	_selectedRow = UTL.getElem( "DocListTable" ).lastChild.childNodes[rowIndex];
	setActionButtonsState( true );	
}


/**
 * click handler for Add button 
 */
function clickHandler_addBtn()
{	
	displayPopup( _ADD_MODE );
}


/**
 * click handler for Modify button 
 */
function clickHandler_modifyBtn()
{
	displayPopup( _MODIFY_MODE );
}


/**
 * click handler for Delete button 
 */
function clickHandler_deleteBtn()
{
	displayPopup( _DELETE_MODE );
}


/**
 * click handler for Save/OK button (on popup) 
 */
function clickHandler_saveBtn()
{	
	sendRegDocUpdateRequest();
}


/**
 * click handler for Cancel button (on popup) 
 */
function clickHandler_cancelBtn()
{	
	hidePopup();	
}


/**
 * enable/disable the "Action" buttons (Add/Modify/Delete), 
 * based on when a row is selected, and if user has permissions 
 */
function setActionButtonsState( isRowSelected )
{
	var addBtn = UTL.getElem( "btnAdd" );
	var modBtn = UTL.getElem( "btnModify" );
	var delBtn = UTL.getElem( "btnDelete" ); 
		
	if ( _userPermissionMap["add"] == "yes" )
	{
    	addBtn.disabled = false;
	}
	else
	{
		addBtn.disabled = true;
	}
		
	if ( isRowSelected )
	{
		if ( _userPermissionMap["mod"] == "yes" )
		{
			modBtn.disabled = false;
		}
		
		if ( _userPermissionMap["del"] == "yes" )
		{
			delBtn.disabled = false
		}			
	}
	else
	{
		modBtn.disabled = true;
		delBtn.disabled = true;
	}	
}


/**
 * displays the popup
 * 
 * @param {number} mode indicates the popup mode (Add/Modify/Delete) 
 */
function displayPopup( mode )
{	
	if ( mode == _ADD_MODE )
	{	
		// unclick any row that might be selected, and disable action buttons
		if( _selectedRow )
		{
			_docListTable.clearSelectedRowIndex();
			_selectedRow = null;
			setActionButtonsState( true );				
		}
		// all popup fields enabled for add mode
		UTL.getElem( "Popup_docCodeFld" ).disabled = false;
		UTL.getElem( "Popup_descriptionFld" ).disabled = false;		
		UTL.getElem( "btnSave" ).style.display = "inline";			
	}
	else if ( mode == _MODIFY_MODE )
	{
		if ( _selectedRow )
		{
			// load details from selected row
			populatePopup( _selectedRow );
		}
		else
		{
			throw new Error( Err.genErrMsg( "_selectedRow is null", "displayPopup()", "DocList.js" ) );								
		}		
		// only description field enabled for modify mode
		UTL.getElem( "Popup_descriptionFld" ).disabled = false;
		UTL.getElem( "btnSave" ).style.display = "inline";
	}
	else if ( mode == _DELETE_MODE )
	{
		if ( _selectedRow )
		{
			// load details from selected row
			populatePopup( _selectedRow );
		}
		else
		{
			throw new Error( Err.genErrMsg( "_selectedRow is null", "displayPopup()", "DocList.js" ) );
		}
		// no fields enabled for delete mode
		UTL.getElem( "DeleteConfirm" ).style.display = "block";
		UTL.getElem( "btnOK" ).style.display = "inline";
	}
	
	displayDisabler();	
	UTL.getElem( "PopupIframe" ).style.display = "block";
	UTL.getElem( "DocListPopup" ).style.display = "block";
	_popupMode = mode;
}


/**
 * hides the update popup 
 */
function hidePopup()
{
	resetPopup();
	hideDisabler();
	UTL.getElem( "PopupIframe" ).style.display = "none";
	UTL.getElem( "DocListPopup" ).style.display = "none";		
}


/**
 * populate the popup fields with values from the given row 
 */
function populatePopup( DocListTableRow )
{	
	UTL.getElem( "Popup_docCodeFld" ).value = DocListTableRow.childNodes[0].data;
	UTL.getElem( "Popup_descriptionFld" ).value = DocListTableRow.childNodes[1].data;
}


/**
 * resets the popup 
 */
function resetPopup()
{
	UTL.getElem( "btnOK" ).style.display = "none";
	UTL.getElem( "btnSave" ).style.display = "none";			
	UTL.getElem( "Popup_docCodeFld" ).value = "";
	UTL.getElem( "Popup_docCodeFld" ).disabled = true;
	UTL.getElem( "Popup_descriptionFld" ).value = "";
	UTL.getElem( "Popup_descriptionFld" ).disabled = true;
	UTL.getElem( "DeleteConfirm" ).style.display = "none";
	_popupMode = null;
}


/**
 * clears the doc list table 
 */
function clearTable()
{
	var docListDiv = UTL.getElem( "DocListDiv" );
	var docListTable = UTL.getElem( "DocListTable" );
	
	docListDiv.removeChild( docListTable );	
}


/**
 * sends update request 
 */
function sendRegDocUpdateRequest()
{
	var paramMap = {}
    paramMap["cz"]                = _vCZ;
    paramMap["jobname"]           = "RegDoc_Process";    
    paramMap["companyCode"]       = _companyCode;
    paramMap["ruserId"]           = _ruserId;
    paramMap["sessionId"]         = _sessionId;
    paramMap["envName"]           = _envName;
    paramMap["dateFormat"]        = _dateFormat;
    
    var xml = "";
    var docCodeFld = UTL.getElem( "Popup_docCodeFld" );
    var docDescFld = UTL.getElem( "Popup_descriptionFld" );
        
    if ( _popupMode == _ADD_MODE )
    {    	
    	paramMap["action"] = "add";
    	xml = XML.createNodeStr( "RegDoc",
    	                         XML.createNodeStr( "docCode", XML.charEncode( docCodeFld.value ) )
    	                         + XML.createNodeStr( "docDesc", XML.charEncode( docDescFld.value ) ) );		
    }
    else if ( _popupMode == _MODIFY_MODE )
    {
    	paramMap["action"] = "modify";
    	xml = XML.createNodeStr( "RegDoc",
    	                         XML.createNodeStr( "docCode", XML.charEncode( docCodeFld.value ) )
    	                         + XML.createNodeStr( "docDesc", XML.charEncode( docDescFld.value ) ) );
    }
    else
    {
    	paramMap["action"] = "delete";
    	// don't think should need to include docDesc when deleting    	
    	xml = XML.createNodeStr( "RegDoc",
    	                         XML.createNodeStr( "docCode", XML.charEncode( docCodeFld.value ) )
    	                         + XML.createNodeStr( "docDesc", XML.charEncode( docDescFld.value ) ) );
    }
        
    var url = HTTP.buildURL( _vServletPath, paramMap );        		    	  
	displayProcessing();
	
	var req = HTTP.getPOSTRequest( url );
	req.setCallbackFunction( sendRegDocUpdateRequest_callback );	
	req.send( xml );    			  
}


/**
 * call back function from update request 
 */
function sendRegDocUpdateRequest_callback( responseText )
{
	var responseXML = XML.parseToXML( responseText );

    var errorNode = XML.getNode( "/responseContents/Error", responseXML );
    
    if ( errorNode )
    {
    	var errorType = XML.getNode( "type", errorNode ).firstChild.nodeValue;
    	var errorMsg = XML.getNode( "msg", errorNode ).firstChild.nodeValue;
    	if ( errorType.toLowerCase() == "environment" )
    	{
    		DesktopError.displayProcessingError( "Regulatory Documents", errorMsg );  
    	}
    	else
    	{
    		alert( errorMsg );
    	}
    	hideProcessing( true );        
    }
    else
    {   
    	// clear existing list
    	clearTable();
    	
    	// populate table with response
    	var tableUpdateNode = XML.getNode( "/responseContents/tableUpdate", responseXML );
    	var tableHTML = tableUpdateNode.firstChild.xml;    	    	    	
    	UTL.getElem( "DocListDiv" ).innerHTML = tableHTML;
    	// reInit the IFDSTable with the new contents
    	IFDSTableManager.reInitTable( "DocListTable" );
    	
    	setActionButtonsState( false );
    	hideProcessing( true );    	
    	hidePopup();
    	    	    	
		_updatesMade = true;    	
    }
}


/**
 * build the page disable div
 */
function buildDisableDiv()
{
	var screenDiv = UTL.getElem( "ScreenDiv" );
	var d = screenDiv.appendChild( document.createElement( "div" ) );	
	d.style.position = "absolute";	
	d.style.left = 0;	
	d.style.top = 0;
	d.style.width = screenDiv.offsetWidth; 		
	d.style.height = screenDiv.offsetHeight;
	d.style.zIndex = 1;
	d.style.display = "none";
	d.style.background = "black";
	d.style.filter = "alpha(opacity=20)";
	
	return d;	   
}


/**
 * build the "processing" div
 */
function buildProcessingDiv()
{
	var screenDiv = UTL.getElem( "ScreenDiv" );
	var d = screenDiv.appendChild( document.createElement( "div" ) );
	d.style.position = "absolute";
	
	var width = 200;
	var height = 50;
	
	d.style.width = width;
	d.style.height = height
		
	d.style.left = ( screenDiv.offsetWidth - width ) / 2;	
	d.style.top = ( screenDiv.offsetHeight - height ) / 2;
	
	d.style.zIndex = 4;
	d.style.paddingTop = 10;
	d.style.textAlign = "center";
	d.style.display = "none";	
	d.style.border = "2px solid black";
	d.style.background = "white";
	d.style.fontSize = "14px";
	d.style.fontStyle = "italic";
	d.innerHTML = "Processing ...";
	
	return d;
}


/**
 * display the disabler div
 */
function displayDisabler()
{
	_disableDiv.style.display = "block";
	
	// rather than re-drawing the disableDiv to cover the whole browser 
	// screen (whose size may vary), we just have it cover the screenDiv 
	// and make the rest of the document background a matching color 
	document.body.style.backgroundColor = "#BCBABE";	
}


/**
 * remove disabler div
 */
function hideDisabler()
{
	document.body.style.backgroundColor = _desktopColor;
	_disableDiv.style.display = "none";
}


/**
 * disables the screen and displays "processing" msg 
 */
function displayProcessing()
{
	displayDisabler();
	_processingDiv.style.display = "block";
}


/**
 * re-enables the screen and hides the "processing" msg 
 */
function hideProcessing( popupOpen )
{
	if ( !popupOpen )
	{
		hideDisabler();
	}
	_processingDiv.style.display = "none";
}


function clickHandler_closeBtn()
{
	UTL.getElem( "btnConfirmDlg" ).click();
}


/**
 * returns true/false depending on whether updates have been done
 */
function getUpdateStatus()
{	
	return _updatesMade;	
}