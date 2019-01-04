package com.ifdsgroup.ifast.desktop.web.core.config;

import static com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants.PROP_PATH;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.HashMap;
import java.util.Properties;

import javax.annotation.PostConstruct;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.jasypt.encryption.pbe.StandardPBEStringEncryptor;
import org.jasypt.properties.EncryptableProperties;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.web.servlet.ServletRegistrationBean;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
import org.springframework.context.annotation.PropertySource;
import org.springframework.core.env.Environment;
import org.springframework.oxm.jaxb.Jaxb2Marshaller;

import com.ifdsgroup.ifast.desktop.web.service.IFastApiInvoker;
import com.ifdsgroup.ifast.desktop.web.service.IFastApiInvokerImpl;
import com.ifdsgroup.ifast.desktop.web.service.IFastOEInvokerImpl;
import com.ifdsgroup.ifast.desktop.web.service.SmartPDFService;
import com.ifdsgroup.integration.util.MsgProperties;
import com.ifdsgroup.msg.client.appmsg.messenger.client.AppMsgClientFactory;

/**
 * 
 * This class is used to load configurations from Application.properties file It
 * stores the properties for connecting to messaging infrastructure
 * 
 * @author if993762
 *
 */
@Configuration
@PropertySource("/application.properties")
public class ServicesConfiguration {

	@Autowired
	private Environment env;

	private static final Logger LOG = LogManager.getLogger(ServicesConfiguration.class);

	private Properties props;

	@Bean
	ServletRegistrationBean myServletRegistration() {
		return new ServletRegistrationBean(new SmartPDFService(), "/smartpdf");
	}
	
	@Bean
	@Primary
	public IFastApiInvoker ifastApiInvoker() {
		String connector = env.getProperty("ifast.connector");
		if ("oe".equals(connector)) {
			return new IFastOEInvokerImpl();
		}else {
			return new IFastApiInvokerImpl();
		}
		
	}

	/**
	 * Method for loading properties file to configure the Sonic Messenger in
	 * order to relay XML payload accessing the back-end API
	 */
	@PostConstruct
	public void initializeProperties() {
		try {
			/*
			 * Load encrypted Sonic settings externally
			 */
			String key = env.getProperty("external.prop.key");
			StandardPBEStringEncryptor encryptor = new StandardPBEStringEncryptor();
			encryptor.setPassword(key);
			props = new EncryptableProperties(encryptor);
			props.load(new FileInputStream(PROP_PATH));
			//SonicMessengerSingleton.INSTANCE.configure(props);
			AppMsgClientFactory.INSTANCE.getAppMsgClient().configure(new MsgProperties("1", props));
		} catch (FileNotFoundException e) {
			LOG.error(e.getMessage(), e);
		} catch (IOException e) {
			LOG.error(e.getMessage(), e);
		}
	}

	public Properties getProperties() {
		return props;
	}
	
	public String getAppUrl() {
		return env.getProperty("ifast.connector.appurl");
	}
	
	public String getProcFile() {
		return env.getProperty("ifast.connector.procfile");
		
	}
	
    @SuppressWarnings("serial")
	@Bean
    public Jaxb2Marshaller jaxb2Marshaller() {
        Jaxb2Marshaller marshaller = new Jaxb2Marshaller();
        marshaller.setPackagesToScan("com.ifdsgroup.ifast.desktop.web.api.dto"); 

        marshaller.setMarshallerProperties(new HashMap<String, Object>() {{
          put(javax.xml.bind.Marshaller.JAXB_FORMATTED_OUTPUT, true);
        }});

        return marshaller;
    }	

}