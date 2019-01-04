<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:template name="ClassList_Tmpl">		
		<xsl:param name="resultsSrc"/>
		
		<table id="ClassList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
			<thead>
				<tr>						
					<td>
						<xsl:attribute name="style">width:80</xsl:attribute>
						<xsl:attribute name="columnWidth">80</xsl:attribute>					
						Class
					</td>
					<td>
						<xsl:attribute name="style">width:120</xsl:attribute>
						<xsl:attribute name="columnWidth">120</xsl:attribute>
						Effective Date
					</td>
					<td>
						<xsl:attribute name="style">width:110</xsl:attribute>
						<xsl:attribute name="columnWidth">110</xsl:attribute>
						ISIN
					</td>
					<td>
						<xsl:attribute name="style">width:110</xsl:attribute>
						<xsl:attribute name="columnWidth">110</xsl:attribute>
						CUSIP
					</td>
					<td>
						<xsl:attribute name="style">width:129</xsl:attribute>
						<xsl:attribute name="columnWidth">129</xsl:attribute>
						WKN Fund ID
					</td>
					<td>
						<xsl:attribute name="style">width:130</xsl:attribute>
						<xsl:attribute name="columnWidth">130</xsl:attribute>
						External Fund ID
					</td>
					<td>
						<xsl:attribute name="style">width:180</xsl:attribute>
						<xsl:attribute name="columnWidth">180</xsl:attribute>
						Fund Load Group
					</td>			
				</tr>
			</thead>					
			<tbody>
				<xsl:choose>
					<xsl:when test="$resultsSrc">
						<xsl:if test="count($resultsSrc/Classes/ClassInfo) &gt; 0">												
							<xsl:for-each select="$resultsSrc/Classes/ClassInfo">
								<tr>
									<xsl:attribute name="classCode"><xsl:value-of select="classCode"/></xsl:attribute>
																	
									<td><xsl:value-of select="classCode"/></td>										
									<td><xsl:value-of select="dateEff"/></td>
									<td><xsl:value-of select="isin"/></td>
									<td><xsl:value-of select="cusip"/></td>
									<td><xsl:value-of select="wkn"/></td>
									<td><xsl:value-of select="extFundId"/></td>
									<td><xsl:value-of select="fundLoadGrp"/></td>									
								</tr>								
							</xsl:for-each>
						</xsl:if>						
					</xsl:when>					
				</xsl:choose>				      
			</tbody>                			
		</table>
		     
	</xsl:template>	
   
</xsl:stylesheet>
