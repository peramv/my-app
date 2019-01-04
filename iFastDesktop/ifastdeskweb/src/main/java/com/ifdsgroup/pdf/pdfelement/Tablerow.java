package com.ifdsgroup.pdf.pdfelement;

import java.util.ArrayList;

import com.ifdsgroup.pdf.pdfelement.Tablecell.Cell;

/*
 * @author Zijian Ying
 */

public class Tablerow extends TableElement {
	private ArrayList<Cell> cells = new ArrayList<Cell>();

	private float maxheight = 0;

	public void doEnd(final String text) throws Exception {
		drawRow();
	}

	public void addCell(Cell cell) throws Exception {
		cell.setWidth(tb.getColumn(cells.size()).getColumnwidth());
		if(cell.getTextalign()==null)
			cell.setTextalign(tb.getColumn(cells.size()).getHeadertextalign());
		cells.add(cell);

		setMaxRowHeight(cell.getCellHeight());
	}

	public void setMaxRowHeight(float height) {
		if (height > maxheight)
			maxheight = height;
	}

	public void drawRow() throws Exception {
		Simplepagemaster pagemaster = getPdfDoc().getCurrentPagemaster();

		float celltop = tb.getBottom();
		if (celltop + maxheight > pagemaster.getPageheight()
				- pagemaster.getMarginbottom()) {
			tb.doEnd("");
			pl.end_page();
			pl
					.begin_page(pagemaster.getPagewidth(), pagemaster
							.getPageheight());

			tb.setTop(pagemaster.getMargintop());
			tb.setBottom(tb.getTop());
			tb.drawLine(tb.getLeft(), tb.getBottom(), tb.getLeft() + tb.getWidth(),
					tb.getBottom());
			tb.getHeader().drawRow();
		}

		celltop = tb.getBottom();

		float left = tb.getLeft();
		for (int i = 0; i < cells.size(); i++) {
			cells.get(i).drawCell(left);
			left += tb.getColumn(i).getColumnwidth();

		}

		tb.setBottom(celltop + maxheight);
		tb.drawLine(tb.getLeft(), tb.getBottom(), tb.getLeft() + tb.getWidth(),
				tb.getBottom());

	}
}
