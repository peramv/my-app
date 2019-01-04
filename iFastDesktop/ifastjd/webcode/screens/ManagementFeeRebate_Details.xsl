<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />
    
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/ManagementFeeRebate_FeeIDTemplates.xsl"/>
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/DST_WebBehavioursTemplate.xsl"/>
    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>
    
    <xsl:variable name="vClient"       		select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath"  	select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir"      	select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL"          		select="concat( $vDataDir, $vClient, '/' )"/>
    <xsl:variable name="vTX"           		select="/websrvXML/FormInformation/tx"/>
    <xsl:variable name="vCZ"           		select="/websrvXML/FormInformation/cz"/>          
    <xsl:variable name="vTIDX"         		select="/websrvXML/FormInformation/tidx"/>    
    <xsl:variable name="dateFormat"    	select="/websrvXML/FormInformation/dateFormat"/>
    
    <xsl:template match="/">
        
        <Screen>
            
            <html>
                <title>Management Fee Rebate Details</title>
                
                <head>
                    <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"></link>
                    
                    <script src="{$vURL}WebLibrary/JSLib/Err.js"/>          
                    <script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
                    <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
                    <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
                    <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
                    <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
                    <script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
                                           
                    <script src="{$vURL}WebLibrary/WebComps/SuggestFieldComponent.js"/>
                    
                    <script src="{$vURL}javascript/ManagementFeeRebate_Details.js"></script>
                    
                    <xsl:call-template name="DST_WebBehavioursTmpl"/>
                    
                    <style>
                        .Dropdown
                        {
                        width:450;
                        height:228;				
                        border:0px solid black;
                        background:url('<xsl:value-of select="$vURL"/>images/SuggestDropdown_big.gif');
                        padding:5px;				
                        }
                        
                        .DropdownContent
                        {
                        font-size:10px;
                        cursor:default;
                        }
                        
                        .DropdownHighlight
                        {
                        cursor:default;
                        font-size:10px;
                        background: #EDEDED;
                        }
                    </style>
                </head>
                
                <body bgcolor="white" style=" border: 0px solid black" onload="onLoad()">                   
                    
                    <xsl:if test="/websrvXML/responseContents/error">
                        <script>alert('<xsl:value-of select="/websrvXML/responseContents/error"/>');</script>
                    </xsl:if>
                    
                    <div id="feeIDMasterDiv" style="width:365">
                        <fieldset style="position:relative; left:-5; left:10; top:0; width:760;  display:block;">
                            <legend>
                                <span style="font-weight:bold">Management Fee Rebate Fee Model Information</span>                                                                                                                                      
                            </legend>
                            
                            <xsl:if test="/websrvXML/dtMFRFeeIDInitResponse/allowUpdates='yes'">
                                <span style="cursor:pointer; position:absolute; left:513; top:0; width:70; height:15; overflow:hidden;"
                                    align="center">
                                    <xsl:call-template name="ColorButtonTmpl">
                                        <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                        <xsl:with-param name="id">modifyDescBtn</xsl:with-param>
                                        <xsl:with-param name="onclick">modifyDescription();</xsl:with-param>
                                        <xsl:with-param name="size">small</xsl:with-param>
                                        <xsl:with-param name="width">70</xsl:with-param>
                                        <xsl:with-param name="text">Modify</xsl:with-param>
                                        <xsl:with-param name="color">orange</xsl:with-param>
                                    </xsl:call-template>
                                </span>
                                
                                <span style="cursor:pointer; position:absolute; left:587; top:0; width:70; height:15; overflow:hidden;"
                                    align="center">
                                    <xsl:call-template name="ColorButtonTmpl">
                                        <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                        <xsl:with-param name="id">deleteDescBtn</xsl:with-param>
                                        <!-- disabled part of day 2 changes -->                                        
                                        <xsl:with-param name="xxxonclick">if(confirm("Are you sure you want to delete this MFR ID?")) deleteRebateFeeID();</xsl:with-param>
                                        <xsl:with-param name="size">small</xsl:with-param>
                                        <xsl:with-param name="width">70</xsl:with-param>
                                        <xsl:with-param name="text">Delete</xsl:with-param>
                                        <xsl:with-param name="color">gray</xsl:with-param>
                                    </xsl:call-template>
                                </span>
                                
                            	<span style="cursor:pointer; position:absolute; left:662; top:0; width:70; height:15; overflow:hidden;"
                            		align="center">
                            		<xsl:call-template name="ColorButtonTmpl">
                            			<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                            			<xsl:with-param name="id">historyDescBtn</xsl:with-param>                            			
                            			<xsl:with-param name="onclick">sendHistoryRequest( "MFRID" );</xsl:with-param>
                            			<xsl:with-param name="size">small</xsl:with-param>
                            			<xsl:with-param name="width">70</xsl:with-param>
                            			<xsl:with-param name="text">History</xsl:with-param>
                            			<xsl:with-param name="color">orange</xsl:with-param>
                            		</xsl:call-template>
                            	</span>
                                                            	
                            </xsl:if>
                            
                                                        
                            <div style="position:relative; top:3; left:15;">
                                
                                <table style="width:90%; position:relative; top:-3;" id="descriptionTable">
                                    <tr>
                                        <td style="width:150;" align="right"> MFR Model Code: </td>
                                        <td id="feeIDCode" style="verticalAlign:top;">
                                            <xsl:value-of select="/websrvXML/dtMFRFeeIDInitResponse/FeeID/feeIDCode"/>                                            
                                        </td>
                                    </tr>
                                    <tr>
                                        <td style="width:150;" align="right"> Description: </td>
                                        <td>
                                            <span id="descriptionField" style="height:100%; verticalAlign:top;">
                                                <xsl:value-of select="translate( /websrvXML/dtMFRFeeIDInitResponse/FeeID/feeIDDesc, '&#xa;', ' ' )"/>
                                            </span>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td style="width:150;" align="right"> Calculation Method: </td>
                                        <td>
                                            <span id="calcMethodLabel" style="height:100%; verticalAlign:top;">
                                                <xsl:attribute name="code"><xsl:value-of select="/websrvXML/dtMFRFeeIDInitResponse/FeeID/mfCalcType"/></xsl:attribute>
                                                <!-- this is a bit of a hack to get the CalMethod label to be dispalyed, rather than just the code -->
                                                <xsl:variable name="calcMethodSelection">
                                                    <xsl:value-of select="/websrvXML/dtMFRFeeIDInitResponse/FeeID/mfCalcType"/>  
                                                </xsl:variable>
                                                <xsl:for-each select="/websrvXML/dtMFRFeeIDInitResponse/List[@listName='CalcMethods']/Element">
                                                    <xsl:if test="code = $calcMethodSelection">
                                                        <xsl:value-of select="value"/>
                                                    </xsl:if>
                                                </xsl:for-each>     
                                            </span>
                                        </td>
                                    </tr>       
                                    <!-- MFR Calculation -->                                    
									<xsl:if test="/websrvXML/dtMFRFeeIDInitResponse/isMFRCalc='yes'">
										<tr>
											<td style="width:150;" align="right"> Schedule: </td>
											<td>
												<span id="scheduleCodeLabel" style="height:100%; verticalAlign:top;">
													<xsl:attribute name="code"><xsl:value-of select="/websrvXML/dtMFRFeeIDInitResponse/FeeID/scheduleCode"/></xsl:attribute>
													<xsl:variable name="scheduleCodeSelection">
														<xsl:value-of select="/websrvXML/dtMFRFeeIDInitResponse/FeeID/scheduleCode"/>  
													</xsl:variable>
													<xsl:for-each select="/websrvXML/dtMFRFeeIDInitResponse/List[@listName='ScheduleCodes']/Element">
														<xsl:if test="code = $scheduleCodeSelection">
															<xsl:value-of select="value"/>
														</xsl:if>
													</xsl:for-each>     
												</span>
											</td>
										</tr>
									</xsl:if>
                                </table> 
                                
                                <table style="width:95%; display:none; position:relative; top:5; z-index:20;" id="modifyDescriptionTable">
                                    <tr>
                                        <td style="width:150;" align="right"> MFR Model Code: </td>
                                        <td style="verticalAlign:top;">
                                            <input id="feeIDCodeInput">
                                                <xsl:attribute name="value">
                                                    <xsl:value-of select="//FeeID/feeIDCode"/>
                                                </xsl:attribute>
                                            </input>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td style="width:150;" align="right">
                                            <span style="height:100%; verticalAlign:top;">Description:</span>
                                        </td>
                                        <td>
                                            <input id="modifiedDescInput" type="text" style="width:100%">
                                                <xsl:attribute name="value"><xsl:value-of select="translate( /websrvXML/dtMFRFeeIDInitResponse/FeeID/feeIDDesc, '&#xa;', ' ' )"/></xsl:attribute>
                                            </input> 
                                        </td>
                                    </tr>
                                    <tr>
                                        <td style="width:150;" align="right">
                                            <span style="height:100%; verticalAlign:top;">Calculation Method:</span>
                                        </td>
                                        <td>
                                            <select id="calcMethodFld">                                                
                                                <option></option>
                                                <xsl:apply-templates select="//List[@listName='CalcMethods']"/>
                                            </select>                                            
                                        </td>
                                    </tr>
                                    
                                    <!-- MFR Calculation -->
                                    <xsl:if test="/websrvXML/dtMFRFeeIDInitResponse/isMFRCalc='yes'">
										<tr>
												<td style="width:150;" align="right">
													<span style="height:100%; verticalAlign:top;">Schedule:</span>
												</td>
												<td>
													<select id="scheduleCodeFld">                                                
														<option></option>
														<xsl:apply-templates select="//List[@listName='ScheduleCodes']"/>
													</select>                                            
												</td>
											</tr>
                                    </xsl:if> 
                                    
                                    <tr style="height:30">
                                        <td align="right" colspan="2">
                                            <xsl:call-template name="ColorButtonTmpl">
                                                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                                <xsl:with-param name="id">modifyDescBtn</xsl:with-param>
                                                <xsl:with-param name="onclick">saveDescription();</xsl:with-param>
                                                <xsl:with-param name="size">small</xsl:with-param>
                                                <xsl:with-param name="width">85</xsl:with-param>
                                                <xsl:with-param name="text">Save</xsl:with-param>
                                                <xsl:with-param name="color">green</xsl:with-param>
                                            </xsl:call-template>
                                            
                                            <xsl:call-template name="ColorButtonTmpl">
                                                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                                <xsl:with-param name="id">closeDescModifyBtn</xsl:with-param>
                                                <xsl:with-param name="onclick">closeDescription();</xsl:with-param>
                                                <xsl:with-param name="size">small</xsl:with-param>
                                                <xsl:with-param name="width">85</xsl:with-param>
                                                <xsl:with-param name="text">Close</xsl:with-param>
                                                <xsl:with-param name="color">red</xsl:with-param>
                                            </xsl:call-template>
                                        </td>
                                    </tr>
                                </table>
                            </div>
                        </fieldset>
                        
                        <div id="grayDiv"
                            style="width:680; height:300; display:none; position:absolute; z-index:21; background:white; filter:alpha(opacity=50);"> </div>
                        
                        <!-- Accounts Div -->
                        <fieldset id="accountsFieldset">
                            <xsl:attribute name="style">
								position:relative; left:10; top:0; width:760; 
								<xsl:if test="not(/websrvXML/dtMFRFeeIDInitResponse/FeeID)">
									display:none;
								</xsl:if>
							</xsl:attribute>
                            <legend style="cursor:pointer;" onclick='toggleDiv( "accountsDiv" ); togglePlusMinus( this.firstChild ); maintainAccountHeight();'>
                                <img src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/>
                                Accounts                                 
                            </legend>
                            
                            <table><tr><td></td></tr></table>     
                            
                            <div id="accountsDiv" style="display:none; height:50;">
                            
                                <div align="center" style="width:100%; padding-bottom:10px">
                                    
                                    <span style="position:relative; width:60;">Action:</span>
                                    
                                    <span style=" position:relative; top:-2;">
                                        <select id="accountActionSelect" onchange="handleAccountActionSelectChange()" style="width:190; position:relative; zoom:100%">
                                            <option></option>
                                            <xsl:apply-templates select="//List[@listName='AccountActions']"/>          
                                        </select>   
                                    </span>
                                    
                                    <span style="width:50; position:relative; top:-2;">
                                        <xsl:call-template name="ColorButtonTmpl">
                                            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                                        
                                            <xsl:with-param name="onclick">handleAccountActionSelectChange()</xsl:with-param>
                                            <xsl:with-param name="size">small</xsl:with-param>
                                            <xsl:with-param name="width">40</xsl:with-param>
                                            <xsl:with-param name="text">Go</xsl:with-param>
                                            <xsl:with-param name="color">green</xsl:with-param>
                                        </xsl:call-template>
                                    </span>
                                </div>    
                                
                                <div id="scrollableAccountsDiv">                                                                                                                 
                                    <div id="accounts_ListDiv">
                                        <xsl:call-template name="AccountListTmpl">
                                            <xsl:with-param name="sourceNode" select="/websrvXML/dtMFRFeeIDInitResponse/FeeID/Accounts"/>
                                        </xsl:call-template>
                                    </div>
                                </div>
                            </div>
                        </fieldset>
                        
                                                
                        <!-- Funds Div -->                       
                        <fieldset id="fundsFieldset">
                            <xsl:attribute name="style">
                                position:relative; left:10; top:0; width:760; display:block;
                                <xsl:if test="not(/websrvXML/dtMFRFeeIDInitResponse/FeeID/mfCalcType = 'TR')">
                                    display:none;
                                </xsl:if>
                            </xsl:attribute>
                            <legend style="cursor:pointer;" onclick='toggleDiv( "fundsDiv" ); togglePlusMinus( this.firstChild ); maintainFundHeight();'>
                                <img id="aggregationDivToggle" src="{$vURL}images/plus.png" style="position:relative; top:2; left: 1; cursor:pointer"/>
                                Funds                                 
                            </legend>
                            
                            <table><tr><td></td></tr></table>
                                
                            <div id="fundsDiv" style="display:none;">
                                
                                <div align="center" style="width:100%; padding-bottom:10px">
                                    
                                    <span style="position:relative; width:60;">Action:</span>
                                    
                                    <span style=" position:relative; top:-2;">
                                        <select id="fundActionSelect" onchange="handleFundActionSelectChange()" style="width:190; position:relative; zoom:100%">                                            
                                        </select>   
                                    </span>
                                    
                                    <span style="width:50; position:relative; top:-2;">
                                        <xsl:call-template name="ColorButtonTmpl">
                                            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                                        
                                            <xsl:with-param name="onclick">handleFundActionSelectChange()</xsl:with-param>
                                            <xsl:with-param name="size">small</xsl:with-param>
                                            <xsl:with-param name="width">40</xsl:with-param>
                                            <xsl:with-param name="text">Go</xsl:with-param>
                                            <xsl:with-param name="color">green</xsl:with-param>
                                        </xsl:call-template>
                                    </span>
                                </div>    
                                
                                <div id="scrollableFundsDiv">
                                    <div id="fund_ListDiv"  style="position:relative; top:0;">
                                        <div>                                    
                                            <xsl:for-each select="//Funds/Fund">
                                                <xsl:call-template name="FeeIDFundListTmpl">
                                                    <xsl:with-param name="position"><xsl:value-of select="position()"/></xsl:with-param>
                                                    <xsl:with-param name="vURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                                </xsl:call-template>
                                            </xsl:for-each>
                                        </div>                                    
                                    </div>
                                </div>
                            </div>
                        </fieldset>                                            
                    </div>
                    
                    <div style="width:340; position:relative; left:290; top:10;">
                        <div
                            style="cursor:pointer; position:absolute; top:2; left:57; width:105; height:20;"
                            class="biggerButton" align="center"
                            >                            
                            <xsl:call-template name="ColorButtonTmpl">
                                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                <xsl:with-param name="id">closeFeeIDBtn</xsl:with-param>
                                <xsl:with-param name="onclick">parent.closeFeeIDScreen( true );</xsl:with-param>
                                <xsl:with-param name="size">large</xsl:with-param>
                                <xsl:with-param name="width">105</xsl:with-param>
                                <xsl:with-param name="text">Close</xsl:with-param>
                                <xsl:with-param name="color">orange</xsl:with-param>
                            </xsl:call-template>
                            <input type="hidden" id="btnClose"/>
                        </div>
                    </div>
                    
                    <!-- page disabling div -->
                    <div id="disableDiv" style="position:absolute; top:0; left:0; width:800; height:100%; background:e6e6e6; filter:alpha(opacity=70); display:none;">
                    </div>
                    
                    <!-- Account Popup Div -->
					<iframe id="account_PopupIframe"             
                        style="position:absolute; top:100px; left:40px; width:630; height:170; background:white; display:none; overflow:visible; border:none" frameborder="0">
                        <xsl:attribute name="src">
                            javascript: "Loading ..."
                        </xsl:attribute>
                    </iframe>
                    <div id="account_PopupDiv" style="position:absolute; width:630; height:170; top:100; left:40; background:white; display:none; border:2px solid black">                                                
                        <table align="center" style="width:620; position:relative; top:10;" >                            
                            <tr>
                                <td style="width:120; padding-left:5px">
                                    Account:
                                </td>
                                <td style="width:440">            
                                    <!-- account suggestfield -->
                                    <input suggestField="true"
                                        class="DataInput" 
                                        type="text" 
                                        id="accountPopup_AccountFld"
                                        style="width:100%"                              
                                        dropdownClass="Dropdown" 
                                        contentClass="DropdownContent"
                                        highlightClass="DropdownHighlight" 
                                        displayItems="displayValue"                
                                        searchURLGenerator="getAccountSearchURL"
                                        initialValue=""
                                        detailsDisplayElement="accountSuggestDetailsDiv"
                                    />
                                </td>
                                <td style="width:70">
                                    <span style="position:relative; top:0px">
                                        <xsl:call-template name="ColorButtonTmpl">
                                            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                            <xsl:with-param name="onclick">alertAccountSuggestOptions();</xsl:with-param>                                                   
                                            <xsl:with-param name="size">small</xsl:with-param>
                                            <xsl:with-param name="width">70</xsl:with-param>
                                            <xsl:with-param name="text">Options</xsl:with-param>
                                            <xsl:with-param name="color">orange</xsl:with-param>
                                        </xsl:call-template>
                                    </span>                     
                                </td>
                            </tr>
                            <tr>
                                <td style="width:120; padding-left:5px">
                                    Frequency:
                                </td>
                                <td style="width:450" colspan="2">
                                    <select id="accountPopup_FreqFld" style="width:150">
                                        <option></option>
                                        <xsl:choose>
											<xsl:when test="/websrvXML/dtMFRFeeIDInitResponse/isMFRCalc='yes'">
												<xsl:apply-templates select="//List[@listName='ScheduleCodes']"/>
											</xsl:when>
											<xsl:otherwise>
												<xsl:apply-templates select="//List[@listName='frequencies']"/>
											</xsl:otherwise>
										</xsl:choose>
                                    </select>
                                </td>
                            </tr>                           
                            <tr>            
                                <td style="width:120; padding-left:5px">
                                    Effective Date:
                                </td> 
                                <td style="width:450" colspan="2">
                                    <span style="width:150">
                                        <input id="accountPopup_EffDateFld" type="text" class="dstdatepicker">
                                            <xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
                                        </input>
                                    </span>
                                </td> 
                            </tr>
                            <tr>            
                                <td style="width:120; padding-left:5px">
                                    Stop Date:
                                </td> 
                                <td style="width:450" colspan="2">
                                    <span style="width:150">
                                        <input id="accountPopup_StopDateFld" type="text" class="dstdatepicker">
                                            <xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
                                        </input>
                                    </span>
                                </td> 
                            </tr>
                            <xsl:if test="/websrvXML/dtMFRFeeIDInitResponse/isMFRCalc='yes'">
								<tr>            
									<td style="width:120; padding-left:5px">
										Last Accrual Date:
									</td> 
									<td style="width:450" colspan="2">
										<span style="width:150">
											<input id="accountPopup_LastAccrualDateFld" type="text" class="dstdatepicker" >
												<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
											</input>
										</span>
									</td> 
								</tr>
								<tr>            
									<td style="width:120; padding-left:5px">
										Next MFR Date:
									</td> 
									<td style="width:450" colspan="2">
										<span style="width:150">
											<input id="accountPopup_NextMFRDateFld" type="text" class="dstdatepicker">
												<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
											</input>
										</span>
									</td> 
								</tr>
							</xsl:if>
                            <tr>
                                <td colspan="3" style="position:relative; text-align:center">
                                    <span style="padding-right:5px">
                                        <xsl:call-template name="ColorButtonTmpl">
                                            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                                            <xsl:with-param name="id">accountPopup_SaveBtn</xsl:with-param>                  
                                            <xsl:with-param name="size">large</xsl:with-param>
                                            <xsl:with-param name="width">100</xsl:with-param>
                                            <xsl:with-param name="text">Save</xsl:with-param>
                                            <xsl:with-param name="color">green</xsl:with-param>
                                        </xsl:call-template>
                                    </span>              
                                    <span>
                                        <xsl:call-template name="ColorButtonTmpl">
                                            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>                
                                            <xsl:with-param name="onclick">closeAccountPopup();</xsl:with-param>
                                            <xsl:with-param name="size">large</xsl:with-param>
                                            <xsl:with-param name="width">100</xsl:with-param>
                                            <xsl:with-param name="text">Cancel</xsl:with-param>
                                            <xsl:with-param name="color">orange</xsl:with-param>
                                        </xsl:call-template>
                                    </span>                       
                                </td>
                            </tr>
                        </table>                              
                    </div>
                    
                    
				<iframe id="fundHistoryIframe"  style="position:absolute; top:50px; left:70px; width:600; height:525; background:white; display:none; overflow:visible; border:none" frameborder="0">
					<xsl:attribute name="src">
						javascript: "Loading ..."
					</xsl:attribute>
				</iframe>
				 <div id="fundHistoryDiv" style="background:white; position:absolute; top:50px; left:70; width:600; height:525; border:3px solid gray; text-align:center; padding-top:5px; display:none;">
						 <div style="height:25; text-align:left; width:100%; padding-left:40px; padding-bottom:5px">			 
							 <span style="width:200">
								 <span style="position:relative; top: -8; width:80">Start Date:</span>
								 <span style="width:100">
									 <input id="fundHistoryFilter_startDateFld" type="text" class="dstdatepicker">
										<xsl:attribute name="dateformat">
										  <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
										</xsl:attribute>
									  </input>
								  </span>
							 </span>			 			 
							 <span style="width:200">
								 <span style="position:relative; top: -8; width:80">End Date:</span>
								 <span style="width:100">
									 <input id="fundHistoryFilter_endDateFld" type="text" class="dstdatepicker">
										<xsl:attribute name="dateformat">
										  <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
										</xsl:attribute>
									  </input>
								  </span>
							 </span>
							 <span style="position:relative; top:-8">
								 <xsl:call-template name="ColorButtonTmpl">
									  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
									  <xsl:with-param name="id">filterFundHistoryBtn</xsl:with-param>
									  <xsl:with-param name="onclick">filterFundHistory()</xsl:with-param>
									  <xsl:with-param name="size">small</xsl:with-param>
									  <xsl:with-param name="width">80</xsl:with-param>
									  <xsl:with-param name="text">Filter</xsl:with-param>
									  <xsl:with-param name="color">orange</xsl:with-param>
									</xsl:call-template>			 			 
								</span>
						 </div>
						 <div id="fundHistory_contents" style="height:445; border:1px solid black; overflow-Y:scroll; text-align:left; width:570">		 			 		 
						 </div>
							<div style="position:relative; top:10">
								<xsl:call-template name="ColorButtonTmpl">
								  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
								  <xsl:with-param name="id">closeFundHistoryBtn</xsl:with-param>
								  <xsl:with-param name="onclick">closeFundHistoryPopup()</xsl:with-param>
								  <xsl:with-param name="size">large</xsl:with-param>
								  <xsl:with-param name="width">100</xsl:with-param>
								  <xsl:with-param name="text">Close</xsl:with-param>
								  <xsl:with-param name="color">orange</xsl:with-param>
								</xsl:call-template>
							</div>
				</div>
				
				

					<iframe id="ratesIframe"             
                        style="position:absolute; top:100px; left:70px; width:630; height:140; background:white; display:none; overflow:visible; border:none" frameborder="0">
                        <xsl:attribute name="src">
                            javascript: "Loading ..."
                        </xsl:attribute>
                    </iframe>                                        
                    <div id="ratesDiv" style="background:white; position:absolute; top:100; left:70; border:3px solid gray; display:none;"> 
                        <div align="center" style="position:relative; width:630;">
                            <table style="width:620; position:relative; top:5;" align="center">
                                <tr>
                                    <td style="width:120; padding-left:5px">
                                        Fund:
                                    </td>
                                    <td style="width:450" >
                                        
                                        <!-- fund suggestfield -->
                                        <input suggestField="true"
                                            class="DataInput" 
                                            type="text" 
                                            id="ratesFund"
                                            style="width:100%"                              
                                            dropdownClass="Dropdown" 
                                            contentClass="DropdownContent"
                                            highlightClass="DropdownHighlight" 
                                            displayItems="displayValue"                
                                            searchURLGenerator="getFundSearchURL"
                                            initialValue=""
                                        />
                                    </td>
                                    <td style="width:70">
										<span style="position:relative; top:0px">
											<xsl:call-template name="ColorButtonTmpl">
												<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
												<xsl:with-param name="onclick">alertFundSuggestOptions();</xsl:with-param>                                                   
												<xsl:with-param name="size">small</xsl:with-param>
												<xsl:with-param name="width">70</xsl:with-param>
												<xsl:with-param name="text">Options</xsl:with-param>
												<xsl:with-param name="color">orange</xsl:with-param>
											</xsl:call-template>
                                    </span>                     
                                </td>
                                </tr>
                                <tr>            
                                    <td style="width:120; padding-left:5px">
                                        Effective Date:
                                    </td> 
                                    <td colspan="2">
                                        <span style="width:120">
                                            <input style="" id="effDateFld" type="text" class="dstdatepicker">
                                                <xsl:attribute name="dateformat">
                                                    <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                                                </xsl:attribute>
                                            </input>                                            
                                        </span>
                                    </td> 
                                </tr>
                                <tr>            
                                    <td style="width:120; padding-left:5px">
                                        Stop Date:
                                    </td> 
                                    <td colspan="2">
                                        <span style="width:120">
                                            <input style="" id="stopDateFld" type="text" class="dstdatepicker">
                                                <xsl:attribute name="dateformat">
                                                    <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                                                </xsl:attribute>
                                            </input>
                                        </span>
                                    </td> 
                                </tr>
                                <tr id="aggrLinkRow" style="display:none; width:120; padding-left:5px">
                                    <td>
                                        Aggr Link:
                                    </td> 
                                    <td colspan="2">
                                        <input style="width:122" id="aggrLink"></input>
                                    </td> 
                                </tr>
                            </table>
                            
                            <xsl:if test="/websrvXML/dtMFRFeeIDInitResponse/allowTierLowerUpperChanges='yes'">
                                <table id="ratesTableHeader" style="width:380; position:relative; top:10; display:none">
									<tr>
										<td style="width:160; padding-left:10">Lower Bound (<xsl:text><![CDATA[>=]]></xsl:text>)</td>
										<td style="width:150; padding-left:10">Upper Bound (<xsl:text><![CDATA[<]]></xsl:text>)</td>
										<td style="width:70">Rate</td>
									</tr>
								</table>
								<table id="ratesTable" style="width:380; position:relative; top:5" align="center">
								</table>
							</xsl:if>
                            
                            
                            
                        </div>
                        
                        <xsl:if test="/websrvXML/dtMFRFeeIDInitResponse/allowTierLowerUpperChanges='yes'">
                            <div style="width:80; position:relative; left:257; top:7" align="right">
                                <xsl:call-template name="ColorButtonTmpl">
                                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                    <xsl:with-param name="id">addTierBtn</xsl:with-param>
                                    <xsl:with-param name="onclick">addRow()</xsl:with-param>
                                    <xsl:with-param name="size">small</xsl:with-param>
                                    <xsl:with-param name="width">100</xsl:with-param>
                                    <xsl:with-param name="text">Add Tier</xsl:with-param>
                                    <xsl:with-param name="color">green</xsl:with-param>
                                </xsl:call-template>
                            </div>
                        </xsl:if>
                        
                        <div style="width:275; position:relative; left:200; top:10; height:40">\
							<div
                                style="cursor:pointer; position:absolute; top:2; left:0; width:105; height:20; overflow:hidden; background:url({$vURL}images/prototype/biggerButton.png);"
                                align="center">
                                <xsl:call-template name="ColorButtonTmpl">
                                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                    <xsl:with-param name="id">btnClose</xsl:with-param>
                                    <xsl:with-param name="onclick">updateFeeID();</xsl:with-param>
                                    <xsl:with-param name="size">large</xsl:with-param>
                                    <xsl:with-param name="width">105</xsl:with-param>
                                    <xsl:with-param name="text">Save</xsl:with-param>
                                    <xsl:with-param name="color">orange</xsl:with-param>
                                </xsl:call-template>
                            </div>
                            <div
                                style="cursor:pointer; position:absolute; top:2; left:113; width:105; height:20; overflow:hidden; background:url({$vURL}images/prototype/biggerButton.png);"
                                align="center">
                                <xsl:call-template name="ColorButtonTmpl">
                                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                    <xsl:with-param name="id">closeRateBtn</xsl:with-param>
                                    <xsl:with-param name="onclick">closeRatePopup();</xsl:with-param>
                                    <xsl:with-param name="size">large</xsl:with-param>
                                    <xsl:with-param name="width">105</xsl:with-param>
                                    <xsl:with-param name="text">Close</xsl:with-param>
                                    <xsl:with-param name="color">orange</xsl:with-param>
                                </xsl:call-template>
                            </div>                            
                        </div>
                    </div>
                    
                    
                    <div id="accountSuggestDetailsDiv" 
                        style="position:absolute; top:400; left:0; width:500; height:120; display:none; z-index:1000">
                        <iframe src="javascript:false" style="position:absolute; left:0; top:0; width:100%; height:100%" frameBorder="0"/>                        
                        <div style="position:absolute; left:0; top:0; width:100%; height:100%; background:#FFFFE1; border:1px solid black; padding:2px">
                        
							<table>
								<tr>
									<td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">AcctNum:</td>
									<td suggestField="acctNum" style="font-size:10px; width:60px; padding-bottom:3px;"></td> 
								</tr>
							</table>
							
							<div style="width:100%; text-align:left;">
                                <table>
                                    <tr>
                                        <td valign="top" style="font-size:10px; width:90px; font-weight:bold; padding-top:3px; padding-bottom:3px; padding-right:2px">Address:</td>
                                        <td>
                                            <table>
                                                <tr>
                                                    <td suggestField="addr1" style="font-size:10px"></td>
                                                </tr>    
                                                <tr>
                                                    <td suggestField="addr2" style="font-size:10px"></td>
                                                </tr>
                                                <tr>
                                                    <td suggestField="addr3" style="font-size:10px"></td>
                                                 </tr>
                                                 <tr>
                                                    <td suggestField="addr4" style="font-size:10px"></td>
                                                </tr>
                                                <tr>
                                                    <td suggestField="addr5" style="font-size:10px"></td>
                                                </tr>
                                            </table>
                                        </td>
                                    </tr>
                                </table>                                
                            </div>
						                                
                             <table>																			   
                                <tr>
                                    <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">Broker:</td>
                                    <td suggestField="broker" style="font-size:10px; width:60px; padding-bottom:3px"></td>                  
                                    <td suggestField="brokerName" style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                </tr>
                                <tr>
                                    <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">Branch:</td>
                                    <td suggestField="branch" style="font-size:10px; width:60px; padding-bottom:3px"></td>                  
                                    <td suggestField="brnName" style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                </tr>
                                <tr>
                                    <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">SalesRep:</td>
                                    <td suggestField="salesRep" style="font-size:10px; width:60px; padding-bottom:3px"></td>                  
                                    <td suggestField="slsrepName" style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                </tr>
                                 <tr>
                                    <td style="font-size:10px; width:90px; font-weight:bold; padding-bottom:3px; padding-right:2px">BrkAcct:</td>
                                    <td suggestField="brkAcct" style="font-size:10px; width:60px; padding-bottom:3px;"></td>                                    
                                    <td style="font-size:10px; width:350px; padding-bottom:3px"></td>
                                </tr>                
                            </table>
                            
                            
                            
                        </div>            
                    </div>
                    
                    
                	<!-- history popup -->
                	<iframe id="historyIframe"             
                		style="position:absolute; top:50px; left:120px; width:600; height:525; background:white; display:none; overflow:visible; border:none" frameborder="0">
                		<xsl:attribute name="src">
                			javascript: "Loading ..."
                		</xsl:attribute>
                	</iframe>
                	<div id="historyDiv" style="background:white; position:absolute; top:50; left:120; width:600; height:525; border:3px solid gray; text-align:center; padding-top:5px; display:none;">
                		<input id="historyTypeFld" type="text" style="display:none"/>
                		<div style="height:25; text-align:left; width:100%; padding-left:40px; padding-bottom:5px">			 
                			<span style="width:200">
                				<span style="position:relative; top: -8; width:80">Start Date:</span>
                				<span style="width:100">
                					<input id="historyFilter_startDateFld" type="text" class="dstdatepicker">
                						<xsl:attribute name="dateformat">
                							<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                						</xsl:attribute>
                					</input>
                				</span>
                			</span>			 			 
                			<span style="width:200">
                				<span style="position:relative; top: -8; width:80">End Date:</span>
                				<span style="width:100">
                					<input id="historyFilter_endDateFld" type="text" class="dstdatepicker">
                						<xsl:attribute name="dateformat">
                							<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                						</xsl:attribute>
                					</input>
                				</span>
                			</span>
                			<span style="position:relative; top:-8">
                				<xsl:call-template name="ColorButtonTmpl">
                					<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                					<xsl:with-param name="id">filterHistoryBtn</xsl:with-param>
                					<xsl:with-param name="onclick">filterHistory()</xsl:with-param>
                					<xsl:with-param name="size">small</xsl:with-param>
                					<xsl:with-param name="width">80</xsl:with-param>
                					<xsl:with-param name="text">Filter</xsl:with-param>
                					<xsl:with-param name="color">orange</xsl:with-param>
                				</xsl:call-template>			 			 
                			</span>
                		</div>
                		<div id="historyContents" style="height:445; border:1px solid black; overflow-Y:scroll; text-align:left; width:570">		 			 		 
                		</div>
                		<div style="position:relative; top:10">
                			<xsl:call-template name="ColorButtonTmpl">
                				<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                				<xsl:with-param name="id">closeHistoryBtn</xsl:with-param>
                				<xsl:with-param name="onclick">closeHistoryPopup()</xsl:with-param>
                				<xsl:with-param name="size">large</xsl:with-param>
                				<xsl:with-param name="width">100</xsl:with-param>
                				<xsl:with-param name="text">Close</xsl:with-param>
                				<xsl:with-param name="color">orange</xsl:with-param>
                			</xsl:call-template>
                		</div>
                	</div>
                    
                                                            
                </body>
                <script>
                    var _vURL = "<xsl:value-of select="$vURL"/>";
                    var _vServletPath = "<xsl:value-of select="$vServletPath"/>";
                    var _vCZ = "<xsl:value-of select="$vCZ"/>";  
                    var _treeStructure = new Object ();
					var originalDescription = "<xsl:value-of select="translate(//FeeID/feeIDDesc, '&#xa;', ' ' )"/>";					
                    var _companyCode = "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
                    var _ruserId     = "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
                    var _sessionId   = "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
                    var _envName   = "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";                                        
                    var _aggrLink = "<xsl:value-of select='/websrvXML/dtMFRFeeIDInitResponse/enableAggrLink'/>";
                    var _allowUpdates = "<xsl:value-of select='/websrvXML/dtMFRFeeIDInitResponse/allowUpdates'/>";
                    var _allowTierChanges = "<xsl:value-of select='/websrvXML/dtMFRFeeIDInitResponse/allowTierLowerUpperChanges'/>";
                    var _isMFRCalc = "<xsl:value-of select='/websrvXML/dtMFRFeeIDInitResponse/isMFRCalc'/>";
                    var _maxWindowSize = document.body.clientHeight - 250;      
                    var _originalClosedSize = document.getElementById("fundsDiv").offsetHeight;
                    var _selectedFund = null;
                    var _selectedRateSet = null;
                    var _selectedType = null;
                    var _screenMode = "modify";
                    var _dateFormat = "<xsl:value-of select = "/websrvXML/FormInformation/dateFormat"/>";
                    
                    var _lastAccrualDate = null;
                    var _nextMFRDate = null;                    
                	<xsl:choose>
                		<xsl:when test="/websrvXML/dtMFRFeeIDInitResponse/FeeID">
                			var _feeModelVersion = "<xsl:value-of select="/websrvXML/dtMFRFeeIDInitResponse/FeeID/version"/>";
                			var _newFeeModel = false;
                			var _lastAccrualDate = "<xsl:value-of select='/websrvXML/dtMFRFeeIDInitResponse/FeeID/lastAccrualDate'/>";
                			var _nextMFRDate = "<xsl:value-of select='/websrvXML/dtMFRFeeIDInitResponse/FeeID/nextMFRDate'/>";
                		</xsl:when>
                		<xsl:otherwise>
                			var _feeModelVersion = "1";
                			var _newFeeModel = true;
                			var _lastAccrualDate = ""; 
                			var _nextMFRDate = "";
                		</xsl:otherwise>
                	</xsl:choose>                 	     
                	
                	var _scheduleCode = null;
                	<xsl:if test="/websrvXML/dtMFRFeeIDInitResponse/FeeID/scheduleCode">
						_scheduleCode = "<xsl:value-of select='/websrvXML/dtMFRFeeIDInitResponse/FeeID/scheduleCode'/>";
                	</xsl:if>             
                  
                    var _defaultTiers = new Object();
                    <xsl:for-each select="/websrvXML/dtMFRFeeIDInitResponse/DefaultTiers/MFTier">                        
                        _defaultTiers.tier<xsl:value-of select="position()"/> = new Object();
                        _defaultTiers.tier<xsl:value-of select="position()"/>.lower = "<xsl:value-of select="lower"/>";
                        _defaultTiers.tier<xsl:value-of select="position()"/>.upper = "<xsl:value-of select="upper"/>";  
                    </xsl:for-each>
                    
                    
                    var _actionSelectMap = {};
                    _actionSelectMap["none"] = "";
                    <xsl:for-each select="/websrvXML/dtMFRFeeIDInitResponse/List[@listName='FundActions']/Element">
                        _actionSelectMap["<xsl:value-of select="code"/>"] = "<xsl:value-of select="value"/>";
                    </xsl:for-each>
                    
                    function onLoad()
                    {                        
                        // add or modify
                        
                        if (_allowUpdates == "no")
                            document.getElementById("accountActionSelect").disabled = true;
                        
                        if ("<xsl:value-of select="//FormInformation/feeModelCode"/>" == "")
                        _screenMode = "add";
                        
                        updateGrayDiv();
                        
                        if (_screenMode == "add")
                        {
                            modifyDescription();                                   
                        }
                        updateFundActionMenu();
                    }
                    
                </script>
            </html>
        </Screen>
        
    </xsl:template>
    
    
    <!-- ============================= MAKING A LIST DROP DOWN ======================================================== -->
    <xsl:template match="List">
        <xsl:param name="selected"/>
        <xsl:apply-templates select="Element">
            <xsl:with-param name="selected">
                <xsl:value-of select="$selected"/>
            </xsl:with-param>
        </xsl:apply-templates>
    </xsl:template>
    
    <xsl:template match="Element">
        <xsl:param name="selected"/>
        <option>
            <xsl:attribute name="value">
                <xsl:value-of select="code"/>
            </xsl:attribute>
            <xsl:if test="code=$selected">
                <xsl:attribute name="selected">true</xsl:attribute>
            </xsl:if>
            <xsl:value-of select="value"/>
        </option>
    </xsl:template>
    
</xsl:stylesheet>