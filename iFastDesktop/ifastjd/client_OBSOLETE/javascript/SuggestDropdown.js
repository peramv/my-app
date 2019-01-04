function SuggestDropdown(suggestObj, fld)
{
	var _self = this; 
	
	var _suggestObj = suggestObj;
	var _targetField = fld;
	
	var _frameLayer = null;
	
	var _divDropdown = null;
	var _lblError = null;
	var _lblMore = null;	
	var _tblResults = null;
	var _curHighlightRow = null;
	
	init()
	function init()
	{
		buildDropdown(_targetField);
	}
	
	function calcAbsPos(obj)
	{
		
		var curleft = curtop = 0;
		if (obj.offsetParent) 
		{			
			curleft = obj.offsetLeft
			curtop = obj.offsetTop
			while (obj = obj.offsetParent) 
			{
				curleft += obj.offsetLeft
				curtop += obj.offsetTop
			}
		}
		
		var posObj = new Object();
		posObj.top = curtop;
		posObj.left = curleft;
		
		return posObj;	
	}
		
	function buildDropdown(fld)
	{					
		var fldAbsPos = calcAbsPos(fld);
		
		_divDropdown = document.createElement("div");
		_divDropdown.name = "whatthe";
		_divDropdown.style.position = "absolute";
		_divDropdown.style.top = fldAbsPos.top + 22;		
		_divDropdown.style.left = fldAbsPos.left;
        _divDropdown.style.border = "none";
        _divDropdown.style.zIndex = 100;				
		_divDropdown.style.fontSize = "12";
		_divDropdown.style.width = 336;
		_divDropdown.style.height = 230;
		_divDropdown.style.overflow = "hidden";
		_divDropdown.style.display = "none";		
		_divDropdown.style.background = "url(" + _imagePath + "/fundSuggestBackground.gif)";
		_divDropdown.unselectable = "on";
		
		_tblResults = document.createElement("table");
		_tblResults.style.position = "relative";		
		_tblResults.style.fontSize = "12";
		_tblResults.style.top = 2;
		_tblResults.style.left = 2;		
		_tblResults.style.cursor = "pointer";
		_tblResults.unselectable = "on";			   
		_tblResults.appendChild(document.createElement("tbody"));
		_divDropdown.appendChild(_tblResults);
				
		_lblError = document.createElement("label");		
		_lblError.style.position = "relative";		
		_lblError.style.left = 5;			
		_lblError.style.display = "none";
		_lblError.unselectable = "on";
		_divDropdown.appendChild(_lblError);
		
		_lblMore = document.createElement("label");		
		_lblMore.style.position = "relative";		
		_lblMore.style.left = 5;			
		_lblMore.style.display = "none";
		_lblMore.style.fontStyle = "italic";		
		_lblMore.onclick = function(){_suggestObj.doSearch(fld.value, true);};
		_lblMore.unselectable = "on";
		_divDropdown.appendChild(_lblMore);
		
		
		_frameLayer = document.createElement("iframe");
		_frameLayer.tabIndex = "-1";
		_frameLayer.src = "javascript:false;";
		_frameLayer.frameBorder = false;
		_frameLayer.style.position = "absolute";
		_frameLayer.style.border = "none";
		_frameLayer.style.zIndex = 50;
		_frameLayer.style.display = "none";
		_frameLayer.style.left = parseInt(_divDropdown.style.left) + 1;
		_frameLayer.style.top = parseInt(_divDropdown.style.top) + 2;
		_frameLayer.style.height = parseInt(_divDropdown.style.height) - 2;
		_frameLayer.style.width = parseInt(_divDropdown.style.width) - 2;

		
		document.getElementsByTagName("body")[0].appendChild(_frameLayer);
		document.getElementsByTagName("body")[0].appendChild(_divDropdown);
	}
	
	this.populateResultTable = function(resultsArray)	
	{
		for(var i = 0; i < resultsArray.length; i++)
		{
			var tr = document.createElement("tr");			
			var td = document.createElement("td");
			td.unselectable = "on";			
			td.innerHTML = resultsArray[i].displayVal;
			
			for(var prop in resultsArray[i])
			{
				td[prop] = resultsArray[i][prop];
			}			
			
			tr.appendChild(td);			
			_tblResults.firstChild.appendChild(tr);
		
			tr.onmouseenter = function(){_self.highlightRow(this)};
			tr.unselectable = "on";			
			tr.onclick = this.selectRow;
			
		}
	}
	
	this.highlightRow = function(row)
	{
		if(_curHighlightRow != null)
		{
			_curHighlightRow.style.background = "none";
		}						
		row.style.background = "yellow";
		_curHighlightRow = row;
	}
	
	
	this.selectRow = function()
	{					
		if(_curHighlightRow != null)
		{
			_suggestObj.setValue(_curHighlightRow.firstChild);		      			
			_self.disable();
		}
	}
	
	this.highlightFirstRow = function()
	{
		this.highlightRow(_tblResults.firstChild.firstChild);
	}
	
	this.highlightNextRow = function()
	{		
		if(_curHighlightRow != null && _curHighlightRow.nextSibling != null)
		{
			var temp = _curHighlightRow;			
			this.highlightRow(temp.nextSibling);
		}										
	}
	
	this.highlightPrevRow = function()
	{					
		if(_curHighlightRow != null && _curHighlightRow.previousSibling != null)
		{
			var temp = _curHighlightRow;			
			this.highlightRow(temp.previousSibling);
		}
	}
	
	this.clearTable = function()
	{					
		for(var i = _tblResults.firstChild.childNodes.length - 1; i > -1; i--)
		{						
			_tblResults.firstChild.removeChild(_tblResults.firstChild.childNodes[i]);
		}
		
		_lblError.style.display = "none";
		_lblMore.style.display = "none";
		_divDropdown.style.display = "none";
		_frameLayer.style.display = "none";			
	}
	
	this.setError = function(text)
	{
		_lblError.innerHTML = text;
		_lblError.style.display = "block";
		_lblMore.style.display = "none";
	}
	
	this.setMore = function(text)
	{
		_lblMore.innerHTML = text;
		_lblMore.style.display = "block";
		_lblError.style.display = "none";
	}
	
	this.enable = function()
	{
		_frameLayer.style.display = "block";
		_divDropdown.style.display = "block";
	}
	
	this.isEnabled = function()
	{
		return (_divDropdown.style.display == "block");
	}
	
	this.disable = function()
	{		
		_frameLayer.style.display = "none";
		_divDropdown.style.display = "none";		
	}
}