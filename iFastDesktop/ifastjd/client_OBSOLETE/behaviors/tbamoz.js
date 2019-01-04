//<![CDATA[
function CPersist(attachedTo, storePath)
{
	this._obj = attachedTo;
	this._obj.addBehavior("#default#userData");
	this._path = storePath;
	this._loaded = false;
}

CPersist.prototype.Save = function()
{
	if(this.IsLoaded())
	{
		var enabled = true;
		var code = "try{ this.GetAttached().save(this._path); } catch(e) {enabled = false;}";
		eval(code);
	}
}

CPersist.prototype.Load = function()
{
	if(!this.IsLoaded())
	{
		var enabled = true;
		var code = "try{ this.GetAttached().load(this._path); } catch(e) {enabled = false;}";
		eval(code);

		if(!enabled)
		{
			return;
		}

		this._loaded = true;
	}
}

CPersist.prototype.GetAttached = function()
{
	return this._obj;
}

CPersist.prototype.IsLoaded = function()
{
	return this._loaded;
}

CPersist.prototype.SetAttribute = function(key, value)
{
	if( !this.IsLoaded() ) this.Load();

	if( this.IsLoaded() )
	{
		this.GetAttached().setAttribute(key,value);
	}
	this.Save();
}

CPersist.prototype.GetAttribute = function(key)
{
	if(!this.IsLoaded()) this.Load();

	if(this.IsLoaded())
	{
		var value = this.GetAttached().getAttribute(key);
	}

	return value;
}

CPersist.prototype.RemoveAttribute = function(key)
{
	if(!this.IsLoaded()) this.Load();

	if(this.IsLoaded())
	{
		this.GetAttached().removeAttribute(key);
	}
	this.Save();
}

CPersist.prototype.RemoveAllAttributes = function()
{
	if(!this.IsLoaded()) this.Load();

	if(this.IsLoaded())
	{
		var oDoc=this.GetAttached().XMLDocument;
		var oNamedNodeMap=oDoc.documentElement.attributes;
		while(oNamedNodeMap.length>0)
		{
			this.GetAttached().removeAttribute(oNamedNodeMap.item(0).nodeName);
		}
	}
	this.Save();
}

function GetControlSetup(oControl)
{
	var oListDoc=new ActiveXObject("Msxml2.DOMDocument");
	var oList=oListDoc.createElement("list");
	oListDoc.appendChild(oList);

	var oColumnsDoc=new ActiveXObject("Msxml2.DOMDocument");
	oColumnsDoc.async=false;
	if(oColumnsDoc.loadXML(oControl.GetSetup()))
	{
		oList.appendChild(oColumnsDoc.documentElement.cloneNode(true));
	}

	var oRows=oListDoc.createElement("rows");
	oList.appendChild(oRows);

	var count=oControl.GetItemCount();
	var oRowsDoc=new ActiveXObject("Msxml2.DOMDocument");
	oRowsDoc.async=false;
	for(var index=0;index<count;index++)
	{
		if(oRowsDoc.loadXML(oControl.getItem(index)))
		{
			oRows.appendChild(oRowsDoc.documentElement.cloneNode(true));
		}
	}
	return oListDoc.xml;
}

// strips off all leading and trailing spaces
String.prototype.trim = function()
{
	return this.replace(/(^\s*)|(\s*$)/g, "");
}

// escapes the string so its safe to insert into a page using innerHTML
String.prototype.fixForHTML=function()
{
	var escString="";
	if(null!=this)
	{
		var strLength=this.length;
		for(var index=0;index<strLength;index++)
		{
			var c=this.charAt(index);
			switch(c)
			{
				case '#':
				{
					escString+="&#35;";
					break;
				}
				case '&':
				{
					escString+="&amp;";
					break;
				}
				case '<':
				{
					escString+="&lt;";
					break;
				}
				case '>':
				{
					escString+="&gt;";
					break;
				}
				case '"':
				{
					escString+="&quot;";
					break;
				}
				default:
				{
					escString+=c;
					break;
				}
			}
		}
	}
	return escString;
}

function startHllapi( system, facility )
{
	try
	{
		var hllapi = new ActiveXObject( "TA2000.TCSWIN" );
		var idi = "SYST=" + system;
		hllapi.StartHllapi( "Trailers", facility, idi );
	}
	catch( e )
	{
		alert( "HLLAPI is not configured correctly to work with this application." );
	}
}

