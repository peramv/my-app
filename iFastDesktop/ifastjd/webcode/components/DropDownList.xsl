
  <xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />
  
   <xsl:template match="/">    
   		
   


	<input type="hidden" class="dstcombobox" value="15" width="200px" formfield="formfield">
		<xsl:attribute name="name"><xsl:value-of select="//selectName"/></xsl:attribute>
		<xsl:attribute name="id"><xsl:value-of select="//list/@id"/></xsl:attribute>
		<xsl:attribute name="data">xml<xsl:value-of select="//list/@id"/></xsl:attribute>
	</input>
	
	<xml>
	<xsl:attribute name="id">xml<xsl:value-of select="//list/@id"/></xsl:attribute>	
	<newdataset>

		<xsl:apply-templates select="//list/element"/>
	</newdataset>

	</xml>
	</xsl:template>

    
    
    <xsl:template match="element">
       	<combobox>
			<display><xsl:value-of select="value"/></display>
			<formfield><xsl:value-of select="code"/></formfield>
		</combobox>
    </xsl:template>
  </xsl:stylesheet>
  
  
  