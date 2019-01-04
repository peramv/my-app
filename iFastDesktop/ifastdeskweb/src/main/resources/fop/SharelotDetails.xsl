<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" omit-xml-declaration="no"/>

<xsl:variable name="basePath" select="//basePath"/>
<xsl:variable name="clientDir" select="//clientdir"/>
<xsl:variable name="dataDir" select="//datadir"/>
<xsl:variable name="imagesDir">
	<xsl:value-of select="//basePath"/>
	<xsl:value-of select="'..'"/>
	<xsl:value-of select="//clientdir"/>
	<xsl:value-of select="'images/'"/>
</xsl:variable>
<xsl:variable name="responseNode" select="//sharelotDetailsResponse"/>

	<xsl:template match="/">
		<html >
			<head>
				<title/>
			</head>
			<body>
				<xsl:call-template name="tmpTitle">
				</xsl:call-template>
				<p/>
				<xsl:call-template name="tmplClassLevelValues">
				</xsl:call-template>
				<p/>
				<p/>
				<h6>Share Lots Values</h6>
				<table >
					<col width="250px"/>
					<col width="250px"/>
				
				<tr><td align="left" >
				<xsl:call-template name="tmpGeneralInfoLeft">
				</xsl:call-template>
				</td>
				
				<td align="right" width="40px">
				<xsl:call-template name="tmpGeneralInfoCenter">
				</xsl:call-template>
				</td>
				</tr>
				</table>
				<p/>
				<table >
					<col width="250px"/>
				<tr><td align="left" >
				<xsl:call-template name="tmpGeneralInfoRight">
				</xsl:call-template>
				</td></tr>
				</table>
									
				<xsl:call-template name="tmplSharelotTable">
				</xsl:call-template>
				<xsl:if test="//SharelotDetail/Crystallization/transNumber">
				<p><b>PF Crystalisation-Equalisation Information</b></p>
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
	
		<h2>Sharelot Details</h2>
		<p/>
		<table width="500px">
			<col width="50px"/>
			<col width="50px"/>
			<col width="50px"/>
			<col width="50px"/>
			<col width="50px"/>
			<col width="250px"/>
			<tr>
			<td align="left" >			
			<b>Trans #</b></td><td> <xsl:value-of select="//SharelotDetail/transNumber"/>,
			</td>
			<td align="left" >
			<b>Acct #</b></td><td><xsl:value-of select="//acctNum"/>
			</td>
			<td align="left" >
			<b>Name #</b></td><td><xsl:value-of select="//EntityHeaderInfo/entNm"/>
 			</td>
			</tr></table>
			<hr/>
	</xsl:template>
	
	<xsl:template name="tmplClassLevelValues">
		<h6>Class Level Values (Pre PF Crystallisation)</h6>
		<table border="0"  cellpadding="2">
		<col width="150px"/>
		<col width="150px"/>
		<col width="150px"/>
				
		<tr><td align="left">GAV : <xsl:value-of select="$responseNode/SharelotDetail/ClassPreCrys/gav"/></td>
			<td align="center"  >NAV : <xsl:value-of select="$responseNode/SharelotDetail/ClassPreCrys/nav"/></td>
			<td align="right">Performance per share : <xsl:value-of select="$responseNode/SharelotDetail/ClassPreCrys/perfFeePerShare"/></td>
		</tr>
		</table>
		
	</xsl:template>
		<xsl:template name="tmpGeneralInfoCenter">
		<table border="1"  cellpadding="2">
		<col width="100px"/>
		<col width="130px"/>	
<!-- 
 			<tr><td class="FieldLabel" align="left">Original Units</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/origUnits"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Change</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/unitChange"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Opening Unit Balance</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/unitBalPreCrys"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Lot HWM<sup>10</sup></td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/lotHWM"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Lot HWM Date</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/lotHWMDate"/></td></tr>
 -->
 			<tr><td class="FieldLabel" align="left">Lot HWM<xsl:if test="//ShareLotCalcDetail/LotHWM"><sup>12</sup></xsl:if></td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/lotHWM"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Lot HWM Date</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/lotHWMDate"/></td></tr>
			<tr><td class="FieldLabel" align="left">Lot effective hurdle<sup>2</sup></td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/lotEffHurdle"/></td></tr> 			
			<tr><td class="FieldLabel" align="left">Lot Adj. HWM<sup>1</sup></td><td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/lotAdjHWM" /></td></tr>
			

		</table>
	</xsl:template>
	
	<xsl:template name="tmpGeneralInfoLeft">
		<table border="1"  cellpadding="2">
		<col width="120px"/>
		<col width="120px"/>	
 			<tr><td class="FieldLabel" align="left">Original Units</td><td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/origUnits"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Change</td><td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/unitChange"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Opening Unit Balance</td><td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/unitBalPreCrys"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Closing Unit Balance</td><td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/unitBalPostCrys"/></td></tr>
 			<tr><td class="FieldLabel" align="left">Number of Days since HWM</td><td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/noOfDaysValn"/></td></tr>
