/** 
 * @fileoverview Contains source for identifying, building and applying SuggestField dropdown functionality
 * <br/>
 * REQUIRES: JSLib: {Err.js, UTL.js, XML.js, EvtHandler.js, KeyMap.js, HTTP.js} 
 
 *  
 * @author walkerro
 * @version 0.1 
 */


/** 
 * Static class - no constructor permitted
 * 
 * @class Static class used to hold the source code and functions related to identifying, building and
 * applying the SearchField dropdown functionality.
 * <br/> 
 * Note: The init method of is added to the onload event listener of the document.
 * <br/>
 * The use of SuggestField requires use of number of custom html attributes added to the text input
 * being used as a suggest field:
 * <ul>
 *	<li> suggestField (required) - used to indicate this field is meant for suggest field use (must set to "true") </li>
 *	<li> searchURL (required) - exact url used to make search request, formatted so that the search string
 * can be appended to the end (ie. ending in "&amp;searchVal=" </li>
 *  <li> displayItems (required) - comma deliminated string (no spaces) used to indicate which fields in the response
 * xml are to be displayed in the dropdown. </li>
 *  <li> dropdownClass - className value to be used to style the dropdownDisplay </li>
 *  <li> contentClass - className value to be used to style items displayed within the dropdown </li>
 *  <li> highlightClass - className value to be used to style the highlighting within the dropdown </li>
 * </ul>
 * <br/>
 * sample:
 * &lt; input   suggestField="true" 
 *				type="text" 
 *				id="suggestFieldTest1" 
 *				size="40"
 *				dropdownClass="Dropdown"
 *				contentClass="DropdownContent" 
 *				highlightClass="DropdownHighlight"
 *				searchURL="...&searchVal="
 *				displayItems="dispValue,dispValue2"/&gt; 
 */
