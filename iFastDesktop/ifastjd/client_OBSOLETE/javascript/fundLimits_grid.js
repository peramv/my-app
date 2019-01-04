var curRuleArray = new Array();
var curEntity = null;

function onAccountSelect(row) {
	if (row != null) {
	//the following if statement will add all selected to the array when the ctrl key is pressed
	//	if (event.ctrlKey) {
	//		curRuleArray[curRuleArray.length] = row;
	//		highlightRow(null, row);
	//	}
	//	else {
			_currentRow = Number(row.id.substr(3, (row.id.length-3)));	
			highlightRow(curRuleArray, row);
			delete curRuleArray;
			curRuleArray = new Array();
			curRuleArray[0] = row;
			//alert(curRuleArray[0].childNodes[5].innerHTML);	
	//	}
		curAccount = row;
	}
}

function highlightRow(prevSel, newSel) {
	if(prevSel != null)
	{
		for (var i = 0;  i<prevSel.length; i++) {
			prevSel[i].style.background = 'white';
		}		
	}
	newSel.style.background = "#eef0f5";		
}

function clearGrid(tableId) {
	var grid = document.getElementById(tableId).firstChild;
	var gridRows = grid.childNodes;
	
	// don't delete the row header
	for(var i = gridRows.length - 1; i > 0; i--)
	{		
	grid.removeChild(gridRows[i]);
	}		
}