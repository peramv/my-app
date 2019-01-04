<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version = "1.0">
	<xsl:template match="/">
		<Errors>			
			<xsl:choose>
				<xsl:when test="not(/*//RequestStatus)">
					<xsl:variable name="smartview"><xsl:value-of select="/*/FormInformation/smartview"/></xsl:variable>
					<Error>
						<errorSeverity>error</errorSeverity>
						<type>environment</type>
						<text>View call [<xsl:value-of select="$smartview"/>] to <xsl:value-of select="/*//RequestHeader/envName"/> failed and/or timed out.</text>					
					</Error>
				</xsl:when>
				<xsl:otherwise>
					<xsl:for-each select="/*//RequestStatus/Errors/Error">						
						<xsl:if test="not(errorCode = /*/FormInformation/ignoreErrorCode ) ">
						  <xsl:copy-of select="."/>
						</xsl:if>
					</xsl:for-each>					
				</xsl:otherwise>
			</xsl:choose>
		</Errors>	
	</xsl:template>
</xsl:stylesheet>