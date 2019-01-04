/**
 *
 *  -------------------------------------------------------------------------
 *                                 Copyright
 *
 *               International Financial Data Services Limited 2003
 *                            All rights reserved.
 *
 *  No part of this document may be reproduced, stored in a retrieval system,
 *  or transmitted, in any form or by any means, electronic, mechanical,
 *  photocopying, networking or otherwise, without the prior written permission
 *  of International Financial Data Services Limited. The computer system, procedures,
 *  data bases, and programs created and maintained by International Financial Data
 *  Services Limited are proprietary in nature and as such are confidential.
 *  Any unauthorised use, misuse, or disclosure of such items or information
 *  may result in civil liabilities and may be subject to criminal penalties
 *  under the applicable laws.
 *  -------------------------------------------------------------------------
 *
*/

/**
*
*
*/

var _httpRequest = null;

function createXMLElement(tag, value)
{
    return "<" + tag + ">" + value + "</" + tag + ">";
}

/********************************************************************************
 *
 ********************************************************************************/
function buildBaseURL(jobname)
{
   var envName     = document.getElementById("envName").value;   
   var companyCode = document.getElementById("companyCode").value;
   var ruserId     = document.getElementById("ruserId").value;
   var sessionId   = document.getElementById("sessionId").value;
   var bgColor   = document.getElementById("bgColor").value;
      
   var dateFormat  = ( document.getElementById("dateFormat") ? document.getElementById("dateFormat").value : "" );

   return "" + _servletPath +
       "?cz=" + _cz +
       "&jobname=" + jobname +
       "&envName=" + envName +
       "&dateFormat=" + dateFormat +
       "&companyCode=" + companyCode +
       "&ruserId=" + ruserId +
       "&sessionId=" + sessionId +
       "&bgcolor=" + bgColor;
}


/********************************************************************************
 *
 ********************************************************************************/
function appendParam(url, param, value)
{
    return "" + url + "&" + param + "=" + value;
}


function gotoJob(jobname, cjobname)
{
    document.getElementById("fldJobname").value = jobname;
    document.getElementById("cjobname").value = cjobname;
    document.myform.submit();
}


/********************************************************************************
 *
 ********************************************************************************/

function callJobSimple(url)
{
    _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
    _httpRequest.open("POST", url, false);
    _httpRequest.send();
}


function callJob(url, fn)
{
    _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
    _httpRequest.open("POST", url, true);
    _httpRequest.onreadystatechange = fn;
    _httpRequest.send();
}

/********************************************************************************
 *
 ********************************************************************************/
function callJobAndEval(url)
{
    _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
    _httpRequest.open("POST", url, true);
    //_httpRequest.setRequestHeader("Content-Type", "text/xml")
    _httpRequest.onreadystatechange = evalReturn;
    _httpRequest.send();
}


/********************************************************************************
 *
 ********************************************************************************/
function callJobAndEval_debug(url)
{
    _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
    _httpRequest.open("POST", url, false);
    _httpRequest.onreadystatechange = evalReturn_debug;

    //_httpRequest.setRequestHeader("Content-Type", "text/xml")
    _httpRequest.send();
    //_httpRequest.send("<data>test</data>");
}


/********************************************************************************
 *
 ********************************************************************************/
function evalReturn()
{
    if ( _httpRequest.readyState == 4)
    {
        if( _httpRequest.status == 200)
        {
            try
            {
                var js = _httpRequest.responseText;
                js = js.substring( js.indexOf( '<responseJS>' ) + 12, js.indexOf( '</responseJS>' ) );
                eval(js);

            }
            catch (e)
            {
                alert("ERROR : " + e.description + " ");
            }
        }
        else
        {
            prompt( 'got response error - ', _httpRequest.responseText );
        }
    }
}


/********************************************************************************
 *
 ********************************************************************************/
function evalReturn_debug()
{
    if ( _httpRequest.readyState == 4)
    {
        if( _httpRequest.status == 200)
        {
            try
            {
                var js = _httpRequest.responseText;
                js = js.substring( js.indexOf( '<responseJS>' ) + 12, js.indexOf( '</responseJS>' ) );
                eval(js);
            }
            catch (e)
            {
                alert("ERROR : " + e.description + " ");
            }
        }
        else
        {
            prompt( 'got response error - ', _httpRequest.responseText );
        }
    }
}


