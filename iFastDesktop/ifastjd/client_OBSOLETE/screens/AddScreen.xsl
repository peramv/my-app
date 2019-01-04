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
          <xsl:call-template name="webbehaviours"/>

          <title>
            <xsl:choose>
              <xsl:when test=".//FormInformation/option = 'account'">
                  Account Fund Limitations (Account: <xsl:value-of select=".//FormInformation/accountNum"/>) - Add    
              </xsl:when>
              <xsl:otherwise>
                  Broker Fund Limitations - Add
              </xsl:otherwise>
            </xsl:choose>
          </title>
            

          <link rel="stylesheet"
            type="text/css"
            href="{$vURL}css/fundLimits_grid.css"/>

          <script src="{$vURL}javascript/desktopBase.js">
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
          <script src="{$vURL}javascript/addscreen.js">
            // comment. pls keep
          </script>
          <script src="{$vURL}javascript/loading.js">
            // comment. pls keep
          </script>

          <script>
            var _imagePath = '<xsl:value-of select="$vURL"/>/images';

            var _brokerSuggest = null;
            var _branchSuggest = null;
            var _salesrepSuggest = null;
            var _fundSuggest = null;

            function loading()
            {
              _fundSuggest = new FundSuggest(document.getElementById('fldServletPath').value, document.getElementById('fldCZ').value, document.getElementById('fldCompanyCode').value, document.getElementById('fldEnvName').value, document.getElementById('fldRUserId').value, document.getElementById('fldSessionId').value);
              
              //check updateStatus
              if(document.getElementById("fldUpdateStatus").value == "true")
              {
                setUpdateStatus();
              }
            }
          </script>

        </head>

        <body style="background-color:#ECE9D8" bgcolor="white" onload="loading();">

        <xsl:call-template name="tmplForm"/>


        </body>

      </html>
    </Screen>

  </xsl:template>

  <!-- ======================================================================= -->
  <xsl:template name="tmplForm">

      <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
      <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
      <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
      <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/' )"/>
      <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
      <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
      <xsl:variable name="vTIDX"/>

<style type="text/css">
 
  .backgndColour {

  background-color:#ECE9D8
  }
.bodytext {
text-align: center;
}
.mainBorder {
  width: 650px;
  border: 3px solid #000000;
  margin-top: 0px;
  margin-right: auto;
  margin-bottom: 0px;
  margin-left: auto;
  position: relative;
  text-align: left;
}
.contentRow {
  margin-left:16px;
  margin-right:16px;
  margin-top:5px;
  margin-bottom:1px;

}
.fundDropDown {
  width:140px;
  height:1.5em;
}
.sectionTitle {
  font-size: 16px;
  text-align: center;
  margin-top: 0px;
  margin-right: auto;
  margin-bottom: 0px;
  margin-left: auto;
  padding-top: 5px;
  padding-right: 0px;
  padding-bottom: 3px;
  padding-left: 0px;
}
.tableBorder {
  text-align:center;
  border: 3px solid #000000;
  height: 334px;
  width: 616px;
}
  .boxBackground {
  background-color: #ffffff;
  }
  .tableFont {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 11px;
  }
.tableFontError {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 11px;
  color:red;
}
.mainTitle {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 24px;
  text-align: center;
  margin: 0 auto;
  <!-- margin-left: 0em; margin-top: 0.5em; margin-bottom: 0.5em; -->
}
.brokerBanchRepBlocks {
  margin-top:4px;
  font-size: 16px;
  font-family: Arial, Helvetica, sans-serif;
}
  .fontTypeSize10 {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 10px;
  }
  .btnClass {
  width:6em;
  height:30px;
  margin-right:0px;
  }
  .buttonFont {
  font-family: Verdana, Helvetica, sans-serif;
  font-size: 11px;
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
function basedOnShowForm() {
  var obj2 = document.getElementById("basedOnShowFormId");
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
    showHideDiv('enterSponsor', 'hide');
    showHideDiv('enterFund', 'hide');
    showHideDiv('enterClass', 'hide');    
  }
}
</script>

<!--this is where the main sceen goes.-->

<div class="bodytext">
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

