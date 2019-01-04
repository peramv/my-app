<!--   
  @file     DesktopWeb.xsl
  @desc   The master xsl (html) file for all DesktopWeb screens 
  @author   Rod Walker  
  @date       2010-08-13  
  @history  
    22 May 2014 N. Suanlamyai P0225140 T55105
    16 Jun 2015 N. Suanlamyai P0241773 T81011 Add treegrid library
    24 Feb 2016 Watchara Th. P0241773 DFT0056976 T82328 Fixed screens don't response when user's profile has too many slots attached.
    19 May 2016 Lalitphan S. P0241773 DFT0060804 T82876 Add cookies disable message
    17 Nov 2016 Narin Tong P0256381  T84279 DFT0069397 CHG0045765 Fund Broker Linkage for Germany, adding a new layout to load a screen within a popUp
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" omit-xml-declaration="yes" />
  
  <xsl:variable name="vServletPath"   select="/websrvXML/requestInfo/servletPath"/>
  <xsl:variable name="vClient"        select="/websrvXML/requestInfo/client"/>  
  <xsl:variable name="vPath"          select="concat( /websrvXML/transformNode/datadir, $vClient, '/' )"/>  
  <xsl:variable name="vScreen"    select="/websrvXML/FormInformation/screen"/>
  <xsl:variable name="vLocale"    select="/websrvXML/FormInformation/locale"/>
  
  <xsl:variable name="vExtLayout">
    <xsl:if test="/websrvXML/FormInformation/extLayout and /websrvXML/FormInformation/extLayout != ''">
      <xsl:value-of select="concat('_', /websrvXML/FormInformation/extLayout)"/>
    </xsl:if>
    <xsl:if test="not(/websrvXML/FormInformation/extLayout and /websrvXML/FormInformation/extLayout != '')">
      <xsl:text></xsl:text>
    </xsl:if>
  </xsl:variable>
  
  <xsl:template match="/">
    <HTML_WRAPPER>      
      <xsl:text><![CDATA[<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN"
         "http://www.w3.org/TR/html4/frameset.dtd">]]></xsl:text>     
      <html>
        <head>
            <title><xsl:value-of select="$vScreen"/></title>
            
            <meta http-equiv="content-type" content="text/html;charset=utf-8" />
          
          <!-- EXT JS CSS -->         
          <link rel="stylesheet" type="text/css" href="{$vPath}extjs/resources/css/ext-all.css"/>
          <link rel="stylesheet" type="text/css" href="{$vPath}extjs/resources/css/xtheme-gray.css"/>             
                    <link rel="stylesheet" type="text/css" href="{$vPath}extjs/ux/treegrid/treegrid.css"/>    
          
          <!-- DesktopWeb CSS -->
          <link rel="stylesheet" type="text/css" href="{$vPath}css/DesktopWeb.Common.css"/>
          <link rel="stylesheet" type="text/css" href="{$vPath}css/screens/{$vScreen}.css"/>          
          
          <!-- EXT JS Javascript -->                
          <xsl:choose> 
            <xsl:when test="/websrvXML/FormInformation/debug = 'true'">
              <script src="{$vPath}extjs/adapter/ext/ext-base-debug-w-comments.js"></script> <!-- must be loaded first -->          
              <script src="{$vPath}extjs/ext-all-debug-w-comments.js"></script>
            </xsl:when>
            <xsl:otherwise>
              <script src="{$vPath}extjs/adapter/ext/ext-base.js"></script> <!-- must be loaded first -->
              <script src="{$vPath}extjs/ext-all.js"></script>
            </xsl:otherwise>
          </xsl:choose>

          <script src="{$vPath}extjs/ux/RowExpander.js"></script>
          <script src="{$vPath}extjs/ux/MonthPicker.js"></script>
                    <script src="{$vPath}extjs/ux/treegrid/TreeGrid.js"></script>
                    <script src="{$vPath}extjs/ux/treegrid/TreeGridColumnResizer.js"></script>
                    <script src="{$vPath}extjs/ux/treegrid/TreeGridColumns.js"></script>
                    <script src="{$vPath}extjs/ux/treegrid/TreeGridLoader.js"></script>
                    <script src="{$vPath}extjs/ux/treegrid/TreeGridNodeUI.js"></script>
                    <script src="{$vPath}extjs/ux/treegrid/TreeGridSorter.js"></script>
          <script src="{$vPath}extjs/locale/ext-lang-{$vLocale}.js"></script>
          
          <!-- IFDS Javascript -->
          <script>Ext.namespace("IFDS");</script>  <!-- need to define namespace object-->
          <script src="{$vPath}js/IFDS.Xml.js"/>          
          <script src="{$vPath}js/IFDS.SuggestField.js"/>         
                  
          
          <!-- DesktopWeb Javascript -->          
          <script src="{$vPath}js/DesktopWeb.js"/>          
          <script>
            // initialize DesktopWeb global variables before loading screen
            DesktopWeb._SERVLET_PATH  = '<xsl:value-of select="$vServletPath"/>';
            DesktopWeb._SRC_PATH    = '<xsl:value-of select="$vPath"/>';
            
            DesktopWeb._SCREEN_PARAM_MAP = {};
            <xsl:for-each select=".//FormInformation/*">
                 <xsl:variable name="screenInfo">
                <xsl:call-template name="replace-string">
                  <xsl:with-param name="text" select="."/>
                  <xsl:with-param name="replace" select='"&apos;"'/>
                  <xsl:with-param name="by" select='"&amp;apos;"'/>
                </xsl:call-template>
              </xsl:variable>
              DesktopWeb._SCREEN_PARAM_MAP['<xsl:value-of select="name()"/>'] = '<xsl:value-of select="$screenInfo"/>';
            </xsl:for-each>                                   
          </script> 
          <script src="{$vPath}js/DesktopWeb.Util.js"/>
          <script src="{$vPath}js/DesktopWeb.Translation.js" charset="UTF-8"/>
          <script src="{$vPath}js/DesktopWeb.Ajax.js"/> 
          <script src="{$vPath}js/DesktopWeb.Controls.js"/>
          <script src="{$vPath}js/DesktopWeb.AdvancedControls.js"/>
                    
          <script src="{$vPath}js/DesktopWeb.Main.js"/>
          <script src="{$vPath}js/screens/{$vScreen}.Translation.js" charset="UTF-8"/>                  
          <script src="{$vPath}js/screens/{$vScreen}.Controller.js"/>
          <script src="{$vPath}js/screens/{$vScreen}{$vExtLayout}.Resources.js"/>
          
        </head>
        <body>
          <div id="x-form-field" style="font:normal 12px tahoma, arial, helvetica, sans-serif; color: red; display:none;">
          </div>
          
          <div id="DesktopWeb-Processing-Mask"></div>         
          <div id="DesktopWeb-Processing">            
            <div class="DesktopWeb-Processing-Message">             
            </div>
          </div>
          
          <form id="BuildPDFReport-form" method="POST" style="display:none" action="{$vServletPath}">
            <input type="text" name="BuildPDFReport-data"/>
          </form>
          
          <form id="SmartPDF-form" name="SmartPDF-form" method="POST" style="display:none" action="smartpdf" target="_self" accept-charset="UTF-8">
            <input type="hidden" name="dataXMLString"/>
            <input type="hidden" name="download"/>
          </form>

          <form id="GoToScreen-form" name="GoToScreen-form" method="POST" style="display:none" action="{$vServletPath}" target="_self">
            <xsl:for-each select=".//FormInformation/*">
              <input type="hidden" name="{name()}" value="{.}"/>
            </xsl:for-each>
            <input name="jobname" type="hidden"></input>
          </form>

          <input type="button" name="btnAcctDetail" id="btnAcctDetail" style="display:none;"/>          
          <input type="button" name="btnTransactionDetails" id="btnTransactionDetails" style="display:none;"/>          
          <input type="button" name="btnOK" id="btnOK" style="display:none;"/>
          <input type="button" name="btnCancel" id="btnCancel" style="display:none;"/>
          <input type="button" name="btnConfirmDlg" id="btnConfirmDlg" style="display:none;"/>
        </body>
        <script type="text/javascript">
          //translation declaration
          var _translationMap = DesktopWeb.Translation.getTranslationMap();
          
          //check cookie enable
          var areCookieEnable = (navigator.cookieEnabled) ? true : false;
          if (!areCookieEnable){
            var cookieMsg = document.getElementById("x-form-field");
            cookieMsg.innerHTML = '<img src="{$vPath}images/warning.png" />' + ' ' + _translationMap['CookieDisable'];
            cookieMsg.style.display = "block";
          }
        </script>
      </html>
    </HTML_WRAPPER>
  </xsl:template>

  <xsl:template name="replace-string">
    <xsl:param name="text" />
    <xsl:param name="replace" />
    <xsl:param name="by" />
    <xsl:choose>
    <xsl:when test="contains($text, $replace)">
      <xsl:value-of select="substring-before($text,$replace)" />
      <xsl:value-of select="$by" />
      <xsl:call-template name="replace-string">
      <xsl:with-param name="text" select="substring-after($text,$replace)" />
      <xsl:with-param name="replace" select="$replace" />
      <xsl:with-param name="by" select="$by" />
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$text" />
    </xsl:otherwise>
    </xsl:choose>
  </xsl:template>


</xsl:stylesheet>
<!-- eof -->