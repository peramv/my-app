function Grid(id)
{
	var _self = this;
	
	/* ---------------------------------- VARIABLES ------------------------------- */	
	var _tbl                 = null;
	var _highlightedRow      = null;
	
	var _onRowClickFunction  = null;
	var _clickedRow          = null;
	
	/* -------------------------------- INITIALIZATION ---------------------------- */
	init();
	function init()
	{		
		_tbl = document.getElementById(id);
	}
	
    
	/* ------------------------------- PRIVATE FUNCTIONS --------------------------- */
	
	/********************************************************************************
	 * 
	 ********************************************************************************/
	this.unhighlightRow = function(row)
	{		
		for(var i = 0; i < row.childNodes.length; i++)
		{
			row.childNodes[i].style.background = "white";
			row.childNodes[i].style.color = "black";
		}
	}
	
	
	/* -------------------------------- PUBLIC FUNCTIONS ---------------------------- */
	
	/********************************************************************************
	 * 
	 ********************************************************************************/
	this.highlightRow = function(row)
	{
		if(_highlightedRow != null)
		{			
			this.unhighlightRow(_highlightedRow);
		}
				
		for(var i = 0; i < row.childNodes.length; i++)
		{
			row.childNodes[i].style.background = "#00007E";
			row.childNodes[i].style.color = "white";
		}
		_highlightedRow = row;
	}
	
	
	/********************************************************************************
	 * 
	 ********************************************************************************/
	 this.setOnRowClickFunction = function(fn)
	 {	 
	 	_onRowClickFunction = fn;
	 	
	 	var rowsArray = _tbl.firstChild.childNodes;	 			
	 	for(var i = 1; i < rowsArray.length; i++)
	 	{
	 		var row = rowsArray[i];
	 		row.onclick = function()
				 					 {  				 					 	
				 					 	if(_onRowClickFunction != null)
				 					 	{	 		
				 					 		// note: this = the row that has been clicked			 		
				 					 		_onRowClickFunction(this);
				 					 	}	 					 	
				 					 };
	 	}
	 }
	
	
	/********************************************************************************
	 * 
	 ********************************************************************************/
	 this.getRowCount = function()
	 {
	 	return _tbl.firstChild.childNodes.length;
	 }
	
		
	/********************************************************************************
	 * 
	 ********************************************************************************/
	this.getRow = function(num)
	{
	 	   	
		if(num < _tbl.firstChild.childNodes.length)
		{
			return _tbl.firstChild.childNodes[num];
		}
		else
		{
			alert("getRow - index error");
			return null;
		}	
	}
	
	
	/********************************************************************************
	 * 
	 ********************************************************************************/
this.getCell = function(row, cellNum)
	{
		var rowObj = null;
	
		if(typeof row == "object")
		{
			rowObj = row;
		}
		else if(typeof row == "number")
		{
			rowObj = this.getRow(row);
		}
		else
		{
			alert("row parameter is invalid");
		}
			
		if(rowObj != null)
		{
			if(cellNum < rowObj.childNodes.length)
			{
				return rowObj.childNodes[cellNum];
			}			
		}
		else
		{
			alert('cell number parameter is invalid');
			return null;
		}
	}

	

	
	/********************************************************************************
	 * 
	 ********************************************************************************/
	 this.deleteRowByNum = function(rowNum)
	 {
	 	var row = this.getRow(rowNum);
	 	if(row != null)
	 	{
	 		_tbl.firstChild.removeChild(row);	 		
	 	}
	 	else
	 	{
	 		alert('deleteRow - index error');
	 	}	
	 }
	 
	 this.deleteRow = function(row)
	 {
	 	if(row != null)
	 	{
	 		_tbl.firstChild.removeChild(row);	 		
	 	}
	 	else
	 	{
	 		alert('deleteRow - index error');
	 	}	
	 }
	 
	 
	/********************************************************************************
	 * 
	 ********************************************************************************/
	 this.deleteAllRows = function()
	 {	 	
	 	// don't delete the header
	 	for(var i = _tbl.firstChild.childNodes.length - 1; i > 0; i--)
	 	{
	 		this.deleteRowByNum(i);
	 	}
	 }
	 
	 
	/********************************************************************************
	 * 
	 ********************************************************************************/
	 this.addRow = function(rowHTML)
	 {	 
	 	alert(rowHTML);
	 	var curHTML = _tbl.firstChild.innerHTML;
	 	alert(curHTML);
	 	alert(curHTML + rowHTML);
	 	_tbl.firstChild.innerHTML = "";	
	 	//_tbl.firstChild.innerHTML = rowHTML;
	 }
	 
	 
	 
	/********************************************************************************
	 * 
	 ********************************************************************************/
	 this.addRowByValues = function(valueArray)
	 {
	 	var newRow = document.createElement('tr');
	 	newRow.className = "grid";	 		 	
	 	newRow.onclick = function()
	 					 {
	 					 	if(_onRowClickFunction != null)	 					 	
	 					 	{	 					 		
	 					 		// note: this = the row that has been clicked
	 					 		_onRowClickFunction(this);
	 					 	}	 					 	
	 					 };
	 					 
	 	for(var i = 0; i < valueArray.length; i++)
	 	{
	 		var newCell = document.createElement('td');
	 		if(i == valueArray.length - 1)
	 		{
	 			newCell.className = "grid_end";	 		
	 		}
	 		else
	 		{
	 			newCell.className = "grid";
	 		} 
			
			if(valueArray[i] == "")
			{
				newCell.innerHTML = "&nbsp;";
			}
			else
			{
				newCell.innerHTML = valueArray[i]
			}
	 
	 		newRow.appendChild(newCell);
	 	}
	 	_tbl.firstChild.appendChild(newRow);
	 	
	 	return newRow;
	 }
	 
	 
	/********************************************************************************
	 * xml format:<row><col>val</col><col>val</col></row>, number of cols must 
	 * match the number of cols in the grid
	 ********************************************************************************/
	 this.addRowByXML = function(xml)
	 {	 
	 	// issue with split function - ignores empty strings
	 	var colsXML = xml.replace(/<col>/g, "<col>+");
	 	// strip off <row><col> and </col></row> from start/end	 	
	 	colsXML = colsXML.substring(5 + 5, colsXML.length - 6 - 6);	 		 		
	 	var valueArray = colsXML.split(/<\/col><col>/);
	 	
	 	for(var i = 0; i < valueArray.length; i++)
	 	{
	 		if(valueArray[i] == "+")
	 		{
	 			valueArray[i] = "";
	 		}
	 		else
	 		{
	 			valueArray[i] = valueArray[i].substring(1);
	 		}
	 	}	 	
	 	return this.addRowByValues(valueArray);
	 }
	 
	 
	 /********************************************************************************
	 * xml format:<rows><row><col>val</col><col>val</col></row></rows>, number of cols must 
	 * match the number of cols in the grid
	 ********************************************************************************/
	 this.addRowsByXML = function(xml)
	 {
	 	// strip off <rows> and </rows>
	 	var rowsXML = xml.substring(6, xml.length - 7);	 		 		
	 	var index = 0;
	 	while(index < rowsXML.length)
	 	{	 			 		
	 		var rowXML = rowsXML.substring(index, rowsXML.indexOf('</row>', index + 1) + 6);	 		
	 		this.addRowByXML(rowXML);
	 		
	 		index = rowsXML.indexOf("</row>", index + 1) + 6;
	 	}
	 }
}

