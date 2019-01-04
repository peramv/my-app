<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:template name="NotionalData_Tmpl">		
		<xsl:param name="notlDataNode"/>
		<xsl:param name="notlOtherInfoNode"/>	
		<xsl:param name="dateFilterType"/>
		<xsl:param name="permissionNode"/>
				
		<xsl:variable name="NOTL_EXISTS" select="$notlDataNode/notlExist = 'yes'"/>
		<xsl:variable name="PROV_NOTL_EXISTS" select="$notlDataNode/provNotlExist = 'yes'"/>
		<xsl:variable name="MOD_PERM" select="$permissionNode/modPerm = 'yes'"/>	
		
		<div>
			<input type="hidden" id="versionNotlFld">
				<xsl:attribute name="value"><xsl:value-of select="$notlDataNode/versionNotl"/></xsl:attribute>
			</input>
			<input type="hidden" id="versionPNotlFld">
				<xsl:attribute name="value"><xsl:value-of select="$notlDataNode/versionPNotl"/></xsl:attribute>
			</input>
			<input type="hidden" id="respNotlInfoIdFld">
				<xsl:attribute name="value"><xsl:value-of select="$notlDataNode/respNotlInfoID"/></xsl:attribute>
			</input>
			
			<div class="ScreenSectionDiv">
				<span class="bold" style="padding-left:10px; padding-right:10px;">Market Value:</span>
				<span><xsl:value-of select="$notlDataNode/mktValue"/></span>			
			</div>
			
			<div class="ScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:165px; font-weight:bold">
						Contribution &amp; Income
					</div>
					<div class="FieldSetContentsDiv">						
						<div class="SectionRowDiv" style="height:22px; position:relative; top:-4px;">	
							<span class="rowLabel"/>					
							<span class="columnSpan columnHeader">Purchase</span>
							<span class="columnSpan columnHeader">Redemption</span>
							<span class="columnSpan columnHeader">Repayments</span>
							<span class="columnSpan columnHeader">Balance</span>
						</div>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">1</xsl:with-param>
							<xsl:with-param name="rowLabel">Income</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purIncome )"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purIncome"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redIncome )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redIncome"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyIncome )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyIncome"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balIncome )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balIncome"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">2</xsl:with-param>
							<xsl:with-param name="rowLabel">Total Contribution</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purContrib )"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purContrib"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redContrib )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redContrib"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyContrib )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyContrib"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balTotContrib )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balTotContrib"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">3</xsl:with-param>
							<xsl:with-param name="rowLabel">Assisted Contribution</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purACContrib)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purACContrib"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redACContrib )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redACContrib"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyACContrib )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyACContrib"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balACContrib )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balACContrib"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">4</xsl:with-param>
							<xsl:with-param name="rowLabel">Unassisted Contribution</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purUCContrib)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purUCContrib"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redUCContrib )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redUCContrib"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyUCContrib )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyUCContrib"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balUCContrib )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balUCContrib"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>							
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">5</xsl:with-param>
							<xsl:with-param name="rowLabel">Pre-1998 Contribution</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purPre98)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purPre98"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redPre98 )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redPre98"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyPre98 )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyPre98"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balPre98 )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balPre98"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>					
					</div>					
				</div>
			</div>
						
			<div class="ScreenSectionDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:53px; font-weight:bold">
						Grants
					</div>
					<div class="FieldSetContentsDiv">						
						<div class="SectionRowDiv" style="height:22px; position:relative; top:-4px;">	
							<span class="rowLabel"/>					
							<span class="columnSpan columnHeader">Purchase</span>
							<span class="columnSpan columnHeader">Redemption</span>
							<span class="columnSpan columnHeader">Repayments</span>
							<span class="columnSpan columnHeader">Balance</span>
						</div>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">6</xsl:with-param>
							<xsl:with-param name="rowLabel">Total CESG</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purCESGTotal)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purCESGTotal"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redCESGTotal )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redCESGTotal"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyCESGTotal )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyCESGTotal"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balTotCESG )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balTotCESG"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">7</xsl:with-param>
							<xsl:with-param name="rowLabel">Basic CESG</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purCESGGrant)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purCESGGrant"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redCESGGrant )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redCESGGrant"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyCESGGrant )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyCESGGrant"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balCESG )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balCESG"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">8</xsl:with-param>
							<xsl:with-param name="rowLabel">Additional CESG</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purAddlGrant)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purAddlGrant"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redAddlGrant )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redAddlGrant"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyAddlGrant )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyAddlGrant"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balAddlGrant )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balAddlGrant"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>			
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">9</xsl:with-param>
							<xsl:with-param name="rowLabel">CLB</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purCLB)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purCLB"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redCLB )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redCLB"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyCLB )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyCLB"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balCLB )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balCLB"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">10</xsl:with-param>
							<xsl:with-param name="rowLabel">P-Grant ACES</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purpGrant)"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purpGrant"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redpGrant )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redpGrant"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpypGrant )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpypGrant"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balACES )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balACES"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<xsl:call-template name="DataRow_Tmpl">
							<xsl:with-param name="rowNum">20</xsl:with-param>
							<xsl:with-param name="rowLabel">CESG Grant Received by Other Institution</xsl:with-param>
							<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/purCesgPaid )"/></xsl:with-param>
							<xsl:with-param name="purFldVal" select="$notlDataNode/purCesgPaid"/>
							<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redCesgPaid )"/></xsl:with-param>
							<xsl:with-param name="redFldVal" select="$notlDataNode/redCesgPaid"/>
							<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyCesgPaid )"/></xsl:with-param>
							<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyCesgPaid"/>
							<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balCesgPaid )"/></xsl:with-param>
							<xsl:with-param name="balFldVal" select="$notlDataNode/balCesgPaid"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
							<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
						</xsl:call-template>
						
						<div>
							<xsl:attribute name="style">display:<xsl:choose><xsl:when test="$notlOtherInfoNode/showQESI = 'yes' and $dateFilterType = 'period'">block</xsl:when><xsl:otherwise>none</xsl:otherwise></xsl:choose></xsl:attribute>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">11</xsl:with-param>
								<xsl:with-param name="rowLabel">Total QESI</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/totQGrant)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/totQGrant"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/grantRed )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/grantRed"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/grantRepymt )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/grantRepymt"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balGrant )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balGrant"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$PROV_NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
							</xsl:call-template>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">12</xsl:with-param>
								<xsl:with-param name="rowLabel">Basic QESI</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/grantBasicPur)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/grantBasicPur"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redBasic )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/redBasic"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyBasic )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyBasic"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balGrantBasic )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balGrantBasic"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$PROV_NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
							</xsl:call-template>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">13</xsl:with-param>
								<xsl:with-param name="rowLabel">Increase QESI</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/grantAddlPur)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/grantAddlPur"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/redAddl )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/redAddl"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyAddl )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyAddl"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balGrantAddl )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balGrantAddl"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$PROV_NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
							</xsl:call-template>
						</div>												
					</div>
				</div>
			</div>
						
			<div class="ScreenSectionDiv">
				<xsl:attribute name="style">display:<xsl:choose><xsl:when test="$notlOtherInfoNode/showQESI = 'yes'">block</xsl:when><xsl:otherwise>none</xsl:otherwise></xsl:choose></xsl:attribute>
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:132px; font-weight:bold">
						QESI Contribution
					</div>
					<div class="FieldSetContentsDiv">						
						<div class="SectionRowDiv" style="height:22px; position:relative; top:-4px;">	
							<span class="rowLabel"/>					
							<span class="columnSpan columnHeader">Purchase</span>
							<span class="columnSpan columnHeader">Redemption</span>
							<span class="columnSpan columnHeader">Repayments</span>
							<span class="columnSpan columnHeader">Balance</span>
						</div>
						
						<xsl:if test="$dateFilterType = 'asOf'">
							<div class="SectionRowDiv" style="text-align:center; font-style:italic">
								QESI data not available when filtering by 'As Of' date.
							</div>
						</xsl:if>	
						
						
						<xsl:if test="$dateFilterType = 'period'">
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">14</xsl:with-param>
								<xsl:with-param name="rowLabel"><xsl:value-of select="$notlOtherInfoNode/ytdLabel"/></xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/ytdPurContrib)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/ytdPurContrib"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/ytdRedContrib )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/ytdRedContrib"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/ytdRpyContrib )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/ytdRpyContrib"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balYTDContrib )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balYTDContrib"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow">Y</xsl:with-param>
							</xsl:call-template>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">15</xsl:with-param>
								<xsl:with-param name="rowLabel">Total Contribution</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/qPurContrib)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/qPurContrib"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/qRedContrib )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/qRedContrib"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/qRpyContrib )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/qRpyContrib"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balQTotContrib )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balQTotContrib"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow">Y</xsl:with-param>
							</xsl:call-template>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">16</xsl:with-param>
								<xsl:with-param name="rowLabel">Assisted Contribution</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/qPurACContrib)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/qPurACContrib"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/qRedACContrib )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/qRedACContrib"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/qRpyACContrib )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/qRpyACContrib"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balQACContrib )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balQACContrib"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>								
								<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$PROV_NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
							</xsl:call-template>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">17</xsl:with-param>
								<xsl:with-param name="rowLabel">Unassisted Contribution</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/qPurUCContrib)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/qPurUCContrib"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/qRedUCContrib )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/qRedUCContrib"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/qRpyUCContrib )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/qRpyUCContrib"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balQUCContrib )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balQUCContrib"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$PROV_NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
							</xsl:call-template>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">18</xsl:with-param>
								<xsl:with-param name="rowLabel">Pre-Feb 21 2007 Contribution</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/prePurContrib)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/prePurContrib"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/preRedContrib )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/preRedContrib"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/preRpyContrib )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/preRpyContrib"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balPreContrib )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balPreContrib"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$PROV_NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
							</xsl:call-template>
							
							<xsl:call-template name="DataRow_Tmpl">
								<xsl:with-param name="rowNum">19</xsl:with-param>
								<xsl:with-param name="rowLabel">Pre-1998 Contribution</xsl:with-param>
								<xsl:with-param name="purFldName"><xsl:value-of select="name( $notlDataNode/pre98PurContrib)"/></xsl:with-param>
								<xsl:with-param name="purFldVal" select="$notlDataNode/pre98PurContrib"/>
								<xsl:with-param name="redFldName"><xsl:value-of select="name( $notlDataNode/pre98RedContrib )"/></xsl:with-param>
								<xsl:with-param name="redFldVal" select="$notlDataNode/pre98RedContrib"/>
								<xsl:with-param name="rpyFldName"><xsl:value-of select="name( $notlDataNode/rpyPre98Contrib )"/></xsl:with-param>
								<xsl:with-param name="rpyFldVal" select="$notlDataNode/rpyPre98Contrib"/>
								<xsl:with-param name="balFldName"><xsl:value-of select="name( $notlDataNode/balQPre98 )"/></xsl:with-param>
								<xsl:with-param name="balFldVal" select="$notlDataNode/balQPre98"/>
								<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
								<xsl:with-param name="isStaticRow"><xsl:choose><xsl:when test="$PROV_NOTL_EXISTS and $MOD_PERM">N</xsl:when><xsl:otherwise>Y</xsl:otherwise></xsl:choose></xsl:with-param>
							</xsl:call-template>
						</xsl:if>
					</div>
				</div>			
			</div>					
		</div>  
	</xsl:template>
	
	<!-- ========================== DATA ROW TEMPLATE =============================-->
	<xsl:template name="DataRow_Tmpl">
		<xsl:param name="rowNum"/>
		<xsl:param name="rowLabel"/>
		<xsl:param name="purFldName"/>		
		<xsl:param name="purFldVal"/>
		<xsl:param name="redFldName"/>
		<xsl:param name="redFldVal"/>
		<xsl:param name="rpyFldName"/>
		<xsl:param name="rpyFldVal"/>
		<xsl:param name="balFldName"/>
		<xsl:param name="balFldVal"/>
		<xsl:param name="dateFilterType"/>
		<xsl:param name="isStaticRow">N</xsl:param>
		
		<div class="SectionRowDiv">
			<xsl:attribute name="id">dataRow:<xsl:value-of select="$rowNum"/></xsl:attribute>
			<xsl:attribute name="purFldName"><xsl:value-of select="$purFldName"/></xsl:attribute>
			<xsl:attribute name="redFldName"><xsl:value-of select="$redFldName"/></xsl:attribute>
			<xsl:attribute name="rpyFldName"><xsl:value-of select="$rpyFldName"/></xsl:attribute>
			<xsl:attribute name="balFldName"><xsl:value-of select="$balFldName"/></xsl:attribute>
			<xsl:attribute name="purFldVal"><xsl:value-of select="$purFldVal"/></xsl:attribute>
			
			<span class="columnSpan">	
				<span class="rowLabel">
					<xsl:value-of select="$rowLabel"/>
				</span>					
			</span>
			<span class="columnSpan">
				<xsl:choose>
					<xsl:when test="$purFldName = 'totQGrant'">
						<xsl:call-template name="columnStaticFld_Tmpl">
							<xsl:with-param name="fldId" select="$purFldName"/>					
							<xsl:with-param name="fldVal" select="$purFldVal"/>
						</xsl:call-template>
					</xsl:when>
					<xsl:when test="$purFldName = 'purCesgPaid'">
						<xsl:call-template name="columnStaticFld_Tmpl">
							<xsl:with-param name="fldId" select="$purFldName"/>					
							<xsl:with-param name="fldVal" select="$purFldVal"/>
						</xsl:call-template>
					</xsl:when>
					<xsl:when test="$isStaticRow = 'N'">
						<xsl:call-template name="columnFld_Tmpl">
							<xsl:with-param name="rowNum" select="$rowNum"/>
							<xsl:with-param name="fldId" select="$purFldName"/>									
							<xsl:with-param name="fldVal" select="$purFldVal"/>					
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>									
						</xsl:call-template>							
					</xsl:when>					
					<xsl:otherwise>
						<xsl:call-template name="columnStaticFld_Tmpl">
							<xsl:with-param name="fldId" select="$purFldName"/>					
							<xsl:with-param name="fldVal" select="$purFldVal"/>
						</xsl:call-template>	
					</xsl:otherwise>
				</xsl:choose>				
			</span>
			<span class="columnSpan">				
				<xsl:choose>
					<xsl:when test="$isStaticRow = 'N'">
						<xsl:call-template name="columnFld_Tmpl">
							<xsl:with-param name="rowNum" select="$rowNum"/>
							<xsl:with-param name="fldId" select="$redFldName"/>
							<xsl:with-param name="fldVal" select="$redFldVal"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
						</xsl:call-template>
					</xsl:when>
					<xsl:otherwise>
						<xsl:call-template name="columnStaticFld_Tmpl">
							<xsl:with-param name="fldId" select="$redFldName"/>					
							<xsl:with-param name="fldVal" select="$redFldVal"/>
						</xsl:call-template>	
					</xsl:otherwise>
				</xsl:choose>						
			</span>
			<span class="columnSpan">
				<xsl:choose>
					<xsl:when test="$isStaticRow = 'N'">
						<xsl:call-template name="columnFld_Tmpl">
							<xsl:with-param name="rowNum" select="$rowNum"/>
							<xsl:with-param name="fldId" select="$rpyFldName"/>
							<xsl:with-param name="fldVal" select="$rpyFldVal"/>
							<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
						</xsl:call-template>		
					</xsl:when>
					<xsl:otherwise>
						<xsl:call-template name="columnStaticFld_Tmpl">
							<xsl:with-param name="fldId" select="$rpyFldName"/>					
							<xsl:with-param name="fldVal" select="$rpyFldVal"/>
						</xsl:call-template>
					</xsl:otherwise>
				</xsl:choose>
			</span>
			<span class="columnSpan">
				<xsl:call-template name="columnStaticFld_Tmpl">
					<xsl:with-param name="fldId" select="$balFldName"/>					
					<xsl:with-param name="fldVal" select="$balFldVal"/>
				</xsl:call-template>	
			</span>
		</div>	
				
	</xsl:template>
	
	
	<!-- ========================== COLUMN FLD TEMPLATE =============================-->
	<xsl:template name="columnFld_Tmpl">
		<xsl:param name="rowNum"/>
		<xsl:param name="fldId"/>
		<xsl:param name="fldVal"/>
		<xsl:param name="dateFilterType"/>		
		
		<xsl:choose>
			<xsl:when test="$fldVal = ''">
				<span></span>				
			</xsl:when>
			<xsl:when test="$fldVal = 'N/A'">				
				<xsl:call-template name="columnStaticFld_Tmpl">
					<xsl:with-param name="fldId" select="$fldId"/>
					<xsl:with-param name="fldVal" select="$fldVal"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>				
				<xsl:call-template name="columnEntryFld_Tmpl">
					<xsl:with-param name="rowNum" select="$rowNum"/>
					<xsl:with-param name="fldId" select="$fldId"/>
					<xsl:with-param name="fldVal" select="$fldVal"/>					
					<xsl:with-param name="dateFilterType" select="$dateFilterType"/>
				</xsl:call-template>	
			</xsl:otherwise>
		</xsl:choose>		
	</xsl:template>
	
	<!-- ========================== COLUMN STATIC FLD TEMPLATE =============================-->
	<xsl:template name="columnStaticFld_Tmpl">
		<xsl:param name="fldId"/>
		<xsl:param name="fldVal"/>
		
		<span class="columnStaticFld" id="{$fldId}" style="text-align:right"><xsl:value-of select="$fldVal"/></span>	
	</xsl:template>
	
	<!-- ========================== COLUMN ENTRY FLD TEMPLATE =============================-->
	<xsl:template name="columnEntryFld_Tmpl">
		<xsl:param name="rowNum"/>
		<xsl:param name="fldId"/>
		<xsl:param name="fldVal"/>
		<xsl:param name="dateFilterType"/>
				
		<xsl:if test="$dateFilterType = 'period'">		
			<input type="text" class="columnEntryFld" id="{$fldId}">
				<xsl:attribute name="value"><xsl:value-of select="$fldVal"/></xsl:attribute>
				<xsl:attribute name="onchange">changeHandler_entryFld( this, <xsl:value-of select="$rowNum"/> );</xsl:attribute>
			</input>		
		</xsl:if>
		
		<xsl:if test="$dateFilterType != 'period'">		
			<input type="text" class="columnEntryFld" id="{$fldId}">
				<xsl:attribute name="disabled">true</xsl:attribute>
				<xsl:attribute name="value"><xsl:value-of select="$fldVal"/></xsl:attribute>
				<xsl:attribute name="onchange">changeHandler_entryFld( this, <xsl:value-of select="$rowNum"/> );</xsl:attribute>
			</input>		
		</xsl:if>			
	</xsl:template>
   
</xsl:stylesheet>


