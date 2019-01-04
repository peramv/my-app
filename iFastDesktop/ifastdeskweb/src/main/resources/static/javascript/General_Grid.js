
var myself;
IFDSTable.prototype.SORT_COLUMN_INDEX = 0;
IFDSTable.prototype.minWidth = 110;
IFDSTable.prototype.dragingColumn = null;
IFDSTable.prototype.startingX = 0;
IFDSTable.prototype.currentX = 0;
IFDSTable.prototype.columns = null;
IFDSTable.prototype.trs = null;
IFDSTable.prototype.mysearchid = null;
IFDSTable.prototype.mysearchcatid = null;
IFDSTable.prototype.mytableid = null;
IFDSTable.prototype.timerID = null;
IFDSTable.prototype.myobj = null;
IFDSTable.prototype.mytbody = null;
IFDSTable.prototype.createCookie = function(name, value, days) {
   if (days) {
      var date = new Date();
      date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
      var expires = "; expires=" + date.toGMTString();
      }
   else var expires = "";
   document.cookie = name + "=" + value + expires + "; path=/";
   }
IFDSTable.prototype.readCookie = function(name) {
   var nameEQ = name + "=";
   var ca = document.cookie.split(';');
   for(var i = 0; i < ca.length; i++) {
      var c = ca[i];
      while (c.charAt(0) == ' ') c = c.substring(1, c.length);
      if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length);
      }
   return null;
   }
IFDSTable.prototype.dosearch = function () {
   myself = this.myobj;
   if(document.getElementById(myself.mysearchid) != null && document.getElementById(myself.mysearchid).value != "")myself.redrawtable();
   }
IFDSTable.prototype.redrawtable = function () {
   var tbody = myself.mytbody;
   while (tbody.childNodes[0]) tbody.removeChild(tbody.childNodes[0]);
   var searchtext = "";
   if(document.getElementById(myself.mysearchid) != null) searchtext = document.getElementById(myself.mysearchid).value;
   var searchcat = "";
   if(document.getElementById(myself.mysearchcatid) != null) searchcat = document.getElementById(myself.mysearchcatid).value;
   var rowcount = 0;
   for(var j = 0; j < myself.trs.length; j++) {
      var shouldlist = false;
      mycurrent_row = myself.trs[j];
      for(var i = 0; i < mycurrent_row.childNodes.length; i++) {
         var td = mycurrent_row.childNodes[i];
         if (td.nodeName.toLowerCase () == "td") shouldlist = shouldlist || (((searchcat == "" || searchcat == "All" || searchcat == myself.columns[i].headertext)) && td.getAttribute("rawdata").toLowerCase().indexOf(searchtext) >= 0);
         }
      if(shouldlist) {
         mycurrent_row.className = (++rowcount % 2) == 0 ? "tdcolor" : "tdnormal";
         tbody.appendChild(mycurrent_row);
         }
      }
   }
IFDSTable.prototype.findPosX = function (obj) {
   var curleft = 0;
   if (obj.offsetParent) {
      while (obj.offsetParent) {
         curleft += obj.offsetLeft - obj.scrollLeft;
         obj = obj.offsetParent;
         }
      }
   else if (obj.x) curleft += obj.x;
   return curleft;
   }
IFDSTable.prototype.getNewWidth = function () {
   var newWidth = myself.minWidth;
   if (myself.dragingColumn != null) {
      newWidth = parseInt (myself.dragingColumn.style.width);
      if (isNaN (newWidth)) {
         newWidth = 0;
         }
      newWidth += myself.currentX - myself.startingX;
      if (newWidth < myself.minWidth) {
         newWidth = myself.minWidth;
         }
      }
   return newWidth;
   }
IFDSTable.prototype.columnMouseDownSelect = function (event) {
   if(window.event.srcElement.tagName.toLowerCase () == "th")myself = window.event.srcElement.myobj ;
   if (!event) {
      event = window.event;
      }
   var d = myself.findPosX(myself.columns[0].parentNode.parentNode);
   for(i = 0; i < myself.columns.length; i++) {
      d += parseInt(myself.columns[i].style.width);
      if(Math.abs(d - event.clientX) < 4) {
         myself.columns[i].style.cursor = "col-resize";
         myself.startingX = event.clientX;
         myself.currentX = myself.startingX;
         break;
         }
      else {
         myself.columns[i].style.cursor = "default";
         }
      }
   return true;
   }
