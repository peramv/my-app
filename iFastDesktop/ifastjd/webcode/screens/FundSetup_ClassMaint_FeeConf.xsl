<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	
	<xsl:variable name="SCREEN_NAME">FeeConf</xsl:variable>
	
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
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">feeScalePopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">590</xsl:with-param>
			<xsl:with-param name="height">160</xsl:with-param>
			<xsl:with-param name="top">440</xsl:with-param>
			<xsl:with-param name="left">155</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="FeeScalePopupContents_tmpl"/></xsl:with-param>			
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
		
		
		<div id="FeeConfContentsDiv">
			<div class="EntryScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:75px;">
						Trailer Fee
					</div>	
					<div class="FieldSetContentsDiv">					
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Trailer Fee Date</span>
							<span class="fldValueSpan_med">
								<input type="text" id="trlFeeDateFld" xpath="FeeConfiguration/trlFeeDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>
							
							<span class="fldLabelSpan_lrg">Trailer Fee GrandFather Date</span>
							<span class="fldValueSpan_med">
								<input type="text" id="trlFeeGrandFathDateFld" xpath="FeeConfiguration/trlGrandFathDate" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
								</input>
							</span>
						</div>
					</div>
				</div>
			</div>
				
			<div class="EntryScreenSectionDiv">			
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:91px;">
						Maturity Days
					</div>	
					<div class="FieldSetContentsDiv">					
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Early Maturity Days</span>
							<span class="fldValueSpan_med">
								<input type="text" class="fld_sml" xpath="FeeConfiguration/earlyMatDays">
								</input>
							</span>
							
							<span class="fldLabelSpan_lrg">Short-Term Trading Maturity Days</span>
							<span class="fldValueSpan_med">
								<input type="text" class="fld_sml" xpath="FeeConfiguration/sttrMatDays">
								</input>
							</span>
						</div>
					</div>
				</div>
			</div>	
			
			
			<div class="EntryScreenSectionDiv">				
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:90px;">
						Transfer Fee
					</div>	
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Applicable</span>
							<span class="fldValueCheckbox">
								<input type="checkbox" xpath="FeeConfiguration/tfrFee">								
								</input>
							</span>
							
							<span class="fldLabelSpan_med">Tfr. Fee Type</span>
							<span class="fldValueSpan_sml">
								<select id="tfrFeeTypeFld" class="fld_sml" xpath="FeeConfiguration/tfrFeeType" descXpath="FeeConfiguration/tfrFeeTypeDesc" mandatory="true">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">FeeTypeList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
							
							<span class="fldLabelSpan_med">Tfr. Rate</span>
							<span class="fldValueSpan_med">
								<input id="tfrFeeRateFld" type="text" class="fld_med" xpath="FeeConfiguration/tfrFeeRate" mandatory="true">																	
								</input>
							</span>							
							
						</div>
						<div class="FieldRowDiv">	
							<span class="fldLabelSpan_med">Tfr. Based On</span>
							<span class="fldValueSpan_lrg">
								<select id="tfrBasedOnFld" class="fld_lrg" xpath="FeeConfiguration/tfrBasedOn" mandatory="true">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">BasedOnBELTFRList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
							<span class="fldLabelSpan_sml">Tfr. Paid</span>
							<span class="fldValueSpan_lrg">
								<select id="tfrBasedOnFld" class="fld_lrg" xpath="FeeConfiguration/howPaid">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">HowPaidList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>		
					</div>
				</div>
			</div>
				
			<div class="EntryScreenSectionDiv" style="height:82px;">				
				<div class="FieldSetDiv" style="width:540px; position:absolute; left:0px; top:0px;">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:118px;">
						Management Fee
					</div>	
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Applicable</span>
							<span class="fldValueSpan_sml">
								<input type="checkbox" xpath="FeeConfiguration/mgmtFee">								
								</input>
							</span>
							
							<span class="fldLabelSpan_sml">Pay Option</span>
							<span class="fldValueSpan_med">
								<select class="fld_med" xpath="FeeConfiguration/mgmtFeePayOpt" descXpath="FeeConfiguration/mgmtFeePayOptDesc">
									<xsl:call-template name="List_tmpl">
										<xsl:with-param name="id">MgmtFeePayOptionList</xsl:with-param>
									</xsl:call-template>
								</select>
							</span>
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Broker</span>
							<span class="fldValueSpan_sml">
								<input type="checkbox" xpath="FeeConfiguration/mgmtFeeBroker">								
								</input>
							</span>
							
							<span class="fldLabelSpan_sml">Broker Chg.</span>
							<span class="fldValueSpan_sml">
								<input type="checkbox" xpath="FeeConfiguration/mgmtFeeBrokChg">								
								</input>
							</span>
						</div>		
					</div>
				</div>
				<div class="FieldSetDiv" style="width:345px; position:absolute; top:0px; left:555px;">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:167px;">
						Management Fee Rebate
					</div>	
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_sml">Applicable</span>
							<span class="fldValueSpan_sml">
								<input type="checkbox" xpath="FeeConfiguration/mfrRebate">								
								</input>
							</span>
						</div>
					</div>
				</div>				
			</div>
			
			<div class="EntryScreenSectionDiv">				
				
			</div>
			
			<xsl:variable name="loadType">
				<xsl:choose>
					<xsl:when test="$ADD_MODE = 'true'">
						<xsl:value-of select="/websrvXML/CACHE_DATA/UpdatedClassData/ClassBasic/loadType"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="websrvXML/CACHE_DATA/ClassData/ClassBasic/loadType"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			
			<!-- Display Front End Load for loadType = FEL -->
			<xsl:if test="$loadType = 'FEL'">
				<div class="EntryScreenSectionDiv" id="FrontEndLoadDiv">				
					<div class="FieldSetDiv">
						<div class="FieldSetLabelDiv Desktop_Background" style="width:105px;">
							Front End Load
						</div>	
						<div class="FieldSetContentsDiv">
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med">Acquisit'n Fee Type</span>
								<span class="fldValueSpan_med">
									<select id="felFeeTypeFld" class="fld_sml" xpath="FeeConfiguration/FrontEndLoad/feeType" descXpath="FeeConfiguration/FrontEndLoad/feeTypeDesc" mandatory="true" onchange="changeHandler_felFeeTypeFld()">
										<xsl:call-template name="List_tmpl">
											<xsl:with-param name="id">FeeTypeList</xsl:with-param>
										</xsl:call-template>
									</select>
								</span>
								<span class="fldLabelSpan_med">Acquisit'n Paid</span>
								<span class="fldValueSpan_lrg">
									<select class="fld_lrg" xpath="FeeConfiguration/FrontEndLoad/howPaid" descXpath="FeeConfiguration/FrontEndLoad/howPaidDesc">
										<xsl:call-template name="List_tmpl">
											<xsl:with-param name="id">HowPaidList</xsl:with-param>
										</xsl:call-template>
									</select>	
								</span>
							</div>
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med">Acquisit'n Rate</span>
								<span class="fldValueSpan_med">
									<input id="felRateFld" type="text" class="fld_med" mandatory="true" xpath="FeeConfiguration/FrontEndLoad/rate">
									</input>
								</span>										
								<span class="fldLabelSpan_med">Acquisit'n Based On</span>
								<span class="fldValueSpan_lrg">
									<select id="felBasedOnFld" class="fld_lrg" xpath="FeeConfiguration/FrontEndLoad/basedOn" descXpath="FeeConfiguration/FrontEndLoad/basedOnDesc" mandatory="true">
										<xsl:call-template name="List_tmpl">
											<xsl:with-param name="id">BasedOnList</xsl:with-param>
										</xsl:call-template>
									</select>	
								</span>										
							</div>									
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med">Max. Fee Rate</span>
								<span class="fldValueSpan_med">
									<input id="felMaxRateFld" type="text" class="fld_med" xpath="FeeConfiguration/FrontEndLoad/maxRate" mandatory="true">
									</input>
								</span>
								<span class="fldLabelSpan_med">Min. Fee Rate</span>
								<span class="fldValueSpan_lrg">
									<input id="felMinRateFld" type="text" class="fld_med" xpath="FeeConfiguration/FrontEndLoad/minRate" mandatory="true">
									</input>
								</span>							
							</div>
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med">Withhold Rate</span>
								<span class="fldValueSpan_med">
									<input type="text" class="fld_med" xpath="FeeConfiguration/FrontEndLoad/withHoldRate">
									</input>
								</span>											
							</div>										
						</div>
					</div>
				</div>
			</xsl:if>
			
			<!-- display Backend Load for all load types except FEL and NOL -->
			<xsl:if test="$loadType != 'FEL' and $loadType != 'NOL'">
				<div class="EntryScreenSectionDiv" id="BackEndLoadDiv">				
					<div class="FieldSetDiv">
						<div class="FieldSetLabelDiv Desktop_Background" style="width:105px;">
							Back End Load
						</div>	
						<div class="FieldSetContentsDiv">
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med">Fee Type</span>
								<span class="fldValueSpan_med">
									<select id="belFeeTypeFld" class="fld_sml" disabled='true' xpath="FeeConfiguration/BackEndLoad/feeType" descXpath="FeeConfiguration/BackEndLoad/feeType" mandatory="true">
										<xsl:call-template name="List_tmpl">
											<xsl:with-param name="id">FeeTypeList</xsl:with-param>
										</xsl:call-template>
									</select>
								</span>
								<span class="fldLabelSpan_med">Based On</span>
								<span class="fldValueSpan_xlrg">
									<select id="belBasedOnFld" class="fld_xlrg" disabled='true' xpath="FeeConfiguration/BackEndLoad/basedOn" descXpath="FeeConfiguration/BackEndLoad/basedOnDesc" mandatory="true">
										<xsl:call-template name="List_tmpl">
											<xsl:with-param name="id">BasedOnBELTFRList</xsl:with-param>
										</xsl:call-template>
									</select>								
								</span>
							</div>		
							<div class="FieldRowDiv">								
								<span class="fldLabelSpan_med">Broker Commission</span>
								<span class="fldValueSpan_med">
									<input id="brokerCommFld" type="text" class="fld_med" xpath="FeeConfiguration/BackEndLoad/brokerComm" mandatory="true">
									</input>
								</span>
								<span class="fldLabelSpan_med">Withhold Rate</span>
								<span>
									<input type="text" class="fld_med" xpath="FeeConfiguration/BackEndLoad/withHoldRate">
									</input>								
								</span>		
							</div>										
							<div class="FieldRowDiv">
								<span class="fldLabelSpan_med">DSC Based Rate</span>
								<span class="fldValueSpan_med">
									<input type="text" class="fld_med" xpath="FeeConfiguration/BackEndLoad/dscBasedRate">
									</input>
								</span>
								<span class="fldLabelSpan_med">Minimum Var DSC</span>
								<span class="fldValueSpan_lrg">
									<input type="text" class="fld_med" xpath="FeeConfiguration/BackEndLoad/minVarDsc">
									</input>
								</span>
							</div>				
							<div class="FieldRowDiv">							
								<span class="fldLabelSpan_med">DSC Override</span>
								<span class="fldValueCheckbox">
									<input type="checkbox" xpath="FeeConfiguration/BackEndLoad/dscOverride">								
									</input>
								</span>								
							</div>								
						</div>
					</div>
				</div>
			</xsl:if>
			
			<div class="EntryScreenSectionDiv">
				<div id="FeeScalesSectionDiv" class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:75px">
						Fee Scales
					</div>
					
					<div id="FeeScales_TableDiv" class="Desktop_TableDiv">
						<table id="FeeScales_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" resizable="true" rowSelectable="true" scrollable="true" xpath="FeeConfiguration/FeeDetlScales/FeeScale" fieldList="feeCodeDesc;feeCode;level;lower;upper;rate;deff;scaleUUID;runMode" displayFieldList="feeCodeDesc;level;lower;upper;rate;deff" updated="false">
							<thead>
								<tr>
									<td style="width:110;" columnWidth="209">
										Fee Code
									</td>																
									<td style="width:110;" columnWidth="100">
										Level
									</td>								
									<td style="width:170;" columnWidth="120">
										Lower
									</td>	
									<td style="width:170;" columnWidth="120">
										Upper
									</td>									
									<td style="width:140;" columnWidth="100">
										Rate
									</td>							
									<td style="width:160;" columnWidth="100">
										Eff.Date
									</td>
								</tr>
							</thead>
							<tbody>					
								
							</tbody>
						</table>
					</div>
					
					<div id="FeeScalesSectionActionButtonsDiv">													
						<input type="button" id="FeeScaleAddBtn" value="Add" class="Desktop_Btn" onclick="clickHandler_addFeeDetailScaleBtn();"/>			
						<input type="button" id="FeeScaleModBtn" value="Modify" class="Desktop_Btn" disabled="true" onclick="clickHandler_modFeeDetailScaleBtn();"/>										
						<input type="button" id="FeeScaleDelBtn" value="Delete" class="Desktop_Btn" disabled="true" onclick="clickHandler_delFeeDetailScaleBtn();"/>
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
	
	<!-- ========================== FEE SCALE POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="FeeScalePopupContents_tmpl">
		<input type="hidden" id="feeScalePopup_UUIDFld" />
		
		<div style="padding:10px;">			
			<div class="FieldRowDiv">
				<span class="fldLabelSpan_sml">Fee Code</span>
				<span class="fldValueSpan_lrg">
					<select id="feeScalePopup_feeCodeFld" class="fld_xlrg">
						<xsl:call-template name="List_tmpl">
							<xsl:with-param name="id">FeeCodeList</xsl:with-param>
						</xsl:call-template>
					</select>				
				</span>				
			</div>
			<div class="FieldRowDiv">	
				<span class="fldLabelSpan_sml">Level</span>
				<span class="fldValueSpan_med">
					<input id="feeScalePopup_levelFld" type="text" class="fld_med">
					</input>
				</span>
				<span class="fldLabelSpan_sml">Eff.Date</span>
				<span class="fldValueSpan_med">
					<input id="feeScalePopup_deffFld" type="text" ifdsDatepicker="true" class="Desktop_Datepicker fld_med dateFld">
					</input>
				</span>
			</div>
			<div class="FieldRowDiv">
				<span class="fldLabelSpan_sml">Lower</span>
				<span class="fldValueSpan_med">
					<input id="feeScalePopup_lowerFld" type="text" class="fld_med">
					</input>
				</span>
				<span class="fldLabelSpan_sml">Upper</span>
				<span class="fldValueSpan_med">
					<input id="feeScalePopup_upperFld" type="text" class="fld_med">
					</input>
				</span>
				
			</div>			
			<div class="FieldRowDiv">			
				<span class="fldLabelSpan_sml">Rate</span>
				<span class="fldValueSpan_med">
					<input id="feeScalePopup_rateFld" type="text" class="fld_med">
					</input>
				</span>
				
			</div>
			<div style="padding-top:10px; text-align:center">
				<input type="button" id="popup_closeBtn" value="OK" class="Desktop_Btn" onclick="clickHandler_feeScalePopupOKBtn()"/>
				<input type="button" id="popup_closeBtn" value="Cancel" class="Desktop_Btn" onclick="clickHandler_feeScalePopupCancelBtn()"/>
			</div>
		</div>		
	</xsl:template>
</xsl:stylesheet>