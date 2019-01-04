<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/RESPNotional_DataTemplate.xsl"/>
	
	
	<xsl:template match="/">
		<responseContents>
			<xsl:choose>
				<xsl:when test="/websrvXML/Error">
					<xsl:copy-of select="/websrvXML/Error"/>
				</xsl:when>
				<xsl:otherwise>
					<notionalDataHTML>
						<xsl:call-template name="NotionalData_Tmpl">
							<xsl:with-param name="notlDataNode" select="/websrvXML/dtRESPNotlReloadResponse/NotionalInformation"/>
							<xsl:with-param name="notlOtherInfoNode" select="/websrvXML/dtRESPNotlReloadResponse/NotlOtherInfo"/>
							<xsl:with-param name="dateFilterType"><xsl:choose><xsl:when test="/websrvXML/FormInformation/period">period</xsl:when><xsl:otherwise>asOf</xsl:otherwise></xsl:choose></xsl:with-param>
							<xsl:with-param name="permissionNode" select="/websrvXML/dtRESPNotlReloadResponse/Permission"/>
						</xsl:call-template>
					</notionalDataHTML>		
				</xsl:otherwise>
			</xsl:choose>
				
		</responseContents>		
	</xsl:template>
		
</xsl:stylesheet>