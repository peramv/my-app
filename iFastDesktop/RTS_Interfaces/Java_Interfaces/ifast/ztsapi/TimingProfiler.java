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

import java.io.IOException;
import java.io.OutputStream;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Stack;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.dom4j.Document;
import org.dom4j.DocumentFactory;
import org.dom4j.Element;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.XMLWriter;

/**
 * <p>The TimimgProfiler class provided a static interface to a map of concrete TimingProfiles 
 * mapped by Thread.  That is, each running thread can have just one TimingProfiler at a time.</p>
 * 
 * <p>Concrete TimingProfilers maintain a hierarchy of profiles which are able to report elapse
 * time. Profiles can contain interval marks as well as child profiles. Interval marks are named 
 * and stamped with the system time the markInterval(String name) method is called. Profiles
 * are named and stamped with a start time when a startProfile method is called and stamped with
 * and end time when an endProfile is called.</p>
 * 
 * <p>Typically we use timing profiles to profile methods as in the code example below. Each method
 * uses the static get() or getSoft() methods to get the current threads profiler. The get() method
 * will create a new profiler for the thread if one does not exist.</p>
 * 
 * <p>Calls to getSoft() as in methodB() of our example will not create a new profile, but 
 * will return a "stub" profiler if one has not already been created. The stub profiler is a 
 * very light weight profile that has an empty implementation, and will not cause timings
 * to be collected or reported. The getSoft() methods is typically used in libraries classes
 * where it is up to the user of the library to use timing profiling or not.</p>
 * 
 * <p>The public myMethod() method in the example starts a profile with the name "myMethod"
 * and then calls two subsequent two methods. subsequent profiles started on the thread in these
 * methods will be added to this profile.  It is recommended that a try-finally structure be
 * used to ensure that the report is logged and the profiler is closed in the event of an exception.</p>
 *  
 * <code><pre>
 * class myClass {
 * 
 *    public void myMethod() {
 *       Logger logger = ...;
 *       TimingProfiler tp  = TimingProfiler.get();
 *       tp.startProfile("myMethod");
 *       try {
 *          this.mehtodA();
 *          this.methodB();
 *       } finally {
 *          tp.report(logger);
 *          TimingProfiler.close()
 *       }
 *    }
 * 
 *    private void methodA() {
 *       TimingProfiler tp  = TimingProfiler.get();
 *       tp.startProfile("methodA");
 *       try {
 *          ...
 *          tp.markInterval("mark A1");
 *          ...
 *          tp.markInterval("mark A2");
 *          ...
 *          tp.markInterval("mark A3");
 * 
 *       } finally {
 *          tp.endProfile();
 *       }
 *    }
 * }
 *  
 *    private void methodB() {
 *       TimingProfiler tp  = TimingProfiler.getSoft();
 *       tp.startProfile("methodB");
 *       try {
 *          ...
 *          tp.markInterval("mark B1");
 *          ...
 *          tp.markInterval("mark B2");
 *          ...
 *          tp.markInterval("mark B3");
 * 
 *       } finally {
 *          tp.endProfile();
 *       }
 *    }
 * } 
 * </pre></code>  
 */
public abstract class TimingProfiler 
{
   /**
    * Starts a new profile under the current profile. If there
    * is no current profile the new one will be added as the root
    * profile. 
    * 
    * @param name The name of the profile to start. 
    */
   public abstract void startProfile( String name );
   
   /**
    * Ends the current profile and makes the parent profile 
    * current.  If the current profile is the root profile, it
    * is ended and the profiler will be empty.
    */
   public abstract void endProfile();
   
   /**
    * End the current profile and generates a report on the
    * given logger. The log level will be Level.DEBUG if the DEBUG
    * level is enabled for the logger, otherwise it will be Level.INFO.
    * 
    * @param logger The log4j logger to which the report is written.
    */
   public abstract void endProfile(Logger logger);
   
   /**
    * End the current profile and generates a report on the
    * given logger and at the given level.
    * 
    * @param logger The log4j Logger to which the report is written.
    * @param level Thelog4j Level at which the report will be logged.
    */
   public abstract void endProfile(Logger logger, Level level);
   
   /**
    * Stamps the time of a new interval mark of the given name, and
    * adds it to the current profile.
    * 
    * @param name The name of the new interval mark.
    */
   public abstract void markInterval( String name );
   
   /**
    * Generates a report on the given logger for the current profile. 
    * The log level will be Level.DEBUG if the DEBUG level is enabled 
    * for the logger, otherwise it will be Level.INFO.
    * 
    * All opened profiles will remain open, and their elapse time
    * will use the current system time as the end time.
    * 
    * @param logger The log4j Logger to which the report is written.
    */
   public abstract void report(Logger logger);
   
