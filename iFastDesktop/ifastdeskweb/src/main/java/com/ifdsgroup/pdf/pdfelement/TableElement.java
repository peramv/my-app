package com.ifdsgroup.pdf.pdfelement;

/*
 * @author Zijian Ying
 */

public class TableElement extends PDFElement {
	protected Table tb = null;

	protected void doInit() throws Exception {
		tb = (Table) getParent("table");
	}

	final public Table getTable() {
		return tb;
	}
}
