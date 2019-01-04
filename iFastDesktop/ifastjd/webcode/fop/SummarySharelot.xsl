<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="no"/>


	<xsl:template match="/">
		<html >
			<head>
				<title/>
			</head>
			<body>				
				<xsl:call-template name="tmpTitle">
				</xsl:call-template>
				<table >
				<tr><td align="left" width="200px">
				<xsl:call-template name="tmpGeneralInfo">
				</xsl:call-template>
				</td>
				<td width="250px" align="right"></td>
				<td align="right"  width="100px">
				<xsl:call-template name="tmpTransInfo">
				</xsl:call-template>
				</td>
				</tr>
				</table>
				
				<p><b>Summary sharelot</b></p>
				<xsl:call-template name="tmpSummarySharelot">
				</xsl:call-template>
				
				<p/>
				<p><b>Sharelot Details</b></p>
				<xsl:call-template name="tmpSharelotDetail">
				</xsl:call-template>
				
			</body>
			</html>
	</xsl:template>
	
	
	<xsl:template name="tmpTitle">


		<h2>Summary Sharelot for account <xsl:value-of select="//EntityHeaderInfo/entNm"/></h2>
		<p/>
		<table width="100%"><tr>
			<td align="left" width="10%">Fund : <xsl:value-of select="//SharelotInfoInit/fund"/> Class : <xsl:value-of select="//SharelotInfoInit/class"/>
			</td>
			<td width="80%"></td>
			<td width="10%">
			Sharelot Type : Performance Fee
			</td>
			</tr></table>
			<hr/>
	</xsl:template>
	
	<xsl:template name="tmpGeneralInfo">
	
		<p/>
		<table border="1" width="175px" cellpadding="2">
			<col width="90px"/>
			<col width="120px"/>
		<tr>
			<td align="left" >Valuation Date : </td>
			<td align="right" ><xsl:value-of select="//PerfFeeEvent/valuationDate"/></td>
			</tr><tr>
			<td align="left" >GAV : </td>
			<td align="right" ><xsl:value-of select="//PerfFeeEvent/GAV"/></td>
			</tr><tr>
			<td align="left">NAV : </td>
			<td align="right"><xsl:value-of select="//PerfFeeEvent/NAV"/></td>
			</tr><tr>
			<td align="left" >Unit Balance : </td>
			<td align="right" ><xsl:value-of select="//PerfFeeEvent/unitBalance"/></td>
			</tr><tr>
			<td align="left" >Value : </td>
			<td align="right" ><xsl:value-of select="//PerfFeeEvent/unitValue"/></td>
			</tr><tr>
			<td align="left" >Class HWM : </td>
			<td align="right" ><xsl:value-of select="//PerfFeeEvent/classHWM"/></td>
			</tr><tr>
			<td align="left" >Class Adj. HWM : </td>
			<td align="right" ><xsl:value-of select="//PerfFeeEvent/classAdjHWM"/></td>
			</tr></table>
			<p></p>
	</xsl:template>

	<xsl:template name="tmpTransInfo">
		
	
		<p/>
		<p/>
		<p/>
		<p/>
		<p/>
		
		<table border="1" cellpadding="2"  align="right"><tr>
			<td align="left" >Trans Type : </td>
			<td align="left" ><xsl:value-of select="//TransInfo/transType"/></td>
			</tr><tr>
			<td align="left">Trans Number : </td>
			<td align="left"><xsl:value-of select="//TransInfo/transNumber"/></td>
			</tr><tr>
			<td align="left">Trade Date : </td>
			<td align="left"><xsl:value-of select="//TransInfo/deff"/></td>
			</tr><tr>
			<td align="left">Units : </td>
			<td align="left"><xsl:value-of select="//TransInfo/units"/></td>
			</tr><tr>
			<td align="left">Amount : </td>
			<td align="left"><xsl:value-of select="//TransInfo/amount"/></td>
			</tr></table>
	</xsl:template>

	<xsl:template name="tmpSummarySharelot">
		
	
		<table border="1">
					<col width="100px"/>
					<col width="70px"/>
					<col width="70px"/>
					<col width="70px"/>
					<col width="80px"/>
					<col width="80px"/>
					<col width="70px"/>
			<thead border="1">
				<tr>
					<xsl:attribute name="bgcolor"><xsl:value-of select="'#A0A0A0'" /></xsl:attribute>
					<xsl:attribute name="fgcolor"><xsl:value-of select="'#FFFFFF'" /></xsl:attribute>
					<th >Original Trans Type</th>
					<th >Trade Date</th>
					<th >Original Units</th>
					<th >Unit Balance</th>
					<th >Value Balance</th>
					<th >Equilisation Potential Value</th>
					<th >Equilisation Market Value</th>
					<!-- 
					<td>Eq 1</td>
					<td>Eq 2</td>
					 -->
				</tr>
			</thead>
			<tbody border="1">
				<xsl:for-each select="//Sharelots/Sharelot">
				
					<tr>
						<xsl:choose>
						<xsl:when test="((position()-1) mod 2) = 1">
							<xsl:attribute name="bgcolor"><xsl:value-of select="'#F1F1F1'" /></xsl:attribute>
						</xsl:when>	
						</xsl:choose>				
						<td ><xsl:value-of select="originTransType"/></td>					
						<td ><xsl:value-of select="tradeDate"/></td>
						<td ><xsl:value-of select="origFundUnits"/></td>
						<td ><xsl:value-of select="unitBalAsofDate"/></td>
						<td ><xsl:value-of select="valueBalAsOfDate"/></td>
						<td ><xsl:value-of select="eqPotenValue"/></td>
						<td ><xsl:value-of select="eqMKTValue"/></td>
					</tr>
				</xsl:for-each>
			</tbody>
		</table>
	</xsl:template>
	
	
	
	<xsl:template name="tmpSharelotDetail">
		
		<xsl:variable name="lotID" select="//SharelotInfoInit/lotId"></xsl:variable>
		
		<table border="1" >
			<thead border="1">
				<tr>
					<xsl:attribute name="bgcolor"><xsl:value-of select="'#A0A0A0'" /></xsl:attribute>
					<xsl:attribute name="fgcolor"><xsl:value-of select="'#FFFFFF'" /></xsl:attribute>
					<th>Trans Number</th>
					<th>Trans Type</th>
					<th>Trade Date</th>
					<th>Settle Date</th>
					<th>Units</th>
					<th>Eq Amount</th>
				</tr>
			</thead>
			<xsl:for-each select="//Sharelots/Sharelot">
				<xsl:if test="string(lotID)=$lotID">
					<xsl:for-each select="TransDetls/TransDetl">
						<tbody border="1">
						<tr>
							<xsl:choose>
							<xsl:when test="((position()-1) mod 2) = 1">
								<xsl:attribute name="bgcolor"><xsl:value-of select="'#F1F1F1'" /></xsl:attribute>
							</xsl:when>	
							</xsl:choose>				
							<td><xsl:value-of select="transnumber"/></td>
							<td><xsl:value-of select="transType"/></td>					
							<td><xsl:value-of select="deff"/></td>
							<td><xsl:value-of select="settleDate"/></td>
							<td><xsl:value-of select="units"/></td>
							<td><xsl:value-of select="eqAmount"/></td>
						</tr>
						</tbody>
					
					</xsl:for-each>
				</xsl:if>
			</xsl:for-each>
		</table>
	</xsl:template>
</xsl:stylesheet>