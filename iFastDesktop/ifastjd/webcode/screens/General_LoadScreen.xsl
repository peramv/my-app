<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/MasterLayout.xsl"/>

  <!-- CLIENT & PATH VARIABLES - start -->
  <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/')"/>
  <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
  <xsl:variable name="vTIDX"         select="/websrvXML/FormInfomation/tidx"/>
  <!-- CLIENT & PATH VARIABLES - end -->


  <xsl:template match="/">

    <Screen>
      <html>

      <img src="{$vURL}images/General_Loading.gif"/>

      </html>
    </Screen>
  </xsl:template>

</xsl:stylesheet>
