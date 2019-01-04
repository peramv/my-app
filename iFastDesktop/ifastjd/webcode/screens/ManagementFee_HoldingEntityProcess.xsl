<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/ManagementFee_HoldingEntityListTemplates.xsl"/>
    
    <xsl:variable name="vClient" select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath" select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir" select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL" select="concat( $vDataDir, $vClient, '/' )"/>
    
    <xsl:template match="/">
        <responseContents>
            <xsl:choose>
                <xsl:when test="/websrvXML/dtHoldingEntityMFProcResponse/RequestStatus/Errors">
                    <error>
                        <xsl:value-of select="/websrvXML/dtHoldingEntityMFProcResponse/RequestStatus/Errors/Error/text"/>
                    </error>
                </xsl:when>
                
                <xsl:otherwise>
                    <updatedHTML>
                           
                        <xsl:choose>
                            <xsl:when test="/websrvXML/requestInfo/request/Data/UpdAggrAccount">
                                <xsl:call-template name="AggAccountListTmpl">
                                    <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFProcResponse/Accounts"/>
                                </xsl:call-template>  
                            </xsl:when>
                            
                            <xsl:when test="/websrvXML/requestInfo/request/Data/UpdAggrBroker">
                                <xsl:call-template name="AggBrokerListTmpl">
                                    <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFProcResponse/Brokers"/>
                                </xsl:call-template>                    
                            </xsl:when>
                            
                            <xsl:when test="/websrvXML/requestInfo/request/Data/UpdAggrSalesRep">
                                <xsl:call-template name="AggSalesRepListTmpl">
                                    <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFProcResponse/SalesReps"/>
                                </xsl:call-template>                    
                            </xsl:when>
                            
                            <xsl:when test="/websrvXML/requestInfo/request/Data/UpdAggrAsset">
                                <xsl:call-template name="AggAssetListTmpl">
                                    <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFProcResponse/SubAdvisedAssets"/>
                                </xsl:call-template>                    
                            </xsl:when>
                            
                            <xsl:when test="/websrvXML/requestInfo/request/Data/UpdMFAccount">
                                <xsl:call-template name="AccountListTmpl">
                                    <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFProcResponse/Accounts"/>
                                </xsl:call-template>                    
                            </xsl:when>
                            
                            <xsl:when test="/websrvXML/requestInfo/request/Data/HistoryReq">
                                <xsl:call-template name="HistoryTmpl">
                                    <xsl:with-param name="sourceNode" select="/websrvXML/dtHoldingEntityMFProcResponse/UpdateHistory"/>
                                </xsl:call-template>                    
                            </xsl:when>
                            
                        </xsl:choose>
                        
                    </updatedHTML>        
                    
                </xsl:otherwise>
            
            </xsl:choose>
        </responseContents>
    </xsl:template>
        
    
</xsl:stylesheet>