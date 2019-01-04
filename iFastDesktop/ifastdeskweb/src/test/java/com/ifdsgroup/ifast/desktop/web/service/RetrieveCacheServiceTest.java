package com.ifdsgroup.ifast.desktop.web.service;

import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.List;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import com.ifdsgroup.ifast.desktop.web.exception.DesktopWebSystemException;

/**
 * This test class handles all of the tests for the 'retrieve' portion of
 * cacheService
 * 
 * @author if993883
 *
 */
public class RetrieveCacheServiceTest {
    
    @Rule
    public ExpectedException exceptions = ExpectedException.none();
    
    CacheService cacheService;
    
    public RetrieveCacheServiceTest() {
        this.cacheService = new CacheService();
    }
    
    @Test
    public void processRetrieveCacheTest() {
        
        /*
         * Test InitData use case
         */
        String requestXml = "<RetrieveCacheRequest><cacheKey>InitData</cacheKey></RetrieveCacheRequest>";
        List<String> expectedResponse = new ArrayList<String>();
        expectedResponse.add("InitData");
        
        assertEquals(cacheService.getCacheKeyNodeNames(requestXml), expectedResponse);
        
        /*
         * Test other use case
         */
        requestXml = "<RetrieveCacheRequest><cacheKey>InitData</cacheKey><cacheKey>ScreenDefList</cacheKey><cacheKey>ExistingClassData</cacheKey><cacheKey>UpdatedClassData</cacheKey></RetrieveCacheRequest>";
        
        expectedResponse.add("ScreenDefList");
        expectedResponse.add("ExistingClassData");
        expectedResponse.add("UpdatedClassData");
        
        assertEquals(cacheService.getCacheKeyNodeNames(requestXml), expectedResponse);
        
    }
    
    @Test
    public void processRetrieveCacheNullXml() {
        exceptions.expect(NullPointerException.class);
        assertEquals(cacheService.getCacheKeyNodeNames(null), new ArrayList<String>());
        
    }
    
    @Test
    public void processRetrieveCacheNoXml() {
        
        String requestXml = "";
        
        exceptions.expect(DesktopWebSystemException.class);
        exceptions.expectMessage("Premature end of file.");
        assertEquals(cacheService.getCacheKeyNodeNames(requestXml), new ArrayList<String>());
        
    }
    
    @Test
    public void processRetrieveCacheNoClosingTagTest() {
        
        String requestXml = "<RetrieveCacheRequest><cacheKey></cacheKey>";
        
        exceptions.expect(DesktopWebSystemException.class);
        exceptions.expectMessage("XML document structures must start and end within the same entity.");
        cacheService.getCacheKeyNodeNames(requestXml); 
        
    }
    
    @Test
    public void processRetrieveCacheNoCacheKeyTest() {
        
        String requestXml = "<RetrieveCacheRequest></RetrieveCacheRequest>";
        assertEquals(cacheService.getCacheKeyNodeNames(requestXml), new ArrayList<String>());
        
    }
    
    @Test
    public void processRetrieveCacheNoEnclosingTagTest() {
        
        String requestXml = "<cacheKey>InitData</cacheKey>";
        List<String> expectedResponse = new ArrayList<String>();
        expectedResponse.add("InitData");
        
        assertEquals(cacheService.getCacheKeyNodeNames(requestXml), expectedResponse); 
        
    }
    
    @Test
    public void processRetrieveCacheWrongEnclosingTagTest() {
        
        String requestXml = "<Request><cacheKey>InitData</cacheKey></Request>";
        List<String> expectedResponse = new ArrayList<String>();
        expectedResponse.add("InitData");
        
        assertEquals(cacheService.getCacheKeyNodeNames(requestXml), expectedResponse); 
        
    }
    
    @Test
    public void processRetrieveCacheNoCacheKeyValueTest() {
        
        String requestXml = "<RetrieveCacheRequest><cacheKey></cacheKey></RetrieveCacheRequest>";
        List<String> expectedResponse = new ArrayList<String>();
        expectedResponse.add("");
        
        assertEquals(cacheService.getCacheKeyNodeNames(requestXml), expectedResponse);
        
    }
    
    @Test
    public void processRetrieveCacheSAXExceptionTest() {
        String requestXml = "<RetrieveCacheRequest><cacheKey>InitData</est>";
        
        exceptions.expect(DesktopWebSystemException.class);
        exceptions.expectMessage("The element type \"cacheKey\" must be terminated by the matching end-tag \"</cacheKey>\".");
        cacheService.getCacheKeyNodeNames(requestXml);
    }
    
}
