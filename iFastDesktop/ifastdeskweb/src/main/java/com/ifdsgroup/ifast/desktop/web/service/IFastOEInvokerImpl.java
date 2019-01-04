package com.ifdsgroup.ifast.desktop.web.service;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants;
import com.ifdsgroup.ifast.desktop.web.core.config.ServicesConfiguration;
import com.ifdsgroup.ifast.desktop.web.exception.DesktopWebSystemException;
import com.progress.open4gl.ConnectException;
import com.progress.open4gl.Open4GLException;
import com.progress.open4gl.SystemErrorException;
import com.progress.open4gl.javaproxy.Connection;
import com.progress.open4gl.javaproxy.OpenAppObject;
import com.progress.open4gl.javaproxy.ParamArray;
import com.progress.open4gl.javaproxy.ParamArrayMode;

@Repository
public class IFastOEInvokerImpl implements IFastApiInvoker {
	
	Logger logger = Logger.getLogger(this.getClass());

	   private final Object connectionLock = new Object();
	   private Connection connection = null;
	   private Map<String,Connection> connectionMap = new ConcurrentHashMap<>();
	   
	   @Autowired
	   private ServicesConfiguration servicesConfig;
	   
	   /**
	    * Method to attempt to make sure that the esbadaptr is connected to the
	    * AppServer. It is intended that this method will be called whenever the
	    * 'client' object is needed
	    * 
	    * @throws ConnectException
	    * @throws SystemErrorException
	    * @throws Open4GLException
	    * @throws IOException
	    */
	   private void ensureConnection(String appServiceURL)  {
	      if (null == connectionMap.get(appServiceURL)) {
	               Connection connection = new Connection(appServiceURL, null, null, null);
	               connection.setSessionModel(Connection.SM_SESSION_FREE);
	               connectionMap.put(appServiceURL, connection);

	      }
	   }	   
	   
	   
	  public String apply(String requestXml, String ifastSessionToken, String slotName)  throws DesktopWebSystemException{		  
		  
		  Map<String,String> headers = new HashMap<String,String>();
		  headers.put(DesktopWebConstants.IFAST_SESSION_TOKEN, ifastSessionToken);
		  headers.put(DesktopWebConstants.IFAST_SLOT_NAME, slotName);
		  String headerString = buildHeaderString(headers);
		  
		  Response response;
		  try {
			  response = send(headerString, requestXml);
		  } catch (Exception e) {
			  throw new DesktopWebSystemException(e.getMessage(), e.getCause());
		  } 
		  
		  return response.msgtxt;
	  }
	   
	   
	   public Response send(String hdrVal, String msgtxt) throws Open4GLException, IOException {
	      
         ParamArray oeparams = setParams(hdrVal, msgtxt);
         long invocationTime = -1;
         try {
            ensureConnection(servicesConfig.getAppUrl()); 
            invocationTime = send(oeparams);    
         } catch (com.progress.open4gl.Open4GLException e) {
            logger.info("Received Open4GLException.  Retrying in case AppServer was restarted.");
            oeparams = setParams(hdrVal, msgtxt);
            invocationTime = send(oeparams);          
         }

         hdrVal = (String) oeparams.getOutputParameter(3);         
         msgtxt = (String) oeparams.getOutputParameter(2);
         return new Response(hdrVal, msgtxt, invocationTime);
	      

	   }
	   
	   public static class Response {
	      public final String hdrVal;
	      public final String msgtxt;
	      public final long invocationTime;
	      
	      Response(String hdrVal, String msgtxt, long invocationTime) {
	         this.hdrVal=hdrVal;
	         this.msgtxt=msgtxt;
	         this.invocationTime=invocationTime;
	      }
	      
	   }

	   public void close() {
	      if (null != connection) {
	         synchronized(connectionLock) {
	            if (null != connection) {
	               try {
	                  connection.releaseConnection();
	               } catch (Open4GLException e) {
	                  logger.error("Failed to release AppServer connection.", e);
	               }
	            }
	         }
	      }
	   }

	   public void finalize() {
	      close();
	   }
	   
	   
	   private ParamArray setParams(String hdrVal, String msgtxt) throws Open4GLException {
	      ParamArray oeparams = new ParamArray(4);
	      oeparams.addLongchar(0,  msgtxt, ParamArrayMode.INPUT);
	      oeparams.addCharacter(1, hdrVal, ParamArrayMode.INPUT);
	      oeparams.addLongchar(2,  null, ParamArrayMode.OUTPUT);
	      oeparams.addCharacter(3, null, ParamArrayMode.OUTPUT);
	      return oeparams;
	   }
	   
	   private long send(ParamArray oeparams) throws Open4GLException, IOException {
	      OpenAppObject client = new OpenAppObject(connectionMap.get(servicesConfig.getAppUrl()), "");
	      long startTS = System.nanoTime();
	      long invocationTime = -1;
	      try {
	         client.runProc(servicesConfig.getProcFile(), oeparams);
	      } finally {
	         invocationTime = System.nanoTime() - startTS;
	         client._release();
	      }
	      return invocationTime;
	   }
	   
	   private String buildHeaderString(Map<String,String> values) {
		   StringBuilder stringBuilder = new StringBuilder();
		   for (String key: values.keySet()) {
			   if (stringBuilder.length() != 0) {
				   stringBuilder.append("|");
			   }
			   stringBuilder.append(key);
			   stringBuilder.append("=");
			   stringBuilder.append(values.get(key));
		   }
		   
		   return stringBuilder.toString();
		   
		   
	   }
	

}
