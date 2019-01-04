/**
 * @fileoverview Contains source for IFDSDatepicker, used for creating a datefield input
 * with calendar widget
 * <br/>
 * REQUIRES: JSLib/Err.js, JSLib/WebTools.js, JSLib/EvtHandler.js, JSLib/UTL.js, WebComps/IFDSCalendarWidget.js
 *
 *
 * @author walkerro
 */



/**
 * Static class used to load and keep references to the IFDSDatepickers
 */
var IFDSDatepickerManager = new function()
{
    /**
     * @private
     */
    var _datepickerMap      = {};


    /**
     * @private
     */
    var _dateFormat         = null;


    /**
     * @private
     */
    var _calendar           = null;


    /**
     *
     */
    this._dateFldToGetFocus = null;


    /**
     * Sets the dateFormat - only should be called during init. Throws error when dateForamtString
     * doesn't match known formats
     *
     * @param {string} dateFormatString
     */
    function setDateFormat( dateFormatString )
    {
        if ( dateFormatString != IFDSDatepicker.DATEFORMAT_DMY &&
             dateFormatString != IFDSDatepicker.DATEFORMAT_MDY &&
             dateFormatString != IFDSDatepicker.DATEFORMAT_ISO &&
             dateFormatString != IFDSDatepicker.DATEFORMAT_YYYYMMDD )
        {
            throw new Error( Err.genErrMsg( "invalid dateFormatString: " + dateFormatString, "setDateFormat()", "IFDSDatepicker.js" ) );
        }
        _dateFormat = dateFormatString;
    }


    /**
     * Initializes the datepicker manager, identifying and building all the datepickers
     * and initializing the Calendar
     *
     * @param {string} dateFormat
     * @param {string} calendarStyleClass
     * @param {string} calendarBtnStyleClass
     */
    this.init = function( dateFormat, calendarStyleClass, calendarBtnStyleClass, getCalendarPositionFn )
    {
        _calendar = new IFDSCalendarWidget( document.body, calendarStyleClass, true, true );
        _calendar.setVisible( false );

        setDateFormat( dateFormat );

        var inputElementArray = UTL.getElem( "input", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME );

        for ( var i = 0; i < inputElementArray.length; i++ )
        {
            var input = inputElementArray[i];
            if ( input.getAttribute( "ifdsDatepicker" ) == "true" )
            {
                // check for id, and non-duplicate id
                if ( input.id == "" || _datepickerMap[input.id] )
                {
                    throw new Error( Err.genErrMsg( "datepicker missing unique id", "init()", "IFDSDatepicker.js" ) );
                }

                // build datepicker object
                _datepickerMap[input.id] = new IFDSDatepicker( input, calendarBtnStyleClass, getCalendarPositionFn );
            }
        }
    }


    /**
     * Returns a reference a datepicker object associated with the given id
     *
     * @param {string} daterpickerID
     * @return {object}
     */
    this.getDatepicker = function( datepickerID )
    {
        return _datepickerMap[datepickerID];
    }


    /**
     * Returns a string of the dateFormat
     *
     * @return {object}
     */
    this.getDateFormat = function()
    {
        return _dateFormat;
    }


    /**
     * Returns reference to the calendar widget used with the datepickers
     *
     * @return {object}
     */
    this.getCalendar = function()
    {
        return _calendar;
    }


    /**
     *
     */
    this.refocusDateFld = function( dateFld )
    {
        this._dateFldToGetFocus = dateFld;
        setTimeout( "try{IFDSDatepickerManager._dateFldToGetFocus.focus()}catch(e){}", 10 );
    }
}







/**
 * @class Represents an IFDSDatepicker - DIV, with date field input, and calendar btn
 *
 * @param {DOMElement} datepickerDiv reference to a div element to be used as datepicker holder
 */
