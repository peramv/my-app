<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    
    <xsl:template name="AccountBalanceListTmpl">
        <xsl:param name="sourceNode"/>
        
        <xsl:choose>
            <xsl:when test="$sourceNode/AccountBalance">                
                <table id="accountBal_ListContentsTable" cellpadding="0" cellspacing="0" style="table-layout:fixed">
                    <xsl:for-each select="$sourceNode/AccountBalance">
                        <tr>
                            <xsl:attribute name="acctNum"><xsl:value-of select="acctNum"/></xsl:attribute>
							<xsl:attribute name="acctRowID"><xsl:value-of select="acctRowID"/></xsl:attribute>
                            <xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
                            <xsl:attribute name="fundCode"><xsl:value-of select="fundCode"/></xsl:attribute>                            
                            <xsl:attribute name="classCode"><xsl:value-of select="classCode"/></xsl:attribute>                            
                            <xsl:attribute name="bayCom"><xsl:value-of select="bayCom"/></xsl:attribute>                            
                            <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                            <xsl:attribute name="units"><xsl:value-of select="units"/></xsl:attribute>
                            <xsl:attribute name="fundRowID"><xsl:value-of select="fundRowID"/></xsl:attribute>
                            <xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
                            <xsl:attribute name="updAllowed"><xsl:value-of select="UpdAllowed"/></xsl:attribute>
                            <xsl:attribute name="onclick">
                                selectRow( this );
                            </xsl:attribute>
                                                                    
                            <td style="width:125px;">
								<xsl:attribute name="title"><xsl:value-of select="acctNum"/></xsl:attribute>
								<xsl:value-of select="acctNum"/>
							</td>
                            <td style="width:175px;">                            
   								<xsl:attribute name="title"><xsl:value-of select="name"/></xsl:attribute>
								<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis"><xsl:value-of select="name"/></span>
							</td>                            
                            <td style="width:150px;">
   								<xsl:attribute name="title"><xsl:value-of select="effDate"/></xsl:attribute>
								<xsl:value-of select="effDate"/>
							</td>
                            <td style="width:125px;">
								<xsl:attribute name="title"><xsl:value-of select="fundCode"/> - <xsl:value-of select="classCode"/></xsl:attribute>
								<xsl:value-of select="fundCode"/> - <xsl:value-of select="classCode"/>
							</td>                            
                            <td style="width:100px;">
                            	<xsl:attribute name="title"><xsl:value-of select="units"/></xsl:attribute>
								<xsl:value-of select="units"/>
							</td>
                        </tr>
                    </xsl:for-each>
                </table>
            </xsl:when>
            <xsl:otherwise>
                <span style="width:100%; text-align:center; color:gray; font-style:italic">No matching records.</span>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
</xsl:stylesheet>