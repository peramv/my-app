<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/AccountStaticDataVerify_TableTemplate.xsl"/>	
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">Account Static Data Verify</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/AccountStaticDataVerify.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/AccountStaticDataVerify.js"></script>
		<script language="javascript" type="text/javascript">
			var _AccountNum = "<xsl:value-of select=".//FormInformation/AccountNum"/>";
			<xsl:choose>
				<xsl:when test=".//FormInformation/updatesSubmitted">
					_updatesSubmitted = true;	
				</xsl:when>
				<xsl:otherwise>
					_updatesSubmitted = false;	
				</xsl:otherwise>
			</xsl:choose>
		</script>
	</xsl:template>
	
	
	<!-- ========================== PAGE RELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback"/>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >
		<div id="ClassList_TableDiv" class="Desktop_TableDiv" style="overflow-y:scroll;">
			<xsl:call-template name="Table_Tmpl">
				<xsl:with-param name="accountStaticData" select="/websrvXML/dtEntityFldVrfyInitResponse" />
			</xsl:call-template>
		</div>
		<br />
		<div id="main-closebtnline" align="center">
			<input type="button" value="Update" name="btnUpdate" id="btnUpdate" class='Desktop_Btn' onclick="clickHandler_updateBtn();" disabled="true"/>
			<input type="button" value="Close" name="btnClose" id="btnClose" class='Desktop_Btn' onclick="clickHandler_closeBtn()" />
			<input type="button" value="ConfirmDlg" name="btnConfirmDlg" id="btnConfirmDlg" class='Desktop_Btn' style="display:none" />
		</div>	
	</xsl:template>
	
		
</xsl:stylesheet>