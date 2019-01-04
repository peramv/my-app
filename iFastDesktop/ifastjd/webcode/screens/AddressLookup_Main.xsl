<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/AddressLookup_ListTemplates.xsl"/>

	<!-- identifiers for address entry fields -->
	<xsl:variable name="vSTREET_NUM">streetNum</xsl:variable>
	<xsl:variable name="vSUFFIX">suffix</xsl:variable>
	<xsl:variable name="vUNIT_NUM">unitNum</xsl:variable>
	<xsl:variable name="vUNIT_DESC">unitDesc</xsl:variable>
	<xsl:variable name="vPO_BOX_NUM">poBoxNum</xsl:variable>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">Address Lookup</xsl:with-param>					
		</xsl:call-template>
	</xsl:template>
		
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/AddressLookup.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/AddressLookup.js"></script>
		
		<script language="javascript">
			// address list types
			var _PO_BOX 		= "<xsl:value-of select="$vPO_BOX"/>";
			var _CIVIC 			= "<xsl:value-of select="$vCIVIC"/>";
			var _GENERAL		= "<xsl:value-of select="$vGENERAL"/>";
			var _RURAL_ROUTE 		= "<xsl:value-of select="$vRURAL_ROUTE"/>";
			var _ST_ROUTE 		= "<xsl:value-of select="$vST_ROUTE"/>";
			
			// address entry field identifiers
			var _STREET_NUM 		= "<xsl:value-of select="$vSTREET_NUM"/>";
			var _SUFFIX			= "<xsl:value-of select="$vSUFFIX"/>";
			var _UNIT_NUM		= "<xsl:value-of select="$vUNIT_NUM"/>";
			var _UNIT_DESC 		= "<xsl:value-of select="$vUNIT_DESC"/>";
			var _PO_BOX_NUM 		= "<xsl:value-of select="$vPO_BOX_NUM"/>";						
		</script>					
	</xsl:template>
	
	
	<!-- ========================== PAGE RELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >
		<div id="filter-InputDiv">
			<span id="postalCodeLabel">Postal code:</span>
			<input id="postalCodeLookupFld" type="text" onkeyup="keyupHandler_postalCodeFld()" onclick="clickHandler_postalCodeFld()"  onkeydown="keydownHandler_postalCodeFld()">
				<xsl:attribute name="value"><xsl:value-of select="/websrvXML/FormInformation/pstlCode"/></xsl:attribute>
			</input>
			<input id="searchBtn" type="button" value="Search" class='Desktop_Btn' onclick="clickHandler_searchBtn()"/>							
		</div>
		
		<div id="filter-ResultDiv">
			<div id="ResultLabel" class="Desktop_Background">Search Results</div>
			<div id="ResultContentsDiv">
				<xsl:choose>
					<xsl:when test="/websrvXML/dtPCLookupReloadResponse">
						<xsl:apply-templates select="/websrvXML/dtPCLookupReloadResponse"/>						
					</xsl:when>
					<xsl:otherwise>
						<div id="noSearchLbl">No lookup performed yet ...</div>
					</xsl:otherwise>
				</xsl:choose>
			</div>	
		</div>
		
		<div id="addressEntrySectionDiv">
			<div id="addressEntryDiv">
				<div class="addressEntryItemDiv" id="streetNumItemDiv">
					<span class="addressEntryLabel" id="{$vSTREET_NUM}Lbl">Street number:</span>
					<span class="oddEvenFlag" id="oddOnlyFlag">*</span>
					<span class="oddEvenFlag" id="evenOnlyFlag">**</span>					
					<input class="addressEntryFld" type="text" id="{$vSTREET_NUM}Fld" />									
				</div>
				<div class="addressEntryItemDiv">
					<span class="addressEntryLabel" id="{$vSUFFIX}Lbl">Suffix:</span>
					<input class="addressEntryFld" type="text" id="{$vSUFFIX}Fld" />
				</div>
				<div class="addressEntryItemDiv">
					<span class="addressEntryLabel" id="{$vUNIT_NUM}Lbl">Unit number:</span>
					<input class="addressEntryFld" type="text" id="{$vUNIT_NUM}Fld"/>
				</div>
				<div class="addressEntryItemDiv">
					<span class="addressEntryLabel" id="{$vUNIT_DESC}Lbl">Unit description:</span>
					<input class="addressEntryFld" type="text" id="{$vUNIT_DESC}Fld"/>
				</div>
				<div class="addressEntryItemDiv">
					<span class="addressEntryLabel" id="{$vPO_BOX_NUM}Lbl">PO Box:</span>
					<input class="addressEntryFld" type="text" id="{$vPO_BOX_NUM}Fld" />
				</div>
				<span class="oddEvenOnlyLabel" id="oddOnlyLabel">* Only odd values are permitted</span>
				<span class="oddEvenOnlyLabel" id="evenOnlyLabel">** Only even values are permitted</span>
			</div>
			<div id="addressDisplayDiv">
				<div class="addressDisplayItemDiv">
					<span class="addressDisplayItemLabel">Address 1:</span>
					<span id="addressLineOneLabel" class="addressDisplayItem"></span>
				</div>
				<div class="addressDisplayItemDiv">
					<span class="addressDisplayItemLabel">Address 2:</span>
					<span id="addressLineTwoLabel" class="addressDisplayItem"></span>
				</div>
				<div class="addressDisplayItemDiv">
					<span class="addressDisplayItemLabel">Address 3:</span>
					<span id="addressLineThreeLabel" class="addressDisplayItem"></span>
				</div>
				<div class="addressDisplayItemDiv">
					<span class="addressDisplayItemLabel">City:</span>
					<span id="cityLabel" class="addressDisplayItem"></span>
					<span class="addressDisplayItemLabel">Province:</span>
					<span id="provLabel" class="addressDisplayItem">
						<xsl:attribute name="prov">
							<xsl:value-of select="/websrvXML/dtPCLookupReloadResponse/PCLookupDetails/prov"/>
						</xsl:attribute>
						<xsl:attribute name="pstlCode">
							<xsl:value-of select="/websrvXML/dtPCLookupReloadResponse/PCLookupDetails/pstlCode"/>
						</xsl:attribute>
						<xsl:attribute name="cntryCode">
							<xsl:value-of select="/websrvXML/dtPCLookupReloadResponse/PCLookupDetails/cntryCode"/>
						</xsl:attribute>
						<xsl:value-of select="/websrvXML/dtPCLookupReloadResponse/PCLookupDetails/prov"/>
					</span>
				</div>				
			</div>
		</div>
		<div id="main-closebtnline">
			<input type="button" value="OK" id='okBtn' class='Desktop_Btn' onclick="clickHandler_okBtn();"/>			
			<input type="button" value="Cancel" id='cancelBtn' class='Desktop_Btn' onclick="clickHandler_cancelBtn();"/>
			
			<!-- Desktop integration buttons -->
			<input type="button" value="" style="display:none" name="btnCancel" id="btnCancel"/>			
			<input type="button" value="" style="display:none" name="btnOK" id="btnOK"/>
		</div>		
		
		
	</xsl:template>
		
</xsl:stylesheet>