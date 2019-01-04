/** 
 * @fileoverview Contains useful methods for dealing common tasks when working on a web page.
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b>
 *  
 * @author walkerro 
 */


 
/**
 * Static class - constructor not permitted
 *  
 * @class Static class used to hold WebTools functions
 * <br/>
 * <b>REQUIRES: JSLib/Err.js</b> 
 */ 
var WebTools = new function()
{

	/**
	 * Determines the absolute position of a DOM object
	 * <br/>
	 * Deprecated - should use calcElemPos
	 * 
	 * @param {DOMElement} obj Reference to a DOM element, whose position is to be determined	 
	 * @return {Object} Object with two properties - top and left
	 */	 
	this.findElemPos = function ( obj ) 
	{	
		if ( !obj )
		{
			throw new Error( Err.genErrMsg( "obj is null", "findElemPos()", "UTL.js" ) );
		}
			
		var curleft = curtop = 0;
			
		if ( obj.offsetParent ) 
		{
			curleft = obj.offsetLeft
			curtop = obj.offsetTop
			while ( obj = obj.offsetParent ) 
			{
				curleft += obj.offsetLeft
				curtop += obj.offsetTop
			}
		}
		return {left:curleft, top:curtop};
	}


	/**
	 * Determines the absolute position of a DOM object. Takes padding and borders of parent
	 * nodes into consideration, unlike findElemPos.
	 * 
	 * @param {DOMElement} obj Reference to a DOM element, whose position is to be determined	 
	 * @return {Object} Object with two properties - top and left
	 */	 
	this.calcElemPos = function ( obj ) 
	{	
		if ( !obj )
		{
			throw new Error( Err.genErrMsg( "obj is null", "findElemPos()", "WebTools.js" ) );
		}
			
		var curLeft = curTop = 0;
			
		// go up thru the DOM
		if ( obj.offsetParent ) 
		{
			curLeft = obj.offsetLeft;
			curTop = obj.offsetTop;
						
			while ( obj = obj.offsetParent ) 
			{
				var offsetTotal_left = parseInt( obj.offsetLeft );
				var offsetTotal_top = parseInt( obj.offsetTop );
				
				// offsetLeft and offsetTop do not consider borders
				var borderLeftWidth = 0;
				var borderTopWidth = 0;
				if ( window.getComputedStyle )
				{
					borderLeftWidth = parseInt( window.getComputedStyle( obj, null ).borderLeftWidth );
					borderTopWidth = parseInt( window.getComputedStyle( obj, null ).borderTopWidth );
				}
				else
				{
					borderLeftWidth = ( !isNaN( Number( parseInt( obj.currentStyle.borderLeftWidth ) ) ) ? Number( parseInt( obj.currentStyle.borderLeftWidth ) ) : 0 );
					borderTopWidth = ( !isNaN( Number( parseInt( obj.currentStyle.borderTopWidth ) ) ) ? Number( parseInt( obj.currentStyle.borderTopWidth ) ) : 0 );
				}
				
				offsetTotal_left += borderLeftWidth;
				offsetTotal_top += borderTopWidth;
												
				curLeft += offsetTotal_left;
				curTop += offsetTotal_top;						
			}
		}		
		return {left:curLeft, top:curTop};
	}
	
	
	/**
	 * Wrapper method for adding number of style properties at one time
	 * 
	 * @param {DOMElement} elem Reference to a DOM element, whose style is to be updated	 
	 * @return {Object} stylePropMap map of style properties and values
	 */	 
	this.addStyleProps = function( elem, stylePropMap )
	{
		for( var i in stylePropMap )
		{			
			elem.style[i] = stylePropMap[i];			
		}
	}
	
	
	/**
	 * Builds a table DOM element, with given number of rows and cols (if any)
	 * 
	 * @param {integer} rows number of rows to add (optional)	 
	 * @return {integer} cols number of cols to add (optional)
	 * @return {DOM element}
	 */
	this.buildTableElem = function( rows, cols )
	{
		var table = document.createElement( "table" )
		table.cellPadding = 0;
		table.cellSpacing = 0;
		var tbody = table.appendChild( document.createElement( "tbody" ) );
		
		rows = ( rows == null ? 0 : rows );
		cols = ( cols == null ? 0 : cols );
		
		if ( rows < 0 || cols < 0 )
		{
			throw new Error ( Err.genErrMsg( "invalid row/col values given", "buildTableElem()", "WebTools.js" ) );
		}
		
		for ( var r = 0; r < rows; r++ )
		{
			var tr = tbody.appendChild( document.createElement( "tr" ) );
			for( var c = 0; c < cols; c++ )
			{
				tr.appendChild( document.createElement( "td" ) );
			}
		}
		return table;		
	}
	
	
	/**
	 * Gets reference to a row (TR) in the given table
	 * 
	 * @param {DOM element} table Where to pull the row from	 
	 * @param {integer} rowNum row index
	 * @return {DOM element}
	 */
	this.getTableRow = function( table, rowNum )
	{
		var tbody = table.lastChild;
		if ( !tbody && tbody.nodeName.toUpperCase() != "TBODY" )
		{
			throw new Error( Err.genErrMsg( "invalid table reference given", "getTableRow()", "WebTools.js" ) );
		}
		if ( !tbody.childNodes[rowNum] )
		{
			throw new Error( Err.genErrMsg( "invalid row index given", "getTableRow()", "WebTools.js" ) );
		}
		return tbody.childNodes[rowNum];
	}
	
	
	/**
	 * Gets reference to a cell (TD) in the given table
	 * 
	 * @param {DOM element} table Where to pull the row from	 
	 * @param {integer} rowNum row index
	 * @param {integer} colNum column index	 
	 * @return {DOM element}
	 */
	this.getTableCell = function( table, rowNum, colNum )
	{		
		var tr = this.getTableRow( table, rowNum );
		if ( !tr.childNodes[colNum] )
		{
			throw new Error ( Err.genErrMsg( "invalid col index given", "getTableCell()", "WebTools.js" ) );
		}
		return tr.childNodes[colNum];	
	}
	
	
	/**
	 * Creates an iframe object, to act as buffer layer between the specified element, 
	 * and the rest of the page. This is useful if the elem is to appear "above" all 
	 * other page elements, namely select boxes in IE6 (for which z-index is ignored)
	 * 
	 * @param {DOMElement} elem Reference to a DOM element, whom the iframe layer is to go under	 
	 * @return {DOMElement} 
	 */
	this.buildIframeLayer = function( elem )
	{
		var iframe = document.createElement( "iframe" );
		document.body.appendChild( iframe );
				
		var posObj = this.findElemPos( elem );
		
		var stylePropMap = {};
		stylePropMap["position"] 	= "absolute";
		stylePropMap["top"] 		= posObj.top;
		stylePropMap["left"] 		= posObj.left;
		stylePropMap["width"] 		= elem.offsetWidth;
		stylePropMap["height"] 		= elem.offsetHeight;
		stylePropMap["border"]		= "none";
		stylePropMap["zIndex"] 		= parseInt( elem.style.zIndex ) - 1;
		
		this.addStyleProps( iframe, stylePropMap );
		
		iframe.frameBorder = "0";
		
		return iframe;										
	}
	
	
	/**
	 * Function for "Dragging" an absolutely positioned DOM Element
	 * 
	 * @param {event} evtObj Reference the onmousedown event which is to kick-off the dragging
	 * @param {DOMElement} focusElement Element which has the onmousedown handler attached
	 * @param {DOMElement} elementToDrag Element (absolutely positioned) to actually move with mouse dragging
	 * @param {string} cursorStyle style to set the cursor after dragging is completed	 	 	 	 
	 */
	this.dragElement = function( evtObj, focusElement, elementToDrag, cursorStyle )
	{
		var startX = evtObj.clientX;
		var startY = evtObj.clientY;
		
		var elemOrigPos = this.findElemPos( elementToDrag );				
		
		// NOTE: we don't use EvtHandler here, because doesn't handle event 'capturing' (blame IE)
		if ( document.addEventListener )
		{
			document.addEventListener( "mousemove", moveHandler, true );
			document.addEventListener( "mouseup", upHandler, true );
		}
		else if ( document.attachEvent )
		{
			focusElement.setCapture();
			focusElement.attachEvent( "onmousemove", moveHandler );
			focusElement.attachEvent( "onmouseup", upHandler );
			focusElement.attachEvent( "onlosecapture", upHandler );			
		}
		else
		{
			throw new Error( Err.genErrMsg( "event handling won't support this", "dragElement()", "WebTools" ) );
		}
		
		if ( event.stopPropagation ) event.stopPropagation();		
		else event.cancelBubble = true;
			
		if ( event.preventDefault ) event.preventDefault();
		else event.returnValue = false;		
		
		function moveHandler( e )
		{
			if ( !e ) e = window.event;
			
			elementToDrag.style.left = e.clientX - ( startX - elemOrigPos.left );
			elementToDrag.style.top = e.clientY - ( startY - elemOrigPos.top );
						
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
				focusElement.detachEvent( "onlosecapture", upHandler );
				focusElement.detachEvent( "onmouseup", upHandler );
				focusElement.detachEvent( "onmousemove", moveHandler );	
				focusElement.releaseCapture();										
			}
			
			if ( cursorStyle )
			{
				document.body.style.cursor = cursorStyle;
			}
			
			if ( e.stopPropagation ) e.stopPropagation();		
			else e.cancelBubble = true;
		}	 	
	}

		 
	/**
	 * Function for (deep) cloning a DomElement. Also, to avoid possible id duplication in the cloned element,
	 * an idModifier can specified to augment any ids found within the cloned element.
	 * <br/>
	 * Note: Event handlers are not copied over to cloned nodes
	 * 
	 * @param {DomElement/String} srcElem Either a reference or the id of the DomElement to be cloned
	 * @param {string} idModifier (optional) string that gets added to any ids found within the cloned element	 	 	 
	 */
	this.cloneElement = function( srcElem, idModifier )
	{		
		var clonedElem = srcElem.cloneNode( true );
								
		if ( idModifier != null )
		{
			modId( clonedElem );		
		}
		
		function modId( elem )
		{
			if ( elem.id )
			{
				if ( typeof idModifier != "string" )
				{
					elem.id = idModifier( elem.id )	
				}
				else
				{
					elem.id = elem.id + idModifier;
				}				
			}
			for ( var i = 0; i < elem.childNodes.length; i++ )
			{
				modId( elem.childNodes[i] );
			}
		}
		
		return clonedElem;		
	}
	
	
	/**
	 * Browser generic method for getting the specified style property value for the given element.
	 * Used when style property has been set using CSS, and not style object. 
	 * 
	 * @param {DomElement/String} elem
	 * @param {string} styleProp	 	 	 
	 */
	this.getComputedStyle = function( elem, styleProp )
	{
		if ( elem.currentStyle )
		{
			return elem.currentStyle[styleProp];
		}
		else if ( window.getComputedStyle )
		{
			return window.getComputedStyle( elem, null )[styleProp];
		}
		else
		{
			throw new Error( Err.genErrMsg( "width cannot be determined - browser issue", "getWidth()", "CalendarWidget.js" ) );
		}
	}
	

	/**
	 * Sets the className attribute of the given element to the string array (" " delimited) 
	 * 
	 * @param {DomElement/String} elem
	 * @param {string array} stringArray	 	 	 
	 */	
	this.setClassName = function( elem, stringArray )
	{
		var temp = elem.className;
		elem.className = "";
		for ( var i = 0; i < stringArray.length; i++ )
		{
			if ( i < stringArray.length - 1 )
			{
				elem.className += stringArray[i] + " ";
			}
			else
			{
				elem.className += stringArray[i];
			}
		}
		
		//alert( "BEFORE: |" + temp + "| AFTER: |" + elem.className + "|") 
	}
	
	
	/**
	 * Adds a className to elem 
	 * 
	 * @param {DomElement/String} elem
	 * @param {string} classNameToAdd	 	 	 
	 */
	this.appendCSSClassName = function( elem, classNameToAdd )
	{		
		var classNameArray = null;
		if ( elem.className.length == 0 )
		{
			classNameArray = [classNameToAdd];
		}
		else
		{
			classNameArray = elem.className.split( " " );
			classNameArray[classNameArray.length] = classNameToAdd;
		}
			
		this.setClassName( elem, classNameArray ); 
	}
	
	

	/**
	 * Removes a className from the elem
	 * 
	 * @param {DomElement/String} elem
	 * @param {string} classNameToRemove	 	 
	 */	
	this.removeCSSClassName = function( elem, classNameToRemove )
	{
		var origClassNameArray = elem.className.split( " " );
		var newClassNameArray = [];
		var newCount = 0;
		for ( var i = 0; i < origClassNameArray.length; i++ )
		{
			if ( origClassNameArray[i] != classNameToRemove )
			{
				newClassNameArray[newCount] = origClassNameArray[i];
				newCount++
			}
		}
		
		this.setClassName( elem, newClassNameArray );		
	}
	


	/**
	 * Replaces one className value with another for the given elem
	 * 
	 * @param {DomElement/String} elem	 
	 * @param {string} classNameToRemove
	 * @param {string} classNameToAdd	 	 
	 */		
	this.replaceCSSClassName = function( elem, classNameToRemove, classNameToAdd )
	{
		var classNameArray = elem.className.split( " " );
		
		for ( var i = 0; i < classNameArray.length; i++ )
		{
			if ( classNameArray[i] == classNameToRemove )
			{				
				classNameArray[i] = classNameToAdd;
				break;
			}			
		}
		
		if ( i == classNameArray.length )
		{
		
			throw new Error( Err.genErrMsg( "'" + classNameToRemove + "'" + " not found in element's className", "replaceCSSClassName()", "WebTools.js" ) );
		}
		
		this.setClassName( elem, classNameArray );		
	}
}