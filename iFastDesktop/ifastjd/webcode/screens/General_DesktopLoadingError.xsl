<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
	<xsl:variable name="vClient" 			select="/websrvXML/requestInfo/client"/>
	<xsl:variable name="vServletPath" 		select="/websrvXML/requestInfo/servletPath"/>
	<xsl:variable name="vDataDir" 			select="/websrvXML/transformNode/datadir"/>
	<xsl:variable name="vURL" 				select="concat( $vDataDir, $vClient, '/' )"/>
	<xsl:variable name="vTX" 				select="/websrvXML/FormInformation/tx"/>
	<xsl:variable name="vCZ" 				select="/websrvXML/FormInformation/cz"/>
	<xsl:variable name="vSessionId"			select="/websrvXML/FormInformation/sessionId"/>
	<xsl:variable name="vTIDX"/>
	
  
	<xsl:template match="/">
		
		<xsl:variable name="screenName" select="/websrvXML/Error/screenName"/>	  	
	  	<xsl:variable name="errorMsg" select="/websrvXML/Error/msg"/>
  	
		<Screen>
		  	<html>
		  		<head>
		  			<script src="{$vURL}javascript/General_DesktopError.js"/>
		  			<script src="{$vURL}javascript/General_Desktop.js"/>
		  			<script>
		  				setSessionToken( "<xsl:value-of select="$vSessionId"/>" );
		  						  				
		  				function loading()
		  				{
		  					DesktopError.displayLoadingError( "<xsl:value-of select="$screenName"/>",
		  					                         "<xsl:value-of select="$errorMsg"/>" )
		  				}
		  			</script>
		  		</head>
		  		<body onload="loading()">
		  			
		  		</body>
		  	</html>
		</Screen>	  	
  </xsl:template>
  
</xsl:stylesheet>
	 