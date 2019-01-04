//******************************************************************************
//
// ^FILE   : DSTCAWDDataConvert.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Dec. 18, 2003
//
// ^CLASS    : DSTCAWDDataConvert
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <bfdata\bfdata.hpp>

#undef IFASTAWD_LINKAGE
#ifdef IFASTAWD_DLL
   #define IFASTAWD_LINKAGE CLASS_EXPORT
#else
   #define IFASTAWD_LINKAGE CLASS_IMPORT
#endif


class DSTCAWDSession;
class Configuration;
class IFASTAWD_LINKAGE DSTCAWDDataConvert
{
public:	
	DSTCAWDDataConvert(DSTCAWDSession* pSession);
	~DSTCAWDDataConvert();
	void getExportAwdCallerInfo( BFData &data  );
	void getAwdFormatData(const DString& eventTable,BFData& awdData);
	void retrieveAwdBusinessArea(DString& dstrMgmtCoId,
												 DString& dstrBusinessArea );

private:

	  DSTCAWDSession* getSession()
	  {
		return m_pSession;  
	  };	
	  void retrieveCBOInfo(const BFAbstractCBO* pcbo,Configuration& cfg,BFData& data);
	  void getAwdFieldFromCBO(const DString& dstrTabName,BFData& data);
	  void convertFieldValueForMarket(const BFFieldId& fieldId,DString& dstrInOut );

	  DSTCAWDSession*		m_pSession;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastawd/DSTCAWDDataConvert.hpp-arc  $
//
//   Rev 1.5   Jan 22 2004 11:43:28   PURDYECH
//PET987 - Removed unnecessary #include if <ifastcbo/mfcancbo.hpp> and added PVCS logging section.
//
