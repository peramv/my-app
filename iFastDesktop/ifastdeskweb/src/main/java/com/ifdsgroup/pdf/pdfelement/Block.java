package com.ifdsgroup.pdf.pdfelement;

import com.ifdsgroup.pdf.pdfelement.Tablecell.Cell;

/*
 * @author Zijian Ying
 */

public class Block extends PDFElement {
	private Cell cell = null;
	private Tablecell td = null;

	public void doStart() throws Exception {
		td = (Tablecell) getParent("table-cell");
		if (td != null) {
			cell = td.getCell();
			if (inherentString("font-family") != null
					&& inherentString("font-size") != null) {
				cell.setFontfamily(inherentString("font-family"));
				cell.setFontsize(inherentFloat("font-size"));
			}
		} else {
			if (inherentString("font-family") != null
					&& inherentString("font-size") != null) {
				pl.setfont(pl.findfont(inherentString("font-family"),
						"winansi", 0), inherentFloat("font-size"));
			}
		}
	}

	public void doEnd(String text) throws Exception {
		if (cell != null) {
			cell.addLine(text);
		} else {
			if (!"".equalsIgnoreCase(text)) {
				pl.show(text);
				pl.continue_text("");
			}
		}
	}
}
