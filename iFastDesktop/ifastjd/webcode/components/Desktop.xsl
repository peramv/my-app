<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>
	
	<xsl:template name="DesktopCSSTmpl">
		<xsl:param name="DesktopColor"/>
		<xsl:param name="includeDatepicker">no</xsl:param>
		<xsl:param name="includeSuggest">no</xsl:param>
		
		<style>
			BODY
			{
				width:100%;
			}
			
			BODY, DIV, TABLE, TD, LEGEND, INPUT
			{
				font-family:Arial;
				font-size: 14px;	        		
				cursor: default;	        		   
			}
						
			
			.Desktop_Btn
			{
				height:30px;
				width:80px;
			}
			
			.Desktop_Lbl
			{
				text-align:left;
				position:relative;
			}
			
			.Desktop_Input
			{
				height:22px;				
			}
			
			.Desktop_TableDiv
			{
				border-top:2px solid #A7A6AA;
				border-left:2px solid #A7A6AA;
				border-bottom:2px solid #DCDFE4;
				border-right:2px solid #DCDFE4;
				background:white;
				position:relative;
			}
			
			.Desktop_Background
			{
				background-color: #<xsl:value-of select="$DesktopColor"/>;	        			        			        	
			}
			
			.Desktop_DisabledBackground
			{
				background-color: #BCBABE;
			}
			
			.Desktop_Table
			{
				table-layout:fixed;
				position:absolute;
				left:0px;
				top:0px;				
			}
			
			.Desktop_Table_HEADER
			{
				border-bottom:2px solid #A7A6AA;
				border-right:2px solid #A7A6AA;
				border-top:2px solid #DCDFE4;
				border-left:2px solid #DCDFE4;		        			        			        			        
				background:#<xsl:value-of select="$DesktopColor"/>;
				padding-left:5px;
				overflow:hidden;
				position:relative;
			}
			
			.Desktop_Table_ROW_EVEN, .Desktop_Table_ROW_ODD
			{
				background:white;
				color:black;	   
			}
			
			.Desktop_Table_ROW_SELECTED
			{
				background:url(<xsl:value-of select="$vURL"/>images/selectedRowBackground.png);
				color:white;
				background-repeat: repeat-x;					        		
			}
						
			.Desktop_Table_CELL
			{
				padding-left:5px;
				padding-top:1px;
				padding-bottom:0px;
				height:21px;
				white-space: nowrap;
				text-overflow: ellipsis;	
				overflow:hidden;	        	
			}
			
			.Desktop_Table_Data
			{
				white-space: nowrap;
				overflow:hidden;
				text-overflow: ellipsis;
				width:100%;
			}
			
			.Desktop_ExpandBtn
			{
				width:15px;
				height:15px;	        		
				color:black;
				font-weight:bold;
				cursor:pointer;
				overflow:hidden;
				padding-left:3px;													       
			}			
			
			.Desktop_CollapseBtn
			{
				width:15px;
				height:15px;	        		
				color:black;
				font-weight:bold;
				cursor:pointer;
				overflow:hidden;
				padding-left:4px;									        
			}
			
			.Desktop_ErrorFlag
			{
				background:url(<xsl:value-of select="$vURL"/>images/error.png );
				background-repeat:no-repeat;
				background-position:0px 0px;	
				height:20px;
				width:20px;
			}
			
			.Desktop_WarningFlag
			{
				background:url(<xsl:value-of select="$vURL"/>images/error.png );
				background-repeat:no-repeat;
				background-position:0px 0px;	
				height:20px;
				width:20px;
			}
		</style>
		
		<xsl:if test="not( $includeDatepicker = 'no' )">
			<xsl:call-template name="DesktopDatepickerCSS"/>
		</xsl:if>
		
		<xsl:if test="not( $includeSuggest = 'no' )">
			<xsl:call-template name="DesktopSuggestCSS"/>
		</xsl:if>
	</xsl:template>
	
	<xsl:template name="DesktopSuggestCSS">
		<style>
			.Desktop_suggestDropdown
			{
				width:450;
				height:228;				
				border:0px solid black;
				background:url('<xsl:value-of select="$vURL"/>images/SuggestDropdown_big.gif');
				padding:5px;				
			}
			
			.Desktop_suggestDropdown_veryBig
			{
				width:600;
				height:204;				
				border:0px solid black;
				background:url('<xsl:value-of select="$vURL"/>images/SuggestDropdown_veryBig.gif');
				padding:5px;				
			}
			
			.Desktop_suggestDropdownContent
			{				
				cursor:default;
				border:1px solid red;
			}
			
			.Desktop_suggestDropdownHighlight
			{
				cursor:default;
				font-size:10px;
				background: #EDEDED;
			}
		</style>
	</xsl:template>

	
	<xsl:template name="DesktopDatepickerCSS">
		<style>
			.Desktop_Datepicker
			{				
				height:22px;								
			}
			
			.calendarBtn
			{							
				position:relative;					   		
				width:24px;
				height:21px;				
				cursor:pointer;
				background-position:1px 1px;					   		
				background-image: url(<xsl:value-of select="$vURL"/>images/calendarBtn.png);
				background-repeat: no-repeat;																	
			}						
		</style>
		
		<style>
			.calendarHolder
			{
				position:absolute;
				left:0;
				top:0;
				height:159px;
				width:202px;
				background-color:none;    
			}
			
			
			.calendarHolder .calendarBackground
			{	
				height:159px;
				width:202px;
				background-image:url(<xsl:value-of select="$vURL"/>images/calendarBkgd.png);
				background-color:none;
			}
			
			/* NOTE: month elements must have position=relative */
			
			.calendarHolder .prevMonthBtn
			{  
				position:absolute;
				top:5;
				left:50; 
				height:10px;
				width:6px;
				background-image:url(<xsl:value-of select="$vURL"/>images/left_arrow.png);
				background-repeat:no-repeat; 
				cursor:pointer;
			}			
			
			
			
			.calendarHolder .monthLbl
			{
				position:absolute;
				top:2;
				left:56;
				height:17px;
				width:86px; 
				font-size:12px; 
				font-family:arial;
				font-weight:bold;
				text-align:center;
				text-transform:uppercase;
				cursor: pointer;
			}
			
			
			
			.calendarHolder .nextMonthBtn
			{
				position:absolute;
				top:5;
				left:144;
				height:10px;
				width:6px;
				background-image:url(<xsl:value-of select="$vURL"/>images/right_arrow.png); 
				background-repeat:no-repeat; 
				cursor:pointer;
			}
			
			
			
			.calendarHolder .prevYearBtn
			{
				position:absolute;
				top:4;
				left:74;
				height:10px;
				width:6px;
				background-image:url(<xsl:value-of select="$vURL"/>images/left_arrow.png); 
				background-repeat:no-repeat;
				cursor:pointer;
			}			
			
			
			
			.calendarHolder .yearLbl
			{
				position:absolute;
				top:2;
				left:85;
				height:17px;
				width:36px; 
				font-size:12px; 
				font-family:arial;
				font-weight:bold;
				text-align:center;
				cursor:pointer;
			}
			
			
			
			.calendarHolder .nextYearBtn
			{
				position:absolute;
				top:4;
				left:126;
				height:10px;
				width:6px;
				background-image:url(<xsl:value-of select="$vURL"/>images/right_arrow.png); 
				background-repeat:no-repeat; 
				cursor:pointer;
			}
			
			
			
			.calendarHolder .todayBtn
			{
				position:absolute;
				top:4;
				left:162;
				height:17px;
				width:40px;
				font-size:10px;
				font-family:arial;
				cursor:pointer;
				font-weight:bold;
				color:green;
				text-decoration:underline;
			}
			
			
			
			.calendarHolder .daynameCell
			{
				width:27px; 
				height:17px;
				font-size:10px; 				
				cursor:default;
				text-align:center;
				font-size:10px;
				font-family:arial;
				font-family:arial;
				text-decoration:underline;
				text-transform:capitalize;						
			}
			
			
			
			.calendarHolder .daycell
			{
				font-family:arial;
				font-size:10px; 
				width:27px; 
				height:17px;
				border:1px solid transparent;
				cursor:pointer;	
				text-align:center;
				padding-left:3px;
				padding-right:3px;
				border-width:1px;				
			}
			
			
			
			.calendarHolder .today
			{
				font-weight:bold;
				color:green;
				text-decoration:underline;
			}
			
			
			
			.calendarHolder .prev_or_nextMonth
			{
				font-style:italic;
				color:gray;
			}
			
			
			
			.calendarHolder .normal
			{
				padding:1px;
				border:none;
			}
			
			
			
			.calendarHolder .selected	
			{				
				padding:0px;
				border:1px solid #0087AF;
			}	
			
			
			
			.calendarHolder .highlighted
			{
				padding:0px;
				border:1px dashed black;
			}
		</style>		
	</xsl:template>
	
	<xsl:template name="DesktopPopup">
		<xsl:param name="id"/>
		<xsl:param name="caption"/>
		<xsl:param name="width">300</xsl:param>
		<xsl:param name="height">300</xsl:param>
		<xsl:param name="left">50</xsl:param>
		<xsl:param name="top">50</xsl:param>
		<xsl:param name="contents"/>
		
		<xsl:variable name="captionHeight">20</xsl:variable>
		
		<div 	id="{$id}" 
			class="Desktop_Background" 
			style="position:absolute; width:{$width}; height:{$height}; left:{$left}; top:{$top}; border:2px solid #A7A6AA; display:none">
			<iframe class="Desktop_Background" style="position:absolute; left:0; top:0; width:100%; height:100%" frameBorder="0"/>
			<div class="Desktop_Background" style="position:absolute; top:0px; left:0px; width:100%; height:100%">				
			<div id="{$id}_caption" style="height:{$captionHeight}; width:100%; background:#5A6673; padding:3px; color:white;">
				<xsl:value-of select="$caption"/>				
			</div>
			<div id="{$id}_content">
				<xsl:attribute name="style">
					height:<xsl:value-of select="$height - $captionHeight"/>; width:100%; position:relative;
				</xsl:attribute>
				
				<xsl:copy-of select="$contents"/>
				
																			
			</div>
			</div>						
		</div>		
	</xsl:template>
	
	<xsl:template name="DesktopScreenDisabler">
		<div id="DesktopScreenDisablerDiv" style="position:absolute; height:100%; width:100%; z-index:1000; background:black; filter:alpha(opacity=20); visibility:hidden;">
			<iframe style="position:absolute; left:0; top:0; width:100%; height:100%" frameBorder="0"/>
			<div class="Desktop_Background" style="position:absolute; top:0px; left:0px; width:100%; height:100%; background:black; filter:alpha(opacity=20);"/>						
		</div>
	</xsl:template>
	
	<xsl:template name="DesktopScreenProcessingIndicator">
		<div id="DesktopScreenProcessingIndicatorDiv" style="position:absolute; left:50%; top:50%; height:1px; width:1px; z-index:10000; visibility:hidden;">
			<div style="position:absolute; top:-25px; height:50px; left:-100px; width:200px;; background:white; border:2px solid black; text-align:center; padding-top:10px;">
				<span style="font-style:italic;">Processing ...</span>
			</div>	
		</div> 
		
	</xsl:template>
	
	<xsl:template name="DesktopHistoricalPopupTmpl">
		<div style="padding:10px; width:640px;">
			<div style="height:150px">
				
			</div>
			<div style="padding-top:10px; text-align:center">
				<input type="button" value="Close" class="Desktop_Btn">
					<xsl:attribute name="onclick">Desktop.closeHistoricalPopup()</xsl:attribute>					
				</input>								
			</div>
		</div> 
		
	</xsl:template>
	
	<xsl:template name="DesktopHistoricalTableTmpl">
		<xsl:param name="sourceNode"/>
		
		<div class="Desktop_TableDiv" style="height:150px; width:620px; position:absolute;">
			<table ifdsTable="true" style="position:absolute; left:0; top:0;" tableHeight="150" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true">
				<thead>
					<tr>															
						<td>
							<xsl:attribute name="style">width:100</xsl:attribute>
							<xsl:attribute name="columnWidth">100</xsl:attribute>
							Field Label
						</td>
						<td>
							<xsl:attribute name="style">width:100</xsl:attribute>
							<xsl:attribute name="columnWidth">100</xsl:attribute>
							Previous Value
						</td>
						<td>
							<xsl:attribute name="style">width:100</xsl:attribute>
							<xsl:attribute name="columnWidth">100</xsl:attribute>
							New Value
						</td>	
						<td>
							<xsl:attribute name="style">width:100</xsl:attribute>
							<xsl:attribute name="columnWidth">100</xsl:attribute>
							Modification Date
						</td>	
						<td>
							<xsl:attribute name="style">width:100</xsl:attribute>
							<xsl:attribute name="columnWidth">100</xsl:attribute>
							Modification Time
						</td>	
						<td>
							<xsl:attribute name="style">width:100</xsl:attribute>
							<xsl:attribute name="columnWidth">100</xsl:attribute>
							User Id
						</td>																												
					</tr>
				</thead> 
				<body>
					<xsl:for-each select="$sourceNode/HistoricalInfo">
						<tr>
							<td><xsl:value-of select="fldLbl"/></td>
							<td><xsl:value-of select="prevDisp"/></td>
							<td><xsl:value-of select="newDisp"/></td>
							<td><xsl:value-of select="modDt"/></td>
							<td><xsl:value-of select="modTime"/></td>
							<td><xsl:value-of select="modUsr"/></td>
						</tr>
					</xsl:for-each>
				</body>
			</table>
		</div>
	</xsl:template>
	
</xsl:stylesheet>
