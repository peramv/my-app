<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/DST_WebBehavioursTemplate.xsl"/>
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/AccountBalanceOverride_ResultsTemplate.xsl"/>  
  
  
  <xsl:variable name="vClient"       			select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  	select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      		select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          		select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"           			select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           			select="/websrvXML/FormInformation/cz"/>          
  <xsl:variable name="vTIDX"        			select="/websrvXML/FormInformation/tidx"/>  
  <xsl:variable name="dateFormat"    	select="/websrvXML/FormInformation/dateFormat"/>
  
  
  <xsl:template match="/">

    <Screen>
      
      <html>
        
        <head>
          <title>Account Balance Override</title>
          
          <!-- web library js code -->          
          <script src="{$vURL}WebLibrary/JSLib/Err.js"/>          
          <script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
          <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
          <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
          <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
          <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
          <script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>                       
          <script src="{$vURL}WebLibrary/WebComps/SuggestFieldComponent.js"/>
          <script src="{$vURL}javascript/General_Desktop.js"/>
          
          <script src="{$vURL}javascript/AccountBalanceOverride.js"/>
                                       
          <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"></link>
          
          <script>
            var _vURL             		= "<xsl:value-of select="$vURL"/>";
            var _vServletPath     	= "<xsl:value-of select="$vServletPath"/>";
            var _vCZ             		= "<xsl:value-of select="$vCZ"/>";
            var _companyCode    = "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
            var _ruserId          		= "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
            var _sessionId        	= "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
            var _envName        	= "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";
            var _dateFormat       	= "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
            
            setSessionToken( _sessionId );            
          </script>
         
          <xsl:call-template name="DST_WebBehavioursTmpl"/>
          
          <style>
            .Dropdown
			{
			width:450;
			height:228;				
			border:0px solid black;
			background:url('<xsl:value-of select="$vURL"/>images/SuggestDropdown_big.gif');
			padding:5px;				
			}
			
			.DropdownContent
			{
			font-size:10px;
			cursor:default;
			}
			
			.DropdownHighlight
			{
			cursor:default;
			font-size:10px;
			background: #EDEDED;
			}
            
            
            .DataHeader
            {
              font-weight: bold;
              padding-bottom: 4px;
              padding-left: 3px;
            }
            
            .DataField
            {              
              padding-top: 2px;
              padding-bottom: 2px;
              padding-left: 3px;
            }
          </style>
          
        </head>
        
        <body>
          <xsl:attribute name="onload">
				<xsl:choose>
					<xsl:when test="/websrvXML/responseContents/error">
						alert( "<xsl:value-of select="/websrvXML/responseContents/error"/>" );
					</xsl:when>
					<xsl:otherwise>
					loading();
					</xsl:otherwise>
				</xsl:choose>
          </xsl:attribute>
         
          
          <!-- header section -->
          <div style="width:570px; border:1px solid lightgrey; padding:10px">
            
            <div style="width:100%; padding-bottom:20px; padding-left:10px">
				<table>
					<tr>
						<td>
							<table style="table-layout:fixed">
								<tr>
									<td style="width:150px; font-weight:bold">Search Value:</td>
									<td style="width:420px;">
											<input class="DataInput" type="text" id="search_ValueFld" style="width:100%"/>
									</td>
									<td style="width:70;">
											<span style="">
												<xsl:call-template name="ColorButtonTmpl">
												  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
												  <xsl:with-param name="onclick">alertSearchOptions();</xsl:with-param>                                                   
												  <xsl:with-param name="size">small</xsl:with-param>
												  <xsl:with-param name="width">70</xsl:with-param>
												  <xsl:with-param name="text">Options</xsl:with-param>
												  <xsl:with-param name="color">orange</xsl:with-param>
												</xsl:call-template>
											</span>                
									</td>
								</tr>
								<tr>
								    <td id="searchMatchDetailsLbl" style="width:150px; height:35px; font-style:italic"></td>
									<td style="width:420px; height:35px;" colspan="2">
										<span id="searchMatchDetailsFld"  style=" font-style:italic; width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										</span>
									</td>
								</tr>								
								<tr>
									<td style="width:150px; font-weight:bold">Fund:</td>
									<td style="width:420px">
										  <!-- fund suggestfield -->
										  <input suggestField="true"
											class="DataInput" 
											type="text" 
											id="search_FundFld"
											style="width:100%"                              
											dropdownClass="Dropdown" 
											contentClass="DropdownContent"
											highlightClass="DropdownHighlight" 
											displayItems="displayValue"                
											searchURLGenerator="getFundSearchURL"
											initialValue=""
										  />
									</td>
									<td style="width:70;">
											<span style="">
												<xsl:call-template name="ColorButtonTmpl">
												  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
												  <xsl:with-param name="onclick">alertFundSuggestOptions();</xsl:with-param>                                                   
												  <xsl:with-param name="size">small</xsl:with-param>
												  <xsl:with-param name="width">70</xsl:with-param>
												  <xsl:with-param name="text">Options</xsl:with-param>
												  <xsl:with-param name="color">orange</xsl:with-param>
												</xsl:call-template>
											</span>                
									</td>
								</tr>                              
								<tr>
									<td style="width:150px; font-weight:bold">Start Date:</td>
									<td style="width:420px" colspan="2">
										<span style="width:250">
											<input id="search_StartDateFld" type="text" class="dstdatepicker">
												<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
											</input>
										 </span>
									</td>
								</tr>       
								<tr>
									<td style="width:150px; font-weight:bold">End Date:</td>
									<td style="width:420px" colspan="2">
										<span style="width:250">
											<input id="search_StopDateFld" type="text" class="dstdatepicker">
												<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
										   </input>
										</span>
									</td>
								</tr>                  
							</table>              
						  </td>
						  <td valign="bottom">
							  <span style="position:relative; left:-75; top:5">
								  <xsl:call-template name="ColorButtonTmpl">
									  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
									  <xsl:with-param name="onclick">search();</xsl:with-param>
									  <xsl:with-param name="size">large</xsl:with-param>
									  <xsl:with-param name="width">90</xsl:with-param>
									  <xsl:with-param name="text">Search</xsl:with-param>
									  <xsl:with-param name="color">orange</xsl:with-param>
							  </xsl:call-template>
                    </span>
                  </td>
                </tr>
              </table>              
              
            </div>

            
          <!-- data section -->                                
            <fieldset style="position:relative; left:10px; width:100%; padding-left:15px; padding-right:15px; padding-bottom:25px;">              
              <div style="width:700px">              
                <table cellpadding="0" cellspacing="0" style="table-layout:fixed">
                  <tr>                    
                    <td class="DataHeader" style="width:125px; border-bottom:2px solid black">Account</td>
                    <td class="DataHeader" style="width:175px; border-bottom:2px solid black">Name</td>                                       
                    <td class="DataHeader" style="width:150px; border-bottom:2px solid black">Effective Date</td>
                    <td class="DataHeader" style="width:125px; border-bottom:2px solid black">Fund</td> 
                    <td class="DataHeader" style="width:100px; border-bottom:2px solid black">Units</td>
                  </tr>
                </table>
                
                <div id="accountBal_ListContentsDiv">
                </div>  
               
              </div>                                      
            </fieldset>
            
            <!-- action buttons -->
            <div id="fundActionButtonsDiv" style="position:relative; left:90px; width:100%; text-align:center; padding-top:10px; padding-bottom:10px">
              <span>
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="onclick">openPopup( "add" );</xsl:with-param>
                  <xsl:with-param name="size">small</xsl:with-param>
                  <xsl:with-param name="width">70</xsl:with-param>
                  <xsl:with-param name="text">Add</xsl:with-param>
                  <xsl:with-param name="color">green</xsl:with-param>
                </xsl:call-template>
              </span>
              <span style="padding-left:5px; padding-right:5px;">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                  <xsl:with-param name="onclick">openPopup( "modify" );</xsl:with-param>
                  <xsl:with-param name="size">small</xsl:with-param>
                  <xsl:with-param name="width">70</xsl:with-param>
                  <xsl:with-param name="text">Modify</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>
              <span>
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="onclick">openPopup( "delete" );</xsl:with-param>
                  <xsl:with-param name="size">small</xsl:with-param>
                  <xsl:with-param name="width">70</xsl:with-param>
                  <xsl:with-param name="text">Delete</xsl:with-param>
                  <xsl:with-param name="color">red</xsl:with-param>
                </xsl:call-template>
              </span>                 
            </div>
          </div>
          
          
          <div style="cursor:pointer; position:relative; width:100; left:325; top:25; height:50;" align="center">
			  <xsl:call-template name="ColorButtonTmpl">
				<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
				<xsl:with-param name="id">btnCloseWindow</xsl:with-param>
				<xsl:with-param name="onclick">UTL.getElem( "btnClose" ).click();</xsl:with-param>
				<xsl:with-param name="size">large</xsl:with-param>
				<xsl:with-param name="width">100</xsl:with-param>
				<xsl:with-param name="text">Close</xsl:with-param>
				<xsl:with-param name="color">orange</xsl:with-param>
			  </xsl:call-template>
			  <input type="button" id="btnClose" style="display:none"/>
		  </div>
                                
            
          
          
          <!-- page disabling div -->
          <div id="disableDiv" style="position:absolute; top:0; left; 0; width:100%; height:100%; background:e6e6e6; filter:alpha(opacity=70); display:none;">
          </div>
          
          <div id="searchIndicatorDiv" style="position:absolute; border:2px solid grey; width:200; height:50; background:white; z-index:50; padding-top:10px; display:none">
            <span style="width:100%; text-align:center; font-size:15px; font-style:italic">Searching ...</span>
          </div>
          
          <!-- popup div -->
          <div id="popupDiv" style="position:absolute; border:2px solid grey; width:650; height:170; background:white; z-index:50; display:none">                 
            <table align="center" style="width:550; position:relative; top:10; table-layout:fixed" >
              <tr>
                <td style="width:130px">
                  Account:
                </td>
                <td style="width:420">               
                  <!-- account suggestfield -->
                  <input suggestField="true"                    
                    type="text" 
                    id="popup_AccountFld"
                    style="width:100%"                              
                    dropdownClass="Dropdown" 
                    contentClass="DropdownContent"
                    highlightClass="DropdownHighlight" 
                    displayItems="displayValue"                
                    searchURLGenerator="getAccountSearchURL"
                    initialValue=""
                    detailsDisplayElement="accountSuggestDetailsDiv"
                  />
                </td>
                <td style="width:70">
					<span style="">
						<xsl:call-template name="ColorButtonTmpl">
						  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
						  <xsl:with-param name="onclick">alertAccountSuggestOptions();</xsl:with-param>                                                   
						  <xsl:with-param name="size">small</xsl:with-param>
						  <xsl:with-param name="width">70</xsl:with-param>
						  <xsl:with-param name="text">Options</xsl:with-param>
						  <xsl:with-param name="color">orange</xsl:with-param>
						</xsl:call-template>
					</span>                
                </td>
              </tr>              
              <tr>
                <td style="width:130px">
                  Fund:
                </td>
                <td style="width:420">               
                  <!-- fund suggestfield -->
                  <input suggestField="true"                    
                    type="text" 
                    id="popup_FundFld"
                    style="width:100%"                              
                    dropdownClass="Dropdown" 
                    contentClass="DropdownContent"
                    highlightClass="DropdownHighlight" 
                    displayItems="displayValue"                
                    searchURLGenerator="getFundSearchURL"
                    initialValue=""
                  />
                </td>
                <td style="width:70">
					<span style="">
						<xsl:call-template name="ColorButtonTmpl">
						  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
						  <xsl:with-param name="onclick">alertFundSuggestOptions();</xsl:with-param>                                                   
						  <xsl:with-param name="size">small</xsl:with-param>
						  <xsl:with-param name="width">70</xsl:with-param>
						  <xsl:with-param name="text">Options</xsl:with-param>
						  <xsl:with-param name="color">orange</xsl:with-param>
						</xsl:call-template>
					</span>                
                </td>
              </tr>                            
              <tr>            
                <td style="width:130px">
                  Effective Date:
                </td> 
                <td style="width:420" colspan="2">
                  <span style="width:180">
                    <input id="popup_EffDateFld" type="text" class="dstdatepicker">
						<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
                    </input>
                  </span>
                </td> 
              </tr>
              <tr>            
                <td style="width:130px">
                  Units:
                </td> 
                <td style="width:420" colspan="2">
                  <span style="width:180">
                    <input id="popup_UnitsFld" type="text" style="width:100%">                      
                    </input>
                  </span>
                </td> 
              </tr>             
              <tr>
                <td colspan="3" style="text-align:center; padding-top:10px">                                   
                  <span id="popup_AddBtn" style="padding-right:5px; display:none">
                    <xsl:call-template name="ColorButtonTmpl">
                      <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                      
                      <xsl:with-param name="onclick">addAccountBal()</xsl:with-param>                                      
                      <xsl:with-param name="size">large</xsl:with-param>
                      <xsl:with-param name="width">100</xsl:with-param>
                      <xsl:with-param name="text">Add</xsl:with-param>
                      <xsl:with-param name="color">green</xsl:with-param>
                    </xsl:call-template>
                  </span>
                  <span id="popup_DeleteBtn" style="padding-right:5px; display:none">
                    <xsl:call-template name="ColorButtonTmpl">
                      <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                      
                      <xsl:with-param name="onclick">deleteAccountBal()</xsl:with-param>                                      
                      <xsl:with-param name="size">large</xsl:with-param>
                      <xsl:with-param name="width">100</xsl:with-param>
                      <xsl:with-param name="text">Delete</xsl:with-param>
                      <xsl:with-param name="color">green</xsl:with-param>
                    </xsl:call-template>
                  </span>
                  <span id="popup_ModifyBtn" style="padding-right:5px; display:none">
                    <xsl:call-template name="ColorButtonTmpl">
                      <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                      <xsl:with-param name="id">popup_ModifyBtn</xsl:with-param>
                      <xsl:with-param name="onclick">modifyAccountBal()</xsl:with-param>                                      
                      <xsl:with-param name="size">large</xsl:with-param>
                      <xsl:with-param name="width">100</xsl:with-param>
                      <xsl:with-param name="text">Save</xsl:with-param>
                      <xsl:with-param name="color">green</xsl:with-param>
                    </xsl:call-template>
                  </span>                     
                  <span>
                    <xsl:call-template name="ColorButtonTmpl">
                      <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                      <xsl:with-param name="onclick">closePopup();</xsl:with-param>
                      <xsl:with-param name="size">large</xsl:with-param>
                      <xsl:with-param name="width">100</xsl:with-param>
                      <xsl:with-param name="text">Cancel</xsl:with-param>
                      <xsl:with-param name="color">orange</xsl:with-param>
                    </xsl:call-template>
                  </span>                                
                </td>
              </tr>
            </table>                  
          </div>
          
          <div id="accountSuggestDetailsDiv" 
               style="position:absolute; top:400; left:0; width:220; height:120; display:none; z-index:1000">
            <iframe src="javascript:false" style="position:absolute; left:0; top:0; width:100%; height:100%" frameBorder="0"/>
            <div style="position:absolute; left:0; top:0; width:100%; height:100%; background:#FFFFE1; border:1px solid black; padding:2px">              
              <table cellpadding="0" cellspacing="0" style="table-layout:fixed">
                <tr>
                  <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">AcctNum:</td>
                  <td suggestField="acctNum" style="font-size:10px; width:80px; padding-bottom:3px;"></td>
                  <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">BrokerAcct:</td>
                  <td suggestField="brkAcct" style="font-size:10px; width:130px; padding-bottom:3px"></td>
                </tr>
                <tr>
                  <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">Broker:</td>
                  <td suggestField="broker" style="font-size:10px; width:80px; padding-bottom:3px"></td>                  
                  <td suggestField="brokerName" style="font-size:10px; width:130px; padding-bottom:3px" colspan="2"></td>
                </tr>
                <tr>
                  <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">Branch:</td>
                  <td suggestField="branch" style="font-size:10px; width:80px; padding-bottom:3px"></td>                  
                  <td suggestField="brnName" style="font-size:10px; width:130px; padding-bottom:3px" colspan="2"></td>
                </tr>
                <tr>
                  <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">SalesRep:</td>
                  <td suggestField="salesRep" style="font-size:10px; width:80px; padding-bottom:3px"></td>                  
                  <td suggestField="slsrepName" style="font-size:10px; width:130px; padding-bottom:3px" colspan="2"></td>
                </tr>                
              </table>
              
              <div style="width:100%; text-align:left; padding-left:20px">
                <table>
                  <tr>
                    <td style="font-size:10px; font-weight:bold">Address</td>
                    <td>
                      <table>
                        <tr>
                          <td suggestField="addr1" style="font-size:10px"></td>
                          <td suggestField="addr2" style="font-size:10px"></td>
                        </tr>
                        <tr>
                          <td suggestField="addr3" style="font-size:10px"></td>
                          <td suggestField="addr4" style="font-size:10px"></td>
                        </tr>
                        <tr>
                          <td suggestField="addr5" style="font-size:10px"></td>
                          <td style="font-size:10px"></td>
                        </tr>
                      </table>
                    </td>
                  </tr>
                </table>                                
              </div>
              
            </div>            
          </div>
          
        </body>

      </html>
    </Screen>

  </xsl:template>
  
  <!-- ============================= MAKING A LIST DROP DOWN ======================================================== -->
  <xsl:template match="List">
    <xsl:param name="selected"/>    
    <xsl:apply-templates select="Element"> <xsl:with-param name="selected"><xsl:value-of select="$selected"/></xsl:with-param> </xsl:apply-templates>
  </xsl:template>
  
  <xsl:template match="Element">
    <xsl:param name="selected"/>
    <option>
      <xsl:attribute name="value">
        <xsl:value-of select="code"/>
      </xsl:attribute>
      <xsl:if test="code=$selected">
        <xsl:attribute name="selected">true</xsl:attribute>
      </xsl:if>
      <xsl:value-of select="value"/>
    </option>
  </xsl:template>
  
  
</xsl:stylesheet>
