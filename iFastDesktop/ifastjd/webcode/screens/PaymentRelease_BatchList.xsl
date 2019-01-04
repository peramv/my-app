<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:template match="/">
    <javascript>

      <xsl:choose>
        <xsl:when test="not(//PaymentBatches/PymtBatchDetails)">
          _paymentBatchList.deleteAllRows();
          _batchDetailsList.deleteAllRows();
          hideLoadingDisplay();
        </xsl:when>

        <xsl:otherwise>
          
          var newRow = null;
          var newCell = null;
          
          _paymentBatchList.deleteAllRows();

          currentRecordStart = Number(<xsl:value-of select="//RecordRange/rangeStart"/>);
          currentRecordEnd = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>);           

          if (currentRecordStart != 1)
            document.getElementById("btnPrevPayments").disabled = false;
          else 
            document.getElementById("btnPrevPayments").disabled = true;
          
          if (currentRecordEnd == '<xsl:value-of select="//PaymentBatches/total"/>')
            document.getElementById("btnNextPayments").disabled = true;
          else 
            document.getElementById("btnNextPayments").disabled = false;
          
          if (currentRecordStart != 0)             
          {
            document.getElementById("counterDiv").innerHTML = currentRecordStart + " - " + currentRecordEnd + " of <xsl:value-of select="//PaymentBatches/total"/>";            
          }
          else  
            document.getElementById("counterDiv").innerHTML = "0 - 0 of 0";

          currentRecordStart = Number(<xsl:value-of select="//RecordRange/rangeStart"/>);
          currentRecordEnd = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>);
          
          
          <xsl:if test="//PaymentBatches/PymtBatchDetails">
            searchWithResults = "yes";
          </xsl:if>
          
          <xsl:for-each select="//PaymentBatches/PymtBatchDetails">            

            newRow = document.createElement("tr");
            newRow.rowBatchId = "<xsl:value-of select="pymtBatchID"/>";                      
            newRow.rowStatus = "<xsl:value-of select="stat"/>";
            newRow.modDate = "<xsl:value-of select="modDate"/>";
            newRow.procDate = "<xsl:value-of select="procDate"/>";
            newRow.modUser = "<xsl:value-of select="modID"/>";
            newRow.userName = "<xsl:value-of select="userNm"/>";
            
            <!-- Payment For -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col1";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="pymtFor"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Status -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col2";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="stat"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Payment Date -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col3";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="payDate"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Payment File Name -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col4";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="fileNm"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Counter -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col7";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="pymtCntr"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- ACH Processor -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col7";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="achProc"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            document.getElementById("paymentBatchTable").firstChild.appendChild(newRow);
            
          </xsl:for-each>                           
          hideLoadingDisplay();
          <xsl:if test="//PaymentBatches/PymtBatchDetails">
            document.getElementById("btnAdmin").disabled = false;
            clickFn(_paymentBatchList.getRow(1));            
          </xsl:if>
          
        </xsl:otherwise>
      </xsl:choose>

    </javascript>
  </xsl:template>

</xsl:stylesheet>