function saveControlPreferences(oControl,scrName,ctrlName,txdir,cz,tidx,facility)
{
	// The string returned from getPreferences() is so long that the only way to
	// concat it to another string is by replacing the beginning of the url
	// string with the string that needs to be at the beginning. += and concat do not work.
	var preferences=encodeURIComponent(oControl.getPreferences().xml);
	var data=preferences.replace(/^/,"value=");

	var url=txdir+"/PreferenceEvent.go?&cz="+cz+"&tx=$FlowController&tidx="+tidx+
		"&pc=update&facilityName="+facility+"&scr="+scrName+"&controlName="+ctrlName;

	var httpRequest=new ActiveXObject("MSXML2.XMLHTTP");
	httpRequest.open("POST",url,false);
	httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	httpRequest.send(data);
	if(httpRequest.status!=200)
	{
		alert("Error "+httpRequest.status);
	}
}

function savePreferences(url)
{
	var httpRequest=new ActiveXObject("MSXML2.XMLHTTP");
	httpRequest.open("POST",url,false);
	httpRequest.send();

	if(httpRequest.status!=200)
	{
		alert("Error "+httpRequest.status);
	}
}

// event handler for the body's onbeforeunload event
function onUnload()
{
	event.returnValue = "Changes may have occurred that have not been saved.";
}

// called when application changed or system fund sponsor has changed
function confirmMessage()
{
	var mainOnBeforeUnload=parent.mainframe.document.body.onbeforeunload;
				
	var confirmYes=true; 

	if(null!=mainOnBeforeUnload)
	{
		var confirmMsg="Are you sure you want to navigate away from this page?\n\n"+
			"Changes may have occurred that have not been saved.\n\n"+
			"Press OK to continue, or Cancel to stay on the current page."
		if(confirm(confirmMsg))
		{
			parent.mainframe.document.body.onbeforeunload=null;
			confirmYes=true;						
		}
		else
		{
			confirmYes=false;
		}
	}
	return confirmYes;
}

function getMonth( date )
{
	return date.substring( 0,2 );
}

function getDay( date )
{
	return date.substring( 3,5 );
}

function getYear( date )
{
	return date.substring( 6,10 );
}

function getCityStateZipString( city, state, zip )
{
	city=city.trim();
	state=state.trim();
	zip=zip.trim();

	var citystatezip=city;

	if(state.length>0)
	{
		citystatezip+=", "+state+".";
	}
	if(citystatezip.length>0 && zip.length>0 && zip!="0")
	{
		// If zip contains a hypen, it's already formatted.
		if(zip.indexOf('-') > 0 )
		{
			citystatezip=citystatezip+" " + zip;
		}
		else
		{
			if(zip.length>5)
			{
				citystatezip+=" "+zip.substring(0,5)+ "-"+ zip.substring(5);
			}
			else
			{
				citystatezip=citystatezip+" " + zip;
			}
		}
	}
	return citystatezip;
}

// Gets a formatted message with replacement parameters.
// Ex alert( getMessage( "See {0} run.  She is much {1} than {2}. Good Job {0}!",
//								 new Array( "Jane", "faster", "Terry" ) );
// Users of this function should store messages is a global error message javascript
// file to assist with the ease of editing messages.
//
// Example:
// The global java script file would contain a var
// var FASTMESSAGE = "See {0} run.  She is much {1} than {2}. Good Job {0}!";
// 
// The the JavaScript in the HTML page can just call
// alert( getMessage( FASTMESSAGE, new Array( "Jane", "faster", "Terry" ) ) );
function getMessage( message, parameters )
{
	if( parameters != null )
	{
		for( var i = 0; i < parameters.length; i++ )
		{
			// x7b = Hexadecimal left curly brace "{"
			// x7d = Hexadeciaml right curly brace "}"
			var re = new RegExp("\\x7b"+i+"\\x7d","g");
			message=message.replace(re,parameters[i]);
		}
	}

	// replace all remaining parameters with empty string.
	var re = new RegExp("\\x7b.*\\x7d","g");
	message=message.replace(re,"");

	return message;
}

// Sets the minimum height on an object.
// iValue is optional, 100 is the default height.
// Example:
//	<tr height="50%">
//		<td style="height:expression(setMinHeight())">......</td>
//	</tr>
function setMinHeight(iValue)
{
	if(iValue==undefined) var iValue=100;
	return iValue;
}

//opens help for current application
function onMnuHelp()
{
	if(typeof(parent.frames['mainframe'].helpId )!="undefined")
	{
		loadHelpById(parent.frames['mainframe'].helpId);
	}
	else
	{
		loadHelpById("");
	}
}

//used to alert an error that has occured on a behavior
function onBehaviorError()
{
	window.event.srcElement.focus();
	alert(window.event.message);
	window.event.srcElement.focus();
}

// button - the button object to enable or disable
// disabled - boolean. True to disable the button, false to enable
function disableButton(button,disabled)
{
	if("disable" in button) button.disable(disabled);
	else button.disabled=disabled;
}
//]]>
