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
					<TerminationData>
						<xsl:copy-of select="/websrvXML/dtRESPTermintnReloadResponse/RESPTerminationInfo/TerminationRecords/*"/>
					</TerminationData>
					<xsl:copy-of select="/websrvXML/dtRESPTermintnReloadResponse/RecordRange"/>		
				</xsl:otherwise>
			</xsl:choose>
				
		</responseContents>		
	</xsl:template>
		
</xsl:stylesheet>