package com.ifdsgroup.pdf.pdfelement;

/*
 * @author Zijian Ying
 */

public class Simplepagemaster extends PDFElement {
	private float marginleft, margintop, marginright, marginbottom;
	private String mastername="";
	
	private float pagewidth, pageheight;

	final public float getPagewidth() {
		return pagewidth;
	}

	final public void setPagewidth(final float pagewidth) {
		this.pagewidth = pagewidth;
	}

	final public float getPageheight() {
		return pageheight;
	}

	final public void setPageheight(final float pageheight) {
		this.pageheight = pageheight;
	}
	
	public String getMastername() {
		return mastername;
	}

	public void setMastername(String mastername) {
		this.mastername = mastername;
	}

	public float getMarginleft() {
		return marginleft;
	}

	public void setMarginleft(float marginleft) {
		this.marginleft = marginleft;
	}

	public float getMargintop() {
		return margintop;
	}

	public void setMargintop(float margintop) {
		this.margintop = margintop;
	}

	public float getMarginright() {
		return marginright;
	}

	public void setMarginright(float marginright) {
		this.marginright = marginright;
	}

	public float getMarginbottom() {
		return marginbottom;
	}

	public void setMarginbottom(float marginbottom) {
		this.marginbottom = marginbottom;
	}

	public void doStart() throws Exception {
		setMastername(getString("master-name"));
		setMarginleft(getFloat("margin-left"));
		setMargintop(getFloat("margin-top"));
		setMarginright(getFloat("margin-right"));
		setMarginbottom(getFloat("margin-bottom"));
		
		// default to letter pager
		float tmp = getString("page-height") == null ? 11
				: getFloat("page-height");
		setPageheight(tmp);
		tmp = getString("page-width") == null ? 8.5f : getFloat("page-width");
		setPagewidth(tmp);
		
		((Layoutmasterset)getParent("layout-master-set")).addPagemaster(getString("master-name"), this);
	}
}
