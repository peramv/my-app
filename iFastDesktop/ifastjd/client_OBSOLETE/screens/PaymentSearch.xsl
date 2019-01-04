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
    <script src="{$vURL}javascript/base.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/grid.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/PaymentSearch.js">
      // comment. pls keep
    </script>

    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>

    <div id="initial" style="postion:absolute; left:25; top:50; width:700px; border:1px double #CCCCCC">
      <input type="hidden" id="recordStart" />
      <input type="hidden" id="recordEnd"  />
      <input type ="hidden" id="pymtFor" />
      <select id="cmbPymtFor" name="cmbPymtFor" style="width:200px; display:none" >
        <xsl:for-each select="//List[@listName='PaymentForFilter']/Element">
          <option>
            <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
            <xsl:value-of select="value"/>
          </option>
        </xsl:for-each>
      </select>
      <input type="hidden" id="paymentForID" />
      <input type="hidden" id="listId" />

      <div id="divCriteria" style="position:relative; left:27; top:-10" >
        <label> Criteria:</label>
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
               <select id="cmbSearchType"  style="width:200px" onchange="changeDiv()" >
                 <xsl:for-each select="//List[@listName='SearchTypeFilter']/Element">
                   <option>
                     <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
                     <xsl:value-of select="value"/>
                   </option>
                 </xsl:for-each>
               </select>
          </td>
        </tr>
       </table>
      <div id="accountDiv" style="display:none">
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label>  Value: </label>
            </td>
            <td align="left">
                <input type="integer" id="accountValue" class="dstinteger" maxlength="16" />
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label> From Date: </label>
            </td>
            <td>
                <input type="text" id="accountPaymentDateFrom" class="dstdatepicker" width="120px" maxlength="10">
                  <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/frmDt"/></xsl:attribute>
                </input>
            </td>
            <td align="left">
                <label>To Date:</label>
            </td>
            <td>
                <input type="text" id="accountPaymentDateTo" class="dstdatepicker" width="120px" maxlength="10">
                  <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/toDt"/></xsl:attribute>
                </input>
            </td>
          </tr>
        </table>
      </div>
      <div id="paymentDateDiv" style="display:none">
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label> Payment For:</label>
            </td>
            <td align="left">
                <select id="cmbPaymentFor" name="cmbPaymentFor" style="width:200px" >
                  <xsl:for-each select="//List[@listName='PaymentForFilter']/Element">
                    <option>
                      <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
                      <xsl:value-of select="value"/>
                    </option>
                  </xsl:for-each>
                </select>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label>From Date:</label>
             </td>
             <td>
               <input type="text" id="paymentDateFrom" class="dstdatepicker" width="120px" maxlength="10" >
                 <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/frmDt"/></xsl:attribute>
               </input>
            </td>
            <td align="left">
                <label> To Date: </label>
             </td>
             <td>
                <input type="text" id="paymentDateTo" class="dstdatepicker" width="120px" maxlength="10">
                  <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/toDt"/></xsl:attribute>
                </input>
            </td>
          </tr>
        </table>
      </div>
      <div id="paymentIdDiv" >
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label> Value: </label>
            </td>
            <td align="left">
              <input type="integer" id="paymentValue" class="dstinteger" maxlength="11" />
            </td>
          </tr>
        </table>
      </div>
      <div id="payEntityDiv" style="display:none">
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label> Payment For: </label>
            </td>
            <td align="left">
                <select id="cmbPayEntityPaymentFor" name="cmbPayEntityPaymentFor" style="width:200px" >
                  <xsl:for-each select="//List[@listName='PaymentForFilter']/Element">
                    <option>
                      <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
                      <xsl:value-of select="value"/>
                    </option>
                  </xsl:for-each>
                </select>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label>Broker: </label>
            </td>
            <td align="left">
                <select id="cmbBroker" name="cmbBroker" onchange=" searchBranch(); searchRep();" style="width:200px">
                  <xsl:for-each select="//List[@listName='Broker']">
                    <option>
                      <xsl:attribute name="value"><xsl:value-of select="Element/value"/></xsl:attribute>
                      <xsl:value-of select="Element/value"/>
                    </option>
                  </xsl:for-each>
                </select>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label>  Branch: </label>
            </td>
            <td align="left">
                <select id="cmbBranch" name="cmbBranch" onchange="searchRep();" style="width:200px">
                  <xsl:for-each select="//List[@listName='Branch']">
                    <option>
                      <xsl:attribute name="value"><xsl:value-of select="Element/value"/></xsl:attribute>
                      <xsl:value-of select="Element/value"/>
                    </option>
                  </xsl:for-each>
                </select>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label>  Sales Rep: </label>
            </td>
            <td align="left">
                <select id="cmbSalesRep" name="cmbSalesRep" style="width:200px">
                  <xsl:for-each select="//List[@listName='Sales Rep']">
                    <option>
                      <xsl:attribute name="value"><xsl:value-of select="Element/code"/></xsl:attribute>
                      <xsl:value-of select="Element/value"/>
                    </option>
                  </xsl:for-each>
                </select>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label> From Date: </label>
            </td>
            <td>
                <input type="text" id="payEntityPaymentDateFrom" class="dstdatepicker" width="120px" >
                  <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/frmDt"/> </xsl:attribute>
                </input>
             </td>
             <td>
                <label>To Date:</label>
             </td>
             <td>
                 <input type="text" id="payEntityPaymentDateTo" class="dstdatepicker" width="120px" >
                   <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/toDt"/> </xsl:attribute>
                 </input>
            </td>
          </tr>
        </table>
      </div>
      <div id="transNumDiv" style="display:none">
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label> Value: </label>
            </td>
            <td align="left">
                <input type="integer" id="transNumValue" class="dstinteger" maxlength="11"/>
            </td>
          </tr>
        </table>
      </div>
       <div align="right">
         <input type="button" value="Search" style="width:80px" onClick ="getResults(1,25);" />
         <input type="button" name="Refresh" value="Refresh" style="width:80px"  onClick="refreshPage()"/>
       </div>
    </div>
    <p />
    <br />
    <div id="consolidatedPayments" style="width:700px; border:1px double #CCCCCC; display:none">
      <div id="divResults" style="position:relative; left:27; top:-10" >
        <label> Results:</label>
      </div>
      <label>Consolidated Payments </label>
      <br />
      <div id="consolidatedDetails" >
        <!-- GRID -->
        <div style="overflow:scroll; width:690px; height:100px; background:white">
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
          <div align="right">
            <input type="button" name="btnTransactionDetails" value="Transaction Details" id="btnTransactionDetails" style="width:150px" onclick="dataForTransDetails()" />
          </div>
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
          </xsl:element>
        </div>
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
        <p />
        <div align="right">
          <input type="button" name="More" value="More" style="width:80px" onclick ="moreRecords()"/>
        </div>
      </div>
    </div>
    <p />

  </xsl:template>

<!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >

  </xsl:template>

</xsl:stylesheet>

