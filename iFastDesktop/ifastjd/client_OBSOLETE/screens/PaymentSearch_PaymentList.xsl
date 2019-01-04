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
      

      currentPaymentStart = Number(<xsl:value-of select="//RecordRange/rangeStart"/>);
      currentPaymentEnd = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>);       
      
      if (currentPaymentStart != 1)
        document.getElementById("btnPrevPaymentRecords").disabled = false;
      else 
        document.getElementById("btnPrevPaymentRecords").disabled = true;
      
      if (currentPaymentEnd == '<xsl:value-of select="//PayReconTxnPayList/totRecCnt"/>')
        document.getElementById("btnNextPaymentRecords").disabled = true;
      else 
        document.getElementById("btnNextPaymentRecords").disabled = false;
      
      if (currentPaymentStart != 0)             
      {
      document.getElementById("paymentCounterDiv").innerHTML = currentPaymentStart + " - " + currentPaymentEnd + " of <xsl:value-of select="//PayReconTxnPayList/totRecCnt"/>";            
      }
      else  
        document.getElementById("paymentCounterDiv").innerHTML = "0 - 0 of 0";
      
      
      
      _paymentList.deleteAllRows();     
      <xsl:for-each select="//PayReconTxnPayList/PayReconPayDetails">
        
        newRow = document.createElement("tr");
        
        <!-- Broker -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="broker"/><xsl:text>&#xa0;</xsl:text>';
        newRow.appendChild(newCell);
        
        <!-- Branch -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="branch"/><xsl:text>&#xa0;</xsl:text>';
        newRow.appendChild(newCell);

        <!-- Sales Rep -->
        newCell = document.createElement("td");
        newCell.className = "grid";
        newCell.innerHTML = '<xsl:value-of select="slsRep"/><xsl:text>&#xa0;</xsl:text>';
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
      hideLoadingDisplay();
    </javascript> 
  </xsl:template>
  
</xsl:stylesheet>