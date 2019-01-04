<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
    
  <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/LIFGainLoss_TransTemplate.xsl"/>
    
  <xsl:variable name="vClient"       	select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath"  	select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir"      	select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL"         	select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX"           	select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ"           	select="/websrvXML/FormInformation/cz"/>          
  <xsl:variable name="vTIDX"         	select="/websrvXML/FormInformation/tidx"/>  
  <xsl:variable name="dateFormat"    	select="/websrvXML/FormInformation/dateFormat"/>

  
  <xsl:template match="/">

    <Screen>
      
      <html>
        
        <head>
			<title>LIF Gain/Loss</title>
			
			<!-- web library js code -->
        	<script src="{$vURL}WebLibrary/JSLib/Err.js"/>          
        	<script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/XML.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>        	
        	<script src="{$vURL}WebLibrary/WebComps/SuggestFieldComponent.js"/>
        	
        	<!-- general Desktop js code -->
        	<script src="{$vURL}javascript/General_Desktop.js"/>
        	<script src="{$vURL}javascript/General_DesktopError.js"/>
			        
			<!-- page specific js code -->
        	<script src="{$vURL}javascript/LIFGainLoss.js"/>          
			
			       
			<script>
			var _vURL 			= "<xsl:value-of select="$vURL"/>";
			var _vServletPath 	= "<xsl:value-of select="$vServletPath"/>";
			var _vCZ 			= "<xsl:value-of select="$vCZ"/>";
			var _companyCode 	= "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
			var _ruserId     	= "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
			var _sessionId   	= "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
			var _envName   		= "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";          
			var _dateFormat   	= "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
			var _accountNum		= "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>";
			
			setSessionToken( _sessionId );
			
			
			function loading()
			{            	
				<!--xsl:if test="/websrvXML/dtLIFGainLossInitResponse/RequestStatus/status = 'Accepted' "-->            	
					initLIFGainLoss();						
				<!--/xsl:if-->			                		
			}
			</script>
          
	        <style>
	        	BODY, DIV, TABLE, TD, LEGEND
	        	{
		        	font-family:  CourierNew,  Verdana, Arial, Sans-Serif;
		        	font-size: 10pt;
		        	cursor: default;    
	        	}
	        		        	
	        	.DesktopScreen
	        	{
	        		background-color: #<xsl:value-of select="/websrvXML/FormInformation/bgcolor"/>;	        			        			        	
	        	}
	        	
	        	.MainDiv
	        	{
		        	position:absolute;
		        	left:0px;
		        	top:0px;		        		        			       
	        	}
	        	
	        	.ContentsDiv
	        	{
	        		position:absolute;
	        		left:10px;
	        		top:10px;
	        		width:1150px;
	        		height:600px;
	        	}
	        	
	        	.FilterDiv
	        	{
	        		position:absolute;
	        		left:312px;
	        		top:0px;
	        		width:260px;
	        		height:30px;
	        		font-weight:bold;	        		
	        	}
	        	
	        	.TransDiv
	        	{
	        		position:absolute;
	        		left:0px;
	        		top:40px;
	        		width:917px;
	        		height:300px;
	        		border:1px solid black;
	        		background:white;
	        		overflow-Y:scroll;	        		
	        	}
	        	
	        	.TranTable_header
	        	{
		        	border-bottom:1px solid black;
		        	border-right:1px solid black;		        	
		        	height:20px;
		        	font-weight:bold;
		        	text-align:center;
		        	background:#939496;
	        	}
	        	
	        	.TransTable_evenRow
	        	{
	        		background:white;
	        	}
	        	
	        	.TransTable_oddRow
	        	{
	        		background:#E9E9E9;
	        	}
	        	
	        	.TransTable_cell
	        	{
		        	border-bottom:1px solid black;
		        	border-right:1px solid black;		        	
		        	padding-left:2px;
		        	border-collapse: collapse;
		        	height:32px;
		        	padding-top:3px;		        	
		        }
		        
		        .TransTable_data
		        {
		        	white-space: nowrap;
		        	overflow:hidden;
		        	text-overflow: ellipsis;
		        	width:100%;
		        }
		        
		        .UpdateBtn
		        {
		        	font-size:9px;
		        	width:42px;
		        }
		        
		        
	        	.GainLossTotalDiv
	        	{
	        		position:absolute;
	        		left:600px;
	        		top:365px;
	        		width:295px;	        		
	        		height:35px;
	        		border:1px solid black;
	        		background:white;
	        		padding-left:5px;
	        		padding-right:5px;
	        		padding-top:10px;
	        		padding-bottom:10px;
	        		
	        	}	        		        	
	        	
	        	.CloseBtn
	        	{
		        	position:absolute;
		        	left:415;
		        	top:420px;
		        	width:120px;	        		
	        	}
	        	.ConfirmDlgBtn
	        	{
		        	position:absolute;
		        	left:415;
		        	top:420px;
		        	width:120px;
		        	display:none;	        		
	        	}
	        	
	        	.PopupIframe
	        	{
	        		position:absolute; 
	        		top:150px; 
	        		left:250px; 
	        		width:300; 
	        		height:150; 
	        		background:white; 	        		
	        		overflow:visible; 
	        		border:none;
	        		z-index:1999;
	        		display:none;	
	        	}
	        	
	        	
	        	.GainLossPopup
	        	{
	        		position:absolute;
	        		left:250px;
	        		top:150px;	        		
	        		width:300px;
	        		height:150px;
	        		border:2px solid black;
	        		background-color: #<xsl:value-of select="/websrvXML/FormInformation/bgcolor"/>;	        		
	        		z-index:2000;
	        		padding:10px;
	        		display:none;
	        	}
	        	
	        	.GainLossPopup_label
	        	{
	        		width:100px;
	        		font-weight:bold;
	        		padding-bottom:5px;	        		
	        	}
	        	
	        	.GainLossPopup_input
	        	{
		        	width:245px;	   
		        	padding-bottom:5px;     				        
	        	}
	        </style>                                
        </head>
        
        <body onload="loading()" style="overflow:auto;" class="DesktopScreen">                         	
        	<div id="MainDiv" class="MainDiv">
        		<div class="ContentsDiv">
	        		<div class="FilterDiv">
						<span style="padding-right:10">Year Filter:</span>						
	        			<select id="lifPrevYear" style="width:75">
	        				<xsl:variable name="selectedYear" select="/websrvXML/dtLIFGainLossInitResponse/ListSelection[@id = 'lifPrevYears']"/>	        				
	        				<xsl:for-each select="/websrvXML/dtLIFGainLossInitResponse/List[@listName = 'lifPrevYears']/Element">
	        					<option>
	        						<xsl:if test="$selectedYear = code">
	        							<xsl:attribute name="selected">true</xsl:attribute>
	        						</xsl:if>
	        						<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>	        						
	        						<xsl:value-of select="code"/>
	        					</option>	
	        				</xsl:for-each>	        				
	        			</select>
	        			<input type="button" value="Refresh" style="position:relative; top:1px; left:20; width:80" onclick="clickHandler_refreshBtn()"/>        				        	
	        		</div>
	        		
	        		<div id="TransDiv" class="TransDiv">	       
	        			<xsl:apply-templates select="/websrvXML/dtLIFGainLossInitResponse/transactionList">	        			
	        				<xsl:with-param name="UpdAllowed" select="/websrvXML/dtLIFGainLossInitResponse/UpdFlag/UpdAllowed"/>
	        			</xsl:apply-templates>	        				        			
	        		</div>
	        		
	        		<div class="GainLossTotalDiv">
	        			<span style="padding-right:10px; font-weight:bold;">Total Gain/Loss:</span>
	        			<span style="width:150; text-align:right;">
	        				$
	        				<span id="totalGainLossVal">
	        					<xsl:value-of select="/websrvXML/dtLIFGainLossInitResponse/totalGainLoss/totGainLoss"/>
	        				</span>
	        			</span>
	        		</div>	
	        	</div>
        		<input id="btnClose" name="btnClose" class="CloseBtn" type="button" value="Close" onclick="clickHandler_closeBtn()"/>
        		<input id="btnConfirmDlg" name="btnConfirmDlg" class="ConfirmDlgBtn" type="button"/>	        		
        	</div>
        	
        	
        	<iframe id="PopupIframe" frameborder="0" class="PopupIframe">
        		<xsl:attribute name="src">
        			javascript: "Loading ..."
        		</xsl:attribute>
        	</iframe>
        	
        	<div id="GainLossPopup" class="GainLossPopup">        		
        		<table cellpadding="0" cellspacing="0" style="table-layout:fixed; position:relative;">        			
        			<tr>
        				<td class="GainLossPopup_label" style="padding-top:5px;">Trans Num</td>
        				<td class="GainLossPopup_input">
        					<input type="text" id="transNumFld" disabled="true" style="width:100%"/>
        				</td>
        			</tr>      			
        			<tr>
        				<td class="GainLossPopup_label" style="padding-top:5px;">Eff Date</td>
        				<td class="GainLossPopup_input">
        					<input type="text" id="effDateFld" disabled="true" style="width:100%"/>
        				</td>
        			</tr>
        			<tr>
        				<td class="GainLossPopup_label" style="padding-top:5px;">Gain/Loss</td>
        				<td class="GainLossPopup_input">
        					<input type="text" id="gainLossFld" style="width:100%"/>
        				</td>
        			</tr>
        		</table>
        		<div style="width:400; text-align:center; padding-top:10px;">        			
        			<input type="button" value="Save" style="width:100px;" onclick="clickHandler_saveUpdateBtn()"/>
        			<input type="button" value="Cancel" style="width:100px;" onclick="clickHandler_cancelUpdateBtn()"/>
        		</div>	
        	</div>		
        </body>
      </html>
    </Screen>

  </xsl:template>
  
  
	
  
    

</xsl:stylesheet>
