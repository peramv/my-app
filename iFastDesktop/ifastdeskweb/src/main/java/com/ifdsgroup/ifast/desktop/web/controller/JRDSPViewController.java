package com.ifdsgroup.ifast.desktop.web.controller;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.EXISTING_CLASS_DATA;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.INITIAL_DATA;

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
import com.ifdsgroup.ifast.desktop.web.service.JRDSPViewCallService;
import com.ifdsgroup.ifast.desktop.web.service.SmartViewCallService;

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
@RequestMapping("/jrdspViewAjaxService")
public class JRDSPViewController {

    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(JRDSPViewController.class);

    /*
     * Reference to SmartViewCallService
     */
    private final JRDSPViewCallService jrdspViewCallService;

    /*
     * Constructor used to inject dependencies
     */
    public JRDSPViewController(JRDSPViewCallService jrdspViewCallService) {
        this.jrdspViewCallService = jrdspViewCallService;
    }

    @RequestMapping(value = "/route1", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public String processRequest(HttpServletRequest servletRequest, @RequestBody String payload,
            @RequestParam(value = "ignoreErrorCode", required = false) String ignoreErrorCode) {

        /*
         * This is a call to service layer for getting the response from back
         * end based on the request payload
         */
        SmartViewPayload response = jrdspViewCallService.process(payload, ignoreErrorCode);

        /*
         * If the cache key is passed as request parameter from the front end
         * layer, the XML from back-end is stored in the HTTP Session object
         */
      /*  String cacheKey = servletRequest.getParameter("cacheKey");
        LOG.debug("The cache key value is : " + cacheKey);
        if (cacheKey != null && (cacheKey.equals(INITIAL_DATA) || cacheKey.equals(EXISTING_CLASS_DATA))) {
            HttpSession session = servletRequest.getSession(true);
            LOG.debug("****************************** THE SESSION IS NEW : " + session.isNew());
            session.setAttribute(cacheKey, response.getData());
        }

        LOG.debug("Smartview Response: " + response.toString());
        return response.toString();*/
    	
    	System.out.println("Route using JRDSP Controller.. ");
    	
    	
    	
    	return "<Response></Response>";
    	
    }
}
