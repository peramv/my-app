<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include 
    href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>
  <xsl:include 
    href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/DST_WebBehavioursTemplate.xsl"/>
    
  <xsl:variable name="vClient"       		select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      	select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          	select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"           		select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           		select="/websrvXML/FormInformation/cz"/>          
  <xsl:variable name="vTIDX"        		select="/websrvXML/FormInformation/tidx"/>
    
  <xsl:template match="/">
    
    <Screen>
      
      <!-- 
        This xsl loads up the screen that is loaded inside the iFrame when
        a user presses the Add Control button. 
      -->    
      
      <html>
        <xsl:call-template name="tmplBehaviours"/>
        
        <title>Invoice ID: <xsl:value-of select="//FormInformation/invoiceID"/></title>
        
        <head>
          
          <!-- web library js code -->
          <script src="{$vURL}WebLibrary/JSLib/Cookie.js"/>
          <script src="{$vURL}WebLibrary/JSLib/Err.js"/>
          <script src="{$vURL}WebLibrary/JSLib/JSXML.js"/>
          <script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
          <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
          <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
          <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
          <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
          <script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>

          <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"><!-- comment --></link>
          <script src="{$vURL}javascript/ManagementFee_InvoiceIDMain.js">// comment. pls keep</script>    
          <script src="{$vURL}javascript/Cookie.js">// comment. pls keep</script>
          
          
          
          <style>
            
          </style>
          <xsl:call-template name="DST_WebBehavioursTmpl"/>
        </head>
        
        <body bgcolor="white" onload="onLoad()">
          
          <xsl:call-template name="tmplForm"/>
        </body>
        
      </html>
    </Screen>
    
  </xsl:template>
  
  <!-- ======================================================================= -->
  <xsl:template name="tmplForm">
    
    <xsl:if test="/websrvXML/responseContents/error">
      <script>alert('<xsl:value-of select="/websrvXML/responseContents/error"/>');</script>
    </xsl:if>

    <br></br>
    
    <div id="actionDiv" align="center" style="position:relative; width:500; top:-8; left:-10;">
      <span style="position:relative; width:60;">Action:</span>
      <span style=" position:relative; top:-2;">
        <select id="actionSelect" onchange="handleInvoiceActionChange()" style="width:200; position:relative; zoom:100%">
          <option></option>
          <xsl:apply-templates select="//List[@listName='InvoiceIDActions']"/>          
        </select>   
      </span>
      
      <span style="width:50; position:relative; top:-2;">
        <xsl:call-template name="ColorButtonTmpl">
          <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
          <xsl:with-param name="id"></xsl:with-param>
          <xsl:with-param name="onclick">handleInvoiceActionChange()</xsl:with-param>
          <xsl:with-param name="size">small</xsl:with-param>
          <xsl:with-param name="width">40</xsl:with-param>
          <xsl:with-param name="text">Go</xsl:with-param>
          <xsl:with-param name="color">green</xsl:with-param>
        </xsl:call-template>
      </span>
    </div>
    
    <input type="hidden" id="version">
      <xsl:attribute name="value">
        <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/version"/>
      </xsl:attribute>
    </input>    
    
    <input type="hidden" id="holdingEntityID">
      <xsl:attribute name="value">
        <xsl:value-of select="/websrvXML/FormInformation/holdingEntityID"/>
      </xsl:attribute>
    </input>
    
    <input type="hidden" id="billInstrID">
      <xsl:attribute name="value">
        <xsl:value-of select="/websrvXML/FormInformation/billInstrID"/>
      </xsl:attribute>
    </input>        
    
  	<input type="hidden" id="gbcd">
  		<xsl:attribute name="value">
  			<xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/gbcd"/>
  		</xsl:attribute>
  	</input>        
    
    <!-- Top Fee ID Div -->
    <div style="position:relative; top:-5  ;">
      <fieldset style="position:relative; left:-5; left:10; top:0; width:450; display:block;">
        <legend>
          <font color="black">
            <b> Invoice Information </b>
          </font>
        </legend>
        
        <!--<span style="cursor:pointer; position:absolute; left: 283; top:0; width:70; height:15; overflow:hidden;"
          align="center">
          <xsl:call-template name="ColorButtonTmpl">
            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
            <xsl:with-param name="id">modifyInvoiceID</xsl:with-param>
            <xsl:with-param name="onclick">modifyInvoiceID()</xsl:with-param>
            <xsl:with-param name="size">small</xsl:with-param>
            <xsl:with-param name="width">70</xsl:with-param>
            <xsl:with-param name="text">Modify</xsl:with-param>
            <xsl:with-param name="color">orange</xsl:with-param>
          </xsl:call-template>
        </span>
        
        <span style="cursor:pointer; position:absolute; left: 363; top:0; width:70; height:15; overflow:hidden;"
          align="center">
          <xsl:call-template name="ColorButtonTmpl">
            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
            <xsl:with-param name="id">deleteInvoiceID</xsl:with-param>
            <xsl:with-param name="onclick">deleteInvoiceID()</xsl:with-param>
            <xsl:with-param name="size">small</xsl:with-param>
            <xsl:with-param name="width">70</xsl:with-param>
            <xsl:with-param name="text">Delete</xsl:with-param>
            <xsl:with-param name="color">red</xsl:with-param>
          </xsl:call-template>
        </span>-->
        

        <!-- Top Fee ID Div -->
        <div style="position:relative; top:3; left:15;">
          
          <table style="width:90%; position:relative; top:-3;" id="invoiceTable">
            <tr>
              <td style="width:110;" align="right"> 
                Invoice ID: 
              </td>
              <td style="verticalAlign:top;">
                <input id="invoiceIDCode" style="width:100%" disabled="true">
                  <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                  <!--xsl:attribute name="value">
                    <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/invIDCode"/>  
                  </xsl:attribute-->                                    
                </input>
              </td>
            </tr>
            <tr>
              <td style="width:110;" align="right"> 
                Invoice Name: 
              </td>
              <td style="verticalAlign:top;">
                <input id="invoiceName" style="width:100%" disabled="true">
                  <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                  <!--xsl:attribute name="value">
                    <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/invoiceName"/>  
                  </xsl:attribute-->                                    
                </input>
              </td>
            </tr>
            <tr>
              <td style="width:110;" align="right"> Effective Date: </td>
              <td>
                <span style="width:120">
                  <input disabled="true" id="effectiveDate" class="dstdatepicker">
                    <xsl:attribute name="value">
                      <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/effDate"/>
                    </xsl:attribute>
                    <xsl:attribute name="dateformat">
                      <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                    </xsl:attribute>
                  </input>
                </span>
              </td>
            </tr>
            <tr>
              <td style="width:110;" align="right"> Stop Date: </td>
              <td>
                <span style="width:120">
                  <input disabled="true" id="stopDate" class="dstdatepicker">
                    <xsl:attribute name="value">
                      <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/stopDate"/>
                    </xsl:attribute>
                    <xsl:attribute name="dateformat">
                      <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                    </xsl:attribute>
                  </input>
                </span>
              </td>
            </tr>
          </table>          
        </div>
      </fieldset>
    </div>
    
    
    <!-- Billing Entity Div -->
    <fieldset style="position:relative; left:10; top:0; width:450; display:block;">
      <legend><font color="black"> <b>Billing Entity</b> </font></legend>
      <table><tr><td></td></tr></table>
      
      <div id="billingEntityDiv">
        
        <table style="width:100%;">          
          <tr>
            <td align="right">
              Delivery Name:
            </td>
            <td>
              <input disabled="true" id="delivName1" style="width:100%">
              <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/delivName1"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
          <tr>
            <td align="right">              
            </td>
            <td>
              <input disabled="true" id="delivName2" style="width:100%">
              <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/delivName2"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
          <tr>
            <td align="right" style="width:125;">
              Address:
            </td>
            <td>
              <input disabled="true" id="addrLine1" style="width:100%">
              <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine1"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
          <tr>
            <td>

            </td>
            <td>
              <input disabled="true" id="addrLine2" style="width:100%">
              <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine2"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
          <tr>
            <td>

            </td>
            <td>
              <input disabled="true" id="addrLine3" style="width:100%">
              <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine3"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
          <tr>
            <td>

            </td>
            <td>
              <input disabled="true" id="addrLine4" style="width:100%">
              <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine4"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
          <tr>
            <td align="right">
              City:
            </td>
            <td>
              <input disabled="true" id="city" style="width:100%">
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/city"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
          <tr>
            <td align="right">
              Province/Country:
            </td>
            <td>
              <select disabled="true" id="country" style="width:100%">
              <xsl:apply-templates select="//List[@listName='provCountries']">
                <xsl:with-param name="selected">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/ListSelection[@id='provCountries']"/>
                </xsl:with-param>
              </xsl:apply-templates>
              </select>   
            </td>
          </tr>
          <tr>
            <td align="right">
              Postal/Zip Code:
            </td>
            <td>
              <input disabled="true" id="pstl" style="width:90">
              <!-- text fld values are set by js function at onload - avoids XML entity issues -->
                <!--xsl:attribute name="value">
                  <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/pstl"/>
                </xsl:attribute-->
              </input>
            </td>
          </tr>
        </table>
      </div>
    </fieldset>
    
    <!-- Billing Details Div -->
    <fieldset style="position:relative; left:10; top:0; width:450; display:block;">
      <legend><font color="black"> <b>Billing Details</b> </font></legend>
      <table><tr><td></td></tr></table>
      
      <div id="billingDetailsDiv">
        
        <table style="width:100%;">
          <tr>
            <td align="right" style="width:110;">
              Frequency:
            </td>
            <td>
              <select disabled="true" id="frequency" style="width:100%">
                <xsl:apply-templates select="//List[@listName='frequencies']">
                  <xsl:with-param name="selected">
                    <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/ListSelection[@id='frequencies']"/>
                  </xsl:with-param>
                </xsl:apply-templates>
              </select>   
            </td>
          </tr>
          <tr>
            <td align="right" style="width:110;">
              Payment Option:
            </td>
            <td>
              <select disabled="true" id="chargeOption" style="width:100%">
                <xsl:apply-templates select="//List[@listName='chargeOptions']">
                  <xsl:with-param name="selected">
                    <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/ListSelection[@id='chargeOptions']"/>
                  </xsl:with-param>
                </xsl:apply-templates>
              </select>   
            </td>
          </tr>
          <tr>
            <td align="right" style="width:110;">
              GST Applies:
            </td>
            <td>
              <input disabled="true" id="gstApplies" type="checkbox" align="left">				 
                <xsl:if test="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/gstApplies='yes'">
                  <xsl:attribute name="checked">true</xsl:attribute>                                       
                </xsl:if>                                
              </input>
            </td>
          </tr>
          <tr>
            <td align="right" style="width:110;">
              Branding Type:
            </td>
            <td>
              <select disabled="true" id="brandingType" style="width:100%">
                <xsl:apply-templates select="//List[@listName='BrandingTypes']">
                  <xsl:with-param name="selected">
                    <xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/ListSelection[@id='BrandingTypes']"/>
                  </xsl:with-param>
                </xsl:apply-templates>
              </select>   
            </td>
          </tr>

        </table>
      </div>
    </fieldset>
    
    <div style="width:340; position:relative; left:120; top:10;">
      
      <div style="cursor:pointer; position:absolute;left:0; width:105; height:20;" align="center">
        <xsl:call-template name="ColorButtonTmpl">
          <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
          <xsl:with-param name="id"></xsl:with-param>
          <xsl:with-param name="onclick">             
            updateInvoiceID(); 
          </xsl:with-param>
          <xsl:with-param name="size">large</xsl:with-param>
          <xsl:with-param name="width">105</xsl:with-param>
          <xsl:with-param name="text">Save</xsl:with-param>
          <xsl:with-param name="color">green</xsl:with-param>
        </xsl:call-template>
      </div>

      <div style="cursor:pointer; position:absolute; left:113; width:105; height:20;" align="center">
        <xsl:call-template name="ColorButtonTmpl">
          <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
          <xsl:with-param name="id"></xsl:with-param>
          <xsl:with-param name="onclick">parent.closeInvoiceIDScreen( false );</xsl:with-param>
          <xsl:with-param name="size">large</xsl:with-param>
          <xsl:with-param name="width">105</xsl:with-param>
          <xsl:with-param name="text">Close</xsl:with-param>
          <xsl:with-param name="color">orange</xsl:with-param>
        </xsl:call-template>
      </div>

      <!--<img src="{$vURL}images/prototype/cancelButton.png" style="cursor:pointer" onmousedown='this.src=_vURL + "images/prototype/cancelButtonPressed.png";' onmouseup='this.src=_vURL + "images/prototype/cancelButton.png";'></img>-->
      <!--<img src="{$vURL}images/prototype/saveButton.png" style="cursor:pointer" onmousedown='this.src=_vURL + "images/prototype/saveButtonPressed.png";' onmouseup='this.src=_vURL + "images/prototype/saveButton.png";'></img>-->
    </div>
    
    <script>
      var _vURL = "<xsl:value-of select="$vURL"/>";
      var _vServletPath = "<xsl:value-of select="$vServletPath"/>";
      var _vCZ = "<xsl:value-of select="$vCZ"/>";
      var _companyCode = "<xsl:value-of select="//FormInformation/companyCode"/>";
      var _ruserId     = "<xsl:value-of select="//FormInformation/ruserId"/>";
      var _sessionId   = "<xsl:value-of select="//FormInformation/sessionId"/>";
      var _envName   = "<xsl:value-of select="//FormInformation/envName"/>";
      
      var _screenMode = "";
      var _dateFormat = "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
      
      var _allowUpdates = "<xsl:value-of select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/allowUpdates"/>";
      
      var _textFldValueMap = {};
      
      function onLoad()
      {
		  	
		 _textFldValueMap["invoiceIDCode"] 		= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val"  select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/invIDCode"/></xsl:call-template>" ); 
		 _textFldValueMap["invoiceName"] 		= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/invoiceName"/></xsl:call-template>" ); 
		 _textFldValueMap["delivName1"] 			= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/delivName1"/></xsl:call-template>" );
		 _textFldValueMap["delivName2"] 			= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/delivName2"/></xsl:call-template>" );  
		 _textFldValueMap["addrLine1"] 				= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine1"/></xsl:call-template>" ); 
		 _textFldValueMap["addrLine2"] 				= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine2"/></xsl:call-template>" ); 
 		 _textFldValueMap["addrLine3"] 				= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine3"/></xsl:call-template>" ); 
		 _textFldValueMap["addrLine4"] 				= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/addrLine4"/></xsl:call-template>" );  		 
		 _textFldValueMap["city"] 						= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/city"/></xsl:call-template>" ); 		 
		 _textFldValueMap["pstl"]		 				= unencode( "<xsl:call-template name="escapeQuotes"><xsl:with-param name="val" select="/websrvXML/dtInvoiceIDInitResponse/InvoiceID/pstl"/></xsl:call-template>" );
		 
		 setTextFldValues( _textFldValueMap );  		 
		  
        if ("<xsl:value-of select="/websrvXML/FormInformation/invIDCode"/>" == "")
        {         
          _screenMode = "add";
          setAllFieldsTo(false);
          //document.getElementById("actionSelect").disabled = true;
          document.getElementById("stopDate").disable(true);
          
          if (_dateFormat == "dmy")
            document.getElementById("stopDate").value = "31/12/9999";
          else 
            document.getElementById("stopDate").value = "12/31/9999";		
            
          document.getElementById("actionDiv").innerHTML = "Add New Invoice";
          document.getElementById("actionDiv").style.fontWeight = "bold";
        }
        else
        {
          _screenMode = "modify";
          if (_allowUpdates == "no")
            document.getElementById("actionSelect").disabled = true;
        }
      }
    </script>
    
  </xsl:template>
  
  <xsl:template name="escapeQuotes">
  	<xsl:param name="val"/>
		
	<xsl:variable name="doubleQuote">"</xsl:variable>
	
	<xsl:call-template name="string-replace-all">
		<xsl:with-param name="text" select="$val"/>
		<xsl:with-param name="replace" select="$doubleQuote"/>
		<xsl:with-param name="by" select="concat('\', $doubleQuote)"/>
	</xsl:call-template>
  </xsl:template>
  
  <xsl:template name="string-replace-all">
  <xsl:param name="text"/>
  <xsl:param name="replace"/>
  <xsl:param name="by"/>
  <xsl:choose>
    <xsl:when test="contains($text,$replace)">
      <xsl:value-of select="substring-before($text,$replace)"/>
      <xsl:value-of select="$by"/>
      <xsl:call-template name="string-replace-all">
        <xsl:with-param name="text" select="substring-after($text,$replace)"/>
        <xsl:with-param name="replace" select="$replace"/>
        <xsl:with-param name="by" select="$by"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$text"/>
    </xsl:otherwise>
  </xsl:choose>
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
  
  
  <xsl:template name="tmplBehaviours">
    
  </xsl:template>
  
  
</xsl:stylesheet>
