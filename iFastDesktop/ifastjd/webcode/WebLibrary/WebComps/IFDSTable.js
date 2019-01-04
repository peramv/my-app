/** 
 * @fileoverview Contains source for IFDSTable, used for adding dynamic features to static html text
 * <br/>
 * REQUIRES: JSLib/Err.js, JSLib/WebTools.js, JSLib/EvtHandler.js, JSLib/UTL.js, JSLib/KeyMap.js  
 *
 *  
 * @author walkerro 
 */
 
var IFDSTableManager = new function()
{	
	/**
	 * @private
	 */	
	var _tableMap = {};

	var _getCustomTablePosFn = null;
	
	/**
	 * Static method that gets attached to the page onload event. Looks thru the page and identifies
	 * all the html tables that are to become IFDSTables (ie. have ifdsTable = "true" attribute)
	 */
	this.init = function( getCustomTablePosFn )
	{
		_getCustomTablePosFn = getCustomTablePosFn;
		
		var tableElementArray = UTL.getElem("table", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME);
						
		for ( var i = 0; i < tableElementArray.length; i++ )
		{
			var tableElem = tableElementArray[i];
			if ( tableElem.getAttribute( "ifdsTable" ) == "true" )
			{
				if( ( tableElem.id || tableElem.id.length > 0 ) && !_tableMap[tableElem.id] )
				{
					_tableMap[tableElem.id] = new IFDSTable( tableElem, getCustomTablePosFn );				
				}
				else
				{
					throw new Error( Err.genErrMsg( "Table does not have an id, or its id is not unique", "init()", "IFDSTable.js" ) );
				}													
			}	
		}	
	}
	
	
	
	/**
	 * Returns a reference a table object associated with the given id
	 *
	 * @param {string} id
	 * @return {object}
	 */		
	this.getTable = function( id )
	{
	    return _tableMap[id];
	}



	/**
	 * Add an additional table that wasn't processed when init was called.
	 *
	 * @param {string} id
	 * @return {object}
	 */			
	this.addTable = function( id )
	{			
		if ( !_tableMap[id] )
		{
			var tableElem = UTL.getElem( id );			
			_tableMap[id] = new IFDSTable( tableElem, _getCustomTablePosFn );			
		}
		else
		{
			throw new Error( Err.genErrMsg( "Table already exists", "addTable()", "IFDSTable.js" ) );
		}
	}
	
	
	this.reInitTable = function( id )
	{
		if ( _tableMap[id] )
		{
			var rowSelectFn = null;
			var rowExecuteFn = null;
			if ( _tableMap[id]._isRowSelectable )
			{
				rowSelectFn = _tableMap[id].getOnRowSelectedFunction();				
				rowExecuteFn = _tableMap[id].getOnRowExecuteFunction();
			}
			_tableMap[id].destroy();
			_tableMap[id] = new IFDSTable( UTL.getElem( id ) , _getCustomTablePosFn );
			if ( rowSelectFn )
			{			
				_tableMap[id].setOnRowSelectedFunction( rowSelectFn );
			}
			if ( rowExecuteFn )
			{			
				_tableMap[id].setOnRowExecuteFunction( rowExecuteFn );
			}								
			return _tableMap[id];
		}
		else
		{
			throw new Error( Err.genErrMsg( "IFDSTable " + id + " does not exist" , "reInitTable()", "IFDSTable.js" ) );
		}
	}
	
	
	this.removeTable = function( id )
	{
		if ( _tableMap[id] )
		{
			_tableMap[id].destroy();
			delete _tableMap[id];
			_tableMap[id] = null;
		}
		else
		{
			throw new Error( Err.genErrMsg( "IFDSTable " + id + " does not exist" , "reInitTable()", "IFDSTable.js" ) );
		}
	}}









/**  
 * @class Represents an IFDSTable - html table (of defined format), with dynamic features added to it
 * 
 * @param {DOMElement} tableElem
 */
function IFDSTable( tableElem, getCustomTablePosFn )
{
	this._tableElem = tableElem;
		
	var getTablePosFn = ( getCustomTablePosFn != null ? getCustomTablePosFn : IFDSTable.getDefaultTablePos );
	this.getTablePos = function(){ return getTablePosFn( tableElem ) };
	
    this.init();
}



/**
 * Constant used to identify "Ascending" sorted order
 * @type string
 */
IFDSTable.SORT_ASCENDING     = "ascending";



/**
 * Constant used to identify "Descending" sorted order
 * @type string
 */
IFDSTable.SORT_DESCENDING    = "descending";



/**
 * Constant used to identify "Not sorted" sorted order
 * @type string
 */
