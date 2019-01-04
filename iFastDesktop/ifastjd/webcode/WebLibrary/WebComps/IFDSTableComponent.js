/** 
 * @fileoverview Contains source for FormFlag class, used for adding "flags" for form fields for
 * errors or warnings, etc.
 * <br/>
 * REQUIRES: JSLib: {Err.js, WebTools.js, EvtHandler.js, UTL.js}  
 *  
 * @author walkerro
 * @version 0.1 
 */

var IFDSTableManager = new function()
{
	/**
	 * Maps between Table elements and the corresponding IFDSTable objects, using the
	 * table ids as the key
	 * @type Object
	 */
	this.tableMap = {};
	
	/**
	 * Static method that gets attached to the page onload event. Looks thru the page and identifies
	 * all the html tables that are to become IFDSTables (ie. have ifdsTable = "true" attribute)
	 */
	this.loadTables = function()
	{		
		var tableElementArray = UTL.getElem("table", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME);
						
		for ( var i = 0; i < tableElementArray.length; i++ )
		{
			var TABLE = tableElementArray[i];
			if ( TABLE.getAttribute( "ifdsTable" ) == "true" )
			{
				if( TABLE.id || TABLE.id.length > 0 )
				{
					IFDSTableManager.tableMap[TABLE.id] = new IFDSTable( TABLE );				
				}
				else
				{
					throw new Error( Err.genErrMsg( "Table does not have an id", "loadTables()", "IFDSTableComponent.js" ) );
				}													
			}	
		}	
	}
}

// *** Adding the IFDSTable.load method to the onload event listener
// NOTE: this line must come after the IFDSTableManager.loadTables function definition
EvtHandler.add( window, "load", IFDSTableManager.loadTables );



/**  
 * @class Represents an IFDSTable - html table with sorting and resizing functionality.
 * Note: All functionality is added based on the THEAD of the tableElem. 
 * @param {DOMElement} tableElem reference to a table element 
 */
function IFDSTable( TABLE )
{
    this.init( TABLE );
}	


IFDSTable.prototype.init = function( TABLE )
{
    var initSortCol = null
	// all work is done within the THEAD of the table
	if ( TABLE.firstChild.nodeName.toUpperCase() == "THEAD" )
	{
		this._TABLE = TABLE;
		
		// _colMap is object index by column number, referencing the TH elements and resizeHandles
		this._colMap = {};
								
		var thead = TABLE.firstChild;
		var TH_array = thead.firstChild.childNodes;		
		for ( var i = 0; i < TH_array.length; i++ )
		{						
			this._colMap[i] = {};
			this._colMap[i].TH = TH_array[i];			
			
			// add an index attribute to the TH
			TH_array[i].setAttribute( "_colIndex", i );
						 		
			if ( TH_array[i].getAttribute( "sortable" ) && TH_array[i].getAttribute( "sortable" ).toLowerCase() == "true" )
			{				
				IFDSTable.setupSorting( TH_array[i] );
			}
			
			// note: don't allow the last col to be resizable
			if ( TH_array[i].getAttribute( "resizable" ) && TH_array[i].getAttribute( "resizable" ).toLowerCase() == "true" && i < TH_array.length - 1 )
			{
				// resizing requires the tableLayout to be fixed
				TABLE.style.tableLayout = "fixed";
				IFDSTable.setupResizing( TH_array[i] );
			}
			
			if ( TH_array[i].getAttribute( "initialSorted" ) && TH_array[i].getAttribute( "initialSorted" ).toLowerCase() == "true" )
			{
			    initSortCol = TH_array[i];
			}
		}
	}
	
	if ( TABLE.getAttribute( "rowSelectable") && TABLE.getAttribute( "rowSelectable" ).toLowerCase() == "true" )
	{
		// add event handler for focusing on table
		EvtHandler.add( TABLE, "focus", IFDSTable.focusHandler );		
		
		this._selectedRowClass = TABLE.getAttribute( "selectedRowClass" );
		this._rowOrigClass = null;
		
		this._selectedRow = null;
		
		var tbody = TABLE.lastChild;
		var TR_array = tbody.childNodes;
		for ( var i = 0; i < TR_array.length; i++ )
		{
			TR_array[i].setAttribute( "_rowIndex", i );
			EvtHandler.add( TR_array[i], "click", IFDSTable.clickHandler_dataRow );			
		}					
	}
	
	if ( initSortCol )
	{
	    this.sortColumn( initSortCol );
	}	
}



