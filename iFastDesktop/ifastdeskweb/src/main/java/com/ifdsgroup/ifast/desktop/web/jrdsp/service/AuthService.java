package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import java.util.Arrays;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.converter.json.MappingJackson2HttpMessageConverter;
import org.springframework.security.oauth2.client.DefaultOAuth2ClientContext;
import org.springframework.security.oauth2.client.OAuth2RestTemplate;
import org.springframework.security.oauth2.client.token.grant.password.ResourceOwnerPasswordResourceDetails;
import org.springframework.security.oauth2.common.OAuth2AccessToken;
import org.springframework.stereotype.Service;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.UserToken;

@Service
public class AuthService {
	
	private static final String GRANT_TYPE_PASSWORD = "password";
	private static final String GRANT_TYPE_REFRESH = "refresh_token";

	@Value("${remote.authserver.url}")
	private String authUrl;

	@Value("${remote.authserver.clientId}")
	private String clientId;
	
	@Value("${remote.authserver.clientSecret}")
	private String clientSecret;
	
	public Optional<UserToken> getAccessToken(String ifastToken) {
		
		ResourceOwnerPasswordResourceDetails resourceDetails = new ResourceOwnerPasswordResourceDetails();
		resourceDetails.setUsername(ifastToken);
		resourceDetails.setAccessTokenUri(authUrl);
		resourceDetails.setClientId(clientId);
		resourceDetails.setClientSecret(clientSecret);
		resourceDetails.setGrantType(GRANT_TYPE_PASSWORD);
		resourceDetails.setScope(Arrays.asList("read"));

		DefaultOAuth2ClientContext clientContext = new DefaultOAuth2ClientContext();
		
		OAuth2RestTemplate restTemplate = new OAuth2RestTemplate(resourceDetails, clientContext);
		restTemplate.setMessageConverters(Arrays.asList(new MappingJackson2HttpMessageConverter()));

		OAuth2AccessToken accessToken = restTemplate.getAccessToken();
		
		if(accessToken != null) {
			return Optional.of(new UserToken(accessToken.getValue(), accessToken.getRefreshToken().getValue()));
		}
		
		
		return Optional.empty();
	}
	
	public Optional<UserToken> refreshToken(String refreshToken) {
		ResourceOwnerPasswordResourceDetails resourceDetails = new ResourceOwnerPasswordResourceDetails();
		resourceDetails.setUsername(refreshToken);
		resourceDetails.setAccessTokenUri(authUrl);
		resourceDetails.setClientId(clientId);
		resourceDetails.setClientSecret(clientSecret);
		resourceDetails.setGrantType(GRANT_TYPE_REFRESH);
		resourceDetails.setScope(Arrays.asList("read"));

		DefaultOAuth2ClientContext clientContext = new DefaultOAuth2ClientContext();
		
		OAuth2RestTemplate restTemplate = new OAuth2RestTemplate(resourceDetails, clientContext);
		restTemplate.setMessageConverters(Arrays.asList(new MappingJackson2HttpMessageConverter()));

		OAuth2AccessToken accessToken = restTemplate.getAccessToken();
		
		if(accessToken != null) {
			return Optional.of(new UserToken(accessToken.getValue(), accessToken.getRefreshToken().getValue()));
		}
		return Optional.empty();
	}

}
