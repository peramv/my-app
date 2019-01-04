<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_ClassListTemplate.xsl"/>
	
	<xsl:template match="/">	
		
		<responseContents>					
			<xsl:choose>
				<!-- Sonic Call Error occured --> 
				<xsl:when test="/websrvXML/Error">                    
					<xsl:copy-of select="/websrvXML/Error"/>                    
				</xsl:when>
				
				<!-- get reload records -->
				<xsl:otherwise>
					<xsl:if test="/websrvXML/classSearchResponse">
						<classListResponse>
							<xsl:call-template name="ClassList_Tmpl">								
								<xsl:with-param name="resultsSrc" select="/websrvXML/classSearchResponse"/> 		        				
							</xsl:call-template>
						</classListResponse>						
					</xsl:if>															                                                                                                     
				</xsl:otherwise>
			</xsl:choose>
			
		</responseContents>-->
	</xsl:template>

  
</xsl:stylesheet>
