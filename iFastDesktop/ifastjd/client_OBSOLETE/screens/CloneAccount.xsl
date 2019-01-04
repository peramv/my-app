<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}client/screens/MasterLayout.xsl"/>
  
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
  <xsl:variable name="vMarket"           select="/websrvXML/FormInformation/market"/>
  <xsl:variable name="vTIDX"/>


  <xsl:template match="/">

    <xsl:call-template name="master_layout">
      <xsl:with-param name="pageTitle">Payment Search</xsl:with-param>
      <xsl:with-param name="displayTitle">false</xsl:with-param>
    </xsl:call-template>

  </xsl:template>
  

  <xsl:template name="form_callback">

			<script src="{$vURL}javascript/base.js">
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

            <script src="{$vURL}javascript/navigation.js">
            // comment. pls keep
            </script>

            <script src="{$vURL}javascript/loading.js">
            </script>
            
            <script src="{$vURL}javascript/CloneAccount.js">
            </script>            

            <script>
              var _imagePath = '<xsl:value-of select="$vURL"/>images';

              var _brokerSuggest = null;
              var _branchSuggest = null;
              var _salesrepSuggest = null;
              var _fundSuggest = null;

              function loading()
              {

                var servletPath = document.getElementById("fldServletPath").value;
                var cz = document.getElementById("fldCZ").value;
                var companyCode = document.getElementById("fldCompanyCode").value;
                var envName = document.getElementById("fldEnvName").value;

                var ruserid = document.getElementById("fldRUserId").value;
                var sessionId = document.getElementById("fldSessionId").value;

                if(document.getElementById("brokerBox") != null)
                {				  
				  
                  _brokerSuggest = new BrokerSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);

				  _branchSuggest = new BranchSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);
                  
                  _salesrepSuggest = new SalesRepSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);
                }

                _fundSuggest = new FundSuggest(servletPath, cz, companyCode, envName, ruserid, sessionId);
                
                var intermCode = '<xsl:value-of select="//DefaultValues/intermCode"/>';
                document.getElementById("cmbIntermCode").value = '<xsl:value-of select="//DefaultValues/intermCode"/>';
                document.getElementById("cmbTaxType").value = '<xsl:value-of select="//DefaultValues/taxType"/>';
                document.getElementById("cmbAcctDesign").value = '<xsl:value-of select="//DefaultValues/acctDesig"/>';  
                if( intermCode == "" )              
                {
					document.getElementById("IntermAcctNbr").disabled = true;
                }
                
                var acctDesign = document.getElementById("cmbAcctDesign").value;
				if( acctDesign != "3")
				{
					document.getElementById("cmbIntermCode").disabled = true;	
					document.getElementById("IntermAcctNbr").disabled = true;								
				}  
				
				//var market = document.getElementById("fldMarket").value;
				var enableAllEntity = '<xsl:value-of select="//CopyOptions/cloneAllEnt"/>';
				var enableDistInfo = '<xsl:value-of select="//CopyOptions/cloneDistInfo"/>';
				var enableBankInfo = '<xsl:value-of select="//CopyOptions/cloneBnkInfo"/>';
				if( enableAllEntity == "" )
				{
					document.getElementById("AllEntityBox").disabled = true;
				}
				if( enableDistInfo == "" )
				{
					document.getElementById("DistInfoBox").disabled = true;
				}
				if( enableBankInfo == "" )
				{
					document.getElementById("BankInfoBox").disabled = true;
				}
							
              }              
              
              function OnchangeAcctDesign()
              {              
                var acctDesign = document.getElementById("cmbAcctDesign").value;
				var cmbTaxType = document.getElementById("cmbTaxType");
				cmbTaxType.deleteAllRows();	
				
				var xmlString = "<newdataset>";

                <xsl:for-each select="//List[@listName='TaxTypeValidAcctDesignation']/Element">
                        if( acctDesign == '<xsl:value-of select="value"/>' )
						{
							var TaxTypeValue = getTaxType('<xsl:value-of select="code"/>');
						    if ( TaxTypeValue != '-1' )
						    {
								xmlString += "<combobox>";
								xmlString += "  <display>  " + TaxTypeValue + "</display>";
								xmlString += "  <formfield>" + '<xsl:value-of select="code"/>' + "</formfield>";
								xmlString += "</combobox>";                        
							}
						}
                </xsl:for-each>

				xmlString += "</newdataset>";

				cmbTaxType.addRows( xmlString );
				cmbTaxType.selectedIndex = 0;	
				
				if( acctDesign != "3")
				{
					document.getElementById("cmbIntermCode").value = "";
					document.getElementById("cmbIntermCode").disabled = true;	
					document.getElementById("IntermAcctNbr").value = "";
					document.getElementById("IntermAcctNbr").disabled = true;								
				}
				else
				{
					document.getElementById("cmbIntermCode").disabled = false;			
				}
              }
              
              function getTaxType(taxtypecode)
              {
				<xsl:for-each select="//List[@listName='TaxTypeOptions']/Element">
                        if( taxtypecode == '<xsl:value-of select="code"/>' )
						{
							return '<xsl:value-of select="value"/>';
						}
                </xsl:for-each>
                return '-1';
              }
             
             function OnchangeIntermCode()
             {             
				var intermCode = document.getElementById("cmbIntermCode").value;
				
				if( intermCode == "" )
				{
					document.getElementById("IntermAcctNbr").value = "";
					document.getElementById("IntermAcctNbr").disabled = true;
				}
				else
				{
					document.getElementById("IntermAcctNbr").disabled = false;
				}
             }
             
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
			<xsl:attribute name="blah"><xsl:value-of select="$vRUserId"/></xsl:attribute>
            <xsl:attribute name="value"><xsl:value-of select="$vRUserId"/></xsl:attribute>
          </xsl:element>

          <xsl:element name="input">
            <xsl:attribute name="id">fldSessionId</xsl:attribute>
            <xsl:attribute name="type">hidden</xsl:attribute>
            <xsl:attribute name="value"><xsl:value-of select="$vSessionId"/></xsl:attribute>
          </xsl:element>
          
          <xsl:element name="input">
            <xsl:attribute name="id">fldCreateSaleRep</xsl:attribute>
            <xsl:attribute name="type">hidden</xsl:attribute>
            <xsl:attribute name="value">no</xsl:attribute>
          </xsl:element>
          
          <xsl:element name="input">
            <xsl:attribute name="id">fldMarket</xsl:attribute>
            <xsl:attribute name="type">hidden</xsl:attribute>
            <xsl:attribute name="value"><xsl:value-of select="$vMarket"/></xsl:attribute>
          </xsl:element>    
          
          <xsl:element name="input">
            <xsl:attribute name="id">fldallowBrUpd</xsl:attribute>
            <xsl:attribute name="type">hidden</xsl:attribute>
            <xsl:attribute name="value"><xsl:value-of select="//DefaultValues/allowBrUpd"/></xsl:attribute>
          </xsl:element>                            
          
