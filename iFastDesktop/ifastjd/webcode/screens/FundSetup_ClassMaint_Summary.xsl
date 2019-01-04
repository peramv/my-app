<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_ClassListTemplate.xsl"/>
	
	<xsl:variable name="SCREEN_NAME" select="/websrvXML/FormInformation/screenToLoad"/>			
	
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
			<xsl:call-template name="ClassMaint_CommonJS_Tmpl"/>
			
			_fundCode = "<xsl:value-of select="/websrvXML/CACHE_DATA/ClassData/fundCode"/>";
			_classCode = "<xsl:value-of select="/websrvXML/CACHE_DATA/ClassData/classCode"/>";			
			
			var _detailsSectionMap = {};
			<xsl:for-each select="/websrvXML/ScreensConfig/DetailsScreenSequence/screenName">
				<xsl:variable name="screenName"><xsl:value-of select="."/></xsl:variable>			
				_detailsSectionMap["<xsl:value-of select="$screenName"/>"]= {};				 
			</xsl:for-each>
					
		</script>			
	</xsl:template>

	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">feeScalePopupDiv</xsl:with-param>
			<xsl:with-param name="caption">Fee Scale Details</xsl:with-param>
			<xsl:with-param name="width">450</xsl:with-param>
			<xsl:with-param name="height">160</xsl:with-param>
			<xsl:with-param name="top">325</xsl:with-param>
			<xsl:with-param name="left">230</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="FeeScalePopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>
		
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
		<xsl:variable name="origDataNode" select="/websrvXML/CACHE_DATA/ClassData"/>
		<xsl:variable name="updateDataNode" select="/websrvXML/CACHE_DATA/UpdatedClassData"/>
	
		<div id="FundDescDiv">
			<div class="FundDescItemDiv">
				<span class="FundDescItemLabel">Fund: </span>					
				<span class="FundDescItemValue">
					<xsl:choose>
						<xsl:when test="$ADD_MODE = 'true'">
							<xsl:value-of select="$updateDataNode/fundName"/>		
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="$origDataNode/fundCode"/> - <xsl:value-of select="$origDataNode/fundName"/>
						</xsl:otherwise>
					</xsl:choose>
				</span>
					
			</div>
			<div class="FundDescItemDiv">
				<span class="FundDescItemLabel">Fund Sponsor:</span>
				<span class="FundDescItemValue"><xsl:value-of select="$origDataNode/sponsor"/></span>
			</div>
		</div>
		
		<div id="ExpandCollapseAllDiv">
			<img id="AllDetailsExpand_Btn" class="SectionBtn" src="{$vURL}images/folded_btn.gif" onclick="clickHandler_expandAllBtn();" title="Expand all sections"/>
			<span style="padding:2px;">/</span>
			<img id="AllDetailsCollapse_Btn" class="SectionBtn" src="{$vURL}images/unfolded_btn.gif" onclick="clickHandler_collapseAllBtn();" title="Collapse all sections"/>
			<span style="padding-left: 3px;">All Sections</span>
		</div>
		
		<div id="ClassDetailsDiv">
												
			<xsl:for-each select="/websrvXML/ScreensConfig/DetailsScreenSequence/screenName">
				<xsl:apply-templates select=".">
					<xsl:with-param name="origDataNode" select="$origDataNode"/>
					<xsl:with-param name="updateDataNode" select="$updateDataNode" />
				</xsl:apply-templates>					
			</xsl:for-each>
					
		</div>				

		
		<div id="actionButtonsDiv">		
			<input type="button" id="submitBtn" class="Desktop_Btn" onclick="clickHandler_submitBtn()" disabled="true" value="Submit">				
			</input>											
			<input type="button" id="cancelBtn" value="Cancel" class="Desktop_Btn" onclick="clickHandler_cancelBtn()"/>					
		</div>
		
		<xsl:call-template name="ScreenForm_Tmpl"/>
			
	</xsl:template>
	

	<!-- ========================== SECTION TEMPLATE =============================-->
	<xsl:template name="SectionHeader_Tmpl">
		<xsl:param name="sectionName"/>				
		
		<xsl:variable name="sectionLabel" select="/websrvXML/ScreensConfig/ScreenDefList/ScreenDef[screenName = $sectionName]/screenLabel"/>			
				
		<div id="{$sectionName}DetailsHeaderDiv"  class="ClassDetailsSectionHeaderDiv">
			<img id="{$sectionName}DetailsExpandBtn" class="SectionBtn" src="{$vURL}images/folded_btn.gif">
				<xsl:attribute name="onclick">clickHandler_expandSectionBtn( "<xsl:value-of select="$sectionName"/>" );</xsl:attribute>
				<xsl:attribute name="title">Expand <xsl:value-of select="$sectionLabel"/></xsl:attribute>
			</img>
			<img id="{$sectionName}DetailsCollapseBtn" class="SectionBtn" src="{$vURL}images/unfolded_btn.gif" style="display:none;">
				<xsl:attribute name="onclick">clickHandler_collapseSectionBtn( "<xsl:value-of select="$sectionName"/>" );</xsl:attribute>
				<xsl:attribute name="title">Collapse <xsl:value-of select="$sectionLabel"/> section</xsl:attribute>
			</img>
			<span class="ClassDetailsSectionHeaderLabel">
			 	<xsl:attribute name="onclick">clickHandler_sectionLabel( "<xsl:value-of select="$sectionName"/>" );</xsl:attribute>			
				<xsl:value-of select="$sectionLabel"/>
			</span>
			<input type="button" value="Edit" class="editBtn">
				<xsl:attribute name="onclick">clickHandler_editBtn( "<xsl:value-of select="$sectionName"/>" );</xsl:attribute>
			</input>
		</div>						

	</xsl:template>
	
		
	<!-- ========================== SUB-HEADER ROW TEMPLATE =============================-->
	<xsl:template name="SubHeaderRow_Tmpl">
		<xsl:param name="label"/>
		
		<tr>
			<td class="ClassDetailsSubHeader_Td">
				<xsl:if test="string-length( $label ) != 0">
					<xsl:value-of select="$label"/>
				</xsl:if>
				<xsl:if test="string-length( $label ) = 0">
					<xsl:text>&#xa0;</xsl:text>
				</xsl:if>
			</td>
			<td class="ClassDetailsFieldValue_Td"><xsl:text>&#xa0;</xsl:text></td>
			<td class="ClassDetailsFieldName_Td"><xsl:text>&#xa0;</xsl:text></td>
			<td class="ClassDetailsFieldValue_Td"><xsl:text>&#xa0;</xsl:text></td>
		</tr>
	</xsl:template>
	
	
	<!-- ========================== DETAILS ROW TEMPLATE =============================-->
	<xsl:template name="DetailsRow_Tmpl">
		<xsl:param name="columnOneHTML"/>		
		<xsl:param name="columnTwoHTML"/>
		
		<tr>
			<xsl:copy-of select="$columnOneHTML"/>
			<xsl:copy-of select="$columnTwoHTML"/>
		</tr>
	</xsl:template>
	
	
	<!-- ========================== FIELD TEMPLATE =============================-->
	<xsl:template name="Field_tmpl">
		<xsl:param name="fldXPath"/>
		<xsl:param name="fldLbl"/>
		<xsl:param name="fldVal"/>
		<xsl:param name="fldValDesc"/>
		<xsl:param name="indent">no</xsl:param>
		<xsl:param name="status"/>
		
		
		<td title="{$fldLbl}">
			<xsl:attribute name="class">ClassDetailsFieldName_Td <xsl:if test="$indent='yes'">indent</xsl:if></xsl:attribute>
			<xsl:call-template name="Text_Tmpl">
				<xsl:with-param name="text" select="$fldLbl"/>
			</xsl:call-template>
		</td>
		<td title="{$fldValDesc}" xpath="{$fldXPath}" value="{$fldVal}">			
			<xsl:attribute name="class">ClassDetailsFieldValue_Td <xsl:if test="$ADD_MODE = 'false' and $status = 'mod'">modHighlight</xsl:if></xsl:attribute>
							
			<xsl:call-template name="Text_Tmpl">
				<xsl:with-param name="text" select="$fldValDesc"/>
			</xsl:call-template>
		</td>
	</xsl:template>
	
	
	<!-- ========================== RECORD TEMPLATE =============================-->
	<xsl:template name="Record_tmpl">
		<xsl:param name="recordXPath"/>
		<xsl:param name="recordNode"/>
		<xsl:param name="recordLbl"/>
		<xsl:param name="recordValDesc"/>
		<xsl:param name="status"/>
		<xsl:param name="inclDetailsBtn">no</xsl:param>
		
		<td title="{$recordLbl}">
			<xsl:attribute name="class">ClassDetailsFieldName_Td indent</xsl:attribute>
			<xsl:call-template name="Text_Tmpl">
				<xsl:with-param name="text" select="$recordLbl"/>
			</xsl:call-template>
		</td>
		<td title="{$recordValDesc}" xpath="{$recordXPath}">
			<xsl:attribute name="class">
				ClassDetailsFieldValue_Td
				<xsl:if test="$ADD_MODE = 'false' and $status = 'mod'">modHighlight</xsl:if> 
				<xsl:if test="$ADD_MODE = 'false' and $status = 'add'">addHighlight</xsl:if>
				<xsl:if test="$ADD_MODE = 'false' and $status = 'del'">delHighlight</xsl:if>				
			</xsl:attribute>
			<xsl:attribute name="data">
				<xsl:for-each select="$recordNode/*">
					<xsl:value-of select="name()"/>=<xsl:value-of select="."/><xsl:if test="position() != last()">;</xsl:if>					
				</xsl:for-each>
			</xsl:attribute>
			<xsl:call-template name="Text_Tmpl">
				<xsl:with-param name="text" select="$recordValDesc"/>
			</xsl:call-template>							
			<xsl:if test="$inclDetailsBtn = 'yes'">
				<span style="text-decoration:underline; cursor:pointer; padding-left:10px;" onclick="clickHandler_detailsLink( this.parentNode )">Full details</span>
			</xsl:if>								
		</td>
	</xsl:template>
	
	
	<!-- ========================== CONTENT TABLE HEADER TEMPLATE =============================-->
	<xsl:template name="ContentTableHeader_Tmpl">
		<thead style="visibility:hidden; height:0px; overflow:hidden;">
			<tr style="visibility:hidden; height:0px; overflow:hidden;">						
				<td style="width:220; visibility:hidden; height:0px; overflow:hidden;" columnWidth="220">
					<xsl:text>&#xa0;</xsl:text>
				</td>
				<td style="width:228; visibility:hidden; height:0px; overflow:hidden;" columnWidth="228">
					<xsl:text>&#xa0;</xsl:text>
				</td>
				<td style="width:220; visibility:hidden; height:0px; overflow:hidden;" columnWidth="220">
					<xsl:text>&#xa0;</xsl:text>
				</td>
				<td style="width:228; visibility:hidden; height:0px; overflow:hidden;" columnWidth="228">
					<xsl:text>&#xa0;</xsl:text>
				</td>						
			</tr>
		</thead>
	</xsl:template>
	
		
	<!-- ========================== BASIC INFO SECTION TEMPLATE =============================-->
	<xsl:template match="screenName[text() = 'BasicInfo']">
		<xsl:param name="origDataNode"/>
		<xsl:param name="updateDataNode"/>
		
		<xsl:choose>
			<xsl:when  test="$updateDataNode/ClassBasic">
				<xsl:call-template name="BasicInfoContent_tmpl">
					<xsl:with-param name="dataNode" select="$updateDataNode/ClassBasic"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="BasicInfoContent_tmpl">
					<xsl:with-param name="dataNode" select="$origDataNode/ClassBasic"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
				
	</xsl:template>


	<!-- ========================== BASIC INFO CONTENT TEMPLATE =============================-->
	<xsl:template name="BasicInfoContent_tmpl">
		<xsl:param name="dataNode"/>
		
		<xsl:variable name="sectionName">BasicInfo</xsl:variable>
					
		<div id="{$sectionName}SectionDiv" sectionXpath="ClassBasic">
			<xsl:call-template name="SectionHeader_Tmpl">
				<xsl:with-param name="sectionName" select="$sectionName"/>
			</xsl:call-template>
			<div id="{$sectionName}DetailsContentDiv" class="ClassDetailsSectionDiv">
				<table id="{$sectionName}Details_Table" ifdsTable="true" style="left:0; top:0; position:absolute;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" >
					<xsl:call-template name="ContentTableHeader_Tmpl"/>
					<tbody>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/classE</xsl:with-param>
									<xsl:with-param name="fldLbl">English Description</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/classE"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/classE"/>
									<xsl:with-param name="status" select="$dataNode/classE/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/classF</xsl:with-param>
									<xsl:with-param name="fldLbl">French Description</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/classF"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/classF"/>
									<xsl:with-param name="status" select="$dataNode/classF/@status"/>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/stat</xsl:with-param>
									<xsl:with-param name="fldLbl">Status</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/stat"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/stat"/>
									<xsl:with-param name="status" select="$dataNode/stat/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/statDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Status Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/statDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/statDate"/>
									<xsl:with-param name="status" select="$dataNode/statDate/@status"/>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/deff</xsl:with-param>
									<xsl:with-param name="fldLbl">Effective Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/deff"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/deff"/>
									<xsl:with-param name="status" select="$dataNode/deff/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/stopDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/stopDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/stopDate"/>
									<xsl:with-param name="status" select="$dataNode/stopDate/@status"/>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/loadType</xsl:with-param>
									<xsl:with-param name="fldLbl">Load Type</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/loadType"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/loadType"/>
									<xsl:with-param name="status" select="$dataNode/loadType/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/company</xsl:with-param>
									<xsl:with-param name="fldLbl">ESG Company Code</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/company"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/company"/>
									<xsl:with-param name="status" select="$dataNode/company/@status"/>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/bareTrustee</xsl:with-param>
									<xsl:with-param name="fldLbl">Bare Trustee</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/bareTrustee"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/bareTrusteeDesc"/>
									<xsl:with-param name="status" select="$dataNode/bareTrustee/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/riskRating</xsl:with-param>
									<xsl:with-param name="fldLbl">Risk Rating</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/riskRating"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/riskRatingDesc"/>
									<xsl:with-param name="status" select="$dataNode/riskRating/@status"/>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">ClassBasic/FundCurHldyOpt</xsl:with-param>
									<xsl:with-param name="fldLbl">Fund/Fund Class Curr Holiday</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/FundCurHldyOpt"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/FundCurHldyOptDesc"/>
									<xsl:with-param name="status" select="$dataNode/FundCurHldyOpt/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath" />
									<xsl:with-param name="fldLbl" />
									<xsl:with-param name="fldVal" />
									<xsl:with-param name="fldValDesc" />
									<xsl:with-param name="status" />
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						
							<xsl:call-template name="SubHeaderRow_Tmpl">
								<xsl:with-param name="label">Inventory Tracking</xsl:with-param>
							</xsl:call-template>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">ClassBasic/InventoryTracking/applicable</xsl:with-param>
										<xsl:with-param name="fldLbl">Applicable</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/InventoryTracking/applicable"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/InventoryTracking/applicable"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/InventoryTracking/applicable/@status"/>
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">ClassBasic/InventoryTracking/basedOn</xsl:with-param>
										<xsl:with-param name="fldLbl">Based On</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/InventoryTracking/basedOn"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/InventoryTracking/basedOnDesc"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/InventoryTracking/basedOn/@status"/>
									</xsl:call-template>
								</xsl:with-param>
							</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Fund Sub Categories</xsl:with-param>
						</xsl:call-template>
						<xsl:for-each select="$dataNode/FundSubCategories/FundSubCat">
							<xsl:if test="position() mod 2 = 1">
									<xsl:call-template name="DetailsRow_Tmpl">
										<xsl:with-param name="columnOneHTML">
											<xsl:call-template name="Record_tmpl">
												<xsl:with-param name="recordNode" select="."/>
												<xsl:with-param name="recordXPath">ClassBasic/FundSubCategories/FundSubCat</xsl:with-param>
												<xsl:with-param name="recordLbl" select="subCatDesc"/>
												<xsl:with-param name="recordValDesc" select="subCatFlag"/>
												<xsl:with-param name="status" select="@status"/>
											</xsl:call-template>
										</xsl:with-param>
										<xsl:with-param name="columnTwoHTML">
											<xsl:choose>
												<xsl:when test="position() != last()">
													<xsl:call-template name="Record_tmpl">
														<xsl:with-param name="recordNode" select="following-sibling::FundSubCat[1]"/>
														<xsl:with-param name="recordXPath">ClassBasic/FundSubCategories/FundSubCat</xsl:with-param>
														<xsl:with-param name="recordLbl" select="following-sibling::FundSubCat[1]/subCatDesc"/>
														<xsl:with-param name="recordValDesc" select="following-sibling::FundSubCat[1]/subCatFlag"/>
														<xsl:with-param name="status" select="following-sibling::FundSubCat[1]/@status"/>
													</xsl:call-template>
												</xsl:when>
												<xsl:otherwise>
													<xsl:call-template name="Field_tmpl"/>
												</xsl:otherwise>
											</xsl:choose>
										</xsl:with-param>
									</xsl:call-template>
							</xsl:if>
						</xsl:for-each>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Fund Identifiers</xsl:with-param>
						</xsl:call-template>
						<xsl:for-each select="$dataNode/FundIdentifiers/FundIdentifier">
							<xsl:if test="position() mod 2 = 1">
								<xsl:call-template name="DetailsRow_Tmpl">
									<xsl:with-param name="columnOneHTML">
										<xsl:call-template name="Record_tmpl">
											<xsl:with-param name="recordNode" select="."/>
											<xsl:with-param name="recordXPath">ClassBasic/FundIdentifiers/FundIdentifier</xsl:with-param>
											<xsl:with-param name="recordLbl" select="idTypeDesc"/>
											<xsl:with-param name="recordValDesc" select="idValue"/>
											<xsl:with-param name="status" select="@status"/>
										</xsl:call-template>
									</xsl:with-param>									
									<xsl:with-param name="columnTwoHTML">
										<xsl:choose>
											<xsl:when test="position() != last()">
												<xsl:call-template name="Record_tmpl">
													<xsl:with-param name="recordNode" select="following-sibling::FundIdentifier[1]"/>
													<xsl:with-param name="recordXPath">ClassBasic/FundIdentifiers/FundIdentifier</xsl:with-param>
													<xsl:with-param name="recordLbl" select="following-sibling::FundIdentifier[1]/idTypeDesc"/>
													<xsl:with-param name="recordValDesc" select="following-sibling::FundIdentifier[1]/idValue"/>
													<xsl:with-param name="status" select="following-sibling::FundIdentifier[1]/@status"/>
												</xsl:call-template>
											</xsl:when>
											<xsl:otherwise>
												<xsl:call-template name="Field_tmpl"/>
											</xsl:otherwise>
										</xsl:choose>
									</xsl:with-param>																			
								</xsl:call-template>
							</xsl:if>																						
						</xsl:for-each>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Share Groups</xsl:with-param>
						</xsl:call-template>
						<xsl:for-each select="$dataNode/ShareGroups/ShareGroup">
							<xsl:if test="position() mod 2 = 1">
								<xsl:call-template name="DetailsRow_Tmpl">
									<xsl:with-param name="columnOneHTML">
										<xsl:call-template name="Record_tmpl">
											<xsl:with-param name="recordNode" select="."/>
											<xsl:with-param name="recordXPath">ClassBasic/ShareGroups/ShareGroup</xsl:with-param>
											<xsl:with-param name="recordLbl" select="groupName"/>
											<xsl:with-param name="recordValDesc"><xsl:value-of select="deff"/> (active: <xsl:value-of select="active"/>)</xsl:with-param>
											<xsl:with-param name="status" select="@status"/>
										</xsl:call-template>
									</xsl:with-param>									
									<xsl:with-param name="columnTwoHTML">
										<xsl:choose>
											<xsl:when test="position() != last()">
												<xsl:call-template name="Record_tmpl">
													<xsl:with-param name="recordNode" select="following-sibling::ShareGroup[1]"/>
													<xsl:with-param name="recordXPath">ClassBasic/ShareGroups/ShareGroup</xsl:with-param>
													<xsl:with-param name="recordLbl" select="following-sibling::ShareGroup[1]/groupName"/>
													<xsl:with-param name="recordValDesc"><xsl:value-of select="following-sibling::ShareGroup[1]/deff"/> (active: <xsl:value-of select="following-sibling::ShareGroup[1]/active"/>)</xsl:with-param>
													<xsl:with-param name="status" select="following-sibling::ShareGroup[1]/@status"/>													
												</xsl:call-template>
											</xsl:when>
											<xsl:otherwise>
												<xsl:call-template name="Field_tmpl"/>
											</xsl:otherwise>
										</xsl:choose>
									</xsl:with-param>																			
								</xsl:call-template>
							</xsl:if>																						
						</xsl:for-each>
						
					</tbody>
				</table>
			</div>			
		</div>		
	</xsl:template>
	
	<!-- ========================== PRICE INFO SECTION TEMPLATE ============================= -->
	<xsl:template match="screenName[text() = 'PriceInfo']">		
		<xsl:param name="origDataNode"/>
		<xsl:param name="updateDataNode"/>
		
		<xsl:choose>
			<xsl:when  test="$updateDataNode/PriceInfo">
				<xsl:call-template name="PriceInfoContent_tmpl">
					<xsl:with-param name="dataNode" select="$updateDataNode/PriceInfo"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="PriceInfoContent_tmpl">
					<xsl:with-param name="dataNode" select="$origDataNode/PriceInfo"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	
	<!-- ========================== PRICE INFO CONTENT TEMPLATE ============================= -->
	<xsl:template name="PriceInfoContent_tmpl">
		<xsl:param name="dataNode"/>
		
		<xsl:variable name="sectionName">PriceInfo</xsl:variable>
		
		<div id="{$sectionName}SectionDiv">
			<xsl:call-template name="SectionHeader_Tmpl">
				<xsl:with-param name="sectionName" select="$sectionName"/>
			</xsl:call-template>
			<div id="{$sectionName}DetailsContentDiv" class="ClassDetailsSectionDiv">								
				<table id="{$sectionName}Details_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="false">
					<xsl:call-template name="ContentTableHeader_Tmpl"/>
					<tbody>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/currency</xsl:with-param>
									<xsl:with-param name="fldLbl">NAV Currency</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/currency"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/currDesc"/>		
									<xsl:with-param name="status" select="$dataNode/currency/@status"/>					
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/validSettleCurr</xsl:with-param>
									<xsl:with-param name="fldLbl">Valid Settle Curr.</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/validSettleCurr"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/validSettleCurr"/>		
									<xsl:with-param name="status" select="$dataNode/validSettleCurr/@status"/>							
								</xsl:call-template>
							</xsl:with-param>																			
						</xsl:call-template>						
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/schedTransType</xsl:with-param>
									<xsl:with-param name="fldLbl">Custom Valuation</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/schedTransType"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/schedTransType"/>
									<xsl:with-param name="status" select="$dataNode/schedTransType/@status"/>			
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/esgPriceSuppress</xsl:with-param>
									<xsl:with-param name="fldLbl">ESG Price Suppress</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/esgPriceSuppress"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/esgPriceSuppress"/>		
									<xsl:with-param name="status" select="$dataNode/esgPriceSuppress/@status"/>							
								</xsl:call-template>
							</xsl:with-param>																			
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">NAV</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/fixPrice</xsl:with-param>
									<xsl:with-param name="fldLbl">Fixed Price</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/fixPrice"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/fixPrice"/>			
									<xsl:with-param name="status" select="$dataNode/fixPrice/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/fixRate</xsl:with-param>
									<xsl:with-param name="fldLbl">Fixed Rate</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/fixRate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/fixRate"/>			
									<xsl:with-param name="status" select="$dataNode/fixRate/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>						
								</xsl:call-template>
							</xsl:with-param>																			
						</xsl:call-template>											
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/ratePrecision</xsl:with-param>
									<xsl:with-param name="fldLbl">Rate Precision</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ratePrecision"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ratePrecision"/>		
									<xsl:with-param name="status" select="$dataNode/ratePrecision/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/priceVarAmt</xsl:with-param>
									<xsl:with-param name="fldLbl">Price Var Amount</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/priceVarAmt"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/priceVarAmt"/>			
									<xsl:with-param name="status" select="$dataNode/priceVarAmt/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>					
								</xsl:call-template>
							</xsl:with-param>																			
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/priceVarType</xsl:with-param>
									<xsl:with-param name="fldLbl">Price Var Type</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/priceVarType"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/priceVarTypeDesc"/>
									<xsl:with-param name="status" select="$dataNode/priceVarType/@status"/>		
									<xsl:with-param name="indent">yes</xsl:with-param>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/loadGrp</xsl:with-param>
									<xsl:with-param name="fldLbl">Load Group</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/loadGrp"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/loadGrp"/>		
									<xsl:with-param name="status" select="$dataNode/loadGrp/@status"/>		
									<xsl:with-param name="indent">yes</xsl:with-param>					
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Unit</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">								
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/unitsCalc</xsl:with-param>
									<xsl:with-param name="fldLbl">Calculation Method</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/unitsCalc"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/unitsCalc"/>	
									<xsl:with-param name="status" select="$dataNode/unitsCalc/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>							
								</xsl:call-template>
							</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
								<xsl:with-param name="fldXPath">PriceInfo/unitsPrecision</xsl:with-param>
								<xsl:with-param name="fldLbl">Units Precision</xsl:with-param>
								<xsl:with-param name="fldVal" select="$dataNode/unitsPrecision"/>
								<xsl:with-param name="fldValDesc" select="$dataNode/unitsPrecision"/>		
								<xsl:with-param name="status" select="$dataNode/unitsPrecision/@status"/>	
								<xsl:with-param name="indent">yes</xsl:with-param>						
								</xsl:call-template>
								</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">						
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/fractionalShr</xsl:with-param>
									<xsl:with-param name="fldLbl">Fractional Share</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/fractionalShr"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/fractionalShr"/>		
									<xsl:with-param name="status" select="$dataNode/fractionalShr/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>						
								</xsl:call-template>
							</xsl:with-param>						
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">PriceInfo/allocType</xsl:with-param>
									<xsl:with-param name="fldLbl">Alloc. Type</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/allocType"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/allocTypeDesc"/>			
									<xsl:with-param name="status" select="$dataNode/allocType/@status"/>		
									<xsl:with-param name="indent">yes</xsl:with-param>				
								</xsl:call-template>
							</xsl:with-param>							
						</xsl:call-template>																																												
					</tbody>
					
				</table>
			</div>
		</div>
	</xsl:template>

	
	 <!-- ========================== DISTRIBUTION CONFIGURATION SECTION TEMPLATE ============================= -->
	<xsl:template match="screenName[text() = 'DistrConf']">		
		<xsl:param name="origDataNode"/>
		<xsl:param name="updateDataNode"/>
		
		<xsl:choose>
			<xsl:when  test="$updateDataNode/DistributionConfig">
				<xsl:call-template name="DistrConfContent_tmpl">
					<xsl:with-param name="dataNode" select="$updateDataNode/DistributionConfig"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="DistrConfContent_tmpl">
					<xsl:with-param name="dataNode" select="$origDataNode/DistributionConfig"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	
	<!-- ========================== DISTRIBUTION CONFIGURATION CONTENT TEMPLATE =============================-->
	<xsl:template name="DistrConfContent_tmpl">
		<xsl:param name="dataNode"/>
		
		<xsl:variable name="sectionName">DistrConf</xsl:variable>
		
		<div id="{$sectionName}SectionDiv">
			<xsl:call-template name="SectionHeader_Tmpl">
				<xsl:with-param name="sectionName" select="$sectionName"/>
			</xsl:call-template>
			<div id="{$sectionName}DetailsContentDiv" class="ClassDetailsSectionDiv">								
				<table id="{$sectionName}Details_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="false">
					<xsl:call-template name="ContentTableHeader_Tmpl"/>
					<tbody>
						<xsl:if test="$dataNode/id = 'yes'">
							<xsl:call-template name="SubHeaderRow_Tmpl">
								<xsl:with-param name="label"><xsl:value-of select="$dataNode/idDesc"/></xsl:with-param>
							</xsl:call-template>
							<tr style="display:none">
								<td colspan="2">
									<xsl:attribute name="xpath">DistributionConfig/id</xsl:attribute>
									<xsl:attribute name="value"><xsl:value-of select="$dataNode/id"/></xsl:attribute>									
								</td>							
								<td colspan="2">
									<xsl:attribute name="xpath">DistributionConfig/idDistribId</xsl:attribute>
									<xsl:attribute name="value"><xsl:value-of select="$dataNode/idDistribId"/></xsl:attribute>									
								</td>
							</tr>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">DistributionConfig/idDefInvestOpt</xsl:with-param>
										<xsl:with-param name="fldLbl">Default Investment</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/idDefInvestOpt"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/idDefInvestDesc"/>		
										<xsl:with-param name="status" select="$dataNode/idDefInvestOpt/@status"/>
										<xsl:with-param name="indent">yes</xsl:with-param>							
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">DistributionConfig/idOverrideOpt</xsl:with-param>
										<xsl:with-param name="fldLbl">Override Option</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/idOverrideOpt"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/idOverrideOpt"/>
										<xsl:with-param name="status" select="$dataNode/idOverrideOpt/@status"/>	
										<xsl:with-param name="indent">yes</xsl:with-param>		
									</xsl:call-template>
								</xsl:with-param>
							</xsl:call-template>	
						</xsl:if>
						<xsl:if test="$dataNode/cd = 'yes'">
							<xsl:call-template name="SubHeaderRow_Tmpl">
								<xsl:with-param name="label"><xsl:value-of select="$dataNode/cdDesc"/></xsl:with-param>
							</xsl:call-template>
							<tr style="display:none">
								<td colspan="2">
									<xsl:attribute name="xpath">DistributionConfig/cd</xsl:attribute>
									<xsl:attribute name="value"><xsl:value-of select="$dataNode/cd"/></xsl:attribute>									
								</td>							
								<td colspan="2">
									<xsl:attribute name="xpath">DistributionConfig/cdDistribId</xsl:attribute>
									<xsl:attribute name="value"><xsl:value-of select="$dataNode/cdDistribId"/></xsl:attribute>									
								</td>
							</tr>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">DistributionConfig/cdDefInvestOpt</xsl:with-param>
										<xsl:with-param name="fldLbl">Default Investment</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/cdDefInvestOpt"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/cdDefInvestDesc"/>		
										<xsl:with-param name="status" select="$dataNode/cdDefInvestOpt/@status"/>
										<xsl:with-param name="indent">yes</xsl:with-param>							
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">DistributionConfig/cdOverrideOpt</xsl:with-param>
										<xsl:with-param name="fldLbl">Override Option</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/cdOverrideOpt"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/cdOverrideOpt"/>
										<xsl:with-param name="status" select="$dataNode/cdOverrideOpt/@status"/>
										<xsl:with-param name="indent">yes</xsl:with-param>			
									</xsl:call-template>
								</xsl:with-param>
							</xsl:call-template>	
						</xsl:if>
						<xsl:if test="$dataNode/id = 'no' and $dataNode/cd = 'no'">
							<xsl:call-template name="SubHeaderRow_Tmpl">
								<xsl:with-param name="label"></xsl:with-param>
							</xsl:call-template>
						</xsl:if>				
					</tbody>
				</table>
			</div>
		</div>			
								
		
	</xsl:template>
	
	
	<!-- ========================== FEE CONFIGURATION SECTION TEMPLATE ============================= -->
	<xsl:template match="screenName[text() = 'FeeConf']">		
		<xsl:param name="origDataNode"/>
		<xsl:param name="updateDataNode"/>
		
		<xsl:choose>
			<xsl:when  test="$updateDataNode/FeeConfiguration">
				<xsl:call-template name="FeeConfContent_tmpl">
					<xsl:with-param name="dataNode" select="$updateDataNode/FeeConfiguration"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="FeeConfContent_tmpl">
					<xsl:with-param name="dataNode" select="$origDataNode/FeeConfiguration"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	
	<!-- ========================== FEE SCALE POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="FeeScalePopupContents_tmpl">
		<div style="padding:10px;">
			<div class="DetailsPopupHeader">
				<span id="popup_feeCodeDescFld" style="padding-right:4px;"></span>(Fee code: <span id="popup_feeCodeFld"></span>)
			</div>		
			<table cellpadding="0" cellspacing="0">
				<tr>					
					<td class="DetailsPopupFldLbl">Level:</td>
					<td id="popup_levelFld" class="DetailsPopupFldVal"></td>
					<td class="DetailsPopupFldLbl">Rate:</td>
					<td id="popup_rateFld" class="DetailsPopupFldVal"></td>					
				</tr>
				<tr>
					<td class="DetailsPopupFldLbl">Lower:</td>
					<td id="popup_lowerFld" class="DetailsPopupFldVal"></td>
					<td class="DetailsPopupFldLbl">Upper:</td>
					<td id="popup_upperFld" class="DetailsPopupFldVal"></td>
				</tr>				
				<tr>					
					<td class="DetailsPopupFldLbl">Effective Date:</td>
					<td id="popup_deffFld" class="DetailsPopupFldVal"></td>
				</tr>
				<tr style="display:none">					
					<td class="DetailsPopupFldLbl">Effective Date:</td>
					<td id="popup_scaleUUIDFld" class="DetailsPopupFldVal"></td>
				</tr>
			</table>
			<div style="padding-top:10px; text-align:center">
				<input type="button" id="popup_closeBtn" value="Close" class="Desktop_Btn" onclick="clickHandler_popupCloseBtn()"/>
			</div>
		</div>		
	</xsl:template>
	
	
	<!-- ========================== FEE CONFIGURATION CONTENT TEMPLATE ============================= -->
	<xsl:template name="FeeConfContent_tmpl">
		<xsl:param name="dataNode"/>
		
		<xsl:variable name="sectionName">FeeConf</xsl:variable>
		
		<div id="{$sectionName}SectionDiv">
			<xsl:call-template name="SectionHeader_Tmpl">
				<xsl:with-param name="sectionName" select="$sectionName"/>
			</xsl:call-template>
			<div id="{$sectionName}DetailsContentDiv" class="ClassDetailsSectionDiv">								
				<table id="{$sectionName}Details_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="false">
					<xsl:call-template name="ContentTableHeader_Tmpl"/>
					<tbody>	
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Trailer Fee</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/trlFeeDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Trailer Fee Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/trlFeeDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/trlFeeDate"/>		
									<xsl:with-param name="status" select="$dataNode/trlFeeDate/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>
								</xsl:call-template>								
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/trlFeeGrandFathDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Trailer Fee Grandfather Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/trlFeeGrandFathDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/trlFeeGrandFathDate"/>
									<xsl:with-param name="status" select="$dataNode/trlFeeGrandFathDate/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>									
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Maturity Days</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/earlyMatDays</xsl:with-param>
									<xsl:with-param name="fldLbl">Early Maturity Days</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/earlyMatDays"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/earlyMatDays"/>		
									<xsl:with-param name="status" select="$dataNode/earlyMatDays/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>	
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/sttrMatDays</xsl:with-param>
									<xsl:with-param name="fldLbl">Short-Term Trading Maturity Days</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/sttrMatDays"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/sttrMatDays"/>		
									<xsl:with-param name="status" select="$dataNode/sttrMatDays/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>					
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Transfer Fee</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/tfrFee</xsl:with-param>
									<xsl:with-param name="fldLbl">Transfer Fee Applicable</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/tfrFee"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/tfrFee"/>
									<xsl:with-param name="status" select="$dataNode/tfrFee/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/tfrFeeRate</xsl:with-param>
									<xsl:with-param name="fldLbl">Transfer Fee Rate</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/tfrFeeRate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/tfrFeeRate"/>
									<xsl:with-param name="status" select="$dataNode/tfrFeeRate/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>									
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/tfrFeeType</xsl:with-param>
									<xsl:with-param name="fldLbl">Transfer Fee Type</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/tfrFeeType"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/tfrFeeTypeDesc"/>
									<xsl:with-param name="status" select="$dataNode/tfrFeeType/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>									
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/tfrBasedOne</xsl:with-param>
									<xsl:with-param name="fldLbl">Transfer Fee Based On</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/tfrBasedOn"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/tfrBasedOnDesc"/>
									<xsl:with-param name="status" select="$dataNode/tfrBasedOn/@status"/>									
									<xsl:with-param name="indent">yes</xsl:with-param>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/howPaid</xsl:with-param>
									<xsl:with-param name="fldLbl">Paid</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/howPaid"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/howPaidDesc"/>
									<xsl:with-param name="status" select="$dataNode/howPaid/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>									
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath"/>
									<xsl:with-param name="fldLbl"/>
									<xsl:with-param name="fldVal"/>
									<xsl:with-param name="fldValDesc"/>	
									<xsl:with-param name="status"/>		
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Managment Fee</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/mgmtFee</xsl:with-param>
									<xsl:with-param name="fldLbl">Management Fee Applicable</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/mgmtFee"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/mgmtFee"/>	
									<xsl:with-param name="status" select="$dataNode/mgmtFee/@status"/>		
									<xsl:with-param name="indent">yes</xsl:with-param>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/mgmtFeePayOpt</xsl:with-param>
									<xsl:with-param name="fldLbl">Management Fee Pay Option</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/mgmtFeePayOpt"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/mgmtFeePayOptDesc"/>	
									<xsl:with-param name="status" select="$dataNode/mgmtFeePayOpt/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>	
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/mgmtFeeBroker</xsl:with-param>
									<xsl:with-param name="fldLbl">Management Fee Broker</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/mgmtFeeBroker"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/mgmtFeeBroker"/>	
									<xsl:with-param name="status" select="$dataNode/mgmtFeeBroker/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/mgmtFeeBrokChg</xsl:with-param>
									<xsl:with-param name="fldLbl">Management Fee Broker Chg.</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/mgmtFeeBrokChg"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/mgmtFeeBrokChg"/>	
									<xsl:with-param name="status" select="$dataNode/mgmtFeeBrokChg/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>	
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Management Fee Rebate</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">								
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">FeeConfiguration/mfrRebate</xsl:with-param>
									<xsl:with-param name="fldLbl">MFR Applicable</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/mfrRebate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/mfrRebate"/>			
									<xsl:with-param name="status" select="$dataNode/mfrRebate/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>						
								</xsl:call-template>								
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath"/>
									<xsl:with-param name="fldLbl"/>
									<xsl:with-param name="fldVal"/>
									<xsl:with-param name="fldValDesc"/>	
									<xsl:with-param name="status"/>		
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:if test="$dataNode/FrontEndLoad">
							<xsl:call-template name="SubHeaderRow_Tmpl">
								<xsl:with-param name="label">Front End Load</xsl:with-param>
							</xsl:call-template>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/FrontEndLoad/feeType</xsl:with-param>
										<xsl:with-param name="fldLbl">Acquisit'n Fee Type</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/FrontEndLoad/feeType"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/FrontEndLoad/feeTypeDesc"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/FrontEndLoad/feeType/@status"/>
									</xsl:call-template>	
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/FrontEndLoad/howPaid</xsl:with-param>
										<xsl:with-param name="fldLbl">Acquisit'n Paid</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/FrontEndLoad/howPaid"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/FrontEndLoad/howPaidDesc"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/FrontEndLoad/howPaid/@status"/>
									</xsl:call-template>	
								</xsl:with-param>												
							</xsl:call-template>
							
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">										
										<xsl:with-param name="fldXPath">FeeConfiguration/FrontEndLoad/rate</xsl:with-param>
										<xsl:with-param name="fldLbl">Acquisit'n Rate</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/FrontEndLoad/rate"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/FrontEndLoad/rate"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/FrontEndLoad/rate/@status"/>
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">										
										<xsl:with-param name="fldXPath">FeeConfiguration/FrontEndLoad/basedOn</xsl:with-param>
										<xsl:with-param name="fldLbl">Acquisit'n Based On</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/FrontEndLoad/basedOn"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/FrontEndLoad/basedOnDesc"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/FrontEndLoad/basedOn/@status"/>										
									</xsl:call-template>		
								</xsl:with-param>																			
							</xsl:call-template>		
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/FrontEndLoad/maxRate</xsl:with-param>
										<xsl:with-param name="fldLbl">Max. Fee Rate</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/FrontEndLoad/maxRate"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/FrontEndLoad/maxRate"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/FrontEndLoad/maxRate/@status"/>
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">									
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/FrontEndLoad/minRate</xsl:with-param>
										<xsl:with-param name="fldLbl">Min. Fee Rate</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/FrontEndLoad/minRate"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/FrontEndLoad/minRate"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/FrontEndLoad/minRate/@status"/>
									</xsl:call-template>
								</xsl:with-param>												
							</xsl:call-template>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">	
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/FrontEndLoad/withHoldRate</xsl:with-param>
										<xsl:with-param name="fldLbl">Withhold Rate</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/FrontEndLoad/withHoldRate"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/FrontEndLoad/withHoldRate"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/FrontEndLoad/withHoldRate/@status"/>
									</xsl:call-template>																
								</xsl:with-param>							
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath"/>
										<xsl:with-param name="fldLbl"/>
										<xsl:with-param name="fldVal"/>
										<xsl:with-param name="fldValDesc"/>	
										<xsl:with-param name="status"/>		
									</xsl:call-template>
								</xsl:with-param>
							</xsl:call-template>											
						</xsl:if>
						<xsl:if test="$dataNode/BackEndLoad">
							<xsl:call-template name="SubHeaderRow_Tmpl">
								<xsl:with-param name="label">Back End Load</xsl:with-param>
							</xsl:call-template>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/BackEndLoad/feeType</xsl:with-param>
										<xsl:with-param name="fldLbl">Fee Type</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/BackEndLoad/feeType"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/BackEndLoad/feeTypeDesc"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/BackEndLoad/feeType/@status"/>
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/BackEndLoad/basedOn</xsl:with-param>
										<xsl:with-param name="fldLbl">BEL Based On</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/BackEndLoad/basedOn"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/BackEndLoad/basedOnDesc"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/BackEndLoad/basedOn/@status"/>
									</xsl:call-template>
								</xsl:with-param>												
							</xsl:call-template>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/BackEndLoad/brokerComm</xsl:with-param>
										<xsl:with-param name="fldLbl">Broker Comm.</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/BackEndLoad/brokerComm"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/BackEndLoad/brokerComm"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/BackEndLoad/brokerComm/@status"/>
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/BackEndLoad/withHoldRate</xsl:with-param>
										<xsl:with-param name="fldLbl">Withhold Rate</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/BackEndLoad/withHoldRate"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/BackEndLoad/withHoldRate"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/BackEndLoad/withHoldRate/@status"/>
									</xsl:call-template>
								</xsl:with-param>																
							</xsl:call-template>							
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/BackEndLoad/dscBasedRate</xsl:with-param>
										<xsl:with-param name="fldLbl">DSC Based Rate</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/BackEndLoad/dscBasedRate"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/BackEndLoad/dscBasedRate"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/BackEndLoad/dscBasedRate/@status"/>
									</xsl:call-template>
								</xsl:with-param>		
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/BackEndLoad/minVarDsc</xsl:with-param>
										<xsl:with-param name="fldLbl">Min. Var. DSC</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/BackEndLoad/minVarDsc"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/BackEndLoad/minVarDsc"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/BackEndLoad/minVarDsc/@status"/>
									</xsl:call-template>
								</xsl:with-param>												
							</xsl:call-template>
							<xsl:call-template name="DetailsRow_Tmpl">
								<xsl:with-param name="columnOneHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath">FeeConfiguration/BackEndLoad/dscOverride</xsl:with-param>
										<xsl:with-param name="fldLbl">DSC Override</xsl:with-param>
										<xsl:with-param name="fldVal" select="$dataNode/BackEndLoad/dscOverride"/>
										<xsl:with-param name="fldValDesc" select="$dataNode/BackEndLoad/dscOverride"/>
										<xsl:with-param name="indent">yes</xsl:with-param>
										<xsl:with-param name="status" select="$dataNode/BackEndLoad/dscOverride/@status"/>
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="columnTwoHTML">
									<xsl:call-template name="Field_tmpl">
										<xsl:with-param name="fldXPath"/>
										<xsl:with-param name="fldLbl"/>
										<xsl:with-param name="fldVal"/>
										<xsl:with-param name="fldValDesc"/>	
										<xsl:with-param name="status"/>		
									</xsl:call-template>
								</xsl:with-param>										
							</xsl:call-template>							
						</xsl:if>
						
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Fee Detail Scales</xsl:with-param>
						</xsl:call-template>
						<xsl:for-each select="$dataNode/FeeDetlScales/FeeScale">
							<xsl:if test="position() mod 2 = 1">
								<xsl:call-template name="DetailsRow_Tmpl">
									<xsl:with-param name="columnOneHTML">
										<xsl:call-template name="Record_tmpl">
											<xsl:with-param name="recordNode" select="."/>
											<xsl:with-param name="recordXPath">FeeConfiguration/FeeDetlScales/FeeScale</xsl:with-param>
											<xsl:with-param name="recordLbl"><xsl:text>&#8805;</xsl:text><xsl:value-of select="lower"/><xsl:text>&#160;&#160;&#160;&lt;</xsl:text><xsl:value-of select="upper"/></xsl:with-param>
											<xsl:with-param name="recordValDesc"><xsl:value-of select="rate"/>%</xsl:with-param>
											<xsl:with-param name="inclDetailsBtn">yes</xsl:with-param>
											<xsl:with-param name="status" select="@status"/>
										</xsl:call-template>
									</xsl:with-param>									
									<xsl:with-param name="columnTwoHTML">
										<xsl:choose>
											<xsl:when test="position() != last()">
												<xsl:call-template name="Record_tmpl">
													<xsl:with-param name="recordNode" select="following-sibling::FeeScale[1]"/>
													<xsl:with-param name="recordXPath">FeeConfiguration/FeeDetlScales/FeeScale</xsl:with-param>
													<xsl:with-param name="recordLbl"><xsl:text>&#8805;</xsl:text><xsl:value-of select="following-sibling::FeeScale[1]/lower"/><xsl:text>&#160;&#160;&#160;&lt;</xsl:text><xsl:value-of select="following-sibling::FeeScale[1]/upper"/></xsl:with-param>
													<xsl:with-param name="recordValDesc"><xsl:value-of select="following-sibling::FeeScale[1]/rate"/>%</xsl:with-param>
													<xsl:with-param name="inclDetailsBtn">yes</xsl:with-param>
													<xsl:with-param name="status" select="following-sibling::FeeScale[1]/@status"/>
												</xsl:call-template>
											</xsl:when>
											<xsl:otherwise>
												<xsl:call-template name="Field_tmpl"/>
											</xsl:otherwise>
										</xsl:choose>
									</xsl:with-param>																			
								</xsl:call-template>
							</xsl:if>																						
						</xsl:for-each>																								
					</tbody>
				</table>
			</div>
		</div>	
	</xsl:template>
	
	
	<!-- ========================== TRADE DAY CONTROLS SECTION TEMPLATE =============================-->
	<xsl:template match="screenName[text() = 'TradeDayCtrls']">		
		<xsl:param name="origDataNode"/>
		<xsl:param name="updateDataNode"/>
		
		<xsl:choose>
			<xsl:when  test="$updateDataNode/TradeDayControls">
				<xsl:call-template name="TradeDayCtrlsContent_tmpl">
					<xsl:with-param name="dataNode" select="$updateDataNode/TradeDayControls"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="TradeDayCtrlsContent_tmpl">
					<xsl:with-param name="dataNode" select="$origDataNode/TradeDayControls"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
		
	</xsl:template>
	
	
	<!-- ========================== TRADE DAY CONTROLS CONTENT TEMPLATE =============================-->
	<xsl:template name="TradeDayCtrlsContent_tmpl">
		<xsl:param name="dataNode"/>
		
		<xsl:variable name="sectionName">TradeDayCtrls</xsl:variable>
		
		<div id="{$sectionName}SectionDiv">
			<xsl:call-template name="SectionHeader_Tmpl">
				<xsl:with-param name="sectionName" select="$sectionName"/>
			</xsl:call-template>
			<div id="{$sectionName}DetailsContentDiv" class="ClassDetailsSectionDiv">								
				<table id="{$sectionName}Details_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="false">
					<xsl:call-template name="ContentTableHeader_Tmpl"/>
					<tbody>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Auto Force Cancel Days</xsl:with-param>
						</xsl:call-template>						
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/purAutoCancDays</xsl:with-param>
									<xsl:with-param name="fldLbl">Purchase</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/purAutoCancDays"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/purAutoCancDays"/>	
									<xsl:with-param name="status" select="$dataNode/purAutoCancDays/@status"/>								
									<xsl:with-param name="indent">yes</xsl:with-param>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/redAutoCancDays</xsl:with-param>
									<xsl:with-param name="fldLbl">Redemption</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/redAutoCancDays"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/redAutoCancDays"/>	
									<xsl:with-param name="status" select="$dataNode/redAutoCancDays/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/exchAutoCancDays</xsl:with-param>
									<xsl:with-param name="fldLbl">Exchange</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/exchAutoCancDays"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/exchAutoCancDays"/>
									<xsl:with-param name="status" select="$dataNode/exchAutoCancDays/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>									
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/trfAutoCancDays</xsl:with-param>
									<xsl:with-param name="fldLbl">Transfer</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/tfrAutoCancDays"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/tfrAutoCancDays"/>		
									<xsl:with-param name="status" select="$dataNode/tfrAutoCancDays/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>	
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Cut Off Days</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Record_tmpl">
									<xsl:with-param name="recordNode" select="$dataNode/CutOffDays/Purchase"/>
									<xsl:with-param name="recordXPath">TradeDayControls/CutOffDays/Purchase</xsl:with-param>
									<xsl:with-param name="recordLbl">Purchase</xsl:with-param>
									<xsl:with-param name="recordValDesc"><xsl:value-of select="$dataNode/CutOffDays/Purchase/numDays"/><xsl:text>&#160;</xsl:text>(<xsl:value-of select="$dataNode/CutOffDays/Purchase/dayTypeDesc"/>)</xsl:with-param>									
									<xsl:with-param name="status" select="$dataNode/CutOffDays/Purchase/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Record_tmpl">
									<xsl:with-param name="recordNode" select="$dataNode/CutOffDays/Redemption"/>
									<xsl:with-param name="recordXPath">TradeDayControls/CutOffDays/Redemption</xsl:with-param>
									<xsl:with-param name="recordLbl">Redemption</xsl:with-param>
									<xsl:with-param name="recordValDesc"><xsl:value-of select="$dataNode/CutOffDays/Redemption/numDays"/><xsl:text>&#160;</xsl:text>(<xsl:value-of select="$dataNode/CutOffDays/Redemption/dayTypeDesc"/>)</xsl:with-param>									
									<xsl:with-param name="status" select="$dataNode/CutOffDays/Redemption/@status"/>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Record_tmpl">
									<xsl:with-param name="recordNode" select="$dataNode/CutOffDays/ExchangeIn"/>
									<xsl:with-param name="recordXPath">TradeDayControls/CutOffDays/ExchangeIn</xsl:with-param>
									<xsl:with-param name="recordLbl">Exchange In</xsl:with-param>
									<xsl:with-param name="recordValDesc"><xsl:value-of select="$dataNode/CutOffDays/ExchangeIn/numDays"/><xsl:text>&#160;</xsl:text>(<xsl:value-of select="$dataNode/CutOffDays/ExchangeIn/dayTypeDesc"/>)</xsl:with-param>									
									<xsl:with-param name="status" select="$dataNode/CutOffDays/ExchangeIn/@status"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Record_tmpl">
									<xsl:with-param name="recordNode" select="$dataNode/CutOffDays/ExchangeOut"/>
									<xsl:with-param name="recordXPath">TradeDayControls/CutOffDays/ExchangeOut</xsl:with-param>
									<xsl:with-param name="recordLbl">Exchange Out</xsl:with-param>
									<xsl:with-param name="recordValDesc"><xsl:value-of select="$dataNode/CutOffDays/ExchangeOut/numDays"/><xsl:text>&#160;</xsl:text>(<xsl:value-of select="$dataNode/CutOffDays/ExchangeOut/dayTypeDesc"/>)</xsl:with-param>									
									<xsl:with-param name="status" select="$dataNode/CutOffDays/ExchangeOut/@status"/>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Trade Lead Days</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/tradeLeadDays</xsl:with-param>
									<xsl:with-param name="fldLbl">Trade Lead Days</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/tradeLeadDays"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/tradeLeadDays"/>		
									<xsl:with-param name="status" select="$dataNode/tradeLeadDays/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>							
								</xsl:call-template>
							</xsl:with-param>						
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath"/>
									<xsl:with-param name="fldLbl"/>
									<xsl:with-param name="fldVal"/>
									<xsl:with-param name="fldValDesc"/>		
									<xsl:with-param name="status"/>	
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Miscellaneous</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/lastSetlDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Last Settle Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/lastSetlDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/lastSetlDate"/>		
									<xsl:with-param name="status" select="$dataNode/lastSetlDate/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>								
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/nextSetlDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Next Settle Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/nextSetlDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/nextSetlDate"/>		
									<xsl:with-param name="status" select="$dataNode/nextSetlDate/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>								
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/lastValDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Last Valuation Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/lastValDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/lastValDate"/>		
									<xsl:with-param name="status" select="$dataNode/lastValDate/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>								
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/nextValDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Next Valuation Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/nextValDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/nextValDate"/>		
									<xsl:with-param name="status" select="$dataNode/nextValDate/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>								
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/lastNR</xsl:with-param>
									<xsl:with-param name="fldLbl">Last Cycle Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/lastNR"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/lastNR"/>		
									<xsl:with-param name="status" select="$dataNode/lastNR/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>								
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/nextNR</xsl:with-param>
									<xsl:with-param name="fldLbl">Next Cycle Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/nextNR"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/nextNR"/>		
									<xsl:with-param name="status" select="$dataNode/nextNR/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>								
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>	
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/lastMFeeDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Last Mngmt. Fee Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/lastMFeeDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/lastMFeeDate"/>		
									<xsl:with-param name="status" select="$dataNode/lastMFeeDate/@status"/>	
									<xsl:with-param name="indent">yes</xsl:with-param>								
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/lastMFRDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Last Mngmt. Fee Rebate Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/lastMFRDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/lastMFRDate"/>		
									<xsl:with-param name="status" select="$dataNode/lastMFRDate/@status"/>
									<xsl:with-param name="indent">yes</xsl:with-param>									
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>														
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeDayControls/lastDivdDate</xsl:with-param>
									<xsl:with-param name="fldLbl">Last Dividend Date</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/lastDivdDate"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/lastDivdDate"/>		
									<xsl:with-param name="status" select="$dataNode/lastDivdDate/@status"/>		
									<xsl:with-param name="indent">yes</xsl:with-param>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath"/>
									<xsl:with-param name="fldLbl"/>
									<xsl:with-param name="fldVal"/>
									<xsl:with-param name="fldValDesc"/>		
									<xsl:with-param name="status"/>	
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>																																																									
					</tbody>
				</table>
			</div>
		</div>	
	</xsl:template>
	
	
	<!-- ========================== TRADE CONFIGURATION SECTION TEMPLATE =============================-->
	<xsl:template match="screenName[text() = 'TradeConf']">		
		<xsl:param name="origDataNode"/>
		<xsl:param name="updateDataNode"/>
		
		<xsl:choose>
			<xsl:when test="$updateDataNode/TradeConfiguration">
				<xsl:call-template name="TradeConfContent_tmpl">
					<xsl:with-param name="dataNode" select="$updateDataNode/TradeConfiguration"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="TradeConfContent_tmpl">
					<xsl:with-param name="dataNode" select="$origDataNode/TradeConfiguration"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
		
	</xsl:template>
	
	
	<!-- ========================== TRADE CONFIGURATION CONTENT TEMPLATE =============================-->
	<xsl:template name="TradeConfContent_tmpl">
		<xsl:param name="dataNode"/>
		
		<xsl:variable name="sectionName">TradeConf</xsl:variable>
		
		<div id="{$sectionName}SectionDiv">
			<xsl:call-template name="SectionHeader_Tmpl">
				<xsl:with-param name="sectionName" select="$sectionName"/>
			</xsl:call-template>
			<div id="{$sectionName}DetailsContentDiv" class="ClassDetailsSectionDiv">								
				<table id="{$sectionName}Details_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="false">
					<xsl:call-template name="ContentTableHeader_Tmpl"/>
					<tbody>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/wireElig</xsl:with-param>
									<xsl:with-param name="fldLbl">Wire Order Allowed</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/wireElig"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/wireElig"/>
									<xsl:with-param name="status" select="$dataNode/wireElig/@status"/>									
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ordType</xsl:with-param>
									<xsl:with-param name="fldLbl">Order Type</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ordType"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ordTypeDesc"/>
									<xsl:with-param name="status" select="$dataNode/ordType/@status"/>									
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>												
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Class Eligibility</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/rrsp</xsl:with-param>
									<xsl:with-param name="fldLbl">RRSP</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/rrsp"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/rrsp"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/rrsp/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/rrif</xsl:with-param>
									<xsl:with-param name="fldLbl">RRIF</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/rrif"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/rrif"/>
									<xsl:with-param name="indent">yes</xsl:with-param>				
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/rrif/@status"/>					
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/esop</xsl:with-param>
									<xsl:with-param name="fldLbl">ESOP</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/esop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/esop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>				
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/esop/@status"/>					
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/nscCompliant</xsl:with-param>
									<xsl:with-param name="fldLbl">NSC Compliant</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/nscCompliant"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/nscCompliant"/>
									<xsl:with-param name="indent">yes</xsl:with-param>	
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/nscCompliant/@status"/>								
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/ams</xsl:with-param>
									<xsl:with-param name="fldLbl">AMS</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/ams"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/ams"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/ams/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/marginAllowed</xsl:with-param>
									<xsl:with-param name="fldLbl">Margin Allowed</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/marginAllowed"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/marginAllowed"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/marginAllowed/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/cssErrCorr</xsl:with-param>
									<xsl:with-param name="fldLbl">CSS Error Correction</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/cssErrCorr"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/cssErrCorr"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/cssErrCorr/@status"/>						
								</xsl:call-template>
							</xsl:with-param>							
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/freeRoll</xsl:with-param>
									<xsl:with-param name="fldLbl">Rollover Allowed</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/freeRoll"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/freeRoll"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/freeRoll/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>						
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/eligICTIn</xsl:with-param>
									<xsl:with-param name="fldLbl">Eligible ICT In</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/eligICTIn"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/eligICTInDesc"/>
									<xsl:with-param name="indent">yes</xsl:with-param>				
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/eligICTIn/@status"/>					
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/eligICTOut</xsl:with-param>
									<xsl:with-param name="fldLbl">Eligible ICT Out</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/eligICTOut"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/eligICTOutDesc"/>
									<xsl:with-param name="indent">yes</xsl:with-param>				
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/eligICTOut/@status"/>					
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Rollover Details</xsl:with-param>
						</xsl:call-template>						
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/freeRollFund</xsl:with-param>
									<xsl:with-param name="fldLbl">Rollover Fund</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/freeRollFund"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/freeRollFund"/>
									<xsl:with-param name="indent">yes</xsl:with-param>				
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/freeRollFund/@status"/>					
								</xsl:call-template>							
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/freeRollCl</xsl:with-param>
									<xsl:with-param name="fldLbl">Rollover Class</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/freeRollCl"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/freeRollCl"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/freeRollCl/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>						
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">								
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/freeRollPUD</xsl:with-param>
									<xsl:with-param name="fldLbl">Rollover Amount Type</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/freeRollPUD"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/freePUDDesc"/>
									<xsl:with-param name="indent">yes</xsl:with-param>				
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/freeRollPUD/@status"/>					
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/ClassEligibility/freeRollQualPrd</xsl:with-param>
									<xsl:with-param name="fldLbl">Qual. Period</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/ClassEligibility/freeRollQualPrd"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/ClassEligibility/freeRollQualPrd"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/ClassEligibility/freeRollQualPrd/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Stop Flags</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/commRebStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Comm. Rebate</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/commRebStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/commRebStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/StopFlags/commRebStop/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/pacStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop PAC</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/pacStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/pacStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/StopFlags/pacStop/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>													
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/swpStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop SWP</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/swpStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/swpStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>	
									<xsl:with-param name="status" select="$dataNode/StopFlags/swpStop/@status"/>								
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/purStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Purchase</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/purStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/purStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/StopFlags/purStop/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/redStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Redeem</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/redStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/redStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/StopFlags/redStop/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/autoXferOutStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Auto Transfer Out</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/autoXferOutStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/autoXferOutStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/StopFlags/autoXferOutStop/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/autoXferInStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Auto Transfer In</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/autoXferInStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/autoXferInStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/StopFlags/autoXferInStop/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/xferOutStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Transfer Out</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/xferOutStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/xferOutStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/StopFlags/xferOutStop/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/StopFlags/xferInStop</xsl:with-param>
									<xsl:with-param name="fldLbl">Stop Transfer In</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/StopFlags/xferInStop"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/StopFlags/xferInStop"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/StopFlags/xferInStop/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath"/>
									<xsl:with-param name="fldLbl"/>
									<xsl:with-param name="fldVal"/>
									<xsl:with-param name="fldValDesc"/>		
									<xsl:with-param name="status"/>	
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>					
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Purchase Min. Amounts</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/minInit</xsl:with-param>
									<xsl:with-param name="fldLbl">Min. Initial Amount</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/minInit"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/minInit"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/minInit/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/minSub</xsl:with-param>
									<xsl:with-param name="fldLbl">Min. Subsequent Amount</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/minSub"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/minSub"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/minSub/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>						
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Redemption Min. Amounts</xsl:with-param>
						</xsl:call-template>						
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/redMinInit</xsl:with-param>
									<xsl:with-param name="fldLbl">Min. Initial Amount</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/redMinInit"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/redMinInit"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/redMinInit/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/redMinSub</xsl:with-param>
									<xsl:with-param name="fldLbl">Min. Subsequent Amount</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/redMinSub"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/redMinSub"/>
									<xsl:with-param name="indent">yes</xsl:with-param>	
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/redMinSub/@status"/>								
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Systematic Min. Amounts</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/swpMin</xsl:with-param>
									<xsl:with-param name="fldLbl">SWP Min. Amount</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/swpMin"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/swpMin"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/swpMin/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/pacMin</xsl:with-param>
									<xsl:with-param name="fldLbl">PAC Min. Amount</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/pacMin"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/pacMin"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/pacMin/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>							
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Min. Balance Amounts</xsl:with-param>
						</xsl:call-template>	
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/minFundClBal</xsl:with-param>
									<xsl:with-param name="fldLbl">Min. Fund Class Balance</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/minFundClBal"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/minFundClBal"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/minFundClBal/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/MinMaxAmounts/minAcctBal</xsl:with-param>
									<xsl:with-param name="fldLbl">Min. Account Balance</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/MinMaxAmounts/minAcctBal"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/MinMaxAmounts/minAcctBal"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/MinMaxAmounts/minAcctBal/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="SubHeaderRow_Tmpl">
							<xsl:with-param name="label">Calculation Methods</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/CalcMethods/purAgingRule</xsl:with-param>
									<xsl:with-param name="fldLbl">Purchase Aging Rule</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/CalcMethods/purAgingRule"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/CalcMethods/purAgingRuleDesc"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/CalcMethods/purAgingRule/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/CalcMethods/gainLossMthd</xsl:with-param>
									<xsl:with-param name="fldLbl">Gain/Loss Method</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/CalcMethods/gainLossMthd"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/CalcMethods/gainLossMthdDesc"/>
									<xsl:with-param name="indent">yes</xsl:with-param>		
									<xsl:with-param name="status" select="$dataNode/CalcMethods/gainLossMthd/@status"/>							
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<xsl:call-template name="DetailsRow_Tmpl">
							<xsl:with-param name="columnOneHTML">
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/CalcMethods/freeConsol</xsl:with-param>
									<xsl:with-param name="fldLbl">Free Consolidation</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/CalcMethods/freeConsol"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/CalcMethods/freeConsolDesc"/>
									<xsl:with-param name="indent">yes</xsl:with-param>			
									<xsl:with-param name="status" select="$dataNode/CalcMethods/freeConsol/@status"/>						
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="columnTwoHTML">								
								<xsl:call-template name="Field_tmpl">
									<xsl:with-param name="fldXPath">TradeConfiguration/CalcMethods/pShipUnitAsmt</xsl:with-param>
									<xsl:with-param name="fldLbl">Partnership Unit Assignment</xsl:with-param>
									<xsl:with-param name="fldVal" select="$dataNode/CalcMethods/pShipUnitAsmt"/>
									<xsl:with-param name="fldValDesc" select="$dataNode/CalcMethods/pShipUnitAsmtDesc"/>
									<xsl:with-param name="indent">yes</xsl:with-param>				
									<xsl:with-param name="status" select="$dataNode/CalcMethods/pShipUnitAsmt/@status"/>					
								</xsl:call-template>								
							</xsl:with-param>
						</xsl:call-template>
					</tbody>
				</table>
			</div>
		</div>						
	</xsl:template>
	
</xsl:stylesheet>