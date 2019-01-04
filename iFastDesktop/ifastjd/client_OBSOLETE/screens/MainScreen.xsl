<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />

  <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
  <xsl:variable name="vEnvName"           select="/websrvXML/FormInformation/envName"/>
  <xsl:variable name="vCompanyCode"           select="/websrvXML/FormInformation/companyCode"/>
  <xsl:variable name="vRUserId"           select="/websrvXML/FormInformation/ruserId"/>
  <xsl:variable name="vSessionId"           select="/websrvXML/FormInformation/sessionId"/>
  <xsl:variable name="vTIDX"/>

  <xsl:template match="/">

    <Screen>

      <html>
        <head>
          <xsl:call-template name="tmplBehaviours"/>

          <title>
            <xsl:choose>
              <xsl:when test=".//FormInformation/option = 'account'">
                Account Fund Limitations (Account: <xsl:value-of select=".//FormInformation/AccountNum"/>) - Inquiry
              </xsl:when>
              <xsl:otherwise>
                Broker Fund Limitations - Inquiry
              </xsl:otherwise>
            </xsl:choose>
          </title>


          <link rel="stylesheet"
            type="text/css"
            href="{$vURL}css/fundLimits_grid.css"/>

          <script src="{$vURL}javascript/desktopBase.js">
            // comment. pls keep
          </script>
          <script src="{$vURL}javascript/navigation.js">
            // comment. pls keep
          </script>
          <script src="{$vURL}javascript/FundReload.js">
            // comment. pls keep
          </script>
          <script src="{$vURL}javascript/XML_Lib.js">
              // comment. pls keep
          </script>
          <script src="{$vURL}javascript/FieldSuggest.js">
            // comment. pls keep
          </script>
          <script src="{$vURL}javascript/SuggestDropdown.js">
              // comment. pls keep
          </script>
          <script src="{$vURL}javascript/fundLimits_grid.js">
              // comment. pls keep
          </script>
          <script src="{$vURL}javascript/loading.js">
              // comment. pls keep
          </script>

          <script>
              var _imagePath = '<xsl:value-of select="$vURL"/>images';

              var _brokerSuggest = null;
              var _branchSuggest = null;
              var _salesrepSuggest = null;
              var _fundSuggest = null;
              var _currentRow = null;

              function loading()
              {
            window.status = " Account:   <xsl:value-of select=".//FormInformation/AccountNum"/> - <xsl:value-of select=".//dtOvrdLimitActInitResponse/lastName"/>";

                var servletPath = document.getElementById("fldServletPath").value;
                var cz = document.getElementById("fldCZ").value;
                var companyCode = document.getElementById("fldCompanyCode").value;
                var envName = document.getElementById("fldEnvName").value;

                var ruserid = document.getElementById("fldRUserId").value;
                var sessionId = document.getElementById("fldSessionId").value;

                _brokerSuggest = new BrokerSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);
                _branchSuggest = new BranchSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);
                _salesrepSuggest = new SalesRepSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);

                _fundSuggest = new FundSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);

                // check updateStatus
                if(document.getElementById("fldUpdateStatus").value == "true")
                {
                  setUpdateStatus();
                }
              }
            </script>
        </head>


        <body style="background-color:#ECE9D8" bgcolor="white" onload="loading();">

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


          <xsl:call-template name="tmplForm"/>


        </body>

      </html>
    </Screen>

  </xsl:template>

  <!-- ======================================================================= -->
  <xsl:template name="tmplForm">



<style type="text/css">

  .backgndColour {

  background-color:#ECE9D8
  }

.bodytext {
text-align: center;
}
.mainBorder {
  height: 560px;
  width: 650px;
  border: 3px solid #000000;
  margin-top: 0px;
  margin-right: auto;
  margin-bottom: 0px;
  margin-left: auto;
  position: relative;
  text-align: left;
}
.mainBorderCover {
  height: 560px;
  width: 650px;
  border: 3px solid #000000;
  position: absolute;
  background: #B8B8B8;
  z-index:5;
  filter:alpha(opacity=50);
  display:none;
  left:0;
  }
.contentRow {
  margin-left:16px;
  margin-right:16px;
  margin-top:1px;
  margin-bottom:1px;
}
.fontTypeSize10 {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 10px;
}
.buttonFont {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 11px;
  }

.fundDropDown {
  width:320px;
  height:1.5em;
}
.boxPosition1 {
  position: absolute;
  left: 25%;
}
.spacer1 {
  position:absolute;
  left:35%;
}
.spacer2 {
  position:absolute;
  left:68%;
  }
