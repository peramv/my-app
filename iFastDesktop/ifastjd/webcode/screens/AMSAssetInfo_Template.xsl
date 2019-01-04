<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>
	
	
	<xsl:template name="AssetListTmpl">
		<xsl:param name="sourceNode"/>
		<xsl:param name="searchType"/>
		<table id="listContentsTable" ifdsTable="true" cellpadding="0" cellspacing="0" style="table-layout:fixed">
		    <!-- table headers -->
			<xsl:choose>
				<xsl:when test="$searchType = 'fund'">
					<thead>
						<tr>
							<th class="tableHeader" resizable="true" style="width:100;">
								<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Fund No.
								</span>   
						   </th>
							<th class="tableHeader" resizable="true"  style="width:350;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
									Fund Name
								</span>
						   </th>
							<th class="tableHeader" resizable="true"  style="width:100;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Asset
								</span>
						   </th>
							<th class="tableHeader" resizable="true"  style="width:100;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Sub Asset
								</span>
						   </th>
							<th class="tableHeader"  resizable="true" style="width:100;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   MVC $
								</span>
						   </th>
							<th class="tableHeader"  resizable="true" style="width:100;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Split %
								</span>
						   </th>
							<th class="tableHeader" resizable="true"  style="width:100;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Current %
								</span>
						   </th>
							<th class="tableHeader lastCol" resizable="true"  style="width:100;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Variance %
								</span>
						   </th>
						</tr>
					</thead>
				</xsl:when>
				<xsl:when test="$searchType = 'asset'">
					<thead>
						<tr>
							<th class="tableHeader" resizable="true"  style="width:250;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Asset
								</span>
						   </th>
							<th class="tableHeader"  resizable="true" style="width:200;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   MVC $
								</span>
						   </th>
							<th class="tableHeader"  resizable="true" style="width:200;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Split %
								</span>
						   </th>
							<th class="tableHeader" resizable="true"  style="width:200;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Current %
								</span>
						   </th>
							<th class="tableHeader lastCol" resizable="true"  style="width:200;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Variance %
								</span>
						   </th>
						</tr>
					</thead>
				</xsl:when>
				<xsl:otherwise>
					<thead>
						<tr>
							<th class="tableHeader" resizable="true"  style="width:250;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Asset
								</span>
						   </th>
							<th class="tableHeader" resizable="true"  style="width:250;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Sub Asset
								</span>
						   </th>
							<th class="tableHeader"  resizable="true" style="width:145;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   MVC $
								</span>
						   </th>
							<th class="tableHeader"  resizable="true" style="width:135;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Split %
								</span>
						   </th>
							<th class="tableHeader" resizable="true"  style="width:135;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Current %
								</span>
						   </th>
							<th class="tableHeader lastCol" resizable="true"  style="width:135;">
							   <span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
								   Variance %
								</span>
						   </th>
						</tr>
					</thead>
				</xsl:otherwise>
			</xsl:choose>
			<tbody>
			  <!-- table contents -->
			   <xsl:variable name="recordCount" select="count($sourceNode/AssetDetl)"/>
				<xsl:for-each select="$sourceNode/AssetDetl">
					<xsl:choose>
						<xsl:when test="$searchType = 'fund'">
							<tr>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="fund"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="fundNm"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="asset"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="subAsst"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="mv"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="split"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="current"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData lastCol <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="var"/>
									</span>
								</td>								
							</tr>
						</xsl:when>
						<xsl:when test="$searchType = 'asset'">
							<tr>								
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="asset"/>
									</span>
								</td>								
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="mv"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="split"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="current"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData lastCol <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="var"/>
									</span>
								</td>								
							</tr>
						</xsl:when>
						<xsl:otherwise>
							<tr>								
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="asset"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="subAsst"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="mv"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="split"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="current"/>
									</span>
								</td>
								<td>
									<xsl:attribute name="class">
										tableData lastCol <xsl:if test="position() = $recordCount">lastRow</xsl:if>
									</xsl:attribute>
									<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
										<xsl:value-of select="var"/>
									</span>
								</td>								
							</tr>
						</xsl:otherwise>
					</xsl:choose>				
				</xsl:for-each>
			</tbody>
		</table>
		


 	
		
	</xsl:template>
</xsl:stylesheet>