function IFDSDatepicker( datepickerInput, calendarBtnStyleClass, getCalendarPositionFn )
{
    var datepickerRef = this;

    EvtHandler.add( datepickerInput, "blur",    function( evt ){ IFDSDatepicker.blurHandler_dateFld( datepickerRef, evt ) } );
    EvtHandler.add( datepickerInput, "focus",   function( evt ){ IFDSDatepicker.focusHandler_dateFld( datepickerRef, evt ) } );
    EvtHandler.add( datepickerInput, "keydown", function( evt ){ IFDSDatepicker.keydownHandler_dateFld( datepickerRef, evt ) } );
    EvtHandler.add( datepickerInput, "click",   function( evt ){ IFDSDatepicker.clickHandler_dateFld( datepickerRef, evt ) } );
    this._dateFld = datepickerInput;

    // build calendar btn component of datepicker
    var calendarBtn = datepickerInput.parentNode.appendChild( document.createElement( "span" ) );
    calendarBtn.id = datepickerInput.id + "_calendarBtn";
    calendarBtn.className = calendarBtnStyleClass;
    var calendarBtn_styleProps = { position:"absolute",
                                   top:parseInt( WebTools.getComputedStyle( datepickerInput, "top" ) ) /*+ 1*/,
                                   left:parseInt( WebTools.getComputedStyle( datepickerInput, "left" ) ) + parseInt( WebTools.getComputedStyle( datepickerInput, "width" ) ) - parseInt( WebTools.getComputedStyle( calendarBtn, "width" ) ) };

    // if the field is disabled
    if (WebTools.getComputedStyle(this._dateFld, "backgroundColor") == "gray")
    {
        calendarBtn_styleProps.backgroundColor = "gray";
    }

    WebTools.addStyleProps( calendarBtn, calendarBtn_styleProps );
    EvtHandler.add( calendarBtn, "click", function( evt ){ IFDSDatepicker.clickHandler_calendarBtn( datepickerRef, evt ) } )
    this._calendarBtn = calendarBtn;

    this._dateFld.style.width = parseInt( WebTools.getComputedStyle( this._dateFld, "width" ) ) - parseInt( WebTools.getComputedStyle( this._calendarBtn, "width" ) );

    // validate datepickerInput initial value, if exists
    if ( datepickerInput.value )
    {
        var dateObj = IFDSDatepicker.buildDateObj( datepickerInput.value, IFDSDatepickerManager.getDateFormat() );
        if ( dateObj )
        {
            this.setDateValue( dateObj, IFDSDatepickerManager.getDateFormat(), false /*ignore callback*/ );
        }
        else
        {
            throw new Error( Err.genErrMsg( "invalid initial date value for " + datepickerInput.id, "IFDSDatepicker()", "IFDSDatepicker.js" ) );
        }
    }    

    // disable dateicker control, if input field was set to disabled
    if( datepickerInput.disabled )
    {
        this.disable();
    }

    this._getCalendarPosition = ( getCalendarPositionFn != null ? getCalendarPositionFn : IFDSDatepicker.getCalendarPosition_baseFn );
    
    this._valueSetCallback = this._dateFld.valueSetCallback;
    this._curDateObj = null;
}


/**
 * Identify DMY date format
 * @type string
 */
IFDSDatepicker.DATEFORMAT_DMY = "dmy";


/**
 * Identify MDY date format
 * @type string
 */
IFDSDatepicker.DATEFORMAT_MDY = "mdy";


/**
 * Identify ISO date format
 * @type string
 */
IFDSDatepicker.DATEFORMAT_ISO = "iso";


/**
 * Identify yyyymmdd date format
 * @type string
 */
IFDSDatepicker.DATEFORMAT_YYYYMMDD = "yyyymmdd";


/**
 * @type string
 */
IFDSDatepicker.CALENDAR_POS_ABOVE = "above";


/**
 * @type string
 */
IFDSDatepicker.CALENDAR_POS_BELOW = "below";



