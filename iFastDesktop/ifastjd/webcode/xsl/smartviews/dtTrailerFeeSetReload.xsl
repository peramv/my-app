<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version = "1.0">
	<xsl:template match="/">

		<message>			
			<request>
				<dtTrailerFeeSetReloadRequest>
					<RequestHeader>
						<apiName>dtTrailerFeeSetReload</apiName> 
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
						<searchValue><xsl:value-of select="//body/searchValue"/></searchValue>
						<searchFundGroup><xsl:value-of select="//body/searchFundGroup"/></searchFundGroup>
						<searchFundCode><xsl:value-of select="//body//searchFundCode"/></searchFundCode>
						<searchClassCode><xsl:value-of select="//body/searchClassCode"/></searchClassCode>
						<searchBrokerCode><xsl:value-of select="//body/searchBrokerCode"/></searchBrokerCode>
						<searchBranchCode><xsl:value-of select="//body/searchBranchCode"/></searchBranchCode>
						<searchSlsRepCode><xsl:value-of select="//body/searchSlsRepCode"/></searchSlsRepCode>
						<searchAccountNum><xsl:value-of select="//body/searchAccountNum"/></searchAccountNum>
						<searchDistribChannel><xsl:value-of select="//body/searchDistribChannel"/></searchDistribChannel>
						<startRecNum><xsl:value-of select="//body/startRecNum"/></startRecNum>
						<requestRecNum><xsl:value-of select="//body/requestRecNum"/></requestRecNum>
					</data>
				</dtTrailerFeeSetReloadRequest>
			</request>
			<errorCodesToIgnore>,15,</errorCodesToIgnore>   <!-- use extra commas to avoid false matches -->
		</message>  

	</xsl:template>
</xsl:stylesheet>