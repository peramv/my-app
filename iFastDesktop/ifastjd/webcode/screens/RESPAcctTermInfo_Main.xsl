<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
		<xsl:with-param name="pageTitle">RESP Account Termination Information</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/RESPAcctTermInfo.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/RESPAcctTermInfo.js"></script>		
		<script>
			_accountNum = "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>";
			_respBenefId = "<xsl:value-of select="/websrvXML/FormInformation/RESPBenefID"/>";
			
			_modPerm = "<xsl:value-of select="/websrvXML/dtRESPTermintnReloadResponse/userPermissions/modPerm"/>" == "yes";
			_delPerm = "<xsl:value-of select="/websrvXML/dtRESPTermintnReloadResponse/userPermissions/delPerm"/>" == "yes";
			
			_moreRecordsExist = ("<xsl:value-of select="/websrvXML/dtRESPTermintnReloadResponse/RecordRange/moreRecordsExist"/>" == "yes");
			<xsl:if test="/websrvXML/dtRESPTermintnReloadResponse/RecordRange/moreRecordsExist = 'yes'">
				_rangeStartForNext = <xsl:value-of select="/websrvXML/dtRESPTermintnReloadResponse/RecordRange/rangeStartForNext"/>;
			</xsl:if>
		</script>
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">ActionPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">350</xsl:with-param>
			<xsl:with-param name="height">160</xsl:with-param>
			<xsl:with-param name="top">120</xsl:with-param>
			<xsl:with-param name="left">220</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="ActionPopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>
		
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">DetailsPopupDiv</xsl:with-param>
			<xsl:with-param name="caption">RESP Account Termination - Entry Details</xsl:with-param>
			<xsl:with-param name="width">350</xsl:with-param>
			<xsl:with-param name="height">130</xsl:with-param>
			<xsl:with-param name="top">120</xsl:with-param>
			<xsl:with-param name="left">250</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="DetailsPopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>
		
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >
		<xsl:variable name="AcctInfoNode" select="/websrvXML/dtRESPTermintnReloadResponse/RESPTerminationInfo/RESPAccountInfo"/>		
		<div class="ScreenSectionDiv" style="height:80px; margin-top:7px;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="font-weight:bold">
					RESP Account Information
				</div>
				<div class="FieldSetContentsDiv">
					<div class="SectionRowDiv">
						<span class="FldLabelSpan_left">
							Plan Number:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/planNo"/>
						</span>
						<span class="FldLabelSpan_right">
							RESP Status:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/respStat"/>
						</span>		
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan_left">
							Mature Date:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/matureDt"/>
						</span>
						<span class="FldLabelSpan_right">
							Inception Date:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/incepDt"/>
						</span>
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan_left">
							Grandfathered:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/grandFather"/>
						</span>
						<span class="FldLabelSpan_right">
							Sibling Only:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/siblingOnly"/>
						</span>
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan_left">
							Reported to HRDC:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/repHRDC"/>
						</span>
						<span class="FldLabelSpan_right">
							Reporting Required:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/repReqd"/>
						</span>
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan_left">
							Pre 98 Contributions:
						</span>
						<span class="FldValueSpan">
							<xsl:value-of select="$AcctInfoNode/pre98Contr"/>
						</span>
					</div>
				</div>
			</div>
		</div>
					
		<div class="ScreenSectionDiv" style="height:173px; margin-top:7px;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="font-weight:bold">
					Termination Entries
				</div>
				<div class="FieldSetContentsDiv">
					<div id="EntryList_TableDiv" class="Desktop_TableDiv" style="height:120px; width:767px; position:absolute;">
						<table id="EntryList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
							<thead>
								<tr>															
									<td>
										<xsl:attribute name="style">width:203</xsl:attribute>
										<xsl:attribute name="columnWidth">203</xsl:attribute>
										Trans Type
									</td>
									<td>
										<xsl:attribute name="style">width:90</xsl:attribute>
										<xsl:attribute name="columnWidth">90</xsl:attribute>
										Trans Date
									</td>
									<td>
										<xsl:attribute name="style">width:113</xsl:attribute>
										<xsl:attribute name="columnWidth">113</xsl:attribute>
										HRDC Trans Id
									</td>	
									<td>
										<xsl:attribute name="style">width:100</xsl:attribute>
										<xsl:attribute name="columnWidth">100</xsl:attribute>
										Date Sent
									</td>	
									<td>
										<xsl:attribute name="style">width:91</xsl:attribute>
										<xsl:attribute name="columnWidth">91</xsl:attribute>
										Amount
									</td>	
									<td>
										<xsl:attribute name="style">width:80</xsl:attribute>
										<xsl:attribute name="columnWidth">80</xsl:attribute>
										Reported
									</td>																						
									<td>
										<xsl:attribute name="style">width:70</xsl:attribute>
										<xsl:attribute name="columnWidth">70</xsl:attribute>
										Status
									</td>
								</tr>
							</thead>
							<tbody>
								<xsl:if test="/websrvXML/dtRESPTermintnReloadResponse/RESPTerminationInfo/TerminationRecords">
									<xsl:for-each select="/websrvXML/dtRESPTermintnReloadResponse/RESPTerminationInfo/TerminationRecords/TerminationDetail">
									<tr>
										<xsl:attribute name="runMode"></xsl:attribute>
										<xsl:attribute name="cesg"><xsl:value-of select="cesg"/></xsl:attribute>
										<xsl:attribute name="clb"><xsl:value-of select="clb"/></xsl:attribute>
										<xsl:attribute name="pGrant"><xsl:value-of select="pGrant"/></xsl:attribute>
										<xsl:attribute name="qesiGrant"><xsl:value-of select="qesiGrant"/></xsl:attribute>
										<xsl:attribute name="transType"><xsl:value-of select="transType"/></xsl:attribute>
										<xsl:attribute name="transDate"><xsl:value-of select="transDate"/></xsl:attribute>
										<xsl:attribute name="hrdcTransId"><xsl:value-of select="hrdcTransId"/></xsl:attribute>
										<xsl:attribute name="dateSent"><xsl:value-of select="dateSent"/></xsl:attribute>
										<xsl:attribute name="amt"><xsl:value-of select="amt"/></xsl:attribute>
										<xsl:attribute name="reported"><xsl:value-of select="reported"/></xsl:attribute>
										<xsl:attribute name="normalRvrse"><xsl:value-of select="normalRvrse"/></xsl:attribute>
										
										<td><xsl:value-of select="transType"/></td>
										<td><xsl:value-of select="transDate"/></td>
										<td><xsl:value-of select="hrdcIDDisp"/></td>
										<td><xsl:value-of select="dateSent"/></td>
										<td><xsl:value-of select="amt"/></td>
										<td><xsl:value-of select="reported"/></td>
										<td style="text-transform:capitalize"></td>
									</tr>
									</xsl:for-each>
								</xsl:if>
							</tbody>					
						</table>
					</div>
					<div style="position:absolute; left:0px; top:135px; width:100%; text-align:right; padding-right:20px;">
						<input type="button" class="Desktop_Btn" value="Expand" id="ExpandBtn" onclick="clickHandler_ExpandBtn()"/>
						<input type="button" class="Desktop_Btn" value="Modify" id="ModifyBtn">
							<xsl:attribute name="onclick">clickHandler_UpdateBtn( _MODIFY );</xsl:attribute>
						</input>
						<input type="button" class="Desktop_Btn" value="Delete" id="DeleteBtn">
							<xsl:attribute name="onclick">clickHandler_UpdateBtn( _DELETE );</xsl:attribute>
						</input>
						<input type="button" class="Desktop_Btn" value="Cancel" id="CancelBtn">
							<xsl:attribute name="onclick">clickHandler_UpdateBtn( _CANCEL );</xsl:attribute>
						</input>
						<!--
						<input type="button" class="Desktop_Btn" value="More" id="MoreBtn">
							<xsl:attribute name="onclick">clickHandler_MoreBtn();</xsl:attribute>
						</input>
						-->
					</div>					
				</div>
			</div>
		</div>
		<div class="ScreenButtonsDiv">					
			<input type="button" value="OK" id="btnOK" name="btnOK" class="Desktop_Btn">				
			</input>											
			<input type="button" value="Cancel" class="Desktop_Btn" id="btnCancel" name="btnCancel">				
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
	
	<!-- ========================== DETAILS POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="DetailsPopupContents_tmpl">
				
		<div style="padding:10px;">	
			<table cellpadding="0" cellspacing="0">
				<tr>
					<td width="100" style="padding-bottom:10px; padding-left:50px">CESG:</td>
					<td id="DetailsPopup_CESGFld" width="120" style="padding-bottom:10px; text-align:right"></td>
				</tr>
				<tr>
					<td style="padding-bottom:10px; padding-left:50px">CLB:</td>
					<td id="DetailsPopup_CLBFld" style="padding-bottom:10px; text-align:right"></td>
				</tr>
				<tr>
					<td style="padding-bottom:10px; padding-left:50px">P Grant:</td>
					<td id="DetailsPopup_PGrantFld" style="padding-bottom:10px; text-align:right"></td>
				</tr>								
			</table>		
			<div style="padding-top:10px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn">
					<xsl:attribute name="onclick">Desktop.hidePopup( "DetailsPopupDiv" );</xsl:attribute>
				</input>				
			</div>
		</div>		
	</xsl:template>
	
	<!-- ========================== ACTION POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="ActionPopupContents_tmpl">				
		<div style="padding:10px;">
			<input type="hidden" id="ActionPopup_RunModeFld"/>
			<input type="hidden" id="ActionPopup_TransTypeFld"/>
			<input type="hidden" id="ActionPopup_HRDCTransIDFld"/>
			<input type="hidden" id="ActionPopup_DateSentFld"/>
			<input type="hidden" id="ActionPopup_AmtFld"/>
			<input type="hidden" id="ActionPopup_ReportedFld"/>
			<input type="hidden" id="ActionPopup_NormalReverseFld"/>
			
			<div class="SectionRowDiv" id="DeleteConfirm" style="font-weight:bold; text-align:center; display:none">
				Are you sure you want to delete this record?
			</div>				
			<div class="SectionRowDiv" id="CancelConfirm" style="font-weight:bold; text-align:center; display:none">
				Are you sure you want to cancel this record?
			</div>
			<div class="SectionRowDiv">
				<span class="FldLabelSpan_left PopupFldLbl" style="width:100px;">
					Trans Type:
				</span>
				<span class="FldValueSpan PopupFld" id="ActionPopup_TransTypeLbl" style="width:180px;">
					
				</span>
			</div>
			<div class="SectionRowDiv" id="ActionPopup_TransDateFldRow">
				<span class="FldLabelSpan_left PopupFldLbl" style="width:100px;position:relative; top:7px;">
					Trans Date:
				</span>
				<span class="FldValueSpan PopupFld" style="width:180px; position:relative">
					<input id="ActionPopup_TransDateFld" ifdsDatepicker="true" class="Desktop_Datepicker FldInput dateFld" valueSetCallback="changeHandler_transDateFld()">
						<xsl:attribute name="value"></xsl:attribute>
					</input>
				</span>				
			</div>
			
			<div style="padding-top:15px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_ActionPopupOKBtn();</xsl:attribute>
				</input>				
				<input type="button" value="Cancel" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_ActionPopupCancelBtn();</xsl:attribute>
				</input>
			</div>
		</div>		
	</xsl:template>
	
</xsl:stylesheet>