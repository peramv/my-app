package com.ifdsgroup.pdf.pdfelement;

import java.util.ArrayList;

/*
 * @author Zijian Ying
 */

public class Table extends PDFElement {
	public class Column {
		private String headertextalign = "left", fontfamily="arial";
		private float fontsize=10;
		public String getFontfamily() {
			return fontfamily;
		}

		public void setFontfamily(String fontfamily) {
			this.fontfamily = fontfamily;
		}

		public float getFontsize() {
			return fontsize;
		}

		public void setFontsize(float fontsize) {
			this.fontsize = fontsize;
		}

		private float columnwidth = 100, columnactwidth = 100, paddingleft = 2, paddingright = 2;

		public float getColumnactwidth() {
			return columnactwidth;
		}

		public void setColumnactwidth(float columnactwidth) {
			this.columnactwidth = columnactwidth;
		}

		public float getColumnwidth() {
			return columnwidth;
		}

		public void setColumnwidth(float columnwidth) {
			this.columnwidth = columnwidth;
			setColumnactwidth(columnwidth);
		}

		public float getPaddingleft() {
			return paddingleft;
		}

		public void setPaddingleft(float paddingleft) {
			this.paddingleft = paddingleft;
		}

		public float getPaddingright() {
			return paddingright;
		}

		public void setPaddingright(float paddingright) {
			this.paddingright = paddingright;
		}

		public String getHeadertextalign() {
			return headertextalign;
		}

		public void setHeadertextalign(String headertextalign) {
			this.headertextalign = headertextalign;
		}
	}
	
	private Tableheader header=null;
	
	public Tableheader getHeader() {
		return header;
	}

	public void setHeader(Tableheader header) {
		this.header = header;
	}

	private ArrayList<Column> columns = new ArrayList<Column>();

	public void addColumn(Column col) {
		columns.add(col);
		setWidth(getWidth() + col.getColumnwidth());
	}

	public Column getColumn(int i) {
		return (Column) columns.get(i);
	}

	private float top, left, width, bottom;

	private boolean hasHeader = false;

	public boolean isHasHeader() {
		return hasHeader;
	}

	public void setHasHeader(boolean hasHeader) {
		this.hasHeader = hasHeader;
	}

	public float getTop() {
		return top;
	}

	public void setTop(float top) {
		this.top = top;
	}

	public float getLeft() {
		return left;
	}

	public void setLeft(float left) {
		this.left = left;
	}

	public float getWidth() {
		return width;
	}

	public void setWidth(float width) {
		this.width = width;
	}

	public float getBottom() {
		return bottom;
	}

	public void setBottom(float bottom) {
		this.bottom = bottom;
	}

	public void doStart() throws Exception {
		setTop(getFloat("top"));
		setLeft(getFloat("left"));
		setBottom(getTop());
	}

	public void doEnd(final String text) throws Exception {
		float width = getLeft();
		drawLine(width, getTop(), width, getBottom());
		for (int i = 0; i < columns.size(); i++) {
			width += getColumn(i).getColumnwidth();
			drawLine(width, getTop(), width, getBottom());
		}
	}
}
