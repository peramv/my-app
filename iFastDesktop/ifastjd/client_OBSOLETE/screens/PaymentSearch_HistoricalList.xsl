<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method = "xml" omit-xml-declaration = "yes" />

  <xsl:template match="/">
    <javascript>

      <xsl:choose>
        <xsl:when test="not(//HistoricalInformation/HistoricalInfo)">
          hideLoadingDisplay();
          _historicalList.deleteAllRows();
        </xsl:when>

        <xsl:otherwise>
          var newRow = null;
          var newCell = null;
          
          _historicalList.deleteAllRows();
          
          currentHistoricalStart = Number(<xsl:value-of select="//RecordRange/rangeStart"/>);
          currentHistoricalEnd = Number(<xsl:value-of select="//RecordRange/rangeEnd"/>);
          
          if (currentHistoricalStart != 1)
            document.getElementById("prevHistoricalButton").disabled = false;
          else 
          document.getElementById("prevHistoricalButton").disabled = true;
          
          if ("no" == "<xsl:value-of select="//RecordRange/moreRecordsExist"/>")
            document.getElementById("nextHistoricalButton").disabled = true;
          else 
            document.getElementById("nextHistoricalButton").disabled = false;
          
          <xsl:for-each select="//HistoricalInformation/HistoricalInfo">            
            
            newRow = document.createElement("tr");                      
            
            <!-- Field Label -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="fldLbl"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Previous Value -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="prevDisp"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- New Value -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="newDisp"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Modification Date -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="modDt"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Modification Time -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="modTime"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            <!-- Who Modified? -->
            newCell = document.createElement("td");
            newCell.className = "grid";
            newCell.innerHTML = '<xsl:value-of select="modUsr"/><xsl:text>&#xa0;</xsl:text>';
            newRow.appendChild(newCell);
            
            document.getElementById("historicalTable").firstChild.appendChild(newRow);
            
          </xsl:for-each>
          
          <xsl:if test="//HistoricalInformation/HistoricalInfo">
            hideLoadingDisplay();
            //highlight(_historicalList.getRow(1));            
          </xsl:if>
          
          
          
        </xsl:otherwise>
      </xsl:choose>

    </javascript>
  </xsl:template>

</xsl:stylesheet>