<!-- 
 			<tr><td class="FieldLabel" align="left">Number of days to VD</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/noOfDaysValn"/></td></tr>
			<tr><td class="FieldLabel" align="left">Lot effective hurdle</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/lotEffHurdle"/></td></tr> 			
			<tr><td class="FieldLabel" align="left">Lot Adj. HWM</td><td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/lotAdjHWM" /></td></tr> 			
			<tr><td class="FieldLabel" align="left">New Lot HWM</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/newLotHWM"/></td></tr> 			
 -->
		</table>
	</xsl:template>

	<xsl:template name="tmpGeneralInfoRight">
		<table border="1"  cellpadding="2">
		<col width="75px"/>
		<col width="95px"/>
		<col width="117px"/>		
		<col width="110px"/>				
 			<tr><td class="FieldLabel" align="left">Valuation Date</td>
 			<td  class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/valuationDate"/>
 			</td>
 			<td class="FieldLabel"  align="left">Trans Type</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/transType"/></td>
 			</tr>
 			<tr><td class="FieldLabel" align="left">Trans Number</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/transNumber"/></td>
 			<td class="FieldLabel" align="left">Trade Date</td><td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/tradeDate"/></td></tr>
		</table>
	</xsl:template>

	<xsl:template name="tmplSharelotTable">
			<p/>
			<table border="1" cellpadding="2" cellspacing="0" width="400px">
			<col width="150px"/>
			<col width="100px"/>
			<col width="100px"/>
			
			<tr>
			<td style="width:150px" class="FieldLabel"></td>
			<td align="center" class="FieldLabel" ><b>Per Share</b></td>
			<td align="center" class="FieldLabel" ><b>Total</b></td>
			</tr>
			<tr>
			  <td class="FieldLabel">Lot Total PF Payable</td>
			  <td  align="center" class="FieldData" style="margin-right:2cm;">-</td>
			  <td  align="center" class="FieldData" style="margin-right:2cm;">
				 <xsl:value-of select="//SharelotDetail/lotTTPayPerTotal"/><sup>8</sup>
			  </td>
			</tr>
			<tr>
			  <td class="FieldLabel">Lot Class PF<sup>11</sup></td>
			  <td  align="center" class="FieldData" >-</td>
			  <td  align="center" class="FieldData" >
				 <xsl:value-of select="//SharelotDetail/lotClsTotal"/>			 
			</td>
			</tr>
			<tr>
			  <td    class="FieldLabel">Lot EQmv</td>
			  <td  align="center" class="FieldData" >
 				<xsl:value-of select="//SharelotDetail/lotEQmvPer"/><sup>3</sup>	
			   </td>
			  <td  align="center" class="FieldData" >
 				<xsl:value-of select="//SharelotDetail/lotEQmvTotal"/><sup>4</sup>
			  </td>
			</tr>
			<tr>
			  <td   class="FieldLabel">Lot EQpot</td>
			  <td  align="center" class="FieldData" >
 				<xsl:value-of select="//SharelotDetail/lotEQpotPer"/><sup>5</sup>	
			   </td>
			  <td  align="center" class="FieldData" >
 				<xsl:value-of select="//SharelotDetail/lotEQpotTotal"/><sup>6</sup>
			  </td>
			</tr>
			<tr>
			  <td class="FieldLabel">EQ Lost /Carried Forward</td>
			  <td  align="center" class="FieldData" >-</td>
			  <td  align="center" class="FieldData" >
 				<xsl:value-of select="//SharelotDetail/eQLostTotal"/>	
			  </td>
			</tr>
			<tr>
			  <td class="FieldLabel">Lot PF/Share</td>
			  <td  align="center" class="FieldData" >
			 	<xsl:value-of select="$responseNode/SharelotDetail/lotPFShare"/><sup>7</sup>
			  </td>
			  <td  align="center" class="FieldData" ></td>
			</tr>
			</table>
			
			<p/>
			
			<table width="400px">
			<col width="100px"/>
			<col width="100px"/>
			<col width="100px"/>
			<col width="100px"/>
			<tr>
			  <td class="FieldLabel">Lot Share Value:</td>
			  <td class="FieldData" align="right">
 				<xsl:value-of select="//SharelotDetail/lotShareValue"/><sup>9</sup>	
			  </td>
			  <td class="FieldLabel" align="right">Total Lot Value:</td>
			  <td class="FieldData" align="right">
 				<xsl:value-of select="//SharelotDetail/totLotValue"/><sup>10</sup>
			  </td>
			  
			</tr>
		</table> 	
	
	</xsl:template>
	
		<xsl:template name="tmpCrystalizationInfo">

 			<table border="0" cellpadding="2" cellspacing="0" width="100%">
 				<col width="100px"/>
 				<col width="100px"/>
 				<col width="100px"/>
 				<col width="100px"/>
 				<col width="100px"/>
 				<tr>
 					<td class="FieldLabel">Equalisation Amount</td>
 					<td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/Crystallization/eqAmount"/></td>
 					<td style="width:190px;" class="FieldLabel"></td>
 					
 					<td class="FieldLabel">New Lot HWM<xsl:if test="//ShareLotCalcDetail/LotResetHWM"><sup>13</sup></xsl:if></td>
 					<td class="FieldData"  align="right"><xsl:value-of select="//SharelotDetail/Crystallization/newLotHWM"/></td>
 					
			<!--  			
			<tr><td class="FieldLabel" align="left">New Lot HWM<xsl:if test="//ShareLotCalcDetail/NewLotHWMCalc"><sup>10</sup></xsl:if></td>
			<td class="FieldData" align="right"><xsl:value-of select="$responseNode/SharelotDetail/newLotHWM"/></td></tr>
			 --> 			
 					
 				</tr>
 				<tr>
 					<td class="FieldLabel">Transaction Type</td>
 					<td class="FieldData"  align="right"><xsl:value-of select="//SharelotDetail/Crystallization/transType"/></td>
 					<td style="width:190px;" class="FieldLabel"></td>
 					<td class="FieldLabel"> Trans Number</td>
 					<td class="FieldData" align="right"><xsl:value-of select="//SharelotDetail/Crystallization/transNumber"/></td>
 				</tr>
 				<tr>
 					<td class="FieldLabel" width="20%">NAV</td>
 					<td class="FieldData"  align="right"><xsl:value-of select="//SharelotDetail/Crystallization/nav"/></td>
 					<td style="width:190px;" class="FieldLabel"></td>
 					<td class="FieldLabel" width="20%">Number of units</td>
 					<td  align="right" class="FieldData"><xsl:value-of select="//SharelotDetail/Crystallization/units"/></td>
 				</tr>
 			</table>

			
		</xsl:template>
		
		<xsl:template name="tmpCalculationDetails">

