package com.ifdsgroup.ifast.desktop.web.jrdsp.interceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.stereotype.Component;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;

import com.ifdsgroup.ifast.desktop.web.jrdsp.service.AuthService;

@Component
public class AuthorizationInterceptor extends HandlerInterceptorAdapter {
	
	private AuthService authService;
	
    public AuthorizationInterceptor(AuthService authService) {
    	super();
		this.authService = authService;
	}

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {

        String authToken = request.getHeader("Token");
		authService.getAccessToken(authToken );
        return true;
    }
}
