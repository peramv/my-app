package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;

@JsonInclude(JsonInclude.Include.NON_NULL)
public class Elections {
	
	private List<Election> election;

	public List<Election> getElection() {
		return election;
	}

	public void setElection(List<Election> election) {
		this.election = election;
	}

	


	
}
