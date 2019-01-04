// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * RESP Diploma Get PAC Dates request.
 * For additional view information see <A HREF="../../../../viewspecs/GetPacDates.doc">GetPacDates.doc</A>.
 * 
 * @author RTS Generated
 */
public class GetPacDatesRequest extends IFastRequest implements Serializable
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
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * AcctCommitMstrUUID member variable.
    */
   private String _AcctCommitMstrUUID = "";
            
   /**
    * Original PAC Effective Date member variable.
    */
   private Date _PACDeff = null;
            
   /**
    * New PAC Draw Date member variable.
    */
   private Date _PACDrawDeff = null;
            

   /**
    * Constructs the GetPacDatesRequest object.
    * 
    */
   GetPacDatesRequest()
   {
      super ( 440 );
   }

   /**
    * Constructs the GetPacDatesRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   GetPacDatesRequest( String hostEncoding )
   {
      super ( 440, hostEncoding );
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
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
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
    * Sets the AcctCommitMstrUUID field for the request.
    * 
    * @param value  Value that the AcctCommitMstrUUID will be set to.
    */
   public final void setAcctCommitMstrUUID( String value )
   {
      assertUnsent();
      _AcctCommitMstrUUID = value;
   }
	
   /**
    * Sets the Original PAC Effective Date field for the request.
    * 
    * @param value  Value that the Original PAC Effective Date will be set to.
    */
   public final void setPACDeff( Date value )
   {
      assertUnsent();
      _PACDeff = value;
   }
	
   /**
    * Sets the New PAC Draw Date field for the request.
    * 
    * @param value  Value that the New PAC Draw Date will be set to.
    */
   public final void setPACDrawDeff( Date value )
   {
      assertUnsent();
      _PACDrawDeff = value;
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
      requestBuffer.appendField( _AcctCommitMstrUUID );
      requestBuffer.appendField( _PACDeff );
      requestBuffer.appendField( _PACDrawDeff );
   }

}

