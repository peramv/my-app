package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import static java.util.stream.Collectors.toList;

import java.util.LinkedHashMap;
import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="LatestRunsResponse")
public class LatestRunsResponse {
	private List<RunRecord> run;
	
	public List<RunRecord> getRun() {
		return run;
	}

	public void setRun(List<RunRecord> run) {
		this.run = run;
	}

	static public LatestRunsResponse toXML(List<LinkedHashMap<String, Object>> list) {
		LatestRunsResponse resp = new LatestRunsResponse();
		resp.setRun(list.stream().map(RunRecord::new).collect(toList()));
		return resp;
	}
}
