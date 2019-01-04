package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

public class TransferRdspResponse extends BaseResponse{
 private RdspTransferDetailDto rdspTransferDetail;

public RdspTransferDetailDto getRdspTransferDetail() {
	return rdspTransferDetail;
}

public void setRdspTransferDetail(RdspTransferDetailDto rdspTransferDetail) {
	this.rdspTransferDetail = rdspTransferDetail;
}
}