IFDSTable.prototype.getSelectedRow = function() {
   var trs = myself.trs;
   for (j = 0; j < trs.length; j++) {
      var tableRowNode = trs[j];
      if (tableRowNode.nodeName.toLowerCase () == "tr" && tableRowNode.ishighlight == 1) return tableRowNode;
      }
   return null;
   }
IFDSTable.prototype.removeSelectedRow = function() {
   var trs = myself.trs;
   for (j = 0; j < trs.length; j++) {
      var tableRowNode = trs[j];
      if (tableRowNode.nodeName.toLowerCase () == "tr" && tableRowNode.ishighlight == 1) {
         trs.splice(j, 1);
         break;
         }
      }
   myself.redrawtable();
   }
IFDSTable.prototype.rowOnClick = function (event) {
   var tr = window.event.srcElement.parentNode;
   var tbody = tr.parentNode;
   var rowcount = 0;
   for (j = 0; j < tbody.childNodes.length; j++) {
      var tableRowNode = tbody.childNodes[j];
      if (tableRowNode.nodeName.toLowerCase () == "tr") {
         ++rowcount;
         if( tableRowNode.ishighlight == 1) {
            tableRowNode.ishighlight = 0;
            tableRowNode.className = (rowcount % 2) == 0 ? "tdcolor" : "tdnormal";
            break;
            }
         }
      }
   tr.ishighlight = 1;
   tr.className = "trhighlightcolor";
   }
IFDSTable.prototype.columnMouseDown = function (event) {
   if(window.event.srcElement.tagName.toLowerCase () == "th")myself = window.event.srcElement.myobj ;
   if (!event) {
      event = window.event;
      }
   var d = myself.findPosX(myself.columns[0].parentNode.parentNode);
   for(i = 0; i < myself.columns.length; i++) {
      d += parseInt(myself.columns[i].style.width);
      if(Math.abs(d - event.clientX) < 4) {
         myself.dragingColumn = myself.columns[i];
         myself.dragingColumn.style.cursor = "col-resize";
         myself.startingX = event.clientX;
         myself.currentX = myself.startingX;
         document.body.onmouseup = myself.columnMouseUp;
         document.body.onmousemove = myself.columnMouseMove;
         break;
         }
      }
   return true;
   }
IFDSTable.prototype.columnMouseUp = function () {
   if(window.event.srcElement.tagName.toLowerCase () == "th")myself = window.event.srcElement.myobj ;
   if (myself.dragingColumn != null) {
      myself.dragingColumn.style.width = myself.getNewWidth ();
      myself.dragingColumn.style.cursor = "default";
      document.body.onmousemove = null;
      myself.dragingColumn = null;
      myself.savecolwidth();
      }
   return true;
   }
IFDSTable.prototype.myonkeydown = function () {

   for (i = 1; i < this.rows.length; i++) {
      var row = this.rows[i];
      if( row.ishighlight == 1) {
         this.rows[i].ishighlight = 0;
         this.rows[i].className = (i % 2) == 0 ? "tdcolor" : "tdnormal";
         if(window.event.keyCode == 40) {
            // arrow down
            i = (i == this.rows.length - 1) ? 1 : i + 1;
            }
         else if(window.event.keyCode == 38) {
            //arrow up
            i = (i == 1) ? this.rows.length - 1 : i - 1;
            }
         else {
            return true;
            }
         this.rows[i].ishighlight = 1;
         this.rows[i].className = "trhighlightcolor";
         return false;
         }
      }
   }
IFDSTable.prototype.savecolwidth = function () {
   var widths = "";
   for(i = 0; i < myself.columns.length; i++) {
      d = parseInt(myself.columns[i].style.width);
      if(i == 0) widths = d;
      else widths += "," + d;
      }
   myself.createCookie(myself.mytableid + "widths", widths, 365);
   }
