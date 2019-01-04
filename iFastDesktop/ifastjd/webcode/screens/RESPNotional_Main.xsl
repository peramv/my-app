<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/RESPNotional_DataTemplate.xsl"/>
	
	<!-- Enter Point -->
	<xsl:template match="/">
		<xsl:call-template name="master_layout">
			<xsl:with-param name="pageTitle">RESP Notional Information</xsl:with-param>			
		</xsl:call-template>
	</xsl:template>
		
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >
		<link href="{$vURL}css/RESPNotional.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/RESPNotional.js"></script>
		
		<script>
			_accountNum = "<xsl:value-of select="/websrvXML/FormInformation/AccountNum"/>";
			
			_periodOptionsMap = {};
			<xsl:for-each select="/websrvXML/dtRESPNotlInitResponse/List[contains( @listName, 'PeriodOptions' )]">
				<xsl:variable name="id" select="substring-before( @listName, 'PeriodOptions' )"/>
				_periodOptionsMap["<xsl:value-of select="$id"/>"] = {};
				<xsl:for-each select="Element">					
					_periodOptionsMap["<xsl:value-of select="$id"/>"]["<xsl:value-of select="code"/>"] = "<xsl:value-of select="value"/>";					
				</xsl:for-each>
			</xsl:for-each>
			
			_modPermission = "<xsl:value-of select="/websrvXML/dtRESPNotlInitResponse/Permission/modPerm"/>";			
		</script>		
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
		<xsl:call-template name="DesktopPopup">
			<xsl:with-param name="id">HistoryPopupDiv</xsl:with-param>
			<xsl:with-param name="caption">Historical Information</xsl:with-param>
			<xsl:with-param name="width">644</xsl:with-param>
			<xsl:with-param name="height">225</xsl:with-param>
			<xsl:with-param name="top">150</xsl:with-param>
			<xsl:with-param name="left">55</xsl:with-param>			
			<xsl:with-param name="contents"><xsl:call-template name="DesktopHistoricalPopupTmpl"/></xsl:with-param>			
		</xsl:call-template>						
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >
		<form id="form">						
			<div class="ScreenSectionDiv" style="padding-bottom:0px;">
				<div class="filterSectionDiv">
					<span style="padding-right:10px; position:relative; top:-31px">Information Level:</span>
					<select size="3" style="width:300px" id="infoLevelFld" onchange="changeHandler_infoLevelFld()">
						<xsl:call-template name="list_Tmpl">
							<xsl:with-param name="listName">InfoLevelOptions</xsl:with-param>
						</xsl:call-template>
					</select>
				</div>
				<div class="filterSectionDiv">
					<div>
						<input type="radio" name="dateFilterRadioBtn" id="period_dateFilterRadioBtn" value="period" onclick="clickHandler_dateFilterRadioBtn( this.value )"/>
						<span style="padding-left:5px;width:55px;">Period:</span>
						<select style="width:150px" id="periodFld">
							<xsl:call-template name="list_Tmpl">
								<xsl:with-param name="listName">PeriodOptions</xsl:with-param>
							</xsl:call-template>
						</select>
					</div>
					<div style="padding-top:8px; position:relative;">
						<input type="radio" name="dateFilterRadioBtn" id="asof_dateFilterRadioBtn" value="asof" onclick="clickHandler_dateFilterRadioBtn( this.value )"/>
						<span style="padding-left:5px;width:55px;">As of:</span>
						<input type="text" style="position:absolute; left:75px; top:7px; width:150px;" id="asOfDateFld" ifdsDatepicker="true" class="Desktop_Datepicker"/>
					</div>
				</div>
				<div class="filterSectionDiv" style="padding-right:0px;">
					<input type="button" value="Refresh" class="Desktop_Btn" style="position:relative; top:25px;" onclick="clickHandler_refreshBtn()"/>
				</div>
			</div>
			
			<div id="NotionalDataDiv">
				<xsl:call-template name="NotionalData_Tmpl">
					<xsl:with-param name="notlDataNode" select="/websrvXML/dtRESPNotlInitResponse/NotionalInformation"/>
					<xsl:with-param name="notlOtherInfoNode" select="/websrvXML/dtRESPNotlInitResponse/NotlOtherInfo"/>					
					<xsl:with-param name="permissionNode" select="/websrvXML/dtRESPNotlInitResponse/Permission"/>
					<xsl:with-param name="dateFilterType">period</xsl:with-param>
				</xsl:call-template>
			</div>			
			
		</form>
		<div class="ScreenButtonsDiv">
			<input type="button" value="Historical" id="historicalBtn" class="Desktop_Btn">
				<xsl:attribute name="onclick">Desktop.displayHistorical( "HistoryPopupDiv", "RESPNotional_History", getHistoricalSearchParam() )</xsl:attribute>				
			</input>
			<input type="button" value="OK" class="Desktop_Btn" onclick="clickHandler_OKBtn()">				
			</input>
			<input type="button" style="display:none" name="btnOK" id="btnOK"/>
			<input type="button" value="Cancel" id="btnCancel" name="btnCancel" class="Desktop_Btn">				
			</input>									
		</div>		
	</xsl:template>
	
	<xsl:template name="list_Tmpl">
		<xsl:param name="listName"/>
			
		<xsl:for-each select=".//List[@listName = $listName]/Element">
			<option>
				<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
				
				<xsl:value-of select="value"/>
			</option>
		</xsl:for-each>
	</xsl:template>
	
	
	
	
	
</xsl:stylesheet>