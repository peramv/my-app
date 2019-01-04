<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<!-- ========================== COMMON JS TEMPLATE =============================-->
	<!-- generates javascript code used in each screen -->				
	<xsl:template name="ClassMaint_CommonJS_Tmpl">
		<xsl:param name="isAddMode">false</xsl:param>
		
		var _tidx = "<xsl:value-of select="/websrvXML/FormInformation/tidx"/>";
				
		var _editScreenNameArray = [];
		<xsl:for-each select="/websrvXML/ScreensConfig/DetailsScreenSequence/screenName">
			_editScreenNameArray[_editScreenNameArray.length] = "<xsl:value-of select="."/>";
			<xsl:if test=". = $SCREEN_NAME">
				var _currentEditScreenIndex = <xsl:value-of select="position() - 1"/>;			
			</xsl:if>
		</xsl:for-each>
				
		var _permissionsMap = {};		
		_permissionsMap["inq"] = "<xsl:value-of select="/websrvXML/CACHE_DATA/Permissions/inq"/>";
		_permissionsMap["add"] = "<xsl:value-of select="/websrvXML/CACHE_DATA/Permissions/add"/>";
		
		_isAddMode = <xsl:value-of select="$isAddMode"/>;  			
	</xsl:template>

		
	<!-- ========================== BREAD CRUMB TEMPLATE =============================-->
	<!-- generates bread crumb links at the top of the screen, highlighting the current one -->		
	<xsl:template name="BreadCrumb_Tmpl">
		<xsl:param name="activeScreenName"/>
		<xsl:param name="isAddMode"/>
		
		<div class="BreadCrumbSectionDiv" name="BreadCrumbSectionDiv">
			<xsl:for-each select="/websrvXML/ScreensConfig/DetailsScreenSequence/screenName">
				<xsl:variable name="screenName" select="."/>
				<span name="BreadCrumbItemSpan">
					<xsl:attribute name="class">
						BreadCrumbItemSpan
						<xsl:choose>							
							<xsl:when test="$activeScreenName = $screenName">ActiveBreadCrumbItem</xsl:when>
							<xsl:when test="$isAddMode = 'true' and preceding-sibling::screenName[text() = $activeScreenName]">DisabledBreadCrumbItem</xsl:when>
						</xsl:choose>				
					</xsl:attribute>
					<xsl:attribute name="screenName">
						<xsl:value-of select="$screenName"/>
					</xsl:attribute>
					<xsl:attribute name="screenIndex">
						<xsl:value-of select="position()"/>
					</xsl:attribute>
					<xsl:attribute name="onclick">
						<xsl:choose>
							<xsl:when test="$isAddMode != 'true'">clickHandler_breadCrumbItem( this );</xsl:when>
							<xsl:when test="following-sibling::screenName[text() = $activeScreenName]">clickHandler_breadCrumbItem( this );</xsl:when>
						</xsl:choose>						
					</xsl:attribute>
					
					<xsl:value-of select="/websrvXML/ScreensConfig/ScreenDefList/ScreenDef[screenName = $screenName]/screenLabel"/>
				</span>
				<xsl:if test="position() != last()">
					<span class="BreadCrumbItemSeparatorSpan">
						&gt;
					</span>
				</xsl:if>
			</xsl:for-each>
		</div>
	</xsl:template>

	
	<!-- ========================== SCREEN BUTTONS TEMPLATE =============================-->
	<!-- generates buttons located at the bottom of the screen, based on mode specified (add or not) -->
	<xsl:template name="ScreenButtons_Tmpl">
		<xsl:param name="screenName"/>
		<xsl:param name="isAddMode"/>
	
		<div class="ScreenButtonsDiv">
			<xsl:choose>
				<xsl:when test="$isAddMode = 'false'">
					<input id="resetBtn" type="button" value="Reset" class='Desktop_Btn' onclick="clickHandler_resetScreenBtn()" disabled="true"/>
					<input id="saveChangesBtn" type="button" value="Save Changes" class='Desktop_Btn' onclick="clickHandler_saveChangesBtn()" disabled="true"/>			
					<input id="returnToSummaryBtn" type="button" value="Return to Summary" class='Desktop_Btn' onclick="clickHandler_summaryBtn();"/>
				</xsl:when>
				<xsl:otherwise>
					<input id="prevScreenBtn" type="button" value="Previous" class='Desktop_Btn' onclick="clickHandler_prevEditScreenBtn()"/>
					<input id="resetBtn" type="button" value="Reset" class='Desktop_Btn' onclick="clickHandler_resetScreenBtn()"/>
					<input id="saveChangesBtn" type="button" value="Save Changes" class='Desktop_Btn' onclick="clickHandler_saveChangesBtn()"/>					
					<input id="cancelAddBtn" type="button" value="Cancel" class='Desktop_Btn' onclick="clickHandler_cancelAddBtn()"/>
					<input id="nextScreenBtn" type="button" value="Next" class='Desktop_Btn' onclick="clickHandler_nextEditScreenBtn()"/>
					<input id="viewSummaryBtn" type="button" value="View Summary" class='Desktop_Btn' onclick="clickHandler_addSummaryBtn();" style="position:absolute; right:0px;"/>
				</xsl:otherwise>
			</xsl:choose>
		</div>
	</xsl:template>			
	
	<!-- ========================== LIST TEMPLATE =============================-->
	<!-- generates the options for select box from the view list specified -->
	<xsl:template name="List_tmpl">
		<xsl:param name="listName"/>
		<xsl:param name="id"/>
	
		<xsl:if test="string-length( $listName ) &gt; 0">
			<xsl:for-each select="/websrvXML/CACHE_DATA/Lists/List[@listName = $listName]/Element">
				<option>
					<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
					
					<xsl:value-of select="value"/>				
				</option>
			</xsl:for-each>
		</xsl:if>
		<xsl:if test="string-length( $id ) &gt; 0">
			<xsl:for-each select="/websrvXML/CACHE_DATA/Lists/List[@id = $id]/Element">
				<option>
					<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>
					
					<xsl:value-of select="value"/>				
				</option>
			</xsl:for-each>
		</xsl:if>
	</xsl:template>
	
	<!-- ========================== TEXT TEMPLATE =============================-->
	<!-- prints out the string provided, or a nbsp if string is empty -->
	<xsl:template name="Text_Tmpl">
		<xsl:param name="text"/>
		
		<xsl:if test="string-length( $text ) &gt; 0"><xsl:value-of select="$text"/></xsl:if>
		<xsl:if test="string-length( $text ) = 0"><xsl:text>&#xa0;</xsl:text></xsl:if>		
	</xsl:template>
	
	<!-- ========================== PAGE TITLE TEMPLATE =============================-->
	<xsl:template name="PageTitle_Tmpl">
		<xsl:param name="addMode"/>
		<xsl:param name="screenName"/>
		
		<xsl:value-of select="/websrvXML/ScreensConfig/ScreenDefList/ScreenDef[screenName = $screenName]/screenLabel"/> 		
		<xsl:choose>
			<xsl:when test="$addMode= 'false'">
				- Fund: <xsl:value-of select="/websrvXML/CACHE_DATA/ClassData/fundCode"/>, 
				Class:<xsl:value-of select="/websrvXML/CACHE_DATA/ClassData/classCode"/>
			</xsl:when>
			<xsl:otherwise>
				- Fund: <xsl:value-of select="/websrvXML/CACHE_DATA/UpdatedClassData/fundCode"/>, 
				Class: 
				<xsl:choose>
					<xsl:when test="string-length(/websrvXML/CACHE_DATA/UpdatedClassData/classCode) &gt; 0">*<xsl:value-of select="/websrvXML/CACHE_DATA/UpdatedClassData/classCode"/>*</xsl:when>
					<xsl:otherwise>*NEW*</xsl:otherwise>	
				</xsl:choose> 
			</xsl:otherwise>
		</xsl:choose> 
	</xsl:template>
	
	<!-- ========================== COMMON EDIT SCREEN FIELDS TEMPLATE =============================-->
	<xsl:template name="CommonEditScreenFields_Tmpl">
		<xsl:param name="isAddMode"/>
		
		<input id="xx" type="hidden" xpath="fundCode" mandatory="true"/>
		
		<input type="hidden" xpath="classCode" id="hiddenClassCodeFld"/>
					
		<input type="hidden" override="true" xpath="processingMode" value="update" mandatory="true"/>
			
		<xsl:choose>
			<xsl:when test="$isAddMode = 'false'">
				<input type="hidden" override="true" xpath="runMode" value="M" mandatory="true"/>
				<input type="hidden" xpath="fundDetlVer"/>
				<input type="hidden" xpath="fundInfoVer"/>
				<input type="hidden" xpath="feeDetlVer"/>
				<input type="hidden" xpath="feeDetlRID"/>
			</xsl:when>
			<xsl:otherwise>
				<input type="hidden" override="true" xpath="runMode" value="A" mandatory="true"/>
			</xsl:otherwise>
		</xsl:choose>		
			
	</xsl:template>
	
	<!-- ========================== EDIT SCREEN FORM TEMPLATE =============================-->
	<xsl:template name="ScreenForm_Tmpl">
		<form name="screenForm" id="screenForm" action="" method="POST">
		
			<input type="hidden" name="cz" id="czFld"/>
			<input type="hidden" name="jobname" id="jobnameFld"/>
			<input type="hidden" name="companyCode" id="companyCodeFld"/>
			<input type="hidden" name="ruserId" id="ruserIdFld"/>
			<input type="hidden" name="sessionId" id="sessionIdFld"/>
			<input type="hidden" name="envName" id="envNameFld"/>
			<input type="hidden" name="dateFormat" id="dateFormatFld"/>
			<input type="hidden" name="tidx" id="tidxFld"/>
			<input type="hidden" name="bgcolor" id="bgcolorFld"/>
			<input type="hidden" name="screenToLoad" id="screenToLoadFld"/>
			
			<input type="hidden" name="fundCode" id="fundCodeFld"/>
			
			<input type="hidden" name="data"/>
		</form>		
		
	</xsl:template>
	
	<!-- ========================== EDIT SCREEN FORM TEMPLATE =============================-->
	<xsl:template name="DataXML_Tmpl">
		<xsl:param name="id"/>
		<xsl:param name="xml"/>
		
		<xsl:element name="xml">
			<xsl:attribute name="id"><xsl:value-of select="$id"/></xsl:attribute>
			
			<xsl:copy-of select="$xml"/>
		</xsl:element>
	</xsl:template>
</xsl:stylesheet>