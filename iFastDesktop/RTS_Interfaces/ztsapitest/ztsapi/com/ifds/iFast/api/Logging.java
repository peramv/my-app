/**
 *  -------------------------------------------------------------------------
 *                                 Copyright
 *
 *               International Financial Data Services Limited 2005
 *                            All rights reserved.
 *
 *
 *  No part of this document may be reproduced, stored in a retrieval
 *  system, or transmitted, in any form or by any means, electronic,
 *  mechanical, photocopying, networking or otherwise, without the prior
 *  written permission of International Financial Data Services Limited.
 *
 *  The computer system, procedures, data bases, and programs created and
 *  maintained by International Financial Data Services Limited are proprietary
 *  in nature and as such are confidential. Any unauthorised use, misuse, or
 *  disclosure of such items or information may result in civil liabilities
 *  and may be subject to criminal penalties under the applicable laws.
 *  -------------------------------------------------------------------------
 *
 */
package com.ifds.iFast.api;

import java.io.File;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.FileAppender;
import org.apache.log4j.PatternLayout;

/**
 * @author smithdav
 *
 * Static helper methods for configuring log4j Loggers in a
 * consistent manner.
 */
public class Logging {

   private static final PatternLayout defaultLayout = new PatternLayout();
   private static File logDir = new File(".");
   private static boolean configured = false;

   static {
      defaultLayout.setConversionPattern( "%d{dd MMM yyyy HH:mm} %6p  - %m%n" );
   }
   
   
   /**
    * Set the log directory for all file appenders. This must be called
    * before the configure methods. If unset, the current working directory
    * is used.
    * 
    * @param dir 
    *       The directory to which all file logs will be written.   
    */
   public static void setLogDir( File dir ) {
      if ( configured ) {
         throw new IllegalStateException("Cannot set log directory after a call to configure");
      }
      if ( !dir.exists() ) {
         dir.mkdirs();
      }
      logDir = dir;
   }
   
   /**
    * Set the log directory for all file appenders. This must be called
    * before the configure methods. If this property is set after 
    * configure, any file appenders it created will remain  
    * 
    * If unset, the current working directory is used.
    * 
    * @param dirStr 
    *       The directory to which all file logs will be written.   
    */
   public static void setLogDir( String dirStr ) {
      setLogDir(new File(dirStr));
   }
   
   /**
    * Return the currently set log directory.
    * 
    * @return 
    *       The log directory.
    */
   public static File getLogDir() {
      return logDir;
   }
   
   /**
    * Configures a logger for the com.ifdsgroup.msg package.
    * It will have report at the DEBUG level and will have
    * a ConsoleAppender and a FileAppender to the MsgDebug.log
    * in the logDir.
    * 
    * Only one configure method can be called.
    * 
    */
   public static void configure() {
      if ( configured ) {
         throw new IllegalStateException("Only one call to configured is allowed.");
      }
      try {
         Logger logger = getMsgLogger(Level.DEBUG);
         configureConsole(logger);
         configureFile(logger, new File(logDir, "MsgDebug.log"));
      } catch(Exception e) {
         logLastResort( e );
      }
   }
   
   /**
    * Configures a logger for the given class' package with a
    * reporting level of INFO. Two appender will be associated 
    * with this logger -- a ConsoleAppender and a FileAppender.
    * 
    * A logger for the entire com.ifdsgroup.msg package will 
    * also be created with a reporting level of DEBUG and a 
    * single FileAppender to MsgDebug.log.
    * 
    * Only one configure method can be called.
    * 
    * @param appClass
    *       A class object whos package will be used for the logger.
    */
   public static void configure(Class appClass) {
      configure(appClass, Level.INFO);
   }
   