/**
 * Static event handler wrapper method for initializing keyboard event
 * handling when the table is given focus
 */
IFDSTable.focusHandler = function( evt )
{	
	var TABLE = evt.currentTarget;
	var ifdsTableRef = IFDSTableManager.tableMap[TABLE.id];
	
	function keydownHandler( evt )
	{
		var keyDesc = KeyMap.getKeyDesc( evt.keyCode, KeyMap.KEYUP );
		if ( keyDesc == KeyMap.UP )
		{
			ifdsTableRef.selectPrevRow();
			evt.preventDefault();
		}
		if ( keyDesc == KeyMap.DOWN )
		{
			ifdsTableRef.selectNextRow();
			evt.preventDefault();
		}
	}
	
	function blurHandler()
	{		
		EvtHandler.remove( document.body, "keydown", keydownHandler );
		EvtHandler.remove( TABLE, "blur", blurHandler );
	}
		
	// turn on keydown handler for this table	
	EvtHandler.add( document.body, "keydown", keydownHandler );
	// set a blur event handler, which removes the keydown handler when the table loses focus
	EvtHandler.add( TABLE, "blur", blurHandler)	
}



/**
 * Static event handler wrapper method for handling click event on a table row,
 * which causes the row to be selected, and the table to gain focus
 */
IFDSTable.clickHandler_dataRow = function( evt )
{	
	var TR = evt.currentTarget;
	var TABLE = TR.parentNode.parentNode;
	
	// explicitly give the table focus, since is not done automatically
	TABLE.focus();
	
	var ifdsTableRef = IFDSTableManager.tableMap[TABLE.id];
	ifdsTableRef.selectRow( TR );	
}


/**
 * Set the specified table row (TR element) as the selected row - resets the 
 * currently selectedRow class, and updates the class of the TR to the 
 * selectedRowClass (storing record of the original class)  
 * @param {DOMElement} TR reference to the table row to be selected 
 */
IFDSTable.prototype.selectRow = function( TR )
{		
	if ( this._selectedRow )
	{
		this._selectedRow.className = this._rowOrigClass;	
	}
	
	this._rowOrigClass = TR.className;
	TR.className = this._selectedRowClass;
	this._selectedRow = TR;
}



/**
 * Sets the row following (if any) the current selectedRow as the selectedRow, if
 * none currently selected, the first table row is selected 
 */
IFDSTable.prototype.selectNextRow = function()
{	
	if ( this._selectedRow && this._selectedRow.nextSibling )
	{
		this.selectRow( this._selectedRow.nextSibling );
	}
	else if( !this._selectedRow )
	{
		this.selectRow( this._TABLE.lastChild.firstChild );
	}
}



/**
 * Sets the row preceding (if any) the current selectedRow as the selectedRow, if
 * none currently selected, the first table row is selected 
 */
IFDSTable.prototype.selectPrevRow = function()
{
	if ( this._selectedRow && this._selectedRow.previousSibling )
	{
		this.selectRow( this._selectedRow.previousSibling );
	}
	else if( !this._selectedRow )
	{
		this.selectRow( this._TABLE.lastChild.firstChild );
	}
}



/**
 * Returns reference to the currently selected row
 * @return {DOMReference} 
 */
IFDSTable.prototype.getSelectedRow = function()
{
	return this._selectedRow;
}


/**
 * Static event handler wrapper method for calling sortColumn() after a click event
 * occurs on the column header (TH element)
 */
