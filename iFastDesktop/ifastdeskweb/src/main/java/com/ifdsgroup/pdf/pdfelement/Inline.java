package com.ifdsgroup.pdf.pdfelement;


/*
 * @author Zijian Ying
 */

public class Inline extends PDFElement {
	private String textalign = null;
	private float top, left, right,bottom;

	public void doStart() throws Exception {
		if (inherentString("font-family") != null && inherentString("font-size") != null)
			pl.setfont(pl.findfont(inherentString("font-family"), "winansi", 0),
					inherentFloat("font-size"));
	}
	
	public void doEnd(String text) throws Exception{
		if (!"".equalsIgnoreCase(text)) {
			textalign = inherentString("text-align");
			if (textalign == null) {
				pl.show(text);
				pl.continue_text("");
			} else {
				try {
					top = inherentFloat("top");
					left = inherentFloat("left");
					bottom = inherentFloat("bottom");
					right = inherentFloat("right");
					pl.show_boxed(text, left, getPagemaster().getPageheight()
							- bottom, right - left, bottom - top, textalign, "");
				} catch (Exception e) {
					System.out.println("Missing dimensions.");
				}
			}
		}
	}
}
