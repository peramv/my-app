package com.ifdsgroup.ifast.desktop.web.jrdsp.controller;

import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.security.oauth2.client.OAuth2RestTemplate;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import com.ifdsgroup.ifast.desktop.web.jrdsp.service.AuthService;

@RestController
public class SampleController {
	
	@Autowired
	AuthService authService;
	
//	@Autowired
	OAuth2RestTemplate jrdspRestTemplate;
	
	@RequestMapping("/jrdsp/{name}")
	public String getMessage(@PathVariable String name, @RequestHeader("Token") String ifastToken, HttpSession session) {
		jrdspRestTemplate.getOAuth2ClientContext().getAccessTokenRequest().set("username",ifastToken);
		ResponseEntity<String> jrdspResponse = jrdspRestTemplate.getForEntity("http://localhost:9060/foos/1", String.class);
		System.out.println(jrdspResponse.getBody());
		return "hi " + name;
	}

}
