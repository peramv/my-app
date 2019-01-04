<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes" />

    <xsl:include href="{$APPCFG:ApplicationPrivateDirectory}{$APPCFG:DataDirectory}{$APP:CLIENT}/components/ColorButtons/ColorButtons_Template.xsl"/>

    <xsl:variable name="vClient"       select="/websrvXML/requestInfo/client"/>
    <xsl:variable name="vServletPath"  select="/websrvXML/requestInfo/servletPath"/>
    <xsl:variable name="vDataDir"      select="/websrvXML/transformNode/datadir"/>
    <xsl:variable name="vURL"          select="concat( $vDataDir, $vClient, '/' )"/>
    <xsl:variable name="vTX"           select="/websrvXML/FormInformation/tx"/>
    <xsl:variable name="vCZ"           select="/websrvXML/FormInformation/cz"/>
    <xsl:variable name="vTIDX"         select="/websrvXML/FormInformation/tidx"/>




    <xsl:template match="/">

        <Screen>

            <html>
                <title>Management Fee Rebates</title>

                <head>
                    <link rel="stylesheet" type="text/css" href="{$vURL}css/ManagementFee.css"></link>

                    <script src="{$vURL}WebLibrary/JSLib/UTL.js"></script>
                    <script src="{$vURL}WebLibrary/JSLib/HTTP.js"></script>
                    <script src="{$vURL}WebLibrary/JSLib/Err.js"></script>
                    <script src="{$vURL}WebLibrary/JSLib/XML.js"></script>
                    
                    <script src="{$vURL}javascript/General_Desktop.js"></script>

                    <script src="{$vURL}javascript/ManagementFeeRebate_Main.js"></script>
                    
                    <script>
                        var _vServletPath     = "<xsl:value-of select="$vServletPath"/>";
                        var _vCZ              = "<xsl:value-of select="$vCZ"/>";
                        var _vURL             = "<xsl:value-of select="$vURL"/>";
                        var _companyCode      = "<xsl:value-of select="/websrvXML/FormInformation/companyCode"/>";
                        var _ruserId          = "<xsl:value-of select="/websrvXML/FormInformation/ruserId"/>";
                        var _sessionId        = "<xsl:value-of select="/websrvXML/FormInformation/sessionId"/>";
                        var _envName        = "<xsl:value-of select="/websrvXML/FormInformation/envName"/>";
                        var _dateFormat       = "<xsl:value-of select="/websrvXML/FormInformation/dateFormat"/>";
                        
                        setSessionToken( _sessionId );
                    </script>

                </head>

                <body onload="loading()">

                    <xsl:if test="/websrvXML/responseContents/error">
                        <script>alert('<xsl:value-of select="/websrvXML/responseContents/error"/>');</script>
                    </xsl:if>
                    
                    <div style="width:800px; padding:5px; text-align:center">
                        <!-- Header - title and search -->
                        <div style="width:100%; padding-bottom:15px">
                            <div style="width:100%; text-align:center; padding-top:10px; padding-bottom:20px">
                                <span style="font-weight:bold; padding-right:5px">Search:</span>
                                <span><input id="searchFld" onkeydown="handleKeyDownSearch()" type="text" style="font-size: 13px;" size="20"/></span>
                                <span style="padding-left:5px; padding-right:5px;">                                    
                                    <xsl:call-template name="ColorButtonTmpl">
                                        <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                        <xsl:with-param name="id">searchBtn</xsl:with-param>
                                        <xsl:with-param name="onclick">search();</xsl:with-param>
                                        <xsl:with-param name="size">small</xsl:with-param>
                                        <xsl:with-param name="width">90</xsl:with-param>
                                        <xsl:with-param name="text">Search</xsl:with-param>
                                        <xsl:with-param name="color">green</xsl:with-param>
                                    </xsl:call-template>
                                </span>
                                <span>
                                    <xsl:call-template name="ColorButtonTmpl">
                                        <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                        <xsl:with-param name="onclick">alert( "Search by Account Number or Rebate Fee Model Code" );</xsl:with-param>                                                   
                                        <xsl:with-param name="size">small</xsl:with-param>
                                        <xsl:with-param name="width">70</xsl:with-param>
                                        <xsl:with-param name="text">Options</xsl:with-param>
                                        <xsl:with-param name="color">orange</xsl:with-param>
                                    </xsl:call-template>
                                </span>     
                            </div>
                        </div>

                        <fieldset style="width:98%">
                            <legend>
                                <span style="border-bottom:2px solid #ffd696; height:15px;">Management Fee Rebate Model Codes</span>
                                <span style="padding-left:10px; position:relative; top:-2">
                                    <xsl:call-template name="ColorButtonTmpl">
                                        <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                        <xsl:with-param name="onclick">launchDetails()</xsl:with-param>
                                        <xsl:with-param name="size">small</xsl:with-param>
                                        <xsl:with-param name="width">220</xsl:with-param>
                                        <xsl:with-param name="text">Add Rebate Fee Model Code</xsl:with-param>
                                        <xsl:with-param name="color">orange</xsl:with-param>
                                    </xsl:call-template>
                                </span>
                            </legend>

                            <div id="dataDiv" style="width:100%; text-align:left; padding-top:5px; padding-left:20px">

                            </div>
                        </fieldset>
                        
                        <div style="cursor:pointer; position:relative; width:100; left:200; top:25; height:50;" align="center">
                            <xsl:call-template name="ColorButtonTmpl">
                                <xsl:with-param name="baseURL"><xsl:value-of select="$vURL"/></xsl:with-param>
                                <xsl:with-param name="id">btnCloseWindow</xsl:with-param>
                                <xsl:with-param name="onclick">UTL.getElem( "btnClose" ).click();</xsl:with-param>
                                <xsl:with-param name="size">large</xsl:with-param>
                                <xsl:with-param name="width">100</xsl:with-param>
                                <xsl:with-param name="text">Close</xsl:with-param>
                                <xsl:with-param name="color">orange</xsl:with-param>
                            </xsl:call-template>
                            <input type="button" id="btnClose" style="display:none"/>
                        </div>
                    </div>
                    
                    <!-- page disabling div -->
                    <div id="disableDiv" style="position:absolute; top:0; left; 0; width:100%; height:100%; background:e6e6e6; filter:alpha(opacity=70); display:none;">
                    </div>
                    
                    <div id="searchIndicatorDiv" style="position:absolute; border:2px solid grey; width:200; height:50; top:100; left:250; background:white; z-index:50; padding-top:10px; display:none">
                        <span style="width:100%; text-align:center; font-size:15px; font-style:italic">Searching ...</span>
                    </div>
                    
                    <iframe id="feeID_Frame"             
                        style="position:absolute; top:30px; left:10px; width:800; height:650; background:white; display:none; overflow:visible; border:2px solid gray">
                        <xsl:attribute name="src">
                            javascript: "Loading ..."
                        </xsl:attribute>
                    </iframe>
                                          
                </body>

            </html>
        </Screen>

    </xsl:template>
</xsl:stylesheet>