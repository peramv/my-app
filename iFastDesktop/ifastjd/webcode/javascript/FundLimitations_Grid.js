/**
 * Please don't use FundLimitations_Grid for future development..
 */

var curRuleArray = new Array();
var curEntity = null;

function onAccountSelect(row)
{
  if (row != null)
  {
    // the following if statement will add all selected to the array when the ctrl key is pressed
//PMI    if ( event.ctrlKey )
//PMI    {
//PMI      curRuleArray[curRuleArray.length] = row;
//PMI      highlightRow(null, row);
//PMI    }
//PMI    else
    {
      _currentRow = Number(row.id.substr(3, (row.id.length-3)));
      highlightRow(curRuleArray, row);
      delete curRuleArray;
      curRuleArray = new Array();
      curRuleArray[0] = row;
     //alert(curRuleArray[0].childNodes[5].innerHTML);
    }

    curAccount = row;
  }
}

function highlightRow(prevSel, newSel)
{
  if(prevSel != null)
  {
    for (var i = 0;  i<prevSel.length; i++)
    {
        prevSel[i].style.background = 'white';
        prevSel[i].style.color = 'black';
    }
  }
//PMI  newSel.style.background = "#eef0f5";
    newSel.style.background = "darkBlue";
    newSel.style.color = "white";
}

function clearGrid(tableId)
{
  var grid = document.getElementById(tableId).firstChild;
  var gridRows = grid.childNodes;

  // don't delete the row header
  for(var i = gridRows.length - 1; i > 0; i--)
  {
    grid.removeChild(gridRows[i]);
  }
}