<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="no"/>

<xsl:variable name="basePath" select="//basePath"/>
<xsl:variable name="clientDir" select="//clientdir"/>
<xsl:variable name="dataDir" select="//datadir"/>
<xsl:variable name="response" select="//Valn"/>

	<xsl:template match="/">
		<html >
			<head>
				<title/>
			</head>
			<body>
				<xsl:call-template name="tmpTitle">
				</xsl:call-template>
				<table >
					<col width="250px"/>
					<col width="40px"/>
					<col width="250px"/>		
				
				<tr><td align="left" >
				<xsl:call-template name="tmpGeneralInfoLeft">
				</xsl:call-template>
				</td>
				
				<td align="right" width="40px"></td>
				
				<td align="right" >
				<xsl:call-template name="tmpGeneralInfoRight">
				</xsl:call-template>
				</td>
				</tr>
				</table>
				
				<p><b>Hurdle Details:</b></p>
				<xsl:call-template name="tmpHurdleDetails"></xsl:call-template>
				<p/>
				<xsl:if test="//Valn/CrysDetl/crysStatus">
				<p><b>PF Crystalisation Details</b></p>
				<xsl:call-template name="tmpCrystalizationInfo"></xsl:call-template>
				</xsl:if>
			
				<p/>
				<p/>
				<p><b>PF Calculation Details</b></p>
				<xsl:call-template name="tmpCalculationDetails">
				</xsl:call-template>

			</body>
			</html>
	</xsl:template>
	
	
	<xsl:template name="tmpTitle">
	
		<h2>Valuation Details</h2>
		<p/>
		<table >
			<tr>
			<td align="left" >
			 Fund : <xsl:value-of select="//dtValnDetlReloadResponse/fund"/>
 			 Class : <xsl:value-of select="//dtValnDetlReloadResponse/class"/>
 			</td>
			</tr></table>
			<hr/>
	</xsl:template>
	
	<xsl:template name="tmpGeneralInfoLeft">
		<p/>
		<table border="1"  cellpadding="2">

		<col width="125px"/>
		<col width="100px"/>		
		<tr>
			<td   align="left" >Valuation Date : </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/valnDate"/></td>
			</tr><tr>
			<td  align="left" >GAV : </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/gav"/></td>
			</tr><tr>
			<td  align="left">Dividend Adjusted GAV<sup>1</sup> : </td>
			<td width="50px" align="right"><xsl:value-of select="//Valn/divAdjGav"/></td>
			</tr><tr>
			<td  align="left" >NAV<sup>2</sup> : </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/nav"/></td>
			</tr><tr>
			<td  align="left" >Performance Fee per share<sup>3</sup> : </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/pfPerShare"/></td>
			</tr>
			
			<tr>
			<td  align="left" >Class HWM: </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/clsHWM"/></td>
			</tr>
			<tr>
			<td  align="left" >Class HWM Date: </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/clsHWMDate"/></td>
			</tr>
			<tr>
			<td  align="left" >Number of Days since HWM Reset : </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/numDays"/></td>
			</tr><tr>
			<td  align="left" >Effective Hurdle<sup>5</sup> : </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/effHurdle"/></td>
			</tr><tr>
			<td  align="left" >Class Adjusted HWM<sup>4</sup> : </td>
			<td width="50px" align="right" ><xsl:value-of select="//Valn/clsAdjHWM"/></td>
			</tr></table>
			<p></p>
	</xsl:template>

	<xsl:template name="tmpGeneralInfoRight">
		<p/>
		<table border="1" cellpadding="2"  align="right">
		<col width="150px"/>
		<col width="100px"/>		
		
		<tr>
			<td align="left" >Crystalisation Date : </td>
			<td align="left" ><xsl:value-of select="//Valn/crysFlag"/></td>
			</tr><tr>
			<td align="left">Distribution Date : </td>
			<td align="left"><xsl:value-of select="//Valn/distFlag"/></td>
			</tr><tr>
			<td align="left">Dividend Rate : </td>
			<td align="left"><xsl:value-of select="//Valn/distRate"/></td>
			</tr><tr>
			<td align="left">Calculation Basis : </td>
			<td align="left"><xsl:value-of select="//Valn/calcBasis"/></td>
			</tr><tr>
			<td align="left">Loss Carry Forward Option : </td>
			<td align="left"><xsl:value-of select="//Valn/lossCarrFwOptn"/></td>

			</tr><tr>
			<td align="left">Dividend Treatment Option : </td>
			<td align="left"><xsl:value-of select="//Valn/divTreatOptn"/></td>

			</tr><tr>
			<td align="left">Calculation Precision : </td>
			<td align="left"><xsl:value-of select="//Valn/calcPrec"/></td>

			</tr><tr>
			<td align="left">Performance Fee Precision : </td>
			<td align="left"><xsl:value-of select="//Valn/pfPrec"/></td>
			</tr><tr>
			<td align="left">Status : </td>
			<td align="left"><xsl:value-of select="//Valn/valStatus"/></td>
			</tr></table>
	</xsl:template>

	<xsl:template name="tmpHurdleDetails">
		<table border="1">
					<col width="50px"/>
					<col width="90px"/>
					<col width="90px"/>
					<col width="70px"/>
					<col width="90px"/>
					<col width="50px"/>
					<col width="80px"/>
			<thead border="1">
				<tr>
					<xsl:attribute name="bgcolor"><xsl:value-of select="'#A0A0A0'" /></xsl:attribute>
					<xsl:attribute name="fgcolor"><xsl:value-of select="'#FFFFFF'" /></xsl:attribute>
					<th width="50px">Index</th>
					<th width="90px">Fix Rate/Hurdle</th>
					<th width="90px">Benchmark Adj. Rate</th>
					<th width="70px">Weighting</th>
					<th width="90px">Period</th>
					<th width="50px">Number of Days</th>
					<th width="80px">Day Basis</th>
				</tr>
			</thead>
			<tbody border="1">
				<xsl:for-each select="//Valn/Hurdles/Hurdle">
				
					<tr>
						<xsl:choose>
						<xsl:when test="((position()-1) mod 2) = 1">
							<xsl:attribute name="bgcolor"><xsl:value-of select="'#F1F1F1'" /></xsl:attribute>
						</xsl:when>	
						</xsl:choose>				
						<td width="50"><xsl:value-of select="index"/></td>					
						<td width="90"><xsl:value-of select="fixRate"/></td>
						<td width="90"><xsl:value-of select="benchmark"/></td>
						<td width="70"><xsl:value-of select="weighting"/></td>
						<td width="90"><xsl:value-of select="period"/></td>
						<td width="50"><xsl:value-of select="numDays"/></td>
						<td width="80"><xsl:value-of select="dayBasis"/></td>
					</tr>
				</xsl:for-each>
			</tbody>
		</table>
	</xsl:template>
	
	
	
		<xsl:template name="tmpCrystalizationInfo">
			<table border="1" cellpadding="2"  align="right">
				<col width="150px"/>
				<col width="100px"/>		
		
				<tr>
					<td align="left" >New Class HWM<sup>6</sup> : </td>
					<td align="left" ><xsl:value-of select="//Valn/CrysDetl/newClsHWM"/></td>
					
					<td align="right" >Total number of EQ purchase txn created: </td>
					<td align="left" ><xsl:value-of select="//Valn/CrysDetl/totEqPurTxn"/></td>
				</tr>
				
				<tr>
					<td align="left" >Value of EQ Credits : </td>
					<td align="left" ><xsl:value-of select="//Valn/CrysDetl/valEqCr"/></td>
					
					<td align="right" >Total number of EQ redemption txn created: </td>
					<td align="left" ><xsl:value-of select="//Valn/CrysDetl/totEqRedTxn"/></td>
				</tr>

				<tr>
					<td align="left" >Value of EQ Redemption : </td>
					<td align="left" ><xsl:value-of select="//Valn/CrysDetl/valEqRed"/></td>
					
					<td align="right" >Total Performance Fee Amount<sup>7</sup> : </td>
					<td align="left" ><xsl:value-of select="//Valn/CrysDetl/totPfAmt"/></td>
				</tr>
				
				<tr>
					<td align="left" >Status : </td>
					<td align="left" ><xsl:value-of select="//Valn/CrysDetl/crysStatus"/></td>
					
					<td align="right" > </td>
					<td align="left" > </td>
				</tr>
				
			</table>
			
		</xsl:template>
		
		<xsl:template name="tmpCalculationDetails">
		
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description">Dividend Adjusted GAV</xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//Valn/divAdjGavFML" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//Valn/divAdjGavFMLval" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">1</xsl:with-param>
			  </xsl:call-template>

			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description">NAV</xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//Valn/navFML" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//Valn/navFMLval" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">2</xsl:with-param>
			  </xsl:call-template>

			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description">Performance Fee per share</xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//Valn/pfPerShareFML" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//Valn/pfPerShareFMLval" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">3</xsl:with-param>
			  </xsl:call-template>
			  
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description">Class Adjusted HWM</xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//Valn/clsAdjHWMFML" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//Valn/clsAdjHWMFMLval" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">4</xsl:with-param>
			  </xsl:call-template>


			 <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description">Effective Hurdle</xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//Valn/effHurdleFML" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//Valn/effHurdleFMLval" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">5</xsl:with-param>				  	
			  </xsl:call-template>

			  <xsl:if test="//Valn/CrysDetl/crysStatus">
  			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description">New Class HWM:</xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//Valn/CrysDetl/newClsHWMFML" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//Valn/CrysDetl/newClsHWMFMLval" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">6</xsl:with-param>
			  </xsl:call-template>

			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description">Total Performance Fee Amount:</xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of  select="//Valn/CrysDetl/totPfAmtFML" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//Valn/CrysDetl/totPfAmtFMLval" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">7</xsl:with-param>
			  </xsl:call-template>
			  
			</xsl:if>

			<!-- Combine from table
			 			  
			  <p><b>Effective Hurdle</b><sup><font size="1">5</font></sup></p>
			  <xsl:for-each select="//Hurdles/Hurdle">
				  <xsl:call-template name="tmplDisplayCalculationDetail">
				  	<xsl:with-param name="form"><xsl:value-of select="hurdleDetlFML" /></xsl:with-param>
				  	<xsl:with-param name="value"><xsl:value-of select="hurdleDetlFMLval" /></xsl:with-param>				  	
				  </xsl:call-template>
			  </xsl:for-each>
			-->	
		</xsl:template>
		
		<xsl:template name="tmplDisplayCalculationDetail">
			<xsl:param name="description" select="''"></xsl:param>
			<xsl:param name="form"></xsl:param>
			<xsl:param name="value"></xsl:param>
			<xsl:param name="footnoteNumber" select="''"></xsl:param>
				<p>
				<b><xsl:value-of select="$description"/></b><xsl:if test=" not ($footnoteNumber = '')"><sup><font size="1"><xsl:value-of select="$footnoteNumber"/></font></sup></xsl:if>
				<blockquote>
					<xsl:value-of select="$form"/><pre>
					</pre>
					<xsl:value-of select="$value"/>
				</blockquote>
				</p>
				
		</xsl:template>
</xsl:stylesheet>