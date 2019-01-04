<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes"/>

  <xsl:template name="ColorButtonTmpl">
    <xsl:param name="baseURL"/>
    <xsl:param name="size">small</xsl:param>
    <xsl:param name="color">orange</xsl:param>
    <xsl:param name="width"/>
    <xsl:param name="text"/>
    <xsl:param name="id"/>
    <xsl:param name="onclick"/>


    <xsl:element name="span">
      <xsl:attribute name="id">
        <xsl:value-of select="$id"/>
      </xsl:attribute>
      <xsl:attribute name="onclick">
        <xsl:value-of select="$onclick"/>
      </xsl:attribute>
      <xsl:if test="$size = 'small'">
        <xsl:attribute name="style">cursor:hand; overflow:hidden; width:<xsl:value-of
            select="$width"/>; height:15px;</xsl:attribute>
      </xsl:if>
      <xsl:if test="$size = 'large'">
        <xsl:attribute name="style">cursor:hand; overflow:hidden; width:<xsl:value-of
            select="$width"/>; height:20px;</xsl:attribute>
      </xsl:if>

      <!-- left (colored) end -->
      <xsl:element name="span">
        <xsl:if test="$size = 'small'">
          <xsl:attribute name="style">height:100%; width:12px; background:url(<xsl:value-of
            select="$baseURL"/>components/ColorButtons/images/<xsl:value-of select="$color"
          />_small.png);</xsl:attribute>
        </xsl:if>
        <xsl:if test="$size = 'large'">
          <xsl:attribute name="style">height:100%; width:14px; background:url(<xsl:value-of
            select="$baseURL"/>components/ColorButtons/images/<xsl:value-of select="$color"
          />_large.png);</xsl:attribute>
        </xsl:if>
      </xsl:element>

      <!-- middle -->
      <xsl:element name="span">
        <xsl:if test="$size = 'small'">
          <xsl:attribute name="style">height:100%; text-align:center; font-size:11px;
              width:<xsl:value-of select="$width - (12 + 8)"/>; background:url(<xsl:value-of
                select="$baseURL"/>components/ColorButtons/images/middle_small.png);
          background-repeat:repeat-x;</xsl:attribute>
        </xsl:if>
        <xsl:if test="$size = 'large'">
          <xsl:attribute name="style">position:relative; top:0; height:100%; text-align:center; font-size:14px;
              width:<xsl:value-of select="$width - (14 + 8)"/>; background:url(<xsl:value-of
                select="$baseURL"/>components/ColorButtons/images/middle_large.png);
          background-repeat:repeat-x;</xsl:attribute>
        </xsl:if>

        <!-- text -->
        <span style="overflow:hidden; position:relative; top:1;">
          <xsl:value-of select="$text"/>
        </span>
      </xsl:element>

      <xsl:element name="span">
        <xsl:if test="$size = 'small'">
          <xsl:attribute name="style">height:100%; width:8px; background:url(<xsl:value-of
            select="$baseURL"/>components/ColorButtons/images/end_small.png);</xsl:attribute>
        </xsl:if>
        <xsl:if test="$size = 'large'">
          <xsl:attribute name="style">height:100%; width:8px; background:url(<xsl:value-of
            select="$baseURL"/>components/ColorButtons/images/end_large.png);</xsl:attribute>
        </xsl:if>

      </xsl:element>

    </xsl:element>
  </xsl:template>

</xsl:stylesheet>
