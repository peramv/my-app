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
  <!-- Init Values -->

  <!-- End Init Values -->

  <xsl:template match="/">

    <xsl:call-template name="master_layout">
      <xsl:with-param name="pageTitle">Payment Release</xsl:with-param>
      <xsl:with-param name="displayTitle">false</xsl:with-param>
    </xsl:call-template>

  </xsl:template>

  <!-- ========================== FORM CALLBACK TEMPLATE - start ========================== -->
  <xsl:template name="form_callback">

    <script src="{$vURL}javascript/General_Base.js">
      // comment. pls keep
    </script>
    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>
    <script src="{$vURL}javascript/PaymentRelease.js">
      // comment. pls keep
    </script>
    
    
    
    
    <input type="hidden" id="batchId">
      <xsl:attribute name="value">
        <xsl:value-of select="//FormInformation/batchId"/>
      </xsl:attribute>
    </input>
    
    <table style="width:260;">
      <tr style="height:40">
        <td colspan="4">
          <input id="runNow" TYPE="radio" VALUE="now" NAME="schedRuntime" checked="true" onfocus='disableSchedulingOptions();'/>Run Now
          <input TYPE="radio" VALUE="schedule" NAME="schedRuntime" onfocus='enableSchedulingOptions();'/>Schedule
        </td>
      </tr>
      <tr style="height:40;">
        <td>
          Run On: 
        </td>   
        <td style="width:120px;">

          <input id="dateField" class="dstdatepicker" type="text" disabled="true" style="width:100">
            <xsl:attribute name="value">
              <xsl:value-of select="//runOn"/>                 
            </xsl:attribute>
          </input>  
        </td>   
        <td>  
          at     
        </td>   
        <td>
          <input id="timeField" disabled="true" style="width:50">
            <xsl:attribute name="value">
              <xsl:value-of select="//runTime"/>                 
            </xsl:attribute>
          </input>
        </td>
      </tr>
      <tr style="height:40">
        <td colspan="4" align="right">
          <input style="width:80" type="button" value="OK" onclick="submitSchedule();"/>
          <input style="width:80" type="button" value="Cancel" onclick="history.back()"/>
        </td>
      </tr>
    </table>    
  
    <script>
      
      // dummy var so that loading() method in PaymentRelease.js doesn't give a js error
      var searchWithResults = "null";
      
      function enableSchedulingOptions()
      {
      document.getElementById("dateField").disable(false)
        document.getElementById("timeField").disabled = false;
      }
      function disableSchedulingOptions()
      {
      document.getElementById("dateField").disable(true)
        document.getElementById("timeField").disabled = true;
      }
    </script>
  </xsl:template>

<!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >

  </xsl:template>

</xsl:stylesheet>