var SuggestFieldManager = new function()
{
 	/**
	 * A self reference, required where "this" not available (ie. in private functions) 	 
	 * @private  
	 */
	var _self = this;
	
	/**
	 * Reference to the object used for the DropdownDisplay object. Possible to create multiple objects,
	 * if ever required 	 
	 * @private  
	 */
	var _dropdownDisplay = null;
	
	/**
	 * Reference to the current SuggestField control 	 
	 * @private  
	 */
	var _currentControl = null;
	
	/**
	 * Stores the most recent search string - used to avoid re-searching 	 
	 * @private  
	 */
	var _lastSearchStr = "";
	
	/**
	 * Timer object reference used in scheduling search calls 	 
	 * @private  
	 */
	var _searchTimer = null;
	
	
	var _searchRunning = false;
	
	
	var _prevDataObj = null;
	
	 


	
	function closeDropdown()
	{
	    _dropdownDisplay.setState( _dropdownDisplay.CLOSED_STATE );
	}



	/**
	 * Function which schedules actual search call. Before doing so, checks that the
	 * search string being sent is not a repeat 	 
	 * @private  
	 */	
	function scheduleSearchCall()
	{		
		if(UTL.trimString( _currentControl.value ) != _lastSearchStr)
		{		    
			// clear any search call still pending
			cancelScheduledSearchCall();
			
			// prevent any running search from continuing
			_searchRunning = false;
			
			// schedule new search call			
			_searchTimer = setTimeout( doSearch, 1000 );			
						
			_currentControl.setCapture();
		}	
	}
	
	
	function cancelScheduledSearchCall()
	{
	    clearTimeout( _searchTimer );
	    _searchTimer = null;

        if ( _currentControl != null )
        {	    	    
	        _currentControl.releaseCapture();
	    }
	}
	
	
	function isSearchScheduled()
	{
	    return _searchTimer != null;
	}


	
	/**
	 * Using the url provided by the current control, sends the actual HTTP (AJAX) request.
	 * If more is true, then resends the last search string, along with the nextStartRecNum value,
	 * otherwise, sends request with the current value in the control (and updates_lastSearchStr). 		   	
	 * @private  
	 */		
	function doSearch( nextStartRecNum )
	{	    		   
		// clear _searchTimer as we are now doing the search
		_searchTimer = null
				
		_searchRunning = true;
		_dropdownDisplay.setState( _dropdownDisplay.MESSAGE_STATE, "Retrieving/verifying data ..." );		
		
	    var searchURLGeneratorFunctionName = null;
		if ( _currentControl.getAttribute( "searchURLGenerator" ) )
		{
            searchURLGeneratorFunctionName = _currentControl.getAttribute( "searchURLGenerator" );    			
		}		
		else
		{
			throw new Error( Err.genErrMsg( "searchURLGenerator not provided", "doSearch()", "SuggestFieldComponent.js" ) );
		}
		

		if ( nextStartRecNum )
		{
            var url = eval( searchURLGeneratorFunctionName + "( '" + _currentControl.value + "', " + nextStartRecNum + " )" );
			var urlArray = url.split("?");
									            				    		    				
		    var tmpStr = _lastSearchStr;
			
			var req = HTTP.getPOSTRequest( urlArray[0] );
			var headers = {};
			headers['Content-type'] = "application/x-www-form-urlencoded";
			req.setHeaders(headers);
			req.setCallbackFunction( function( response ){ searchCallback( response, tmpStr ) } );
			req.send(urlArray[1]);
							    
//			HTTP.postText( url, 
//			              function( response ){ searchCallback( response, tmpStr ) },
//						  null, 
//			              true  );            			
		}
		else
		{			    
		    var url = eval( searchURLGeneratorFunctionName + "( '" + _currentControl.value + "', " + null + " )" );
			var urlArray = url.split("?");
			
		    // update _lastSearchStr
		    _lastSearchStr = UTL.trimString( _currentControl.value );
		    // need to use temp var to hold current lastSearchStr for callback function definition
		    var tmpStr = _lastSearchStr;
			var req = HTTP.getPOSTRequest( urlArray[0] );
			var headers = {};
			headers['Content-type'] = "application/x-www-form-urlencoded";
			req.setHeaders(headers);
			req.setCallbackFunction( function( response ){ searchCallback( response, tmpStr ) } );
			req.send(urlArray[1]);					    
//			HTTP.postText( url, 
//			              function( response ){ searchCallback( response, tmpStr ) },
//						  null, 
//			              true );						
		}
	}
	


	/**
	 * Handles the HTTP response - expects a string in proper xml form.
	 * Parses the response looking for either Error information, PossibleMatches list, calling 
	 * the appropriate methods of the dropdownDisplay.  		   	
	 * @private  
	 */		
	function searchCallback( response, searchStrUsed )
	{	    
	    if ( !_searchRunning || _lastSearchStr != searchStrUsed )
	    {
	        // running search was cancelled
	        return; 
	    }
	    
	    _searchRunning = false;
	
		var responseXMLDoc = XML.parseToXML( response );		
		
		// look for error initially
		var errorNode = XML.getNode( "/responseContents/error", responseXMLDoc );
		if( errorNode )
		{
		    _dropdownDisplay.setState( _dropdownDisplay.MESSAGE_STATE, errorNode.firstChild.nodeValue ); 			
		}
		else
		{
			var matchNodeArray = XML.getNodes( "/responseContents/PossibleMatches/PossibleMatch", responseXMLDoc );
				
			var dataObjArray = new Array( matchNodeArray.length );		
			for( var i = 0; i < matchNodeArray.length; i++ )
			{
				dataObjArray[i] = XML.buildJSON( matchNodeArray[i] ); 
			}
			
			// only one result, so just populate the field
			if ( dataObjArray.length == 1 )
			{
				_self.setControlDataObj( dataObjArray[0] );
				_dropdownDisplay.setState( _dropdownDisplay.CLOSED_STATE );				
			}	
			// multiple results, so display dropdown	
			else
			{			    
				var moreNode = XML.getNode( "/responseContents/moreText", responseXMLDoc )
				if ( moreNode )
				{
				    var moreObj = {};
				    moreObj["text"] = moreNode.firstChild.nodeValue;
				    moreObj["nextStartRecNum"] = XML.getNode( "/responseContents/nextStartRecNum", responseXMLDoc ).firstChild.nodeValue; 					
					var dispItemArray = _currentControl.getAttribute("displayItems").split(",");
					_dropdownDisplay.setState( _dropdownDisplay.OPTIONS_STATE, 
					                           dataObjArray, 
					                           dispItemArray, 
					                           moreObj );
				}
				else
				{					
					var dispItemArray = _currentControl.getAttribute("displayItems").split(",");				
					_dropdownDisplay.setState( _dropdownDisplay.OPTIONS_STATE, 
					                           dataObjArray, 
					                           dispItemArray, 
					                           null );				
				}
			}			
		}
		
		_currentControl.releaseCapture();
	}
	
	
	/**
	 * Event handler function for onfocus event. Calls method to update
	 * dropdownDisplay, passing reference of newly active control   		   	
	 * @private  
	 */
	function focusHandler_control( e )
	{	
	    _currentControl = e.currentTarget	    
		_dropdownDisplay.setLayoutToControl( _currentControl );		

        // set _lastSearchStr to current control contents				
		_lastSearchStr = UTL.trimString( _currentControl.value );
		_prevDataObj = _currentControl._suggestDataObj;		
	}
	
	
	/**
	 * Event handler function for onblur event. Ensures the dropdownDisplay
	 * is properly cleared when the control loses focus	    		   	
	 * @private  
	 */
	function blurHandler_control( e )
	{	    	
	    // we have to handle special case where the suggestField was given focus
	    // before the onfocus handler was attached - in which case we do nothing
	    if( _currentControl == null )
	    {
	        return;
	    }
	    	    	
	    if ( _searchRunning )
	    {	        
	        e.preventDefault();
	    }
	    else
	    {	     
	        if ( _dropdownDisplay.getState() == _dropdownDisplay.OPTIONS_STATE )
	        {	            
	            var selectedRow = _dropdownDisplay.getHighlightedRow();
	            if ( selectedRow.rowType == _dropdownDisplay.DATA_ROW )
	            {
	                _self.setControlDataObj( selectedRow.dataObj );
	                closeDropdown();
	                return;	                
	            }
	        }
	        closeDropdown();
	    }
	    
	    // ensure the _curDataObj is stored with the control (could be null)
	    //_self.setControlDataObj( _curDataObj );
	    
	    _currentControl = null;
	    
	    // cancel any scheduled search call that may be active
	    cancelScheduledSearchCall();
	    return;
	}

	
	
	function keydownHandler_control( e )
	{
		if ( _currentControl == null )
		{
			return;
		} 
		
	    // hide the detailsDisplay, if any
	    if ( _currentControl.detailsDisplayElement && _currentControl.detailsDisplayElement.length > 0 )
	    {    
	        UTL.getElem( _currentControl.detailsDisplayElement ).style.display = "none";
	    }
	    
	
	    switch( KeyMap.getKeyDesc( e.keyCode, KeyMap.KEYDOWN ) )
	    {	    
	        case KeyMap.TAB:
	        {
	            if ( isSearchScheduled() )
			    {			        			    
			        //cancel scheduled search
			        cancelScheduledSearchCall();
			        // and force a search to run immediately
			        doSearch();			        			       
			        e.preventDefault();			        
			    }
			    else
			    {
                    if ( _searchRunning )
                    {
                        e.preventDefault();
                    }
                    else
                    {
                        if ( _dropdownDisplay.getState() == _dropdownDisplay.OPTIONS_STATE )
                    	{
                    	    var selectedRow = _dropdownDisplay.getHighlightedRow();                    	    
            	            if ( selectedRow.rowType == _dropdownDisplay.DATA_ROW )
            	            {
            	                _self.setControlDataObj( selectedRow.dataObj );
            	                closeDropdown();            	                
            	            }
            	            // more button
            	            else
            	            {               	                         	               
            	                doSearch( _dropdownDisplay.nextStartRecNum );
            	                e.preventDefault();
            	            }
                    	}                    	
                    }
				}
				return;
	        }
	        case KeyMap.ESCAPE:
	        {
	            cancelScheduledSearchCall();
	            _searchRunning = false;
	            
	            // update _curDataObj with the data obj saved to the control
	            _self.setControlDataObj( _prevDataObj );	            
	            //_curDataObj = _currentControl.getAttribute( "_suggestDataObj" );	            	            	         
	            closeDropdown();
	            return;	            	            	            
	        }
	        case KeyMap.DOWN:
			{	
				if ( _dropdownDisplay.getState() == _dropdownDisplay.OPTIONS_STATE )
				{			
					_dropdownDisplay.highlightNextRow();
					e.preventDefault();
				}
				return;
			}		
			case KeyMap.UP:
			{
				if ( _dropdownDisplay.getState() == _dropdownDisplay.OPTIONS_STATE )
				{
					_dropdownDisplay.highlightPrevRow();
					e.preventDefault();
				}
				return;
			}	       
	    }
	}



	/**
	 * Event handler function for onkeyup event. This is where do all
	 * other listening for keyboard events.	  
	 * 
	 * @private  
	 */	
	function keyupHandler_control( e )
	{
		switch( KeyMap.getKeyDesc( e.keyCode, KeyMap.KEYUP ) )
		{			
			case KeyMap.ENTER:
			{			    
			    if ( isSearchScheduled() )
			    {			        			    
			        //cancel scheduled search
			        cancelScheduledSearchCall();
			        // and force a search to run immediately
			        doSearch();			        
			    }
			    else
			    {			        
			        if ( _searchRunning )
			        {
			            return;
			        }
			        else
			        {			            			           
			            if ( _dropdownDisplay.getState() == _dropdownDisplay.OPTIONS_STATE )
                    	{
                    	    var selectedRow = _dropdownDisplay.getHighlightedRow();
                    	                       
            	            if ( selectedRow.rowType == _dropdownDisplay.DATA_ROW )
            	            {
            	                _self.setControlDataObj( selectedRow.dataObj );
            	                closeDropdown();
            	            }
            	            // more
            	            else
            	            {
            	                doSearch( _dropdownDisplay.nextStartRecNum );
            	            }
                    	} 
                    	else
                    	{
                    	    closeDropdown();    
                    	}                    	                      
			        }
				}
				return;
			}						
			case KeyMap.RIGHT:
			{			
			    if ( _dropdownDisplay.getState() == _dropdownDisplay.OPTIONS_STATE )
			    {
				    if ( e.ctrlKey && _dropdownDisplay.nextStartRecNum != null )
				    {
					    doSearch( _dropdownDisplay.nextStartRecNum );
					    e.preventDefault();					
				    }
				}							
				return;
			}			
			case KeyMap.BACKSPACE:
				// fall thru - same behaviour
			case KeyMap.DELETE:
			{
			    closeDropdown();
			    _self.setControlDataObj( null );
			    //_curDataObj = null;				
				if ( _currentControl.value.length > 0 )
				{				    
					scheduleSearchCall();				
				}
				else
				{
				    _lastSearchStr = "";
				    closeDropdown();
				    _searchRunning = false;				    				   
					cancelScheduledSearchCall();
				}
				return;
			}			
			default:
			{			    
			    if ( KeyMap.isAlphaChar( e.keyCode, KeyMap.KEYDOWN ) ||
			            KeyMap.isNumericChar( e.keyCode, KeyMap.KEYDOWN ) )
			    {			        
			        closeDropdown();
			        _self.setControlDataObj( null );
			        //_curDataObj = null;
				    scheduleSearchCall();				    
				}							
			}
		}
	}
	
	
	
	
	function mouseenterHandler_control( e )
	{	    
	    var control = e.currentTarget;
	    if ( control._suggestDataObj )
	    {
	        var displayElem = UTL.getElem( control.getAttribute( "detailsDisplayElement" ) );
	        
	        // need to update the displayElem
	        if ( displayElem.getAttribute( "_lastControlValue" ) != control.value )
	        {
	            // update contents
	            populateDetailsDisplay( control, displayElem );
	            // update position
	            repositionDetailsDisplay( control, displayElem );
	            
	            displayElem._lastControlValue = control.value;
	        }
	        
	        displayElem.style.display = "block";	            
	    }
	}
	
	
	function mouseleaveHandler_control( e )
	{
	    var control = e.currentTarget;
	    var displayElem = UTL.getElem( control.getAttribute( "detailsDisplayElement" ) );
	    displayElem.style.display = "none"; 
	}
	
	
	
	function populateDetailsDisplay( control, displayElem )
	{
	    if ( displayElem.suggestField )	    
	    {
	        displayElem.innerHTML = control._suggestDataObj[displayElem.suggestField];
	    }
	    
	    for ( var i = 0; i < displayElem.childNodes.length; i++ )
	    {
	        populateDetailsDisplay( control, displayElem.childNodes[i] );   
	    }	        
	}
	
	
	function repositionDetailsDisplay( control, displayElem )
	{
	    displayElem.style.position = "absolute";
	    
	    var controlPosObj = WebTools.findElemPos( control );
	    displayElem.style.top = controlPosObj.top + control.offsetHeight + 2;
	    displayElem.style.left = controlPosObj.left + 10;
	}
	
	
	
	function preloadSuggestField( fld, initVal )
	{
        fld.disabled = true;
        
        _currentControl = fld;
        
        var searchURLGeneratorFunctionName = null;
		if ( _currentControl.getAttribute( "searchURLGenerator" ) )
		{
            searchURLGeneratorFunctionName = _currentControl.getAttribute( "searchURLGenerator" );    			
		}		
		else
		{
			throw new Error( Err.genErrMsg( "searchURLGenerator not provided", "doSearch()", "SuggestFieldComponent.js" ) );
		}
		
		
		var url = eval( searchURLGeneratorFunctionName + "( '" + initVal + "', " + null + " )" );		    
		    
        // we make the ajax call synchronous
        HTTP.postText( url, preloadSuggestField_callback, null, false );
        
        fld.disabled = false;        	        
	}
	
	
	function preloadSuggestField_callback( response )
	{
	    var responseXMLDoc = XML.parseToXML( response );
	    
	    // look for error initially
		var errorNode = XML.getNode( "/responseContents/error", responseXMLDoc );
		if( errorNode )
		{
		    throw new Error( Err.genErrMsg( "error with given initial value: " + errorNode.firstChild.nodeValue, 
		                                    "preloadSuggestField_callback", 
		                                    "SuggestFieldComponent.js" ) ); 		     			
		}
		else
		{
		    var matchNodeArray = XML.getNodes( "/responseContents/PossibleMatches/PossibleMatch", responseXMLDoc );
		    
		    var dataObjArray = new Array( matchNodeArray.length );		
			for( var i = 0; i < matchNodeArray.length; i++ )
			{
				dataObjArray[i] = XML.buildJSON( matchNodeArray[i] ); 
			}
						
			if ( dataObjArray.length == 1 )
			{
				_self.setControlDataObj( dataObjArray[0] );							
			}
			// multiple results - this is bad
			else
			{
			    throw new Error( Err.genErrMsg( "multiple matches found for given initial value", 
			                                    "preloadSuggestField_callback", 
			                                    "SuggestFieldComponent.js" ) );
			}	
		}
	}
	
	
	

	/**
	 * Method called as part of the page onload, to identify all the controls marked for
	 * use as suggest fields. Each control found has a number event handlers attached. 	  	
	 */		
	this.init = function()
	{
		var inputElementArray = UTL.getElem("input", UTL.GET_ELEM_SEARCH_TYPE_TAGNAME);
						
		for ( var i = 0; i < inputElementArray.length; i++ )
		{
			var c = inputElementArray[i];
			if ( c.getAttribute("type") == "text" && c.getAttribute( "suggestField" ) == "true" )
			{
			    // add event handlers to the control
				EvtHandler.add( c,     "focus",     focusHandler_control );
				EvtHandler.add( c,     "keyup",     keyupHandler_control );				
				EvtHandler.add( c,     "blur",      blurHandler_control );
				EvtHandler.add( c,     "keydown",   keydownHandler_control );
				
				if ( c.getAttribute( "detailsDisplayElement" ) && c.getAttribute( "detailsDisplayElement" ).length > 0 )
				{
				    EvtHandler.add( c, "mouseenter", mouseenterHandler_control );
				    EvtHandler.add( c, "mouseleave", mouseleaveHandler_control ); 
				}
				
				// if an initial value given, we need to preload the suggestfield
				if( c.initialValue )
				{
				    preloadSuggestField( c, c.initialValue );
				}
				else
				{
				    c._suggestDataObj = null;
				}
				
				// because we've just added onfocus handlers to c, we want to 
				// ensure the user does start working with c, and the onfocus 
				// handler never got chance to run
				c.blur();
				
				// on the first one we find, create a dropdownDisplay object 
				if ( !_dropdownDisplay )
				{				
					_dropdownDisplay = new SuggestFieldManager.DropdownDisplay();
				}
			}	
		}
	}
	
	
	this.reInit = function( c )
	{
	    if ( c.getAttribute("type") == "text" && c.getAttribute( "suggestField" ) == "true" )
		{
		    // add event handlers to the control
			EvtHandler.add( c,     "focus",     focusHandler_control );
			EvtHandler.add( c,     "keyup",     keyupHandler_control );				
			EvtHandler.add( c,     "blur",      blurHandler_control );
			EvtHandler.add( c,     "keydown",   keydownHandler_control );
			
			if ( c.getAttribute( "detailsDisplayElement" ) && c.getAttribute( "detailsDisplayElement" ).length > 0 )
			{
			    EvtHandler.add( c, "mouseenter", mouseenterHandler_control );
			    EvtHandler.add( c, "mouseleave", mouseleaveHandler_control ); 
			}
			
			// if an initial value given, we need to preload the suggestfield
			if( c.initialValue )
			{
			    preloadSuggestField( c, c.initialValue );
			}
			else
			{
			    c._suggestDataObj = null;
			}
			
			// because we've just added onfocus handlers to c, we want to 
			// ensure the user does start working with c, and the onfocus 
			// handler never got chance to run
			c.blur();
			
			// on the first one we find, create a dropdownDisplay object 
			if ( !_dropdownDisplay )
			{				
				_dropdownDisplay = new SuggestFieldManager.DropdownDisplay();
			}
		}	    
	}

	
	/**
	 * Wrapper function for doing a "more" search 	  	
	 */	 
	this.doMoreSearch = function( nextStartRecNum )
	{	    
		doSearch( nextStartRecNum );
	}
	
	
	/**
	 * Fucntion called when an item is selected from the dropdown. 	  	
	 */	 
	this.setControlDataObj = function( dataObj )	
	{			    			    		        
		_currentControl.setAttribute( "_suggestDataObj", dataObj );		
		if ( _currentControl.getAttribute( "updateCallbackFn" ) && _currentControl.getAttribute( "updateCallbackFn" ) != "" && _currentControl.getAttribute( "updateCallbackFn" ).length > 0)
		{
			eval( _currentControl.getAttribute( "updateCallbackFn" ) + "()" );
		}			
				
		if ( dataObj != null )
		{
		    _prevDataObj = dataObj;
    		var dispItemArray = _currentControl.getAttribute( "displayItems" ).split( "," );
    		var dispStr = "";		
    		for ( var i = 0; i < dispItemArray.length; i++ )
    		{
    			dispStr += dataObj[dispItemArray[i]];
    		}
    		_currentControl.value = dispStr;
    		
    		// also set _lastSearchStr, so we don't do a re-search for this selected val		
    		_lastSearchStr = UTL.trimString( dispStr );    		    	
    	}
    	else
    	{
    	    _lastSearchStr = "";
    	}
    	
    	
	}	
}

