//******************************************************************************
//
// ^FILE   : AWDBPConfig.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 18, 2005
//
// ^CLASS    : AWDBPConfig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

//#include <boost\utility.hpp>

#include <map>
#include <vector>

#include <iostream>
#include <string>
class SectionDataIter;
class  AWDBPConfig
{
public:	
	AWDBPConfig();
	~AWDBPConfig();
   std::string getUserID();
   std::string getPassword();
   std::string getLanguage();
   std::string getLogOff();
   std::string getFundGroup();
   std::string getAccountName();
   std::string getCompanyIdByLobData(const  std::string& lobCmpId );
   std::string getPortNum();
   std::string getIPAddress();
   std::string getLogDirectory();
   std::string getCBOFieldNameByLobField(const  std::string& cboName, 
                                       const  std::string& lobField );
   
   std::string getLobFieldNameByCBOField(const  std::string& cboName, 
                                       const  std::string& cboField );
   std::string getFieldValueInSection( const  std::string& section,const  std::string& key);

    void init();

   class SectionData
   {
      public:
         SectionData();
         ~SectionData();
         std::string getKeyByValue( const  std::string& value );
         std::string getValueByKey( const  std::string& key ); 
         void addSectionData(const  std::string& key,const  std::string& value );

      private:
         typedef std::map< std::string, std::string*  >                          SEC_DATA_MAP;
         typedef SEC_DATA_MAP::iterator                                  SEC_DATA_ITER;
         typedef SEC_DATA_MAP::value_type                                SEC_DATA_VALUE_TYPE;
         SEC_DATA_MAP _sectionData;
         friend SectionDataIter;
   };
  SectionData* getSectionData(const  std::string & secName )
   {
      SectionData* pSectionData = NULL;
      SECTION_DETAIL_ITER iter = _sectionDetail.find( secName );
      if( iter != _sectionDetail.end() )
      {
         pSectionData = (*iter).second;   
      }
      return pSectionData;
   };
 

private:
   void registerSection( std::string secName );
   void deregistSection();
  
   void readSectionData( const  std::string& secName  );
 
   class SectionDataIter;
private:
   typedef std::vector< std::string* >         SECTION_VECTOR;
   typedef SECTION_VECTOR::iterator       SECTION_VECTOR_ITER;
   SECTION_VECTOR _section;

   typedef std::map<  std::string, SectionData*  >                 SECTION_DETAIL_MAP;
   typedef SECTION_DETAIL_MAP::iterator                       SECTION_DETAIL_ITER;
   typedef SECTION_DETAIL_MAP::value_type                     SECTION_DETAIL_VALUE_TYPE;
   SECTION_DETAIL_MAP _sectionDetail;

   char   _fileName[96];
};


class SectionDataIter
{
   public:
      SectionDataIter(AWDBPConfig::SectionData* pSD);
      ~SectionDataIter(){};
      std::string getSectionKey();
      std::string getSectionValue();

      bool begin();
      bool end();
      bool operator ++();
   private:
      AWDBPConfig::SectionData::SEC_DATA_ITER _curIter;
      AWDBPConfig::SectionData* _pSD;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AWDBPConfig.hpp-arc  $
//
//   Rev 1.2   Nov 14 2005 11:39:34   yingbaol
//PET1332,FN09:fix issue
//
//   Rev 1.1   Nov 08 2005 14:15:00   yingbaol
//PET1332,FN09: remove DString and infra structure
//
//   Rev 1.0   Oct 31 2005 14:47:30   yingbaol
//Initial revision.
 * 
 *

 */

