package com.ifds.iFast.api;

import java.io.UnsupportedEncodingException;
import java.util.Properties;

/**
 * SonicManager is a singleton initialized when it is loaded. It gets SonicMQ
 * config using JavaAPIConfig and creates the producer pool based on the config
 * for synchronized call to ifast via SonicMQ
 */
final public class SonicManager {
   private static SonicManager instance = null;

   private JavaAPIConfig apicfg = null;
   private Producer producer = null;

   private void validateProperty( String propName ) throws SonicConfigException {
      validateProperty(propName, false);
   }
   private void validateProperty( String propName, boolean bAllowBlank ) throws SonicConfigException {
      if (System.getProperty(propName) == null ) {
         throw new SonicConfigException( "SonicMQ Configuration Error:  System Property " + propName + " is not set.");
      }
      if( System.getProperty(propName) == "" && !bAllowBlank ) {
         throw new SonicConfigException( "SonicMQ Configuration Error:  System Property " + propName + " can not have blank value.");
      }
   }

   private SonicManager() throws SonicConfigException, Exception {
      try {
         apicfg = new JavaAPIConfig();
         System.setProperty(JavaAPIConfig.ZTS_SONIC_TIMEOUT, Integer.toString(apicfg.getTimeout()));
         System.setProperty(JavaAPIConfig.ZTS_SSL_CERTS_DIR, apicfg.getSSL_CA_CERTIFICATES_DIR());
         System.setProperty(JavaAPIConfig.ZTS_SSL_CERTS_CHAIN, apicfg.getSSL_CERTIFICATE_CHAIN());
         System.setProperty(JavaAPIConfig.ZTS_SSL_CERTS_CHAIN_FORM, apicfg.getSSL_CERTIFICATE_CHAIN_FORM());
         System.setProperty(JavaAPIConfig.ZTS_SSL_PRIVATE_KEY, apicfg.getSSL_PRIVATE_KEY());
         System.setProperty(JavaAPIConfig.ZTS_BROKER_URL, apicfg.getBrokerurl());
         System.setProperty(JavaAPIConfig.ZTS_INQUIRY_Q, apicfg.getInqQue());
      } 
      catch( SonicConfigException e ) {
         System.out.println("Error reading JavaAPIConfig file.  Using existing System.properties instead");
      }

      if( System.getProperty(JavaAPIConfig.ZTS_SONIC_TIMEOUT) == null ) {
         System.setProperty(JavaAPIConfig.ZTS_SONIC_TIMEOUT, "30000");
      }
      validateProperty(JavaAPIConfig.ZTS_BROKER_URL );
      validateProperty(JavaAPIConfig.ZTS_INQUIRY_Q );
      validateProperty(JavaAPIConfig.ZTS_SSL_CERTS_DIR );
      validateProperty(JavaAPIConfig.ZTS_SSL_CERTS_CHAIN );
      validateProperty(JavaAPIConfig.ZTS_SSL_CERTS_CHAIN_FORM );
      validateProperty(JavaAPIConfig.ZTS_SSL_PRIVATE_KEY );
      validateProperty(JavaAPIConfig.ZTS_SSL_PRIVATE_KEY_PASSWORD );
      validateProperty(JavaAPIConfig.ZTS_SONIC_USER_ID );
      validateProperty(JavaAPIConfig.ZTS_SONIC_PASSWORD, true );
      producer = new SonicProducerPool(
         1, 
         new SonicProducerTarget(
            System.getProperty(JavaAPIConfig.ZTS_BROKER_URL),
            System.getProperty(JavaAPIConfig.ZTS_INQUIRY_Q)),
         System.getProperty(JavaAPIConfig.ZTS_SONIC_USER_ID), 
         System.getProperty(JavaAPIConfig.ZTS_SONIC_PASSWORD) );
   }

   public Object clone() throws CloneNotSupportedException {
      // make sure SonicManager is a singleton
      throw new CloneNotSupportedException();
   }

   synchronized public static void init() {
      try {
         if (instance == null)
            instance = new SonicManager();
      } catch (SonicConfigException e) {
         e.printStackTrace();
         System.exit(1);
      } catch (Exception e1) {
         e1.printStackTrace();
         System.exit(1);
      }
   }

   synchronized public static void close() {
      try {
         if (instance != null &&
	     instance.producer != null ) {
	     instance.producer.close();
	 }
      } catch (Exception e1) {
         e1.printStackTrace();
         System.exit(1);
      }
   }

   /**
    * @return the SonicManager instance
    */
   public static SonicManager getInstance() {
      return instance;
   }

   /**
    * This method makes synchronized call to ifast via a producer from producer
    * pool
    * 
    * @param reqByte
    *            byte send to SonicMQ
    * @param routingInstruction
    *            name of Company or Slot to route message to
    * @return byte received from SonicMQ
    * @throws UnsupportedEncodingException
    * @throws ProducerException
    * @throws ProducerClosedException
    */
   public byte[] sendReceive(final byte[] reqByte, String routingInstruction )
         throws UnsupportedEncodingException, ProducerException,
         ProducerClosedException {

      String encStr = new String(reqByte, "ISO8859-1");

      Properties properties = new Properties();
      properties.setProperty("IFAST_SLOT_NAME", routingInstruction);

      int iTimeout = Integer.parseInt( System.getProperty(JavaAPIConfig.ZTS_SONIC_TIMEOUT) );
      String res = producer.sendReceive(encStr, properties, iTimeout );

      byte[] decByte = res.getBytes("ISO8859-1");

      // modify the end of response from '\0' to '\n' for inputstream
      if (decByte.length > 1)
         decByte[decByte.length - 1] = '\n';

      return decByte;

   }

}
