package com.ifdsgroup.pdf.pdfelement;

import java.util.TreeMap;

import org.xml.sax.Attributes;

import com.ifdsgroup.pdf.IFDSPDF;
import com.pdflib.pdflib;

/*
 * @author Zijian Ying
 */

public class PDFElement {
	//private Attributes attrs = null;
	
	private TreeMap<String, String> attrs = new TreeMap<String, String>();

	final public TreeMap<String, String> getAttrs() {
		return attrs;
	}

	final public void setAttrs(final Attributes _attrs) {
		for(int i=0;i<_attrs.getLength();i++)
		attrs.put(_attrs.getQName(i), _attrs.getValue(i));
	}

	private String text = "", tagname = "";

	final public String getText() {
		return text;
	}

	final public void setText(final String newtext) {
		this.text = newtext;
	}

	final public String getTagname() {
		return tagname;
	}

	final public void setTagname(final String tagname) {
		this.tagname = tagname;
	}

	protected pdflib pl = null;

	protected PDFElement parent = null;

	private IFDSPDF pdfDoc = null;

	final public IFDSPDF getPdfDoc() {
		return pdfDoc;
	}
	
	final public pdflib getPDFLib() {
		return getPdfDoc().getPDFLib();
	}
	
	protected void doInit() throws Exception {

	}

	public void init() throws Exception {
		doInit();
	}

	public void doStart() throws Exception {

	}

	final public void start(final String tagname, final Attributes attrs,
			final IFDSPDF pdfDoc) throws Exception {
		this.pdfDoc = pdfDoc;
		this.pl = getPDFLib();
		parent = pdfDoc.getCurrentParent();
		pdfDoc.setCurrentParent(this);
		setTagname(tagname);
		setAttrs(attrs);
		
		// init the tag
		init();
		
		doStart();
	}

	public void doEnd(final String text) throws Exception {

	}

	final public void end(final String text) throws Exception {
		doEnd(text);
		setText(text);
		pdfDoc.setCurrentParent(parent);
	}

	final public String getString(final String key) {
		return (String) attrs.get(key);
	}

	final public float getFloat(final String key) throws Exception {
		return IFDSPDF.getFloat(getString(key));
	}

	final public int getInt(final String key) throws Exception {
		return IFDSPDF.getInt(getString(key));
	}

	final public PDFElement getParent() {
		return parent;
	}

	final public PDFElement getParent(String tag) {
		PDFElement parent = getParent();
		if(parent==null || ("fo:"+tag).equalsIgnoreCase(parent.getTagname()))
			return parent;
		else
			return parent.getParent(tag);
	}
	
	final public String inherentString(final String key) {
		String tmp = getString(key);
		if (tmp == null && getParent() != null)
			return getParent().inherentString(key);
		else
			return tmp;
	}

	final public float inherentFloat(final String key) throws Exception {
		return IFDSPDF.getFloat(inherentString(key));
	}

	final public int inherentInt(final String key) throws Exception {
		return IFDSPDF.getInt(inherentString(key));
	}
	
	final public void drawLine(float x0, float y0, float x1, float y1)
			throws Exception {
		pl.setlinewidth(0.1f);
		pl.moveto(x0, getPagemaster().getPageheight()-y0);
		pl.lineto(x1, getPagemaster().getPageheight()-y1);
		pl.stroke();
	}
	
	final public Simplepagemaster getPagemaster(){
		return getPdfDoc().getCurrentPagemaster();
	}
}
