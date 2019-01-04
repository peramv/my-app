<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:template match="/">
		<responseContents>
			<xsl:choose>
				<xsl:when test="/websrvXML/Error">
					<xsl:copy-of select="/websrvXML/Error"/>
				</xsl:when>
				<xsl:otherwise>
					<InterfaceFileData>
						<xsl:copy-of select="/websrvXML/dtInterfaceFileReloadResponse/InterfaceFileInfo/*"/>
					</InterfaceFileData>
					<xsl:copy-of select="/websrvXML/dtInterfaceFileReloadResponse/RecordRange"/>		
				</xsl:otherwise>
			</xsl:choose>
				
		</responseContents>		
	</xsl:template>
		
</xsl:stylesheet>