<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/ManagementFeeRebate_FeeIDTemplates.xsl"/>
    
    <xsl:include 
        href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>
    
    <xsl:variable name="vClient" select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath" select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir" select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL" select="concat( $vDataDir, $vClient, '/' )"/>
    
    <xsl:template match="/">
      <responseContents>
          
          <xsl:choose>
          
              <xsl:when test="/websrvXML/dtMFRFeeIDProcessingResponse/RequestStatus/Errors">
				  <error>
					  <xsl:value-of select="/websrvXML/dtMFRFeeIDProcessingResponse/RequestStatus/Errors/Error/text"/>
				  </error>
				  <errorSeverity>
					  <xsl:value-of select="/websrvXML/dtMFRFeeIDProcessingResponse/RequestStatus/Errors/Error/errorSeverity"/>
				  </errorSeverity>
			  </xsl:when>
			  			  
			  <xsl:when test="/websrvXML/dtMFRFeeIDProcessingResponse/FundHistory">
				  <xsl:apply-templates select="/websrvXML/dtMFRFeeIDProcessingResponse/FundHistory"/>
			  </xsl:when>
			  			  
			  <xsl:when test="/websrvXML/dtMFRFeeIDProcessingResponse/UpdateHistory">
				  <xsl:apply-templates select="/websrvXML/dtMFRFeeIDProcessingResponse/UpdateHistory"/>
			  </xsl:when>
			  
			  <xsl:otherwise>
				   <updatedHTML>
					   <div>
							<xsl:choose>
								<xsl:when test="/websrvXML/dtMFRFeeIDProcessingResponse/FeeID/CurrentUserDate">
									<input type="hidden" name="CurrentUserDateHid" id="CurrentUserDateHid" >
									   <xsl:attribute name="value"><xsl:value-of 
								   select="/websrvXML/dtMFRFeeIDProcessingResponse/FeeID/CurrentUserDate"/></xsl:attribute></input>
								</xsl:when>
								<xsl:when test="/websrvXML/dtMFRFeeIDProcessingResponse/FeeID/nextMFRDate">
									<input type="hidden" name="nextMFRDateHid" id="nextMFRDateHid" >
									   <xsl:attribute name="value"><xsl:value-of 
								   select="/websrvXML/dtMFRFeeIDProcessingResponse/FeeID/nextMFRDate"/></xsl:attribute></input>
									<input type="hidden" name="lastAccrualDateHid" id="lastAccrualDateHid" >
									   <xsl:attribute name="value"><xsl:value-of 
								   select="/websrvXML/dtMFRFeeIDProcessingResponse/FeeID/lastAccrualDate"/></xsl:attribute></input>
								</xsl:when>
								<xsl:when test="/websrvXML/dtMFRFeeIDProcessingResponse/Accounts/Account/nextMFRDate">
									<input type="hidden" name="nextMFRDateHid" id="nextMFRDateHid" >
									   <xsl:attribute name="value"><xsl:value-of 
								   select="/websrvXML/dtMFRFeeIDProcessingResponse/Accounts/Account/nextMFRDate"/></xsl:attribute></input>
									<input type="hidden" name="lastAccrualDateHid" id="lastAccrualDateHid">
									   <xsl:attribute name="value"><xsl:value-of 
								   select="/websrvXML/dtMFRFeeIDProcessingResponse/Accounts/Account/lastAccrualDate"/></xsl:attribute></input>
								</xsl:when>
							</xsl:choose>
							
						   
						   <xsl:choose>
							   <xsl:when test="//Funds/Fund">
								   <xsl:for-each select="//Funds/Fund">
									   <xsl:call-template name="FeeIDFundListTmpl">
										   <xsl:with-param name="position"><xsl:value-of select="position()"/></xsl:with-param>
										   <xsl:with-param name="vURL"><xsl:value-of select="$vURL"/></xsl:with-param>
									   </xsl:call-template>    
								   </xsl:for-each>
							   </xsl:when>
							   <xsl:when test="//Accounts/Account">
								   <xsl:call-template name="AccountListTmpl">
									   <xsl:with-param name="sourceNode" select="//Accounts"/>
								   </xsl:call-template>
							   </xsl:when>
						   </xsl:choose>
					
					   </div>
				   </updatedHTML>
              </xsl:otherwise>
              
          </xsl:choose>
       </responseContents>
    </xsl:template>
        
    
</xsl:stylesheet>