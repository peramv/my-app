package com.ifdsgroup.pdf.pdfelement;

/*
 * @author Zijian Ying
 */

public class Tableheader extends Tablerow {
	public void doEnd(final String text) throws Exception {
		drawRow();
		tb.setHeader(this);
	}

}
