package com.ifds.iFast.api;

import java.io.File;

import org.dom4j.Document;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;

/**
 * This class retrives SonicMQ config from xml file and 
 * provide interface to access config data. 
 * The filename is specified as java VM argument:
 * -DAPICfg=[config file location] 
 */
final public class JavaAPIConfig {
   public final static String ZTS_SEPARATOR = "ZTS.Separator";
   public final static String ZTS_BROKER_URL = "ZTS.BrokerUrl";
   public final static String ZTS_INQUIRY_Q = "ZTS.InquiryQ";
   public final static String ZTS_SONIC_USER_ID = "ZTS.SonicUserId";
   public final static String ZTS_SONIC_PASSWORD = "ZTS.SonicPassword";
   public final static String ZTS_SONIC_TIMEOUT = "ZTS.SonicTimeout";

   // The names of these properties are dictated by Sonic
   public final static String ZTS_SSL_CERTS_DIR = "SSL_CA_CERTIFICATES_DIR";
   public final static String ZTS_SSL_CERTS_CHAIN = "SSL_CERTIFICATE_CHAIN";
   public final static String ZTS_SSL_CERTS_CHAIN_FORM = "SSL_CERTIFICATE_CHAIN_FORM";
   public final static String ZTS_SSL_PRIVATE_KEY = "SSL_PRIVATE_KEY";
   public final static String ZTS_SSL_PRIVATE_KEY_PASSWORD = "SSL_PRIVATE_KEY_PASSWORD";


   String id, brokerurl, inqQue, SEPARATOR, SSL_CA_CERTIFICATES_DIR,
   SSL_CERTIFICATE_CHAIN,
   SSL_PRIVATE_KEY,
   SSL_CERTIFICATE_CHAIN_FORM;

   String mdb;
   public String getMdb() { return this.mdb; }
   public void setMdb(String mdb) { this.mdb = mdb; }

   public String getSEPARATOR() {
      return SEPARATOR;
   }

   public void setSEPARATOR(String separator) {
      SEPARATOR = separator;
   }

   public String getSSL_CA_CERTIFICATES_DIR() {
      return SSL_CA_CERTIFICATES_DIR;
   }

   public void setSSL_CA_CERTIFICATES_DIR(String ssl_ca_certificates_dir) {
      SSL_CA_CERTIFICATES_DIR = ssl_ca_certificates_dir;
   }

   public String getSSL_CERTIFICATE_CHAIN() {
      return SSL_CERTIFICATE_CHAIN;
   }

   public void setSSL_CERTIFICATE_CHAIN(String ssl_certificate_chain) {
      SSL_CERTIFICATE_CHAIN = ssl_certificate_chain;
   }

   public String getSSL_PRIVATE_KEY() {
      return SSL_PRIVATE_KEY;
   }

   public void setSSL_PRIVATE_KEY(String ssl_private_key) {
      SSL_PRIVATE_KEY = ssl_private_key;
   }

   public String getSSL_CERTIFICATE_CHAIN_FORM() {
      return SSL_CERTIFICATE_CHAIN_FORM;
   }

   public void setSSL_CERTIFICATE_CHAIN_FORM(String ssl_certificate_chain_form) {
      SSL_CERTIFICATE_CHAIN_FORM = ssl_certificate_chain_form;
   }

   int timeout;

   public String getBrokerurl() {
      return brokerurl;
   }

   public void setBrokerurl(String brokerurl) {
      this.brokerurl = brokerurl;
   }

   public int getTimeout() {
      return timeout;
   }

   public void setTimeout(int timeout) {
      this.timeout = timeout;
   }

   public String getId() {
      return id;
   }

   public void setId(String id) {
      this.id = id;
   }

   public String getInqQue() {
      return inqQue;
   }

   public void setInqQue(String inqQue) {
      this.inqQue = inqQue;
   }

   public JavaAPIConfig() throws SonicConfigException {
      try {
         File cfgxml = new File(System.getProperty("APICfg"));
         SAXReader reader = new SAXReader();
         Document document = reader.read(cfgxml);

         Node node = document.selectSingleNode("//SonicMQS/SonicMQ");

         setId(node.valueOf("@id"));
         setMdb(node.valueOf("mdb"));
         setBrokerurl(node.valueOf("brokerurl"));
         setInqQue(node.valueOf("inqQue"));
         setSEPARATOR(node.valueOf("SEPARATOR"));
         setTimeout(new Long(node.valueOf("timeout")).intValue());
         setSSL_CA_CERTIFICATES_DIR(node.valueOf("SSL_CA_CERTIFICATES_DIR"));
         setSSL_CERTIFICATE_CHAIN(node.valueOf("SSL_CERTIFICATE_CHAIN"));
         setSSL_CERTIFICATE_CHAIN_FORM(node.valueOf("SSL_CERTIFICATE_CHAIN_FORM"));
         setSSL_PRIVATE_KEY(node.valueOf("SSL_PRIVATE_KEY"));
      } catch (Exception e) {
         throw new SonicConfigException();
      }
   }

}
