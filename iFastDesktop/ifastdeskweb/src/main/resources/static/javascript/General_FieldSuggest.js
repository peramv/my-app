
/******************************************************************
 *  BROKER SUGGEST
 ******************************************************************/
function BrokerSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId)
{
    var _self = this;

    var _brokerName = null;
    var _branchName = null;
    var _salesRepName = null;
    var _allowBrUpd = null;

    var _brokerSuggestFld = null;
    var _branchFld = null;
    var _salesRepFld = null;

    var _searchTimer = null;
    var _httpRequest = null;

    var _url = null;

    var _suggestDropdown = null;

    var _nextStartRecNum = null;
    
    var _searchScheduled = false;
    var _searchRunning = false;
        


    this.init = function(fld, branch, rep)
    {
        _brokerSuggestFld = fld;
        _branchFld = branch;
        _salesRepFld = rep;

        _brokerSuggestFld.onkeydown = handleOnKeydown;
        _brokerSuggestFld.onkeyup = handleOnKeyup;
        _brokerSuggestFld.onblur = handleOnBlur;


        _suggestDropdown = new SuggestDropdown(_self, _brokerSuggestFld);


        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
            + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_BrokerSuggest";
    }



    this.init2 = function(fld, branch, rep, brokerName, branchName, salesRepName, allowBrUpd)
    {
        _branchName = branchName;
        _salesRepName = salesRepName;
        _brokerName = brokerName;
        _brokerSuggestFld = fld;
        _branchFld = branch;
        _salesRepFld = rep;
        _allowBrUpd = allowBrUpd;

        _brokerSuggestFld.onkeydown = handleOnKeydown;
        _brokerSuggestFld.onkeyup = handleOnKeyup;
        _brokerSuggestFld.onblur = handleOnBlur;
        
        _suggestDropdown = new SuggestDropdown(_self, _brokerSuggestFld);
        
        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
            + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_BrokerSuggest";
    }



    function clearBranchAndSalesRep()
    {
         _branchFld.value = "";
         if( _branchName != null) _branchName.innerHTML = "";
         _branchFld.disabled = true;

         _salesRepFld.value = "";
         if( _salesRepName != null) _salesRepName.innerHTML = "";
         _salesRepFld.disabled = true;
    }

    
    
    function clearBrokerName()
    {
    	if ( _brokerName )
    	{
    		_brokerName.innerHTML = "";
    	}
    }

    
    
    function handleOnBlur()
    {
		_suggestDropdown.disable();
		if ( _brokerSuggestFld.code == "" )
		{
			_brokerSuggestFld.value = "";
		}		
    }
    
    
    
    function handleOnKeydown()
    {
        var keyCode = event.keyCode;

        if( isTab( keyCode ) )
        {
        	if ( _suggestDropdown.isEnabled() )
        	{
        		if ( _searchRunning )
        		{
        			return false;
        		}
        		else
        		{
					_suggestDropdown.selectRow();
					return true;
        		}        		
        	}
        	else
        	{
        		if ( _searchScheduled )
        		{
        			cancelScheduledSearch();
        			// do search immediately
        			_self.doSearch( _brokerSuggestFld.value );
        			return false;
        		}
        		else
        		{
        			return true;
        		}
        	}
        }
    }


    
    function cancelScheduledSearch()
    {
    	_searchScheduled = false;
    	clearTimeout( _searchTimer );
    	_brokerSuggestFld.releaseCapture();
    }
    

    
    function scheduleSearch( searchString )
    {
    	cancelScheduledSearch();
    	
    	_brokerSuggestFld.setCapture();
    	_searchScheduled = true;    	
        _searchTimer = setTimeout(function(){_self.doSearch(searchString)}, 1000);
    }

    

    function handleOnKeyup()
    {
        var keyCode = event.keyCode;
        var searchString = _brokerSuggestFld.value;

        if(isChar(keyCode) || isNum(keyCode))
        {
            _brokerSuggestFld.code = "";
            clearBrokerName();
            clearBranchAndSalesRep();
            
            _suggestDropdown.disable();

            // no empty strings
            if(searchString.length > 0)
            {
                scheduleSearch( searchString );
            }
        }
        else if(isBackspace(keyCode) || isDelete(keyCode))
        {
            _brokerSuggestFld.code = "";
            clearBrokerName();
            clearBranchAndSalesRep();
            
            _suggestDropdown.disable();
                                    
            if(searchString.length == 0)
            {
            	cancelScheduledSearch();
                _suggestDropdown.disable();
            }
            else
            {
                scheduleSearch( searchString );
            }
        }
        else if(isUpArrow(keyCode))
        {
            _suggestDropdown.highlightPrevRow();
        }
        else if(isDownArrow(keyCode))
        {
            _suggestDropdown.highlightNextRow();
        }
        else if(isEnter(keyCode))
        {
        	if ( _suggestDropdown.isEnabled() && !_searchRunning )
        	{
        		_suggestDropdown.selectRow();
        	}
        	else if ( _brokerSuggestFld.code == "" && _brokerSuggestFld.value != "" )
        	{
        		cancelScheduledSearch();
        		// call search immediately                
                _self.doSearch(searchString);
        	}            
        }

        return true;
    }



    this.setValue = function(selection)
    {
    	
        if( _brokerName!= null )
        {
            _brokerSuggestFld.value = selection.code;
            _brokerSuggestFld.code = selection.code;
            clearBrokerName();
            _brokerName.innerHTML = selection.displayVal;
        }
        else
        {
            _brokerSuggestFld.value = selection.displayVal;
            _brokerSuggestFld.code = selection.code;
        }

         if( _allowBrUpd == "no")
         {
            _salesRepFld.disabled = false;
            _branchFld.disabled = true;
         }
         else
         {
            _branchFld.disabled = false;
         }
    }



    this.doSearch = function(searchString, moreFlag)
    {    	
    	_searchScheduled = false;
    	_searchRunning = true;
    	_suggestDropdown.clearTable();
        _suggestDropdown.setError( "retrieving/verifying data ... ");
        _suggestDropdown.enable();
    
        _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");
        
        if(moreFlag)
        {
            if(_nextStartRecNum != null)
            {
                _httpRequest.open("POST", _url + "&searchData=" + searchString + "&startRecordNum=" + _nextStartRecNum, true);
            }
            else
            {
                alert("error: nextStartRecNum is null");
            }
        }
        else
        {
            _httpRequest.open("POST", _url + "&searchData=" + searchString, true);
        }
        _httpRequest.onreadystatechange = function(){handleSearchResponse(searchString)};
        
        _httpRequest.send();
    }
    

       
    function handleSearchResponse( searchString )
    {    	    	
    	if( searchString == _brokerSuggestFld.value)
    	{
	        if (_httpRequest.readyState == 4)
	        {
	            if (_httpRequest.status == 200)
	            {
	            	_searchRunning = false;	            	
	            	_brokerSuggestFld.releaseCapture();	            	
	            
	                // _httpRequest.responseText is of the form "<responseContents>...</responseContents>"
	                var responseXMLDoc = XML_Lib.createXMLDoc();
	                XML_Lib.loadFromString(responseXMLDoc, _httpRequest.responseText);
	
	                var xmlRoot = responseXMLDoc.documentElement;
	
	
	                var numRecordsNode = xmlRoot.selectSingleNode("./numRecords");//.firstChild.nodeValue;
	
	                if(numRecordsNode == null)
	                {
	                    alert("Error: no response for Broker Search");
	                }
	                else
	                {
	                    var numRecords = numRecordsNode.firstChild.nodeValue;
	
	                    if(numRecords == 0)
	                    {
	                        _suggestDropdown.clearTable();
	                        _suggestDropdown.setError(xmlRoot.selectSingleNode("./error").firstChild.nodeValue);
	                        _suggestDropdown.enable();
	                    }
	                    else if(numRecords == 1)
	                    {
	                        _suggestDropdown.clearTable();
	                        var selection = new Object();
	                        selection.displayVal = xmlRoot.selectSingleNode("./PossibleMatches/PossibleMatch/displayValue").firstChild.nodeValue;
	                        selection.code = xmlRoot.selectSingleNode("./PossibleMatches/PossibleMatch/agencyCode").firstChild.nodeValue;
	                        _self.setValue(selection);
	                    }
	                    else
	                    {
	                        _suggestDropdown.clearTable();
	
	                        var nextStartRecNumNode = xmlRoot.selectSingleNode("./nextStartRecNum");
	                        if(nextStartRecNumNode != null)
	                        {
	                            _suggestDropdown.setMore(xmlRoot.selectSingleNode("./moreText").firstChild.nodeValue);
	                            _nextStartRecNum = nextStartRecNumNode.firstChild.nodeValue;
	                        }
	                        else
	                        {
	                            _nextStartRecNum = null;
	                        }
	
	                        var possibleMatchesNodes = xmlRoot.selectNodes("./PossibleMatches/PossibleMatch");
	                        var resultsArray = new Array();
	                        for(var i = 0; i < possibleMatchesNodes.length; i++)
	                        {
	                            resultsArray[i] = new Object();
	                            resultsArray[i].displayVal = possibleMatchesNodes[i].selectSingleNode("./displayValue").firstChild.nodeValue;
	                            resultsArray[i].code = possibleMatchesNodes[i].selectSingleNode("./agencyCode").firstChild.nodeValue;
	                        }
	
	                        _suggestDropdown.populateResultTable(resultsArray);
	                        _suggestDropdown.highlightFirstRow();
	                        _suggestDropdown.enable();
	                    }
	                }
	
	            }
	            else
	            {
	                alert("HTTP error: " + _httpRequest.status);
	            }
	        }
		}	      
    }
}



