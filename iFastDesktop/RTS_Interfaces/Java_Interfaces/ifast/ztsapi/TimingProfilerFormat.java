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

import java.util.Iterator;

/**
 * This provides an interface for TimingProfiler format implementations.
 * Implementations provide a format() method that takes a Profile as a 
 * parameter and returns the formatted string.
 * 
 * Implementations must be thread-safe.  Ideally this will mean that
 * that they will maintain no thread-specific attributes. Thread 
 * synchronization is not recommended.  
 */
public interface TimingProfilerFormat {
   /**
    * Formats the profile. Implementations normally output all 
    * mark intervals and walk down the profile hierarchy to report
    * sub-profiles. Implementations should be re-enterant since many
    * thread may make use of this class.
    * 
    * @param profile The profile to format.
    * 
    * @return the String formatted output for the profile.
    */
   String format(Profile profile);
}

abstract class AbstractTimingProfilerFormat implements TimingProfilerFormat {

   interface FormatBuffer {
      void formatHeader();
      void formatFooter();
      void formatProfileStart(Profile profile);
      void formatProfileEnd(Profile profile);
      void formatInterval(String name, long intervalTime, long elaspeTime);
   }

   abstract FormatBuffer getBuffer();

   public String format(Profile profile) {
      FormatBuffer buffer = getBuffer();
      buffer.formatHeader();
      format(buffer, profile);
      buffer.formatFooter();
      return buffer.toString();
   }
   
   void format(FormatBuffer buffer, Profile profile) {
      
      buffer.formatProfileStart(profile);
      
      long ti = profile.t0;
      Iterator iter = profile.iterator();
      while ( iter.hasNext() ) {
    	  ProfileItem item = (ProfileItem)iter.next();
         if ( item instanceof Interval ) {
            Interval interval = (Interval)item;
            buffer.formatInterval(interval.getName(), interval.ti-ti, interval.ti-profile.t0);
            ti = interval.ti;
         } else if ( item instanceof Profile ) {
            format(buffer, (Profile)item);
         }            
      }

      buffer.formatProfileEnd(profile);
   }
   
   
}

/**
 *  -------------------------------------------------------------------------
 *
 * CHANGE LOG:
 *
 *   $Log:   Y:/VCS/RTS Interfaces/Java Interfaces/ifast/ztsapi/TimingProfilerFormat.java-arc  $
 * 
 *    Rev 1.0   Oct 05 2009 13:12:06   yingz
 * Initial revision.
 * 
 *    Rev 1.1   Jul 16 2009 07:00:30   serverbu
 * Changed package to com.ifds.iFast.api
 * 
 *    Rev 1.0   Jul 15 2009 15:49:26   purdyech
 * Initial revision.
 * 
 *    Rev 1.2   Aug 19 2008 16:12:58   smithdav
 * Java 5 cleanup.
 * 
 *    Rev 1.1   Jul 22 2008 14:23:44   smithdav
 * Remove commented code and add javadocs.
 * 
 * 
 */
