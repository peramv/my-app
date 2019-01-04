<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">RESP Grant Information</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/RESPGrantInfo.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/RESPGrantInfo.js"></script>
		
		<script>
			_accountNum = "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>";
			_respBenefId = "<xsl:value-of select="/websrvXML/FormInformation/RESPBenefID"/>";			
			
			_statusMap = {};
			
			_statusMap[_CESG] = {};
			<xsl:for-each select="/websrvXML/dtRESPGrantInitResponse/StatusOptions/List[contains( @listName, 'CESG' )]">
				<xsl:variable name="listName"><xsl:value-of select="substring( @listName, 5 )"/></xsl:variable>
				_statusMap[_CESG]['<xsl:value-of select="$listName"/>'] = {};
				<xsl:for-each select="Element">
					_statusMap[_CESG]['<xsl:value-of select="$listName"/>']['<xsl:value-of select="code"/>'] = '<xsl:value-of select="value"/>';
				</xsl:for-each>				
			</xsl:for-each>
			
			_statusMap[_CLB] = {};
			<xsl:for-each select="/websrvXML/dtRESPGrantInitResponse/StatusOptions/List[contains( @listName, 'CLB' )]">
				<xsl:variable name="listName"><xsl:value-of select="substring( @listName, 4 )"/></xsl:variable>
				_statusMap[_CLB]['<xsl:value-of select="$listName"/>'] = {};
				<xsl:for-each select="Element">
					_statusMap[_CLB]['<xsl:value-of select="$listName"/>']['<xsl:value-of select="code"/>'] = '<xsl:value-of select="value"/>';
				</xsl:for-each>				
			</xsl:for-each>
			
			_statusMap[_ACES] = {};
			<xsl:for-each select="/websrvXML/dtRESPGrantInitResponse/StatusOptions/List[contains( @listName, 'ACES' )]">
				<xsl:variable name="listName"><xsl:value-of select="substring( @listName, 5 )"/></xsl:variable>
				_statusMap[_ACES]['<xsl:value-of select="$listName"/>'] = {};
				<xsl:for-each select="Element">
					_statusMap[_ACES]['<xsl:value-of select="$listName"/>']['<xsl:value-of select="code"/>'] = '<xsl:value-of select="value"/>';
				</xsl:for-each>				
			</xsl:for-each>
			
			_statusMap[_QESI] = {};
			<xsl:for-each select="/websrvXML/dtRESPGrantInitResponse/StatusOptions/List[contains( @listName, 'QESI' )]">
				<xsl:variable name="listName"><xsl:value-of select="substring( @listName, 5 )"/></xsl:variable>
				_statusMap[_QESI]['<xsl:value-of select="$listName"/>'] = {};
				<xsl:for-each select="Element">
					_statusMap[_QESI]['<xsl:value-of select="$listName"/>']['<xsl:value-of select="code"/>'] = '<xsl:value-of select="value"/>';
				</xsl:for-each>				
			</xsl:for-each>
			
			_CESGCurStat = "<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/currStat"/>";
			_CESGVersion = "<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/version"/>";
			
			_CLBCurStat = "<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CLBInformation/currStat"/>";
			_CLBVersion = "<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CLBInformation/version"/>";
			
			_genRT511 = "<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/genRT511"/>";
			
			_addPerm = ("<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/Permission/addPerm"/>" == "yes");
			_modPerm = ("<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/Permission/modPerm"/>" == "yes");
		</script>
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">ACESPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">320</xsl:with-param>
			<xsl:with-param name="height">130</xsl:with-param>
			<xsl:with-param name="top">397</xsl:with-param>
			<xsl:with-param name="left">250</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="ACESPopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>
		
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">QESIPopupDiv</xsl:with-param>
			<xsl:with-param name="caption"></xsl:with-param>
			<xsl:with-param name="width">390</xsl:with-param>
			<xsl:with-param name="height">135</xsl:with-param>
			<xsl:with-param name="top">520</xsl:with-param>
			<xsl:with-param name="left">225</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="QESIPopupContents_tmpl"/></xsl:with-param>			
		</xsl:call-template>				
		
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">HistoryPopupDiv</xsl:with-param>
			<xsl:with-param name="caption">Historical Information</xsl:with-param>
			<xsl:with-param name="width">644</xsl:with-param>
			<xsl:with-param name="height">225</xsl:with-param>
			<xsl:with-param name="top">70</xsl:with-param>
			<xsl:with-param name="left">75</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="DesktopHistoricalPopupTmpl"/></xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >		
		<div class="ScreenSectionDiv" style="height:98px; margin-top:4px;">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="overflow:visible; white-space:nowrap; font-weight:bold; text-align:center">
					RESP Beneficiary - <xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/name"/>					
				</div>
				<div class="FieldSetContentsDiv">					
					<div class="SectionRowDiv">
						<span class="FldLabelSpan BeneFldLbl_sml">
							SIN:
						</span>
						<span class="FldValueSpan BeneFld">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/sin"/>
							</span>
						</span>
						<span class="FldLabelSpan BeneFldLbl_med">
							Date of Birth:
						</span>
						<span class="FldValueSpan BeneFld" style="width:75px;">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/dob"/>
							</span>
						</span>
						<span class="FldLabelSpan BeneFldLbl_lrg">
							Tax Jurisdiction:
						</span>
						<span class="FldValueSpan BeneFld">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/taxjuris"/>
							</span>
						</span>			
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan BeneFldLbl_sml">
							Tax Type:
						</span>
						<span class="FldValueSpan BeneFld">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/taxTypeDesc"/>
							</span>
						</span>
						<span class="FldLabelSpan BeneFldLbl_med">
							Sibling Only:
						</span>
						<span class="FldValueSpan BeneFld" style="width:75px;">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/siblingOnly"/>
							</span>
						</span>
						<span class="FldLabelSpan BeneFldLbl_lrg">
							Specimen Number:
						</span>
						<span class="FldValueSpan BeneFld">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/specimenNum"/>
							</span>
						</span>											
					</div>
					
					<div class="SectionRowDiv">
						<span style="text-align:center">							
							<span class="FldLabelSpan BeneFldLbl_sml">
								Address:
							</span>
							<span class="FldValueSpan AddressFld">
								<span class="StaticFldValue">
									<xsl:variable name="benAddrInfo" select="/websrvXML/dtRESPGrantInitResponse/BenAddrInfo"/>
																		
									<xsl:value-of select="$benAddrInfo/addr1"/>
																		
									<xsl:if test="string-length( $benAddrInfo/addr2 ) &gt; 0">
										, <xsl:value-of select="$benAddrInfo/addr2"/>
									</xsl:if>
									
									<xsl:if test="string-length( $benAddrInfo/addr3 ) &gt; 0">
										, <xsl:value-of select="$benAddrInfo/addr3"/>
									</xsl:if>
									
									<xsl:if test="string-length( $benAddrInfo/city ) &gt; 0">
										, <xsl:value-of select="$benAddrInfo/city"/>
									</xsl:if>
									
									<xsl:if test="string-length( $benAddrInfo/prov ) &gt; 0">
										, <xsl:value-of select="$benAddrInfo/prov"/>
									</xsl:if>
									
									<xsl:if test="string-length( $benAddrInfo/cntry ) &gt; 0">
										, <xsl:value-of select="$benAddrInfo/cntry"/>
									</xsl:if>
									
									<xsl:if test="string-length( $benAddrInfo/pstl ) &gt; 0">
										, <xsl:value-of select="$benAddrInfo/pstl"/>
									</xsl:if>																		
																		
								</span>
							</span>
						</span>
					</div>						
				</div>
			</div>
		</div>
		<div class="ScreenSectionDiv">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="width:180px; font-weight:bold">
					Primary Care Giver (PCG)
				</div>
				<div class="FieldSetContentsDiv">
					<div class="SectionRowDiv">
						<span class="FldLabelSpan" style="width:100px;">
							Name:
						</span>
						<span class="FldValueSpan" style="text-align:left; width:200px;">
							<span class="StaticFldValue" style="width:100%; text-align:right;">								
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/pcgName"/>
							</span>
						</span>
						<span class="FldSpacerSpan"/>																
						<span class="FldLabelSpan">
							SIN/BN:
						</span>
						<span class="FldValueSpan AdminFld" style="width:60px;">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/pcgSINBN"/>
							</span>
						</span>							
					</div>
				</div>					
			</div>			
		</div>		
		
		<input type="hidden" id="CESG_runModeFld"/>	
		<div class="ScreenSectionDiv">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="width:120px; font-weight:bold">
					Additional CESG
				</div>
				<div class="FieldSetContentsDiv">
					<div class="SectionRowDiv">
						<span class="FldLabelSpan">
							Current Status:
						</span>
						<span class="FldValueSpan">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/currStat"/>
							</span>
						</span>
						<span class="FldSpacerSpan"/>
						<span class="AdminFldLabelSpan">
							Created By:
						</span>
						<span class="AdminFldValueSpan">							
							<span class="StaticFldValue">
								
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/createdby"/>
							</span>
						</span>
						<span class="AdminFldLabelSpan" style="margin-left:20px;">
							Process Date:
						</span>
						<span class="AdminFldValueSpan">
							<span class="StaticFldValue">
								
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/procdate"/>
							</span>
						</span>				
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan">
							New Status:
						</span>
						<span class="FldValueSpan">
							<xsl:if test="/websrvXML/dtRESPGrantInitResponse/CESGInformation/allowStatUpd = 'yes'">
								<select class="FldInput" id="CESGStatusFld" onchange="changeHandler_CESGStatusFld()">							
								</select>
							</xsl:if>
							<xsl:if test="/websrvXML/dtRESPGrantInitResponse/CESGInformation/allowStatUpd = 'no'">
								<select class="FldInput" id="CESGStatusFld" disabled='true'>							
								</select>
							</xsl:if>
						</span>
						<span class="FldSpacerSpan"/>
						<span class="AdminFldLabelSpan">
							Mod User:
						</span>
						<span class="AdminFldValueSpan">							
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/modUser"/>
							</span>
						</span>
						<span class="AdminFldLabelSpan" style="margin-left:20px;">
							Mod Date:
						</span>
						<span class="AdminFldValueSpan">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CESGInformation/modDate"/>
							</span>
						</span>
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan">
							Generate RT511:
						</span>
						<span class="FldValueSpan">
							<select class="FldInput" id="genRT511Fld" onchange="changeHandler_CESGFld();">
								<option/>							
								<option value="no">No</option>	
								<option value="yes">Yes</option>
							</select>
						</span>						
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan">
							Cut Off Date:
						</span>
						<span class="FldValueSpan" style="position:relative;">
							<input id="cutoffDateFld" ifdsDatepicker="true" class="Desktop_Datepicker FldInput dateFld" onchange="changeHandler_CESGFld();" valueSetCallback="changeHandler_cutoffDateFld()">
								<xsl:attribute name="value"></xsl:attribute>
							</input>
						</span>
						<span class="FldSpacerSpan"/>					
					</div>					
				</div>
			</div>	
		</div>
		
		<input type="hidden" id="CLB_runModeFld"/>
		<div class="ScreenSectionDiv">
			<div class="FieldSetDiv">
				<div class="FieldSetLabelDiv Desktop_Background" style="width:220px; font-weight:bold">
					Canadian Learning Bond (CLB)
				</div>
				<div class="FieldSetContentsDiv">					
					<div class="SectionRowDiv">
						<span class="FldLabelSpan">
							Current Status:
						</span>
						<span class="FldValueSpan">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CLBInformation/currStat"/>
							</span>
						</span>
						<span class="FldSpacerSpan"/>
						<span class="AdminFldLabelSpan">
							Created By:
						</span>
						<span class="AdminFldValueSpan AdminFld">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CLBInformation/createdby"/>
							</span>
						</span>
						<span class="AdminFldLabelSpan" style="margin-left:20px;">
							Process Date:
						</span>
						<span class="AdminFldValueSpan">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CLBInformation/procdate"/>
							</span>
						</span>
					</div>
					<div class="SectionRowDiv">
						<span class="FldLabelSpan">
							New Status:
						</span>
						<span class="FldValueSpan">
							<xsl:if test="/websrvXML/dtRESPGrantInitResponse/CLBInformation/allowStatUpd = 'yes'">
								<select class="FldInput" id="CLBStatusFld" onchange="changeHandler_CLBFld()">							
								</select>
							</xsl:if>
							<xsl:if test="/websrvXML/dtRESPGrantInitResponse/CLBInformation/allowStatUpd = 'no'">
								<select class="FldInput" id="CLBStatusFld" disabled="true">							
								</select>
							</xsl:if>
						</span>
						<span class="FldSpacerSpan"/>
						<span class="AdminFldLabelSpan">
							Mod User:
						</span>
						<span class="AdminFldValueSpan">
							<span class="StaticFldValue">
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CLBInformation/modUser"/>
							</span>
						</span>
						<span class="AdminFldLabelSpan" style="margin-left:20px;">
							Mod Date:
						</span>
						<span class="AdminFldValueSpan">
							<span class="StaticFldValue">								
								<xsl:value-of select="/websrvXML/dtRESPGrantInitResponse/CLBInformation/modDate"/>
							</span>
						</span>
					</div>					
				</div>				
			</div>	
		</div>
		
		<xsl:if test="/websrvXML/dtRESPGrantInitResponse/ShowOtherGrants/showACES = 'yes'">
			<div class="ScreenSectionDiv" style="height:132px;">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:125px; font-weight:bold">
						Grant Type: ACES
					</div>
					<div class="FieldSetContentsDiv">					
						<div id="ACESList_TableDiv" class="Desktop_TableDiv" style="height:80px; width:767px; position:absolute;">
							<table id="ACESList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
								<thead>
									<tr>															
										<td>
											<xsl:attribute name="style">width:173</xsl:attribute>
											<xsl:attribute name="columnWidth">173</xsl:attribute>
											Current Status
										</td>
										<td>
											<xsl:attribute name="style">width:153</xsl:attribute>
											<xsl:attribute name="columnWidth">153</xsl:attribute>
											Grant Option
										</td>
										<td>
											<xsl:attribute name="style">width:120</xsl:attribute>
											<xsl:attribute name="columnWidth">120</xsl:attribute>
											Created By
										</td>	
										<td>
											<xsl:attribute name="style">width:100</xsl:attribute>
											<xsl:attribute name="columnWidth">100</xsl:attribute>
											Process Date
										</td>	
										<td>
											<xsl:attribute name="style">width:100</xsl:attribute>
											<xsl:attribute name="columnWidth">100</xsl:attribute>
											Mod User
										</td>	
										<td>
											<xsl:attribute name="style">width:100</xsl:attribute>
											<xsl:attribute name="columnWidth">100</xsl:attribute>
											Mod Date
										</td>																						
									</tr>
								</thead>
								<tbody>
									<xsl:for-each select="/websrvXML/dtRESPGrantInitResponse/ACESInformation/ACESRecord">
										<tr>
											<xsl:attribute name="runMode"></xsl:attribute>
											<xsl:attribute name="grantInfoId"><xsl:value-of select="grantInfoID"/></xsl:attribute>
											<xsl:attribute name="stat"><xsl:value-of select="stat"/></xsl:attribute>
											<xsl:attribute name="year"><xsl:value-of select="grantOpt"/></xsl:attribute>
											<xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
											<xsl:attribute name="allowUpd"><xsl:value-of select="allowStatUpd"/></xsl:attribute>
											
											<td><xsl:value-of select="stat"/></td>
											<td><xsl:value-of select="grantDesc"/></td>
											<td><xsl:value-of select="createdBy"/></td>
											<td><xsl:value-of select="procDate"/></td>
											<td><xsl:value-of select="modUser"/></td>
											<td><xsl:value-of select="modDate"/></td>										
										</tr>
									</xsl:for-each>
								</tbody>					
							</table>
						</div>
						<div class="GrantActionButtonsDiv">
							<xsl:choose>
								<xsl:when test="/websrvXML/dtRESPGrantInitResponse/RESPGrantInfo/siblingOnly = 'Y'">
									<input type="button" value="Add" id='ACESAddBtn' class="Desktop_Btn">
										<xsl:attribute name="onclick">clickHandler_addGrantBtn( _ACES );</xsl:attribute>
									</input>
								</xsl:when>
								<xsl:otherwise>
									<input type="button" value="Add" id='ACESAddBtn' class="Desktop_Btn" disabled="true"/>
								</xsl:otherwise>
							</xsl:choose>																			
							<input type="button" value="Modify" id='ACESModBtn' class="Desktop_Btn" disabled='true'>
								<xsl:attribute name="onclick">clickHandler_modGrantBtn( _ACES );</xsl:attribute>
							</input>																								
							<input type="button" value="Delete" id='ACESDelBtn' class="Desktop_Btn" disabled='true'>
								<xsl:attribute name="onclick">clickHandler_delGrantBtn( _ACES );</xsl:attribute>
							</input>
						</div>						
					</div>
				</div>	
			</div>
		</xsl:if>
		
		<xsl:if test="/websrvXML/dtRESPGrantInitResponse/ShowOtherGrants/showQESI = 'yes'">
			<div class="ScreenSectionDiv" style="height:132px;">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:125px; font-weight:bold">
						Grant Type: QESI
					</div>
					<div class="FieldSetContentsDiv">					
						<div id="QESIList_TableDiv" class="Desktop_TableDiv" style="height:80px; width:767px; position:absolute;">
							<table id="QESIList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
								<thead>
									<tr>															
										<td>
											<xsl:attribute name="style">width:153</xsl:attribute>
											<xsl:attribute name="columnWidth">153</xsl:attribute>
											Current Status
										</td>
										<td>
											<xsl:attribute name="style">width:61</xsl:attribute>
											<xsl:attribute name="columnWidth">61</xsl:attribute>
											Year
										</td>
										<td>
											<xsl:attribute name="style">width:130</xsl:attribute>
											<xsl:attribute name="columnWidth">130</xsl:attribute>
											Stop Reason
										</td>
										<td>
											<xsl:attribute name="style">width:102</xsl:attribute>
											<xsl:attribute name="columnWidth">102</xsl:attribute>
											Created By
										</td>	
										<td>
											<xsl:attribute name="style">width:100</xsl:attribute>
											<xsl:attribute name="columnWidth">100</xsl:attribute>
											Process Date
										</td>	
										<td>
											<xsl:attribute name="style">width:100</xsl:attribute>
											<xsl:attribute name="columnWidth">100</xsl:attribute>
											Mod User
										</td>	
										<td>
											<xsl:attribute name="style">width:100</xsl:attribute>
											<xsl:attribute name="columnWidth">100</xsl:attribute>
											Mod Date
										</td>																						
									</tr>
								</thead>
								<tbody>
									<xsl:for-each select="/websrvXML/dtRESPGrantInitResponse/QESIInformation/QESIRecord">
										<tr>
											<xsl:attribute name="runMode"></xsl:attribute>
											<xsl:attribute name="grantInfoId"><xsl:value-of select="grantInfoID"/></xsl:attribute>
											<xsl:attribute name="stat"><xsl:value-of select="stat"/></xsl:attribute>
											<xsl:attribute name="year"><xsl:value-of select="grantYr"/></xsl:attribute>
											<xsl:attribute name="stopReason"><xsl:value-of select="stopReason"/></xsl:attribute>
											<xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
											<xsl:attribute name="allowUpd"><xsl:value-of select="allowStatUpd"/></xsl:attribute>
											
											<td><xsl:value-of select="stat"/></td>
											<td><xsl:value-of select="grantYr"/></td>
											<td><xsl:value-of select="stopReasonDesc"/></td>
											<td><xsl:value-of select="createdBy"/></td>
											<td><xsl:value-of select="procDate"/></td>
											<td><xsl:value-of select="modUser"/></td>
											<td><xsl:value-of select="modDate"/></td>										
										</tr>
									</xsl:for-each>
								</tbody>					
							</table>
						</div>
						<div class="GrantActionButtonsDiv">		
							<input type="button" value="Add" id='QESIAddBtn' class="Desktop_Btn">
								<xsl:attribute name="onclick">clickHandler_addGrantBtn( _QESI );</xsl:attribute>
							</input> 										
							<input type="button" value="Modify" id='QESIModBtn' class="Desktop_Btn" disabled="true">
								<xsl:attribute name="onclick">clickHandler_modGrantBtn( _QESI );</xsl:attribute>
							</input>																								
							<input type="button" value="Delete" id='QESIDelBtn' class="Desktop_Btn" disabled="true">
								<xsl:attribute name="onclick">clickHandler_delGrantBtn( _QESI );</xsl:attribute>
							</input>
						</div>						
					</div>
				</div>	
			</div>
		</xsl:if>
		
		<div class="ScreenButtonsDiv">
			<input type="button" value="Historical" id="historicalBtn" class="Desktop_Btn">
				<xsl:attribute name="onclick">Desktop.displayHistorical( "HistoryPopupDiv", "RESPGrantInfo_History", {searchValue1:_accountNum, searchValue2:_respBenefId} )</xsl:attribute>				
			</input>			
			<xsl:choose>
				<xsl:when test="/websrvXML/dtRESPGrantInitResponse/Permission/modPerm = 'no'and /websrvXML/dtRESPGrantInitResponse/Permission/addPerm = 'no'">
					<input type="button" value="OK" class="Desktop_Btn" disabled='true'>				
					</input>					
				</xsl:when>
				<xsl:otherwise>
					<input type="button" value="OK" id="okBtn" class="Desktop_Btn" onclick="clickHandler_okBtn();">				
					</input>
					<input type="button" style="display:none" id="btnOK" name="btnOK"/>
				</xsl:otherwise>
			</xsl:choose>
			<input type="button" value="Cancel" id="btnCancel" name="btnCancel" class="Desktop_Btn">				
			</input>			
		</div>
	</xsl:template>
	
	
	<!-- ========================== ACES POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="ACESPopupContents_tmpl">
		
		<input type="hidden" id="ACESPopup_modeFld"></input>
		<input type="hidden" id="ACESPopup_grantInfoIdFld"></input>
		<input type="hidden" id="ACESPopup_versionFld"></input>								
		<div style="padding:10px;">				
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">
					Status
				</span>
				<span class="FldValueSpan PopupFld">
					<select id="ACESPopup_statusFld" class="FldInput">
						
					</select>
				</span>
			</div>
			<div class="SectionRowDiv">				
				<span class="FldLabelSpan">
					Grant Option
				</span>
				<span class="FldValueSpan PopupFld">
					<select id="ACESPopup_yearFld" class="FldInput">						
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">ACESYearOptions</xsl:with-param>
						</xsl:call-template>
					</select>
				</span>
			</div>
			
			<div style="padding-top:10px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_grantPopupOKBtn( _ACES );</xsl:attribute>
				</input>
				<input type="button" value="Cancel" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_grantPopupCancelBtn( _ACES );</xsl:attribute>
				</input>
			</div>
		</div>		
	</xsl:template>
	
	<!-- ========================== QESI POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="QESIPopupContents_tmpl">
		
		<input type="hidden" id="QESIPopup_modeFld"></input>
		<input type="hidden" id="QESIPopup_grantInfoIdFld"></input>
		<input type="hidden" id="QESIPopup_versionFld"></input>
		<div style="padding:10px;">				
			<div class="SectionRowDiv">
				<span class="FldLabelSpan">
					Status
				</span>
				<span class="FldValueSpan PopupFld">
					<select id="QESIPopup_statusFld" class="FldInput" onchange="changeHandler_QESIStatusFld()">
						
					</select>
				</span>
			</div>
			<div class="SectionRowDiv">				
				<span class="FldLabelSpan">
					Year
				</span>
				<span class="FldValueSpan PopupFld">
					<select id="QESIPopup_yearFld" class="FldInput">						
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">QESIYearOptions</xsl:with-param>
						</xsl:call-template>
					</select>
					<input id="QESIPopup_yearStaticFld" class="FldInput" disabled="true"/>					
				</span>
			</div>
			<div class="SectionRowDiv">				
				<span class="FldLabelSpan">
					Stop Reason
				</span>
				<span class="FldValueSpan PopupFld" width="225">
					<select id="QESIPopup_stopReasonFld" class="FldInput" style="width:220">						
						<xsl:call-template name="List_Tmpl">
							<xsl:with-param name="listName">StopReasonList</xsl:with-param>
						</xsl:call-template>
					</select>									
				</span>
			</div>
			
			<div style="padding-top:10px; text-align:center">
				<input type="button" value="OK" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_grantPopupOKBtn( _QESI );</xsl:attribute>
				</input>
				<input type="button" value="Cancel" class="Desktop_Btn">
					<xsl:attribute name="onclick">clickHandler_grantPopupCancelBtn( _QESI );</xsl:attribute>
				</input>
			</div>
		</div>		
	</xsl:template>
	
	<!-- ========================== HISTORY POPUP CONTENTS TEMPLATE =============================-->
	<xsl:template name="HistoryPopupContents_tmpl">
		
	</xsl:template>
	
	<!-- ========================== LIST TEMPLATE =============================-->
	<xsl:template name="List_Tmpl">
		<xsl:param name="listName"/>
		
		<xsl:for-each select=".//List[@listName = $listName]/Element">
			<option>
				<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
				
				<xsl:value-of select="value"/>
			</option>
		</xsl:for-each>
	</xsl:template>
	
</xsl:stylesheet>