<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:fo="http://www.w3.org/1999/XSL/Format" version="1.1"
	exclude-result-prefixes="fo">
	<fo:root>
		<fo:block font-size="16pt" font-weight="bold" space-after="5mm">
			Company Name:
			<xsl:value-of select="//EntityHeaderInfo/entNm" />
		</fo:block>
	</fo:root>
</xsl:stylesheet>