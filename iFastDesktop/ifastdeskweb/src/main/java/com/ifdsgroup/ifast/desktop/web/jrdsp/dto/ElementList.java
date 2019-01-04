package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import javax.xml.bind.annotation.XmlAttribute;

public class ElementList {
	
	private String listName;
	private java.util.List<Element> elements;

	public java.util.List<Element> getElements() {
		return elements;
	}

	public void setElements(java.util.List<Element> elements) {
		this.elements = elements;
	}

	@XmlAttribute(name="listName")
	public String getListName() {
		return listName;
	}

	public void setListName(String listName) {
		this.listName = listName;
	}
}
