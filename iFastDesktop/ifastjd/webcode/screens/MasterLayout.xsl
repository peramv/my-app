<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:template name="master_layout">
    <xsl:param name="session"/>
    <xsl:param name="noheader" />
    <xsl:param name="additionalTitle"/>
    <xsl:param name="pageTitle"/>
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

          <script src="{$vURL}javascript/grid.js">
           // comment. pls keep
          </script>

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

              <input type="hidden" name="envName"     id="envName"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/envName"/></xsl:attribute></input>
              <input type="hidden" name="dateFormat"  id="dateFormat"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/dateFormat"/></xsl:attribute></input>
              <input type="hidden" name="companyCode" id="companyCode"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/companyCode"/></xsl:attribute></input>
              <input type="hidden" name="ruserId"     id="ruserId"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/ruserId"/></xsl:attribute></input>
              <input type="hidden" name="sessionId"   id="envName"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/sessionId"/></xsl:attribute></input>
              <input type="hidden" name="bgColor"     id="bgColor"><xsl:attribute name="value"><xsl:value-of select="//FormInformation/bgcolor"/></xsl:attribute></input>

              <input type="hidden" id="fldJobname" name="jobname" value=""/>
              <input type="hidden" id="cjobname"   name="cjobname" value=""/>

              <xsl:call-template name="form_callback" />

            </form>

            <xsl:call-template name="page_callback"/>

          </div>

          <br/>

        </body>
      </html>
    </Screen>

  </xsl:template>

  <!-- ============================= COMMON JS TEMPLATE - start  ======================== -->
  <xsl:template name="common_js">

    <link rel="stylesheet" type="text/css" href="{$vURL}css/grey.css"/>
    <link rel="stylesheet" type="text/css" href="{$vURL}css/ifd.css"/>
    <link rel="shortcut icon" href="{$vURL}images/favicon.ico" type="image/x-icon" />
    <script src="{$vURL}behaviors/tba.js">
      // comment. pls keep
    </script>
    <script language="javascript">
      var _servletPath = '<xsl:value-of select="$vServletPath"/>';
      var _cz = '<xsl:value-of select="$vCZ"/>';
    </script>
    <script src="{$vURL}javascript/General_Base.js">
      // comment. pls keep
    </script>

    <script language="javascript">

      //TODO: add description - called when a page is loading???
      function preload()
      {
        if( this.loading )
        {
          loading();
        }
      }

      // make div visible
      function makeVisible( divName )
      {
        if ( document.getElementById( divName ) )
        {
          document.getElementById( divName ).style.visibility = 'visible';
        }
      }

      function makeInvisible( divName )
      {
        if ( document.getElementById( divName ) )
        {
          document.getElementById( divName ).style.visibility = 'hidden';
        }
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

</xsl:stylesheet>


