<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/ManagementFee_FeeIDTemplates.xsl"/>
    
    <xsl:include 
        href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>
    
    <xsl:variable name="vClient" select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath" select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir" select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL" select="concat( $vDataDir, $vClient, '/' )"/>
    
    <xsl:template match="/">
      <responseContents>
          
          <xsl:choose>
          
              <xsl:when test="/websrvXML/dtFeeIDProcessingResponse/RequestStatus/Errors">
				  <error>
					  <xsl:value-of select="/websrvXML/dtFeeIDProcessingResponse/RequestStatus/Errors/Error/text"/>
				  </error>
				  <errorSeverity>
					  <xsl:value-of select="/websrvXML/dtFeeIDProcessingResponse/RequestStatus/Errors/Error/errorSeverity"/>
				  </errorSeverity>
			  </xsl:when>
			  
			  <xsl:when test="/websrvXML/dtFeeIDProcessingResponse/FundHistory">
				  <xsl:apply-templates select="/websrvXML/dtFeeIDProcessingResponse/FundHistory"/>
			  </xsl:when>
			  
			  <xsl:otherwise>
				   <updatedHTML>
					   <div>
							<xsl:for-each select="//Funds/Fund">
								<xsl:call-template name="FeeIDFundListTmpl">
									<xsl:with-param name="position"><xsl:value-of select="position()"/></xsl:with-param>
									<xsl:with-param name="vURL"><xsl:value-of select="$vURL"/></xsl:with-param>
								</xsl:call-template>    
							</xsl:for-each>
					   </div>
				   </updatedHTML>
				   <refreshNode><xsl:value-of select="/websrvXML/dtFeeIDProcessingResponse/refreshFeeIDScreen"/></refreshNode>
              </xsl:otherwise>
              
          </xsl:choose>
       </responseContents>
    </xsl:template>
        
    
</xsl:stylesheet>