/******************************************************************
 *  BRANCH SUGGEST
 ******************************************************************/
function BranchSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId)
{
    var _self = this;

    var _branchName = null;
    var _salesRepName = null;

    var _branchSuggestFld = null;
    var _brokerFld = null;
    var _salesRepFld = null;

    var _searchTimer = null;
    var _httpRequest = null;

    var _url = null;

    var _suggestDropdown = null;

    var _nextStartRecNum = null;
    
    var _searchScheduled = false;
    var _searchRunning = false;
    
    

    this.init = function(brokerFld, branchFld, repFld)
    {
        _branchSuggestFld = branchFld;
        _brokerFld = brokerFld;
        _salesRepFld = repFld;
        
        _branchSuggestFld.onkeydown = handleOnKeydown;
        _branchSuggestFld.onkeyup = handleOnKeyup;
        _branchSuggestFld.onblur = handleOnBlur;

        _suggestDropdown = new SuggestDropdown(_self, _branchSuggestFld);

        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
            + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_BranchSuggest";
    }



    this.init2 = function(brokerFld, branchFld, repFld, branchName, salesRepName)
    {
        _salesRepName = salesRepName;
        _branchName = branchName;
        _branchSuggestFld = branchFld;
        
        _branchSuggestFld.onkeydown = handleOnKeydown;
        _branchSuggestFld.onkeyup = handleOnKeyup;
        _branchSuggestFld.onblur = handleOnBlur;

        _brokerFld = brokerFld;
        _salesRepFld = repFld;

        _suggestDropdown = new SuggestDropdown(_self, _branchSuggestFld);

        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
            + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_BranchSuggest";
    }

    

    function clearSalesRep()
    {
        _salesRepFld.value = "";
        if( _salesRepName != null ) _salesRepName.innerHTML = "";
        _salesRepFld.disabled = true;
    }
    
    
    
    function clearBranchName()
    {
    	if ( _branchName )
    	{
    		_branchName.innerHTML = "";
    	}
    }



	function handleOnBlur()
    {
		_suggestDropdown.disable();
		if ( _branchSuggestFld.code == "" )
		{
			_branchSuggestFld.value = "";
		}		
    }
//    function handleOnBlur()
//    {
//        if(_suggestDropdown != null)
//        {
//            clearTimeout(_searchTimer);
//            _suggestDropdown.disable();
//        }
//
//        if(_branchSuggestFld.code == "")
//        {
//            _branchSuggestFld.value = "";
//        }
//    }



	function handleOnKeydown()
    {
        var keyCode = event.keyCode;

        if( isTab( keyCode ) )
        {
        	if ( _suggestDropdown.isEnabled() )
        	{
        		if ( _searchRunning )
        		{
        			return false;
        		}
        		else
        		{
					_suggestDropdown.selectRow();
					return true;
        		}        		
        	}
        	else
        	{
        		if ( _searchScheduled )
        		{
        			cancelScheduledSearch();
        			// do search immediately
        			_self.doSearch( _branchSuggestFld.value );
        			return false;
        		}
        		else
        		{
        			return true;
        		}
        	}
        }
    }


    
    function cancelScheduledSearch()
    {
    	_searchScheduled = false;
    	clearTimeout( _searchTimer );
    	_branchSuggestFld.releaseCapture();
    }
    

    
    function scheduleSearch( searchString )
    {
    	cancelScheduledSearch();
    	
    	_branchSuggestFld.setCapture();
    	_searchScheduled = true;    	
        _searchTimer = setTimeout(function(){_self.doSearch(searchString)}, 1000);
    }
//    function handleOnKeydown()
//    {
//        var keyCode = event.keyCode;
//
//        if(isTab(keyCode))
//        {
//             if(_suggestDropdown.isEnabled())
//            {
//                _suggestDropdown.selectRow();
//                handleOnKeydown();
//                return false;
//            }
//        }
//        return true;
//    }



    function handleOnKeyup()
    {
        var keyCode = event.keyCode;
        var searchString = _branchSuggestFld.value;

        if(isChar(keyCode) || isNum(keyCode))
        {
            _branchSuggestFld.code = "";
            clearSalesRep();
            clearBranchName();
            
			_suggestDropdown.disable();

            // no empty strings
            if(searchString.length > 0)
            {
				scheduleSearch( searchString );
            }
        }
        else if(isBackspace(keyCode) || isDelete(keyCode))
        {        	
            _branchSuggestFld.code = "";
            clearSalesRep();
            clearBranchName();
            
            _suggestDropdown.disable();

            if(searchString.length == 0)
            {            	
				cancelScheduledSearch();
                _suggestDropdown.disable();             
            }
            else
            {
				scheduleSearch( searchString );
            }
        }
        else if(isUpArrow(keyCode))
        {
            _suggestDropdown.highlightPrevRow();
        }
        else if(isDownArrow(keyCode))
        {
            _suggestDropdown.highlightNextRow();

        }
        else if(isEnter(keyCode))
        {
        	if ( _suggestDropdown.isEnabled() )
        	{
        		_suggestDropdown.selectRow();
        	}
        	else if ( _branchSuggestFld.code == "" && _branchSuggestFld.value != "" )
        	{
        		cancelScheduledSearch();
        		// call search immediately                
                _self.doSearch(searchString);
        	}            
        }

        return true;
    }



    this.setValue = function(selection)
    {
        if(_branchName != null )
        {
            _branchSuggestFld.value = selection.code;
            _branchSuggestFld.code = selection.code;
            _branchName.innerHTML = "";
            _branchName.innerHTML = selection.displayVal;
        }
        else
        {
            _branchSuggestFld.value = selection.displayVal;
            _branchSuggestFld.code = selection.code;
        }

        _salesRepFld.disabled = false;
    }



    this.doSearch = function(searchString, moreFlag)
    {
		_searchScheduled = false;
    	_searchRunning = true;
    	_suggestDropdown.clearTable();
        _suggestDropdown.setError( "retrieving/verifying data ... ");
        _suggestDropdown.enable();
		
        _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");

        var urlWithParam = _url + "&agencyCode=" + _brokerFld.code + "&searchData=" + searchString;

        if(moreFlag)
        {
            if(_nextStartRecNum != null)
            {
                _httpRequest.open("POST", urlWithParam + "&searchData=" + searchString + "&startRecordNum=" + _nextStartRecNum, true);
            }
            else
            {
                alert("error: nextStartRecNum is null");
            }
        }
        else
        {
            _httpRequest.open("POST", urlWithParam + "&searchData=" + searchString, true);
        }
        _httpRequest.onreadystatechange = function(){ handleSearchResponse( searchString ) };

        _httpRequest.send();
    }


    
    function handleSearchResponse( searchString )
    {
    	if( searchString == _branchSuggestFld.value)
    	{
	        if (_httpRequest.readyState == 4)
	        {
	            if (_httpRequest.status == 200)
	            {
	            	_searchRunning = false;	            	
		            _branchSuggestFld.releaseCapture();	   
	            
	                // _httpRequest.responseText is of the form "<responseContents>...</responseContents>"
	                var responseXMLDoc = XML_Lib.createXMLDoc();
	                XML_Lib.loadFromString(responseXMLDoc, _httpRequest.responseText);
	
	                var xmlRoot = responseXMLDoc.documentElement;
	
	                var numRecordsNode = xmlRoot.selectSingleNode("./numRecords");
	
	                if(numRecordsNode == null)
	                {
	                    alert("Error: No response for Branch Suggest");
	                }
	                else
	                {
	                    var numRecords = numRecordsNode.firstChild.nodeValue;
	
	                    if(numRecords == 0)
	                    {
	                        _suggestDropdown.clearTable();
	                        _suggestDropdown.setError(xmlRoot.selectSingleNode("./error").firstChild.nodeValue);
	                        _suggestDropdown.enable();
	                    }
	                    else if(numRecords == 1)
	                    {
	                        _suggestDropdown.clearTable();
	                        var selection = new Object();
	                        selection.displayVal = xmlRoot.selectSingleNode("./PossibleMatches/PossibleMatch/displayValue").firstChild.nodeValue;
	                        selection.code = xmlRoot.selectSingleNode("./PossibleMatches/PossibleMatch/branch").firstChild.nodeValue
	                        _self.setValue(selection);
	                    }
	                    else
	                    {
	                        _suggestDropdown.clearTable();
	
	                        var nextStartRecNumNode = xmlRoot.selectSingleNode("./nextStartRecNum");
	                        if(nextStartRecNumNode != null)
	                        {
	                            _suggestDropdown.setMore(xmlRoot.selectSingleNode("./moreText").firstChild.nodeValue);
	                            _nextStartRecNum = nextStartRecNumNode.firstChild.nodeValue;
	                        }
	                        else
	                        {
	                            _nextStartRecNum = null;
	                        }
	
	                        var possibleMatchesNodes = xmlRoot.selectNodes("./PossibleMatches/PossibleMatch");
	                        var resultsArray = new Array();
	                        for(var i = 0; i < possibleMatchesNodes.length; i++)
	                        {
	                            resultsArray[i] = new Object();
	                            resultsArray[i].displayVal = possibleMatchesNodes[i].selectSingleNode("./displayValue").firstChild.nodeValue;
	                            resultsArray[i].code = possibleMatchesNodes[i].selectSingleNode("./branch").firstChild.nodeValue;
	                        }
	
	                        _suggestDropdown.populateResultTable(resultsArray);
	                        _suggestDropdown.highlightFirstRow();
	                        _suggestDropdown.enable();
	                    }
	                }
	            }
	            else
	            {
	                alert("HTTP error: " + _httpRequest.status);
	            }
	        }
	    }
	}
}


