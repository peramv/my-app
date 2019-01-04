package com.ifdsgroup.ifast.desktop.web.service;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.KEY;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.TO_BE_CACHED_ATTRIBUTE;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.TO_BE_CACHED_HEADER;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildDocument;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildXPath;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.compile;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.evaluateXPath;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.nodeListToArrayList;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.nodeToString;

import java.util.List;

import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;

import org.springframework.stereotype.Service;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

/**
 * This class is the business layer for the UpdateCache and RetrieveCache
 * controllers. It handles all XPath and DOM manipulation for these controllers
 * 
 * @author if993883
 *
 */
@Service
public class CacheService {

    /**
     * Retrieves the key name of an element at the given index
     * 
     * @param index
     * @param xp
     * @param element
     * @return The name of the key in the form of a String
     */
    public String getXMLCacheKey(int index, XPath xp, Element element) {
        return evaluateXPath(xp, getXpathIndex(index) + "/@" + TO_BE_CACHED_ATTRIBUTE, element);
    }

    /**
     * Retrieves the value of the document at the given index
     * 
     * @param index
     * @param xp
     * @param document
     * @return The value of the document at the given index
     */
    public String getXMLCacheValue(int index, XPath xp, Document document) {
        return nodeToString(
                (Node) evaluateXPath(compile(xp, getXpathIndex(index) + "/*"), document, XPathConstants.NODE));
    }

    /**
     * Business method for processing the request xml for the
     * RetrieveCacheController. Executes all necessary XPath and DOM
     * manipulation required to retrieve the cache.
     * 
     * @param requestXml
     * @return A list that contains all of the session attributes that need to
     *         be retrieved from cache
     */
    public List<String> getCacheKeyNodeNames(String xml) {
        return nodeListToArrayList((NodeList) evaluateXPath(compile(buildXPath(), "//" + KEY), buildDocument(xml),
                XPathConstants.NODESET));
    }

    private static String getXpathIndex(int index) {
        return TO_BE_CACHED_HEADER + "[" + index + "]";
    }

}
