<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
    <xsl:template name="Table_Tmpl">		
        <xsl:param name="accountStaticData"/>
        
        <table id="accountStaticData_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="false">			
            <thead>
                <tr>					
                    <td style="width:115;" columnWidth="115">
                        Verify Status
                    </td>
                    <td style="width:77;" columnWidth="77">
                        EntityID
                    </td>
                    <td style="width:100;" columnWidth="100">
                        FieldName
                    </td>
                    <td style="width:125;" columnWidth="125">
                        Previous Value
                    </td>
                    <td style="width:125;" columnWidth="125">
                        New Value
                    </td>
                    <td style="width:85;" columnWidth="85">
                        Mod User
                    </td>
                    <td style="width:142;" columnWidth="142">
                        Mod Date
                    </td>
                    <td style="width:85;" columnWidth="85">
                        Verify User
                    </td>
                    <td style="width:120;" columnWidth="120">
                        Verify Date
                    </td>														
                </tr>
            </thead>					
            <tbody>
                <xsl:if test="$accountStaticData and count($accountStaticData/EntityInfo/EntityInfo) &gt; 0">																
                    <xsl:for-each select="$accountStaticData/EntityInfo/EntityInfo">
                        <tr>
                            <td>
                                <select name="verifyStat" onchange="ddlChangeHandler_verifyStat();">
                                    <xsl:if test="verifyStat = 'Verified' or allowVerify = 'no'">
                                        <xsl:attribute name="disabled">true</xsl:attribute>    
                                    </xsl:if>
                                    
                                    <option>
                                        <xsl:attribute name="value">UnVerified</xsl:attribute>                                        
                                        <xsl:if test="verifyStat = 'Unverified'">
                                            <xsl:attribute name="selected">selected</xsl:attribute>
                                        </xsl:if>
                                        
                                        UnVerified
                                    </option>
                                    <option>
                                        <xsl:attribute name="value">Verified</xsl:attribute>                                        
                                        <xsl:if test="verifyStat = 'Verified'">                                        
                                            <xsl:attribute name="selected">selected</xsl:attribute>
                                        </xsl:if>
                                        
                                        Verified
                                    </option>
                                </select>
                            </td>							
                            <td>
                                <xsl:value-of select="entityId"/>
                            </td>									
                            <td>
                                <table style="height: 100%;"><tbody>
                                    <xsl:for-each select="fieldInfo/fldLabel">
                                        <tr><td>
                                            <xsl:if test="string-length(.) = 0">
                                                <xsl:text>&#xa0;</xsl:text>
                                            </xsl:if>
                                            <xsl:value-of select="." />
                                        </td></tr>
                                    </xsl:for-each>
                                </tbody></table>
                            </td>
                            <td>
                                <table style="height: 100%;"><tbody>
                                    <xsl:for-each select="fieldInfo/oldVal">
                                        <tr><td>
                                            <xsl:if test="string-length(.) = 0">
                                                <xsl:text>&#xa0;</xsl:text>
                                            </xsl:if>
                                            <xsl:value-of select="." />
                                        </td></tr>
                                    </xsl:for-each>
                                </tbody></table>
                            </td>
                            <td>
                                <table style="height: 100%;"><tbody>
                                    <xsl:for-each select="fieldInfo/newVal">
                                        <tr><td>
                                            <xsl:if test="string-length(.) = 0">
                                                <xsl:text>&#xa0;</xsl:text>
                                            </xsl:if>
                                            <xsl:value-of select="." />
                                        </td></tr>
                                    </xsl:for-each>
                                </tbody></table>
                            </td>
                            <td>
                                <xsl:value-of select="modUser"/>
                            </td>
                            <td>
                                <xsl:value-of select="modTime"/>
                                <xsl:text>&#xa0;</xsl:text>
                                <xsl:value-of select="modDate"/>
                            </td>
                            <td>
                                <xsl:value-of select="verfyUser"/>
                            </td>
                            <td>
                                <xsl:value-of select="verifyDate"/>
                            </td>																					
                        </tr>
                    </xsl:for-each>											
                </xsl:if>
            </tbody>                			
        </table>
        
    </xsl:template>	
    
</xsl:stylesheet>