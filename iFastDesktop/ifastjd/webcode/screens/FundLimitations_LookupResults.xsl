<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />

  <xsl:template match="/">

  <Screen>
    <responseContents>
      <!--xsl:copy-of select="//PendingUpdateList"/-->

      <xsl:choose>
        <xsl:when test=".//Errors">
            <error><xsl:value-of select=".//Errors/Error/text"/></error>
        </xsl:when>
        <xsl:otherwise>

          <newRuleCount><xsl:value-of select="count(//PendingUpdateList/PendingUpdateDetail/t-FundsToUpd/UpdType[. = 'New'])"/></newRuleCount>
          <stoppedRuleCount><xsl:value-of select="count(//PendingUpdateList/PendingUpdateDetail/t-FundsToUpd/UpdType[. = 'stopped'])"/></stoppedRuleCount>
          <div id="ruleListDiv" class="boxBackground" style="position:absolute; left:0; top:0; height:100%; width:100%; border:1px solid #D3D3D3; overflow:scroll;">
            <table id="ruleList" cellpadding="1" cellspacing="0" style="cursor:default" width="1605px">

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
                <th class="grid" width="125px" align="left">Online EWI</th>
                <th class="grid" width="125px" align="left">Cycle EWI</th>
                <th class="grid" width="125px" align="left">ESG EWI</th>
                <th class="grid" width="125px" align="left">Status</th>
                <th class="grid" align="left" style="display:none">controlsid</th>
                <th class="grid" align="left" style="display:none">version</th>
                <th class="grid" align="left" style="display:none">overrideamt</th>
              </tr>


              <xsl:for-each select=".//PendingUpdateList/PendingUpdateDetail/t-FundsToUpd">
                <xsl:element name="tr">
                <xsl:attribute name="id">row<xsl:value-of select="position()"/></xsl:attribute>
                <xsl:attribute name="onclick">_currentRow = Number(this.id.substr(3, (this.id.length-3))); onRuleSelect(this);</xsl:attribute>
                <xsl:attribute name="onkeydown">addHandleOnKeydown( "ruleListDiv" );</xsl:attribute>
                <xsl:attribute name="class">boxBackground</xsl:attribute>

                  <td class="grid tableFont" align="left" name="Fund"><xsl:value-of select="FundSponsor"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="Fund"><xsl:value-of select="Fund"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="Class"><xsl:value-of select="Class"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="FundGroup"><xsl:value-of select="FundGroup"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="ruleDesc"><xsl:value-of select="ruleDesc"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="StartDate"><xsl:value-of select="StartDate"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="StopDate"><xsl:value-of select="StopDate"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="OverrideAmt"><xsl:value-of select="dispamt"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="OverrideLog"><xsl:value-of select="OverrideLog"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="onlineewi"><xsl:value-of select="OnlineEWI"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="cycleewi"><xsl:value-of select="CycleEWI"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="esgewi"><xsl:value-of select="ESGEWI"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="status"><xsl:value-of select="UpdType"/><xsl:text></xsl:text></td>
                  <td class="grid tableFont" align="left" name="controlsid" style="display:none"><xsl:value-of select="ControlsID"/></td>
                  <td class="grid tableFont" align="left" name="version" style="display:none"><xsl:value-of select="Version"/></td>
                  <td class="grid tableFont" align="left" name="overrideamt" style="display:none"><xsl:value-of select="OverrideAmt"/><xsl:text></xsl:text></td>

                </xsl:element>
              </xsl:for-each>
            </table>
          </div>

        </xsl:otherwise>
      </xsl:choose>
    </responseContents>
  </Screen>

  </xsl:template>

</xsl:stylesheet>
