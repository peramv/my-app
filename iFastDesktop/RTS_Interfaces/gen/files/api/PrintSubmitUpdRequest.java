// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Report Printing Submission request.
 * For additional view information see <A HREF="../../../../viewspecs/PrintSubmitUpd.doc">PrintSubmitUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class PrintSubmitUpdRequest extends IFastRequest implements Serializable
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
    * Printer Name member variable.
    */
   private String _PrinterName = "";
            
   /**
    * File Path member variable.
    */
   private String _FilePath = "";
            
   /**
    * Output File Name member variable.
    */
   private String _OutputFileName = "";
            

   /**
    * Constructs the PrintSubmitUpdRequest object.
    * 
    */
   PrintSubmitUpdRequest()
   {
      super ( 225 );
   }

   /**
    * Constructs the PrintSubmitUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   PrintSubmitUpdRequest( String hostEncoding )
   {
      super ( 225, hostEncoding );
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
    * Sets the File Path field for the request.
    * 
    * @param value  Value that the File Path will be set to.
    */
   public final void setFilePath( String value )
   {
      assertUnsent();
      _FilePath = value;
   }
	
   /**
    * Sets the Output File Name field for the request.
    * 
    * @param value  Value that the Output File Name will be set to.
    */
   public final void setOutputFileName( String value )
   {
      assertUnsent();
      _OutputFileName = value;
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
      requestBuffer.appendField( _PrinterName );
      requestBuffer.appendField( _FilePath );
      requestBuffer.appendField( _OutputFileName );
   }

}

