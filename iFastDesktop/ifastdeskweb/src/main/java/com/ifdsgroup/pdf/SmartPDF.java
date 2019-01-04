package com.ifdsgroup.pdf;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.NumberFormat;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.xml.soap.Node;
import javax.xml.transform.Source;
import javax.xml.transform.TransformerException;
import javax.xml.transform.stream.StreamSource;

import org.dom4j.Attribute;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

import com.ifdsgroup.ifast.desktop.web.service.SmartPDFService;

public class SmartPDF {
    SmartPDFService _pdfbase;
    Document _smartPDFControl;

    private static String BREAKLINE_TAG = "<br/>";
    private static String TRANSLATION_TAG = "TRANSLATION";
    private static String THOUSAND_TAG = "ADDTHOUSANDSEPARATOR";
    private static String CORNERTABLEINDICATOR = "cornerBoxNumber";
    private boolean isFromWebplus = false;

    Map<String, String> paramList;
    Map<String, String> translationList;

    public SmartPDF(SmartPDFService smartPDFService, String xml) {
        this(smartPDFService);
        updateXML(xml);
    }

    public SmartPDF(SmartPDFService smartPDFService) {
        _pdfbase = smartPDFService;
        initialize();
        _smartPDFControl = getDocument(new File(getPDFConfigFile()));
    }

