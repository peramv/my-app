<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />
  
  <xsl:template match="/">
    <javascript>
      
      <xsl:choose>
        <xsl:when test="not(//PayReconTxnPayList)">
        </xsl:when>
        
        <xsl:otherwise>
          <xsl:if test="//RecordRange/moreRecordsExist='yes'">
            //document.getElementById("recordStart").value = '<xsl:value-of select="//RecordRange/rangeStartForNext"/>';
            //document.getElementById("btnGetMoreTransactionRecords").disabled = "false";           
          </xsl:if> 
          <xsl:if test="//RecordRange/moreRecordsExist='no'">
            //document.getElementById("recordStart").value = '<xsl:value-of select="//RecordRange/rangeStartForNext"/>';
            //document.getElementById("btnGetMoreTransactionRecords").disabled = "true"; 
          </xsl:if>
          
          var transactionList = document.getElementById("transactionList");
          
          var newRow = null;
          var newCell = null;
                    
          currentPaymentStart = Number(<xsl:value-of select="//RecordRange/rangeStart"/>);
          currentPaymentEnd = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>);       
          
          if (currentPaymentStart != 1)
            document.getElementById("btnPrevTransactionRecords").disabled = false;
          else 
            document.getElementById("btnPrevTransactionRecords").disabled = true;
          
          if (currentPaymentEnd == '<xsl:value-of select="//PayReconTxnPayList/totRecCnt"/>')
            document.getElementById("btnNextTransactionRecords").disabled = true;
          else 
            document.getElementById("btnNextTransactionRecords").disabled = false;
          
          if (currentPaymentStart != 0)             
          {
            document.getElementById("transactionCounterDiv").innerHTML = currentPaymentStart + " - " + currentPaymentEnd + " of <xsl:value-of select="//PayReconTxnPayList/totRecCnt"/>";            
          }
          else  
            document.getElementById("transactionCounterDiv").innerHTML = "0 - 0 of 0";
          
          
          
          
          
          _transactionList.deleteAllRows();
          
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
        </xsl:otherwise>
      </xsl:choose>
      hideLoadingDisplay();
      
    </javascript> 
  </xsl:template>
  
</xsl:stylesheet>