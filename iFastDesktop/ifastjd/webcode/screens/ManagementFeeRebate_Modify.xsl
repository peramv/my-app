<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/ManagementFee_ButtonTemplate.xsl"/>
    
    <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/' )"/>
    <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
    <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>          
    <xsl:variable name="vTIDX"         select="/websrvXML/FormInformation/tidx"/>
    
    <xsl:template match="/">
        
        <Screen>
            
            <html>
                <title>Management Fee Rebates - Details</title>
                
                <head>
                    <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"></link>    
                    
                </head>
                
                <body>
                    <div style="width:350px; border:1px solid #DBE5F7;">
                        <div style="width:100%">
                            <div style="width:100%; padding-bottom:10px">
                                <span>MFR1234 - Doe Family</span>
                                <span style="padding-left:30px">
                                    <xsl:call-template name="ButtonTmpl">                                            
                                        <xsl:with-param name="onclick">alert();</xsl:with-param>
                                        <xsl:with-param name="size">small</xsl:with-param>
                                        <xsl:with-param name="width">75</xsl:with-param>
                                        <xsl:with-param name="text">modify</xsl:with-param>
                                        <xsl:with-param name="color">orange</xsl:with-param>
                                    </xsl:call-template>
                                 </span>
                            </div>
                            
                            <div style="width:100%; padding-left:10px; padding-bottom:10px">
                                <table style="positon:relative; left:20px;">
                                    <tr>
                                        <td>Account:</td>
                                        <td>102345</td>
                                    </tr>
                                    <tr>
                                        <td>Effective Date:</td>
                                        <td><input type="text" size="20"/></td>
                                    </tr>
                                    <tr>
                                        <td>Frequency:</td>
                                        <td><input type="text" size="20"/></td>
                                    </tr>
                                </table>
                            </div>
                            
                            <div style="width:100%; text-align:right;">
                                <xsl:call-template name="ButtonTmpl">                                            
                                    <xsl:with-param name="onclick">alert();</xsl:with-param>
                                    <xsl:with-param name="size">small</xsl:with-param>
                                    <xsl:with-param name="width">75</xsl:with-param>
                                    <xsl:with-param name="text">save</xsl:with-param>
                                    <xsl:with-param name="color">green</xsl:with-param>
                                </xsl:call-template>
                                <xsl:call-template name="ButtonTmpl">                                            
                                    <xsl:with-param name="onclick">window.history.back();</xsl:with-param>
                                    <xsl:with-param name="size">small</xsl:with-param>
                                    <xsl:with-param name="width">75</xsl:with-param>
                                    <xsl:with-param name="text">cancel</xsl:with-param>
                                    <xsl:with-param name="color">red</xsl:with-param>
                                </xsl:call-template>
                            </div>                                                
                        </div>
                    </div>    
                </body>
                
            </html>
        </Screen>
        
    </xsl:template>
</xsl:stylesheet>