IFDSDatepicker.getCalendarPosition_baseFn = function( dateFld )
{
    var posObj = {};
    posObj["container"] = dateFld.parentNode;

    if ( dateFld.style.top )
    {
        posObj["top"] = parseInt( dateFld.style.top ) + parseInt( dateFld.offsetHeight );
    }
    else
    {
        posObj["top"] = parseInt( WebTools.getComputedStyle( dateFld, "top" ) ) + parseInt( dateFld.offsetHeight );;
    }

    if ( dateFld.style.left )
    {
        posObj["left"] = parseInt( dateFld.style.left ) + parseInt( dateFld.offsetWidth );
    }
    else
    {
        posObj["left"] = parseInt( WebTools.getComputedStyle( dateFld, "left" ) )  + parseInt( dateFld.offsetWidth );
    }

    return posObj;
}


/**
 * Static function for checking validity of a dateString, against the given dateformat
 *
 * @param {string} dateString
 * @param {string} dateFormat
 */
IFDSDatepicker.isValidDateValue = function( dateString, dateFormat )
{
    if ( dateString != "" )
    {
        return ( IFDSDatepicker.buildDateObj( dateString, dateFormat ) != null );
    }
    return true;
}


/**
 * Static function for constructing a dateString, with given format, from a Date object
 *
 * @param {Date} dateObj
 * @param {string} dateFormat
 */
IFDSDatepicker.buildDateString = function( dateObj, dateFormat )
{
    if ( dateObj && dateObj.getDate )
    {
    	var dateVal = dateObj.getUTCDate();
    	var dateStr = ( dateVal <= 9 ? "0" + dateVal : dateVal );
    	
    	var monVal = dateObj.getUTCMonth() + 1;
    	var monStr = ( monVal <= 8 ? "0" + monVal : monVal );
    	
    	var yearVal = dateObj.getUTCFullYear();
    	var yearStr = "";
    	if ( yearVal <= 9 )
    	{
    		yearStr = "000" + yearVal;
    	}
    	else if ( yearVal > 9 && yearVal <= 99 )
    	{
    		yearStr = "00" + yearVal;
    	}
    	else if ( yearVal > 99 && yearVal <= 999 )
    	{
    		yearStr = "0" + yearVal;
    	}
    	else
    	{
    		yearStr = yearVal;
    	}
    	                
        switch( dateFormat )
        {
            case IFDSDatepicker.DATEFORMAT_DMY:
            {
                return ( dateStr + "/" + monStr + "/" + yearStr );
            }
            case IFDSDatepicker.DATEFORMAT_MDY:
            {
                return ( monStr + "/" + dateStr + "/" + yearStr );
            }
            case IFDSDatepicker.DATEFORMAT_ISO:
            {
                return ( yearStr + "-" + monStr + "-" + dateStr );
            }
            case IFDSDatepicker.DATEFORMAT_YYYYMMDD:
            {
                return ( yearStr + monStr + dateStr );
            }
            default:
            {
                throw new Error( Err.genErrMsg( "invalid dateFormat", "buildDateString()", "IFDSDatepicker" ) );
            }
        }
    }
    else
    {
        throw new Error( Err.genErrMsg( "invalid dateObj", "buildDateString()", "IFDSDatepicker" ) );
    }
}


/**
 * Static function for constructing a Date object using the given dateString/dateFormat.
 * Returns null if the dateString is not valid.
 *
 * @param {string} dateString
 * @param {string} dateFormat
 */
