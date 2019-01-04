<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />
  
  <xsl:template match="/">
    <javascript>

      var branchList = document.getElementById('cmbBranch');
      branchList.innerHTML="";
      
      <xsl:for-each select="//List[@listName='Branch']/Element">

        var newOption = document.createElement('option');
        newOption.value = '<xsl:value-of select="value"/>';
        newOption.innerHTML = '<xsl:value-of select="value"/>';
        branchList.appendChild(newOption);
        
      </xsl:for-each> 

    </javascript> 
  </xsl:template>
  
</xsl:stylesheet>