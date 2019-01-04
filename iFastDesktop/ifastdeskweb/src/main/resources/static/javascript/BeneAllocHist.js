var _beneAllocDetails = [];


//******************************************************
function loading()
{
	IFDSTableManager.init();
	
	IFDSTableManager.getTable( "BenAlloc_Table" ).setOnRowSelectedFunction( selectHandler_BenAllocTable )
}

//******************************************************
function selectHandler_BenAllocTable()
{
	var rowIndex = IFDSTableManager.getTable( "BenAlloc_Table" ).getSelectedRowIndex();
	populateDetailsTable( rowIndex );
}

//******************************************************
function populateDetailsTable(rowIndex)
{
	clearDetailsTable();
	
	var detailsTable = UTL.getElem( "BenAllocDetails_Table" );  
	for( var i = 0; i < _beneAllocDetails[rowIndex].length; i++ )
	{		
		var xml = XML.parseToXML( _beneAllocDetails[rowIndex][i] );
		var newRow = document.createElement( "tr" );
		var nameCell = newRow.appendChild( document.createElement( "td" ) );
		nameCell.innerHTML = (XML.getNode( "beneName", xml ).firstChild ? XML.getNode( "beneName", xml ).firstChild.nodeValue : "");
		var effDateCell = newRow.appendChild( document.createElement( "td" ) );
		effDateCell.innerHTML = (XML.getNode( "deff", xml ).firstChild ? XML.getNode( "deff", xml ).firstChild.nodeValue : "");
		var percentCell = newRow.appendChild( document.createElement( "td" ) );
		percentCell.innerHTML = (XML.getNode( "prcnt", xml ).firstChild ? XML.getNode( "prcnt", xml ).firstChild.nodeValue : "");
		var amountCell = newRow.appendChild( document.createElement( "td" ) );
		amountCell.innerHTML = (XML.getNode( "amt", xml ).firstChild ? XML.getNode( "amt", xml ).firstChild.nodeValue : "");
		var reportedCell = newRow.appendChild( document.createElement( "td" ) );
		reportedCell.innerHTML = (XML.getNode( "reported", xml ).firstChild ? XML.getNode( "reported", xml ).firstChild.nodeValue : "");		
		var modDateCell = newRow.appendChild( document.createElement( "td" ) );
		modDateCell.innerHTML = (XML.getNode( "modDate", xml ).firstChild ? XML.getNode( "modDate", xml ).firstChild.nodeValue : "");
		var modUserCell = newRow.appendChild( document.createElement( "td" ) );
		modUserCell.innerHTML = (XML.getNode( "moduser", xml ).firstChild ? XML.getNode( "moduser", xml ).firstChild.nodeValue : "");
		detailsTable.lastChild.appendChild( newRow );				
	}
	IFDSTableManager.reInitTable( "BenAllocDetails_Table" );
	
}

//******************************************************
function clearDetailsTable()
{
	var detailsTable = UTL.getElem( "BenAllocDetails_Table" );
	while( detailsTable.lastChild.lastChild )
	{
		detailsTable.lastChild.removeChild(detailsTable.lastChild.lastChild);
	}
	IFDSTableManager.reInitTable( "BenAllocDetails_Table" );
}


