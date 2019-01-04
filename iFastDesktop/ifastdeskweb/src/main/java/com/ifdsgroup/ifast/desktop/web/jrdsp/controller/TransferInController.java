package com.ifdsgroup.ifast.desktop.web.jrdsp.controller;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.TransferUpdateRequest;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Transfers;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.TransferInService;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletRequest;

@RestController
@RequestMapping("/transfers")
public class TransferInController {
    private TransferInService transferInService;
    
    public TransferInController(TransferInService transferInService) {
        this.transferInService = transferInService;
    }
    
    @RequestMapping(value = "/transaction/{accountNum}/{transactionId}/transfer", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity<Transfers> getTransfersDetails(@PathVariable("accountNum") String accountNum,
                                              @PathVariable("transactionId") String transactionId,
                                              HttpServletRequest servletRequest,
                                              @RequestParam(value = "ignoreErrorCode", required = false) String ignoreErrorCode) {
        /*
         * This is a call to service layer for getting the response from back
         * end based on the request payload
         */
        Transfers transfers = transferInService.getTransferInDetails(accountNum, transactionId);
        return ResponseEntity.ok(transfers);
    }
    
    @RequestMapping(value = "/update/transaction/{accountNum}/{transactionId}/transfer", method = RequestMethod.POST, produces = MediaType.TEXT_XML_VALUE, consumes = MediaType.TEXT_XML_VALUE)
    public ResponseEntity<Transfers> putTransfersDetails(@PathVariable("accountNum") String accountNum,
    		@PathVariable("transactionId") String transactionId,
    		HttpServletRequest servletRequest, @RequestBody TransferUpdateRequest transferUpdateRequest,
            @RequestParam(value = "ignoreErrorCode", required = false) String ignoreErrorCode) {
    	
    	Transfers transfers = transferInService.updateTransferInDetails(accountNum,transactionId,transferUpdateRequest,ignoreErrorCode);
        return ResponseEntity.ok(transfers);
    }
    
}
