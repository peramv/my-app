package com.ifdsgroup.pdf.pdfelement;

public class Tablebody extends TableElement {
	public void doStart() throws Exception {
		if (!tb.isHasHeader()) {
			drawLine(tb.getLeft(), tb.getTop(), tb.getLeft() + tb.getWidth(),
					tb.getTop());
		}

	}
}
