package com.ifdsgroup.ifast.desktop.web.jrdsp.controller;

import javax.servlet.http.HttpServletRequest;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountResponse;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.ifdsgroup.ifast.desktop.web.dto.SmartViewPayload;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountUpdateRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.BaseResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ConfigGetResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ConfigurationResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.AccountService;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.ConfigurationService;

@RestController
@RequestMapping("/configService")
public class ConfigurationController {

    private static final Logger LOG = LogManager.getLogger(ConfigurationController.class);

    @Autowired
    private ConfigurationService configurationService;

    @RequestMapping(value = "/getConfiguration", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity processRequest(HttpServletRequest servletRequest) {
        /*
         * This is a call to service layer for getting the response from back
         * end based on the request payload
         */
    	BaseResponse response = configurationService.getConfigurationDetails();
        
    	if(!(response instanceof ConfigurationResponse))
        {
     	 
     	   return ResponseEntity.status(response.getStatusCodeValue()).body(response);
        }
        
        
        return  ResponseEntity.ok().body(response);
    }
    
   
}
