/** 
 * @fileoverview Contains source code for contructing and interacting with browser Calendar Widget 
 * <br/>
 * <b>REQUIRES: JSLib/Err.js, JSLib/EvtHandler.js, JSLib/WebTools.js, JSLib/UTL.js</b>
 * 
 *  
 * @author walkerro 
 */


/**  
 * @class IFDSCalendarWidget
 * 
 * @param {DOMNode} container DOM element in which to build the calendar
 * @param {string} holderStyleClass class name to give the the calendar holder - all other predesignated
 * element class definitions are assumed to be declared as a child of this class definition
 * @param {boolean} isPopup (optional) boolean to indicate if this calendar instance is to be used as a popup 
 * (ie. with datepickers ). default is false
 * @param (boolean} iframeReqd (optional) boolean to indicate if Calendar should make use of an iframe buffer layer
 * (ie. as popup - in IE6 ). default is false
 */
function IFDSCalendarWidget( container, holderStyleClass, isPopup, iframeReqd )
{
	// predesignated classNames used for the calendar components
	// the CSS definition of these classes is assumed to be provided
	this._styleClassMap = {
		calendarHolder:     	holderStyleClass,
		
		calendarBackground:		"calendarBackground",
				
		monthLbl:				"monthLbl",
		prevMonthBtn:       	"prevMonthBtn",
		nextMonthBtn:       	"nextMonthBtn",
		
		yearLbl:				"yearLbl",
		prevYearBtn:        	"prevYearBtn",
		nextYearBtn:        	"nextYearBtn",
		
		todayBtn:				"todayBtn",
		
		daynameCell:			"daynameCell",
		dayCell:				"dayCell",
		
		today:					"today",
		prev_or_nextMonth:		"prev_or_nextMonth",
		
		normal:					"normal",
		highlighted:			"highlighted",
		selected:				"selected"		
	};

	// references to the calendar components
	this._mainDiv 					= null;
	this._monthLbl					= null;
	this._prevMonthBtn				= null;
	this._nextMonthBtn  			= null;	
	this._yearLbl					= null;
	this._prevYearBtn				= null;
	this._nextYearBtn				= null;		
	this._todayBtn					= null;	
	this._weekDivArray				= null;		
	this._monthSelectorDiv 			= null;
	this._yearSelectorDiv			= null;		
	this._selectedDate				= null;
	this._onDateSelectedFunction 	= null;
	this._isPopup					= null;
	this._assocDatepicker			= null;
	
	this._isPopup = ( isPopup == null ? false : isPopup );
		
	// build main div, and place in the given container element				
	this._mainDiv = this.buildMainDiv( container );
	
	// build iframeLayer, if req'd
	if ( iframeReqd )
	{ 
		this.buildIframeLayer( this._mainDiv );
	}
	
	// build contentsDiv
	var contentsDiv = this.buildContentsDiv( this._mainDiv ); 
		
	// build month (header) section
	var monthSection = this.buildMonthSection( contentsDiv, 0, 0 );	
	// build days (body) section	 
	var daysSection = this.buildDaysSection( contentsDiv, parseInt( WebTools.getComputedStyle( monthSection, "height" ) ), 0 );	
	// build year (footer) section
	this.buildYearSection( contentsDiv, parseInt( WebTools.getComputedStyle( monthSection, "height" ) ) + parseInt( WebTools.getComputedStyle( daysSection, "height" ) ), 0 );
						
	// build the selectors - year and month
	this._monthSelectorDiv = this.buildMonthSelector( contentsDiv ); 
	this._yearSelectorDiv = this.buildYearSelector( contentsDiv );
		
	// initially set month to current
	var today = new Date();	
	this.setMonth( today.getMonth(), today.getFullYear() );
}


/**
 * Array used to identify month names
 * @type string array
 */
IFDSCalendarWidget.MONTH_NAME_ARRAY = ["january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"];


/**
 * Array used to identify names for days of the week
 * @type string array
 */
IFDSCalendarWidget.DAY_NAME_ARRAY 	= ["sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"];


/**
 * Constant for the max calendar year
 * @type integer
 */
IFDSCalendarWidget.MAX_YEAR			= 9999;


/**
 * Constant for the min calendar year
 * @type integer
 */
IFDSCalendarWidget.MIN_YEAR			= 0;


/**
 * EVENT HANDLER: blur handler for the calendar holder
 * 
 * Note: this is only for use when calendar being used as a popup, and in MOZ, since IE
 * doesn't properly support focus/blur events for divs.
 */
IFDSCalendarWidget.blurHandler_mainDiv = function( calendarRef, evt )
{
	if ( calendarRef._isPopup && UTL.isMOZEventModel() )
	{
		calendarRef.setVisible( false );
		// after closing the calendar popup, we want to re-enable the calendarBtn which
		// opened the popup, which requires a delay in order to allow user to click the calendarBtn
		// to close the calendar
		if ( calendarRef._assocDatepicker )
		{
			// this is a bit of a hack - in MOZ timeouts are run at global scope
			setTimeout( "IFDSDatepickerManager.getDatepicker( \"" + calendarRef._assocDatepicker._dateFld.id + "\" ).enableCalendarBtn()", 125 );
		}		 			
	}
	evt.stopPropagation();
}


/**
 * EVENT HANDLER: click handler for the calendar holder
 */
IFDSCalendarWidget.clickHandler_mainDiv = function( calendarRef, evt )
{
	if ( calendarRef.isYearSelectorOpen() )
	{
		calendarRef.closeYearSelector();
	}
	
	if ( calendarRef.isMonthSelectorOpen() )
	{
		calendarRef.closeMonthSelector();
	}
	evt.stopPropagation();
}


/**
 * EVENT HANDLER: click handler for the month label
 */
IFDSCalendarWidget.clickHandler_monthLbl = function( calendarRef, evt )
{
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		calendarRef.openMonthSelector();
		evt.stopPropagation();			
	}		
}


/**
 * EVENT HANDLER: click handler for the prev month btn
 */
