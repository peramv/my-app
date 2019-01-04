<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />
  
  <xsl:template match="/">
    <javascript>
      
      //var repList = document.getElementById('cmbSalesRep');
      //repList.deleteAllRows();
      
      //var comboboxXML = "";
      //<xsl:for-each select="//List[@listName='SlsRep']/Element">
        //comboboxXML += createXMLElement("combobox", createXMLElement("display", "<xsl:value-of select="value"/>") + createXMLElement("formfield","<xsl:value-of select="code"/>"));
        
      //</xsl:for-each>
      //document.getElementById("cmbSalesRep").addRows(createXMLElement("newdatatset", comboboxXML));
      //document.getElementById("cmbSalesRep").selectedIndex = 0;
    
      
      var repList = document.getElementById('cmbSalesRep');
      repList.innerHTML="";
      
      <xsl:for-each select="//List[@listName='SlsRep']/Element">
        
        var newOption = document.createElement('option');
        newOption.value = '<xsl:value-of select="value"/>';
        newOption.innerHTML = '<xsl:value-of select="value"/>';
        repList.appendChild(newOption);
        
      </xsl:for-each> 

    
    </javascript> 
  </xsl:template>
  
</xsl:stylesheet>