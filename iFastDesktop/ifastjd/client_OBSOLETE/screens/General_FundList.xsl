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
      
      var transactionList = document.getElementById("transactionList");
      
      var newRow = null;
      var newCell = null;
      
      <xsl:for-each select="//PayReconTxnPayList/PayReconTxnDetails">
        
        newRow = document.createElement("tr");
        
        <!-- Trans Type -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="transType"/>';
        newRow.appendChild(newCell);
        
        <!-- Broker -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="broker"/>';
        newRow.appendChild(newCell);
        
        <!-- Amount -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="amt"/>';
        newRow.appendChild(newCell);
        
        <!-- Account -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="acct"/>';
        newRow.appendChild(newCell);
        
        <!-- Consolidated Level -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="level"/>';
        newRow.appendChild(newCell);

        <!-- Trans Num -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="transNum"/>';
        newRow.appendChild(newCell);
        
        <!-- Trade Date -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="tradeDt"/>';
        newRow.appendChild(newCell);
        
        <!-- Settlement Date -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="settleDt"/>';
        newRow.appendChild(newCell);
        
        <!-- Fund -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="fund"/>';
        newRow.appendChild(newCell);
        
        <!-- Class -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="class"/>';
        newRow.appendChild(newCell);
        
        transactionList.firstChild.appendChild(newRow);    
      </xsl:for-each>
      <xsl:if test="//PayReconTxnPayList/PayReconTxnDetails">
        highlightRow(_transactionList.getRow(1));
      </xsl:if>
      
    </javascript> 
  </xsl:template>
  
</xsl:stylesheet>