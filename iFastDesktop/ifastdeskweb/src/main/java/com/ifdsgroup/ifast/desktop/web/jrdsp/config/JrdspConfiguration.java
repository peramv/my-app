package com.ifdsgroup.ifast.desktop.web.jrdsp.config;

import java.util.Arrays;

import org.apache.http.client.HttpClient;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.impl.conn.PoolingHttpClientConnectionManager;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.client.ClientHttpRequestFactory;
import org.springframework.http.client.HttpComponentsClientHttpRequestFactory;
import org.springframework.security.oauth2.client.OAuth2ClientContext;
import org.springframework.security.oauth2.client.OAuth2RestTemplate;
import org.springframework.security.oauth2.client.resource.OAuth2ProtectedResourceDetails;
import org.springframework.security.oauth2.client.token.AccessTokenProvider;
import org.springframework.security.oauth2.client.token.grant.password.ResourceOwnerPasswordAccessTokenProvider;
import org.springframework.security.oauth2.client.token.grant.password.ResourceOwnerPasswordResourceDetails;
import org.springframework.security.oauth2.config.annotation.web.configuration.EnableOAuth2Client;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurerAdapter;

import com.ifdsgroup.ifast.desktop.web.jrdsp.service.AuthService;

@Configuration
@ComponentScan(basePackages={"com.ifdsgroup.ifast.desktop.web"})
//@EnableOAuth2Client
public class JrdspConfiguration extends WebMvcConfigurerAdapter {
	
	@Value("${remote.authserver.url}")
	private String accessTokenUri;

	@Value("${remote.authserver.clientId}")
	private String clientId;
	
	@Value("${remote.authserver.clientSecret}")
	private String clientSecret;	
	
    @Value("${http.client.maxPoolSize}")
    private Integer maxPoolSize;
	
    @Autowired
    private OAuth2ClientContext oauth2ClientContext;
	
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
       //registry.addInterceptor(new AuthorizationInterceptor(authService())).addPathPatterns("/jrdsp/*");
    }
    
    @Bean
    public AuthService authService() {
    	return new AuthService();
    }
    
    @Bean
    public HttpClient httpClient() {
        PoolingHttpClientConnectionManager connectionManager = new PoolingHttpClientConnectionManager();
        connectionManager.setMaxTotal(maxPoolSize);
        // This client is for internal connections so only one route is expected
        connectionManager.setDefaultMaxPerRoute(maxPoolSize);
        return HttpClientBuilder.create().setConnectionManager(connectionManager).build();
    } 

    
    @Bean
    public ClientHttpRequestFactory httpRequestFactory() {
        return new HttpComponentsClientHttpRequestFactory(httpClient());
    }
    
    @Bean
    public OAuth2ProtectedResourceDetails oauth2ProtectedResourceDetails() {
        ResourceOwnerPasswordResourceDetails details = new ResourceOwnerPasswordResourceDetails();
        details.setClientId(clientId);
        details.setClientSecret(clientSecret);
        details.setAccessTokenUri(accessTokenUri);
        return details;
    }    
    
    @Bean
    public AccessTokenProvider accessTokenProvider() {
        ResourceOwnerPasswordAccessTokenProvider tokenProvider = new ResourceOwnerPasswordAccessTokenProvider();
        tokenProvider.setRequestFactory(httpRequestFactory());
        return new IFDSAccessTokenProviderChain(
                  Arrays.<AccessTokenProvider> asList(tokenProvider)
                );
    }    
    
/*    @Bean
    public OAuth2RestTemplate jrdspRestTemplate() {
        OAuth2RestTemplate template = new OAuth2RestTemplate(oauth2ProtectedResourceDetails(), oauth2ClientContext);
        template.setRequestFactory(httpRequestFactory());
        template.setAccessTokenProvider(accessTokenProvider());
        template.setRetryBadAccessTokens(true);
        return template;
    }  */  
    
    @Bean
    public RestTemplate jrdspRestTemplate() {
        
        return new RestTemplate();
    }  
    
}
