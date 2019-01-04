<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	
	<xsl:variable name="SCREEN_NAME">PriceInfo</xsl:variable>
	
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
			
			_fundListsMap = {};
			<xsl:for-each select="/websrvXML/CACHE_DATA/Lists/List[@id = 'FundList']/Element">
				_fundListsMap["<xsl:value-of select="code"/>"] = "<xsl:value-of select="value"/>";
			</xsl:for-each>
		</script>		
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">settleCurrencyPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">630</xsl:with-param>
			<xsl:with-param name="height">40</xsl:with-param>
			<xsl:with-param name="top">100</xsl:with-param>
			<xsl:with-param name="left">100</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="SettleCurrencyPopupContents_tmpl"/></xsl:with-param>			
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
		
		
		<div id="PriceInfoContentsDiv">
			<div class="EntryScreenSectionDiv">
				<div class="SimpleSectionContentsDiv">
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">NAV Currency</span>
						<span class="fldValueSpan_med">
							<select class="fld_med" id="currencyFld" xpath="PriceInfo/currency" mandatory="true">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="id">CurrencyList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>
					</div>
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">Valid Settle Currency</span>
						<span class="fldValueSpan_xlrg"> 
							<input id="validSettleCurrFld" type="text" class="fld_lrg"  xpath="PriceInfo/validSettleCurr" disabled="true">
							</input>
							<input type="button" value="Edit" class="editBtn" onclick="clickHandler_editSettleCurrencyBtn()"/>						
						</span>
					</div>
					<div class="FieldRowDiv">
						
						<span class="fldLabelSpan_med">Custom Valuation</span>
						<span class="fldValueSpan_lrg">
							<select class="fld_med" xpath="PriceInfo/schedTransType" descXpath="PriceInfo/schedTransTypeDesc">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="id">SchedTransTypeList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>
						
						<span class="fldLabelSpan_med">ESG Price Suppress</span>
						<span class="fldValueSpan_med">
							<input type="checkbox" xpath="PriceInfo/esgPriceSuppress"/>								
						</span>																
					</div>
					
				</div>											
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:33px;">
						NAV
					</div>	
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Fixed Price</span>
							<span class="fldValueSpan_med">
								<input type="checkbox" xpath="PriceInfo/fixPrice"/>								
							</span>
														
							<span class="fldLabelSpan_med">Fixed Rate</span>
							<span class="fldValueSpan_med">
								<input id="fixedRateFld" type="text" class="fld_med"  xpath="PriceInfo/fixRate" mandatory="true">
								</input>
							</span>
							
							<span class="fldLabelSpan_sml">Precision</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml"  xpath="PriceInfo/ratePrecision">
								</input>
							</span>
						</div>	
											
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Variance Amount</span>
							<span class="fldValueSpan_med">
								<input type="text" class="fld_med" xpath="PriceInfo/priceVarAmt">
								</input>
							</span>
							
							<span class="fldLabelSpan_med">Variance Type</span>
							<span class="fldValueSpan_lrg">
								<select class="fld_med" xpath="PriceInfo/priceVarType" descXpath="PriceInfo/priceVarTypeDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">PriceVarTypeList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>	
						
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Load Group</span>
							<span class="fldValueSpan_lrg">
								<select class="fld_med" xpath="PriceInfo/loadGrp">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">FundLoadGrpList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>
												
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:33px;">
						Unit
					</div>	
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Calculation Method</span>
							<span class="fldValueSpan_lrg">
								<select class="fld_lrg" xpath="PriceInfo/unitsCalc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">UnitCalcList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						
							<span class="fldLabelSpan_med">Precision</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" id="unitsPrecisionFld" xpath="PriceInfo/unitsPrecision" mandatory="true">
								</input>
							</span>
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Fractional Shares</span>
							<span class="fldValueSpan_lrg">
								<input type="checkbox" xpath="PriceInfo/fractionalShr"/>								
							</span>
							
							<span class="fldLabelSpan_med">Allocated Type</span>
							<span class="fldValueSpan_med">
								<select class="fld_med" xpath="PriceInfo/allocType" descXpath="PriceInfo/allocTypeDesc">
										<xsl:call-template name="List_tmpl">
											<xsl:with-param name="id">AllocTypeList</xsl:with-param>
										</xsl:call-template>
								</select>														
							</span>
						</div>						
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
	
	<!-- ========================== SETTLE CURRENCY POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="SettleCurrencyPopupContents_tmpl">
		
		<div style="padding:10px;">	
						
			<xsl:for-each select="/websrvXML/CACHE_DATA/Lists/List[@id='CurrencyList']/Element[string-length(code) &gt; 0]">
				<xsl:if test="position() mod 3 = 1">
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med"><xsl:value-of select="value"/></span>
						<span class="fldValueCheckbox">
							<input type="checkbox" name="currencyCheckbox">
								<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
								<xsl:attribute name="onclick"><xsl:if test="code='*'">clickHandler_allCurrCheckbox( this )</xsl:if></xsl:attribute>
							</input>
						</span>
						
						<xsl:if test="following-sibling::Element[1]">
							<span class="fldLabelSpan_med"><xsl:value-of select="following-sibling::Element[1]/value"/></span>
							<span class="fldValueCheckbox">
								<input type="checkbox" name="currencyCheckbox">
									<xsl:attribute name="value"><xsl:value-of select="following-sibling::Element[1]/code"/></xsl:attribute>
								</input>
							</span>
						</xsl:if>
						
						<xsl:if test="following-sibling::Element[2]">
							<span class="fldLabelSpan_med"><xsl:value-of select="following-sibling::Element[2]/value"/></span>
							<span class="fldValueCheckbox">
								<input type="checkbox" name="currencyCheckbox">
									<xsl:attribute name="value"><xsl:value-of select="following-sibling::Element[2]/code"/></xsl:attribute>
								</input>
							</span>
						</xsl:if>
					</div>
				</xsl:if>
			</xsl:for-each>
			
			
			<div style="padding-top:10px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn" onclick="clickHandler_settleCurrencyPopupOKBtn()"/>
				<input type="button" value="Cancel" class="Desktop_Btn" onclick="clickHandler_settleCurrencyPopupCancelBtn()"/>
			</div>
		</div>		
	</xsl:template>
</xsl:stylesheet>