IFDSTable.SORT_NONE			= "none";



/**
 * Constant used to identify "string" data type
 * @type string
 */
IFDSTable.DT_STRING 		= "string";



/**
 * Constant used to identify "numeric" data type
 * @type string
 */
IFDSTable.DT_NUMERIC 		= "numeric";



/**
 * Constant used to identify "date" data type
 * @type string
 */
IFDSTable.DT_DATE 			= "date";


IFDSTable.HEADER_SUFFIX	    	= "_HEADER";
IFDSTable.CELL_SUFFIX	    	= "_CELL";
IFDSTable.ROW_SUFFIX	    	= "_ROW";
IFDSTable.SELECTED_SUFFIX	    = "_SELECTED";
IFDSTable.UNSORTED_SUFFIX	    = "_UNSORTED";
IFDSTable.ASCENDING_SUFFIX	    = "_ASCENDING";
IFDSTable.DESCENDING_SUFFIX	    = "_DESCENDING";
IFDSTable.ODD_SUFFIX	  		= "_ODD";
IFDSTable.EVEN_SUFFIX	 	    = "_EVEN";



/**
 * Static function to determine the position of the given table element
 * Only useful if table is positioned absolutely.
 * 
 * @param {DOMElement} tableElem
 */
IFDSTable.getDefaultTablePos = function( tableElem )
{
    var container = tableElem.parentNode;
		
	var top = null;
	if ( !isNaN( parseInt( tableElem.style.top ) ) )
	{	
		top = parseInt( tableElem.style.top );		
	}
	else if ( !isNaN( parseInt( WebTools.getComputedStyle( tableElem, "top" ) ) ) )
	{	
		top = parseInt( WebTools.getComputedStyle( tableElem, "top" ) );
	}
	else
	{		
		throw new Error( Err.genErrMsg( "cannot determine tableElem position-top", "getTablePos()", "IFDSTable.js" ) );
	}
	 
	var left = null;
	if ( !isNaN( parseInt( tableElem.style.left ) ) )
	{
		left = parseInt( tableElem.style.left );		
	}
	else if ( !isNaN( parseInt( WebTools.getComputedStyle( tableElem, "left" ) ) ) )
	{
		left = parseInt( WebTools.getComputedStyle( tableElem, "left" ) );
	} 
	else
	{
		throw new Error( Err.genErrMsg( "cannot determine tableElem position-left", "getTablePos()", "IFDSTable.js" ) );
	}
		
	var posMap = {};
	posMap["container"] = container;
	posMap["top"] = top;
	posMap["left"] = left;
	return posMap;
}



/**
 * Static function to build the resizeHandle div for the column with the 
 * given header element  
 * 
 * @param {Object} tableRef IFDSTable
 * @param {DOMElement} headerElem Reference to the header TD of the table assoc with tableRef
 */
IFDSTable.buildResizeHandle = function( tableRef, index, headerElem, colWidth )
{
    var tablePosObj = tableRef.getTablePos();
    
    var div = tablePosObj.container.appendChild( document.createElement( "div" ) );
    div._tableId = tableRef._tableElem.id;
    div._colIndex = index;
    div.style.position = "absolute";
    div.style.top = parseInt( tablePosObj.top );
    var colOffset = colWidth;
    for ( var i = 0; i < index; i++ )
    {
    	colOffset += parseInt( tableRef._colArray[i].getWidth() );
    }    
    div.style.left = parseInt( tablePosObj.left ) + colOffset - 3;    
    div.style.width = 5;
    // table is currently visible
    if ( tableRef._tableElem.offsetHeight != 0 )
    {
    	div.style.height = tableRef._tableElem.offsetHeight;
    }
    // table is not visible, need height value to be given
   	else
   	{
   		var tableHeight = tableRef._tableElem.getAttribute( "tableHeight" );
   		if ( tableHeight )
   		{
   			div.style.height = tableHeight	
   		}
   		else
   		{
   			throw new Error( Err.genErrMsg( "tableHeight attribute is required when initializing IFDSTable for invisible table", "buildResizeHandle()", "IFDSTable.js" ) );
   		}	
   	}       
    div.style.cursor = "w-resize";
    div.style.background = "black";    
	div.style.filter = "alpha( opacity = 0 )";        
    
    var innerDiv = div.appendChild( document.createElement( "div" ) );
    innerDiv.style.position = "absolute";
    innerDiv.style.top = 0;
    innerDiv.style.left = 3;
    innerDiv.style.width = 0;
    innerDiv.style.borderLeft = "1px dashed black";
    innerDiv.style.height = "100%";    
    //innerDiv.style.filter = "alpha( opacity = 0 )";
    
    return div;
}


