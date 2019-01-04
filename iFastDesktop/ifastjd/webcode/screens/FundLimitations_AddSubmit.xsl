<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />

    <xsl:template match="/">
      <Screen>
        <responseContents>
          <xsl:choose>
            <xsl:when test=".//RuleErrorList">
              <responseStatus>errors</responseStatus>
              <errorDisp>
                <div class="boxBackground" style="position:absolute; left:0; top:0; height:100%; width:100%; border:1px solid #D3D3D3; overflow:scroll;">
                  <table id="ruleList" cellpadding="1" cellspacing="0" style="cursor:default" width="1455px">
                    <tr class="fixedHeader tableFont" style="height:28px">
                      <th class="grid" width="100" align="left">Fund Sponsor</th>
                      <th class="grid" width="80" align="left">Fund</th>
                      <th class="grid" width="50" align="left">Class</th>
                      <th class="grid" width="150px" align="left">Fund Group</th>
                      <th class="grid" width="200" align="left">Rule Type</th>
                      <th class="grid" width="125" align="left">Start Date</th>
                      <th class="grid" width="125" align="left">Stop Date</th>
                      <th class="grid" width="125" align="left">Override Amount</th>
                      <th class="grid" width="100" align="left">Applicable</th>
                      <th class="grid" width="100" align="left">Online EWI</th>
                      <th class="grid" width="100" align="left">Cycle EWI</th>
                      <th class="grid" width="100" align="left">ESG EWI</th>
                      <th class="grid" width="125" align="left">Status</th>
                    </tr>

                    <xsl:for-each select=".//RuleErrorList/tPendingRule">
                      <xsl:element name="tr">
                        <xsl:attribute name="class">tableFontError</xsl:attribute>
                        <td class="grid" align="left" name="fund"><xsl:value-of select="fundSponsor"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="fund"><xsl:value-of select="fund"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="class"><xsl:value-of select="class"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="class"><xsl:value-of select="fundgroup"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="ruleDesc"><xsl:value-of select="ruleDesc"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="startDate"><xsl:value-of select="startDateChar"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="stopDate"><xsl:value-of select="stopDateChar"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="dispAmt"><xsl:value-of select="dispAmt"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="stopFlag"><xsl:value-of select="overrideLog"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="onlineewi"><xsl:value-of select="onlineEWI"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="cycleewi"><xsl:value-of select="cycleEWI"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="esgewi"><xsl:value-of select="esgEWI"/><xsl:text></xsl:text></td>
                        <td class="grid" align="left" name="status"><xsl:value-of select="updateStatus"/>: <xsl:value-of select="errorDesc"/><xsl:text></xsl:text></td>
                      </xsl:element>
                    </xsl:for-each>
                  </table>
                </div>
              </errorDisp>
            </xsl:when>
            <xsl:otherwise>
                <responseStatus>accepted</responseStatus>
            </xsl:otherwise>
          </xsl:choose>
        </responseContents>
      </Screen>

    </xsl:template>

</xsl:stylesheet>