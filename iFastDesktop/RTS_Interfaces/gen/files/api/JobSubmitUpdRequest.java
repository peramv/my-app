// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Job Submission request.
 * For additional view information see <A HREF="../../../../viewspecs/JobSubmitUpd.doc">JobSubmitUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class JobSubmitUpdRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Flag indicating whether db is to be updated or inquire only member variable.
    */
   private Boolean _UpdMode = new Boolean(false);
            
   /**
    * Scheduled run  date member variable.
    */
   private Date _RunDate = null;
            
   /**
    * Scheduled run time member variable.
    */
   private String _RunTime = "";
            
   /**
    * Job  Name member variable.
    */
   private String _JobName = "";
            
   /**
    * Printer Name member variable.
    */
   private String _PrinterName = "";
            
   /**
    * Flag indicating if job is to be scheduled member variable.
    */
   private Boolean _ToBeScheduled = new Boolean(false);
            
   /**
    * Flag indicating if job is to be run on-line member variable.
    */
   private Boolean _RunOnLine = new Boolean(false);
            
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Parameter Type member array.
    */
   private String[] _ParamType = new String[25];
            
   /**
    * Parameter Value member array.
    */
   private String[] _ParamValue = new String[25];
            
   /**
    * field indicating whether Parameter should be included or excluded in search criteria member array.
    */
   private Boolean[] _Include = new Boolean[25];
            
   /**
    * Record Type member array.
    */
   private String[] _RecType = new String[25];
            

   /**
    * Constructs the JobSubmitUpdRequest object.
    * 
    */
   JobSubmitUpdRequest()
   {
      super ( 220 );
   }

   /**
    * Constructs the JobSubmitUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   JobSubmitUpdRequest( String hostEncoding )
   {
      super ( 220, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Flag indicating whether db is to be updated or inquire only field for the request.
    * 
    * @param value  Value that the Flag indicating whether db is to be updated or inquire only will be set to.
    */
   public final void setUpdMode( Boolean value )
   {
      assertUnsent();
      _UpdMode = value;
   }
	
   /**
    * Sets the Scheduled run  date field for the request.
    * 
    * @param value  Value that the Scheduled run  date will be set to.
    */
   public final void setRunDate( Date value )
   {
      assertUnsent();
      _RunDate = value;
   }
	
   /**
    * Sets the Scheduled run time field for the request.
    * 
    * @param value  Value that the Scheduled run time will be set to.
    */
   public final void setRunTime( String value )
   {
      assertUnsent();
      _RunTime = value;
   }
	
   /**
    * Sets the Job  Name field for the request.
    * 
    * @param value  Value that the Job  Name will be set to.
    */
   public final void setJobName( String value )
   {
      assertUnsent();
      _JobName = value;
   }
	
   /**
    * Sets the Printer Name field for the request.
    * 
    * @param value  Value that the Printer Name will be set to.
    */
   public final void setPrinterName( String value )
   {
      assertUnsent();
      _PrinterName = value;
   }
	
   /**
    * Sets the Flag indicating if job is to be scheduled field for the request.
    * 
    * @param value  Value that the Flag indicating if job is to be scheduled will be set to.
    */
   public final void setToBeScheduled( Boolean value )
   {
      assertUnsent();
      _ToBeScheduled = value;
   }
	
   /**
    * Sets the Flag indicating if job is to be run on-line field for the request.
    * 
    * @param value  Value that the Flag indicating if job is to be run on-line will be set to.
    */
   public final void setRunOnLine( Boolean value )
   {
      assertUnsent();
      _RunOnLine = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Parameter Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Parameter Type will be set to.
    */
   public final void setParamType( int index, String value )
   {
      assertUnsent();
      _ParamType[index] = value;
   }
	
   /**
    * Sets the Parameter Value field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Parameter Value will be set to.
    */
   public final void setParamValue( int index, String value )
   {
      assertUnsent();
      _ParamValue[index] = value;
   }
	
   /**
    * Sets the field indicating whether Parameter should be included or excluded in search criteria field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the field indicating whether Parameter should be included or excluded in search criteria will be set to.
    */
   public final void setInclude( int index, Boolean value )
   {
      assertUnsent();
      _Include[index] = value;
   }
	
   /**
    * Sets the Record Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Record Type will be set to.
    */
   public final void setRecType( int index, String value )
   {
      assertUnsent();
      _RecType[index] = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _UpdMode );
      requestBuffer.appendField( _RunDate );
      requestBuffer.appendField( _RunTime );
      requestBuffer.appendField( _JobName );
      requestBuffer.appendField( _PrinterName );
      requestBuffer.appendField( _ToBeScheduled );
      requestBuffer.appendField( _RunOnLine );
      encodeOverrideRepeatsField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _ParamType[x] );
         requestBuffer.appendField( _ParamValue[x] );
         requestBuffer.appendField( _Include[x] );
         requestBuffer.appendField( _RecType[x] );
      }
   }

}