IFDSTable.clickHandler_columnHeader = function( evt )
{	
	var TH = evt.currentTarget;
	// get the ifdsTableRef from the table element - need to move up the DOM from the TH
	var table = TH.parentNode.parentNode.parentNode;		
	var ifdsTableRef = IFDSTableManager.tableMap[table.id];		
	ifdsTableRef.sortColumn( TH );			
}


/**
 * Static event handler wrapper method for calling resizeColumn after a mousedown
 * event occurs on a resizeHandle 
 */ 
IFDSTable.mousedownHandler_resizeHandle = function( evt )
{	
	var resizeHandle = evt.currentTarget;
	
	// using the id of the resizeHandle, and a bit of work, we get a reference to the
	// ifdsTable and TH which the resizeHandle is associated with
	var temp = resizeHandle.id.split( "#" );	
	var ifdsTableRef = IFDSTableManager.tableMap[temp[1]];		
	var TH = ifdsTableRef._colMap[temp[2]].TH;
		
	ifdsTableRef.resizeColumn( evt, TH, resizeHandle );	
	
	evt.preventDefault();
	evt.stopPropagation();
}



/**
 * Static wrapper method used when setting up resizing functionality on a table column
 * @param {DOMElement} TH reference to the colHeader for the column that is to be resizable 
 */ 
IFDSTable.setupResizing = function( TH )
{	
	var defaultHandleWidth = 3;
	
	var div = document.createElement( "div" );
	div.id = "resizeHandle#" + TH.parentNode.parentNode.parentNode.id + "#" + TH.getAttribute( "_colIndex" ); 		
		
	div.style.width = defaultHandleWidth;
	// height spans the column header height	
	div.style.height = TH.offsetHeight;
	
	div.style.position = "absolute";	
	var TH_absPos = WebTools.findElemPos( TH );
	// positioned at the top and right of the TH - regardless of border, padding, etc.		
	div.style.top = TH_absPos.top;	
	div.style.left = TH_absPos.left + TH.offsetWidth - parseInt( div.style.width )
	
	div.style.background = "red";
	div.style.filter = "alpha(opacity=0)";
	div.style.MozOpacity = 0;
	div.style.cursor = "col-resize";	
	div.style.zIndex = 1000;
			
	document.body.appendChild( div );
	TH.setAttribute( "_resizeHandle", div );
	if( div.offsetParent != TH )
	{
		TH.style.position = "relative";
	}
	
	// add mousedown event handler to the resizeHandle
	EvtHandler.add( div, "mousedown", IFDSTable.mousedownHandler_resizeHandle );
	 		
}


/**
 * HTML stingfor the unsorted tag added to the column header of a sortable column 
 */ 
IFDSTable.unsortedTag = "<span name='sortTag' style='font-size:12'>&nbsp;&loz;&nbsp;</span>";
/**
 * HTML string for the unsorted tag added to the column header of a sortable column 
 */
IFDSTable.descendingTag = "<span name='sortTag' style='font-size:14'>&nbsp;&darr;&nbsp;</span>";
/**
 * HTML string for the unsorted tag added to the column header of a sortable column 
 */
IFDSTable.ascendingTag = "<span name='sortTag' style='font-size:14'>&nbsp;&uarr;&nbsp;</span>";



/**
 * Static method used when setting up sorting functionality on a table column
 * @param {DOMElement} TH reference to the colHeader for the column that is to be sortable 
 */ 
IFDSTable.setupSorting = function( TH )
{	
	// added unsorted tag to the TH html
	TH.innerHTML = IFDSTable.unsortedTag + TH.innerHTML;
	// add attribute to the TH indicated sort direction	
	TH.setAttribute( "_sortDir", "unsorted" );
	
	// add event handler to the TH
	EvtHandler.add( TH, "click", IFDSTable.clickHandler_columnHeader );
}


/**
 * Static method used when updating the sorting indicator of a colHeader (TH)
 * @param {DOMElement} TH reference to the colHeader that was just used in resorting the table
 * @param {string} sortDir indicates the direction the indicator should now show 
 */
