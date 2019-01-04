package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;

public class UsageSummary {
	private List<NotionalLotUsage> notionalLotUsages = new ArrayList<>();

	public List<NotionalLotUsage> getNotionalLotUsages() {
		return notionalLotUsages;
	}

	public void setNotionalLotUsages(List<NotionalLotUsage> notionalLotUsages) {
		this.notionalLotUsages = notionalLotUsages;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		if (!super.equals(o)) return false;
		UsageSummary that = (UsageSummary) o;
		return Objects.equals(notionalLotUsages, that.notionalLotUsages);
	}

	@Override
	public int hashCode() {

		return Objects.hash(super.hashCode(), notionalLotUsages);
	}

	@Override
	public String toString() {
		return "LimitResponse{" +
			"\nlimits=" + notionalLotUsages +
			"}\n " + super.toString();
	}}