.boxWidth1 {
  width: 150px;
}
.boxBackground {
  background-color: #ffffff;
}
  .tableFont {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 11px;
  }
.sectionTitle {
  text-align: center;
  margin-top: 0;
  margin-right: auto;
  margin-bottom: 0;
  margin-left: auto;
  padding-top: 20px;
}
.tableBorder {
  text-align:center;
  border: 3px solid #000000;
  height: 334px;
  width: 616px;
  position: absolute;
  bottom: 40px;
}
.mainTitle {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 24px;
  text-align: center;
  margin: 0 auto;
  <!-- margin-left: 0em; margin-top: 0.5em; margin-bottom: 0.5em; -->
}
.btnClass {
  width:6em;
  height:30px;
  margin-right:0px;
}
.rowSpacer1 {
  margin-bottom: 5px;
  }
</style>

<script type="text/javascript">
function showHideDiv(id,option) {
  var div=document.getElementById(id);
  if (option=='hide')
  {
    div.style.display = 'none'
  }
  else if (option=='show')
  {
    div.style.display = 'block'
  }
}
function basedOnShowForm(id) {
  var obj2 = document.getElementById(id);
  if (obj2.value =='fundSponsor') {
    showHideDiv('enterSponsor','show');
    showHideDiv('enterFund','hide');
    showHideDiv('enterClass','hide');
  }
  else if (obj2.value =='specificFunds'){
    showHideDiv('enterSponsor','hide');
    showHideDiv('enterFund','show');
    showHideDiv('enterClass','hide');
  }
  else if (obj2.value =='specificClass'){
    showHideDiv('enterSponsor','hide');
    showHideDiv('enterFund','hide');
    showHideDiv('enterClass','show');
  }
  else {
    //none selected
  }
}
function rootType() {
  if (document.getElementById('tempDropDown').value == 'brokerBranchRep') {
    showHideDiv('brokerBranchRep','show');
    showHideDiv('account','hide');
  }
  else {
    showHideDiv('brokerBranchRep','hide');
    showHideDiv('account','show');
  }
}
function enableID(id) {
  document.getElementById(id).disabled=false;
}
function hideClass() {
  classfinal = document.getElementById('fundBox').fundClass;
  if (classfinal == null || classfinal == 'undefined' || classfinal =='*' || classfinal =='' || document.getElementById('fundBox').value=='') {
    document.getElementById('classBox').style.backgroundColor = "#ffffff";
    document.getElementById('classBox').disabled=false;
  }
  else {
    document.getElementById('classBox').value="";
    document.getElementById('classBox').style.backgroundColor = "#cccccc";
    document.getElementById('classBox').disabled=true;
  }
}

</script>

