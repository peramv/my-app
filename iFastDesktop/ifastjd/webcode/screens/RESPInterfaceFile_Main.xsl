<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
		<xsl:with-param name="pageTitle">RESP Interface File</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/RESPInterfaceFile.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/RESPInterfaceFile.js"></script>
		<script>					
			_accountNum = "<xsl:value-of select="/*/FormInformation/AccountNum"/>";
		</script>		
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >			
		<div class="ScreenSectionDiv" style="height:107px; margin-top:7px;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="font-weight:bold">
					Interface File Content Inquiry
				</div>
				<div class="FieldSetContentsDiv">
					<div class="SectionRowDiv">
						<span class="FldLabelSpan" style="width:100px;">
							Account:
						</span>
						<span class="FldValueSpan" style="text-align:left; width:600px;">
							<input suggestField="true" 				  				      
								type="text"
								id="accountFld"
								disabled="true"			
								dropdownClass="Desktop_suggestDropdown_veryBig"
								contentClass="Desktop_suggestDropdownContent"
								highlightClass="Desktop_suggestDropdownHighlight"
								displayItems="displayValue"
								updateCallbackFn="updateHandler_accountFld"
								searchURLGenerator="getAccountSuggestURL">
								<xsl:attribute name="value"><xsl:if test="/websrvXML/FormInformation/AccountNum != 'ALL'"><xsl:value-of select="/websrvXML/FormInformation/AccountNum"/> - <xsl:value-of select="/websrvXML/dtInterfaceFileInitResponse/ownerNam"/></xsl:if></xsl:attribute>
							</input>					
						</span>
						<xsl:if test="/websrvXML/FormInformation/AccountNum = 'ALL'">
							<span class="FldValueSpan" style="text-align:left; width:100px; position:relative; top:3px;">
								(<span style="font-style:italic; font-size:12px;">ALL</span> 
								<input id="allFld" type="checkbox" checked="true" onclick="clickHandler_allFld()"/>)
							</span>
						</xsl:if>									
					</div>
					<div class="SectionRowDiv">						
						<span class="FldLabelSpan" style="width:100px;">
							Beneficiary:
						</span>
						<span class="FldValueSpan" style="text-align:left; width:260px;">
							<select class="FldInput" style="width:200px;" id="respBenefFld">	
								<xsl:call-template name="List_Tmpl">
									<xsl:with-param name="listName">BeneficiaryList</xsl:with-param>									
								</xsl:call-template>				
							</select>
						</span>
						<span class="FldLabelSpan" style="width:100px;">
							File Type:
						</span>
						<span class="FldValueSpan" style="text-align:left; width:225px;">
							<select class="FldInput" style="width:225px;" id="fileTypeFld" onchange="changeHandler_fileTypeFld()">
								<xsl:call-template name="List_Tmpl">
									<xsl:with-param name="listName">FileTypeList</xsl:with-param>									
								</xsl:call-template>						
							</select>
						</span>
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan" style="width:100px;">
							Tax Year:
						</span>
						<span class="FldValueSpan" style="text-align:left; width:260px;">
							<select class="FldInput" style="width:100px;" id="taxYearFld">
								<xsl:call-template name="List_Tmpl">
									<xsl:with-param name="listName">TaxYearList</xsl:with-param>									
								</xsl:call-template>						
							</select>
						</span>		
						<span class="FldLabelSpan" style="width:100px;">
							Record Type:
						</span>
						<span class="FldValueSpan" style="text-align:left; width:225px;">
							<select class="FldInput" style="width:225px;" id="recordTypeFld">									
							</select>
						</span>
						<input id="searchBtn" type="button" value="Search" class="Desktop_Btn" onclick="clickHandler_searchBtn()"/>
					</div>
				</div>
			</div>
		</div>
					
		<div class="ScreenSectionDiv" style="height:345px; margin-top:7px;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="font-weight:bold">
					Search Results
				</div>
				<div class="FieldSetContentsDiv">
					<div id="FileList_TableDiv" class="Desktop_TableDiv" style="height:110px; width:805px; position:absolute;">
						<table id="FileList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
							<thead>
								<tr>															
									<td>
										<xsl:attribute name="style">width:183</xsl:attribute>
										<xsl:attribute name="columnWidth">183</xsl:attribute>
										File Name
									</td>
									<td>
										<xsl:attribute name="style">width:100</xsl:attribute>
										<xsl:attribute name="columnWidth">100</xsl:attribute>
										Account
									</td>
									<td>
										<xsl:attribute name="style">width:200</xsl:attribute>
										<xsl:attribute name="columnWidth">200</xsl:attribute>
										Beneficiary (Name)
									</td>	
									<td>
										<xsl:attribute name="style">width:100</xsl:attribute>
										<xsl:attribute name="columnWidth">100</xsl:attribute>
										Record Type
									</td>										
									<td>
										<xsl:attribute name="style">width:100</xsl:attribute>
										<xsl:attribute name="columnWidth">100</xsl:attribute>
										Process Date
									</td>																						
									<td>
										<xsl:attribute name="style">width:101</xsl:attribute>
										<xsl:attribute name="columnWidth">101</xsl:attribute>
										NEQ
									</td>
								</tr>
							</thead>
							<tbody>
								
							</tbody>					
						</table>
					</div>
					<div style="position:absolute; left:0px; top:125px; width:100%; text-align:right; padding-right:20px;">
						<input type="button" class="Desktop_Btn" value="More" id="moreBtn" disabled="true" onclick="clickHandler_moreBtn()"/>
					</div>
					<div id="FieldList_TableDiv" class="Desktop_TableDiv" style="height:160px; width:805px; position:absolute; top:175px; left:6px;">
						<table id="FieldList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true">
							<thead>
								<tr>															
									<td>
										<xsl:attribute name="style">width:220</xsl:attribute>
										<xsl:attribute name="columnWidth">220</xsl:attribute>
										Field Name
									</td>
									<td>
										<xsl:attribute name="style">width:171</xsl:attribute>
										<xsl:attribute name="columnWidth">171</xsl:attribute>
										Value
									</td>
									<td>
										<xsl:attribute name="style">width:220</xsl:attribute>
										<xsl:attribute name="columnWidth">220</xsl:attribute>
										Field Name
									</td>	
									<td>
										<xsl:attribute name="style">width:173</xsl:attribute>
										<xsl:attribute name="columnWidth">173</xsl:attribute>
										Value
									</td>																															
								</tr>
							</thead>
							<tbody>
								
							</tbody>					
						</table>
					</div>
				</div>
			</div>
		</div>
		<div class="ScreenButtonsDiv">					
			<input type="button" value="Close" id="btnCancel" name="btnCancel" class="Desktop_Btn" style="width:100px;">				
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
	
</xsl:stylesheet>