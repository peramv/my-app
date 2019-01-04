<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes"/>
   
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/DST_WebBehavioursTemplate.xsl"/>

  <xsl:variable name="vClient" 			select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath" 	select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir" 		select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL" 			select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX" 				select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ" 				select="/websrvXML/FormInformation/cz"/>
  <xsl:variable name="vTIDX"/>

  <xsl:variable name="vEnvName" 		select="/websrvXML/FormInformation/envName"/>
  <xsl:variable name="vCompanyCode"     select="/websrvXML/FormInformation/companyCode"/>
  <xsl:variable name="vRUserId" 		select="/websrvXML/FormInformation/ruserId"/>
  <xsl:variable name="vSessionId" 		select="/websrvXML/FormInformation/sessionId"/>
  <xsl:variable name="dateFormat" 		select="/websrvXML/FormInformation/dateFormat"/>

  <xsl:variable name="vMarket" 			select="/websrvXML/FormInformation/market"/>



  <xsl:template match="/">
    <Screen>  
      <html>
        <head>
            
            <title>Dilution Calculator</title>
  
            <!-- Library Code-->
            <script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
            <script src="{$vURL}WebLibrary/JSLib/Err.js"/>
            <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
            <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
            <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
            <script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
            <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
            <script src="{$vURL}WebLibrary/WebComps/SuggestFieldComponent.js"/>          
            <script src="{$vURL}/javascript/General_DesktopError.js"/>
            <script src="{$vURL}/javascript/General_Desktop.js"/>
            
            <!-- Page Specific Code-->
            <script src="{$vURL}/javascript/DilutionCalculator.js"/>
            <script>
                var _vURL 						= "<xsl:value-of select="$vURL"/>";
                var _vServletPath 			    = "<xsl:value-of select="$vServletPath"/>";
                var _vCZ 							= "<xsl:value-of select="$vCZ"/>";
                var _companyCode 			        = "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
                var _ruserId     					= "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
                var _sessionId   				    = "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
                var _envName   				    = "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";
                var _dateFormat 				    = "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
                
                setSessionToken( _sessionId );
                
                function loading()
                {
                   initDilutionCalc();
                }   
            </script>
  
            <style>
                BODY, DIV, TABLE, TD, LEGEND
                {
                font-family:  CourierNew,  Verdana, Arial, Sans-Serif;
                font-size: 10pt;
                cursor: default;    
                }
                
                LEGEND
                {
                color: black;
                font-weight: 600;
                }
                
                
                
                .ScreenTitle
                {
                font-size: 10pt;
                font-weight: 600;
                }
              
              
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
                          
                .TableLabel
                {
                  font-weight: bold;
                  width: 100px;
                }
                
                .FieldLabel
                {
                  font-weight: bold;
                  width:175px;        
                }
                
                .FieldFlag
                {
                  width:30px;
                }
                
                .FieldData
                {
                  width:200px;
                }
                
                .DataInput
                {
                  width:100%;
                }
                
                .TransTable
                {
                  border:1px solid black;                
                }
                            
                .TransTable .TransDataHeader
                {
                  border-bottom:1px solid black;
                  border-right:1px solid black;
                  font-weight:bold;
                  height:20px;
                  text-align:center;
                  background:#939496;
                }
                
                .TransTable .TransRow_even
                {              
                  background:white;
                }
                
                .TransTable .TransRow_odd
                {              
                  background:#E9E9E9;
                }
                
                .TransTable .TransDataItem
                {
                  border-bottom:1px solid black;
                  border-right:1px solid black;
                  height:20px;
                  padding-left:1px;
                  border-collapse: collapse;
                }
                
                .TransTable .ExclCheckbox
                {
                  position:relative;
                  left:5px;
                }
                
                .TransTable .TransDataEmpty
                {
                  text-align:center;
                  font-style:italic;
                  height:26px;
                }                 
            </style>
  
            <xsl:call-template name="DST_WebBehavioursTmpl"/>
          </head>
  
          <body onload="loading()">
            
            <div id="maindiv" style="position:relative; top:5; left:5; text-align:center; width:1215;">
              
              <!-- **** INPUT SECTION ***** -->
              <fieldset style="width:739; padding-bottom:5px">
                                
                <div style="width:100%; text-align:left;">
                  <table style="tableLayout:fixed; position:relative; left:50">
                    <tr>
                      <td class="FieldLabel">Account</td>
                      <td class="FieldData">                                         
                        <!-- account suggestfield -->
                        <input suggestField="true"
                               class="DataInput" 
                               type="text" 
                               id="suggestAccountField"                              
                               dropdownClass="Dropdown" 
                               contentClass="DropdownContent"
                               highlightClass="DropdownHighlight" 
                               displayItems="displayValue"
                               searchURLGenerator="getAccountSearchURL"
                               initialValue=""
                               detailsDisplayElement="accountSuggestDetailsDiv"
                               style="width:450"                            
                               />
                      </td>
                    </tr>                  
                    <tr>
                      <td class="FieldLabel">Fund</td>
                      <td class="FieldData">                      
                        <!-- fund suggestfield -->
                        <input suggestField="true" 
                          type="text"
                          class="DataInput" 
                          id="suggestFundField" 
                          dropdownClass="Dropdown" 
                          contentClass="DropdownContent"
                          highlightClass="DropdownHighlight" 
                          displayItems="displayValue"
                          searchURLGenerator="getFundSearchURL"
                          style="width:450"
                        />
                      </td>
                    </tr>
                    <tr>
                      <td class="FieldLabel">Transaction Type</td>
                      <td class="FieldData">
                        <!-- trans type select box -->
                        <select id="transTypeField" class="DataInput">
                          <xsl:apply-templates select="//List[@listName='TransactionTypeOptions']">
                            <xsl:with-param name="selected"
                              select="//ListSelection[@listName='TransactionTypeOptions']"/>
                          </xsl:apply-templates>
                        </select>
                      </td>
                    </tr>
                    <tr>
                      <td class="FieldLabel">Trans #</td>
                      <td class="FieldData">
                        <!-- trans num text field -->
                        <input id="transNumField" type="text" class="DataInput" value=""/>
                      </td>
                    </tr>
                    <tr>
                      <td class="FieldLabel">Gross Amount</td>
                      <td class="FieldData">
                        <!-- gross amt text field -->
                        <input id="grossAmountField" type="text" class="DataInput" value=""/>
                      </td>
                    </tr>
                    <tr>
                      <td class="FieldLabel">Trade Date</td>
                      <td class="FieldData">
                        <!-- trade date dstdatepicker -->
                        <input id="tradeDateField" type="text" class="dstdatepicker" value="">
                          <xsl:attribute name="dateformat">
                            <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                          </xsl:attribute>
                        </input>
                        
                      </td>
                    </tr>
                    <tr>
                      <td class="FieldLabel">Calculation Date</td>
                      <td class="FieldData">
                        <!-- calc date dstdatepicker -->
                        <input id="calcDateField" type="text" class="dstdatepicker DataInput" value="">
                          <xsl:attribute name="dateformat">
                            <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                          </xsl:attribute>
                        </input>
                      </td>
                    </tr>
                  </table>
                </div>
                
                <!-- buttons -->
                <div style="text-align:right; width:95%; padding-top:5px;">
                  <input id="btnAddTrans" type="button" value="Add Trans." style="width:100px"/>
                  <input id="btnClearFields" type="button" value="Clear" style="width:100px"/>
                </div>                           
              </fieldset>
              
              
              <!-- **** TRANS TABLE SECTION **** -->
              <fieldset style="position:relative; padding:6px; text-align:center; top:25px" >
                <div id="transTableDiv" class="TransTable" style="width:960; height:200; text-align:left; overflow-y:scroll">
                  <!-- table -->
                  <table cellpadding="0" cellspacing="0" id="transTable" style="table-layout:fixed">
                    <thead>
                      <tr>
                        <td class="TransDataHeader" style="width:37;">Excl.</td>
                        <td class="TransDataHeader" style="width:80">Account</td>
                        <td class="TransDataHeader" style="width:90">Fund/Class</td>                      
                        <td class="TransDataHeader" style="width:120">Trans.Type</td>
                        <td class="TransDataHeader" style="width:120">Trans.#</td>
                        <td class="TransDataHeader" style="width:143">Gross Amt.</td>
                        <td class="TransDataHeader" style="width:118">Units</td>
                        <td class="TransDataHeader" style="width:90">Trade Date</td>
                        <td class="TransDataHeader" style="width:95">Trade Rate</td>
                        <td class="TransDataHeader" style="width:90">Calc. Date</td>
                        <td class="TransDataHeader" style="width:95">Calc. Rate</td>
                        <td class="TransDataHeader" style="width:100">Gain/Loss</td>
                      </tr>
                    </thead>
                    <tbody>
                    </tbody>
                  </table>                
                </div>
                <!-- buttons -->
                <div style="text-align:right; width:95%; padding-top:10px">
                  <input type="button" id="btnCalcDilution" value="Calculate Dilution"/>
                  <input type="button" id="btnClearTrans" value="Clear" style="width:100px;"/>  
                </div>              
              </fieldset>
  
              
              
              <!-- **** TOTALS SECTION ***  -->
              <fieldset style="position:relative; top:50; width:600">
                <table>   
                  <tr>
                    <!-- total gross amt -->
                    <td class="FieldLabel" align="right" style="width:250;"  valign="bottom">
                      Total Gross Amount:
                    </td>
                    <td class="FieldData" id="results_totalGrossAmtFld" style="width:150; height:25px" valign="bottom" colspan="2">					  
                    </td>
                  </tr>                               
                  <tr>
                    <!-- gain/loss before distribution -->
                    <td class="FieldLabel" valign="bottom" align="right" style="width:250; height:25px">
                      Gain/Loss before Distribution:
                    </td>
                    <td id="results_gainLossBeforeDistrFld"  valign="bottom" class="FieldData" style="width:150; height:25px" colspan="2"></td>
                  </tr>
                  <tr>
                    <!-- distribution dilution -->
                    <td  class="FieldLabel" align="right"  valign="bottom" style="width:250; height:25px">
                      Distribution Dilution:</td>
                    <td class="FieldData" style="width:150; height:25px" colspan="2">
  					  <input type="text" id="results_distrDilutionFld" style="width:130px; text-align:right" disabled="true"></input>
                    </td>
                  </tr>                
                  <tr>
                    <!-- total dilution -->
                    <td class="FieldLabel" align="right" style="width:250;"  valign="bottom">
                      Total Dilution:
                    </td>
                    <td id="results_totalDilutionFld" class="FieldData" style="width:150; height:25px"  valign="bottom"></td>
  				  <td style="width:100; height:25px"  valign="bottom">
  				      <!-- total dilution update btn -->
  					  <input type="button" id="updateTotalDilutionBtn" value="Update" disabled="true" onclick="updateTotalDilution()"/>
  				  </td>
                  </tr>
                </table>
              </fieldset>            
  
              <div style="position:relative; top:75; text-align:right; padding-right:40">
                <input id="btnClose" type="button" value="Close" style="width:100px;"/>
              </div>
  
            </div>
  
            
            
  
  
            <!-- popup div for the account details -->          
           <div id="accountSuggestDetailsDiv" 
                          style="position:absolute; top:400; left:0; width:500; height:120; display:none; z-index:1000">
                          <iframe src="javascript:false" style="position:absolute; left:0; top:0; width:100%; height:100%" frameBorder="0"/>                        
                          <div style="position:absolute; left:0; top:0; width:100%; height:100%; background:#FFFFE1; border:1px solid black; padding:2px">
                          
  							<table>
  								<tr>
  									<td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">AcctNum:</td>
  									<td suggestField="acctNum" style="font-size:10px; width:60px; padding-bottom:3px;"></td> 
  								</tr>
  							</table>
  							
  							<div style="width:100%; text-align:left;">
                                  <table>
                                      <tr>
                                          <td valign="top" style="font-size:10px; width:90px; font-weight:bold; padding-top:3px; padding-bottom:3px; padding-right:2px">Address:</td>
                                          <td>
                                              <table>
                                                  <tr>
                                                      <td suggestField="addr1" style="font-size:10px"></td>
                                                  </tr>    
                                                  <tr>
                                                      <td suggestField="addr2" style="font-size:10px"></td>
                                                  </tr>
                                                  <tr>
                                                      <td suggestField="addr3" style="font-size:10px"></td>
                                                   </tr>
                                                   <tr>
                                                      <td suggestField="addr4" style="font-size:10px"></td>
                                                  </tr>
                                                  <tr>
                                                      <td suggestField="addr5" style="font-size:10px"></td>
                                                  </tr>
                                              </table>
                                          </td>
                                      </tr>
                                  </table>                                
                              </div>
  						                                
                               <table>																			   
                                  <tr>
                                      <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">Broker:</td>
                                      <td suggestField="broker" style="font-size:10px; width:60px; padding-bottom:3px"></td>                  
                                      <td suggestField="brokerName" style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                  </tr>
                                  <tr>
                                      <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">Branch:</td>
                                      <td suggestField="branch" style="font-size:10px; width:60px; padding-bottom:3px"></td>                  
                                      <td suggestField="brnName" style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                  </tr>
                                  <tr>
                                      <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">SalesRep:</td>
                                      <td suggestField="salesRep" style="font-size:10px; width:60px; padding-bottom:3px"></td>                  
                                      <td suggestField="slsrepName" style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                  </tr>
                                   <tr>
                                      <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">BrkAcct:</td>
                                      <td suggestField="brkAcct" style="font-size:10px; width:60px; padding-bottom:3px;"></td>                                    
                                      <td style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                  </tr>                
                              </table>
                              
                          </div>            
                      </div>
              
          </body>
        </html>
      </Screen>      
  </xsl:template>

  
  <!-- select box LIST template -->
  <xsl:template match="List">
    <xsl:param name="showCode"/>
    <xsl:param name="selected"/>
    <xsl:for-each select="Element">
      <xsl:element name="option">
        <xsl:if test="$selected=code">
          <xsl:attribute name="selected">selected</xsl:attribute>
        </xsl:if>
        <xsl:choose>
          <xsl:when test="$showCode =&quot;yes&quot;">
            <xsl:attribute name="value">
              <xsl:value-of select="code"/>
            </xsl:attribute>
            <xsl:value-of select="value"/> - <xsl:value-of select="code"/>
          </xsl:when>
          <xsl:otherwise>
            <xsl:attribute name="value">
              <xsl:value-of select="code"/>
            </xsl:attribute>
            <xsl:value-of select="value"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