<!--this is where the main sceen goes.-->
<div class="bodytext">
  <div class="mainTitle " style="color: black">
    <xsl:choose>
      <xsl:when test=".//FormInformation/option = 'account'">
        Account Fund Limitations - Inquiry
      </xsl:when>
      <xsl:otherwise>
        Broker Fund Limitations - Inquiry
      </xsl:otherwise>
    </xsl:choose>
  </div>
  <div class="mainBorder">

    <xsl:element name="iframe">
      <xsl:attribute name="id">mainBorderCover</xsl:attribute>
      <xsl:attribute name="src"><xsl:value-of select="$vURL"/>screens/blank.html</xsl:attribute>
      <xsl:attribute name="width">100%</xsl:attribute>
      <xsl:attribute name="height">100%</xsl:attribute>
      <xsl:attribute name="frameborder">0</xsl:attribute>
      <xsl:attribute name="style">position:absolute; z-index:50; top:0; left:0; filter:alpha(opacity=20); display:none;</xsl:attribute>

      <xsl:text><![CDATA[ <!-- comment --> ]]></xsl:text>
    </xsl:element>

    <iframe id = "modifyIframe" style="position:absolute; top:155; left:-20; z-index:100; width:680;height:250; border:2px solid #B8B8B8; border-right:4px solid black; border-bottom:3px solid black; display:none;">
      <xsl:attribute name="src"><xsl:value-of select="$vURL"/>screens/blank.html</xsl:attribute>
      <xsl:text><![CDATA[ <!-- comment --> ]]></xsl:text>
    </iframe>

    <xsl:choose>
       <xsl:when test="//FormInformation/option = 'account'">
        <div id="account" class="contentRow fontTypeSize10" style="margin-top:14px; margin-bottom:10px; display:block; position:relative;">
          <span >
            Account:
          </span>
          <span id = "mainAccountNumber" class="boxPosition1">
            <xsl:value-of select=".//FormInformation/AccountNum"/> -
            <xsl:value-of select=".//dtOvrdLimitActInitResponse/lastName"/><xsl:if test="string-length(.//dtOvrdLimitActInitResponse/firstName) != 0">, <xsl:value-of select=".//dtOvrdLimitActInitResponse/firstName"/></xsl:if>
          </span>
        </div>
      </xsl:when>
      <xsl:otherwise>
        <div id="brokerBranchRep" class="fontTypeSize10" style="display:block">
          <div class="contentRow fontTypeSize10" style="margin-top:14px; margin-bottom:4px;">
            <span>
              <span class="fontTypeSize10">
                Broker:
              </span>
              <span class="fontTypeSize10" style="position:relative; left:0px;" >
                <xsl:element name="input">
                  <xsl:attribute name="id">brokerBox</xsl:attribute>
                  <xsl:attribute name="name">brokerBox</xsl:attribute>
                  <xsl:attribute name="class">fontTypeSize10 boxWidth1 boxBackground</xsl:attribute>
                  <xsl:attribute name="type">text</xsl:attribute>
                  <xsl:attribute name="value"><xsl:value-of select="//FormInformation/broker"/></xsl:attribute>
                  <xsl:attribute name="code"><xsl:value-of select="//FormInformation/broker"/></xsl:attribute>
                  <xsl:attribute name="style">position:relative; top:0; left:0</xsl:attribute>
                  <xsl:attribute name="onfocus">_brokerSuggest.init(this, document.getElementById("branchBox"), document.getElementById("repBox"));</xsl:attribute>
                </xsl:element>
              </span>
            </span>
            <span class="spacer1">
              <span id= "branchID" class="fontTypeSize10" style="position:relative; left:0px;">
                Branch:
              </span>
              <span id="branchID2" class="fontTypeSize10" style="position:relative; left:0px;">

                <xsl:element name="input">
                  <xsl:attribute name="id">branchBox</xsl:attribute>
                  <xsl:attribute name="name">branchBox</xsl:attribute>
                  <xsl:attribute name="class">fontTypeSize10 boxWidth1 boxBackground</xsl:attribute>
                  <xsl:attribute name="type">text</xsl:attribute>
                  <xsl:attribute name="value"><xsl:value-of select="//FormInformation/branch"/></xsl:attribute>
                  <xsl:attribute name="code"><xsl:value-of select="//FormInformation/branch"/></xsl:attribute>
                  <xsl:if test="string-length(.//FormInformation/broker) = 0">
                    <xsl:attribute name="disabled">true</xsl:attribute>
                  </xsl:if>
                  <xsl:attribute name="onfocus">_branchSuggest.init(document.getElementById("brokerBox"), this, document.getElementById("repBox"));</xsl:attribute>
                </xsl:element>

              </span>
            </span>
            <span class="spacer2">
              <span id="repID" class="fontTypeSize10" style="position:relative; left:0px;">
                Rep:
              </span>
              <span id="repID2" class="fontTypeSize10" type="text" value="" style="position:relative; top:0; left:0;">
                <xsl:element name="input">
                  <xsl:attribute name="id">repBox</xsl:attribute>
                  <xsl:attribute name="name">repBox</xsl:attribute>
                  <xsl:attribute name="class">fontTypeSize10 boxWidth1 boxBackground</xsl:attribute>
                  <xsl:attribute name="type">text</xsl:attribute>
                  <xsl:attribute name="value"><xsl:value-of select="//FormInformation/salesRep"/></xsl:attribute>
                  <xsl:attribute name="code"><xsl:value-of select="//FormInformation/salesRep"/></xsl:attribute>
                  <xsl:if test="string-length(.//FormInformation/branch) = 0">
                    <xsl:attribute name="disabled">true</xsl:attribute>
                  </xsl:if>
                  <xsl:attribute name="onfocus">_salesrepSuggest.init(document.getElementById("brokerBox"), document.getElementById("branchBox"), this);</xsl:attribute>
                </xsl:element>
              </span>
            </span>
          </div>
        </div>
      </xsl:otherwise>
    </xsl:choose>
    <div id="ruleType" class="contentRow fontTypeSize10 rowSpacer1" style="position:relative; height:3ex;">
      <span>
        Fund Limitation Type:
      </span>
      <span class="boxPosition1">
        <xsl:element name = "select">
          <xsl:attribute name = "name">ruleTypeDropdown</xsl:attribute>
          <xsl:attribute name = "id">ruleTypeDropdown</xsl:attribute>
          <xsl:attribute name = "class">fundDropDown fontTypeSize10 boxBackground</xsl:attribute>
            <xsl:for-each select="//List[@listName='RuleTypeOptions']/Element">
              <xsl:element name = "option">
                <xsl:attribute name="value">
                  <xsl:value-of select="code"/>
                </xsl:attribute>
                <xsl:attribute name="class">boxBackground</xsl:attribute>
                <xsl:value-of select="value"/>
              </xsl:element>
            </xsl:for-each>
        </xsl:element>
      </span>
    </div>
    <div id="fundSponsor" class="contentRow fontTypeSize10  rowSpacer1" style="position:relative; height:3ex;">
      <span>
        Fund Sponsor:
      </span>
      <span class="boxPosition1">
        <xsl:element name = "select">
          <xsl:attribute name = "name">fundSponsorDropdown</xsl:attribute>
          <xsl:attribute name = "id">fundSponsorDropdown</xsl:attribute>
          <xsl:attribute name = "class">fundDropDown fontTypeSize10 boxBackground</xsl:attribute>
          <xsl:attribute name="onchange">populateClassList(this);</xsl:attribute>
          <xsl:for-each select="//List[@listName='FundSponsorList']/Element">
            <xsl:element name = "option">
              <xsl:attribute name="value">
                <xsl:value-of select="value"/>
              </xsl:attribute>
              <xsl:attribute name="class">boxBackground</xsl:attribute>
              <xsl:attribute name="fundSponsorClassList">
                <xsl:call-template name="tmplFundSponsorClassList">
                  <xsl:with-param name="fundSponsor"><xsl:value-of select="value"/></xsl:with-param>
                </xsl:call-template>
              </xsl:attribute>
              <xsl:value-of select="value"/>
            </xsl:element>
          </xsl:for-each>
        </xsl:element>
      </span>
    </div>
    <div id="fundListBasedOn" class="contentRow fontTypeSize10 rowSpacer1" style="position:relative; height:3ex; z-index:1;">
      <span style="position:absolute;">
        Fund:
      </span>
      <span id= "mainFund" class="boxPosition1">
        <xsl:element name="input">
          <xsl:attribute name="id">fundBox</xsl:attribute>
          <xsl:attribute name="class">fontTypeSize10 boxBackground</xsl:attribute>
          <xsl:attribute name="name">fundBox</xsl:attribute>
          <xsl:attribute name="type">text</xsl:attribute>
          <xsl:attribute name="value"></xsl:attribute>
          <xsl:attribute name="style">position:relative; top:0; left:0; width:320px</xsl:attribute>
          <xsl:attribute name="onfocus">_fundSuggest.init(this, false, document.getElementById("fundSponsorDropdown").value);</xsl:attribute>
          <xsl:attribute name="onblur">hideClass();</xsl:attribute>
        </xsl:element>
      </span>
      <span style="position:relative; left:477px;">
        <img src="{$vURL}images/help.gif" alt="Search Fund by Fund/Class/ISIN, WKN"/>
      </span>
    </div>
    <div id="classListBasedOn" class="contentRow fontTypeSize10" style="position:relative; height:3ex; z-index:1;">
      <span style="position:absolute;">
        Class:
      </span>
      <span id= "mainClass" class="boxPosition1">
        <span id="classSpan">
          <xsl:element name = "select">
            <xsl:attribute name = "name">classBox</xsl:attribute>
            <xsl:attribute name = "id">classBox</xsl:attribute>
            <xsl:attribute name = "class">fundDropDown fontTypeSize10 boxBackground</xsl:attribute>
            <xsl:for-each select="//List[@listName='ClassList']/Element">
              <xsl:element name = "option">
                <xsl:attribute name="value">
                  <xsl:value-of select="value"/>
                </xsl:attribute>
                <xsl:attribute name="class">boxBackground</xsl:attribute>
                <xsl:value-of select="value"/>
              </xsl:element>
            </xsl:for-each>
          </xsl:element>
        </span>
        <span style="position:relative; left:4px;">
          <input name="fundGo" type="button" value="Go" class="fontTypeSize10" onclick='FundReload();'/>
        </span>
      </span>
    </div>

    <div class="contentRow fontTypeSize10">
      <div class="sectionTitle" style="position:absolute; bottom:380px; width:616px;">
        <table width="100%">
          <tr>
            <td width="30%"><div id="loadingBar3" name = "loadingBar3" style="font-style:italic; color: #696565; font-size: 16px; display:none;">Loading...</div></td>
            <td width="40%" align="center"><span style="text-transform: uppercase; font-weight: bold; font-size: 16px;">Existing Rules</span></td>
            <td width="30%"><span class="fontTypeSize10"><input type="checkbox" name="onlyActiveBox" id="onlyActiveBox" value="yes" />Show only active records</span></td>
          </tr>
        </table>
      </div>

      <div id = "FundRuleTable" class="tableBorder">
        <div id = "accountListDiv"  style="position:absolute; left:0; top:0; height:100%; width:100%; border:1px solid #D3D3D3; overflow:scroll; background-color: #ffffff;">
          <table id="accountList" cellpadding="1" cellspacing="0" style="cursor:default; background-color: #ffffff;" width="1455px">
            <tr class="fixedHeader tableFont" style="height:28px">

              <th class="grid" width="100px" align="left">Fund Sponsor</th>
              <th class="grid" width="80px" align="left">Fund</th>
              <th class="grid" width="50px" align="left">Class</th>
              <th class="grid" width="200px" align="left">Rule Type</th>
              <th class="grid" width="125px" align="left">Start Date</th>
              <th class="grid" width="125px" align="left">Stop Date</th>
              <th class="grid" width="125px" align="left">Override Amount</th>
              <th class="grid" width="100px" align="left">Stop Flag</th>
              <th class="grid" width="100px" align="left">Online EWI</th>
              <th class="grid" width="100px" align="left">Cycle EWI</th>
              <th class="grid" width="100px" align="left">ESG EWI</th>
              <th class="grid" width="125px" align="left">Status</th>
              <th class="grid" width="1px" align="left" style="display:none">Rule Type</th>
              <th class="grid" width="1px" align="left" style="display:none">ControlsID</th>
              <th class="grid" width="1px" align="left" style="display:none">overridelog</th>
              <th class="grid" width="1px" align="left" style="display:none">overrideamt</th>
              <th class="grid" width="1px" align="left" style="display:none">overridechar</th>
              <th class="grid" width="1px" align="left" style="display:none">Version</th>
              <th class="grid" width="1px" align="left" style="display:none">ModDate</th>
              <th class="grid" width="1px" align="left" style="display:none">ProcessDate</th>
              <th class="grid" width="1px" align="left" style="display:none">ModUser</th>
              <th class="grid" width="1px" align="left" style="display:none">UserName</th>

            </tr>
          </table>
        </div>

      </div>
    </div>
    <div style="text-align:right; position: absolute; bottom: 6px; right:10px;">
      <span>
        <input name="addBtn" type="button" id="addBtn" value="Add" class="btnClass buttonFont" onclick="goToAddPage()"/>
        </span>
      <span>
        <input name="modifyBtn" type="button" id="modifyBtn" value="Modify" disabled="true" class="btnClass buttonFont" onclick="goToModifyPage()"/>
      </span>
      <span>
        <input name="deleteBtn" type="button" id="deleteBtn" value="Delete" disabled="true" class="btnClass buttonFont" onclick="deleteRow();"/>
      </span>
      <span>
        <input name="stopLimitationsBtn" type="button" id="stopLimitationsBtn" disabled="true" value="Stop Limitations" class="btnClass buttonFont" style="width:10em;" onclick="stopLimitations();"/>
      </span>
      <span>
        <input name="adminDatesBtn" type="button" id="adminDatesBtn" disabled="true" value="Admin Dates" class="btnClass buttonFont" style="width:10em;" onclick="showAdminDates()"/>
      </span>
      <span>
        <input name="resetBtn" type="button" id="resetBtn" value="Reset" class="btnClass buttonFont" onclick='document.location.reload();'/>
      </span>
      <span>
        <input name="moreBtn" type="button" id="moreBtn" disabled="true" value="More" class="btnClass buttonFont" onclick='FundReload("more")'/>
      </span>
    </div>
  </div>

</div>

  </xsl:template>

  <xsl:template name="tmplBehaviours">
  </xsl:template>

  <xsl:template name="tmplFundSponsorClassList">
    <xsl:param name="fundSponsor"/>

    <xsl:choose>
      <xsl:when test="string-length(normalize-space($fundSponsor)) = 0">
        <xsl:for-each select="//List[@listName='ClassList']/Element"><xsl:value-of select="value"/>,</xsl:for-each>
      </xsl:when>
      <xsl:otherwise>
        <xsl:for-each select="//List[@listName='FundSponsorClassList']/Element">
          <xsl:variable name="classFundSponsor">
            <xsl:value-of select="code"/>
          </xsl:variable>
          <xsl:if test="$fundSponsor = $classFundSponsor"><xsl:value-of select="value"/>,</xsl:if>
        </xsl:for-each>
      </xsl:otherwise>
    </xsl:choose>

  </xsl:template>


</xsl:stylesheet>
