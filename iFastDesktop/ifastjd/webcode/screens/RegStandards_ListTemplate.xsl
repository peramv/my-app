<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:template name="RegStandardsList_Tmpl">
        <xsl:param name="listSrc"/>
        
        <table id="RegStandardsListTable" ifdsTable="true" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true">
            <thead>
                <tr>
                    <td style="width:20;">
                        <xsl:text>&#xa0;</xsl:text>
                    </td>
                    <td style="width:115;">
                        Country
                    </td>
                    <td style="width:150;">
                        Regulation Rule
                    </td>
                    <td style="width:125;">	
                        Regulatory Code
                    </td>		
                    <td style="width:535;">	
                        Description
                    </td>		        							
                </tr>
            </thead>							
            <tbody>
                <xsl:if test="$listSrc">
                    <xsl:for-each select="$listSrc/RegStandard">
                        <xsl:variable name="rowIndex" select="number( position() ) - 1"/>                                               
                        <tr rowIndex="{$rowIndex}">
                            <xsl:attribute name="regStandardId"><xsl:value-of select="regStandardId"/></xsl:attribute>
                            <xsl:attribute name="countryCode"><xsl:value-of select="countryCode"/></xsl:attribute>
                            <xsl:attribute name="regRule"><xsl:value-of select="regRule"/></xsl:attribute>
                            <xsl:attribute name="complyCode"><xsl:value-of select="complyCode"/></xsl:attribute>
                            <xsl:attribute name="description"><xsl:value-of select="description"/></xsl:attribute>
                            <xsl:attribute name="investorType"><xsl:value-of select="investorType"/></xsl:attribute>
                            <xsl:attribute name="investFor3rdParty"><xsl:value-of select="investFor3rdParty"/></xsl:attribute>
                            <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                            <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
                            <xsl:attribute name="provinceCode"><xsl:value-of select="provinceCode"/></xsl:attribute>
                            <xsl:attribute name="taxTypes"><xsl:for-each select="TaxTypes/code"><xsl:value-of select="."/><xsl:if test="position() != last()">,</xsl:if></xsl:for-each></xsl:attribute>
                            
                            <td style="padding-left:3px">
                                <div class="expandBtn" title="expand details"/>
                                <div class="collapseBtn" title="hide details"/>    
                            </td>
                            <td>                                
                                <xsl:attribute name="data">
                                    <xsl:value-of select="countryCode"/>
                                </xsl:attribute>
                                <span class="Desktop_Table_Data">
                                    <xsl:attribute name="title">
                                        <xsl:value-of select="countryDesc"/>
                                    </xsl:attribute>                                    
                                    <xsl:value-of select="countryDesc"/>
                                </span>
                            </td>
                            <td>                                
                                <xsl:attribute name="data">
                                    <xsl:value-of select="regRule"/>
                                </xsl:attribute>
                                <span class="Desktop_Table_Data">
                                    <xsl:attribute name="title">
                                        <xsl:value-of select="regRuleDesc"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="regRuleDesc"/>
                                </span>
                            </td>
                            <td>                                
                                <xsl:attribute name="data">
                                    <xsl:value-of select="complyCode"/>
                                </xsl:attribute>
                                <span class="Desktop_Table_Data">
                                    <xsl:attribute name="title">
                                        <xsl:value-of select="complyCode"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="complyCode"/>
                                </span>
                            </td>
                            <td>                                
                                <xsl:attribute name="data">
                                    <xsl:value-of select="description"/>
                                </xsl:attribute>
                                <span class="Desktop_Table_Data">
                                    <xsl:attribute name="title">
                                        <xsl:value-of select="description"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="description"/>
                                </span>
                                
                               <div class="DetailsDiv">
                               	<xsl:attribute name="style">
                               		<xsl:if test="regRule != 'CC'">height:190px;</xsl:if>
                               	</xsl:attribute>                               	
                                    <div class="DetailsContentsDiv">
                                        <xsl:attribute name="style">
                                    		<xsl:if test="regRule != 'CC'">height:165px;</xsl:if>
                                        </xsl:attribute>
                                        <xsl:if test="regRule != 'CC'">                                      	
	                                        <div class="DetailsSectionDiv">
	                                            <span class="Desktop_Lbl DetailsLbl" style="left:0px;">
	                                                Investor Type:
	                                            </span>
	                                            <span class="Desktop_Lbl DetailsLbl" style="left:200px;">
	                                                <xsl:value-of select="investorTypeDesc"/>
	                                            </span>			        				
	                                            <span class="Desktop_Lbl DetailsLbl" style="left:420px;">
	                                                Invest on behalf of 3rd party:
	                                            </span>
	                                            <span class="Desktop_Lbl DetailsLbl" style="left:620px;">
	                                                <xsl:value-of select="investFor3rdParty"/>
	                                            </span>	
	                                        </div>
                                        </xsl:if>
                                        <div class="DetailsSectionDiv">
                                            <span class="Desktop_Lbl DetailsLbl" style="left:0px;">
                                                Effective Date:
                                            </span>
                                            <span class="Desktop_Lbl DetailsLbl" style="left:200px;">
                                                <xsl:value-of select="effDate"/>
                                            </span>			        				
                                            <span class="Desktop_Lbl DetailsLbl" style="left:420px;">
                                                Stop Date:
                                            </span>
                                            <span class="Desktop_Lbl DetailsLbl" style="left:620px;">
                                                <xsl:value-of select="stopDate"/>
                                            </span>	
                                        </div>                                        
                                        <div class="DetailsSectionDiv">
                                    		<span class="Desktop_Lbl DetailsLbl" style="left:0px;">
                                    			Province:
                                    		</span>
                                    		<span class="Desktop_Lbl DetailsLbl" style="left:200px;">
                                    			<xsl:value-of select="provinceDesc"/>
                                    		</span>			        				
                                    		<span class="Desktop_Lbl DetailsLbl" style="left:420px;">
                                    			Tax Type(s):
                                    		</span>
                                    		<span class="Desktop_Lbl DetailsLbl" style="left:620px;">
                                    			<xsl:for-each select="TaxTypes/code">
                                    				<xsl:value-of select="."/><xsl:if test="position() != last()">,</xsl:if>
                                    			</xsl:for-each>
                                    		</span>	
                                        </div>
                                        <div class="DetailsSectionDiv" style="padding-top:4px;">
                                            <div id="DetailsDocListDiv_{$rowIndex}" class="Desktop_TableDiv" style="width:617; height:88; overflow-x:scroll">
                                                <table id="DetailsDocListTable_{$rowIndex}" ifdsTable="true" baseClassName="Desktop_Table" style="position:absolute; left:0; top:0;" tableHeight="88" cellpadding="0" cellspacing="0" scrollable="true"  rowSelectable="false" resizable="true">
                                                    <thead>
                                                        <tr>
                                                            <td style="width:100" columnWidth="100">DocCode</td>
                                                            <td style="width:1000" columnWidth="1000">Description</td>
                                                        </tr>
                                                    </thead>
                                                    <tbody>
                                                        <xsl:for-each select="docList/docListItem">
                                                            <tr>
                                                                <xsl:attribute name="docItemId"><xsl:value-of select="docItemId"/></xsl:attribute>
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
                                            </div>							
                                        </div>
                                    </div>                                       	        				
                                </div>	
                            </td>
                        </tr>
                    </xsl:for-each>
                </xsl:if>                            
            </tbody>                			
        </table>	        
        
    </xsl:template>
    
</xsl:stylesheet>   

	        