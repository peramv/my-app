<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:template name="master_layout">
    <xsl:param name="session"/>
    <xsl:param name="noheader" />
    <xsl:param name="nofooter" />
    <xsl:param name="showMenu"/>
    <xsl:param name="showAwdContainer"/>
    <xsl:param name="additionalTitle"/>
    <xsl:param name="pageTitle"/>
    <xsl:param name="selectClient"/>
    <xsl:param name="displayTitle"/>

    <xsl:variable name="vPageTitle">
      <xsl:choose>
        <xsl:when test="string-length( $pageTitle ) &gt; 0">
          <xsl:value-of select="$pageTitle"/>
        </xsl:when>
        <xsl:otherwise></xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <Screen>
      <html>
        <head>
          <title>
            <xsl:value-of select="$pageTitle"/> <xsl:value-of select="$additionalTitle"/> <xsl:if test="//context/entityId!=''">  Entity <xsl:value-of select="//context/entityId"/> </xsl:if><xsl:if test="//context/accountNumber!=''"> Account <xsl:value-of select="//context/accountNumber"/></xsl:if>
          </title>

          <xsl:call-template name="webbehaviours"/>

          <style type="text/css">
            ..topmenu { color: white; background: white; font-family:Tahoma, Verdana, Helvetica, sans-serif; font-size: 10pt; font-weight: bold; margin:1px; width:100%; text-decoration: none; z-index=1001; align:right; }
            ..topmenu UL { PADDING-RIGHT: 0px; PADDING-LEFT: 0px; PADDING-BOTTOM: 0px; MARGIN: 0px; PADDING-TOP: 0px; LIST-STYLE-TYPE: none; width:100%;text-decoration: none; }
            ..topmenu LI { FLOAT: left; WIDTH: 10em; POSITION:relative; text-decoration: none; }
            ..topmenu LI UL { DISPLAY: none; LEFT: 0px; POSITION: absolute; TOP: 1em; border-width:1px; border-color:black;  text-decoration: none; }
            ..topmenu LI:hover UL { DISPLAY: block; text-decoration:none; }
            ..topmenu LI.over UL { DISPLAY: block; text-decoration: none; }
            ..topmenu UL LI A { text-decoration:none; color: #003366; width: 100%; }
            ..titleDiv {   height:16px; background-image:url({$vURL}images/menubackground.jpg); }
            ..menuFont { color: darkblue; font-family: Verdana, Helvetica, sans-serif; font-size: 10px; font-style: normal; font-weight: bold; margin-left: 0em;  margin-top: 0.5em; margin-bottom: 0.5em; text-align: center; text-indent: 0em;
            text-decoration: none; white-space: normal }
            ..menuFont hover menuFont { color: lightblue; font-family: Verdana, Helvetica, sans-serif; font-size: 10px;  font-style: normal; font-weight: bold; margin-left: 0em; margin-top: 0.5em;
            margin-bottom: 0.5em; text-align: center; text-indent: 0em; text-decoration:
            none; white-space: normal }
            ..disabledMenuFont { color: darkgray; font-family: Verdana, Helvetica, sans-serif; font-size: 10px; font-style: normal; font-weight: bold; margin-left: 0em; margin-top: 0.5em; margin-bottom: 0.5em; text-align: center;
            text-indent: 0em; text-decoration: none; white-space: normal }
          </style>

          <xsl:call-template name="common_js"/>
        </head>

        <body text="black" onload="preload()">
          <xsl:attribute name="style">
            background:#<xsl:value-of select="//FormInformation/bgcolor"/>;
          </xsl:attribute>

          <xsl:call-template name="valuesets"/>

          <xsl:if test="not($noheader='true')">
            <div id="menuDiv">
              <xsl:apply-templates select="//menu"/>
              <script src="{$vURL}javascript/topmenu.js">
                // comment. pls keep
              </script>
            </div>
          </xsl:if>

          <div id="contentsDiv" class="contentsDiv" style="margin-left:10px">
            <xsl:if test="not($noheader='true')">
              <br></br>
              <p align="left" style="margin-left:10px">
                <xsl:if test="$displayTitle!='false'">
                  <font class="pageTitleFont"><xsl:value-of select="$vPageTitle"/></font>
                </xsl:if>
              </p>
            </xsl:if>

            <form name="myform" method="POST">
              <xsl:attribute name="action">
                <xsl:value-of select="$vServletPath"/>
              </xsl:attribute>

              <!--
                <xsl:if test="$createSession=not('true')">
                <input type="hidden" name="tidx" value="^TIDX^" />
                </xsl:if>
              -->

              <!--
                <input type="hidden" name="cz" value="^CLIENT^" />
                <input type="hidden" name="random" value="^RANDOM^" />
                <input type="hidden" name="isNASU" value="^_FormBean.isNASU^" />
                <input type="hidden" name="isCOA" value="^_FormBean.isCOA^" />
                <input type="hidden" name="coaFromScr" value="" />
                <input type="hidden" name="coaFromScrAction" value="" />
              -->


              <xsl:element name="input">
                <xsl:attribute name="type">hidden</xsl:attribute>
                <xsl:attribute name="name">cz</xsl:attribute>
                <xsl:attribute name="value"><xsl:value-of select="$vCZ"/></xsl:attribute>
              </xsl:element>

              <xsl:if test="$session='yes'">
                <xsl:element name="input">
                  <xsl:attribute name="type">hidden</xsl:attribute>
                  <xsl:attribute name="name">tidx</xsl:attribute>
                  <xsl:attribute name="value"><xsl:value-of select="$vTIDX"/></xsl:attribute>
                </xsl:element>
              </xsl:if>

              <input type="hidden" name="envName" id="envName"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/envName"/></xsl:attribute></input>
              <input type="hidden" name="companyCode" id="companyCode"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/companyCode"/></xsl:attribute></input>
              <input type="hidden" name="ruserId" id="ruserId"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/ruserId"/></xsl:attribute></input>
              <input type="hidden" name="sessionId" id="envName"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/sessionId"/></xsl:attribute></input>
              <input type="hidden" name="bgColor" id="bgColor"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/bgcolor"/></xsl:attribute></input>

              <input type="hidden" id="fldJobname" name="jobname" value=""/>
              <input type="hidden" id="cjobname" name="cjobname" value=""/>

              <xsl:choose>
                <xsl:when test="//requestStatus/status='error'">
                  <xsl:call-template name="tmplErrorHandler"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:call-template name="form_callback" />
                </xsl:otherwise>
              </xsl:choose>

            </form>



            <xsl:if test="not( //requestStatus/status='error' )">
              <xsl:call-template name="page_callback"/>
            </xsl:if>

          </div>




          <!-- AWD Container -->
          <xsl:if test="$showAwdContainer='true'">
            <xsl:call-template name="tmplAwdContainer"/>
          </xsl:if>
          <!-- END AWD Container -->

          <!--- FOOTER -->
          <xsl:if test="not($nofooter='true')">
            <!-- xsl:call-template name="footer"/ -->
          </xsl:if>
          <!-- PROGRESS BAR -->



          <br/>


        </body>
      </html>
    </Screen>

  </xsl:template>



  <!-- ============================= COMMON JS TEMPLATE - start  ======================== -->
  <xsl:template name="common_js">

    <link rel="stylesheet" type="text/css" href="{$vURL}css/grey.css"/>
    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>
    <link rel="shortcut icon" href="{$vURL}images/favicon-canada-64x64.ico" type="image/x-icon" />
    <script src="{$vURL}behaviors/tba.js">
      // comment. pls keep
    </script>
    <script language="javascript">
      var _servletPath = '<xsl:value-of select="$vServletPath"/>';
      var _cz = '<xsl:value-of select="$vCZ"/>';
    </script>
    <script src="{$vURL}javascript/base.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/grid.js">
      // comment. pls keep
    </script>
    <script src="{$vURL}javascript/errors.js">
      // comment. pls keep
    </script>

    <script language="javascript">
      function documentOnKeyDown() {
      //alert(event.keyCode);
      /*
      if (event.keyCode == 113) {
      event.keyCode = 0;
      event.returnValue = false;
      event.cancelBubble = true;
      trading();
      return false;
      }

      if (event.keyCode == 115) {
      event.keyCode = 0;
      event.returnValue = false;
      event.cancelBubble = true;
      <xsl:if test="//context/accountNumber!=''">  accountSummary();      </xsl:if>
      return false;
      }
      */

      /* if (event.keyCode == 119) {
      event.keyCode = 0;
      event.returnValue = false;
      event.cancelBubble = true;
      <xsl:if test="//context/accountNumber!=''">  transactionHistory();   </xsl:if>
      return false;
      }
      */
      /*  if (event.keyCode == 117) {
      event.keyCode = 0;
      event.returnValue = false;
      event.cancelBubble = true;
      <xsl:if test="//context/accountNumber!=''"> banking();         </xsl:if>
      return false;
      }
      */
      /*
      if (event.keyCode == 118) {
      event.keyCode = 0;
      event.returnValue = false;
      event.cancelBubble = true;
      goto('/BckOfficeTradingLayoutEdit');
      return false;
      }
      */
      /*
      if (event.keyCode == 117) {
      event.keyCode = 0;
      event.returnValue = false;
      event.cancelBubble = true;
      goto('/AI');
      return false;
      }
      */

      }
      document.onkeydown = function () {
      documentOnKeyDown();
      }

      // Defines for the error images...
      var ERROR_IMAGE_URL   = "<xsl:value-of select="$vURL"/>images/bad2.gif";
      var ROW_HIGHLIGHT_COLOR   = "lightyellow";
      var BLANK_IMAGE_URL   = "<xsl:value-of select="$vURL"/>images/blank.jpg";
      var WARNING_IMAGE_URL = "<xsl:value-of select="$vURL"/>images/warning.gif";
      var ROW_COLOR   = "white";


      function resetErrorImg(element)
      {

        if (element) {
                        element.src = BLANK_IMAGE_URL;
                        element.alt = "";
                      }
      }

      function getErrorImgElement(element)
      {
          var img = element.name + "Img";
          return img;

      }



      // sets the next event name in the form but will only move to
      // the next event when the form is submitted via a submit button
      // or via the JavaScript submit() function.
      // NOT USED WITH JD
      /*
      // goto a flow control event, e.g. goto( '/displayLogin.go' );
      /*
      function goto( event_name )
      {
      if (event_name.indexOf("/") == 0) { event_name = event_name.substring(1, event_name.length); };
      setActionEvent(event_name);
      myform.submit();
      }
      /*
      function setActionEvent(event_name)
      {
      myform.action = "^CLIENTCFGVAL:servletcontext^^TXDIR^/" + event_name;
      }
      */

      //TODO: add description - called when a page is loading???
      function preload()
      {
      if(this.loading)
      {
      loading();
      }
      }
      // make div visible
      function     makeVisible(divName) {
      if (document.getElementById(divName))   document.getElementById(divName).style.visibility='visible'      ;

      }
      function     makeInvisible(divName) {

      if (document.getElementById(divName))   document.getElementById(divName).style.visibility='hidden'      ;

      }

    </script>


  </xsl:template>
  <!-- ============================= COMMON JS TEMPLATE - end  ======================== -->


  <!-- ============================= VALUE SETS TEMPLATE - start  ======================== -->
  <xsl:template name="valuesets">
    <xsl:for-each select="//lists/list">
      <xml>
        <xsl:attribute name="id">
          <xsl:text>xml</xsl:text><xsl:value-of select="@id"/>
        </xsl:attribute>
        <newdataset>
          <xsl:for-each select="element">
            <combobox>
              <display>
                <xsl:value-of select="value"/>
              </display>
              <formfield>
                <xsl:value-of select="code"/>
              </formfield>
            </combobox>
          </xsl:for-each>
        </newdataset>
      </xml>
    </xsl:for-each>
  </xsl:template>
  <!-- ============================= VALUE SETS TEMPLATE - end ======================== -->


  <!-- ============================= ERRORS TEMPLATE - start  ========================== -->
  <xsl:template name="tmplErrorHandler">
    <center>

      <table width="80%">
        <tr>
          <td align="left">
            The following errors have occured...
          </td>
        </tr>
      </table>

      <br/>
      <hr/>
      <br/>

      <table width="80%">
        <tr>
          <td width="10px"></td>
          <td width="10px"></td>
          <td><b>Error Code</b></td>
          <td><b>Description</b></td>
        </tr>
        <xsl:for-each select="//errors/error">
          <tr>
            <td width="10px">
              <xsl:choose>
                <xsl:when test="errorSeverity=warning">
                  <img id ="branchCodeImg" src="{$vURL}images/warning.gif">
                    <xsl:attribute name="title">
                      <xsl:value-of select="errorCode"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="errorType"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="errorSeverity"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="nodeName"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="text"/>
                    </xsl:attribute>
                  </img>
                </xsl:when>
                <xsl:otherwise>
                  <img id ="efOtherReferenceImg" src="^CLIENTCFGVAL:servletcontext^^CLIENTDIR^images/bad2.gif">
                    <xsl:attribute name="title">
                      <xsl:value-of select="errorCode"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="errorType"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="errorSeverity"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="nodeName"/>
                      <xsl:text> - </xsl:text>
                      <xsl:value-of select="text"/>
                    </xsl:attribute>
                  </img>
                </xsl:otherwise>
              </xsl:choose>
            </td>
            <td width="10px"></td>
            <td><xsl:value-of select="errorCode"/></td>
            <td><xsl:value-of select="text"/></td>
          </tr>
        </xsl:for-each>
      </table>

      <br/>
      <hr/>
      <br/>

      <table>
        <tr>
          <td>
            <button id="btnRetry"
              name="btnRetry"
              AccessKey='R'
              type="button"
              class="dstbutton"
              style="margin:0; align=right"
              onclick="javascript:history.go( 0 );">
              <u>R</u>etry</button>
          </td>
          <td>
            <xsl:text disable-output-escaping="yes"><![CDATA[ ]]></xsl:text>

          </td>
          <td>
            <button id="btnCancel"
              name="btnCancel"
              AccessKey='C'
              type="button"
              class="dstbutton"
              style="margin:0; align=right"
              onclick="javascript:history.go( -1 );">
              <u>C</u>ancel</button>
          </td>
        </tr>
      </table>

      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>
      <br/>

    </center>

  </xsl:template>
  <!-- ============================= ERRORS TEMPLATE - end  ========================== -->


  <!-- ============================= AWD CONTAINER TEMPLATE - start  ========================== -->
  <xsl:template name="tmplAwdContainer">
    <div id="divAwdContainer" style="margin-left:10px;OVERFLOW:auto;border:1px solid black;height:120px;width:795px;" >
      <table width="100%" cellpadding="0" cellspacing="0">
        <thead class="fixedHeader">
          <tr class="DataGridFixedHeader">
            <td align="left" style="background-image:url(^CLIENTCFGVAL:servletcontext^^CLIENTDIR^images/TA2000BackDrop.jpg);margin: 0.75em 0;padding: 0.3em;">
              <font color="white">Work Assistant</font>
            </td>
          </tr>
        </thead>
        <tr>
          <td>
            <table width="100%" cellpadding="0" cellspacing="0" border="0" style="margin-left:0px">
              <tr>
                <td>
                  <img height="16px" width="16px" src="^CLIENTCFGVAL:servletcontext^^CLIENTDIR^images/awd_workObject.gif"/>
                  <xsl:text> </xsl:text><a href="">SAMPLE BA - SAMPLECASE - INDEXED - PROCESS - Updatable - Locked By: USERID - 2005-06-01.12.00.00.00</a>
                </td>
                <tr>
                  <td>
                    <img height="16px" width="16px" src="^CLIENTCFGVAL:servletcontext^^CLIENTDIR^images/treeL.jpg"/>
                    <img height="16px" width="16px" src="^CLIENTCFGVAL:servletcontext^^CLIENTDIR^images/awd_sourceObject.gif"/>
                    <xsl:text> </xsl:text><a href="">SAMPLE BA - SAMPLEWT - CREATED - PROCESS - Updatable - Locked By: USERID - 2005-06-01.12.00.00.00</a>
                  </td>
                </tr>
              </tr>
            </table>
          </td>
        </tr>
      </table>
    </div>
  </xsl:template>
  <!-- ============================= AWD CONTAINER TEMPLATE - end ========================== -->


  <!-- ============================= WEB BEHAVIOURS TEMPLATE - start  ======================== -->
  <xsl:template name="webbehaviours">

    <link rel="stylesheet" href="{$vURL}behaviors/ta2000.css" type="text/css" />

    <style type="text/css">
      button.dstbutton{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstbutton.htc)}
      button.dstappbutton{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstappbutton.htc)}
      select.flat{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstselect.htc)}
      dst\:dstgrid{width:100%;height:100%;}
      dst\:dsttooltip{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/tooltip.htc)}
      xml.dsttabs{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dsttabs/dsttabs.htc)}
      input.dstcurrency{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstcurrency.htc)}
      input.dstinteger{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstinteger.htc)}
      input.dstpercent{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstpercent.htc)}
      input.dsttextbox{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dsttextbox.htc)}
      input.dstcombobox{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstcombobox/dstcombobox.htc)}
      input.dstspinner{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstspinner/dstspinner.htc)}
      input.dstdatepicker{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstdatepicker/dstdatepicker.htc)}
      input.dstmask{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstmask.htc)}
      input.mask{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/mask.htc)}
      div.dstpanel{behavior:url(<xsl:value-of select="$vURL"/>behaviors/js/dstpanel/dstpanel.htc)}
    </style>
  </xsl:template>
  <!-- ============================= WEB BEHAVIOURS TEMPLATE - end  ======================== -->


  <!-- ======================== POPUP WINDOWS TEMPLATE - start ========================== -->
  <xsl:template name="tmplPopup">
    <xsl:param name="id"/>
    <xsl:param name="message"/>
    <xsl:param name="left" />
    <xsl:param name="style"/>
    <xsl:param name="header"/>
    <xsl:param name="imageIcon"/>

    <div class="popupWaiting" >
      <xsl:attribute name="id"><xsl:value-of select="$id"/></xsl:attribute>
      <xsl:attribute name="style"><xsl:if test="$style!=''"><xsl:value-of select="$style"/></xsl:if></xsl:attribute>
      <center>
        <table border="0">
          <tr>
            <td> <header><xsl:value-of select="$header"/></header></td>
            <td> <xsl:if test="$imageIcon!=''"><img><xsl:attribute name="src"><xsl:value-of select="$imageIcon"/></xsl:attribute></img></xsl:if> </td>
          </tr>
          <tr><td colspan="2"> <label><xsl:value-of  select="$message"/></label>    </td></tr></table>   </center>
    </div>

  </xsl:template>
  <!-- ======================== POPUP WINDOWS TEMPLATE - start ========================== -->


  <!-- =============================== MENU TEMPLATE - start ========================== -->
  <xsl:template match="menu">

    <!--table width="100%">
      <tr>
      <td align="left" width="10%">
      <img
      src="^CLIENTCFGVAL:servletcontext^^CLIENTDIR^/images/ifast.jpg"
      border="0"></img><BR/>
      </td>
      <td align="left" valign="center" width="90%">
      <xsl:choose>
      <xsl:when test="/root/AWDData/usingAWD='true'">
      <font class="tinyText">Using AWD</font>
      </xsl:when>
      <xsl:otherwise>
      <font class="tinyText">Not Using AWD</font>
      </xsl:otherwise>
      </xsl:choose>
      </td>
      </tr>
      </table -->

    <div id="menu" class="topmenu">

      <UL id="nav">
        <xsl:for-each select="topmenu">
          <LI>
            <div class="titleDiv">
              <center><xsl:text>
              </xsl:text><font class="menuFont"><xsl:value-of
                select="title"/></font>
              </center>
            </div>
            <ul>
              <table
                style="border-width:1px;width:100%;background-color:#eff3fc;border-color:black"
                cellpadding="0" cellspacing="0">
                <tr><td>
                  <xsl:apply-templates select="submenu"/>
                </td></tr></table>
            </ul>
          </LI>
        </xsl:for-each>
      </UL>
    </div>

  </xsl:template>
  <!-- =============================== SUBMENU TEMPLATE - end ========================== -->


  <!-- =============================== SUBMENU TEMPLATE - start ========================== -->
  <xsl:template match="submenu">


    <!--
      - Default the enabled state flag to 'true'
    -->
    <xsl:variable name="vEnableLink">
      <xsl:choose>
        <xsl:when test="string-length( onlyEnabledForAWD ) = 0">true</xsl:when>
        <xsl:otherwise>
          <xsl:choose>
            <xsl:when test="onlyEnabledForAWD='true'">
              <xsl:value-of select="/root/AWDData/usingAWD"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:choose>
                <xsl:when test="/root/AWDData/usingAWD='true'">false</xsl:when>
                <xsl:otherwise>true</xsl:otherwise>
              </xsl:choose>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <!--
      - If the value of the XML node specifed by the 'controlFlag' (e.g. 'usingAWD')
      - then enable/disable menu links based on that.
    -->
    <xsl:choose>
      <xsl:when test="$vEnableLink='true'">
        <LI><xsl:text>
        </xsl:text>
          <a href="" TARGET="_top">
            <xsl:attribute name="onClick">
              <xsl:value-of select="onClick"/></xsl:attribute>
            <font class="menuFont">
              <xsl:value-of select="title"/>
            </font>
          </a>
        </LI>
      </xsl:when>
      <xsl:otherwise>
        <LI><xsl:text>
        </xsl:text>
          <font class="disabledMenuFont">
            <xsl:value-of select="title"/>
          </font>
        </LI>
      </xsl:otherwise>
    </xsl:choose>

  </xsl:template>
  <!-- =============================== SUBMENU TEMPLATE - end ========================== -->

</xsl:stylesheet>


