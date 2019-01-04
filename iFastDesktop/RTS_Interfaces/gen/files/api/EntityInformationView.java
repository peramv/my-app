
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Entity Informaiton view.
 * For additional view information see <A HREF="../../../../viewspecs/EntityInformation.doc">EntityInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntityInformationView extends IFastView implements Serializable
{

   /**
    * Entity Salutation member variable.
    */
   private String _Salutation = null;
   
   /**
    * Entity Last Name member variable.
    */
   private String _LastName = null;
   
   /**
    * Entity First Name member variable.
    */
   private String _FirstName = null;
   
   /**
    * Last Name at Birth member variable.
    */
   private String _BirthLastName = null;
   
   /**
    * First Name at Birth member variable.
    */
   private String _BirthFirstName = null;
   
   /**
    * Date of Birth member variable.
    */
   private Date _DofBirth = null;
   
   /**
    * Gender member variable.
    */
   private String _Gender = null;
   
   /**
    * Social Insurance Number member variable.
    */
   private String _SIN = null;
   
   /**
    * Occupation Code member variable.
    */
   private String _OccupationCode = null;
   
   /**
    * Occupation Description member variable.
    */
   private String _OccupationDesc = null;
   
   /**
    * Language Code member variable.
    */
   private String _Lang = null;
   
   /**
    * Language member variable.
    */
   private String _Language = null;
   
   /**
    * Home Phone Number member variable.
    */
   private String _HomePhone = null;
   
   /**
    * Business Phone Number member variable.
    */
   private String _BusinessPhone = null;
   
   /**
    * Business Phone Extention member variable.
    */
   private String _BuisnessExt = null;
   
   /**
    * Buisness Fax Number member variable.
    */
   private String _BusinessFax = null;
   
   /**
    * Telex Number member variable.
    */
   private String _Telex = null;
   
   /**
    * Email Address member variable.
    */
   private String _Email = null;
   
   /**
    * Date of Death member variable.
    */
   private Date _DofDate = null;
   
   /**
    * Date of Death Notification member variable.
    */
   private Date _DofDeathNotice = null;
   
   /**
    * Effective Date member variable.
    */
   private Date _EffectiveDate = null;
   
   /**
    * Created On member variable.
    */
   private Date _ProcessDate = null;
   
   /**
    * Modified On member variable.
    */
   private Date _ModDate = null;
   
   /**
    * Created By member variable.
    */
   private String _Username = null;
   
   /**
    * Modified By member variable.
    */
   private String _ModUser = null;
   
   /**
    * Home Fax member variable.
    */
   private String _HomeFax = null;
   
   /**
    * Entity Identity Version member variable.
    */
   private Integer _EntityIdentityVer = null;
   
   /**
    * Entity Identity Record Id member variable.
    */
   private Integer _EntityIdentityRid = null;
   
   /**
    * Hone Phone Country member variable.
    */
   private String _HomePhoneCntry = null;
   
   /**
    * Home Phone Area member variable.
    */
   private String _HomePhoneArea = null;
   
   /**
    * Business Phone Country member variable.
    */
   private String _BusinessPhoneCntry = null;
   
   /**
    * Business Phone Area member variable.
    */
   private String _BusinessPhoneArea = null;
   
   /**
    * Home Fax Country member variable.
    */
   private String _HomeFaxCntry = null;
   
   /**
    * Home Fax Area member variable.
    */
   private String _HomeFaxArea = null;
   
   /**
    * Business Fax Country member variable.
    */
   private String _BusFaxCntry = null;
   
   /**
    * Business Fax Area member variable.
    */
   private String _BusFaxArea = null;
   
   /**
    * Employee Flag member variable.
    */
   private String _EmployeeFlag = null;
   
   /**
    * Nationality member variable.
    */
   private String _Nationality = null;
   
   /**
    * Other Occupation member variable.
    */
   private String _OtherOccupation = null;
   
   /**
    * Spouse EntityID member variable.
    */
   private Integer _SpouseEntityID = null;
   
   /**
    * Place of Birth member variable.
    */
   private String _PlaceOfBirth = null;
   
   /**
    * Risk Level member variable.
    */
   private String _RiskLevel = null;
   
   /**
    * Effective Date of the Tax Juris Info member variable.
    */
   private Date _TaxJurisDeff = null;
   
   /**
    * Tax Jurisdiction of the Entity member variable.
    */
   private String _TaxJuris = null;
   
   /**
    * EUSD Tax Option member variable.
    */
   private String _EUSDTaxOption = null;
   
   /**
    * Where Used member variable.
    */
   private String _WhereUsed = null;
   
   /**
    * Entity Status member variable.
    */
   private Boolean _EntStatus = null;
   
   /**
    * Country of Birth of the account holder member variable.
    */
   private String _CountryOfBirth = null;
   
   /**
    * Conact name for institutional entity member variable.
    */
   private String _ContactName = null;
   
   /**
    * Email2 member variable.
    */
   private String _Email2 = null;
   
   /**
    * Second Phone Number member variable.
    */
   private String _SecondPhnNum = null;
   
   /**
    * Second Phone Number Extension member variable.
    */
   private String _SecondPhnNumExt = null;
   
   /**
    * FATCAFFI member variable.
    */
   private String _FATCAFFI = null;
   
   private int _RepeatCount = 0;
   
   /**
    * ID Type member array.
    */
   private String[] _IdType = null;
   
   /**
    * ID Type Description member array.
    */
   private String[] _IdTypeDesc = null;
   
   /**
    * ID Value member array.
    */
   private String[] _IdValue = null;
   
   /**
    * ID Issue Date member array.
    */
   private Date[] _IdDate = null;
   
   /**
    * Entity-Search Id Version Number member array.
    */
   private Integer[] _EntitySearchIdVer = null;
   
   /**
    * Recid of Entity-Search Id record member array.
    */
   private Integer[] _EntitySearchIdRid = null;
   
   /**
    * ID Status member array.
    */
   private String[] _IDStatus = null;
   
   /**
    * Allow Override member array.
    */
   private Boolean[] _AllowOverride = null;
   
   /**
    * Country Of Issue member array.
    */
   private String[] _CountryofIssue = null;
   
   /**
    * IdExpireDate member array.
    */
   private Date[] _IdExpireDate = null;
   

   /**
    * Constructs the EntityInformationView object.
    * 
    */
   public EntityInformationView()
   {
      super ( new EntityInformationRequest() );
   }

   /**
    * Constructs the EntityInformationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public EntityInformationView( String hostEncoding )
   {
      super ( new EntityInformationRequest( hostEncoding ) );
   }

   /**
    * Gets the EntityInformationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The EntityInformationRequest object.
    */
   public final EntityInformationRequest getRequest()
   {
      return (EntityInformationRequest)getIFastRequest();
   }
        
   /**
    * Gets the Entity Salutation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Salutation or null.
    */
   public final String getSalutation()
   {
      return _Salutation;
   }
	
   /**
    * Gets the Entity Salutation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Salutation or the specified default value.
    */
   public final String getSalutation( String defaultValue )
   {
      return _Salutation == null ? defaultValue : _Salutation;
   }
                  
   /**
    * Gets the Entity Last Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Last Name or null.
    */
   public final String getLastName()
   {
      return _LastName;
   }
	
   /**
    * Gets the Entity Last Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Last Name or the specified default value.
    */
   public final String getLastName( String defaultValue )
   {
      return _LastName == null ? defaultValue : _LastName;
   }
                  
   /**
    * Gets the Entity First Name field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity First Name or null.
    */
   public final String getFirstName()
   {
      return _FirstName;
   }
	
   /**
    * Gets the Entity First Name field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity First Name or the specified default value.
    */
   public final String getFirstName( String defaultValue )
   {
      return _FirstName == null ? defaultValue : _FirstName;
   }
                  
   /**
    * Gets the Last Name at Birth field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Last Name at Birth or null.
    */
   public final String getBirthLastName()
   {
      return _BirthLastName;
   }
	
   /**
    * Gets the Last Name at Birth field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Name at Birth or the specified default value.
    */
   public final String getBirthLastName( String defaultValue )
   {
      return _BirthLastName == null ? defaultValue : _BirthLastName;
   }
                  
   /**
    * Gets the First Name at Birth field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the First Name at Birth or null.
    */
   public final String getBirthFirstName()
   {
      return _BirthFirstName;
   }
	
   /**
    * Gets the First Name at Birth field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the First Name at Birth or the specified default value.
    */
   public final String getBirthFirstName( String defaultValue )
   {
      return _BirthFirstName == null ? defaultValue : _BirthFirstName;
   }
                  
   /**
    * Gets the Date of Birth field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date of Birth or null.
    */
   public final Date getDofBirth()
   {
      return _DofBirth;
   }
	
   /**
    * Gets the Date of Birth field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Birth or the specified default value.
    */
   public final Date getDofBirth( Date defaultValue )
   {
      return _DofBirth == null ? defaultValue : _DofBirth;
   }
                  
   /**
    * Gets the Gender field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Gender or null.
    */
   public final String getGender()
   {
      return _Gender;
   }
	
   /**
    * Gets the Gender field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Gender or the specified default value.
    */
   public final String getGender( String defaultValue )
   {
      return _Gender == null ? defaultValue : _Gender;
   }
                  
   /**
    * Gets the Social Insurance Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Social Insurance Number or null.
    */
   public final String getSIN()
   {
      return _SIN;
   }
	
   /**
    * Gets the Social Insurance Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Social Insurance Number or the specified default value.
    */
   public final String getSIN( String defaultValue )
   {
      return _SIN == null ? defaultValue : _SIN;
   }
                  
   /**
    * Gets the Occupation Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Occupation Code or null.
    */
   public final String getOccupationCode()
   {
      return _OccupationCode;
   }
	
   /**
    * Gets the Occupation Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Occupation Code or the specified default value.
    */
   public final String getOccupationCode( String defaultValue )
   {
      return _OccupationCode == null ? defaultValue : _OccupationCode;
   }
                  
   /**
    * Gets the Occupation Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Occupation Description or null.
    */
   public final String getOccupationDesc()
   {
      return _OccupationDesc;
   }
	
   /**
    * Gets the Occupation Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Occupation Description or the specified default value.
    */
   public final String getOccupationDesc( String defaultValue )
   {
      return _OccupationDesc == null ? defaultValue : _OccupationDesc;
   }
                  
   /**
    * Gets the Language Code field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Language Code or null.
    */
   public final String getLang()
   {
      return _Lang;
   }
	
   /**
    * Gets the Language Code field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Language Code or the specified default value.
    */
   public final String getLang( String defaultValue )
   {
      return _Lang == null ? defaultValue : _Lang;
   }
                  
   /**
    * Gets the Language field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Language or null.
    */
   public final String getLanguage()
   {
      return _Language;
   }
	
   /**
    * Gets the Language field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Language or the specified default value.
    */
   public final String getLanguage( String defaultValue )
   {
      return _Language == null ? defaultValue : _Language;
   }
                  
   /**
    * Gets the Home Phone Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Home Phone Number or null.
    */
   public final String getHomePhone()
   {
      return _HomePhone;
   }
	
   /**
    * Gets the Home Phone Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Home Phone Number or the specified default value.
    */
   public final String getHomePhone( String defaultValue )
   {
      return _HomePhone == null ? defaultValue : _HomePhone;
   }
                  
   /**
    * Gets the Business Phone Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Business Phone Number or null.
    */
   public final String getBusinessPhone()
   {
      return _BusinessPhone;
   }
	
   /**
    * Gets the Business Phone Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Phone Number or the specified default value.
    */
   public final String getBusinessPhone( String defaultValue )
   {
      return _BusinessPhone == null ? defaultValue : _BusinessPhone;
   }
                  
   /**
    * Gets the Business Phone Extention field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Business Phone Extention or null.
    */
   public final String getBuisnessExt()
   {
      return _BuisnessExt;
   }
	
   /**
    * Gets the Business Phone Extention field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Phone Extention or the specified default value.
    */
   public final String getBuisnessExt( String defaultValue )
   {
      return _BuisnessExt == null ? defaultValue : _BuisnessExt;
   }
                  
   /**
    * Gets the Buisness Fax Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Buisness Fax Number or null.
    */
   public final String getBusinessFax()
   {
      return _BusinessFax;
   }
	
   /**
    * Gets the Buisness Fax Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Buisness Fax Number or the specified default value.
    */
   public final String getBusinessFax( String defaultValue )
   {
      return _BusinessFax == null ? defaultValue : _BusinessFax;
   }
                  
   /**
    * Gets the Telex Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Telex Number or null.
    */
   public final String getTelex()
   {
      return _Telex;
   }
	
   /**
    * Gets the Telex Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Telex Number or the specified default value.
    */
   public final String getTelex( String defaultValue )
   {
      return _Telex == null ? defaultValue : _Telex;
   }
                  
   /**
    * Gets the Email Address field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Email Address or null.
    */
   public final String getEmail()
   {
      return _Email;
   }
	
   /**
    * Gets the Email Address field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Email Address or the specified default value.
    */
   public final String getEmail( String defaultValue )
   {
      return _Email == null ? defaultValue : _Email;
   }
                  
   /**
    * Gets the Date of Death field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date of Death or null.
    */
   public final Date getDofDate()
   {
      return _DofDate;
   }
	
   /**
    * Gets the Date of Death field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Death or the specified default value.
    */
   public final Date getDofDate( Date defaultValue )
   {
      return _DofDate == null ? defaultValue : _DofDate;
   }
                  
   /**
    * Gets the Date of Death Notification field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Date of Death Notification or null.
    */
   public final Date getDofDeathNotice()
   {
      return _DofDeathNotice;
   }
	
   /**
    * Gets the Date of Death Notification field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Date of Death Notification or the specified default value.
    */
   public final Date getDofDeathNotice( Date defaultValue )
   {
      return _DofDeathNotice == null ? defaultValue : _DofDeathNotice;
   }
                  
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate()
   {
      return _EffectiveDate;
   }
	
   /**
    * Gets the Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( Date defaultValue )
   {
      return _EffectiveDate == null ? defaultValue : _EffectiveDate;
   }
                  
   /**
    * Gets the Created On field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Created On or null.
    */
   public final Date getProcessDate()
   {
      return _ProcessDate;
   }
	
   /**
    * Gets the Created On field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created On or the specified default value.
    */
   public final Date getProcessDate( Date defaultValue )
   {
      return _ProcessDate == null ? defaultValue : _ProcessDate;
   }
                  
   /**
    * Gets the Modified On field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Modified On or null.
    */
   public final Date getModDate()
   {
      return _ModDate;
   }
	
   /**
    * Gets the Modified On field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified On or the specified default value.
    */
   public final Date getModDate( Date defaultValue )
   {
      return _ModDate == null ? defaultValue : _ModDate;
   }
                  
   /**
    * Gets the Created By field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Created By or null.
    */
   public final String getUsername()
   {
      return _Username;
   }
	
   /**
    * Gets the Created By field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Created By or the specified default value.
    */
   public final String getUsername( String defaultValue )
   {
      return _Username == null ? defaultValue : _Username;
   }
                  
   /**
    * Gets the Modified By field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Modified By or null.
    */
   public final String getModUser()
   {
      return _ModUser;
   }
	
   /**
    * Gets the Modified By field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Modified By or the specified default value.
    */
   public final String getModUser( String defaultValue )
   {
      return _ModUser == null ? defaultValue : _ModUser;
   }
                  
   /**
    * Gets the Home Fax field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Home Fax or null.
    */
   public final String getHomeFax()
   {
      return _HomeFax;
   }
	
   /**
    * Gets the Home Fax field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Home Fax or the specified default value.
    */
   public final String getHomeFax( String defaultValue )
   {
      return _HomeFax == null ? defaultValue : _HomeFax;
   }
                  
   /**
    * Gets the Entity Identity Version field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Identity Version or null.
    */
   public final Integer getEntityIdentityVer()
   {
      return _EntityIdentityVer;
   }
	
   /**
    * Gets the Entity Identity Version field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Identity Version or the specified default value.
    */
   public final int getEntityIdentityVer( int defaultValue )
   {
      return _EntityIdentityVer == null ? defaultValue : _EntityIdentityVer.intValue();
   }
                  
   /**
    * Gets the Entity Identity Record Id field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Identity Record Id or null.
    */
   public final Integer getEntityIdentityRid()
   {
      return _EntityIdentityRid;
   }
	
   /**
    * Gets the Entity Identity Record Id field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Identity Record Id or the specified default value.
    */
   public final int getEntityIdentityRid( int defaultValue )
   {
      return _EntityIdentityRid == null ? defaultValue : _EntityIdentityRid.intValue();
   }
                  
   /**
    * Gets the Hone Phone Country field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Hone Phone Country or null.
    */
   public final String getHomePhoneCntry()
   {
      return _HomePhoneCntry;
   }
	
   /**
    * Gets the Hone Phone Country field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Hone Phone Country or the specified default value.
    */
   public final String getHomePhoneCntry( String defaultValue )
   {
      return _HomePhoneCntry == null ? defaultValue : _HomePhoneCntry;
   }
                  
   /**
    * Gets the Home Phone Area field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Home Phone Area or null.
    */
   public final String getHomePhoneArea()
   {
      return _HomePhoneArea;
   }
	
   /**
    * Gets the Home Phone Area field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Home Phone Area or the specified default value.
    */
   public final String getHomePhoneArea( String defaultValue )
   {
      return _HomePhoneArea == null ? defaultValue : _HomePhoneArea;
   }
                  
   /**
    * Gets the Business Phone Country field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Business Phone Country or null.
    */
   public final String getBusinessPhoneCntry()
   {
      return _BusinessPhoneCntry;
   }
	
   /**
    * Gets the Business Phone Country field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Phone Country or the specified default value.
    */
   public final String getBusinessPhoneCntry( String defaultValue )
   {
      return _BusinessPhoneCntry == null ? defaultValue : _BusinessPhoneCntry;
   }
                  
   /**
    * Gets the Business Phone Area field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Business Phone Area or null.
    */
   public final String getBusinessPhoneArea()
   {
      return _BusinessPhoneArea;
   }
	
   /**
    * Gets the Business Phone Area field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Phone Area or the specified default value.
    */
   public final String getBusinessPhoneArea( String defaultValue )
   {
      return _BusinessPhoneArea == null ? defaultValue : _BusinessPhoneArea;
   }
                  
   /**
    * Gets the Home Fax Country field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Home Fax Country or null.
    */
   public final String getHomeFaxCntry()
   {
      return _HomeFaxCntry;
   }
	
   /**
    * Gets the Home Fax Country field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Home Fax Country or the specified default value.
    */
   public final String getHomeFaxCntry( String defaultValue )
   {
      return _HomeFaxCntry == null ? defaultValue : _HomeFaxCntry;
   }
                  
   /**
    * Gets the Home Fax Area field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Home Fax Area or null.
    */
   public final String getHomeFaxArea()
   {
      return _HomeFaxArea;
   }
	
   /**
    * Gets the Home Fax Area field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Home Fax Area or the specified default value.
    */
   public final String getHomeFaxArea( String defaultValue )
   {
      return _HomeFaxArea == null ? defaultValue : _HomeFaxArea;
   }
                  
   /**
    * Gets the Business Fax Country field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Business Fax Country or null.
    */
   public final String getBusFaxCntry()
   {
      return _BusFaxCntry;
   }
	
   /**
    * Gets the Business Fax Country field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Fax Country or the specified default value.
    */
   public final String getBusFaxCntry( String defaultValue )
   {
      return _BusFaxCntry == null ? defaultValue : _BusFaxCntry;
   }
                  
   /**
    * Gets the Business Fax Area field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Business Fax Area or null.
    */
   public final String getBusFaxArea()
   {
      return _BusFaxArea;
   }
	
   /**
    * Gets the Business Fax Area field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Business Fax Area or the specified default value.
    */
   public final String getBusFaxArea( String defaultValue )
   {
      return _BusFaxArea == null ? defaultValue : _BusFaxArea;
   }
                  
   /**
    * Gets the Employee Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Employee Flag or null.
    */
   public final String getEmployeeFlag()
   {
      return _EmployeeFlag;
   }
	
   /**
    * Gets the Employee Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Employee Flag or the specified default value.
    */
   public final String getEmployeeFlag( String defaultValue )
   {
      return _EmployeeFlag == null ? defaultValue : _EmployeeFlag;
   }
                  
   /**
    * Gets the Nationality field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Nationality or null.
    */
   public final String getNationality()
   {
      return _Nationality;
   }
	
   /**
    * Gets the Nationality field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Nationality or the specified default value.
    */
   public final String getNationality( String defaultValue )
   {
      return _Nationality == null ? defaultValue : _Nationality;
   }
                  
   /**
    * Gets the Other Occupation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Other Occupation or null.
    */
   public final String getOtherOccupation()
   {
      return _OtherOccupation;
   }
	
   /**
    * Gets the Other Occupation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Other Occupation or the specified default value.
    */
   public final String getOtherOccupation( String defaultValue )
   {
      return _OtherOccupation == null ? defaultValue : _OtherOccupation;
   }
                  
   /**
    * Gets the Spouse EntityID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Spouse EntityID or null.
    */
   public final Integer getSpouseEntityID()
   {
      return _SpouseEntityID;
   }
	
   /**
    * Gets the Spouse EntityID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Spouse EntityID or the specified default value.
    */
   public final int getSpouseEntityID( int defaultValue )
   {
      return _SpouseEntityID == null ? defaultValue : _SpouseEntityID.intValue();
   }
                  
   /**
    * Gets the Place of Birth field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Place of Birth or null.
    */
   public final String getPlaceOfBirth()
   {
      return _PlaceOfBirth;
   }
	
   /**
    * Gets the Place of Birth field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Place of Birth or the specified default value.
    */
   public final String getPlaceOfBirth( String defaultValue )
   {
      return _PlaceOfBirth == null ? defaultValue : _PlaceOfBirth;
   }
                  
   /**
    * Gets the Risk Level field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Risk Level or null.
    */
   public final String getRiskLevel()
   {
      return _RiskLevel;
   }
	
   /**
    * Gets the Risk Level field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Risk Level or the specified default value.
    */
   public final String getRiskLevel( String defaultValue )
   {
      return _RiskLevel == null ? defaultValue : _RiskLevel;
   }
                  
   /**
    * Gets the Effective Date of the Tax Juris Info field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Effective Date of the Tax Juris Info or null.
    */
   public final Date getTaxJurisDeff()
   {
      return _TaxJurisDeff;
   }
	
   /**
    * Gets the Effective Date of the Tax Juris Info field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date of the Tax Juris Info or the specified default value.
    */
   public final Date getTaxJurisDeff( Date defaultValue )
   {
      return _TaxJurisDeff == null ? defaultValue : _TaxJurisDeff;
   }
                  
   /**
    * Gets the Tax Jurisdiction of the Entity field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Jurisdiction of the Entity or null.
    */
   public final String getTaxJuris()
   {
      return _TaxJuris;
   }
	
   /**
    * Gets the Tax Jurisdiction of the Entity field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction of the Entity or the specified default value.
    */
   public final String getTaxJuris( String defaultValue )
   {
      return _TaxJuris == null ? defaultValue : _TaxJuris;
   }
                  
   /**
    * Gets the EUSD Tax Option field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EUSD Tax Option or null.
    */
   public final String getEUSDTaxOption()
   {
      return _EUSDTaxOption;
   }
	
   /**
    * Gets the EUSD Tax Option field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EUSD Tax Option or the specified default value.
    */
   public final String getEUSDTaxOption( String defaultValue )
   {
      return _EUSDTaxOption == null ? defaultValue : _EUSDTaxOption;
   }
                  
   /**
    * Gets the Where Used field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Where Used or null.
    */
   public final String getWhereUsed()
   {
      return _WhereUsed;
   }
	
   /**
    * Gets the Where Used field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Used or the specified default value.
    */
   public final String getWhereUsed( String defaultValue )
   {
      return _WhereUsed == null ? defaultValue : _WhereUsed;
   }
                  
   /**
    * Gets the Entity Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Status or null.
    */
   public final Boolean getEntStatus()
   {
      return _EntStatus;
   }
	
   /**
    * Gets the Entity Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Status or the specified default value.
    */
   public final boolean getEntStatus( boolean defaultValue )
   {
      return _EntStatus == null ? defaultValue : _EntStatus.booleanValue();
   }
                  
   /**
    * Gets the Country of Birth of the account holder field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Country of Birth of the account holder or null.
    */
   public final String getCountryOfBirth()
   {
      return _CountryOfBirth;
   }
	
   /**
    * Gets the Country of Birth of the account holder field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country of Birth of the account holder or the specified default value.
    */
   public final String getCountryOfBirth( String defaultValue )
   {
      return _CountryOfBirth == null ? defaultValue : _CountryOfBirth;
   }
                  
   /**
    * Gets the Conact name for institutional entity field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Conact name for institutional entity or null.
    */
   public final String getContactName()
   {
      return _ContactName;
   }
	
   /**
    * Gets the Conact name for institutional entity field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Conact name for institutional entity or the specified default value.
    */
   public final String getContactName( String defaultValue )
   {
      return _ContactName == null ? defaultValue : _ContactName;
   }
                  
   /**
    * Gets the Email2 field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Email2 or null.
    */
   public final String getEmail2()
   {
      return _Email2;
   }
	
   /**
    * Gets the Email2 field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Email2 or the specified default value.
    */
   public final String getEmail2( String defaultValue )
   {
      return _Email2 == null ? defaultValue : _Email2;
   }
                  
   /**
    * Gets the Second Phone Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Second Phone Number or null.
    */
   public final String getSecondPhnNum()
   {
      return _SecondPhnNum;
   }
	
   /**
    * Gets the Second Phone Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Second Phone Number or the specified default value.
    */
   public final String getSecondPhnNum( String defaultValue )
   {
      return _SecondPhnNum == null ? defaultValue : _SecondPhnNum;
   }
                  
   /**
    * Gets the Second Phone Number Extension field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Second Phone Number Extension or null.
    */
   public final String getSecondPhnNumExt()
   {
      return _SecondPhnNumExt;
   }
	
   /**
    * Gets the Second Phone Number Extension field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Second Phone Number Extension or the specified default value.
    */
   public final String getSecondPhnNumExt( String defaultValue )
   {
      return _SecondPhnNumExt == null ? defaultValue : _SecondPhnNumExt;
   }
                  
   /**
    * Gets the FATCAFFI field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the FATCAFFI or null.
    */
   public final String getFATCAFFI()
   {
      return _FATCAFFI;
   }
	
   /**
    * Gets the FATCAFFI field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FATCAFFI or the specified default value.
    */
   public final String getFATCAFFI( String defaultValue )
   {
      return _FATCAFFI == null ? defaultValue : _FATCAFFI;
   }
                  
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the ID Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type or null.
    */
   public final String getIdType( int index )
   {
      return _IdType[index];
   }
    
   /**
    * Gets the ID Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type or the specified default value.
    */
   public final String getIdType( int index, String defaultValue )
   {
      return _IdType[index] == null ? defaultValue : _IdType[index];
   }
    
   /**
    * Gets the array of ID Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type values.
    */
   public final String[] getIdTypeArray()
   {
      return _IdType;
   }
    
   /**
    * Gets the ID Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Type Description or null.
    */
   public final String getIdTypeDesc( int index )
   {
      return _IdTypeDesc[index];
   }
    
   /**
    * Gets the ID Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Type Description or the specified default value.
    */
   public final String getIdTypeDesc( int index, String defaultValue )
   {
      return _IdTypeDesc[index] == null ? defaultValue : _IdTypeDesc[index];
   }
    
   /**
    * Gets the array of ID Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Type Description values.
    */
   public final String[] getIdTypeDescArray()
   {
      return _IdTypeDesc;
   }
    
   /**
    * Gets the ID Value field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Value or null.
    */
   public final String getIdValue( int index )
   {
      return _IdValue[index];
   }
    
   /**
    * Gets the ID Value field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Value or the specified default value.
    */
   public final String getIdValue( int index, String defaultValue )
   {
      return _IdValue[index] == null ? defaultValue : _IdValue[index];
   }
    
   /**
    * Gets the array of ID Value fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Value values.
    */
   public final String[] getIdValueArray()
   {
      return _IdValue;
   }
    
   /**
    * Gets the ID Issue Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Issue Date or null.
    */
   public final Date getIdDate( int index )
   {
      return _IdDate[index];
   }
    
   /**
    * Gets the ID Issue Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Issue Date or the specified default value.
    */
   public final Date getIdDate( int index, Date defaultValue )
   {
      return _IdDate[index] == null ? defaultValue : _IdDate[index];
   }
    
   /**
    * Gets the array of ID Issue Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Issue Date values.
    */
   public final Date[] getIdDateArray()
   {
      return _IdDate;
   }
    
   /**
    * Gets the Entity-Search Id Version Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity-Search Id Version Number or null.
    */
   public final Integer getEntitySearchIdVer( int index )
   {
      return _EntitySearchIdVer[index];
   }
    
   /**
    * Gets the Entity-Search Id Version Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity-Search Id Version Number or the specified default value.
    */
   public final int getEntitySearchIdVer( int index, int defaultValue )
   {
      return _EntitySearchIdVer[index] == null ? defaultValue : _EntitySearchIdVer[index].intValue();
   }
    
   /**
    * Gets the array of Entity-Search Id Version Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity-Search Id Version Number values.
    */
   public final Integer[] getEntitySearchIdVerArray()
   {
      return _EntitySearchIdVer;
   }
    
   /**
    * Gets the Recid of Entity-Search Id record field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Recid of Entity-Search Id record or null.
    */
   public final Integer getEntitySearchIdRid( int index )
   {
      return _EntitySearchIdRid[index];
   }
    
   /**
    * Gets the Recid of Entity-Search Id record field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Recid of Entity-Search Id record or the specified default value.
    */
   public final int getEntitySearchIdRid( int index, int defaultValue )
   {
      return _EntitySearchIdRid[index] == null ? defaultValue : _EntitySearchIdRid[index].intValue();
   }
    
   /**
    * Gets the array of Recid of Entity-Search Id record fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Recid of Entity-Search Id record values.
    */
   public final Integer[] getEntitySearchIdRidArray()
   {
      return _EntitySearchIdRid;
   }
    
   /**
    * Gets the ID Status field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ID Status or null.
    */
   public final String getIDStatus( int index )
   {
      return _IDStatus[index];
   }
    
   /**
    * Gets the ID Status field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ID Status or the specified default value.
    */
   public final String getIDStatus( int index, String defaultValue )
   {
      return _IDStatus[index] == null ? defaultValue : _IDStatus[index];
   }
    
   /**
    * Gets the array of ID Status fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ID Status values.
    */
   public final String[] getIDStatusArray()
   {
      return _IDStatus;
   }
    
   /**
    * Gets the Allow Override field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Allow Override or null.
    */
   public final Boolean getAllowOverride( int index )
   {
      return _AllowOverride[index];
   }
    
   /**
    * Gets the Allow Override field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Allow Override or the specified default value.
    */
   public final boolean getAllowOverride( int index, boolean defaultValue )
   {
      return _AllowOverride[index] == null ? defaultValue : _AllowOverride[index].booleanValue();
   }
    
   /**
    * Gets the array of Allow Override fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Allow Override values.
    */
   public final Boolean[] getAllowOverrideArray()
   {
      return _AllowOverride;
   }
    
   /**
    * Gets the Country Of Issue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Of Issue or null.
    */
   public final String getCountryofIssue( int index )
   {
      return _CountryofIssue[index];
   }
    
   /**
    * Gets the Country Of Issue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Of Issue or the specified default value.
    */
   public final String getCountryofIssue( int index, String defaultValue )
   {
      return _CountryofIssue[index] == null ? defaultValue : _CountryofIssue[index];
   }
    
   /**
    * Gets the array of Country Of Issue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Of Issue values.
    */
   public final String[] getCountryofIssueArray()
   {
      return _CountryofIssue;
   }
    
   /**
    * Gets the IdExpireDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IdExpireDate or null.
    */
   public final Date getIdExpireDate( int index )
   {
      return _IdExpireDate[index];
   }
    
   /**
    * Gets the IdExpireDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IdExpireDate or the specified default value.
    */
   public final Date getIdExpireDate( int index, Date defaultValue )
   {
      return _IdExpireDate[index] == null ? defaultValue : _IdExpireDate[index];
   }
    
   /**
    * Gets the array of IdExpireDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IdExpireDate values.
    */
   public final Date[] getIdExpireDateArray()
   {
      return _IdExpireDate;
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
      _Salutation = responseBuffer.decodeString(responseBuffer.getNextField());
      _LastName = responseBuffer.decodeString(responseBuffer.getNextField());
      _FirstName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BirthLastName = responseBuffer.decodeString(responseBuffer.getNextField());
      _BirthFirstName = responseBuffer.decodeString(responseBuffer.getNextField());
      _DofBirth = responseBuffer.decodeDate(responseBuffer.getNextField());
      _Gender = responseBuffer.decodeString(responseBuffer.getNextField());
      _SIN = responseBuffer.decodeString(responseBuffer.getNextField());
      _OccupationCode = responseBuffer.decodeString(responseBuffer.getNextField());
      _OccupationDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _Lang = responseBuffer.decodeString(responseBuffer.getNextField());
      _Language = responseBuffer.decodeString(responseBuffer.getNextField());
      _HomePhone = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusinessPhone = responseBuffer.decodeString(responseBuffer.getNextField());
      _BuisnessExt = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusinessFax = responseBuffer.decodeString(responseBuffer.getNextField());
      _Telex = responseBuffer.decodeString(responseBuffer.getNextField());
      _Email = responseBuffer.decodeString(responseBuffer.getNextField());
      _DofDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _DofDeathNotice = responseBuffer.decodeDate(responseBuffer.getNextField());
      _EffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ProcessDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ModDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _Username = responseBuffer.decodeString(responseBuffer.getNextField());
      _ModUser = responseBuffer.decodeString(responseBuffer.getNextField());
      _HomeFax = responseBuffer.decodeString(responseBuffer.getNextField());
      _EntityIdentityVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _EntityIdentityRid = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _HomePhoneCntry = responseBuffer.decodeString(responseBuffer.getNextField());
      _HomePhoneArea = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusinessPhoneCntry = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusinessPhoneArea = responseBuffer.decodeString(responseBuffer.getNextField());
      _HomeFaxCntry = responseBuffer.decodeString(responseBuffer.getNextField());
      _HomeFaxArea = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusFaxCntry = responseBuffer.decodeString(responseBuffer.getNextField());
      _BusFaxArea = responseBuffer.decodeString(responseBuffer.getNextField());
      _EmployeeFlag = responseBuffer.decodeString(responseBuffer.getNextField());
      _Nationality = responseBuffer.decodeString(responseBuffer.getNextField());
      _OtherOccupation = responseBuffer.decodeString(responseBuffer.getNextField());
      _SpouseEntityID = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _PlaceOfBirth = responseBuffer.decodeString(responseBuffer.getNextField());
      _RiskLevel = responseBuffer.decodeString(responseBuffer.getNextField());
      _TaxJurisDeff = responseBuffer.decodeDate(responseBuffer.getNextField());
      _TaxJuris = responseBuffer.decodeString(responseBuffer.getNextField());
      _EUSDTaxOption = responseBuffer.decodeString(responseBuffer.getNextField());
      _WhereUsed = responseBuffer.decodeString(responseBuffer.getNextField());
      _EntStatus = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CountryOfBirth = responseBuffer.decodeString(responseBuffer.getNextField());
      _ContactName = responseBuffer.decodeString(responseBuffer.getNextField());
      _Email2 = responseBuffer.decodeString(responseBuffer.getNextField());
      _SecondPhnNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _SecondPhnNumExt = responseBuffer.decodeString(responseBuffer.getNextField());
      _FATCAFFI = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _IdType = resizeArray( _IdType, _RepeatCount );
      _IdTypeDesc = resizeArray( _IdTypeDesc, _RepeatCount );
      _IdValue = resizeArray( _IdValue, _RepeatCount );
      _IdDate = resizeArray( _IdDate, _RepeatCount );
      _EntitySearchIdVer = resizeArray( _EntitySearchIdVer, _RepeatCount );
      _EntitySearchIdRid = resizeArray( _EntitySearchIdRid, _RepeatCount );
      _IDStatus = resizeArray( _IDStatus, _RepeatCount );
      _AllowOverride = resizeArray( _AllowOverride, _RepeatCount );
      _CountryofIssue = resizeArray( _CountryofIssue, _RepeatCount );
      _IdExpireDate = resizeArray( _IdExpireDate, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _IdType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdValue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EntitySearchIdVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntitySearchIdRid[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _IDStatus[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AllowOverride[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _CountryofIssue[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IdExpireDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
      }
      

   }

}
      
