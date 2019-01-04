<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/AccountBalanceOverride_ResultsTemplate.xsl"/>
  
  
  <xsl:template match="/">
    <responseContents>
      <xsl:choose>
        
        <!-- RELOAD -->
        <xsl:when test="/websrvXML/dtAcctBalORReloadResponse">
          <xsl:choose>
            <xsl:when test="/websrvXML/dtAcctBalORReloadResponse/RequestStatus/Errors">
              <error>
                <xsl:value-of select="/websrvXML/dtAcctBalORReloadResponse/RequestStatus/Errors/Error/text"/>
              </error>
              <xsl:if test="websrvXML/dtAcctBalORReloadResponse/SearchMatchDetails">
				  <searchMatchDetails>
					  <xsl:copy-of select="/websrvXML/dtAcctBalORReloadResponse/SearchMatchDetails/*"/>
				  </searchMatchDetails>
              </xsl:if>
            </xsl:when>
            <xsl:otherwise>
              <searchMatchDetails>
				  <xsl:copy-of select="/websrvXML/dtAcctBalORReloadResponse/SearchMatchDetails/*"/>
              </searchMatchDetails>
              <updatedHTML>
                <xsl:call-template name="AccountBalanceListTmpl">
                  <xsl:with-param name="sourceNode" select="/websrvXML/dtAcctBalORReloadResponse/AccountBalances"/>
                </xsl:call-template>
              </updatedHTML>
            </xsl:otherwise>            
          </xsl:choose>
        </xsl:when>        
          
         <!-- PROCESS --> 
        <xsl:when test="/websrvXML/dtAcctBalORProcessingResponse">
          <xsl:choose>
            <xsl:when test="/websrvXML/dtAcctBalORProcessingResponse/RequestStatus/Errors">
              <error>
                <xsl:value-of select="/websrvXML/dtAcctBalORProcessingResponse/RequestStatus/Errors/Error/text"/>
              </error>
            </xsl:when>
            <xsl:otherwise>
              <updatedSearchValues>
                <xsl:copy-of select="/websrvXML/dtAcctBalORProcessingResponse/SearchValues/*"/>
              </updatedSearchValues>
              <searchMatchDetails>
				  <xsl:copy-of select="/websrvXML/dtAcctBalORProcessingResponse/SearchMatchDetails/*"/>
              </searchMatchDetails>
              <updatedHTML>
                <xsl:call-template name="AccountBalanceListTmpl">
                  <xsl:with-param name="sourceNode" select="/websrvXML/dtAcctBalORProcessingResponse/AccountBalances"/>
                </xsl:call-template>
              </updatedHTML>
            </xsl:otherwise>            
          </xsl:choose>
        </xsl:when>
          
      </xsl:choose>  
        
        
    </responseContents>
  </xsl:template>
  
</xsl:stylesheet>