<!-- 		
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/ClassPFsh/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/ClassPFsh/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/ClassPFsh/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">1</xsl:with-param>
			  </xsl:call-template>
 -->
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotAdjHWM/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotAdjHWM/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotAdjHWM/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">1</xsl:with-param>
			  </xsl:call-template>

			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotEffHurdle/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotEffHurdle/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotEffHurdle/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">2</xsl:with-param>
			  </xsl:call-template>
			  
			  
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotEQmvsh/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotEQmvsh/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotEQmvsh/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">3</xsl:with-param>
			  </xsl:call-template>
			  
			  
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotEQmvAmt/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotEQmvAmt/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotEQmvAmt/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">4</xsl:with-param>
			  </xsl:call-template>
			  
			  
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotEQpotsh/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotEQpotsh/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotEQpotsh/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">5</xsl:with-param>
			  </xsl:call-template>
			  		  
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotEQpotAmt/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotEQpotAmt/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotEQpotAmt/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">6</xsl:with-param>
			  </xsl:call-template>
			  
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotPFsh/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotPFsh/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotPFsh/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">7</xsl:with-param>
			  </xsl:call-template>
			  
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotTotPFAmt/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotTotPFAmt/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotTotPFAmt/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">8</xsl:with-param>
			  </xsl:call-template>
			  
		  	<xsl:if test="//ShareLotCalcDetail/LotPFsh">
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotShareAmt/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotShareAmt/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotShareAmt/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">9</xsl:with-param>
			  </xsl:call-template>
		  	</xsl:if>

		  	<xsl:if test="//ShareLotCalcDetail/TotalLoteAmt">
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/TotalLoteAmt/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/TotalLoteAmt/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/TotalLoteAmt/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">10</xsl:with-param>
			  </xsl:call-template>
		  	</xsl:if>

		  	<xsl:if test="//ShareLotCalcDetail/LotClPFAmt">
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotClPFAmt/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotClPFAmt/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotClPFAmt/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">11</xsl:with-param>
			  </xsl:call-template>
		  	</xsl:if>

		  	<xsl:if test="//ShareLotCalcDetail/LotHWM">
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotHWM/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotHWM/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotHWM/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">12</xsl:with-param>
			  </xsl:call-template>
		  	</xsl:if>
			    
	
  			<xsl:if test="//ShareLotCalcDetail/LotResetHWM">
			  <xsl:call-template name="tmplDisplayCalculationDetail">
			  	<xsl:with-param name="description"><xsl:value-of select="//ShareLotCalcDetail/LotResetHWM/description" /></xsl:with-param>
			  	<xsl:with-param name="form"><xsl:value-of select="//ShareLotCalcDetail/LotResetHWM/form" /></xsl:with-param>
			  	<xsl:with-param name="value"><xsl:value-of select="//ShareLotCalcDetail/LotResetHWM/value" /></xsl:with-param>
			  	<xsl:with-param name="footnoteNumber">13</xsl:with-param>
			  </xsl:call-template>
		  	</xsl:if>
			  				
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