<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/DST_WebBehavioursTemplate.xsl"/>
  
  <xsl:variable name="vClient"       			select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  	select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      		select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          		select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"          			select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           			select="/websrvXML/FormInformation/cz"/>          
  <xsl:variable name="vTIDX"         		select="/websrvXML/FormInformation/tidx"/>
   <xsl:variable name="dateFormat"    	select="/websrvXML/FormInformation/dateFormat"/>

  <xsl:template match="/">

    <Screen>
      
      <html>
        <title>Institutional Accounts</title>
        
        <head>
			<script src="{$vURL}WebLibrary/JSLib/Cookie.js"/>
			<script src="{$vURL}WebLibrary/JSLib/Err.js"/>          
			<script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
            <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
            <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
            <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
            <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
            <script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>        
                  
            <script>
				var _vURL 						= "<xsl:value-of select="$vURL"/>";
				var _vServletPath 			= "<xsl:value-of select="$vServletPath"/>";
				var _vCZ 						= "<xsl:value-of select="$vCZ"/>";
				var _companyCode 		= "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
				var _ruserId     				= "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
				var _sessionId   				= "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
				var _envName   				= "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";            
				var _dateFormat  			= "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
				
				var _assetCode  			= "<xsl:value-of select="/websrvXML/dtFeeIDAssetValInitResponse/assetCode"/>";
				
				
				function refresh()
				{
					var paramMap = {}
					paramMap["cz"]                			= _vCZ;
					paramMap["jobname"]           		= "ManagementFee_AssetValues";    
					paramMap["companyCode"]       = _companyCode;
					paramMap["ruserId"]           		= _ruserId;
					paramMap["sessionId"]        		= _sessionId;
					paramMap["envName"]       	  	= _envName;
					paramMap["dateFormat"]        	= _dateFormat;
					paramMap["assetCode"]        	= _assetCode;					
					paramMap["startDate"]				= UTL.getElem( "startDate" ).value;
					paramMap["endDate"]				= UTL.getElem( "endDate" ).value;
					paramMap["refresh"]					= "true";
    
					var url = HTTP.buildURL( _vServletPath, paramMap );
					
					// clear the current inner html
					UTL.getElem( "valuesDiv" ).innerHTML = "";
					
					HTTP.getText( url, refresh_callback );					
				}
				
				function refresh_callback( responseText )
				{
					var responseXML = XML.parseToXML( responseText );

					var errorNode = XML.getNode( "/responseContents/error", responseXML );
    
					if ( errorNode )
					{
						alert( UTL.trimString( errorNode.firstChild.nodeValue ) );
						return;
					}
					else
					{
						var updatedHTMLNode = XML.getNode( "/responseContents/updatedHTML", responseXML );        
                						
						// set the inner html to the html contents within updatedHTMLNode
						// note: the html contents are treated as xml within the xml dom
                
						UTL.getElem( "valuesDiv" ).innerHTML = updatedHTMLNode.firstChild.xml;
					}	
				}
          </script>
          
          <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"></link>
          
          <xsl:call-template name="DST_WebBehavioursTmpl"/>
        </head>
        
        <body bgcolor="white" style="overflow:auto;">
          <xsl:attribute name="onload">
             <xsl:choose>
                   <xsl:when test="/websrvXML/responseContents/error">
					   alert( "<xsl:value-of select="/websrvXML/responseContents/error"/>" );
                   </xsl:when>
                   <xsl:when test="/websrvXML/dtFeeIDAssetValInitResponse/RequestStatus/Errors">
					   alert( "<xsl:value-of select="/websrvXML/dtFeeIDAssetValInitResponse/RequestStatus/Errors/Error/text"/>" );
                   </xsl:when>
             </xsl:choose>
          </xsl:attribute>
          
          <table style="position:relative; top:10; left:22; width:260">
            <tr>
              <td style="font-weight:bold" colspan="2">
                Asset Values
              </td>
            </tr>
            <tr>
              <td colspan="2" style="width:300">
                Asset: <xsl:value-of select="/websrvXML/dtFeeIDAssetValInitResponse/assetCode"/> - <xsl:value-of select="/websrvXML/dtFeeIDAssetValInitResponse/assetName"/>
              </td>
            </tr>
            <tr>
              <td style="width:80">
                Start Date:
              </td>
              <td style="width:160">
                <input type="text" id="startDate" class="dstdatepicker">
                  <xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
                  <xsl:attribute name="value">
                    <xsl:value-of select="/websrvXML/dtFeeIDAssetValInitResponse/startDate"/>
                  </xsl:attribute>
                </input>
              </td>
            </tr>
            <tr>
              <td style="width:80">
                End Date:
              </td>
              <td style="width:160">
                <input type="text" id="endDate" class="dstdatepicker">
                <xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
                  <xsl:attribute name="value">
                    <xsl:value-of select="/websrvXML/dtFeeIDAssetValInitResponse/endDate"/>
                  </xsl:attribute>
                </input>
              </td>
            </tr>
          </table>
          
          <fieldset style="position:relative; left:25; top:10; width:250; display:block; padding-bottom:20px">
            <legend style="cursor:pointer" onclick='' ><font color="black"><b> Asset Values </b> </font></legend>
            
            <span style="position:relative; top:-16px; left:155px">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                            
                <xsl:with-param name="id">refreshAssetValuesBtn</xsl:with-param>
                <xsl:with-param name="onclick">refresh();</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">80</xsl:with-param>
                <xsl:with-param name="text">Refresh</xsl:with-param>
                <xsl:with-param name="color">orange</xsl:with-param>
              </xsl:call-template>
            </span>   
            
            <div style="width:100%;">
              <div style="width:100%">                
                <span style="width:50%; font-weight:bold; height:20px; padding-left: 5px">
                  <span style="border-bottom: 2px solid #ffd696; width:70%; text-align:center">Date</span>
                </span>
                <span style="width:50%; font-weight:bold; height:20px;">
                  <span style="border-bottom: 2px solid #ffd696; width:70%; text-align:center">Value</span>
                </span>
              </div>
              <div id="valuesDiv" style="width:100%; height:200px; overflow-y:scroll">
                <table style="table-layout:fixed;">
                  <xsl:for-each select="/websrvXML/dtFeeIDAssetValInitResponse/AssetValues/AssetValue">                    
                    <tr>
                      <td style="width:45%; border-right:1px solid gray; padding-left:5px">
                        <xsl:value-of select="assetDate"/>
                      </td>
                      <td style="width:55%; padding-left:5px">
                        <xsl:value-of select="assetValue"/>
                      </td>
                    </tr>                    
                  </xsl:for-each>
                </table>              
              </div>
            </div>
          </fieldset>      
          
          <span style="position:relative; top:-2px; left:95px">
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                            
              <xsl:with-param name="size">large</xsl:with-param>
              <xsl:with-param name="onclick">parent.closeAssetValuesScreen()</xsl:with-param>              
              <xsl:with-param name="width">80</xsl:with-param>
              <xsl:with-param name="text">Close</xsl:with-param>
              <xsl:with-param name="color">orange</xsl:with-param>
            </xsl:call-template>
          </span>             
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
