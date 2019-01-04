
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Pension Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/PensionInq.doc">PensionInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class PensionInqView extends IFastView implements Serializable
{

   /**
    * Effective Date of record member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Date as of record was modified member variable.
    */
   private Date _ModDate = null;
   
   /**
    * Date the record was created member variable.
    */
   private Date _ProcessDate = null;
   
   /**
    * User's name who created the record member variable.
    */
   private String _UserName = null;
   
   /**
    * User's name who modified the record member variable.
    */
   private String _ModUser = null;
   
   /**
    * Pension Jurisdiction member variable.
    */
   private String _PensionJuris = null;
   
   /**
    * Minimum Withdrawal Age member variable.
    */
   private Integer _MinWithAge = null;
   
   /**
    * Pension source Line 1 member variable.
    */
   private String _PenSourceLine1 = null;
   
   /**
    * Pension source Line 2 member variable.
    */
   private String _PenSourceLine2 = null;
   
   /**
    * Pension Source Line 3 member variable.
    */
   private String _PenSourceLine3 = null;
   
   /**
    * Unisex Amount member variable.
    */
   private String _UniSexPer = null;
   
   /**
    * Sex distriction amount member variable.
    */
   private String _SexDistinctPer = null;
   
   /**
    * Verion of LIPPenInfo record member variable.
    */
   private Integer _LIPPenInfoVer = null;
   
   /**
    * LIPPenInfo recid member variable.
    */
   private Integer _LIPPenInfoRid = null;
   
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = null;
   

   /**
    * Constructs the PensionInqView object.
    * 
    */
   public PensionInqView()
   {
      super ( new PensionInqRequest() );
   }

   /**
    * Constructs the PensionInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public PensionInqView( String hostEncoding )
   {
      super ( new PensionInqRequest( hostEncoding ) );
   }

   /**
    * Gets the PensionInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The PensionInqRequest object.
    */
   public final PensionInqRequest getRequest()
   {
      return (PensionInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Effective Date of record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date of record or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Effective Date of record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date of record or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Date as of record was modified field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date as of record was modified or null.
    */
   public final Date getModDate()
   {
      return _ModDate;
   }
	
   /**
    * Gets the Date as of record was modified field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date as of record was modified or the specified default value.
    */
   public final Date getModDate( Date defaultValue )
   {
      return _ModDate == null ? defaultValue : _ModDate;
   }
                  
   /**
    * Gets the Date the record was created field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date the record was created or null.
    */
   public final Date getProcessDate()
   {
      return _ProcessDate;
   }
	
   /**
    * Gets the Date the record was created field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date the record was created or the specified default value.
    */
   public final Date getProcessDate( Date defaultValue )
   {
      return _ProcessDate == null ? defaultValue : _ProcessDate;
   }
                  
   /**
    * Gets the User's name who created the record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the User's name who created the record or null.
    */
   public final String getUserName()
   {
      return _UserName;
   }
	
   /**
    * Gets the User's name who created the record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User's name who created the record or the specified default value.
    */
   public final String getUserName( String defaultValue )
   {
      return _UserName == null ? defaultValue : _UserName;
   }
                  
   /**
    * Gets the User's name who modified the record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the User's name who modified the record or null.
    */
   public final String getModUser()
   {
      return _ModUser;
   }
	
   /**
    * Gets the User's name who modified the record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User's name who modified the record or the specified default value.
    */
   public final String getModUser( String defaultValue )
   {
      return _ModUser == null ? defaultValue : _ModUser;
   }
                  
   /**
    * Gets the Pension Jurisdiction field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pension Jurisdiction or null.
    */
   public final String getPensionJuris()
   {
      return _PensionJuris;
   }
	
   /**
    * Gets the Pension Jurisdiction field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension Jurisdiction or the specified default value.
    */
   public final String getPensionJuris( String defaultValue )
   {
      return _PensionJuris == null ? defaultValue : _PensionJuris;
   }
                  
   /**
    * Gets the Minimum Withdrawal Age field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Minimum Withdrawal Age or null.
    */
   public final Integer getMinWithAge()
   {
      return _MinWithAge;
   }
	
   /**
    * Gets the Minimum Withdrawal Age field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Minimum Withdrawal Age or the specified default value.
    */
   public final int getMinWithAge( int defaultValue )
   {
      return _MinWithAge == null ? defaultValue : _MinWithAge.intValue();
   }
                  
   /**
    * Gets the Pension source Line 1 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pension source Line 1 or null.
    */
   public final String getPenSourceLine1()
   {
      return _PenSourceLine1;
   }
	
   /**
    * Gets the Pension source Line 1 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension source Line 1 or the specified default value.
    */
   public final String getPenSourceLine1( String defaultValue )
   {
      return _PenSourceLine1 == null ? defaultValue : _PenSourceLine1;
   }
                  
   /**
    * Gets the Pension source Line 2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pension source Line 2 or null.
    */
   public final String getPenSourceLine2()
   {
      return _PenSourceLine2;
   }
	
   /**
    * Gets the Pension source Line 2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension source Line 2 or the specified default value.
    */
   public final String getPenSourceLine2( String defaultValue )
   {
      return _PenSourceLine2 == null ? defaultValue : _PenSourceLine2;
   }
                  
   /**
    * Gets the Pension Source Line 3 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pension Source Line 3 or null.
    */
   public final String getPenSourceLine3()
   {
      return _PenSourceLine3;
   }
	
   /**
    * Gets the Pension Source Line 3 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pension Source Line 3 or the specified default value.
    */
   public final String getPenSourceLine3( String defaultValue )
   {
      return _PenSourceLine3 == null ? defaultValue : _PenSourceLine3;
   }
                  
   /**
    * Gets the Unisex Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Unisex Amount or null.
    */
   public final String getUniSexPer()
   {
      return _UniSexPer;
   }
	
   /**
    * Gets the Unisex Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Unisex Amount or the specified default value.
    */
   public final String getUniSexPer( String defaultValue )
   {
      return _UniSexPer == null ? defaultValue : _UniSexPer;
   }
                  
   /**
    * Gets the Sex distriction amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Sex distriction amount or null.
    */
   public final String getSexDistinctPer()
   {
      return _SexDistinctPer;
   }
	
   /**
    * Gets the Sex distriction amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Sex distriction amount or the specified default value.
    */
   public final String getSexDistinctPer( String defaultValue )
   {
      return _SexDistinctPer == null ? defaultValue : _SexDistinctPer;
   }
                  
   /**
    * Gets the Verion of LIPPenInfo record field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Verion of LIPPenInfo record or null.
    */
   public final Integer getLIPPenInfoVer()
   {
      return _LIPPenInfoVer;
   }
	
   /**
    * Gets the Verion of LIPPenInfo record field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Verion of LIPPenInfo record or the specified default value.
    */
   public final int getLIPPenInfoVer( int defaultValue )
   {
      return _LIPPenInfoVer == null ? defaultValue : _LIPPenInfoVer.intValue();
   }
                  
   /**
    * Gets the LIPPenInfo recid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the LIPPenInfo recid or null.
    */
   public final Integer getLIPPenInfoRid()
   {
      return _LIPPenInfoRid;
   }
	
   /**
    * Gets the LIPPenInfo recid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the LIPPenInfo recid or the specified default value.
    */
   public final int getLIPPenInfoRid( int defaultValue )
   {
      return _LIPPenInfoRid == null ? defaultValue : _LIPPenInfoRid.intValue();
   }
                  
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Shareholder Number or null.
    */
   public final String getShrNum()
   {
      return _ShrNum;
   }
	
   /**
    * Gets the Shareholder Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Shareholder Number or the specified default value.
    */
   public final String getShrNum( String defaultValue )
   {
      return _ShrNum == null ? defaultValue : _ShrNum;
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ModDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ProcessDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _UserName = responseBuffer.decodeString(responseBuffer.getNextField());
      _ModUser = responseBuffer.decodeString(responseBuffer.getNextField());
      _PensionJuris = responseBuffer.decodeString(responseBuffer.getNextField());
      _MinWithAge = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PenSourceLine1 = responseBuffer.decodeString(responseBuffer.getNextField());
      _PenSourceLine2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _PenSourceLine3 = responseBuffer.decodeString(responseBuffer.getNextField());
      _UniSexPer = responseBuffer.decodeString(responseBuffer.getNextField());
      _SexDistinctPer = responseBuffer.decodeString(responseBuffer.getNextField());
      _LIPPenInfoVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _LIPPenInfoRid = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _ShrNum = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
