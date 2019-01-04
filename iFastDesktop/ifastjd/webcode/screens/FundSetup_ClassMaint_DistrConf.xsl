<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	
	<xsl:variable name="SCREEN_NAME">DistrConf</xsl:variable>
	
	<xsl:variable name="ADD_MODE">
		<xsl:choose>
			<xsl:when test="/websrvXML/CACHE_DATA/ClassData">
				<xsl:text>false</xsl:text>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>true</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">
				<xsl:call-template name="PageTitle_Tmpl">
					<xsl:with-param name="addMode" select="$ADD_MODE"/>
					<xsl:with-param name="screenName" select="$SCREEN_NAME"/>
				</xsl:call-template>
			</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >		
		<link href="{$vURL}css/FundSetup_ClassMaint_Common.css" rel="stylesheet" type="text/css" />		
		<link href="{$vURL}css/FundSetup_ClassMaint_{$SCREEN_NAME}.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/FundSetup_ClassMaint_Common.js"></script>
		<script language="javascript" src="{$vURL}javascript/FundSetup_ClassMaint_{$SCREEN_NAME}.js"></script>
		
		<script language="javascript">
			<xsl:call-template name="ClassMaint_CommonJS_Tmpl">
				<xsl:with-param name="isAddMode" select="$ADD_MODE"/>
			</xsl:call-template>					
		</script>		
	</xsl:template>
	
	
	<!-- ========================== PAGE RELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:if test="$ADD_MODE = 'false'">
			<xsl:call-template name="DataXML_Tmpl">
				<xsl:with-param name="id">ClassData</xsl:with-param>
				<xsl:with-param name="xml" select="/websrvXML/CACHE_DATA/ClassData"/>
			</xsl:call-template>			
		</xsl:if>
		
		<xsl:if test="/websrvXML/CACHE_DATA/UpdatedClassData">
			<xsl:call-template name="DataXML_Tmpl">
				<xsl:with-param name="id">UpdatedClassData</xsl:with-param>
				<xsl:with-param name="xml" select="/websrvXML/CACHE_DATA/UpdatedClassData"/>
			</xsl:call-template>
		</xsl:if>		
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >
		<xsl:call-template name="BreadCrumb_Tmpl">
			<xsl:with-param name="isAddMode" select="$ADD_MODE"/>
			<xsl:with-param name="activeScreenName" select="$SCREEN_NAME"/>
		</xsl:call-template>
		
		<xsl:call-template name="CommonEditScreenFields_Tmpl">
			<xsl:with-param name="isAddMode" select="$ADD_MODE"/>
		</xsl:call-template>
		
		<div class="ScreenContentsDiv" style="padding-top:20px">			
						
			<input id="DistributionConfig/id" type="hidden" xpath="DistributionConfig/id">
			</input>
			<input id="DistributionConfig/idDesc" type="hidden" xpath="DistributionConfig/idDesc">
			</input>
			<input id="DistributionConfig/idDefInvestOpt" type="hidden" xpath="DistributionConfig/idDefInvestOpt">
			</input>
			<input id="DistributionConfig/idDefInvestDesc" type="hidden" xpath="DistributionConfig/idDefInvestDesc">
			</input>
			<input id="DistributionConfig/idOverrideOpt" type="hidden" xpath="DistributionConfig/idOverrideOpt">
			</input>
			<input id="DistributionConfig/idDistribId" type="hidden" xpath="DistributionConfig/idDistribId">
			</input>					
			<xsl:if test="$ADD_MODE = 'true' or /websrvXML/CACHE_DATA/ClassData/DistributionConfig/id = 'yes'">
				<div class="EntryScreenSectionDiv">				
					<div class="FieldSetDiv" style="height:110px;">
						<div class="FieldSetLabelDiv Desktop_Background" style="width:125px;">
							Income Distribution
						</div>
							
						<div class="FieldSetContentsDiv" style="padding-top:10px;">							
							
							<xsl:if test="$ADD_MODE = 'true'">
								<div class="FieldRowDiv">
									<span class="fldLabelSpan_med">Applicable</span>
									<span class="fldValueCheckbox">									
										<input type="checkbox" id="idApplicableFld" value="yes" onclick="clickHandler_idApplicableFld( this );">
										</input>
									</span>
								</div>
							</xsl:if>
																				
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med" style="font-style:italic">Default Investment:</span>
								
								<span class="fldLabelSpan_sml">Cash</span>
								<span class="fldValueCheckbox">
									<input type="radio" name="idDefInvestOpt" id="cs_idDefInvestOptFld" value="CS" desc="Cash" onclick="clickHandler_idDefaultInvestRadio( this )">
									</input>
								</span>
								
								<span class="fldLabelSpan_med">ReInvestment</span>
								<span class="fldValueCheckbox">
									<input type="radio" name="idDefInvestOpt" id="ri_idDefInvestOptFld" value="RI" desc="Reinvestment" onclick="clickHandler_idDefaultInvestRadio( this )">
									</input>
								</span>
							</div>
							
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med" style="font-style:italic">Override Options:</span>
								
								<span class="fldLabelSpan_sml">Cash</span>
								<span class="fldValueCheckbox">									
									<input type="checkbox" id="cs_idOverrideOptFld" value="CS" onclick="clickHandler_idOverrideCheckbox( this );">
									</input>
								</span>
								
								<span class="fldLabelSpan_med">ReDirect</span>
								<span class="fldValueCheckbox">
									<input type="checkbox" id="rd_idOverrideOptFld" value="RD" onclick="clickHandler_idOverrideCheckbox( this );">
									</input>
								</span>
								
								<span class="fldLabelSpan_med">ReInvestment</span>
								<span class="fldValueCheckbox">
									<input type="checkbox" id="ri_idOverrideOptFld" value="RI" onclick="clickHandler_idOverrideCheckbox( this );">
									</input>
								</span>															
							</div>					

						</div>
					</div>
				</div>
			</xsl:if>
			
			
			<input id="DistributionConfig/cd" type="hidden" xpath="DistributionConfig/cd">
			</input>
			<input id="DistributionConfig/cdDesc" type="hidden" xpath="DistributionConfig/cdDesc">
			</input>
			<input id="DistributionConfig/cdDefInvestOpt" type="hidden" xpath="DistributionConfig/cdDefInvestOpt">
			</input>
			<input id="DistributionConfig/cdDefInvestDesc" type="hidden" xpath="DistributionConfig/cdDefInvestDesc">
			</input>
			<input id="DistributionConfig/cdOverrideOpt" type="hidden" xpath="DistributionConfig/cdOverrideOpt">
			</input>
			<input id="DistributionConfig/cdDistribId" type="hidden" xpath="DistributionConfig/cdDistribId">
			</input>					
			<xsl:if test="$ADD_MODE = 'true' or /websrvXML/CACHE_DATA/ClassData/DistributionConfig/cd = 'yes'">
				<div class="EntryScreenSectionDiv">				
					<div class="FieldSetDiv" style="height:110px;">
						<div class="FieldSetLabelDiv Desktop_Background" style="width:90px;">
							Capital Gains
						</div>	
						<div class="FieldSetContentsDiv" style="padding-top:10px;">
							
							<xsl:if test="$ADD_MODE = 'true'">
								<div class="FieldRowDiv">
									<span class="fldLabelSpan_med">Applicable</span>
									<span class="fldValueCheckbox">									
										<input type="checkbox" id="cdApplicableFld" value="yes" onclick="clickHandler_cdApplicableFld( this );">
										</input>
									</span>
								</div>
							</xsl:if>
							
							
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med" style="font-style:italic">Default Investment:</span>
								
								<span class="fldLabelSpan_sml">Cash</span>
								<span class="fldValueCheckbox">
									<input type="radio" name="cdDefInvestOpt" id="cs_cdDefInvestOptFld" value="CS" desc="Cash" onclick="clickHandler_cdDefaultInvestRadio( this )">
									</input>
								</span>
								
								<span class="fldLabelSpan_med">ReInvestment</span>
								<span class="fldValueCheckbox">
									<input type="radio" name="cdDefInvestOpt" id="ri_cdDefInvestOptFld" value="RI" desc="Reinvestment" onclick="clickHandler_cdDefaultInvestRadio( this )">
									</input>
								</span>
							</div>
								
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med" style="font-style:italic">Override Options:</span>
								
								<span class="fldLabelSpan_sml">Cash</span>
								<span class="fldValueCheckbox">
									<input type="checkbox" id="cs_cdOverrideOptFld" value="CS" onclick="clickHandler_cdOverrideCheckbox( this );">
									</input>
								</span>
								
								<span class="fldLabelSpan_med">ReDirect</span>
								<span class="fldValueCheckbox">
									<input type="checkbox" id="rd_cdOverrideOptFld" value="RD" onclick="clickHandler_cdOverrideCheckbox( this );">
									</input>
								</span>
								
								<span class="fldLabelSpan_med">ReInvestment</span>
								<span class="fldValueCheckbox">
									<input type="checkbox" id="ri_cdOverrideOptFld" value="RI" onclick="clickHandler_cdOverrideCheckbox( this );">
									</input>
								</span>															
							</div>					
						</div>
					</div>
				</div>
			</xsl:if>
			
		</div>
		<xsl:call-template name="ScreenButtons_Tmpl">
			<xsl:with-param name="screenName" select="$SCREEN_NAME"/>
			<xsl:with-param name="isAddMode" select="$ADD_MODE"/>
		</xsl:call-template>
		
		<xsl:call-template name="ScreenForm_Tmpl"/>
	</xsl:template>
</xsl:stylesheet>