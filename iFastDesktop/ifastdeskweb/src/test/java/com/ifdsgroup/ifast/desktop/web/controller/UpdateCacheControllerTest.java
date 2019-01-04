package com.ifdsgroup.ifast.desktop.web.controller;

import static org.junit.Assert.assertEquals;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.junit.Test;
import org.springframework.mock.web.MockHttpServletRequest;

import com.ifdsgroup.ifast.desktop.web.service.CacheService;

public class UpdateCacheControllerTest {
    
    private UpdateCacheController updateCacheController;
    private HttpServletRequest request;
    private CacheService cacheService;
    
    public UpdateCacheControllerTest() {
        cacheService = new CacheService();

        updateCacheController = new UpdateCacheController(cacheService);
    }
    
    @Test
    public void updateCacheTest() {
        String dummyData1 = "<SomeDummyData>Data1</SomeDummyData>";
        String dummyData2 = "<SomeDummyData>Data2</SomeDummyData>";
        String payload = "<UpdateCacheRequest><ToBeCached cacheKey=\"UpdatedClassData\">" + dummyData1 + "</ToBeCached><ToBeCached cacheKey=\"ScreenDefList\">" + dummyData2 + "</ToBeCached></UpdateCacheRequest>";
        
        request = new MockHttpServletRequest();
        updateCacheController.processRequest(request, payload);

        HttpSession session = request.getSession(true);
        assertEquals(dummyData1, session.getAttribute("UpdatedClassData"));
        assertEquals(dummyData2, session.getAttribute("ScreenDefList"));
        
    }
    
    @Test
    public void updateCacheNoKeysTest() {
        String payload = "<UpdateCacheRequest></UpdateCacheRequest>";
        
        request = new MockHttpServletRequest();
        updateCacheController.processRequest(request, payload);

        HttpSession session = request.getSession(true);
        assertEquals(null, session.getAttribute("UpdatedClassData"));
        assertEquals(null, session.getAttribute("ScreenDefList"));
        
    }
}
