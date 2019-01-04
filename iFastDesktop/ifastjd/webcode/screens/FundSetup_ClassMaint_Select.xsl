<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_ClassListTemplate.xsl"/>
	
	<xsl:variable name="SCREEN_NAME" select="/websrvXML/FormInformation/screenToLoad"/>	
		
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle" select="/websrvXML/ScreensConfig/ScreenDefList/ScreenDef[screenName = $SCREEN_NAME]/screenLabel"/>			
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
			
			<xsl:if test="/websrvXML/FormInformation/fundCode">
				_initFundCode = "<xsl:value-of select="/websrvXML/FormInformation/fundCode"/>";
			</xsl:if>
		</script>		
	</xsl:template>
	
	
	<!-- ========================== PAGE RELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback" />
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >		
		<div id="filterSectionDiv">
			<div class="filterItemDiv">
				<span class="filterItemLbl">Fund</span>
				<input suggestField="true" 				  				      
					type="text"
					id="fundFld"			
					dropdownClass="Desktop_suggestDropdown_veryBig"
					contentClass="Desktop_suggestDropdownContent"
					highlightClass="Desktop_suggestDropdownHighlight"
					displayItems="fndDisp"
					searchURLGenerator="getFundOnlySuggestURL"														
					updateCallbackFn="updateHandler_fundFld"
					onkeyup="keyupHandler_fundFld();"/>					
			</div>
			
			<input type="button" value="Search" id='classLookupBtn' class='Desktop_Btn' onclick='clickHandler_classLookupBtn()'/>			
		</div>
				
		<div id="resultsSectionDiv">
			<div id="ClassList_TableDiv" class="Desktop_TableDiv">
				<xsl:call-template name="ClassList_Tmpl"/>
			</div>	
		</div>
							
		<div id="actionButtonsDiv">		
			<input type="button" value="Add" id='addBtn' class="Desktop_Btn" onclick='clickHandler_addBtn()'/>											
			<input type="button" value="View" id='viewBtn' class="Desktop_Btn" onclick='clickHandler_viewBtn();'/>																		
			<input type="button" value="Limitation Override" id='limitOverrideBtn' class="Desktop_Btn" onclick='clickHandler_limitOverrideBtn();'/>
		</div>
		
		<div class="ScreenButtonsDiv">
			<input type="button" value="Close" name="btnClose" id="btnClose" class="Desktop_Btn"/>
		</div>
		
		<xsl:call-template name="ScreenForm_Tmpl"/>
	</xsl:template>
</xsl:stylesheet>