IFDSTable.verifyDataType = function( dataType )
{
	if ( dataType == IFDSTable.DT_STRING
		 || dataType == IFDSTable.DT_NUMERIC
		 || dataType == IFDSTable.DT_DATE )
	{
		return true;
	}
	return false;
}



/**
 * Static function for creating a row mapping after sorting the given IFDSTable_Cell array.   
 * 
 * @param {Object Array} cellArray array of IFDSTable_Cell objects
 * @param {string} sortDir direction cellArray should be sorted, to determine row mapping
 */
IFDSTable.createSortedRowMap = function( cellArray, sortDir, dataType )
{
    var dataMap = new Array( cellArray.length );
    for ( var i = 0; i < cellArray.length; i++ )
    {
        dataMap[i] = { index:i, data:cellArray[i].getData() }; 
    }
    
    var compareType = null;
    switch( dataType )
    {
    	case IFDSTable.DT_STRING:
    	{
    		compareType = UTL.COMPARE_STRING;
    		break;
    	}
    	case IFDSTable.DT_NUMERIC:
    	{
    		compareType = UTL.COMPARE_NUMERIC;
    		break;
    	}
    	case IFDSTable.DT_DATE:
    	{
    		compareType = UTL.COMPARE_DATE;
    		break;
    	}
    }
           
    var compFn = UTL.getCompareFn( compareType, ( sortDir == IFDSTable.SORT_DESCENDING ) );
    dataMap.sort( function( dataMapElem1, dataMapElem2 ){ return compFn( dataMapElem1.data, dataMapElem2.data ) } );
    
    var rowMap = new Array( cellArray.length );
    for( var i = 0; i< cellArray.length; i++ )
    {
        rowMap[i] = dataMap[i].index;
    }
        
    return rowMap;    
}



/**
 * EVENT HANDLER
 */
IFDSTable.clickHandler_tableRow = function( evt )
{	
	var trElem = evt.currentTarget;
	var tableRef = IFDSTableManager.getTable( trElem.parentNode.parentNode.id );
	
	var rowIndex = trElem.getAttribute( "_rowIndex" );
		
	var scrollTop = tableRef.setSelectedRowIndex( rowIndex );
	tableRef._tableElem.focus();
	tableRef._tableElem.parentNode.scrollTop = scrollTop;		
	
	evt.stopPropagation();	
}



/**
 * EVENT HANDLER - Static event handler wrapper method for initializing keyboard event
 * handling when the table is given focus
 */
