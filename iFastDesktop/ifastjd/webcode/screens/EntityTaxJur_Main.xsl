<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">Entity Tax History</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/EntityTaxJur.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/EntityTaxJur.js"></script>
		
		<script>
			_entityId = "<xsl:value-of select="/websrvXML/FormInformation/entityID"/>";
			_allowAdd = "<xsl:value-of select="/websrvXML/dtEntTaxHistInitResponse/Permissions/addPerm"/>" == "yes";
			_allowMod = "<xsl:value-of select="/websrvXML/dtEntTaxHistInitResponse/Permissions/modPerm"/>" == "yes";
			_allowDel = "<xsl:value-of select="/websrvXML/dtEntTaxHistInitResponse/Permissions/delPerm"/>" == "yes";
			
		</script>
		
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">TaxJurPopup</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">400</xsl:with-param>
			<xsl:with-param name="height">140</xsl:with-param>
			<xsl:with-param name="top">55</xsl:with-param>
			<xsl:with-param name="left">228</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="TaxJurPopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >		
		<div class="ScreenSectionDiv" style="height:300px;">								
			<div id="TaxJur_TableDiv" class="Desktop_TableDiv" style="height:250px; width:842px; position:absolute;">
				<table id="TaxJur_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" rowSelectable="true" cellpadding="0" cellspacing="0" scrollable="true" resizable="true">
					<thead>
						<tr>															
							<td>
								<xsl:attribute name="style">width:80</xsl:attribute>
								<xsl:attribute name="columnWidth">80</xsl:attribute>
								Tax Year
							</td>
							<td>
								<xsl:attribute name="style">width:200</xsl:attribute>
								<xsl:attribute name="columnWidth">200</xsl:attribute>
								Tax Jurisdiction
							</td>
							<td>
								<xsl:attribute name="style">width:100</xsl:attribute>
								<xsl:attribute name="columnWidth">100</xsl:attribute>
								Eff. Date
							</td>	
							<td>
								<xsl:attribute name="style">width:100</xsl:attribute>
								<xsl:attribute name="columnWidth">100</xsl:attribute>
								Created On
							</td>	
							<td>
								<xsl:attribute name="style">width:120</xsl:attribute>
								<xsl:attribute name="columnWidth">120</xsl:attribute>
								Created By
							</td>	
							<td>
								<xsl:attribute name="style">width:100</xsl:attribute>
								<xsl:attribute name="columnWidth">100</xsl:attribute>
								Mod. Date
							</td>																						
							<td>
								<xsl:attribute name="style">width:120</xsl:attribute>
								<xsl:attribute name="columnWidth">120</xsl:attribute>
								Modified By
							</td>							
						</tr>
					</thead>
					<tbody>
						<xsl:for-each select="/websrvXML/dtEntTaxHistInitResponse/EntityTaxJurisInfo/EntityTaxJurisDetail">
							<tr>
								<xsl:attribute name="taxJuris"><xsl:value-of select="taxJuris"/></xsl:attribute>
								<xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
								<xsl:attribute name="entTaxHistID"><xsl:value-of select="entTaxHistID"/></xsl:attribute>
								<xsl:attribute name="runMode"/>
								<xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
								<xsl:attribute name="allowUpd"><xsl:value-of select="allowUpd"/></xsl:attribute>
								<xsl:attribute name="allowDel"><xsl:value-of select="allowDel"/></xsl:attribute>
								
								<td><xsl:value-of select="taxyr"/></td>
								<td><xsl:value-of select="taxJuris"/> - <xsl:value-of select="taxDesc"/></td>								
								<td><xsl:value-of select="effDate"/></td>
								<td><xsl:value-of select="procDate"/></td>
								<td><xsl:value-of select="username"/></td>
								<td><xsl:value-of select="modDate"/></td>																										
								<td><xsl:value-of select="modUser"/></td>
																
							</tr>
						</xsl:for-each>
					</tbody>					
				</table>
			</div>
			<div class="ActionButtonsDiv">		
				<input type="button" value="Add" id='AddBtn' class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_addBtn()</xsl:attribute>
				</input>											
				<input type="button" value="Modify" id='ModBtn' class="Desktop_Btn" disabled='true'>
					<xsl:attribute name="onclick">clickHandler_modBtn()</xsl:attribute>
				</input>																								
				<input type="button" value="Delete" id='DelBtn' class="Desktop_Btn" disabled='true'>
					<xsl:attribute name="onclick">clickHandler_delBtn()</xsl:attribute>
				</input>
			</div>				
		</div>	
		
		
	
		
		<div class="ScreenButtonsDiv">
			<input type="button" value="OK" id="btnOK" name="btnOK" class="Desktop_Btn">				
			</input>
			<input type="button" value="Cancel" id="btnCancel" name="btnCancel" class="Desktop_Btn">				
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
	
	<!-- ========================== TAX JUR POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="TaxJurPopupContents_tmpl">
				
		<div style="padding:10px;">
			<input type="hidden" id="TaxJurPopup_runModeFld"/>
			<div class="SectionRowDiv" id="deleteConfirmationDiv" style="text-align:center">
				<span style="font-weight:bold">Are you sure you wish to delete this record?</span>
			</div>				
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">Tax Jurisdiction:</span>
				<span class="FldValueSpan">
					<select class="FldInput" style="width:220px" id="TaxJurPopup_taxJurFld">
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">TaxJurisList</xsl:with-param>
						</xsl:call-template>
					</select>
				</span>
			</div>
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">Effective Date:</span>
				<span class="FldValueSpan" style="position:relative;">
					<input id="TaxJurPopup_effDateFld" ifdsDatepicker="true" class="Desktop_Datepicker FldInput dateFld" valueSetCallback="changeHandler_taxJurPopupEffDateFld()">
						
					</input>
				</span>
			</div>
			<div style="padding-top:20px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_TaxJurPopupOKBtn()</xsl:attribute>
				</input>				
				<input type="button" value="Cancel" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_TaxJurPopupCancelBtn()</xsl:attribute>
				</input>
			</div>
		</div>		
	</xsl:template>
	
</xsl:stylesheet>