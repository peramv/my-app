<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<!-- Init CLIENT & PATH VARIABLES - start -->
	<xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
	<xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
	<xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
	<xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/')"/>
	<xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
	<xsl:variable name="vTIDX"         select="/websrvXML/FormInformation/tidx"/>
	<xsl:variable name="vDesktopColor" select="/websrvXML/FormInformation/bgcolor"/>	
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	
	<xsl:template match="/">
		<responseContents>
			<xsl:choose>
				<xsl:when test="/websrvXML/Error">
					<xsl:copy-of select="/websrvXML/Error"/>
				</xsl:when>
				<xsl:otherwise>
					<HistoricalHTML>
						<xsl:call-template name="DesktopHistoricalTableTmpl">
							<xsl:with-param name="sourceNode" select="/websrvXML/dtHistRESPGrantResponse/HistoricalInformation"/>
						</xsl:call-template>
					</HistoricalHTML>	
				</xsl:otherwise>
			</xsl:choose>
				
		</responseContents>		
	</xsl:template>
		
</xsl:stylesheet>