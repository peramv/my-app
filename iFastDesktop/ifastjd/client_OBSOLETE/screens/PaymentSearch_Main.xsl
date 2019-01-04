<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}client/screens/MasterLayout.xsl"/>


  <!-- CLIENT & PATH VARIABLES - start -->
  <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
  <xsl:variable name="vEnvName"      select="/websrvXML/FormInformation/envName"/>
  <xsl:variable name="vCompanyCode"  select="/websrvXML/FormInformation/companyCode"/>
  <xsl:variable name="vRUserId"      select="/websrvXML/FormInformation/ruserId"/>
  <xsl:variable name="vSessionId"    select="/websrvXML/FormInformation/sessionId"/>
  <xsl:variable name="vTIDX"/>
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
    <script src="{$vURL}javascript/General_Grid.js">
      // comment. pls keep
    </script>    
    <script src="{$vURL}javascript/PaymentSearch.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/SuggestDropdown.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/FieldSuggest.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/XML_Lib.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/PaymentSearch_HistoricalInfo.js">
      // comment. pls keep
    </script>


    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>
    <link rel="stylesheet"
      type="text/css"
      href="{$vURL}css/General_Grid.css"/>
    
    <script>
      var _consolidatedPaymentList = "";
      var _paymentList = "";
      var _transactionList = "";
            
      var _versionList = new Array();
      var _vrecid = new Array();
      var verifySend = "no";
      var approveSend = "no";
      var stopSend = "no";
      
      var currentRecordStart = 0;
      var currentRecordEnd = 0;
      
      var currentPaymentStart = 0;
      var currentPaymentEnd = 0;
      
      var recordsPerPage = 100;
      
      var currentSelectedRow = -1;  
      var massStatus = null;
      
      var _imagePath = '<xsl:value-of select="$vURL"/>images';
      
      var _brokerSuggest = null;
      var _branchSuggest = null;
      var _salesrepSuggest = null;

      var auditRecid = 0;
    </script>
    
    <xsl:element name="input">
      <xsl:attribute name="id">fldCZ</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select="$vCZ"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldServletPath</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select="$vServletPath"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldEnvName</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select="$vEnvName"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldCompanyCode</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select="$vCompanyCode"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldAccountNum</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select=".//FormInformation/AccountNum"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldRUserId</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select="$vRUserId"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldSessionId</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select="$vSessionId"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldOption</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select=".//FormInformation/option"/></xsl:attribute>
    </xsl:element>
    <xsl:element name="input">
      <xsl:attribute name="id">fldUpdateStatus</xsl:attribute>
      <xsl:attribute name="type">hidden</xsl:attribute>
      <xsl:attribute name="value"><xsl:value-of select=".//FormInformation/updateStatus"/></xsl:attribute>
    </xsl:element>
    
    

             
    <fieldset id="initial" style="postion:absolute; left:25; top:50; width:712px;">
      <legend><font color="black">Criteria:</font></legend>
      
      <input type="hidden" id="recordStart" />
      <input type="hidden" id="recordEnd"  />
      <input type ="hidden" id="pymtFor" />
      <select id="cmbPymtFor" name="cmbPymtFor" style="width:200px; display:none" >
        <xsl:for-each select="//List[@id='PaymentForOptions']/Element">
          <option>
            <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
            <xsl:value-of select="value"/>
          </option>
        </xsl:for-each>
      </select>
      <input type="hidden" id="paymentForID" />
      <input type="hidden" id="listId" />
      <table width="100%">
        <tr>
          <td>

          </td>
        </tr>
        <tr>
          <td align="left" width="120px; ">
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
      
      <div id="paymentForDiv" style="height:180px">
        <table width="100%">
          <tr>
            <td align="left" width="120px">
              <label> Payment For: </label>
            </td>
            <td align="left">
              <select id="cmbPaymentForPaymentFor" name="cmbPaymentForPaymentFor" style="width:200px" onchange="limitSearchFields()">
                <xsl:for-each select="//List[@id='PaymentForOptions']/Element">
                  <option>
                    <xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
                    <xsl:value-of select="value"/>
                  </option>
                </xsl:for-each>
              </select>
            </td>
            <td align="left" width="120px">
              <label> Pay Type: </label>
            </td>
            <td align="left">
              <select id="cmbPaymentForPayType" name="cmbPaymentForPayType" style="width:200px" onchange="limitSearchFields()">
                <xsl:for-each select="//List[@id='PaymentTypeOptions']/Element">
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
              <xsl:element name="input">
                <xsl:attribute name="id">paymentForBrokerBox</xsl:attribute>
                <xsl:attribute name="name">paymentForBrokerBox</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="//List[@listName='Broker']/Element/value"/></xsl:attribute>
                <xsl:attribute name="code"><xsl:value-of select="//List[@listName='Broker']/Element/code"/></xsl:attribute>
                <xsl:attribute name="style">position:relative; top:0; left:0</xsl:attribute>
                <xsl:attribute name="onfocus">_brokerSuggest.init(this, document.getElementById("paymentForBranchBox"), document.getElementById("paymentForRepBox"));</xsl:attribute>
              </xsl:element>
            </td>
            <td align="left" width="120px">
              <label> Status: </label>
            </td>
            <td align="left">
              <select id="cmbPaymentForStatus" name="cmbPaymentForStatus" style="width:200px" >
                <xsl:for-each select="//List[@id='PaymentStatusOptions']/Element">
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
              <label>  Branch: </label>
            </td>
            <td align="left">
              
              <xsl:element name="input">
                <xsl:attribute name="id">paymentForBranchBox</xsl:attribute>
                <xsl:attribute name="name">paymentForBranchBox</xsl:attribute>
                <xsl:attribute name="class">fontTypeSize10 boxWidth1 boxBackground</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="//List[@listName='Branch']/Element/value"/></xsl:attribute>
                <xsl:attribute name="code"><xsl:value-of select="//List[@listName='Branch']/Element/code"/></xsl:attribute>
                <xsl:attribute name="onfocus">_branchSuggest.init(document.getElementById("paymentForBrokerBox"), this, document.getElementById("paymentForRepBox"));</xsl:attribute>
              </xsl:element>
              
            </td>
            <td align="left" width="120px">
              <label> Account: </label>
            </td>
            <td align="left">
              <input id="paymentForAccountField" style="width:200px"></input>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
              <label>  Sales Rep: </label>
            </td>
            <td align="left">
              <xsl:element name="input">
                <xsl:attribute name="id">paymentForRepBox</xsl:attribute>
                <xsl:attribute name="name">paymentForRepBox</xsl:attribute>
                <xsl:attribute name="class">fontTypeSize10 boxWidth1 boxBackground</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="//List[@listName='SalesRep']/Element/value"/></xsl:attribute>
                <xsl:attribute name="code"><xsl:value-of select="//List[@listName='SalesRep']/Element/code"/></xsl:attribute>
                <xsl:attribute name="onfocus">_salesrepSuggest.init(document.getElementById("paymentForBrokerBox"), document.getElementById("paymentForBranchBox"), this);</xsl:attribute>
              </xsl:element>
            </td>
            <td>
              
            </td>
            <td>
              
            </td>
          </tr>          
        </table>
        
        <fieldset id="datesRow" style="position:absolute; top:165; left:370; width:300; height:80;">
          <legend><font color="black">Dates:</font></legend>
          <table style="position:absolute;">
            
          <tr>
            <td align="left" width="120px">
              <label> From Date: </label>
            </td>
            <td>
              <input type="text" id="paymentForPaymentDateFrom" class="dstdatepicker" width="160px" >
                <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/frmDt"/> </xsl:attribute>
              </input>
            </td>
          </tr>
          <tr>  
            <td>
              <label>To Date:</label>
            </td>
            <td>
              <input type="text" id="paymentForPaymentDateTo" class="dstdatepicker" width="160px" >
                <xsl:attribute name="value"><xsl:value-of select="//DefaultDates/toDt"/> </xsl:attribute>
              </input>
            </td>
          </tr>
          </table>
        </fieldset>
      </div>
      <div id="accountDiv" style="display:none">
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label>  Value: </label>
            </td>
            <td align="left">
                <input type="integer" id="accountValue" maxlength="16" />
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
                  <xsl:for-each select="//List[@id='PaymentForOptions']/Element">
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
      <div id="paymentIdDiv" style="display:none;" >
        <table width="100%">
          <tr>
            <td align="left" width="120px">
                <label> Value: </label>
            </td>
            <td align="left">
              <input type="integer" id="paymentValue" maxlength="11" />
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
                  <xsl:for-each select="//List[@id='PaymentForOptions']/Element">
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
              <xsl:element name="input">
                <xsl:attribute name="id">payEntityBrokerBox</xsl:attribute>
                <xsl:attribute name="name">payEntityBrokerBox</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="//List[@listName='Broker']/Element/value"/></xsl:attribute>
                <xsl:attribute name="code"><xsl:value-of select="//List[@listName='Broker']/Element/code"/></xsl:attribute>
                <xsl:attribute name="style">position:relative; top:0; left:0</xsl:attribute>
                <xsl:attribute name="onfocus">_brokerSuggest.init(this, document.getElementById("payEntityBranchBox"), document.getElementById("payEntityRepBox"));</xsl:attribute>
              </xsl:element>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label>  Branch: </label>
            </td>
            <td align="left">
              <xsl:element name="input">
                <xsl:attribute name="id">payEntityBranchBox</xsl:attribute>
                <xsl:attribute name="name">payEntityBranchBox</xsl:attribute>
                <xsl:attribute name="class">fontTypeSize10 boxWidth1 boxBackground</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="//List[@listName='Branch']/Element/value"/></xsl:attribute>
                <xsl:attribute name="code"><xsl:value-of select="//List[@listName='Branch']/Element/code"/></xsl:attribute>
                <xsl:attribute name="onfocus">_branchSuggest.init(document.getElementById("payEntityBrokerBox"), this, document.getElementById("payEntityRepBox"));</xsl:attribute>
              </xsl:element>
            </td>
          </tr>
          <tr>
            <td align="left" width="120px">
                <label>  Sales Rep: </label>
            </td>
            <td align="left">
              
              <xsl:element name="input">
                <xsl:attribute name="id">payEntityRepBox</xsl:attribute>
                <xsl:attribute name="name">payEntityRepBox</xsl:attribute>
                <xsl:attribute name="class">fontTypeSize10 boxWidth1 boxBackground</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="//List[@listName='SalesRep']/Element/value"/></xsl:attribute>
                <xsl:attribute name="code"><xsl:value-of select="//List[@listName='SalesRep']/Element/code"/></xsl:attribute>
                <xsl:attribute name="onfocus">_salesrepSuggest.init(document.getElementById("payEntityBrokerBox"), document.getElementById("payEntityBranchBox"), this);</xsl:attribute>
              </xsl:element>
              

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
                <input type="integer" id="transNumValue" maxlength="11"/>
            </td>
          </tr>
        </table>
      </div>
       <div align="right">
         <input type="button" id="searchButton" value="Search" style="width:80px" onClick ='document.getElementById("refreshButton").disabled = false; getResults(1, recordsPerPage);' />
         <input type="button" id="refreshButton" name="Refresh" value="Refresh" style="width:80px" disabled="true" onClick='this.disabled="true"; refreshPage(); '/>
       </div>
    </fieldset>
    <p />
    <br />

    <fieldset id="consolidatedPayments" style="position:relative; width:704px; display:none; z-index:9;">
      <legend><font color="black">Results:</font></legend>

      <div style="position:relative; top:5; left:8;">
        Consolidated Payments:
      </div>
      <div style="position:relative; top:7;" id="consolidatedDetails" >
        <!-- GRID -->
        <div style="position:relative; width:100%; height:210px; background:white; border-style:inset;">
          <div id="consolidatedLoadingDiv" style="position:absolute; top:25; left:5; background:white; border-bottom:1px solid black; width:70px;" >
          </div>
          <table cellpadding="1" cellspacing="0" style="position:relative; width:100%; cursor:default; position:relative; " class="table.sortable"
            id="consolidatedPaymentList">
            <!-- header -->
            <thead>

              <th class="grid" align="left">Status </th>
              <th class="grid" align="left">Payment ID </th>
              <th class="grid" align="left">Payment Date</th>
              <th class="grid" align="left">Consolidation Indicator</th>
              <th class="grid" align="left">Amount</th>
              <th class="grid" align="left">Currency</th>
              <th class="grid" align="left">Batch ID</th>
              <th class="grid" align="left">Trans Type</th>

            </thead>           
          </table>
          
          <script>
            var table = new IFDSTable ("consolidatedPaymentList", "searchid", "searchcatid", 690, 200);            
            _consolidatedPaymentList = document.getElementById("consolidatedPaymentList");
          </script>
        </div>
        <p />
        <div id="consolidatedPaymentCounter" style="width:100%; position:relative; left:5;">
          <span id="counterDiv">0 - 0 of 0</span>    
          <div align="right" style="position:relative; left:-5; top:-18;">
            <input id="btnPrevConsPaymentRecords" type="button" name="Previous" value="Previous" style="width:80px;" disabled="true" onclick="getResults (Number(currentRecordStart) - Number(recordsPerPage), recordsPerPage);"/>                     
            <input id="btnNextConsPaymentRecords" type="button" name="Next" value="Next" style="width:80px;" disabled="true" onclick="getResults (Number(currentRecordEnd)+1, recordsPerPage);"/>
            <input id="resetRecordButton" type="button" name="Reset" value="Reset" style="width:80px;" disabled="true" onclick='resetSelected();'/>
          </div>
        </div>
        <span id="verifyAllDiv" align="left" style="position:relative; top:-20; display:none;">
          <input id="verifyAll" type="checkbox">
            <xsl:attribute name="onclick">              
              
              if (this.checked)
              {
                verifySend = "yes";
                approveSend = "no";
                stopSend = "no";
                document.getElementById("approveAll").checked=false;
                document.getElementById("stopAll").checked=false;
                
                modifyAllStatuses ("Verify");
                massStatus = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML + " Verified";
              }
              else
              {
                modifyAllStatuses ("Default");
                massStatus = null;
                verifySend = "no";
              }
            </xsl:attribute>
          </input> 
          Verify All
        </span>
        <span id="approveAllDiv" align="left" style="position:relative; top:-20; display:none;">
          <input id="approveAll" type="checkbox">
            <xsl:attribute name="onclick">
              if (this.checked)
              {
                verifySend = "no";
                approveSend = "yes";
                stopSend = "no";
                document.getElementById("verifyAll").checked=false;
                document.getElementById("stopAll").checked=false;
                
                
                modifyAllStatuses ("Approved");
                massStatus = "Approved";
                
              }
              else
              {
                modifyAllStatuses ("Default");
                massStatus = null;
                approveSend = "no";
              }
            </xsl:attribute>
          </input>
          Approve All 
        </span>
        <span id="stopAllDiv" align="left" style="position:relative; top:-20; display:none;">
          <input id="stopAll" type="checkbox">
            <xsl:attribute name="onclick">
              if (this.checked)
              {
                verifySend = "no";
                approveSend = "no";
                stopSend = "yes";
                document.getElementById("approveAll").checked=false;              
                document.getElementById("verifyAll").checked=false;
                                
                modifyAllStatuses ("Stopped");
                massStatus = "Stopped";
              }
              else
              {
                
                modifyAllStatuses ("Default");
                massStatus = null;
                stopSend = "no";
              }
            </xsl:attribute>
          </input>  
          Stop All
        </span>
          

      </div>
      <p />
      <div id="transactionDetails" style="width:700px; display:none">
        <div style="position:relative; top:5; left:8;">
          Transactions:
        </div>
         <div style="position:relative; top:7;" id="transactionsDetails" >
          <!-- GRID -->
           <div style="position:relative; width:100%; height:100px; background:white; border-style:inset;">
             <div id="transactionLoadingDiv" style="position:absolute; top:25; left:5; background:white; border-bottom:1px solid black; width:70px;" >
            </div>
            <table width="690px" cellpadding="1" cellspacing="0" style="cursor:default;" class="table.sortable"
              id="transactionList">
              <!-- header -->
              <thead>
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
              </thead>
            </table>
            
            <script>
              var table = new IFDSTable ("transactionList", "searchid", "searchcatid", 690, 100);
              _transactionList = document.getElementById("transactionList");
            </script>
          </div>
          <p />
          <div align="right">
            
          </div>
        </div>
        <p />
          
        <div id="transactionCounter" style="width:100%; position:relative; left:5;">
          <span id="transactionCounterDiv">0 - 0 of 0</span>    
          <div align="right" style="position:relative; top:-10; left:-5;">
            
            <input id="btnPrevTransactionRecords" type="button" name="Previous" value="Previous" style="width:80px;" disabled="true" onclick="getList (Number(currentPaymentStart) - Number(recordsPerPage), recordsPerPage);"/>                     
            <input id="btnNextTransactionRecords" type="button" name="Next" value="Next" style="width:80px;" disabled="true" onclick="getList (Number(currentPaymentEnd)+1, recordsPerPage);"/>
            <input type="button" name="btnTransactionDetails" value="Details" id="btnTransactionDetails" style="width:80px;" onclick="dataForTransDetails()" />           
          </div>
        </div>
        
      </div>
      <div id="paymentDetails" style="width:700px;  display:none" >
        <div style="position:relative; top:5; left:8;">
          Payments:
        </div>
          <div style="position:relative; top:7;" id="paymentsDetails" >
            <!-- GRID -->
            <div style="position:relative; width:100%px; height:100px; background:white; border-style:inset;">
              <div id="paymentLoadingDiv" style="position:absolute; top:25; left:5; background:white; border-bottom:1px solid black; width:70px;" >
              </div>
              <table cellpadding="1" cellspacing="0" style="cursor:default;" class="table.sortable"
                        id="paymentList">
                  <!-- header -->
                  <thead>
                    <th class="grid" align="left">Broker</th>
                    <th class="grid" align="left">Branch</th>
                    <th class="grid" align="left">Sales Rep</th>
                    <th class="grid" align="left">Amount</th>
                    <th class="grid" align="left">Fund </th>
                    <th class="grid" align="left">Class</th>
                  </thead>
                </table>
                
                <script>
                  var table = new IFDSTable ("paymentList", "searchid", "searchcatid", 690, 100);
                  _paymentList = document.getElementById("paymentList");
                </script>
              </div>
          </div>
        <p />
        
        <div id="paymentCounter" style="width:100%; position:relative; left:5; ">
          <span id="paymentCounterDiv">0 - 0 of 0</span>    
          <div align="right" style="position:relative; top:-10; left:-5;">
            <input id="btnPrevPaymentRecords" type="button" name="Previous" value="Previous" style="width:80px;" disabled="true" onclick="getList (Number(currentPaymentStart) - Number(recordsPerPage), recordsPerPage);"/>                     
            <input id="btnNextPaymentRecords" type="button" name="Next" value="Next" style="width:80px;" disabled="true" onclick="getList (Number(currentPaymentEnd)+1, recordsPerPage);"/>          
          </div>
        </div>
      </div>
      <div align="right" style="position:relative; width:700;">
        
          
        <div align="left" id="submitLoadingDiv" style="position:relative; font-size:140%; display:none; width:120px; height:25; left:-30; top:3; z-index:10;" >
        </div>
        
        <input id="btnOK" disabled="yes" type="button" value="OK" style="width:80;">
          <xsl:attribute name="onclick">
            
           showLoadingDisplay("submitLoadingDiv", "Submitting");
                       	 
           var previousStatus = document.getElementById("cmbPaymentForStatus").options[document.getElementById("cmbPaymentForStatus").selectedIndex].innerHTML;
           
           if (verifySend == "yes") 
           {         
            if(confirm ("You are about to Verify all " + previousStatus + " records from the SYSTEM, Would you like to proceed?"))
              submitChanges();
           }
           else if (approveSend == "yes")
           {          
            if(confirm ("You are about to Approve all " + previousStatus + " records from the SYSTEM, Would you like to proceed?"))
              submitChanges();
           }
           else if (stopSend == "yes")        
           {
            if (confirm ("You are about to Stop all " + previousStatus + " records from the SYSTEM, Would you like to proceed?"))
              submitChanges();
           }
           else           
             submitChanges();
          </xsl:attribute>
        </input>
        <input id="btnCancel" type="button" value="Cancel" style="width:80;" onclick=""/>
        <input id="historicalButton" name="historicalButton" type="button" value="Historical" style="width:80;" onclick='loadHistoricalScreen()'/>
      </div>
    </fieldset>

    <p/>

  </xsl:template>

<!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >

  </xsl:template>

</xsl:stylesheet>

