<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	
	<xsl:variable name="SCREEN_NAME">TradeDayCtrls</xsl:variable>
	
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
			<div class="EntryScreenSectionDiv" style="height:145px;">
				<div id="AutoForceCancelDaysDiv" class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:162px;">
						Auto Force Cancel Days
					</div>
					<div class="FieldSetContentsDiv" style="text-align:center">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Purchase</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/purAutoCancDays">
								</input>
							</span>
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Redemption</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/redAutoCancDays">
								</input>
							</span>
						</div>		
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Exchange</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/exchAutoCancDays">
								</input>
							</span>
						</div>		
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Transfer</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/tfrAutoCancDays">
								</input>
							</span>
						</div>									
					</div>
				</div>
				
				<div id="CutOffDaysDiv" class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:88px;">
						Cut Off Days
					</div>
					<div class="FieldSetContentsDiv">
						<div>
							<span class="fldLabelSpan_med"></span>
							<span class="fldLabelSpan_sml" style="text-align:left; padding-left:20px;">Days</span>
							<span class="fldLabelSpan_med" style="text-align:left; padding-left:40px;">Day Type</span>
						</div>						
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Purchase</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/CutOffDays/Purchase/numDays">
								</input>
							</span>
							<span class="fldValueSpan_med">
								<select class="fld_med" xpath="TradeDayControls/CutOffDays/Purchase/dayType" descXpath="TradeDayControls/CutOffDays/Purchase/dayTypeDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">DayTypes</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Redemption</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/CutOffDays/Redemption/numDays">
								</input>
							</span>
							<span class="fldValueSpan_med">
								<select class="fld_med" xpath="TradeDayControls/CutOffDays/Redemption/dayType" descXpath="TradeDayControls/CutOffDays/Redemption/dayTypeDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">DayTypes</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>				
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Exchange In</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/CutOffDays/ExchangeIn/numDays">
								</input>
							</span>
							<span class="fldValueSpan_med">
								<select class="fld_med" xpath="TradeDayControls/CutOffDays/ExchangeIn/dayType" descXpath="TradeDayControls/CutOffDays/ExchangeIn/dayTypeDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">DayTypes</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>				
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Exchange Out</span>
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/CutOffDays/ExchangeOut/numDays">
								</input>
							</span>
							<span class="fldValueSpan_med">
								<select class="fld_med" xpath="TradeDayControls/CutOffDays/ExchangeOut/dayType" descXpath="TradeDayControls/CutOffDays/ExchangeOut/dayTypeDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">DayTypes</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>										
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">				
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:115px;">
						Trade Lead Days
					</div>	
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_med">Trade Lead Days</span>			
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/tradeLeadDays">
								</input>
							</span>
							<span class="fldLabelSpan_med">Purchase</span>			
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/tradeLeadDaysPur">
								</input>
							</span>	
							<span class="fldLabelSpan_med">Redemption</span>			
							<span class="fldValueSpan_sml">
								<input type="text" class="fld_sml" xpath="TradeDayControls/tradeLeadDaysRed">
								</input>
							</span>																				
						</div>
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">				
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:95px;">
						Miscellaneous
					</div>	
					<div class="FieldSetContentsDiv center">
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_med">Last Settle Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="lastSetlDateFld" xpath="TradeDayControls/lastSetlDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>
							<span class="fldLabelSpan_lrg">Next Settle Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="nextSetlDateFld" xpath="TradeDayControls/nextSetlDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>																									
						</div>
					
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_med">Last Valuation Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="lastValDateFld" xpath="TradeDayControls/lastValDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>
							<span class="fldLabelSpan_lrg">Next Valuation Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="nextValDateFld" xpath="TradeDayControls/nextValDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>																									
						</div>
					
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_med">Last Cycle Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="lastNRDateFld" xpath="TradeDayControls/lastNR" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>
							<span class="fldLabelSpan_lrg">Next Cycle Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="nextNRDateFld" xpath="TradeDayControls/nextNR" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>																									
						</div>
					
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_med">Last Mgmt. Fee Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="lastMFeeDateFld" xpath="TradeDayControls/lastMFeeDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>
							<span class="fldLabelSpan_lrg">Last Mgmt. Fee Rebate Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="lastMFRDateFld" xpath="TradeDayControls/lastMFRDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>																									
						</div>
						
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_med">NAV Calc. Days</span>			
							<span class="fldValueSpan_med">
								<input type="text" class="fld_med" xpath="TradeDayControls/navCalcDays">
								</input>
							</span>
							<span class="fldLabelSpan_lrg">Payment Lead Days</span>			
							<span class="fldValueSpan_med">
								<input type="text" class="fld_med" xpath="TradeDayControls/pymtLeadDays">
								</input>
							</span>																									
						</div>
						
						<div class="FieldRowDiv">				
							<span class="fldLabelSpan_med">Last Dividend Date</span>			
							<span class="fldValueSpan_med">
								<input type="text" id="lastDivdDateFld" xpath="TradeDayControls/lastDivdDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>
							<span class="fldLabelSpan_lrg"/>			
							<span class="fldValueSpan_med"/>																																							
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
</xsl:stylesheet>