IFDSTable.prototype.applycolwidth = function () {
   var widths = myself.readCookie(myself.mytableid + "widths");
   if(widths != null) {
      var myarray = widths.split(",");
      for(i = 0; i < myself.columns.length; i++) {
         myself.columns[i].style.width = myarray[i];
         }
      }
   }
IFDSTable.prototype.columnMouseMove = function (event) {
   if(window.event.srcElement.tagName.toLowerCase () == "th")myself = window.event.srcElement.myobj ;
   if (!event) {
      event = window.event;
      }
   if (myself.dragingColumn != null) {
      myself.dragingColumn.style.cursor = "col-resize";
      myself.currentX = event.clientX;
      myself.dragingColumn.style.width = myself.getNewWidth ();
      myself.startingX = event.clientX;
      myself.currentX = myself.startingX;
      }
   return false;
   }
IFDSTable.prototype.triggerredraw = function () {
   myself = this.myobj;
   if(myself.timerID != null) {
      clearTimeout(myself.timerID);
      myself.timerID = null;
      }
   myself.timerID = self.setTimeout("myself.redrawtable()", 200);
   }
function IFDSTable(tableid, searchid, searchcatid, width, height) {
   
   if(document.getElementById(tableid) != null) {
   	
      myself = this;
       
      this.myobj = this;
     
      document.getElementById(tableid).className = "sortable";
      myself.mytableid = tableid;
      myself.mysearchid = searchid;
      myself.mysearchcatid = searchcatid;
      var table = document.getElementById (tableid);
      
      if (table != null) {
         table.IFDSTable = this;
         table.onkeydown = myself.myonkeydown;
         if (table.nodeName.toLowerCase () == "table") {
            // create div
            mytableborder = document.createElement("div");
            table.parentNode.insertBefore(mytableborder, table);
            mytableborder.appendChild(table);
            mytableborder.className = "tableborder";
            if(height != 0) mytableborder.style.height = height;
            if(width != 0) mytableborder.style.width = width;
            
            
            
            for (i = 0; i < table.childNodes.length; i++) {
               var tablechild = table.childNodes[i];
               // Tables without header will not be handled.
               
               
               if (tablechild.nodeName.toLowerCase () == "thead") {
                  for (j = 0; j < tablechild.childNodes.length; j++) {
                     var tableHeadNode = tablechild.childNodes[j];
                     if (tableHeadNode.nodeName.toLowerCase () == "tr") {
                        if(myself.columns == null) myself.columns = new Array(tableHeadNode.childNodes.length);
                        
                        myself.trs = new Array();
                        
                        for (k = 0; k < tableHeadNode.childNodes.length; k++) {
                           var column = tableHeadNode.childNodes[k];                           
                           column.style.width = (column.offsetWidth < myself.minWidth) ? myself.minWidth : column.offsetWidth;
                           column.onmousedown = myself.columnMouseDown;
                           column.onmousemove = myself.columnMouseDownSelect;
                           myself.columns[k] = column;
                           myself.columns[k].myobj = myself;
                           myself.columns[k].headertext = myself.ts_getInnerText(column);
                           tableHeadNode.childNodes[k].innerHTML = '<a href="#" class="sortheader" ' + 'onclick="myself.ts_resortTable(this);return false;">' + myself.columns[k].headertext + '<span class="sortarrow">&nbsp;&nbsp;&nbsp;</span></a>';
                           }
                        }
                        
                     }
                  table.style.tableLayout = "fixed";
                  }
                  
               
               if (tablechild.nodeName.toLowerCase () == "tbody") {
               	  
                  myself.mytbody = tablechild;
                  var rowcount = 0;
                  for (j = 0; j < tablechild.childNodes.length; j++) {
                     var tableRowNode = tablechild.childNodes[j];
                     if (tableRowNode.nodeName.toLowerCase () == "tr") {
                        tableRowNode.onclick = myself.rowOnClick;
                        tableRowNode.className = (++rowcount % 2) == 0 ? "tdcolor" : "tdnormal";
                        for (k = 0; k < tableRowNode.childNodes.length; k++) {
                           if (tableRowNode.childNodes[k].nodeName.toLowerCase () == "td") {
                              tableRowNode.childNodes[k].setAttribute("rawdata", myself.ts_getInnerText(tableRowNode.childNodes[k]));
                              }
                           }
                        myself.trs.push(tableRowNode);
                        }
                     }
                  }
               }
            }
         }
      if(document.getElementById(myself.mysearchcatid) != null) {
         var sel = document.getElementById(myself.mysearchcatid);
         sel.myobj = myself;
         sel.onchange = myself.dosearch;
         for( i = 0; i < myself.columns.length; i++) {
            document.getElementById(myself.mysearchcatid).options[i + 1] = new Option(myself.columns[i].headertext, myself.columns[i].headertext);
            }
         }
      if(document.getElementById(myself.mysearchid) != null) {
         var ed = document.getElementById(myself.mysearchid);
         ed.myobj = myself;
         ed.onkeyup = myself.triggerredraw;
         }
      myself.dosearch();
      myself.applycolwidth();
      }
   }
