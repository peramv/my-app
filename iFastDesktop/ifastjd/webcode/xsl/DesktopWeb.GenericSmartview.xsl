<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version = "1.0">
	<xsl:template match="/">
		<xsl:variable name="smartview"><xsl:value-of select="/websrvXML/FormInformation/smartview"/></xsl:variable>
		<message>			
			<request>
				<GENERIC_SMV_REQ>				
					<RequestHeader>
						<xsl:copy-of select="/websrvXML/requestInfo/request/SmartviewRequest/header/*"/>						
						<elementLength>short</elementLength>          						
						<dataMode>inquire</dataMode> 						
						<downLoadMode>no</downLoadMode> 						
					</RequestHeader>
					<data>						
						<xsl:copy-of select="/websrvXML/requestInfo/request/SmartviewRequest/body/*"/>
					</data>
				</GENERIC_SMV_REQ>
			</request>			
		</message>  

	</xsl:template>
</xsl:stylesheet>
