<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:template match="/">
    <javascript>

      <xsl:choose>
        <xsl:when test="not(//ConsolidatedPayments)">
          _paymentList.deleteAllRows();
          _transactionList.deleteAllRows();
        </xsl:when>

        <xsl:otherwise>
          <xsl:if test="//RecordRange/moreRecordsExist='yes'">
            document.getElementById("recordStart").value = '<xsl:value-of select="//RecordRange/rangeStartForNext"/>';
            document.getElementById("btnGetMoreConsolidatePaymentRecords").disabled = "false";
          </xsl:if>
          <xsl:if test="//RecordRange/moreRecordsExist='no'">
            document.getElementById("recordStart").value = '<xsl:value-of select="//RecordRange/rangeStartForNext"/>';
            document.getElementById("btnGetMoreConsolidatePaymentRecords").disabled = "true";
          </xsl:if>

          var consolidatedPaymentList = document.getElementById("consolidatedPaymentList");
          var newRow = null;
          var newCell = null;

          var forList = document.getElementById('cmbPymtFor');
          forList.innerHTML="";

          _consolidatedList.deleteAllRows();
          <xsl:for-each select="//ConsolidatedPayments/ConsolidatedPaymentDetail">

            newRow = document.createElement("tr");

            newRow.pymtFor = '<xsl:value-of select="pymtFor"/>';

            <!-- Payment ID -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="pymtId"/>';
            newRow.appendChild(newCell);

            <!-- Payment Date -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="tapeDate"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Amount -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="payAmt"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Currency -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="curr"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Consolidated Indicator -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="consolInd"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            consolidatedPaymentList.firstChild.appendChild(newRow);

            var newOption = document.createElement('option');
            newOption.innerHTML = '<xsl:value-of select="pymtFor"/>';
            forList.appendChild(newOption);
          </xsl:for-each>
          <xsl:if test="//ConsolidatedPayments/ConsolidatedPaymentDetail">
            test(_consolidatedList.getRow(1));
          </xsl:if>


        </xsl:otherwise>
      </xsl:choose>
    </javascript>
  </xsl:template>

</xsl:stylesheet>
