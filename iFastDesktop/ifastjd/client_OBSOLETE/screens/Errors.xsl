<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />
  
<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}client/screens/MasterLayout.xsl"/>
  
  
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
    
    <xsl:call-template name="master_layout">
      <xsl:with-param name="pageTitle">Error</xsl:with-param>
      <xsl:with-param name="displayTitle">false</xsl:with-param>
    </xsl:call-template>
    
  </xsl:template>
  
  <!-- ========================== FORM CALLBACK TEMPLATE - start ========================== -->
  <xsl:template name="form_callback">
    
    <center><font size="3">There is an internal problem. Contact a support
                           representative and report this message. </font></center><xsl:value-of select="//FormInformation/ErrorCode"/>
    
  </xsl:template>
  
  <!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >
    
  </xsl:template>
  
  
</xsl:stylesheet>
  