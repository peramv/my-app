/** 
 * @fileoverview Source for static class containing browser protable functions for
 * adding and removing event handlers to DOM elements
 *  
 * @author walkerro
 * @version 0.1 
 */


/**
 * Static class - no constructor permitted
 *  
 * @class Static class used to hold browser portable event functions for adding
 * and removing event handlers.
 * <p> 
 * In MOZ standard browsers, functions simply wrap the 
 * existing add/removeEventListener functions.
 * </p>
 * <p> 
 * In IE, uses attach/removeEvent, and a lot of hacking to provide compatibility 
 * with MOZ standard. Includes code to eliminate memory leakage, by adding 
 * code to track and clear all registered handlers at "unload" time.
 * </p>
 * 
 */

var EvtHandler = new function()
{	
	var _browserCodeObj = null;
	
	// MOZ - simply wrap add/removeEventListener functions
	var _MOZ = {
		add :	function( element, eventType, handler )
				{		
					element.addEventListener( eventType, handler, false );
				},
		remove: function( element, eventType, handler )
				{
					element.removeEventListener( eventType, handler, false );
				}		 
	};
	
	// IE - wrap handler in a closure, build object for tracking, and add/remove
	// using attach/removeEvent functions
	var _IE = {
		add :	function( element, eventType, handler )
				{
					// ensure no duplicate handler registrations
					if ( _IE.find( element, eventType, handler ) != -1 )
					{
						return;
					}
		
					// to invoke handler as a method of the element, we define
 					// a nest function and register it instead of the given function					
					var wrappedHandler = function( e )
					{
						if( !e )
						{
							e = window.event;
						}
			
						// create a wrapper Event object 
						var event = {	
							// reference to original IE event	
							_event: e,
							// event type    
							type: e.type,
							// where the event happened
							target: e.srcElement,
							// where we're handling it
							currentTarget: element,
							// used in handling mouseout/in events
							relatedTarget: e.fromElement ? e.fromElement : e.toElement,
				
							eventPhase: (e.srcElement == element)? 2 : 3,
				
							// mouse co-ords
							clientX: e.clientX,
							clientY: e.clientY,
							screenX: e.screenX,
							screenY: e.screenY,
				
							// key state	
							altKey: e.altKey,
							ctrlKey: e.ctrlKey,
							shiftKey: e.shiftKey,
							charCode: e.keyCode,
							keyCode: e.keyCode,
				
							// event management functions	
							stopPropagation: function(){ this._event.cancelBubble = true; },
							preventDefault: function(){ this._event.returnValue = false; }
						};
			
						// invoke the given handler function, as a method of element
						// passing our event object as its single argument
						handler.call( element, event );															
					};
		
					// register the wrapper function as the event handler
					element.attachEvent( "on" + eventType, wrappedHandler );
		
					// record keeping - associate the user-supplied handler
					// and our wrapper function that invokes it.
					// this is necessary for deregistering to work correctly
		
					// store info about the handler
					var h = {	
						element: element,
						eventType: eventType,
						handler: handler,
						wrappedHandler: wrappedHandler
					};
		
					// store reference to document, which the element may in fact be
					var d = element.document || element;
					// store reference to the window
					var w = d.parentWindow;
		
					// associate the handler with the window, so it can be
					// removed correctly (avoid mem leak) when window is unloaded
		
					// generate unique id
					var id = _IE.uid();
					// create storage object if necessary
					if( !w._allHandlers ) w._allHandlers = {};
					// store handler info in the storage object
					w._allHandlers[id] = h;
		
					// also associate the handler id with the element
					if(!element._handlers) element._handlers = [];
					element._handlers.push(id);
		
					// if there is no onunload handler associated, 
					// do so now
					if(!w._onunloadHandlerRegistered)
					{
						w.onunloadHandlerRegistered = true;
						w.attachEvent("onunload", _IE.removeAllHandlers);
					}		
				},
			
			remove:	function( element, eventType, handler )
					{
						// find this handler i the element._handlers[] array
						var i = _IE.find( element, eventType, handler );
						// do nothing if no handler was registered
						if ( i == -1 ) return;
						
						// get window of this element
						var d = element.document || element;
						var w = d.parentWindow;
						
						// look up the unique id of this handler
						var handlerId = element._handlers[i];
						// use id to look up handler info
						var h = w._allHandlers[handlerId];
						// use the handler info to detach the wrapped handler
						element.detachEvent("on" + eventType, h.wrappedHandler);
						// remove id refence from element's handler list
						element._handlers.splice(i, 1);
						// delete the handler info from the window storage object
						delete w._allHandlers[handlerId];	
					},
			
			// find method - util function for getting handler id from element's array
			find:	function( element, eventType, handler )
					{	
						var handlers = element._handlers;
						// no handlers registered
						if( !handlers ) return -1;
						
						// get window of this element
						var d = element.document || element;
						var w = d.parentWindow;
						
						// loop thru the handlers associated with this element, looking
						// for on with right type and function		  
						for ( var i = handlers.length - 1; i >= 0; i-- )
						{
							// get handler id
							var handlerId = handlers[i];
							// get handler info
							var h = w._allHandlers[handlerId];
							// return id, if type and function match info
							if( h.eventType == eventType && h.handler == handler )
							{
								return i;
							}
						}
						// no match found
						return -1;
					},
			
			// removeAllHandler method - attached to the onunload event to clear
			// all event handlers still remaining
			removeAllHandlers: 	function()
								{
									// this = window, since attached directly using attachEvent
									var w = this;
									
									for( id in w._allHandlers )
									{
										// get handler info for handler id i
										var h = w._allHandlers[id];
										// use the info to detach wrapped handler
										h.element.detachEvent("on" + h.eventType, h.wrappedHandler);
										// delete the handler info
										delete w._allHandlers[id];
									}
								},
			
			// private function/variable for generating unique handler ids
			counter: 0,
			uid: function(){ return "h" + _IE.counter++; }
	};
	
	
	
	/**
	 * Browser portable method for adding an eventHandler function to the specified element, to
	 * occur in response to the given eventType. Adheres to DOM 2 (ie. Mozilla) standard. 
	 * 
	 * @param {DOMElement} element DOMElement to which handler is to be applied
	 * @param {string} eventType String indicating the event handler will be attached to,
	 * follows DOM 2 standard (ie. no "on" prefix for mouse/keyboard events)
	 * @param {function} handler Reference to the function being attached	 
	 */
	this.add = function( element, eventType, handler )
	{
		if( !_browserCodeObj )
		{
			// set _browserCodeObj to _MOZ, and clear out _IE 			
			if( document.addEventListener )
			{
				_browserCodeObj = _MOZ;
				clear( _IE );
				_IE = null;
			}
			// set _browserCodeObj to _IE, and clear out _MOZ
			else
			{
				_browserCodeObj = _IE;
				clear( _MOZ );
				_MOZ = null;
			}			
		}
		
		_browserCodeObj.add( element, eventType, handler );
	}
	
	
	
	/**
	 * Browser portable method for removing an eventHandler function to the specified element, to
	 * occur in response to the given eventType. Adheres to DOM 2 (ie. Mozilla) standard. 
	 * 
	 * @param {DOMElement} element DOMElement to which handler is to be applied
	 * @param {string} eventType String indicating the event handler will be attached to,
	 * follows DOM 2 standard (ie. no "on" prefix for mouse/keyboard events)
	 * @param {function} handler Reference to the function being attached	 
	 */
	this.remove = function( element, eventType, handler )
	{
		if( !_browserCodeObj )
		{
			// set _browserCodeObj to _MOZ, and clear out _IE
			// note: this should never happen, since remove should never be first method called 			
			if( document.addEventListener )
			{
				_browserObj = _MOZ;
				clear( _IE );
			}
			// set _browserCodeObj to _IE, and clear out _MOZ
			else
			{
				_browserCodeObj = _IE;
				clear( _MOZ );
				_MOZ = null;
			}						
		}
		
		_browserCodeObj.remove( element, eventType, handler );
	}
	
	/**
	 * @private
	 */ 
	function clear( obj )
	{
		for( var i in obj )
		{
			delete obj[i];
		}		
	}
}

