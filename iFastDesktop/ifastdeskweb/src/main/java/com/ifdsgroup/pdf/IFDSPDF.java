package com.ifdsgroup.pdf;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.StringReader;
import java.lang.reflect.Constructor;
import java.util.Stack;

import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;

import com.ifdsgroup.pdf.pdfelement.Layoutmasterset;
import com.ifdsgroup.pdf.pdfelement.PDFElement;
import com.ifdsgroup.pdf.pdfelement.Simplepagemaster;
import com.pdflib.pdflib;

/*
 * @author Zijian Ying
 */

public class IFDSPDF {

    public class IFDSPDFElementContainer {
        private Stack<PDFElement> elements = new Stack<PDFElement>();

        final public void push(final PDFElement element, final String tagname, final Attributes attrs,
                final IFDSPDF pdfDoc) throws Exception {
            element.start(tagname, attrs, pdfDoc);
            elements.push(element);
        }

        final public void pop(final String text) throws Exception {
            ((PDFElement) elements.pop()).end(text);
        }
    }

    private pdflib pl = null;

    public final pdflib getPDFLib() {
        return pl;
    }

    private PDFElement currentParent = null;

    private IFDSPDFElementContainer pdfelements = new IFDSPDFElementContainer();

    private Layoutmasterset layoutmasterset = null;

    private Simplepagemaster currentPagemaster = null;

    public Simplepagemaster getCurrentPagemaster() {
        return currentPagemaster;
    }

    public void setCurrentPagemaster(Simplepagemaster currentPagemaster) {
        this.currentPagemaster = currentPagemaster;
    }

    public Layoutmasterset getLayoutmasterset() {
        return layoutmasterset;
    }

    public void setLayoutmasterset(Layoutmasterset layoutmasterset) {
        this.layoutmasterset = layoutmasterset;
    }

    public final void start() throws Exception {
        pl = new pdflib();
        pl.open_file("");
    }

    public final void end() throws Exception {
        if (pl != null)
            pl.close();
    }

    // from xml and xsl
    public IFDSPDF(final String xml, final Source xslSource) throws Exception {
        Source xmlSource = new StreamSource(new StringReader(xml));
        ByteArrayOutputStream foStream = new ByteArrayOutputStream();
        StreamResult result = new StreamResult(foStream);
        TransformerFactory fTransformer = TransformerFactory.newInstance();
        Transformer trans = fTransformer.newTransformer(xslSource);
        trans.transform(xmlSource, result);
//         System.out.println("Stream : " +foStream.toString());
        // System.out.flush();

        new SAXEventHandler(this, new InputSource(new StringReader(new String(foStream.toByteArray(), "ISO-8859-1"))));
    }

    // from fo xml
    public IFDSPDF(final String foxml) throws Exception {
        new SAXEventHandler(this, new InputSource(new StringReader(foxml)));
    }

    // from .fo file
    public IFDSPDF(final File fofile) throws Exception {
        new SAXEventHandler(this, fofile);
    }

    @SuppressWarnings("unchecked")
    public final void startElement(final String tagname, final Attributes attrs) throws Exception {
        String elementname = tagname.replace("fo:", "").replace("-", "");
        elementname = elementname.substring(0, 1).toUpperCase() + elementname.substring(1);
        Class obj = null;
        PDFElement instance = null;

        try {
            obj = Class.forName("com.ifdsgroup.pdf.pdfelement." + elementname);
            Constructor cons = obj.getConstructor((Class[]) null);
            instance = (PDFElement) cons.newInstance((Object[]) null);
        } catch (ClassNotFoundException e) {
            instance = new PDFElement();
        }

        pdfelements.push(instance, tagname, attrs, this);
    }

    public final void endElement(final String text) throws Exception {
        pdfelements.pop(text.trim());

    }

    public final byte[] getByte() throws Exception {
        return pl.get_buffer();
    }

    public final void save(final String filename) throws Exception {
        FileOutputStream fs = null;

        try {
            fs = new FileOutputStream(new File(filename));
            fs.write(getByte());
            fs.flush();
        } finally {
            if (fs != null)
                fs.close();
        }
    }

    public final void stream(final OutputStream os) throws Exception {
        os.write(getByte());
        os.flush();
    }

    public final PDFElement getCurrentParent() {
        return currentParent;
    }

    public final void setCurrentParent(final PDFElement currentParent) {
        this.currentParent = currentParent;
    }

    public static float getFloat(final String val) throws Exception {
        float factor = 1f;
        if (val.indexOf("in") > 0)
            factor = 72f;
        else if (val.indexOf("cm") > 0)
            factor = 28.4f;
        return new Float(val.replaceAll("[^0-9.]", "")).floatValue() * factor;
    }

    public static int getInt(final String val) throws Exception {
        return new Integer(val.replaceAll("[^0-9]", "")).intValue();
    }
}
