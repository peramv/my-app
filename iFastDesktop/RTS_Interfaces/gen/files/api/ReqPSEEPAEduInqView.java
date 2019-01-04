
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Request File of PSE/EPA Education Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/ReqPSEEPAEduInq.doc">ReqPSEEPAEduInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class ReqPSEEPAEduInqView extends IFastView implements Serializable
{

   /**
    * EntityID of RESP Beneficiary. member variable.
    */
   private String _RESPBenefID = null;
   
   /**
    * RESP Beneficiary Name member variable.
    */
   private String _RESPBenefName = null;
   
   /**
    * RESP Beneficiary LastName member variable.
    */
   private String _RESPBenefLastName = null;
   
   /**
    * Academic Year Start Date member variable.
    */
   private Date _CourseStart = null;
   
   /**
    * Academic Year Length member variable.
    */
   private Integer _CourseLen = null;
   
   /**
    * PSE Program Length member variable.
    */
   private Integer _PSEProgramLen = null;
   
   /**
    * PSE Program Type member variable.
    */
   private Integer _PSEProgramType = null;
   
   /**
    * PSE Program Year member variable.
    */
   private Integer _PSEProgramYear = null;
   
   /**
    * Education Institution Postal Code or Country Name member variable.
    */
   private String _EduInstPstl = null;
   

   /**
    * Constructs the ReqPSEEPAEduInqView object.
    * 
    */
   public ReqPSEEPAEduInqView()
   {
      super ( new ReqPSEEPAEduInqRequest() );
   }

   /**
    * Constructs the ReqPSEEPAEduInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public ReqPSEEPAEduInqView( String hostEncoding )
   {
      super ( new ReqPSEEPAEduInqRequest( hostEncoding ) );
   }

   /**
    * Gets the ReqPSEEPAEduInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The ReqPSEEPAEduInqRequest object.
    */
   public final ReqPSEEPAEduInqRequest getRequest()
   {
      return (ReqPSEEPAEduInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the EntityID of RESP Beneficiary. field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EntityID of RESP Beneficiary. or null.
    */
   public final String getRESPBenefID()
   {
      return _RESPBenefID;
   }
	
   /**
    * Gets the EntityID of RESP Beneficiary. field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EntityID of RESP Beneficiary. or the specified default value.
    */
   public final String getRESPBenefID( String defaultValue )
   {
      return _RESPBenefID == null ? defaultValue : _RESPBenefID;
   }
                  
   /**
    * Gets the RESP Beneficiary Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Beneficiary Name or null.
    */
   public final String getRESPBenefName()
   {
      return _RESPBenefName;
   }
	
   /**
    * Gets the RESP Beneficiary Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary Name or the specified default value.
    */
   public final String getRESPBenefName( String defaultValue )
   {
      return _RESPBenefName == null ? defaultValue : _RESPBenefName;
   }
                  
   /**
    * Gets the RESP Beneficiary LastName field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Beneficiary LastName or null.
    */
   public final String getRESPBenefLastName()
   {
      return _RESPBenefLastName;
   }
	
   /**
    * Gets the RESP Beneficiary LastName field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary LastName or the specified default value.
    */
   public final String getRESPBenefLastName( String defaultValue )
   {
      return _RESPBenefLastName == null ? defaultValue : _RESPBenefLastName;
   }
                  
   /**
    * Gets the Academic Year Start Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Academic Year Start Date or null.
    */
   public final Date getCourseStart()
   {
      return _CourseStart;
   }
	
   /**
    * Gets the Academic Year Start Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Academic Year Start Date or the specified default value.
    */
   public final Date getCourseStart( Date defaultValue )
   {
      return _CourseStart == null ? defaultValue : _CourseStart;
   }
                  
   /**
    * Gets the Academic Year Length field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Academic Year Length or null.
    */
   public final Integer getCourseLen()
   {
      return _CourseLen;
   }
	
   /**
    * Gets the Academic Year Length field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Academic Year Length or the specified default value.
    */
   public final int getCourseLen( int defaultValue )
   {
      return _CourseLen == null ? defaultValue : _CourseLen.intValue();
   }
                  
   /**
    * Gets the PSE Program Length field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PSE Program Length or null.
    */
   public final Integer getPSEProgramLen()
   {
      return _PSEProgramLen;
   }
	
   /**
    * Gets the PSE Program Length field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PSE Program Length or the specified default value.
    */
   public final int getPSEProgramLen( int defaultValue )
   {
      return _PSEProgramLen == null ? defaultValue : _PSEProgramLen.intValue();
   }
                  
   /**
    * Gets the PSE Program Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PSE Program Type or null.
    */
   public final Integer getPSEProgramType()
   {
      return _PSEProgramType;
   }
	
   /**
    * Gets the PSE Program Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PSE Program Type or the specified default value.
    */
   public final int getPSEProgramType( int defaultValue )
   {
      return _PSEProgramType == null ? defaultValue : _PSEProgramType.intValue();
   }
                  
   /**
    * Gets the PSE Program Year field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PSE Program Year or null.
    */
   public final Integer getPSEProgramYear()
   {
      return _PSEProgramYear;
   }
	
   /**
    * Gets the PSE Program Year field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PSE Program Year or the specified default value.
    */
   public final int getPSEProgramYear( int defaultValue )
   {
      return _PSEProgramYear == null ? defaultValue : _PSEProgramYear.intValue();
   }
                  
   /**
    * Gets the Education Institution Postal Code or Country Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Education Institution Postal Code or Country Name or null.
    */
   public final String getEduInstPstl()
   {
      return _EduInstPstl;
   }
	
   /**
    * Gets the Education Institution Postal Code or Country Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Education Institution Postal Code or Country Name or the specified default value.
    */
   public final String getEduInstPstl( String defaultValue )
   {
      return _EduInstPstl == null ? defaultValue : _EduInstPstl;
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
      _RESPBenefID = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPBenefName = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPBenefLastName = responseBuffer.decodeString(responseBuffer.getNextField());
      _CourseStart = responseBuffer.decodeDate(responseBuffer.getNextField());
      _CourseLen = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PSEProgramLen = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PSEProgramType = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PSEProgramYear = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _EduInstPstl = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