IFDSDatepicker.buildDateObj = function( dateString, dateFormat )
{
    var datePartArray = [];
    if ( dateString.indexOf( "/" ) != -1 )
    {
        datePartArray = dateString.split( "/" );
    }
    else if ( dateString.indexOf( "-" ) != -1 )
    {
        datePartArray = dateString.split( "-" );
    }
    else
    {
        if ( dateFormat == IFDSDatepicker.DATEFORMAT_YYYYMMDD )
        {
            datePartArray[0] = dateString.substring( 0, 4 );
            datePartArray[1] = dateString.substring( 4, 6 );
            datePartArray[2] = dateString.substring( 6 );
        }
        else
        {
            return null;
        }
    }

    var dayStr = "";
    var monStr = "";
    var yearStr = "";
    switch( dateFormat )
    {
        case IFDSDatepicker.DATEFORMAT_DMY:
        {
            dayStr      = datePartArray[0];
            monStr      = datePartArray[1];
            yearStr     = datePartArray[2];
            break;
        }
        case IFDSDatepicker.DATEFORMAT_MDY:
        {
            dayStr      = datePartArray[1];
            monStr      = datePartArray[0];
            yearStr     = datePartArray[2];
            break;
        }
        case IFDSDatepicker.DATEFORMAT_ISO:
        {
            dayStr      = datePartArray[2];
            monStr      = datePartArray[1];
            yearStr     = datePartArray[0];
            break;
        }
        case IFDSDatepicker.DATEFORMAT_YYYYMMDD:
        {
            dayStr      = datePartArray[2];
            monStr      = datePartArray[1];
            yearStr     = datePartArray[0];
            break;
        }
        default:
        {
            throw new Error( Err.genErrMsg( "invalid dateFormat", "buildDateString()", "IFDSDatepicker" ) );
        }
    }       

    var dayVal = null;
    if( !dayStr.match(/\D/g) && ( dayStr.length == 2 || dayStr.length == 1 ) )
    {
        var temp = ( dayStr.charAt(0) == "0" ) ? parseInt( dayStr.charAt(1) ) : parseInt( dayStr );
        dayVal = ( temp >= 1 ) ? temp : null;
    }

    var monVal = null;
    if( !monStr.match(/\D/g) && ( monStr.length == 2 || monStr.length == 1 ) )
    {
        var temp = ( monStr.charAt(0) == "0" ) ? parseInt( monStr.charAt(1) ) : parseInt( monStr );
        monVal = ( temp >= 1 && temp <= 12 ) ?  temp - 1 :  null;
    }

    var yearVal = null;
    if( yearStr && !yearStr.match(/\D/g) && yearStr.length == 4 )
    {
        var temp = parseInt( yearStr );
        yearVal = ( temp >= 1 && temp <= 9999 ) ? temp : null;
    }
    

    if ( dayVal != null && monVal != null && yearVal != null )
    {
        if ( dayVal <= IFDSDatepicker.getNumDaysInMonth( monVal, yearVal ) )
        {
        	var date = new Date();
        	date.setUTCFullYear( yearVal, monVal, dayVal );        	    		
            return date;
        }
        else
        {
            return null;
        }
    }
    else
    {
        return null;
    }
}



/**
 * Static function for determining the number of days in the given month/year
 * Returns null if the dateString is not valid.
 *
 * @param {number} monVal value between 0 and 11
 * @param {string} dateFormat
 */
IFDSDatepicker.getNumDaysInMonth = function( monVal, yearVal )
{
    if ( monVal > -1 && monVal < 12 && yearVal > -1 && yearVal <= 9999 )
    {
        var max = 31;
        var min = 28;
        var d = new Date( yearVal, monVal, min );
        for ( var i = min + 1; i < max + 1; i++ )
        {
            d.setDate( i )
            if ( d.getMonth() != monVal )
            {
                return i - 1;
            }
        }
        return i;
    }
    else
    {
        throw new Error( Err.genErrMsg( "invalid month and/or year", "getNumDaysInMonth()", "IFDSDatepicker.js" ) );
    }
}


/**
 * EVENT HANDLER - blur handler for a date picker date field
 */
