package com.ifdsgroup.ifast.desktop.web.jrdsp.controller.advice;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.client.HttpStatusCodeException;

@ControllerAdvice(basePackages = {"com.ifdsgroup.ifast.desktop.web.jrdsp.controller"})
public class ControllerExceptionHandler {
    @ExceptionHandler(value=HttpStatusCodeException.class)
    public ResponseEntity httpStatusCodeExceptionHandler(HttpStatusCodeException e) {
        return ResponseEntity.status(e.getStatusCode()).body(e.getStatusCode().getReasonPhrase());
    }

    @ExceptionHandler(value=Exception.class)
    public ResponseEntity unexpectedExceptionHandler(Exception e) {
        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(e.getMessage());
    }
}
