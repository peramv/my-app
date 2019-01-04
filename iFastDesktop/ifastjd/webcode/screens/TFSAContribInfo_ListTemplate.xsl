<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:template name="TFSAContribInfoList_Tmpl">
        <xsl:param name="listSrc"/>
        
        <table id="ContribInfoListTable" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true">
            <thead id="ContribInfoListTable_head">
                <tr>
                    <td align="center" style="width:160;" columnWidth="160">
                        Year
                    </td>
                    <td align="center" style="width:160;" columnWidth="160">	
                        YTD Contribution
                    </td>
                    <td align="center" style="width:160;" columnWidth="160">	
                        YTD Withdrawal
                    </td>
                    <td align="center" style="width:160;" columnWidth="160">	
                        LTD Contribution
                    </td>
                    <td align="center" style="width:160;" columnWidth="160">	
                        LTD Withdrawal
                    </td>
                </tr>
            </thead>					
            <tbody id="ContribInfoListTable_body">
            
            	<xsl:choose>
            		<xsl:when test="$listSrc/AcctContrib">            	
            			<xsl:for-each select="$listSrc/AcctContrib">
            				<tr>
            					<td>
            						<xsl:attribute name="title">
            							<xsl:value-of select="Deff"/>
            						</xsl:attribute>
            						<xsl:attribute name="data">
            							<xsl:value-of select="Deff"/>
            						</xsl:attribute>
            						<span class="Desktop_Table_Data Right_Align">
            							<xsl:value-of select="Deff"/>
            						</span>
            					</td>
            					<td>
            						<xsl:attribute name="title">
            							<xsl:value-of select="ytmContrib"/>
            						</xsl:attribute>
            						<xsl:attribute name="data">
            							<xsl:value-of select="ytmContrib"/>
            						</xsl:attribute>
            						<span class="Desktop_Table_Data Right_Align">
            							<xsl:value-of select="ytmContrib"/>
            						</span>
            					</td>
            					<td>
            						<xsl:attribute name="title">
            							<xsl:value-of select="ytmWithdrawal"/>
            						</xsl:attribute>
            						<xsl:attribute name="data">
            							<xsl:value-of select="ytmWithdrawal"/>
            						</xsl:attribute>
            						<span class="Desktop_Table_Data Right_Align">
            							<xsl:value-of select="ytmWithdrawal"/>
            						</span>
            					</td>
            					<td>
            						<xsl:attribute name="title">
            							<xsl:value-of select="ltdContrib"/>
            						</xsl:attribute>
            						<xsl:attribute name="data">
            							<xsl:value-of select="ltdContrib"/>
            						</xsl:attribute>
            						<span class="Desktop_Table_Data Right_Align">
            							<xsl:value-of select="ltdContrib"/>
            						</span>
            					</td>
            					<td>
            						<xsl:attribute name="title">
            							<xsl:value-of select="ltdWithdrawal"/>
            						</xsl:attribute>
            						<xsl:attribute name="data">
            							<xsl:value-of select="ltdWithdrawal"/>
            						</xsl:attribute>
            						<span class="Desktop_Table_Data Right_Align">
            							<xsl:value-of select="ltdWithdrawal"/>
            						</span>
            					</td>	
            				</tr>	
            			</xsl:for-each>	
            		</xsl:when>
            		
            		<xsl:otherwise>
            			<tr>
            				<td style="font-style:italic; text-align:center; padding-top:5px;" colspan="5">
            					No contribution data found for this account
            				</td>            				    			
            			</tr>	
            		</xsl:otherwise>	
            			
            	</xsl:choose>                
                                                            
            </tbody>                			
        </table>	        
        
    </xsl:template>
    
</xsl:stylesheet>   

	        