   /**
    * Generates a report on the given logger and at the given level 
    * for the current profile.
    * 
    * All opened profiles will remain open, and their elapse time
    * will use the current system time as the end time.
    *  
    * @param logger The log4j Logger to which the report is written.
    * @param level Thelog4j Level at which the report will be logged.
    */
   public abstract void report(Logger logger, Level level);

   public abstract String getReportStr(TimingProfilerFormat formatter);
   
   protected void report(Profile profile, Logger logger) {
      if ( logger.isDebugEnabled() ) {
         report(profile, debugFormat, logger, Level.DEBUG);
      } else {
         report(profile, infoFormat, logger, Level.INFO);
      }
   }
   
   protected void report(Profile profile, Logger logger, Level level) {
      if ( logger.isEnabledFor(level)) {
         if ( level.isGreaterOrEqual(Level.INFO) ) {
            report(profile, infoFormat, logger, level);
         } else {
            report(profile, debugFormat, logger, level);
         }
      }
   }
   
   protected void report(Profile profile, TimingProfilerFormat formatter, Logger logger, 
                         Level level) {
      if ( logger.isEnabledFor(level)) {
         logger.log(level, formatter.format(profile));
      }
   }
   
   protected String getReportStr(Profile profile, TimingProfilerFormat formatter) {
      return formatter.format(profile);
   }
   
   private static final TimingProfiler STUB_PROFILER = new TimingProfiler() {
      public void startProfile( String profileName ) {}
      public void endProfile() {}
      public void endProfile(Logger logger) {}
      public void endProfile(Logger logger, Level level) {}
      public void markInterval( String intervalName ) {}
      public void report(Logger logger) {}
      public void report(Logger logger, Level level) {}
      public String getReportStr(TimingProfilerFormat formatter) { return ""; }
   };
 
   /**
    * A TimingProfileFormat implementation the formats to a compact, single-line text report.
    */
   public static final TimingProfilerFormat COMPACT_FORMAT = new AbstractTimingProfilerFormat() {
      AbstractTimingProfilerFormat.FormatBuffer getBuffer() {
         return new AbstractTimingProfilerFormat.FormatBuffer() {
            StringBuffer buffer = new StringBuffer();
            boolean isAfterInterval = false;
            public String toString() {
               return buffer.toString();
            }
            public void formatHeader() {
               buffer.append("Timing Profile: ");
            }
            public void formatFooter() {
            }
            public void formatProfileStart(Profile profile) {
               if ( !isAfterInterval ) {
                  buffer.append(" ");
               }
               buffer.append("{" + profile.getName() + ":" + profile.getElapseTime() 
                             + (profile.isEmpty() ? "" : " -"));
               isAfterInterval = false;
            }
            public void formatProfileEnd(Profile profile) {
               buffer.append(profile.isOpen() ? "*" : "}");
               isAfterInterval = false;
            }
            public void formatInterval(String name, long intervalTime, long elaspeTime){
               if ( isAfterInterval ) {
                  buffer.append(" | " + name + ":" + intervalTime);
               } else {
                  buffer.append(" " + name + ":" + intervalTime);
               }
               isAfterInterval = true;
            }
         };
      }
   };
   
   /**
    * A TimingProfileFormat implementation the formats to a readable, multi-line text report.
    */
   public static final TimingProfilerFormat LONG_FORMAT = new AbstractTimingProfilerFormat() {
      AbstractTimingProfilerFormat.FormatBuffer getBuffer() {
         return new AbstractTimingProfilerFormat.FormatBuffer() {
            StringBuffer buffer = new StringBuffer();
            int indentLevel = 0;
            public String toString() {
               return buffer.toString();
            }
            public void formatHeader() {
               buffer.append("Timing Profile Report...\n");
            }
            public void formatFooter() {
            }
            public void formatProfileStart(Profile profile) {
               indent();
               buffer.append((profile.isOpen() ? "*" : "+") + "Profile \"" + profile.getName() 
                             + "\": elapse(" + profile.getElapseTime()/1000000f + " ms).\n");
               ++indentLevel;
            }
            public void formatProfileEnd(Profile profile) {
               --indentLevel;
            }
            public void formatInterval(String name, long intervalTime, long elaspeTime) {
               indent();
               buffer.append("|Mark \"" + name + "\": interval(" + intervalTime/1000000f + " ms).\n");
            }
            private void indent() {
               for (int i=0; i <indentLevel; i++) {
                  buffer.append("|  ");
               }
            }
         };
      }
   };