IFDSCalendarWidget.clickHandler_prevMonthBtn = function( calendarRef, evt )
{	
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		var curMonth = parseInt( calendarRef._monthLbl.getAttribute( "_monthVal" ) );
		var curYear = parseInt( calendarRef._yearLbl.getAttribute( "_yearVal" ) );
		
		if ( curMonth == 0 && curYear > IFDSCalendarWidget.MIN_YEAR )
		{
			calendarRef.setMonth( 11, curYear - 1 );
		}
		else
		{
			calendarRef.setMonth( curMonth - 1, curYear );
		}
	}					
}


/**
 * EVENT HANDLER: click handler for the next month btn
 */
IFDSCalendarWidget.clickHandler_nextMonthBtn = function( calendarRef, evt )
{
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		var curMonth = parseInt( calendarRef._monthLbl.getAttribute( "_monthVal" ) );
		var curYear = parseInt( calendarRef._yearLbl.getAttribute( "_yearVal" ) );
		
		if ( curMonth == 11 && curYear < IFDSCalendarWidget.MAX_YEAR )
		{
			calendarRef.setMonth( 0, curYear + 1 );
		}
		else
		{
			calendarRef.setMonth( curMonth + 1, curYear );
		}
	}			
}


/**
 * EVENT HANDLER: click handler for the year label
 */
IFDSCalendarWidget.clickHandler_yearLbl = function( calendarRef, evt )
{	
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		calendarRef.openYearSelector();
		evt.stopPropagation();			
	}
		
}


/**
 * EVENT HANDLER: click handler for the prev year btn
 */
IFDSCalendarWidget.clickHandler_prevYearBtn = function( calendarRef, evt )
{
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		var curMonth = parseInt( calendarRef._monthLbl.getAttribute( "_monthVal" ) );
		var curYear = parseInt( calendarRef._yearLbl.getAttribute( "_yearVal" ) );
		
		if ( curYear > IFDSCalendarWidget.MIN_YEAR )
		{
			calendarRef.setMonth( curMonth, curYear - 1 );
		}
	}			
}


/**
 * EVENT HANDLER: click handler for the next year btn
 */
IFDSCalendarWidget.clickHandler_nextYearBtn = function( calendarRef, evt )
{
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		var curMonth = parseInt( calendarRef._monthLbl.getAttribute( "_monthVal" ) );
		var curYear = parseInt( calendarRef._yearLbl.getAttribute( "_yearVal" ) );
		
		if ( curYear < IFDSCalendarWidget.MAX_YEAR )
		{
			calendarRef.setMonth( curMonth, curYear + 1 );
		}		
	}
}


/**
 * EVENT HANDLER: click handler for the today btn
 */
IFDSCalendarWidget.clickHandler_todayBtn = function( calendarRef, evt )
{	
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		var today = new Date();
		calendarRef.setMonth( today.getMonth(), today.getFullYear() );
	}						
}


/**
 * EVENT HANDLER: click handler for a day cell in the calendar
 */
IFDSCalendarWidget.clickHandler_day = function( calendarRef, evt )
{	
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{		
		if ( calendarRef._onDateSelectedFunction )
		{
			var dateLbl = evt.currentTarget;
			calendarRef._onDateSelectedFunction( new Date( dateLbl.getAttribute( "_dateVal" ) ) );
		}
		else
		{
			throw new Error( Err.genErrMsg( "OnDateSelectedFunction has not been set", "clickHandler_day()", "IFDSCalendarWidget.js" ) );
		}
	}		
}


/**
 * EVENT HANDLER: mouseover handler for a day cell in the calendar
 */
IFDSCalendarWidget.mouseoverHandler_day = function( calendarRef, evt )
{	
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		var dayTD = evt.currentTarget;		
		if ( calendarRef._selectedDate == null || dayTD.getAttribute( "_dateVal" ) != calendarRef._selectedDate.toDateString() )
		{						
			var classNamesArray = dayTD.className.split( " " );
			dayTD.className = "";
			for ( var i = 0; i < classNamesArray.length - 1; i++ )
			{	
				if ( i == 0 )
				{
					dayTD.className = classNamesArray[i];
				}			
				else
				{
					dayTD.className += " " + classNamesArray[i]; 
				}
				
			}
			dayTD.className += " " + calendarRef._styleClassMap["highlighted"];						
		}	
	}			
}


/**
 * EVENT HANDLER: mouseout handler for a day cell in the calendar
 */
IFDSCalendarWidget.mouseoutHandler_day = function( calendarRef, evt )
{
	if ( !calendarRef.isYearSelectorOpen() && !calendarRef.isMonthSelectorOpen() )
	{
		var dayTD = evt.currentTarget;
		if ( calendarRef._selectedDate && dayTD.getAttribute( "_dateVal" ) == calendarRef._selectedDate.toDateString() )
		{			
			var classNamesArray = dayTD.className.split( " " );
			dayTD.className = "";
			for ( var i = 0; i < classNamesArray.length - 1; i++ )
			{
				if ( i == 0 )
				{
					dayTD.className = classNamesArray[i];
				}
				else
				{
					dayTD.className += " " + classNamesArray[i];
				}				
			}
			dayTD.className += " " + calendarRef._styleClassMap["selected"];
		}
		else
		{		
			var classNamesArray = dayTD.className.split( " " );
			dayTD.className = "";
			for ( var i = 0; i < classNamesArray.length - 1; i++ )
			{
				if ( i == 0 )
				{
					dayTD.className = classNamesArray[i];
				}
				else
				{
					dayTD.className += " " + classNamesArray[i]
				}			
			}
			dayTD.className += " " + calendarRef._styleClassMap["normal"];
		}						
	}		
}


/**
 * EVENT HANDLER: mouseover handler for a month selector item
 */
IFDSCalendarWidget.mouseoverHandler_monthSelectorItem = function( calendarRef, evt )
{
	evt.currentTarget.style.padding = 0;
	evt.currentTarget.style.border = "1px dashed black";			
}


