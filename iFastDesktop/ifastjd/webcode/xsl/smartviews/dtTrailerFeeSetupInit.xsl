<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version = "1.0">
	<xsl:template match="/">

		<message>			
			<request>
				<dtTrailerFeeSetupInitRequest>
					<RequestHeader>
						<apiName>dtTrailerFeeSetupInit</apiName> 
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
						<elementLength>short</elementLength>          
						<interfaceName/> 
						<dataMode>inquire</dataMode> 
						<language>en</language> 
						<downLoadMode>no</downLoadMode> 
						<locale>enUS</locale> 
					</RequestHeader>
					<data>
						<accountNum><xsl:value-of select="//accountNum"/></accountNum>
					</data>
				</dtTrailerFeeSetupInitRequest>
			</request>
			<errorCodesToIgnore/>
		</message>  

	</xsl:template>
</xsl:stylesheet>