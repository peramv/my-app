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
           
    <script src="{$vURL}javascript/General_Grid.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/General_Base.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/PaymentRelease.js">
      // comment. pls keep
    </script>
    
    <link rel="stylesheet"
      type="text/css"
      href="{$vURL}css/General_Grid.css"/>
    
    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>
    
    <script>
      
      var searchWithResults = "no";
      
      
      var _batchDetailsTable = "";
      var _paymentBatchTable = "";
      
      var recordsPerPage = 100;
      var currentRecordStart = 0;
      var currentRecordEnd = 0;
      
      var currentBatchDetailStart = 0;
      var currentBatchDetailEnd = 0;
      
      var currentRowBatch = "";
      var currentRowModDate = "";
      var currentRowProcDate = "";
      var currentRowModUser = "";
      var currentRowUserName = ""; 
      
      var generateBaffPermission = "<xsl:value-of select="//allowGenBAFF"/>";  
    </script>
    
    <!-- Upper Box, Search Criteria -->
    <fieldset align="center" id="datesRow" style="position:absolute; top:140; left:45; width:460; height:50;">
      <legend><font color="black">Dates:</font></legend>
      <center><table>
        <tr>
          <td>
            From:
          </td>
          <td>            
            <input type="text" id="fromDate" class="dstdatepicker" width="120px" >
              <xsl:attribute name="value">
                <xsl:value-of select="//DefaultDates/fromDate"/>
              </xsl:attribute>
            </input>
          </td>
          <td>
            To:
          </td>
          <td>
            <input  width="120px" maxlength="10" id="toDate" class="dstdatepicker">
              <xsl:attribute name="value">
                <xsl:value-of select="//DefaultDates/toDate"/>
              </xsl:attribute>
            </input>
          </td>
        </tr>
      </table>
      </center>

    </fieldset>
    <fieldset style="width:540; height:200;">
      <legend><font color="black">Criteria:</font></legend>
      <table width="100%">
        <tr style="position:relative; top:5;">
          <td align="left" style="position:relative; left:15;width:90;">
            Search Using:
          </td>
          <td style="width:180;">
            
            <select id="searchType" style="width:180;">
              <xsl:attribute name="onchange">document.getElementById("batchValue").value = ""; searchTypeChange()</xsl:attribute>
              <xsl:for-each select="//List[@listName='SearchTypeOptions']/Element">
                <option> 
                  <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>                 
                  <xsl:if test='//FormInformation/searchType=code'><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>
                  <xsl:value-of select="value"/>                  
                </option>
              </xsl:for-each>
            </select>
          </td>
          <td style="width:120;">
          </td>
        </tr>
        <tr id="pymtForRow" style="position:relative; top:5;">  
          <td align="left" style="position:relative; left:15;width:90;">
            Payment For:
          </td>
          <td style="width:180;">
            <select id="paymentFor" style="width:180;">
              <xsl:for-each select="//List[@id='PaymentForOptions']/Element">
                <option> 
                  <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
                  <xsl:if test='//FormInformation/searchValue=code'><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>                        
                  <xsl:value-of select="value"/>                  
                </option>
              </xsl:for-each>
            </select>
          </td>
          <td style="width:120;">
          </td>
        </tr>
        <tr id="batchStatusRow" style="position:relative; top:5;">
          <td align="left" style="position:relative; left:15;width:90;">
            Batch Status:
          </td>
          <td style="width:180;">
            <select id="batchStatus" style="width:180;">
              <xsl:for-each select="//List[@id='BatchStatusOptions']/Element">
                <option> 
                  <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>   
                  <xsl:if test='//FormInformation/batchStatus=code'><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>                     
                  <xsl:value-of select="value"/>                  
                </option>
              </xsl:for-each>
            </select>
          </td>
          <td style="width:120;">
          </td>
        </tr>
        <tr id="batchValueRow" style="position:relative; top:5; display:none;">
          <td align="left" style="position:relative; left:15;width:90;">
            Value:
          </td>
          <td style="width:180;">
            <input id="batchValue">
              <xsl:attribute name="value">
                <xsl:value-of select="//FormInformation/searchValue"/>
              </xsl:attribute>
            </input>
          </td>
          <td style="width:120;">
          </td>
        </tr>
        <tr style="position:absolute; top:200;">
          <td colspan="4" align="right">
            <input style="width:80;" type="button" value="Search" onclick="sendResetCall(); sendSearchCall(1, recordsPerPage)"/>
            <input style="width:80;" type="button" value="Refresh" onclick="sendResetCall()"/>
          </td>
        </tr>
      </table>      
    </fieldset>


    <!-- Lower Box, Search Criteria -->
    <fieldset style="position:relative; width:540; height:465; top:10;">
      <legend><font color="black">Results:</font></legend>
      <table style="position:relative; width:525; height:130; top:20;">
        <tr style="position:relative; height:10;">
          <td >
            Payment Batch:
          </td>
        </tr>
        <tr style="position:relative; height:120;">
          <td> 
            <div style="position:relative; width:520; height:140; overflow:auto; background:white; border-style:inset;">
              <div id="paymentBatchLoadingDiv" style="position:absolute; top:25; left:5; background:white; border-bottom:1px solid black; width:70px; display:none;" >
              </div>
              <table style="position:relative; width:100%;" class="table.sortable" id="paymentBatchTable">
                <THEAD>
                  <TR>
                    <TH>Payment For</TH>
                    <TH>Status</TH>
                    <TH>Payment Date</TH>
                    <TH>Payment File Name</TH>
                    <TH>Counter</TH>                    
                    <TH>ACH Processor</TH>
                  </TR>
                </THEAD>
              </table>
              <script>                
                var table = new IFDSTable ("paymentBatchTable", "searchid", "searchcatid", 510, 132);

                   
              </script>              
            </div>
          </td>
        </tr>
        <tr style="position:relative; height:26;">
          <td align="left" width="100%">
            
            <div id="lowerBatchTableDiv" style="width:100%; position:relative; left:5;">
              <span id="counterDiv">0 - 0 of 0</span>    
              <div align="right" style="position:relative; left:-5; top:-18;">
                <input id="btnPrevPayments" type="button" name="Previous" value="Previous" style="width:80px;" disabled="true" onclick="sendSearchCall (Number(currentRecordStart) - Number(recordsPerPage), recordsPerPage);"/>                     
                <input id="btnNextPayments" type="button" name="Next" value="Next" style="width:80px;" disabled="true" onclick="sendSearchCall (Number(currentRecordEnd)+1, recordsPerPage);"/>                
              </div>
            </div>

          </td>
        </tr>
        
        
        <tr style="position:relative; height:10;">
          <td >
            Payments:
          </td>
        </tr>
        <tr style="position:relative; height:120;">
          <td> 
            <div style="position:relative; width:100%; height:140; background:white; border-style:inset;">
              <div id="paymentBatchDetailLoadingDiv" style="position:absolute; top:25; left:5; background:white; border-bottom:1px solid black; width:70px; display:none;" >
              </div>
              <table style="" class="table.sortable" id="batchDetailsTable">
                <THEAD>
                  <TR>
                    <TH>Payment ID</TH>
                    <TH>Consolidate Indicator</TH>
                    <TH>Currency</TH>
                    <TH>Amount</TH>
                  </TR>
                </THEAD>
                <TBODY>
                </TBODY>
              </table>
              <script>                
                var table = new IFDSTable ("batchDetailsTable", "searchid", "searchcatid", 512, 130);
                _batchDetailsTable = document.getElementById("batchDetailsTable");
                //table.redrawtable();          
              </script>              
            </div>
          </td>
        </tr>
        <tr style="position:relative;">
          <td align="left">
            <div id="batchDetailCounter" style="width:100%; position:relative; left:5;">
              <span id="batchDetailCounterDiv">0 - 0 of 0</span>    
              <div align="right" style="position:relative; left:-5; top:-18;">
                <input id="btnPrevBatchDetails" type="button" name="Previous" value="Previous" style="width:80px;" disabled="true" onclick="sendBatchPaymentCall (currentRowBatch, Number(currentBatchDetailStart) - Number(recordsPerPage), recordsPerPage);"/>                     
                <input id="btnNextBatchDetails" type="button" name="Next" value="Next" style="width:80px;" disabled="true" onclick="sendBatchPaymentCall (currentRowBatch, Number(currentBatchDetailEnd)+1, recordsPerPage);"/>                
              </div>
            </div>
          </td>
        </tr>
        
        
        <tr style="position:relative; top:-16;">
          <td align="right">
            <input style="width:160;" id="generateBaffButton" type="button" value="Generate Payment File" disabled="true" onclick="sendScheduleCall()"/>
          </td>
        </tr>
      </table>
    </fieldset>
    
    <div style="position:relative; width:540; top:25; y-overflow:scroll;" align="right">
      <input style="width:80;" id="btnClose" type="button" value="Close"/>
      <input style="width:80;" id="btnAdmin" type="button" disabled="true" value="Admin" onclick='alert("Mod Date: \t" + currentRowModDate + "\t Processed Date: \t" + currentRowProcDate + "\t \n\nMod User: \t" + currentRowModUser + "\t User Name: \t" + currentRowUserName);'/>
    </div>
    
    <script>
      
      
      
      // Changing displayed values to match the default Search Type:
      try
      {
        searchTypeChange();
      }
      catch(e)
      {
        alert("Initial values not available, check listener.");
      }
      
      function searchTypeChange()
      {
        var searchTypeDropdown = document.getElementById("searchType");
        if (searchTypeDropdown.options[searchTypeDropdown.selectedIndex].value == "paymentFor")
        {
          document.getElementById("pymtForRow").style.display = "block";
          document.getElementById("batchStatusRow").style.display = "block";
          document.getElementById("datesRow").style.display = "block";
          document.getElementById("batchValueRow").style.display = "none";
        }
        else
        {
          document.getElementById("pymtForRow").style.display = "none";
          document.getElementById("batchStatusRow").style.display = "none";
          document.getElementById("datesRow").style.display = "none";
          document.getElementById("batchValueRow").style.display = "block";
        }
      }
    </script>
    
  </xsl:template>
  
  <!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >
    
  </xsl:template>
  
</xsl:stylesheet>

