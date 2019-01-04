<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassCopy_ClassListTemplate.xsl"/>

	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">Fund Class Copy</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/FundSetup_ClassCopy.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/FundSetup_ClassCopy.js"></script>		
	</xsl:template>
	
	
	<!-- ========================== PAGE RELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">classPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">600</xsl:with-param>
			<xsl:with-param name="height">215</xsl:with-param>
			<xsl:with-param name="top">75</xsl:with-param>
			<xsl:with-param name="left">200</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="classPopupContents"/></xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >
		
		<div id="main-filter">
			<div id="fromFundDiv">
				<span class="fundLabel">From Fund</span>
				<input suggestField="true" 				      
					style="width:600px;"
					type="text"
					id="fromFundFld"
					size="40"
					dropdownClass="Desktop_suggestDropdown_veryBig"
					contentClass="Desktop_suggestDropdownContent"
					highlightClass="Desktop_suggestDropdownHighlight"
					displayItems="fndDisp"
					searchURLGenerator="getFundOnlySuggestURL"														
					updateCallbackFn="updateHandler_fromFundFld"
					onkeyup="keyupHandler_fromFundFld();" />											
			</div>			
			<input type="button" value="Lookup Class List" id='btnClassLookup' class='Desktop_Btn' onclick='clickHandler_classLookupBtn()' style="float:left; width:140px;"/>
			<div id="copyInfoDiv">
				<div id="copyInfoLabel">Copy Following Class Information</div>
				<div id="copyInfoOptionsDiv">
					<div class="copyInfoOption">
						<input type="checkbox" id="basicInfoCheckbox" checked="true" disabled="true"/>
						<span class="copyInfoOptionLabel">Basic Info</span>
					</div>
					<div class="copyInfoOption">
						<input type="checkbox" id="feeParmsCheckbox"/>
						<span class="copyInfoOptionLabel">Fee Parameters</span>
					</div>
					<div class="copyInfoOption">
						<input type="checkbox" id="shGrpFundsCheckbox"/>
						<span class="copyInfoOptionLabel">Shareholder Group Funds Available</span>
					</div>
					<div class="copyInfoOption">
						<input type="checkbox" id="regTrusteeCheckbox"/>
						<span class="copyInfoOptionLabel">Registered Trustee</span>
					</div>
					<div class="copyInfoOption">
						<input type="checkbox" id="pshipCheckbox"/>
						<span class="copyInfoOptionLabel">Partnership</span>
					</div>
				</div>								
			</div>		
			<div id="toFundDiv">
				<span class="fundLabel">To Fund</span>
				<input suggestField="true" 				      
					style="width:600px;"
					type="text"
					id="toFundFld"
					size="40"
					dropdownClass="Desktop_suggestDropdown_veryBig"
					contentClass="Desktop_suggestDropdownContent"
					highlightClass="Desktop_suggestDropdownHighlight"
					displayItems="fndDisp"
					searchURLGenerator="getFundOnlySuggestURL"														
					updateCallbackFn="updateHandler_toFundFld" />
			</div>
		</div>
		<!--#main-targetbox-->
		<div id="main-targetbox">
			<div id="excludeAllDiv">
				<input type="checkbox" id="excludeAllCheckbox" onclick="clickHandler_excludeAllCheckbox( this )"/>Exclude All
			</div>
			<div id="ClassList_TableDiv" class="Desktop_TableDiv" style="overflow-y:scroll;">
				<xsl:call-template name="ClassList_Tmpl"/>
			</div>	
		</div>
		<!--#mainer-btnline-->
		<div id="main-btnline" align="right">
			<span style="padding-right:10px;">										
				<input type="button" value="Add" id='btnClassAdd' class='Desktop_Btn' onclick='clickHandler_addBtn();'/>			
				<input type="button" value="Modify" id='btnClassModify' class='Desktop_Btn'  onclick='clickHandler_modifyBtn()'/>			
			</span>
			<span>
				<input type="button" value="Clear All" id='btnClearAll' class='Desktop_Btn'  onclick='clickHandler_clearAllBtn()'/>				
			</span>
		</div>
		<div id="main-closebtnline" align="center">
			<input type="button" value="OK" id='btnClassClose' class='Desktop_Btn' onclick="clickHandler_okBtn();"/>
			<input type="button" value="" style="display:none" name="btnOK" id="btnOK"/>
			<input type="button" value="Cancel" id='btnClassClose' class='Desktop_Btn' onclick="clickHandler_cancelBtn();"/>
			<input type="button" value="" style="display:none" name="btnCancel" id="btnCancel"/>
		</div>			
	</xsl:template>
	
	
	<!-- ========================== POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="classPopupContents">
		<input type="hidden" id="Popup_fundCodeFld" value=""/>
		<div style="width:100%; height:30px; padding:5px;">
			<div style="float:left; width:290px;">
				<span style="width:125px;">From Class</span>
				<input id="Popup_fromClassCodeFld" type="text" style="width:120px;"/>
			</div>
			<div style=" width:290px;">
				<span style="width:125px;">New Class Code</span>
				<input id="Popup_classCodeFld" type="text" style="width:120px;"/>
			</div>
		</div>
		<div style="width:100%; height:30px; padding:5px;">
			<div style="float:left; width:290px;">
				<span style="width:125px;">Effective Date</span>
				<input id="Popup_deffFld" type="text" style="width:120px; position:absolute; left:130px; top:40px;" ifdsDatepicker="true" class="Desktop_Datepicker"/>				  
			</div>
			<div style=" width:290px;">
				<span style="width:125px;">ISIN</span>
				<input id="Popup_isinFld" type="text" style="width:120px;"/>
			</div>
		</div>
		<div style="width:100%; height:30px; padding:5px;">
			<div style="float:left; width:290px; height:30px;">
				<span style="width:125px;">CUSIP</span>
				<input id="Popup_cusipFld" type="text" style="width:120px;"/>
			</div>
			<div style=" width:290px;">
				<span style="width:125px;">WKN Fund ID</span>
				<input id="Popup_wknFld" type="text" style="width:120px;"/>
			</div>
		</div>
		<div style="width:100%; height:30px; padding:5px;">
			<div style="float:left; width:290px;">
				<span style="width:125px;">External Fund ID</span>
				<input id="Popup_extIDFld" type="text" style="width:120px;"/>
			</div>
			<div style=" width:290px;">
				<span style="width:125px;">Fund Load Group</span>
				<input id="Popup_fundLoadGrpFld" type="text" style="width:120px;"/>
			</div>
		</div>
		<div style="width:100%; height:40px; text-align:center; padding-top:5px;">
			<input type="button" value="OK" class='Desktop_Btn' onclick="clickHandler_savePopupBtn()"/>			
			<input type="button" value="Cancel" class='Desktop_Btn' onclick="clickHandler_cancelPopupBtn()"/>			
		</div>						
		
	</xsl:template>
</xsl:stylesheet>