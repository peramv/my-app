var XML_Lib = new function()
{
	/********************************************************************************************
	 * METHOD: createXMLDoc
	 * 
	 * DESC: Returns xml dom doc, using browser appropriate method.
	 *  
	 ********************************************************************************************/		
	this.createXMLDoc = function()
	{
		// IE
	    if(window.ActiveXObject)
	    {
	    	return new ActiveXObject("Microsoft.XMLDOM");
	    }
	    // MOZ
	    else
	    {
	    	return document.implementation.createDocument("","",null);
	    }
	}
	
	
	/********************************************************************************************
	 * METHOD: loadFromFile
	 * 
	 * DESC: loads xml into xmlDoc, from the specified file
	 *  
	 ********************************************************************************************/
	 this.loadFromFile = function(xmlDoc, fileName)
	 {
	 	xmlDoc.load(fileName);
	 } 
	 
	 
	/********************************************************************************************
	 * METHOD: loadFromString
	 * 
	 * DESC: loads xml into xmlDoc, from the given string
	 *  
	 ********************************************************************************************/
	 this.loadFromString = function(xmlDoc, xmlStr)
	 {
	 	// IE
	 	if(window.ActiveXObject)
	 	{
	 		xmlDoc.loadXML(xmlStr);
	 	}
	 	// MOZ
	 	else
	 	{
	 		var domParser = new DOMParser();
	 		var newXMLDoc = domParser.parseFromString(xmlStr, "text/xml");
	 		xmlDoc = newXMLDoc;
	 	}
	 }
	
	
	/********************************************************************************************
	 * METHOD: createXMLStr
	 * 
	 * DESC: Returns a string in xml format ie."<nodeName>nodeValue</nodeName>"
	 *  
	 ********************************************************************************************/
	this.createXMLStr = function(nodeName, nodeValue)
	{
		return "<" + nodeName + ">" + nodeValue + "</" + nodeName + ">";
	}
}