/**
  * function to transform ifast date to behaviour ctrls date format
  * Y2K problem.
  */
function ifastToBehaviourDate(fastdate) {
        if (fastdate.length < 8) return "";
        var behaviourDate = fastdate.substring(3,5)  + "/" +
        fastdate.substring(0,2)+ "/20" + fastdate.substring(6,8);
        return behaviourDate;
}
function ctrlDateToFastDate(ctrldate) {
        if (ctrldate.length < 10) return "";
        var fastDate = ctrldate.substring(3,5)  + "/" +
        ctrldate.substring(0,2)+ "/" + ctrldate.substring(8,10);
        return fastDate;
}

//******************************************************************************
function searching()
{
 goto("/DisplaySearch");
}
//******************************************************************************
function accountSummary() {

    goto("/LoadAccountListSummary");

}
//******************************************************************************
function transactionHistory() {
    goto("/transactionHistoryList");
}
//******************************************************************************

function banking() {
    goto("/Banks");
}

//******************************************************************************
function trading()
{
    goto('/LoadTrading');
}

//******************************************************************************
function fnAWDLogon()
{
  myform.scr.value='AWDLogon';
  myform.target="_top";
  myform.submit();
}

//******************************************************************************
function fnAWDGetWork()
{
  myform.scr.value='AWDGetWork';
  myform.target="_top";
  myform.submit();
}

//******************************************************************************
function fnAWDLookup()
{
  alert( 'not implemented' );
  myform.scr.value='AWDLookup';
  myform.target="_top";
  myform.submit();
}

//******************************************************************************
function fnAWDLogoff()
{
  myform.scr.value='AWDLogoff';
  myform.target="_top";
  myform.submit();
}

//******************************************************************************
// handle Y/N style checkboxes...
function validateYNCheckBox( blChecked, hiddenYN )
{
  // if any of them are ticked, then set the value to "Y"
  if ( blChecked )
  {
     hiddenYN.value = "Y";
  }
  else
  {
    hiddenYN.value = "N";
  }

  return true;
}

//******************************************************************************
// prepends iTargetLength - iLength zero characters onto the value.
function zeroPadNumeric( textInputControl, iTargetLength )
{
  iLength = textInputControl.value.length;

  for ( iPrepend = iLength; iPrepend < iTargetLength; iPrepend++ )
  {
    textInputControl.value = "0" + textInputControl.value;
  }

  return true;
}

//******************************************************************************
// prepends iTargetLength - iLength zero characters onto the value.
function zeroPadNumericIfNotBlank( textInputControl, iTargetLength )
{
  iLength = textInputControl.value.length;

  if ( iLength > 0 )
  {
    for ( iPrepend = iLength; iPrepend < iTargetLength; iPrepend++ )
    {
      textInputControl.value = "0" + textInputControl.value;
    }
  }

  return true;
}

//******************************************************************************
// prepends iTargetLength - iLength zero characters onto the value.
function ensureAllNumeric( textInputControl )
{
  var digits = "0123456789";
  var result = "";

  iLength = textInputControl.value.length;

  for ( iPos = 0; iPos < iLength; iPos++ )
  {
    if ( digits.indexOf( parseInt( textInputControl.value.charAt( iPos ) + "" ) ) != -1 )
    {
      result += textInputControl.value.charAt( iPos );
    }
  }

  textInputControl.value = result;

  return true;
}

//******************************************************************************
function ensureNumericKey()
{
    var evt = window.event;
    // '0' = 48 ... '9' = 57
    if(lessThan(evt.keyCode, 48) || greaterThan(evt.keyCode, 57))
    {
        evt.returnValue = false;
    }
}

