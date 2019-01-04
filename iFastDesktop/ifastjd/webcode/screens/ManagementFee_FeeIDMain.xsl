<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes"/>
  
  <xsl:include 
    href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/DST_WebBehavioursTemplate.xsl"/>
  <xsl:include 
    href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>  
  <xsl:include
    href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/screens/ManagementFee_FeeIDTemplates.xsl"/>
  
  <xsl:variable name="vClient" select="/websrvXML/requestInfo/client"/>
  <xsl:variable name="vServletPath" select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vDataDir" select="/websrvXML/transformNode/datadir"/>
  <xsl:variable name="vURL" select="concat( $vDataDir, $vClient, '/' )"/>
  <xsl:variable name="vTX" select="/websrvXML/FormInformation/tx"/>
  <xsl:variable name="vCZ" select="/websrvXML/FormInformation/cz"/>
  <xsl:variable name="vTIDX" select="/websrvXML/FormInformation/tidx"/>
  
  
  <xsl:template match="/">

    <Screen>

      <!-- 
        This xsl loads up the screen that is loaded inside the iFrame when
        a user presses the Add Control button. 
      -->

      <html>
        <xsl:call-template name="tmplBehaviours"/>

        <title>Fee ID: <xsl:value-of select="//FormInformation/feeModelCode"/></title>

        <head>
          
          <!-- web library js code -->
          <script src="{$vURL}WebLibrary/JSLib/Cookie.js"/>
          <script src="{$vURL}WebLibrary/JSLib/Err.js"/>
          <script src="{$vURL}WebLibrary/JSLib/JSXML.js"/>
          <script src="{$vURL}WebLibrary/JSLib/UTL.js"/>
          <script src="{$vURL}WebLibrary/JSLib/WebTools.js"/>
          <script src="{$vURL}WebLibrary/JSLib/EvtHandler.js"/>
          <script src="{$vURL}WebLibrary/JSLib/HTTP.js"/>
          <script src="{$vURL}WebLibrary/JSLib/XML.js"/>
          <script src="{$vURL}WebLibrary/JSLib/KeyMap.js"/>
          
          <script src="{$vURL}WebLibrary/WebComps/SuggestFieldComponent.js"/>
          
          <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"><!-- comment --></link>
          <script src="{$vURL}javascript/ManagementFee_FeeIDMain.js">// comment. pls keep</script>
          <script src="{$vURL}javascript/Cookie.js">// comment. pls keep</script>
          
          
          <style>
                        .Dropdown
                        {
                        width:450;
                        height:228;				
                        border:0px solid black;
                        background:url('<xsl:value-of select="$vURL"/>images/SuggestDropdown_big.gif');
                        padding:5px;				
                        }
                        
                        .DropdownContent
                        {
                        font-size:10px;
                        cursor:default;
                        }
                        
                        .DropdownHighlight
                        {
                        cursor:default;
                        font-size:10px;
                        background: #EDEDED;
                        }
                    </style>
         
          <xsl:call-template name="DST_WebBehavioursTmpl"/>
        </head>

        <body bgcolor="white" style=" border: 0px solid black" onload="onLoad()">

          <xsl:call-template name="tmplForm"/>
        </body>

      </html>
    </Screen>

  </xsl:template>

  <!-- ======================================================================= -->
  <xsl:template name="tmplForm">
    <br/>
    
    <xsl:if test="/websrvXML/responseContents/error">
      <script>alert('<xsl:value-of select="/websrvXML/responseContents/error"/>');</script>
    </xsl:if>
    
    <input type="hidden" id="holdingEntityID">
      <xsl:attribute name="value">
        <xsl:value-of select="/websrvXML/FormInformation/holdingEntityID"/>
      </xsl:attribute>
    </input>
    
    <div id="feeIDMasterDiv" style="width:365">
        <fieldset style="position:relative; left:-5; left:10; top:0; width:760;  display:block;">
          <legend>
            <font color="black">
              
              <b> Fee ID Information </b>
            </font>
          </legend>
          
          <xsl:if test="/websrvXML/dtFeeIDInitResponse/allowUpdates='yes'">
            <span style="cursor:pointer; position:absolute; left:585; top:-1; width:70; height:15; overflow:hidden;"
              align="center">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <xsl:with-param name="id">modifyDescBtn</xsl:with-param>
                <xsl:with-param name="onclick">modifyFeeIDInfo()</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">70</xsl:with-param>
                <xsl:with-param name="text">Modify</xsl:with-param>
                <xsl:with-param name="color">orange</xsl:with-param>
              </xsl:call-template>
            </span>
            
            <span style="cursor:pointer; position:absolute; left:658; top:-1; width:70; height:15; overflow:hidden;"
              align="center">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <!-- disabled as part of day 2 updates -->
                <xsl:with-param name="id">deleteDescBtn</xsl:with-param>                
                <xsl:with-param name="xxxonclick">if(confirm("Are you sure you want to delete this Fee ID?")) deleteFeeID()</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">70</xsl:with-param>
                <xsl:with-param name="text">Delete</xsl:with-param>
                <xsl:with-param name="color">gray</xsl:with-param>
              </xsl:call-template>
            </span>       
      </xsl:if>

          
          
          <!-- Top Fee ID Div -->
          <div style="position:relative; top:3; left:15;">

            <table style="width:90%; position:relative; top:-3;" id="descriptionTable">
              <tr>
                <td style="width:110;" align="right"> Fee ID: </td>
                <td id="feeIDCode" style="verticalAlign:top;">
                      <xsl:value-of select="//FeeID/feeIDCode"/>
                </td>
              </tr>
              <tr>
                <td style="width:110;" align="right"> Description: </td>
                <td>
                  <span id="descriptionField" style="height:100%; verticalAlign:top;">
                    <xsl:value-of select="translate( //FeeID/feeIDDesc, '&#xa;', ' ' )"/>
                  </span>
                </td>
              </tr>       
            </table> 
                    
            <table style="width:95%; display:none; position:relative; top:5; z-index:20;" id="modifyDescriptionTable">
              <tr>
                <td style="width:110;" align="right"> Fee ID: </td>
                <td style="verticalAlign:top;">
                    <input id="feeIDCodeInput">
                      <xsl:attribute name="value">
                        <xsl:value-of select="//FeeID/feeIDCode"/>
                      </xsl:attribute>
                    </input>
                </td>
              </tr>
              <tr>
                <td style="width:110;" align="right">
                  <span style="height:100%; verticalAlign:top;">Description:</span>
                </td>
                <td>
                  <input id="modifiedDescInput" type="text" style="width:100%">
                    <xsl:attribute name="value"><xsl:value-of select="translate( //FeeID/feeIDDesc, '&#xa;', ' ' )"/></xsl:attribute>
                  </input>                  
                </td>
              </tr>        
              <tr style="height:30">
                <td align="right" colspan="2">
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">saveDescBtn</xsl:with-param>
                    <xsl:with-param name="onclick">saveDescription();</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">85</xsl:with-param>
                    <xsl:with-param name="text">Save</xsl:with-param>
                    <xsl:with-param name="color">green</xsl:with-param>
                  </xsl:call-template>
    
                  <xsl:call-template name="ColorButtonTmpl">
                    <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                    <xsl:with-param name="id">closeDescBtn</xsl:with-param>
                    <xsl:with-param name="onclick">closeDescription();</xsl:with-param>
                    <xsl:with-param name="size">small</xsl:with-param>
                    <xsl:with-param name="width">85</xsl:with-param>
                    <xsl:with-param name="text">Close</xsl:with-param>
                    <xsl:with-param name="color">red</xsl:with-param>
                  </xsl:call-template>
                </td>
              </tr>
            </table>
          </div>
        </fieldset>


      <div id="grayDiv"
        style="width:610; height:300; display:none; position:absolute; z-index:21; background:white; filter:alpha(opacity=50);"> </div>
      

      
      <!-- Funds Div -->
      <fieldset id="fundsFieldset">
		  <xsl:attribute name="style">
			  position:relative; left:10; top:0; width:760;
			  <xsl:if test="not(/websrvXML/dtFeeIDInitResponse/FeeID)">
				  display:none;
			  </xsl:if>
		  </xsl:attribute>

        <legend>
          <font style="cursor:pointer" onclick="toggleDiv(&quot;fundsDiv&quot;); togglePlusMinus(this.firstChild); updateGrayDiv();" color="black">
            <img src="{$vURL}images/minus.png" style="position:relative; top:2; left: 1; "/>
            <b> Funds </b>
          </font>
        </legend>
        <table>
          <tr>
            <td/>
          </tr>
        </table>
     
        <div id="fundsDiv" style="display:block;">
          
          <!-- Funds Action Dropdown -->
          <div align="center" style="width:720; left:10; top:-2; position:relative;">
            <span style="position:relative; width:60;">Action:</span>
            <span style=" position:relative; top:-2;">
              <select id="actionSelect" onchange="handleActionSelectChange()" style="width:180; position:relative; zoom:100%">
              </select>   
            </span>
            
            <span style="width:50; position:relative; top:-2;">
              <xsl:call-template name="ColorButtonTmpl">
                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                <xsl:with-param name="id"></xsl:with-param>
                <xsl:with-param name="onclick">handleActionSelectChange()</xsl:with-param>
                <xsl:with-param name="size">small</xsl:with-param>
                <xsl:with-param name="width">40</xsl:with-param>
                <xsl:with-param name="text">Go</xsl:with-param>
                <xsl:with-param name="color">green</xsl:with-param>
              </xsl:call-template>
            </span>
          </div>   
          
          <div id="scrollableFundsDiv"  style="position:relative; top:0;">
            <div id="fund_ListDiv">
              <div>              
                <xsl:for-each select="/websrvXML/dtFeeIDInitResponse/FeeID/Funds/Fund">
                  <xsl:call-template name="FeeIDFundListTmpl">                
                    <xsl:with-param name="position"><xsl:value-of select="position()"/></xsl:with-param>
                    <xsl:with-param name="vURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                  </xsl:call-template>
                </xsl:for-each>
              </div>                           
            </div>
          </div>
          
        </div>
      </fieldset>


      <div style="width:340; position:relative; left:275; top:10;">
        <div
          style="cursor:pointer; position:absolute; top:2; left:57; width:105; height:20;"
          class="biggerButton" align="center"
          >                            
          <xsl:call-template name="ColorButtonTmpl">
            <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
            <xsl:with-param name="id">closeFeeIDBtn</xsl:with-param>
            <xsl:with-param name="onclick">parent.closeFeeIDScreen( true );</xsl:with-param>
            <xsl:with-param name="size">large</xsl:with-param>
            <xsl:with-param name="width">105</xsl:with-param>
            <xsl:with-param name="text">Close</xsl:with-param>
            <xsl:with-param name="color">orange</xsl:with-param>
          </xsl:call-template>
          <input type="hidden" id="btnClose"/>
        </div>
      </div>

    
      <div id="disableDiv" style="position:absolute; top:0; left:-10; width:808; height:648; background:e6e6e6; filter:alpha(opacity=70); display:none;">
      </div>
      
      
      <iframe id="fundHistoryIframe"             
				style="position:absolute; top:75px; left:70px; width:600; height:510; background:white; display:none; overflow:visible; border:none" frameborder="0">
				<xsl:attribute name="src">
					javascript: "Loading ..."
				</xsl:attribute>
	</iframe>
	 <div id="fundHistoryDiv" style="background:white; position:absolute; top:75; left:70; width:600; height:510; border:3px solid gray; text-align:center; padding-top:5px; display:none;">
		 <div style="height:25; text-align:left; width:100%; padding-left:40px; padding-bottom:5px">			 
			 <span style="width:200">
				 <span style="position:relative; top: -8; width:80">Start Date:</span>
				 <span style="width:100">
					 <input id="historyFilter_startDateFld" type="text" class="dstdatepicker">
						<xsl:attribute name="dateformat">
						  <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
						</xsl:attribute>
					  </input>
				  </span>
			 </span>			 			 
			 <span style="width:200">
				 <span style="position:relative; top: -8; width:80">End Date:</span>
				 <span style="width:100">
					 <input id="historyFilter_endDateFld" type="text" class="dstdatepicker">
						<xsl:attribute name="dateformat">
						  <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
						</xsl:attribute>
					  </input>
				  </span>
			 </span>
			 <span style="position:relative; top:-8">
				 <xsl:call-template name="ColorButtonTmpl">
					  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
					  <xsl:with-param name="id">filterFundHistoryBtn</xsl:with-param>
					  <xsl:with-param name="onclick">filterFundHistory()</xsl:with-param>
					  <xsl:with-param name="size">small</xsl:with-param>
					  <xsl:with-param name="width">80</xsl:with-param>
					  <xsl:with-param name="text">Filter</xsl:with-param>
					  <xsl:with-param name="color">orange</xsl:with-param>
					</xsl:call-template>			 			 
				</span>
		 </div>
		 <div id="fundHistory_contents" style="height:430; border:1px solid black; overflow-Y:scroll; text-align:left; width:570">		 			 		 
		 </div>
			<div style="position:relative; top:10">
				<xsl:call-template name="ColorButtonTmpl">
				  <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
				  <xsl:with-param name="id">closeFundHistoryBtn</xsl:with-param>
				  <xsl:with-param name="onclick">closeHistoryPopup()</xsl:with-param>
				  <xsl:with-param name="size">large</xsl:with-param>
				  <xsl:with-param name="width">100</xsl:with-param>
				  <xsl:with-param name="text">Close</xsl:with-param>
				  <xsl:with-param name="color">orange</xsl:with-param>
				</xsl:call-template>
			</div>
	</div>
	
    
    
     <iframe id="ratesIframe"             
				style="position:absolute; top:100px; left:70px; width:630; height:140; background:white; display:none; overflow:visible; border:none" frameborder="0">
				<xsl:attribute name="src">
					javascript: "Loading ..."
				</xsl:attribute>
	</iframe>          
      <div id="ratesDiv" style="background:white; position:absolute; top:100; left:70; border:3px solid gray; display:none;"> 
        <div align="center" style="position:relative; width:630;">
          <table style="width:620; position:relative; top:5;" align="center">
            <tr>
              <td style="width:120; padding-left:5px">
                Fund:
              </td>
              <td style="width:450" >
                            
                  <!-- account suggestfield -->
                  <input suggestField="true"
                    class="DataInput" 
                    type="text" 
                    id="ratesFund"
                    style="width:100%"                              
                    dropdownClass="Dropdown" 
                    contentClass="DropdownContent"
                    highlightClass="DropdownHighlight" 
                    displayItems="displayValue"                
                    searchURLGenerator="getFundSearchURL"
                    initialValue=""
                  />
              </td>
               <td style="width:70">
					<span style="position:relative; top:0px">
						<xsl:call-template name="ColorButtonTmpl">
							<xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
							<xsl:with-param name="onclick">alertFundSuggestOptions();</xsl:with-param>                                                   
							<xsl:with-param name="size">small</xsl:with-param>
							<xsl:with-param name="width">70</xsl:with-param>
							<xsl:with-param name="text">Options</xsl:with-param>
							<xsl:with-param name="color">orange</xsl:with-param>
						</xsl:call-template>
					</span>                     
				</td>
            </tr>
            <tr>            
              <td style="width:120; padding-left:5px">
                Effective Date:
              </td> 
              <td colspan="2">
				<span style="width:120">
                  <input style="" id="effDateFld" type="text" class="dstdatepicker">
                    <xsl:attribute name="dateformat">
                      <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                    </xsl:attribute>
                  </input>
                
                </span>
              </td> 
            </tr>
            <tr>            
              <td style="width:120; padding-left:5px">
                Stop Date:
              </td> 
              <td colspan="2">
				<span style="width:120">
                  <input style="" id="stopDateFld" type="text" class="dstdatepicker">
                    <xsl:attribute name="dateformat">
                      <xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>
                    </xsl:attribute>
                  </input>
                </span>
              </td> 
            </tr>           
            <tr id="aggrLinkRow" style="display:none; width:120; padding-left:5px">
              <td align="right">
                Aggr Link:
              </td> 
              <td colspan="2">
                <input style="width:122" id="aggrLink"></input>
              </td> 
            </tr>
          </table>
			 
			<table id="ratesTableHeader" style="width:380; position:relative; top:10; display:none">
				<tr>
					<td style="width:160; padding-left:10">Lower Bound (<xsl:text><![CDATA[>=]]></xsl:text>)</td>
					<td style="width:150; padding-left:10">Upper Bound (<xsl:text><![CDATA[<]]></xsl:text>)</td>
					<td style="width:70">Rate</td>
				</tr>
			</table>
			<table id="ratesTable" style="width:380; position:relative; top:5" align="center">
			</table>		
          
          <table id="ratesTable" style="width:380; position:relative; top:5" align="center">
								</table>
          
          
          
        </div>
        
        <xsl:if test="/websrvXML/dtFeeIDInitResponse/allowTierLowerUpperChanges='yes'">
          <div style="width:80; position:relative; left:257; top:7" align="right">
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">addTierBtn</xsl:with-param>
              <xsl:with-param name="onclick">addRow()</xsl:with-param>
              <xsl:with-param name="size">small</xsl:with-param>
              <xsl:with-param name="width">100</xsl:with-param>
              <xsl:with-param name="text">Add Tier</xsl:with-param>
              <xsl:with-param name="color">green</xsl:with-param>
            </xsl:call-template>
          </div> 
        </xsl:if>

        
          <div style="width:275; position:relative; left:200; top:10; height:40">
          <div
            style="cursor:pointer; position:absolute; top:2; left:0; width:105; height:20; overflow:hidden; background:url({$vURL}images/prototype/biggerButton.png);"
            align="center">
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">btnClose</xsl:with-param>
              <xsl:with-param name="onclick">updateFeeID();</xsl:with-param>
              <xsl:with-param name="size">large</xsl:with-param>
              <xsl:with-param name="width">105</xsl:with-param>
              <xsl:with-param name="text">Save</xsl:with-param>
              <xsl:with-param name="color">green</xsl:with-param>
            </xsl:call-template>
          </div>
          <div
            style="cursor:pointer; position:absolute; top:2; left:113; width:105; height:20; overflow:hidden; background:url({$vURL}images/prototype/biggerButton.png);"
            align="center">
            <xsl:call-template name="ColorButtonTmpl">
              <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
              <xsl:with-param name="id">closeRateBtn</xsl:with-param>
              <xsl:with-param name="onclick">closeRatePopup();</xsl:with-param>
              <xsl:with-param name="size">large</xsl:with-param>
              <xsl:with-param name="width">105</xsl:with-param>
              <xsl:with-param name="text">Close</xsl:with-param>
              <xsl:with-param name="color">orange</xsl:with-param>
            </xsl:call-template>
          </div>
          
        </div>
      </div>
      <!-- End of Non Implemented Stuff -->
    </div>

    <script>
      var _vURL = "<xsl:value-of select="$vURL"/>";
      var _vServletPath = "<xsl:value-of select="$vServletPath"/>";
      var _vCZ = "<xsl:value-of select="$vCZ"/>";  
      var _treeStructure = new Object ();
      var originalDescription = "<xsl:value-of select="translate( //FeeID/feeIDDesc, '&#xa;', ' ' )"/>";
      var _companyCode = "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
      var _ruserId     = "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
      var _sessionId   = "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
      var _envName   = "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";
      
      var _aggrLink = "<xsl:value-of select='/websrvXML/dtFeeIDInitResponse/enableAggrLink'/>";
      var _allowUpdates = "<xsl:value-of select='/websrvXML/dtFeeIDInitResponse/allowUpdates'/>";
      var _allowTierChanges = "<xsl:value-of select='/websrvXML/dtFeeIDInitResponse/allowTierLowerUpperChanges'/>";      
      
      var _maxWindowSize = document.body.clientHeight - 250;      
      var _originalClosedSize = document.getElementById("fundsDiv").offsetHeight;
      var _selectedFund = null;
      var _selectedRateSet = null;
      var _selectedType = null;
      var _screenMode = "modify";
      var _dateFormat = "<xsl:value-of select = "/websrvXML/FormInformation/dateFormat"/>";
      
    	<xsl:choose>
    		<xsl:when test="/websrvXML/dtFeeIDInitResponse/FeeID">
    			var _feeModelVersion = "<xsl:value-of select="/websrvXML/dtFeeIDInitResponse/FeeID/version"/>";
    		</xsl:when>
    		<xsl:otherwise>
    			var _feeModelVersion = "1";
    		</xsl:otherwise>
    	</xsl:choose>    	
     
      var _defaultTiers = new Object();
      <xsl:for-each select="/websrvXML/dtFeeIDInitResponse/DefaultTiers/MFTier">
        _defaultTiers.tier<xsl:value-of select="position()"/> = new Object();
        _defaultTiers.tier<xsl:value-of select="position()"/>.lower = "<xsl:value-of select="lower"/>";
        _defaultTiers.tier<xsl:value-of select="position()"/>.upper = "<xsl:value-of select="upper"/>";  
      </xsl:for-each>
      
      var _actionSelectMap = {};
      _actionSelectMap["none"] = "";
      <xsl:for-each select="/websrvXML/dtFeeIDInitResponse/List[@listName='FundActions']/Element">
         _actionSelectMap["<xsl:value-of select="code"/>"] = "<xsl:value-of select="value"/>";
      </xsl:for-each>

            
   
      
      function onLoad()
      {
      // add or modify
      
      if ("<xsl:value-of select="//FormInformation/feeModelCode"/>" == "")
      _screenMode = "add";
      
      updateGrayDiv();
      
      if (_screenMode == "add")
      {
      modifyDescription();    
      document.getElementById("actionSelect").disabled = true;    
      }
      
        updateActionMenu();
      }
      
    </script>

  </xsl:template>

  <!-- ============================= MAKING A LIST DROP DOWN ======================================================== -->
  <xsl:template match="List">
    <xsl:param name="selected"/>
    <xsl:apply-templates select="Element">
      <xsl:with-param name="selected">
        <xsl:value-of select="$selected"/>
      </xsl:with-param>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="Element">
    <xsl:param name="selected"/>
    <option>
      <xsl:attribute name="value">
        <xsl:value-of select="code"/>
      </xsl:attribute>
      <xsl:if test="code=$selected">
        <xsl:attribute name="selected">true</xsl:attribute>
      </xsl:if>
      <xsl:value-of select="value"/>
    </option>
  </xsl:template>


  <xsl:template name="tmplBehaviours"> </xsl:template>


</xsl:stylesheet>
