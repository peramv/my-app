<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/GrantContrib_DataTemplate.xsl"/>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">Grant Contributions</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/GrantContrib.css" rel="stylesheet" type="text/css" />
		<script src="{$vURL}javascript/GrantContrib.js"/>
		
		<script>
			_accountNum = "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>";
			_respBenId = "<xsl:value-of select="/websrvXML/FormInformation/RESPBenID"/>";
			_reasonCode = "<xsl:value-of select="/websrvXML/FormInformation/ReasonCode"/>";
			_depositType = "<xsl:value-of select="/websrvXML/FormInformation/DepositType"/>";
			_redCode = "<xsl:value-of select="/websrvXML/FormInformation/RedCode"/>";
			
			_moreRecordsExist = ( "<xsl:value-of select="/websrvXML/dtGrantContribReloadResponse/RecordRange/moreRecordsExist"/>" == "yes" );
			
			<xsl:if test="/websrvXML/dtGrantContribReloadResponse/RecordRange/moreRecordsExist = 'yes'">
				_rangeStartForNext = <xsl:value-of select="/websrvXML/dtGrantContribReloadResponse/RecordRange/rangeStartForNext"/>;
			</xsl:if>
			 
		</script>		
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >				
		<div class="ScreenSectionDiv" style="height:237px; margin-top:10px; position:relative;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="overflow:visible; white-space:nowrap; font-weight:bold; text-align:center">
					<xsl:value-of select="/websrvXML/dtGrantContribReloadResponse/GrantContributionInfo/scrTitle"/>					
				</div>
				<div class="FieldSetContentsDiv" style="position:relative">				
					<div id="GrantContrib_TableDiv" class="Desktop_TableDiv" style="height:180px; width:1024px; position:absolute;">
						<xsl:call-template name="GrantContrib_Tmpl">
							<xsl:with-param name="sourceNode" select="/websrvXML/dtGrantContribReloadResponse"/>
						</xsl:call-template>			
					</div>
					<div style="position:absolute; top:200px; width:100%; text-align:right; margin-right:30px;">
						<input type="button" value="More" id="moreBtn" class="Desktop_Btn" onclick="clickHandler_moreBtn()">				
						</input>
					</div>
				</div>
			</div>
		</div>

		
		<div class="ScreenButtonsDiv">
			<input type="button" value="OK" id="btnOK" name="btnOK" class="Desktop_Btn" disabled="true">				
			</input>
			<input type="button" value="Cancel" id="btnCancel" name="btnCancel" class="Desktop_Btn">				
			</input>			
		</div>
	</xsl:template>
	
</xsl:stylesheet>
