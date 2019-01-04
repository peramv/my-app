package com.ifdsgroup.ifast.desktop.web.controller;

import static org.junit.Assert.*;
import static org.mockito.BDDMockito.given;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.junit.Test;
import org.mockito.Mockito;

import com.ifdsgroup.ifast.desktop.web.service.CacheService;

public class RetrieveCacheControllerTest {
    
    private RetrieveCacheController retrieveCacheController;
    private HttpServletRequest request;
    private CacheService cacheService;
    
    public RetrieveCacheControllerTest() {
        cacheService = Mockito.mock(CacheService.class);
        request = Mockito.mock(HttpServletRequest.class);

        retrieveCacheController = new RetrieveCacheController(cacheService);
    }
    
    @Test
    public void retrieveCacheTest() {
        String payload = "<RetrieveCacheRequest><cacheKey>InitData</cacheKey><cacheKey>ScreenDefList</cacheKey><cacheKey>ExistingClassData</cacheKey><cacheKey>UpdatedClassData</cacheKey></RetrieveCacheRequest>";
        
        List<String> keys = new ArrayList<String>();
        keys.add("InitData");
        keys.add("ScreenDefList");
        keys.add("ExistingClassData");
        keys.add("UpdatedClassData");
        
        String cachedData = "<SomeDummyData></SomeDummyData>";
        
        HttpSession session = Mockito.mock(HttpSession.class);
        keys.forEach(key -> given(session.getAttribute(key)).willReturn(cachedData));
        
        given(request.getSession(true)).willReturn(session);
        given(cacheService.getCacheKeyNodeNames(payload)).willReturn(keys);
        
        String response = retrieveCacheController.processRequest(request, payload);
        String expectedResponse = "<RetrieveCacheResponse><InitData><SomeDummyData></SomeDummyData></InitData><ScreenDefList><SomeDummyData></SomeDummyData></ScreenDefList><ExistingClassData><SomeDummyData></SomeDummyData></ExistingClassData><UpdatedClassData><SomeDummyData></SomeDummyData></UpdatedClassData></RetrieveCacheResponse>";
        
        assertEquals(expectedResponse, response);
    }
    
    @Test
    public void retrieveCacheNullTest() {
        String payload = "<RetrieveCacheRequest><cacheKey>InitData</cacheKey><cacheKey>ScreenDefList</cacheKey><cacheKey>ExistingClassData</cacheKey><cacheKey>UpdatedClassData</cacheKey></RetrieveCacheRequest>";
        
        List<String> keys = new ArrayList<String>();
        keys.add("InitData");
        keys.add("ScreenDefList");
        keys.add("ExistingClassData");
        keys.add("UpdatedClassData");
        
        String cachedData = null;
        
        HttpSession session = Mockito.mock(HttpSession.class);
        keys.forEach(key -> given(session.getAttribute(key)).willReturn(cachedData));
        
        given(request.getSession(true)).willReturn(session);
        given(cacheService.getCacheKeyNodeNames(payload)).willReturn(keys);
        
        String response = retrieveCacheController.processRequest(request, payload);
        String expectedResponse = "<RetrieveCacheResponse><InitData>null</InitData><ScreenDefList>null</ScreenDefList><ExistingClassData>null</ExistingClassData><UpdatedClassData>null</UpdatedClassData></RetrieveCacheResponse>";
        
        assertEquals(expectedResponse, response);
    }
    
    @Test
    public void retrieveCacheNoKeysTest() {
        String payload = "<RetrieveCacheRequest></RetrieveCacheRequest>";
        
        List<String> keys = new ArrayList<String>();
        
        String cachedData = "<SomeDummyData></SomeDummyData>";
        
        HttpSession session = Mockito.mock(HttpSession.class);
        keys.forEach(key -> given(session.getAttribute(key)).willReturn(cachedData));
        
        given(request.getSession(true)).willReturn(session);
        given(cacheService.getCacheKeyNodeNames(payload)).willReturn(keys);
        
        String response = retrieveCacheController.processRequest(request, payload);
        String expectedResponse = "<RetrieveCacheResponse></RetrieveCacheResponse>";
        
        assertEquals(expectedResponse, response);
    }

}
