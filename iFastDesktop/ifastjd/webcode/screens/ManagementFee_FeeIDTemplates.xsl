<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    

    <xsl:template name="FeeIDFundListTmpl">
        <xsl:param name="position"/>
        <xsl:param name="vURL"/>
        
        <xsl:variable name="fundId" select="uuid"/>
                
        <div>
            <xsl:attribute name="id">fundDiv_<xsl:value-of select="$fundId"/></xsl:attribute>
            <xsl:attribute name="selected">false</xsl:attribute>
            <xsl:attribute name="rcdStat"><xsl:value-of select="rcdStat"/></xsl:attribute>
            <xsl:attribute name="fund"><xsl:value-of select="fndCd"/></xsl:attribute>
            <xsl:attribute name="fundDesc"><xsl:value-of select="fundDesc"/></xsl:attribute>                     
            <xsl:attribute name="classCd"><xsl:value-of select="classCd"/></xsl:attribute>
            <xsl:attribute name="uuid"><xsl:value-of select="uuid"/></xsl:attribute>
            <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
            <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
            
            <div style="position:relative; left:20; width:720">                
                <xsl:element name="img">                    
                    <xsl:attribute name="src"><xsl:value-of select="$vURL"/>images/plus.png</xsl:attribute>                    
                    <xsl:attribute name="style">position:relative; top:2; left:1; cursor:pointer</xsl:attribute>
                    <xsl:attribute name="onclick">                        
                        togglePlusMinus( this ); 
                        toggleDiv( "fundRatesDiv_<xsl:value-of select="$fundId"/>" );
                        maintainFundHeight(); 
                        updateGrayDiv();                        
                    </xsl:attribute>
                </xsl:element>
                <span class="headerRow">
                    <xsl:attribute name="id">fundDesc_<xsl:value-of select="$fundId"/></xsl:attribute>                        
                    <xsl:attribute name="style">
                        cursor:pointer;
                        position:relative;
                        left:4;
                        top:-1;
                        font-weight:bold;                        
                        <xsl:if test="rcdStat = 'Active'">
                            color:black;
                        </xsl:if>
                        <xsl:if test="not( rcdStat = 'Active' )">
                            color:gray;
                        </xsl:if>                                                                                      
                    </xsl:attribute>                        
                    <xsl:attribute name="onclick">
                        fundDescClickHandler( "<xsl:value-of select="$fundId"/>", this );                                                          
                    </xsl:attribute>
                    <xsl:value-of select="fundDesc"/> <xsl:if test="not( rcdStat = 'Active' )">- <xsl:value-of select="rcdStat"/> (<xsl:value-of select="stopDate"/>)</xsl:if>
                </span>
            </div>
            <div style="display:none">
                <xsl:attribute name="id">fundRatesDiv_<xsl:value-of select="$fundId"/></xsl:attribute>
                             
                <xsl:call-template name="FeeIDRateListTmpl">
                    <xsl:with-param name="containerDivId">fundRatesDiv_<xsl:value-of select="$fundId"/></xsl:with-param>
                    <xsl:with-param name="fundId" select="$fundId"/>
                    <xsl:with-param name="sourceNode" select="MFTiers"/>
                    <xsl:with-param name="selectable">
                        <xsl:if test="rcdStat = 'Active'">yes</xsl:if>
                        <xsl:if test="not( rcdStat = 'Active' )">no</xsl:if>
                    </xsl:with-param>
                </xsl:call-template>
            </div>                      
        </div>   
    </xsl:template>
    
    
    <xsl:template name="FeeIDRateListTmpl">
        <xsl:param name="containerDivId"/>
        <xsl:param name="fundId"/>
        <xsl:param name="sourceNode"/>
        <xsl:param name="selectable"/>
        
        <xsl:variable name="tierSetCount">
            <xsl:value-of select="count( $sourceNode/MFTierSet )"/>
        </xsl:variable>
        
        <xsl:for-each select="$sourceNode/MFTierSet">
            
            <xsl:variable name="rateSetId"><xsl:value-of select="$fundId"/>_<xsl:value-of select="position()"/></xsl:variable>
            
            <xsl:variable name="mostRecent">
                <xsl:if test="position() = 1">yes</xsl:if>
                <xsl:if test="not( position() = 1 )">no</xsl:if>
            </xsl:variable>            

            <div>
                <xsl:attribute name="style">
                    <xsl:if test="$mostRecent = 'yes'">                        
                        display:block;
                    </xsl:if>
                    <xsl:if test="$mostRecent = 'no'">                        
                        display:none;
                    </xsl:if>
                </xsl:attribute>                
                                            
                <table style="table-layout:fixed; position:relative;">
                    <xsl:attribute name="id">rateSetTable_<xsl:value-of select="$rateSetId"/></xsl:attribute>
                    <xsl:attribute name="selected">false</xsl:attribute>
                    <xsl:attribute name="rateSetId"><xsl:value-of select="$rateSetId"/></xsl:attribute>
                    <xsl:attribute name="aggrLink"><xsl:value-of select="aggrLink"/></xsl:attribute>
                    <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                    <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
                    <xsl:attribute name="proDate"><xsl:value-of select="proDate"/></xsl:attribute>
                    <xsl:attribute name="onclick">
                        <xsl:if test="$mostRecent = 'yes' and $selectable = 'yes'">
                            rateSetClickHandler( "<xsl:value-of select="$fundId"/>", "<xsl:value-of select="$rateSetId"/>" );
                        </xsl:if>  
                    </xsl:attribute>                                
                    <thead>
                        <xsl:variable name="cursorType">
                            <xsl:if test="$mostRecent = 'yes'">pointer</xsl:if>
                            <xsl:if test="$mostRecent = 'no'">default</xsl:if>
                        </xsl:variable>
                        <tr>
                            <xsl:attribute name="style">
                                <xsl:if test="$mostRecent = 'no' or $selectable = 'no'">color:gray;</xsl:if>
                            </xsl:attribute>
                            <td style=" padding-top:5px; border-bottom:1px solid #e6e6e6; width:195; cursor:{$cursorType}">
                                [<xsl:value-of select="effDate"/> to <xsl:value-of select="stopDate"/>]                        
                            </td>
                            <td style="padding-left:5px; padding-top:5px; border-bottom:1px solid #e6e6e6; width:150; cursor:{$cursorType}">
                                <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
                                    User: <xsl:value-of select="user"/>
                                </span>
                            </td>
                            <td style=" padding-top:5px; border-bottom:1px solid #e6e6e6; width:160; cursor:{$cursorType}">                        
                                Proc.Date:  <xsl:value-of select="proDate"/>
                            </td>
                            <td style=" padding-top:5px; border-bottom:1px solid #e6e6e6; width:150; cursor:{$cursorType}">
                                <xsl:if test="aggrLink">
                                    <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
                                        Aggr.Link:<xsl:value-of select="aggrLink"/>
                                    </span>
                                </xsl:if>
                            </td>
                            <xsl:if test="$mostRecent = 'yes' and $tierSetCount &gt; 1">
                                <td style="width:80">                                
                                    <span style="width:80; position:relative; left:2; top:0; color:black;" align="right">
                                        <xsl:call-template name="ColorButtonTmpl">
                                            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                            <xsl:with-param name="id">modifyDescBtn</xsl:with-param>                                    
                                            <xsl:with-param name="size">small</xsl:with-param>
                                            <xsl:with-param name="width">80</xsl:with-param>
                                            <xsl:with-param name="text">Show Hist.</xsl:with-param>
                                            <xsl:with-param name="color">orange</xsl:with-param>
                                            <xsl:with-param name="onclick">toggleRatesHistory( "<xsl:value-of select="$containerDivId"/>", this);</xsl:with-param>
                                        </xsl:call-template>
                                    </span>                                                                                                                                      
                                </td>
                            </xsl:if>            
                        </tr> 
                    </thead>  
                    <tbody>          
                        <xsl:for-each select="MFTier">
                            <tr>
                                <xsl:attribute name="style">
                                    <xsl:if test="$mostRecent = 'no' or $selectable = 'no'">color:gray</xsl:if>
                                </xsl:attribute>
                                <xsl:attribute name="lowerBound"><xsl:value-of select="lower"/></xsl:attribute>
                                <xsl:attribute name="upperBound"><xsl:value-of select="upper"/></xsl:attribute>
                                <xsl:attribute name="rate"><xsl:value-of select="rate"/></xsl:attribute>                    
                                <td align="right" style="">
                                    <xsl:value-of select="lower"/>
                                </td>
                                <td align="center">
                                    -
                                </td> 
                                <td>
                                    <xsl:value-of select="upper"/>
                                </td>
                                <td align="left" style="">
                                    <xsl:value-of select="rate"/>
                                </td>
                            </tr>
                        </xsl:for-each>
                    </tbody>
                </table>
            </div>            
        </xsl:for-each>
    </xsl:template>
    
    
    
    
    
    
    
    <xsl:template match="FundHistory">
		<div>
			<xsl:for-each select="Fund">			
				<div style="width:100%; padding-left:5; padding-bottom:15" >
					 <div style="width:100%; height:20" onclick="toggleHistoryDetailsDisplay(this);">
						 <img src="{$vURL}images/plus.png" style="position:relative; top:2; left:1; cursor:pointer; "/>
						 <span style="border-bottom:2px solid #FFD696; font-weight:bold; position:relative; left:5px;cursor:pointer;"><xsl:value-of select="fundDesc"/></span>
					 </div>
					 <div style="display:none;">
						 <xsl:for-each select="FundUpdates/FundUpdate">
							 <div style="width:100%; padding-bottom:5">
								 <div style="width:100%">
									 <span style="width:100; font-weight:bold; text-transform:uppercase"><xsl:value-of select="updType"/></span>									 
									 <span style="width:170"><xsl:value-of select="updDate"/> (<xsl:value-of select="updTime"/>)</span>
									 <span style="width:50; font-weight:bold;">User:</span>
									 <span style="width:120"><xsl:value-of select="userName"/></span>
								</div>
								<div style="padding-left:100">
									<div>
										<div>
											<span style="width:70; font-weight:bold;">Eff.Date:</span>
											<span style="width:100"><xsl:value-of select="effDate"/></span>									
											<xsl:if test="aggrLink">
												<span style="width:80; font-weight:bold;">Aggr.Link:</span>
												<span style="width:60"><xsl:value-of select="aggrLink"/></span>
											</xsl:if>
										</div>
										<xsl:if test="stopDate">
											<div>
												<span style="width:78; font-weight:bold;">StopDate:</span>
												<span style="width:100"><xsl:value-of select="stopDate"/></span>		
											</div>
										</xsl:if>
										<xsl:if test="TierSet/Tier">
											<div>
												<span style="width:55; font-weight:bold; float:left;">Rates:</span>
												<span style="">	
													<table cellpadding="0" cellspacing="0">
														<xsl:for-each select="TierSet/Tier">
															<tr>
																<td style="width:120"><xsl:value-of select="lower"/></td>
																<td style="width:20; text-align:left">-</td>
																<td style="width:120"><xsl:value-of select="upper"/></td>
																<td style="width:100; text-align:right"><xsl:value-of select="rate"/></td>
															</tr>
														</xsl:for-each>
													</table>
												</span>
											</div>
										</xsl:if>
									</div>
								</div>
							</div>
						</xsl:for-each>
					</div>
				</div>
			</xsl:for-each>
		</div>
    </xsl:template>

</xsl:stylesheet>