IFDSDatepicker.blurHandler_dateFld = function( datepickerRef, evt )
{
    var dateFld = evt.currentTarget;

    if ( !IFDSDatepicker.isValidDateValue( dateFld.value, IFDSDatepickerManager.getDateFormat() ) )
    {
        // forces focus to remain on the dateFld if its value isn't valid
        // note: we have to do a bit of hack to make this work correctly - use IFDSDatepickerManager to keep track of the field
        IFDSDatepickerManager.refocusDateFld( dateFld )        
    }
    else
    {
    	var datepicker = IFDSDatepickerManager.getDatepicker( dateFld.id );
        if ( dateFld.value )
        {
        	var dateObj = IFDSDatepicker.buildDateObj( dateFld.value, IFDSDatepickerManager.getDateFormat() );        	
        	if ( datepicker._curDateObj == null || dateObj.getTime() != datepicker._curDateObj.getTime() )
			{        	
            	datepicker.setDateValue( dateObj, IFDSDatepickerManager.getDateFormat() );
			}
        }
        else if ( datepicker._curDateObj != null )
        {
        	datepicker.setDateValue( null );
        }
    }

    var calendar = IFDSDatepickerManager.getCalendar();
    if ( calendar.isVisible() )
    {
        calendar.setVisible( false );
        // after closing the calendar popup, we want to re-enable the calendarBtn which
        // opened the popup, which requires a delay in order to allow user to click the calendarBtn
        // to close the calendar

        // this is a bit of a hack - in MOZ timeouts are run at global scope
        setTimeout( "IFDSDatepickerManager.getDatepicker( \"" + datepickerRef._dateFld.id + "\" ).enableCalendarBtn()", 125 );
    }
}


/**
 * EVENT HANDLER - focus handler for a date picker date field
 */
IFDSDatepicker.focusHandler_dateFld = function( datepickerRef, evt )
{

}


/**
 * EVENT HANDLER - keydown handler for a date picker date field
 */
IFDSDatepicker.keydownHandler_dateFld = function( datepickerRef, evt )
{
    var calendar = IFDSDatepickerManager.getCalendar();
    if ( calendar.isVisible() )
    {
        calendar.setVisible( false );
        datepickerRef.enableCalendarBtn();
    }
}


/**
 * EVENT HANDLER - click handler for a date picker date field
 */
IFDSDatepicker.clickHandler_dateFld = function( datepickerRef, evt )
{
    var calendar = IFDSDatepickerManager.getCalendar();
    if ( calendar.isVisible() )
    {
        calendar.setVisible( false );
        datepickerRef.enableCalendarBtn();
    }
}




/**
 * EVENT HANDLER - click handler for a date picker calendar btn
 */
IFDSDatepicker.clickHandler_calendarBtn = function( datepickerRef, evt )
{
    var calendarBtn = evt.currentTarget;
    var calendar = IFDSDatepickerManager.getCalendar();

    if ( !datepickerRef.isCalendarBtnDisabled() )
    {
        // calendar has already been associated with datepickerRef (ie. not first time clicking this calendarBtn)
        if ( calendar.getAssocDatepicker() == datepickerRef )
        {
            var enteredDate = IFDSDatepicker.buildDateObj( datepickerRef._dateFld.value, IFDSDatepickerManager.getDateFormat() );
            if ( enteredDate )
            {
                calendar.setSelectedDate( enteredDate );
                calendar.setMonth( enteredDate.getUTCMonth(), enteredDate.getUTCFullYear() );
            }
            else
            {
                var today = new Date();
                calendar.setMonth( today.getUTCMonth(), today.getUTCFullYear() );
            }

            datepickerRef.disableCalendarBtn();
            calendar.setVisible( true );
            if ( UTL.isIEEventModel() )
            {
                datepickerRef._dateFld.focus();
            }
            else if ( UTL.isMOZEventModel() )
            {
                calendar.focus();
            }
        }
        // calendar is currently associated with another datepicker or none at all
        else
        {
            // if calendar is not associated with another datepicker
            // OR its currently associated datepicker has a valid date value
            if ( calendar.getAssocDatepicker() == null
                 || IFDSDatepicker.isValidDateValue( calendar.getAssocDatepicker().getDateValue(), IFDSDatepickerManager.getDateFormat() ) )
            {
                calendar.setAssocDatepicker( datepickerRef );
                var enteredDate = IFDSDatepicker.buildDateObj( datepickerRef._dateFld.value, IFDSDatepickerManager.getDateFormat() );
                if ( enteredDate )
                {
                    calendar.setSelectedDate( enteredDate );
                    calendar.setMonth( enteredDate.getUTCMonth(), enteredDate.getUTCFullYear() );
                }
                else
                {
                    var today = new Date();
                    calendar.setMonth( today.getUTCMonth(), today.getUTCFullYear() );
                }

                //var calendarBtnPos = WebTools.calcElemPos( calendarBtn );
                var calendarBtnPos = {};
                calendarBtnPos.top = parseInt( WebTools.getComputedStyle( calendarBtn, "top" ) );
                calendarBtnPos.left = parseInt( WebTools.getComputedStyle( calendarBtn, "left" ) );
//              calendar.setPosition( calendarBtnPos.top + calendarBtn.offsetHeight + 2,
//                                    calendarBtnPos.left - 10, calendarBtn.parentNode );
                calendar.setPosition( datepickerRef._getCalendarPosition( datepickerRef._dateFld ) );

                calendar.setOnDateSelectedFunction( function( dateObj ){ IFDSDatepicker.onDateSelected( datepickerRef, dateObj ) } );

                datepickerRef.disableCalendarBtn();
                calendar.setVisible( true );
                if ( UTL.isIEEventModel() )
               {
                    datepickerRef._dateFld.focus();
                }
                else if ( UTL.isMOZEventModel() )
                {
                    calendar.focus();
                }
            }
        }
    }
}