IFDSTable.setSortDir = function( TH, sortDir )
{
	//remove "sort tag" from html
	var sortTag = null;
	for ( var i = 0; i < TH.childNodes.length; i++ )
	{		
		if( TH.childNodes[i].nodeName.toLowerCase() == "span" && TH.childNodes[i].getAttribute( "name" ) == "sortTag" )
		{		
			sortTag = TH.childNodes[i];
		}
	}
	if ( sortTag == null )
	{
		throw new Error( Err.genErrMsg( "Sort tag not found", "setSortDir()", "IFDSTableComponent.js" ) );
	}
	TH.removeChild( sortTag );
	
	// set the new inner html for the TH	
	var html = TH.innerHTML;	 
	
	switch( sortDir )
	{
		case "unsorted":
		{
			html = IFDSTable.unsortedTag + html;			
			break;
		} 
		case "ascending":
		{
			html = IFDSTable.ascendingTag + html;
			break;			
		}
		case "descending":
		{
			html = IFDSTable.descendingTag + html;
			break;
		}
		default:
		{
			throw new Error( Err.genErrMsg( "unknown sort direction", "setSortDir()", "IFDSTableComponnent.js" ) );
		}
	}
	TH.innerHTML = html;
	
	// update the sortDir attribute of the TH
	TH.setAttribute( "_sortDir", sortDir );	
}


/**
 * Sort the column for which the TH is the column header. The data will be sorted in ascending order,
 * unless it is already in this direction. Also, if the dataType attribute is set on the TH to one of
 * the predefined types, this will be used to more accurately sort the data. 
 * @param {DOMElement} TH reference to the colHeader that is to be used in resorting the table 
 */
IFDSTable.prototype.sortColumn = function( TH )
{	
	var TABLE = TH.parentNode.parentNode.parentNode;

	var colIndex = TH.getAttribute( "_colIndex" );
	
	// get sortTag from the colHeader, or create one if not found
	var curSortDir = TH.getAttribute( "_sortDir" );
				
	// iterate thru the table rows and store the row objects in an array that will be sorted				
	var rows = TABLE.lastChild.childNodes;
	var rowCount = rows.length;	
	var tableDataArray = new Array( rows.length );	 	 	 
	for ( var r = 0; r < rowCount; r++ )
	{
		var colToBeSortedContents = rows[r].childNodes[colIndex].innerHTML;
		
		tableDataArray[r] = { sortVal: 	colToBeSortedContents, 
							  rowObj: 	rows[r],
							  selected: this._selectedRow == rows[r] };
	}
	
	// sort - using dataType, if given
	// retrieve the compare function to to be used in the sort	
	// only make descending if column is currently sorted ascending
	var makeDescending = ( curSortDir == "ascending" );
	var comp = UTL.getCompareFn(TH.getAttribute( "dataType" ), makeDescending);	
	tableDataArray.sort( function( item1, item2 ){ return comp( item1.sortVal, item2.sortVal ) } );
	
	// empty out the current rows, before adding in the sorted rows
	for( var r = r; r < rowCount; r++ )
	{
		TABLE.lastChild.removeChild( TABLE.lastChild.lastChild );
	}
		
	// put sorted rows into the table	
	var indexOfRowToBeSelected = null;
	for ( var r = 0; r < rows.length; r++ )
	{		
		TABLE.lastChild.appendChild( tableDataArray[r].rowObj );
		
		// check for selectedRow, and remember its index
		if ( tableDataArray[r].selected )
		{
			indexOfRowToBeSelected = r;
		}
	}
	
	// re-select a row, if applicable
	if ( indexOfRowToBeSelected )
	{
		this.selectRow( TABLE.lastChild.childNodes[indexOfRowToBeSelected] );
	}
	
	// reset the sorting in all the column headers that are sortable
	var TH_array = TH.parentNode.childNodes;
	for ( var i = 0; i < TH_array.length; i++ )
	{
		if ( TH_array[i].getAttribute( "sortable" ) )
		{
			IFDSTable.setSortDir( TH_array[i], "unsorted" );			
		}
	}
	
	// update the sortedTag for the newly sorted column
	if ( makeDescending )
	{
		IFDSTable.setSortDir( TH, "descending" );
	}
	else
	{
		IFDSTable.setSortDir( TH, "ascending" );		
	}			
}

