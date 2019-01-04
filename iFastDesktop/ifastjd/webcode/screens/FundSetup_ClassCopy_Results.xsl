<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassCopy_ClassListTemplate.xsl"/>
	
	<xsl:template match="/">	
		
		<responseContents>					
			<xsl:choose>
				<!-- Sonic Call Error occured --> 
				<xsl:when test="/websrvXML/Error">                    
					<xsl:copy-of select="/websrvXML/Error"/>                    
				</xsl:when>
								
				<xsl:otherwise>
					<xsl:if test="/websrvXML/classSearchResponse">
						<classListResponse>
							<xsl:call-template name="ClassList_Tmpl">								
								<xsl:with-param name="listSrc" select="/websrvXML/classSearchResponse/Classes"/> 		        				
							</xsl:call-template>
						</classListResponse>						
					</xsl:if>
					
					<xsl:if test="/websrvXML/validateFundInfoResponse">
						<validationResponse>
							<status><xsl:value-of select="/websrvXML/validateFundInfoResponse/RequestStatus/status"/></status>
							<xsl:if test="/websrvXML/validateFundInfoResponse/RequestStatus/Errors">
								<Errors>
									<xsl:for-each select="/websrvXML/validateFundInfoResponse/RequestStatus/Errors/Error">
										<Error>
											<field><xsl:value-of select="fieldSource/xmlElementName"/></field>
											<desc><xsl:value-of select="text"/></desc>
										</Error>
									</xsl:for-each>
								</Errors>
							</xsl:if>
						</validationResponse>						
					</xsl:if>
					
					<xsl:if test="/websrvXML/dtCopyClassUpdResponse">
						<updateResponse>
							<status><xsl:value-of select="/websrvXML/dtCopyClassUpdResponse/RequestStatus/status"/></status>							
						</updateResponse>						
					</xsl:if>																									                                                                                                    
				</xsl:otherwise>
			</xsl:choose>
			
		</responseContents>
	</xsl:template>

  
</xsl:stylesheet>
