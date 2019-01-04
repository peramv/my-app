package com.ifdsgroup.ifast.desktop.web.dto;

/**
 * This class is an immutable class representing the backend API response. It
 * acts as a DTO and stores xml data, response status (success/failed) and the
 * corresponding response message.
 * 
 * @author if993762
 *
 */
public final class SmartViewPayload {

    private final String data;
    private final String responseStatus;
    private final String responseMsg;

    public SmartViewPayload(String data, String responseStatus, String responseMsg) {
        this.data = data;
        this.responseStatus = responseStatus;
        this.responseMsg = responseMsg;
    }
    
    public String getData() {
        return data;
    }

    public String getResponseStatus() {
        return responseStatus;
    }

    public String getResponseMsg() {
        return responseMsg;
    }

    @Override
    public String toString() {
        StringBuilder response = new StringBuilder().append("<SmartviewResponse>");
        if (data != null) {
            response.append(data);
        }
        if (responseMsg != null) {
            response.append(responseMsg);
        }
        if (responseStatus != null) {
            response.append("<status>").append(responseStatus).append("</status>");
        }
        response.append("</SmartviewResponse>");
        return response.toString();
    }
}