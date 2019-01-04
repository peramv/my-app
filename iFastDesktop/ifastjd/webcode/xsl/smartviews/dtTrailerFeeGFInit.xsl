<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version = "1.0">
	<xsl:template match="/">

		<message>			
			<request>
				<dtTrailerFeeGFInitRequest>
					<RequestHeader>
						<apiName>dtTrailerFeeGFInit</apiName> 
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
						<searchAccountNum><xsl:value-of select="//searchAccountNum"/></searchAccountNum>
						<searchValue><xsl:value-of select="//searchValue"/></searchValue>
						<searchFundGroup><xsl:value-of select="//searchFundGroup"/></searchFundGroup>
						<searchFundCode><xsl:value-of select="//searchFundCode"/></searchFundCode>
						<searchClassCode><xsl:value-of select="//searchClassCode"/></searchClassCode>
						<searchBrokerCode><xsl:value-of select="//searchBrokerCode"/></searchBrokerCode>
						<searchBranchCode><xsl:value-of select="//searchBranchCode"/></searchBranchCode>
						<searchSlsRepCode><xsl:value-of select="//searchSlsRepCode"/></searchSlsRepCode>
						<avgType><xsl:value-of select="//avgType"/></avgType>
						<balType><xsl:value-of select="//balType"/></balType>
						<balAsOf><xsl:value-of select="//balAsOf"/></balAsOf>
						<distribChannel><xsl:value-of select="//distribChannel"/></distribChannel>
						<effDate><xsl:value-of select="//effDate"/></effDate>
						<stopDate><xsl:value-of select="//stopDate"/></stopDate>
						<startRecNum></startRecNum>
						<requestRecNum></requestRecNum>
					</data>
				</dtTrailerFeeGFInitRequest>
			</request>
			<errorCodesToIgnore/>
		</message>  

	</xsl:template>
</xsl:stylesheet>