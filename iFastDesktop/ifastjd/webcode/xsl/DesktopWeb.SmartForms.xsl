<!-- 	 
	@file 		DesktopWeb.xsl
	@desc		The master xsl (html) file for all DesktopWeb screens 
	@author		Rod Walker	
	@date      	2010-08-13	
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes" />
	
	<xsl:variable name="vServletPath"  	select="/websrvXML/requestInfo/servletPath"/>
	<xsl:variable name="vClient"       	select="/websrvXML/requestInfo/client"/>	
	<xsl:variable name="vPath"          select="concat( /websrvXML/transformNode/datadir, $vClient, '/' )"/>	
	<xsl:variable name="vScreen"		select="/websrvXML/FormInformation/screen"/>
	<xsl:variable name="vCompanyCode"	select="translate(/websrvXML/FormInformation/companyCode, 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
	
	<xsl:template match="/">
		<HTML_WRAPPER>			
			<xsl:text><![CDATA[<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN"
			   "http://www.w3.org/TR/html4/frameset.dtd">]]></xsl:text>			
			<html>
				<head>
				  	<title>SmartForms: <xsl:value-of select="/websrvXML/SmartFormsDetails/formName"/></title>
					
					<!-- EXT JS CSS -->					
					<link rel="stylesheet" type="text/css" href="{$vPath}extjs/resources/css/ext-all.css"/>
					<link rel="stylesheet" type="text/css" href="{$vPath}extjs/resources/css/xtheme-gray.css"/>							
					
					<!-- DesktopWeb CSS -->
					<link rel="stylesheet" type="text/css" href="{$vPath}css/DesktopWeb.Common.css"/>								
					
					<!-- SmartForms CSS -->
					<link rel="stylesheet" type="text/css" href="{$vPath}css/DesktopWeb.SmartForms.css"/>
					
					<!-- EXT JS Javascript -->								
					<xsl:choose> 
						<xsl:when test="/websrvXML/FormInformation/debug = 'true'">
							<script src="{$vPath}extjs/adapter/ext/ext-base-debug-w-comments.js"></script> <!-- must be loaded first -->					
							<script src="{$vPath}extjs/ext-all-debug-w-comments.js"></script>
						</xsl:when>
						<xsl:otherwise>
							<script src="{$vPath}extjs/adapter/ext/ext-base.js"></script> <!-- must be loaded first -->
							<script src="{$vPath}extjs/ext-all.js"></script>
						</xsl:otherwise>
					</xsl:choose>
					
					<!-- IFDS Javascript -->
					<script>Ext.namespace("IFDS");</script>  <!-- need to define namespace object-->
					<script src="{$vPath}js/IFDS.Xml.js"/>					
					<script src="{$vPath}js/IFDS.SuggestField.js"/>					
									
					
					<!-- DesktopWeb Javascript -->					
					<script src="{$vPath}js/DesktopWeb.js"/>					
					<script>
						// initialize DesktopWeb global variables before loading screen
						DesktopWeb._SERVLET_PATH 	= '<xsl:value-of select="$vServletPath"/>';
						DesktopWeb._SRC_PATH 		= '<xsl:value-of select="$vPath"/>';
						
						DesktopWeb._SCREEN_PARAM_MAP = {};
						<xsl:for-each select=".//FormInformation/*">
							DesktopWeb._SCREEN_PARAM_MAP['<xsl:value-of select="name()"/>'] = '<xsl:value-of select="."/>';
						</xsl:for-each>																		
					</script>	
					<script src="{$vPath}js/DesktopWeb.Util.js"/>	
					<script src="{$vPath}js/DesktopWeb.Translation.js"/>
					<script src="{$vPath}js/DesktopWeb.Controls.js"/>
					<script src="{$vPath}js/DesktopWeb.AdvancedControls.js"/>
					<script src="{$vPath}js/DesktopWeb.Ajax.js"/>
					
					<script src="{$vPath}js/DesktopWeb.SmartForms.js"/>
					<script src="{$vPath}js/smartforms/FormTitlebar.js"/>
					<script src="{$vPath}js/smartforms/FormToolbar.js"/>
					<script src="{$vPath}js/smartforms/PageNavigator.js"/>
					<script src="{$vPath}js/smartforms/ContentViewer.js"/>
					<script src="{$vPath}js/smartforms/FormItems.js"/>
					<script src="{$vPath}js/smartforms/FormDataStore.js"/>							
					<script src="{$vPath}js/smartforms/Bubble.js"/>
					<script src="{$vPath}js/smartforms/Footer.js"/>
					<script src="{$vPath}js/smartforms/APIResponse.js"/>
					<script src="{$vPath}js/smartforms/Notifications.js"/>
					<script src="{$vPath}js/smartforms/AccountLookup.js"/>
					
					<script>
						<xsl:variable name="FORM_NAME" select="/websrvXML/SmartFormsDetails/formName"/>					
						var form = null;
						<xsl:if test="/*//SmartForm">
							form = {
								name: "<xsl:value-of select="/*//FormName"/>"
								,description: "<xsl:value-of select="/*//FormDescription"/>"
								,images: [
									<xsl:for-each select="/*//SmartForm/FormBackground/ImageDetails/Image">
										{										
											uri: "<xsl:value-of select="$vPath"/>smartforms/images/<xsl:value-of select="$vCompanyCode"/>/<xsl:value-of select="fileName"/>", 
											height: <xsl:value-of select="height"/>, 
											width: <xsl:value-of select="width"/>
										}<xsl:if test="position() != last()">,</xsl:if>									
									</xsl:for-each>																																												
								]							
							};
						</xsl:if>
						
						var source = null;						
						<xsl:if test="/*//AWDWorkDetails/status and /*//AWDWorkSource/ImageDetails and /*//SmartForm">																		
							source = {
								createDateTime: "<xsl:value-of select="/*//AWDWorkDetails/createTime"/>"
								,businessArea: "<xsl:value-of select="/*//AWDWorkDetails/businessArea"/>"
								,status: "<xsl:value-of select="/*//AWDWorkDetails/status"/>"
								,workType: "<xsl:value-of select="/*//AWDWorkDetails/workType"/>"
								,images: [															
									<xsl:for-each select="/*//AWDWorkSource/ImageDetails/Image">
										{
											<xsl:variable name="formImageHeight" select="/*//SmartForm/FormBackground/ImageDetails/Image[position()]/height"/>
											<xsl:variable name="formImageWidth" select="/*//SmartForm/FormBackground/ImageDetails/Image[position()]/width"/>									 
											uri: "<xsl:value-of select="concat($vServletPath, '?cz=', /*//FormInformation/cz, '&amp;jobname=GetAFTImage&amp;')"/><xsl:value-of select="concat('sourceValue=', url, '&amp;sourceWidth=', $formImageWidth, '&amp;sourceHeight=', $formImageHeight)"/>"
											,width: form.images[0].width
											,height: form.images[0].height																				
										}<xsl:if test="position() != last()">,</xsl:if>										
									</xsl:for-each>																													
								]	
							};						
						</xsl:if>						
						
						var formLayout = {};
						formLayout.pages = [];
						<xsl:for-each select="/*//SmartForm/FormLayout/Pages/Page">
							<xsl:variable name="PAGE_INDEX" select="position() - 1"/>
							formLayout.pages[<xsl:value-of select="$PAGE_INDEX"/>] = {};
							formLayout.pages[<xsl:value-of select="$PAGE_INDEX"/>].sections = [];
														
							<xsl:for-each select="Sections/Section">
								<xsl:variable name="SECTION_INDEX" select="position() - 1"/>
								formLayout.pages[<xsl:value-of select="$PAGE_INDEX"/>].sections[<xsl:value-of select="$SECTION_INDEX"/>] = {};
								formLayout.pages[<xsl:value-of select="$PAGE_INDEX"/>].sections[<xsl:value-of select="$SECTION_INDEX"/>].height = <xsl:value-of select="height"/>;
								formLayout.pages[<xsl:value-of select="$PAGE_INDEX"/>].sections[<xsl:value-of select="$SECTION_INDEX"/>].top = <xsl:value-of select="top"/>;								
								formLayout.pages[<xsl:value-of select="$PAGE_INDEX"/>].sections[<xsl:value-of select="$SECTION_INDEX"/>].controls = [];
															
								<xsl:for-each select="Controls/Control">
									<xsl:variable name="CONTROL_INDEX" select="position() - 1"/>
									
									formLayout.pages[<xsl:value-of select="$PAGE_INDEX"/>].sections[<xsl:value-of select="$SECTION_INDEX"/>].controls[<xsl:value-of select="$CONTROL_INDEX"/>] = {
										<xsl:for-each select="*">
											<xsl:choose>
												<xsl:when test="name(.) = 'value'">
													value: "<xsl:value-of select="."/>"
												</xsl:when>
												<xsl:when test="name(.) = 'apiValue'">
													apiValue: "<xsl:value-of select="."/>"
												</xsl:when>
												<xsl:when test="string(number(.)) = 'NaN'">
													<xsl:value-of select="name(.)"/>: "<xsl:value-of select="."/>"
												</xsl:when>
												<xsl:otherwise>
													<xsl:value-of select="name(.)"/>: <xsl:value-of select="number(.)"/>
												</xsl:otherwise>
											</xsl:choose>												
											<xsl:if test="position() != last()">, </xsl:if>
										</xsl:for-each>
									};	
									
								</xsl:for-each>
							</xsl:for-each>
						</xsl:for-each>
						
						var altFormList = [
							<xsl:for-each select="//FormList/form[. != $FORM_NAME]">								
								["<xsl:value-of select="."/>"]<xsl:if test="position() != last()">,</xsl:if>	
							</xsl:for-each>
						];

						var API = {};
					</script>
					
					<!-- API mapping JSON files -->
					<xsl:if test="/*//SmartForm">
						<xsl:for-each select="/*//SmartForm/APIs/API">
							<xsl:variable name="API_NAME" select="name"/>							
							<xsl:choose>
								<xsl:when test="/*//AWDWorkDetails/workType">
									<xsl:variable name="AWD_WORK_TYPE" select="/*//AWDWorkDetails/workType"/>
									<xsl:for-each select="applicableWorkAreas/workArea">
										<xsl:variable name="WORK_AREA" select="."/>
										<xsl:if test="contains($AWD_WORK_TYPE, $WORK_AREA)">
											<xsl:element name="script">
												<xsl:attribute name="src"><xsl:value-of select="$vPath"/>smartforms/api_mappings/<xsl:value-of select="$API_NAME"/>.js</xsl:attribute>							
											</xsl:element>
										</xsl:if>
									</xsl:for-each>
								</xsl:when>
								<xsl:otherwise>
									<xsl:element name="script">
										<xsl:attribute name="src"><xsl:value-of select="$vPath"/>smartforms/api_mappings/<xsl:value-of select="name"/>.js</xsl:attribute>							
									</xsl:element>
								</xsl:otherwise>
							</xsl:choose>																
						</xsl:for-each>
					</xsl:if>
					
					<xsl:if test="/*//SmartForm/JSCode">
						<script>
							<xsl:copy-of select="/*//SmartForm/JSCode/text()"/>
						</script>
					</xsl:if>
											
					<script>																		
						Ext.onReady(function(){SmartFormsApp.load(API, form, source, formLayout, altFormList);});
					</script>	
																																								
				</head>
				<body>
					<div id="DesktopWeb-Processing-Mask"></div>					
					<div id="DesktopWeb-Processing">						
						<div class="DesktopWeb-Processing-Message">							
						</div>
					</div>
					
				  	<input type="button" name="btnConfirmDlg" id="btnConfirmDlg" style="display:none;"/>
					<input type="button" name="btnCancel" id="btnCancel" style="display:none;"/>
				</body>
			</html>
		</HTML_WRAPPER>
	</xsl:template>
		
</xsl:stylesheet>
<!-- eof -->