<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:variable name="vPO_BOX">poBox</xsl:variable>
	<xsl:variable name="vCIVIC">civic</xsl:variable>
	<xsl:variable name="vGENERAL">general</xsl:variable>
	<xsl:variable name="vRURAL_ROUTE">ruralRoute</xsl:variable>
	<xsl:variable name="vST_ROUTE">stRoute</xsl:variable>
	

	<!-- ADDRESS LIST TEMPLATE -->
	<xsl:template match="dtPCLookupReloadResponse">
		<div id="addressListDiv">
			<xsl:apply-templates select="PCLookupDetails/Civic"/>
			<xsl:apply-templates select="PCLookupDetails/POBox"/>
			<xsl:apply-templates select="PCLookupDetails/RuralRoute"/>
			<xsl:apply-templates select="PCLookupDetails/General"/>
			<xsl:apply-templates select="PCLookupDetails/StRoute"/>			
		</div>		
	</xsl:template>


	<!-- GENERAL DELIVERY ADDRESS TEMPLATE -->
	<xsl:template match="General">
		<div id="{$vGENERAL}_AddressSectionDiv" class="addressSectionDiv">
			<div class="addressSectionLabelDiv">
				General Delivery
			</div>
			<div id="{$vGENERAL}_AddressList_TableDiv" class="Desktop_TableDiv AddressList_TableDiv" style="overflow-y:scroll;">	
				<table id="{$vGENERAL}_AddressList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true">			
					<thead>
						<tr>	
							<td style="width:260;" columnWidth="260">
								<div>Delivery Area</div>
								
							</td>
							<td style="width:440;" columnWidth="440">
								<div>Delivery Installation</div>								
							</td>																		
						</tr>
					</thead>					
					<tbody>
						<xsl:for-each select="AddressRec">
							<tr>		
								<xsl:attribute name="city"><xsl:value-of select="city"/></xsl:attribute>
								<xsl:attribute name="delArea"><xsl:value-of select="delArea"/></xsl:attribute>
								<xsl:attribute name="delInstall"><xsl:value-of select="delInstall"/></xsl:attribute>								
													
								<td>
									<xsl:value-of select="delArea"/>								
								</td>
								<td>
									<xsl:value-of select="delInstall"/>								
								</td>																																		
							</tr>
						</xsl:for-each>																	
					</tbody>                			
				</table>
			</div>
		</div>		     
	</xsl:template>
	
	
	<!-- RURAL ROUTE ADDRESS TEMPLATE -->
	<xsl:template match="RuralRoute">
		<div id="{$vRURAL_ROUTE}_AddressSectionDiv" class="addressSectionDiv">
			<div class="addressSectionLabelDiv">
				Rural Route
			</div>
			<div id="{$vRURAL_ROUTE}_AddressList_TableDiv" class="Desktop_TableDiv AddressList_TableDiv" style="overflow-y:scroll;">	
				<table id="{$vRURAL_ROUTE}_AddressList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true">			
					<thead>
						<tr>	
							<td style="width:540;" columnWidth="540">
								<div>Delivery Area</div>
								
							</td>
							<td style="width:160;" columnWidth="160">
								<div>Route Info</div>								
							</td>																		
						</tr>
					</thead>					
					<tbody>
						<xsl:for-each select="AddressRec">
							<tr>
								<xsl:attribute name="city"><xsl:value-of select="city"/></xsl:attribute>
								<xsl:attribute name="routeInfo"><xsl:value-of select="routeInfo"/></xsl:attribute>
								<xsl:attribute name="delArea"><xsl:value-of select="delArea"/></xsl:attribute>
															
								<td>
									<xsl:value-of select="delArea"/>								
								</td>
								<td>
									<xsl:value-of select="routeInfo"/>								
								</td>																																		
							</tr>
						</xsl:for-each>																	
					</tbody>                			
				</table>
			</div>
		</div>		     
	</xsl:template>
	
	<!-- CIVIC ADDRESS TEMPLATE -->
	<xsl:template match="Civic">
		<div id="{$vCIVIC}_AddressSectionDiv" class="addressSectionDiv">
			<div class="addressSectionLabelDiv">
				Civic or Street Address
			</div>
			<div id="{$vCIVIC}_AddressList_TableDiv" class="Desktop_TableDiv AddressList_TableDiv" style="overflow-y:scroll;">	
				<table id="{$vCIVIC}_AddressList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true">			
					<thead>
						<tr>	
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>From</div>
							</td>
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>To</div>
							</td>
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>Suffix From</div>
							</td>
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>Suffix To</div>
							</td>
							<td style="width:220;" columnWidth="220">
								Street Name
							</td>
							<td style="width:70;" columnWidth="70">
								<div>Unit</div>
								<div>From</div>
							</td>
							<td style="width:70;" columnWidth="70">
								<div>Unit</div>
								<div>To</div>
							</td>																		
						</tr>
					</thead>					
					<tbody>
						<xsl:for-each select="AddressRec">
							<tr>
								<xsl:attribute name="stFrom"><xsl:value-of select="stFrom"/></xsl:attribute>
								<xsl:attribute name="stTo"><xsl:value-of select="stTo"/></xsl:attribute>
								<xsl:attribute name="oddeven"><xsl:value-of select="oddeven"/></xsl:attribute>
								<xsl:attribute name="stSfxFrom"><xsl:value-of select="stSfxFrom"/></xsl:attribute>
								<xsl:attribute name="stSfxTo"><xsl:value-of select="stSfxTo"/></xsl:attribute>
								<xsl:attribute name="stName"><xsl:value-of select="stName"/></xsl:attribute>
								<xsl:attribute name="unitFrom"><xsl:value-of select="unitFrom"/></xsl:attribute>
								<xsl:attribute name="unitTo"><xsl:value-of select="unitTo"/></xsl:attribute>
								<xsl:attribute name="city"><xsl:value-of select="city"/></xsl:attribute>
								
								<td>
									<xsl:value-of select="stFrom"/>								
								</td>
								<td>
									<xsl:value-of select="stTo"/>								
								</td>							
								<td>
									<xsl:value-of select="stSfxFrom"/>
								</td>									
								<td>
									<xsl:value-of select="stSfxTo"/>
								</td>
								<td>
									<xsl:value-of select="stName"/>
								</td>
								<td>
									<xsl:value-of select="unitFrom"/>
								</td>
								<td>
									<xsl:value-of select="unitTo"/>
								</td>																											
							</tr>
						</xsl:for-each>											
						
					</tbody>                			
				</table>
			</div>
		</div>		     
	</xsl:template>
	
	<!-- PO Box -->
	<xsl:template match="POBox">
		<div id="{$vPO_BOX}_AddressSectionDiv" class="addressSectionDiv">
			<div class="addressSectionLabelDiv">
				PO Box
			</div>
			<div id="{$vPO_BOX}_AddressList_TableDiv" class="Desktop_TableDiv AddressList_TableDiv" style="overflow-y:scroll;">	
				<table id="{$vPO_BOX}_AddressList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true">			
					<thead>
						<tr>	
							<td style="width:70;" columnWidth="70">
								<div>PO Box From</div>								
							</td>
							<td style="width:70;" columnWidth="70">
								<div>PO Box To</div>								
							</td>
							<td style="width:490;" columnWidth="490">
								<div>Delivery Area</div>								
							</td>
							<td style="width:70;" columnWidth="70">
								<div>Route Info</div>								
							</td>																						
						</tr>
					</thead>					
					<tbody>
						<xsl:for-each select="AddressRec">
							<tr>
								<xsl:attribute name="pobFrom"><xsl:value-of select="pobFrom"/></xsl:attribute>
								<xsl:attribute name="pobTo"><xsl:value-of select="pobTo"/></xsl:attribute>
								<xsl:attribute name="delArea"><xsl:value-of select="delArea"/></xsl:attribute>								
								<xsl:attribute name="routeInfo"><xsl:value-of select="routeInfo"/></xsl:attribute>
								<xsl:attribute name="city"><xsl:value-of select="city"/></xsl:attribute>
														
								<td>
									<xsl:value-of select="pobFrom"/>								
								</td>
								<td>
									<xsl:value-of select="pobTo"/>								
								</td>							
								<td>
									<xsl:value-of select="delArea"/>
								</td>								
								<td>
									<xsl:value-of select="routeInfo"/>
								</td>																															
							</tr>
						</xsl:for-each>											
						
					</tbody>                			
				</table>
			</div>
		</div>
		
	</xsl:template>
	
	<!-- ST ROUTE TEMPLATE -->
	<xsl:template match="StRoute">
		<div id="{$vST_ROUTE}_AddressSectionDiv" class="addressSectionDiv">
			<div class="addressSectionLabelDiv">
				Street Served by Rural Route
			</div>
			<div id="{$vST_ROUTE}_AddressList_TableDiv" class="Desktop_TableDiv AddressList_TableDiv" style="overflow-y:scroll;">	
				<table id="{$vST_ROUTE}_AddressList_Table" ifdsTable="true" style="position:absolute; left:0; top:0;" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true">			
					<thead>
						<tr>	
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>From</div>
							</td>
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>To</div>
							</td>
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>Suffix From</div>
							</td>
							<td style="width:85;" columnWidth="85">
								<div>Street No.</div>
								<div>Suffix To</div>
							</td>
							<td style="width:220;" columnWidth="220">
								Street Name
							</td>
							<td style="width:140;" columnWidth="140">
								<div>Route Info</div>								
							</td>
																				
						</tr>
					</thead>					
					<tbody>
						<xsl:for-each select="AddressRec">
							<tr>
								<xsl:attribute name="stFrom"><xsl:value-of select="stFrom"/></xsl:attribute>
								<xsl:attribute name="stTo"><xsl:value-of select="stTo"/></xsl:attribute>
								<xsl:attribute name="oddeven"><xsl:value-of select="oddeven"/></xsl:attribute>
								<xsl:attribute name="stSfxFrom"><xsl:value-of select="stSfxFrom"/></xsl:attribute>
								<xsl:attribute name="stSfxTo"><xsl:value-of select="stSfxTo"/></xsl:attribute>
								<xsl:attribute name="stName"><xsl:value-of select="stName"/></xsl:attribute>
								<xsl:attribute name="routeInfo"><xsl:value-of select="routeInfo"/></xsl:attribute>
								<xsl:attribute name="city"><xsl:value-of select="city"/></xsl:attribute>
														
								<td>
									<xsl:value-of select="stFrom"/>								
								</td>
								<td>
									<xsl:value-of select="stTo"/>								
								</td>							
								<td>
									<xsl:value-of select="stSfxFrom"/>
								</td>								
								<td>
									<xsl:value-of select="stSfxTo"/>
								</td>	
								<td>
									<xsl:value-of select="stName"/>
								</td>																															
								<td>
									<xsl:value-of select="routeInfo"/>
								</td>
							</tr>
						</xsl:for-each>											
						
					</tbody>                			
				</table>
			</div>
		</div>
		
	</xsl:template>				
   
</xsl:stylesheet>
