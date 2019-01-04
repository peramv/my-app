// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Message Process Search request.
 * For additional view information see <A HREF="../../../../viewspecs/MesgProcSrch.doc">MesgProcSrch.doc</A>.
 * 
 * @author RTS Generated
 */
public class MesgProcSrchRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
    */
   private String _SessionID = "";
            
   /**
    * User ID member variable.
    */
   private String _User_ID = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company ID member variable.
    */
   private String _CompanyID = "";
            
            
            
            
            
   /**
    * Search Type member variable.
    */
   private String _SearchType = "";
            
   /**
    * Company Code member variable.
    */
   private String _CompanyCode = "";
            
   /**
    * Envelope ID member variable.
    */
   private String _EnvelopeID = "0";
            
   /**
    * Process Type member variable.
    */
   private String _ProcessType = "";
            
   /**
    * Start Date member variable.
    */
   private Date _StartDate = null;
            
   /**
    * End Date member variable.
    */
   private Date _EndDate = null;
            
   /**
    * Process Status member variable.
    */
   private String _ProcessStatus = "";
            
   /**
    * Network ID member variable.
    */
   private String _NetworkID = "";
            
   /**
    * Senders Reference Number member variable.
    */
   private String _SenderRefNum = "";
            
   /**
    * Transaction Number member variable.
    */
   private Integer _TransNum = null;
            
   /**
    * Aggregate Order Reference Number member variable.
    */
   private String _AggOrdRefNum = "";
            
   /**
    * Activity ID member variable.
    */
   private String _ActivityID = "0";
            
   /**
    * Process Category member variable.
    */
   private String _ProcessCategory = "";
            

   /**
    * Constructs the MesgProcSrchRequest object.
    * 
    */
   MesgProcSrchRequest()
   {
      super ( 333 );
   }

   /**
    * Constructs the MesgProcSrchRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MesgProcSrchRequest( String hostEncoding )
   {
      super ( 333, hostEncoding );
   }

   /**
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
    */
   public final void setUser_ID( String value )
   {
      assertUnsent();
      _User_ID = value;
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
    * Sets the Company ID field for the request.
    * 
    * @param value  Value that the Company ID will be set to.
    */
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
   }
	
   /**
    * Sets the Search Type field for the request.
    * 
    * @param value  Value that the Search Type will be set to.
    */
   public final void setSearchType( String value )
   {
      assertUnsent();
      _SearchType = value;
   }
	
   /**
    * Sets the Company Code field for the request.
    * 
    * @param value  Value that the Company Code will be set to.
    */
   public final void setCompanyCode( String value )
   {
      assertUnsent();
      _CompanyCode = value;
   }
	
   /**
    * Sets the Envelope ID field for the request.
    * 
    * @param value  Value that the Envelope ID will be set to.
    */
   public final void setEnvelopeID( String value )
   {
      assertUnsent();
      _EnvelopeID = value;
   }
	
   /**
    * Sets the Process Type field for the request.
    * 
    * @param value  Value that the Process Type will be set to.
    */
   public final void setProcessType( String value )
   {
      assertUnsent();
      _ProcessType = value;
   }
	
   /**
    * Sets the Start Date field for the request.
    * 
    * @param value  Value that the Start Date will be set to.
    */
   public final void setStartDate( Date value )
   {
      assertUnsent();
      _StartDate = value;
   }
	
   /**
    * Sets the End Date field for the request.
    * 
    * @param value  Value that the End Date will be set to.
    */
   public final void setEndDate( Date value )
   {
      assertUnsent();
      _EndDate = value;
   }
	
   /**
    * Sets the Process Status field for the request.
    * 
    * @param value  Value that the Process Status will be set to.
    */
   public final void setProcessStatus( String value )
   {
      assertUnsent();
      _ProcessStatus = value;
   }
	
   /**
    * Sets the Network ID field for the request.
    * 
    * @param value  Value that the Network ID will be set to.
    */
   public final void setNetworkID( String value )
   {
      assertUnsent();
      _NetworkID = value;
   }
	
   /**
    * Sets the Senders Reference Number field for the request.
    * 
    * @param value  Value that the Senders Reference Number will be set to.
    */
   public final void setSenderRefNum( String value )
   {
      assertUnsent();
      _SenderRefNum = value;
   }
	
   /**
    * Sets the Transaction Number field for the request.
    * 
    * @param value  Value that the Transaction Number will be set to.
    */
   public final void setTransNum( Integer value )
   {
      assertUnsent();
      _TransNum = value;
   }
	
   /**
    * Sets the Aggregate Order Reference Number field for the request.
    * 
    * @param value  Value that the Aggregate Order Reference Number will be set to.
    */
   public final void setAggOrdRefNum( String value )
   {
      assertUnsent();
      _AggOrdRefNum = value;
   }
	
   /**
    * Sets the Activity ID field for the request.
    * 
    * @param value  Value that the Activity ID will be set to.
    */
   public final void setActivityID( String value )
   {
      assertUnsent();
      _ActivityID = value;
   }
	
   /**
    * Sets the Process Category field for the request.
    * 
    * @param value  Value that the Process Category will be set to.
    */
   public final void setProcessCategory( String value )
   {
      assertUnsent();
      _ProcessCategory = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_ID );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( _SearchType );
      requestBuffer.appendField( _CompanyCode );
      requestBuffer.appendField( _EnvelopeID );
      requestBuffer.appendField( _ProcessType );
      requestBuffer.appendField( _StartDate );
      requestBuffer.appendField( _EndDate );
      requestBuffer.appendField( _ProcessStatus );
      requestBuffer.appendField( _NetworkID );
      requestBuffer.appendField( _SenderRefNum );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _AggOrdRefNum );
      requestBuffer.appendField( _ActivityID );
      requestBuffer.appendField( _ProcessCategory );
   }

}

