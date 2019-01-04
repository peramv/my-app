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
  
  <!-- ============= MAIN TEMPLATE - start ============== -->
  <xsl:template match="/">
    <responseInfo>
      <responseNode>.//responseHTML/*</responseNode>
      <headers>
        <header>
          <name>Content-Type</name>
          <value>text/html</value>
        </header>
        <header>
          <name>Cache-Control</name>
          <value>no-cache</value>
        </header>
      </headers>
      <responseHTML>
        <html>
          <head>
            <title>Fund Suggest Test</title>
            
            <script src="{$vURL}javascript/XML_Lib.js">
              // comment. pls keep
            </script>
            <script src="{$vURL}javascript/FundSuggest.js">
              // comment. pls keep
            </script>
            
            <script>
              var _fundSuggest = null;
              function loading()
              {                                       
                _fundSuggest = new FundSuggest('<xsl:value-of select="$vURL"/>' + 'images');
              }      
            </script>
          </head>
          <body onload="loading();">
            <input id="inputbox" type="text" style="position:absolute; top:150;left:150; width:300;" onfocus="_fundSuggest.init(this)" />        
          </body>
        </html>
       </responseHTML>
      </responseInfo>
  </xsl:template>


</xsl:stylesheet>