/******************************************************************
 *  SALESREP SUGGEST
 ******************************************************************/
function SalesRepSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId)
{
    var _self = this;

    var _createSaleRep = null;
    var _salesRepName = null;
    var _branchNameFld = null;

    var _salesRepSuggestFld = null;
    var _brokerFld = null;
    var _branchFld = null;

    var _searchTimer = null;
    var _httpRequest = null;

    var _url = null;

    var _suggestDropdown = null;

    var _nextStartRecNum = null;
    
    var _searchScheduled = false;
    var _searchRunning = false;



    this.init = function(brokerFld, branchFld, salesrepFld)
    {
        _salesRepSuggestFld = salesrepFld;
        
        _salesRepSuggestFld.onkeydown = handleOnKeydown;
        _salesRepSuggestFld.onkeyup = handleOnKeyup;
        _salesRepSuggestFld.onblur = handleOnBlur;

        _brokerFld = brokerFld;
        _branchFld = branchFld

        _suggestDropdown = new SuggestDropdown(_self, _salesRepSuggestFld);

        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
            + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_SalesRepSuggest";
    }



    this.init2 = function(brokerFld, branchFld, salesrepFld, salesRepName, createSalesRep, branchNameFld)
    {
        _createSaleRep = createSalesRep;
        _salesRepName = salesRepName;
        _branchNameFld = branchNameFld;
        _salesRepSuggestFld = salesrepFld;
        
        _salesRepSuggestFld.onkeydown = handleOnKeydown;
        _salesRepSuggestFld.onkeyup = handleOnKeyup;
        _salesRepSuggestFld.onblur = handleOnBlur;

        _brokerFld = brokerFld;
        _branchFld = branchFld

        if(_suggestDropdown == null)
        {
            _suggestDropdown = new SuggestDropdown(_self, _salesRepSuggestFld);
        }

        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
            + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_SalesRepSuggest";
    }



    function clearSalesRepName()
    {
    	if ( _salesRepName )
    	{
    		_salesRepName.innerHTML = "";
    	}
    }
    


    function handleOnBlur()
    {
        _suggestDropdown.disable();               
		if ( _salesRepSuggestFld.code == "" )
		{
			_salesRepSuggestFld.value = "";
		}		
    }



    function handleOnKeydown()
    {
        var keyCode = event.keyCode;

        if( isTab( keyCode ) )
        {
        	if ( _suggestDropdown.isEnabled() )
        	{
        		if ( _searchRunning )
        		{
        			return false;
        		}
        		else
        		{
					_suggestDropdown.selectRow();
					return true;
        		}        		
        	}
        	else
        	{
        		if ( _searchScheduled )
        		{
        			cancelScheduledSearch();
        			// do search immediately
        			_self.doSearch( _salesRepSuggestFld.value );
        			return false;
        		}
        		else
        		{
        			return true;
        		}
        	}
        }
    }
    
    
    
    function cancelScheduledSearch()
    {
    	_searchScheduled = false;
    	clearTimeout( _searchTimer );
    	_salesRepSuggestFld.releaseCapture();
    }
    

    
    function scheduleSearch( searchString )
    {
    	cancelScheduledSearch();
    	
    	_salesRepSuggestFld.setCapture();
    	_searchScheduled = true;    	
        _searchTimer = setTimeout(function(){_self.doSearch(searchString)}, 1000);
    }



    function handleOnKeyup()
    {
        var keyCode = event.keyCode;
        var searchString = _salesRepSuggestFld.value;

        if(isChar(keyCode) || isNum(keyCode))
        {
        	clearSalesRepName();
                    
            _salesRepSuggestFld.code = "";                        
                
            _suggestDropdown.disable();

            // no empty strings
            if(searchString.length > 0)
            {
                scheduleSearch( searchString );
            }
        }
        else if(isBackspace(keyCode) || isDelete(keyCode))
        {
        	clearSalesRepName();
                   
            _salesRepSuggestFld.code = "";                           
                
			_suggestDropdown.disable();                
            
            if(searchString.length == 0)
            {
            	cancelScheduledSearch();
                _suggestDropdown.disable();
            }
            else
            {
                scheduleSearch( searchString );
            }
        }
        else if(isUpArrow(keyCode))
        {
            _suggestDropdown.highlightPrevRow();
        }
        else if(isDownArrow(keyCode))
        {
            _suggestDropdown.highlightNextRow();
        }
        else if(isEnter(keyCode))
        {            	    
            if ( _suggestDropdown.isEnabled() && !_searchRunning )
        	{
        		_suggestDropdown.selectRow();
        	}
        	else if ( _searchScheduled )
        	{        		
        		cancelScheduledSearch();
        		// call search immediately                
                _self.doSearch( searchString );
        	}         
        }

        return true;
    }


    this.setValue = function(selection)
    {
        if( _salesRepName != null )
        {
            _salesRepSuggestFld.value = selection.code;
            _salesRepSuggestFld.code = selection.code;
            _salesRepName.innerHTML = "";
            _salesRepName.innerHTML = selection.displayVal;
        }
        else
        {
            _salesRepSuggestFld.value = selection.displayVal;
            _salesRepSuggestFld.code = selection.code;
        }

        if(_createSaleRep != null)
        {
            var _GetBranchName = new GetBranchName(servletPath, cz, companyCode, envName, ruserid, sessionId, _brokerFld.code, selection.code, _branchFld, _branchNameFld );
            _GetBranchName.search();
        }
    }

    this.doSearch = function(searchString, moreFlag)
    {
    	_searchScheduled = false;
    	_searchRunning = true;
    	_suggestDropdown.clearTable();
        _suggestDropdown.setError( "retrieving/verifying data ... ");
        _suggestDropdown.enable();
    
        _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");

        var urlWithParam = _url + "&agencyCode=" + _brokerFld.code + "&branch=" + _branchFld.code + "&searchData=" + searchString;

        if(moreFlag)
        {
            if(_nextStartRecNum != null)
            {
                _httpRequest.open("POST", urlWithParam + "&searchData=" + searchString + "&startRecordNum=" + _nextStartRecNum, true);
            }
            else
            {
                alert("error: nextStartRecNum is null");
            }
        }
        else
        {
            _httpRequest.open("POST", urlWithParam + "&searchData=" + searchString, true);
        }
        _httpRequest.onreadystatechange = function(){ handleSearchResponse( searchString ) };

        _httpRequest.send();
    }


   
    function handleSearchResponse( searchString )
    {
    	if ( searchString == _salesRepSuggestFld.value )
    	{
	        if (_httpRequest.readyState == 4)
	        {
	            if (_httpRequest.status == 200)
	            {
	            	_searchRunning = false;
	            	_salesRepSuggestFld.releaseCapture();
	            
	                // _httpRequest.responseText is of the form "<responseContents>...</responseContents>"
	                var responseXMLDoc = XML_Lib.createXMLDoc();
	                XML_Lib.loadFromString(responseXMLDoc, _httpRequest.responseText);
	
	                var xmlRoot = responseXMLDoc.documentElement;
	
	                var numRecordsNode = xmlRoot.selectSingleNode("./numRecords");
	
	                if(numRecordsNode == null)
	                {
	                    alert("Error: no response for SalesRep suggest");
	                }
	                else
	                {
	                    var numRecords = xmlRoot.selectSingleNode("./numRecords").firstChild.nodeValue;
	
	                    if(numRecords == 0)
	                    {
	                        if(_createSaleRep != null)
	                        {
	                        	_salesRepSuggestFld.code = searchString;
	                            var ret = confirm ("do you want create salesrep?");
	                            if(!ret)
	                            {	                            	
	                                _suggestDropdown.clearTable();
	                                _suggestDropdown.setError(xmlRoot.selectSingleNode("./error").firstChild.nodeValue);
	                                _suggestDropdown.enable();
	                                _salesRepSuggestFld.code = "";
	                            }
	                            else
	                            {
	                                _createSaleRep.value = "yes";
	                                if( _salesRepName != null )
	                                {
	                                    _salesRepName.innerHTML = "";
	                                }
	                                
	                                if ( document.getElementById( "fldallowBrUpd" ).value == "no" )
	                                {
		                                var branchBox = document.getElementById( "branchBox" );
		                                branchBox.value = "";
		                                branchBox.code = "";
		                                document.getElementById( "branchName" ).innerHTML = "";    	                                
		                            }
	                            }
	                        }
	                        else
	                        {
	                            _suggestDropdown.clearTable();
	                            _suggestDropdown.setError(xmlRoot.selectSingleNode("./error").firstChild.nodeValue);
	                            _suggestDropdown.enable();
	                        }
	                    }
	                    else if(numRecords == 1)
	                    {
	                        _suggestDropdown.clearTable();
	                        var selection = new Object();
	                        selection.displayVal = xmlRoot.selectSingleNode("./PossibleMatches/PossibleMatch/displayValue").firstChild.nodeValue;
	                        selection.code = xmlRoot.selectSingleNode("./PossibleMatches/PossibleMatch/agentCode").firstChild.nodeValue;
	                        _self.setValue(selection);
	                    }
	                    else
	                    {
	                        _suggestDropdown.clearTable();
	
	                        var nextStartRecNumNode = xmlRoot.selectSingleNode("./nextStartRecNum");
	                        if(nextStartRecNumNode != null)
	                        {
	                            _suggestDropdown.setMore(xmlRoot.selectSingleNode("./moreText").firstChild.nodeValue);
	                            _nextStartRecNum = nextStartRecNumNode.firstChild.nodeValue;
	                        }
	                        else
	                        {
	                            _nextStartRecNum = null;
	                        }
	
	                        var possibleMatchesNodes = xmlRoot.selectNodes("./PossibleMatches/PossibleMatch");
	                        var resultsArray = new Array();
	                        for(var i = 0; i < possibleMatchesNodes.length; i++)
	                        {
	                            resultsArray[i] = new Object();
	                            resultsArray[i].displayVal = possibleMatchesNodes[i].selectSingleNode("./displayValue").firstChild.nodeValue;
	                            resultsArray[i].code = possibleMatchesNodes[i].selectSingleNode("./agentCode").firstChild.nodeValue;
	                        }
	
	                        _suggestDropdown.populateResultTable(resultsArray);
	                        _suggestDropdown.highlightFirstRow();
	                        _suggestDropdown.enable();
	                    }
	                }
	            }
	            else
	            {
	                alert("HTTP error: " + _httpRequest.status);
	            }
	        }
	    }
	}
}



