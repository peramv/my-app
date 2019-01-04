package com.ifdsgroup.ifast.desktop.web.exception;

/**
 * This class is a custom Runtime Exception class to wrap any checked
 * exceptions.
 * 
 * @author if993762
 *
 */
public class DesktopWebSystemException extends RuntimeException {

    private String errorCode;

    public DesktopWebSystemException(String code, String message) {
        this(message);
        this.errorCode = code;
    }

    public DesktopWebSystemException(String code, String message, Throwable cause) {
        this(message, cause);
        this.errorCode = code;
    }

    public DesktopWebSystemException(String message, Throwable cause) {
        super(message, cause);
    }

    public DesktopWebSystemException(Throwable cause) {
        super(cause);
    }

    public DesktopWebSystemException(String message) {
        super(message);
        this.errorCode = message;
    }

    public String getErrorCode() {
        return errorCode;
    }

    public void setErrorCode(String errorCode) {
        this.errorCode = errorCode;
    }

}