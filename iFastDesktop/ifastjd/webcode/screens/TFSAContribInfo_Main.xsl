<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>  
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/TFSAContribInfo_ListTemplate.xsl"/>
    
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
        	<title>TFSA Contribution/Withdrawal Information</title>
			
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
			_userPermissionMap["run"] = "<xsl:value-of select="/websrvXML/dtAcctContribInqResponse/userPermissions/run"/>";
			_userPermissionMap["mod"] = "<xsl:value-of select="/websrvXML/dtAcctContribInqResponse/userPermissions/mod"/>";
			_userPermissionMap["add"] = "<xsl:value-of select="/websrvXML/dtAcctContribInqResponse/userPermissions/add"/>";
			_userPermissionMap["del"] = "<xsl:value-of select="/websrvXML/dtAcctContribInqResponse/userPermissions/del"/>";
			
			setSessionToken( _sessionId );
						
			function loading()
			{            					          
				initTFSAContribInfo();									                	
			}     
			
			/**
			* init TFSA Contribution/Withdrawal Information screen 
			*/
			function initTFSAContribInfo()
			{
				IFDSTableManager.init();	
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
	        	
	        	#ContribInfoListDiv
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
	        	
	        	.Right_Align
	        	{
	        		text-align: right;
	        		padding-right: 5px;
	        	}
	        </style>                                
        </head>
        
        <body style="overflow:auto;" class="Desktop_Background" onload="loading()">         
		
        	<div id="ScreenDiv">
        		<div id="ContentsDiv">        			
        			<div id="ContribInfoListDiv" class="Desktop_TableDiv ContentsSectionDiv" style="overflow-x:scroll">			
        				<xsl:call-template name="TFSAContribInfoList_Tmpl">
        					<xsl:with-param name="listSrc" select="/websrvXML/dtAcctContribInqResponse/AcctContribList"/>	        				
	        			</xsl:call-template>
	        		</div>
        			<div id="ActionButtonsDiv" class="ContentsSectionDiv">
        				        				
	        		</div>
	        		<div id="ScreenButtonsDiv" class="ContentsSectionDiv">
        				<input id="btnClose" name="btnClose" type="button" value="Close" class="Desktop_Btn ScreenBtn"/>
        				<input id="btnConfirmDlg" name="btnConfirmDlg" style="display:none"/>
        			</div>        		
        		</div>        		        		
        	</div>        	        
        </body>
      </html>
    </Screen>
    
  </xsl:template>
    

</xsl:stylesheet>
