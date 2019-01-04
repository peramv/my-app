<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  

    
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
			<title>Declaration of Trust and Addendum Screen</title>
			
			<!-- web library js code -->
        	<script src="{$vURL}WebLibrary/JSLib/Err.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
        	<script src="{$vURL}WebLibrary/JSLib/XML.js"/>
        	
        	<script src="{$vURL}javascript/General_DesktopError.js"/>
        	<script src="{$vURL}javascript/General_Desktop.js"/>
			        
			<!-- page specific js code -->          
			<script src="{$vURL}javascript/DOTAndAddendum.js"/>
			       
			<script>
			var _vURL = "<xsl:value-of select="$vURL"/>";
			var _vServletPath = "<xsl:value-of select="$vServletPath"/>";
			var _vCZ = "<xsl:value-of select="$vCZ"/>";
			var _companyCode 	= "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
			var _ruserId     	= "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
			var _sessionId   	= "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
			var _envName   		= "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";          
			var _dateFormat   	= "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
			
			var _accountNum     = "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>";
			var _requestRecNum 	= <xsl:value-of select="/websrvXML/message/request/dtDOTInitRequest/data/requestRecNum"/>;
			
			setSessionToken( _sessionId );		 				
			
			function loading()
			{            	
				<xsl:if test="/websrvXML/dtDOTInitResponse/RequestStatus/status = 'Accepted' ">            	
					initDOT();	
				</xsl:if>			                		
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
		        	left:20px;
		        	top:20px;
		        	width:680px;
		        	height:600px;		        	
	        	}
	        	
	        	.ContentsDiv
	        	{
	        		position:absolute;
	        		left:0px;
	        		top:0px;
	        		width:660px;
	        		height:470px;
	        		border:1px solid black;
	        	}
	        		        	
	        	.DOTTable
	        	{	        	
	        		position:absolute;
	        		left:20px;
	        		top:20px;
	        		width:620px;
	        		height:400px; 
	        		border:1px solid black; 
	        		background:white;
	        		overflow-Y:scroll;
	        	}
	        	
	        	.ButtonsDiv
	        	{
	        		position:absolute;
	        		left:20px;
	        		top:445px;
	        		width:600px;
	        		height:25px; 
	        		border:1px solid black; 	        		
	        	}
	        	
	        	.DOTTable .DOTDataHeader
	        	{
		        	border-bottom:1px solid black;
		        	border-right:1px solid black;		        	
		        	height:20px;
		        	font-weight:bold;
		        	text-align:center;
		        	background:#939496;
	        	}
	        	
	        	.DOTTable .DOTRow_even
	        	{              
	        		background:white;
	        	}
	        	
	        	.DOTTable .DOTRow_odd
	        	{              
	        		background:#E9E9E9;
	        	}
	        	
	        	.DOTTable .DOTDataItem
	        	{
		        	border-bottom:1px solid black;
		        	border-right:1px solid black;
		        	height:20px;
		        	padding-left:2px;
		        	border-collapse: collapse;
	        	}
	        	
	        	.RecordRangeDiv
	        	{
	        		position:absolute;
	        		left:20px;
	        		top:425px;
	        		width:620px;
	        		height:25px;	        		
	        	}
	        	
	        	.CloseBtn
	        	{
	        		position:absolute;
	        		left:260;
	        		top:490px;
	        		width:120px;	        		
	        	}	        		        	
	        </style>                                
        </head>
        
        <body onload="loading()" style="overflow:auto;" class="DesktopScreen">         
		
        	<div id="mainDiv" class="MainDiv">
        		<div class="ContentsDiv">
        			
	        		<div id="DOTTableDiv" class="DOTTable">			
	        			<table id="DOTTable" cellpadding="0" cellspacing="0" style="table-layout:fixed">
	        				<thead>
	        					<tr>
	        						<td  class="DOTDataHeader" style="width:200;">
	        							File Type
	        						</td>
	        						<td  class="DOTDataHeader" style="width:200;">
	        							Date of Issue
	        						</td>
	        						<td  class="DOTDataHeader" style="width:200;">	
	        							User
	        						</td>		
	        					</tr>
	        				</thead>					
	        				<tbody>        					        				
		        				<xsl:for-each select="/websrvXML/dtDOTInitResponse/OutputActionList/OutputAction">	        					
		        					<tr>
		        						<xsl:attribute name="fileType">
		        							<xsl:value-of select="fileType"/>
		        						</xsl:attribute>
		        						<xsl:attribute name="fileTypeDesc">
		        							<xsl:value-of select="fileTypeDesc"/>
		        						</xsl:attribute>
		        						<xsl:attribute name="Deff">
		        							<xsl:value-of select="Deff"/>
		        						</xsl:attribute>
		        						<xsl:attribute name="userName">
		        							<xsl:value-of select="userName"/>
		        						</xsl:attribute>		        						
		        						<xsl:attribute name="class">
		        							<xsl:if test="( position() - 1 ) mod 2 = 0">DOTRow_even</xsl:if>
		        							<xsl:if test="not( ( position() - 1 ) mod 2 = 0 )">DOTRow_odd</xsl:if>
		        						</xsl:attribute>
		        						
		        						<td class="DOTDataItem">
		        							<xsl:value-of select="fileTypeDesc"/>
		        						</td>	
		        						<td class="DOTDataItem">
		        							<xsl:value-of select="Deff"/>
		        						</td>
		        						<td class="DOTDataItem">
		        							<xsl:value-of select="userName"/>
		        						</td>								
		        					</tr>
		        				</xsl:for-each>
	        				</tbody>
	        			</table>	
	        		</div>
	        		<div class="RecordRangeDiv">
	        			<span style="width:50%; text-align:left; padding-bottom:5px;">
	        				<span>Records: </span>
	        				<span id="recordRange_start">
	        					<xsl:attribute name="rangeStart">
	        						<xsl:value-of select="/websrvXML/dtDOTInitResponse/RecordRange/rangeStart"/>
	        					</xsl:attribute>
	        					<xsl:value-of select="/websrvXML/dtDOTInitResponse/RecordRange/rangeStart"/>
	        				</span>
	        				<span> - </span>
	        				<span id="recordRange_end">
	        					<xsl:attribute name="rangeEnd">
	        						<xsl:value-of select="/websrvXML/dtDOTInitResponse/RecordRange/rangeEnd"/>
	        					</xsl:attribute>
	        					<xsl:value-of select="/websrvXML/dtDOTInitResponse/RecordRange/rangeEnd"/>
	        				</span>	
	        			</span>
	        			
	        			<span style="width:50%; text-align:right;">
		        			<span style="padding-left:10px">
		        				<input id="prevBtn" type="button" value="Prev." style="width:80px">
		        					<xsl:if test="/websrvXML/dtDOTInitResponse/RecordRange/rangeStart = 1">
		        						<xsl:attribute name="disabled">true</xsl:attribute>
		        					</xsl:if>		        							        					
		        				</input>
		        			</span>
		        			<span style="padding-left:5px">
		        				<input id="nextBtn" type="button" value="Next" style="width:80px;">
		        					<xsl:if test="/websrvXML/dtDOTInitResponse/RecordRange/moreRecordsExist = 'no'">
		        						<xsl:attribute name="disabled">true</xsl:attribute>
		        					</xsl:if>	
		        				</input> 
		        			</span>
		        		</span>
	        		</div>
        		</div>
        		<input id="btnClose" name="btnClose" type="button" value="Close" class="CloseBtn"/>
        		
        	</div>
			
        </body>
      </html>
    </Screen>

  </xsl:template>
    

</xsl:stylesheet>
