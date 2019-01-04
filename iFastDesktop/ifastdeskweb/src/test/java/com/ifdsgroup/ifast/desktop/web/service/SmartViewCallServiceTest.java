package com.ifdsgroup.ifast.desktop.web.service;

import static org.junit.Assert.assertEquals;
import static org.mockito.BDDMockito.given;

import org.junit.Test;
import org.mockito.Mockito;

import com.ifdsgroup.msg.client.appmsg.auth.AuthException;

/**
 * This test class handles all of the tests for SmartViewCallService
 * 
 * @author if993883
 *
 */
public class SmartViewCallServiceTest {

	SmartViewCallService smartViewCallService;
	IFastApiInvokerImpl impl;

	public SmartViewCallServiceTest() {
		this.impl = Mockito.mock(IFastApiInvokerImpl.class);
		this.smartViewCallService = new SmartViewCallService(impl);
	}

	String slotName = "devslotx67";
	String sessionToken = "Oup8Q1HBnLL/spjkVkZdZN/+vrVY/exu8YleIZEOHAiQrW0JuqWSY6c1EiB/NZCUmqK0h596d7ME97f97ZYU4GKT+9qsoOqIYOoC2AaBJwGulceROGij9pnzllTmMHTB973paf80WNvl1QXmNZgdr7/IVnfGhqXwVN54kv1+I79wuWuG8uhEn4L4QzBXlE1VdaqjwgoXHpV49ze83JSGsN0cV5au8NzTuYZy0XhF5KsoweMfBJAGGbhEQ5e8VZWY7INqjNiaV4OM00Ipv/3itmDt5di2ZtCCd1AoaEN8dN8dzilx8YBugJsyWQ7Gv4uWUF6nEyIEE5ITKuRChN0nQhpgb+DQ9SkAUyTHI1xZv1CnPQ7y57+vEWBcFO/m2RfwiK6XLuRDVg9ofPvo11uLptwCIOmG+zXErtZH+T73ek19nZ2+UF297pzZg28MTw5j39OBpjDlYPqLLZg6KRXxdMw/GYfSgW/0IhgoaZQMHyXejvS/qDwgTbGoE0ASBRDV08Uck0XSVL1cHOnYFytC088/VUjambuwGR5PMTHhIxjeOgAoyG6lA/kkDphu8xv9a801BGebQJLqff0UfmVM0ItQEAeeAcHq7w6kgi9TKw8=";
	String requestXml = "<request><fundOnlySearchRequest><RequestHeader><apiName>fundOnlySearch</apiName><envName>"
			+ slotName + "</envName><companyCode>SLF</companyCode><ruserId>if993762</ruserId><sessionId>" + sessionToken
			+ "</sessionId><dateFormat>mdy</dateFormat><locale>enUS</locale><dataMode>inquire</dataMode><interfaceName>ifds.desktop</interfaceName><language>en</language></RequestHeader><data><searchValue>sentry</searchValue><maxRecords>10</maxRecords><startRecordNum>1</startRecordNum></data></fundOnlySearchRequest></request>";

	@Test
	public void processRejectedTest() throws AuthException {
		String expectedResponse = "<dtRelFrozenAcctInitResponse><RequestStatus><status>Rejected</status><Errors><Error><errorType>business</errorType><errorCode>754</errorCode><text>Unclaimed property has not been reported for this account.(00754)</text><programmerNote>Unclaimed property has not been reported for this account.(uc00754)</programmerNote><errorSeverity>error</errorSeverity><module>/devslots/devslotx67/corfax/smartview/SMS00255.P</module></Error></Errors><viewModule>/devslots/devslotx67/corfax/smartview/SMS00255.P</viewModule><executionMilliseconds>9</executionMilliseconds></RequestStatus></dtRelFrozenAcctInitResponse>";
		given(impl.apply(requestXml, sessionToken, slotName)).willReturn(expectedResponse);
		assertEquals(smartViewCallService.process(requestXml, null).getData(), expectedResponse);
	}

	@Test
	public void processSuccessTest() throws AuthException {
		String expectedResponse = "<RequestStatus><status>Accepted</status><viewModule>/devslots/devslotx67/corfax/smartview/SMS00271.P</viewModule><executionMilliseconds>18</executionMilliseconds></RequestStatus>";
		given(impl.apply(requestXml, sessionToken, slotName)).willReturn(expectedResponse);
		assertEquals(smartViewCallService.process(requestXml, null).getData(), expectedResponse);
	}

}
