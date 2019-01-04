package com.ifdsgroup.ifast.desktop.web.controller;

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

/**
 * 
 * This class is the landing controller for all the requests required to delete
 * any session based information. It uses http session object to remove data
 * within the session
 * 
 * @author if993762
 *
 */
@RestController
public class DeleteCacheController {

    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(DeleteCacheController.class);

    /*
     * Reference to CacheCallService
     */
    private final CacheService cacheService;

    /*
     * Constructor used to inject dependencies
     */
    public DeleteCacheController(CacheService cacheService) {
        this.cacheService = cacheService;
    }

    @RequestMapping(value = "/deleteCache", method = RequestMethod.POST, consumes = MediaType.TEXT_XML_VALUE)
    public void processRequest(HttpServletRequest servletRequest, @RequestBody String payload) {

    	LOG.debug("DeleteCacheController : Request payload : "+payload);
    	LOG.debug("DeleteCacheController : Request Header : "+ CommonUtil.getHeaderInfo(servletRequest));
     	
        /*
         * Retrieve the session from the request
         */
        HttpSession session = servletRequest.getSession(true);
        LOG.debug("****************************** THE SESSION IS NEW : " + session.isNew());

        /*
         * Sends the payload xml to cacheService to be processed into a list of
         * node names which are then deleted from session
         */
        cacheService.getCacheKeyNodeNames(payload).forEach(key -> session.removeAttribute(key));

    }

}
