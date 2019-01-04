package com.ifdsgroup.ifast.desktop.web.xpath.util;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class XPathUtilTest {
    @Test
    public void makeNodeSuccessTest() {
        String root = "Root";
        String value = "Value";
        assertEquals(XPathUtil.makeNode(root, value), "<" + root + ">" + value + "</" + root + ">");
    }
    
    @Test
    public void makeNodeNullRootTest() {
        String root = null;
        String value = "Value";
        assertEquals(XPathUtil.makeNode(root, value), "<" + root + ">" + value + "</" + root + ">"); 
    }
    
    @Test
    public void makeNodeNullValueTest() {
        String root = "Root";
        String value = null;
        assertEquals(XPathUtil.makeNode(root, value), "<" + root + ">" + value + "</" + root + ">"); 
    }
    
    @Test
    public void makeNodeNullTest() {
        String root = null;
        String value = null;
        assertEquals(XPathUtil.makeNode(root, value), "<" + root + ">" + value + "</" + root + ">"); 
    }
}