<!--this is where the main sceen goes.-->
    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>

    <div id="initial" style="postion:absolute; left:25; top:50; width:750px; border:1px double #CCCCCC">
    
      <div id="divCloneAccount" style="position:relative; left:27; top:-10" >
        <label> New Account Parameters:</label>
      </div>
             
            <table>
              <tr>
				<td>
					Broker:
				</td>
				<td style="position:relative; left:0px;" >
					<xsl:element name="input">
					<xsl:attribute name="id">brokerBox</xsl:attribute>
					<xsl:attribute name="name">brokerBox</xsl:attribute>
					<xsl:attribute name="type">text</xsl:attribute>
					<xsl:attribute name="value"><xsl:value-of select="//DefaultValues/broker"/></xsl:attribute>
					<xsl:attribute name="code"><xsl:value-of select="//DefaultValues/broker"/></xsl:attribute>
					<xsl:attribute name="style">position:relative; top:0; left:0</xsl:attribute>
					<xsl:attribute name="onfocus">_brokerSuggest.init2( this, document.getElementById("branchBox"), document.getElementById("repBox"), document.getElementById("brokerName"), document.getElementById("branchName"), document.getElementById("repName"), document.getElementById("fldallowBrUpd").value);</xsl:attribute>					
					</xsl:element>
				</td> 
				<td colspan="3">
					<div id="brokerName">
						<xsl:value-of select="//DefaultValues/brokerName"/>
					</div>
				</td>				           
              </tr>
              <tr>
				<td id= "branchID" style="position:relative; left:0px;">
					Branch:
				</td>
				<td id="branchID2" style="position:relative; left:0px;">

					<xsl:element name="input">
					<xsl:attribute name="id">branchBox</xsl:attribute>
					<xsl:attribute name="name">branchBox</xsl:attribute>
					<xsl:attribute name="type">text</xsl:attribute>
					
					<xsl:if test="//DefaultValues/allowBrUpd = 'no'">
						<xsl:attribute name="value"></xsl:attribute>
						<xsl:attribute name="code"></xsl:attribute>					
						<xsl:attribute name="disabled">true</xsl:attribute>
					</xsl:if>
					
					<xsl:if test="not(//DefaultValues/allowBrUpd = 'no')">
						<xsl:attribute name="value"><xsl:value-of select="//DefaultValues/branch"/></xsl:attribute>
						<xsl:attribute name="code"><xsl:value-of select="//DefaultValues/branch"/></xsl:attribute>					
						<xsl:attribute name="onfocus">_branchSuggest.init2(document.getElementById("brokerBox"), this, document.getElementById("repBox"), document.getElementById("branchName"), document.getElementById("repName"));</xsl:attribute>
					</xsl:if>
				
					</xsl:element>

				</td>              
				<td colspan="3">
					<div id="branchName">
						<xsl:if test="not(//DefaultValues/allowBrUpd = 'no')">
							<xsl:value-of select="//DefaultValues/branchName"/>
						</xsl:if>
					</div>
				</td>				
              </tr>
              <tr>
				<td id="repID" style="position:relative; left:0px;">
					Sales rep:
				</td>
				<td id="repID2" type="text" value="" style="position:relative; top:0; left:0;">                
					<xsl:element name="input">
					<xsl:attribute name="id">repBox</xsl:attribute>
					<xsl:attribute name="name">repBox</xsl:attribute>
					<xsl:attribute name="type">text</xsl:attribute>
					<xsl:attribute name="value"><xsl:value-of select="//DefaultValues/slsRep"/></xsl:attribute>
					<xsl:attribute name="code"><xsl:value-of select="//DefaultValues/slsRep"/></xsl:attribute>
					<xsl:if test="not(//DefaultValues/slsRep)">
						<xsl:attribute name="disabled">true</xsl:attribute>
					</xsl:if>
					<xsl:attribute name="onfocus">_salesrepSuggest.init2(document.getElementById("brokerBox"), document.getElementById("branchBox"), this, document.getElementById("repName"), document.getElementById("fldCreateSaleRep"), document.getElementById("branchName"));</xsl:attribute>					
					</xsl:element>
				</td> 
				<td colspan="5">
					<div id="repName">
						<xsl:value-of select="//DefaultValues/slsRepName"/>
					</div>
				</td>					             
              </tr>
              
              
			<tr>
				<td>
					<label> Acct design:</label>
				</td>
				<td style="position:relative; left:0px;">
					<!--select id="cmbAcctDesign"  style="width:160px" onchange="OnchangeAcctDesign()">
						<xsl:for-each select="//List[@listName='AcctDesignationsOptions']/Element">
						<option>
							<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
							<xsl:value-of select="value"/>
						</option>
						</xsl:for-each>
					</select-->
					<input type="hidden" class="dstcombobox" formfield="formfield" name="cmbAcctDesign" id="cmbAcctDesign" data="xmlcmbAcctDesign"  tabindex = "4" width="160px" onchange="OnchangeAcctDesign()" />
                          <xml id="xmlcmbAcctDesign">
                              <newdataset>
                                  <xsl:for-each select="//List[@listName='AcctDesignationsOptions']/Element">
                                      <combobox>
                                          <display><xsl:value-of select="value"/></display>
                                          <formfield><xsl:value-of select="code"/></formfield>
                                      </combobox>
                                  </xsl:for-each>
                              </newdataset>
                          </xml>        					
				</td>
				<td>
					<label> Tax Type:</label>
				</td>
				<td style="position:relative; left:0px;" colspan="3">
					<!--select id="cmbTaxType"  style="width:160px" onchange="" >
						<xsl:for-each select="//List[@listName='TaxTypeOptions']/Element">
						<option>
							<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
							<xsl:value-of select="value"/>					
						</option>
						</xsl:for-each>
					</select-->
					
					
					<input type="hidden" class="dstcombobox" formfield="formfield" name="cmbTaxType" id="cmbTaxType" data="xmlcmbTaxType"  tabindex = "4" width="260px" />
                          <xml id="xmlcmbTaxType">
                              <newdataset>
                                  <xsl:for-each select="//List[@listName='TaxTypeOptions']/Element">
                                      <combobox>
                                          <display><xsl:value-of select="value"/></display>
                                          <formfield><xsl:value-of select="code"/></formfield>
                                      </combobox>
                                  </xsl:for-each>
                              </newdataset>
                          </xml>					
				</td>
			</tr> 
			
			
			<tr>
				<td >
					<label> Alt acct nbr:</label>
				</td>
				<td style="position:relative; left:0px;" >
					<xsl:element name="input">
						<xsl:attribute name="id">AltAcctNbr</xsl:attribute>
						<xsl:attribute name="name">AltAcctNbr</xsl:attribute>
						<xsl:attribute name="type">text</xsl:attribute>
						<xsl:attribute name="value"><xsl:value-of select="//DefaultValues/altAcct"/></xsl:attribute>
					</xsl:element>
				</td>
				<td>
					<label> Effective Date: </label>
				</td>
				<td style="position:relative; left:0px;" >
					<input type="text" id="EffectiveDate" class="dstdatepicker" width="100px" maxlength="10">
						<xsl:attribute name="value"><xsl:value-of select="//DefaultValues/effectDt"/></xsl:attribute>
					</input>
				</td> 				
			</tr> 
			
			
			<tr>
				<td>
					<label> Interm. code:</label>
				</td>
				<td style="position:relative; left:0px;" colspan="3">
					<!--select id="cmbIntermCode"  style="width:350px" onchange="OnchangeIntermCode()" >
						<xsl:for-each select="//List[@listName='IntermediaryOptions']/Element">
						<option>
							<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
							<xsl:value-of select="value"/>
						</option>
						</xsl:for-each>						
					</select-->
					<input type="hidden" class="dstcombobox" formfield="formfield" name="cmbIntermCode" id="cmbIntermCode" data="xmlcmbIntermCode"  tabindex = "4" width="350px" onchange="OnchangeIntermCode()"/>
                          <xml id="xmlcmbIntermCode">
                              <newdataset>
                                  <xsl:for-each select="//List[@listName='IntermediaryOptions']/Element">
                                      <combobox>
                                          <display><xsl:value-of select="value"/></display>
                                          <formfield><xsl:value-of select="code"/></formfield>
                                      </combobox>
                                  </xsl:for-each>
                              </newdataset>
                          </xml>						
				</td>          
				<td>
					<label> Interm. acct nbr:</label>
				</td>
				<td style="position:relative; left:0px;" >
					<xsl:element name="input">
						<xsl:attribute name="id">IntermAcctNbr</xsl:attribute>
						<xsl:attribute name="name">IntermAcctNbr</xsl:attribute>
						<xsl:attribute name="type">text</xsl:attribute>
						<xsl:attribute name="value"><xsl:value-of select="//DefaultValues/intermAcct"/></xsl:attribute>
					</xsl:element>
				</td>           
			</tr> 
			
			
			<tr>
				<td colspan="2">
					<xsl:element name="input">
						<xsl:attribute name="type">checkbox</xsl:attribute>
						<xsl:attribute name="id">DistInfoBox</xsl:attribute>
						<xsl:attribute name="name">DistInfoBox</xsl:attribute>
						<xsl:if test="//CopyOptions/cloneDistInfo='yes'">
							<xsl:attribute name="checked"/>
						</xsl:if>						
					</xsl:element>
					Distribution. info
				</td>
			</tr>
			
			<tr>
				<td >
					<xsl:element name="input">
						<xsl:attribute name="type">checkbox</xsl:attribute>
						<xsl:attribute name="id">BankInfoBox</xsl:attribute>
						<xsl:attribute name="name">BankInfoBox</xsl:attribute>
						<xsl:if test="//CopyOptions/cloneBnkInfo='yes'">
							<xsl:attribute name="checked"/>
						</xsl:if>						
					</xsl:element>				
					<!--input type="checkbox" name="BankInfoBox" id="BankInfoBox" value="no" /-->
					Bank info
				</td>			
			</tr>
			
			<tr>
				<td >                				
					<xsl:element name="input">
						<xsl:attribute name="type">checkbox</xsl:attribute>
						<xsl:attribute name="id">AllEntityBox</xsl:attribute>
						<xsl:attribute name="name">AllEntityBox</xsl:attribute>
						
						<xsl:if test="//CopyOptions/cloneAllEnt='yes'">
							<xsl:attribute name="checked"/>
						</xsl:if>						
					</xsl:element>				
					All Entities
				</td>			
			</tr>
		
			<p/>               
              
            </table>
			
	</div>
  	<div align="right" style="position:relative; width:750px;">
		<input id="btnOK" name="btnOK" type="button" value="OK" style="width:80;"/>
  		<input id="btnCancel" name="btnCancel" type="button" value="Cancel" style="width:80;"/>		
  	</div>
	
	<!--input type="button" name="btnOK" value="OK" id="btnOK" style="width:150px" onclick="update()" /-->
  </xsl:template>
  
  <!-- ========================== PAGE CALLBACK TEMPLATE ===================================-->
  <xsl:template name="page_callback" >

  </xsl:template>
  
</xsl:stylesheet>
