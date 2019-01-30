package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.Date;

import javax.xml.bind.annotation.adapters.XmlJavaTypeAdapter;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.DateAdapter;

public class TransRecordDto {
	private long id;
	private int row;
	
	private boolean checked;
	private boolean changed;
	private long account;
	private Date transDate;
	private long esdcTransNo;
	private String recordType;
	private String transType;
	private String description;
	private String status;
	private String serverStatus;
	
	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public int getRow() {
		return row;
	}

	public void setRow(int row) {
		this.row = row;
	}

	public boolean isChecked() {
		return checked;
	}

	public void setChecked(boolean checked) {
		this.checked = checked;
	}

	public long getAccount() {
		return account;
	}

	public void setAccount(long account) {
		this.account = account;
	}

	@XmlJavaTypeAdapter(DateAdapter.class)
	public Date getTransDate() {
		return transDate;
	}

	@JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "dd/MM/yyyy")
	public void setTransDate(Date transDate) {
		this.transDate = transDate;
	}

	public long getEsdcTransNo() {
		return esdcTransNo;
	}

	public void setEsdcTransNo(long esdcTransNo) {
		this.esdcTransNo = esdcTransNo;
	}

	public String getRecordType() {
		return recordType;
	}

	public void setRecordType(String recordType) {
		this.recordType = recordType;
	}

	public String getTransType() {
		return transType;
	}

	public void setTransType(String transType) {
		this.transType = transType;
	}
	
	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
		serverStatus = status;
	}
	
	public String getServerStatus() {
		return serverStatus;
	}

	public void setServerStatus(String serverStatus) {
		this.serverStatus = serverStatus;
	}
	public boolean isChanged() {
		return changed;
	}
	
	public void setChanged(boolean changed) {
		this.changed = changed;
	}
}

