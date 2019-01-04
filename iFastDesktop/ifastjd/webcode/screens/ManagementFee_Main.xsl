<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/DST_WebBehavioursTemplate.xsl"/>
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/ManagementFee_HoldingEntityListTemplates.xsl"/>
  
  <xsl:variable name="vClient"    		select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  	select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"    		select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"       		select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"        		select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"        		select="/websrvXML/FormInformation/cz"/>          
  <xsl:variable name="vTIDX"       		select="/websrvXML/FormInformation/tidx"/>  
  <xsl:variable name="dateFormat"    	select="/websrvXML/FormInformation/dateFormat"/>

  
  <xsl:template match="/">

    <Screen>
      
      <html>
        
        <head>
          <title>Institutional Accounts</title>

          <!-- web library js code -->
          <script src="{$vURL}WebLibrary/JSLib/Cookie.js"/>
          <script src="{$vURL}WebLibrary/JSLib/Err.js"/>          
          <script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
          <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
          <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
          <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
          <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
          <script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
          
          <script src="{$vURL}WebLibrary/WebComps/IFDSTableComponent.js"/>    
          <script src="{$vURL}WebLibrary/WebComps/SuggestFieldComponent.js"/>
          
          <script src="{$vURL}javascript/General_Desktop.js"/>
                    
          <!-- page specific js code -->          
          <script src="{$vURL}javascript/ManagementFee_Main.js"/>          
          
          <script>
            var _vURL = "<xsl:value-of select="$vURL"/>";
            var _vServletPath = "<xsl:value-of select="$vServletPath"/>";
            var _vCZ = "<xsl:value-of select="$vCZ"/>";
            var _companyCode = "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
            var _ruserId     = "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
            var _sessionId   = "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
            var _envName   = "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";
            
            var _dateFormat   = "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
            var _holdingEntityID = "<xsl:value-of select="/websrvXML/FormInformation/EntityID"/>";
            var _updateOccured = false;
            var _allowUpdates = "<xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates"/>";
            var _invoiceHistoryStatus = "";
            
            setSessionToken( _sessionId );
               
            <xsl:choose>
              <xsl:when test="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity">
                var _holdingEntityVersionNum = <xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/version"/>;
              </xsl:when>
              <xsl:otherwise>
                var _holdingEntityVersionNum = 0;                
              </xsl:otherwise>
            </xsl:choose>
                              
            var _imagePath = '<xsl:value-of select="$vURL"/>images';
                        
            var _modifiableDivs = new Array ();       
            var _treeStructure = new Object ();
            var _structure = new Cookie ("structure");
            
            
            function onLoad()
            {                                        
				<xsl:choose>
					<xsl:when test="/websrvXML/dtHoldingEntityMFInitResponse/RequestStatus/Errors">					
						 UTL.getElem( "grayDiv" ).style.display = "none";
						alert( "<xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/RequestStatus/Errors/Error/text"/>" );
					</xsl:when>
					<xsl:otherwise>
						   hideInvoiceHistory();
						  _invoiceHistoryStatus = "hidden";
						  
						  if ("<xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/ListSelection[@id='MFCalMethods']"/>" == "FA")
							document.getElementById("aggregationFieldset").style.display = "none";
							
						  buildModifiableDivs();
						  //document.getElementById("accountsDiv").style.display = "none";
						  handleLoadCookie(); 
										
						  if ( _holdingEntityVersionNum == 0 )
						  {
							  UTL.getElem( "grayDiv" ).style.height = 0;
							  openEntityModify();
						  }
						  else
						  {
							  UTL.getElem( "grayDiv" ).style.height = WebTools.findElemPos( UTL.getElem( "btnCloseWindow" ) )["top"] - 160;   
						  }         
						  hideInvoiceHistory();
						  _invoiceHistoryStatus = "hidden";
						  
						  if ("<xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/ListSelection[@id='MFCalMethods']"/>" == "FA")
							document.getElementById("aggregationFieldset").style.display = "none";
							
						  buildModifiableDivs();
						  //document.getElementById("accountsDiv").style.display = "none";
						  handleLoadCookie(); 
										
						  if ( _holdingEntityVersionNum == 0 )
						  {
							  UTL.getElem( "grayDiv" ).style.height = 0;
							  openEntityModify();
						  }
						  else
						  {
							  UTL.getElem( "grayDiv" ).style.height = WebTools.findElemPos( UTL.getElem( "btnCloseWindow" ) )["top"] - 160;   
						  }         
						  
						  setAccountsScrolling();
					</xsl:otherwise>
				</xsl:choose>
            }
            
            function onUnload()
            {              
              handleSaveCookie();                    
            }        
          </script>
          
          
          <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"></link>
          
          
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
                    </style>
          
          <xsl:call-template name="DST_WebBehavioursTmpl"/>
          
        </head>
        
        <body bgcolor="white" style="overflow:auto;" onLoad="onLoad();" onUnload="onUnload();">         
          <xsl:call-template name="tmplForm"/>
        </body>

      </html>
    </Screen>

  </xsl:template>



  <!-- ======================================================================= -->
  <xsl:template name="tmplForm">
    <br/>
    
    <xsl:if test="/websrvXML/responseContents/error">
      <script>alert('<xsl:value-of select="/websrvXML/responseContents/error"/>');</script>
    </xsl:if>
    
    <!-- Top Information Div -->    
    <fieldset style="position:relative; left:-5; left:10; top:0; width:900;  display:block;">
      <legend>
        <font color="black">          
          <b> Holding Entity </b>
        </font>
      </legend>
      
      
      <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">
        <div id="modifyEntityBtn" align="center">
          <xsl:attribute name="style">
          	cursor:pointer; position:absolute; left:725; top:0; width:70; height:15; overflow:hidden; 
            <xsl:choose>
              <xsl:when test="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity">                
                display:block;
              </xsl:when>
              <xsl:otherwise>
                display:none;
              </xsl:otherwise>
            </xsl:choose>                        
          </xsl:attribute>
          
          <xsl:call-template name="ColorButtonTmpl">
            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
            <xsl:with-param name="id">modifyDescBtn</xsl:with-param>
            <xsl:with-param name="onclick">openEntityModify();</xsl:with-param>
            <xsl:with-param name="size">small</xsl:with-param>
            <xsl:with-param name="width">70</xsl:with-param>
            <xsl:with-param name="text">Modify</xsl:with-param>
            <xsl:with-param name="color">orange</xsl:with-param>
          </xsl:call-template>
        </div>
      </xsl:if>
    	<div id="entityHistoryBtnDiv" align="center">
    		<xsl:attribute name="style">
    			cursor:pointer; position:absolute; left:800; top:0; width:70; height:15; overflow:hidden; 
    			<xsl:choose>
    				<xsl:when test="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity">                
    					display:block;
    				</xsl:when>
    				<xsl:otherwise>
    					display:none;
    				</xsl:otherwise>
    			</xsl:choose>                        
    		</xsl:attribute>
    		
    		<xsl:call-template name="ColorButtonTmpl">
    			<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
    			<xsl:with-param name="id">entityHistoryBtn</xsl:with-param>
    			<xsl:with-param name="onclick">sendHistoryRequest( "HoldEnt" );</xsl:with-param>
    			<xsl:with-param name="size">small</xsl:with-param>
    			<xsl:with-param name="width">70</xsl:with-param>
    			<xsl:with-param name="text">History</xsl:with-param>
    			<xsl:with-param name="color">orange</xsl:with-param>
    		</xsl:call-template>
    	</div>
      <div style="position:relative; top:3; left:15;">
              
        <!-- HOLDING ENTITY INFORMATION - DESCRIPTION TABLE -->
        <table id="holdingEntityInfo_descriptionTable">
          <xsl:attribute name="style">
                display:block; width:90%; position:relative; top:-3;
          </xsl:attribute>
          <tr>
            <td style="width:180;" align="right"> Entity Name: </td>
            <td id="holdingEntityInfo_entName">
              <xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/entName"/>
            </td>
          </tr>    
          <tr>
            <td style="width:180;" align="right"> Entity Code: </td>
            <td id="holdingEntityInfo_EntityCodeLbl">
              <xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/holdingEntityCode"/>
            </td>
          </tr>          
          <tr>
            <td style="width:180;" align="right"> Calculation Method: </td>
            <td id="holdingEntityInfo_CalcMethodLbl">
              <!-- this is a bit of a hack to get the CalMethod label to be dispalyed, rather than just the code -->
              <xsl:variable name="calcMethodSelection">
                <xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/ListSelection[@id='MFCalMethods']"/>  
              </xsl:variable>
              <xsl:for-each select="/websrvXML/dtHoldingEntityMFInitResponse/List[@listName='MfCalMethods']/Element">
                <xsl:if test="code = $calcMethodSelection">
                  <xsl:value-of select="value"/>
                </xsl:if>
              </xsl:for-each>                           
            </td>
          </tr>          
        </table> 
        
        <!-- HOLDING ENTITY INFORMATION - EDIT TABLE -->
        <table id="holdingEntityInfo_modifyDescriptionTable">
          <xsl:attribute name="style">
                display:none; width:95%; position:relative; top:5; z-index:20;   
          </xsl:attribute>
         
          <tr>
            <td style="width:180;" align="right"> Entity Code: </td>
            <td style="verticalAlign:top;">
              <input id="holdingEntityInfo_EntityCodeFld">
                <xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/holdingEntityCode"/>
                </xsl:attribute>
              </input>
            </td>
          </tr>         
          <tr>
            <td style="width:180;" align="right">
              <span style="height:100%; verticalAlign:top;">Calculation Method:</span>
            </td>
            <td>
              <select id="holdingEntityInfo_CalcMethodFld">
                <xsl:apply-templates select="//List[@listName='MfCalMethods']"/>
              </select>
            </td>
          </tr>          
          <tr style="height:30">
            <td align="right" colspan="2">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <xsl:with-param name="id">saveDescBtn</xsl:with-param>
                <xsl:with-param name="onclick">saveEntityModify();</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">85</xsl:with-param>
                <xsl:with-param name="text">Save</xsl:with-param>
                <xsl:with-param name="color">green</xsl:with-param>
              </xsl:call-template>
              
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <xsl:with-param name="id">closeDescBtn</xsl:with-param>
                <xsl:with-param name="onclick">closeEntityModify();</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">85</xsl:with-param>
                <xsl:with-param name="text">Close</xsl:with-param>
                <xsl:with-param name="color">red</xsl:with-param>
              </xsl:call-template>
            </td>
          </tr>
        </table>
      </div>      
    </fieldset>
    
        
    
    <div id="grayDiv">
      <xsl:attribute name="style">
        <xsl:choose>
          <xsl:when test="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity">
            width:100%; height:118px; position:absolute; top:160; left:0; z-index:21; background:white; filter:alpha(opacity=50); display:none;       
          </xsl:when>
          <xsl:otherwise>
            width:100%; height:118px; position:absolute; top:160; left:0; z-index:21; background:white; filter:alpha(opacity=50); display:block;
          </xsl:otherwise>
        </xsl:choose>
      </xsl:attribute>
      .
      <!-- this is used to disable the rest of the screen, while holdingEntityInfo update is open --> 
    </div>
      
      
      <!-- Aggregation Div -->
    <fieldset id="aggregationFieldset">
		<xsl:attribute name="style">
			position:relative; top:0; left:10; width:900; display:block;
		    <xsl:if test="not(/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity)">
				display:none;
		    </xsl:if>
		</xsl:attribute>
      <legend style="cursor:pointer;" onclick='toggleDiv("aggregationDiv"); togglePlusMinus(this.firstChild.firstChild);'><font color="black"><img id="aggregationDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/><b> Management Fee Aggregation</b> </font></legend>
      
      <table><tr><td></td></tr></table>      
      
      <div id="aggregationDiv" style="display:none;">
		  <div style="width:98%; position:relative; top:-24" align="right">          
			  <div style="cursor:pointer; position:absolute; top:2; left:721; overflow:hidden; width:70; height:15;" align="center">
				  <xsl:call-template name="ColorButtonTmpl">
					  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
					  <xsl:with-param name="id">showAllAggregationDiv</xsl:with-param>
					  <xsl:with-param name="onclick">showAllAggregation(this);</xsl:with-param>
					  <xsl:with-param name="size">small</xsl:with-param>
					  <xsl:with-param name="width">70</xsl:with-param>
					  <xsl:with-param name="text">Show All</xsl:with-param>
					  <xsl:with-param name="color">orange</xsl:with-param>
				  </xsl:call-template>   	  
			  </div>
			  <div style="cursor:pointer; position:absolute; top:2; left:796; overflow:hidden; width:70; height:15;" align="center">
				  <xsl:call-template name="ColorButtonTmpl">
					  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
					  <xsl:with-param name="id">showAggHistoryBtn</xsl:with-param>
					  <xsl:with-param name="onclick">sendHistoryRequest( "feeAggregation" );</xsl:with-param>
					  <xsl:with-param name="size">small</xsl:with-param>
					  <xsl:with-param name="width">70</xsl:with-param>
					  <xsl:with-param name="text">History</xsl:with-param>
					  <xsl:with-param name="color">orange</xsl:with-param>
				  </xsl:call-template>   
			  </div>
		  </div>         
	  

        <div style="position:relative; top:0;"> 
          
          <!-- Accounts -->
          <div style="position:relative; left:20; width:200">
            <div style="cursor:pointer" onclick='toggleDiv("aggAccount_ListDiv"); togglePlusMinus(this.firstChild);'><img id="aggAccount_ListDivToggle" src="{$vURL}images/plus.png"  style="position:relative; top:2; left: 1; cursor:pointer"/> <b> Accounts </b></div>
          </div>
                    
          <div id="aggAccount_ListDiv" style="display:none">
            
            <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">
              <div style="width:98%; position:relative; top:-26" align="right"> 
                <div align="center"  style="cursor:pointer; position:absolute; top:10; left:201; width:70; height:15; overflow:hidden;">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">addAggregationAccountBtn</xsl:with-param>
                    <xsl:with-param name="onclick">openPopup( "aggAccount", true );</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Add</xsl:with-param>
                    <xsl:with-param name="color">green</xsl:with-param>
                  </xsl:call-template>            
                </div>
                <div style="cursor:pointer; position:absolute; top:10; left:275; width:70; height:15; overflow:hidden;" align="center">
              	<xsl:call-template name="ColorButtonTmpl">
              		<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              		<xsl:with-param name="id">modifyAggregationAccountBtn</xsl:with-param>              		
              		<xsl:with-param name="onclick">clickHandler_modifyAggAccountBtn()</xsl:with-param>
              		<xsl:with-param name="size">small</xsl:with-param>
              		<xsl:with-param name="width">70</xsl:with-param>
              		<xsl:with-param name="text">Modify</xsl:with-param>
              		<xsl:with-param name="color">orange</xsl:with-param>
              	</xsl:call-template>        
                </div>                            
                <div style="cursor:pointer; position:absolute; top:10; left:350; width:70; height:15; overflow:hidden;" align="center">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">deleteAggregationAccountBtn</xsl:with-param>                    
                    <xsl:with-param name="onclick">clickHandler_deleteAggAccountBtn()</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Delete</xsl:with-param>
                    <xsl:with-param name="color">red</xsl:with-param>
                  </xsl:call-template>        
                </div>              	
              </div>
            </xsl:if>
            <div id="aggAccount_ListContentsDiv">
              <xsl:call-template name="AggAccountListTmpl">
                <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/FeeAggregation/Accounts"/>
              </xsl:call-template>
            </div>
                        
          </div>

          
          <!-- Brokers -->         
          <div style="position:relative; left:20; width:200; padding-top:4px;">
            <div style="cursor:pointer;" onclick='toggleDiv("aggBroker_ListDiv"); togglePlusMinus(this.firstChild);'><img id="aggBroker_ListDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/> <b> Brokers</b></div>            
          </div>
          
          <div id="aggBroker_ListDiv" style="display:none">
            <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">
              <div style="width:98%; position:relative; top:-26" align="right"> 
                <div style="cursor:pointer; position:absolute; top:10; left:201; width:70; height:15; overflow:hidden;" align="center">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">addAggregationBrokerBtn</xsl:with-param>
                    <xsl:with-param name="onclick">openPopup( "aggBroker", true );</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Add</xsl:with-param>
                    <xsl:with-param name="color">green</xsl:with-param>
                  </xsl:call-template>   
                </div>
                <div style="cursor:pointer; position:absolute; top:10; left:275; width:70; height:15; overflow:hidden;" align="center">
              	<xsl:call-template name="ColorButtonTmpl">
	              	<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
	              	<xsl:with-param name="id">modifyAggregationBrokerBtn</xsl:with-param>	              	
              		<xsl:with-param name="onclick">clickHandler_modifyAggBrokerBtn()</xsl:with-param>
	              	<xsl:with-param name="size">small</xsl:with-param>
	              	<xsl:with-param name="width">70</xsl:with-param>
	              	<xsl:with-param name="text">Modify</xsl:with-param>
	              	<xsl:with-param name="color">orange</xsl:with-param>
              	</xsl:call-template>   
                </div>                              
                <div style="cursor:pointer; position:absolute; top:10; left:350; width:70; height:15; overflow:hidden;" align="center">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">deleteAggregationBrokerBtn</xsl:with-param>                    
                  	<xsl:with-param name="onclick">clickHandler_deleteAggBrokerBtn()</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Delete</xsl:with-param>
                    <xsl:with-param name="color">red</xsl:with-param>
                  </xsl:call-template>   
                </div>
              </div> 
            </xsl:if> 
            <div id="aggBroker_ListContentsDiv">
              <xsl:call-template name="AggBrokerListTmpl">              
                <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/FeeAggregation/Brokers"/>              
              </xsl:call-template>                
            </div>        
          </div>
          
          <!-- Sales Reps -->
          <div style="position:relative; left:20; width:200; padding-top:4px;">
            <div style="cursor:pointer;"  onclick='toggleDiv("aggSalesRep_ListDiv"); togglePlusMinus(this.firstChild);'><img id="aggSalesRep_ListDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/><b> Sales Reps</b> </div>
          </div>          
          <div id="aggSalesRep_ListDiv" style="display:none">
            <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">
              <div style="width:98%; position:relative; top:-26" align="right">
                <div style="cursor:pointer; position:absolute; top:10; left:201; width:70; height:15; overflow:hidden;" align="center">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">addAggregationSlsRepBtn</xsl:with-param>
                    <xsl:with-param name="onclick">openPopup( "aggSalesRep", true );</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Add</xsl:with-param>
                    <xsl:with-param name="color">green</xsl:with-param>
                  </xsl:call-template>   
                </div>
              	<div style="cursor:pointer; position:absolute; top:10; left:275; width:70; height:15; overflow:hidden;" align="center">
              	<xsl:call-template name="ColorButtonTmpl">
              		<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              		<xsl:with-param name="id">modifyAggregationSlsRepBtn</xsl:with-param>              			
              		<xsl:with-param name="onclick">clickHandler_modifyAggSalesRepBtn()</xsl:with-param>
              		<xsl:with-param name="size">small</xsl:with-param>
              		<xsl:with-param name="width">70</xsl:with-param>
              		<xsl:with-param name="text">Modify</xsl:with-param>
              		<xsl:with-param name="color">orange</xsl:with-param>
              	</xsl:call-template>
              	</div>                            
                <div style="cursor:pointer; position:absolute; top:10; left:350; width:70; height:15; overflow:hidden;" align="center">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">deleteAggregationSlsRepBtn</xsl:with-param>                    
                  	<xsl:with-param name="onclick">clickHandler_deleteAggSalesRepBtn()</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Delete</xsl:with-param>
                    <xsl:with-param name="color">red</xsl:with-param>
                  </xsl:call-template>
                </div>
              </div>   
            </xsl:if>
            <div id="aggSalesRep_ListContentsDiv">
              <xsl:call-template name="AggSalesRepListTmpl">              
                <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/FeeAggregation/SalesReps"/>              
              </xsl:call-template>
            </div>
            
          </div>  
                    
          
          <!-- SubAdvised Assets -->         
          <div style="position:relative; left:20; width:200; padding-top:4px;">
            <div style="cursor:pointer;" onclick='toggleDiv("aggAsset_ListDiv"); togglePlusMinus(this.firstChild);' ><img id="aggAsset_ListDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/><b> SubAdvised Assets </b></div>
          </div>
          
          <div id="aggAsset_ListDiv" style="display:none">
            <div style="width:98%; position:relative; top:-26" align="right">              
              <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">              
                <div style="cursor:pointer; position:absolute; top:10; left:201; width:70; height:15; overflow:hidden;" align="center">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">addAggregationAssetsBtn</xsl:with-param>
                    <xsl:with-param name="onclick">openPopup( "aggAsset", true );</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Add</xsl:with-param>
                    <xsl:with-param name="color">green</xsl:with-param>
                  </xsl:call-template>
                </div>
	          <div style="cursor:pointer; position:absolute; top:10; left:275; width:70; height:15; overflow:hidden;" align="center">
              	<xsl:call-template name="ColorButtonTmpl">
              		<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              		<xsl:with-param name="id">modifyAggregationAssetsBtn</xsl:with-param>              		
              		<xsl:with-param name="onclick">clickHandler_modifyAggAssetBtn()</xsl:with-param>
              		<xsl:with-param name="size">small</xsl:with-param>              		
              		<xsl:with-param name="width">70</xsl:with-param>
              		<xsl:with-param name="text">Modify</xsl:with-param>
              		<xsl:with-param name="color">orange</xsl:with-param>
              	</xsl:call-template>
	          </div>                         
                <div style="cursor:pointer; position:absolute; top:10; left:350; width:70; height:15; overflow:hidden;" align="center">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">deleteAggregationAssetsBtn</xsl:with-param>                    
                  	<xsl:with-param name="onclick">clickHandler_deleteAggAssetBtn()</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">70</xsl:with-param>
                    <xsl:with-param name="text">Delete</xsl:with-param>
                    <xsl:with-param name="color">red</xsl:with-param>
                  </xsl:call-template>
                </div>
              </xsl:if>
            	<div style="cursor:pointer; position:absolute; top:10; left:425; width:70; height:15; overflow:hidden;" align="center">
            		<xsl:call-template name="ColorButtonTmpl">
            			<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
            			<xsl:with-param name="id">valuesAggregationAssetsBtn</xsl:with-param>
            			<xsl:with-param name="onclick">launchAssetValuesScreen();</xsl:with-param>
            			<xsl:with-param name="size">small</xsl:with-param>
            			<xsl:with-param name="width">70</xsl:with-param>
            			<xsl:with-param name="text">Values</xsl:with-param>
            			<xsl:with-param name="color">orange</xsl:with-param>
            		</xsl:call-template>
            	</div>
            </div>    
            <div id="aggAsset_ListContentsDiv">
              <xsl:call-template name="AggAssetListTmpl">              
                <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/FeeAggregation/SubAdvisedAssets"/>              
              </xsl:call-template>
            </div>
             
          </div>
        </div>
      </div>
    </fieldset>
     
    <!-- Fee ID Div -->
    <fieldset id="feeIDFieldSet">
      <xsl:attribute name="style">
		   position:relative; left:10; top:0; width:900; display:block;
			<xsl:if test="not(/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity)">
				display:none;
		    </xsl:if>
      </xsl:attribute>
      <legend style="cursor:pointer" onclick='toggleDiv("feeIDDiv"); togglePlusMinus(this.firstChild.firstChild);' ><font color="black"><img id="feeIDDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/><b> Management Fee IDs</b> </font></legend>
      <table><tr><td></td></tr></table>
      
      <div id="feeIDDiv" style="display:none;">
        <div style="width:98%; position:relative; top:-24" align="right">          
          <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">
            <div style="cursor:pointer; position:absolute; top:2; left:651; overflow:hidden; width:70; height:15;" align="center">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <xsl:with-param name="id">addFeeIdBtn</xsl:with-param>
                <xsl:with-param name="onclick">launchFeeIDScreen()</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">70</xsl:with-param>
                <xsl:with-param name="text">Add</xsl:with-param>
                <xsl:with-param name="color">green</xsl:with-param>
              </xsl:call-template>
            </div>
          </xsl:if>
          <div style="cursor:pointer; position:absolute; top:2; left:725; width:70; height:15; overflow:hidden;" align="center"> 
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">feeIdDetailsBtn</xsl:with-param>
              <xsl:with-param name="onclick">
                if ( _selectedRowMap["feeID"] )
                  launchFeeIDScreen( _selectedRowMap["feeID"].feeModelCode );
                else
                  alert( "Please select a record" );
              </xsl:with-param>
              <xsl:with-param name="size">small</xsl:with-param>
              <xsl:with-param name="width">70</xsl:with-param>
              <xsl:with-param name="text">Details</xsl:with-param>
              <xsl:with-param name="color">orange</xsl:with-param>
            </xsl:call-template>
            <input type="hidden" id="btnLaunch" 
            desktopORGID="BPROC_MANAGEMENT_FEE_ID"
            desktopBrowserTitle="Management Fee ID"                           
            desktopfeeModelCode="">
              <xsl:attribute name="desktopholdingEntityID"><xsl:value-of select="/websrvXML/FormInformation/EntityID"/></xsl:attribute>
            </input>
          </div>
          <div style="cursor:pointer; position:absolute; top:2; left:799; overflow:hidden; width:70; height:15;" align="center">
        		<xsl:call-template name="ColorButtonTmpl">
        			<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
        			<xsl:with-param name="id">feeIDHistoryBtn</xsl:with-param>
        			<xsl:with-param name="onclick">sendHistoryRequest( "FeeID" );</xsl:with-param>
        			<xsl:with-param name="size">small</xsl:with-param>
        			<xsl:with-param name="width">70</xsl:with-param>
        			<xsl:with-param name="text">History</xsl:with-param>
        			<xsl:with-param name="color">orange</xsl:with-param>
        		</xsl:call-template>
           </div>            
        </div>
        <div id="feeID_ListDiv">
          <div id="feeID_ListContentsDiv">
            <xsl:call-template name="FeeIDListTmpl">              
              <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/FeeIDs"/>              
            </xsl:call-template>          
          </div>
        </div>
      </div>
    </fieldset>    
    
    <!-- Invoice IDs Div -->
    <fieldset id="invoiceIDFieldSet">
    <xsl:attribute name="style">
        position:relative; left:10; top:0; width:900; display:block;
        <xsl:if test="not(/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity)">
				display:none;
		    </xsl:if>
    </xsl:attribute>

      <legend style="cursor:pointer" onclick='toggleDiv("invoiceIDDiv"); togglePlusMinus(this.firstChild.firstChild);' ><font color="black"><img id="invoiceIDDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/><b> Management Fee Invoice IDs</b> </font></legend>
      <table><tr><td></td></tr></table>
      
      <div id="invoiceIDDiv" style="display:none;">
        <div style="width:98%; position:relative; top:-24" align="right">          
          <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">
            <div style="cursor:pointer; position:absolute; top:2; left:651; overflow:hidden; width:70; height:15;" align="center">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <xsl:with-param name="id">addInvoiceIdBtn</xsl:with-param>
                <xsl:with-param name="onclick">launchInvoiceIDScreen();</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">70</xsl:with-param>
                <xsl:with-param name="text">Add</xsl:with-param>
                <xsl:with-param name="color">green</xsl:with-param>
              </xsl:call-template>
            </div>  
          </xsl:if>  
          <div style="cursor:pointer; position:absolute; top:2; left:725; width:70; height:15; overflow:hidden;" align="center">            
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">invoiceIdDetailsBtn</xsl:with-param>
              <xsl:with-param name="onclick">
                if ( _selectedRowMap["invoiceID"] )
                launchInvoiceIDScreen( _selectedRowMap["invoiceID"].invIDCode, _selectedRowMap["invoiceID"].billInstrID );
                else
                  alert( "Please select a record" );
              </xsl:with-param>
              <xsl:with-param name="size">small</xsl:with-param>
              <xsl:with-param name="width">70</xsl:with-param>
              <xsl:with-param name="text">Details</xsl:with-param>
              <xsl:with-param name="color">orange</xsl:with-param>
            </xsl:call-template>
          </div>   
          <div style="cursor:pointer; position:absolute; top:2; left:799; width:70; height:15; overflow:hidden;" align="center">            
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">invoiceHistoryBtn</xsl:with-param>
              <xsl:with-param name="onclick">sendHistoryRequest( "Invoice" );</xsl:with-param>
              <xsl:with-param name="size">small</xsl:with-param>
              <xsl:with-param name="width">70</xsl:with-param>
              <xsl:with-param name="text">History</xsl:with-param>
              <xsl:with-param name="color">orange</xsl:with-param>
            </xsl:call-template>
          </div>       
        </div>
        <div id="invoiceID_ListDiv">
          <div id="invoiceID_ListContentsDiv">
            <xsl:call-template name="InvoiceIDListTmpl">              
              <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/InvoiceIDs"/>              
            </xsl:call-template>
          </div>
        </div>
      </div>
    </fieldset>          
    
    <!-- Accounts Div -->
    <fieldset id="accountFieldSet">
		<xsl:attribute name="style">
			 position:relative; left:10; top:0; width:900; display:block;
			 <xsl:if test="not(/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity)">
				display:none;
		    </xsl:if>
		</xsl:attribute>
      <legend style="cursor:pointer" onclick='toggleDiv("accountsDiv"); togglePlusMinus(this.firstChild.firstChild);' ><font color="black"><img id="accountsDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2;cursor:pointer"/><b> Management Fee Accounts </b> </font></legend>
      <table><tr><td></td></tr></table>

      <div id="accountsDiv" style="display:none;">
        <div style="width:98%; position:relative; top:-24" align="right"> 
        
          <xsl:if test="/websrvXML/dtHoldingEntityMFInitResponse/allowUpdates='yes'">
            <div style="cursor:pointer; position:absolute; top:2; left:651; overflow:hidden; width:70; height:15;" align="center">
              <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">addAccountBtn</xsl:with-param>
              <xsl:with-param name="onclick">openPopup( "account", true );</xsl:with-param>
              <xsl:with-param name="size">small</xsl:with-param>
              <xsl:with-param name="width">70</xsl:with-param>
              <xsl:with-param name="text">Add</xsl:with-param>
              <xsl:with-param name="color">green</xsl:with-param>
              </xsl:call-template>
            </div>
          </xsl:if>
          
          <div style="cursor:pointer; position:absolute; top:2; left:726; width:70; height:15; overflow:hidden;" align="center">
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">accountDetailsBtn</xsl:with-param>
              <xsl:with-param name="onclick">                
                if ( _selectedRowMap["account"] )
                {
                  openPopup( "account", false );
                }
                else
                {
                  alert( "Please select a record" );
                }
              </xsl:with-param>
              <xsl:with-param name="size">small</xsl:with-param>
              <xsl:with-param name="width">70</xsl:with-param>
              <xsl:with-param name="text">Details</xsl:with-param>
              <xsl:with-param name="color">orange</xsl:with-param>
            </xsl:call-template>
          </div>
          <div style="cursor:pointer; position:absolute; top:2; left:799; overflow:hidden; width:70; height:15;" align="center">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <xsl:with-param name="id">accountHistoryBtn</xsl:with-param>
                <xsl:with-param name="onclick">sendHistoryRequest( "MFaccounts" );</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">70</xsl:with-param>
                <xsl:with-param name="text">History</xsl:with-param>
                <xsl:with-param name="color">orange</xsl:with-param>
              </xsl:call-template>
          </div>                    
          
        </div>
        <div id="account_ListDiv">
          <div id="account_ListContentsDiv">
            <xsl:call-template name="AccountListTmpl">              
              <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFInitResponse/HoldingEntity/Accounts"/>              
            </xsl:call-template>
          </div>
        </div>
      </div>
    </fieldset>
        
    <div style="cursor:pointer; position:relative; width:100; left:650; top:25; height:50;" align="center">
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
    <div id="disableDiv" style="position:absolute; top:0; left; 0; z-index:0; width:100%; height:100%; background:e6e6e6; filter:alpha(opacity=70); display:none;">
    </div>
    
    
    <!-- POPUP DIVS -->
    
    <!-- Aggregation Account Add Div -->
    <div id="aggAccount_PopupDiv" style="verticalAlign:middle; position:absolute; left:110; top:100; width:600; height:155; background:white; display:none">
    	<input type="hidden" id="aggAccount_UpdTypeFld"/>
    	<input type="hidden" id="aggAccount_FeeAggrIdFld"/>
    	<input type="hidden" id="aggAccount_VersionFld"/>
      <fieldset style=" border: 3px solid gray; width:100%; height:100%; ">      
        <table align="center" style="width:95%; left:-5; position:relative; top:5;" >
          <tr>
            <td align="right" style="width:120">              
              Account:
            </td>
            <td style="width:400; padding-bottom:10px">               
              <!-- account suggestfield -->
              <input suggestField="true"
                class="DataInput" 
                type="text" 
                id="aggAccount_AccountFld"
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
            <td>
              <span style="position:relative; top:-4px">
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
          	<td align="right" style="width:110">              
          		Effective Date:
          	</td>
          	<td style="width:150; padding-bottom:10px" colspan="2">               
          		<input id="aggAccount_EffDateFld" type="text" style="width:150" class="dstdatepicker">
          			<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
          		</input>
          	</td>
          </tr>
          <tr>
        	<td align="right" style="width:110">              
        		Stop Date:
        	</td>
        	<td style="width:150; padding-bottom:10px" colspan="2">               
        		<input id="aggAccount_StopDateFld" type="text" style="width:150" class="dstdatepicker">
        			<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        		</input>
        	</td>
          </tr>                          
          <tr>
            <td colspan="3" style="position:relative; text-align:center">
              <span style="padding-right:5px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                  <xsl:with-param name="onclick">saveAggAccount();</xsl:with-param>                
                  <xsl:with-param name="id">aggAccount_SaveBtn</xsl:with-param>                  
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Save</xsl:with-param>
                  <xsl:with-param name="color">green</xsl:with-param>
                </xsl:call-template>
              </span>              
              <span>
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="onclick">closePopup( "aggAccount" );</xsl:with-param>
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Cancel</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                        
            </td>
          </tr>         
        </table>
       
      </fieldset>
    </div>

    <!-- Aggregation Broker Add Div -->
    <div id="aggBroker_PopupDiv" style="verticalAlign:middle; position:absolute; left:110; top:100; width:600; height:160; background:white; display:none">
    	<input type="hidden" id="aggBroker_UpdTypeFld"/>
    	<input type="hidden" id="aggBroker_FeeAggrIdFld"/>
    	<input type="hidden" id="aggBroker_VersionFld"/>
      <fieldset style=" border: 3px solid gray; width:100%; height:100%; ">      
        <table align="center" style="width:93%; position:relative; top:10;" >
          <tr>
            <td align="right" style="width:120">     
              Broker:
            </td>
            <td style="width:400; padding-bottom:10px">    
              <!-- broker suggestfield -->
              <input suggestField="true"
                class="DataInput" 
                type="text" 
                id="aggBroker_BrokerFld"  
                style="width:100%"                            
                dropdownClass="Dropdown" 
                contentClass="DropdownContent"
                highlightClass="DropdownHighlight" 
                displayItems="displayValue"
                searchURLGenerator="getBrokerSearchURL"
                initialValue=""
              />          
            </td>
            <td>
              <span style="position:relative; top:-4px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                  <xsl:with-param name="onclick">alertBrokerSuggestOptions();</xsl:with-param>                                                    
                  <xsl:with-param name="size">small</xsl:with-param>
                  <xsl:with-param name="width">70</xsl:with-param>
                  <xsl:with-param name="text">Options</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                     
            </td>
          </tr>
        	<tr>
        		<td align="right" style="width:110">              
        			Effective Date:
        		</td>
        		<td style="width:150; padding-bottom:10px" colspan="2">               
        			<input id="aggBroker_EffDateFld" type="text" style="width:150" class="dstdatepicker">
        				<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        			</input>
        		</td>
        	</tr>
        	<tr>
        		<td align="right" style="width:110">              
        			Stop Date:
        		</td>
        		<td style="width:150; padding-bottom:10px" colspan="2">               
        			<input id="aggBroker_StopDateFld" type="text" style="width:150" class="dstdatepicker">
        				<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        			</input>
        		</td>
        	</tr>                                    
          <tr>
            <td colspan="3" style="position:relative; text-align:center">
              <span style="padding-right:5px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="id">aggBroker_SaveBtn</xsl:with-param>
                  <xsl:with-param name="onclick">saveAggBroker();</xsl:with-param>                  
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Save</xsl:with-param>
                  <xsl:with-param name="color">green</xsl:with-param>
                </xsl:call-template>
              </span>              
              <span>
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="onclick">closePopup( "aggBroker" );</xsl:with-param>
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Cancel</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                        
            </td>
          </tr>
        </table>      
      </fieldset>
    </div>
    
    <!-- Aggregation SalesRep Add Div -->
    <div id="aggSalesRep_PopupDiv" style="verticalAlign:middle; position:absolute; left:110; top:100; width:620; height:200; background:white; display:none">
    	<input type="hidden" id="aggSalesRep_UpdTypeFld"/>
    	<input type="hidden" id="aggSalesRep_FeeAggrIdFld"/>
    	<input type="hidden" id="aggSalesRep_VersionFld"/>
      <fieldset style=" border: 3px solid gray; width:100%; height:100%; ">      
        <table align="center" style="width:95%; position:relative; top:10;" >
          
          <tr>
            <td align="right" style="width:120">
              Broker:
            </td>    
            <td style="width:400; padding-bottom:10px"> 
              <!-- broker suggestfield -->
              <input suggestField="true"
                class="DataInput" 
                type="text" 
                id="aggSalesRep_BrokerFld"  
                style="width:100%"                            
                dropdownClass="Dropdown" 
                contentClass="DropdownContent"
                highlightClass="DropdownHighlight" 
                displayItems="displayValue"
                searchURLGenerator="getBrokerSearchURL"
                initialValue=""                
                />
            </td>
            <td>
              <span style="position:relative; top:-4px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                  <xsl:with-param name="onclick">alertBrokerSuggestOptions();</xsl:with-param>                                                     
                  <xsl:with-param name="size">small</xsl:with-param>
                  <xsl:with-param name="width">70</xsl:with-param>
                  <xsl:with-param name="text">Options</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                     
            </td>
          </tr>          
          <tr>
            <td align="right" style="width:120">
              Sales Rep:
            </td>
            <td style="width:400; padding-bottom:10px"> 
              <!-- sales rep suggestfield -->
              <input suggestField="true"
                class="DataInput" 
                type="text" 
                id="aggSalesRep_SalesRepFld"  
                style="width:100%"                            
                dropdownClass="Dropdown" 
                contentClass="DropdownContent"
                highlightClass="DropdownHighlight" 
                displayItems="displayValue"
                searchURLGenerator="getSalesRepSearchURL"
                initialValue="">
                  <xsl:attribute name="onfocus">
                    if ( !UTL.getElem( "aggSalesRep_BrokerFld" )._suggestDataObj )
                    {
                      this.blur();
                    }                    
                  </xsl:attribute>
              </input>                               
            </td>          	                    
            <td>
              <span style="position:relative; top:-4px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                  <xsl:with-param name="onclick">alertSalesRepSuggestOptions();</xsl:with-param>                                                       
                  <xsl:with-param name="size">small</xsl:with-param>
                  <xsl:with-param name="width">70</xsl:with-param>
                  <xsl:with-param name="text">Options</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                     
            </td>
          </tr>
        	<tr>
        		<td align="right" style="width:120">              
        			Effective Date:
        		</td>
        		<td style="width:150; padding-bottom:10px" colspan="2">               
        			<input id="aggSalesRep_EffDateFld" type="text" style="width:150" class="dstdatepicker">
        				<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        			</input>
        		</td>
        	</tr>
        	<tr>
        		<td align="right" style="width:120">              
        			Stop Date:
        		</td>
        		<td style="width:150; padding-bottom:10px" colspan="2">               
        			<input id="aggSalesRep_StopDateFld" type="text" style="width:150" class="dstdatepicker">
        				<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        			</input>
        		</td>
        	</tr>               
          <tr>
            <td colspan="3" style="position:relative; text-align:center">
              <span style="padding-right:5px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="id">aggSalesRep_SaveBtn</xsl:with-param>
                  <xsl:with-param name="onclick">saveAggSalesRep();</xsl:with-param>                  
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Save</xsl:with-param>
                  <xsl:with-param name="color">green</xsl:with-param>
                </xsl:call-template>
              </span>              
              <span>
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="onclick">closePopup( "aggSalesRep" );</xsl:with-param>
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Cancel</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                        
            </td>
          </tr>
        </table>      
      </fieldset>
    </div>
    
    <!-- Aggregation Asset Add Div -->
    <div id="aggAsset_PopupDiv" style="verticalAlign:middle; position:absolute; top:100; left:210; width:400; height:160; background:white; display:none">
    	<input type="hidden" id="aggAsset_UpdTypeFld"/>
    	<input type="hidden" id="aggAsset_FeeAggrIdFld"/>
    	<input type="hidden" id="aggAsset_VersionFld"/>
      <fieldset style=" border: 3px solid gray; width:100%; height:100%; ">      
        <table align="center" style="width:90%; position:relative; top:10;" >
          <tr>
            <td align="right" style="width:110px;">
              Asset:
            </td>
            <td style="width:180; padding-bottom:10">
              <select id="aggAsset_AssetFld" style="width:100%">
                <xsl:apply-templates select="//List[@listName='SubAdvisedAssets']"/>
              </select>
            </td>
          </tr>
        	<tr>
        		<td align="right" style="width:110">              
        			Effective Date:
        		</td>
        		<td style="width:150; padding-bottom:10px" colspan="2">               
        			<input id="aggAsset_EffDateFld" type="text" style="width:150" class="dstdatepicker">
        				<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        			</input>
        		</td>
        	</tr>
        	<tr>
        		<td align="right" style="width:110">              
        			Stop Date:
        		</td>
        		<td style="width:150; padding-bottom:10px" colspan="2">               
        			<input id="aggAsset_StopDateFld" type="text" style="width:150" class="dstdatepicker">
        				<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        			</input>
        		</td>
        	</tr>                          
          <tr>
            <td colspan="2" style="position:relative; width:100%; text-align:center">
              <span style="padding-right:5px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="id">aggAsset_SaveBtn</xsl:with-param>
                  <xsl:with-param name="onclick">saveAggAsset();</xsl:with-param>
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Save</xsl:with-param>
                  <xsl:with-param name="color">green</xsl:with-param>
                </xsl:call-template>
              </span>              
              <span>
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="onclick">closePopup( "aggAsset" );</xsl:with-param>
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Cancel</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                     
            </td>
          </tr>
        </table>      
      </fieldset>
    </div>
        
    <!-- Account Add Div -->
    <div id="account_PopupDiv" style="verticalAlign:middle; position:absolute; left:130; top:100; width:706; height:225; background:white; display:none; overflow:hidden;">
      <fieldset style=" border: 3px solid gray; width:700; height:100%; ">
            
        <div id="actionsDiv" style="width:700; padding-top:5px; visibility:hidden; text-align:center;">         
          <span style="position:relative; width:60;">Action:</span>          
          <span style=" position:relative; top:-2;">
            <select id="accountActionSelect" onchange="handleAccountActionSelectChange()" style="width:190; position:relative; zoom:100%">
              <option></option>
              <xsl:apply-templates select="//List[@listName='AccountActions']"/>          
            </select>   
          </span>
        </div>    
        
        <input type="hidden" id="account_VersionFld"/>
        <input type="hidden" id="account_ShrAcctIDFld"/>
        <input type="hidden" id="account_GBCDFld"/>
        <table align="center" style="width:700; position:relative; top:0; padding-top:5px">
          <tr>
            <td style="width:100px; padding-left:10px">
              Account:
            </td>
            <td style="width:500">               
              <!-- account suggestfield -->
              <input suggestField="true"
                class="DataInput" 
                type="text" 
                id="account_AccountFld"
                style="width:500px;"                              
                dropdownClass="Dropdown" 
                contentClass="DropdownContent"
                highlightClass="DropdownHighlight" 
                displayItems="displayValue"                
                searchURLGenerator="getAccountSearchURL"
                initialValue=""
                detailsDisplayElement="accountSuggestDetailsDiv"
              />
            </td>
            <td style="width:100px;">
              <span style="position:relative; top:0px">
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
            <td style="width:100px; padding-left:10px">
              Eff Date:
            </td>
            <td colspan="2" style="width:400px">
                <span style="width:200">
					<input id="account_EffDateFld" type="text" style="width:200" class="dstdatepicker">
						<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
					</input>
                </span>				
            </td>
          </tr>
        	<tr>
        		<td style="width:100px; padding-left:10px">
        			Stop Date:
        		</td>
        		<td colspan="2" style="width:400px">
        			<span style="width:200">
        				<input id="account_StopDateFld" type="text" style="width:200" class="dstdatepicker">
        					<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
        				</input>
        			</span>				
        		</td>
        	</tr>                   
          <tr>
            <td style="width:100px; padding-left:10px"> 
              Fee ID:
            </td>
            <td colspan="2" style="width:400px">
              <select id="account_FeeIDFld" style="width:200"></select>
            </td>
          </tr>
          <tr>
            <td style="width:100px; padding-left:10px">
              Invoice ID:
            </td>
            <td colspan="2" style="width:400px">
              <select id="account_InvoiceIDFld" style="width:200"></select>
            </td>
          </tr>          
          <tr>
            <td colspan="3" style="position:relative; text-align:center; z-index:30; padding-top:20px">
              <span style="padding-right:5px">
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="id">account_SaveBtn</xsl:with-param>                  
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Save</xsl:with-param>
                  <xsl:with-param name="color">green</xsl:with-param>
                </xsl:call-template>
              </span>              
              <span>
                <xsl:call-template name="ColorButtonTmpl">
                  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                  <xsl:with-param name="onclick">closePopup( "account" );</xsl:with-param>
                  <xsl:with-param name="size">large</xsl:with-param>
                  <xsl:with-param name="width">100</xsl:with-param>
                  <xsl:with-param name="text">Cancel</xsl:with-param>
                  <xsl:with-param name="color">orange</xsl:with-param>
                </xsl:call-template>
              </span>                       
            </td>
          </tr>
        </table>      
      </fieldset>
    </div>
    
    
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
    
     
    <iframe id="invoiceID_Frame"             
            style="position:absolute; top:40px; left:200px; width:525; height:670; background:white; display:none; overflow:visible; border:2px solid gray">
      <xsl:attribute name="src">
        javascript: "Loading ..."
      </xsl:attribute>
    </iframe>
    
    <iframe id="feeID_Frame"             
      style="position:absolute; top:40px; left:30px; width:800; height:650; background:white; display:none; overflow:visible; border:2px solid gray">
      <xsl:attribute name="src">
        javascript: "Loading ..."
      </xsl:attribute>
    </iframe>
    
    
    <iframe id="assetValues_Frame"        
            style="position:absolute; top:75px; left:150px; width:320; height:430; background:white; display:none; overflow:visible; border:2px solid gray">
      <xsl:attribute name="src">
        javascript: "Loading ..."
      </xsl:attribute>
    </iframe>
    
    
    <iframe id="historyIframe"             
		style="position:absolute; top:50px; left:120px; width:600; height:525; background:white; display:none; overflow:visible; border:none" frameborder="0">
		<xsl:attribute name="src">
			javascript: "Loading ..."
		</xsl:attribute>
	</iframe>
	 <div id="historyDiv" style="background:white; position:absolute; top:50; left:120; width:600; height:525; border:3px solid gray; text-align:center; padding-top:5px; display:none;">
	     <input id="historyTypeFld" type="text" style="display:none"/>
		 <div style="height:25; text-align:left; width:100%; padding-left:40px; padding-bottom:5px">			 
			 <span style="width:200">
				 <span style="position:relative; top: -8; width:80">Start Date:</span>
				 <span style="width:100">
					 <input id="historyFilter_startDateFld" type="text" class="dstdatepicker">
						<xsl:attribute name="dateformat">
						  <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
						</xsl:attribute>
					  </input>
				  </span>
			 </span>			 			 
			 <span style="width:200">
				 <span style="position:relative; top: -8; width:80">End Date:</span>
				 <span style="width:100">
					 <input id="historyFilter_endDateFld" type="text" class="dstdatepicker">
						<xsl:attribute name="dateformat">
						  <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
						</xsl:attribute>
					  </input>
				  </span>
			 </span>
			 <span style="position:relative; top:-8">
				 <xsl:call-template name="ColorButtonTmpl">
					  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
					  <xsl:with-param name="id">filterHistoryBtn</xsl:with-param>
					  <xsl:with-param name="onclick">filterHistory()</xsl:with-param>
					  <xsl:with-param name="size">small</xsl:with-param>
					  <xsl:with-param name="width">80</xsl:with-param>
					  <xsl:with-param name="text">Filter</xsl:with-param>
					  <xsl:with-param name="color">orange</xsl:with-param>
					</xsl:call-template>			 			 
				</span>
		 </div>
		 <div id="historyContents" style="height:445; border:1px solid black; overflow-Y:scroll; text-align:left; width:570">		 			 		 
		 </div>
			<div style="position:relative; top:10">
				<xsl:call-template name="ColorButtonTmpl">
				  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
				  <xsl:with-param name="id">closeHistoryBtn</xsl:with-param>
				  <xsl:with-param name="onclick">closeHistoryPopup()</xsl:with-param>
				  <xsl:with-param name="size">large</xsl:with-param>
				  <xsl:with-param name="width">100</xsl:with-param>
				  <xsl:with-param name="text">Close</xsl:with-param>
				  <xsl:with-param name="color">orange</xsl:with-param>
				</xsl:call-template>
			</div>
	</div>    
	
	
    <div id="refreshIndicatorDiv" style="position:absolute; border:2px solid grey; width:200; height:50; top:100; left:225; background:white; z-index:50; padding-top:10px; display:none">
		<span style="width:100%; text-align:center; font-size:15px; font-style:italic">Refreshing ...</span>
	</div>   

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
