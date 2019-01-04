<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	
	<xsl:variable name="SCREEN_NAME">TradeConf</xsl:variable>
	
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
		
		<div id="TradeConfContentsDiv">
		
			<div class="EntryScreenSectionDiv">
				<div class="SimpleSectionContentsDiv">
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_med">Wire Order Allowed</span>
						<span class="fldCheckboxSpan">
							<input type="checkbox" xpath="TradeConfiguration/wireElig"/>								
						</span>
						
						<span class="fldLabelSpan_med">Order Type</span>
						<span class="fldValueSpan_med">
							<select class="fld_med" xpath="TradeConfiguration/ordType" descXpath="TradeConfiguration/ordTypeDesc">
								<xsl:call-template name="List_tmpl">
									<xsl:with-param name="id">OrdTypeList</xsl:with-param>
								</xsl:call-template>
							</select>
						</span>
					</div>
				</div>
					
			</div>
								
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Eligibility
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							
							<span class="fldLabelSpan_med">RRSP</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/ClassEligibility/rrsp"/>								
							</span>
							
							<span class="fldLabelSpan_lrg">RRIF</span>							
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/ClassEligibility/rrif" />								
							</span>
							
							<span class="fldLabelSpan_lrg">EsoP</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox"  xpath="TradeConfiguration/ClassEligibility/esop"/>								
							</span>
							
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">NSC Compliant</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox"  xpath="TradeConfiguration/ClassEligibility/nscCompliant"/>								
							</span>						
							
							<span class="fldLabelSpan_lrg">CSS Correction</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox"  xpath="TradeConfiguration/ClassEligibility/cssErrCorr"/>								
							</span>
							
							<span class="fldLabelSpan_lrg">AMS</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox"  xpath="TradeConfiguration/ClassEligibility/ams"/>							
							</span>
														
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Margin Allowed</span>
							<span class="fldCheckboxSpan">								
								<input type="checkbox"  xpath="TradeConfiguration/ClassEligibility/marginAllowed"/>							
							</span>
							<span class="fldLabelSpan_lrg">Rollover Allowed</span>
							<span class="fldCheckboxSpan">								
								<input type="checkbox"  xpath="TradeConfiguration/ClassEligibility/freeRoll"/>							
							</span>																
						</div>
						<div class="FieldRowDiv">													
							<span class="fldLabelSpan_lrg">Eligible ICT In</span>
							<span class="fldValueSpan_med">
								<select id="eligICTInFld" class="fld_med" xpath="TradeConfiguration/ClassEligibility/eligICTIn" descXpath="TradeConfiguration/ClassEligibility/eligICTInDesc" mandatory="true">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">EligICTInList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
							
							<span class="fldLabelSpan_med">Eligible ICT Out</span>
							<span class="fldValueSpan_med">
								<select id="eligICTOutFld" class="fld_med" xpath="TradeConfiguration/ClassEligibility/eligICTOut" descXpath="TradeConfiguration/ClassEligibility/eligICTOutDesc" mandatory="true">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">EligICTOutList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Rollover Details
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Fund</span>
							<span class="fldValueSpan_xlrg">
								<select class="fld_xlrg" xpath="TradeConfiguration/ClassEligibility/freeRollFund" descXpath="TradeConfiguration/ClassEligibility/freeRollFundDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">Funds</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>		
							<span class="fldLabelSpan_sml">Class</span>
							<span class="fldValueSpan_sml">
								<select class="fld_med" xpath="TradeConfiguration/ClassEligibility/freeRollCl" descXpath="TradeConfiguration/ClassEligibility/freeRollClDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">ClassList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Amount Type</span>
							<span class="fldValueSpan_xlrg">
								<select class="fld_lrg" xpath="TradeConfiguration/ClassEligibility/freeRollPUD" descXpath="TradeConfiguration/ClassEligibility/freePUDDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">PUDList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
							
							<span class="fldLabelSpan_sml">Qual. Period</span>
							<span class="fldValueSpan_lrg">
								<input type="text" class="fld_med" xpath="TradeConfiguration/ClassEligibility/freeRollQualPrd">
								</input>
							</span>				
						</div>
					</div>
				</div>
			</div>
				
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Stop Flags
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Stop Comm. Rebate</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/commRebStop"/>							
							</span>
							
							<span class="fldLabelSpan_lrg">Stop PAC</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/pacStop"/>							
							</span>
							
							<span class="fldLabelSpan_lrg">Stop SWP</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/swpStop"/>							
							</span>
																				
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Stop Purchase</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/purStop"/>							
							</span>
							
							<span class="fldLabelSpan_lrg">Stop Redeem</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/redStop"/>							
							</span>
							
							<span class="fldLabelSpan_lrg">Stop Auto Transfer Out</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/autoXferOutStop"/>							
							</span>
							
						</div>		
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Stop Auto Transfer In</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/autoXferInStop"/>							
							</span>
							
							<span class="fldLabelSpan_lrg">Stop Transfer Out</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/xferOutStop"/>							
							</span>
							
							<span class="fldLabelSpan_lrg">Stop Transfer In</span>
							<span class="fldCheckboxSpan">
								<input type="checkbox" xpath="TradeConfiguration/StopFlags/xferInStop"/>							
							</span>							
						</div>				
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Purchase Min Amounts
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_lrg">Min Initial Amount</span>
							<span class="fldValueSpan_med">
								<input id="minInitFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/minInit">
								</input>
							</span>
							<span class="fldLabelSpan_med">Min Subsequent Amount</span>
							<span class="fldValueSpan_med">
								<input id="minSubFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/minSub">
								</input>
							</span>
							
						</div>						
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Redemption Min Amounts
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_lrg">Min Initial Amount</span>
							<span class="fldValueSpan_med">
								<input id="redMinInitFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/redMinInit">
								</input>
							</span>
							
							<span class="fldLabelSpan_med">Min Subsequent Amount</span>
							<span class="fldValueSpan_med">
								<input id="redMinSubFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/redMinSub">
								</input>
							</span>
						</div>						
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Systematic Min Amounts
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_lrg">PAC Min Amount</span>
							<span class="fldValueSpan_med">
								<input id="pacMinFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/pacMin">
								</input>
							</span>
							
							<span class="fldLabelSpan_med">SWP Min Amount</span>
							<span class="fldValueSpan_med">
								<input id="swpMinFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/swpMin">
								</input>
							</span>						
						</div>							
					</div>										
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Min Balance Amounts
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_lrg">Min Fund Class Balance</span>
							<span class="fldValueSpan_med">
								<input id="minFundClBalFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/minFundClBal">
								</input>
							</span>
							
							<span class="fldLabelSpan_med">Min Account Balance</span>
							<span class="fldValueSpan_med">
								<input id="minAcctBalFld" type="text" class="fld_med" xpath="TradeConfiguration/MinMaxAmounts/minAcctBal">
								</input>
							</span>						
						</div>						
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background">
						Calculation Methods
					</div>
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Purchase Aging Rule</span>
							<span class="fldValueSpan_lrg">
								<select class="fld_med" xpath="TradeConfiguration/CalcMethods/purAgingRule" descXpath="TradeConfiguration/CalcMethods/purAgingRuleDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">PurAgingRuleList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>							
							<span class="fldLabelSpan_med">Partnership Unit Assign.</span>
							<span class="fldValueSpan_med">
								<select id="pShipUnitAsmtFld" class="fld_med" xpath="TradeConfiguration/CalcMethods/pShipUnitAsmt" descXpath="TradeConfiguration/CalcMethods/pShipUnitAsmtDesc" mandatory="true">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">PShipUnitAsmtList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>		
													
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Free Consolidation</span>
							<span class="fldValueSpan_lrg">
								<select id="freeConsolFld" class="fld_lrg" xpath="TradeConfiguration/CalcMethods/freeConsol" descXpath="TradeConfiguration/CalcMethods/freeConsolDesc" mandatory="true">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">FreeConsolList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
							<span class="fldLabelSpan_med">Gain/Loss Method</span>
							<span class="fldValueSpan_med">
								<select id="gainLossMthdFld" class="fld_med" xpath="TradeConfiguration/CalcMethods/gainLossMthd" descXpath="TradeConfiguration/CalcMethods/gainLossMthdDesc" mandatory="true">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">GainLossMthdList</xsl:with-param>
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
</xsl:stylesheet>