IFDSTable.focusHandler = function( evt )
{			
	var TABLE = evt.currentTarget;	
	var ifdsTableRef = IFDSTableManager.getTable( TABLE.id );
	
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
		if ( keyDesc == KeyMap.ENTER )
		{			
			if ( ifdsTableRef._onRowExecuteFunction )
			{
				ifdsTableRef._onRowExecuteFunction();	
			}
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
	EvtHandler.add( TABLE, "blur", blurHandler )
	
	evt.preventDefault();	
}



/**  
 * Initializes all the aspects of this IFDSTable object, based on the html table ref given.
 * Will throw errors if table doesn't have required structure.
 * <br/>
 * required structure: table - thead - tr - td(s), - tbody - tr(s) - td(s) 
 */
IFDSTable.prototype.init = function()
{
    var tableRef = this;            
        
    this._colArray = [];    
    var tableElem = this._tableElem;
    
    this._baseClassName = tableElem.baseClassName;
    
    WebTools.appendCSSClassName( tableElem, this._baseClassName );
            
    this._isRowSelectable = ( tableElem.getAttribute( "rowSelectable" ) && tableElem.getAttribute( "rowSelectable" ) == "true" ? true : false );
    
    if ( this._isRowSelectable )
    {    	    
    	this._selectedRowIndex = null;    		
    }
    
    var isResizable = ( tableElem.getAttribute( "resizable" ) && tableElem.getAttribute( "resizable" ) == "true" ? true : false );    
    
    var theadElem = tableElem.firstChild       
    if ( theadElem.nodeName.toUpperCase() == "THEAD" )
    {
        var theadTrElem = theadElem.firstChild;
        if ( theadTrElem.nodeName.toUpperCase() == "TR" )
        {        
            var firstTdElem = theadTrElem.firstChild;    
            if ( firstTdElem.nodeName.toUpperCase() == "TD" )
            {
                for ( var c = 0; c < theadTrElem.childNodes.length; c++ )
                {                    
                    var theadTdElem = theadTrElem.childNodes[c];                    
                    theadTdElem.setAttribute( "_columnIndex", c );
                    
                    var sortable = ( theadTdElem.getAttribute( "sortable" ) && theadTdElem.getAttribute( "sortable" ) == "true" ? true : false );
                    var sortableDataType = ( theadTdElem.getAttribute( "dataType" ) ? theadTdElem.getAttribute( "dataType" ) : IFDSTable.DT_STRING );
                    if ( sortable && !IFDSTable.verifyDataType( sortableDataType ) )
                    {
                    	throw new Error( Err.genErrMsg( "unknown data type specified for sorting", "init()", "IFDSTable.js" ) ); 
                    }
                    
                    if ( isResizable )
                    {
                    	var colWidth = theadTdElem.getAttribute( "columnWidth" );
                    	if ( colWidth )
                    	{
                    		theadTdElem.style.width = colWidth;
                    	}
                    	else
                    	{
                    		throw new Error( Err.genErrMsg( "columnWidth attribute required on headers when table is resizable", "init()", "IFDSTable.js" ) );
                    	}
                    }
                    // note: we don't add resize functionality to the last column                                        
                    this._colArray[c] = new IFDSTable_Column( this, theadTdElem, c, isResizable && c < theadTrElem.childNodes.length - 1, sortable, sortableDataType );                    
                }
            }
            else
            {
                throw new Error( Err.genErrMsg( "table is missing THEAD-TR-TD nodes", "init()", "IFDSTable.js" ) );
            }    
        }
        else
        {
            throw new Error( Err.genErrMsg( "table is missing THEAD-TR node", "init()", "IFDSTable.js" ) );
        }       
    }
    else
    {
        throw new Error( Err.genErrMsg( "table is missing THEAD node", "init()", "IFDSTable.js" ) );
    }
    
    if ( this._isRowSelectable )
    {
    	EvtHandler.add( tableElem, "focus", IFDSTable.focusHandler );
    }
    
        
    if ( tableElem.lastChild.nodeName.toUpperCase() == "TBODY" )
    {    	
        var tbodyElem = tableElem.lastChild;           
        for( var r = 0; r < tbodyElem.childNodes.length; r++ )
        {        	
            var tbodyTrElem = tbodyElem.childNodes[r];
            tbodyTrElem.setAttribute( "_rowIndex", r );
            if ( r % 2 == 0)
            {
            	WebTools.appendCSSClassName( tbodyTrElem, this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.EVEN_SUFFIX );
            }
            else
            {
        		WebTools.appendCSSClassName( tbodyTrElem, this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.ODD_SUFFIX );
            }
            
            if ( this._isRowSelectable )
            {
            	EvtHandler.add( tbodyTrElem, "click", IFDSTable.clickHandler_tableRow );            	
            }
            
            for ( var c = 0; c < tbodyTrElem.childNodes.length; c++ )
            {            	
                var tbodyTdElem = tbodyTrElem.childNodes[c];                               
                WebTools.appendCSSClassName( tbodyTdElem, this._baseClassName + IFDSTable.CELL_SUFFIX );
                var cellObj = new IFDSTable_Cell( tbodyTdElem );                                            
                this._colArray[c].setCell( r, cellObj );
            }
        }
    }
    else
    {
        throw new Error( Err.genErrMsg( "table is missing TBODY node", "init()", "IFDSTable.js" ) );
    }
    
        
    this._isScrollable = ( this._tableElem.getAttribute( "scrollable" ) && this._tableElem.getAttribute( "scrollable" ) == "true" ? true : false );
    if ( this._isScrollable )
    {
        var parentElem = this._tableElem.parentNode;
        parentElem.style.overflowY = "scroll";
        parentElem.onscroll = function(){ tableRef.scrollHandler() };
    }   
}



IFDSTable.prototype.destroy = function()
{
	if ( this._isRowSelectable )
	{
		EvtHandler.remove( this._tableElem, "focus", IFDSTable.focusHandler );		
	}
	
	if ( this._isRowSelectable )
	{
		var rowArray = this._tableElem.lastChild.childNodes;
		for ( var r = 0; r < rowArray.length; r++ )
		{
			EvtHandler.remove( rowArray[r], "click", IFDSTable.clickHandler_tableRow );
		}
	}
		
    if ( this._isScrollable )
    {
        var parentElem = this._tableElem.parentNode;        
        parentElem.onscroll = null;
    }
    
    for ( var c = this._colArray.length - 1; c >= 0; c-- )
    {
    	this._colArray[c].destroy();
    	delete this._colArray[c];
    	this._colArray[c] = null;
    }
    
    this._tableElem = null;
    this.getTablePos = null;
    this._baseClassName = null;
    this._isRowSelectable = null;    
    this._selectedRowIndex = null;
    this._isScrollable = null;
}



/**  
 * Event Handler - scroll handler, keeps the table header stationary when scrolliing 
 */
IFDSTable.prototype.scrollHandler = function()
{
	var tableElem = this._tableElem;
	var parentElem = tableElem.parentNode;
			
	tableElem.firstChild.firstChild.style.position = "relative";
	tableElem.firstChild.firstChild.style.zIndex = 1000;	
	tableElem.firstChild.firstChild.style.top = parentElem.scrollTop;	
}



/**  
 * Sorts the table by the given column index
 * 
 * @param {number} colIndex 
 */
IFDSTable.prototype.sort = function( colIndex )
{	
    var colObjToSortBy = this._colArray[colIndex];
    if ( colObjToSortBy.isSortable() )
    {
        var cellArray = colObjToSortBy.getCellArray();       
        var newSortDir = ( colObjToSortBy.getSortDir() == IFDSTable.SORT_ASCENDING ? IFDSTable.SORT_DESCENDING : IFDSTable.SORT_ASCENDING );
        var dataType = colObjToSortBy.getDataType();
        var sortedRowMap = IFDSTable.createSortedRowMap( cellArray, newSortDir, dataType );
        
        for ( var c = 0; c < this._colArray.length; c++ )
        {
            var colObj = this._colArray[c];
            colObj.setSortDir( IFDSTable.SORT_NONE );
        
            // clone the cell array    
            var origCellArray = colObj.getCellArray();
            var cloneCellArray = new Array( origCellArray.length );
            for ( var r = 0; r < origCellArray.length; r++ )
            {
                cloneCellArray[r] = origCellArray[r];                
            }
            
           
            // reorganize the cells in the column, and update the TDs in the TABLE
            for ( var r = 0; r < sortedRowMap.length; r++ )
            {
                var cellObj = cloneCellArray[sortedRowMap[r]];
                colObj.setCell( r, cellObj );
                                
                var tdElem = WebTools.getTableCell( this._tableElem, r, c );
                                
                // clear out the tdElem of its child nodes
                while( tdElem.lastChild )
                {
                	tdElem.removeChild( tdElem.lastChild );
                }
                
                tdElem.setAttribute( "data", cellObj.getData() );
				
				var newTDChildNodes = cellObj.getContents();
				                
                for ( var i = 0; i < newTDChildNodes.length; i++ )
                {
                	tdElem.appendChild( newTDChildNodes[i] );
                } 
            } 
        }
        
        colObjToSortBy.setSortDir( newSortDir )
    }
    else
    {
        throw new Error( Err.genErrMsg( "column " + colIndex + " is not sortable", "sort()", "IFDSTable.js" ) );
    }    
}


IFDSTable.prototype.setOnRowSelectedFunction = function( fn )
{	
	this._onRowSelectedFunction = fn;	
}


IFDSTable.prototype.getOnRowSelectedFunction = function()
{
	return this._onRowSelectedFunction;	
}

IFDSTable.prototype.setOnRowExecuteFunction = function( fn )
{	
	this._onRowExecuteFunction = fn;	
}

IFDSTable.prototype.getOnRowExecuteFunction = function( fn )
{	
	return this._onRowExecuteFunction;	
}


IFDSTable.prototype.clearSelectedRowIndex = function()
{		
	if ( this._selectedRowIndex != null )
	{		
		var oldSelectedRowIndex = this._selectedRowIndex;
		var oldSelectedTr = WebTools.getTableRow( this._tableElem, oldSelectedRowIndex );
		 
		if ( oldSelectedRowIndex % 2 == 0 )
		{
			WebTools.replaceCSSClassName( oldSelectedTr, 
		                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.SELECTED_SUFFIX,
		                              	  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.EVEN_SUFFIX );
		}
		else
		{
			WebTools.replaceCSSClassName( oldSelectedTr, 
		                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.SELECTED_SUFFIX,
		                              	  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.ODD_SUFFIX );
		}
	}	
	this._selectedRowIndex = null;
}


IFDSTable.prototype.setSelectedRowIndex = function( rowIndex )
{	
	if ( this._selectedRowIndex != null )
	{
		var oldSelectedRowIndex = this._selectedRowIndex;
		var oldSelectedTr = WebTools.getTableRow( this._tableElem, oldSelectedRowIndex );
		 
		if ( oldSelectedRowIndex % 2 == 0 )
		{
			WebTools.replaceCSSClassName( oldSelectedTr, 
		                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.SELECTED_SUFFIX,
		                              	  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.EVEN_SUFFIX );
		}
		else
		{
			WebTools.replaceCSSClassName( oldSelectedTr, 
		                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.SELECTED_SUFFIX,
		                              	  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.ODD_SUFFIX );
		}
	}
	
	this._selectedRowIndex = rowIndex;
	var trElem = WebTools.getTableRow( this._tableElem, rowIndex );
	this._selectedRowPrevStyleClass = trElem.className;
	
	if ( rowIndex % 2 == 0 )
	{
		WebTools.replaceCSSClassName( trElem,  
	                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.EVEN_SUFFIX,
	                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.SELECTED_SUFFIX );
	}
	else
	{
		WebTools.replaceCSSClassName( trElem,  
	                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.ODD_SUFFIX,
	                                  this._baseClassName + IFDSTable.ROW_SUFFIX + IFDSTable.SELECTED_SUFFIX );
	}
	
	if ( this._onRowSelectedFunction )
	{			
		this._onRowSelectedFunction( rowIndex );
	}
	
	if ( this._isScrollable )
	{
		return this.scrollIntoView( trElem );
	}
}



IFDSTable.prototype.scrollIntoView = function( tableRow )
{		
	var outerDiv = this._tableElem.parentNode;
	//window.status = outerDiv.scrollTop;
	var headerHeight = this._tableElem.firstChild.offsetHeight;
	
	//window.status = "outerDiv.scrollTop:" + outerDiv.scrollTop + ", tableRow.top:" + tableRow.offsetTop;
				
	// scroll up				
	if ( tableRow.offsetTop + tableRow.offsetHeight > outerDiv.scrollTop + outerDiv.offsetHeight )
	{		
		//window.status = "DOWN: outerDiv.scrollTop + outerDiv.offsetHeight=" + outerDiv.scrollTop + " + " + outerDiv.offsetHeight + ", tableRow.top + tableRow.offsetHeight=" + tableRow.offsetTop + " + " + tableRow.offsetHeight;
		outerDiv.scrollTop = ( tableRow.offsetTop + tableRow.offsetHeight ) - outerDiv.offsetHeight;		
	}
	// scroll down
	else if ( tableRow.offsetTop < ( outerDiv.scrollTop + headerHeight ) )
	{			
		//window.status = "UP: outerDiv.scrollTop:" + outerDiv.scrollTop + ", tableRow.top:" + tableRow.offsetTop;		
		outerDiv.scrollTop = tableRow.offsetTop	- headerHeight;		
	}
	
	return outerDiv.scrollTop;				
}



IFDSTable.prototype.getSelectedRowIndex = function()
{
	return this._selectedRowIndex;
}


IFDSTable.prototype.selectNextRow = function()
{
	if ( this._selectedRowIndex != null )
	{
		var nextRowIndex = this._selectedRowIndex + 1;
		if ( nextRowIndex < this._tableElem.lastChild.childNodes.length )
		{
			this.setSelectedRowIndex( nextRowIndex );
		}
	}
}


IFDSTable.prototype.selectPrevRow = function()
{
	if ( this._selectedRowIndex != null )
	{
		var prevRowIndex = this._selectedRowIndex - 1;
		if ( prevRowIndex >= 0 )
		{
			this.setSelectedRowIndex( prevRowIndex );
		}
	}
}


IFDSTable.prototype.getCell = function( row, col )
{
	return this._colArray[col].getCell( row ); 
}


IFDSTable.prototype.getNumRows = function()
{
	// last child = TBODY, childNodes = rows array
	return this._tableElem.lastChild.childNodes.length;
}


IFDSTable.prototype.getNumCols = function()
{
	return this._colArray.length;
}













/**  
 * @class Represents an IFDSTable_Column - component object of IFDSTable instance
 * 
 * @param {object} tableRef IFDSTable instance
 * @param {DOMElement} headerElem TD element that is the header of this column
 * @param {number} index column index
 * @param {boolean} sortable if column is sortable
 * @param {boolean} resizable if column is resizable
 */
function IFDSTable_Column( tableRef, headerElem, index, resizable, sortable, dataType )
{   
    this._tableRef = tableRef;
    this._headerElem = headerElem;
    this._baseStyleClass = headerElem.getAttribute( "baseClassName" );
    this._index = index;        
    this._cellArray = [];       
    this._resizeHandle = null;
    this._width = parseInt( headerElem.columnWidth );
    this._sortDir = null;
    this._isSortable = sortable;
    this._dataType = null;
    
    headerElem._columnIndex = index;
    
    WebTools.appendCSSClassName( headerElem, tableRef._baseClassName + IFDSTable.HEADER_SUFFIX );
               
    var columnRef = this;
    if ( sortable )
    {
        EvtHandler.add( headerElem, "click", IFDSTable_Column.clickHandler_headerElem );
        this.setSortDir( IFDSTable.SORT_NONE );
        this._dataType = dataType;   
    }    
    
    if ( resizable )
    {        
        var resizeHandle = IFDSTable.buildResizeHandle( this._tableRef, index, headerElem, this._width );
        EvtHandler.add( resizeHandle, "mousedown", IFDSTable_Column.mousedownHandler_resizeHandle );
        this._resizeHandle = resizeHandle;    
    }    
}



/**  
 * EVENT HANDLER - click handler for the header element. Only if column is sortable 
 */
IFDSTable_Column.clickHandler_headerElem = function( evt )
{
	var headerElem = evt.currentTarget;
	var tableElem = headerElem.parentNode.parentNode.parentNode;
	var tableRef = IFDSTableManager.getTable( tableElem.id );
	
	var columnIndex = parseInt( headerElem._columnIndex );
	    
    tableRef.sort( columnIndex );        
}



/**  
 * EVENT HANDLER - mousedown handler for the resize handler 
 */
IFDSTable_Column.mousedownHandler_resizeHandle = function( evt )
{
	var resizeHandle = evt.currentTarget;
	var tableRef = IFDSTableManager.getTable( resizeHandle._tableId )
	var columnRef = tableRef._colArray[resizeHandle._colIndex];
    columnRef.dragResizeHandle( evt );   
}



IFDSTable_Column.prototype.destroy = function()
{
	if ( this._isSortable )
	{
		EvtHandler.remove( this._headerElem, "click", IFDSTable_Column.clickHandler_headerElem );
	}
	
	if ( this._resizeHandle )
	{
		EvtHandler.remove( this._resizeHandle, "mousedown", IFDSTable_Column.mousedownHandler_resizeHandle );
		this._resizeHandle.parentNode.removeChild( this._resizeHandle );
		this._resizeHandle = null;
	}
	
	this._tableRef = null;
    this._headerElem = null;
    this._baseStyleClass = null;
    this._index = null;
    for ( var i = this._cellArray.length - 1; i >= 0; i-- )
    {        
    	delete this._cellArray[i];
    }
               
    this._width = null
    this._sortDir = null;
    this._isSortable = null
    this._dataType = null;	
}



/**  
 * processes the dragging of the resize handle, once complete (mouseup) will call resize on this column 
 */
IFDSTable_Column.prototype.dragResizeHandle = function( evtObj )
{
    var columnRef = this;
	var resizeHandle = this._resizeHandle;	
	
	// makes the resize handle visibile
	resizeHandle.style.filter = "alpha( opacity=100 )";
	resizeHandle.style.background  = "none";
	resizeHandle.style.height = columnRef._tableRef._tableElem.offsetHeight;
	
	var startMouseX = evtObj.clientX;
	var startHandleLeft = resizeHandle.offsetLeft;
	var minLeft = startHandleLeft - parseInt( this._headerElem.offsetWidth );
	var maxLeft = startHandleLeft + parseInt( this._headerElem.nextSibling.offsetWidth );	
	
	
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
		throw new Error( Err.genErrMsg( "browser event handling not supported", "dragResizeHandle()", "IFDSTable.js" ) );
	}
	
	if ( evtObj.stopPropagation ) evtObj.stopPropagation();		
	else evtObj.cancelBubble = true;
		
	if ( evtObj.preventDefault ) evtObj.preventDefault();
	else evtObj.returnValue = false;
	
	// handler function that gets attached to mouse move event
	function moveHandler( e )
	{
		if ( !e ) e = window.event;
		
		var newX = e.clientX;
		var newLeft = newX - ( startMouseX - startHandleLeft );
						
		if ( newLeft > minLeft && newLeft < maxLeft )
		{					
			resizeHandle.style.left = newLeft;
		}
								
		if ( e.stopPropagation ) e.stopPropagation();		
		else e.cancelBubble = true;																				
	}
		
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
		
		columnRef.setWidth( parseInt( resizeHandle.style.left ) - minLeft );
		
		// re-hides the resize handle
		resizeHandle.style.filter = "alpha( opacity=0 )";
		resizeHandle.style.background = "black";
		
		if ( e.stopPropagation ) e.stopPropagation();		
		else e.cancelBubble = true;
	}	 							
}



