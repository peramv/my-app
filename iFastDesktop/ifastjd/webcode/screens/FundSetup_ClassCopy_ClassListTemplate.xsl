<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:template name="ClassList_Tmpl">		
		<xsl:param name="listSrc"/>
				
		<table id="classList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true">			
			<thead>
				<tr>	
					<td style="width:22;" columnWidth="22">
						<xsl:text>&#xa0;</xsl:text>
					</td>					
					<td style="width:75;" columnWidth="75">
						Exclude
					</td>
					<td style="width:100;" columnWidth="100">
						From Class
					</td>
					<td style="width:120;" columnWidth="120">
						New Class Code
					</td>
					<td style="width:100;" columnWidth="100">
						Effective Date
					</td>
					<td style="width:60;" columnWidth="60">
						ISIN
					</td>
					<td style="width:60;" columnWidth="60">
						CUSIP
					</td>
					<td style="width:120;" columnWidth="117">
						WKN Fund ID
					</td>
					<td style="width:160;" columnWidth="160">
						External Fund ID
					</td>
					<td style="width:160;" columnWidth="160">
						Fund Load Group
					</td>														
				</tr>
			</thead>					
			<tbody>
				<xsl:if test="$listSrc and count($listSrc/ClassInfo) &gt; 0">																
					<xsl:for-each select="$listSrc/ClassInfo">
						<tr ondblclick="dblclickHandler_classListRow()" onkeyup="test()">
							<xsl:attribute name="exclude">false</xsl:attribute>
							<xsl:attribute name="fromClassCode"><xsl:value-of select="classCode"/></xsl:attribute>									
							<xsl:attribute name="classCode"></xsl:attribute>
							<xsl:attribute name="deff"></xsl:attribute>
							<xsl:attribute name="isin"></xsl:attribute>
							<xsl:attribute name="cusip"></xsl:attribute>
							<xsl:attribute name="wkn"></xsl:attribute>
							<xsl:attribute name="extID"></xsl:attribute>
							<xsl:attribute name="fundLoadGrp"></xsl:attribute>																
							
							<td>								
							</td>
							<td>
								<input type="checkbox" onclick="clickHandler_excludeCheckbox( this )" ondblclick="event.cancelBubble=true;">
									<xsl:attribute name="rowNum"><xsl:value-of select="position() - 1"/></xsl:attribute>
								</input>								
							</td>							
							<td>
								<xsl:value-of select="classCode"/>
							</td>									
							<td></td>
							<td></td>
							<td></td>
							<td></td>
							<td></td>
							<td></td>
							<td></td>																					
						</tr>
					</xsl:for-each>											
				</xsl:if>
			</tbody>                			
		</table>
		     
	</xsl:template>	
   
</xsl:stylesheet>
