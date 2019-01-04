<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />

  <xsl:template match="/">

  <Screen>
    <responseContents>


      <div class = "boxBackground" style="position:absolute; left:0; top:0; height:100%; width:100%; border:1px solid #D3D3D3; overflow:scroll;">
          <xsl:element name="table">
          <xsl:attribute name="id">accountList</xsl:attribute>
          <xsl:attribute name="cellpadding">1</xsl:attribute>
          <xsl:attribute name="cellspacing">0</xsl:attribute>
          <xsl:attribute name="style">cursor:default;</xsl:attribute>
          <xsl:attribute name="class">boxBackground</xsl:attribute>
          <xsl:attribute name="width">1455px</xsl:attribute>
          <xsl:attribute name="requestRecNum"><xsl:value-of select="//Data/requestRecNum"/></xsl:attribute>
            <tr class="fixedHeader tableFont" style="height:28px">
              <th class="grid" width="100px" align="left">Fund Sponsor</th>
              <th class="grid" width="80px" align="left">Fund</th>
              <th class="grid" width="50px" align="left">Class</th>
              <th class="grid" width="150px" align="left">Fund Group</th>
              <th class="grid" width="200px" align="left">Rule Type</th>
              <th class="grid" width="125px" align="left">Start Date</th>
              <th class="grid" width="125px" align="left">Stop Date</th>
              <th class="grid" width="125px" align="left">Override Amount</th>
              <th class="grid" width="100px" align="left">Applicable</th>
              <th class="grid" width="100px" align="left">Online EWI</th>
              <th class="grid" width="100px" align="left">Cycle EWI</th>
              <th class="grid" width="100px" align="left">ESG EWI</th>
              <th class="grid" width="125px" align="left">Status</th>

              <!-- Items not for display  ..... -->
              <th style="display:none">Rule Type</th>
              <th style="display:none">ControlsID</th>
              <th style="display:none">overridelog</th>
              <th style="display:none">overrideamt</th>
              <th style="display:none">overridechar</th>
              <th style="display:none">Version</th>
              <th style="display:none">ModDate</th>
              <th style="display:none">ProcessDate</th>
              <th style="display:none">ModUser</th>
              <th style="display:none">UserName</th>

            </tr>

            <xsl:for-each select="//RuleDetail/*">
              <xsl:element name="tr">
                <xsl:attribute name="id">row<xsl:value-of select="position()"/></xsl:attribute>
                <xsl:attribute name="accountNumber"><xsl:value-of select="Account"/></xsl:attribute>
                <xsl:attribute name="onclick">onAccountSelect(this);</xsl:attribute>
                <xsl:attribute name="onkeydown">addHandleOnKeydown( this, "accountList" );</xsl:attribute>
                <xsl:attribute name="class">tableFont boxBackground</xsl:attribute>

                <td class="grid" align="left" name="fundSponsor"><xsl:value-of select="fundSponsor"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="fund"><xsl:value-of select="Fund"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="class"><xsl:value-of select="Class"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="class"><xsl:value-of select="FundGroup"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="ruleDesc"><xsl:value-of select="ruleDesc"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="startDateChar"><xsl:value-of select="startDateChar"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="stopDateChar"><xsl:value-of select="stopDateChar"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="dispAmt"><xsl:value-of select="dispAmt"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="overridelog"><xsl:value-of select="OverrideLog"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="onlineewi"><xsl:value-of select="OnlineEWI"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="cycleewi"><xsl:value-of select="CycleEWI"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="esgewi"><xsl:value-of select="ESGEWI"/><xsl:text></xsl:text></td>
                <td class="grid" align="left" name="status"><xsl:value-of select="status"/><xsl:text></xsl:text></td>

                <!-- Items not for display .... -->
                <td style="display:none" name="ruleType"><xsl:value-of select="RuleType"/><xsl:text></xsl:text></td>
                <xsl:choose>
                  <xsl:when test="//FormInformation/option= 'account'">
                    <td style="display:none" name="controlsid"><xsl:value-of select="AcctControlsID"/><xsl:text></xsl:text></td>
                  </xsl:when>
                  <xsl:otherwise>
                    <td style="display:none" name="controlsid"><xsl:value-of select="BrokerControlsID"/><xsl:text></xsl:text></td>
                  </xsl:otherwise>
                </xsl:choose>
                <td style="display:none" name="overridelog"><xsl:value-of select="OverrideLog"/><xsl:text></xsl:text></td>
                <td style="display:none" name="overrideamt"><xsl:value-of select="OverrideAmt"/><xsl:text></xsl:text></td>
                <td style="display:none" name="overridechar"><xsl:value-of select="OverrideChar"/><xsl:text></xsl:text></td>
                <td style="display:none" name="version"><xsl:value-of select="Version"/><xsl:text></xsl:text></td>
                <td style="display:none" name="modeDate"><xsl:value-of select="ModDate"/><xsl:text></xsl:text></td>
                <td style="display:none" name="processDate"><xsl:value-of select="ProcessDate"/><xsl:text></xsl:text></td>
                <td style="display:none" name="moduser"><xsl:value-of select="ModUser"/><xsl:text></xsl:text></td>
                <td style="display:none" name="username"><xsl:value-of select="UserName"/><xsl:text></xsl:text></td>
              </xsl:element>
            </xsl:for-each>
          </xsl:element>
        </div>


    </responseContents>
  </Screen>

  </xsl:template>

</xsl:stylesheet>
