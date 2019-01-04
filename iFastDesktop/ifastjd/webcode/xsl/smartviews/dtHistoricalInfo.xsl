<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version = "1.0">
	<xsl:template match="/">
		
		<message>			
			<request>
				<dtHistoricalInfoRequest>
					<RequestHeader>
						<apiName>dtHistoricalInfo</apiName> 
						<ruserId>
							<xsl:value-of select="/websrvXML/requestInfo/request/SmartviewRequest/header/ruserId"/>
						</ruserId>						
						<envName>
							<xsl:value-of select="/websrvXML/requestInfo/request/SmartviewRequest/header/envName"/>
						</envName>									
						<clientCode>
							<xsl:value-of select="/websrvXML/requestInfo/request/SmartviewRequest/header/companyCode"/>
						</clientCode>
						<sessionId>
							<xsl:value-of select="/websrvXML/requestInfo/request/SmartviewRequest/header/sessionId"/>
						</sessionId> 
						<dateFormat>
							<xsl:value-of select="/websrvXML/requestInfo/request/SmartviewRequest/header/dateFormat"/>
						</dateFormat>
						
						<!--
						<dateFormat>
							<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
						</dateFormat>
						-->

						<elementLength>short</elementLength>          
						<interfaceName>ifds.dt</interfaceName> 
						<dataMode>inquire</dataMode> 
						<language>en</language> 
						<downLoadMode>no</downLoadMode> 
						<locale>enUS</locale> 
					</RequestHeader>
					<data>
						<!-- TrailerFeeSetup screen is passing parameters old way, so require this check until can go back and correct it -->
						<xsl:choose>
							<xsl:when test="/websrvXML/requestInfo/request/*">
								<xsl:copy-of select="/websrvXML/requestInfo/request/SmartviewRequest/body/*"/>
							</xsl:when>
							<xsl:otherwise>
								<auditType><xsl:value-of select="/websrvXML/FormInformation/auditType"/></auditType>						
								<auditRecId><xsl:value-of select="/websrvXML/FormInformation/auditRecId"/></auditRecId>						
								<startRecNum><xsl:value-of select="/websrvXML/FormInformation/startRecNum"/></startRecNum>
								<requestRecNum><xsl:value-of select="/websrvXML/FormInformation/requestRecNum"/></requestRecNum>
							</xsl:otherwise>
						</xsl:choose>	
					</data>
				</dtHistoricalInfoRequest>
			</request>
			<errorCodesToIgnore/>
		</message>  

	</xsl:template>
</xsl:stylesheet>