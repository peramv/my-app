<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    
    <xsl:template name="AggAccountListTmpl">
        <xsl:param name="sourceNode"/>
        
        <xsl:choose>
            <xsl:when test="$sourceNode/Account">
                <table id="aggAccount_ListTable" style="position:relative; left:30; table-layout:fixed">            
                    <xsl:for-each select="$sourceNode/Account">
                        <tr style="position:relative; width:100%; cursor:pointer;">
                            <xsl:attribute name="acctNum"><xsl:value-of select="acctNum"/></xsl:attribute>
      			    <xsl:attribute name="acctRowID"><xsl:value-of select="acctRowID"/></xsl:attribute>
                            <xsl:attribute name="ownerName"><xsl:value-of select="ownerName"/></xsl:attribute>
                            <xsl:attribute name="feeAggrID"><xsl:value-of select="feeAggrID"/></xsl:attribute>                            
                            <xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
                            <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                            <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
                            <xsl:attribute name="gbcd"><xsl:value-of select="gbcd"/></xsl:attribute>
                                                        
                            <xsl:attribute name="onclick">    
                                selectRow( this, "aggAccount" );                        
                            </xsl:attribute>
                            
                            <td style="width:75; text-align:left"><xsl:value-of select="acctNum"/></td>                            
                            <td style="width:500; text-align:left"><xsl:value-of select="ownerName"/></td>                            
                            <td style="width:195; text-align:left;">[<xsl:value-of select="effDate"/> to <xsl:value-of select="stopDate"/>]</td>                                                
                            <td style="width:70; text-align:left;"><xsl:value-of select="gbcd"/></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </xsl:when>
            <xsl:otherwise>
                <span style="padding-left:50px; color:gray; font-style:italic">No Accounts have been added.</span>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
    
    
    <xsl:template name="AggBrokerListTmpl">
        <xsl:param name="sourceNode"/>
        
        <xsl:choose>
            <xsl:when test="$sourceNode/Broker">
                <table id="aggBroker_ListTable" style="position:relative; left:30; table-layout:fixed">
                    <xsl:for-each select="$sourceNode/Broker">
                        <tr style="position:relative; width:100%; cursor:pointer;">
                            <xsl:attribute name="brkcode"><xsl:value-of select="brkcode"/></xsl:attribute>
                            <xsl:attribute name="brkName"><xsl:value-of select="brkName"/></xsl:attribute>
                            <xsl:attribute name="feeAggrID"><xsl:value-of select="feeAggrID"/></xsl:attribute>                            
                            <xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
                            <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                            <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
                        	<xsl:attribute name="gbcd"><xsl:value-of select="gbcd"/></xsl:attribute>
                            <xsl:attribute name="onclick">                                    
                                selectRow( this, "aggBroker" );
                            </xsl:attribute>
                            
                            <td style="width:75; text-align:left"><xsl:value-of select="brkcode"/></td>                            
                            <td style="width:500; text-align:left"><xsl:value-of select="brkName"/></td>
                            <td style="width:195; text-align:left;">[<xsl:value-of select="effDate"/> to <xsl:value-of select="stopDate"/>]</td>
                            <td style="width:70; text-align:left;"><xsl:value-of select="gbcd"/></td>                          
                        </tr>
                    </xsl:for-each>
                </table>                
            </xsl:when>
            <xsl:otherwise>
                <span style="padding-left:50px; color:gray; font-style:italic">No Brokers have been added.</span>
            </xsl:otherwise>
        </xsl:choose>
                        
    </xsl:template>
    
    
    
    <xsl:template name="AggSalesRepListTmpl">
        <xsl:param name="sourceNode"/>
        
        <xsl:choose>
            <xsl:when test="$sourceNode/BrokerReps">
                <div>
                    <xsl:for-each select="$sourceNode/BrokerReps">            
                        <xsl:variable name="brkCode"><xsl:value-of select="brkCode"/></xsl:variable>                                       
                        <div style="position:relative; left:35px">
                            <span class="headerRow" style=""> <xsl:value-of select="brkCode"/></span><span style="position:relative; left:10;"> <xsl:value-of select="brkName"/></span> 
                        </div>
                                        
                        <table style="position:relative; left:60; table-layout:fixed">
                            <xsl:attribute name="id">aggSalesRep_ListTable<xsl:value-of select="position()"/></xsl:attribute>
                            <xsl:for-each select="SalesRep">
                                <tr style="position:relative; width:100%; cursor:pointer;">
                                    <xsl:attribute name="brkCode"><xsl:value-of select="$brkCode"/></xsl:attribute>
                                    <xsl:attribute name="repCode"><xsl:value-of select="repCode"/></xsl:attribute>
                                    <xsl:attribute name="feeAggrID"><xsl:value-of select="feeAggrID"/></xsl:attribute>                                                                
                                    <xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
                                	<xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                                	<xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
                                	<xsl:attribute name="gbcd"><xsl:value-of select="gbcd"/></xsl:attribute>
                                    <xsl:attribute name="onclick">
                                        selectRow( this, "aggSalesRep" );           
                                    </xsl:attribute>    
                                                                    
                                    <td style="width:45; align:left;"><xsl:value-of select="repCode"/></td>                                    
                                    <td style="width:500; padding-right:5px"><xsl:value-of select="repName"/></td>        
                                	<td style="width:195; text-align:left;">[<xsl:value-of select="effDate"/> to <xsl:value-of select="stopDate"/>]</td>
                                	<td style="width:70; text-align:left;"><xsl:value-of select="gbcd"/></td>                                                       
                                </tr>
                            </xsl:for-each>
                        </table>                           
                    </xsl:for-each>
                </div>        
            </xsl:when>
            
            <xsl:otherwise>
                <span style="padding-left:50px; color:gray; font-style:italic">No SalesReps have been added.</span>
            </xsl:otherwise>
        </xsl:choose>
        
    </xsl:template>
    
    
    
    
    <xsl:template name="AggAssetListTmpl">
        <xsl:param name="sourceNode"/>
        
        <xsl:choose>
            <xsl:when test="$sourceNode/Asset">
                <table id="aggAsset_ListTable" style="position:relative; left:30; table-layout:fixed">        
                    <xsl:for-each select="$sourceNode/Asset">
                        <tr style="position:relative; width:100%; cursor:pointer;">                    
                            <xsl:attribute name="assetCode"><xsl:value-of select="assetCode"/></xsl:attribute>
                            <xsl:attribute name="feeAggrID"><xsl:value-of select="feeAggrID"/></xsl:attribute>
                            <xsl:attribute name="version"><xsl:value-of select="version"/></xsl:attribute>
                            <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>           
                            <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>   
                        	<xsl:attribute name="gbcd"><xsl:value-of select="gbcd"/></xsl:attribute>                                                                
                            <xsl:attribute name="onclick">
                                selectRow( this, "aggAsset" );
                            </xsl:attribute>
                            
                            <td style="width:75; text-align:left"><xsl:value-of select="assetCode"/></td>                            
                            <td style="width:500; text-align:left"><xsl:value-of select="assetName"/></td>
                            <td style="width:195; text-align:left;">[<xsl:value-of select="effDate"/> to <xsl:value-of select="stopDate"/>]</td>
                            <td style="width:70; text-align:left;"><xsl:value-of select="gbcd"/></td>                                                                        
                        </tr>
                    </xsl:for-each>            
                </table>        
            </xsl:when>
            
            <xsl:otherwise>
                <span style="padding-left:50px; color:gray; font-style:italic">No Assets have been added.</span>
            </xsl:otherwise>          
        </xsl:choose>
        
   </xsl:template>
   
   
   
   
   <xsl:template name="FeeIDListTmpl">
       <xsl:param name="sourceNode"/>
       
       <xsl:choose>
           <xsl:when test="$sourceNode/FeeID">
               <table id="feeID_ListTable" style="position:relative; left:30; width:525; table-layout:fixed">
                   <xsl:for-each select="$sourceNode/FeeID">
                       <tr style="position:relative; width:100%; cursor:pointer;">
                           <xsl:attribute name="feeModelCode"><xsl:value-of select="feeModelCode"/></xsl:attribute>
                           <xsl:attribute name="desc"><xsl:value-of select="desc"/></xsl:attribute>
                           <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                           <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
                           <xsl:attribute name="onclick">
                               selectRow( this, "feeID" );
                           </xsl:attribute>
                           
                           <td align="left" style="width:100; font-weight:bold;"><xsl:value-of select="feeModelCode"/></td>                           
                           <td style="width:745; padding-right:5px"><span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis"><xsl:value-of select="desc"/></span></td>                                                                 
                       </tr>
                   </xsl:for-each>
               </table>               
           </xsl:when>
           
           <xsl:otherwise>
               <span style="padding-left:50px; color:gray; font-style:italic">No FeeIDs have been added.</span>
           </xsl:otherwise>
       </xsl:choose>
       
       
   </xsl:template>
   
   

   
   <xsl:template name="InvoiceIDListTmpl">
       <xsl:param name="sourceNode"/>
       
       <xsl:choose>
           <xsl:when test="$sourceNode/InvoiceID">
               <table id="invoiceID_ListTable" style="position:relative; left:30; width:525; table-layout:fixed">                 
                   <xsl:for-each select="$sourceNode/InvoiceID">
                       <tr style="position:relative; width:100%; cursor:pointer;">
                           <xsl:attribute name="rcdStat"><xsl:value-of select="rcdStat"/></xsl:attribute>
                           <xsl:attribute name="invIDCode"><xsl:value-of select="invIDCode"/></xsl:attribute>
                           <xsl:attribute name="billInstrID"><xsl:value-of select="billInstrID"/></xsl:attribute>
                           <xsl:attribute name="frequency"><xsl:value-of select="frequency"/></xsl:attribute>
                           <xsl:attribute name="effDate"><xsl:value-of select="effDate"/></xsl:attribute>
                           <xsl:attribute name="stopDate"><xsl:value-of select="stopDate"/></xsl:attribute>
                       	   <xsl:attribute name="gbcd"><xsl:value-of select="gbcd"/></xsl:attribute>
                           <xsl:attribute name="onclick">
                               selectRow( this, "invoiceID" );
                           </xsl:attribute>
                           
                           <td align="left" style="width:100; font-weight:bold"><xsl:value-of select="invIDCode"/></td>                           
                           <td style="width:460; padding-right:5px"><xsl:value-of select="invoiceName"/></td>
                           <td align="right" style="width:200px">[<xsl:value-of select="effDate"/> to <xsl:value-of select="stopDate"/>]</td>
                       	   <td style="width:70; padding-right:5px"><xsl:value-of select="gbcd"/></td>
                       </tr>
                   </xsl:for-each>
               </table>               
           </xsl:when>
           
           <xsl:otherwise>
               <span style="padding-left:50px; color:gray; font-style:italic">No InvoiceIDs have been added.</span>
           </xsl:otherwise>
       </xsl:choose>       
   </xsl:template>
   

   
   <xsl:template name="AccountListTmpl">
       <xsl:param name="sourceNode"/>
       
       <xsl:choose>
           <xsl:when test="$sourceNode/Account">
               <table id="accounts_ListTable" ifdsTable="true" style="left:30; margin:0; padding:0; table-layout:fixed">
                   <thead>
                       <tr align="left" style="position:relative;">
                           <th style="border:1px solid gray; cursor:pointer; width:81; background:#ffd696;"
                               initialSorted="true"  
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Account
                           </th>
                           <th style="border:1px solid gray; cursor:pointer; width:335; background:#ffd696;"  
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Owner
                           </th>
                           <th style="border:1px solid gray; cursor:pointer; width:95;background:#ffd696;"   
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Eff.Date
                           </th>
                       	<th style="border:1px solid gray; cursor:pointer; width:95;background:#ffd696;"   
                       		sortable="true" 
                       		dataType="string" 
                       		onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                       		Stop Date
                       	</th>                 
                           <th style="border:1px solid gray; cursor:pointer; width:73; background:#ffd696;"  
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Fee ID
                           </th>
                           <th style="border:1px solid gray; cursor:pointer; width:98;background:#ffd696;"   
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Invoice ID
                           </th>
                       	<th style="border:1px solid gray; cursor:pointer; width:98;background:#ffd696;"   
                       		sortable="true" 
                       		dataType="string" 
                       		onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                       		GBCD
                       	</th>                     
                                      
                       </tr>
                   </thead>                              
               	<xsl:for-each select="$sourceNode/Account">
               		<tr style="position:relative; cursor:pointer;">
               			<xsl:attribute name="acctNum">
               				<xsl:value-of select="acctNum"/>
               			</xsl:attribute>                           
               			<xsl:attribute name="acctRowID">
               				<xsl:value-of select="acctRowID"/>
               			</xsl:attribute>                           
               			<xsl:attribute name="feeModelCode">
               				<xsl:value-of select="feeModelCode"/>
               			</xsl:attribute>
               			<xsl:attribute name="billInstrCode">
               				<xsl:value-of select="billInstrCode"/>
               			</xsl:attribute>
               			<xsl:attribute name="effDate">
               				<xsl:value-of select="effDate"/>
               			</xsl:attribute>
               			<xsl:attribute name="stopDate">
               				<xsl:value-of select="stopDate"/>
               			</xsl:attribute>                           
               			<xsl:attribute name="version">
               				<xsl:value-of select="version"/>
               			</xsl:attribute>
               			<xsl:attribute name="shrAcctID">
               				<xsl:value-of select="shrAcctID"/>
               			</xsl:attribute>
               			<xsl:attribute name="gbcd">
               				<xsl:value-of select="gbcd"/>
               			</xsl:attribute>
               			<xsl:attribute name="onclick">
               				selectRow( this, "account" );           
               			</xsl:attribute>
               			
               			<td style="width:81px">
               				<xsl:attribute name="sortValue">
               					<xsl:value-of select="acctNum"/>
               				</xsl:attribute>							   
               				<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
               					<xsl:attribute name="title">
               						<xsl:value-of select="acctNum"/>
               					</xsl:attribute>
               					<xsl:value-of select="acctNum"/>
               				</span>
               			</td>
               			<td style="width:335px">
               				<xsl:attribute name="sortValue">
               					<xsl:value-of select="ownName"/>
               				</xsl:attribute>		
               				<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
               					<xsl:attribute name="title">
               						<xsl:value-of select="ownName"/>
               					</xsl:attribute>
               					<xsl:value-of select="ownName"/>
               				</span>
               			</td>
               			<td style="width:95px">
               				<xsl:attribute name="sortValue">
               					<xsl:value-of select="effDate"/>
               				</xsl:attribute>		                           
               				<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
               					<xsl:attribute name="title">
               						<xsl:value-of select="effDate"/>
               					</xsl:attribute>
               					<xsl:value-of select="effDate"/>
               				</span>
               			</td>
               			<td style="width:95px">
               				<xsl:attribute name="sortValue">
               					<xsl:value-of select="stopDate"/>
               				</xsl:attribute>		                           
               				<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
               					<xsl:attribute name="title">
               						<xsl:value-of select="stopDate"/>
               					</xsl:attribute>
               					<xsl:value-of select="stopDate"/>
               				</span>
               			</td>               			                     
               			<td style="width:71">
               				<xsl:attribute name="sortValue">
               					<xsl:value-of select="feeModelCode"/>
               				</xsl:attribute>		                           
               				<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
               					<xsl:attribute name="title">
               						<xsl:value-of select="feeModelCode"/>
               					</xsl:attribute>
               					<xsl:value-of select="feeModelCode"/>
               				</span>
               			</td>
               			<td style="width:98px">
               				<xsl:attribute name="sortValue">
               					<xsl:value-of select="billInstrCode"/>
               				</xsl:attribute>		                           
               				<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
               					<xsl:attribute name="title">
               						<xsl:value-of select="billInstrCode"/>
               					</xsl:attribute>
               					<xsl:value-of select="billInstrCode"/>
               				</span>
               			</td>
               			<td style="width:98px">
               				<xsl:attribute name="sortValue">
               					<xsl:value-of select="billInstrCode"/>
               				</xsl:attribute>		                           
               				<span style="width:100%; overflow:hidden; white-space:nowrap; text-overflow:ellipsis">
               					<xsl:attribute name="title">
               						<xsl:value-of select="gbcd"/>
               					</xsl:attribute>
               					<xsl:value-of select="gbcd"/>
               				</span>
               			</td>                                                                   
               		</tr>
               	</xsl:for-each>  
               </table>               
           </xsl:when>
           
           <xsl:otherwise>
               <span style="padding-left:50px; color:gray; font-style:italic;">No Accounts have been added.</span>
                <table id="accounts_ListTable" ifdsTable="true" style="left:30; margin:0; padding:0; table-layout:fixed; display:none">
                    <thead>
                       <tr align="left" >
                           <th style="border:1px solid gray; cursor:pointer; width:81; background:#ffd696;"
                               initialSorted="true"  
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Account
                           </th>
                           <th style="border:1px solid gray; cursor:pointer; width:245; background:#ffd696;"  
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Owner
                           </th>
                           <th style="border:1px solid gray; cursor:pointer; width:71; background:#ffd696;"  
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Fee ID
                           </th>
                           <th style="border:1px solid gray; cursor:pointer; width:98;background:#ffd696;"   
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Invoice ID
                           </th>            
                           <th style="border:1px solid gray; cursor:pointer; width:82;background:#ffd696;"   
                               sortable="true" 
                               dataType="string" 
                               onclick='if( _selectedRowMap["account"] ) unselectRow( "account" );'>
                               Eff.Date
                           </th>                           
                       </tr>
                   </thead>                              
                  </table>
           </xsl:otherwise>
       </xsl:choose>
              
   </xsl:template>


   
   <xsl:template name="HistoryTmpl">
	   <xsl:param name="sourceNode"/>
	   
	   <div>
			<xsl:for-each select="$sourceNode/UpdatedEntity">			
				<div style="width:100%; padding-left:5; padding-bottom:10">
					 <div style="width:100%; height:20" onclick="toggleHistoryDetailsDisplay(this);">
						 <img src="{$vURL}images/plus.png" style="position:relative; top:2; left:1; cursor:pointer; "/>
						 <span style="border-bottom:2px solid #FFD696; font-weight:bold; position:relative; left:5px;cursor:pointer; "><xsl:value-of select="updForDesc"/></span>
					 </div>
					 <div style="display:none;">
						 <xsl:for-each select="Updates/Update">
							 <div style="width:100%; padding-bottom:5">
								 <div style="width:100%">
									 <span style="width:100; font-weight:bold; text-transform:uppercase"><xsl:value-of select="updType"/></span>								 									 
									 <span style="width:210"><xsl:value-of select="updDate"/> (<xsl:value-of select="updTime"/>)</span>
									 <span style="width:50; font-weight:bold;">User:</span>
									 <span style="width:120"><xsl:value-of select="updUser"/></span>
								</div>
								<xsl:if test="Values/Value">
									<div style="padding-left:100">
										<div>
											<span style="width:60; font-weight:bold; text-decoration:underline; font-style:italic">Details</span>
										</div>
										<div style="padding-left:20">
											<span style="">	
												<table cellpadding="0" cellspacing="0">
													<xsl:for-each select="Values/Value">
														<tr>														
															<td style="width:130"><xsl:value-of select="valType"/>:</td>
															<xsl:choose>
																<xsl:when test="oldValue">
																	<td>
																		<span><xsl:value-of select="newValue"/></span>
																		<span style="font-size:11; padding-left:10px;">( old: <xsl:value-of select="oldValue"/> )</span>
																	</td>
																</xsl:when>															
																<xsl:otherwise>
																	<td>
																		<span><xsl:value-of select="newValue"/></span>
																	</td>
																</xsl:otherwise>
															</xsl:choose>															
														</tr>
													</xsl:for-each>
												</table>
											</span>
										</div>							
									</div>
								</xsl:if>
							</div>
						</xsl:for-each>
					</div>
				</div>
			</xsl:for-each>
		</div>
   </xsl:template>
      
   

</xsl:stylesheet>