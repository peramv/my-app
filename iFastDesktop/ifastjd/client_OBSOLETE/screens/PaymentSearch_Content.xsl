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
      <xsl:with-param name="pageTitle">Payment Search</xsl:with-param>
      <xsl:with-param name="displayTitle">false</xsl:with-param>
    </xsl:call-template>

  </xsl:template>

  <!-- ========================== FORM CALLBACK TEMPLATE - start ========================== -->
  <xsl:template name="form_callback">
    <script src="{$vURL}javascript/General_Base.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/FundLimitations_Grid.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/PaymentSearch.js">
      // comment. pls keep
    </script>

    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>

    <div id="initial" style="postion:absolute; left:25; top:50; width:700px; border:1px double #CCCCCC">
      <input type="hidden" id="recordStart" >
        <xsl:attribute name="value"><xsl:value-of select="//FormInformation/rangeStart"/></xsl:attribute>
      </input>
      <input type="hidden" id="recordEnd">
        <xsl:attribute name="value"><xsl:value-of select="//FormInformation/rangeEnd"/></xsl:attribute>
      </input>
      <input type ="hidden" id="pymtFor" />

      <input type="hidden" id="paymentForID" />
      <input type="hidden" id="listId" />

      <div id="divCriteria" style="position:relative; left:27; top:-10" >
        <label>Criteria:</label>
      </div>
      <table width="100%">
        <tr>
          <td>

          </td>
        </tr>
        <tr>
          <td align="left" width="120px">
              <label> Search Using:</label>
           </td>
           <td align="left">
               <select id="cmbSearchType"  style="width:200px" onchange="changeDiv()" disabled="true">
                   <option>
                     Transaction Number
                   </option>
               </select>
          </td>
        </tr>
       </table>

      <div id="transNumDiv">
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label> Value: </label>
            </td>
            <td align="left">
                <input type="integer" id="transNumValue" class="dstinteger" maxlength="11" disabled ="true">
                  <xsl:attribute name="value"><xsl:value-of select="//FormInformation/searchValue"/></xsl:attribute>
                </input>
            </td>
          </tr>
        </table>
      </div>
       <div align="right">
         <input type="button" value="Search" style="width:80px" onClick ="getResults(1,25);" disabled="true"/>
         <input type="button" name="Refresh" value="Refresh" style="width:80px"  onClick="refreshPage()" disabled="true"/>
       </div>
    </div>
    <p />
    <br />
    <div id="consolidatedPayments" style="width:700px; border:1px double #CCCCCC">
      <div id="divResults" style="position:relative; left:27; top:-10" >
        <label> Results:</label>
      </div>
      <label>Consolidated Payments </label>
      <br />
      <div id="consolidatedDetails" >
        <!-- GRID -->
        <div style="overflow:scroll; width:690px; height:100px; background:white" onload=" test(_consolidatedList.getRow(1));">
          <table width="680px" cellpadding="1" cellspacing="0" style="cursor:default;"
            id="consolidatedPaymentList">
            <!-- header -->
            <tr class="fixedHeader">
              <th class="grid" align="left">Payment ID </th>
              <th class="grid" align="left">Payment Date</th>
              <th class="grid" align="left">Amount</th>
              <th class="grid" align="left">Currency</th>
              <th class="grid" align="left">Consolidation Indicator</th>
            </tr>
            <xsl:for-each select="//ConsolidatedPayments/ConsolidatedPaymentDetail">
              <xsl:element name="tr">
                <xsl:attribute name="pymtFor"><xsl:value-of select="pymtFor"/></xsl:attribute>
                <td class="grid"><xsl:value-of select="pymtId" /></td>
                <td class="grid"><xsl:value-of select="tapeDate" /></td>
                <td class="grid"><xsl:value-of select="payAmt" /></td>
                <td class="grid"><xsl:value-of select="curr" /></td>
                <td class="grid"><xsl:value-of select="consolInd" /></td>
              </xsl:element>
            </xsl:for-each>
            <select id="cmbPymtFor" name="cmbPymtFor" style="width:200px; display:none" >
              <xsl:for-each select="//ConsolidatedPayments/ConsolidatedPaymentDetail">
                <option>
                  <xsl:attribute name="value"><xsl:value-of select="pymtFor"/></xsl:attribute>
                  <xsl:value-of select="pymtFor"/>
                </option>
              </xsl:for-each>
            </select>
          </table>
        </div>
        <p />
        <div align="right">
          <xsl:element name="input">
            <xsl:attribute name="id">btnGetMoreConsolidatePaymentRecords</xsl:attribute>
            <xsl:attribute name="type">button</xsl:attribute>
            <xsl:attribute name="name">More</xsl:attribute>
            <xsl:attribute name="value">More</xsl:attribute>
            <xsl:attribute name="style">width:80px</xsl:attribute>
            <xsl:attribute name="onclick">getMoreRecords();</xsl:attribute>
            <xsl:if test="//RecordRange/moreRecordsExist='no'">
              <xsl:attribute name="disabled">true</xsl:attribute>
            </xsl:if>
          </xsl:element>
        </div>
      </div>
      <p />
      <div id="transactionDetails" style="width:700px; display:none">
        <label>Transactions</label>
         <br />
         <div id="transactionsDetails" >
          <!-- GRID -->
          <div style="overflow:scroll; width:700px; height:100px; background:white">
            <table width="700px" cellpadding="1" cellspacing="0" style="cursor:default;"
              id="transactionList">
              <!-- header -->
              <tr class="fixedHeader">
                <th class="grid" align="left">Trans Type </th>
                <th class="grid" align="left">Broker</th>
                <th class="grid" align="left">Amount</th>
                <th class="grid" align="left">Account</th>
                <th class="grid" align="left">Consolidation Level </th>
                <th class="grid" align="left">Trans Num.</th>
                <th class="grid" align="left">Trade Date</th>
                <th class="grid" align="left">Settlement Date</th>
                <th class="grid" align="left">Fund </th>
                <th class="grid" align="left">Class</th>
              </tr>
            </table>
          </div>
          <p />

        </div>
        <p />
        <div align="right">
          <xsl:element name="input">
            <xsl:attribute name="id">btnGetMoreTransactionRecords</xsl:attribute>
            <xsl:attribute name="type">button</xsl:attribute>
            <xsl:attribute name="name">More</xsl:attribute>
            <xsl:attribute name="value">More</xsl:attribute>
            <xsl:attribute name="style">width:80px</xsl:attribute>
            <xsl:attribute name="onclick">moreRecords();</xsl:attribute>
            <!--xsl:if test="//RecordRange/moreRecordsExist='no'">
              <xsl:attribute name="disabled">true</xsl:attribute>
            </xsl:if-->
          </xsl:element>
        </div>
        <div id="paymentDetails" style="width:700px;  display:none" >
          <label>Payments</label>
          <br />
          <div id="paymentsDetails" >
            <!-- GRID -->
            <div style="overflow:scroll; width:700px; height:100px; background:white">
              <table width="700px" cellpadding="1" cellspacing="0" style="cursor:default;"
                id="paymentList">
                <!-- header -->
                <tr class="fixedHeader">
                  <th class="grid" align="left">Broker</th>
                  <th class="grid" align="left">Amount</th>
                  <th class="grid" align="left">Fund </th>
                  <th class="grid" align="left">Class</th>
                </tr>
              </table>
            </div>
            </div>
            </div>
      </div>
    </div>
    <p />

  </xsl:template>

<!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >

  </xsl:template>

</xsl:stylesheet>