   /**
    * Configures a logger for the given class' package with the given 
    * reporting level. Two appender will be associated with this 
    * logger -- a ConsoleAppender and a FileAppender.
    * 
    * A logger for the entire com.ifdsgroup.msg package will 
    * also be created with a reporting level of DEBUG and a 
    * single FileAppender to MsgDebug.log.
    * 
    * Only one configure method can be called.
    * 
    * @param appClass
    *       A class object whos package will be used for the logger.
    * @param appLevel
    *       The reporting level for the logger.
    */
   public static void configure(Class appClass, Level appLevel) {
      if ( configured ) {
         throw new IllegalStateException("Only one call to configured is allowed.");
      }
      try {
         Logger logger = getAppLogger(appClass, appLevel);
         configureConsole(logger);
         configureFile(logger, new File(logDir, appClass.getName() + ".log"));
         
         logger = getMsgLogger(Level.DEBUG);
         configureFile(logger, new File(logDir, "MsgDebug.log"));
      } catch(Exception e) {
         logLastResort( e );
      }
      configured=true;
   }

   /**
    * Creates an adhoc logger of the given name with 
    * the given reporting level. A single FileAppender
    * is created to a file in the logDir having a name 
    * of name.log
    * 
    * 
    * @param name
    *       The name of the logger.
    * @param level
    *       The reporting level for the logger.
    * @return
    *       The created Logger.
    */
   public static Logger configureAdhoc(String name, Level level) {
      Logger logger = Logger.getLogger(name);
      logger.setLevel(level);
      configureFile(logger, new File(logDir, name + ".log"));
      return logger;
   }
   
   private static void configureConsole(Logger logger) {
      logger.addAppender( new ConsoleAppender(defaultLayout) );
   }
   
   
   private static void configureFile(Logger logger, File logFile) {
      try {            
         File logFileDir = logFile.getParentFile();
         if ( logFileDir!=null && !logFileDir.exists() ) {
            logFileDir.mkdirs();
         } 
         logger.addAppender(new FileAppender(defaultLayout, logFile.getAbsolutePath(), true ));
      }  catch(Exception e) {
         logger.error("Unable to add File Appender", e);
      }
   }
   
   private static void logLastResort( Throwable e ) {
      Logger rootLogger = Logger.getRootLogger();
      rootLogger.addAppender(new ConsoleAppender(new PatternLayout()));
      rootLogger.error("Unable to configure loggers.", e);
   }
   
   public static Logger getMsgLogger(Level level) {
      if ( !Logging.class.getPackage().getName().equals("com.ifds.iFast.api") ) {
         throw new IllegalStateException("Logging has invalid package.");
      }
      Logger logger = Logger.getLogger("com.ifds.iFast.api");
      logger.setLevel(level);

      return logger;
   }
   
   public static Logger getAppLogger(Class appClass, Level level) {
      Logger logger = Logger.getLogger(appClass.getPackage().getName());
      logger.setLevel(level);

      return logger;
   }
   
   public static PatternLayout getDefaultLayout() {
      return defaultLayout;
   }
   
}

/**
 *  -------------------------------------------------------------------------
 *
 * CHANGE LOG:
 *
 *   $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/Logging.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:10:52   yingz
 * Initial revision.
 * 
 *    Rev 1.2   Jul 16 2009 07:26:40   purdyech
 * Changed references to com.ifdsgroup.* to com.ifds.iFast.api
 * 
 *    Rev 1.1   Jul 16 2009 06:57:42   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:34:06   purdyech
 * Initial revision.
 * 
 *    Rev 1.6   Aug 19 2008 16:12:58   smithdav
 * Java 5 cleanup.
 * 
 *    Rev 1.5   May 22 2008 17:17:32   smithdav
 * javadoc fixes.
 * 
 *    Rev 1.4   May 07 2008 09:28:04   smithdav
 * Add javadoc and flag to prevent duplicate configuration.
 * 
 *    Rev 1.3   Apr 17 2008 11:42:52   smithdav
 * Fix bug in static configure method that forced Level.DEBUG.  Now uses the appLevel parameter.
 * 
 *    Rev 1.2   Sep 04 2007 11:29:46   smithdav
 * Fixes.
 * 
 *    Rev 1.1   Aug 27 2007 17:57:50   smithdav
 * Improvements.
 * 
 *    Rev 1.0   Aug 13 2007 21:49:08   smithdav
 * Initial revision.
 * 
 */
