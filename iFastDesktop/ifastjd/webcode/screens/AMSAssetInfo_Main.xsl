<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/AMSAssetInfo_Template.xsl"/>
  
  <xsl:variable name="vClient"       		select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      	select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          	select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"           		select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           		select="/websrvXML/FormInformation/cz"/>          
  <xsl:variable name="vTIDX"        		select="/websrvXML/FormInformation/tidx"/>  
  <xsl:variable name="dateFormat"    select="/websrvXML/FormInformation/dateFormat"/>
  
  
  <xsl:template match="/">

    <Screen>
      
      <html>
        
        <head>
          <title>AMS Asset Information</title>
          <script src="{$vURL}javascript/General_Desktop.js"/>
          
          <!-- web library js code -->          
          <script src="{$vURL}WebLibrary/JSLib/Err.js"/>          
          <script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
          <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
          <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
          <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
          <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
          <script src="{$vURL}WebLibrary/WebComps/IFDSTableComponent.js"></script>
          
          <script src="{$vURL}javascript/AMSAssetInfo.js"/>
                                                 
          <script>
            var _vURL             		= "<xsl:value-of select="$vURL"/>";
            var _vServletPath     	= "<xsl:value-of select="$vServletPath"/>";
            var _vCZ              		= "<xsl:value-of select="$vCZ"/>";
            var _companyCode    = "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
            var _ruserId         		= "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
            var _sessionId        	= "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
            var _envName        	= "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";
            var _dateFormat       	= "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";            
            
            var _accountNum 		= "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>"; 
			var _searchType			= "<xsl:value-of select="/websrvXML/dtAMSAssetInitResponse/AMSAssetInfo/searchType"/>".toLowerCase();
			
			setSessionToken( _sessionId );
          </script>
          
          <style>
			  BODY, DIV, TABLE, TD, LEGEND
			  {
					font-family:  CourierNew,  Verdana, Arial, Sans-Serif;
					font-size: 10pt;
					cursor: default;    
			  }
			  
			  .tableHeader
			  {
				  background:lightgrey;
				  padding-top:3px;
				  padding-bottom:3px;
				  border-bottom:1px solid black;
				  border-left:1px solid black;
				  border-top:1px solid black;
			  }
			  			
			  .tableData
			  {
				  border-left: 1px solid black;
				  padding:3px;
			  }
			  
			  .lastRow
			  {
				  border-bottom: 1px solid black;
			  }
			  
			  .lastCol
			  {
				  border-right: 1px solid black;
			  }
          </style>
         
        </head>
        
        <body>
          <xsl:attribute name="onload">
              <xsl:choose>
				  <xsl:when test="/websrvXML/dtAMSAssetInitResponse/RequestStatus/Errors">
					  alert( "<xsl:value-of select="/websrvXML/dtAMSAssetInitResponse/RequestStatus/Errors/Error/text"/>" );
				  </xsl:when>
  				  <xsl:when test="/websrvXML/responseContents/error">
					  alert( "<xsl:value-of select="/websrvXML/responseContents/error"/>" );
				  </xsl:when>
				  <xsl:otherwise>
					  loading();
				  </xsl:otherwise>
              </xsl:choose>
          </xsl:attribute>
         
			<div id="contentsDiv" style="width:800px">

				<div id="headerInfoDiv" style="width:100%; text-align:left; padding-left:30px; padding-bottom:10px;">
					<table cellpadding="0" cellspacing="0" style="table-layout:fixed">
						<tr>
							<td style="width:100; padding-bottom:3px; font-weight:bold;">Shareholder:</td>
							<td style="width:300; padding-bottom:3px;"><xsl:value-of select="/websrvXML/dtAMSAssetInitResponse/AMSAssetInfo/shrNum"/></td>
						</tr>
						<tr>
							<td style="width:100; padding-bottom:3px; font-weight:bold;">Account:</td>
							<td style="width:300; padding-bottom:3px;"><xsl:value-of select="/websrvXML/FormInformation/AccountNum"/></td>
						</tr>
						<tr>
							<td style="width:100; padding-bottom:3px; font-weight:bold;">Name:</td>
							<td style="width:300; padding-bottom:3px;"><xsl:value-of select="/websrvXML/dtAMSAssetInitResponse/AMSAssetInfo/name"/></td>
						</tr>
					</table>
				</div>				
				<div id="dataDiv" style="width:1050; text-align:center;">					
					<div style="padding-bottom:5px;">
						<table>
							<tr>
								<td style="width:50; text-align:right;">
									<input id="fundOpt" type="radio" name="searchType" value="fund"/>
								</td>
								<td style="width:100; text-align:left;">
									Fund
								</td>
								<td style="width:50; text-align:right;">
									<input id="assetOpt" type="radio" name="searchType" value="asset"/>
								</td>
								<td style="width:100; text-align:left;">
									Asset
								</td>
								<td style="width:50; text-align:right;">
									<input id="subassetOpt" type="radio" name="searchType" value="subasset"/>
								</td>
								<td style="width:100; text-align:left;">
									SubAsset
								</td>
							</tr>
						</table>
					</div>
										
					<div id="listContentsDiv">
						<xsl:call-template name="AssetListTmpl">
							<xsl:with-param name="sourceNode" select=".//AssetInfo"/>
							<xsl:with-param name="searchType" select="//searchType"/>
						</xsl:call-template>
					</div>
				</div>
			</div>
			
			<div id="disableDiv" style="position:absolute; top:0; left; 0; width:100%; height:100%; background:e6e6e6; filter:alpha(opacity=70); display:none;">
			</div>
			
			<div id="searchIndicatorDiv" style="position:absolute; border:2px solid grey; width:200; height:50; top:100; left:300; background:white; z-index:50; padding-top:10px; display:none">
				<span style="width:100%; text-align:center; font-size:15px; font-style:italic">Searching ...</span>
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