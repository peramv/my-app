<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/LIFGainLoss_TransTemplate.xsl"/>
    
	<xsl:template match="/">	
		<responseContents>					
			<xsl:choose>
				<!-- Sonic Call Error occured --> 
				<xsl:when test="/websrvXML/Error">                    
					<xsl:copy-of select="/websrvXML/Error"/>                    
				</xsl:when>
								
				<!-- get reload records -->
				<xsl:otherwise>
					<xsl:if test="/websrvXML/dtLIFGainLossReloadResponse">
						<tableUpdate>							
							<xsl:apply-templates select="/websrvXML/dtLIFGainLossReloadResponse/transactionList">
								<xsl:with-param name="UpdAllowed" select="/websrvXML/dtLIFGainLossReloadResponse/UpdFlag/UpdAllowed"/>
							</xsl:apply-templates>
						</tableUpdate>
						<totalGainLoss>
							<xsl:value-of select="/websrvXML/dtLIFGainLossReloadResponse/totalGainLoss/totGainLoss"/>
						</totalGainLoss>	
					</xsl:if>
					<xsl:if test="/websrvXML/dtLIFGainLossProcResponse">
						<tableUpdate>							
							<xsl:apply-templates select="/websrvXML/dtLIFGainLossProcResponse/transactionList">
								<xsl:with-param name="UpdAllowed" select="/websrvXML/dtLIFGainLossProcResponse/UpdFlag/UpdAllowed"/>
							</xsl:apply-templates>
						</tableUpdate>
						<totalGainLoss>
							<xsl:value-of select="/websrvXML/dtLIFGainLossProcResponse/totalGainLoss/totGainLoss"/>
						</totalGainLoss>
					</xsl:if>															                                                                                                     
				</xsl:otherwise>
			</xsl:choose>
			
		</responseContents>
	</xsl:template>


</xsl:stylesheet>
