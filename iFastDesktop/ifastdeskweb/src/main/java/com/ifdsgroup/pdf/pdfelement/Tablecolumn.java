package com.ifdsgroup.pdf.pdfelement;

import com.ifdsgroup.pdf.pdfelement.Table.Column;

/*
 * @author Zijian Ying
 */

public class Tablecolumn extends TableElement {
	public void doStart() throws Exception {
		Column col = tb.new Column();
		String tmp = getString("text-align");
		if (tmp == null)
			tmp = "left";

		col.setHeadertextalign(tmp);

		try {
			col.setColumnwidth(getFloat("column-width"));
			
		} catch (Exception e) {
		}

		try {
			col.setPaddingleft(getFloat("padding-left"));
		} catch (Exception e) {
		}

		try {
			col.setPaddingright(getFloat("padding-right"));
		} catch (Exception e) {
		}
		
		tb.addColumn(col);
	}
}
