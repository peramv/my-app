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
      <xsl:with-param name="pageTitle">Historical Information</xsl:with-param>
      <xsl:with-param name="displayTitle">false</xsl:with-param>
    </xsl:call-template>

  </xsl:template>

  <!-- ========================== FORM CALLBACK TEMPLATE - start ========================== -->
  <xsl:template name="form_callback">
    
    <script src="{$vURL}javascript/General_Base.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/General_Grid.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/PaymentSearch_HistoricalInfo.js">
      // comment. pls keep
    </script>
    
    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>
    <link rel="stylesheet" type="text/css" href="{$vURL}css/General_Grid.css"/>
    
    <input type="hidden" id="vrecid">
      <xsl:attribute name="value">
        <xsl:value-of select="//FormInformation/auditRecid"/>
      </xsl:attribute>
    </input>
    
    <script>
      var _historicalList = "";
      
      var recordsPerPage = 100;
      var currentHistoricalStart = 0;
      var currentHistoricalEnd = 0;
      
      
      
    </script>
        
    <div style="position:relative; width:700;">
      <div style="position:relative; width:100%; height:210px; background:white; border-style:inset;">

        <div id="historicalLoadingDiv" style="position:absolute; top:25; left:5; background:white; border-bottom:1px solid black; width:70px; display:none;" >
        </div>
        <table style="width:700;" class="table.sortable" id="historicalTable">
         <thead align="left">
          <th>Field Label</th>
          <th>Previous Value</th>
          <th>New Value</th>
          <th>Modification Date</th>
          <th>Modification Time</th>  
          <th>Who Modified?</th>
        </thead>
        <tbody>
          
        </tbody>
      </table>  
      </div>
    
      <div style="width:100%; position:relative; left:5;">
        <!-- Add counter here if necessary -->
        <div align="right" style="position:relative; left:-5;">
          <input style="width:80px" type="button" id="prevHistoricalButton" value="Previous" disabled="true" onclick="sendHistoricalCall (Number(currentRecordStart) - Number(recordsPerPage), recordsPerPage);"/>
          <input style="width:80px" type="button" id="nextHistoricalButton" value="Next" disabled="true" onclick="sendHistoricalCall  (Number(currentRecordEnd)+1, recordsPerPage);"/>
          <input style="width:80px" type="button" id="btnClose" value="Close" onclick=""/>
        </div>
      </div>
    
      <div align="right">
                   
      </div>
      
    </div>
    <script>
      var table = new IFDSTable ("historicalTable", "searchid", "searchcatid", 690, 350);
      _historicalList = new Grid('historicalTable');
      
      showLoadingDisplay("historicalLoadingDiv");
      sendHistoricalCall (1, recordsPerPage);
    </script>
  </xsl:template>

<!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >

  </xsl:template>

</xsl:stylesheet>

