var DesktopFlag = function( id, type, desc )
{
	this._div = DesktopFlag.buildDiv( id, type );
	this._div.title = desc;	
}

DesktopFlag.ERROR = "Error";
DesktopFlag.WARNING = "Warning";

DesktopFlag.buildDiv = function( id, type )
{	
	var div = null;	
	div = document.createElement( "div" );	
	div.id = id;
	div.className = "Desktop_" + type + "Flag";
	div.style.position = "absolute";	
	div.style.display = "none";
	
	return div;
}

DesktopFlag.changeHandler_assocFld = function( flagRef, evt )
{	
	flagRef.hide();
}

DesktopFlag.prototype.setFieldAssoc = function( fldId )
{
	var flagRef = this;
	var fld = UTL.getElem( fldId );
	EvtHandler.add( fld, "change", function( evt ){ DesktopFlag.changeHandler_assocFld( flagRef, evt ); } ); 
}

DesktopFlag.prototype.setPosition = function( top, left, container )
{
	if ( container )
	{
		container.appendChild( this._div );
	}
	else
	{
		document.body.appendChild( this._div );
	}
	
	this._div.style.top = top;
	this._div.style.left = left;	
}

DesktopFlag.prototype.show = function()
{
	this._div.style.display = "block";
}

DesktopFlag.prototype.hide = function()
{
	this._div.style.display = "none";
}