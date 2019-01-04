<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
	<xsl:template match="/">	
		<responseContents>					
			<xsl:choose>
				<!-- Sonic Call Error occured --> 
				<xsl:when test="/websrvXML/Error">                    
					<xsl:copy-of select="/websrvXML/Error"/>                    
				</xsl:when>
								
				<!-- get reload records -->
				<xsl:otherwise>
					<xsl:if test="/websrvXML/dtRelFrozenAcctInitResponse">
						<xsl:copy-of select="/websrvXML/dtRelFrozenAcctInitResponse/*"/>
					</xsl:if>
					
					<xsl:if test="/websrvXML/dtRelFrozenAcctProcResponse">								
						<xsl:copy-of select="/websrvXML/dtRelFrozenAcctProcResponse/RequestStatus"/>							
					</xsl:if>
				</xsl:otherwise>
			</xsl:choose>
			
		</responseContents>
	</xsl:template>


</xsl:stylesheet>
