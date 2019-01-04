package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

public class TransferRdspPutRequest extends BaseRequest{
	private RdspTransferDetailDto rdspTransferDetail;

	public RdspTransferDetailDto getRdspTransferDetail() {
		return rdspTransferDetail;
	}

	public void setRdspTransferDetail(RdspTransferDetailDto rdspTransferDetail) {
		this.rdspTransferDetail = rdspTransferDetail;
	}
}
