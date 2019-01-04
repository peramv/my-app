package com.ifdsgroup.pdf.pdfelement;

/*
 * @author Zijian Ying
 */

public class Blockcontainer extends PDFElement {
	public void doStart() throws Exception {
		if (getString("left") != null && getString("top") != null)
			pl.set_text_pos(getFloat("left"), getPagemaster().getPageheight()
					- getFloat("top"));
	}
}
