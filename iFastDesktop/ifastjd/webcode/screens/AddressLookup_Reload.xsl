<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/AddressLookup_ListTemplates.xsl"/>
	
	<xsl:template match="/">	
		
		<responseContents>					
			<xsl:choose>
				<!-- Sonic Call Error occured --> 
				<xsl:when test="/websrvXML/Error">                    
					<xsl:copy-of select="/websrvXML/Error"/>                    
				</xsl:when>
								
				<xsl:otherwise>
					<addressLookupResponse>
						<addressList>
							<xsl:apply-templates select="/websrvXML/dtPCLookupReloadResponse"/>
						</addressList>
						<provDetails>
							<xsl:copy-of select="/websrvXML/dtPCLookupReloadResponse/PCLookupDetails/prov"/>
							<xsl:copy-of select="/websrvXML/dtPCLookupReloadResponse/PCLookupDetails/cntryCode"/>
							<xsl:copy-of select="/websrvXML/dtPCLookupReloadResponse/PCLookupDetails/pstlCode"/>
						</provDetails>			
					</addressLookupResponse>						
				</xsl:otherwise>
			</xsl:choose>
			
		</responseContents>
	</xsl:template>

  
</xsl:stylesheet>
