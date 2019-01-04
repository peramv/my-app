package com.ifdsgroup.ifast.desktop.web.service;

import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildDocument;
import static com.ifdsgroup.ifast.desktop.web.xpath.util.XPathUtil.buildXPath;
import static org.junit.Assert.*;

import javax.xml.xpath.XPath;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.ifdsgroup.ifast.desktop.web.exception.DesktopWebSystemException;

public class UpdateCacheServiceTest {
    
    @Rule
    public ExpectedException exceptions = ExpectedException.none();
    
    private CacheService cacheService;
    
    public UpdateCacheServiceTest() {
        cacheService = new CacheService();
    }
    
    @Test
    public void getKeyTest() {
        String request = "<UpdateCacheRequest><ToBeCached cacheKey=\"UpdatedClassData\"><SomeDummyData>Data</SomeDummyData></ToBeCached><ToBeCached cacheKey=\"ScreenDefList\"><SomeDummyData>Data</SomeDummyData></ToBeCached></UpdateCacheRequest>";
        
        Document document = buildDocument(request);
        Element documentElement = document.getDocumentElement();
        
        XPath xp = buildXPath();
        
        assertEquals("UpdatedClassData", cacheService.getXMLCacheKey(1, xp, documentElement));
        assertEquals("ScreenDefList", cacheService.getXMLCacheKey(2, xp, documentElement));
        
    }
    
    @Test
    public void getKeyValueTest() {
        String request = "<UpdateCacheRequest><ToBeCached cacheKey=\"UpdatedClassData\"><SomeDummyData>Data</SomeDummyData></ToBeCached><ToBeCached cacheKey=\"ScreenDefList\"><SomeDummyData>Data</SomeDummyData></ToBeCached></UpdateCacheRequest>";
        
        Document document = buildDocument(request);
        
        XPath xp = buildXPath();
        
        assertEquals("<SomeDummyData>Data</SomeDummyData>", cacheService.getXMLCacheValue(1, xp, document));
        assertEquals("<SomeDummyData>Data</SomeDummyData>", cacheService.getXMLCacheValue(2, xp, document));
        
    }
    
    @Test
    public void keyDoesntExistTest() {
        String request = "<UpdateCacheRequest><ToBeCached><SomeDummyData>Data</SomeDummyData></ToBeCached><ToBeCached cacheKey=\"ScreenDefList\"><SomeDummyData>Data</SomeDummyData></ToBeCached></UpdateCacheRequest>";
        
        Document document = buildDocument(request);
        Element documentElement = document.getDocumentElement();
        
        XPath xp = buildXPath();
        
        assertEquals("", cacheService.getXMLCacheKey(1, xp, documentElement));
        
    }
    
    @Test
    public void getOutOfBoundsKeyTest() {
        String request = "<UpdateCacheRequest><ToBeCached cacheKey=\"UpdatedClassData\"><SomeDummyData>Data</SomeDummyData></ToBeCached><ToBeCached cacheKey=\"ScreenDefList\"><SomeDummyData>Data</SomeDummyData></ToBeCached></UpdateCacheRequest>";
        
        Document document = buildDocument(request);
        Element documentElement = document.getDocumentElement();
        
        XPath xp = buildXPath();
        
        assertEquals("", cacheService.getXMLCacheKey(3, xp, documentElement));
        
    }
    
    @Test
    public void getOutOfBoundsKeyValueTest() {
        String request = "<UpdateCacheRequest><ToBeCached cacheKey=\"UpdatedClassData\"><SomeDummyData>Data</SomeDummyData></ToBeCached><ToBeCached cacheKey=\"ScreenDefList\"><SomeDummyData>Data</SomeDummyData></ToBeCached></UpdateCacheRequest>";
        
        Document document = buildDocument(request);
        
        XPath xp = buildXPath();
        
        assertEquals("", cacheService.getXMLCacheValue(3, xp, document));
        
    }
    
    @Test
    public void incompleteXMLTest() {
        String request = "<UpdateCacheRequest><ToBeCached cachquest>";

        exceptions.expect(DesktopWebSystemException.class);
        exceptions.expectMessage("Attribute name \"cachquest\" associated with an element type \"ToBeCached\" must be followed by the ' = ' character.");
        Document document = buildDocument(request);
        Element documentElement = document.getDocumentElement();
        
        XPath xp = buildXPath();
        
        cacheService.getXMLCacheKey(1, xp, documentElement);
        
    }
    
}