/***************************************************************
 * FUND SUGGEST
 ***************************************************************/
function FundSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId)
{
    var _self = this;

    var _fundSuggestFld = null;

    var _searchTimer = null;
    var _httpRequest = null;

    var _url = null;

    var _suggestDropdown = null;

    var _nextStartRecNum = null;

    var _allFlag = null;


    this.init = function(fld, allPermitted, fundSponsor)
    {
        _allFlag = allPermitted;

        _fundSuggestFld = fld;
        _fundSuggestFld.onkeyup = handleOnKeyup;
        _fundSuggestFld.onkeydown = handleOnKeydown;
        _fundSuggestFld.attachEvent("onblur", handleOnBlur);

        if(_suggestDropdown == null)
        {
            _suggestDropdown = new SuggestDropdown(_self, _fundSuggestFld);
        }

        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
                        + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_FundSuggest"
            + "&fundSponsor=" + fundSponsor;

    }

    function handleOnBlur()
    {
        if(_suggestDropdown != null)
        {
            clearTimeout(_searchTimer);
            _suggestDropdown.disable();
        }

        if(_fundSuggestFld.code == "")
        {
            _fundSuggestFld.value = "";
            _fundSuggestFld.fundClass = "";
        }
    }

    function handleOnKeydown()
    {
        var keyCode = event.keyCode;
        var searchString = _fundSuggestFld.value;

        if(isTab(keyCode))
        {
             if(_suggestDropdown.isEnabled())
            {
                _suggestDropdown.selectRow();
                handleOnKeydown();
                return false;
            }
        }
        else if( !( _allFlag && searchString.toLowerCase() == "all" ) )
        {
        	if(isUpArrow(keyCode))
            {
                _suggestDropdown.highlightPrevRow();
            }
            if(isDownArrow(keyCode))
            {
                _suggestDropdown.highlightNextRow();
            }
        }
        return true;
    }


    function handleOnKeyup()
    {
        var keyCode = event.keyCode;
        var searchString = _fundSuggestFld.value;

        if(_allFlag && searchString.toLowerCase() == "all")
        {
            clearTimeout(_searchTimer);
            _suggestDropdown.disable();
            _fundSuggestFld.code = "ALL";
            _fundSuggestFld.fundClass = "";
        }
        else
        {

            if(isChar(keyCode) || isNum(keyCode))
            {
                _fundSuggestFld.code = "";
                _fundSuggestFld.fundClass = "";

                // no empty strings
                if(searchString.length > 0)
                {
                    clearTimeout(_searchTimer);
                    _searchTimer = setTimeout(function(){_self.doSearch(searchString)}, 1000);
                }
            }
            else if(isBackspace(keyCode) || isDelete(keyCode))
            {
                _fundSuggestFld.code = "";
                _fundSuggestFld.fundClass = "";

                clearTimeout(_searchTimer);
                if(searchString.length == 0)
                {
                    _suggestDropdown.disable();
                }
                else
                {
                    _searchTimer = setTimeout(function(){_self.doSearch(searchString)}, 1000);
                }
            }           
            else if(isEnter(keyCode))
            {
                if(!_suggestDropdown.isEnabled())
                {
                    clearTimeout(_searchTimer);
                    _self.doSearch(searchString);
                }
                else
                {
                    _suggestDropdown.selectRow();
                }
            }
        }
        return true;
    }


    this.setValue = function(selection)
    {
        _fundSuggestFld.value = selection.displayVal;
        _fundSuggestFld.code = selection.code;
        _fundSuggestFld.fundClass = selection.fundClass;
    }

    this.doSearch = function(searchString, moreFlag)
    {
        _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");

        if(moreFlag)
        {
            _httpRequest.open("POST", _url + "&searchData=" + searchString + "&startRecordNum=" + _nextStartRecNum, false);
        }
        else
        {
            _httpRequest.open("POST", _url + "&searchData=" + searchString, false);
        }
        _httpRequest.onreadystatechange = handleSearchResponse;

        _httpRequest.send();
    }


    /**************************************************************************
     *
     **************************************************************************/
    function handleSearchResponse()
    {
        if (_httpRequest.readyState == 4)
        {
            if (_httpRequest.status == 200)
            {
                // _httpRequest.responseText is of the form "<responseContents>...</responseContents>"
                var responseXMLDoc = XML_Lib.createXMLDoc();
                XML_Lib.loadFromString(responseXMLDoc, _httpRequest.responseText);

                var xmlRoot = responseXMLDoc.documentElement;

                var numRecordsNode = xmlRoot.selectSingleNode("./numRecords");//.firstChild.nodeValue;

                if(numRecordsNode == null)
                {
                    alert("Error: no response for Fund Search");
                }
                else
                {
                    var numRecords = numRecordsNode.firstChild.nodeValue;

                    if(numRecords == 0)
                    {
                        _suggestDropdown.clearTable();
                        _suggestDropdown.setError(xmlRoot.selectSingleNode("./error").firstChild.nodeValue);
                        _suggestDropdown.enable();
                    }
                    else if(numRecords == 1)
                    {
                        _suggestDropdown.clearTable();
                        var selectionObj = {};
                        selectionObj.displayVal = xmlRoot.selectSingleNode( "./PossibleMatches/PossibleMatch/displayValue" ).firstChild.nodeValue;
                        selectionObj.code = xmlRoot.selectSingleNode( "./PossibleMatches/PossibleMatch/fund" ).firstChild.nodeValue;
                        selectionObj.fundClass = xmlRoot.selectSingleNode( "./PossibleMatches/PossibleMatch/class" ).firstChild.nodeValue;
                        _self.setValue( selectionObj ); 
                    }
                    else
                    {
                        _suggestDropdown.clearTable();

                        var nextStartRecNumNode = xmlRoot.selectSingleNode("./nextStartRecNum");
                        if(nextStartRecNumNode != null)
                        {
                            _suggestDropdown.setMore(xmlRoot.selectSingleNode("./moreText").firstChild.nodeValue);
                            _nextStartRecNum = nextStartRecNumNode.firstChild.nodeValue;
                        }
                        else
                        {
                            _nextStartRecNum = null;
                        }

                        var possibleMatchesNodes = xmlRoot.selectNodes("./PossibleMatches/PossibleMatch");
                        var resultsArray = new Array();
                        for(var i = 0; i < possibleMatchesNodes.length; i++)
                        {
                            resultsArray[i] = new Object();
                            resultsArray[i].displayVal = possibleMatchesNodes[i].selectSingleNode("./displayValue").firstChild.nodeValue;
                            resultsArray[i].code = possibleMatchesNodes[i].selectSingleNode("./fund").firstChild.nodeValue;
                            resultsArray[i].fundClass = possibleMatchesNodes[i].selectSingleNode("./class").firstChild.nodeValue;

                        }

                        _suggestDropdown.populateResultTable(resultsArray);
                        _suggestDropdown.highlightFirstRow();
                        _suggestDropdown.enable();
                    }
                }
            }
            else
            {
                alert("HTTP error: " + _httpRequest.status);
            }
        }
    }
}




