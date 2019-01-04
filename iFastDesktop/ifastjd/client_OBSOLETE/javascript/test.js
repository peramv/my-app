var _inputBox = null;
function callFundSuggest(inputBox)
{	
	_inputBox = inputBox;	
	var url = "http://ifds1953:8080/desktop/desktop?cz=6021108041319&jobname=desktop_FundSuggest&searchData="+inputBox.value;
	_httpRequest = new ActiveXObject("MSXML2.XMLHTTP");                               
	_httpRequest.open("POST", url, false);
	_httpRequest.onreadystatechange = evalReturn;
	
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
             	var type = js.substring(js.indexOf( '|' ));
             	//alert(type)
             	//alert(type == "javascript")
             	       			
				
				var fundSuggestResults = document.getElementById("fundSuggestResults");
				fundSuggestResults.innerHTML = js;
				fundSuggestResults.style.top = parseInt(_inputBox.style.top) + 30;
				fundSuggestResults.style.left = _inputBox.style.left;
				fundSuggestResults.style.display = "block";
				//alert(js)*/
																 	
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

function populateField(selectedFund)
{
	_inputBox.value = selectedFund;
	document.getElementById("fundSuggestResults").style.display = "none";
	_inputBox.focus();
}