// *** Adding the SuggestFieldManager init method to the onload event listener
// NOTE: this line must come after the SuggestFieldManager declaration
EvtHandler.add( window, "load", SuggestFieldManager.init );









 

/**  
 * @class This is a nested class of the SuggestFieldManager. It is used to create
 * and store code for the actual dropdown display object. 
 */ 
SuggestFieldManager.DropdownDisplay = function()
{
    this.CLOSED_STATE = "closed";
    this.MESSAGE_STATE = "message";
    this.OPTIONS_STATE = "options";
    
    this.DATA_ROW = "data";
    this.MORE_ROW = "more";

	/**
	 * A self reference, required where "this" not available (ie. in private functions) 	 
	 * @private  
	 */
	var _self = this;
	/**
	 * the div used as the main container of the dropdown 	 
	 * @private  
	 */
	var _div = buildDiv();
	/**
	 * iframe used as a buffer for the div, so select boxes dont show thru 	 
	 * @private  
	 */
	var _iframeLayer = buildIframe();		
	/**
	 * reference to the table inside the dropdown, holding the actual content 	 
	 * @private  
	 */
	var _contentTbl = null;
	/**
	 * the style class name being applied to the drop down div 	 
	 * @private  
	 */
	var _dropdownClass = null;
	/**
	 * the style class name being applied to the data items within the dropdown 	 
	 * @private  
	 */
	var _contentClass = null;
	/**
	 * the style class name being applied to the data items when being highlighted 	 
	 * @private  
	 */
	var _highlightClass = null;
	/**
	 * Reference to the row in the dropdown display currently highlighted 	 
	 * @type Object  
	 */
	var _highlightedRow = null;
	
	var _currentState = this.CLOSED_STATE;
	
	/**
	 * Boolean indicating whether more records are available for the current search 	 
	 * @type boolean  
	 */
	//this.isMoreAvailable = false;
	this.nextStartRecNum = null;
	
	
	
	/**
	 * Function for building the div when first initialized 	 
	 * @private  
	 */
	function buildDiv()
	{
		var d = document.createElement( "div" ); 	   
        d.style.position = "absolute";                
        d.style.zIndex = 100000001;                
        d.style.overflowX = "hidden";
        d.style.overflowY = "visible";
        d.style.display = "none";        
        d.unselectable = "on";                
        document.body.appendChild( d );
        
        return d;
	}
	
	

	/**
	 * Function for building the iframe when first initialized 	 
	 * @private  
	 */	
	function buildIframe()
	{	
		var f = document.createElement( "iframe" );		
        f.tabIndex = "-1";
        
        // hack to make the Iframe appear with a transparent background
        var html = '<body style="background-color:transparent;"></body>';
        f.src = "javascript: {this.innerHTML = '" + html + "';}";        
        f.id = "suggestDropdown_iframe";
        f.frameBorder = "no";
        f.style.position = "absolute";
        f.style.zIndex = 100000000;
        f.style.width=100;
        f.style.height=100;
        f.style.display = "none";        
                       
        document.body.appendChild( f );
        return f;                	
	}
	
	
	
	/**
	 * Handler function - mouse enters a content row of the dropdown, sets highlightedRow
	 * and clears any previously highlighted row 	 
	 * @private  
	 */
	function mouseenterHandler_row( e )
	{
		if ( _highlightedRow )
		{
			clearHighlightedRow();
		}
		
		setHighlightedRow( e.currentTarget );	
	}
	
	
	/**
	 * Handler function - click on a content row of the dropdown, passing
	 * the displayed text and dataObj to the SuggestFieldManager so it can be
	 * associated with the current control. 
	 * @private  
	 */
	function clickHandler_row( e )
	{
		var row = e.currentTarget;	
		SuggestFieldManager.setControlDataObj( row.dataObj );
		_self.setState( _self.CLOSED_STATE );		
	}
	
	
	/**
	 * Handler function - click on the "more" row of the dropdown (if available), calling
	 * the doMoreSearch method. 
	 * @private  
	 */
	function clickHandler_moreRow( e )
	{		      
	    var moreRow = e.currentTarget;
		SuggestFieldManager.doMoreSearch( _self.nextStartRecNum );		
	} 
	
	
	/**
	 * Handles the "unhighlighting" of the currently highlighted row.  
	 * @private  
	 */
	function clearHighlightedRow()
	{
		_highlightedRow.className = _contentClass;
		_highlightedRow = null;
	}
	
	
	/**
	 * Handles the "highlighting" of the specified row  
	 * @private  
	 */
	function setHighlightedRow( row )
	{
		row.className = _highlightClass; 
		_highlightedRow = row;		
	}

	
	
	/**
	 * Relocates the dropdown display to the specified control, as well as pulling
	 * the classNames to be used.
	 * @param {DOMElement} ctrl reference to 'suggest field' control 	 
	 * @return   
	 */
	this.setLayoutToControl = function( ctrl )
	{
		// get and set style class for dropdown and content		
		_dropdownClass = ctrl.getAttribute( "dropdownClass" ) ? ctrl.getAttribute( "dropdownClass" ) : "";
		_contentClass = ctrl.getAttribute( "contentClass" ) ? ctrl.getAttribute( "contentClass" ) : "";	
		_highlightClass = ctrl.getAttribute( "highlightClass" ) ? ctrl.getAttribute( "highlightClass" ) : "";
		
		// get and set style position
		var ctrlPosObj = WebTools.findElemPos( ctrl );
		_div.style.top = ctrlPosObj.top + ctrl.offsetHeight + 1;
		_iframeLayer.style.top = parseInt( _div.style.top ) + 2;
		_div.style.left = ctrlPosObj.left;
		_iframeLayer.style.left = parseInt( _div.style.left ) + 2;						
	}
	
	
	
	/**
	 * Cleans up the data and private members of the dropdown, and then hides it the div/iframe	  	
	 * @return  
	 */
	function clearDropdownDisplay()
	{
		if( _contentTbl )
		{
			//this.isMoreAvailable = false;
			_self.nextStartRecNum = null;			
			_highlightedRow = null;
			_div.removeChild( _contentTbl );
			_contentTbl = null;
		}
		
		_div.style.display = "none"
		_iframeLayer.style.display = "none";
	}
	
	
	/**
	 * Makes the dropdown visible/active and displays within it the errorString specified
	 * @param {string} errorString 	  	
	 * @return  
	 */
	function displayMessage ( msgString )
	{		
		if ( _contentTbl )
		{
			clearDropdownDisplay();
		}
				
		_contentTbl = document.createElement( "table");
		_contentTbl.style.width = "100%";
		_contentTbl.border = "0";		
		_contentTbl.cellPadding = "0";
		_contentTbl.cellSpacing = "0";
		
		var tblBody = document.createElement( "tbody" );
		_contentTbl.appendChild( tblBody );
		
		var r = document.createElement( "tr" );
		r.className = _contentClass;									
		var msgLbl = document.createElement( "td" ); 			
		msgLbl.innerHTML = msgString;
		
		r.appendChild( msgLbl );
		tblBody.appendChild( r );
		
		_div.appendChild( _contentTbl );
		
		_div.className = _dropdownClass;		
		_div.style.display = "block";
		
		// we set the height/width of the iframe here, 
		// since only able to refer to offsetHeight/Width
		// when _div is actually being displayed
		_iframeLayer.style.width = parseInt( _div.offsetWidth ) - 4;
		_iframeLayer.style.height = parseInt( _div.offsetHeight ) - 4;
		_iframeLayer.style.display = "block";
	}
	
	
	
	/**
	 * Makes the dropdown visible/active and displays within it the data
	 * provided in the array. Specifically the fields listed in the propsToDisplayArray 
	 * (or just "displayValue" if not provided. And finally a moreLabel, if given.
	 * @param {array(Object)} dataArray array of standard javascript objects
	 * @param {string} moreLabel string to be used as the more option - empty string for none
	 * @param {array(strings)} propsToDisplayArray (optional) array of property names to look for in the dataArray objects,
	 * if not given then jsut looks for single property "displayValue"	   	  
	 * @return  
	 */
	function displayData( dataArray, propsToDisplayArray, moreObj )
	{
		if( _contentTbl )
		{
			clearDropdownDisplay();
		}
		
		propsToDisplayArray = propsToDisplayArray ? propsToDisplayArray : ["displayValue"]; 
	
		_contentTbl = document.createElement( "table");
		_contentTbl.style.width = "100%";
		_contentTbl.border = "0";		
		_contentTbl.cellPadding = "0";
		_contentTbl.cellSpacing = "0";
		
		var tblBody = document.createElement( "tbody" );
		_contentTbl.appendChild( tblBody );
		
		for ( var i = 0; i < dataArray.length; i++ )
		{
			var r = document.createElement( "tr" );			
			r.setAttribute( "rowType", _self.DATA_ROW );			 								
			r.setAttribute( "dataObj", dataArray[i] );
			r.className = _contentClass;					
			EvtHandler.add( r, "mouseenter", mouseenterHandler_row );
			EvtHandler.add( r, "click", clickHandler_row ); 
			
			for ( var j = 0; j < propsToDisplayArray.length; j++ )
			{
				var dataItem = document.createElement( "td" );
				dataItem.padding = 0;
				var dataItemContent = document.createElement( "span" );
				dataItemContent.className = _contentClass;
				dataItemContent.style.border = "0px solid black";				
				dataItemContent.style.overflow = "hidden";
				dataItemContent.style.whiteSpace = "nowrap";
				dataItemContent.style.textOverflow = "ellipsis";
				dataItemContent.unselectable = "on";							
				dataItemContent.innerHTML = dataArray[i][propsToDisplayArray[j]];
				dataItem.appendChild( dataItemContent );
				r.appendChild( dataItem );
			}						
								
			if ( i == 0 )
			{
				setHighlightedRow( r );
			}								
			tblBody.appendChild( r ); 		
		}
		
		if( moreObj )
		{
			var r = document.createElement( "tr" );			
			r.setAttribute( "rowType", _self.MORE_ROW );
			_self.nextStartRecNum = moreObj.nextStartRecNum;
						
			r.className = _contentClass;
			EvtHandler.add( r, "mouseenter", mouseenterHandler_row);
			EvtHandler.add( r, "click", clickHandler_moreRow );
						
			var moreItem = document.createElement( "td" );
			moreItem.colSpan = propsToDisplayArray.length;			
			moreItem.innerHTML = moreObj.text;
			moreItem.unselectable = "on";	
			
			r.appendChild( moreItem );
			tblBody.appendChild( r );
		}										
		_div.appendChild( _contentTbl );
		
		_div.className = _dropdownClass;		
		_div.style.display = "block";
		
		// we set the height/width of the iframe here, 
		// since only able to refer to offsetHeight/Width
		// when _div is actually being displayed
		_iframeLayer.style.width = parseInt( _div.offsetWidth ) - 4;
		_iframeLayer.style.height = parseInt( _div.offsetHeight ) - 4;
		_iframeLayer.style.display = "block";																	
	}
	
	
		
	this.getState = function()
	{
	    return _currentState;
	}
	

	
	this.setState = function( stateStr, param1, param2, param3 )
	{	    
	    if ( stateStr == _self.CLOSED_STATE )
	    {
	        _currentState = _self.CLOSED_STATE;
	        clearDropdownDisplay();
	    }
	    else if ( stateStr == _self.MESSAGE_STATE )
	    {	        
	        _currentState = _self.MESSAGE_STATE;
	        displayMessage( param1 );
	    }
	    else if ( stateStr == _self.OPTIONS_STATE )
	    {	        	       
	        if ( param1 != null )
	        {
	            _currentState = _self.OPTIONS_STATE;
	            displayData( param1, param2, param3 );
	        }
	        else
	        {
	            throw new Error( Err.genErrMsg( "invalid param for OPTIONS_STATE", 
	                                            "setState()", 
	                                            "SuggestFieldComponent.js" ) );
	        }
	    }	   
	}
	
	
	
	this.getHighlightedRow = function()
	{
	    return _highlightedRow;
	}
	
	
	
	/**
	 * Sets the next row down from currently highlightedRow as the new highlightedRow,
	 * if currently highlighted is not the last one.
	 * Also, if currently highlighted row is null, tries to use first row of dropdown.
	 * <br/>
	 * Meant for use with arrow keys.	   
	 */
	this.highlightNextRow = function()
	{
		if ( _highlightedRow )
		{	
			// check that not at the end of the list			
			if( _highlightedRow.nextSibling )
			{
				// nextSibling = next row
				var newhr = _highlightedRow.nextSibling;
				clearHighlightedRow();
				setHighlightedRow( newhr );
			}
		}
		else
		{
			// try to set to the first row, if there is one
			if ( _contentTbl && _contentTbl.firstChild.firstChild )
			{				
				setHighlightedRow( _contentTbl.firstChild.firstChild );
			}
		}
	}
	
	
	
	/**
	 * Sets the previous row up from currently highlightedRow as the new highlightedRow,
	 * if currently highlighted is not the first one.
	 * Also, if currently highlighted row is null, tries to use first row of dropdown.
	 * <br/>
	 * Meant for use with arrow keys.	   
	 */
	this.highlightPrevRow = function()
	{
		if ( _highlightedRow )
		{
			// check not the start of the list
			if ( _highlightedRow.previousSibling)
			{
				// previousSibling = next row
				var newhr = _highlightedRow.previousSibling;
				clearHighlightedRow();
				setHighlightedRow( newhr );
			}
		}
		else
		{
			// try to set to the first field, if there is one
			if ( _contentTbl && _contentTbl.firstChild.firstChild )
			{				
				setHighlightedRow( _contentTbl.firstChild.firstChild );
			}
		}
	}
}