//******************************************************************************
// prepends iTargetLength - iLength zero characters onto the value.
function ensureNumber( textInputControl )
{
  var digits = "0123456789";
  var result = "";
  var oneDot = false;
  iLength = textInputControl.value.length;

  for ( iPos = 0; iPos < iLength; iPos++ )
  {
     // an insane way of checking if a digit is "." but just adding it to digits doesn't work.
    if ( (digits.indexOf( parseInt( textInputControl.value.charAt( iPos ) + "" ) ) != -1 ) || (!oneDot && textInputControl.value.charAt( iPos )+""=="."))
    {
      if (textInputControl.value.charAt( iPos )+""==".") { oneDot = true;}
      result += textInputControl.value.charAt( iPos );
    }
  }

  textInputControl.value = result;

  return true;
}

//******************************************************************************
// print this page...
function printPage( )
{
  // add anything else here that needs to be done...

  // print the page
  window.print();
}

/************** set global vars for which browser we're using ************/
var _isOpera = navigator.userAgent.indexOf("Opera") > -1;
var _isIE = navigator.userAgent.indexOf("MSIE") > 1  && !_isOpera;
var _isMoz = navigator.userAgent.indexOf("Mozilla") == 0 && !_isOpera;

function textboxSelect (oTextbox, iStart, iEnd) {
        if (_isIE) {
               var oRange = oTextbox.createTextRange();
               oRange.moveStart("character", iStart);
               oRange.moveEnd("character", -oTextbox.value.length + iEnd);
               oRange.select();
           } else if (_isMoz) {
               oTextbox.setSelectionRange(iStart, iEnd);
           }
}



//******************************************************************************
 function rnd() {
    var rndm = Math.random() + "";
    return "%26r="+rndm.substring(2,7);
}

//******************************************************************************
 function greaterThan (a,b) {
    return (a>b);
}

//******************************************************************************
 function greaterThanOrEqual (a,b) {
    return (a>=b);
}

//******************************************************************************
 function lessThan (a,b) {
    return (a<b);
}

//******************************************************************************
 function lessThanOrEqual (a,b) {
    return (a<=b);
}

//******************************************************************************
function limitTextArea( textArea, maxLines, maxCols )
{
  //textArea.value = trimString( textArea.value );

  split( textArea.value, '\r\n' );

  if ( splitArray[ splitArray.length - 1 ].length > maxCols )
  {
//     alert('Maximum amount of cols reached')
     textArea.value = textArea.value.substring( 0, textArea.value.length - 1 );
  }
  else if ( splitIndex > maxLines )
  {
//    alert('Maximum amount of lines reached')
    textArea.value = textArea.value.substring( 0, textArea.value.length - 2 );
    //alert( textArea.value );
    return false;
  }

  return true;
}

//******************************************************************************
function split( string, text )
{
  splitArray = string.split( text );
  splitIndex = splitArray.length;
}

//******************************************************************************
function trimString (str)
{
  str = this != window? this : str;
  return str.replace(/^\s+/g, '').replace(/\s+$/g, '');
}

//******************************************************************************
function cnvNewlinesToCommas( text )
{
  var temp = text.replace( "\r\n", ", " );
  temp = trimString( temp );
  return( temp );
}

//******************************************************************************
// Fetch a value from a grid via it's coordinates
function getGridItemValue( grid, rowIndex, colIndex )
{
  var result = "";

  var xmlNode = grid.getItem( rowIndex ).childNodes[colIndex].firstChild;

  if ( xmlNode != null )
  {
    result = xmlNode.nodeValue;
  }

  //alert( rowIndex + ":" + colIndex + "=" + result );

  return result;
}

//******************************************************************************
// helper function to add a form value into a DOM, intended for use with
// the grid.
function addToDom( document, row, tag, value )
{
  var column = document.createElement( tag );
  column.text = value
  row.appendChild( column );
}

//******************************************************************************
function parseRowXML( xmlDocument, listNodeName, childNodename )
{
  var xmlStringResult = xmlDocument.xml;

  xmlStringResult = xmlStringResult.replace( /rows/g, listNodeName );
  xmlStringResult = xmlStringResult.replace( /row/g, childNodename );

  return( xmlStringResult );
}

