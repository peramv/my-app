<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/RegDoc_ListTemplate.xsl"/>
    
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
			<title>Regulatory Documents</title>
			
			<!-- web library js code -->
        	<script src="{$vURL}WebLibrary/JSLib/Err.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/XML.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
        	
        	<script src="{$vURL}WebLibrary/WebComps/IFDSTable.js"/>
        	
        	<script src="{$vURL}javascript/General_DesktopError.js"/>
        	<script src="{$vURL}javascript/General_Desktop.js"/>
			        
			<!-- page specific js code -->
        	<script src="{$vURL}javascript/RegDoc.js"/>        
        	
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
			
			var _userPermissionMap = {};
			_userPermissionMap["run"] = "<xsl:value-of select="/websrvXML/dtRegDocListsInitResponse/userPermissions/run"/>";
			_userPermissionMap["mod"] = "<xsl:value-of select="/websrvXML/dtRegDocListsInitResponse/userPermissions/mod"/>";
			_userPermissionMap["add"] = "<xsl:value-of select="/websrvXML/dtRegDocListsInitResponse/userPermissions/add"/>";
			_userPermissionMap["del"] = "<xsl:value-of select="/websrvXML/dtRegDocListsInitResponse/userPermissions/del"/>";
			
			setSessionToken( _sessionId );
						
			function loading()
			{            	
				<xsl:if test="/websrvXML/dtRegDocListsInitResponse/RequestStatus/status = 'Accepted' ">            	
					initRegDoc();		
				</xsl:if>			                		
			}                                                           
			  
			</script>
			
        	
			
        	<xsl:call-template name="DesktopCSSTmpl">
        		<xsl:with-param name="DesktopColor" select="$vDesktopColor"/>        			        		
        	</xsl:call-template>
          
	        <style>	        	
	        	#ScreenDiv
	        	{
	        		background-color: #<xsl:value-of select="$vDesktopColor"/>;
		        	position:absolute;
		        	left:0px;
		        	top:0px;
		        	width:882px;
		        	padding-left:30px;
		        	padding-right:30px;
		        	height:500px;
		        	padding-top:30px;
		        	padding-bottom:30px;		        	
	        	}
	        	
	        	#ContentsDiv
	        	{
		        	position:relative;
		        	width:822px;
		        	height:440px;
		        	z-index:0;
	        	}
	        	
	        	.ContentsSectionDiv
	        	{	        	
	        		position:relative;
		        	width:100%;		        			        			        		        
	        	}
	        	
	        	#DocListDiv
	        	{
	        		height:340px;
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
		        	top:150px; 
		        	left:76px; 
		        	width:700; 
		        	height:110; 
		        	background:white; 	        		
		        	overflow:visible; 
		        	border:none;
		        	z-index:2;
		        	display:none;	
	        	}
	        		        	
	        	#DocListPopup
	        	{
		        	position:absolute;
		        	left:76px;
		        	top:150px;	        		
		        	width:700px;
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
		        	width:100px;		        			        
		        	position:absolute;		        	
		        	top:6px;		        			        		        
	        	}
	        	
	        	.PopupInput
	        	{
	        		position:absolute;
	        		width:195px;
	        	}
	        </style>                                
        </head>
        
        <body style="overflow:auto;" class="Desktop_Background" onload="loading()">         
		
        	<div id="ScreenDiv">
        		<div id="ContentsDiv">        			
        			<div id="DocListDiv" class="Desktop_TableDiv ContentsSectionDiv" style="overflow-x:scroll">			
	        			<xsl:call-template name="RegDocList_Tmpl">
	        				<xsl:with-param name="listSrc" select="/websrvXML/dtRegDocListsInitResponse/RegDocList"/>	        				
	        			</xsl:call-template>
	        		</div>
        			<div id="ActionButtonsDiv" class="ContentsSectionDiv">
        				<input id="btnAdd" type="button" value="Add" class="Desktop_Btn ActionBtn" onclick="clickHandler_addBtn()"/>
        				<input id="btnModify" type="button" value="Modify" class="Desktop_Btn ActionBtn" onclick="clickHandler_modifyBtn()"/>
        				<input id="btnDelete" type="button" value="Delete" class="Desktop_Btn ActionBtn" onclick="clickHandler_deleteBtn()"/>        				
	        		</div>
	        		<div id="ScreenButtonsDiv" class="ContentsSectionDiv">
        				<input id="btnClose" name="btnClose" type="button" value="Close" class="Desktop_Btn ScreenBtn" onclick="clickHandler_closeBtn()"/>
        				<input id="btnConfirmDlg" name="btnConfirmDlg" style="display:none"/>
        			</div>        		
        		</div>
        		
        		<iframe id="PopupIframe" frameborder="0" class="PopupIframe">
        			<xsl:attribute name="src">
        				javascript: "Loading ..."
        			</xsl:attribute>
        		</iframe>
        		
        		<div id="DocListPopup">
        			<div id="DeleteConfirm" class="PopupSectionDiv" style="display:none">	        		
        				<span class="Desktop_Lbl PopupLbl" style="left:0px; font-weight:bold; width:100%; text-align:center;">
        					Are you sure you wish to delete this record?
        				</span>	        				        
        			</div>
        			<div class="PopupSectionDiv">	        		
        				<span class="Desktop_Lbl PopupLbl" style="left:0px;">
        					DocCode:
        				</span>
        				<input type="text" id="Popup_docCodeFld" class="Desktop_Input PopupInput" style="left:120px" disabled="true"></input>		        	
        			</div>
        			<div class="PopupSectionDiv">	        		
        				<span class="Desktop_Lbl PopupLbl" style="left:0px;">
        					Description:
        				</span>
        				<input id="Popup_descriptionFld" class="Desktop_Input PopupInput" type="text" style="left:120px; width:555px;" disabled="true"></input>	        		
        			</div>
        			<div class="PopupSectionDiv" style="text-align:center">
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
