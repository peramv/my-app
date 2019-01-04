<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />
  
  <xsl:template match="/">
    <javascript>
      
      <xsl:if test="//RecordRange/moreRecordsExist='yes'">
        document.getElementById("recordStart").value = '<xsl:value-of select="//RecordRange/rangeStartForNext"/>';    
      </xsl:if> 
      <xsl:if test="//RecordRange/moreRecordsExist='no'">
        document.getElementById("recordStart").value = '<xsl:value-of select="//RecordRange/rangeStartForNext"/>'; 
      </xsl:if>        
      
      var paymentList = document.getElementById("paymentList");
      
      var newRow = null;
      var newCell = null;
      
      _paymentList.deleteAllRows();     
      <xsl:for-each select="//PayReconTxnPayList/PayReconPayDetails">
        
        newRow = document.createElement("tr");
        
        <!-- Broker -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="broker"/><xsl:text>&#xa0;</xsl:text>';
        newRow.appendChild(newCell);
        
        <!-- Amount -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="amt"/><xsl:text>&#xa0;</xsl:text>';
        newRow.appendChild(newCell);
        
        <!-- Fund -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="fund"/><xsl:text>&#xa0;</xsl:text>';
        newRow.appendChild(newCell);
        
        <!-- Class -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="class"/><xsl:text>&#xa0;</xsl:text>';
        newRow.appendChild(newCell);
     
        paymentList.firstChild.appendChild(newRow);
        
      </xsl:for-each>
      <xsl:if test ="//PayReconTxnPayList/PayReconPayDetails">
        highlightRow(_paymentList.getRow(1));
      </xsl:if>
      
    </javascript> 
  </xsl:template>
  
</xsl:stylesheet>