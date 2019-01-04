package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

public class RecordRange {
	private int rangeStart;
	private int rangeEnd;
	private String moreRecordsExist;
	private int rangeStartForPrev;
	private int rangeStartForNext;

	public int getRangeStart() {
		return rangeStart;
	}

	public void setRangeStart(int rangeStart) {
		this.rangeStart = rangeStart;
	}

	public int getRangeEnd() {
		return rangeEnd;
	}

	public void setRangeEnd(int rangeEnd) {
		this.rangeEnd = rangeEnd;
	}

	public String getMoreRecordsExist() {
		return moreRecordsExist;
	}

	public void setMoreRecordsExist(String moreRecordsExist) {
		this.moreRecordsExist = moreRecordsExist;
	}

	public int getRangeStartForPrev() {
		return rangeStartForPrev;
	}

	public void setRangeStartForPrev(int rangeStartForPrev) {
		this.rangeStartForPrev = rangeStartForPrev;
	}

	public int getRangeStartForNext() {
		return rangeStartForNext;
	}

	public void setRangeStartForNext(int rangeStartForNext) {
		this.rangeStartForNext = rangeStartForNext;
	}
}
