package com.ifdsgroup.ifast.desktop.web.jrdsp.controller.advice;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
import org.mockito.runners.MockitoJUnitRunner;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.client.HttpClientErrorException;
import org.springframework.web.client.HttpServerErrorException;
import org.springframework.web.client.HttpStatusCodeException;

import static org.junit.Assert.*;

@RunWith(MockitoJUnitRunner.class)
public class ControllerExceptionHandlerTest {
    @InjectMocks
    private ControllerExceptionHandler handler;

    @Test
    public void testHttpStatusCodeExceptionHandler() {
        ResponseEntity expected = ResponseEntity.status(HttpStatus.MULTI_STATUS).body(HttpStatus.MULTI_STATUS.getReasonPhrase());
        HttpStatusCodeException httpStatusCodeException = new HttpClientErrorException(HttpStatus.MULTI_STATUS);

        ResponseEntity actual = handler.httpStatusCodeExceptionHandler(httpStatusCodeException);

        assertEquals(expected, actual);

        httpStatusCodeException = new HttpServerErrorException(HttpStatus.MULTI_STATUS);

        actual = handler.httpStatusCodeExceptionHandler(httpStatusCodeException);

        assertEquals(expected, actual);
    }

    @Test
    public void testUnexpectedExceptionHandler() {
        RuntimeException e = new RuntimeException("aaa");
        ResponseEntity expected = ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(e.getMessage());

        ResponseEntity actual = handler.unexpectedExceptionHandler(e);

        assertEquals(expected, actual);
    }
}