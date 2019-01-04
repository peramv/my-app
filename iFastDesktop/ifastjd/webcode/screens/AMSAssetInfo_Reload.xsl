<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
        
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/AMSAssetInfo_Template.xsl"/>
    
    <xsl:template match="/">
        <responseContents>
            <xsl:choose>
                <xsl:when test="/websrvXML/dtAMSAssetInitResponse/RequestStatus/Errors">
                    <error>
                        <xsl:value-of select="/websrvXML/dtAMSAssetInitResponse/RequestStatus/Errors/Error/text"/>
                    </error>
                </xsl:when>
                
                <xsl:otherwise>
					<searchType><xsl:value-of select="/websrvXML/dtAMSAssetInitResponse/AMSAssetInfo/searchType"/></searchType>
					<updatedHTML>    
                        <xsl:call-template name="AssetListTmpl">
							<xsl:with-param name="sourceNode" select="/websrvXML/dtAMSAssetInitResponse/AMSAssetInfo/AssetInfo"/>
							<xsl:with-param name="searchType" select="/websrvXML/dtAMSAssetInitResponse/AMSAssetInfo/searchType"/>
						</xsl:call-template>
                    </updatedHTML>
                </xsl:otherwise>
            </xsl:choose>
        </responseContents>
    </xsl:template>
</xsl:stylesheet>
