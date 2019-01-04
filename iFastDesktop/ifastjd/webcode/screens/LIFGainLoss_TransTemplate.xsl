<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes"/>

    <xsl:template match="transactionList">
        <xsl:param name="UpdAllowed"/>
        
        <table id="TransTable" cellpadding="0" cellspacing="0" style="table-layout:fixed">
            <thead>
                <tr>                                       
                    <td class="TranTable_header" style="width:100">Trans Num</td>
                    <td class="TranTable_header" style="width:82">Eff Date</td>
                    <td class="TranTable_header" style="width:82">Sett Date</td>
                    <td class="TranTable_header" style="width:300">Deposit Type</td>
                    <td class="TranTable_header" style="width:146">Gross Amt</td>
                    <td class="TranTable_header" style="width:189">Gain/Loss</td>
                </tr>
            </thead>            	        		
            <tbody>
                <xsl:if test="count( Transaction ) = 0">
                    <tr>
                        <td colspan="8" style="text-align:center; font-style:italic; padding-top:10px">
                            <span>No transaction records available</span>
                        </td>
                    </tr>
                </xsl:if>
                <xsl:if test="count( Transaction ) &gt; 0">
                    <xsl:for-each select="Transaction">
                        <xsl:variable name="rowIndex"><xsl:value-of select="position() - 1"/></xsl:variable>
                        <tr>                            
                            <!-- TRANSACTION NUM -->
                            <td class="TransTable_cell">
                                <xsl:attribute name="txnNum">
                                    <xsl:value-of select="txnNum"/>
                                </xsl:attribute>
                                <xsl:attribute name="title">
                                    <xsl:value-of select="txnNum"/>
                                </xsl:attribute>
                                <span class="TransTable_data">
                                    <xsl:value-of select="txnNum"/>
                                </span>
                            </td>
                            <!-- EFF DATE -->
                            <td class="TransTable_cell">
                                <xsl:attribute name="deff">
                                    <xsl:value-of select="deff"/>
                                </xsl:attribute>
                                <xsl:attribute name="title">
                                    <xsl:value-of select="deff"/>
                                </xsl:attribute>
                                <span class="TransTable_data">
                                    <xsl:value-of select="deff"/>
                                </span>
                            </td>
                            <!-- SETT DATE -->
                            <td class="TransTable_cell">
                                <xsl:attribute name="setDt">
                                    <xsl:value-of select="setDt"/>
                                </xsl:attribute>
                                <xsl:attribute name="title">
                                    <xsl:value-of select="setDt"/>
                                </xsl:attribute>
                                <span class="TransTable_data">
                                    <xsl:value-of select="setDt"/>
                                </span>
                            </td>
                            <!-- DEPOSIT TYPE -->
                            <td class="TransTable_cell">
                                <xsl:attribute name="depTyp">
                                    <xsl:value-of select="depTyp"/>
                                </xsl:attribute>
                                <xsl:attribute name="title">
                                    <xsl:value-of select="depTyp"/>-<xsl:value-of select="depTypDesc"/>
                                </xsl:attribute>
                                <span class="TransTable_data">
                                    <xsl:value-of select="depTyp"/>-<xsl:value-of select="depTypDesc"/>
                                </span>
                            </td>
                            <!-- GROSS AMT -->
                            <td class="TransTable_cell">
                                <xsl:attribute name="grossAmt">
                                    <xsl:value-of select="grossAmt"/>
                                </xsl:attribute>
                                <xsl:attribute name="title">
                                    <xsl:value-of select="grossAmt"/>
                                </xsl:attribute>
                                <span class="TransTable_data">
                                    <xsl:value-of select="grossAmt"/>
                                </span>
                            </td>
                            <!-- GAIN/LOSS -->
                            <td class="TransTable_cell">	        		
                                <xsl:attribute name="gainLoss">
                                    <xsl:value-of select="gainLoss"/>
                                </xsl:attribute>	
                                <xsl:attribute name="title">
                                    <xsl:value-of select="gainLoss"/>
                                </xsl:attribute>					
                                <span style="padding-right:3px; width:142px;">
                                    <xsl:value-of select="gainLoss"/>
                                </span>
                                <xsl:if test="$UpdAllowed = 'yes'">
                                    <input type="button" value="update" class="UpdateBtn" onclick="displayUpdatePopup( {$rowIndex} )"/>
                                </xsl:if>                                    
                            </td>
                        </tr>	        		
                    </xsl:for-each>
                </xsl:if>                                                  
            </tbody>
        </table>
    </xsl:template>
    
</xsl:stylesheet>