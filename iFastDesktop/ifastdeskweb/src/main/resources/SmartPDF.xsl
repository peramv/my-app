<?xml version="1.0"  encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
	<xsl:output method="html" encoding="ISO-8859-1" indent="no"/>
	<xsl:template match="/">
		<fo:root>
			<fo:layout-master-set>
				<xsl:if test="/SmartPDF/layout/simple-page-master">
					<fo:simple-page-master>
					<xsl:if test="/SmartPDF/layout/simple-page-master/page-height!=''">
						<xsl:attribute name="page-height"><xsl:value-of select="/SmartPDF/layout/simple-page-master/page-height"/></xsl:attribute>
					</xsl:if>
					<xsl:if test="/SmartPDF/layout/simple-page-master/page-width!=''">
						<xsl:attribute name="page-width"><xsl:value-of select="/SmartPDF/layout/simple-page-master/page-width"/></xsl:attribute>
					</xsl:if>
					<xsl:if test="/SmartPDF/layout/simple-page-master/margin-left!=''">
						<xsl:attribute name="margin-left"><xsl:value-of select="/SmartPDF/layout/simple-page-master/margin-left"/></xsl:attribute>
					</xsl:if>
					<xsl:if test="/SmartPDF/layout/simple-page-master/margin-top!=''">
						<xsl:attribute name="margin-top"><xsl:value-of select="/SmartPDF/layout/simple-page-master/margin-top"/></xsl:attribute>
					</xsl:if>
					<xsl:if test="/SmartPDF/layout/simple-page-master/margin-right!=''">
						<xsl:attribute name="margin-right"><xsl:value-of select="/SmartPDF/layout/simple-page-master/margin-right"/></xsl:attribute>
					</xsl:if>
					<xsl:if test="/SmartPDF/layout/simple-page-master/margin-bottom!=''">
						<xsl:attribute name="margin-bottom"><xsl:value-of select="/SmartPDF/layout/simple-page-master/margin-bottom"/></xsl:attribute>
					</xsl:if>
				
						<xsl:attribute name="master-name"><xsl:value-of select="/SmartPDF/layout/simple-page-master/master-name"/></xsl:attribute>
						<xsl:if test="/SmartPDF/layout/region-body">
							<fo:region-body>
								<!-- xsl:if test="/SmartPDF/layout/region-body/margin">
									<xsl:attribute name="margin"><xsl:value-of select="/SmartPDF/layout/region-body/margin"/></xsl:attribute>
								</xsl:if -->
							</fo:region-body>
						</xsl:if>
						<xsl:if test="/SmartPDF/layout/region-before">
							<fo:region-before>
								<xsl:if test="/SmartPDF/layout/region-before/margin">
									<xsl:attribute name="margin"><xsl:value-of select="/SmartPDF/layout/region-before/margin"/></xsl:attribute>
								</xsl:if>
							</fo:region-before>
						</xsl:if>
						<xsl:if test="/SmartPDF/layout/region-after">
							<fo:region-after>
								<xsl:if test="/SmartPDF/layout/region-after/margin">
									<xsl:attribute name="margin"><xsl:value-of select="/SmartPDF/layout/region-after/margin"/></xsl:attribute>
								</xsl:if>
							</fo:region-after>
						</xsl:if>
					</fo:simple-page-master>
				</xsl:if>
			</fo:layout-master-set>
			<xsl:for-each select="/SmartPDF/page">
				<fo:page-sequence>
					<xsl:attribute name="master-reference"><xsl:value-of select="pagename"/></xsl:attribute>
					<fo:flow>
						<xsl:attribute name="flow-name"><xsl:value-of select="section-name"/></xsl:attribute>
						<xsl:for-each select="section">
							
								<!--                                <xsl:call-template name="tmplFontAttributes"/>-->
								<xsl:for-each select="control">
									<xsl:call-template name="tmplControlSelector"/>
								</xsl:for-each>
							
						</xsl:for-each>
					</fo:flow>
				</fo:page-sequence>
			</xsl:for-each>
		</fo:root>
	</xsl:template>
	<xsl:template name="tmplControlSelector">
		<xsl:if test="type = 'table'">
		<fo:block>	<xsl:call-template name="tmplTable"/></fo:block>
		</xsl:if>
		<xsl:if test="type = 'text'">
				<xsl:call-template name="tmplText"/>
		</xsl:if>
		<xsl:if test="type = 'multi-line'">
			<fo:block>	<xsl:call-template name="tmplMultiLine"/></fo:block>
		</xsl:if>
		<xsl:if test="type = 'concatenate'">
				<xsl:call-template name="tmplConcatenate"/>
		</xsl:if>
		<xsl:if test="type = 'image'">
			<xsl:call-template name="tmplImage"/>
		</xsl:if>
	</xsl:template>
	<xsl:template name="tmplMultiLine">
		<fo:block-container>
			<xsl:if test="position != ''">
				<xsl:attribute name="position"><xsl:value-of select="position"/></xsl:attribute>
			</xsl:if>
			<xsl:call-template name="tmplPositionAttributes"/>
			<xsl:for-each select="control">
				<xsl:call-template name="tmplControlSelector"/>
			</xsl:for-each>
		</fo:block-container>
	</xsl:template>
	<xsl:template name="tmplConcatenate">
		<fo:block-container>
			<xsl:if test="position != ''">
				<xsl:attribute name="position"><xsl:value-of select="position"/></xsl:attribute>
			</xsl:if>
			<xsl:call-template name="tmplPositionAttributes"/>
			<fo:block>
			<xsl:call-template name="tmplFontAttributes"/>
			<fo:inline>
			<xsl:for-each select="control"> 
					<xsl:value-of select="defaultValue" disable-output-escaping="yes"/><xsl:text disable-output-escaping="yes"><![CDATA[    ]]></xsl:text>
			</xsl:for-each>
			</fo:inline>
			</fo:block>
		</fo:block-container>
	</xsl:template>
	
	<xsl:template name="tmplTable">
		<fo:block-container>
			<xsl:if test="position != ''">
				<xsl:attribute name="position">absolute</xsl:attribute>
			</xsl:if>
			<xsl:call-template name="tmplPositionAttributes"/>
			<fo:block>
				<fo:table-and-caption>
					<fo:table>
						<xsl:call-template name="tmplPositionAttributes"/>
						<xsl:call-template name="tmplFontAttributes"/>
						<xsl:for-each select="columnWidths/col">
							<fo:table-column>
								<xsl:attribute name="column-width">
									<xsl:value-of select="@width"/>
								</xsl:attribute>
								<xsl:attribute name="text-align">
									<xsl:value-of select="@header-text-align"/>
								</xsl:attribute>
							</fo:table-column>
						</xsl:for-each>
						<fo:table-header>
						<xsl:for-each select="columnWidths/col">
							<xsl:variable name="nameOfField" select="@name"/>
							<xsl:variable name="headerFontSize" select="@font-size"></xsl:variable>
							<xsl:variable name="headerFont" select="@font"/>
							<xsl:choose>
								<xsl:when test="count(../../table/th/td[@key=$nameOfField])!=0">
									<fo:table-cell>
											
										<xsl:if test="$headerFontSize">
											<xsl:attribute name="font-size">
											<xsl:value-of select="$headerFontSize"/>
											</xsl:attribute></xsl:if>
										<xsl:if test="$headerFont">
											<xsl:attribute name="font-family"><xsl:value-of select="$headerFont"/>
											</xsl:attribute>
										</xsl:if>
														
										<xsl:choose>
											<xsl:when test="count(../../table/th/td[@key=$nameOfField]/section) != 0">
												<xsl:for-each select="../../table/th/td[@key=$nameOfField]/section">
													<fo:block>
														<xsl:value-of  disable-output-escaping="yes" select="."/>
													</fo:block>
												</xsl:for-each>
											</xsl:when>
											<xsl:otherwise>
												<fo:block>
												    <xsl:value-of disable-output-escaping="yes" select="../../table/th/td[@key=$nameOfField]"/>
												</fo:block>
											</xsl:otherwise>
										</xsl:choose>
														
									</fo:table-cell>
								</xsl:when>
							</xsl:choose>
					
							</xsl:for-each>
						</fo:table-header>
						<fo:table-body>
							<xsl:for-each select="table/tr">
							  <xsl:variable name="lastTransactionFont" select="@data-font-size-override"/>						
							  <xsl:variable name="currentTr" select="."/>
								<xsl:variable name="isLast"><xsl:choose>
									<xsl:when test="position()=count(../tr)">true</xsl:when><xsl:otherwise>false</xsl:otherwise>
								</xsl:choose></xsl:variable>
								<fo:table-row><!-- order by the order in the column list in the xml -->
									<xsl:for-each select="../../columnWidths/col">
										<xsl:variable name="colName" select="@name"/>
										<fo:table-cell padding-bottom="2px">														
														<xsl:attribute name="text-align"><xsl:value-of select="@data-text-align"/></xsl:attribute>
														<fo:block>
														<xsl:choose>
															<xsl:when test="$isLast='true'">
																<xsl:if test="//lastRowFont !=''">
																	<xsl:attribute name="font-family"><xsl:value-of select="//lastRowFont"/></xsl:attribute>
																</xsl:if>
																<xsl:if test="//lastRowFontWeight !=''">
																	<xsl:attribute name="font-weight"><xsl:value-of select="//lastRowFontWeight"/></xsl:attribute>
																</xsl:if>
																<xsl:if test="//lastRowFontSize !=''">
																		<xsl:attribute name="font-size"><xsl:value-of select="//lastRowFontSize"/></xsl:attribute>
																</xsl:if>
																<xsl:if test="count(//lastRowFontsize) = 0 and @data-font-size-override!=''">
																	<xsl:attribute name="font-size"><xsl:value-of select="@data-font-size-override"/></xsl:attribute>
																</xsl:if>																	
															</xsl:when>
															<xsl:otherwise>
																<xsl:if test="@data-font-size-override!=''">
																	<xsl:attribute name="font-size"><xsl:value-of select="@data-font-size-override"/></xsl:attribute>
																</xsl:if>																
															</xsl:otherwise>														
														</xsl:choose>														
														<xsl:if test="$lastTransactionFont!=''">
																	<xsl:attribute name="font-family">
																		<xsl:value-of select="$lastTransactionFont"/>
																	</xsl:attribute>
														</xsl:if>
														<xsl:attribute name="text-align"><xsl:value-of select="@data-text-align"/></xsl:attribute>
															<xsl:value-of select="$currentTr/td[@key=$colName]" disable-output-escaping="yes"/>
															
														</fo:block> 
														
										</fo:table-cell>
									</xsl:for-each>
								</fo:table-row>
							</xsl:for-each>
						</fo:table-body>
					</fo:table>
				</fo:table-and-caption>
			</fo:block>
		</fo:block-container>
	</xsl:template>
	<xsl:template name="tmplText">
		<fo:block-container>
			<xsl:if test="position != ''">
				<xsl:attribute name="position"><xsl:value-of select="position"/></xsl:attribute>
			</xsl:if>
			<xsl:call-template name="tmplPositionAttributes"/>
			<xsl:call-template name="tmplSizeAttributes"/>
			<fo:block>
				<xsl:call-template name="tmplFontAttributes"/>
				<fo:inline>
					<!--                    <xsl:call-template name="tmplFontAttributes"/>-->
					<xsl:value-of select="defaultValue" disable-output-escaping="yes"/>
				</fo:inline>
			</fo:block>
		</fo:block-container>
	</xsl:template>
	<xsl:template name="tmplImage">
		<fo:external-graphic>
			<xsl:call-template name="tmplImageAttributes"/>
			<xsl:if test="defaultValue">
				<xsl:attribute name="src"><xsl:value-of select="defaultValue" disable-output-escaping="yes"/></xsl:attribute>
			</xsl:if>
		</fo:external-graphic>
	</xsl:template>
	<xsl:template name="tmplImageAttributes">
		<xsl:if test="top != ''">
			<xsl:attribute name="top"><xsl:value-of select="top"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="left != ''">
			<xsl:attribute name="left"><xsl:value-of select="left"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="height">
			<xsl:attribute name="height"><xsl:value-of select="height"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="width">
			<xsl:attribute name="width"><xsl:value-of select="width"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="content-height">
			<xsl:attribute name="content-height"><xsl:value-of select="content-height"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="content-width">
			<xsl:attribute name="content-width"><xsl:value-of select="content-width"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="background-color != ''">
			<xsl:attribute name="background-color"><xsl:value-of select="background-color"/></xsl:attribute>
		</xsl:if>
	</xsl:template>
	<xsl:template name="tmplSizeAttributes">
		<xsl:if test="height != ''">
			<xsl:attribute name="height"><xsl:value-of select="height"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="width != ''">
			<xsl:attribute name="width"><xsl:value-of select="width"/></xsl:attribute>
		</xsl:if>
	
	</xsl:template>
	<xsl:template name="tmplPositionAttributes">
		<xsl:if test="top != ''">
			<xsl:attribute name="top"><xsl:value-of select="top"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="left != ''">
			<xsl:attribute name="left"><xsl:value-of select="left"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="bottom != ''">
			<xsl:attribute name="bottom"><xsl:value-of select="bottom"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="right != ''">
			<xsl:attribute name="right"><xsl:value-of select="right"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="text-align != ''">
			<xsl:attribute name="text-align"><xsl:value-of select="text-align"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="position !=''">
			<xsl:attribute name="position"><xsl:value-of select="position"/></xsl:attribute>
		</xsl:if>
			
	</xsl:template>
	<xsl:template name="tmplFontAttributes">
		<xsl:if test="font !=''">
			<xsl:attribute name="font-family"><xsl:value-of select="font"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="font-size !=''">
			<xsl:attribute name="font-size"><xsl:value-of select="font-size"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="font-weight != ''">
			<xsl:attribute name="font-weight"><xsl:value-of select="font-weight"/></xsl:attribute>
		</xsl:if>
		
	</xsl:template>
</xsl:stylesheet>