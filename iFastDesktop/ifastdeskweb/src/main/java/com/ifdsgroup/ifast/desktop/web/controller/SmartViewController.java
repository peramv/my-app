package com.ifdsgroup.ifast.desktop.web.controller;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.EXISTING_CLASS_DATA;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.INITIAL_DATA;

import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.ifdsgroup.ifast.desktop.web.dto.SmartViewPayload;
import com.ifdsgroup.ifast.desktop.web.service.SmartViewCallService;
import com.ifdsgroup.ifast.desktop.web.xpath.util.CommonUtil;

/**
 *
 * This class is the landing controller for all the requests having jobname as
 * 'SmartViewAjax' It is composed of SmartViewCallService to call the back-end
 * API's. It is a Spring RESTFul controller
 *
 * @author if993762
 *
 */
@RestController
public class SmartViewController {

    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(SmartViewController.class);

    /*
     * Reference to SmartViewCallService
     */
    private final SmartViewCallService smartViewCallService;

    /*
     * Constructor used to inject dependencies
     */
    public SmartViewController(SmartViewCallService smartViewCallService) {
        this.smartViewCallService = smartViewCallService;
    }

    @RequestMapping(value = "/smartViewAjaxService", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public String processRequest(HttpServletRequest servletRequest, @RequestBody String payload,
            @RequestParam(value = "ignoreErrorCode", required = false) String ignoreErrorCode) {

    	LOG.debug("SmartViewController : Request payload : "+payload);
    	
    	LOG.debug("SmartViewController : Request Header : "+ CommonUtil.getHeaderInfo(servletRequest));

    	
        /*
         * This is a call to service layer for getting the response from back
         * end based on the request payload
         */
        SmartViewPayload response = smartViewCallService.process(payload, ignoreErrorCode);

        /*
         * If the cache key is passed as request parameter from the front end
         * layer, the XML from back-end is stored in the HTTP Session object
         */
        String cacheKey = servletRequest.getParameter("cacheKey");
        LOG.debug("The cache key value is : " + cacheKey);
        if (cacheKey != null && (cacheKey.equals(INITIAL_DATA) || cacheKey.equals(EXISTING_CLASS_DATA))) {
            HttpSession session = servletRequest.getSession(true);
            LOG.debug("****************************** THE SESSION IS NEW : " + session.isNew());
            session.setAttribute(cacheKey, response.getData());
        }

        LOG.debug("Smartview Response: " + response.toString());
        return response.toString();
    }
}
