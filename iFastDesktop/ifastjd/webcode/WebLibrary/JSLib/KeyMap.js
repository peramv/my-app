/** 
 * @fileoverview KeyMap contains objects for mapping from keyCode (as per keyboard Event object)
 * to printable (ASCII) characters, and to function keys (ie. esc)
 *  
 * @author walkerro
 * @version 0.1 
 */


/**
 * Static class - constructor not permitted 
 *  
 * @class Static class used to objects and functions for working with keyboard events - keycode
 * <br/>
 * <b>REQUIRES:</b> Err.js
 */
var KeyMap = new function()
{


	/**
	 * @type string
	 */
	this.KEYDOWN = "keydown";
	/**
	 * @type string
	 */
	this.KEYUP = "keyup";
	/**
	 * @type string
	 */
	this.KEYPRESS = "keypress";	
	/**
	 * @type string
	 */
	this.BACKSPACE = 		"backspace";
	/**
	 * @type string
	 */
	this.TAB = 				"tab";
	/**
	 * @type string
	 */	 
	this.RETURN = 			"return";
	/**
	 * @type string
	 */	 
	this.SHIFT = 			"shift";
	/**
	 * @type string
	 */	 
	this.CTRL = 			"ctrl";
	/**
	 * @type string
	 */	 
	this.ALT = 				"alt";
	/**
	 * @type string
	 */	 
	this.WINDOWS_RIGHT =	"windows_right";
	/**
	 * @type string
	 */	 
	this.WINDOWS_LEFT =	    "windows_left";
	/**
	 * @type string
	 */	 
	this.APPLICATION = 		"application";
	/**
	 * @type string
	 */
	this.ENTER = 			"return";
	/**
	 * @type string
	 */
	this.PAUSE = 			"pause";
	/**
	 * @type string
	 */
	this.ESCAPE = 			"escape";
	/**
	 * @type string
	 */
	this.SPACE =			"space";
	/**
	 * @type string
	 */
	this.PAGEUP	=			"pageup";
	/**
	 * @type string
	 */
	this.PAGEDOWN = 		"pagedown";
	/**
	 * @type string
	 */
	this.END = 				"end";
	/**
	 * @type string
	 */
	this.HOME = 			"home";
	/**
	 * @type string
	 */
	this.LEFT = 			"left";
	/**
	 * @type string
	 */
	this.UP = 				"up";
	/**
	 * @type string
	 */
	this.RIGHT = 			"right";
	/**
	 * @type string
	 */
	this.DOWN = 			"down";
	/**
	 * @type string
	 */
	this.PRINTSCREEN =    	"printscreen";
	/**
	 * @type string
	 */
	this.INSERT = 			"insert";
	/**
	 * @type string
	 */
	this.DELETE = 			"delete";
	/**
	 * @type string
	 */
	this.F1 =				"f1";
	/**
	 * @type string
	 */
	this.F2 =				"f2";
	/**
	 * @type string
	 */
	this.F3 =				"f3";
	/**
	 * @type string
	 */
	this.F4 =				"f4";
	/**
	 * @type string
	 */
	this.F5 =				"f5";
	/**
	 * @type string
	 */
	this.F6 =				"f6";
	/**
	 * @type string
	 */
	this.F7 =				"f7";
	/**
	 * @type string
	 */
	this.F8 =				"f8";
	/**
	 * @type string
	 */
	this.F9 =				"f9";
	/**
	 * @type string
	 */
	this.F10 =				"f10";
	/**
	 * @type string
	 */
	this.F11 =				"f11";
	/**
	 * @type string
	 */
	this.F12 =				"f12";
	/**
	 * @type string
	 */
	this.NUMLOCK = 			"numlock";
	/**
	 * @type string
	 */
	this.SCROLL_LOCK =		"scroll_lock";
	/**
	 * @type string
	 */	
	this.CAPS_LOCK =        "caps_lock";  	
	/**
	 * @type string
	 * number key pad "5", when num lock is OFF = does nothing, but still has a key code
	 */	
	this.DOES_NOTHING =      "does_nothing";  	
	 
	
	/**
	 * Mapping keyCode to Function key descriptions
	 * @type object
	 * @private
	 */
	var keyCodeToFunctionKey = {	    
		8: 		this.BACKSPACE,
		9: 		this.TAB,
        12:     this.DOES_NOTHING, 		
		13: 	this.RETURN,
		16:		this.SHIFT,
		17:		this.CTRL,
		18:		this.ALT,
		19:		this.PAUSE,
		20:     this.CAPS_LOCK,
		27:		this.ESCAPE,
		32:		this.SPACE,
		33:		this.PAGEUP,
		34:		this.PAGEDOWN,
		35:		this.END,
		36:		this.HOME,
		37:		this.LEFT,
		38:		this.UP,
		39:		this.RIGHT,
		40:		this.DOWN,
		44:		this.PRINTSCREEN,
		45:   	this.INSERT,
		46:		this.DELETE,
		91:		this.WINDOWS_LEFT,
		92:     this.WINDOWS_RIGHT,
		93:		this.APPLICATION,
		112:	this.F1,
		113:	this.F2,
		114:	this.F3,
		115:	this.F4,
		116:	this.F5,
		117:	this.F6,
		118:	this.F7,
		119:	this.F8,
		120:	this.F9,
		121:	this.F10,
		122:	this.F11,
		123:	this.F12,
		144:	this.NUMLOCK,
		145: 	this.SCROLL_LOCK		
	};
	
	
	/**
	 * Mapping keyCode to printable characters
	 * @type object
	 * @private
	 */
	var keyCodeToPrintableChar = {	
			48:		"0",
			49:		"1",
			50:		"2",
			51:		"3",
			52:		"4",
			53:		"5",
			54:		"6",
			55:		"7",
			56:		"8",
			57:		"9",					
			61:		"=",
			65:		"a",
			66:		"b",
			67:		"c",		
			68:		"d",	
			69:		"e",
			70:		"f",
			71:		"g",
			72:		"h",
			73:		"i",
			74:		"j",
			75:		"k",
			76:		"l",
			77:		"m",
			78:		"n",
			79:		"o",		
			80:		"p",
			81:		"q",
			82:		"r",
			83:		"s",
			84:		"t",
			85:		"u",
			86:		"v",
			87:		"w",
			88:		"x",
			89:		"y",
			90:		"z",
			96:     "0",
			97:     "1",
			98:     "2",
			99:     "3",
			100:    "4",
			101:    "5",
			102:    "6",			   
			103:    "7",
			104:    "8",
			105:    "9",
			106:    "*",
			107:	"+",
			109:	"-",	// numpad		
			110:	".",
			111:    "/",
			186:    ";",
			187:    "=",
			188:	",",
			189:    "-",   // normal
			190:	".",
			191:	"/",
			192:	"`",
			219:	"[",
			220:	"\\",
			221:	"]",
			222:	"\""		
	};
	
	
	
	/**
	 * Returns a string matching the keyCode given, either an ASCII printable char, or
	 * description of a function key (as per defined descriptions). Able to specify 
	 * which keyevent generated keyCode, since keypress and keydown/up use different 
	 * keycode mapping. If keyEvent is not provided, then defaulted to KEYPRESS.
	 * @param {number} keyCode integer value representing the key used in a keyboard event
	 * @param {string} keyEvent string (optional) describing which type of keyboard event the keyCode is 
	 * associated with, defaults to KEYPRESS 
	 * @return {string}
	 */
	this.getKeyDesc = function( keyCode, keyEvent )
	{		
		keyEvent = ( keyEvent ) ? keyEvent : this.KEYPRESS;		
		switch( keyEvent )
		{
			case this.KEYPRESS:
			{
				return String.fromCharCode( keyCode );			
			}
			case this.KEYDOWN:
				// fall thru, since keydown and keyup use same mapping
			case this.KEYUP:
			{							
				var result = ( keyCodeToPrintableChar[keyCode] ) ? keyCodeToPrintableChar[keyCode] : keyCodeToFunctionKey[keyCode];
				if( !result )
				{
					throw new Error( Err.genErrMsg( "Unknown key code", "getKeyDesc()", "KeyMap.js" ) );
				}
				return result; 
			}
		}
	}
	
	
	/**
	 * Returns a boolean according to whether the given keyCode matches to a printable keyboard char
	 * <br/>
	 * Note: this function only relevant to KEYUP/DOWN event, since only printable
	 * characters can generate a KEYPRESS event 
	 * @param {number} keyCode integer value representing the key used in a keyboard event  
	 * @return {boolean}
	 */
	this.isPrintableChar = function( keyCode )
	{
		if ( keyCodeToPrintableChar[keyCode] )
		{
			return true
		}
		return false;
	}
	
	
	/**
	 * Returns a boolean according to whether the given keyCode matches to a numeric keyboard char
	 * Do not need to specify key event type, since keycode for numeric keys is consistent.
	 * @param {number} keyCode integer value representing the key used in a keyboard event  
	 * @return {boolean}
	 */
	this.isNumericChar = function( keyCode )
	{		
		return ( ( keyCode >= 48 && keyCode <= 57 ) || ( keyCode >= 96 && keyCode <= 105 ) );		
	}
	
	
	/**
	 * Returns a boolean according to whether the given keyCode matches to an alpha keyboard char
	 * Need to specify keyboard event type, since KEYUP/DOWN do not map uppercase.
	 * @param {number} keyCode integer value representing the key used in a keyboard event
	 * @param {string} keyEvent string (optional) describing which type of keyboard event the keyCode is
	 * associated with, defaults to KEYPRESS     
	 * @return {boolean}
	 */
	this.isAlphaChar = function( keyCode, keyEvent )
	{
		keyEvent = ( keyEvent ) ? keyEvent : this.KEYPRESS;
				
		if ( keyEvent == this.KEYPRESS )
		{
			return ( ( keyCode >= 65 && keyCode <= 90 ) || ( keyCode >= 97 && keyCode <= 122 ) )				
		}
		else
		{
			return ( keyCode >= 65 && keyCode <= 90 );
		}
	}
}