/**
 * EVENT HANDLER: mouseout handler for a month selector item
 */
IFDSCalendarWidget.mouseoutHandler_monthSelectorItem = function( calendarRef, evt )
{
	evt.currentTarget.style.padding = 1;
	evt.currentTarget.style.border = 0;
}


/**
 * EVENT HANDLER: click handler for a month selector item
 */
IFDSCalendarWidget.clickHandler_monthSelectorItem = function( calendarRef, evt )
{	
	var monthLbl = evt.currentTarget;
	var selectedMonth = monthLbl.getAttribute( "_monthVal" );		
	var curYear = calendarRef._yearLbl.getAttribute( "_yearVal" );		
	calendarRef.setMonth( selectedMonth, curYear );
	calendarRef.closeMonthSelector();	
}


/**
 * EVENT HANDLER: click handler for a month selector close btn
 */
IFDSCalendarWidget.clickHandler_monthSelectorCloseBtn = function( calendarRef, evt )
{
	calendarRef.closeMonthSelector();
}


/**
 * EVENT HANDLER: mouseover handler for a year selector item
 */
IFDSCalendarWidget.mouseoverHandler_yearSelectorItem = function( calendarRef, evt )
{	
	evt.currentTarget.style.padding = 0;
	evt.currentTarget.style.border = "1px dashed black";		
}


/**
 * EVENT HANDLER: mouseout handler for a year selector item
 */
IFDSCalendarWidget.mouseoutHandler_yearSelectorItem = function( calendarRef, evt )
{
	evt.currentTarget.style.padding = 1;
	evt.currentTarget.style.border = "none";		
}


/**
 * EVENT HANDLER: click handler for a year selector item
 */
IFDSCalendarWidget.clickHandler_yearSelectorItem = function( calendarRef, evt )
{
	var yearLbl = evt.currentTarget;
	var selectedYear = parseInt( yearLbl.innerHTML );		
	var curMonth = calendarRef._monthLbl.getAttribute( "_monthVal" );		
	calendarRef.setMonth( curMonth, selectedYear );
	calendarRef.closeYearSelector();			
}


/**
 * EVENT HANDLER: click handler for the prev decade btn in the Year Selector Div
 */
IFDSCalendarWidget.clickHandler_prevDecadeBtn = function( calendarRef, evt )
{	
	var yearTable = calendarRef._yearSelectorDiv.firstChild;
	var yearTable_startYear = parseInt( yearTable.firstChild.firstChild.firstChild.innerHTML );
		
	if ( yearTable_startYear - 10 >= IFDSCalendarWidget.MIN_YEAR )
	{
		calendarRef.populateYearSelector( yearTable_startYear - 10 );
	}	
}


/**
 * EVENT HANDLER: click handler for the next decade btn in the Year Selector Div
 */
IFDSCalendarWidget.clickHandler_nextDecadeBtn = function( calendarRef, evt )
{	
	var yearTable = calendarRef._yearSelectorDiv.firstChild;
	var yearTable_startYear = parseInt( yearTable.firstChild.firstChild.firstChild.innerHTML );	
		
	if ( yearTable_startYear + 10 <= IFDSCalendarWidget.MAX_YEAR - 9 )
	{
		calendarRef.populateYearSelector( yearTable_startYear + 10 );
	}
}


/**
 * EVENT HANDLER: click handler year selector close btn
 */
IFDSCalendarWidget.clickHandler_yearSelectorCloseBtn = function( calendarRef, evt )
{
	calendarRef.closeYearSelector();
}


/**
 * EVENT HANDLER: click handler year selector close btn
 * 
 * Note: this blur handler is actually used for BOTH MOZ AND IE, because
 * focus is explicitly set to the year selector when its opened (when not used as a popup),
 * and in that case IE does handle blur/focus events properly
 */
IFDSCalendarWidget.blurHandler_yearSelector = function( calendarRef, evt )
{		
	if ( !calendarRef._isPopup )
	{	
		calendarRef.closeYearSelector();
	}
}


/**
 * EVENT HANDLER: click handler year selector close btn
 * 
 * Note: this blur handler is actually used for BOTH MOZ AND IE, because
 * focus is explicitly set to the month selector when its opened (when not used as a popup),
 * and in that case IE does handle blur/focus events properly
 */
IFDSCalendarWidget.blurHandler_monthSelector = function( calendarRef, evt )
{	
	if ( !calendarRef._isPopup )
	{	
		calendarRef.closeMonthSelector();
	}
}


/**
 * Builds the main holder div
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @return {DOMNode} 
 */ 
IFDSCalendarWidget.prototype.buildMainDiv = function( container )
{
	var d = container.appendChild( document.createElement( "div" ) );	
	d.className = this._styleClassMap["calendarHolder"];
	if ( UTL.isMOZEventModel() )
	{
		d.tabIndex = -1;
		d.style.MozOutlineStyle = "none";	
	}
	else if( UTL.isIEEventModel() && this._isPopup )
	{		
		d.unselectable = "on";
	}
						
	var calendarRef = this;
	EvtHandler.add( d, "click", function( evt ){ IFDSCalendarWidget.clickHandler_mainDiv( calendarRef, evt ) } );
	EvtHandler.add( d, "focus", function( evt ){ IFDSCalendarWidget.focusHandler_mainDiv( calendarRef, evt ) } );
	EvtHandler.add( d, "blur",  function( evt ){ IFDSCalendarWidget.blurHandler_mainDiv( calendarRef, evt ) } );
	
	return d;
}


/**
 * Builds the contents div
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @return {DOMNode}
 */
IFDSCalendarWidget.prototype.buildContentsDiv = function( container )
{
	var d = container.appendChild( document.createElement( "div" ) );
	d.className = this._styleClassMap["calendarBackground"];
	if ( UTL.isIEEventModel() && this._isPopup ) d.unselectable = "on";		
	
	var wd = parseInt( WebTools.getComputedStyle( container, "width" ) );
	var ht = parseInt( WebTools.getComputedStyle( container, "height" ) );
	WebTools.addStyleProps( d, { position:"absolute", top:0, left:0, width:wd, height:ht, zIndex:1 } );
	
	return d;	
}