/**  
 * Returns the index of this column 
 */
IFDSTable_Column.prototype.getIndex = function()
{
    return this._index;
}



/**  
 * Returns the index of this column 
 */
IFDSTable_Column.prototype.getDataType = function()
{
    return this._dataType;
}



/**  
 * Sets the width of this column, and also the corresponding width to the adjacent column 
 * 
 * @param {number} newWidth
 */
IFDSTable_Column.prototype.setWidth = function( newWidth )
{    
    var nextCol = this._tableRef._colArray[this._index + 1]
    if ( nextCol )
    {   
        var oldWidth = this._width;
        this._headerElem.style.width = newWidth;
        this._width = newWidth;
        
        var nextHeaderElem = nextCol._headerElem;
        var nextColNewWidth = parseInt( nextCol.getWidth() ) + parseInt( oldWidth - newWidth );   
        nextHeaderElem.style.width = nextColNewWidth;
        nextCol._width = nextColNewWidth;                         
    }    
}



/**  
 * Gets the width of this column  
 */
IFDSTable_Column.prototype.getWidth = function()
{
    return this._width;
}



/**  
 * Sets a cell within this column, at the given row Index
 *
 * @param {number} rowIndex
 * @param {object} cellObj IFDSTable_Cell object  
 */
IFDSTable_Column.prototype.setCell = function( rowIndex, cellObj )
{
    this._cellArray[rowIndex] = cellObj;
}



