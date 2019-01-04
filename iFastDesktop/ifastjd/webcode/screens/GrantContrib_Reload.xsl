<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/GrantContrib_DataTemplate.xsl"/>
		
	<xsl:template match="/">
		<responseContents>
			<xsl:choose>
				<xsl:when test="/websrvXML/Error">
					<xsl:copy-of select="/websrvXML/Error"/>
				</xsl:when>
				<xsl:otherwise>
					<GrantContribData>
						<xsl:copy-of select="/websrvXML/dtGrantContribReloadResponse/GrantContributionInfo/*"/>
					</GrantContribData>
					<xsl:copy-of select="/websrvXML/dtGrantContribReloadResponse/RecordRange"/>		
				</xsl:otherwise>
			</xsl:choose>
				
		</responseContents>		
	</xsl:template>
		
</xsl:stylesheet>