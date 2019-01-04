<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:template match="/">
    <javascript>

      <xsl:choose>
        <xsl:when test="not(//ConsolidatedPayments/ConsolidatedPaymentDetail)">
          _consolidatedList.deleteAllRows();
          _paymentList.deleteAllRows();
          _transactionList.deleteAllRows();
          hideLoadingDisplay();
        </xsl:when>

        <xsl:otherwise>

          var consolidatedPaymentList = document.getElementById("consolidatedPaymentList");
          var newRow = null;
          var newCell = null;
          var newDropdown = null;
          var newOption = null;
          var selectedOption = null;
          
          var forList = document.getElementById('cmbPymtFor');
          forList.innerHTML="";
          
          currentSelectedRow = -1;
          _consolidatedList.deleteAllRows();

          currentRecordStart = Number(<xsl:value-of select="//RecordRange/rangeStart"/>);
          currentRecordEnd = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>);
          //recordsPerPage = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>) - Number(<xsl:value-of select="//RecordRange/rangeStart"/>); 
          
          if (currentRecordStart != 1)
            document.getElementById("btnPrevConsPaymentRecords").disabled = false;
          else 
            document.getElementById("btnPrevConsPaymentRecords").disabled = true;
          
          if (currentRecordEnd == <xsl:value-of select="//ConsolidatedPayments/totRecCnt"/>)
            document.getElementById("btnNextConsPaymentRecords").disabled = true;
          else 
            document.getElementById("btnNextConsPaymentRecords").disabled = false;
            
          <xsl:for-each select="//ConsolidatedPayments/ConsolidatedPaymentDetail">            
            _versionList[<xsl:value-of select="position()-1"/>] = <xsl:value-of select="version"/>;
            _vrecid[<xsl:value-of select="position()-1"/>] = <xsl:value-of select="recId"/>;


            newRow = document.createElement("tr");
            newRow.rowPosition = <xsl:value-of select="position()-1"/>;            
            newRow.pymtFor = '<xsl:value-of select="pymtFor"/>';
            
            <!-- Status -->
            if ("<xsl:value-of select="statUpd"/>" == "yes")
            {
              newCell = document.createElement("td");              
              newCell.className = "grid";
              newDropdown = document.createElement("select");
              newDropdown.id = "row<xsl:value-of select="position()-1"/>col1";
              newDropdown.style.width = "100%";
              selectedOption = "<xsl:value-of select="pymtStat"/>";            
              <xsl:for-each select="List[@id='ValidStatuses']/Element">
                newOption = document.createElement("option");
                newOption.value = "<xsl:value-of select="code"/>";              
                newOption.innerHTML = '<xsl:value-of select="value"/>';
                if (selectedOption == newOption.innerHTML)
                  newOption.selected = true;
                newDropdown.appendChild(newOption);
              </xsl:for-each>
              newCell.appendChild (newDropdown);   
              newRow.appendChild(newCell);
            }
            else
            {
              newCell = document.createElement("td");
              newCell.className = "grid";
              newCell.innerHTML = '<xsl:value-of select="pymtStat"/>';
              <xsl:if test="pymtStatMsg">
                  var pymtStatMsg = "<xsl:value-of select="pymtStatMsg"/>";
				  newCell.title = pymtStatMsg;
              </xsl:if>
              
              newRow.appendChild(newCell);
            }
            
            <!-- Payment ID -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col2";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="pymtId"/>';
            newRow.appendChild(newCell);

            <!-- Payment Date -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col3";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="tapeDate"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Consolidated Indicator -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col4";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="consolInd"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Amount -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col5";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="payAmt"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Currency -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col6";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="curr"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            <!-- Batch ID -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col7";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="batchID"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Trans Type -->
            newCell = document.createElement("td");
            newCell.id = "row<xsl:value-of select="position()-1"/>col8";
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="pymtFor"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);

            consolidatedPaymentList.firstChild.appendChild(newRow);

            var newOption = document.createElement('option');
            newOption.innerHTML = '<xsl:value-of select="pymtFor"/>';
            forList.appendChild(newOption);
          </xsl:for-each>
          
          <xsl:if test="//ConsolidatedPayments/ConsolidatedPaymentDetail">
            hideLoadingDisplay();
            onRowClick(_consolidatedList.getRow(1));
            document.getElementById("counterDiv").innerHTML = "<xsl:value-of select="//RecordRange/rangeStart"/> - <xsl:value-of select="//RecordRange/rangeEnd"/> of <xsl:value-of select="//ConsolidatedPayments/totRecCnt"/>";
          </xsl:if>
          
          
          
        </xsl:otherwise>
      </xsl:choose>
      
      <xsl:choose>          
        <xsl:when test='//dtPaymentRecReload1Response/vrfAll="yes"'>
          document.getElementById("verifyAllDiv").style.display = "inline";
        </xsl:when>
        <xsl:otherwise>
          document.getElementById("verifyAllDiv").style.display = "none";
        </xsl:otherwise>
      </xsl:choose>
      
      
      <xsl:choose>          
        <xsl:when test='//dtPaymentRecReload1Response/appvAll="yes"'>
          document.getElementById("approveAllDiv").style.display = "inline";
        </xsl:when>
        <xsl:otherwise>
          document.getElementById("approveAllDiv").style.display = "none";
        </xsl:otherwise>
      </xsl:choose>
      
      
      <xsl:choose>          
        <xsl:when test='//dtPaymentRecReload1Response/stpAll="yes"'>
          document.getElementById("stopAllDiv").style.display = "inline";
        </xsl:when>
        <xsl:otherwise>
          document.getElementById("stopAllDiv").style.display = "none";
        </xsl:otherwise>
      </xsl:choose>
      
      
      <xsl:choose>       
        <xsl:when test='//dtPaymentRecReload1Response/oK="yes"'>
          document.getElementById("btnOK").disabled = false;
        </xsl:when>
        <xsl:otherwise>
          document.getElementById("btnOK").disabled = true;
        </xsl:otherwise>
      </xsl:choose>
      
      <xsl:choose>    
        <xsl:when test='//RecordRange/moreRecordsExist="yes"'>          
          document.getElementById("btnNextConsPaymentRecords").disabled = false;
        </xsl:when>
        <xsl:otherwise>
          document.getElementById("btnNextConsPaymentRecords").disabled = true;
        </xsl:otherwise>
      </xsl:choose>
      
      <xsl:choose>    
        <xsl:when test='//ConsolidatedPayments/ConsolidatedPaymentDetail/statUpd="yes"'>
          document.getElementById("resetRecordButton").disabled = false;
        </xsl:when>      
        <xsl:otherwise>
          document.getElementById("resetRecordButton").disabled = true;    
        </xsl:otherwise>
      </xsl:choose>

    </javascript>
  </xsl:template>

</xsl:stylesheet>