IFDSTable.prototype.ts_getInnerText = function (el) {
   if (typeof el == "string" || typeof el == "undefined") return el;
   if (el.innerText) return el.innerText;
   //Not needed but it is faster
   var str = "";
   var cs = el.childNodes;
   var l = cs.length;
   for (var i = 0; i < l; i++) {
      switch (cs[i].nodeType) {
         case 1 : //ELEMENT_NODE
         str += myself.ts_getInnerText(cs[i]);
         break;
         case 3 : //TEXT_NODE
         str += cs[i].nodeValue;
         break;
         }
      }
   return str;
   }
IFDSTable.prototype.resortColumn = function (colname) {
   for (var i = 0; i < myself.columns.length; i++) {
      if(myself.columns[i].headertext == colname)myself.ts_resortTable(myself.columns[i].childNodes[0]);
      }
   }
IFDSTable.prototype.ts_resortTable = function (lnk) {
   // get the span
   var span;
   for (var ci = 0; ci < lnk.childNodes.length; ci++) {
      if (lnk.childNodes[ci].tagName && lnk.childNodes[ci].tagName.toLowerCase() == 'span') span = lnk.childNodes[ci];
      }
   var spantext = myself.ts_getInnerText(span);
   var td = lnk.parentNode;
   var column = td.cellIndex;
   var table = document.getElementById (myself.mytableid);
   // Work out a type for the column
   if (table.rows.length <= 1) return;
   var itm = myself.ts_getInnerText(table.rows[1].cells[column]);
   myself.SORT_COLUMN_INDEX = column;
   sortfn = myself.ts_sort_caseinsensitive;
   if (itm.match(/^\d\d[\/-]\d\d[\/-]\d\d\d\d$/)) sortfn = myself.ts_sort_date;
   if (itm.match(/^\d\d[\/-]\d\d[\/-]\d\d$/)) sortfn = myself.ts_sort_date;
   if (itm.match(/^[$]/)) sortfn = myself.ts_sort_currency;
   if (itm.match(/^[\d\.]+$/)) sortfn = myself.ts_sort_numeric;
   var firstRow = new Array();
   var newRows = new Array();
   for (i = 0; i < table.rows[0].length; i++) {
      firstRow[i] = table.rows[0][i];
      }
   for (j = 1; j < table.rows.length; j++) {
      newRows[j - 1] = table.rows[j];
      }
   newRows.sort(sortfn);
   //if (span.getAttribute("sortdir") == 'down') {
   //   ARROW = '&nbsp;&nbsp;&uarr;';
   //   newRows.reverse();
   //   span.setAttribute('sortdir', 'up');
   //   }
   //else {
      ARROW = '&nbsp;&nbsp;&darr;';
      span.setAttribute('sortdir', 'down');
   //   }
   for (i = 0; i < newRows.length; i++) {
      if (!newRows[i].className || (newRows[i].className && (newRows[i].className.indexOf('sortbottom') == - 1))) table.tBodies[0].appendChild(newRows[i]);
      }
   for (i = 0; i < newRows.length; i++) {
      if (newRows[i].className && (newRows[i].className.indexOf('sortbottom') != - 1)) table.tBodies[0].appendChild(newRows[i]);
      }
   var allspans = document.getElementsByTagName("span");
   for (var ci = 0; ci < allspans.length; ci++) {
      if (allspans[ci].className == 'sortarrow') {
         if (myself.getParent(allspans[ci], "table") == myself.getParent(lnk, "table")) {
            allspans[ci].innerHTML = '&nbsp;&nbsp;&nbsp;';
            }
         }
      }
   span.innerHTML = ARROW;
   myself.coloringRows();
   }
