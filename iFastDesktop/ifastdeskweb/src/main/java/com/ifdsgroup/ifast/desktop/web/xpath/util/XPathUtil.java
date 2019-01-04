package com.ifdsgroup.ifast.desktop.web.xpath.util;

import java.io.IOException;
import java.io.StringReader;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.List;

import javax.xml.namespace.QName;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import com.ifdsgroup.ifast.desktop.web.exception.DesktopWebSystemException;

public class XPathUtil {

    private static final Logger LOG = LogManager.getLogger(XPathUtil.class);

    private XPathUtil() {
    }

    public static String nodeToString(Node node) {
        StringWriter sw = new StringWriter();
        try {
            Transformer t = TransformerFactory.newInstance().newTransformer();
            t.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
            t.transform(new DOMSource(node), new StreamResult(sw));
        } catch (TransformerException te) {
            LOG.debug(te.getMessage(), te);
            throw new DesktopWebSystemException(te.getMessage(), te.getCause());
        }
        return sw.toString();
    }

    public static Document buildDocument(String xml) {

        try {
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            return db.parse(new InputSource(new StringReader(xml)));
        } catch (ParserConfigurationException pce) {
            LOG.debug(pce.getMessage(), pce);
            throw new DesktopWebSystemException(pce.getMessage(), pce.getCause());
        } catch (IOException ioe) {
            LOG.debug(ioe.getMessage(), ioe);
            throw new DesktopWebSystemException("IO Exception", ioe.getCause());
        } catch (SAXException se) {
            LOG.debug(se.getMessage(), se);
            throw new DesktopWebSystemException(se.getMessage(), se.getCause());
        }

    }

    public static Element getDomElement(String xml) {
        Document document = buildDocument(xml);
        return document.getDocumentElement();
    }

    public static XPath buildXPath() {

        XPathFactory xpf = XPathFactory.newInstance();
        return xpf.newXPath();

    }

    public static String evaluateXPath(XPath xpath, String expression, Element element) {
        try {
            return xpath.evaluate(expression, element);
        } catch (XPathExpressionException xpe) {
            LOG.debug(xpe.getMessage(), xpe);
            throw new DesktopWebSystemException(xpe.getMessage(), xpe.getCause());
        }

    }

    public static Object evaluateXPath(XPathExpression expression, Document document, QName returnType) {
        try {
            return expression.evaluate(document, returnType);
        } catch (XPathExpressionException xpe) {
            LOG.debug(xpe.getMessage(), xpe);
            throw new DesktopWebSystemException(xpe.getMessage(), xpe.getCause());
        }

    }

    public static XPathExpression compile(XPath xpath, String expression) {
        try {
            return xpath.compile(expression);
        } catch (XPathExpressionException xpe) {
            LOG.debug(xpe.getMessage(), xpe);
            throw new DesktopWebSystemException(xpe.getMessage(), xpe.getCause());
        }
    }

    /**
     * Converts a given NodeList into an ArrayList that contains the text
     * context of each node
     * 
     * @param nodeList
     * @return An ArrayList of type String that contains the text content of
     *         each Node in the NodeList
     */
    public static List<String> nodeListToArrayList(NodeList nodeList) {
        ArrayList<String> arr = new ArrayList<String>();

        for (int i = 0; i < nodeList.getLength(); i++) {
            arr.add(nodeList.item(i).getTextContent());
        }

        return arr;
    }

    /**
     * Generates a String representation of an xml block based on the parameters
     * 
     * @param tagName
     * @param value
     * @return A String representation of an xml block of 'value' wrapped in
     *         'tagName' tags
     */
    public static String makeNode(String tagName, String value) {
        StringBuilder sb = new StringBuilder();
        sb.append("<").append(tagName).append(">");
        sb.append(value);
        sb.append("</").append(tagName).append(">");
        return sb.toString();
    }
    
    /**
     * Business method for evaluating the XML to get total count of nodes
     * present with the given nodename
     * 
     * @param nodeName
     * @param documentElement
     * @return A total count of nodes present with the given nodeName
     */
    public static int getAttributeNodeCount(String nodeName, String attributeName, Element documentElement, XPath xp) {
        return Integer.parseInt(evaluateXPath(xp, "count(/" + nodeName + "/@" + attributeName + ")", documentElement));
    }

}