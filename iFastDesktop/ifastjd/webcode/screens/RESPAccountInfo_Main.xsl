<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">RESP Account Information</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	<xsl:variable name="AccountInfoNode" select="/websrvXML/dtRESPAcctInfoInitResponse/RESPAccountInfo"/>
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/RESPAccountInfo.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/RESPAccountInfo.js"></script>
		
		<script>
			_accountNum = "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>";
			_origMatureDate = "<xsl:value-of select="$AccountInfoNode/origMatureDt"/>";
			_taxType = "<xsl:value-of select="$AccountInfoNode/taxType"/>";
			_version = "<xsl:value-of select="$AccountInfoNode/version"/>";
			_allowMod = ( "<xsl:value-of select="/websrvXML/dtRESPAcctInfoInitResponse/Permission/modPerm"/>" == "yes" );
		</script>
		
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">DTCPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">380</xsl:with-param>
			<xsl:with-param name="height">140</xsl:with-param>
			<xsl:with-param name="top">130</xsl:with-param>
			<xsl:with-param name="left">292</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="DTCPopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>
		
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">HistoryPopupDiv</xsl:with-param>
			<xsl:with-param name="caption">Historical Information</xsl:with-param>
			<xsl:with-param name="width">644</xsl:with-param>
			<xsl:with-param name="height">225</xsl:with-param>
			<xsl:with-param name="top">70</xsl:with-param>
			<xsl:with-param name="left">145</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="DesktopHistoricalPopupTmpl"/></xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >		
		<div class="ScreenSectionDiv" style="height:110px;">
			
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">
					Plan Number:
				</span>
				<span class="FldValueSpan">
					<span class="StaticFldValue" id="planNumberFld">
						<xsl:value-of select="$AccountInfoNode/planNo"/>
					</span>
				</span>
				<span class="FldSpacerSpan"/>
				<span class="FldLabelSpan">
					RESP Status:
				</span>
				<span class="FldValueSpan">
					<select class="FldInput" id="respStatFld">
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">RESPStatOpt</xsl:with-param>
							<xsl:with-param name="curVal" select="$AccountInfoNode/respStat"/>
						</xsl:call-template>
					</select>
				</span>
			</div>
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">
					Mature Date:
				</span>
				<span class="FldValueSpan">
					<input id="matureDateFld" ifdsDatepicker="true" class="Desktop_Datepicker FldInput dateFld" valueSetCallback="changeHandler_matureDateFld()">
						<xsl:attribute name="value"><xsl:value-of select="$AccountInfoNode/matureDt"/></xsl:attribute>
					</input>
				</span>
				<span class="FldSpacerSpan"/>
				<span class="FldLabelSpan">
					Inception Date:
				</span>
				<span class="FldValueSpan">
					<input id="inceptionDateFld" ifdsDatepicker="true" class="Desktop_Datepicker FldInput dateFld" valueSetCallback="changeHandler_inceptionDateFld()">
						<xsl:attribute name="value"><xsl:value-of select="$AccountInfoNode/incepDt"/></xsl:attribute>
					</input>
				</span>
			</div>
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">
					Grandfathered:
				</span>
				<span class="FldValueSpan">
					<span class="StaticFldValue" id="grandFatheredFld" style="text-transform:uppercase">
						<xsl:value-of select="$AccountInfoNode/grandFather"/>
					</span>
				</span>
				<span class="FldSpacerSpan"/>
				<span class="FldLabelSpan">
					Sibling Only:
				</span>
				<span class="FldValueSpan">
					<select class="FldInput" id="siblingOnlyFld">
						<xsl:attribute name="onchange">changeHandler_siblingOnlyFld()</xsl:attribute>
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">SiblingOnlyOpt</xsl:with-param>
							<xsl:with-param name="curVal" select="$AccountInfoNode/siblingOnly"/>
						</xsl:call-template>
					</select>
				</span>
			</div>
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">
					Reported to HRDC:
				</span>
				<span class="FldValueSpan">
					<select class="FldInput" id="reportToHRDCFld">
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">RepHRDCOpt</xsl:with-param>
							<xsl:with-param name="curVal" select="$AccountInfoNode/repHRDC"/>
						</xsl:call-template>
					</select>
				</span>
				<span class="FldSpacerSpan"/>
				<span class="FldLabelSpan">
					Reporting Required:
				</span>
				<span class="FldValueSpan">
					<select class="FldInput" id="reportingReqFld">
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">RepReqdOpt</xsl:with-param>
							<xsl:with-param name="curVal" select="$AccountInfoNode/repReqd"/>
						</xsl:call-template>
					</select>
				</span>
			</div>	
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">
					Pre-98 Contribution:
				</span>
				<span class="FldValueSpan">
					<select class="FldInput" id="pre98ContrFld">
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">Pre98ContribOpt</xsl:with-param>
							<xsl:with-param name="curVal" select="$AccountInfoNode/pre98Contr"/>
						</xsl:call-template>
					</select>
				</span>
				<span class="FldSpacerSpan"/>				
			</div>	
		</div>
		
		<div class="ScreenSectionDiv" style="height:155px;">								
			<div id="BenDetails_TableDiv" class="Desktop_TableDiv" style="height:150px; width:936px; position:absolute;">
				<table id="BenDetails_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true">
					<thead>
						<tr>															
							<td>
								<xsl:attribute name="style">width:200</xsl:attribute>
								<xsl:attribute name="columnWidth">200</xsl:attribute>
								Beneficiary Name
							</td>
							<td>
								<xsl:attribute name="style">width:75</xsl:attribute>
								<xsl:attribute name="columnWidth">75</xsl:attribute>
								Allocation %
							</td>
							<td>
								<xsl:attribute name="style">width:100</xsl:attribute>
								<xsl:attribute name="columnWidth">100</xsl:attribute>
								Relationship
							</td>	
							<td>
								<xsl:attribute name="style">width:85</xsl:attribute>
								<xsl:attribute name="columnWidth">85</xsl:attribute>
								Date of Birth
							</td>	
							<td>
								<xsl:attribute name="style">width:120</xsl:attribute>
								<xsl:attribute name="columnWidth">120</xsl:attribute>
								Termination Date of Contribution
							</td>	
							<td>
								<xsl:attribute name="style">width:75</xsl:attribute>
								<xsl:attribute name="columnWidth">75</xsl:attribute>
								Reported to HRDC
							</td>																						
							<td>
								<xsl:attribute name="style">width:120</xsl:attribute>
								<xsl:attribute name="columnWidth">120</xsl:attribute>
								Tax Jurisdiction
							</td>
							<td>
								<xsl:attribute name="style">width:60</xsl:attribute>
								<xsl:attribute name="columnWidth">60</xsl:attribute>
								Tainted
							</td>
							<td>
								<xsl:attribute name="style">width:80</xsl:attribute>
								<xsl:attribute name="columnWidth">80</xsl:attribute>
								Tainted End Date
							</td>
						</tr>
					</thead>
					<tbody>
						<xsl:for-each select="/websrvXML/dtRESPAcctInfoInitResponse/BeneficiaryInformation/BeneficiaryDetails">
							<tr>
								<td><xsl:value-of select="benName"/></td>
								<td><xsl:value-of select="allocPrcnt"/></td>
								<td><xsl:value-of select="reltn"/></td>
								<td><xsl:value-of select="dtBirth"/></td>
								<td><xsl:value-of select="terminDt"/></td>
								<td><xsl:value-of select="repHRDC"/></td>										
								<td><xsl:value-of select="taxjuris"/></td>
								<td><xsl:value-of select="tainted"/></td>
								<td><xsl:value-of select="taintendDt"/></td>
							</tr>
						</xsl:for-each>
					</tbody>					
				</table>
			</div>
		</div>	
		
		
		<div class="ScreenSectionDiv" style="height:70px;">
			<div id="RegStatus_TableDiv" class="Desktop_TableDiv" style="height:65px; width:621px; position:absolute;">
				<table id="RegStatus_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
					<thead>
						<tr>															
							<td>
								<xsl:attribute name="style">width:200</xsl:attribute>
								<xsl:attribute name="columnWidth">200</xsl:attribute>
								Registration Status
							</td>
							<td>
								<xsl:attribute name="style">width:200</xsl:attribute>
								<xsl:attribute name="columnWidth">200</xsl:attribute>
								Reject Reason
							</td>
							<td>
								<xsl:attribute name="style">width:200</xsl:attribute>
								<xsl:attribute name="columnWidth">200</xsl:attribute>
								Process Data
							</td>																													
						</tr>
					</thead>
					<tbody>
						<xsl:for-each select="/websrvXML/dtRESPAcctInfoInitResponse/RegistrationStatusInfo/RegistrationStatusDetail">
							<tr>							
								<td><xsl:value-of select="regStat"/></td>
								<td><xsl:value-of select="rejREason"/></td>
								<td><xsl:value-of select="procDate"/></td>																	
							</tr>
						</xsl:for-each>						
					</tbody>					
				</table>
			</div>					
		</div>
		
		
		<div class="ScreenButtonsDiv">
			<input type="button" value="Historical" id="historicalBtn" class="Desktop_Btn">
				<xsl:attribute name="onclick">Desktop.displayHistorical( "HistoryPopupDiv", "RESPAccountInfo_History", {searchValue1:_accountNum} )</xsl:attribute>				
			</input>
			<input type="button" value="OK" id="okBtn" class="Desktop_Btn">
				<xsl:attribute name="onclick">clickHandler_okBtn()</xsl:attribute>				
			</input>
			
			<input type="button" style="display:none" id="btnOK" name="btnOK"/>					
				
			<input type="button" value="Cancel" id="btnCancel" name="btnCancel" class="Desktop_Btn">				
			</input>			
		</div>
	</xsl:template>
	
	
	<!-- ========================== LIST TEMPLATE =============================-->
	<xsl:template name="List_Tmpl">
		<xsl:param name="listName"/>
		<xsl:param name="curVal"/>
		
		<xsl:for-each select=".//List[@listName = $listName]/Element">
			<xsl:if test="code = $curVal">
				<option>
					<xsl:attribute name="selected">true</xsl:attribute>
					<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
					
					<xsl:value-of select="value"/>
				</option>
			</xsl:if>
			<xsl:if test="code != $curVal">
				<option>					
					<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
					
					<xsl:value-of select="value"/>
				</option>
			</xsl:if>
		</xsl:for-each>
	</xsl:template>
	
	<!-- ========================== DTC POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="DTCPopupContents_tmpl">
				
		<div style="padding:10px;">				
			<div class="SectionRowDiv">
				<span id="DTCPopup_QuestionLbl">
					
				</span>
			</div>
			<div style="padding-top:20px; text-align:center">
				<input type="button" value="Yes" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_DTCResponseBtn( "yes" )</xsl:attribute>					
				</input>				
				<input type="button" value="No" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_DTCResponseBtn( "no" )</xsl:attribute>					
				</input>
			</div>
		</div>		
	</xsl:template>
	
	<!-- ========================== HISTORY POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="HistoryPopupContents_tmpl">
		
		<div style="padding:10px;">				
			
		</div>		
	</xsl:template>
	
</xsl:stylesheet>