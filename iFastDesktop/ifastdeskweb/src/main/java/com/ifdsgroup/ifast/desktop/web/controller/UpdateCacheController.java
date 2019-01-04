package com.ifdsgroup.ifast.desktop.web.controller;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.TO_BE_CACHED_ATTRIBUTE;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.TO_BE_CACHED_HEADER;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildDocument;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildXPath;

import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import javax.xml.xpath.XPath;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.ifdsgroup.ifast.desktop.web.service.CacheService;
import com.ifdsgroup.ifast.desktop.web.xpath.util.CommonUtil;
import com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil;

/**
 * 
 * This class is the landing controller for all the requests having jobname as
 * 'UpdateCache' It uses http session object to update data within the session
 * 
 * @author if993762
 *
 */
@RestController
public class UpdateCacheController {

    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(UpdateCacheController.class);

    /*
     * Reference to CacheCallService
     */
    private final CacheService cacheService;

    /*
     * Constructor used to inject dependencies
     */
    public UpdateCacheController(CacheService cacheService) {
        this.cacheService = cacheService;
    }

    @RequestMapping(value = "/updateCache", method = RequestMethod.POST, consumes = MediaType.TEXT_XML_VALUE)
    public void processRequest(HttpServletRequest servletRequest, @RequestBody String payload) {

    	LOG.debug("UpdateCacheController : Request payload : "+payload);
    	
    	LOG.debug("UpdateCacheController : Request Header : "+ CommonUtil.getHeaderInfo(servletRequest));

    	
        /*
         * Retrieve the session from the request
         */
        HttpSession session = servletRequest.getSession(true);
        LOG.debug("****************************** THE SESSION IS NEW : " + session.isNew());

        /*
         * Creates the DOM from the request xml
         */
        Document document = buildDocument(payload);
        Element documentElement = document.getDocumentElement();

        /*
         * Creates a new XPath
         */
        XPath xp = buildXPath();

        /*
         * Sends the payload xml to cacheCallService to be processed into a list
         * of key-value pairs which are then set as attributes in the session
         */
        int attributeCount = XPathUtil.getAttributeNodeCount(TO_BE_CACHED_HEADER, TO_BE_CACHED_ATTRIBUTE,
                documentElement, xp);

        for (int i = 1; i < attributeCount + 1; i++) {

            session.setAttribute(cacheService.getXMLCacheKey(i, xp, documentElement),
                    cacheService.getXMLCacheValue(i, xp, document));

        }

    }

}