   /**
    * A TimingProfileFormat implementation the formats compact XML.
    */
   public static final TimingProfilerFormat XML_FORMAT = new AbstractTimingProfilerFormat() {
      AbstractTimingProfilerFormat.FormatBuffer getBuffer() {
         return new AbstractTimingProfilerFormat.FormatBuffer() {
            DocumentFactory df = new DocumentFactory();
            Document document = null;
            Element currentElement = null;
            {
               document = df.createDocument();
            }
            public String toString() {
               StringWriter stringOut = new StringWriter();
               try {
                  OutputFormat format = OutputFormat.createCompactFormat();
                  format.setSuppressDeclaration(true);
                  XMLWriter writer =  new XMLWriter(stringOut, format);
                  writer.write(document);
                  writer.flush();
               } catch (IOException e ) {
               }
               return stringOut.toString();
            }
            public void formatHeader() {
               currentElement = df.createElement("timings");
               document.setRootElement(currentElement);
            }
            public void formatFooter() {
            }
            public void formatProfileStart(Profile profile) {
               Element profileElement = df.createElement("profile");
               profileElement.add(df.createAttribute(profileElement, "name", profile.getName()));
               profileElement.add(df.createAttribute(profileElement, "elapse", 
                                                     Long.toString(profile.getElapseTime())));
               currentElement.add(profileElement);
               currentElement = profileElement;
            }
            public void formatProfileEnd(Profile profile) {
               currentElement = currentElement.getParent();
            }
            public void formatInterval(String name, long intervalTime, long elaspeTime) {
               Element profileElement = df.createElement("mark");
               profileElement.add(df.createAttribute(profileElement, "name", name));
               profileElement.add(df.createAttribute(profileElement, "interval", 
                                                     Long.toString(intervalTime)));
               profileElement.add(df.createAttribute(profileElement, "elapse", 
                                                     Long.toString(elaspeTime)));
               currentElement.add(profileElement);
            }
         };
      }
   };
   
   private static TimingProfilerFormat debugFormat = LONG_FORMAT;
   private static TimingProfilerFormat infoFormat = XML_FORMAT;
   
   private static HashMap tpmap = new HashMap();
   
   /**
    * Get the timing profiler for the current thread if one
    * has already been opened using get(). Otherwise a "stub"
    * profiler will be returned. A stub profiler had an empty
    * implementation, so will do nothing when methods are called.
    * 
    * @return the profiler for the current thread or the stub profiler.
    */
   public static TimingProfiler getSoft() {
      Thread tpkey=Thread.currentThread();
      synchronized(tpmap) {
         TimingProfiler tp = (TimingProfiler)tpmap.get(tpkey);
         if ( tp==null ) {
            return STUB_PROFILER;
         } else {
            return tp;
         }
      }
   }
   
   /**
    * Get the timing profiler for the current thread if one
    * has already been opened using get(). If one has not
    * does not yet exist, a new concrete profiler will be created 
    * and stored. If this method is called, there must be a subsequent 
    * call to close().
    * 
    * @return the profiler for the current thread
    */
   public static TimingProfiler get() {
      Thread tpkey=Thread.currentThread();
      synchronized(tpmap) {
         TimingProfiler tp = (TimingProfiler)tpmap.get(tpkey);
         if ( tp==null ) {
            tp = new ConcreteTimingProfiler();
            tpmap.put(tpkey, tp);
         }
         return tp;
      }
   }
   
   /**
    * Close the timing profiler for the current thread. This
    * must be called once per thread if the get() method is called.
    * Once closed a subsequent call to get() open a new empty timing
    * profiler.
    */
   public static void close() {
      Thread tpkey=Thread.currentThread();
      synchronized(tpmap) {
         TimingProfiler tp = (TimingProfiler)tpmap.get(tpkey);
         if ( tp!=null ) {
            tpmap.remove(tpkey);
         }
      }
   }
   
   /**
    * Sets the format of debug reports. The default is LONG_FORMAT.
    * 
    * @param format The new format of debug reports.
    */
   public static void setDebugFormat(TimingProfilerFormat format) {
      debugFormat = format;
   }

   /**
    * Sets the format of info reports. The default is XML_FORMAT.
    * 
    * @param format The new format of info reports.
    */
   public static void setInfoFormat(TimingProfilerFormat format) {
      infoFormat = format;
   }
   
}



interface ProfileItem {
	String getName();
}

final class Interval implements ProfileItem {
   private final String name;
   final long ti;
   Interval (String name ) {
      this.name = name;
      this.ti = System.currentTimeMillis();
   }

   public String getName() {
      return name;
   }
   
}

final class Profile implements ProfileItem {
   private final String name;
   final long t0;
   private long tx = -1;
   private final ArrayList iList = new ArrayList();
   
   Profile(String name) {
      this.name = name;
      this.t0=System.currentTimeMillis();
   }
   
   void markInterval( String intervalName ) {
      iList.add(new Interval( intervalName ));
   }
   
   Profile addProfile( String profileName ) {
      Profile newProfile = new Profile(profileName); 
      iList.add(newProfile);
      return newProfile;
   }
   
   public String getName() {
      return name;
   }
   
   long getElapseTime() {
      return ( tx == -1 ) ? (System.currentTimeMillis()-t0)
                          : (tx-t0);
   }
   
