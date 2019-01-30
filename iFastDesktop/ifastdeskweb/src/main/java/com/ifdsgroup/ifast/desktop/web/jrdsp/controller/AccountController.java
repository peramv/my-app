package com.ifdsgroup.ifast.desktop.web.jrdsp.controller;

import javax.servlet.http.HttpServletRequest;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountResponse;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
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
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.AccountService;

@RestController
@RequestMapping("/accountService")
public class AccountController {

    /*
     * Logger to log any errors/issues in the log file
     */
    private static final Logger LOG = LogManager.getLogger(AccountController.class);

    /*
     * Reference to SmartViewCallService
     */
    private final AccountService accountService;

    /*
     * Constructor used to inject dependencies
     */
    public AccountController(AccountService accountService) {
        this.accountService = accountService;
    }


    @RequestMapping(value = "/update/{accountNum}", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity processRequest(@PathVariable("accountNum") String accountNum,HttpServletRequest servletRequest,  @RequestParam("ruserId") String userId,
    		@RequestBody AccountUpdateRequest accountUpdateRequest,
            @RequestParam(value = "ignoreErrorCode", required = false) String ignoreErrorCode) {
        /*
         * This is a call to service layer for getting the response from back
         * end based on the request payload
         */
    	BaseResponse response = accountService.updateAccountDetails(accountNum,accountUpdateRequest,userId,ignoreErrorCode);
        
    	if(!(response instanceof AccountResponse))
        {
     	 
     	   return ResponseEntity.status(response.getStatusCodeValue()).body(response);
        }
        
        
        return  ResponseEntity.ok().body(response);
    }
    
    
    @RequestMapping(value = "/details/{accountNum}", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity getAccountDetails(@PathVariable("accountNum") String accountNum, HttpServletRequest servletRequest,
                                             @RequestParam(value = "ignoreErrorCode", required = false) String ignoreErrorCode) {
        /*
         * This is a call to service layer for getting the response from back
         * end based on the request payload
         */
    	BaseResponse accountResponse = accountService.getAccountDetails(accountNum);
       
       if(!(accountResponse instanceof AccountResponse))
       {
    	 
    	   return ResponseEntity.status(accountResponse.getStatusCodeValue()).body(accountResponse);
       }
       
       BaseResponse entityResponse = accountService.getEntityDetails(accountNum);
       
       if(!(entityResponse instanceof AccountResponse))
       {
    	 
    	   return ResponseEntity.status(entityResponse.getStatusCodeValue()).body(entityResponse);
       }
       
       ((AccountResponse) accountResponse).setEntityInfo(((AccountResponse) entityResponse).getEntityInfo());
       
       return ResponseEntity.ok().body(accountResponse);
    }
    
	
	// Temp method to load the default values for the page.
	
	@RequestMapping(value = "/getConfig", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getConfigValue() {
		return "<RDSPDropDownResponse>"
				+ "<List listName=\"booleanList\">"
				+ "<Element><code>Yes</code><value>Yes</value></Element>"
				+ "<Element><code>No</code><value>No</value></Element>"
				+ "</List>"
				+ "<List listName=\"electionTypeList\">"
				+ "<Element><code>1</code><value>DTC Election</value></Element>"
				+ "<Element><code>2</code><value>SDSP Election</value></Element>"
				+ "<Element><code>3</code><value>Specified Year</value></Element>"
				+ "<Element><code>4</code><value>DTC Eligible</value></Element>"
				+ "<Element><code>5</code><value>DTC Ineligible</value></Element>"
				+ "<Element><code>6</code><value>DTC Undetermined</value></Element>"
				+ "</List>"
				+ "<List listName=\"electionTypeFilterList\">"
				+ "<Element><code>All</code><value>All</value></Element>"
				+ "<Element><code>1</code><value>DTC Election</value></Element>"
				+ "<Element><code>2</code><value>SDSP Election</value></Element>"
				+ "<Element><code>3</code><value>Specified Year</value></Element>"
				+ "<Element><code>4</code><value>DTC Eligible</value></Element>"
				+ "<Element><code>5</code><value>DTC Ineligible</value></Element>"
				+ "<Element><code>6</code><value>DTC Undetermined</value></Element>"
				+ "</List>"
				+ "</RDSPDropDownResponse>";
	}
	
	@RequestMapping(value = "/getContractRegistrationStatusDescription", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
	public String getContractRegistrationStatusDescriptoin() {
		return "<ContractRegistrationStatusDescription>\n" + 
				"	<List listName=\"statusDescription\">\n" + 
				"		<Element><code>01</code><value>Pending</value></Element>\n" +	
				"		<Element><code>02</code><value>Registration Confirmed</value></Element>\n" +
				"		<Element><code>03</code><value>De-Registered</value></Element>\n" +	
				"		<Element><code>04</code><value>Closed</value></Element>\n" +	
				"		<Element><code>05</code><value>Nullified</value></Element>\n" +
				"		<Element><code>99</code><value>Rejected</value></Element>\n" +
				"	</List>\n" + 
				"</ContractRegistrationStatusDescription>";
	}
}
