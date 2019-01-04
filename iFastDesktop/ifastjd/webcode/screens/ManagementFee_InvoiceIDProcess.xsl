<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:variable name="vClient" select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath" select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir" select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL" select="concat( $vDataDir, $vClient, '/' )"/>
    
    <xsl:template match="/">
      <responseContents>

          <xsl:if test="/websrvXML/dtInvoiceIDProcessingResponse/RequestStatus/Errors">
              <error>
                  <xsl:value-of select="/websrvXML/dtInvoiceIDProcessingResponse/RequestStatus/Errors/Error/text"/>
              </error>
              <errorSeverity>
                  <xsl:value-of select="/websrvXML/dtInvoiceIDProcessingResponse/RequestStatus/Errors/Error/errorSeverity"/>
              </errorSeverity>
          </xsl:if>
       </responseContents>
    </xsl:template>
        
    
</xsl:stylesheet>