IFDSTable.prototype.coloringRows = function () {
   var tbody = myself.mytbody;
   var rowcount = 0;
   for (j = 0; j < tbody.childNodes.length; j++) {
      var tableRowNode = tbody.childNodes[j];
      if (tableRowNode.nodeName.toLowerCase () == "tr") {
         tableRowNode.className = (++rowcount % 2) == 0 ? "tdcolor" : "tdnormal";
         if(tableRowNode.ishighlight == 1) tableRowNode.className = "trhighlightcolor";
         }
      }
   }
IFDSTable.prototype.getParent = function (el, pTagName) {
   if (el == null) return null;
   else if (el.nodeType == 1 && el.tagName.toLowerCase() == pTagName.toLowerCase()) return el;
   else return myself.getParent(el.parentNode, pTagName);
   }
IFDSTable.prototype.ts_sort_date = function (a, b) {
   aa = myself.ts_getInnerText(a.cells[myself.SORT_COLUMN_INDEX]);
   bb = myself.ts_getInnerText(b.cells[myself.SORT_COLUMN_INDEX]);
   if (aa.length == 10) {
      dt1 = aa.substr(6, 4) + aa.substr(3, 2) + aa.substr(0, 2);
      }
   else {
      yr = aa.substr(6, 2);
      yr = (parseInt(yr) < 50) ? '20' + yr : '19' + yr;
      dt1 = yr + aa.substr(3, 2) + aa.substr(0, 2);
      }
   if (bb.length == 10) {
      dt2 = bb.substr(6, 4) + bb.substr(3, 2) + bb.substr(0, 2);
      }
   else {
      yr = bb.substr(6, 2);
      yr = (parseInt(yr) < 50) ? '20' + yr : '19' + yr;
      dt2 = yr + bb.substr(3, 2) + bb.substr(0, 2);
      }
   if (dt1 == dt2) return 0;
   if (dt1 < dt2) return - 1;
   return 1;
   }
IFDSTable.prototype.ts_sort_currency = function (a, b) {
   aa = myself.ts_getInnerText(a.cells[myself.SORT_COLUMN_INDEX]).replace(/[^0-9.]/g, '');
   bb = myself.ts_getInnerText(b.cells[myself.SORT_COLUMN_INDEX]).replace(/[^0-9.]/g, '');
   return parseFloat(aa) - parseFloat(bb);
   }
IFDSTable.prototype.ts_sort_numeric = function (a, b) {
   aa = parseFloat(myself.ts_getInnerText(a.cells[myself.SORT_COLUMN_INDEX]));
   if (isNaN(aa)) aa = 0;
   bb = parseFloat(myself.ts_getInnerText(b.cells[myself.SORT_COLUMN_INDEX]));
   if (isNaN(bb)) bb = 0;
   return aa - bb;
   }
IFDSTable.prototype.ts_sort_caseinsensitive = function (a, b) {
   aa = myself.ts_getInnerText(a.cells[myself.SORT_COLUMN_INDEX]).toLowerCase();
   bb = myself.ts_getInnerText(b.cells[myself.SORT_COLUMN_INDEX]).toLowerCase();
   if (aa == bb) return 0;
   if (aa < bb) return - 1;
   return 1;
   }
IFDSTable.prototype.ts_sort_default = function (a, b) {
   aa = myself.ts_getInnerText(a.cells[myself.SORT_COLUMN_INDEX]);
   bb = myself.ts_getInnerText(b.cells[myself.SORT_COLUMN_INDEX]);
   if (aa == bb) return 0;
   if (aa < bb) return - 1;
   return 1;
   }

