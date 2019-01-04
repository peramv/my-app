<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes" />
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>  
  
	<xsl:variable name="vClient"       		select="/websrvXML/requestInfo/client"/>
	<xsl:variable name="vServletPath"  		select="/websrvXML/requestInfo/servletPath"/>
	<xsl:variable name="vDataDir"      		select="/websrvXML/transformNode/datadir"/>
	<xsl:variable name="vURL"         		select="concat( $vDataDir, $vClient, '/' )"/>
	<xsl:variable name="vTX"           		select="/websrvXML/FormInformation/tx"/>
	<xsl:variable name="vCZ"           		select="/websrvXML/FormInformation/cz"/>          
	<xsl:variable name="vTIDX"         		select="/websrvXML/FormInformation/tidx"/>  
	<xsl:variable name="dateFormat"    		select="/websrvXML/FormInformation/dateFormat"/>
	<xsl:variable name="vDesktopColor"    	select="/websrvXML/FormInformation/bgcolor"/>

  
  	<xsl:template match="/">

		<Screen>
      
      		<html>
        
				<head>
					<title>Release Frozen Account</title>
					
					<!-- web library js code -->
					<script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
					<script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
					<script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
					<script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
					<script src="{$vURL}WebLibrary/JSLib/Err.js"/>
					<script src="{$vURL}WebLibrary/JSLib/XML.js"/>
					
					
					<!-- page specific js code -->
        			<script src="{$vURL}javascript/ReleaseFrozenAcct.js"/>
					<script src="{$vURL}javascript/General_Desktop.js"/>         			
					<script src="{$vURL}javascript/General_DesktopError.js"/> 
        			
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
						
						setSessionToken( _sessionId );
						
        				function loading()
        				{               					     	        					           
	        				initReleaseFrozenAcct();	        							                	
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
				        	
				        	font-family:Arial;
							font-size: 14px;    	
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
			        	
			        	.TopSectionDiv
			        	{	     	
			        		position:relative;
				        	width:100%;	
				        	height:74px;	        			        			        		        
			        	}
			        	
			        	#ActionsSectionDiv
			        	{	     	
			        		position:relative;
			        		border:#AFAFAF 1px solid;
				        	width:400px;
				        	height:282px;
				        	z-index:0;	     		        			        		        
			        	}
			        	
			        	.ActionsTitleDiv
			        	{
			        		position:absolute;
			        		top:-10px;
			        		left:7px;
			        		width:155px;
			        		text-align:left;			        					        	
			        	}
			        	
			        	.ActionsTitleLbl
			        	{			        		
							background-color: #<xsl:value-of select="$vDesktopColor"/>;
			        	}
			        	
			        	.BottomSectionDiv
			        	{	     	
			        		position:relative;
				        	width:100%;	
				        	height:54px;	    			        			        		        
			        	}
			        	
			        	#ActionsTableDiv
			        	{	 
			        		position:relative;
			        		width:92%; 	
			        		top:11px;       			        		        
			        	}
			        	
			        	.ActionsRowDiv
			        	{	     	
			        		aligh:right;   
			        		height:30px;			        			        		        
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
			        	
			        	#UpdateButtonDiv
			        	{
			        		padding-top:20px;
			        	}
			        	
			        	#CloseButtonDiv
			        	{
			        		height:50px;
			        		text-align:center;
			        		padding-top:30px;
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
		        	
		        	</style>  
					                       
       	 		</head>
        
      			<body onload="loading()" class="Desktop_Background">
			        <div id="ScreenDiv">
		        		<div id="ContentsDiv">
		        		
		        			<div id="ActionNumberDiv" class="TopSectionDiv">
		        				<center>
		        					<table style="width:75%">
			        					<tr>
			        						<td><b>Account Number:</b></td>
					        				<td><input id="accountFld" size='42'/></td>
					        				<td><input id="btnLookup" type="button" value="Lookup" class="ScreenBtn" onclick="clickHandler_LookupBtn()"/>  </td>    				
						        		</tr>
			        				</table>
			        			</center>
			        		</div>
							<center>
		        			<div id="ActionsSectionDiv">			
								<div class="ActionsTitleDiv">
									<span class="ActionsTitleLbl" style="padding-left:5px; padding-right:3px;">Account:</span>
									<span class="ActionsTitleLbl" style="padding-right:5px;" id="accountLbl"></span>
								</div>
								
									<table id="ActionsTableDiv">
										<tr align="right">
											<td class="ActionsRowDiv">Remove curator file statement date</td>
											<td>
												<select id="rmStmtDateFld" style="width:110px" selectedIndex="-1" value="" disabled="true">																																	
                                   				</select>
                                   			</td>
                                   		</tr>
                                   		<tr align="right">
											<td class="ActionsRowDiv">Stop NFU</td>
											<td>
												<select id="stopNFUFld" style="width:110px" selectedIndex="-1" value="" disabled="true">													
                                   				</select>
                                   			</td>
                                   		</tr>
                                   		<tr align="right">
											<td class="ActionsRowDiv">Stop Purchase</td>
											<td>
												<select id="stopPurchaseFld" style="width:110px" selectedIndex="-1" value="">													
                                   				</select>
                                   			</td>
                                   		</tr>
                                   		<tr align="right">
											<td class="ActionsRowDiv">Stop Redemption</td>
											<td>
												<select id="stopRedempFld" style="width:110px" selectedIndex="-1" value="">													
                                   				</select>
                                   			</td>
                                   		</tr>
                                   		<tr align="right">
											<td class="ActionsRowDiv">Stop Transfer/Exchange Out</td>
											<td>
												<select id="stopTransferOutFld" style="width:110px" selectedIndex="-1" value="">													
                                   				</select>
                                   			</td>
                                   		</tr>
                                   		<tr align="right">
											<td class="ActionsRowDiv">Stop Transfer/Exchange In</td>
											<td>
												<select id="stopTransferInFld" style="width:110px" selectedIndex="-1" value="">													
                                   				</select>
                                   			</td>
                                   		</tr>
                                   		<tr align="right">
											<td class="ActionsRowDiv">Reactive PAC/SWP</td>
											<td>
												<select id="reactivePACSWPFld" style="width:110px" selectedIndex="-1" value="">													
                                   				</select>
                                   			</td>
                                   		</tr>	
									</table>
									<div id="UpdateButtonDiv" class="ContentsSectionDiv">
									<input id="btnUpdate" type="button" value="Update" class="ScreenBtn" onclick="clickHandler_UpdateBtn()"/>
									</div>
			        		</div></center>
							<center>
			        		<div id="CloseButtonDiv" class="ContentsSectionDiv">
		        				<input id="btnClose" name="btnClose" type="button" value="Close" class="Desktop_Btn ScreenBtn"/>
		        			</div> 
		        			</center>       		
		        		</div>
		        		
		        		<iframe id="PopupIframe" frameborder="0" class="PopupIframe">
		        			<xsl:attribute name="src">
		        				javascript: "Loading ..."
		        			</xsl:attribute>
		        		</iframe>
		        		
		        	</div>
		       	</body> 
      		</html>
    	</Screen>
	</xsl:template>
    

</xsl:stylesheet>