   Iterator iterator() {
      return iList.iterator();
   }
   
   boolean isEmpty() {
      return iList.isEmpty();
   }
   
   boolean isOpen() {
      return (tx == -1);
   }
   
   void close() {
      tx = System.currentTimeMillis();
   }
}

final class ConcreteTimingProfiler extends TimingProfiler
{
   private final Stack profileStack = new Stack();
   
   ConcreteTimingProfiler() {
   }

   public void startProfile( String profileName ) {
      try {
         if ( profileStack.empty() ) {
            profileStack.push(new Profile(profileName));
         } else {
            profileStack.push(((Profile)profileStack.peek()).addProfile(profileName));
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
   }
   
   public void endProfile() {
      try {
         if (!profileStack.empty()) {
            ((Profile)profileStack.pop()).close();
         } else {
            System.err.println("TimingProfiler.endProfile() - no current profile.");
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
   }
   
   public void endProfile(Logger logger) {
      try {
         if (!profileStack.empty()) {
            Profile profile = (Profile)profileStack.pop();
            profile.close();
            report(profile, logger);
         } else {
            System.err.println("TimingProfiler.endProfile(Logger) - no current profile.");
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
   }
   
   public void endProfile(Logger logger, Level level) {
      try {
         if (!profileStack.empty()) {
            Profile profile = (Profile)profileStack.pop();
            profile.close();
            report(profile, logger, level);
         } else {
            System.err.println("TimingProfiler.endProfile(Logger, Level) - no current profile.");
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
   }
   
   public void markInterval( String intervalName ) {
      try {
         if (!profileStack.empty()) {
            ((Profile)profileStack.peek()).markInterval(intervalName);
         } else {
            System.err.println("TimingProfiler.markInterval(\"" + intervalName 
                               + "\") - no current profile.");
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
   }
   
   public void report(Logger logger) {
      try {
         if (!profileStack.empty()) {
            report((Profile)profileStack.peek(), logger);
         } else {
            System.err.println("TimingProfiler.report(Logger) - no current profile.");
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
   }
   
   public void report(Logger logger, Level level) {
      try {
         if (!profileStack.empty()) {
            report((Profile)profileStack.peek(), logger, level);
         } else {
            System.err.println("TimingProfiler.report(Logger, Level) - no current profile.");
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
   }
   
   public String getReportStr(TimingProfilerFormat formatter) { 
      try {
         if (!profileStack.empty()) {
            return getReportStr((Profile)profileStack.peek(), formatter);
         } else {
            System.err.println("TimingProfiler.getReportStr(TimingProfilerFormat) - no current profile.");
         }
      } catch(Exception e) {
         System.err.println("TimingProfiler error.");
         e.printStackTrace();
      }
      return "";
   }

}

/**
 *  -------------------------------------------------------------------------
 *
 * CHANGE LOG:
 *
 *   $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/TimingProfiler.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:11:58   yingz
 * Initial revision.
 * 
 *    Rev 1.1   Jul 16 2009 07:00:18   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:50:40   purdyech
 * Initial revision.
 * 
 *    Rev 1.12   Apr 22 2009 15:59:56   smithdav
 * Use high resolution timer, and ad getReportStr.
 * 
 *    Rev 1.11   Dec 05 2008 15:04:06   smithdav
 * Fixed syncronization bug. Remove implicit Root Profile.
 * 
 *    Rev 1.10   Aug 19 2008 16:12:58   smithdav
 * Java 5 cleanup.
 * 
 *    Rev 1.9   Jul 22 2008 14:23:44   smithdav
 * Remove commented code and add javadocs.
 * 
 *    Rev 1.8   Jul 21 2008 20:17:52   smithdav
 * Use TimingProfilerFormat implementations and add an XML format using dom4j.
 * 
 *    Rev 1.7   Jul 21 2008 14:19:36   smithdav
 * Clean upr reporting.
 * 
 *    Rev 1.6   Jul 21 2008 11:28:18   smithdav
 * Add compact report format.
 * 
 *    Rev 1.5   Jul 18 2008 12:39:58   smithdav
 * TimingProfiler improvements.
 * 
 *    Rev 1.4   Jul 17 2008 20:36:42   smithdav
 * Force the creation of a root profile.
 * 
 *    Rev 1.3   Jul 17 2008 19:38:42   smithdav
 * Timing profiler changes.
 * 
 *    Rev 1.2   Apr 28 2008 17:59:08   smithdav
 * Add constructor to allow users to select other log levels. The existing constructor defaults to debug as before.
 * 
 *    Rev 1.1   Aug 27 2007 17:57:50   smithdav
 * Improvements.
 * 
 *    Rev 1.0   Aug 13 2007 21:49:08   smithdav
 * Initial revision.
 * 
 */
