<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	
	<xsl:variable name="SCREEN_NAME">BasicInfo</xsl:variable>
	
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
		
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">fundIdentifierPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">400</xsl:with-param>
			<xsl:with-param name="height">130</xsl:with-param>
			<xsl:with-param name="top">400</xsl:with-param>
			<xsl:with-param name="left">250</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="FundIdentifierPopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>
		
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">shareGroupPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">490</xsl:with-param>
			<xsl:with-param name="height">130</xsl:with-param>
			<xsl:with-param name="top">600</xsl:with-param>
			<xsl:with-param name="left">225</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="ShareGroupPopupContents_tmpl"/></xsl:with-param>			
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
		<xsl:call-template name="BreadCrumb_Tmpl">
			<xsl:with-param name="isAddMode" select="$ADD_MODE"/>
			<xsl:with-param name="activeScreenName" select="$SCREEN_NAME"/>
		</xsl:call-template>
		
		<xsl:call-template name="CommonEditScreenFields_Tmpl">
			<xsl:with-param name="isAddMode" select="$ADD_MODE"/>
		</xsl:call-template>
		
		<div class="ScreenContentsDiv">
			<div class="EntryScreenSectionDiv">
				<div class="SimpleSectionContentsDiv">
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">Fund Code</span>
						<span class="fldValueSpan_lrg">
							<input id="fundCodeFld" type="text" class="fld_sml" disabled="true">
							</input>
						</span>
						
						<span class="fldLabelSpan_med">Class Code</span>
						<span class="fldValueSpan_lrg">
							<input id="classCodeFld" type="text" class="fld_sml" mandatory="true">
								<xsl:attribute name="onchange">
									<xsl:if test="$ADD_MODE = 'true'">changeHandler_classCodeFld()</xsl:if>
								</xsl:attribute>							
							</input>
						</span>
					</div>
					
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">English Description</span>
						<span class="fldValueSpan_lrg">
							<input type="text" class="fld_lrg" xpath="ClassBasic/classE">
							</input>
						</span>
						
						<span class="fldLabelSpan_med">French Description</span>
						<span class="fldValueSpan_lrg">
							<input type="text" class="fld_lrg" xpath="ClassBasic/classF">
							</input>
						</span>
					</div>		
					
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">Status</span>
						<span class="fldValueSpan_lrg">
							<select id="statFld" class="fld_med" xpath="ClassBasic/stat" mandatory="true">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="id">StatusList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>
						
						<span class="fldLabelSpan_med">Status Date</span>
						<span class="fldValueSpan_lrg">
							<input type="text" id="statDateFld" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld" xpath="ClassBasic/statDate">
							</input>
						</span>
					</div>		
					
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">Effective Date</span>
						<span class="fldValueSpan_lrg">
							<input type="text" id="effDateFld" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld"  xpath="ClassBasic/deff" mandatory="true">
							</input>
						</span>
						
						<span class="fldLabelSpan_med">Stop Date</span>
						<span class="fldValueSpan_lrg">
							<input type="text" id="stopDateFld" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld" xpath="ClassBasic/stopDate" mandatory="true">
							</input>
						</span>
					</div>
									
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">ESG Company Code</span>
						<span class="fldValueSpan_lrg">							
							<select id="companyFld" class="fld_med" xpath="ClassBasic/company" mandatory="true">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="listName">CompanyCodeList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>											
						<span class="fldLabelSpan_med">Bare Trustee</span>
						<span class="fldValueSpan_lrg">
							<select class="fld_lrg" xpath="ClassBasic/bareTrustee" descXpath="ClassBasic/bareTrusteeDesc">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="id">BareTrusteeList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>																			
					</div>
					
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">Load Type</span>
						<span class="fldValueSpan_lrg">
							<select id="loadTypeFld" class="fld_med" xpath="ClassBasic/loadType" descXpath="ClassBasic/loadTypeDesc" mandatory="true">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="id">LoadTypeList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>						
						<span class="fldLabelSpan_med">Risk Rating</span>
						<span class="fldValueSpan_med">
							<select class="fld_med" xpath="ClassBasic/riskRating" descXpath="ClassBasic/riskRatingDesc">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="id">RiskRatingList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>											
					</div>
				
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_lrg">Fund/Fund Class Curr Holiday</span>
						<span class="fldValueSpan_lrg">
							<select id="fundCurHldyOptFld" class="fld_xlrg_2" xpath="ClassBasic/FundCurHldyOpt" descXpath="ClassBasic/FundCurHldyOptDesc">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="listName">FundCurHldyOptList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>
					</div>
			
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">				
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:123px;">
						Inventory Tracking
					</div>	
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_lrg">Applicable</span>			
							<span class="fldValueCheckbox">
								<input type="checkbox" xpath="ClassBasic/InventoryTracking/applicable">								
								</input>
							</span>																			
							<span class="fldLabelSpan_med">Based On</span>
							<span class="fldValueSpan_lrg">																		
								<select class="fld_lrg" xpath="ClassBasic/InventoryTracking/basedOn" descXpath="ClassBasic/InventoryTracking/basedOnDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">BasedOnInvTrackList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>							
													
						</div>
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:140px">
						Fund Sub-Categories
					</div>
					
					<div class="FieldSetContentsDiv">
						<xsl:for-each select="//Lists/List[@id='FundSubCatList']/Element[string-length(code) &gt; 0]">
							<xsl:if test="position() mod 3 = 1">							
								<div class="FieldRowDiv">							
									<span class="fldLabelSpan_med"><xsl:value-of select="value"/></span>
									<span class="fldCheckboxSpan">
										<input type="checkbox" onclick="clickHandler_subCatCheckbox( this );">
											<xsl:attribute name="id">subCat<xsl:value-of select="code"/>Cbox</xsl:attribute>
											<xsl:attribute name="subCat"><xsl:value-of select="code"/></xsl:attribute>
										</input>								
									</span>
									
									<xsl:if test="following-sibling::Element[1]">
										<span class="fldLabelSpan_lrg"><xsl:value-of select="following-sibling::Element[1]/value"/></span>
										<span class="fldCheckboxSpan">
											<input type="checkbox" onclick="clickHandler_subCatCheckbox( this );">
												<xsl:attribute name="id">subCat<xsl:value-of select="following-sibling::Element[1]/code"/>Cbox</xsl:attribute>
												<xsl:attribute name="subCat"><xsl:value-of select="following-sibling::Element[1]/code"/></xsl:attribute>
											</input>								
										</span>
									</xsl:if>
									
									<xsl:if test="following-sibling::Element[2]">
										<span class="fldLabelSpan_lrg"><xsl:value-of select="following-sibling::Element[2]/value"/></span>
										<span class="fldCheckboxSpan">
											<input type="checkbox" onclick="clickHandler_subCatCheckbox( this );">
												<xsl:attribute name="id">subCat<xsl:value-of select="following-sibling::Element[2]/code"/>Cbox</xsl:attribute>
												<xsl:attribute name="subCat"><xsl:value-of select="following-sibling::Element[2]/code"/></xsl:attribute>
											</input>								
										</span>
									</xsl:if>
								</div>
							</xsl:if>	
						</xsl:for-each>
					</div>	
					
					<!-- Table is used for storing data only (not displayed), and is updated via the checkboxes -->
					<div id="SubCategories_TableDiv"  class="Desktop_TableDiv" style="display:none">
						<table id="SubCategories_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" xpath="ClassBasic/FundSubCategories/FundSubCat" fieldList="subCat;subCatDesc;subCatFlag;subCatVer" displayFieldList="subCatDesc;subCatFlag" updated="false">
							<thead>
								<tr>						
									<td style="width:500;" columnWidth="500">
										Sub-Category
									</td>
									<td style="width:250;" columnWidth="250">
										Flag
									</td>						
								</tr>
							</thead>
							<tbody>					
								
							</tbody>
						</table>
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div id="FundIdentifiersSectionDiv" class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:106px">
						Fund Identifiers
					</div>
					
					<div id="FundIdentifiers_TableDiv" class="Desktop_TableDiv">
						<table id="FundIdentifiers_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="true" rowSelectable="true" scrollable="true" xpath="ClassBasic/FundIdentifiers/FundIdentifier" fieldList="idType;idTypeDesc;idValue;fundIDVer;fundIDUUID;runMode" displayFieldList="idTypeDesc;idValue">
							<thead>
								<tr>						
									<td style="width:500;" columnWidth="500">
										ID Type
									</td>
									<td style="width:250;" columnWidth="250">
										ID Value
									</td>						
								</tr>
							</thead>
							<tbody>					
								
							</tbody>
						</table>
					</div>
					
					<div id="FundIdentifersSectionActionButtonsDiv">													
						<input type="button" id="FundIdentifierAddBtn" value="Add" class="Desktop_Btn" onclick="clickHandler_addFundIdentifierBtn();"/>			
						<input type="button" id="FundIdentifierModBtn" value="Modify" disabled="true" class="Desktop_Btn" onclick="clickHandler_modFundIdentifierBtn();"/>										
						<input type="button" id="FundIdentifierDelBtn" value="Delete" disabled="true" class="Desktop_Btn" onclick="clickHandler_delFundIdentifierBtn();"/>
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div id="ShareGroupsSectionDiv" class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:95px">
						Share Groups
					</div>
					
					<div id="ShareGroups_TableDiv" class="Desktop_TableDiv">
						<table id="ShareGroups_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="true" rowSelectable="true" scrollable="true" xpath="ClassBasic/ShareGroups/ShareGroup" fieldList="shGroup;groupName;deff;active;runMode" displayFieldList="shGroup;groupName;deff;active">
							<thead>
								<tr>						
									<td style="width:100;" columnWidth="100">
										Group Id
									</td>
									<td style="width:400;" columnWidth="400">
										Group Name
									</td>
									<td style="width:150;" columnWidth="150">
										Effective Date
									</td>
									<td style="width:100;" columnWidth="100">
										Active
									</td>																				
								</tr>
							</thead>
							<tbody>					
								
							</tbody>
						</table>
					</div>
					
					<div id="ShareGroupsSectionActionButtonsDiv">													
						<input type="button" id="ShareGroupAddBtn" value="Add" class="Desktop_Btn" onclick="clickHandler_addShareGroupBtn();"/>			
						<input type="button" id="ShareGroupModBtn" value="Modify" class="Desktop_Btn" disabled="true" onclick="clickHandler_modShareGroupBtn();"/>										
						<input type="button" id="ShareGroupDelBtn" value="Delete" class="Desktop_Btn" disabled="true" onclick="clickHandler_delShareGroupBtn();"/>
					</div>
				</div>
			</div>
			
			
		</div>
		<xsl:call-template name="ScreenButtons_Tmpl">
			<xsl:with-param name="screenName" select="$SCREEN_NAME"/>
			<xsl:with-param name="isAddMode" select="$ADD_MODE"/>
		</xsl:call-template>
		
		<xsl:call-template name="ScreenForm_Tmpl"/>
		
	</xsl:template>
	
	<!-- ========================== FUND IDENTIFIER POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="FundIdentifierPopupContents_tmpl">
		<input type="hidden" id="fundIdentPopup_fundIDVerFld"/>
		<input type="hidden" id="fundIdentPopup_fundIDUUIDFld"/>		
		
		<div style="padding:10px;">	
				
			<div class="FieldRowDiv">
				<span class="fldLabelSpan_sml">Id Type</span>
				<span class="fldValueSpan_lrg">
					<select id="fundIdentPopup_idTypeFld" class="fld_lrg">
						<xsl:call-template name="List_tmpl">
							<xsl:with-param name="id">FundIdentifierList</xsl:with-param>
						</xsl:call-template>
					</select>
				</span>
			</div>
			<div class="FieldRowDiv">
				<span class="fldLabelSpan_sml">Id Value</span>
				<span class="fldValueSpan_lrg">
					<input id="fundIdentPopup_idValueFld" type="text" class="fld_med">
					</input>
				</span>
			</div>
			
			<div style="padding-top:10px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn" onclick="clickHandler_fundIdentifierPopupOKBtn()"/>
				<input type="button" value="Cancel" class="Desktop_Btn" onclick="clickHandler_fundIdentifierPopupCancelBtn()"/>
			</div>
		</div>		
	</xsl:template>
	
	<!-- ========================== SHARE GROUP POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="ShareGroupPopupContents_tmpl">
		<div style="padding:10px;">	
			
			<div class="FieldRowDiv">
				<span class="fldLabelSpan_sml">Share Group</span>
				<span class="fldValueSpan_xlrg">
					<select class="fld_xlrg" id="shareGroupPopup_groupFld">
						<xsl:call-template name="List_tmpl">
							<xsl:with-param name="id">ShGroupList</xsl:with-param>
						</xsl:call-template>
					</select>
				</span>		
			</div>
			
			<div class="FieldRowDiv">
				<span class="fldLabelSpan_sml">Active</span>
				<span class="fldValueCheckbox">
					<input type="checkbox" id="shareGroupPopup_activeFld">
					</input>
				</span>
				<span class="fldLabelSpan_sml">Eff.Date</span>
				<span class="fldValueSpan_med">
					<input id="shareGroupPopup_deffFld" type="text" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
					</input>
				</span>				
			</div>
			
			<div style="padding-top:10px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn" onclick="clickHandler_shareGroupPopupOKBtn()"/>
				<input type="button" value="Cancel" class="Desktop_Btn" onclick="clickHandler_shareGroupPopupCancelBtn()"/>
			</div>
		</div>		
	</xsl:template>
	
	
</xsl:stylesheet>