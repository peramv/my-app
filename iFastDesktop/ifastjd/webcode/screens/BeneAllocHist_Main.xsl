<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
		<xsl:with-param name="pageTitle">Beneficiary Allocation History</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/BeneAllocHist.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/BeneAllocHist.js"></script>
		
		<script>			
			<xsl:for-each select="/websrvXML/dtBenAllocHistReloadResponse/BeneficiaryAllocHistInfo/BeneficiaryAllocDetail">
				<xsl:variable name="detailRecNum" select="position() - 1"/>
				_beneAllocDetails[<xsl:value-of select="$detailRecNum"/>] = [];
				<xsl:for-each select="BeneficiaryAllocRec">
					_beneAllocDetails[<xsl:value-of select="$detailRecNum"/>][<xsl:value-of select="position() - 1"/>] = '<xsl:copy-of select="."/>'; 
				</xsl:for-each>  	
			</xsl:for-each>
			
		</script>			
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >		
		<div class="ScreenSectionDiv" style="height:170px; margin-top:7px;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="font-weight:bold">
					Beneficiary Allocation History
				</div>
				<div class="FieldSetContentsDiv">								
					<div id="BenAlloc_TableDiv" class="Desktop_TableDiv" style="height:150px; width:876px; position:absolute;">
						<table id="BenAlloc_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true">
							<thead>
								<tr>															
									<td>
										<xsl:attribute name="style">width:580</xsl:attribute>
										<xsl:attribute name="columnWidth">580</xsl:attribute>
										Beneficiaries
									</td>
									<td>
										<xsl:attribute name="style">width:95</xsl:attribute>
										<xsl:attribute name="columnWidth">95</xsl:attribute>
										Eff. Date
									</td>
									<td>
										<xsl:attribute name="style">width:95</xsl:attribute>
										<xsl:attribute name="columnWidth">95</xsl:attribute>
										Mod. Date
									</td>	
									<td>
										<xsl:attribute name="style">width:85</xsl:attribute>
										<xsl:attribute name="columnWidth">85</xsl:attribute>
										Mod. User
									</td>								
								</tr>
							</thead>
							<tbody>
								<xsl:for-each select="/websrvXML/dtBenAllocHistReloadResponse/BeneficiaryAllocHistInfo/BeneficiaryAllocDetail">
									<tr>
										<xsl:attribute name="details"><xsl:copy-of select="."/></xsl:attribute>										
										<td>
											<xsl:for-each select="BeneficiaryAllocRec">
												<xsl:if test="amt &gt; 0">
													<xsl:value-of select="beneName"/>
													<xsl:if test="position() != last()">; </xsl:if>
												</xsl:if>
											</xsl:for-each>
										</td>
										<td>
											<xsl:value-of select="BeneficiaryAllocRec/deff"/>
										</td>
										<td>
											<xsl:value-of select="BeneficiaryAllocRec/modDate"/>
										</td>
										<td>
											<xsl:value-of select="BeneficiaryAllocRec/moduser"/>
										</td>
									</tr>
								</xsl:for-each>
							</tbody>					
						</table>
					</div>
				</div>
			</div>
		</div>
					
		<div class="ScreenSectionDiv" style="height:110px;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="font-weight:bold">
					Allocation Details
				</div>
				<div class="FieldSetContentsDiv">											
					<div id="BenAllocDetails_TableDiv" class="Desktop_TableDiv" style="height:85px; width:876px; position:absolute;">
						<table id="BenAllocDetails_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
							<thead>
								<tr>															
									<td>
										<xsl:attribute name="style">width:300</xsl:attribute>
										<xsl:attribute name="columnWidth">300</xsl:attribute>
										Beneficiary Name
									</td>
									<td>
										<xsl:attribute name="style">width:95</xsl:attribute>
										<xsl:attribute name="columnWidth">95</xsl:attribute>
										Eff. Date
									</td>
									<td>
										<xsl:attribute name="style">width:100</xsl:attribute>
										<xsl:attribute name="columnWidth">100</xsl:attribute>
										Percent
									</td>
									<td>
										<xsl:attribute name="style">width:100</xsl:attribute>
										<xsl:attribute name="columnWidth">100</xsl:attribute>
										Amount
									</td>
									<td>
										<xsl:attribute name="style">width:80</xsl:attribute>
										<xsl:attribute name="columnWidth">80</xsl:attribute>
										Reported
									</td>																																				
									<td>
										<xsl:attribute name="style">width:95</xsl:attribute>
										<xsl:attribute name="columnWidth">95</xsl:attribute>
										Mod. Date
									</td>
									<td>
										<xsl:attribute name="style">width:85</xsl:attribute>
										<xsl:attribute name="columnWidth">85</xsl:attribute>
										Mod. User
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