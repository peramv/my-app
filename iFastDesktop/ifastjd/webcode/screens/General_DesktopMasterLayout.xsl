<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	
	<!-- Init CLIENT & PATH VARIABLES - start -->
	<xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
	<xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
	<xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
	<xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/')"/>
	<xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
	<xsl:variable name="vTIDX"         select="/websrvXML/FormInformation/tidx"/>
	<xsl:variable name="vDesktopColor" select="/websrvXML/FormInformation/bgcolor"/>	
	
	<!-- =============================MASTER LAYOUT - start  ======================== -->
	<xsl:template name="master_layout">
		<xsl:param name="session"/>		
		<xsl:param name="pageTitle"/>
		
						
				
		<Screen>
			<html xmlns="http://www.w3.org/1999/xhtml">
				<head>
					<meta http-equiv="Content-Type" content="text/html;" />
					
					<!--Display Title-->
					<title>
						<xsl:value-of select="$pageTitle"/>
					</title>
					
					<!--Display Common header -->
					<xsl:call-template name="common_header"/>					
				</head>
				
				<body onload="preload()" class="Desktop_Background">
					<xsl:call-template name="main_page">						
						<xsl:with-param name="pageTitle">
							<xsl:value-of select="$pageTitle"/>
						</xsl:with-param>						
					</xsl:call-template>
				</body>
				
			</html>
		</Screen>
	</xsl:template>
	
	
	<!-- =================MAIN PAGE(page_preload_callback) TEMPLATE - start================ -->
	<xsl:template name="main_page">			
		<xsl:param name="pageTitle"/>		
		
		<!--div class="overOut" id="loadingID" style="z-index: 1999;">
			<div class="over"/>
			<dl id="totalBox" class="box boxMargin">
				<div id="loadingID_msg"/>
			</dl>
		</div-->
		
		<xsl:call-template name="page_preload_callback" />
						
		<div class="wrapper Desktop_Background">			
			<xsl:call-template name="DesktopScreenDisabler"/>
			<xsl:call-template name="DesktopScreenProcessingIndicator"/>
						
			<div class="main">				
					<!--Page Title and Navigation Bar start-->
					<xsl:if test="string-length( $pageTitle ) &gt; 0">
						<div id="main-topic">
							<span id='title'>
								<xsl:value-of select="$pageTitle"/>
							</span>
						</div>
					</xsl:if>
					
					<xsl:call-template name="main_form"/>
									
			</div>

		</div>
	</xsl:template>	
	
	
	<!-- =====================MAIN FORM TEMPLATE (form_callback) - start  =================== -->
	<xsl:template name="main_form">		
			<xsl:attribute name="action">
				<xsl:value-of select="$vServletPath"/>
			</xsl:attribute>
			<xsl:call-template name="form_callback" />		
	</xsl:template>	
	
		
	<!-- ============= COMMON HTTP HEADER TEMPLATE(header_callback) - start  ============ -->
	<xsl:template name="common_header">
		<script src="{$vURL}javascript/General_Desktop.js"/>
		<script src="{$vURL}javascript/General_DesktopError.js"/>
		<script src="{$vURL}javascript/General_DesktopFlag.js"/>
		<script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
		<script src="{$vURL}WebLibrary/JSLib/XML.js"/>
		<script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
		<script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
		<script src="{$vURL}WebLibrary/JSLib/Err.js"/>
		<script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
		<script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
		<script src="{$vURL}WebLibrary/JSLib/JSXML.js"/>		
		<script src="{$vURL}WebLibrary/WebComps/IFDSTable.js"/>
		<script src="{$vURL}WebLibrary/WebComps/IFDSDatepicker.js"/>
		<script src="{$vURL}WebLibrary/WebComps/IFDSCalendarWidget.js"/>
		<script src="{$vURL}WebLibrary/WebComps/SuggestFieldComponent.js"/>
		
		<!-- define common javascript vars -->
		<script language="javascript">
			var _vClient 		= "<xsl:value-of select="$vClient"/>";
			var _vServletPath 	= "<xsl:value-of select="$vServletPath"/>";
			var _vURL 			= "<xsl:value-of select="$vURL"/>";
			var _vCZ 			= "<xsl:value-of select="$vCZ"/>";
			var _vTIDX 			= "<xsl:value-of select="$vTIDX"/>";
			var _envName 		= "<xsl:value-of select=".//FormInformation/envName"/>";
			var _companyCode 		= "<xsl:value-of select=".//FormInformation/companyCode"/>";
			var _ruserId 		= "<xsl:value-of select=".//FormInformation/ruserId"/>";
			var _sessionId 		= "<xsl:value-of select=".//FormInformation/sessionId"/>";
			var _dateFormat 		= "<xsl:value-of select=".//FormInformation/dateFormat"/>";	 
			var _vDesktopColor 	= "<xsl:value-of select=".//FormInformation/bgcolor"/>";
			
			setSessionToken( _sessionId );			
		</script>
		
		<!-- define preload function, can be overrided in specifc page-->
		<script language="javascript">
			//TODO: add description - called when a page is loading
			function preload()  {
				if( this.loading ) {
					loading();
				}
			}
		</script>
		
		<xsl:call-template name="DesktopCSSTmpl">
			<xsl:with-param name="DesktopColor" select="$vDesktopColor"/>
			<xsl:with-param name="includeDatepicker">yes</xsl:with-param>
			<xsl:with-param name="includeSuggest">yes</xsl:with-param>            			        		
		</xsl:call-template>				
				
		<xsl:call-template name="header_callback"/>
	</xsl:template>	
	
</xsl:stylesheet>