/**  
 * Returns the cell object at the given row index 
 */
IFDSTable_Column.prototype.getCell = function( rowIndex )
{
    return this._cellArray[rowIndex];
}



/**  
 * Returns the complete cell array of this column 
 */
IFDSTable_Column.prototype.getCellArray = function()
{
    return this._cellArray;
}



/**  
 * Sets the sort direction of this column, note, will update the column header style class accordingly
 * 
 * @param {string} sortDir 
 */
IFDSTable_Column.prototype.setSortDir = function( newSortDir )
{
    if ( this._isSortable )
    {
		var oldSortDir = this._sortDir;	
		var oldClassName = null;		
		if ( oldSortDir == IFDSTable.SORT_ASCENDING )
        {
        	oldClassName = this._tableRef._baseClassName + IFDSTable.HEADER_SUFFIX + IFDSTable.ASCENDING_SUFFIX;
        }
        else if ( oldSortDir == IFDSTable.SORT_DESCENDING )
        {
            oldClassName = this._tableRef._baseClassName + IFDSTable.HEADER_SUFFIX + IFDSTable.DESCENDING_SUFFIX;
        }
        else if ( oldSortDir == IFDSTable.SORT_NONE )
        {
            oldClassName = this._tableRef._baseClassName + IFDSTable.HEADER_SUFFIX + IFDSTable.UNSORTED_SUFFIX;
        }
        else
        {
        	oldClassName = this._tableRef._baseClassName + IFDSTable.HEADER_SUFFIX;
        }
        
	 	var newClassName = null;
        if ( newSortDir == IFDSTable.SORT_ASCENDING )
        {
        	newClassName = this._tableRef._baseClassName + IFDSTable.HEADER_SUFFIX + IFDSTable.ASCENDING_SUFFIX;
        }
        else if ( newSortDir == IFDSTable.SORT_DESCENDING )
        {
            newClassName = this._tableRef._baseClassName + IFDSTable.HEADER_SUFFIX + IFDSTable.DESCENDING_SUFFIX;
        }
        else
        {
            newClassName = this._tableRef._baseClassName + IFDSTable.HEADER_SUFFIX + IFDSTable.UNSORTED_SUFFIX;
        }
        
        //alert( "|" + this._headerElem.className + "| |" + oldClassName + "| |" + newClassName + "|" );
        this._sortDir = newSortDir;
        WebTools.replaceCSSClassName( this._headerElem, oldClassName, newClassName );
    }
}



/**  
 * Returns the sort direction of this column 
 */
IFDSTable_Column.prototype.getSortDir = function()
{
    return this._sortDir;
}



/**  
 * Returns boolean of whether this column is sortable 
 */
IFDSTable_Column.prototype.isSortable = function()
{
    return this._isSortable;
}














function IFDSTable_Cell( tableCellRef )
{   	 
    this._data = tableCellRef.data;
    this._contents = new Array( tableCellRef.childNodes.length );
    for ( var i = 0; i < tableCellRef.childNodes.length; i++ )
    {
    	this._contents[i] = tableCellRef.childNodes[i];
    }
}

IFDSTable_Cell.prototype.setContents = function( tableCellRef )
{	
    this._contents = tableCellRef.childNodes;
}

IFDSTable_Cell.prototype.getContents = function()
{
    return this._contents;
}

IFDSTable_Cell.prototype.setData = function( data )
{
    this._data = data;
}

IFDSTable_Cell.prototype.getData = function()
{
    return this._data;
}