/**
 * Method for resizing a column in the table
 * @param {eventObject} evt  the mousedown event that is used to kick off the resizing
 * @param {DOMElement} TH reference to the colHeader that is to be resized within the table 
 */
IFDSTable.prototype.resizeColumn = function( evtObj, TH, resizeHandle )
{	
	var MIN_WIDTH = 10;
	
	var prevCursor = document.body.style.cursor;
	document.body.style.cursor = "col-resize";
	
	// the mouse position in window (not page) co-ordinates, at which the resize begins
	var startX = parseInt( evtObj.clientX );
	
	// reference to the right adjacent column header - we are assured one exists,
	// since end columns cannot be made resizable
	var adjTH = TH.nextSibling;
	
	// store some initial details of width and position for the TH, and adjTH
	var TH_origWidth = parseInt( TH.style.width );
	var TH_X = WebTools.findElemPos( TH ).left;	
	
	var adjTH_origWidth = parseInt( adjTH.style.width );
	var adjTH_X = WebTools.findElemPos( adjTH ).left;

	// NOTE: we don't use EvtHandler here, because doesn't handle event 'capturing' (blame IE)	
	if ( document.addEventListener )
	{
		document.addEventListener( "mousemove", moveHandler, true );
		document.addEventListener( "mouseup", upHandler, true );
	}
	else if ( document.attachEvent )
	{
		document.body.setCapture();
		document.body.attachEvent( "onmousemove", moveHandler );
		document.body.attachEvent( "onmouseup", upHandler );
		document.body.attachEvent( "onlosecapture", upHandler );			
	}
	else
	{
		throw new Error( Err.genErrMsg( "browser event handling not supported", "resizeColumn()", "IFDSTableComponent.js" ) );
	}	
	
	if ( evtObj.stopPropagation ) evtObj.stopPropagation();		
	else evtObj.cancelBubble = true;
		
	if ( evtObj.preventDefault ) evtObj.preventDefault();
	else evtObj.returnValue = false;
	
	
	// handler function that gets attached to mouse move event
	function moveHandler( e )
	{
		if ( !e ) e = window.event;
		
		if( ( e.clientX > TH_X + MIN_WIDTH ) && ( e.clientX < adjTH_X + adjTH_origWidth - MIN_WIDTH ) )
		{				
			var diffX = e.clientX - startX;
			
			// modify colHeader width
			TH.style.width = TH_origWidth + diffX;			
			
			// do opposite modification to nextColHeader				
			adjTH.style.width = adjTH_origWidth - diffX;
		}
		
		if ( e.stopPropagation ) e.stopPropagation();		
		else e.cancelBubble = true;																				
	}
	
	
	// handler function that gets attached on mouse up event - cancels the moveHandler
	// and does all the required updating
	function upHandler( e )
	{
		if ( !e ) e = window.event;
		
		if( document.removeEventListener )
		{
			document.removeEventListener( "mouseup", upHandler, true );
			document.removeEventListener( "mousemove", moveHandler, true );
		}
		else
		{
			document.body.detachEvent( "onlosecapture", upHandler );
			document.body.detachEvent( "onmouseup", upHandler );
			document.body.detachEvent( "onmousemove", moveHandler );
			document.body.releaseCapture();											
		}
		
		// update resizeHandle positions in the							
		resizeHandle.style.left = WebTools.findElemPos( TH ).left + TH.offsetWidth - parseInt( resizeHandle.style.width );
		
		document.body.style.cursor = prevCursor;
		
		if ( e.stopPropagation ) e.stopPropagation();		
		else e.cancelBubble = true;
	}	 							
}