//==========================================================================================//

/**************************************************************************
 *
 **************************************************************************/
function isChar(keyCode)
{
    // a = 65 .... z = 90
     return (keyCode >= 65 && keyCode <= 90)
}


/**************************************************************************
 *
 **************************************************************************/
function isNum(keyCode)
{
    // 0 = 48 .... 9 = 57 (using top numeric keys)... 0 = 96 ... 9 = 105 (using keypad)
     return ((keyCode >= 48 && keyCode <= 57) || (keyCode >= 96 && keyCode <= 105))
}


/**************************************************************************
 *
 **************************************************************************/
function isTab(keyCode)
{

    // a = 65 .... z = 90
     return (keyCode == 9);
}


/**************************************************************************
 *
 **************************************************************************/
function isBackspace(keyCode)
{
     return (keyCode == 8);
}

/**************************************************************************
 *
 **************************************************************************/
function isDelete(keyCode)
{
    return (keyCode == 46);
}

/**************************************************************************
 *
 **************************************************************************/
function isUpArrow(keyCode)
{
     return (keyCode == 38);
}


/**************************************************************************
 *
 **************************************************************************/
function isDownArrow(keyCode)
{
     return (keyCode == 40);
}

/**************************************************************************
 *
 **************************************************************************/
function isRightArrow(keyCode)
{
     return (keyCode == 39);
}


