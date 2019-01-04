<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
  <xsl:variable name="vEnvName"           select="/websrvXML/FormInformation/envName"/>
  <xsl:variable name="vRUserId"           select="/websrvXML/FormInformation/ruserId"/>
  <xsl:variable name="vCompanyCode"           select="/websrvXML/FormInformation/companyCode"/>
  <xsl:variable name="vSessionId"           select="/websrvXML/FormInformation/sessionId"/>
  <xsl:variable name="vTIDX"/>

  <xsl:template match="/">

    <Screen>

      <html>
        <head>          
        	<xsl:call-template name="tmplBehaviours"/>
        	<xsl:call-template name="webbehaviours"/>
        	<title>Fund Limitations - Modify</title>
        	
        	<link rel="stylesheet"
        		type="text/css"
        		href="{$vURL}css/fundLimits_grid.css"/>
        		
        	<script src="{$vURL}javascript/XML_Lib.js">
              // comment. pls keep
            </script>
            <script src="{$vURL}javascript/FieldSuggest.js">
              // comment. pls keep
            </script>
            <script src="{$vURL}javascript/SuggestDropdown.js">
              // comment. pls keep
            </script>
            
            <script src="{$vURL}javascript/FundReload.js">
              // comment. pls keep
            </script>
        	<script src="{$vURL}javascript/modifySubmit.js">
        		// comment. pls keep
        	</script>
        	<script src="{$vURL}javascript/fundLimits_grid.js">
        		// comment. pls keep
        	</script>
            
            <script>
            	var _accountNumber = '<xsl:value-of select="//FormInformation/accountNum"/>';
            	var _broker		   = '<xsl:value-of select="//FormInformation/broker"/>'; 
            	var _branch        = '<xsl:value-of select="//FormInformation/branch"/>'; 
            	var _salesRep      = '<xsl:value-of select="//FormInformation/salesRep"/>';  
            	var _ruletype      = '<xsl:value-of select="//FormInformation/ruleTypeCode"/>'; 
            	var _startDate     = '<xsl:value-of select="//FormInformation/startDate"/>'; 
            	var _stopDate      = '<xsl:value-of select="//FormInformation/endDate"/>'; 
            	var _fund		   = '<xsl:value-of select="//FormInformation/fund"/>';
            	var _class		   = '<xsl:value-of select="//FormInformation/class"/>';
            	var _ruleTypeCode  = '<xsl:value-of select="//FormInformation/ruleTypeCode"/>';
            	var _controlsId    = '<xsl:value-of select="//FormInformation/controlsid"/>';
            	var _version       = '<xsl:value-of select="//FormInformation/version"/>';
            	
              function loading()
              {                

            	var esgSelectBox    = document.getElementById('esgSelectBox');
            	var onlineSelectBox = document.getElementById('onlineSelectBox');
            	var cycleSelectBox  = document.getElementById('cycleSelectBox');

            	switch('<xsl:value-of select="//FormInformation/ESGEWI"/>')
            	{
            		case 'e': esgSelectBox.selectedIndex = 0;break;
	            	case 'w': esgSelectBox.selectedIndex = 1;break;
	            	case 'i': esgSelectBox.selectedIndex = 2;break;
	            	default: break;
            	}
            	switch('<xsl:value-of select="//FormInformation/cycleEWI"/>')
            	{
	            	case 'e': cycleSelectBox.selectedIndex = 0;break;
	            	case 'w': cycleSelectBox.selectedIndex = 1;break;
	            	case 'i': cycleSelectBox.selectedIndex = 2;break;
	            	default: break;
            	}
            	switch('<xsl:value-of select="//FormInformation/onlineEWI"/>')
            	{
	            	case 'e': onlineSelectBox.selectedIndex = 0;break;
	            	case 'w': onlineSelectBox.selectedIndex = 1;break;
	            	case 'i': onlineSelectBox.selectedIndex = 2;break;
	            	default: break;
            	}
            	
              }
            </script>
        </head>
        

      	<body bgcolor="white" onload="loading();" style="position:absolute; left:10; top:5; border:0px solid black; background-color:#ECE9D8">

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
	height: 200px;
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
	margin-top:1px;
	margin-bottom:1px;
	}
	.fontTypeSize10 {	
	font-family: Verdana, Helvetica, sans-serif;
	font-size: 10px;
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
	.sectionTitle {
	font-size: 16px;
	text-transform: uppercase;
	font-weight: bold;
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
	height:4ex;
	margin-right:24px;
	}
	.rowSpacer1 {
	margin-bottom: 5px;
	}
</style>

     
<!--this is where the main sceen goes.-->
  	<div class="bodytext">
  		<div class="mainTitle">
  			Fund Limitations - Modify </div>
  		<div class="mainBorder">
  			<div id="ruleAppliesTo_Section" style="border-bottom:3px solid #000000; width:100%">
  				<div class="contentRow fontTypeSize10" style="margin-top:4px; height:10px;">
  					
  				</div>
  				<xsl:choose>
  					<xsl:when test="//FormInformation/option = 'account'">
  						<div id="account" class="contentRow fontTypeSize10" style="display:block">
  							<div style="width:6em; position:absolute; top:3px; left:3%;">
  								Account:
  							</div>
  							<div style="width:7em; position:absolute; top:3px; left:20%;">
  								<xsl:value-of select="//FormInformation/accountNum"/>
  							</div> 							
  						</div>
  					</xsl:when>
  					<xsl:otherwise>
  						<div id="brokerBranchRep" style="display:block">
  							<div id="labelBlock"  class="contentRow fontTypeSize10" style="width:6em; position:absolute; top:0px; left:5%;">
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
  							<div id="codesBlock" class="contentRow fontTypeSize10" style="width:7em; position:absolute; top:0px; left:10%;">
  								<div>
  									<xsl:value-of select="//FormInformation/branchCode"/>
  								</div>
  								<div>
  									<xsl:value-of select="//FormInformation/brokerCode"/>
  								</div>
  								<div>
  									<xsl:value-of select="//FormInformation/repCode"/>
  								</div>
  							</div>
  							<div id="fullNamesBlock" class="contentRow fontTypeSize10" style="width:14em; position:absolute; top:0px; left:18%;">
  								<div style="width:450">
  									<xsl:value-of select="//FormInformation/branch"/>
  								</div>
  								<div style="width:450">
  									<xsl:value-of select="//FormInformation/broker"/>
  								</div>
  								<div style="width:450">
  									<xsl:value-of select="//FormInformation/salesRep"/>
  								</div>
  							</div>
  							<div style="width:1em; height:25px">
  								<!--spacer for base-line border-->
  							</div>						
  						</div>
  					</xsl:otherwise>
  				</xsl:choose>
  			</div>
  			<div id="ruleType" style="border-bottom:3px solid #000000;">
  				<div class="contentRow fontTypeSize10" style="margin-top:4px; margin-bottom:2px; position:relative;">
  					<table class="fontTypeSize10" style="width:90%">
  						<tr>
  							<td class="fontTypeSize10" width="15%">Rule Type:</td>
  							<td class="fontTypeSize10" width="35%" style="text-align:left">
  								<xsl:value-of select="//FormInformation/ruleType"/>
  							</td>
  							<td width="17%"></td>
  							<td width="33%"></td>
  						</tr>
  						<tr>
  							<td class="fontTypeSize10" >Start Date:</td>
  							<td class="fontTypeSize10" style="text-align:left"><xsl:value-of select="//FormInformation/startDate"/></td>
  							<td class="fontTypeSize10"><span style="margin-left:25px;text-align:right">End Date:</span></td>
  							<td class="fontTypeSize10" style="text-align:left">
  								<xsl:element name="input">
  									<xsl:attribute name="name">endDate</xsl:attribute>
  									<xsl:attribute name="id">endDateInput</xsl:attribute>
  									<xsl:attribute name="type">text</xsl:attribute>
  									<xsl:attribute name="style">width:140px; height: 14px;</xsl:attribute>
  									<xsl:attribute name="class">dstdatepicker</xsl:attribute>
  									<xsl:attribute name="value"><xsl:value-of select="//FormInformation/endDate"/></xsl:attribute>
  								</xsl:element>
  								<!--<input name="endDate" type="text" id="endDate" style="width:140px" value="01/01/2010"/>-->
  							</td>
  						</tr>
  					</table>
  				</div>			
  			</div>
  			<div id="fundListBasedOn" style="border-bottom:3px solid #000000;">
  				<div style="position:relative">
  					<div class="contentRow fontTypeSize10" style="margin-top:4px; margin-bottom:8px; position:relative">
  						<span>
  							Fund: <b><xsl:value-of select="//FormInformation/fund"/></b>
  						</span>
  						<span style="position:absolute; right:55%">
  							Class: <b><xsl:value-of select="//FormInformation/class"/></b>
  						</span>
  						
  						
  						
  					</div>
  					<div class="fontTypeSize10" style="margin-bottom:12px;" id="dynamicallyChangingBox">
  						
  						<div id="enterSponsor" style="display:block">								
  							<div id="minimumInitialPurchase" class="contentRow" style="margin-top:2px; margin-bottom:4px; position:relative; height:3ex;">  		
  								<xsl:call-template name="fundLimitation">
  									<xsl:with-param name="ruleTypeName"><xsl:value-of select="//FormInformation/ruleType"/></xsl:with-param>
  									<xsl:with-param name="ruleTypeCode"><xsl:value-of select="//FormInformation/ruleTypeCode"/></xsl:with-param>  									
  								</xsl:call-template>
  							</div>					
  							<div id="EWI" class="contentRow" style="margin-top:10px; margin-bottom:4px; position:relative; height:3ex;">
  								<span>
  									Online EWI:
  								</span>
  								<span style="position:absolute; right:73%;">
  									<select id="onlineSelectBox">
  										<option value="e">Error</option>
  										<option value="w">Warning</option>
  										<option value="i">Ignore</option>
  									</select>
  									
  								</span>
  								<span style="position:absolute; right:55%;">
  									Cycle EWI:
  								</span>
  								<span style="position:absolute; right:40%;">
  									<select id ="cycleSelectBox">
  										<option value="e">Error</option>
  										<option value="w">Warning</option>
  										<option value="i">Ignore</option>
  									</select>
  									
  								</span>
  								<span style="position:absolute; right:25%;">
  									ESG EWI:
  								</span>
  								<span style="position:absolute; right:11%;">
  									<select id = "esgSelectBox">
  										<option value="e">Error</option>
  										<option value="w">Warning</option>
  										<option value="i">Ignore</option>
  									</select>
  									
  								</span>
  							</div>  							
  						</div>  						
  					</div>
  				</div>
  			</div>
  			<div  class="contentRow fontTypeSize10" style="text-align:right;height:35;">
  				<span>
  					<input name="commitBtn" type="button" id="commitBtn" value="  OK  " style="position:relative; width:6em; height:4ex; top:5" onclick = "SubmitModify()"/>
  				</span>
  				<span>
  					<input name="cancelBtn" type="button" id="cancelBtn" value="Cancel" style="position:relative; width:6em; height:4ex; top:5;"  onclick = 'parent.closeModifyIframe("no")'/>
  				</span>
  			</div>
  		</div>
  	</div>


  </xsl:template>
  
	<xsl:template name="fundLimitation">
		<xsl:param name="ruleTypeName"/>
		<xsl:param name="ruleTypeCode"/>
		<span>
			<xsl:value-of select="$ruleTypeName"/>
		</span>
		<xsl:choose>
			<xsl:when test="$ruleTypeCode = '01'">
				<xsl:call-template name="fundLimitationAmount"/>
			</xsl:when>
			<xsl:when test="$ruleTypeCode = '02'">
				<xsl:call-template name="fundLimitationAmount"/>
			</xsl:when>
			<xsl:when test="$ruleTypeCode = '03'">
				<xsl:call-template name="fundLimitationBoolean"/>
			</xsl:when>
			<xsl:when test="$ruleTypeCode = '04'">
				<xsl:call-template name="fundLimitationBoolean"/>
			</xsl:when>
			<xsl:when test="$ruleTypeCode = '05'">
				<xsl:call-template name="fundLimitationBoolean"/>
			</xsl:when>
			<xsl:when test="$ruleTypeCode = '06'">
				<xsl:call-template name="fundLimitationBoolean"/>
			</xsl:when>
			<xsl:when test="$ruleTypeCode = '16'">
				<xsl:call-template name="fundLimitationAmount"/>
			</xsl:when>
			
		</xsl:choose>
	</xsl:template>
	
	<xsl:template name="fundLimitationAmount">
		<span style="position:absolute; right:50%;">
			<xsl:element name="input">
				<xsl:attribute name="name">minimumInitialPurchaseBox</xsl:attribute>
				<xsl:attribute name="id">overrideAmtInput</xsl:attribute>
				<xsl:attribute name="type">text</xsl:attribute>
				<xsl:attribute name="style">width:120px</xsl:attribute>
				<xsl:attribute name="value">
					<xsl:choose>
						<xsl:when test="string-length(//FormInformation/minInitPurchase) = 0">0.00</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="//FormInformation/minInitPurchase"/>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:attribute>
				<xsl:attribute name="onkeydown">return validateNumeric(this)</xsl:attribute>
			</xsl:element>			
		</span>		
	</xsl:template>
	
	<xsl:template name="fundLimitationBoolean">
		<span style="position:absolute; right:60%;">
			YES
		</span> 
	</xsl:template>
  
  <xsl:template name="tmplBehaviours">

  </xsl:template>
	
	<!-- ============================= WEB BEHAVIOURS TEMPLATE - start  ======================== -->
	<xsl:template name="webbehaviours">
		
		<link rel="stylesheet" href="{$vURL}behaviors/ta2000.css" type="text/css" />
		
		<style type="text/css">
			
			input.dstdatepicker{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstdatepicker/dstdatepicker.htc)}
			
		</style>
	</xsl:template>
	<!-- ============================= WEB BEHAVIOURS TEMPLATE - end  ======================== -->
	
  
</xsl:stylesheet>
