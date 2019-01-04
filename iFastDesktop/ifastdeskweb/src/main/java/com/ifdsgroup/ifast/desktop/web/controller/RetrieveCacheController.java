package com.ifdsgroup.ifast.desktop.web.controller;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.RETRIEVE_CACHE_RESPONSE_HEADER;

import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import com.ifdsgroup.ifast.desktop.web.service.CacheService;
import com.ifdsgroup.ifast.desktop.web.xpath.util.CommonUtil;
import com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil;

/**
 * 
 * This class is the landing controller for all the requests having jobname as
 * 'RetrieveCache' It uses http session object to retrieve data within the
 * session
 * 
 * @author if993762
 *
 */
@RestController
public class RetrieveCacheController {
    
    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(RetrieveCacheController.class);

    /*
     * Reference to CacheCallService
     */
    private final CacheService cacheService;
    
    /*
     * Constructor used to inject dependencies
     */
    public RetrieveCacheController(CacheService cacheService) {
        this.cacheService = cacheService;
    }

    @RequestMapping(value = "/retrieveCache", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public String processRequest(HttpServletRequest servletRequest, @RequestBody String payload) {
        
    	LOG.debug("RetrieveCacheController : Request payload : "+payload);
    	
    	LOG.debug("RetrieveCacheController : Request Header : "+ CommonUtil.getHeaderInfo(servletRequest));

    	
        /*
         * Retrieve the session from the request
         */
        HttpSession session = servletRequest.getSession(true);
        
        /*
         * Creating a string builder that will store the body of the response
         */
        StringBuilder cacheResponseBody = new StringBuilder();
        
        /*
         * Sends the payload xml to the cacheCallService to be processed
         * into a list that contains all the the names of session attributes
         * that need to be retrieved. This list is then used to build up the 
         * body of the xml response
         */
        cacheService.getCacheKeyNodeNames(payload).forEach(tagName -> cacheResponseBody.append(XPathUtil.makeNode(tagName, (String) session.getAttribute(tagName))));
        
        /*
         * Wraps the response body xml in retrieve cache tags
         * so the response can be interpreted by the client
         */
        String response = XPathUtil.makeNode(RETRIEVE_CACHE_RESPONSE_HEADER, cacheResponseBody.toString());

        LOG.debug("THE RESPONSE FROM CACHE : " + response);

        return response;

    }
}