/**
 * Function called by CalendarWidget when a date is selected
 */
IFDSDatepicker.onDateSelected = function( datepickerRef, dateObj )
{
    IFDSDatepickerManager.getCalendar().setVisible( false );
    datepickerRef.enableCalendarBtn();
    datepickerRef.setDateValue( dateObj, IFDSDatepickerManager.getDateFormat() );
}


/**
 * Enables the datepicker (sets dateFld.disabled to false)
 */
IFDSDatepicker.prototype.enable = function()
{
    this._dateFld.disabled = false;
    this.enableCalendarBtn();
}


/**
 * Disables the datepicker (sets dateFld.disabled to true)
 */
IFDSDatepicker.prototype.disable = function()
{
    this._dateFld.disabled = true;
    this.disableCalendarBtn();
}


/**
 * Returns true if the dateFld is disabled
 */
IFDSDatepicker.prototype.isDisabled = function()
{
    return ( this._dateFld.disabled );
}


/**
 * Enables the datepicker (sets dateFld.disabled to false)
 */
IFDSDatepicker.prototype.enableCalendarBtn = function()
{
    this._calendarBtn.disabled = false;
}


/**
 * Disables the datepicker (sets dateFld.disabled to true)
 */
IFDSDatepicker.prototype.disableCalendarBtn = function()
{
    this._calendarBtn.disabled = true;
}


/**
 * Returns true if the dateFld is disabled
 */
IFDSDatepicker.prototype.isCalendarBtnDisabled = function()
{
    return ( this._calendarBtn.disabled );
}


/**
 * Returns the value in the datepicker dateFld
 */
IFDSDatepicker.prototype.getDateValue = function( dateFormat )
{
    return this._dateFld.value;
}


/**
 * Sets the value of the datepicker dateFld
 * @param {Date} dateObj
 * @param {string} dateFormat
 */
IFDSDatepicker.prototype.setDateValue = function( dateObj, dateFormat, runCallback )
{	
	runCallback = ( runCallback == null ?  true : runCallback );
	
	if ( dateObj != null )
	{
    	this._dateFld.value = IFDSDatepicker.buildDateString( dateObj, dateFormat );
	}
	else
	{
		this._dateFld.value = "";
	}
    this._curDateObj = dateObj;
    
    if ( runCallback && this._valueSetCallback  )
    {
    	eval( this._valueSetCallback );    
    }
}