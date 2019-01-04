package com.ifdsgroup.pdf.pdfelement;

import java.util.TreeMap;

/*
 * @author Zijian Ying
 */

public class Layoutmasterset extends PDFElement {
	private TreeMap<String, Simplepagemaster> pagemasters = new TreeMap<String, Simplepagemaster>();

	public void addPagemaster(String name, Simplepagemaster pagemaster) {
		pagemasters.put(name, pagemaster);
	}

	public Simplepagemaster getSimplepagemaster(String name) {
		return pagemasters.get(name);
	}
	
	public void doEnd(final String text) throws Exception {
		getPdfDoc().setLayoutmasterset(this);
	}

}
