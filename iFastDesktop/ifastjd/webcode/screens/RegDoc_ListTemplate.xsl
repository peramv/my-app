<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:template name="RegDocList_Tmpl">
        <xsl:param name="listSrc"/>
        
        <table id="DocListTable" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true" resizable="true">
            <thead id="DocListTable_head">
                <tr>
                    <td style="width:114;" columnWidth="114">
                        DocCode
                    </td>
                    <td style="width:1000;" columnWidth="1000">	
                        Description
                    </td>		
                </tr>
            </thead>					
            <tbody id="DocListTable_body">                
                    <xsl:for-each select="$listSrc/DocItem">
                        <tr>
                            <td>
                                <xsl:attribute name="title">
                                    <xsl:value-of select="docCode"/>
                                </xsl:attribute>
                                <xsl:attribute name="data">
                                    <xsl:value-of select="docCode"/>
                                </xsl:attribute>
                                <span class="Desktop_Table_Data">
                                    <xsl:value-of select="docCode"/>
                                </span>
                            </td>
                            <td>
                                <xsl:attribute name="title">
                                    <xsl:value-of select="description"/>
                                </xsl:attribute>
                                <xsl:attribute name="data">
                                    <xsl:value-of select="description"/>
                                </xsl:attribute>
                                <span class="Desktop_Table_Data">
                                    <xsl:value-of select="description"/>
                                </span>
                            </td>		
                        </tr>	
                    </xsl:for-each>                                            
            </tbody>                			
        </table>	        
        
    </xsl:template>
    
</xsl:stylesheet>   

	        