    public SmartPDF(SmartPDFService pdf, InputStream stream) {
        System.out.println("**** TEMP PDFLIB7 SMARTPDF BUILD *********");
        _pdfbase = pdf;
        initialize();
        try {
            SAXReader xmlReader = new SAXReader();
            _smartPDFControl = xmlReader.read(stream);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /* Store all the parameters */
    private void initialize() {
        paramList = new HashMap<String, String>();

        paramList.put("xslTranslationFile", "/SmartPDF.xsl");

        /* Parameters coming from Caller */
        paramList.put("imageDirectory",
                _pdfbase.getImagePath() + (getRightmostchar(_pdfbase.getImagePath() != "/" ? "/" : "")));
        
        paramList.put("resourcesDirectory",
                _pdfbase.getResourcesPath() + (getRightmostchar(_pdfbase.getResourcesPath() != "/" ? "/" : "")));
        
        paramList.put("configDirectory", _pdfbase.getConfigurationPath()
                + (getRightmostchar(_pdfbase.getConfigurationPath() != "/" ? "/" : "")));
        
        paramList.put("formType", _pdfbase.getFormType());
        
        paramList.put("decimalDelimitor", _pdfbase.getDecimalDelimitor());
        
        paramList.put("cluture", _pdfbase.getCulture().substring(0,
                2)); /* take only first 2 characters */
        paramList.put("thousandSeparator", " ");
        getTranslations();
    }

    public void updateXML(String xmlData) {
        if (!_pdfbase.getFormType().equalsIgnoreCase("CR")) {
            xmlData = addTotalsRow(xmlData);
        }

        isFromWebplus = xmlData.contains("<gnTaxFormDtlsResponse>") || xmlData.contains("<RRSPReceipt>") ? true : false;

        xmlData = revertHtmlforAPI(xmlData);
        if (paramList.get("formType").equalsIgnoreCase("T5008")) {
            updateXMLWithResponseDataT5008OrRL18(xmlData, false);
        } else if (paramList.get("formType").equalsIgnoreCase("R18")) {
            updateXMLWithResponseDataT5008OrRL18(xmlData, true);
        } else {
            updateXMLWithResponseData(xmlData);
        }

    }

    /*
     * This revert is for support API which send String by using tagChar.
     * tagChar will be replace in HTML format and sent to front.
     * 
     */
    private static String revertHtmlforAPI(String xmlData) {
        return xmlData.replaceAll("&amp;a", "&a").replaceAll("&amp;l", "&l").replaceAll("&amp;g", "&g")
                .replaceAll("&amp;q", "&q").replaceAll("&", "&#38;");
    }

    private void updateXMLWithResponseData(String responseData) {
        try {
            Document doc = DocumentHelper.parseText(responseData);
            for (Iterator iter = DocumentHelper.createXPath("//control").selectNodes(_smartPDFControl).iterator(); iter
                    .hasNext();) {
                Element element = (Element) iter.next();
                String requiresFormat = element.valueOf("RequiresFormatting");

                if ("image".equalsIgnoreCase(element.valueOf("type").trim())) {
                    element.selectSingleNode("defaultValue").setText(getImageFile(element.valueOf("imageKey")));
                }
                if ("table".equals(element.valueOf("type").trim())) {
                    List rows = doc.selectNodes(element.valueOf("viewMapping"));
                    Element table = element.addElement("table");
                    for (int i = 0; i < rows.size(); i++) {
                        String path = ((Element) rows.get(i)).getUniquePath();
                        List columns = doc.selectNodes(path + "/*");
                        if (i == 0) {
                            Element th = table.addElement("th");
                            for (int j = 0; j < columns.size(); j++) {
                                Element el = (Element) columns.get(j);
                                Element td = th.addElement("td");
                                String contents = getFormattedValue(TRANSLATION_TAG, el.getName());
                                if (contents.contains(BREAKLINE_TAG)) {
                                    Element section;
                                    // forcing string tokenizer to add the last
                                    // tokens in the string even though empty
                                    // (there must be a better way)
                                    String[] tokens = (contents + "<br/>End").split(BREAKLINE_TAG);
                                    for (int t = 0; t < tokens.length - 1; t++) {
                                        section = td.addElement("section");
                                        section.setText(tokens[t]);
                                        if (tokens[t] == null || tokens[t].equals("")) {
                                            section.setText(" ");
                                        }

                                    }
                                } else {
                                    td.setText(getFormattedValue("", contents));
                                }
                                td.addAttribute("key", el.getName());
                            } // for (int j = 0; j < columns.size(); j++)
                        } // if (i == 0)

                        Element tr = table.addElement("tr");
                        for (int j = 0; j < columns.size(); j++) {
                            Element el = (Element) columns.get(j);
                            Element td = tr.addElement("td");
                            Attribute attrib = el.attribute("requiresTranslation");

                            td.addAttribute("key", el.getName());
                            if (attrib != null && attrib.getStringValue().equalsIgnoreCase("y")) {
                                td.setText(getFormattedValue(TRANSLATION_TAG, el.getStringValue()));
                            } else if (THOUSAND_TAG.equalsIgnoreCase(requiresFormat)) {
                                td.setText(getFormattedValue(THOUSAND_TAG, el.getStringValue()));

                            } else {
                                td.setText(getFormattedValue("", el.getStringValue()));
                            }
                        }
                    } // for (int i = 0; i<rows.size(); i++)
                } // if ("table".equals(element.valueOf("type").trim()))
                else {
                    if (!"".equals(element.valueOf("viewMapping"))) {
                        String value = doc.valueOf(element.valueOf("viewMapping"));
                        String description = element.valueOf("description");
                        if ("yes".equals(requiresFormat)) {
                            value = getFormattedValue(description, value);
                        } else if (THOUSAND_TAG.equalsIgnoreCase(requiresFormat)) {

                            value = getFormattedValue((description.contains("_BREAK") ? description : THOUSAND_TAG),
                                    value);
                        }
                        element.selectSingleNode("defaultValue").setText(value);
                    }
                }
            } // for (Iterator iter = DocumentHelper.createXPath("//control")
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void updateXMLWithResponseDataT5008OrRL18(String responseData, boolean isRL18) {
        Element tableElement = null;
        Element imageElement = null;
        Document doc = null;
        boolean isWithTransactions = false;
        try {
            doc = DocumentHelper.parseText(responseData);
            for (Iterator<Element> iter = DocumentHelper.createXPath("//control").selectNodes(_smartPDFControl)
                    .iterator(); iter.hasNext();) {
                Element element = (Element) iter.next();

                if ("image".equalsIgnoreCase(element.valueOf("type").trim())) {
                    element.selectSingleNode("defaultValue").setText(getImageFile(element.valueOf("imageKey")));
                }
                if (element.valueOf("type").trim().equalsIgnoreCase("table")) {
                    tableElement = element;

                } else {

                    if (!"".equals(element.valueOf("viewMapping"))) {
                        String value = doc.valueOf(element.valueOf("viewMapping"));
                        String requiresFormat = element.valueOf("RequiresFormatting");
                        String description = element.valueOf("description");
                        if ("yes".equals(requiresFormat)) {
                            value = getFormattedValue(description, value);
                        }
                        element.selectSingleNode("defaultValue").setText(getFormattedValue("", value));
                    }
                }
            } ///////////////////////////////////// Stop here

        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            isWithTransactions = !isRL18
                    && ((Element) (DocumentHelper.createXPath("//TaxFormDtls").selectNodes(doc).get(0)))
                            .valueOf("withTransAction").equalsIgnoreCase("y");
        } catch (Exception e) {
            e.printStackTrace();
        }
        if (isWithTransactions) {
            addTransactions(doc, tableElement, imageElement);
        } else {
            addTransactionsSummary(doc, tableElement, imageElement);
        }
        addDuplicateCopies(Integer
                .parseInt(((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl)).get(0))
                        .valueOf("numberOfCopies")));

    }

    private void addTransactions(Document doc, Element tableElement, Element imageElement) {
        int pageCount = 1;
        int allowedNoOfTransactionsInPage = 0;
        int noTransactionPrintedOnPage = 0;
        int tableTopPosition = 0;
        int rowWidth = 0;
        int headerWidth = 0;
        int transactionInTable = 0;
        int transactionsSize = 0;
        Element table = null;

        try {
            // 2. Store the legal page control
            Element legalPageNodeControl = getElementFromXML(
                    ((Element) (DocumentHelper.createXPath("//page[2]").selectNodes(_smartPDFControl).get(0))).asXML());
            // 3. Store table control node
            Element tableNodeControl = getElementFromXML(
                    ((Element) (DocumentHelper.createXPath("//columnWidths").selectNodes(_smartPDFControl)).get(0))
                            .getParent().asXML());
            rowWidth = Integer.parseInt(
                    ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl)).get(0))
                            .valueOf("rowWidth"));
            headerWidth = Integer.parseInt(
                    ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl)).get(0))
                            .valueOf("headerWidth"));
            tableTopPosition = Integer.parseInt(tableNodeControl.valueOf("top").replaceAll("px", ""));
            // 4. Store table columns
            List tableColumns = DocumentHelper.createXPath("//columnWidths/*").selectNodes(_smartPDFControl);

            List<Node> fundTables = doc.selectNodes(tableElement.valueOf("viewMapping"));
            for (int fundIdx = 0; fundIdx < fundTables.size(); fundIdx++) {
                allowedNoOfTransactionsInPage = Integer.parseInt(
                        ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl)).get(0))
                                .valueOf(pageCount < 2 ? "noOfTrnInFirstPage" : "noOfTrnInOtherPage"));
                // Add control with table for each TaxFund
                // Do not add just the table header in the current page
                if (noTransactionPrintedOnPage != allowedNoOfTransactionsInPage) {
                    if (fundIdx > 0) {

                        tableTopPosition += rowWidth * transactionInTable + headerWidth;
                        tableElement.getParent().addElement("control").appendContent(tableNodeControl);
                        tableElement = getLastElement("table");
                        tableElement.selectSingleNode("top").setText((tableTopPosition) + "px");

                        transactionInTable = 0;
                    }

                    // Add the table headers
                    table = addTableHeaders(tableElement, tableColumns, tableTopPosition);
                }

                // Add Transactions

                List transactions = ((Element) fundTables.get(fundIdx)).elements();
                transactionsSize = transactions.size();
                for (int transCount = 0; transCount < transactions.size(); transCount++) {
                    // Check if whole table will have to move to next page
                    boolean addNewPage = false;
                    // Contains only 2 transactions, do not print the header and
                    // one transaction, rather add a new page
                    if (transactionsSize == 2 && noTransactionPrintedOnPage == allowedNoOfTransactionsInPage - 2) {
                        addNewPage = true;

                        // only the last transaction will go to next page, so
                        // take at least 2 transaction in the next page
                    } else if (noTransactionPrintedOnPage + 1 == allowedNoOfTransactionsInPage
                            && transactionsSize - transactionInTable == 2) {
                        addNewPage = true;
                        // already expected number of transaction printed in the
                        // page/ add a new one
                    } else if (noTransactionPrintedOnPage == allowedNoOfTransactionsInPage) {
                        addNewPage = true;
                    }
                    if (addNewPage) {
                        pageCount++;

                        noTransactionPrintedOnPage = 0;
                        tableTopPosition = Integer.parseInt(
                                ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl))
                                        .get(0)).valueOf("tablePositionOnOtherPage"));
                        transactionInTable = 0;
                        allowedNoOfTransactionsInPage = Integer.parseInt(
                                ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl))
                                        .get(0)).valueOf(pageCount < 2 ? "noOfTrnInFirstPage" : "noOfTrnInOtherPage"));

                        Document pageDocument = getNewPageDocument();
                        // Add the image
                        ((Element) DocumentHelper.createXPath("//page/section").selectNodes(pageDocument).get(0))
                                .addElement("control").appendContent(imageElement);
                        // Add the table
                        ((Element) DocumentHelper.createXPath("//page/section").selectNodes(pageDocument).get(0))
                                .addElement("control").appendContent(tableNodeControl);
                        // Set default values
                        for (Iterator<Element> iter = DocumentHelper.createXPath("//control").selectNodes(pageDocument)
                                .iterator(); iter.hasNext();) {
                            Element element = (Element) iter.next();

                            if (element.valueOf("type").trim().equalsIgnoreCase("image")) {

                                element.selectSingleNode("defaultValue")
                                        .setText(element.valueOf("defaultValue").replace("_legal", "_other"));

                            }
                            if (element.valueOf("type").trim().equalsIgnoreCase("table")) {

                                element.selectSingleNode("top").setText((tableTopPosition) + "px");
                            }

                        }
                        // Add the new page to the main document
                        _smartPDFControl.getRootElement().addElement("page")
                                .appendContent(pageDocument.getRootElement());
                        _smartPDFControl.getRootElement().addElement("page").appendContent(legalPageNodeControl);
                        tableElement = getLastElement("table");
                        // Add the table headers
                        table = addTableHeaders(tableElement, tableColumns, tableTopPosition);
                    }

                    noTransactionPrintedOnPage++;
                    transactionInTable++;
                    Element transaction = (Element) transactions.get(transCount);
                    Element tr = table.addElement("tr");
                    if (transCount == transactions.size() - 1) {
                        tr.addAttribute("data-font-size-override",
                                ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl))
                                        .get(0)).valueOf("lastTransactionFont"));
                    }
                    List<Element> transItems = transaction.elements();
                    for (int transItemCount = 0; transItemCount < transItems.size(); transItemCount++) {
                        Element el = (Element) transItems.get(transItemCount);
                        Element td = tr.addElement("td");
                        Attribute attrib = el.attribute("requiresTranslation");
                        td.addAttribute("key", el.getName());
                        if (attrib != null && attrib.getStringValue().equalsIgnoreCase("y")) {
                            td.setText(getFormattedValue(TRANSLATION_TAG, el.getStringValue()));
                        } else {
                            td.setText(getFormattedValue(THOUSAND_TAG, el.getStringValue()));
                        }
                    }
                } // for(int
                  // transCount=0;transCount<transactions.size();transCount++)
            } // for(int fundIdx=0;fundIdx<fundTables.size();fundIdx++)

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    private void addTransactionsSummary(Document doc, Element tableElement, Element imageElement) {
        int pageCount = 1;
        int allowedNoOfTransactionsInPage = 0;
        int noTransactionPrintedOnPage = 0;
        int tableTopPosition = 0;
        Element table = null;

        try {
            // 2. Store the legal page control
            Element legalPageNodeControl = getElementFromXML(
                    ((Element) (DocumentHelper.createXPath("//page[2]").selectNodes(_smartPDFControl).get(0))).asXML());
            // 3. Store table control node
            Element tableNodeControl = getElementFromXML(
                    ((Element) (DocumentHelper.createXPath("//columnWidths").selectNodes(_smartPDFControl)).get(0))
                            .getParent().asXML());
            tableTopPosition = Integer.parseInt(tableNodeControl.valueOf("top").replaceAll("px", ""));
            // 4. Store table columns
            List tableColumns = DocumentHelper.createXPath("//columnWidths/*").selectNodes(_smartPDFControl);

            List<Node> fundTables = doc.selectNodes(tableElement.valueOf("viewMapping"));
            for (int fundIdx = 0; fundIdx < fundTables.size(); fundIdx++) {
                allowedNoOfTransactionsInPage = Integer.parseInt(
                        ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl)).get(0))
                                .valueOf(pageCount < 2 ? "noOfTrnInFirstPage" : "noOfTrnInOtherPage"));
                if (fundIdx == 0) {
                    // Add the table headers
                    table = addTableHeaders(tableElement, tableColumns, tableTopPosition);
                }

                // Add Transactions

                List transactions = ((Element) fundTables.get(fundIdx)).elements();
                for (int transCount = 0; transCount < transactions.size(); transCount++) {
                    // Check if whole table will have to move to next page

                    if (noTransactionPrintedOnPage == allowedNoOfTransactionsInPage) {
                        pageCount++;

                        noTransactionPrintedOnPage = 0;
                        tableTopPosition = Integer.parseInt(
                                ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl))
                                        .get(0)).valueOf("tablePositionOnOtherPage"));
                        allowedNoOfTransactionsInPage = Integer.parseInt(
                                ((Element) (DocumentHelper.createXPath("//pageControl").selectNodes(_smartPDFControl))
                                        .get(0)).valueOf(pageCount < 2 ? "noOfTrnInFirstPage" : "noOfTrnInOtherPage"));

                        Document pageDocument = getNewPageDocument();
                        // Add the image
                        ((Element) DocumentHelper.createXPath("//page/section").selectNodes(pageDocument).get(0))
                                .addElement("control").appendContent(imageElement);
                        // Add the table
                        ((Element) DocumentHelper.createXPath("//page/section").selectNodes(pageDocument).get(0))
                                .addElement("control").appendContent(tableNodeControl);
                        // Set default values
                        for (Iterator<Element> iter = DocumentHelper.createXPath("//control").selectNodes(pageDocument)
                                .iterator(); iter.hasNext();) {
                            Element element = (Element) iter.next();
                            if (element.valueOf("type").trim().equalsIgnoreCase("image")) {
                                element.selectSingleNode("defaultValue")
                                        .setText(element.valueOf("defaultValue").replace("_legal", "_other"));
                            }
                            if (element.valueOf("type").trim().equalsIgnoreCase("table")) {
                                element.selectSingleNode("top").setText((tableTopPosition) + "px");
                            }
                        }
                        // Add the new page to the main document
                        _smartPDFControl.getRootElement().addElement("page")
                                .appendContent(pageDocument.getRootElement());
                        _smartPDFControl.getRootElement().addElement("page").appendContent(legalPageNodeControl);
                        tableElement = getLastElement("table");
                        // Add the table headers
                        table = addTableHeaders(tableElement, tableColumns, tableTopPosition);
                    }

                    noTransactionPrintedOnPage++;
                    Element transaction = (Element) transactions.get(transCount);
                    Element tr = table.addElement("tr");

                    List<Element> transItems = transaction.elements();
                    for (int transItemCount = 0; transItemCount < transItems.size(); transItemCount++) {
                        Element el = (Element) transItems.get(transItemCount);
                        Element td = tr.addElement("td");

                        // Get attribute from column table.
                        String reqTransaction = getAttributeColumnValue(tableColumns, el.getName(),
                                "requiresTranslation");

                        Attribute attrib = el.attribute("requiresTranslation");
                        td.addAttribute("key", el.getName());

                        if (attrib != null && attrib.getStringValue().equalsIgnoreCase("y")) {
                            td.setText(getFormattedValue(TRANSLATION_TAG, el.getStringValue()));
                        } else if (reqTransaction != null && reqTransaction.equalsIgnoreCase("y")) {
                            td.setText(getFormattedValue(TRANSLATION_TAG, el.getStringValue()));
                        } else {
                            td.setText(getFormattedValue(THOUSAND_TAG, el.getStringValue()));
                        }
                    }
                } // for(int
                  // transCount=0;transCount<transactions.size();transCount++)
            } // for(int fundIdx=0;fundIdx<fundTables.size();fundIdx++)

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    private String getAttributeColumnValue(List tableColumns, String colName, String attrName) {
        String resultValue = "";
        for (int columnNo = 0; columnNo < tableColumns.size(); columnNo++) {
            if (((Element) tableColumns.get(columnNo)).attributeValue("name").equalsIgnoreCase(colName)) {
                resultValue = ((Element) tableColumns.get(columnNo)).attributeValue(attrName);
                break;
            }

        }
        return resultValue;
    }

    private Element addTableHeaders(Element tableElement, List tableColumns, int tableTopPosition) {
        Element table = tableElement.addElement("table");
        Element th = table.addElement("th");
        for (int columnNo = 0; columnNo < tableColumns.size(); columnNo++) {
            Element td = th.addElement("td");
            String contents = buildCornerTable(
                    getFormattedValue(TRANSLATION_TAG, ((Element) tableColumns.get(columnNo)).attributeValue("name")));

            contents = contents.replaceAll("top_y", tableTopPosition + "px");
            if (contents.contains(BREAKLINE_TAG)) {
                Element section;
                // forcing string tokenizer to add the last tokens in the string
                // even though empty (there must be a better way)
                String[] tokens = (contents + "<br/>End").split(BREAKLINE_TAG);
                for (int t = 0; t < tokens.length - 1; t++) {
                    section = td.addElement("section");
                    section.setText(tokens[t]);
                    if (tokens[t] == null || tokens[t].equals("")) {
                        section.setText(" ");
                    }
                }
            } else {
                td.setText(getFormattedValue("", contents));
            }
            td.addAttribute("key", ((Element) tableColumns.get(columnNo)).attributeValue("name"));
        } // for (int j = 0; j < columns.size(); j++)
        return table;
    }

    private String buildCornerTable(String header) {
        StringBuffer sb = new StringBuffer();
        if (header.contains(CORNERTABLEINDICATOR)) {
            sb.append("<fo:block><fo:block-container><fo:block><fo:table-and-caption>");
            sb.append(
                    "<fo:table top=\"top_y\" left=\"leftPosition\" position=\"relative\" font-family=\"fontName\" font-size=\"fontSize\">");
            sb.append("<fo:table-column column-width=\"columnWidth\"  text-align=\"textAlign\"/>");
            sb.append("<fo:table-header><fo:table-cell>");
            sb.append("<fo:block>cornerBoxNumber</fo:block>");
            sb.append("<fo:block/><fo:block/></fo:table-cell></fo:table-header><fo:table-body/></fo:table>");
            sb.append("</fo:table-and-caption></fo:block></fo:block-container></fo:block>");
            String[] str = header.split(";");
            for (int idx = 0; idx < str.length; idx++) {
                if (str[idx].contains(":")) {
                    String[] keyVal = str[idx].split(":");
                    sb = new StringBuffer(sb.toString().replaceAll(keyVal[0], keyVal[1]));
                } else {
                    sb.append(str[idx]);
                }
            }

            return sb.toString();
        }
        return header;
    }

    private void addDuplicateCopies(int numberOfCopies) {
        List pageNodes = DocumentHelper.createXPath("//page").selectNodes(_smartPDFControl);
        for (int loopCount = 0; loopCount < numberOfCopies - 1; loopCount++) {
            for (int pageCount = 0; pageCount < pageNodes.size(); pageCount++) {
                _smartPDFControl.getRootElement().addElement("page").appendContent((Element) pageNodes.get(pageCount));
            }
        }
    }

    private Element getElementFromXML(String elementXML) {
        Document doc = null;
        try {
            doc = DocumentHelper.parseText(elementXML);
        } catch (DocumentException e) {
            e.printStackTrace();
        }
        return (doc == null ? null : doc.getRootElement());
    }

    private Document getNewPageDocument() {
        Document doc = null;
        StringBuffer sb = new StringBuffer();
        sb.append("<page><pagename>TaxForms</pagename><section-name>xsl-region-body</section-name><section>");
        sb.append("</section></page>");
        try {
            doc = DocumentHelper.parseText(sb.toString());
        } catch (DocumentException e) {
            e.printStackTrace();
        }
        return doc;

    }

    private Element getLastElement(String elementType) {
        Element resultElement = null;
        for (Iterator<Element> iter = DocumentHelper.createXPath("//control").selectNodes(_smartPDFControl)
                .iterator(); iter.hasNext();) {
            Element element = (Element) iter.next();
            if (element.valueOf("type").trim().equalsIgnoreCase(elementType)) {
                resultElement = element;
            }
        }
        return resultElement;
    }

    public StringBuilder getControlXML() {
        return new StringBuilder(_smartPDFControl.asXML());
    }

    /* Generate the pdf byte */
    final public byte[] generate() throws IOException, TransformerException, Exception {
        IFDSPDF pdf = null;
        try {
            pdf = new IFDSPDF(_smartPDFControl.asXML(), getXslSource());
        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }
        return pdf.getByte();
    }

    /* Find the XSL file that is used to Translate */
    private Source getXslSource() {
        return new StreamSource(this.getClass().getResourceAsStream(paramList.get("xslTranslationFile")));
    }

    private String getImageFile(String keyValue) {
        if (keyValue == null) {
            return "";
        } else if (keyValue.equalsIgnoreCase("backgroundImagePage1")) {
            return paramList.get("imageDirectory") + paramList.get("formType") + "_page.jpg";
        } else if (keyValue.equalsIgnoreCase("backgroundImageLegal")) {
            return paramList.get("imageDirectory") + paramList.get("formType") + "_legal.jpg";
        } else if (keyValue.equalsIgnoreCase("backgroundImageTable")) {
            return paramList.get("imageDirectory") + paramList.get("formType") + "_table.jpg";
        }
        return "";
    }

    private String getFormattedValue(String key, String value) {

        if (translationList.get("TF_" + paramList.get("formType") + "_" + value) != null) {
            return translationList.get("TF_" + paramList.get("formType") + "_" + value);
        }

        if (key.equalsIgnoreCase("TRANSLATION"))
            return (value == null ? "" : value);
        else if (key.equalsIgnoreCase("imageKey")) {
            if (value.equalsIgnoreCase("backgroundImagePage1")) {
                return paramList.get("formType") + "_page.jpg";
            }
            if (value.equalsIgnoreCase("backgroundImageLegal")) {
                return paramList.get("formType") + "_legal.jpg";
            }
            if (value.equalsIgnoreCase("backgroundImageTable")) {
                return paramList.get("formType") + "_table.jpg";
            }
        }

        /*
         * break SIN into three EXTRA CODE HAS BEEN ADDED TO HANDLE SIN numbers
         * returned with dashes i.e 123-456-789 as opposed to 123456789
         */
        if (key.equals(paramList.get("formType") + "_SIN_1") && (value.length() == 9 || value.length() == 11)) {
            return value.substring(0, 3);
        } else if (key.equals(paramList.get("formType") + "_SIN_2")) {
            if (value.length() == 9)
                return value.substring(3, 6);
            else if (value.length() == 11)
                return value.substring(4, 7);
        } else if (key.equals(paramList.get("formType") + "_SIN_3")) {
            if (value.length() == 9)
                return value.substring(6, 9);
            if (value.length() == 11)
                return value.substring(8, 11);
        }

        if (key.equals(paramList.get("formType") + "_FORMAT_SIN") && value.length() == 9) {
            return value.substring(0, 3) + "-" + value.substring(3, 6) + "-" + value.substring(6, 9);
        }
        if (key.equals(paramList.get("formType") + "_ADD_ACCT_LABEL")) {
            if (value == null || value.length() == 0)
                return "";
            return translationList.get("TF_" + paramList.get("formType") + "_ACCT_LABEL") + " " + value;
        } else if (key.startsWith(paramList.get("formType") + "_ADD_LABEL")) {
            if (value == null || value.length() == 0)
                return "";

            return translationList.get(
                    "TF_" + paramList.get("formType") + "_" + key.substring(key.indexOf("(") + 1, key.indexOf(")")))
                    + " " + value;
        }

        /* translate status to uppercase */
        if (key.equals("rptCodeD") && value != null && value.length() > 0) {
            return "*" + value.toUpperCase() + "*";
        }

        /* return 00.00 value as empty */
        if (value.matches(
                "^-?\\d+(\\" + (isFromWebplus ? "." : paramList.get("decimalDelimitor").replace("\\", "")) + "\\d+)?$")
                && Double.parseDouble(
                        value.replace((isFromWebplus ? "." : paramList.get("decimalDelimitor")), "")) == 0) {
            return "";
        }

        /* break function - to move into SmartView base. */
        if (key.startsWith(paramList.get("formType") + "_BREAK") && value.length() != 0) {

            String delimitor = key.substring(key.indexOf("(") + 1, key.lastIndexOf(","));
            if (delimitor.equalsIgnoreCase("DECIMAL")) {
            	// value coming from smart view always have decimal point however if in certain scenario
            	// decimal is not expected, the contains check should make sure that the delimiator
            	// we want to use for later split is present in expression (issue identified en - fr conversion of docs)
                delimitor = (isFromWebplus || !value.contains(paramList.get("decimalDelimitor")) ? "\\." : paramList.get("decimalDelimitor"));
            }
            if (delimitor == null || delimitor.equals(".")) {
                delimitor = "\\.";
            }
            String whichItem = key.substring(key.lastIndexOf(",") + 1, key.indexOf(")"));
            int item = 1;
            try {
                item = Integer.parseInt(whichItem);
            } catch (Exception e) {
            }
            ;

            String[] items = value.split(delimitor);

            if (items.length < item - 1) {
                return "";
            } else if (item == 1) {
                return formatForThousandSeparator(items[item - 1]);
            } else
                return items[item - 1];

        }

        /* format for thousand separator */
        if (THOUSAND_TAG.equalsIgnoreCase(key)) {
            value = formatForThousandSeparator(value);
        }

        if (key.equals("Amount")) {
            return "$" + formatForThousandSeparator(value);
        }

        /* YES OR NO CHECK BOX */
        if (key.equals(paramList.get("formType") + "_BOX_YES")) {
            if (value.length() == 3)
                return "X";
            else
                return " ";
        } else if (key.equals(paramList.get("formType") + "_BOX_NO")) {
            if (value.length() == 2)
                return "X";
            else
                return " ";
        }

        /* Split up the Date Format from DDMMYYYY to DD MM and YYYY */
        if ((key.equals(paramList.get("formType") + "_DATE_1")) && (value.length() == 6)) {
            return value.substring(0, 2);
        } else if ((key.equals(paramList.get("formType") + "_DATE_2")) && (value.length() == 6)) {
            return value.substring(2, 4);
        } else if ((key.equals(paramList.get("formType") + "_DATE_3")) && (value.length() == 6)) {
            return value.substring(4, 6);
        }

        return (value == null ? "" : value);
    }

    private String getPDFConfigFile() {
        return paramList.get("configDirectory") + paramList.get("formType") + ".xml";
    }

    private void getTranslations() {
        translationList = new HashMap<String, String>();

        // Load English as base translation
        loadTranslations(paramList.get("resourcesDirectory") + paramList.get("formType") + "_en.xml");

        // Override with specific translation
        if (paramList.get("culture") != null && !paramList.get("culture").equalsIgnoreCase("en")) {
            loadTranslations(paramList.get("resourcesDirectory") + paramList.get("formType") + "_"
                    + paramList.get("culture") + ".xml");
        }
    }

    private void loadTranslations(String docPath) {
        Document doc = getDocument(new File(docPath));

        for (@SuppressWarnings("unchecked")
        Iterator<Element> iter = DocumentHelper.createXPath("//Property/propertyItem").selectNodes(doc).iterator(); iter
                .hasNext();) {
            Element element = (Element) iter.next();
            translationList.put(element.valueOf("key").trim(), element.valueOf("value").trim());
        }
    }

    private Document getDocument(File xmlFile) {
        try {
            SAXReader xmlReader = new SAXReader();
            return xmlReader.read(xmlFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private char getRightmostchar(String inputStr) {
        return inputStr.charAt(inputStr.length() - 1);
    }

    /*
     * This code has been placed here to avoid modification in web/desktop and
     * old iFastWeb callers
     */
    private String addTotalsRow(String xmlData) {
        StringBuilder taxDtl = new StringBuilder(xmlData);
        if (taxDtl.lastIndexOf("</TaxFundDtls>") >= 0) {
            int offset = taxDtl.lastIndexOf("</TaxFundDtls>") + "</TaxFundDtls>".length();
            int offsetContent = taxDtl.lastIndexOf("<TaxFundDtls>") + "<TaxFundDtls>".length();
            taxDtl.insert(offset, "<TotalsRow>" + taxDtl.substring(offsetContent, taxDtl.lastIndexOf("</TaxFundDtls>"))
                    + "</TotalsRow>");
        }
        return taxDtl.toString();
    }

    private String formatForThousandSeparator(String value) {
        /* The form is either coming from webplus or is not a decimal then return as is without formatting */
        if (!isFromWebplus && !value.matches("^[0-9]+([,.][0-9]+)$")) {
            return value;
        }

        value = value.replace(" ", "").replace(",", "");

        String delimiter = paramList.get("decimalDelimitor").replace("\\", "");
        String thousandSeparator = paramList.get("thousandSeparator").replace("\\", "");

        /* Return in case the thousandSeparator is not set or blank */
        if (thousandSeparator.isEmpty()) {
            return value;
        }

        DecimalFormatSymbols symbols = new DecimalFormatSymbols();
        symbols.setDecimalSeparator(delimiter.charAt(0));
        symbols.setGroupingSeparator(thousandSeparator.charAt(0));
        // NumberFormat numberFormat = new DecimalFormat("#,###.###########",
        // symbols); //cannot use as contribution receipt displays .00
        NumberFormat numberFormat = new DecimalFormat("#,###", symbols);

        return numberFormat
                .format(Double.parseDouble((value.indexOf('.') > -1 ? value.substring(0, value.indexOf('.')) : value)))

                + (value.indexOf('.') > -1 ? (delimiter + value.substring(value.indexOf('.') + 1)) : ""); // web
                                                                                                          // plus
                                                                                                          // response
                                                                                                          // is
                                                                                                          // in
                                                                                                          // English
                                                                                                          // always

    }
}
