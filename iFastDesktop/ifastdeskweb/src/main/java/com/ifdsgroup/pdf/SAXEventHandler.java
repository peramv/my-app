package com.ifdsgroup.pdf;

import java.io.File;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.Locator;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/*
 * @author Zijian Ying
 */

final public class SAXEventHandler extends DefaultHandler {
    private IFDSPDF pdf = null;

    private StringBuffer plaintext = new StringBuffer();

    public SAXEventHandler(IFDSPDF pdf, InputSource is) throws Exception {
        this.pdf = pdf;
        getSAXParser().parse(is, this);
    }

    public SAXEventHandler(IFDSPDF pdf, File fofile) throws Exception {
        this.pdf = pdf;
        getSAXParser().parse(fofile, this);
    }

    private SAXParser getSAXParser() throws Exception {
        return SAXParserFactory.newInstance().newSAXParser();
    }

    public void setDocumentLocator(Locator arg0) {

    }

    public void startDocument() throws SAXException {
        try {
            pdf.start();
        } catch (Exception e) {
            throw new SAXException(e);
        }
    }

    public void endDocument() throws SAXException {
        try {
            pdf.end();
        } catch (Exception e) {
            throw new SAXException(e);
        }

    }

    public void startPrefixMapping(String arg0, String arg1) throws SAXException {
        // TODO Auto-generated method stub

    }

    public void endPrefixMapping(String arg0) throws SAXException {
        // TODO Auto-generated method stub

    }

    public void startElement(String arg0, String arg1, String tagname, Attributes attrs) throws SAXException {
        try {
            pdf.startElement(tagname, attrs);
        } catch (Exception e) {
            throw new SAXException(e.getMessage());
        }
    }

    public void endElement(String arg0, String arg1, String tagname) throws SAXException {
        String text = plaintext.toString().trim();

        try {
            pdf.endElement(text);
        } catch (Exception e) {
            throw new SAXException(e.getMessage());
        } finally {
            plaintext = new StringBuffer();
        }
    }

    public void characters(char[] arg0, int arg1, int arg2) throws SAXException {
        plaintext.append(arg0, arg1, arg2);
    }

    public void ignorableWhitespace(char[] arg0, int arg1, int arg2) throws SAXException {
        // TODO Auto-generated method stub

    }

    public void processingInstruction(String arg0, String arg1) throws SAXException {
        // TODO Auto-generated method stub

    }

    public void skippedEntity(String arg0) throws SAXException {
        // TODO Auto-generated method stub

    }
}
