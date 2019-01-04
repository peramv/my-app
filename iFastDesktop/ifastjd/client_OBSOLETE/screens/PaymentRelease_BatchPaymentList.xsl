<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:template match="/">
    <javascript>

      <xsl:choose>
        <xsl:when test="not(//ConsolidatedPayments/ConsolidatedPaymentDetail)">
          _batchDetailsList.deleteAllRows();
          hideLoadingDisplay();
        </xsl:when>

        <xsl:otherwise>
          
          var batchDetailsTable = document.getElementById("batchDetailsTable");
          var newRow = null;
          var newCell = null;
          
          currentBatchDetailStart = Number(<xsl:value-of select="//RecordRange/rangeStart"/>);
          currentBatchDetailEnd = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>);                   
          
          _batchDetailsList.deleteAllRows();
          <xsl:for-each select="//ConsolidatedPayments/ConsolidatedPaymentDetail">

            newRow = document.createElement("tr");


            
            <!-- Payment ID -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="pymtId"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Consolidated Indicator -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="consolInd"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
    
            <!-- Currency -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="curr"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
          
            <!-- Amount -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="payAmt"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            batchDetailsTable.firstChild.appendChild(newRow);

          </xsl:for-each>
          
          if (currentBatchDetailStart != 1)
            document.getElementById("btnPrevBatchDetails").disabled = false;
          else 
          document.getElementById("btnPrevBatchDetails").disabled = true;
          
          if (currentBatchDetailEnd == '<xsl:value-of select="//ConsolidatedPayments/totRecCnt"/>')
            document.getElementById("btnNextBatchDetails").disabled = true;
          else 
            document.getElementById("btnNextBatchDetails").disabled = false;
          
          if (currentBatchDetailStart != 0)                       
          document.getElementById("batchDetailCounterDiv").innerHTML = currentBatchDetailStart + " - " + currentBatchDetailEnd + " of <xsl:value-of select="//ConsolidatedPayments/totRecCnt"/>";
          else  
            document.getElementById("batchDetailCounterDiv").innerHTML = "0 - 0 of 0";
          
          hideLoadingDisplay();
          <xsl:if test="//ConsolidatedPayments/ConsolidatedPaymentDetail">
            highlightRow(_batchDetailsList.getRow(1));
          </xsl:if>


        </xsl:otherwise>
      </xsl:choose>
    </javascript>
  </xsl:template>

</xsl:stylesheet>