<xsl:attribute name="id">fldUpdateLevel</xsl:attribute>
    <xsl:attribute name="type">hidden</xsl:attribute>
    <xsl:attribute name="value"><xsl:value-of select="//FormInformation/option"/></xsl:attribute>
  </xsl:element>
  <xsl:element name="input">
    <xsl:attribute name="id">fldAccount</xsl:attribute>
    <xsl:attribute name="type">hidden</xsl:attribute>
    <xsl:attribute name="value"><xsl:value-of select="//FormInformation/accountNum"/></xsl:attribute>
  </xsl:element>
  <xsl:element name="input">
    <xsl:attribute name="id">fldBroker</xsl:attribute>
    <xsl:attribute name="type">hidden</xsl:attribute>
    <xsl:attribute name="value"><xsl:value-of select="//FormInformation/broker"/></xsl:attribute>
  </xsl:element>
  <xsl:element name="input">
    <xsl:attribute name="id">fldBranch</xsl:attribute>
    <xsl:attribute name="type">hidden</xsl:attribute>
    <xsl:attribute name="value"><xsl:value-of select="//FormInformation/branch"/></xsl:attribute>
  </xsl:element>
  <xsl:element name="input">
    <xsl:attribute name="id">fldSalesRep</xsl:attribute>
    <xsl:attribute name="type">hidden</xsl:attribute>
    <xsl:attribute name="value"><xsl:value-of select="//FormInformation/salesRep"/></xsl:attribute>
  </xsl:element>
  <xsl:element name="input">
    <xsl:attribute name="id">fldUpdateStatus</xsl:attribute>
    <xsl:attribute name="type">hidden</xsl:attribute>
    <xsl:attribute name="value"><xsl:value-of select="//FormInformation/updateStatus"/></xsl:attribute>
  </xsl:element>
  
  <div class="mainTitle">
    <xsl:choose>
      <xsl:when test=".//FormInformation/option = 'account'">
        Account Fund Limitations - Add    
      </xsl:when>
      <xsl:otherwise>
        Broker Fund Limitations - Add
      </xsl:otherwise>
    </xsl:choose>
    
  </div>
  <div class="mainBorder">
    <div id="ruleAppliesTo_Section" style="border-bottom:3px solid #000000; width:100%;">     
      <xsl:choose>
        <xsl:when test="//FormInformation/option = 'account'">
          <div id="account" class="contentRow fontTypeSize10" style="margin-top:12px; margin-bottom:4px; display:block;">
            <span>
              Account:
            </span>
            <span id="mainAccountNumber" style="position:relative; left:20px;">
              <xsl:value-of select="//FormInformation/accountNum"/> -
              <xsl:value-of select=".//dtOvrdLimitAddInitResponse/lastName"/><xsl:if test="string-length(.//dtOvrdLimitAddInitResponse/firstName) != 0">, <xsl:value-of select=".//dtOvrdLimitAddInitResponse/firstName"/></xsl:if>
            </span>
          </div>
        </xsl:when>
        <xsl:otherwise>
          <div id="brokerBranchRep" style="display:block">
            <div id="labelBlock"  class="brokerBanchRepBlocks fontTypeSize10" style="width:6em; position:absolute; top:0px; left:20px;">
              <div>
                Broker:
              </div>
              <div>
                Branch:
              </div>
              <div>
                SalesRep:
              </div>
            </div>
            <div id="codesBlock" class="brokerBanchRepBlocks fontTypeSize10" style="width:7em; position:absolute; top:0px; left:80px;">
              <div>
                <xsl:value-of select="//FormInformation/brokerCode"/>
              </div>
              <div>
                <xsl:value-of select="//FormInformation/branchCode"/>
              </div>
              <div>
                <xsl:value-of select="//FormInformation/repCode"/>
              </div>
            </div>
            <div id="fullNamesBlock" class="brokerBanchRepBlocks fontTypeSize10" style="width:14em; position:absolute; top:0px; left:120px;">
              <div>
                <xsl:value-of select="//FormInformation/broker"/>
              </div>
              <div>
                <xsl:value-of select="//FormInformation/branch"/>
              </div>
              <div>
                <xsl:value-of select="//FormInformation/salesRep"/>
              </div>
            </div>
            <div style="width:1em; height:3.6em">
              <!--spacer for base-line border-->
            </div>
          </div>
        </xsl:otherwise>
      </xsl:choose>
    </div>
    <div id="ruleType" class="fontTypeSize10" style="border-bottom:3px solid #000000;">
      <div class="contentRow" style="margin-top:10px; margin-bottom:2px; position:relative;">
        <table class="fontTypeSize10" style="width:90%">
          <tr>
            <td class="fontTypeSize10" width="17%">Rule Type:</td>
            <td width="33%" style="text-align:right">
              <xsl:element name = "select">
                <xsl:attribute name = "name">ruleTypeDropdown</xsl:attribute>
                <xsl:attribute name = "id">ruleTypeDropdown</xsl:attribute>
                <xsl:attribute name = "class">fundDropDown fontTypeSize10</xsl:attribute>
                <xsl:attribute name = "width">150px</xsl:attribute>
                <xsl:attribute name = "onchange">onRuleTypeChange(this)</xsl:attribute>
                <xsl:for-each select="//List[@listName='RuleTypeOptions']/Element">
                  <xsl:element name = "option">
                    <xsl:attribute name="value">
                      <xsl:value-of select="code"/>
                    </xsl:attribute>
                    <xsl:value-of select="value"/>
                  </xsl:element>
                </xsl:for-each>
              </xsl:element>
            </td>
            <td width="17%"></td>
            <td width="33%"></td>
          </tr>
          <tr>
            <td class="fontTypeSize10" >Start Date:</td>
            <td style="text-align:right">
              <xsl:element name="input">
                <xsl:attribute name="name">startDate</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="class">dstdatepicker fontTypeSize10</xsl:attribute>
                <xsl:attribute name="id">startDate</xsl:attribute>
                <xsl:attribute name="width">139px</xsl:attribute>
                <xsl:attribute name="style">height:1.2em;</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select=".//DefaultDates/start"/></xsl:attribute>
                <xsl:attribute name="defaultValue"><xsl:value-of select=".//DefaultDates/start"/></xsl:attribute>
                
              </xsl:element>
            </td>
            <td class="fontTypeSize10" >End date:</td>
            <td style="text-align:right">
              <xsl:element name="input">
                <xsl:attribute name="name">endDate</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="class">dstdatepicker  fontTypeSize10</xsl:attribute>
                <xsl:attribute name="id">endDate</xsl:attribute>
                <xsl:attribute name="width">139px</xsl:attribute>
                <xsl:attribute name="style">height:1.2em;</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select=".//DefaultDates/stop"/></xsl:attribute>
                <xsl:attribute name="defaultValue"><xsl:value-of select=".//DefaultDates/start"/></xsl:attribute>
              </xsl:element>
            </td>
          </tr>
        </table>
      </div>
    </div>
    <div id="fundListBasedOn" style="border-bottom:3px solid #000000;">
    <div style="position:relative">
      <div class="contentRow fontTypeSize10" style="margin-top:4px; margin-bottom:8px; position:relative">
        <span>
          Fund List Based On:
        </span>
        <span class="fontTypeSize10" style="position:absolute; right:50%">
          <select name="basedOnDropDown" class="fontTypeSize10" id = "basedOnShowFormId" onchange="basedOnShowForm();" style="width:140px">
            <option value="noneselected">Choose One...</option>
            <option value="fundSponsor">Fund Sponsor</option>
            <option value="specificFunds">Specific Funds</option>
            <option value="specificClass">Specific Class</option>
          </select>
        </span>
      </div>
      <div id="dynamicallyChangingBox">
        <!-- FUND SPONSOR ============  -->
        <div id="enterSponsor" style="display:none">
          <div id="fundSponsor" class="contentRow fontTypeSize10" style="margin-top:5px; margin-bottom:4px; position: relative; height:3ex;">
            <span>
              Fund Sponsor:
            </span>
            <span id="fundSponsor" style="position:absolute; right:50%">
              <xsl:element name = "select">
                <xsl:attribute name = "id">fundSponsor_fundSponsorDropdown</xsl:attribute>
                <xsl:attribute name = "name">fundSponsorDropdown</xsl:attribute>
                <xsl:attribute name = "class">fundDropDown fontTypeSize10</xsl:attribute>

                <xsl:for-each select="//List[@listName='FundSponsorList']/Element">
                  <xsl:element name = "option">
                    <xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
                    <xsl:value-of select="value"/>
                  </xsl:element>
                </xsl:for-each>
              </xsl:element>
            </span>
          </div>

          <div id="divFundSponsor_amt" class="contentRow fontTypeSize10" style="display:block; margin-top:2px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Amount:
            </span>
            <span style="position:absolute; right:50%;">              
              <input id="fundSponsor_amt" name="minimumInitialPurchaseBox" value="0.00" defaultValue="0.00" type="text" class="fontTypeSize10" style="width:140px" onkeydown="return validateNumeric(this)"/>
            </span>
          </div>
          <div id="divFundSponsor_flag" class="contentRow fontTypeSize10" style="display:none; margin-top:2px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Stop Flag:
            </span>
            <span style="position:absolute; right:50%;">
              <input id="fundSponsor_flag" name="minimumInitialPurchaseBox" type="text" class="fontTypeSize10" style="width:140px" value="yes"/>
            </span>
          </div>


          <div id="onlineEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:6px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Online EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="fundSponsor_onlineewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>
          <div id="cycleEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Cycle EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="fundSponsor_cycleewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>

          <div id="esgEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              ESG EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="fundSponsor_esgewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>
          <div class="contentRow" style="position:absolute; top:0px; left:350px; width:266px; height:12ex; font-size:16px; text-align:left;">
            <div class="fontTypeSize10" style="position:relative; left:4px; height:3ex; font-weight:bold; font-style:italic;">
              If Existing Rule Found:
            </div>
            <div class="fontTypeSize10" style="position:relative; height:3ex;">
              <input id="fundSponsor_exclude" class="fontTypeSize10" name="fundSponsor_ifRuleFound" checked="true" type="radio" value="exclude" />Exclude Fund From Update
            </div>
            <div class="fontTypeSize10" style="position:relative; height:3ex;">
              <input id="fundSponsor_stop" sclass="fontTypeSize10" name="fundSponsor_ifRuleFound" type="radio" value="stop" />Stop Existing Rule
            </div>
            <div id="addLimitation" class ="contentRow" style="text-align:center;">
              <input id="fundSponsor_addLimitationsBtn" class="btnClass buttonFont" style="position:relative; top:20px; width:140px;" name="addLimitationBtn" type="button" value="Add Limitations" onclick="fundSponsorLimitationsLookup();"/>
            </div>

          </div>

        </div>
        <!-- FUND ============  -->
        <div id="enterFund" style="display:none">
          <div id="fundSponsor" class="contentRow fontTypeSize10" style="margin-top:5px; margin-bottom:4px; position: relative; height:3ex;">
            <span>
              Fund Sponsor:
            </span>
            <span id="fundSponsor" style="position:absolute; right:50%">
              <xsl:element name = "select">                
                <xsl:attribute name = "id">fund_fundSponsorDropdown</xsl:attribute>
                <xsl:attribute name = "name">fundSponsorDropdown</xsl:attribute>
                <xsl:attribute name = "class">fundDropDown fontTypeSize10</xsl:attribute>
                <xsl:attribute name = "onchange">fundSponsorOnChange(this);</xsl:attribute>

                <xsl:for-each select="//List[@listName='FundSponsorList']/Element">
                  <xsl:element name = "option">
                    <xsl:attribute name="value">
                      <xsl:value-of select="value"/>
                    </xsl:attribute>
                    <xsl:value-of select="value"/>
                  </xsl:element>
                </xsl:for-each>
              </xsl:element>
            </span>
          </div>
          <div id="fundName" class="contentRow fontTypeSize10" style="margin-top:5px; margin-bottom:5px; height:3ex; position:relative">
            <span>
              Fund:
            </span>
            <span style="position:absolute; left:165px">
              <xsl:element name="input">
                <xsl:attribute name="id">fund_fundName</xsl:attribute>
                <xsl:attribute name="name">fundBox</xsl:attribute>
                <xsl:attribute name="type">text</xsl:attribute>
                <xsl:attribute name="class">fontTypeSize10</xsl:attribute>
                <xsl:attribute name="style">width:140px; position:relative; top:0px; left:0px;</xsl:attribute>
                <xsl:attribute name="value">ALL</xsl:attribute>
                <xsl:attribute name="code">ALL</xsl:attribute>
                <xsl:attribute name="fundClass"></xsl:attribute>
                <xsl:attribute name="onfocus">_fundSuggest.init(this, document.getElementById("fund_fundSponsorDropdown").selectedIndex == 0, document.getElementById("fund_fundSponsorDropdown").value);</xsl:attribute>                
              </xsl:element>              
            </span>
            <span style="position:absolute; left:305px; top:3px">
              <img src="{$vURL}images/help.gif" alt="Search Fund by Fund/Class/ISIN, WKN"/>
            </span>
          </div>

          <div id="divFund_amt" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Amount:
            </span>
            <span style="position:absolute; right:50%">
              <input name="fund_amt" id="fund_amt" class="fontTypeSize10" type="text" value="0.00" defaultValue="0.00" style="width:140px" onkeydown="return validateNumeric(this)"/>
            </span>
          </div>
          <div id="divFund_flag" class="contentRow fontTypeSize10" style="display:none; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Stop Flag:
            </span>
            <span style="position:absolute; right:50%">
              <input name="fund_flag" id="fund_flag" class="fontTypeSize10" type="text" style="width:140px" value="yes"/>
            </span>
          </div>
          <div id="onlineEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:6px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Online EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="fund_onlineewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>
          <div id="cycleEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Cycle EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="fund_cycleewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>

          <div id="esgEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              ESG EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="fund_esgewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>


          <div class="contentRow" style="position:absolute; top:0px; left:350px; width:266px; height:12ex; font-size:16px; text-align:left;">
            <div class="fontTypeSize10" style="position:relative; left:4px; height:3ex; font-weight:bold; font-style:italic;">
              If Existing Rule Found:
            </div>
            <div class="fontTypeSize10" style="position:relative; height:3ex;">
              <input id="fund_exclude" class="fontTypeSize10" name="fund_ifRuleFound" type="radio" value="exclude" checked="true" />Exclude Fund From Update
            </div>
            <div class="fontTypeSize10" style="position:relative; height:3ex;">
              <input id="fund_stop" class="fontTypeSize10" name="fund_ifRuleFound" type="radio" value="stop" />Stop Existing Rule
            </div>
            <div id="addLimitation" class ="contentRow" style="text-align:center;">
              <input id="fund_addLimitationsBtn" class="btnClass buttonFont" style="position:relative; top:20px; width:140px;" name="addLimitationBtn" type="button" value="Add Limitations" onclick="fundLimitationsLookup()"/>
            </div>
          </div>

        </div>

        <!-- CLASS ============  -->
        <div id="enterClass" style="display:none">
          <div id="fundSponsor" class="contentRow fontTypeSize10" style="margin-top:5px; margin-bottom:4px; height:3ex; position:relative">
            <span>
              Fund Sponsor:
            </span>
            <span style="position:absolute; right:50%">
              <xsl:element name = "select">
                <xsl:attribute name = "name">fundSponsorDropdown</xsl:attribute>
                <xsl:attribute name = "id">class_fundSponsorDropdown</xsl:attribute>
                <xsl:attribute name = "class">fundDropDown fontTypeSize10</xsl:attribute>
                <xsl:attribute name="onchange">populateClassList(this);</xsl:attribute>

                <xsl:for-each select="//List[@listName='FundSponsorList']/Element">
                  <xsl:element name = "option">
                    <xsl:attribute name="fundSponsorClassList">
                      <xsl:call-template name="tmplFundSponsorClassList">
                        <xsl:with-param name="fundSponsor"><xsl:value-of select="value"/></xsl:with-param>
                      </xsl:call-template>    
                    </xsl:attribute>       
                    <xsl:attribute name="value">
                      <xsl:value-of select="value"/>
                    </xsl:attribute>
                    <xsl:value-of select="value"/>
                  </xsl:element>
                </xsl:for-each>
              </xsl:element>
            </span>
          </div>
          <div id="" class="contentRow fontTypeSize10" style="margin-top:0px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Class:
            </span>
            <span style="position:absolute; right:50%">
              <xsl:element name = "select">
                <xsl:attribute name = "name">class_classBox</xsl:attribute>
                <xsl:attribute name = "id">class_classBox</xsl:attribute>
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
          </div>
          <div id="divClass_amt" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Amount:
            </span>
            <span style="position:absolute; right:50%">
              <input name="class_amt" id="class_amt" class="fontTypeSize10" type="text" style="width:140px" value="0.00" defaultValue="0.00" onclick='if(this.value=="0.00") this.select();' onkeydown="return validateNumeric(this)"/>
            </span>
          </div>
          <div id="divClass_flag" class="contentRow fontTypeSize10" style="display:none; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Stop Flag:
            </span>
            <span style="position:absolute; right:50%">
              <input name="class_flag" id="class_flag" class="fontTypeSize10" type="text" style="width:140px" value="yes"/>
            </span>
          </div>
          <div id="onlineEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:6px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Online EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="class_onlineewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>
          <div id="cycleEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              Cycle EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="class_cycleewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>

          <div id="esgEWI" class="contentRow fontTypeSize10" style="display:block; margin-top:5px; margin-bottom:5px; position:relative; height:3ex;">
            <span>
              ESG EWI:
            </span>
            <span style="position:absolute; right:50%">
              <select id="class_esgewi" class="fundDropDown fontTypeSize10">
                <option value="e">Error</option>
                <option value="w">Warning</option>
                <option value="i">Ignore</option>
              </select>
            </span>
          </div>
          <div class="contentRow" style="position:absolute; top:0px; left:350px; width:266px; height:12ex; font-size:16px; text-align:left;">
            <div class="fontTypeSize10" style="position:relative; left:4px; height:3ex; font-weight:bold; font-style:italic;">
              If Existing Rule Found:
            </div>
            <div class="fontTypeSize10" style="position:relative; height:3ex;">
              <input class="fontTypeSize10" id="class_exclude" name="class_ifRuleFound" type="radio" checked="true" value="exclude" />Exclude Fund From Update
            </div>
            <div class="fontTypeSize10" style="position:relative; height:3ex;">
              <input class="fontTypeSize10" id="class_stop" name="class_ifRuleFound" type="radio" value="stop" />Stop Existing Rule
            </div>

            <div id="addLimitation" class ="contentRow" style="text-align:center;">
              <input id="class_addLimitationsBtn" class="btnClass buttonFont" style="position:relative; top:20px; width:140px;" name="addLimitationBtn" type="button" value="Add Limitations" onclick="classLimitationsLookup();" />
            </div>
          </div>


        </div>
      </div>
    </div>
    </div>
    <div class="contentRow" style="margin: 0 auto; text-align: center;">
      <div class="sectionTitle" style="position:relative; margin-top:4px; margin-left:auto; margin-right:auto; margin-bottom:4px; width:616px">
        <table width="100%">
          <tr>
            <td width="30%"><div id="loadingBar3" name = "loadingBar3" style="font-style:italic; color: #696565; font-size: 16px; display:none;">Loading...</div></td>
            <td width="40%" align="center">
              <span style="text-transform: uppercase; font-weight: bold; font-size: 16px;">Pending Updates</span>
            </td>
            <td width="30%">
              <div style="position:absolute; top:0px; right:2px; width:166px; font-size:12px; text-align:left">
                <div style="position:relative">
                  Records to be deactivated:
                  <div style="position:absolute; top:0px; right:0px;">
                    <label id="lblStoppedRecords"></label>
                  </div>
                </div>
                <div style="position:relative">
                  New Records:
                  <div style="position:absolute; top:0px; right:0px;">
                    <label id="lblNewRecords"></label>
                  </div>
                </div>
              </div>
            </td>
          </tr>
        </table>                
      </div>
      <div id = "FundRuleTable" class="tableBorder" style="position:relative; margin-left:auto; margin-right:auto;">
        <div class="boxBackground" style="position:absolute; left:0; top:0; height:100%; width:100%; border:1px solid #D3D3D3; overflow:scroll;">
          <table id="ruleList" cellpadding="1" cellspacing="0" style="cursor:default" width="1455px">
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
            </tr>


          </table>
        </div>
      </div>
    </div>
    <div  class="contentRow" style="text-align:right;">
      <span>
        <input name="deleteBtn" type="button" class="btnClass buttonFont" id="deleteBtn" value="Delete" disabled="true" style="width:6em; height:29px; margin-right:0px;" onclick="deleteRules();"/>
        </span>
      <span>
        <input name="commitBtn" type="button" class="btnClass buttonFont" id="commitBtn" value="OK" disabled="true" style="width:6em; height:29px; margin-right:0px;" onclick="submitRules();"/>
        </span>
      <span>
        <input name="cancelBtn" type="button" class="btnClass buttonFont" id="cancelBtn" value="Cancel" style="width:6em; height:29px;" onclick="cancel();"/>
      </span>
    </div>
  </div>
</div>

  </xsl:template>

  <!-- ============================= WEB BEHAVIOURS TEMPLATE - start  ======================== -->
  <xsl:template name="webbehaviours">

    <link rel="stylesheet" href="{$vURL}behaviors/ta2000.css" type="text/css" />

    <style type="text/css">

      input.dstdatepicker{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstdatepicker/dstdatepicker.htc)}

    </style>
  </xsl:template>
  <!-- ============================= WEB BEHAVIOURS TEMPLATE - end  ======================== -->

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
