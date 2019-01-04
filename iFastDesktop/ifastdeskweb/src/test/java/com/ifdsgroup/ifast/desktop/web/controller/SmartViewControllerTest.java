package com.ifdsgroup.ifast.desktop.web.controller;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.EXISTING_CLASS_DATA;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.FAILURE_RESPONSE;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.INITIAL_DATA;
import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.SUCCESS_RESPONSE;
import static org.junit.Assert.assertEquals;
import static org.mockito.BDDMockito.given;
import static org.mockito.Mockito.mock;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.junit.Test;

import com.ifdsgroup.ifast.desktop.web.dto.SmartViewPayload;
import com.ifdsgroup.ifast.desktop.web.service.SmartViewCallService;

public class SmartViewControllerTest {
    
    SmartViewController smartViewController;
    SmartViewCallService smartViewCallService;
    HttpServletRequest request;
    
    private String requestXml = "<request><fundOnlySearchRequest><RequestHeader><apiName>fundOnlySearch</apiName><envName>qaslotx124</envName><companyCode>NCE</companyCode><ruserId>if993762</ruserId><sessionId>Oup8Q1HBnLL/spjkVkZdZN/+vrVY/exu8YleIZEOHAiQrW0JuqWSY6c1EiB/NZCUmqK0h596d7ME97f97ZYU4GKT+9qsoOqIYOoC2AaBJwGulceROGij9pnzllTmMHTB973paf80WNvl1QXmNZgdr7/IVnfGhqXwVN54kv1+I79wuWuG8uhEn4L4QzBXlE1VdaqjwgoXHpV49ze83JSGsN0cV5au8NzTuYZy0XhF5KsoweMfBJAGGbhEQ5e8VZWY7INqjNiaV4OM00Ipv/3itmDt5di2ZtCCd1AoaEN8dN8dzilx8YBugJsyWQ7Gv4uWUF6nEyIEE5ITKuRChN0nQhpgb+DQ9SkAUyTHI1xZv1CnPQ7y57+vEWBcFO/m2RfwiK6XLuRDVg9ofPvo11uLptwCIOmG+zXErtZH+T73ek19nZ2+UF297pzZg28MTw5j39OBpjDlYPqLLZg6KRXxdMw/GYfSgW/0IhgoaZQMHyXejvS/qDwgTbGoE0ASBRDV08Uck0XSVL1cHOnYFytC088/VUjambuwGR5PMTHhIxjeOgAoyG6lA/kkDphu8xv9a801BGebQJLqff0UfmVM0ItQEAeeAcHq7w6kgi9TKw8=</sessionId><dateFormat>mdy</dateFormat><locale>enUS</locale><dataMode>inquire</dataMode><interfaceName>ifds.desktop</interfaceName><language>en</language></RequestHeader><data><searchValue>sentry</searchValue><maxRecords>10</maxRecords><startRecordNum>1</startRecordNum></data></fundOnlySearchRequest></request>";
    private String successResponse = "<RequestStatus><status>Accepted</status><viewModule>/devslots/devslotx67/corfax/smartview/SMS00271.P</viewModule><executionMilliseconds>18</executionMilliseconds></RequestStatus>";
    private String rejectedResponse = "<dtRelFrozenAcctInitResponse><RequestStatus><status>Rejected</status><Errors><Error><errorType>business</errorType><errorCode>754</errorCode><text>Unclaimed property has not been reported for this account.(00754)</text><programmerNote>Unclaimed property has not been reported for this account.(uc00754)</programmerNote><errorSeverity>error</errorSeverity><module>/devslots/devslotx67/corfax/smartview/SMS00255.P</module></Error></Errors><viewModule>/devslots/devslotx67/corfax/smartview/SMS00255.P</viewModule><executionMilliseconds>9</executionMilliseconds></RequestStatus></dtRelFrozenAcctInitResponse>";
    
    public SmartViewControllerTest() {
        this.smartViewCallService = mock(SmartViewCallService.class);
        this.smartViewController = new SmartViewController(smartViewCallService);
        this.request = mock(HttpServletRequest.class);
    }

    @Test
    public void cacheKeyNullTest() {
        given(request.getParameter("cacheKey")).willReturn(null);
        
        SmartViewPayload xmlPayload = new SmartViewPayload("<RequestStatus><status>Accepted</status><viewModule>/devslots/devslotx67/corfax/smartview/SMS00271.P</viewModule><executionMilliseconds>18</executionMilliseconds></RequestStatus>", SUCCESS_RESPONSE, null);
        given(this.smartViewCallService.process(requestXml, null)).willReturn(xmlPayload);
        
        assertEquals(xmlPayload.toString(), smartViewController.processRequest(request, requestXml, null));
    }
    
    @Test
    public void cacheKeyInitialDataTest() {
        given(request.getParameter("cacheKey")).willReturn(INITIAL_DATA);
        given(request.getSession(true)).willReturn(mock(HttpSession.class));
        
        SmartViewPayload xmlPayload = new SmartViewPayload("<RequestStatus><status>Accepted</status><viewModule>/devslots/devslotx67/corfax/smartview/SMS00271.P</viewModule><executionMilliseconds>18</executionMilliseconds></RequestStatus>", SUCCESS_RESPONSE, null);
        given(this.smartViewCallService.process(requestXml, null)).willReturn(xmlPayload);
        
        assertEquals(xmlPayload.toString(), smartViewController.processRequest(request, requestXml, null));
    }
    
    @Test
    public void cacheKeyExistingDataTest() {
        given(request.getParameter("cacheKey")).willReturn(EXISTING_CLASS_DATA);
        given(request.getSession(true)).willReturn(mock(HttpSession.class));
        
        SmartViewPayload xmlPayload = new SmartViewPayload(successResponse, SUCCESS_RESPONSE, null);
        given(this.smartViewCallService.process(requestXml, null)).willReturn(xmlPayload);
        
        assertEquals(xmlPayload.toString(), smartViewController.processRequest(request, requestXml, null));
    }
    
    @Test
    public void failureResponseTest() {
        SmartViewPayload xmlPayload = new SmartViewPayload(rejectedResponse, FAILURE_RESPONSE, null);
        given(this.smartViewCallService.process(requestXml, null)).willReturn(xmlPayload);
        
        assertEquals(xmlPayload.toString(), smartViewController.processRequest(request, requestXml, null));
    }
    
    @Test
    public void wrongFailureResponseTest() {
        SmartViewPayload xmlPayload = new SmartViewPayload("<Test></Test>", "WRONG", null);
        given(this.smartViewCallService.process(requestXml, null)).willReturn(xmlPayload);
        
        assertEquals(xmlPayload.toString(), smartViewController.processRequest(request, requestXml, null));
    }
    
    
    
}
