// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder Remarks request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrRemarks.doc">ShrRemarks.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrRemarksRequest extends IFastRequest implements Serializable
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
    * Shareholder Number member variable.
    */
   private Integer _ShareholderNum = null;
            
   /**
    * Remark1 member variable.
    */
   private String _Remark1 = "";
            
   /**
    * Remark2 member variable.
    */
   private String _Remark2 = "";
            
   /**
    * Remark3 member variable.
    */
   private String _Remark3 = "";
            
   /**
    * Remark4 member variable.
    */
   private String _Remark4 = "";
            
   /**
    * Remark5 member variable.
    */
   private String _Remark5 = "";
            
   /**
    * Remark6 member variable.
    */
   private String _Remark6 = "";
            
   /**
    * Remark7 member variable.
    */
   private String _Remark7 = "";
            
   /**
    * Remark8 member variable.
    */
   private String _Remark8 = "";
            
   /**
    * Remark9 member variable.
    */
   private String _Remark9 = "";
            
   /**
    * Remark10 member variable.
    */
   private String _Remark10 = "";
            

   /**
    * Constructs the ShrRemarksRequest object.
    * 
    */
   ShrRemarksRequest()
   {
      super ( 154 );
   }

   /**
    * Constructs the ShrRemarksRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrRemarksRequest( String hostEncoding )
   {
      super ( 154, hostEncoding );
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
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShareholderNum( Integer value )
   {
      assertUnsent();
      _ShareholderNum = value;
   }
	
   /**
    * Sets the Remark1 field for the request.
    * 
    * @param value  Value that the Remark1 will be set to.
    */
   public final void setRemark1( String value )
   {
      assertUnsent();
      _Remark1 = value;
   }
	
   /**
    * Sets the Remark2 field for the request.
    * 
    * @param value  Value that the Remark2 will be set to.
    */
   public final void setRemark2( String value )
   {
      assertUnsent();
      _Remark2 = value;
   }
	
   /**
    * Sets the Remark3 field for the request.
    * 
    * @param value  Value that the Remark3 will be set to.
    */
   public final void setRemark3( String value )
   {
      assertUnsent();
      _Remark3 = value;
   }
	
   /**
    * Sets the Remark4 field for the request.
    * 
    * @param value  Value that the Remark4 will be set to.
    */
   public final void setRemark4( String value )
   {
      assertUnsent();
      _Remark4 = value;
   }
	
   /**
    * Sets the Remark5 field for the request.
    * 
    * @param value  Value that the Remark5 will be set to.
    */
   public final void setRemark5( String value )
   {
      assertUnsent();
      _Remark5 = value;
   }
	
   /**
    * Sets the Remark6 field for the request.
    * 
    * @param value  Value that the Remark6 will be set to.
    */
   public final void setRemark6( String value )
   {
      assertUnsent();
      _Remark6 = value;
   }
	
   /**
    * Sets the Remark7 field for the request.
    * 
    * @param value  Value that the Remark7 will be set to.
    */
   public final void setRemark7( String value )
   {
      assertUnsent();
      _Remark7 = value;
   }
	
   /**
    * Sets the Remark8 field for the request.
    * 
    * @param value  Value that the Remark8 will be set to.
    */
   public final void setRemark8( String value )
   {
      assertUnsent();
      _Remark8 = value;
   }
	
   /**
    * Sets the Remark9 field for the request.
    * 
    * @param value  Value that the Remark9 will be set to.
    */
   public final void setRemark9( String value )
   {
      assertUnsent();
      _Remark9 = value;
   }
	
   /**
    * Sets the Remark10 field for the request.
    * 
    * @param value  Value that the Remark10 will be set to.
    */
   public final void setRemark10( String value )
   {
      assertUnsent();
      _Remark10 = value;
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
      requestBuffer.appendField( _ShareholderNum );
      requestBuffer.appendField( _Remark1 );
      requestBuffer.appendField( _Remark2 );
      requestBuffer.appendField( _Remark3 );
      requestBuffer.appendField( _Remark4 );
      requestBuffer.appendField( _Remark5 );
      requestBuffer.appendField( _Remark6 );
      requestBuffer.appendField( _Remark7 );
      requestBuffer.appendField( _Remark8 );
      requestBuffer.appendField( _Remark9 );
      requestBuffer.appendField( _Remark10 );
   }

}

