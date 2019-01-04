package com.ifdsgroup.ifast.desktop.web.controller;

import static org.junit.Assert.assertEquals;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.junit.Test;
import org.springframework.mock.web.MockHttpServletRequest;

import com.ifdsgroup.ifast.desktop.web.service.CacheService;

public class DeleteCacheControllerTest {
    
    private DeleteCacheController deleteCacheController;
    private HttpServletRequest request;
    private CacheService cacheService;
    
    public DeleteCacheControllerTest() {
        cacheService = new CacheService();
        deleteCacheController = new DeleteCacheController(cacheService);
    }
    
    @Test
    public void deleteCacheTest() {
        String dummyData1 = "<SomeDummyData>Data1</SomeDummyData>";
        String dummyData2 = "<SomeDummyData>Data2</SomeDummyData>";
        String payload = "<DeleteCacheRequest><cacheKey>ExistingClassData</cacheKey><cacheKey>AnotherKey</cacheKey></DeleteCacheRequest>";
        
        request = new MockHttpServletRequest();
        
        HttpSession session = request.getSession(true);
        session.setAttribute("ExistingClassData", dummyData1);
        session.setAttribute("AnotherKey", dummyData2);
        
        deleteCacheController.processRequest(request, payload);
        
        assertEquals(null, session.getAttribute("ExistingClassData"));
        assertEquals(null, session.getAttribute("AnotherKey"));
        
    }
    
    @Test
    public void deleteCacheThatIsNullTest() {
        String payload = "<DeleteCacheRequest><cacheKey>ExistingClassData</cacheKey></DeleteCacheRequest>";
        
        request = new MockHttpServletRequest();
        HttpSession session = request.getSession(true);
        
        deleteCacheController.processRequest(request, payload);
        assertEquals(null, session.getAttribute("ExistingClassData"));
        
    }
    
    @Test
    public void wrongXMLRequestTagTest() {
        String payload = "<WRONG><cacheKey>ExistingClassData</cacheKey></WRONG>";
        String dummyData = "<SomeDummyData>Data1</SomeDummyData>";
        
        request = new MockHttpServletRequest();
        HttpSession session = request.getSession(true);
        session.setAttribute("ExistingClassData", dummyData);
        
        deleteCacheController.processRequest(request, payload);
        
        assertEquals(null, session.getAttribute("ExistingClassData"));
        
    }
}
