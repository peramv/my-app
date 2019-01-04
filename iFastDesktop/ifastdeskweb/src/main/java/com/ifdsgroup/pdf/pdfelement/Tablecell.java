package com.ifdsgroup.pdf.pdfelement;

import java.util.ArrayList;

/*
 * @author Zijian Ying
 */

public class Tablecell extends TableElement {
	public class Cell {
		private float width = 100, leftpadding = 2, rightpadding = 2,
				paddingtop = 0, paddingbottom = 0, textlineheight = 2f,
				fontsize = 4.5f;

		public float getPaddingtop() {
			return paddingtop;
		}

		public void setPaddingtop(float paddingtop) {
			this.paddingtop = paddingtop;
		}

		public float getPaddingbottom() {
			return paddingbottom;
		}

		public void setPaddingbottom(float paddingbottom) {
			this.paddingbottom = paddingbottom;
		}

		public float getTextlineheight() {
			return textlineheight;
		}

		public void setTextlineheight(float textlineheight) {
			this.textlineheight = textlineheight;
		}

		private String textalign = null, fontfamily = "Arial";

		public float getFontsize() {
			return fontsize;
		}

		public void setFontsize(float fontsize) {
			this.fontsize = fontsize;
		}

		public String getFontfamily() {
			return fontfamily;
		}

		public void setFontfamily(String fontfamily) {
			this.fontfamily = fontfamily;
		}

		public String getTextalign() {
			return textalign;
		}

		public void setTextalign(String textalign) {
			this.textalign = textalign;
		}

		public float getLeftpadding() {
			return leftpadding;
		}

		public void setLeftpadding(float leftpadding) {
			this.leftpadding = leftpadding;
		}

		public float getRightpadding() {
			return rightpadding;
		}

		public void setRightpadding(float rightpadding) {
			this.rightpadding = rightpadding;
		}

		public float getWidth() {
			return width;
		}

		public void setWidth(float width) {
			this.width = width;
		}

		private ArrayList<String> texts = new ArrayList<String>();

		public ArrayList<String> getTexts() {
			return texts;
		}

		public void addLine(String text) {
			texts.add(text);
		}

		public float getCellHeight() throws Exception {
			pl.setfont(pl.findfont(getFontfamily(), "winansi", 0),
					getFontsize());

			float totalh = 0;
			Simplepagemaster pagemaster = getPdfDoc().getCurrentPagemaster();

			for (int i = 0; i < texts.size(); i++) {
				int ret = -1;
				boolean isOk = false;
				float h = getTextlineheight();
				String str = texts.get(i);
				while (!isOk) {
					while (ret != 0) {
						ret = pl.show_boxed(str, getLeftpadding(),
								0, getWidth() - getLeftpadding()
										- getRightpadding(), h, getTextalign(),
								"blind");
						if (ret != 0) {
							h += getTextlineheight();
							if (h > pagemaster.getPageheight()) {
								setWidth(getWidth() + 2);
								h = getTextlineheight();
								break;
							}
						} else {
							isOk = true;
						}
					}

				}
				totalh += (h+getPaddingtop() + getPaddingbottom());
			}
			return totalh;
		}

		public void drawCell(float left) throws Exception {
			pl.setfont(pl.findfont(getFontfamily(), "winansi", 0),
					getFontsize());

			Simplepagemaster pagemaster = getPdfDoc().getCurrentPagemaster();

			float top = tb.getBottom();

			for (int i = 0; i < texts.size(); i++) {
				int ret = -1;
				boolean isOk = false;
				float h = getTextlineheight();
				String str = texts.get(i);
				while (!isOk) {
					while (ret != 0) {
						ret = pl.show_boxed(str, getLeftpadding(),
								0, getWidth() - getLeftpadding()
										- getRightpadding(), h, getTextalign(),
								"blind");
						if (ret != 0) {
							h += getTextlineheight();
							if (h > pagemaster.getPageheight()) {
								setWidth(getWidth() + 2);
								h = getTextlineheight();
								break;
							}
						} else {
							isOk = true;
							h += (getPaddingtop() + getPaddingbottom());
							pl.show_boxed(str, left + getLeftpadding(),
									getPagemaster().getPageheight()
											- (top + getPaddingtop()) - h,
									getWidth() - getLeftpadding()
											- getRightpadding(), h,
									getTextalign(), "");

							top += (h);

						}
					}

				}
			}
		}
	}

	private Cell cell = null;
	private Tablerow tr = null;
	private Tableheader th = null;

	public Cell getCell() {
		return cell;
	}

	public void doStart() throws Exception {
		cell = new Cell();

		String tmp = getString("text-align");
		if (tmp != null) {
			cell.setTextalign(tmp);
		}

		try {
			cell.setPaddingtop(getFloat("padding-top"));
		} catch (Exception e) {

		}

		try {
			cell.setPaddingbottom(getFloat("padding-bottom"));
		} catch (Exception e) {

		}
		try {
			cell.setLeftpadding(getFloat("padding-left"));
		} catch (Exception e) {

		}
		try {
			cell.setRightpadding(getFloat("padding-right"));
		} catch (Exception e) {

		}

	}

	public void doEnd(String text) throws Exception {
		tr = (Tablerow) getParent("table-row");
		if (tr != null) {

			tr.addCell(cell);
		}

		th = (Tableheader) getParent("table-header");
		if (th != null) {

			th.addCell(cell);
		}
	}
}
