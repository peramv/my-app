<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:template name="GrantContrib_Tmpl">
		<xsl:param name="sourceNode"/>
		
		<table id="GrantContrib_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
			<thead>
				<tr>															
					<td>
						<xsl:attribute name="style">width:180</xsl:attribute>
						<xsl:attribute name="columnWidth">180</xsl:attribute>
						Entity Name
					</td>
					<td>
						<xsl:attribute name="style">width:85</xsl:attribute>
						<xsl:attribute name="columnWidth">85</xsl:attribute>
						Trans ID
					</td>
					<td>
						<xsl:attribute name="style">width:85</xsl:attribute>
						<xsl:attribute name="columnWidth">85</xsl:attribute>
						HRDC Trans ID
					</td>
					<td>
						<xsl:attribute name="style">width:88</xsl:attribute>
						<xsl:attribute name="columnWidth">88</xsl:attribute>
						Trade Date
					</td>	
					<td>
						<xsl:attribute name="style">width:50</xsl:attribute>
						<xsl:attribute name="columnWidth">50</xsl:attribute>
						Trans Type
					</td>	
					<td>
						<xsl:attribute name="style">width:120</xsl:attribute>
						<xsl:attribute name="columnWidth">120</xsl:attribute>
						Red/Dep Code
					</td>	
					<td>
						<xsl:attribute name="style">width:79</xsl:attribute>
						<xsl:attribute name="columnWidth">79</xsl:attribute>
						UC Amount
					</td>																						
					<td>
						<xsl:attribute name="style">width:79</xsl:attribute>
						<xsl:attribute name="columnWidth">79</xsl:attribute>
						AC Amount
					</td>
					<td>
						<xsl:attribute name="style">width:79</xsl:attribute>
						<xsl:attribute name="columnWidth">79</xsl:attribute>
						Gross Amount
					</td>
					<td>
						<xsl:attribute name="style">width:79</xsl:attribute>
						<xsl:attribute name="columnWidth">79</xsl:attribute>
						Grant Amount
					</td>
					<td>
						<xsl:attribute name="style">width:79</xsl:attribute>
						<xsl:attribute name="columnWidth">79</xsl:attribute>
						Received Grant
					</td>
				</tr>
			</thead>
			<tbody>
				<xsl:for-each select="$sourceNode/GrantContributionInfo/GrantContribRec">
					<tr>
						<xsl:attribute name="transID"><xsl:value-of select="transID"/></xsl:attribute>
						<xsl:attribute name="entityID"><xsl:value-of select="entityID"/></xsl:attribute>
						
						<td><xsl:value-of select="entName"/></td>
						<td><xsl:value-of select="transID"/></td>
						<td><xsl:value-of select="hrdcTransID"/></td>
						<td><xsl:value-of select="tradeDt"/></td>
						<td><xsl:value-of select="transType"/></td>
						<td><xsl:value-of select="redDepCode"/></td>
						<td><xsl:value-of select="ucAmt"/></td>
						<td><xsl:value-of select="acAmt"/></td>
						<td><xsl:value-of select="grossAmt"/></td>
						<td><xsl:value-of select="grantAmt"/></td>
						<td><xsl:value-of select="rcvdAmt"/></td>
					</tr>						
				</xsl:for-each>
			</tbody>					
		</table>			
	</xsl:template>
	
</xsl:stylesheet>
