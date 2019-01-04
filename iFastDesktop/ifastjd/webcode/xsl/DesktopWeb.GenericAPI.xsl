<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
		version = "1.0"
		xmlns:java ="http://xml.apache.org/xslt/java"
		extension-element-prefixes="java">
			
	<xsl:template match="/">
		<xsl:variable name="apiName"><xsl:value-of select="/websrvXML/FormInformation/apiName"/></xsl:variable>
		<message>		
			<GENERIC_API_REQ>				
				<RequestHeader>
					<xsl:copy-of select="/websrvXML/requestInfo/request/APIRequest/header/*"/>
					<dataMode><xsl:value-of select="/websrvXML/FormInformation/dataMode"/></dataMode>						
					<networkID>IFSF</networkID>					
					<companyIDType>IFAST</companyIDType>
					<companyIDValue><xsl:value-of select="/websrvXML/requestInfo/request/APIRequest/header/companyCode"/></companyIDValue>						
					<msgDate><xsl:value-of select="java:com.dstsystems.api.valueOf( ., '$DATE:yyyyMMdd' )"/></msgDate>
					<msgTime><xsl:value-of select="java:com.dstsystems.api.valueOf( ., '$TIME:HHmmss' )"/></msgTime>					
				</RequestHeader>									
				<xsl:copy-of select="/websrvXML/requestInfo/request/APIRequest/body/*"/>				
			</GENERIC_API_REQ>
		</message>		
	</xsl:template>
</xsl:stylesheet>
