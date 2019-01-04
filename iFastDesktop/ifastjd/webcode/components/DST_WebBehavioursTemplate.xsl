<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml" omit-xml-declaration="yes"/>

    <xsl:template name="DST_WebBehavioursTmpl">
        
        <!--link rel="stylesheet" href="{$vURL}behaviors/ta2000.css" type="text/css"/-->
        
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
</xsl:stylesheet>
