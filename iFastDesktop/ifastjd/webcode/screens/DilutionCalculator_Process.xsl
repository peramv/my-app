<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:template match="/">
        <responseContents>					
            <xsl:choose>
                <!-- Error occured --> 
                <xsl:when test="/websrvXML/Error">                    
                    <xsl:copy-of select="/websrvXML/Error"/>                    
                </xsl:when>
                            
                <!-- get calcProc response -->            
                <xsl:when test="/websrvXML/dtDilutionCalcProcResponse">                    
                    <xsl:copy-of select="/websrvXML/dtDilutionCalcProcResponse/DilutionTransactions"/>                                                
                </xsl:when>
                
                <!-- get calulate response -->
                <xsl:otherwise>
                    <xsl:copy-of select="/websrvXML/dtDilutionCalculateResponse/DilutionTotal"/>                                                                                                      
                </xsl:otherwise>
            </xsl:choose>
            
        </responseContents>
    </xsl:template>
        
    
</xsl:stylesheet>