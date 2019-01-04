<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/RegDoc_ListTemplate.xsl"/>
    
	<xsl:template match="/">	
		<responseContents>					
			<xsl:choose>
				<!-- Sonic Call Error occured --> 
				<xsl:when test="/websrvXML/Error">                    
					<xsl:copy-of select="/websrvXML/Error"/>                    
				</xsl:when>
								
				<!-- get reload records -->
				<xsl:otherwise>
					<xsl:if test="/websrvXML/dtRegDocListsProcResponse">
						<tableUpdate>
							<xsl:call-template name="RegDocList_Tmpl">
								<xsl:with-param name="listSrc" select="/websrvXML/dtRegDocListsProcResponse/RegDocList"/>	        				
							</xsl:call-template>
						</tableUpdate>						
					</xsl:if>															                                                                                                     
				</xsl:otherwise>
			</xsl:choose>
			
		</responseContents>
	</xsl:template>


</xsl:stylesheet>
