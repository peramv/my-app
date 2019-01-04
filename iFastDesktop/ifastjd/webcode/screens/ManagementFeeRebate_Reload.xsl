<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>  
    
    <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/' )"/>
    <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
    <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>          
    <xsl:variable name="vTIDX"         select="/websrvXML/FormInformation/tidx"/>
    
    
    
    <xsl:template match="/">
        <responseContents>
            <xsl:choose>
                <xsl:when test="/websrvXML/dtMFRModelListReloadResponse/RequestStatus/Errors">
                    <error>
                        <xsl:value-of select="//websrvXML/dtMFRModelListReloadResponse/RequestStatus/Errors/Error/text"/>
                    </error>
                </xsl:when>
                
                <xsl:otherwise>
                    <updatedHTML>    
                        <div>
                           <xsl:variable name="MFRModelCount"><xsl:value-of select="count(/websrvXML/dtMFRModelListReloadResponse/MFRModels/MFRModel)"/></xsl:variable>                    
                            <xsl:for-each select="/websrvXML/dtMFRModelListReloadResponse/MFRModels/MFRModel">
                                <xsl:variable name="MFRModelCode"><xsl:value-of select="MFRModelCode"/></xsl:variable>
                                <div style="padding-bottom:5px">
                                    <div style="position:relative; left:20; width:400;">
                                        <div style="cursor:pointer;">                                                                                                          
                                            <xsl:choose>
													<xsl:when test="$MFRModelCount &gt; 10">
														<img src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer;">
															<xsl:attribute name="onclick">toggleDiv( "<xsl:value-of select="$MFRModelCode"/>_ListDiv" ); togglePlusMinus( this );</xsl:attribute>
														</img>
													</xsl:when>
													<xsl:otherwise>
														<img src="{$vURL}images/minus.png" style="position:relative; top:2; left: 1; cursor:pointer;">
															<xsl:attribute name="onclick">toggleDiv( "<xsl:value-of select="$MFRModelCode"/>_ListDiv" ); togglePlusMinus( this );</xsl:attribute>
														</img>
													</xsl:otherwise>
											</xsl:choose>
                                             
											 <span style="padding-left:3px; font-weight:bold">
												 <xsl:attribute name="onclick">launchDetails( "<xsl:value-of select="$MFRModelCode"/>" );</xsl:attribute>
											     <xsl:value-of select="$MFRModelCode"/>  -  <xsl:value-of select="translate( ModelDesc, '&#xa;', ' ' )"/> <span style="padding-left:10px;"><xsl:value-of select="ModelType"/></span>
											</span>                                     
                                        </div>
                                    </div>
                                    
									  <div style="width:98%; position:relative; top:-24" align="right">
										<div style="cursor:pointer; position:absolute; top:10; left:620; width:70; height:15; overflow:hidden;" align="center">
											<xsl:call-template name="ColorButtonTmpl">
												<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                                               
												<xsl:with-param name="id"></xsl:with-param>
												<xsl:with-param name="onclick">launchDetails( "<xsl:value-of select="$MFRModelCode"/>" );</xsl:with-param>
												<xsl:with-param name="size">small</xsl:with-param>
												<xsl:with-param name="width">70</xsl:with-param>
												<xsl:with-param name="text">Details</xsl:with-param>
												<xsl:with-param name="color">orange</xsl:with-param>
											</xsl:call-template>   
										</div>									  	                                      
									</div>
                                    
                                    <div >
                                        <xsl:attribute name="style">
											<xsl:choose>
												<xsl:when test="$MFRModelCount &gt; 10">display:none;</xsl:when>
												<xsl:otherwise>display:block</xsl:otherwise>
											</xsl:choose>
										</xsl:attribute>
                                        <xsl:attribute name="id"><xsl:value-of select="$MFRModelCode"/>_ListDiv</xsl:attribute>
                                        
                                        <table style="position:relative; left:10; table-layout:fixed">
                                            <xsl:for-each select="Accounts/Account">
                                                <tr>
                                                    <td style="width:75px; text-align:right">
                                                        <xsl:value-of select="acctNum"/>
                                                    </td>
                                                    <td style="width:10;"> - </td>
                                                    <td style="width:350; text-align:left">
                                                        <span style="width:350; text-overflow:ellipsis; overflow:hidden;"><xsl:value-of select="ownerName"/></span> 
                                                    </td>
                                                    <td style="width:130px">
                                                        <xsl:value-of select="taxType"/>
                                                    </td>                                    
                                                	<td style="width:60px">
                                                		<xsl:value-of select="gbcd"/>
                                                	</td>
                                                </tr>                                
                                            </xsl:for-each>
                                        </table>
                                    </div>
                               </div>
                            </xsl:for-each>
                        </div>    
                    </updatedHTML>
                </xsl:otherwise>
            </xsl:choose>
        </responseContents>
    </xsl:template>
</xsl:stylesheet>
