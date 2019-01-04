<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes" />
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/RegStandards_ListTemplate.xsl"/>	
	
	<xsl:variable name="vClient"       	select="/websrvXML/requestInfo/client"/>
	<xsl:variable name="vServletPath"  	select="/websrvXML/requestInfo/servletPath"/>
	<xsl:variable name="vDataDir"      	select="/websrvXML/transformNode/datadir"/>
	<xsl:variable name="vURL"         	select="concat( $vDataDir, $vClient, '/' )"/>
	<xsl:variable name="vTX"           	select="/websrvXML/FormInformation/tx"/>
	<xsl:variable name="vCZ"           	select="/websrvXML/FormInformation/cz"/>          
	<xsl:variable name="vTIDX"         	select="/websrvXML/FormInformation/tidx"/>  
	<xsl:variable name="dateFormat"    	select="/websrvXML/FormInformation/dateFormat"/>
	<xsl:variable name="vDesktopColor"    select="/websrvXML/FormInformation/bgcolor"/>

  
  	<xsl:template match="/">

		<Screen>
      
      		<html>
        
				<head>
					<title>Regulation Standards</title>
			
					<!-- web library js code -->
		        	<script src="{$vURL}WebLibrary/JSLib/Err.js"/>
		        	<script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
		        	<script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
		        	<script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
		        	<script src="{$vURL}WebLibrary/JSLib/XML.js"/>
		        	<script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
					<script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
		        	
		        	<script src="{$vURL}WebLibrary/WebComps/IFDSTable.js"/>
					<script src="{$vURL}WebLibrary/WebComps/IFDSCalendarWidget.js"/>
					<script src="{$vURL}WebLibrary/WebComps/IFDSDatepicker.js"/>
		        	
					<script src="{$vURL}javascript/General_Desktop.js"/>
		        	<script src="{$vURL}javascript/General_DesktopError.js"/>
					        
					<!-- page specific js code -->
		        	<script src="{$vURL}javascript/RegStandards.js"/>        	        
        	
					<script>
						var _vURL 			= "<xsl:value-of select="$vURL"/>";
						var _vServletPath 	= "<xsl:value-of select="$vServletPath"/>";
						var _vCZ 			= "<xsl:value-of select="$vCZ"/>";
						var _companyCode 	= "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
						var _ruserId     	= "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
						var _sessionId   	= "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
						var _envName   		= "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";          
						var _dateFormat   	= "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
						var _desktopColor  	= "<xsl:value-of select="$vDesktopColor"/>";
						
						var _docMap = {};
						<xsl:for-each select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'regDocLists']/Element">
							_docMap["<xsl:value-of select="docCode"/>"] = XML.charDecode( "<xsl:value-of select="description"/>" );
						</xsl:for-each>
						
						var _regRuleFilterValue = "";
						var _startRecNum = "";
						var _nextStartRecNum = "";
						var _requestRecNum = 100;
						
						var _userPermissionMap = {};
						_userPermissionMap["run"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/userPermissions/run"/>";
						_userPermissionMap["mod"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/userPermissions/mod"/>";
						_userPermissionMap["add"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/userPermissions/add"/>";
						_userPermissionMap["del"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/userPermissions/del"/>";
						
						var _docListPermissionMap = {};
						_docListPermissionMap["run"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/docListsPermissions/run"/>";
						_docListPermissionMap["mod"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/docListsPermissions/mod"/>";
						_docListPermissionMap["add"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/docListsPermissions/add"/>";
						_docListPermissionMap["del"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/docListsPermissions/del"/>";
						
						var _defaultValueMap = {};
						_defaultValueMap["effDate"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/effDateDefault"/>";
						_defaultValueMap["stopDate"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/stopDateDefault"/>";
						_defaultValueMap["regCountries"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'regCountries']/ListSelection"/>";
						_defaultValueMap["regProvinces"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'regProvinces']/ListSelection"/>";
						_defaultValueMap["taxTypes"] = "<xsl:value-of select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'taxTypes']/ListSelection"/>";
						
						setSessionToken( _sessionId );													
									
						function loading()
						{            	
							<xsl:if test="/websrvXML/dtRegStandardsInitResponse/RequestStatus/status = 'Accepted' ">            	
								initRegStandards();
							</xsl:if>			                		
						}                                                           					  
					</script>
					
			    	<xsl:call-template name="DesktopCSSTmpl">
		        		<xsl:with-param name="DesktopColor" select="$vDesktopColor"/>
		        		<xsl:with-param name="includeDatepicker">yes</xsl:with-param>        			        		
		        	</xsl:call-template>
          
			        <style>
			        	#ScreenDiv
			        	{
				        	background-color: #<xsl:value-of select="$vDesktopColor"/>;
				        	position:absolute;
				        	left:0px;
				        	top:0px;
				        	width:967px;
				        	padding-left:30px;
				        	padding-right:30px;
				        	height:500px;
				        	padding-top:15px;
				        	padding-bottom:30px;				        			        
			        	}
			        	
			        	#ContentsDiv
			        	{
				        	position:relative;
				        	width:967px;
				        	height:440px;
				        	z-index:0;
						}
						
			        	.ContentsSectionDiv
			        	{	        	
				        	position:relative;
				        	width:100%;			        		
			        		padding-bottom:8px;	  			        			        		        
			        	}
			        	
			        	#RegRuleFilterDiv
			        	{
			        		height:28px;
			        		text-align:center;			        			        	
			        	}
			        	
			        	#RegStandardsListDiv
			        	{
			        		height:380px;
			        	}
			        	
			        	#ActionButtonsDiv
			        	{
				        	position:relative;	        			        			        		
				        	width:100%;        		
				        	height:50px;
				        	text-align:right;
				        	padding-top:5px;	        		
			        	}
			        	
			        	#ScreenButtonsDiv
			        	{
				        	position:relative;
				        	width:100%;
				        	height:50px;
				        	text-align:center;
				        	padding-top:10px;
			        	}
			        	
			        	.ActionBtn	
			        	{
			        		width:80px;
			        	}
			        	
			        	.ScreenBtn
			        	{
				        	position:relative;		        			        
				        	width:120px;		        		        	
			        	}
			        	
			        	#PopupIframe
			        	{
				        	position:absolute; 
				        	top:90px; 
				        	left:100px; 
				        	width:800; 
				        	height:110; 
				        	background:white; 	        		
				        	overflow:visible; 
				        	border:none;
				        	z-index:2;
				        	display:none;	
			        	}
			        	
			        	#RegStandardsPopup
			        	{
				        	position:absolute;
				        	left:100px;
				        	top:70px;	        		
				        	width:800px;
				        	height:110px;
				        	border:2px solid #A7A6AA;		        	
				        	background-color: #<xsl:value-of select="$vDesktopColor"/>;	        		
				        	z-index:3;
				        	padding:10px;
				        	display:none;
			        	}
			        	
			        	.PopupSectionDiv
			        	{
				        	width:100%;
				        	height:30px;	        		
				        	position:relative;	        		
			        	}
			        	
			        	.PopupLbl
			        	{
				        	width:140px;		        			        
				        	position:absolute;		        	
				        	top:6px;		        			        		        
			        	}
			        	
			        	.PopupInput
			        	{
				        	position:absolute;
				        	width:200px;
				        	top:0px;
			        	}
			        	
			        	.DetailsSectionDiv
			        	{
			        		position:relative;
			        		width:100%;
			        		height:20px;			        		
			        	}
			        	
			        	.DetailsDiv
			        	{
			        		width:1000px;
			        		height:160px;
			        		background-color:transparent;
			        		color:black;
			        		overflow:hidden;
			        		position:absolute;
			        		top:13px;
			        		left:-30px;
			        		padding:10px;
			        		display:none;			
			        		text-align:center;
			        		       	
			        	}
			        	
			        	.DetailsContentsDiv
			        	{
			        		width:850px;
			        		height:145px;
			        		border:1px solid #A7A6AA;
			        		padding:5px;
			        		background-color:<xsl:value-of select="$vDesktopColor"/>;
			        	}
			        	
			        	.DetailsLbl
			        	{
			        		position:absolute;
			        		width:200px;
			        		overflow:hidden;
			        	}
			        	
			        	.expandBtn
			        	{
			        		width:15px;
			        		height:15px;
			        		overflow:hidden;
			        		background:url(<xsl:value-of select="$vURL"/>images/expand.png);
			        		cursor:pointer;
			        	}    	
			        	
			        	.collapseBtn
			        	{
				        	width:15px;
				        	height:15px;
				        	overflow:hidden;
				        	background:url(<xsl:value-of select="$vURL"/>images/collapse.png);
				        	cursor:pointer;
			        	}
			        	
			        </style>                                
       	 		</head>
        
		        <body style="overflow:auto;" class="Desktop_Background" onload="loading()">
		        	<!-- SCREEN DIV -->         				
			        <div id="ScreenDiv">
			        	
			        	<!-- CONTENTS DIV -->
		        		<div id="ContentsDiv">
		        			<div id="RegRuleFilterDiv" class="ContentsSectionDiv">		        				
		        				<span style="height:100%; width:120px; padding-top:4px; text-align:left">
		        					<span class="Desktop_Lbl" style="top:6px;">Regulation Rule:</span>
		        				</span>
		        				<span style="height:100%; width:165px; padding-top:4px;">
		        					<select style="width:155px" id="regRuleFilterFld">
		        						<xsl:for-each select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'regRules']/Element">
		        							<option>
		        								<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
		        								<xsl:if test="code = ''">
		        									ALL
		        								</xsl:if>
		        								<xsl:if test="not( code = '' )">
		        									<xsl:value-of select="value"/>	
		        								</xsl:if>		        								
		        							</option>		        							
		        						</xsl:for-each>
		        					</select>
		        				</span>
		        				<span style="height:100%;">
		        					<input class="ActionBtn Desktop_Btn" type="button" value="Search" onclick="clickHandler_searchBtn()"/>
		        				</span>
		        			</div>
		        			<div id="RegStandardsListDiv" class="Desktop_TableDiv ContentsSectionDiv">
		        				<xsl:call-template name="RegStandardsList_Tmpl">		        				
		        				</xsl:call-template>
		        			</div>
		        			<div id="ActionButtonsDiv" class="ContentsSectionDiv">
		        				<span style="padding-right:10px;">
			        				<input id="btnAddRegStandard" type="button" value="Add" class="Desktop_Btn ActionBtn" onclick="clickHandler_addRegStandardBtn()" disabled="true"/>
		        					<input id="btnModifyRegStandard" type="button" value="Modify" class="Desktop_Btn ActionBtn" onclick="clickHandler_modifyRegStandardBtn()" disabled="true"/>
		        					<input id="btnDeleteRegStandard" type="button" value="Delete" class="Desktop_Btn ActionBtn" onclick="clickHandler_deleteRegStandardBtn()" disabled="true"/>
			        			</span>
			        			<span>        				
		        					<input id="btnMore" type="button" value="More" class="Desktop_Btn ActionBtn" onclick="clickHandler_moreBtn()" disabled="true"/>
		        				</span>
		        			</div>
		        			<div id="ScreenButtonsDiv" class="ContentsSectionDiv">
		        				<input id="btnClose" name="btnClose" type="button" value="Close" class="Desktop_Btn ScreenBtn" onclick="clickHandler_closeBtn()"/>
		        				<input id="btnConfirmDlg" name="btnConfirmDlg" style="display:none"/>
		        			</div>     
		        		</div>
		        		
		        		<!-- POPUP IFRAME -->
			        	<iframe id="PopupIframe" frameborder="0" class="PopupIframe">
			        		<xsl:attribute name="src">
			        			javascript: "Loading ..."
			        		</xsl:attribute>
			        	</iframe>
			        	
			        	<!-- POPUP -->
			        	<div id="RegStandardsPopup">
			        		<input type="hidden" id="Popup_regStandardIdFld"/>
			        		<input type="hidden" id="Popup_delDocId"/>
			        		<div id="Popup_deleteConfirm" class="PopupSectionDiv" style="display:none">	        		
			        			<span class="Desktop_Lbl PopupLbl" style="top:0px; left:0px; font-weight:bold; width:100%; text-align:center; padding-bottom:5px;">
			        				Regulatory Standard might be in use by existing accounts.  Do you want to proceed with the 'deletion'?
			        			</span>	        				        
			        		</div>
			        		<div class="PopupSectionDiv" style="z-index:20">	        		
			        			<span class="Desktop_Lbl PopupLbl" style="left:0px;">
			        				Regulation Rule:
			        			</span>
			        			<select id="Popup_regRuleFld" class="Desktop_Input PopupInput" style="left:140px" disabled="true" onchange="changeHandler_regulationRuleFld()">			        				
			        				<xsl:for-each select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'regRules']/Element">
			        					<option>
			        						<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
			        						<xsl:attribute name="closedCountry"><xsl:value-of select="closedCountry"/></xsl:attribute>
			        						<xsl:attribute name="regCodeDflt"><xsl:value-of select="regCodeDflt"/></xsl:attribute>
			        						<xsl:value-of select="value"/>
			        					</option>							        					
			        				</xsl:for-each>	
			        			</select>			        					        
			        			
			        			<span class="Desktop_Lbl PopupLbl" style="left:390px;">
			        				Country:
			        			</span>
			        			<select id="Popup_countryFld" class="Desktop_Input PopupInput" style="left:540px" disabled="true">			        				
			        				<xsl:for-each select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'regCountries']/Element">
			        					<option>
			        						<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>			        						
			        						<xsl:value-of select="value"/>
			        					</option>							        					
			        				</xsl:for-each>	
			        			</select>
			        		</div>
			        		<div class="PopupSectionDiv"  style="z-index:19">	        		
			        			<span class="Desktop_Lbl PopupLbl" style="left:0px;">
			        				Regulatory Code:
			        			</span>
			        			<input id="Popup_regCodeFld" class="Desktop_Input PopupInput" style="left:140px" disabled="true"/>
			        			
			        			<span class="Desktop_Lbl PopupLbl" style="left:390px;">
			        				Province:
			        			</span>
			        			<select id="Popup_provinceFld" class="Desktop_Input PopupInput" style="left:540px" disabled="true">			        				
			        				<xsl:for-each select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'regProvinces']/Element">
			        					<option>
			        						<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>			        						
			        						<xsl:value-of select="value"/>
			        					</option>							        					
			        				</xsl:for-each>	
			        			</select>			        				
			        		</div>
			        		<div class="PopupSectionDiv"  style="z-index:18">	        		
			        			<span class="Desktop_Lbl PopupLbl" style="left:0px;">
			        				Description:
			        			</span>
			        			<input id="Popup_descriptionFld" class="Desktop_Input PopupInput" style="left:140px; width:600px" disabled="true"/>			        				
			        		</div>
			        		<div class="PopupSectionDiv"  style="z-index:17">	        		
			        			<span class="Desktop_Lbl PopupLbl" style="left:0px;">
			        				Effective Date:
			        			</span>			        						        		
		        				<input id="Popup_effDateFld" ifdsDatepicker="true" class="Desktop_Datepicker PopupInput" style="left:140px" disabled="true"/>
			        			<span class="Desktop_Lbl PopupLbl" style="left:390px;">
			        				Stop Date:
			        			</span>			        						        		
			        			<input id="Popup_stopDateFld" ifdsDatepicker="true"  class="Desktop_Datepicker PopupInput" style="left:540px;" disabled="true">
			        				<xsl:attribute name="dateFormat"><xsl:value-of select="$dateFormat"/></xsl:attribute>
			        			</input>			        							        	
			        		</div>
			        		<div class="PopupSectionDiv"  style="z-index:16">	        		
			        			<span class="Desktop_Lbl PopupLbl" style="left:0px;">
			        				Investor Type:
			        			</span>
			        			<select id="Popup_investorTypeFld" class="Desktop_Input PopupInput" style="left:140px" disabled="true">			        				
			        				<xsl:for-each select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'investorTypes']/Element">
			        					<option>
			        						<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
			        						<xsl:value-of select="value"/>
			        					</option>							        					
			        				</xsl:for-each>	
			        			</select>			        				
			        			<span class="Desktop_Lbl PopupLbl" style="left:390px; width:200px;">
			        				Invest on behalf of 3rd party:
			        			</span>
			        			<select id="Popup_invest3rdPartyFld" class="Desktop_Input PopupInput" style="left:610px; width:75px" disabled="true">
			        				<option/>
			        				<option value="yes">Yes</option>
			        				<option value="no">No</option>
			        			</select>
			        		</div>
			        		<div class="PopupSectionDiv"  style="z-index:15; height:75px">
			        			<span class="Desktop_Lbl PopupLbl" style="left:0px;">
			        				Tax Type(s):
			        			</span>
			        			<select id="Popup_taxTypeFld" class="Desktop_Input PopupInput" style="left:140px; height:70px; width:460px;" multiple="true" size="4" disabled="true">
			        				<xsl:for-each select="/websrvXML/dtRegStandardsInitResponse/List[@listName = 'taxTypes']/Element">
			        					<option>
			        						<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
			        						<xsl:value-of select="value"/>
			        					</option>							        					
			        				</xsl:for-each>	
			        			</select>
			        		</div>
			        		<div class="PopupSectionDiv" style="padding-top:10px; text-align:center; z-index:14">
			        			<div id="Popup_docListDiv" class="Desktop_TableDiv" style="width:750; height:80; overflow-x:scroll">
			        				<table id="Popup_docListTable" ifdsTable="true" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" rowSelectable="true">
			        					<thead>
			        						<tr>
			        							<td style="width:80">DocCode</td>
				        						<td style="width:1100">Description</td>
				        					</tr>
			        					</thead>
			        					<tbody>
			        						
			        					</tbody>
			        				</table>
			        			</div>				        				
			        		</div>
			        		<div class="PopupSectionDiv" style="text-align:center; padding-bottom:10px; z-index:13">
			        			<span style="width:617px; text-align:right">
			        				<input type="button" id="Popup_addDocBtn" value="Add" style="width:60px;" onclick="clickHandler_addDocBtn()" disabled="true"/>
			        				<input type="button" id="Popup_deleteDocBtn" value="Delete"  style="width:60px;" onclick="clickHandler_deleteDocBtn()" disabled="true"/>
				        		</span>
			        		</div>			 			        					        					        	
			        		<div class="PopupSectionDiv" style="text-align:center; z-index:10;">
			        			<input type="button" id="btnOK" value="OK" class="Desktop_Btn ActionBtn" onclick="clickHandler_saveBtn()" style="display:none"/>
			        			<input type="button" id="btnSave" value="Save" class="Desktop_Btn ActionBtn" onclick="clickHandler_saveBtn()" style="display:none"/>
			        			<input type="button" id="btnCancel" value="Cancel" class="Desktop_Btn ActionBtn" onclick="clickHandler_cancelBtn()"/>
			        		</div>
			        	</div>	        		       
		        	</div>
		        </body> 
      		</html>
    	</Screen>
	</xsl:template>
    

</xsl:stylesheet>