//******************************************************************************
function createTag( tag, value )
{
  return( '<' + tag + '>' +  value +  '</' + tag + '>' );
}

//******************************************************************************
function appendToURL(url, toAppend)
{
  return url + "&" + toAppend;
}

//******************************************************************************
function IEKeyCap()
{
  // if somebody hits CTRL + S display the system smartview inventory...
  if (  window.event.ctrlKey && window.event.keyCode == 83 /* S key */ )
  {
    goto( '/systemInventory.go' );
  }
}

document.onkeyup = function keyPress(evt) { IEKeyCap(); };

//******************************************************************************
//var arrayOfErrorImages =  "fundClassImg,fundImg,baycomImg,wkinImg,isinImg,tradeDateImg,settlementDateImg,depositDateImg,accountNumberImg,attributeValueImg";
//var arrayOfAttributeErrorImages = "exchangeRateImg,acquisitionFeeOptionImg,discountImg,fundBrokerImg,aggregateOptionImg,dealTimeImg,"+
                                       //   "depositIdImg,sourceOfFundImg,sourceOfAccountImg,otherConfirmTypeImg" +
                                        //   ",dealDateImg,cashDateImg";


 function resetAllErrorMessages()
     {
      document.getElementById("generalErrorInnerDiv").innerHTML = "";
      document.getElementById("generalErrorDiv").style.display = "none";

      var arr=  arrayOfErrorImages.split(",");
       for (var i = 0; i < arr.length;i++)
       {
         try {
              resetErrorImg(document.getElementById(arr[i])) ;

          } catch (e)
          { alert(e + " image " + arr[i]);
          }
      }
     }

/******************************************************************************
* showLoadingDisplay and hideLoadingDisplay control the "Loading..." dialog
* Params for showLoadingDisplay:
* @ div -> the div that the loading text should be placed in (this should be an empty positioned div)
* @ (can be left blank)message -> the text that should be displayed, ie "Loading" or "Please Wait"
* @ (can be left blank)inc -> the beginning increment, ie "." or ".."
* the increment is more of an internal variable so it can and probably should be left as ""
*
* hideLoadingDisplay just disables the current one
*/

var timeout = null;
var text = "";
var currentLoadingDivId = "";
var message = "Loading";
function showLoadingDisplay(div, msg, inc)
{

    if ((currentLoadingDivId != div && currentLoadingDivId != "") || timeout != null)
     hideLoadingDisplay(currentLoadingDivId);
    if (msg != undefined)
    {
     message = msg;
    }
    if (inc != undefined)
     text = inc;

    try
    {
        currentLoadingDivId = div;
        var loadingDiv = document.getElementById(currentLoadingDivId);
        loadingDiv.style.display = "inline";
    }
    catch (e)
    {
        alert(e + "\nInvalid div for \"Loading...\" message.");
    }

    if (text == ".....")
        text = "";
    else
        text = text + ".";

    loadingDiv.innerHTML = message + text;
    timeout = setTimeout("showLoadingDisplay(currentLoadingDivId, message, text)", 500)

}

function hideLoadingDisplay()
{
    //alert("Stopping: " + currentLoadingDivId)
     text = "";
     message = "Loading";
     clearTimeout(timeout);
     timeout = null;
     if (currentLoadingDivId != null && currentLoadingDivId != "")
     {
        document.getElementById(currentLoadingDivId).innerHTML = "";
        document.getElementById(currentLoadingDivId).style.display = "none";
     }
}

//******************************************************************************



/*****************************************************************
 * desktop update code - confirmation dialog
 *****************************************************************/
var _updateStatus = false;

function getUpdateStatus()
{
  return _updateStatus;
}

function setUpdateStatus()
{
  _updateStatus = true;

  // fire up the confirmation dialog event in the C++ code
  var btnConfirmDlgObj = document.getElementById( "btnConfirmDlg" );

  if ( btnConfirmDlgObj != null &&
       btnConfirmDlgObj != undefined )
  {
    btnConfirmDlgObj.click();
  }
//PMI  else
//PMI  {
//PMI    alert( "Can't find btnConfirmDlgObj" );
//PMI  }


}