/**************************************************************************
 *
 **************************************************************************/
function isLeftArrow(keyCode)
{
     return (keyCode == 37);
}

/**************************************************************************
 *
 **************************************************************************/
function isEnter(keyCode)
{
     return (keyCode == 13)
}


/**************************************************************************
 *
 **************************************************************************/
function isDecimal(keyCode)
{
     return (keyCode == 110 || keyCode == 190);
}

/**************************************************************************
 *
 **************************************************************************/
function isHome(keyCode)
{
     return (keyCode == 36);
}

/**************************************************************************
 *
 **************************************************************************/
function isEnd(keyCode)
{
     return (keyCode == 35);
}


/**************************************************************************
 *
 **************************************************************************/
function GetBranchName(servletPath, cz, companyCode, envName, ruserid, sessionId, brokercode, slsrepcode, branchFld, branchNameFld)
{
    var _self = this;

    var _branchName = null;
    var _branchCode = null;
    var _brokerCode = null;
    var _salesRepCode = null;

    var _branchFld = branchFld;
    var _branchNameFld = branchNameFld;

    var _httpRequest = null;

    var _url = null;

    this.search = function()
    {
        _url = servletPath + "?cz=" + cz
            + "&companyCode=" + companyCode
            + "&envName=" + envName
            + "&ruserId=" + ruserid
            + "&sessionId=" + sessionId
            + "&jobname=General_GetBranchName";

        _httpRequest = new ActiveXObject("MSXML2.XMLHTTP");

        var urlWithParam = _url + "&broker=" + brokercode + "&slsrep=" + slsrepcode;

        _httpRequest.open("POST", urlWithParam, false);

        _httpRequest.onreadystatechange = handleSearchResponse;

        _httpRequest.send();
    }

    /**************************************************************************
     *
     **************************************************************************/
    function handleSearchResponse()
    {
        if (_httpRequest.readyState == 4)
        {
            if (_httpRequest.status == 200)
            {
                // _httpRequest.responseText is of the form "<responseContents>...</responseContents>"
                var responseXMLDoc = XML_Lib.createXMLDoc();
                XML_Lib.loadFromString(responseXMLDoc, _httpRequest.responseText);

                var xmlRoot = responseXMLDoc.documentElement;

                _branchName = xmlRoot.selectSingleNode("./branchNm").firstChild.nodeValue;
                _branchCode = xmlRoot.selectSingleNode("./branch").firstChild.nodeValue;
                _self.setValue();
            }
            else
            {
                alert("HTTP error: " + _httpRequest.status);
            }
        }
    }

    this.setValue = function()
    {
        _branchFld.value = _branchCode;
        _branchFld.code = _branchCode;
        _branchNameFld.innerHTML = _branchName;
    }
}