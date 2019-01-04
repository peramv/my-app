<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/RegStandards_ListTemplate.xsl"/>
    
	<xsl:template match="/">	
		<responseContents>					
			<xsl:choose>
				<!-- Sonic Call Error occured --> 
				<xsl:when test="/websrvXML/Error">                    
					<xsl:copy-of select="/websrvXML/Error"/>                    
				</xsl:when>
								
				<!-- get reload records -->
				<xsl:otherwise>
					<!-- reload call -->
					<xsl:if test="/websrvXML/dtRegStandardsReloadResponse">
						<tableUpdate>
							<xsl:call-template name="RegStandardsList_Tmpl">
								<xsl:with-param name="listSrc" select="/websrvXML/dtRegStandardsReloadResponse/RegStandardsList"/>	        				
							</xsl:call-template>
						</tableUpdate>
						<xsl:copy-of select="/websrvXML/dtRegStandardsReloadResponse/RecordRange"/>						
					</xsl:if>															                                                                                                     
					
					<!-- proc call -->
					<xsl:if test="/websrvXML/dtRegStandardsProcResponse">
						<tableUpdate>
							<xsl:call-template name="RegStandardsList_Tmpl">
								<xsl:with-param name="listSrc" select="/websrvXML/dtRegStandardsProcResponse/RegStandardsList"/>	        				
							</xsl:call-template>
						</tableUpdate>
						<xsl:copy-of select="/websrvXML/dtRegStandardsProcResponse/RecordRange"/>						
					</xsl:if>
				</xsl:otherwise>
			</xsl:choose>
			
		</responseContents>
	</xsl:template>


</xsl:stylesheet>