/**
 * Builds the iframe layer
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @return {DOMNode} 
 */ 
IFDSCalendarWidget.prototype.buildIframeLayer = function( container )
{
	var ifr = container.appendChild( document.createElement( "iframe" ) );
	var html = '<body style="background-color:transparent;"></body>';
	if ( UTL.isIEEventModel() && this._isPopup ) ifr.unselectable = "on";
    ifr.src = "javascript: {this.innerHTML = '" + html + "';}";		
	ifr.frameBorder = "no";
	ifr.tabIndex = -1;
	
	WebTools.addStyleProps( ifr, { position:"absolute", top:0, left:0, zIndex:0, width:"100%", height:"100%" } );
	
	return ifr;	
}


/**
 * Builds the Month section: prev/next btns and the label
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @param {number} topPos top co-ord to place the absolutely positioned month section within container
 * @param {number} leftPos left co-ord to place the absolutely positioned month section within container
 * @return {DOMNode} 
 */ 
IFDSCalendarWidget.prototype.buildMonthSection = function( container, topPos, leftPos )
{
	var calendarRef = this;
	
	var div = container.appendChild( document.createElement( "div" ) );	
	if ( UTL.isIEEventModel() && this._isPopup ) div.unselectable = "on";
	
	// prev btn			
	this._prevMonthBtn = div.appendChild( document.createElement( "span" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) this._prevMonthBtn.unselectable = "on";	
	this._prevMonthBtn.className = this._styleClassMap["prevMonthBtn"];			
	EvtHandler.add( this._prevMonthBtn, "click", function( evt ){ IFDSCalendarWidget.clickHandler_prevMonthBtn( calendarRef, evt ) } );
		
	// build _monthLbl
	this._monthLbl = div.appendChild( document.createElement( "span" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) this._monthLbl.unselectable = "on";	
	this._monthLbl.className = this._styleClassMap["monthLbl"];			
	EvtHandler.add( this._monthLbl, "click", function( evt ){ IFDSCalendarWidget.clickHandler_monthLbl( calendarRef, evt ) } );		
	
	// next btn
	this._nextMonthBtn = div.appendChild( document.createElement( "span" ) );	
	if ( UTL.isIEEventModel() && this._isPopup ) this._nextMonthBtn.unselectable = "on";	
	this._nextMonthBtn.className = this._styleClassMap["nextMonthBtn"];			
	EvtHandler.add( this._nextMonthBtn, "click", function( evt ){ IFDSCalendarWidget.clickHandler_nextMonthBtn( calendarRef, evt ) } );

	// calculate the height of the month section
	var ht = Math.max( parseInt( WebTools.getComputedStyle( this._prevMonthBtn, "height" ) ),
					   parseInt( WebTools.getComputedStyle( this._monthLbl, "height" ) ),
					   parseInt( WebTools.getComputedStyle( this._nextMonthBtn, "height" ) ) );
					       
	WebTools.addStyleProps( div, { position:"absolute", width:"100%", height:ht, top:topPos, left:leftPos } );
		
	return div;
}


/**
 * Builds the Year section: prev/next btns, and the label. Also includes the "today" btn.
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @param {number} topPos top co-ord to place the absolutely positioned year section within container
 * @param {number} leftPos left co-ord to place the absolutely positioned year section within container 
 * @return {DOMNode} 
 */ 
IFDSCalendarWidget.prototype.buildYearSection = function( container, topPos, leftPos )
{
	var calendarRef = this;

	var div = container.appendChild( document.createElement( "div" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) div.unselectable = "on";		

	// prev btn					
	this._prevYearBtn = div.appendChild( document.createElement( "span" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) this._prevYearBtn.unselectable = "on";	
	this._prevYearBtn.className = this._styleClassMap["prevYearBtn"];		
	EvtHandler.add( this._prevYearBtn, "click", function( evt ){ IFDSCalendarWidget.clickHandler_prevYearBtn( calendarRef, evt ) } );
			
	// year label			
	this._yearLbl = div.appendChild( document.createElement( "span" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) this._yearLbl.unselectable = "on";			
	this._yearLbl.className = this._styleClassMap["yearLbl"];			
	EvtHandler.add( this._yearLbl, "click", function( evt ){ IFDSCalendarWidget.clickHandler_yearLbl( calendarRef, evt ) } );		
	
	// next btn
	this._nextYearBtn = div.appendChild( document.createElement( "span" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) this._nextYearBtn.unselectable = "on";	
	this._nextYearBtn.className = this._styleClassMap["nextYearBtn"];		
	EvtHandler.add( this._nextYearBtn, "click", function( evt ){ IFDSCalendarWidget.clickHandler_nextYearBtn( calendarRef, evt ) } );
	
	// today btn
	this._todayBtn = div.appendChild( document.createElement( "span" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) this._todayBtn.unselectable = "on";	
	this._todayBtn.className = this._styleClassMap["todayBtn"];
	this._todayBtn.innerHTML = "Today";		
	EvtHandler.add( this._todayBtn, "click", function( evt ){ IFDSCalendarWidget.clickHandler_todayBtn( calendarRef, evt ) } );

	// calculate the height of the year section
	var ht = Math.max( parseInt( WebTools.getComputedStyle( this._prevYearBtn, "height" ) ),
					   parseInt( WebTools.getComputedStyle( this._yearLbl, "height" ) ),
					   parseInt( WebTools.getComputedStyle( this._nextYearBtn, "height" ) ) );
					       
	WebTools.addStyleProps( div, { position:"absolute", width:"100%", height:ht, top:topPos, left:leftPos } );
	
	return div;	
}


/**
 * Builds the Days section: day names row, and the cells for the calendar dates
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @return {DOMNode} 
 */ 
IFDSCalendarWidget.prototype.buildDaysSection = function( container, topPos, leftPos )
{
	var calendarRef = this;
	
	var daysHolderDiv = container.appendChild( document.createElement( "div" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) daysHolderDiv.unselectable = "on";
		
	var daysContentDiv = daysHolderDiv.appendChild( document.createElement( "div" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) daysContentDiv.unselectable = "on";	
	
	// construct the dayname headers
	var dayNamesDiv = daysContentDiv.appendChild( document.createElement( "div" ) );
	if ( UTL.isIEEventModel() && this._isPopup ) dayNamesDiv.unselectable = "on";	
	for ( var i = 0; i < IFDSCalendarWidget.DAY_NAME_ARRAY.length; i++ )
	{
		var dayNameSpan = dayNamesDiv.appendChild( document.createElement( "span" ) );
		if ( UTL.isIEEventModel() && this._isPopup ) dayNameSpan.unselectable = "on";
		dayNameSpan.className = this._styleClassMap["daynameCell"];
		dayNameSpan.innerHTML = IFDSCalendarWidget.DAY_NAME_ARRAY[i].substring( 0, 3 );
		var wd = parseInt( WebTools.getComputedStyle( dayNameSpan, "width" ) );		
		WebTools.addStyleProps( dayNameSpan, { position:"absolute", top:0, left:( i * wd ) } );
	}
	var dayNamesDiv_styleProps = {};
	dayNamesDiv_styleProps["position"] = "absolute";
	dayNamesDiv_styleProps["top"] = 0;	
	dayNamesDiv_styleProps["left"] = 0;
	dayNamesDiv_styleProps["height"] = parseInt( WebTools.getComputedStyle( dayNamesDiv.firstChild, "height" ) );
	dayNamesDiv_styleProps["width"] = parseInt( WebTools.getComputedStyle( dayNamesDiv.firstChild, "width" ) ) * IFDSCalendarWidget.DAY_NAME_ARRAY.length;	
	WebTools.addStyleProps( dayNamesDiv, dayNamesDiv_styleProps );	
	
	// construct the weeks ( 6 of them ) of the calendar
	this._weekDivArray = [];	
	for ( var w = 0; w < 6; w++ )
	{
		this._weekDivArray[w] = daysContentDiv.appendChild( document.createElement( "div" ) );
		if ( UTL.isIEEventModel() && this._isPopup ) this._weekDivArray[w].unselectable = "on";
		for ( var d = 0; d < 7; d++ )
		{
			var daySpan = this._weekDivArray[w].appendChild( document.createElement( "span" ) );
			if ( UTL.isIEEventModel() && this._isPopup ) daySpan.unselectable = "on";
			daySpan.className = this._styleClassMap["dayCell"];
			var wd = parseInt( WebTools.getComputedStyle( daySpan, "width" ) );
			WebTools.addStyleProps( daySpan, { position:"absolute", top:0, left:(d * wd) } );					
			
			// add event handlers to the day cells
			EvtHandler.add( daySpan, "click", function( evt ){ IFDSCalendarWidget.clickHandler_day( calendarRef, evt ) } );
			EvtHandler.add( daySpan, "mouseover", function( evt ){ IFDSCalendarWidget.mouseoverHandler_day( calendarRef, evt ) } );
			EvtHandler.add( daySpan, "mouseout", function( evt ){ IFDSCalendarWidget.mouseoutHandler_day( calendarRef, evt ) } );	
		}
		var weekDiv_styleProps = {};
		weekDiv_styleProps["position"] = "absolute";
		weekDiv_styleProps["height"] = parseInt( WebTools.getComputedStyle( this._weekDivArray[w].firstChild, "height" ) );			
		weekDiv_styleProps["width"] = parseInt( WebTools.getComputedStyle( this._weekDivArray[w].firstChild, "height" ) ) * 7;
		weekDiv_styleProps["top"] = dayNamesDiv_styleProps["height"] + ( w * weekDiv_styleProps["height"] );
		weekDiv_styleProps["left"] = 0
		WebTools.addStyleProps( this._weekDivArray[w], weekDiv_styleProps );		
	}
	
	var daysContentDiv_styleProps = {};
	daysContentDiv_styleProps["position"] = "absolute";	
	daysContentDiv_styleProps["width"] = Math.max( dayNamesDiv_styleProps["width"], parseInt( WebTools.getComputedStyle( this._weekDivArray[0], "width" ) ) );
	daysContentDiv_styleProps["height"] = dayNamesDiv_styleProps["height"] + ( 6 * parseInt( WebTools.getComputedStyle( this._weekDivArray[0], "height" ) ) );
	daysContentDiv_styleProps["top"] = 0;
	daysContentDiv_styleProps["left"] = Math.floor( ( parseInt( WebTools.getComputedStyle( container, "width" ) ) - daysContentDiv_styleProps["width"] ) / 2 );;
    WebTools.addStyleProps( daysContentDiv, daysContentDiv_styleProps );
	
	var daysHolderDiv_styleProps = {};
	daysHolderDiv_styleProps["position"] = "absolute";
	daysHolderDiv_styleProps["width"] = parseInt( WebTools.getComputedStyle( container, "width" ) );
	daysHolderDiv_styleProps["height"] = daysContentDiv_styleProps["height"];
	daysHolderDiv_styleProps["top"] = topPos;
	daysHolderDiv_styleProps["left"] = leftPos;		
	WebTools.addStyleProps( daysHolderDiv, daysHolderDiv_styleProps );
	
	return daysHolderDiv;
}



/**
 * Builds the Month selector div
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @return {DOMNode} 
 */ 
IFDSCalendarWidget.prototype.buildMonthSelector = function( container )
{
	var calendarRef = this;
	
	var selectorWidth = 130;
	var selectorHeight = 110;
	var itemHeight = 15;
	var itemWidth = 65;	
				
	var d = container.appendChild( document.createElement( "div" ) );
	if ( UTL.isIEEventModel() ) d.unselectable = "on";
	WebTools.addStyleProps( d, {position:"absolute", 
								height:selectorHeight, 
								width:selectorWidth, 
								left:parseInt( parseInt( this._mainDiv.offsetWidth ) / 2 ) - ( selectorWidth/2 ),
								top:2,
								padding:2,
								border:"1px solid black",
								background:"#FFFFE1"} );
	EvtHandler.add( d, "click", function( e ){ e.stopPropagation() } );
	EvtHandler.add( d, "blur", function( evt ){ IFDSCalendarWidget.blurHandler_monthSelector( calendarRef, evt ) } );
	if ( UTL.isMOZEventModel()  && !this._isPopup )
	{
		d.tabIndex = -1;
		d.style.MozOutlineStyle = "none";	
	}
									
	var table = d.appendChild( WebTools.buildTableElem() );
	table.unselectable = "on";
	table.style.tableLayout = "fixed";
			
	for ( var m = 0; m < 6; m++ )
	{
		var tr = table.firstChild.appendChild( document.createElement( "tr" ) );
		tr.unselectable = "on";
		
		var itemStylePropsMap = {width:itemWidth,
							     height:itemHeight,
							     padding:1,	 
							     cursor:"pointer", 
							     fontSize:10, 
							     fontFamily:"arial",
							     textTransform:"uppercase"};							 		
		var td1 = tr.appendChild( document.createElement( "td" ) );
		td1.unselectable = "on";		
		td1.setAttribute( "_monthVal", m );		
		WebTools.addStyleProps( td1, itemStylePropsMap );					 	
		td1.innerHTML = IFDSCalendarWidget.MONTH_NAME_ARRAY[m];			
		EvtHandler.add( td1, "mouseover", function( evt ){ IFDSCalendarWidget.mouseoverHandler_monthSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td1, "mouseout", function( evt ){ IFDSCalendarWidget.mouseoutHandler_monthSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td1, "click", function( evt ){ IFDSCalendarWidget.clickHandler_monthSelectorItem( calendarRef, evt ) } );
		
		var td2 = tr.appendChild( document.createElement( "td" ) );
		td2.unselectable = "on";		
		td2.setAttribute( "_monthVal", m + 6 );
		WebTools.addStyleProps( td2, itemStylePropsMap );				
		td2.innerHTML = IFDSCalendarWidget.MONTH_NAME_ARRAY[m + 6];			
		EvtHandler.add( td2, "mouseover", function( evt ){ IFDSCalendarWidget.mouseoverHandler_monthSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td2, "mouseout", function( evt ){ IFDSCalendarWidget.mouseoutHandler_monthSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td2, "click", function( evt ){ IFDSCalendarWidget.clickHandler_monthSelectorItem( calendarRef, evt ) } );	
	}		
	
	// closeBtn
	var closeBtnTR = table.firstChild.appendChild( document.createElement( "tr" ) );
	closeBtnTR.unselectable = "on";
	var closeBtnTDStylePropsMap = {height:itemHeight,
						           paddingTop:7,	 
						     	   cursor:"pointer", 
						     	   fontSize:8, 
						           fontFamily:"arial",
						           textAlign:"center",
						           textTransform:"uppercase"};
	var closeBtnTD = closeBtnTR.appendChild( document.createElement( "td" ) );
	closeBtnTD.colSpan = 2;
	closeBtnTD.unselectable = "on";
	WebTools.addStyleProps( closeBtnTD, closeBtnTDStylePropsMap );
	closeBtnTD.innerHTML = "close";
	EvtHandler.add( closeBtnTD, "click", function( evt ){ IFDSCalendarWidget.clickHandler_monthSelectorCloseBtn( calendarRef, evt ) } );	
							     
	d.style.display = "none";		
	return d;
}


/**
 * Builds the Year selector div
 *
 * @param {DOMNode} container DOMNode that the main div will be appended to
 * @return {DOMNode} 
 */
IFDSCalendarWidget.prototype.buildYearSelector = function( container )
{
	var calendarRef = this;
	
	var selectorWidth = 120;
	var selectorHeight = 90;
	var itemHeight = 15;
	var itemWidth = 40;	

	var div = container.appendChild(  document.createElement( "div" ) );		
	if ( UTL.isIEEventModel() ) div.unselectable = "on";
	WebTools.addStyleProps( div, {position:"absolute", 
								  height:selectorHeight, 
								  width:selectorWidth, 
								  left:parseInt( parseInt( this._mainDiv.offsetWidth ) / 2 ) - ( selectorWidth / 2 ),
								  bottom:2,
								  border:"1px solid black",															
								  background:"#FFFFE1"} );
	EvtHandler.add( div, "click", function( e ){ e.stopPropagation() } );
	EvtHandler.add( div, "blur", function( evt ){ IFDSCalendarWidget.blurHandler_yearSelector( calendarRef, evt ) } );
	if ( UTL.isMOZEventModel() && !this._isPopup )
	{
		div.tabIndex = -1;
		div.style.MozOutlineStyle = "none";	
	}
	
	// table to hold the years
	var table = div.appendChild( WebTools.buildTableElem() );
	table.unselectable = "on";
	WebTools.addStyleProps( table, {position:"absolute", top:0, left:20, tableLayout:"fixed"} );  
	for ( var i = 0; i < 5; i++ )
	{
		var tr = table.firstChild.appendChild( document.createElement( "tr" ) );
		tr.unselectable = "on";
		var tdStylePropsMap = {fontSize:10, 
		                       cursor:"pointer", 
		                       padding:1, 
		                       fontFamily:"arial",
		                       textAlign:"center", 		                      
		                       height:itemHeight, 
		                       width:itemWidth};
		var td1 = tr.appendChild( document.createElement( "td" ) );
		td1.unselectable = "on";		
		WebTools.addStyleProps( td1, tdStylePropsMap );
		EvtHandler.add( td1, "mouseover", function( evt ){ IFDSCalendarWidget.mouseoverHandler_yearSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td1, "mouseout",  function( evt ){ IFDSCalendarWidget.mouseoutHandler_yearSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td1, "click",     function( evt ){ IFDSCalendarWidget.clickHandler_yearSelectorItem( calendarRef, evt ) } );		
		
		var td2 = tr.appendChild( document.createElement( "td" ) );
		td2.unselectable = "on";		
		WebTools.addStyleProps( td2, tdStylePropsMap );
		EvtHandler.add( td2, "mouseover", function( evt ){ IFDSCalendarWidget.mouseoverHandler_yearSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td2, "mouseout",  function( evt ){ IFDSCalendarWidget.mouseoutHandler_yearSelectorItem( calendarRef, evt ) } );
		EvtHandler.add( td2, "click",     function( evt ){ IFDSCalendarWidget.clickHandler_yearSelectorItem( calendarRef, evt ) } );				
	}
	
	// closeBtn
	var closeBtnTR = table.firstChild.appendChild( document.createElement( "tr" ) );
	closeBtnTR.unselectable = "on";
	var closeBtnTDStylePropsMap = {height:itemHeight,
						           paddingTop:4,	 
						     	   cursor:"pointer", 
						     	   fontSize:8, 
						           fontFamily:"arial",
						           textAlign:"center",
						           textTransform:"uppercase"};
	var closeBtnTD = closeBtnTR.appendChild( document.createElement( "td" ) );
	closeBtnTD.colSpan = 2;
	closeBtnTD.unselectable = "on";
	WebTools.addStyleProps( closeBtnTD, closeBtnTDStylePropsMap );
	closeBtnTD.innerHTML = "close";
	EvtHandler.add( closeBtnTD, "click", function( evt ){ IFDSCalendarWidget.clickHandler_yearSelectorCloseBtn( calendarRef, evt ) } );	
	
	// prev decade btn
	var prevDecadeBtn = div.appendChild( document.createElement( "div" ) );
	prevDecadeBtn.unselectable = "on";
	WebTools.addStyleProps( prevDecadeBtn, {position:"absolute", top:27, left:5, cursor:"pointer"} );
	prevDecadeBtn.innerHTML = "&laquo;";
	EvtHandler.add( prevDecadeBtn, "click", function( evt ){ IFDSCalendarWidget.clickHandler_prevDecadeBtn( calendarRef, evt ) } );
	
	// next decade btn
	var nextDecadeBtn = div.appendChild( document.createElement( "div" ) );
	nextDecadeBtn.unselectable = "on";	
	WebTools.addStyleProps( nextDecadeBtn, {position:"absolute", top:27, right:5, cursor:"pointer"} );
	nextDecadeBtn.innerHTML = "&raquo;";
	EvtHandler.add( nextDecadeBtn, "click", function( evt ){ IFDSCalendarWidget.clickHandler_nextDecadeBtn( calendarRef, evt ) } );
					
	div.style.display = "none";			
	return div;
}


/**
 * Updates the calendar to display the specified month/year
 *
 * @param {number} month value between 0 (jan) and 11 (dec)
 * @param {number} year
 */
IFDSCalendarWidget.prototype.setMonth = function( month, year )
{
	if ( month > IFDSCalendarWidget.MONTH_NAME_ARRAY.length || month < 0 )
	{
		throw new Error( Err.genErrMsg( "invalid month value", "setMonth()", "IFDSCalendarWidget.js" ) );
	} 
	
	this._monthLbl.innerHTML 	= IFDSCalendarWidget.MONTH_NAME_ARRAY[month];
	this._monthLbl.setAttribute( "_monthVal", month );
	this._yearLbl.innerHTML	 	= year;
	this._yearLbl.setAttribute( "_yearVal",	year );
	
	// populate the days
			
	// store firstDayOfMonth, to use as reference while iterating thru days
	var firstDayOfMonth = new Date( year, month, 1 );
			
	// initiallly set to first day of month
	var curDay = new Date( year, month, 1 );
	// push back to the sunday prior
	curDay.setDate( 1 - firstDayOfMonth.getDay() );
					
	// iterate thru the weeks (6) of the calendar month						
	for ( var w = 0; w < this._weekDivArray.length; w++ )
	{								
		// iterate thru the days of the week
		var daysSpanArray = this._weekDivArray[w].childNodes;			
		for ( var d = 0; d < daysSpanArray.length; d++ )
		{
			daysSpanArray[d].setAttribute( "_dateVal", curDay.toDateString() );
			daysSpanArray[d].innerHTML = curDay.getDate();
			daysSpanArray[d].className = this._styleClassMap["dayCell"];
							
			var today = new Date();
			if ( curDay.getMonth() != firstDayOfMonth.getMonth() )
			{
				daysSpanArray[d].className += " " + this._styleClassMap["prev_or_nextMonth"];
			}
			else if ( curDay.toDateString() == today.toDateString() )
			{
				daysSpanArray[d].className += " " + this._styleClassMap["today"];
			}
			
			// set any "status indicators" (note: these are mutually exclusive)            						
			if ( this._selectedDate && curDay.toDateString() == this._selectedDate.toDateString() )
			{
				daysSpanArray[d].className += " " + this._styleClassMap["selected"];
			} 
			else
			{
				daysSpanArray[d].className += " " + this._styleClassMap["normal"];
			}
			
			curDay.setDate( curDay.getDate() + 1 );
		}
	}	  
}


/**
 * Opens the Month Selector div
 */
IFDSCalendarWidget.prototype.openMonthSelector = function()
{
	this._monthSelectorDiv.style.display = "block";
	
	if ( !this._isPopup )
	{
		// explicity set focus to month selector
		this._monthSelectorDiv.focus();
	}				
}


/**
 * Closes the Month Selector div
 */
IFDSCalendarWidget.prototype.closeMonthSelector = function()
{
	this._monthSelectorDiv.style.display = "none";		
}


/**
 * Returns true/false if the Month Selector div is open
 *
 * @return {boolean} 
 */
IFDSCalendarWidget.prototype.isMonthSelectorOpen = function()
{
	return ( this._monthSelectorDiv.style.display == "block" );
}


/**
 * Opens the Year Selector div
 */
IFDSCalendarWidget.prototype.openYearSelector = function()
{	
	var curYearVal = parseInt( this._yearLbl.getAttribute( "_yearVal" ) );	
	this.populateYearSelector( Math.floor( curYearVal / 10 ) * 10 ) 
	this._yearSelectorDiv.style.display = "block";
	
	if ( !this._isPopup )
	{
		// explicitly set focus to year selector
		this._yearSelectorDiv.focus();
	}		 	
}




/**
 * Populates the year table of the Year Selector div
 *
 * @param {number} startYear
 */
IFDSCalendarWidget.prototype.populateYearSelector = function( startYear )
{
	if ( startYear < 0 || startYear > IFDSCalendarWidget.MAX_YEAR - 9 )
	{
		throw new Error( Err.genErrMsg( "invalid start year", "populateYearSelector()", "IFDSCalendarWidget.js" ) );
	}
	 	
	var yearTable = this._yearSelectorDiv.firstChild;			
	var yearRows = yearTable.firstChild.childNodes;
	for( var i = 0; i < 5; i++ )
	{		
		var td1 = yearRows[i].childNodes[0];
		td1.innerHTML = "" + ( startYear + i );
		var td2 = yearRows[i].childNodes[1];
		td2.innerHTML = "" + ( startYear + i + 5 );		
	}
}


/**
 * Closes the Year Selector div
 */
IFDSCalendarWidget.prototype.closeYearSelector = function()
{
	this._yearSelectorDiv.style.display = "none";				
}


/**
 * Returns true/false if the Year Selector div is open
 *
 * @return {boolean} 
 */
IFDSCalendarWidget.prototype.isYearSelectorOpen = function()
{
	return ( this._yearSelectorDiv.style.display == "block" );
}


/**
 * Returns true/false if the calendar is visible
 *
 * @return {boolean} 
 */	
IFDSCalendarWidget.prototype.isVisible = function()
{
	return this._mainDiv.style.display == "block";
}


/**
 * Sets the visibilty of this calendar widget instance
 *
 * @param {boolean} makeVisible
 */
IFDSCalendarWidget.prototype.setVisible = function( makeVisible )
{
	if ( makeVisible )
	{
		this._mainDiv.style.display = "block";
	}
	else
	{
		if ( this.isYearSelectorOpen() )
		{
			this.closeYearSelector();
		}
		
		if ( this.isMonthSelectorOpen() )
		{
			this.closeMonthSelector();
		}
		
		this._mainDiv.style.display = "none";
	}
}


/**
 * Sets the position (top/left) of this calendar widget instance. Also can relocate within
 * the DOM by specifying container
 * <br/>
 * Note: assumes calendarHolder has position="absolute", and also top, and left will be
 * in reference to the node containing the calendar 
 */
IFDSCalendarWidget.prototype.setPosition = function( posObj )
{   
    posObj.container = ( posObj.container ?  posObj.container : document.body );     
	if ( posObj.container != this._mainDiv.parentNode )
	{
		this._mainDiv.parentNode.removeChild( this._mainDiv );
		posObj.container.appendChild( this._mainDiv );		
	}
	
	this._mainDiv.style.top = posObj.top;
	this._mainDiv.style.left = posObj.left;
	
	if ( posObj.zIndex )
	{
	    this._mainDiv.style.zIndex = posObj.zIndex;
	}
}


/**
 * Sets the selectedDate of this calendar
 *
 * @param {Date} dateObj
 */
IFDSCalendarWidget.prototype.setSelectedDate = function( dateObj )
{	
	this._selectedDate = dateObj;
	
	// see if need to redraw the calendar	
	if ( this._monthLbl.getAttribute( "_monthVal" ) == dateObj.getMonth() 
	     && this._yearLbl.getAttribute( "_yearVal" ) == dateObj.getFullYear() )	 
	{
		this.setMonth( dateObj.getMonth(), dateObj.getFullYear() ); 
	} 
}


/**
 * Sets the _onDateSelectedFunction - the function to call when a user
 * selects a date within the calendar. The function should expect a single param of type Date.
 *
 * @param {function} fn
 */
IFDSCalendarWidget.prototype.setOnDateSelectedFunction = function( fn )
{
	this._onDateSelectedFunction = fn;
}


/**
 * @return {integer}  
 */
IFDSCalendarWidget.prototype.getHeight = function()
{
	// IE
	if ( this._mainDiv.currentStyle )
	{
		return parseInt( this._mainDiv.currentStyle.height );
	}
	// MOZ
	else if ( window.getComputedStyle )
	{
		return parseInt( window.getComputedStyle( this._mainDiv, null ).height );
	}
	// OTHER
	else
	{
		throw new Error( Err.genErrMsg( "height cannot be determined - browser issue", "getHeight()", "IFDSCalendarWidget.js" ) );
	}
}


/**
 * @return {integer} 
 */
IFDSCalendarWidget.prototype.getWidth = function()
{
	// IE
	if ( this._mainDiv.currentStyle )
	{
		return parseInt( this._mainDiv.currentStyle.width );
	}
	// MOZ
	else if ( window.getComputedStyle )
	{
		return parseInt( window.getComputedStyle( this._mainDiv, null ).width );
	}
	// OTHER
	else
	{
		throw new Error( Err.genErrMsg( "width cannot be determined - browser issue", "getWidth()", "IFDSCalendarWidget.js" ) );
	}
}


/**
 * Sets the associated datepicker. Only meant for use when calendar is used as a popup
 * @param {object} datepicker  
 */
IFDSCalendarWidget.prototype.setAssocDatepicker = function( datepicker )
{
	this._assocDatepicker = datepicker;
}


/**
 * Returns the associated datepicker. Only meant for use when calendar is used as a popup
 * @return {object}  
 */
IFDSCalendarWidget.prototype.getAssocDatepicker = function()
{
	return this._assocDatepicker;
}


/**
 * Sets the focus to the calendar (ie. the main div).
 * This would only make sense in MOZ. 
 */
IFDSCalendarWidget.prototype.focus = function()
{
	this._mainDiv.focus();
}
