<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/General_DesktopMasterLayout.xsl"/>
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/Desktop.xsl"/>	
	<xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/FundSetup_ClassMaint_Common.xsl"/>
	
    <xsl:variable name="SCREEN_NAME">LtOvrd</xsl:variable>
    
    <!-- some constant variables -->
    <xsl:variable name="RuleTypeListName">RuleTypeList</xsl:variable>
    <xsl:variable name="TaxJurisListName">TaxJurisList</xsl:variable>
    <xsl:variable name="AcctTypeListName">AcctTypeList</xsl:variable>
    <xsl:variable name="AcctDesignationListName">AcctDesignationList</xsl:variable>
    <xsl:variable name="TaxTypeListName">TaxTypeList</xsl:variable>
    <xsl:variable name="EWIListName">EWIList</xsl:variable>
    
	<!-- using the same list as tax jurisdiction -->
	<xsl:variable name="ProvResListName">TaxJurisList</xsl:variable>
	
	<xsl:variable name="fundCode">
		<xsl:value-of select="/websrvXML/FormInformation/fundCode" />
	</xsl:variable>
	<xsl:variable name="classCode">
		<xsl:value-of select="/websrvXML/FormInformation/classCode" />
	</xsl:variable>
    
    <!-- list variables -->
    <xsl:variable name="RuleTypeList">
        <xsl:call-template name="selectTmpl">
        	<xsl:with-param name="selectList" select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$RuleTypeListName]" />
            <xsl:with-param name="selectID"><xsl:value-of select="$RuleTypeListName" /></xsl:with-param>
            <xsl:with-param name="selected"><xsl:value-of select="/websrvXML/dtClassLtOvrdInitResponse/ListSelection[@id=$RuleTypeListName]" /></xsl:with-param>
        </xsl:call-template>
    </xsl:variable>
	<xsl:variable name="EWIList">
		<xsl:call-template name="selectTmpl">
			<xsl:with-param name="selectList" select="/websrvXML/dtClassLtOvrdInitResponse/List[@listName=$EWIListName]" />
			<xsl:with-param name="selectID"><xsl:value-of select="$EWIListName" /></xsl:with-param>
			<xsl:with-param name="selected"><xsl:value-of select="/websrvXML/dtClassLtOvrdInitResponse/ListSelection[@id=$EWIListName]" /></xsl:with-param>
		</xsl:call-template>
	</xsl:variable>
		
	<!-- Enter Point -->
	<xsl:template match="/">
	    <xsl:call-template name="master_layout">
	    	<xsl:with-param name="pageTitle">Limitation Override - Fund: <xsl:value-of select="$fundCode" />, Class: <xsl:value-of select="$classCode" /></xsl:with-param>			
	    </xsl:call-template>
	</xsl:template>
	
	<!-- ========================== HEADER CALLBACK TEMPLATE =============================-->
	<xsl:template name="header_callback" >		
		<link href="{$vURL}css/FundSetup_ClassMaint_Common.css" rel="stylesheet" type="text/css" />		
		<link href="{$vURL}css/FundSetup_ClassMaint_{$SCREEN_NAME}.css" rel="stylesheet" type="text/css" />
		<script language="javascript" src="{$vURL}javascript/FundSetup_ClassMaint_Common.js"></script>
		<script language="javascript" src="{$vURL}javascript/FundSetup_ClassMaint_{$SCREEN_NAME}.js"></script>
		<script language="javascript" type="text/javascript">
			<xsl:call-template name="ClassMaint_CommonJS_Tmpl"/>
			
			_fundCode = "<xsl:value-of select="$fundCode" />";
			_classCode = "<xsl:value-of select="$classCode" />";
	    	
	    	<xsl:for-each select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$TaxJurisListName]/Element">
	    		_TaxJurisList["<xsl:value-of select="code" />"] = "<xsl:value-of select="value" />";
	    	</xsl:for-each>
	    	
	    	<xsl:for-each select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$AcctTypeListName]/Element">
	    		_AcctTypeList["<xsl:value-of select="code" />"] = "<xsl:value-of select="value" />";
	    	</xsl:for-each>
	    	
	    	<xsl:for-each select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$TaxTypeListName]/Element">
	    		_TaxTypeList["<xsl:value-of select="code" />"] = "<xsl:value-of select="value" />";
	    	</xsl:for-each>
	    	
	    	<xsl:for-each select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$AcctDesignationListName]/Element">
	    		_AcctDesignationList["<xsl:value-of select="code" />"] = "<xsl:value-of select="value" />";
	    	</xsl:for-each>
			
			<xsl:for-each select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$ProvResListName]/Element">
				_ProvResList["<xsl:value-of select="code" />"] = "<xsl:value-of select="value" />";
			</xsl:for-each>
					
			<xsl:for-each select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$RuleTypeListName]/Element">
				_RuleTypeMap["<xsl:value-of select="code" />"] = "<xsl:value-of select="code/@override" />";
			</xsl:for-each>			
			
			<xsl:for-each select="/websrvXML/dtClassLtOvrdInqResponse/FundLtOvrds/FundLtOvrd">
				var newData = new fundLimitOverrideData("<xsl:value-of select="ruleType" />","<xsl:value-of select="ruleTypeDesc" />","<xsl:value-of select="overrideDec" />","<xsl:value-of select="overrideLog" />","<xsl:value-of select="taxJurisDecl" />","<xsl:value-of select="provResDecl" />","<xsl:value-of select="accountTypeDecl" />","<xsl:value-of select="taxTypeDecl" />","<xsl:value-of select="acctDesigDecl" />","<xsl:value-of select="onlineEWI" />","<xsl:value-of select="cycleEWI" />","<xsl:value-of select="esgEWI" />","<xsl:value-of select="fundLtOvrdRID" />","");
				detailOvrdData.push(newData);
			</xsl:for-each>
	    </script>
	</xsl:template>
	
	
	<!-- ========================== PAGE PRELOAD CALLBACK TEMPLATE =============================-->
	<xsl:template name="page_preload_callback">
	    <xsl:call-template name="DesktopPopup">
	        <xsl:with-param name="id">ruleTypePopupDiv</xsl:with-param>
	        <xsl:with-param name="caption"></xsl:with-param>
	        <xsl:with-param name="width">580</xsl:with-param>
	        <xsl:with-param name="height">120</xsl:with-param>
	        <xsl:with-param name="top">200</xsl:with-param>
	        <xsl:with-param name="left">170</xsl:with-param>			
	        <xsl:with-param name="contents"><xsl:call-template name="ruleTypeAddPopupContent" /></xsl:with-param>			
	    </xsl:call-template>
	    
	    <xsl:call-template name="DesktopPopup">
	        <xsl:with-param name="id">appToPopupDiv</xsl:with-param>
	        <xsl:with-param name="caption"></xsl:with-param>
	        <xsl:with-param name="width">530</xsl:with-param>
	        <xsl:with-param name="height">400</xsl:with-param>
	        <xsl:with-param name="top">150</xsl:with-param>
	        <xsl:with-param name="left">180</xsl:with-param>			
	    	<xsl:with-param name="contents"><xsl:call-template name="appToPopupContentTmpl" /></xsl:with-param>			
	    </xsl:call-template>
	</xsl:template>
	
	
	<!-- ========================== FORM CALLBACK TEMPLATE =============================-->
	<xsl:template name="form_callback" >
		
		<div class="ScreenContentsDiv">

			<div class="EntryScreenSectionDiv">
				<div class="SimpleSectionContentsDiv">
					<div class="FieldRowDiv">
						<span class="fldLabelSpan_lrg">Filter by Rule Type:&#xa0;</span>
						<!-- rule type selection dropdownlist -->
						<span class="fldValueSpan_xlrg">
							<xsl:copy-of select="$RuleTypeList" />
						</span>
					</div>
				</div>
			</div>
			
			<div class="EntryScreenSectionDiv">
			    <div id="ruleDiv">
		    	    <!-- rule type and override value -->
		    	    <div id="ClassList_TableDiv" class="Desktop_TableDiv" style="overflow-y:scroll;">
		    	        <table id="LtOvrdTable" ifdsTable="true" baseClassName="Desktop_Table" cellpadding="0" cellspacing="0" scrollable="true" resizable="true" rowSelectable="true" tableHeight="290">
		        	        <thead>
		        	            <tr>					
		        	                <td style="width:450;" columnWidth="450">
		        	                    Rule Type
		        	                </td>
		        	                <td style="width:433;" columnWidth="429">
		        	                    Override Value
		        	                </td>													
		        	            </tr>
		        	        </thead>					
		        	        <tbody>
		        	        </tbody>
		    	        </table>
		    	    </div>
		    	    
		    	    <!-- add and delete button -->
			    	<div class="SectionActionButtonsDiv">
			    		<input type="button" value="Add" id="btnRuleAdd" class="Desktop_Btn">
			    			<xsl:attribute name="onclick">clickHandler_ruleBtns( "add" )</xsl:attribute>
			    		</input>
			    		<input type="button" value="Delete" id="btnRuleDel" class="Desktop_Btn">
			    			<xsl:attribute name="onclick">clickHandler_ruleBtns( "del" )</xsl:attribute>
			    		</input>
			    	</div>
			    </div>
			</div>
		    
			<div class="EntryScreenSectionDiv" id="appToDiv">
		    	<div class="FieldSetDiv">
		    		<div class="FieldSetLabelDiv Desktop_Background" style="width:93px">
		    			Applicable To
		    		</div>
		    		
		    		<div class="FieldSetContentsDiv">
		    			<div class="FieldRowDiv">
		    				<span class="fldLabelSpan_med applicableTitle_med">Application Category</span>
		    				<span class="fldValueSpan_xlrg applicableTitle_xlrg">Value</span>		    				
		    			</div>
						<div class="FieldRowDiv" style="height:60px;">
		    				<table cellpadding="0" cellspacing="0">
		    					<tr>
		    						<td class="fldLabelSpan_med" style="width:160px;" valign="top">Tax Jurisdiction:</td>
		    						<td id="taxJurisDecl" class="fldValueSpan_xlrg applicableData" style="width:577px;padding-top:12px;padding-right:3px;"></td>
		    						<td class="fldValueSpan_sml" style="padding-top:8px;" valign="top">
		    							<input type="button" name="fldEditBtn" value="Edit" class="Desktop_Btn limitEditBtn" disabled="true">
		    								<xsl:attribute name="onclick">editField( "<xsl:value-of select="$TaxJurisListName"/>" );</xsl:attribute>
		    							</input>
		    						</td>
		    					</tr>
		    				</table>
		    			</div>
						<div class="FieldRowDiv">
		    				<span class="fldLabelSpan_med">Province of Residence:</span>
		    				<span id="provResDecl" class="fldValueSpan_xlrg applicableData"></span>
		    				<span class="fldValueSpan_sml">
		    					<input type="button" name="fldEditBtn" value="Edit" class="Desktop_Btn limitEditBtn" disabled="true">
		    						<xsl:attribute name="onclick">editField( "ProvResList" );</xsl:attribute>
		    					</input>
		    				</span>
		    			</div>
						<div class="FieldRowDiv">
		    				<span class="fldLabelSpan_med">Account Type:</span>
		    				<span id="accountTypeDecl" class="fldValueSpan_xlrg applicableData"></span>
		    				<span class="fldValueSpan_sml">
		    					<input type="button" name="fldEditBtn" value="Edit" class="Desktop_Btn limitEditBtn" disabled="true">
		    						<xsl:attribute name="onclick">editField( "<xsl:value-of select="$AcctTypeListName"/>" );</xsl:attribute>
		    					</input>
		    				</span>
		    			</div>
		    			
		    			<div class="FieldRowDiv">
		    				<span class="fldLabelSpan_med">Tax Type:</span>
		    				<span id="taxTypeDecl" class="fldValueSpan_xlrg applicableData"></span>
		    				<span class="fldValueSpan_sml">
		    					<input type="button" name="fldEditBtn" value="Edit" class="Desktop_Btn limitEditBtn" disabled="true">
		    						<xsl:attribute name="onclick">editField( "<xsl:value-of select="$TaxTypeListName"/>" );</xsl:attribute>
		    					</input>		    					
		    				</span>
		    			</div>
		    			
		    			<div class="FieldRowDiv">
		    				<span class="fldLabelSpan_med">Account Designation:</span>
		    				<span id="acctDesigDecl" class="fldValueSpan_xlrg applicableData"></span>
		    				<span class="fldValueSpan_sml">
		    					<input type="button" name="fldEditBtn" value="Edit" class="Desktop_Btn limitEditBtn" disabled="true">
		    						<xsl:attribute name="onclick">editField( "<xsl:value-of select="$AcctDesignationListName"/>" );</xsl:attribute>
		    					</input>
		    				</span>
		    			</div>
		    			
		    		</div>
		    	</div>
			</div>
			
			<div class="EntryScreenSectionDiv" id="serverityDiv">
				<div class="FieldSetDiv">
					<div class="FieldSetLabelDiv Desktop_Background" style="width:58px">
						Severity
					</div>
					
					<div class="FieldSetContentsDiv">
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Online Entry</span>
							<span class="fldValueSpan_med" id="onlineEWI">
								<xsl:copy-of select="$EWIList" />
							</span>
						</div>						
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">Cycle Processing</span>
							<span class="fldValueSpan_med" id="cycleEWI">
								<xsl:copy-of select="$EWIList" />
							</span>
						</div>
						<div class="FieldRowDiv">
							<span class="fldLabelSpan_med">ESG Network</span>
							<span class="fldValueSpan_med" id="esgEWI">
								<xsl:copy-of select="$EWIList" />
							</span>
						</div>
					</div>
				</div>
			</div>
		    
		    <!-- bottom button -->
			<div class="ScreenButtonsDiv">
				<input type="button" id="resetBtn" class="Desktop_Btn" value="Reset" onclick="clickHandler_resBtn();" disabled="true"/>
				<input type="button" id="submitBtn" class="Desktop_Btn" value="Submit" onclick="clickHandler_okBtn();" disabled="true"/>
				<input type="button" class="Desktop_Btn" value="Cancel" onclick="clickHandler_canBtn();" />				
				
			</div>
		</div>
	</xsl:template>
    
    <!-- Select Template -->
    <xsl:template name="selectTmpl">
        <xsl:param name="selectList" />
        <xsl:param name="selectID" />
        <xsl:param name="selected" />
        
        <select>
            <xsl:attribute name="name">
                <xsl:value-of select="$selectID" />
            </xsl:attribute>
        	<xsl:if test="string-length($selectID) &gt; 0">
	            <xsl:attribute name="onchange">
	                <xsl:text>ddlChangeHandler_</xsl:text>
	                <xsl:value-of select="$selectID" />
	                <xsl:text>(this);</xsl:text>
	            </xsl:attribute>
        	</xsl:if>
        	<xsl:attribute name="class">
        		<xsl:text>fld_xlrg</xsl:text>
        	</xsl:attribute>
            <xsl:for-each select="$selectList/Element">
                <option>
                    <xsl:attribute name="value">
                        <xsl:value-of select="code" />
                    </xsl:attribute>
                    <xsl:if test="code = $selected">
                        <xsl:attribute name="selected">selected</xsl:attribute>
                    </xsl:if>
                	<!-- it doesnt like the text attribute -->
                	<!--<xsl:attribute name="text">
                		<xsl:value-of select="value" />
                	</xsl:attribute>-->
                	<xsl:value-of select="value" />
                </option>
            </xsl:for-each>
        </select>
    </xsl:template>
    
    <!-- Add new rule type popup -->
    <xsl:template name="ruleTypeAddPopupContent">
    	<div class="EntryScreenSectionDiv" style="padding-bottom:10px;">    		
    		<div class="FieldRowDiv">
    			<span class="fldLabelSpan_med">Rule Type:&#xa0;</span>
    			<span class="fldValueSpan_xlrg" id="ruleTypeAddSelect">
    				<select id="Popup_ruleTypeSelect" onchange="changeHandler_PopupRuleSelect(this)">
    					
    					<xsl:for-each select="/websrvXML/dtClassLtOvrdInitResponse/List[@id=$RuleTypeListName]/Element">
    						<xsl:element name="option">
    							<xsl:attribute name="value"><xsl:value-of select="code"/></xsl:attribute>								
								<xsl:value-of select="value"/>
    						</xsl:element>    					
						</xsl:for-each>	
    				</select>
    			</span>
    		</div>
    		<div class="FieldRowDiv">
    			<span class="fldLabelSpan_med">Override Value:&#xa0;</span>
    			<span class="fldValueSpan_med">
    				<input type="text" id="overrideDecFld" style="width:200px; display:block">
    				</input>
					<input type="text" id="overrideLogFld" style="width:200px; display:none" value="yes" disabled="true">						
    				</input>
    			</span>
    		</div>
    		<div class="FieldRowDiv" style="height:50px;">
    			<div class="PopupButtonsDiv">
    				<input type="button" class="Desktop_Btn" value="Save" onclick="clickHandler_popupSaveAddBtn()" />
    				<input type="button" class="Desktop_Btn" value="Cancel" onclick="clickHandler_popupCancelAddBtn()" />
    			</div>
    		</div>
    		
    	</div>
    </xsl:template>
    
	<!-- ========================== EDIT APP. CATEGORY POPUP TEMPLATE =============================-->
    <xsl:template name="appToPopupContentTmpl">
    	<xsl:param name="selectID" />
    	<xsl:param name="inDivData" />
    	<xsl:param name="exDivData" />
    	
    	<div class="EntryScreenSectionDiv" style="padding:15px;">    		    		
    		<div class="rowContentDiv" style="text-align:right; padding-right:8px;">
    			<span style="padding-right:5px;">Include/Exclude:</span>
    			<select id="ieSelect" onchange="ddlChangeHandler_ieSelect();" style="width:90px;">
    				<option value="i">Include</option>
    				<option value="e">Exclude</option>
    			</select>
    		</div>
    		<div class="rowContentDiv">
    			<div class="leftDiv titleRow">
    				<span>All Values</span>
    			</div>
    			<div class="midDiv titleRow">
    				<xsl:text>&#xa0;</xsl:text>
    			</div>
    			<div class="rightDiv titleRow">
    				<span id="listTitle"></span><span>&#xa0;List</span>
    			</div>
    			
    			<div class="leftDiv listDiv" id="allList">

    			</div>
    			<div class="midDiv btnDiv">
    				<br /><br />
    				<input type="button" id="eMoveBtn" class="popupBtn" value="&#8594;" onclick="moveItem();" disabled="true" /><br />
    				<input type="button" id="iMoveBtn" class="popupBtn" value="&#8592;" onclick="moveItem();" disabled="true" />
    			</div>
    			<div class="rightDiv listDiv" id="selList">

    			</div>
    		</div>
    		<div class="rowContentDiv">
    			<div class="PopupButtonsDiv">
    				<input type="button" class="Desktop_Btn" value="Save" onclick="clickHandler_popupSaveBtn()" />
    				<input type="button" class="Desktop_Btn" value="Cancel" onclick="clickHandler_popupCancelBtn()" />
    			</div>
    		</div>
    		
    		<input type="hidden" id="whichPopup" />    		
    	</div>
    </xsl:template>

</xsl:stylesheet>